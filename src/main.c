#include <stdbool.h>
#include "stm32f303xc.h"

#include "runtime.h"
#include "uart.h"
#include "board.h"

static bool application_init (void);

void dummy()
{
    
}

int main ()
{
    if (!application_init())
        return 1;

    uint32_t idx = 0;
    uint8_t buffer [128] = {};

    dummy();

    uart_instance_t *UART = UART5;
    while (true)
    {
        

        if (uart_ready (UART5))
        {
            uint8_t byte = uart_read_byte (UART5);
            
            if (byte != 0x7F)
            {
                uart_write_byte (UART5, byte);
                buffer [idx] = byte;          
                idx++;
            }
            else
            {
                idx--;
                uart_write_blocking (UART5, (uint8_t*)"\b \b", 3);
            }
            

            if (byte == '\r')
            {
                uart_write_byte (UART5, '\n');


                uart_write_blocking (UART5, buffer, idx);
                uart_write_byte (UART5, '\n');

                idx = 0;
            }
                

        }
    }    
    
    //runtime_run_once();    

    return 0;
}

static bool application_init (void)
{
    __disable_irq();
    // ----- Place init functions here ----- //

    board_init ();
    uart_init (UART5, SystemCoreClock, 115200);
    //uart_init (USART2, SystemCoreClock, 9600);

    //if (!runtime_init())
    //    return false;

    // communication_init
     
    // ----- Place init functions here ----- //
    __enable_irq();

    return true;
}