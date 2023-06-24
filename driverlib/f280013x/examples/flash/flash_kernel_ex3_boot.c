//###########################################################################
//
// FILE:    flashapi_ex3_boot.c
//
// TITLE:   Boot Source Code
//! \addtogroup driver_example_list
//! <h1> Boot Source Code </h1>
//!
//! Functions:
//!
//!     void   copyData(void)
//!     uint32_t getLongData(void)
//!     void readReservedFn(void)
//
//###########################################################################
// $Copyright:
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
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

//
// Includes
//
#include "cpu1bootrom.h"
#include "flash_kernel_ex3_commands.h"
#include "FlashTech_F280013x_C28x.h"
#include "cpu1bootrom.h"
#include "cpu1brom_boot_modes.h"
#include "flash_programming_f280013x.h"


#include "assert.h"

//
// Globals
//

// getWordData is a pointer to the function that interfaces to the peripheral.
// Each loader assigns this pointer to it's particular getWordData function.
//
uint16fptr getWordData;

typedef struct
{
    uint16_t status;
    uint32_t address;
    uint16_t flashAPIError;
    uint32_t flashAPIFsmStatus;
} StatusCode;
extern StatusCode statusCode;

//
// Because of ECC, must be multiple of 64 bits, or 4 words, BUFFER_SIZE % 4 == 0
//
#define BUFFER_SIZE                 0x80 

//
// Function Prototypes
//
extern void sciSendChecksum(void);
uint32_t getLongData(void);
void copyData(void);
void readReservedFn(void);
uint32_t findSector(uint32_t address);
uint16_t findSize(uint32_t address);
void exampleError(Fapi_StatusType status);
void setFlashAPIError(Fapi_StatusType status);

