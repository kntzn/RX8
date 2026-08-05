#include <stddef.h>

#include "irq_manager.h"

#include "uart.h"
#include "utils.h"

typedef uint64_t irq_event_mask;
typedef void (*irq_event_handler)(void *context);

static irq_event_mask event_mask;
static irq_event_handler handlers [IRQ_EVENT_COUNT] = {NULL};

irq_event_mask irq_manager_take_events ();

void irq_manager_init ()
{

}

void irq_manager_raise (irq_event_t event)
{
    event_mask |= (1UL << event);
}

void irq_manager_dispatch ()
{
    irq_event_mask mask = irq_manager_take_events();

    while (mask != IRQ_EVENT_NONE)
    {
        uint32_t popped =  __builtin_ctz(mask);
        mask &= ~(1UL << popped);

        irq_event_handler handler = handlers [popped];
        if (handler != NULL)
        {
            handler ((void*) NULL);
        }
        else
        {
            // TODO: Not Implemented error   
        }
        
    }
}


irq_event_mask irq_manager_take_events ()
{
    irq_event_mask mask;

    IRQ_LOCK
    {
        mask = event_mask;
        event_mask = IRQ_EVENT_NONE;
    }

    return mask;
}