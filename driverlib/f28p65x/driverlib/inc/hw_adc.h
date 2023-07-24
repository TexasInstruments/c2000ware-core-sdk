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
#define ADC_O_CTL1             0x0U    // ADC Control 1 Register
#define ADC_O_CTL2             0x1U    // ADC Control 2 Register
#define ADC_O_BURSTCTL         0x2U    // ADC Burst Control Register
#define ADC_O_INTFLG           0x3U    // ADC Interrupt Flag Register
#define ADC_O_INTFLGCLR        0x4U    // ADC Interrupt Flag Clear Register
#define ADC_O_INTOVF           0x5U    // ADC Interrupt Overflow Register
#define ADC_O_INTOVFCLR        0x6U    // ADC Interrupt Overflow Clear Register
#define ADC_O_INTSEL1N2        0x7U    // ADC Interrupt 1 and 2 Selection Register
#define ADC_O_INTSEL3N4        0x8U    // ADC Interrupt 3 and 4 Selection Register
#define ADC_O_SOCPRICTL        0x9U    // ADC SOC Priority Control Register
#define ADC_O_INTSOCSEL1       0xAU    // ADC Interrupt SOC Selection 1 Register
#define ADC_O_INTSOCSEL2       0xBU    // ADC Interrupt SOC Selection 2 Register
#define ADC_O_SOCFLG1          0xCU    // ADC SOC Flag 1 Register
#define ADC_O_SOCFRC1          0xDU    // ADC SOC Force 1 Register
#define ADC_O_SOCOVF1          0xEU    // ADC SOC Overflow 1 Register
#define ADC_O_SOCOVFCLR1       0xFU    // ADC SOC Overflow Clear 1 Register
#define ADC_O_SOC0CTL          0x10U   // ADC SOC0 Control Register
#define ADC_O_SOC1CTL          0x12U   // ADC SOC1 Control Register
#define ADC_O_SOC2CTL          0x14U   // ADC SOC2 Control Register
#define ADC_O_SOC3CTL          0x16U   // ADC SOC3 Control Register
#define ADC_O_SOC4CTL          0x18U   // ADC SOC4 Control Register
#define ADC_O_SOC5CTL          0x1AU   // ADC SOC5 Control Register
#define ADC_O_SOC6CTL          0x1CU   // ADC SOC6 Control Register
#define ADC_O_SOC7CTL          0x1EU   // ADC SOC7 Control Register
#define ADC_O_SOC8CTL          0x20U   // ADC SOC8 Control Register
#define ADC_O_SOC9CTL          0x22U   // ADC SOC9 Control Register
#define ADC_O_SOC10CTL         0x24U   // ADC SOC10 Control Register
#define ADC_O_SOC11CTL         0x26U   // ADC SOC11 Control Register
#define ADC_O_SOC12CTL         0x28U   // ADC SOC12 Control Register
#define ADC_O_SOC13CTL         0x2AU   // ADC SOC13 Control Register
#define ADC_O_SOC14CTL         0x2CU   // ADC SOC14 Control Register
#define ADC_O_SOC15CTL         0x2EU   // ADC SOC15 Control Register
#define ADC_O_EVTSTAT          0x30U   // ADC Event Status Register
#define ADC_O_EVTCLR           0x32U   // ADC Event Clear Register
#define ADC_O_EVTSEL           0x34U   // ADC Event Selection Register
#define ADC_O_EVTINTSEL        0x36U   // ADC Event Interrupt Selection Register
#define ADC_O_OSDETECT         0x38U   // ADC Open and Shorts Detect Register
#define ADC_O_COUNTER          0x39U   // ADC Counter Register
#define ADC_O_REV              0x3AU   // ADC Revision Register
#define ADC_O_OFFTRIM          0x3BU   // ADC Offset Trim Register
#define ADC_O_OFFTRIM2         0x3CU   // ADC Offset Trim Register
#define ADC_O_OFFTRIM3         0x3DU   // ADC Offset Trim Register
#define ADC_O_PPB1CONFIG       0x40U   // ADC PPB1 Config Register
#define ADC_O_PPB1STAMP        0x41U   // ADC PPB1 Sample Delay Time Stamp Register
#define ADC_O_PPB1OFFCAL       0x42U   // ADC PPB1 Offset Calibration Register
#define ADC_O_PPB1OFFREF       0x43U   // ADC PPB1 Offset Reference Register
#define ADC_O_PPB1TRIPHI       0x44U   // ADC PPB1 Trip High Register
#define ADC_O_PPB1TRIPLO       0x46U   // ADC PPB1 Trip Low/Trigger Time Stamp Register
#define ADC_O_PPB2CONFIG       0x48U   // ADC PPB2 Config Register
#define ADC_O_PPB2STAMP        0x49U   // ADC PPB2 Sample Delay Time Stamp Register
#define ADC_O_PPB2OFFCAL       0x4AU   // ADC PPB2 Offset Calibration Register
#define ADC_O_PPB2OFFREF       0x4BU   // ADC PPB2 Offset Reference Register
#define ADC_O_PPB2TRIPHI       0x4CU   // ADC PPB2 Trip High Register
#define ADC_O_PPB2TRIPLO       0x4EU   // ADC PPB2 Trip Low/Trigger Time Stamp Register
#define ADC_O_PPB3CONFIG       0x50U   // ADC PPB3 Config Register
#define ADC_O_PPB3STAMP        0x51U   // ADC PPB3 Sample Delay Time Stamp Register
#define ADC_O_PPB3OFFCAL       0x52U   // ADC PPB3 Offset Calibration Register
#define ADC_O_PPB3OFFREF       0x53U   // ADC PPB3 Offset Reference Register
#define ADC_O_PPB3TRIPHI       0x54U   // ADC PPB3 Trip High Register
#define ADC_O_PPB3TRIPLO       0x56U   // ADC PPB3 Trip Low/Trigger Time Stamp Register
#define ADC_O_PPB4CONFIG       0x58U   // ADC PPB4 Config Register
#define ADC_O_PPB4STAMP        0x59U   // ADC PPB4 Sample Delay Time Stamp Register
#define ADC_O_PPB4OFFCAL       0x5AU   // ADC PPB4 Offset Calibration Register
#define ADC_O_PPB4OFFREF       0x5BU   // ADC PPB4 Offset Reference Register
#define ADC_O_PPB4TRIPHI       0x5CU   // ADC PPB4 Trip High Register
#define ADC_O_PPB4TRIPLO       0x5EU   // ADC PPB4 Trip Low/Trigger Time Stamp Register
#define ADC_O_SAFECHECKRESEN   0x60U   // ADC Safe Check Result Enable Register
#define ADC_O_INTCYCLE         0x6FU   // ADC Early Interrupt Generation Cycle
#define ADC_O_INLTRIM1         0x70U   // ADC Linearity Trim 1 Register
#define ADC_O_INLTRIM2         0x72U   // ADC Linearity Trim 2 Register
#define ADC_O_INLTRIM3         0x74U   // ADC Linearity Trim 3 Register
#define ADC_O_INLTRIM4         0x76U   // ADC Linearity Trim 4 Register
#define ADC_O_INLTRIM5         0x78U   // ADC Linearity Trim 5 Register
#define ADC_O_INLTRIM6         0x7AU   // ADC Linearity Trim 6 Register
#define ADC_O_REV2             0x7DU   // ADC Wrapper Revision Register
#define ADC_O_REP1CTL          0x80U   // ADC Trigger Repeater 1 Control Register
#define ADC_O_REP1N            0x82U   // ADC Trigger Repeater 1 N Select Register
#define ADC_O_REP1PHASE        0x84U   // ADC Trigger Repeater 1 Phase Select Register
#define ADC_O_REP1SPREAD       0x86U   // ADC Trigger Repeater 1 Spread Select Register
#define ADC_O_REP1FRC          0x88U   // ADC Trigger Repeater 1 Software Force Register
#define ADC_O_REP2CTL          0x90U   // ADC Trigger Repeater 2 Control Register
#define ADC_O_REP2N            0x92U   // ADC Trigger Repeater 2 N Select Register
#define ADC_O_REP2PHASE        0x94U   // ADC Trigger Repeater 2 Phase Select Register
#define ADC_O_REP2SPREAD       0x96U   // ADC Trigger Repeater 2 Spread Select Register
#define ADC_O_REP2FRC          0x98U   // ADC Trigger Repeater 2 Software Force Register
#define ADC_O_PPB1LIMIT        0xA0U   // ADC PPB1Conversion Count Limit Register
#define ADC_O_PPBP1PCOUNT      0xA2U   // ADC PPB1 Partial Conversion Count Register
#define ADC_O_PPB1CONFIG2      0xA4U   // ADC PPB1 Sum Shift Register
#define ADC_O_PPB1PSUM         0xA6U   // ADC PPB1 Partial Sum Register
#define ADC_O_PPB1PMAX         0xA8U   // ADC PPB1 Partial Max Register
#define ADC_O_PPB1PMAXI        0xAAU   // ADC PPB1 Partial Max Index Register
#define ADC_O_PPB1PMIN         0xACU   // ADC PPB1 Partial MIN Register
#define ADC_O_PPB1PMINI        0xAEU   // ADC PPB1 Partial Min Index Register
#define ADC_O_PPB1TRIPLO2      0xB0U   // ADC PPB1 Extended Trip Low Register
#define ADC_O_PPB2LIMIT        0xBAU   // ADC PPB2Conversion Count Limit Register
#define ADC_O_PPBP2PCOUNT      0xBCU   // ADC PPB2 Partial Conversion Count Register
#define ADC_O_PPB2CONFIG2      0xBEU   // ADC PPB2 Sum Shift Register
#define ADC_O_PPB2PSUM         0xC0U   // ADC PPB2 Partial Sum Register
#define ADC_O_PPB2PMAX         0xC2U   // ADC PPB2 Partial Max Register
#define ADC_O_PPB2PMAXI        0xC4U   // ADC PPB2 Partial Max Index Register
#define ADC_O_PPB2PMIN         0xC6U   // ADC PPB2 Partial MIN Register
#define ADC_O_PPB2PMINI        0xC8U   // ADC PPB2 Partial Min Index Register
#define ADC_O_PPB2TRIPLO2      0xCAU   // ADC PPB2 Extended Trip Low Register
#define ADC_O_PPB3LIMIT        0xD4U   // ADC PPB3Conversion Count Limit Register
#define ADC_O_PPBP3PCOUNT      0xD6U   // ADC PPB3 Partial Conversion Count Register
#define ADC_O_PPB3CONFIG2      0xD8U   // ADC PPB3 Sum Shift Register
#define ADC_O_PPB3PSUM         0xDAU   // ADC PPB3 Partial Sum Register
#define ADC_O_PPB3PMAX         0xDCU   // ADC PPB3 Partial Max Register
#define ADC_O_PPB3PMAXI        0xDEU   // ADC PPB3 Partial Max Index Register
#define ADC_O_PPB3PMIN         0xE0U   // ADC PPB3 Partial MIN Register
#define ADC_O_PPB3PMINI        0xE2U   // ADC PPB3 Partial Min Index Register
#define ADC_O_PPB3TRIPLO2      0xE4U   // ADC PPB3 Extended Trip Low Register
#define ADC_O_PPB4LIMIT        0xEEU   // ADC PPB4Conversion Count Limit Register
#define ADC_O_PPBP4PCOUNT      0xF0U   // ADC PPB4 Partial Conversion Count Register
#define ADC_O_PPB4CONFIG2      0xF2U   // ADC PPB4 Sum Shift Register
#define ADC_O_PPB4PSUM         0xF4U   // ADC PPB4 Partial Sum Register
#define ADC_O_PPB4PMAX         0xF6U   // ADC PPB4 Partial Max Register
#define ADC_O_PPB4PMAXI        0xF8U   // ADC PPB4 Partial Max Index Register
#define ADC_O_PPB4PMIN         0xFAU   // ADC PPB4 Partial MIN Register
#define ADC_O_PPB4PMINI        0xFCU   // ADC PPB4 Partial Min Index Register
#define ADC_O_PPB4TRIPLO2      0xFEU   // ADC PPB4 Extended Trip Low Register

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
#define ADC_O_PPB1RESULT   0x10U   // ADC Post Processing Block 1 Result Register
#define ADC_O_PPB2RESULT   0x12U   // ADC Post Processing Block 2 Result Register
#define ADC_O_PPB3RESULT   0x14U   // ADC Post Processing Block 3 Result Register
#define ADC_O_PPB4RESULT   0x16U   // ADC Post Processing Block 4 Result Register
#define ADC_O_PPB1SUM      0x18U   // ADC PPB 1 Final Sum Result Register
#define ADC_O_PPB1COUNT    0x1AU   // ADC PPB1 Final Conversion Count Register
#define ADC_O_PPB2SUM      0x1CU   // ADC PPB 2 Final Sum Result Register
#define ADC_O_PPB2COUNT    0x1EU   // ADC PPB2 Final Conversion Count Register
#define ADC_O_PPB3SUM      0x20U   // ADC PPB 3 Final Sum Result Register
#define ADC_O_PPB3COUNT    0x22U   // ADC PPB3 Final Conversion Count Register
#define ADC_O_PPB4SUM      0x24U   // ADC PPB 4 Final Sum Result Register
#define ADC_O_PPB4COUNT    0x26U   // ADC PPB4 Final Conversion Count Register
#define ADC_O_PPB1MAX      0x28U   // ADC PPB 1 Final Max Result Register
#define ADC_O_PPB1MAXI     0x2AU   // ADC PPB 1 Final Max Index Result Register
#define ADC_O_PPB1MIN      0x2CU   // ADC PPB 1 Final Min Result Register
#define ADC_O_PPB1MINI     0x2EU   // ADC PPB 1 Final Min Index Result Register
#define ADC_O_PPB2MAX      0x30U   // ADC PPB 2 Final Max Result Register
#define ADC_O_PPB2MAXI     0x32U   // ADC PPB 2 Final Max Index Result Register
#define ADC_O_PPB2MIN      0x34U   // ADC PPB 2 Final Min Result Register
#define ADC_O_PPB2MINI     0x36U   // ADC PPB 2 Final Min Index Result Register
#define ADC_O_PPB3MAX      0x38U   // ADC PPB 3 Final Max Result Register
#define ADC_O_PPB3MAXI     0x3AU   // ADC PPB 3 Final Max Index Result Register
#define ADC_O_PPB3MIN      0x3CU   // ADC PPB 3 Final Min Result Register
#define ADC_O_PPB3MINI     0x3EU   // ADC PPB 3 Final Min Index Result Register
#define ADC_O_PPB4MAX      0x40U   // ADC PPB 4 Final Max Result Register
#define ADC_O_PPB4MAXI     0x42U   // ADC PPB 4 Final Max Index Result Register
#define ADC_O_PPB4MIN      0x44U   // ADC PPB 4 Final Min Result Register
#define ADC_O_PPB4MINI     0x46U   // ADC PPB 4 Final Min Index Result Register

