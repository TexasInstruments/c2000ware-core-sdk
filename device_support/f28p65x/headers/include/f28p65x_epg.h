//###########################################################################
//
// FILE:    f28p65x_epg.h
//
// TITLE:   Definitions for the EPG registers.
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

#ifndef F28P65X_EPG_H
#define F28P65X_EPG_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// EPG Individual Register Bit Definitions:

struct GCTL0_BITS {                     // bits description
    Uint16 EN:1;                        // 0 Enable EPG
    Uint16 SIGGEN0_EN:1;                // 1 Signal generator enable
    Uint16 SIGGEN1_EN:1;                // 2 Signal generator enable
    Uint16 rsvd1:5;                     // 7:3 Reserved
    Uint16 EPGOUT13SEL:1;               // 8 EPG output 13 Clock/signal select
    Uint16 EPGOUT15SEL:1;               // 9 EPG output 15 Clock/signal select
    Uint16 EPGOUT16SEL:1;               // 10 EPG output 16 Clock/signal select
    Uint16 EPGOUT17SEL:1;               // 11 EPG output 17 Clock/signal select
    Uint16 EPGOUT20SEL:1;               // 12 EPG output 20 Clock/signal select
    Uint16 EPGOUT21SEL:1;               // 13 EPG output 21 Clock/signal select
    Uint16 EPGOUT22SEL:1;               // 14 EPG output 22 Clock/signal select
    Uint16 EPGOUT23SEL:1;               // 15 EPG output 23 Clock/signal select
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union GCTL0_REG {
    Uint32  all;
    struct  GCTL0_BITS  bit;
};

struct GCTL1_BITS {                     // bits description
    Uint16 SIGGEN0_CLKSEL:3;            // 2:0 Clock source select of SIGGEN0
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 rsvd2:3;                     // 6:4 Reserved
    Uint16 rsvd3:1;                     // 7 Reserved
    Uint16 rsvd4:8;                     // 15:8 Reserved
    Uint16 rsvd5:16;                    // 31:16 Reserved
};

union GCTL1_REG {
    Uint32  all;
    struct  GCTL1_BITS  bit;
};

struct GCTL2_BITS {                     // bits description
    Uint16 EPGOUT0_CLKOUTSEL:3;         // 2:0 Selects the clock signal source of EPG output 0.
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 EPGOUT1_CLKOUTSEL:3;         // 6:4 Selects the clock signal source of EPG output 1.
    Uint16 rsvd2:1;                     // 7 Reserved
    Uint16 EPGOUT2_CLKOUTSEL:3;         // 10:8 Selects the clock signal source of EPG output 2.
    Uint16 rsvd3:1;                     // 11 Reserved
    Uint16 EPGOUT3_CLKOUTSEL:3;         // 14:12 Selects the clock signal source of EPG output 3.
    Uint16 rsvd4:1;                     // 15 Reserved
    Uint16 EPGOUT4_CLKOUTSEL:3;         // 18:16 Selects the clock signal source of EPG output 4.
    Uint16 rsvd5:1;                     // 19 Reserved
    Uint16 EPGOUT5_CLKOUTSEL:3;         // 22:20 Selects the clock signal source of EPG output 5.
    Uint16 rsvd6:1;                     // 23 Reserved
    Uint16 EPGOUT6_CLKOUTSEL:3;         // 26:24 Selects the clock signal source of EPG output 6.
    Uint16 rsvd7:1;                     // 27 Reserved
    Uint16 EPGOUT7_CLKOUTSEL:3;         // 30:28 Selects the clock signal source of EPG output 7.
    Uint16 rsvd8:1;                     // 31 Reserved
};

union GCTL2_REG {
    Uint32  all;
    struct  GCTL2_BITS  bit;
};

struct GCTL3_BITS {                     // bits description
    Uint16 EPGOUT0_SIGOUTSEL:4;         // 3:0 Selects the signal source of EPG output 0.
    Uint16 EPGOUT1_SIGOUTSEL:4;         // 7:4 Selects the signal source of EPG output 1.
    Uint16 EPGOUT2_SIGOUTSEL:4;         // 11:8 Selects the signal source of EPG output 2.
    Uint16 EPGOUT3_SIGOUTSEL:4;         // 15:12 Selects the signal source of EPG output 3.
    Uint16 EPGOUT4_SIGOUTSEL:4;         // 19:16 Selects the signal source of EPG output 4.
    Uint16 EPGOUT5_SIGOUTSEL:4;         // 23:20 Selects the signal source of EPG output 5.
    Uint16 EPGOUT6_SIGOUTSEL:4;         // 27:24 Selects the signal source of EPG output 6.
    Uint16 EPGOUT7_SIGOUTSEL:4;         // 31:28 Selects the signal source of EPG output 7.
};

union GCTL3_REG {
    Uint32  all;
    struct  GCTL3_BITS  bit;
};

struct EPGLOCK_BITS {                   // bits description
    Uint16 GCTL0:1;                     // 0 GCTL0 Lock bit
    Uint16 GCTL1:1;                     // 1 GCTL1 Lock bit
    Uint16 GCTL2:1;                     // 2 GCTL2 Lock bit
    Uint16 GCTL3:1;                     // 3 GCTL3 Lock bit
    Uint16 CLKDIV0_CTL0:1;              // 4 CLKDIV0_CTL0 Lock bit
    Uint16 CLKDIV1_CTL0:1;              // 5 CLKDIV1_CTL0 Lock bit
    Uint16 SIGGEN0_CTL0:1;              // 6 SIGGEN0_CTL0 Lock bit
    Uint16 SIGGEN0_CTL1:1;              // 7 SIGGEN0_CTL1 Lock bit
    Uint16 rsvd1:1;                     // 8 Reserved
    Uint16 rsvd2:1;                     // 9 Reserved
    Uint16 rsvd3:6;                     // 15:10 Reserved
    Uint16 rsvd4:16;                    // 31:16 Reserved
};

union EPGLOCK_REG {
    Uint32  all;
    struct  EPGLOCK_BITS  bit;
};

struct EPGCOMMIT_BITS {                 // bits description
    Uint16 GCTL0:1;                     // 0 GCTL0 Commit bit
    Uint16 GCTL1:1;                     // 1 GCTL1 Commit bit
    Uint16 GCTL2:1;                     // 2 GCTL2 Commit bit
    Uint16 GCTL3:1;                     // 3 GCTL3 Commit bit
    Uint16 CLKDIV0_CTL0:1;              // 4 CLKDIV0_CTL0 Commit bit
    Uint16 CLKDIV1_CTL0:1;              // 5 CLKDIV1_CTL0 Commit bit
    Uint16 SIGGEN0_CTL0:1;              // 6 SIGGEN0_CTL0 Commit bit
    Uint16 SIGGEN0_CTL1:1;              // 7 SIGGEN0_CTL1 Commit bit
    Uint16 rsvd1:1;                     // 8 Reserved
    Uint16 rsvd2:1;                     // 9 Reserved
    Uint16 rsvd3:6;                     // 15:10 Reserved
    Uint16 rsvd4:16;                    // 31:16 Reserved
};

union EPGCOMMIT_REG {
    Uint32  all;
    struct  EPGCOMMIT_BITS  bit;
};

struct GINTSTS_BITS {                   // bits description
    Uint16 INT:1;                       // 0 Global interrupt flag register
    Uint16 SIGGEN0_DONE:1;              // 1 SIGGEN0 operation done status
    Uint16 SIGGEN0_FILL:1;              // 2 SIGGEN0 data fill status
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 rsvd2:1;                     // 4 Reserved
    Uint16 rsvd3:11;                    // 15:5 Reserved
    Uint16 rsvd4:16;                    // 31:16 Reserved
};

union GINTSTS_REG {
    Uint32  all;
    struct  GINTSTS_BITS  bit;
};

struct GINTEN_BITS {                    // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 SIGGEN0_DONE:1;              // 1 SIGGEN0 operation done interrupt enable
    Uint16 SIGGEN0_FILL:1;              // 2 SIGGEN0 data fill interrupt enable
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 rsvd3:1;                     // 4 Reserved
    Uint16 rsvd4:11;                    // 15:5 Reserved
    Uint16 rsvd5:16;                    // 31:16 Reserved
};

union GINTEN_REG {
    Uint32  all;
    struct  GINTEN_BITS  bit;
};

struct GINTCLR_BITS {                   // bits description
    Uint16 INT:1;                       // 0 Global interrupt flag clear
    Uint16 SIGGEN0_DONE:1;              // 1 SIGGEN0 operation done interrupt flag clear
    Uint16 SIGGEN0_FILL:1;              // 2 SIGGEN0 data fill interrupt flag clear
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 rsvd2:1;                     // 4 Reserved
    Uint16 rsvd3:11;                    // 15:5 Reserved
    Uint16 rsvd4:16;                    // 31:16 Reserved
};

union GINTCLR_REG {
    Uint32  all;
    struct  GINTCLR_BITS  bit;
};

struct GINTFRC_BITS {                   // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 SIGGEN0_DONE:1;              // 1 SIGGEN0 operation done interrupt flag set
    Uint16 SIGGEN0_FILL:1;              // 2 SIGGEN0 data fill interrupt flag set
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 rsvd3:1;                     // 4 Reserved
    Uint16 rsvd4:11;                    // 15:5 Reserved
    Uint16 rsvd5:16;                    // 31:16 Reserved
};

union GINTFRC_REG {
    Uint32  all;
    struct  GINTFRC_BITS  bit;
};

struct CLKDIV0_CTL0_BITS {              // bits description
    Uint16 PRD:16;                      // 15:0 Clock divider value
    Uint16 CLKSTOP:3;                   // 18:16 Clock Stop Configuration
    Uint16 rsvd1:13;                    // 31:19 Reserved
};

union CLKDIV0_CTL0_REG {
    Uint32  all;
    struct  CLKDIV0_CTL0_BITS  bit;
};

struct CLKDIV0_CLKOFFSET_BITS {         // bits description
    Uint16 CLK0OFFSET:8;                // 7:0 Clock output 0 offset delay value.
    Uint16 CLK1OFFSET:8;                // 15:8 Clock output 0 offset delay value.
    Uint16 CLK2OFFSET:8;                // 23:16 Clock output 0 offset delay value.
    Uint16 CLK3OFFSET:8;                // 31:24 Clock output 0 offset delay value.
};

union CLKDIV0_CLKOFFSET_REG {
    Uint32  all;
    struct  CLKDIV0_CLKOFFSET_BITS  bit;
};

struct CLKDIV1_CTL0_BITS {              // bits description
    Uint16 PRD:16;                      // 15:0 Clock divider value
    Uint16 CLKSTOP:3;                   // 18:16 Clock Stop Configuration
    Uint16 rsvd1:13;                    // 31:19 Reserved
};

union CLKDIV1_CTL0_REG {
    Uint32  all;
    struct  CLKDIV1_CTL0_BITS  bit;
};

struct CLKDIV1_CLKOFFSET_BITS {         // bits description
    Uint16 CLK0OFFSET:8;                // 7:0 Clock output 0 offset delay value.
    Uint16 CLK1OFFSET:8;                // 15:8 Clock output 0 offset delay value.
    Uint16 CLK2OFFSET:8;                // 23:16 Clock output 0 offset delay value.
    Uint16 CLK3OFFSET:8;                // 31:24 Clock output 0 offset delay value.
};

union CLKDIV1_CLKOFFSET_REG {
    Uint32  all;
    struct  CLKDIV1_CLKOFFSET_BITS  bit;
};

struct SIGGEN0_CTL0_BITS {              // bits description
    Uint16 MODE:4;                      // 3:0 Signal generator modes
    Uint16 rsvd1:1;                     // 4 Reserved
    Uint16 BRIN:1;                      // 5 Reverse bits before transform
    Uint16 BROUT:1;                     // 6 Reverse bits after transform
    Uint16 rsvd2:9;                     // 15:7 Reserved
    Uint16 BITLENGTH:8;                 // 23:16 Length of bit stream
    Uint16 rsvd3:8;                     // 31:24 Reserved
};

union SIGGEN0_CTL0_REG {
    Uint32  all;
    struct  SIGGEN0_CTL0_BITS  bit;
};

struct SIGGEN0_CTL1_BITS {              // bits description
    Uint16 DATA0_INSEL:4;               // 3:0 Select the source of DATA[0] bit.
    Uint16 rsvd1:12;                    // 15:4 Reserved
    Uint16 rsvd2:12;                    // 27:16 Reserved
    Uint16 DATA63_INSEL:4;              // 31:28 Select the source of DATA[63] bit.
};

union SIGGEN0_CTL1_REG {
    Uint32  all;
    struct  SIGGEN0_CTL1_BITS  bit;
};

struct REVISION_BITS {                  // bits description
    Uint16 MINOR:6;                     // 5:0 Minor Revision Number
    Uint16 CUSTOM:2;                    // 7:6 Custom Module Number
    Uint16 MAJOR:3;                     // 10:8 Major Revision Number
    Uint16 rsvd1:5;                     // 15:11 Reserved
    Uint16 FUNC:12;                     // 27:16 Functional Release Number
    Uint16 rsvd2:2;                     // 29:28 Reserved
    Uint16 SCHEME:2;                    // 31:30 Defines Scheme for Module
};

union REVISION_REG {
    Uint32  all;
    struct  REVISION_BITS  bit;
};

struct EPG_REGS {
    union   GCTL0_REG                        GCTL0;                        // EPG Global control register 0
    union   GCTL1_REG                        GCTL1;                        // EPG Global control register 1
    union   GCTL2_REG                        GCTL2;                        // EPG Global control register 2
    union   GCTL3_REG                        GCTL3;                        // EPG Global control register 3
    union   EPGLOCK_REG                      EPGLOCK;                      // EPG LOCK Register
    union   EPGCOMMIT_REG                    EPGCOMMIT;                    // EPG COMMIT register
    union   GINTSTS_REG                      GINTSTS;                      // EPG Global interrupt status register.
    union   GINTEN_REG                       GINTEN;                       // EPG Global interrupt enable register.
    union   GINTCLR_REG                      GINTCLR;                      // EPG Global interrupt clear register.
    union   GINTFRC_REG                      GINTFRC;                      // EPG Global interrupt force register.
    Uint16                                   rsvd1[4];                     // Reserved
    union   CLKDIV0_CTL0_REG                 CLKDIV0_CTL0;                 // Clock divider 0's control register 0
    Uint16                                   rsvd2[4];                     // Reserved
    union   CLKDIV0_CLKOFFSET_REG            CLKDIV0_CLKOFFSET;            // Clock divider 0's clock offset value
    Uint16                                   rsvd3[4];                     // Reserved
    union   CLKDIV1_CTL0_REG                 CLKDIV1_CTL0;                 // Clock divider 1's control register 0
    Uint16                                   rsvd4[4];                     // Reserved
    union   CLKDIV1_CLKOFFSET_REG            CLKDIV1_CLKOFFSET;            // Clock divider 1's clock offset value
    Uint16                                   rsvd5[4];                     // Reserved
    union   SIGGEN0_CTL0_REG                 SIGGEN0_CTL0;                 // Signal generator 0's control register 0
    union   SIGGEN0_CTL1_REG                 SIGGEN0_CTL1;                 // Signal generator 0's control register 1
    Uint16                                   rsvd6[4];                     // Reserved
    Uint32                                   SIGGEN0_DATA0;                // Signal generator 0's data register 0
    Uint32                                   SIGGEN0_DATA1;                // Signal generator 0's data register 1
    Uint32                                   SIGGEN0_DATA0_ACTIVE;         // Signal generator 0's data active register 0
    Uint32                                   SIGGEN0_DATA1_ACTIVE;         // Signal generator 0's data active register 1
    Uint16                                   rsvd7[16];                    // Reserved
    union   REVISION_REG                     REVISION;                     // IP Revision tie-off value
};

struct EPGMXSEL0_BITS {                 // bits description
    Uint16 SEL0:1;                      // 0 DATAOUT[0] mux select.
    Uint16 SEL1:1;                      // 1 DATAOUT[1] mux select.
    Uint16 SEL2:1;                      // 2 DATAOUT[2] mux select.
    Uint16 SEL3:1;                      // 3 DATAOUT[3] mux select.
    Uint16 SEL4:1;                      // 4 DATAOUT[4] mux select.
    Uint16 SEL5:1;                      // 5 DATAOUT[5] mux select.
    Uint16 SEL6:1;                      // 6 DATAOUT[6] mux select.
    Uint16 SEL7:1;                      // 7 DATAOUT[7] mux select.
    Uint16 SEL8:1;                      // 8 DATAOUT[8] mux select.
    Uint16 SEL9:1;                      // 9 DATAOUT[9] mux select.
    Uint16 SEL10:1;                     // 10 DATAOUT[10] mux select.
    Uint16 SEL11:1;                     // 11 DATAOUT[11] mux select.
    Uint16 SEL12:1;                     // 12 DATAOUT[12] mux select.
    Uint16 SEL13:1;                     // 13 DATAOUT[13] mux select.
    Uint16 SEL14:1;                     // 14 DATAOUT[14] mux select.
    Uint16 SEL15:1;                     // 15 DATAOUT[15] mux select.
    Uint16 SEL16:1;                     // 16 DATAOUT[16] mux select.
    Uint16 SEL17:1;                     // 17 DATAOUT[17] mux select.
    Uint16 SEL18:1;                     // 18 DATAOUT[18] mux select.
    Uint16 SEL19:1;                     // 19 DATAOUT[19] mux select.
    Uint16 SEL20:1;                     // 20 DATAOUT[20] mux select.
    Uint16 SEL21:1;                     // 21 DATAOUT[21] mux select.
    Uint16 SEL22:1;                     // 22 DATAOUT[22] mux select.
    Uint16 SEL23:1;                     // 23 DATAOUT[23] mux select.
    Uint16 SEL24:1;                     // 24 DATAOUT[24] mux select.
    Uint16 SEL25:1;                     // 25 DATAOUT[25] mux select.
    Uint16 SEL26:1;                     // 26 DATAOUT[26] mux select.
    Uint16 SEL27:1;                     // 27 DATAOUT[27] mux select.
    Uint16 SEL28:1;                     // 28 DATAOUT[28] mux select.
    Uint16 SEL29:1;                     // 29 DATAOUT[29] mux select.
    Uint16 SEL30:1;                     // 30 DATAOUT[30] mux select.
    Uint16 SEL31:1;                     // 31 DATAOUT[31] mux select.
};

union EPGMXSEL0_REG {
    Uint32  all;
    struct  EPGMXSEL0_BITS  bit;
};

struct EPGMXSELLOCK_BITS {              // bits description
    Uint16 EPGMXSEL0:1;                 // 0 EPGMXSEL0 lock bit
    Uint16 rsvd1:1;                     // 1 Reserved
    Uint16 rsvd2:14;                    // 15:2 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union EPGMXSELLOCK_REG {
    Uint32  all;
    struct  EPGMXSELLOCK_BITS  bit;
};

struct EPGMXSELCOMMIT_BITS {            // bits description
    Uint16 EPGMXSEL0:1;                 // 0 EPGMXSEL0 commit bit
    Uint16 rsvd1:1;                     // 1 Reserved
    Uint16 rsvd2:14;                    // 15:2 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union EPGMXSELCOMMIT_REG {
    Uint32  all;
    struct  EPGMXSELCOMMIT_BITS  bit;
};

struct EPG_MUX_REGS {
    union   EPGMXSEL0_REG                    EPGMXSEL0;                    // EPG Mux select register 0
    Uint16                                   rsvd1[10];                    // Reserved
    union   EPGMXSELLOCK_REG                 EPGMXSELLOCK;                 // EPG Mux select register lock
    union   EPGMXSELCOMMIT_REG               EPGMXSELCOMMIT;               // EPG Mux select register commit
};

//---------------------------------------------------------------------------
// EPG External References & Function Declarations:
//
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
