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
#define ASYSCTL_O_INTERNALTESTCTL     0x4AU    // INTERNALTEST Node Control Register
#define ASYSCTL_O_CONFIGLOCK          0x5EU    // Lock Register for all the config registers.
#define ASYSCTL_O_TSNSCTL             0x60U    // Temperature Sensor Control Register
#define ASYSCTL_O_ANAREFPCTL          0x68U    // Analog Reference Control Register for VREFHI
#define ASYSCTL_O_ANAREFNCTL          0x69U    // Analog Reference Control Register for VREFLO
#define ASYSCTL_O_VMONCTL             0x70U    // Voltage Monitor Control Register
#define ASYSCTL_O_CMPHPMXSEL          0x82U    // Bits to select one of the many sources on CompHP
                                               // inputs. Refer to Pimux diagram for details.
#define ASYSCTL_O_CMPLPMXSEL          0x84U    // Bits to select one of the many sources on CompLP
                                               // inputs. Refer to Pimux diagram for details.
#define ASYSCTL_O_CMPHNMXSEL          0x86U    // Bits to select one of the many sources on CompHN
                                               // inputs. Refer to Pimux diagram for details.
#define ASYSCTL_O_CMPLNMXSEL          0x87U    // Bits to select one of the many sources on CompLN
                                               // inputs. Refer to Pimux diagram for details.
#define ASYSCTL_O_ADCDACLOOPBACK      0x88U    // Enabble loopback from DAC to ADCs
#define ASYSCTL_O_CMPSSCTL            0x8BU    // CMPSS Control Register
#define ASYSCTL_O_CMPSSDACBUFCONFIG   0x8CU    // Config bits for CMPSS DAC buffer
#define ASYSCTL_O_LOCK                0x8EU    // Lock Register
#define ASYSCTL_O_AGPIOFILTER         0x108U   // AGPIO Filter Control Register
#define ASYSCTL_O_AGPIOCTRLA          0x10AU   // AGPIO Control Register
#define ASYSCTL_O_AGPIOCTRLB          0x10CU   // AGPIO Control Register
#define ASYSCTL_O_AGPIOCTRLG          0x116U   // AGPIO Control Register
#define ASYSCTL_O_AGPIOCTRLH          0x118U   // AGPIO Control Register
#define ASYSCTL_O_GPIOINENACTRL       0x132U   // GPIOINENACTRL Control Register
#define ASYSCTL_O_IO_DRVSEL           0x134U   // IO Drive strength select register
#define ASYSCTL_O_IO_MODESEL          0x135U   // IO Mode select register
#define ASYSCTL_O_ADCSOCFRCGB         0x136U   // ADC Global SOC Force
#define ASYSCTL_O_ADCSOCFRCGBSEL      0x138U   // ADC Global SOC Force Select


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
// The following are defines for the bit fields in the ANAREFPCTL register
//
//*************************************************************************************************
#define ASYSCTL_ANAREFPCTL_REFPMUXSELA_S    0U
#define ASYSCTL_ANAREFPCTL_REFPMUXSELA_M    0x3U      // Analog Reference Select ADCA
#define ASYSCTL_ANAREFPCTL_REFPMUXSELB_S    2U
#define ASYSCTL_ANAREFPCTL_REFPMUXSELB_M    0xCU      // Analog Reference Select ADCB
#define ASYSCTL_ANAREFPCTL_REFPMUXSELC_S    4U
#define ASYSCTL_ANAREFPCTL_REFPMUXSELC_M    0x30U     // Analog Reference Select ADCC
#define ASYSCTL_ANAREFPCTL_REFPMUXSELD_S    6U
#define ASYSCTL_ANAREFPCTL_REFPMUXSELD_M    0xC0U     // Analog Reference Select ADCD
#define ASYSCTL_ANAREFPCTL_REFPMUXSELE_S    8U
#define ASYSCTL_ANAREFPCTL_REFPMUXSELE_M    0x300U    // Analog Reference Select ADCE
#define ASYSCTL_ANAREFPCTL_ANAREFA1P65SEL   0x400U    // 1.65v Reference Select ADCA
#define ASYSCTL_ANAREFPCTL_ANAREFB1P65SEL   0x800U    // 1.65v Reference Select ADCB
#define ASYSCTL_ANAREFPCTL_ANAREFC1P65SEL   0x1000U   // 1.65v Reference Select ADCC
#define ASYSCTL_ANAREFPCTL_ANAREFD1P65SEL   0x2000U   // 1.65v Reference Select ADCD
#define ASYSCTL_ANAREFPCTL_ANAREFE1P65SEL   0x4000U   // 1.65v Reference Select ADCE

