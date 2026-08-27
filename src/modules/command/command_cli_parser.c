#include "modules/command/command_cli_parser.h"

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
    bool is_cont_space = false;
    size_t linec = 0;
    
    if (argc == NULL || argv == NULL)
        return false;
    
    // reset argument counter;
    *argc = 0;    

    // drop heading spaces
    for (; linec < len; linec++)
    {
        // on first non-space symbol occurance
        if (! command_symbol_is_split_symbol (line [linec]))
        {
            // set first argument
            if (*argc < PARSER_MAX_ARGS-1)
                argv [*argc++] = (char*)(line + linec);
            
            // continue parsing with at least 2nd char
            linec++;
            break;
        }
    }

    // continue splitting until EOL
    for (; linec < len; linec++)
    {
        if ( command_symbol_is_split_symbol (line [linec]))
        {
            // 
            if ( command_symbol_is_split_symbol (line [linec-1]))
                is_cont_space = true;
               
            if (!is_cont_space)
            {
                if (*argc < PARSER_MAX_ARGS-1)
                    argv [*argc++] = (char*)(line + linec);
            }   
            
            line [linec] = '\0';
        }
        else
            is_cont_space = false;
    }

    // console guaranties to have at least one excessive symbol at the end of buffer
    line [linec+1] = '\0';

    return true;
}

inline bool command_symbol_is_split_symbol (uint8_t symbol)
{
    return symbol == ' ' || symbol == '\t' || symbol == '\0';
}