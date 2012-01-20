#ifndef ISA_H_
#define ISA_H_

#include <stdint.h>

#include "context.h"
#include "register.h"
#include "memory.h"

/**
 * This enumeration specifies the type a target is and also the type an
 * instruction parameter is allowed to be.
 */
typedef enum ex86_instruction_param_type {
    /** Nothing. */
    EX86_TARGET_NONE        = 0x0,

    /** Register. */
    EX86_TARGET_REGISTER    = 0x1,

    /** Memory address. */
    EX86_TARGET_MEMORY      = 0x2,

    /** Immediate value. */
    EX86_TARGET_IMMEDIATE   = 0x4,

    /** Label. */
    EX86_TARGET_LABEL       = 0x8
} ex86_instruction_param_type;

/** The label type. */
typedef int ex86_label;

/**
 * A parameter to a basic instruction.
 */
typedef union ex86_basic_instr_param {
    /** 16-bit register. */
    ex86_register_16 *r16;
#if REGISTER_SIZE >= 32
    /** 32-bit register. */
    ex86_register_32 *r32;
#endif
#if REGISTER_SIZE >= 64
    /** 64-bit register. */
    ex86_register_64 *r64;
#endif

    /** Pointer to an 8-bit integer. */
    ex86_pointer_8 p8;
    /** Pointer to an 16-bit integer. */
    ex86_pointer_16 p16;
    /** Pointer to an 32-bit integer. */
    ex86_pointer_32 p32;
    /** Pointer to an 16-bit integer. */
    ex86_pointer_64 p64;

    /** An immediate 8-bit value. */
    int8_t i8;
    /** An immediate 16-bit value. */
    int16_t i16;
    /** An immediate 32-bit value. */
    int32_t i32;
    /** An immediate 64-bit value. */
    int64_t i64;

    /** A label. */
    ex86_label lbl;
} ex86_instruction_param;

#define EX86_INSTRUCTION_PARAMS \
    ex86_context *ctx, \
    ex86_instruction_param dest, \
    ex86_instruction_param src1, \
    ex86_instruction_param src2 \

/**
 * The function type for an instruction.
 */
typedef void ex86_instruction_func(EX86_INSTRUCTION_PARAMS);

/**
 * A specification for a function.
 */
typedef struct ex86_instruction_spec {
    ex86_instruction_func *func;
    ex86_instruction_param_type dest_type;
    ex86_instruction_param_type src1_type;
    ex86_instruction_param_type src2_type;
} ex86_instruction_spec;

#define EX86_SPECIFY_INSTRUCTION(FUNC, DEST_TYPE, SRC1_TYPE, SRC2_TYPE) \
static void FUNC(EX86_INSTRUCTION_PARAMS);\
static ex86_instruction_spec FUNC##_spec = { \
    .func       = &FUNC, \
    .dest_type  = DEST_TYPE, \
    .src1_type  = SRC1_TYPE, \
    .src2_type  = SRC1_TYPE \
}; \
void FUNC(EX86_INSTRUCTION_PARAMS)

#endif
