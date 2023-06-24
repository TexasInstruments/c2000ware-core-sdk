//###########################################################################
//
// FILE:    hw_asysctl.h
//
// TITLE:   Definitions for the ASYSCTL registers.
//
//###########################################################################
// $Copyright:
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
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
#define ASYSCTL_O_TSNSCTL          0x60U   // Temperature Sensor Control Register
#define ASYSCTL_O_ANAREFCTL        0x68U   // Analog Reference Control Register
#define ASYSCTL_O_VMONCTL          0x70U   // Voltage Monitor Control Register
#define ASYSCTL_O_CMPHPMXSEL       0x82U   // Bits to select one of the many sources on CopmHP
                                           // inputs. Refer to Pimux diagram for details.
#define ASYSCTL_O_CMPLPMXSEL       0x84U   // Bits to select one of the many sources on CopmLP
                                           // inputs. Refer to Pimux diagram for details.
#define ASYSCTL_O_CMPHNMXSEL       0x86U   // Bits to select one of the many sources on CopmHN
                                           // inputs. Refer to Pimux diagram for details.
#define ASYSCTL_O_CMPLNMXSEL       0x87U   // Bits to select one of the many sources on CopmLN
                                           // inputs. Refer to Pimux diagram for details.
#define ASYSCTL_O_ADCDACLOOPBACK   0x88U   // Enabble loopback from DAC to ADCs
#define ASYSCTL_O_LOCK             0x8EU   // Lock Register


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
#define ASYSCTL_ANAREFCTL_ANAREFASEL      0x1U     // Analog Reference A Select
#define ASYSCTL_ANAREFCTL_ANAREFCSEL      0x4U     // Analog Reference C Select
#define ASYSCTL_ANAREFCTL_ANAREFA2P5SEL   0x100U   // Analog Reference A Select
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
#define ASYSCTL_ADCDACLOOPBACK_ENLB2ADCC   0x4U          // Enable DACA loopback to ADCC
#define ASYSCTL_ADCDACLOOPBACK_KEY_S       16U
#define ASYSCTL_ADCDACLOOPBACK_KEY_M       0xFFFF0000U   // Key to enable writes

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



#endif
