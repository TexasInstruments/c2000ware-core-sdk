//#############################################################################
// FILE: usb_ids.h
// TITLE: Definitions of VIDs and PIDs used by C2000 USB examples.
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

#ifndef __USBIDS_H__
#define __USBIDS_H__

//*****************************************************************************
//
// TI Vendor ID for devices that use VID as 0x1CBE.
//
//*****************************************************************************
#define USB_VID_TI_1CBE         0x1cbe

//*****************************************************************************
//
// Product IDs.
//
//*****************************************************************************
#define USB_PID_MOUSE           0x0000
#define USB_PID_KEYBOARD        0x0001
#define USB_PID_SERIAL          0x0002
#define USB_PID_BULK            0x0003
#define USB_PID_SCOPE           0x0004
#define USB_PID_MSC             0x0005
#define USB_PID_AUDIO           0x0006
#define USB_PID_COMP_SERIAL     0x0007
#define USB_PID_COMP_AUDIO_HID  0x0008
#define USB_PID_COMP_HID_SER    0x0009
#define USB_PID_COMP_HID_DFU    0x000A
#define USB_PID_DATA_LOGGER     0x000B
#define USB_PID_COMP_HID_HID    0x000D
#define USB_PID_DFU             0x00FF

#endif /* __USBIDS_H__ */
