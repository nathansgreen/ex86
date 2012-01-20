#include "context.h"
#include "register.h"
#include "memory.h"
#include "types.h"

/**
 * movb register, register
 */
static void movb_r_r(ex86_register_16 *src, ex86_register_16 *dest) {
    *dest = *src;
}

/**
 * movb immediate, register
 */
static void movb_i_r(uint_16t src, ex86_register_16 *dest) {
    *dest = src;
}

/**
 * movb immediate, memory
 */
static void movb_i_m(uint_16t src, ex86_pointer_16 dest) {
    *dest = src;
}

/**
 * movb memory, register
 */
static void movb_m_r(ex86_pointer_16 src, ex86_register_16 *dest) {
    *dest = *src;
}

/**
 * movb register, memory
 */
static void movb_r_m(ex86_register_16 *src, ex86_pointer_16 dest) {
    *dest = *src;
}

/**
 * movb memory, memory
 */
static void movb_m_m(ex86_pointer_16 src, ex86_pointer_16 dest) {
    *dest = *src;
}

/**
 * movl register, register
 */
static void movl_r_r(ex86_register_32 *src, ex86_register_32 *dest) {
    *dest = *src;
}

/**
 * movl immediate, register
 */
static void movl_i_r(uint_32t src, ex86_register_32 *dest) {
    *dest = src;
}

/**
 * movl immediate, memory
 */
static void movl_i_m(uint_16t src, ex86_pointer_32 dest) {
    *dest = src;
}

/**
 * movl memory, register
 */
static void movl_m_r(ex86_pointer_32 src, ex86_register_32 *dest) {
    *dest = *src;
}

/**
 * movl register, memory
 */
static void movl_r_m(ex86_register_32 *src, ex86_pointer_32 dest) {
    *dest = *src;
}

/**
 * movl memory, memory
 */
static void movl_m_m(ex86_pointer_32 src, ex86_pointer_32 dest) {
    *dest = *src;
}

/**
 * movq register, register
 */
static void movq_r_r(ex86_register_64 *src, ex86_register_64 *dest) {
    *dest = *src;
}

/**
 * movq immediate, register
 */
static void movq_i_r(uint_64t src, ex86_register_64 *dest) {
    *dest = src;
}

/**
 * movq immediate, memory
 */
static void movq_i_m(uint_32t src, ex86_pointer_64 dest) {
    *dest = src;
}

/**
 * movq memory, register
 */
static void movq_m_r(ex86_pointer_64 src, ex86_register_64 *dest) {
    *dest = *src;
}

/**
 * movl register, memory
 */
static void movq_r_m(ex86_register_64 *src, ex86_pointer_64 dest) {
    *dest = *src;
}

/**
 * movl memory, memory
 */
static void movq_m_m(ex86_pointer_64 src, ex86_pointer_64 dest) {
    *dest = *src;
}
