#include "isa/8086.h"

#include "isa.h"
#include "interpreter.h"
#include "error.h"
#include "assert.h"
#include "log.h"

/** nop */
EX86_INSTRUCTION(nop) {
}

/** mov8 registerlo, registerlo */
EX86_INSTRUCTION(mov8_rl_rl) {
    EX86_REGISTER_8_LO_SET(ctx, dest.r, EX86_REGISTER_8_LO_GET(ctx, src1.r));
}

/** mov8 registerlo, registerhi */
EX86_INSTRUCTION(mov8_rl_rh) {
    EX86_REGISTER_8_LO_SET(ctx, dest.r, EX86_REGISTER_8_HI_GET(ctx, src1.r));
}

/** mov8 registerhi, registerlo */
EX86_INSTRUCTION(mov8_rh_rl) {
    EX86_REGISTER_8_HI_SET(ctx, dest.r, EX86_REGISTER_8_LO_GET(ctx, src1.r));
}

/** mov8 registerhi, registerhi */
EX86_INSTRUCTION(mov8_rh_rh) {
    EX86_REGISTER_8_HI_SET(ctx, dest.r, EX86_REGISTER_8_HI_GET(ctx, src1.r));
}

/** mov8 registerlo, immediate */
EX86_INSTRUCTION(mov8_rl_i) {
    EX86_REGISTER_8_LO_SET(ctx, dest.r, EX86_IMMEDIATE_8(src1.i));
}

/** mov8 registerhi, immediate */
EX86_INSTRUCTION(mov8_rh_i) {
    EX86_REGISTER_8_HI_SET(ctx, dest.r, EX86_IMMEDIATE_8(src1.i));
}

/** mov8 memory, immediate */
EX86_INSTRUCTION(mov8_m_i) {
    EX86_MEMORY_8_SET(ctx, dest.p, EX86_IMMEDIATE_8(src1.i));
}

/** mov8 registerlo, memory */
EX86_INSTRUCTION(mov8_rl_m) {
    EX86_REGISTER_8_LO_SET(ctx, dest.r, EX86_MEMORY_8_GET(ctx, dest.p));
}

/** mov8 registerhi, memory */
EX86_INSTRUCTION(mov8_rh_m) {
    EX86_REGISTER_8_HI_SET(ctx, dest.r, EX86_MEMORY_8_GET(ctx, dest.p));
}

/** mov8 memory, registerlo */
EX86_INSTRUCTION(mov8_m_rl) {
    EX86_MEMORY_8_SET(ctx, dest.p, EX86_REGISTER_8_LO_GET(ctx, dest.r));
}

/** mov8 memory, registerhi */
EX86_INSTRUCTION(mov8_m_rh) {
    EX86_MEMORY_8_SET(ctx, dest.p, EX86_REGISTER_8_HI_GET(ctx, dest.r));
}

/** mov8 memory, memory */
EX86_INSTRUCTION(mov8_m_m) {
    EX86_MEMORY_8_SET(ctx, dest.p, EX86_MEMORY_8_GET(ctx, src1.p));
}

#if defined(REGISTER_SIZE) && REGISTER_SIZE >= 16
/** mov16 register, register */
EX86_INSTRUCTION(mov16_r_r) {
    EX86_REGISTER_16_SET(ctx, dest.r, EX86_REGISTER_16_GET(ctx, src1.r));
}

/** mov16 register, immediate */
EX86_INSTRUCTION(mov16_r_i) {
    EX86_REGISTER_16_SET(ctx, dest.r, EX86_IMMEDIATE_16(src1.i));
}

/** mov16 memory, immediate */
EX86_INSTRUCTION(mov16_m_i) {
    EX86_MEMORY_16_SET(ctx, dest.p, EX86_IMMEDIATE_16(src1.i));
}

/** mov16 register, memory */
EX86_INSTRUCTION(mov16_r_m) {
    EX86_REGISTER_16_SET(ctx, dest.r, EX86_MEMORY_16_GET(ctx, dest.p));
}

/** mov16 memory, register */
EX86_INSTRUCTION(mov16_m_r) {
    EX86_MEMORY_16_SET(ctx, dest.p, EX86_REGISTER_16_GET(ctx, dest.r));
}

/** mov16 memory, memory */
EX86_INSTRUCTION(mov16_m_m) {
    EX86_MEMORY_16_SET(ctx, dest.p, EX86_MEMORY_16_GET(ctx, dest.p));
}
#endif

#if defined(REGISTER_SIZE) && REGISTER_SIZE >= 32
/** mov32 register, register */
EX86_INSTRUCTION(mov32_r_r) {
    EX86_REGISTER_32_SET(ctx, dest.r, EX86_REGISTER_32_GET(ctx, src1.r));
}

