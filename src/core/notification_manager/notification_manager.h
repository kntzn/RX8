#include <stdbool.h>

typedef uint32_t notification_id_t;

notification_id_t notification_manager_register_callback (void* callback);

void notification_manager_raise (notification_id_t id);


/**
 * @brief Transfer mechanism to provide low-level event notifications 
 * to module layer's handlers
 * @brief up to 64 notifications
 */
void notification_manager_dispatch ();