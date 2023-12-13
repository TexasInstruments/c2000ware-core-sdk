//###########################################################################
//
// FILE:    hw_asysctl.h
//
// TITLE:   Definitions for the ASYSCTL registers.
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

#ifndef HW_ASYSCTL_H
#define HW_ASYSCTL_H

//*************************************************************************************************
//
// The following are defines for the ASYSCTL register offsets
//
//*************************************************************************************************
#define ASYSCTL_O_INTERNALTESTCTL   0x4AU    // INTERNALTEST Node Control Register
#define ASYSCTL_O_CONFIGLOCK        0x5EU    // Lock Register for all the config registers.
#define ASYSCTL_O_TSNSCTL           0x60U    // Temperature Sensor Control Register
#define ASYSCTL_O_ANAREFCTL         0x68U    // Analog Reference Control Register.
#define ASYSCTL_O_VMONCTL           0x70U    // Voltage Monitor Control Register
#define ASYSCTL_O_CMPHPMXSEL        0x82U    // Bits to select one of the many sources on CopmHP
                                             // inputs. Refer to Pimux diagram for details.
#define ASYSCTL_O_CMPLPMXSEL        0x84U    // Bits to select one of the many sources on CopmLP
                                             // inputs. Refer to Pimux diagram for details.
#define ASYSCTL_O_CMPHNMXSEL        0x86U    // Bits to select one of the many sources on CopmHN
                                             // inputs. Refer to Pimux diagram for details.
#define ASYSCTL_O_CMPLNMXSEL        0x87U    // Bits to select one of the many sources on CopmLN
                                             // inputs. Refer to Pimux diagram for details.
#define ASYSCTL_O_ADCDACLOOPBACK    0x88U    // Enabble loopback from DAC to ADCs
#define ASYSCTL_O_LOCK              0x8EU    // Lock Register
#define ASYSCTL_O_CMPHPMXSEL1       0x90U    // Bits to select one of the many sources on CopmHP
                                             // inputs. Refer to Pimux diagram for details.
#define ASYSCTL_O_CMPLPMXSEL1       0x92U    // Bits to select one of the many sources on CopmLP
                                             // inputs. Refer to Pimux diagram for details.
#define ASYSCTL_O_ADCSOCFRCGB       0x10EU   // ADC Global SOC Force
#define ASYSCTL_O_ADCSOCFRCGBSEL    0x110U   // ADC Global SOC Force Select
#define ASYSCTL_O_AGPIOFILTER       0x111U   // AGPIO Filter Control Register
#define ASYSCTL_O_AGPIOCTRLG        0x120U   // AGPIO Control Register
#define ASYSCTL_O_AGPIOCTRLH        0x122U   // AGPIO Control Register
#define ASYSCTL_O_GPIOINENACTRL     0x134U   // GPIOINENACTRL Control Register


//*************************************************************************************************
//
// The following are defines for the bit fields in the INTERNALTESTCTL register
//
//*************************************************************************************************
#define ASYSCTL_INTERNALTESTCTL_TESTSEL_S   0U
#define ASYSCTL_INTERNALTESTCTL_TESTSEL_M   0x3FU         // Test Select
#define ASYSCTL_INTERNALTESTCTL_KEY_S       16U
#define ASYSCTL_INTERNALTESTCTL_KEY_M       0xFFFF0000U   // Key to Enable writes

