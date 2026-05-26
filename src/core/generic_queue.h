#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

typedef struct
{
    uint16_t head, tail, len, capacity;
    size_t element_size;
    uint8_t* buffer;
} generic_queue;

#define DEFINE_GENERIC_STATIC_QUEUE(TYPE, NAME, SIZE) \
static uint8_t NAME##_buffer [SIZE*sizeof(TYPE)];     \
static generic_queue NAME =                           \
{                                                     \
    .buffer = (uint8_t*)NAME##_buffer,                \
    .element_size = sizeof (TYPE),                    \
    .head = 0,                                        \
    .tail = 0,                                        \
    .len = 0,                                         \
    .capacity = SIZE                                  \
};

void     generic_queue_clear (generic_queue *q);
uint16_t generic_queue_len   (generic_queue *q);
bool     generic_queue_push  (generic_queue *q, const void *item);
bool     generic_queue_pop   (generic_queue *q, void *item);
