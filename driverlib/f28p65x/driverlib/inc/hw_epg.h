//###########################################################################
//
// FILE:    hw_epg.h
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

#ifndef HW_EPG_H
#define HW_EPG_H

//*************************************************************************************************
//
// The following are defines for the EPG register offsets
//
//*************************************************************************************************
#define EPG_O_GCTL0                  0x0U    // EPG Global control register 0
#define EPG_O_GCTL1                  0x2U    // EPG Global control register 1
#define EPG_O_GCTL2                  0x4U    // EPG Global control register 2
#define EPG_O_GCTL3                  0x6U    // EPG Global control register 3
#define EPG_O_LOCK                   0x8U    // EPG LOCK Register
#define EPG_O_COMMIT                 0xAU    // EPG COMMIT register
#define EPG_O_GINTSTS                0xCU    // EPG Global interrupt status register.
#define EPG_O_GINTEN                 0xEU    // EPG Global interrupt enable register.
#define EPG_O_GINTCLR                0x10U   // EPG Global interrupt clear register.
#define EPG_O_GINTFRC                0x12U   // EPG Global interrupt force register.
#define EPG_O_CLKDIV0_CTL0           0x18U   // Clock divider 0's control register 0
#define EPG_O_CLKDIV0_CLKOFFSET      0x1EU   // Clock divider 0's clock offset value
#define EPG_O_CLKDIV1_CTL0           0x24U   // Clock divider 1's control register 0
#define EPG_O_CLKDIV1_CLKOFFSET      0x2AU   // Clock divider 1's clock offset value
#define EPG_O_SIGGEN0_CTL0           0x30U   // Signal generator 0's control register 0
#define EPG_O_SIGGEN0_CTL1           0x32U   // Signal generator 0's control register 1
#define EPG_O_SIGGEN0_DATA0          0x38U   // Signal generator 0's data register 0
#define EPG_O_SIGGEN0_DATA1          0x3AU   // Signal generator 0's data register 1
#define EPG_O_SIGGEN0_DATA0_ACTIVE   0x3CU   // Signal generator 0's data active register 0
#define EPG_O_SIGGEN0_DATA1_ACTIVE   0x3EU   // Signal generator 0's data active register 1
#define EPG_O_REVISION               0x50U   // IP Revision tie-off value

#define EPG_O_MXSEL0        0x0U   // EPG Mux select register 0
#define EPG_O_MXSELLOCK     0xCU   // EPG Mux select register lock
#define EPG_O_MXSELCOMMIT   0xEU   // EPG Mux select register commit


//*************************************************************************************************
//
// The following are defines for the bit fields in the GCTL0 register
//
//*************************************************************************************************
#define EPG_GCTL0_EN            0x1U      // Enable EPG
#define EPG_GCTL0_SIGGEN0_EN    0x2U      // Signal generator enable
#define EPG_GCTL0_SIGGEN1_EN    0x4U      // Signal generator enable
#define EPG_GCTL0_EPGOUT13SEL   0x100U    // EPG output 13 Clock/signal select
#define EPG_GCTL0_EPGOUT15SEL   0x200U    // EPG output 15 Clock/signal select
#define EPG_GCTL0_EPGOUT16SEL   0x400U    // EPG output 16 Clock/signal select
#define EPG_GCTL0_EPGOUT17SEL   0x800U    // EPG output 17 Clock/signal select
#define EPG_GCTL0_EPGOUT20SEL   0x1000U   // EPG output 20 Clock/signal select
#define EPG_GCTL0_EPGOUT21SEL   0x2000U   // EPG output 21 Clock/signal select
#define EPG_GCTL0_EPGOUT22SEL   0x4000U   // EPG output 22 Clock/signal select
#define EPG_GCTL0_EPGOUT23SEL   0x8000U   // EPG output 23 Clock/signal select

//*************************************************************************************************
//
// The following are defines for the bit fields in the GCTL1 register
//
//*************************************************************************************************
#define EPG_GCTL1_SIGGEN0_CLKSEL_S   0U
#define EPG_GCTL1_SIGGEN0_CLKSEL_M   0x7U   // Clock source select of SIGGEN0

