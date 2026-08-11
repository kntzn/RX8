#pragma once

#include "uart.h"

#define CONSOLE_BUFFER_SIZE 64

typedef struct {
    uart_instance_t* usart;

    uint8_t command_line [CONSOLE_BUFFER_SIZE];
    size_t cursor;

    bool command_pending;

} console_t;

bool console_init (console_t* self, uart_instance_t* usart);

void console_uart_callback (void* context);