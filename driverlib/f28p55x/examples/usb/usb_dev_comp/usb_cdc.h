#ifndef _USB_CDC_H
#define _USB_CDC_H

extern volatile bool g_bUSBConfigured;
extern char *g_pcStatus;
extern volatile uint32_t g_ui32Flags;
extern bool g_bSendingBreak;

extern volatile uint32_t g_ui32SCITxCount;
extern volatile uint32_t g_ui32SCIRxCount;

#define COMMAND_PACKET_RECEIVED 0x00000001
#define COMMAND_STATUS_UPDATE   0x00000002

//******************************************************************************
//
// Default line coding settings for the redirected SCI.
//
//******************************************************************************
#define DEFAULT_BIT_RATE        115200
#define DEFAULT_SCI_CONFIG     (SCI_CONFIG_WLEN_8 | SCI_CONFIG_PAR_NONE | \
                                SCI_CONFIG_STOP_ONE)

__interrupt void
USBSCITXIntHandler(void);

__interrupt void
USBSCIRXIntHandler(void);

void
ConfigureSCI(void);

void usb_cdc_sim_handler();

#endif
