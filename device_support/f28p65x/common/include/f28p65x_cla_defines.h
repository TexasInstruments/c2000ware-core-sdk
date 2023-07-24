//###########################################################################
//
// FILE:   f28p65x_cla_defines.h
//
// TITLE:  #defines used in CLA examples
//
//###########################################################################
//
//
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

#ifndef F28P65X_CLA_DEFINES_H
#define F28P65X_CLA_DEFINES_H

#ifdef __cplusplus
extern "C" {
#endif

//
// Defines
//

//
// MCTL Register
//
#define CLA_FORCE_RESET           0x1
#define CLA_IACK_ENABLE           0x1
#define CLA_IACK_DISABLE          0x0

//
// MMEMCFG Register
//
#define CLA_CLA_SPACE             0x1
#define CLA_CPU_SPACE             0x0

//
// MIER Interrupt Enable Register
//
#define CLA_INT_ENABLE            0x1
#define CLA_INT_DISABLE           0x0

//
// Peripheral Interrupt Source Select define for DMAnCLASourceSelect Register
//
#define CLA_TRIG_NOPERPH	 0
#define CLA_TRIG_ADCAINT1    1
#define CLA_TRIG_ADCAINT2    2
#define CLA_TRIG_ADCAINT3    3
#define CLA_TRIG_ADCAINT4    4
#define CLA_TRIG_ADCAEVT     5
#define CLA_TRIG_ADCBINT1    6
#define CLA_TRIG_ADCBINT2    7
#define CLA_TRIG_ADCBINT3    8
#define CLA_TRIG_ADCBINT4    9
#define CLA_TRIG_ADCBEVT     10
#define CLA_TRIG_ADCCINT1    11
#define CLA_TRIG_ADCCINT2    12
#define CLA_TRIG_ADCCINT3    13
#define CLA_TRIG_ADCCINT4    14
#define CLA_TRIG_ADCCEVT     15

#define CLA_TRIG_XINT1   	29
#define CLA_TRIG_XINT2   	30
#define CLA_TRIG_XINT3   	31
#define CLA_TRIG_XINT4   	32
#define CLA_TRIG_XINT5   	33

#define CLA_TRIG_EPWM1INT  	36
#define CLA_TRIG_EPWM2INT  	37
#define CLA_TRIG_EPWM3INT  	38
#define CLA_TRIG_EPWM4INT  	39
#define CLA_TRIG_EPWM5INT  	40
#define CLA_TRIG_EPWM6INT  	41
#define CLA_TRIG_EPWM7INT  	42
#define CLA_TRIG_EPWM8INT  	43
#define CLA_TRIG_EPWM9INT  	44
#define CLA_TRIG_EPWM10INT  45
#define CLA_TRIG_EPWM11INT  46
#define CLA_TRIG_EPWM12INT  47
#define CLA_TRIG_EPWM13INT  48
#define CLA_TRIG_EPWM14INT  49
#define CLA_TRIG_EPWM15INT  50
#define CLA_TRIG_EPWM16INT  51

#define CLA_TRIG_MCANA_FEVT0  52
#define CLA_TRIG_MCANA_FEVT1  53
#define CLA_TRIG_MCANA_FEVT2  54
#define CLA_TRIG_MCANB_FEVT0  55
#define CLA_TRIG_MCANB_FEVT1  56
#define CLA_TRIG_MCANB_FEVT2  57

#define CLA_TRIG_EPWM17INT  58
#define CLA_TRIG_EPWM18INT  59

#define CLA_TRIG_TINT0   	68
#define CLA_TRIG_TINT1   	69
#define CLA_TRIG_TINT2   	70

#define CLA_TRIG_ECAP1INT   75
#define CLA_TRIG_ECAP2INT   76
#define CLA_TRIG_ECAP3INT   77
#define CLA_TRIG_ECAP4INT   78
#define CLA_TRIG_ECAP5INT   79
#define CLA_TRIG_ECAP6INT   80
#define CLA_TRIG_ECAP7INT   81

#define CLA_TRIG_EQEP1INT 	83
#define CLA_TRIG_EQEP2INT   84
#define CLA_TRIG_EQEP3INT   85
#define CLA_TRIG_EQEP4INT 	86
#define CLA_TRIG_EQEP5INT   87
#define CLA_TRIG_EQEP6INT   88

#define CLA_TRIG_ECAP6INT2  92
#define CLA_TRIG_ECAP7INT2  93

#define CLA_TRIG_SD1INT		95
#define CLA_TRIG_SD2INT     96
#define CLA_TRIG_SD3INT     97
#define CLA_TRIG_SD4INT     98

#define CLA_TRIG_LINA1      99
#define CLA_TRIG_LINA0      100
#define CLA_TRIG_LINB1      101
#define CLA_TRIG_LINB0      102

#define CLA_TRIG_SPITXINTA  109
#define CLA_TRIG_SPIRXINTA	110
#define CLA_TRIG_SPITXINTB	111
#define CLA_TRIG_SPIRXINTB	112
#define CLA_TRIG_SPITXINTC	113
#define CLA_TRIG_SPIRXINTC	114
#define CLA_TRIG_SPITXINTD	115
#define CLA_TRIG_SPIRXINTD	116

#define CLA_TRIG_CLB5INT    117
#define CLA_TRIG_CLB6INT    118

#define CLA_TRIG_CLA1CRC   	121

#define CLA_TRIG_FSITXA_INT1   	123
#define CLA_TRIG_FSITXA_INT2   	124
#define CLA_TRIG_FSIRXA_INT1   	125
#define CLA_TRIG_FSIRXA_INT2   	126

#define CLA_TRIG_CLB1INT    127
#define CLA_TRIG_CLB2INT    128
#define CLA_TRIG_CLB3INT    129
#define CLA_TRIG_CLB4INT    130

#define CLA_TRIG_SD1DRINT1	143
#define CLA_TRIG_SD1DRINT2	144
#define CLA_TRIG_SD1DRINT3	145
#define CLA_TRIG_SD1DRINT4	146
#define CLA_TRIG_SD2DRINT1	147
#define CLA_TRIG_SD2DRINT2	148
#define CLA_TRIG_SD2DRINT3	149
#define CLA_TRIG_SD2DRINT4	150
#define CLA_TRIG_SD3DRINT1	151
#define CLA_TRIG_SD3DRINT2	152
#define CLA_TRIG_SD3DRINT3	153
#define CLA_TRIG_SD3DRINT4	154

#define CLA_TRIG_FSITXB_INT1   	155
#define CLA_TRIG_FSITXB_INT2   	156
#define CLA_TRIG_FSIRXB_INT1   	157
#define CLA_TRIG_FSIRXB_INT2   	158
#define CLA_TRIG_FSIRXC_INT1   	159
#define CLA_TRIG_FSIRXC_INT2   	160
#define CLA_TRIG_FSIRXD_INT1   	161
#define CLA_TRIG_FSIRXD_INT2   	162

#define CLA_TRIG_DMACH1 	184
#define CLA_TRIG_DMACH2 	185
#define CLA_TRIG_DMACH3 	186
#define CLA_TRIG_DMACH4 	187
#define CLA_TRIG_DMACH5 	188
#define CLA_TRIG_DMACH6 	189

#define CLA_TRIG_SD4DRINT1	202
#define CLA_TRIG_SD4DRINT2	203
#define CLA_TRIG_SD4DRINT3	204
#define CLA_TRIG_SD4DRINT4	205

#define Cla1ForceTask1andWait()asm("  IACK  #0x0001");             \
                               asm("  RPT #3 || NOP");             \
                                while(Cla1Regs.MIRUN.bit.INT1 == 1);

#define Cla1ForceTask2andWait()asm("  IACK  #0x0002");             \
                               asm("  RPT #3 || NOP");             \
                                while(Cla1Regs.MIRUN.bit.INT2 == 1);

#define Cla1ForceTask3andWait()asm("  IACK  #0x0004");             \
                               asm("  RPT #3 || NOP");             \
                                while(Cla1Regs.MIRUN.bit.INT3 == 1);

#define Cla1ForceTask4andWait()asm("  IACK  #0x0008");             \
                               asm("  RPT #3 || NOP");             \
                                while(Cla1Regs.MIRUN.bit.INT4 == 1);

#define Cla1ForceTask5andWait()asm("  IACK  #0x0010");             \
                               asm("  RPT #3 || NOP");             \
                                while(Cla1Regs.MIRUN.bit.INT5 == 1);

#define Cla1ForceTask6andWait()asm("  IACK  #0x0020");             \
                               asm("  RPT #3 || NOP");             \
                                while(Cla1Regs.MIRUN.bit.INT6 == 1);

#define Cla1ForceTask7andWait()asm("  IACK  #0x0040");             \
                               asm("  RPT #3 || NOP");             \
                                while(Cla1Regs.MIRUN.bit.INT7 == 1);

#define Cla1ForceTask8andWait()asm("  IACK  #0x0080");             \
                               asm("  RPT #3 || NOP");             \
                                while(Cla1Regs.MIRUN.bit.INT8 == 1);

#define Cla1ForceTask1()       asm("  IACK  #0x0001")
#define Cla1ForceTask2()       asm("  IACK  #0x0002")
#define Cla1ForceTask3()       asm("  IACK  #0x0004")
#define Cla1ForceTask4()       asm("  IACK  #0x0008")
#define Cla1ForceTask5()       asm("  IACK  #0x0010")
#define Cla1ForceTask6()       asm("  IACK  #0x0020")
#define Cla1ForceTask7()       asm("  IACK  #0x0040")
#define Cla1ForceTask8()       asm("  IACK  #0x0080")

#ifdef __cplusplus
}
#endif

#endif   // - end of F28P65X_CLA_DEFINES_H

//
// End of file
//
