#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include "isa.h"
#include "context.h"
#include "uthash.h"

struct ex86_config;
struct ex86_syntax;

typedef struct ex86_register_mapping {
    const char *name;
    ex86_register target;
    ex86_instruction_param_type type;
    UT_hash_handle hh;
} ex86_register_mapping;

/** The interpreter struct. */
typedef struct ex86_interpreter {
    struct ex86_context *ctx;
    ex86_instruction_candidates ***isas;
    struct ex86_syntax *syntaxes;
    ex86_register_mapping *register_map;
} ex86_interpreter;

/** Allocate a new interpreter. */
ex86_interpreter *ex86_interpreter_new(struct ex86_config *);

/** Destroy the interpreter. */
void ex86_interpreter_destroy(ex86_interpreter *interp);

/** Register a syntax with the interpreter. */
void ex86_interpreter_register_syntax(ex86_interpreter *, struct ex86_syntax *);

#endif
