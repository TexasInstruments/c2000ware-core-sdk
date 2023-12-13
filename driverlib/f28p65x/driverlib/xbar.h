//###########################################################################
//
// FILE:   xbar.h
//
// TITLE:  C28x X-BAR driver.
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

#ifndef XBAR_H
#define XBAR_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \addtogroup xbar_api XBAR
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_clbxbar.h"
#include "inc/hw_epwmxbar.h"
#include "inc/hw_inputxbar.h"
#include "inc/hw_outputxbar.h"
#include "inc/hw_clboutputxbar.h"
#include "inc/hw_mindbxbar.h"
#include "inc/hw_iclxbar.h"
#include "inc/hw_xbar.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "cpu.h"
#include "debug.h"

//*****************************************************************************
//
// Useful defines used within the driver functions.
// Not intended for use by application code.
//
//*****************************************************************************
#define XBARA_EPWM_CFG_REG_BASE   (EPWMXBARA_BASE + XBAR_O_OUT1MUX0TO15CFG)
#define XBARA_EPWM_EN_REG_BASE    (EPWMXBARA_BASE + XBAR_O_OUT1MUXENABLE)

#define XBARB_EPWM_CFG_REG_BASE   (EPWMXBARB_BASE + XBAR_O_OUT1MUX0TO15CFG)
#define XBARB_EPWM_EN_REG_BASE    (EPWMXBARB_BASE + XBAR_O_OUT1MUXENABLE)

#define XBAR_CLB_CFG_REG_BASE     (CLBXBAR_BASE + XBAR_O_AUXSIG0MUX0TO15CFG)
#define XBAR_CLB_EN_REG_BASE      (CLBXBAR_BASE + XBAR_O_AUXSIG0MUXENABLE)

#define XBAR_INPUT_FLG_INPUT_M    0x00FFU
#define XBAR_INPUT_FLG_REG_M      0xFF00U
#define XBAR_INPUT_FLG_REG_1      0x0000U
#define XBAR_INPUT_FLG_REG_2      0x0100U
#define XBAR_INPUT_FLG_REG_3      0x0200U
#define XBAR_INPUT_FLG_REG_4      0x0300U
#define XBAR_INPUT_FLG_REG_5      0x0400U
#define XBAR_INPUT_FLG_REG_6      0x0500U
#define XBAR_INPUT_FLG_REG_7      0x0600U
#define XBAR_INPUT_FLG_REG_8      0x0700U
#define XBAR_INPUT_FLG_REG_9      0x0800U
#define XBAR_INPUT_FLG_REG_10     0x0900U
#define XBAR_INPUT_FLG_REG_11     0x0A00U
#define XBAR_INPUT_FLG_REG_12     0x0B00U
#define XBAR_INPUT_FLG_REG_13     0x0C00U
#define XBAR_INPUT_FLG_REG_14     0x0D00U
#define XBAR_INPUT_FLG_REG_15     0x0E00U
#define XBAR_INPUT_FLG_REG_16     0x0F00U

#define XBAR_GPIO_MAX_CNT                168U
#define XBAR_GPIO_AIO_MIN_CNT            198U
#define XBAR_GPIO_AIO_MAX_CNT            242U
#define XBAR_NON_GPIO_MIN_CNT            0xFFFDU
#define XBAR_NON_GPIO_MAX_CNT            0xFFFFU

//
// To acheive backward compatibilty for previously defined macros naming
// in XBAR
//

//
//OUTPUTXBAR
//
#define XBAR_OUT_MUX00_SD3FLT1_COMPH            XBAR_OUT_MUX00_SD3FLT1_CEVT1
#define XBAR_OUT_MUX02_SD3FLT1_COMPL            XBAR_OUT_MUX02_SD3FLT1_CEVT2
#define XBAR_OUT_MUX04_SD3FLT2_COMPH            XBAR_OUT_MUX04_SD3FLT2_CEVT1
#define XBAR_OUT_MUX06_SD3FLT2_COMPL            XBAR_OUT_MUX06_SD3FLT2_CEVT2
#define XBAR_OUT_MUX08_SD3FLT3_COMPH            XBAR_OUT_MUX08_SD3FLT3_CEVT1
#define XBAR_OUT_MUX10_SD3FLT3_COMPL            XBAR_OUT_MUX10_SD3FLT3_CEVT2
#define XBAR_OUT_MUX12_SD3FLT4_COMPH            XBAR_OUT_MUX12_SD3FLT4_CEVT1
#define XBAR_OUT_MUX14_SD3FLT4_COMPL            XBAR_OUT_MUX14_SD3FLT4_CEVT2
#define XBAR_OUT_MUX16_SD1FLT1_COMPH            XBAR_OUT_MUX16_SD1FLT1_CEVT1
#define XBAR_OUT_MUX16_SD4FLT1_COMPH            XBAR_OUT_MUX16_SD4FLT1_CEVT1
#define XBAR_OUT_MUX17_SD1FLT1_COMPL            XBAR_OUT_MUX17_SD1FLT1_CEVT2
#define XBAR_OUT_MUX18_SD1FLT2_COMPH            XBAR_OUT_MUX18_SD1FLT2_CEVT1
#define XBAR_OUT_MUX18_SD4FLT1_COMPL            XBAR_OUT_MUX18_SD4FLT1_CEVT2
#define XBAR_OUT_MUX19_SD1FLT2_COMPL            XBAR_OUT_MUX19_SD1FLT2_CEVT2
#define XBAR_OUT_MUX20_SD1FLT3_COMPH            XBAR_OUT_MUX20_SD1FLT3_CEVT1
#define XBAR_OUT_MUX20_SD4FLT2_COMPH            XBAR_OUT_MUX20_SD4FLT2_CEVT1
#define XBAR_OUT_MUX21_SD1FLT3_COMPL            XBAR_OUT_MUX21_SD1FLT3_CEVT2
#define XBAR_OUT_MUX22_SD1FLT4_COMPH            XBAR_OUT_MUX22_SD1FLT4_CEVT1
#define XBAR_OUT_MUX22_SD4FLT2_COMPL            XBAR_OUT_MUX22_SD4FLT2_CEVT2
#define XBAR_OUT_MUX23_SD1FLT4_COMPL            XBAR_OUT_MUX23_SD1FLT4_CEVT2
#define XBAR_OUT_MUX24_SD2FLT1_COMPH            XBAR_OUT_MUX24_SD2FLT1_CEVT1
#define XBAR_OUT_MUX24_SD4FLT3_COMPH            XBAR_OUT_MUX24_SD4FLT3_CEVT1
#define XBAR_OUT_MUX25_SD2FLT1_COMPL            XBAR_OUT_MUX25_SD2FLT1_CEVT2
#define XBAR_OUT_MUX26_SD2FLT2_COMPH            XBAR_OUT_MUX26_SD2FLT2_CEVT1
#define XBAR_OUT_MUX26_SD4FLT3_COMPL            XBAR_OUT_MUX26_SD4FLT3_CEVT2
#define XBAR_OUT_MUX27_SD2FLT2_COMPL            XBAR_OUT_MUX27_SD2FLT2_CEVT2
#define XBAR_OUT_MUX28_SD2FLT3_COMPH            XBAR_OUT_MUX28_SD2FLT3_CEVT1
#define XBAR_OUT_MUX28_SD4FLT4_COMPH            XBAR_OUT_MUX28_SD4FLT4_CEVT1
#define XBAR_OUT_MUX29_SD2FLT3_COMPL            XBAR_OUT_MUX29_SD2FLT3_CEVT2
#define XBAR_OUT_MUX30_SD2FLT4_COMPH            XBAR_OUT_MUX30_SD2FLT4_CEVT1
#define XBAR_OUT_MUX30_SD4FLT4_COMPL            XBAR_OUT_MUX30_SD4FLT4_CEVT2
#define XBAR_OUT_MUX31_SD2FLT4_COMPL            XBAR_OUT_MUX31_SD2FLT4_CEVT2
//
//EPWMXBAR
//
#define XBAR_EPWM_MUX00_SD3FLT1_COMPH            XBAR_EPWM_MUX00_SD3FLT1_CEVT1
#define XBAR_EPWM_MUX02_SD3FLT1_COMPL            XBAR_EPWM_MUX02_SD3FLT1_CEVT2
#define XBAR_EPWM_MUX04_SD3FLT2_COMPH            XBAR_EPWM_MUX04_SD3FLT2_CEVT1
#define XBAR_EPWM_MUX06_SD3FLT2_COMPL            XBAR_EPWM_MUX06_SD3FLT2_CEVT2
#define XBAR_EPWM_MUX08_SD3FLT3_COMPH            XBAR_EPWM_MUX08_SD3FLT3_CEVT1
#define XBAR_EPWM_MUX10_SD3FLT3_COMPL            XBAR_EPWM_MUX10_SD3FLT3_CEVT2
#define XBAR_EPWM_MUX12_SD3FLT4_COMPH            XBAR_EPWM_MUX12_SD3FLT4_CEVT1
#define XBAR_EPWM_MUX14_SD3FLT4_COMPL            XBAR_EPWM_MUX14_SD3FLT4_CEVT2
#define XBAR_EPWM_MUX16_SD1FLT1_COMPH            XBAR_EPWM_MUX16_SD1FLT1_CEVT1
#define XBAR_EPWM_MUX16_SD4FLT1_COMPH            XBAR_EPWM_MUX16_SD4FLT1_CEVT1
#define XBAR_EPWM_MUX17_SD1FLT1_COMPL            XBAR_EPWM_MUX17_SD1FLT1_CEVT2
#define XBAR_EPWM_MUX18_SD1FLT2_COMPH            XBAR_EPWM_MUX18_SD1FLT2_CEVT1
#define XBAR_EPWM_MUX18_SD4FLT1_COMPL            XBAR_EPWM_MUX18_SD4FLT1_CEVT2
#define XBAR_EPWM_MUX19_SD1FLT2_COMPL            XBAR_EPWM_MUX19_SD1FLT2_CEVT2
#define XBAR_EPWM_MUX20_SD1FLT3_COMPH            XBAR_EPWM_MUX20_SD1FLT3_CEVT1
#define XBAR_EPWM_MUX20_SD4FLT2_COMPH            XBAR_EPWM_MUX20_SD4FLT2_CEVT1
#define XBAR_EPWM_MUX21_SD1FLT3_COMPL            XBAR_EPWM_MUX21_SD1FLT3_CEVT2
#define XBAR_EPWM_MUX22_SD1FLT4_COMPH            XBAR_EPWM_MUX22_SD1FLT4_CEVT1
#define XBAR_EPWM_MUX22_SD4FLT2_COMPL            XBAR_EPWM_MUX22_SD4FLT2_CEVT2
#define XBAR_EPWM_MUX23_SD1FLT4_COMPL            XBAR_EPWM_MUX23_SD1FLT4_CEVT2
#define XBAR_EPWM_MUX24_SD2FLT1_COMPH            XBAR_EPWM_MUX24_SD2FLT1_CEVT1
#define XBAR_EPWM_MUX24_SD4FLT3_COMPH            XBAR_EPWM_MUX24_SD4FLT3_CEVT1
#define XBAR_EPWM_MUX25_SD2FLT1_COMPL            XBAR_EPWM_MUX25_SD2FLT1_CEVT2
#define XBAR_EPWM_MUX26_SD2FLT2_COMPH            XBAR_EPWM_MUX26_SD2FLT2_CEVT1
#define XBAR_EPWM_MUX26_SD4FLT3_COMPL            XBAR_EPWM_MUX26_SD4FLT3_CEVT2
#define XBAR_EPWM_MUX27_SD2FLT2_COMPL            XBAR_EPWM_MUX27_SD2FLT2_CEVT2
#define XBAR_EPWM_MUX28_SD2FLT3_COMPH            XBAR_EPWM_MUX28_SD2FLT3_CEVT1
#define XBAR_EPWM_MUX28_SD4FLT4_COMPH            XBAR_EPWM_MUX28_SD4FLT4_CEVT1
#define XBAR_EPWM_MUX29_SD2FLT3_COMPL            XBAR_EPWM_MUX29_SD2FLT3_CEVT2
#define XBAR_EPWM_MUX30_SD2FLT4_COMPH            XBAR_EPWM_MUX30_SD2FLT4_CEVT1
#define XBAR_EPWM_MUX30_SD4FLT4_COMPL            XBAR_EPWM_MUX30_SD4FLT4_CEVT2
#define XBAR_EPWM_MUX31_SD2FLT4_COMPL            XBAR_EPWM_MUX31_SD2FLT4_CEVT2

#ifndef DOXYGEN_PDF_IGNORE
//*****************************************************************************
//
// The following values define the muxes parameter for XBAR_enableEPWMMux(),
// XBAR_enableOutputMux(), XBAR_disableEPWMMux(), and
// XBAR_disableOutputMux().
//
//*****************************************************************************
#define XBAR_MUX00                  0x00000001U //!< Mask for X-BAR mux 0
#define XBAR_MUX01                  0x00000002U //!< Mask for X-BAR mux 1
#define XBAR_MUX02                  0x00000004U //!< Mask for X-BAR mux 2
#define XBAR_MUX03                  0x00000008U //!< Mask for X-BAR mux 3
#define XBAR_MUX04                  0x00000010U //!< Mask for X-BAR mux 4
#define XBAR_MUX05                  0x00000020U //!< Mask for X-BAR mux 5
#define XBAR_MUX06                  0x00000040U //!< Mask for X-BAR mux 6
#define XBAR_MUX07                  0x00000080U //!< Mask for X-BAR mux 7
#define XBAR_MUX08                  0x00000100U //!< Mask for X-BAR mux 8
#define XBAR_MUX09                  0x00000200U //!< Mask for X-BAR mux 9
#define XBAR_MUX10                  0x00000400U //!< Mask for X-BAR mux 10
#define XBAR_MUX11                  0x00000800U //!< Mask for X-BAR mux 11
#define XBAR_MUX12                  0x00001000U //!< Mask for X-BAR mux 12
#define XBAR_MUX13                  0x00002000U //!< Mask for X-BAR mux 13
#define XBAR_MUX14                  0x00004000U //!< Mask for X-BAR mux 14
#define XBAR_MUX15                  0x00008000U //!< Mask for X-BAR mux 15
#define XBAR_MUX16                  0x00010000U //!< Mask for X-BAR mux 16
#define XBAR_MUX17                  0x00020000U //!< Mask for X-BAR mux 17
#define XBAR_MUX18                  0x00040000U //!< Mask for X-BAR mux 18
#define XBAR_MUX19                  0x00080000U //!< Mask for X-BAR mux 19
#define XBAR_MUX20                  0x00100000U //!< Mask for X-BAR mux 20
#define XBAR_MUX21                  0x00200000U //!< Mask for X-BAR mux 21
#define XBAR_MUX22                  0x00400000U //!< Mask for X-BAR mux 22
#define XBAR_MUX23                  0x00800000U //!< Mask for X-BAR mux 23
#define XBAR_MUX24                  0x01000000U //!< Mask for X-BAR mux 24
#define XBAR_MUX25                  0x02000000U //!< Mask for X-BAR mux 25
#define XBAR_MUX26                  0x04000000U //!< Mask for X-BAR mux 26
#define XBAR_MUX27                  0x08000000U //!< Mask for X-BAR mux 27
#define XBAR_MUX28                  0x10000000U //!< Mask for X-BAR mux 28
#define XBAR_MUX29                  0x20000000U //!< Mask for X-BAR mux 29
#define XBAR_MUX30                  0x40000000U //!< Mask for X-BAR mux 30
#define XBAR_MUX31                  0x80000000U //!< Mask for X-BAR mux 31
#define XBAR_MUX32          0x0000000100000000U //!< Mask for X-BAR mux 32
#define XBAR_MUX33          0x0000000200000000U //!< Mask for X-BAR mux 33
#define XBAR_MUX34          0x0000000400000000U //!< Mask for X-BAR mux 34
#define XBAR_MUX35          0x0000000800000000U //!< Mask for X-BAR mux 35
#define XBAR_MUX36          0x0000001000000000U //!< Mask for X-BAR mux 36
#define XBAR_MUX37          0x0000002000000000U //!< Mask for X-BAR mux 37
#define XBAR_MUX38          0x0000004000000000U //!< Mask for X-BAR mux 38
#define XBAR_MUX39          0x0000008000000000U //!< Mask for X-BAR mux 39
#define XBAR_MUX40          0x0000010000000000U //!< Mask for X-BAR mux 40
#define XBAR_MUX41          0x0000020000000000U //!< Mask for X-BAR mux 41
#define XBAR_MUX42          0x0000040000000000U //!< Mask for X-BAR mux 42
#define XBAR_MUX43          0x0000080000000000U //!< Mask for X-BAR mux 43
#define XBAR_MUX44          0x0000100000000000U //!< Mask for X-BAR mux 44
#define XBAR_MUX45          0x0000200000000000U //!< Mask for X-BAR mux 45
#define XBAR_MUX46          0x0000400000000000U //!< Mask for X-BAR mux 46
#define XBAR_MUX47          0x0000800000000000U //!< Mask for X-BAR mux 47
#define XBAR_MUX48          0x0001000000000000U //!< Mask for X-BAR mux 48
#define XBAR_MUX49          0x0002000000000000U //!< Mask for X-BAR mux 49
#define XBAR_MUX50          0x0004000000000000U //!< Mask for X-BAR mux 50
#define XBAR_MUX51          0x0008000000000000U //!< Mask for X-BAR mux 51
#define XBAR_MUX52          0x0010000000000000U //!< Mask for X-BAR mux 52
#define XBAR_MUX53          0x0020000000000000U //!< Mask for X-BAR mux 53
#define XBAR_MUX54          0x0040000000000000U //!< Mask for X-BAR mux 54
#define XBAR_MUX55          0x0080000000000000U //!< Mask for X-BAR mux 55
#define XBAR_MUX56          0x0100000000000000U //!< Mask for X-BAR mux 56
#define XBAR_MUX57          0x0200000000000000U //!< Mask for X-BAR mux 57
#define XBAR_MUX58          0x0400000000000000U //!< Mask for X-BAR mux 58
#define XBAR_MUX59          0x0800000000000000U //!< Mask for X-BAR mux 59
#define XBAR_MUX60          0x1000000000000000U //!< Mask for X-BAR mux 60
#define XBAR_MUX61          0x2000000000000000U //!< Mask for X-BAR mux 61
#define XBAR_MUX62          0x4000000000000000U //!< Mask for X-BAR mux 62
#define XBAR_MUX63          0x8000000000000000U //!< Mask for X-BAR mux 63
#endif

