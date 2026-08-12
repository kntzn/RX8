#include <stddef.h>
#include <assert.h>

#include "stm32f303xc.h"

#include "board.h"
#include "uart.h"
#include "utils.h"
#include "debug.h"

#define USART_INSTANCE_COUNT 5

static uart_instance_t * instance_table [USART_INSTANCE_COUNT] = {0};
static USART_TypeDef*   usart_table    [USART_INSTANCE_COUNT] = {0};

bool uart_register_instance (uart_instance_t * self, USART_TypeDef* uart);
uart_instance_t * uart_get_instance_by_uart (USART_TypeDef* stm_uart);

bool uart_process_rx_isr (uart_instance_t * self);
bool uart_process_tx_isr (uart_instance_t * self);


bool uart_init (uart_instance_t * self, USART_TypeDef* uart, uint32_t clock_freq, uint32_t baudrate)
{
    self->instance = uart;

    self->instance->CR1 &= ~USART_CR1_UE;

    self->instance->CR1 = 0;
    self->instance->CR2 = 0;
    self->instance->CR3 = 0;

    self->instance->BRR = (clock_freq + baudrate/2U)/baudrate;

    self->instance->CR1 |= USART_CR1_TE | USART_CR1_RE;
    self->instance->CR1 |= USART_CR1_RXNEIE;

    self->instance->CR1 |= USART_CR1_UE;

    static_assert (IS_POWER_OF_2 (UART_BUFFER_SIZE));

    if (!(ring_buffer_init (&self->rx_buffer, self->rx_data, UART_BUFFER_SIZE)))
        return false;
    
    if (!(ring_buffer_init (&self->tx_buffer, self->tx_data, UART_BUFFER_SIZE)))
        return false;
   
    
    byte_stream_init (&self->stream)

    return uart_register_instance (self, uart);
}

byte_stream_t* uart_get_stream (uart_instance_t* self)
{
    return &self->stream;
}

bool uart_irq_handler (USART_TypeDef* stm_uart)
{
    uart_instance_t * uart = uart_get_instance_by_uart (stm_uart);

    uart_irq_event_t raised_events = UART_IRQ_EVENT_NONE;

    debug_assert (uart != NULL);
    
    if ((uart->instance->ISR & USART_ISR_RXNE) != 0u) 
    {
        if (!uart_process_rx_isr(uart))
            debug_raise_fault (FAULT_OUT_OF_SPACE);
        
        raised_events |= UART_IRQ_EVENT_RX_AVAIL;
    }

    if (((uart->instance->ISR & USART_ISR_TXE) != 0u) &&
        ((uart->instance->CR1 & USART_CR1_TXEIE) != 0u)) 
    {
        if (!uart_process_tx_isr(uart))
            debug_raise_fault (FAULT_OUT_OF_SPACE);
        
        raised_events |= UART_IRQ_EVENT_TX_READY;
    }


    if ((uart->instance->ISR & USART_ISR_ORE) != 0u) 
    {
        uart->instance->ICR = USART_ICR_ORECF;
        raised_events |= UART_IRQ_EVENT_ERROR;

        debug_raise_fault (FAULT_UART_OVERRUN);
    }
    
    uart->events |= raised_events;
    return raised_events != UART_IRQ_EVENT_NONE;
}

bool uart_register_instance (uart_instance_t * self, USART_TypeDef* uart)
{
    // Save ptrs to instance and stm uart regs structure
    for (uint8_t idx = 0; idx < USART_INSTANCE_COUNT; idx++)
    { 
        // Already registered
        if (usart_table    [idx] == uart)
            return true;

        // Successfully registered
        if (instance_table [idx] == NULL &&
            usart_table    [idx] == NULL)
        {
            instance_table [idx] = self;
            usart_table    [idx] = uart;

            return true;
        }
        
    }

    // Out of space in table
    return false;
}

uart_irq_event_t uart_take_events (uart_instance_t * self)
{
    uart_irq_event_t event_mask;

    IRQ_LOCK
        {
        event_mask = self->events;
        self->events = UART_IRQ_EVENT_NONE;
        }

    return event_mask;
}

bool uart_read_async (uart_instance_t * self, uint8_t * byte)
{
    if (self == NULL)
    {
        debug_raise_fault (FAULT_UNEXPECTED_NULL);
        return false;
    }

    return ring_buffer_pop (&self->rx_buffer, byte);
}

bool uart_write_async (uart_instance_t * self, uint8_t byte)
{
    if (self == NULL)
    {
        debug_raise_fault (FAULT_UNEXPECTED_NULL);
        return false;
    }

    // enable TXE interrupt

    if (!ring_buffer_push (&self->tx_buffer, byte))
        return false;
    
    self->instance->CR1 |= USART_CR1_TXEIE;
    return true;

}

bool uart_write_bytes_async (uart_instance_t * self, uint8_t * string, size_t len)
{
    if (self == NULL)
    {
        debug_raise_fault (FAULT_UNEXPECTED_NULL);
        return false;
    }

    // enable TXE interrupt
  
    for (size_t i = 0; i < len; i++)
        if (!ring_buffer_push (&self->tx_buffer, string[i]))
            return false;

    self->instance->CR1 |= USART_CR1_TXEIE;   
    return true;   
}

// ---------- Private defenitions ---------- //

bool uart_process_tx_isr (uart_instance_t * self)
{   
    uint8_t byte;
    
    if (!ring_buffer_pop (&self->tx_buffer, &byte))
    {
        // disable TXE interrupt on buffer empty
        self->instance->CR1 &= ~USART_CR1_TXEIE;
        
        return false;
    }
    self->instance->TDR = byte; 
    return true;
}

bool uart_process_rx_isr (uart_instance_t * self)
{
    uint8_t byte = (uint8_t)self->instance->RDR;
    
    if (!ring_buffer_push (&self->rx_buffer, byte))
        return false;

    return true;
}  

uart_instance_t * uart_get_instance_by_uart (USART_TypeDef* stm_uart)
{
    for (uint8_t idx = 0; idx < USART_INSTANCE_COUNT; idx++)
    {
        if (usart_table [idx] == stm_uart &&
            instance_table [idx] != NULL)
            return instance_table [idx];
    }

    return NULL;
}


// ---------- Deprecated ---------- //

void uart_write_blocking (uart_instance_t * self, uint8_t* buffer, uint32_t len)
{
    for (uint32_t i = 0; i < len; i++)
    {
        // Wait for TDR to be ready to receive data
        while (!(self->instance->ISR & USART_ISR_TXE));

        // Write byte to TX
        self->instance->TDR = buffer[i];
    }

    // Wait for end of transaction
    while (!(self->instance->ISR & USART_ISR_TC));
}

void uart_read_blocking  (uart_instance_t * self, uint8_t* buffer, uint32_t len)
{
    for (uint32_t i = 0; i < len; i++)
    {
        while (!(self->instance->ISR & USART_ISR_RXNE));

        buffer[i] = (uint8_t)self->instance->RDR;
    }

}

uint8_t uart_read_byte  (uart_instance_t * self)
{
    return (uint8_t)self->instance->RDR;
}

bool uart_ready (uart_instance_t * self)
{
    return (bool)(self->instance->ISR & USART_ISR_RXNE);
}

void uart_write_byte (uart_instance_t * self, uint8_t byte)
{
    // Wait for TDR to be ready to receive data
    while (!(self->instance->ISR & USART_ISR_TXE));
 
    // Write byte to TX
    self->instance->TDR = byte;
 
    // Wait for end of transaction
    while (!(self->instance->ISR & USART_ISR_TC));
}



#undef USART_INSTANCE_COUNT



