
#pragma once

#include <stdio.h>

#ifndef LOGLEVEL
    #define LOGLEVEL 0
#endif

#ifdef DEBUG
    #define BREAKPOINT() __asm__("int $3")
#else
    #define BREAKPOINT()
#endif

#if LOGLEVEL > 0
    #define LOG(level, file, line, msg, ...) fprintf(stderr, "%s: ./%s:%d: " msg "\n", level, file, line, ##__VA_ARGS__)
    #define ERROR(...) LOG("ERROR", __FILE__, __LINE__, __VA_ARGS__)
    #define ERROR_DETAILS(file, line, msg, ...) LOG("ERROR", file, line, msg, __VA_ARGS__)
    #define ASSERT(x, ...) if (!(x)) { BREAKPOINT(); ERROR(__VA_ARGS__); }
#else
    #define LOG(level, file, line, msg, ...)
    #define ERROR(...)
    #define ERROR_DETAILS(file, line, msg, ...) LOG("ERROR", file, line, msg, __VA_ARGS__)
    #define ASSERT(x, ...)
#endif

#if LOGLEVEL > 1
    #define WARN(...) LOG("WARN", __FILE__, __LINE__, __VA_ARGS__)
    #define ASSERT_WARN(x, ...) if (!(x)) WARN(__VA_ARGS__)
#else
    #define WARN(...)
    #define ASSERT_WARN(x, ...)
#endif

#if LOGLEVEL > 2
    #define INFO(...) LOG("INFO", __FILE__, __LINE__, __VA_ARGS__)
    #define ASSERT_INFO(x, ...) if (!(x)) INFO(__VA_ARGS__)
#else
    #define INFO(...)
    #define ASSERT_INFO(x, ...)
#endif
