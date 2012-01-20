#ifndef CONTEXT_H_
#define CONTEXT_H_

#include <stdint.h>

#if defined(REGISTER_SIZE) && REGISTER_SIZE >= 16
    /** A 16-bit register value. */
    typedef int16_t ex86_register_value_16;

    /** A 16-bit register. */
    typedef ex86_register_value_16 *ex86_register_16;
#endif

#if defined(REGISTER_SIZE) && REGISTER_SIZE >= 32
    /** A 32-bit register value. */
    typedef int32_t ex86_register_value_32;

    /** A 32-bit register. */
    typedef ex86_register_value_32 *ex86_register_32;
#endif

#if defined(REGISTER_SIZE) && REGISTER_SIZE >= 64
    /** A 64-bit register value. */
    typedef int64_t ex86_register_value_64;

    /** A 64-bit register. */
    typedef ex86_register_value_64 *ex86_register_64;
#endif

#if defined(REGISTER_SIZE) && REGISTER_SIZE == 64
    /** Set the actual register size. */
    typedef ex86_register_value_64 ex86_register_value;

    /** Get the first 64-bits of the register (rax, rbx, etc.) */
#   define EX86_REGISTER_VALUE_64(VALUE) VALUE

    /** Get the first 32-bits of the register (eax, ebx, etc.) */
#   define EX86_REGISTER_VALUE_32(VALUE) (ex86_register_value_32)(VALUE & 0xFFFFFFFF)

    /** Get the first 16-bits of the register (ax, bx, etc.) */
#   define EX86_REGISTER_VALUE_16(VALUE) (ex86_register_value_16)(VALUE & 0xFFFF)
#elif defined(REGISTER_SIZE) && REGISTER_SIZE == 32
    /** Set the actual register size. */
    typedef ex86_register_value_32 ex86_register_value;

    /** Get the first 32-bits of the register (eax, ebx, etc.) */
#   define EX86_REGISTER_VALUE_32(VALUE) VALUE

    /** Get the first 16-bits of the register (ax, bx, etc.) */
#   define EX86_REGISTER_VALUE_16(VALUE) (ex86_register_value_16)(VALUE & 0xFFFF)
#elif defined(REGISTER_SIZE) && REGISTER_SIZE == 16
    /** Set the actual register size. */
    typedef ex86_register_value_16 ex86_register_value;

    /** Get the first 16-bits of the register (ax, bx, etc.) */
#   define EX86_REGISTER_VALUE_16(VALUE) VALUE
#else
#   error "REGISTER_SIZE not specified or invalid"
#endif

typedef ex86_register_value *ex86_register;

/** FLAGS register. */
typedef int ex86_flags;

/** Carry flag. */
#define EX86_FLAGS_CF(FLAGS)        (FLAGS & 0x0001) // 0

/** Reserved. */
#define EX86_FLAGS_1F(FLAGS) 1 //   (FLAGS & 0x0002) // 1

/** Parity flag. */
#define EX86_FLAGS_PF(FLAGS)        (FLAGS & 0x0004) // 2

/** Reserved. */
#define EX86_FLAGS_3F(FLAGS) 0 //   (FLAGS & 0x0008) // 3

/** Adjust flag. */
#define EX86_FLAGS_AF(FLAGS)        (FLAGS & 0x0010) // 4

/** Reserved. */
#define EX86_FLAGS_5F(FLAGS) 0 //   (FLAGS & 0x0020) // 5

/** Zero flag. */
#define EX86_FLAGS_ZF(FLAGS)        (FLAGS & 0x0040) // 6

/** Sign flag. */
#define EX86_FLAGS_SF(FLAGS)        (FLAGS & 0x0080) // 7

/** Trap flag. */
#define EX86_FLAGS_TF(FLAGS)        (FLAGS & 0x0100) // 8

/** Interrupt enable flag. */
#define EX86_FLAGS_IF(FLAGS)        (FLAGS & 0x0200) // 9

/** Direction flag. */
#define EX86_FLAGS_DF(FLAGS)        (FLAGS & 0x0400) // 10

/** Overflow flag. */
#define EX86_FLAGS_OF(FLAGS)        (FLAGS & 0x0800) // 11

/** I/O privilege level (lo bit). */
#define EX86_FLAGS_IOPL_LO(FLAGS)   (FLAGS & 0x1000) // 12

/** I/O privilege level (hi bit). */
#define EX86_FLAGS_IOPL_HI(FLAGS)   (FLAGS & 0x2000) // 13

/** Nested task flag. */
#define EX86_FLAGS_NT(FLAGS)        (FLAGS & 0x4000) // 14

/** A pointer to an 8-bit value in memory. */
typedef int8_t *ex86_pointer_8;

/** A pointer to a 16-bit value in memory. */
typedef int16_t *ex86_pointer_16;

/** A pointer to a 32-bit value in memory. */
typedef int32_t *ex86_pointer_32;

/** A pointer to a 64-bit value in memory. */
typedef int64_t *ex86_pointer_64;

/**
 * The ex86 execution context.
 */
typedef struct ex86_context {
    /** The accumulator register. */
    ex86_register_value ax;

    /** The base register. */
    ex86_register_value bx;

    /** The counter register. */
    ex86_register_value cx;

    /** The data register. */
    ex86_register_value dx;

    /** The source index register. */
    ex86_register_value si;

    /** The destination register. */
    ex86_register_value di;

    /** The base pointer register. */
    ex86_register_value bp;

    /** The stack pointer register. */
    ex86_register_value sp;

    /** The instruction pointer register. */
    ex86_register_value ip;

    /** The FLAGS register. */
    ex86_flags flags;

    /** A chunk of memory. */
    void *memory;
} ex86_context;

/**
 * Allocate a new ex86 context context.
 */
ex86_context *ex86_context_new();

/**
 * Destroy the ex86 context context.
 */
void ex86_context_destroy(ex86_context *interp);

#endif
