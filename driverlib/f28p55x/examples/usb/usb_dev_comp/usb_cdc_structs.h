
#ifndef _USB_CDC_STRUCTS_H_
#define _USB_CDC_STRUCTS_H_

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_types.h"
#include "usb.h"
#include "usblib.h"
#include "usb_ids.h"

#include "device/usbdevice.h"

#include "usbcdc.h"
#include "device/usbdcdc.h"

//
// Defines
//

//
// The size of the transmit and receive buffers used for the redirected SCI.
// This number should be a power of 2 for best performance.  256 is chosen
// pretty much at random though the buffer should be at least twice the size of
// a maximum-sized USB packet.
//
#define myUSB0_LIB_SCI_BUFFER_SIZE 256

//
// Globals
//
extern tUSBBuffer g_sTxBuffer;
extern tUSBBuffer g_sRxBuffer;
extern tUSBDCDCDevice g_sCDCDevice;
extern uint8_t g_pi8USBTxBuffer[];
extern uint8_t g_pi8USBRxBuffer[];

//
// Function Prototypes
//
extern uint32_t RxHandler(void *pvCBData, uint32_t ui32Event,
                          uint32_t ui32MsgValue, void *pvMsgData);
extern uint32_t TxHandler(void *pvi32CBData, uint32_t ui32Event,
                          uint32_t ui32MsgValue, void *pvMsgData);


#endif
