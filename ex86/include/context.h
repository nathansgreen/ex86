#ifndef CONTEXT_H_
#define CONTEXT_H_

#include <stdint.h>
#include <stddef.h>

struct ex86_config;

typedef ptrdiff_t ex86_pointer;

#if defined(REGISTER_SIZE) && REGISTER_SIZE == 64
    /** A register value. */
    typedef int64_t ex86_register_value;

    /** Get the low 64-bits of the register (rax, rbx, etc.) */
#   define EX86_REGISTER_64_GET(CTX, SRC) CTX->registers[(SRC)]

    /** Set the low 64-bits of the register (rax, rbx, etc.) */
#   define EX86_REGISTER_64_SET(CTX, DEST, SRC) CTX->registers[DEST] = (SRC)

    /** Get the low 32-bits of the register (eax, ebx, etc.) */
#   define EX86_REGISTER_32_GET(CTX, SRC) (int32_t)(CTX->registers[SRC])

    /** Set the low 32-bits of the register (eax, ebx, etc.) */
#   define EX86_REGISTER_32_SET(CTX, DEST, SRC) CTX->registers[DEST] = (CTX->registers[DEST] & 0xFFFFFFFF00000000) | (SRC)

    /** Get the low 16-bits of the register (ax, bx, etc.) */
#   define EX86_REGISTER_16_GET(CTX, SRC) (int16_t)(CTX->registers[SRC])

    /** Set the low 16-bits of the register (ax, bx, etc.) */
#   define EX86_REGISTER_16_SET(CTX, DEST, SRC) CTX->registers[DEST] = (CTX->registers[DEST] & 0xFFFFFFFFFFFF0000) | (SRC)

    /** Get the low 8-bits of the register (al, bl, etc.) */
#   define EX86_REGISTER_8_LO_GET(CTX, SRC) (int8_t)(CTX->registers[SRC])

    /** Set the low 8-bits of the register (al, bl, etc.) */
#   define EX86_REGISTER_8_LO_SET(CTX, DEST, SRC) CTX->registers[DEST] = (CTX->registers[DEST] & 0xFFFFFFFFFFFFFF00) | (SRC)

    /** Get the high 8-bits of the 16-bit register (ah, bh, etc.) */
#   define EX86_REGISTER_8_HI_GET(CTX, SRC) (int8_t)(CTX->registers[SRC] >> 8)

    /** Set the high 8-bits of the 16-bit register (ah, bh, etc.) */
#   define EX86_REGISTER_8_HI_SET(CTX, DEST, SRC) CTX->registers[DEST] = (CTX->registers[DEST] & 0xFFFFFFFFFFFF00FF) | ((SRC) << 8)

    /** Get the raw memory pointer. */
#   define EX86_MEMORY_POINTER(CTX, POINTER) (int64_t *)((int64_t *)CTX->memory + POINTER)

    /** Get 64 bits in memory. */
#   define EX86_MEMORY_64_GET(CTX, SRC) *EX86_MEMORY_POINTER(CTX, SRC)

    /** Set 64 bits in memory. */
#   define EX86_MEMORY_64_SET(CTX, DEST, SRC) *EX86_MEMORY_POINTER(CTX, DEST) = (SRC)

    /** Get 32 bits in memory. */
#   define EX86_MEMORY_32_GET(CTX, SRC) (int32_t)(*EX86_MEMORY_POINTER(CTX, SRC) >> 32)

    /** Set 32 bits in memory. */
#   define EX86_MEMORY_32_SET(CTX, DEST, SRC) *EX86_MEMORY_POINTER(CTX, DEST) = (*EX86_MEMORY_POINTER(CTX, DEST) & 0x00000000FFFFFFFF) | ((int32_t)(SRC) << 32)

    /** Get 16 bits in memory. */