#define ADC_O_CHECKCONFIG    0x0U   // ADC Check Configuration Register
#define ADC_O_CHECKSTATUS    0x2U   // ADC Check Status Register
#define ADC_O_RESSEL1        0x4U   // ADC Check 1 Select Register
#define ADC_O_RESSEL2        0x6U   // ADC Check 2 Select Register
#define ADC_O_TOLERANCE      0x8U   // ADC Check Tolerance Register
#define ADC_O_CHECKRESULT1   0xCU   // ADC Check Captured Result 1
#define ADC_O_CHECKRESULT2   0xEU   // ADC Check Captured Result 2

#define ADC_O_OOTFLG           0x0U    // Checker Out-of-Tolerance Flag Register
#define ADC_O_OOTFLGCLR        0x2U    // Checker Out-of-Tolerance Flag Clear Register
#define ADC_O_RES1OVF          0x4U    // Checker Overflow Result 1 Flag Register
#define ADC_O_RES1OVFCLR       0x6U    // Checker Overflow Result 1 Flag Clear Register
#define ADC_O_RES2OVF          0x8U    // Checker Overflow Result 2 Flag Register
#define ADC_O_RES2OVFCLR       0xAU    // Checker Overflow Result 2 Flag Clear Register
#define ADC_O_CHECKINTFLG      0xCU    // Checker Interrupt Flag Register
#define ADC_O_CHECKINTFLGCLR   0xEU    // Checker Interrupt Flag Clear Register
#define ADC_O_CHECKINTSEL1     0x10U   // Checker Interrupt Source Select Register 1
#define ADC_O_CHECKINTSEL2     0x12U   // Checker Interrupt Source Select Register 2
#define ADC_O_CHECKINTSEL3     0x14U   // Checker Interrupt Source Select Register 3
#define ADC_O_CHECKEVT1SEL1    0x18U   // Checker X-Bar EVT1 Source Select Register 1
#define ADC_O_CHECKEVT1SEL2    0x1AU   // Checker X-Bar EVT1 Source Select Register 2
#define ADC_O_CHECKEVT1SEL3    0x1CU   // Checker X-Bar EVT1 Source Select Register 3
#define ADC_O_CHECKEVT2SEL1    0x20U   // Checker X-Bar EVT2 Source Select Register 1
#define ADC_O_CHECKEVT2SEL2    0x22U   // Checker X-Bar EVT2 Source Select Register 2
#define ADC_O_CHECKEVT2SEL3    0x24U   // Checker X-Bar EVT2 Source Select Register 3
#define ADC_O_CHECKEVT3SEL1    0x28U   // Checker X-Bar EVT3 Source Select Register 1
#define ADC_O_CHECKEVT3SEL2    0x2AU   // Checker X-Bar EVT3 Source Select Register 2
#define ADC_O_CHECKEVT3SEL3    0x2CU   // Checker X-Bar EVT3 Source Select Register 3
#define ADC_O_CHECKEVT4SEL1    0x30U   // Checker X-Bar EVT4 Source Select Register 1
#define ADC_O_CHECKEVT4SEL2    0x32U   // Checker X-Bar EVT4 Source Select Register 2
#define ADC_O_CHECKEVT4SEL3    0x34U   // Checker X-Bar EVT4 Source Select Register 3


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
#define ADC_CTL2_PRESCALE_S    0U
#define ADC_CTL2_PRESCALE_M    0xFU     // ADC Clock Prescaler
#define ADC_CTL2_RESOLUTION    0x40U    // SOC Conversion Resolution
#define ADC_CTL2_SIGNALMODE    0x80U    // SOC Signaling Mode
#define ADC_CTL2_OFFTRIMMODE   0x100U   // Offset Trim Mode

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
#define ADC_INTSEL1N2_INT1SEL_M   0x1FU     // ADCINT1 EOC Source Select
#define ADC_INTSEL1N2_INT1E       0x20U     // ADCINT1 Interrupt Enable
#define ADC_INTSEL1N2_INT1CONT    0x40U     // ADCINT1 Continue to Interrupt Mode
#define ADC_INTSEL1N2_INT2SEL_S   8U
#define ADC_INTSEL1N2_INT2SEL_M   0x1F00U   // ADCINT2 EOC Source Select
#define ADC_INTSEL1N2_INT2E       0x2000U   // ADCINT2 Interrupt Enable
#define ADC_INTSEL1N2_INT2CONT    0x4000U   // ADCINT2 Continue to Interrupt Mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCINTSEL3N4 register
//
//*************************************************************************************************
#define ADC_INTSEL3N4_INT3SEL_S   0U
#define ADC_INTSEL3N4_INT3SEL_M   0x1FU     // ADCINT3 EOC Source Select
#define ADC_INTSEL3N4_INT3E       0x20U     // ADCINT3 Interrupt Enable
#define ADC_INTSEL3N4_INT3CONT    0x40U     // ADCINT3 Continue to Interrupt Mode
#define ADC_INTSEL3N4_INT4SEL_S   8U
#define ADC_INTSEL3N4_INT4SEL_M   0x1F00U   // ADCINT4 EOC Source Select
#define ADC_INTSEL3N4_INT4E       0x2000U   // ADCINT4 Interrupt Enable
#define ADC_INTSEL3N4_INT4CONT    0x4000U   // ADCINT4 Continue to Interrupt Mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOCPRICTL register
//
//*************************************************************************************************
#define ADC_SOCPRICTL_SOCPRIORITY_S   0U
#define ADC_SOCPRICTL_SOCPRIORITY_M   0x1FU    // SOC Priority
#define ADC_SOCPRICTL_RRPOINTER_S     5U
#define ADC_SOCPRICTL_RRPOINTER_M     0x3E0U   // Round Robin Pointer

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCINTSOCSEL1 register
//
//*************************************************************************************************
#define ADC_INTSOCSEL1_SOC0_S   0U
#define ADC_INTSOCSEL1_SOC0_M   0x3U      // SOC0 ADC Interrupt Trigger Select
#define ADC_INTSOCSEL1_SOC1_S   2U
#define ADC_INTSOCSEL1_SOC1_M   0xCU      // SOC1 ADC Interrupt Trigger Select
#define ADC_INTSOCSEL1_SOC2_S   4U
#define ADC_INTSOCSEL1_SOC2_M   0x30U     // SOC2 ADC Interrupt Trigger Select
#define ADC_INTSOCSEL1_SOC3_S   6U
#define ADC_INTSOCSEL1_SOC3_M   0xC0U     // SOC3 ADC Interrupt Trigger Select
#define ADC_INTSOCSEL1_SOC4_S   8U
#define ADC_INTSOCSEL1_SOC4_M   0x300U    // SOC4 ADC Interrupt Trigger Select
#define ADC_INTSOCSEL1_SOC5_S   10U
#define ADC_INTSOCSEL1_SOC5_M   0xC00U    // SOC5 ADC Interrupt Trigger Select
#define ADC_INTSOCSEL1_SOC6_S   12U
#define ADC_INTSOCSEL1_SOC6_M   0x3000U   // SOC6 ADC Interrupt Trigger Select
#define ADC_INTSOCSEL1_SOC7_S   14U
#define ADC_INTSOCSEL1_SOC7_M   0xC000U   // SOC7 ADC Interrupt Trigger Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCINTSOCSEL2 register
//
//*************************************************************************************************
#define ADC_INTSOCSEL2_SOC8_S    0U
#define ADC_INTSOCSEL2_SOC8_M    0x3U      // SOC8 ADC Interrupt Trigger Select
#define ADC_INTSOCSEL2_SOC9_S    2U
#define ADC_INTSOCSEL2_SOC9_M    0xCU      // SOC9 ADC Interrupt Trigger Select
#define ADC_INTSOCSEL2_SOC10_S   4U
#define ADC_INTSOCSEL2_SOC10_M   0x30U     // SOC10 ADC Interrupt Trigger Select
#define ADC_INTSOCSEL2_SOC11_S   6U
#define ADC_INTSOCSEL2_SOC11_M   0xC0U     // SOC11 ADC Interrupt Trigger Select
#define ADC_INTSOCSEL2_SOC12_S   8U
#define ADC_INTSOCSEL2_SOC12_M   0x300U    // SOC12 ADC Interrupt Trigger Select
#define ADC_INTSOCSEL2_SOC13_S   10U
#define ADC_INTSOCSEL2_SOC13_M   0xC00U    // SOC13 ADC Interrupt Trigger Select
#define ADC_INTSOCSEL2_SOC14_S   12U
#define ADC_INTSOCSEL2_SOC14_M   0x3000U   // SOC14 ADC Interrupt Trigger Select
#define ADC_INTSOCSEL2_SOC15_S   14U
#define ADC_INTSOCSEL2_SOC15_M   0xC000U   // SOC15 ADC Interrupt Trigger Select

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
#define ADC_SOC0CTL_ACQPS_S      0U
#define ADC_SOC0CTL_ACQPS_M      0x1FFU        // SOC0 Acquisition Prescale
#define ADC_SOC0CTL_CHSEL_S      15U
#define ADC_SOC0CTL_CHSEL_M      0xF8000U      // SOC0 Channel Select
#define ADC_SOC0CTL_TRIGSEL_S    20U
#define ADC_SOC0CTL_TRIGSEL_M    0x7F00000U    // SOC0 Trigger Source Select
#define ADC_SOC0CTL_EXTCHSEL_S   28U
#define ADC_SOC0CTL_EXTCHSEL_M   0xF0000000U   // SOC0 External Channel Mux Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC1CTL register
//
//*************************************************************************************************
#define ADC_SOC1CTL_ACQPS_S      0U
#define ADC_SOC1CTL_ACQPS_M      0x1FFU        // SOC1 Acquisition Prescale
#define ADC_SOC1CTL_CHSEL_S      15U
#define ADC_SOC1CTL_CHSEL_M      0xF8000U      // SOC1 Channel Select
#define ADC_SOC1CTL_TRIGSEL_S    20U
#define ADC_SOC1CTL_TRIGSEL_M    0x7F00000U    // SOC1 Trigger Source Select
#define ADC_SOC1CTL_EXTCHSEL_S   28U
#define ADC_SOC1CTL_EXTCHSEL_M   0xF0000000U   // SOC1 External Channel Mux Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC2CTL register
//
//*************************************************************************************************
#define ADC_SOC2CTL_ACQPS_S      0U
#define ADC_SOC2CTL_ACQPS_M      0x1FFU        // SOC2 Acquisition Prescale
#define ADC_SOC2CTL_CHSEL_S      15U
#define ADC_SOC2CTL_CHSEL_M      0xF8000U      // SOC2 Channel Select
#define ADC_SOC2CTL_TRIGSEL_S    20U
#define ADC_SOC2CTL_TRIGSEL_M    0x7F00000U    // SOC2 Trigger Source Select
#define ADC_SOC2CTL_EXTCHSEL_S   28U
#define ADC_SOC2CTL_EXTCHSEL_M   0xF0000000U   // SOC2 External Channel Mux Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC3CTL register
//
//*************************************************************************************************
#define ADC_SOC3CTL_ACQPS_S      0U
#define ADC_SOC3CTL_ACQPS_M      0x1FFU        // SOC3 Acquisition Prescale
#define ADC_SOC3CTL_CHSEL_S      15U
#define ADC_SOC3CTL_CHSEL_M      0xF8000U      // SOC3 Channel Select
#define ADC_SOC3CTL_TRIGSEL_S    20U
#define ADC_SOC3CTL_TRIGSEL_M    0x7F00000U    // SOC3 Trigger Source Select
#define ADC_SOC3CTL_EXTCHSEL_S   28U
#define ADC_SOC3CTL_EXTCHSEL_M   0xF0000000U   // SOC3 External Channel Mux Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC4CTL register
//
//*************************************************************************************************
#define ADC_SOC4CTL_ACQPS_S      0U
#define ADC_SOC4CTL_ACQPS_M      0x1FFU        // SOC4 Acquisition Prescale
#define ADC_SOC4CTL_CHSEL_S      15U
#define ADC_SOC4CTL_CHSEL_M      0xF8000U      // SOC4 Channel Select
#define ADC_SOC4CTL_TRIGSEL_S    20U
#define ADC_SOC4CTL_TRIGSEL_M    0x7F00000U    // SOC4 Trigger Source Select
#define ADC_SOC4CTL_EXTCHSEL_S   28U
#define ADC_SOC4CTL_EXTCHSEL_M   0xF0000000U   // SOC4 External Channel Mux Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC5CTL register
//
//*************************************************************************************************
#define ADC_SOC5CTL_ACQPS_S      0U
#define ADC_SOC5CTL_ACQPS_M      0x1FFU        // SOC5 Acquisition Prescale
#define ADC_SOC5CTL_CHSEL_S      15U
#define ADC_SOC5CTL_CHSEL_M      0xF8000U      // SOC5 Channel Select
#define ADC_SOC5CTL_TRIGSEL_S    20U
#define ADC_SOC5CTL_TRIGSEL_M    0x7F00000U    // SOC5 Trigger Source Select
#define ADC_SOC5CTL_EXTCHSEL_S   28U
#define ADC_SOC5CTL_EXTCHSEL_M   0xF0000000U   // SOC5 External Channel Mux Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC6CTL register
//
//*************************************************************************************************
#define ADC_SOC6CTL_ACQPS_S      0U
#define ADC_SOC6CTL_ACQPS_M      0x1FFU        // SOC6 Acquisition Prescale
#define ADC_SOC6CTL_CHSEL_S      15U
#define ADC_SOC6CTL_CHSEL_M      0xF8000U      // SOC6 Channel Select
#define ADC_SOC6CTL_TRIGSEL_S    20U
#define ADC_SOC6CTL_TRIGSEL_M    0x7F00000U    // SOC6 Trigger Source Select
#define ADC_SOC6CTL_EXTCHSEL_S   28U
#define ADC_SOC6CTL_EXTCHSEL_M   0xF0000000U   // SOC6 External Channel Mux Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC7CTL register
//
//*************************************************************************************************
#define ADC_SOC7CTL_ACQPS_S      0U
#define ADC_SOC7CTL_ACQPS_M      0x1FFU        // SOC7 Acquisition Prescale
#define ADC_SOC7CTL_CHSEL_S      15U
#define ADC_SOC7CTL_CHSEL_M      0xF8000U      // SOC7 Channel Select
#define ADC_SOC7CTL_TRIGSEL_S    20U
#define ADC_SOC7CTL_TRIGSEL_M    0x7F00000U    // SOC7 Trigger Source Select
#define ADC_SOC7CTL_EXTCHSEL_S   28U
#define ADC_SOC7CTL_EXTCHSEL_M   0xF0000000U   // SOC7 External Channel Mux Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC8CTL register
//
//*************************************************************************************************
#define ADC_SOC8CTL_ACQPS_S      0U
#define ADC_SOC8CTL_ACQPS_M      0x1FFU        // SOC8 Acquisition Prescale
#define ADC_SOC8CTL_CHSEL_S      15U
#define ADC_SOC8CTL_CHSEL_M      0xF8000U      // SOC8 Channel Select
#define ADC_SOC8CTL_TRIGSEL_S    20U
#define ADC_SOC8CTL_TRIGSEL_M    0x7F00000U    // SOC8 Trigger Source Select
#define ADC_SOC8CTL_EXTCHSEL_S   28U
#define ADC_SOC8CTL_EXTCHSEL_M   0xF0000000U   // SOC8 External Channel Mux Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC9CTL register
//
//*************************************************************************************************
#define ADC_SOC9CTL_ACQPS_S      0U
#define ADC_SOC9CTL_ACQPS_M      0x1FFU        // SOC9 Acquisition Prescale
#define ADC_SOC9CTL_CHSEL_S      15U
#define ADC_SOC9CTL_CHSEL_M      0xF8000U      // SOC9 Channel Select
#define ADC_SOC9CTL_TRIGSEL_S    20U
#define ADC_SOC9CTL_TRIGSEL_M    0x7F00000U    // SOC9 Trigger Source Select
#define ADC_SOC9CTL_EXTCHSEL_S   28U
#define ADC_SOC9CTL_EXTCHSEL_M   0xF0000000U   // SOC9 External Channel Mux Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC10CTL register
//
//*************************************************************************************************
#define ADC_SOC10CTL_ACQPS_S      0U
#define ADC_SOC10CTL_ACQPS_M      0x1FFU        // SOC10 Acquisition Prescale
#define ADC_SOC10CTL_CHSEL_S      15U
#define ADC_SOC10CTL_CHSEL_M      0xF8000U      // SOC10 Channel Select
#define ADC_SOC10CTL_TRIGSEL_S    20U
#define ADC_SOC10CTL_TRIGSEL_M    0x7F00000U    // SOC10 Trigger Source Select
#define ADC_SOC10CTL_EXTCHSEL_S   28U
#define ADC_SOC10CTL_EXTCHSEL_M   0xF0000000U   // SOC10 External Channel Mux Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC11CTL register
//
//*************************************************************************************************
#define ADC_SOC11CTL_ACQPS_S      0U
#define ADC_SOC11CTL_ACQPS_M      0x1FFU        // SOC11 Acquisition Prescale
#define ADC_SOC11CTL_CHSEL_S      15U
#define ADC_SOC11CTL_CHSEL_M      0xF8000U      // SOC11 Channel Select
#define ADC_SOC11CTL_TRIGSEL_S    20U
#define ADC_SOC11CTL_TRIGSEL_M    0x7F00000U    // SOC11 Trigger Source Select
#define ADC_SOC11CTL_EXTCHSEL_S   28U
#define ADC_SOC11CTL_EXTCHSEL_M   0xF0000000U   // SOC11 External Channel Mux Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC12CTL register
//
//*************************************************************************************************
#define ADC_SOC12CTL_ACQPS_S      0U
#define ADC_SOC12CTL_ACQPS_M      0x1FFU        // SOC12 Acquisition Prescale
#define ADC_SOC12CTL_CHSEL_S      15U
#define ADC_SOC12CTL_CHSEL_M      0xF8000U      // SOC12 Channel Select
#define ADC_SOC12CTL_TRIGSEL_S    20U
#define ADC_SOC12CTL_TRIGSEL_M    0x7F00000U    // SOC12 Trigger Source Select
#define ADC_SOC12CTL_EXTCHSEL_S   28U
#define ADC_SOC12CTL_EXTCHSEL_M   0xF0000000U   // SOC12 External Channel Mux Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC13CTL register
//
//*************************************************************************************************
#define ADC_SOC13CTL_ACQPS_S      0U
#define ADC_SOC13CTL_ACQPS_M      0x1FFU        // SOC13 Acquisition Prescale
#define ADC_SOC13CTL_CHSEL_S      15U
#define ADC_SOC13CTL_CHSEL_M      0xF8000U      // SOC13 Channel Select
#define ADC_SOC13CTL_TRIGSEL_S    20U
#define ADC_SOC13CTL_TRIGSEL_M    0x7F00000U    // SOC13 Trigger Source Select
#define ADC_SOC13CTL_EXTCHSEL_S   28U
#define ADC_SOC13CTL_EXTCHSEL_M   0xF0000000U   // SOC13 External Channel Mux Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC14CTL register
//
//*************************************************************************************************
#define ADC_SOC14CTL_ACQPS_S      0U
#define ADC_SOC14CTL_ACQPS_M      0x1FFU        // SOC14 Acquisition Prescale
#define ADC_SOC14CTL_CHSEL_S      15U
#define ADC_SOC14CTL_CHSEL_M      0xF8000U      // SOC14 Channel Select
#define ADC_SOC14CTL_TRIGSEL_S    20U
#define ADC_SOC14CTL_TRIGSEL_M    0x7F00000U    // SOC14 Trigger Source Select
#define ADC_SOC14CTL_EXTCHSEL_S   28U
#define ADC_SOC14CTL_EXTCHSEL_M   0xF0000000U   // SOC14 External Channel Mux Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC15CTL register
//
//*************************************************************************************************
#define ADC_SOC15CTL_ACQPS_S      0U
#define ADC_SOC15CTL_ACQPS_M      0x1FFU        // SOC15 Acquisition Prescale
#define ADC_SOC15CTL_CHSEL_S      15U
#define ADC_SOC15CTL_CHSEL_M      0xF8000U      // SOC15 Channel Select
#define ADC_SOC15CTL_TRIGSEL_S    20U
#define ADC_SOC15CTL_TRIGSEL_M    0x7F00000U    // SOC15 Trigger Source Select
#define ADC_SOC15CTL_EXTCHSEL_S   28U
#define ADC_SOC15CTL_EXTCHSEL_M   0xF0000000U   // SOC15 External Channel Mux Select

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
// The following are defines for the bit fields in the ADCOSDETECT register
//
//*************************************************************************************************
#define ADC_OSDETECT_DETECTCFG_S   0U
#define ADC_OSDETECT_DETECTCFG_M   0x7U   // ADC Opens and Shorts Detect Configuration

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
#define ADC_OFFTRIM_OFFTRIM_S           0U
#define ADC_OFFTRIM_OFFTRIM_M           0xFFU     // ADC Offset Trim 12B SE Even
#define ADC_OFFTRIM_OFFTRIM12BSEODD_S   8U
#define ADC_OFFTRIM_OFFTRIM12BSEODD_M   0xFF00U   // ADC Offset Trim 12B SE Odd

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCOFFTRIM2 register
//
//*************************************************************************************************
#define ADC_OFFTRIM2_OFFTRIM16BSEEVEN_S   0U
#define ADC_OFFTRIM2_OFFTRIM16BSEEVEN_M   0xFFU     // ADC Offset Trim 16B SE Even
#define ADC_OFFTRIM2_OFFTRIM16BSEODD_S    8U
#define ADC_OFFTRIM2_OFFTRIM16BSEODD_M    0xFF00U   // ADC Offset Trim 16B SE Odd

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCOFFTRIM3 register
//
//*************************************************************************************************
#define ADC_OFFTRIM3_OFFTRIM12BDE_S   0U
#define ADC_OFFTRIM3_OFFTRIM12BDE_M   0xFFU     // ADC Offset Trim 12B DE
#define ADC_OFFTRIM3_OFFTRIM16BDE_S   8U
#define ADC_OFFTRIM3_OFFTRIM16BDE_M   0xFF00U   // ADC Offset Trim 16B DE

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB1CONFIG register
//
//*************************************************************************************************
#define ADC_PPB1CONFIG_CONFIG_S     0U
#define ADC_PPB1CONFIG_CONFIG_M     0xFU    // ADC Post Processing Block 1 Configuration
#define ADC_PPB1CONFIG_TWOSCOMPEN   0x10U   // ADC Post Processing Block 1 Two's Complement Enable
#define ADC_PPB1CONFIG_CBCEN        0x20U   // Cycle By Cycle Enable
#define ADC_PPB1CONFIG_ABSEN        0x40U   // ADC Post Processing Block 1 Absolute Enable

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
// The following are defines for the bit fields in the ADCPPB2CONFIG register
//
//*************************************************************************************************
#define ADC_PPB2CONFIG_CONFIG_S     0U
#define ADC_PPB2CONFIG_CONFIG_M     0xFU    // ADC Post Processing Block 2 Configuration
#define ADC_PPB2CONFIG_TWOSCOMPEN   0x10U   // ADC Post Processing Block 2 Two's Complement Enable
#define ADC_PPB2CONFIG_CBCEN        0x20U   // Cycle By Cycle Enable
#define ADC_PPB2CONFIG_ABSEN        0x40U   // ADC Post Processing Block 2 Absolute Enable

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
// The following are defines for the bit fields in the ADCPPB3CONFIG register
//
//*************************************************************************************************
#define ADC_PPB3CONFIG_CONFIG_S     0U
#define ADC_PPB3CONFIG_CONFIG_M     0xFU    // ADC Post Processing Block 3 Configuration
#define ADC_PPB3CONFIG_TWOSCOMPEN   0x10U   // ADC Post Processing Block 3 Two's Complement Enable
#define ADC_PPB3CONFIG_CBCEN        0x20U   // Cycle By Cycle Enable
#define ADC_PPB3CONFIG_ABSEN        0x40U   // ADC Post Processing Block 3 Absolute Enable

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
// The following are defines for the bit fields in the ADCPPB4CONFIG register
//
//*************************************************************************************************
#define ADC_PPB4CONFIG_CONFIG_S     0U
#define ADC_PPB4CONFIG_CONFIG_M     0xFU    // ADC Post Processing Block 4 Configuration
#define ADC_PPB4CONFIG_TWOSCOMPEN   0x10U   // ADC Post Processing Block 4 Two's Complement Enable
#define ADC_PPB4CONFIG_CBCEN        0x20U   // Cycle By Cycle Enable
#define ADC_PPB4CONFIG_ABSEN        0x40U   // ADC Post Processing Block 4 Absolute Enable

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
// The following are defines for the bit fields in the ADCSAFECHECKRESEN register
//
//*************************************************************************************************
#define ADC_SAFECHECKRESEN_SOC0CHKEN_S    0U
#define ADC_SAFECHECKRESEN_SOC0CHKEN_M    0x3U          // ADC SOC0 Safety Checker Result Enable
#define ADC_SAFECHECKRESEN_SOC1CHKEN_S    2U
#define ADC_SAFECHECKRESEN_SOC1CHKEN_M    0xCU          // ADC SOC1 Safety Checker Result Enable
#define ADC_SAFECHECKRESEN_SOC2CHKEN_S    4U
#define ADC_SAFECHECKRESEN_SOC2CHKEN_M    0x30U         // ADC SOC2 Safety Checker Result Enable
#define ADC_SAFECHECKRESEN_SOC3CHKEN_S    6U
#define ADC_SAFECHECKRESEN_SOC3CHKEN_M    0xC0U         // ADC SOC3 Safety Checker Result Enable
#define ADC_SAFECHECKRESEN_SOC4CHKEN_S    8U
#define ADC_SAFECHECKRESEN_SOC4CHKEN_M    0x300U        // ADC SOC4 Safety Checker Result Enable
#define ADC_SAFECHECKRESEN_SOC5CHKEN_S    10U
#define ADC_SAFECHECKRESEN_SOC5CHKEN_M    0xC00U        // ADC SOC5 Safety Checker Result Enable
#define ADC_SAFECHECKRESEN_SOC6CHKEN_S    12U
#define ADC_SAFECHECKRESEN_SOC6CHKEN_M    0x3000U       // ADC SOC6 Safety Checker Result Enable
#define ADC_SAFECHECKRESEN_SOC7CHKEN_S    14U
#define ADC_SAFECHECKRESEN_SOC7CHKEN_M    0xC000U       // ADC SOC7 Safety Checker Result Enable
#define ADC_SAFECHECKRESEN_SOC8CHKEN_S    16U
#define ADC_SAFECHECKRESEN_SOC8CHKEN_M    0x30000U      // ADC SOC8 Safety Checker Result Enable
#define ADC_SAFECHECKRESEN_SOC9CHKEN_S    18U
#define ADC_SAFECHECKRESEN_SOC9CHKEN_M    0xC0000U      // ADC SOC9 Safety Checker Result Enable
#define ADC_SAFECHECKRESEN_SOC10CHKEN_S   20U
#define ADC_SAFECHECKRESEN_SOC10CHKEN_M   0x300000U     // ADC SOC10 Safety Checker Result Enable
#define ADC_SAFECHECKRESEN_SOC11CHKEN_S   22U
#define ADC_SAFECHECKRESEN_SOC11CHKEN_M   0xC00000U     // ADC SOC11 Safety Checker Result Enable
#define ADC_SAFECHECKRESEN_SOC12CHKEN_S   24U
#define ADC_SAFECHECKRESEN_SOC12CHKEN_M   0x3000000U    // ADC SOC12 Safety Checker Result Enable
#define ADC_SAFECHECKRESEN_SOC13CHKEN_S   26U
#define ADC_SAFECHECKRESEN_SOC13CHKEN_M   0xC000000U    // ADC SOC13 Safety Checker Result Enable
#define ADC_SAFECHECKRESEN_SOC14CHKEN_S   28U
#define ADC_SAFECHECKRESEN_SOC14CHKEN_M   0x30000000U   // ADC SOC14 Safety Checker Result Enable
#define ADC_SAFECHECKRESEN_SOC15CHKEN_S   30U
#define ADC_SAFECHECKRESEN_SOC15CHKEN_M   0xC0000000U   // ADC SOC15 Safety Checker Result Enable

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
#define ADC_REP1CTL_SYNCINSEL_M   0x1F0000U   // ADC Trigger Repeater 1 Sync. In Select
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
#define ADC_REP2CTL_SYNCINSEL_M   0x1F0000U   // ADC Trigger Repeater 2 Sync. In Select
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
#define ADC_PPB1CONFIG2_SYNCINSEL_M   0x1F0U    // Post Processing Block 1 Sync. Input Select
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
#define ADC_PPB2CONFIG2_SYNCINSEL_M   0x1F0U    // Post Processing Block 2 Sync. Input Select
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
#define ADC_PPB3CONFIG2_SYNCINSEL_M   0x1F0U    // Post Processing Block 3 Sync. Input Select
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
#define ADC_PPB4CONFIG2_SYNCINSEL_M   0x1F0U    // Post Processing Block 4 Sync. Input Select
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


