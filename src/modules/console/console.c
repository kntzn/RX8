#include <string.h>

#include "console.h"
#include "debug.h"

#include "utils.h"

inline bool console_is_special (uint8_t byte);
inline bool console_is_BS (uint8_t byte);
inline bool console_is_CR (uint8_t byte);
const char * console_get_response (uint8_t byte);

bool console_echo (console_t * self, uint8_t byte);

bool console_init (console_t* self, byte_stream_t* stream)
{
    bool ok = true;

    self->stream = stream;

    self->cursor = 0;
    self->command_pending = false;
    self->callback = NULL;
    self->callback_ctx = NULL;
    
    return ok;
}

bool console_bind_command_pending_callback(console_t *self, command_pending_callback_t callback, void *context)
{
    if (self == NULL || callback == NULL || context == NULL)
        return false;

    self->callback = callback;
    self->callback_ctx = context;

    return true;
}

bool console_take_line (console_t* self, uint8_t* line, size_t* len)
{
    if (self == NULL || line == NULL || len == 0)
        return false;

    if (!self->command_pending)
        return false;

    memcpy (line, self->command_line, self->cursor);
    *len = self->cursor;

    self->cursor = 0;
    self->command_pending = false;
    return true;
}

void console_rx_callback (void* context)
{
    console_t* self = (console_t*) context;
    uint8_t incomming_byte;

    // read uart if pending until return found 
    if (!self->command_pending)
    {
        while (byte_stream_read (self->stream, &incomming_byte))
        {
            console_echo (self, incomming_byte);

            if (console_is_BS (incomming_byte))
            {
                if (self->cursor > 0)
                    self->cursor--;
            } 
            else if (console_is_CR (incomming_byte))
            {
                self->command_pending = true;
                if (self->callback != NULL)
                    self->callback (self->callback_ctx);
            }
            else
            {
                if (self->cursor < CONSOLE_BUFFER_SIZE-1)
                    self->command_line [self->cursor++] = incomming_byte;
                else                
                    console_echo (self, '\b');
            }
        }
    }
}

inline bool console_is_special (uint8_t byte)
{
    return byte < 32 || byte == 127;
}
inline bool console_is_BS (uint8_t byte)
{
    return byte == '\b' || byte == 127;
}
inline bool console_is_CR (uint8_t byte)
{
    return byte == '\n' || byte == '\r';
}

bool console_echo (console_t * self, uint8_t byte)
{
    if (console_is_special (byte))
    {
        switch (byte)
        {
        case '\n':
        case '\r':
            if (!byte_stream_write (self->stream, '\n')) // TODO: impement multiple bytes write
                return false;
            if (!byte_stream_write (self->stream, '\r'))
                return false;
            break;

        case '\b':
        case 0x7F:
            // TODO: impement multiple bytes write
            if (!byte_stream_write (self->stream, '\b')) // TODO: impement multiple bytes write
                return false;
            if (!byte_stream_write (self->stream, ' ')) // TODO: impement multiple bytes write
                return false;
            if (!byte_stream_write (self->stream, '\b'))
                return false;
            break;
        default:
            break;
        }
    }
    else
    {
        if (!byte_stream_write (self->stream, byte))
            return false;
    }

    return true;
}