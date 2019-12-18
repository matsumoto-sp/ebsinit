#include <malloc.h>
#include "ebsinit_test.h"
#include "../ebsinit.c"

int main()
{
    ebsinit_handle h = ebsinit_alloc(10);
    ASSERT(h != NULL);
    ASSERT(malloc_usable_size(h->buf) >= 512);
    ASSERT(malloc_usable_size(h->iocb_tbl) >= sizeof(struct iocb*) * 10);
    ASSERT(malloc_usable_size(h->iocbs) >= sizeof(struct iocb) * 10);
    ASSERT(malloc_usable_size(h->events) >= sizeof(struct io_event) * 10);
    ebsinit_release(h);
    return 0;
}