//*************************************************************************************************
//
// The following are defines for the bit fields in the GCTL2 register
//
//*************************************************************************************************
#define EPG_GCTL2_EPGOUT0_CLKOUTSEL_S   0U
#define EPG_GCTL2_EPGOUT0_CLKOUTSEL_M   0x7U          // Selects the clock signal source of EPG
                                                      // output 0.
#define EPG_GCTL2_EPGOUT1_CLKOUTSEL_S   4U
#define EPG_GCTL2_EPGOUT1_CLKOUTSEL_M   0x70U         // Selects the clock signal source of EPG
                                                      // output 1.
#define EPG_GCTL2_EPGOUT2_CLKOUTSEL_S   8U
#define EPG_GCTL2_EPGOUT2_CLKOUTSEL_M   0x700U        // Selects the clock signal source of EPG
                                                      // output 2.
#define EPG_GCTL2_EPGOUT3_CLKOUTSEL_S   12U
#define EPG_GCTL2_EPGOUT3_CLKOUTSEL_M   0x7000U       // Selects the clock signal source of EPG
                                                      // output 3.
#define EPG_GCTL2_EPGOUT4_CLKOUTSEL_S   16U
#define EPG_GCTL2_EPGOUT4_CLKOUTSEL_M   0x70000U      // Selects the clock signal source of EPG
                                                      // output 4.
#define EPG_GCTL2_EPGOUT5_CLKOUTSEL_S   20U
#define EPG_GCTL2_EPGOUT5_CLKOUTSEL_M   0x700000U     // Selects the clock signal source of EPG
                                                      // output 5.
#define EPG_GCTL2_EPGOUT6_CLKOUTSEL_S   24U
#define EPG_GCTL2_EPGOUT6_CLKOUTSEL_M   0x7000000U    // Selects the clock signal source of EPG
                                                      // output 6.
#define EPG_GCTL2_EPGOUT7_CLKOUTSEL_S   28U
#define EPG_GCTL2_EPGOUT7_CLKOUTSEL_M   0x70000000U   // Selects the clock signal source of EPG
                                                      // output 7.

//*************************************************************************************************
//
// The following are defines for the bit fields in the GCTL3 register
//
//*************************************************************************************************
#define EPG_GCTL3_EPGOUT0_SIGOUTSEL_S   0U
#define EPG_GCTL3_EPGOUT0_SIGOUTSEL_M   0xFU          // Selects the signal source of EPG output 0.
#define EPG_GCTL3_EPGOUT1_SIGOUTSEL_S   4U
#define EPG_GCTL3_EPGOUT1_SIGOUTSEL_M   0xF0U         // Selects the signal source of EPG output 1.
#define EPG_GCTL3_EPGOUT2_SIGOUTSEL_S   8U
#define EPG_GCTL3_EPGOUT2_SIGOUTSEL_M   0xF00U        // Selects the signal source of EPG output 2.
#define EPG_GCTL3_EPGOUT3_SIGOUTSEL_S   12U
#define EPG_GCTL3_EPGOUT3_SIGOUTSEL_M   0xF000U       // Selects the signal source of EPG output 3.
#define EPG_GCTL3_EPGOUT4_SIGOUTSEL_S   16U
#define EPG_GCTL3_EPGOUT4_SIGOUTSEL_M   0xF0000U      // Selects the signal source of EPG output 4.
#define EPG_GCTL3_EPGOUT5_SIGOUTSEL_S   20U
#define EPG_GCTL3_EPGOUT5_SIGOUTSEL_M   0xF00000U     // Selects the signal source of EPG output 5.
#define EPG_GCTL3_EPGOUT6_SIGOUTSEL_S   24U
#define EPG_GCTL3_EPGOUT6_SIGOUTSEL_M   0xF000000U    // Selects the signal source of EPG output 6.
#define EPG_GCTL3_EPGOUT7_SIGOUTSEL_S   28U
#define EPG_GCTL3_EPGOUT7_SIGOUTSEL_M   0xF0000000U   // Selects the signal source of EPG output 7.

