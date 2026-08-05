#include <stdbool.h>
#include "uart.h"

typedef enum 
{
    IRQ_EVENT_NONE = 0UL,
    IRQ_EVENT_UART_1 = 1UL,
    IRQ_EVENT_UART_2 = 2UL,
    IRQ_EVENT_UART_3 = 3UL,
    IRQ_EVENT_UART_4 = 4UL,
    IRQ_EVENT_UART_5 = 5UL,
    IRQ_EVENT_SPI_1 = 6UL,
    IRQ_EVENT_SPI_2 = 7UL,
    IRQ_EVENT_EXTI_4 = 8UL,
    IRQ_EVENT_EXTI_5 = 9UL,
    //IRQ_EVENT_UART_5 = 1UL << 9,
    //IRQ_EVENT_UART_1 = 1UL << 10,
    //IRQ_EVENT_UART_2 = 1UL << 11,
    //IRQ_EVENT_UART_3 = 1UL << 12,
    //IRQ_EVENT_UART_4 = 1UL << 13,
    //IRQ_EVENT_UART_5 = 1UL << 14,
    //IRQ_EVENT_ = 1UL << 15
    IRQ_EVENT_COUNT
} irq_event_t;

void irq_manager_init ();

bool irq_manager_register_callback (irq_event_t event, void* callback);

void irq_manager_raise (irq_event_t event);

void irq_manager_dispatch ();