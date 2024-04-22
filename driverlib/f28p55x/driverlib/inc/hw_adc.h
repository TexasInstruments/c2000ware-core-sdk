//###########################################################################
//
// FILE:    hw_adc.h
//
// TITLE:   Definitions for the ADC registers.
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

#ifndef HW_ADC_H
#define HW_ADC_H

//*************************************************************************************************
//
// The following are defines for the ADC register offsets
//
//*************************************************************************************************
#define ADC_O_CTL1                0x0U     // ADC Control 1 Register
#define ADC_O_CTL2                0x1U     // ADC Control 2 Register
#define ADC_O_BURSTCTL            0x6U     // ADC Burst Control Register
#define ADC_O_INTFLG              0x7U     // ADC Interrupt Flag Register
#define ADC_O_INTFLGCLR           0x8U     // ADC Interrupt Flag Clear Register
#define ADC_O_INTOVF              0x9U     // ADC Interrupt Overflow Register
#define ADC_O_INTOVFCLR           0xAU     // ADC Interrupt Overflow Clear Register
#define ADC_O_INTSEL1N2           0xBU     // ADC Interrupt 1 and 2 Selection Register
#define ADC_O_INTSEL3N4           0xCU     // ADC Interrupt 3 and 4 Selection Register
#define ADC_O_SOCPRICTL           0xDU     // ADC SOC Priority Control Register
#define ADC_O_INTSOCSEL1          0xEU     // ADC Interrupt SOC Selection 1 Register
#define ADC_O_SOCFLG1             0x12U    // ADC SOC Flag 1 Register
#define ADC_O_SOCFRC1             0x14U    // ADC SOC Force 1 Register
#define ADC_O_SOCOVF1             0x16U    // ADC SOC Overflow 1 Register
#define ADC_O_SOCOVFCLR1          0x18U    // ADC SOC Overflow Clear 1 Register
#define ADC_O_SOC0CTL             0x1AU    // ADC SOC0 Control Register
#define ADC_O_SOC1CTL             0x1CU    // ADC SOC1 Control Register
#define ADC_O_SOC2CTL             0x1EU    // ADC SOC2 Control Register
#define ADC_O_SOC3CTL             0x20U    // ADC SOC3 Control Register
#define ADC_O_SOC4CTL             0x22U    // ADC SOC4 Control Register
#define ADC_O_SOC5CTL             0x24U    // ADC SOC5 Control Register
#define ADC_O_SOC6CTL             0x26U    // ADC SOC6 Control Register
#define ADC_O_SOC7CTL             0x28U    // ADC SOC7 Control Register
#define ADC_O_SOC8CTL             0x2AU    // ADC SOC8 Control Register
#define ADC_O_SOC9CTL             0x2CU    // ADC SOC9 Control Register
#define ADC_O_SOC10CTL            0x2EU    // ADC SOC10 Control Register
#define ADC_O_SOC11CTL            0x30U    // ADC SOC11 Control Register
#define ADC_O_SOC12CTL            0x32U    // ADC SOC12 Control Register
#define ADC_O_SOC13CTL            0x34U    // ADC SOC13 Control Register
#define ADC_O_SOC14CTL            0x36U    // ADC SOC14 Control Register
#define ADC_O_SOC15CTL            0x38U    // ADC SOC15 Control Register
#define ADC_O_EVTSTAT             0x5AU    // ADC Event Status Register
#define ADC_O_EVTCLR              0x5CU    // ADC Event Clear Register
#define ADC_O_EVTSEL              0x5EU    // ADC Event Selection Register
#define ADC_O_EVTINTSEL           0x60U    // ADC Event Interrupt Selection Register
#define ADC_O_COUNTER             0x63U    // ADC Counter Register
#define ADC_O_REV                 0x64U    // ADC Revision Register
#define ADC_O_OFFTRIM             0x65U    // ADC Offset Trim Register
#define ADC_O_CONFIG2             0x66U    // ADC Config Register Upper 32 bits
#define ADC_O_PPB1CONFIG          0x6AU    // ADC PPB{#} Config Register
#define ADC_O_PPB1STAMP           0x6BU    // ADC PPB1 Sample Delay Time Stamp Register
#define ADC_O_PPB1OFFCAL          0x6CU    // ADC PPB1 Offset Calibration Register
#define ADC_O_PPB1OFFREF          0x6DU    // ADC PPB1 Offset Reference Register
#define ADC_O_PPB1TRIPHI          0x6EU    // ADC PPB1 Trip High Register
#define ADC_O_PPB1TRIPLO          0x70U    // ADC PPB1 Trip Low/Trigger Time Stamp Register
#define ADC_O_PPBTRIP1FILCTL      0x72U    // ADCEVT1 Trip High Filter Control Register
#define ADC_O_PPBTRIP1FILCLKCTL   0x74U    // ADCEVT1 Trip High Filter Prescale Control Register
#define ADC_O_PPB2CONFIG          0x7AU    // ADC PPB{#} Config Register
#define ADC_O_PPB2STAMP           0x7BU    // ADC PPB2 Sample Delay Time Stamp Register
#define ADC_O_PPB2OFFCAL          0x7CU    // ADC PPB2 Offset Calibration Register
#define ADC_O_PPB2OFFREF          0x7DU    // ADC PPB2 Offset Reference Register
#define ADC_O_PPB2TRIPHI          0x7EU    // ADC PPB2 Trip High Register
#define ADC_O_PPB2TRIPLO          0x80U    // ADC PPB2 Trip Low/Trigger Time Stamp Register
#define ADC_O_PPBTRIP2FILCTL      0x82U    // ADCEVT2 Trip High Filter Control Register
#define ADC_O_PPBTRIP2FILCLKCTL   0x84U    // ADCEVT2 Trip High Filter Prescale Control Register
#define ADC_O_PPB3CONFIG          0x8AU    // ADC PPB{#} Config Register
#define ADC_O_PPB3STAMP           0x8BU    // ADC PPB3 Sample Delay Time Stamp Register
#define ADC_O_PPB3OFFCAL          0x8CU    // ADC PPB3 Offset Calibration Register
#define ADC_O_PPB3OFFREF          0x8DU    // ADC PPB3 Offset Reference Register
#define ADC_O_PPB3TRIPHI          0x8EU    // ADC PPB3 Trip High Register
#define ADC_O_PPB3TRIPLO          0x90U    // ADC PPB3 Trip Low/Trigger Time Stamp Register
#define ADC_O_PPBTRIP3FILCTL      0x92U    // ADCEVT3 Trip High Filter Control Register
#define ADC_O_PPBTRIP3FILCLKCTL   0x94U    // ADCEVT3 Trip High Filter Prescale Control Register
#define ADC_O_PPB4CONFIG          0x9AU    // ADC PPB{#} Config Register
#define ADC_O_PPB4STAMP           0x9BU    // ADC PPB4 Sample Delay Time Stamp Register
#define ADC_O_PPB4OFFCAL          0x9CU    // ADC PPB4 Offset Calibration Register
#define ADC_O_PPB4OFFREF          0x9DU    // ADC PPB4 Offset Reference Register
#define ADC_O_PPB4TRIPHI          0x9EU    // ADC PPB4 Trip High Register
#define ADC_O_PPB4TRIPLO          0xA0U    // ADC PPB4 Trip Low/Trigger Time Stamp Register
#define ADC_O_PPBTRIP4FILCTL      0xA2U    // ADCEVT4 Trip High Filter Control Register
#define ADC_O_PPBTRIP4FILCLKCTL   0xA4U    // ADCEVT4 Trip High Filter Prescale Control Register
#define ADC_O_INTCYCLE            0xB9U    // ADC Early Interrupt Generation Cycle
#define ADC_O_INLTRIM1            0xBAU    // ADC Linearity Trim 1 Register
#define ADC_O_INLTRIM2            0xBCU    // ADC Linearity Trim 2 Register
#define ADC_O_INLTRIM3            0xBEU    // ADC Linearity Trim 3 Register
#define ADC_O_INLTRIM4            0xC0U    // ADC Linearity Trim 4 Register
#define ADC_O_INLTRIM5            0xC2U    // ADC Linearity Trim 5 Register
#define ADC_O_INLTRIM6            0xC4U    // ADC Linearity Trim 6 Register
#define ADC_O_REV2                0xC7U    // ADC Wrapper Revision Register
#define ADC_O_REP1CTL             0xCAU    // ADC Trigger Repeater 1 Control Register
#define ADC_O_REP1N               0xCCU    // ADC Trigger Repeater 1 N Select Register
#define ADC_O_REP1PHASE           0xCEU    // ADC Trigger Repeater 1 Phase Select Register
#define ADC_O_REP1SPREAD          0xD0U    // ADC Trigger Repeater 1 Spread Select Register
#define ADC_O_REP1FRC             0xD2U    // ADC Trigger Repeater 1 Software Force Register
#define ADC_O_REP2CTL             0xDAU    // ADC Trigger Repeater 2 Control Register
#define ADC_O_REP2N               0xDCU    // ADC Trigger Repeater 2 N Select Register
#define ADC_O_REP2PHASE           0xDEU    // ADC Trigger Repeater 2 Phase Select Register
#define ADC_O_REP2SPREAD          0xE0U    // ADC Trigger Repeater 2 Spread Select Register
#define ADC_O_REP2FRC             0xE2U    // ADC Trigger Repeater 2 Software Force Register
#define ADC_O_PPB1LIMIT           0xEAU    // ADC PPB1Conversion Count Limit Register
#define ADC_O_PPBP1PCOUNT         0xECU    // ADC PPB1 Partial Conversion Count Register
#define ADC_O_PPB1CONFIG2         0xEEU    // ADC PPB1 Sum Shift Register
#define ADC_O_PPB1PSUM            0xF0U    // ADC PPB1 Partial Sum Register
#define ADC_O_PPB1PMAX            0xF2U    // ADC PPB1 Partial Max Register
#define ADC_O_PPB1PMAXI           0xF4U    // ADC PPB1 Partial Max Index Register
#define ADC_O_PPB1PMIN            0xF6U    // ADC PPB1 Partial MIN Register
#define ADC_O_PPB1PMINI           0xF8U    // ADC PPB1 Partial Min Index Register
#define ADC_O_PPB1TRIPLO2         0xFAU    // ADC PPB1 Extended Trip Low Register
#define ADC_O_PPB2LIMIT           0x104U   // ADC PPB2Conversion Count Limit Register
#define ADC_O_PPBP2PCOUNT         0x106U   // ADC PPB2 Partial Conversion Count Register
#define ADC_O_PPB2CONFIG2         0x108U   // ADC PPB2 Sum Shift Register
#define ADC_O_PPB2PSUM            0x10AU   // ADC PPB2 Partial Sum Register
#define ADC_O_PPB2PMAX            0x10CU   // ADC PPB2 Partial Max Register
#define ADC_O_PPB2PMAXI           0x10EU   // ADC PPB2 Partial Max Index Register
#define ADC_O_PPB2PMIN            0x110U   // ADC PPB2 Partial MIN Register
#define ADC_O_PPB2PMINI           0x112U   // ADC PPB2 Partial Min Index Register
#define ADC_O_PPB2TRIPLO2         0x114U   // ADC PPB2 Extended Trip Low Register
#define ADC_O_PPB3LIMIT           0x11EU   // ADC PPB3Conversion Count Limit Register
#define ADC_O_PPBP3PCOUNT         0x120U   // ADC PPB3 Partial Conversion Count Register
#define ADC_O_PPB3CONFIG2         0x122U   // ADC PPB3 Sum Shift Register
#define ADC_O_PPB3PSUM            0x124U   // ADC PPB3 Partial Sum Register
#define ADC_O_PPB3PMAX            0x126U   // ADC PPB3 Partial Max Register
#define ADC_O_PPB3PMAXI           0x128U   // ADC PPB3 Partial Max Index Register
#define ADC_O_PPB3PMIN            0x12AU   // ADC PPB3 Partial MIN Register
#define ADC_O_PPB3PMINI           0x12CU   // ADC PPB3 Partial Min Index Register
#define ADC_O_PPB3TRIPLO2         0x12EU   // ADC PPB3 Extended Trip Low Register
#define ADC_O_PPB4LIMIT           0x138U   // ADC PPB4Conversion Count Limit Register
#define ADC_O_PPBP4PCOUNT         0x13AU   // ADC PPB4 Partial Conversion Count Register
#define ADC_O_PPB4CONFIG2         0x13CU   // ADC PPB4 Sum Shift Register
#define ADC_O_PPB4PSUM            0x13EU   // ADC PPB4 Partial Sum Register
#define ADC_O_PPB4PMAX            0x140U   // ADC PPB4 Partial Max Register
#define ADC_O_PPB4PMAXI           0x142U   // ADC PPB4 Partial Max Index Register
#define ADC_O_PPB4PMIN            0x144U   // ADC PPB4 Partial MIN Register
#define ADC_O_PPB4PMINI           0x146U   // ADC PPB4 Partial Min Index Register
#define ADC_O_PPB4TRIPLO2         0x148U   // ADC PPB4 Extended Trip Low Register

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
#define ADC_O_PPB4RESULT   0x26U   // ADC Post Processing Block 4 Result Register
#define ADC_O_PPB1SUM      0x28U   // ADC PPB 1 Final Sum Result Register
#define ADC_O_PPB1COUNT    0x2AU   // ADC PPB1 Final Conversion Count Register
#define ADC_O_PPB2SUM      0x2CU   // ADC PPB 2 Final Sum Result Register
#define ADC_O_PPB2COUNT    0x2EU   // ADC PPB2 Final Conversion Count Register
#define ADC_O_PPB3SUM      0x30U   // ADC PPB 3 Final Sum Result Register
#define ADC_O_PPB3COUNT    0x32U   // ADC PPB3 Final Conversion Count Register
#define ADC_O_PPB4SUM      0x34U   // ADC PPB 4 Final Sum Result Register
#define ADC_O_PPB4COUNT    0x36U   // ADC PPB4 Final Conversion Count Register
#define ADC_O_PPB1MAX      0x38U   // ADC PPB 1 Final Max Result Register
#define ADC_O_PPB1MAXI     0x3AU   // ADC PPB 1 Final Max Index Result Register
#define ADC_O_PPB1MIN      0x3CU   // ADC PPB 1 Final Min Result Register
#define ADC_O_PPB1MINI     0x3EU   // ADC PPB 1 Final Min Index Result Register
#define ADC_O_PPB2MAX      0x40U   // ADC PPB 2 Final Max Result Register
#define ADC_O_PPB2MAXI     0x42U   // ADC PPB 2 Final Max Index Result Register
#define ADC_O_PPB2MIN      0x44U   // ADC PPB 2 Final Min Result Register
#define ADC_O_PPB2MINI     0x46U   // ADC PPB 2 Final Min Index Result Register
#define ADC_O_PPB3MAX      0x48U   // ADC PPB 3 Final Max Result Register
#define ADC_O_PPB3MAXI     0x4AU   // ADC PPB 3 Final Max Index Result Register
#define ADC_O_PPB3MIN      0x4CU   // ADC PPB 3 Final Min Result Register
#define ADC_O_PPB3MINI     0x4EU   // ADC PPB 3 Final Min Index Result Register
#define ADC_O_PPB4MAX      0x50U   // ADC PPB 4 Final Max Result Register
#define ADC_O_PPB4MAXI     0x52U   // ADC PPB 4 Final Max Index Result Register
#define ADC_O_PPB4MIN      0x54U   // ADC PPB 4 Final Min Result Register
#define ADC_O_PPB4MINI     0x56U   // ADC PPB 4 Final Min Index Result Register


