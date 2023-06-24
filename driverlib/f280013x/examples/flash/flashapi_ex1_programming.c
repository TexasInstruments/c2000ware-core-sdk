//#############################################################################
//
// FILE:   flashapi_ex1_programming.c
//
// TITLE:  Flash programming example
//
//! \addtogroup driver_example_list
//! <h1> Flash Programming with AutoECC, DataAndECC, DataOnly and EccOnly </h1>
//!
//! This example demonstrates how to program Flash using API's following options
//! 1. AutoEcc generation
//! 2. DataOnly and EccOnly
//! 3. DataAndECC
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - None.
//!
//
//#############################################################################
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
//#############################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"

//
// Include Flash API include file
//
#include "FlashTech_F280013x_C28x.h"

// Include Flash API example header file
//
#include "flash_programming_f280013x.h"

//
// Defines
//

//
// Length (in 16-bit words) of data buffer used for program
//
#define  WORDS_IN_FLASH_BUFFER    0x400

//
// Globals
//

//
// Data Buffers used for program operation using the flash API program function
//
#pragma  DATA_SECTION(Buffer,"DataBufferSection");
uint16   Buffer[WORDS_IN_FLASH_BUFFER];
uint32   *Buffer32 = (uint32 *)Buffer;


//
// Prototype of the functions used in this example
//
void Example_Error(Fapi_StatusType status);
void Example_Done(void);
void Example_CallFlashAPI(void);
void FMSTAT_Fail(void);
void ECC_Fail(void);
void Example_EraseSector(void);

void Example_EraseBanks(void);
void Example_ProgramUsingAutoECC(void);
void Example_ProgramBankUsingAutoECC(void);
void Example_ProgramUsingDataOnlyECCOnly(void);
void Example_ProgramUsingDataAndECC(void);
void ClearFSMStatus(void);

//
// Main
//
void main(void)
{
    //
    // Initialize device clock and peripherals
    // Copy the Flash initialization code from Flash to RAM
    // Copy the Flash API from Flash to RAM
    // Configure Flash wait-states, fall back power mode, performance features
    // and ECC
    //
    Device_init();

    //
    // Initialize GPIO
    //
    Device_initGPIO();

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // At 120MHz, execution wait-states for external oscillator is 2. Modify the
    // wait-states when the system clock frequency is changed.
    //
    Flash_initModule(FLASH0CTRL_BASE, FLASH0ECC_BASE, 2);

    //
    // Flash API functions should not be executed from the same bank on which
    // erase/program operations are in progress.
    // Also, note that there should not be any access to the Flash bank on
    // which erase/program operations are in progress.  Hence below function
    // is mapped to RAM for execution.
    //
    Example_CallFlashAPI();


    //
    // Example is done here
    //
    Example_Done();
}

//*****************************************************************************
//  ClearFSMStatus
//
//  This function clears the status (STATCMD, similar to FMSTAT of the previous 
//  devices) of the previous flash operation.
//  This function and the flash API functions used in this function are 
//  executed from RAM in this example.
//  Note: this function is applicable for only F280013X and F280015X devices
//*****************************************************************************
#ifdef __cplusplus
#pragma CODE_SECTION(".TI.ramfunc");
#else
#pragma CODE_SECTION(ClearFSMStatus, ".TI.ramfunc");
#endif
void ClearFSMStatus(void){
    Fapi_FlashStatusType  oFlashStatus;
    Fapi_StatusType  oReturnCheck;

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
                //
                // Check Flash API documentation for possible errors
                //
                Example_Error(oReturnCheck);
            }
        }
}

