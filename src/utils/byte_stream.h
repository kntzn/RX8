#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef bool (*byte_stream_write_fn)(void * context, uint8_t byte);
typedef bool (*byte_stream_read_fn)(void * context, uint8_t* byte);

typedef struct 
{
    void * context;

    byte_stream_write_fn write_fn;
    byte_stream_read_fn read_fn;

} byte_stream_t;

bool byte_stream_init (byte_stream_t * self, 
                       void* context,
                       byte_stream_read_fn read,
                       byte_stream_write_fn write);

bool byte_stream_read (byte_stream_t * self, uint8_t* byte);
bool byte_stream_write (byte_stream_t * self, uint8_t byte);