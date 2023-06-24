//#############################################################################
//
// FILE:   i2cLib_FIFO_master_interrupt.c
//
// TITLE:  C28x-I2C Library source file for FIFO interrupts
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

#include "driverlib.h"
#include "device.h"
#include "i2cLib_FIFO_master_interrupt.h"



void handleI2C_ErrorCondition(struct I2CHandle *I2C_Params);
void Write_Read_TX_RX_FIFO(struct I2CHandle *I2C_Params);

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
    uint16_t status;

    uint32_t base = I2C_Params->base;

    status = checkBusStatus(base);
    if(status)
    {
        return status;
    }

    I2C_disableFIFO(base);

    I2C_setConfig(base, (I2C_MASTER_SEND_MODE));

    if((I2C_Params->SlaveAddr) > MAX_7_BIT_ADDRESS)
    {
        //10-bit addressing
        I2C_setAddressMode(base, I2C_ADDR_MODE_10BITS);
    }

    // Setup slave address
    I2C_setSlaveAddress(base, I2C_Params->SlaveAddr);

    I2C_setDataCount(base, (I2C_Params->NumOfAddrBytes));

    I2C_enableFIFO(base);

    uint32_t temp = *(I2C_Params->pControlAddr);

    temp = temp & 0x00FFFFFF;

    temp |= (uint32_t)(I2C_Params->NumOfDataBytes)<<24U;

    int16_t i;
    i = I2C_Params->NumOfAddrBytes-1;

    for(i=I2C_Params->NumOfAddrBytes-1;i>=0;i--)
    {
       I2C_putData(base, (temp >> (i*8U)) & 0xFF);
    }

    I2C_sendStartCondition(base);

    return SUCCESS;
}

uint16_t I2C_MasterTransmitter(struct I2CHandle *I2C_Params)
{
    uint16_t status;

    uint32_t base = I2C_Params->base;

    I2C_Params->numofSixteenByte  = (I2C_Params->NumOfDataBytes) / I2C_FIFO_LEVEL;
    I2C_Params->remainingBytes    = (I2C_Params->NumOfDataBytes) % I2C_FIFO_LEVEL;

    ASSERT(I2C_Params->NumOfDataBytes <= MAX_BUFFER_SIZE);

    I2C_enableFIFO(base);

    status = I2C_TransmitSlaveAddress_ControlBytes(I2C_Params);

    if(status)
    {
        return status;
    }

    I2C_setDataCount(base, (I2C_Params->NumOfAddrBytes + I2C_Params->NumOfDataBytes));
    //I2C_sendStopCondition(base);

    I2C_setFIFOInterruptLevel(base, I2C_FIFO_TXEMPTY, I2C_FIFO_RXFULL);

    I2C_enableInterrupt(base, (I2C_INT_STOP_CONDITION | I2C_INT_ARB_LOST | I2C_INT_NO_ACK));
    I2C_enableInterrupt(base, I2C_INT_TXFF);

    I2C_clearInterruptStatus(base, I2C_INT_TXFF);

    return SUCCESS;
}

uint16_t I2C_MasterReceiver(struct I2CHandle *I2C_Params)
{
    uint16_t status;
    uint32_t base = I2C_Params->base;

    I2C_Params->numofSixteenByte  = (I2C_Params->NumOfDataBytes) / I2C_FIFO_LEVEL;
    I2C_Params->remainingBytes    = (I2C_Params->NumOfDataBytes) % I2C_FIFO_LEVEL;

    I2C_disableInterrupt(base, I2C_INT_TXFF|I2C_INT_RXFF);

    I2C_clearInterruptStatus(base, (I2C_INT_REG_ACCESS_RDY|I2C_INT_TXFF|I2C_INT_RXFF));

    I2C_enableInterrupt(base, I2C_INT_REG_ACCESS_RDY);

    status = I2C_TransmitSlaveAddress_ControlBytes(I2C_Params);

    SysCtl_delay(50); //Adding delay to correctly read I2C bus status

    if(status)
    {
        return status;
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
        I2C_disableFIFO(base);
        I2C_sendStopCondition(base);
        I2C_enableFIFO(base);

        return ERROR_NACK_RECEIVED;
    }

    return SUCCESS;
}

