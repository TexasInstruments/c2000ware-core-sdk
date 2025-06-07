//#############################################################################
//
// FILE:   clb_ex32_ccsi_socket.c
//
// TITLE:  Function definitions for CCSI socket.
//
//#############################################################################
// $TI Release: $
// 
// 
// C2000Ware v5.05.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
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

//
// Included Files
//
#include <clb_ex32_ccsi_hal.h>
#include <clb_ex32_ccsi_socket.h>
#include <clb_ex32_lp5891.h>
#include <clb_ex32_system_info.h>
#include "driverlib.h"

/* Function Name: CCSI_write
 *
 * Purpose: Write data bytes
 *
 * Parameters:
 * headBytes -> Head bytes of the command.
 * dataBytes -> Data bytes, MSB first.
 * length -> Length of data bytes.
 * checkResponse -> For CLB solution this is a dummy argument
 *
 */
void CCSI_write(uint16_t headBytes, uint16_t *dataBytes, uint16_t length, unsigned int checkResponse)
{
    uint32_t ledXmtFrameSize;
    uint32_t i = 0;

    // Wait for CLB to finish any ongoing transfer
    while(clbXmtDone == 0){}

    // Load data to CLB transfer array
    clbXmtBuffer[0] = (uint32_t)headBytes;
    for(i = 0; i < length; i++)
    {
        clbXmtBuffer[i + 1] = (uint32_t)dataBytes[i];
    }

    ledXmtFrameSize = i + 1;

    if(checkResponse)
    {
        // Trash any data in the RX CLB
        CCSI_HAL_ringBufferReset();

        // Enable the RX CLB
        CCSI_HAL_enableClbReceiver();
    }

    //
    // Start CLB transfer
    //
    CCSI_HAL_clbTransferNonBlocking(&clbXmtBuffer[0], ledXmtFrameSize);

    if(checkResponse)
    {
        processReadData(headBytes, ledXmtFrameSize, FALSE);

        // Disable the receiver
        CCSI_HAL_disableClbReceiver();
    }
}

void CCSI_write_sync(uint16_t headBytes, uint16_t *dataBytes, uint16_t length)
{
    uint32_t ledXmtFrameSize;
    uint32_t i = 0;

    // Wait for CLB to finish any ongoing transfer
    while(clbXmtDone == 0){}

    // Load data to CLB transfer array
    clbXmtBuffer[0] = (uint32_t)headBytes;
    for(i = 0; i < length; i++)
    {
        clbXmtBuffer[i + 1] = (uint32_t)dataBytes[i];
    }

    ledXmtFrameSize = i + 1;

    //
    // Prepare CLB for transfer, but do not start transfer yet
    //
    CCSI_HAL_clbTransferNonBlocking(&clbXmtBuffer[0], ledXmtFrameSize);
}


/* Function Name: processReadData
 *
 * Purpose: Process the RX data buffer from CLB
 *
 * Parameters:
 * length -> Length of data bytes requested.
 * compareCheckBit -> Check the buffer if CHECK bit was successfully received.
 *
 */
void processReadData(uint16_t headBytes, uint16_t length, unsigned int compareCheckBit)
{
    uint16_t rcvCount = 1;
    uint16_t checkByte;
    uint16_t data;
    uint16_t max_trials = 16 * MAX_DATA_LENGTH;

    if(headBytes == W_CHIP_INDEX) {
        checkByte = (W_CHIP_INDEX + CASCADED_UNITS);
    }
    else {
        checkByte = headBytes;
    }

    // Clear first index
    clbRcvBuffer[0] = 0;

    // First wait until headByte is received - It might be that data from previous transmission is first received
    while((max_trials > 0) & (!(clbRcvBuffer[0] == checkByte))) {
        if (CCSI_HAL_clbRxRingBuffRead(&data) == 0) {
            clbRcvBuffer[0] = data;
        }
        max_trials--;
    }

    // Wait for receive data bytes
    if(max_trials > 0) {
        while(rcvCount < length)
        {
            if (CCSI_HAL_clbRxRingBuffRead(&clbRcvBuffer[rcvCount]) == 0)
                rcvCount++;
        }
    }
}

/* Function Name: CCSI_read
 *
 * Purpose: Read data bytes
 *
 * Parameters:
 * headBytes -> Head bytes of the command.
 *
 */
void CCSI_read(uint16_t headBytes)
{
    uint16_t data[1] = {0x0000};

    // Wait for CLB to finish any ongoing transfer
    while(clbXmtDone == 0){}

    // Trash any data in the RX CLB
    CCSI_HAL_ringBufferReset();

    // Enable the RX CLB
    CCSI_HAL_enableClbReceiver();

    CCSI_write(headBytes, data, 0, FALSE);

    processReadData(headBytes, (CASCADED_UNITS * 3) + 1, FALSE);

    // Disable the receiver
    CCSI_HAL_disableClbReceiver();
}
