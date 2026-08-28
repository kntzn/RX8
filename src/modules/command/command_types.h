#pragma once

typedef enum
{
    DOMAIN_UNKNOWN = 0,
    DOMAIN_TRACTION,
    DOMAIN_LIGHTS,
    DOMAIN_RADIO
} command_domain_t;

typedef struct
{
    
} command_lights_t;

typedef struct
{
    
} command_traction_t;

typedef struct
{
    
} command_radio_t;

typedef struct 
{
    command_domain_t domain;

    union
    {
        command_traction_t traction;
        command_lights_t lights;
        command_radio_t radio;
    };
    
} command_t;

