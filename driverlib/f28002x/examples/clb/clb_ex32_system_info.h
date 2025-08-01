//#############################################################################
//
// FILE:   clb_ex32_system_info.h
//
// TITLE:  User configurable system settings.
//
//#############################################################################
// $TI Release: F28004x Support Library v6.00.00.00 $
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
//#############################################################################

#ifndef CLB_EX32_SYSTEM_INFO_H_
#define CLB_EX32_SYSTEM_INFO_H_

#include <clb_ex32_lp5891.h>
#include <stdint.h>

// The LP5891 EVM is independent mode
#define TOTAL_SCAN_LINES       16
#define CASCADED_UNITS         1
#define MAX_DATA_LENGTH        3 * CASCADED_UNITS + 1

// Desired SCLK frequency
// Note: Exact frequency may not be possible
#define SPICLK_FREQ_IN_HZ      5000000

#define FALSE 0
#define TRUE  1

#define _FC0_2 ((FREQ_MUL__14) >> 32) & 0xFFFF
#define _FC0_1 ((FREQ_MUL__14 | FREQ_MOD__LF | SUBP_NUM__128 | SCAN_NUM__16) >> 16) & 0xFFFF
#define _FC0_0 ((LODRM_EN_0 | PSP_MOD_0 | PS_EN_0 | PDC_EN_1 | CHIP_NUM__1)) & 0xFFFF

#define _FC1_2 ((BLK_ADJ_0 | LINE_SWT__45 | LG_ENH_B_2 | LG_ENH_G_15) >> 32) & 0xFFFF
#define _FC1_1 ((LG_ENH_G_15 | LG_ENH_R_1 | LG_STEP_B__6 | LG_STEP_G__6) >> 16) & 0xFFFF
#define _FC1_0 ((LG_STEP_G__6 | LG_STEP_R__6 | SEG_LENGTH__512)) & 0xFFFF

#define _FC2_2 ((MPSM_EN_0 | MOD_SIZE_0 | SUBP_MAX_256_0 | CH_B_IMMUNITY_0 | CH_G_IMMUNITY_0 | CH_R_IMMUNITY_0 | LG_COLOR_B__14) >> 32) & 0xFFFF
#define _FC2_1 ((LG_COLOR_G__14 | LG_COLOR_R__1 | DE_COUPLE1_B__4 | DE_COUPLE1_G__4) >> 16) & 0xFFFF
#define _FC2_0 ((DE_COUPLE1_R__1 | V_PDC_B__0V1 | V_PDC_G__0V1 | V_PDC_R__0V1)) & 0xFFFF

#define _FC3_2 ((LSDVTH_B__0V2 | LSDVTH_G__0V2 | LSDVTH_R__0V2 | LSD_RM__8 | BC_2) >> 32) & 0xFFFF
#define _FC3_1 ((CC_B_64 | CC_G_85) >> 16) & 0xFFFF
#define _FC3_0 ((CC_R_143 | LOD_LSD_RB_0 | LODVTH_B__0V2 | LODVTH_G__0V2 | LODVTH_R__0V2)) & 0xFFFF

#define _FC4_2 ((DE_COUPLE3_EN_0 | DE_COUPLE3__1 | DE_COUPLE2_0 | FIRST_LINE_DIM__1 | CAURSE_B_1 | CAURSE_G_1 | CAURSE_R_1) >> 32) & 0xFFFF
#define _FC4_1 ((SR_ON_B_0 | SR_ON_G_0 | SR_ON_R_0 | SR_OFF_B_1 | SR_OFF_G_1 | SR_OFF_R_1 | FINE_B_1 | FINE_G_1 | FINE_R_1) >> 16) & 0xFFFF
#define _FC4_0 ((SCAN_REV_1 | IMAX_0)) & 0xFFFF

enum SCREENCOLOR{
    WHITE = 0,
    RED,
    GREEN,
    BLUE
};

extern const uint16_t FRAME_PERIOD;

#endif /* CLB_EX32_SYSTEM_INFO_H_ */
