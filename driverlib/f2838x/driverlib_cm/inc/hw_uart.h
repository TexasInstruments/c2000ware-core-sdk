//###########################################################################
//
// FILE:    hw_uart.h
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

#ifndef HW_UART_H
#define HW_UART_H

//*************************************************************************************************
//
// The following are defines for the UART register offsets
//
//*************************************************************************************************
#define UART_O_DR          0x0U     // UART Data
#define UART_O_RSR         0x4U     // UART Receive Status/Error Clear
#define UART_O_FR          0x18U    // UART Flag
#define UART_O_ILPR        0x20U    // UART IrDA Low-Power Register
#define UART_O_IBRD        0x24U    // UART Integer Baud-Rate Divisor
#define UART_O_FBRD        0x28U    // UART Fractional Baud-Rate Divisor
#define UART_O_LCRH        0x2CU    // UART Line Control
#define UART_O_CTL         0x30U    // UART Control
#define UART_O_IFLS        0x34U    // UART Interrupt FIFO Level Select
#define UART_O_IM          0x38U    // UART Interrupt Mask
#define UART_O_RIS         0x3CU    // UART Raw Interrupt Status
#define UART_O_MIS         0x40U    // UART Masked Interrupt Status
#define UART_O_ICR         0x44U    // UART Interrupt Clear
#define UART_O_DMACTL      0x48U    // UART DMA Control
#define UART_O_9BITADDR    0xA4U    // UART 9-Bit Self Address
#define UART_O_9BITAMASK   0xA8U    // UART 9-Bit Self Address Mask
#define UART_O_PP          0xFC0U   // UART Peripheral Properties
#define UART_O_PERIPHID4   0xFD0U   // UART Peripheral Identification 4
#define UART_O_PERIPHID5   0xFD4U   // UART Peripheral Identification 5
#define UART_O_PERIPHID6   0xFD8U   // UART Peripheral Identification 6
#define UART_O_PERIPHID7   0xFDCU   // UART Peripheral Identification 7
#define UART_O_PERIPHID0   0xFE0U   // UART Peripheral Identification 0
#define UART_O_PERIPHID1   0xFE4U   // UART Peripheral Identification 1
#define UART_O_PERIPHID2   0xFE8U   // UART Peripheral Identification 2
#define UART_O_PERIPHID3   0xFECU   // UART Peripheral Identification 3
#define UART_O_PCELLID0    0xFF0U   // UART PrimeCell Identification 0
#define UART_O_PCELLID1    0xFF4U   // UART PrimeCell Identification 1
#define UART_O_PCELLID2    0xFF8U   // UART PrimeCell Identification 2
#define UART_O_PCELLID3    0xFFCU   // UART PrimeCell Identification 3

#define UART_O_ECR   0x4U   // UART Error Clear


//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTDR register
//
//*************************************************************************************************
#define UART_DR_DATA_S   0U
#define UART_DR_DATA_M   0xFFU    // Data Transmitted or Received
#define UART_DR_FE       0x100U   // UART Framing Error
#define UART_DR_PE       0x200U   // UART Parity Error
#define UART_DR_BE       0x400U   // UART Break Error
#define UART_DR_OE       0x800U   // UART Overrun Error

//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTRSR register
//
//*************************************************************************************************
#define UART_RSR_FE   0x1U   // UART Framing Error
#define UART_RSR_PE   0x2U   // UART Parity Error
#define UART_RSR_BE   0x4U   // UART Break Error
#define UART_RSR_OE   0x8U   // UART Overrun Error

//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTFR register
//
//*************************************************************************************************
#define UART_FR_BUSY   0x8U    // UART Busy
#define UART_FR_RXFE   0x10U   // UART Receive FIFO Empty
#define UART_FR_TXFF   0x20U   // UART Transmit FIFO Full
#define UART_FR_RXFF   0x40U   // UART Receive FIFO Full
#define UART_FR_TXFE   0x80U   // UART Transmit FIFO Empty

//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTILPR register
//
//*************************************************************************************************
#define UART_ILPR_ILPDVSR_S   0U
#define UART_ILPR_ILPDVSR_M   0xFFU   // IrDA Low-Power Divisor

//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTIBRD register
//
//*************************************************************************************************
#define UART_IBRD_DIVINT_S   0U
#define UART_IBRD_DIVINT_M   0xFFFFU   // Integer Baud-Rate Divisor

//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTFBRD register
//
//*************************************************************************************************
#define UART_FBRD_DIVFRAC_S   0U
#define UART_FBRD_DIVFRAC_M   0x3FU   // Fractional Baud-Rate Divisor

