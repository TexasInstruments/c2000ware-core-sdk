//###########################################################################
//
// FILE:   cpu02_to_cpu01_ipcdrivers_lite_cpu01.c
//
//
// TITLE:  CPU02 to CPU01 IPC Drivers (CPU01) Example
//
//! \addtogroup dual_example_list
//! <h1> CPU02 to CPU01 IPC Lite Drivers (cpu02_to_cpu1_ipcdrivers_lite)</h1>
//!
//! This example application demonstrates the use of CPU02 to CPU01
//! IPC Lite Driver Functions which allow the CPU02 to read/write to
//! addresses on the CPU01. CPU01toCPU02 MSG RAM is used to pass the addresses
//! of local variables between the processors.
//!
//! \b Watch \b Variables \b for \b CPU02: \n
//!  - ErrorCount - Counts # of errors
//!  - usWWord16  - 16-bit word to write to CPU01
//!  - ulWWord32  - 32-bit word to write to CPU01
//!  - usRWord16  - 16-bit word to read from CPU01
//!  - ulRWord32  - 32-bit word to read from CPU01
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
#define CPU01_TO_CPU02_PASSMSG  0x0003FFF4     // CPU01 TO CPU02 MSG RAM
                                               // offsets for passing addresses

//
// Globals
//
volatile uint16_t ErrorFlag;
volatile uint16_t FnCallFlag;

//
// Function Prototypes
//
void Error(void);
void FunctionCallNoReturn(void);
uint32_t FunctionCallReturn(uint32_t ulData);
__interrupt void CPU02toCPU01IPC0IntHandler(void);

//
// Main
//
void main(void)
{
    uint16_t usWWord16;
    uint32_t ulWWord32;
    uint32_t *pulMsgRam;

//
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the F2837xD_SysCtrl.c file.
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
// Initialize the PIE control registers to their default state.
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
    EALLOW; // This is needed to write to EALLOW protected registers
    PieVectTable.IPC0_INT = &CPU02toCPU01IPC0IntHandler;
    EDIS;   // This is needed to disable write to EALLOW protected registers

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
    // No peripheral initialization necessary for this example.

//
// Step 5. User specific code, enable interrupts:
//

//
// Enable CPU INT1 which is connected to CPU01 TO CPU02 IPC INT0-3:
//
    IER |= M_INT1;

    PieCtrlRegs.PIEIER1.bit.INTx13 = 1;  // Enable INTn in the PIE Group 1

//
// Enable global Interrupts and higher priority real-time debug events:
//
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

    ErrorFlag = 0;
    FnCallFlag = 0;
    usWWord16 = 0;
    ulWWord32 = 0;

    EALLOW;
    CpuSysRegs.PCLKCR7.all = 0; // Used as example of a write protected
                                // register that can be written to using IPC
    EDIS;

//
// Write addresses of variables where words should be written to pulMsgRam
// array.
// 0 = Address of 16-bit variable to write into.
// 1 = Address of 32-bit variable to write into.
// 2 = Address of PCLKCR7 register in CPU SYS Regs space to write to.
//    (Write Protected)
// 3 = Address of FnCallNoReturn() function to call.
// 4 = Address of FnCallReturn() function to call.
// 5 = Address of 16-bitFnCallFlag variable to check FnCallNoReturn()
// function.
//
    pulMsgRam = (void *)CPU01_TO_CPU02_PASSMSG;
    pulMsgRam[0] = (uint32_t)&usWWord16;
    pulMsgRam[1] = (uint32_t)&ulWWord32;
    pulMsgRam[2] = (uint32_t)&CpuSysRegs.PCLKCR7.all;
    pulMsgRam[3] = (uint32_t)&FunctionCallNoReturn;
    pulMsgRam[4] = (uint32_t)&FunctionCallReturn;
    pulMsgRam[5] = (uint32_t)&FnCallFlag;

//
// Flag to CPU02 that the variables are ready in MSG RAM with CPU01 TO
// CPU02 IPC Flag 17
//
    IPCLtoRFlagSet(IPC_FLAG17);

//
// Step 6. IDLE loop. Just sit and loop forever (optional):
//
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
// Error - Function to Indicate an Error has Occurred
//        (Invalid Command Received).
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
// FunctionCallNoReturn - Functions run by IPC_FUNC_CALL command
//
void
FunctionCallNoReturn(void)
{
    FnCallFlag = 1;
}

//
// FunctionCallReturn - Return data
//
uint32_t
FunctionCallReturn(uint32_t ulData)
{
    ulData = 2;
    return ulData;
}

//
// CPU02toCPU01IPC0IntHandler - Handles Data Word Reads/Writes
//
__interrupt void
CPU02toCPU01IPC0IntHandler (void)
{
    //
    // Continue processing messages
    //
    uint32_t command;
    command = IpcRegs.IPCRECVCOM;

    switch (command)
    {
        case IPC_SET_BITS_16:
            IPCLiteRtoLSetBits(IPC_FLAG0, IPC_FLAG31);
            break;
        case IPC_SET_BITS_32:
            IPCLiteRtoLSetBits(IPC_FLAG0, IPC_FLAG31);
            break;
        case IPC_CLEAR_BITS_16:
            IPCLiteRtoLClearBits(IPC_FLAG0, IPC_FLAG31);
            break;
        case IPC_CLEAR_BITS_32:
            IPCLiteRtoLClearBits(IPC_FLAG0, IPC_FLAG31);
            break;
        case IPC_DATA_WRITE_16:
            IPCLiteRtoLDataWrite(IPC_FLAG0, IPC_FLAG31);
            break;
        case IPC_DATA_WRITE_32:
            IPCLiteRtoLDataWrite(IPC_FLAG0, IPC_FLAG31);
            break;
        case IPC_SET_BITS_16_PROTECTED:
            IPCLiteRtoLSetBits_Protected(IPC_FLAG0, IPC_FLAG31);
            break;
        case IPC_SET_BITS_32_PROTECTED:
            IPCLiteRtoLSetBits_Protected(IPC_FLAG0, IPC_FLAG31);
            break;
        case IPC_CLEAR_BITS_16_PROTECTED:
            IPCLiteRtoLClearBits_Protected(IPC_FLAG0, IPC_FLAG31);
            break;
        case IPC_CLEAR_BITS_32_PROTECTED:
            IPCLiteRtoLClearBits_Protected(IPC_FLAG0, IPC_FLAG31);
            break;
        case IPC_DATA_WRITE_16_PROTECTED:
            IPCLiteRtoLDataWrite_Protected(IPC_FLAG0, IPC_FLAG31);
            break;
        case IPC_DATA_WRITE_32_PROTECTED:
            IPCLiteRtoLDataWrite_Protected(IPC_FLAG0, IPC_FLAG31);
            break;
        case IPC_DATA_READ_16:
            IPCLiteRtoLDataRead(IPC_FLAG0, IPC_FLAG31);
            break;
        case IPC_DATA_READ_32:
            IPCLiteRtoLDataRead(IPC_FLAG0, IPC_FLAG31);
            break;
        case IPC_FUNC_CALL:
            IPCLiteRtoLFunctionCall(IPC_FLAG0, IPC_FLAG31);
            break;
        default:
            ErrorFlag = 1;
            break;
    }

    //
    // IPC Lite Driver Functions acknowledge the IPC interrupt.
    // There is no need to ACK the IPC interrupt flag separately.
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE
}

//
// End of file
//
