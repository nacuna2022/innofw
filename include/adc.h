#ifndef __INCLUDE_ADC_H__
#define __INCLUDE_ADC_H__
#include <device_core.h>
#include <config.h>
#include <list.h>
#include <kernel/timer.h>

enum adc_resolution {
        adc_resolution_unkown = 0,
        adc_resolution_8b,
        adc_resolution_10b,
        adc_resolution_12b,
        adc_resolution_16b,
        adc_resolution_24b,
        adc_resolution_32b,
};

struct adc_ops {
        struct driver_ops base;
        unsigned long (*vref)(struct inno_device *dev);
};

enum adc_averaging {
        adc_averaging_none = 0,
        adc_averaging_simple_moving_average,
        adc_averaging_exponential_moving_average,
};

struct adc_averaging_algo {
        void (*init)(struct inno_device *dev);
        void (*update)(struct inno_device *dev, const unsigned long value);
        unsigned long (*read)(struct inno_device *dev);
        void (*exit)(struct inno_device *dev);
};

/* right now this is the only adc data we keep per device.
 * each averaging is the one responsible for allocating this and storing 
 * a reference to inno_device->driver_data field. */
struct adc_device_data {
        enum adc_averaging adc_avg;
        struct ktimer *ktimer;
        unsigned char avg_data[] __align(8);
};

/* driver init code should call adc_init()/adc_exit() 
 * in their init/exit routines */
void adc_init(struct inno_device *dev, enum adc_averaging avg_algo);
void adc_exit(struct inno_device *dev);

/* driver code should call adc_avg_update() routinely to pass its raw adc value
 * to the system averaging algorithm */
void adc_avg_update(struct inno_device *dev, const unsigned long value);

unsigned long adc_avg_read(struct inno_device *dev);

static inline unsigned long adc_vref(struct inno_device *dev)
{
        struct adc_ops *ops = container_of(dev->driver->ops, struct adc_ops, base);
        return ops->vref(dev);
}

static inline void adc_read(struct inno_device *dev)
{
        adc_avg_read(dev);
        return;
}
#endif /* __INCLUDE_ADC_H__ */

