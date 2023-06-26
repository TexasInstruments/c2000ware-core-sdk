//###########################################################################
//
// FILE:   usb_ids.h
//
// TITLE:  Definitions of VIDs and PIDs used by TI USB examples.
//
//###########################################################################
// $TI Release: F2806x C/C++ Header Files and Peripheral Examples V141 $
// $Release Date: January 19, 2015 $
// $Copyright: Copyright (C) 2011-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef __USBIDS_H__
#define __USBIDS_H__

//*****************************************************************************
//
// TI C2000 Vendor ID.
//
//*****************************************************************************
#define USB_VID_C2000       0x1cbe

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
#define USB_PID_DFU             0x00FF

#ifndef DEPRECATED
//*****************************************************************************
//
// Deprecated definitions.
//
//*****************************************************************************
#define USB_VID_TI        USB_VID_C2000
#endif

#endif /* __USBIDS_H__ */
