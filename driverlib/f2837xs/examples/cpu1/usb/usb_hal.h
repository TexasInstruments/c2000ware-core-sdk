//##############################################################################
//
// FILE:   usb_hal.h
//
// TITLE:  Compatability layer for ported software.
//
//##############################################################################
//
//
// $Copyright:
// Copyright (C) 2014-2025 Texas Instruments Incorporated - http://www.ti.com/
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
//##############################################################################

#ifndef USB_HAL_H
#define USB_HAL_H

//******************************************************************************
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//******************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "usblib.h"
#include "usblibpriv.h"
#include "device/usbdevice.h"
#include "host/usbhost.h"
#include "host/usbhostpriv.h"
#include "usblibpriv.h"

//
// Defines.
//

//
// Define to pass to SysCtl_setAuxClock(). Will configure the clock as follows:
// AUXPLLCLK =
//       20MHz (XTAL_OSC) * 12 (IMULT) / (4 (SYSDIV) )
//
#define DEVICE_AUXSETCLOCK_CFG_USB   (SYSCTL_OSCSRC_XTAL | SYSCTL_PLL_ENABLE |\
                                      SYSCTL_IMULT(12) | SYSCTL_SYSDIV(4))

//******************************************************************************
//! \addtogroup c2000_specific
//! @{
//******************************************************************************
extern void USBGPIOEnable(void);
extern void CPUTimerInit(void);
extern void USBDelay(uint32_t ui32Delay);
extern void f28x_USB0DualModeIntHandler(void);
extern void f28x_USB0OTGModeIntHandler(void);

//******************************************************************************
// Mark the end of the C bindings section for C++ compilers.
//******************************************************************************
#ifdef __cplusplus
}
#endif

//******************************************************************************
// Close the Doxygen group.
//! @}
//******************************************************************************

#endif //  USB_HAL_H
