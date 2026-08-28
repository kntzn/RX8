#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

bool command_init ();

bool command_cli_callback (void * dest, void * context);
bool command_proto_callback (void * dest, void * context);
