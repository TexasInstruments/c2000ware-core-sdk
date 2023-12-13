//###########################################################################
//
// FILE:   pmbus_over_i2c_lib.c.h
//
// TITLE:  I2C Functions used in PMBUS Communications Stack
//
//###########################################################################
//
//
// $Copyright: Copyright (C) 2015-2023 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################
#ifdef PMBUS_OVER_I2C

//
// Includes
//
#include "pmbus_over_i2c_lib.h"


void I2CWrite(uint32_t base, uint16_t targetAddr, uint16_t *pTXbuff, uint16_t byteCount, bool sendStopCondition)
{

    I2C_enableInterrupt(base, I2C_INT_STOP_CONDITION | I2C_INT_NO_ACK | I2C_INT_ARB_LOST);

    //Disable and enable FIFO to flush any previous I2C transaction
    I2C_disableFIFO(base);
    I2C_enableFIFO(base);

    I2C_setTargetAddress(base, targetAddr);
    //Controller Transmit mode + Repeat mode
    //I2CCNT register settings are ignored
    I2C_setConfig(base, I2C_CONTROLLER_SEND_MODE);
    I2C_setDataCount(base, byteCount);

    I2C_setFIFOInterruptLevel(base, I2C_FIFO_TXEMPTY, I2C_FIFO_RXFULL);

    uint16_t numofSixteenByte  = byteCount / I2C_FIFO_TXFULL;
    uint16_t remainingBytes    = byteCount % I2C_FIFO_TXFULL;

    uint16_t count = 0;
    uint16_t i = 0;
    uint16_t buff_pos = 0;

    I2C_sendStartCondition(base);

    while(count < numofSixteenByte)
    {
        for(i=1;i<=I2C_FIFO_TXFULL;i++)
        {
          I2C_putData(base, pTXbuff[buff_pos++]);
        }

        //Wait till TX FIFO contents are transmitted
        while(WAIT_TILL_TX_FIFO_IS_EMPTY);

        count++;
    }

    for (i=0; i < remainingBytes; i++)
    {
      I2C_putData(base, pTXbuff[buff_pos++]);
    }

    //Wait till TX FIFO contents are transmitted
    while(WAIT_TILL_TX_FIFO_IS_EMPTY);

    if(sendStopCondition)
    {
        I2C_sendStopCondition(base);
        while(I2C_getStopConditionStatus(base));
        I2C_clearStatus(base, I2C_STS_STOP_CONDITION | I2C_STS_NO_ACK | I2C_STS_BYTE_SENT);
    }
}

uint16_t I2CRead(uint32_t base, uint16_t targetAddr, uint16_t *pRXbuff, uint16_t byteCount, bool sendStopCondition)
{
    I2C_enableInterrupt(base, I2C_INT_STOP_CONDITION | I2C_INT_NO_ACK | I2C_INT_ARB_LOST);

    //Disable and enable FIFO to flush any previous I2C transaction
    I2C_disableFIFO(base);
    I2C_enableFIFO(base);

    I2C_setTargetAddress(base, targetAddr);

    //Controller Receiver mode + Repeat mode
    //I2CCNT register settings are ignored
    I2C_setConfig(base, I2C_CONTROLLER_RECEIVE_MODE);
    I2C_setDataCount(base, byteCount);

    I2C_sendStartCondition(base);

    I2C_setFIFOInterruptLevel(base, I2C_FIFO_TXEMPTY, I2C_FIFO_RXFULL);

    uint16_t numofSixteenByte  = byteCount / I2C_FIFO_RXFULL;
    uint16_t remainingBytes    = byteCount % I2C_FIFO_RXFULL;

    uint16_t count = 0;
    uint16_t i = 0;
    uint16_t buff_pos = 0;

    while(count < numofSixteenByte)
    {
        while(WAIT_TILL_RX_FIFO_IS_FULL);

        for(i=0;i<I2C_FIFO_RXFULL;i++)
        {
            pRXbuff[buff_pos++] = I2C_getData(base);
            count++;
        }

    }

    while(WAIT_TILL_RX_FIFO_HAS(remainingBytes));

    for(i=0; i<remainingBytes; i++)
    {
        pRXbuff[buff_pos++] = I2C_getData(base);
        count++;
    }

    if(sendStopCondition)
    {
        I2C_sendStopCondition(base);
        while(I2C_getStopConditionStatus(base));
        I2C_clearStatus(base, I2C_STS_STOP_CONDITION | I2C_STS_NO_ACK | I2C_STS_BYTE_SENT);
    }
    return count;
}

#endif