/** mov32 register, immediate */
EX86_INSTRUCTION(mov32_r_i) {
    EX86_REGISTER_32_SET(ctx, dest.r, EX86_IMMEDIATE_32(src1.i));
}

/** mov32 memory, immediate */
EX86_INSTRUCTION(mov32_m_i) {
    EX86_MEMORY_32_SET(ctx, dest.p, EX86_IMMEDIATE_32(src1.i));
}

/** mov32 register, memory */
EX86_INSTRUCTION(mov32_r_m) {
    EX86_REGISTER_32_SET(ctx, dest.r, EX86_MEMORY_32_GET(ctx, dest.p));
}

/** mov32 memory, register */
EX86_INSTRUCTION(mov32_m_r) {
    EX86_MEMORY_32_SET(ctx, dest.p, EX86_REGISTER_32_GET(ctx, dest.r));
}

/** mov32 memory, memory */
EX86_INSTRUCTION(mov32_m_m) {
    EX86_MEMORY_32_SET(ctx, dest.p, EX86_MEMORY_32_GET(ctx, dest.p));
}
#endif

#if defined(REGISTER_SIZE) && REGISTER_SIZE >= 64
/** mov64 register, register */
EX86_INSTRUCTION(mov64_r_r) {
    EX86_REGISTER_64_SET(ctx, dest.r, EX86_REGISTER_64_GET(ctx, src1.r));
}

/** mov64 register, immediate */
EX86_INSTRUCTION(mov64_r_i) {
    EX86_REGISTER_64_SET(ctx, dest.r, EX86_IMMEDIATE_64(src1.i));
}

/** mov64 memory, immediate */
EX86_INSTRUCTION(mov64_m_i) {
    EX86_MEMORY_64_SET(ctx, dest.p, EX86_IMMEDIATE_64(src1.i));
}

/** mov64 register, memory */
EX86_INSTRUCTION(mov64_r_m) {
    EX86_REGISTER_64_SET(ctx, dest.r, EX86_MEMORY_64_GET(ctx, dest.p));
}

/** mov64 memory, register */
EX86_INSTRUCTION(mov64_m_r) {
    EX86_MEMORY_64_SET(ctx, dest.p, EX86_REGISTER_64_GET(ctx, dest.r));
}

/** mov64 memory, memory */
EX86_INSTRUCTION(mov64_m_m) {
    EX86_MEMORY_64_SET(ctx, dest.p, EX86_MEMORY_64_GET(ctx, dest.p));
}
#endif

static ex86_instruction_candidates lookup[EX86_MAX_ISA_8086_OP] = {
    [EX86_ISA_8086_OP_NOP     ][EX86_TARGET_NONE         ][EX86_TARGET_NONE         ][EX86_TARGET_NONE         ] = &nop,

    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_REGISTER_8_LO][EX86_TARGET_REGISTER_8_LO][EX86_TARGET_NONE         ] = &mov8_rl_rl,
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_REGISTER_8_LO][EX86_TARGET_REGISTER_8_HI][EX86_TARGET_NONE         ] = &mov8_rl_rh,
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_REGISTER_8_HI][EX86_TARGET_REGISTER_8_LO][EX86_TARGET_NONE         ] = &mov8_rh_rl,
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_REGISTER_8_HI][EX86_TARGET_REGISTER_8_HI][EX86_TARGET_NONE         ] = &mov8_rh_rh,
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_REGISTER_8_LO][EX86_TARGET_IMMEDIATE_8  ][EX86_TARGET_NONE         ] = &mov8_rl_i,
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_REGISTER_8_HI][EX86_TARGET_IMMEDIATE_8  ][EX86_TARGET_NONE         ] = &mov8_rh_i,
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_MEMORY_8     ][EX86_TARGET_IMMEDIATE_8  ][EX86_TARGET_NONE         ] = &mov8_m_i,
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_REGISTER_8_LO][EX86_TARGET_MEMORY_8     ][EX86_TARGET_NONE         ] = &mov8_rl_m,
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_REGISTER_8_HI][EX86_TARGET_MEMORY_8     ][EX86_TARGET_NONE         ] = &mov8_rh_m,
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_MEMORY_16    ][EX86_TARGET_REGISTER_8_LO][EX86_TARGET_NONE         ] = &mov8_m_rl,
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_MEMORY_16    ][EX86_TARGET_REGISTER_8_HI][EX86_TARGET_NONE         ] = &mov8_m_rh,
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_MEMORY_8     ][EX86_TARGET_MEMORY_8     ][EX86_TARGET_NONE         ] = &mov8_m_m,

