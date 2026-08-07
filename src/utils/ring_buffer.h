#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct 
{
    uint8_t* data;

    size_t head, tail;
    size_t capacity;

} ring_buffer_t;

bool ring_buffer_init (ring_buffer_t * self, uint8_t * data, size_t len);

bool ring_buffer_push (ring_buffer_t * self, uint8_t byte);
bool ring_buffer_pop  (ring_buffer_t * self, uint8_t * byte);