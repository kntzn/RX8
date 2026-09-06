#include "mcal/spi/spi.h"

typedef struct 
{
    spi_device_t * spi;
    // gpio_t * cs;
    // exti_t * gdo0;
    // exti_t * gdo2;
} cc1101_t;

bool cc1101_init (cc1101_t * self);