// TI File $Revision: /main/1 $
// Checkin $Date: August 18, 2006   13:52:24 $
//###########################################################################
//
// FILE:   DSP2833x_PieCtrl.h
//
// TITLE:  DSP2833x Device PIE Control Register Definitions.
//
//###########################################################################
// $TI Release: 2833x/2823x Header Files V1.32 $
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

#ifndef DSP2833x_PIE_CTRL_H
#define DSP2833x_PIE_CTRL_H

#ifdef __cplusplus
extern "C" {
#endif

//
// PIE Control Register Bit Definitions
//

//
// PIECTRL: Register bit definitions
//
struct PIECTRL_BITS {       // bits description
    Uint16  ENPIE:1;        // 0    Enable PIE block
    Uint16  PIEVECT:15;     // 15:1 Fetched vector address
};

union PIECTRL_REG {
    Uint16                 all;
    struct PIECTRL_BITS  bit;
};  

//
// PIEIER: Register bit definitions
//
struct PIEIER_BITS {        // bits description
    Uint16 INTx1:1;         // 0    INTx.1
    Uint16 INTx2:1;         // 1    INTx.2
    Uint16 INTx3:1;         // 2    INTx.3
    Uint16 INTx4:1;         // 3    INTx.4
    Uint16 INTx5:1;         // 4    INTx.5
    Uint16 INTx6:1;         // 5    INTx.6
    Uint16 INTx7:1;         // 6    INTx.7
    Uint16 INTx8:1;         // 7    INTx.8
    Uint16 rsvd:8;          // 15:8 reserved
};
  
union PIEIER_REG {
    Uint16              all;
    struct PIEIER_BITS  bit;
}; 

//
// PIEIFR: Register bit definitions
//
struct PIEIFR_BITS {        // bits description
    Uint16 INTx1:1;         // 0    INTx.1
    Uint16 INTx2:1;         // 1    INTx.2
    Uint16 INTx3:1;         // 2    INTx.3
    Uint16 INTx4:1;         // 3    INTx.4
    Uint16 INTx5:1;         // 4    INTx.5
    Uint16 INTx6:1;         // 5    INTx.6
    Uint16 INTx7:1;         // 6    INTx.7
    Uint16 INTx8:1;         // 7    INTx.8
    Uint16 rsvd:8;          // 15:8 reserved
}; 

union PIEIFR_REG {
    Uint16              all;
    struct PIEIFR_BITS  bit;
};

//
// PIEACK: Register bit definitions
//
struct PIEACK_BITS {        // bits description
    Uint16 ACK1:1;          // 0    Acknowledge PIE interrupt group 1
    Uint16 ACK2:1;          // 1    Acknowledge PIE interrupt group 2
    Uint16 ACK3:1;          // 2    Acknowledge PIE interrupt group 3
    Uint16 ACK4:1;          // 3    Acknowledge PIE interrupt group 4
    Uint16 ACK5:1;          // 4    Acknowledge PIE interrupt group 5
    Uint16 ACK6:1;          // 5    Acknowledge PIE interrupt group 6
    Uint16 ACK7:1;          // 6    Acknowledge PIE interrupt group 7
    Uint16 ACK8:1;          // 7    Acknowledge PIE interrupt group 8
    Uint16 ACK9:1;          // 8    Acknowledge PIE interrupt group 9
    Uint16 ACK10:1;         // 9    Acknowledge PIE interrupt group 10
    Uint16 ACK11:1;         // 10   Acknowledge PIE interrupt group 11
    Uint16 ACK12:1;         // 11   Acknowledge PIE interrupt group 12
    Uint16 rsvd:4;          // 15:12 reserved
};

union PIEACK_REG {
    Uint16              all;
    struct PIEACK_BITS  bit;
};

//
// PIE Control Register File
//
struct PIE_CTRL_REGS {
    union PIECTRL_REG PIECTRL;       // PIE control register
    union PIEACK_REG  PIEACK;        // PIE acknowledge
    union PIEIER_REG  PIEIER1;       // PIE int1 IER register  
    union PIEIFR_REG  PIEIFR1;       // PIE int1 IFR register
    union PIEIER_REG  PIEIER2;       // PIE INT2 IER register 
    union PIEIFR_REG  PIEIFR2;       // PIE INT2 IFR register
    union PIEIER_REG  PIEIER3;       // PIE INT3 IER register 
    union PIEIFR_REG  PIEIFR3;       // PIE INT3 IFR register
    union PIEIER_REG  PIEIER4;       // PIE INT4 IER register             
    union PIEIFR_REG  PIEIFR4;       // PIE INT4 IFR register
    union PIEIER_REG  PIEIER5;       // PIE INT5 IER register  
    union PIEIFR_REG  PIEIFR5;       // PIE INT5 IFR register
    union PIEIER_REG  PIEIER6;       // PIE INT6 IER register 
    union PIEIFR_REG  PIEIFR6;       // PIE INT6 IFR register
    union PIEIER_REG  PIEIER7;       // PIE INT7 IER register 
    union PIEIFR_REG  PIEIFR7;       // PIE INT7 IFR register
    union PIEIER_REG  PIEIER8;       // PIE INT8 IER register
    union PIEIFR_REG  PIEIFR8;       // PIE INT8 IFR register
    union PIEIER_REG  PIEIER9;       // PIE INT9 IER register  
    union PIEIFR_REG  PIEIFR9;       // PIE INT9 IFR register
    union PIEIER_REG  PIEIER10;      // PIE int10 IER register 
    union PIEIFR_REG  PIEIFR10;      // PIE int10 IFR register
    union PIEIER_REG  PIEIER11;      // PIE int11 IER register 
    union PIEIFR_REG  PIEIFR11;      // PIE int11 IFR register
    union PIEIER_REG  PIEIER12;      // PIE int12 IER register
    union PIEIFR_REG  PIEIFR12;      // PIE int12 IFR register
};     

//
// Defines
//
#define PIEACK_GROUP1   0x0001
#define PIEACK_GROUP2   0x0002
#define PIEACK_GROUP3   0x0004
#define PIEACK_GROUP4   0x0008
#define PIEACK_GROUP5   0x0010
#define PIEACK_GROUP6   0x0020
#define PIEACK_GROUP7   0x0040
#define PIEACK_GROUP8   0x0080
#define PIEACK_GROUP9   0x0100
#define PIEACK_GROUP10  0x0200
#define PIEACK_GROUP11  0x0400
#define PIEACK_GROUP12  0x0800

//
// PIE Control Registers External References & Function Declarations
//
extern volatile struct PIE_CTRL_REGS PieCtrlRegs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of DSP2833x_PIE_CTRL_H definition

//
// End of file
//