//*************************************************************************************************
//
// The following are defines for the bit fields in the CHECKCONFIG register
//
//*************************************************************************************************
#define ADC_CHECKCONFIG_SWSYNC   0x40U     // Result Safe Check SW Force Sync.
#define ADC_CHECKCONFIG_CHKEN    0x8000U   // Result Safe Check Module Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the CHECKSTATUS register
//
//*************************************************************************************************
#define ADC_CHECKSTATUS_RES1READY   0x1U   // Result Safe Check Result 1 Arrived
#define ADC_CHECKSTATUS_RES2READY   0x2U   // Result Safe Check Result 2 Arrived
#define ADC_CHECKSTATUS_OOT         0x4U   // Safe Check OOT Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCRESSEL1 register
//
//*************************************************************************************************
#define ADC_RESSEL1_ADCSEL_S         0U
#define ADC_RESSEL1_ADCSEL_M         0x7U     // Result Safe Check ADC Select 1
#define ADC_RESSEL1_ADCRESULTSEL_S   4U
#define ADC_RESSEL1_ADCRESULTSEL_M   0x3F0U   // Result Safe Check Result Select 1

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCRESSEL2 register
//
//*************************************************************************************************
#define ADC_RESSEL2_ADCSEL_S         0U
#define ADC_RESSEL2_ADCSEL_M         0x7U     // Result Safe Check ADC Select 2
#define ADC_RESSEL2_ADCRESULTSEL_S   4U
#define ADC_RESSEL2_ADCRESULTSEL_M   0x3F0U   // Result Safe Check Result Select 2

