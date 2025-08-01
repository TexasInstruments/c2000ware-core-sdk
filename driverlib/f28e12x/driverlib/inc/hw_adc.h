//###########################################################################
//
// FILE:    hw_adc.h
//
// TITLE:   Definitions for the ADC registers.
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

#ifndef HW_ADC_H
#define HW_ADC_H

//*************************************************************************************************
//
// The following are defines for the ADC register offsets
//
//*************************************************************************************************
#define ADC_O_CTL1          0x0U     // ADC Control 1 Register
#define ADC_O_CTL2          0x2U     // ADC Control 2 Register
#define ADC_O_INTSEL        0x8U     // ADC Interrupt 1, 2, 3 and 4 Selection Register
#define ADC_O_DMAINTSEL     0xAU     // ADC DMA Interrupt 1, 2, 3 and 4 Selection Register
#define ADC_O_RAWINTFLG     0xCU     // ADC Raw Interrupt Flag Register
#define ADC_O_INTFLG        0xEU     // ADC Interrupt Flag Register
#define ADC_O_INTFLGFRC     0x10U    // ADC Interrupt Flag Force Register
#define ADC_O_INTFLGCLR     0x12U    // ADC Interrupt Flag Clear Register
#define ADC_O_INTOVF        0x14U    // ADC Interrupt Overflow Register
#define ADC_O_INTOVFCLR     0x16U    // ADC Interrupt Overflow Clear Register
#define ADC_O_SOCPRICTL     0x18U    // ADC SOC Priority Control Register
#define ADC_O_INTSOCSEL1    0x1AU    // ADC Interrupt SOC Selection 1 Register
#define ADC_O_SOCFLG1       0x1EU    // ADC SOC Flag 1 Register
#define ADC_O_SOCFRC1       0x20U    // ADC SOC Force 1 Register
#define ADC_O_SOCOVF1       0x22U    // ADC SOC Overflow 1 Register
#define ADC_O_SOCOVFCLR1    0x24U    // ADC SOC Overflow Clear 1 Register
#define ADC_O_SOC0CTL       0x26U    // ADC SOC0 Control Register
#define ADC_O_SOC1CTL       0x28U    // ADC SOC1 Control Register
#define ADC_O_SOC2CTL       0x2AU    // ADC SOC2 Control Register
#define ADC_O_SOC3CTL       0x2CU    // ADC SOC3 Control Register
#define ADC_O_SOC4CTL       0x2EU    // ADC SOC4 Control Register
#define ADC_O_SOC5CTL       0x30U    // ADC SOC5 Control Register
#define ADC_O_SOC6CTL       0x32U    // ADC SOC6 Control Register
#define ADC_O_SOC7CTL       0x34U    // ADC SOC7 Control Register
#define ADC_O_SOC8CTL       0x36U    // ADC SOC8 Control Register
#define ADC_O_SOC9CTL       0x38U    // ADC SOC9 Control Register
#define ADC_O_SOC10CTL      0x3AU    // ADC SOC10 Control Register
#define ADC_O_SOC11CTL      0x3CU    // ADC SOC11 Control Register
#define ADC_O_SOC12CTL      0x3EU    // ADC SOC12 Control Register
#define ADC_O_SOC13CTL      0x40U    // ADC SOC13 Control Register
#define ADC_O_SOC14CTL      0x42U    // ADC SOC14 Control Register
#define ADC_O_SOC15CTL      0x44U    // ADC SOC15 Control Register
#define ADC_O_EVTSTAT       0x66U    // ADC Event Status Register
#define ADC_O_EVTCLR        0x68U    // ADC Event Clear Register
#define ADC_O_EVTSEL        0x6AU    // ADC Event Selection Register
#define ADC_O_EVTINTSEL     0x6CU    // ADC Event Interrupt Selection Register
#define ADC_O_REV           0x72U    // ADC Revision Register
#define ADC_O_OFFTRIM       0x74U    // ADC Offset Trim Register 1
#define ADC_O_PPB1CONFIG    0x80U    // ADC PPB{#} Config Register
#define ADC_O_PPB1OFFCAL    0x84U    // ADC PPB1 Offset Calibration Register
#define ADC_O_PPB1OFFREF    0x86U    // ADC PPB1 Offset Reference Register
#define ADC_O_PPB1TRIPHI    0x88U    // ADC PPB1 Trip High Register
#define ADC_O_PPB1TRIPLO    0x8AU    // ADC PPB1 Trip Low/Trigger Time Stamp Register
#define ADC_O_PPB2CONFIG    0x90U    // ADC PPB{#} Config Register
#define ADC_O_PPB2OFFCAL    0x94U    // ADC PPB2 Offset Calibration Register
#define ADC_O_PPB2OFFREF    0x96U    // ADC PPB2 Offset Reference Register
#define ADC_O_PPB2TRIPHI    0x98U    // ADC PPB2 Trip High Register
#define ADC_O_PPB2TRIPLO    0x9AU    // ADC PPB2 Trip Low/Trigger Time Stamp Register
#define ADC_O_PPB3CONFIG    0xA0U    // ADC PPB{#} Config Register
#define ADC_O_PPB3OFFCAL    0xA4U    // ADC PPB3 Offset Calibration Register
#define ADC_O_PPB3OFFREF    0xA6U    // ADC PPB3 Offset Reference Register
#define ADC_O_PPB3TRIPHI    0xA8U    // ADC PPB3 Trip High Register
#define ADC_O_PPB3TRIPLO    0xAAU    // ADC PPB3 Trip Low/Trigger Time Stamp Register
#define ADC_O_INTCYCLE      0xC0U    // ADC Early Interrupt Generation Cycle
#define ADC_O_INLTRIM1      0xC2U    // ADC Linearity Trim 1 Register
#define ADC_O_INLTRIM2      0xC4U    // ADC Linearity Trim 2 Register
#define ADC_O_REV2          0xCEU    // ADC Wrapper Revision Register
#define ADC_O_REP1CTL       0xE0U    // ADC Trigger Repeater 1 Control Register
#define ADC_O_REP1N         0xE2U    // ADC Trigger Repeater 1 N Select Register
#define ADC_O_REP1SPREAD    0xE6U    // ADC Trigger Repeater 1 Spread Select Register
#define ADC_O_REP1FRC       0xE8U    // ADC Trigger Repeater 1 Software Force Register
#define ADC_O_PPB1LIMIT     0x100U   // ADC PPB1Conversion Count Limit Register
#define ADC_O_PPBP1PCOUNT   0x102U   // ADC PPB1 Partial Conversion Count Register
#define ADC_O_PPB1CONFIG2   0x104U   // ADC PPB1 Sum Shift Register
#define ADC_O_PPB1PSUM      0x106U   // ADC PPB1 Partial Sum Register

