//##############################################################################
//
// FILE:   usb_hal.h
//
// TITLE:  Compatability layer for ported software.
//
//##############################################################################
//
//
// 
// C2000Ware v6.00.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
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
#ifdef USE_20MHZ_XTAL
//
// Define to pass to SysCtl_setAuxClock(). Will configure the clock as follows:
// AUXPLLCLK =
//       20MHz (XTAL_OSC) * 48 (IMULT) / (2 (REFDIV) * 4 (ODIV) * 2(AUXPLLDIV) )
//
// AUXPLLRAWCLK = 120MHz (before the AUXCLK divider)
// USB clock    = 60MHz  (after the AUXCLK divider)
//
#define DEVICE_AUXSETCLOCK_CONFIG_USB   (SYSCTL_AUXPLL_OSCSRC_XTAL        |   \
                                      SYSCTL_AUXPLL_IMULT(48)             |   \
                                      SYSCTL_REFDIV(2U) | SYSCTL_ODIV(4U) |   \
                                      SYSCTL_AUXPLL_DIV_2                 |   \
                                      SYSCTL_AUXPLL_ENABLE                |   \
                                      SYSCTL_DCC_BASE_0)
#else
//
// Define to pass to SysCtl_setAuxClock(). Will configure the clock as follows:
// AUXPLLCLK =
//       25MHz (XTAL_OSC) * 48 (IMULT) / (2 (REFDIV) * 5 (ODIV) * 2(AUXPLLDIV) )
//
// AUXPLLRAWCLK = 120MHz (before the AUXCLK divider)
// USB clock    = 60MHz  (after the AUXCLK divider)
//
#define DEVICE_AUXSETCLOCK_CONFIG_USB   (SYSCTL_AUXPLL_OSCSRC_XTAL        |   \
                                      SYSCTL_AUXPLL_IMULT(48)             |   \
                                      SYSCTL_REFDIV(2U) | SYSCTL_ODIV(5U) |   \
                                      SYSCTL_AUXPLL_DIV_2                 |   \
                                      SYSCTL_AUXPLL_ENABLE                |   \
                                      SYSCTL_DCC_BASE_0)
#endif

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