//*************************************************************************************************
//
// The following are defines for the bit fields in the TOLERANCE register
//
//*************************************************************************************************
#define ADC_TOLERANCE_TOLERANCE_S   0U
#define ADC_TOLERANCE_TOLERANCE_M   0xFFFFFFU   // Result Safe Check Tolerance

//*************************************************************************************************
//
// The following are defines for the bit fields in the CHECKRESULT1 register
//
//*************************************************************************************************
#define ADC_CHECKRESULT1_RESULT_S   0U
#define ADC_CHECKRESULT1_RESULT_M   0xFFFFFFU   // Result Safe Check Captured Result

//*************************************************************************************************
//
// The following are defines for the bit fields in the CHECKRESULT2 register
//
//*************************************************************************************************
#define ADC_CHECKRESULT2_RESULT_S   0U
#define ADC_CHECKRESULT2_RESULT_M   0xFFFFFFU   // Result Safe Check Captured Result


//*************************************************************************************************
//
// The following are defines for the bit fields in the OOTFLG register
//
//*************************************************************************************************
#define ADC_OOTFLG_OOT1    0x1U      // Checker 1 Out-of-Tolerance Flag
#define ADC_OOTFLG_OOT2    0x2U      // Checker 2 Out-of-Tolerance Flag
#define ADC_OOTFLG_OOT3    0x4U      // Checker 3 Out-of-Tolerance Flag
#define ADC_OOTFLG_OOT4    0x8U      // Checker 4 Out-of-Tolerance Flag
#define ADC_OOTFLG_OOT5    0x10U     // Checker 5 Out-of-Tolerance Flag
#define ADC_OOTFLG_OOT6    0x20U     // Checker 6 Out-of-Tolerance Flag
#define ADC_OOTFLG_OOT7    0x40U     // Checker 7 Out-of-Tolerance Flag
#define ADC_OOTFLG_OOT8    0x80U     // Checker 8 Out-of-Tolerance Flag
#define ADC_OOTFLG_OOT9    0x100U    // Checker 9 Out-of-Tolerance Flag
#define ADC_OOTFLG_OOT10   0x200U    // Checker 10 Out-of-Tolerance Flag
#define ADC_OOTFLG_OOT11   0x400U    // Checker 11 Out-of-Tolerance Flag
#define ADC_OOTFLG_OOT12   0x800U    // Checker 12 Out-of-Tolerance Flag
#define ADC_OOTFLG_OOT13   0x1000U   // Checker 13 Out-of-Tolerance Flag
#define ADC_OOTFLG_OOT14   0x2000U   // Checker 14 Out-of-Tolerance Flag
#define ADC_OOTFLG_OOT15   0x4000U   // Checker 15 Out-of-Tolerance Flag
#define ADC_OOTFLG_OOT16   0x8000U   // Checker 16 Out-of-Tolerance Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the OOTFLGCLR register
//
//*************************************************************************************************
#define ADC_OOTFLGCLR_OOT1    0x1U      // Checker 1 OOT Flag Clear
#define ADC_OOTFLGCLR_OOT2    0x2U      // Checker 2 OOT Flag Clear
#define ADC_OOTFLGCLR_OOT3    0x4U      // Checker 3 OOT Flag Clear
#define ADC_OOTFLGCLR_OOT4    0x8U      // Checker 4 OOT Flag Clear
#define ADC_OOTFLGCLR_OOT5    0x10U     // Checker 5 OOT Flag Clear
#define ADC_OOTFLGCLR_OOT6    0x20U     // Checker 6 OOT Flag Clear
#define ADC_OOTFLGCLR_OOT7    0x40U     // Checker 7 OOT Flag Clear
#define ADC_OOTFLGCLR_OOT8    0x80U     // Checker 8 OOT Flag Clear
#define ADC_OOTFLGCLR_OOT9    0x100U    // Checker 9 OOT Flag Clear
#define ADC_OOTFLGCLR_OOT10   0x200U    // Checker 10 OOT Flag Clear
#define ADC_OOTFLGCLR_OOT11   0x400U    // Checker 11 OOT Flag Clear
#define ADC_OOTFLGCLR_OOT12   0x800U    // Checker 12 OOT Flag Clear
#define ADC_OOTFLGCLR_OOT13   0x1000U   // Checker 13 OOT Flag Clear
#define ADC_OOTFLGCLR_OOT14   0x2000U   // Checker 14 OOT Flag Clear
#define ADC_OOTFLGCLR_OOT15   0x4000U   // Checker 15 OOT Flag Clear
#define ADC_OOTFLGCLR_OOT16   0x8000U   // Checker 16 OOT Flag Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the RES1OVF register
//
//*************************************************************************************************
#define ADC_RES1OVF_RES1OVF1    0x1U      // Checker 1 Result 1 Overflow Flag
#define ADC_RES1OVF_RES1OVF2    0x2U      // Checker 2 Result 1 Overflow Flag
#define ADC_RES1OVF_RES1OVF3    0x4U      // Checker 3 Result 1 Overflow Flag
#define ADC_RES1OVF_RES1OVF4    0x8U      // Checker 4 Result 1 Overflow Flag
#define ADC_RES1OVF_RES1OVF5    0x10U     // Checker 5 Result 5 Overflow Flag
#define ADC_RES1OVF_RES1OVF6    0x20U     // Checker 6 Result 1 Overflow Flag
#define ADC_RES1OVF_RES1OVF7    0x40U     // Checker 7 Result 1 Overflow Flag
#define ADC_RES1OVF_RES1OVF8    0x80U     // Checker 8 Result 1 Overflow Flag
#define ADC_RES1OVF_RES1OVF9    0x100U    // Checker 9 Result 1 Overflow Flag
#define ADC_RES1OVF_RES1OVF10   0x200U    // Checker 10 Result 1 Overflow Flag
#define ADC_RES1OVF_RES1OVF11   0x400U    // Checker 11 Result 1 Overflow Flag
#define ADC_RES1OVF_RES1OVF12   0x800U    // Checker 12 Result 1 Overflow Flag
#define ADC_RES1OVF_RES1OVF13   0x1000U   // Checker 13 Result 5 Overflow Flag
#define ADC_RES1OVF_RES1OVF14   0x2000U   // Checker 14 Result 1 Overflow Flag
#define ADC_RES1OVF_RES1OVF15   0x4000U   // Checker 15 Result 1 Overflow Flag
#define ADC_RES1OVF_RES1OVF16   0x8000U   // Checker 16 Result 1 Overflow Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the RES1OVFCLR register
//
//*************************************************************************************************
#define ADC_RES1OVFCLR_RES1OVF1    0x1U      // Checker 1 Result 1  OVF Flag Clear
#define ADC_RES1OVFCLR_RES1OVF2    0x2U      // Checker 2 Result 1 OVF Flag Clear
#define ADC_RES1OVFCLR_RES1OVF3    0x4U      // Checker 3 Result 1 OVF Flag Clear
#define ADC_RES1OVFCLR_RES1OVF4    0x8U      // Checker 4 Result 1 OVF Flag Clear
#define ADC_RES1OVFCLR_RES1OVF5    0x10U     // Checker 5 Result 1  OVF Flag Clear
#define ADC_RES1OVFCLR_RES1OVF6    0x20U     // Checker 6 Result 1 OVF Flag Clear
#define ADC_RES1OVFCLR_RES1OVF7    0x40U     // Checker 7 Result 1 OVF Flag Clear
#define ADC_RES1OVFCLR_RES1OVF8    0x80U     // Checker 8 Result 1 OVF Flag Clear
#define ADC_RES1OVFCLR_RES1OVF9    0x100U    // Checker 9 Result 1  OVF Flag Clear
#define ADC_RES1OVFCLR_RES1OVF10   0x200U    // Checker 10 Result 1 OVF Flag Clear
#define ADC_RES1OVFCLR_RES1OVF11   0x400U    // Checker 11 Result 1 OVF Flag Clear
#define ADC_RES1OVFCLR_RES1OVF12   0x800U    // Checker 12 Result 1 OVF Flag Clear
#define ADC_RES1OVFCLR_RES1OVF13   0x1000U   // Checker 13 Result 1  OVF Flag Clear
#define ADC_RES1OVFCLR_RES1OVF14   0x2000U   // Checker 14 Result 1 OVF Flag Clear
#define ADC_RES1OVFCLR_RES1OVF15   0x4000U   // Checker 15 Result 1 OVF Flag Clear
#define ADC_RES1OVFCLR_RES1OVF16   0x8000U   // Checker 16 Result 1 OVF Flag Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the RES2OVF register
//
//*************************************************************************************************
#define ADC_RES2OVF_RES2OVF1    0x1U      // Checker 1 Result 2 Overflow Flag
#define ADC_RES2OVF_RES2OVF2    0x2U      // Checker 2 Result 2 Overflow Flag
#define ADC_RES2OVF_RES2OVF3    0x4U      // Checker 3 Result 2 Overflow Flag
#define ADC_RES2OVF_RES2OVF4    0x8U      // Checker 4 Result 2 Overflow Flag
#define ADC_RES2OVF_RES2OVF5    0x10U     // Checker 5 Result 2 Overflow Flag
#define ADC_RES2OVF_RES2OVF6    0x20U     // Checker 6 Result 2 Overflow Flag
#define ADC_RES2OVF_RES2OVF7    0x40U     // Checker 7 Result 2 Overflow Flag
#define ADC_RES2OVF_RES2OVF8    0x80U     // Checker 8 Result 2 Overflow Flag
#define ADC_RES2OVF_RES2OVF9    0x100U    // Checker 9 Result 2 Overflow Flag
#define ADC_RES2OVF_RES2OVF10   0x200U    // Checker 10 Result 2 Overflow Flag
#define ADC_RES2OVF_RES2OVF11   0x400U    // Checker 11 Result 2 Overflow Flag
#define ADC_RES2OVF_RES2OVF12   0x800U    // Checker 12 Result 2 Overflow Flag
#define ADC_RES2OVF_RES2OVF13   0x1000U   // Checker 13 Result 2 Overflow Flag
#define ADC_RES2OVF_RES2OVF14   0x2000U   // Checker 14 Result 2 Overflow Flag
#define ADC_RES2OVF_RES2OVF15   0x4000U   // Checker 15 Result 2 Overflow Flag
#define ADC_RES2OVF_RES2OVF16   0x8000U   // Checker 16 Result 2 Overflow Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the RES2OVFCLR register
//
//*************************************************************************************************
#define ADC_RES2OVFCLR_RES2OVF1    0x1U      // Checker 1 Result 2  OVF Flag Clear
#define ADC_RES2OVFCLR_RES2OVF2    0x2U      // Checker 2 Result 2 OVF Flag Clear
#define ADC_RES2OVFCLR_RES2OVF3    0x4U      // Checker 3 Result 2 OVF Flag Clear
#define ADC_RES2OVFCLR_RES2OVF4    0x8U      // Checker 4 Result 2 OVF Flag Clear
#define ADC_RES2OVFCLR_RES2OVF5    0x10U     // Checker 5 Result 2  OVF Flag Clear
#define ADC_RES2OVFCLR_RES2OVF6    0x20U     // Checker 6 Result 2 OVF Flag Clear
#define ADC_RES2OVFCLR_RES2OVF7    0x40U     // Checker 7 Result 2 OVF Flag Clear
#define ADC_RES2OVFCLR_RES2OVF8    0x80U     // Checker 8 Result 2 OVF Flag Clear
#define ADC_RES2OVFCLR_RES2OVF9    0x100U    // Checker 9 Result 2  OVF Flag Clear
#define ADC_RES2OVFCLR_RES2OVF10   0x200U    // Checker 10 Result 2 OVF Flag Clear
#define ADC_RES2OVFCLR_RES2OVF11   0x400U    // Checker 11 Result 2 OVF Flag Clear
#define ADC_RES2OVFCLR_RES2OVF12   0x800U    // Checker 12 Result 2 OVF Flag Clear
#define ADC_RES2OVFCLR_RES2OVF13   0x1000U   // Checker 13 Result 2  OVF Flag Clear
#define ADC_RES2OVFCLR_RES2OVF14   0x2000U   // Checker 14 Result 2 OVF Flag Clear
#define ADC_RES2OVFCLR_RES2OVF15   0x4000U   // Checker 15 Result 2 OVF Flag Clear
#define ADC_RES2OVFCLR_RES2OVF16   0x8000U   // Checker 16 Result 2 OVF Flag Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the CHECKINTFLG register
//
//*************************************************************************************************
#define ADC_CHECKINTFLG_CHECKINT   0x1U   // ADC Safety Checker Subsystem Interrupt Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the CHECKINTFLGCLR register
//
//*************************************************************************************************
#define ADC_CHECKINTFLGCLR_CHECKINTCLR   0x1U   // ADC Safety Checker Subsystem Interrupt Flag
                                                // Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the CHECKINTSEL1 register
