//#############################################################################
//
// FILE:   ipc_ex1_basic_cm.c
//
// TITLE:  IPC example with interrupt
//
//! \addtogroup driver_cm_c28x_dual_example_list
//! <h1> IPC basic message passing example with interrupt </h1>
//!
//! This example demonstrates how to configure IPC and pass information from
//! C28x to CM core without message queues
//! It is recommended to run the C28x1 core first, followed by the CM core.
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
// C2000Ware v5.05.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
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
#include "cm.h"
#include "ipc.h"

//
// Defines
//
#define IPC_CMD_READ_MEM   0x1001
#define IPC_CMD_RESP       0x2001

#define TEST_PASS          0x5555
#define TEST_FAIL          0xAAAA


//
// IPC ISR for Flag 0.
// C28x core sends data without message queue using Flag 0
//
__interrupt void IPC_ISR0()
{
    int i;
    uint32_t command, addr, data;
    bool status = false;

    //
    // Read the command
    //
    IPC_readCommand(IPC_CM_L_CPU1_R, IPC_FLAG0, IPC_ADDR_CORRECTION_ENABLE,
                    &command, &addr, &data);

    if(command == IPC_CMD_READ_MEM)
    {
        status = true;

        //
        // Read and compare data
        //
        for(i=0; i<data; i++)
        {
            if(*((uint32_t *)addr + i) != i)
                status = false;
        }
    }

    //
    // Send response to C28x core
    //
    if(status)
    {
        IPC_sendResponse(IPC_CM_L_CPU1_R, TEST_PASS);
    }
    else
    {
        IPC_sendResponse(IPC_CM_L_CPU1_R, TEST_FAIL);
    }

    //
    // Acknowledge the flag
    //
    IPC_ackFlagRtoL(IPC_CM_L_CPU1_R, IPC_FLAG0);
}

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
    // Clear any IPC flags if set already
    //
    IPC_clearFlagLtoR(IPC_CM_L_CPU1_R, IPC_FLAG_ALL);

    //
    // Enable IPC interrupts
    //
    IPC_registerInterrupt(IPC_CM_L_CPU1_R, IPC_INT0, IPC_ISR0);

    //
    // Synchronize both the cores.
    //
    IPC_sync(IPC_CM_L_CPU1_R, IPC_FLAG31);

    //
    // Loop forever. Wait for IPC interrupt
    //
    while(1);
}


//
// End of File
//
