//###########################################################################
//
// FILE:   i2cLib_FIFO_polling.c
//
// TITLE:  I2C FIFO Polling Library source file.
//
//###########################################################################
// $TI Release: $
// $Release Date: $
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

#include "i2cLib_FIFO_polling.h"

//
// Global variables used by i2cLib_FIFO_polling
//
Uint16 timeoutCheck;

//
// I2C_TxSlaveAddress_ControlBytes - This function transmits the SlaveAddr
//      and pControlBuffer control bytes of the passed I2CHandle.
//
Uint16 I2C_TxSlaveAddress_ControlBytes(struct I2CHandle *I2C_Params)
{
    Uint16 status;

    //
    // Check if the I2C bus is busy before starting comms
    //
    status = checkBusStatus();

    if(status)
    {
        return status;
    }

    //
    // Set up as master transmitter
    // FREE + MST + TRX + IRS
    //
    I2caRegs.I2CMDR.all = 0x4620;

    //
    // Setup slave address
    //
    I2caRegs.I2CSAR = I2C_Params->SlaveAddr;

    I2caRegs.I2CMDR.bit.STT = 0x1; // Send START condition

    Uint16 count;

    //
    // Transmit NumOfControlBytes that are in pControlBuffer
    //
    for(count=0;count<I2C_Params->NumOfControlBytes;count++)
    {
        // Write control byte to I2C transmit FIFO
        I2caRegs.I2CDXR = I2C_Params->pControlBuffer[count];

        timeoutCheck = I2C_Params->Timeout;

        //
        // Wait for data to be transmitted out of FIFO.
        // Times out if TX takes too long.
        //
        while(I2caRegs.I2CFFTX.bit.TXFFST)
        {
            status = handleNACKandTimeout();

            if(status)
            {
                return status;
            }

            DELAY_US(10);
        }
    }

    return SUCCESS;
}

//
// I2C_MasterWrite - This function transmits the full I2C message of the
//      passed I2CHandle. Function sequence is the following:
//
//      1. Generate START condition and transmit SlaveAddr
//      2. Transmit NumOfControlBytes in pControlBuffer
//      3. Transmit NumOfDataBytes in pMsgBuffer
//      4. Generate STOP condition
//
Uint16 I2C_MasterWrite(struct I2CHandle *I2C_Params)
{
    Uint16 status, buff_pos = 0;

    if(I2C_Params->NumOfDataBytes > MAX_BUFFER_SIZE)
    {
        return ERROR_BUFFER_MAX;
    }

    // Enable TX FIFO
    I2caRegs.I2CFFTX.all = 0x6000;

    // Set I2CCNT to number of bytes to transmit
    I2caRegs.I2CCNT = (I2C_Params->NumOfControlBytes) +
            (I2C_Params->NumOfDataBytes);

    //
    // Transmit slave address and control bytes
    //
    status = I2C_TxSlaveAddress_ControlBytes(I2C_Params);

    if(status)
    {
        return status;
    }

    //
    // Calculate number of bytes to be transmitted out of the FIFO
    //
    Uint16 numofFourBytes  = (I2C_Params->NumOfDataBytes) / I2C_FIFO_LEVEL;
    Uint16 remainingBytes    = (I2C_Params->NumOfDataBytes) % I2C_FIFO_LEVEL;

    Uint16 i,count = 0;

    //
    // Transmit bytes in pMsgBuffer using the full I2C_FIFO_LEVEL
    //
    while(count < numofFourBytes)
    {
        //
        // Fill the TX FIFO up to I2C_FIFO_LEVEL
        //
        for(i=1;i<=I2C_FIFO_LEVEL;i++)
        {
            I2caRegs.I2CDXR = I2C_Params->pMsgBuffer[buff_pos++];
        }

        timeoutCheck = I2C_Params->Timeout;

        //
        // Wait for data to be transmitted out of FIFO.
        // Times out if TX takes too long.
        //
        while(I2caRegs.I2CFFTX.bit.TXFFST)
        {
            status = handleNACKandTimeout();

            if(status)
            {
                return status;
            }

            DELAY_US(10);
        }

        count++;
    }

    //
    // Fill the TX FIFO up to remainingBytes
    //
    for (i=0; i < remainingBytes; i++)
    {
        I2caRegs.I2CDXR = I2C_Params->pMsgBuffer[buff_pos++];
    }

    timeoutCheck = I2C_Params->Timeout;

    //
    // Wait for data to be transmitted out of FIFO.
    // Times out if TX takes too long.
    //
    while(I2caRegs.I2CFFTX.bit.TXFFST)
    {
        status = handleNACKandTimeout();

        if(status)
        {
            return status;
        }

        DELAY_US(10);
    }

    // Generate STOP condition
    I2caRegs.I2CMDR.bit.STP = 1;

    timeoutCheck = I2C_Params->Timeout;

    //
    // Wait for STOP condition to be generated.
    // Times out if STOP condition not generated in time.
    //
    while(I2caRegs.I2CMDR.bit.STP)
    {
        status = handleNACKandTimeout();

        if(status)
        {
            return status;
        }

        DELAY_US(10);
    }

    return SUCCESS;
}