//*****************************************************************************
//
//! The following values define the \e output parameter for
//! XBAR_setOutputMuxConfig(), XBAR_enableOutputMux(), and
//! XBAR_disableOutputMux().
//
//*****************************************************************************
typedef enum
{
    XBAR_OUTPUT1 = 0,       //!< OUTPUT1 of the Output X-BAR
    XBAR_OUTPUT2 = 4,       //!< OUTPUT2 of the Output X-BAR
    XBAR_OUTPUT3 = 8,       //!< OUTPUT3 of the Output X-BAR
    XBAR_OUTPUT4 = 12,      //!< OUTPUT4 of the Output X-BAR
    XBAR_OUTPUT5 = 16,      //!< OUTPUT5 of the Output X-BAR
    XBAR_OUTPUT6 = 20,      //!< OUTPUT6 of the Output X-BAR
    XBAR_OUTPUT7 = 24,      //!< OUTPUT7 of the Output X-BAR
    XBAR_OUTPUT8 = 28,      //!< OUTPUT8 of the Output X-BAR
} XBAR_OutputNum;

//*****************************************************************************
//
//! The following values define the \e trip parameter for
//! XBAR_setEPWMMuxConfig(), XBAR_invertEPWMSignal(), XBAR_enableEPWMMux(),
//! and XBAR_disableEPWMMux().
//
//*****************************************************************************
typedef enum
{
    XBAR_TRIP1 = 0,      //!< TRIP1 of the ePWM X-BAR
    XBAR_TRIP2 = 4,      //!< TRIP2 of the ePWM X-BAR
    XBAR_TRIP3 = 8,      //!< TRIP3 of the ePWM X-BAR
    XBAR_TRIP4 = 12,     //!< TRIP4 of the ePWM X-BAR
    XBAR_TRIP5 = 16,     //!< TRIP5 of the ePWM X-BAR
    XBAR_TRIP6 = 20,     //!< TRIP6 of the ePWM X-BAR
    XBAR_TRIP7 = 24,     //!< TRIP7 of the ePWM X-BAR
    XBAR_TRIP8 = 28,     //!< TRIP8 of the ePWM X-BAR
    XBAR_TRIP9 = 32,     //!< TRIP9 of the ePWM X-BAR
    XBAR_TRIP10 = 36,    //!< TRIP10 of the ePWM X-BAR
    XBAR_TRIP11 = 40,    //!< TRIP11 of the ePWM X-BAR
    XBAR_TRIP12 = 44,    //!< TRIP12 of the ePWM X-BAR
    XBAR_TRIP14 = 52,    //!< TRIP14 of the ePWM X-BAR
    XBAR_TRIP15 = 56     //!< TRIP15 of the ePWM X-BAR
} XBAR_TripNum;

//*****************************************************************************
//
// The following values define the trip parameter for XBAR_setCLBMuxConfig(),
// XBAR_enableCLBMux(), and XBAR_disableCLBMux().
//
//*****************************************************************************
typedef enum
{
    XBAR_AUXSIG0 = 0,
    XBAR_AUXSIG1 = 2,
    XBAR_AUXSIG2 = 4,
    XBAR_AUXSIG3 = 6,
    XBAR_AUXSIG4 = 8,
    XBAR_AUXSIG5 = 10,
    XBAR_AUXSIG6 = 12,
    XBAR_AUXSIG7 = 14
} XBAR_AuxSigNum;

//*****************************************************************************
//
//! The following values define the \e input parameter for XBAR_setInputPin().
//
//*****************************************************************************
typedef enum
{
    XBAR_INPUT1,            //!< ePWM[TZ1], ePWM[TRIP1], X-BARs, eCAPs
    XBAR_INPUT2,            //!< ePWM[TZ2], ePWM[TRIP2], X-BARs, eCAPs
    XBAR_INPUT3,            //!< ePWM[TZ3], ePWM[TRIP3], X-BARs, eCAPs
    XBAR_INPUT4,            //!< ADC wrappers, X-BARs, XINT1, eCAPs
    XBAR_INPUT5,            //!< EXTSYNCIN1, X-BARs, XINT2, eCAPs
    XBAR_INPUT6,            //!< EXTSYNCIN2, ePWM[TRIP6], X-BARs, XINT3, eCAPs
    XBAR_INPUT7,            //!< X-BARs, eCAPs
    XBAR_INPUT8,            //!< X-BARs, eCAPs
    XBAR_INPUT9,            //!< X-BARs, eCAPs
    XBAR_INPUT10,           //!< X-BARs, eCAPs
    XBAR_INPUT11,           //!< X-BARs, eCAPs
    XBAR_INPUT12,           //!< X-BARs, eCAPs
    XBAR_INPUT13,           //!< XINT4, X-BARs, eCAPs
    XBAR_INPUT14,           //!< XINT5, X-BARs, eCAPs
    XBAR_INPUT15,           //!< eCAPs
    XBAR_INPUT16            //!< eCAPs
} XBAR_InputNum;

#ifndef DOXYGEN_PDF_IGNORE
//*****************************************************************************
//
//! The following values define the \e muxConfig parameter for
//! XBAR_setOutputMuxConfig().
//
//*****************************************************************************
typedef enum
{
    //
    //OUTPUTXBAR
    //
    XBAR_OUT_MUX00_CMPSS1_CTRIPOUTH        = 0x0000,
    XBAR_OUT_MUX00_SD3FLT1_CEVT1           = 0x0001,
    XBAR_OUT_MUX00_ADCAEVT1                = 0x0002,
    XBAR_OUT_MUX00_ECAP1_OUT               = 0x0003,
    XBAR_OUT_MUX01_CMPSS1_CTRIPOUTL        = 0x0200,
    XBAR_OUT_MUX01_INPUTXBAR1              = 0x0201,
    XBAR_OUT_MUX01_CLB1_OUT4               = 0x0202,
    XBAR_OUT_MUX01_ADCCEVT1                = 0x0203,
    XBAR_OUT_MUX02_CMPSS2_CTRIPOUTH        = 0x0400,
    XBAR_OUT_MUX02_SD3FLT1_CEVT2           = 0x0401,
    XBAR_OUT_MUX02_ADCAEVT2                = 0x0402,
    XBAR_OUT_MUX02_ECAP2_OUT               = 0x0403,
    XBAR_OUT_MUX03_CMPSS2_CTRIPOUTL        = 0x0600,
    XBAR_OUT_MUX03_INPUTXBAR2              = 0x0601,
    XBAR_OUT_MUX03_CLB1_OUT5               = 0x0602,
    XBAR_OUT_MUX03_ADCCEVT2                = 0x0603,
    XBAR_OUT_MUX04_CMPSS3_CTRIPOUTH        = 0x0800,
    XBAR_OUT_MUX04_SD3FLT2_CEVT1           = 0x0801,
    XBAR_OUT_MUX04_ADCAEVT3                = 0x0802,
    XBAR_OUT_MUX04_ECAP3_OUT               = 0x0803,
    XBAR_OUT_MUX05_CMPSS3_CTRIPOUTL        = 0x0A00,
    XBAR_OUT_MUX05_INPUTXBAR3              = 0x0A01,
    XBAR_OUT_MUX05_CLB2_OUT4               = 0x0A02,
    XBAR_OUT_MUX05_ADCCEVT3                = 0x0A03,
    XBAR_OUT_MUX06_CMPSS4_CTRIPOUTH        = 0x0C00,
    XBAR_OUT_MUX06_SD3FLT2_CEVT2           = 0x0C01,
    XBAR_OUT_MUX06_ADCAEVT4                = 0x0C02,
    XBAR_OUT_MUX06_ECAP4_OUT               = 0x0C03,
    XBAR_OUT_MUX07_CMPSS4_CTRIPOUTL        = 0x0E00,
    XBAR_OUT_MUX07_INPUTXBAR4              = 0x0E01,
    XBAR_OUT_MUX07_CLB2_OUT5               = 0x0E02,
    XBAR_OUT_MUX07_ADCCEVT4                = 0x0E03,
    XBAR_OUT_MUX08_CMPSS5_CTRIPOUTH        = 0x1000,
    XBAR_OUT_MUX08_SD3FLT3_CEVT1           = 0x1001,
    XBAR_OUT_MUX08_ADCBEVT1                = 0x1002,
    XBAR_OUT_MUX08_ECAP5_OUT               = 0x1003,
    XBAR_OUT_MUX09_CMPSS5_CTRIPOUTL        = 0x1200,
    XBAR_OUT_MUX09_INPUTXBAR5              = 0x1201,
    XBAR_OUT_MUX09_CLB3_OUT4               = 0x1202,
    XBAR_OUT_MUX10_CMPSS6_CTRIPOUTH        = 0x1400,
    XBAR_OUT_MUX10_SD3FLT3_CEVT2           = 0x1401,
    XBAR_OUT_MUX10_ADCBEVT2                = 0x1402,
    XBAR_OUT_MUX10_ECAP6_OUT               = 0x1403,
    XBAR_OUT_MUX11_CMPSS6_CTRIPOUTL        = 0x1600,
    XBAR_OUT_MUX11_INPUTXBAR6              = 0x1601,
    XBAR_OUT_MUX11_CLB3_OUT5               = 0x1602,
    XBAR_OUT_MUX12_CMPSS7_CTRIPOUTH        = 0x1800,
    XBAR_OUT_MUX12_SD3FLT4_CEVT1           = 0x1801,
    XBAR_OUT_MUX12_ADCBEVT3                = 0x1802,
    XBAR_OUT_MUX12_ECAP7_OUT               = 0x1803,
    XBAR_OUT_MUX13_CMPSS7_CTRIPOUTL        = 0x1A00,
    XBAR_OUT_MUX13_ADCSOCA                 = 0x1A01,
    XBAR_OUT_MUX13_CLB4_OUT4               = 0x1A02,
    XBAR_OUT_MUX14_CMPSS8_CTRIPOUTH        = 0x1C00,
    XBAR_OUT_MUX14_SD3FLT4_CEVT2           = 0x1C01,
    XBAR_OUT_MUX14_ADCBEVT4                = 0x1C02,
    XBAR_OUT_MUX14_EXTSYNCOUT              = 0x1C03,
    XBAR_OUT_MUX15_CMPSS8_CTRIPOUTL        = 0x1E00,
    XBAR_OUT_MUX15_ADCSOCB                 = 0x1E01,
    XBAR_OUT_MUX15_CLB4_OUT5               = 0x1E02,
    XBAR_OUT_MUX16_SD1FLT1_CEVT1           = 0x2000,
    XBAR_OUT_MUX16_SD4FLT1_CEVT1           = 0x2001,
    XBAR_OUT_MUX17_SD1FLT1_CEVT2           = 0x2200,
    XBAR_OUT_MUX17_CLB5_OUT4               = 0x2202,
    XBAR_OUT_MUX18_SD1FLT2_CEVT1           = 0x2400,
    XBAR_OUT_MUX18_SD4FLT1_CEVT2           = 0x2401,
    XBAR_OUT_MUX18_ECATSYNC0               = 0x2403,
    XBAR_OUT_MUX19_SD1FLT2_CEVT2           = 0x2600,
    XBAR_OUT_MUX19_CLB5_OUT5               = 0x2602,
    XBAR_OUT_MUX19_ECATSYNC1               = 0x2603,
    XBAR_OUT_MUX20_SD1FLT3_CEVT1           = 0x2800,
    XBAR_OUT_MUX20_SD4FLT2_CEVT1           = 0x2801,
    XBAR_OUT_MUX21_SD1FLT3_CEVT2           = 0x2A00,
    XBAR_OUT_MUX21_CLB6_OUT4               = 0x2A02,
    XBAR_OUT_MUX21_FSIA_RX_TRIG2           = 0x2A03,
    XBAR_OUT_MUX22_SD1FLT4_CEVT1           = 0x2C00,
    XBAR_OUT_MUX22_SD4FLT2_CEVT2           = 0x2C01,
    XBAR_OUT_MUX22_FSIB_RX_TRIG2           = 0x2C03,
    XBAR_OUT_MUX23_SD1FLT4_CEVT2           = 0x2E00,
    XBAR_OUT_MUX23_CLB6_OUT5               = 0x2E02,
    XBAR_OUT_MUX23_FSIC_RX_TRIG2           = 0x2E03,
    XBAR_OUT_MUX24_SD2FLT1_CEVT1           = 0x3000,
    XBAR_OUT_MUX24_SD4FLT3_CEVT1           = 0x3001,
    XBAR_OUT_MUX24_FSID_RX_TRIG2           = 0x3003,
    XBAR_OUT_MUX25_SD2FLT1_CEVT2           = 0x3200,
    XBAR_OUT_MUX26_SD2FLT2_CEVT1           = 0x3400,
    XBAR_OUT_MUX26_SD4FLT3_CEVT2           = 0x3401,
    XBAR_OUT_MUX27_SD2FLT2_CEVT2           = 0x3600,
    XBAR_OUT_MUX27_ERRORSTS                = 0x3602,
    XBAR_OUT_MUX28_SD2FLT3_CEVT1           = 0x3800,
    XBAR_OUT_MUX28_SD4FLT4_CEVT1           = 0x3801,
    XBAR_OUT_MUX28_XCLKOUT                 = 0x3802,
    XBAR_OUT_MUX29_SD2FLT3_CEVT2           = 0x3A00,
    XBAR_OUT_MUX30_SD2FLT4_CEVT1           = 0x3C00,
    XBAR_OUT_MUX30_SD4FLT4_CEVT2           = 0x3C01,
    XBAR_OUT_MUX30_EPG1_OUT0               = 0x3C03,
    XBAR_OUT_MUX31_SD2FLT4_CEVT2           = 0x3E00,
    XBAR_OUT_MUX31_EPG1_OUT1               = 0x3E03,
    XBAR_OUT_MUX32_EPWM1_TRIPOUT           = 0x4000,
    XBAR_OUT_MUX32_EPWM1_DE_DEMONTRIP      = 0x4001,
    XBAR_OUT_MUX32_EPWM1_DE_ACTIVE         = 0x4002,
    XBAR_OUT_MUX33_EPWM2_TRIPOUT           = 0x4200,
    XBAR_OUT_MUX33_EPWM2_DE_DEMONTRIP      = 0x4201,
    XBAR_OUT_MUX33_EPWM2_DE_ACTIVE         = 0x4202,
    XBAR_OUT_MUX34_EPWM3_TRIPOUT           = 0x4400,
    XBAR_OUT_MUX34_EPWM3_DE_DEMONTRIP      = 0x4401,
    XBAR_OUT_MUX34_EPWM3_DE_ACTIVE         = 0x4402,
    XBAR_OUT_MUX35_EPWM4_TRIPOUT           = 0x4600,
    XBAR_OUT_MUX35_EPWM4_DE_DEMONTRIP      = 0x4601,
    XBAR_OUT_MUX35_EPWM4_DE_ACTIVE         = 0x4602,
    XBAR_OUT_MUX36_EPWM5_TRIPOUT           = 0x4800,
    XBAR_OUT_MUX36_EPWM5_DE_DEMONTRIP      = 0x4801,
    XBAR_OUT_MUX36_EPWM5_DE_ACTIVE         = 0x4802,
    XBAR_OUT_MUX37_EPWM6_TRIPOUT           = 0x4A00,
    XBAR_OUT_MUX37_EPWM6_DE_DEMONTRIP      = 0x4A01,
    XBAR_OUT_MUX37_EPWM6_DE_ACTIVE         = 0x4A02,
    XBAR_OUT_MUX38_EPWM7_TRIPOUT           = 0x4C00,
    XBAR_OUT_MUX38_EPWM7_DE_DEMONTRIP      = 0x4C01,
    XBAR_OUT_MUX38_EPWM7_DE_ACTIVE         = 0x4C02,
    XBAR_OUT_MUX39_EPWM8_TRIPOUT           = 0x4E00,
    XBAR_OUT_MUX39_EPWM8_DE_DEMONTRIP      = 0x4E01,
    XBAR_OUT_MUX39_EPWM8_DE_ACTIVE         = 0x4E02,
    XBAR_OUT_MUX40_EPWM9_TRIPOUT           = 0x5000,
    XBAR_OUT_MUX40_EPWM9_DE_DEMONTRIP      = 0x5001,
    XBAR_OUT_MUX40_EPWM9_DE_ACTIVE         = 0x5002,
    XBAR_OUT_MUX41_EPWM10_TRIPOUT          = 0x5200,
    XBAR_OUT_MUX41_EPWM10_DE_DEMONTRIP     = 0x5201,
    XBAR_OUT_MUX41_EPWM10_DE_ACTIVE        = 0x5202,
    XBAR_OUT_MUX42_EPWM11_TRIPOUT          = 0x5400,
    XBAR_OUT_MUX42_EPWM11_DE_DEMONTRIP     = 0x5401,
    XBAR_OUT_MUX42_EPWM11_DE_ACTIVE        = 0x5402,
    XBAR_OUT_MUX43_EPWM12_TRIPOUT          = 0x5600,
    XBAR_OUT_MUX43_EPWM12_DE_DEMONTRIP     = 0x5601,
    XBAR_OUT_MUX43_EPWM12_DE_ACTIVE        = 0x5602,
    XBAR_OUT_MUX44_EPWM13_TRIPOUT          = 0x5800,
    XBAR_OUT_MUX44_EPWM13_DE_DEMONTRIP     = 0x5801,
    XBAR_OUT_MUX44_EPWM13_DE_ACTIVE        = 0x5802,
    XBAR_OUT_MUX45_EPWM14_TRIPOUT          = 0x5A00,
    XBAR_OUT_MUX45_EPWM14_DE_DEMONTRIP     = 0x5A01,
    XBAR_OUT_MUX45_EPWM14_DE_ACTIVE        = 0x5A02,
    XBAR_OUT_MUX46_EPWM15_TRIPOUT          = 0x5C00,
    XBAR_OUT_MUX46_EPWM15_DE_DEMONTRIP     = 0x5C01,
    XBAR_OUT_MUX46_EPWM15_DE_ACTIVE        = 0x5C02,
    XBAR_OUT_MUX47_EPWM16_TRIPOUT          = 0x5E00,
    XBAR_OUT_MUX47_EPWM16_DE_DEMONTRIP     = 0x5E01,
    XBAR_OUT_MUX47_EPWM16_DE_ACTIVE        = 0x5E02,
    XBAR_OUT_MUX48_EPWM17_TRIPOUT          = 0x6000,
    XBAR_OUT_MUX48_EPWM17_DE_DEMONTRIP     = 0x6001,
    XBAR_OUT_MUX48_EPWM17_DE_ACTIVE        = 0x6002,
    XBAR_OUT_MUX49_EPWM18_TRIPOUT          = 0x6200,
    XBAR_OUT_MUX49_EPWM18_DE_DEMONTRIP     = 0x6201,
    XBAR_OUT_MUX49_EPWM18_DE_ACTIVE        = 0x6202,
    XBAR_OUT_MUX50_CPU1_ADCCHECK_EVT1      = 0x6403,
    XBAR_OUT_MUX51_CPU1_ADCCHECK_EVT2      = 0x6603,
    XBAR_OUT_MUX52_ADCA_EXTMUXSEL0         = 0x6802,
    XBAR_OUT_MUX52_CPU1_ADCCHECK_EVT3      = 0x6803,
    XBAR_OUT_MUX53_ADCA_EXTMUXSEL1         = 0x6A02,
    XBAR_OUT_MUX53_CPU1_ADCCHECK_EVT4      = 0x6A03,
    XBAR_OUT_MUX54_ADCA_EXTMUXSEL2         = 0x6C02,
    XBAR_OUT_MUX54_CPU2_ADCCHECK_EVT1      = 0x6C03,
    XBAR_OUT_MUX55_ADCA_EXTMUXSEL3         = 0x6E02,
    XBAR_OUT_MUX55_CPU2_ADCCHECK_EVT2      = 0x6E03,
    XBAR_OUT_MUX56_ADCB_EXTMUXSEL0         = 0x7002,
    XBAR_OUT_MUX56_CPU2_ADCCHECK_EVT3      = 0x7003,
    XBAR_OUT_MUX57_ADCB_EXTMUXSEL1         = 0x7202,
    XBAR_OUT_MUX57_CPU2_ADCCHECK_EVT4      = 0x7203,
    XBAR_OUT_MUX58_CMPSS9_CTRIPOUTH        = 0x7400,
    XBAR_OUT_MUX58_ADCB_EXTMUXSEL2         = 0x7402,
    XBAR_OUT_MUX59_CMPSS9_CTRIPOUTL        = 0x7600,
    XBAR_OUT_MUX59_ADCB_EXTMUXSEL3         = 0x7602,
    XBAR_OUT_MUX60_CMPSS10_CTRIPOUTH       = 0x7800,
    XBAR_OUT_MUX60_ADCC_EXTMUXSEL0         = 0x7802,
    XBAR_OUT_MUX61_CMPSS10_CTRIPOUTL       = 0x7A00,
    XBAR_OUT_MUX61_ADCC_EXTMUXSEL1         = 0x7A02,
    XBAR_OUT_MUX62_CMPSS11_CTRIPOUTH       = 0x7C00,
    XBAR_OUT_MUX62_ADCC_EXTMUXSEL2         = 0x7C02,
    XBAR_OUT_MUX63_CMPSS11_CTRIPOUTL       = 0x7E00,
    XBAR_OUT_MUX63_ADCC_EXTMUXSEL3         = 0x7E02,

    //
    //CLBOUTPUTXBAR
    //
    XBAR_OUT_MUX00_CLB1_OUT0               = 0x0000,
    XBAR_OUT_MUX00_CLB5_OUT0               = 0x0001,
    XBAR_OUT_MUX00_XTRIP_OUT1              = 0x0003,
    XBAR_OUT_MUX01_CLB1_OUT1               = 0x0200,
    XBAR_OUT_MUX01_CLB5_OUT1               = 0x0201,
    XBAR_OUT_MUX01_XTRIP_OUT2              = 0x0203,
    XBAR_OUT_MUX02_CLB1_OUT2               = 0x0400,
    XBAR_OUT_MUX02_CLB5_OUT2               = 0x0401,
    XBAR_OUT_MUX03_CLB1_OUT3               = 0x0600,
    XBAR_OUT_MUX03_CLB5_OUT3               = 0x0601,
    XBAR_OUT_MUX04_CLB1_OUT4               = 0x0800,
    XBAR_OUT_MUX04_CLB5_OUT4               = 0x0801,
    XBAR_OUT_MUX05_CLB1_OUT5               = 0x0A00,
    XBAR_OUT_MUX05_CLB5_OUT5               = 0x0A01,
    XBAR_OUT_MUX06_CLB1_OUT6               = 0x0C00,
    XBAR_OUT_MUX06_CLB5_OUT6               = 0x0C01,
    XBAR_OUT_MUX07_CLB1_OUT7               = 0x0E00,
    XBAR_OUT_MUX07_CLB5_OUT7               = 0x0E01,
    XBAR_OUT_MUX08_CLB2_OUT0               = 0x1000,
    XBAR_OUT_MUX08_CLB6_OUT0               = 0x1001,
    XBAR_OUT_MUX08_XTRIP_OUT3              = 0x1003,
    XBAR_OUT_MUX09_CLB2_OUT1               = 0x1200,
    XBAR_OUT_MUX09_CLB6_OUT1               = 0x1201,
    XBAR_OUT_MUX09_XTRIP_OUT4              = 0x1203,
    XBAR_OUT_MUX10_CLB2_OUT2              = 0x1400,
    XBAR_OUT_MUX10_CLB6_OUT2              = 0x1401,
    XBAR_OUT_MUX11_CLB2_OUT3              = 0x1600,
    XBAR_OUT_MUX11_CLB6_OUT3              = 0x1601,
    XBAR_OUT_MUX12_CLB2_OUT4              = 0x1800,
    XBAR_OUT_MUX12_CLB6_OUT4              = 0x1801,
    XBAR_OUT_MUX13_CLB2_OUT5              = 0x1A00,
    XBAR_OUT_MUX13_CLB6_OUT5              = 0x1A01,
    XBAR_OUT_MUX14_CLB2_OUT6              = 0x1C00,
    XBAR_OUT_MUX14_CLB6_OUT6              = 0x1C01,
    XBAR_OUT_MUX15_CLB2_OUT7              = 0x1E00,
    XBAR_OUT_MUX15_CLB6_OUT7              = 0x1E01,
    XBAR_OUT_MUX16_CLB3_OUT0              = 0x2000,
    XBAR_OUT_MUX16_XTRIP_OUT5             = 0x2003,
    XBAR_OUT_MUX17_CLB3_OUT1              = 0x2200,
    XBAR_OUT_MUX17_XTRIP_OUT6             = 0x2203,
    XBAR_OUT_MUX18_CLB3_OUT2              = 0x2400,
    XBAR_OUT_MUX19_CLB3_OUT3              = 0x2600,
    XBAR_OUT_MUX20_CLB3_OUT4              = 0x2800,
    XBAR_OUT_MUX21_CLB3_OUT5              = 0x2A00,
    XBAR_OUT_MUX22_CLB3_OUT6              = 0x2C00,
    XBAR_OUT_MUX23_CLB3_OUT7              = 0x2E00,
    XBAR_OUT_MUX24_CLB4_OUT0              = 0x3000,
    XBAR_OUT_MUX24_XTRIP_OUT7             = 0x3003,
    XBAR_OUT_MUX25_CLB4_OUT1              = 0x3200,
    XBAR_OUT_MUX25_XTRIP_OUT8             = 0x3203,
    XBAR_OUT_MUX26_CLB4_OUT2              = 0x3400,
    XBAR_OUT_MUX27_CLB4_OUT3              = 0x3600,
    XBAR_OUT_MUX28_CLB4_OUT4              = 0x3800,
    XBAR_OUT_MUX29_CLB4_OUT5              = 0x3A00,
    XBAR_OUT_MUX30_CLB4_OUT6              = 0x3C00,
    XBAR_OUT_MUX30_EPG1_OUT2              = 0x3C03,
    XBAR_OUT_MUX31_CLB4_OUT7              = 0x3E00,
    XBAR_OUT_MUX31_EPG1_OUT3              = 0x3E03,
} XBAR_OutputMuxConfig;

