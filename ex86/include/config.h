#ifndef CONFIG_H_
#define CONFIG_H_

#include <stddef.h>

/** The configuration object for ex86. */
typedef struct ex86_context_config {
    /** How much memory to allocate for the interpreter. */
    size_t memory_size;
} ex86_context_config;

#endif
