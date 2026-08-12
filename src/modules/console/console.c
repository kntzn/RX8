#include <string.h>

#include "console.h"
#include "uart.h"
#include "debug.h"

#include "utils.h"

inline bool console_is_special (uint8_t byte);
inline bool console_is_BS (uint8_t byte);
inline bool console_is_CR (uint8_t byte);
const char * console_get_response (uint8_t byte);

bool console_echo (console_t * self, uint8_t byte);

bool console_init (console_t* self, uart_instance_t* usart)
{
    bool ok = true;

    self->usart = usart;

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

void console_uart_callback (void* context)
{
    console_t* self = (console_t*) context;
    uint8_t incomming_byte;

    // read uart if pending until return found 
    if (self->usart->events & UART_IRQ_EVENT_RX_AVAIL && !self->command_pending)
    {
        while (uart_read_async (self->usart, &incomming_byte))
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
            if (!uart_write_bytes_async (self->usart, (uint8_t *)"\n\r", 2))
                return false;
            break;

        case '\b':
        case 0x7F:
            if (!uart_write_bytes_async (self->usart, (uint8_t *)"\b \b", 3))
                return false;
            break;
        default:
            break;
        }
    }
    else
    {
        if (!uart_write_async (self->usart, byte))
            return false;
    }

    return true;
}