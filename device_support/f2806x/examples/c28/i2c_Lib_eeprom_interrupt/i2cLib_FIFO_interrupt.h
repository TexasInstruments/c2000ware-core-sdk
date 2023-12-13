//###########################################################################
//
// FILE:   i2cLib_FIFO_interrupt.h
//
// TITLE:  I2C FIFO Interrupt Library header file.
//
//###########################################################################
// $TI Release: $
// $Release Date: $
// $Copyright:
// Copyright (C) 2009-2023 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef I2CLIB_FIFO_INTERRUPT_H_
#define I2CLIB_FIFO_INTERRUPT_H_

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

//
// Error messages for read and write functions
//
#define ERROR_BUS_BUSY              0x1000
#define ERROR_STOP_NOT_READY        0x5555
#define ERROR_NACK_RECEIVED         0x2000
#define ERROR_TIMEOUT               0x3000
#define ERROR_BUFFER_MAX            0x4000
#define SUCCESS                     0x0000

//
// I2C Library Defines
//
#define MAX_BUFFER_SIZE             64
#define I2C_FIFO_LEVEL              4

//
// Typedefs
//
struct I2CHandle
{
    Uint16 SlaveAddr;           // Slave address tied to the message.
    Uint16 *pControlBuffer;     // Pointer to control bytes buffer
    Uint16 NumOfControlBytes;   // Number of control bytes in message
    Uint16 *pMsgBuffer;         // Pointer to message buffer
    Uint16 NumOfDataBytes;      // Number of valid data bytes in message.
    Uint16 Timeout;             // I2C Timeout variable
};

//
// Extern data types
//
extern struct I2CHandle *currentResponderPtr;  // Used in interrupt

//
// I2C function prototypes
//
Uint16 I2C_TxSlaveAddress_ControlBytes(struct I2CHandle *I2C_Params);

Uint16 I2C_MasterWrite(struct I2CHandle *I2C_Params);
Uint16 I2C_MasterRead(struct I2CHandle *I2C_Params);

interrupt void i2c_isr(void);
interrupt void i2cFIFO_isr(void);

Uint16 checkBusStatus(void);
Uint16 handleNACK(void);
Uint16 handleNACKandTimeout(void);

#endif /* I2CLIB_FIFO_INTERRUPT_H_ */
