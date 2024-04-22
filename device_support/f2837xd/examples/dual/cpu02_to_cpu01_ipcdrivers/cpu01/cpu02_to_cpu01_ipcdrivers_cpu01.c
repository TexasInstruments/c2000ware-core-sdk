//###########################################################################
//
// FILE:   cpu01_to_cpu02_ipcdrivers_cpu01.c
//
// TITLE:  CPU01 to CPU02 IPC Driver TestExample(CPU01) Example
//
//! \addtogroup dual_example_list
//! <h1> CPU02 to CPU01 IPC Driver </h1>
//!
//! This example tests all of the basic read/write CPU02 to CPU01 IPC Driver
//! functions available in F2837xD_Ipc_Driver.c.
//! The CPU02 project sends commands to the CPU01 project, which then processes
//! the commands.
//! The CPU01 project responds to the commands sent from the CPU02 project.
//! Note that IPC INT0 and IPC INT1 are used for this example to process IPC
//! commands.
//!
//! \b  Watch \b Variables \b for \b CPU02 : \n
//!  - ErrorCount - Counts # of errors
//!  - usCPU02Buffer  - Stores 256 16-bit words block to write to CPU01
//!  - pusCPU01BufferPt - Points to beginning of 256 word block received
//!                       back from CPU01
//!  - usWWord16 - 16-bit word to write to CPU01
//!  - ulWWord32 - 32-bit word to write to CPU01
//!  - usRWord16 - 16-bit word to read from CPU01
//!  - ulRWord32 - 32-bit word to read from CPU01
//!
//! \b  Watch \b Variables \b for \b CPU01 : \n
//!  - ErrorFlag  - Indicates an unrecognized command was sent from
//!                 CPU02 to CPU01.
//!
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
#define CPU01TOCPU02_PASSMSG  0x0003FFF4     // CPU01 to CPU02 MSG RAM offsets
                                             // for passing address

//
// Globals
//

//
// At least 1 volatile global tIpcController instance is required when using
// IPC API Drivers.
//
volatile tIpcController g_sIpcController1;
volatile tIpcController g_sIpcController2;

//
// Global variable used in this example to track errors
//
volatile uint16_t ErrorFlag;
volatile uint32_t FnCallStatus;

//
// Global variables used in this example to read/write data passed between
// CPU01 and CPU02
//
uint16_t usWWord16;
uint32_t ulWWord32;
uint16_t usCPU01Buffer[256];

//
// Function Prototypes
//
__interrupt void CPU02toCPU01IPC0IntHandler(void);
__interrupt void CPU02toCPU01IPC1IntHandler(void);
void FunctionCall(void);
void FunctionCallParam(uint32_t ulParam);
void Error(void);

//
// Main
//
void
main(void)
{
    uint32_t *pulMsgRam;
    uint16_t counter;

//
// Step 1. Initialize System Control (Performed by CPU01):
// PLL, WatchDog, enable Peripheral Clocks
//
   InitSysCtrl();

//
// Step 2. Initialize GPIO:
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
// The shell ISR routines are found in F2837xD_DefaultISR.c.
// This function is found in F2837xD_PieVect.c.
//
    InitPieVectTable();

//
// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
//
    EALLOW;  // This is needed to write to EALLOW protected registers
    PieVectTable.IPC0_INT = &CPU02toCPU01IPC0IntHandler;
    PieVectTable.IPC1_INT = &CPU02toCPU01IPC1IntHandler;
    EDIS;    // This is needed to disable write to EALLOW protected registers

#ifdef _STANDALONE
#ifdef _FLASH
    //
    //  Send boot command to allow the CPU02 application to begin execution
    //
    IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_FLASH);
#else
    //
    //  Send boot command to allow the CPU02 application to begin execution
    //
    IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_RAM);
#endif
#endif

//
// Step 4. Initialize the Device Peripherals:
//
    IPCInitialize(&g_sIpcController1, IPC_INT0, IPC_INT0);
    IPCInitialize(&g_sIpcController2, IPC_INT1, IPC_INT1);

//
// Step 5. User specific code, enable interrupts:
//

//
// Enable CPU INT1 which is connected to Upper PIE IPC INT0-3:
//
    IER |= M_INT1;

//
// Enable CPU01 to CPU02 INTn in the PIE: Group 11 interrupts
//
    PieCtrlRegs.PIEIER1.bit.INTx13 = 1;   // CPU1 to CPU2 INT0
    PieCtrlRegs.PIEIER1.bit.INTx14 = 1;   // CPU1 to CPU2 INT0

//
// Enable global Interrupts and higher priority real-time debug events:
//
    EINT;   // Enable Global interrupt INTM
    ERTM;   // Enable Global realtime interrupt DBGM

    ErrorFlag = 0;
    FnCallStatus = 0;
    usWWord16 = 0;
    ulWWord32 = 0;
    for(counter = 0; counter < 256; counter++)
    {
        usCPU01Buffer[counter] = 0;
    }

