#include "isa/8086.h"

#include "isa.h"
#include "interpreter.h"
#include "error.h"
#include "assert.h"
#include "log.h"

/** nop */
EX86_INSTRUCTION(nop) {
}

#if defined(REGISTER_SIZE) && REGISTER_SIZE >= 16
/** mov16 register, register */
EX86_INSTRUCTION(mov16_r_r) {
    *dest.r16 = *src1.r16;
}

/** mov16 register, immediate */
EX86_INSTRUCTION(mov16_r_i) {
    *dest.r16 = src1.i16;
}

/** mov16 memory, immediate */
EX86_INSTRUCTION(mov16_m_i) {
    *dest.p16 = src1.i16;
}

/** mov16 register, memory */
EX86_INSTRUCTION(mov16_r_m) {
    *dest.r16 = *src1.p16;
}

/** mov16 memory, register */
EX86_INSTRUCTION(mov16_m_r) {
    *dest.p16 = *src1.r16;
}

/** mov16 memory, memory */
EX86_INSTRUCTION(mov16_m_m) {
    *dest.p16 = *src1.p16;
}
#endif

#if defined(REGISTER_SIZE) && REGISTER_SIZE >= 32
/** mov32 register, register */
EX86_INSTRUCTION(mov32_r_r) {
    *dest.r32 = *src1.r32;
}

/** mov32 register, immediate */
EX86_INSTRUCTION(mov32_r_i) {
    *dest.r32 = src1.i32;
}

/** mov32 memory, immediate */
EX86_INSTRUCTION(mov32_m_i) {
    *dest.p32 = src1.i32;
}

/** mov32 register, memory */
EX86_INSTRUCTION(mov32_r_m) {
    *dest.r32 = *src1.p32;
}

/** mov32 memory, register */
EX86_INSTRUCTION(mov32_m_r) {
    *dest.p32 = *src1.r32;
}

/** mov32 memory, memory */
EX86_INSTRUCTION(mov32_m_m) {
    *dest.p32 = *src1.p32;
}
#endif

#if defined(REGISTER_SIZE) && REGISTER_SIZE >= 64
/** mov64 register, register */
EX86_INSTRUCTION(mov64_r_r) {
    *dest.r64 = *src1.r64;
}

/** mov64 register, immediate */
EX86_INSTRUCTION(mov64_r_i) {
    *dest.r64 = src1.i64;
}

/** mov64 memory, immediate */
EX86_INSTRUCTION(mov64_m_i) {
    *dest.p64 = src1.i64;
}

/** mov64 register, memory */
EX86_INSTRUCTION(mov64_r_m) {
    *dest.r64 = *src1.p64;
}

/** mov64 memory, register */
EX86_INSTRUCTION(mov64_m_r) {
    *dest.p64 = *src1.r64;
}

/** mov64 memory, memory */
EX86_INSTRUCTION(mov64_m_m) {
    *dest.p64 = *src1.p64;
}
#endif