#define ADC_O_RESULT0      0x0U    // ADC Result 0 Register
#define ADC_O_RESULT1      0x1U    // ADC Result 1 Register
#define ADC_O_RESULT2      0x2U    // ADC Result 2 Register
#define ADC_O_RESULT3      0x3U    // ADC Result 3 Register
#define ADC_O_RESULT4      0x4U    // ADC Result 4 Register
#define ADC_O_RESULT5      0x5U    // ADC Result 5 Register
#define ADC_O_RESULT6      0x6U    // ADC Result 6 Register
#define ADC_O_RESULT7      0x7U    // ADC Result 7 Register
#define ADC_O_RESULT8      0x8U    // ADC Result 8 Register
#define ADC_O_RESULT9      0x9U    // ADC Result 9 Register
#define ADC_O_RESULT10     0xAU    // ADC Result 10 Register
#define ADC_O_RESULT11     0xBU    // ADC Result 11 Register
#define ADC_O_RESULT12     0xCU    // ADC Result 12 Register
#define ADC_O_RESULT13     0xDU    // ADC Result 13 Register
#define ADC_O_RESULT14     0xEU    // ADC Result 14 Register
#define ADC_O_RESULT15     0xFU    // ADC Result 15 Register
#define ADC_O_PPB1RESULT   0x20U   // ADC Post Processing Block 1 Result Register
#define ADC_O_PPB2RESULT   0x22U   // ADC Post Processing Block 2 Result Register
#define ADC_O_PPB3RESULT   0x24U   // ADC Post Processing Block 3 Result Register
#define ADC_O_PPB1SUM      0x28U   // ADC PPB 1 Final Sum Result Register
#define ADC_O_PPB1COUNT    0x2AU   // ADC PPB1 Final Conversion Count Register