//
// I2C_MasterRead - This function reads data bytes from an I2C slave device
//      based on the passed I2CHandle. Function sequence is the following:
//
//      1. Generate START condition and transmit SlaveAddr
//      2. Transmit NumOfControlBytes in pControlBuffer
//      3. Generate repeated START condition
//      4. Receive NumOfDataBytes into pMsgBuffer
//      5. Generate STOP condition
//
Uint16 I2C_MasterRead(struct I2CHandle *I2C_Params)
{
    Uint16 status, buff_pos = 0;

    if(I2C_Params->NumOfDataBytes > MAX_BUFFER_SIZE)
    {
        return ERROR_BUFFER_MAX;
    }

    // Enable TX FIFO
    I2caRegs.I2CFFTX.all = 0x6000;

    // Set I2CCNT for number of control bytes to transmit
    I2caRegs.I2CCNT = I2C_Params->NumOfControlBytes;

    //
    // Transmit slave address and control bytes
    //
    status = I2C_TxSlaveAddress_ControlBytes(I2C_Params);

    // Disable TX FIFO
    I2caRegs.I2CFFTX.bit.TXFFRST = 0;

    if(status)
    {
        return status;
    }

    //
    // Calculate number of bytes to be received into the FIFO
    //
    Uint16 numofFourBytes  = (I2C_Params->NumOfDataBytes) / I2C_FIFO_LEVEL;
    Uint16 remainingBytes    = (I2C_Params->NumOfDataBytes) % I2C_FIFO_LEVEL;

    // Set I2CCNT for number of bytes to receive
    I2caRegs.I2CCNT = I2C_Params->NumOfDataBytes;

    // Enable RX FIFO
    I2caRegs.I2CFFRX.all = 0x2040;

    //
    // Set up as master receiver
    // FREE + MST + IRS
    //
    I2caRegs.I2CMDR.all = 0x4420;

    I2caRegs.I2CMDR.bit.STT = 0x1; // Send repeated START condition

    Uint16 i,count = 0;

    //
    // Receive bytes into pMsgBuffer using the full I2C_FIFO_LEVEL
    //
    while(count < numofFourBytes)
    {
        timeoutCheck = I2C_Params->Timeout;

        //
        // Wait for data to be received into FIFO.
        // Times out if RX takes too long.
        //
        while(!(I2caRegs.I2CFFRX.bit.RXFFST == I2C_FIFO_LEVEL))
        {
            status = handleNACKandTimeout();

            if(status)
            {
                return status;
            }

            DELAY_US(10);
        }

        //
        // Read all bytes currently in FIFO
        //
        for(i=0; i<I2C_FIFO_LEVEL; i++)
        {
            I2C_Params->pMsgBuffer[buff_pos++] = I2caRegs.I2CDRR;
        }

        count++;
    }

    //
    // Receive remainingBytes if there are any.
    //
    if(remainingBytes)
    {
        timeoutCheck = I2C_Params->Timeout;

        //
        // Wait for remainingBytes to be received into FIFO.
        // Times out if RX takes too long.
        //
        while(!(I2caRegs.I2CFFRX.bit.RXFFST == remainingBytes))
        {
            status = handleNACKandTimeout();

            if(status)
            {
                return status;
            }

            DELAY_US(10);
        }

        //
        // Read remainingBytes currently in FIFO
        //
        for(i=0; i<remainingBytes; i++)
        {
            I2C_Params->pMsgBuffer[buff_pos++] = I2caRegs.I2CDRR;
        }
    }

    //
    // Generate STOP condition
    //
    I2caRegs.I2CMDR.bit.STP = 1;

    timeoutCheck = I2C_Params->Timeout;

    //
    // Wait for STOP condition to be generated.
    // Times out if STOP condition not generated in time.
    //
    while(I2caRegs.I2CMDR.bit.STP)
    {
        status = handleNACKandTimeout();

        if(status)
        {
            return status;
        }

        DELAY_US(10);
    }

    return SUCCESS;
}

