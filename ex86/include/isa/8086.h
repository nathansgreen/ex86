#ifndef ISA_8086_H_
#define ISA_8086_H_

#include "isa.h"

/** ID of the ISA. */
#define EX86_ISA_8086_ID 1

/** Name of the ISA. */
#define EX86_ISA_8086_NAME "8086"

/** The opcodes for the generic instructions. */
typedef enum ex86_isa_8086_ops {
    /** nop */
    EX86_ISA_8086_OP_NOP,

#if defined(REGISTER_SIZE) && REGISTER_SIZE >= 16
    /** mov16 */
    EX86_ISA_8086_OP_MOV16,
#endif

#if defined(REGISTER_SIZE) && REGISTER_SIZE >= 32
    /** mov32 */
    EX86_ISA_8086_OP_MOV32,
#endif

#if defined(REGISTER_SIZE) && REGISTER_SIZE >= 64
    /** mov64 */
    EX86_ISA_8086_OP_MOV64
#endif
} ex86_isa_8086_ops;

ex86_isa *ex86_isa_8086();

#endif
