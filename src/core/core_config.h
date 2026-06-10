#pragma once

// Number of events to be dispatched on command_queue_dispatch_event by default
#define COMMAND_QUEUE_DISPATCH_EVENT_COUNT 5

// Number of events to be dispatched on event_dispatch_event by default
#define EVENT_DISPATCH_EVENT_COUNT 5

// Max event count to be stored
#define COMMAND_QUEUE_SIZE 32u

// Max schedule count to be managed
#define SCHEDULE_TABLE_SIZE 8u