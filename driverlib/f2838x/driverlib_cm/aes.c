//###########################################################################
//
// FILE:   aes.c
//
// TITLE:  Driver for the AES module.
//
//###########################################################################
// $Copyright:
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com
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

#include "aes.h"

//*****************************************************************************
//
// AES_configureModule
//
//*****************************************************************************
void
AES_configureModule(uint32_t base, const AES_ConfigParams *config)
{
    //
    // Check the arguments.
    //
    ASSERT(AES_isBaseValid(base));

    //
    // Write the ctrl register with new value and backup the save context field
    //
    HWREG_BP(base + AES_O_CTRL) = ((HWREG_BP(base + AES_O_CTRL) &
                                    ~AES_CONFIG_M)  |
                                   ((uint32_t)config->direction  |
                                    (uint32_t)config->keySize  |
                                    (uint32_t)config-> opMode     |
                                    (uint32_t)config->ctrWidth |
                                    (uint32_t)config->ccmLenWidth |
                                    (uint32_t)config->ccmAuthLenWidth));
}

//*****************************************************************************
//
// AES_setKey1
//
//*****************************************************************************
void
AES_setKey1(uint32_t base, const uint32_t key[], AES_KeySize keySize)
{
    //
    // Check the arguments.
    //
    ASSERT(AES_isBaseValid(base));

    //
    // With all key sizes, the first 4 words are written.
    //
    HWREG_BP(base + AES_O_KEY1_0) = key[0U];
    HWREG_BP(base + AES_O_KEY1_1) = key[1U];
    HWREG_BP(base + AES_O_KEY1_2) = key[2U];
    HWREG_BP(base + AES_O_KEY1_3) = key[3U];

    //
    // The key is 192 or 256 bits.  Write the next 2 words.
    //
    if(keySize != AES_KEY_SIZE_128BIT)
    {
        HWREG_BP(base + AES_O_KEY1_4) = key[4U];
        HWREG_BP(base + AES_O_KEY1_5) = key[5U];
    }

    //
    // The key is 256 bits.  Write the last 2 words.
    //
    if(keySize == AES_KEY_SIZE_256BIT)
    {
        HWREG_BP(base + AES_O_KEY1_6) = key[6U];
        HWREG_BP(base + AES_O_KEY1_7) = key[7U];
    }
}

//*****************************************************************************
//
// AES_setKey2
//
//*****************************************************************************
void
AES_setKey2(uint32_t base, const uint32_t key[], AES_KeySize keySize)
{
    //
    // Check the arguments.
    //
    ASSERT(AES_isBaseValid(base));

    //
    // With all key sizes, the first 4 words are written.
    //
    HWREG_BP(base + AES_O_KEY2_0) = key[0U];
    HWREG_BP(base + AES_O_KEY2_1) = key[1U];
    HWREG_BP(base + AES_O_KEY2_2) = key[2U];
    HWREG_BP(base + AES_O_KEY2_3) = key[3U];

    //
    // The key is 192 or 256 bits.  Write the next 2 words.
    //
    if(keySize != AES_KEY_SIZE_128BIT)
    {
        HWREG_BP(base + AES_O_KEY2_4) = key[4U];
        HWREG_BP(base + AES_O_KEY2_5) = key[5U];
    }

    //
    // The key is 256 bits.  Write the last 2 words.
    //
    if(keySize == AES_KEY_SIZE_256BIT)
    {
        HWREG_BP(base + AES_O_KEY2_6) = key[6U];
        HWREG_BP(base + AES_O_KEY2_7) = key[7U];
    }
}

//*****************************************************************************
//
// AES_setKey3
//
//*****************************************************************************
void
AES_setKey3(uint32_t base, const uint32_t key[])
{
    //
    // Check the arguments.
    //
    ASSERT(AES_isBaseValid(base));

    //
    // With all key sizes, the first 4 words are written.
    //
    HWREG_BP(base + AES_O_KEY2_4) = key[0U];
    HWREG_BP(base + AES_O_KEY2_5) = key[1U];
    HWREG_BP(base + AES_O_KEY2_6) = key[2U];
    HWREG_BP(base + AES_O_KEY2_7) = key[3U];
}

//*****************************************************************************
//
// AES_setInitializationVector
//
//*****************************************************************************
void
AES_setInitializationVector(uint32_t base, const uint32_t iniVector[])
{
    //
    // Check the arguments.
    //
    ASSERT(AES_isBaseValid(base));

    //
    // Set Initialization vector.
    //
    HWREG_BP(base + AES_O_IV_IN_OUT_0) = iniVector[0U];
    HWREG_BP(base + AES_O_IV_IN_OUT_1) = iniVector[1U];
    HWREG_BP(base + AES_O_IV_IN_OUT_2) = iniVector[2U];
    HWREG_BP(base + AES_O_IV_IN_OUT_3) = iniVector[3U];
}

