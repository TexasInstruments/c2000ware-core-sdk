//#############################################################################
//
// FILE:   clapromcrc_ex1_cpuinterrupt.c
//
// TITLE:  Background CLA Program ROM CRC computation with interrupt.
//
//! \addtogroup driver_example_list
//! <h1> CLAPROMCRC CPU Interrupt Example </h1>
//!
//! This example demonstrates how to configure and run the CLAPROMCRC from the CPU.
//! This uses the golden CRC values in 'clapromcrc_ex1_crctable.h' The CRC
//! calculation uses the 32-bit polynomial 0x04C11DB7.
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - None.
//!
//
//#############################################################################
//
//
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
//#############################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "clapromcrc_ex1_crctable.h"

#ifdef _FLASH
// These are defined by the linker (see device linker command file)
extern uint16_t RamfuncsLoadStart;
extern uint16_t RamfuncsLoadSize;
extern uint16_t RamfuncsRunStart;
#endif

//
// Globals
//
bool pass[97] = {false};
int32_t Result[97] = {0x0000};
volatile uint32_t i = 0;
volatile uint32_t j = 0;
//
// Function Prototypes
//
__interrupt void clapromcrcISR(void);

//
// Main
//
void main(void)
{
	volatile uint32_t currentAddress = 0x0000;
	volatile bool runStatus = false;


    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Initialize GPIO and configure the GPIO pin as a push-pull output
    //
    Device_initGPIO();

    //
    // Disable global interrupts.
    //
    DINT;

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts. 
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Map the ISR to the CLAPROMCRC interrupt.
    //
    Interrupt_register(INT_CLA1PROMCRC, clapromcrcISR);

    //
    // Enable the wake interrupt in the PIE: Group 7 interrupt 15.
    //
    Interrupt_enable(INT_CLA1PROMCRC);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Set the emulation mode of the CLAPROMCRC to free run.
    //
    CLAPROMCRC_setEmulationMode(CLA1PROMCRC_BASE, CLAPROMCRC_MODE_FREE);

    for (i=0; i<64;i++)
    {
        //
        // Set the block size to 96KB for the CRC.
        //
        CLAPROMCRC_setBlockSize(CLA1PROMCRC_BASE, 1);

        //
        // Set the start address for the 1KB block desired according of
        // CLA program ROM
        //
        CLAPROMCRC_setStartAddress(CLA1PROMCRC_BASE, (0x0200)*i);

        //
        // Set the seed of the CRC to 0x00000000.
        //
        CLAPROMCRC_setSeed(CLA1PROMCRC_BASE, 0x00000000);

        //
        // Set the golden CRC value of the desired block in program ROM.
        //
        CLAPROMCRC_setGoldenCRC(CLA1PROMCRC_BASE, clapromcrcTable[i]);

        //
        // Enable the DONE interrupt of the CLAPROMCRC.
        //
        CLAPROMCRC_enableDoneInterrupt(CLA1PROMCRC_BASE);

        //
        // Start the CRC calculation.
        //
        CLAPROMCRC_start(CLA1PROMCRC_BASE);

        //
        // Set runStatus to true;
        //
        runStatus = true;

        //
        // Loop Forever
        //
        while (runStatus)
        {
            runStatus = CLAPROMCRC_getRunStatus(CLA1PROMCRC_BASE);
        }
    }

    for (j=0; j<32; j++)
        {
            //
            // Set the block size to 96KB for the CRC.
            //
            CLAPROMCRC_setBlockSize(CLA1PROMCRC_BASE, 1);

            //
            // Set the start address to 0xC000 according to the start address of
            // program ROM of the CLA memory map ext.
            //
            CLAPROMCRC_setStartAddress(CLA1PROMCRC_BASE, (0x0C000 + (0x200*j)));

            //
            // Set the seed of the CRC to 0x00000000.
            //
            CLAPROMCRC_setSeed(CLA1PROMCRC_BASE, 0x00000000);

            //
            // Set the golden CRC value for the block of desired program ROM.
            //
            CLAPROMCRC_setGoldenCRC(CLA1PROMCRC_BASE, clapromcrcTable[i]);

            //
            // Enable the DONE interrupt of the CLAPROMCRC.
            //
            CLAPROMCRC_enableDoneInterrupt(CLA1PROMCRC_BASE);

            //
            // Start the CRC calculation.
            //
            CLAPROMCRC_start(CLA1PROMCRC_BASE);

            //
            // Set runStatus to true;
            //
            runStatus = true;

            //
            // Loop Forever
            //
            while (runStatus)
            {
                runStatus = CLAPROMCRC_getRunStatus(CLA1PROMCRC_BASE);
            }
        }


    // Set the block size to 96KB for the CRC.
    //
    CLAPROMCRC_setBlockSize(CLA1PROMCRC_BASE, 96);

    //
    // Set the start address to 0x0000 according to the start address of
    // program ROM of the CLA memory map for entire 96kB for CLAPROM
    //
    CLAPROMCRC_setStartAddress(CLA1PROMCRC_BASE, 0x0000);

    //
    // Set the seed of the CRC to 0x00000000.
    //
    CLAPROMCRC_setSeed(CLA1PROMCRC_BASE, 0x00000000);

    //
    // Set the golden CRC value for the block of desired program ROM.
    //
    CLAPROMCRC_setGoldenCRC(CLA1PROMCRC_BASE, clapromcrcTable[i]);

    //
    // Enable the DONE interrupt of the CLAPROMCRC.
    //
    CLAPROMCRC_enableDoneInterrupt(CLA1PROMCRC_BASE);

    //
    // Start the CRC calculation.
    //
    CLAPROMCRC_start(CLA1PROMCRC_BASE);

    //
    // Set runStatus to true to wait until calculation is complete in while loop;
    //
    runStatus = true;

    while(runStatus)
    {
    	//
    	// Check the run status and current address of the CRC calculation.
    	//
    	runStatus = CLAPROMCRC_getRunStatus(CLA1PROMCRC_BASE);
    	currentAddress = CLAPROMCRC_getCurrentAddress(CLA1PROMCRC_BASE);
    }


}

//
// clapromcrcISR - DONE interrupt from CLAPROMCRC.
//
__interrupt void
clapromcrcISR(void)
{
    //
    // Check the status of the CRC calculation and set the global pass array
    // variable.
    //
    if(CLAPROMCRC_checkStatus(CLA1PROMCRC_BASE))
    {
    	pass[i] = true;
    }

    Result[i] = CLAPROMCRC_getResult(CLA1PROMCRC_BASE);

    if (i > 63)
    {
        i++;
    }
    //
    // Clear the CLAPROMCRC interrupt flags.
    //
    CLAPROMCRC_clearInterruptFlag(CLA1PROMCRC_BASE, CLAPROMCRC_CRCDONE_FLG);
    CLAPROMCRC_clearInterruptFlag(CLA1PROMCRC_BASE, CLAPROMCRC_INT_FLG);

    //
    // Acknowledge the PIE interrupt.
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);
}

//
// End of File
//
