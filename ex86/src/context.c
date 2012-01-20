#include <stdlib.h>
#include <string.h>

#include "context.h"

ex86_context *ex86_context_new() {
    /* Conveniently, we don't have to care about initializing the registers to
       zero. */
    return (ex86_context *)malloc(sizeof(ex86_context));
}

void ex86_context_destroy(ex86_context *interp) {
    free(interp);
}