//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCCTL1 register
//
//*************************************************************************************************
#define ADC_CTL1_INTPULSEPOS         0x4U      // ADC Interrupt Pulse Position
#define ADC_CTL1_ADCPWDNZ            0x80U     // ADC Power Down
#define ADC_CTL1_ADCBSYCHN_S         8U
#define ADC_CTL1_ADCBSYCHN_M         0xF00U    // ADC Busy Channel
#define ADC_CTL1_ADCBSY              0x2000U   // ADC Busy
#define ADC_CTL1_EXTMUXPRESELECTEN   0x4000U   // External Mux Preselect Enable
#define ADC_CTL1_TDMAEN              0x8000U   // Enable Alternate DMA Timings

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCCTL2 register
//
//*************************************************************************************************
#define ADC_CTL2_PRESCALE_S   0U
#define ADC_CTL2_PRESCALE_M   0xFU   // ADC Clock Prescaler

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCBURSTCTL register
//
//*************************************************************************************************
#define ADC_BURSTCTL_BURSTTRIGSEL_S   0U
#define ADC_BURSTCTL_BURSTTRIGSEL_M   0x7FU     // SOC Burst Trigger Source Select
#define ADC_BURSTCTL_BURSTSIZE_S      8U
#define ADC_BURSTCTL_BURSTSIZE_M      0xF00U    // SOC Burst Size Select
#define ADC_BURSTCTL_BURSTEN          0x8000U   // SOC Burst Mode Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCINTFLG register
//
//*************************************************************************************************
#define ADC_INTFLG_ADCINT1         0x1U    // ADC Interrupt 1 Flag
#define ADC_INTFLG_ADCINT2         0x2U    // ADC Interrupt 2 Flag
#define ADC_INTFLG_ADCINT3         0x4U    // ADC Interrupt 3 Flag
#define ADC_INTFLG_ADCINT4         0x8U    // ADC Interrupt 4 Flag
#define ADC_INTFLG_ADCINT1RESULT   0x10U   // ADC Interrupt 1 Results Ready
#define ADC_INTFLG_ADCINT2RESULT   0x20U   // ADC Interrupt 2 Results Ready
#define ADC_INTFLG_ADCINT3RESULT   0x40U   // ADC Interrupt 3 Results Ready
#define ADC_INTFLG_ADCINT4RESULT   0x80U   // ADC Interrupt 4 Results Ready

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCINTFLGCLR register
//
//*************************************************************************************************
#define ADC_INTFLGCLR_ADCINT1   0x1U   // ADC Interrupt 1 Flag Clear
#define ADC_INTFLGCLR_ADCINT2   0x2U   // ADC Interrupt 2 Flag Clear
#define ADC_INTFLGCLR_ADCINT3   0x4U   // ADC Interrupt 3 Flag Clear
#define ADC_INTFLGCLR_ADCINT4   0x8U   // ADC Interrupt 4 Flag Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCINTOVF register
//
//*************************************************************************************************
#define ADC_INTOVF_ADCINT1   0x1U   // ADC Interrupt 1 Overflow Flags
#define ADC_INTOVF_ADCINT2   0x2U   // ADC Interrupt 2 Overflow Flags
#define ADC_INTOVF_ADCINT3   0x4U   // ADC Interrupt 3 Overflow Flags
#define ADC_INTOVF_ADCINT4   0x8U   // ADC Interrupt 4 Overflow Flags

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCINTOVFCLR register
//
//*************************************************************************************************
#define ADC_INTOVFCLR_ADCINT1   0x1U   // ADC Interrupt 1 Overflow Clear Bits
#define ADC_INTOVFCLR_ADCINT2   0x2U   // ADC Interrupt 2 Overflow Clear Bits
#define ADC_INTOVFCLR_ADCINT3   0x4U   // ADC Interrupt 3 Overflow Clear Bits
#define ADC_INTOVFCLR_ADCINT4   0x8U   // ADC Interrupt 4 Overflow Clear Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCINTSEL1N2 register
//
//*************************************************************************************************
#define ADC_INTSEL1N2_INT1SEL_S   0U
#define ADC_INTSEL1N2_INT1SEL_M   0x3FU     // ADCINT1 EOC Source Select
#define ADC_INTSEL1N2_INT1CONT    0x40U     // ADCINT1 Continue to Interrupt Mode
#define ADC_INTSEL1N2_INT1E       0x80U     // ADCINT1 Interrupt Enable
#define ADC_INTSEL1N2_INT2SEL_S   8U
#define ADC_INTSEL1N2_INT2SEL_M   0x3F00U   // ADCINT2 EOC Source Select
#define ADC_INTSEL1N2_INT2CONT    0x4000U   // ADCINT2 Continue to Interrupt Mode
#define ADC_INTSEL1N2_INT2E       0x8000U   // ADCINT2 Interrupt Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCINTSEL3N4 register
//
//*************************************************************************************************
#define ADC_INTSEL3N4_INT3SEL_S   0U
#define ADC_INTSEL3N4_INT3SEL_M   0x3FU     // ADCINT3 EOC Source Select
#define ADC_INTSEL3N4_INT3CONT    0x40U     // ADCINT3 Continue to Interrupt Mode
#define ADC_INTSEL3N4_INT3E       0x80U     // ADCINT3 Interrupt Enable
#define ADC_INTSEL3N4_INT4SEL_S   8U
#define ADC_INTSEL3N4_INT4SEL_M   0x3F00U   // ADCINT4 EOC Source Select
#define ADC_INTSEL3N4_INT4CONT    0x4000U   // ADCINT4 Continue to Interrupt Mode
#define ADC_INTSEL3N4_INT4E       0x8000U   // ADCINT4 Interrupt Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOCPRICTL register
//
//*************************************************************************************************
#define ADC_SOCPRICTL_SOCPRIORITY_S   0U
#define ADC_SOCPRICTL_SOCPRIORITY_M   0x1FU    // SOC Priority
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
#define ADC_SOCOVF1_SOC0    0x1U      // SOC0 Start of Conversion Overflow Flag
#define ADC_SOCOVF1_SOC1    0x2U      // SOC1 Start of Conversion Overflow Flag
#define ADC_SOCOVF1_SOC2    0x4U      // SOC2 Start of Conversion Overflow Flag
#define ADC_SOCOVF1_SOC3    0x8U      // SOC3 Start of Conversion Overflow Flag
#define ADC_SOCOVF1_SOC4    0x10U     // SOC4 Start of Conversion Overflow Flag
#define ADC_SOCOVF1_SOC5    0x20U     // SOC5 Start of Conversion Overflow Flag
#define ADC_SOCOVF1_SOC6    0x40U     // SOC6 Start of Conversion Overflow Flag
#define ADC_SOCOVF1_SOC7    0x80U     // SOC7 Start of Conversion Overflow Flag
#define ADC_SOCOVF1_SOC8    0x100U    // SOC8 Start of Conversion Overflow Flag
#define ADC_SOCOVF1_SOC9    0x200U    // SOC9 Start of Conversion Overflow Flag
#define ADC_SOCOVF1_SOC10   0x400U    // SOC10 Start of Conversion Overflow Flag
#define ADC_SOCOVF1_SOC11   0x800U    // SOC11 Start of Conversion Overflow Flag
#define ADC_SOCOVF1_SOC12   0x1000U   // SOC12 Start of Conversion Overflow Flag
#define ADC_SOCOVF1_SOC13   0x2000U   // SOC13 Start of Conversion Overflow Flag
#define ADC_SOCOVF1_SOC14   0x4000U   // SOC14 Start of Conversion Overflow Flag
#define ADC_SOCOVF1_SOC15   0x8000U   // SOC15 Start of Conversion Overflow Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOCOVFCLR1 register
//
//*************************************************************************************************
#define ADC_SOCOVFCLR1_SOC0    0x1U      // SOC0 Clear Start of Conversion Overflow Bit
#define ADC_SOCOVFCLR1_SOC1    0x2U      // SOC1 Clear Start of Conversion Overflow Bit
#define ADC_SOCOVFCLR1_SOC2    0x4U      // SOC2 Clear Start of Conversion Overflow Bit
#define ADC_SOCOVFCLR1_SOC3    0x8U      // SOC3 Clear Start of Conversion Overflow Bit
#define ADC_SOCOVFCLR1_SOC4    0x10U     // SOC4 Clear Start of Conversion Overflow Bit
#define ADC_SOCOVFCLR1_SOC5    0x20U     // SOC5 Clear Start of Conversion Overflow Bit
#define ADC_SOCOVFCLR1_SOC6    0x40U     // SOC6 Clear Start of Conversion Overflow Bit
#define ADC_SOCOVFCLR1_SOC7    0x80U     // SOC7 Clear Start of Conversion Overflow Bit
#define ADC_SOCOVFCLR1_SOC8    0x100U    // SOC8 Clear Start of Conversion Overflow Bit
#define ADC_SOCOVFCLR1_SOC9    0x200U    // SOC9 Clear Start of Conversion Overflow Bit
#define ADC_SOCOVFCLR1_SOC10   0x400U    // SOC10 Clear Start of Conversion Overflow Bit
#define ADC_SOCOVFCLR1_SOC11   0x800U    // SOC11 Clear Start of Conversion Overflow Bit
#define ADC_SOCOVFCLR1_SOC12   0x1000U   // SOC12 Clear Start of Conversion Overflow Bit
#define ADC_SOCOVFCLR1_SOC13   0x2000U   // SOC13 Clear Start of Conversion Overflow Bit
#define ADC_SOCOVFCLR1_SOC14   0x4000U   // SOC14 Clear Start of Conversion Overflow Bit
#define ADC_SOCOVFCLR1_SOC15   0x8000U   // SOC15 Clear Start of Conversion Overflow Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC0CTL register
//
//*************************************************************************************************
#define ADC_SOC0CTL_ACQPS_S               0U
#define ADC_SOC0CTL_ACQPS_M               0x1FFU        // SOC0 Acquisition Prescale
#define ADC_SOC0CTL_SAMPCAPRESETDISABLE   0x200UL       // SOC0 Sample Cap Reset Select
#define ADC_SOC0CTL_CHSEL_S               15U
#define ADC_SOC0CTL_CHSEL_M               0xF8000U      // SOC0 Channel Select
#define ADC_SOC0CTL_TRIGSEL_S             20U
#define ADC_SOC0CTL_TRIGSEL_M             0x7F00000U    // SOC0 Trigger Source Select
#define ADC_SOC0CTL_EXTCHSEL_S            28U
#define ADC_SOC0CTL_EXTCHSEL_M            0xF0000000U   // SOC0 External Channel Mux Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC1CTL register
//
//*************************************************************************************************
#define ADC_SOC1CTL_ACQPS_S               0U
#define ADC_SOC1CTL_ACQPS_M               0x1FFU        // SOC1 Acquisition Prescale
#define ADC_SOC1CTL_SAMPCAPRESETDISABLE   0x200U        // SOC1 Sample Cap Reset Select
#define ADC_SOC1CTL_CHSEL_S               15U
#define ADC_SOC1CTL_CHSEL_M               0xF8000U      // SOC1 Channel Select
#define ADC_SOC1CTL_TRIGSEL_S             20U
#define ADC_SOC1CTL_TRIGSEL_M             0x7F00000U    // SOC1 Trigger Source Select
#define ADC_SOC1CTL_EXTCHSEL_S            28U
#define ADC_SOC1CTL_EXTCHSEL_M            0xF0000000U   // SOC1 External Channel Mux Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC2CTL register
//
//*************************************************************************************************
#define ADC_SOC2CTL_ACQPS_S               0U
#define ADC_SOC2CTL_ACQPS_M               0x1FFU        // SOC2 Acquisition Prescale
#define ADC_SOC2CTL_SAMPCAPRESETDISABLE   0x200U        // SOC2 Sample Cap Reset Select
#define ADC_SOC2CTL_CHSEL_S               15U
#define ADC_SOC2CTL_CHSEL_M               0xF8000U      // SOC2 Channel Select
#define ADC_SOC2CTL_TRIGSEL_S             20U
#define ADC_SOC2CTL_TRIGSEL_M             0x7F00000U    // SOC2 Trigger Source Select
#define ADC_SOC2CTL_EXTCHSEL_S            28U
#define ADC_SOC2CTL_EXTCHSEL_M            0xF0000000U   // SOC2 External Channel Mux Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC3CTL register
//
//*************************************************************************************************
#define ADC_SOC3CTL_ACQPS_S               0U
#define ADC_SOC3CTL_ACQPS_M               0x1FFU        // SOC3 Acquisition Prescale
#define ADC_SOC3CTL_SAMPCAPRESETDISABLE   0x200U        // SOC3 Sample Cap Reset Select
#define ADC_SOC3CTL_CHSEL_S               15U
#define ADC_SOC3CTL_CHSEL_M               0xF8000U      // SOC3 Channel Select
#define ADC_SOC3CTL_TRIGSEL_S             20U
#define ADC_SOC3CTL_TRIGSEL_M             0x7F00000U    // SOC3 Trigger Source Select
#define ADC_SOC3CTL_EXTCHSEL_S            28U
#define ADC_SOC3CTL_EXTCHSEL_M            0xF0000000U   // SOC3 External Channel Mux Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC4CTL register
//
//*************************************************************************************************
#define ADC_SOC4CTL_ACQPS_S               0U
#define ADC_SOC4CTL_ACQPS_M               0x1FFU        // SOC4 Acquisition Prescale
#define ADC_SOC4CTL_SAMPCAPRESETDISABLE   0x200U        // SOC4 Sample Cap Reset Select
#define ADC_SOC4CTL_CHSEL_S               15U
#define ADC_SOC4CTL_CHSEL_M               0xF8000U      // SOC4 Channel Select
#define ADC_SOC4CTL_TRIGSEL_S             20U
#define ADC_SOC4CTL_TRIGSEL_M             0x7F00000U    // SOC4 Trigger Source Select
#define ADC_SOC4CTL_EXTCHSEL_S            28U
#define ADC_SOC4CTL_EXTCHSEL_M            0xF0000000U   // SOC4 External Channel Mux Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC5CTL register
//
//*************************************************************************************************
#define ADC_SOC5CTL_ACQPS_S               0U
#define ADC_SOC5CTL_ACQPS_M               0x1FFU        // SOC5 Acquisition Prescale
#define ADC_SOC5CTL_SAMPCAPRESETDISABLE   0x200U        // SOC5 Sample Cap Reset Select
#define ADC_SOC5CTL_CHSEL_S               15U
#define ADC_SOC5CTL_CHSEL_M               0xF8000U      // SOC5 Channel Select
#define ADC_SOC5CTL_TRIGSEL_S             20U
#define ADC_SOC5CTL_TRIGSEL_M             0x7F00000U    // SOC5 Trigger Source Select
#define ADC_SOC5CTL_EXTCHSEL_S            28U
#define ADC_SOC5CTL_EXTCHSEL_M            0xF0000000U   // SOC5 External Channel Mux Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC6CTL register
//
//*************************************************************************************************
#define ADC_SOC6CTL_ACQPS_S               0U
#define ADC_SOC6CTL_ACQPS_M               0x1FFU        // SOC6 Acquisition Prescale
#define ADC_SOC6CTL_SAMPCAPRESETDISABLE   0x200U        // SOC6 Sample Cap Reset Select
#define ADC_SOC6CTL_CHSEL_S               15U
#define ADC_SOC6CTL_CHSEL_M               0xF8000U      // SOC6 Channel Select
#define ADC_SOC6CTL_TRIGSEL_S             20U
#define ADC_SOC6CTL_TRIGSEL_M             0x7F00000U    // SOC6 Trigger Source Select
#define ADC_SOC6CTL_EXTCHSEL_S            28U
#define ADC_SOC6CTL_EXTCHSEL_M            0xF0000000U   // SOC6 External Channel Mux Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC7CTL register
//
//*************************************************************************************************
#define ADC_SOC7CTL_ACQPS_S               0U
#define ADC_SOC7CTL_ACQPS_M               0x1FFU        // SOC7 Acquisition Prescale
#define ADC_SOC7CTL_SAMPCAPRESETDISABLE   0x200U        // SOC7 Sample Cap Reset Select
#define ADC_SOC7CTL_CHSEL_S               15U
#define ADC_SOC7CTL_CHSEL_M               0xF8000U      // SOC7 Channel Select
#define ADC_SOC7CTL_TRIGSEL_S             20U
#define ADC_SOC7CTL_TRIGSEL_M             0x7F00000U    // SOC7 Trigger Source Select
#define ADC_SOC7CTL_EXTCHSEL_S            28U
#define ADC_SOC7CTL_EXTCHSEL_M            0xF0000000U   // SOC7 External Channel Mux Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC8CTL register
//
//*************************************************************************************************
#define ADC_SOC8CTL_ACQPS_S               0U
#define ADC_SOC8CTL_ACQPS_M               0x1FFU        // SOC8 Acquisition Prescale
#define ADC_SOC8CTL_SAMPCAPRESETDISABLE   0x200U        // SOC8 Sample Cap Reset Select
#define ADC_SOC8CTL_CHSEL_S               15U
#define ADC_SOC8CTL_CHSEL_M               0xF8000U      // SOC8 Channel Select
#define ADC_SOC8CTL_TRIGSEL_S             20U
#define ADC_SOC8CTL_TRIGSEL_M             0x7F00000U    // SOC8 Trigger Source Select
#define ADC_SOC8CTL_EXTCHSEL_S            28U
#define ADC_SOC8CTL_EXTCHSEL_M            0xF0000000U   // SOC8 External Channel Mux Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC9CTL register
//
//*************************************************************************************************
#define ADC_SOC9CTL_ACQPS_S               0U
#define ADC_SOC9CTL_ACQPS_M               0x1FFU        // SOC9 Acquisition Prescale
#define ADC_SOC9CTL_SAMPCAPRESETDISABLE   0x200U        // SOC9 Sample Cap Reset Select
#define ADC_SOC9CTL_CHSEL_S               15U
#define ADC_SOC9CTL_CHSEL_M               0xF8000U      // SOC9 Channel Select
#define ADC_SOC9CTL_TRIGSEL_S             20U
#define ADC_SOC9CTL_TRIGSEL_M             0x7F00000U    // SOC9 Trigger Source Select
#define ADC_SOC9CTL_EXTCHSEL_S            28U
#define ADC_SOC9CTL_EXTCHSEL_M            0xF0000000U   // SOC9 External Channel Mux Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC10CTL register
//
//*************************************************************************************************
#define ADC_SOC10CTL_ACQPS_S               0U
#define ADC_SOC10CTL_ACQPS_M               0x1FFU        // SOC10 Acquisition Prescale
#define ADC_SOC10CTL_SAMPCAPRESETDISABLE   0x200U        // SOC10 Sample Cap Reset Select
#define ADC_SOC10CTL_CHSEL_S               15U
#define ADC_SOC10CTL_CHSEL_M               0xF8000U      // SOC10 Channel Select
#define ADC_SOC10CTL_TRIGSEL_S             20U
#define ADC_SOC10CTL_TRIGSEL_M             0x7F00000U    // SOC10 Trigger Source Select
#define ADC_SOC10CTL_EXTCHSEL_S            28U
#define ADC_SOC10CTL_EXTCHSEL_M            0xF0000000U   // SOC10 External Channel Mux Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC11CTL register
//
//*************************************************************************************************
#define ADC_SOC11CTL_ACQPS_S               0U
#define ADC_SOC11CTL_ACQPS_M               0x1FFU        // SOC11 Acquisition Prescale
#define ADC_SOC11CTL_SAMPCAPRESETDISABLE   0x200U        // SOC11 Sample Cap Reset Select
#define ADC_SOC11CTL_CHSEL_S               15U
#define ADC_SOC11CTL_CHSEL_M               0xF8000U      // SOC11 Channel Select
#define ADC_SOC11CTL_TRIGSEL_S             20U
#define ADC_SOC11CTL_TRIGSEL_M             0x7F00000U    // SOC11 Trigger Source Select
#define ADC_SOC11CTL_EXTCHSEL_S            28U
#define ADC_SOC11CTL_EXTCHSEL_M            0xF0000000U   // SOC11 External Channel Mux Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC12CTL register
//
//*************************************************************************************************
#define ADC_SOC12CTL_ACQPS_S               0U
#define ADC_SOC12CTL_ACQPS_M               0x1FFU        // SOC12 Acquisition Prescale
#define ADC_SOC12CTL_SAMPCAPRESETDISABLE   0x200U        // SOC12 Sample Cap Reset Select
#define ADC_SOC12CTL_CHSEL_S               15U
#define ADC_SOC12CTL_CHSEL_M               0xF8000U      // SOC12 Channel Select
#define ADC_SOC12CTL_TRIGSEL_S             20U
#define ADC_SOC12CTL_TRIGSEL_M             0x7F00000U    // SOC12 Trigger Source Select
#define ADC_SOC12CTL_EXTCHSEL_S            28U
#define ADC_SOC12CTL_EXTCHSEL_M            0xF0000000U   // SOC12 External Channel Mux Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC13CTL register
//
//*************************************************************************************************
#define ADC_SOC13CTL_ACQPS_S               0U
#define ADC_SOC13CTL_ACQPS_M               0x1FFU        // SOC13 Acquisition Prescale
#define ADC_SOC13CTL_SAMPCAPRESETDISABLE   0x200U        // SOC13 Sample Cap Reset Select
#define ADC_SOC13CTL_CHSEL_S               15U
#define ADC_SOC13CTL_CHSEL_M               0xF8000U      // SOC13 Channel Select
#define ADC_SOC13CTL_TRIGSEL_S             20U
#define ADC_SOC13CTL_TRIGSEL_M             0x7F00000U    // SOC13 Trigger Source Select
#define ADC_SOC13CTL_EXTCHSEL_S            28U
#define ADC_SOC13CTL_EXTCHSEL_M            0xF0000000U   // SOC13 External Channel Mux Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC14CTL register
//
//*************************************************************************************************
#define ADC_SOC14CTL_ACQPS_S               0U
#define ADC_SOC14CTL_ACQPS_M               0x1FFU        // SOC14 Acquisition Prescale
#define ADC_SOC14CTL_SAMPCAPRESETDISABLE   0x200U        // SOC14 Sample Cap Reset Select
#define ADC_SOC14CTL_CHSEL_S               15U
#define ADC_SOC14CTL_CHSEL_M               0xF8000U      // SOC14 Channel Select
#define ADC_SOC14CTL_TRIGSEL_S             20U
#define ADC_SOC14CTL_TRIGSEL_M             0x7F00000U    // SOC14 Trigger Source Select
#define ADC_SOC14CTL_EXTCHSEL_S            28U
#define ADC_SOC14CTL_EXTCHSEL_M            0xF0000000U   // SOC14 External Channel Mux Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC15CTL register
//
//*************************************************************************************************
#define ADC_SOC15CTL_ACQPS_S               0U
#define ADC_SOC15CTL_ACQPS_M               0x1FFU        // SOC15 Acquisition Prescale
#define ADC_SOC15CTL_SAMPCAPRESETDISABLE   0x200U        // SOC15 Sample Cap Reset Select
#define ADC_SOC15CTL_CHSEL_S               15U
#define ADC_SOC15CTL_CHSEL_M               0xF8000U      // SOC15 Channel Select
#define ADC_SOC15CTL_TRIGSEL_S             20U
#define ADC_SOC15CTL_TRIGSEL_M             0x7F00000U    // SOC15 Trigger Source Select
#define ADC_SOC15CTL_EXTCHSEL_S            28U
#define ADC_SOC15CTL_EXTCHSEL_M            0xF0000000U   // SOC15 External Channel Mux Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCEVTSTAT register
//
//*************************************************************************************************
#define ADC_EVTSTAT_PPB1TRIPHI   0x1U      // Post Processing Block 1 Trip High Flag
#define ADC_EVTSTAT_PPB1TRIPLO   0x2U      // Post Processing Block 1 Trip Low Flag
#define ADC_EVTSTAT_PPB1ZERO     0x4U      // Post Processing Block 1 Zero Crossing Flag
#define ADC_EVTSTAT_PPB2TRIPHI   0x10U     // Post Processing Block 2 Trip High Flag
#define ADC_EVTSTAT_PPB2TRIPLO   0x20U     // Post Processing Block 2 Trip Low Flag
#define ADC_EVTSTAT_PPB2ZERO     0x40U     // Post Processing Block 2 Zero Crossing Flag
#define ADC_EVTSTAT_PPB3TRIPHI   0x100U    // Post Processing Block 3 Trip High Flag
#define ADC_EVTSTAT_PPB3TRIPLO   0x200U    // Post Processing Block 3 Trip Low Flag
#define ADC_EVTSTAT_PPB3ZERO     0x400U    // Post Processing Block 3 Zero Crossing Flag
#define ADC_EVTSTAT_PPB4TRIPHI   0x1000U   // Post Processing Block 4 Trip High Flag
#define ADC_EVTSTAT_PPB4TRIPLO   0x2000U   // Post Processing Block 4 Trip Low Flag
#define ADC_EVTSTAT_PPB4ZERO     0x4000U   // Post Processing Block 4 Zero Crossing Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCEVTCLR register
//
//*************************************************************************************************
#define ADC_EVTCLR_PPB1TRIPHI   0x1U      // Post Processing Block 1 Trip High Clear
#define ADC_EVTCLR_PPB1TRIPLO   0x2U      // Post Processing Block 1 Trip Low Clear
#define ADC_EVTCLR_PPB1ZERO     0x4U      // Post Processing Block 1 Zero Crossing Clear
#define ADC_EVTCLR_PPB2TRIPHI   0x10U     // Post Processing Block 2 Trip High Clear
#define ADC_EVTCLR_PPB2TRIPLO   0x20U     // Post Processing Block 2 Trip Low Clear
#define ADC_EVTCLR_PPB2ZERO     0x40U     // Post Processing Block 2 Zero Crossing Clear
#define ADC_EVTCLR_PPB3TRIPHI   0x100U    // Post Processing Block 3 Trip High Clear
#define ADC_EVTCLR_PPB3TRIPLO   0x200U    // Post Processing Block 3 Trip Low Clear
#define ADC_EVTCLR_PPB3ZERO     0x400U    // Post Processing Block 3 Zero Crossing Clear
#define ADC_EVTCLR_PPB4TRIPHI   0x1000U   // Post Processing Block 4 Trip High Clear
#define ADC_EVTCLR_PPB4TRIPLO   0x2000U   // Post Processing Block 4 Trip Low Clear
#define ADC_EVTCLR_PPB4ZERO     0x4000U   // Post Processing Block 4 Zero Crossing Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCEVTSEL register
//
//*************************************************************************************************
#define ADC_EVTSEL_PPB1TRIPHI   0x1U      // Post Processing Block 1 Trip High Event Enable
#define ADC_EVTSEL_PPB1TRIPLO   0x2U      // Post Processing Block 1 Trip Low Event Enable
#define ADC_EVTSEL_PPB1ZERO     0x4U      // Post Processing Block 1 Zero Crossing Event Enable
#define ADC_EVTSEL_PPB2TRIPHI   0x10U     // Post Processing Block 2 Trip High Event Enable
#define ADC_EVTSEL_PPB2TRIPLO   0x20U     // Post Processing Block 2 Trip Low Event Enable
#define ADC_EVTSEL_PPB2ZERO     0x40U     // Post Processing Block 2 Zero Crossing Event Enable
#define ADC_EVTSEL_PPB3TRIPHI   0x100U    // Post Processing Block 3 Trip High Event Enable
#define ADC_EVTSEL_PPB3TRIPLO   0x200U    // Post Processing Block 3 Trip Low Event Enable
#define ADC_EVTSEL_PPB3ZERO     0x400U    // Post Processing Block 3 Zero Crossing Event Enable
#define ADC_EVTSEL_PPB4TRIPHI   0x1000U   // Post Processing Block 4 Trip High Event Enable
#define ADC_EVTSEL_PPB4TRIPLO   0x2000U   // Post Processing Block 4 Trip Low Event Enable
#define ADC_EVTSEL_PPB4ZERO     0x4000U   // Post Processing Block 4 Zero Crossing Event Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCEVTINTSEL register
//
//*************************************************************************************************
#define ADC_EVTINTSEL_PPB1TRIPHI   0x1U      // Post Processing Block 1 Trip High Interrupt Enable
#define ADC_EVTINTSEL_PPB1TRIPLO   0x2U      // Post Processing Block 1 Trip Low Interrupt Enable
#define ADC_EVTINTSEL_PPB1ZERO     0x4U      // Post Processing Block 1 Zero Crossing Interrupt
                                             // Enable
