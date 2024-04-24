#ifndef __ARM_INCLUDE_ARM_TASK_H__
#define __ATM_INCLUDE_ARM_TASK_H__

struct context_switch_frame {
        addr_t r4;
        addr_t r5;
        addr_t r6;
        addr_t r7;
        addr_t r8;
        addr_t r9;
        addr_t r10;
        addr_t r11;
        addr_t elr;     /* exception link */
        addr_t r0;
        addr_t r1;
        addr_t r2;
        addr_t r3;
        addr_t r12;
        addr_t lr;
        addr_t ret_addr;
        addr_t xpsr;
};

#endif /* __ARM_INCLUDE_ARM_TASK_H__ */

