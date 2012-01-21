#ifndef LOG_H_
#define LOG_H_

#ifdef NDEBUG
#   include <stdio.h>
#endif

#ifdef NDEBUG
#   define LOG_DEBUG(...) do { fprintf(stderr, "[DEBUG] " __VA_ARGS__); fprintf(stderr, "\n"); } while(0)
#else
#   define LOG_DEBUG(...)
#endif

#endif
