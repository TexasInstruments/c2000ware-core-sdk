//###########################################################################
//
// FILE:    f28p65x_uart.h
//
// TITLE:   Definitions for the UART registers.
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

#ifndef F28P65X_UART_H
#define F28P65X_UART_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// UART Individual Register Bit Definitions:

struct UARTDR_BITS {                    // bits description
    Uint16 DATA:8;                      // 7:0 Data Transmitted or Received
    Uint16 FE:1;                        // 8 UART Framing Error
    Uint16 PE:1;                        // 9 UART Parity Error
    Uint16 BE:1;                        // 10 UART Break Error
    Uint16 OE:1;                        // 11 UART Overrun Error
    Uint16 rsvd1:4;                     // 15:12 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union UARTDR_REG {
    Uint32  all;
    struct  UARTDR_BITS  bit;
};

struct UARTRSR_BITS {                   // bits description
    Uint16 FE:1;                        // 0 UART Framing Error
    Uint16 PE:1;                        // 1 UART Parity Error
    Uint16 BE:1;                        // 2 UART Break Error
    Uint16 OE:1;                        // 3 UART Overrun Error
    Uint16 rsvd1:12;                    // 15:4 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union UARTRSR_REG {
    Uint32  all;
    struct  UARTRSR_BITS  bit;
};

struct UARTFR_BITS {                    // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 rsvd2:1;                     // 1 Reserved
    Uint16 rsvd3:1;                     // 2 Reserved
    Uint16 BUSY:1;                      // 3 UART Busy
    Uint16 RXFE:1;                      // 4 UART Receive FIFO Empty
    Uint16 TXFF:1;                      // 5 UART Transmit FIFO Full
    Uint16 RXFF:1;                      // 6 UART Receive FIFO Full
    Uint16 TXFE:1;                      // 7 UART Transmit FIFO Empty
    Uint16 rsvd4:1;                     // 8 Reserved
    Uint16 rsvd5:7;                     // 15:9 Reserved
    Uint16 rsvd6:16;                    // 31:16 Reserved
};

union UARTFR_REG {
    Uint32  all;
    struct  UARTFR_BITS  bit;
};

