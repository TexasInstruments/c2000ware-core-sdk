//###########################################################################
//
// FILE:   sysctl.h
//
// TITLE:  Stellaris style wrapper driver for C28x system control.
//
//###########################################################################
// $TI Release: f2806x Support Library v1.15 $
// $Release Date: December 12, 2011 $
// $Copyright:
// Copyright (C) 2009-2024 Texas Instruments Incorporated - http://www.ti.com/
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
//###########################################################################

#ifndef __SYSCTL_H__
#define __SYSCTL_H__

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
//! \addtogroup sysctl_api
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! Defined System Clock Speed (CPU speed).  Adjust this to reflect your
//! actual clock speed.
//
//*****************************************************************************
#define SYSTEM_CLOCK_SPEED      80000000

//*****************************************************************************
//
// The following are values that can be passed to the
// SysCtlPeripheralPresent(), SysCtlPeripheralEnable(),
// SysCtlPeripheralDisable(), and SysCtlPeripheralReset() APIs as the
// ulPeripheral parameter.  The peripherals in the fourth group (upper nibble
// is 3) can only be used with the SysCtlPeripheralPresent() API.
//
//*****************************************************************************

#define SYSCTL_PERIPH_UART0     0x1  // SCI 0
#define SYSCTL_PERIPH_UART1     0x2  // SCI 1
#define SYSCTL_PERIPH_SPI0      0x3  // SPI 0
#define SYSCTL_PERIPH_SPI1      0x4  // SPI 1
#define SYSCTL_PERIPH_DMA       0x5  // uDMA
#define SYSCTL_PERIPH_USB0      0x6  // USB0

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

    extern void SysCtlPeripheralReset(unsigned long ulPeripheral);
    extern void SysCtlPeripheralEnable(unsigned long ulPeripheral);
    extern void SysCtlPeripheralDisable(unsigned long ulPeripheral);
    extern tBoolean SysCtlPeripheralPresent(unsigned long ulPeripheral);
    extern void SysCtlDelay(unsigned long ulCount);
    extern unsigned long SysCtlClockGet(unsigned long ulClockIn);
    extern void SysCtlUSBPLLEnable(void);
    extern void SysCtlUSBPLLDisable(void);

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//****************************************************************************    

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __SYSCTL_H__