//
// checkBusStatus - This function checks the status of the I2C Bus.
//
Uint16 checkBusStatus(void)
{
    //
    // Check if bus busy
    //
    if (I2caRegs.I2CSTR.bit.BB == 1)
    {
        return ERROR_BUS_BUSY;
    }

    //
    // Wait until the STP bit is cleared from any previous master communication
    // Clearing of this bit by the module is delayed until after the SCD bit is
    // set. If this bit is not checked prior to initiating a new message, the
    // I2C could get confused.
    //
    if (I2caRegs.I2CMDR.bit.STP == 1)
    {
        return ERROR_STOP_NOT_READY;
    }

    return SUCCESS;
}

//
// handleNACK - This function checks for and handles a NACK
//      from the receiving device.
//
Uint16 handleNACK(void)
{
    // Check if NACK was received
    if(I2caRegs.I2CSTR.bit.NACK == 1)
    {
        // Clear NACK
        I2caRegs.I2CSTR.bit.NACK = 1;

        // disable FIFO
        I2caRegs.I2CFFTX.all = 0x0000;
        I2caRegs.I2CFFRX.all = 0x0000;

        // Generate STOP condition
        I2caRegs.I2CMDR.bit.STP = 1;

        return ERROR_NACK_RECEIVED;
    }

    return SUCCESS;
}

//
// handleNACKandTimeout - This function checks for and handles a NACK
//      from the receiving device. It also checks for a timeout condition
//      based on Timeout value of the respective I2CHandle.
//
Uint16 handleNACKandTimeout()
{
    // Check if NACK was received
    if(I2caRegs.I2CSTR.bit.NACK == 1)
    {
        // Clear NACK
        I2caRegs.I2CSTR.bit.NACK = 1;

        // disable FIFO
        I2caRegs.I2CFFTX.all = 0x0000;
        I2caRegs.I2CFFRX.all = 0x0000;

        // Generate STOP condition
        I2caRegs.I2CMDR.bit.STP = 1;

        return ERROR_NACK_RECEIVED;
    }

    // Check if timeout
    if(timeoutCheck == 0)
    {
        // disable FIFO
        I2caRegs.I2CFFTX.all = 0x0000;
        I2caRegs.I2CFFRX.all = 0x0000;

        // Generate STOP condition
        I2caRegs.I2CMDR.bit.STP = 1;

        return ERROR_TIMEOUT;
    }

    // Update variable for timeout checking
    timeoutCheck--;

    return SUCCESS;
}

//
// End of file
//
