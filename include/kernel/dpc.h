#ifndef __INCLUDE_DPC_H__
#define __INCLUDE_DPC_H__
#include <list.h>

typedef void (*dpc_fn)(void *dpc_arg);

struct dpc {
        dpc_fn fn;
        void *arg;
        struct list_head node;
};

void init_dpc(void);
void queue_dpc(dpc_fn fn, void *arg);

#endif /* __INCLUDE_DPC_H__ */

