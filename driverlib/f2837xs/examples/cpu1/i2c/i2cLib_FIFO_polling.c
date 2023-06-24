//#############################################################################
//
// FILE:   i2cLib_FIFO_polling.c
//
// TITLE:  C28x-I2C Library source file for FIFO using polling
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

#include "i2cLib_FIFO_polling.h"



uint16_t I2CBusScan(uint32_t base, uint16_t *pAvailableI2C_slaves)
{
    uint16_t probeSlaveAddress, i;

    //Disable interrupts on Stop condition, NACK and arbitration lost condition
    I2C_disableInterrupt(base, (I2C_INT_ADDR_SLAVE|I2C_INT_STOP_CONDITION | I2C_INT_ARB_LOST | I2C_INT_NO_ACK));

    i = 0;
    for(probeSlaveAddress=1;probeSlaveAddress<=MAX_10_BIT_ADDRESS;probeSlaveAddress++)
    {
        //Check I2C bus status
        status = checkBusStatus(base);
        if(status)
        {
           ESTOP0;
           return status;
        }

        I2C_setConfig(base, (I2C_MASTER_SEND_MODE | I2C_REPEAT_MODE));

        //Enable 10-bit addressing if probeSlaveAddress is greater than 127U
        if(probeSlaveAddress > MAX_7_BIT_ADDRESS)
        {
            //10-bit addressing
            I2C_setAddressMode(base, I2C_ADDR_MODE_10BITS);
        }

        // Setup slave address
        I2C_setSlaveAddress(base, probeSlaveAddress);


        I2C_sendStartCondition(base);

        //Wait for the slave address to be transmitted
        while(!(I2C_getStatus(base) & I2C_STS_REG_ACCESS_RDY));

        //Generate STOP condition
        I2C_sendStopCondition(base);

        //Wait for the I2CMDR.STP to be cleared
        while(I2C_getStopConditionStatus(base));

        //Wait for the Bus busy bit to be cleared
        while(I2C_isBusBusy(base));

        uint16_t I2CStatus = I2C_getStatus(base);

        //If Slave address is acknowledged, store slave address
        //in pAvailableI2C_slaves
        if(!(I2CStatus & I2C_STS_NO_ACK))
        {
            pAvailableI2C_slaves[i++] = probeSlaveAddress;
        }
        //Clear NACK bit in I2CSTR
        I2C_clearStatus(base,I2C_STS_NO_ACK|I2C_STS_ARB_LOST|I2C_STS_REG_ACCESS_RDY|I2C_STS_STOP_CONDITION);
    }

    I2C_setConfig(base, (I2C_MASTER_SEND_MODE));
    I2C_setAddressMode(base, I2C_ADDR_MODE_7BITS); //7-bit addressing
    I2C_enableInterrupt(base, (I2C_INT_ADDR_SLAVE|I2C_INT_STOP_CONDITION | I2C_INT_ARB_LOST | I2C_INT_NO_ACK));
    return SUCCESS;
}

uint16_t I2C_TransmitSlaveAddress_ControlBytes(struct I2CHandle *I2C_Params)
{
    uint16_t status, attemptCount=1;

    uint32_t base = I2C_Params->base;

    status = 1;

    while(status & (attemptCount <= I2C_Params->NumOfAttempts))
    {
        status = checkBusStatus(base);
        attemptCount++;
        DEVICE_DELAY_US(I2C_Params->Delay_us);
    }

    if(status)
    {
        return status;
    }

    I2C_setConfig(base, (I2C_MASTER_SEND_MODE|I2C_REPEAT_MODE));

    if((I2C_Params->SlaveAddr) > MAX_7_BIT_ADDRESS)
    {
        //10-bit addressing
        I2C_setAddressMode(base, I2C_ADDR_MODE_10BITS);
    }

    // Setup slave address
    I2C_setSlaveAddress(base, I2C_Params->SlaveAddr);


    int16_t  i;
    uint32_t temp = *(I2C_Params->pControlAddr);

    for(i=I2C_Params->NumOfAddrBytes-1;i>=0;i--)
    {
        I2C_putData(base, (temp >> (i*8U)) & 0xFF);
    }

    I2C_sendStartCondition(base);

    DEVICE_DELAY_US(150U);

    status = handleNACK(base);
    if(status)
    {
      if(attemptCount <= (I2C_Params->NumOfAttempts))
      {
          attemptCount++;
          I2C_setConfig(base, (I2C_MASTER_SEND_MODE));
          I2C_sendStartCondition(base);
          DEVICE_DELAY_US(I2C_Params->Delay_us);
      }
      else
      {
          return status;
      }
	}

    attemptCount = 1;

    while(I2C_getTxFIFOStatus(base) && attemptCount <= 9 * (I2C_Params->NumOfAddrBytes + 2U))
    {
       status = handleNACK(base);
       if(status)
       {
          return status;
       }
       attemptCount++;
       DEVICE_DELAY_US(I2C_Params->Delay_us);
    }

    return SUCCESS;
}

