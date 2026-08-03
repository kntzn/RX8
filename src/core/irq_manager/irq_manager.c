#include "irq_manager.h"

#include "uart.h"

typedef uint64_t irq_event_mask;

static irq_event_mask events;

void irq_manager_raise (irq_event_t event)
{
    events |= event;
}

