#include "ebsinit_test.h"
#include "../ebsinit.c"

#define BLOCK (512 * 1024)

int core_test_1(ebsinit_handle h, int range)
{
    static int count = 0;
    ASSERT(count < 1);
    ASSERT(range == 1);
    count++;
    return 0;
}

int core_test_2(ebsinit_handle h, int range)
{
    static int count = 0;
    ASSERT(count < 2);
    if (count == 0) {
        ASSERT(range == 7);
        ASSERT(h->iocbs[0].aio_offset == 0);
        ASSERT(h->iocbs[1].aio_offset == BLOCK * 1);
        ASSERT(h->iocbs[2].aio_offset == BLOCK * 2);
        ASSERT(h->iocbs[3].aio_offset == BLOCK * 3);
        ASSERT(h->iocbs[4].aio_offset == BLOCK * 4);
        ASSERT(h->iocbs[5].aio_offset == BLOCK * 5);
        ASSERT(h->iocbs[6].aio_offset == BLOCK * 6);
    } else {
        ASSERT(range == 3);
        ASSERT(h->iocbs[0].aio_offset == BLOCK * 7);
        ASSERT(h->iocbs[1].aio_offset == BLOCK * 8);
        ASSERT(h->iocbs[2].aio_offset == BLOCK * 9);
    }
    count++;
    return 0;
}

int core_test_3(ebsinit_handle h, int range)
{
    static int count = 0;
    ASSERT(count < 2);
    if (count == 0) {
        ASSERT(range == 7);
        ASSERT(h->iocbs[0].aio_offset == 0);
        ASSERT(h->iocbs[1].aio_offset == BLOCK * 1);
        ASSERT(h->iocbs[2].aio_offset == BLOCK * 2);
        ASSERT(h->iocbs[3].aio_offset == BLOCK * 3);
        ASSERT(h->iocbs[4].aio_offset == BLOCK * 4);
        ASSERT(h->iocbs[5].aio_offset == BLOCK * 5);
        ASSERT(h->iocbs[6].aio_offset == BLOCK * 6);
    } else {
        ASSERT(range == 3);
        ASSERT(h->iocbs[0].aio_offset == BLOCK * 7);
        ASSERT(h->iocbs[1].aio_offset == BLOCK * 8);
        ASSERT(h->iocbs[2].aio_offset == BLOCK * 9);
    }
    count++;
    return 0;
}

int core_test_4(ebsinit_handle h, int range)
{
    static int count = 0;
    ASSERT(count < 2);
    if (count == 0) {
        ASSERT(range == 7);
        ASSERT(h->iocbs[0].aio_offset == BLOCK * 1);
        ASSERT(h->iocbs[1].aio_offset == BLOCK * 2);
        ASSERT(h->iocbs[2].aio_offset == BLOCK * 3);
        ASSERT(h->iocbs[3].aio_offset == BLOCK * 4);
        ASSERT(h->iocbs[4].aio_offset == BLOCK * 5);
        ASSERT(h->iocbs[5].aio_offset == BLOCK * 6);
        ASSERT(h->iocbs[6].aio_offset == BLOCK * 7);
    } else {
        ASSERT(range == 2);
        ASSERT(h->iocbs[0].aio_offset == BLOCK * 8);
        ASSERT(h->iocbs[1].aio_offset == BLOCK * 9);
    }
    count++;
    return 0;
}

int core_test_5(ebsinit_handle h, int range)
{
    static int count = 0;
    ASSERT(count < 2);
    if (count == 0) {
        ASSERT(range == 7);
        ASSERT(h->iocbs[0].aio_offset == BLOCK * 1);
        ASSERT(h->iocbs[1].aio_offset == BLOCK * 2);
        ASSERT(h->iocbs[2].aio_offset == BLOCK * 3);
        ASSERT(h->iocbs[3].aio_offset == BLOCK * 4);
        ASSERT(h->iocbs[4].aio_offset == BLOCK * 5);
        ASSERT(h->iocbs[5].aio_offset == BLOCK * 6);
        ASSERT(h->iocbs[6].aio_offset == BLOCK * 7);
    } else {
        ASSERT(range == 2);
        ASSERT(h->iocbs[0].aio_offset == BLOCK * 8);
        ASSERT(h->iocbs[1].aio_offset == BLOCK * 9);
    }
    count++;
    return 0;
}

int core_test_6(ebsinit_handle h, int range)
{
    static int count = 0;
    ASSERT(count < 2);
    if (count == 0) {
        ASSERT(range == 7);
        ASSERT(h->iocbs[0].aio_offset == BLOCK * 1);
        ASSERT(h->iocbs[1].aio_offset == BLOCK * 2);
        ASSERT(h->iocbs[2].aio_offset == BLOCK * 3);
        ASSERT(h->iocbs[3].aio_offset == BLOCK * 4);
        ASSERT(h->iocbs[4].aio_offset == BLOCK * 5);
        ASSERT(h->iocbs[5].aio_offset == BLOCK * 6);
        ASSERT(h->iocbs[6].aio_offset == BLOCK * 7);
    } else {
        ASSERT(range == 2);
        ASSERT(h->iocbs[0].aio_offset == BLOCK * 8);
        ASSERT(h->iocbs[1].aio_offset == BLOCK * 9);
    }
    count++;
    return 0;
}

