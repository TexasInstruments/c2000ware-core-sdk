//###########################################################################
//
// FILE:   lin.c
//
// TITLE:  C28x LIN driver.
//
//###########################################################################
// $Copyright:
// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com/
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
#include "lin.h"

//*****************************************************************************
//
// LIN_initModule
//
//*****************************************************************************
void
LIN_initModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    EALLOW;

    //
    // Reset LIN module
    // Release from hard reset
    //
    LIN_disableModule(base);
    LIN_enableModule(base);

    //
    // Enter Software Reset State
    //
    LIN_enterSoftwareReset(base);

    //
    // Enable LIN Mode
    //
    LIN_disableSCIMode(base);

    //
    // Set LIN mode to Commander
    //
    LIN_setLINMode(base, LIN_MODE_LIN_COMMANDER);

    //
    // Enable Fixed baud rate mode
    //
    LIN_disableAutomaticBaudrate(base);

    //
    // Use the set frame length and not ID4/ID5 bits for length control
    //
    LIN_setCommMode(base, LIN_COMM_LIN_USELENGTHVAL);

    //
    // Setup to continue operating on emulation suspend
    //
    LIN_setDebugSuspendMode(base, LIN_DEBUG_COMPLETE);

    //
    // Use Enhanced Checksum
    //
    LIN_setChecksumType(base, LIN_CHECKSUM_ENHANCED);

    //
    // Message filtering uses responder task ID byte
    //
    LIN_setMessageFiltering(base, LIN_MSG_FILTER_IDRESPONDER);

    //
    // Disable Internal loopback for external communication
    //
    LIN_disableIntLoopback(base);

    //
    // Enable multi-buffer mode
    //
    LIN_enableMultibufferMode(base);

    //
    // Enable parity check on received ID
    //
    LIN_enableParity(base);

    //
    // Enable transfer of data to and from the shift registers
    //
    LIN_enableDataTransmitter(base);
    LIN_enableDataReceiver(base);

    //
    // Enable the triggering of checksum compare on extended frames
    //
    LIN_triggerChecksumCompare(base);

    //
    // Set LIN interrupts to disabled
    //
    LIN_disableInterrupt(base, LIN_INT_ALL);

    //
    // Set Baud Rate Settings - 100MHz Device
    //
    LIN_setBaudRatePrescaler(base, 96U, 11U);
    LIN_setMaximumBaudRate(base, 100000000U, 20000U);

    //
    // Set response field to 1 byte
    //
    LIN_setFrameLength(base, 1U);

    //
    // Configure sync field
    // Sync break (13 + 5 = 18 Tbits)
    // Sync delimiter (1 + 3 = 4 Tbits)
    //
    LIN_setSyncFields(base, 5U, 3U);

    //
    // Set Mask ID so TX/RX match will always happen
    //
    LIN_setTxMask(base, 0xFFU);
    LIN_setRxMask(base, 0xFFU);

    //
    // Disable IODFT testing and external loopback mode
    //
    LIN_disableExtLoopback(base);

    //
    // Finally exit SW reset and enter LIN ready state
    //
    LIN_exitSoftwareReset(base);

    EDIS;
}

//*****************************************************************************
//
// LIN_initSCIModule
//
//*****************************************************************************
void
LIN_initSCIModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    EALLOW;

    //
    // Reset LIN module
    // Release from hard reset
    //
    LIN_disableModule(base);
    LIN_enableModule(base);

    //
    // Enter LIN reset state to perform configurations
    //
    LIN_enterSoftwareReset(base);

    //
    // Switch LIN into SCI mode
    //
    LIN_enableSCIMode(base);

    //
    // Set the SCI communication mode to idle line
    //
    LIN_setSCICommMode(base, LIN_COMM_SCI_IDLELINE);

    //
    // Module set to complete operations when halted by debugger
    //
    LIN_setDebugSuspendMode(base, LIN_DEBUG_COMPLETE);

    //
    // Disable Internal loopback for external communication
    //
    LIN_disableIntLoopback(base);

    //
    // Set SCI to transmit one stop bit
    //
    LIN_setSCIStopBits(base, LIN_SCI_STOP_ONE);

    //
    // Disable multi-buffer mode
    //
    LIN_disableMultibufferMode(base);

    //
    // Disable parity check
    //
    LIN_disableSCIParity(base);

    //
    // Enable transfer of data to and from the shift registers
    //
    LIN_enableDataTransmitter(base);
    LIN_enableDataReceiver(base);

    //
    // Set SCI interrupts to disabled
    //
    LIN_disableSCIInterrupt(base, LIN_SCI_INT_ALL);

    //
    // Set Baud Rate Settings
    //
    LIN_setBaudRatePrescaler(base, 96U, 11U);

    //
    // Set character length as 8-bits
    //
    LIN_setSCICharLength(base, 8U);

    //
    // Set to 1 character in response field
    //
    LIN_setSCIFrameLength(base, 1U);

    //
    // Disable IODFT testing and external loopback mode
    //
    LIN_disableExtLoopback(base);

    //
    // Finally exit SW reset and enter ready state
    //
    LIN_exitSoftwareReset(base);

    EDIS;
}

//*****************************************************************************
//
// LIN_sendData
//
//*****************************************************************************
void
LIN_sendData(uint32_t base, uint16_t *data)
{
    int16_t i;
    uint16_t length;
    uint16_t *pData;

    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    //
    // Get the length from the SCIFORMAT register.
    //
    length = (uint16_t)((HWREG_BP(base + LIN_O_SCIFORMAT) &
                          LIN_SCIFORMAT_LENGTH_M) >> LIN_SCIFORMAT_LENGTH_S);

    pData = data + length;

    //
    // Shift each 8-bit piece of data into the correct register.
    //
    for(i = (int32_t)length; i >= 0; i--)
    {
        if(pData != 0U)
        {
            HWREGB(base + LIN_O_TD0 + ((uint16_t)i ^ 3U)) = *pData;
            pData--;
        }
    }
}

//*****************************************************************************
//
// LIN_getData
//
//*****************************************************************************
void
LIN_getData(uint32_t base, uint16_t * const data)
{
    uint16_t i;
    uint16_t length;
    uint16_t *pData = data;

    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    //
    // Get the length from the SCIFORMAT register.
    //
    length = (uint16_t)((HWREG_BP(base + LIN_O_SCIFORMAT) &
                         LIN_SCIFORMAT_LENGTH_M) >> LIN_SCIFORMAT_LENGTH_S);

    //
    // Read each 8-bit piece of data.
    //
    for(i = 0U; i <= length; i++)
    {
        if(pData != 0U)
        {
            *pData = HWREGB(base + LIN_O_RD0 + ((uint32_t)i ^ 3U));
            pData++;
        }
    }
}
