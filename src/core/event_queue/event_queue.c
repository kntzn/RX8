#include "event_queue.h"

// ------- Private declarations ------ //
static void     event_queue_clear ();
static uint16_t event_queue_len   ();
static event_t  event_queue_pop   ();

typedef struct
{
    uint16_t head, tail;
    uint16_t len, max_len_reached;
    uint16_t* buffer;
} event_queue;

// --------- Private objects --------- //
static uint16_t queue_buffer [EVENT_QUEUE_SIZE];
static event_queue queue = 
{
    .head = 0,
    .tail = 0,
    .buffer=queue_buffer,
    .len=0    
};


static void default_handler(event_t event) 
{
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
    if (queue.len < EVENT_QUEUE_SIZE)
        return false;

    return true;
}

void event_queue_dispatch_event (uint16_t count)
{
    if (count == (uint16_t)DEFAULT)
        count = EVENT_QUEUE_DISPATCH_COUNT;
    
    for (int i = 0; i < count; i++)
    {
        event_t event = event_queue_pop ();
        
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
    queue.len  = 0;
}

static uint16_t event_queue_len ()
{
    return queue.len;
}

static event_t event_queue_pop ()
{
    return NONE;
}