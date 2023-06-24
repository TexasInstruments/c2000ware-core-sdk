//###########################################################################
//
// FILE:    flash_kernel_ex3_ldfu.c
//
// TITLE:   Live DFU Command Functionality
//! \addtogroup driver_example_list
//! <h1>  Live DFU Command Functionality </h1>
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
#include "flash_kernel_ex3_ldfu.h"

//
// Globals
//

//
// BUFF: Data Buffer used for programming 'KEY', 'REV', and 'START' values
//
uint16   BUFF[WORDS_IN_FLASH_BUFFER + 1];
uint32   *Buffer32 = (uint32 *)BUFF;

//
// getWordData is a pointer to the function that interfaces to the peripheral.
// Each loader assigns this pointer to it's particular getWordData function.
//
uint16fptr getWordData;

//
// checksum contains a running total of each byte that is received through SCI
//
extern uint16_t checksum;


//
// Typedefs
//

//
// statusCode.staus is used to record an error
// statusCode.address is used to record the address of the error
//
typedef struct
{
   uint16_t status;
   uint32_t address;
}  StatusCode;
extern StatusCode statusCode;

#ifdef __cplusplus
#pragma CODE_SECTION("LDFU_BANK0");
#else
#pragma CODE_SECTION(liveDFU, "LDFU_BANK0");
#endif


//
// liveDFU -  liveDFU is the main function of the Live DFU command. The
//            function initializes statusCode.status, statusCode.address,
//            and the checksum. The function branches to the LDFU_Load function
//            in order to erase the appropriate bank, load a hex formatted program (in the appropriate
//            SCI boot format) into flash, and verify the program. The watchdog is configured
//            for a reset. At the end, the watchdog is enabled in order for
//            a reset to occur.
//
void liveDFU(void)
{
    //
    // EntryAddr is used to branch to the ldfuLoad function
    //
    volatile uint32_t EntryAddr;

    //
    // Initialize the status code address and status to default values
    // NO_ERROR for statusCode.status indicates that an error has not occurred
    // 0x12345678 for statusCode.address is a default value that specifies no
    // real address
    //
    statusCode.status = NO_ERROR;
    statusCode.address = 0x12345678;

    //
    // Initialize the checksum to 0 in order to prevent false checksum errors.
    // checksum keeps a running total of each byte that is received from a host
    //
    checksum = 0;

    //
    // Branch to the ldfuLoad function in order to erase the appropriate bank, read in
    // the program, program it to flash, and verify it.
    //
    EntryAddr = ldfuLoad();


}

//
// fmstatFail -  fmstatFail is the function that is executed when an error
//               occurs in the Flash State Machine (FSM). By default, it
//               halts execution, so that the error can be observed.
//
void fmstatFail(void)
{
    //
    //  Error code will be in the status parameter
    //
    __asm("    ESTOP0");
}

//
// ldfuLoad - Reads in an SCI boot hex formatted file until information related to
//            each block of data remains. Calls on ldfuCopyData in order to
//            erase flash, receive the remaining data via SCI, program the data
//            to flash, and verify the data in flash; also returns the starting address
//            specified by the file
//
uint32_t ldfuLoad(void)
{
    //
    // EntryAddr is used to store the starting address specified by the file
    // being read and loaded to flash
    //
    uint32_t EntryAddr;

    //
    // Assign getWordData to the SCI-A version of the
    // function. getWordData is a pointer to a function.
    //
    getWordData = sciaGetWordData;

    //
    // If the KeyValue was invalid, return the flash entry point.
    //
    if (sciaGetWordData() != 0x08AA)
    {
        statusCode.status = VERIFY_ERROR;
        statusCode.address = FLASH_ENTRY_POINT;
    }

    //
    // Reads and discards 8 reserved words
    //
    readReservedFn();

    //
    // The next 32 bits specify the starting address. Read the starting address
    // and store it in EntryAddr
    //
    EntryAddr = getLongData();

    //
    // Load the rest of the SCI boot hex formatted file into flash
    //
    ldfuCopyData();

    //
    // Wait
    //
    uint16_t x = 0;
    for(x = 0; x < 32676; x++){}
    for(x = 0; x < 32676; x++){}

    //
    // Return EntryAddr
    //
    return EntryAddr;
}

