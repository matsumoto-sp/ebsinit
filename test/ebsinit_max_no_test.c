#include "ebsinit_test.h"
#include "../ebsinit.c"

int main()
{
    #define BLOCK (512 * 1024)
    ebsinit_handle h = ebsinit_alloc(123);
    ASSERT(ebsinit_max_no(h, 0, 0) == 0);
    ASSERT(ebsinit_max_no(h, 0, 1) == 1);
    ASSERT(ebsinit_max_no(h, 0, 2) == 1);
    ASSERT(ebsinit_max_no(h, 0, BLOCK - 1) == 1);
    ASSERT(ebsinit_max_no(h, 0, BLOCK) == 1);
    ASSERT(ebsinit_max_no(h, 0, BLOCK + 1) == 1);
    ASSERT(ebsinit_max_no(h, 0, 2 * BLOCK) == 1);
    ASSERT(ebsinit_max_no(h, 0, 3 * BLOCK - 1) == 1);
    ASSERT(ebsinit_max_no(h, 0, 3 * BLOCK) == 1);
    ASSERT(ebsinit_max_no(h, 0, 123 * BLOCK) == 1);
    ASSERT(ebsinit_max_no(h, 0, 123 * BLOCK + 1) == 2);
    ASSERT(ebsinit_max_no(h, 0, 2 * 123 * BLOCK - 1) == 2);
    ASSERT(ebsinit_max_no(h, 0, 3 * 123 * BLOCK - 1) == 3);
    ASSERT(ebsinit_max_no(h, 0, 3 * 123 * BLOCK) == 3);

    ASSERT(ebsinit_max_no(h, 1, 0) == 0);
    ASSERT(ebsinit_max_no(h, 1, BLOCK) == 1);
    ASSERT(ebsinit_max_no(h, BLOCK - 1, BLOCK) == 1);
    ASSERT(ebsinit_max_no(h, BLOCK, BLOCK) == 0);
    ASSERT(ebsinit_max_no(h, BLOCK, BLOCK * 2) == 1);
    ASSERT(ebsinit_max_no(h, BLOCK * 2, BLOCK * 2) == 0);
    ASSERT(ebsinit_max_no(h, BLOCK * 2 - 1, BLOCK * 2) == 1);
    ASSERT(ebsinit_max_no(h, BLOCK * 2 - 1, 123 * BLOCK) == 1);
    ASSERT(ebsinit_max_no(h, BLOCK * 123, 123 * BLOCK * 2) == 1);
    ASSERT(ebsinit_max_no(h, BLOCK * 123 - 1, 123 * BLOCK * 2) == 2);
    ASSERT(ebsinit_max_no(h, BLOCK * 123 + 1, 123 * BLOCK * 2) == 1);
    ASSERT(ebsinit_max_no(h, BLOCK * 123 - 1, 123 * BLOCK * 2) == 2);
    ASSERT(ebsinit_max_no(h, BLOCK * 123 - 1, 123 * BLOCK * 2 + BLOCK - 1) == 2);
    ASSERT(ebsinit_max_no(h, BLOCK * 123 - 1, 123 * BLOCK * 3 - BLOCK) == 2);
    ASSERT(ebsinit_max_no(h, BLOCK * 123 - 1, 123 * BLOCK * 3 - BLOCK) == 2);
    ASSERT(ebsinit_max_no(h, BLOCK * 123 - 1, 123 * BLOCK * 3 - BLOCK + 1) == 3);
    return 0;
}
