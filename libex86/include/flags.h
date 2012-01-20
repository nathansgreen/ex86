#ifndef FLAGS_H_
#define FLAGS_H_

typedef int ex86_flags;

/// Carry flag.
#define EX86_FLAGS_CF(FLAGS)        (FLAGS & 0x0001) // 0

/// Reserved.
#define EX86_FLAGS_1F(FLAGS) 1 //   (FLAGS & 0x0002) // 1

/// Parity flag.
#define EX86_FLAGS_PF(FLAGS)        (FLAGS & 0x0004) // 2

/// Reserved.
#define EX86_FLAGS_3F(FLAGS) 0 //   (FLAGS & 0x0008) // 3

/// Adjust flag.
#define EX86_FLAGS_AF(FLAGS)        (FLAGS & 0x0010) // 4

/// Reserved.
#define EX86_FLAGS_5F(FLAGS) 0 //   (FLAGS & 0x0020) // 5

/// Zero flag.
#define EX86_FLAGS_ZF(FLAGS)        (FLAGS & 0x0040) // 6

/// Sign flag.
#define EX86_FLAGS_SF(FLAGS)        (FLAGS & 0x0080) // 7

/// Trap flag.
#define EX86_FLAGS_TF(FLAGS)        (FLAGS & 0x0100) // 8

/// Interrupt enable flag.
#define EX86_FLAGS_IF(FLAGS)        (FLAGS & 0x0200) // 9

/// Direction flag.
#define EX86_FLAGS_DF(FLAGS)        (FLAGS & 0x0400) // 10

/// Overflow flag.
#define EX86_FLAGS_OF(FLAGS)        (FLAGS & 0x0800) // 11

/// I/O privilege level (lo bit).
#define EX86_FLAGS_IOPL_LO(FLAGS)   (FLAGS & 0x1000) // 12

/// I/O privilege level (hi bit).
#define EX86_FLAGS_IOPL_HI(FLAGS)   (FLAGS & 0x2000) // 13

/// Nested task flag.
#define EX86_FLAGS_NT(FLAGS)        (FLAGS & 0x4000) // 14

#endif
