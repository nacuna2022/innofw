#include <refcount.h>
#include <kernel/irq.h>

void init_ref(struct refcount *ref)
{
        ref->count = 1;
        return;
}

void get_ref(struct refcount *ref)
{
        irqflag_t irqflag = enter_critical_section();
        ref->count += 1;
        exit_critical_section(irqflag);
        return;
}

void put_ref(struct refcount *ref, void (*release)(struct refcount *ref))
{
        irqflag_t irqflag = enter_critical_section();
        if (ref->count > 0) {
                ref->count -= 1;
                if (ref->count == 0) {
                        if (release) {
                                release(ref);
                        }
                }
        }
        exit_critical_section(irqflag);
        return;
}

