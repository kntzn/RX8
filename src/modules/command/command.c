#include "command.h"

#include "console.h"

bool command_console_line_parse (console_line_t line);
bool command_console_line_split (uint8_t * line, size_t len, uint8_t ** strings);

extern bool execute_command;

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

    if (!console_take_line (source, &console_input))
        return false;
    if (!command_console_line_parse (console_input))
        return false;

    execute_command = true;

    return true;
}

bool command_proto_callback (void * dest, void * context)
{
    (void)context;
    (void)dest;
    return false;
}

bool command_console_line_parse (console_line_t line)
{
    return command_console_line_split (line.line, line.len, NULL);
}

bool command_console_line_split (uint8_t * line, size_t len, uint8_t ** strings)
{
    (void)line;
    (void)len;
    (void)strings;
    return true;
}