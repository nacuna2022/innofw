        .thumb
        .syntax unified
        
        .align
        .section .text, "ax"

        .type __systick, function
        .globl __systick
        .extern arm_systick
__systick:
        push    {lr}
       
        ldr     r1, =__tick
        ldr     r0, [r1, #0]
        add     r0, r0, #1
        str     r0, [r1, #0]
        ldr     r1, =arm_systick
        blx     r1

        pop     {pc}


        .type __pendsv, function
        .globl __pendsv
        .extern sched_task_switch
__pendsv:
        push    {r4-r11, lr}
        
        mov     r0, sp
        ldr     r1, =sched_task_switch
        blx     r1
        mov     sp, r0

        pop     {r4-r11, pc}


        .type arm_exception_entry, function
        .globl arm_exception_entry
arm_exception_entry:
        push    {r0, r3, lr}
        mrs     r0, ipsr
        .extern arm_exception_handler
        ldr     r3, =arm_exception_handler
        blx     r3
        pop     {r0, r3, pc}
        

        .align 4
        .section .data, "aw"
        .globl  __tick
__tick: .long   0x0


