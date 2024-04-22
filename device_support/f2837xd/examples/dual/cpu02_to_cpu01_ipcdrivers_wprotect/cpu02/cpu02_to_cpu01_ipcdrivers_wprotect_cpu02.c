//###########################################################################
//
// FILE:   cpu02_to_cpu01_ipcdrivers_wprotect_cpu02.c
//
// TITLE:  CPU02 to CPU01 IPC Write Protect Driver TestExample
//
//
// This example tests all of the basic read/write CPU02 to CPU01 IPC Write
// Protect Driver functions available in F2837xD_Ipc_Driver.c.
// The CPU02 project sends commands to the CPU01 project, which then processes
// the commands.
// The CPU01 project responds to the commands sent from the CPU02 project.
// Note that IPC INT0 and IPC INT1 are used for this example to process IPC
// commands.
//
// \b  Watch \b Variables \b for \b CPU02 :
//  ErrorCount - Counts # of errors
//  ulCPU02Buffer    - Stores 4 32-bit words block to write to CPU01
//  pulCPU01BufferPt - Points to beginning of 256 word block received back
//                     from CPU01
//  usWWord16 - 16-bit word to write to CPU01
//  ulWWord32 - 32-bit word to write to CPU01
//  usRWord16 - 16-bit word to read from CPU01
//  ulRWord32 - 32-bit word to read from CPU01
//
// \b  Watch \b Variables \b for \b CPU01 :
//  ErrorFlag - Indicates an unrecognized command was sent from CPU01 to CPU02.
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
#define CPU01TOCPU02_PASSMSG  0x0003FFF0        // Used by CPU01 to pass
                                                // address of local variables
                                                // to perform actions on
#define SETMASK_16BIT         0x000A            // Mask for setting bits of
                                                // 16-bit word
#define CLEARMASK_16BIT       0x000A            // Mask for clearing bits of
                                                // 16-bit word
#define SETMASK_32BIT         0x00010005        // Mask for setting bits of
                                                // 32-bit word
#define CLEARMASK_32BIT       0x00010005        // Mask for clearing bits of
                                                // 32-bit word
#define GS0SARAM_START        0xC000            // Start of GS0 SARAM in CPU01
                                                // memory map

#define PCLKCR9               0x00030003        // Value to write into PCLKCR9
                                                // register
#define PCLKCR10              0x0000000C        // Value to write into PCLKCR10
                                                // register
#define PCLKCR11              0x00020002        // Value to write into PCLKCR11
                                                // register
#define PCLKCR12              0x00000001        // Value to write into PCLKCR12
                                                // register

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

//
// Function Prototypes
//
__interrupt void CPU01TOCPU02IPC0IntHandler(void);
__interrupt void CPU01TOCPU02IPC1IntHandler(void);

