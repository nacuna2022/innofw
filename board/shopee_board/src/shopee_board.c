#include <board/board.h>
#include <kernel/timer.h>
#include <gd32f4xx.h>
#include <device_core.h>

unsigned long board_cpu_hz(void)
{
        return CONFIG_SYSTEM_CLOCK_VALUE;
}

void early_board_initialize(void)
{
        SystemInit();
        rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
        return;
}

/**
 * for now, just use all the gd32f4xx APIs directly because there is still no 
 * generic driver layer
 */
void initialize_board(void)
{
        /* initialize board periphs */
        /* start our main processing task */
        return;
}


/** sample innofw device declaration *****************************************/

struct dummy_parameters {
        uint32_t signature1;
        uint32_t signature2;
} dummy_parameters = {
        .signature1 = 0xfafa,
        .signature2 = 0xdede,
};

create_inno_device(dummy, "dummy", &dummy_parameters);
create_inno_device(dummy2, "dummy", &dummy_parameters);



/** sample innofw driver declaration *****************************************/

static int my_dummy_init(struct inno_device *dev);
static void my_dummy_start(struct inno_device *dev);
static void my_dummy_shutdown(struct inno_device *dev);
static void my_dummy_suspend(struct inno_device *dev);
static void my_dummy_resume(struct inno_device *dev);
static void my_dummy_read(struct inno_device *dev);
static void my_dummy_write(struct inno_device *dev);

struct dummy_driver_ops {
        void (*dummy_read)(struct inno_device *dev);
        void (*dummy_write)(struct inno_device *dev);
        struct driver_ops base;
} dummy_driver_ops = {
        .dummy_read = my_dummy_read,
        .dummy_write = my_dummy_write,
        .base = {
                .init = my_dummy_init,
                .start = my_dummy_start,
                .shutdown = my_dummy_shutdown,
                .suspend = my_dummy_suspend,
                .resume = my_dummy_resume,
        }
};
inno_driver(dummy, &dummy_driver_ops.base);

static int my_dummy_init(struct inno_device *dev)
{
        return 0;
}

static void my_dummy_start(struct inno_device *dev)
{
        return;
}

static void my_dummy_shutdown(struct inno_device *dev)
{
        return ;
}

static void my_dummy_suspend(struct inno_device *dev)
{
        return;
}

static void my_dummy_resume(struct inno_device *dev)
{
        return;
}

static void my_dummy_read(struct inno_device *dev)
{
        return;
}

static void my_dummy_write(struct inno_device *dev)
{
        return;
}
