// TI File $Revision: /main/1 $
// Checkin $Date: August 18, 2006   13:52:13 $
//###########################################################################
//
// FILE:   DSP2823x_EQep.h
//
// TITLE:  DSP2823x Enhanced Quadrature Encoder Pulse Module 
//         Register Bit Definitions.
//
//###########################################################################
// $TI Release: 2823x/2823x Header Files V1.32 $
// $Release Date: June 28, 2010 $
// $Copyright:
// Copyright (C) 2009-2025 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef DSP2823x_EQEP_H
#define DSP2823x_EQEP_H


#ifdef __cplusplus
extern "C" {
#endif

//
// Capture decoder control register bit definitions
//
struct QDECCTL_BITS {       // bits  description
    Uint16 rsvd1:5;         // 4:0   reserved
    Uint16 QSP:1;           // 5     QEPS input polarity
    Uint16 QIP:1;           // 6     QEPI input polarity
    Uint16 QBP:1;           // 7     QEPB input polarity
    Uint16 QAP:1;           // 8     QEPA input polarity
    Uint16 IGATE:1;         // 9     Index pulse gating option
    Uint16 SWAP:1;          // 10    CLK/DIR signal source for Position Counter
    Uint16 XCR:1;           // 11    External clock rate
    Uint16 SPSEL:1;         // 12    Sync output pin select
    Uint16 SOEN:1;          // 13    Enable position compare sync
    Uint16 QSRC:2;          // 15:14 Position counter source
};

union QDECCTL_REG {
    Uint16              all;
    struct QDECCTL_BITS   bit;
};

//
// QEP control register bit definitions
//
struct QEPCTL_BITS {            // bits   description
    Uint16 WDE:1;               // 0      QEP watchdog enable
    Uint16 UTE:1;               // 1      QEP unit timer enable
    Uint16 QCLM:1;              // 2      QEP capture latch mode
    Uint16 QPEN:1;              // 3      Quadrature position counter enable
    Uint16 IEL:2;               // 5:4    Index event latch
    Uint16 SEL:1;               // 6      Strobe event latch
    Uint16 SWI:1;               // 7      Software init position counter
    Uint16 IEI:2;               // 9:8    Index event init of position count
    Uint16 SEI:2;               // 11:10  Strobe event init
    Uint16 PCRM:2;              // 13:12  Position counter reset
    Uint16 FREE_SOFT:2;         // 15:14  Emulation mode
};

union QEPCTL_REG {
    Uint16               all;
    struct QEPCTL_BITS   bit;
};         

//
// Quadrature capture control register bit definitions
//
struct QCAPCTL_BITS {          // bits   description
    Uint16 UPPS:4;              // 3:0    Unit position pre-scale         
    Uint16 CCPS:3;              // 6:4    QEP capture timer pre-scale
    Uint16 rsvd1:8;             // 14:7   reserved
    Uint16 CEN:1;               // 15     Enable QEP capture
};

union QCAPCTL_REG {
    Uint16               all;
    struct QCAPCTL_BITS  bit;
}; 

//
// Position compare control register bit definitions
//
struct QPOSCTL_BITS {           // bits   description
    Uint16 PCSPW:12;            // 11:0   Position compare sync pulse width
    Uint16 PCE:1;               // 12     Position compare enable/disable
    Uint16 PCPOL:1;             // 13     Polarity of sync output
    Uint16 PCLOAD:1;            // 14     Position compare of shadow load
    Uint16 PCSHDW:1;            // 15     Position compare shadow enable
};

union QPOSCTL_REG {
    Uint16               all;
    struct QPOSCTL_BITS  bit;
};         

//
// QEP interrupt control register bit definitions
//
struct QEINT_BITS {           // bits   description
    Uint16 rsvd1:1;           // 0      reserved
    Uint16 PCE:1;             // 1      Position counter error
    Uint16 QPE:1;             // 2      Quadrature phase error
    Uint16 QDC:1;             // 3      Quadrature dir change
    Uint16 WTO:1;             // 4      Watchdog timeout
    Uint16 PCU:1;             // 5      Position counter underflow
    Uint16 PCO:1;             // 6      Position counter overflow
    Uint16 PCR:1;             // 7      Position compare ready
    Uint16 PCM:1;             // 8      Position compare match
    Uint16 SEL:1;             // 9      Strobe event latch
    Uint16 IEL:1;             // 10     Event latch
    Uint16 UTO:1;             // 11     Unit timeout
    Uint16 rsvd2:4;           // 15:12  reserved
};

union QEINT_REG {
    Uint16               all;
    struct QEINT_BITS    bit;
};

//
// QEP interrupt status register bit definitions
//
struct QFLG_BITS {           // bits   description
    Uint16 INT:1;            // 0      Global interrupt 
    Uint16 PCE:1;            // 1      Position counter error
    Uint16 PHE:1;            // 2      Quadrature phase error
    Uint16 QDC:1;            // 3      Quadrature dir change
    Uint16 WTO:1;            // 4      Watchdog timeout
    Uint16 PCU:1;            // 5      Position counter underflow
    Uint16 PCO:1;            // 6      Position counter overflow
    Uint16 PCR:1;            // 7      Position compare ready
    Uint16 PCM:1;            // 8      Position compare match
    Uint16 SEL:1;            // 9      Strobe event latch
    Uint16 IEL:1;            // 10     Event latch
    Uint16 UTO:1;            // 11     Unit timeout
    Uint16 rsvd2:4;          // 15:12  reserved
};

union QFLG_REG {
    Uint16               all;
    struct QFLG_BITS     bit;
};

//
// QEP interrupt force register bit definitions
//
struct QFRC_BITS {           // bits   description
    Uint16 reserved:1;       // 0      Reserved
    Uint16 PCE:1;            // 1      Position counter error
    Uint16 PHE:1;            // 2      Quadrature phase error
    Uint16 QDC:1;            // 3      Quadrature dir change
    Uint16 WTO:1;            // 4      Watchdog timeout
    Uint16 PCU:1;            // 5      Position counter underflow
    Uint16 PCO:1;            // 6      Position counter overflow
    Uint16 PCR:1;            // 7      Position compare ready
    Uint16 PCM:1;            // 8      Position compare match
    Uint16 SEL:1;            // 9      Strobe event latch
    Uint16 IEL:1;            // 10     Event latch
    Uint16 UTO:1;            // 11     Unit timeout
    Uint16 rsvd2:4;          // 15:12  reserved
};


union QFRC_REG {
    Uint16               all;
    struct QFRC_BITS     bit;
};

//
// V1.1 Added UPEVNT (bit 7) This reflects changes 
// made as of F2823x Rev A devices
//

//
// QEP status register bit definitions
//
struct QEPSTS_BITS {           // bits   description
    Uint16 PCEF:1;             // 0      Position counter error
    Uint16 FIMF:1;             // 1      First index marker
    Uint16 CDEF:1;             // 2      Capture direction error
    Uint16 COEF:1;             // 3      Capture overflow error
    Uint16 QDLF:1;             // 4      QEP direction latch
    Uint16 QDF:1;              // 5      Quadrature direction
    Uint16 FIDF:1;             // 6      Direction on first index marker
    Uint16 UPEVNT:1;           // 7      Unit position event flag
    Uint16 rsvd1:8;            // 15:8   reserved
};

union QEPSTS_REG {
    Uint16               all;
    struct QEPSTS_BITS   bit;
};

struct EQEP_REGS {
    Uint32              QPOSCNT;   // Position counter 
    Uint32              QPOSINIT;  // Position counter init
    Uint32              QPOSMAX;   // Maximum position count
    Uint32              QPOSCMP;   // Position compare
    Uint32              QPOSILAT;  // Index position latch
    Uint32              QPOSSLAT;  // Strobe position latch
    Uint32              QPOSLAT;   // Position latch
    Uint32              QUTMR;     // Unit timer
    Uint32              QUPRD;     // Unit period
    Uint16              QWDTMR;    // QEP watchdog timer
    Uint16              QWDPRD;    // QEP watchdog period
    union  QDECCTL_REG  QDECCTL;   // Quadrature decoder control
    union  QEPCTL_REG   QEPCTL;    // QEP control 
    union  QCAPCTL_REG  QCAPCTL;   // Quadrature capture control     
    union  QPOSCTL_REG  QPOSCTL;   // Position compare control
    union  QEINT_REG    QEINT;     // QEP interrupt control        
    union  QFLG_REG     QFLG;      // QEP interrupt flag
    union  QFLG_REG     QCLR;      // QEP interrupt clear                   
    union  QFRC_REG     QFRC;      // QEP interrupt force                   
    union  QEPSTS_REG   QEPSTS;    // QEP status
    Uint16              QCTMR;     // QEP capture timer
    Uint16              QCPRD;     // QEP capture period
    Uint16              QCTMRLAT;  // QEP capture latch
    Uint16              QCPRDLAT;  // QEP capture period latch
    Uint16              rsvd1[30]; // reserved
};

//
// GPI/O External References & Function Declarations
//
extern volatile struct EQEP_REGS EQep1Regs;
extern volatile struct EQEP_REGS EQep2Regs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of DSP2823x_EQEP_H definition

//
// End of file
//

