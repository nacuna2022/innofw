#include <arch/timer.h>
#include <board/board.h>
#include <mmio.h>
#include <arm_regs.h>

static system_tick_fn system_tick;
static void *system_tick_arg;

void arm_systick(void)
{
        system_tick(system_tick_arg);
        return;
}

void arch_init_timer(system_tick_fn systick_fn, void *systick_arg, 
                     const unsigned long hz)
{
        reg32_t systick_reload = (board_cpu_hz()/hz)-1;
                
        /* disable systick */
        write32(SYST_CSR, 0);

        system_tick = systick_fn;
        system_tick_arg = systick_arg;
         
        /* set priority of systick and also pendv interrupt 
         * to lowest priority */
        

        /* load the systick counter value  */
        write32(SYST_RVR, systick_reload);

        /* enable systick, set clock source, tick irqen */
        reg32_t csr = 0x7;
        write32(SYST_CSR, csr);
        return;
}

unsigned long arch_get_tick(void)
{
        extern unsigned long __tick[];
        return __tick[0];
}