//*************************************************************************************************
//
// The following are defines for the bit fields in the EPGLOCK register
//
//*************************************************************************************************
#define EPG_LOCK_GCTL0          0x1U    // GCTL0 Lock bit
#define EPG_LOCK_GCTL1          0x2U    // GCTL1 Lock bit
#define EPG_LOCK_GCTL2          0x4U    // GCTL2 Lock bit
#define EPG_LOCK_GCTL3          0x8U    // GCTL3 Lock bit
#define EPG_LOCK_CLKDIV0_CTL0   0x10U   // CLKDIV0_CTL0 Lock bit
#define EPG_LOCK_CLKDIV1_CTL0   0x20U   // CLKDIV1_CTL0 Lock bit
#define EPG_LOCK_SIGGEN0_CTL0   0x40U   // SIGGEN0_CTL0 Lock bit
#define EPG_LOCK_SIGGEN0_CTL1   0x80U   // SIGGEN0_CTL1 Lock bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the EPGCOMMIT register
//
//*************************************************************************************************
#define EPG_COMMIT_GCTL0          0x1U    // GCTL0 Commit bit
#define EPG_COMMIT_GCTL1          0x2U    // GCTL1 Commit bit
#define EPG_COMMIT_GCTL2          0x4U    // GCTL2 Commit bit
#define EPG_COMMIT_GCTL3          0x8U    // GCTL3 Commit bit
#define EPG_COMMIT_CLKDIV0_CTL0   0x10U   // CLKDIV0_CTL0 Commit bit
#define EPG_COMMIT_CLKDIV1_CTL0   0x20U   // CLKDIV1_CTL0 Commit bit
#define EPG_COMMIT_SIGGEN0_CTL0   0x40U   // SIGGEN0_CTL0 Commit bit
#define EPG_COMMIT_SIGGEN0_CTL1   0x80U   // SIGGEN0_CTL1 Commit bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the GINTSTS register
//
//*************************************************************************************************
#define EPG_GINTSTS_INT            0x1U   // Global interrupt flag register
#define EPG_GINTSTS_SIGGEN0_DONE   0x2U   // SIGGEN0 operation done status
#define EPG_GINTSTS_SIGGEN0_FILL   0x4U   // SIGGEN0 data fill status

//*************************************************************************************************
//
// The following are defines for the bit fields in the GINTEN register
//
//*************************************************************************************************
#define EPG_GINTEN_SIGGEN0_DONE   0x2U   // SIGGEN0 operation done interrupt enable
#define EPG_GINTEN_SIGGEN0_FILL   0x4U   // SIGGEN0 data fill interrupt enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the GINTCLR register
//
//*************************************************************************************************
#define EPG_GINTCLR_INT            0x1U   // Global interrupt flag clear
#define EPG_GINTCLR_SIGGEN0_DONE   0x2U   // SIGGEN0 operation done interrupt flag clear
#define EPG_GINTCLR_SIGGEN0_FILL   0x4U   // SIGGEN0 data fill interrupt flag clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the GINTFRC register
//
//*************************************************************************************************
#define EPG_GINTFRC_SIGGEN0_DONE   0x2U   // SIGGEN0 operation done interrupt flag set
#define EPG_GINTFRC_SIGGEN0_FILL   0x4U   // SIGGEN0 data fill interrupt flag set

//*************************************************************************************************
//
// The following are defines for the bit fields in the CLKDIV0_CTL0 register
//
//*************************************************************************************************
#define EPG_CLKDIV0_CTL0_PRD_S       0U
#define EPG_CLKDIV0_CTL0_PRD_M       0xFFFFU    // Clock divider value
#define EPG_CLKDIV0_CTL0_CLKSTOP_S   16U
#define EPG_CLKDIV0_CTL0_CLKSTOP_M   0x70000U   // Clock Stop Configuration