void handleI2C_ErrorCondition(struct I2CHandle *I2C_Params)
{
    uint32_t base = I2C_Params->base;

    I2C_InterruptSource intSource = I2C_getInterruptSource(base);

    switch (intSource)
    {
        case I2C_INTSRC_ARB_LOST:
            //Report Arbitration lost failure
            status = ERROR_ARBITRATION_LOST;
            break;

        case I2C_INTSRC_NO_ACK:
            //Clear NACK flag and generate STOP condition on a NACK condition
            I2C_clearStatus(base, I2C_STS_NO_ACK);
            I2C_sendStopCondition(base);
            status = ERROR_NACK_RECEIVED;
            break;

        case I2C_INTSRC_REG_ACCESS_RDY:
            I2C_disableInterrupt(base, I2C_INT_REG_ACCESS_RDY);
            I2C_disableInterrupt(base, I2C_INT_TXFF);
            I2C_disableFIFO(base);
            I2C_enableFIFO(base);
            I2C_setConfig(base, (I2C_MASTER_RECEIVE_MODE));
            I2C_clearInterruptStatus(base, I2C_INT_TXFF);
            if(I2C_Params->numofSixteenByte)
            {
                I2C_setFIFOInterruptLevel(base, I2C_FIFO_TXEMPTY, I2C_FIFO_RXFULL);
            }
            else
            {
                I2C_setFIFOInterruptLevel(base, I2C_FIFO_TXEMPTY, (I2C_RxFIFOLevel)I2C_Params->remainingBytes);
            }

            I2C_setDataCount(base, I2C_Params->NumOfDataBytes);

            I2C_sendStartCondition(base);
            I2C_sendStopCondition(base);

            break;

        case I2C_INTSRC_RX_DATA_RDY:
            break;

        case I2C_INTSRC_TX_DATA_RDY:
            break;

        case I2C_INTSRC_STOP_CONDITION:
            I2C_disableInterrupt(base, (I2C_INT_TXFF | I2C_INT_RXFF));
            I2C_Params->pTX_MsgBuffer   = TX_MsgBuffer;
            I2C_Params->pRX_MsgBuffer   = RX_MsgBuffer;
            //I2C_disableFIFO(base);
            break;

        case I2C_INTSRC_ADDR_SLAVE:
            //Set TX / RX FIFO Level
            I2C_setFIFOInterruptLevel(base, I2C_FIFO_TXEMPTY, (I2C_RxFIFOLevel)(I2C_Params->NumOfAddrBytes));

            if((I2C_getStatus(base) & I2C_STS_SLAVE_DIR))
            {
                //Slave Transmitter (SDIR = 1)
                I2C_setConfig(base, I2C_SLAVE_SEND_MODE);
                //Enable TX FIFO interrupt and disable RXFF interrupt
                I2C_enableInterrupt(base, I2C_INT_TXFF);
                I2C_disableInterrupt(base, I2C_INT_RXFF);
                I2C_clearInterruptStatus(base, (I2C_INT_TXFF|I2C_INT_RXFF));
            }
            else
            {
                //Slave Receiver (SDIR = 0)
                I2C_setConfig(base, I2C_SLAVE_RECEIVE_MODE);
                //Fill dummy data in Transmit FIFO to clear pending FIFO interrupt flag
                //I2C_putData(base, 0xAA);
                //I2C_putData(base, 0x55);

                //Enable RX FIFO interrupt and disable TXFF interrupt
                I2C_disableInterrupt(base, I2C_INT_TXFF);
                I2C_enableInterrupt(base, I2C_INT_RXFF);
                I2C_clearInterruptStatus(base, (I2C_INT_TXFF|I2C_INT_RXFF));

            }
            break;
    }
}

