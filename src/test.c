//#include "stm32f1xx.h"
#include "queue.h"
#include <stdio.h>

typedef struct {
    uint16_t event;
    uint8_t payload [10];
} event_t;

int main ()
{
    DEFINE_STATIC_QUEUE (event_t, event_queue, 3);

    event_t event1 = {.event = 1, .payload = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}};
    event_t event2 = event1; event2.event = 2;
    event_t event3 = event2; event3.event = 3;

    queue_push (&event_queue, &event1);
    queue_push (&event_queue, &event2);
    queue_push (&event_queue, &event3);


    event_t out_event;

    for (int j = 0; j < 3; j++)
    {
        queue_pop (&event_queue, &out_event);

        printf ("%d\n", out_event.event);
        for (int i = 0; i < 10; i++)
            printf ("%d ", out_event.payload [i]);
        printf ("\n");
    }
}