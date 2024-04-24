#ifndef __INCLUDE_DEVICE_H__
#define __INCLUDE_DEVICE_H__
#include <compiler.h>
#include <stddef.h>
#include <types.h>

enum device_state {
        device_uninitialized = 0,
        device_initialized,
        device_suspended,
};

/* devices are statically allocated by the board */
struct inno_driver;
struct inno_device {
        char *name;
        char *compatibility;
        void *parameters;
        void *device_data;
        struct inno_driver *driver;
        enum device_state state;
};
#define create_inno_device(_name, _compat, _params) \
        static struct inno_device static_inno_device_##_name = { \
                .name = #_name, \
                .compatibility = _compat, \
                .parameters = _params, \
                .state = device_uninitialized, \
        }; \
        static const struct inno_device *static_device_ptr_##_name \
        __section(".devices") = &static_inno_device_##_name


/* drivers are statically allocated by the board */
struct driver_ops {
        void (*init)(struct inno_device *dev);
        void (*exit)(struct inno_device *dev);

        void (*suspend)(struct inno_device *dev);
        void (*resume)(struct inno_device *dev);
};

struct inno_driver {
        char *compatibility;
        struct driver_ops *ops;
};
#define inno_driver(compat, driver_ops) \
        static const struct inno_driver static_inno_driver_##compat = { \
                .compatibility = #compat, \
                .ops = &(driver_ops), \
        }; \
        static const struct inno_driver *static_inno_driver_ptr_##compat \
        __section(".drivers") = &static_inno_driver_##compat

void init_device_core(void);
void exit_device_core(void);

/* APIs for manipulating device data */
void *alloc_device_data(struct inno_device *dev, const size_t size);
void free_device_data(struct inno_device *dev);
void *device_data(struct inno_device *dev);

#endif /* __INCLUDE_DEVICE_H__ */

