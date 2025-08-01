//###########################################################################
//
// FILE:   f28e12x_mcpwm_defines.h
//
// TITLE:  #defines used in MCPwm examples
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

#ifndef F28E12x_MCPWM_DEFINES_H
#define F28E12x_MCPWM_DEFINES_H

#ifdef __cplusplus
extern "C" {
#endif

//
// Defines
//

//
// TBCTL Register
//

//
// CTRMODE Counter Mode bits
//
#define TB_COUNT_UP       0x0
#define TB_COUNT_UPDOWN   0x1
#define TB_FREEZE         0X2

//
// CLKDIV Time Base Clock Pre-scaler bits
//
#define TB_DIV1           0x0     
#define TB_DIV2           0x1     
#define TB_DIV4           0x2     
#define TB_DIV8           0x3     
#define TB_DIV16          0x4    
#define TB_DIV32          0x5    
#define TB_DIV64          0x6    
#define TB_DIV128         0x7   
#define TB_DIV256         0x8   
#define TB_DIV512         0x9   
#define TB_DIV1024        0xA 
#define TB_DIV2048        0xB
#define TB_DIV4096        0xC
#define TB_DIV8192        0xD 
#define TB_DIV16384       0xE
#define TB_DIV32768       0xF

//
// PRDLD Shadow to active load of TBPRD bit
//
#define TB_SHADOW_LOAD_ENABLE   0x0 // Shadow to active load of TBPRD occurs on TBCTR = 0
#define TB_SHADOW_LOAD_DISABLE  0x1 // Shadow to active load of TBPRD is disabled

//
// PHSEN Phase Load Enable bit
//
#define TB_PHASE_DISABLE   0x0 
#define TB_PHASE_ENABLE    0x1

//
// PHSDIR Phase Direction Bit
//
#define TB_DOWN            0x0
#define TB_UP              0x1

//
// SWSYNC Software Force Sync Pulse bit
//
#define TB_SWSYNC          0x1

//
// SYNCOSEL Sync Output Select bits
//
#define SYNC_OUT_ON_SOFTWARE  0x0
#define SYNC_OUT_ON_COUNTER_ZERO  0x1
#define SYNC_OUT_ON_COUNTER_COMPARE_C     0x2
#define SYNC_OUT_ON_COUNTER_COMPARE_D     0x3
#define SYNC_OUT_DISABLED     0x4

//
// FREE_SOFT Emulation Mode Bits
//
#define EMULATION_STOP_AFTER_NEXT_TB    0x0
#define EMULATION_STOP_AFTER_FULL_CYCLE 0x1
#define EMULATION_FREE_RUN              0x2

//
// SYNCPERSEL Sync peripheral Select bits
//
#define SYNC_PULSE_DISABLED         0x0
#define SYNCPERSEL_SOURCE_PERIOD    0x2
#define SYNCPERSEL_SOURCE_ZERO      0x3
#define SYNCPERSEL_SOURCE_CMPC_UP   0x4
#define SYNCPERSEL_SOURCE_CMPC_DOWN 0x5
#define SYNCPERSEL_SOURCE_CMPD_UP   0x6
#define SYNCPERSEL_SOURCE_CMPD_DOWN 0x7

//
// SYNCISEL Sync Input Select bits
//
#define SYNC_IN_PULSE_SRC_DISABLE		         0x0	//! Disable Sync-in
#define SYNC_IN_PULSE_SRC_INPUTXBAR_OUT5		 0x1	//! Sync-in source is Input XBAR out5 signal
#define SYNC_IN_PULSE_SRC_INPUTXBAR_OUT6		 0x2	//! Sync-in source is Input XBAR out6 signal
#define SYNC_IN_PULSE_SRC_SYNCOUT_ECAP1		     0x3	//! Sync-in source is ECAP1 sync-out signal
#define SYNC_IN_PULSE_SRC_SYNCOUT_MCPWM1		 0x5	//! Sync-in source is MCPWM1 sync-out signal
#define SYNC_IN_PULSE_SRC_SYNCOUT_MCPWM3		 0x7	//! Sync-in source is MCPWM3 sync-out signal

//
// CMPCTL (Counter Compare Control) Register
//
#define CC_CTR_ZERO     0x0
#define CC_CTR_UP       0x1
#define CC_CTR_ZERO_PRD 0x2
#define CC_LD_DISABLE   0x3

//
// AQCTL (Action Qualifier Control) Register
//
#define AQ_CTR_ZERO     0x0
#define AQ_CTR_UP       0x1
#define AQ_CTR_ZERO_PRD 0x2
#define AQ_LD_DISABLE   0x3

//
// AQSFRC (Action Qualifier Software Force) Register 
//
#define AQ_SW_FORCE_DISABLED   0
#define AQ_SW_CONTINUOUS_LOW   1
#define AQ_SW_CONTINUOUS_HIGH  2
#define AQ_SW_ONE_SHOT_LOW     5
#define AQ_SW_ONE_SHOT_HIGH    6
#define AQ_SW_ONE_SHOT_TOGGLE  7

//
// AQCTLA and AQCTLB (Action Qualifier Control) Registers
//
// ZRO, PRD, CAU, CAD, CBU, and CBD bits
//
#define AQ_NO_ACTION    0x0
#define AQ_CLEAR        0x1
#define AQ_SET          0x2
#define AQ_TOGGLE       0x3

//
// SOCEN (Start of Conversion Enable) Register
//
#define SOC_ENABLE      0x1
#define SOC_DISABLE     0x0

//
// SOCSEL (Start of Conversion Event Selection) Register
//
// for SOCA, SOCB, SOCC, SOCD Selection bits
//
#define SOC_DISABLED            0
#define SOC_TBCTR_ZERO          2
#define SOC_TBCTR_PERIOD        3
#define SOC_TBCTR_ZERO_PERIOD   4
#define SOC_TBCTR_U_CMPC        8
#define SOC_TBCTR_U_CMPD        9
#define SOC_TBCTR_U_CMP1A       10
#define SOC_TBCTR_U_CMP1B       11
#define SOC_TBCTR_U_CMP2A       12
#define SOC_TBCTR_U_CMP2B       13
#define SOC_TBCTR_U_CMP3A       14
#define SOC_TBCTR_U_CMP3B       15
#define SOC_TBCTR_D_CMPC        16
#define SOC_TBCTR_D_CMPD        17
#define SOC_TBCTR_D_CMP1A       18
#define SOC_TBCTR_D_CMP1B       19
#define SOC_TBCTR_D_CMP2A       20
#define SOC_TBCTR_D_CMP2B       21
#define SOC_TBCTR_D_CMP3A       22
#define SOC_TBCTR_D_CMP3B       23

//
// ETSEL (Event Trigger Selection) Register
// 
// ET1 and ET2 Selection bits
//
#define EVT_DISABLED            0
#define EVT_TBCTR_ZERO          2
#define EVT_TBCTR_PERIOD        3
#define EVT_TBCTR_ZERO_PERIOD   4
#define EVT_TBCTR_U_CMPC        8
#define EVT_TBCTR_U_CMPD        9
#define EVT_TBCTR_U_CMP1A       10
#define EVT_TBCTR_U_CMP1B       11
#define EVT_TBCTR_U_CMP2A       12
#define EVT_TBCTR_U_CMP2B       13
#define EVT_TBCTR_U_CMP3A       14
#define EVT_TBCTR_U_CMP3B       15
#define EVT_TBCTR_D_CMPC        16
#define EVT_TBCTR_D_CMPD        17
#define EVT_TBCTR_D_CMP1A       18
#define EVT_TBCTR_D_CMP1B       19
#define EVT_TBCTR_D_CMP2A       20
#define EVT_TBCTR_D_CMP2B       21
#define EVT_TBCTR_D_CMP3A       22
#define EVT_TBCTR_D_CMP3B       23

//
// INTEN (Interrupt Enable) Register
//
// used for CBC, OST, ET1, ET2, CNT_OVF bits
//
#define INT_ENABLE     0x1
#define INT_DISABLE    0x0

//
// TZSEL (Trip Zone Selection) Register
//
// for CBC1, CBC2, CBC3, CBC4, CBC5, CBC6, CBC7, CBC8, 
//     OST1, OST2, OST3, OST4, OST5, OST6, OST7, OST8 bits
//
#define TZ_ENABLE    0x1
#define TZ_DISABLE    0x0

//
// TZCTL (Trip Zone Control) Register
//

//
// TZA, TZB bits
//

#define TZ_HIZ       0x0
#define TZ_FORCE_HI  0x1
#define TZ_FORCE_LO  0x2
#define TZ_NO_CHANGE 0x3

//
// CBCPULSE (Clear Pulse for CBC Trip Latch) bits
//
#define CBCPULSE_DISABLE        0x0
#define CBCPULSE_CTR_ZERO       0x1
#define CBCPULSE_CTR_PRD        0x2
#define CBCPULSE_CTR_ZERO_PRD   0x3


//
// DBCTL (Dead Band Control) Register
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
// OUTSWAP bits
//
#define DB_SWAP_DISABLE             0x0
#define DB_A_APATH_B_APATH          0x1
#define DB_A_BPATH_B_BPATH          0x2
#define DB_A_BPATH_B_APATH          0x3

//
// DEDBMODE DeadBand Dual Edge B Mode Control Bits
//
#define DB_DEDB_DISABLE    0x0
#define DB_DEDB_ENABLE     0x1 // Rising Edge delay applied to Falling edge delay output

//
// LOADFEDMODE, LOADREDMODE bits
// 
#define DB_CTR_ZERO     0x0
#define DB_CTR_UP       0x1
#define DB_CTR_ZERO_PRD 0x2
#define DB_LD_DISABLE   0x3

//
// GLDCTL (Global Load Control) Register
//

//
// GLD bits
//
#define GLD_ENABLE 0x1
#define GLD_DISABLE 0x0

//
// OSHTMODE bits
//
#define GLD_ONESHOT_DISABLE 0x0
#define GLD_ONESHOT_ENABLE 0x1

//
// GLDMODE bits
// 
#define GLD_CTR_ZERO     0x0
#define GLD_CTR_UP       0x1
#define GLD_CTR_ZERO_PRD 0x2
#define GLD_LD_DISABLE   0x3


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of F28E12x_MCPWM_DEFINES_H

//
// End of file
//
