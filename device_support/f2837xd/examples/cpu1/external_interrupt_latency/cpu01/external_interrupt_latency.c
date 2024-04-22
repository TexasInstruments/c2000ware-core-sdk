//###########################################################################
//
// FILE:   ExternalInterruptLatency.c
//
// TITLE:  External Interrupt Latency test program.
//
//! \addtogroup cpu01_example_list
//! <h1>External Interrupts Latency (ExternalInterruptLatency)</h1>
//!
//! This program triggers external interrupts when GPIO16 is pulled low. GPIO10
//! can be used to do this, or an external signal generator can be connected.
//! GPIO19 will toggle when the interrupt is entered. A global variable 
//! (isrType) can be modified at run time to switch between C and assembly ISRs
//! running out of RAM (0-wait state) or flash (3-wait states).
//!
//! Measured delays from GPIO16 falling to GPIO19 rising at SYSCLK=200 MHz:
//!
//! ISR         Delay   Cycles  \n
//! --------------------------- \n
//! ASM/RAM     125ns   25      \n
//! ASM/Flash   135ns   27      \n
//! C/RAM       145ns   29      \n
//! C/Flash     155ns   31      \n
//!
//! Some of the delay is due to the rise and fall times of the IOs. To see 
//! this, reduce SYSCLK to less than 75 MHz. Under that condition, the ASM/RAM 
//! delay is 23 cycles, which is close to the theoretical minimum latency of 
//! 16 cycles.
//!
//! The extra delay in the flash ISRs is due to the wait states. The extra 
//! delay in the C ISRs is due to two CLRC instructions that are generated to 
//! make sure the address and overflow modes match the normal C environment.
//! With optimization enabled (-O1 and above), these instructions are removed.
//!
//
//###########################################################################
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
//###########################################################################

//
// Included Files
//
#include "F28x_Project.h"

//
// Defines
//
#define CPU_FREQ_MHZ 200ul

//
// Typedefs
//

//
// The XINT ISR can be switched at run time to observe the timing differences
// between flash, RAM, C, and assembly.
//
typedef enum 
{
    ISR_C_RAM, 
    ISR_C_FLASH, 
    ISR_ASM_RAM, 
    ISR_ASM_FLASH
} eIsrType;

//
// Globals
//
volatile eIsrType isrType;
volatile Uint16 timerFlag;

//
// Function Prototypes
//
interrupt void XINT_C_ISR_RAM(void);
interrupt void XINT_C_ISR_FLASH(void);
extern interrupt void XINT_ASM_ISR_RAM(void);
extern interrupt void XINT_ASM_ISR_FLASH(void);
interrupt void TIMER_ISR(void);
void WaitLoopFlash(void);
void WaitLoopRam(void);

