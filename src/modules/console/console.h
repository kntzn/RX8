#pragma once

#include "byte_stream.h"

#define CONSOLE_BUFFER_SIZE 64

typedef void (*command_pending_callback_t)(void * context);

typedef struct {
    byte_stream_t* stream;

    uint8_t command_line [CONSOLE_BUFFER_SIZE];
    size_t cursor;

    bool command_pending;
    command_pending_callback_t callback;
    void * callback_ctx;

} console_t;

bool console_init (console_t* self, byte_stream_t* stream);

bool console_bind_command_pending_callback (console_t* self, command_pending_callback_t callback, void* context);

bool console_take_line (console_t* self, uint8_t* line, size_t* len);

void console_rx_callback (void* context);