//*************************************************************************************************
//
// The following are defines for the bit fields in the ANAREFNCTL register
//
//*************************************************************************************************
#define ASYSCTL_ANAREFNCTL_REFNMUXSELA_S   0U
#define ASYSCTL_ANAREFNCTL_REFNMUXSELA_M   0x3U     // Analog Reference Select ADCA
#define ASYSCTL_ANAREFNCTL_REFNMUXSELB_S   2U
#define ASYSCTL_ANAREFNCTL_REFNMUXSELB_M   0xCU     // Analog Reference Select ADCB
#define ASYSCTL_ANAREFNCTL_REFNMUXSELC_S   4U
#define ASYSCTL_ANAREFNCTL_REFNMUXSELC_M   0x30U    // Analog Reference Select ADCC
#define ASYSCTL_ANAREFNCTL_REFNMUXSELD_S   6U
#define ASYSCTL_ANAREFNCTL_REFNMUXSELD_M   0xC0U    // Analog Reference Select ADCD
#define ASYSCTL_ANAREFNCTL_REFNMUXSELE_S   8U
#define ASYSCTL_ANAREFNCTL_REFNMUXSELE_M   0x300U   // Analog Reference Select ADCE

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
#define ASYSCTL_CMPHPMXSEL_CMP1HPMXSEL_S   0U
#define ASYSCTL_CMPHPMXSEL_CMP1HPMXSEL_M   0x7U     // CMP1HPMXSEL bits
#define ASYSCTL_CMPHPMXSEL_CMP2HPMXSEL_S   3U
#define ASYSCTL_CMPHPMXSEL_CMP2HPMXSEL_M   0x38U    // CMP2HPMXSEL bits
#define ASYSCTL_CMPHPMXSEL_CMP3HPMXSEL_S   6U
#define ASYSCTL_CMPHPMXSEL_CMP3HPMXSEL_M   0x1C0U   // CMP3HPMXSEL bits
#define ASYSCTL_CMPHPMXSEL_CMP4HPMXSEL_S   9U
#define ASYSCTL_CMPHPMXSEL_CMP4HPMXSEL_M   0xE00U   // CMP4HPMXSEL bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPLPMXSEL register
//
//*************************************************************************************************
#define ASYSCTL_CMPLPMXSEL_CMP1LPMXSEL_S   0U
#define ASYSCTL_CMPLPMXSEL_CMP1LPMXSEL_M   0x7U     // CMP1LPMXSEL bits
#define ASYSCTL_CMPLPMXSEL_CMP2LPMXSEL_S   3U
#define ASYSCTL_CMPLPMXSEL_CMP2LPMXSEL_M   0x38U    // CMP2LPMXSEL bits
#define ASYSCTL_CMPLPMXSEL_CMP3LPMXSEL_S   6U
#define ASYSCTL_CMPLPMXSEL_CMP3LPMXSEL_M   0x1C0U   // CMP3LPMXSEL bits
#define ASYSCTL_CMPLPMXSEL_CMP4LPMXSEL_S   9U
#define ASYSCTL_CMPLPMXSEL_CMP4LPMXSEL_M   0xE00U   // CMP4LPMXSEL bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPHNMXSEL register
//
//*************************************************************************************************
#define ASYSCTL_CMPHNMXSEL_CMP1HNMXSEL   0x1U   // CMP1HNMXSEL bits
#define ASYSCTL_CMPHNMXSEL_CMP2HNMXSEL   0x2U   // CMP2HNMXSEL bits
#define ASYSCTL_CMPHNMXSEL_CMP3HNMXSEL   0x4U   // CMP3HNMXSEL bits
#define ASYSCTL_CMPHNMXSEL_CMP4HNMXSEL   0x8U   // CMP4HNMXSEL bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPLNMXSEL register
//
//*************************************************************************************************
#define ASYSCTL_CMPLNMXSEL_CMP1LNMXSEL   0x1U   // CMP1LNMXSEL bits
#define ASYSCTL_CMPLNMXSEL_CMP2LNMXSEL   0x2U   // CMP2LNMXSEL bits
#define ASYSCTL_CMPLNMXSEL_CMP3LNMXSEL   0x4U   // CMP3LNMXSEL bits
#define ASYSCTL_CMPLNMXSEL_CMP4LNMXSEL   0x8U   // CMP4LNMXSEL bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCDACLOOPBACK register
//
//*************************************************************************************************
#define ASYSCTL_ADCDACLOOPBACK_ENLB2ADCA   0x1U          // Enable DACA loopback to ADCA
#define ASYSCTL_ADCDACLOOPBACK_ENLB2ADCB   0x2U          // Enable DACA loopback to ADCB
#define ASYSCTL_ADCDACLOOPBACK_ENLB2ADCC   0x4U          // Enable DACA loopback to ADCC
#define ASYSCTL_ADCDACLOOPBACK_ENLB2ADCD   0x8U          // Enable DACA loopback to ADCD
#define ASYSCTL_ADCDACLOOPBACK_ENLB2ADCE   0x10U         // Enable DACA loopback to ADCE
#define ASYSCTL_ADCDACLOOPBACK_KEY_S       16U
#define ASYSCTL_ADCDACLOOPBACK_KEY_M       0xFFFF0000U   // Key to enable writes

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPSSCTL register
//
//*************************************************************************************************
#define ASYSCTL_CMPSSCTL_CMP1LDACOUTEN   0x1U      // Enable general purpose DAC functionality for
                                                   // CMPSS1.COMPDACL
