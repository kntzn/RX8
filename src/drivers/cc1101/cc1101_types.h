typedef enum 
{
    CC1101_IOCFG2      = 0x00, // IOCFG2 GDO2 output pin configuration
    CC1101_IOCFG1      = 0x01, // IOCFG1 GDO1 output pin configuration
    CC1101_IOCFG0      = 0x02, // IOCFG0 GDO0 output pin configuration
    CC1101_FIFOTHR     = 0x03, // FIFOTHR RX FIFO and TX FIFO thresholds
    CC1101_SYNC1       = 0x04, // SYNC1 Sync word, high byte
    CC1101_SYNC0       = 0x05, // SYNC0 Sync word, low byte
    CC1101_PKTLEN      = 0x06, // PKTLEN Packet length
    CC1101_PKTCTRL1    = 0x07, // PKTCTRL1 Packet automation control
    CC1101_PKTCTRL0    = 0x08, // PKTCTRL0 Packet automation control
    CC1101_ADDR        = 0x09, // ADDR Device address
    CC1101_CHANNR      = 0x0A, // CHANNR Channel number
    CC1101_FSCTRL1     = 0x0B, // FSCTRL1 Frequency synthesizer control
    CC1101_FSCTRL0     = 0x0C, // FSCTRL0 Frequency synthesizer control
    CC1101_FREQ2       = 0x0D, // FREQ2 Frequency control word, high byte
    CC1101_FREQ1       = 0x0E, // FREQ1 Frequency control word, middle byte
    CC1101_FREQ0       = 0x0F, // FREQ0 Frequency control word, low byte
    CC1101_MDMCFG4     = 0x10, // MDMCFG4 Modem configuration
    CC1101_MDMCFG3     = 0x11, // MDMCFG3 Modem configuration
    CC1101_MDMCFG2     = 0x12, // MDMCFG2 Modem configuration
    CC1101_MDMCFG1     = 0x13, // MDMCFG1 Modem configuration
    CC1101_MDMCFG0     = 0x14, // MDMCFG0 Modem configuration
    CC1101_DEVIATN     = 0x15, // DEVIATN Modem deviation setting
    CC1101_MCSM2       = 0x16, // MCSM2 Main Radio Control State Machine configuration
    CC1101_MCSM1       = 0x17, // MCSM1 Main Radio Control State Machine configuration
    CC1101_MCSM0       = 0x18, // MCSM0 Main Radio Control State Machine configuration
    CC1101_FOCCFG      = 0x19, // FOCCFG Frequency Offset Compensation configuration
    CC1101_BSCFG       = 0x1A, // BSCFG Bit Synchronization configuration
    CC1101_AGCCTRL2    = 0x1B, // AGCTRL2 AGC control
    CC1101_AGCCTRL1    = 0x1C, // AGCTRL1 AGC control
    CC1101_AGCCTRL0    = 0x1D, // AGCTRL0 AGC control
    CC1101_WOREVT1     = 0x1E, // WOREVT1 High byte Event 0 timeout
    CC1101_WOREVT0     = 0x1F, // WOREVT0 Low byte Event 0 timeout
    CC1101_WORCTRL     = 0x20, // WORCTRL Wake On Radio control
    CC1101_FREND1      = 0x21, // FREND1 Front end RX configuration
    CC1101_FREND0      = 0x22, // FREND0 Front end TX configuration
    CC1101_FSCAL3      = 0x23, // FSCAL3 Frequency synthesizer calibration
    CC1101_FSCAL2      = 0x24, // FSCAL2 Frequency synthesizer calibration
    CC1101_FSCAL1      = 0x25, // FSCAL1 Frequency synthesizer calibration
    CC1101_FSCAL0      = 0x26, // FSCAL0 Frequency synthesizer calibration
    CC1101_RCCTRL1     = 0x27, // RCCTRL1 RC oscillator configuration
    CC1101_RCCTRL0     = 0x28, // RCCTRL0 RC oscillator configuration
    CC1101_FSTEST      = 0x29, // FSTEST Frequency synthesizer calibration control
    CC1101_PTEST       = 0x2A, // PTEST Production test
    CC1101_AGCTEST     = 0x2B, // AGCTEST AGC test
    CC1101_TEST2       = 0x2C, // TEST2 Various test settings
    CC1101_TEST1       = 0x2D, // TEST1 Various test settings
    CC1101_TEST0       = 0x2E  // TEST0 Various test settings 2
} cc1101_configuration_register_t;

typedef enum
{
    CC1101_SRES     = 0x30, // Reset chip.
    CC1101_SFSTXON  = 0x31, // Enable and calibrate frequency synthesizer (if MCSM0.FS_AUTOCAL=1). If in RX (with CCA): Go to a wait state where only the synthesizer is running (for quick RX / TX turnaround).
    CC1101_SXOFF    = 0x32, // Turn off crystal oscillator.
    CC1101_SCAL     = 0x33, // Calibrate frequency synthesizer and turn it off. SCAL can be strobed from IDLE mode without setting manual calibration mode (MCSM0.FS_AUTOCAL=0)
    CC1101_SRX      = 0x34, // Enable RX. Perform calibration first if coming from IDLE and MCSM0.FS_AUTOCAL=1.
    CC1101_STX      = 0x35, // In IDLE state: Enable TX. Perform calibration first if MCSM0.FS_AUTOCAL=1. If in RX state and CCA is enabled: Only go to TX if channel is clear.
    
    CC1101_SIDLE    = 0x37, // Exit RX / TX, turn off frequency synthesizer and exit Wake-On-Radio mode if applicable.
    CC1101_SWOR     = 0x38, // Start automatic RX polling sequence (Wake-on-Radio) as described in Section 19.5 if WORCTRL.RC_PD=0.
    CC1101_SPWD     = 0x39, // Enter power down mode when CSn goes high.
    CC1101_SFRX     = 0x3A, // Flush the RX FIFO buffer. Only issue SFRX in IDLE or RXFIFO_OVERFLOW states.
    CC1101_SFTX     = 0x3B, // Flush the TX FIFO buffer. Only issue SFTX in IDLE or TXFIFO_UNDERFLOW states.
    CC1101_SWORRST  = 0x3C, // Reset real time clock to Event1 value.
    CC1101_SNOP     = 0x3D  // No operation. May be used to get access to the chip status byte.
} cc1101_command_strobe_t;

typedef enum 
{
    PARTNUM         = 0x30, // Part number for CC1101
    VERSION         = 0x31, // Current version number
    FREQEST         = 0x32, // Frequency Offset Estimate
    LQI             = 0x33, // Demodulator estimate for Link Quality
    RSSI            = 0x34, // Received signal strength indication
    MARCSTATE       = 0x35, // Control state machine state 
    WORTIME1        = 0x36, // High byte of WOR timer
    WORTIME0        = 0x37, // Low byte of WOR timer 
    PKTSTATUS       = 0x38, // Current GDOx status and packet status 
    VCO_VC_DAC      = 0x3A, // Current setting from PLL calibration module
    TXBYTES         = 0x3B, // Underflow and number of bytes in the TX FIFO
    RXBYTES         = 0x3C, // Overflow and number of bytes in the RX FIFO
    RCCTRL1_STATUS  = 0x3D, // Last RC oscillator calibration result
    RCCTRL0_STATUS  = 0x3E, // Last RC oscillator calibration result
} cc1101_status_register_t;













