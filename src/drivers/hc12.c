#include "hc12.h"
#include "uart.h"


void hc12_init (hc12_t* self, uart_instance_t* usart, gpio_t* set)
{
    self->usart = usart;
    self->set = set;
}
