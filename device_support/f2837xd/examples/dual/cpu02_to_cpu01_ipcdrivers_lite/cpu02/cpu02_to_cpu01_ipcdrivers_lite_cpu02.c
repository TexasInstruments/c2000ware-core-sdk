//###########################################################################
//
// FILE:   cpu02_to_cpu01_ipcdrivers_lite_cpu02.c
//
// TITLE:  F2837xD CPU02 to CPU01 IPC LiteDrivers Test Example
//
// ASSUMPTIONS:
//   This program requires the F2837xD header files.
//   As supplied, this project is configured for "boot to SARAM"
//   operation.
//
// DESCRIPTION:
//   This example tests the basic read/write CPU02 to CPU01 IPC Lite Driver
//   functions available in F28X7_IpcDriver_Lite.c. The CPU02 project sends
//   commands to the CPU01 project, which then processes the commands. MtoC
//   MSG RAM is used to pass the addresses of local variables between
//   the processors.
//
// Watch Variables:
//   ErrorCount - Counts # of errors
//   usWWord16  - 16-bit word to write to CPU01
//   ulWWord32  - 32-bit word to write to CPU01
//   usRWord16  - 16-bit word to read from CPU01
//   ulRWord32  - 32-bit word to read from CPU01
//
//###########################################################################
//
// $Release Date:  $
// $Copyright:
// Copyright (C) 2013-2024 Texas Instruments Incorporated - http://www.ti.com/
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
// Included Files
//
#include "F28x_Project.h"
#include "F2837xD_Ipc_drivers.h"

//
// Defines
//
#define CPU01_TO_CPU02_PASSMSG  0x0003FFF4      // Used by CPU01 to pass
                                                // address of local variables
                                                // to perform actions on
#define SETMASK_16BIT           0xFF00          // Mask for setting bits of
                                                // 16-bit word
#define CLEARMASK_16BIT         0xA5A5          // Mask for clearing bits of
                                                // 16-bit word
#define SETMASK_32BIT           0xFFFF0000      // Mask for setting bits of
                                                // 32-bit word
#define CLEARMASK_32BIT         0xA5A5A5A5      // Mask for clearing bits of
                                                // 32-bit word

//
// Globals
//
volatile uint16_t ErrorFlag;

