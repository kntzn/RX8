#pragma once

#include "uart.h"
#include "ring_buffer.h"

#define CONSOLE_BUFFER_SIZE 256

typedef struct {
    uart_instance_t* usart;

    uint8_t tx_data [CONSOLE_BUFFER_SIZE];
    uint8_t rx_data [CONSOLE_BUFFER_SIZE];
    ring_buffer_t rx_buffer, tx_buffer;

} console_t;

bool console_init (console_t* self, uart_instance_t* usart);

void console_uart_callback (void* context);