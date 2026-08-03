#include <stm32f303xc.h>

// #include something to capture hw_events
#include "irq_manager.h"

#include "uart.h"


void USART1_IRQHandler ()
{
    uart_irq_handler(USART1);
    irq_manager_raise(IRQ_EVENT_UART_1);
}

void USART2_IRQHandler ()
{
    uart_irq_handler(USART2);
    irq_manager_raise(IRQ_EVENT_UART_2);
}

void USART3_IRQHandler ()
{
    uart_irq_handler(USART3);
    irq_manager_raise(IRQ_EVENT_UART_3);
}

void UART4_IRQHandler ()
{
    uart_irq_handler(UART4);
    irq_manager_raise(IRQ_EVENT_UART_4);    
}

void UART5_IRQHandler ()
{
    uart_irq_handler(UART5);
    irq_manager_raise(IRQ_EVENT_UART_5);
}