//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCCTL1 register
//
//*************************************************************************************************
#define ADC_CTL1_INTPULSEPOS   0x4U      // ADC Interrupt Pulse Position
#define ADC_CTL1_ADCPWDNZ      0x80U     // ADC Power Down
#define ADC_CTL1_ADCBSYCHN_S   8U
#define ADC_CTL1_ADCBSYCHN_M   0xF00U    // ADC Busy Channel
#define ADC_CTL1_ADCBSY        0x2000U   // ADC Busy

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCCTL2 register
//
//*************************************************************************************************
#define ADC_CTL2_PRESCALE_S   0U
#define ADC_CTL2_PRESCALE_M   0xFU   // ADC Clock Prescaler

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCINTSEL register
//
//*************************************************************************************************
#define ADC_INTSEL_INT1SEL_S   0U
#define ADC_INTSEL_INT1SEL_M   0x3FU     // ADCINT1 EOC Source Select
#define ADC_INTSEL_INT1CONT    0x40U     // ADCINT1 Continue to Interrupt Mode
#define ADC_INTSEL_INT1E       0x80U     // ADCINT1 Interrupt Enable
#define ADC_INTSEL_INT2SEL_S   8U
#define ADC_INTSEL_INT2SEL_M   0x3F00U   // ADCINT2 EOC Source Select
#define ADC_INTSEL_INT2CONT    0x4000U   // ADCINT2 Continue to Interrupt Mode
#define ADC_INTSEL_INT2E       0x8000U   // ADCINT2 Interrupt Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCDMAINTSEL register
//
//*************************************************************************************************
#define ADC_DMAINTSEL_DMAINT1SEL_S   0U
#define ADC_DMAINTSEL_DMAINT1SEL_M   0x3FU     // ADCDMAINT1 EOC Source Select
#define ADC_DMAINTSEL_DMAINT1CONT    0x40U     // ADCDMAINT1 Continue to Interrupt Mode
#define ADC_DMAINTSEL_DMAINT1E       0x80U     // ADCDMAINT1 Interrupt Enable
#define ADC_DMAINTSEL_DMAINT2SEL_S   8U
#define ADC_DMAINTSEL_DMAINT2SEL_M   0x3F00U   // ADCDMAINT2 EOC Source Select
#define ADC_DMAINTSEL_DMAINT2CONT    0x4000U   // ADCDMAINT2 Continue to Interrupt Mode
#define ADC_DMAINTSEL_DMAINT2E       0x8000U   // ADCDMAINT2 Interrupt Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCRAWINTFLG register
//
//*************************************************************************************************
#define ADC_RAWINTFLG_ADCRAWINT1      0x1U       // ADC Raw Interrupt 1 Flag
#define ADC_RAWINTFLG_ADCRAWINT2      0x2U       // ADC Raw Interrupt 2 Flag
#define ADC_RAWINTFLG_ADCDMARAWINT1   0x10000U   // ADC DMA Raw Interrupt 1 Flag
#define ADC_RAWINTFLG_ADCDMARAWINT2   0x20000U   // ADC DMA Raw Interrupt 2 Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCINTFLG register
//
//*************************************************************************************************
#define ADC_INTFLG_ADCINT1         0x1U       // ADC Interrupt 1 Flag
#define ADC_INTFLG_ADCINT2         0x2U       // ADC Interrupt 2 Flag
#define ADC_INTFLG_ADCINT1RESULT   0x100U     // ADC Interrupt 1 Results Ready
#define ADC_INTFLG_ADCINT2RESULT   0x200U     // ADC Interrupt 2 Results Ready
#define ADC_INTFLG_ADCDMAINT1      0x10000U   // ADC DMA Interrupt 1 Flag
#define ADC_INTFLG_ADCDMAINT2      0x20000U   // ADC DMA Interrupt 2 Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCINTFLGFRC register
//
//*************************************************************************************************
#define ADC_INTFLGFRC_ADCINT1      0x1U       // ADC Interrupt 1 Flag Force
#define ADC_INTFLGFRC_ADCINT2      0x2U       // ADC Interrupt 2 Flag Force
#define ADC_INTFLGFRC_ADCDMAINT1   0x10000U   // ADC DMA Interrupt 1 Flag Force
#define ADC_INTFLGFRC_ADCDMAINT2   0x20000U   // ADC DMA Interrupt 2 Flag Force

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCINTFLGCLR register
//
//*************************************************************************************************
#define ADC_INTFLGCLR_ADCINT1      0x1U       // ADC Interrupt 1 Flag Clear
#define ADC_INTFLGCLR_ADCINT2      0x2U       // ADC Interrupt 2 Flag Clear
#define ADC_INTFLGCLR_ADCDMAINT1   0x10000U   // ADC DMA Interrupt 1 Flag Clear
#define ADC_INTFLGCLR_ADCDMAINT2   0x20000U   // ADC DMA Interrupt 2 Flag Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCINTOVF register
//
//*************************************************************************************************
#define ADC_INTOVF_ADCINT1OVF      0x1U       // ADC Interrupt 1 Overflow Flags
#define ADC_INTOVF_ADCINT2OVF      0x2U       // ADC Interrupt 2 Overflow Flags
#define ADC_INTOVF_ADCDMAINT1OVF   0x10000U   // ADC DMA Interrupt 1 Overflow Flags
#define ADC_INTOVF_ADCDMAINT2OVF   0x20000U   // ADC DMA Interrupt 2 Overflow Flags

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCINTOVFCLR register
//
//*************************************************************************************************
#define ADC_INTOVFCLR_ADCINT1OVF      0x1U       // ADC Interrupt 1 Overflow Clear Bits
#define ADC_INTOVFCLR_ADCINT2OVF      0x2U       // ADC Interrupt 2 Overflow Clear Bits
#define ADC_INTOVFCLR_ADCDMAINT1OVF   0x10000U   // ADC DMA Interrupt 1 Overflow Clear Bits
#define ADC_INTOVFCLR_ADCDMAINT2OVF   0x20000U   // ADC DMA Interrupt 2 Overflow Clear Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOCPRICTL register
//
//*************************************************************************************************
#define ADC_SOCPRICTL_SOCPRIORITY_S   0U
#define ADC_SOCPRICTL_SOCPRIORITY_M   0x3U     // SOC Priority
#define ADC_SOCPRICTL_RRPOINTER_S     6U
#define ADC_SOCPRICTL_RRPOINTER_M     0x7C0U   // Round Robin Pointer

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCINTSOCSEL1 register
//
//*************************************************************************************************
#define ADC_INTSOCSEL1_SOC0_S    0U
#define ADC_INTSOCSEL1_SOC0_M    0x3U          // SOC0 ADC Interrupt Trigger Select
#define ADC_INTSOCSEL1_SOC1_S    2U
#define ADC_INTSOCSEL1_SOC1_M    0xCU          // SOC1 ADC Interrupt Trigger Select
#define ADC_INTSOCSEL1_SOC2_S    4U
#define ADC_INTSOCSEL1_SOC2_M    0x30U         // SOC2 ADC Interrupt Trigger Select
#define ADC_INTSOCSEL1_SOC3_S    6U
#define ADC_INTSOCSEL1_SOC3_M    0xC0U         // SOC3 ADC Interrupt Trigger Select
#define ADC_INTSOCSEL1_SOC4_S    8U
#define ADC_INTSOCSEL1_SOC4_M    0x300U        // SOC4 ADC Interrupt Trigger Select
#define ADC_INTSOCSEL1_SOC5_S    10U
#define ADC_INTSOCSEL1_SOC5_M    0xC00U        // SOC5 ADC Interrupt Trigger Select
#define ADC_INTSOCSEL1_SOC6_S    12U
#define ADC_INTSOCSEL1_SOC6_M    0x3000U       // SOC6 ADC Interrupt Trigger Select
#define ADC_INTSOCSEL1_SOC7_S    14U
#define ADC_INTSOCSEL1_SOC7_M    0xC000U       // SOC7 ADC Interrupt Trigger Select
#define ADC_INTSOCSEL1_SOC8_S    16U
#define ADC_INTSOCSEL1_SOC8_M    0x30000U      // SOC8 ADC Interrupt Trigger Select
#define ADC_INTSOCSEL1_SOC9_S    18U
#define ADC_INTSOCSEL1_SOC9_M    0xC0000U      // SOC9 ADC Interrupt Trigger Select
#define ADC_INTSOCSEL1_SOC10_S   20U
#define ADC_INTSOCSEL1_SOC10_M   0x300000U     // SOC10 ADC Interrupt Trigger Select
#define ADC_INTSOCSEL1_SOC11_S   22U
#define ADC_INTSOCSEL1_SOC11_M   0xC00000U     // SOC11 ADC Interrupt Trigger Select
#define ADC_INTSOCSEL1_SOC12_S   24U
#define ADC_INTSOCSEL1_SOC12_M   0x3000000U    // SOC12 ADC Interrupt Trigger Select
#define ADC_INTSOCSEL1_SOC13_S   26U
#define ADC_INTSOCSEL1_SOC13_M   0xC000000U    // SOC13 ADC Interrupt Trigger Select
#define ADC_INTSOCSEL1_SOC14_S   28U
#define ADC_INTSOCSEL1_SOC14_M   0x30000000U   // SOC14 ADC Interrupt Trigger Select
#define ADC_INTSOCSEL1_SOC15_S   30U
#define ADC_INTSOCSEL1_SOC15_M   0xC0000000U   // SOC15 ADC Interrupt Trigger Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOCFLG1 register
//
//*************************************************************************************************
#define ADC_SOCFLG1_SOC0    0x1U      // SOC0 Start of Conversion Flag
#define ADC_SOCFLG1_SOC1    0x2U      // SOC1 Start of Conversion Flag
#define ADC_SOCFLG1_SOC2    0x4U      // SOC2 Start of Conversion Flag
#define ADC_SOCFLG1_SOC3    0x8U      // SOC3 Start of Conversion Flag
#define ADC_SOCFLG1_SOC4    0x10U     // SOC4 Start of Conversion Flag
#define ADC_SOCFLG1_SOC5    0x20U     // SOC5 Start of Conversion Flag
#define ADC_SOCFLG1_SOC6    0x40U     // SOC6 Start of Conversion Flag
#define ADC_SOCFLG1_SOC7    0x80U     // SOC7 Start of Conversion Flag
#define ADC_SOCFLG1_SOC8    0x100U    // SOC8 Start of Conversion Flag
#define ADC_SOCFLG1_SOC9    0x200U    // SOC9 Start of Conversion Flag
#define ADC_SOCFLG1_SOC10   0x400U    // SOC10 Start of Conversion Flag
#define ADC_SOCFLG1_SOC11   0x800U    // SOC11 Start of Conversion Flag
#define ADC_SOCFLG1_SOC12   0x1000U   // SOC12 Start of Conversion Flag
#define ADC_SOCFLG1_SOC13   0x2000U   // SOC13 Start of Conversion Flag
#define ADC_SOCFLG1_SOC14   0x4000U   // SOC14 Start of Conversion Flag
#define ADC_SOCFLG1_SOC15   0x8000U   // SOC15 Start of Conversion Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOCFRC1 register
//
//*************************************************************************************************
#define ADC_SOCFRC1_SOC0    0x1U      // SOC0 Force Start of Conversion Bit
#define ADC_SOCFRC1_SOC1    0x2U      // SOC1 Force Start of Conversion Bit
#define ADC_SOCFRC1_SOC2    0x4U      // SOC2 Force Start of Conversion Bit
#define ADC_SOCFRC1_SOC3    0x8U      // SOC3 Force Start of Conversion Bit
#define ADC_SOCFRC1_SOC4    0x10U     // SOC4 Force Start of Conversion Bit
#define ADC_SOCFRC1_SOC5    0x20U     // SOC5 Force Start of Conversion Bit
#define ADC_SOCFRC1_SOC6    0x40U     // SOC6 Force Start of Conversion Bit
#define ADC_SOCFRC1_SOC7    0x80U     // SOC7 Force Start of Conversion Bit
#define ADC_SOCFRC1_SOC8    0x100U    // SOC8 Force Start of Conversion Bit
#define ADC_SOCFRC1_SOC9    0x200U    // SOC9 Force Start of Conversion Bit
#define ADC_SOCFRC1_SOC10   0x400U    // SOC10 Force Start of Conversion Bit
#define ADC_SOCFRC1_SOC11   0x800U    // SOC11 Force Start of Conversion Bit
#define ADC_SOCFRC1_SOC12   0x1000U   // SOC12 Force Start of Conversion Bit
#define ADC_SOCFRC1_SOC13   0x2000U   // SOC13 Force Start of Conversion Bit
#define ADC_SOCFRC1_SOC14   0x4000U   // SOC14 Force Start of Conversion Bit
#define ADC_SOCFRC1_SOC15   0x8000U   // SOC15 Force Start of Conversion Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOCOVF1 register
//
//*************************************************************************************************
#define ADC_SOCOVF1_SOC0OVF    0x1U      // SOC0 Start of Conversion Overflow Flag
#define ADC_SOCOVF1_SOC1OVF    0x2U      // SOC1 Start of Conversion Overflow Flag
#define ADC_SOCOVF1_SOC2OVF    0x4U      // SOC2 Start of Conversion Overflow Flag
#define ADC_SOCOVF1_SOC3OVF    0x8U      // SOC3 Start of Conversion Overflow Flag
#define ADC_SOCOVF1_SOC4OVF    0x10U     // SOC4 Start of Conversion Overflow Flag
#define ADC_SOCOVF1_SOC5OVF    0x20U     // SOC5 Start of Conversion Overflow Flag
#define ADC_SOCOVF1_SOC6OVF    0x40U     // SOC6 Start of Conversion Overflow Flag
#define ADC_SOCOVF1_SOC7OVF    0x80U     // SOC7 Start of Conversion Overflow Flag
#define ADC_SOCOVF1_SOC8OVF    0x100U    // SOC8 Start of Conversion Overflow Flag
#define ADC_SOCOVF1_SOC9OVF    0x200U    // SOC9 Start of Conversion Overflow Flag
#define ADC_SOCOVF1_SOC10OVF   0x400U    // SOC10 Start of Conversion Overflow Flag
#define ADC_SOCOVF1_SOC11OVF   0x800U    // SOC11 Start of Conversion Overflow Flag
#define ADC_SOCOVF1_SOC12OVF   0x1000U   // SOC12 Start of Conversion Overflow Flag
#define ADC_SOCOVF1_SOC13OVF   0x2000U   // SOC13 Start of Conversion Overflow Flag
#define ADC_SOCOVF1_SOC14OVF   0x4000U   // SOC14 Start of Conversion Overflow Flag
#define ADC_SOCOVF1_SOC15OVF   0x8000U   // SOC15 Start of Conversion Overflow Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOCOVFCLR1 register
//
//*************************************************************************************************
#define ADC_SOCOVFCLR1_SOC0OVF    0x1U      // SOC0 Clear Start of Conversion Overflow Bit
#define ADC_SOCOVFCLR1_SOC1OVF    0x2U      // SOC1 Clear Start of Conversion Overflow Bit
#define ADC_SOCOVFCLR1_SOC2OVF    0x4U      // SOC2 Clear Start of Conversion Overflow Bit
#define ADC_SOCOVFCLR1_SOC3OVF    0x8U      // SOC3 Clear Start of Conversion Overflow Bit
#define ADC_SOCOVFCLR1_SOC4OVF    0x10U     // SOC4 Clear Start of Conversion Overflow Bit
#define ADC_SOCOVFCLR1_SOC5OVF    0x20U     // SOC5 Clear Start of Conversion Overflow Bit
#define ADC_SOCOVFCLR1_SOC6OVF    0x40U     // SOC6 Clear Start of Conversion Overflow Bit
#define ADC_SOCOVFCLR1_SOC7OVF    0x80U     // SOC7 Clear Start of Conversion Overflow Bit
#define ADC_SOCOVFCLR1_SOC8OVF    0x100U    // SOC8 Clear Start of Conversion Overflow Bit
#define ADC_SOCOVFCLR1_SOC9OVF    0x200U    // SOC9 Clear Start of Conversion Overflow Bit
#define ADC_SOCOVFCLR1_SOC10OVF   0x400U    // SOC10 Clear Start of Conversion Overflow Bit
#define ADC_SOCOVFCLR1_SOC11OVF   0x800U    // SOC11 Clear Start of Conversion Overflow Bit
#define ADC_SOCOVFCLR1_SOC12OVF   0x1000U   // SOC12 Clear Start of Conversion Overflow Bit
#define ADC_SOCOVFCLR1_SOC13OVF   0x2000U   // SOC13 Clear Start of Conversion Overflow Bit
#define ADC_SOCOVFCLR1_SOC14OVF   0x4000U   // SOC14 Clear Start of Conversion Overflow Bit
#define ADC_SOCOVFCLR1_SOC15OVF   0x8000U   // SOC15 Clear Start of Conversion Overflow Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC0CTL register
//
//*************************************************************************************************
#define ADC_SOC0CTL_ACQPS_S               0U
#define ADC_SOC0CTL_ACQPS_M               0xFFU        // SOC0 Acquisition Prescale
#define ADC_SOC0CTL_SAMPCAPRESETDISABLE   0x200U       // SOC0 Sample Cap Reset Enable
#define ADC_SOC0CTL_SAMPCAPRESETSEL       0x400U       // SOC0 Sample Cap Reset Select
#define ADC_SOC0CTL_CHSEL_S               15U
#define ADC_SOC0CTL_CHSEL_M               0xF8000U     // SOC0 Channel Select
#define ADC_SOC0CTL_TRIGSEL_S             20U
#define ADC_SOC0CTL_TRIGSEL_M             0x1F00000U   // SOC0 Trigger Source Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC1CTL register
//
//*************************************************************************************************
#define ADC_SOC1CTL_ACQPS_S               0U
#define ADC_SOC1CTL_ACQPS_M               0xFFU        // SOC1 Acquisition Prescale
#define ADC_SOC1CTL_SAMPCAPRESETDISABLE   0x200U       // SOC1 Sample Cap Reset Enable
#define ADC_SOC1CTL_SAMPCAPRESETSEL       0x400U       // SOC1 Sample Cap Reset Select
#define ADC_SOC1CTL_CHSEL_S               15U
#define ADC_SOC1CTL_CHSEL_M               0xF8000U     // SOC1 Channel Select
#define ADC_SOC1CTL_TRIGSEL_S             20U
#define ADC_SOC1CTL_TRIGSEL_M             0x1F00000U   // SOC1 Trigger Source Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC2CTL register
//
//*************************************************************************************************
#define ADC_SOC2CTL_ACQPS_S               0U
#define ADC_SOC2CTL_ACQPS_M               0xFFU        // SOC2 Acquisition Prescale
#define ADC_SOC2CTL_SAMPCAPRESETDISABLE   0x200U       // SOC2 Sample Cap Reset Enable
#define ADC_SOC2CTL_SAMPCAPRESETSEL       0x400U       // SOC2 Sample Cap Reset Select
#define ADC_SOC2CTL_CHSEL_S               15U
#define ADC_SOC2CTL_CHSEL_M               0xF8000U     // SOC2 Channel Select
#define ADC_SOC2CTL_TRIGSEL_S             20U
#define ADC_SOC2CTL_TRIGSEL_M             0x1F00000U   // SOC2 Trigger Source Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC3CTL register
//
//*************************************************************************************************
#define ADC_SOC3CTL_ACQPS_S               0U
#define ADC_SOC3CTL_ACQPS_M               0xFFU        // SOC3 Acquisition Prescale
#define ADC_SOC3CTL_SAMPCAPRESETDISABLE   0x200U       // SOC3 Sample Cap Reset Enable
#define ADC_SOC3CTL_SAMPCAPRESETSEL       0x400U       // SOC3 Sample Cap Reset Select
#define ADC_SOC3CTL_CHSEL_S               15U
#define ADC_SOC3CTL_CHSEL_M               0xF8000U     // SOC3 Channel Select
#define ADC_SOC3CTL_TRIGSEL_S             20U
#define ADC_SOC3CTL_TRIGSEL_M             0x1F00000U   // SOC3 Trigger Source Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC4CTL register
//
//*************************************************************************************************
#define ADC_SOC4CTL_ACQPS_S               0U
#define ADC_SOC4CTL_ACQPS_M               0xFFU        // SOC4 Acquisition Prescale
#define ADC_SOC4CTL_SAMPCAPRESETDISABLE   0x200U       // SOC4 Sample Cap Reset Enable
#define ADC_SOC4CTL_SAMPCAPRESETSEL       0x400U       // SOC4 Sample Cap Reset Select
#define ADC_SOC4CTL_CHSEL_S               15U
#define ADC_SOC4CTL_CHSEL_M               0xF8000U     // SOC4 Channel Select
#define ADC_SOC4CTL_TRIGSEL_S             20U
#define ADC_SOC4CTL_TRIGSEL_M             0x1F00000U   // SOC4 Trigger Source Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC5CTL register
//
//*************************************************************************************************
#define ADC_SOC5CTL_ACQPS_S               0U
#define ADC_SOC5CTL_ACQPS_M               0xFFU        // SOC5 Acquisition Prescale
#define ADC_SOC5CTL_SAMPCAPRESETDISABLE   0x200U       // SOC5 Sample Cap Reset Enable
#define ADC_SOC5CTL_SAMPCAPRESETSEL       0x400U       // SOC5 Sample Cap Reset Select
#define ADC_SOC5CTL_CHSEL_S               15U
#define ADC_SOC5CTL_CHSEL_M               0xF8000U     // SOC5 Channel Select
#define ADC_SOC5CTL_TRIGSEL_S             20U
#define ADC_SOC5CTL_TRIGSEL_M             0x1F00000U   // SOC5 Trigger Source Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC6CTL register
//
//*************************************************************************************************
#define ADC_SOC6CTL_ACQPS_S               0U
#define ADC_SOC6CTL_ACQPS_M               0xFFU        // SOC6 Acquisition Prescale
#define ADC_SOC6CTL_SAMPCAPRESETDISABLE   0x200U       // SOC6 Sample Cap Reset Enable
#define ADC_SOC6CTL_SAMPCAPRESETSEL       0x400U       // SOC6 Sample Cap Reset Select
#define ADC_SOC6CTL_CHSEL_S               15U
#define ADC_SOC6CTL_CHSEL_M               0xF8000U     // SOC6 Channel Select
#define ADC_SOC6CTL_TRIGSEL_S             20U
#define ADC_SOC6CTL_TRIGSEL_M             0x1F00000U   // SOC6 Trigger Source Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC7CTL register
//
//*************************************************************************************************
#define ADC_SOC7CTL_ACQPS_S               0U
#define ADC_SOC7CTL_ACQPS_M               0xFFU        // SOC7 Acquisition Prescale
#define ADC_SOC7CTL_SAMPCAPRESETDISABLE   0x200U       // SOC7 Sample Cap Reset Enable
#define ADC_SOC7CTL_SAMPCAPRESETSEL       0x400U       // SOC7 Sample Cap Reset Select
#define ADC_SOC7CTL_CHSEL_S               15U
#define ADC_SOC7CTL_CHSEL_M               0xF8000U     // SOC7 Channel Select
#define ADC_SOC7CTL_TRIGSEL_S             20U
#define ADC_SOC7CTL_TRIGSEL_M             0x1F00000U   // SOC7 Trigger Source Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC8CTL register
//
//*************************************************************************************************
#define ADC_SOC8CTL_ACQPS_S               0U
#define ADC_SOC8CTL_ACQPS_M               0xFFU        // SOC8 Acquisition Prescale
#define ADC_SOC8CTL_SAMPCAPRESETDISABLE   0x200U       // SOC8 Sample Cap Reset Enable
#define ADC_SOC8CTL_SAMPCAPRESETSEL       0x400U       // SOC8 Sample Cap Reset Select
#define ADC_SOC8CTL_CHSEL_S               15U
#define ADC_SOC8CTL_CHSEL_M               0xF8000U     // SOC8 Channel Select
#define ADC_SOC8CTL_TRIGSEL_S             20U
#define ADC_SOC8CTL_TRIGSEL_M             0x1F00000U   // SOC8 Trigger Source Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC9CTL register
//
//*************************************************************************************************
#define ADC_SOC9CTL_ACQPS_S               0U
#define ADC_SOC9CTL_ACQPS_M               0xFFU        // SOC9 Acquisition Prescale
#define ADC_SOC9CTL_SAMPCAPRESETDISABLE   0x200U       // SOC9 Sample Cap Reset Enable
#define ADC_SOC9CTL_SAMPCAPRESETSEL       0x400U       // SOC9 Sample Cap Reset Select
#define ADC_SOC9CTL_CHSEL_S               15U
#define ADC_SOC9CTL_CHSEL_M               0xF8000U     // SOC9 Channel Select
#define ADC_SOC9CTL_TRIGSEL_S             20U
#define ADC_SOC9CTL_TRIGSEL_M             0x1F00000U   // SOC9 Trigger Source Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC10CTL register
//
//*************************************************************************************************
#define ADC_SOC10CTL_ACQPS_S               0U
#define ADC_SOC10CTL_ACQPS_M               0xFFU        // SOC10 Acquisition Prescale
#define ADC_SOC10CTL_SAMPCAPRESETDISABLE   0x200U       // SOC10 Sample Cap Reset Enable
#define ADC_SOC10CTL_SAMPCAPRESETSEL       0x400U       // SOC10 Sample Cap Reset Select
#define ADC_SOC10CTL_CHSEL_S               15U
#define ADC_SOC10CTL_CHSEL_M               0xF8000U     // SOC10 Channel Select
#define ADC_SOC10CTL_TRIGSEL_S             20U
#define ADC_SOC10CTL_TRIGSEL_M             0x1F00000U   // SOC10 Trigger Source Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC11CTL register
//
//*************************************************************************************************
#define ADC_SOC11CTL_ACQPS_S               0U
#define ADC_SOC11CTL_ACQPS_M               0xFFU        // SOC11 Acquisition Prescale
#define ADC_SOC11CTL_SAMPCAPRESETDISABLE   0x200U       // SOC11 Sample Cap Reset Enable
#define ADC_SOC11CTL_SAMPCAPRESETSEL       0x400U       // SOC11 Sample Cap Reset Select
#define ADC_SOC11CTL_CHSEL_S               15U
#define ADC_SOC11CTL_CHSEL_M               0xF8000U     // SOC11 Channel Select
#define ADC_SOC11CTL_TRIGSEL_S             20U
#define ADC_SOC11CTL_TRIGSEL_M             0x1F00000U   // SOC11 Trigger Source Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC12CTL register
//
//*************************************************************************************************
#define ADC_SOC12CTL_ACQPS_S               0U
#define ADC_SOC12CTL_ACQPS_M               0xFFU        // SOC12 Acquisition Prescale
#define ADC_SOC12CTL_SAMPCAPRESETDISABLE   0x200U       // SOC12 Sample Cap Reset Enable
#define ADC_SOC12CTL_SAMPCAPRESETSEL       0x400U       // SOC12 Sample Cap Reset Select
#define ADC_SOC12CTL_CHSEL_S               15U
#define ADC_SOC12CTL_CHSEL_M               0xF8000U     // SOC12 Channel Select
#define ADC_SOC12CTL_TRIGSEL_S             20U
#define ADC_SOC12CTL_TRIGSEL_M             0x1F00000U   // SOC12 Trigger Source Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC13CTL register
//
//*************************************************************************************************
#define ADC_SOC13CTL_ACQPS_S               0U
#define ADC_SOC13CTL_ACQPS_M               0xFFU        // SOC13 Acquisition Prescale
#define ADC_SOC13CTL_SAMPCAPRESETDISABLE   0x200U       // SOC13 Sample Cap Reset Enable
#define ADC_SOC13CTL_SAMPCAPRESETSEL       0x400U       // SOC13 Sample Cap Reset Select
#define ADC_SOC13CTL_CHSEL_S               15U
#define ADC_SOC13CTL_CHSEL_M               0xF8000U     // SOC13 Channel Select
#define ADC_SOC13CTL_TRIGSEL_S             20U
#define ADC_SOC13CTL_TRIGSEL_M             0x1F00000U   // SOC13 Trigger Source Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC14CTL register
//
//*************************************************************************************************
#define ADC_SOC14CTL_ACQPS_S               0U
#define ADC_SOC14CTL_ACQPS_M               0xFFU        // SOC14 Acquisition Prescale
#define ADC_SOC14CTL_SAMPCAPRESETDISABLE   0x200U       // SOC14 Sample Cap Reset Enable
#define ADC_SOC14CTL_SAMPCAPRESETSEL       0x400U       // SOC14 Sample Cap Reset Select
#define ADC_SOC14CTL_CHSEL_S               15U
#define ADC_SOC14CTL_CHSEL_M               0xF8000U     // SOC14 Channel Select
#define ADC_SOC14CTL_TRIGSEL_S             20U
#define ADC_SOC14CTL_TRIGSEL_M             0x1F00000U   // SOC14 Trigger Source Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC15CTL register
//
//*************************************************************************************************
#define ADC_SOC15CTL_ACQPS_S               0U
#define ADC_SOC15CTL_ACQPS_M               0xFFU        // SOC15 Acquisition Prescale
#define ADC_SOC15CTL_SAMPCAPRESETDISABLE   0x200U       // SOC15 Sample Cap Reset Enable
#define ADC_SOC15CTL_SAMPCAPRESETSEL       0x400U       // SOC15 Sample Cap Reset Select
#define ADC_SOC15CTL_CHSEL_S               15U
#define ADC_SOC15CTL_CHSEL_M               0xF8000U     // SOC15 Channel Select
#define ADC_SOC15CTL_TRIGSEL_S             20U
#define ADC_SOC15CTL_TRIGSEL_M             0x1F00000U   // SOC15 Trigger Source Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCEVTSTAT register
//
//*************************************************************************************************
#define ADC_EVTSTAT_PPB1TRIPHI    0x1U     // Post Processing Block 1 Trip High Flag
#define ADC_EVTSTAT_PPB1TRIPLO    0x2U     // Post Processing Block 1 Trip Low Flag
#define ADC_EVTSTAT_PPB1ZERO      0x4U     // Post Processing Block 1 Zero Crossing Flag
#define ADC_EVTSTAT_PPB1INLIMIT   0x8U     // Post Processing Block 1 Within trip limit Flag
#define ADC_EVTSTAT_PPB2TRIPHI    0x10U    // Post Processing Block 2 Trip High Flag
#define ADC_EVTSTAT_PPB2TRIPLO    0x20U    // Post Processing Block 2 Trip Low Flag
#define ADC_EVTSTAT_PPB2ZERO      0x40U    // Post Processing Block 2 Zero Crossing Flag
#define ADC_EVTSTAT_PPB2INLIMIT   0x80U    // Post Processing Block 2 Within trip limit Flag
#define ADC_EVTSTAT_PPB3TRIPHI    0x100U   // Post Processing Block 3 Trip High Flag
#define ADC_EVTSTAT_PPB3TRIPLO    0x200U   // Post Processing Block 3 Trip Low Flag
#define ADC_EVTSTAT_PPB3ZERO      0x400U   // Post Processing Block 3 Zero Crossing Flag
#define ADC_EVTSTAT_PPB3INLIMIT   0x800U   // Post Processing Block 3 Within trip limit Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCEVTCLR register
//
//*************************************************************************************************
#define ADC_EVTCLR_PPB1TRIPHI    0x1U     // Post Processing Block 1 Trip High Clear
#define ADC_EVTCLR_PPB1TRIPLO    0x2U     // Post Processing Block 1 Trip Low Clear
#define ADC_EVTCLR_PPB1ZERO      0x4U     // Post Processing Block 1 Zero Crossing Clear
#define ADC_EVTCLR_PPB1INLIMIT   0x8U     // Post Processing Block 1 Within trip limit flag Clear
#define ADC_EVTCLR_PPB2TRIPHI    0x10U    // Post Processing Block 2 Trip High Clear
#define ADC_EVTCLR_PPB2TRIPLO    0x20U    // Post Processing Block 2 Trip Low Clear
#define ADC_EVTCLR_PPB2ZERO      0x40U    // Post Processing Block 2 Zero Crossing Clear
#define ADC_EVTCLR_PPB2INLIMIT   0x80U    // Post Processing Block 2 Within trip limit flag Clear
#define ADC_EVTCLR_PPB3TRIPHI    0x100U   // Post Processing Block 3 Trip High Clear
#define ADC_EVTCLR_PPB3TRIPLO    0x200U   // Post Processing Block 3 Trip Low Clear
#define ADC_EVTCLR_PPB3ZERO      0x400U   // Post Processing Block 3 Zero Crossing Clear
#define ADC_EVTCLR_PPB3INLIMIT   0x800U   // Post Processing Block 3 Within trip limit flag Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCEVTSEL register
//
//*************************************************************************************************
#define ADC_EVTSEL_PPB1TRIPHI    0x1U     // Post Processing Block 1 Trip High Event Enable
#define ADC_EVTSEL_PPB1TRIPLO    0x2U     // Post Processing Block 1 Trip Low Event Enable
#define ADC_EVTSEL_PPB1ZERO      0x4U     // Post Processing Block 1 Zero Crossing Event Enable
#define ADC_EVTSEL_PPB1INLIMIT   0x8U     // Post Processing Block 1 Within trip limit event enable
#define ADC_EVTSEL_PPB2TRIPHI    0x10U    // Post Processing Block 2 Trip High Event Enable
#define ADC_EVTSEL_PPB2TRIPLO    0x20U    // Post Processing Block 2 Trip Low Event Enable
#define ADC_EVTSEL_PPB2ZERO      0x40U    // Post Processing Block 2 Zero Crossing Event Enable
#define ADC_EVTSEL_PPB2INLIMIT   0x80U    // Post Processing Block 2 Within trip limit event enable
#define ADC_EVTSEL_PPB3TRIPHI    0x100U   // Post Processing Block 3 Trip High Event Enable
#define ADC_EVTSEL_PPB3TRIPLO    0x200U   // Post Processing Block 3 Trip Low Event Enable
#define ADC_EVTSEL_PPB3ZERO      0x400U   // Post Processing Block 3 Zero Crossing Event Enable
#define ADC_EVTSEL_PPB3INLIMIT   0x800U   // Post Processing Block 3 Within trip limit event enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCEVTINTSEL register
//
//*************************************************************************************************
#define ADC_EVTINTSEL_PPB1TRIPHI    0x1U     // Post Processing Block 1 Trip High Interrupt Enable
#define ADC_EVTINTSEL_PPB1TRIPLO    0x2U     // Post Processing Block 1 Trip Low Interrupt Enable
#define ADC_EVTINTSEL_PPB1ZERO      0x4U     // Post Processing Block 1 Zero Crossing Interrupt
                                             // Enable
