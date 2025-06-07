//###########################################################################
//
// FILE:   f280013x_epwm_defines.h
//
// TITLE:  #defines used in EPwm examples
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

#ifndef F280013x_EPWM_DEFINES_H
#define F280013x_EPWM_DEFINES_H

#ifdef __cplusplus
extern "C" {
#endif

//
// Defines
//

//
// TBCTL (Time-Base Control) Register
//

//
// CTRMODE bits
//
#define TB_COUNT_UP      0x0
#define TB_COUNT_DOWN    0x1
#define TB_COUNT_UPDOWN  0x2
#define TB_FREEZE        0x3

//
// PHSEN bit
//
#define TB_DISABLE  0x0
#define TB_ENABLE   0x1

//
// PRDLD bit
//
#define TB_SHADOW     0x0
#define TB_IMMEDIATE  0x1

//
// HSPCLKDIV and CLKDIV bits
//
#define TB_DIV1   0x0
#define TB_DIV2   0x1
#define TB_DIV4   0x2

//
// HSPCLKDIV bits 
//
#define TB_HSDIV1  0x0
#define TB_HSDIV2  0x1
#define TB_HSDIV4  0x2
#define TB_HSDIV6  0x3
#define TB_HSDIV8  0x4
#define TB_HSDIV10  0x5
#define TB_HSDIV12  0x6
#define TB_HSDIV14  0x7

//
// CLKDIV bits
//
#define TB_CLOCK_DIV1   0x0
#define TB_CLOCK_DIV2   0x1
#define TB_CLOCK_DIV4   0x2
#define TB_CLOCK_DIV8   0x3
#define TB_CLOCK_DIV16  0x4
#define TB_CLOCK_DIV32  0x5
#define TB_CLOCK_DIV64  0x6
#define TB_CLOCK_DIV128 0x7

//
// PHSDIR bit
//
#define TB_DOWN   0x0
#define TB_UP     0x1

//
// EPWMSYNINSEL (EPWMxSYNCIN Source Select) Register
//

//
// SEL bits
//
#define SYNC_IN_SRC_DISABLE_ALL      0x0
#define SYNC_IN_SRC_SYNCOUT_EPWM1    0x1
#define SYNC_IN_SRC_SYNCOUT_EPWM2    0x2
#define SYNC_IN_SRC_SYNCOUT_EPWM3    0x3
#define SYNC_IN_SRC_SYNCOUT_EPWM4    0x4
#define SYNC_IN_SRC_SYNCOUT_EPWM5    0x5
#define SYNC_IN_SRC_SYNCOUT_EPWM6    0x6
#define SYNC_IN_SRC_SYNCOUT_EPWM7    0x7
#define SYNC_IN_SRC_SYNCOUT_EPWM11   0xB
#define SYNC_IN_SRC_SYNCOUT_EPWM12   0xC
#define SYNC_IN_SRC_SYNCOUT_EPWM13   0xD
#define SYNC_IN_SRC_SYNCOUT_EPWM14   0xE
#define SYNC_IN_SRC_SYNCOUT_EPWM15   0xF
#define SYNC_IN_SRC_SYNCOUT_EPWM16   0x10
#define SYNC_IN_SRC_SYNCOUT_ECAP1    0x11
#define SYNC_IN_SRC_SYNCOUT_ECAP2    0x12
#define SYNC_IN_SRC_SYNCOUT_ECAP3    0x13
#define SYNC_IN_SRC_INPUTXBAR_OUT5   0x18
#define SYNC_IN_SRC_INPUTXBAR_OUT6   0x19

//
// EPWMSYNOUTEN (EPWMxSYNCOUT Source Enable) Register
//

#define SYNC_OUT_SRC_DISABLE_ALL     0x0
#define SYNC_OUT_SRC_ENABLE_ALL      0x7F

//
// SWEN, ZEROEN, CMPBEN, CMPCEN, CMPCEN, DCAEVT1EN & DCBEVT1EN  bits
//
#define SYNC_OUT_SRC_ENABLE       0x1
#define SYNC_OUT_SRC_DISABLE      0x0

//
// CMPCTL (Compare Control) Register
//

//
// LOADAMODE and LOADBMODE bits
//
#define CC_CTR_ZERO      0x0
#define CC_CTR_PRD       0x1
#define CC_CTR_ZERO_PRD  0x2
#define CC_LD_DISABLE    0x3

//
// SHDWAMODE and SHDWBMODE bits
//
#define CC_SHADOW     0x0
#define CC_IMMEDIATE  0x1

//
// AQCTLA and AQCTLB (Action Qualifier Control)
//

//
// ZRO, PRD, CAU, CAD, CBU, CBD bits
//
#define AQ_NO_ACTION  0x0
#define AQ_CLEAR      0x1
#define AQ_SET        0x2
#define AQ_TOGGLE     0x3

//
// DBCTL (Dead-Band Control) Register
//

//
// OUT MODE bits
//
#define DB_DISABLE      0x0
#define DBB_ENABLE      0x1
#define DBA_ENABLE      0x2
#define DB_FULL_ENABLE  0x3

//
// POLSEL bits
//
#define DB_ACTV_HI   0x0
#define DB_ACTV_LOC  0x1
#define DB_ACTV_HIC  0x2
#define DB_ACTV_LO   0x3

//
// IN MODE bits
//
#define DBA_ALL          0x0
#define DBB_RED_DBA_FED  0x1
#define DBA_RED_DBB_FED  0x2
#define DBB_ALL          0x3

//
// PCCTL (PWM chopper control) Register
//

//
// CHPEN bit
//
#define CHP_DISABLE  0x0
#define CHP_ENABLE   0x1

//
// CHPFREQ bits
//
#define CHP_DIV1  0x0
#define CHP_DIV2  0x1
#define CHP_DIV3  0x2
#define CHP_DIV4  0x3
#define CHP_DIV5  0x4
#define CHP_DIV6  0x5
#define CHP_DIV7  0x6
#define CHP_DIV8  0x7

//
// CHPDUTY bits
//
#define CHP1_8TH  0x0
#define CHP2_8TH  0x1
#define CHP3_8TH  0x2
#define CHP4_8TH  0x3
#define CHP5_8TH  0x4
#define CHP6_8TH  0x5
#define CHP7_8TH  0x6

//
// TZSEL (Trip Zone Select) Register
//

//
// CBCn and OSHTn bits
//
#define TZ_DISABLE  0x0
#define TZ_ENABLE   0x1

//
// TZCTL (Trip Zone Control) Register
//

//
// TZA and TZB bits
//
#define TZ_HIZ       0x0
#define TZ_FORCE_HI  0x1
#define TZ_FORCE_LO  0x2
#define TZ_NO_CHANGE 0x3

//
// TZDCSEL (Trip Zone Digital Compare) Register
//

//
// DCAEVT1, DCAEVT2, DCBEVT1, DCBEVT2 bits
//
#define TZ_EVT_DISABLE      0x0
#define TZ_DCAH_LOW         0x1
#define TZ_DCAH_HI          0x2
#define TZ_DCAL_LOW         0x3
#define TZ_DCAL_HI          0x4
#define TZ_DCAL_HI_DCAH_LOW 0x5

#define TZ_DCBH_LOW         0x1
#define TZ_DCBH_HI          0x2
#define TZ_DCBL_LOW         0x3
#define TZ_DCBL_HI          0x4
#define TZ_DCBL_HI_DCBH_LOW 0x5

//
// ETSEL (Event Trigger Select) Register
//

//
// INTSEL bits
//
#define ET_DCAEVT1SOC   0x0
#define ET_CTR_ZERO     0x1
#define ET_CTR_PRD      0x2
#define ET_CTR_PRDZERO  0x3
#define ET_CTRU_CMPA    0x4
#define ET_CTRD_CMPA    0x5
#define ET_CTRU_CMPB    0x6
#define ET_CTRD_CMPB    0x7

//
// ETPS (Event Trigger Pre-scale) Register
//

//
// INTPRD, SOCAPRD, SOCBPRD bits
//
#define ET_DISABLE  0x0
#define ET_1ST      0x1
#define ET_2ND      0x2
#define ET_3RD      0x3

//
// HRPWM (High Resolution PWM)
//

//
// HRCNFG Register
//

//
// EDGEMODE, EDGEMODEB bits
//
#define HR_DISABLE        0x0
#define HR_REP            0x1
#define HR_FEP            0x2
#define HR_BEP            0x3

//
// CTLMODE, CTLMODEB bits
//
#define HR_CMP            0x0
#define HR_PHS            0x1

//
// HRLOAD, HRLOADB bits
//
#define HR_CTR_ZERO       0x0
#define HR_CTR_PRD        0x1
#define HR_CTR_ZERO_PRD   0x2

//
// SELOUTB bit
//
#define HR_NORM_B         0x0
#define HR_INVERT_B       0x1

//
// SWAPAB bit
//
#define HR_NORM_AB        0x0
#define HR_SWAP_AB        0x1

//
// DC (Digital Compare)
//

//
// DCTRIPSEL Register
//
#define DC_TZ1           0x0
#define DC_TZ2           0x1
#define DC_TZ3           0x2
#define DC_TRIPIN1       0x0
#define DC_TRIPIN2       0x1
#define DC_TRIPIN3       0x2
#define DC_TRIPIN4       0x3
#define DC_TRIPIN5       0x4
#define DC_TRIPIN6       0x5
#define DC_TRIPIN7       0x6
#define DC_TRIPIN8       0x7
#define DC_TRIPIN9       0x8
#define DC_TRIPIN10      0x9
#define DC_TRIPIN11      0xA
#define DC_TRIPIN12      0xB
//      Reserved         0xC
#define DC_TRIPIN14      0xD
#define DC_TRIPIN15      0xE
#define DC_COMBINATION   0xF

//
// DCFCTL Register
//

//
// SRCSEL bits
//
#define DC_SRC_DCAEVT1   0x0
#define DC_SRC_DCAEVT2   0x1
#define DC_SRC_DCBEVT1   0x2
#define DC_SRC_DCBEVT2   0x3

//
// PULSESEL bits
//
#define DC_PULSESEL_PRD      0x0
#define DC_PULSESEL_ZERO     0x1
#define DC_PULSESEL_ZERO_PRD 0x2

//
// BLANKE bit
//
#define DC_BLANK_DISABLE 0x0
#define DC_BLANK_ENABLE  0x1

//
// BLANKINV bit
//
#define DC_BLANK_NOTINV  0x0
#define DC_BLANK_INV     0x1

//
// DCACTL/DCBCTL Register
//

//
// EVT1SRCSEL, EVT2SRCSEL bits
//
#define DC_EVT1          0x0
#define DC_EVT2          0x0
#define DC_EVT_FLT       0x1

//
// EVT1SYNCE bit
//
#define DC_EVT_SYNC      0x0
#define DC_EVT_ASYNC     0x1

//
// EVT1SOCE bit
//
#define DC_SOC_DISABLE   0x0
#define DC_SOC_ENABLE    0x1

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of F280013x_EPWM_DEFINES_H

//
// End of file
//
