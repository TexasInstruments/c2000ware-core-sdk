//#############################################################################
//
// FILE:   dma_ex1_shared_periph_cpu2.c
//
// TITLE:  DMA Transfer for Shared Peripheral Example (CPU2)
//
// This example shows how to initiate a DMA transfer on CPU1 from a shared
// peripheral which is owned by CPU2.  In this specific example, a timer ISR
// is used on CPU2 to initiate a SPI transfer which will trigger the CPU1 DMA.
// CPU1's DMA will then in turn update the ePWM1 CMPA value for the PWM which
// it owns.  The PWM output can be observed on the GPIO pins.
//
//#############################################################################
//
// $Release Date:  $
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
// Globals
//
uint16_t newCMPValue;
#pragma DATA_SECTION(newCMPValue, "SHARERAMGS2");

uint16_t direction = 1;

//
// Function Prototypes
//
void Example_deviceInit(void);
void initSpi(void);
void loadBuffer(void);

void initCPUTimer(uint32_t);
void configCPUTimer(uint32_t, float, float);
__interrupt void cpuTimer1ISR(void);

//
// Main
//
void main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Example_deviceInit();

    newCMPValue = 3000;  // Set CMP value

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
    // Wait for IPC from CPU1 confirming DMA is configured before initializing
    // SPI. Note that because of the way the TXFIFO interrupt is configured a
    // DMA transfer will be triggered immediately after the SPI is released
    // from reset.
    //
    while((HWREG(IPC_BASE + IPC_O_STS) & IPC_STS_IPC1) == 0U)
    {
    }

    //
    // Configure the SPI
    //
    initSpi();

    //
    // Setup CPU Timer 1 to interrupt every 10 ms
    //
    initCPUTimer(CPUTIMER1_BASE);
    configCPUTimer(CPUTIMER1_BASE, DEVICE_SYSCLK_FREQ, 10000);
    CPUTimer_startTimer(CPUTIMER1_BASE);

    //
    // Interrupts that are used in this example are re-mapped to ISR functions
    // found within this file.
    //
    Interrupt_register(INT_TIMER1, &cpuTimer1ISR);

    //
    // Enable CPU Timer 1 interrupt
    //
    Interrupt_enable(INT_TIMER1);

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
// Example_deviceInit function
// This example uses custom Device_init function since CPU2 owns some of the
// peripherals
//
void Example_deviceInit(void)
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
    // Wait for IPC flag from CPU1
    //
    while((HWREG(IPC_BASE + IPC_O_STS) & IPC_STS_IPC0) == 0U)
    {
    }
    HWREG(IPC_BASE + IPC_O_ACK) = IPC_ACK_IPC0;

    //
    // Turn on required peripherals
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPIA);
}

//
// initSpi - Function to Setup SPI for FIFO mode
//
void initSpi(void)
{
    //
    // Must put SPI into reset before configuring it
    //
    SPI_disableModule(SPIA_BASE);

    //
    // SPI configuration. Use a 500kHz SPICLK and 16-bit word size.
    //
    SPI_setConfig(SPIA_BASE, DEVICE_LSPCLK_FREQ, SPI_PROT_POL0PHA0,
                  SPI_MODE_MASTER, 500000, 16);
    SPI_enableLoopback(SPIA_BASE);
    SPI_enableModule(SPIA_BASE);

    //
    // FIFO configuration
    //
    SPI_enableFIFO(SPIA_BASE);
    SPI_clearInterruptStatus(SPIA_BASE, SPI_INT_RXFF | SPI_INT_TXFF);
    SPI_setFIFOInterruptLevel(SPIA_BASE, SPI_FIFO_TX2, SPI_FIFO_RX2);

   //
   // A DMA transfer will be triggered here!
   //

   //
   // Load the SPI FIFO Tx Buffer
   //
   loadBuffer();

   //
   // Disable the clock to prevent continuous transfer/DMA triggers. Note that
   // this method of disabling the clock should not be used if actual data is
   // being transmitted.
   //
   SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_SPIA);
}