#define ADC_EVTINTSEL_PPB1INLIMIT   0x8U     // Post Processing Block 1 Within trip limit interrupt
                                             // enable
#define ADC_EVTINTSEL_PPB2TRIPHI    0x10U    // Post Processing Block 2 Trip High Interrupt Enable
#define ADC_EVTINTSEL_PPB2TRIPLO    0x20U    // Post Processing Block 2 Trip Low Interrupt Enable
#define ADC_EVTINTSEL_PPB2ZERO      0x40U    // Post Processing Block 2 Zero Crossing Interrupt
                                             // Enable
#define ADC_EVTINTSEL_PPB2INLIMIT   0x80U    // Post Processing Block 2 Within trip limit interrupt
                                             // enable
#define ADC_EVTINTSEL_PPB3TRIPHI    0x100U   // Post Processing Block 3 Trip High Interrupt Enable
#define ADC_EVTINTSEL_PPB3TRIPLO    0x200U   // Post Processing Block 3 Trip Low Interrupt Enable
#define ADC_EVTINTSEL_PPB3ZERO      0x400U   // Post Processing Block 3 Zero Crossing Interrupt
                                             // Enable
#define ADC_EVTINTSEL_PPB3INLIMIT   0x800U   // Post Processing Block 3 Within trip limit interrupt
                                             // enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCREV register
