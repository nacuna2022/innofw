#include <config.h>
#include <kernel/irq.h>
#include <arch/irq.h>
#include <bug.h>

#include <string.h>

static struct arch_irq_controller *irq_controller;
static struct irq_handler_entry irq_table[CONFIG_MCU_INTERRUPT_COUNT];

static void init_irq_controller(struct arch_irq_controller *irq_cntl)
{
        return;
}

void init_interrupt(void)
{
        irq_controller = NULL;

        /* initialize our interrupt vector table */
        memset(irq_table, 0, sizeof irq_table);

        /* call on the arch layer code so it can register its 
         * interrupt controller */
        arch_init_controller();
        return;
}

void register_irq_controller(struct arch_irq_controller *controller)
{
        irq_controller = controller;
        if (controller->init) {
                controller->init(controller);
        }
        return;
}

static void ack_irq(const int irq_number)
{
        if (irq_controller->ack_irq) {
                irq_controller->ack_irq(irq_controller, irq_number);
        }
        return;
}

void handle_irq(const int irq_number)
{
        BUG_ON(irq_number > (CONFIG_MCU_INTERRUPT_COUNT-1));
        if (irq_table[irq_number].handler) {
                irq_table[irq_number].handler(irq_table[irq_number].arg);
                ack_irq(irq_number);
        }
        return;
}

void register_irq(const int irq_number, irq_handler handler, 
                  void *handler_arg, const enum interrupt_type irq_type)
{
        BUG_ON(irq_number > (CONFIG_MCU_INTERRUPT_COUNT-1));
        irq_table[irq_number].handler = handler;
        irq_table[irq_number].arg = handler_arg;
        return;
}

void enable_irq(const int irq_number)
{
        BUG_ON(irq_number > (CONFIG_MCU_INTERRUPT_COUNT-1));
        if (irq_controller->enable_irq) {
                irq_controller->enable_irq(irq_controller, irq_number);
        }
        return;
}

void disable_irq(const int irq_number)
{
        BUG_ON(irq_number > (CONFIG_MCU_INTERRUPT_COUNT-1));
        if (irq_controller->disable_irq) {
                irq_controller->disable_irq(irq_controller, irq_number);
        }
        return;
}