//*****************************************************************************
//
//! The following values define the \e muxConfig parameter for
//! XBAR_setEPWMMuxConfig().
//
//*****************************************************************************
typedef enum
{
    XBAR_EPWM_MUX00_CMPSS1_CTRIPH          = 0x0000,
    XBAR_EPWM_MUX00_SD3FLT1_CEVT1          = 0x0001,
    XBAR_EPWM_MUX00_ADCAEVT1               = 0x0002,
    XBAR_EPWM_MUX00_ECAP1_OUT              = 0x0003,
    XBAR_EPWM_MUX01_CMPSS1_CTRIPL          = 0x0200,
    XBAR_EPWM_MUX01_INPUTXBAR1_INPUT1      = 0x0201,
    XBAR_EPWM_MUX01_CLB1_OUT4              = 0x0202,
    XBAR_EPWM_MUX01_ADCCEVT1               = 0x0203,
    XBAR_EPWM_MUX02_CMPSS2_CTRIPH          = 0x0400,
    XBAR_EPWM_MUX02_SD3FLT1_CEVT2          = 0x0401,
    XBAR_EPWM_MUX02_ADCAEVT2               = 0x0402,
    XBAR_EPWM_MUX02_ECAP2_OUT              = 0x0403,
    XBAR_EPWM_MUX03_CMPSS2_CTRIPL          = 0x0600,
    XBAR_EPWM_MUX03_INPUTXBAR1_INPUT2      = 0x0601,
    XBAR_EPWM_MUX03_CLB1_OUT5              = 0x0602,
    XBAR_EPWM_MUX03_ADCCEVT2               = 0x0603,
    XBAR_EPWM_MUX04_CMPSS3_CTRIPH          = 0x0800,
    XBAR_EPWM_MUX04_SD3FLT2_CEVT1          = 0x0801,
    XBAR_EPWM_MUX04_ADCAEVT3               = 0x0802,
    XBAR_EPWM_MUX04_ECAP3_OUT              = 0x0803,
    XBAR_EPWM_MUX05_CMPSS3_CTRIPL          = 0x0A00,
    XBAR_EPWM_MUX05_INPUTXBAR1_INPUT3      = 0x0A01,
    XBAR_EPWM_MUX05_CLB2_OUT4              = 0x0A02,
    XBAR_EPWM_MUX05_ADCCEVT3               = 0x0A03,
    XBAR_EPWM_MUX06_CMPSS4_CTRIPH          = 0x0C00,
    XBAR_EPWM_MUX06_SD3FLT2_CEVT2          = 0x0C01,
    XBAR_EPWM_MUX06_ADCAEVT4               = 0x0C02,
    XBAR_EPWM_MUX06_ECAP4_OUT              = 0x0C03,
    XBAR_EPWM_MUX07_CMPSS4_CTRIPL          = 0x0E00,
    XBAR_EPWM_MUX07_INPUTXBAR1_INPUT4      = 0x0E01,
    XBAR_EPWM_MUX07_CLB2_OUT5              = 0x0E02,
    XBAR_EPWM_MUX07_ADCCEVT4               = 0x0E03,
    XBAR_EPWM_MUX08_CMPSS5_CTRIPH          = 0x1000,
    XBAR_EPWM_MUX08_SD3FLT3_CEVT1          = 0x1001,
    XBAR_EPWM_MUX08_ADCBEVT1               = 0x1002,
    XBAR_EPWM_MUX08_ECAP5_OUT              = 0x1003,
    XBAR_EPWM_MUX09_CMPSS5_CTRIPL          = 0x1200,
    XBAR_EPWM_MUX09_INPUTXBAR1_INPUT5      = 0x1201,
    XBAR_EPWM_MUX09_CLB3_OUT4              = 0x1202,
    XBAR_EPWM_MUX10_CMPSS6_CTRIPH          = 0x1400,
    XBAR_EPWM_MUX10_SD3FLT3_CEVT2          = 0x1401,
    XBAR_EPWM_MUX10_ADCBEVT2               = 0x1402,
    XBAR_EPWM_MUX10_ECAP6_OUT              = 0x1403,
    XBAR_EPWM_MUX11_CMPSS6_CTRIPL          = 0x1600,
    XBAR_EPWM_MUX11_INPUTXBAR1_INPUT6      = 0x1601,
    XBAR_EPWM_MUX11_CLB3_OUT5              = 0x1602,
    XBAR_EPWM_MUX12_CMPSS7_CTRIPH          = 0x1800,
    XBAR_EPWM_MUX12_SD3FLT4_CEVT1          = 0x1801,
    XBAR_EPWM_MUX12_ADCBEVT3               = 0x1802,
    XBAR_EPWM_MUX12_ECAP7_OUT              = 0x1803,
    XBAR_EPWM_MUX13_CMPSS7_CTRIPL          = 0x1A00,
    XBAR_EPWM_MUX13_ADCSOCA                = 0x1A01,
    XBAR_EPWM_MUX13_CLB4_OUT4              = 0x1A02,
    XBAR_EPWM_MUX14_CMPSS8_CTRIPH          = 0x1C00,
    XBAR_EPWM_MUX14_SD3FLT4_CEVT2          = 0x1C01,
    XBAR_EPWM_MUX14_ADCBEVT4               = 0x1C02,
    XBAR_EPWM_MUX14_EXTSYNCOUT             = 0x1C03,
    XBAR_EPWM_MUX15_CMPSS8_CTRIPL          = 0x1E00,
    XBAR_EPWM_MUX15_ADCSOCB                = 0x1E01,
    XBAR_EPWM_MUX15_CLB4_OUT5              = 0x1E02,
    XBAR_EPWM_MUX16_SD1FLT1_CEVT1          = 0x2000,
    XBAR_EPWM_MUX16_SD4FLT1_CEVT1          = 0x2001,
    XBAR_EPWM_MUX16_INPUTXBAR2_INPUT7      = 0x2202,
    XBAR_EPWM_MUX16_ERRORSTS               = 0x2003,
    XBAR_EPWM_MUX17_SD1FLT1_CEVT2          = 0x2200,
    XBAR_EPWM_MUX17_INPUTXBAR1_INPUT7      = 0x2201,
    XBAR_EPWM_MUX17_CLB5_OUT4              = 0x2202,
    XBAR_EPWM_MUX17_CLAHALT                = 0x2203,
    XBAR_EPWM_MUX18_SD1FLT2_CEVT1          = 0x2400,
    XBAR_EPWM_MUX18_SD4FLT1_CEVT2          = 0x2401,
    XBAR_EPWM_MUX18_INPUTXBAR2_INPUT8      = 0x2402,
    XBAR_EPWM_MUX18_ECATSYNC0              = 0x2403,
    XBAR_EPWM_MUX19_SD1FLT2_CEVT2          = 0x2600,
    XBAR_EPWM_MUX19_INPUTXBAR1_INPUT8      = 0x2601,
    XBAR_EPWM_MUX19_CLB5_OUT5              = 0x2602,
    XBAR_EPWM_MUX19_ECATSYNC1              = 0x2603,
    XBAR_EPWM_MUX20_SD1FLT3_CEVT1          = 0x2800,
    XBAR_EPWM_MUX20_SD4FLT2_CEVT1          = 0x2801,
    XBAR_EPWM_MUX20_INPUTXBAR1_INPUT9      = 0x2802,
    XBAR_EPWM_MUX20_FSIA_RX_TRIG1          = 0x2803,
    XBAR_EPWM_MUX21_SD1FLT3_CEVT2          = 0x2A00,
    XBAR_EPWM_MUX21_INPUTXBAR1_INPUT9      = 0x2A01,
    XBAR_EPWM_MUX21_CLB6_OUT4              = 0x2A02,
    XBAR_EPWM_MUX21_FSIB_RX_TRIG1          = 0x2A03,
    XBAR_EPWM_MUX22_SD1FLT4_CEVT1          = 0x2C00,
    XBAR_EPWM_MUX22_SD4FLT2_CEVT2          = 0x2C01,
    XBAR_EPWM_MUX22_INPUTXBAR2_INPUT10     = 0x2C02,
    XBAR_EPWM_MUX22_FSIC_RX_TRIG1          = 0x2C03,
    XBAR_EPWM_MUX23_SD1FLT4_CEVT2          = 0x2E00,
    XBAR_EPWM_MUX23_INPUTXBAR1_INPUT10     = 0x2E01,
    XBAR_EPWM_MUX23_CLB6_OUT5              = 0x2E02,
    XBAR_EPWM_MUX23_FSID_RX_TRIG1          = 0x2E03,
    XBAR_EPWM_MUX24_SD2FLT1_CEVT1          = 0x3000,
    XBAR_EPWM_MUX24_SD4FLT3_CEVT1          = 0x3001,
    XBAR_EPWM_MUX24_INPUTXBAR2_INPUT11     = 0x3002,
    XBAR_EPWM_MUX25_SD2FLT1_CEVT2          = 0x3200,
    XBAR_EPWM_MUX25_INPUTXBAR1_INPUT11     = 0x3201,
    XBAR_EPWM_MUX25_MCANA_FEVT0            = 0x3202,
    XBAR_EPWM_MUX26_SD2FLT2_CEVT1          = 0x3400,
    XBAR_EPWM_MUX26_SD4FLT3_CEVT2          = 0x3401,
    XBAR_EPWM_MUX26_INPUTXBAR2_INPUT12     = 0x3402,
    XBAR_EPWM_MUX26_MCANB_FEVT0            = 0x3403,
    XBAR_EPWM_MUX27_SD2FLT2_CEVT2          = 0x3600,
    XBAR_EPWM_MUX27_INPUTXBAR1_INPUT12     = 0x3601,
    XBAR_EPWM_MUX27_MCANA_FEVT1            = 0x3602,
    XBAR_EPWM_MUX28_SD2FLT3_CEVT1          = 0x3800,
    XBAR_EPWM_MUX28_SD4FLT4_CEVT1          = 0x3801,
    XBAR_EPWM_MUX28_INPUTXBAR2_INPUT13     = 0x3802,
    XBAR_EPWM_MUX28_MCANB_FEVT1            = 0x3803,
    XBAR_EPWM_MUX29_SD2FLT3_CEVT2          = 0x3A00,
    XBAR_EPWM_MUX29_INPUTXBAR1_INPUT13     = 0x3A01,
    XBAR_EPWM_MUX29_MCANA_FEVT2            = 0x3A02,
    XBAR_EPWM_MUX30_SD2FLT4_CEVT1          = 0x3C00,
    XBAR_EPWM_MUX30_SD4FLT4_CEVT2          = 0x3C01,
    XBAR_EPWM_MUX30_INPUTXBAR2_INPUT14     = 0x3C02,
    XBAR_EPWM_MUX30_MCANB_FEVT2            = 0x3C03,
    XBAR_EPWM_MUX31_SD2FLT4_CEVT2          = 0x3E00,
    XBAR_EPWM_MUX31_INPUTXBAR1_INPUT14     = 0x3E01,
    XBAR_EPWM_MUX31_ERRORSTS               = 0x3E02,
    XBAR_EPWM_MUX32_EPWM1_TRIPOUT          = 0x4000,
    XBAR_EPWM_MUX32_EPWM1_DE_DEMONTRIP     = 0x4001,
    XBAR_EPWM_MUX32_EPWM1_DE_ACTIVE        = 0x4002,
    XBAR_EPWM_MUX32_ECAP1_TRIPOUT          = 0x4003,
    XBAR_EPWM_MUX33_EPWM2_TRIPOUT          = 0x4200,
    XBAR_EPWM_MUX33_EPWM2_DE_DEMONTRIP     = 0x4201,
    XBAR_EPWM_MUX33_EPWM2_DE_ACTIVE        = 0x4202,
    XBAR_EPWM_MUX33_ECAP2_TRIPOUT          = 0x4203,
    XBAR_EPWM_MUX34_EPWM3_TRIPOUT          = 0x4400,
    XBAR_EPWM_MUX34_EPWM3_DE_DEMONTRIP     = 0x4401,
    XBAR_EPWM_MUX34_EPWM3_DE_ACTIVE        = 0x4402,
    XBAR_EPWM_MUX34_ECAP3_TRIPOUT          = 0x4403,
    XBAR_EPWM_MUX35_EPWM4_TRIPOUT          = 0x4600,
    XBAR_EPWM_MUX35_EPWM4_DE_DEMONTRIP     = 0x4601,
    XBAR_EPWM_MUX35_EPWM4_DE_ACTIVE        = 0x4602,
    XBAR_EPWM_MUX35_ECAP4_TRIPOUT          = 0x4603,
    XBAR_EPWM_MUX36_EPWM5_TRIPOUT          = 0x4800,
    XBAR_EPWM_MUX36_EPWM5_DE_DEMONTRIP     = 0x4801,
    XBAR_EPWM_MUX36_EPWM5_DE_ACTIVE        = 0x4802,
    XBAR_EPWM_MUX36_ECAP5_TRIPOUT          = 0x4803,
    XBAR_EPWM_MUX37_EPWM6_TRIPOUT          = 0x4A00,
    XBAR_EPWM_MUX37_EPWM6_DE_DEMONTRIP     = 0x4A01,
    XBAR_EPWM_MUX37_EPWM6_DE_ACTIVE        = 0x4A02,
    XBAR_EPWM_MUX37_ECAP6_TRIPOUT          = 0x4A03,
    XBAR_EPWM_MUX38_EPWM7_TRIPOUT          = 0x4C00,
    XBAR_EPWM_MUX38_EPWM7_DE_DEMONTRIP     = 0x4C01,
    XBAR_EPWM_MUX38_EPWM7_DE_ACTIVE        = 0x4C02,
    XBAR_EPWM_MUX38_ECAP7_TRIPOUT          = 0x4C03,
    XBAR_EPWM_MUX39_EPWM8_TRIPOUT          = 0x4E00,
    XBAR_EPWM_MUX39_EPWM8_DE_DEMONTRIP     = 0x4E01,
    XBAR_EPWM_MUX39_EPWM8_DE_ACTIVE        = 0x4E02,
    XBAR_EPWM_MUX40_EPWM9_TRIPOUT          = 0x5000,
    XBAR_EPWM_MUX40_EPWM9_DE_DEMONTRIP     = 0x5001,
    XBAR_EPWM_MUX40_EPWM9_DE_ACTIVE        = 0x5002,
    XBAR_EPWM_MUX41_EPWM10_TRIPOUT         = 0x5200,
    XBAR_EPWM_MUX41_EPWM10_DE_DEMONTRIP    = 0x5201,
    XBAR_EPWM_MUX41_EPWM10_DE_ACTIVE       = 0x5202,
    XBAR_EPWM_MUX42_EPWM11_TRIPOUT         = 0x5400,
    XBAR_EPWM_MUX42_EPWM11_DE_DEMONTRIP    = 0x5401,
    XBAR_EPWM_MUX42_EPWM11_DE_ACTIVE       = 0x5402,
    XBAR_EPWM_MUX43_EPWM12_TRIPOUT         = 0x5600,
    XBAR_EPWM_MUX43_EPWM12_DE_DEMONTRIP    = 0x5601,
    XBAR_EPWM_MUX43_EPWM12_DE_ACTIVE       = 0x5602,
    XBAR_EPWM_MUX44_EPWM13_TRIPOUT         = 0x5800,
    XBAR_EPWM_MUX44_EPWM13_DE_DEMONTRIP    = 0x5801,
    XBAR_EPWM_MUX44_EPWM13_DE_ACTIVE       = 0x5802,
    XBAR_EPWM_MUX45_EPWM14_TRIPOUT         = 0x5A00,
    XBAR_EPWM_MUX45_EPWM14_DE_DEMONTRIP    = 0x5A01,
    XBAR_EPWM_MUX45_EPWM14_DE_ACTIVE       = 0x5A02,
    XBAR_EPWM_MUX46_EPWM15_TRIPOUT         = 0x5C00,
    XBAR_EPWM_MUX46_EPWM15_DE_DEMONTRIP    = 0x5C01,
    XBAR_EPWM_MUX46_EPWM15_DE_ACTIVE       = 0x5C02,
    XBAR_EPWM_MUX47_EPWM16_TRIPOUT         = 0x5E00,
    XBAR_EPWM_MUX47_EPWM16_DE_DEMONTRIP    = 0x5E01,
    XBAR_EPWM_MUX47_EPWM16_DE_ACTIVE       = 0x5E02,
    XBAR_EPWM_MUX48_EPWM17_TRIPOUT         = 0x6000,
    XBAR_EPWM_MUX48_EPWM17_DE_DEMONTRIP    = 0x6001,
    XBAR_EPWM_MUX48_EPWM17_DE_ACTIVE       = 0x6002,
    XBAR_EPWM_MUX48_PIEERR                 = 0x6003,
    XBAR_EPWM_MUX49_EPWM18_TRIPOUT         = 0x6200,
    XBAR_EPWM_MUX49_EPWM18_DE_DEMONTRIP    = 0x6201,
    XBAR_EPWM_MUX49_EPWM18_DE_ACTIVE       = 0x6202,
    XBAR_EPWM_MUX49_ECCDBLERR              = 0x6203,
    XBAR_EPWM_MUX50_CPU1_ADCCHECK_EVT1     = 0x6403,
    XBAR_EPWM_MUX51_CPU1_ADCCHECK_EVT2     = 0x6603,
    XBAR_EPWM_MUX52_CPU1_ADCCHECK_EVT3     = 0x6803,
    XBAR_EPWM_MUX53_CPU1_ADCCHECK_EVT4     = 0x6A03,
    XBAR_EPWM_MUX54_CPU2_ADCCHECK_EVT1     = 0x6C03,
    XBAR_EPWM_MUX55_CPU2_ADCCHECK_EVT2     = 0x6E03,
    XBAR_EPWM_MUX56_CPU2_ADCCHECK_EVT3     = 0x7003,
    XBAR_EPWM_MUX57_CPU2_ADCCHECK_EVT4     = 0x7203,
    XBAR_EPWM_MUX58_CMPSS9_CTRIPH          = 0x7400,
    XBAR_EPWM_MUX59_CMPSS9_CTRIPL          = 0x7600,
    XBAR_EPWM_MUX60_CMPSS10_CTRIPH         = 0x7800,
    XBAR_EPWM_MUX61_CMPSS10_CTRIPL         = 0x7A00,
    XBAR_EPWM_MUX62_CMPSS11_CTRIPH         = 0x7C00,
    XBAR_EPWM_MUX63_CMPSS11_CTRIPL         = 0x7E00,
} XBAR_EPWMMuxConfig;

