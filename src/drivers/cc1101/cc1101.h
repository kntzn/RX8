#pragma once

#include "mcal/spi/spi.h"
#include "mcal/gpio/gpio.h"

typedef struct 
{
    spi_device_t * spi;
    gpio_t * cs;
    // exti_t * gdo0;
    // exti_t * gdo2;
} cc1101_t;

bool cc1101_init (cc1101_t * self, gpio_t * cs);

bool cc1101_handler (void * dest, void * context);