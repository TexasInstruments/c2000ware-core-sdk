//###########################################################################
//
// FILE:   DSP2803x_Device.h
//
// TITLE:  DSP2803x Device Definitions.
//
//###########################################################################
// $TI Release: $
// $Release Date: $
// $Copyright:
// Copyright (C) 2009-2024 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef DSP2803x_DEVICE_H
#define DSP2803x_DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

//
// Defines
//
#define   TARGET   1

//
// Defines for user to select target device
//
#define   DSP28_28030PAG   0
#define   DSP28_28030PN    0

#define   DSP28_28031PAG   0
#define   DSP28_28031PN    0

#define   DSP28_28032PAG   0
#define   DSP28_28032PN    0

#define   DSP28_28033PAG   0
#define   DSP28_28033PN    0

#define   DSP28_28034PAG   0
#define   DSP28_28034PN    0

#define   DSP28_28035PAG   0
#define   DSP28_28035PN    TARGET

//
// Common CPU Definitions
//
extern __cregister volatile unsigned int IFR;
extern __cregister volatile unsigned int IER;

#define  EINT   __asm(" clrc INTM")
#define  DINT   __asm(" setc INTM")
#define  ERTM   __asm(" clrc DBGM")
#define  DRTM   __asm(" setc DBGM")
#define  EALLOW __asm(" EALLOW")
#define  EDIS   __asm(" EDIS")
#define  ESTOP0 __asm(" ESTOP0")

#define M_INT1  0x0001
#define M_INT2  0x0002
#define M_INT3  0x0004
#define M_INT4  0x0008
#define M_INT5  0x0010
#define M_INT6  0x0020
#define M_INT7  0x0040
#define M_INT8  0x0080
#define M_INT9  0x0100
#define M_INT10 0x0200
#define M_INT11 0x0400
#define M_INT12 0x0800
#define M_INT13 0x1000
#define M_INT14 0x2000
#define M_DLOG  0x4000
#define M_RTOS  0x8000

#define BIT0    0x0001
#define BIT1    0x0002
#define BIT2    0x0004
#define BIT3    0x0008
#define BIT4    0x0010
#define BIT5    0x0020
#define BIT6    0x0040
#define BIT7    0x0080
#define BIT8    0x0100
#define BIT9    0x0200
#define BIT10   0x0400
#define BIT11   0x0800
#define BIT12   0x1000
#define BIT13   0x2000
#define BIT14   0x4000
#define BIT15   0x8000

//
// For Portability, User Is Recommended To Use Following Data Type Size
// Definitions For 16-bit and 32-Bit Signed/Unsigned Integers
//
#ifndef DSP28_DATA_TYPES
#define DSP28_DATA_TYPES
typedef int             int16;
typedef long            int32;
typedef unsigned int    Uint16;
typedef unsigned long   Uint32;
typedef float           float32;
typedef long double     float64;
#endif

//
// Included Peripheral Header Files
//
#include "DSP2803x_Adc.h"                // ADC Registers
#include "DSP2803x_BootVars.h"           // Boot ROM Variables
#include "DSP2803x_DevEmu.h"             // Device Emulation Registers
#include "DSP2803x_Cla.h"                // Control Law Accelerator Registers
#include "DSP2803x_Comp.h"               // Comparator Registers
#include "DSP2803x_CpuTimers.h"          // 32-bit CPU Timers
#include "DSP2803x_ECan.h"               // Enhanced eCAN Registers
#include "DSP2803x_ECap.h"               // Enhanced Capture
#include "DSP2803x_EPwm.h"               // Enhanced PWM
#include "DSP2803x_EQep.h"               // Enhanced QEP
#include "DSP2803x_Gpio.h"               // General Purpose I/O Registers
#include "DSP2803x_HRCap.h"              // High Resolution Capture
#include "DSP2803x_I2c.h"                // I2C Registers
#include "DSP2803x_Lin.h"                // LIN Registers
#include "DSP2803x_NmiIntrupt.h"         // NMI Interrupt Registers
#include "DSP2803x_PieCtrl.h"            // PIE Control Registers
#include "DSP2803x_PieVect.h"            // PIE Vector Table
#include "DSP2803x_Spi.h"                // SPI Registers
#include "DSP2803x_Sci.h"                // SCI Registers
#include "DSP2803x_SysCtrl.h"            // System Control/Power Modes
#include "DSP2803x_XIntrupt.h"           // External Interrupts

#if (DSP28_28035PN||DSP28_28034PN||DSP28_28033PN||DSP28_28032PN \
        ||DSP28_28031PN||DSP28_28030PN)
#define DSP28_COMP1 1
#define DSP28_COMP2 1
#define DSP28_COMP3 1
#define DSP28_EPWM1 1
#define DSP28_EPWM2 1
#define DSP28_EPWM3 1
#define DSP28_EPWM4 1
#define DSP28_EPWM5 1
#define DSP28_EPWM6 1
#define DSP28_EPWM7 1
#define DSP28_ECAP1 1
#define DSP28_EQEP1 1
#define DSP28_ECANA 1
#define DSP28_HRCAP1 1
#define DSP28_HRCAP2 1
#define DSP28_SPIA  1
#define DSP28_SPIB  1
#define DSP28_SCIA  1
#define DSP28_I2CA  1
#define DSP28_LINA  1
#endif

#if (DSP28_28035PAG||DSP28_28034PAG||DSP28_28033PAG||DSP28_28032PAG \
        ||DSP28_28031PAG||DSP28_28030PAG)
#define DSP28_COMP1 1
#define DSP28_COMP2 1
#define DSP28_COMP3 1
#define DSP28_EPWM1 1
#define DSP28_EPWM2 1
#define DSP28_EPWM3 1
#define DSP28_EPWM4 1
#define DSP28_EPWM5 1
#define DSP28_EPWM6 1
#define DSP28_EPWM7 0
#define DSP28_ECAP1 1
#define DSP28_EQEP1 1
#define DSP28_ECANA 1
#define DSP28_HRCAP1 1
#define DSP28_HRCAP2 1
#define DSP28_SPIA  1
#define DSP28_SPIB  0
#define DSP28_SCIA  1
#define DSP28_I2CA  1
#define DSP28_LINA  1
#endif

//
// Timer definitions based on System Clock
// 60 MHz devices
//
	#define      mSec0_5          30000           // 0.5 mS
	#define      mSec0_75         45000           // 0.75 mS
	#define      mSec1            60000           // 1.0 mS
	#define      mSec2            120000          // 2.0 mS
	#define      mSec5            300000          // 5.0 mS
	#define      mSec7_5          450000          // 7.5 mS
	#define      mSec10           600000          // 10 mS
	#define      mSec20           1200000         // 20 mS
	#define      mSec50           3000000         // 50 mS
	#define      mSec75           4500000         // 75 mS
	#define      mSec100          6000000         // 100 mS
	#define      mSec200          12000000        // 200 mS
	#define      mSec500          30000000        // 500 mS
	#define      mSec750          45000000        // 750 mS
	#define      mSec1000         60000000        // 1000 mS
	#define      mSec2000         120000000       // 2000 mS
	#define      mSec5000         300000000       // 5000 mS

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of DSP2803x_DEVICE_H definition

//
// End of file
//

