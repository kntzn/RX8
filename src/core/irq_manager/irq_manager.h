#include <stdbool.h>
#include "uart.h"

typedef enum 
{
    IRQ_EVENT_UART_1 = 1UL << 0,    
    IRQ_EVENT_UART_2 = 1UL << 1,    
    IRQ_EVENT_UART_3 = 1UL << 2,
    IRQ_EVENT_UART_4 = 1UL << 3,
    IRQ_EVENT_UART_5 = 1UL << 4,
    IRQ_EVENT_SPI_1 = 1UL << 5,
    IRQ_EVENT_SPI_2 = 1UL << 6,
    IRQ_EVENT_EXTI_4 = 1UL << 7,
    IRQ_EVENT_EXTI_5 = 1UL << 8,    
    //IRQ_EVENT_UART_5 = 1UL << 9,
    //IRQ_EVENT_UART_1 = 1UL << 10,
    //IRQ_EVENT_UART_2 = 1UL << 11,
    //IRQ_EVENT_UART_3 = 1UL << 12,
    //IRQ_EVENT_UART_4 = 1UL << 13,
    //IRQ_EVENT_UART_5 = 1UL << 14,
    //IRQ_EVENT_ = 1UL << 15
} irq_event_t;

void irq_manager_init ();

bool irq_manager_register_callback (irq_event_t event, void* callback);

void irq_manager_raise (irq_event_t event);

//void irq_manager_dispatch ();