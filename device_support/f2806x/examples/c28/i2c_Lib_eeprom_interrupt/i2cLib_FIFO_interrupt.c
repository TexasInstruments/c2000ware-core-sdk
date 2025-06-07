//###########################################################################
//
// FILE:   i2cLib_FIFO_interrupt.c
//
// TITLE:  I2C FIFO Interrupt Library source file.
//
//###########################################################################
// $TI Release: $
// $Release Date: $
// $Copyright:
// Copyright (C) 2009-2025 Texas Instruments Incorporated - http://www.ti.com/
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

#include "i2cLib_FIFO_interrupt.h"

//
// Global variables used by i2cLib_FIFO_interrupt
//
Uint16 timeoutCheck;
Uint16 numofBytes;      // Tracks pMsgBuffer index
Uint16 numofFourBytes;
Uint16 remainingBytes;

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
// I2C_MasterWrite - This function configures the I2C module for
//      transmitting the full I2C message of the passed I2CHandle utilizing
//      the I2C FIFO ISR, i2cFIFO_isr.
//
//      Function sequence is the following:
//
//      1. Generate START condition and transmit SlaveAddr
//      2. Transmit NumOfControlBytes in pControlBuffer
//      3. Configure TX FIFO interrupts
//      4. TX of bytes in pMsgBuffer handled in i2cFIFO_isr
//      5. STOP condition generated in i2cFIFO_isr
//
Uint16 I2C_MasterWrite(struct I2CHandle *I2C_Params)
{
    Uint16 status;

    if(I2C_Params->NumOfDataBytes > MAX_BUFFER_SIZE)
    {
        return ERROR_BUFFER_MAX;
    }

    // Enable TX FIFO
    I2caRegs.I2CFFTX.all = 0x6000;

    // Set I2CCNT for number of bytes to transmit
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

    // Reset numofBytes for pMsgBuffer index tracking
    numofBytes = 0;

    //
    // Calculate number of bytes to be transmitted out of the FIFO
    //
    numofFourBytes  = (I2C_Params->NumOfDataBytes) / I2C_FIFO_LEVEL;
    remainingBytes    = (I2C_Params->NumOfDataBytes) % I2C_FIFO_LEVEL;

    // Enable I2C NACK interrupt
    I2caRegs.I2CIER.bit.NACK = 1;

    //
    // Set I2C TX FIFO Interrupt Levels
    //

    // Configure TX FIFO interrupt to trigger when EMPTY
    I2caRegs.I2CFFTX.bit.TXFFIL = 0;

    // Enable TX FIFO level interrupt
    I2caRegs.I2CFFTX.bit.TXFFIENA = 1;

    // Clear TX FIFO level interrupt
    I2caRegs.I2CFFTX.bit.TXFFINTCLR = 1;

    return SUCCESS;
}

//
// I2C_MasterWrite - This function configures the I2C module for receiving
//      the full I2C message of the passed I2CHandle utilizing the I2C FIFO
//      ISR, i2cFIFO_isr.
//
//      Function sequence is the following:
//
//      1. Generate START condition and transmit SlaveAddr
//      2. Transmit NumOfControlBytes in pControlBuffer
//      3. Configure RX FIFO and interrupts
//      4. Generate repeated START condition
//      5. RX of bytes in pMsgBuffer handled in i2cFIFO_isr
//      6. STOP condition generated in i2cFIFO_isr
//
Uint16 I2C_MasterRead(struct I2CHandle *I2C_Params)
{
    Uint16 status;

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

    // Set I2CCNT for number of bytes to receive
    I2caRegs.I2CCNT = I2C_Params->NumOfDataBytes;

    // Reset numofBytes for pMsgBuffer index tracking
    numofBytes = 0;

    //
    // Calculate number of bytes to be received into the FIFO
    //
    numofFourBytes  = (I2C_Params->NumOfDataBytes) / I2C_FIFO_LEVEL;
    remainingBytes    = (I2C_Params->NumOfDataBytes) % I2C_FIFO_LEVEL;

    // Enable RX FIFO
    I2caRegs.I2CFFRX.all = 0x2040;

    //
    // Set I2C TX FIFO Interrupt Levels
    //
    if(numofFourBytes)
    {
        // Configure RX FIFO interrupt to trigger when FULL
        I2caRegs.I2CFFRX.bit.RXFFIL = I2C_FIFO_LEVEL;
    }
    else
    {
        // Configure RX FIFO interrupt to trigger for remainingBytes
        I2caRegs.I2CFFRX.bit.RXFFIL = remainingBytes;
    }

    // Clear RX FIFO level interrupt
    I2caRegs.I2CFFRX.bit.RXFFINTCLR = 1;

    // Enable RX FIFO level interrupt
    I2caRegs.I2CFFRX.bit.RXFFIENA = 1;

    //
    // Set up as master receiver
    // FREE + MST + IRS
    //
    I2caRegs.I2CMDR.all = 0x4420;

    I2caRegs.I2CMDR.bit.STT = 0x1; // Send repeated START condition

    return SUCCESS;
}