//*************************************************************************************************
//
// The following are defines for the bit fields in the CLKDIV0_CLKOFFSET register
//
//*************************************************************************************************
#define EPG_CLKDIV0_CLKOFFSET_CLK0OFFSET_S   0U
#define EPG_CLKDIV0_CLKOFFSET_CLK0OFFSET_M   0xFFU         // Clock output 0 offset delay value.
#define EPG_CLKDIV0_CLKOFFSET_CLK1OFFSET_S   8U
#define EPG_CLKDIV0_CLKOFFSET_CLK1OFFSET_M   0xFF00U       // Clock output 0 offset delay value.
#define EPG_CLKDIV0_CLKOFFSET_CLK2OFFSET_S   16U
#define EPG_CLKDIV0_CLKOFFSET_CLK2OFFSET_M   0xFF0000U     // Clock output 0 offset delay value.
#define EPG_CLKDIV0_CLKOFFSET_CLK3OFFSET_S   24U
#define EPG_CLKDIV0_CLKOFFSET_CLK3OFFSET_M   0xFF000000U   // Clock output 0 offset delay value.

//*************************************************************************************************
//
// The following are defines for the bit fields in the CLKDIV1_CTL0 register
//
//*************************************************************************************************
#define EPG_CLKDIV1_CTL0_PRD_S       0U
#define EPG_CLKDIV1_CTL0_PRD_M       0xFFFFU    // Clock divider value
#define EPG_CLKDIV1_CTL0_CLKSTOP_S   16U
#define EPG_CLKDIV1_CTL0_CLKSTOP_M   0x70000U   // Clock Stop Configuration

//*************************************************************************************************
//
// The following are defines for the bit fields in the CLKDIV1_CLKOFFSET register
//
//*************************************************************************************************
#define EPG_CLKDIV1_CLKOFFSET_CLK0OFFSET_S   0U
#define EPG_CLKDIV1_CLKOFFSET_CLK0OFFSET_M   0xFFU         // Clock output 0 offset delay value.
#define EPG_CLKDIV1_CLKOFFSET_CLK1OFFSET_S   8U
#define EPG_CLKDIV1_CLKOFFSET_CLK1OFFSET_M   0xFF00U       // Clock output 0 offset delay value.
#define EPG_CLKDIV1_CLKOFFSET_CLK2OFFSET_S   16U
#define EPG_CLKDIV1_CLKOFFSET_CLK2OFFSET_M   0xFF0000U     // Clock output 0 offset delay value.
#define EPG_CLKDIV1_CLKOFFSET_CLK3OFFSET_S   24U
#define EPG_CLKDIV1_CLKOFFSET_CLK3OFFSET_M   0xFF000000U   // Clock output 0 offset delay value.

//*************************************************************************************************
//
// The following are defines for the bit fields in the SIGGEN0_CTL0 register
//
//*************************************************************************************************
#define EPG_SIGGEN0_CTL0_MODE_S        0U
#define EPG_SIGGEN0_CTL0_MODE_M        0xFU        // Signal generator modes
#define EPG_SIGGEN0_CTL0_BRIN          0x20U       // Reverse bits before transform
#define EPG_SIGGEN0_CTL0_BROUT         0x40U       // Reverse bits after transform
#define EPG_SIGGEN0_CTL0_BITLENGTH_S   16U
#define EPG_SIGGEN0_CTL0_BITLENGTH_M   0xFF0000U   // Length of bit stream

//*************************************************************************************************
//
// The following are defines for the bit fields in the SIGGEN0_CTL1 register
//
//*************************************************************************************************
#define EPG_SIGGEN0_CTL1_DATA0_INSEL_S    0U
#define EPG_SIGGEN0_CTL1_DATA0_INSEL_M    0xFU          // Select the source of DATA[0] bit.
#define EPG_SIGGEN0_CTL1_DATA63_INSEL_S   28U
#define EPG_SIGGEN0_CTL1_DATA63_INSEL_M   0xF0000000U   // Select the source of DATA[63] bit.

//*************************************************************************************************
//
// The following are defines for the bit fields in the REVISION register
//
//*************************************************************************************************
#define EPG_REVISION_MINOR_S    0U
#define EPG_REVISION_MINOR_M    0x3FU         // Minor Revision Number
#define EPG_REVISION_CUSTOM_S   6U
#define EPG_REVISION_CUSTOM_M   0xC0U         // Custom Module Number
#define EPG_REVISION_MAJOR_S    8U
#define EPG_REVISION_MAJOR_M    0x700U        // Major Revision Number
#define EPG_REVISION_FUNC_S     16U
#define EPG_REVISION_FUNC_M     0xFFF0000U    // Functional Release Number
#define EPG_REVISION_SCHEME_S   30U
#define EPG_REVISION_SCHEME_M   0xC0000000U   // Defines Scheme for Module


