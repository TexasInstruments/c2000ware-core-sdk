//#############################################################################
// FILE: usbdevicepriv.h
// TITLE: Private header file used to share internal variables and
//        modules in the USB library.  This header MUST NOT be
//        used by application code.
//#############################################################################
// $TI Release: $
// $Release Date: $
// $Copyright:
// Copyright (C) 2009-2023 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//#############################################################################

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
    eUSBStateIdle,

    //
    // The USB device is sending data back to the host due to an IN request.
    //
    eUSBStateTx,

    //
    // The USB device is sending the configuration descriptor back to the host
    // due to an IN request.
    //
    eUSBStateTxConfig,

    //
    // The USB device is receiving data from the host due to an OUT
    // request from the host.
    //
    eUSBStateRx,

    //
    // The USB device has completed the IN or OUT request and is now waiting
    // for the host to acknowledge the end of the IN/OUT transaction.  This
    // is the status phase for a USB control transaction.
    //
    eUSBStateStatus,

    //
    // This endpoint has signaled a stall condition and is waiting for the
    // stall to be acknowledged by the host controller.
    //
    eUSBStateStall
}
tEP0State;

typedef struct tDeviceInfo tDeviceInfo;

//*****************************************************************************
//
// The USB controller device information.
//
//*****************************************************************************
typedef struct
{
    //
    // The current state of endpoint zero.
    //
    volatile tEP0State iEP0State;

    //
    // The devices current address, this also has a change pending bit in the
    // MSB of this value specified by DEV_ADDR_PENDING.
    //
    volatile uint32_t ui32DevAddress;

    //
    // This holds the current active configuration for this device.
    //
    uint32_t ui32Configuration;

    //
    // This holds the configuration id that will take effect after a reset.
    //
    uint32_t ui32DefaultConfiguration;

    //
    // This holds the current alternate interface for this device.
    //
    uint8_t pui8AltSetting[USB_MAX_INTERFACES_PER_DEVICE];

    //
    // This is the pointer to the current data being sent out or received
    // on endpoint zero.
    //
    uint8_t *pui8EP0Data;

    //
    // This is the number of bytes that remain to be sent from or received
    // into the g_sUSBDeviceState.pui8EP0Data data buffer.
    //
    volatile uint32_t ui32EP0DataRemain;

    //
    // The amount of data being sent/received due to a custom request.
    //
    uint32_t ui32OUTDataSize;

    //
    // Holds the current device status.
    //
    uint8_t ui8Status;

    //
    // Holds the endpoint status for the HALT condition.  This array is sized
    // to hold halt status for all IN and OUT endpoints.
    //
    uint8_t ppui8Halt[2][USBLIB_NUM_EP - 1];

    //
    // Holds the configuration descriptor section number currently being sent
    // to the host.
    //
    uint8_t ui8ConfigSection;

    //
    // Holds the offset within the configuration descriptor section currently
    // being sent to the host.
    //
    uint8_t ui8SectionOffset;

    //
    // Holds the index of the configuration that we are currently sending back
    // to the host.
    //
    uint8_t ui8ConfigIndex;

    //
    // This flag is set to true if the client has called USBDPowerStatusSet()
    // and tells the USB library not to try to determine the current power
    // status from the configuration descriptor.
    //
    bool bPwrSrcSet;

    //
    // This flag indicates whether or not remote wake up signaling is in
    // progress.
    //
    bool bRemoteWakeup;

    //
    // During remote wake up signaling, this counter is used to track the
    // number of milliseconds since the signaling was initiated.
    //
    uint8_t ui8RemoteWakeupCount;

    //
    // The DMA instance information for this USB controller.
    //
    tUSBDMAInstance *psDMAInstance;

    //
    // The interrupt number for this instance.
    //
    uint32_t ui32IntNum;

    //
    // Pointer to the device supplied call back data.
    //
    void *pvCBData;
}
tDCDInstance;

extern tDCDInstance g_psDCDInst[];
extern tDeviceInfo *g_ppsDevInfo[];

//*****************************************************************************
//
// Device enumeration functions provided by device/usbenum.c and called from
// the interrupt handler in device/usbhandler.c
//
//*****************************************************************************
extern bool USBDeviceConfig(tDCDInstance *psDevInst,
                            const tConfigHeader *psConfig);
extern bool USBDeviceConfigAlternate(tDCDInstance *psDevInst,
                                     const tConfigHeader *psConfig,
                                     uint8_t ui8InterfaceNum,
                                     uint8_t ui8AlternateSetting);

extern void USBDCDDeviceInfoInit(uint32_t ui32Index, tDeviceInfo *psDevice);

//*****************************************************************************
//
// Macro access function to device information.
//
//*****************************************************************************
#define DCDGetDMAInstance(psDevInfo)    (&(psDevInfo->psDCDInst->sDMAInstance))

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __USBDEVICEPRIV_H__