#define ADC_EVTINTSEL_PPB2TRIPHI   0x10U     // Post Processing Block 2 Trip High Interrupt Enable
#define ADC_EVTINTSEL_PPB2TRIPLO   0x20U     // Post Processing Block 2 Trip Low Interrupt Enable
#define ADC_EVTINTSEL_PPB2ZERO     0x40U     // Post Processing Block 2 Zero Crossing Interrupt
                                             // Enable
#define ADC_EVTINTSEL_PPB3TRIPHI   0x100U    // Post Processing Block 3 Trip High Interrupt Enable
#define ADC_EVTINTSEL_PPB3TRIPLO   0x200U    // Post Processing Block 3 Trip Low Interrupt Enable
#define ADC_EVTINTSEL_PPB3ZERO     0x400U    // Post Processing Block 3 Zero Crossing Interrupt
                                             // Enable
#define ADC_EVTINTSEL_PPB4TRIPHI   0x1000U   // Post Processing Block 4 Trip High Interrupt Enable
#define ADC_EVTINTSEL_PPB4TRIPLO   0x2000U   // Post Processing Block 4 Trip Low Interrupt Enable
#define ADC_EVTINTSEL_PPB4ZERO     0x4000U   // Post Processing Block 4 Zero Crossing Interrupt
                                             // Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCCOUNTER register
