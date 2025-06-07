//###########################################################################
//
// FILE:   f28004x_defaultisr.c
//
// TITLE:  f28004x Device Default Interrupt Service Routines
//
//###########################################################################
//
//
// $Copyright:
// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com/
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
#include "f28004x_device.h"       // F28004x Header File Include File
#include "f28004x_examples.h"     // F28004x Examples Include File

//
// TIMER1_ISR - CPU Timer 1 Interrupt
//
__interrupt void
TIMER1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// TIMER2_ISR - CPU Timer 2 Interrupt
//
__interrupt void
TIMER2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// DATALOG_ISR - Datalogging Interrupt
//
__interrupt void
DATALOG_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// RTOS_ISR - RTOS Interrupt
//
__interrupt void
RTOS_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// EMU_ISR - Emulation Interrupt
//
__interrupt void
EMU_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// NMI_ISR - Non-Maskable Interrupt
//
__interrupt void
NMI_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// ILLEGAL_ISR - Illegal Operation Trap
//
__interrupt void
ILLEGAL_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// USER1_ISR - User Defined Trap 1
//
__interrupt void
USER1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// USER2_ISR - User Defined Trap 2
//
__interrupt void
USER2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// USER3_ISR - User Defined Trap 3
//
__interrupt void
USER3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// USER4_ISR - User Defined Trap 4
//
__interrupt void
USER4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// USER5_ISR - User Defined Trap 5
//
__interrupt void
USER5_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// USER6_ISR - User Defined Trap 6
//
__interrupt void
USER6_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// USER7_ISR - User Defined Trap 7
//
__interrupt void
USER7_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// USER8_ISR - User Defined Trap 8
//
__interrupt void
USER8_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// USER9_ISR - User Defined Trap 9
//
__interrupt void
USER9_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// USER10_ISR - User Defined Trap 10
//
__interrupt void
USER10_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// USER11_ISR - User Defined Trap 11
//
__interrupt void
USER11_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// USER12_ISR - User Defined Trap 12
//
__interrupt void
USER12_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// ADCA1_ISR - ADCA Interrupt 1
//
__interrupt void
ADCA1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// ADCB1_ISR - ADCB Interrupt 1
//
__interrupt void
ADCB1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// ADCC1_ISR - ADCC Interrupt 1
//
__interrupt void
ADCC1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// XINT1_ISR - XINT1 Interrupt
//
__interrupt void
XINT1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// XINT2_ISR - XINT2 Interrupt
//
__interrupt void
XINT2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// TIMER0_ISR - Timer 0 Interrupt
//
__interrupt void
TIMER0_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// WAKE_ISR - Halt Wakeup Interrupt
//
__interrupt void
WAKE_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// EPWM1_TZ_ISR - ePWM1 Trip Zone Interrupt
//
__interrupt void
EPWM1_TZ_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// EPWM2_TZ_ISR - ePWM2 Trip Zone Interrupt
//
__interrupt void
EPWM2_TZ_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// EPWM3_TZ_ISR - ePWM3 Trip Zone Interrupt
//
__interrupt void
EPWM3_TZ_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// EPWM4_TZ_ISR - ePWM4 Trip Zone Interrupt
//
__interrupt void
EPWM4_TZ_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// EPWM5_TZ_ISR - ePWM5 Trip Zone Interrupt
//
__interrupt void
EPWM5_TZ_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// EPWM6_TZ_ISR - ePWM6 Trip Zone Interrupt
//
__interrupt void
EPWM6_TZ_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// EPWM7_TZ_ISR - ePWM7 Trip Zone Interrupt
//
__interrupt void
EPWM7_TZ_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// EPWM8_TZ_ISR - ePWM8 Trip Zone Interrupt
//
__interrupt void
EPWM8_TZ_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// EPWM1_ISR - ePWM1 Interrupt
//
__interrupt void
EPWM1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// EPWM2_ISR - ePWM2 Interrupt
//
__interrupt void
EPWM2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// EPWM3_ISR - ePWM3 Interrupt
//
__interrupt void
EPWM3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// EPWM4_ISR - ePWM4 Interrupt
//
__interrupt void
EPWM4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// EPWM5_ISR - ePWM5 Interrupt
//
__interrupt void
EPWM5_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// EPWM6_ISR - ePWM6 Interrupt
//
__interrupt void
EPWM6_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// EPWM7_ISR - ePWM7 Interrupt
//
__interrupt void
EPWM7_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// EPWM8_ISR - ePWM8 Interrupt
//
__interrupt void
EPWM8_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// ECAP1_ISR - eCAP1 Interrupt
//
__interrupt void
ECAP1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// ECAP2_ISR - eCAP2 Interrupt
//
__interrupt void
ECAP2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// ECAP3_ISR - eCAP3 Interrupt
//
__interrupt void
ECAP3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// ECAP4_ISR - eCAP4 Interrupt
//
__interrupt void
ECAP4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// ECAP5_ISR - eCAP5 Interrupt
//
__interrupt void
ECAP5_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// ECAP6_ISR - eCAP6 Interrupt
//
__interrupt void
ECAP6_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// ECAP7_ISR - eCAP7 Interrupt
//
__interrupt void
ECAP7_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// ECAP6_2_ISR - eCAP6_2 Interrupt
//
__interrupt void
ECAP6_2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// ECAP7_2_ISR - eCAP7_2 Interrupt
//
__interrupt void
ECAP7_2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// EQEP1_ISR - eQEP1 Interrupt
//
__interrupt void
EQEP1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// EQEP2_ISR - eQEP2 Interrupt
//
__interrupt void
EQEP2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// SPIA_RX_ISR - SPIA Receive Interrupt
//
__interrupt void
SPIA_RX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// SPIA_TX_ISR - SPIA Transmit Interrupt
//
__interrupt void
SPIA_TX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// SPIB_RX_ISR - SPIB Receive Interrupt
//
__interrupt void
SPIB_RX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// SPIB_TX_ISR - SPIB Transmit Interrupt
//
__interrupt void
SPIB_TX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// DMA_CH1_ISR - DMA Channel 1 Interrupt
//
__interrupt void
DMA_CH1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// DMA_CH2_ISR - DMA Channel 2 Interrupt
//
__interrupt void
DMA_CH2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// DMA_CH3_ISR - DMA Channel 3 Interrupt
//
__interrupt void
DMA_CH3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// DMA_CH4_ISR - DMA Channel 4 Interrupt
//
__interrupt void
DMA_CH4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// DMA_CH5_ISR - DMA Channel 5 Interrupt
//
__interrupt void
DMA_CH5_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// DMA_CH6_ISR - DMA Channel 6 Interrupt
//
__interrupt void
DMA_CH6_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// I2CA_ISR - I2CA Interrupt 1
//
__interrupt void
I2CA_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// I2CA_FIFO_ISR - I2CA Interrupt 2
//
__interrupt void
I2CA_FIFO_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// SCIA_RX_ISR - SCIA Receive Interrupt
//
__interrupt void
SCIA_RX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// SCIA_TX_ISR - SCIA Transmit Interrupt
//
__interrupt void
SCIA_TX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// SCIB_RX_ISR - SCIB Receive Interrupt
//
__interrupt void
SCIB_RX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// SCIB_TX_ISR - SCIB Transmit Interrupt
//
__interrupt void
SCIB_TX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// CANA0_ISR - CANA Interrupt 0
//
__interrupt void
CANA0_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// CANA1_ISR - CANA Interrupt 1
//
__interrupt void
CANA1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// CANB0_ISR - CANB Interrupt 0
//
__interrupt void
CANB0_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// CANB1_ISR - CANB Interrupt 1
//
__interrupt void
CANB1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// ADCA_EVT_ISR - ADCA Event Interrupt
//
__interrupt void
ADCA_EVT_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// ADCA2_ISR - ADCA Interrupt 2
//
__interrupt void
ADCA2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// ADCA3_ISR - ADCA Interrupt 3
//
__interrupt void
ADCA3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// ADCA4_ISR - ADCA Interrupt 4
//
__interrupt void
ADCA4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// ADCB_EVT_ISR - ADCB Event Interrupt
//
__interrupt void
ADCB_EVT_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// ADCB2_ISR - ADCB Interrupt 2
//
__interrupt void
ADCB2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// ADCB3_ISR - ADCB Interrupt 3
//
__interrupt void
ADCB3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// ADCB4_ISR - ADCB Interrupt 4
//
__interrupt void
ADCB4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// CLA1_1_ISR - CLA1 Interrupt 1
//
__interrupt void
CLA1_1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// CLA1_2_ISR - CLA1 Interrupt 2
//
__interrupt void
CLA1_2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// CLA1_3_ISR - CLA1 Interrupt 3
//
__interrupt void
CLA1_3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// CLA1_4_ISR - CLA1 Interrupt 4
//
__interrupt void
CLA1_4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// CLA1_5_ISR - CLA1 Interrupt 5
//
__interrupt void
CLA1_5_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// CLA1_6_ISR - CLA1 Interrupt 6
//
__interrupt void
CLA1_6_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// CLA1_7_ISR - CLA1 Interrupt 7
//
__interrupt void
CLA1_7_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// CLA1_8_ISR - CLA1 Interrupt 8
//
__interrupt void
CLA1_8_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// XINT3_ISR - XINT3 Interrupt
//
__interrupt void
XINT3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// XINT4_ISR - XINT4 Interrupt
//
__interrupt void
XINT4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// XINT5_ISR - XINT5 Interrupt
//
__interrupt void
XINT5_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// FPU_OVERFLOW_ISR - FPU Overflow Interrupt
//
__interrupt void
FPU_OVERFLOW_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// FPU_UNDERFLOW_ISR - FPU Underflow Interrupt
//
__interrupt void
FPU_UNDERFLOW_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// SD1_ISR - SDFM1 Interrupt
//
__interrupt void
SD1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// SD1DR1_ISR - SDFM1 DR Interrupt 1
//
__interrupt void
SD1DR1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// SD1DR2_ISR - SDFM1 DR Interrupt 2
//
__interrupt void
SD1DR2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// SD1DR3_ISR - SDFM1 DR Interrupt 3
//
__interrupt void
SD1DR3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// SD1DR4_ISR - SDFM1 DR Interrupt 4
//
__interrupt void
SD1DR4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}


