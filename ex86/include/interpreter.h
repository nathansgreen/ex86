#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include "isa.h"
#include "context.h"

#include "isa/defs.h"

struct ex86_config;

/** The interpreter struct. */
typedef struct ex86_interpreter {
    struct ex86_context *ctx;
    ex86_instruction_candidates **isas[EX86_MAX_ISA];
} ex86_interpreter;

/** Allocate a new interpreter. */
ex86_interpreter *ex86_interpreter_new(struct ex86_config *);

/** Destroy the interpreter. */
void ex86_interpreter_destroy(ex86_interpreter *);

/** The type of the statement. */
typedef enum ex86_statement_type {
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
            char *comment;
        } comment;

        /** A named label. */
        struct {
            /** Symbol name. */
            char *symbol;
        } label;

        /** An instruction. */
        struct {
            /** ISA id. */
            ex86_isa_id id;

            /** Opcode. */
            ex86_opcode op;

            /** Destination parameter. */
            ex86_instruction_param dest;

            /** Destination parameter type. */
            ex86_instruction_param_type dest_type;

            /** First source register. */
            ex86_instruction_param src1;

            /** First source register parameter type. */
            ex86_instruction_param_type src1_type;

            /** Second source register (for use with AVX, etc.). */
            ex86_instruction_param src2;

            /** Second source register parameter type. */
            ex86_instruction_param_type src2_type;
        } instruction;
    } data;
} ex86_statement;

/** Evaluate a statement. */
ex86_error ex86_evaluate(ex86_interpreter *, ex86_statement *);

#endif
