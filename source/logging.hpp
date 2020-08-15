
#pragma once

#define LOGLEVEL 3

#define LOG(level, msg) fprintf(stderr, level msg "\n")
#define LOGF(level, fmt, ...) fprintf(stderr, level fmt "\n", __VA_ARGS__)

#if LOGLEVEL > 0
    #define ERROR(msg) LOG("ERROR: ", msg)
    #define ERRORF(fmt, ...) LOGF("ERROR: ", fmt, __VA_ARGS__)
#else
    #define ERROR(msg)
    #define ERRORF(fmt, ...)
#endif

#if LOGLEVEL > 1
    #define WARN(msg) LOG("WARN: ", msg)
    #define WARNF(fmt, ...) LOGF("WARN: ", fmt, __VA_ARGS__)
    #define ASSERT_WARN(x, msg) if (!(x)) { WARN(msg) }
    #define ASSERT_WARNF(x, fmt, ...) if (!(x)) WARNF(fmt, __VA_ARGS__)
#else
    #define WARN(msg)
    #define WARNF(fmt, ...)
    #define ASSERT_WARN(x, msg)
    #define ASSERT_WARNF(x, fmt, ...)
#endif

#if LOGLEVEL > 2
    #define INFO(msg) LOG("INFO: ", msg)
    #define INFOF(fmt, ...) LOGF("INFO: ", fmt, __VA_ARGS__)
#else
    #define INFO(msg)
    #define INFOF(fmt, ...)
#endif


#ifdef DEBUG
    #define ASSERT(x) if (!(x)) __asm__("int $3")
    #define DEBUG_CHECK(x, msg) if (!(x)) WARN(msg)
    #define DEBUG_CHECKF(x, fmt, ...) if (!(x)) WARNF(fmt, __VA_ARGS__)
#else
    #define ASSERT(x)
    #define DEBUG_CHECK(x, msg)
    #define DEBUG_CHECKF(x, fmt, ...)
#endif
