#ifndef SYNTAX_H_
#define SYNTAX_H_

#include "isa.h"

#include "uthash.h"

/** Forward declare interpreter. */
struct ex86_interpreter;

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
            /** Comment data. */
            const char *comment;
        } comment;

        /** A named label. */
        struct {
            /** Symbol name. */
            const char *symbol;
        } label;

        /** An instruction. */
        struct {
            /** ISA id. */
            ex86_isa_id id;

            /** Opcode. */
            ex86_opcode op;

            /** Destination parameter. */
            ex86_instruction_param dest;

            /** First source register. */
            ex86_instruction_param src1;

            /** Second source register (for use with AVX, etc.). */
            ex86_instruction_param src2;
        } instruction;
    } data;
} ex86_statement;

/** The registration function for syntaxes. */
typedef void ex86_syntax_register_func(struct ex86_interpreter *);

/** The unregistration function for syntaxes. */
typedef void ex86_syntax_unregister_func(struct ex86_interpreter *);

/** The syntax struct. */
typedef struct ex86_syntax {
    const char *name;
    ex86_syntax_register_func *on_register;
    ex86_syntax_unregister_func *on_unregister;
    UT_hash_handle hh;
} ex86_syntax;

#endif
