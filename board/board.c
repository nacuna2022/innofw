#include <board/board.h>
#include <kernel/sched.h>
#include <kernel/timer.h>
#include <kernel/irq.h>
#include <kernel/dpc.h>
#include <device_core.h>

void __no_return start_board(void)
{
        irqflag_t irqflag;

        irqflag = enter_critical_section();

        /* call early board initialization that doesn't rely on 
         * any kernel facilities like task or interrupt management. 
         * this is where the PLLs and system clocks and bus initializations 
         * takes place */
        early_board_initialize();
        
        /* initialize the facilities that 
         * user level code will use
         *
         * timer subsystem
         * scheduler subsystem
         * dpc subsystem
         * interrupt subsystem
         * driver subsystem
         */
        ktimer_init();
        sched_init();
        init_dpc();
        init_interrupt();
        init_device_core();

        initialize_board();
        
        exit_critical_section(irqflag);
        kernel_idle();
}