//
// 128 sectors.
//
unsigned char erasedAlready[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

//
// void CopyData(void) - This routine copies multiple blocks of data from the host
//                       to the specified RAM locations.  There is no error
//                       checking on any of the destination addresses.
//                       That is it is assumed all addresses and block size
//                       values are correct.
//
//                       Multiple blocks of data are copied until a block
//                       size of 00 00 is encountered.
//
void copyData()
{
    struct HEADER
    {
        uint16_t BlockSize;
        uint32_t DestAddr;
    } BlockHeader;

    uint16_t Buffer[BUFFER_SIZE];
    
    //
    // useful for 8-word access to flash with
    //
    uint16_t miniBuffer[8]; 
    uint16_t i = 0;
    uint16_t j = 0;
    uint16_t k = 0;
    uint32_t sectorAddress;
    uint16_t sectorSize;
    uint16_t wordData;
    uint16_t wordsWritten = 0;
    int fail = 0;

    assert(BUFFER_SIZE % 8 == 0);

    if (statusCode.status != NO_ERROR)
    {
        fail++;
    }

    //
    // Reset erase status of all flash sectors
    // 36 sectors.
    //
    for (i = 0; i < 32; i++)
    {
        erasedAlready[i] = 0;
    }

    //
    // Send checksum to satisfy before we begin
    //
#if checksum_enable
    sciSendChecksum();
#endif

    //
    // Get the size in words of the first block
    //
    BlockHeader.BlockSize = (*getWordData)();

    //
    // While the block size is > 0 copy the data
    // to the DestAddr.  There is no error checking
    // as it is assumed the DestAddr is a valid
    // memory location
    //

    EALLOW;
    while (BlockHeader.BlockSize != (uint16_t) 0x0000)
    {
        Fapi_StatusType oReturnCheck;
        Fapi_FlashStatusWordType oFlashStatusWord;
        Fapi_FlashStatusType oFlashStatus;
       
        BlockHeader.DestAddr = getLongData();
        for (i = 0; i < BlockHeader.BlockSize; i += 0)
        {
            if (BlockHeader.BlockSize < BUFFER_SIZE)
            {
                for (j = 0; j < BlockHeader.BlockSize; j++)
                {
                    wordData = (*getWordData)();
                    Buffer[j] = wordData;
                    i++;
                }
                for (j = BlockHeader.BlockSize; j < BUFFER_SIZE; j++)
                {
                    Buffer[j] = 0xFFFF;
                }
            }
            
            //
            // BlockHeader.BlockSize >= BUFFER_SIZE
            //
            else 
            {
                //
                // less than one BUFFER_SIZE left
                //
                if ((BlockHeader.BlockSize - i) < BUFFER_SIZE) 
                {
                    //
                    // fill Buffer with rest of data
                    //
                    for (j = 0; j < BlockHeader.BlockSize - i; j++) 
                    {
                        wordData = (*getWordData)();
                        Buffer[j] = wordData;
                    }
                    
                    //
                    // increment i outside here so it doesn't affect loop above
                    //
                    i += j; 
                    
                    //
                    // fill the rest with 0xFFFF
                    //
                    for (; j < BUFFER_SIZE; j++) 
                    {
                        Buffer[j] = 0xFFFF;
                    }
                }
                else
                {
                    //
                    // fill up like normal, up to BUFFER_SIZE
                    //
                    for (j = 0; j < BUFFER_SIZE; j++) 
                    {
                        wordData = (*getWordData)();
                        Buffer[j] = wordData;
                        i++;
                    }
                }
            }
            for (k = 0; k < (BUFFER_SIZE / 8); k++)
            {
                miniBuffer[0] = Buffer[k * 8 + 0];
                miniBuffer[1] = Buffer[k * 8 + 1];
                miniBuffer[2] = Buffer[k * 8 + 2];
                miniBuffer[3] = Buffer[k * 8 + 3];
                miniBuffer[4] = Buffer[k * 8 + 4];
                miniBuffer[5] = Buffer[k * 8 + 5];
                miniBuffer[6] = Buffer[k * 8 + 6];
                miniBuffer[7] = Buffer[k * 8 + 7];
                
                //
                // check that all the words have not already been written
                //
                if (wordsWritten < BlockHeader.BlockSize)
                {
                    if(fail == 0)
                    {
                        //
                        // clean out flash banks if needed
                        //
                        sectorAddress = findSector(BlockHeader.DestAddr);
                        if (sectorAddress != 0xdeadbeef)
                        {
                            //
                            // FindSize returns size of sector in 32 bit words. 
                            //
                            sectorSize = findSize(sectorAddress);
                            //
                            // Wait until FSM is done with the previous flash operation
                            //
                            while (Fapi_checkFsmForReady() != Fapi_Status_FsmReady){}
                            oFlashStatus = Fapi_getFsmStatus();
                            if(oFlashStatus != 0)
                            {

                                /* Clear the Status register */
                                oReturnCheck = Fapi_issueAsyncCommand(Fapi_ClearStatus);
                                //
                                // Wait until status is cleared
                                //
                                while (Fapi_getFsmStatus() != 0) {}

                                if(oReturnCheck != Fapi_Status_Success)
                                {
                                statusCode.status = CLEAR_STATUS_ERROR;
                                statusCode.address = 0;
                                setFlashAPIError(oReturnCheck);
                                statusCode.flashAPIFsmStatus = 0; // not used here
                                fail++;
                                }
                            }
                            //
                            // Disable erase/program protection
                            // CMDWEPROTA is applicable for sectors 0-31
                            // Bits 0-11 of CMDWEPROTB is applicable for sectors 32-127, each bit represents
                            // a group of 8 sectors, e.g bit 0 represents sectors 32-39, bit 1 represents
                            // sectors 40-47, etc
                            //
                            Fapi_setupBankSectorEnable(FLASH_WRAPPER_PROGRAM_BASE+FLASH_O_CMDWEPROTA, 0);
                            Fapi_setupBankSectorEnable(FLASH_WRAPPER_PROGRAM_BASE+FLASH_O_CMDWEPROTB, 0);

                            oReturnCheck = Fapi_issueAsyncCommandWithAddress(
                                    Fapi_EraseSector, (uint32_t *) sectorAddress);

                            while (Fapi_checkFsmForReady() != Fapi_Status_FsmReady){}
                            
                            oFlashStatus = Fapi_getFsmStatus();

                            oReturnCheck = Fapi_doBlankCheck(
                                    (uint32_t *) sectorAddress, sectorSize,
                                    &oFlashStatusWord);
                            if (oReturnCheck != Fapi_Status_Success || oFlashStatus != 3)
                            {
                                //
                                //first fail
                                //
                                if (fail == 0) 
                                {
                                    statusCode.status = BLANK_ERROR;
                                    statusCode.address =
                                            oFlashStatusWord.au32StatusWord[0];
                                    setFlashAPIError(oReturnCheck);
                                    statusCode.flashAPIFsmStatus = oFlashStatus;
                                }
                                fail++;
                            }
                        }
                    }
                    if(fail == 0)
                    {
                        //
                        // Wait until FSM is done with the previous flash operation
                        //
                        while (Fapi_checkFsmForReady() != Fapi_Status_FsmReady){}
                        oFlashStatus = Fapi_getFsmStatus();
                        if(oFlashStatus != 0)
                        {

                            /* Clear the Status register */
                            oReturnCheck = Fapi_issueAsyncCommand(Fapi_ClearStatus);
                            //
                            // Wait until status is cleared
                            //
                            while (Fapi_getFsmStatus() != 0) {}

                            if(oReturnCheck != Fapi_Status_Success)
                            {
                            statusCode.status = CLEAR_STATUS_ERROR;
                            statusCode.address = 0;
                            setFlashAPIError(oReturnCheck);
                            statusCode.flashAPIFsmStatus = 0; // not used here
                            fail++;
                            }
                        }
                        //
                        // Disable erase/program protection
                        // Bits 0-11 of CMDWEPROTB is applicable for sectors 32-127, each bit represents
                        // a group of 8 sectors, e.g bit 0 represents sectors 32-39, bit 1 represents
                        // sectors 40-47, etc
                        //
                       Fapi_setupBankSectorEnable(FLASH_WRAPPER_PROGRAM_BASE+FLASH_O_CMDWEPROTA, 0);
                       Fapi_setupBankSectorEnable(FLASH_WRAPPER_PROGRAM_BASE+FLASH_O_CMDWEPROTB, 0);
                        //
                        //program 8 words at once, 128-bits
                        //
                        oReturnCheck = Fapi_issueProgrammingCommand(
                                (uint32_t *) BlockHeader.DestAddr, miniBuffer,
                                sizeof(miniBuffer), 0, 0, Fapi_AutoEccGeneration);
                        
                        while (Fapi_checkFsmForReady() == Fapi_Status_FsmBusy);
                        
                        oFlashStatus = Fapi_getFsmStatus();
                        if (oReturnCheck != Fapi_Status_Success || oFlashStatus != 3)
                        {
                            //
                            // first fail
                            //
                            if (fail == 0) 
                            {
                                statusCode.status = PROGRAM_ERROR;
                                statusCode.address =
                                        BlockHeader.DestAddr;
                                setFlashAPIError(oReturnCheck);
                                statusCode.flashAPIFsmStatus = oFlashStatus;
                            }
                            fail++;
                        }
                    }
                    for (j = 0; j < 8; j += 2)
                    {
                        uint32_t toVerify = miniBuffer[j + 1];
                        toVerify = toVerify << 16;
                        toVerify |= miniBuffer[j];
                        if(fail == 0)
                        {
                            oReturnCheck = Fapi_doVerify(
                                    (uint32_t *) (BlockHeader.DestAddr + j), 1,
                                    (uint32_t *) (&toVerify), &oFlashStatusWord);
                            if (oReturnCheck != Fapi_Status_Success)
                            {
                                //
                                // first fail
                                //
                                if (fail == 0) 
                                {
                                    statusCode.status = VERIFY_ERROR;
                                    statusCode.address =
                                            oFlashStatusWord.au32StatusWord[0];
                                    setFlashAPIError(oReturnCheck);
                                    //
                                    // FMSTAT not checked for Verify 
                                    //
                                    statusCode.flashAPIFsmStatus = 0; 
                                }
                                fail++;
                            }
                        }
                    } //for j; for Fapi_doVerify
                } //check if all the words are not already written
                BlockHeader.DestAddr += 0x8;
                wordsWritten += 0x8;
            } //for(int k); loads miniBuffer with Buffer elements
#if checksum_enable
            sciSendChecksum();
#endif
        }
        //
        // get the size of the next block
        //
        BlockHeader.BlockSize = (*getWordData)();
        wordsWritten = 0;
    }
    EDIS;
    return;
}


//
// uint32_t findSector(uint32_t address) - This routine finds what sector the mentioned address
//                                         is a part of.
//
uint32_t findSector(uint32_t address)
{
    //
    //******************** Bzero_sector0~15_start~End *********************
    //
     if((address >= Bzero_Sector0_start) && (address < Bzero_Sector1_start) &&
       (erasedAlready[0] == 0))
    {
        erasedAlready[0] = 1;
        return (uint32_t)Bzero_Sector0_start;
    }
    else if((address >= Bzero_Sector1_start) &&
            (address < Bzero_Sector2_start) && (erasedAlready[1] == 0))
    {
        erasedAlready[1] = 1;
        return (uint32_t)Bzero_Sector1_start;
    }
    else if((address >= Bzero_Sector2_start) &&
            (address < Bzero_Sector3_start) && (erasedAlready[2] == 0))
    {
        erasedAlready[2] = 1;
        return (uint32_t)Bzero_Sector2_start;
    }
    else if((address >= Bzero_Sector3_start) &&
            (address < Bzero_Sector4_start) && (erasedAlready[3] == 0))
    {
        erasedAlready[3] = 1;
        return (uint32_t)Bzero_Sector3_start;
    }
    else if((address >= Bzero_Sector4_start) &&
            (address < Bzero_Sector5_start) && (erasedAlready[4] == 0))
    {
        erasedAlready[4] = 1;
        return (uint32_t)Bzero_Sector4_start;
    }
    else if((address >= Bzero_Sector5_start) &&
            (address < Bzero_Sector6_start) && (erasedAlready[5] == 0))
    {
        erasedAlready[5] = 1;
        return (uint32_t)Bzero_Sector5_start;
    }
    else if((address >= Bzero_Sector6_start) &&
            (address < Bzero_Sector7_start) && (erasedAlready[6] == 0))
    {
        erasedAlready[6] = 1;
        return (uint32_t)Bzero_Sector6_start;
    }
    else if((address >= Bzero_Sector7_start) &&
            (address < Bzero_Sector8_start) && (erasedAlready[7] == 0))
    {
        erasedAlready[7] = 1;
        return (uint32_t)Bzero_Sector7_start;
    }
    else if((address >= Bzero_Sector8_start) &&
            (address < Bzero_Sector9_start) && (erasedAlready[8] == 0))
    {
        erasedAlready[8] = 1;
        return (uint32_t)Bzero_Sector8_start;
    }
    else if((address >= Bzero_Sector9_start) &&
            (address < Bzero_Sector10_start) && (erasedAlready[9] == 0))
    {
        erasedAlready[9] = 1;
        return (uint32_t)Bzero_Sector9_start;
    }
    else if((address >= Bzero_Sector10_start) &&
            (address < Bzero_Sector11_start) && (erasedAlready[10] == 0))
    {
        erasedAlready[10] = 1;
        return (uint32_t)Bzero_Sector10_start;
    }
    else if((address >= Bzero_Sector11_start) &&
            (address < Bzero_Sector12_start) && (erasedAlready[11] == 0))
    {
        erasedAlready[11] = 1;
        return (uint32_t)Bzero_Sector11_start;
    }
    else if((address >= Bzero_Sector12_start) &&
            (address < Bzero_Sector13_start) && (erasedAlready[12] == 0))
    {
        erasedAlready[12] = 1;
        return (uint32_t)Bzero_Sector12_start;
    }
    else if((address >= Bzero_Sector13_start) &&
            (address < Bzero_Sector14_start) && (erasedAlready[13] == 0))
    {
        erasedAlready[13] = 1;
        return (uint32_t)Bzero_Sector13_start;
    }
    else if((address >= Bzero_Sector14_start) &&
            (address < Bzero_Sector15_start) && (erasedAlready[14] == 0))
    {
       erasedAlready[14] = 1;
       return (uint32_t)Bzero_Sector14_start;
    }
    else if((address >= Bzero_Sector15_start) &&
            (address <= Bzero_Sector16_start) && (erasedAlready[15] == 0))
    {
       erasedAlready[15] = 1;
       return (uint32_t)Bzero_Sector15_start;
    }
        else if((address >= Bzero_Sector16_start) &&
            (address < Bzero_Sector17_start) && (erasedAlready[16] == 0))
    {
        erasedAlready[16] = 1;
        return (uint32_t)Bzero_Sector16_start;
    }
    else if((address >= Bzero_Sector17_start) &&
            (address < Bzero_Sector18_start) && (erasedAlready[17] == 0))
    {
        erasedAlready[17] = 1;
        return (uint32_t)Bzero_Sector17_start;
    }
    else if((address >= Bzero_Sector18_start) &&
            (address < Bzero_Sector19_start) && (erasedAlready[18] == 0))
    {
        erasedAlready[18] = 1;
        return (uint32_t)Bzero_Sector18_start;
    }
    else if((address >= Bzero_Sector19_start) &&
            (address < Bzero_Sector20_start) && (erasedAlready[19] == 0))
    {
        erasedAlready[19] = 1;
        return (uint32_t)Bzero_Sector19_start;
    }
    else if((address >= Bzero_Sector20_start) &&
            (address < Bzero_Sector21_start) && (erasedAlready[20] == 0))
    {
        erasedAlready[20] = 1;
        return (uint32_t)Bzero_Sector20_start;
    }
    else if((address >= Bzero_Sector21_start) &&
            (address < Bzero_Sector22_start) && (erasedAlready[21] == 0))
    {
        erasedAlready[21] = 1;
        return (uint32_t)Bzero_Sector21_start;
    }
    else if((address >= Bzero_Sector22_start) &&
            (address < Bzero_Sector23_start) && (erasedAlready[22] == 0))
    {
        erasedAlready[22] = 1;
        return (uint32_t)Bzero_Sector22_start;
    }
    else if((address >= Bzero_Sector23_start) &&
            (address < Bzero_Sector24_start) && (erasedAlready[23] == 0))
    {
        erasedAlready[23] = 1;
        return (uint32_t)Bzero_Sector23_start;
    }
    else if((address >= Bzero_Sector24_start) &&
            (address < Bzero_Sector25_start) && (erasedAlready[24] == 0))
    {
        erasedAlready[24] = 1;
        return (uint32_t)Bzero_Sector24_start;
    }
    else if((address >= Bzero_Sector25_start) &&
            (address < Bzero_Sector26_start) && (erasedAlready[25] == 0))
    {
        erasedAlready[25] = 1;
        return (uint32_t)Bzero_Sector25_start;
    }
    else if((address >= Bzero_Sector26_start) &&
            (address < Bzero_Sector27_start) && (erasedAlready[26] == 0))
    {
        erasedAlready[26] = 1;
        return (uint32_t)Bzero_Sector26_start;
    }
    else if((address >= Bzero_Sector27_start) &&
            (address < Bzero_Sector28_start) && (erasedAlready[27] == 0))
    {
        erasedAlready[27] = 1;
        return (uint32_t)Bzero_Sector27_start;
    }
    else if((address >= Bzero_Sector28_start) &&
            (address < Bzero_Sector29_start) && (erasedAlready[28] == 0))
    {
        erasedAlready[28] = 1;
        return (uint32_t)Bzero_Sector28_start;
    }
    else if((address >= Bzero_Sector29_start) &&
            (address < Bzero_Sector30_start) && (erasedAlready[29] == 0))
    {
       erasedAlready[29] = 1;
       return (uint32_t)Bzero_Sector29_start;
    }
    else if((address >= Bzero_Sector30_start) &&
            (address <= Bzero_Sector31_start) && (erasedAlready[30] == 0))
    {
       erasedAlready[30] = 1;
       return (uint32_t)Bzero_Sector30_start;
    }
    else if((address >= Bzero_Sector31_start) &&
            (address < Bzero_Sector32_start) && (erasedAlready[31] == 0))
    {
        erasedAlready[31] = 1;
        return (uint32_t)Bzero_Sector31_start;
    }
    else if((address >= Bzero_Sector32_start) &&
            (address < Bzero_Sector33_start) && (erasedAlready[32] == 0))
    {
        erasedAlready[32] = 1;
        return (uint32_t)Bzero_Sector32_start;
    }
    else if((address >= Bzero_Sector33_start) &&
            (address < Bzero_Sector34_start) && (erasedAlready[33] == 0))
    {
        erasedAlready[33] = 1;
        return (uint32_t)Bzero_Sector33_start;
    }
    else if((address >= Bzero_Sector34_start) &&
            (address < Bzero_Sector35_start) && (erasedAlready[34] == 0))
    {
        erasedAlready[34] = 1;
        return (uint32_t)Bzero_Sector34_start;
    }
    else if((address >= Bzero_Sector35_start) &&
            (address < Bzero_Sector36_start) && (erasedAlready[35] == 0))
    {
        erasedAlready[35] = 1;
        return (uint32_t)Bzero_Sector35_start;
    }
    else if((address >= Bzero_Sector36_start) &&
            (address < Bzero_Sector37_start) && (erasedAlready[36] == 0))
    {
        erasedAlready[36] = 1;
        return (uint32_t)Bzero_Sector36_start;
    }
    else if((address >= Bzero_Sector37_start) &&
            (address < Bzero_Sector38_start) && (erasedAlready[37] == 0))
    {
        erasedAlready[37] = 1;
        return (uint32_t)Bzero_Sector37_start;
    }
    else if((address >= Bzero_Sector38_start) &&
            (address < Bzero_Sector39_start) && (erasedAlready[38] == 0))
    {
        erasedAlready[38] = 1;
        return (uint32_t)Bzero_Sector38_start;
    }
    else if((address >= Bzero_Sector39_start) &&
            (address < Bzero_Sector40_start) && (erasedAlready[39] == 0))
    {
        erasedAlready[39] = 1;
        return (uint32_t)Bzero_Sector39_start;
    }
    else if((address >= Bzero_Sector40_start) &&
            (address < Bzero_Sector41_start) && (erasedAlready[40] == 0))
    {
        erasedAlready[40] = 1;
        return (uint32_t)Bzero_Sector40_start;
    }
    else if((address >= Bzero_Sector41_start) &&
            (address < Bzero_Sector42_start) && (erasedAlready[41] == 0))
    {
        erasedAlready[41] = 1;
        return (uint32_t)Bzero_Sector41_start;
    }
    else if((address >= Bzero_Sector42_start) &&
            (address < Bzero_Sector43_start) && (erasedAlready[42] == 0))
    {
        erasedAlready[42] = 1;
        return (uint32_t)Bzero_Sector42_start;
    }
    else if((address >= Bzero_Sector43_start) &&
            (address < Bzero_Sector44_start) && (erasedAlready[43] == 0))
    {
        erasedAlready[43] = 1;
        return (uint32_t)Bzero_Sector43_start;
    }
    else if((address >= Bzero_Sector44_start) &&
            (address < Bzero_Sector45_start) && (erasedAlready[44] == 0))
    {
       erasedAlready[44] = 1;
       return (uint32_t)Bzero_Sector44_start;
    }
    else if((address >= Bzero_Sector45_start) &&
            (address <= Bzero_Sector46_start) && (erasedAlready[45] == 0))
    {
       erasedAlready[45] = 1;
       return (uint32_t)Bzero_Sector45_start;
    }
        else if((address >= Bzero_Sector46_start) &&
            (address < Bzero_Sector47_start) && (erasedAlready[46] == 0))
    {
        erasedAlready[46] = 1;
        return (uint32_t)Bzero_Sector46_start;
    }
    else if((address >= Bzero_Sector47_start) &&
            (address < Bzero_Sector48_start) && (erasedAlready[47] == 0))
    {
        erasedAlready[47] = 1;
        return (uint32_t)Bzero_Sector47_start;
    }
    else if((address >= Bzero_Sector48_start) &&
            (address < Bzero_Sector49_start) && (erasedAlready[48] == 0))
    {
        erasedAlready[48] = 1;
        return (uint32_t)Bzero_Sector48_start;
    }
    else if((address >= Bzero_Sector49_start) &&
            (address < Bzero_Sector50_start) && (erasedAlready[49] == 0))
    {
        erasedAlready[49] = 1;
        return (uint32_t)Bzero_Sector49_start;
    }
    else if((address >= Bzero_Sector50_start) &&
            (address < Bzero_Sector51_start) && (erasedAlready[50] == 0))
    {
        erasedAlready[50] = 1;
        return (uint32_t)Bzero_Sector50_start;
    }
    else if((address >= Bzero_Sector51_start) &&
            (address < Bzero_Sector52_start) && (erasedAlready[51] == 0))
    {
        erasedAlready[51] = 1;
        return (uint32_t)Bzero_Sector51_start;
    }
    else if((address >= Bzero_Sector52_start) &&
            (address < Bzero_Sector53_start) && (erasedAlready[52] == 0))
    {
        erasedAlready[52] = 1;
        return (uint32_t)Bzero_Sector52_start;
    }
    else if((address >= Bzero_Sector53_start) &&
            (address < Bzero_Sector54_start) && (erasedAlready[53] == 0))
    {
        erasedAlready[53] = 1;
        return (uint32_t)Bzero_Sector53_start;
    }
    else if((address >= Bzero_Sector54_start) &&
            (address < Bzero_Sector55_start) && (erasedAlready[54] == 0))
    {
        erasedAlready[54] = 1;
        return (uint32_t)Bzero_Sector54_start;
    }
    else if((address >= Bzero_Sector55_start) &&
            (address < Bzero_Sector26_start) && (erasedAlready[55] == 0))
    {
        erasedAlready[55] = 1;
        return (uint32_t)Bzero_Sector55_start;
    }
    else if((address >= Bzero_Sector56_start) &&
            (address < Bzero_Sector57_start) && (erasedAlready[56] == 0))
    {
        erasedAlready[56] = 1;
        return (uint32_t)Bzero_Sector56_start;
    }
    else if((address >= Bzero_Sector57_start) &&
            (address < Bzero_Sector58_start) && (erasedAlready[57] == 0))
    {
        erasedAlready[57] = 1;
        return (uint32_t)Bzero_Sector57_start;
    }
    else if((address >= Bzero_Sector58_start) &&
            (address < Bzero_Sector59_start) && (erasedAlready[58] == 0))
    {
        erasedAlready[58] = 1;
        return (uint32_t)Bzero_Sector58_start;
    }
    else if((address >= Bzero_Sector59_start) &&
            (address < Bzero_Sector30_start) && (erasedAlready[59] == 0))
    {
       erasedAlready[59] = 1;
       return (uint32_t)Bzero_Sector59_start;
    }
    else if((address >= Bzero_Sector60_start) &&
            (address <= Bzero_Sector61_start) && (erasedAlready[60] == 0))
    {
       erasedAlready[60] = 1;
       return (uint32_t)Bzero_Sector60_start;
    }
 else if((address >= Bzero_Sector61_start) &&
         (address < Bzero_Sector62_start) && (erasedAlready[61] == 0))
    {
        erasedAlready[61] = 1;
        return (uint32_t)Bzero_Sector61_start;
    }
    else if((address >= Bzero_Sector62_start) &&
            (address < Bzero_Sector63_start) && (erasedAlready[62] == 0))
    {
        erasedAlready[62] = 1;
        return (uint32_t)Bzero_Sector62_start;
    }
    else if((address >= Bzero_Sector63_start) &&
            (address < Bzero_Sector64_start) && (erasedAlready[63] == 0))
    {
        erasedAlready[63] = 1;
        return (uint32_t)Bzero_Sector63_start;
    }
    else if((address >= Bzero_Sector64_start) &&
            (address < Bzero_Sector65_start) && (erasedAlready[64] == 0))
    {
        erasedAlready[64] = 1;
        return (uint32_t)Bzero_Sector64_start;
    }
    else if((address >= Bzero_Sector65_start) &&
            (address < Bzero_Sector66_start) && (erasedAlready[65] == 0))
    {
        erasedAlready[65] = 1;
        return (uint32_t)Bzero_Sector65_start;
    }
    else if((address >= Bzero_Sector66_start) &&
            (address < Bzero_Sector67_start) && (erasedAlready[66] == 0))
    {
        erasedAlready[66] = 1;
        return (uint32_t)Bzero_Sector66_start;
    }
    else if((address >= Bzero_Sector67_start) &&
            (address < Bzero_Sector68_start) && (erasedAlready[67] == 0))
    {
        erasedAlready[67] = 1;
        return (uint32_t)Bzero_Sector67_start;
    }
    else if((address >= Bzero_Sector68_start) &&
            (address < Bzero_Sector69_start) && (erasedAlready[68] == 0))
    {
        erasedAlready[68] = 1;
        return (uint32_t)Bzero_Sector68_start;
    }
    else if((address >= Bzero_Sector69_start) &&
            (address < Bzero_Sector70_start) && (erasedAlready[69] == 0))
    {
        erasedAlready[69] = 1;
        return (uint32_t)Bzero_Sector69_start;
    }
    else if((address >= Bzero_Sector70_start) &&
            (address < Bzero_Sector71_start) && (erasedAlready[70] == 0))
    {
        erasedAlready[70] = 1;
        return (uint32_t)Bzero_Sector70_start;
    }
    else if((address >= Bzero_Sector71_start) &&
            (address < Bzero_Sector72_start) && (erasedAlready[71] == 0))
    {
        erasedAlready[71] = 1;
        return (uint32_t)Bzero_Sector71_start;
    }
    else if((address >= Bzero_Sector72_start) &&
            (address < Bzero_Sector73_start) && (erasedAlready[72] == 0))
    {
        erasedAlready[72] = 1;
        return (uint32_t)Bzero_Sector72_start;
    }
    else if((address >= Bzero_Sector73_start) &&
            (address < Bzero_Sector74_start) && (erasedAlready[73] == 0))
    {
        erasedAlready[73] = 1;
        return (uint32_t)Bzero_Sector73_start;
    }
    else if((address >= Bzero_Sector74_start) &&
            (address < Bzero_Sector75_start) && (erasedAlready[74] == 0))
    {
       erasedAlready[74] = 1;
       return (uint32_t)Bzero_Sector74_start;
    }
    else if((address >= Bzero_Sector75_start) &&
            (address <= Bzero_Sector76_start) && (erasedAlready[75] == 0))
    {
       erasedAlready[75] = 1;
       return (uint32_t)Bzero_Sector75_start;
    }
        else if((address >= Bzero_Sector76_start) &&
            (address < Bzero_Sector77_start) && (erasedAlready[76] == 0))
    {
        erasedAlready[76] = 1;
        return (uint32_t)Bzero_Sector76_start;
    }
    else if((address >= Bzero_Sector77_start) &&
            (address < Bzero_Sector78_start) && (erasedAlready[77] == 0))
    {
        erasedAlready[77] = 1;
        return (uint32_t)Bzero_Sector77_start;
    }
    else if((address >= Bzero_Sector78_start) &&
            (address < Bzero_Sector79_start) && (erasedAlready[78] == 0))
    {
        erasedAlready[78] = 1;
        return (uint32_t)Bzero_Sector78_start;
    }
    else if((address >= Bzero_Sector79_start) &&
            (address < Bzero_Sector80_start) && (erasedAlready[79] == 0))
    {
        erasedAlready[79] = 1;
        return (uint32_t)Bzero_Sector79_start;
    }
    else if((address >= Bzero_Sector80_start) &&
            (address < Bzero_Sector81_start) && (erasedAlready[80] == 0))
    {
        erasedAlready[80] = 1;
        return (uint32_t)Bzero_Sector80_start;
    }
    else if((address >= Bzero_Sector81_start) &&
            (address < Bzero_Sector82_start) && (erasedAlready[81] == 0))
    {
        erasedAlready[81] = 1;
        return (uint32_t)Bzero_Sector81_start;
    }
    else if((address >= Bzero_Sector82_start) &&
            (address < Bzero_Sector83_start) && (erasedAlready[82] == 0))
    {
        erasedAlready[82] = 1;
        return (uint32_t)Bzero_Sector82_start;
    }
    else if((address >= Bzero_Sector83_start) &&
            (address < Bzero_Sector84_start) && (erasedAlready[83] == 0))
    {
        erasedAlready[83] = 1;
        return (uint32_t)Bzero_Sector83_start;
    }
    else if((address >= Bzero_Sector84_start) &&
            (address < Bzero_Sector85_start) && (erasedAlready[84] == 0))
    {
        erasedAlready[84] = 1;
        return (uint32_t)Bzero_Sector84_start;
    }
    else if((address >= Bzero_Sector85_start) &&
            (address < Bzero_Sector86_start) && (erasedAlready[85] == 0))
    {
        erasedAlready[85] = 1;
        return (uint32_t)Bzero_Sector85_start;
    }
    else if((address >= Bzero_Sector86_start) &&
            (address < Bzero_Sector87_start) && (erasedAlready[86] == 0))
    {
        erasedAlready[86] = 1;
        return (uint32_t)Bzero_Sector86_start;
    }
    else if((address >= Bzero_Sector87_start) &&
            (address < Bzero_Sector88_start) && (erasedAlready[87] == 0))
    {
        erasedAlready[87] = 1;
        return (uint32_t)Bzero_Sector87_start;
    }
    else if((address >= Bzero_Sector88_start) &&
            (address < Bzero_Sector89_start) && (erasedAlready[88] == 0))
    {
        erasedAlready[88] = 1;
        return (uint32_t)Bzero_Sector88_start;
    }
    else if((address >= Bzero_Sector89_start) &&
            (address < Bzero_Sector90_start) && (erasedAlready[89] == 0))
    {
       erasedAlready[89] = 1;
       return (uint32_t)Bzero_Sector89_start;
    }
    else if((address >= Bzero_Sector90_start) &&
            (address <= Bzero_Sector91_start) && (erasedAlready[90] == 0))
    {
       erasedAlready[90] = 1;
       return (uint32_t)Bzero_Sector90_start;
    }
    else if((address >= Bzero_Sector91_start) &&
            (address < Bzero_Sector92_start) && (erasedAlready[91] == 0))
    {
        erasedAlready[91] = 1;
        return (uint32_t)Bzero_Sector91_start;
    }
    else if((address >= Bzero_Sector92_start) &&
            (address < Bzero_Sector93_start) && (erasedAlready[92] == 0))
    {
        erasedAlready[92] = 1;
        return (uint32_t)Bzero_Sector92_start;
    }
    else if((address >= Bzero_Sector93_start) &&
            (address < Bzero_Sector94_start) && (erasedAlready[93] == 0))
    {
        erasedAlready[93] = 1;
        return (uint32_t)Bzero_Sector93_start;
    }
    else if((address >= Bzero_Sector94_start) &&
            (address < Bzero_Sector95_start) && (erasedAlready[94] == 0))
    {
        erasedAlready[94] = 1;
        return (uint32_t)Bzero_Sector94_start;
    }
    else if((address >= Bzero_Sector95_start) &&
            (address < Bzero_Sector96_start) && (erasedAlready[95] == 0))
    {
        erasedAlready[95] = 1;
        return (uint32_t)Bzero_Sector95_start;
    }
    else if((address >= Bzero_Sector96_start) &&
            (address < Bzero_Sector97_start) && (erasedAlready[96] == 0))
    {
        erasedAlready[96] = 1;
        return (uint32_t)Bzero_Sector96_start;
    }
    else if((address >= Bzero_Sector97_start) &&
            (address < Bzero_Sector98_start) && (erasedAlready[97] == 0))
    {
        erasedAlready[97] = 1;
        return (uint32_t)Bzero_Sector97_start;
    }
    else if((address >= Bzero_Sector98_start) &&
            (address < Bzero_Sector99_start) && (erasedAlready[98] == 0))
    {
        erasedAlready[98] = 1;
        return (uint32_t)Bzero_Sector98_start;
    }
    else if((address >= Bzero_Sector99_start) &&
            (address < Bzero_Sector100_start) && (erasedAlready[99] == 0))
    {
        erasedAlready[99] = 1;
        return (uint32_t)Bzero_Sector99_start;
    }
    else if((address >= Bzero_Sector100_start) &&
            (address < Bzero_Sector101_start) && (erasedAlready[100] == 0))
    {
        erasedAlready[100] = 1;
        return (uint32_t)Bzero_Sector100_start;
    }
    else if((address >= Bzero_Sector101_start) &&
            (address < Bzero_Sector102_start) && (erasedAlready[101] == 0))
    {
        erasedAlready[101] = 1;
        return (uint32_t)Bzero_Sector101_start;
    }
    else if((address >= Bzero_Sector102_start) &&
            (address < Bzero_Sector103_start) && (erasedAlready[102] == 0))
    {
        erasedAlready[102] = 1;
        return (uint32_t)Bzero_Sector102_start;
    }
    else if((address >= Bzero_Sector103_start) &&
            (address < Bzero_Sector104_start) && (erasedAlready[103] == 0))
    {
        erasedAlready[103] = 1;
        return (uint32_t)Bzero_Sector103_start;
    }
    else if((address >= Bzero_Sector104_start) &&
            (address < Bzero_Sector105_start) && (erasedAlready[104] == 0))
    {
       erasedAlready[104] = 1;
       return (uint32_t)Bzero_Sector104_start;
    }
    else if((address >= Bzero_Sector105_start) &&
            (address <= Bzero_Sector106_start) && (erasedAlready[105] == 0))
    {
       erasedAlready[105] = 1;
       return (uint32_t)Bzero_Sector105_start;
    }
        else if((address >= Bzero_Sector106_start) &&
            (address < Bzero_Sector107_start) && (erasedAlready[106] == 0))
    {
        erasedAlready[106] = 1;
        return (uint32_t)Bzero_Sector106_start;
    }
    else if((address >= Bzero_Sector107_start) &&
            (address < Bzero_Sector108_start) && (erasedAlready[107] == 0))
    {
        erasedAlready[107] = 1;
        return (uint32_t)Bzero_Sector107_start;
    }
    else if((address >= Bzero_Sector108_start) &&
            (address < Bzero_Sector109_start) && (erasedAlready[108] == 0))
    {
        erasedAlready[108] = 1;
        return (uint32_t)Bzero_Sector108_start;
    }
    else if((address >= Bzero_Sector109_start) &&
            (address < Bzero_Sector110_start) && (erasedAlready[109] == 0))
    {
        erasedAlready[109] = 1;
        return (uint32_t)Bzero_Sector109_start;
    }
    else if((address >= Bzero_Sector110_start) &&
            (address < Bzero_Sector111_start) && (erasedAlready[110] == 0))
    {
        erasedAlready[110] = 1;
        return (uint32_t)Bzero_Sector110_start;
    }
    else if((address >= Bzero_Sector111_start) &&
            (address < Bzero_Sector112_start) && (erasedAlready[111] == 0))
    {
        erasedAlready[111] = 1;
        return (uint32_t)Bzero_Sector111_start;
    }
    else if((address >= Bzero_Sector112_start) &&
            (address < Bzero_Sector113_start) && (erasedAlready[112] == 0))
    {
        erasedAlready[112] = 1;
        return (uint32_t)Bzero_Sector112_start;
    }
    else if((address >= Bzero_Sector113_start) &&
            (address < Bzero_Sector114_start) && (erasedAlready[113] == 0))
    {
        erasedAlready[113] = 1;
        return (uint32_t)Bzero_Sector113_start;
    }
    else if((address >= Bzero_Sector114_start) &&
            (address < Bzero_Sector115_start) && (erasedAlready[114] == 0))
    {
        erasedAlready[114] = 1;
        return (uint32_t)Bzero_Sector114_start;
    }
    else if((address >= Bzero_Sector115_start) &&
            (address < Bzero_Sector116_start) && (erasedAlready[115] == 0))
    {
        erasedAlready[115] = 1;
        return (uint32_t)Bzero_Sector115_start;
    }
    else if((address >= Bzero_Sector116_start) &&
            (address < Bzero_Sector117_start) && (erasedAlready[116] == 0))
    {
        erasedAlready[116] = 1;
        return (uint32_t)Bzero_Sector116_start;
    }
    else if((address >= Bzero_Sector117_start) &&
            (address < Bzero_Sector118_start) && (erasedAlready[117] == 0))
    {
        erasedAlready[117] = 1;
        return (uint32_t)Bzero_Sector117_start;
    }
    else if((address >= Bzero_Sector118_start) &&
            (address < Bzero_Sector119_start) && (erasedAlready[118] == 0))
    {
        erasedAlready[118] = 1;
        return (uint32_t)Bzero_Sector118_start;
    }
    else if((address >= Bzero_Sector119_start) &&
            (address < Bzero_Sector120_start) && (erasedAlready[119] == 0))
    {
       erasedAlready[119] = 1;
       return (uint32_t)Bzero_Sector119_start;
    }
    else if((address >= Bzero_Sector120_start) &&
            (address <= Bzero_Sector121_start) && (erasedAlready[120] == 0))
    {
       erasedAlready[120] = 1;
       return (uint32_t)Bzero_Sector120_start;
    }
    else if((address >= Bzero_Sector121_start) &&
            (address < Bzero_Sector122_start) && (erasedAlready[121] == 0))
    {
        erasedAlready[121] = 1;
        return (uint32_t)Bzero_Sector121_start;
    }
    else if((address >= Bzero_Sector122_start) &&
            (address < Bzero_Sector123_start) && (erasedAlready[122] == 0))
    {
        erasedAlready[122] = 1;
        return (uint32_t)Bzero_Sector122_start;
    }
    else if((address >= Bzero_Sector123_start) &&
            (address < Bzero_Sector124_start) && (erasedAlready[123] == 0))
    {
        erasedAlready[123] = 1;
        return (uint32_t)Bzero_Sector123_start;
    }
    else if((address >= Bzero_Sector124_start) &&
            (address < Bzero_Sector125_start) && (erasedAlready[124] == 0))
    {
        erasedAlready[124] = 1;
        return (uint32_t)Bzero_Sector124_start;
    }
    else if((address >= Bzero_Sector125_start) &&
            (address < Bzero_Sector126_start) && (erasedAlready[125] == 0))
    {
        erasedAlready[125] = 1;
        return (uint32_t)Bzero_Sector125_start;
    }
    else if((address >= Bzero_Sector126_start) &&
            (address < Bzero_Sector127_start) && (erasedAlready[126] == 0))
    {
        erasedAlready[126] = 1;
        return (uint32_t)Bzero_Sector126_start;
    }
    else if((address >= Bzero_Sector127_start) &&
            (address < FlashBank0EndAddress) && (erasedAlready[127] == 0))
    {
        erasedAlready[127] = 1;
        return (uint32_t)Bzero_Sector127_start;
    }
    else
    {
        return 0xdeadbeef; // a proxy address to signify that it is not
                           // a flash sector.
    }
}

//
// uint32_t findSize(uint32_t address) - This routine finds the size of the sector under use.
//
uint16_t findSize(uint32_t address)
{
    //
    // set erasedAlready, all sectors are 8K in 32bits in size.
    //
    return Sector2KB_u32length;

}

//
// uint32_t getLongData(void) - This routine fetches a 32-bit value from the peripheral
//                              input stream.
//
uint32_t getLongData()
{
    uint32_t longData;

    //
    // Fetch the upper 1/2 of the 32-bit value
    //
    longData = ((uint32_t) (*getWordData)() << 16);

    //
    // Fetch the lower 1/2 of the 32-bit value
    //
    longData |= (uint32_t) (*getWordData)();

    return longData;
}

//
//
// void readReservedFn(void) - This function reads 8 reserved words in the header.
//                             None of these reserved words are used by the
//                             this boot loader at this time, they may be used in
//                             future devices for enhancements.  Loaders that use
//                             these words use their own read function.
//
void readReservedFn()
{
    uint16_t i;

    //
    // Read and discard the 8 reserved words.
    //
    for (i = 1; i <= 8; i++)
    {
        getWordData();
    }
    return;
}

//
// void setFlashAPIError(Fapi_StatusType status) - sets Flash API error from 
//                                                 operation into struct to 
//                                                 display on console
//
void setFlashAPIError(Fapi_StatusType status)
{
    if(status == Fapi_Error_AsyncIncorrectDataBufferLength)
    {
        statusCode.flashAPIError = INCORRECT_DATA_BUFFER_LENGTH;
    }
    else if(status == Fapi_Error_AsyncIncorrectEccBufferLength)
    {
        statusCode.flashAPIError = INCORRECT_ECC_BUFFER_LENGTH;
    }
    else if(status == Fapi_Error_AsyncDataEccBufferLengthMismatch)
    {
        statusCode.flashAPIError = DATA_ECC_BUFFER_LENGTH_MISMATCH;
    }
    else if(status == Fapi_Error_FlashRegsNotWritable)
    {
        statusCode.flashAPIError = FLASH_REGS_NOT_WRITABLE;
    }
    else if(status == Fapi_Error_FeatureNotAvailable)
    {
        statusCode.flashAPIError = FEATURE_NOT_AVAILABLE;
    }
    else if(status == Fapi_Error_InvalidAddress)
    {
        statusCode.flashAPIError = INVALID_ADDRESS;
    }
    else if(status == Fapi_Error_Fail)
    {
        statusCode.flashAPIError = FAILURE;
    }
    else
    {
        statusCode.status = NOT_RECOGNIZED;
    }
}
