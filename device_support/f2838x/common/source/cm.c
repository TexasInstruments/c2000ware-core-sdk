//#############################################################################
//
// FILE:   cm.c
//
// TITLE:   Communication manager setup for examples.
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com
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
//#############################################################################

//
// Included Files
//
#include "cm.h"

//*****************************************************************************
//
// Function to initialize the device. Primarily initializes system control to a
// known state by disabling the watchdog and enabling the clocks to the peripherals.
//
//*****************************************************************************
void CM_init(void)
{
    //
    // Disable the watchdog
    //
    SysCtl_disableWatchdog();

#ifdef _FLASH
    //
    // Copy time critical code and flash setup code to RAM. This includes the
    // following functions: InitFlash();
    //
    // The RamfuncsLoadStart, RamfuncsLoadSize, and RamfuncsRunStart symbols
    // are created by the linker. Refer to the device .cmd file.
    //
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);

    //
    // Call Flash Initialization to setup flash waitstates. This function must
    // reside in RAM.
    //
    Flash_initModule(FLASH0CTRL_BASE, FLASH0ECC_BASE, DEVICE_FLASH_WAITSTATES);
#endif

    //
    // Turn on all peripherals
    //
    CM_enableAllPeripherals();

    //
    // Sets the NVIC vector table offset address.
    //
#ifdef _FLASH
    Interrupt_setVectorTableOffset((uint32_t)vectorTableFlash);
#else
    Interrupt_setVectorTableOffset((uint32_t)vectorTableRAM);
#endif
    
}

//*****************************************************************************
//
// Function to turn on all peripherals, enabling reads and writes to the
// peripherals' registers.
//
// Note that to reduce power, unused peripherals should be disabled.
//
//*****************************************************************************
void CM_enableAllPeripherals(void)
{

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_UART0);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SSI0);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_I2C0);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_USB);
    
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ENET);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAT);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CAN_A);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CAN_B);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_MCAN_A);
    
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TIMER0);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TIMER1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TIMER2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_UDMA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_AESIP);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_GCRC);

}

//*****************************************************************************
//
// Error handling function to be called when an ASSERT is violated
//
//*****************************************************************************
void __error__(const char *filename, uint32_t line)
{
    //
    // An ASSERT condition was evaluated as false. You can use the filename and
    // line parameters to determine what went wrong.
    //
    __asm("   bkpt #0");
}
