#include <arch/irq.h>
#include <arm_irq.h>
#include <arm_ops.h>
#include <arm_regs.h>
#include <mmio.h>
#include <kernel/irq.h>
#include <bug.h>

irqflag_t arch_irq_save(void)
{
        irqflag_t primask;
        __asm__ volatile("mrs   %0, primask\n\t"
                         "cpsid i\n\t"
                         : "=r" (primask)
                         : 
                         : "memory");
        return primask;
}

void arch_irq_restore(const irqflag_t irqflag)
{
        __asm__ volatile("msr   primask, %0"
                         :
                         : "r" (irqflag)
                         : "memory");
        return;
}

void arm_exception_handler(const int exception_n)
{
        handle_irq(exception_n - 16);
        return;
}

static void nvic_init(struct arch_irq_controller *nvic);
static void nvic_config_irq(struct arch_irq_controller *irq_controller,
                           const int irq_number, const enum interrupt_type);
static void nvic_disable_irq(struct arch_irq_controller *irq_controller, 
                            const int irq_number);
static void nvic_enable_irq(struct arch_irq_controller *irq_controller, 
                            const int irq_number);
static void nvic_ack_irq(struct arch_irq_controller *irq_controller, 
                         const int irq_number);

static struct arch_irq_controller armv7m_nvic = {
        .init = nvic_init,
        .disable_irq = nvic_disable_irq,
        .enable_irq = nvic_enable_irq,
        .ack_irq = nvic_ack_irq,
};

void arch_init_controller(void)
{
        register_irq_controller(&armv7m_nvic);
        return;
}

void nvic_set_irq_priority(const int irq_number, const int priority)
{
        addr_t *ipr_ptr = (addr_t *)NVIC_IPR0;
        reg32_t ipr;
        int shift;

        ipr_ptr = ipr_ptr + (irq_number / 4);
        ipr = read32((addr_t)ipr_ptr);
        shift = ((irq_number % 4) * 8);

        /* insert the new IPR for irq_number in its proper field */
        ipr = ipr & ~(0xFF << shift);
        ipr = ipr | (priority << shift);
        write32((addr_t)ipr_ptr, ipr);
        return;
}

void nvic_set_irq_enable(const int irq_number, bool enable)
{
        addr_t *ixer_ptr;
        reg32_t ixer_value;
        int shift;
        int reg_num;

        shift = irq_number % 32;
        reg_num = irq_number / 32;
        if (enable) {
                ixer_ptr = (addr_t *)NVIC_ISER0;
                ixer_ptr = ixer_ptr + reg_num;
                ixer_value = read32((addr_t)ixer_ptr);
                ixer_value |= (1 << shift);
        } else {
                ixer_ptr = (addr_t *)NVIC_ICER0;
                ixer_ptr = ixer_ptr + reg_num;
                ixer_value = read32((addr_t)ixer_ptr);
                ixer_value &= ~(1 << shift);
        }
        write32((addr_t)ixer_ptr, ixer_value);
        return;
}


static void nvic_init(struct arch_irq_controller *nvic)
{
        extern const addr_t __vtor[];
        int irq_number;

        /* configure prioritization policy we will follow 
         * AIRCR.PRIGROUP = 000 so 7 bits for grp prio and 1 bit for subprio
         * we will have a total of 255 priority levels for all interrupts 
         */
        reg32_t aircr;
        aircr = read32(AIRCR) & ~(0xFFFF << 16);
        aircr &= ~(0b111 << 3);
        aircr |= (0x05fa << 16);

        write32(AIRCR, aircr);

        /* set VTOR */
        if (((addr_t)__vtor) & 0x3f) {
                BUG();
        }
        write32(VTOR, (addr_t)__vtor);

        /* disable all interrupts and set to lowest priority */
        for (irq_number = 0;
             irq_number < CONFIG_MCU_INTERRUPT_COUNT;
             irq_number++) {
                nvic_set_irq_enable(irq_number, false);
                nvic_set_irq_priority(irq_number, 255);
        }
        return;
}

static void nvic_disable_irq(struct arch_irq_controller *irq_controller, 
                             const int irq_number)
{
        nvic_set_irq_enable(irq_number, false);
        return;
}

static void nvic_enable_irq(struct arch_irq_controller *irq_controller, 
                            const int irq_number)
{
        nvic_set_irq_enable(irq_number, true);
        return;
}

static void nvic_ack_irq(struct arch_irq_controller *irq_controller, 
                         const int irq_number)
{
        addr_t icpr_reg;
        reg32_t icpr_value;
        int shift;
        int reg_num;
        reg32_t icpr;
        shift = irq_number % 32;
        reg_num = irq_number / 32;

        icpr_reg = (addr_t)(((addr_t *)NVIC_ICPR0) + reg_num);
        icpr = read32(icpr_reg);
        if (icpr & (1 << shift)) {
                write32(icpr_reg, (1 << shift));
        }
        return;
}

