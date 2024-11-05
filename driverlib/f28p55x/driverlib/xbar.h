//###########################################################################
//
// FILE:   xbar.h
//
// TITLE:  C28x X-BAR driver.
//
//###########################################################################
// 
// C2000Ware v5.04.00.00
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
#define XBAR_EPWM_CFG_REG_BASE    (EPWMXBAR_BASE + XBAR_O_TRIP4MUX0TO15CFG)
#define XBAR_EPWM_EN_REG_BASE     (EPWMXBAR_BASE + XBAR_O_TRIP4MUXENABLE)
#define XBAR_CLB_CFG_REG_BASE     (CLBXBAR_BASE + XBAR_O_AUXSIG0MUX0TO15CFG)
#define XBAR_CLB_EN_REG_BASE      (CLBXBAR_BASE + XBAR_O_AUXSIG0MUXENABLE)

#define XBAR_INPUT_FLG_INPUT_M    0x00FFU
#define XBAR_INPUT_FLG_REG_M      0xFF00U
#define XBAR_INPUT_FLG_REG_1      0x0000U
#define XBAR_INPUT_FLG_REG_2      0x0100U
#define XBAR_INPUT_FLG_REG_3      0x0200U
#define XBAR_INPUT_FLG_REG_4      0x0300U

#define XBAR_GPIO_MAX_CNT                81U
#define XBAR_GPIO_AIO_MIN_CNT            208U
#define XBAR_GPIO_AIO_MAX_CNT            253U
#define XBAR_NON_GPIO_MIN_CNT            0xFFFDU
#define XBAR_NON_GPIO_MAX_CNT            0xFFFFU

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
    XBAR_OUTPUT2 = 2,       //!< OUTPUT2 of the Output X-BAR
    XBAR_OUTPUT3 = 4,       //!< OUTPUT3 of the Output X-BAR
    XBAR_OUTPUT4 = 6,       //!< OUTPUT4 of the Output X-BAR
    XBAR_OUTPUT5 = 8,       //!< OUTPUT5 of the Output X-BAR
    XBAR_OUTPUT6 = 10,      //!< OUTPUT6 of the Output X-BAR
    XBAR_OUTPUT7 = 12,      //!< OUTPUT7 of the Output X-BAR
    XBAR_OUTPUT8 = 14,      //!< OUTPUT8 of the Output X-BAR
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
    XBAR_TRIP4  = 0,        //!< TRIP4 of the ePWM X-BAR
    XBAR_TRIP5  = 2,        //!< TRIP5 of the ePWM X-BAR
    XBAR_TRIP7  = 4,        //!< TRIP7 of the ePWM X-BAR
    XBAR_TRIP8  = 6,        //!< TRIP8 of the ePWM X-BAR
    XBAR_TRIP9  = 8,        //!< TRIP9 of the ePWM X-BAR
    XBAR_TRIP10 = 10,       //!< TRIP10 of the ePWM X-BAR
    XBAR_TRIP11 = 12,       //!< TRIP11 of the ePWM X-BAR
    XBAR_TRIP12 = 14        //!< TRIP12 of the ePWM X-BAR
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
	XBAR_OUT_MUX00_CMPSS1_CTRIPOUTH		 = 0x0000,	//!OUT MUX00 CMPSS1 CTRIPOUTH
	XBAR_OUT_MUX00_CMPSS1_CTRIPOUTH_OR_L		 = 0x0001,	//!OUT MUX00 CMPSS1 CTRIPOUTH OR L
	XBAR_OUT_MUX00_ADCAEVT1		 = 0x0002,	//!OUT MUX00 ADCAEVT1
	XBAR_OUT_MUX00_ECAP1_OUT		 = 0x0003,	//!OUT MUX00 ECAP1 OUT
	XBAR_OUT_MUX01_CMPSS1_CTRIPOUTL		 = 0x0200,	//!OUT MUX01 CMPSS1 CTRIPOUTL
	XBAR_OUT_MUX01_INPUTXBAR1		 = 0x0201,	//!OUT MUX01 INPUTXBAR1
	XBAR_OUT_MUX01_CLB1_OUT4		 = 0x0202,	//!OUT MUX01 CLB1 OUT4
	XBAR_OUT_MUX01_ADCCEVT1		 = 0x0203,	//!OUT MUX01 ADCCEVT1
	XBAR_OUT_MUX02_CMPSS2_CTRIPOUTH		 = 0x0400,	//!OUT MUX02 CMPSS2 CTRIPOUTH
	XBAR_OUT_MUX02_CMPSS2_CTRIPOUTH_OR_L		 = 0x0401,	//!OUT MUX02 CMPSS2 CTRIPOUTH OR L
	XBAR_OUT_MUX02_ADCAEVT2		 = 0x0402,	//!OUT MUX02 ADCAEVT2
	XBAR_OUT_MUX02_ECAP2_OUT		 = 0x0403,	//!OUT MUX02 ECAP2 OUT
	XBAR_OUT_MUX03_CMPSS2_CTRIPOUTL		 = 0x0600,	//!OUT MUX03 CMPSS2 CTRIPOUTL
	XBAR_OUT_MUX03_INPUTXBAR2		 = 0x0601,	//!OUT MUX03 INPUTXBAR2
	XBAR_OUT_MUX03_CLB1_OUT5		 = 0x0602,	//!OUT MUX03 CLB1 OUT5
	XBAR_OUT_MUX03_ADCCEVT2		 = 0x0603,	//!OUT MUX03 ADCCEVT2
	XBAR_OUT_MUX04_CMPSS3_CTRIPOUTH		 = 0x0800,	//!OUT MUX04 CMPSS3 CTRIPOUTH
	XBAR_OUT_MUX04_CMPSS3_CTRIPOUTH_OR_L		 = 0x0801,	//!OUT MUX04 CMPSS3 CTRIPOUTH OR L
	XBAR_OUT_MUX04_ADCAEVT3		 = 0x0802,	//!OUT MUX04 ADCAEVT3
	XBAR_OUT_MUX05_CMPSS3_CTRIPOUTL		 = 0x0A00,	//!OUT MUX05 CMPSS3 CTRIPOUTL
	XBAR_OUT_MUX05_INPUTXBAR3		 = 0x0A01,	//!OUT MUX05 INPUTXBAR3
	XBAR_OUT_MUX05_CLB2_OUT4		 = 0x0A02,	//!OUT MUX05 CLB2 OUT4
	XBAR_OUT_MUX05_ADCCEVT3		 = 0x0A03,	//!OUT MUX05 ADCCEVT3
	XBAR_OUT_MUX06_CMPSS4_CTRIPOUTH		 = 0x0C00,	//!OUT MUX06 CMPSS4 CTRIPOUTH
	XBAR_OUT_MUX06_CMPSS4_CTRIPOUTH_OR_L		 = 0x0C01,	//!OUT MUX06 CMPSS4 CTRIPOUTH OR L
	XBAR_OUT_MUX06_ADCAEVT4		 = 0x0C02,	//!OUT MUX06 ADCAEVT4
	XBAR_OUT_MUX07_CMPSS4_CTRIPOUTL		 = 0x0E00,	//!OUT MUX07 CMPSS4 CTRIPOUTL
	XBAR_OUT_MUX07_INPUTXBAR4		 = 0x0E01,	//!OUT MUX07 INPUTXBAR4
	XBAR_OUT_MUX07_CLB2_OUT5		 = 0x0E02,	//!OUT MUX07 CLB2 OUT5
	XBAR_OUT_MUX07_ADCCEVT4		 = 0x0E03,	//!OUT MUX07 ADCCEVT4
	XBAR_OUT_MUX08_ADCBEVT1		 = 0x1002,	//!OUT MUX08 ADCBEVT1
	XBAR_OUT_MUX09_INPUTXBAR5		 = 0x1201,	//!OUT MUX09 INPUTXBAR5
	XBAR_OUT_MUX09_ADCDEVT1		 = 0x1203,	//!OUT MUX09 ADCDEVT1
	XBAR_OUT_MUX10_ADCBEVT2		 = 0x1402,	//!OUT MUX10 ADCBEVT2
	XBAR_OUT_MUX11_INPUTXBAR6		 = 0x1601,	//!OUT MUX11 INPUTXBAR6
	XBAR_OUT_MUX11_ADCDEVT2		 = 0x1603,	//!OUT MUX11 ADCDEVT2
	XBAR_OUT_MUX12_ADCBEVT3		 = 0x1802,	//!OUT MUX12 ADCBEVT3
	XBAR_OUT_MUX13_ADCSOCA		 = 0x1A01,	//!OUT MUX13 ADCSOCA
	XBAR_OUT_MUX13_ADCDEVT3		 = 0x1A03,	//!OUT MUX13 ADCDEVT3
	XBAR_OUT_MUX14_ADCBEVT4		 = 0x1C02,	//!OUT MUX14 ADCBEVT4
	XBAR_OUT_MUX14_EXTSYNCOUT		 = 0x1C03,	//!OUT MUX14 EXTSYNCOUT
	XBAR_OUT_MUX15_ADCSOCB		 = 0x1E01,	//!OUT MUX15 ADCSOCB
	XBAR_OUT_MUX15_ADCDEVT4		 = 0x1E03,	//!OUT MUX15 ADCDEVT4
	XBAR_OUT_MUX16_ADCEEVT1		 = 0x2002,	//!OUT MUX16 ADCEEVT1
	XBAR_OUT_MUX17_CLAHALT		 = 0x2203,
	XBAR_OUT_MUX18_ADCEEVT2		 = 0x2402,	//!OUT MUX18 ADCEEVT2
	XBAR_OUT_MUX19_ERRSTS		 = 0x2603,	//!OUT MUX19 ERRSTS
	XBAR_OUT_MUX20_ADCEEVT3		 = 0x2802,	//!OUT MUX20 ADCEEVT3
	XBAR_OUT_MUX21_FSIA_RX_TRIG2		 = 0x2A03,	//!OUT MUX21 FSIA RX TRIG2
	XBAR_OUT_MUX22_ADCEEVT4		 = 0x2C02,	//!OUT MUX22 ADCEEVT4
	XBAR_OUT_MUX23_ADCA_EXTMUXSEL0		 = 0x2E01,	//!OUT MUX23 ADCA EXTMUXSEL0
	XBAR_OUT_MUX23_ADCC_EXTMUXSEL0		 = 0x2E02,	//!OUT MUX23 ADCC EXTMUXSEL0
	XBAR_OUT_MUX23_ADCE_EXTMUXSEL0		 = 0x2E03,	//!OUT MUX23 ADCE EXTMUXSEL0
	XBAR_OUT_MUX24_ADCA_EXTMUXSEL1		 = 0x3001,	//!OUT MUX24 ADCA EXTMUXSEL1
	XBAR_OUT_MUX24_ADCC_EXTMUXSEL1		 = 0x3002,	//!OUT MUX24 ADCC EXTMUXSEL1
	XBAR_OUT_MUX24_ADCE_EXTMUXSEL1		 = 0x3003,	//!OUT MUX24 ADCE EXTMUXSEL1
	XBAR_OUT_MUX25_ADCA_EXTMUXSEL2		 = 0x3201,	//!OUT MUX25 ADCA EXTMUXSEL2
	XBAR_OUT_MUX25_ADCC_EXTMUXSEL2		 = 0x3202,	//!OUT MUX25 ADCC EXTMUXSEL2
	XBAR_OUT_MUX25_ADCE_EXTMUXSEL2		 = 0x3203,	//!OUT MUX25 ADCE EXTMUXSEL2
	XBAR_OUT_MUX26_ADCA_EXTMUXSEL3		 = 0x3401,	//!OUT MUX26 ADCA EXTMUXSEL3
	XBAR_OUT_MUX26_ADCC_EXTMUXSEL3		 = 0x3402,	//!OUT MUX26 ADCC EXTMUXSEL3
	XBAR_OUT_MUX26_ADCE_EXTMUXSEL3		 = 0x3403,	//!OUT MUX26 ADCE EXTMUXSEL3
	XBAR_OUT_MUX27_ADCB_EXTMUXSEL0		 = 0x3601,	//!OUT MUX27 ADCB EXTMUXSEL0
	XBAR_OUT_MUX27_ADCD_EXTMUXSEL0		 = 0x3602,	//!OUT MUX27 ADCD EXTMUXSEL0
	XBAR_OUT_MUX28_ADCB_EXTMUXSEL1		 = 0x3801,	//!OUT MUX28 ADCB EXTMUXSEL1
	XBAR_OUT_MUX28_ADCD_EXTMUXSEL1		 = 0x3802,	//!OUT MUX28 ADCD EXTMUXSEL1
	XBAR_OUT_MUX29_ADCB_EXTMUXSEL2		 = 0x3A01,	//!OUT MUX29 ADCB EXTMUXSEL2
	XBAR_OUT_MUX29_ADCD_EXTMUXSEL2		 = 0x3A02,	//!OUT MUX29 ADCD EXTMUXSEL2
	XBAR_OUT_MUX30_ADCB_EXTMUXSEL3		 = 0x3C01,	//!OUT MUX30 ADCB EXTMUXSEL3
	XBAR_OUT_MUX30_ADCD_EXTMUXSEL3		 = 0x3C02,	//!OUT MUX30 ADCD EXTMUXSEL3
	XBAR_OUT_MUX30_EPG1_OUT0		 = 0x3C03,	//!OUT MUX30 EPG1 OUT0
	XBAR_OUT_MUX31_ERRSTS		 = 0x3E02,	//!OUT MUX31 ERRSTS
	XBAR_OUT_MUX31_EPG1_OUT1		 = 0x3E03,	//!OUT MUX31 EPG1 OUT1

	//
	//CLBOUTPUTXBAR
	//
	XBAR_OUT_MUX00_CLB1_OUT0		 = 0x0000,
	XBAR_OUT_MUX00_XTRIP_OUT1		 = 0x0003,
	XBAR_OUT_MUX01_CLB1_OUT1		 = 0x0200,
	XBAR_OUT_MUX01_XTRIP_OUT2		 = 0x0203,
	XBAR_OUT_MUX02_CLB1_OUT2		 = 0x0400,
	XBAR_OUT_MUX03_CLB1_OUT3		 = 0x0600,
	XBAR_OUT_MUX04_CLB1_OUT4		 = 0x0800,
	XBAR_OUT_MUX05_CLB1_OUT5		 = 0x0A00,
	XBAR_OUT_MUX06_CLB1_OUT6		 = 0x0C00,
	XBAR_OUT_MUX07_CLB1_OUT7		 = 0x0E00,
	XBAR_OUT_MUX08_CLB2_OUT0		 = 0x1000,
	XBAR_OUT_MUX08_XTRIP_OUT3		 = 0x1003,
	XBAR_OUT_MUX09_CLB2_OUT1		 = 0x1200,
	XBAR_OUT_MUX09_XTRIP_OUT4		 = 0x1203,
	XBAR_OUT_MUX10_CLB2_OUT2		 = 0x1400,
	XBAR_OUT_MUX11_CLB2_OUT3		 = 0x1600,
	XBAR_OUT_MUX12_CLB2_OUT4		 = 0x1800,
	XBAR_OUT_MUX13_CLB2_OUT5		 = 0x1A00,
	XBAR_OUT_MUX14_CLB2_OUT6		 = 0x1C00,
	XBAR_OUT_MUX15_CLB2_OUT7		 = 0x1E00,
	XBAR_OUT_MUX16_XTRIP_OUT5		 = 0x2003,
	XBAR_OUT_MUX17_XTRIP_OUT6		 = 0x2203,
	XBAR_OUT_MUX24_XTRIP_OUT7		 = 0x3003,
	XBAR_OUT_MUX25_XTRIP_OUT8		 = 0x3203,
	XBAR_OUT_MUX30_EPG1_OUT2		 = 0x3C03,
	XBAR_OUT_MUX31_EPG1_OUT3		 = 0x3E03
} XBAR_OutputMuxConfig;


