#pragma once

#include <stdint.h>
#include <stdbool.h>

#include <stm32f303xc.h>

#define UART_BUFFER_SIZE 64

typedef enum
{
    UART_IRQ_EVENT_NONE = 0,
    UART_IRQ_EVENT_RX_AVAIL = 1U << 0,
    UART_IRQ_EVENT_TX_READY = 1U << 1,
    UART_IRQ_EVENT_ERROR    = 1U << 2
} uart_irq_event_t;

typedef struct
{
    USART_TypeDef* instance;

    uart_irq_event_t events;
    // context (buffers etc)

    // TODO:
    uint8_t rx_buffer [UART_BUFFER_SIZE];
    uint16_t rx_head, rx_tail;
    
    uint8_t tx_buffer [UART_BUFFER_SIZE];
    uint16_t tx_head, tx_tail;

    // counter rx / tx
    // irq_mode_rx None/IRQ/DMA
    // irq_mode_tx None/IRQ/DMA

} uart_instance_t;


/**
 * @brief Init function
 * @details Initializes USART, updates instance table, configures baud and interrupts
 * 
 * @param self - instance to be inited
 * @param uart - stm USART_TypeDef object
 * @param clock_freq - system clock frequency
 */
bool uart_init (uart_instance_t* self, USART_TypeDef* uart, uint32_t clock_freq, uint32_t baudrate);

// Buffer blocking functions
void uart_write_blocking (uart_instance_t* self, uint8_t* buffer, uint32_t len);
void uart_read_blocking  (uart_instance_t* self, uint8_t* buffer, uint32_t len);

// Single-byte functions
uint8_t uart_read_byte  (uart_instance_t* self);
bool uart_ready (uart_instance_t* self);
void uart_write_byte (uart_instance_t* self, uint8_t byte);

/**
 * @brief common irq handler for all u(s)arts
 * @brief captures events by interrupt flags and saves values to buffers
 */
bool uart_irq_handler (USART_TypeDef* stm_uart);

uart_irq_event_t uart_take_events (uart_instance_t* self);