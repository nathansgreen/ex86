#ifndef SYNTAX_H_
#define SYNTAX_H_

#include "isa.h"

/** The type of the statement. */
typedef enum ex86_statement_type {
    /** An unknown statement type. */
    EX86_STATEMENT_UNKNOWN = 0,

    /** A comment statement. */
    EX86_STATEMENT_COMMENT,

    /** A label statement. */
    EX86_STATEMENT_LABEL,

    /** An instruction statement. */
    EX86_STATEMENT_INSTRUCTION
} ex86_statement_type;

/** A statement. */
typedef struct ex86_statement {
    /** The type of the statement. */
    ex86_statement_type type;

    /** The statement data. */
    union {
        /** A comment. */
        struct {
            const char *comment;
        } comment;

        /** A named label. */
        struct {
            const char *symbol;
        } label;

        /** An instruction. */
        struct {
            ex86_isa_id id;
            ex86_opcode op;
            ex86_instruction_param dest;
            ex86_instruction_param src1;
            ex86_instruction_param src2;
        } instruction;
    } data;
} ex86_statement;

#endif