int core_test_7(ebsinit_handle h, int range)
{
    static int count = 0;
    ASSERT(count < 2);
    if (count == 0) {
        ASSERT(range == 7);
        ASSERT(h->iocbs[0].aio_offset == BLOCK * 2);
        ASSERT(h->iocbs[1].aio_offset == BLOCK * 3);
        ASSERT(h->iocbs[2].aio_offset == BLOCK * 4);
        ASSERT(h->iocbs[3].aio_offset == BLOCK * 5);
        ASSERT(h->iocbs[4].aio_offset == BLOCK * 6);
        ASSERT(h->iocbs[5].aio_offset == BLOCK * 7);
        ASSERT(h->iocbs[6].aio_offset == BLOCK * 8);
    } else {
        ASSERT(range == 1);
        ASSERT(h->iocbs[0].aio_offset == BLOCK * 9);
    }
    count++;
    return 0;
}

int core_test_8(ebsinit_handle h, int range)
{
    static int count = 0;
    ASSERT(count < 2);
    if (count == 0) {
        ASSERT(range == 7);
        ASSERT(h->iocbs[0].aio_offset == BLOCK * 2);
        ASSERT(h->iocbs[1].aio_offset == BLOCK * 3);
        ASSERT(h->iocbs[2].aio_offset == BLOCK * 4);
        ASSERT(h->iocbs[3].aio_offset == BLOCK * 5);
        ASSERT(h->iocbs[4].aio_offset == BLOCK * 6);
        ASSERT(h->iocbs[5].aio_offset == BLOCK * 7);
        ASSERT(h->iocbs[6].aio_offset == BLOCK * 8);
    } else {
        ASSERT(range == 2);
        ASSERT(h->iocbs[0].aio_offset == BLOCK * 9);
        ASSERT(h->iocbs[1].aio_offset == BLOCK * 10);
    }
    count++;
    return 0;
}

int core_test_9(ebsinit_handle h, int range)
{
    static int count = 0;
    ASSERT(count < 1);
    ASSERT(h->iocbs[0].aio_offset == BLOCK * 0);
    ASSERT(h->iocbs[1].aio_offset == BLOCK * 1);
    ASSERT(h->iocbs[2].aio_offset == BLOCK * 2);
    ASSERT(h->iocbs[3].aio_offset == BLOCK * 3);
    ASSERT(h->iocbs[4].aio_offset == BLOCK * 4);
    ASSERT(h->iocbs[5].aio_offset == BLOCK * 5);
    ASSERT(h->iocbs[6].aio_offset == BLOCK * 6);
    count++;
    return 0;
}

int core_test_10(ebsinit_handle h, int range)
{
    static int count = 0;
    ASSERT(count < 2);
    if (count == 0) {
        ASSERT(range == 7);
        ASSERT(h->iocbs[0].aio_offset == BLOCK * 0);
        ASSERT(h->iocbs[1].aio_offset == BLOCK * 1);
        ASSERT(h->iocbs[2].aio_offset == BLOCK * 2);
        ASSERT(h->iocbs[3].aio_offset == BLOCK * 3);
        ASSERT(h->iocbs[4].aio_offset == BLOCK * 4);
        ASSERT(h->iocbs[5].aio_offset == BLOCK * 5);
        ASSERT(h->iocbs[6].aio_offset == BLOCK * 6);
    } else {
        ASSERT(range == 1);
        ASSERT(h->iocbs[0].aio_offset == BLOCK * 7);
    }
    count++;
    return 0;
}

int core_dummy(ebsinit_handle h, int range)
{
    return 0;
}

void print_test_1(ebsinit_handle h, int cur_no, int max_no)
{
    static int count = 0;
    ASSERT(count == 0);
    ASSERT(cur_no == 1);
    ASSERT(max_no == 1);
    count++;
}

void print_test_2(ebsinit_handle h, int cur_no, int max_no)
{
    static int count = 0;
    ASSERT(count <= 14);
    ASSERT(max_no == 15);
    ASSERT(cur_no == count + 1);
    count++;
}

int main()
{
    ebsinit_handle h = ebsinit_alloc(7);
    h->core = core_test_1;
    ebsinit_do(h, 0, 1000);
    h->core = core_test_2;
    ebsinit_do(h, 0, BLOCK * 10);
    h->core = core_test_3;
    ebsinit_do(h, 1024, BLOCK * 10);
    h->core = core_test_4;
    ebsinit_do(h, BLOCK, BLOCK * 10);
    h->core = core_test_5;
    ebsinit_do(h, BLOCK + 1, BLOCK * 10);
    h->core = core_test_6;
    ebsinit_do(h, BLOCK * 2 - 1, BLOCK * 10);
    h->core = core_test_7;
    ebsinit_do(h, BLOCK * 2, BLOCK * 10);
    h->core = core_test_8;
    ebsinit_do(h, BLOCK * 2, BLOCK * 10 + 1);
    h->core = core_test_9;
    ebsinit_do(h, 0, BLOCK * 7);
    h->core = core_test_10;
    ebsinit_do(h, 0, BLOCK * 7 + 1);
    h->core = core_dummy;
    h->print = print_test_1;
    ebsinit_do(h, 0, 1);
    h->print = print_test_2;
    ebsinit_do(h, 0, BLOCK * 100);
    return 0;
}
