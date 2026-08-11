#include <string.h>

#include "console.h"
#include "uart.h"
#include "debug.h"

#include "utils.h"

inline bool console_is_special (uint8_t byte);
const char * console_get_response (uint8_t byte);

bool console_init (console_t* self, uart_instance_t* usart)
{
    bool ok = true;

    self->usart = usart;

    ok = ok && ring_buffer_init (&self->rx_buffer, self->rx_data, CONSOLE_BUFFER_SIZE);
    ok = ok && ring_buffer_init (&self->tx_buffer, self->tx_data, CONSOLE_BUFFER_SIZE);

    return ok;
}

void console_uart_callback (void* context)
{
    console_t* self = (console_t*) context;
    uint8_t incomming_byte;

    if (self->usart->events & UART_IRQ_EVENT_RX_AVAIL)
    {
        while (uart_read_async (self->usart, &incomming_byte))
        {
            if (console_is_special (incomming_byte))
            {
                const char * resp_p = console_get_response (incomming_byte);
                
                uart_write_bytes_async (self->usart, (uint8_t *) resp_p, strlen (resp_p));
            }
            else
            {
                uart_write_async (self->usart, incomming_byte);
                // response = incomming_byte;


                if (!ring_buffer_push (&self->rx_buffer, incomming_byte))
                {
                    debug_raise_fault (FAULT_OUT_OF_SPACE);
                    break;
                }
            }
        }
    }
}

inline bool console_is_special (uint8_t byte)
{
    return byte < 32 || byte == 127;
}

const char * console_get_response (uint8_t byte)
{


    switch (byte)
    {
        case '\r':
        case '\n':
        {
            
            return "\n";
            break;
        }
            
        case '\b':
        case 0x7F:
        {   
            return "\b \b";
            break;
        }
        default:
        {
            
            return NULL;
            break;
        }
    }
    

} 