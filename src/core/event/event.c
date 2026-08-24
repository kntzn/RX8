#include "event.h"

#include "utils.h"

#define EVENT_QUEUE_SIZE 32

static_assert (IS_POWER_OF_2 (EVENT_QUEUE_SIZE));

// ------- Private declarations ------ //
static bool     event_pop (event_t* event);

typedef struct 
{
    event_t event;
    void * context;
} event_record_t;


// --------- Private objects --------- //
//static uint64_t event_mask;


static size_t queue_head = 0, queue_tail = 0;
static event_record_t event_queue [EVENT_QUEUE_SIZE] = {};

static event_handler_t event_handlers[__EVENT_MAX] = { NULL };
static void * event_handler_contexts[__EVENT_MAX] = { NULL };

static void default_handler(const event_t event) 
{
    // TODO: handle failed events
    (void)event;
}

// ------- Public  defenitions ------- //
bool event_register_handler (event_t event, event_handler_t handler, void * context)
{
    if (event >= __EVENT_MAX || 
        handler == NULL || 
        event_handlers [event] != NULL ||
        event_handler_contexts [event] != NULL)
        return false;
    
    event_handlers [event] = handler;
    

    //event_handler_contexts [event] = context;

    return true;
}

void event_raise (event_t event, void * context)
{

    //event_mask |= (1ULL << (uint64_t)event);
}

void event_dispatch (uint16_t count)
{

    /*
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
    } */

}
/*
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
}*/

// ------- Private defenitions ------- //
static bool event_pop (event_t* event)
{
    if (queue_head == queue_tail)
        return false;
    
    queue_head
    //if (!event_mask)
    //    return false;
    
    //event_t popped = __builtin_ctz(event_mask);
    //event_mask &= ~(1ULL << popped);
    //*event = popped;
    
    return true;
}