/** Generate lookup tables. */
EX86_LOOKUP_INSTRUCTION(lookup) {
    switch(op) {
        case EX86_ISA_8086_OP_NOP:
        switch(sig) {
            case EX86_INSTRUCTION_SIGNATURE(EX86_TARGET_NONE, EX86_TARGET_NONE, EX86_TARGET_NONE): return &nop;
            default: *errno = EX86_ERROR_INSTRUCTION_SIGNATURE_MISMATCH; return 0;
        }

#if defined(REGISTER_SIZE) && REGISTER_SIZE >= 16
        case EX86_ISA_8086_OP_MOV16:
            switch(sig) {
                case EX86_INSTRUCTION_SIGNATURE(EX86_TARGET_REGISTER_16, EX86_TARGET_REGISTER_16, EX86_TARGET_NONE): return &mov16_r_r;
                case EX86_INSTRUCTION_SIGNATURE(EX86_TARGET_REGISTER_16, EX86_TARGET_IMMEDIATE_16, EX86_TARGET_NONE): return &mov16_r_i;
                case EX86_INSTRUCTION_SIGNATURE(EX86_TARGET_MEMORY_16, EX86_TARGET_IMMEDIATE_16, EX86_TARGET_NONE): return &mov16_m_i;
                case EX86_INSTRUCTION_SIGNATURE(EX86_TARGET_REGISTER_16, EX86_TARGET_MEMORY_16, EX86_TARGET_NONE): return &mov16_r_m;
                case EX86_INSTRUCTION_SIGNATURE(EX86_TARGET_MEMORY_16, EX86_TARGET_REGISTER_16, EX86_TARGET_NONE): return &mov16_m_r;
                case EX86_INSTRUCTION_SIGNATURE(EX86_TARGET_MEMORY_16, EX86_TARGET_MEMORY_16, EX86_TARGET_NONE): return &mov16_m_m;
                default: *errno = EX86_ERROR_INSTRUCTION_SIGNATURE_MISMATCH; return 0;
            }
#endif

#if defined(REGISTER_SIZE) && REGISTER_SIZE >= 32
        case EX86_ISA_8086_OP_MOV32:
            switch(sig) {
                case EX86_INSTRUCTION_SIGNATURE(EX86_TARGET_REGISTER_32, EX86_TARGET_REGISTER_32, EX86_TARGET_NONE): return &mov32_r_r;
                case EX86_INSTRUCTION_SIGNATURE(EX86_TARGET_REGISTER_32, EX86_TARGET_IMMEDIATE_32, EX86_TARGET_NONE): return &mov32_r_i;
                case EX86_INSTRUCTION_SIGNATURE(EX86_TARGET_MEMORY_32, EX86_TARGET_IMMEDIATE_32, EX86_TARGET_NONE): return &mov32_m_i;
                case EX86_INSTRUCTION_SIGNATURE(EX86_TARGET_REGISTER_32, EX86_TARGET_MEMORY_32, EX86_TARGET_NONE): return &mov32_r_m;
                case EX86_INSTRUCTION_SIGNATURE(EX86_TARGET_MEMORY_32, EX86_TARGET_REGISTER_32, EX86_TARGET_NONE): return &mov32_m_r;
                case EX86_INSTRUCTION_SIGNATURE(EX86_TARGET_MEMORY_32, EX86_TARGET_MEMORY_32, EX86_TARGET_NONE): return &mov32_m_m;
                default: *errno = EX86_ERROR_INSTRUCTION_SIGNATURE_MISMATCH; return 0;
            }
#endif

#if defined(REGISTER_SIZE) && REGISTER_SIZE >= 64
        case EX86_ISA_8086_OP_MOV64:
            switch(sig) {
                case EX86_INSTRUCTION_SIGNATURE(EX86_TARGET_REGISTER_64, EX86_TARGET_REGISTER_64, EX86_TARGET_NONE): return &mov64_r_r;
                case EX86_INSTRUCTION_SIGNATURE(EX86_TARGET_REGISTER_64, EX86_TARGET_IMMEDIATE_64, EX86_TARGET_NONE): return &mov64_r_i;
                case EX86_INSTRUCTION_SIGNATURE(EX86_TARGET_MEMORY_64, EX86_TARGET_IMMEDIATE_64, EX86_TARGET_NONE): return &mov64_m_i;
                case EX86_INSTRUCTION_SIGNATURE(EX86_TARGET_REGISTER_64, EX86_TARGET_MEMORY_64, EX86_TARGET_NONE): return &mov64_r_m;
                case EX86_INSTRUCTION_SIGNATURE(EX86_TARGET_MEMORY_64, EX86_TARGET_REGISTER_64, EX86_TARGET_NONE): return &mov64_m_r;
                case EX86_INSTRUCTION_SIGNATURE(EX86_TARGET_MEMORY_64, EX86_TARGET_MEMORY_64, EX86_TARGET_NONE): return &mov64_m_m;
                default: *errno = EX86_ERROR_INSTRUCTION_SIGNATURE_MISMATCH; return 0;
            }
#endif
        default: *errno = EX86_ERROR_OP_NOT_FOUND; return 0;
    }
}

static void on_register(ex86_interpreter *interp) {
}

static void on_unregister(ex86_interpreter *interp) {
}

static ex86_isa isa = {
    .id             = EX86_ISA_8086_ID,
    .name           = EX86_ISA_8086_NAME,
    .on_register    = &on_register,
    .on_unregister  = &on_unregister,
    .lookup         = &lookup
};

ex86_isa *ex86_isa_8086() {
    return &isa;
}
