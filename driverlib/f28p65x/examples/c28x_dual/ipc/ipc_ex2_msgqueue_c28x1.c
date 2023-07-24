//#############################################################################
//
// FILE:   ipc_ex2_msgqueue_c28x1.c
//
// TITLE:  IPC example with interrupt and message queue
//
//! \addtogroup driver_dual_example_list
//! <h1> IPC message passing example with interrupt and message queue </h1>
//!
//! This example demonstrates how to configure IPC and pass information from
//! C28x1 to C28x2 core with message queues.
//! It is recommended to run the C28x1 core first, followed by the C28x2 core.
//!
//! \note In the default CPU2 linker cmd file, GS4, FLASH_BANK3 and FLASH_BANK4
//! are used for allocating various CPU2 sections. The CPU1 application
//! assigns the ownership of these memory regions to CPU2. Please note that CPU2
//! .out file can be loaded only after CPU1 completes this configuration
//!
//! The erase setting (CPU1/CPU2 On-Chip Flash -> erase setting) needs to be
//! configured as selected banks only (Choose the corresponding BANKS allocated
//! for CPUs) or necessary sectors only before loading CPU1/CPU2.out file
//! (This is applicable only for FLASH configuration)
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - pass
//!
//
//#############################################################################
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
//###########################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"

//
// Defines
//
#define IPC_CMD_READ_MEM   0x1001
#define IPC_CMD_RESP       0x2001

#define TEST_PASS          0x5555
#define TEST_FAIL          0xAAAA


#pragma DATA_SECTION(readData, "MSGRAM_CPU1_TO_CPU2")
uint32_t readData[10];

uint32_t pass;

//
// Main
//
void main(void)
{
    int i;
    IPC_MessageQueue_t messageQueue;
    IPC_Message_t      TxMsg, RxMsg;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Assign RAMs and Flash banks to CPU2.
    // In the default CPU2 linker cmd files, GS4, FLASH_BANK3 and FLASH_BANK4
    // are used for allocating various CPU2 sections.
    // In case CPU2 needs additional RAM or Flash regions, CPU1 needs to assign
    // its ownership to CPU2 using the following functions :
    //      - MemCfg_setGSRAMControllerSel for GSRAM
    //      - SysCtl_allocateDxRAM for DRAM
    //      - SysCtl_allocateFlashBank for Flash
    //
    MemCfg_setGSRAMControllerSel(MEMCFG_SECT_GS4, MEMCFG_GSRAMCONTROLLER_CPU2);
    SysCtl_allocateFlashBank(SYSCTL_FLASH_BANK3, SYSCTL_CPUSEL_CPU2);
    SysCtl_allocateFlashBank(SYSCTL_FLASH_BANK4, SYSCTL_CPUSEL_CPU2);

    //
    // Boot CPU2 core
    //
#ifdef _FLASH
    Device_bootCPU2(BOOTMODE_BOOT_TO_FLASH_BANK3_SECTOR0);
#else
    Device_bootCPU2(BOOTMODE_BOOT_TO_M0RAM);
#endif


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
    // Clear any IPC flags if set already
    //
    IPC_clearFlagLtoR(IPC_CPU1_L_CPU2_R, IPC_FLAG_ALL);

    //
    // Initialize message queue
    //
    IPC_initMessageQueue(IPC_CPU1_L_CPU2_R, &messageQueue, IPC_INT1, IPC_INT1);

    //
    // Synchronize both the cores
    //
    IPC_sync(IPC_CPU1_L_CPU2_R, IPC_FLAG31);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Fill in the data to be sent
    //
    for(i=0; i<10; i++)
    {
        readData[i] = i;
    }

    //
    // Update the message
    //
    TxMsg.command = IPC_CMD_READ_MEM;
    TxMsg.address = (uint32_t)readData;
    TxMsg.dataw1  = 10;  // Using dataw1 as data length
    TxMsg.dataw2  = 1;   // Message identifier

    //
    // Send message to the queue
    //
    IPC_sendMessageToQueue(IPC_CPU1_L_CPU2_R, &messageQueue, IPC_ADDR_CORRECTION_ENABLE,
                           &TxMsg, IPC_BLOCKING_CALL);

    //
    // Read message from the queue
    //
    IPC_readMessageFromQueue(IPC_CPU1_L_CPU2_R, &messageQueue, IPC_ADDR_CORRECTION_DISABLE,
                             &RxMsg, IPC_BLOCKING_CALL);

    if((RxMsg.command == IPC_CMD_RESP) && (RxMsg.dataw1 == TEST_PASS) && (RxMsg.dataw2 == 1))
        pass = 1;
    else
        pass = 0;


    //
    // End of example. Loop forever
    //
    while(1);
}


//
// End of File
//