//
//*************************************************************************************************
#define ADC_COUNTER_FREECOUNT_S   0U
#define ADC_COUNTER_FREECOUNT_M   0xFFFU   // ADC Free Running Counter Value

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCREV register
//
//*************************************************************************************************
#define ADC_REV_TYPE_S   0U
#define ADC_REV_TYPE_M   0xFFU     // ADC Type
#define ADC_REV_REV_S    8U
#define ADC_REV_REV_M    0xFF00U   // ADC Revision

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCOFFTRIM register
//
//*************************************************************************************************
#define ADC_OFFTRIM_OFFTRIM_S   0U
#define ADC_OFFTRIM_OFFTRIM_M   0xFFFU   // ADC Offset Trim

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCCONFIG2 register
//
//*************************************************************************************************
#define ADC_CONFIG2_TESTANA1_CONFIG_S   0U
#define ADC_CONFIG2_TESTANA1_CONFIG_M   0x3U   // TESTANA1 ADC Configuration

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB1CONFIG register
//
//*************************************************************************************************
#define ADC_PPB1CONFIG_CONFIG_S     0U
#define ADC_PPB1CONFIG_CONFIG_M     0xFU     // ADC Post Processing Block 1 Configuration
#define ADC_PPB1CONFIG_CBCEN        0x20U    // Cycle By Cycle Enable
#define ADC_PPB1CONFIG_ABSEN        0x40U    // ADC Post Processing Block 1 Absolute Enable
#define ADC_PPB1CONFIG_TWOSCOMPEN   0x80U    // ADC Post Processing Block 1 Two's Complement Enable
#define ADC_PPB1CONFIG_DELTAEN      0x100U   // ADC Post Processing Block 1 Last Sample Delta
                                             // Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB1STAMP register
