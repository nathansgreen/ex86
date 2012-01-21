#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include "uthash.h"

#include "context.h"
#include "config.h"

struct ex86_isa;
struct ex86_syntax;

/** The interpreter struct. */
typedef struct ex86_interpreter {
    ex86_context *ctx;
    struct ex86_isa *isas;
    struct ex86_syntax *syntaxes;
} ex86_interpreter;

/** Allocate a new interpreter. */
ex86_interpreter *ex86_interpreter_new(ex86_config *);

/** Destroy the interpreter. */
void ex86_interpreter_destroy(ex86_interpreter *interp);

/** Register an ISA with the interpreter. */
void ex86_interpreter_register_isa(ex86_interpreter *, struct ex86_isa *);

/** Register a syntax with the interpreter. */
void ex86_interpreter_register_syntax(ex86_interpreter *, struct ex86_syntax *);

#endif
