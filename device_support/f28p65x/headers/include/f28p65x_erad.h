//###########################################################################
//
// FILE:    f28p65x_erad.h
//
// TITLE:   Definitions for the ERAD registers.
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

#ifndef F28P65X_ERAD_H
#define F28P65X_ERAD_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// ERAD Individual Register Bit Definitions:

struct GLBL_EVENT_STAT_BITS {           // bits description
    Uint16 HWBP1:1;                     // 0 Enhanced Bus Comparator (EBC) Module Event Status
    Uint16 HWBP2:1;                     // 1 Enhanced Bus Comparator (EBC) Module Event Status
    Uint16 HWBP3:1;                     // 2 Enhanced Bus Comparator (EBC) Module Event Status
    Uint16 HWBP4:1;                     // 3 Enhanced Bus Comparator (EBC) Module Event Status
    Uint16 HWBP5:1;                     // 4 Enhanced Bus Comparator (EBC) Module Event Status
    Uint16 HWBP6:1;                     // 5 Enhanced Bus Comparator (EBC) Module Event Status
    Uint16 HWBP7:1;                     // 6 Enhanced Bus Comparator (EBC) Module Event Status
    Uint16 HWBP8:1;                     // 7 Enhanced Bus Comparator (EBC) Module Event Status
    Uint16 CTM1:1;                      // 8 Counter Module Event Status
    Uint16 CTM2:1;                      // 9 Counter Module Event Status
    Uint16 CTM3:1;                      // 10 Counter Module Event Status
    Uint16 CTM4:1;                      // 11 Counter Module Event Status
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union GLBL_EVENT_STAT_REG {
    Uint16  all;
    struct  GLBL_EVENT_STAT_BITS  bit;
};

struct GLBL_HALT_STAT_BITS {            // bits description
    Uint16 HWBP1:1;                     // 0 Enhanced Bus Comparator (EBC) Module Halt Status
    Uint16 HWBP2:1;                     // 1 Enhanced Bus Comparator (EBC) Module Halt Status
    Uint16 HWBP3:1;                     // 2 Enhanced Bus Comparator (EBC) Module Halt Status
    Uint16 HWBP4:1;                     // 3 Enhanced Bus Comparator (EBC) Module Halt Status
    Uint16 HWBP5:1;                     // 4 Enhanced Bus Comparator (EBC) Module Halt Status
    Uint16 HWBP6:1;                     // 5 Enhanced Bus Comparator (EBC) Module Halt Status
    Uint16 HWBP7:1;                     // 6 Enhanced Bus Comparator (EBC) Module Halt Status
    Uint16 HWBP8:1;                     // 7 Enhanced Bus Comparator (EBC) Module Halt Status
    Uint16 CTM1:1;                      // 8 Counter Module Halt Status
    Uint16 CTM2:1;                      // 9 Counter Module Halt Status
    Uint16 CTM3:1;                      // 10 Counter Module Halt Status
    Uint16 CTM4:1;                      // 11 Counter Module Halt Status
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union GLBL_HALT_STAT_REG {
    Uint16  all;
    struct  GLBL_HALT_STAT_BITS  bit;
};

struct GLBL_ENABLE_BITS {               // bits description
    Uint16 HWBP1:1;                     // 0 Enhanced Bus Comparator (EBC) Module Global Enable
    Uint16 HWBP2:1;                     // 1 Enhanced Bus Comparator (EBC) Module Global Enable
    Uint16 HWBP3:1;                     // 2 Enhanced Bus Comparator (EBC) Module Global Enable
    Uint16 HWBP4:1;                     // 3 Enhanced Bus Comparator (EBC) Module Global Enable
    Uint16 HWBP5:1;                     // 4 Enhanced Bus Comparator (EBC) Module Global Enable
    Uint16 HWBP6:1;                     // 5 Enhanced Bus Comparator (EBC) Module Global Enable
    Uint16 HWBP7:1;                     // 6 Enhanced Bus Comparator (EBC) Module Global Enable
    Uint16 HWBP8:1;                     // 7 Enhanced Bus Comparator (EBC) Module Global Enable
    Uint16 CTM1:1;                      // 8 Counter Module Global Enable
    Uint16 CTM2:1;                      // 9 Counter Module Global Enable
    Uint16 CTM3:1;                      // 10 Counter Module Global Enable
    Uint16 CTM4:1;                      // 11 Counter Module Global Enable
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union GLBL_ENABLE_REG {
    Uint16  all;
    struct  GLBL_ENABLE_BITS  bit;
};

struct GLBL_CTM_RESET_BITS {            // bits description
    Uint16 CTM1:1;                      // 0 Global Reset for the counters
    Uint16 CTM2:1;                      // 1 Global Reset for the counters
    Uint16 CTM3:1;                      // 2 Global Reset for the counters
    Uint16 CTM4:1;                      // 3 Global Reset for the counters
    Uint16 rsvd1:12;                    // 15:4 Reserved
};

union GLBL_CTM_RESET_REG {
    Uint16  all;
    struct  GLBL_CTM_RESET_BITS  bit;
};

struct GLBL_NMI_CTL_BITS {              // bits description
    Uint16 HWBP1:1;                     // 0 Enhanced Bus Comparator (EBC) non-maskable interrupt enable
    Uint16 HWBP2:1;                     // 1 Enhanced Bus Comparator (EBC) non-maskable interrupt enable
    Uint16 HWBP3:1;                     // 2 Enhanced Bus Comparator (EBC) non-maskable interrupt enable
    Uint16 HWBP4:1;                     // 3 Enhanced Bus Comparator (EBC) non-maskable interrupt enable
    Uint16 HWBP5:1;                     // 4 Enhanced Bus Comparator (EBC) non-maskable interrupt enable
    Uint16 HWBP6:1;                     // 5 Enhanced Bus Comparator (EBC) non-maskable interrupt enable
    Uint16 HWBP7:1;                     // 6 Enhanced Bus Comparator (EBC) non-maskable interrupt enable
    Uint16 HWBP8:1;                     // 7 Enhanced Bus Comparator (EBC) non-maskable interrupt enable
    Uint16 CTM1:1;                      // 8 Counter  non-maskable interrupt enable
    Uint16 CTM2:1;                      // 9 Counter  non-maskable interrupt enable
    Uint16 CTM3:1;                      // 10 Counter  non-maskable interrupt enable
    Uint16 CTM4:1;                      // 11 Counter  non-maskable interrupt enable
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union GLBL_NMI_CTL_REG {
    Uint16  all;
    struct  GLBL_NMI_CTL_BITS  bit;
};

struct GLBL_OWNER_BITS {                // bits description
    Uint16 OWNER:2;                     // 1:0 Global Ownership Bits
    Uint16 rsvd1:14;                    // 15:2 Reserved
};

union GLBL_OWNER_REG {
    Uint16  all;
    struct  GLBL_OWNER_BITS  bit;
};

struct GLBL_EVENT_AND_MASK_BITS {       // bits description
    Uint16 MASK1_HWBP1:1;               // 0 Enhanced Bus Comparator (EBC) AND Event Mask1
    Uint16 MASK1_HWBP2:1;               // 1 Enhanced Bus Comparator (EBC) AND Event Mask1
    Uint16 MASK1_HWBP3:1;               // 2 Enhanced Bus Comparator (EBC) AND Event Mask1
    Uint16 MASK1_HWBP4:1;               // 3 Enhanced Bus Comparator (EBC) AND Event Mask1
    Uint16 MASK1_HWBP5:1;               // 4 Enhanced Bus Comparator (EBC) AND Event Mask1
    Uint16 MASK1_HWBP6:1;               // 5 Enhanced Bus Comparator (EBC) AND Event Mask1
    Uint16 MASK1_HWBP7:1;               // 6 Enhanced Bus Comparator (EBC) AND Event Mask1
    Uint16 MASK1_HWBP8:1;               // 7 Enhanced Bus Comparator (EBC) AND Event Mask1
    Uint16 MASK2_HWBP1:1;               // 8 Enhanced Bus Comparator (EBC) AND Event Mask2
    Uint16 MASK2_HWBP2:1;               // 9 Enhanced Bus Comparator (EBC) AND Event Mask2
    Uint16 MASK2_HWBP3:1;               // 10 Enhanced Bus Comparator (EBC) AND Event Mask2
    Uint16 MASK2_HWBP4:1;               // 11 Enhanced Bus Comparator (EBC) AND Event Mask2
    Uint16 MASK2_HWBP5:1;               // 12 Enhanced Bus Comparator (EBC) AND Event Mask2
    Uint16 MASK2_HWBP6:1;               // 13 Enhanced Bus Comparator (EBC) AND Event Mask2
    Uint16 MASK2_HWBP7:1;               // 14 Enhanced Bus Comparator (EBC) AND Event Mask2
    Uint16 MASK2_HWBP8:1;               // 15 Enhanced Bus Comparator (EBC) AND Event Mask2
    Uint16 MASK3_HWBP1:1;               // 16 Enhanced Bus Comparator (EBC) AND Event Mask3
    Uint16 MASK3_HWBP2:1;               // 17 Enhanced Bus Comparator (EBC) AND Event Mask3
    Uint16 MASK3_HWBP3:1;               // 18 Enhanced Bus Comparator (EBC) AND Event Mask3
    Uint16 MASK3_HWBP4:1;               // 19 Enhanced Bus Comparator (EBC) AND Event Mask3
    Uint16 MASK3_HWBP5:1;               // 20 Enhanced Bus Comparator (EBC) AND Event Mask3
    Uint16 MASK3_HWBP6:1;               // 21 Enhanced Bus Comparator (EBC) AND Event Mask3
    Uint16 MASK3_HWBP7:1;               // 22 Enhanced Bus Comparator (EBC) AND Event Mask3
    Uint16 MASK3_HWBP8:1;               // 23 Enhanced Bus Comparator (EBC) AND Event Mask3
    Uint16 MASK4_HWBP1:1;               // 24 Enhanced Bus Comparator (EBC) AND Event Mask4
    Uint16 MASK4_HWBP2:1;               // 25 Enhanced Bus Comparator (EBC) AND Event Mask4
    Uint16 MASK4_HWBP3:1;               // 26 Enhanced Bus Comparator (EBC) AND Event Mask4
    Uint16 MASK4_HWBP4:1;               // 27 Enhanced Bus Comparator (EBC) AND Event Mask4
    Uint16 MASK4_HWBP5:1;               // 28 Enhanced Bus Comparator (EBC) AND Event Mask4
    Uint16 MASK4_HWBP6:1;               // 29 Enhanced Bus Comparator (EBC) AND Event Mask4
    Uint16 MASK4_HWBP7:1;               // 30 Enhanced Bus Comparator (EBC) AND Event Mask4
    Uint16 MASK4_HWBP8:1;               // 31 Enhanced Bus Comparator (EBC) AND Event Mask4
};

union GLBL_EVENT_AND_MASK_REG {
    Uint32  all;
    struct  GLBL_EVENT_AND_MASK_BITS  bit;
};

struct GLBL_EVENT_OR_MASK_BITS {        // bits description
    Uint16 MASK1_HWBP1:1;               // 0 Enhanced Bus Comparator (EBC) OR Event Mask1
    Uint16 MASK1_HWBP2:1;               // 1 Enhanced Bus Comparator (EBC) OR Event Mask1
    Uint16 MASK1_HWBP3:1;               // 2 Enhanced Bus Comparator (EBC) OR Event Mask1
    Uint16 MASK1_HWBP4:1;               // 3 Enhanced Bus Comparator (EBC) OR Event Mask1
    Uint16 MASK1_HWBP5:1;               // 4 Enhanced Bus Comparator (EBC) OR Event Mask1
    Uint16 MASK1_HWBP6:1;               // 5 Enhanced Bus Comparator (EBC) OR Event Mask1
    Uint16 MASK1_HWBP7:1;               // 6 Enhanced Bus Comparator (EBC) OR Event Mask1
    Uint16 MASK1_HWBP8:1;               // 7 Enhanced Bus Comparator (EBC) OR Event Mask1
    Uint16 MASK2_HWBP1:1;               // 8 Enhanced Bus Comparator (EBC) OR Event Mask2
    Uint16 MASK2_HWBP2:1;               // 9 Enhanced Bus Comparator (EBC) OR Event Mask2
    Uint16 MASK2_HWBP3:1;               // 10 Enhanced Bus Comparator (EBC) OR Event Mask2
    Uint16 MASK2_HWBP4:1;               // 11 Enhanced Bus Comparator (EBC) OR Event Mask2
    Uint16 MASK2_HWBP5:1;               // 12 Enhanced Bus Comparator (EBC) OR Event Mask2
    Uint16 MASK2_HWBP6:1;               // 13 Enhanced Bus Comparator (EBC) OR Event Mask2
    Uint16 MASK2_HWBP7:1;               // 14 Enhanced Bus Comparator (EBC) OR Event Mask2
    Uint16 MASK2_HWBP8:1;               // 15 Enhanced Bus Comparator (EBC) OR Event Mask2
    Uint16 MASK3_HWBP1:1;               // 16 Enhanced Bus Comparator (EBC) OR Event Mask3
    Uint16 MASK3_HWBP2:1;               // 17 Enhanced Bus Comparator (EBC) OR Event Mask3
    Uint16 MASK3_HWBP3:1;               // 18 Enhanced Bus Comparator (EBC) OR Event Mask3
    Uint16 MASK3_HWBP4:1;               // 19 Enhanced Bus Comparator (EBC) OR Event Mask3
    Uint16 MASK3_HWBP5:1;               // 20 Enhanced Bus Comparator (EBC) OR Event Mask3
    Uint16 MASK3_HWBP6:1;               // 21 Enhanced Bus Comparator (EBC) OR Event Mask3
    Uint16 MASK3_HWBP7:1;               // 22 Enhanced Bus Comparator (EBC) OR Event Mask3
    Uint16 MASK3_HWBP8:1;               // 23 Enhanced Bus Comparator (EBC) OR Event Mask3
    Uint16 MASK4_HWBP1:1;               // 24 Enhanced Bus Comparator (EBC) OR Event Mask4
    Uint16 MASK4_HWBP2:1;               // 25 Enhanced Bus Comparator (EBC) OR Event Mask4
    Uint16 MASK4_HWBP3:1;               // 26 Enhanced Bus Comparator (EBC) OR Event Mask4
    Uint16 MASK4_HWBP4:1;               // 27 Enhanced Bus Comparator (EBC) OR Event Mask4
    Uint16 MASK4_HWBP5:1;               // 28 Enhanced Bus Comparator (EBC) OR Event Mask4
    Uint16 MASK4_HWBP6:1;               // 29 Enhanced Bus Comparator (EBC) OR Event Mask4
    Uint16 MASK4_HWBP7:1;               // 30 Enhanced Bus Comparator (EBC) OR Event Mask4
    Uint16 MASK4_HWBP8:1;               // 31 Enhanced Bus Comparator (EBC) OR Event Mask4
};

union GLBL_EVENT_OR_MASK_REG {
    Uint32  all;
    struct  GLBL_EVENT_OR_MASK_BITS  bit;
};

struct GLBL_AND_EVENT_INT_MASK_BITS {   // bits description
    Uint16 RTOSINT_MASK1:1;             // 0 RTOSINT generation mask for global AND events
    Uint16 RTOSINT_MASK2:1;             // 1 RTOSINT generation mask for global AND events
    Uint16 RTOSINT_MASK3:1;             // 2 RTOSINT generation mask for global AND events
    Uint16 RTOSINT_MASK4:1;             // 3 RTOSINT generation mask for global AND events
    Uint16 rsvd1:12;                    // 15:4 Reserved
};

union GLBL_AND_EVENT_INT_MASK_REG {
    Uint16  all;
    struct  GLBL_AND_EVENT_INT_MASK_BITS  bit;
};

struct GLBL_OR_EVENT_INT_MASK_BITS {    // bits description
    Uint16 RTOSINT_MASK1:1;             // 0 RTOSINT generation mask for global OR events
    Uint16 RTOSINT_MASK2:1;             // 1 RTOSINT generation mask for global OR events
    Uint16 RTOSINT_MASK3:1;             // 2 RTOSINT generation mask for global OR events
    Uint16 RTOSINT_MASK4:1;             // 3 RTOSINT generation mask for global OR events
    Uint16 rsvd1:12;                    // 15:4 Reserved
};

union GLBL_OR_EVENT_INT_MASK_REG {
    Uint16  all;
    struct  GLBL_OR_EVENT_INT_MASK_BITS  bit;
};

struct ERAD_GLOBAL_REGS {
    union   GLBL_EVENT_STAT_REG              GLBL_EVENT_STAT;              // Global Event Status Register
    Uint16                                   rsvd1;                        // Reserved
    union   GLBL_HALT_STAT_REG               GLBL_HALT_STAT;               // Global Halt Status Register
    Uint16                                   rsvd2;                        // Reserved
    union   GLBL_ENABLE_REG                  GLBL_ENABLE;                  // Global Enable Register
    Uint16                                   rsvd3;                        // Reserved
    union   GLBL_CTM_RESET_REG               GLBL_CTM_RESET;               // Global Counter Reset
    Uint16                                   rsvd4;                        // Reserved
    union   GLBL_NMI_CTL_REG                 GLBL_NMI_CTL;                 // Global Debug NMI control
    Uint16                                   rsvd5;                        // Reserved
    union   GLBL_OWNER_REG                   GLBL_OWNER;                   // Global Ownership
    Uint16                                   rsvd6;                        // Reserved
    union   GLBL_EVENT_AND_MASK_REG          GLBL_EVENT_AND_MASK;          // Global Bus Comparator Event AND Mask Register
    union   GLBL_EVENT_OR_MASK_REG           GLBL_EVENT_OR_MASK;           // Global Bus Comparator Event OR Mask Register
    union   GLBL_AND_EVENT_INT_MASK_REG      GLBL_AND_EVENT_INT_MASK;      // Global AND Event Interrupt Mask Register
    Uint16                                   rsvd7;                        // Reserved
    union   GLBL_OR_EVENT_INT_MASK_REG       GLBL_OR_EVENT_INT_MASK;       // Global OR Event Interrupt Mask Register
};

struct HWBP_CLEAR_BITS {                // bits description
    Uint16 EVENT_CLR:1;                 // 0 Event Clear register
    Uint16 rsvd1:15;                    // 15:1 Reserved
};

union HWBP_CLEAR_REG {
    Uint16  all;
    struct  HWBP_CLEAR_BITS  bit;
};

struct HWBP_CNTL_BITS {                 // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 BUS_SEL:4;                   // 4:1 Bus select bits
    Uint16 STOP:1;                      // 5 Stop bit (Halt/No Halt of CPU)
    Uint16 RTOSINT:1;                   // 6 RTOSINT bit
    Uint16 COMP_MODE:3;                 // 9:7 Compare mode
    Uint16 rsvd2:1;                     // 10 Reserved
    Uint16 rsvd3:1;                     // 11 Reserved
    Uint16 rsvd4:4;                     // 15:12 Reserved
};

union HWBP_CNTL_REG {
    Uint16  all;
    struct  HWBP_CNTL_BITS  bit;
};

struct HWBP_STATUS_BITS {               // bits description
    Uint16 EVENT_FIRED:1;               // 0 HWBP (EBC) Event Fired bits
    Uint16 rsvd1:7;                     // 7:1 Reserved
    Uint16 MODULE_ID:6;                 // 13:8 Identification bits
    Uint16 STATUS:2;                    // 15:14 Status bits
};

union HWBP_STATUS_REG {
    Uint16  all;
    struct  HWBP_STATUS_BITS  bit;
};

struct ERAD_HWBP_REGS {
    Uint32                                   HWBP_MASK;                    // HWBP (EBC) Mask Register
    Uint32                                   HWBP_REF;                     // HWBP (EBC) Reference Register
    union   HWBP_CLEAR_REG                   HWBP_CLEAR;                   // HWBP (EBC) Clear Register
    Uint16                                   rsvd1;                        // Reserved
    union   HWBP_CNTL_REG                    HWBP_CNTL;                    // HWBP (EBC) Control Register
    union   HWBP_STATUS_REG                  HWBP_STATUS;                  // HWBP (EBC) Status Register
};

struct CTM_CNTL_BITS {                  // bits description
    Uint16 rsvd1:2;                     // 1:0 Reserved
    Uint16 START_STOP_MODE:1;           // 2 Start_stop mode bit
    Uint16 EVENT_MODE:1;                // 3 Event mode bit
    Uint16 RST_ON_MATCH:1;              // 4 Reset_on_match bit
    Uint16 rsvd2:1;                     // 5 Reserved
    Uint16 STOP:1;                      // 6 Stop bit (Halt/No Halt of CPU)
    Uint16 RTOSINT:1;                   // 7 RTOSINT bit
    Uint16 START_STOP_CUMULATIVE:1;     // 8 Start stop cumulative bit
    Uint16 rsvd3:1;                     // 9 Reserved
    Uint16 RST_EN:1;                    // 10 Enable Reset
    Uint16 CNT_INP_SEL_EN:1;            // 11 Counter Input Select Enable
    Uint16 rsvd4:4;                     // 15:12 Reserved
};

union CTM_CNTL_REG {
    Uint16  all;
    struct  CTM_CNTL_BITS  bit;
};

struct CTM_STATUS_BITS {                // bits description
    Uint16 EVENT_FIRED:1;               // 0 Counter Event Fired bits
    Uint16 OVERFLOW:1;                  // 1 Counter Overflowed
    Uint16 MODULE_ID:10;                // 11:2 Identification bits
    Uint16 STATUS:4;                    // 15:12 Status bits
};

union CTM_STATUS_REG {
    Uint16  all;
    struct  CTM_STATUS_BITS  bit;
};

struct CTM_INPUT_SEL_BITS {             // bits description
    Uint16 CNT_INP_SEL:8;               // 7:0 Counter Input Select
    Uint16 STA_INP_SEL:8;               // 15:8 Counter Sart Input Select
};

union CTM_INPUT_SEL_REG {
    Uint16  all;
    struct  CTM_INPUT_SEL_BITS  bit;
};

struct CTM_CLEAR_BITS {                 // bits description
    Uint16 EVENT_CLEAR:1;               // 0 Clear EVENT_FIRED
    Uint16 OVERFLOW_CLEAR:1;            // 1 Clear OVERFLOW
    Uint16 rsvd1:14;                    // 15:2 Reserved
};

union CTM_CLEAR_REG {
    Uint16  all;
    struct  CTM_CLEAR_BITS  bit;
};

struct CTM_INPUT_SEL_2_BITS {           // bits description
    Uint16 STO_INP_SEL:8;               // 7:0 Counter Stop Input Select
    Uint16 RST_INP_SEL:8;               // 15:8 Counter Reset input Select
};

union CTM_INPUT_SEL_2_REG {
    Uint16  all;
    struct  CTM_INPUT_SEL_2_BITS  bit;
};

struct CTM_INPUT_COND_BITS {            // bits description
    Uint16 CTM_INP_INV:1;               // 0 Counter Input Invert
    Uint16 CTM_INP_SYNCH:1;             // 1 Counter input synchronizer enable
    Uint16 rsvd1:2;                     // 3:2 Reserved
    Uint16 STA_INP_INV:1;               // 4 Start input Invert
    Uint16 STA_INP_SYNCH:1;             // 5 Start input synchronizer enable
    Uint16 rsvd2:2;                     // 7:6 Reserved
    Uint16 STO_INP_INV:1;               // 8 Stop input Invert
    Uint16 STO_INP_SYNCH:1;             // 9 Stop input synchronizer enable
    Uint16 rsvd3:2;                     // 11:10 Reserved
    Uint16 RST_INP_INV:1;               // 12 Reset input Invert
    Uint16 RST_INP_SYNCH:1;             // 13 Reset input synchronizer enable
    Uint16 rsvd4:2;                     // 15:14 Reserved
};

union CTM_INPUT_COND_REG {
    Uint16  all;
    struct  CTM_INPUT_COND_BITS  bit;
};

struct ERAD_COUNTER_REGS {
    union   CTM_CNTL_REG                     CTM_CNTL;                     // Counter Control Register
    union   CTM_STATUS_REG                   CTM_STATUS;                   // Counter Status Register
    Uint32                                   CTM_REF;                      // Counter Reference Register
    Uint32                                   CTM_COUNT;                    // Counter Current Value Register
    Uint32                                   CTM_MAX_COUNT;                // Counter Max Count Value Register
    union   CTM_INPUT_SEL_REG                CTM_INPUT_SEL;                // Counter Input Select Register
    union   CTM_CLEAR_REG                    CTM_CLEAR;                    // Counter Clear Register
    union   CTM_INPUT_SEL_2_REG              CTM_INPUT_SEL_2;              // Counter Input Select Extension Register
    union   CTM_INPUT_COND_REG               CTM_INPUT_COND;               // Counter Input Conditioning Register
};

struct CRC_GLOBAL_CTRL_BITS {           // bits description
    Uint16 CRC1_INIT:1;                 // 0 Initialize CRC Module 1
    Uint16 CRC2_INIT:1;                 // 1 Initialize CRC Module 2
    Uint16 CRC3_INIT:1;                 // 2 Initialize CRC Module 3
    Uint16 CRC4_INIT:1;                 // 3 Initialize CRC Module 4
    Uint16 CRC5_INIT:1;                 // 4 Initialize CRC Module 5
    Uint16 CRC6_INIT:1;                 // 5 Initialize CRC Module 6
    Uint16 CRC7_INIT:1;                 // 6 Initialize CRC Module 7
    Uint16 CRC8_INIT:1;                 // 7 Initialize CRC Module 8
    Uint16 CRC1_EN:1;                   // 8 Enable CRC Module 1
    Uint16 CRC2_EN:1;                   // 9 Enable CRC Module 2
    Uint16 CRC3_EN:1;                   // 10 Enable CRC Module 3
    Uint16 CRC4_EN:1;                   // 11 Enable CRC Module 4
    Uint16 CRC5_EN:1;                   // 12 Enable CRC Module 5
    Uint16 CRC6_EN:1;                   // 13 Enable CRC Module 6
    Uint16 CRC7_EN:1;                   // 14 Enable CRC Module 7
    Uint16 CRC8_EN:1;                   // 15 Enable CRC Module 8
};

union CRC_GLOBAL_CTRL_REG {
    Uint16  all;
    struct  CRC_GLOBAL_CTRL_BITS  bit;
};

struct ERAD_CRC_GLOBAL_REGS {
    union   CRC_GLOBAL_CTRL_REG              CRC_GLOBAL_CTRL;              // CRC_GLOBAL_CRTL
};

struct CRC_QUALIFIER_BITS {             // bits description
    Uint16 CRC_QUALIFIER:5;             // 4:0 CRC Qualifier Register
    Uint16 rsvd1:11;                    // 15:5 Reserved
};

union CRC_QUALIFIER_REG {
    Uint16  all;
    struct  CRC_QUALIFIER_BITS  bit;
};

struct ERAD_CRC_REGS {
    Uint32                                   CRC_CURRENT;                  // CRC_CURRENT
    Uint32                                   CRC_SEED;                     // CRC SEED value
    union   CRC_QUALIFIER_REG                CRC_QUALIFIER;                // CRC_QUALIFIER
};

struct PCTRACE_GLOBAL_BITS {            // bits description
    Uint16 EN:1;                        // 0 Enable PC  trace
    Uint16 rsvd1:7;                     // 7:1 Reserved
    Uint16 INIT:1;                      // 8 Initialize the PC Trace and buffer pointer
    Uint16 rsvd2:7;                     // 15:9 Reserved
};

union PCTRACE_GLOBAL_REG {
    Uint16  all;
    struct  PCTRACE_GLOBAL_BITS  bit;
};

struct PCTRACE_BUFFER_BITS {            // bits description
    Uint16 PTR:10;                      // 9:0 Trace Buffer Pointer
    Uint16 rsvd1:5;                     // 14:10 Reserved
    Uint16 BUFFER_FULL:1;               // 15 Trace Buffer Full
};

union PCTRACE_BUFFER_REG {
    Uint16  all;
    struct  PCTRACE_BUFFER_BITS  bit;
};

struct PCTRACE_QUAL1_BITS {             // bits description
    Uint16 WINDOWED_INP_SEL:8;          // 7:0 Windowed trace qualifier
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 TRACE_MODE:2;                // 17:16 Trace qualifier mode
    Uint16 WINDOWED_INP_INV:1;          // 18 Windowed trace Input Invert
    Uint16 WINDOWED_INP_SYNCH:1;        // 19 Windowed trace input synchronizer enable
    Uint16 START_INP_INV:1;             // 20 Start input Invert
    Uint16 START_INP_SYNCH:1;           // 21 Start input synchronizer enable
    Uint16 STOP_INP_INV:1;              // 22 Stop input Invert
    Uint16 STOP_INP_SYNCH:1;            // 23 Stop input synchronizer enable
    Uint16 rsvd2:8;                     // 31:24 Reserved
};

union PCTRACE_QUAL1_REG {
    Uint32  all;
    struct  PCTRACE_QUAL1_BITS  bit;
};

struct PCTRACE_QUAL2_BITS {             // bits description
    Uint16 START_INP_SEL:8;             // 7:0 Trace Start event select
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 STOP_INP_SEL:8;              // 23:16 Trace Stop event select
    Uint16 rsvd2:8;                     // 31:24 Reserved
};

union PCTRACE_QUAL2_REG {
    Uint32  all;
    struct  PCTRACE_QUAL2_BITS  bit;
};

struct PCTRACE_LOGPC_SOFTENABLE_BITS {  // bits description
    Uint32 PC_SOFTENABLE:22;            // 21:0 PC when PC Trace was last enabled by software
    Uint16 rsvd1:10;                    // 31:22 Reserved
};

union PCTRACE_LOGPC_SOFTENABLE_REG {
    Uint32  all;
    struct  PCTRACE_LOGPC_SOFTENABLE_BITS  bit;
};

struct PCTRACE_LOGPC_SOFTDISABLE_BITS { // bits description
    Uint32 PC_SOFTDISABLE:22;           // 21:0 PC when PC Trace was last disabled by software
    Uint16 rsvd1:10;                    // 31:22 Reserved
};

union PCTRACE_LOGPC_SOFTDISABLE_REG {
    Uint32  all;
    struct  PCTRACE_LOGPC_SOFTDISABLE_BITS  bit;
};

struct PCTRACE_REGS {
    union   PCTRACE_GLOBAL_REG               PCTRACE_GLOBAL;               // PCTRACE_GLOBAL
    union   PCTRACE_BUFFER_REG               PCTRACE_BUFFER;               // PCTRACE_BUFFER
    union   PCTRACE_QUAL1_REG                PCTRACE_QUAL1;                // PCTRACE_QUAL1
    union   PCTRACE_QUAL2_REG                PCTRACE_QUAL2;                // PCTRACE_QUAL2
    union   PCTRACE_LOGPC_SOFTENABLE_REG     PCTRACE_LOGPC_SOFTENABLE;     // PCTRACE_LOGPC_SOFTENABLE
    union   PCTRACE_LOGPC_SOFTDISABLE_REG    PCTRACE_LOGPC_SOFTDISABLE;    // PCTRACE_LOGPC_SOFTDISABLE
};

struct PCTRACE_BUFFER_BASE_BITS {       // bits description
    Uint32 PROGRAM_COUNTER:22;          // 21:0 Program Counter
    Uint16 BLOCKED:1;                   // 22 Access blocked due to security
    Uint16 rsvd1:9;                     // 31:23 Reserved
};

union PCTRACE_BUFFER_BASE_REG {
    Uint32  all;
    struct  PCTRACE_BUFFER_BASE_BITS  bit;
};

struct PCTRACE_BUFFER_REGS {
    union   PCTRACE_BUFFER_BASE_REG          PCTRACE_BUFFER_BASE[1024];    // PCTRACE_BUFFER_BASE
};

//---------------------------------------------------------------------------
// ERAD External References & Function Declarations:
//
#ifdef CPU1
extern volatile struct ERAD_GLOBAL_REGS EradGlobalRegs;
extern volatile struct ERAD_HWBP_REGS EradHWBP1Regs;
extern volatile struct ERAD_HWBP_REGS EradHWBP2Regs;
extern volatile struct ERAD_HWBP_REGS EradHWBP3Regs;
extern volatile struct ERAD_HWBP_REGS EradHWBP4Regs;
extern volatile struct ERAD_HWBP_REGS EradHWBP5Regs;
extern volatile struct ERAD_HWBP_REGS EradHWBP6Regs;
extern volatile struct ERAD_HWBP_REGS EradHWBP7Regs;
extern volatile struct ERAD_HWBP_REGS EradHWBP8Regs;
extern volatile struct ERAD_COUNTER_REGS EradCounter1Regs;
extern volatile struct ERAD_COUNTER_REGS EradCounter2Regs;
extern volatile struct ERAD_COUNTER_REGS EradCounter3Regs;
extern volatile struct ERAD_COUNTER_REGS EradCounter4Regs;
extern volatile struct ERAD_CRC_GLOBAL_REGS EradCRCGlobalRegs;
extern volatile struct ERAD_CRC_REGS EradCRC1Regs;
extern volatile struct ERAD_CRC_REGS EradCRC2Regs;
extern volatile struct ERAD_CRC_REGS EradCRC3Regs;
extern volatile struct ERAD_CRC_REGS EradCRC4Regs;
extern volatile struct ERAD_CRC_REGS EradCRC5Regs;
extern volatile struct ERAD_CRC_REGS EradCRC6Regs;
extern volatile struct ERAD_CRC_REGS EradCRC7Regs;
extern volatile struct ERAD_CRC_REGS EradCRC8Regs;
extern volatile struct PCTRACE_REGS EradPCTraceRegs;
#endif
#ifdef CPU2
extern volatile struct ERAD_GLOBAL_REGS EradGlobalRegs;
extern volatile struct ERAD_HWBP_REGS EradHWBP1Regs;
extern volatile struct ERAD_HWBP_REGS EradHWBP2Regs;
extern volatile struct ERAD_HWBP_REGS EradHWBP3Regs;
extern volatile struct ERAD_HWBP_REGS EradHWBP4Regs;
extern volatile struct ERAD_HWBP_REGS EradHWBP5Regs;
extern volatile struct ERAD_HWBP_REGS EradHWBP6Regs;
extern volatile struct ERAD_HWBP_REGS EradHWBP7Regs;
extern volatile struct ERAD_HWBP_REGS EradHWBP8Regs;
extern volatile struct ERAD_COUNTER_REGS EradCounter1Regs;
extern volatile struct ERAD_COUNTER_REGS EradCounter2Regs;
extern volatile struct ERAD_COUNTER_REGS EradCounter3Regs;
extern volatile struct ERAD_COUNTER_REGS EradCounter4Regs;
extern volatile struct ERAD_CRC_GLOBAL_REGS EradCRCGlobalRegs;
extern volatile struct ERAD_CRC_REGS EradCRC1Regs;
extern volatile struct ERAD_CRC_REGS EradCRC2Regs;
extern volatile struct ERAD_CRC_REGS EradCRC3Regs;
extern volatile struct ERAD_CRC_REGS EradCRC4Regs;
extern volatile struct ERAD_CRC_REGS EradCRC5Regs;
extern volatile struct ERAD_CRC_REGS EradCRC6Regs;
extern volatile struct ERAD_CRC_REGS EradCRC7Regs;
extern volatile struct ERAD_CRC_REGS EradCRC8Regs;
extern volatile struct PCTRACE_REGS EradPCTraceRegs;
#endif
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
