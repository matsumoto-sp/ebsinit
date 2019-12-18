#include "ebsinit_test.h"
#include "../ebsinit.c"

int main()
{
    ebsinit_handle h = ebsinit_alloc(3000);
    h->buf[0] = 12;
    h->buf[1] = 34;
    h->buf[2] = 56;
    h->buf[3] = 78;
    h->read_size = 12345;
    ebsinit_setup(h, 123);
    int i = 0;
    for (; i < 3000; i++) {
        ASSERT(h->iocb_tbl[i]== h->iocbs + i);
        ASSERT(h->iocbs[i].aio_fildes == 123);
        ASSERT(h->iocbs[i].aio_lio_opcode == IOCB_CMD_PREAD);
        ASSERT(((char*)h->iocbs[i].aio_buf)[0] == 12);
        ASSERT(((char*)h->iocbs[i].aio_buf)[1] == 34);
        ASSERT(((char*)h->iocbs[i].aio_buf)[2] == 56);
        ASSERT(((char*)h->iocbs[i].aio_buf)[3] == 78);
        ASSERT(h->iocbs[i].aio_nbytes == 12345);
    }
    ebsinit_release(h);
    return 0;
}
