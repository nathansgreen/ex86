#ifndef LOG_H_
#define LOG_H_

#ifdef NDEBUG
#   include <stdio.h>
#endif

#ifdef NDEBUG
#   define EX86_LOG_DEBUG(...) { fprintf(stderr, "[DEBUG] " __VA_ARGS__); fprintf(stderr, "\n"); }
#else
#   define EX86_LOG_DEBUG(...)
#endif

#endif
