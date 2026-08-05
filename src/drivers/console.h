#pragma once

#include "uart.h"

typedef struct {
    uart_instance_t* usart;
} console_t;

void console_init (console_t* self, uart_instance_t* usart);

void console_uart_callback (void* context);