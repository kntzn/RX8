//#include "stm32f1xx.h"
#include "evqueue.h"
#include <stdio.h>

int main ()
{


printf ("Init\n");
evqueue_init (&queue);
event_t* array = evqueue_dump (&queue);
printf ("%d\n", (uint16_t)queue.array);



}