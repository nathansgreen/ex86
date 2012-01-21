#include "interpreter.h"

#include "context.h"

#include <stddef.h>
#include <stdlib.h>

ex86_interpreter *ex86_interpreter_new(ex86_config *config) {
    ex86_interpreter *interp = (ex86_interpreter *)malloc(sizeof(ex86_interpreter));
    interp->ctx = ex86_context_new(config);
    interp->isas = NULL;
    interp->syntaxes = NULL;
    return interp;
}

void ex86_interpreter_destroy(ex86_interpreter *interp) {
    ex86_context_destroy(interp->ctx);
    free(interp->isas);
    free(interp);
}

void ex86_interpreter_register_isa(ex86_interpreter *interp, ex86_isa_id id,
                                   ex86_lookup_instruction_func *lookup) {
    ex86_interpreter_isa *isa = (ex86_interpreter_isa *)malloc(sizeof(ex86_interpreter_isa));
    isa->id = id;
    isa->lookup = lookup;
    HASH_ADD_INT(interp->isas, id, isa);
}

void ex86_interpreter_register_syntax(ex86_interpreter *interp,
                                      const char *name,
                                      ex86_syntax_vtable *vtable) {
    ex86_interpreter_syntax *syntax = (ex86_interpreter_syntax *)malloc(sizeof(ex86_interpreter_syntax));
    syntax->name = name;
    syntax->vtable = vtable;
    HASH_ADD_KEYPTR(hh, interp->syntaxes, syntax->name, strlen(syntax->name), syntax);
}
