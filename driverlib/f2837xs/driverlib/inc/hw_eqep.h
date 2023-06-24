//###########################################################################
//
// FILE:    hw_eqep.h
//
// TITLE:   Definitions for the EQEP registers.
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

#ifndef HW_EQEP_H
#define HW_EQEP_H

//*************************************************************************************************
//
// The following are defines for the EQEP register offsets
//
//*************************************************************************************************
#define EQEP_O_QPOSCNT    0x0U    // Position Counter
#define EQEP_O_QPOSINIT   0x2U    // Position Counter Init
#define EQEP_O_QPOSMAX    0x4U    // Maximum Position Count
#define EQEP_O_QPOSCMP    0x6U    // Position Compare
#define EQEP_O_QPOSILAT   0x8U    // Index Position Latch
#define EQEP_O_QPOSSLAT   0xAU    // Strobe Position Latch
#define EQEP_O_QPOSLAT    0xCU    // Position Latch
#define EQEP_O_QUTMR      0xEU    // QEP Unit Timer
#define EQEP_O_QUPRD      0x10U   // QEP Unit Period
#define EQEP_O_QWDTMR     0x12U   // QEP Watchdog Timer
#define EQEP_O_QWDPRD     0x13U   // QEP Watchdog Period
#define EQEP_O_QDECCTL    0x14U   // Quadrature Decoder Control
#define EQEP_O_QEPCTL     0x15U   // QEP Control
#define EQEP_O_QCAPCTL    0x16U   // Qaudrature Capture Control
#define EQEP_O_QPOSCTL    0x17U   // Position Compare Control
#define EQEP_O_QEINT      0x18U   // QEP Interrupt Control
#define EQEP_O_QFLG       0x19U   // QEP Interrupt Flag
#define EQEP_O_QCLR       0x1AU   // QEP Interrupt Clear
#define EQEP_O_QFRC       0x1BU   // QEP Interrupt Force
#define EQEP_O_QEPSTS     0x1CU   // QEP Status
#define EQEP_O_QCTMR      0x1DU   // QEP Capture Timer
#define EQEP_O_QCPRD      0x1EU   // QEP Capture Period
#define EQEP_O_QCTMRLAT   0x1FU   // QEP Capture Latch
#define EQEP_O_QCPRDLAT   0x20U   // QEP Capture Period Latch


//*************************************************************************************************
//
// The following are defines for the bit fields in the QDECCTL register
//
//*************************************************************************************************
#define EQEP_QDECCTL_QSP      0x20U     // QEPS input polarity
#define EQEP_QDECCTL_QIP      0x40U     // QEPI input polarity
#define EQEP_QDECCTL_QBP      0x80U     // QEPB input polarity
#define EQEP_QDECCTL_QAP      0x100U    // QEPA input polarity
#define EQEP_QDECCTL_IGATE    0x200U    // Index pulse gating option
#define EQEP_QDECCTL_SWAP     0x400U    // CLK/DIR Signal Source for Position Counter
#define EQEP_QDECCTL_XCR      0x800U    // External Clock Rate
#define EQEP_QDECCTL_SPSEL    0x1000U   // Sync output pin selection
#define EQEP_QDECCTL_SOEN     0x2000U   // Sync output-enable
#define EQEP_QDECCTL_QSRC_S   14U
#define EQEP_QDECCTL_QSRC_M   0xC000U   // Position-counter source selection

//*************************************************************************************************
//
// The following are defines for the bit fields in the QEPCTL register
//
//*************************************************************************************************
#define EQEP_QEPCTL_WDE           0x1U      // QEP watchdog enable
#define EQEP_QEPCTL_UTE           0x2U      // QEP unit timer enable
#define EQEP_QEPCTL_QCLM          0x4U      // QEP capture latch mode
#define EQEP_QEPCTL_QPEN          0x8U      // Quadrature postotion counter enable
#define EQEP_QEPCTL_IEL_S         4U
#define EQEP_QEPCTL_IEL_M         0x30U     // Index event latch
#define EQEP_QEPCTL_SEL           0x40U     // Strobe event latch
#define EQEP_QEPCTL_SWI           0x80U     // Software init position counter
#define EQEP_QEPCTL_IEI_S         8U
#define EQEP_QEPCTL_IEI_M         0x300U    // Index event init of position count
#define EQEP_QEPCTL_SEI_S         10U
#define EQEP_QEPCTL_SEI_M         0xC00U    // Strobe event init
#define EQEP_QEPCTL_PCRM_S        12U
#define EQEP_QEPCTL_PCRM_M        0x3000U   // Postion counter reset
#define EQEP_QEPCTL_FREE_SOFT_S   14U
#define EQEP_QEPCTL_FREE_SOFT_M   0xC000U   // Emulation mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the QCAPCTL register
//
//*************************************************************************************************
#define EQEP_QCAPCTL_UPPS_S   0U
#define EQEP_QCAPCTL_UPPS_M   0xFU      // Unit position event prescaler
#define EQEP_QCAPCTL_CCPS_S   4U
#define EQEP_QCAPCTL_CCPS_M   0x70U     // eQEP capture timer clock prescaler
#define EQEP_QCAPCTL_CEN      0x8000U   // Enable eQEP capture

