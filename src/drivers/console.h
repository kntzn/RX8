#pragma once

#include "uart.h"

#define CONSOLE_BUFFER_SIZE 64

typedef void (*command_pending_callback_t)(void * context);

typedef struct {
    uart_instance_t* usart;

    uint8_t command_line [CONSOLE_BUFFER_SIZE];
    size_t cursor;

    bool command_pending;
    command_pending_callback_t callback;
    void * callback_ctx;

} console_t;

bool console_init (console_t* self, uart_instance_t* usart);

bool console_bind_command_pending_callback (console_t* self, command_pending_callback_t callback, void* context);

bool console_take_line (console_t* self, uint8_t** line, size_t len);

void console_uart_callback (void* context);