//
//*************************************************************************************************
#define ADC_CHECKINTSEL1_RES1OVF1EN    0x1U      // Overflow Enable from Checker 1 Result 1
#define ADC_CHECKINTSEL1_RES1OVF2EN    0x2U      // Overflow Enable from Checker 2 Result 1
#define ADC_CHECKINTSEL1_RES1OVF3EN    0x4U      // Overflow Enable from Checker 3 Result 1
#define ADC_CHECKINTSEL1_RES1OVF4EN    0x8U      // Overflow Enable from Checker 4 Result 1
#define ADC_CHECKINTSEL1_RES1OVF5EN    0x10U     // Overflow Enable from Checker 5 Result 1
#define ADC_CHECKINTSEL1_RES1OVF6EN    0x20U     // Overflow Enable from Checker 6 Result 1
#define ADC_CHECKINTSEL1_RES1OVF7EN    0x40U     // Overflow Enable from Checker 7 Result 1
#define ADC_CHECKINTSEL1_RES1OVF8EN    0x80U     // Overflow Enable from Checker 8 Result 1
#define ADC_CHECKINTSEL1_RES1OVF9EN    0x100U    // Overflow Enable from Checker 9 Result 1
#define ADC_CHECKINTSEL1_RES1OVF10EN   0x200U    // Overflow Enable from Checker 10 Result 1
#define ADC_CHECKINTSEL1_RES1OVF11EN   0x400U    // Overflow Enable from Checker 11 Result 1
#define ADC_CHECKINTSEL1_RES1OVF12EN   0x800U    // Overflow Enable from Checker 12 Result 1
#define ADC_CHECKINTSEL1_RES1OVF13EN   0x1000U   // Overflow Enable from Checker 13 Result 1
#define ADC_CHECKINTSEL1_RES1OVF14EN   0x2000U   // Overflow Enable from Checker 14 Result 1
#define ADC_CHECKINTSEL1_RES1OVF15EN   0x4000U   // Overflow Enable from Checker 15 Result 1
#define ADC_CHECKINTSEL1_RES1OVF16EN   0x8000U   // Overflow Enable from Checker 16 Result 1

