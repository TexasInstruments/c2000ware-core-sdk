//###########################################################################
//
// FILE:    hw_erad.h
//
// TITLE:   Definitions for the ERAD registers.
//
//###########################################################################
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

#ifndef HW_ERAD_H
#define HW_ERAD_H

//*************************************************************************************************
//
// The following are defines for the ERAD register offsets
//
//*************************************************************************************************
#define ERAD_O_GLBL_EVENT_STAT   0x0U   // Global Event Status Register
#define ERAD_O_GLBL_HALT_STAT    0x2U   // Global Halt Status Register
#define ERAD_O_GLBL_ENABLE       0x4U   // Global Enable Register
#define ERAD_O_GLBL_CTM_RESET    0x6U   // Global Counter Reset
#define ERAD_O_GLBL_OWNER        0xAU   // Global Ownership

#define ERAD_O_HWBP_MASK     0x0U   // HWBP (EBC) Mask Register
#define ERAD_O_HWBP_REF      0x2U   // HWBP (EBC) Reference Register
#define ERAD_O_HWBP_CLEAR    0x4U   // HWBP (EBC) Clear Register
#define ERAD_O_HWBP_CNTL     0x6U   // HWBP (EBC) Control Register
#define ERAD_O_HWBP_STATUS   0x7U   // HWBP (EBC) Status Register

#define ERAD_O_CTM_CNTL        0x0U   // Counter Control Register
#define ERAD_O_CTM_STATUS      0x1U   // Counter Status Register
#define ERAD_O_CTM_REF         0x2U   // Counter Reference Register
#define ERAD_O_CTM_COUNT       0x4U   // Counter Current Value Register
#define ERAD_O_CTM_MAX_COUNT   0x6U   // Counter Max Count Value Register
#define ERAD_O_CTM_INPUT_SEL   0x8U   // Counter Input Select Register
#define ERAD_O_CTM_CLEAR       0x9U   // Counter Clear Register


