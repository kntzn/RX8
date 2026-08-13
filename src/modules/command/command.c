#include "command.h"

#include "console.h"

bool command_console_line_parse (uint8_t * line, size_t len);
bool command_console_line_split (uint8_t * line, size_t len, uint8_t ** strings);

static char* known_words[] = \
{
    "help",
    "add",
    "set",
    "get",
    "motor",
    "current",
};

bool command_cli_callback (void * context)
{
    console_t * source = (console_t*) context;
    console_line_t console_input;

    if (!console_take_line (source, &console_input))
        return false;
    if (!command_console_line_parse (NULL, 0))
        return false;
    

    return true;
}

bool command_proto_callback (void * context)
{
    (void)context;
    return false;
}

bool command_console_line_parse (uint8_t * line, size_t len)
{

    command_console_line_split (line, len, );
}

bool command_console_line_split (uint8_t * line, size_t len, uint8_t ** strings)
{

}