//
// Main
//
void
main(void)
{
    uint16_t ErrorCount = 0;
    uint16_t usWWord16;
    uint32_t ulWWord32;
    uint16_t usRWord16;
    uint32_t ulRWord32;
    uint32_t *pulMsgRam = (void *)CPU01_TO_CPU02_PASSMSG;

//
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the F2837xD_SysCtrl.c file.
//
   // InitSysCtrl();

//
// Step 2. Initialize GPIO:
// This example function is found in the F2837xD__Gpio.c file and
// illustrates how to set the GPIO to it's default state.
//
// InitGpio();  // Skipped for this example

//
// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
//
    DINT;

//
// Initialize PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the F2837xD_PieCtrl.c file.
//
    InitPieCtrl();

//
// Disable CPU interrupts and clear all CPU interrupt flags:
//
    IER = 0x0000;
    IFR = 0x0000;

//
// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in F2837xD_DefaultIsr.c.
// This function is found in F2837xD_PieVect.c.
//
    InitPieVectTable();

//
// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
//
    // No interrupts are enabled for this example.

//
// Step 4. Initialize the Device Peripherals:
//
    // No peripheral initialization necessary for this example.

//
// Step 5. User specific code, enable interrupts:
//
    // No interrupts are enabled for this example.

    ErrorFlag = 0;
    usWWord16 = 0x1234;
    ulWWord32 = 0xABCD5678;
    usRWord16 = 0;
    ulRWord32 = 0;

//
// Spin here until CPU01 is ready
//
    while(!IPCRtoLFlagBusy(IPC_FLAG17));
    IPCRtoLFlagAcknowledge(IPC_FLAG17);

//
// 16 and 32-bit Data Writes
//

//
// Write 16-bit word to CPU01 16-bit write word variable.
//
    IPCLiteLtoRDataWrite(IPC_FLAG0, pulMsgRam[0],(uint32_t)usWWord16,
                         IPC_LENGTH_16_BITS, IPC_FLAG31);

//
// Optionally Get result of the Write (i.e. read word that was written at
// address) without
// performing a separate read command. IPCLiteLtoRGetResult() will return
// STATUS_FAIL if
// the CPU01 did not recognize the command being sent, and therefore did not
// process the
// command. Otherwise it will return STATUS_PASS and the appropriate read
// value.
//
    while(IPCLiteLtoRGetResult(&usRWord16,IPC_LENGTH_16_BITS,
                               IPC_FLAG31) != STATUS_PASS)
    {
    }

    if(usWWord16 != usRWord16)
    {
        ErrorCount++;
    }

    usRWord16 = 0;

//
// OR Read 16-bit word from CPU01 16-bit write word variable. Use IPC Flag 32
// to check status of command.
// Notice that the command function is in a while-loop. All command
// functions will return STATUS_FAIL if
// the IPC interrupt ulFlag is still busy, and subsequently, will not send
// the command to the CPU01.  If
// the IPC interrupt ulFlag is available, the command will be sent, and the
// function will return STATUS_PASS.
//
    while(IPCLiteLtoRDataRead(IPC_FLAG0, pulMsgRam[0], IPC_LENGTH_16_BITS,
                              IPC_FLAG31) != STATUS_PASS)
    {
    }

//
// Result of Read will be read into usRWord16 variable.
//
    while(IPCLiteLtoRGetResult(&usRWord16,IPC_LENGTH_16_BITS,
                               IPC_FLAG31) != STATUS_PASS)
    {
    }

    if(usWWord16 != usRWord16)
    {
        ErrorCount++;
    }

//
// Write 32-bit word to CPU01 32-bit write word variable.
//
    while(IPCLiteLtoRDataWrite(IPC_FLAG0, pulMsgRam[1],ulWWord32,
                               IPC_LENGTH_32_BITS,  IPC_FLAG31) != STATUS_PASS)
    {
    }

//
// Optionally Get result of the Write (i.e. read word that was written at
// address) without performing a separate read command.
//
    while(IPCLiteLtoRGetResult(&ulRWord32,IPC_LENGTH_32_BITS,
                               IPC_FLAG31) != STATUS_PASS)
    {
    }

    if(ulWWord32 != ulRWord32)
    {
        ErrorCount++;
    }

    ulRWord32 = 0;

//
// Read 32-bit word from CPU01 32-bit write word variable. Use IPC Flag 32 to
// check status of command
//
    IPCLiteLtoRDataRead(IPC_FLAG0, pulMsgRam[1], IPC_LENGTH_32_BITS,
                        IPC_FLAG31);

//
// Result of Read will be read into ulRWord32 variable.
//
    while(IPCLiteLtoRGetResult(&ulRWord32,IPC_LENGTH_32_BITS,
                               IPC_FLAG31) != STATUS_PASS)
    {
    }

    if(ulWWord32 != ulRWord32)
    {
        ErrorCount++;
    }

//
// 16 and 32-bit Data Set Bits
// Set upper 8 bits in 16-bit write word variable location.
//
    IPCLiteLtoRSetBits(IPC_FLAG0, pulMsgRam[0], SETMASK_16BIT,
                       IPC_LENGTH_16_BITS, IPC_FLAG31);

//
// Optionally Get result of the Write (i.e. read word that was written at
// address) without performing a separate read command.
//
    while(IPCLiteLtoRGetResult(&usRWord16,IPC_LENGTH_16_BITS,
                               IPC_FLAG31) != STATUS_PASS)
    {
    }

    if(usRWord16 != (usWWord16 | SETMASK_16BIT))
    {
        ErrorCount++;
    }

//
// Set upper 16 bits in 32-bit write word variable location.
//
    IPCLiteLtoRSetBits(IPC_FLAG0, pulMsgRam[1], SETMASK_32BIT,
                       IPC_LENGTH_32_BITS, IPC_FLAG31);

//
// Optionally Get result of the Write (i.e. read word that was written at
// address) without performing a separate read command.
//
    while(IPCLiteLtoRGetResult(&ulRWord32,IPC_LENGTH_32_BITS,
                               IPC_FLAG31) != STATUS_PASS)
    {
    }

    if(ulRWord32 != (ulWWord32 | SETMASK_32BIT))
    {
        ErrorCount++;
    }

//
// 16 and 32-bit Data Clear Bits
// Clear alternating bits in 16-bit write word variable location
//
    IPCLiteLtoRClearBits(IPC_FLAG0, pulMsgRam[0], CLEARMASK_16BIT,
                         IPC_LENGTH_16_BITS, IPC_FLAG31);

//
// Optionally Get result of the Write (i.e. read word that was written at
// address) without performing a separate read command.
//
    while(IPCLiteLtoRGetResult(&usRWord16,IPC_LENGTH_16_BITS,
                               IPC_FLAG31) != STATUS_PASS)
    {
    }

    if(usRWord16 != ((usWWord16 | SETMASK_16BIT) & (~CLEARMASK_16BIT)))
    {
        ErrorCount++;
    }

//
// Clear alternating bits in 32-bit write word variable location
//
    IPCLiteLtoRClearBits(IPC_FLAG0, pulMsgRam[1], CLEARMASK_32BIT,
                         IPC_LENGTH_32_BITS, IPC_FLAG31);

//
// Optionally Get result of the Write (i.e. read word that was written at
// address) without performing a separate read command.
//
    while(IPCLiteLtoRGetResult(&ulRWord32,IPC_LENGTH_32_BITS,
                               IPC_FLAG31) != STATUS_PASS)
    {
    }

    if(ulRWord32 != ((ulWWord32 | SETMASK_32BIT) & (~CLEARMASK_32BIT)))
    {
        ErrorCount++;
    }

//
// Check Request Memory Access Function (and Set Bits/Clear Bits Protected
// functions)
//
// Request Memory Access to GS0 SARAM for CPU02 (Invokes
// IPCLtoRSetBits_Protected() function)
//
    IPCLiteReqMemAccess(IPC_FLAG0, GS0_ACCESS, IPC_GSX_CPU2_MASTER,
                        IPC_FLAG31);
    while((MemCfgRegs.GSxMSEL.all & GS0_ACCESS) != GS0_ACCESS)
    {
    }

//
// Result of ReqmemAccess will be read into ulRWord32 variable.
//
    while(IPCLiteLtoRGetResult(&ulRWord32,IPC_LENGTH_32_BITS,
                               IPC_FLAG31) != STATUS_PASS)
    {
    }

    if((ulRWord32 & GS0_ACCESS) != GS0_ACCESS)
    {
        ErrorCount++;
    }

//
// Return Memory Access to GS0 SARAM to CPU01 (Invokes
// IPCCtoMClearBits_Protected() function)
//
    IPCLiteReqMemAccess(IPC_FLAG0, GS0_ACCESS, IPC_GSX_CPU1_MASTER,
                        IPC_FLAG31);

    while((MemCfgRegs.GSxMSEL.all & GS0_ACCESS) != 0)
    {
    }

//
// Result of ReqmemAccess will be read into ulRWord32 variable.
//
    while(IPCLiteLtoRGetResult(&ulRWord32,IPC_LENGTH_32_BITS,
                               IPC_FLAG31) != STATUS_PASS)
    {
    }

    if((ulRWord32 & GS0_ACCESS) != 0)
    {
        ErrorCount++;
    }

//
// Check Data Write Protected Function
//

//
// Write to write-protected CPU01 PCLKCR0 register
//
    IPCLiteLtoRDataWrite_Protected(IPC_FLAG0, pulMsgRam[2], 0x000A,
                                   IPC_LENGTH_32_BITS, IPC_FLAG31);

//
// Result of write will be read into ulRWord32 variable.
//
    while(IPCLiteLtoRGetResult(&ulRWord32, IPC_LENGTH_32_BITS,
                               IPC_FLAG31) != STATUS_PASS)
    {
    }

    if(ulRWord32 != 0x000A)
    {
        ErrorCount++;
    }

//
// Check Function Call Function
//

//
// Call FunctionCallNoReturn() function on CPU01 with a dummy parameter of "0".
//
    IPCLiteLtoRFunctionCall(IPC_FLAG0, pulMsgRam[3], 0, IPC_FLAG31);

//
// When IPC_FLAG0 is ready, Read FnCallFlag to see if FunctionCallNoReturn()
// was called and executed properly.
//
    while(IPCLiteLtoRDataRead(IPC_FLAG0, pulMsgRam[5], IPC_LENGTH_16_BITS,
                              IPC_FLAG31) != STATUS_PASS) ;

//
// Result of Read will be read into usRWord16 variable.
//
    while(IPCLiteLtoRGetResult(&usRWord16,IPC_LENGTH_16_BITS,
                               IPC_FLAG31) != STATUS_PASS)
    {
    }

    if(usRWord16 != 1 )
    {
        ErrorCount++;
    }

//
// Call FunctionCallReturn() function on CPU01 with a parameter of 0x12345678.
//
    IPCLiteLtoRFunctionCall(IPC_FLAG0, pulMsgRam[4], 0x12345678, IPC_FLAG31);

//
// Return value from function call will be read into ulRWord32 variable.
//
    while(IPCLiteLtoRGetResult(&ulRWord32,IPC_LENGTH_32_BITS,
                               IPC_FLAG31) != STATUS_PASS)
    {
    }

    if(ulRWord32 != 2)
    {
        ErrorCount++;
    }

    for(;;)
    {
        //
        // When Complete, Loop Forever here.
        //
    }
}

//
// End of file
//
