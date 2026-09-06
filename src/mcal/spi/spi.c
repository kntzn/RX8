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

    // always use master mode
    self->instance->CR1 |= SPI_CR1_MSTR;

    // set up CPOL / CPHA
    self->instance->CR1 &= ~(SPI_CR1_CPHA | SPI_CR1_CPOL);
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

    // set up software CS:
    self->instance->CR1 |= SPI_CR1_SSI |
                           SPI_CR1_SSM;

    // set up prescaler
    uint32_t prescaler;
    for (prescaler = 0; prescaler < 8; prescaler++)
    {
        uint32_t divider = 2UL << prescaler;
        // TODO [CRITICAL]: replace system core clock with get_spi_clock
        if ((SystemCoreClock / divider) <= self->max_frequency)
            break;
    }
    // Can not fit desired frequency
    if (prescaler == 8)
        return false;
    
    // threshold & data size (8bit)
    self->instance->CR2 &= ~SPI_CR2_DS_Msk;
    self->instance->CR2 |= ((8U-1U) << SPI_CR2_DS_Pos);
    self->instance->CR2 |= SPI_CR2_FRXTH;

    self->instance->CR1 &= ~SPI_CR1_BR_Msk;
    self->instance->CR1 |= (prescaler << SPI_CR1_BR_Pos);

    // enable SPI on setup completion
    self->instance->CR1 |= SPI_CR1_SPE;

    return true;
}

bool spi_transfer_blocking (spi_device_t * self, uint8_t * from, uint8_t * to, size_t len)
{
    if (!self)
        return false;

    size_t rx_ptr = 0, tx_ptr = 0;
    // kickstart the transaction (packer Workaround)
    while (tx_ptr < 4)
    {
        *(volatile uint8_t *) &self->instance->DR = from ? from[tx_ptr] : 0x00;
        tx_ptr++;
    }

    while (tx_ptr < len || rx_ptr < len)
    {    
        if ((tx_ptr < len) && (self->instance->SR & SPI_SR_TXE))
        {
            *(volatile uint8_t *) &self->instance->DR = from? from [tx_ptr] : 0x00;
            tx_ptr++;
        }

        if ((rx_ptr < len) && (self->instance->SR & SPI_SR_RXNE))
        {
            uint8_t rx_byte = *(volatile uint8_t *) &self->instance->DR;
            if (to)
                to [rx_ptr] = rx_byte;
            rx_ptr++;  
        }
    }

    while (self->instance->SR & SPI_SR_BSY)
        ;

    return true;
}
