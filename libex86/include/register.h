#ifndef REGISTER_H_
#define REGISTER_H_

#include "types.h"

typedef uint_16t ex86_register_16;
typedef uint_32t ex86_register_32;
typedef uint_64t ex86_register_64;

#if defined(REGISTER_SIZE) && REGISTER_SIZE == 64
    typedef ex86_register_64 ex86_register;
#   define EX86_REGISTER_64(REGISTER) REGISTER
#   define EX86_REGISTER_32(REGISTER) (ex86_register_32)(REGISTER & 0xFFFFFFFF)
#   define EX86_REGISTER_16(REGISTER) (ex86_register_16)(REGISTER & 0xFFFF)
#elif defined(REGISTER_SIZE) && REGISTER_SIZE == 32
    typedef ex86_register_32 ex86_register;
#   define EX86_REGISTER_32(REGISTER) REGISTER
#   define EX86_REGISTER_16(REGISTER) (ex86_register_16)(REGISTER & 0xFFFF)
#elif defined(REGISTER_SIZE) && REGISTER_SIZE == 16
    typedef ex86_register_16 ex86_register;
#   define EX86_REGISTER_16(REGISTER) REGISTER
#else
#   error "REGISTER_SIZE not specified or invalid"
#endif

#endif