void Write_Read_TX_RX_FIFO(struct I2CHandle *I2C_Params)
{
    int16_t i;
    uint32_t base = I2C_Params->base;
    uint16_t numofSixteenByte = I2C_Params->numofSixteenByte;
    uint16_t remainingBytes  = I2C_Params->remainingBytes;

    struct I2CHandle *currentPtr = I2C_Params->currentHandlePtr;

    uint32_t intSource = (uint32_t)I2C_getInterruptStatus(base);
    uint32_t txFIFOinterruptenabled = HWREGH(base + I2C_O_FFTX) & I2C_FFTX_TXFFIENA;

    //Read the Address and Command
    if((intSource & I2C_INT_RXFF) && (I2C_Params->pControlAddr) == 0x0)
    {
        uint32_t Addr_Ctrl = 0;
        int16_t NumRX_Bytes = I2C_getRxFIFOStatus(base);

        for(i=NumRX_Bytes-1;i>=0;i--)
        {
            Addr_Ctrl |= (uint32_t)(I2C_getData(base))<<(i*8U);
        }

        I2C_Params->pControlAddr       = (uint32_t *)Addr_Ctrl;
        I2C_Params->NumOfDataBytes     = Addr_Ctrl >> 24U;
        I2C_Params->numofSixteenByte   = I2C_Params->NumOfDataBytes / I2C_FIFO_LEVEL;
        I2C_Params->remainingBytes     = I2C_Params->NumOfDataBytes % I2C_FIFO_LEVEL;

        numofSixteenByte = I2C_Params->numofSixteenByte;
        remainingBytes   = I2C_Params->remainingBytes;

        if(numofSixteenByte)
        {
            I2C_setFIFOInterruptLevel(base, I2C_FIFO_TXEMPTY, I2C_FIFO_RXFULL);
        }
        else
        {
            I2C_setFIFOInterruptLevel(base, I2C_FIFO_TXEMPTY, (I2C_RxFIFOLevel)remainingBytes);
        }

        I2C_clearInterruptStatus(base,(I2C_INT_RXFF));
    }

    else
    {
        if((intSource & I2C_INT_TXFF) || (intSource & I2C_INT_RXFF))
        {
            //When numofSixteenByte becomes 0, read only remaining bytes
          if(remainingBytes && (numofSixteenByte == 0))
          {
            for(i=0;i<remainingBytes;i++)
            {
                if((intSource & I2C_INT_TXFF) && txFIFOinterruptenabled)
                {
                    I2C_putData(base, *(currentPtr->pTX_MsgBuffer++));
                }
                if(intSource & I2C_INT_RXFF)
                {
                    *(currentPtr->pRX_MsgBuffer++) = I2C_getData(base);
                }
            }
            remainingBytes = 0;
          }

          //When numofSixteenByte greater than 0, read all the 16 bytes in FIFO
          if(numofSixteenByte)
          {
            if((intSource & I2C_INT_TXFF) && txFIFOinterruptenabled)
            {
                for(i=0;i<I2C_FIFO_TXFULL;i++)
                {
                   I2C_putData(base, *(currentPtr->pTX_MsgBuffer++));
                }
                numofSixteenByte--;
            }

            if(intSource & I2C_INT_RXFF)
            {
                for(i=0;i<I2C_FIFO_RXFULL;i++)
                {
                    *(currentPtr->pRX_MsgBuffer++) = I2C_getData(base);
                }
                numofSixteenByte--;
            }
          }

          //When numofSixteenByte equal to 0, change RX FIFO level (RXFFIL) to remaining bytes
          if((numofSixteenByte == 0) && (remainingBytes))
          {
            I2C_setFIFOInterruptLevel(base, I2C_FIFO_TXEMPTY, (I2C_RxFIFOLevel)remainingBytes);
          }

          //When number of bytes are 0, then disable TX / RX FIFO interrupts, disable FIFO
          //and send STOP condition
          if((remainingBytes == 0) && (numofSixteenByte == 0))
          {
            //I2C_disableInterrupt(base, (I2C_INT_TXFF | I2C_INT_RXFF));
            //I2C_disableFIFO(base);
              if(HWREGH(I2C_Params->base + I2C_O_MDR) & I2C_MDR_MST)
              {
                  I2C_sendStopCondition(base);
              }
          }

          I2C_clearInterruptStatus(base,(I2C_INT_TXFF | I2C_INT_RXFF));
        }

          I2C_Params->numofSixteenByte = numofSixteenByte;
          I2C_Params->remainingBytes   = remainingBytes;
    }
}

