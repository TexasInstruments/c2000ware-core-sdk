//#############################################################################
//
// FILE:   mcan_ex3_loopback_syscfg.c
//
// TITLE:   MCAN Loopback with Interrupts Example Using SYSCONFIG Tool
//
//! \addtogroup driver_example_list
//! <h1> MCAN Loopback with Interrupts Example Using SYSCONFIG Tool </h1>
//!
//! This example illustrates the MCAN Loopback functionality. The internal
//! loopback mode is entered. The message transmitted would be received by the
//! node. The last address of memory is used for the Rx buffer.
//! Peripheral configuration is done through SYSCONFIG
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - error - Checks if there is an error that occurred when the data was
//!            sent using internal loopback.
//!
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
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
//#############################################################################

//
// Include Files
//
#include "driverlib.h"
#include "device.h"
#include "inc/stw_dataTypes.h"
#include "inc/stw_types.h"
#include "board.h"

//
// Defines
//
#define MCAN_EXT_ID_AND_MASK            (0x1FFFFFFFU)
#define MCAN_MSG_INT                    (0x81200)

//
// Global Variables.
//
volatile uint32_t isrIntr0Flag = 1U;
volatile uint32_t isrIntr1Flag = 1U;
volatile unsigned long msgCount = 0;
volatile unsigned long error = 0;

//
// Function Prototype.
//
static void MCANFilterConfig(void);
static void MCANIntrConfig(void);
__interrupt void MCANIntr0ISR(void);
__interrupt void MCANIntr1ISR(void);

//
// Main
//
void main(void)
{
    volatile uint32_t mode = 0U;
    MCAN_TxBufElement    txMsg;
    MCAN_RxBufElement    rxMsg;
    MCAN_RxNewDataStatus newData;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Initialize GPIO and unlock the GPIO configuration registers
    //
    Device_initGPIO();

    //
    // Configure the divisor for the MCAN bit-clock
    //
    SysCtl_setMCANClk(SYSCTL_MCANCLK_DIV_3);

    //
    // CrossBar and ISR Configuration.
    //
    MCANIntrConfig();

    //
    // Board initialization
    //
    Board_init();

    //
    // Initialize message to transmit.
    //
    txMsg.id       = ((uint32_t)(0x4)) << 18U; // Identifier Value.
    txMsg.rtr      = 0U; // Transmit data frame.
    txMsg.xtd      = 0U; // 11-bit standard identifier.
    txMsg.esi      = 0U; // ESI bit in CAN FD format depends only on error
                         // passive flag.
    txMsg.dlc      = 4U; // CAN + CAN FD: transmit frame has 0-8 data bytes.
    txMsg.brs      = 1U; // CAN FD frames transmitted with bit rate
                         // switching.
    txMsg.fdf      = 1U; // Frame transmitted in CAN FD format.
    txMsg.efc      = 1U; // Store Tx events.
    txMsg.mm       = 0xAAU; // Message Marker.

    //
    // Data bytes.
    //
    txMsg.data[0]  = 0x12;
    txMsg.data[1]  = 0x34;
    txMsg.data[2]  = 0x56;
    txMsg.data[3]  = 0x78;

    //
    // Write Tx Message to the Message RAM.
    //
    MCAN_writeMsgRam(MCANA_DRIVER_BASE, MCAN_MEM_TYPE_BUF, 1U, &txMsg);

    //
    // Enable Transmission interrupt.
    //
    MCAN_txBufTransIntrEnable(MCANA_DRIVER_BASE, 1U,1U);

    //
    // Add request for transmission.
    //
    MCAN_txBufAddReq(MCANA_DRIVER_BASE, 1U);

    //
    // Wait for the isrIntr1Flag to be reset.
    //
    while(isrIntr1Flag)
    {
    }

    //
    // Read Message RAM.
    //
    MCAN_readMsgRam(MCANA_DRIVER_BASE, MCAN_MEM_TYPE_BUF, 0U, MCAN_RX_FIFO_NUM_1,
                    &rxMsg);

    //
    // Get the New Data Status.
    //
    MCAN_getNewDataStatus(MCANA_DRIVER_BASE, &newData);

    //
    // Check that received data matches sent data.
    // Device will halt here during debug if data doesn't match.
    //
    if((txMsg.data[0] != rxMsg.data[0]) ||
       (txMsg.data[1] != rxMsg.data[1]) ||
       (txMsg.data[2] != rxMsg.data[2]) ||
       (txMsg.data[3] != rxMsg.data[3]))
    {
        //
        // Device will halt here if transmitted and received data are
        // not same.
        //
        asm(" ESTOP0");
    }
    else
    {
        //
        // Increment message count if message is received.
        //
        msgCount++;
    }

    //
    // Stop Application.
    //
    asm(" ESTOP0");
}

//
// This function will configure X-BAR for MCAN interrupts.
//
static void MCANIntrConfig(void)
{

    Interrupt_initModule();
    Interrupt_initVectorTable();

    Interrupt_enableGlobal();

}

//
// This is Interrupt Service Routine for MCAN interrupt 0.
//
__interrupt void MCANIntr0ISR(void)
{
    uint32_t intrStatus;
    intrStatus = MCAN_getIntrStatus(MCANA_DRIVER_BASE);

    if (MCAN_MSG_INT != intrStatus)
    {
        error++;
    }

    //
    // Clear the interrupt Status.
    //
    MCAN_clearIntrStatus(MCANA_DRIVER_BASE, intrStatus);

    //
    // Update the flag value.
    //
    isrIntr0Flag = 0U;

    //
    // Acknowledge this interrupt located in group 9
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
}

//
// This is Interrupt Service Routine for MCAN interrupt 1.
//
__interrupt void MCANIntr1ISR(void)
{
    uint32_t intrStatus;

    intrStatus = MCAN_getIntrStatus(MCANA_DRIVER_BASE);
    if (MCAN_MSG_INT != intrStatus)
    {
        error++;
    }

    //
    // Clear the interrupt Status.
    //
    MCAN_clearIntrStatus(MCANA_DRIVER_BASE, intrStatus);

    //
    // Update the flag value.
    //
    isrIntr1Flag = 0U;

    //
    // Acknowledge this interrupt located in group 9
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
}