//*****************************************************************************
//  Example_CallFlashAPI
//
//  This function will interface to the flash API.
//  Flash API functions used in this function are executed from RAM in this
//  example.
//*****************************************************************************
#ifdef __cplusplus
#pragma CODE_SECTION(".TI.ramfunc");
#else
#pragma CODE_SECTION(Example_CallFlashAPI, ".TI.ramfunc");
#endif
void Example_CallFlashAPI(void)
{
    uint16 i = 0;
    Fapi_StatusType  oReturnCheck;

    //
    // Initialize the Flash API by providing the Flash register base address
    // and operating frequency(in MHz).
    // This function is required to initialize the Flash API based on System
    // frequency before any other Flash API operation can be performed.
    // This function must also be called whenever System frequency or RWAIT is
    // changed.
    //
    oReturnCheck = Fapi_initializeAPI(FlashTech_CPU0_BASE_ADDRESS, 
                                      DEVICE_SYSCLK_FREQ/1000000U);

    if(oReturnCheck != Fapi_Status_Success)
    {
        //
        // Check Flash API documentation for possible errors
        //
        Example_Error(oReturnCheck);
    }

    //
    // Initialize the Flash banks and FMC for erase and program operations.
    // Fapi_setActiveFlashBank() function sets the Flash banks and FMC for
    // further Flash operations to be performed on the banks.
    //
    oReturnCheck = Fapi_setActiveFlashBank(Fapi_FlashBank0);

    if(oReturnCheck != Fapi_Status_Success)
    {
        //
        // Check Flash API documentation for possible errors
        //
        Example_Error(oReturnCheck);
    }

    //
    // Erase bank before programming
    //
    Example_EraseBanks();
    //
    // Fill a buffer with data to program into the flash.
    //
    for(i=0; i < WORDS_IN_FLASH_BUFFER; i++)
    {
        Buffer[i] = i;
    }

    //
    // Program the sector using AutoECC option
    //
    Example_ProgramUsingAutoECC();

    //
    // Erase bank before programming
    //
    Example_EraseBanks();

    //
    // Program the sector using DataOnly and ECCOnly options
    //
    Example_ProgramUsingDataOnlyECCOnly();

    //
    // Erase the sector before programming
    //
    Example_EraseSector();

    //
    // Program Bank using AutoECC option
    //
    // Note that executing entire bank needs a special flash API library -
	// for this 
	Example_ProgramBankUsingAutoECC();
	// 

    //
    // Erase bank before programming
    //
    Example_EraseBanks();

    //
    // Program the sector using DataAndECC option
    //
    Example_ProgramUsingDataAndECC();

    //
    // Erase the sector for cleaner exit from the example.
    //
    Example_EraseSector();

}