//*************************************************************************************************
//
// The following are defines for the bit fields in the GLBL_EVENT_STAT register
//
//*************************************************************************************************
#define ERAD_GLBL_EVENT_STAT_HWBP1   0x1U     // Enhanced Bus Comparator (EBC) Module Event Status
#define ERAD_GLBL_EVENT_STAT_HWBP2   0x2U     // Enhanced Bus Comparator (EBC) Module Event Status
#define ERAD_GLBL_EVENT_STAT_HWBP3   0x4U     // Enhanced Bus Comparator (EBC) Module Event Status
#define ERAD_GLBL_EVENT_STAT_HWBP4   0x8U     // Enhanced Bus Comparator (EBC) Module Event Status
#define ERAD_GLBL_EVENT_STAT_HWBP5   0x10U    // Enhanced Bus Comparator (EBC) Module Event Status
#define ERAD_GLBL_EVENT_STAT_HWBP6   0x20U    // Enhanced Bus Comparator (EBC) Module Event Status
#define ERAD_GLBL_EVENT_STAT_HWBP7   0x40U    // Enhanced Bus Comparator (EBC) Module Event Status
#define ERAD_GLBL_EVENT_STAT_HWBP8   0x80U    // Enhanced Bus Comparator (EBC) Module Event Status
#define ERAD_GLBL_EVENT_STAT_CTM1    0x100U   // Counter Module Event Status
#define ERAD_GLBL_EVENT_STAT_CTM2    0x200U   // Counter Module Event Status
#define ERAD_GLBL_EVENT_STAT_CTM3    0x400U   // Counter Module Event Status
#define ERAD_GLBL_EVENT_STAT_CTM4    0x800U   // Counter Module Event Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the GLBL_HALT_STAT register
//
//*************************************************************************************************
#define ERAD_GLBL_HALT_STAT_HWBP1   0x1U     // Enhanced Bus Comparator (EBC) Module Halt Status
#define ERAD_GLBL_HALT_STAT_HWBP2   0x2U     // Enhanced Bus Comparator (EBC) Module Halt Status
#define ERAD_GLBL_HALT_STAT_HWBP3   0x4U     // Enhanced Bus Comparator (EBC) Module Halt Status
#define ERAD_GLBL_HALT_STAT_HWBP4   0x8U     // Enhanced Bus Comparator (EBC) Module Halt Status
#define ERAD_GLBL_HALT_STAT_HWBP5   0x10U    // Enhanced Bus Comparator (EBC) Module Halt Status
#define ERAD_GLBL_HALT_STAT_HWBP6   0x20U    // Enhanced Bus Comparator (EBC) Module Halt Status
#define ERAD_GLBL_HALT_STAT_HWBP7   0x40U    // Enhanced Bus Comparator (EBC) Module Halt Status
#define ERAD_GLBL_HALT_STAT_HWBP8   0x80U    // Enhanced Bus Comparator (EBC) Module Halt Status
#define ERAD_GLBL_HALT_STAT_CTM1    0x100U   // Counter Module Halt Status
#define ERAD_GLBL_HALT_STAT_CTM2    0x200U   // Counter Module Halt Status
#define ERAD_GLBL_HALT_STAT_CTM3    0x400U   // Counter Module Halt Status
#define ERAD_GLBL_HALT_STAT_CTM4    0x800U   // Counter Module Halt Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the GLBL_ENABLE register
//
//*************************************************************************************************
#define ERAD_GLBL_ENABLE_HWBP1   0x1U     // Enhanced Bus Comparator (EBC) Module Global Enable
#define ERAD_GLBL_ENABLE_HWBP2   0x2U     // Enhanced Bus Comparator (EBC) Module Global Enable
#define ERAD_GLBL_ENABLE_HWBP3   0x4U     // Enhanced Bus Comparator (EBC) Module Global Enable
#define ERAD_GLBL_ENABLE_HWBP4   0x8U     // Enhanced Bus Comparator (EBC) Module Global Enable
#define ERAD_GLBL_ENABLE_HWBP5   0x10U    // Enhanced Bus Comparator (EBC) Module Global Enable
#define ERAD_GLBL_ENABLE_HWBP6   0x20U    // Enhanced Bus Comparator (EBC) Module Global Enable
#define ERAD_GLBL_ENABLE_HWBP7   0x40U    // Enhanced Bus Comparator (EBC) Module Global Enable
#define ERAD_GLBL_ENABLE_HWBP8   0x80U    // Enhanced Bus Comparator (EBC) Module Global Enable
#define ERAD_GLBL_ENABLE_CTM1    0x100U   // Counter Module Global Enable
#define ERAD_GLBL_ENABLE_CTM2    0x200U   // Counter Module Global Enable
#define ERAD_GLBL_ENABLE_CTM3    0x400U   // Counter Module Global Enable
#define ERAD_GLBL_ENABLE_CTM4    0x800U   // Counter Module Global Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the GLBL_CTM_RESET register
//
//*************************************************************************************************
#define ERAD_GLBL_CTM_RESET_CTM1   0x1U   // Global Reset for the counters
#define ERAD_GLBL_CTM_RESET_CTM2   0x2U   // Global Reset for the counters
#define ERAD_GLBL_CTM_RESET_CTM3   0x4U   // Global Reset for the counters
#define ERAD_GLBL_CTM_RESET_CTM4   0x8U   // Global Reset for the counters

//*************************************************************************************************
//
// The following are defines for the bit fields in the GLBL_OWNER register
//
//*************************************************************************************************
#define ERAD_GLBL_OWNER_OWNER_S   0U
#define ERAD_GLBL_OWNER_OWNER_M   0x3U   // Global Ownership Bits


//*************************************************************************************************
//
// The following are defines for the bit fields in the HWBP_CLEAR register
//
//*************************************************************************************************
#define ERAD_HWBP_CLEAR_EVENT_CLR   0x1U   // Event Clear register