//
//*************************************************************************************************
#define ADC_REV_TYPE_S   0U
#define ADC_REV_TYPE_M   0xFFU         // ADC Type
#define ADC_REV_REV_S    8U
#define ADC_REV_REV_M    0xFFFFFF00U   // ADC Revision

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCOFFTRIM register
//
//*************************************************************************************************
#define ADC_OFFTRIM_OFFTRIM_S   0U
#define ADC_OFFTRIM_OFFTRIM_M   0xFFU   // ADC Offset Trim

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB1CONFIG register
//
//*************************************************************************************************
#define ADC_PPB1CONFIG_CONFIG_S     0U
#define ADC_PPB1CONFIG_CONFIG_M     0xFU    // ADC Post Processing Block {#} Configuration
#define ADC_PPB1CONFIG_CBCEN        0x20U   // Cycle By Cycle Enable
#define ADC_PPB1CONFIG_TWOSCOMPEN   0x80U   // ADC Post Processing Block {#} Two's Complement
                                            // Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB1OFFCAL register
//
//*************************************************************************************************
#define ADC_PPB1OFFCAL_OFFCAL_S   0U
#define ADC_PPB1OFFCAL_OFFCAL_M   0x3FU   // ADC Post Processing Block Offset Correction

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB1OFFREF register
//
//*************************************************************************************************
#define ADC_PPB1OFFREF_OFFREF_S   0U
#define ADC_PPB1OFFREF_OFFREF_M   0xFFFU   // ADC Post Processing Block 1 Offset Reference

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB1TRIPHI register
//
//*************************************************************************************************
#define ADC_PPB1TRIPHI_LIMITHI_S   0U
#define ADC_PPB1TRIPHI_LIMITHI_M   0xFFFFU   // ADC Post Processing Block 1 Trip High Limit

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB1TRIPLO register
//
//*************************************************************************************************
#define ADC_PPB1TRIPLO_LIMITLO_S   0U
#define ADC_PPB1TRIPLO_LIMITLO_M   0xFFFFU   // ADC Post Processing Block 1 Trip Low Limit

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB2CONFIG register
//
//*************************************************************************************************
#define ADC_PPB2CONFIG_CONFIG_S     0U
#define ADC_PPB2CONFIG_CONFIG_M     0xFU    // ADC Post Processing Block {#} Configuration
#define ADC_PPB2CONFIG_CBCEN        0x20U   // Cycle By Cycle Enable
#define ADC_PPB2CONFIG_TWOSCOMPEN   0x80U   // ADC Post Processing Block {#} Two's Complement
                                            // Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB2OFFCAL register
