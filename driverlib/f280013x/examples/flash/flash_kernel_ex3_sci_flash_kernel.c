//###########################################################################
//
// FILE:   flash_kernel_ex3_sci_flash_kernel.c
//
// TITLE:  Flash Programming Solution using SCI.
//
//! \addtogroup driver_example_list
//! <h1> Flash Programming Solution using SCI </h1>
//!
//! In this example, we set up a UART connection with a host using SCI, receive
//! commands for CPU1 to perform which then sends ACK, NAK, and status packets
//! back to the host after receiving and completing the tasks.  This kernel has
//! the ability to program, verify, unlock, reset, and run an application.
//! Each command either expects no data from the command packet
//! or specific data relative to the command.
//!
//! In this example, we set up a UART connection with a host using SCI, receive
//! an application for CPU01 in -sci8 ascii format to run on the device and
//! program it into Flash.
//!
//
//###########################################################################
// $Copyright:
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
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

//
// Included Files
//

#include <string.h>
#include "FlashTech_F280013x_C28x.h"
#include "cpu1brom_boot_modes.h"
#include "flash_programming_f280013x.h" // Flash API example header file
#include "cpu1bootrom.h"
#include "device.h"
#include "flash.h"
#include "gpio.h"
#include "interrupt.h"
#include "driverlib.h"


//
// Function Prototypes
//
void exampleError(Fapi_StatusType status);
void initFlashSectors(void);
extern uint32_t sciGetFunction(uint32_t BootMode);
extern void sciaFlush(void);

//
// Main
//
uint32_t main(void)
{
//
// flush SCIA TX port by waiting while it is busy, driverlib.
//
    sciaFlush();
//
// Step 1. Initialize System Control:
// Enable Peripheral Clocks
//
    Device_init();
//
// Step 2. Initialize GPIO:
//
    Device_initGPIO();

//
// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
//
    DINT;

//
// init interrupt and vectorTable, driverlib.
//
    Interrupt_initModule();
    Interrupt_initVectorTable();


//
// Disable CPU interrupts and clear all CPU interrupt flags:
//
    IER = 0x0000;
    IFR = 0x0000;

   Flash_initModule(FLASH0CTRL_BASE, FLASH0ECC_BASE, 2);
    initFlashSectors();

    uint32_t EntryAddr;

//
// parameter SCI_BOOT for GPIO28,29
// refer to cpu1bootrom.h for alternate SCI Boot Pin configurations
//
    EntryAddr = sciGetFunction(SCI_BOOT);

    return(EntryAddr);
}

//
// initFlashSectors - Initialize flash API and active flash bank sectors
//
void initFlashSectors(void)
{
    EALLOW;
    Fapi_StatusType oReturnCheck;
    oReturnCheck = Fapi_initializeAPI(FlashTech_CPU0_BASE_ADDRESS, 120); 
    if(oReturnCheck != Fapi_Status_Success)
    {
        exampleError(oReturnCheck);
    }

    oReturnCheck = Fapi_setActiveFlashBank(Fapi_FlashBank0);
    if(oReturnCheck != Fapi_Status_Success)
    {
        exampleError(oReturnCheck);
    }
    EDIS;
}

//
// exampleError - For this example, if an error is found just stop here
//
#ifdef __TI_COMPILER_VERSION__
    #if __TI_COMPILER_VERSION__ >= 15009000
        #pragma CODE_SECTION(exampleError,".TI.ramfunc");
    #else
        #pragma CODE_SECTION(exampleError,"ramfuncs");
    #endif
#endif
void exampleError(Fapi_StatusType status)
{
    //
    // Error code will be in the status parameter
    //
    __asm("    ESTOP0");
}

//
// End of file
//
