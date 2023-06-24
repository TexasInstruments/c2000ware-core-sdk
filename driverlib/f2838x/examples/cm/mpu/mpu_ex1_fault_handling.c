//#############################################################################
//
// FILE:   mpu_ex1_fault_handling.c
//
// TITLE:  Demonstrate CM4 MPU usage.
//
//! \addtogroup driver_example_cm_list
//! <h1> Demonstrate CM4 MPU usage. </h1>
//!
//! This example demonstrates how to configure MPU regions for different levels
//! of memory protection using core MPU. It demonstrates the use of the MPU to
//! protect a region of memory from access, and to handle a memory management
//! fault when there is an access violation.
//!
//! The following memory map is set up:
//! -\b Region 0 - executable, prv(r/w), user(r/w)
//! -\b Region 1 - executable, prv(read only), user(read only), code mem(RAM)
//! -\b Region 2 - executable, prv(read only), user(read only), code mem(RAM)
//! -\b Region 3 - non-exec, prv(r/w), user(r/w), for NVIC
//! -\b Region 4 - non-exec, prv(read only), user(none)
//! -\b Region 5 - non-exec, prv(none), user(none)
//! -\b Region 6 - non-exec, prv(read only), user(read only)
//! -\b Region 7 - non-exec, prv (r/w), user (none)
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//! - \b testStatusGlobal - Equivalent to \b TEST_PASS if test finished
//!                         correctly, else the value is set to \b TEST_FAIL
//!
//
//#############################################################################
//
//
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
//#############################################################################

//
// Included Files
//
#include "driverlib_cm.h"
#include "cm.h"

//
// Defines
//
#define TEST_PASS 0xABCDABCD
#define TEST_FAIL 0xDEADDEAD

//
// Global Variables
//

//
// Global test status
//
uint32_t testStatusGlobal;

//
// Variables to hold the state of the fault status when the fault occurs and
// the faulting address.
//
static volatile uint32_t memFaultAdd, busFaultAdd;
static volatile uint32_t faultStatus;

//
// A counter to track the number of times the fault handler has been entered.
//
static volatile uint32_t faultCount;

//
// A location for storing data read from various addresses.  Volatile forces
// the compiler to use it and not optimize the access away.
//
static volatile uint32_t readVal;
uint32_t successFlag = 0, tempVal;

//
// Function Prototypes
//
void MPUFaultHandler(void);
void BUSFaultHandler(void);