//
//*************************************************************************************************
#define ADC_PPB2OFFCAL_OFFCAL_S   0U
#define ADC_PPB2OFFCAL_OFFCAL_M   0x3FU   // ADC Post Processing Block Offset Correction

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB2OFFREF register
//
//*************************************************************************************************
#define ADC_PPB2OFFREF_OFFREF_S   0U
#define ADC_PPB2OFFREF_OFFREF_M   0xFFFU   // ADC Post Processing Block 2 Offset Reference

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB2TRIPHI register
//
//*************************************************************************************************
#define ADC_PPB2TRIPHI_LIMITHI_S   0U
#define ADC_PPB2TRIPHI_LIMITHI_M   0xFFFFU   // ADC Post Processing Block 2 Trip High Limit

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB2TRIPLO register
//
//*************************************************************************************************
#define ADC_PPB2TRIPLO_LIMITLO_S   0U
#define ADC_PPB2TRIPLO_LIMITLO_M   0xFFFFU   // ADC Post Processing Block 2 Trip Low Limit

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB3CONFIG register
//
//*************************************************************************************************
#define ADC_PPB3CONFIG_CONFIG_S     0U
#define ADC_PPB3CONFIG_CONFIG_M     0xFU    // ADC Post Processing Block {#} Configuration
#define ADC_PPB3CONFIG_CBCEN        0x20U   // Cycle By Cycle Enable
#define ADC_PPB3CONFIG_TWOSCOMPEN   0x80U   // ADC Post Processing Block {#} Two's Complement
                                            // Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB3OFFCAL register
