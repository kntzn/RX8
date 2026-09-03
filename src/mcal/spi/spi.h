#include <stm32f303xc.h>

typedef struct
{
    SPI_TypeDef* instance;

    // counter rx / tx
    // irq_mode_rx None/IRQ/DMA
    // irq_mode_tx None/IRQ/DMA

} spi_instance_t;

// CC1101
// CPOL = 0
// CPHA = 0

// ADXL345
// CPOL = 1
// CPHA = 1