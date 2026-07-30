#include <uart.h>

#include "stm32f303xc.h"

void uart_init (uart_instance_t* self, USART_TypeDef* uart, uint32_t clock_freq, uint32_t baudrate)
{
    self->instance = uart;

    self->instance->CR1 &= ~USART_CR1_UE;

    self->instance->CR1 = 0;
    self->instance->CR2 = 0;
    self->instance->CR3 = 0;

    self->instance->BRR = (clock_freq + baudrate/2U)/baudrate;

    self->instance->CR1 |= USART_CR1_TE | USART_CR1_RE;

    self->instance->CR1 |= USART_CR1_UE;
}

void uart_write_blocking (uart_instance_t* self, uint8_t* buffer, uint32_t len)
{
    for (uint32_t i = 0; i < len; i++)
    {
        // Wait for TDR to be ready to receive data
        while (!(self->instance->ISR & USART_ISR_TXE));

        // Write byte to TX
        self->instance->TDR = buffer[i];
    }

    // Wait for end of transaction
    while (!(self->instance->ISR & USART_ISR_TC));
}

void uart_read_blocking  (uart_instance_t* self, uint8_t* buffer, uint32_t len)
{
    for (uint32_t i = 0; i < len; i++)
    {
        while (!(self->instance->ISR & USART_ISR_RXNE));

        buffer[i] = (uint8_t)self->instance->RDR;
    }

}

uint8_t uart_read_byte  (uart_instance_t* self)
{
    return (uint8_t)self->instance->RDR;
}

bool uart_ready (uart_instance_t* self)
{
    return (bool)(self->instance->ISR & USART_ISR_RXNE);
}

void uart_write_byte (uart_instance_t* self, uint8_t byte)
{
    // Wait for TDR to be ready to receive data
    while (!(self->instance->ISR & USART_ISR_TXE));

    // Write byte to TX
    self->instance->TDR = byte;
 
    // Wait for end of transaction
    while (!(self->instance->ISR & USART_ISR_TC));
}

void uart_irq_handler (USART_TypeDef* stm_uart)
{
    // For now!!! // TODO: uart_instance_t getInstance (USART_TypeDef* self){}
    uart_instance_t* uart = (uart_instance_t*)stm_uart;

    if ((uart->instance->ISR & USART_ISR_RXNE) != 0u) 
    {
        uint8_t byte = (uint8_t)uart->instance->RDR;
        //uart_rx_push_isr(uart, byte);
    (void)byte;
    }

    if (((uart->instance->ISR & USART_ISR_TXE) != 0u) &&
        ((uart->instance->CR1 & USART_CR1_TXEIE) != 0u)) 
        {
        //uart_tx_process_isr(uart);
        }

    // if ((uart->instance->ISR & USART_ISR_ORE) != 0u) 
        // {
        // uart->instance->ICR = USART_ICR_ORECF;
        // }
}

void USART1_IRQHandler ()
{
    uart_irq_handler(USART1);
}

void USART2_IRQHandler ()
{
    uart_irq_handler(USART2);
}

void USART3_IRQHandler ()
{
    uart_irq_handler(USART3);
}

void UART4_IRQHandler ()
{
    uart_irq_handler(UART4);
}
void UART5_IRQHandler ()
{
    uart_irq_handler(UART5);
}
