#include <stdlib.h>

#include "interpreter.h"

#include "context.h"

ex86_interpreter *ex86_interpreter_new() {
    ex86_interpreter *interp = (ex86_interpreter *)malloc(sizeof(ex86_interpreter));
    interp->ctx = ex86_context_new();
    return interp;
}

void ex86_interpreter_destroy(ex86_interpreter *interp) {
    ex86_context_destroy(interp->ctx);
    free(interp);
}

void ex86_isa_register(ex86_interpreter *interp, int isa_id,
                       ex86_lookup_instruction_func *lookup) {
    return;
}
