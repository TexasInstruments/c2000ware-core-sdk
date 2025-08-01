//###########################################################################
//
// FILE:    hw_asysctl.h
//
// TITLE:   Definitions for the ASYSCTL registers.
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

#ifndef HW_ASYSCTL_H
#define HW_ASYSCTL_H

//*************************************************************************************************
//
// The following are defines for the ASYSCTL register offsets
//
//*************************************************************************************************
#define ASYSCTL_O_EXTROSCCSR1       0x2AU    // ExtR Oscillator Status Register
#define ASYSCTL_O_ADCOSDETECT       0x2CU    // I2V Logic Control
#define ASYSCTL_O_REFCONFIGA        0x3AU    // Config register for analog reference A.
#define ASYSCTL_O_INTERNALTESTCTL   0x56U    // INTERNALTEST Node Control Register
#define ASYSCTL_O_CONFIGLOCK        0x6AU    // Lock Register for all the config registers.
#define ASYSCTL_O_TSNSCTL           0x6CU    // Temperature Sensor Control Register
#define ASYSCTL_O_ANAREFCTL         0x74U    // Analog Reference Control Register. This register is
                                             // not configurable for 32QFN package
#define ASYSCTL_O_VMONCTL           0x7CU    // Voltage Monitor Control Register
#define ASYSCTL_O_CMPHPMXSEL        0x8EU    // Bits to select one of the many sources on CompHP
                                             // inputs. Refer to Pimux diagram for details.
#define ASYSCTL_O_CMPLPMXSEL        0x90U    // Bits to select one of the many sources on CompLP
                                             // inputs. Refer to Pimux diagram for details.
#define ASYSCTL_O_CMPHNMXSEL        0x92U    // Bits to select one of the many sources on CompHN
                                             // inputs. Refer to Pimux diagram for details.
#define ASYSCTL_O_CMPLNMXSEL        0x93U    // Bits to select one of the many sources on CompLN
                                             // inputs. Refer to Pimux diagram for details.
#define ASYSCTL_O_ADCDACLOOPBACK    0x94U    // Enabble loopback from DAC to ADCs
#define ASYSCTL_O_CMPSSCTL          0x97U    // CMPSS Control Register
#define ASYSCTL_O_LOCK              0x9AU    // Lock Register
#define ASYSCTL_O_AGPIOCTRLA        0x120U   // AGPIO Control Register
#define ASYSCTL_O_AGPIOCTRLH        0x12EU   // AGPIO Control Register
#define ASYSCTL_O_GPIOINENACTRL     0x140U   // GPIOINENACTRL Control Register


//*************************************************************************************************
//
// The following are defines for the bit fields in the EXTROSCCSR1 register
//
//*************************************************************************************************
#define ASYSCTL_EXTROSCCSR1_OSCSTATUS_S   24U
#define ASYSCTL_EXTROSCCSR1_OSCSTATUS_M   0xFF000000U   // Running status of ExtR.

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCOSDETECT register
//
//*************************************************************************************************
#define ASYSCTL_ADCOSDETECT_OSDETECT_EN   0x10U   // Enable OS Detect Logic
#define ASYSCTL_ADCOSDETECT_DETECTCFG_S   5U
#define ASYSCTL_ADCOSDETECT_DETECTCFG_M   0xE0U   // OS Detect configuration bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the REFCONFIGA register
//
//*************************************************************************************************
#define ASYSCTL_REFCONFIGA_CONFIG8   0x100000U   // Analog reference mode select

//*************************************************************************************************
//
// The following are defines for the bit fields in the INTERNALTESTCTL register
//
//*************************************************************************************************
#define ASYSCTL_INTERNALTESTCTL_TESTSEL_S   0U
#define ASYSCTL_INTERNALTESTCTL_TESTSEL_M   0x3FU   // Test Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the CONFIGLOCK register
//
//*************************************************************************************************
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
#define ASYSCTL_ANAREFCTL_ANAREF2P5SEL   0x100U   // Analog Reference Select

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

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPHNMXSEL register
//
//*************************************************************************************************
#define ASYSCTL_CMPHNMXSEL_CMP1HNMXSEL   0x1U   // CMP1HNMXSEL bits
#define ASYSCTL_CMPHNMXSEL_CMP2HNMXSEL   0x2U   // CMP2HNMXSEL bits
#define ASYSCTL_CMPHNMXSEL_CMP3HNMXSEL   0x4U   // CMP3HNMXSEL bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPLNMXSEL register
//
//*************************************************************************************************
#define ASYSCTL_CMPLNMXSEL_CMP1LNMXSEL   0x1U   // CMP1LNMXSEL bits
#define ASYSCTL_CMPLNMXSEL_CMP2LNMXSEL   0x2U   // CMP2LNMXSEL bits
#define ASYSCTL_CMPLNMXSEL_CMP3LNMXSEL   0x4U   // CMP3LNMXSEL bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCDACLOOPBACK register
//
//*************************************************************************************************
#define ASYSCTL_ADCDACLOOPBACK_ENLB2ADCA   0x1U          // Enable CMPSS.DAC loopback to ADCA
#define ASYSCTL_ADCDACLOOPBACK_KEY_S       16U
#define ASYSCTL_ADCDACLOOPBACK_KEY_M       0xFFFF0000U   // Key to enable writes

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPSSCTL register
//
//*************************************************************************************************
#define ASYSCTL_CMPSSCTL_CMP3LDACOUTEN   0x1U      // Enable general purpose DAC functionality for
                                                   // CMPSS3.COMPDACL
#define ASYSCTL_CMPSSCTL_CMPSSCTLEN      0x8000U   // Enable the CMPSSCTL Register

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
#define ASYSCTL_LOCK_CMPSSCTL     0x400U   // CMPSSCTL Register lock bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the AGPIOCTRLA register
//
//*************************************************************************************************
#define ASYSCTL_AGPIOCTRLA_GPIO12   0x1000U       // AGPIOCTRL for GPIO12
#define ASYSCTL_AGPIOCTRLA_GPIO13   0x2000U       // AGPIOCTRL for GPIO13
#define ASYSCTL_AGPIOCTRLA_GPIO28   0x10000000U   // AGPIOCTRL for GPIO28

//*************************************************************************************************
//
// The following are defines for the bit fields in the AGPIOCTRLH register
//
//*************************************************************************************************
#define ASYSCTL_AGPIOCTRLH_GPIO224   0x1U       // AGPIOCTRL for GPIO224
#define ASYSCTL_AGPIOCTRLH_GPIO226   0x4U       // AGPIOCTRL for GPIO226
#define ASYSCTL_AGPIOCTRLH_GPIO227   0x8U       // AGPIOCTRL for GPIO227
#define ASYSCTL_AGPIOCTRLH_GPIO228   0x10U      // AGPIOCTRL for GPIO228
#define ASYSCTL_AGPIOCTRLH_GPIO230   0x40U      // AGPIOCTRL for GPIO230
#define ASYSCTL_AGPIOCTRLH_GPIO242   0x40000U   // AGPIOCTRL for GPIO242
#define ASYSCTL_AGPIOCTRLH_GPIO243   0x80000U   // AGPIOCTRL for GPIO243

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPIOINENACTRL register
//
//*************************************************************************************************
#define ASYSCTL_GPIOINENACTRL_GPIO43   0x1U   // Input Buffer Control for GPIO43
#define ASYSCTL_GPIOINENACTRL_GPIO44   0x2U   // Input Buffer Control for GPIO44
#define ASYSCTL_GPIOINENACTRL_GPIO45   0x4U   // Input Buffer Control for GPIO45



#endif
