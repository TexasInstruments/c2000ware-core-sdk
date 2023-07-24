//###########################################################################
//
// FILE:    hw_lcm.h
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

#ifndef HW_LCM_H
#define HW_LCM_H

//*************************************************************************************************
//
// The following are defines for the LCM register offsets
//
//*************************************************************************************************
#define LCM_O_REVISION       0x0U    // IP Revision tie-off value
#define LCM_O_CONTROL        0x8U    // LCM Control configuration
#define LCM_O_STATUS         0x20U   // LCM status register
#define LCM_O_STATUS_CLEAR   0x28U   // LCM Status clear register
#define LCM_O_PARITY_TEST    0x68U   // Enabling the parity test feature
#define LCM_O_LOCK           0x70U   // LCM lock configuration
#define LCM_O_COMMIT         0x78U   // LCM commit configuration


//*************************************************************************************************
//
// The following are defines for the bit fields in the REVISION register
//
//*************************************************************************************************
#define LCM_REVISION_MINOR_S    0U
#define LCM_REVISION_MINOR_M    0x3FU         // Minor Revision Number
#define LCM_REVISION_CUSTOM_S   6U
#define LCM_REVISION_CUSTOM_M   0xC0U         // Custom Module Number
#define LCM_REVISION_MAJOR_S    8U
#define LCM_REVISION_MAJOR_M    0x700U        // Major Revision Number
#define LCM_REVISION_FUNC_S     16U
#define LCM_REVISION_FUNC_M     0xFFF0000U    // Functional Release Number
#define LCM_REVISION_SCHEME_S   30U
#define LCM_REVISION_SCHEME_M   0xC0000000U   // Defines Scheme for Module

//*************************************************************************************************
//
// The following are defines for the bit fields in the LCM_CONTROL register
//
//*************************************************************************************************
#define LCM_CONTROL_CMPEN            0x1U        // Enable/disable configuration for lockstep
                                                 // compare.
#define LCM_CONTROL_STEN             0x10000U    // Self-test enable
#define LCM_CONTROL_CMP1_ERR_FORCE   0x80000U    // Force error on comparator-1 lockstep compare
                                                 // error output
#define LCM_CONTROL_CMP2_ERR_FORCE   0x200000U   // Force error on comparator-2 lockstep compare
                                                 // error output

//*************************************************************************************************
//
// The following are defines for the bit fields in the LCM_STATUS register
//
//*************************************************************************************************
#define LCM_STATUS_LSEN                  0x1U        // Lockstep configuration status
#define LCM_STATUS_CMP_FAIL              0x2U        // Pass/fail status of lockstep compare
#define LCM_STATUS_DBGCON                0x100U      // debugger connected status information
#define LCM_STATUS_STPASS                0x10000U    // self-test pass/fail status
#define LCM_STATUS_STDONE                0x20000U    // self-test completion status
#define LCM_STATUS_STACTIVE              0x40000U    // self-test active status indication
#define LCM_STATUS_CMP1_ERR_FORCE_PASS   0x80000U    // fail status of comparator1 func error
                                                     // forcing
#define LCM_STATUS_CMP1_ERR_FORCE_DONE   0x100000U   // completion status of comparator1 func error
                                                     // forcing
#define LCM_STATUS_CMP2_ERR_FORCE_PASS   0x200000U   // fail status of comparator2 func error
                                                     // forcing
#define LCM_STATUS_CMP2_ERR_FORCE_DONE   0x400000U   // completion status of comparator2 func error
                                                     // forcing

//*************************************************************************************************
//
// The following are defines for the bit fields in the LCM_STATUS_CLEAR register
//
//*************************************************************************************************
#define LCM_STATUS_CLEAR_CMP_FAIL              0x2U        // Clear lockstep compare fail status
#define LCM_STATUS_CLEAR_STPASS                0x10000U    // clear Self-test_fail_status
#define LCM_STATUS_CLEAR_STDONE                0x20000U    // clear Self-test_done_status
#define LCM_STATUS_CLEAR_CMP1_ERR_FORCE_PASS   0x80000U    // clear
                                                           // cmp1_func_error_force_fail_status
#define LCM_STATUS_CLEAR_CMP1_ERR_FORCE_DONE   0x100000U   // clear
                                                           // cmp1_func_error_force_done_status
#define LCM_STATUS_CLEAR_CMP2_ERR_FORCE_PASS   0x200000U   // clear
                                                           // cmp2_func_error_force_fail_status
#define LCM_STATUS_CLEAR_CMP2_ERR_FORCE_DONE   0x400000U   // clear
                                                           // cmp2_func_error_force_done_status

//*************************************************************************************************
//
// The following are defines for the bit fields in the PARITY_TEST register
//
//*************************************************************************************************
#define LCM_PARITY_TEST_TESTEN_S   0U
#define LCM_PARITY_TEST_TESTEN_M   0xFU   // Parity test enable configuration

//*************************************************************************************************
//
// The following are defines for the bit fields in the LCM_LOCK register
//
//*************************************************************************************************
#define LCM_LOCK_LCM_CONTROL        0x4U         // Register lock configuration
#define LCM_LOCK_LCM_STATUS_CLEAR   0x400U       // Register lock configuration
#define LCM_LOCK_PARITY_TEST        0x4000000U   // Register lock configuration

//*************************************************************************************************
//
// The following are defines for the bit fields in the LCM_COMMIT register
//
//*************************************************************************************************
#define LCM_COMMIT_LCM_CONTROL        0x4U         // Register commit configuration
#define LCM_COMMIT_LCM_STATUS_CLEAR   0x400U       // Register commit configuration
#define LCM_COMMIT_PARITY_TEST        0x4000000U   // Register commit configuration



#endif
