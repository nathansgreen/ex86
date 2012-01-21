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
    EX86_REGISTER_16_SET(dest.r, EX86_REGISTER_16_GET(src1.r));
}

/** mov16 register, immediate */
EX86_INSTRUCTION(mov16_r_i) {
    EX86_REGISTER_16_SET(dest.r, src1.i16);
}

/** mov16 memory, immediate */
EX86_INSTRUCTION(mov16_m_i) {
    EX86_MEMORY_16_SET(dest.p, src1.i16);
}

/** mov16 register, memory */
EX86_INSTRUCTION(mov16_r_m) {
    EX86_REGISTER_16_SET(dest.r, EX86_MEMORY_16_GET(dest.p));
}

/** mov16 memory, register */
EX86_INSTRUCTION(mov16_m_r) {
    EX86_MEMORY_16_SET(dest.p, EX86_REGISTER_16_GET(dest.r));
}

/** mov16 memory, memory */
EX86_INSTRUCTION(mov16_m_m) {
    EX86_MEMORY_16_SET(dest.p, EX86_MEMORY_16_GET(dest.p));
}
#endif

#if defined(REGISTER_SIZE) && REGISTER_SIZE >= 32
/** mov32 register, register */
EX86_INSTRUCTION(mov32_r_r) {
    EX86_REGISTER_32_SET(dest.r, EX86_REGISTER_32_GET(src1.r));
}

/** mov32 register, immediate */
EX86_INSTRUCTION(mov32_r_i) {
    EX86_REGISTER_32_SET(dest.r, src1.i32);
}

/** mov32 memory, immediate */
EX86_INSTRUCTION(mov32_m_i) {
    EX86_MEMORY_32_SET(dest.p, src1.i32);
}

/** mov32 register, memory */
EX86_INSTRUCTION(mov32_r_m) {
    EX86_REGISTER_32_SET(dest.r, EX86_MEMORY_32_GET(dest.p));
}

/** mov32 memory, register */
EX86_INSTRUCTION(mov32_m_r) {
    EX86_MEMORY_32_SET(dest.p, EX86_REGISTER_32_GET(dest.r));
}

/** mov32 memory, memory */
EX86_INSTRUCTION(mov32_m_m) {
    EX86_MEMORY_32_SET(dest.p, EX86_MEMORY_32_GET(dest.p));
}
#endif

#if defined(REGISTER_SIZE) && REGISTER_SIZE >= 64
/** mov64 register, register */
EX86_INSTRUCTION(mov64_r_r) {
    EX86_REGISTER_64_SET(dest.r, EX86_REGISTER_64_GET(src1.r));
}

/** mov64 register, immediate */
EX86_INSTRUCTION(mov64_r_i) {
    EX86_REGISTER_64_SET(dest.r, src1.i64);
}

/** mov64 memory, immediate */
EX86_INSTRUCTION(mov64_m_i) {
    EX86_MEMORY_64_SET(dest.p, src1.i64);
}

/** mov64 register, memory */
EX86_INSTRUCTION(mov64_r_m) {
    EX86_REGISTER_64_SET(dest.r, EX86_MEMORY_64_GET(dest.p));
}

/** mov64 memory, register */
EX86_INSTRUCTION(mov64_m_r) {
    EX86_MEMORY_64_SET(dest.p, EX86_REGISTER_64_GET(dest.r));
}

/** mov64 memory, memory */
EX86_INSTRUCTION(mov64_m_m) {
    EX86_MEMORY_64_SET(dest.p, EX86_MEMORY_64_GET(dest.p));
}
#endif

