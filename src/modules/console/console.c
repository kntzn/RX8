#include <string.h>

#include "console.h"
#include "debug.h"

#include "utils.h"

#include "core/event/event.h"

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

    return ok;
}

bool console_take_line (console_t* self, console_line_t* input_line)
{
    if (self == NULL || input_line == NULL)
        return false;

    if (!self->command_pending)
        return false;

    input_line->line = self->command_line;
    input_line->len = self->cursor;
    
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
                event_raise (EVENT_CONSOLE_LINE_READY, self);
            }
            else
            {
                if (self->cursor < CONSOLE_BUFFER_SIZE-1-1)
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
    // TODO: \t echo should be \t
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