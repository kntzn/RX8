#include "event_queue.h"


static uint16_t queue_buffer [EVENT_QUEUE_SIZE];
static event_queue queue = 
{
    .head = 0,
    .tail = 0,
    .buffer=queue_buffer,
    .len=0
    
};

void event_queue_clear ()
{
    queue.head = 0;
    queue.tail = 0;
    queue.len  = 0;
}

uint16_t event_queue_len ()
{
    return queue.len;
}

bool event_queue_push (event_t event)
{
    if (queue.len < EVENT_QUEUE_SIZE)
        

    return false;
}

event_t event_queue_pop ()
{
    return NONE;
}