#   define EX86_MEMORY_16_GET(CTX, SRC) (int16_t)(*EX86_MEMORY_POINTER(CTX, SRC) >> 48)

    /** Set 16 bits in memory. */
#   define EX86_MEMORY_16_SET(CTX, DEST, SRC) *(int64_t)(CTX->memory + DEST) = (*EX86_MEMORY_POINTER(CTX, DEST) & 0x0000FFFFFFFFFFFF) | ((int16_t)(SRC) << 48)

    /** Get 8 bits in memory. */
#   define EX86_MEMORY_8_GET(CTX, SRC) (int8_t)(*EX86_MEMORY_POINTER(CTX, SRC) >> 56)

    /** Set 8 bits in memory. */
#   define EX86_MEMORY_8_SET(CTX, DEST, SRC) *EX86_MEMORY_POINTER(CTX, DEST) = (*EX86_MEMORY_POINTER(CTX, DEST) & 0x00FFFFFFFFFFFFFF) | ((int8_t)(SRC) << 56)

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
#   define EX86_REGISTER_32_GET(CTX, SRC) CTX->registers[SRC]

    /** Set the low 32-bits of the register (eax, ebx, etc.) */
#   define EX86_REGISTER_32_SET(CTX, DEST, SRC) CTX->registers[DEST] = (SRC)

    /** Get the low 16-bits of the register (ax, bx, etc.) */
#   define EX86_REGISTER_16_GET(CTX, SRC) (int16_t)(CTX->registers[SRC])

    /** Set the low 16-bits of the register (ax, bx, etc.) */
#   define EX86_REGISTER_16_SET(CTX, DEST, SRC) CTX->registers[DEST] = (CTX->registers[DEST] & 0xFFFF0000) | (SRC)

    /** Get the low 8-bits of the register (al, bl, etc.) */
#   define EX86_REGISTER_8_LO_GET(CTX, SRC) (int8_t)(CTX->registers[SRC])

    /** Set the low 8-bits of the register (al, bl, etc.) */
#   define EX86_REGISTER_8_LO_SET(CTX, DEST, SRC) CTX->registers[DEST] = (CTX->registers[DEST] & 0xFFFFFF00) | (SRC)

    /** Get the high 8-bits of the 16-bit register (ah, bh, etc.) */
#   define EX86_REGISTER_8_HI_GET(CTX, SRC) (int8_t)(CTX->registers[SRC] >> 8)

    /** Set the high 8-bits of the 16-bit register (ah, bh, etc.) */
#   define EX86_REGISTER_8_HI_SET(CTX, DEST, SRC) CTX->registers[DEST] = (CTX->registers[DEST] & 0xFFFF00FF) | ((SRC) << 8)

    /** Get the raw memory pointer. */
#   define EX86_MEMORY_POINTER(CTX, POINTER) (int32_t *)((int32_t *)CTX->memory + POINTER)

    /** Get 32 bits in memory. */
#   define EX86_MEMORY_32_GET(CTX, SRC) *EX86_MEMORY_POINTER(CTX, SRC)

    /** Set 32 bits in memory. */
#   define EX86_MEMORY_32_SET(CTX, DEST, SRC) *EX86_MEMORY_POINTER(CTX, SRC) = (SRC)

    /** Get 16 bits in memory. */
#   define EX86_MEMORY_16_GET(CTX, SRC) (int16_t)(*EX86_MEMORY_POINTER(CTX, SRC) >> 16)

    /** Set 16 bits in memory. */
#   define EX86_MEMORY_16_SET(CTX, DEST, SRC) *EX86_MEMORY_POINTER(CTX, DEST) = (*EX86_MEMORY_POINTER(CTX, DEST) & 0x0000FFFF) | ((int32_t)(SRC) << 16)

    /** Get 8 bits in memory. */
#   define EX86_MEMORY_8_GET(CTX, SRC) (int8_t)(*EX86_MEMORY_POINTER(CTX, SRC) >> 24)

    /** Set 8 bits in memory. */
