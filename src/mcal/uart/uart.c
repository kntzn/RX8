#include <uart.h>

#include "stm32f303xc.h"

void uart_init (uart_instance_t* uart, uint32_t clock_freq, uint32_t baudrate)
{
    uart->CR1 &= ~USART_CR1_UE;

    uart->CR1 = 0;
    uart->CR2 = 0;
    uart->CR3 = 0;

    uart->BRR = (clock_freq + baudrate/2U)/baudrate;

    uart->CR1 |= USART_CR1_TE | USART_CR1_RE;

    uart->CR1 |= USART_CR1_UE;
}

void uart_write_blocking (uart_instance_t* uart, uint8_t* buffer, uint32_t len)
{
    for (uint32_t i = 0; i < len; i++)
    {
        // Wait for TDR to be ready to receive data
        while (!(uart->ISR & USART_ISR_TXE));

        // Write byte to TX
        uart->TDR = buffer[i];
    }

    // Wait for end of transaction
    while (!(uart->ISR & USART_ISR_TC));
}

void uart_read_blocking  (uart_instance_t* uart, uint8_t* buffer, uint32_t len)
{
    for (uint32_t i = 0; i < len; i++)
    {
        // Wait for TDR to be ready to receive data
        while (!(uart->ISR & USART_ISR_RXNE));

        // Write byte to TX
        buffer[i] = (uint8_t)uart->RDR;
    }

}