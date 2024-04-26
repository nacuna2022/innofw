MEMORY
{
        FLASH (rx)      : ORIGIN = 0x08000000, LENGTH = 512K
        SRAM  (rwx)     : ORIGIN = 0x20000000, LENGTH = 128K
}

ENTRY(__arm_reset)

SECTIONS
{
        .text : {
                __vtor = .;
                *(.vector)

                . = ALIGN(256);
                *(.rominfo)
                *(.headers)

                . = ALIGN(8);
                *(.text*)



                __initcall_start = .;
                *(.initcall)
                __initcall_end = .;

                __finicall_start = .;
                *(.finicall)
                __finicall_end = .;

                *(.rodata*)

                KEEP(*(.eh_frame*))

                __devices_info = .;
                LONG(__device_array_start);
                LONG(__driver_array_start);
                LONG(__driver_array_start);
                LONG(__driver_array_end);

                __copy_info = .;
                LONG(__etext);
                LONG(__data_start);
                LONG(__data_end - __data_start);

                __zero_info = .;
                LONG(__bss_start);
                LONG(__bss_end - __bss_start);
        } > FLASH

        .ARM : {
                *(.ARM.exidx*)
                *(.ARM.extab*)
                *(.ARM.preemptmap)
        } > FLASH

        __etext = ALIGN (4);

        .data : AT (__etext) {
                . = ALIGN(8);
                __data_start = .;
                *(.data)
                *(.data*)

                __device_array_start = .;
                *(.devices)
                __driver_array_start = .;
                *(.drivers)
                __driver_array_end = .;

                . = ALIGN(4);
                __data_end = .;
        } > SRAM

        __rom_size = (__etext + SIZEOF(.data)) - ADDR(.text);

        .bss :  {
                . = ALIGN(8);
                __bss_start = .;
                *(.bss)
                *(.bss.*)

                . = ALIGN(4);
                __bss_end = .;
        } > SRAM

        .heap (NOLOAD) : {
                . = ALIGN(8);
                __initial_brk = .;
        } > SRAM

        .stack (ORIGIN(SRAM) + LENGTH(SRAM)) (NOLOAD) : {
                . = ALIGN(8);
               __SP_main = .;
        } > SRAM

        /* newlib libnosys brk() system call */
        end = __initial_brk;
        __entry_point = __arm_reset;
}

