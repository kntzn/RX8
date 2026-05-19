#include <stdint.h>

#define MAX_QUEUE_SIZE 256

typedef enum 
{
EMPTY = 0,
RESERVED1,
RESERVED2,
RESERVED3,
_MAKE_ENUM_8_BIT = 0xFF,
} event_t;

typedef struct 
{
    uint16_t first_id, last_id, len;
    event_t array [MAX_QUEUE_SIZE];
} event_queue;

void evqueue_init (event_queue *queue);
uint8_t evqueue_len (event_queue *queue);
uint8_t evqueue_push (event_queue *queue, event_t event);
event_t evqueue_pop (event_queue *queue);