//
// Main
//
void main(void)
{
    //
    // Initialize system control: PLL, watchdog, and peripheral clocks.
    // This also copies the RAM functions to RAM.
    //
    InitSysCtrl();

    //
    // Disable interrupts and initialize the PIE vector table and CPU interrupt
    // mask
    //
    DINT;
    InitPieCtrl();
    InitPieVectTable();
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Initialize and configure the GPIO pins. GPIO16 will be used as the XINT 
    // input. GPIO10 will be a push-pull output that toggles low once per 
    // millisecond. GPIO19 will toggle to indicate ISR entry.
    //
    InitGpio();
    GPIO_SetupPinMux(16, GPIO_MUX_CPU1, 0x0);
    GPIO_SetupPinOptions(16, GPIO_INPUT, GPIO_PULLUP);
    GPIO_SetupPinMux(10, GPIO_MUX_CPU1, 0x0);
    GPIO_SetupPinOptions(10, GPIO_OUTPUT, GPIO_PUSHPULL);
    GPIO_SetupPinMux(19, GPIO_MUX_CPU1, 0x0);
    GPIO_SetupPinOptions(19, GPIO_OUTPUT, GPIO_PUSHPULL);

    //
    // Turn on XCLKOUT on GPIO73
    //
    GPIO_SetupPinMux(73, GPIO_MUX_CPU1, 0x3);
    EALLOW;
    ClkCfgRegs.CLKSRCCTL3.bit.XCLKOUTSEL = 0;
    ClkCfgRegs.XCLKOUTDIVSEL.all = 0;

    //
    // Set the initial GPIO states
    //
    GpioDataRegs.GPASET.bit.GPIO10 = 1;
    GpioDataRegs.GPACLEAR.bit.GPIO19 = 1;

    //
    // Enable the XINT1 interrupt on PIE channel 1.4 and the Timer0 interrupt 
    // on PIE channel 1.7.
    //
    EALLOW;
    isrType = ISR_ASM_RAM;
    
    //
    // Write an XINT1 ISR to the PIE vector table
    //
    PieVectTable.XINT1_INT = &XINT_ASM_ISR_RAM; 
    
    //
    // Write the Timer0 ISR to the PIE vector table
    //
    PieVectTable.TIMER0_INT = &TIMER_ISR;
    
    PieCtrlRegs.PIEIER1.bit.INTx4 = 1;     // Enable PIE channel 1.4
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;     // Enable PIE channel 1.7
    EDIS;
    IER |= M_INT1;                         // Enable CPU interrupt group 1

    //
    // Set up XINT1 to trigger on a falling edge on GPIO16
    //
    EALLOW;
    
    //
    // Select GPIO16 as the source for input XBAR channel 4 (XINT1)
    //
    InputXbarRegs.INPUT4SELECT = 16;
    
    XintRegs.XINT1CR.bit.POLARITY = 0;     // Trigger XINT1 on a falling edge
    XintRegs.XINT1CR.bit.ENABLE = 1;       // Enable XINT1
    EDIS;

    //
    // Set up CPU Timer0 to trigger an interrupt once per millisecond
    //
    timerFlag = 0;
    
    EALLOW;
    CpuTimer0Regs.TCR.bit.TSS = 1;
    CpuTimer0Regs.PRD.all = 1000ul * CPU_FREQ_MHZ;
    CpuTimer0Regs.TPR.bit.TDDR = 0;
    CpuTimer0Regs.TPRH.bit.TDDRH = 0;
    
    //
    // Enable the interrupt and reset and start the timer
    //
    CpuTimer0Regs.TCR.all = 0x4020;
    
    EDIS;

    //
    // Enable CPU interrupts
    //
    EINT;

    //
    // Wait for an interrupt
    //
    while (1)
    {
        if (timerFlag)
        {
            //
            // One tick per millisecond is slow enough that we don't need to 
            // worry about disabling interrupts here.
            //
            timerFlag = 0;

            //
            // Switch the ISR type
            //
            EALLOW;
            switch (isrType)
            {
                case ISR_C_RAM:     
                    PieVectTable.XINT1_INT = &XINT_C_ISR_RAM;     
                    break;
                case ISR_C_FLASH:
                    PieVectTable.XINT1_INT = &XINT_C_ISR_FLASH;
                    break;
                case ISR_ASM_RAM:   
                    PieVectTable.XINT1_INT = &XINT_ASM_ISR_RAM;
                    break;
                case ISR_ASM_FLASH:
                    PieVectTable.XINT1_INT = &XINT_ASM_ISR_FLASH; 
                    break;
            }
            EDIS;

            //
            // Drive GPIO10 low to trigger the XINT. Wait until after the 
            // interrupt is serviced to release GPIO10 again.
            //
            GpioDataRegs.GPACLEAR.bit.GPIO10 = 1;
            asm(" NOP");
            asm(" NOP");
            asm(" NOP");
            asm(" NOP");
            asm(" NOP");
            asm(" NOP");
            asm(" NOP");
            asm(" NOP");
            asm(" NOP");
            asm(" NOP");
            asm(" NOP");
            asm(" NOP");
            asm(" NOP");
            asm(" NOP");
            asm(" NOP");
            GpioDataRegs.GPASET.bit.GPIO10 = 1;
        }
    }
}

// 
// XINT1 interrupt handlers. Both of these toggle GPIO19.
//

//
// XINT_C_ISR_RAM - This copy of the function runs out of RAM with zero wait 
// states. The delay from GPIO16 going low to GPIO19 going high was measured
// as 145 nanoseconds, which is 29 cycles at 200 MHz.
//
#pragma CODE_SECTION(XINT_C_ISR_RAM, ".TI.ramfunc")
interrupt void
XINT_C_ISR_RAM(void)
{
    GpioDataRegs.GPATOGGLE.bit.GPIO19 = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    GpioDataRegs.GPATOGGLE.bit.GPIO19 = 1;
}

//
// XINT_C_ISR_FLASH - This copy of the function runs out of flash with three 
// wait states. The delay from GPIO16 going low to GPIO19 going high was 
// measured as 155 nanoseconds, which is 31 cycles at 200 MHz.
//
interrupt void
XINT_C_ISR_FLASH(void)
{
    GpioDataRegs.GPATOGGLE.bit.GPIO19 = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    GpioDataRegs.GPATOGGLE.bit.GPIO19 = 1;
}

//
// TIMER_ISR - Timer0 interrupt handler. Tells the main loop to pull GPIO10 
// low.
//
interrupt void
TIMER_ISR(void)
{
    timerFlag = 1;
    //GpioDataRegs.GPATOGGLE.bit.GPIO19 = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

//
// End of File
//