//*************************************************************************************************
//
// The following are defines for the bit fields in the CHECKINTSEL2 register
//
//*************************************************************************************************
#define ADC_CHECKINTSEL2_RES2OVF1EN    0x1U      // Overflow Enable from Checker 1 Result 2
#define ADC_CHECKINTSEL2_RES2OVF2EN    0x2U      // Overflow Enable from Checker 2 Result 2
#define ADC_CHECKINTSEL2_RES2OVF3EN    0x4U      // Overflow Enable from Checker 3 Result 2
#define ADC_CHECKINTSEL2_RES2OVF4EN    0x8U      // Overflow Enable from Checker 4 Result 2
#define ADC_CHECKINTSEL2_RES2OVF5EN    0x10U     // Overflow Enable from Checker 5 Result 2
#define ADC_CHECKINTSEL2_RES2OVF6EN    0x20U     // Overflow Enable from Checker 6 Result 2
#define ADC_CHECKINTSEL2_RES2OVF7EN    0x40U     // Overflow Enable from Checker 7 Result 2
#define ADC_CHECKINTSEL2_RES2OVF8EN    0x80U     // Overflow Enable from Checker 8 Result 2
#define ADC_CHECKINTSEL2_RES2OVF9EN    0x100U    // Overflow Enable from Checker 9 Result 2
#define ADC_CHECKINTSEL2_RES2OVF10EN   0x200U    // Overflow Enable from Checker 10 Result 2
#define ADC_CHECKINTSEL2_RES2OVF11EN   0x400U    // Overflow Enable from Checker 11 Result 2
#define ADC_CHECKINTSEL2_RES2OVF12EN   0x800U    // Overflow Enable from Checker 12 Result 2
#define ADC_CHECKINTSEL2_RES2OVF13EN   0x1000U   // Overflow Enable from Checker 13 Result 2
#define ADC_CHECKINTSEL2_RES2OVF14EN   0x2000U   // Overflow Enable from Checker 14 Result 2
#define ADC_CHECKINTSEL2_RES2OVF15EN   0x4000U   // Overflow Enable from Checker 15 Result 2
#define ADC_CHECKINTSEL2_RES2OVF16EN   0x8000U   // Overflow Enable from Checker 16 Result 2

//*************************************************************************************************
//
// The following are defines for the bit fields in the CHECKINTSEL3 register
//
//*************************************************************************************************
#define ADC_CHECKINTSEL3_OOT1EN    0x1U      // Out-of-Tolerance Enable from Checker 1
#define ADC_CHECKINTSEL3_OOT2EN    0x2U      // Out-of-Tolerance Enable from Checker 2
#define ADC_CHECKINTSEL3_OOT3EN    0x4U      // Out-of-Tolerance Enable from Checker 3
#define ADC_CHECKINTSEL3_OOT4EN    0x8U      // Out-of-Tolerance Enable from Checker 4
#define ADC_CHECKINTSEL3_OOT5EN    0x10U     // Out-of-Tolerance Enable from Checker 5
#define ADC_CHECKINTSEL3_OOT6EN    0x20U     // Out-of-Tolerance Enable from Checker 6
#define ADC_CHECKINTSEL3_OOT7EN    0x40U     // Out-of-Tolerance Enable from Checker 7
#define ADC_CHECKINTSEL3_OOT8EN    0x80U     // Out-of-Tolerance Enable from Checker 8
#define ADC_CHECKINTSEL3_OOT9EN    0x100U    // Out-of-Tolerance Enable from Checker 9
#define ADC_CHECKINTSEL3_OOT10EN   0x200U    // Out-of-Tolerance Enable from Checker 10
#define ADC_CHECKINTSEL3_OOT11EN   0x400U    // Out-of-Tolerance Enable from Checker 11
#define ADC_CHECKINTSEL3_OOT12EN   0x800U    // Out-of-Tolerance Enable from Checker 12
#define ADC_CHECKINTSEL3_OOT13EN   0x1000U   // Out-of-Tolerance Enable from Checker 13
#define ADC_CHECKINTSEL3_OOT14EN   0x2000U   // Out-of-Tolerance Enable from Checker 14
#define ADC_CHECKINTSEL3_OOT15EN   0x4000U   // Out-of-Tolerance Enable from Checker 15
#define ADC_CHECKINTSEL3_OOT16EN   0x8000U   // Out-of-Tolerance Enable from Checker 16

//*************************************************************************************************
//
// The following are defines for the bit fields in the CHECKEVT1SEL1 register
//
//*************************************************************************************************
#define ADC_CHECKEVT1SEL1_RES1OVF1EN    0x1U      // Overflow Enable from Checker 1 Result 1
#define ADC_CHECKEVT1SEL1_RES1OVF2EN    0x2U      // Overflow Enable from Checker 2 Result 1
#define ADC_CHECKEVT1SEL1_RES1OVF3EN    0x4U      // Overflow Enable from Checker 3 Result 1
#define ADC_CHECKEVT1SEL1_RES1OVF4EN    0x8U      // Overflow Enable from Checker 4 Result 1
#define ADC_CHECKEVT1SEL1_RES1OVF5EN    0x10U     // Overflow Enable from Checker 5 Result 1
#define ADC_CHECKEVT1SEL1_RES1OVF6EN    0x20U     // Overflow Enable from Checker 6 Result 1
#define ADC_CHECKEVT1SEL1_RES1OVF7EN    0x40U     // Overflow Enable from Checker 7 Result 1
#define ADC_CHECKEVT1SEL1_RES1OVF8EN    0x80U     // Overflow Enable from Checker 8 Result 1
#define ADC_CHECKEVT1SEL1_RES1OVF9EN    0x100U    // Overflow Enable from Checker 9 Result 1
#define ADC_CHECKEVT1SEL1_RES1OVF10EN   0x200U    // Overflow Enable from Checker 10 Result 1
#define ADC_CHECKEVT1SEL1_RES1OVF11EN   0x400U    // Overflow Enable from Checker 11 Result 1
#define ADC_CHECKEVT1SEL1_RES1OVF12EN   0x800U    // Overflow Enable from Checker 12 Result 1
#define ADC_CHECKEVT1SEL1_RES1OVF13EN   0x1000U   // Overflow Enable from Checker 13 Result 1
#define ADC_CHECKEVT1SEL1_RES1OVF14EN   0x2000U   // Overflow Enable from Checker 14 Result 1
#define ADC_CHECKEVT1SEL1_RES1OVF15EN   0x4000U   // Overflow Enable from Checker 15 Result 1
#define ADC_CHECKEVT1SEL1_RES1OVF16EN   0x8000U   // Overflow Enable from Checker 16 Result 1

//*************************************************************************************************
//
// The following are defines for the bit fields in the CHECKEVT1SEL2 register
//
//*************************************************************************************************
#define ADC_CHECKEVT1SEL2_RES2OVF1EN    0x1U      // Overflow Enable from Checker 1 Result 2
#define ADC_CHECKEVT1SEL2_RES2OVF2EN    0x2U      // Overflow Enable from Checker 2 Result 2
#define ADC_CHECKEVT1SEL2_RES2OVF3EN    0x4U      // Overflow Enable from Checker 3 Result 2
#define ADC_CHECKEVT1SEL2_RES2OVF4EN    0x8U      // Overflow Enable from Checker 4 Result 2
#define ADC_CHECKEVT1SEL2_RES2OVF5EN    0x10U     // Overflow Enable from Checker 5 Result 2
#define ADC_CHECKEVT1SEL2_RES2OVF6EN    0x20U     // Overflow Enable from Checker 6 Result 2
#define ADC_CHECKEVT1SEL2_RES2OVF7EN    0x40U     // Overflow Enable from Checker 7 Result 2
#define ADC_CHECKEVT1SEL2_RES2OVF8EN    0x80U     // Overflow Enable from Checker 8 Result 2
#define ADC_CHECKEVT1SEL2_RES2OVF9EN    0x100U    // Overflow Enable from Checker 9 Result 2
#define ADC_CHECKEVT1SEL2_RES2OVF10EN   0x200U    // Overflow Enable from Checker 10 Result 2
#define ADC_CHECKEVT1SEL2_RES2OVF11EN   0x400U    // Overflow Enable from Checker 11 Result 2
#define ADC_CHECKEVT1SEL2_RES2OVF12EN   0x800U    // Overflow Enable from Checker 12 Result 2
#define ADC_CHECKEVT1SEL2_RES2OVF13EN   0x1000U   // Overflow Enable from Checker 13 Result 2
#define ADC_CHECKEVT1SEL2_RES2OVF14EN   0x2000U   // Overflow Enable from Checker 14 Result 2
#define ADC_CHECKEVT1SEL2_RES2OVF15EN   0x4000U   // Overflow Enable from Checker 15 Result 2
#define ADC_CHECKEVT1SEL2_RES2OVF16EN   0x8000U   // Overflow Enable from Checker 16 Result 2

