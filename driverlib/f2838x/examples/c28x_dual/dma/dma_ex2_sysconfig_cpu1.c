//#############################################################################
//
// FILE:   dma_ex2_sysconfig_cpu1.c
//
// TITLE:  SysConfig DMA Transfer for Shared Peripheral Example
//
//! \addtogroup driver_dual_example_list
//! <h1> DMA Transfer Shared Peripheral </h1>
//!
//! This example shows how to initiate a DMA transfer on CPU1 from a shared
//! peripheral which is owned by CPU2.  In this specific example, a timer ISR
//! is used on CPU2 to initiate a SPI transfer which will trigger the CPU1 DMA.
//! CPU1's DMA will then in turn update the ePWM1 CMPA value for the PWM which
//! it owns.  The PWM output can be observed on the GPIO pins.
//! It is recommended to run the c28x1 core first, followed by the C28x2 core.
//!
//! \b Watch \b Pins
//!   - GPIO0 and GPIO1 - ePWM output can be viewed with oscilloscope
//!
//
//#############################################################################
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
//#############################################################################


//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "ipc.h"
#include "board.h"

//
// Defines
//
//#define USE_DMA_INTERRUPT

//
// Globals
//
uint16_t newCMPValue;
#pragma DATA_SECTION(newCMPValue, "ramgs1");

//
// Function Prototypes
//
void setupDMA(void);

#ifdef USE_DMA_INTERRUPT
__interrupt void dmaISR(void);
#endif


//
// Main
//
void main(void)
{
    //
    // Initialize device clock and peripherals
    // Give peripheral/RAM ownership to CPU2
    //
    //Example_deviceInit();
    Device_init();

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Initialize SysConfig Settings
    //
    Board_init();

    //
    // Set IPC_FLAG31 from local CPU1 to remote CPU2
    //
    IPC_setFlagLtoR(IPC_CPU1_L_CPU2_R, IPC_FLAG31);

    //
    // Boot CPU2 core
    //
    Device_bootCPU2(BOOT_MODE_CPU2);

    //
    // Configure the DMA (mostly done in SysConfig)
    //
    setupDMA();

    //
    // Send IPC to CPU2 telling it to proceed with configuring the SPI
    //
    IPC_setFlagLtoR(IPC_CPU1_L_CPU2_R, IPC_FLAG1);

    //
    // Enable DMA interrupt
    //
#ifdef USE_DMA_INTERRUPT
    Interrupt_enable(INT_DMA_CH5);
    Interrupt_register(INT_DMA_CH5, &dmaISR);
#endif

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Loop indefinitely
    //
    for(;;)
    {
        NOP;
    }
}

//
// setupDMA - Function to Setup DMA
//
void setupDMA(void)
{
    //
    // Setup DMA to transfer a single 16-bit word. The DMA is setup to run
    // continuously so that an interrupt is not required to restart the RUN
    // bit. The DMA trigger is SPIA-FFTX. This is mostly done in SysConfig.
    //
    const void *destAddr, *srcAddr;

    //
    // Initialize DMA
    //
    //DMA_initController();

    destAddr = (const void *)(EPWM1_BASE + EPWM_O_CMPA + 1);
    srcAddr = (const void *)&newCMPValue;

    DMA_configAddresses(DMA_CH5_BASE, destAddr, srcAddr);
}

//
// dmaISR - DMA Interrupt Service Routine (uncomment to enable DMA ISR)
//
#ifdef USE_DMA_INTERRUPT
__interrupt void dmaISR(void)
{
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);
}
#endif

//
// End of File
//