//*************************************************************************************************
//
// The following are defines for the bit fields in the HWBP_CNTL register
//
//*************************************************************************************************
#define ERAD_HWBP_CNTL_BUS_SEL_S     2U
#define ERAD_HWBP_CNTL_BUS_SEL_M     0x1CU    // Bus select bits
#define ERAD_HWBP_CNTL_STOP          0x20U    // Stop bit (Halt/No Halt of CPU)
#define ERAD_HWBP_CNTL_RTOSINT       0x40U    // RTOSINT bit
#define ERAD_HWBP_CNTL_COMP_MODE_S   7U
#define ERAD_HWBP_CNTL_COMP_MODE_M   0x380U   // Compare mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the HWBP_STATUS register
//
//*************************************************************************************************
#define ERAD_HWBP_STATUS_EVENT_FIRED   0x1U      // HWBP (EBC) Event Fired bits
#define ERAD_HWBP_STATUS_MODULE_ID_S   8U
#define ERAD_HWBP_STATUS_MODULE_ID_M   0x3F00U   // Identification bits
#define ERAD_HWBP_STATUS_STATUS_S      14U
#define ERAD_HWBP_STATUS_STATUS_M      0xC000U   // Status bits


//*************************************************************************************************
//
// The following are defines for the bit fields in the CTM_CNTL register
//
//*************************************************************************************************
#define ERAD_CTM_CNTL_START_STOP_MODE   0x4U      // Start_stop mode bit
#define ERAD_CTM_CNTL_EVENT_MODE        0x8U      // Event mode bit
#define ERAD_CTM_CNTL_RST_ON_MATCH      0x10U     // Reset_on_match bit
#define ERAD_CTM_CNTL_STOP              0x40U     // Stop bit (Halt/No Halt of CPU)
#define ERAD_CTM_CNTL_RTOSINT           0x80U     // RTOSINT bit
#define ERAD_CTM_CNTL_RST_EN            0x400U    // Enable Reset
#define ERAD_CTM_CNTL_RST_INP_SEL_S     11U
#define ERAD_CTM_CNTL_RST_INP_SEL_M     0xF800U   // Reset Input select

//*************************************************************************************************
//
// The following are defines for the bit fields in the CTM_STATUS register
//
//*************************************************************************************************
#define ERAD_CTM_STATUS_EVENT_FIRED   0x1U      // Counter Event Fired bits
#define ERAD_CTM_STATUS_OVERFLOW      0x2U      // Counter Overflowed
#define ERAD_CTM_STATUS_MODULE_ID_S   2U
#define ERAD_CTM_STATUS_MODULE_ID_M   0xFFCU    // Identification bits
#define ERAD_CTM_STATUS_STATUS_S      12U
#define ERAD_CTM_STATUS_STATUS_M      0xF000U   // Status bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the CTM_INPUT_SEL register
//
//*************************************************************************************************
#define ERAD_CTM_INPUT_SEL_CTM_INP_SEL_EN   0x1U      // Count input select enable
#define ERAD_CTM_INPUT_SEL_CNT_INP_SEL_S    1U
#define ERAD_CTM_INPUT_SEL_CNT_INP_SEL_M    0x3EU     // Count input select
#define ERAD_CTM_INPUT_SEL_STA_INP_SEL_S    6U
#define ERAD_CTM_INPUT_SEL_STA_INP_SEL_M    0x7C0U    // Start input select
#define ERAD_CTM_INPUT_SEL_STO_INP_SEL_S    11U
#define ERAD_CTM_INPUT_SEL_STO_INP_SEL_M    0xF800U   // Stop input select

//*************************************************************************************************
//
// The following are defines for the bit fields in the CTM_CLEAR register
//
//*************************************************************************************************
#define ERAD_CTM_CLEAR_EVENT_CLEAR      0x1U   // Clear EVENT_FIRED
#define ERAD_CTM_CLEAR_OVERFLOW_CLEAR   0x2U   // Clear OVERFLOW



#endif
