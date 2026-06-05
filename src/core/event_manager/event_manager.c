#include "event_queue.h"

// ------- Private declarations ------ //
static void     event_queue_clear ();
static bool     event_queue_pop (event_t* event);

typedef struct
{
    volatile uint16_t head, tail;
    uint16_t max_len_reached;
    event_t* buffer;
} event_queue_t;

// --------- Private objects --------- //
static event_t queue_buffer [EVENT_QUEUE_SIZE];
static event_queue_t queue = 
{
    .head = 0,
    .tail = 0,
    .max_len_reached = 0,
    .buffer=queue_buffer
};


static void default_handler(const event_t event) 
{
    // TODO: handle failed events
}

static event_handler_t event_handlers[__EVENT_MAX] = { };

// ------- Public  defenitions ------- //
bool event_queue_register_event_handler (event_t event, event_handler_t handler)
{
    if (event >= __EVENT_MAX || 
        handler == NULL || 
        event_handlers [event] != NULL)
        return false;
    
    event_handlers [event] = handler;
    return true;
}

bool event_queue_push (event_t event)
{
    uint16_t next = queue.tail + 1;
    if (next >= EVENT_QUEUE_SIZE)
        next = 0;
    
    if(next == queue.head)
        return false;

    queue.buffer [next] = event;
    queue.tail = next;

    return true;
}

void event_queue_dispatch (uint16_t count)
{
    for (int i = 0; i < count; i++)
    {
        event_t event;
        if (!event_queue_pop (&event))
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

void event_queue_dispatch_default ()
{
    for (int i = 0; i < EVENT_QUEUE_DISPATCH_EVENT_COUNT; i++)
    {
        event_t event;
        if (!event_queue_pop (&event))
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
static void event_queue_clear ()
{
    queue.head = 0;
    queue.tail = 0;
}

static bool event_queue_pop (event_t* event)
{
    if (queue.head == queue.tail)
        return false;
    
    *event = queue.buffer [queue.head++];
    if (queue.head >= EVENT_QUEUE_SIZE)
        queue.head = 0;
    
    return true;
}