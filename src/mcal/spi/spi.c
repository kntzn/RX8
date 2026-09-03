#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include <stm32f303xc.h>

#include "mcal/spi/spi.h"

#define SPI_INSTANCE_COUNT 3

static spi_instance_t * instance_table [SPI_INSTANCE_COUNT] = {0};
static SPI_TypeDef*     spi_table    [SPI_INSTANCE_COUNT] = {0};
 
bool spi_register_instance (spi_instance_t * self, SPI_TypeDef * spi);

bool spi_init (spi_instance_t * self, SPI_TypeDef * spi)
{
    self->instance = spi;

    // spi config ?
    
    return spi_register_instance (self, spi);
} 

bool spi_register_instance (spi_instance_t * self, SPI_TypeDef * spi)
{
    // Save ptrs to instance and stm uart regs structure
    for (uint8_t idx = 0; idx < SPI_INSTANCE_COUNT; idx++)
    { 
        // Already registered
        if (spi_table [idx] == spi)
            return true;

        // Successfully registered
        if (instance_table [idx] == NULL &&
            spi_table [idx] == NULL)
        {
            instance_table [idx] = self;
            spi_table [idx] = spi;

            return true;
        }
        
    }

    // Out of space in table
    return false;
}