//*****************************************************************************
//
//! The following values define the \e muxConfig parameter for
//! XBAR_setEPWMMuxConfig().
//
//*****************************************************************************
typedef enum
{
	XBAR_EPWM_MUX00_CMPSS1_CTRIPH		 = 0x0000,	//!EPWM MUX00 CMPSS1 CTRIPH
	XBAR_EPWM_MUX00_CMPSS1_CTRIPH_OR_L		 = 0x0001,	//!EPWM MUX00 CMPSS1 CTRIPH OR L
	XBAR_EPWM_MUX00_ADCAEVT1		 = 0x0002,	//!EPWM MUX00 ADCAEVT1
	XBAR_EPWM_MUX00_ECAP1_OUT		 = 0x0003,	//!EPWM MUX00 ECAP1 OUT
	XBAR_EPWM_MUX02_CMPSS2_CTRIPH		 = 0x0400,	//!EPWM MUX02 CMPSS2 CTRIPH
	XBAR_EPWM_MUX02_CMPSS2_CTRIPH_OR_L		 = 0x0401,	//!EPWM MUX02 CMPSS2 CTRIPH OR L
	XBAR_EPWM_MUX02_ADCAEVT2		 = 0x0402,	//!EPWM MUX02 ADCAEVT2
	XBAR_EPWM_MUX02_ECAP2_OUT		 = 0x0403,	//!EPWM MUX02 ECAP2 OUT
	XBAR_EPWM_MUX04_CMPSS3_CTRIPH		 = 0x0800,	//!EPWM MUX04 CMPSS3 CTRIPH
	XBAR_EPWM_MUX04_CMPSS3_CTRIPH_OR_L		 = 0x0801,	//!EPWM MUX04 CMPSS3 CTRIPH OR L
	XBAR_EPWM_MUX04_ADCAEVT3		 = 0x0802,	//!EPWM MUX04 ADCAEVT3
	XBAR_EPWM_MUX06_CMPSS4_CTRIPH		 = 0x0C00,	//!EPWM MUX06 CMPSS4 CTRIPH
	XBAR_EPWM_MUX06_CMPSS4_CTRIPH_OR_L		 = 0x0C01,	//!EPWM MUX06 CMPSS4 CTRIPH OR L
	XBAR_EPWM_MUX06_ADCAEVT4		 = 0x0C02,	//!EPWM MUX06 ADCAEVT4
	XBAR_EPWM_MUX08_ADCBEVT1		 = 0x1002,	//!EPWM MUX08 ADCBEVT1
	XBAR_EPWM_MUX10_ADCBEVT2		 = 0x1402,	//!EPWM MUX10 ADCBEVT2
	XBAR_EPWM_MUX12_ADCBEVT3		 = 0x1802,	//!EPWM MUX12 ADCBEVT3
	XBAR_EPWM_MUX14_ADCBEVT4		 = 0x1C02,	//!EPWM MUX14 ADCBEVT4
	XBAR_EPWM_MUX14_EXTSYNCOUT		 = 0x1C03,	//!EPWM MUX14 EXTSYNCOUT
	XBAR_EPWM_MUX16_ADCEEVT1		 = 0x2002,	//!EPWM MUX16 ADCEEVT1
	XBAR_EPWM_MUX18_ADCEEVT2		 = 0x2402,	//!EPWM MUX18 ADCEEVT2
	XBAR_EPWM_MUX20_ADCEEVT3		 = 0x2802,	//!EPWM MUX20 ADCEEVT3
	XBAR_EPWM_MUX20_FSIA_RX_TRIG1		 = 0x2803,	//!EPWM MUX20 FSIA RX TRIG1
	XBAR_EPWM_MUX22_ADCEEVT4		 = 0x2C02,	//!EPWM MUX22 ADCEEVT4
	XBAR_EPWM_MUX01_CMPSS1_CTRIPL		 = 0x0200,	//!EPWM MUX01 CMPSS1 CTRIPL
	XBAR_EPWM_MUX01_INPUTXBAR1_INPUT1		 = 0x0201,	//!EPWM MUX01 INPUTXBAR1 INPUT1
	XBAR_EPWM_MUX01_CLB1_OUT4		 = 0x0202,	//!EPWM MUX01 CLB1 OUT4
	XBAR_EPWM_MUX01_ADCCEVT1		 = 0x0203,	//!EPWM MUX01 ADCCEVT1
	XBAR_EPWM_MUX03_CMPSS2_CTRIPL		 = 0x0600,	//!EPWM MUX03 CMPSS2 CTRIPL
	XBAR_EPWM_MUX03_INPUTXBAR1_INPUT2		 = 0x0601,	//!EPWM MUX03 INPUTXBAR1 INPUT2
	XBAR_EPWM_MUX03_CLB1_OUT5		 = 0x0602,	//!EPWM MUX03 CLB1 OUT5
	XBAR_EPWM_MUX03_ADCCEVT2		 = 0x0603,	//!EPWM MUX03 ADCCEVT2
	XBAR_EPWM_MUX05_CMPSS3_CTRIPL		 = 0x0A00,	//!EPWM MUX05 CMPSS3 CTRIPL
	XBAR_EPWM_MUX05_INPUTXBAR1_INPUT3		 = 0x0A01,	//!EPWM MUX05 INPUTXBAR1 INPUT3
	XBAR_EPWM_MUX05_CLB2_OUT4		 = 0x0A02,	//!EPWM MUX05 CLB2 OUT4
	XBAR_EPWM_MUX05_ADCCEVT3		 = 0x0A03,	//!EPWM MUX05 ADCCEVT3
	XBAR_EPWM_MUX07_CMPSS4_CTRIPL		 = 0x0E00,	//!EPWM MUX07 CMPSS4 CTRIPL
	XBAR_EPWM_MUX07_INPUTXBAR1_INPUT4		 = 0x0E01,	//!EPWM MUX07 INPUTXBAR1 INPUT4
	XBAR_EPWM_MUX07_CLB2_OUT5		 = 0x0E02,	//!EPWM MUX07 CLB2 OUT5
	XBAR_EPWM_MUX07_ADCCEVT4		 = 0x0E03,	//!EPWM MUX07 ADCCEVT4
	XBAR_EPWM_MUX23_INPUTXBAR1_INPUT10		 = 0x2E01,	//!EPWM MUX23 INPUTXBAR1 INPUT10
	XBAR_EPWM_MUX23_INPUTXBAR2_INPUT10		 = 0x2E02,	//!EPWM MUX23 INPUTXBAR2 INPUT10
	XBAR_EPWM_MUX17_INPUTXBAR1_INPUT7		 = 0x2201,	//!EPWM MUX17 INPUTXBAR1 INPUT7
	XBAR_EPWM_MUX17_INPUTXBAR2_INPUT7		 = 0x2202,	//!EPWM MUX17 INPUTXBAR2 INPUT7
	XBAR_EPWM_MUX17_CLAHALT		 = 0x2203,	//!EPWM MUX17 CLAHALT
	XBAR_EPWM_MUX19_INPUTXBAR1_INPUT8		 = 0x2601,	//!EPWM MUX19 INPUTXBAR1 INPUT8
	XBAR_EPWM_MUX19_INPUTXBAR2_INPUT8		 = 0x2602,	//!EPWM MUX19 INPUTXBAR2 INPUT8
	XBAR_EPWM_MUX19_ERRORSTS		 = 0x2603,	//!EPWM MUX19 ERRORSTS
	XBAR_EPWM_MUX21_INPUTXBAR1_INPUT9		 = 0x2A01,	//!EPWM MUX21 INPUTXBAR1 INPUT9
	XBAR_EPWM_MUX21_INPUTXBAR2_INPUT9		 = 0x2A02,	//!EPWM MUX21 INPUTXBAR2 INPUT9
	XBAR_EPWM_MUX31_INPUTXBAR1_INPUT14		 = 0x3E01,	//!EPWM MUX31 INPUTXBAR1 INPUT14
	XBAR_EPWM_MUX31_ERRORSTS		 = 0x3E02,	//!EPWM MUX31 ERRORSTS
	XBAR_EPWM_MUX31_INPUTXBAR2_INPUT14		 = 0x3E03,	//!EPWM MUX31 INPUTXBAR2 INPUT14
	XBAR_EPWM_MUX25_INPUTXBAR1_INPUT11		 = 0x3201,	//!EPWM MUX25 INPUTXBAR1 INPUT11
	XBAR_EPWM_MUX25_MCANA_FEVT0		 = 0x3202,	//!EPWM MUX25 MCANA FEVT0
	XBAR_EPWM_MUX25_INPUTXBAR2_INPUT11		 = 0x3203,	//!EPWM MUX25 INPUTXBAR2 INPUT11
	XBAR_EPWM_MUX27_INPUTXBAR1_INPUT12		 = 0x3601,	//!EPWM MUX27 INPUTXBAR1 INPUT12
	XBAR_EPWM_MUX27_MCANA_FEVT1		 = 0x3602,	//!EPWM MUX27 MCANA FEVT1
	XBAR_EPWM_MUX27_INPUTXBAR2_INPUT12		 = 0x3603,	//!EPWM MUX27 INPUTXBAR2 INPUT12
	XBAR_EPWM_MUX29_INPUTXBAR1_INPUT13		 = 0x3A01,	//!EPWM MUX29 INPUTXBAR1 INPUT13
	XBAR_EPWM_MUX29_MCANA_FEVT2		 = 0x3A02,	//!EPWM MUX29 MCANA FEVT2
	XBAR_EPWM_MUX29_INPUTXBAR2_INPUT13		 = 0x3A03,	//!EPWM MUX29 INPUTXBAR2 INPUT13
	XBAR_EPWM_MUX09_INPUTXBAR1_INPUT5		 = 0x1201,	//!EPWM MUX09 INPUTXBAR1 INPUT5
	XBAR_EPWM_MUX09_ADCDEVT1		 = 0x1203,	//!EPWM MUX09 ADCDEVT1
	XBAR_EPWM_MUX11_INPUTXBAR1_INPUT6		 = 0x1601,	//!EPWM MUX11 INPUTXBAR1 INPUT6
	XBAR_EPWM_MUX11_ADCDEVT2		 = 0x1603,	//!EPWM MUX11 ADCDEVT2
	XBAR_EPWM_MUX13_ADCSOCA		 = 0x1A01,	//!EPWM MUX13 ADCSOCA
	XBAR_EPWM_MUX13_ADCDEVT3		 = 0x1A03,	//!EPWM MUX13 ADCDEVT3
	XBAR_EPWM_MUX15_ADCSOCB		 = 0x1E01,	//!EPWM MUX15 ADCSOCB
	XBAR_EPWM_MUX15_ADCDEVT4		 = 0x1E03,	//!EPWM MUX15 ADCDEVT4
	XBAR_EPWM_MUX26_MCANB_FEVT0		 = 0x3403,	//!EPWM MUX26 MCANB FEVT0
	XBAR_EPWM_MUX28_MCANB_FEVT1		 = 0x3803,	//!EPWM MUX28 MCANB FEVT1
	XBAR_EPWM_MUX30_MCANB_FEVT2		 = 0x3C03	//!EPWM MUX30 MCANB FEVT2
} XBAR_EPWMMuxConfig;


