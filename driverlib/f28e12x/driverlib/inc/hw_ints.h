//###########################################################################
//
// FILE:   hw_ints.h
//
// TITLE:  Definitions of interrupt numbers for use with interrupt.c.
//
//###########################################################################
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

#ifndef HW_INTS_H
#define HW_INTS_H

//*****************************************************************************
//
// PIE Interrupt Numbers
//
// 0x00FF = PIE Table Row #
// 0xFF00 = PIE Table Column #
// 0xFFFF0000 = PIE Vector ID
//
//*****************************************************************************
#define INT_TIMER1                  0x000D0000U // CPU Timer 1 Interrupt
#define INT_TIMER2                  0x000E0000U // CPU Timer 2 Interrupt
#define INT_DATALOG                 0x000F0000U // Datalogging Interrupt
#define INT_RTOS                    0x00100000U // RTOS Interrupt from ERAD
#define INT_EMU                     0x00110000U // Emulation Interrupt
#define INT_NMI                     0x00120000U // Non-Maskable Interrupt
#define INT_ILLEGAL                 0x00130000U // Illegal Operation Trap
#define INT_USER1                   0x00140000U // User Defined Trap 1
#define INT_USER2                   0x00150000U // User Defined Trap 2
#define INT_USER3                   0x00160000U // User Defined Trap 3
#define INT_USER4                   0x00170000U // User Defined Trap 4
#define INT_USER5                   0x00180000U // User Defined Trap 5
#define INT_USER6                   0x00190000U // User Defined Trap 6
#define INT_USER7                   0x001A0000U // User Defined Trap 7
#define INT_USER8                   0x001B0000U // User Defined Trap 8
#define INT_USER9                   0x001C0000U // User Defined Trap 9
#define INT_USER10                  0x001D0000U // User Defined Trap 10
#define INT_USER11                  0x001E0000U // User Defined Trap 11
#define INT_USER12                  0x001F0000U // User Defined Trap 12
#define INT_ADCA1                   0x00200101U // 1.1 - ADCA Interrupt 1
#define INT_XINT1                   0x00220103U // 1.3 - XINT1 Interrupt
#define INT_XINT2                   0x00230104U // 1.4 - XINT2 Interrupt
#define INT_SYS_ERR                 0x00240201U // 2.1 - SYS_ERR Interrupt
#define INT_TIMER0                  0x00250202U // 2.2 - Timer 0 Interrupt
#define INT_WAKE                    0x00260203U // 2.3 - Standby and Halt Wakeup Interrupt
#define INT_MCPWM1                  0x00270204U // 2.4 - MCPWM1 Interrupt
#define INT_MCPWM3                  0x00290302U // 3.2 - MCPWM3 Interrupt
#define INT_ECAP1                   0x002E0403U // 4.3 - eCAP1 Interrupt
#define INT_EQEP1                   0x00300501U // 5.1 - eQEP1 Interrupt
#define INT_SPIA_RX                 0x00310502U // 5.2 - SPIA Receive Interrupt
#define INT_SPIA_TX                 0x00320503U // 5.3 - SPIA Transmit Interrupt
#define INT_DCC0                    0x00350602U // 6.2 - DCC0 Interrupt
#define INT_DMA_CH1                 0x00360603U // 6.3 - DMA Channel 1 Interrupt
#define INT_DMA_CH2                 0x00370604U // 6.4 - DMA Channel 2 Interrupt
#define INT_I2CA                    0x00390702U // 7.2 - I2CA Interrupt 1
#define INT_I2CA_FIFO               0x003A0703U // 7.3 - I2CA Interrupt 2
#define INT_SCIA_RX                 0x003B0704U // 7.4 - SCIA Receive Interrupt
#define INT_SCIA_TX                 0x003C0801U // 8.1 - SCIA Transmit Interrupt
#define INT_SCIB_RX                 0x003D0802U // 8.2 - SCIB Receive Interrupt
#define INT_SCIB_TX                 0x003E0803U // 8.3 - SCIB Transmit Interrupt
#define INT_UARTA                   0x00410902U // 9.2 - UARTA Interrupt
#define INT_ADCA_EVT                0x00420903U // 9.3 - ADCA Event Interrupt
#define INT_ADCA2                   0x00430904U // 9.4 - ADCA Interrupt 2
#define INT_XINT3                   0x00460A03U // 10.3 - XINT3 Interrupt
#define INT_XINT4                   0x00470A04U // 10.4 - XINT4 Interrupt
#define INT_XINT5                   0x00480B01U // 11.1 - XINT5 Interrupt
#define INT_FLSS                    0x00490B02U // 11.2 - Interrupt from flash sub-system

//*****************************************************************************
//
// The following interrupts are added manually
// DO NOT EDIT / REMOVE !!!
//
//*****************************************************************************
#define INT_FREERTOS                0x004A0B03U // 11.3 - FreeRTOS SW interrupt

#endif // HW_INTS_H