//*****************************************************************************
//
// AES_readInitializationVector
//
//*****************************************************************************
void
AES_readInitializationVector(uint32_t base, uint32_t iniVector[])
{
    //
    // Check the arguments.
    //
    ASSERT(AES_isBaseValid(base));

    //
    // Read the initialization vector
    //
    iniVector[0U] = HWREG_BP(base + AES_O_IV_IN_OUT_0);
    iniVector[1U] = HWREG_BP(base + AES_O_IV_IN_OUT_1);
    iniVector[2U] = HWREG_BP(base + AES_O_IV_IN_OUT_2);
    iniVector[3U] = HWREG_BP(base + AES_O_IV_IN_OUT_3);

}

//*****************************************************************************
//
// AES_readTag
//
//*****************************************************************************
void
AES_readTag(uint32_t base, uint32_t tagData[])
{
    //
    // Check the arguments.
    //
    ASSERT(AES_isBaseValid(base));

    //
    // Wait for the output context to be ready.
    //
    while((AES_CTRL_SVCTXTRDY & (HWREG_BP(base + AES_O_CTRL))) !=
          AES_CTRL_SVCTXTRDY)
    {
    }

    //
    // Read the tag data.
    //
    tagData[0U] = HWREG_BP(base + AES_O_TAG_OUT_0);
    tagData[1U] = HWREG_BP(base + AES_O_TAG_OUT_1);
    tagData[2U] = HWREG_BP(base + AES_O_TAG_OUT_2);
    tagData[3U] = HWREG_BP(base + AES_O_TAG_OUT_3);
}

//*****************************************************************************
//
// AES_readDataNonBlocking
//
//*****************************************************************************
bool
AES_readDataNonBlocking(uint32_t base, uint32_t destArray[])
{
    bool temp;

    //
    // Check the arguments.
    //
    ASSERT(AES_isBaseValid(base));

    //
    // Check if the output is ready before reading the data.  If it is not
    // ready, return false.
    //
    if((AES_CTRL_OUTPUT_READY & (HWREG_BP(base + AES_O_CTRL))) !=
        AES_CTRL_OUTPUT_READY)
    {
        temp = false;
    }
    else
    {
        //
        // Read a block of data from the data registers
        //
        destArray[0U] = HWREG_BP(base + AES_O_DATA_IN_OUT_3);
        destArray[1U] = HWREG_BP(base + AES_O_DATA_IN_OUT_2);
        destArray[2U] = HWREG_BP(base + AES_O_DATA_IN_OUT_1);
        destArray[3U] = HWREG_BP(base + AES_O_DATA_IN_OUT_0);

        //
        // Read successful, return true.
        //
        temp = true;
    }
    return(temp);
}

//*****************************************************************************
//
// AES_readDataBlocking
//
//*****************************************************************************
void
AES_readDataBlocking(uint32_t base, uint32_t destArray[])
{
    //
    // Check the arguments.
    //
    ASSERT(AES_isBaseValid(base));

    //
    // Wait for the output to be ready before reading the data.
    //
    while((AES_CTRL_OUTPUT_READY & (HWREG_BP(base + AES_O_CTRL))) !=
           AES_CTRL_OUTPUT_READY)
    {
    }

    //
    // Read a block of data from the data registers
    //
    destArray[0U] = HWREG_BP(base + AES_O_DATA_IN_OUT_3);
    destArray[1U] = HWREG_BP(base + AES_O_DATA_IN_OUT_2);
    destArray[2U] = HWREG_BP(base + AES_O_DATA_IN_OUT_1);
    destArray[3U] = HWREG_BP(base + AES_O_DATA_IN_OUT_0);
}

//*****************************************************************************
//
// AES_writeDataNonBlocking
//
//*****************************************************************************
bool
AES_writeDataNonBlocking(uint32_t base, const uint32_t srcArray[])
{
    bool temp;

    //
    // Check the arguments.
    //
    ASSERT(AES_isBaseValid(base));

    //
    // Check if the input is ready.  If not, then return false.
    //
    if((AES_CTRL_INPUT_READY & (HWREG_BP(base + AES_O_CTRL))) !=
        AES_CTRL_INPUT_READY)
    {
        temp = false;
    }
    else
    {
        //
        // Write a block of data into the data registers.
        //
        HWREG_BP(base + AES_O_DATA_IN_OUT_3) = srcArray[0U];
        HWREG_BP(base + AES_O_DATA_IN_OUT_2) = srcArray[1U];
        HWREG_BP(base + AES_O_DATA_IN_OUT_1) = srcArray[2U];
        HWREG_BP(base + AES_O_DATA_IN_OUT_0) = srcArray[3U];

        //
        // Write successful, return true.
        //
        temp = true;
    }
    return(temp);
}