//*****************************************************************************
//
// The following values define the muxConfig parameter for
// XBAR_setCLBMuxConfig().
//
//*****************************************************************************
typedef enum
{
	XBAR_CLB_MUX00_CMPSS1_CTRIPH		 = 0x0000,	//!CLB MUX00 CMPSS1 CTRIPH
	XBAR_CLB_MUX00_CMPSS1_CTRIPH_OR_L		 = 0x0001,	//!CLB MUX00 CMPSS1 CTRIPH OR L
	XBAR_CLB_MUX00_ADCAEVT1		 = 0x0002,	//!CLB MUX00 ADCAEVT1
	XBAR_CLB_MUX00_ECAP1_OUT		 = 0x0003,	//!CLB MUX00 ECAP1 OUT
	XBAR_CLB_MUX01_CMPSS1_CTRIPL		 = 0x0200,	//!CLB MUX01 CMPSS1 CTRIPL
	XBAR_CLB_MUX01_INPUTXBAR1_INPUT1		 = 0x0201,	//!CLB MUX01 INPUTXBAR1 INPUT1
	XBAR_CLB_MUX01_CLB1_OUT4		 = 0x0202,	//!CLB MUX01 CLB1 OUT4
	XBAR_CLB_MUX01_ADCCEVT1		 = 0x0203,	//!CLB MUX01 ADCCEVT1
	XBAR_CLB_MUX02_CMPSS2_CTRIPH		 = 0x0400,	//!CLB MUX02 CMPSS2 CTRIPH
	XBAR_CLB_MUX02_CMPSS2_CTRIPH_OR_L		 = 0x0401,	//!CLB MUX02 CMPSS2 CTRIPH OR L
	XBAR_CLB_MUX02_ADCAEVT2		 = 0x0402,	//!CLB MUX02 ADCAEVT2
	XBAR_CLB_MUX02_ECAP2_OUT		 = 0x0403,	//!CLB MUX02 ECAP2 OUT
	XBAR_CLB_MUX03_CMPSS2_CTRIPL		 = 0x0600,	//!CLB MUX03 CMPSS2 CTRIPL
	XBAR_CLB_MUX03_INPUTXBAR1_INPUT2		 = 0x0601,	//!CLB MUX03 INPUTXBAR1 INPUT2
	XBAR_CLB_MUX03_CLB1_OUT5		 = 0x0602,	//!CLB MUX03 CLB1 OUT5
	XBAR_CLB_MUX03_ADCCEVT2		 = 0x0603,	//!CLB MUX03 ADCCEVT2
	XBAR_CLB_MUX04_CMPSS3_CTRIPH		 = 0x0800,	//!CLB MUX04 CMPSS3 CTRIPH
	XBAR_CLB_MUX04_CMPSS3_CTRIPH_OR_L		 = 0x0801,	//!CLB MUX04 CMPSS3 CTRIPH OR L
	XBAR_CLB_MUX04_ADCAEVT3		 = 0x0802,	//!CLB MUX04 ADCAEVT3
	XBAR_CLB_MUX05_CMPSS3_CTRIPL		 = 0x0A00,	//!CLB MUX05 CMPSS3 CTRIPL
	XBAR_CLB_MUX05_INPUTXBAR1_INPUT3		 = 0x0A01,	//!CLB MUX05 INPUTXBAR1 INPUT3
	XBAR_CLB_MUX05_CLB2_OUT4		 = 0x0A02,	//!CLB MUX05 CLB2 OUT4
	XBAR_CLB_MUX05_ADCCEVT3		 = 0x0A03,	//!CLB MUX05 ADCCEVT3
	XBAR_CLB_MUX06_CMPSS4_CTRIPH		 = 0x0C00,	//!CLB MUX06 CMPSS4 CTRIPH
	XBAR_CLB_MUX06_CMPSS4_CTRIPH_OR_L		 = 0x0C01,	//!CLB MUX06 CMPSS4 CTRIPH OR L
	XBAR_CLB_MUX06_ADCAEVT4		 = 0x0C02,	//!CLB MUX06 ADCAEVT4
	XBAR_CLB_MUX07_CMPSS4_CTRIPL		 = 0x0E00,	//!CLB MUX07 CMPSS4 CTRIPL
	XBAR_CLB_MUX07_INPUTXBAR1_INPUT4		 = 0x0E01,	//!CLB MUX07 INPUTXBAR1 INPUT4
	XBAR_CLB_MUX07_CLB2_OUT5		 = 0x0E02,	//!CLB MUX07 CLB2 OUT5
	XBAR_CLB_MUX07_ADCCEVT4		 = 0x0E03,	//!CLB MUX07 ADCCEVT4
	XBAR_CLB_MUX08_ADCBEVT1		 = 0x1002,	//!CLB MUX08 ADCBEVT1
	XBAR_CLB_MUX09_INPUTXBAR1_INPUT5		 = 0x1201,	//!CLB MUX09 INPUTXBAR1 INPUT5
	XBAR_CLB_MUX09_ADCDEVT1		 = 0x1203,	//!CLB MUX09 ADCDEVT1
	XBAR_CLB_MUX10_ADCBEVT2		 = 0x1402,	//!CLB MUX10 ADCBEVT2
	XBAR_CLB_MUX11_INPUTXBAR1_INPUT6		 = 0x1601,	//!CLB MUX11 INPUTXBAR1 INPUT6
	XBAR_CLB_MUX11_ADCDEVT2		 = 0x1603,	//!CLB MUX11 ADCDEVT2
	XBAR_CLB_MUX12_ADCBEVT3		 = 0x1802,	//!CLB MUX12 ADCBEVT3
	XBAR_CLB_MUX13_ADCSOCA		 = 0x1A01,	//!CLB MUX13 ADCSOCA
	XBAR_CLB_MUX13_ADCDEVT3		 = 0x1A03,	//!CLB MUX13 ADCDEVT3
	XBAR_CLB_MUX14_ADCBEVT4		 = 0x1C02,	//!CLB MUX14 ADCBEVT4
	XBAR_CLB_MUX14_EXTSYNCOUT		 = 0x1C03,	//!CLB MUX14 EXTSYNCOUT
	XBAR_CLB_MUX15_ADCSOCB		 = 0x1E01,	//!CLB MUX15 ADCSOCB
	XBAR_CLB_MUX15_ADCDEVT4		 = 0x1E03,	//!CLB MUX15 ADCDEVT4
	XBAR_CLB_MUX16_FSIA_RX_TRIG2		 = 0x2002,	//!CLB MUX16 FSIA RX TRIG2
	XBAR_CLB_MUX16_FSIA_RX_TRIG3		 = 0x2003,	//!CLB MUX16 FSIA RX TRIG3
	XBAR_CLB_MUX17_INPUTXBAR1_INPUT7		 = 0x2201,	//!CLB MUX17 INPUTXBAR1 INPUT7
	XBAR_CLB_MUX17_ADCEEVT1		 = 0x2202,	//!CLB MUX17 ADCEEVT1
	XBAR_CLB_MUX17_CLAHALT		 = 0x2203,	//!CLB MUX17 CLAHALT
	XBAR_CLB_MUX19_INPUTXBAR1_INPUT8		 = 0x2601,	//!CLB MUX19 INPUTXBAR1 INPUT8
	XBAR_CLB_MUX19_ADCEEVT2		 = 0x2602,	//!CLB MUX19 ADCEEVT2
	XBAR_CLB_MUX19_ERRORSTS		 = 0x2603,	//!CLB MUX19 ERRORSTS
	XBAR_CLB_MUX21_INPUTXBAR1_INPUT9		 = 0x2A01,	//!CLB MUX21 INPUTXBAR1 INPUT9
	XBAR_CLB_MUX21_ADCEEVT3		 = 0x2A02,	//!CLB MUX21 ADCEEVT3
	XBAR_CLB_MUX23_INPUTXBAR1_INPUT10		 = 0x2E01,	//!CLB MUX23 INPUTXBAR1 INPUT10
	XBAR_CLB_MUX23_ADCEEVT4		 = 0x2E02,	//!CLB MUX23 ADCEEVT4
	XBAR_CLB_MUX24_CPU1_ERADEVT8		 = 0x3002,	//!CLB MUX24 CPU1 ERADEVT8
	XBAR_CLB_MUX25_INPUTXBAR1_INPUT11		 = 0x3201,	//!CLB MUX25 INPUTXBAR1 INPUT11
	XBAR_CLB_MUX25_MCANA_FEVT0		 = 0x3202,	//!CLB MUX25 MCANA FEVT0
	XBAR_CLB_MUX26_CPU1_ERADEVT9		 = 0x3402,	//!CLB MUX26 CPU1 ERADEVT9
	XBAR_CLB_MUX26_MCANB_FEVT0		 = 0x3403,	//!CLB MUX26 MCANB FEVT0
	XBAR_CLB_MUX27_INPUTXBAR1_INPUT12		 = 0x3601,	//!CLB MUX27 INPUTXBAR1 INPUT12
	XBAR_CLB_MUX27_MCANA_FEVT1		 = 0x3602,	//!CLB MUX27 MCANA FEVT1
	XBAR_CLB_MUX28_CPU1_ERADEVT10		 = 0x3802,	//!CLB MUX28 CPU1 ERADEVT10
	XBAR_CLB_MUX28_MCANB_FEVT1		 = 0x3803,	//!CLB MUX28 MCANB FEVT1
	XBAR_CLB_MUX29_INPUTXBAR1_INPUT13		 = 0x3A01,	//!CLB MUX29 INPUTXBAR1 INPUT13
	XBAR_CLB_MUX29_MCANA_FEVT2		 = 0x3A02,	//!CLB MUX29 MCANA FEVT2
	XBAR_CLB_MUX30_CPU1_ERADEVT11		 = 0x3C02,	//!CLB MUX30 CPU1 ERADEVT11
	XBAR_CLB_MUX30_MCANB_FEVT2		 = 0x3C03,	//!CLB MUX30 MCANB FEVT2
	XBAR_CLB_MUX31_INPUTXBAR1_INPUT14		 = 0x3E01,	//!CLB MUX31 INPUTXBAR1 INPUT14
	XBAR_CLB_MUX31_ERRORSTS		 = 0x3E02	//!CLB MUX31 ERRORSTS
} XBAR_CLBMuxConfig;



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
    XBAR_INPUT_FLG_CMPSS1_CTRIPOUTL = 0x0010,
    XBAR_INPUT_FLG_CMPSS1_CTRIPOUTH = 0x0011,
    XBAR_INPUT_FLG_CMPSS2_CTRIPOUTL = 0x0012,
    XBAR_INPUT_FLG_CMPSS2_CTRIPOUTH = 0x0013,
    XBAR_INPUT_FLG_CMPSS3_CTRIPOUTL = 0x0014,
    XBAR_INPUT_FLG_CMPSS3_CTRIPOUTH = 0x0015,
    XBAR_INPUT_FLG_CMPSS4_CTRIPOUTL = 0x0016,
    XBAR_INPUT_FLG_CMPSS4_CTRIPOUTH = 0x0017,
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
    XBAR_INPUT_FLG_ADCDEVT1         = 0x0203,
    XBAR_INPUT_FLG_ADCDEVT2         = 0x0204,
    XBAR_INPUT_FLG_ADCDEVT3         = 0x0205,
    XBAR_INPUT_FLG_ADCDEVT4         = 0x0206,
    XBAR_INPUT_FLG_ADCEEVT1         = 0x020F,
    XBAR_INPUT_FLG_ADCEEVT2         = 0x0210,
    XBAR_INPUT_FLG_ADCEEVT3         = 0x0211,
    XBAR_INPUT_FLG_ADCEEVT4         = 0x0212,
    //
    // XBARFLG4
    //
    XBAR_INPUT_FLG_MCANA_FEVT0      = 0x0309,
    XBAR_INPUT_FLG_MCANA_FEVT1      = 0x030A,
    XBAR_INPUT_FLG_MCANA_FEVT2      = 0x030B,
    XBAR_INPUT_FLG_MCANB_FEVT0      = 0x030C,
    XBAR_INPUT_FLG_MCANB_FEVT1      = 0x030D,
    XBAR_INPUT_FLG_MCANB_FEVT2      = 0x030E,
    XBAR_INPUT_FLG_CLB1_OUT4        = 0x0310,
    XBAR_INPUT_FLG_CLB1_OUT5        = 0x0311,
    XBAR_INPUT_FLG_CLB2_OUT4        = 0x0312,
    XBAR_INPUT_FLG_CLB2_OUT5        = 0x0313,
    XBAR_INPUT_FLG_ERRORSTS_ERROR   = 0x031C,
    XBAR_INPUT_FLG_CLAHALT          = 0x031F,
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
XBAR_enableOutputMux(uint32_t base, XBAR_OutputNum output, uint32_t muxes)
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

    HWREG(base + XBAR_O_OUTPUT1MUXENABLE + outputNum) |= muxes;

    EDIS;


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
XBAR_disableOutputMux(uint32_t base, XBAR_OutputNum output, uint32_t muxes)
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

    HWREG(base + XBAR_O_OUTPUT1MUXENABLE + outputNum) &= ~(muxes);

    EDIS;
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
        HWREGH(base + XBAR_O_OUTPUTLATCHENABLE) |=
               0x1U << ((uint16_t)output / 2U);
    }
    else
    {
        HWREGH(base + XBAR_O_OUTPUTLATCHENABLE) &=
               ~(0x1U << ((uint16_t)output / 2U));
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
    return((HWREGH(base + XBAR_O_OUTPUTLATCH) &
            (0x1U << ((uint16_t)output / 2U))) != 0U);
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
        HWREGH(base + XBAR_O_OUTPUTLATCHCLR) |=
        0x1U << ((uint16_t)output / 2U);
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
    HWREGH(base + XBAR_O_OUTPUTLATCHFRC) =
        (uint16_t)0x1U << ((uint16_t)output / 2U);
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
        HWREGH(base + XBAR_O_OUTPUTINV) |=
            0x1U << ((uint16_t)output / 2U);
    }
    else
    {
        HWREGH(base + XBAR_O_OUTPUTINV) &=
            ~(0x1U << ((uint16_t)output / 2U));
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
XBAR_enableEPWMMux(XBAR_TripNum trip, uint32_t muxes)
{
    //
    // Set the enable bit.
    //
    EALLOW;

    HWREG(XBAR_EPWM_EN_REG_BASE + (uint32_t)trip) |= muxes;
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
XBAR_disableEPWMMux(XBAR_TripNum trip, uint32_t muxes)
{
    //
    // Clear the enable bit.
    //
    EALLOW;

    HWREG(XBAR_EPWM_EN_REG_BASE + (uint32_t)trip) &= ~(muxes);

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
    //
    // Set or clear the polarity setting bit based on the invert parameter.
    //
    EALLOW;

    if(invert)
    {
        HWREGH(EPWMXBAR_BASE + XBAR_O_TRIPOUTINV) |=
            0x1U << ((uint16_t)trip / 2U);
    }
    else
    {
        HWREGH(EPWMXBAR_BASE + XBAR_O_TRIPOUTINV) &=
            ~(0x1U << ((uint16_t)trip / 2U));
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
//! Locks an input to the Input X-BAR.
//!
//! \param base specifies the X-BAR base address.
//! \param input is an input to the Input X-BAR.
//!
//! This function locks the specific input on the Input X-BAR.
//!
//! The \e base parameter can take base addresses
//! INPUTXBAR_BASE
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
//! \return None.
//
//*****************************************************************************
static inline void
XBAR_lockEPWM(void)
{
    //
    // Lock the ePWM X-BAR with the TRIPLOCK register.
    // Write key 0x5A5A to the KEY bits and 1 to LOCK bit.
    //
    EALLOW;

    HWREG(EPWMXBAR_BASE + XBAR_O_TRIPLOCK) =
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
