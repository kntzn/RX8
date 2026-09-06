#pragma once

#include <stddef.h>

#include <stm32f303xc.h>

#include "mcal/gpio/gpio.h"

typedef enum
{
    SPI_MODE_0 = 0,
    SPI_MODE_1,    
    SPI_MODE_2,
    SPI_MODE_3   
} spi_mode_t;

typedef struct 
{
    SPI_TypeDef* instance;
    gpio_t * cs_pin;
    spi_mode_t mode;
    uint32_t max_frequency;
} spi_device_t;


/**
 * @brief configure the spi peripherial
 * @param spi_device_t * - spi device structure that should contain
 */
bool spi_init (spi_device_t * self);

bool spi_transfer_blocking (spi_device_t * self, uint8_t * from, uint8_t * to, size_t len);

// CC1101
// CPOL = 0
// CPHA = 0

// ADXL345
// CPOL = 1
// CPHA = 1