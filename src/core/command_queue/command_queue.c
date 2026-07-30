#include "command_queue.h"

// ------- Private declarations ------ //
static bool     event_queue_pop (command_t* event);

typedef struct
{
    volatile uint16_t head, tail;
    uint16_t max_len_reached;
    command_t* buffer;
} command_queue_t;

// --------- Private objects --------- //
static command_t queue_buffer [COMMAND_QUEUE_SIZE];
static command_queue_t queue = 
{
    .head = 0,
    .tail = 0,
    .max_len_reached = 0,
    .buffer=queue_buffer
};


static void default_handler(const command_t event) 
{
    (void)event;
    // TODO: handle failed events
    // TODO: Trace
}

static command_handler_t event_handlers[__COMMAND_MAX] = { };

// ------- Public  defenitions ------- //
bool command_queue_register_command_handler (command_t event, command_handler_t handler)
{
    if (event >= __COMMAND_MAX || 
        handler == NULL || 
        event_handlers [event] != NULL)
        return false;
    
    event_handlers [event] = handler;
    return true;
}

bool command_queue_push (command_t event)
{
    uint16_t next = queue.tail + 1;
    if (next >= COMMAND_QUEUE_SIZE)
        next = 0;
    
    if(next == queue.head)
        return false;

    queue.buffer [next] = event;
    queue.tail = next;

    return true;
}

void command_queue_dispatch (uint16_t count)
{
    for (int i = 0; i < count; i++)
    {
        command_t event;
        if (!event_queue_pop (&event))
            break;
        
        if (event >= __COMMAND_MAX)
        {
            default_handler (event);
            continue;
        }
        
        command_handler_t handler = event_handlers[event];
        if (handler != NULL)
            handler (event);
        else
            default_handler (event);
    }
}

void command_queue_dispatch_default ()
{
    command_queue_dispatch (COMMAND_QUEUE_DISPATCH_EVENT_COUNT);
}

// ------- Private defenitions ------- //
static bool event_queue_pop (command_t* event)
{
    if (queue.head == queue.tail)
        return false;
    
    *event = queue.buffer [queue.head++];
    if (queue.head >= COMMAND_QUEUE_SIZE)
        queue.head = 0;
    
    return true;
}