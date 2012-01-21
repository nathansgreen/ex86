#ifndef ISA_8086_H_
#define ISA_8086_H_

#include "isa.h"

/** The opcodes for the generic instructions. */
typedef enum ex86_isa_8086_ops {
    /** nop */
    EX86_ISA_8086_OP_NOP,

    /** mov */
    EX86_ISA_8086_OP_MOV,

    /** Maximum value. */
    EX86_MAX_ISA_8086_OP
} ex86_isa_8086_ops;

ex86_instruction_candidates **ex86_isa_8086_lookup();

#endif
