#include "hc12.h"
#include "communication.h"

typedef enum
{
    COMMUNICATION_MODE_DISABLED = 0,
    COMMUNICATION_MODE_CONTROL,
    COMMUNICATION_MODE_EXPORT,
    COMMUNICATION_MODE_PAIRING,
    COMMUNICATION_MODE_UPDATE
} communication_mode_t;

typedef enum
{
    COMMUNICATION_PHASE_IDLE = 0,
    COMMUNICATION_PHASE_RX_WINDOW,
    COMMUNICATION_PHASE_RX,
    COMMUNICATION_PHASE_TX_WAIT,
    COMMUNICATION_PHASE_TX,

} communication_phase_t;

bool communication_init()
{
    return true; //return hc12_init ();
}