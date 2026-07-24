#include <stdint.h>

#include <stm32f303xc.h>

typedef USART_TypeDef uart_instance_t;

void uart_init (uart_instance_t* uart, uint32_t clock_freq, uint32_t baudrate);

void uart_write_blocking (uart_instance_t* uart, uint8_t* buffer, uint32_t len);
void uart_read_blocking  (uart_instance_t* uart, uint8_t* buffer, uint32_t len);