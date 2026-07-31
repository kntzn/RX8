#include "irq_manager.h"

#include "uart.h"

typedef uint64_t irq_event_mask;



void irq_manager_raise_uart (uart_irq_event_t event)
{
    UART_IRQ_EVENT_TX_READY;
}