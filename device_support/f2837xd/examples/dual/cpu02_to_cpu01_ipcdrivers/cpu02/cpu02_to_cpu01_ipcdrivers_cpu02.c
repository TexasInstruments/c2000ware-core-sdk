//###########################################################################
//
// FILE:   cpu02_to_cpu01_ipcdrivers_cpu02.c
//
// TITLE:  CPU02 to CPU01 IPC Driver TestExample
//
// This example tests all of the basic read/write CPU02 to CPU01 IPC Driver
// functions available in F2837xD_Ipc_Driver.c.
// The CPU02 project sends commands to the CPU01 project, which then processes
// the commands.
// The CPU01 project responds to the commands sent from the CPU02 project.
// Note that IPC INT0 and IPC INT1 are used for this example to process IPC
// commands.
//
// Watch Variables for CPU02 :
//  ErrorCount - Counts # of errors
//  usCPU02BufferPt  - Stores 256 16-bit words block to write to CPU01
//  pusCPU01BufferPt - Points to beginning of 256 word block received
//                     back from CPU01
//  usWWord16 - 16-bit word to write to CPU01
//  ulWWord32 - 32-bit word to write to CPU01
//  usRWord16 - 16-bit word to read from CPU01
//  ulRWord32 - 32-bit word to read from CPU01
//
// Watch Variables for CPU01 :
//  ErrorFlag - Indicates an unrecognized command was sent from CPU02 to CPU01.
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
#define SETMASK_16BIT         0xFF00         // Mask for setting bits of
                                             // 16-bit word
#define CLEARMASK_16BIT       0xA5A5         // Mask for clearing bits of
                                             // 16-bit word
#define SETMASK_32BIT         0xFFFF0000     // Mask for setting bits of
                                             // 32-bit word
#define CLEARMASK_32BIT       0xA5A5A5A5     // Mask for clearing bits of
                                             // 32-bit word
#define GS0SARAM_START        0xC000         // Start of GS0 SARAM

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
volatile uint16_t ErrorCount;

//
// Global variables used in this example to read/write data passed between
// CPU01 and CPU02
//
uint16_t usWWord16;
uint32_t ulWWord32;
uint16_t usRWord16;
uint32_t ulRWord32;
uint16_t usCPU02Buffer[256];

//
// Function Prototypes
//
void Error(void);
__interrupt void CPU01toCPU02IPC0IntHandler(void);
__interrupt void CPU01toCPU02IPC1IntHandler(void);

