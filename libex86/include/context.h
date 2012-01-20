#ifndef CONTEXT_H_
#define CONTEXT_H_

#include "register.h"
#include "flags.h"

/**
 * The ex86 context context.
 */
typedef struct ex86_context {
    /** The accumulator register. */
    ex86_register ax;

    /** The base register. */
    ex86_register bx;

    /** The counter register. */
    ex86_register cx;

    /** The data register. */
    ex86_register dx;

    /** The source index register. */
    ex86_register si;

    /** The destination register. */
    ex86_register di;

    /** The base pointer register. */
    ex86_register bp;

    /** The stack pointer register. */
    ex86_register sp;

    /** The instruction pointer register. */
    ex86_register ip;

    /** The FLAGS register. */
    ex86_flags flags;
} ex86_context;

/**
 * Allocate a new ex86 context context.
 */
ex86_context *ex86_context_new();

/**
 * Destroy the ex86 context context.
 */
void ex86_context_destory(ex86_context *interp);

#endif