//*************************************************************************************************
//
// The following are defines for the bit fields in the QPOSCTL register
//
//*************************************************************************************************
#define EQEP_QPOSCTL_PCSPW_S   0U
#define EQEP_QPOSCTL_PCSPW_M   0xFFFU    // Position compare sync pulse width
#define EQEP_QPOSCTL_PCE       0x1000U   // Position compare enable/disable
#define EQEP_QPOSCTL_PCPOL     0x2000U   // Polarity of sync output
#define EQEP_QPOSCTL_PCLOAD    0x4000U   // Position compare of shadow load
#define EQEP_QPOSCTL_PCSHDW    0x8000U   // Position compare of shadow enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the QEINT register
//
//*************************************************************************************************
#define EQEP_QEINT_PCE   0x2U     // Position counter error interrupt enable
#define EQEP_QEINT_QPE   0x4U     // Quadrature phase error interrupt enable
#define EQEP_QEINT_QDC   0x8U     // Quadrature direction change interrupt enable
#define EQEP_QEINT_WTO   0x10U    // Watchdog time out interrupt enable
#define EQEP_QEINT_PCU   0x20U    // Position counter underflow interrupt enable
#define EQEP_QEINT_PCO   0x40U    // Position counter overflow interrupt enable
#define EQEP_QEINT_PCR   0x80U    // Position-compare ready interrupt enable
#define EQEP_QEINT_PCM   0x100U   // Position-compare match interrupt enable
#define EQEP_QEINT_SEL   0x200U   // Strobe event latch interrupt enable
#define EQEP_QEINT_IEL   0x400U   // Index event latch interrupt enable
#define EQEP_QEINT_UTO   0x800U   // Unit time out interrupt enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the QFLG register
//
//*************************************************************************************************
#define EQEP_QFLG_INT   0x1U     // Global interrupt status flag
#define EQEP_QFLG_PCE   0x2U     // Position counter error interrupt flag
#define EQEP_QFLG_PHE   0x4U     // Quadrature phase error interrupt flag
#define EQEP_QFLG_QDC   0x8U     // Quadrature direction change interrupt flag
#define EQEP_QFLG_WTO   0x10U    // Watchdog timeout interrupt flag
#define EQEP_QFLG_PCU   0x20U    // Position counter underflow interrupt flag
#define EQEP_QFLG_PCO   0x40U    // Position counter overflow interrupt flag
#define EQEP_QFLG_PCR   0x80U    // Position-compare ready interrupt flag
#define EQEP_QFLG_PCM   0x100U   // eQEP compare match event interrupt flag
#define EQEP_QFLG_SEL   0x200U   // Strobe event latch interrupt flag
#define EQEP_QFLG_IEL   0x400U   // Index event latch interrupt flag
#define EQEP_QFLG_UTO   0x800U   // Unit time out interrupt flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the QCLR register
//
//*************************************************************************************************
#define EQEP_QCLR_INT   0x1U     // Global interrupt clear flag
#define EQEP_QCLR_PCE   0x2U     // Clear position counter error interrupt flag
#define EQEP_QCLR_PHE   0x4U     // Clear quadrature phase error interrupt flag
#define EQEP_QCLR_QDC   0x8U     // Clear quadrature direction change interrupt flag
#define EQEP_QCLR_WTO   0x10U    // Clear watchdog timeout interrupt flag
#define EQEP_QCLR_PCU   0x20U    // Clear position counter underflow interrupt flag
#define EQEP_QCLR_PCO   0x40U    // Clear position counter overflow interrupt flag
#define EQEP_QCLR_PCR   0x80U    // Clear position-compare ready interrupt flag
#define EQEP_QCLR_PCM   0x100U   // Clear eQEP compare match event interrupt flag
#define EQEP_QCLR_SEL   0x200U   // Clear strobe event latch interrupt flag
#define EQEP_QCLR_IEL   0x400U   // Clear index event latch interrupt flag
#define EQEP_QCLR_UTO   0x800U   // Clear unit time out interrupt flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the QFRC register
//
//*************************************************************************************************
#define EQEP_QFRC_PCE   0x2U     // Force position counter error interrupt
#define EQEP_QFRC_PHE   0x4U     // Force quadrature phase error interrupt
#define EQEP_QFRC_QDC   0x8U     // Force quadrature direction change interrupt
#define EQEP_QFRC_WTO   0x10U    // Force watchdog time out interrupt
#define EQEP_QFRC_PCU   0x20U    // Force position counter underflow interrupt
#define EQEP_QFRC_PCO   0x40U    // Force position counter overflow interrupt
#define EQEP_QFRC_PCR   0x80U    // Force position-compare ready interrupt
#define EQEP_QFRC_PCM   0x100U   // Force position-compare match interrupt
#define EQEP_QFRC_SEL   0x200U   // Force strobe event latch interrupt
#define EQEP_QFRC_IEL   0x400U   // Force index event latch interrupt
#define EQEP_QFRC_UTO   0x800U   // Force unit time out interrupt

//*************************************************************************************************
//
// The following are defines for the bit fields in the QEPSTS register
//
//*************************************************************************************************
#define EQEP_QEPSTS_PCEF     0x1U    // Position counter error flag.
#define EQEP_QEPSTS_FIMF     0x2U    // First index marker flag
#define EQEP_QEPSTS_CDEF     0x4U    // Capture direction error flag
#define EQEP_QEPSTS_COEF     0x8U    // Capture overflow error flag
#define EQEP_QEPSTS_QDLF     0x10U   // eQEP direction latch flag
#define EQEP_QEPSTS_QDF      0x20U   // Quadrature direction flag
#define EQEP_QEPSTS_FIDF     0x40U   // The first index marker
#define EQEP_QEPSTS_UPEVNT   0x80U   // Unit position event flag



#endif
