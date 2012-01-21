#include "syntax/intel.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "uthash.h"

#include "error.h"
#include "log.h"
#include "isa.h"
#include "syntax.h"
#include "interpreter.h"

#ifdef ISA_8086
#include "isa/8086.h"
#endif

/** Table of mnemonic to ISA+opcode translations. */
typedef struct ex86_syntax_intel_mnemonic_entry {
    const char *name;
    ex86_isa_id id;
    ex86_opcode op;
    UT_hash_handle hh;
} ex86_syntax_intel_mnemonic_entry;

static ex86_syntax_intel_mnemonic_entry *lookup = NULL;

#define ADD_INTEL_MNEMONIC(NAME, ID, OP) \
{ \
    ex86_syntax_intel_mnemonic_entry *entry = (ex86_syntax_intel_mnemonic_entry *)malloc(sizeof(ex86_syntax_intel_mnemonic_entry)); \
    entry->id = ID; \
    entry->op = OP; \
    HASH_ADD_KEYPTR(hh, lookup, entry->name, strlen(entry->name), entry); \
}

static void on_register(ex86_interpreter *interp) {
    /* initialize string -> enumerated mnemonic hashtable */
#ifdef ISA_8086
    ADD_INTEL_MNEMONIC("nop", EX86_ISA_8086_ID, EX86_ISA_8086_OP_NOP)
    ADD_INTEL_MNEMONIC("mov", EX86_ISA_8086_ID, EX86_ISA_8086_OP_MOV)
#endif
}

#undef ADD_INTEL_MNEMONIC

static void on_unregister(ex86_interpreter *interp) {
    ex86_syntax_intel_mnemonic_entry *entry, *tmp;
    HASH_ITER(hh, lookup, entry, tmp) {
        free(entry);
    }
}

#define FILL_PARAMETER(INTERP, STMT, STR, FIELD) \
if(dest != NULL) { \
    long long int temp; \
    errno = 0; \
    strtoll(STR, NULL, 10); \
    if(!errno) { \
        ex86_immediate immediate = (ex86_immediate)temp; \
        STMT->data.instruction.FIELD.i = immediate; \
        STMT->data.instruction.FIELD##_type = EX86_IMMEDIATE_TYPE(immediate); \
        return true; \
    } \
    ex86_register_mapping *rmap = NULL; \
    HASH_FIND_STR(INTERP->register_map, STR, rmap); \
    if(rmap != NULL) \
    { \
        STMT->data.instruction.FIELD##_type = rmap->type; \
    } \
    return false; \
}

bool fill_parameters(ex86_interpreter *interp, ex86_statement *stmt,
                     char *dest, char *src1, char *src2) {
    FILL_PARAMETER(interp, stmt, dest, dest)
    FILL_PARAMETER(interp, stmt, src1, src1)
    FILL_PARAMETER(interp, stmt, src2, src2)
    return true;
}

#undef FILL_PARAMETER

bool emit_statement(ex86_interpreter *interp, const char *line,
                    ex86_statement *stmt, ex86_error *errno) {
    /* try scan for a label first with PROFESSIONAL SSCANF PARSING */
    char *label_name = NULL;
    if(sscanf(line, "%as:", &label_name)) {
        stmt->type = EX86_STATEMENT_LABEL;
        stmt->data.label.symbol = label_name;
        return true;
    }

    /* we should now scan for mnemonics (last resort) */
    ex86_syntax_intel_mnemonic_entry *entry = NULL;
    char *instr_mnemonic = NULL;
    char *instr_dest = NULL;
    char *instr_src1 = NULL;
    char *instr_src2 = NULL;

    /* scan for a 3 argument instruction invocation */
    if(sscanf(line, "%as %as, %as, %as", &instr_mnemonic, &instr_dest,
                                         &instr_src1, &instr_src2)) {
        stmt->type = EX86_STATEMENT_INSTRUCTION;

        HASH_FIND_STR(lookup, instr_mnemonic, entry);
        if(entry == NULL) {
            *errno = EX86_ERROR_OP_NOT_FOUND;
            goto cleanup;
        }

        stmt->data.instruction.id = entry->id;
        stmt->data.instruction.op = entry->op;
        if(!fill_parameters(interp, stmt, instr_dest, instr_src1,
                            instr_src2)) {
            *errno = EX86_ERROR_SYNTAX_ERROR;
            goto cleanup;
        }
        return true;
    }

    /* scan for a 2 argument instruction now */
    if(sscanf(line, "%as %as, %as", &instr_mnemonic, &instr_dest,
                                    &instr_src1)) {
        stmt->type = EX86_STATEMENT_INSTRUCTION;

        HASH_FIND_STR(lookup, instr_mnemonic, entry);
        if(entry == NULL) {
            *errno = EX86_ERROR_OP_NOT_FOUND;
            goto cleanup;
        }

        stmt->data.instruction.id = entry->id;
        stmt->data.instruction.op = entry->op;
        stmt->data.instruction.src2_type = EX86_TARGET_NONE;
        if(!fill_parameters(interp, stmt, instr_dest, instr_src1,
                            NULL)) {
            *errno = EX86_ERROR_SYNTAX_ERROR;
            goto cleanup;
        }
        return true;
    }

    /* scan for a 1 argument */
    if(sscanf(line, "%as %as", &instr_mnemonic, &instr_dest)) {
        stmt->type = EX86_STATEMENT_INSTRUCTION;

        HASH_FIND_STR(lookup, instr_mnemonic, entry);
        if(entry == NULL) {
            *errno = EX86_ERROR_OP_NOT_FOUND;
            goto cleanup;
        }

        stmt->data.instruction.id = entry->id;
        stmt->data.instruction.op = entry->op;
        stmt->data.instruction.src1_type = EX86_TARGET_NONE;
        stmt->data.instruction.src2_type = EX86_TARGET_NONE;
        if(!fill_parameters(interp, stmt, instr_dest, NULL, NULL)) {
            *errno = EX86_ERROR_SYNTAX_ERROR;
            goto cleanup;
        }
        return true;
    }

    /* oh come on, really? */
    if(sscanf(line, "%as", &instr_mnemonic)) {
        stmt->type = EX86_STATEMENT_INSTRUCTION;

        HASH_FIND_STR(lookup, instr_mnemonic, entry);
        if(entry == NULL) {
            *errno = EX86_ERROR_OP_NOT_FOUND;
            goto cleanup;
        }

        stmt->data.instruction.id = entry->id;
        stmt->data.instruction.op = entry->op;
        stmt->data.instruction.dest_type = EX86_TARGET_NONE;
        stmt->data.instruction.src1_type = EX86_TARGET_NONE;
        stmt->data.instruction.src2_type = EX86_TARGET_NONE;
    }

    *errno = EX86_ERROR_SYNTAX_ERROR;

cleanup:
    free(instr_mnemonic);
    free(instr_dest);
    free(instr_src1);
    free(instr_src2);
    return false;
}

static ex86_syntax syntax = {
    .name           = "intel",
    .on_register    = &on_register,
    .on_unregister  = &on_unregister,
    //.emit_statement = &emit_statement
};

ex86_syntax *ex86_syntax_intel() {
    return &syntax;
}