#   define EX86_MEMORY_8_SET(CTX, DEST, SRC) *EX86_MEMORY_POINTER(CTX, SRC) = (*EX86_MEMORY_POINTER(CTX, DEST) & 0x00FFFFFF) | ((int8_t)(SRC) << 24)

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
#   define EX86_REGISTER_16_GET(CTX, SRC) CTX->registers[SRC]

    /** Set the low 16-bits of the register (ax, bx, etc.) */
#   define EX86_REGISTER_16_SET(CTX, DEST, SRC) CTX->registers[DEST] = (SRC)

    /** Get the low 8-bits of the register (al, bl, etc.) */
#   define EX86_REGISTER_8_LO_GET(CTX, SRC) (int8_t)(CTX->registers[SRC])

    /** Set the low 8-bits of the register (al, bl, etc.) */
#   define EX86_REGISTER_8_LO_SET(CTX, DEST, SRC) CTX->registers[DEST] = (CTX->registers[DEST] & 0xFF00) | (SRC)

    /** Get the high 8-bits of the 16-bit register (ah, bh, etc.) */
#   define EX86_REGISTER_8_HI_GET(CTX, SRC) (int8_t)(CTX->registers[SRC] >> 8)

    /** Set the high 8-bits of the 16-bit register (ah, bh, etc.) */
#   define EX86_REGISTER_8_HI_SET(CTX, DEST, SRC) CTX->registers[DEST] = (CTX->registers[DEST] & 0x00FF) | ((SRC) << 8)

    /** Get the raw memory pointer. */
#   define EX86_MEMORY_POINTER(CTX, POINTER) (int16_t *)((int16_t *)CTX->memory + POINTER)

    /** Get 16 bits in memory. */
#   define EX86_MEMORY_16_GET(CTX, SRC) *EX86_MEMORY_POINTER(CTX, SRC)

    /** Set 16 bits in memory. */
#   define EX86_MEMORY_16_SET(CTX, DEST, SRC) *EX86_MEMORY_POINTER(CTX, DEST) = (SRC)

    /** Get 8 bits in memory. */
#   define EX86_MEMORY_8_GET(CTX, SRC) (int8_t)(*EX86_MEMORY_POINTER(CTX, SRC) >> 8)

    /** Set 8 bits in memory. */
#   define EX86_MEMORY_8_SET(CTX, DEST, SRC) *EX86_MEMORY_POINTER(CTX, DEST) = (*EX86_MEMORY_POINTER(CTX, DEST) & 0x00FF) | ((int8_t)(SRC) << 8)

    /** An immediate value. */
    typedef int16_t ex86_immediate;

    /** Convert an immediate value to 16 bits. */
#   define EX86_IMMEDIATE_16(VALUE) VALUE
#else
#   error "REGISTER_SIZE not specified or invalid"
#endif

/** Convert an immediate value to 16 bits. */
#define EX86_IMMEDIATE_8(VALUE) (int8_t)(VALUE)

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

/** Enum for context stuff. */
typedef enum ex86_register {
    /** The accumulator register. */
    EX86_REGISTER_AX,

    /** The base register. */
    EX86_REGISTER_BX,

    /** The counter register. */
    EX86_REGISTER_CX,

    /** The data register. */
    EX86_REGISTER_DX,

    /** The source index register. */
    EX86_REGISTER_SI,

    /** The destination register. */
    EX86_REGISTER_DI,

    /** The base pointer register. */
    EX86_REGISTER_BP,

    /** The stack pointer register. */
    EX86_REGISTER_SP,

    /** The instruction pointer register. */
    EX86_REGISTER_IP,

    /** Maximum register value. */
    EX86_MAX_REGISTER
} ex86_register;

/** The ex86 execution context. */
typedef struct ex86_context {
    /** Registers. */
    ex86_register_value registers[EX86_MAX_REGISTER];

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