//
// loadBuffer - Function to load SPI Tx FIFO Buffer
//
void loadBuffer(void)
{
    //
    // Fill up the FIFO buffer
    //
    HWREGH(SPIA_BASE + SPI_O_TXBUF) = 0xAAAA;
    HWREGH(SPIA_BASE + SPI_O_TXBUF) = 0xAAAA;
    HWREGH(SPIA_BASE + SPI_O_TXBUF) = 0xAAAA;
    HWREGH(SPIA_BASE + SPI_O_TXBUF) = 0xAAAA;
    HWREGH(SPIA_BASE + SPI_O_TXBUF) = 0xAAAA;
    HWREGH(SPIA_BASE + SPI_O_TXBUF) = 0xAAAA;
    HWREGH(SPIA_BASE + SPI_O_TXBUF) = 0xAAAA;
    HWREGH(SPIA_BASE + SPI_O_TXBUF) = 0xAAAA;
    HWREGH(SPIA_BASE + SPI_O_TXBUF) = 0xAAAA;
    HWREGH(SPIA_BASE + SPI_O_TXBUF) = 0xAAAA;
    HWREGH(SPIA_BASE + SPI_O_TXBUF) = 0xAAAA;
    HWREGH(SPIA_BASE + SPI_O_TXBUF) = 0xAAAA;
    HWREGH(SPIA_BASE + SPI_O_TXBUF) = 0xAAAA;
    HWREGH(SPIA_BASE + SPI_O_TXBUF) = 0xAAAA;
    HWREGH(SPIA_BASE + SPI_O_TXBUF) = 0xAAAA;
    HWREGH(SPIA_BASE + SPI_O_TXBUF) = 0xAAAA;
}

//
// initCPUTimer - This function initializes a CPU Timer to a known state.
//
void
initCPUTimer(uint32_t cpuTimer)
{
    //
    // Initialize timer period to maximum
    //
    CPUTimer_setPeriod(cpuTimer, 0xFFFFFFFF);

    //
    // Initialize pre-scale counter to divide by 1 (SYSCLKOUT)
    //
    CPUTimer_setPreScaler(cpuTimer, 0);

    //
    // Make sure timer is stopped
    //
    CPUTimer_stopTimer(cpuTimer);

    //
    // Reload all counter registers with period value
    //
    CPUTimer_reloadTimerCounter(cpuTimer);
}

//
// configCPUTimer - This function initializes the selected timer to the
// period specified by the "freq" and "period" parameters. The "freq" is
// entered as Hz and the period in microseconds. The timer is held in the
// stopped state after configuration.
//
void
configCPUTimer(uint32_t cpuTimer, float freq, float period)
{
    uint32_t temp;

    //
    // Initialize timer period:
    //
    temp = (uint32_t)(freq / 1000000 * period);
    CPUTimer_setPeriod(cpuTimer, temp);

    //
    // Set pre-scale counter to divide by 1 (SYSCLKOUT):
    //
    CPUTimer_setPreScaler(cpuTimer, 0);

    //
    // Initializes timer control register. The timer is stopped, reloaded,
    // free run disabled, and interrupt enabled.
    //
    CPUTimer_stopTimer(cpuTimer);
    CPUTimer_reloadTimerCounter(cpuTimer);
    CPUTimer_setEmulationMode(cpuTimer,
                              CPUTIMER_EMULATIONMODE_STOPAFTERNEXTDECREMENT);
    CPUTimer_enableInterrupt(cpuTimer);
}

//
// cpuTimer1ISR - CPU Timer 1 ISR
//
__interrupt void cpuTimer1ISR(void)
{
    //
    // Re-enable SPI clock to allow DMA trigger
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPIA);

    //
    // Wait for interrupt flag. This is when the DMA trigger will occur.
    //
    while((SPI_getInterruptStatus(SPIA_BASE) & SPI_INT_TXFF) == 0)
    {
    }

    //
    // Reload the SPI TX buffer and clear interrupt flag
    //
    loadBuffer();
    SPI_clearInterruptStatus(SPIA_BASE, SPI_INT_TXFF);

    //
    // Disable the clock to prevent continuous transfer/DMA triggers. Note that
    // this method of disabling the clock should not be used if actual data is
    // being transmitted.
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_SPIA);

    //
    // Update next value to be transferred to the ePWM
    //
    if(newCMPValue >= 4500)
    {
        direction = 0;
    }
    else if(newCMPValue <= 1500)
    {
        direction = 1;
    }

    if(!direction)
    {
        newCMPValue -= 50;
    }
    else
    {
        newCMPValue += 50;
    }
}

//
// End of File
//
