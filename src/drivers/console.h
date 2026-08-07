#pragma once

#include "uart.h"

#define CONSOLE_BUFFER_SIZE 256

typedef struct {
    uart_instance_t* usart;

    uint8_t rx_buffer [CONSOLE_BUFFER_SIZE];
    uint16_t rx_head, rx_tail;

    uint8_t tx_buffer [CONSOLE_BUFFER_SIZE];
    uint16_t tx_head, tx_tail;

} console_t;

void console_init (console_t* self, uart_instance_t* usart);

void console_uart_callback (void* context);