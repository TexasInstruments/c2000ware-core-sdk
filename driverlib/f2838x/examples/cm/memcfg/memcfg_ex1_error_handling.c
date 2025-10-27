//#############################################################################
//
// FILE:   memcfg_ex1_error_handling.c
//
// TITLE:  Demonstrate memconfig diagnostics and error handling
//
//! \addtogroup driver_example_cm_list
//! <h1> Demonstrate memconfig diagnostics and error handling. </h1>
//!
//! This example demonstrates how to configure the diagnostic mode and induce
//! ECC errors. This example induces single and two bit ECC errors in E0RAM and
//! tries to read the corrupted location in diagnostic and functional mode.
//! cm_common_config_c28x example needs to be run on C28x1 before running this
//! example on the CM core
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//! - \b testStatus - Equivalent to \b TEST_PASS if test finished
//!                   correctly, else the value is set to \b TEST_FAIL
//! - \b errorGlobalCount - Error counter
//! - \b retx - Individual test status
//!
//
//#############################################################################
//
//
// 
// C2000Ware v6.00.01.00
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

#include <stdint.h>
#include <stdbool.h>
#include "cpu.h"
#include "sysctl.h"
#include "interrupt.h"
#include "memcfg.h"


#define TEST_PASS 0xABCDABCD
#define TEST_FAIL 0xDEADDEAD

void Write_CAFECAFE(uint32_t startAddress, uint32_t endAddress)
{
    uint32_t * addr;
    for (addr = (uint32_t *)startAddress;addr <= (uint32_t *)endAddress ; addr++)
        {
            *addr = 0xCAFECAFE;
        }
}

static volatile uint32_t memcfgErrorCount;
static volatile uint32_t nmiFaultCount, nmiFaultAddr;
uint32_t offset, eccRead1, eccRead2, readDataStart, cnt;

static volatile uint32_t testStatus = TEST_FAIL;
static volatile uint32_t errorGlobalCount = 0;


void
NMIFaultHandler(void)
{
	//
	// Check the NMI flag and clear it
	//
    if(!SysCtl_isNMIFlagSet(SYSCTL_NMI_MEMUNCERR))
    {
        errorGlobalCount++;
    }
    SysCtl_clearAllNMIFlags();
	
	//
	// get the address at which error occured and clear the flag
	//
    nmiFaultAddr = MemCfg_getUncorrErrorAddress(MEMCFG_UCERR_M4READ);
    MemCfg_clearUncorrErrorStatus(MEMCFG_UCERR_M4READ);

    //
    // Increment a counter to indicate the fault occurred.
    //
    nmiFaultCount++;
}


void
memcfgErrorISR(void)
{
	// 
	// Check the flag and clear it
	//
    if(MemCfg_getCorrErrorInterruptStatus() != MEMCFG_CERR_M4READ)
    {
        errorGlobalCount++;
    }
    MemCfg_clearCorrErrorInterruptStatus(MEMCFG_CERR_M4READ);

    //
    // Increment a counter to indicate the error occurred.
    //
    memcfgErrorCount++;
}

bool Test_CorrErr_DiagMode();
bool Test_CorrErr_FuncMode();
bool Test_UncorrErr();

//
// Main
//
int
main(void)
{
    //
    // Enable Memcfg interrupt and NMI.
    //
    Interrupt_registerHandler(INT_CMRAM_TESTERROR_LOG, memcfgErrorISR);
    Interrupt_enable(INT_CMRAM_TESTERROR_LOG);

    Interrupt_registerHandler(FAULT_NMI, NMIFaultHandler);
    SysCtl_enableGlobalNMI();

    //
    // Run the tests
    //
    bool ret1 = Test_CorrErr_DiagMode();
    bool ret2 = Test_CorrErr_FuncMode();
    bool ret3 = Test_UncorrErr();

    if(ret1 && ret2 && ret3)
        testStatus = TEST_PASS;
    else
        testStatus = TEST_FAIL;

    while(1);
}

