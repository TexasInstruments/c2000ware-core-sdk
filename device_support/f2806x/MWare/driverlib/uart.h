//###########################################################################
//
// FILE:   uart.h
//
// TITLE:  Stellaris style wrapper driver for C28x SCI peripheral.
//
//###########################################################################
// $TI Release: f2806x Support Library v1.15 $
// $Release Date: December 12, 2011 $
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

#ifndef __UART_H__
#define __UART_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// Values that can be passed to UARTIntEnable, UARTIntDisable, and UARTIntClear
// as the ulIntFlags parameter, and returned from UARTIntStatus.
//
//*****************************************************************************
#define UART_INT_RXERR          0x01
#define UART_INT_RXRDY_BRKDT    0x02
#define UART_INT_TXRDY          0x04
#define UART_INT_TXFF           0x08
#define UART_INT_RXFF           0x10

//*****************************************************************************
//
// Values that can be passed to UARTConfigSetExpClk as the ulConfig parameter
// and returned by UARTConfigGetExpClk in the pulConfig parameter.
// Additionally, the UART_CONFIG_PAR_* subset can be passed to
// UARTParityModeSet as the ulParity parameter, and are returned by
// UARTParityModeGet.
//
//*****************************************************************************
#define UART_CONFIG_WLEN_MASK   0x00000007  // Mask for extracting word length
#define UART_CONFIG_WLEN_8      0x00000007  // 8 bit data
#define UART_CONFIG_WLEN_7      0x00000006  // 7 bit data
#define UART_CONFIG_WLEN_6      0x00000005  // 6 bit data
#define UART_CONFIG_WLEN_5      0x00000004  // 5 bit data
#define UART_CONFIG_STOP_MASK   0x00000080  // Mask for extracting stop bits
#define UART_CONFIG_STOP_ONE    0x00000000  // One stop bit
#define UART_CONFIG_STOP_TWO    0x00000080  // Two stop bits
#define UART_CONFIG_PAR_MASK    0x00000060  // Parity Mask
#define UART_CONFIG_PAR_NONE    0x00000000  // No parity
#define UART_CONFIG_PAR_EVEN    0x00000060  // Even parity
#define UART_CONFIG_PAR_ODD     0x00000020  // Odd parity
#define UART_CONFIG_PAR_ONE     0x00000020  // Parity bit is one
#define UART_CONFIG_PAR_ZERO    0x00000060  // Parity bit is zero

//*****************************************************************************
//
// Values that can be passed to UARTFIFOLevelSet as the ulTxLevel parameter and
// returned by UARTFIFOLevelGet in the pulTxLevel.
//
//*****************************************************************************
#define UART_FIFO_TX1_8         0x00000001  // Transmit interrupt at 1/4 Full
#define UART_FIFO_TX2_8         0x00000002  // Transmit interrupt at 1/2 Full
#define UART_FIFO_TX4_8         0x00000003  // Transmit interrupt at 3/4 Full
#define UART_FIFO_TX6_8         0x00000004  // Transmit interrupt Full

//*****************************************************************************
//
// Values that can be passed to UARTFIFOLevelSet as the ulRxLevel parameter and
// returned by UARTFIFOLevelGet in the pulRxLevel.
//
//*****************************************************************************
#define UART_FIFO_RX1_8         0x00000001  // Receive interrupt at 1/4 Full
#define UART_FIFO_RX2_8         0x00000002  // Receive interrupt at 1/2 Full
#define UART_FIFO_RX4_8         0x00000003  // Receive interrupt at 3/4 Full
#define UART_FIFO_RX6_8         0x00000004  // Receive interrupt at Full

//*****************************************************************************
//
// Values that can be passed to UARTDMAEnable() and UARTDMADisable().
//
//*****************************************************************************
#define UART_DMA_ERR_RXSTOP     0x00000004  // Stop DMA receive if UART error
#define UART_DMA_TX             0x00000002  // Enable DMA for transmit
#define UART_DMA_RX             0x00000001  // Enable DMA for receive

