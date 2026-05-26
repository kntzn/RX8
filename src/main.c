#include "stm32f1xx.h"
#include "event_queue.h"

int main ()
{

    event_t event = NONE;
    event_queue_push (event);
    event_queue_dispatch_event (DEFAULT);

}