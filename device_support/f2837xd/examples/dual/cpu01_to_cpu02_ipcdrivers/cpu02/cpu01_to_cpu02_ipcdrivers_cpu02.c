//###########################################################################
//
// FILE:   cpu01_to_cpu02_ipcdrivers_cpu02.c
//
// TITLE:  CPU01 to CPU02 IPC Driver TestExample(CPU02) Example
//
// This example tests all of the basic read/write CPU01toCPU02 IPC Driver
// functions available in F2837xD_Ipc_Driver.c
//
// The CPU02 project responds to the commands sent from the CPU01 project.
// Note that IPC INT0 and IPC INT1 are used for this example to process
// IPC commands.
//
// Watch Variables:
//    - ErrorFlag - Indicates an unrecognized command was sent from
//                  CPU01 to CPU02.
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
#define CPU02TOCPU01_PASSMSG  0x0003FBF4    // Used by CPU02 to pass address
                                            // of local variables to perform
                                            // actions on

//
// Globals
//

//
// At least 1 volatile global tIpcController instance is required when using
// IPC API Drivers.
//
volatile tIpcController g_sIpcController1;
volatile tIpcController g_sIpcController2;

volatile uint16_t ErrorFlag;
volatile uint32_t FnCallStatus;

//
// Global variables used in this example to read/write data passed between
// CPU01 and CPU02
//
uint16_t usWWord16;
uint32_t ulWWord32;
uint16_t usCPU02Buffer[256];

//
// Function Prototypes
//
__interrupt void CPU01toCPU02IPC0IntHandler(void);
__interrupt void CPU01toCPU02IPC1IntHandler(void);
void FunctionCall(void);
void FunctionCallParam(uint32_t ulParam);
void Error (void);

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
//  InitSysCtrl();

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
    PieVectTable.IPC0_INT = &CPU01toCPU02IPC0IntHandler;
    PieVectTable.IPC1_INT = &CPU01toCPU02IPC1IntHandler;
    EDIS;    // This is needed to disable write to EALLOW protected registers

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
    PieCtrlRegs.PIEIER1.bit.INTx14 = 1;   // CPU1 to CPU2 INT1

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
        usCPU02Buffer[counter] = 0;
    }

//
// Point array to address in CPU02 TO CPU01 MSGRAM for passing
// variable locations
//
    pulMsgRam = (void *)CPU02TOCPU01_PASSMSG;

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
    pulMsgRam[2] = (uint32_t)&usCPU02Buffer[0];
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
        if (ErrorFlag == 1)
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
// FunctionCallParam - Set the call status param
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
// CPU01toCPU02IPC0IntHandler - Handles Data Word Reads/Writes
//
__interrupt void
CPU01toCPU02IPC0IntHandler (void)
{
    tIpcMessage sMessage;

    //
    // Continue processing messages as long as CPU01toCPU02 GetBuffer1 is full
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
// CPU01toCPU02IPC1IntHandler - Handles Data Block Reads/Writes
//
__interrupt void
CPU01toCPU02IPC1IntHandler (void)
{
    tIpcMessage sMessage;

    //
    // Continue processing messages as long as CPU01toCPU02 GetBuffer2 is full
    //
    while(IpcGet(&g_sIpcController2, &sMessage,
                 DISABLE_BLOCKING)!= STATUS_FAIL)
    {
        switch (sMessage.ulcommand)
        {
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