//
// Main
//
void main(void)
{
    //
    // Initialize device clock and peripherals
    //
    CM_init();

    //
    // Configuring Region 0- executable, prv(r/w), user(r/w)
    //
    MPU_setRegionAttributes(MPU_RGN_0, S3RAM_BASE,
                            (MPU_RGN_SIZE_16K | MPU_RGN_PERM_EXEC |
                             MPU_RGN_PERM_PRV_RW_USR_RW | MPU_RGN_ENABLE));

    //
    // Configuring Region 1- executable, prv(read only), user(read only)
    //
    MPU_setRegionAttributes(MPU_RGN_1, S1RAM_BASE,
                            (MPU_RGN_SIZE_16K | MPU_RGN_PERM_EXEC |
                             MPU_RGN_PERM_PRV_RO_USR_RO | MPU_RGN_ENABLE));

    //
    // Configuring Region 2- executable, prv(read only), user(read only)
    //
    MPU_setRegionAttributes(MPU_RGN_2, S0RAM_BASE,
                            (MPU_RGN_SIZE_16K | MPU_RGN_PERM_EXEC |
                             MPU_RGN_PERM_PRV_RO_USR_RO | MPU_RGN_ENABLE));

    //
    // Configuring Region 3- non-executable, prv(r/w), user(r/w)
    // This region is needed because NVIC registers are needed
    // in order to control the MPU.
    //
    MPU_setRegionAttributes(MPU_RGN_3, NVIC_BASE,
                            (MPU_RGN_SIZE_4K | MPU_RGN_PERM_NOEXEC |
                             MPU_RGN_PERM_PRV_RW_USR_RW | MPU_RGN_ENABLE));

    //
    // Configuring Region 4- non-executable, prv(read only), user(none)
    //
    MPU_setRegionAttributes(MPU_RGN_4, (S2RAM_BASE + 0x1800U),
                            (MPU_RGN_SIZE_2K | MPU_RGN_PERM_NOEXEC |
                             MPU_RGN_PERM_PRV_RO_USR_NO | MPU_RGN_ENABLE));

    //
    // Configuring Region 5- non-executable, prv(none), user(none)
    //
    MPU_setRegionAttributes(MPU_RGN_5, (S2RAM_BASE + 0x1000U),
                            (MPU_RGN_SIZE_2K | MPU_RGN_PERM_NOEXEC |
                             MPU_RGN_PERM_PRV_NO_USR_NO | MPU_RGN_ENABLE));

    //
    // Configuring Region 6- non-executable, prv(read only), user(read only)
    //
    MPU_setRegionAttributes(MPU_RGN_6, (S2RAM_BASE + 0x800U),
                            (MPU_RGN_SIZE_2K | MPU_RGN_PERM_NOEXEC |
                             MPU_RGN_PERM_PRV_RO_USR_RO | MPU_RGN_ENABLE));

    //
    // Configuring Region 7- non-executable, prv(r/w), user(none)
    //
    MPU_setRegionAttributes(MPU_RGN_7, S2RAM_BASE,
                            (MPU_RGN_SIZE_2K | MPU_RGN_PERM_NOEXEC |
                             MPU_RGN_PERM_PRV_RW_USR_NO | MPU_RGN_ENABLE));

    //
    // Need to clear the NVIC fault status register to make sure there is no
    // status hanging around from a previous program.
    //
    faultStatus = HWREG(NVIC_BASE + NVIC_O_MMSR);
    HWREG(NVIC_BASE + NVIC_O_MMSR) = faultStatus;

    //
    // Enable the MPU & bus fault interrupts.
    //
    Interrupt_enable(FAULT_MPU);
    Interrupt_registerHandler(FAULT_MPU, MPUFaultHandler);
    Interrupt_enable(FAULT_BUS);
    Interrupt_registerHandler(FAULT_BUS, BUSFaultHandler);

    //
    // Enable the MPU.  This will begin to enforce the memory protection
    // regions.  The MPU is configured so that when in the hard fault or NMI
    // exceptions, a default map will be used.  Neither of these should occur
    // in this example program.
    //
    MPU_enable(MPU_CONFIG_HARDFLT_NMI | MPU_CONFIG_PRIV_DEFAULT);

    //
    // Attempt to write to region 1(code  memory). This should cause a
    // protection fault due to the fact that this region is read-only.
    // These memory locations are chosen only for demonstration purpose.
    //
    faultCount = 0;
    HWREG(S0RAM_BASE + 0x1000U) = 0x12345678U;

    //
    // Adding NOPs to return execution to any of these NOPs and not the above
    // statement which generated fault. This has been done to avoid repeated
    // fault generation due to above memory write operation to protected memory.
    //
    NOP;
    NOP;
    NOP;
    NOP;

    //
    // Verify that the fault occurred, at the expected address.
    //
    if((faultCount == 1U) && (faultStatus == 0x82U) &&
       (memFaultAdd == (S0RAM_BASE + 0x1000U)))
    {
        //
        // Correct fault has occurred
        //
        successFlag++;
    }

    //
    // Writing to memory location region 7 which allows r/w in priv mode.
    // These memory locations are chosen only for demonstration purpose.
    //
    faultCount = 0;
    tempVal = HWREG(S2RAM_BASE + 0x100U);
	HWREG(S2RAM_BASE + 0x100U) = 0x12345678U;
	readVal = HWREG(S2RAM_BASE + 0x100U);
	if((readVal == 0x12345678U) && (faultCount == 0U))
	{
        //
        // Fault has not occurred
        //
		successFlag++;
	}

	//
	// Write back the original value.
	//
	HWREG(S2RAM_BASE + 0x100U) = tempVal;

	//
	// Writing to memory location region 6 which is read only in priv mode.
    // These memory locations are chosen only for demonstration purpose.
	//
	faultCount = 0;
	readVal = HWREG(S2RAM_BASE + 0x900);
	HWREG(S2RAM_BASE + 0x900) = 0x87654321;

    //
    // Adding NOPs to return execution to any of these NOPs and not the above
    // statement which generated fault. This has been done to avoid repeated
    // fault generation due to above memory write operation to protected memory.
    //
    NOP;
    NOP;
    NOP;
    NOP;

	//
	// Verify that the fault occurred, at the expected address.
	//
	if((faultCount == 1U) && (faultStatus == 0x82U) &&
	   (memFaultAdd == (S2RAM_BASE + 0x900U)))
	{
        //
        // Correct fault has occurred
        //
	    successFlag++;
	}

	faultCount = 0U;

	//
	// Reading from a memory location in region 5. This should generate fault.
	// Memory locations are chosen for demonstration purpose only.
	//
	readVal = HWREG(S2RAM_BASE + 0x1200U);

    //
    // Adding NOPs to return execution to any of these NOPs and not the above
    // statement which generated fault. This has been done to avoid repeated
    // fault generation due to above memory read operation to protected memory.
    //
    NOP;
    NOP;
    NOP;
    NOP;

	//
	// Verify that the fault occurred, at the expected address.
	//
	if((faultCount == 1U) && (faultStatus == 0x82U) &&
	   (memFaultAdd == (S2RAM_BASE + 0x1200U)))
	{
        //
        // Correct fault has occurred
        //
		successFlag++;
	}

	faultCount = 0U;

    //
    // Writing to a memory location in region 5. This should generate fault.
    // Memory locations are chosen for demonstration purpose only.
    //
	HWREG(S2RAM_BASE + 0x1200U) = readVal;

    //
    // Adding NOPs to return execution to any of these NOPs and not the above
    // statement which generated fault. This has been done to avoid repeated
    // fault generation due to above memory write operation to protected memory.
    //
    NOP;
    NOP;
    NOP;
    NOP;

	//
	// Verify that the fault occurred, at the expected address.
	//
	if((faultCount == 1U) && (faultStatus == 0x82U) &&
	   (memFaultAdd == (S2RAM_BASE + 0x1200U)))
	{
        //
        // Correct fault has occurred
        //
		successFlag++;
	}

    //
    // Disable the MPU, so there are no lingering side effects if another
    // program is run.
    //
    MPU_disable();

    if(successFlag == 5U)
    {
        testStatusGlobal = TEST_PASS;
    }

    //
    // Loop forever.
    //
    while(1)
    {
    }
}

