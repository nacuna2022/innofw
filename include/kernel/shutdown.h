#ifndef __INCLUDE_KERNEL_SHUTDOWN_H__
#define __INCLUDE_KERNEL_SHUTDOWN_H__

enum shutdown_action {
        shutdown_poweroff = 0,
        shutdown_restart,
};

enum shutdown_reason {
        shutdown_reason_secret = 0,     /* dont bother giving a reason */
        shutdown_reason_sw_request,     /* due to user request */
        shutdown_reason_sw_update,      /* due to software update */
        shutdown_reason_gross_error,    /* due to unrecoverable error */
        shutdown_reason_wd_timeout,     /* due to watchdog timeout */
        shutdown_reason_overheat,       /* due to overheating */
        shutdown_reason_low_power,      /* due to power loss/brownout */
};

typedef void(*shutdown_callback)(void *arg, const enum shutdown_reason);

void register_shutdown_hook(shutdown_callback fn, void *arg);

void shutdown(enum shutdown_reason reason, enum shutdown_action action);

#endif /* __INCLUDE_KERNEL_SHUTDOWN_H__ */

