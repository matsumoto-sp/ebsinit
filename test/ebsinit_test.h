#define ASSERT(r) { \
  if (!(r)) { \
    printf("%s(%d): %s", __FILE__, __LINE__, #r); \
    exit(1); \
  } \
}
