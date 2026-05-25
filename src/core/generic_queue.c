#include "generic_queue.h"

void generic_queue_clear (generic_queue *q)
{
    q->head = 0;
    q->tail = 0;
    q->len  = 0;
}

uint16_t generic_queue_len (generic_queue *q)
{
    return q->len;
}

bool generic_queue_push (generic_queue *q, const void *item)
{
    // exit on overflow
    if (q->len >= q->capacity)
        return false;
    
    // get new element address
    uint8_t* p_addr = q->buffer + q->element_size*(q->tail);
    // move element
    memcpy (p_addr, (uint8_t*)item, q->element_size);

    // move tail idx
    q->len++;
    q->tail++;
    if (q->tail >= q->capacity)
        q->tail = 0;

    return true;
}

bool generic_queue_pop (generic_queue *q, void *item)
{
    // exit on empty
    if (q->len <= 0)
        return false;
     
    // get new element address
    uint8_t* p_addr = q->buffer + q->element_size*(q->head);
    // move element
    memcpy ((uint8_t*)item, p_addr, q->element_size);

    // move head idx
    q->len--;
    q->head++;
    if (q->head >= q->capacity)
        q->head = 0;

    return true;
}