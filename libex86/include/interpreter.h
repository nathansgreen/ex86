#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include "isa.h"

typedef struct ex86_interpreter {
    int derp;
} ex86_interpreter;

/**
 * Register an ISA with the interpreter.
 */
void ex86_isa_register(ex86_interpreter *, int, ex86_lookup_instruction_func *);

#endif
