//#############################################################################
// FILE: usbdevicepriv.h
// TITLE: Private header file used to share internal variables and
//        modules in the USB library.  This header MUST NOT be
//        used by application code.
//#############################################################################
//!
//! Copyright: Copyright (C) 2023 Texas Instruments Incorporated -
//!	All rights reserved not granted herein.
//!	Limited License.
//!
//! Texas Instruments Incorporated grants a world-wide, royalty-free,
//! non-exclusive license under copyrights and patents it now or hereafter
//! owns or controls to make, have made, use, import, offer to sell and sell
//! ("Utilize") this software subject to the terms herein. With respect to the
//! foregoing patent license, such license is granted solely to the extent that
//! any such patent is necessary to Utilize the software alone. The patent
//! license shall not apply to any combinations which include this software,
//! other than combinations with devices manufactured by or for TI 
//! ("TI Devices").
//! No hardware patent is licensed hereunder.
//!
//! Redistributions must preserve existing copyright notices and reproduce this
//! license (including the above copyright notice and the disclaimer and
//! (if applicable) source code license limitations below) in the documentation
//!  and/or other materials provided with the distribution.
//!
//! Redistribution and use in binary form, without modification, are permitted
//! provided that the following conditions are met:
//!
//! * No reverse engineering, decompilation, or disassembly of this software is 
//! permitted with respect to any software provided in binary form.
//! * Any redistribution and use are licensed by TI for use only 
//!   with TI Devices.
//! * Nothing shall obligate TI to provide you with source code for the 
//!   software licensed and provided to you in object code.
//!
//! If software source code is provided to you, modification and redistribution
//! of the source code are permitted provided that the following conditions 
//! are met:
//!
//! * any redistribution and use of the source code, including any resulting
//!   derivative works, are licensed by TI for use only with TI Devices.
//! * any redistribution and use of any object code compiled from the source
//!   code and any resulting derivative works, are licensed by TI for use 
//!   only with TI Devices.
//!
//! Neither the name of Texas Instruments Incorporated nor the names of its
//! suppliers may be used to endorse or promote products derived from this 
//! software without specific prior written permission.
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