//*****************************************************************************
//  Example_ProgramUsingAutoECC
//
//  Example function to Program data in Flash using "AutoEccGeneration" option.
//  Flash API functions used in this function are executed from RAM in this
//  example.
//*****************************************************************************
#ifdef __cplusplus
#pragma CODE_SECTION(".TI.ramfunc");
#else
#pragma CODE_SECTION(Example_ProgramUsingAutoECC, ".TI.ramfunc");
#endif
void Example_ProgramUsingAutoECC(void)
{
    uint32 u32Index = 0;
    uint16 i = 0;
    Fapi_StatusType  oReturnCheck;
    Fapi_FlashStatusType  oFlashStatus;
    Fapi_FlashStatusWordType  oFlashStatusWord;

    //
    // A data buffer of max 8 16-bit words can be supplied to the program
    // function.
    // Each word is programmed until the whole buffer is programmed or a
    // problem is found. However to program a buffer that has more than 8
    // words, program function can be called in a loop to program 8 words for
    // each loop iteration until the whole buffer is programmed.
    //
    // Remember that the main array flash programming must be aligned to
    // 64-bit address boundaries and each 64 bit word may only be programmed
    // once per write/erase cycle.  Meaning the length of the data buffer
    // (3rd parameter for Fapi_issueProgrammingCommand() function) passed
    // to the program function can only be either 4 or 8.
    //
    // Program data in Flash using "AutoEccGeneration" option.
    // When AutoEccGeneration option is used, Flash API calculates ECC for the
    // given 64-bit data and programs it along with the 64-bit main array data.
    // Note that any unprovided data with in a 64-bit data slice
    // will be assumed as 1s for calculating ECC and will be programmed.
    //
    // Note that data buffer (Buffer) is aligned on 64-bit boundary for verify
    // reasons.
    //
    // Monitor ECC address for the sector below while programming with 
    // AutoEcc mode.
    //
    // In this example, the number of bytes specified in the flash buffer
    // are programmed in the flash sector below along with auto-generated
    // ECC.
    //

    for(i=0, u32Index = Bzero_Sector0_start;
       (u32Index < (Bzero_Sector0_start + WORDS_IN_FLASH_BUFFER));
       i+= 8, u32Index+= 8)
    {
        ClearFSMStatus();

        // Enable program/erase protection for select sectors where this example is 
        // located
        // CMDWEPROTA is applicable for sectors 0-31
        // Bits 0-11 of CMDWEPROTB is applicable for sectors 32-127, each bit represents
        // a group of 8 sectors, e.g bit 0 represents sectors 32-39, bit 1 represents
        // sectors 40-47, etc
        Fapi_setupBankSectorEnable(FLASH_WRAPPER_PROGRAM_BASE+FLASH_O_CMDWEPROTA, 0x13FFFF00);
        Fapi_setupBankSectorEnable(FLASH_WRAPPER_PROGRAM_BASE+FLASH_O_CMDWEPROTB, 0x00000080);


        oReturnCheck = Fapi_issueProgrammingCommand((uint32 *)u32Index,Buffer+i,
                                               8, 0, 0, Fapi_AutoEccGeneration);

        //
        // Wait until the Flash program operation is over
        //
        while(Fapi_checkFsmForReady() == Fapi_Status_FsmBusy);

        if(oReturnCheck != Fapi_Status_Success)
        {
            //
            // Check Flash API documentation for possible errors
            //
            Example_Error(oReturnCheck);
        }

        //
        // Read FMSTAT register contents to know the status of FSM after
        // program command to see if there are any program operation related
        // errors
        //
        oFlashStatus = Fapi_getFsmStatus();
        if(oFlashStatus != 3)
        {
            //
            //Check FMSTAT and debug accordingly
            //
            FMSTAT_Fail();
        }

        //
        // Verify the programmed values.  Check for any ECC errors.
        //
        oReturnCheck = Fapi_doVerify((uint32 *)u32Index,
                                     4, (uint32 *)(uint32)(Buffer + i),
                                     &oFlashStatusWord);

        if(oReturnCheck != Fapi_Status_Success)
        {
            //
            // Check Flash API documentation for possible errors
            //
            Example_Error(oReturnCheck);
        }
    }
}

