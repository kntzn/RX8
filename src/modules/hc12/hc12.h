#include <stm32f303xc.h>

#include "gpio.h"

typedef struct {
    USART_TypeDef* usart;
    gpio_t* gpio;
} hc12_t;

void hc12_init (hc12_t* hc12);