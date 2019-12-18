#include "ebsinit_test.h"
#include "../ebsinit.c"

static char fname[] = "/tmp/ebsinit_test_XXXXXX";

void create_test_file()
{
    int fd = mkstemp(fname);
    write(fd, "012345678", 10);
    lseek(fd, 512 - 10, SEEK_SET);
    write(fd, "ABCDEFGHI", 10);
    lseek(fd, 512 * 1024, SEEK_SET);
    write(fd, "KLMNOPQRS", 10);
    lseek(fd, 512 * 1024 + 512 - 10, SEEK_SET);
    write(fd, "UVWXYZ123", 10);
    close(fd);
}

void delete_test_file()
{
    unlink(fname);
}

int core_test(ebsinit_handle h, int range)
{
    static int count = 0;
    ASSERT(ebsinit_core(h, range) == 0);
    ASSERT(count <= 1);
    ASSERT(range == 1);
    if (count == 0) {
        ASSERT(strcmp(h->buf, "012345678") == 0);
        ASSERT(strcmp(h->buf + 512 - 10, "ABCDEFGHI") == 0);
    } else {
        ASSERT(strcmp(h->buf, "KLMNOPQRS") == 0);
        ASSERT(strcmp(h->buf + 512 - 10, "UVWXYZ123") == 0);
    }
    count++;
    return 0;
}

int main()
{
    create_test_file();
    ebsinit_handle h = ebsinit_alloc(1);
    h->core = core_test;
    int fd = open(fname, O_RDONLY | O_DIRECT);
    ebsinit_setup(h, fd);
    ebsinit_do(h, 0, 512 * 1024 + 512);
    close(fd);
    ebsinit_release(h);
    delete_test_file();
    return 0;
}