//
//*************************************************************************************************
#define ADC_PPB1STAMP_DLYSTAMP_S   0U
#define ADC_PPB1STAMP_DLYSTAMP_M   0xFFFU   // ADC Post Processing Block 1 Delay Time Stamp

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB1OFFCAL register
//
//*************************************************************************************************
#define ADC_PPB1OFFCAL_OFFCAL_S   0U
#define ADC_PPB1OFFCAL_OFFCAL_M   0x3FFU   // ADC Post Processing Block Offset Correction

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB1TRIPHI register
//
//*************************************************************************************************
#define ADC_PPB1TRIPHI_LIMITHI_S   0U
#define ADC_PPB1TRIPHI_LIMITHI_M   0xFFFFFFU   // ADC Post Processing Block 1 Trip High Limit

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB1TRIPLO register
//
//*************************************************************************************************
#define ADC_PPB1TRIPLO_LIMITLO_S    0U
#define ADC_PPB1TRIPLO_LIMITLO_M    0xFFFFU       // ADC Post Processing Block 1 Trip Low Limit
#define ADC_PPB1TRIPLO_LSIGN        0x10000U      // Low Limit Sign Bit
#define ADC_PPB1TRIPLO_LIMITLO2EN   0x80000U      // Extended Low Limit 2 Enable
#define ADC_PPB1TRIPLO_REQSTAMP_S   20U
#define ADC_PPB1TRIPLO_REQSTAMP_M   0xFFF00000U   // ADC Post Processing Block 1 Request Time Stamp

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPBTRIP1FILCTL register
//
//*************************************************************************************************
#define ADC_PPBTRIP1FILCTL_FILTHIEN    0x1U      // ADCPPB1 TRIPHI Filter Enable
#define ADC_PPBTRIP1FILCTL_FILTLOEN    0x2U      // ADCPPB1 TRIPLO Filter Enable
#define ADC_PPBTRIP1FILCTL_SAMPWIN_S   3U
#define ADC_PPBTRIP1FILCTL_SAMPWIN_M   0x1F8U    // Sample Window
#define ADC_PPBTRIP1FILCTL_THRESH_S    9U
#define ADC_PPBTRIP1FILCTL_THRESH_M    0x7E00U   // Majority Voting Threshold
#define ADC_PPBTRIP1FILCTL_FILINIT     0x8000U   // Filter Initialization Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPBTRIP1FILCLKCTL register
//
//*************************************************************************************************
#define ADC_PPBTRIP1FILCLKCTL_CLKPRESCALE_S   0U
#define ADC_PPBTRIP1FILCLKCTL_CLKPRESCALE_M   0xFFFFU   // Filter Clock Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB2CONFIG register
//
//*************************************************************************************************
#define ADC_PPB2CONFIG_CONFIG_S     0U
#define ADC_PPB2CONFIG_CONFIG_M     0xFU     // ADC Post Processing Block 2 Configuration
#define ADC_PPB2CONFIG_CBCEN        0x20U    // Cycle By Cycle Enable
#define ADC_PPB2CONFIG_ABSEN        0x40U    // ADC Post Processing Block 2 Absolute Enable
#define ADC_PPB2CONFIG_TWOSCOMPEN   0x80U    // ADC Post Processing Block 2 Two's Complement Enable
#define ADC_PPB2CONFIG_DELTAEN      0x100U   // ADC Post Processing Block 2 Last Sample Delta
                                             // Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB2STAMP register
//
//*************************************************************************************************
#define ADC_PPB2STAMP_DLYSTAMP_S   0U
#define ADC_PPB2STAMP_DLYSTAMP_M   0xFFFU   // ADC Post Processing Block 2 Delay Time Stamp

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB2OFFCAL register
//
//*************************************************************************************************
#define ADC_PPB2OFFCAL_OFFCAL_S   0U
#define ADC_PPB2OFFCAL_OFFCAL_M   0x3FFU   // ADC Post Processing Block Offset Correction

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB2TRIPHI register
//
//*************************************************************************************************
#define ADC_PPB2TRIPHI_LIMITHI_S   0U
#define ADC_PPB2TRIPHI_LIMITHI_M   0xFFFFFFU   // ADC Post Processing Block 2 Trip High Limit

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB2TRIPLO register
//
//*************************************************************************************************
#define ADC_PPB2TRIPLO_LIMITLO_S    0U
#define ADC_PPB2TRIPLO_LIMITLO_M    0xFFFFU       // ADC Post Processing Block 2 Trip Low Limit
#define ADC_PPB2TRIPLO_LSIGN        0x10000U      // Low Limit Sign Bit
#define ADC_PPB2TRIPLO_LIMITLO2EN   0x80000U      // Extended Low Limit 2 Enable
#define ADC_PPB2TRIPLO_REQSTAMP_S   20U
#define ADC_PPB2TRIPLO_REQSTAMP_M   0xFFF00000U   // ADC Post Processing Block 2 Request Time Stamp

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPBTRIP2FILCTL register
//
//*************************************************************************************************
#define ADC_PPBTRIP2FILCTL_FILTHIEN    0x1U      // ADCPPB2 TRIPHI Filter Enable
#define ADC_PPBTRIP2FILCTL_FILTLOEN    0x2U      // ADCPPB2 TRIPLO Filter Enable
#define ADC_PPBTRIP2FILCTL_SAMPWIN_S   3U
#define ADC_PPBTRIP2FILCTL_SAMPWIN_M   0x1F8U    // Sample Window
#define ADC_PPBTRIP2FILCTL_THRESH_S    9U
#define ADC_PPBTRIP2FILCTL_THRESH_M    0x7E00U   // Majority Voting Threshold
#define ADC_PPBTRIP2FILCTL_FILINIT     0x8000U   // Filter Initialization Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPBTRIP2FILCLKCTL register
//
//*************************************************************************************************
#define ADC_PPBTRIP2FILCLKCTL_CLKPRESCALE_S   0U
#define ADC_PPBTRIP2FILCLKCTL_CLKPRESCALE_M   0xFFFFU   // Filter Clock Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB3CONFIG register
//
//*************************************************************************************************
#define ADC_PPB3CONFIG_CONFIG_S     0U
#define ADC_PPB3CONFIG_CONFIG_M     0xFU     // ADC Post Processing Block 3 Configuration
#define ADC_PPB3CONFIG_CBCEN        0x20U    // Cycle By Cycle Enable
#define ADC_PPB3CONFIG_ABSEN        0x40U    // ADC Post Processing Block 3 Absolute Enable
#define ADC_PPB3CONFIG_TWOSCOMPEN   0x80U    // ADC Post Processing Block 3 Two's Complement Enable
#define ADC_PPB3CONFIG_DELTAEN      0x100U   // ADC Post Processing Block 3 Last Sample Delta
                                             // Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB3STAMP register
