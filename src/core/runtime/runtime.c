#include "runtime.h"
#include "scheduler.h"
#include "event.h"

/**
 * What it should do:
 * runtime_run () - run superloop logic
 *      realtime_run () - run realtime tasks ----> SCHEDULER
 *           realtime_get_budget () ----> SCHEDULER
 *      process_events () - process pending events in time budget 
 *      background_run () - run background task's steps if there is time slack
 * 
 * 
 */

bool runtime_init()
{
    scheduler_init ();

    // background init 
    // 
}

void runtime_run_once()
{
    scheduler_tick ();
    // Process realtime
    
    // Process events
    event_dispatch_default ();

    // Process background
    // 

    // Idle
    __WFI ();
}