//
// ldfuCopyData -  Erases and programs the appropriate flash bank. 
//                 The steps taken are listed below:
//
//                 1. Reads 'REV' value of the banks
//                 2. Erases Sectors 2-15 of the bank with the higher revision
//                 3. Writes 'START' value to B0/1/2_START_ADD
//                 4. Programs the bank with the higher revision and verifies
//                    the data
//                 5. Decrements the bank's revision value
//                 6. Writes 'KEY' value to B0/1/2_KEY_ADD and 'REV' value to
//                    B0/1/2_REV_ADD
//                
//
void ldfuCopyData(void)
{
    //
    // BlockSize is used to store the size of the block of data to be read in
    // DestAddr is used to store the address of where the block of data is
    // to be written to in flash
    //
    struct HEADER
    {
        uint16_t BlockSize;
        uint32_t DestAddr;
    } BlockHeader;

    //
    // Buffer: Used to program data to flash
    //
    uint16_t Buffer[BUFFER_SIZE];

    //
    // miniBuffer: Useful for 4-word access to flash
    //
    uint16_t miniBuffer[4];

    //
    // i, j, k, and n are used to iterate through each block of data
    //
    uint16_t i = 0;
    uint16_t j = 0;
    uint16_t k = 0;
    uint16_t n = 0;

    //
    // sectorAddress: Used to store the address of a sector
    //
    uint32_t sectorAddress;

    //
    // sectorSize: Used to store the size of a sector
    //
    uint16_t sectorSize;

    //
    // wordData: Stores a word of data
    //
    uint16_t wordData;

    //
    // oReturnCheck: Used to store the status of the Flash API after operations
    // are performed
    //
    Fapi_StatusType oReturnCheck;

    //
    // oFlashStatusWord: used during a blank check and other Flash API operations
    //
    Fapi_FlashStatusWordType oFlashStatusWord;

    //
    // oFlashStatus: Used to read the FMSTAT register when checking the Flash
    //               State Machine for errors
    //
    Fapi_FlashStatusType oFlashStatus;

    //
    // u32Index: Used to specify an address to the Flash API programming operation
    //
    uint32_t u32Index = 0;

    //
    // fail: Keeps a running total of the number of fails in this function;
    //       used to record an error if it is the first error to occur
    //
    int fail = 0;

    //
    // beginAddress: Used to specify the index of the address in the
    //               secAddress array at which erasing needs to start
    //
    uint16_t beginAddress;

    //
    // endAddress: Used to specify the index of the address in the
    //             secAddress array at which erasing needs to end
    //
    uint16_t endAddress;

    //
    // startAdd: Used to store the addres at which the 'START' value will be written
    //
    uint32_t startAdd;
    
    //
    // BzeroRev: Contains the value of bank 0's revision
    //
    uint32_t BzeroRev = HWREG((uint32_t)B0_REV_ADD);

    //
    // Ensure BUFFER_SIZE is a valid value
    //
    assert(BUFFER_SIZE % 4 == 0);

    //
    // Check if an error has occurred before the start of this function; increment
    // 'fail' accordingly
    //
    if (statusCode.status != NO_ERROR)
    {
        fail++;
    }

    //
    // Fill 'BUFF' with the 'START' value in order to program it to flash
    //
     for(i=0; i <= WORDS_IN_FLASH_BUFFER; i++)
     {
         BUFF[i] = (uint16)START;
     }


    //
    // Enable writing to the EALLOW protected registers
    //
    EALLOW;

    //
    // The for loop iterates through the secAddress array and erases the
    // sector that corresponds to each specified index.
    //
    for(n = beginAddress; n <= endAddress; n++ )
    {
        //
        // Get the current address
        //
        sectorAddress = secAddress[n];

        //
        // FindSize just returns 0x4000. 
        //
        sectorSize = findSize(sectorAddress);

        //
        // Execute an erase operation using the Flash API
        //
        oReturnCheck = Fapi_issueAsyncCommandWithAddress(
                Fapi_EraseSector, (uint32_t *) sectorAddress);

        //
        // Wait until the Flash State Machine is ready
        //
        while (Fapi_checkFsmForReady() != Fapi_Status_FsmReady){}

        //
        // Perform a blank check on the recently erased sector to ensure it was erased
        //
        oReturnCheck = Fapi_doBlankCheck(
                (uint32_t *) sectorAddress, sectorSize,
                &oFlashStatusWord);

        //
        // Check the Flash API status for an error
        //
        if (oReturnCheck != Fapi_Status_Success)
        {
            //
            // If an error occurred and it was the first error, then record it
            //
            if (fail == 0)
            {
                //
                // Record the error as a blank error
                //
                statusCode.status = BLANK_ERROR;

                //
                // Record the address of the error
                //
                statusCode.address =
                        oFlashStatusWord.au32StatusWord[0];
            }

            //
            // Increment fail
            //
            fail++;
        }

        //
        // Wait for the Flash State Machine
        //
        while (Fapi_checkFsmForReady() == Fapi_Status_FsmBusy)
        {
        }

    }

    //
    // Write the 'START' value to the appropriate address
    //
    for(i=0, u32Index = startAdd;
        (u32Index < (startAdd + WORDS_IN_FLASH_BUFFER)) &&
        (oReturnCheck == Fapi_Status_Success); i+= 4, u32Index+= 4)
    {
        //
        // Execute a programming command; put the contents of 'BUFF'
        // in the specified address
        //
        oReturnCheck = Fapi_issueProgrammingCommand((uint32 *)u32Index,
                                                     BUFF+i, 4, 0, 0,
                                                     Fapi_AutoEccGeneration);
        //
        // Wait until the Flash program operation is over
        //
        while(Fapi_checkFsmForReady() == Fapi_Status_FsmBusy);

        //
        // Check for an error
        //
        if(oReturnCheck != Fapi_Status_Success)
        {
            //
            // Check Flash API documentation for possible errors
            //
            exampleError(oReturnCheck);
        }

        //
        // Read FMSTAT register contents to know the status of FSM after
        // program command to see if there are any program operation related errors
        //
        oFlashStatus = Fapi_getFsmStatus();

        //
        // Check for a failure
        //
        if(oFlashStatus != 0)
        {
            //
            //Check FMSTAT and debug accordingly
            //
            fmstatFail();
        }

    }

    //
    // Disable writing to the EALLOW protected registers
    //
    EDIS;

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
    // Enable writing to the EALLOW protected registers
    //
    EALLOW;

    //
    // While the block size is > 0 copy the data
    // to the DestAddr. It is assumed the DestAddr is a valid
    // memory location; however, a value less than the
    // reserved memory boundary for the bank will halt operation
    //
    while (BlockHeader.BlockSize != (uint16_t) 0x0000)
    {
        //
        // Get the destination address of the block of data
        //
        BlockHeader.DestAddr = getLongData();

        //
        // Iterate through the block of data in order to program the data
        // in flash and verify it
        //
        for (i = 0; i < BlockHeader.BlockSize; i += 0)
        {
            //
            // If the size of the block of data is less than the size of the buffer,
            // then fill the buffer with the block of data and pad the remaining
            // elements
            //
            if (BlockHeader.BlockSize < BUFFER_SIZE)
            {
                //
                // Receive the block of data one word at a time and place it in
                // the buffer
                //
                for (j = 0; j < BlockHeader.BlockSize; j++)
                {
                    //
                    // Receive one word of data
                    //
                    wordData = (*getWordData)();

                    //
                    // Put the word of data in the buffer
                    //
                    Buffer[j] = wordData;

                    //
                    // Increment i to keep track of how many words have been received
                    //
                    i++;
                }

                //
                // Pad the remaining elements of the buffer
                //
                for (j = BlockHeader.BlockSize; j < BUFFER_SIZE; j++)
                {
                    //
                    // Put 0xFFFF into the current element of the buffer. OxFFFF is equal to erased
                    // data and has no effect
                    //
                    Buffer[j] = 0xFFFF;
                }
            }

            //
            // BlockHeader.BlockSize >= BUFFER_SIZE
            //
            else
            {
                //
                // Less than one BUFFER_SIZE left
                //
                if ((BlockHeader.BlockSize - i) < BUFFER_SIZE)
                {
                    //
                    // Fill Buffer with rest of data
                    //
                    for (j = 0; j < BlockHeader.BlockSize - i; j++)
                    {
                        //
                        // Receive one word of data
                        //
                        wordData = (*getWordData)();

                        //
                        // Put the word of data into the current element of Buffer
                        //
                        Buffer[j] = wordData;
                    }

                    //
                    // Increment i outside here so it doesn't affect loop above
                    //
                    i += j;

                    //
                    // Fill the rest with 0xFFFF
                    //
                    for (; j < BUFFER_SIZE; j++)
                    {
                        Buffer[j] = 0xFFFF;
                    }
                }
                else
                {
                    //
                    // Fill up like normal, up to BUFFER_SIZE
                    //
                    for (j = 0; j < BUFFER_SIZE; j++)
                    {
                        wordData = (*getWordData)();
                        Buffer[j] = wordData;
                        i++;
                    }
                }
            }

            //
            // Fill miniBuffer with the data in Buffer in order to program the data
            // to flash; miniBuffer takes data from Buffer, 4 words at a time.
            //
            for (k = 0; k < (BUFFER_SIZE / 4); k++)
            {
                //
                // Get 4 words from Buffer
                //
                miniBuffer[0] = Buffer[k * 4 + 0];
                miniBuffer[1] = Buffer[k * 4 + 1];
                miniBuffer[2] = Buffer[k * 4 + 2];
                miniBuffer[3] = Buffer[k * 4 + 3];

                //
                // Check that miniBuffer is not already all erased data
                //
                if (!((miniBuffer[0] == 0xFFFF) && (miniBuffer[1] == 0xFFFF)
                        && (miniBuffer[2] == 0xFFFF)
                        && (miniBuffer[3] == 0xFFFF)))
                {
                    //
                    // Program 4 words at once, 64-bits
                    //
                    oReturnCheck = Fapi_issueProgrammingCommand(
                            (uint32_t *) BlockHeader.DestAddr, miniBuffer,
                            sizeof(miniBuffer), 0, 0, Fapi_AutoEccGeneration);
                    //
                    // Wait for the programming operation to finish
                    //
                    while (Fapi_checkFsmForReady() == Fapi_Status_FsmBusy){};

                    //
                    // Check for an error
                    //
                    if (oReturnCheck != Fapi_Status_Success)
                    {
                        //
                        // First fail; store the error type and address of the error
                        //
                        if (fail == 0)
                        {
                            //
                            // Record the error type as PROGRAM_ERROR
                            //
                            statusCode.status = PROGRAM_ERROR;

                            //
                            // Get the address of the error
                            //
                            statusCode.address =
                                    oFlashStatusWord.au32StatusWord[0];
                        }

                        //
                        // Increment fail
                        //
                        fail++;
                    }

                    //
                    // oFlashStatus = Fapi_getFsmStatus();
                    // Verify the data that was programmed by using the Flash API
                    //
                    for (j = 0; j < 4; j += 2)
                    {
                        uint32_t toVerify = miniBuffer[j + 1];
                        toVerify = toVerify << 16;
                        toVerify |= miniBuffer[j];

                        //
                        // Perform a verify operation with the Flash API
                        //
                        oReturnCheck = Fapi_doVerify(
                                (uint32_t *) (BlockHeader.DestAddr + j), 1,
                                (uint32_t *) (&toVerify), &oFlashStatusWord);

                        //
                        // Check for an error with the verify operation
                        //
                        if (oReturnCheck != Fapi_Status_Success)
                        {
                            //
                            // If first error, store the error type and the address of the error
                            //
                            if (fail == 0)
                            {
                                //
                                // Record the error type as VERIFY_ERROR
                                //
                                statusCode.status = VERIFY_ERROR;

                                //
                                // Get the address of the error
                                //
                                statusCode.address =
                                        oFlashStatusWord.au32StatusWord[0];
                            }

                            //
                            // Increment fail
                            //
                            fail++;
                        }
                    //
                    // for j; for Fapi_doVerify
                    //
                    }
                //
                // check if miniBuffer does not contain all already erased data
                //
                }
                BlockHeader.DestAddr += 0x4;
            //
            // for(int k); loads miniBuffer with Buffer elements
            //
            }

            //
            // Send a checksum to the host to ensure data has been received correctly
            //
            #if checksum_enable
                sciSendChecksum();
            #endif
        }

        //
        // Get the size of the next block of data
        //
        BlockHeader.BlockSize = (*getWordData)();
    }

    //
    // Disable writing to the EALLOW protected registers
    //
    EDIS;


    //
    // Store lower half of 'KEY' value in 'BUFF'
    //
    BUFF[0] = (uint16)KEY;

    //
    // Store upper half of 'KEY' value in 'BUFF'
    //
    BUFF[1] = (uint16)(KEY >> 16);

    //
    // Execute a programming command in order to =write the 'KEY' and
    // revision values to flash for the appropriate bank
    //
    oReturnCheck = Fapi_issueProgrammingCommand((uint32 *)u32Index, BUFF, 4,
                                                0, 0, Fapi_AutoEccGeneration);
    //
    // Wait until the Flash API program operation is over
    //
    while(Fapi_checkFsmForReady() == Fapi_Status_FsmBusy){};

    return;
}

