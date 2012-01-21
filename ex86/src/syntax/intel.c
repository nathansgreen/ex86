#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "syntax/intel.h"

#include "log.h"
#include "uthash.h"

static ex86_syntax_intel_mnemonic_entry *lookup = NULL;

#define ADD_INTEL_MNEMONIC(NAME, CODE) \
{ \
    ex86_syntax_intel_mnemonic_entry *entry = (ex86_syntax_intel_mnemonic_entry *)malloc(sizeof(ex86_syntax_intel_mnemonic_entry)); \
    HASH_ADD_KEYPTR(hh, lookup, entry->name, strlen(entry->name), entry); \
}

static void on_register(ex86_interpreter *interp) {
    /* initialize string -> enumerated mnemonic hashtable */
    ADD_INTEL_MNEMONIC("nop", EX86_INTEL_NOP)
    ADD_INTEL_MNEMONIC("mov", EX86_INTEL_MOV)
}

#undef ADD_INTEL_MNEMONIC

static void on_unregister(ex86_interpreter *interp) {
    ex86_syntax_intel_mnemonic_entry *entry, *tmp;
    HASH_ITER(hh, lookup, entry, tmp) {
        free(entry);
    }
}

static ex86_syntax syntax = {
    .name = "intel",
    .on_register = &on_register,
    .on_unregister = &on_unregister
};

ex86_syntax *ex86_syntax_intel() {
    return &syntax;
}