#define ASYSCTL_CMPSSCTL_CMPSSCTLEN      0x8000U   // Enable the CMPSSCTL Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPSSDACBUFCONFIG register
//
//*************************************************************************************************
#define ASYSCTL_CMPSSDACBUFCONFIG_CMPSSADACL_S   0U
#define ASYSCTL_CMPSSDACBUFCONFIG_CMPSSADACL_M   0xFFU   // Configuration bits for CMPSS DACA

//*************************************************************************************************
//
// The following are defines for the bit fields in the LOCK register
//
//*************************************************************************************************
#define ASYSCTL_LOCK_TSNSCTL      0x1U     // TSNSCTL Register lock bit
#define ASYSCTL_LOCK_ANAREFCTL    0x2U     // ANAREFCTL Register lock bit
#define ASYSCTL_LOCK_VMONCTL      0x4U     // VMONCTL Register lock bit
#define ASYSCTL_LOCK_CMPHPMXSEL   0x20U    // CMPHPMXSEL Register lock bit
#define ASYSCTL_LOCK_CMPLPMXSEL   0x40U    // CMPLPMXSEL Register lock bit
#define ASYSCTL_LOCK_CMPHNMXSEL   0x80U    // CMPHNMXSEL Register lock bit
#define ASYSCTL_LOCK_CMPLNMXSEL   0x100U   // CMPLNMXSEL Register lock bit
#define ASYSCTL_LOCK_VREGCTL      0x200U   // VREGCTL Register lock bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the AGPIOFILTER register
//
//*************************************************************************************************
#define ASYSCTL_AGPIOFILTER_GROUP1_S   0U
#define ASYSCTL_AGPIOFILTER_GROUP1_M   0x3U     // AGPIOFILTER Control for group1 side pins
#define ASYSCTL_AGPIOFILTER_GROUP2_S   8U
#define ASYSCTL_AGPIOFILTER_GROUP2_M   0x300U   // AGPIOFILTER Control for group2 side pins

//*************************************************************************************************
//
// The following are defines for the bit fields in the AGPIOCTRLA register
//
//*************************************************************************************************
#define ASYSCTL_AGPIOCTRLA_GPIO11   0x800U        // AGPIOCTRL for GPIO11
#define ASYSCTL_AGPIOCTRLA_GPIO12   0x1000U       // AGPIOCTRL for GPIO12
#define ASYSCTL_AGPIOCTRLA_GPIO13   0x2000U       // AGPIOCTRL for GPIO13
#define ASYSCTL_AGPIOCTRLA_GPIO16   0x10000U      // AGPIOCTRL for GPIO16
#define ASYSCTL_AGPIOCTRLA_GPIO17   0x20000U      // AGPIOCTRL for GPIO17
#define ASYSCTL_AGPIOCTRLA_GPIO20   0x100000U     // AGPIOCTRL for GPIO20
#define ASYSCTL_AGPIOCTRLA_GPIO21   0x200000U     // AGPIOCTRL for GPIO21
#define ASYSCTL_AGPIOCTRLA_GPIO24   0x1000000U    // AGPIOCTRL for GPIO24
#define ASYSCTL_AGPIOCTRLA_GPIO28   0x10000000U   // AGPIOCTRL for GPIO28

//*************************************************************************************************
//
// The following are defines for the bit fields in the AGPIOCTRLB register
//
//*************************************************************************************************
#define ASYSCTL_AGPIOCTRLB_GPIO33   0x2U   // AGPIOCTRL for GPIO33

