//##############################################################################
//
// FILE:   usb_hal.c
//
// TITLE:  Wrapper for interrupt functions and USB support pins.
//
//##############################################################################
//
//
// $Copyright:
// Copyright (C) 2014-2023 Texas Instruments Incorporated - http://www.ti.com/
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

//
// Include Files.
//
#include "usb_hal.h"

//******************************************************************************
//
//! \addtogroup c2000_specific
//! @{
//
//******************************************************************************
//******************************************************************************
//
//! Enables USB related GPIOs to perform their USB function.
//
//******************************************************************************
void USBGPIOEnable(void)
{
    //
    // Set the USB DM and DP.
    //
    GPIO_setMasterCore(42, GPIO_CORE_CPU1);
    GPIO_setAnalogMode(42, GPIO_ANALOG_ENABLED);
    GPIO_setMasterCore(43, GPIO_CORE_CPU1);
    GPIO_setAnalogMode(43, GPIO_ANALOG_ENABLED);

    //
    // Set the direction for VBUS.
    //
    GPIO_setMasterCore(46, GPIO_CORE_CPU1);
    GPIO_setDirectionMode(46, GPIO_DIR_MODE_IN);

    //
    // Set the direction for ID.
    //
    GPIO_setMasterCore(47, GPIO_CORE_CPU1);
    GPIO_setDirectionMode(47, GPIO_DIR_MODE_IN);

    GPIO_setMasterCore(120, GPIO_CORE_CPU1);
    GPIO_setDirectionMode(120, GPIO_DIR_MODE_IN);

    GPIO_setMasterCore(121, GPIO_CORE_CPU1);
	GPIO_setDirectionMode(121, GPIO_DIR_MODE_OUT);
	GPIO_writePin(121, 1);
}

//******************************************************************************
//
//! Configure the CPU Timer.
//
//******************************************************************************
void CPUTimerInit(void)
{
    //
    // Initialize timer period to maximum.
    //
    CPUTimer_setPeriod(CPUTIMER0_BASE,0xFFFFFFFF);

    //
    // Initialize Pre-scale counter to divide by 1.
    //
    CPUTimer_setPreScaler(CPUTIMER0_BASE, 0U);

    //
    // Make sure timer is stopped.
    //
    CPUTimer_stopTimer(CPUTIMER0_BASE);

    //
    // Reload all counter register with period value:
    //
    CPUTimer_reloadTimerCounter(CPUTIMER0_BASE);
}
//******************************************************************************
//
//! Wrapper function to implement mS based delay for USB functions
//
//******************************************************************************
void USBDelay(uint32_t ui32Delay)
{
    DEVICE_DELAY_US(ui32Delay*1000);
}


//******************************************************************************
//
//! Dual mode interrupt service routine wrapper to make ISR compatible with
//! C2000 PIE controller.
//
//******************************************************************************
__interrupt void
f28x_USB0DualModeIntHandler(void)
{
    USB0DualModeIntHandler();
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
}

//******************************************************************************
//
//! Dual mode interrupt service routine wrapper to make ISR compatible with
//! C2000 PIE controller.
//
//******************************************************************************
__interrupt void
f28x_USB0OTGModeIntHandler(void)
{
    USB0OTGModeIntHandler();
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
}

//******************************************************************************
//
// Close the c2000_specific Doxygen group.
//! @}
//
//******************************************************************************
