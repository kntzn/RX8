#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#define EVENT_QUEUE_SIZE 32

typedef struct
{
    uint16_t head, tail;
    uint16_t len, max_len_reached;
    uint16_t* buffer;
} event_queue;

typedef enum
{
NONE = 0,
RESERVED1,
RESERVED2,
RESERVED3,

_MAKE_ENUM_16_BIT = 0xFFFF
} event_t;

void     event_queue_clear ();
uint16_t event_queue_len   ();
bool     event_queue_push  (event_t event);
event_t  event_queue_pop   ();