//
// Main
//
void
main(void)
{
    uint16_t counter;
    uint16_t *pusCPU01BufferPt;
    uint16_t *pusCPU02BufferPt;
    uint32_t *pulMsgRam ;

//
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the F2837xD_SysCtrl.c file.
//
    // InitSysCtrl();

//
// Step 2. Initialize GPIO:
// This example function is found in the F2837xD_SysCtrl.c file and
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
// The shell ISR routines are found in F2837xD_DefaultISR.c.
// This function is found in F2837xD_PieVect.c.
//
    InitPieVectTable();

//
// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
//
    EALLOW; // This is needed to write to EALLOW protected registers
    PieVectTable.IPC0_INT = &CPU01toCPU02IPC0IntHandler;
    PieVectTable.IPC1_INT = &CPU01toCPU02IPC1IntHandler;
    EDIS;   // This is needed to disable write to EALLOW protected registers

//
// Step 4. Initialize the Device Peripherals:
//
    ErrorFlag = 0;

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
// Enable CPU2 to CPU1 IPC INTn in the PIE: Group 1 interrupts
//
    PieCtrlRegs.PIEIER1.bit.INTx13 = 1;    // CPU2 to CPU1 INT0
    PieCtrlRegs.PIEIER1.bit.INTx14 = 1;    // CPU2 to CPU1 INT1

//
// Enable global Interrupts and higher priority real-time debug events:
//
    EINT;   // Enable Global interrupt INTM
    ERTM;   // Enable Global realtime interrupt DBGM

//
// Initialize local variables
//
    pulMsgRam = (void *)CPU01TOCPU02_PASSMSG;
    pusCPU01BufferPt = (void *)GS0SARAM_START;
    pusCPU02BufferPt = (void *)(GS0SARAM_START + 256);
    ErrorCount = 0;

//
// Initialize all variables used in example.
//
    for(counter = 0; counter < 256; counter++)
    {
        usCPU02Buffer[counter] = ((counter<<8)+(~counter));
    }

    usWWord16 = 0x1234;
    ulWWord32 = 0xABCD5678;
    usRWord16 = 0;
    ulRWord32 = 0;

//
// Spin here until CPU01 has written variable addresses to pulMsgRam
//
    while(IpcRegs.IPCSTS.bit.IPC17 != 1)
    {
    }
    IpcRegs.IPCACK.bit.IPC17 = 1;

//
// 16 and 32-bit Data Writes
//

//
// Write 16-bit word to CPU01 16-bit write word variable.
//
    IPCLtoRDataWrite(&g_sIpcController1, pulMsgRam[0],(uint32_t)usWWord16,
                     IPC_LENGTH_16_BITS, ENABLE_BLOCKING,NO_FLAG);

//
// Read 16-bit word from CPU01 16-bit write word variable. Use IPC Flag 17 to
// check when read data is ready.
//
    IPCLtoRDataRead(&g_sIpcController1, pulMsgRam[0], &usRWord16,
                    IPC_LENGTH_16_BITS, ENABLE_BLOCKING,
                    IPC_FLAG17);

//
// Write 32-bit word to CPU01 32-bit write word variable.
//
    IPCLtoRDataWrite(&g_sIpcController1, pulMsgRam[1],ulWWord32,
                     IPC_LENGTH_32_BITS, ENABLE_BLOCKING, NO_FLAG);

//
// Read 32-bit word from CPU01 32-bit write word variable. Use IPC Flag 18 to
// check when read data is ready.
//
    IPCLtoRDataRead(&g_sIpcController1, pulMsgRam[1], &ulRWord32,
                    IPC_LENGTH_32_BITS, ENABLE_BLOCKING, IPC_FLAG18);

//
// Wait until read variables are ready (by checking IPC Response Flag is
// cleared). Then check Read var = Write var
//
    while(IpcRegs.IPCFLG.bit.IPC17)
    {
    }

    if(usWWord16 != usRWord16)
    {
        ErrorCount++;
    }

    while(IpcRegs.IPCFLG.bit.IPC18)
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
    IPCLtoRSetBits(&g_sIpcController1, pulMsgRam[0],(uint32_t)SETMASK_16BIT,
                   IPC_LENGTH_16_BITS,ENABLE_BLOCKING);

//
// Read 16-bit word from CPU01 16-bit write word variable. Use IPC Flag 17 to
// check when read data is ready.
//
    IPCLtoRDataRead(&g_sIpcController1, pulMsgRam[0], &usRWord16,
                    IPC_LENGTH_16_BITS, ENABLE_BLOCKING,IPC_FLAG17);

//
// Set upper 16 bits in 32-bit write word variable location.
//
    IPCLtoRSetBits(&g_sIpcController1, pulMsgRam[1], SETMASK_32BIT,
                   IPC_LENGTH_32_BITS,ENABLE_BLOCKING);

//
// Read 32-bit word from CPU01 32-bit write word variable. Use IPC Flag 18 to
// check when read data is ready.
//
    IPCLtoRDataRead(&g_sIpcController1, pulMsgRam[1], &ulRWord32,
                    IPC_LENGTH_32_BITS, ENABLE_BLOCKING,IPC_FLAG18);

//
// Wait until read variables are ready (by checking IPC Response Flag is
// cleared). Then check correct bits are set.
//
    while(IpcRegs.IPCFLG.bit.IPC17)
    {
    }

    if(usRWord16 != (usWWord16 | SETMASK_16BIT))
    {
        ErrorCount++;
    }

    while(IpcRegs.IPCFLG.bit.IPC18)
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
    IPCLtoRClearBits(&g_sIpcController1, pulMsgRam[0],(uint32_t)CLEARMASK_16BIT,
                     IPC_LENGTH_16_BITS,ENABLE_BLOCKING);

//
// Read 16-bit word from CPU01 16-bit write word variable. Use IPC Flag 17 to
// check when read data is ready.
//
    IPCLtoRDataRead(&g_sIpcController1, pulMsgRam[0], &usRWord16,
                    IPC_LENGTH_16_BITS, ENABLE_BLOCKING,IPC_FLAG17);

//
// Clear alternating bits in 32-bit write word variable location
//
    IPCLtoRClearBits(&g_sIpcController1, pulMsgRam[1],(uint32_t)CLEARMASK_32BIT,
                     IPC_LENGTH_32_BITS,ENABLE_BLOCKING);

//
// Read 16-bit word from CPU01 32-bit write word variable. Use IPC Flag 18 to
// check when read data is ready.
//
    IPCLtoRDataRead(&g_sIpcController1, pulMsgRam[1], &ulRWord32,
                    IPC_LENGTH_32_BITS, ENABLE_BLOCKING,IPC_FLAG18);

//
// Wait until read variables are ready (by checking IPC Response Flag is
// cleared). Then check correct bits are clear.
//
    while(IpcRegs.IPCFLG.bit.IPC17)
    {
    }

    if(usRWord16 != ((usWWord16 | SETMASK_16BIT) & (~CLEARMASK_16BIT)))
    {
        ErrorCount++;
    }

    while(IpcRegs.IPCFLG.bit.IPC18)
    {
    }

    if(ulRWord32 != ((ulWWord32 | SETMASK_32BIT) & (~CLEARMASK_32BIT)))
    {
        ErrorCount++;
    }

//
// Data Block Writes
//

//
// Request Memory Access to GS0 SARAM for CPU02
// Set bits to let CPU02 own GS0
//
    IPCReqMemAccess(&g_sIpcController2, GS0_ACCESS, IPC_GSX_CPU2_MASTER,
                    ENABLE_BLOCKING);

    while(MemCfgRegs.GSxMSEL.bit.MSEL_GS0 != 1U)
    {
    }

//
// Write a block of data from CPU02 to GS0 shared RAM which is then written to
// an CPU01 address.
//
    for(counter = 0; counter < 256; counter++)
    {
        pusCPU02BufferPt[counter] = usCPU02Buffer[counter];
    }

    IPCLtoRBlockWrite(&g_sIpcController2, pulMsgRam[2],
                      (uint32_t)pusCPU02BufferPt,
                      256, IPC_LENGTH_16_BITS,ENABLE_BLOCKING);

//
// Give Memory Access to GS0 SARAM to CPU02
//
    IPCReqMemAccess(&g_sIpcController2, GS0_ACCESS, IPC_GSX_CPU1_MASTER,
                    ENABLE_BLOCKING);

    IPCLtoRBlockRead(&g_sIpcController2, pulMsgRam[2],
                     (uint32_t)pusCPU01BufferPt,
                     256, ENABLE_BLOCKING,IPC_FLAG17);

//
// Wait until read data is ready (by checking IPC Response Flag is cleared).
// Then check for correct data.
//
    while(IpcRegs.IPCFLG.bit.IPC17)
    {
    }

    for(counter = 0; counter <256; counter++)
    {
        if(usCPU02Buffer[counter] != pusCPU01BufferPt[counter])
        {
            ErrorFlag = 1;
        }
    }

    if(ErrorFlag == 1)
    {
        ErrorCount++;
    }
//
// Check Function Call Function
//

//
// Call FunctionCall() function on CPU01 with a dummy parameter of "0"(i.e. no
// parameter).
//
    IPCLtoRFunctionCall(&g_sIpcController1, pulMsgRam[3], 0, ENABLE_BLOCKING);

//
// Read status variable to check if function was entered. Use IPC Flag 17 to
// check when read data is ready.
//
    IPCLtoRDataRead(&g_sIpcController1, pulMsgRam[5], &usRWord16,
                    IPC_LENGTH_16_BITS, ENABLE_BLOCKING,IPC_FLAG17);

//
// Call FunctionCall() function on CPU01 with a parameter of "0x12345678".
//
    IPCLtoRFunctionCall(&g_sIpcController1, pulMsgRam[4], 0x12345678,
                        ENABLE_BLOCKING);

//
// Read status variable to check if function was entered. Use IPC Flag 18 to
// check when read data is ready.
//
    IPCLtoRDataRead(&g_sIpcController1, pulMsgRam[5], &ulRWord32,
                    IPC_LENGTH_32_BITS, ENABLE_BLOCKING,IPC_FLAG18);

//
// Wait until read data is ready (by checking IPC Response Flag is cleared).
// Then check status
// variables to see if function was entered.
//
    while(IpcRegs.IPCFLG.bit.IPC17)
    {
    }

    if(usRWord16 != 1)
    {
        ErrorCount++;
    }

    while(IpcRegs.IPCFLG.bit.IPC18)
    {
    }

    if(ulRWord32 != 0x12345678)
    {
        ErrorCount++;
    }

    if(ErrorCount != 0)
    {
        ESTOP0;
    }

    for(;;)
    {
        //
        // When Complete, Loop Forever here.
        //
    }
}

//
// CPU01toCPU02IPC0IntHandler - Handles writes into CPU01 addresses as a
//                              result of read commands to the CPU02.
//
__interrupt void CPU01toCPU02IPC0IntHandler (void)
{
    tIpcMessage sMessage;

    //
    // Continue processing messages as long as CPU01 to CPU02
    // GetBuffer1 is full
    //
    while(IpcGet(&g_sIpcController1, &sMessage,
                 DISABLE_BLOCKING) != STATUS_FAIL)
    {
        switch (sMessage.ulcommand)
        {
            case IPC_DATA_WRITE:
                IPCRtoLDataWrite(&sMessage);
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
// CPU01toCPU02IPC1IntHandler - Should never reach this ISR. This is an
//                              optional placeholder for g_sIpcController2.
//
__interrupt void CPU01toCPU02IPC1IntHandler(void)
{
    //
    // Should never reach here - Placeholder for Debug
    //
    // Acknowledge IPC INT1 Flag and PIE to receive more interrupts
    //
    IpcRegs.IPCACK.bit.IPC1 = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

//
// End of file
//