//*****************************************************************************
//  Example_ProgramBankUsingAutoECC
//
//  Example function to Program data in Flash using "AutoEccGeneration" option.
//  Flash API functions used in this function are executed from RAM in this
//  example.
//*****************************************************************************
#ifdef __cplusplus
#pragma CODE_SECTION(".TI.ramfunc");
#else
#pragma CODE_SECTION(Example_ProgramBankUsingAutoECC, ".TI.ramfunc");
#endif
void Example_ProgramBankUsingAutoECC(void)
{
    uint32 u32Index = 0;
    uint32 sector = 0;
    uint16 i = 0;
    Fapi_StatusType  oReturnCheck;
    Fapi_FlashStatusType  oFlashStatus;
    Fapi_FlashStatusWordType  oFlashStatusWord;

    //
    // A data buffer of max 8 16-bit words can be supplied to the program
    // function.
    // Each word is programmed until the whole buffer is programmed or a
    // problem is found. However to program a buffer that has more than 8
    // words, program function can be called in a loop to program 8 words for
    // each loop iteration until the whole buffer is programmed.
    //
    // Remember that the main array flash programming must be aligned to
    // 64-bit address boundaries and each 64 bit word may only be programmed
    // once per write/erase cycle.  Meaning the length of the data buffer
    // (3rd parameter for Fapi_issueProgrammingCommand() function) passed
    // to the program function can only be either 4 or 8.
    //
    // Program data in Flash using "AutoEccGeneration" option.
    // When AutoEccGeneration option is used, Flash API calculates ECC for the
    // given 64-bit data and programs it along with the 64-bit main array data.
    // Note that any unprovided data with in a 64-bit data slice
    // will be assumed as 1s for calculating ECC and will be programmed.
    //
    // Note that data buffer (Buffer) is aligned on 64-bit boundary for verify
    // reasons.
    //
    // Monitor ECC address for Bank 0 while programming with AutoEcc mode.
    //
    // In this example, Flash Bank 0 is programmed along with auto-generated 
    // ECC.
    //
    for(sector = FlashBank0StartAddress; sector < FlashBank0EndAddress;
        sector += Sector2KB_u16length)
    {
        for(i=0, u32Index = sector;
           (u32Index < (sector + WORDS_IN_FLASH_BUFFER));
            i+= 8, u32Index+= 8)
        {
            ClearFSMStatus();

            // Enable program/erase protection for select sectors where this example is 
            // located
            // CMDWEPROTA is applicable for sectors 0-31
            // Bits 0-11 of CMDWEPROTB is applicable for sectors 32-127, each bit represents
            // a group of 8 sectors, e.g bit 0 represents sectors 32-39, bit 1 represents
            // sectors 40-47, etc
            Fapi_setupBankSectorEnable(FLASH_WRAPPER_PROGRAM_BASE+FLASH_O_CMDWEPROTA, 0x013FFFF00);
            Fapi_setupBankSectorEnable(FLASH_WRAPPER_PROGRAM_BASE+FLASH_O_CMDWEPROTB, 0x000000080);

            oReturnCheck = Fapi_issueProgrammingCommand((uint32 *)u32Index,
                                                        Buffer+i, 8, 0, 0,
                                                        Fapi_AutoEccGeneration);

            //
            // Wait until the Flash program operation is over
            //
            while(Fapi_checkFsmForReady() == Fapi_Status_FsmBusy);

            if(oReturnCheck != Fapi_Status_Success)
            {
                //
                // Check Flash API documentation for possible errors
                //
                Example_Error(oReturnCheck);
            }

            //
            // Read FMSTAT register contents to know the status of FSM after
            // program command to see if there are any program operation
            // related errors
            //
            oFlashStatus = Fapi_getFsmStatus();
            if(oFlashStatus != 3)
            {
                // oFlashStatus will be 17 when there is a program error due to
                // the sector having protection enabled. In this example,
                // protections are enabled for sectors in which the example
                // itself is written. We don't want to write over the program
                // itself so the protection is enabled. Due to this, we will
                // see an oFlashStatus of 17.
                if(oFlashStatus != 0x11)
                {
                    //
                    //Check FMSTAT and debug accordingly
                    //
                    FMSTAT_Fail();
                }
                
            }

           if(oFlashStatus != 0x11)
           {
                //
                // Verify the programmed values.  Check for any ECC errors.
                //

                oReturnCheck = Fapi_doVerify((uint32 *)u32Index,
                                             4, (uint32 *)(uint32)(Buffer + i),
                                             &oFlashStatusWord);

                if(oReturnCheck != Fapi_Status_Success)
                {
                    //
                    // Check Flash API documentation for possible errors
                    //
                    Example_Error(oReturnCheck);
                }
           }

        }
    }

}

