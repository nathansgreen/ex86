#ifndef ISA_DEFS_H_
#define ISA_DEFS_H_

typedef enum ex86_isas {
#ifdef ISA_8086
    EX86_ISA_8086 = 1,
#endif
    EX86_MAX_ISA = 2
} ex86_isas;

#endif
