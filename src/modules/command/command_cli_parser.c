#include "modules/command/command_cli_parser.h"

#include <stm32f303xc.h>

// string "xxx xx xxxx" -> array of ptrs -> converter (ptr_x) ~= dict -> form commands

//void command_parse (cli_interface_t* cli, command_t *command_t)
//{
    //cli->read ()
//}

#define PARSER_MAX_ARGS 8

inline bool command_symbol_is_split_symbol (uint8_t symbol);
bool command_console_line_split (uint8_t * line, size_t len, size_t * argc, char ** argv);

void dummy()
{}

bool command_console_line_parse (console_line_t line)
{
    size_t argc;
    char* argv [PARSER_MAX_ARGS]; 

    if (!command_console_line_split (line.line, line.len, &argc, argv))
        return false;

    dummy();

    return true;
}

/**
 * TODO list:
 * 1. find first symbol
 * 2. set argv
 * 3. i
 */

bool command_console_line_split (uint8_t * line, size_t len, size_t * argc, char ** argv)
{
    size_t linec = 0;
    size_t arg_counter = 0;

    if (argc == NULL || argv == NULL)
        return false;
    
    // reset argument counter;
    arg_counter = 0;    

    // drop heading spaces
    for (; linec < len; linec++)
        if (! command_symbol_is_split_symbol (line [linec]))
            break;

    // replace all split symb with \0
    for (size_t i = linec; i < len; i++)
        if (command_symbol_is_split_symbol (line [i]))
            line [i] = '\0';

    // continue with splitting until EOL
    for (; linec < len; linec++)
    {   
        // if first symbol in line is non-split, set first arg
        if (linec == 0)
        {
            if (arg_counter < PARSER_MAX_ARGS-1)
                argv [arg_counter++] = (char*)(line + linec);
        }
        else
        {
            if (command_symbol_is_split_symbol (line [linec-1]) &&
                !command_symbol_is_split_symbol (line [linec]))
                if (arg_counter < PARSER_MAX_ARGS-1)
                    argv [arg_counter++] = (char*)(line + linec);
        }
            
    }

    // console guaranties to have at least one excessive symbol at the end of buffer
    line [linec+1] = '\0';

    *argc = arg_counter;

    __BKPT();

    return true;
}

inline bool command_symbol_is_split_symbol (uint8_t symbol)
{
    return symbol == ' ' || symbol == '\t' || symbol == '\0';
}