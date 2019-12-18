/**
 * @file ebsinit.c
 * @brief Core processing of ebsinit
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/aio_abi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <signal.h>

/**
 * @brief data class
 */
typedef struct tag_ebsinit_data {
    /** Number of concurrent IO executions */
    int io_range;
    /** Temporary buffer */
    char* buf;
    /** File descriptor of target device */
    int fd;
    /** Pointer array of IO to be executed simultaneously */
    struct iocb** iocb_tbl;
    /** Array of IO to be executed simultaneously */
    struct iocb* iocbs;
    /** Size of target device */
    __u64 file_size;
    /** Seek amount per operation */
    __u64 step_range;
    /** Read size per operation */
    __u64 read_size;
    /** Event receive buffer */
    struct io_event* events;
    /** Function pointer of core processing */
    int (*core)(struct tag_ebsinit_data*, int);
    /** Function pointer of progress display process */
    void (*print)(struct tag_ebsinit_data*, int, int);
    /** User data */
    void* user_data;
} ebsinit_data;

/**
 * @brief handle for ebsinit_data
 */
typedef ebsinit_data* ebsinit_handle;

int ebsinit_core(ebsinit_handle h, int range);
void ebsinit_print(ebsinit_handle h, int cur_no, int max_no);

/**
 * @brief initialize memory
 * @param io_range Number of concurrent IO executions
 * @return handle of ebsinit
 */
ebsinit_handle ebsinit_alloc(int io_range)
{
    ebsinit_handle out = malloc(sizeof(ebsinit_data));
    if (!out) {
        return NULL;
    }
    out->io_range = io_range;
    out->step_range = 512 * 1024;
    out->read_size = 512;
    out->core = ebsinit_core;
    out->print = ebsinit_print;
    posix_memalign((void*)&(out->buf), 512, out->read_size);
    out->iocb_tbl = (struct iocb**)malloc(sizeof(struct iocb*) * io_range);
    if (!out->iocb_tbl) {
        free(out);
        return NULL;
    }
    out->iocbs = (struct iocb*)malloc(sizeof(struct iocb) * io_range);
    if (!out->iocbs) {
        free(out->iocb_tbl);
        free(out);
        return NULL;
    }
    out->events = (struct io_event*)malloc(sizeof(struct io_event) * io_range);
    if (!out->events) {
        free(out->iocbs);
        free(out->iocb_tbl);
        free(out);
        return NULL;
    }
    return out;
}

/**
 * @brief release ebsinit_handle
 * @param h handle
 */
void ebsinit_release(ebsinit_handle h)
{
    free(h->events);
    free(h->iocbs);
    free(h->iocb_tbl);
    free(h->buf);
    free(h);
}

/**
 * @brief setup tables
 * @param h handle
 * @param fd File descriptor of target device 
 */
void ebsinit_setup(ebsinit_handle h, int fd)
{
    int i = 0;
    for (; i < h->io_range; i++) {
        h->iocb_tbl[i] = h->iocbs + i;
        memset(h->iocbs + i, 0, sizeof(struct iocb));
        h->iocbs[i].aio_lio_opcode = IOCB_CMD_PREAD;
        h->iocbs[i].aio_fildes = fd;
        h->iocbs[i].aio_buf = (__u64)h->buf;
        h->iocbs[i].aio_nbytes = h->read_size;
    }
}

/**
 * @brief Align the file pointer offset
 * @param h handle
 * @param offset file pointer offset
 * @return Aligned value
 */
__u64 ebsinit_alignment_offset(ebsinit_handle h, __u64 offset)
{
    return offset / h->step_range * h->step_range;
}

/**
 * @brief Run IO
 * @param h handle
 * @param range Number of IOs to execute at a time
 * @return Zero or error code
 */
int ebsinit_core(ebsinit_handle h, int range)
{
    aio_context_t laio;
    memset(&laio, 0, sizeof(laio));
    int err = syscall(SYS_io_setup, range, &laio);
    if (err < 0) {
        return -err;
    }
    err = syscall(SYS_io_submit, laio, range, h->iocb_tbl);
    if (err < 0) {
        return -err;
    }
    err = syscall(SYS_io_getevents, laio, range, range, h->events, NULL);
    if (err < 0) {
        return -err;
    }
    err = syscall(SYS_io_destroy, laio);
    if (err < 0) {
        return -err;
    }
    return 0;
}

/**
 * @brief Calculate the number of processes
 * @param h handle
 * @param offset file pointer offset
 * @param size file size
 * @return number of processes
 */
int ebsinit_max_no(ebsinit_handle h, __u64 offset, __u64 size)
{
    offset = ebsinit_alignment_offset(h, offset);
    return (size - offset + h->step_range * h->io_range - 1)
        / (h->step_range * h->io_range);
}

/**
 * @brief Show progress
 * @param h handle
 * @param cur_no Current processing number
 * @param max_no Maximum processing number
 *
 * The default implementation does nothing. You must change 
 * the handler's function pointer to execute the appropriate 
 * display function.
 */
void ebsinit_print(ebsinit_handle h, int cur_no, int max_no)
{
}

/**
 * @brief Perform initialization
 * @param h handle
 * @param offset file pointer offset
 * @param size file size
 * @return Zero or error code
 */
int ebsinit_do(ebsinit_handle h, __u64 offset, __u64 size)
{
    __u64 i = ebsinit_alignment_offset(h, offset);
    int cur_no = 1;
    int max_no = ebsinit_max_no(h, i, size);
    for (; i < size; i+= h->step_range * h->io_range, cur_no++) {
        int j = 0;
        for (; j < h->io_range && i + (__u64)j * h->step_range < size; j++) {
            h->iocbs[j].aio_offset = i + (__u64)j * h->step_range;
        }
        if ((errno = h->core(h, j)) != 0) {
            return errno;
        }
        h->print(h, cur_no, max_no);
    }
    return 0;
}
