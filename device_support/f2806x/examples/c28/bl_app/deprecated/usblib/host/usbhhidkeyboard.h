//###########################################################################
//
// FILE:   usbhhidkeyboard.h
//
// TITLE:  This file holds the application interfaces for USB
//         keyboard devices.
//
//###########################################################################
// $TI Release: F2806x C/C++ Header Files and Peripheral Examples V141 $
// $Release Date: January 19, 2015 $
// $Copyright: Copyright (C) 2011-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef __USBHHIDKEYBOARD_H__
#define __USBHHIDKEYBOARD_H__

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

    extern unsigned long USBHKeyboardOpen(tUSBCallback pfnCallback,
                                          unsigned char *pucBuffer,
                                          unsigned long ulBufferSize);
    extern unsigned long USBHKeyboardClose(unsigned long ulInstance);
    extern unsigned long USBHKeyboardInit(unsigned long ulInstance);
    extern unsigned long USBHKeyboardModifierSet(unsigned long ulInstance,
            unsigned long ulModifiers);
    extern unsigned long USBHKeyboardPollRateSet(unsigned long ulInstance,
            unsigned long ulPollRate);

    extern unsigned long USBHKeyboardUsageToChar(
        unsigned long ulInstance,
        const tHIDKeyboardUsageTable *pTable,
        unsigned char ucUsageID);

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

#endif