//*************************************************************************************************
//
// The following are defines for the bit fields in the EPGMXSEL0 register
//
//*************************************************************************************************
#define EPG_MXSEL0_SEL0    0x1U          // DATAOUT[0] mux select.
#define EPG_MXSEL0_SEL1    0x2U          // DATAOUT[1] mux select.
#define EPG_MXSEL0_SEL2    0x4U          // DATAOUT[2] mux select.
#define EPG_MXSEL0_SEL3    0x8U          // DATAOUT[3] mux select.
#define EPG_MXSEL0_SEL4    0x10U         // DATAOUT[4] mux select.
#define EPG_MXSEL0_SEL5    0x20U         // DATAOUT[5] mux select.
#define EPG_MXSEL0_SEL6    0x40U         // DATAOUT[6] mux select.
#define EPG_MXSEL0_SEL7    0x80U         // DATAOUT[7] mux select.
#define EPG_MXSEL0_SEL8    0x100U        // DATAOUT[8] mux select.
#define EPG_MXSEL0_SEL9    0x200U        // DATAOUT[9] mux select.
#define EPG_MXSEL0_SEL10   0x400U        // DATAOUT[10] mux select.
#define EPG_MXSEL0_SEL11   0x800U        // DATAOUT[11] mux select.
#define EPG_MXSEL0_SEL12   0x1000U       // DATAOUT[12] mux select.
#define EPG_MXSEL0_SEL13   0x2000U       // DATAOUT[13] mux select.
#define EPG_MXSEL0_SEL14   0x4000U       // DATAOUT[14] mux select.
#define EPG_MXSEL0_SEL15   0x8000U       // DATAOUT[15] mux select.
#define EPG_MXSEL0_SEL16   0x10000U      // DATAOUT[16] mux select.
#define EPG_MXSEL0_SEL17   0x20000U      // DATAOUT[17] mux select.
#define EPG_MXSEL0_SEL18   0x40000U      // DATAOUT[18] mux select.
#define EPG_MXSEL0_SEL19   0x80000U      // DATAOUT[19] mux select.
#define EPG_MXSEL0_SEL20   0x100000U     // DATAOUT[20] mux select.
#define EPG_MXSEL0_SEL21   0x200000U     // DATAOUT[21] mux select.
#define EPG_MXSEL0_SEL22   0x400000U     // DATAOUT[22] mux select.
#define EPG_MXSEL0_SEL23   0x800000U     // DATAOUT[23] mux select.
#define EPG_MXSEL0_SEL24   0x1000000U    // DATAOUT[24] mux select.
#define EPG_MXSEL0_SEL25   0x2000000U    // DATAOUT[25] mux select.
#define EPG_MXSEL0_SEL26   0x4000000U    // DATAOUT[26] mux select.
#define EPG_MXSEL0_SEL27   0x8000000U    // DATAOUT[27] mux select.
#define EPG_MXSEL0_SEL28   0x10000000U   // DATAOUT[28] mux select.
#define EPG_MXSEL0_SEL29   0x20000000U   // DATAOUT[29] mux select.
#define EPG_MXSEL0_SEL30   0x40000000U   // DATAOUT[30] mux select.
#define EPG_MXSEL0_SEL31   0x80000000U   // DATAOUT[31] mux select.

//*************************************************************************************************
//
// The following are defines for the bit fields in the EPGMXSELLOCK register
//
//*************************************************************************************************
#define EPG_MXSELLOCK_EPGMXSEL0   0x1U   // EPGMXSEL0 lock bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the EPGMXSELCOMMIT register
//
//*************************************************************************************************
#define EPG_MXSELCOMMIT_EPGMXSEL0   0x1U   // EPGMXSEL0 commit bit



#endif