//*****************************************************************************
//
// The following values define the muxConfig parameter for
// XBAR_setCLBMuxConfig().
//
//*****************************************************************************
typedef enum
{
    XBAR_CLB_MUX00_CMPSS1_CTRIPH           = 0x0000,
    XBAR_CLB_MUX00_SD3FLT1_COMPH           = 0x0001,
    XBAR_CLB_MUX00_ADCAEVT1                = 0x0002,
    XBAR_CLB_MUX00_ECAP1_OUT               = 0x0003,
    XBAR_CLB_MUX01_CMPSS1_CTRIPL           = 0x0200,
    XBAR_CLB_MUX01_INPUTXBAR1_INPUT1       = 0x0201,
    XBAR_CLB_MUX01_CLB1_OUT4               = 0x0202,
    XBAR_CLB_MUX01_ADCCEVT1                = 0x0203,
    XBAR_CLB_MUX02_CMPSS2_CTRIPH           = 0x0400,
    XBAR_CLB_MUX02_SD3FLT1_COMPL           = 0x0401,
    XBAR_CLB_MUX02_ADCAEVT2                = 0x0402,
    XBAR_CLB_MUX02_ECAP2_OUT               = 0x0403,
    XBAR_CLB_MUX03_CMPSS2_CTRIPL           = 0x0600,
    XBAR_CLB_MUX03_INPUTXBAR1_INPUT2       = 0x0601,
    XBAR_CLB_MUX03_CLB1_OUT5               = 0x0602,
    XBAR_CLB_MUX03_ADCCEVT2                = 0x0603,
    XBAR_CLB_MUX04_CMPSS3_CTRIPH           = 0x0800,
    XBAR_CLB_MUX04_SD3FLT2_COMPH           = 0x0801,
    XBAR_CLB_MUX04_ADCAEVT3                = 0x0802,
    XBAR_CLB_MUX04_ECAP3_OUT               = 0x0803,
    XBAR_CLB_MUX05_CMPSS3_CTRIPL           = 0x0A00,
    XBAR_CLB_MUX05_INPUTXBAR1_INPUT3       = 0x0A01,
    XBAR_CLB_MUX05_CLB2_OUT4               = 0x0A02,
    XBAR_CLB_MUX05_ADCCEVT3                = 0x0A03,
    XBAR_CLB_MUX06_CMPSS4_CTRIPH           = 0x0C00,
    XBAR_CLB_MUX06_SD3FLT2_COMPL           = 0x0C01,
    XBAR_CLB_MUX06_ADCAEVT4                = 0x0C02,
    XBAR_CLB_MUX06_ECAP4_OUT               = 0x0C03,
    XBAR_CLB_MUX07_CMPSS4_CTRIPL           = 0x0E00,
    XBAR_CLB_MUX07_INPUTXBAR1_INPUT4       = 0x0E01,
    XBAR_CLB_MUX07_CLB2_OUT5               = 0x0E02,
    XBAR_CLB_MUX07_ADCCEVT4                = 0x0E03,
    XBAR_CLB_MUX08_CMPSS5_CTRIPH           = 0x1000,
    XBAR_CLB_MUX08_SD3FLT3_COMPH           = 0x1001,
    XBAR_CLB_MUX08_ADCBEVT1                = 0x1002,
    XBAR_CLB_MUX08_ECAP5_OUT               = 0x1003,
    XBAR_CLB_MUX09_CMPSS5_CTRIPL           = 0x1200,
    XBAR_CLB_MUX09_INPUTXBAR1_INPUT5       = 0x1201,
    XBAR_CLB_MUX09_CLB3_OUT4               = 0x1202,
    XBAR_CLB_MUX10_CMPSS6_CTRIPH           = 0x1400,
    XBAR_CLB_MUX10_SD3FLT3_COMPL           = 0x1401,
    XBAR_CLB_MUX10_ADCBEVT2                = 0x1402,
    XBAR_CLB_MUX10_ECAP6_OUT               = 0x1403,
    XBAR_CLB_MUX11_CMPSS6_CTRIPL           = 0x1600,
    XBAR_CLB_MUX11_INPUTXBAR1_INPUT6       = 0x1601,
    XBAR_CLB_MUX11_CLB3_OUT5               = 0x1602,
    XBAR_CLB_MUX12_CMPSS7_CTRIPH           = 0x1800,
    XBAR_CLB_MUX12_SD3FLT4_COMPH           = 0x1801,
    XBAR_CLB_MUX12_ADCBEVT3                = 0x1802,
    XBAR_CLB_MUX12_ECAP7_OUT               = 0x1803,
    XBAR_CLB_MUX13_CMPSS7_CTRIPL           = 0x1A00,
    XBAR_CLB_MUX13_ADCSOCA                 = 0x1A01,
    XBAR_CLB_MUX13_CLB4_OUT4               = 0x1A02,
    XBAR_CLB_MUX13_MCANB_FEVT1             = 0x1A03,
    XBAR_CLB_MUX14_CMPSS8_CTRIPH           = 0x1C00,
    XBAR_CLB_MUX14_SD3FLT4_COMPL           = 0x1C01,
    XBAR_CLB_MUX14_ADCBEVT4                = 0x1C02,
    XBAR_CLB_MUX14_EXTSYNCOUT              = 0x1C03,
    XBAR_CLB_MUX15_CMPSS8_CTRIPL           = 0x1E00,
    XBAR_CLB_MUX15_ADCSOCB                 = 0x1E01,
    XBAR_CLB_MUX15_CLB4_OUT5               = 0x1E02,
    XBAR_CLB_MUX15_MCANB_FEVT0             = 0x1E03,
    XBAR_CLB_MUX16_SD1FLT1_COMPH           = 0x2000,
    XBAR_CLB_MUX16_SD4FLT1_COMPH           = 0x2001,
    XBAR_CLB_MUX16_FSIA_RX_TRIG2           = 0x2002,
    XBAR_CLB_MUX16_FSIA_RX_TRIG3           = 0x2003,
    XBAR_CLB_MUX17_SD1FLT1_COMPL           = 0x2200,
    XBAR_CLB_MUX17_INPUTXBAR1_INPUT7       = 0x2201,
    XBAR_CLB_MUX17_CLB5_OUT4               = 0x2202,
    XBAR_CLB_MUX17_CLAHALT                 = 0x2203,
    XBAR_CLB_MUX18_SD1FLT2_COMPH           = 0x2400,
    XBAR_CLB_MUX18_SD4FLT1_COMPL           = 0x2401,
    XBAR_CLB_MUX18_FSIB_RX_TRIG2           = 0x2402,
    XBAR_CLB_MUX18_FSIB_RX_TRIG3           = 0x2403,
    XBAR_CLB_MUX19_SD1FLT2_COMPL           = 0x2600,
    XBAR_CLB_MUX19_INPUTXBAR1_INPUT8       = 0x2601,
    XBAR_CLB_MUX19_CLB5_OUT5               = 0x2602,
    XBAR_CLB_MUX19_ERRORSTS                = 0x2603,
    XBAR_CLB_MUX20_SD1FLT3_COMPH           = 0x2800,
    XBAR_CLB_MUX20_SD4FLT2_COMPH           = 0x2801,
    XBAR_CLB_MUX20_FSIC_RX_TRIG2           = 0x2802,
    XBAR_CLB_MUX20_FSIC_RX_TRIG3           = 0x2803,
    XBAR_CLB_MUX21_SD1FLT3_COMPL           = 0x2A00,
    XBAR_CLB_MUX21_INPUTXBAR1_INPUT9       = 0x2A01,
    XBAR_CLB_MUX21_CLB6_OUT4               = 0x2A02,
    XBAR_CLB_MUX22_SD1FLT4_COMPH           = 0x2C00,
    XBAR_CLB_MUX22_SD4FLT2_COMPL           = 0x2C01,
    XBAR_CLB_MUX22_FSID_RX_TRIG2           = 0x2C02,
    XBAR_CLB_MUX22_FSIC_RX_TRIG3           = 0x2C03,
    XBAR_CLB_MUX23_SD1FLT4_COMPL           = 0x2E00,
    XBAR_CLB_MUX23_INPUTXBAR1_INPUT10      = 0x2E01,
    XBAR_CLB_MUX23_CLB6_OUT5               = 0x2E02,
    XBAR_CLB_MUX23_CPU2_ERADEVT9           = 0x2E03,
    XBAR_CLB_MUX24_SD2FLT1_COMPH           = 0x3000,
    XBAR_CLB_MUX24_SD4FLT3_COMPH           = 0x3001,
    XBAR_CLB_MUX24_CPU1_ERADEVT8           = 0x3002,
    XBAR_CLB_MUX24_CMPSS9_CTRIPH           = 0x3003,
    XBAR_CLB_MUX25_SD2FLT1_COMPL           = 0x3200,
    XBAR_CLB_MUX25_INPUTXBAR1_INPUT11      = 0x3201,
    XBAR_CLB_MUX25_MCANA_FEVT0             = 0x3202,
    XBAR_CLB_MUX25_CPU2_ERADEVT10          = 0x3203,
    XBAR_CLB_MUX26_SD2FLT2_COMPH           = 0x3400,
    XBAR_CLB_MUX26_SD4FLT3_COMPL           = 0x3401,
    XBAR_CLB_MUX26_CPU1_ERADEVT9           = 0x3402,
    XBAR_CLB_MUX26_CMPSS9_CTRIPL           = 0x3403,
    XBAR_CLB_MUX27_SD2FLT2_COMPL           = 0x3600,
    XBAR_CLB_MUX27_INPUTXBAR1_INPUT12      = 0x3601,
    XBAR_CLB_MUX27_MCANA_FEVT1             = 0x3602,
    XBAR_CLB_MUX27_CPU2_ERADEVT11          = 0x3603,
    XBAR_CLB_MUX28_SD2FLT3_COMPH           = 0x3800,
    XBAR_CLB_MUX28_SD4FLT4_COMPH           = 0x3801,
    XBAR_CLB_MUX28_CPU1_ERADEVT10          = 0x3802,
    XBAR_CLB_MUX28_CMPSS10_CTRIPH          = 0x3803,
    XBAR_CLB_MUX29_SD2FLT3_COMPL           = 0x3A00,
    XBAR_CLB_MUX29_INPUTXBAR1_INPUT13      = 0x3A01,
    XBAR_CLB_MUX29_MCANA_FEVT2             = 0x3A02,
    XBAR_CLB_MUX29_CMPSS10_CTRIPL          = 0x3A03,
    XBAR_CLB_MUX30_SD2FLT4_COMPH           = 0x3C00,
    XBAR_CLB_MUX30_SD4FLT4_COMPL           = 0x3C01,
    XBAR_CLB_MUX30_CPU1_ERADEVT11          = 0x3C02,
    XBAR_CLB_MUX30_CMPSS11_CTRIPH          = 0x3C03,
    XBAR_CLB_MUX31_SD2FLT4_COMPL           = 0x3E00,
    XBAR_CLB_MUX31_INPUTXBAR1_INPUT14      = 0x3E01,
    XBAR_CLB_MUX31_MCANB_FEVT2             = 0x3E02,
    XBAR_CLB_MUX31_CMPSS11_CTRIPL          = 0x3E03,
} XBAR_CLBMuxConfig;