//*****************************************************************************
//
// Values returned from UARTRxErrorGet().
//
//*****************************************************************************
#define UART_RXERROR_OVERRUN    0x00000008
#define UART_RXERROR_BREAK      0x00000020
#define UART_RXERROR_PARITY     0x00000004
#define UART_RXERROR_FRAMING    0x00000010

//*****************************************************************************
//
// Values that can be passed to UARTHandshakeOutputsSet() or returned from
// UARTHandshakeOutputGet().
//
//*****************************************************************************
#define UART_OUTPUT_RTS         0x00000800
#define UART_OUTPUT_DTR         0x00000400

//*****************************************************************************
//
// Values that can be returned from UARTHandshakeInputsGet().
//
//*****************************************************************************
#define UART_INPUT_RI           0x00000100
#define UART_INPUT_DCD          0x00000004
#define UART_INPUT_DSR          0x00000002
#define UART_INPUT_CTS          0x00000001

//*****************************************************************************
//
// Values that can be passed to UARTTxIntModeSet() or returned from
// UARTTxIntModeGet().
//
//*****************************************************************************
#define UART_TXINT_MODE_FIFO_M  0x0000001F
#define UART_TXINT_MODE_EOT     0x00000000

//*****************************************************************************
//
// API Function prototypes
//
//*****************************************************************************
    extern void UARTParityModeSet(unsigned long ulBase, unsigned long ulParity);
    extern unsigned long UARTParityModeGet(unsigned long ulBase);
    extern void UARTFIFOLevelSet(unsigned long ulBase, unsigned long ulTxLevel,
                                 unsigned long ulRxLevel);
    extern void UARTFIFOLevelGet(unsigned long ulBase, unsigned long *pulTxLevel,
                                 unsigned long *pulRxLevel);
    extern void UARTConfigSetExpClk(unsigned long ulBase, unsigned long ulUARTClk,
                                    unsigned long ulBaud, unsigned long ulConfig);
    extern void UARTConfigGetExpClk(unsigned long ulBase, unsigned long ulUARTClk,
                                    unsigned long *pulBaud,
                                    unsigned long *pulConfig);
    extern void UARTEnable(unsigned long ulBase);
    extern void UARTDisable(unsigned long ulBase);
    extern void UARTFIFOEnable(unsigned long ulBase);
    extern void UARTFIFODisable(unsigned long ulBase);
    extern tBoolean UARTCharsAvail(unsigned long ulBase);
    extern tBoolean UARTSpaceAvail(unsigned long ulBase);
    extern long UARTCharGetNonBlocking(unsigned long ulBase);
    extern long UARTCharGet(unsigned long ulBase);
    extern tBoolean UARTCharPutNonBlocking(unsigned long ulBase,
                                           unsigned char ucData);
    extern void UARTCharPut(unsigned long ulBase, unsigned char ucData);
    extern tBoolean UARTBusy(unsigned long ulBase);
    extern void UARTRXIntRegister(unsigned long ulBase, void(*pfnHandler)(void));
    extern void UARTTXIntRegister(unsigned long ulBase, void(*pfnHandler)(void));
    extern void UARTRXIntUnregister(unsigned long ulBase);
    extern void UARTTXIntUnregister(unsigned long ulBase);
    extern void UARTIntEnable(unsigned long ulBase, unsigned long ulIntFlags);
    extern void UARTIntDisable(unsigned long ulBase, unsigned long ulIntFlags);
    extern unsigned long UARTIntStatus(unsigned long ulBase, tBoolean bMasked);
    extern void UARTIntClear(unsigned long ulBase, unsigned long ulIntFlags);
    extern unsigned long UARTRxErrorGet(unsigned long ulBase);
    extern void UARTRxErrorClear(unsigned long ulBase);
    extern void UARTTxIntModeSet(unsigned long ulBase, unsigned long ulMode);
    extern unsigned long UARTTxIntModeGet(unsigned long ulBase);


//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif //  __UART_H__


