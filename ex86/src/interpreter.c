#include "interpreter.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "uthash.h"

#include "isa.h"
#include "syntax.h"
#include "config.h"
#include "context.h"
#include "log.h"

void ex86_interpreter_register_syntax(ex86_interpreter *interp,
                                      struct ex86_syntax *syntax)
{
    syntax->on_register(interp);
    EX86_LOG_DEBUG("registered syntax: %s", syntax->name);
    HASH_ADD_KEYPTR(hh, interp->syntaxes, syntax->name, strlen(syntax->name),
                    syntax);
}

static void interpreter_map_registers(ex86_interpreter *);
static void interpreter_init(ex86_interpreter *);

ex86_interpreter *ex86_interpreter_new(ex86_config *config) {
    ex86_interpreter *interp = (ex86_interpreter *)malloc(sizeof(ex86_interpreter));
    EX86_LOG_DEBUG("created interpreter");
    interp->ctx = ex86_context_new(config);
    interp->isas = NULL;
    interp->syntaxes = NULL;
    interp->register_map = NULL;
    interpreter_map_registers(interp);
    interpreter_init(interp);
    return interp;
}

void ex86_interpreter_destroy(ex86_interpreter *interp) {
    ex86_syntax *syntax, *tmp1;
    HASH_ITER(hh, interp->syntaxes, syntax, tmp1) {
        syntax->on_unregister(interp);
        EX86_LOG_DEBUG("unregistered syntax: %s", syntax->name);
        free(syntax);
    }

    ex86_register_mapping *rmap, *tmp2;
    HASH_ITER(hh, interp->register_map, rmap, tmp2) {
        free(rmap);
    }

    ex86_context_destroy(interp->ctx);
    free(interp);

    EX86_LOG_DEBUG("destroyed interpreter");
}

#define ADD_REGISTER_MAPPING(INTERP, NAME, TYPE, TARGET) { \
    ex86_register_mapping *rmap = (ex86_register_mapping *)malloc(sizeof(ex86_register_mapping)); \
    rmap->name = NAME; \
    rmap->type = TYPE; \
    rmap->target = &interp->ctx->TARGET; \
    HASH_ADD_KEYPTR(hh, interp->register_map, rmap->name, strlen(rmap->name), rmap); \
}

static void interpreter_map_registers(ex86_interpreter *interp) {
#if defined(REGISTER_SIZE) && REGISTER_SIZE >= 64
    ADD_REGISTER_MAPPING(interp, "rax", EX86_TARGET_REGISTER_64, ax);
    ADD_REGISTER_MAPPING(interp, "rbx", EX86_TARGET_REGISTER_64, bx);
    ADD_REGISTER_MAPPING(interp, "rcx", EX86_TARGET_REGISTER_64, cx);
    ADD_REGISTER_MAPPING(interp, "rdx", EX86_TARGET_REGISTER_64, dx);
#endif

#if defined(REGISTER_SIZE) && REGISTER_SIZE >= 32
    ADD_REGISTER_MAPPING(interp, "eax", EX86_TARGET_REGISTER_32, ax);
    ADD_REGISTER_MAPPING(interp, "ebx", EX86_TARGET_REGISTER_32, bx);
    ADD_REGISTER_MAPPING(interp, "ecx", EX86_TARGET_REGISTER_32, cx);
    ADD_REGISTER_MAPPING(interp, "edx", EX86_TARGET_REGISTER_32, dx);
#endif

#if defined(REGISTER_SIZE) && REGISTER_SIZE >= 16
    ADD_REGISTER_MAPPING(interp,  "ax", EX86_TARGET_REGISTER_16, ax);
    ADD_REGISTER_MAPPING(interp,  "bx", EX86_TARGET_REGISTER_16, bx);
    ADD_REGISTER_MAPPING(interp,  "cx", EX86_TARGET_REGISTER_16, cx);
    ADD_REGISTER_MAPPING(interp,  "dx", EX86_TARGET_REGISTER_16, dx);
#endif
}

#undef ADD_REGISTER_MAPPING

/* do ISA/syntax registration stuff here */

#ifdef ISA_8086
#include "isa/8086.h"
#endif

static ex86_instruction_candidates **isas[] = {
#ifdef ISA_8086
    [EX86_ISA_8086_ID] = NULL
#endif
};

#ifdef SYNTAX_INTEL
#include "syntax/intel.h"
#endif

static void interpreter_init(ex86_interpreter *interp) {
    /* attach ISAs */
#ifdef ISA_8086
    isas[EX86_ISA_8086_ID] = ex86_isa_8086_lookup();
#endif
    interp->isas = (ex86_instruction_candidates ***)&isas;

    /* register syntaxes */
#ifdef SYNTAX_INTEL
    ex86_interpreter_register_syntax(interp, ex86_syntax_intel());
#endif
}
