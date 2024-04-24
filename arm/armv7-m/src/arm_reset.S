#include <compiler.h>
#define __ASSEMBLY__

        .thumb
        .syntax unified
        .globl __arm_reset
        .extern start_board
        .extern __etext

        .align
        .section .text, "ax"
__arm_reset:
        # copy data
        ldr     r5, =__copy_info
        ldr     r0, [r5, #0]
        ldr     r1, [r5, #4]
        ldr     r2, [r5, #8]
        mov     r3, #0
1:      cmp     r3, r2
        beq     1f
        
        ldr     r4, [r0, r3]
        str     r4, [r1, r3]
        add     r3, r3, #4
        b       1b
1:

        # zero bss 
        ldr     r5, =__zero_info
        ldr     r0, [r5, #0]
        ldr     r1, [r5, #4]
        mov     r2, #0
        mov     r3, #0
2:      cmp     r3, r1
        beq     2f
        str     r2, [r0, r3]
        add     r3, r3, #4
        b       2b
2:
        # initialize libc? 
        # we dont use init/fini so no. ... for now. 

        bl      start_board
        b       .

