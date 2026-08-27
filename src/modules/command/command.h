#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

bool command_init ();

bool command_cli_callback (void * dest, void * context);
bool command_proto_callback (void * dest, void * context);



/*
typedef enum
{
COMMAND_TYPE_SET_THROTTLE,
COMMAND_TYPE_GET_TEMP
} command_type_t;

typedef struct 
{
    command_type_t type;
} command_t;

typedef struct 
{
    command_type_t type;
    void * payload;
    size_t len;
} command_reply_t;

typedef bool (*cli_interface_write_fn)(void * context, uint8_t byte);
typedef bool (*cli_interface_read_fn)(void * context, uint8_t* byte);
typedef struct 
{
    void * context;
    cli_interface_read_fn read;
    cli_interface_write_fn write;
} cli_interface_t;

typedef bool (*proto_interface_write_fn)(void * context, uint8_t byte);
typedef bool (*proto_interface_read_fn)(void * context, uint8_t* byte);
typedef struct 
{
    void * context;
    proto_interface_read_fn read;
    proto_interface_write_fn write;
} proto_interface_t;

bool cli_interface_init ();
bool cli_interface_read ();
bool cli_interface_write ();

bool proto_interface_init (proto_interface_t * self,
                           void * context,
                           proto_interface_read_fn read,
                           proto_interface_write_fn write);
bool proto_interface_read (proto_interface_t * self, command_t* cmd);
bool proto_interface_write (proto_interface_t * self, command_reply_t rep);



//bool command_init ();
bool command_init ();

*/