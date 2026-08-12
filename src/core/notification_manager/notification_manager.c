#include <stddef.h>
#include <stdint.h>

#include "notification_manager.h"

#include "utils.h"
#include "debug.h"

#define IRQ_EVENT_COUNT 64
typedef uint64_t irq_event_mask;

static irq_event_mask event_mask = 0;
static notification_callback_t handlers [IRQ_EVENT_COUNT] = {NULL};
static void* handlers_context [IRQ_EVENT_COUNT] = {NULL};
static uint32_t counter = 0;

irq_event_mask notification_manager_take_events ();

notification_id_t notification_manager_register_callback (notification_callback_t callback, void * context)
{
    debug_assert (counter < IRQ_EVENT_COUNT);

    handlers [counter] = callback;
    handlers_context [counter] = context;
    counter++;
    return counter - 1;
}

void notification_manager_raise (notification_id_t id)
{
    event_mask |= (1UL << id);
}

void notification_manager_dispatch ()
{
    irq_event_mask mask = notification_manager_take_events();

    while (mask)
    {
        uint32_t popped =  __builtin_ctz(mask);
        mask &= ~(1UL << popped);

        notification_callback_t handler = handlers [popped];
        if (handler != NULL)
            handler (handlers_context [popped]);
        else
            debug_raise_fault (FAULT_NOT_IMPLEMENTED);
    }
}

irq_event_mask notification_manager_take_events ()
{
    irq_event_mask mask;

    IRQ_LOCK
    {
        mask = event_mask;
        event_mask = 0;
    }

    return mask;
}