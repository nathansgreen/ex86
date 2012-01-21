#include "interpreter.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "isa.h"
#include "config.h"
#include "context.h"
#include "log.h"

static void interpreter_init(ex86_interpreter *);

ex86_interpreter *ex86_interpreter_new(ex86_config *config) {
    ex86_interpreter *interp = (ex86_interpreter *)malloc(sizeof(ex86_interpreter));
    EX86_LOG_DEBUG("created interpreter");
    interp->ctx = ex86_context_new(config);
    interpreter_init(interp);
    return interp;
}

ex86_error ex86_evaluate(ex86_interpreter *interp, ex86_statement *stmt) {
    switch(stmt->type)
    {
        case EX86_STATEMENT_COMMENT: {
            return EX86_NO_ERROR;
        }
        case EX86_STATEMENT_LABEL: {
            return EX86_NO_ERROR;
        }
        case EX86_STATEMENT_INSTRUCTION: {
            ex86_instruction_candidates **isa_lut = interp->isas
                [stmt->data.instruction.id];
            ex86_instruction_func *instr_func = *isa_lut
                [stmt->data.instruction.op]
                [stmt->data.instruction.dest_type]
                [stmt->data.instruction.src1_type]
                [stmt->data.instruction.src2_type];
            if(instr_func == NULL) {
                return EX86_ERROR_INSTRUCTION_SIGNATURE_MISMATCH;
            }
            instr_func(interp->ctx,
                       stmt->data.instruction.dest,
                       stmt->data.instruction.src1,
                       stmt->data.instruction.src2);
            return EX86_NO_ERROR;
        }
    }
    return EX86_ERROR_UNKNOWN;
}

void ex86_interpreter_destroy(ex86_interpreter *interp) {
    ex86_context_destroy(interp->ctx);
    free(interp);

    EX86_LOG_DEBUG("destroyed interpreter");
}

/* do ISA registration stuff here */
#include "isa/defs.h"

#ifdef ISA_8086
#include "isa/8086.h"
#endif

static void interpreter_init(ex86_interpreter *interp) {
    /* attach ISAs */
#ifdef ISA_8086
    interp->isas[EX86_ISA_8086] = ex86_isa_8086_lookup();
    EX86_LOG_DEBUG("loaded 8086 ISA");
#endif
}