//
// findSize - Returns the size of a sector
//
uint16_t findSize(uint32_t address)
{
    //
    // All sectors are 8K 
    //
    return  Sector8KB_u32length;
}

//
// readReservedFn -  This function reads 8 reserved words.
//                   Used to read the 8 reserved words in the header of an
//                   sci8, boot, ascii formatted file. Nothing is done with
//                   the words, but they are part of the format.
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
// getLongData- Fetches a 32-bit value from the peripheral
//              input stream.
//
uint32_t getLongData(void)
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
// revInit - Initializes the revision values of each bank; data in the
//            key value location is erased.
//
void revInit(void)
{
    //
    // oReturnCheck is used to store the status of the Flash API.
    //
    volatile Fapi_StatusType oReturnCheck;

    //
    // Fill each index of the buffer with 0xFFFF
    //
    BUFF[0] = (uint16)0xFFFF;
    BUFF[1] = (uint16)0xFFFF;
    BUFF[2] = (uint16)0xFFFF;
    BUFF[3] = (uint16)0xFFFF;

    //
    // Initialize the revision value of bank 0 to 0xFFFFFFFF, erase the data in
    // bank 0's key value location
    //
    oReturnCheck = Fapi_issueProgrammingCommand((uint32 *)B0_KEY_ADD, BUFF, 4,
                                                0, 0, Fapi_AutoEccGeneration);
    //
    // Wait until the Flash program operation is over
    //
    while(Fapi_checkFsmForReady() == Fapi_Status_FsmBusy){};


    return;
}

