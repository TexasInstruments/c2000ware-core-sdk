//###########################################################################
//
// FILE:   hw_ints.h
//
// TITLE:  Macros that define the interrupt assignment.
//
//###########################################################################
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
//###########################################################################

#ifndef HW_INTS_H
#define HW_INTS_H

//*****************************************************************************
// The following are defines for the fault assignments.
//*****************************************************************************
#define FAULT_NMI                   2U // NMI
#define FAULT_HARD                  3U // HardFault
#define FAULT_MPU                   4U // MemManage
#define FAULT_BUS                   5U // BusFault
#define FAULT_USAGE                 6U // UsageFault
#define FAULT_SVCALL                11U // SVCall
#define FAULT_DEBUG                 12U // Debug Monitor
#define FAULT_PENDSV                14U // PendSV
#define FAULT_SYSTICK               15U // SysTick

//*****************************************************************************
// The following are defines for the interrupt assignments.
//*****************************************************************************
#define INT_MCANSS_0                16U // MCANSS_0 Interrupt
#define INT_MCANSS_1                17U // MCANSS_1 Interrupt
#define INT_MCANSS_WAKE_AND_TS_PLS  18U // MCANSS_WAKE_AND_TS_PLS Interrupt
#define INT_MCANSS_ECC_CORR_PLS     19U // MCANSS_ECC_CORR_PLS Interrupt
#define INT_ECAT                    21U // ECAT Interrupt
#define INT_ECAT_SYNC0              22U // ECAT_SYNC0 Interrupt
#define INT_ECAT_SYNC1              23U // ECAT_SYNC1 Interrupt
#define INT_ECAT_RST                24U // ECAT_RST Interrupt
#define INT_CANA0                   25U // CANA0 Interrupt
#define INT_CANA1                   26U // CANA1 Interrupt
#define INT_CANB0                   27U // CANB0 Interrupt
#define INT_CANB1                   28U // CANB1 Interrupt
#define INT_EMAC                    29U // EMAC Interrupt
#define INT_EMAC_TX0                30U // EMAC_TX0 Interrupt
#define INT_EMAC_TX1                31U // EMAC_TX1 Interrupt
#define INT_EMAC_RX0                32U // EMAC_RX0 Interrupt
#define INT_EMAC_RX1                33U // EMAC_RX1 Interrupt
#define INT_UART0                   34U // UART0 Interrupt
#define INT_SSI0                    36U // SSI0 Interrupt
#define INT_I2C0                    38U // I2C0 Interrupt
#define INT_USB0                    40U // USB Interrupt
#define INT_UDMA_SW                 41U // UDMA_SW Interrupt
#define INT_UDMA_ERR                42U // UDMA_ERR Interrupt
#define INT_CPU1TOCMIPC0            45U // CPU1TOCMIPC0 Interrupt
#define INT_CPU1TOCMIPC1            46U // CPU1TOCMIPC1 Interrupt
#define INT_CPU1TOCMIPC2            47U // CPU1TOCMIPC2 Interrupt
#define INT_CPU1TOCMIPC3            48U // CPU1TOCMIPC3 Interrupt
#define INT_CPU1TOCMIPC4            49U // CPU1TOCMIPC4 Interrupt
#define INT_CPU1TOCMIPC5            50U // CPU1TOCMIPC5 Interrupt
#define INT_CPU1TOCMIPC6            51U // CPU1TOCMIPC6 Interrupt
#define INT_CPU1TOCMIPC7            52U // CPU1TOCMIPC7 Interrupt
#define INT_CPU2TOCMIPC0            53U // CPU2TOCMIPC0 Interrupt
#define INT_CPU2TOCMIPC1            54U // CPU2TOCMIPC1 Interrupt
#define INT_CPU2TOCMIPC2            55U // CPU2TOCMIPC2 Interrupt
#define INT_CPU2TOCMIPC3            56U // CPU2TOCMIPC3 Interrupt
#define INT_CPU2TOCMIPC4            57U // CPU2TOCMIPC4 Interrupt
#define INT_CPU2TOCMIPC5            58U // CPU2TOCMIPC5 Interrupt
#define INT_CPU2TOCMIPC6            59U // CPU2TOCMIPC6 Interrupt
#define INT_CPU2TOCMIPC7            60U // CPU2TOCMIPC7 Interrupt
#define INT_FMC                     61U // FMC Interrupt
#define INT_FMC_CORR_ERR            62U // FMC_CORR_ERR Interrupt
#define INT_AES                     63U // AES Interrupt
#define INT_TIMER0                  64U // TIMER0 Interrupt
#define INT_TIMER1                  65U // TIMER1 Interrupt
#define INT_TIMER2                  66U // TIMER2 Interrupt
#define INT_CMRAM_TESTERROR_LOG     67U // CMRAM_TESTERROR_LOG Interrupt

//*****************************************************************************
// The following are defines for the total number of interrupts.
//*****************************************************************************
#define NUM_INTERRUPTS                 80U

//*****************************************************************************
// The following are defines for the total number of priority levels.
//*****************************************************************************
#define NUM_PRIORITY                   8U
#define NUM_PRIORITY_BITS              3U


#endif // HW_INTS_H