//*************************************************************************************************
//
// The following are defines for the bit fields in the CONFIGLOCK register
//
//*************************************************************************************************
#define ASYSCTL_CONFIGLOCK_AGPIOFILTER     0x2U    // Locks AGPIOFILTER Register
#define ASYSCTL_CONFIGLOCK_AGPIOCTRL       0x8U    // Locks all AGPIOCTRL Register
#define ASYSCTL_CONFIGLOCK_GPIOINENACTRL   0x40U   // Locks all GPIOINENACTRL Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the TSNSCTL register
//
//*************************************************************************************************
#define ASYSCTL_TSNSCTL_ENABLE   0x1U   // Temperature Sensor Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the ANAREFCTL register
//
//*************************************************************************************************
#define ASYSCTL_ANAREFCTL_ANAREFASEL      0x1U     // Analog Reference Select
#define ASYSCTL_ANAREFCTL_ANAREFBSEL      0x2U     // Analog Reference B Select
#define ASYSCTL_ANAREFCTL_ANAREFCSEL      0x4U     // Analog Reference C Select
#define ASYSCTL_ANAREFCTL_ANAREFA2P5SEL   0x100U   // Analog Reference Select
#define ASYSCTL_ANAREFCTL_ANAREFB2P5SEL   0x200U   // Analog Reference B Select
#define ASYSCTL_ANAREFCTL_ANAREFC2P5SEL   0x400U   // Analog Reference C Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the VMONCTL register
//
//*************************************************************************************************
#define ASYSCTL_VMONCTL_BORLVMONDIS   0x100U   // Disable BORL(ow) feature on VDDIO

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPHPMXSEL register
//
//*************************************************************************************************
#define ASYSCTL_CMPHPMXSEL_CMP1HPMXSEL_S    0U
#define ASYSCTL_CMPHPMXSEL_CMP1HPMXSEL_M    0x7U          // CMP1HPMXSEL bits
#define ASYSCTL_CMPHPMXSEL_CMP2HPMXSEL_S    3U
#define ASYSCTL_CMPHPMXSEL_CMP2HPMXSEL_M    0x38U         // CMP2HPMXSEL bits
#define ASYSCTL_CMPHPMXSEL_CMP3HPMXSEL_S    6U
#define ASYSCTL_CMPHPMXSEL_CMP3HPMXSEL_M    0x1C0U        // CMP3HPMXSEL bits
#define ASYSCTL_CMPHPMXSEL_CMP4HPMXSEL_S    9U
#define ASYSCTL_CMPHPMXSEL_CMP4HPMXSEL_M    0xE00U        // CMP4HPMXSEL bits
#define ASYSCTL_CMPHPMXSEL_CMP5HPMXSEL_S    12U
#define ASYSCTL_CMPHPMXSEL_CMP5HPMXSEL_M    0x7000U       // CMP5HPMXSEL bits
#define ASYSCTL_CMPHPMXSEL_CMP6HPMXSEL_S    15U
#define ASYSCTL_CMPHPMXSEL_CMP6HPMXSEL_M    0x38000U      // CMP6HPMXSEL bits
#define ASYSCTL_CMPHPMXSEL_CMP7HPMXSEL_S    18U
#define ASYSCTL_CMPHPMXSEL_CMP7HPMXSEL_M    0x1C0000U     // CMP7HPMXSEL bits
#define ASYSCTL_CMPHPMXSEL_CMP8HPMXSEL_S    21U
#define ASYSCTL_CMPHPMXSEL_CMP8HPMXSEL_M    0xE00000U     // CMP8HPMXSEL bits
#define ASYSCTL_CMPHPMXSEL_CMP9HPMXSEL_S    24U
#define ASYSCTL_CMPHPMXSEL_CMP9HPMXSEL_M    0x7000000U    // CMP9HPMXSEL bits
#define ASYSCTL_CMPHPMXSEL_CMP10HPMXSEL_S   27U
#define ASYSCTL_CMPHPMXSEL_CMP10HPMXSEL_M   0x38000000U   // CMP10HPMXSEL bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPLPMXSEL register
//
//*************************************************************************************************
#define ASYSCTL_CMPLPMXSEL_CMP1LPMXSEL_S    0U
#define ASYSCTL_CMPLPMXSEL_CMP1LPMXSEL_M    0x7U          // CMP1LPMXSEL bits
#define ASYSCTL_CMPLPMXSEL_CMP2LPMXSEL_S    3U
#define ASYSCTL_CMPLPMXSEL_CMP2LPMXSEL_M    0x38U         // CMP2LPMXSEL bits
#define ASYSCTL_CMPLPMXSEL_CMP3LPMXSEL_S    6U
#define ASYSCTL_CMPLPMXSEL_CMP3LPMXSEL_M    0x1C0U        // CMP3LPMXSEL bits
#define ASYSCTL_CMPLPMXSEL_CMP4LPMXSEL_S    9U
#define ASYSCTL_CMPLPMXSEL_CMP4LPMXSEL_M    0xE00U        // CMP4LPMXSEL bits
#define ASYSCTL_CMPLPMXSEL_CMP5LPMXSEL_S    12U
#define ASYSCTL_CMPLPMXSEL_CMP5LPMXSEL_M    0x7000U       // CMP5LPMXSEL bits
#define ASYSCTL_CMPLPMXSEL_CMP6LPMXSEL_S    15U
#define ASYSCTL_CMPLPMXSEL_CMP6LPMXSEL_M    0x38000U      // CMP6LPMXSEL bits
#define ASYSCTL_CMPLPMXSEL_CMP7LPMXSEL_S    18U
#define ASYSCTL_CMPLPMXSEL_CMP7LPMXSEL_M    0x1C0000U     // CMP7LPMXSEL bits
#define ASYSCTL_CMPLPMXSEL_CMP8LPMXSEL_S    21U
#define ASYSCTL_CMPLPMXSEL_CMP8LPMXSEL_M    0xE00000U     // CMP8LPMXSEL bits
#define ASYSCTL_CMPLPMXSEL_CMP9LPMXSEL_S    24U
#define ASYSCTL_CMPLPMXSEL_CMP9LPMXSEL_M    0x7000000U    // CMP9LPMXSEL bits
#define ASYSCTL_CMPLPMXSEL_CMP10LPMXSEL_S   27U
#define ASYSCTL_CMPLPMXSEL_CMP10LPMXSEL_M   0x38000000U   // CMP10LPMXSEL bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPHNMXSEL register
//
//*************************************************************************************************
#define ASYSCTL_CMPHNMXSEL_CMP1HNMXSEL    0x1U     // CMP1HNMXSEL bits
#define ASYSCTL_CMPHNMXSEL_CMP2HNMXSEL    0x2U     // CMP2HNMXSEL bits
#define ASYSCTL_CMPHNMXSEL_CMP3HNMXSEL    0x4U     // CMP3HNMXSEL bits
#define ASYSCTL_CMPHNMXSEL_CMP4HNMXSEL    0x8U     // CMP4HNMXSEL bits
#define ASYSCTL_CMPHNMXSEL_CMP5HNMXSEL    0x10U    // CMP5HNMXSEL bits
#define ASYSCTL_CMPHNMXSEL_CMP6HNMXSEL    0x20U    // CMP6HNMXSEL bits
#define ASYSCTL_CMPHNMXSEL_CMP7HNMXSEL    0x40U    // CMP7HNMXSEL bits
#define ASYSCTL_CMPHNMXSEL_CMP8HNMXSEL    0x80U    // CMP8HNMXSEL bits
#define ASYSCTL_CMPHNMXSEL_CMP9HNMXSEL    0x100U   // CMP9HNMXSEL bits
#define ASYSCTL_CMPHNMXSEL_CMP10HNMXSEL   0x200U   // CMP10HNMXSEL bits
#define ASYSCTL_CMPHNMXSEL_CMP11HNMXSEL   0x400U   // CMP11HNMXSEL bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPLNMXSEL register
//
//*************************************************************************************************
#define ASYSCTL_CMPLNMXSEL_CMP1LNMXSEL    0x1U     // CMP1LNMXSEL bits
#define ASYSCTL_CMPLNMXSEL_CMP2LNMXSEL    0x2U     // CMP2LNMXSEL bits
#define ASYSCTL_CMPLNMXSEL_CMP3LNMXSEL    0x4U     // CMP3LNMXSEL bits
#define ASYSCTL_CMPLNMXSEL_CMP4LNMXSEL    0x8U     // CMP4LNMXSEL bits
#define ASYSCTL_CMPLNMXSEL_CMP5LNMXSEL    0x10U    // CMP5LNMXSEL bits
#define ASYSCTL_CMPLNMXSEL_CMP6LNMXSEL    0x20U    // CMP6LNMXSEL bits
#define ASYSCTL_CMPLNMXSEL_CMP7LNMXSEL    0x40U    // CMP7LNMXSEL bits
#define ASYSCTL_CMPLNMXSEL_CMP8LNMXSEL    0x80U    // CMP8LNMXSEL bits
#define ASYSCTL_CMPLNMXSEL_CMP9LNMXSEL    0x100U   // CMP9LNMXSEL bits
#define ASYSCTL_CMPLNMXSEL_CMP10LNMXSEL   0x200U   // CMP10LNMXSEL bits
#define ASYSCTL_CMPLNMXSEL_CMP11LNMXSEL   0x400U   // CMP11LNMXSEL bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCDACLOOPBACK register
//
//*************************************************************************************************
#define ASYSCTL_ADCDACLOOPBACK_ENLB2ADCA   0x1U          // Enable COMPDACA loopback to ADCA
#define ASYSCTL_ADCDACLOOPBACK_ENLB2ADCB   0x2U          // Enable COMPDACA loopback to ADCB
#define ASYSCTL_ADCDACLOOPBACK_ENLB2ADCC   0x4U          // Enable COMPDACA loopback to ADCC
#define ASYSCTL_ADCDACLOOPBACK_KEY_S       16U
#define ASYSCTL_ADCDACLOOPBACK_KEY_M       0xFFFF0000U   // Key to enable writes