//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTLCRH register
//
//*************************************************************************************************
#define UART_LCRH_BRK      0x1U    // UART Send Break
#define UART_LCRH_PEN      0x2U    // UART Parity Enable
#define UART_LCRH_EPS      0x4U    // UART Even Parity Select
#define UART_LCRH_STP2     0x8U    // UART Two Stop Bits Select
#define UART_LCRH_FEN      0x10U   // UART Enable FIFOs
#define UART_LCRH_WLEN_S   5U
#define UART_LCRH_WLEN_M   0x60U   // UART Word Length
#define UART_LCRH_SPS      0x80U   // UART Stick Parity Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTCTL register
//
//*************************************************************************************************
#define UART_CTL_UARTEN   0x1U     // UART Enable
#define UART_CTL_SIREN    0x2U     // UART SIR Enable
#define UART_CTL_SIRLP    0x4U     // UART SIR Low-Power Mode
#define UART_CTL_EOT      0x10U    // End of Transmission
#define UART_CTL_HSE      0x20U    // High-Speed Enable
#define UART_CTL_LBE      0x80U    // UART Loop Back Enable
#define UART_CTL_TXE      0x100U   // UART Transmit Enable
#define UART_CTL_RXE      0x200U   // UART Receive Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTIFLS register
//
//*************************************************************************************************
#define UART_IFLS_TXIFLSEL_S   0U
#define UART_IFLS_TXIFLSEL_M   0x7U    // UART Transmit Interrupt FIFO Level Select
#define UART_IFLS_RXIFLSEL_S   3U
#define UART_IFLS_RXIFLSEL_M   0x38U   // UART Receive Interrupt FIFO Level Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTIM register
//
//*************************************************************************************************
#define UART_IM_RXIM      0x10U      // UART Receive Interrupt Mask
#define UART_IM_TXIM      0x20U      // UART Transmit Interrupt Mask
#define UART_IM_RTIM      0x40U      // UART Receive Time-Out Interrupt Mask
#define UART_IM_FEIM      0x80U      // UART Framing Error Interrupt Mask
#define UART_IM_PEIM      0x100U     // UART Parity Error Interrupt Mask
#define UART_IM_BEIM      0x200U     // UART Break Error Interrupt Mask
#define UART_IM_OEIM      0x400U     // UART Overrun Error Interrupt Mask
#define UART_IM_9BITIM    0x1000U    // 9-Bit Mode Interrupt Mask
#define UART_IM_DMARXIM   0x10000U   // Receive DMA Interrupt Mask
#define UART_IM_DMATXIM   0x20000U   // Transmit DMA Interrupt Mask

//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTRIS register
//
//*************************************************************************************************
#define UART_RIS_RXRIS      0x10U      // UART Receive Raw Interrupt Status
#define UART_RIS_TXRIS      0x20U      // UART Transmit Raw Interrupt Status
#define UART_RIS_RTRIS      0x40U      // UART Receive Time-Out Raw Interrupt Status
#define UART_RIS_FERIS      0x80U      // UART Framing Error Raw Interrupt Status
#define UART_RIS_PERIS      0x100U     // UART Parity Error Raw Interrupt Status
#define UART_RIS_BERIS      0x200U     // UART Break Error Raw Interrupt Status
#define UART_RIS_OERIS      0x400U     // UART Overrun Error Raw Interrupt Status
#define UART_RIS_9BITRIS    0x1000U    // 9-Bit Mode Raw Interrupt Status
#define UART_RIS_DMARXRIS   0x10000U   // Receive DMA Raw Interrupt Status
#define UART_RIS_DMATXRIS   0x20000U   // Transmit DMA Raw Interrupt Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTMIS register
//
//*************************************************************************************************
#define UART_MIS_RXMIS      0x10U      // UART Receive Masked Interrupt Status
#define UART_MIS_TXMIS      0x20U      // UART Transmit Masked Interrupt Status
#define UART_MIS_RTMIS      0x40U      // UART Receive Time-Out Masked Interrupt Status
#define UART_MIS_FEMIS      0x80U      // UART Framing Error Masked Interrupt Status
#define UART_MIS_PEMIS      0x100U     // UART Parity Error Masked Interrupt Status
#define UART_MIS_BEMIS      0x200U     // UART Break Error Masked Interrupt Status
#define UART_MIS_OEMIS      0x400U     // UART Overrun Error Masked Interrupt Status
#define UART_MIS_9BITMIS    0x1000U    // 9-Bit Mode Masked Interrupt Status
#define UART_MIS_DMARXMIS   0x10000U   // Receive DMA Masked Interrupt Status
#define UART_MIS_DMATXMIS   0x20000U   // Transmit DMA Masked Interrupt Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTICR register
//
//*************************************************************************************************
#define UART_ICR_RXIC      0x10U      // Receive Interrupt Clear
#define UART_ICR_TXIC      0x20U      // Transmit Interrupt Clear
#define UART_ICR_RTIC      0x40U      // Receive Time-Out Interrupt Clear
#define UART_ICR_FEIC      0x80U      // Framing Error Interrupt Clear
#define UART_ICR_PEIC      0x100U     // Parity Error Interrupt Clear
#define UART_ICR_BEIC      0x200U     // Break Error Interrupt Clear
#define UART_ICR_OEIC      0x400U     // Overrun Error Interrupt Clear
#define UART_ICR_EOTIC     0x800U     // End of Transmission Interrupt Clear
#define UART_ICR_9BITIC    0x1000U    // 9-Bit Mode Interrupt Clear
#define UART_ICR_DMARXIC   0x10000U   // Receive DMA Interrupt Clear
#define UART_ICR_DMATXIC   0x20000U   // Transmit DMA Interrupt Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTDMACTL register
//
//*************************************************************************************************
#define UART_DMACTL_RXDMAE   0x1U   // Receive DMA Enable
#define UART_DMACTL_TXDMAE   0x2U   // Transmit DMA Enable
#define UART_DMACTL_DMAERR   0x4U   // DMA on Error

