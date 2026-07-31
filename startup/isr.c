#include <stm32f303xc.h>

// #include something to capture hw_events
#include "irq_manager.h"

#include "uart.h"


void USART1_IRQHandler ()
{
    uart_irq_event_t irq_event_mask = uart_irq_handler(USART1);
}

void USART2_IRQHandler ()
{
    uart_irq_event_t irq_event_mask = uart_irq_handler(USART2);
}

void USART3_IRQHandler ()
{
    uart_irq_event_t irq_event_mask = uart_irq_handler(USART3);
}

void UART4_IRQHandler ()
{
    uart_irq_event_t irq_event_mask = uart_irq_handler(UART4);
}

void UART5_IRQHandler ()
{
    uart_irq_event_t irq_event_mask = uart_irq_handler(UART5);
}
