#ifndef __INCLUDE_COMPILER_H__
#define __INCLUDE_COMPILER_H__

#define __section(s)    __attribute__((section(s)))

#define __weak          __attribute__((weak))

#define __used          __attribute__((used))

#define __alias(t)      __attribute__((alias (t)))

#define __align(n)      __attribute__((aligned (n)))

#define __always_inline __attribute__((always_inline))

#define __no_return     __attribute__((noreturn))

#endif /* __INTERNAL_COMPILER_H__ */