//*************************************************************************************************
//
// The following are defines for the bit fields in the UART9BITADDR register
//
//*************************************************************************************************
#define UART_9BITADDR_ADDR_S   0U
#define UART_9BITADDR_ADDR_M   0xFFU     // Self Address for 9-Bit Mode
#define UART_9BITADDR_9BITEN   0x8000U   // Enable 9-Bit Mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the UART9BITAMASK register
//
//*************************************************************************************************
#define UART_9BITAMASK_MASK_S   0U
#define UART_9BITAMASK_MASK_M   0xFFU   // Self Address Mask for 9-Bit Mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTPP register
//
//*************************************************************************************************
#define UART_PP_SC    0x1U   // Smart Card Support
#define UART_PP_NB    0x2U   // 9-Bit Support
#define UART_PP_MS    0x4U   // Modem Support
#define UART_PP_MSE   0x8U   // Modem Support Extended

//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTPeriphID4 register
//
//*************************************************************************************************
#define UART_PERIPHID4_PID4_S   0U
#define UART_PERIPHID4_PID4_M   0xFFU   // UART Peripheral ID Register [7:0]

//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTPeriphID5 register
//
//*************************************************************************************************
#define UART_PERIPHID5_PID5_S   0U
#define UART_PERIPHID5_PID5_M   0xFFU   // UART Peripheral ID Register [15:8]

//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTPeriphID6 register
//
//*************************************************************************************************
#define UART_PERIPHID6_PID6_S   0U
#define UART_PERIPHID6_PID6_M   0xFFU   // UART Peripheral ID Register [23:16]

//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTPeriphID7 register
//
//*************************************************************************************************
#define UART_PERIPHID7_PID7_S   0U
#define UART_PERIPHID7_PID7_M   0xFFU   // UART Peripheral ID Register [31:24]

//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTPeriphID0 register
//
//*************************************************************************************************
#define UART_PERIPHID0_PID0_S   0U
#define UART_PERIPHID0_PID0_M   0xFFU   // UART Peripheral ID Register [7:0]

//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTPeriphID1 register
//
//*************************************************************************************************
#define UART_PERIPHID1_PID1_S   0U
#define UART_PERIPHID1_PID1_M   0xFFU   // UART Peripheral ID Register [15:8]

//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTPeriphID2 register
//
//*************************************************************************************************
#define UART_PERIPHID2_PID2_S   0U
#define UART_PERIPHID2_PID2_M   0xFFU   // UART Peripheral ID Register [23:16]

//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTPeriphID3 register
//
//*************************************************************************************************
#define UART_PERIPHID3_PID3_S   0U
#define UART_PERIPHID3_PID3_M   0xFFU   // UART Peripheral ID Register [31:24]

//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTPCellID0 register
//
//*************************************************************************************************
#define UART_PCELLID0_CID0_S   0U
#define UART_PCELLID0_CID0_M   0xFFU   // UART PrimeCell ID Register [7:0]

//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTPCellID1 register
//
//*************************************************************************************************
#define UART_PCELLID1_CID1_S   0U
#define UART_PCELLID1_CID1_M   0xFFU   // UART PrimeCell ID Register [15:8]

//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTPCellID2 register
//
//*************************************************************************************************
#define UART_PCELLID2_CID2_S   0U
#define UART_PCELLID2_CID2_M   0xFFU   // UART PrimeCell ID Register [23:16]

//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTPCellID3 register
//
//*************************************************************************************************
#define UART_PCELLID3_CID3_S   0U
#define UART_PCELLID3_CID3_M   0xFFU   // UART PrimeCell ID Register [31:24]


//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTECR register
//
//*************************************************************************************************
#define UART_ECR_DATA_S   0U
#define UART_ECR_DATA_M   0xFFU   // Error Clear



#endif
