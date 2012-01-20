#include <stdint.h>

#include "isa.h"
#include "context.h"
#include "register.h"
#include "memory.h"

#include "isa/8086.h"

/**
 * mov16 register, register
 */
EX86_SPECIFY_INSTRUCTION(
    mov16_r_r,
    EX86_TARGET_REGISTER,
    EX86_TARGET_REGISTER,
    EX86_TARGET_NONE
) {
    *dest.r16 = *src1.r16;
}

/**
 * mov16 register, immediate
 */
EX86_SPECIFY_INSTRUCTION(
    mov16_r_i,
    EX86_TARGET_REGISTER,
    EX86_TARGET_IMMEDIATE,
    EX86_TARGET_NONE
) {
    *dest.r16 = src1.i16;
}

/**
 * mov16 memory, immediate
 */
EX86_SPECIFY_INSTRUCTION(
    mov16_m_i,
    EX86_TARGET_MEMORY,
    EX86_TARGET_IMMEDIATE,
    EX86_TARGET_NONE
) {
    *dest.p16 = src1.i16;
}

/**
 * mov16 register, memory
 */
EX86_SPECIFY_INSTRUCTION(
    mov16_r_m,
    EX86_TARGET_REGISTER,
    EX86_TARGET_MEMORY,
    EX86_TARGET_NONE
) {
    *dest.r16 = *src1.p16;
}

/**
 * mov16 memory, register
 */
EX86_SPECIFY_INSTRUCTION(
    mov16_m_r,
    EX86_TARGET_MEMORY,
    EX86_TARGET_REGISTER,
    EX86_TARGET_NONE
) {
    *dest.p16 = *src1.r16;
}

/**
 * mov16 memory, memory
 */
EX86_SPECIFY_INSTRUCTION(
    mov16_m_m,
    EX86_TARGET_MEMORY,
    EX86_TARGET_MEMORY,
    EX86_TARGET_NONE
) {
    *dest.p16 = *src1.p16;
}

/**
 * mov32 register, register
 */
EX86_SPECIFY_INSTRUCTION(
    mov32_r_r,
    EX86_TARGET_REGISTER,
    EX86_TARGET_REGISTER,
    EX86_TARGET_NONE
) {
    *dest.r32 = *src1.r32;
}

/**
 * mov32 register, immediate
 */
EX86_SPECIFY_INSTRUCTION(
    mov32_r_i,
    EX86_TARGET_REGISTER,
    EX86_TARGET_IMMEDIATE,
    EX86_TARGET_NONE
) {
    *dest.r32 = src1.i32;
}

/**
 * mov32 memory, immediate
 */
EX86_SPECIFY_INSTRUCTION(
    mov32_m_i,
    EX86_TARGET_MEMORY,
    EX86_TARGET_IMMEDIATE,
    EX86_TARGET_NONE
) {
    *dest.p32 = src1.i32;
}

/**
 * mov32 register, memory
 */
EX86_SPECIFY_INSTRUCTION(
    mov32_r_m,
    EX86_TARGET_REGISTER,
    EX86_TARGET_MEMORY,
    EX86_TARGET_NONE
) {
    *dest.r32 = *src1.p32;
}

/**
 * mov32 memory, register
 */
EX86_SPECIFY_INSTRUCTION(
    mov32_m_r,
    EX86_TARGET_MEMORY,
    EX86_TARGET_REGISTER,
    EX86_TARGET_NONE
) {
    *dest.p32 = *src1.r32;
}

/**
 * mov32 memory, memory
 */
EX86_SPECIFY_INSTRUCTION(
    mov32_m_m,
    EX86_TARGET_MEMORY,
    EX86_TARGET_MEMORY,
    EX86_TARGET_NONE
) {
    *dest.p32 = *src1.p32;
}

/**
 * mov64 register, register
 */
EX86_SPECIFY_INSTRUCTION(
    mov64_r_r,
    EX86_TARGET_REGISTER,
    EX86_TARGET_REGISTER,
    EX86_TARGET_NONE
) {
    *dest.r64 = *src1.r64;
}

/**
 * mov64 register, immediate
 */
EX86_SPECIFY_INSTRUCTION(
    mov64_r_i,
    EX86_TARGET_REGISTER,
    EX86_TARGET_IMMEDIATE,
    EX86_TARGET_NONE
) {
    *dest.r64 = src1.i64;
}

/**
 * mov64 memory, immediate
 */
EX86_SPECIFY_INSTRUCTION(
    mov64_m_i,
    EX86_TARGET_MEMORY,
    EX86_TARGET_IMMEDIATE,
    EX86_TARGET_NONE
) {
    *dest.p64 = src1.i64;
}

/**
 * mov64 register, memory
 */
EX86_SPECIFY_INSTRUCTION(
    mov64_r_m,
    EX86_TARGET_REGISTER,
    EX86_TARGET_MEMORY,
    EX86_TARGET_NONE
) {
    *dest.r64 = *src1.p64;
}

/**
 * mov64 memory, register
 */
EX86_SPECIFY_INSTRUCTION(
    mov64_m_r,
    EX86_TARGET_MEMORY,
    EX86_TARGET_REGISTER,
    EX86_TARGET_NONE
) {
    *dest.p64 = *src1.r64;
}

/**
 * mov64 memory, memory
 */
EX86_SPECIFY_INSTRUCTION(
    mov64_m_m,
    EX86_TARGET_MEMORY,
    EX86_TARGET_MEMORY,
    EX86_TARGET_NONE
) {
    *dest.p64 = *src1.p64;
}
