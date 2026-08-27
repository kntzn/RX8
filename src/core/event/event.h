#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef enum
{
EVENT_NONE = 0,
EVENT_CONSOLE_LINE_READY,
EVENT_RESERVED2,
EVENT_RESERVED3,

// Private
__EVENT_MAX
} event_t;

typedef bool (*event_handler_t)(void * dest, void *source);

/**
 * @brief Add new event to the queue
 * @details Should be called on each event to be dispatched
 * 
 * @param event Event to be dispatched later
 * 
 * @return true on succesfull push, false on overflow
 */
bool event_raise  (event_t event, void * context);

/**
 * @brief Event dispatcher handler
 * 
 * @param count Number of events to be processed
 * @example event_queue_dispatch_event (8);
 */
void event_dispatch (uint16_t count);

/**
 * @brief Event dispatcher handler. 
 * @details processes EVENT_QUEUE_DISPATCH_EVENT_COUNT events
 */
//void event_dispatch_default ();

/**
 * @brief Registers event handler to selected event type
 * 
 * @param event Event id
 * @param handler Handler function
 * 
 * @example event_queue_register_event_handler (RX_PACKET_AVAILABLE, process_packet);
 */
bool event_register_handler (event_t event, event_handler_t handler, void * context);