//
// FSITXA1_ISR - FSITXA1_ISR Interrupt
//
__interrupt void
FSITXA1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// FSITXA2_ISR - FSITXA2_ISR Interrupt
//
__interrupt void
FSITXA2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// FSIRXA1_ISR - FSIRXA1_ISR Interrupt
//
__interrupt void
FSIRXA1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// FSIRXA2_ISR - FSIRXA2_ISR Interrupt
//
__interrupt void
FSIRXA2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// CLA1PROMCRC - CLA1PROMCRC Interrupt
//
__interrupt void
CLA1PROMCRC_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// LINA_0 - LINA Interrupt 0
//
__interrupt void
LINA_0_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// LINA_1 - LINA Interrupt 1
//
__interrupt void
LINA_1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// PMBUSA - PMBUSA Interrupt
//
__interrupt void
PMBUSA_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// ADCC_EVT_ISR - ADCC Event Interrupt
//
__interrupt void
ADCC_EVT_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// ADCC2_ISR - ADCC Interrupt 2
//
__interrupt void
ADCC2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// ADCC3_ISR - ADCC Interrupt 3
//
__interrupt void
ADCC3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// ADCC4_ISR - ADCC Interrupt 4
//
__interrupt void
ADCC4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// RAM_CORRECTABLE_ERROR_ISR - RAM Correctable Error Interrupt
//
__interrupt void
RAM_CORRECTABLE_ERROR_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// FLASH_CORRECTABLE_ERROR_ISR - Flash Correctable Error Interrupt
//
__interrupt void
FLASH_CORRECTABLE_ERROR_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// RAM_ACCESS_VIOLATION_ISR - RAM Access Violation Interrupt
//
__interrupt void
RAM_ACCESS_VIOLATION_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// SYS_PLL_SLIP_ISR - System PLL Slip Interrupt
//
__interrupt void
SYS_PLL_SLIP_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// CLA_OVERFLOW_ISR - CLA Overflow Interrupt
//
__interrupt void
CLA_OVERFLOW_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// CLA_UNDERFLOW_ISR - CLA Underflow Interrupt
//
__interrupt void
CLA_UNDERFLOW_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    ESTOP0;
    for(;;);
}

//
// Catch-all Default ISRs
//

//
// PIE_RESERVED_ISR - Reserved ISR
//
__interrupt void
PIE_RESERVED_ISR(void)
{
    ESTOP0;
    for(;;);
}

//
// EMPTY_ISR - Only does a return
//
__interrupt void
EMPTY_ISR(void)
{

}

//
// NOTUSED_ISR - Unused ISR
//
__interrupt void
NOTUSED_ISR(void)
{
    ESTOP0;
    for(;;);
}

//
// End of File
//

