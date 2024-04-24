#include <device_core.h>
#include <string.h>
#include <stdlib.h>

struct devices_info {
        struct inno_device **devices;
        u32 device_count;
        struct inno_driver **drivers;
        u32 driver_count;
};

extern struct devices_info __devices_info;

#define foreach_device(devpp) \
        for (devpp = __devices_info.devices; \
             devpp < __devices_info.devices + __devices_info.device_count; \
             devpp++)

#define foreach_driver(drvpp) \
        for (drvpp = __devices_info.drivers; \
             drvpp < __devices_info.drivers + __devices_info.driver_count; \
             drvpp++)

static void test(struct inno_device *dev)
{
        return;
}

static void init_device(struct inno_device *dev);
static void exit_device(struct inno_device *dev);
static void suspend_device(struct inno_device *dev);
static void resume_device(struct inno_device *dev);



/* for each device, associate with suitable driver */
void init_device_core(void)
{
        struct inno_device **devpp;
        struct inno_driver **drvpp;
        foreach_device(devpp) {
                struct inno_device *dev = *devpp;
                foreach_driver(drvpp) {
                        struct inno_driver *drv = *drvpp;
                        if (strcmp(dev->compatibility, drv->compatibility) == 0) {
                                dev->driver = drv;
                                init_device(dev);
                                continue;
                        }
                }
        }
        return;
}

void exit_device_core(void)
{
        struct inno_device **devpp;
        foreach_device(devpp) {
                struct inno_device *dev = *devpp;
                exit_device(dev);                                
        }
        return;
}


static void init_device(struct inno_device *dev)
{
        struct inno_driver *driver = dev->driver;
        if (dev->state == device_uninitialized) {
                driver->ops->init(dev);
                dev->state = device_initialized;
        }
        return;
}

static void exit_device(struct inno_device *dev)
{
        struct inno_driver *driver = dev->driver;
        if (dev->state == device_initialized) {
                driver->ops->exit(dev);
                dev->state = device_uninitialized;
        }
        return;
}

static void suspend_device(struct inno_device *dev)
{
        return;
}

static void resume_device(struct inno_device *dev)
{
        return;
}

void *alloc_device_data(struct inno_device *dev, const size_t size)
{
        char *data;
        if ((data = malloc(size)) != NULL) {
                memset(data, 0, size);
                dev->device_data = data;
        }
        return data;
}

void free_device_data(struct inno_device *dev)
{
        free(dev->device_data);
        return;
}

void *device_data(struct inno_device *dev)
{
        return dev->device_data;
}

