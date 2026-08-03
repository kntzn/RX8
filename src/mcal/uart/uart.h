#pragma once

#include <stdint.h>
#include <stdbool.h>

#include <stm32f303xc.h>

typedef enum
{
    UART_IRQ_EVENT_RX_AVAIL = 1U << 0,
    UART_IRQ_EVENT_TX_READY = 1U << 1,
    UART_IRQ_EVENT_ERROR    = 1U << 2
} uart_irq_event_t;

typedef struct
{
    USART_TypeDef* instance;

    // context

} uart_instance_t;


//typedef USART_TypeDef uart_instance_t;

void uart_init (uart_instance_t* self, USART_TypeDef* uart, uint32_t clock_freq, uint32_t baudrate);

void uart_write_blocking (uart_instance_t* self, uint8_t* buffer, uint32_t len);
void uart_read_blocking  (uart_instance_t* self, uint8_t* buffer, uint32_t len);

uint8_t uart_read_byte  (uart_instance_t* self);
bool uart_ready (uart_instance_t* self);
void uart_write_byte (uart_instance_t* self, uint8_t byte);

uart_irq_event_t uart_irq_handler (USART_TypeDef* stm_uart);