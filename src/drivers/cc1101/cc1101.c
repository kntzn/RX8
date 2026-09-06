#include "drivers/cc1101/cc1101.h"

#define CC1101_BURST (1U << 6)
#define CC1101_READ  (1U << 7)
#define CC1101_WRITE (0)


bool cc1101_write_reg (cc1101_t * self);

bool cc1101_init (cc1101_t * self, gpio_t * cs)
{
    self->cs = cs;

    return true;
}

bool cc1101_handler (void * dest, void * context)
{
    // context is source of event;
    // dest is self;
    (void)context;
    cc1101_t * self = (cc1101_t *) dest;

    cc1101_write_reg (self);

    return true;
}

bool cc1101_write_reg (cc1101_t * self)
{
    uint8_t tx_buffer [2] = { 0, 0 };
    uint8_t rx_buffer [2] = { 0, 0 };

    tx_buffer [0] = 0xF5; //CC1101_READ | 0x35;

    gpio_write (self->cs, GPIO_STATE_LOW);
    
    spi_transfer_blocking (self->spi, tx_buffer, rx_buffer, 2);

    gpio_write (self->cs, GPIO_STATE_HIGH);
    return true;   
}