#if defined(REGISTER_SIZE) && REGISTER_SIZE >= 16
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_REGISTER_16  ][EX86_TARGET_REGISTER_16  ][EX86_TARGET_NONE         ] = &mov16_r_r,
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_REGISTER_16  ][EX86_TARGET_IMMEDIATE_16 ][EX86_TARGET_NONE         ] = &mov16_r_i,
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_REGISTER_16  ][EX86_TARGET_IMMEDIATE_8  ][EX86_TARGET_NONE         ] = &mov16_r_i,
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_MEMORY_16    ][EX86_TARGET_IMMEDIATE_16 ][EX86_TARGET_NONE         ] = &mov16_m_i,
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_MEMORY_16    ][EX86_TARGET_IMMEDIATE_8  ][EX86_TARGET_NONE         ] = &mov16_m_i,
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_REGISTER_16  ][EX86_TARGET_MEMORY_16    ][EX86_TARGET_NONE         ] = &mov16_r_m,
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_MEMORY_16    ][EX86_TARGET_REGISTER_16  ][EX86_TARGET_NONE         ] = &mov16_m_r,
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_MEMORY_16    ][EX86_TARGET_MEMORY_16    ][EX86_TARGET_NONE         ] = &mov16_m_m,
#endif

#if defined(REGISTER_SIZE) && REGISTER_SIZE >= 32
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_REGISTER_32  ][EX86_TARGET_REGISTER_32  ][EX86_TARGET_NONE         ] = &mov32_r_r,
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_REGISTER_32  ][EX86_TARGET_IMMEDIATE_32 ][EX86_TARGET_NONE         ] = &mov32_r_i,
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_REGISTER_32  ][EX86_TARGET_IMMEDIATE_16 ][EX86_TARGET_NONE         ] = &mov32_r_i,
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_REGISTER_32  ][EX86_TARGET_IMMEDIATE_8  ][EX86_TARGET_NONE         ] = &mov32_r_i,
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_MEMORY_32    ][EX86_TARGET_IMMEDIATE_32 ][EX86_TARGET_NONE         ] = &mov32_m_i,
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_MEMORY_32    ][EX86_TARGET_IMMEDIATE_16 ][EX86_TARGET_NONE         ] = &mov32_m_i,
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_MEMORY_32    ][EX86_TARGET_IMMEDIATE_8  ][EX86_TARGET_NONE         ] = &mov32_m_i,
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_REGISTER_32  ][EX86_TARGET_MEMORY_32    ][EX86_TARGET_NONE         ] = &mov32_r_m,
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_MEMORY_32    ][EX86_TARGET_REGISTER_32  ][EX86_TARGET_NONE         ] = &mov32_m_r,
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_MEMORY_32    ][EX86_TARGET_MEMORY_32    ][EX86_TARGET_NONE         ] = &mov32_m_m,
#endif

#if defined(REGISTER_SIZE) && REGISTER_SIZE >= 64
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_REGISTER_64  ][EX86_TARGET_REGISTER_64  ][EX86_TARGET_NONE         ] = &mov64_r_r,
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_REGISTER_64  ][EX86_TARGET_IMMEDIATE_64 ][EX86_TARGET_NONE         ] = &mov64_r_i,
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_REGISTER_64  ][EX86_TARGET_IMMEDIATE_32 ][EX86_TARGET_NONE         ] = &mov64_r_i,
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_REGISTER_64  ][EX86_TARGET_IMMEDIATE_16 ][EX86_TARGET_NONE         ] = &mov64_r_i,
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_REGISTER_64  ][EX86_TARGET_IMMEDIATE_8  ][EX86_TARGET_NONE         ] = &mov64_r_i,
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_MEMORY_64    ][EX86_TARGET_IMMEDIATE_64 ][EX86_TARGET_NONE         ] = &mov64_m_i,
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_MEMORY_64    ][EX86_TARGET_IMMEDIATE_32 ][EX86_TARGET_NONE         ] = &mov64_m_i,
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_MEMORY_64    ][EX86_TARGET_IMMEDIATE_16 ][EX86_TARGET_NONE         ] = &mov64_m_i,
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_MEMORY_64    ][EX86_TARGET_IMMEDIATE_8  ][EX86_TARGET_NONE         ] = &mov64_m_i,
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_REGISTER_64  ][EX86_TARGET_MEMORY_64    ][EX86_TARGET_NONE         ] = &mov64_r_m,
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_MEMORY_64    ][EX86_TARGET_REGISTER_64  ][EX86_TARGET_NONE         ] = &mov64_m_r,
    [EX86_ISA_8086_OP_MOV     ][EX86_TARGET_MEMORY_64    ][EX86_TARGET_MEMORY_64    ][EX86_TARGET_NONE         ] = &mov64_m_m,
#endif
};

ex86_instruction_candidates **ex86_isa_8086_lookup() {
    return (ex86_instruction_candidates **)lookup;
}
