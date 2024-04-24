#ifndef __ARMV7M_INCLUDE_ARM_IRQ_H__
#define __ARMV7M_INCLUDE_ARM_IRQ_H__
#include <kernel/irq.h>
#include <stdbool.h>

void nvic_set_irq_priority(const int irq_number, const int priority);
void nvic_set_irq_enable(const int irq_number, bool enable);

#endif /* __ARMV7_INCLUDE_ARM_IRQ_H__ */