static ex86_instruction_candidates lookup[EX86_MAX_ISA_8086_OP] = {
    [EX86_ISA_8086_OP_NOP    ][EX86_TARGET_NONE        ][EX86_TARGET_NONE        ][EX86_TARGET_NONE        ] = &nop,

#if defined(REGISTER_SIZE) && REGISTER_SIZE >= 16
    [EX86_ISA_8086_OP_MOV16  ][EX86_TARGET_REGISTER_16 ][EX86_TARGET_REGISTER_16 ][EX86_TARGET_NONE        ] = &mov16_r_r,
    [EX86_ISA_8086_OP_MOV16  ][EX86_TARGET_REGISTER_16 ][EX86_TARGET_IMMEDIATE_16][EX86_TARGET_NONE        ] = &mov16_r_i,
    [EX86_ISA_8086_OP_MOV16  ][EX86_TARGET_MEMORY_16   ][EX86_TARGET_IMMEDIATE_16][EX86_TARGET_NONE        ] = &mov16_m_i,
    [EX86_ISA_8086_OP_MOV16  ][EX86_TARGET_REGISTER_16 ][EX86_TARGET_MEMORY_16   ][EX86_TARGET_NONE        ] = &mov16_r_m,
    [EX86_ISA_8086_OP_MOV16  ][EX86_TARGET_MEMORY_16   ][EX86_TARGET_REGISTER_16 ][EX86_TARGET_NONE        ] = &mov16_m_r,
    [EX86_ISA_8086_OP_MOV16  ][EX86_TARGET_MEMORY_16   ][EX86_TARGET_MEMORY_16   ][EX86_TARGET_NONE        ] = &mov16_m_m,
#endif

#if defined(REGISTER_SIZE) && REGISTER_SIZE >= 32
    [EX86_ISA_8086_OP_MOV32  ][EX86_TARGET_REGISTER_32 ][EX86_TARGET_REGISTER_32 ][EX86_TARGET_NONE        ] = &mov32_r_r,
    [EX86_ISA_8086_OP_MOV32  ][EX86_TARGET_REGISTER_32 ][EX86_TARGET_IMMEDIATE_32][EX86_TARGET_NONE        ] = &mov32_r_i,
    [EX86_ISA_8086_OP_MOV32  ][EX86_TARGET_MEMORY_32   ][EX86_TARGET_IMMEDIATE_32][EX86_TARGET_NONE        ] = &mov32_m_i,
    [EX86_ISA_8086_OP_MOV32  ][EX86_TARGET_REGISTER_32 ][EX86_TARGET_MEMORY_32   ][EX86_TARGET_NONE        ] = &mov32_r_m,
    [EX86_ISA_8086_OP_MOV32  ][EX86_TARGET_MEMORY_32   ][EX86_TARGET_REGISTER_32 ][EX86_TARGET_NONE        ] = &mov32_m_r,
    [EX86_ISA_8086_OP_MOV32  ][EX86_TARGET_MEMORY_32   ][EX86_TARGET_MEMORY_32   ][EX86_TARGET_NONE        ] = &mov32_m_m,
#endif

#if defined(REGISTER_SIZE) && REGISTER_SIZE >= 64
    [EX86_ISA_8086_OP_MOV64  ][EX86_TARGET_REGISTER_64 ][EX86_TARGET_REGISTER_64 ][EX86_TARGET_NONE        ] = &mov64_r_r,
    [EX86_ISA_8086_OP_MOV64  ][EX86_TARGET_REGISTER_64 ][EX86_TARGET_IMMEDIATE_64][EX86_TARGET_NONE        ] = &mov64_r_i,
    [EX86_ISA_8086_OP_MOV64  ][EX86_TARGET_MEMORY_64   ][EX86_TARGET_IMMEDIATE_64][EX86_TARGET_NONE        ] = &mov64_m_i,
    [EX86_ISA_8086_OP_MOV64  ][EX86_TARGET_REGISTER_64 ][EX86_TARGET_MEMORY_64   ][EX86_TARGET_NONE        ] = &mov64_r_m,
    [EX86_ISA_8086_OP_MOV64  ][EX86_TARGET_MEMORY_64   ][EX86_TARGET_REGISTER_64 ][EX86_TARGET_NONE        ] = &mov64_m_r,
    [EX86_ISA_8086_OP_MOV64  ][EX86_TARGET_MEMORY_64   ][EX86_TARGET_MEMORY_64   ][EX86_TARGET_NONE        ] = &mov64_m_m,
#endif
};

static void on_register(ex86_interpreter *interp) {
}

static void on_unregister(ex86_interpreter *interp) {
}

static ex86_isa isa = {
    .id             = EX86_ISA_8086_ID,
    .name           = EX86_ISA_8086_NAME,
    .on_register    = &on_register,
    .on_unregister  = &on_unregister,
    .lookup         = (ex86_instruction_candidates **)&lookup
};

ex86_isa *ex86_isa_8086() {
    return &isa;
}