//*****************************************************************************
//  Example_ProgramUsingDataOnlyECCOnly
//
//  Example function to Program data in Flash using "DataOnly" option and ECC
//  using "EccOnly" option.
//  Flash API functions used in this function are executed from RAM in this
//  example.
//*****************************************************************************
#ifdef __cplusplus
#pragma CODE_SECTION(".TI.ramfunc");
#else
#pragma CODE_SECTION(Example_ProgramUsingDataOnlyECCOnly, ".TI.ramfunc");
#endif
void Example_ProgramUsingDataOnlyECCOnly(void)
{
    uint32 u32Index = 0;
    uint16 i = 0, ECC_B = 0, ECC_LB = 0, ECC_HB = 0;
    uint64 *LData, *HData;
    Fapi_StatusType  oReturnCheck;
    Fapi_FlashStatusType  oFlashStatus;
    Fapi_FlashStatusWordType  oFlashStatusWord;

    //
    // Program data using "DataOnly" option and ECC using "EccOnly" option.
    //
    // When DataOnly option is used, Flash API will program only the data
    // portion in Flash at the address specified.
    //
    // When EccOnly option is used, Flash API will program only the ECC portion
    // in Flash ECC memory space (Flash main array address should be provided
    // for this function and not the corresponding ECC address).
    // Fapi_calculateEcc is used to calculate the corresponding ECC of the data.
    //
    // Note that data buffer (Buffer) is aligned on 64-bit boundary for verify
    // reasons.
    //
    // In this example, 0x100 bytes are programmed in Flash Sector6
    // along with the specified ECC.
    //

    for(i=0, u32Index = Bzero_Sector0_start;
       (u32Index < (Bzero_Sector0_start + WORDS_IN_FLASH_BUFFER));
       i+= 8, u32Index+= 8)
    {
        ClearFSMStatus();

        // Enable program/erase protection for select sectors where this example is 
        // located
        // CMDWEPROTA is applicable for sectors 0-31
        // Bits 0-11 of CMDWEPROTB is applicable for sectors 32-127, each bit represents
        // a group of 8 sectors, e.g bit 0 represents sectors 32-39, bit 1 represents
        // sectors 40-47, etc
        Fapi_setupBankSectorEnable(FLASH_WRAPPER_PROGRAM_BASE+FLASH_O_CMDWEPROTA, 0x13FFFF00);
        Fapi_setupBankSectorEnable(FLASH_WRAPPER_PROGRAM_BASE+FLASH_O_CMDWEPROTB, 0x00000080);

        //
        // Point LData to the lower 64 bit data
        // and   HData to the higher 64 bit data
        //
        LData = (uint64 *)(Buffer32 + i/2);
        HData = (uint64 *)(Buffer32 + i/2 + 2);

        //
        // Calculate ECC for lower 64 bit and higher 64 bit data
        //
        ECC_LB = Fapi_calculateEcc(u32Index,*LData);
        ECC_HB = Fapi_calculateEcc(u32Index+4,*HData);
        ECC_B = ((ECC_HB<<8) | ECC_LB);

        oReturnCheck = Fapi_issueProgrammingCommand((uint32 *)u32Index,Buffer+i,
                                                        8, 0, 0, Fapi_DataOnly);

        //
        // Wait until the Flash program operation is over
        //
        while(Fapi_checkFsmForReady() == Fapi_Status_FsmBusy);

        if(oReturnCheck != Fapi_Status_Success)
        {
            //
            // Check Flash API documentation for possible errors
            //
            Example_Error(oReturnCheck);
        }

        //
        // Read FMSTAT register contents to know the status of FSM after
        // program command to see if there are any program operation related
        // errors
        //
        oFlashStatus = Fapi_getFsmStatus();
        if(oFlashStatus != 3)
        {
            //Check FMSTAT and debug accordingly
            FMSTAT_Fail();
        }
        // Enable program/erase protection for select sectors where this example is 
        // located
        // CMDWEPROTA is applicable for sectors 0-31
        // Bits 0-11 of CMDWEPROTB is applicable for sectors 32-127, each bit represents
        // a group of 8 sectors, e.g bit 0 represents sectors 32-39, bit 1 represents
        // sectors 40-47, etc
        Fapi_setupBankSectorEnable(FLASH_WRAPPER_PROGRAM_BASE+FLASH_O_CMDWEPROTA, 0x13FFFF00);
        Fapi_setupBankSectorEnable(FLASH_WRAPPER_PROGRAM_BASE+FLASH_O_CMDWEPROTB, 0x00000080);

        oReturnCheck = Fapi_issueProgrammingCommand((uint32 *)u32Index, 0, 0,
                                                    &ECC_B, 2, Fapi_EccOnly);

        //
        // Wait until the Flash program operation is over
        //
        while(Fapi_checkFsmForReady() == Fapi_Status_FsmBusy);

        if(oReturnCheck != Fapi_Status_Success)
        {
            //
            // Check Flash API documentation for possible errors
            //
            Example_Error(oReturnCheck);
        }

        //
        // Read FMSTAT register contents to know the status of FSM after
        // program command to see if there are any program operation related
        // errors
        //
        oFlashStatus = Fapi_getFsmStatus();
        if(oFlashStatus != 3)
        {
            //
            // Check FMSTAT and debug accordingly
            //
            FMSTAT_Fail();
        }

        Flash_enableECC(FLASH0ECC_BASE);

        //
        // Verify the programmed values.  Check for any ECC errors.
        //
        oReturnCheck = Fapi_doVerify((uint32 *)u32Index,
                                     4, (uint32 *)(uint32)(Buffer + i),
                                     &oFlashStatusWord);

        if(oReturnCheck != Fapi_Status_Success)
        {
            //
            // Check Flash API documentation for possible errors
            //
            Example_Error(oReturnCheck);
        }
    }
}

