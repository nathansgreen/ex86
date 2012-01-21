#ifndef ERROR_H_
#define ERROR_H_

/** Error codes. */
typedef enum ex86_error {
    /** No error. */
    EX86_NO_ERROR = -1,

    /** Unknown error. */
    EX86_ERROR_UNKNOWN = 0,

    /** Opcode not found. */
    EX86_ERROR_OP_NOT_FOUND,

    /** Instruction signature does not match. */
    EX86_ERROR_INSTRUCTION_SIGNATURE_MISMATCH,

    /** Syntax error. */
    EX86_ERROR_SYNTAX_ERROR
} ex86_error;

#endif