//*************************************************************************************************
//
// The following are defines for the bit fields in the CHECKEVT1SEL3 register
//
//*************************************************************************************************
#define ADC_CHECKEVT1SEL3_OOT1EN    0x1U      // Out-of-Tolerance Enable from Checker 1
#define ADC_CHECKEVT1SEL3_OOT2EN    0x2U      // Out-of-Tolerance Enable from Checker 2
#define ADC_CHECKEVT1SEL3_OOT3EN    0x4U      // Out-of-Tolerance Enable from Checker 3
#define ADC_CHECKEVT1SEL3_OOT4EN    0x8U      // Out-of-Tolerance Enable from Checker 4
#define ADC_CHECKEVT1SEL3_OOT5EN    0x10U     // Out-of-Tolerance Enable from Checker 5
#define ADC_CHECKEVT1SEL3_OOT6EN    0x20U     // Out-of-Tolerance Enable from Checker 6
#define ADC_CHECKEVT1SEL3_OOT7EN    0x40U     // Out-of-Tolerance Enable from Checker 7
#define ADC_CHECKEVT1SEL3_OOT8EN    0x80U     // Out-of-Tolerance Enable from Checker 8
#define ADC_CHECKEVT1SEL3_OOT9EN    0x100U    // Out-of-Tolerance Enable from Checker 9
#define ADC_CHECKEVT1SEL3_OOT10EN   0x200U    // Out-of-Tolerance Enable from Checker 10
#define ADC_CHECKEVT1SEL3_OOT11EN   0x400U    // Out-of-Tolerance Enable from Checker 11
#define ADC_CHECKEVT1SEL3_OOT12EN   0x800U    // Out-of-Tolerance Enable from Checker 12
#define ADC_CHECKEVT1SEL3_OOT13EN   0x1000U   // Out-of-Tolerance Enable from Checker 13
#define ADC_CHECKEVT1SEL3_OOT14EN   0x2000U   // Out-of-Tolerance Enable from Checker 14
#define ADC_CHECKEVT1SEL3_OOT15EN   0x4000U   // Out-of-Tolerance Enable from Checker 15
#define ADC_CHECKEVT1SEL3_OOT16EN   0x8000U   // Out-of-Tolerance Enable from Checker 16

//*************************************************************************************************
//
// The following are defines for the bit fields in the CHECKEVT2SEL1 register
//
//*************************************************************************************************
#define ADC_CHECKEVT2SEL1_RES1OVF1EN    0x1U      // Overflow Enable from Checker 1 Result 1
#define ADC_CHECKEVT2SEL1_RES1OVF2EN    0x2U      // Overflow Enable from Checker 2 Result 1
#define ADC_CHECKEVT2SEL1_RES1OVF3EN    0x4U      // Overflow Enable from Checker 3 Result 1
#define ADC_CHECKEVT2SEL1_RES1OVF4EN    0x8U      // Overflow Enable from Checker 4 Result 1
#define ADC_CHECKEVT2SEL1_RES1OVF5EN    0x10U     // Overflow Enable from Checker 5 Result 1
#define ADC_CHECKEVT2SEL1_RES1OVF6EN    0x20U     // Overflow Enable from Checker 6 Result 1
#define ADC_CHECKEVT2SEL1_RES1OVF7EN    0x40U     // Overflow Enable from Checker 7 Result 1
#define ADC_CHECKEVT2SEL1_RES1OVF8EN    0x80U     // Overflow Enable from Checker 8 Result 1
#define ADC_CHECKEVT2SEL1_RES1OVF9EN    0x100U    // Overflow Enable from Checker 9 Result 1
#define ADC_CHECKEVT2SEL1_RES1OVF10EN   0x200U    // Overflow Enable from Checker 10 Result 1
#define ADC_CHECKEVT2SEL1_RES1OVF11EN   0x400U    // Overflow Enable from Checker 11 Result 1
#define ADC_CHECKEVT2SEL1_RES1OVF12EN   0x800U    // Overflow Enable from Checker 12 Result 1
#define ADC_CHECKEVT2SEL1_RES1OVF13EN   0x1000U   // Overflow Enable from Checker 13 Result 1
#define ADC_CHECKEVT2SEL1_RES1OVF14EN   0x2000U   // Overflow Enable from Checker 14 Result 1
#define ADC_CHECKEVT2SEL1_RES1OVF15EN   0x4000U   // Overflow Enable from Checker 15 Result 1
#define ADC_CHECKEVT2SEL1_RES1OVF16EN   0x8000U   // Overflow Enable from Checker 16 Result 1

//*************************************************************************************************
//
// The following are defines for the bit fields in the CHECKEVT2SEL2 register
//
//*************************************************************************************************
#define ADC_CHECKEVT2SEL2_RES2OVF1EN    0x1U      // Overflow Enable from Checker 1 Result 2
#define ADC_CHECKEVT2SEL2_RES2OVF2EN    0x2U      // Overflow Enable from Checker 2 Result 2
#define ADC_CHECKEVT2SEL2_RES2OVF3EN    0x4U      // Overflow Enable from Checker 3 Result 2
#define ADC_CHECKEVT2SEL2_RES2OVF4EN    0x8U      // Overflow Enable from Checker 4 Result 2
#define ADC_CHECKEVT2SEL2_RES2OVF5EN    0x10U     // Overflow Enable from Checker 5 Result 2
#define ADC_CHECKEVT2SEL2_RES2OVF6EN    0x20U     // Overflow Enable from Checker 6 Result 2
#define ADC_CHECKEVT2SEL2_RES2OVF7EN    0x40U     // Overflow Enable from Checker 7 Result 2
#define ADC_CHECKEVT2SEL2_RES2OVF8EN    0x80U     // Overflow Enable from Checker 8 Result 2
#define ADC_CHECKEVT2SEL2_RES2OVF9EN    0x100U    // Overflow Enable from Checker 9 Result 2
#define ADC_CHECKEVT2SEL2_RES2OVF10EN   0x200U    // Overflow Enable from Checker 10 Result 2
#define ADC_CHECKEVT2SEL2_RES2OVF11EN   0x400U    // Overflow Enable from Checker 11 Result 2
#define ADC_CHECKEVT2SEL2_RES2OVF12EN   0x800U    // Overflow Enable from Checker 12 Result 2
#define ADC_CHECKEVT2SEL2_RES2OVF13EN   0x1000U   // Overflow Enable from Checker 13 Result 2
#define ADC_CHECKEVT2SEL2_RES2OVF14EN   0x2000U   // Overflow Enable from Checker 14 Result 2
#define ADC_CHECKEVT2SEL2_RES2OVF15EN   0x4000U   // Overflow Enable from Checker 15 Result 2
#define ADC_CHECKEVT2SEL2_RES2OVF16EN   0x8000U   // Overflow Enable from Checker 16 Result 2

//*************************************************************************************************
//
// The following are defines for the bit fields in the CHECKEVT2SEL3 register
//
//*************************************************************************************************
#define ADC_CHECKEVT2SEL3_OOT1EN    0x1U      // Out-of-Tolerance Enable from Checker 1
#define ADC_CHECKEVT2SEL3_OOT2EN    0x2U      // Out-of-Tolerance Enable from Checker 2
#define ADC_CHECKEVT2SEL3_OOT3EN    0x4U      // Out-of-Tolerance Enable from Checker 3
#define ADC_CHECKEVT2SEL3_OOT4EN    0x8U      // Out-of-Tolerance Enable from Checker 4
#define ADC_CHECKEVT2SEL3_OOT5EN    0x10U     // Out-of-Tolerance Enable from Checker 5
#define ADC_CHECKEVT2SEL3_OOT6EN    0x20U     // Out-of-Tolerance Enable from Checker 6
#define ADC_CHECKEVT2SEL3_OOT7EN    0x40U     // Out-of-Tolerance Enable from Checker 7
#define ADC_CHECKEVT2SEL3_OOT8EN    0x80U     // Out-of-Tolerance Enable from Checker 8
#define ADC_CHECKEVT2SEL3_OOT9EN    0x100U    // Out-of-Tolerance Enable from Checker 9
#define ADC_CHECKEVT2SEL3_OOT10EN   0x200U    // Out-of-Tolerance Enable from Checker 10
#define ADC_CHECKEVT2SEL3_OOT11EN   0x400U    // Out-of-Tolerance Enable from Checker 11
#define ADC_CHECKEVT2SEL3_OOT12EN   0x800U    // Out-of-Tolerance Enable from Checker 12
#define ADC_CHECKEVT2SEL3_OOT13EN   0x1000U   // Out-of-Tolerance Enable from Checker 13
#define ADC_CHECKEVT2SEL3_OOT14EN   0x2000U   // Out-of-Tolerance Enable from Checker 14
#define ADC_CHECKEVT2SEL3_OOT15EN   0x4000U   // Out-of-Tolerance Enable from Checker 15
#define ADC_CHECKEVT2SEL3_OOT16EN   0x8000U   // Out-of-Tolerance Enable from Checker 16

//*************************************************************************************************
//
// The following are defines for the bit fields in the CHECKEVT3SEL1 register
//
//*************************************************************************************************
#define ADC_CHECKEVT3SEL1_RES1OVF1EN    0x1U      // Overflow Enable from Checker 1 Result 1
#define ADC_CHECKEVT3SEL1_RES1OVF2EN    0x2U      // Overflow Enable from Checker 2 Result 1
#define ADC_CHECKEVT3SEL1_RES1OVF3EN    0x4U      // Overflow Enable from Checker 3 Result 1
#define ADC_CHECKEVT3SEL1_RES1OVF4EN    0x8U      // Overflow Enable from Checker 4 Result 1
#define ADC_CHECKEVT3SEL1_RES1OVF5EN    0x10U     // Overflow Enable from Checker 5 Result 1
#define ADC_CHECKEVT3SEL1_RES1OVF6EN    0x20U     // Overflow Enable from Checker 6 Result 1
#define ADC_CHECKEVT3SEL1_RES1OVF7EN    0x40U     // Overflow Enable from Checker 7 Result 1
#define ADC_CHECKEVT3SEL1_RES1OVF8EN    0x80U     // Overflow Enable from Checker 8 Result 1
#define ADC_CHECKEVT3SEL1_RES1OVF9EN    0x100U    // Overflow Enable from Checker 9 Result 1
#define ADC_CHECKEVT3SEL1_RES1OVF10EN   0x200U    // Overflow Enable from Checker 10 Result 1
#define ADC_CHECKEVT3SEL1_RES1OVF11EN   0x400U    // Overflow Enable from Checker 11 Result 1
#define ADC_CHECKEVT3SEL1_RES1OVF12EN   0x800U    // Overflow Enable from Checker 12 Result 1
#define ADC_CHECKEVT3SEL1_RES1OVF13EN   0x1000U   // Overflow Enable from Checker 13 Result 1
#define ADC_CHECKEVT3SEL1_RES1OVF14EN   0x2000U   // Overflow Enable from Checker 14 Result 1
#define ADC_CHECKEVT3SEL1_RES1OVF15EN   0x4000U   // Overflow Enable from Checker 15 Result 1
#define ADC_CHECKEVT3SEL1_RES1OVF16EN   0x8000U   // Overflow Enable from Checker 16 Result 1

