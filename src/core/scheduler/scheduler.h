#pragma once 


#include <stdbool.h>

typedef bool (*schedule_handler_t)();

bool scheduler_init ();

bool scheduler_tick ();

bool scheduler_reset_schedule (uint8_t* instance_id);

bool scheduler_register_schedule (uint8_t* instance_id, uint32_t period, schedule_handler_t handler);