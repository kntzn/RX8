#pragma once

#include "console.h"

#define CLI_BUFFER_SIZE 64

typedef struct {
    console_t* console;

} command_queue_t;

bool command_queue_init (command_queue_t* self);


