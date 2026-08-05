#pragma once

#include <stdbool.h>

typedef enum
{
    FAULT_NONE,
    FAULT_UART_OVERRUN,
    FAULT_NOT_IMPLEMENTED,
    FAULT_OUT_OF_SPACE,
    FAULT_UNEXPECTED_NULL,
    FAULT_ASSERTION_FAILED
} fault_t;

void debug_init ();

void debug_raise_fault (fault_t fault);

void debug_assertion_failed ();

static inline void debug_assert (bool condition)
{
    if (!condition)
        debug_assertion_failed ();
}