//*************************************************************************************************
//
// The following are defines for the bit fields in the AGPIOCTRLG register
//
//*************************************************************************************************
#define ASYSCTL_AGPIOCTRLG_GPIO211   0x80000U    // AGPIOCTRL for GPIO211
#define ASYSCTL_AGPIOCTRLG_GPIO212   0x100000U   // AGPIOCTRL for GPIO212
#define ASYSCTL_AGPIOCTRLG_GPIO213   0x200000U   // AGPIOCTRL for GPIO213
#define ASYSCTL_AGPIOCTRLG_GPIO214   0x400000U   // AGPIOCTRL for GPIO214
#define ASYSCTL_AGPIOCTRLG_GPIO215   0x800000U   // AGPIOCTRL for GPIO215

//*************************************************************************************************
//
// The following are defines for the bit fields in the AGPIOCTRLH register
//
//*************************************************************************************************
#define ASYSCTL_AGPIOCTRLH_GPIO224   0x1U          // AGPIOCTRL for GPIO224
#define ASYSCTL_AGPIOCTRLH_GPIO226   0x4U          // AGPIOCTRL for GPIO226
#define ASYSCTL_AGPIOCTRLH_GPIO227   0x8U          // AGPIOCTRL for GPIO227
#define ASYSCTL_AGPIOCTRLH_GPIO228   0x10U         // AGPIOCTRL for GPIO228
#define ASYSCTL_AGPIOCTRLH_GPIO230   0x40U         // AGPIOCTRL for GPIO230
#define ASYSCTL_AGPIOCTRLH_GPIO236   0x1000U       // AGPIOCTRL for GPIO236
#define ASYSCTL_AGPIOCTRLH_GPIO242   0x40000U      // AGPIOCTRL for GPIO242
#define ASYSCTL_AGPIOCTRLH_GPIO247   0x800000U     // AGPIOCTRL for GPIO247
#define ASYSCTL_AGPIOCTRLH_GPIO253   0x20000000U   // AGPIOCTRL for GPIO253

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPIOINENACTRL register
//
//*************************************************************************************************
#define ASYSCTL_GPIOINENACTRL_GPIO20   0x1U   // Input Buffer Control for GPIO20
#define ASYSCTL_GPIOINENACTRL_GPIO21   0x2U   // Input Buffer Control for GPIO21
#define ASYSCTL_GPIOINENACTRL_GPIO62   0x4U   // Input Buffer Control for GPIO62
#define ASYSCTL_GPIOINENACTRL_GPIO63   0x8U   // Input Buffer Control for GPIO63

//*************************************************************************************************
//
// The following are defines for the bit fields in the IO_DRVSEL register
//
//*************************************************************************************************
#define ASYSCTL_IO_DRVSEL_DRVSEL_GPIO2    0x1U   // Drive select for GPIO 2
#define ASYSCTL_IO_DRVSEL_DRVSEL_GPIO3    0x2U   // Drive select for GPIO 3
#define ASYSCTL_IO_DRVSEL_DRVSEL_GPIO9    0x4U   // Drive select for GPIO 9
#define ASYSCTL_IO_DRVSEL_DRVSEL_GPIO32   0x8U   // Drive select for GPIO 32

//*************************************************************************************************
//
// The following are defines for the bit fields in the IO_MODESEL register
//
//*************************************************************************************************
#define ASYSCTL_IO_MODESEL_MODESEL_GPIO2    0x1U   // Mode select for GPIO 2
#define ASYSCTL_IO_MODESEL_MODESEL_GPIO3    0x2U   // Mode select for GPIO 3
#define ASYSCTL_IO_MODESEL_MODESEL_GPIO9    0x4U   // Mode select for GPIO 9
#define ASYSCTL_IO_MODESEL_MODESEL_GPIO32   0x8U   // Mode select for GPIO 32

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
#define ASYSCTL_ADCSOCFRCGBSEL_ADCA   0x1U    // Generate synchronous SW trigger for ADCA
#define ASYSCTL_ADCSOCFRCGBSEL_ADCB   0x2U    // Generate synchronous SW trigger for ADCB
#define ASYSCTL_ADCSOCFRCGBSEL_ADCC   0x4U    // Generate synchronous SW trigger for ADCC
#define ASYSCTL_ADCSOCFRCGBSEL_ADCD   0x8U    // Generate synchronous SW trigger for ADCD
#define ASYSCTL_ADCSOCFRCGBSEL_ADCE   0x10U   // Generate synchronous SW trigger for ADCE



#endif