//
// Induce correctable error in memory in diagnostics mode
//
bool Test_CorrErr_DiagMode()
{
    memcfgErrorCount = 0;
    nmiFaultCount = 0;
    bool status = true;

    MemCfg_setTestMode(MEMCFG_SECT_E0, MEMCFG_TEST_FUNCTIONAL);
	
    //
    // Initial ROM read leads to error since ROM parity bits are not loaded
    // properly
	//
    MemCfg_clearUncorrErrorStatus(MEMCFG_UCERR_M4READ);
    MemCfg_clearCorrErrorStatus(MEMCFG_CERR_M4READ);
    MemCfg_enableCorrErrorInterrupt(MEMCFG_CERR_M4READ);
    SysCtl_clearAllNMIFlags();

    //
    // Write to E0 RAM
    //
    Write_CAFECAFE(E0RAM_BASE, E0RAM_BASE + 0x3FFF);

    //
    // Set correctable error threshold. Correctable interrupt will be generated
    // once correctable error count reaches the threshold value.
    //
    MemCfg_setCorrErrorThreshold(5U);

    //
	// Generate 6 correctable errors
	//
    for(cnt = 1U; cnt<= 6U; cnt++)
    {
        offset = 0x08U + cnt*4U;

        //
		// ECC data read before corrupting
        //
		MemCfg_setTestMode(MEMCFG_SECT_E0,MEMCFG_TEST_WRITE_ECC);
        eccRead1 = HWREG(E0RAM_BASE + offset);

        //
		// Flip single bit and write back
        //
		MemCfg_setTestMode(MEMCFG_SECT_E0,MEMCFG_TEST_WRITE_DATA);
        HWREG(E0RAM_BASE + offset) = HWREG(E0RAM_BASE + offset) ^ 0x02;

        //
		// ECC data read after corrupting
        //
		MemCfg_setTestMode(MEMCFG_SECT_E0,MEMCFG_TEST_WRITE_ECC);
        eccRead2 = HWREG(E0RAM_BASE + offset);

        //
        // Go to diagnostic mode.
        // Try to read data and ceheck if diagnostic log register bits
        // are getting updated.
        //
        MemCfg_setTestMode(MEMCFG_SECT_E0,MEMCFG_TEST_FUNC_DIAG);
        readDataStart = HWREG(E0RAM_BASE + offset);
		
        uint32_t diagErrStatus = MemCfg_getDiagErrorStatus();
        uint32_t diagErrAddr = MemCfg_getDiagErrorAddress();
		
        if((diagErrStatus != MEMCFG_DIAGERR_CORR_READ) ||
            (diagErrAddr != (E0RAM_BASE + offset)) ||
            (eccRead1 != eccRead2))
        {
           return false;
        }
		
		//
		// Clear the error flag
		//
        MemCfg_clearDiagErrorStatus(MEMCFG_DIAGERR_CORR_READ);
    }

	//
	// Go back to functional mode
	//
    MemCfg_setTestMode(MEMCFG_SECT_E0, MEMCFG_TEST_FUNCTIONAL);
    MemCfg_disableCorrErrorInterrupt(MEMCFG_CERR_M4READ);

	//
	// Adding NOPs to introduce delay
	//
    asm(" nop");
    asm(" nop");
    asm(" nop");
    asm(" nop");

	//
	// Check for fault flags if any
	//
    if(memcfgErrorCount != 0)
        return false;
    if(nmiFaultCount != 0)
        return false;

    return status;
}

//
// Induce correctable error & check if interrupt is
// getting generated once threshold is reached.
//
bool Test_CorrErr_FuncMode()
{
    memcfgErrorCount = 0;
    nmiFaultCount = 0;
    errorGlobalCount = 0;

    MemCfg_setTestMode(MEMCFG_SECT_E0, MEMCFG_TEST_FUNCTIONAL);

    //
    // Initial ROM read leads to error since ROM parity bits are not loaded
    // properly
	//
    MemCfg_clearUncorrErrorStatus(MEMCFG_UCERR_M4READ);
    MemCfg_clearCorrErrorStatus(MEMCFG_CERR_M4READ);
    MemCfg_enableCorrErrorInterrupt(MEMCFG_CERR_M4READ);
    SysCtl_clearAllNMIFlags();
    HWREG(CMMEMORYERROR_BASE + MEMCFG_O_CERRCNT) = 0;

    //
    // Write to E0 RAM
    //
    Write_CAFECAFE(E0RAM_BASE, E0RAM_BASE+0x3FFF);

    //
    // Set correctable error threshold. Correctable interrupt will be generated
    // once corr error count reaches the threshold value.
    //
    MemCfg_setCorrErrorThreshold(5U);

    //
	// Generate 6 correctable erros
    //
	for(cnt = 1U; cnt<= 6U; cnt++)
    {
        offset = 0x08U + cnt * 4U;

       //
	   // ECC data read before corrupting
       //
	   MemCfg_setTestMode(MEMCFG_SECT_E0,MEMCFG_TEST_WRITE_ECC);
       eccRead1 = HWREG(E0RAM_BASE + offset);

       //
	   // Flip single bit and write back
       //
	   MemCfg_setTestMode(MEMCFG_SECT_E0,MEMCFG_TEST_WRITE_DATA);
       HWREG(E0RAM_BASE + offset) = HWREG(E0RAM_BASE + offset) ^ 0x02;
       readDataStart = HWREG(E0RAM_BASE + offset);

       //
	   // ECC data read after corrupting
       //
	   MemCfg_setTestMode(MEMCFG_SECT_E0,MEMCFG_TEST_WRITE_ECC);
       eccRead2 = HWREG(E0RAM_BASE + offset);

       //
	   // Bring back to functional mode.
	   //
	   MemCfg_setTestMode(MEMCFG_SECT_E0,MEMCFG_TEST_FUNCTIONAL);
       MemCfg_clearUncorrErrorStatus(MEMCFG_UCERR_M4READ);


       //
	   // Read data to induce error
       //
	   readDataStart = HWREG(E0RAM_BASE + offset);
	   
	   //
	   // Check for the correctable error count. An interrupt is genertaed one
	   // the count reaches 5 and the count is reset
	   //
       uint32_t corrErrCnt = MemCfg_getCorrErrorCount();
       if(corrErrCnt != (cnt % 5))
           return false;

       //
	   // Check if the ECC before and after corruption is the same
	   // Check for error flag and address
       //
	   uint32_t corrErrStatus = MemCfg_getCorrErrorStatus();
       uint32_t corrErrAddr = MemCfg_getCorrErrorAddress(MEMCFG_CERR_M4READ);
       if((eccRead1 != eccRead2) ||
          (corrErrStatus != MEMCFG_CERR_M4READ) ||
          (corrErrAddr != (E0RAM_BASE + offset)))
       {
           return false;
       }
	   
	   //
	   // Clear the flags
	   //
       MemCfg_clearCorrErrorStatus(MEMCFG_CERR_M4READ);
       MemCfg_disableCorrErrorInterrupt(MEMCFG_CERR_M4READ);
       MemCfg_enableCorrErrorInterrupt(MEMCFG_CERR_M4READ);

    }

    MemCfg_disableCorrErrorInterrupt(MEMCFG_CERR_M4READ);

	//
	// Adding NOPs to introduce delay
	//
    asm(" nop");
    asm(" nop");
    asm(" nop");
    asm(" nop");

	//
	// Check for the fault ISRs. Check if MemCfg error interrupt is invoked once
	//
    if(memcfgErrorCount != 1)
        return false;
    if(nmiFaultCount != 0)
        return false;
    if(errorGlobalCount != 0)
        return false;

    return true;
}