//*************************************************************************************************
//
// The following are defines for the bit fields in the LOCK register
//
//*************************************************************************************************
#define ASYSCTL_LOCK_TSNSCTL       0x1U      // TSNSCTL Register lock bit
#define ASYSCTL_LOCK_ANAREFCTL     0x2U      // ANAREFCTL Register lock bit
#define ASYSCTL_LOCK_VMONCTL       0x4U      // VMONCTL Register lock bit
#define ASYSCTL_LOCK_CMPHPMXSEL    0x20U     // CMPHPMXSEL Register lock bit
#define ASYSCTL_LOCK_CMPLPMXSEL    0x40U     // CMPLPMXSEL Register lock bit
#define ASYSCTL_LOCK_CMPHNMXSEL    0x80U     // CMPHNMXSEL Register lock bit
#define ASYSCTL_LOCK_CMPLNMXSEL    0x100U    // CMPLNMXSEL Register lock bit
#define ASYSCTL_LOCK_VREGCTL       0x200U    // VREGCTL Register lock bit
#define ASYSCTL_LOCK_CMPSSCTL      0x400U    // CMPSSCTL Register lock bit
#define ASYSCTL_LOCK_CMPHPMXSEL1   0x800U    // CMPHPMXSEL1 Register lock bit
#define ASYSCTL_LOCK_CMPLPMXSEL1   0x1000U   // CMPLPMXSEL1 Register lock bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPHPMXSEL1 register
//
//*************************************************************************************************
#define ASYSCTL_CMPHPMXSEL1_CMP11HPMXSEL_S   0U
#define ASYSCTL_CMPHPMXSEL1_CMP11HPMXSEL_M   0x7U   // CMP15HPMXSEL bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPLPMXSEL1 register
//
//*************************************************************************************************
#define ASYSCTL_CMPLPMXSEL1_CMP11LPMXSEL_S   0U
#define ASYSCTL_CMPLPMXSEL1_CMP11LPMXSEL_M   0x7U   // CMP15LPMXSEL bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOCFRCGB register
//
//*************************************************************************************************
#define ASYSCTL_ADCSOCFRCGB_SOC0    0x1U      // Generate synchronous SW trigger for SOC0
#define ASYSCTL_ADCSOCFRCGB_SOC1    0x2U      // Generate synchronous SW trigger for SOC1
#define ASYSCTL_ADCSOCFRCGB_SOC2    0x4U      // Generate synchronous SW trigger for SOC2
#define ASYSCTL_ADCSOCFRCGB_SOC3    0x8U      // Generate synchronous SW trigger for SOC3
#define ASYSCTL_ADCSOCFRCGB_SOC4    0x10U     // Generate synchronous SW trigger for SOC4
#define ASYSCTL_ADCSOCFRCGB_SOC5    0x20U     // Generate synchronous SW trigger for SOC5
#define ASYSCTL_ADCSOCFRCGB_SOC6    0x40U     // Generate synchronous SW trigger for SOC6
#define ASYSCTL_ADCSOCFRCGB_SOC7    0x80U     // Generate synchronous SW trigger for SOC7
#define ASYSCTL_ADCSOCFRCGB_SOC8    0x100U    // Generate synchronous SW trigger for SOC8
#define ASYSCTL_ADCSOCFRCGB_SOC9    0x200U    // Generate synchronous SW trigger for SOC9
#define ASYSCTL_ADCSOCFRCGB_SOC10   0x400U    // Generate synchronous SW trigger for SOC10
#define ASYSCTL_ADCSOCFRCGB_SOC11   0x800U    // Generate synchronous SW trigger for SOC11
#define ASYSCTL_ADCSOCFRCGB_SOC12   0x1000U   // Generate synchronous SW trigger for SOC12
#define ASYSCTL_ADCSOCFRCGB_SOC13   0x2000U   // Generate synchronous SW trigger for SOC13
#define ASYSCTL_ADCSOCFRCGB_SOC14   0x4000U   // Generate synchronous SW trigger for SOC14
#define ASYSCTL_ADCSOCFRCGB_SOC15   0x8000U   // Generate synchronous SW trigger for SOC15

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOCFRCGBSEL register
//
//*************************************************************************************************
#define ASYSCTL_ADCSOCFRCGBSEL_ADCA   0x1U   // Generate synchronous SW trigger for ADCA
#define ASYSCTL_ADCSOCFRCGBSEL_ADCB   0x2U   // Generate synchronous SW trigger for ADCB
#define ASYSCTL_ADCSOCFRCGBSEL_ADCC   0x4U   // Generate synchronous SW trigger for ADCC