//
//*************************************************************************************************
#define ADC_PPB3OFFCAL_OFFCAL_S   0U
#define ADC_PPB3OFFCAL_OFFCAL_M   0x3FU   // ADC Post Processing Block Offset Correction

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB3OFFREF register
//
//*************************************************************************************************
#define ADC_PPB3OFFREF_OFFREF_S   0U
#define ADC_PPB3OFFREF_OFFREF_M   0xFFFU   // ADC Post Processing Block 3 Offset Reference

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB3TRIPHI register
//
//*************************************************************************************************
#define ADC_PPB3TRIPHI_LIMITHI_S   0U
#define ADC_PPB3TRIPHI_LIMITHI_M   0xFFFFU   // ADC Post Processing Block 3 Trip High Limit

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB3TRIPLO register
//
//*************************************************************************************************
#define ADC_PPB3TRIPLO_LIMITLO_S   0U
#define ADC_PPB3TRIPLO_LIMITLO_M   0xFFFFU   // ADC Post Processing Block 3 Trip Low Limit

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCINTCYCLE register
//
//*************************************************************************************************
#define ADC_INTCYCLE_DELAY_S   0U
#define ADC_INTCYCLE_DELAY_M   0x3FU   // Delay from ADCSOC fall edge to early interrupt
                                       // generation.

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCREV2 register
//
//*************************************************************************************************
#define ADC_REV2_WRAPPERTYPE_S   0U
#define ADC_REV2_WRAPPERTYPE_M   0xFFU         // ADC Wrapper Type
#define ADC_REV2_WRAPPERREV_S    8U
#define ADC_REV2_WRAPPERREV_M    0xFFFFFF00U   // ADC Wrapper Revision

//*************************************************************************************************
//
// The following are defines for the bit fields in the REP1CTL register
//
//*************************************************************************************************
#define ADC_REP1CTL_MODULEBUSY    0x8U        // ADC Trigger Repeater 1 Module Busy
#define ADC_REP1CTL_TRIGGEROVF    0x80U       // ADC Trigger Repeater 1 Oversampled Trigger
                                              // Overflow
#define ADC_REP1CTL_TRIGGER_S     8U
#define ADC_REP1CTL_TRIGGER_M     0x1F00U     // ADC Trigger Repeater 1 Trigger Select
#define ADC_REP1CTL_SYNCINSEL_S   16U
#define ADC_REP1CTL_SYNCINSEL_M   0x70000U    // ADC Trigger Repeater 1 Sync. In Select
#define ADC_REP1CTL_SWSYNC        0x800000U   // ADC Trigger Repeater 1 Software Sync.

//*************************************************************************************************
//
// The following are defines for the bit fields in the REP1N register
//
//*************************************************************************************************
#define ADC_REP1N_NSEL_S     0U
#define ADC_REP1N_NSEL_M     0x3U       // ADC Trigger Repeater 1 Trigger Number Selection
#define ADC_REP1N_NCOUNT_S   16U
#define ADC_REP1N_NCOUNT_M   0x70000U   // ADC Trigger Repeater 1 Trigger Counter

