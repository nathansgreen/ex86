#ifndef ISA_H_
#define ISA_H_

#include <stdint.h>

#include "error.h"
#include "context.h"

struct ex86_interpreter;

/** The ISA ID type. */
typedef int ex86_isa_id;

/** This enumeration specifies the type a target is and also the type an
    instruction parameter is allowed to be. */
typedef enum ex86_instruction_param_type {
    /** Nothing (i.e. should be blank). */
    EX86_TARGET_NONE = 0,

    /** Pointer to 8 bits in memory. */
    EX86_TARGET_MEMORY_8 = 1,

    /** Immediate 8-bit value. */
    EX86_TARGET_IMMEDIATE_8 = 2,

    /** Low 8-bit register. */
    EX86_TARGET_REGISTER_8_LO = 3,

    /** High 8-bit register. */
    EX86_TARGET_REGISTER_8_HI = 4,

#if defined(REGISTER_SIZE) && REGISTER_SIZE >= 16
    /** 16-bit register. */
    EX86_TARGET_REGISTER_16 = 5,

    /** Pointer to 16 bits in memory. */
    EX86_TARGET_MEMORY_16 = 6,

    /** Immediate 16-bit value. */
    EX86_TARGET_IMMEDIATE_16 = 7,
#endif

#if defined(REGISTER_SIZE) && REGISTER_SIZE >= 32
    /** 32-bit register. */
    EX86_TARGET_REGISTER_32 = 8,

    /** Pointer to 32 bits in memory. */
    EX86_TARGET_MEMORY_32 = 9,

    /** Immediate 32-bit value. */
    EX86_TARGET_IMMEDIATE_32 = 10,
#endif

#if defined(REGISTER_SIZE) && REGISTER_SIZE >= 64
    /** 64-bit register. */
    EX86_TARGET_REGISTER_64 = 11,

    /** Pointer to 64 bits in memory. */
    EX86_TARGET_MEMORY_64 = 12,

    /** Immediate 64-bit value. */
    EX86_TARGET_IMMEDIATE_64 = 13,
#endif

    /** Label. */
    EX86_TARGET_LABEL = 14,

    /** Maximum limit. */
    EX86_MAX_TARGET
} ex86_instruction_param_type;

/** Get an appropriate type for an immediate value. */
#if defined(REGISTER_SIZE) && REGISTER_SIZE >= 64
#   define EX86_IMMEDIATE_TYPE(VALUE) ((VALUE >> 64) != 0 ? EX86_TARGET_IMMEDIATE_64 : \
                                       (VALUE >> 32) != 0 ? EX86_TARGET_IMMEDIATE_32 : \
                                       (VALUE >> 16) != 0 ? EX86_TARGET_IMMEDIATE_16 : \
                                       EX86_TARGET_IMMEDIATE_8)
#elif defined(REGISTER_SIZE) && REGISTER_SIZE >= 32
#   define EX86_IMMEDIATE_TYPE(VALUE) ((VALUE >> 32) != 0 ? EX86_TARGET_IMMEDIATE_32 : \
                                       (VALUE >> 16) != 0 ? EX86_TARGET_IMMEDIATE_16 : \
                                       EX86_TARGET_IMMEDIATE_8)
#elif defined(REGISTER_SIZE) && REGISTER_SIZE >= 16
#   define EX86_IMMEDIATE_TYPE(VALUE) ((VALUE >> 16) != 0 ? EX86_TARGET_IMMEDIATE_16 : \
                                       EX86_TARGET_IMMEDIATE_8)
#endif

/** The label type. */
typedef int ex86_label;

/** The type signature type. */
typedef int64_t ex86_type_signature;

/** A parameter to a basic instruction. */
typedef union ex86_instruction_param {
    /** Register value. */
    ex86_register r;

    /** Pointer value. */
    ex86_pointer p;

    /** An immediate value. */
    ex86_immediate i;

    /** A label. */
    ex86_label lbl;
} ex86_instruction_param;

#define EX86_INSTRUCTION_PARAMS \
    ex86_context *ctx, \
    ex86_instruction_param dest, \
    ex86_instruction_param src1, \
    ex86_instruction_param src2

/** The opcode type. */
typedef int ex86_opcode;

/** The function type for an instruction. */
typedef void ex86_instruction_func(EX86_INSTRUCTION_PARAMS);

/** The candidate table type. */
typedef ex86_instruction_func *ex86_instruction_candidates[EX86_MAX_TARGET][EX86_MAX_TARGET][EX86_MAX_TARGET];

/** A macro for specifying new instructions. */
#define EX86_INSTRUCTION(FUNC) \
static void FUNC(EX86_INSTRUCTION_PARAMS)

/** The function for looking up instruction candidates. */
typedef ex86_instruction_candidates **ex86_isa_lookup_func();

#endif