//*************************************************************************************************
//
// The following are defines for the bit fields in the AGPIOFILTER register
//
//*************************************************************************************************
#define ASYSCTL_AGPIOFILTER_RIGHT_S    0U
#define ASYSCTL_AGPIOFILTER_RIGHT_M    0x3U     // AGPIOFILTER Control for right side pins
#define ASYSCTL_AGPIOFILTER_BOTTOM_S   8U
#define ASYSCTL_AGPIOFILTER_BOTTOM_M   0x300U   // AGPIOFILTER Control for bottom side pins

//*************************************************************************************************
//
// The following are defines for the bit fields in the AGPIOCTRLG register
//
//*************************************************************************************************
#define ASYSCTL_AGPIOCTRLG_GPIO198   0x40U        // AGPIOCTRL for GPIO198
#define ASYSCTL_AGPIOCTRLG_GPIO199   0x80U        // AGPIOCTRL for GPIO199
#define ASYSCTL_AGPIOCTRLG_GPIO200   0x100U       // AGPIOCTRL for GPIO200
#define ASYSCTL_AGPIOCTRLG_GPIO201   0x200U       // AGPIOCTRL for GPIO201
#define ASYSCTL_AGPIOCTRLG_GPIO202   0x400U       // AGPIOCTRL for GPIO202
#define ASYSCTL_AGPIOCTRLG_GPIO203   0x800U       // AGPIOCTRL for GPIO203
#define ASYSCTL_AGPIOCTRLG_GPIO204   0x1000U      // AGPIOCTRL for GPIO204
#define ASYSCTL_AGPIOCTRLG_GPIO205   0x2000U      // AGPIOCTRL for GPIO205
#define ASYSCTL_AGPIOCTRLG_GPIO206   0x4000U      // AGPIOCTRL for GPIO206
#define ASYSCTL_AGPIOCTRLG_GPIO207   0x8000U      // AGPIOCTRL for GPIO207
#define ASYSCTL_AGPIOCTRLG_GPIO208   0x10000U     // AGPIOCTRL for GPIO208
#define ASYSCTL_AGPIOCTRLG_GPIO209   0x20000U     // AGPIOCTRL for GPIO209
#define ASYSCTL_AGPIOCTRLG_GPIO210   0x40000U     // AGPIOCTRL for GPIO210
#define ASYSCTL_AGPIOCTRLG_GPIO211   0x80000U     // AGPIOCTRL for GPIO211
#define ASYSCTL_AGPIOCTRLG_GPIO212   0x100000U    // AGPIOCTRL for GPIO212
#define ASYSCTL_AGPIOCTRLG_GPIO213   0x200000U    // AGPIOCTRL for GPIO213
#define ASYSCTL_AGPIOCTRLG_GPIO214   0x400000U    // AGPIOCTRL for GPIO214
#define ASYSCTL_AGPIOCTRLG_GPIO215   0x800000U    // AGPIOCTRL for GPIO215
#define ASYSCTL_AGPIOCTRLG_GPIO216   0x1000000U   // AGPIOCTRL for GPIO216
#define ASYSCTL_AGPIOCTRLG_GPIO217   0x2000000U   // AGPIOCTRL for GPIO217
#define ASYSCTL_AGPIOCTRLG_GPIO218   0x4000000U   // AGPIOCTRL for GPIO218
#define ASYSCTL_AGPIOCTRLG_GPIO219   0x8000000U   // AGPIOCTRL for GPIO219

