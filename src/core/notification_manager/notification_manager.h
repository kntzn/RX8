#include <stdbool.h>

typedef uint32_t notification_id_t;
typedef void (*notification_callback_t)(void * context);

notification_id_t notification_manager_register_callback (notification_callback_t callback, void * context);

void notification_manager_raise (notification_id_t id);


/**
 * @brief Transfer mechanism to provide low-level event notifications 
 * to module layer's handlers
 * @brief up to 64 notifications
 */
void notification_manager_dispatch ();