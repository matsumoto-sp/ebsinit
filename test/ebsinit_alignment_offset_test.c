#include "ebsinit_test.h"
#include "../ebsinit.c"

int main()
{
    ebsinit_handle h = ebsinit_alloc(10);
    ASSERT(ebsinit_alignment_offset(h, 0) == 0);
    ASSERT(ebsinit_alignment_offset(h, 1) == 0);
    ASSERT(ebsinit_alignment_offset(h, 512 * 1024 - 1) == 0);
    ASSERT(ebsinit_alignment_offset(h, 512 * 1024) == 512 * 1024);
    ASSERT(ebsinit_alignment_offset(h, 512 * 1024 * 2 - 1) == 512 * 1024);
    ASSERT(ebsinit_alignment_offset(h, 512 * 1024 * 2) == 512 * 1024 * 2);
    ASSERT(ebsinit_alignment_offset(h, 512 * 1024 * 3 - 1) == 512 * 1024 * 2);
    return 0;
}
