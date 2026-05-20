#include "evqueue.h"

static event_queue queue;

void evqueue_init(event_queue *queue)
{
    queue->first_id = 0;
    queue->last_id = 0;
    queue->len = 0;
}

uint8_t evqueue_len(event_queue *queue)
{
    return queue->len;
}

uint8_t evqueue_push(event_queue *queue, event_t event)
{
    if (queue->len < MAX_QUEUE_SIZE)
    {
        queue->array [queue->last_id] = event;

        queue->last_id++;
        if (queue->last_id >= MAX_QUEUE_SIZE)
            queue->last_id = 0;

        queue->len++;
        
        return 1;
    }

    return 0;
}

event_t evqueue_pop(event_queue *queue)
{
    if (queue->len > 0)
    {
        uint16_t id_to_pop = queue->first_id;

        queue->first_id++;
        if (queue->first_id >= MAX_QUEUE_SIZE)
            queue->first_id = 0;

        queue->len--;

        return queue->array [id_to_pop];
    }

    return (event_t)EMPTY;
}

#ifdef DEBUG
event_t* evqueue_dump(event_queue *queue)
{
    return (event_t*)queue->array;
}
#endif 