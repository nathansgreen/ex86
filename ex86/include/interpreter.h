#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include "uthash.h"

#include "isa.h"
#include "syntax.h"
#include "context.h"
#include "config.h"

/** The ISA entry for registration. */
typedef struct ex86_interpreter_isa {
    ex86_isa_id id;
    ex86_lookup_instruction_func *lookup;
    UT_hash_handle hh;
} ex86_interpreter_isa;

/** The syntax entry for registration. */
typedef struct ex86_interpreter_syntax {
    const char *name;
    ex86_syntax_vtable *vtable;
    UT_hash_handle hh;
} ex86_interpreter_syntax;

/** The interpreter struct. */
typedef struct ex86_interpreter {
    ex86_context *ctx;
    ex86_interpreter_isa *isas;
    ex86_interpreter_syntax *syntaxes;
} ex86_interpreter;

/** Allocate a new interpreter. */
ex86_interpreter *ex86_interpreter_new(ex86_config *);

/** Destroy the interpreter. */
void ex86_interpreter_destroy(ex86_interpreter *interp);

/** Register an ISA with the interpreter. */
void ex86_interpreter_register_isa(ex86_interpreter *, ex86_isa_id,
                                   ex86_lookup_instruction_func *);

/** Register a syntax with the interpreter. */
void ex86_interpreter_register_syntax(ex86_interpreter *, const char *,
                                      ex86_syntax_vtable *);

#endif
