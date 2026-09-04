#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include <stm32f303xc.h>

#include "mcal/spi/spi.h"

bool spi_init (spi_device_t * self)
{

    switch (self->mode)
    {
    case SPI_MODE_0:
        break;
    case SPI_MODE_0:
        break;
    
    default:
        break;
    }
    self->instance->CR1;
    // spi config ?
    
    return spi_register_instance (self);
} 

