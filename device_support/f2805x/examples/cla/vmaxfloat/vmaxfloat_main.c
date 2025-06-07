//###########################################################################
//
// FILE:  vmaxfloat_main.c
//
// TITLE: Vector Maximum
//
//! \addtogroup f2805x_example_cla_list
//! <h1> Vector Maximum</h1>
//!
//! Task 1 calculates the vector max moving backward through the array. \n
//! Task 2 calculates the vector max moving forward through the array. \n
//! Task 3 calculates the vector max using the ternary operator. \n
//! Task 2 calculates the vector max using min/max intrinsics. \n
//!
//! \b Watch \b Variables \n
//! - vector1 - Input vector to task 1
//! - vector2 - Input vector to task 2
//! - vector3 - Input vector to task 3
//! - vector4 - Input vector to task 4
//! - max1 - Maximum value in vector 1
//! - index1 - Index of the maximum value in vector 1
//! - max2 - Maximum value in vector 2
//! - index2 - Index of the maximum value in vector 2
//! - max3 - Maximum value in vector 3
//! - index3 - Index of the maximum value in vector 3
//! - max4 - Maximum value in vector 4
//! - min4 - Minimum value in vector 4
//!
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:
// Copyright (C) 2012-2025 Texas Instruments Incorporated - http://www.ti.com/
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
#include "DSP28x_Project.h"     // DSP28x Headerfile
#include "F2805x_Cla_defines.h"

//
// Include the test header file whose name is based on the test name
// which is defined by the macro TEST on the command line
//
#include XSTRINGIZE(XCONCAT(TEST_NAME, _shared.h))

#define CLA_PROG_ENABLE      0x0001
#define CLARAM0_ENABLE       0x0010
#define CLARAM1_ENABLE       0x0020
#define CLARAM2_ENABLE       0x0040
#define CLA_RAM0CPUE         0x0100
#define CLA_RAM1CPUE         0x0200
#define CLA_RAM2CPUE         0x0400

#define HARDWARE 1

//
// Constants
//
#define OSCCLK        (10000000UL)              // < Internal OSC frequency
#define SYSCLK        (80000000UL)              // < System Clock frequency
#define PER_CLK_DIV    (4)                     // < Low speed peripheral clock dividers
#define PER_CLK       (SYSCLK/PER_CLK_DIV)     // < Low speed peripheral clock
#define DIV_SEL       (2)                         // < Clock divider selection
#define CLK_DIV       ((SYSCLK * DIV_SEL)/OSCCLK) // < Clock divider

//
// CLA ISRs
//
__interrupt void cla1_task1_isr(void);
__interrupt void cla1_task2_isr(void);
__interrupt void cla1_task3_isr(void);
__interrupt void cla1_task4_isr(void);
__interrupt void cla1_task5_isr(void);
__interrupt void cla1_task6_isr(void);
__interrupt void cla1_task7_isr(void);
__interrupt void cla1_task8_isr(void);

//
// Linker defined vars
//
extern Uint16 Cla1Prog_Start;
extern Uint16 Cla1funcsLoadStart;
extern Uint16 Cla1funcsLoadEnd;
extern Uint16 Cla1funcsRunStart;
extern Uint16 Cla1funcsLoadSize;
extern Uint16 Cla1mathTablesLoadStart;
extern Uint16 Cla1mathTablesRunStart;
extern Uint16 Cla1mathTablesLoadSize;

