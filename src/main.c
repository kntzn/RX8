#include <stdbool.h>
#include "stm32f303xc.h"

#include "runtime.h"
#include "uart.h"
#include "board.h"

static bool application_init (void);

int main ()
{
    if (!application_init())
        return 1;
    
    uint8_t buffer [32] = "Hello world!\n";

    while (true)
        {
        uart_write_blocking (UART5, buffer, 13);
        for (uint32_t i = 0; i < 8000000; i++)
            __NOP();
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

    if (!runtime_init())
        return false;

    // communication_init
     
    //

    // ----- Place init functions here ----- //
    __enable_irq();

    return true;
}