#pragma once

#include "byte_stream.h"

#define CONSOLE_BUFFER_SIZE 64

typedef void (*command_pending_callback_t)(void * context);

typedef struct 
{
    uint8_t * line;
    size_t len;
} console_line_t;

typedef struct {
    byte_stream_t* stream;

    uint8_t command_line [CONSOLE_BUFFER_SIZE];
    size_t cursor;

    bool command_pending;

} console_t;

bool console_init (console_t* self, byte_stream_t* stream);

bool console_take_line (console_t* self, console_line_t* line);

void console_rx_callback (void* context);