//*****************************************************************************
//
//! The following values define the \e signal parameter for
//! XBAR_setInputSignal().
//
//*****************************************************************************
typedef enum
{
    //
    //Inputs for MINDB XBAR
    //
    XBAR_MINDB_EPWM1A_DB_NO_HR             = 0,
	XBAR_MINDB_EPWM1B_DB_NO_HR             = 1,
	XBAR_MINDB_EPWM2A_DB_NO_HR             = 2,
	XBAR_MINDB_EPWM2B_DB_NO_HR             = 3,
	XBAR_MINDB_EPWM3A_DB_NO_HR             = 4,
	XBAR_MINDB_EPWM3B_DB_NO_HR             = 5,
	XBAR_MINDB_EPWM4A_DB_NO_HR             = 6,
	XBAR_MINDB_EPWM4B_DB_NO_HR             = 7,
	XBAR_MINDB_EPWM5A_DB_NO_HR             = 8,
	XBAR_MINDB_EPWM5B_DB_NO_HR             = 9,
	XBAR_MINDB_EPWM6A_DB_NO_HR             = 10,
	XBAR_MINDB_EPWM6B_DB_NO_HR             = 11,
	XBAR_MINDB_EPWM7A_DB_NO_HR             = 12,
	XBAR_MINDB_EPWM7B_DB_NO_HR             = 13,
	XBAR_MINDB_EPWM8A_DB_NO_HR             = 14,
	XBAR_MINDB_EPWM8B_DB_NO_HR             = 15,
	XBAR_MINDB_EPWM9A_DB_NO_HR             = 16,
	XBAR_MINDB_EPWM9B_DB_NO_HR             = 17,
	XBAR_MINDB_EPWM10A_DB_NO_HR            = 18,
	XBAR_MINDB_EPWM10B_DB_NO_HR            = 19,
	XBAR_MINDB_EPWM11A_DB_NO_HR            = 20,
	XBAR_MINDB_EPWM11B_DB_NO_HR            = 21,
	XBAR_MINDB_EPWM12A_DB_NO_HR            = 22,
	XBAR_MINDB_EPWM12B_DB_NO_HR            = 23,
	XBAR_MINDB_EPWM13A_DB_NO_HR            = 24,
	XBAR_MINDB_EPWM13B_DB_NO_HR            = 25,
	XBAR_MINDB_EPWM14A_DB_NO_HR            = 26,
	XBAR_MINDB_EPWM14B_DB_NO_HR            = 27,
	XBAR_MINDB_EPWM15A_DB_NO_HR            = 28,
	XBAR_MINDB_EPWM15B_DB_NO_HR            = 29,
	XBAR_MINDB_EPWM16A_DB_NO_HR            = 30,
	XBAR_MINDB_EPWM16B_DB_NO_HR            = 31,
	XBAR_MINDB_EPWM17A_DB_NO_HR            = 32,
	XBAR_MINDB_EPWM17B_DB_NO_HR            = 33,
	XBAR_MINDB_EPWM18A_DB_NO_HR            = 34,
	XBAR_MINDB_EPWM18B_DB_NO_HR            = 35,
	XBAR_MINDB_CLB1_OUT4                   = 36,
	XBAR_MINDB_CLB1_OUT5                   = 37,
	XBAR_MINDB_CLB2_OUT4                   = 38,
	XBAR_MINDB_CLB2_OUT5                   = 39,
	XBAR_MINDB_CLB3_OUT4                   = 40,
	XBAR_MINDB_CLB3_OUT5                   = 41,
	XBAR_MINDB_CLB4_OUT4                   = 42,
	XBAR_MINDB_CLB4_OUT5                   = 43,
	XBAR_MINDB_CLB5_OUT4                   = 44,
	XBAR_MINDB_CLB5_OUT5                   = 45,
	XBAR_MINDB_CLB6_OUT4                   = 46,
	XBAR_MINDB_CLB6_OUT5                   = 47,

    //
    //Inputs for ICL XBAR
    //
    XBAR_ICL_EPWM1A_MINDB                  = 0,
	XBAR_ICL_EPWM1B_MINDB                  = 1,
	XBAR_ICL_EPWM2A_MINDB                  = 2,
	XBAR_ICL_EPWM2B_MINDB                  = 3,
	XBAR_ICL_EPWM3A_MINDB                  = 4,
	XBAR_ICL_EPWM3B_MINDB                  = 5,
	XBAR_ICL_EPWM4A_MINDB                  = 6,
	XBAR_ICL_EPWM4B_MINDB                  = 7,
	XBAR_ICL_EPWM5A_MINDB                  = 8,
	XBAR_ICL_EPWM5B_MINDB                  = 9,
	XBAR_ICL_EPWM6A_MINDB                  = 10,
	XBAR_ICL_EPWM6B_MINDB                  = 11,
	XBAR_ICL_EPWM7A_MINDB                  = 12,
	XBAR_ICL_EPWM7B_MINDB                  = 13,
	XBAR_ICL_EPWM8A_MINDB                  = 14,
	XBAR_ICL_EPWM8B_MINDB                  = 15,
	XBAR_ICL_EPWM9A_MINDB                  = 16,
	XBAR_ICL_EPWM9B_MINDB                  = 17,
	XBAR_ICL_EPWM10A_MINDB                 = 18,
	XBAR_ICL_EPWM10B_MINDB                 = 19,
	XBAR_ICL_EPWM11A_MINDB                 = 20,
	XBAR_ICL_EPWM11B_MINDB                 = 21,
	XBAR_ICL_EPWM12A_MINDB                 = 22,
	XBAR_ICL_EPWM12B_MINDB                 = 23,
	XBAR_ICL_EPWM13A_MINDB                 = 24,
	XBAR_ICL_EPWM13B_MINDB                 = 25,
	XBAR_ICL_EPWM14A_MINDB                 = 26,
	XBAR_ICL_EPWM14B_MINDB                 = 27,
	XBAR_ICL_EPWM15A_MINDB                 = 28,
	XBAR_ICL_EPWM15B_MINDB                 = 29,
	XBAR_ICL_EPWM16A_MINDB                 = 30,
	XBAR_ICL_EPWM16B_MINDB                 = 31,
	XBAR_ICL_EPWM17A_MINDB                 = 32,
	XBAR_ICL_EPWM17B_MINDB                 = 33,
	XBAR_ICL_EPWM18A_MINDB                 = 34,
	XBAR_ICL_EPWM18B_MINDB                 = 35,
	XBAR_ICL_CLB1_OUT4                     = 36,
	XBAR_ICL_CLB1_OUT5                     = 37,
	XBAR_ICL_CLB2_OUT4                     = 38,
	XBAR_ICL_CLB2_OUT5                     = 39,
	XBAR_ICL_CLB3_OUT4                     = 40,
	XBAR_ICL_CLB3_OUT5                     = 41,
	XBAR_ICL_CLB4_OUT4                     = 42,
	XBAR_ICL_CLB4_OUT5                     = 43,
	XBAR_ICL_CLB5_OUT4                     = 44,
	XBAR_ICL_CLB5_OUT5                     = 45,
	XBAR_ICL_CLB6_OUT4                     = 46,
	XBAR_ICL_CLB6_OUT5                     = 47, 
} XBAR_InputSignal;

