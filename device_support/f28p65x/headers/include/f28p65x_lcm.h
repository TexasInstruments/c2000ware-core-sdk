//###########################################################################
//
// FILE:    f28p65x_lcm.h
//
// TITLE:   Definitions for the LCM registers.
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

#ifndef F28P65X_LCM_H
#define F28P65X_LCM_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// LCM Individual Register Bit Definitions:

struct LCM_REVISION_BITS {              // bits description
    bp_16 MINOR:6;                      // 5:0 Minor Revision Number
    bp_16 CUSTOM:2;                     // 7:6 Custom Module Number
    bp_16 MAJOR:3;                      // 10:8 Major Revision Number
    bp_16 rsvd1:5;                      // 15:11 Reserved
    bp_32 FUNC:12;                      // 27:16 Functional Release Number
    bp_32 rsvd2:2;                      // 29:28 Reserved
    bp_32 SCHEME:2;                     // 31:30 Defines Scheme for Module
};

union LCM_REVISION_REG {
    bp_32  all;
    struct  LCM_REVISION_BITS  bit;
};

struct LCM_CONTROL_BITS {               // bits description
    bp_16 CMPEN:1;                      // 0 Enable/disable configuration for lockstep compare.
    bp_16 rsvd1:15;                     // 15:1 Reserved
    bp_32 STEN:1;                       // 16 Self-test enable
    bp_32 rsvd2:2;                      // 18:17 Reserved
    bp_32 CMP1_ERR_FORCE:1;             // 19 Force error on comparator-1 lockstep compare error output
    bp_32 rsvd3:1;                      // 20 Reserved
    bp_32 CMP2_ERR_FORCE:1;             // 21 Force error on comparator-2 lockstep compare error output
    bp_32 rsvd4:10;                     // 31:22 Reserved
};

union LCM_CONTROL_REG {
    bp_32  all;
    struct  LCM_CONTROL_BITS  bit;
};

struct LCM_STATUS_BITS {                // bits description
    bp_16 LSEN:1;                       // 0 Lockstep configuration status
    bp_16 CMP_FAIL:1;                   // 1 Pass/fail status of lockstep compare
    bp_16 rsvd1:6;                      // 7:2 Reserved
    bp_16 DBGCON:1;                     // 8 debugger connected status information
    bp_16 rsvd2:7;                      // 15:9 Reserved
    bp_32 STPASS:1;                     // 16 self-test pass/fail status
    bp_32 STDONE:1;                     // 17 self-test completion status
    bp_32 STACTIVE:1;                   // 18 self-test active status indication
    bp_32 CMP1_ERR_FORCE_PASS:1;        // 19 fail status of comparator1 func error forcing
    bp_32 CMP1_ERR_FORCE_DONE:1;        // 20 completion status of comparator1 func error forcing
    bp_32 CMP2_ERR_FORCE_PASS:1;        // 21 fail status of comparator2 func error forcing
    bp_32 CMP2_ERR_FORCE_DONE:1;        // 22 completion status of comparator2 func error forcing
    bp_32 rsvd3:9;                      // 31:23 Reserved
};

union LCM_STATUS_REG {
    bp_32  all;
    struct  LCM_STATUS_BITS  bit;
};

struct LCM_STATUS_CLEAR_BITS {          // bits description
    bp_16 rsvd1:1;                      // 0 Reserved
    bp_16 CMP_FAIL:1;                   // 1 Clear lockstep compare fail status
    bp_16 rsvd2:14;                     // 15:2 Reserved
    bp_32 STPASS:1;                     // 16 clear Self-test_fail_status
    bp_32 STDONE:1;                     // 17 clear Self-test_done_status
    bp_32 rsvd3:1;                      // 18 Reserved
    bp_32 CMP1_ERR_FORCE_PASS:1;        // 19 clear cmp1_func_error_force_fail_status
    bp_32 CMP1_ERR_FORCE_DONE:1;        // 20 clear cmp1_func_error_force_done_status
    bp_32 CMP2_ERR_FORCE_PASS:1;        // 21 clear cmp2_func_error_force_fail_status
    bp_32 CMP2_ERR_FORCE_DONE:1;        // 22 clear cmp2_func_error_force_done_status
    bp_32 rsvd4:9;                      // 31:23 Reserved
};

union LCM_STATUS_CLEAR_REG {
    bp_32  all;
    struct  LCM_STATUS_CLEAR_BITS  bit;
};

struct PARITY_TEST_BITS {               // bits description
    bp_16 TESTEN:4;                     // 3:0 Parity test enable configuration
    bp_16 rsvd1:12;                     // 15:4 Reserved
    bp_32 rsvd2:16;                     // 31:16 Reserved
};

union PARITY_TEST_REG {
    bp_32  all;
    struct  PARITY_TEST_BITS  bit;
};

