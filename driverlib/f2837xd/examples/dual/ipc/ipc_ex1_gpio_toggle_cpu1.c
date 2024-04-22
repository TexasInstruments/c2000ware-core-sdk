//###########################################################################
//
// FILE:   ipc_ex1_gpio_toggle_cpu1.c
//
// TITLE:  GPIO Toggle for F2837xD CPU1.
//
//! \addtogroup dual_example_list
//! <h1> IPC GPIO toggle </h1>
//!
//! This example shows GPIO input on the local CPU triggering an output on the
//! remote CPU. A GPIO input change on CPU01 causes an output change on CPU02
//! and vice versa. \n
//! CPU1 has control of GPIO31 , GPIO15 and GPIO14.\n
//! CPU2 has control of GPIO34 , GPIO10 and GPIO11.\n
//!
//! The IPC is used to signal a change on the CPU's input pin.\n
//!
//! \b Hardware \b Connections
//!   - connect GPIO15 to GPIO11
//!   - connect GPIO14 to GPIO10
//!
//! \b Watch \b Pins
//!   - GPIO34 - output on CPU2
//!   - GPIO11 - input on CPU2
//!   - GPIO31 - output on CPU1
//!   - GPIO14 - input on CPU1
//!   - GPIO10 - square wave output on CPU02
//!   - GPIO15 - square wave output on CPU01
//
//#############################################################################
//
// 
// $Copyright:
// Copyright (C) 2013-2024 Texas Instruments Incorporated - http://www.ti.com/
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
#include "driverlib.h"
#include "device.h"
#include "inc/hw_ipc.h"


//
// Main
//
void main(void)
{
    uint16_t state;
    uint32_t count;
    uint16_t ipcFlag17 = 17U;
    uint16_t ipcFlag10 = 10U;
    uint16_t ipcFlag11 = 11U;
    //
    // Initialize device clock and peripherals
    //
    Device_init();

#ifdef _STANDALONE
#ifdef _FLASH
    //
    // Send boot command to allow the CPU2 application to begin execution
    //
    Device_bootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_FLASH);
#else
    //
    // Send boot command to allow the CPU2 application to begin execution
    //
    Device_bootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_RAM);

#endif // _FLASH
#endif // _STANDALONE

    //
    // Initialize GPIO and configure the GPIO pin as a push-pull output
    //
    Device_initGPIO();

    //
    // GPIO34 (LED2) is assigned to CPU2 and is an output pin.
    //
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED2, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED2, GPIO_DIR_MODE_OUT);
    GPIO_setMasterCore(DEVICE_GPIO_PIN_LED2, GPIO_CORE_CPU2);

    //
    // GPIO10 is assigned to CPU2 and is an output pin.
    //
    GPIO_setPadConfig(10UL, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(10UL, GPIO_DIR_MODE_OUT);
    GPIO_setMasterCore(10UL, GPIO_CORE_CPU2);

    //
    // GPIO11 is assigned to CPU2 and is an input pin.
    //
    GPIO_setPadConfig(11UL, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(11UL, GPIO_DIR_MODE_IN);
    GPIO_setMasterCore(11UL, GPIO_CORE_CPU2);

    //
    // GPIO31 (LED2) is assigned to CPU1 and is an output pin.
    //
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED1, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED1, GPIO_DIR_MODE_OUT);
    GPIO_setMasterCore(DEVICE_GPIO_PIN_LED1, GPIO_CORE_CPU1);


    //
    // GPIO15 is assigned to CPU1 and is an output pin.
    //
    GPIO_setPadConfig(15UL, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(15UL, GPIO_DIR_MODE_OUT);
    GPIO_setMasterCore(15UL, GPIO_CORE_CPU1);

    //
    // GPIO14 is assigned to CPU1 and is an input pin.
    //
    GPIO_setPadConfig(14UL, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(14UL, GPIO_DIR_MODE_IN);
    GPIO_setMasterCore(14UL, GPIO_CORE_CPU1);

    //
    // Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    //
    DINT;

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Wait until CPU02 is ready and IPC flag 17 is set
    //
    while(!(HWREG(IPC_BASE + IPC_O_STS) & (1UL << ipcFlag17)))
    {
    }

    //
    // ACK IPC flag 17 for CPU2
    //
    HWREG(IPC_BASE + IPC_O_ACK) = 1UL << ipcFlag17;

    //
    // Set the state to the DAT value of GPIO14
    //
    state = GPIO_readPin(14UL);

    while(1)
    {
        //
        // Generate a Square Wave on GPIO15. This signal will be used to drive
        // GPIO11 input on CPU2
        //
        if(count++ > 1000000)
        {
            count = 0;

            //
            // Toggle GPIO15
            //
            GPIO_togglePin(15UL);
        }

        //
        // Set Flag 10 when GPIO14 input changes
        //
        if(GPIO_readPin(14UL) != state)
        {
            state = GPIO_readPin(14UL);

            if(!(HWREG(IPC_BASE + IPC_O_STS) & (1UL << ipcFlag10)))
            {
                //
                // Send IPC flag 10 to CPU2
                //
            	HWREG(IPC_BASE + IPC_O_SET) = 1UL << ipcFlag10;
            }
        }

        //
        // Toggle GPIO31 output if Flag 11 is set by CPU2
        //
        if((HWREG(IPC_BASE + IPC_O_STS) & (1UL << ipcFlag11)))
        {
        	//
        	// Toggle GPIO31 (LED1)
        	//
        	GPIO_togglePin(DEVICE_GPIO_PIN_LED1);

            //
            // ACK IPC flag 11 for CPU2
            //
            HWREG(IPC_BASE + IPC_O_ACK) = 1UL << ipcFlag11;

            //
            // Clear IPC flag 11 for CPU2
            //
            HWREG(IPC_BASE + IPC_O_CLR) = 1UL << ipcFlag11;
        }
    }
}

//
// End of file
//