//*****************************************************************************
//
//! The following values define the \e inputFlag parameter for
//! XBAR_getInputFlagStatus() and XBAR_clearInputFlag().
//
//*****************************************************************************
typedef enum
{
    //
    // XBARFLG1
    //
    XBAR_INPUT_FLG_CMPSS1_CTRIPL    = 0x0000,
    XBAR_INPUT_FLG_CMPSS1_CTRIPH    = 0x0001,
    XBAR_INPUT_FLG_CMPSS2_CTRIPL    = 0x0002,
    XBAR_INPUT_FLG_CMPSS2_CTRIPH    = 0x0003,
    XBAR_INPUT_FLG_CMPSS3_CTRIPL    = 0x0004,
    XBAR_INPUT_FLG_CMPSS3_CTRIPH    = 0x0005,
    XBAR_INPUT_FLG_CMPSS4_CTRIPL    = 0x0006,
    XBAR_INPUT_FLG_CMPSS4_CTRIPH    = 0x0007,
    XBAR_INPUT_FLG_CMPSS5_CTRIPL    = 0x0008,
    XBAR_INPUT_FLG_CMPSS5_CTRIPH    = 0x0009,
    XBAR_INPUT_FLG_CMPSS6_CTRIPL    = 0x000A,
    XBAR_INPUT_FLG_CMPSS6_CTRIPH    = 0x000B,
    XBAR_INPUT_FLG_CMPSS7_CTRIPL    = 0x000C,
    XBAR_INPUT_FLG_CMPSS7_CTRIPH    = 0x000D,
    XBAR_INPUT_FLG_CMPSS8_CTRIPL    = 0x000E,
    XBAR_INPUT_FLG_CMPSS8_CTRIPH    = 0x000F,
    XBAR_INPUT_FLG_CMPSS1_CTRIPOUTL = 0x0010,
    XBAR_INPUT_FLG_CMPSS1_CTRIPOUTH = 0x0011,
    XBAR_INPUT_FLG_CMPSS2_CTRIPOUTL = 0x0012,
    XBAR_INPUT_FLG_CMPSS2_CTRIPOUTH = 0x0013,
    XBAR_INPUT_FLG_CMPSS3_CTRIPOUTL = 0x0014,
    XBAR_INPUT_FLG_CMPSS3_CTRIPOUTH = 0x0015,
    XBAR_INPUT_FLG_CMPSS4_CTRIPOUTL = 0x0016,
    XBAR_INPUT_FLG_CMPSS4_CTRIPOUTH = 0x0017,
    XBAR_INPUT_FLG_CMPSS5_CTRIPOUTL = 0x0018,
    XBAR_INPUT_FLG_CMPSS5_CTRIPOUTH = 0x0019,
    XBAR_INPUT_FLG_CMPSS6_CTRIPOUTL = 0x001A,
    XBAR_INPUT_FLG_CMPSS6_CTRIPOUTH = 0x001B,
    XBAR_INPUT_FLG_CMPSS7_CTRIPOUTL = 0x001C,
    XBAR_INPUT_FLG_CMPSS7_CTRIPOUTH = 0x001D,
    XBAR_INPUT_FLG_CMPSS8_CTRIPOUTL = 0x001E,
    XBAR_INPUT_FLG_CMPSS8_CTRIPOUTH = 0x001F,
    //
    // XBARFLG2
    //
    XBAR_INPUT_FLG_INPUT1           = 0x0100,
    XBAR_INPUT_FLG_INPUT2           = 0x0101,
    XBAR_INPUT_FLG_INPUT3           = 0x0102,
    XBAR_INPUT_FLG_INPUT4           = 0x0103,
    XBAR_INPUT_FLG_INPUT5           = 0x0104,
    XBAR_INPUT_FLG_INPUT6           = 0x0105,
    XBAR_INPUT_FLG_ADCSOCA          = 0x0106,
    XBAR_INPUT_FLG_ADCSOCB          = 0x0107,
    XBAR_INPUT_FLG_INPUT7           = 0x0108,
    XBAR_INPUT_FLG_INPUT8           = 0x0109,
    XBAR_INPUT_FLG_INPUT9           = 0x010A,
    XBAR_INPUT_FLG_INPUT10          = 0x010B,
    XBAR_INPUT_FLG_INPUT11          = 0x010C,
    XBAR_INPUT_FLG_INPUT12          = 0x010D,
    XBAR_INPUT_FLG_INPUT13          = 0x010E,
    XBAR_INPUT_FLG_INPUT14          = 0x010F,
    XBAR_INPUT_FLG_ECAP1_OUT        = 0x0110,
    XBAR_INPUT_FLG_ECAP2_OUT        = 0x0111,
    XBAR_INPUT_FLG_ECAP3_OUT        = 0x0112,
    XBAR_INPUT_FLG_ECAP4_OUT        = 0x0113,
    XBAR_INPUT_FLG_ECAP5_OUT        = 0x0114,
    XBAR_INPUT_FLG_ECAP6_OUT        = 0x0115,
    XBAR_INPUT_FLG_EXTSYNCOUT       = 0x0116,
    XBAR_INPUT_FLG_ADCAEVT1         = 0x0117,
    XBAR_INPUT_FLG_ADCAEVT2         = 0x0118,
    XBAR_INPUT_FLG_ADCAEVT3         = 0x0119,
    XBAR_INPUT_FLG_ADCAEVT4         = 0x011A,
    XBAR_INPUT_FLG_ADCBEVT1         = 0x011B,
    XBAR_INPUT_FLG_ADCBEVT2         = 0x011C,
    XBAR_INPUT_FLG_ADCBEVT3         = 0x011D,
    XBAR_INPUT_FLG_ADCBEVT4         = 0x011E,
    XBAR_INPUT_FLG_ADCCEVT1         = 0x011F,
    //
    // XBARFLG3
    //
    XBAR_INPUT_FLG_ADCCEVT2         = 0x0200,
    XBAR_INPUT_FLG_ADCCEVT3         = 0x0201,
    XBAR_INPUT_FLG_ADCCEVT4         = 0x0202,
    XBAR_INPUT_FLG_SD1FLT1_COMPL    = 0x0207,
    XBAR_INPUT_FLG_SD1FLT1_COMPH    = 0x0208,
    XBAR_INPUT_FLG_SD1FLT2_COMPL    = 0x0209,
    XBAR_INPUT_FLG_SD1FLT2_COMPH    = 0x020A,
    XBAR_INPUT_FLG_SD1FLT3_COMPL    = 0x020B,
    XBAR_INPUT_FLG_SD1FLT3_COMPH    = 0x020C,
    XBAR_INPUT_FLG_SD1FLT4_COMPL    = 0x020D,
    XBAR_INPUT_FLG_SD1FLT4_COMPH    = 0x020E,
    XBAR_INPUT_FLG_SD2FLT1_COMPL    = 0x020F,
    XBAR_INPUT_FLG_SD2FLT1_COMPH    = 0x0210,
    XBAR_INPUT_FLG_SD2FLT2_COMPL    = 0x0211,
    XBAR_INPUT_FLG_SD2FLT2_COMPH    = 0x0212,
    XBAR_INPUT_FLG_SD2FLT3_COMPL    = 0x0213,
    XBAR_INPUT_FLG_SD2FLT3_COMPH    = 0x0214,
    XBAR_INPUT_FLG_SD2FLT4_COMPL    = 0x0215,
    XBAR_INPUT_FLG_SD2FLT4_COMPH    = 0x0216,
    XBAR_INPUT_FLG_ECAP7_OUT        = 0x0217,
    //
    // XBARFLG4
    //
    XBAR_INPUT_FLG_MCANA_FEVT0      = 0x0309,
    XBAR_INPUT_FLG_MCANA_FEVT1      = 0x030A,
    XBAR_INPUT_FLG_MCANA_FEVT2      = 0x030B,
    XBAR_INPUT_FLG_CLB1_OUT4        = 0x0310,
    XBAR_INPUT_FLG_CLB1_OUT5        = 0x0311,
    XBAR_INPUT_FLG_CLB2_OUT4        = 0x0312,
    XBAR_INPUT_FLG_CLB2_OUT5        = 0x0313,
    XBAR_INPUT_FLG_CLB3_OUT4        = 0x0314,
    XBAR_INPUT_FLG_CLB3_OUT5        = 0x0315,
    XBAR_INPUT_FLG_CLB4_OUT4        = 0x0316,
    XBAR_INPUT_FLG_CLB4_OUT5        = 0x0317,
    XBAR_INPUT_FLG_CLB5_OUT4        = 0x0318,
    XBAR_INPUT_FLG_CLB5_OUT5        = 0x0319,
    XBAR_INPUT_FLG_CLB6_OUT4        = 0x031A,
    XBAR_INPUT_FLG_CLB6_OUT5        = 0x031B,
    XBAR_INPUT_FLG_ERRORSTS_ERROR   = 0x031C,
    XBAR_INPUT_FLG_ECATSYNC0        = 0x031D,
    XBAR_INPUT_FLG_ECATSYNC1        = 0x031E,
    XBAR_INPUT_FLG_CLAHALT          = 0x031F,
    //
    // XBARFLG5
    //
    XBAR_INPUT_FLG_EPWM1_TRIPOUT    = 0x0400,
    XBAR_INPUT_FLG_EPWM2_TRIPOUT    = 0x0401,
    XBAR_INPUT_FLG_EPWM3_TRIPOUT    = 0x0402,
    XBAR_INPUT_FLG_EPWM4_TRIPOUT    = 0x0403,
    XBAR_INPUT_FLG_EPWM5_TRIPOUT    = 0x0404,
    XBAR_INPUT_FLG_EPWM6_TRIPOUT    = 0x0405,
    XBAR_INPUT_FLG_EPWM7_TRIPOUT    = 0x0406,
    XBAR_INPUT_FLG_EPWM8_TRIPOUT    = 0x0407,
    XBAR_INPUT_FLG_EPWM9_TRIPOUT    = 0x0408,
    XBAR_INPUT_FLG_EPWM10_TRIPOUT   = 0x0409,
    XBAR_INPUT_FLG_EPWM11_TRIPOUT   = 0x040A,
    XBAR_INPUT_FLG_EPWM12_TRIPOUT   = 0x040B,
    XBAR_INPUT_FLG_EPWM13_TRIPOUT   = 0x040C,
    XBAR_INPUT_FLG_EPWM14_TRIPOUT   = 0x040D,
    XBAR_INPUT_FLG_EPWM15_TRIPOUT   = 0x040E,
    XBAR_INPUT_FLG_EPWM16_TRIPOUT   = 0x040F,
    XBAR_INPUT_FLG_EPWM17_TRIPOUT   = 0x0410,
    XBAR_INPUT_FLG_EPWM18_TRIPOUT   = 0x0411,
    //
    // XBARFLG6
    //
    XBAR_INPUT_FLG_EPWM1_DE_DEMONTRIP  = 0x0500,
    XBAR_INPUT_FLG_EPWM2_DE_DEMONTRIP  = 0x0501,
    XBAR_INPUT_FLG_EPWM3_DE_DEMONTRIP  = 0x0502,
    XBAR_INPUT_FLG_EPWM4_DE_DEMONTRIP  = 0x0503,
    XBAR_INPUT_FLG_EPWM5_DE_DEMONTRIP  = 0x0504,
    XBAR_INPUT_FLG_EPWM6_DE_DEMONTRIP  = 0x0505,
    XBAR_INPUT_FLG_EPWM7_DE_DEMONTRIP  = 0x0506,
    XBAR_INPUT_FLG_EPWM8_DE_DEMONTRIP  = 0x0507,
    XBAR_INPUT_FLG_EPWM9_DE_DEMONTRIP  = 0x0508,
    XBAR_INPUT_FLG_EPWM10_DE_DEMONTRIP = 0x0509,
    XBAR_INPUT_FLG_EPWM11_DE_DEMONTRIP = 0x050A,
    XBAR_INPUT_FLG_EPWM12_DE_DEMONTRIP = 0x050B,
    XBAR_INPUT_FLG_EPWM13_DE_DEMONTRIP = 0x050C,
    XBAR_INPUT_FLG_EPWM14_DE_DEMONTRIP = 0x050D,
    XBAR_INPUT_FLG_EPWM15_DE_DEMONTRIP = 0x050E,
    XBAR_INPUT_FLG_EPWM16_DE_DEMONTRIP = 0x050F,
    XBAR_INPUT_FLG_EPWM17_DE_DEMONTRIP = 0x0510,
    XBAR_INPUT_FLG_EPWM18_DE_DEMONTRIP = 0x0511,
    //
    // XBARFLG7
    //
    XBAR_INPUT_FLG_EPWM1_DE_ACTIVE    = 0x0600,
    XBAR_INPUT_FLG_EPWM2_DE_ACTIVE    = 0x0601,
    XBAR_INPUT_FLG_EPWM3_DE_ACTIVE    = 0x0602,
    XBAR_INPUT_FLG_EPWM4_DE_ACTIVE    = 0x0603,
    XBAR_INPUT_FLG_EPWM5_DE_ACTIVE    = 0x0604,
    XBAR_INPUT_FLG_EPWM6_DE_ACTIVE    = 0x0605,
    XBAR_INPUT_FLG_EPWM7_DE_ACTIVE    = 0x0606,
    XBAR_INPUT_FLG_EPWM8_DE_ACTIVE    = 0x0607,
    XBAR_INPUT_FLG_EPWM9_DE_ACTIVE    = 0x0608,
    XBAR_INPUT_FLG_EPWM10_DE_ACTIVE   = 0x0609,
    XBAR_INPUT_FLG_EPWM11_DE_ACTIVE   = 0x060A,
    XBAR_INPUT_FLG_EPWM12_DE_ACTIVE   = 0x060B,
    XBAR_INPUT_FLG_EPWM13_DE_ACTIVE   = 0x060C,
    XBAR_INPUT_FLG_EPWM14_DE_ACTIVE   = 0x060D,
    XBAR_INPUT_FLG_EPWM15_DE_ACTIVE   = 0x060E,
    XBAR_INPUT_FLG_EPWM16_DE_ACTIVE   = 0x060F,
    XBAR_INPUT_FLG_EPWM17_DE_ACTIVE   = 0x0610,
    XBAR_INPUT_FLG_EPWM18_DE_ACTIVE   = 0x0611,
    //
    // XBARFLG8
    //
    XBAR_INPUT_FLG_EPWM1A_DB_NO_HR    = 0x0700,
    XBAR_INPUT_FLG_EPWM1B_DB_NO_HR    = 0x0701,
    XBAR_INPUT_FLG_EPWM2A_DB_NO_HR    = 0x0702,
    XBAR_INPUT_FLG_EPWM2B_DB_NO_HR    = 0x0703,
    XBAR_INPUT_FLG_EPWM3A_DB_NO_HR    = 0x0704,
    XBAR_INPUT_FLG_EPWM3B_DB_NO_HR    = 0x0705,
    XBAR_INPUT_FLG_EPWM4A_DB_NO_HR    = 0x0706,
    XBAR_INPUT_FLG_EPWM4B_DB_NO_HR    = 0x0707,
    XBAR_INPUT_FLG_EPWM5A_DB_NO_HR    = 0x0708,
    XBAR_INPUT_FLG_EPWM5B_DB_NO_HR    = 0x0709,
    XBAR_INPUT_FLG_EPWM6A_DB_NO_HR    = 0x070A,
    XBAR_INPUT_FLG_EPWM6B_DB_NO_HR    = 0x070B,
    XBAR_INPUT_FLG_EPWM7A_DB_NO_HR    = 0x070C,
    XBAR_INPUT_FLG_EPWM7B_DB_NO_HR    = 0x070D,
    XBAR_INPUT_FLG_EPWM8A_DB_NO_HR    = 0x070E,
    XBAR_INPUT_FLG_EPWM8B_DB_NO_HR    = 0x070F,
    XBAR_INPUT_FLG_EPWM9A_DB_NO_HR    = 0x0710,
    XBAR_INPUT_FLG_EPWM9B_DB_NO_HR    = 0x0711,
    XBAR_INPUT_FLG_EPWM10A_DB_NO_HR   = 0x0712,
    XBAR_INPUT_FLG_EPWM10B_DB_NO_HR   = 0x0713,
    XBAR_INPUT_FLG_EPWM11A_DB_NO_HR   = 0x0714,
    XBAR_INPUT_FLG_EPWM11B_DB_NO_HR   = 0x0715,
    XBAR_INPUT_FLG_EPWM12A_DB_NO_HR   = 0x0716,
    XBAR_INPUT_FLG_EPWM12B_DB_NO_HR   = 0x0717,
    XBAR_INPUT_FLG_EPWM13A_DB_NO_HR   = 0x0718,
    XBAR_INPUT_FLG_EPWM13B_DB_NO_HR   = 0x0719,
    XBAR_INPUT_FLG_EPWM14A_DB_NO_HR   = 0x071A,
    XBAR_INPUT_FLG_EPWM14B_DB_NO_HR   = 0x071B,
    XBAR_INPUT_FLG_EPWM15A_DB_NO_HR   = 0x071C,
    XBAR_INPUT_FLG_EPWM15B_DB_NO_HR   = 0x071D,
    XBAR_INPUT_FLG_EPWM16A_DB_NO_HR   = 0x071E,
    XBAR_INPUT_FLG_EPWM16B_DB_NO_HR   = 0x071F,
    //
    // XBARFLG9
    //
    XBAR_INPUT_FLG_EPWM17A_DB_NO_HR   = 0x0800,
    XBAR_INPUT_FLG_EPWM17B_DB_NO_HR   = 0x0801,
    XBAR_INPUT_FLG_EPWM18A_DB_NO_HR   = 0x0802,
    XBAR_INPUT_FLG_EPWM18B_DB_NO_HR   = 0x0803,
    //
    // XBARFLG10
    //
    XBAR_INPUT_FLG_EPWM1A_MINDB    = 0x0900,
    XBAR_INPUT_FLG_EPWM1B_MINDB    = 0x0901,
    XBAR_INPUT_FLG_EPWM2A_MINDB    = 0x0902,
    XBAR_INPUT_FLG_EPWM2B_MINDB    = 0x0903,
    XBAR_INPUT_FLG_EPWM3A_MINDB    = 0x0904,
    XBAR_INPUT_FLG_EPWM3B_MINDB    = 0x0905,
    XBAR_INPUT_FLG_EPWM4A_MINDB    = 0x0906,
    XBAR_INPUT_FLG_EPWM4B_MINDB    = 0x0907,
    XBAR_INPUT_FLG_EPWM5A_MINDB    = 0x0908,
    XBAR_INPUT_FLG_EPWM5B_MINDB    = 0x0909,
    XBAR_INPUT_FLG_EPWM6A_MINDB    = 0x090A,
    XBAR_INPUT_FLG_EPWM6B_MINDB    = 0x090B,
    XBAR_INPUT_FLG_EPWM7A_MINDB    = 0x090C,
    XBAR_INPUT_FLG_EPWM7B_MINDB    = 0x090D,
    XBAR_INPUT_FLG_EPWM8A_MINDB    = 0x090E,
    XBAR_INPUT_FLG_EPWM8B_MINDB    = 0x090F,
    XBAR_INPUT_FLG_EPWM9A_MINDB    = 0x0910,
    XBAR_INPUT_FLG_EPWM9B_MINDB    = 0x0911,
    XBAR_INPUT_FLG_EPWM10A_MINDB   = 0x0912,
    XBAR_INPUT_FLG_EPWM10B_MINDB   = 0x0913,
    XBAR_INPUT_FLG_EPWM11A_MINDB   = 0x0914,
    XBAR_INPUT_FLG_EPWM11B_MINDB   = 0x0915,
    XBAR_INPUT_FLG_EPWM12A_MINDB   = 0x0916,
    XBAR_INPUT_FLG_EPWM12B_MINDB   = 0x0917,
    XBAR_INPUT_FLG_EPWM13A_MINDB   = 0x0918,
    XBAR_INPUT_FLG_EPWM13B_MINDB   = 0x0919,
    XBAR_INPUT_FLG_EPWM14A_MINDB   = 0x091A,
    XBAR_INPUT_FLG_EPWM14B_MINDB   = 0x091B,
    XBAR_INPUT_FLG_EPWM15A_MINDB   = 0x091C,
    XBAR_INPUT_FLG_EPWM15B_MINDB   = 0x091D,
    XBAR_INPUT_FLG_EPWM16A_MINDB   = 0x091E,
    XBAR_INPUT_FLG_EPWM16B_MINDB   = 0x091F,
    //
    // XBARFLG11
    //
    XBAR_INPUT_FLG_EPWM17A_MINDB   = 0x0A00,
    XBAR_INPUT_FLG_EPWM17B_MINDB   = 0x0A01,
    XBAR_INPUT_FLG_EPWM18A_MINDB   = 0x0A02,
    XBAR_INPUT_FLG_EPWM18B_MINDB   = 0x0A03,
    //
    // XBARFLG12
    //
    XBAR_INPUT_FLG_CLB1_OUT0    = 0x0B00,
    XBAR_INPUT_FLG_CLB1_OUT1    = 0x0B01,
    XBAR_INPUT_FLG_CLB1_OUT2    = 0x0B02,
    XBAR_INPUT_FLG_CLB1_OUT3    = 0x0B03,
    XBAR_INPUT_FLG_CLB1_OUT6    = 0x0B04,
    XBAR_INPUT_FLG_CLB1_OUT7    = 0x0B05,
    XBAR_INPUT_FLG_CLB2_OUT0    = 0x0B06,
    XBAR_INPUT_FLG_CLB2_OUT1    = 0x0B07,
    XBAR_INPUT_FLG_CLB2_OUT2    = 0x0B08,
    XBAR_INPUT_FLG_CLB2_OUT3    = 0x0B09,
    XBAR_INPUT_FLG_CLB2_OUT6    = 0x0B0A,
    XBAR_INPUT_FLG_CLB2_OUT7    = 0x0B0B,
    XBAR_INPUT_FLG_CLB3_OUT0    = 0x0B0C,
    XBAR_INPUT_FLG_CLB3_OUT1    = 0x0B0D,
    XBAR_INPUT_FLG_CLB3_OUT2    = 0x0B0E,
    XBAR_INPUT_FLG_CLB3_OUT3    = 0x0B0F,
    XBAR_INPUT_FLG_CLB3_OUT6    = 0x0B10,
    XBAR_INPUT_FLG_CLB3_OUT7    = 0x0B11,
    XBAR_INPUT_FLG_CLB4_OUT0    = 0x0B12,
    XBAR_INPUT_FLG_CLB4_OUT1    = 0x0B13,
    XBAR_INPUT_FLG_CLB4_OUT2    = 0x0B14,
    XBAR_INPUT_FLG_CLB4_OUT3    = 0x0B15,
    XBAR_INPUT_FLG_CLB4_OUT6    = 0x0B16,
    XBAR_INPUT_FLG_CLB4_OUT7    = 0x0B17,
    XBAR_INPUT_FLG_CLB5_OUT0    = 0x0B18,
    XBAR_INPUT_FLG_CLB5_OUT1    = 0x0B19,
    XBAR_INPUT_FLG_CLB5_OUT2    = 0x0B1A,
    XBAR_INPUT_FLG_CLB5_OUT3    = 0x0B1B,
    XBAR_INPUT_FLG_CLB5_OUT6    = 0x0B1C,
    XBAR_INPUT_FLG_CLB5_OUT7    = 0x0B1D,
    XBAR_INPUT_FLG_CLB6_OUT0    = 0x0B1E,
    XBAR_INPUT_FLG_CLB6_OUT1    = 0x0B1F,
    //
    // XBARFLG13
    //
    XBAR_INPUT_FLG_CLB6_OUT2        = 0x0C00,
    XBAR_INPUT_FLG_CLB6_OUT3        = 0x0C01,
    XBAR_INPUT_FLG_CLB6_OUT6        = 0x0C02,
    XBAR_INPUT_FLG_CLB6_OUT7        = 0x0C03,
    XBAR_INPUT_FLG_XTRIP_OUT1       = 0x0C04,
    XBAR_INPUT_FLG_XTRIP_OUT2       = 0x0C05,
    XBAR_INPUT_FLG_XTRIP_OUT3       = 0x0C06,
    XBAR_INPUT_FLG_XTRIP_OUT4       = 0x0C07,
    XBAR_INPUT_FLG_XTRIP_OUT5       = 0x0C08,
    XBAR_INPUT_FLG_XTRIP_OUT6       = 0x0C09,
    XBAR_INPUT_FLG_XTRIP_OUT7       = 0x0C0A,
    XBAR_INPUT_FLG_XTRIP_OUT8       = 0x0C0B,
    XBAR_INPUT_FLG_ADCA_EXTMUXSEL0  = 0x0C0C,
    XBAR_INPUT_FLG_ADCA_EXTMUXSEL1  = 0x0C0D,
    XBAR_INPUT_FLG_ADCA_EXTMUXSEL2  = 0x0C0E,
    XBAR_INPUT_FLG_ADCA_EXTMUXSEL3  = 0x0C0F,
    XBAR_INPUT_FLG_ADCB_EXTMUXSEL0  = 0x0C10,
    XBAR_INPUT_FLG_ADCB_EXTMUXSEL1  = 0x0C11,
    XBAR_INPUT_FLG_ADCB_EXTMUXSEL2  = 0x0C12,
    XBAR_INPUT_FLG_ADCB_EXTMUXSEL3  = 0x0C13,
    XBAR_INPUT_FLG_ADCC_EXTMUXSEL0  = 0x0C14,
    XBAR_INPUT_FLG_ADCC_EXTMUXSEL1  = 0x0C15,
    XBAR_INPUT_FLG_ADCC_EXTMUXSEL2  = 0x0C16,
    XBAR_INPUT_FLG_ADCC_EXTMUXSEL3  = 0x0C17,
    XBAR_INPUT_FLG_PIEERR           = 0x0C1A,
    XBAR_INPUT_FLG_ECCERR           = 0x0C1B,
    XBAR_INPUT_EPG1_OUT0            = 0x0C1C,
    XBAR_INPUT_EPG1_OUT1            = 0x0C1D,
    XBAR_INPUT_EPG1_OUT2            = 0x0C1E,
    XBAR_INPUT_EPG1_OUT3            = 0x0C1F,
    //
    // XBARFLG14
    //
    XBAR_INPUT_FLG_SD3FLT1_COMPH      = 0x0D00,
    XBAR_INPUT_FLG_SD3FLT1_COMPL      = 0x0D01,
    XBAR_INPUT_FLG_SD3FLT2_COMPH      = 0x0D02,
    XBAR_INPUT_FLG_SD3FLT2_COMPL      = 0x0D03,
    XBAR_INPUT_FLG_SD3FLT3_COMPH      = 0x0D04,
    XBAR_INPUT_FLG_SD3FLT3_COMPL      = 0x0D05,
    XBAR_INPUT_FLG_SD3FLT4_COMPH      = 0x0D06,
    XBAR_INPUT_FLG_SD3FLT4_COMPL      = 0x0D07,
    XBAR_INPUT_FLG_SD4FLT1_COMPH      = 0x0D08,
    XBAR_INPUT_FLG_SD4FLT1_COMPL      = 0x0D09,
    XBAR_INPUT_FLG_SD4FLT2_COMPH      = 0x0D0A,
    XBAR_INPUT_FLG_SD4FLT2_COMPL      = 0x0D0B,
    XBAR_INPUT_FLG_SD4FLT3_COMPH      = 0x0D0C,
    XBAR_INPUT_FLG_SD4FLT3_COMPL      = 0x0D0D,
    XBAR_INPUT_FLG_SD4FLT4_COMPH      = 0x0D0E,
    XBAR_INPUT_FLG_SD4FLT4_COMPL      = 0x0D0F,
    XBAR_INPUT_FLG_INPUTXBAR2_INPUT10 = 0x0D11,
    XBAR_INPUT_FLG_INPUTXBAR2_INPUT11 = 0x0D12,
    XBAR_INPUT_FLG_INPUTXBAR2_INPUT12 = 0x0D13,
    XBAR_INPUT_FLG_INPUTXBAR2_INPUT13 = 0x0D14,
    XBAR_INPUT_FLG_INPUTXBAR2_INPUT14 = 0x0D15,
    XBAR_INPUT_FLG_INPUTXBAR2_INPUT7  = 0x0D16,
    XBAR_INPUT_FLG_INPUTXBAR2_INPUT8  = 0x0D17,
    XBAR_INPUT_FLG_INPUTXBAR2_INPUT9  = 0x0D18,
    XBAR_INPUT_FLG_MCANB_FEVT0        = 0x0D19,
    XBAR_INPUT_FLG_MCANB_FEVT1        = 0x0D1A,
    XBAR_INPUT_FLG_MCANB_FEVT2        = 0x0D1B,
    XBAR_INPUT_FLG_FSIA_RX_TRIG1      = 0x0D1C,
    XBAR_INPUT_FLG_FSIB_RX_TRIG1      = 0x0D1D,
    XBAR_INPUT_FLG_FSIC_RX_TRIG1      = 0x0D1E,
    XBAR_INPUT_FLG_FSID_RX_TRIG1      = 0x0D1F,
    //
    // XBARFLG15
    //
    XBAR_INPUT_FLG_FSIA_RX_TRIG2      = 0x0E00,
    XBAR_INPUT_FLG_FSIA_RX_TRIG3      = 0x0E01,
    XBAR_INPUT_FLG_FSIB_RX_TRIG2      = 0x0E02,
    XBAR_INPUT_FLG_FSIB_RX_TRIG3      = 0x0E03,
    XBAR_INPUT_FLG_FSIC_RX_TRIG2      = 0x0E04,
    XBAR_INPUT_FLG_FSIC_RX_TRIG3      = 0x0E05,
    XBAR_INPUT_FLG_FSID_RX_TRIG2      = 0x0E06,
    XBAR_INPUT_FLG_FSID_RX_TRIG3      = 0x0E07,
    XBAR_INPUT_FLG_ECAP1_TRIPOUT      = 0x0E08,
    XBAR_INPUT_FLG_ECAP2_TRIPOUT      = 0x0E09,
    XBAR_INPUT_FLG_ECAP3_TRIPOUT      = 0x0E0A,
    XBAR_INPUT_FLG_ECAP4_TRIPOUT      = 0x0E0B,
    XBAR_INPUT_FLG_ECAP5_TRIPOUT      = 0x0E0C,
    XBAR_INPUT_FLG_ECAP6_TRIPOUT      = 0x0E0D,
    XBAR_INPUT_FLG_CPU1_ERADEVT10     = 0x0E0E,
    XBAR_INPUT_FLG_CPU1_ERADEVT11     = 0x0E0F,
    XBAR_INPUT_FLG_CPU1_ERADEVT8      = 0x0E10,
    XBAR_INPUT_FLG_CPU1_ERADEVT9      = 0x0E11,
    XBAR_INPUT_FLG_CPU1_ADCCHECK_EVT1 = 0x0E12,
    XBAR_INPUT_FLG_CPU1_ADCCHECK_EVT2 = 0x0E13,
    XBAR_INPUT_FLG_CPU1_ADCCHECK_EVT3 = 0x0E14,
    XBAR_INPUT_FLG_CPU1_ADCCHECK_EVT4 = 0x0E15,
    XBAR_INPUT_FLG_CPU2_ERADEVT10     = 0x0E16,
    XBAR_INPUT_FLG_CPU2_ERADEVT11     = 0x0E17,
    XBAR_INPUT_FLG_CPU2_ERADEVT8      = 0x0E18,
    XBAR_INPUT_FLG_CPU2_ERADEVT9      = 0x0E19,
    XBAR_INPUT_FLG_CPU2_ADCCHECK_EVT1 = 0x0E1A,
    XBAR_INPUT_FLG_CPU2_ADCCHECK_EVT2 = 0x0E1B,
    XBAR_INPUT_FLG_CPU2_ADCCHECK_EVT3 = 0x0E1C,
    XBAR_INPUT_FLG_CPU2_ADCCHECK_EVT4 = 0x0E1D,
    //
    // XBARFLG16
    //
    XBAR_INPUT_FLG_CMPSS9_CTRIPH     = 0x0F00,
    XBAR_INPUT_FLG_CMPSS9_CTRIPL     = 0x0F01,
    XBAR_INPUT_FLG_CMPSS9_CTRIPOUTH  = 0x0F02,
    XBAR_INPUT_FLG_CMPSS9_CTRIPOUTL  = 0x0F03,
    XBAR_INPUT_FLG_CMPSS10_CTRIPH    = 0x0F04,
    XBAR_INPUT_FLG_CMPSS10_CTRIPL    = 0x0F05,
    XBAR_INPUT_FLG_CMPSS10_CTRIPOUTH = 0x0F06,
    XBAR_INPUT_FLG_CMPSS10_CTRIPOUTL = 0x0F07,
    XBAR_INPUT_FLG_CMPSS11_CTRIPH    = 0x0F08,
    XBAR_INPUT_FLG_CMPSS11_CTRIPL    = 0x0F09,
    XBAR_INPUT_FLG_CMPSS11_CTRIPOUTH = 0x0F0A,
    XBAR_INPUT_FLG_CMPSS11_CTRIPOUTL = 0x0F0B,
    XBAR_INPUT_FLG_CMPSS12_CTRIPH    = 0x0F0C,
    XBAR_INPUT_FLG_CMPSS12_CTRIPL    = 0x0F0D,
    XBAR_INPUT_FLG_CMPSS12_CTRIPOUTH = 0x0F0E,
    XBAR_INPUT_FLG_CMPSS12_CTRIPOUTL = 0x0F0F,
    XBAR_INPUT_FLG_XCLKOUT           = 0x0F1F,
} XBAR_InputFlag;
#endif

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! \internal
//! Checks a X-BAR base address.
//!
//! \param base is the base address of the X-BAR.
//!
//! This function determines if a X-BAR base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool
XBAR_isBaseValid(uint32_t base)
{
    return((base == OUTPUTXBAR_BASE) ||
           (base == CLBOUTPUTXBAR_BASE) || (base == CLBINPUTXBAR_BASE ) ||
           (base == MINDBXBAR_BASE) || (base == ICLXBAR_BASE ) ||
           (base == INPUTXBAR_BASE));

}
#endif
//*****************************************************************************
//
//! Enables the Output X-BAR mux values to be passed to the output signal.
//!
//! \param base specifies the X-BAR Enable register base address.
//! \param output is the X-BAR output being configured.
//! \param muxes is a bit field of the muxes to be enabled.
//!
//! This function enables the mux values to be passed to the X-BAR output
//! signal. The \e output parameter is a value \b XBAR_OUTPUTy where y is
//! the output number between 1 and 8 inclusive.
//!
//! The \e base parameter can take base addresses
//! OUTPUTXBAR_BASE
//! or CLBOUTPUTXBAR_BASE.
//!
//! The \e muxes parameter is a bit field of the muxes being enabled where bit
//! 0 represents mux 0, bit 1 represents mux 1 and so on. Defines are provided
//! in the form of \b XBAR_MUXnn that can be OR'd together to enable several
//! muxes on an output at the same time. For example, passing this function
//! ( \b XBAR_MUX04 | \b XBAR_MUX10 ) would enable muxes 4 and 10.
//!
//! \return None.
//
//*****************************************************************************
static inline void
XBAR_enableOutputMux(uint32_t base, XBAR_OutputNum output, uint64_t muxes)
{
    uint16_t outputNum = (uint16_t)output;
    //
    // Check the arguments.
    //
    ASSERT(XBAR_isBaseValid(base));

    //
    // Set the enable bit.
    //
    EALLOW;


    EDIS;

    if(base == OUTPUTXBAR_BASE)
    {
        EALLOW;
        HWREG(base + XBAR_O_OUTPUT1MUXENABLE + outputNum + 2U) |=
              (muxes >> 32U);

        HWREG(base + XBAR_O_OUTPUT1MUXENABLE + outputNum) |= muxes;
        EDIS;
    }
    else
    {
        EALLOW;
        HWREG(base + CLBXBAR_O_OUTPUT1MUXENABLE + (outputNum / 2U)) |= muxes;
        EDIS;
    }

}