//*************************************************************************************************
//
// The following are defines for the bit fields in the AGPIOCTRLH register
//
//*************************************************************************************************
#define ASYSCTL_AGPIOCTRLH_GPIO224   0x1U       // AGPIOCTRL for GPIO224
#define ASYSCTL_AGPIOCTRLH_GPIO225   0x2U       // AGPIOCTRL for GPIO225
#define ASYSCTL_AGPIOCTRLH_GPIO226   0x4U       // AGPIOCTRL for GPIO226
#define ASYSCTL_AGPIOCTRLH_GPIO227   0x8U       // AGPIOCTRL for GPIO227
#define ASYSCTL_AGPIOCTRLH_GPIO228   0x10U      // AGPIOCTRL for GPIO228
#define ASYSCTL_AGPIOCTRLH_GPIO229   0x20U      // AGPIOCTRL for GPIO229
#define ASYSCTL_AGPIOCTRLH_GPIO230   0x40U      // AGPIOCTRL for GPIO230
#define ASYSCTL_AGPIOCTRLH_GPIO231   0x80U      // AGPIOCTRL for GPIO231
#define ASYSCTL_AGPIOCTRLH_GPIO232   0x100U     // AGPIOCTRL for GPIO232
#define ASYSCTL_AGPIOCTRLH_GPIO233   0x200U     // AGPIOCTRL for GPIO233
#define ASYSCTL_AGPIOCTRLH_GPIO234   0x400U     // AGPIOCTRL for GPIO234
#define ASYSCTL_AGPIOCTRLH_GPIO235   0x800U     // AGPIOCTRL for GPIO235
#define ASYSCTL_AGPIOCTRLH_GPIO236   0x1000U    // AGPIOCTRL for GPIO236
#define ASYSCTL_AGPIOCTRLH_GPIO237   0x2000U    // AGPIOCTRL for GPIO237
#define ASYSCTL_AGPIOCTRLH_GPIO238   0x4000U    // AGPIOCTRL for GPIO238
#define ASYSCTL_AGPIOCTRLH_GPIO239   0x8000U    // AGPIOCTRL for GPIO239
#define ASYSCTL_AGPIOCTRLH_GPIO240   0x10000U   // AGPIOCTRL for GPIO240
#define ASYSCTL_AGPIOCTRLH_GPIO241   0x20000U   // AGPIOCTRL for GPIO241
#define ASYSCTL_AGPIOCTRLH_GPIO242   0x40000U   // AGPIOCTRL for GPIO242

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPIOINENACTRL register
//
//*************************************************************************************************
#define ASYSCTL_GPIOINENACTRL_GPIO0     0x1U    // Input Buffer Control for GPIO0
#define ASYSCTL_GPIOINENACTRL_GPIO23    0x2U    // Input Buffer Control for GPIO23
#define ASYSCTL_GPIOINENACTRL_GPIO25    0x4U    // Input Buffer Control for GPIO25
#define ASYSCTL_GPIOINENACTRL_GPIO31    0x8U    // Input Buffer Control for GPIO31
#define ASYSCTL_GPIOINENACTRL_GPIO46    0x10U   // Input Buffer Control for GPIO46
#define ASYSCTL_GPIOINENACTRL_GPIO103   0x20U   // Input Buffer Control for GPIO103



#endif
