#include "console.h"
#include "uart.h"

#include "utils.h"


void console_init (console_t* self, uart_instance_t* usart)
{
    self->usart = usart;

    self->rx_head = 0;
    self->rx_tail = 0;
    self->tx_head = 0;
    self->tx_tail = 0;
}

void console_uart_callback (void* context)
{
    console_t* self = (console_t*) context;

    if (self->usart->events & UART_IRQ_EVENT_RX_AVAIL)
    {
        
        // move bytes here
    }
}