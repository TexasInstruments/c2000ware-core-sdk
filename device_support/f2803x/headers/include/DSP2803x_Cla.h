//###########################################################################
//
// FILE:  DSP2803x_Cla.h
//
// TITLE: CLA Type 0 Register Definitions.
//
//###########################################################################
// $TI Release: $
// $Release Date: $
// $Copyright:
// Copyright (C) 2009-2024 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef DSP2803X_CLA_H
#define DSP2803X_CLA_H

#ifdef __cplusplus
extern "C" {
#endif

//
// CLA Control Register
//
struct MCTL_BITS {             // bits   description
    Uint16   HARDRESET:1;      // 0      Issue a hard reset
    Uint16   SOFTRESET:1;      // 1      Issue a soft reset
    Uint16   IACKE:1;          // 2      Enable IACK for task start
    Uint16   rsvd1:13;         // 15:3   reserved
};

union MCTL_REG {
    Uint16                   all;
    struct MCTL_BITS         bit;
};

//
// CLA Memory Configuration Register
//
struct MMEMCFG_BITS {          // bits   description
    Uint16   PROGE:1;          // 0      Program RAM enable
    Uint16   rsvd1:3;          // 3:1    reserved
    Uint16   RAM0E:1;          // 4      Data RAM 0 enable
    Uint16   RAM1E:1;          // 5      Data RAM 1 enable
    Uint16   rsvd2:10;         // 15:6   reserved
};

union MMEMCFG_REG {
    Uint16                   all;
    struct MMEMCFG_BITS      bit;
};

//
// CLA Peripheral Interrupt Select Register
//
struct MPISRCSEL1_BITS {        // bits     description
    Uint16   PERINT1SEL:4;      // 3:0      Source for CLA interrupt 1
    Uint16   PERINT2SEL:4;      // 7:4      Source for CLA interrupt 2
    Uint16   PERINT3SEL:4;      // 11:8     Source for CLA interrupt 3
    Uint16   PERINT4SEL:4;      // 15:12    Source for CLA interrupt 4
    Uint16   PERINT5SEL:4;      // 19:16    Source for CLA interrupt 5
    Uint16   PERINT6SEL:4;      // 23:20    Source for CLA interrupt 6
    Uint16   PERINT7SEL:4;      // 27:24    Source for CLA interrupt 7
    Uint16   PERINT8SEL:4;      // 31:28    Source for CLA interrupt 8
};

union MPISRCSEL1_REG {
    Uint32                   all;
    struct MPISRCSEL1_BITS   bit;
};

//
// CLA Interrupt Registers
//
struct MIFR_BITS {              // bits     description
    Uint16   INT1:1;            // 0        Interrupt 1 flag
    Uint16   INT2:1;            // 1        Interrupt 2 flag
    Uint16   INT3:1;            // 2        Interrupt 3 flag
    Uint16   INT4:1;            // 3        Interrupt 4 flag
    Uint16   INT5:1;            // 4        Interrupt 5 flag
    Uint16   INT6:1;            // 5        Interrupt 6 flag
    Uint16   INT7:1;            // 6        Interrupt 7 flag
    Uint16   INT8:1;            // 7        Interrupt 8 flag
    Uint16   rsvd:8;
};

union MIFR_REG {
    Uint16              all;
    struct MIFR_BITS    bit;
};

union MIOVF_REG {
    Uint16              all;
    struct MIFR_BITS    bit;
};

union MIFRC_REG {
    Uint16              all;
    struct MIFR_BITS    bit;
};

union MICLR_REG {
    Uint16              all;
    struct MIFR_BITS    bit;
};

union MICLROVF_REG {
    Uint16              all;
    struct MIFR_BITS    bit;
};

union MIER_REG {
    Uint16              all;
    struct MIFR_BITS    bit;
};

union MIRUN_REG {
    Uint16              all;
    struct MIFR_BITS    bit;
};

//
// CLA Status Register
//
struct MSTF_BITS {              // bits     description
    Uint16   LVF:1;             // 0        Latched overflow flag
    Uint16   LUF:1;             // 1        Latched underflow flag
    Uint16   NF:1;              // 2        Negative float flag
    Uint16   ZF:1;              // 3        Zero float flag
    Uint16   rsvd1:2;           // 5,4
    Uint16   TF:1;              // 6        Test flag
    Uint16   rsvd2:2;           // 8,7
    Uint16   RNDF32:1;          // 9        Rounding mode
    Uint16   rsvd3:1;           // 10
    Uint16   MEALLOW:1;         // 11       MEALLOW status
    Uint16   RPCL:4;            // 15:12    Return PC, low portion
    Uint16   RPCH:8;            // 23:16    Return PC, high portion
    Uint16   rsvd4:8;           // 31:24
};

union MSTF_REG {
    Uint32              all;
    struct MSTF_BITS    bit;
};

union MR_REG {
    Uint32              i32;
    float               f32;
};

//
// External Interrupt Register File:
//
struct CLA_REGS {
    Uint16  MVECT1;                        // Task 1 vector
    Uint16  MVECT2;                        // Task 2 vector
    Uint16  MVECT3;                        // Task 3 vector
    Uint16  MVECT4;                        // Task 4 vector
    Uint16  MVECT5;                        // Task 5 vector
    Uint16  MVECT6;                        // Task 6 vector
    Uint16  MVECT7;                        // Task 7 vector
    Uint16  MVECT8;                        // Task 8 vector
    Uint16  rsvd1[8];
    union   MCTL_REG        MCTL;          // CLA control
    union   MMEMCFG_REG     MMEMCFG;       // CLA memory configuration
    Uint16  rsvd2[2];
    union   MPISRCSEL1_REG  MPISRCSEL1;    // CLA interrupt source select
    Uint16  rsvd3[10];
    union   MIFR_REG        MIFR;          // CLA interrupt flag
    union   MIOVF_REG       MIOVF;         // CLA interrupt overflow flag
    union   MIFRC_REG       MIFRC;         // CLA interrupt force
    union   MICLR_REG       MICLR;         // CLA interrupt flag clear
    union   MICLROVF_REG    MICLROVF;      // CLA interrupt overflow flag clear
    union   MIER_REG        MIER;          // CLA interrupt enable
    union   MIRUN_REG       MIRUN;         // CLA interrupt run status
    Uint16  rsvd10;
    
    //
	// Leading _ in front of execution registers avoids
	// conflicts when using this header in assembly files
    //
    Uint16  _MPC;                         // CLA program counter
    Uint16  rsvd4;
    Uint16  _MAR0;                        // CLA auxillary register 0
    Uint16  _MAR1;                        // CLA auxillary register 1
    Uint16  rsvd5[2];
    union   MSTF_REG        _MSTF;        // CLA floating-point status register
    union   MR_REG          _MR0;         // CLA result register 0
    Uint32  rsvd6;
    union   MR_REG          _MR1;         // CLA result register 1
    Uint32  rsvd7;
    union   MR_REG          _MR2;         // CLA result register 2
    Uint32  rsvd8;
    union   MR_REG          _MR3;         // CLA result register 3
    Uint32  rsvd9;
};

//
// External Interrupt References & Function Declarations:
//
extern volatile struct CLA_REGS Cla1Regs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of DSP2803X_CLA definition

//
// End of file
//

