//###########################################################################
//
// FILE:   usbdevicepriv.h
//
// TITLE:  Private header file used to share internal variables and
//         function prototypes between the various device-related
//         modules in the USB library.  This header MUST NOT be
//         used by application code.
//
//###########################################################################
// $TI Release: F2806x C/C++ Header Files and Peripheral Examples V141 $
// $Release Date: January 19, 2015 $
// $Copyright: Copyright (C) 2011-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef __USBDEVICEPRIV_H__
#define __USBDEVICEPRIV_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// The states for endpoint zero during enumeration.
//
//*****************************************************************************
typedef enum
{
    //
    // The USB device is waiting on a request from the host controller on
    // endpoint zero.
    //
    USB_STATE_IDLE,

    //
    // The USB device is sending data back to the host due to an IN request.
    //
    USB_STATE_TX,

    //
    // The USB device is sending the configuration descriptor back to the host
    // due to an IN request.
    //
    USB_STATE_TX_CONFIG,

    //
    // The USB device is receiving data from the host due to an OUT
    // request from the host.
    //
    USB_STATE_RX,

    //
    // The USB device has completed the IN or OUT request and is now waiting
    // for the host to acknowledge the end of the IN/OUT transaction.  This
    // is the status phase for a USB control transaction.
    //
    USB_STATE_STATUS,

    //
    // This endpoint has signaled a stall condition and is waiting for the
    // stall to be acknowledged by the host controller.
    //
    USB_STATE_STALL
}
tEP0State;

typedef struct tDeviceInfo tDeviceInfo;
typedef struct tDeviceInstance tDeviceInstance;

//*****************************************************************************
//
// The USB controller device information.
//
//*****************************************************************************
struct tDeviceInstance
{
    //
    // The device information for the USB device.
    //
    tDeviceInfo *psInfo;

    //
    // The instance data for the USB device.
    //
    void *pvInstance;

    //
    // The current state of endpoint zero.
    //
    volatile tEP0State eEP0State;

    //
    // The devices current address, this also has a change pending bit in the
    // MSB of this value specified by DEV_ADDR_PENDING.
    //
    volatile unsigned long ulDevAddress;

    //
    // This holds the current active configuration for this device.
    //
    unsigned long ulConfiguration;

    //
    // This holds the configuration id that will take effect after a reset.
    //
    unsigned long ulDefaultConfiguration;

    //
    // This holds the current alternate interface for this device.
    //
    unsigned char pucAltSetting[USB_MAX_INTERFACES_PER_DEVICE];

    //
    // This is the pointer to the current data being sent out or received
    // on endpoint zero.
    //
    unsigned char *pEP0Data;

    //
    // This is the number of bytes that remain to be sent from or received
    // into the g_sUSBDeviceState.pEP0Data data buffer.
    //
    volatile unsigned long ulEP0DataRemain;

    //
    // The amount of data being sent/received due to a custom request.
    //
    unsigned long ulOUTDataSize;

    //
    // Holds the current device status.
    //
    unsigned char ucStatus;

    //
    // Holds the endpoint status for the HALT condition.  This array is sized
    // to hold halt status for all IN and OUT endpoints.
    //
    unsigned char ucHalt[2][USBLIB_NUM_EP - 1];

    //
    // Holds the configuration descriptor section number currently being sent
    // to the host.
    //
    unsigned char ucConfigSection;

    //
    // Holds the offset within the configuration descriptor section currently
    // being sent to the host.
    //
    unsigned char ucSectionOffset;

    //
    // Holds the index of the configuration that we are currently sending back
    // to the host.
    //
    unsigned char ucConfigIndex;

    //
    // This flag is set to true if the client has called USBDPowerStatusSet
    // and tells the USB library not to try to determine the current power
    // status from the configuration descriptor.
    //
    tBoolean bPwrSrcSet;

    //
    // This flag indicates whether or not remote wake up signaling is in
    // progress.
    //
    tBoolean bRemoteWakeup;

    //
    // During remote wake up signaling, this counter is used to track the
    // number of milliseconds since the signaling was initiated.
    //
    unsigned char ucRemoteWakeupCount;
};

extern tDeviceInstance g_psUSBDevice[];

//*****************************************************************************
//
// Device enumeration functions provided by device/usbenum.c and called from
// the interrupt handler in device/usbhandler.c
//
//*****************************************************************************
extern tBoolean USBDeviceConfig(tDeviceInstance *psDevInst,
                                const tConfigHeader *psConfig);
extern tBoolean USBDeviceConfigAlternate(tDeviceInstance *psDevInst,
            const tConfigHeader *psConfig,
            unsigned char ucInterfaceNum,
            unsigned char ucAlternateSetting);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __USBDEVICEPRIV_H__


