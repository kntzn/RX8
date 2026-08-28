#include <string.h>

#include "modules/command/command_cli_parser.h"
#include "modules/command/command_types.h"

#define PARSER_MAX_ARGS 8

inline bool command_symbol_is_split_symbol (uint8_t symbol);
bool command_console_line_split (uint8_t * line, size_t len, size_t * argc, char ** argv);

command_t command_parse_args (size_t argc, char ** argv);
command_domain_t command_parse_domain (const char * domain_str);

bool command_console_line_parse (console_line_t line, command_t* command)
{
    size_t argc;
    char* argv [PARSER_MAX_ARGS]; 

    if (!command_console_line_split (line.line, line.len, &argc, argv))
        return false;

    *command = command_parse_args (argc, argv);

    return true;
}

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

    return true;
}

inline bool command_symbol_is_split_symbol (uint8_t symbol)
{
    return symbol == ' ' || symbol == '\t' || symbol == '\0';
}

command_domain_t command_parse_domain (const char * domain_str)
{
    if (!strcmp (domain_str, "traction"))
        return DOMAIN_TRACTION;
    if (!strcmp (domain_str, "lights"))
        return DOMAIN_LIGHTS;
    if (!strcmp (domain_str, "radio"))
        return DOMAIN_RADIO;

    return DOMAIN_UNKNOWN;
}

command_t command_parse_args (size_t argc, char ** argv)
{
    command_t command;
    command_domain_t domain = command_parse_domain (argv[0]);

    (void)argc;

    switch (domain)
    {
    case DOMAIN_TRACTION:
        //parse_traction (argc-1, argv+1)
        break;
    case DOMAIN_LIGHTS:
        // parse_lights
        break;
    case DOMAIN_RADIO:
        // parse_radio
        break;
    default:
        break;
    }

    command.domain = domain;

    return command;
}