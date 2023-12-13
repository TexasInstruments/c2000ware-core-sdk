//#############################################################################
// FILE: usbhhid.h
// TITLE: This hold the host driver for hid class
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

#ifndef __USBHHID_H__
#define __USBHHID_H__

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
//! \addtogroup usblib_host_class
//! @{
//
//*****************************************************************************

typedef struct tHIDInstance tHIDInstance;

//*****************************************************************************
//
// These defines are the the events that will be passed in the ui32Event
// parameter of the callback from the driver.
//
//*****************************************************************************
#define USBH_EVENT_HID_SETRPT   USBH_HID_EVENT_BASE + 0
#define USBH_EVENT_HID_REPORT   USBH_HID_EVENT_BASE + 1

//
//! The HID keyboard detected a key being pressed.
//
#define USBH_EVENT_HID_KB_PRESS USBH_HID_EVENT_BASE + 16

//
//! The HID keyboard detected a key being released.
//
#define USBH_EVENT_HID_KB_REL   USBH_HID_EVENT_BASE + 17

//
//! The HID keyboard detected one of the keyboard modifiers being pressed.
//
#define USBH_EVENT_HID_KB_MOD   USBH_HID_EVENT_BASE + 18

//
//! A button was pressed on a HID mouse.
//
#define USBH_EVENT_HID_MS_PRESS USBH_HID_EVENT_BASE + 32

//
//! A button was released on a HID mouse.
//
#define USBH_EVENT_HID_MS_REL   USBH_HID_EVENT_BASE + 33

//
//! The HID mouse detected movement in the X direction.
//
#define USBH_EVENT_HID_MS_X     USBH_HID_EVENT_BASE + 34

//
//! The HID mouse detected movement in the Y direction.
//
#define USBH_EVENT_HID_MS_Y     USBH_HID_EVENT_BASE + 35

//*****************************************************************************
//
//! The following values are used to register callbacks to the USB HOST HID
//! device class layer.
//
//*****************************************************************************
typedef enum
{
    //
    //! No device should be used.  This value should not be used by
    //! applications.
    //
    eUSBHHIDClassNone = 0,

    //
    //! This is a keyboard device.
    //
    eUSBHHIDClassKeyboard,

    //
    //! This is a mouse device.
    //
    eUSBHHIDClassMouse,

    //
    //! This is a vendor specific device.
    //
    eUSBHHIDClassVendor
}
tHIDSubClassProtocol;

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Prototypes.
//
//*****************************************************************************
extern tHIDInstance * USBHHIDOpen(tHIDSubClassProtocol iDeviceType,
                                  tUSBCallback pfnCallback,
                                  void *pvCBData);
extern void USBHHIDClose(tHIDInstance *psHIDInstance);
extern uint32_t USBHHIDGetReportDescriptor(tHIDInstance *psHIDInstance,
                                           uint8_t *pui8Buffer,
                                           uint32_t ui32Size);
extern uint32_t USBHHIDSetIdle(tHIDInstance *psHIDInstance, uint8_t ui8Duration,
                               uint8_t ui8ReportID);
extern uint32_t USBHHIDSetProtocol(tHIDInstance *psHIDInstance,
                                   uint32_t ui32BootProtocol);
extern uint32_t USBHHIDSetReport(tHIDInstance *psHIDInstance,
                                 uint32_t ui32Interface, uint8_t *pui8Data,
                                 uint32_t ui32Size);
extern uint32_t USBHHIDGetReport(tHIDInstance *psHIDInstance,
                                 uint32_t ui32Interface, uint8_t *pui8Data,
                                 uint32_t ui32Size);

extern const tUSBHostClassDriver g_sUSBHIDClassDriver;

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __USBHHID_H__
