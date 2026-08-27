#include "command.h"

#include "modules/command/command_cli_parser.h"
#include "modules/console/console.h"

/*
static char* known_words[] = \
{
    "help",
    "add",
    "set",
    "get",
    "motor",
    "current",
}; */

bool command_cli_callback (void * dest, void * context)
{
    (void)dest;

    console_t * source = (console_t*) context;
    console_line_t console_input;

    // TODO check for data race
    if (!console_take_line (source, &console_input)) // TODO: line length in console_line_t
        return false;
    if (!command_console_line_parse (console_input))
        return false;
    
    return true;
}


bool command_proto_callback (void * dest, void * context)
{
    (void)context;
    (void)dest;
    return false;
}
