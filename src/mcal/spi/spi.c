#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include <stm32f303xc.h>

#include "mcal/spi/spi.h"

bool spi_configure (spi_device_t * self);

bool spi_init (spi_device_t * self)
{
    spi_configure (self);
    
    return true;
} 

bool spi_configure (spi_device_t * self)
{
    // disable SPI during setup
    self->instance->CR1 &= ~SPI_CR1_SPE;

    // disable SPI during setup
    self->instance->CR1 &= ~SPI_CR1_SPE;

    self->instance->CR1 &= ~(SPI_CR1_CPHA | SPI_CR1_CPOL);

    // set up CPOL / CPHA
    switch (self->mode)
    {
        case SPI_MODE_0:
            break;
        case SPI_MODE_1:
            self->instance->CR1 |= SPI_CR1_CPHA;
            break;
        case SPI_MODE_2:
            self->instance->CR1 |= SPI_CR1_CPOL;
            break;
        case SPI_MODE_3:
            self->instance->CR1 |= SPI_CR1_CPOL | SPI_CR1_CPHA;
            break;
        default:
            break;
    }


    // TODO [CRITICAL]: replace system core clock with get_spi_clock

    // set up prescaler
    uint32_t prescaler;
    for (prescaler = 0; prescaler < 8; prescaler++)
    {
        uint32_t divider = 2UL << prescaler;
    
        if ((SystemCoreClock / divider) <= self->max_frequency)
            break;
    }
    
    // Can not fit desired frequency
    if (prescaler == 8)
        return false;
    
    self->instance->CR1 &= ~SPI_CR1_BR_Msk;
    self->instance->CR1 |= (prescaler << SPI_CR1_BR_Pos);

    return true;
}

bool spi_transfer_blocking (spi_device_t * self, uint8_t * from, uint8_t * to, size_t len)
{
    if (!self)
        return false;
    
    // toggle off for now (would be toggled in executing code before CS)
    //if (!spi_configure (self))
    //    return false;
    
    for (size_t i = 0; i < len; i++)
    {
        while (!(self->instance->SR & SPI_SR_TXE))
            ;

        self->instance->DR = from? from [i] : 0xFF;
        
        while (!(self->instance->SR & SPI_SR_RXNE))
            ;

        if (to)
            to [i] = self->instance->DR;
        
    }

    while (!(self->instance->SR & SPI_SR_TXE))
        ;

    while (!(self->instance->SR & SPI_SR_BSY))
        ;

    return true;
}