//
//*************************************************************************************************
#define ADC_PPB3STAMP_DLYSTAMP_S   0U
#define ADC_PPB3STAMP_DLYSTAMP_M   0xFFFU   // ADC Post Processing Block 3 Delay Time Stamp

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB3OFFCAL register
//
//*************************************************************************************************
#define ADC_PPB3OFFCAL_OFFCAL_S   0U
#define ADC_PPB3OFFCAL_OFFCAL_M   0x3FFU   // ADC Post Processing Block Offset Correction

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB3TRIPHI register
//
//*************************************************************************************************
#define ADC_PPB3TRIPHI_LIMITHI_S   0U
#define ADC_PPB3TRIPHI_LIMITHI_M   0xFFFFFFU   // ADC Post Processing Block 3 Trip High Limit

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB3TRIPLO register
//
//*************************************************************************************************
#define ADC_PPB3TRIPLO_LIMITLO_S    0U
#define ADC_PPB3TRIPLO_LIMITLO_M    0xFFFFU       // ADC Post Processing Block 3 Trip Low Limit
#define ADC_PPB3TRIPLO_LSIGN        0x10000U      // Low Limit Sign Bit
#define ADC_PPB3TRIPLO_LIMITLO2EN   0x80000U      // Extended Low Limit 2 Enable
#define ADC_PPB3TRIPLO_REQSTAMP_S   20U
#define ADC_PPB3TRIPLO_REQSTAMP_M   0xFFF00000U   // ADC Post Processing Block 3 Request Time Stamp

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPBTRIP3FILCTL register
//
//*************************************************************************************************
#define ADC_PPBTRIP3FILCTL_FILTHIEN    0x1U      // ADCPPB3 TRIPHI Filter Enable
#define ADC_PPBTRIP3FILCTL_FILTLOEN    0x2U      // ADCPPB3 TRIPLO Filter Enable
#define ADC_PPBTRIP3FILCTL_SAMPWIN_S   3U
#define ADC_PPBTRIP3FILCTL_SAMPWIN_M   0x1F8U    // Sample Window
#define ADC_PPBTRIP3FILCTL_THRESH_S    9U
#define ADC_PPBTRIP3FILCTL_THRESH_M    0x7E00U   // Majority Voting Threshold
#define ADC_PPBTRIP3FILCTL_FILINIT     0x8000U   // Filter Initialization Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPBTRIP3FILCLKCTL register
//
//*************************************************************************************************
#define ADC_PPBTRIP3FILCLKCTL_CLKPRESCALE_S   0U
#define ADC_PPBTRIP3FILCLKCTL_CLKPRESCALE_M   0xFFFFU   // Filter Clock Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB4CONFIG register
//
//*************************************************************************************************
#define ADC_PPB4CONFIG_CONFIG_S     0U
#define ADC_PPB4CONFIG_CONFIG_M     0xFU     // ADC Post Processing Block 4 Configuration
#define ADC_PPB4CONFIG_CBCEN        0x20U    // Cycle By Cycle Enable
#define ADC_PPB4CONFIG_ABSEN        0x40U    // ADC Post Processing Block 4 Absolute Enable
#define ADC_PPB4CONFIG_TWOSCOMPEN   0x80U    // ADC Post Processing Block 4 Two's Complement Enable
#define ADC_PPB4CONFIG_DELTAEN      0x100U   // ADC Post Processing Block 4 Last Sample Delta
                                             // Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB4STAMP register
//
//*************************************************************************************************
#define ADC_PPB4STAMP_DLYSTAMP_S   0U
#define ADC_PPB4STAMP_DLYSTAMP_M   0xFFFU   // ADC Post Processing Block 4 Delay Time Stamp

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB4OFFCAL register
//
//*************************************************************************************************
#define ADC_PPB4OFFCAL_OFFCAL_S   0U
#define ADC_PPB4OFFCAL_OFFCAL_M   0x3FFU   // ADC Post Processing Block Offset Correction

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB4TRIPHI register
//
//*************************************************************************************************
#define ADC_PPB4TRIPHI_LIMITHI_S   0U
#define ADC_PPB4TRIPHI_LIMITHI_M   0xFFFFFFU   // ADC Post Processing Block 4 Trip High Limit

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB4TRIPLO register
//
//*************************************************************************************************
#define ADC_PPB4TRIPLO_LIMITLO_S    0U
#define ADC_PPB4TRIPLO_LIMITLO_M    0xFFFFU       // ADC Post Processing Block 4 Trip Low Limit
#define ADC_PPB4TRIPLO_LSIGN        0x10000U      // Low Limit Sign Bit
#define ADC_PPB4TRIPLO_LIMITLO2EN   0x80000U      // Extended Low Limit 2 Enable
#define ADC_PPB4TRIPLO_REQSTAMP_S   20U
#define ADC_PPB4TRIPLO_REQSTAMP_M   0xFFF00000U   // ADC Post Processing Block 4 Request Time Stamp

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPBTRIP4FILCTL register
//
//*************************************************************************************************
#define ADC_PPBTRIP4FILCTL_FILTHIEN    0x1U      // ADCPPB4 TRIPHI Filter Enable
#define ADC_PPBTRIP4FILCTL_FILTLOEN    0x2U      // ADCPPB4 TRIPLO Filter Enable
#define ADC_PPBTRIP4FILCTL_SAMPWIN_S   3U
#define ADC_PPBTRIP4FILCTL_SAMPWIN_M   0x1F8U    // Sample Window
#define ADC_PPBTRIP4FILCTL_THRESH_S    9U
#define ADC_PPBTRIP4FILCTL_THRESH_M    0x7E00U   // Majority Voting Threshold
#define ADC_PPBTRIP4FILCTL_FILINIT     0x8000U   // Filter Initialization Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPBTRIP4FILCLKCTL register
//
//*************************************************************************************************
#define ADC_PPBTRIP4FILCLKCTL_CLKPRESCALE_S   0U
#define ADC_PPBTRIP4FILCLKCTL_CLKPRESCALE_M   0xFFFFU   // Filter Clock Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCREV2 register
//
//*************************************************************************************************
#define ADC_REV2_WRAPPERTYPE_S   0U
#define ADC_REV2_WRAPPERTYPE_M   0xFFU     // ADC Wrapper Type
#define ADC_REV2_WRAPPERREV_S    8U
#define ADC_REV2_WRAPPERREV_M    0xFF00U   // ADC Wrapper Revision

//*************************************************************************************************
//
// The following are defines for the bit fields in the REP1CTL register
//
//*************************************************************************************************
#define ADC_REP1CTL_MODE          0x1U        // ADC Trigger Repeater 1 Mode Select
#define ADC_REP1CTL_ACTIVEMODE    0x2U        // ADC Trigger Repeater 1 Active Mode
#define ADC_REP1CTL_MODULEBUSY    0x8U        // ADC Trigger Repeater 1 Module Busy
#define ADC_REP1CTL_PHASEOVF      0x40U       // ADC Trigger Repeater 1 Phase Delay Overflow
#define ADC_REP1CTL_TRIGGEROVF    0x80U       // ADC Trigger Repeater 1 Oversampled Trigger
                                              // Overflow
#define ADC_REP1CTL_TRIGGER_S     8U
#define ADC_REP1CTL_TRIGGER_M     0x7F00U     // ADC Trigger Repeater 1 Trigger Select
#define ADC_REP1CTL_SYNCINSEL_S   16U
#define ADC_REP1CTL_SYNCINSEL_M   0x3F0000U   // ADC Trigger Repeater 1 Sync. In Select
#define ADC_REP1CTL_SWSYNC        0x800000U   // ADC Trigger Repeater 1 Software Sync.

//*************************************************************************************************
//
// The following are defines for the bit fields in the REP1N register
//
//*************************************************************************************************
#define ADC_REP1N_NSEL_S     0U
#define ADC_REP1N_NSEL_M     0x7FU       // ADC Trigger Repeater 1 Trigger Number Selection
#define ADC_REP1N_NCOUNT_S   16U
#define ADC_REP1N_NCOUNT_M   0x7F0000U   // ADC Trigger Repeater 1 Trigger Counter

//*************************************************************************************************
//
// The following are defines for the bit fields in the REP1PHASE register
//
//*************************************************************************************************
#define ADC_REP1PHASE_PHASE_S        0U
#define ADC_REP1PHASE_PHASE_M        0xFFFFU       // ADC Trigger Repeater 1 Phase Delay
                                                   // Configuration
#define ADC_REP1PHASE_PHASECOUNT_S   16U
#define ADC_REP1PHASE_PHASECOUNT_M   0xFFFF0000U   // ADC Trigger Repeater 1 Phase Delay Status

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
// The following are defines for the bit fields in the REP2CTL register
//
//*************************************************************************************************
#define ADC_REP2CTL_MODE          0x1U        // ADC Trigger Repeater 2 Mode Select
#define ADC_REP2CTL_ACTIVEMODE    0x2U        // ADC Trigger Repeater 2 Active Mode
#define ADC_REP2CTL_MODULEBUSY    0x8U        // ADC Trigger Repeater 2 Module Busy
#define ADC_REP2CTL_PHASEOVF      0x40U       // ADC Trigger Repeater 2 Phase Delay Overflow
#define ADC_REP2CTL_TRIGGEROVF    0x80U       // ADC Trigger Repeater 2 Oversampled Trigger
                                              // Overflow
#define ADC_REP2CTL_TRIGGER_S     8U
#define ADC_REP2CTL_TRIGGER_M     0x7F00U     // ADC Trigger Repeater 2 Trigger Select
#define ADC_REP2CTL_SYNCINSEL_S   16U
#define ADC_REP2CTL_SYNCINSEL_M   0x3F0000U   // ADC Trigger Repeater 2 Sync. In Select
#define ADC_REP2CTL_SWSYNC        0x800000U   // ADC Trigger Repeater 2 Software Sync.

//*************************************************************************************************
//
// The following are defines for the bit fields in the REP2N register
//
//*************************************************************************************************
#define ADC_REP2N_NSEL_S     0U
#define ADC_REP2N_NSEL_M     0x7FU       // ADC Trigger Repeater 2 Trigger Number Selection
#define ADC_REP2N_NCOUNT_S   16U
#define ADC_REP2N_NCOUNT_M   0x7F0000U   // ADC Trigger Repeater 2 Trigger Counter

//*************************************************************************************************
//
// The following are defines for the bit fields in the REP2PHASE register
//
//*************************************************************************************************
#define ADC_REP2PHASE_PHASE_S        0U
#define ADC_REP2PHASE_PHASE_M        0xFFFFU       // ADC Trigger Repeater 2 Phase Delay
                                                   // Configuration
#define ADC_REP2PHASE_PHASECOUNT_S   16U
#define ADC_REP2PHASE_PHASECOUNT_M   0xFFFF0000U   // ADC Trigger Repeater 2 Phase Delay Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the REP2SPREAD register
//
//*************************************************************************************************
#define ADC_REP2SPREAD_SPREAD_S        0U
#define ADC_REP2SPREAD_SPREAD_M        0xFFFFU       // ADC Trigger Repeater 2 Spread Delay
                                                     // Configuration
