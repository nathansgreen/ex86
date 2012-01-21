#ifndef SYNTAX_INTEL_H_
#define SYNTAX_INTEL_H_

#include "uthash.h"

#include "syntax.h"
#include "interpreter.h"

/** Register the Intel syntax with the interpreter. */
void ex86_syntax_intel_register(ex86_interpreter *);

/** The enum of mnemonics. */
typedef enum ex86_syntax_intel_mnemonic {
    EX86_INTEL_MOV,
    EX86_INTEL_NOP
} ex86_syntax_intel_mnemonic;

/**  */
typedef struct ex86_syntax_intel_mnemonic_entry {
    const char *name;
    ex86_syntax_intel_mnemonic op;
    UT_hash_handle hh;
} ex86_syntax_intel_mnemonic_entry;

struct ex86_syntax *ex86_syntax_intel();

#endif
