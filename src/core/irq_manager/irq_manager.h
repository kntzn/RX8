

typedef enum 
{
    IRQ_EVENT_UART_1_RX_AVAIL = 1UL << 0,    
    IRQ_EVENT_UART_2_RX_AVAIL = 1UL << 1,    
    IRQ_EVENT_UART_3_RX_AVAIL = 1UL << 2,
    IRQ_EVENT_UART_4_RX_AVAIL = 1UL << 3,
    IRQ_EVENT_UART_5_RX_AVAIL = 1UL << 4,
    IRQ_EVENT_UART_1_TX_READY = 1UL << 5,
    IRQ_EVENT_UART_2_TX_READY = 1UL << 6,
    IRQ_EVENT_UART_3_TX_READY = 1UL << 7,
    IRQ_EVENT_UART_4_TX_READY = 1UL << 8,    
    IRQ_EVENT_UART_5_TX_READY = 1UL << 9,
    IRQ_EVENT_ = 1UL << 10,
    IRQ_EVENT_ = 1UL << 11,
    IRQ_EVENT_ = 1UL << 12,
    IRQ_EVENT_ = 1UL << 13,
    IRQ_EVENT_ = 1UL << 14,
    IRQ_EVENT_ = 1UL << 15
} irq_event_t;

void irq_manager_register_callback ();

void irq_manager_raise_uart (uart_irq_event_t event);
//void irq_manager_raise_spi (spi_irq_event_t event);