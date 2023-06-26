//###########################################################################
//
// FILE:   usbhmsc.h
//
// TITLE:  Definitions for the USB MSC host driver.
//
//###########################################################################
// $TI Release: F2806x C/C++ Header Files and Peripheral Examples V141 $
// $Release Date: January 19, 2015 $
// $Copyright: Copyright (C) 2011-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef __USBHMSC_H__
#define __USBHMSC_H__

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
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
// These defines are the the events that will be passed in the \e ulEvent
// parameter of the callback from the driver.
//
//*****************************************************************************
#define MSC_EVENT_OPEN          1
#define MSC_EVENT_CLOSE         2

//*****************************************************************************
//
// The prototype for the USB MSC host driver callback function.
//
//*****************************************************************************
    typedef void (*tUSBHMSCCallback)(unsigned long ulInstance,
                                     unsigned long ulEvent,
                                     void *pvEventData);

//*****************************************************************************
//
// Prototypes for the USB MSC host driver APIs.
//
//*****************************************************************************
    extern unsigned long USBHMSCDriveOpen(unsigned long ulDrive,
                                          tUSBHMSCCallback pfnCallback);
    extern void USBHMSCDriveClose(unsigned long ulInstance);
    extern long USBHMSCDriveReady(unsigned long ulInstance);
    extern long USBHMSCBlockRead(unsigned long ulInstance, unsigned long ulLBA,
                                 unsigned char *pucData,
                                 unsigned long ulNumBlocks);
    extern long USBHMSCBlockWrite(unsigned long ulInstance, unsigned long ulLBA,
                                  unsigned char *pucData,
                                  unsigned long ulNumBlocks);

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __USBHMSC_H__


