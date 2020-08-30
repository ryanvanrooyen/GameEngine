
#pragma once

#include <stdio.h>
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include "spdlog/spdlog.h"


#ifndef LOGLEVEL
    #ifdef DEBUG
        #define LOGLEVEL 4
    #else
        #define LOGLEVEL 0
    #endif
#endif


#ifdef DEBUG
    #if defined(PLATFORM_MAC)
        #define BREAKPOINT() __asm__("int $3")
    #elif defined(PLATFORM_WINDOWS)
        #define BREAKPOINT() __debugbreak()
    #else
        #define BREAKPOINT()
    #endif
#else
    #define BREAKPOINT()
#endif


#if LOGLEVEL > 0
    #define ENABLE_LOGGING() spdlog::set_level(spdlog::level::trace)
    #define SET_LOG_FORMAT(fmt) spdlog::set_pattern(fmt)

    #define ERROR(...) BREAKPOINT(); SPDLOG_ERROR(__VA_ARGS__)
    #define ASSERT(x, ...) if (!(x)) { ERROR(__VA_ARGS__); }
#else
    #define ENABLE_LOGGING()
    #define SET_LOG_FORMAT(fmt)

    #define ERROR(...)
    #define ASSERT(x, ...)
#endif

#if LOGLEVEL > 1
    #define WARN(...) SPDLOG_WARN(__VA_ARGS__)
    #define ASSERT_WARN(x, ...) if (!(x)) { WARN(__VA_ARGS__); }
#else
    #define WARN(...)
    #define ASSERT_WARN(x, ...)
#endif

#if LOGLEVEL > 2
    #define INFO(...) SPDLOG_DEBUG(__VA_ARGS__)
    #define ASSERT_INFO(x, ...) if (!(x)) { INFO(__VA_ARGS__); }
#else
    #define INFO(...)
    #define ASSERT_INFO(x, ...)
#endif

#if LOGLEVEL > 3
    #define TRACE(...) SPDLOG_TRACE(__VA_ARGS__)
    #define ASSERT_TRACE(x, ...) if (!(x)) { TRACE(__VA_ARGS__); }
#else
    #define TRACE(...)
    #define ASSERT_TRACE(x, ...)
#endif