//*************************************************************************************************
//
// The following are defines for the bit fields in the CHECKEVT3SEL2 register
//
//*************************************************************************************************
#define ADC_CHECKEVT3SEL2_RES2OVF1EN    0x1U      // Overflow Enable from Checker 1 Result 2
#define ADC_CHECKEVT3SEL2_RES2OVF2EN    0x2U      // Overflow Enable from Checker 2 Result 2
#define ADC_CHECKEVT3SEL2_RES2OVF3EN    0x4U      // Overflow Enable from Checker 3 Result 2
#define ADC_CHECKEVT3SEL2_RES2OVF4EN    0x8U      // Overflow Enable from Checker 4 Result 2
#define ADC_CHECKEVT3SEL2_RES2OVF5EN    0x10U     // Overflow Enable from Checker 5 Result 2
#define ADC_CHECKEVT3SEL2_RES2OVF6EN    0x20U     // Overflow Enable from Checker 6 Result 2
#define ADC_CHECKEVT3SEL2_RES2OVF7EN    0x40U     // Overflow Enable from Checker 7 Result 2
#define ADC_CHECKEVT3SEL2_RES2OVF8EN    0x80U     // Overflow Enable from Checker 8 Result 2
#define ADC_CHECKEVT3SEL2_RES2OVF9EN    0x100U    // Overflow Enable from Checker 9 Result 2
#define ADC_CHECKEVT3SEL2_RES2OVF10EN   0x200U    // Overflow Enable from Checker 10 Result 2
#define ADC_CHECKEVT3SEL2_RES2OVF11EN   0x400U    // Overflow Enable from Checker 11 Result 2
#define ADC_CHECKEVT3SEL2_RES2OVF12EN   0x800U    // Overflow Enable from Checker 12 Result 2
#define ADC_CHECKEVT3SEL2_RES2OVF13EN   0x1000U   // Overflow Enable from Checker 13 Result 2
#define ADC_CHECKEVT3SEL2_RES2OVF14EN   0x2000U   // Overflow Enable from Checker 14 Result 2
#define ADC_CHECKEVT3SEL2_RES2OVF15EN   0x4000U   // Overflow Enable from Checker 15 Result 2
#define ADC_CHECKEVT3SEL2_RES2OVF16EN   0x8000U   // Overflow Enable from Checker 16 Result 2

//*************************************************************************************************
//
// The following are defines for the bit fields in the CHECKEVT3SEL3 register
//
//*************************************************************************************************
#define ADC_CHECKEVT3SEL3_OOT1EN    0x1U      // Out-of-Tolerance Enable from Checker 1
#define ADC_CHECKEVT3SEL3_OOT2EN    0x2U      // Out-of-Tolerance Enable from Checker 2
#define ADC_CHECKEVT3SEL3_OOT3EN    0x4U      // Out-of-Tolerance Enable from Checker 3
#define ADC_CHECKEVT3SEL3_OOT4EN    0x8U      // Out-of-Tolerance Enable from Checker 4
#define ADC_CHECKEVT3SEL3_OOT5EN    0x10U     // Out-of-Tolerance Enable from Checker 5
#define ADC_CHECKEVT3SEL3_OOT6EN    0x20U     // Out-of-Tolerance Enable from Checker 6
#define ADC_CHECKEVT3SEL3_OOT7EN    0x40U     // Out-of-Tolerance Enable from Checker 7
#define ADC_CHECKEVT3SEL3_OOT8EN    0x80U     // Out-of-Tolerance Enable from Checker 8
#define ADC_CHECKEVT3SEL3_OOT9EN    0x100U    // Out-of-Tolerance Enable from Checker 9
#define ADC_CHECKEVT3SEL3_OOT10EN   0x200U    // Out-of-Tolerance Enable from Checker 10
#define ADC_CHECKEVT3SEL3_OOT11EN   0x400U    // Out-of-Tolerance Enable from Checker 11
#define ADC_CHECKEVT3SEL3_OOT12EN   0x800U    // Out-of-Tolerance Enable from Checker 12
#define ADC_CHECKEVT3SEL3_OOT13EN   0x1000U   // Out-of-Tolerance Enable from Checker 13
#define ADC_CHECKEVT3SEL3_OOT14EN   0x2000U   // Out-of-Tolerance Enable from Checker 14
#define ADC_CHECKEVT3SEL3_OOT15EN   0x4000U   // Out-of-Tolerance Enable from Checker 15
#define ADC_CHECKEVT3SEL3_OOT16EN   0x8000U   // Out-of-Tolerance Enable from Checker 16

//*************************************************************************************************
//
// The following are defines for the bit fields in the CHECKEVT4SEL1 register
//
//*************************************************************************************************
#define ADC_CHECKEVT4SEL1_RES1OVF1EN    0x1U      // Overflow Enable from Checker 1 Result 1
#define ADC_CHECKEVT4SEL1_RES1OVF2EN    0x2U      // Overflow Enable from Checker 2 Result 1
#define ADC_CHECKEVT4SEL1_RES1OVF3EN    0x4U      // Overflow Enable from Checker 3 Result 1
#define ADC_CHECKEVT4SEL1_RES1OVF4EN    0x8U      // Overflow Enable from Checker 4 Result 1
#define ADC_CHECKEVT4SEL1_RES1OVF5EN    0x10U     // Overflow Enable from Checker 5 Result 1
#define ADC_CHECKEVT4SEL1_RES1OVF6EN    0x20U     // Overflow Enable from Checker 6 Result 1
#define ADC_CHECKEVT4SEL1_RES1OVF7EN    0x40U     // Overflow Enable from Checker 7 Result 1
#define ADC_CHECKEVT4SEL1_RES1OVF8EN    0x80U     // Overflow Enable from Checker 8 Result 1
#define ADC_CHECKEVT4SEL1_RES1OVF9EN    0x100U    // Overflow Enable from Checker 9 Result 1
#define ADC_CHECKEVT4SEL1_RES1OVF10EN   0x200U    // Overflow Enable from Checker 10 Result 1
#define ADC_CHECKEVT4SEL1_RES1OVF11EN   0x400U    // Overflow Enable from Checker 11 Result 1
#define ADC_CHECKEVT4SEL1_RES1OVF12EN   0x800U    // Overflow Enable from Checker 12 Result 1
#define ADC_CHECKEVT4SEL1_RES1OVF13EN   0x1000U   // Overflow Enable from Checker 13 Result 1
#define ADC_CHECKEVT4SEL1_RES1OVF14EN   0x2000U   // Overflow Enable from Checker 14 Result 1
#define ADC_CHECKEVT4SEL1_RES1OVF15EN   0x4000U   // Overflow Enable from Checker 15 Result 1
#define ADC_CHECKEVT4SEL1_RES1OVF16EN   0x8000U   // Overflow Enable from Checker 16 Result 1

//*************************************************************************************************
//
// The following are defines for the bit fields in the CHECKEVT4SEL2 register
//
//*************************************************************************************************
#define ADC_CHECKEVT4SEL2_RES2OVF1EN    0x1U      // Overflow Enable from Checker 1 Result 2
#define ADC_CHECKEVT4SEL2_RES2OVF2EN    0x2U      // Overflow Enable from Checker 2 Result 2
#define ADC_CHECKEVT4SEL2_RES2OVF3EN    0x4U      // Overflow Enable from Checker 3 Result 2
#define ADC_CHECKEVT4SEL2_RES2OVF4EN    0x8U      // Overflow Enable from Checker 4 Result 2
#define ADC_CHECKEVT4SEL2_RES2OVF5EN    0x10U     // Overflow Enable from Checker 5 Result 2
#define ADC_CHECKEVT4SEL2_RES2OVF6EN    0x20U     // Overflow Enable from Checker 6 Result 2
#define ADC_CHECKEVT4SEL2_RES2OVF7EN    0x40U     // Overflow Enable from Checker 7 Result 2
#define ADC_CHECKEVT4SEL2_RES2OVF8EN    0x80U     // Overflow Enable from Checker 8 Result 2
#define ADC_CHECKEVT4SEL2_RES2OVF9EN    0x100U    // Overflow Enable from Checker 9 Result 2
#define ADC_CHECKEVT4SEL2_RES2OVF10EN   0x200U    // Overflow Enable from Checker 10 Result 2
#define ADC_CHECKEVT4SEL2_RES2OVF11EN   0x400U    // Overflow Enable from Checker 11 Result 2
#define ADC_CHECKEVT4SEL2_RES2OVF12EN   0x800U    // Overflow Enable from Checker 12 Result 2
#define ADC_CHECKEVT4SEL2_RES2OVF13EN   0x1000U   // Overflow Enable from Checker 13 Result 2
#define ADC_CHECKEVT4SEL2_RES2OVF14EN   0x2000U   // Overflow Enable from Checker 14 Result 2
#define ADC_CHECKEVT4SEL2_RES2OVF15EN   0x4000U   // Overflow Enable from Checker 15 Result 2
#define ADC_CHECKEVT4SEL2_RES2OVF16EN   0x8000U   // Overflow Enable from Checker 16 Result 2

//*************************************************************************************************
//
// The following are defines for the bit fields in the CHECKEVT4SEL3 register
//
//*************************************************************************************************
#define ADC_CHECKEVT4SEL3_OOT1EN    0x1U      // Out-of-Tolerance Enable from Checker 1
#define ADC_CHECKEVT4SEL3_OOT2EN    0x2U      // Out-of-Tolerance Enable from Checker 2
#define ADC_CHECKEVT4SEL3_OOT3EN    0x4U      // Out-of-Tolerance Enable from Checker 3
#define ADC_CHECKEVT4SEL3_OOT4EN    0x8U      // Out-of-Tolerance Enable from Checker 4
#define ADC_CHECKEVT4SEL3_OOT5EN    0x10U     // Out-of-Tolerance Enable from Checker 5
#define ADC_CHECKEVT4SEL3_OOT6EN    0x20U     // Out-of-Tolerance Enable from Checker 6
#define ADC_CHECKEVT4SEL3_OOT7EN    0x40U     // Out-of-Tolerance Enable from Checker 7
#define ADC_CHECKEVT4SEL3_OOT8EN    0x80U     // Out-of-Tolerance Enable from Checker 8
#define ADC_CHECKEVT4SEL3_OOT9EN    0x100U    // Out-of-Tolerance Enable from Checker 9
#define ADC_CHECKEVT4SEL3_OOT10EN   0x200U    // Out-of-Tolerance Enable from Checker 10
#define ADC_CHECKEVT4SEL3_OOT11EN   0x400U    // Out-of-Tolerance Enable from Checker 11
#define ADC_CHECKEVT4SEL3_OOT12EN   0x800U    // Out-of-Tolerance Enable from Checker 12
#define ADC_CHECKEVT4SEL3_OOT13EN   0x1000U   // Out-of-Tolerance Enable from Checker 13
#define ADC_CHECKEVT4SEL3_OOT14EN   0x2000U   // Out-of-Tolerance Enable from Checker 14
#define ADC_CHECKEVT4SEL3_OOT15EN   0x4000U   // Out-of-Tolerance Enable from Checker 15
#define ADC_CHECKEVT4SEL3_OOT16EN   0x8000U   // Out-of-Tolerance Enable from Checker 16



#endif
