#include "drivers/cc1101/cc1101.h"
#include "drivers/cc1101/cc1101_types.h"

#define CC1101_BURST 0x40
#define CC1101_READ  0x80
#define CC1101_WRITE (0)



bool cc1101_strobe      (cc1101_t * self, uint8_t command);
bool cc1101_read_reg    (cc1101_t * self, uint8_t address, uint8_t * value);
bool cc1101_write_reg   (cc1101_t * self, uint8_t address, uint8_t value);
bool cc1101_read_status (cc1101_t * self, uint8_t address, uint8_t * value);
bool cc1101_write_burst (cc1101_t * self, uint8_t address, uint8_t value);
bool cc1101_read_burst  (cc1101_t * self, uint8_t address, uint8_t * value);


bool cc1101_init (cc1101_t * self, gpio_t * cs, gpio_t * gdo1)
{
    self->cs = cs;
    self->gdo1 = gdo1;

    return true;
}

bool cc1101_handler (void * dest, void * context)
{
    // context is source of event;
    // dest is self;
    (void)context;
    cc1101_t * self = (cc1101_t *) dest;

    uint8_t status;
    cc1101_read_reg (self, 0x35, &status);

    return true;
}

bool cc1101_strobe (cc1101_t * self, uint8_t command);
bool cc1101_read_reg (cc1101_t * self, uint8_t address, uint8_t * value)
{
    uint8_t tx_buffer [2] = { 0, 0 };
    uint8_t rx_buffer [2] = { 0, 0 };
    uint8_t marcstate_byte = 0;

    tx_buffer [0] = CC1101_READ | CC1101_BURST | address;

    gpio_write (self->cs, GPIO_STATE_LOW);
    
    // part of cc1101 protocol (CS low -> wait for miso low -> transfer)
    while (gpio_read (self->gdo1) == GPIO_STATE_HIGH)
        ;

    spi_transfer_blocking (self->spi, tx_buffer, rx_buffer, 2);

    gpio_write (self->cs, GPIO_STATE_HIGH);

    marcstate_byte = rx_buffer [0];
    *value = rx_buffer [1];

    return true;   
}

bool cc1101_write_reg (cc1101_t * self, uint8_t address, uint8_t value);
bool cc1101_read_status (cc1101_t * self, uint8_t address, uint8_t * value);
bool cc1101_write_burst (cc1101_t * self, uint8_t address, uint8_t value);
bool cc1101_read_burst (cc1101_t * self, uint8_t address, uint8_t * value);