//*****************************************************************************
//
//! Disables the Output X-BAR mux values from being passed to the output.
//!
//! \param base specifies the X-BAR Enable Register base address.
//! \param output is the X-BAR output being configured.
//! \param muxes is a bit field of the muxes to be disabled.
//!
//! This function disables the mux values from being passed to the X-BAR output
//! signal. The \e output parameter is a value \b XBAR_OUTPUTy where y is
//! the output number between 1 and 8 inclusive.
//!
//! The \e base parameter can take base addresses
//! OUTPUTXBAR_BASE
//! or CLBOUTPUTXBAR_BASE.
//!
//! The \e muxes parameter is a bit field of the muxes being disabled where bit
//! 0 represents mux 0, bit 1 represents mux 1 and so on. Defines are provided
//! in the form of \b XBAR_MUXnn that can be OR'd together to disable several
//! muxes on an output at the same time. For example, passing this function
//! ( \b XBAR_MUX04 | \b XBAR_MUX10 ) would disable muxes 4 and 10.
//!
//! \return None.
//
//*****************************************************************************
static inline void
XBAR_disableOutputMux(uint32_t base, XBAR_OutputNum output, uint64_t muxes)
{
    uint16_t outputNum = (uint16_t)output;

    //
    // Check the arguments.
    //
    ASSERT(XBAR_isBaseValid(base));

    //
    // Clear the enable bit.
    //
    EALLOW;


    EDIS;
    if(base == OUTPUTXBAR_BASE)
    {
        EALLOW;
        HWREG(base + XBAR_O_OUTPUT1MUXENABLE + outputNum + 2U) &=
              ~(muxes >> 32U);

        HWREG(base + XBAR_O_OUTPUT1MUXENABLE + outputNum) &= ~(muxes);
        EDIS;
    }
    else
    {
        EALLOW;
        HWREG(base + CLBXBAR_O_OUTPUT1MUXENABLE + (outputNum / 2U)) &=
              ~(muxes);
        EDIS;
    }
}

//*****************************************************************************
//
//! Enables or disables the output latch to drive the selected output.
//!
//! \param base specifies the X-BAR base address.
//! \param output is the X-BAR output being configured.
//! The valid inputs are XBAR_OUTPUTy where y is from 1 to 8.
//! \param enable is a flag that determines whether or not the latch is
//! selected to drive the X-BAR output.
//!
//! The \e base parameter can take base addresses
//! OUTPUTXBAR_BASE
//! or CLBOUTPUTXBAR_BASE.
//!
//! This function sets the Output X-BAR output signal latch mode. If the
//! \e enable parameter is \b true, the output specified by \e output will be
//! driven by the output latch.
//!
//! \return None.
//
//*****************************************************************************
static inline void
XBAR_setOutputLatchMode(uint32_t base, XBAR_OutputNum output, bool enable)
{
    //
    // Check the arguments.
    //
    ASSERT(XBAR_isBaseValid(base));

    EALLOW;

    //
    // Set or clear the latch setting bit based on the enable parameter.
    //
    if(enable)
    {
    if(base == OUTPUTXBAR_BASE)
    {
        HWREGH(base + XBAR_O_OUTPUTLATCHENABLE) |=
               0x1U << ((uint16_t)output / 4U);
    }
    else
    {
        HWREGH(base + CLBXBAR_O_OUTPUTLATCHENABLE) |=
               0x1U << ((uint16_t)output / 4U);
    }
    }
    else
    {
    if(base == OUTPUTXBAR_BASE)
    {
        HWREGH(base + XBAR_O_OUTPUTLATCHENABLE) &=
               ~(0x1U << ((uint16_t)output / 4U));
    }
    else
    {
        HWREGH(base + CLBXBAR_O_OUTPUTLATCHENABLE) &=
               ~(0x1U << ((uint16_t)output / 4U));
    }
    }

    EDIS;
}

//*****************************************************************************
//
//! Returns the status of the output latch
//!
//! \param base specifies the X-BAR base address.
//! \param output is the X-BAR output being checked.
//! The valid inputs are XBAR_OUTPUTy where y is from 1 to 8.
//!
//! The \e base parameter can take base addresses
//! OUTPUTXBAR_BASE
//! or CLBOUTPUTXBAR_BASE.
//!
//! \return Returns \b true if the output corresponding to \e output was
//! triggered. If not, it will return \b false.
//
//*****************************************************************************
static inline bool
XBAR_getOutputLatchStatus(uint32_t base, XBAR_OutputNum output)
{
    //
    // Check the arguments.
    //
    ASSERT(XBAR_isBaseValid(base));

    //
    // Get the status of the Output X-BAR output latch.
    //
    if(base == OUTPUTXBAR_BASE)
    {
        return((HWREGH(base + XBAR_O_OUTPUTLATCH) &
                (0x1U << ((uint16_t)output / 4U))) != 0U);
    }
    else
    {
        return((HWREGH(base + CLBXBAR_O_OUTPUTLATCH) &
                (0x1U << ((uint16_t)output / 4U))) != 0U);
    }
}

//*****************************************************************************
//
//! Clears the output latch for the specified output.
//!
//! \param base specifies the X-BAR base address.
//! \param output is the X-BAR output being configured.
//! The valid inputs are XBAR_OUTPUTy where y is from 1 to 8.
//!
//! The \e base parameter can take base addresses
//! OUTPUTXBAR_BASE
//! or CLBOUTPUTXBAR_BASE.
//!
//! This function clears the Output X-BAR output latch. The output to be
//! configured is specified by the \e output parameter.
//!
//! \return None.
//
//*****************************************************************************
static inline void
XBAR_clearOutputLatch(uint32_t base, XBAR_OutputNum output)
{
    //
    // Check the arguments.
    //
    ASSERT(XBAR_isBaseValid(base));

    //
    // Set the bit that clears the corresponding OUTPUTLATCH bit.
    //
    if(base == OUTPUTXBAR_BASE)
    {
        HWREGH(base + XBAR_O_OUTPUTLATCHCLR) |=
        0x1U << ((uint16_t)output / 4U);
    }
    else
    {
        HWREGH(base + CLBXBAR_O_OUTPUTLATCHCLR) |=
        0x1U << ((uint16_t)output / 4U);
    }
}

//*****************************************************************************
//
//! Forces the output latch for the specified output.
//!
//! \param base specifies the X-BAR base address.
//! \param output is the X-BAR output being configured.
//! The valid inputs are XBAR_OUTPUTy where y is from 1 to 8.
//!
//! The \e base parameter can take base addresses
//! OUTPUTXBAR_BASE
//! or CLBOUTPUTXBAR_BASE.
//!
//! This function forces the Output X-BAR output latch. The output to be
//! configured is specified by the \e output parameter.
//!
//! \return None.
//
//*****************************************************************************
static inline void
XBAR_forceOutputLatch(uint32_t base, XBAR_OutputNum output)
{
    //
    // Check the arguments.
    //
    ASSERT(XBAR_isBaseValid(base));

    //
    // Set the bit that forces the corresponding OUTPUTLATCH bit.
    //
    if(base == OUTPUTXBAR_BASE)
    {
        HWREGH(base + XBAR_O_OUTPUTLATCHFRC) =
        (uint16_t)0x1U << ((uint16_t)output / 4U);
    }
    else
    {
        HWREGH(base + CLBXBAR_O_OUTPUTLATCHFRC) =
        (uint16_t)0x1U << ((uint16_t)output / 4U);
    }
}

//*****************************************************************************
//
//! Configures the polarity of an Output X-BAR output.
//!
//! \param base specifies the X-BAR base address.
//! \param output is the X-BAR output being configured.
//! The valid inputs are XBAR_OUTPUTy where y is from 1 to 8.
//! \param invert is a flag that determines whether the output is active-high
//! or active-low.
//!
//! The \e base parameter can take base addresses
//! OUTPUTXBAR_BASE
//! or CLBOUTPUTXBAR_BASE.
//!
//! This function inverts the Output X-BAR signal if the \e invert parameter is
//! \b true. If \e invert is \b false, the signal will be passed as is. The
//! \e output parameter is a value \b XBAR_OUTPUTy where y is the output
//! number between 1 and 8 inclusive.
//!
//! \return None.
//
//*****************************************************************************
static inline void
XBAR_invertOutputSignal(uint32_t base, XBAR_OutputNum output, bool invert)
{
    //
    // Check the arguments.
    //
    ASSERT(XBAR_isBaseValid(base));

    //
    // Set or clear the polarity setting bit based on the invert parameter.
    //
    EALLOW;

    if(invert)
    {
    if(base == OUTPUTXBAR_BASE)
    {
        HWREGH(base + XBAR_O_OUTPUTINV) |=
            0x1U << ((uint16_t)output / 4U);
    }
    else
    {
        HWREGH(base + CLBXBAR_O_OUTPUTINV) |=
            0x1U << ((uint16_t)output / 4U);
    }
    }
    else
    {
    if(base == OUTPUTXBAR_BASE)
    {
        HWREGH(base + XBAR_O_OUTPUTINV) &=
            ~(0x1U << ((uint16_t)output / 4U));
    }
    else
    {
        HWREGH(base + CLBXBAR_O_OUTPUTINV) &=
            ~(0x1U << ((uint16_t)output / 4U));
    }
    }

    EDIS;
}

//*****************************************************************************
//
//! Enables the ePWM X-BAR mux values to be passed to an ePWM module.
//!
//! \param trip is the X-BAR output being configured.
//! \param muxes is a bit field of the muxes to be enabled.
//!
//! This function enables the mux values to be passed to the X-BAR trip
//! signal. The \e trip parameter is a value \b XBAR_TRIPy where y is
//! the number of the trip signal on the ePWM.
//!
//! The \e muxes parameter is a bit field of the muxes being enabled where bit
//! 0 represents mux 0, bit 1 represents mux 1 and so on. Defines are provided
//! in the form of \b XBAR_MUXnn that can be logically OR'd together to
//! enable several muxes on an output at the same time.
//!
//! \return None.
//
//*****************************************************************************
static inline void
XBAR_enableEPWMMux(XBAR_TripNum trip, uint64_t muxes)
{
    uint32_t base;
    uint32_t tripSel = (uint32_t)trip;
    if (tripSel <= (uint16_t)XBAR_TRIP8)
    {
        base = XBARA_EPWM_EN_REG_BASE;
    }
    else
    {
        base = XBARB_EPWM_EN_REG_BASE;
        tripSel = tripSel - 32U;
    }
    //
    // Set the enable bit.
    //
    EALLOW;

    HWREG(base + tripSel + 2U) |= (uint32_t)(muxes >> 32U);

    HWREG(base + tripSel) |= muxes;
    EDIS;
}