//*****************************************************************************
//  Example_ProgramUsingDataAndECC
//
//  Example function to Program data in Flash using "DataAndEcc" option.
//  Flash API functions used in this function are executed from RAM in this
//  example.
//*****************************************************************************
#ifdef __cplusplus
#pragma CODE_SECTION(".TI.ramfunc");
#else
#pragma CODE_SECTION(Example_ProgramUsingDataAndECC, ".TI.ramfunc");
#endif
void Example_ProgramUsingDataAndECC(void)
{
    uint32 u32Index = 0;
    uint16 i = 0, ECC_B = 0, ECC_LB = 0, ECC_HB = 0;
    uint64 *LData, *HData;
    Fapi_StatusType  oReturnCheck;
    Fapi_FlashStatusType  oFlashStatus;
    Fapi_FlashStatusWordType  oFlashStatusWord;

    //
    // Program data and ECC in Flash using "DataAndEcc" option.
    // When DataAndECC option is used, Flash API will program both the supplied
    // data and ECC in Flash at the address specified.
    // Fapi_calculateEcc is used to calculate the corresponding ECC of the data.
    //
    // Note that data buffer (Buffer) is aligned on 64-bit boundary for verify
    // reasons.
    //
    // In this example, 0x100 bytes are programmed in Flash Sector6
    // along with the specified ECC.
    //

    for(i=0, u32Index = Bzero_Sector0_start;
       (u32Index < (Bzero_Sector0_start + WORDS_IN_FLASH_BUFFER));
       i+= 8, u32Index+= 8)
    {
        ClearFSMStatus();

        // Enable program/erase protection for select sectors where this example is 
        // located
        // CMDWEPROTA is applicable for sectors 0-31
        // Bits 0-11 of CMDWEPROTB is applicable for sectors 32-127, each bit represents
        // a group of 8 sectors, e.g bit 0 represents sectors 32-39, bit 1 represents
        // sectors 40-47, etc
        Fapi_setupBankSectorEnable(FLASH_WRAPPER_PROGRAM_BASE+FLASH_O_CMDWEPROTA, 0x13FFFF00);
        Fapi_setupBankSectorEnable(FLASH_WRAPPER_PROGRAM_BASE+FLASH_O_CMDWEPROTB, 0x00000080);

        //
        // Point LData to the lower 64 bit data
        // and   HData to the higher 64 bit data
        //
        LData = (uint64 *)(Buffer32 + i/2);
        HData = (uint64 *)(Buffer32 + i/2 + 2);

        //
        // Calculate ECC for lower 64 bit and higher 64 bit data
        //
        ECC_LB = Fapi_calculateEcc(u32Index,*LData);
        ECC_HB = Fapi_calculateEcc(u32Index+4,*HData);
        ECC_B = ((ECC_HB<<8) | ECC_LB);

        oReturnCheck = Fapi_issueProgrammingCommand((uint32 *)u32Index,Buffer+i,
                                                 8, &ECC_B, 2, Fapi_DataAndEcc);

        //
        // Wait until the Flash program operation is over
        //
        while(Fapi_checkFsmForReady() == Fapi_Status_FsmBusy);

        if(oReturnCheck != Fapi_Status_Success)
        {
            //
            // Check Flash API documentation for possible errors
            //
            Example_Error(oReturnCheck);
        }

        //
        // Read FMSTAT register contents to know the status of FSM after
        // program command to see if there are any program operation related
        // errors
        //
        oFlashStatus = Fapi_getFsmStatus();
        if(oFlashStatus != 3)
        {
            //
            // Check FMSTAT and debug accordingly
            //
            FMSTAT_Fail();
        }

        Flash_enableECC(FLASH0ECC_BASE);

        //
        // Verify the programmed values.  Check for any ECC errors.
        //
        oReturnCheck = Fapi_doVerify((uint32 *)u32Index,
                                     4, (uint32 *)(uint32)(Buffer + i),
                                     &oFlashStatusWord);

        if(oReturnCheck != Fapi_Status_Success)
        {
            //
            // Check Flash API documentation for possible errors
            //
            Example_Error(oReturnCheck);
        }
    }

}

