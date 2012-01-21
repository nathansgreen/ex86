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

void ex86_interpreter_register_isa(ex86_interpreter *interp,
                                   struct ex86_isa *isa)
{
    isa->on_register(interp);
    EX86_LOG_DEBUG("registered ISA: %s", isa->name);
    HASH_ADD_INT(interp->isas, id, isa);
}

void ex86_interpreter_register_syntax(ex86_interpreter *interp,
                                      struct ex86_syntax *syntax)
{
    syntax->on_register(interp);
    EX86_LOG_DEBUG("registered syntax: %s", syntax->name);
    HASH_ADD_KEYPTR(hh, interp->syntaxes, syntax->name, strlen(syntax->name),
                    syntax);
}

static void interpreter_register(ex86_interpreter *interp);

ex86_interpreter *ex86_interpreter_new(ex86_config *config) {
    ex86_interpreter *interp = (ex86_interpreter *)malloc(sizeof(ex86_interpreter));
    EX86_LOG_DEBUG("created interpreter");
    interp->ctx = ex86_context_new(config);
    interp->isas = NULL;
    interp->syntaxes = NULL;
    interpreter_register(interp);
    return interp;
}

void ex86_interpreter_destroy(ex86_interpreter *interp) {
    ex86_isa *isa, *tmp1;
    HASH_ITER(hh, interp->isas, isa, tmp1) {
        isa->on_unregister(interp);
        EX86_LOG_DEBUG("unregistered ISA: %s", isa->name);
        free(isa);
    }

    ex86_syntax *syntax, *tmp2;
    HASH_ITER(hh, interp->syntaxes, syntax, tmp2) {
        syntax->on_unregister(interp);
        EX86_LOG_DEBUG("unregistered syntax: %s", syntax->name);
        free(syntax);
    }

    ex86_context_destroy(interp->ctx);
    free(interp);

    EX86_LOG_DEBUG("destroyed interpreter");
}

/* do ISA/syntax registration stuff here */

#ifdef ISA_8086
#include "isa/8086.h"
#endif

#ifdef SYNTAX_INTEL
#include "syntax/intel.h"
#endif

static void interpreter_register(ex86_interpreter *interp) {
    /* register ISAs */
#ifdef ISA_8086
    ex86_interpreter_register_isa(interp, ex86_isa_8086());
#endif

    /* register syntaxes */
#ifdef SYNTAX_INTEL
    ex86_interpreter_register_syntax(interp, ex86_syntax_intel());
#endif
}