#define ADC_REP2SPREAD_SPREADCOUNT_S   16U
#define ADC_REP2SPREAD_SPREADCOUNT_M   0xFFFF0000U   // ADC Trigger Repeater 2 Spread Delay Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the REP2FRC register
//
//*************************************************************************************************
#define ADC_REP2FRC_SWFRC   0x1U   // ADC Trigger Repeater 2 Software Force

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB1LIMIT register
//
//*************************************************************************************************
#define ADC_PPB1LIMIT_LIMIT_S   0U
#define ADC_PPB1LIMIT_LIMIT_M   0x3FFU   // Post Processing Block 1 Limit

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPBP1PCOUNT register
//
//*************************************************************************************************
#define ADC_PPBP1PCOUNT_PCOUNT_S   0U
#define ADC_PPBP1PCOUNT_PCOUNT_M   0x3FFU   // Post Processing Block 1 Partial Count

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB1CONFIG2 register
//
//*************************************************************************************************
#define ADC_PPB1CONFIG2_SHIFT_S       0U
#define ADC_PPB1CONFIG2_SHIFT_M       0xFU      // Post Processing Block 1 Right Shift
#define ADC_PPB1CONFIG2_SYNCINSEL_S   4U
#define ADC_PPB1CONFIG2_SYNCINSEL_M   0x3F0U    // Post Processing Block 1 Sync. Input Select
#define ADC_PPB1CONFIG2_SWSYNC        0x800U    // Post Processing Block 1 Software Force Sync.
#define ADC_PPB1CONFIG2_OSINTSEL      0x1000U   // Post Processing Block 1 Interrupt Source Select
#define ADC_PPB1CONFIG2_COMPSEL_S     14U
#define ADC_PPB1CONFIG2_COMPSEL_M     0xC000U   // Post Processing Block 1 Compare Source Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB1PSUM register
//
//*************************************************************************************************
#define ADC_PPB1PSUM_PSUM_S   0U
#define ADC_PPB1PSUM_PSUM_M   0xFFFFFFU     // Post Processing Block 1 Oversampling Partial Sum
#define ADC_PPB1PSUM_SIGN_S   24U
#define ADC_PPB1PSUM_SIGN_M   0xFF000000U   // Sign Extended Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB1PMAX register
//
//*************************************************************************************************
#define ADC_PPB1PMAX_PMAX_S   0U
#define ADC_PPB1PMAX_PMAX_M   0x1FFFFU      // Post Processing Block 1 Oversampling Partial Max
#define ADC_PPB1PMAX_SIGN_S   17U
#define ADC_PPB1PMAX_SIGN_M   0xFFFE0000U   // Sign Extended Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB1PMAXI register
//
//*************************************************************************************************
#define ADC_PPB1PMAXI_PMAXI_S   0U
#define ADC_PPB1PMAXI_PMAXI_M   0x3FFU   // Post Processing Block 1 Oversampling Partial Index of
                                         // Max

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB1PMIN register
//
//*************************************************************************************************
#define ADC_PPB1PMIN_PMIN_S   0U
#define ADC_PPB1PMIN_PMIN_M   0x1FFFFU      // Post Processing Block 1 Oversampling Partial Min
#define ADC_PPB1PMIN_SIGN_S   17U
#define ADC_PPB1PMIN_SIGN_M   0xFFFE0000U   // Sign Extended Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB1PMINI register
//
//*************************************************************************************************
#define ADC_PPB1PMINI_PMINI_S   0U
#define ADC_PPB1PMINI_PMINI_M   0x3FFU   // Post Processing Block 1 Oversampling Partial Index of
                                         // Min

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB1TRIPLO2 register
//
//*************************************************************************************************
#define ADC_PPB1TRIPLO2_LIMITLO_S   0U
#define ADC_PPB1TRIPLO2_LIMITLO_M   0xFFFFFFU   // ADC Post Processing Block 1 Trip Low Limit

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB2LIMIT register
//
//*************************************************************************************************
#define ADC_PPB2LIMIT_LIMIT_S   0U
#define ADC_PPB2LIMIT_LIMIT_M   0x3FFU   // Post Processing Block 2 Limit

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPBP2PCOUNT register
//
//*************************************************************************************************
#define ADC_PPBP2PCOUNT_PCOUNT_S   0U
#define ADC_PPBP2PCOUNT_PCOUNT_M   0x3FFU   // Post Processing Block 2 Partial Count

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB2CONFIG2 register
//
//*************************************************************************************************
#define ADC_PPB2CONFIG2_SHIFT_S       0U
#define ADC_PPB2CONFIG2_SHIFT_M       0xFU      // Post Processing Block 2 Right Shift
#define ADC_PPB2CONFIG2_SYNCINSEL_S   4U
#define ADC_PPB2CONFIG2_SYNCINSEL_M   0x3F0U    // Post Processing Block 2 Sync. Input Select
#define ADC_PPB2CONFIG2_SWSYNC        0x800U    // Post Processing Block 2 Software Force Sync.
#define ADC_PPB2CONFIG2_OSINTSEL      0x1000U   // Post Processing Block 2 Interrupt Source Select
#define ADC_PPB2CONFIG2_COMPSEL_S     14U
#define ADC_PPB2CONFIG2_COMPSEL_M     0xC000U   // Post Processing Block 2 Compare Source Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB2PSUM register
//
//*************************************************************************************************
#define ADC_PPB2PSUM_PSUM_S   0U
#define ADC_PPB2PSUM_PSUM_M   0xFFFFFFU     // Post Processing Block 2 Oversampling Partial Sum
#define ADC_PPB2PSUM_SIGN_S   24U
#define ADC_PPB2PSUM_SIGN_M   0xFF000000U   // Sign Extended Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB2PMAX register
//
//*************************************************************************************************
#define ADC_PPB2PMAX_PMAX_S   0U
#define ADC_PPB2PMAX_PMAX_M   0x1FFFFU      // Post Processing Block 2 Oversampling Partial Max
#define ADC_PPB2PMAX_SIGN_S   17U
#define ADC_PPB2PMAX_SIGN_M   0xFFFE0000U   // Sign Extended Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB2PMAXI register
//
//*************************************************************************************************
#define ADC_PPB2PMAXI_PMAXI_S   0U
#define ADC_PPB2PMAXI_PMAXI_M   0x3FFU   // Post Processing Block 2 Oversampling Partial Index of
                                         // Max

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB2PMIN register
//
//*************************************************************************************************
#define ADC_PPB2PMIN_PMIN_S   0U
#define ADC_PPB2PMIN_PMIN_M   0x1FFFFU      // Post Processing Block 2 Oversampling Partial Min
#define ADC_PPB2PMIN_SIGN_S   17U
#define ADC_PPB2PMIN_SIGN_M   0xFFFE0000U   // Sign Extended Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB2PMINI register
//
//*************************************************************************************************
#define ADC_PPB2PMINI_PMINI_S   0U
#define ADC_PPB2PMINI_PMINI_M   0x3FFU   // Post Processing Block 2 Oversampling Partial Index of
                                         // Min

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB2TRIPLO2 register
//
//*************************************************************************************************
#define ADC_PPB2TRIPLO2_LIMITLO_S   0U
#define ADC_PPB2TRIPLO2_LIMITLO_M   0xFFFFFFU   // ADC Post Processing Block 2 Trip Low Limit

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB3LIMIT register
//
//*************************************************************************************************
#define ADC_PPB3LIMIT_LIMIT_S   0U
#define ADC_PPB3LIMIT_LIMIT_M   0x3FFU   // Post Processing Block 3 Limit

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPBP3PCOUNT register
//
//*************************************************************************************************
#define ADC_PPBP3PCOUNT_PCOUNT_S   0U
#define ADC_PPBP3PCOUNT_PCOUNT_M   0x3FFU   // Post Processing Block 3 Partial Count

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB3CONFIG2 register
//
//*************************************************************************************************
#define ADC_PPB3CONFIG2_SHIFT_S       0U
#define ADC_PPB3CONFIG2_SHIFT_M       0xFU      // Post Processing Block 3 Right Shift
#define ADC_PPB3CONFIG2_SYNCINSEL_S   4U
#define ADC_PPB3CONFIG2_SYNCINSEL_M   0x3F0U    // Post Processing Block 3 Sync. Input Select
#define ADC_PPB3CONFIG2_SWSYNC        0x800U    // Post Processing Block 3 Software Force Sync.
#define ADC_PPB3CONFIG2_OSINTSEL      0x1000U   // Post Processing Block 3 Interrupt Source Select
#define ADC_PPB3CONFIG2_COMPSEL_S     14U
#define ADC_PPB3CONFIG2_COMPSEL_M     0xC000U   // Post Processing Block 3 Compare Source Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB3PSUM register
//
//*************************************************************************************************
#define ADC_PPB3PSUM_PSUM_S   0U
#define ADC_PPB3PSUM_PSUM_M   0xFFFFFFU     // Post Processing Block 3 Oversampling Partial Sum
#define ADC_PPB3PSUM_SIGN_S   24U
#define ADC_PPB3PSUM_SIGN_M   0xFF000000U   // Sign Extended Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB3PMAX register
//
//*************************************************************************************************
#define ADC_PPB3PMAX_PMAX_S   0U
#define ADC_PPB3PMAX_PMAX_M   0x1FFFFU      // Post Processing Block 3 Oversampling Partial Max
#define ADC_PPB3PMAX_SIGN_S   17U
#define ADC_PPB3PMAX_SIGN_M   0xFFFE0000U   // Sign Extended Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB3PMAXI register
//
//*************************************************************************************************
#define ADC_PPB3PMAXI_PMAXI_S   0U
#define ADC_PPB3PMAXI_PMAXI_M   0x3FFU   // Post Processing Block 3 Oversampling Partial Index of
                                         // Max

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB3PMIN register
//
//*************************************************************************************************
#define ADC_PPB3PMIN_PMIN_S   0U
#define ADC_PPB3PMIN_PMIN_M   0x1FFFFU      // Post Processing Block 3 Oversampling Partial Min
#define ADC_PPB3PMIN_SIGN_S   17U
#define ADC_PPB3PMIN_SIGN_M   0xFFFE0000U   // Sign Extended Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB3PMINI register
//
//*************************************************************************************************
#define ADC_PPB3PMINI_PMINI_S   0U
#define ADC_PPB3PMINI_PMINI_M   0x3FFU   // Post Processing Block 3 Oversampling Partial Index of
                                         // Min

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB3TRIPLO2 register
//
//*************************************************************************************************
#define ADC_PPB3TRIPLO2_LIMITLO_S   0U
#define ADC_PPB3TRIPLO2_LIMITLO_M   0xFFFFFFU   // ADC Post Processing Block 3 Trip Low Limit

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB4LIMIT register
//
//*************************************************************************************************
#define ADC_PPB4LIMIT_LIMIT_S   0U
#define ADC_PPB4LIMIT_LIMIT_M   0x3FFU   // Post Processing Block 4 Limit

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPBP4PCOUNT register
//
//*************************************************************************************************
#define ADC_PPBP4PCOUNT_PCOUNT_S   0U
#define ADC_PPBP4PCOUNT_PCOUNT_M   0x3FFU   // Post Processing Block 4 Partial Count

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB4CONFIG2 register
//
//*************************************************************************************************
#define ADC_PPB4CONFIG2_SHIFT_S       0U
#define ADC_PPB4CONFIG2_SHIFT_M       0xFU      // Post Processing Block 4 Right Shift
#define ADC_PPB4CONFIG2_SYNCINSEL_S   4U
#define ADC_PPB4CONFIG2_SYNCINSEL_M   0x3F0U    // Post Processing Block 4 Sync. Input Select
#define ADC_PPB4CONFIG2_SWSYNC        0x800U    // Post Processing Block 4 Software Force Sync.
#define ADC_PPB4CONFIG2_OSINTSEL      0x1000U   // Post Processing Block 4 Interrupt Source Select
#define ADC_PPB4CONFIG2_COMPSEL_S     14U
#define ADC_PPB4CONFIG2_COMPSEL_M     0xC000U   // Post Processing Block 4 Compare Source Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB4PSUM register
//
//*************************************************************************************************
#define ADC_PPB4PSUM_PSUM_S   0U
#define ADC_PPB4PSUM_PSUM_M   0xFFFFFFU     // Post Processing Block 4 Oversampling Partial Sum
#define ADC_PPB4PSUM_SIGN_S   24U
#define ADC_PPB4PSUM_SIGN_M   0xFF000000U   // Sign Extended Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB4PMAX register
//
//*************************************************************************************************
#define ADC_PPB4PMAX_PMAX_S   0U
#define ADC_PPB4PMAX_PMAX_M   0x1FFFFU      // Post Processing Block 4 Oversampling Partial Max
#define ADC_PPB4PMAX_SIGN_S   17U
#define ADC_PPB4PMAX_SIGN_M   0xFFFE0000U   // Sign Extended Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB4PMAXI register
//
//*************************************************************************************************
#define ADC_PPB4PMAXI_PMAXI_S   0U
#define ADC_PPB4PMAXI_PMAXI_M   0x3FFU   // Post Processing Block 4 Oversampling Partial Index of
                                         // Max

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB4PMIN register
//
//*************************************************************************************************
#define ADC_PPB4PMIN_PMIN_S   0U
#define ADC_PPB4PMIN_PMIN_M   0x1FFFFU      // Post Processing Block 4 Oversampling Partial Min
#define ADC_PPB4PMIN_SIGN_S   17U
#define ADC_PPB4PMIN_SIGN_M   0xFFFE0000U   // Sign Extended Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB4PMINI register
//
//*************************************************************************************************
#define ADC_PPB4PMINI_PMINI_S   0U
#define ADC_PPB4PMINI_PMINI_M   0x3FFU   // Post Processing Block 4 Oversampling Partial Index of
                                         // Min

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB4TRIPLO2 register
//
//*************************************************************************************************
#define ADC_PPB4TRIPLO2_LIMITLO_S   0U
#define ADC_PPB4TRIPLO2_LIMITLO_M   0xFFFFFFU   // ADC Post Processing Block 4 Trip Low Limit