//*****************************************************************************
//
// AES_writeDataBlocking
//
//*****************************************************************************
void
AES_writeDataBlocking(uint32_t base, const uint32_t srcArray[])
{
    //
    // Check the arguments.
    //
    ASSERT(AES_isBaseValid(base));

    //
    // Wait for input ready.
    //
    while((AES_CTRL_INPUT_READY & (HWREG_BP(base + AES_O_CTRL))) !=
          AES_CTRL_INPUT_READY)
    {
    }

    //
    // Write a block of data into the data registers.
    //
    HWREG_BP(base + AES_O_DATA_IN_OUT_3) = srcArray[0U];
    HWREG_BP(base + AES_O_DATA_IN_OUT_2) = srcArray[1U];
    HWREG_BP(base + AES_O_DATA_IN_OUT_1) = srcArray[2U];
    HWREG_BP(base + AES_O_DATA_IN_OUT_0) = srcArray[3U];
}

//*****************************************************************************
//
// AES_processData
//
//*****************************************************************************
bool
AES_processData(uint32_t base, const uint32_t srcArray[], uint32_t destArray[],
                uint64_t dataLength)
{
    uint64_t count;

    //
    // Check the arguments.
    //
    ASSERT(AES_isBaseValid(base));

    //
    // Write the length register first, which triggers the engine to start
    // using this context.
    //
    AES_setDataLength(base, dataLength);

    //
    // Now loop until the blocks are written.
    //
    for(count = 0U; count < ((dataLength + 15U) / 16U); count++)
    {
        //
        // Write the data registers.
        //
        AES_writeDataBlocking(base, srcArray + (count * 4U));

        //
        // Read the data registers.
        //
        AES_readDataBlocking(base, destArray + (count * 4U));
    }

    //
    // Return true to indicate successful completion of the function.
    //
    return((bool)true);
}

//*****************************************************************************
//
// AES_authenticateData
//
//*****************************************************************************
bool
AES_authenticateData(uint32_t base, const uint32_t srcArray[],
                     uint64_t dataLength, uint32_t tagArray[])
{
    uint32_t count;

    //
    // Check the arguments.
    //
    ASSERT(AES_isBaseValid(base));

    //
    // Write the length register first, which triggers the engine to start
    // using this context.
    //
    AES_setDataLength(base, dataLength);

    //
    // Now loop until the blocks are written.
    //
    for(count = 0U; count < ((dataLength + 15U) / 16U); count++)
    {
        //
        // Write the data registers.
        //
        AES_writeDataBlocking(base, srcArray + (count * 4U));
    }

    //
    // Read the hash tag value.
    //
    AES_readTag(base, tagArray);

    //
    // Return true to indicate successful completion of the function.
    //
    return((bool)true);
}

//*****************************************************************************
//
// AES_processDatainAuthMode
//
//*****************************************************************************
bool
AES_processDatainAuthMode(uint32_t base, const uint32_t srcArray[],
                          uint32_t destArray[], uint64_t dataLength,
                          const uint32_t authDataArray[],
                          uint32_t authDataLength, uint32_t tagArray[])
{
    uint32_t count;

    //
    // Check the arguments.
    //
    ASSERT(AES_isBaseValid(base));

    //
    // Set the data length.
    //
    AES_setDataLength(base, dataLength);

    //
    // Set the additional authentication data length.
    //
    AES_setAuthDataLength(base, authDataLength);

    //
    // Now loop until the authentication data blocks are written.
    //
    for(count = 0U; count < ((authDataLength  + 15U) / 16U); count++)
    {
        //
        // Write the data registers.
        //
        AES_writeDataBlocking(base, authDataArray + (count * 4U));
    }

    //
    // Now loop until the data blocks are written.
    //
    for(count = 0U; count < ((dataLength + 15U) / 16U); count++)
    {
        //
        // Write the data registers.
        //
        AES_writeDataBlocking(base, srcArray + (count * 4U));

        //
        //
        // Read the data registers.
        //
        AES_readDataBlocking(base, destArray + (count * 4U));
    }

    //
    // Read the hash tag value.
    //
    AES_readTag(base, tagArray);

    //
    // Return true to indicate successful completion of the function.
    //
    return((bool)true);
}

//*****************************************************************************
//
// AES_getInterruptStatus
//
//*****************************************************************************
uint32_t
AES_getInterruptStatus(uint32_t base, uint32_t wrapperBase, bool intMask)
{
    uint32_t intStatus, intEnable;

    //
    // Check the arguments.
    //
    ASSERT(AES_isBaseValid(base));
    ASSERT(AES_isWrapperBaseValid(wrapperBase));

    //
    // Read the IRQ status register and return the value.
    //
    intStatus = HWREG_BP(base + AES_O_IRQSTATUS) |
                (HWREG_BP(wrapperBase + AES_SS_O_AESDMASTATUS) << 16U);
    if(intMask)
    {
        intEnable = HWREG_BP(base + AES_O_IRQENABLE) |
                    (HWREG_BP(wrapperBase + AES_SS_O_AESDMAINTEN) << 16U);
        intStatus &= intEnable;
    }

    return(intStatus);
}