//*****************************************************************************
//
//! Disables the ePWM X-BAR mux values to be passed to an ePWM module.
//!
//! \param trip is the X-BAR output being configured.
//! \param muxes is a bit field of the muxes to be disabled.
//!
//! This function disables the mux values to be passed to the X-BAR trip
//! signal. The \e trip parameter is a value \b XBAR_TRIPy where y is
//! the number of the trip signal on the ePWM.
//!
//! The \e muxes parameter is a bit field of the muxes being disabled where bit
//! 0 represents mux 0, bit 1 represents mux 1 and so on. Defines are provided
//! in the form of \b XBAR_MUXnn that can be logically OR'd together to
//! disable several muxes on an output at the same time.
//!
//! \return None.
//
//*****************************************************************************
static inline void
XBAR_disableEPWMMux(XBAR_TripNum trip, uint64_t muxes)
{
    uint32_t base;
    uint32_t tripSel = (uint32_t)trip;
    if (tripSel <= (uint16_t)XBAR_TRIP8)
    {
        base = XBARA_EPWM_EN_REG_BASE;
    }
    else
    {
        base = XBARB_EPWM_EN_REG_BASE;
        tripSel = tripSel - 32U;
    }

    //
    // Clear the enable bit.
    //
    EALLOW;

    HWREG(base + tripSel + 2U) &= ~(uint32_t)(muxes >> 32U);

    HWREG(base + tripSel) &= ~(muxes);

    EDIS;
}

//*****************************************************************************
//
//! Configures the polarity of an ePWM X-BAR output.
//!
//! \param trip is the X-BAR output being configured.
//! \param invert is a flag that determines whether the output is active-high
//! or active-low.
//!
//! The \e base parameter can take base addresses
//! EPWMXBARA_BASE or EPWMXBARB_BASE
//!
//! This function inverts the ePWM X-BAR trip signal if the \e invert
//! parameter is \b true. If \e invert is \b false, the signal will be passed
//! as is. The \e trip parameter is a value \b XBAR_TRIPy where y is
//! the number of the trip signal on the ePWM X-BAR that is being configured.
//!
//! \return None.
//
//*****************************************************************************
static inline void
XBAR_invertEPWMSignal(XBAR_TripNum trip, bool invert)
{
    uint32_t base;
    uint32_t tripSel = (uint32_t)trip;
    if (tripSel <= (uint16_t)XBAR_TRIP8)
    {
        base = EPWMXBARA_BASE;
    }
    else
    {
        base = EPWMXBARB_BASE;
        tripSel = tripSel - 32U;
    }

    //
    // Set or clear the polarity setting bit based on the invert parameter.
    //
    EALLOW;

    if(invert)
    {
        HWREGH(base + XBAR_O_TRIPOUTINV) |=
            0x1U << (tripSel / 4U);
    }
    else
    {
        HWREGH(base + XBAR_O_TRIPOUTINV) &=
            ~(0x1U << (tripSel / 4U));
    }

    EDIS;
}

//*****************************************************************************
//
//! Sets the GPIO / non-GPIO pin for an Input X-BAR input.
//!
//! \param base specifies the X-BAR base address.
//! \param input is the X-BAR input being configured.
//! \param pin is the identifying number of the pin.
//!
//! The \e base parameter can take base addresses
//! INPUTXBAR_BASE
//! or CLBINPUTXBAR_BASE.
//!
//! This function configures which GPIO is assigned to an Input X-BAR input.
//! The \e input parameter is a value in the form of a define \b XBAR_INPUTy
//! where y is a the input number for the Input X-BAR.
//!
//! The pin is specified by its numerical value. For example, GPIO34 is
//! specified by passing 34 as \e pin.
//!
//! For the other non - GPIO values:
//! 0xFFFD: '1' will be driven to the destination
//! 0xFFFE: '1' will be driven to the destination
//! 0xFFFF: '0' will be driven to the destination
//! NOTE: Pin value greater than the available number of GPIO pins on a
//! device (except 0xFFFF) will cause the destination to be driven '1'.
//!
//! \return None.
//
//*****************************************************************************
static inline void
XBAR_setInputPin(uint32_t base, XBAR_InputNum input, uint16_t pin)
{
    //
    // Check the argument.
    //
    ASSERT((pin <= XBAR_GPIO_MAX_CNT) ||
          ((pin >= XBAR_NON_GPIO_MIN_CNT) && (pin <= XBAR_NON_GPIO_MAX_CNT)) ||
          ((pin >= XBAR_GPIO_AIO_MIN_CNT) && (pin <= XBAR_GPIO_AIO_MAX_CNT)));
    ASSERT(XBAR_isBaseValid(base));

    //
    // Write the requested pin to the appropriate input select register.
    //
    EALLOW;

    HWREGH(base + XBAR_O_INPUT1SELECT + (uint16_t)input) = pin;

    EDIS;
}

//*****************************************************************************
//
//! Selects the input signal for MINDB or ICL X-BAR.
//!
//! \param base specifies the X-BAR base address.
//! \param input is the X-BAR input being configured.
//! \param signal is the input signal to be enabled.
//!
//! The \e base parameter can take base addresses
//! MINDBXBAR_BASE or ICLXBAR_BASE.
//!
//! This function configures which signal is assigned to an MINDB or ICL XBAR.
//!
//! The \e input parameter is a value in the form of a define \b XBAR_INPUTy
//! where y is a the input number for the Input X-BAR.
//!
//! The \e signal parameter inputs are passed through \e XBAR_InputSignal
//! enumumeration.
//! The connections to the MINDB and ICL XBAR corresponding to the \e signal
//! parameter are described in the device reference manual.
//!
//! \return None.
//
//*****************************************************************************
static inline void
XBAR_setInputSignal(uint32_t base, XBAR_InputNum input,
                                        XBAR_InputSignal inputSignal)
{
    //
    // Check the argument.
    //
    ASSERT((base == MINDBXBAR_BASE) || (base == ICLXBAR_BASE));

    if(base == MINDBXBAR_BASE)
    {
        //
        // Enable the requested signal to the appropriate input select register.
        //
        EALLOW;
        HWREGH(base + XBAR_O_MDL1SELECT +
               (uint16_t)input) = (uint16_t)inputSignal;
        EDIS;
    }
    else
    {
        //
        // Enable the requested signal to the appropriate input select register.
        //
        EALLOW;
        HWREGH(base + XBAR_O_ICL1SELECT +
               (uint16_t)input) = (uint16_t)inputSignal;
        EDIS;
    }
}

//*****************************************************************************
//
//! Locks an input to the Input X-BAR.
//!
//! \param base specifies the X-BAR base address.
//! \param input is an input to the Input X-BAR.
//!
//! This function locks the specific input on the Input X-BAR.
//!
//! The \e base parameter can take base addresses
//! INPUTXBAR_BASE
//! MINDBXBAR_BASE, ICLXBAR_BASE
//! or CLBINPUTXBAR_BASE .
//!
//! \return None.
//
//*****************************************************************************
static inline void
XBAR_lockInput(uint32_t base, XBAR_InputNum input)
{
    //
    // Check the arguments.
    //
    ASSERT(XBAR_isBaseValid(base));

    //
    // lock the input in the INPUTSELECTLOCK register.
    //
    EALLOW;
    HWREG(base + XBAR_O_INPUTSELECTLOCK) =
            1UL << (uint16_t)input;
    EDIS;
}

//*****************************************************************************
//
//! Locks the Output X-BAR.
//!
//! \param base specifies the X-BAR base address.
//! This function locks the Output X-BAR.
//!
//! The \e base parameter can take base addresses
//! OUTPUTXBAR_BASE
//! or CLBOUTPUTXBAR_BASE.
//!
//! \return None.
//
//*****************************************************************************
static inline void
XBAR_lockOutput(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(XBAR_isBaseValid(base));

    //
    // Lock the Output X-BAR with the OUTPUTLOCK register.
    // Write key 0x5A5A to the KEY bits and 1 to LOCK bit.
    //
    EALLOW;

    if(base == OUTPUTXBAR_BASE)
    {
        HWREG(base + XBAR_O_OUTPUTLOCK) =
         ((uint32_t)0x5A5A << XBAR_OUTPUTLOCK_KEY_S) |
         (uint32_t)XBAR_OUTPUTLOCK_LOCK;
    }
    else
    {
        HWREG(base + CLBXBAR_O_OUTPUTLOCK) =
         ((uint32_t)0x5A5A << XBAR_OUTPUTLOCK_KEY_S) |
         (uint32_t)XBAR_OUTPUTLOCK_LOCK;
    }

    EDIS;
}

//*****************************************************************************
//
//! Locks the ePWM X-BAR.
//!
//! This function locks the ePWM X-BAR.
//!
//! The \e base parameter can take base addresses
//! EPWMXBARA_BASE or EPWMXBARB_BASE
//!
//! \return None.
//
//*****************************************************************************
static inline void
XBAR_lockEPWM(uint32_t base)
{
    //
    // Lock the ePWM X-BAR with the TRIPLOCK register.
    // Write key 0x5A5A to the KEY bits and 1 to LOCK bit.
    //
    EALLOW;

    HWREG(base + XBAR_O_TRIPLOCK) =
        ((uint32_t)0x5A5A << XBAR_TRIPLOCK_KEY_S) |
        (uint32_t)XBAR_TRIPLOCK_LOCK;
    EDIS;
}

//*****************************************************************************
//
//! Enables the CLB X-BAR mux values to be passed to an CLB module.
//!
//! \param auxSignal is the X-BAR output being configured.
//! \param muxes is a bit field of the muxes to be enabled.
//!
//! This function enables the mux values to be passed to the X-BAR auxSignal
//! signal. The \e auxSignal parameter is a value \b XBAR_AUXSIGy where y is
//! the number of the signal on the CLB.
//!
//! The \e muxes parameter is a bit field of the muxes being enabled where bit
//! 0 represents mux 0, bit 1 represents mux 1 and so on. Defines are provided
//! in the form of \b XBAR_MUXnn that can be logically OR'd together to
//! enable several muxes on an output at the same time.
//!
//! \return None.
//
//*****************************************************************************
static inline void
XBAR_enableCLBMux(XBAR_AuxSigNum auxSignal, uint32_t muxes)
{
    //
    // Set the enable bit.
    //
    EALLOW;

    HWREG(XBAR_CLB_EN_REG_BASE + (uint32_t)auxSignal) |= muxes;

    EDIS;
}

//*****************************************************************************
//
//! Disables the CLB X-BAR mux values to be passed to an CLB module.
//!
//! \param auxSignal is the X-BAR output being configured.
//! \param muxes is a bit field of the muxes to be disabled.
//!
//! This function disables the mux values to be passed to the X-BAR auxSignal
//! signal. The \e auxSignal parameter is a value \b XBAR_AUXSIGy where y is
//! the number of the signal on the CLB.
//!
//! The \e muxes parameter is a bit field of the muxes being disabled where bit
//! 0 represents mux 0, bit 1 represents mux 1 and so on. Defines are provided
//! in the form of \b XBAR_MUXnn that can be logically OR'd together to
//! disable several muxes on an output at the same time.
//!
//! \return None.
//
//*****************************************************************************
static inline void
XBAR_disableCLBMux(XBAR_AuxSigNum auxSignal, uint32_t muxes)
{
    //
    // Clear the enable bit.
    //
    EALLOW;

    HWREG(XBAR_CLB_EN_REG_BASE + (uint32_t)auxSignal) &= ~(muxes);

    EDIS;
}

//*****************************************************************************
//
//! Configures the polarity of an CLB X-BAR output.
//!
//! \param auxSignal is the X-BAR output being configured.
//! \param invert is a flag that determines whether the output is active-high
//! or active-low.
//!
//! This function inverts the CLB X-BAR auxSignal signal if the \e invert
//! parameter is \b true. If \e invert is \b false, the signal will be passed
//! as is. The \e auxSignal parameter is a value \b XBAR_AUXSIGy where y is
//! the number of the signal on the CLB X-BAR that is being configured.
//!
//! \return None.
//
//*****************************************************************************
static inline void
XBAR_invertCLBSignal(XBAR_AuxSigNum auxSignal, bool invert)
{
    //
    // Set or clear the polarity setting bit based on the invert parameter.
    //
    EALLOW;

    if(invert)
    {
        HWREGH(CLBXBAR_BASE + XBAR_O_AUXSIGOUTINV) |=
            0x1U << ((uint16_t)auxSignal / 2U);
    }
    else
    {
        HWREGH(CLBXBAR_BASE + XBAR_O_AUXSIGOUTINV) &=
            ~(0x1U << ((uint16_t)auxSignal / 2U));
    }

    EDIS;
}

//*****************************************************************************
//
//! Configures the Output X-BAR mux that determines the signals passed to an
//! output.
//!
//! \param base specifies the X-BAR Config Register base address.
//! \param output is the X-BAR output being configured.
//! \param muxConfig is mux configuration that specifies the signal.
//!
//! This function configures an Output X-BAR mux. This determines which
//! signal(s) should be passed through the X-BAR to a GPIO. The \e output
//! parameter is a value \b XBAR_OUTPUTy where y is a the output number
//! between 1 and 8 inclusive.
//!
//! The \e base parameter can take base addresses
//! OUTPUTXBAR_BASE
//! or CLBOUTPUTXBAR_BASE.
//!
//! The \e muxConfig parameter for OUTPUT XBAR is the mux configuration
//! value that specifies which signal will be passed from the mux. The
//! values have the format of \b XBAR_OUT_MUXnn_xx where the 'xx' is
//! the signal and nn is the mux number.
//!
//! The \e muxConfig parameter for the CLB OUTPUT XBAR have the similar
//! format as \b XBAR_OUT_MUXnn_xx where the 'xx' is the signal and nn is
//! the mux number.
//!
//! This function may be called for each mux of an output and their values will
//! be logically OR'd before being passed to the output signal. This means that
//! this function may be called, for example, with the argument
//! \b XBAR_OUT_MUX00_ECAP1_OUT and then with the argument
//! \b XBAR_OUT_MUX01_INPUTXBAR1, resulting in the values of MUX00 and MUX01
//! being logically OR'd if both are enabled. Calling the function twice for
//! the same mux on the output will result in the configuration in the second
//! call overwriting the first.
//!
//! \return None.
//
//*****************************************************************************
extern void
XBAR_setOutputMuxConfig(uint32_t base, XBAR_OutputNum output,
                        XBAR_OutputMuxConfig muxConfig);

//*****************************************************************************
//
//! Configures the ePWM X-BAR mux that determines the signals passed to an
//! ePWM module.
//!
//! \param trip is the X-BAR output being configured.
//! \param muxConfig is mux configuration that specifies the signal.
//!
//! This function configures an ePWM X-BAR mux. This determines which signal(s)
//! should be passed through the X-BAR to an ePWM module. The \e trip
//! parameter is a value \b XBAR_TRIPy where y is a the number of the trip
//! signal on the ePWM.
//!
//! The \e muxConfig parameter is the mux configuration value that specifies
//! which signal will be passed from the mux. The values have the format of
//! \b XBAR_EPWM_MUXnn_xx where the 'xx' is the signal and nn is the mux
//! number (0 through 31). The possible values are found in <tt>xbar.h</tt>
//!
//! This function may be called for each mux of an output and their values will
//! be logically OR'd before being passed to the trip signal. This means that
//! this function may be called, for example, with the argument
//! \b XBAR_EPWM_MUX00_ECAP1_OUT and then with the argument
//! \b XBAR_EPWM_MUX01_INPUTXBAR1, resulting in the values of MUX00 and MUX01
//! being logically OR'd if both are enabled. Calling the function twice for
//! the same mux on the output will result in the configuration in the second
//! call overwriting the first.
//!
//! \return None.
//
//*****************************************************************************
extern void
XBAR_setEPWMMuxConfig(XBAR_TripNum trip, XBAR_EPWMMuxConfig muxConfig);

//*****************************************************************************
//
//! Returns the status of the input latch.
//!
//! \param inputFlag is the X-BAR input latch being checked. Values are in the
//! format of /b XBAR_INPUT_FLG_XXXX where "XXXX" is name of the signal.
//!
//! \return Returns \b true if the X-BAR input corresponding to the
//! \e inputFlag has been triggered. If not, it will return \b false.
//
//*****************************************************************************
extern bool
XBAR_getInputFlagStatus(XBAR_InputFlag inputFlag);

//*****************************************************************************
//
//! Clears the input latch for the specified input latch.
//!
//! \param inputFlag is the X-BAR input latch being cleared.
//!
//! This function clears the Input X-BAR input latch. The input latch to be
//! cleared is specified by the \e inputFlag parameter.
//!
//! \return None.
//
//*****************************************************************************
extern void
XBAR_clearInputFlag(XBAR_InputFlag inputFlag);

//*****************************************************************************
//
//! Configures the CLB X-BAR mux that determines the signals passed to a
//! CLB module.
//!
//! \param auxSignal is the X-BAR output being configured.
//! \param muxConfig is mux configuration that specifies the signal.
//!
//! This function configures an CLB X-BAR mux. This determines which signal(s)
//! should be passed through the X-BAR to an CLB module. The \e auxSignal
//! parameter is a value \b XBAR_AUXSIGy where y is a the number of the
//! signal on the CLB.
//!
//! The \e muxConfig parameter is the mux configuration value that specifies
//! which signal will be passed from the mux. The values have the format of
//! \b XBAR_CLB_MUXnn_xx where the 'xx' is the signal and nn is the mux
//! number (0 through 31). The possible values are found in <tt>xbar.h</tt>
//!
//! This function may be called for each mux of an output and their values will
//! be logically OR'd before being passed to the signal. This means that
//! this function may be called, for example, with the argument
//! \b XBAR_CLB_MUX00_ECAP1_OUT and then with the argument
//! \b XBAR_CLB_MUX03_INPUTXBAR2, resulting in the values of MUX00 and MUX03
//! being logically OR'd if both are enabled. Calling the function twice for
//! the same mux on the output will result in the configuration in the second
//! call overwriting the first.
//!
//! \return None.
//
//*****************************************************************************
extern void XBAR_setCLBMuxConfig(XBAR_AuxSigNum auxSignal,
                                 XBAR_CLBMuxConfig muxConfig);

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // XBAR_H
