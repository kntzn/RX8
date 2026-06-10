#pragma once

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct
{
    bool communication_enabled;
    bool traction_enabled;
} system_policy_t;

typedef enum 
{
    SYSTEM_STATE_BOOT = 0,
    SYSTEM_STATE_IDLE,
    SYSTEM_STATE_CONNECTING,
    SYSTEM_STATE_LOCK,
    SYSTEM_STATE_EXPORT,
    SYSTEM_STATE_READY
} system_state_t;



/**
 * @brief inits 
 */
bool fsm_init ();


void fsm_tick ();