//*****************************************************************************
//  Example_EraseSector
//
//  Example function to Erase data of a sector in Flash.
//  Flash API functions used in this function are executed from RAM in this
//  example.
//*****************************************************************************
#ifdef __cplusplus
#pragma CODE_SECTION(".TI.ramfunc");
#else
#pragma CODE_SECTION(Example_EraseSector, ".TI.ramfunc");
#endif
void Example_EraseSector(void)
{
    Fapi_StatusType  oReturnCheck;
    Fapi_FlashStatusType  oFlashStatus;
    Fapi_FlashStatusWordType  oFlashStatusWord;
        ClearFSMStatus();

        // Enable program/erase protection for select sectors where this example is 
        // located
        // CMDWEPROTA is applicable for sectors 0-31
        // Bits 0-11 of CMDWEPROTB is applicable for sectors 32-127, each bit represents
        // a group of 8 sectors, e.g bit 0 represents sectors 32-39, bit 1 represents
        // sectors 40-47, etc
        Fapi_setupBankSectorEnable(FLASH_WRAPPER_PROGRAM_BASE+FLASH_O_CMDWEPROTA, 0x13FFFF00);
        Fapi_setupBankSectorEnable(FLASH_WRAPPER_PROGRAM_BASE+FLASH_O_CMDWEPROTB, 0x00000080);


    //
    // Erase the sector that is programmed in the above example
    // Erase Sector 0
    //
    oReturnCheck = Fapi_issueAsyncCommandWithAddress(Fapi_EraseSector,
                   (uint32 *)Bzero_Sector0_start);
    //
    // Wait until FSM is done with erase sector operation
    //
    while (Fapi_checkFsmForReady() != Fapi_Status_FsmReady){}

    if(oReturnCheck != Fapi_Status_Success)
    {
        //
        // Check Flash API documentation for possible errors
        //
        Example_Error(oReturnCheck);
    }

    //
    // Read FMSTAT register contents to know the status of FSM after
    // erase command to see if there are any erase operation related errors
    //
    oFlashStatus = Fapi_getFsmStatus();
        if(oFlashStatus != 3)
    {
        //
        // Check Flash API documentation for FMSTAT and debug accordingly
        // Fapi_getFsmStatus() function gives the FMSTAT register contents.
        // Check to see if any of the EV bit, ESUSP bit, CSTAT bit or
        // VOLTSTAT bit is set (Refer to API documentation for more details).
        //
        FMSTAT_Fail();
    }

    //
    // Verify that Sector0 is erased
    //
    oReturnCheck = Fapi_doBlankCheck((uint32 *)Bzero_Sector0_start,
                   Sector2KB_u32length,
                   &oFlashStatusWord);
    if(oReturnCheck != Fapi_Status_Success)
    {
        //
        // Check Flash API documentation for error info
        //
        Example_Error(oReturnCheck);
    }
}

