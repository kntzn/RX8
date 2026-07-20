#include <stdbool.h>
#include "stm32f303xc.h"

#include "runtime.h"

static bool application_init (void);

int main ()
{
    if (!application_init())
        return 1;
    
    while (true)
        runtime_run_once();    

    return 0;
}

static bool application_init (void)
{
    __disable_irq();
    // ----- Place init functions here ----- //

    if (!runtime_init())
        return false;

    // communication_init
     
    //

    // ----- Place init functions here ----- //
    __enable_irq();

    return true;
}