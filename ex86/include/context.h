#ifndef CONTEXT_H_
#define CONTEXT_H_

#include <stdint.h>

struct ex86_config;

#if defined(REGISTER_SIZE) && REGISTER_SIZE == 64
    /** A register value. */
    typedef int64_t ex86_register_value;

    /** Get the low 64-bits of the register (rax, rbx, etc.) */
#   define EX86_REGISTER_64_GET(SRC) *(SRC)

    /** Set the low 64-bits of the register (rax, rbx, etc.) */
#   define EX86_REGISTER_64_SET(DEST, SRC) *DEST = (SRC)

    /** Get the low 32-bits of the register (eax, ebx, etc.) */
#   define EX86_REGISTER_32_GET(SRC) (int32_t)(*(SRC))

    /** Set the low 32-bits of the register (eax, ebx, etc.) */
#   define EX86_REGISTER_32_SET(DEST, SRC) *DEST = *(DEST) >> 32 << 32 | (SRC)

    /** Get the low 16-bits of the register (ax, bx, etc.) */
#   define EX86_REGISTER_16_GET(SRC) (int16_t)(*(SRC))

    /** Set the low 16-bits of the register (ax, bx, etc.) */
#   define EX86_REGISTER_16_SET(DEST, SRC) *DEST = *(DEST) >> 16 << 16 | (SRC)

    /** A pointer to a value in memory. */
    typedef int64_t *ex86_pointer;

    /** Get 64 bits in memory. */
#   define EX86_MEMORY_64_GET(SRC) *(SRC)

    /** Set 64 bits in memory. */
#   define EX86_MEMORY_64_SET(DEST, SRC) *DEST = (SRC)

    /** Get 32 bits in memory. */
#   define EX86_MEMORY_32_GET(SRC) (int32_t)(*(SRC) >> 32)

    /** Set 32 bits in memory. */
#   define EX86_MEMORY_32_SET(DEST, SRC) *DEST = (*(DEST) & 0x00000000FFFFFFFF) | ((int32_t)(SRC) << 32)

    /** Get 16 bits in memory. */
#   define EX86_MEMORY_16_GET(SRC) (int16_t)(*(SRC) >> 48)

    /** Set 16 bits in memory. */
#   define EX86_MEMORY_16_SET(DEST, SRC) *DEST = (*(DEST) & 0x0000FFFFFFFFFFFF) | ((int16_t)(SRC) << 48)

    /** Get 8 bits in memory. */
#   define EX86_MEMORY_8_GET(SRC) (int8_t)(*(SRC) >> 56)

    /** Set 8 bits in memory. */
#   define EX86_MEMORY_8_SET(DEST, SRC) *DEST = (*(DEST) & 0x00FFFFFFFFFFFFFFF) | ((int8_t)(SRC) << 56)

    /** An immediate value. */
    typedef int64_t ex86_immediate;

    /** Convert an immediate value to 64 bits. */
#   define EX86_IMMEDIATE_64(VALUE) (VALUE)

    /** Convert an immediate value to 32 bits. */
#   define EX86_IMMEDIATE_32(VALUE) (int32_t)(VALUE)

    /** Convert an immediate value to 16 bits. */
#   define EX86_IMMEDIATE_16(VALUE) (int16_t)(VALUE)
#elif defined(REGISTER_SIZE) && REGISTER_SIZE == 32
    /** A register value. */
    typedef int32_t ex86_register_value;

    /** Get the low 32-bits of the register (eax, ebx, etc.) */
#   define EX86_REGISTER_32_GET(SRC) *(SRC)

    /** Set the low 32-bits of the register (eax, ebx, etc.) */
#   define EX86_REGISTER_32_SET(DEST, SRC) *DEST = (SRC)

    /** Get the low 16-bits of the register (ax, bx, etc.) */
#   define EX86_REGISTER_16_GET(SRC) (int16_t)(*(SRC))

    /** Set the low 16-bits of the register (ax, bx, etc.) */
#   define EX86_REGISTER_16_SET(DEST, SRC) *DEST = *(DEST) >> 16 << 16 | (SRC)

    /** A pointer to a value in memory. */
    typedef int32_t *ex86_pointer;

    /** Get 32 bits in memory. */
#   define EX86_MEMORY_32_GET(SRC) *(SRC)

    /** Set 32 bits in memory. */
#   define EX86_MEMORY_32_SET(DEST, SRC) *DEST = (SRC)

    /** Get 16 bits in memory. */
#   define EX86_MEMORY_16_GET(SRC) (*(SRC) >> 16)

    /** Set 16 bits in memory. */
#   define EX86_MEMORY_16_SET(DEST, SRC) *DEST = (*(DEST) & 0x0000FFFF) | ((int32_t)(SRC) << 16)

    /** Get 8 bits in memory. */
#   define EX86_MEMORY_8_GET(SRC) (*(SRC) >> 24)

    /** Set 8 bits in memory. */
#   define EX86_MEMORY_8_SET(DEST, SRC) *DEST = (*(DEST) & 0x00FFFFFF) | ((int8_t)(SRC) << 24)

    /** An immediate value. */
    typedef int32_t ex86_immediate;

    /** Convert an immediate value to 32 bits. */
#   define EX86_IMMEDIATE_32(VALUE) VALUE

    /** Convert an immediate value to 16 bits. */
#   define EX86_IMMEDIATE_16(VALUE) (int16_t)(VALUE)
#elif defined(REGISTER_SIZE) && REGISTER_SIZE == 16
    /** A register value. */
    typedef int16_t ex86_register_value;

    /** Get the low 16-bits of the register (ax, bx, etc.) */
#   define EX86_REGISTER_16_GET(SRC) *SRC

    /** Set the low 16-bits of the register (ax, bx, etc.) */
#   define EX86_REGISTER_16_SET(DEST, SRC) *DEST = (SRC)

    /** A pointer to a value in memory. */
    typedef int16_t *ex86_pointer;

    /** Get 16 bits in memory. */
#   define EX86_MEMORY_16_GET(SRC) *SRC

    /** Set 16 bits in memory. */
#   define EX86_MEMORY_16_SET(DEST, SRC) *DEST = (SRC)

    /** Get 8 bits in memory. */
#   define EX86_MEMORY_8_GET(SRC) (*SRC >> 8)

    /** Set 8 bits in memory. */
#   define EX86_MEMORY_8_SET(DEST, SRC) *DEST = (*(DEST) & 0x00FF) | ((int8_t)(SRC) << 8)

    /** An immediate value. */
    typedef int16_t ex86_immediate;

    /** Convert an immediate value to 16 bits. */
#   define EX86_IMMEDIATE_16(VALUE) VALUE
#else
#   error "REGISTER_SIZE not specified or invalid"
#endif

#define EX86_REGISTER_8_HI_GET(SRC) (int8_t)(*(SRC) >> 8)
#define EX86_REGISTER_8_LO_GET(src) (int8_t)(*(SRC))

/** Convert an immediate value to 16 bits. */
#define EX86_IMMEDIATE_8(VALUE) (int8_t)(VALUE)

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

/** The ex86 execution context. */
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

/** Allocate a new ex86 context. */
ex86_context *ex86_context_new(struct ex86_config *);

/** Destroy the ex86 context. */
void ex86_context_destroy(ex86_context *interp);

#endif
