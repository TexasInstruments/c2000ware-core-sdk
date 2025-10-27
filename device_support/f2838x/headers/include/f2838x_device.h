//###########################################################################
//
// FILE:   f2838x_device.h
//
// TITLE:  F2838x Device Definitions.
//
//###########################################################################
//
//
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
//###########################################################################

#ifndef F2838x_DEVICE_H
#define F2838x_DEVICE_H

#if (!defined(CPU1) && !defined(CPU2))
#error "You must define CPU1 or CPU2 in your project properties.  Otherwise, the offsets in your header files will be inaccurate."
#endif

#if (defined(CPU1) && defined(CPU2))
#error "You have defined both CPU1 and CPU2 in your project properties.  Only a single CPU should be defined."
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define   TARGET   1

#ifndef __TMS320C28XX__
#define __cregister
#endif  //__TMS320C28xx__
//
// User To Select Target Device:
//
#define   F28_2838x    TARGET

//
// Common CPU Definitions:
//
extern __cregister volatile unsigned int IFR;
extern __cregister volatile unsigned int IER;

#define  EINT   __asm(" clrc INTM")
#define  DINT   __asm(" setc INTM")
#define  ERTM   __asm(" clrc DBGM")
#define  DRTM   __asm(" setc DBGM")
#ifndef  EALLOW
#ifndef _TMS320C28XX_CLA_
#define  EALLOW __eallow()
#else
#define  EALLOW __meallow()
#endif // _TMS320C28XX_CLA_
#endif // EALLOW
 
#ifndef  EDIS
#ifndef _TMS320C28XX_CLA_
#define  EDIS   __edis()
#else
#define  EDIS   __medis()
#endif // _TMS320C28XX_CLA_
#endif // EDIS
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

#ifndef C28X_BIT0
#define C28X_BIT0    0x00000001
#endif

#ifndef C28X_BIT1
#define C28X_BIT1    0x00000002
#endif

#ifndef C28X_BIT2
#define C28X_BIT2    0x00000004
#endif

#ifndef C28X_BIT3
#define C28X_BIT3    0x00000008
#endif

#ifndef C28X_BIT4
#define C28X_BIT4    0x00000010
#endif

#ifndef C28X_BIT5
#define C28X_BIT5    0x00000020
#endif

#ifndef C28X_BIT6
#define C28X_BIT6    0x00000040
#endif

#ifndef C28X_BIT7
#define C28X_BIT7    0x00000080
#endif

#ifndef C28X_BIT8
#define C28X_BIT8    0x00000100
#endif

#ifndef C28X_BIT9
#define C28X_BIT9    0x00000200
#endif

#ifndef C28X_BIT10
#define C28X_BIT10   0x00000400
#endif

#ifndef C28X_BIT11
#define C28X_BIT11   0x00000800
#endif

#ifndef C28X_BIT12
#define C28X_BIT12   0x00001000
#endif

#ifndef C28X_BIT13
#define C28X_BIT13   0x00002000
#endif

#ifndef C28X_BIT14
#define C28X_BIT14   0x00004000
#endif

#ifndef C28X_BIT15
#define C28X_BIT15   0x00008000
#endif

#ifndef C28X_BIT16
#define C28X_BIT16   0x00010000
#endif

#ifndef C28X_BIT17
#define C28X_BIT17   0x00020000
#endif

#ifndef C28X_BIT18
#define C28X_BIT18   0x00040000
#endif

#ifndef C28X_BIT19
#define C28X_BIT19   0x00080000
#endif

#ifndef C28X_BIT20
#define C28X_BIT20   0x00100000
#endif

#ifndef C28X_BIT21
#define C28X_BIT21   0x00200000
#endif

#ifndef C28X_BIT22
#define C28X_BIT22   0x00400000
#endif

#ifndef C28X_BIT23
#define C28X_BIT23   0x00800000
#endif

#ifndef C28X_BIT24
#define C28X_BIT24   0x01000000
#endif

#ifndef C28X_BIT25
#define C28X_BIT25   0x02000000
#endif

#ifndef C28X_BIT26
#define C28X_BIT26   0x04000000
#endif

#ifndef C28X_BIT27
#define C28X_BIT27   0x08000000
#endif

#ifndef C28X_BIT28
#define C28X_BIT28   0x10000000
#endif

#ifndef C28X_BIT29
#define C28X_BIT29   0x20000000
#endif

#ifndef C28X_BIT30
#define C28X_BIT30   0x40000000
#endif

#ifndef C28X_BIT31
#define C28X_BIT31   0x80000000
#endif

