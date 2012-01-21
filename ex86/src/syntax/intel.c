#include "syntax/intel.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"
#include "isa.h"
#include "uthash.h"

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

void emit_statement() {
    
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
