#ifndef ERROR_H_
#define ERROR_H_

typedef enum ex86_error {
    EX86_ERROR_UNKNOWN = 0,
    EX86_ERROR_OP_NOT_FOUND,
    EX86_ERROR_INSTRUCTION_SIGNATURE_MISMATCH
} ex86_error;

#endif
