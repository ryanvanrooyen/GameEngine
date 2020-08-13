

#define WARN(msg) fprintf(stderr, msg)
#define WARNF(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)

#define CHECK(x, msg) if (!(x)) WARN(msg)

#ifdef DEBUG
    #define ASSERT(x) if (!(x)) __asm__("int $3")
    #define DEBUG_CHECK(x, msg) if (!(x)) WARN(msg)
    #define DEBUG_CHECKF(x, fmt, ...) if (!(x)) WARNF(fmt, __VA_ARGS__)
#else
    #define ASSERT(x)
    #define DEBUG_CHECK(x, msg)
    #define DEBUG_CHECKF(x, fmt, ...)
#endif
