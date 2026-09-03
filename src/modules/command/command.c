#include "command.h"

#include "modules/command/command_types.h"
#include "modules/command/command_cli_parser.h"

#include "modules/console/console.h"

bool command_execute (command_t command);

bool command_cli_callback (void * dest, void * context)
{
    (void)dest;

    command_t command;
    console_t * source = (console_t*) context;
    console_line_t console_input;

    // TODO check for data race
    if (!console_get_line (source, &console_input)) // TODO: line length in console_line_t
        return false;
    if (!command_console_line_parse (console_input, &command))
        return false;
    if (!console_release_line (source))
        return false;
    if (!command_execute (command))
        return false;

    return true;
}


bool command_proto_callback (void * dest, void * context)
{
    (void)context;
    (void)dest;
    return false;
}

bool command_execute (command_t command)
{
    (void)command;
    return false;
}