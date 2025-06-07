//#############################################################################
// FILE: usbhost.h
// TITLE: Host specific definitions for the USB host library
//#############################################################################
// $TI Release: $
// $Release Date: $
// $Copyright:
// Copyright (C) 2009-2025 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef __USBHOST_H__
#define __USBHOST_H__

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
//! \addtogroup usblib_hcd
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
// This is the type used to identify what the pipe is currently in use for.
//
//*****************************************************************************
#define USBHCD_PIPE_UNUSED          0x00100000
#define USBHCD_PIPE_CONTROL         0x00130000
#define USBHCD_PIPE_BULK_OUT        0x00210000
#define USBHCD_PIPE_BULK_IN         0x00220000
#define USBHCD_PIPE_INTR_OUT        0x00410000
#define USBHCD_PIPE_INTR_IN         0x00420000
#define USBHCD_PIPE_ISOC_OUT        0x00810000
#define USBHCD_PIPE_ISOC_IN         0x00820000
#define USBHCD_PIPE_ISOC_OUT_DMA    0x01810000
#define USBHCD_PIPE_ISOC_IN_DMA     0x01820000
#define USBHCD_PIPE_BULK_OUT_DMA    0x01210000
#define USBHCD_PIPE_BULK_IN_DMA     0x01220000

//*****************************************************************************
//
// These are the defines that are used with USBHCDPowerConfigInit().
//
//*****************************************************************************
#define USBHCD_FAULT_LOW        0x00000010
#define USBHCD_FAULT_HIGH       0x00000030
#define USBHCD_FAULT_VBUS_NONE  0x00000000
#define USBHCD_FAULT_VBUS_TRI   0x00000140
#define USBHCD_FAULT_VBUS_DIS   0x00000400
#define USBHCD_VBUS_MANUAL      0x00000004
#define USBHCD_VBUS_AUTO_LOW    0x00000002
#define USBHCD_VBUS_AUTO_HIGH   0x00000003
#define USBHCD_VBUS_FILTER      0x00010000

//*****************************************************************************
//
//! This macro is used to declare an instance of an Event driver for the USB
//! library.
//!
//! \param VarName is the name of the variable.
//! \param pfnOpen is the callback for the Open call to this driver.  This
//! value is currently reserved and should be set to 0.
//! \param pfnClose is the callback for the Close call to this driver.  This
//! value is currently reserved and should be set to 0.
//! \param pfnEvent is the callback that will be called for various USB events.
//!
//! The first parameter is the actual name of the variable that will
//! be declared by this macro.  The second and third parameter are reserved
//! for future functionality and are unused and should be set to zero.  The
//! last parameter is the actual callback function and is specified as
//! a function pointer of the type:
//!
//! void (*pfnEvent)(void *pvData);
//!
//! When the \e pfnEvent function is called the void pointer that is passed in
//! as a parameter should be cast to a pointer to a structure of type
//! tEventInfo.  This will contain the event that caused the pfnEvent function
//! to be called.
//
//*****************************************************************************
#define DECLARE_EVENT_DRIVER(VarName, pfnOpen, pfnClose, pfnEvent)          \
void IntFn(void *pvData);                                                   \
const tUSBHostClassDriver VarName =                                         \
{                                                                           \
    USB_CLASS_EVENTS,                                                       \
    0,                                                                      \
    0,                                                                      \
    pfnEvent                                                                \
}

//*****************************************************************************
//
// This is the type definition a callback for events on USB Pipes allocated
// by USBHCDPipeAlloc().
//
// \param ui32Pipe is well the pipe
// \param ui32Event is well the event
//
// This prototype is used by any Pipe callbacks that are used in the host
// class drivers.  These functions typically handle data events like
// USB_EVENT_RX_AVAILABLE or USB_EVENT_TX_COMPLETE but can be sent other events
// depending on the USB host class in use.  See the documentation for the
// individual classes for the valid events for that class.
//
// \return None.
//
//*****************************************************************************
typedef void (* tHCDPipeCallback)(uint32_t ui32Pipe, uint32_t ui32Event);

//*****************************************************************************
//
// Predeclare the private tUSBHostDevice structure.
//
//*****************************************************************************
typedef struct tUSBHostDevice tUSBHostDevice;

//*****************************************************************************
//
//! This structure defines a USB host class driver interface, it is parsed to
//! find a USB class driver once a USB device is enumerated.
//
//*****************************************************************************
typedef struct
{
    //
    //! The interface class that this device class driver supports.
    //
    uint32_t ui32InterfaceClass;

    //
    //! The function is called when this class of device has been detected.
    //
    void *(*pfnOpen)(tUSBHostDevice *psDevice);

    //
    //! The function is called when the device, originally opened with a call
    //! to the pfnOpen function, is disconnected.
    //
    void (*pfnClose)(void *pvInstance);

    //
    //! This is the optional interrupt handler that will be called when an
    //! endpoint associated with this device instance generates an interrupt.
    //
    void (*pfnIntHandler)(void *pvInstance);
}
tUSBHostClassDriver;

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// If the g_USBEventDriver is included in the host controller driver list then
// this function must be provided by the application.
//
//*****************************************************************************
extern void USBHCDEvents(void *pvData);

