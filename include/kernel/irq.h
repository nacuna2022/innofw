#ifndef __INCLUDE_KERNEL_IRQ_H__
#define __INCLUDE_KERNEL_IRQ_H__
#include <compiler.h>
#include <arch/irq.h>

#define enter_critical_section()        arch_irq_save()
#define exit_critical_section(flag)     arch_irq_restore(flag)

typedef void (*irq_handler)(void *arg);

struct arch_irq_controller;
struct irq_handler_entry {
        irq_handler handler;
        void *arg;
};

void register_irq_controller(struct arch_irq_controller *irq_controller);

void init_interrupt(void);
void register_irq(const int irq_number, irq_handler handler, 
                  void *handler_arg, const enum interrupt_type);
void enable_irq(const int irq_number);
void disable_irq(const int irq_number);

/* call this inside the lowlevel handler to pass interrupt handling to the 
 * kernel */
void handle_irq(const int irq_number);

#endif /* __INCLUDE_KERNEL_IRQ_H__ */