//*************************************************************************************************
//
// The following are defines for the bit fields in the REP1SPREAD register
//
//*************************************************************************************************
#define ADC_REP1SPREAD_SPREAD_S        0U
#define ADC_REP1SPREAD_SPREAD_M        0xFFFFU       // ADC Trigger Repeater 1 Spread Delay
                                                     // Configuration
#define ADC_REP1SPREAD_SPREADCOUNT_S   16U
#define ADC_REP1SPREAD_SPREADCOUNT_M   0xFFFF0000U   // ADC Trigger Repeater 1 Spread Delay Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the REP1FRC register
//
//*************************************************************************************************
#define ADC_REP1FRC_SWFRC   0x1U   // ADC Trigger Repeater 1 Software Force

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB1LIMIT register
//
//*************************************************************************************************
#define ADC_PPB1LIMIT_LIMIT_S   0U
#define ADC_PPB1LIMIT_LIMIT_M   0x3U   // Post Processing Block 1 Limit

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPBP1PCOUNT register
//
//*************************************************************************************************
#define ADC_PPBP1PCOUNT_PCOUNT_S   0U
#define ADC_PPBP1PCOUNT_PCOUNT_M   0x7U   // Post Processing Block 1 Partial Count

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB1CONFIG2 register
//
//*************************************************************************************************
#define ADC_PPB1CONFIG2_SHIFT_S       0U
#define ADC_PPB1CONFIG2_SHIFT_M       0x7U      // Post Processing Block 1 Right Shift
#define ADC_PPB1CONFIG2_SYNCINSEL_S   4U
#define ADC_PPB1CONFIG2_SYNCINSEL_M   0x70U     // Post Processing Block 1 Sync. Input Select
#define ADC_PPB1CONFIG2_SWSYNC        0x800U    // Post Processing Block 1 Software Force Sync.
#define ADC_PPB1CONFIG2_OSINTSEL      0x1000U   // Post Processing Block 1 Interrupt Source Select
#define ADC_PPB1CONFIG2_COMPSEL       0x8000U   // Post Processing Block 1 Compare Source Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB1PSUM register
//
//*************************************************************************************************
#define ADC_PPB1PSUM_PSUM_S   0U
#define ADC_PPB1PSUM_PSUM_M   0xFFFFU       // Post Processing Block 1 Oversampling Partial Sum
#define ADC_PPB1PSUM_SIGN_S   16U
#define ADC_PPB1PSUM_SIGN_M   0xFFFF0000U   // Sign Extended Bits


//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCRESULT0 register
//
//*************************************************************************************************
#define ADC_RESULT0_RESULT_S   0U
#define ADC_RESULT0_RESULT_M   0xFFFU   // ADC Result

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCRESULT1 register
//
//*************************************************************************************************
#define ADC_RESULT1_RESULT_S   0U
#define ADC_RESULT1_RESULT_M   0xFFFU   // ADC Result

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCRESULT2 register
//
//*************************************************************************************************
#define ADC_RESULT2_RESULT_S   0U
#define ADC_RESULT2_RESULT_M   0xFFFU   // ADC Result

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCRESULT3 register
//
//*************************************************************************************************
#define ADC_RESULT3_RESULT_S   0U
#define ADC_RESULT3_RESULT_M   0xFFFU   // ADC Result

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCRESULT4 register
//
//*************************************************************************************************
#define ADC_RESULT4_RESULT_S   0U
#define ADC_RESULT4_RESULT_M   0xFFFU   // ADC Result

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCRESULT5 register
//
//*************************************************************************************************
#define ADC_RESULT5_RESULT_S   0U
#define ADC_RESULT5_RESULT_M   0xFFFU   // ADC Result

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCRESULT6 register
//
//*************************************************************************************************
#define ADC_RESULT6_RESULT_S   0U
#define ADC_RESULT6_RESULT_M   0xFFFU   // ADC Result

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCRESULT7 register
//
//*************************************************************************************************
#define ADC_RESULT7_RESULT_S   0U
#define ADC_RESULT7_RESULT_M   0xFFFU   // ADC Result

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCRESULT8 register
//
//*************************************************************************************************
#define ADC_RESULT8_RESULT_S   0U
#define ADC_RESULT8_RESULT_M   0xFFFU   // ADC Result

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCRESULT9 register
//
//*************************************************************************************************
#define ADC_RESULT9_RESULT_S   0U
#define ADC_RESULT9_RESULT_M   0xFFFU   // ADC Result

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCRESULT10 register
//
//*************************************************************************************************
#define ADC_RESULT10_RESULT_S   0U
#define ADC_RESULT10_RESULT_M   0xFFFU   // ADC Result

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCRESULT11 register
//
//*************************************************************************************************
#define ADC_RESULT11_RESULT_S   0U
#define ADC_RESULT11_RESULT_M   0xFFFU   // ADC Result

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCRESULT12 register
//
//*************************************************************************************************
#define ADC_RESULT12_RESULT_S   0U
#define ADC_RESULT12_RESULT_M   0xFFFU   // ADC Result

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCRESULT13 register
//
//*************************************************************************************************
#define ADC_RESULT13_RESULT_S   0U
#define ADC_RESULT13_RESULT_M   0xFFFU   // ADC Result

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCRESULT14 register
//
//*************************************************************************************************
#define ADC_RESULT14_RESULT_S   0U
#define ADC_RESULT14_RESULT_M   0xFFFU   // ADC Result

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCRESULT15 register
//
//*************************************************************************************************
#define ADC_RESULT15_RESULT_S   0U
#define ADC_RESULT15_RESULT_M   0xFFFU   // ADC Result

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB1RESULT register
//
//*************************************************************************************************
#define ADC_PPB1RESULT_PPBRESULT_S   0U
#define ADC_PPB1RESULT_PPBRESULT_M   0x1FFFU       // ADC Post Processing Block Result
#define ADC_PPB1RESULT_SIGN_S        13U
#define ADC_PPB1RESULT_SIGN_M        0xFFFFE000U   // Sign Extended Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB2RESULT register
//
//*************************************************************************************************
#define ADC_PPB2RESULT_PPBRESULT_S   0U
#define ADC_PPB2RESULT_PPBRESULT_M   0x1FFFU       // ADC Post Processing Block Result
#define ADC_PPB2RESULT_SIGN_S        13U
#define ADC_PPB2RESULT_SIGN_M        0xFFFFE000U   // Sign Extended Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB3RESULT register
//
//*************************************************************************************************
#define ADC_PPB3RESULT_PPBRESULT_S   0U
#define ADC_PPB3RESULT_PPBRESULT_M   0x1FFFU       // ADC Post Processing Block Result
#define ADC_PPB3RESULT_SIGN_S        13U
#define ADC_PPB3RESULT_SIGN_M        0xFFFFE000U   // Sign Extended Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB1SUM register
//
//*************************************************************************************************
#define ADC_PPB1SUM_SUM_S    0U
#define ADC_PPB1SUM_SUM_M    0xFFFFU       // Post Processing Block 1 Oversampling Sum
#define ADC_PPB1SUM_SIGN_S   16U
#define ADC_PPB1SUM_SIGN_M   0xFFFF0000U   // Sign Extended Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB1COUNT register
//
//*************************************************************************************************
#define ADC_PPB1COUNT_COUNT_S   0U
#define ADC_PPB1COUNT_COUNT_M   0xFU   // Post Processing Block 1 Final Count



#endif