//*****************************************************************************
//
// Prototypes for the USB Host controller APIs.
//
//*****************************************************************************
extern void USBHCDMain(void);
extern int32_t USBHCDEventEnable(uint32_t ui32Index, void *pvEventDriver,
                                 uint32_t ui32Event);
extern int32_t USBHCDEventDisable(uint32_t ui32Index, void *pvEventDriver,
                                  uint32_t ui32Event);
extern void USBHCDInit(uint32_t ui32Index, void *pvData,
                       uint32_t ui32Size);
extern void USBHCDPowerConfigInit(uint32_t ui32Index,
                                  uint32_t ui32Flags);
extern uint32_t USBHCDPowerConfigGet(uint32_t ui32Index);
extern uint32_t USBHCDPowerConfigSet(uint32_t ui32Index,
                                     uint32_t ui32Config);
extern uint32_t USBHCDPowerAutomatic(uint32_t ui32Index);
extern void USBHCDRegisterDrivers(uint32_t ui32Index,
                            const tUSBHostClassDriver * const *ppsHClassDrvrs,
                            uint32_t ui32NumDrivers);
extern void USBHCDTerm(uint32_t ui32Index);
extern void USBHCDSetConfig(uint32_t ui32Index, uint32_t ui32Device,
                            uint32_t ui32Configuration);
extern void USBHCDSetInterface(uint32_t ui32Index, uint32_t ui32Device,
                               uint32_t ui32Interface,
                               uint32_t ui32AltSetting);
extern void USBHCDSuspend(uint32_t ui32Index);
extern void USBHCDResume(uint32_t ui32Index);
extern void USBHCDReset(uint32_t ui32Index);
extern void USBHCDPipeFree(uint32_t ui32Pipe);
extern uint32_t USBHCDPipeAlloc(uint32_t ui32Index,
                                uint32_t ui32EndpointType,
                                tUSBHostDevice *psDevice,
                                tHCDPipeCallback pfnCallback);
extern uint32_t USBHCDPipeAllocSize(uint32_t ui32Index,
                                     uint32_t ui32EndpointType,
                                     tUSBHostDevice *psDevice,
                                     uint32_t ui32FIFOSize,
                                     tHCDPipeCallback pfnCallback);
extern uint32_t USBHCDPipeConfig(uint32_t ui32Pipe, uint32_t ui32MaxPayload,
                                 uint32_t ui32Interval,
                                 uint32_t ui32TargetEndpoint);
extern uint32_t USBHCDPipeStatus(uint32_t ui32Pipe);
extern uint32_t USBHCDPipeWrite(uint32_t ui32Pipe, uint8_t *pui8Data,
                                uint32_t ui32Size);
extern uint32_t USBHCDPipeRead(uint32_t ui32Pipe, uint8_t *pui8Data,
                               uint32_t ui32Size);
extern uint32_t USBHCDPipeSchedule(uint32_t ui32Pipe, uint8_t *pui8Data,
                                   uint32_t ui32Size);
extern void USBHCDPipeDataAck(uint32_t ui32Pipe);
extern uint32_t USBHCDPipeReadNonBlocking(uint32_t ui32Pipe, uint8_t *pui8Data,
                                          uint32_t ui32Size);
extern uint32_t USBHCDControlTransfer(uint32_t ui32Index,
                                      tUSBRequest *psSetupPacket,
                                      tUSBHostDevice *psDevice,
                                      uint8_t *pui8Data, uint32_t ui32Size,
                                      uint32_t ui32MaxPacketSize);
extern void USB0HostIntHandler(void);

extern uint8_t USBHCDDevHubPort(uint32_t ui32Instance);
extern uint8_t USBHCDDevAddress(uint32_t ui32Instance);
extern uint8_t USBHCDDevClass(uint32_t ui32Instance, uint32_t ui32Interface);
extern uint8_t USBHCDDevSubClass(uint32_t ui32Instance,
                                 uint32_t ui32Interface);
extern uint8_t USBHCDDevProtocol(uint32_t ui32Instance,
                                 uint32_t ui32Interface);

//*****************************************************************************
//
// The host class drivers supported by the USB library.
//
//*****************************************************************************
extern const tUSBHostClassDriver g_sUSBHostMSCClassDriver;
extern const tUSBHostClassDriver g_sUSBHIDClassDriver;
extern const tUSBHostClassDriver g_sUSBHostAudioClassDriver;

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __USBHOST_H__