uint16_t I2C_MasterTransmitter(struct I2CHandle *I2C_Params)
{
    uint16_t status, attemptCount;

    uint32_t base = I2C_Params->base;

    I2C_disableFIFO(base);
    I2C_enableFIFO(base);

    status = I2C_TransmitSlaveAddress_ControlBytes(I2C_Params);

    if(status)
    {
        return status;
    }

    I2C_setDataCount(base, (I2C_Params->NumOfAddrBytes + I2C_Params->NumOfDataBytes));

    I2C_setFIFOInterruptLevel(base, I2C_FIFO_TXEMPTY, I2C_FIFO_RXFULL);

    I2C_enableInterrupt(base, I2C_INT_TXFF);

    uint16_t numofSixteenByte  = (I2C_Params->NumOfDataBytes) / I2C_FIFO_LEVEL;
    uint16_t remainingBytes    = (I2C_Params->NumOfDataBytes) % I2C_FIFO_LEVEL;

    uint16_t i,count = 0,buff_pos=0;

    while(count < numofSixteenByte)
    {
        for(i=1;i<=I2C_FIFO_LEVEL;i++)
        {
            I2C_putData(base, I2C_Params->pTX_MsgBuffer[buff_pos++]);
        }

        attemptCount = 1;
        while(I2C_getTxFIFOStatus(base) && attemptCount <= 9 * (I2C_FIFO_LEVEL + 2U))
        {
            status = handleNACK(base);
            if(status)
            {
              return status;
            }
            attemptCount++;
            DEVICE_DELAY_US(I2C_Params->Delay_us);
        }

        count++;
    }

    for (i=0; i < remainingBytes; i++)
    {
        I2C_putData(base, I2C_Params->pTX_MsgBuffer[buff_pos++]);
    }

    attemptCount = 1;
    while(I2C_getTxFIFOStatus(base) && attemptCount <= 9 * (remainingBytes + 2U))
    {
        status = handleNACK(base);
        if(status)
        {
          return status;
        }
        attemptCount++;
        DEVICE_DELAY_US(I2C_Params->Delay_us);
    }

    I2C_sendStopCondition(base);

    attemptCount = 1;
    while(I2C_getStopConditionStatus(base) && attemptCount <= 3U)
    {
        DEVICE_DELAY_US(I2C_Params->Delay_us);
        attemptCount++;
    }

    return SUCCESS;
}

uint16_t I2C_MasterReceiver(struct I2CHandle *I2C_Params)
{
    uint16_t status;
    uint16_t attemptCount;

    uint32_t base = I2C_Params->base;

    I2C_disableFIFO(base);
    I2C_enableFIFO(base);

    status = I2C_TransmitSlaveAddress_ControlBytes(I2C_Params);

    if(status)
    {
        return status;
    }

    uint16_t numofSixteenByte  = (I2C_Params->NumOfDataBytes) / I2C_FIFO_LEVEL;
    uint16_t remainingBytes    = (I2C_Params->NumOfDataBytes) % I2C_FIFO_LEVEL;

    I2C_setConfig(base, (I2C_MASTER_RECEIVE_MODE|I2C_REPEAT_MODE));

    I2C_sendStartCondition(base);

    uint16_t i,count = 0,buff_pos=0;
    while(count < numofSixteenByte)
    {
        status = handleNACK(base);
        if(status)
        {
          return status;
        }

        count++;

        attemptCount = 1;
        while(!(I2C_getRxFIFOStatus(base) == I2C_FIFO_RXFULL) && attemptCount <= 9 * (I2C_FIFO_RXFULL + 2U))
        {
            DEVICE_DELAY_US(I2C_Params->Delay_us);
            attemptCount++;
        }

        for(i=0; i<I2C_FIFO_LEVEL; i++)
        {
            I2C_Params->pRX_MsgBuffer[buff_pos++] = I2C_getData(base);
        }
    }

    attemptCount = 1;
    while(!(I2C_getRxFIFOStatus(base) == remainingBytes) && attemptCount <= 9 * (remainingBytes + 2U))
    {
       DEVICE_DELAY_US(I2C_Params->Delay_us);
       attemptCount++;
    }

    I2C_sendStopCondition(base);

    for(i=0; i<remainingBytes; i++)
    {
        I2C_Params->pRX_MsgBuffer[buff_pos++] = I2C_getData(base);
    }

    status = handleNACK(base);
    if(status)
    {
      return status;
    }

    I2C_disableFIFO(base);

    attemptCount = 1;
    while(I2C_getStopConditionStatus(base) && attemptCount <= 3U);
    {
        DEVICE_DELAY_US(I2C_Params->Delay_us);
        attemptCount++;
    }

    return SUCCESS;

}


uint16_t checkBusStatus(uint32_t base)
{

    if(I2C_isBusBusy(base))
    {
        return ERROR_BUS_BUSY;
    }

    if(I2C_getStopConditionStatus(base))
    {
        return ERROR_STOP_NOT_READY;
    }

    return SUCCESS;
}

uint16_t handleNACK(uint32_t base)
{
    if(I2C_getStatus(base) & I2C_STS_NO_ACK)
    {
        I2C_clearStatus(base, I2C_STS_NO_ACK);
        I2C_sendStopCondition(base);

        return ERROR_NACK_RECEIVED;
    }

    return SUCCESS;
}

