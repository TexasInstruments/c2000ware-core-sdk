//###########################################################################
//
// FILE:   cpu01_to_cpu02_ipcdrivers_wprotect_cpu02.c
//
// TITLE:  CPU01 to CPU02 IPC Write Protect Driver TestExample
//
// ASSUMPTIONS:
//    This program requires the 2837xD header files.
//    As supplied, this project is configured for "boot to SARAM"
//    operation.
//
// DESCRIPTION:
//   This example tests all of the basic read/write  IPC Driver functions
//   which access write-protected addresses available in F2837xD_Ipc_Driver.c
//   The CPU02 project responds to the commands sent from the CPU01 project.
//   Note that IPC INT0 and IPC INT1 are used for this example to process
//   IPC commands.
//
// Watch Variables:
//   ErrorFlag  - Indicates an unrecognized command was sent from
//                CPU01 to CPU02.
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
#define CPU02TOCPU01_PASSMSG   0x0003FBF0        // Used by CPU02 to pass
                                                 // addresses of local variables
                                                 // to perform actions on
#define SET_PCLKCR7            0x00000001        // Value to read into 32-bits
                                                 // of PCLKCR7 register
#define SET_PCLKCR8            0x00010002        // Value to read into 32-bits
                                                 // of PCLKCR8 register

//
// Globals
//
volatile tIpcController g_sIpcController1;
volatile tIpcController g_sIpcController2;
volatile Uint16 ErrorFlag;

//
// Function Prototypes
//
__interrupt void CPU01toCPU02IPC0IntHandler(void);
__interrupt void CPU01toCPU02IPC1IntHandler(void);
void Error (void);

//
// Main
//
void
main(void)
{
    uint32_t *pulMsgRam;
    uint32_t ulPeripheral1Clkset = SET_PCLKCR7;
    uint32_t ulPeripheral2Clkset = SET_PCLKCR8;

//
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the F2837xD_SysCtrl.c file.
//
   // InitSysCtrl();

//
// Step 2. Initialize GPIO:
// This example function is found in the F2837xD_Gpio.c file and
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
    EALLOW;  // This is needed to write to EALLOW protected registers
    PieVectTable.IPC0_INT = &CPU01toCPU02IPC0IntHandler;
    PieVectTable.IPC1_INT = &CPU01toCPU02IPC1IntHandler;
    EDIS;    // This is needed to disable write to EALLOW protected registers

//
// Step 4. Initialize the Device Peripherals:
//
    ErrorFlag = 0;
    IPCInitialize (&g_sIpcController1, IPC_INT0, IPC_INT0);
    IPCInitialize (&g_sIpcController2, IPC_INT1, IPC_INT1);

//
// Step 5. User specific code, enable interrupts:
//

//
// Enable CPU INT1 which is connected to Upper PIE IPC INT0-3:
//
    IER |= M_INT1;

//
// Enable MTOCIPC INTn in the PIE: Group 11 interrupts
//
    PieCtrlRegs.PIEIER1.bit.INTx13 = 1;     // CPU01 to CPU02  IPC INT0
    PieCtrlRegs.PIEIER1.bit.INTx14 = 1;     // CPU01 to CPU02  IPC INT0

//
// Enable global Interrupts and higher priority real-time debug events:
//
    EINT;   // Enable Global interrupt INTM
    ERTM;   // Enable Global realtime interrupt DBGM

//
// Write addresses of variables where words should be written to pulMsgRam
// array.
// 0 = Address of PCLKCR9 register
// 1 = Address of PCLKCR10 register
// 2 = Address of PCLKCR11 registers
// 3 = Address of PCLKCR12 registers
// 4 = Address of variable with value which will be read into 32-bit address.
//
    pulMsgRam = (void *)CPU02TOCPU01_PASSMSG;
    pulMsgRam[0] = (uint32_t)&CpuSysRegs.PCLKCR7;
    pulMsgRam[1] = (uint32_t)&CpuSysRegs.PCLKCR8;
    pulMsgRam[2] = (uint32_t)&CpuSysRegs.PCLKCR9;
    pulMsgRam[3] = (uint32_t)&ulPeripheral1Clkset;
    pulMsgRam[4] = (uint32_t)&ulPeripheral2Clkset;

//
// Flag to CPU01 that the variables are ready in MSG RAM with IPC Flag 17
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
    // Continue processing messages as long as CPU02 to CPU01 GetBuffer1
    // is full
    //
    while(IpcGet (&g_sIpcController1, &sMessage,
                  DISABLE_BLOCKING)!= STATUS_FAIL)
    {
        switch (sMessage.ulcommand)
        {
            case IPC_SET_BITS_PROTECTED:
                IPCRtoLSetBits_Protected(&sMessage);
                break;
            case IPC_CLEAR_BITS_PROTECTED:
                IPCRtoLClearBits_Protected(&sMessage);
                break;
            case IPC_DATA_WRITE_PROTECTED:
                IPCRtoLDataWrite_Protected(&sMessage);
                break;
            case IPC_DATA_READ:
                IPCRtoLDataRead(&g_sIpcController1, &sMessage, ENABLE_BLOCKING);
                break;
            case IPC_DATA_READ_PROTECTED:
                IPCRtoLDataRead_Protected(&g_sIpcController1, &sMessage,
                                          ENABLE_BLOCKING);
                break;
            default:
                ErrorFlag = 1;
                break;
        }
    }

    //
    // Acknowledge IPC INT0 Flag and PIE to receive more interrupts from group
    // 11
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
    // Continue processing messages as long as CPU02 to CPU01 GetBuffer2
    // is full
    //
    while(IpcGet (&g_sIpcController2, &sMessage,
                  DISABLE_BLOCKING)!= STATUS_FAIL)
    {
        switch (sMessage.ulcommand)
        {

           case IPC_BLOCK_WRITE_PROTECTED:
               IPCRtoLBlockWrite_Protected(&sMessage);
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
    // Acknowledge IPC INT1 Flag and PIE to receive more interrupts from group
    // 11
    //
    IpcRegs.IPCACK.bit.IPC1 = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

//
// End of file
//
