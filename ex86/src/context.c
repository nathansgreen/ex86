#include <stdlib.h>
#include <string.h>

#include "context.h"

ex86_context *ex86_context_new(ex86_config *config) {
    /* Conveniently, we don't have to care about initializing the registers to
       zero. */
    ex86_context *ctx = (ex86_context *)malloc(sizeof(ex86_context));
    ctx->memory = malloc(config->memory_size);
    return ctx;
}

void ex86_context_destroy(ex86_context *interp) {
    free(interp);
}