//
// MPUFaultHandler - The exception handler for memory management faults,
// which are caused by MPU access violations.  This handler will verify the
// cause of the fault and clear the NVIC fault status register.
//
void MPUFaultHandler(void)
{
    //
    // Preserve the value of the MMAR (the address causing the fault).
    // Preserve the fault status register value, then clear it.
    //
    memFaultAdd = HWREG(NVIC_BASE + NVIC_O_MMFAR);
    faultStatus = HWREG(NVIC_BASE + NVIC_O_MMSR);
    HWREG(NVIC_BASE + NVIC_O_MMSR) = faultStatus;

    //
    // Increment a counter to indicate the fault occurred.
    //
    faultCount++;

    //
    // Once ISR is executed the execution returns to the instruction that
    // caused the fault and this again leads to another fault.
    // Updating the return address in the stack so that the handler returns
    // to any of the NOP instructions added in the example code.
    // This is being done for demonstration purpose only. The application code
    // should handle the fault as per requirement.
    //
    asm(" ldr r0, [sp, #0x18]");
    asm(" add r0, r0, #4");
    asm(" str r0, [sp, #0x18]");
}

//
// BUSFaultHandler - The exception handler for bus faults. This handler will
// verify the cause of the fault and clear the NVIC fault status register.
//
void BUSFaultHandler(void)
{
    //
    // Preserve the value of the MMAR (the address causing the fault).
    // Preserve the fault status register value, then clear it.
    //
    busFaultAdd = HWREG(NVIC_BASE + NVIC_O_BFAR);
    faultStatus = HWREG(NVIC_BASE + NVIC_O_BFSR);
    HWREG(NVIC_BASE + NVIC_O_BFSR) = faultStatus;

    //
    // Increment a counter to indicate the fault occurred.
    //
    faultCount++;

    //
    // Bus fault ISR returns to the instruction that caused the fault and this
    // this again leads to another fault. Updating the return address in the
    // stack so that the handler returns to the next instruction. Adjust the
    // required return address offset as per requirement.
    // This is being done for demonstration purpose only. The application code
    // should handle the fault as per requirement.
    //
    asm(" ldr r0, [sp, #0x18]");
    asm(" add r0, r0, #4");
    asm(" str r0, [sp, #0x18]");
}

//
// End of File
//
