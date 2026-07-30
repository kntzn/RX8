#pragma once

#include "uart.h"
#include "gpio.h"

typedef struct {
    uart_instance_t* usart;
    gpio_t* gpio;
} hc12_t;

void hc12_init (hc12_t* self, uart_instance_t* usart, gpio_t* set);