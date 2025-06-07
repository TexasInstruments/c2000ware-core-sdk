//###########################################################################
//
// FILE:   f280013x_device.h
//
// TITLE:  f280013x Device Definitions.
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

#ifndef f280013x_DEVICE_H
#define f280013x_DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif


#ifndef __TMS320C28XX__
#define __cregister
#endif  //__TMS320C28xx__

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

#define BIT0    0x00000001
#define BIT1    0x00000002
#define BIT2    0x00000004
#define BIT3    0x00000008
#define BIT4    0x00000010
#define BIT5    0x00000020
#define BIT6    0x00000040
#define BIT7    0x00000080
#define BIT8    0x00000100
#define BIT9    0x00000200
#define BIT10   0x00000400
#define BIT11   0x00000800
#define BIT12   0x00001000
#define BIT13   0x00002000
#define BIT14   0x00004000
#define BIT15   0x00008000
#define BIT16   0x00010000
#define BIT17   0x00020000
#define BIT18   0x00040000
#define BIT19   0x00080000
#define BIT20   0x00100000
#define BIT21   0x00200000
#define BIT22   0x00400000
#define BIT23   0x00800000
#define BIT24   0x01000000
#define BIT25   0x02000000
#define BIT26   0x04000000
#define BIT27   0x08000000
#define BIT28   0x10000000
#define BIT29   0x20000000
#define BIT30   0x40000000
#define BIT31   0x80000000

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
// Used for a bool function return status
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
typedef short                                   int16;
typedef long                                    int32;
typedef unsigned char                           Uint8;
typedef unsigned short                          Uint16;
typedef unsigned long                           Uint32;
typedef float                                   float32;
typedef long double                             float64;
typedef struct { Uint32 low32; Uint32 high32; } Uint64;
typedef struct { int32  low32; int32  high32; } int64;
#else // __TMS320C28XX__
typedef int                                     int16;
typedef long                                    int32;
typedef long long                               int64;
typedef unsigned int                            Uint16;
typedef unsigned long                           Uint32;
typedef unsigned long long                      Uint64;
#ifndef C2000_IEEE754_TYPES
#define C2000_IEEE754_TYPES
#ifdef __TI_EABI__
typedef float         float32_t;
typedef double        float64_t;
#else // TI COFF
typedef float         float32_t;
typedef long double   float64_t;
#endif // __TI_EABI__
#endif // C2000_IEEE754_TYPES
#endif //__TMS320C28XX_CLA__

#endif //(!defined(DSP28_DATA_TYPES) && !defined(F28_DATA_TYPES))

//
// The following data types are for use with byte addressable peripherals.
// See compiler documentation on the byte_peripheral type attribute.
//
#ifndef __TMS320C28XX_CLA__
typedef unsigned int bp_16 __attribute__((byte_peripheral));
typedef unsigned long bp_32 __attribute__((byte_peripheral));
#endif

//
// Include All Peripheral Header Files:
//
#include "f280013x_adc.h"
#include "f280013x_analogsubsys.h"
#include "f280013x_cmpss.h"
#include "f280013x_cmpss_lite.h"
#include "f280013x_cputimer.h"
#include "f280013x_dcsm.h"
#include "f280013x_ecap.h"
#include "f280013x_epg.h"
#include "f280013x_epwm.h"
#include "f280013x_epwm_xbar.h"
#include "f280013x_eqep.h"
#include "f280013x_flash.h"
#include "f280013x_gpio.h"
#include "f280013x_i2c.h"
#include "f280013x_input_xbar.h"
#include "f280013x_memconfig.h"
#include "f280013x_nmiintrupt.h"
#include "f280013x_otp.h"
#include "f280013x_output_xbar.h"
#include "f280013x_piectrl.h"
#include "f280013x_pievect.h"
#include "f280013x_sci.h"
#include "f280013x_spi.h"
#include "f280013x_sysctrl.h"
#include "f280013x_xbar.h"
#include "f280013x_xint.h"
#include "f280013x_tempsensorconv.h"

//
// byte_peripheral attribute is only supported on the C28
//
#ifndef __TMS320C28XX_CLA__
#include "f280013x_can.h"
#include "f280013x_dcc.h"
#endif

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif                                  // end of f280013x_DEVICE_H definition

//===========================================================================
// End of file.
//===========================================================================
