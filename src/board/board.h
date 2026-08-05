#include <stm32f303xc.h>

// TODO: lit the LED
#define board_assert(cond) if(!(cond)){while(1){}}

void board_assert_failed_exception();
void board_not_implemented_exception();

void board_init ();