struct UARTILPR_BITS {                  // bits description
    Uint16 ILPDVSR:8;                   // 7:0 IrDA Low-Power Divisor
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union UARTILPR_REG {
    Uint32  all;
    struct  UARTILPR_BITS  bit;
};

struct UARTIBRD_BITS {                  // bits description
    Uint16 DIVINT:16;                   // 15:0 Integer Baud-Rate Divisor
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union UARTIBRD_REG {
    Uint32  all;
    struct  UARTIBRD_BITS  bit;
};

struct UARTFBRD_BITS {                  // bits description
    Uint16 DIVFRAC:6;                   // 5:0 Fractional Baud-Rate Divisor
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union UARTFBRD_REG {
    Uint32  all;
    struct  UARTFBRD_BITS  bit;
};

struct UARTLCRH_BITS {                  // bits description
    Uint16 BRK:1;                       // 0 UART Send Break
    Uint16 PEN:1;                       // 1 UART Parity Enable
    Uint16 EPS:1;                       // 2 UART Even Parity Select
    Uint16 STP2:1;                      // 3 UART Two Stop Bits Select
    Uint16 FEN:1;                       // 4 UART Enable FIFOs
    Uint16 WLEN:2;                      // 6:5 UART Word Length
    Uint16 SPS:1;                       // 7 UART Stick Parity Select
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union UARTLCRH_REG {
    Uint32  all;
    struct  UARTLCRH_BITS  bit;
};

struct UARTCTL_BITS {                   // bits description
    Uint16 UARTEN:1;                    // 0 UART Enable
    Uint16 SIREN:1;                     // 1 UART SIR Enable
    Uint16 SIRLP:1;                     // 2 UART SIR Low-Power Mode
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 EOT:1;                       // 4 End of Transmission
    Uint16 HSE:1;                       // 5 High-Speed Enable
    Uint16 rsvd2:1;                     // 6 Reserved
    Uint16 LBE:1;                       // 7 UART Loop Back Enable
    Uint16 TXE:1;                       // 8 UART Transmit Enable
    Uint16 RXE:1;                       // 9 UART Receive Enable
    Uint16 rsvd3:1;                     // 10 Reserved
    Uint16 rsvd4:1;                     // 11 Reserved
    Uint16 rsvd5:2;                     // 13:12 Reserved
    Uint16 rsvd6:1;                     // 14 Reserved
    Uint16 rsvd7:1;                     // 15 Reserved
    Uint16 rsvd8:16;                    // 31:16 Reserved
};

union UARTCTL_REG {
    Uint32  all;
    struct  UARTCTL_BITS  bit;
};

struct UARTIFLS_BITS {                  // bits description
    Uint16 TXIFLSEL:3;                  // 2:0 UART Transmit Interrupt FIFO Level Select
    Uint16 RXIFLSEL:3;                  // 5:3 UART Receive Interrupt FIFO Level Select
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union UARTIFLS_REG {
    Uint32  all;
    struct  UARTIFLS_BITS  bit;
};

struct UARTIM_BITS {                    // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 rsvd2:1;                     // 1 Reserved
    Uint16 rsvd3:1;                     // 2 Reserved
    Uint16 rsvd4:1;                     // 3 Reserved
    Uint16 RXIM:1;                      // 4 UART Receive Interrupt Mask
    Uint16 TXIM:1;                      // 5 UART Transmit Interrupt Mask
    Uint16 RTIM:1;                      // 6 UART Receive Time-Out Interrupt Mask
    Uint16 FEIM:1;                      // 7 UART Framing Error Interrupt Mask
    Uint16 PEIM:1;                      // 8 UART Parity Error Interrupt Mask
    Uint16 BEIM:1;                      // 9 UART Break Error Interrupt Mask
    Uint16 OEIM:1;                      // 10 UART Overrun Error Interrupt Mask
    Uint16 rsvd5:1;                     // 11 Reserved
    Uint16 _9BITIM:1;                   // 12 9-Bit Mode Interrupt Mask
    Uint16 rsvd6:3;                     // 15:13 Reserved
    Uint16 DMARXIM:1;                   // 16 Receive DMA Interrupt Mask
    Uint16 DMATXIM:1;                   // 17 Transmit DMA Interrupt Mask
    Uint16 rsvd7:14;                    // 31:18 Reserved
};

union UARTIM_REG {
    Uint32  all;
    struct  UARTIM_BITS  bit;
};

struct UARTRIS_BITS {                   // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 rsvd2:1;                     // 1 Reserved
    Uint16 rsvd3:1;                     // 2 Reserved
    Uint16 rsvd4:1;                     // 3 Reserved
    Uint16 RXRIS:1;                     // 4 UART Receive Raw Interrupt Status
    Uint16 TXRIS:1;                     // 5 UART Transmit Raw Interrupt Status
    Uint16 RTRIS:1;                     // 6 UART Receive Time-Out Raw Interrupt Status
    Uint16 FERIS:1;                     // 7 UART Framing Error Raw Interrupt Status
    Uint16 PERIS:1;                     // 8 UART Parity Error Raw Interrupt Status
    Uint16 BERIS:1;                     // 9 UART Break Error Raw Interrupt Status
    Uint16 OERIS:1;                     // 10 UART Overrun Error Raw Interrupt Status
    Uint16 rsvd5:1;                     // 11 Reserved
    Uint16 _9BITRIS:1;                  // 12 9-Bit Mode Raw Interrupt Status
    Uint16 rsvd6:3;                     // 15:13 Reserved
    Uint16 DMARXRIS:1;                  // 16 Receive DMA Raw Interrupt Status
    Uint16 DMATXRIS:1;                  // 17 Transmit DMA Raw Interrupt Status
    Uint16 rsvd7:14;                    // 31:18 Reserved
};

union UARTRIS_REG {
    Uint32  all;
    struct  UARTRIS_BITS  bit;
};

struct UARTMIS_BITS {                   // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 rsvd2:1;                     // 1 Reserved
    Uint16 rsvd3:1;                     // 2 Reserved
    Uint16 rsvd4:1;                     // 3 Reserved
    Uint16 RXMIS:1;                     // 4 UART Receive Masked Interrupt Status
    Uint16 TXMIS:1;                     // 5 UART Transmit Masked Interrupt Status
    Uint16 RTMIS:1;                     // 6 UART Receive Time-Out Masked Interrupt Status
    Uint16 FEMIS:1;                     // 7 UART Framing Error Masked Interrupt Status
    Uint16 PEMIS:1;                     // 8 UART Parity Error Masked Interrupt Status
    Uint16 BEMIS:1;                     // 9 UART Break Error Masked Interrupt Status
    Uint16 OEMIS:1;                     // 10 UART Overrun Error Masked Interrupt Status
    Uint16 rsvd5:1;                     // 11 Reserved
    Uint16 _9BITMIS:1;                  // 12 9-Bit Mode Masked Interrupt Status
    Uint16 rsvd6:3;                     // 15:13 Reserved
    Uint16 DMARXMIS:1;                  // 16 Receive DMA Masked Interrupt Status
    Uint16 DMATXMIS:1;                  // 17 Transmit DMA Masked Interrupt Status
    Uint16 rsvd7:14;                    // 31:18 Reserved
};

union UARTMIS_REG {
    Uint32  all;
    struct  UARTMIS_BITS  bit;
};

struct UARTICR_BITS {                   // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 rsvd2:1;                     // 1 Reserved
    Uint16 rsvd3:1;                     // 2 Reserved
    Uint16 rsvd4:1;                     // 3 Reserved
    Uint16 RXIC:1;                      // 4 Receive Interrupt Clear
    Uint16 TXIC:1;                      // 5 Transmit Interrupt Clear
    Uint16 RTIC:1;                      // 6 Receive Time-Out Interrupt Clear
    Uint16 FEIC:1;                      // 7 Framing Error Interrupt Clear
    Uint16 PEIC:1;                      // 8 Parity Error Interrupt Clear
    Uint16 BEIC:1;                      // 9 Break Error Interrupt Clear
    Uint16 OEIC:1;                      // 10 Overrun Error Interrupt Clear
    Uint16 EOTIC:1;                     // 11 End of Transmission Interrupt Clear
    Uint16 _9BITIC:1;                   // 12 9-Bit Mode Interrupt Clear
    Uint16 rsvd5:3;                     // 15:13 Reserved
    Uint16 DMARXIC:1;                   // 16 Receive DMA Interrupt Clear
    Uint16 DMATXIC:1;                   // 17 Transmit DMA Interrupt Clear
    Uint16 rsvd6:14;                    // 31:18 Reserved
};

union UARTICR_REG {
    Uint32  all;
    struct  UARTICR_BITS  bit;
};

struct UARTDMACTL_BITS {                // bits description
    Uint16 RXDMAE:1;                    // 0 Receive DMA Enable
    Uint16 TXDMAE:1;                    // 1 Transmit DMA Enable
    Uint16 DMAERR:1;                    // 2 DMA on Error
    Uint16 rsvd1:13;                    // 15:3 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union UARTDMACTL_REG {
    Uint32  all;
    struct  UARTDMACTL_BITS  bit;
};

struct UART_GLB_INT_FLG_BITS {          // bits description
    Uint16 INT_FLG:1;                   // 0 Global Interrupt Flag for UART Interrupt
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union UART_GLB_INT_FLG_REG {
    Uint32  all;
    struct  UART_GLB_INT_FLG_BITS  bit;
};

struct UART_GLB_INT_CLR_BITS {          // bits description
    Uint16 INT_FLG_CLR:1;               // 0 Global Interrupt flag clear for UART Interrupt
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union UART_GLB_INT_CLR_REG {
    Uint32  all;
    struct  UART_GLB_INT_CLR_BITS  bit;
};

struct UART9BITADDR_BITS {              // bits description
    Uint16 ADDR:8;                      // 7:0 Self Address for 9-Bit Mode
    Uint16 rsvd1:7;                     // 14:8 Reserved
    Uint16 _9BITEN:1;                   // 15 Enable 9-Bit Mode
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union UART9BITADDR_REG {
    Uint32  all;
    struct  UART9BITADDR_BITS  bit;
};

struct UART9BITAMASK_BITS {             // bits description
    Uint16 MASK:8;                      // 7:0 Self Address Mask for 9-Bit Mode
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union UART9BITAMASK_REG {
    Uint32  all;
    struct  UART9BITAMASK_BITS  bit;
};

struct UARTPP_BITS {                    // bits description
    Uint16 SC:1;                        // 0 Smart Card Support
    Uint16 NB:1;                        // 1 9-Bit Support
    Uint16 MS:1;                        // 2 Modem Support
    Uint16 MSE:1;                       // 3 Modem Support Extended
    Uint16 rsvd1:12;                    // 15:4 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union UARTPP_REG {
    Uint32  all;
    struct  UARTPP_BITS  bit;
};

struct UARTPeriphID4_BITS {             // bits description
    Uint16 PID4:8;                      // 7:0 UART Peripheral ID Register [7:0]
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union UARTPeriphID4_REG {
    Uint32  all;
    struct  UARTPeriphID4_BITS  bit;
};

struct UARTPeriphID5_BITS {             // bits description
    Uint16 PID5:8;                      // 7:0 UART Peripheral ID Register [15:8]
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union UARTPeriphID5_REG {
    Uint32  all;
    struct  UARTPeriphID5_BITS  bit;
};

struct UARTPeriphID6_BITS {             // bits description
    Uint16 PID6:8;                      // 7:0 UART Peripheral ID Register [23:16]
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union UARTPeriphID6_REG {
    Uint32  all;
    struct  UARTPeriphID6_BITS  bit;
};

struct UARTPeriphID7_BITS {             // bits description
    Uint16 PID7:8;                      // 7:0 UART Peripheral ID Register [31:24]
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union UARTPeriphID7_REG {
    Uint32  all;
    struct  UARTPeriphID7_BITS  bit;
};

struct UARTPeriphID0_BITS {             // bits description
    Uint16 PID0:8;                      // 7:0 UART Peripheral ID Register [7:0]
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union UARTPeriphID0_REG {
    Uint32  all;
    struct  UARTPeriphID0_BITS  bit;
};

struct UARTPeriphID1_BITS {             // bits description
    Uint16 PID1:8;                      // 7:0 UART Peripheral ID Register [15:8]
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union UARTPeriphID1_REG {
    Uint32  all;
    struct  UARTPeriphID1_BITS  bit;
};

struct UARTPeriphID2_BITS {             // bits description
    Uint16 PID2:8;                      // 7:0 UART Peripheral ID Register [23:16]
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union UARTPeriphID2_REG {
    Uint32  all;
    struct  UARTPeriphID2_BITS  bit;
};

struct UARTPeriphID3_BITS {             // bits description
    Uint16 PID3:8;                      // 7:0 UART Peripheral ID Register [31:24]
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union UARTPeriphID3_REG {
    Uint32  all;
    struct  UARTPeriphID3_BITS  bit;
};

struct UARTPCellID0_BITS {              // bits description
    Uint16 CID0:8;                      // 7:0 UART PrimeCell ID Register [7:0]
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union UARTPCellID0_REG {
    Uint32  all;
    struct  UARTPCellID0_BITS  bit;
};

struct UARTPCellID1_BITS {              // bits description
    Uint16 CID1:8;                      // 7:0 UART PrimeCell ID Register [15:8]
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union UARTPCellID1_REG {
    Uint32  all;
    struct  UARTPCellID1_BITS  bit;
};

struct UARTPCellID2_BITS {              // bits description
    Uint16 CID2:8;                      // 7:0 UART PrimeCell ID Register [23:16]
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union UARTPCellID2_REG {
    Uint32  all;
    struct  UARTPCellID2_BITS  bit;
};

struct UARTPCellID3_BITS {              // bits description
    Uint16 CID3:8;                      // 7:0 UART PrimeCell ID Register [31:24]
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union UARTPCellID3_REG {
    Uint32  all;
    struct  UARTPCellID3_BITS  bit;
};

struct UART_REGS {
    union   UARTDR_REG                       UARTDR;                       // UART Data
    union   UARTRSR_REG                      UARTRSR;                      // UART Receive Status/Error Clear
    Uint16                                   rsvd1[8];                     // Reserved
    union   UARTFR_REG                       UARTFR;                       // UART Flag
    Uint16                                   rsvd2[2];                     // Reserved
    union   UARTILPR_REG                     UARTILPR;                     // UART IrDA Low-Power Register
    union   UARTIBRD_REG                     UARTIBRD;                     // UART Integer Baud-Rate Divisor
    union   UARTFBRD_REG                     UARTFBRD;                     // UART Fractional Baud-Rate Divisor
    union   UARTLCRH_REG                     UARTLCRH;                     // UART Line Control
    union   UARTCTL_REG                      UARTCTL;                      // UART Control
    union   UARTIFLS_REG                     UARTIFLS;                     // UART Interrupt FIFO Level Select
    union   UARTIM_REG                       UARTIM;                       // UART Interrupt Mask
    union   UARTRIS_REG                      UARTRIS;                      // UART Raw Interrupt Status
    union   UARTMIS_REG                      UARTMIS;                      // UART Masked Interrupt Status
    union   UARTICR_REG                      UARTICR;                      // UART Interrupt Clear
    union   UARTDMACTL_REG                   UARTDMACTL;                   // UART DMA Control
    Uint16                                   rsvd3[28];                    // Reserved
    union   UART_GLB_INT_FLG_REG             UART_GLB_INT_FLG;             // UART Global Interrupt Flag Register
    union   UART_GLB_INT_CLR_REG             UART_GLB_INT_CLR;             // UART Global Interrupt Clear Register
    Uint16                                   rsvd4[12];                    // Reserved
    union   UART9BITADDR_REG                 UART9BITADDR;                 // UART 9-Bit Self Address
    union   UART9BITAMASK_REG                UART9BITAMASK;                // UART 9-Bit Self Address Mask
    Uint16                                   rsvd5[1930];                  // Reserved
    union   UARTPP_REG                       UARTPP;                       // UART Peripheral Properties
    Uint16                                   rsvd6[6];                     // Reserved
    union   UARTPeriphID4_REG                UARTPeriphID4;                // UART Peripheral Identification 4
    union   UARTPeriphID5_REG                UARTPeriphID5;                // UART Peripheral Identification 5
    union   UARTPeriphID6_REG                UARTPeriphID6;                // UART Peripheral Identification 6
    union   UARTPeriphID7_REG                UARTPeriphID7;                // UART Peripheral Identification 7
    union   UARTPeriphID0_REG                UARTPeriphID0;                // UART Peripheral Identification 0
    union   UARTPeriphID1_REG                UARTPeriphID1;                // UART Peripheral Identification 1
    union   UARTPeriphID2_REG                UARTPeriphID2;                // UART Peripheral Identification 2
    union   UARTPeriphID3_REG                UARTPeriphID3;                // UART Peripheral Identification 3
    union   UARTPCellID0_REG                 UARTPCellID0;                 // UART PrimeCell Identification 0
    union   UARTPCellID1_REG                 UARTPCellID1;                 // UART PrimeCell Identification 1
    union   UARTPCellID2_REG                 UARTPCellID2;                 // UART PrimeCell Identification 2
    union   UARTPCellID3_REG                 UARTPCellID3;                 // UART PrimeCell Identification 3
};

struct UARTECR_BITS {                   // bits description
    Uint16 DATA:8;                      // 7:0 Error Clear
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union UARTECR_REG {
    Uint32  all;
    struct  UARTECR_BITS  bit;
};

struct UART_REGS_WRITE {
    Uint16                                   rsvd1[2];                     // Reserved
    union   UARTECR_REG                      UARTECR;                      // UART Error Clear
};

//---------------------------------------------------------------------------
// UART External References & Function Declarations:
//
#ifdef CPU1
extern volatile struct UART_REGS UartARegs;
extern volatile struct UART_REGS UartBRegs;
#endif
#ifdef CPU2
extern volatile struct UART_REGS UartARegs;
extern volatile struct UART_REGS UartBRegs;
#endif
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
