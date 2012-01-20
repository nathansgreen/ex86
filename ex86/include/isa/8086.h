#ifndef ISA_8086_H_
#define ISA_8086_H_

#include "interpreter.h"

#define EX86_ISA_8086_ID 1

/** The opcodes for the generic instructions. */
typedef enum ex86_isa_8086_ops {
    EX86_ISA_8086_OP_MOV16,
    EX86_ISA_8086_OP_MOV32,
    EX86_ISA_8086_OP_MOV64
} ex86_isa_8086_ops;

/**
 * Register the 8086 ISA with the interpreter.
 */
void ex86_isa_register_8086(ex86_interpreter *);

#endif
