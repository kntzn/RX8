#include "stm32f1xx.h"
#include "event.h"

int main ()
{

    event_t event = EVENT_NONE;
    event_queue_push (event);
    event_queue_dispatch (5);

}