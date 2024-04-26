#include <device_core.h>
#include <string.h>
#include <stdlib.h>

struct devices_info {
        struct inno_device *devices;
        struct inno_device *devices_end;
        struct inno_driver *drivers;
        struct inno_driver *drivers_end;
};

extern struct devices_info __devices_info;

#define foreach_device(devp) \
        for (devp = __devices_info.devices; \
             devp < __devices_info.devices_end; \
             devp++)

#define foreach_driver(drvp) \
        for (drvp = __devices_info.drivers; \
             drvp < __devices_info.drivers_end; \
             drvp++)

static void init_device(struct inno_device *dev);
static void shutdown_device(struct inno_device *dev);
static void suspend_device(struct inno_device *dev);
static void resume_device(struct inno_device *dev);

/* for each device, associate with suitable driver */
void init_device_core(void)
{
        struct inno_device *dev;
        struct inno_driver *drv;
        foreach_device(dev) {
                foreach_driver(drv) {
                        if (dev->compatibility == drv->compatibility) {
                                dev->driver = drv;
                                init_device(dev);
                        }
                }
        }
        return;
}

void shutdown_device_core(void)
{
        struct inno_device *dev;
        foreach_device(dev) {
                shutdown_device(dev);                                
        }
        return;
}

static void device_start(struct inno_device *dev)
{
        struct inno_driver *driver = dev->driver;
        if (dev->state == device_initialized) {
                driver->ops->start(dev);
                dev->state = device_running;
        }
        return;
}

static void init_device(struct inno_device *dev)
{
        struct inno_driver *driver = dev->driver;
        if (dev->state == device_uninitialized) {
                if (driver->ops->init(dev) == 0) {
                        dev->state = device_initialized;
                        device_start(dev);
                }
        }
        return;
}

static void shutdown_device(struct inno_device *dev)
{
        struct inno_driver *driver = dev->driver;
        if (dev->state == device_running) {
                dev->state = device_shutdown;
                driver->ops->shutdown(dev);
        }
        return;
}

static void suspend_device(struct inno_device *dev)
{
        struct inno_driver *driver = dev->driver;
        if (dev->state == device_running) {
                driver->ops->suspend(dev);
                dev->state = device_suspended;
        }
        return;
}

static void resume_device(struct inno_device *dev)
{
        struct inno_driver *driver = dev->driver;
        if (dev->state == device_suspended) {
                driver->ops->suspend(dev);
                dev->state = device_running;
        }
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

