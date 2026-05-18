#include "stm32f1xx.h"

enum 
{
    BOOT = 0,
    LOCK,
    CONNECTING,
    READY,
    EXPORT,
    SLEEP,
    _MAKE_ENUM_32_BIT = 0xFFFFFFFF
} system_state_t;



int main ()
{

}