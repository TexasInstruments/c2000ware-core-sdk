//#############################################################################
//
// FILE:   ipc_ex4_msgqueue_sysconfig_c28x2.c
//
// TITLE:  SysConfig IPC example with interrupt and message queue
//
//! \addtogroup driver_dual_example_list
//! <h1> IPC message passing example with interrupt and message queue </h1>
//!
//! This example demonstrates how to configure IPC and pass information from
//! C28x1 to C28x2 core with message queues.
//! It is recommended to run the C28x1 core first, followed by the C28x2 core.
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - None.
//!
//
//#############################################################################
//
// 
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
#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// Defines
//
#define IPC_CMD_READ_MEM   0x1001
#define IPC_CMD_RESP       0x2001

#define TEST_PASS          0x5555
#define TEST_FAIL          0xAAAA

IPC_MessageQueue_t messageQueue;

//
// Function prototypes
//
//__interrupt void IPC_ISR1();

//
// Main
//
void main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    Board_init();

    //
    // Clear any IPC flags if set already
    //
    IPC_clearFlagLtoR(IPC_CPU2_L_CPU1_R, IPC_FLAG_ALL);

    //
    // Initialize message queue
    //
    IPC_initMessageQueue(IPC_CPU2_L_CPU1_R, &messageQueue, IPC_INT1, IPC_INT1);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Synchronize both the cores.
    //
    IPC_sync(IPC_CPU2_L_CPU1_R, SYNC_FLAG);

    //
    // Loop forever. Wait for IPC interrupt
    //
    while(1);
}

//
// IPC ISR for Flag 1
// C28x core sends data with message queue using Flag 0
//
__interrupt void IPC_ISR1()
{
    int i;
    IPC_Message_t TxMsg, RxMsg;
    bool status = false;

    //
    // Read the message from the message queue
    //
    IPC_readMessageFromQueue(IPC_CPU2_L_CPU1_R, &messageQueue, IPC_ADDR_CORRECTION_ENABLE,
                             &RxMsg, IPC_NONBLOCKING_CALL);

    if(RxMsg.command == IPC_CMD_READ_MEM)
    {
        status = true;

        //
        // Read and compare data
        //
        for(i=0; i<RxMsg.dataw1; i++)
        {
            if(*((uint32_t *)RxMsg.address + i) != i)
                status = false;
        }
    }

    //
    // Send response message
    //
    TxMsg.command = IPC_CMD_RESP;
    TxMsg.address = 0; // Not used
    TxMsg.dataw1  = status ? TEST_PASS : TEST_FAIL;
    TxMsg.dataw2  = RxMsg.dataw2; // Use the message identifier from the received message

    IPC_sendMessageToQueue(IPC_CPU2_L_CPU1_R, &messageQueue, IPC_ADDR_CORRECTION_DISABLE,
                           &TxMsg, IPC_NONBLOCKING_CALL);

    //
    // Acknowledge the flag
    //
    IPC_ackFlagRtoL(IPC_CPU2_L_CPU1_R, IPC_FLAG1);

    //
    // Acknowledge the PIE interrupt.
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}

//
// End of File
//
