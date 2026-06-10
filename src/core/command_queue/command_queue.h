#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "core_config.h"

typedef enum
{
COMMAND_NONE = 0,
COMMAND_RESERVED1,
COMMAND_RESERVED2,
COMMAND_RESERVED3,

// Private
__COMMAND_MAX
} command_t;

typedef void (*command_handler_t)(const command_t event);

/**
 * @brief Add new event to the queue
 * @details Should be called on each event to be dispatched
 * 
 * @param event Event to be dispatched later
 * 
 * @return true on succesfull push, false on overflow
 */
bool command_queue_push  (command_t event);

/**
 * @brief Event dispatcher handler
 * 
 * @param count Number of events to be processed
 * @example event_queue_dispatch_event (8);
 */
void command_queue_dispatch (uint16_t count);

/**
 * @brief Event dispatcher handler. 
 * @details processes EVENT_QUEUE_DISPATCH_EVENT_COUNT events
 */
void command_queue_dispatch_default ();

/**
 * @brief Registers event handler to selected event type
 * 
 * @param event Event id
 * @param handler Handler function
 * 
 * @example event_queue_register_event_handler (RX_PACKET_AVAILABLE, process_packet);
 */
bool command_queue_register_command_handler (command_t event, command_handler_t handler);

