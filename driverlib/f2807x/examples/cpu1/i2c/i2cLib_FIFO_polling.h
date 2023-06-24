//#############################################################################
//
// FILE:   i2cLib_FIFO_polling.h
//
// TITLE:  C28x-I2C Library header file for FIFO using polling
//
//#############################################################################
//#############################################################################
//
// $Release Date: $
// $Copyright:
// Copyright (C) 2014-2023 Texas Instruments Incorporated - http://www.ti.com/
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
//#############################################################################

#ifndef I2CLIB_FIFO_POLLING_H
#define I2CLIB_FIFO_POLLING_H

#include "device.h"

//
// Error messages for read and write functions
//
#define ERROR_BUS_BUSY              0x1000
#define ERROR_NACK_RECEIVED         0x2000
#define ERROR_ARBITRATION_LOST      0x3000
#define ERROR_STOP_NOT_READY        0x5555
#define SUCCESS                     0x0000

#define MAX_BUFFER_SIZE             64
#define I2C_FIFO_LEVEL              16

#define MAX_7_BIT_ADDRESS 127U
#define MAX_10_BIT_ADDRESS 1023U


//
// Typedefs
//
struct I2CHandle
{
    uint32_t base;
    uint16_t SlaveAddr;                  // Slave address tied to the message.
    uint32_t *pControlAddr;
    uint16_t NumOfAddrBytes;
    uint16_t *pTX_MsgBuffer;             // Pointer to TX message buffer
    uint16_t *pRX_MsgBuffer;             // Pointer to RX message buffer
    uint16_t NumOfDataBytes;             // Number of valid bytes in message.
    struct I2CHandle *currentHandlePtr;

    uint16_t numofSixteenByte;
    uint16_t remainingBytes;

    uint16_t WriteCycleTime_in_us;      //  Slave write cycle time. Depends on slave.
                                        //  Please check slave device datasheet

    uint16_t NumOfAttempts;             //  Number of attempts to make before reporting
                                        //  slave not ready (NACK condition)
    uint16_t Delay_us;                  //  Delay time in microsecs (us)
};

uint16_t I2C_TransmitSlaveAddress_ControlBytes(struct I2CHandle *I2C_Params);
uint16_t I2CBusScan(uint32_t base, uint16_t *pAvailableI2C_slaves);

uint16_t I2C_MasterTransmitter(struct I2CHandle *I2C_Params);
uint16_t I2C_MasterReceiver(struct I2CHandle *I2C_Params);
uint16_t I2C_SlaveTransmitter(struct I2CHandle *I2C_Params);
uint16_t I2C_SlaveReceiver(struct I2CHandle *I2C_Params);

uint16_t checkBusStatus(uint32_t base);

uint16_t handleNACK(uint32_t base);

extern void handleI2C_ErrorCondition(struct I2CHandle *I2C_Params);
extern void Write_Read_TX_RX_FIFO(struct I2CHandle *I2C_Params);

extern uint16_t TX_MsgBuffer[MAX_BUFFER_SIZE];
extern uint16_t RX_MsgBuffer[MAX_BUFFER_SIZE];

extern uint16_t status;

extern struct I2CHandle *currentSlavePtr;

#endif


