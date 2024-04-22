// TI File $Revision: /main/3 $
// Checkin $Date: April 17, 2008   11:08:27 $
//###########################################################################
//
// FILE:   DSP2833x_Spi.h
//
// TITLE:  DSP2833x Device SPI Register Definitions.
//
//###########################################################################
// $TI Release: 2833x/2823x Header Files V1.32 $
// $Release Date: June 28, 2010 $
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

#ifndef DSP2833x_SPI_H
#define DSP2833x_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

//
// SPI Individual Register Bit Definitions
//

//
// SPI FIFO Transmit register bit definitions
//
struct  SPIFFTX_BITS {        // bit    description
    Uint16 TXFFIL:5;          // 4:0    Interrupt level
    Uint16 TXFFIENA:1;        // 5      Interrupt enable
    Uint16 TXFFINTCLR:1;      // 6      Clear INT flag
    Uint16 TXFFINT:1;         // 7      INT flag
    Uint16 TXFFST:5;          // 12:8   FIFO status
    Uint16 TXFIFO:1;          // 13     FIFO reset
    Uint16 SPIFFENA:1;        // 14     Enhancement enable
    Uint16 SPIRST:1;          // 15     Reset SPI
};

union SPIFFTX_REG {
    Uint16               all;
    struct SPIFFTX_BITS  bit;
};

//
// SPI FIFO recieve register bit definitions
//
struct  SPIFFRX_BITS {        // bits   description
    Uint16 RXFFIL:5;          // 4:0    Interrupt level
    Uint16 RXFFIENA:1;        // 5      Interrupt enable
    Uint16 RXFFINTCLR:1;      // 6      Clear INT flag
    Uint16 RXFFINT:1;         // 7      INT flag
    Uint16 RXFFST:5;          // 12:8   FIFO status
    Uint16 RXFIFORESET:1;     // 13     FIFO reset
    Uint16 RXFFOVFCLR:1;      // 14     Clear overflow
    Uint16 RXFFOVF:1;         // 15     FIFO overflow
};

union SPIFFRX_REG {
    Uint16               all;
    struct SPIFFRX_BITS  bit;
};

//
// SPI FIFO control register bit definitions
//
struct  SPIFFCT_BITS {        // bits   description
    Uint16 TXDLY:8;           // 7:0    FIFO transmit delay
    Uint16 rsvd:8;            // 15:8   reserved
}; 

union SPIFFCT_REG {
    Uint16               all;
    struct SPIFFCT_BITS  bit;
};

//
// SPI configuration register bit definitions
//
struct  SPICCR_BITS {         // bits   description
    Uint16 SPICHAR:4;         // 3:0    Character length control
    Uint16 SPILBK:1;          // 4      Loop-back enable/disable
    Uint16 rsvd1:1;           // 5      reserved
    Uint16 CLKPOLARITY:1;     // 6      Clock polarity
    Uint16 SPISWRESET:1;      // 7      SPI SW Reset
    Uint16 rsvd2:8;           // 15:8   reserved
};

union SPICCR_REG {
    Uint16              all;
    struct SPICCR_BITS  bit;
};

//
// SPI operation control register bit definitions
//
struct  SPICTL_BITS {         // bits   description
    Uint16 SPIINTENA:1;       // 0      Interrupt enable
    Uint16 TALK:1;            // 1      Master/Slave transmit enable
    Uint16 MASTER_SLAVE:1;    // 2      Network control mode
    Uint16 CLK_PHASE:1;       // 3      Clock phase select
    Uint16 OVERRUNINTENA:1;   // 4      Overrun interrupt enable
    Uint16 rsvd:11;           // 15:5   reserved
};

union SPICTL_REG {
    Uint16              all;
    struct SPICTL_BITS  bit;
};

//
// SPI status register bit definitions
//
struct  SPISTS_BITS {         // bits   description
    Uint16 rsvd1:5;           // 4:0    reserved
    Uint16 BUFFULL_FLAG:1;    // 5      SPI transmit buffer full flag
    Uint16 INT_FLAG:1;        // 6      SPI interrupt flag
    Uint16 OVERRUN_FLAG:1;    // 7      SPI reciever overrun flag
    Uint16 rsvd2:8;           // 15:8   reserved
};

union SPISTS_REG {
    Uint16              all;
    struct SPISTS_BITS  bit;
};

//
// SPI priority control register bit definitions
//
struct  SPIPRI_BITS {         // bits   description
    Uint16 rsvd1:4;           // 3:0    reserved
    Uint16 FREE:1;            // 4      Free emulation mode control
    Uint16 SOFT:1;            // 5      Soft emulation mode control
    Uint16 rsvd2:1;           // 6      reserved
    Uint16 rsvd3:9;           // 15:7   reserved
};

union SPIPRI_REG {
    Uint16              all;
    struct SPIPRI_BITS  bit;
};

//
// SPI Register File
//
struct  SPI_REGS {
    union SPICCR_REG     SPICCR;      // Configuration register
    union SPICTL_REG     SPICTL;      // Operation control register
    union SPISTS_REG     SPISTS;      // Status register
    Uint16               rsvd1;       // reserved
    Uint16               SPIBRR;      // Baud Rate
    Uint16               rsvd2;       // reserved
    Uint16               SPIRXEMU;    // Emulation buffer
    Uint16               SPIRXBUF;    // Serial input buffer
    Uint16               SPITXBUF;    // Serial output buffer
    Uint16               SPIDAT;      // Serial data
    union SPIFFTX_REG    SPIFFTX;     // FIFO transmit register
    union SPIFFRX_REG    SPIFFRX;     // FIFO recieve register
    union SPIFFCT_REG    SPIFFCT;     // FIFO control register
    Uint16               rsvd3[2];    // reserved
    union SPIPRI_REG     SPIPRI;      // FIFO Priority control
};

//
// SPI External References & Function Declarations
//
extern volatile struct SPI_REGS SpiaRegs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of DSP2833x_SPI_H definition

//
// End of file
//

