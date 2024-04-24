#ifndef __INCLUDE_ARCH_IRQ_H__
#define __INCLUDE_ARCH_IRQ_H__
#include <types.h>

irqflag_t arch_irq_save(void);
void arch_irq_restore(const irqflag_t irqflag);

enum interrupt_type {
        level_triggered = 0,
        edge_triggered,
};

/* we model a simple irq controller where all interrupts are same priority
 * and we can only enable or disable interrupts - no more no less.
 */
struct arch_irq_controller {
        void (*init)(struct arch_irq_controller *irq_controller);
        void (*config_irq)(struct arch_irq_controller *irq_controller,
                           const int irq_number, const enum interrupt_type type);
        void (*disable_irq)(struct arch_irq_controller *irq_controller, 
                            const int irq_number);
        void (*enable_irq)(struct arch_irq_controller *irq_controller,
                           const int irq_number);
        void (*ack_irq)(struct arch_irq_controller *irq_controller,
                        const int irq_number);
        void *private_data;
};

void arch_init_controller(void);

#endif /* __INCLUDE_ARCH_IRQ_H__ */

