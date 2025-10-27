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
// C2000Ware v6.00.01.00
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
#include "cm.h"
#include "usblib.h"
#include "usblibpriv.h"
#include "device/usbdevice.h"
#include "host/usbhost.h"
#include "host/usbhostpriv.h"
#include "usblibpriv.h"

//
// CM Clock given to UART Module to enable USB to UART communication.
//
#define UART_CLK_FREQ_USB 120000000

//******************************************************************************
//
// USB HAL API Prototypes
//
//******************************************************************************
extern void USBDelay(uint32_t ui32Delay);
extern void CM_USB0DeviceIntHandler(void);
extern void CM_USB0HostIntHandler(void);

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
