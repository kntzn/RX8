#include <stm32f303xc.h>

// #include something to capture hw_events
#include "irq_manager.h"

#include "uart.h"


void USART1_IRQHandler ()
{
    uart_irq_event_t irq_event_mask = uart_irq_handler(USART1);

    if (irq_event_mask & UART_IRQ_EVENT_RX_AVAIL)
        irq_manager_raise(IRQ_EVENT_UART_1_RX_AVAIL);
    if (irq_event_mask & UART_IRQ_EVENT_TX_READY)
        irq_manager_raise(IRQ_EVENT_UART_1_TX_READY);
    if (irq_event_mask & UART_IRQ_EVENT_ERROR)
        irq_manager_raise(IRQ_EVENT_UART_1_ERROR);
}

void USART2_IRQHandler ()
{
    uart_irq_event_t irq_event_mask = uart_irq_handler(USART2);
    
    if (irq_event_mask & UART_IRQ_EVENT_RX_AVAIL)
        irq_manager_raise(IRQ_EVENT_UART_2_RX_AVAIL);
    if (irq_event_mask & UART_IRQ_EVENT_TX_READY)
        irq_manager_raise(IRQ_EVENT_UART_2_TX_READY);
    if (irq_event_mask & UART_IRQ_EVENT_ERROR)
        irq_manager_raise(IRQ_EVENT_UART_2_ERROR);
}

void USART3_IRQHandler ()
{
    uart_irq_event_t irq_event_mask = uart_irq_handler(USART3);

    if (irq_event_mask & UART_IRQ_EVENT_RX_AVAIL)
        irq_manager_raise(IRQ_EVENT_UART_3_RX_AVAIL);
    if (irq_event_mask & UART_IRQ_EVENT_TX_READY)
        irq_manager_raise(IRQ_EVENT_UART_3_TX_READY);
    if (irq_event_mask & UART_IRQ_EVENT_ERROR)
        irq_manager_raise(IRQ_EVENT_UART_3_ERROR);
}

void UART4_IRQHandler ()
{
    uart_irq_event_t irq_event_mask = uart_irq_handler(UART4);

    if (irq_event_mask & UART_IRQ_EVENT_RX_AVAIL)
        irq_manager_raise(IRQ_EVENT_UART_4_RX_AVAIL);
    if (irq_event_mask & UART_IRQ_EVENT_TX_READY)
        irq_manager_raise(IRQ_EVENT_UART_4_TX_READY);
    if (irq_event_mask & UART_IRQ_EVENT_ERROR)
        irq_manager_raise(IRQ_EVENT_UART_4_ERROR);
}

void UART5_IRQHandler ()
{
    uart_irq_event_t irq_event_mask = uart_irq_handler(UART5);

    if (irq_event_mask & UART_IRQ_EVENT_RX_AVAIL)
        irq_manager_raise(IRQ_EVENT_UART_5_RX_AVAIL);
    if (irq_event_mask & UART_IRQ_EVENT_TX_READY)
        irq_manager_raise(IRQ_EVENT_UART_5_TX_READY);
    if (irq_event_mask & UART_IRQ_EVENT_ERROR)
        irq_manager_raise(IRQ_EVENT_UART_5_ERROR);
}