//*****************************************************************************
//  Example_EraseBanks
//
//  Example function to Erase data of a sector in Flash.
//  Flash API functions used in this function are executed from RAM in this
//  example.
//*****************************************************************************
#ifdef __cplusplus
#pragma CODE_SECTION(".TI.ramfunc");
#else
#pragma CODE_SECTION(Example_EraseBanks, ".TI.ramfunc");
#endif
void Example_EraseBanks(void)
{
    Fapi_StatusType  oReturnCheck;
    Fapi_FlashStatusType  oFlashStatus;
    Fapi_FlashStatusWordType  oFlashStatusWord;
    uint32 u32CurrentAddress = 0;

    ClearFSMStatus();

    // Enable program/erase protection for select sectors where this example is 
    // located
    // CMDWEPROTA is applicable for sectors 0-31
    // Bits 0-11 of CMDWEPROTB is applicable for sectors 32-127, each bit represents
    // a group of 8 sectors, e.g bit 0 represents sectors 32-39, bit 1 represents
    // sectors 40-47, etc
    Fapi_setupBankSectorEnable(FLASH_WRAPPER_PROGRAM_BASE+FLASH_O_CMDWEPROTA, 0x13FFFF00);
    Fapi_setupBankSectorEnable(FLASH_WRAPPER_PROGRAM_BASE+FLASH_O_CMDWEPROTB, 0x00000080);

    u32CurrentAddress = Bzero_Sector0_start;

    //
    //Issue bank erase command
    //
    oReturnCheck = Fapi_issueBankEraseCommand((uint32 *)u32CurrentAddress);

    //
    // Wait until FSM is done with erase sector operation
    //
    while (Fapi_checkFsmForReady() != Fapi_Status_FsmReady){}

    if(oReturnCheck != Fapi_Status_Success)
    {
        // Check Flash API documentation for possible errors
        Example_Error(oReturnCheck);
    }

    // Read FMSTAT register contents to know the status of FSM after
    // erase command to see if there are any erase operation related errors
    oFlashStatus = Fapi_getFsmStatus();
    if(oFlashStatus != 3)
    {
        // Check Flash API documentation for FMSTAT and debug accordingly
        // Fapi_getFsmStatus() function gives the FMSTAT register contents.
        // Check to see if any of the EV bit, ESUSP bit, CSTAT bit or
        // VOLTSTAT bit is set (Refer to API documentation for more details).
        FMSTAT_Fail();
    }


    // Do blank check
    // Blank check is performed on all the sectors that are not protected 
    // during Bank erase 
    // Verify that Bank 0 is erased.
    // The Erase command itself does a verify as it goes.
    // Hence erase verify by CPU reads (Fapi_doBlankCheck()) is optional.
    u32CurrentAddress = Bzero_Sector0_start;
    oReturnCheck = Fapi_doBlankCheck((uint32 *)u32CurrentAddress,
                   (8*Sector2KB_u32length),
                   &oFlashStatusWord);

    if(oReturnCheck != Fapi_Status_Success)
    {
        // Check Flash API documentation for error info
        Example_Error(oReturnCheck);
    }

    u32CurrentAddress = Bzero_Sector26_start;
        oReturnCheck = Fapi_doBlankCheck((uint32 *)u32CurrentAddress,
                       (2*Sector2KB_u32length),
                       &oFlashStatusWord);

    if(oReturnCheck != Fapi_Status_Success)
    {
        // Check Flash API documentation for error info
        Example_Error(oReturnCheck);
    }

    u32CurrentAddress = Bzero_Sector29_start;
           oReturnCheck = Fapi_doBlankCheck((uint32 *)u32CurrentAddress,
                          (59*Sector2KB_u32length),
                          &oFlashStatusWord);

   if(oReturnCheck != Fapi_Status_Success)
   {
       // Check Flash API documentation for error info
       Example_Error(oReturnCheck);
   }

   u32CurrentAddress = Bzero_Sector89_start;
          oReturnCheck = Fapi_doBlankCheck((uint32 *)u32CurrentAddress,
                         (39*Sector2KB_u32length),
                         &oFlashStatusWord);

  if(oReturnCheck != Fapi_Status_Success)
  {
      // Check Flash API documentation for error info
      Example_Error(oReturnCheck);
  }
}

//******************************************************************************
// For this example, just stop here if an API error is found
//******************************************************************************
void Example_Error(Fapi_StatusType status)
{
    //
    //  Error code will be in the status parameter
    //
    __asm("    ESTOP0");
}

//******************************************************************************
//  For this example, once we are done just stop here
//******************************************************************************
void Example_Done(void)
{
    __asm("    ESTOP0");
}

//******************************************************************************
// For this example, just stop here if FMSTAT fail occurs
//******************************************************************************
void FMSTAT_Fail(void)
{
    __asm("    ESTOP0");
}

//******************************************************************************
// For this example, just stop here if ECC fail occurs
//******************************************************************************
void ECC_Fail(void)
{
    __asm("    ESTOP0");
}

//
// End of File
//