//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB1RESULT register
//
//*************************************************************************************************
#define ADC_PPB1RESULT_PPBRESULT_S   0U
#define ADC_PPB1RESULT_PPBRESULT_M   0xFFFFU       // ADC Post Processing Block Result
#define ADC_PPB1RESULT_SIGN_S        16U
#define ADC_PPB1RESULT_SIGN_M        0xFFFF0000U   // Sign Extended Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB2RESULT register
//
//*************************************************************************************************
#define ADC_PPB2RESULT_PPBRESULT_S   0U
#define ADC_PPB2RESULT_PPBRESULT_M   0xFFFFU       // ADC Post Processing Block Result
#define ADC_PPB2RESULT_SIGN_S        16U
#define ADC_PPB2RESULT_SIGN_M        0xFFFF0000U   // Sign Extended Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB3RESULT register
//
//*************************************************************************************************
#define ADC_PPB3RESULT_PPBRESULT_S   0U
#define ADC_PPB3RESULT_PPBRESULT_M   0xFFFFU       // ADC Post Processing Block Result
#define ADC_PPB3RESULT_SIGN_S        16U
#define ADC_PPB3RESULT_SIGN_M        0xFFFF0000U   // Sign Extended Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB4RESULT register
//
//*************************************************************************************************
#define ADC_PPB4RESULT_PPBRESULT_S   0U
#define ADC_PPB4RESULT_PPBRESULT_M   0xFFFFU       // ADC Post Processing Block Result
#define ADC_PPB4RESULT_SIGN_S        16U
#define ADC_PPB4RESULT_SIGN_M        0xFFFF0000U   // Sign Extended Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB1SUM register
//
//*************************************************************************************************
#define ADC_PPB1SUM_SUM_S    0U
#define ADC_PPB1SUM_SUM_M    0xFFFFFFU     // Post Processing Block 1 Oversampling Sum
#define ADC_PPB1SUM_SIGN_S   24U
#define ADC_PPB1SUM_SIGN_M   0xFF000000U   // Sign Extended Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB1COUNT register
//
//*************************************************************************************************
#define ADC_PPB1COUNT_COUNT_S   0U
#define ADC_PPB1COUNT_COUNT_M   0x3FFU   // Post Processing Block 1 Final Count

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB2SUM register
//
//*************************************************************************************************
#define ADC_PPB2SUM_SUM_S    0U
#define ADC_PPB2SUM_SUM_M    0xFFFFFFU     // Post Processing Block 2 Oversampling Sum
#define ADC_PPB2SUM_SIGN_S   24U
#define ADC_PPB2SUM_SIGN_M   0xFF000000U   // Sign Extended Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB2COUNT register
//
//*************************************************************************************************
#define ADC_PPB2COUNT_COUNT_S   0U
#define ADC_PPB2COUNT_COUNT_M   0x3FFU   // Post Processing Block 2 Final Count

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB3SUM register
//
//*************************************************************************************************
#define ADC_PPB3SUM_SUM_S    0U
#define ADC_PPB3SUM_SUM_M    0xFFFFFFU     // Post Processing Block 3 Oversampling Sum
#define ADC_PPB3SUM_SIGN_S   24U
#define ADC_PPB3SUM_SIGN_M   0xFF000000U   // Sign Extended Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB3COUNT register
//
//*************************************************************************************************
#define ADC_PPB3COUNT_COUNT_S   0U
#define ADC_PPB3COUNT_COUNT_M   0x3FFU   // Post Processing Block 3 Final Count

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB4SUM register
//
//*************************************************************************************************
#define ADC_PPB4SUM_SUM_S    0U
#define ADC_PPB4SUM_SUM_M    0xFFFFFFU     // Post Processing Block 4 Oversampling Sum
#define ADC_PPB4SUM_SIGN_S   24U
#define ADC_PPB4SUM_SIGN_M   0xFF000000U   // Sign Extended Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB4COUNT register
//
//*************************************************************************************************
#define ADC_PPB4COUNT_COUNT_S   0U
#define ADC_PPB4COUNT_COUNT_M   0x3FFU   // Post Processing Block 4 Final Count

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB1MAX register
//
//*************************************************************************************************
#define ADC_PPB1MAX_MAX_S    0U
#define ADC_PPB1MAX_MAX_M    0x1FFFFU      // Post Processing Block 1 Oversampling Max
#define ADC_PPB1MAX_SIGN_S   17U
#define ADC_PPB1MAX_SIGN_M   0xFFFE0000U   // Sign Extended Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB1MAXI register
//
//*************************************************************************************************
#define ADC_PPB1MAXI_MAXI_S   0U
#define ADC_PPB1MAXI_MAXI_M   0x3FFU   // Post Processing Block 1 Oversampling Index of Max

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB1MIN register
//
//*************************************************************************************************
#define ADC_PPB1MIN_MIN_S    0U
#define ADC_PPB1MIN_MIN_M    0x1FFFFU      // Post Processing Block 1 Oversampling Min
#define ADC_PPB1MIN_SIGN_S   17U
#define ADC_PPB1MIN_SIGN_M   0xFFFE0000U   // Sign Extended Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB1MINI register
//
//*************************************************************************************************
#define ADC_PPB1MINI_MINI_S   0U
#define ADC_PPB1MINI_MINI_M   0x3FFU   // Post Processing Block 1 Oversampling Index of Min

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB2MAX register
//
//*************************************************************************************************
#define ADC_PPB2MAX_MAX_S    0U
#define ADC_PPB2MAX_MAX_M    0x1FFFFU      // Post Processing Block 2 Oversampling Max
#define ADC_PPB2MAX_SIGN_S   17U
#define ADC_PPB2MAX_SIGN_M   0xFFFE0000U   // Sign Extended Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB2MAXI register
//
//*************************************************************************************************
#define ADC_PPB2MAXI_MAXI_S   0U
#define ADC_PPB2MAXI_MAXI_M   0x3FFU   // Post Processing Block 2 Oversampling Index of Max

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB2MIN register
//
//*************************************************************************************************
#define ADC_PPB2MIN_MIN_S    0U
#define ADC_PPB2MIN_MIN_M    0x1FFFFU      // Post Processing Block 2 Oversampling Min
#define ADC_PPB2MIN_SIGN_S   17U
#define ADC_PPB2MIN_SIGN_M   0xFFFE0000U   // Sign Extended Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB2MINI register
//
//*************************************************************************************************
#define ADC_PPB2MINI_MINI_S   0U
#define ADC_PPB2MINI_MINI_M   0x3FFU   // Post Processing Block 2 Oversampling Index of Min

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB3MAX register
//
//*************************************************************************************************
#define ADC_PPB3MAX_MAX_S    0U
#define ADC_PPB3MAX_MAX_M    0x1FFFFU      // Post Processing Block 3 Oversampling Max
#define ADC_PPB3MAX_SIGN_S   17U
#define ADC_PPB3MAX_SIGN_M   0xFFFE0000U   // Sign Extended Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB3MAXI register
//
//*************************************************************************************************
#define ADC_PPB3MAXI_MAXI_S   0U
#define ADC_PPB3MAXI_MAXI_M   0x3FFU   // Post Processing Block 3 Oversampling Index of Max

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB3MIN register
//
//*************************************************************************************************
#define ADC_PPB3MIN_MIN_S    0U
#define ADC_PPB3MIN_MIN_M    0x1FFFFU      // Post Processing Block 3 Oversampling Min
#define ADC_PPB3MIN_SIGN_S   17U
#define ADC_PPB3MIN_SIGN_M   0xFFFE0000U   // Sign Extended Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB3MINI register
//
//*************************************************************************************************
#define ADC_PPB3MINI_MINI_S   0U
#define ADC_PPB3MINI_MINI_M   0x3FFU   // Post Processing Block 3 Oversampling Index of Min

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB4MAX register
//
//*************************************************************************************************
#define ADC_PPB4MAX_MAX_S    0U
#define ADC_PPB4MAX_MAX_M    0x1FFFFU      // Post Processing Block 4 Oversampling Max
#define ADC_PPB4MAX_SIGN_S   17U
#define ADC_PPB4MAX_SIGN_M   0xFFFE0000U   // Sign Extended Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB4MAXI register
//
//*************************************************************************************************
#define ADC_PPB4MAXI_MAXI_S   0U
#define ADC_PPB4MAXI_MAXI_M   0x3FFU   // Post Processing Block 4 Oversampling Index of Max

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB4MIN register
//
//*************************************************************************************************
#define ADC_PPB4MIN_MIN_S    0U
#define ADC_PPB4MIN_MIN_M    0x1FFFFU      // Post Processing Block 4 Oversampling Min
#define ADC_PPB4MIN_SIGN_S   17U
#define ADC_PPB4MIN_SIGN_M   0xFFFE0000U   // Sign Extended Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB4MINI register
//
//*************************************************************************************************
#define ADC_PPB4MINI_MINI_S   0U
#define ADC_PPB4MINI_MINI_M   0x3FFU   // Post Processing Block 4 Oversampling Index of Min



#endif
