#ifndef ISA_8086_H_
#define ISA_8086_H_

#include "interpreter.h"

/** The ID for the 8086 ISA. */
#define EX86_ISA_8086_ID 1

/** The opcodes for the generic instructions. */
typedef enum ex86_isa_8086_ops {
#if defined(REGISTER_SIZE) && REGISTER_SIZE >= 16
    /** mov16 **/
    EX86_ISA_8086_OP_MOV16,
#endif

#if defined(REGISTER_SIZE) && REGISTER_SIZE >= 32
    /** mov32 **/
    EX86_ISA_8086_OP_MOV32,
#endif

#if defined(REGISTER_SIZE) && REGISTER_SIZE >= 64
    /** mov64 **/
    EX86_ISA_8086_OP_MOV64
#endif
} ex86_isa_8086_ops;

/** Register the 8086 ISA with the interpreter. */
void ex86_isa_register_8086(ex86_interpreter *);

#endif
