#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/**
 * What it should do:
 * Run schedule every x us
 * 
 * 
 * 
 * 
 */

#define SCHEDULE_TABLE_SIZE 32

typedef void (*schedule_handler_t)(void);

typedef struct 
{
    uint32_t period;
    uint32_t counter;
    
    schedule_handler_t callback;
} schedule_t;

static uint8_t schedule_count = 0;
static schedule_t schedules [SCHEDULE_TABLE_SIZE] = {};

bool scheduler_init()
{
    return true;
}

bool scheduler_tick()
{
    for (uint8_t i = 0; i < schedule_count; i++)
    {
        //schedules
    }
    return false;
}

bool scheduler_reset_schedule(uint8_t *instance_id)
{
    if (*instance_id > schedule_count || *instance_id == 0)
        return false;
    
    schedules [*instance_id].period = 0;
    return true;
}

bool scheduler_register_schedule(uint8_t* instance_id, uint32_t period, schedule_handler_t handler)
{
    if (handler == NULL || period == 0 || schedule_count >= SCHEDULE_TABLE_SIZE)
    {
        *instance_id = 0;
        return false;
    }
        
    schedules [schedule_count++] = (schedule_t) \
    {
        .period = period, 
        .counter = 0,
        .callback = handler 
    };
    *instance_id = schedule_count;

    return true;
}