//
// Point array to address in CPU02 TO CPU01 MSGRAM for passing
// variable locations
//
    pulMsgRam = (void *)CPU01TOCPU02_PASSMSG;

//
// Write addresses of variables where words should be written to pulMsgRam
// array.
// 0 = Address of 16-bit word to write to.
// 1 = Address of 32-bit word to write to.
// 2 = Address of buffer to block write to.
// 3 = Address of FunctionCall() function to call.
// 4 = Address of FunctionCallParam() function to call.
// 5 = Address of 32-bit FnCallStatus variable to check function call
// executed
//
    pulMsgRam[0] = (uint32_t)&usWWord16;
    pulMsgRam[1] = (uint32_t)&ulWWord32;
    pulMsgRam[2] = (uint32_t)&usCPU01Buffer[0];
    pulMsgRam[3] = (uint32_t)&FunctionCall;
    pulMsgRam[4] = (uint32_t)&FunctionCallParam;
    pulMsgRam[5] = (uint32_t)&FnCallStatus;

//
// Flag to CPU01 that the variables are ready in MSG RAM with CPU02 TO
// CPU01 IPC Flag 17
//
    IpcRegs.IPCSET.bit.IPC17 = 1;

    for(;;)
    {
        //
        // Flag an Error if an Invalid Command has been received.
        //
        if(ErrorFlag == 1)
        {
            Error();
        }
    }
}

//
// FunctionCall - Function run by IPC_FUNC_CALL command
//
void
FunctionCall(void)
{
    FnCallStatus = 1;
}

//
// FunctionCallParam - Set status param
//
void
FunctionCallParam(uint32_t ulParam)
{
    FnCallStatus = ulParam;
}

//
// Error - Function to Indicate an Error has Occurred
//         (Invalid Command Received).
//
void
Error(void)
{
    //
    // An error has occurred (invalid command received). Loop forever.
    //
    for (;;)
    {
    }
}

//
// CPU02toCPU01IPC0IntHandler - Handles Data Word Reads/Writes
//
__interrupt void
CPU02toCPU01IPC0IntHandler(void)
{
    tIpcMessage sMessage;

    //
    // Continue processing messages as long as CPU02toCPU01 GetBuffer1 is full
    //
    while(IpcGet(&g_sIpcController1, &sMessage,
                 DISABLE_BLOCKING)!= STATUS_FAIL)
    {
        switch (sMessage.ulcommand)
        {
            case IPC_SET_BITS:
                 IPCRtoLSetBits(&sMessage);
                 break;
            case IPC_CLEAR_BITS:
                IPCRtoLClearBits(&sMessage);
                break;
            case IPC_DATA_WRITE:
                IPCRtoLDataWrite(&sMessage);
                break;
            case IPC_DATA_READ:
                IPCRtoLDataRead(&g_sIpcController1, &sMessage,
                                ENABLE_BLOCKING);
                break;
            case IPC_FUNC_CALL:
                IPCRtoLFunctionCall(&sMessage);
                break;
            default:
                ErrorFlag = 1;
                break;
        }
    }

    //
    // Acknowledge IPC INT0 Flag and PIE to receive more interrupts
    //
    IpcRegs.IPCACK.bit.IPC0 = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

//
// CPU02toCPU01IPC1IntHandler - Handles Data Block Reads/Writes
//
__interrupt void
CPU02toCPU01IPC1IntHandler (void)
{
    tIpcMessage sMessage;

    //
    // Continue processing messages as long as CPU02toCPU01 GetBuffer2 is full
    //
    while(IpcGet(&g_sIpcController2, &sMessage,
                 DISABLE_BLOCKING)!= STATUS_FAIL)
    {
        switch (sMessage.ulcommand)
        {
            case IPC_SET_BITS_PROTECTED:
                IPCRtoLSetBits_Protected(&sMessage);       // Processes
                                                           // IPCReqMemAccess()
                                                           // function
                break;
            case IPC_CLEAR_BITS_PROTECTED:
                IPCRtoLClearBits_Protected(&sMessage);     // Processes
                                                           // IPCReqMemAccess()
                                                           // function
                break;
            case IPC_BLOCK_WRITE:
                IPCRtoLBlockWrite(&sMessage);
                break;
            case IPC_BLOCK_READ:
                IPCRtoLBlockRead(&sMessage);
                break;
            default:
                ErrorFlag = 1;
                break;
        }
    }

    //
    // Acknowledge IPC INT1 Flag and PIE to receive more interrupts
    //
    IpcRegs.IPCACK.bit.IPC1 = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

//
// End of file
//