//
// Bank Selection Logic
//

//
// Bank selection logic is not included in the BANK1 configuration
//
#ifdef BANK0

//
// bankSelect -  Located at the beginning of bank 0 (0x80000),
//               Bank_Select branches to the most recently programmed
//               bank after execution of the Live DFU command.
//               If a bank has not been programmed using the Live
//               DFU command, it branches to the kernel setup so that
//               the command can be used to program bank 1.
//
#ifdef __cplusplus
#pragma CODE_SECTION("codestart");
#else
#pragma CODE_SECTION(bankSelect, "codestart");
#endif
void bankSelect(void)
{
    //
    // EntryAddr is used to branch to the kernel setup
    //
    volatile uint32_t EntryAddr;

    //
    // Read the revision value of bank 0
    //
    uint32_t REV_BANK0 = HWREG((uint32_t)B0_REV_ADD);


    //
    // Initialize the Flash API
    //
    initFlashSectors();

    //
    // If each bank doesn't contain a 'KEY' value, then a bank
    // has not been programmed using the Live DFU command
    //
    {        
        //
        // initialize device, driverlib.
        //
        Device_init();        

        //
        // init interrupt and vectorTable, driverlib.
        //
        Interrupt_initModule();
        Interrupt_initVectorTable();

        //
        // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
        //
        EINT;
        ERTM;
		
		//
		// Initialize the Flash API
		//
		initFlashSectors();

        //
        // Initialize the revision values of each bank and erase data in the
        // key address location.
        //
        revInit();

        //
        // Branch to sciGetFunction so the Live DFU command can be used to
        //
        EntryAddr = sciGetFunction(0x01);
    }

    //
    // Else, branch to the codestart of bank 0
    //
    else
    {
        //
        // Branch to 8EFF0;  the codestart of bank 0 is
        // located at 8EFF0, which is a flash alt. entry point
        //
        asm("    LB 0x8EFF0");
    }
}

#endif

//
// End of file
//