//
//Induce uncorrectable error in memory
//
bool Test_UncorrErr()
{
    memcfgErrorCount = 0;
    nmiFaultCount = 0;
    errorGlobalCount = 0;

    MemCfg_setTestMode(MEMCFG_SECT_E0, MEMCFG_TEST_FUNCTIONAL);

    //
    // Initial ROM read leads to error since ROM parity bits are not loaded
    // properly
	//
    MemCfg_clearUncorrErrorStatus(MEMCFG_UCERR_M4READ);
    MemCfg_clearCorrErrorStatus(MEMCFG_CERR_M4READ);
    MemCfg_enableCorrErrorInterrupt(MEMCFG_CERR_M4READ);
    SysCtl_clearAllNMIFlags();

    //
    // Write to E0 RAM
    //
    Write_CAFECAFE(E0RAM_BASE, E0RAM_BASE+0x3FFF);

    //
    // Set correctable error threshold. Correctable interrupt will be generated
    // once corr error count reaches the threshold value.
    //
    MemCfg_setCorrErrorThreshold(5U);

    //
	// Generate 6 correctable erros
    //
	for(cnt = 1U; cnt<= 6U; cnt++)
    {
        offset = 0x08U + cnt*4U;

        MemCfg_setTestMode(MEMCFG_SECT_E0,MEMCFG_TEST_WRITE_ECC);

        //
		// ECC data read before corrupting
        //
		eccRead1 = HWREG(E0RAM_BASE + offset);
        MemCfg_setTestMode(MEMCFG_SECT_E0,MEMCFG_TEST_WRITE_DATA);

        //
		// Flip two bits and write back
        //
		HWREG(E0RAM_BASE + offset) = HWREG(E0RAM_BASE + offset) ^ 0x03;

        //
		// ECC data read after corrupting
        //
		MemCfg_setTestMode(MEMCFG_SECT_E0,MEMCFG_TEST_WRITE_ECC);
        eccRead2 = HWREG(E0RAM_BASE + offset);

        //
        // Bring back to functional mode.
        //
        MemCfg_setTestMode(MEMCFG_SECT_E0,MEMCFG_TEST_FUNCTIONAL);

        //
        // Initial ROM read leads to error since ROM parity bits are not loaded
        // properly
        //
        MemCfg_clearUncorrErrorStatus(MEMCFG_UCERR_M4READ);
		
        //
		// Read data to induce error. This causes an NMI
        //
		readDataStart = HWREG(E0RAM_BASE + offset);

		//
		// Adding NOPs to introduce delay
		//
        asm(" nop");
        asm(" nop");
        asm(" nop");
        asm(" nop");

        //
		// Check if the ECC before and after corruption is the same
		// Check for NMI flag and address
        //
		if((eccRead1 != eccRead2) || (nmiFaultCount != cnt) || nmiFaultAddr != (E0RAM_BASE + offset))
        {
            return false;
        }
		
        MemCfg_clearUncorrErrorStatus(MEMCFG_UCERR_M4READ);
    }

 	//
	// Adding NOPs to introduce delay
	//
	asm(" nop");
    asm(" nop");
    asm(" nop");
    asm(" nop");

	//
	// Check for fault ISRs. Check if NMI fault is invoked 6 times
	//
    if(memcfgErrorCount != 0)
        return false;
    if(nmiFaultCount != 6)
        return false;
    if(errorGlobalCount != 0)
        return false;

    return true;
}
