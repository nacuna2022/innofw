#include <board/board.h>
#include <kernel/timer.h>
#include <gd32f4xx.h>
#include <device_core.h>

unsigned long board_cpu_hz(void)
{
        return CONFIG_SYSTEM_CLOCK_VALUE;
}

void early_board_initialize(void)
{
        SystemInit();
        rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
        return;
}

/**
 * for now, just use all the gd32f4xx APIs directly because there is still no 
 * generic driver layer
 */
void initialize_board(void)
{
        /* initialize board periphs */
        /* start our main processing task */
        return;
}

