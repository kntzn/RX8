#include "event.h"

#include "debug/debug.h"
#include "utils.h"

#define EVENT_QUEUE_SIZE 32

// ------- Private declarations ------ //
static bool     event_pop (event_record_t* event);


// --------- Private objects --------- //
typedef struct 
{
    event_t event;
    void * context;
} event_record_t;

static size_t queue_head = 0, queue_tail = 0;
static event_record_t event_queue [EVENT_QUEUE_SIZE] = {};

static event_handler_t event_handlers[__EVENT_MAX] = { NULL };

static void default_handler(const event_t event) 
{
    debug_raise_fault (FAULT_NOT_IMPLEMENTED);
    // TODO: handle failed events
    (void)event;
}

// ------- Public  defenitions ------- //
bool event_register_handler (event_t event, event_handler_t handler)
{
    static_assert (IS_POWER_OF_2 (EVENT_QUEUE_SIZE));

    if (event >= __EVENT_MAX || 
        handler == NULL || 
        event_handlers [event] != NULL)
        return false;
    
    event_handlers [event] = handler;
    
    return true;
}

bool event_raise (event_t event, void * context)
{
    event_record_t raised;
    raised.event = event;
    raised.context = context;

    size_t next_tail = (queue_tail + 1) & (EVENT_QUEUE_SIZE - 1);
    if (next_tail == queue_head)
        return false;

    event_queue [next_tail] = raised;
    queue_tail = next_tail;

    return true;
}

void event_dispatch (uint16_t count)
{
    for (int i = 0; i < count; i++)
    {
        event_record_t record;
        if (!event_pop (&record))
            break;
        
        if (record.event >= __EVENT_MAX)
        {
            default_handler (record.event);
            continue;
        }
        
        event_handler_t handler = event_handlers[record.event];
        if (handler != NULL)
            handler (record.event, record.context);
        else
            default_handler (record.event);
    }
}

// ------- Private defenitions ------- //
static bool event_pop (event_record_t* event)
{
    if (queue_head == queue_tail)
        return false;
    
    *event = event_queue [queue_head];
    queue_head = (queue_head + 1) & (EVENT_QUEUE_SIZE - 1);

    return true;
}