//
// i2c_isr - This ISR is for handling basic I2C interrupts.
//
interrupt void i2c_isr(void)
{
    Uint16 intSource;

    //
    // Read interrupt source
    //
    intSource = I2caRegs.I2CISRC.all;

    if(intSource == I2C_NACK_ISRC)
    {
        // NACK Received
        handleNACK();

        // Disable I2C NACK interrupt
        I2caRegs.I2CIER.bit.NACK = 0;

        ESTOP0;
    }

    if(intSource == I2C_ARB_ISRC)
    {
        //Arbitration lost
        ESTOP0;
    }

    //
    // Enable future I2C (PIE Group 8) interrupts
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
}

//
// i2cFIFO_isr - This ISR is for handling both TX and rX I2C FIFO
//      interrupts.
//
interrupt void i2cFIFO_isr(void)
{
    Uint16 i;
    Uint16 TxFIFOInt, RxFifoInt;

    //
    // Read I2C FIFO interrupt sources
    //
    TxFIFOInt = I2caRegs.I2CFFTX.bit.TXFFINT;
    RxFifoInt = I2caRegs.I2CFFRX.bit.RXFFINT;

    if((TxFIFOInt) || (RxFifoInt))
    {
        //
        // If there are no more bytes to TX or RX...
        //
        if((remainingBytes == 0) && (numofFourBytes == 0))
        {
            // disable FIFOs
            I2caRegs.I2CFFTX.all = 0x0000;
            I2caRegs.I2CFFRX.all = 0x0000;

            // Disable I2C NACK interrupt
            I2caRegs.I2CIER.bit.NACK = 0;

            // Generate STOP condition
            I2caRegs.I2CMDR.bit.STP = 1;
        }

        //
        // Write or read remaining bytes.
        //
        if(remainingBytes && (numofFourBytes == 0))
        {
            for(i=0;i<remainingBytes;i++)
            {
                if(TxFIFOInt)
                {
                    // Write to I2C transmit FIFO
                    I2caRegs.I2CDXR = currentResponderPtr->pMsgBuffer[numofBytes++];
                }
                if(RxFifoInt)
                {
                    // Read from I2C receive FIFO
                    currentResponderPtr->pMsgBuffer[numofBytes++] = I2caRegs.I2CDRR;
                }
            }
            remainingBytes = 0;
        }

        //
        // Write or read bytes using the full I2C_FIFO_LEVEL.
        //
        if(numofFourBytes)
        {
            if(TxFIFOInt)
            {
                for(i=0;i<I2C_FIFO_LEVEL;i++)
                {
                    // Write to I2C transmit FIFO
                    I2caRegs.I2CDXR = currentResponderPtr->pMsgBuffer[numofBytes++];
                }
            }

            if(RxFifoInt)
            {
                for(i=0;i<I2C_FIFO_LEVEL;i++)
                {
                    // Read from I2C receive FIFO
                    currentResponderPtr->pMsgBuffer[numofBytes++] = I2caRegs.I2CDRR;
                }
            }
            numofFourBytes--;
        }

        //
        // No more numofFourBytes to TX or RX.
        // Configure FIFO interrupts for remainingBytes
        //
        if(numofFourBytes == 0)
        {
            // Configure TX FIFO interrupt to trigger when EMPTY
            I2caRegs.I2CFFTX.bit.TXFFIL = 0;

            // Configure RX FIFO interrupt to trigger for remainingBytes
            I2caRegs.I2CFFRX.bit.RXFFIL = remainingBytes;
        }

        // Clear FIFO level interrupts to receive more
        I2caRegs.I2CFFTX.bit.TXFFINTCLR = 1;
        I2caRegs.I2CFFRX.bit.RXFFINTCLR = 1;
    }

    //
    // Enable future I2C (PIE Group 8) interrupts
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
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