//
// For Portability, User Is Recommended To Use the C99 Standard integer types
//
#if !defined(__TMS320C28XX_CLA__)
#include <assert.h>
#include <stdarg.h>
#endif //__TMS320C28XX_CLA__
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

//
// C++ Bool Compatibility
//
#if defined(__cplusplus)
typedef bool _Bool;
#endif

//
// C99 defines boolean type to be _Bool, but this doesn't match the format of
// the other standard integer types.  bool_t has been defined to fill this gap.
//
typedef _Bool bool_t;

//
//used for a bool function return status
//
typedef _Bool status_t;

#ifndef SUCCESS
#define SUCCESS     true
#endif

#ifndef FAIL
#define FAIL        false
#endif

//
// The following data types are included for compatibility with legacy code,
// they are not recommended for use in new software.  Please use the C99
// types included above
//
#if (!defined(DSP28_DATA_TYPES) && !defined(F28_DATA_TYPES))
#define DSP28_DATA_TYPES
#define F28_DATA_TYPES

#ifdef __TMS320C28XX_CLA__
typedef short           						int16;
typedef long            						int32;
typedef unsigned char   						Uint8;
typedef unsigned short  						Uint16;
typedef unsigned long   						Uint32;
typedef float           						float32;
typedef long double     						float64;
typedef struct { Uint32 low32; Uint32 high32; } Uint64;
typedef struct { int32  low32; int32  high32; } int64;
#else // __TMS320C28XX__
typedef int             	int16;
typedef long            	int32;
typedef long long			int64;
typedef unsigned int    	Uint16;
typedef unsigned long   	Uint32;
typedef unsigned long long	Uint64;
typedef float           	float32;
typedef long double     	float64;
#endif

#endif //(!defined(DSP28_DATA_TYPES) && !defined(F28_DATA_TYPES))
//
// The following data types are for use with byte addressable peripherals.
// See compiler documentation on the byte_peripheral type attribute.
//
#ifndef __TMS320C28XX_CLA__
#if __TI_COMPILER_VERSION__ >= 16006000
typedef unsigned int bp_16 __attribute__((byte_peripheral));
typedef unsigned long bp_32 __attribute__((byte_peripheral));
#endif
#endif

//
// Include All Peripheral Header Files:
//
#include "f2838x_adc.h"
#include "f2838x_analogsubsys.h"
#include "f2838x_bgcrc.h"
#include "f2838x_cla.h"
#include "f2838x_clb.h"
#include "f2838x_clbxbar.h"
#include "f2838x_cmpss.h"
#include "f2838x_cputimer.h"
#include "f2838x_dac.h"
#include "f2838x_dcsm.h"
#include "f2838x_dma.h"
#include "f2838x_ecap.h"
#include "f2838x_ecat_ss.h"
#include "f2838x_emif.h"
#include "f2838x_epwm.h"                // Enhanced PWM
#include "f2838x_epwmxbar.h"
#include "f2838x_eqep.h"
#include "f2838x_erad.h"
#include "f2838x_flash.h"
#include "f2838x_fsi.h"
#include "f2838x_gpio.h"                // General Purpose I/O Registers
#include "f2838x_hwbist.h"
#include "f2838x_i2c.h"
#include "f2838x_inputxbar.h"
#include "f2838x_ipc.h"
#include "f2838x_mcbsp.h"
#include "f2838x_memconfig.h"
#include "f2838x_nmiintrupt.h"          // NMI Interrupt Registers
#include "f2838x_otp.h"
#include "f2838x_outputxbar.h"
#include "f2838x_pbist.h"
#include "f2838x_piectrl.h"             // PIE Control Registers
#include "f2838x_pievect.h"
#include "f2838x_pmbus.h"
#include "f2838x_sci.h"
#include "f2838x_sdfm.h"
#include "f2838x_spi.h"
#include "f2838x_sysctrl.h"             // System Control/Power Modes
#include "f2838x_wwd.h"
#include "f2838x_xbar.h"
#include "f2838x_xint.h"                // External Interrupts

//
// byte_peripheral attribute is only supported on the C28
//
#ifndef __TMS320C28XX_CLA__
#if __TI_COMPILER_VERSION__ >= 16006000
#include "f2838x_can.h"
#include "f2838x_dcc.h"
//
// Include MCAN bitfield header only if driverlib header is not already included
//
#ifndef HW_MCANSS_H_
#include "f2838x_mcan.h"       
#endif
#endif
#endif

#ifdef __cplusplus
}
#endif                                  // extern "C"

#endif                                  // end of F2838x_DEVICE_H definition

//
// End of file.
//
