#include <stddef.h>
#include <assert.h>

#include "ring_buffer.h"
#include "debug.h"
#include "utils.h"

bool ring_buffer_init (ring_buffer_t * self, uint8_t * data, size_t len)
{
    debug_assert (IS_POWER_OF_2 (len));

    if (self == NULL)
        return false;
    
    self->data = data;

    self->head = 0;
    self->tail = 0;
    self->capacity = len;

    return true;
}

bool ring_buffer_push (ring_buffer_t * self, uint8_t byte)
{
    size_t next_tail = (self->tail+1)&(self->capacity - 1);

    if (next_tail == self->head)
        return false;

    self->data [self->tail] = byte;
    self->tail = next_tail;

    return true;
}
bool ring_buffer_pop  (ring_buffer_t * self, uint8_t * byte)
{
    if (self->head == self->tail)
        return false;

    *byte = self->data [self->head];
    self->head = (self->head+1)&(self->capacity - 1);

    return true;
}