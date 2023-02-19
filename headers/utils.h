#define UNIMPLEMENTED(...)                                                     \
  do {                                                                         \
    printf("%s:%d: UNIMPLEMENTED: %s \n", __FILE__, __LINE__, __VA_ARGS__);    \
    exit(1);                                                                   \
  } while (0);
