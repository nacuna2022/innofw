#ifndef __INCLUDE_KERNEL_H__
#define __INCLUDE_KERNEL_H__

#define ct_assert(cond) \
        do { \
                int __assert_array[(-1 + !!(cond))]; \
        } while(0)


#endif /* __INCLUDE_KERNEL_H__ */

