#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include "isa.h"
#include "context.h"
#include "config.h"

/** The interpreter struct. */
typedef struct ex86_interpreter {
    ex86_context *ctx;
} ex86_interpreter;

/** Allocate a new interpreter. */
ex86_interpreter *ex86_interpreter_new(ex86_config *);

/** Destroy the interpreter. */
void ex86_interpreter_destroy(ex86_interpreter *interp);

/** Register an ISA with the interpreter. */
void ex86_isa_register(ex86_interpreter *, ex86_isa_id,
                       ex86_lookup_instruction_func *);

#endif