//
// Main Function
//
void main(void)
{
    //
    // Step 1: Setup the system clock
    // Disable the watchdog timer, initialize the system clock,
    // PLL and configure the peripheral clock.
    //
    InitSysCtrl();

    //
    // Step 2: Initialize PIE control
    // Initialize PIE control, disable all __interrupts and
    // then copy over the PIE Vector table from BootROM to RAM
    //
    DINT;
    InitPieCtrl();
    IER = 0x00000000;
    IFR = 0x00000000;
    InitPieVectTable();

    //
    // Assign user defined ISR to the PIE vector table
    //
    EALLOW;
    PieVectTable.CLA1_INT1  = &cla1_task1_isr;
    PieVectTable.CLA1_INT2  = &cla1_task2_isr;
    PieVectTable.CLA1_INT3  = &cla1_task3_isr;
    PieVectTable.CLA1_INT4  = &cla1_task4_isr;
    PieVectTable.CLA1_INT5  = &cla1_task5_isr;
    PieVectTable.CLA1_INT6  = &cla1_task6_isr;
    PieVectTable.CLA1_INT7  = &cla1_task7_isr;
    PieVectTable.CLA1_INT8  = &cla1_task8_isr;
    EDIS;

    //
    // Copy over the CLA code and Tables
    //
    memcpy(&Cla1funcsRunStart, &Cla1funcsLoadStart,
            (Uint32)&Cla1funcsLoadSize);
    memcpy(&Cla1mathTablesRunStart, &Cla1mathTablesLoadStart,
            (Uint32)&Cla1mathTablesLoadSize);

    //
    // Compute all CLA task vectors
    //
    EALLOW;
    Cla1Regs.MVECT1 = (Uint16)((Uint32)&Cla1Task1 - (Uint32)&Cla1Prog_Start);
    Cla1Regs.MVECT2 = (Uint16)((Uint32)&Cla1Task2 - (Uint32)&Cla1Prog_Start);
    Cla1Regs.MVECT3 = (Uint16)((Uint32)&Cla1Task3 - (Uint32)&Cla1Prog_Start);
    Cla1Regs.MVECT4 = (Uint16)((Uint32)&Cla1Task4 - (Uint32)&Cla1Prog_Start);
    Cla1Regs.MVECT5 = (Uint16)((Uint32)&Cla1Task5 - (Uint32)&Cla1Prog_Start);
    Cla1Regs.MVECT6 = (Uint16)((Uint32)&Cla1Task6 - (Uint32)&Cla1Prog_Start);
    Cla1Regs.MVECT7 = (Uint16)((Uint32)&Cla1Task7 - (Uint32)&Cla1Prog_Start);
    Cla1Regs.MVECT8 = (Uint16)((Uint32)&Cla1Task8 - (Uint32)&Cla1Prog_Start);
    EDIS;

    //
    // Step 3 : Mapping CLA tasks
    // All tasks are enabled and will be started by an ePWM trigger
    // Map CLA program memory to the CLA and enable software breakpoints
    //
    EALLOW;
    Cla1Regs.MPISRCSEL1.bit.PERINT1SEL     = CLA_INT1_NONE;
    Cla1Regs.MPISRCSEL1.bit.PERINT2SEL     = CLA_INT2_NONE;
    Cla1Regs.MPISRCSEL1.bit.PERINT3SEL     = CLA_INT3_NONE;
    Cla1Regs.MPISRCSEL1.bit.PERINT4SEL     = CLA_INT4_NONE;
    Cla1Regs.MPISRCSEL1.bit.PERINT5SEL     = CLA_INT5_NONE;
    Cla1Regs.MPISRCSEL1.bit.PERINT6SEL     = CLA_INT6_NONE;
    Cla1Regs.MPISRCSEL1.bit.PERINT7SEL     = CLA_INT7_NONE;
    Cla1Regs.MPISRCSEL1.bit.PERINT8SEL     = CLA_INT8_NONE;
    Cla1Regs.MIER.all                      = 0x00FF;
    EDIS;

    //
    // Enable CLA __interrupts at the group and subgroup levels
    //
    PieCtrlRegs.PIEIER11.all       = 0xFFFF;
    IER = (M_INT11 );
    EINT;   // Enable Global __interrupt INTM
    ERTM;   // Enable Global realtime __interrupt DBGM

    //
    // Switch the CLA program space to the CLA and enable software forcing
    // Also switch over CLA data ram 0, 1 and 2
    // CAUTION: The RAMxCPUE bits can only be enabled by writing to the
    // register and not the individual bit field. Furthermore, the status of
    // these bitfields is not reflected in either the watch or register
    // views - they always read as zeros. This is a known bug and the user is
    // advised to test CPU accessibility first before proceeding.
    //
    EALLOW;
    Cla1Regs.MMEMCFG.all = CLA_PROG_ENABLE | CLARAM0_ENABLE | CLARAM1_ENABLE |
                           CLA_RAM1CPUE;
    Cla1Regs.MCTL.bit.IACKE = 1;
    EDIS;

    //
    // Invoke Task(s)
    //
    test_run();

    //
    // Report Results
    //
    test_report();

    #if HARDWARE
    {
        __asm(" ESTOP0");
    }
    #endif
}

//
// CLA ISRs
//
__interrupt void cla1_task1_isr(void)
{
    PieCtrlRegs.PIEACK.bit.ACK11 = 1;
}

__interrupt void cla1_task2_isr(void)
{
    PieCtrlRegs.PIEACK.bit.ACK11 = 1;
}

__interrupt void cla1_task3_isr(void)
{
    PieCtrlRegs.PIEACK.bit.ACK11 = 1;
}

__interrupt void cla1_task4_isr(void)
{
    PieCtrlRegs.PIEACK.bit.ACK11 = 1;
}

__interrupt void cla1_task5_isr(void)
{
    PieCtrlRegs.PIEACK.bit.ACK11 = 1;
}

__interrupt void cla1_task6_isr(void)
{
    PieCtrlRegs.PIEACK.bit.ACK11 = 1;
}

__interrupt void cla1_task7_isr(void)
{
    PieCtrlRegs.PIEACK.bit.ACK11 = 1;
}

__interrupt void cla1_task8_isr(void)
{
    PieCtrlRegs.PIEACK.bit.ACK11 = 1;
}

