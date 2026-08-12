#include <stddef.h>
#include <assert.h>

#include "byte_stream.h"
#include "debug.h"
#include "utils.h"

bool byte_stream_init (byte_stream_t * self, 
                       void* context,
                       byte_stream_read_fn read,
                       byte_stream_write_fn write)
{
    if (!self || !context || !read || !write)
    {
        debug_raise_fault (FAULT_UNEXPECTED_NULL);    
        return false;
    }

    self->context = context;
    self->read_fn = read;
    self->write_fn = write;
    return true;
}

bool byte_stream_read (byte_stream_t * self, uint8_t* byte)
{
    return self->read_fn (self->context, byte);
}
bool byte_stream_write (byte_stream_t * self, uint8_t byte)
{
    return self->write_fn (self->context, byte);
}