struct LCM_LOCK_BITS {                  // bits description
    bp_16 rsvd1:1;                      // 0 Reserved
    bp_16 rsvd2:1;                      // 1 Reserved
    bp_16 LCM_CONTROL:1;                // 2 Register lock configuration
    bp_16 rsvd3:1;                      // 3 Reserved
    bp_16 rsvd4:1;                      // 4 Reserved
    bp_16 rsvd5:1;                      // 5 Reserved
    bp_16 rsvd6:1;                      // 6 Reserved
    bp_16 rsvd7:1;                      // 7 Reserved
    bp_16 rsvd8:1;                      // 8 Reserved
    bp_16 rsvd9:1;                      // 9 Reserved
    bp_16 LCM_STATUS_CLEAR:1;           // 10 Register lock configuration
    bp_16 rsvd10:1;                     // 11 Reserved
    bp_16 rsvd11:1;                     // 12 Reserved
    bp_16 rsvd12:1;                     // 13 Reserved
    bp_16 rsvd13:1;                     // 14 Reserved
    bp_16 rsvd14:1;                     // 15 Reserved
    bp_32 rsvd15:1;                     // 16 Reserved
    bp_32 rsvd16:1;                     // 17 Reserved
    bp_32 rsvd17:1;                     // 18 Reserved
    bp_32 rsvd18:1;                     // 19 Reserved
    bp_32 rsvd19:1;                     // 20 Reserved
    bp_32 rsvd20:1;                     // 21 Reserved
    bp_32 rsvd21:1;                     // 22 Reserved
    bp_32 rsvd22:1;                     // 23 Reserved
    bp_32 rsvd23:1;                     // 24 Reserved
    bp_32 rsvd24:1;                     // 25 Reserved
    bp_32 PARITY_TEST:1;                // 26 Register lock configuration
    bp_32 rsvd25:1;                     // 27 Reserved
    bp_32 rsvd26:1;                     // 28 Reserved
    bp_32 rsvd27:1;                     // 29 Reserved
    bp_32 rsvd28:1;                     // 30 Reserved
    bp_32 rsvd29:1;                     // 31 Reserved
};

union LCM_LOCK_REG {
    bp_32  all;
    struct  LCM_LOCK_BITS  bit;
};

struct LCM_COMMIT_BITS {                // bits description
    bp_16 rsvd1:1;                      // 0 Reserved
    bp_16 rsvd2:1;                      // 1 Reserved
    bp_16 LCM_CONTROL:1;                // 2 Register commit configuration
    bp_16 rsvd3:1;                      // 3 Reserved
    bp_16 rsvd4:1;                      // 4 Reserved
    bp_16 rsvd5:1;                      // 5 Reserved
    bp_16 rsvd6:1;                      // 6 Reserved
    bp_16 rsvd7:1;                      // 7 Reserved
    bp_16 rsvd8:1;                      // 8 Reserved
    bp_16 rsvd9:1;                      // 9 Reserved
    bp_16 LCM_STATUS_CLEAR:1;           // 10 Register commit configuration
    bp_16 rsvd10:1;                     // 11 Reserved
    bp_16 rsvd11:1;                     // 12 Reserved
    bp_16 rsvd12:1;                     // 13 Reserved
    bp_16 rsvd13:1;                     // 14 Reserved
    bp_16 rsvd14:1;                     // 15 Reserved
    bp_32 rsvd15:1;                     // 16 Reserved
    bp_32 rsvd16:1;                     // 17 Reserved
    bp_32 rsvd17:1;                     // 18 Reserved
    bp_32 rsvd18:1;                     // 19 Reserved
    bp_32 rsvd19:1;                     // 20 Reserved
    bp_32 rsvd20:1;                     // 21 Reserved
    bp_32 rsvd21:1;                     // 22 Reserved
    bp_32 rsvd22:1;                     // 23 Reserved
    bp_32 rsvd23:1;                     // 24 Reserved
    bp_32 rsvd24:1;                     // 25 Reserved
    bp_32 PARITY_TEST:1;                // 26 Register commit configuration
    bp_32 rsvd25:1;                     // 27 Reserved
    bp_32 rsvd26:1;                     // 28 Reserved
    bp_32 rsvd27:1;                     // 29 Reserved
    bp_32 rsvd28:1;                     // 30 Reserved
    bp_32 rsvd29:1;                     // 31 Reserved
};

union LCM_COMMIT_REG {
    bp_32  all;
    struct  LCM_COMMIT_BITS  bit;
};

struct LCM_REGS {
    union   LCM_REVISION_REG                 REVISION;                     // IP Revision tie-off value
    uint32_t                                 rsvd1[2];                     // Reserved
    union   LCM_CONTROL_REG                  LCM_CONTROL;                  // LCM Control configuration
    uint32_t                                 rsvd2[10];                    // Reserved
    union   LCM_STATUS_REG                   LCM_STATUS;                   // LCM status register
    uint32_t                                 rsvd3[2];                     // Reserved
    union   LCM_STATUS_CLEAR_REG             LCM_STATUS_CLEAR;             // LCM Status clear register
    uint32_t                                 rsvd4[30];                    // Reserved
    union   PARITY_TEST_REG                  PARITY_TEST;                  // Enabling the parity test feature
    uint32_t                                 rsvd5[2];                     // Reserved
    union   LCM_LOCK_REG                     LCM_LOCK;                     // LCM lock configuration
    uint32_t                                 rsvd6[2];                     // Reserved
    union   LCM_COMMIT_REG                   LCM_COMMIT;                   // LCM commit configuration
};

//---------------------------------------------------------------------------
// LCM External References & Function Declarations:
//
extern volatile struct LCM_REGS LCMCPU2Regs;
extern volatile struct LCM_REGS LCMCPU2DMA1Regs;
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