//
// Main
//
void
main(void)
{
    uint16_t ErrorCount = 0;
    uint16_t counter;
    uint16_t usWWord16;
    uint32_t ulWWord32;
    uint16_t usRWord16;
    uint32_t ulRWord32;
    uint32_t ulCPU02Buffer[4];
    uint32_t *pulMsgRam = (void *)CPU01TOCPU02_PASSMSG;
    uint32_t *pulCPU01BufferPt = (void *)GS0SARAM_START;
    uint32_t *pulCPU02BufferPt = (void *)(GS0SARAM_START + 4);

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
    PieVectTable.IPC0_INT = &CPU01TOCPU02IPC0IntHandler;
    PieVectTable.IPC1_INT = &CPU01TOCPU02IPC1IntHandler;
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
// Enable IPC INTn in the PIE: Group 11 interrupts
//
    PieCtrlRegs.PIEIER1.bit.INTx13 = 1; // CPU01 to CPU02 IPC INT0
    PieCtrlRegs.PIEIER1.bit.INTx14 = 1; // CPU01 to CPU02 IPC INT1

//
// Enable global Interrupts and higher priority real-time debug events:
//
    EINT;   // Enable Global interrupt INTM
    ERTM;   // Enable Global realtime interrupt DBGM

//
// Initialize all variables used in example.
//
    ErrorFlag = 0;
    usWWord16 = 0x0005;     // set bits 0 and 2
    ulWWord32 = 0x0002000A; // set bits 1,3 and 17
    usRWord16 = 0;
    ulRWord32 = 0;
    ulCPU02Buffer[0] = PCLKCR9;
    ulCPU02Buffer[1] = PCLKCR10;
    ulCPU02Buffer[2] = PCLKCR11;
    ulCPU02Buffer[3] = PCLKCR12;

//
// Spin here until CPU01 has written variable addresses to pulMsgRam
//
    while(IpcRegs.IPCSTS.bit.IPC17 != 1)
    {
    }
    IpcRegs.IPCACK.bit.IPC17 = 1;

//
// 16 and 32-bit Data Writes to Write-Protected CPU01 Addresses
//

//
// Write 16-bit word to CPU01 16-bit write word variable.
//
    IPCLtoRDataWrite_Protected(&g_sIpcController1, pulMsgRam[0],
                               (uint32_t)usWWord16, IPC_LENGTH_16_BITS,
                               ENABLE_BLOCKING,
                               NO_FLAG);

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
    IPCLtoRDataWrite_Protected(&g_sIpcController1, pulMsgRam[1],ulWWord32,
                               IPC_LENGTH_32_BITS, ENABLE_BLOCKING,
                               NO_FLAG);

//
// Read 32-bit word from CPU01 32-bit write word variable. Use IPC Flag 18 to
// check when read data is ready.
//
    IPCLtoRDataRead(&g_sIpcController1, pulMsgRam[1], &ulRWord32,
                    IPC_LENGTH_32_BITS, ENABLE_BLOCKING,
                    IPC_FLAG18);

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
// 16 and 32-bit Data Set Bits to Write Protected CPU01 Addresses
// Set bits 0 and 3 of register whose address is in pulMsgRam[0]
//
    IPCLtoRSetBits_Protected(&g_sIpcController1, pulMsgRam[0],
                             (uint32_t)SETMASK_16BIT, IPC_LENGTH_16_BITS,
                             ENABLE_BLOCKING);

//
// Read 16-bit word from CPU01 16-bit write word variable. Use IPC Flag 17 to
// check when read data is ready.
//
    IPCLtoRDataRead(&g_sIpcController1, pulMsgRam[0], &usRWord16,
                    IPC_LENGTH_16_BITS, ENABLE_BLOCKING,
                    IPC_FLAG17);

//
// Set bits 0 and 3 of register whose address is in pulMsgRam[0]
//
    IPCLtoRSetBits_Protected(&g_sIpcController1, pulMsgRam[1], SETMASK_32BIT,
                             IPC_LENGTH_32_BITS,
                             ENABLE_BLOCKING);

//
// Read 32-bit word from CPU01 32-bit write word variable. Use IPC Flag 18 to
// check when read data is ready.
//
    IPCLtoRDataRead(&g_sIpcController1, pulMsgRam[1], &ulRWord32,
                    IPC_LENGTH_32_BITS, ENABLE_BLOCKING,
                    IPC_FLAG18);

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
// 16 and 32-bit Data Clear Bits to Write-Protected CPU01 Addresses
// Clear alternating bits in 16-bit write word variable location
//
    IPCLtoRClearBits_Protected(&g_sIpcController1, pulMsgRam[0],
                               (uint32_t)CLEARMASK_16BIT, IPC_LENGTH_16_BITS,
                               ENABLE_BLOCKING);

//
// Read 32-bit word from CPU01 16-bit write word variable. Use IPC Flag 17 to
// check when read data is ready.
//
    IPCLtoRDataRead(&g_sIpcController1, pulMsgRam[0], &usRWord16,
                    IPC_LENGTH_16_BITS, ENABLE_BLOCKING,
                    IPC_FLAG17);

//
// Clear alternating bits in 32-bit write word variable location
//
    IPCLtoRClearBits_Protected(&g_sIpcController1, pulMsgRam[1],
                               (uint32_t)CLEARMASK_32BIT, IPC_LENGTH_32_BITS,
                               ENABLE_BLOCKING);

//
// Read 32-bit word from CPU01 32-bit write word variable. Use IPC Flag 18 to
// check when read data is ready.
//
    IPCLtoRDataRead(&g_sIpcController1, pulMsgRam[1], &ulRWord32,
                    IPC_LENGTH_32_BITS, ENABLE_BLOCKING,
                    IPC_FLAG18);

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
// Data Block Writes to Write-Protected CPU02 Addresses
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
    for(counter = 0; counter < 4; counter++)
    {
        pulCPU02BufferPt[counter] = ulCPU02Buffer[counter];
    }

    IPCLtoRBlockWrite_Protected(&g_sIpcController2, pulMsgRam[2],
                                (uint32_t)pulCPU02BufferPt, 4,
                                IPC_LENGTH_32_BITS, ENABLE_BLOCKING);

//
// Give Memory Access to GS0 SARAM to CPU01
//
    IPCReqMemAccess(&g_sIpcController2, GS0_ACCESS, IPC_GSX_CPU1_MASTER,
                    ENABLE_BLOCKING);

//
// Read data back from CPU01.
//
    IPCLtoRBlockRead(&g_sIpcController2, pulMsgRam[2],
                     (uint32_t)pulCPU01BufferPt, 8,
                     ENABLE_BLOCKING,IPC_FLAG17);

//
// Wait until read data is ready (by checking IPC Response Flag is cleared).
// Then check for correct data.
//
    while(IpcRegs.IPCFLG.bit.IPC17)
    {
    }

    for(counter = 0; counter <4; counter++)
    {
        if(ulCPU02Buffer[counter] != pulCPU01BufferPt[counter])
        {
            ErrorFlag = 1;
        }
    }

    if (ErrorFlag == 1)
    {
        ErrorCount++;
    }

//
// 16 and 32-bit Data Reads into Write-Protected CPU02 Addresses
//
    EALLOW;
    CpuSysRegs.PCLKCR7.all = 0;
    EDIS;

//
// Read 16-bit word from CPU01 to configure EALLOW-protected PCLKCR7
// Use IPC Flag 17 to check when read data is ready.
//
    IPCLtoRDataRead_Protected(&g_sIpcController1, pulMsgRam[3],
                              (void *)&CpuSysRegs.PCLKCR7.all,
                              IPC_LENGTH_16_BITS, ENABLE_BLOCKING,IPC_FLAG17);

    EALLOW;
    CpuSysRegs.PCLKCR8.all = 0;
    EDIS;

//
// Read 32-bit word from CPU01 to configure EALLOW-protected PCLKCR8
// Use IPC Flag 18 to check when read data is ready.
//
    IPCLtoRDataRead_Protected(&g_sIpcController1, pulMsgRam[4],
                              (void *)&CpuSysRegs.PCLKCR8.all,
                              IPC_LENGTH_32_BITS, ENABLE_BLOCKING,IPC_FLAG18);

//
// Wait until read variables are ready (by checking IPC Response Flag is
// cleared). Then check correct bits are set.
//
    while(IpcRegs.IPCFLG.bit.IPC17)
    {
    }

    if(CpuSysRegs.PCLKCR7.all != 0x0001)
    {
        ErrorCount++;
    }

    while(IpcRegs.IPCFLG.bit.IPC18)
    {
    }

    if(CpuSysRegs.PCLKCR8.all != 0x00010002)
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
// CPU01TOCPU02IPC0IntHandler - Handles writes into CPU02 addresses as a
//                              result of read commands to the CPU01.
//
__interrupt void
CPU01TOCPU02IPC0IntHandler(void)
{
    tIpcMessage sMessage;

    //
    // Continue processing messages as long as CPU01 to CPU02 GetBuffer1
    // has messages
    //
    while(IpcGet(&g_sIpcController1, &sMessage,DISABLE_BLOCKING) !=
          STATUS_FAIL)
    {
        switch (sMessage.ulcommand)
        {
            case IPC_DATA_WRITE:
                IPCRtoLDataWrite (&sMessage);
                break;
            case IPC_DATA_WRITE_PROTECTED:
                IPCRtoLDataWrite_Protected(&sMessage);
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
// CPU01TOCPU02IPC1IntHandler - Should never reach this ISR. This is an
//                              optional placeholder for g_sIpcController2.
//
__interrupt void
CPU01TOCPU02IPC1IntHandler(void)
{
    //
    // Should never reach here - Placeholder for Debug
    //

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
