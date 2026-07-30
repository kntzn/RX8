#include "event.h"

// ------- Private declarations ------ //
static bool     event_pop (event_t* event);

// --------- Private objects --------- //
static uint64_t event_mask;

static void default_handler(const event_t event) 
{
    // TODO: handle failed events
    (void)event;
}

static event_handler_t event_handlers[__EVENT_MAX] = { };

// ------- Public  defenitions ------- //
bool event_register_event_handler (event_t event, event_handler_t handler)
{
    if (event >= __EVENT_MAX || 
        handler == NULL || 
        event_handlers [event] != NULL)
        return false;
    
    event_handlers [event] = handler;
    return true;
}

void event_push (event_t event)
{
    event_mask |= (1ULL << (uint64_t)event);
}

void event_dispatch (uint16_t count)
{
    for (int i = 0; i < count; i++)
    {
        event_t event;
        if (!event_pop (&event))
            break;
        
        if (event >= __EVENT_MAX)
        {
            default_handler (event);
            continue;
        }
        
        event_handler_t handler = event_handlers[event];
        if (handler != NULL)
            handler (event);
        else
            default_handler (event);
    }
}

void event_dispatch_default ()
{
    for (int i = 0; i < EVENT_DISPATCH_EVENT_COUNT; i++)
    {
        event_t event;
        if (!event_pop (&event))
            break;
        
        if (event >= __EVENT_MAX)
        {
            default_handler (event);
            continue;
        }
        
        event_handler_t handler = event_handlers[event];
        if (handler != NULL)
            handler (event);
        else
            default_handler (event);
    }
}

// ------- Private defenitions ------- //
static bool event_pop (event_t* event)
{
    if (!event_mask)
        return false;
    
    event_t popped = __builtin_ctz(event_mask);
    event_mask &= ~(1ULL << popped);
    *event = popped;
    
    return true;
}