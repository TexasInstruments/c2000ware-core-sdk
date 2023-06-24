//#############################################################################
//
// FILE:   ethernet_ipc_ex1_basic_c28x1.c
//
// TITLE:  Ethernet IPC example with interrupt
//
//! \addtogroup driver_cm_c28x_dual_example_list
//! <h1> Ethernet + IPC basic message passing example with interrupt </h1>
//!
//! This example demonstrates how to configure IPC and pass information from
//! C28x to CM core without message queues. This configures the Pinmux for Ethernet
//! Prepares the Ethernet frame that is sent to the CM core
//! over IPC Message RAM. Uses the IPC command interface to signal
//! the IPC Command, Packet address, Packet Length which is used by CM
//! side code to send it on the Ethernet Line, which is acknowledged by
//! the CM core side code over IPC on succesfully receiving a packet
//! It is recommended to run the C28x1 core first, followed by the CM core.
//!
//! \b External \b Connections \n
//!  - Connections for Ethernet in MII mode
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

#define PACKET_LENGTH 132
#pragma DATA_SECTION(packetData, "MSGRAM_CPU_TO_CM")
uint8_t packetData[PACKET_LENGTH];

uint32_t pass;

//
// Main
//
void main(void)
{
    int i;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Boot CM core
    //
#ifdef _FLASH
    Device_bootCM(BOOTMODE_BOOT_TO_FLASH_SECTOR0);
#else
    Device_bootCM(BOOTMODE_BOOT_TO_S0RAM);
#endif

    //
    //Set up EnetCLK to use SYSPLL as the clock source and set the
    //clock divider to 2.
    //
    //This way we ensure that the PTP clock is 100 MHz. Note that this value
    //is not automatically/dynamically known to the CM core and hence it needs
    //to be made available to the CM side code beforehand.
    //
    SysCtl_setEnetClk(SYSCTL_ENETCLKOUT_DIV_2, SYSCTL_SOURCE_SYSPLL);

    //
    // Configure the GPIOs for ETHERNET.
    //

    //
    // MDIO Signals
    //
    GPIO_setPinConfig(GPIO_105_ENET_MDIO_CLK);
    GPIO_setPinConfig(GPIO_106_ENET_MDIO_DATA);

    //
    // Use this only for RMII Mode
    //GPIO_setPinConfig(GPIO_73_ENET_RMII_CLK);
    //

    //
    //MII Signals
    //
    GPIO_setPinConfig(GPIO_109_ENET_MII_CRS);
    GPIO_setPinConfig(GPIO_110_ENET_MII_COL);

    GPIO_setPinConfig(GPIO_75_ENET_MII_TX_DATA0);
    GPIO_setPinConfig(GPIO_122_ENET_MII_TX_DATA1);
    GPIO_setPinConfig(GPIO_123_ENET_MII_TX_DATA2);
    GPIO_setPinConfig(GPIO_124_ENET_MII_TX_DATA3);

    //
    //Use this only if the TX Error pin has to be connected
    //GPIO_setPinConfig(GPIO_46_ENET_MII_TX_ERR);
    //

    GPIO_setPinConfig(GPIO_118_ENET_MII_TX_EN);

    GPIO_setPinConfig(GPIO_114_ENET_MII_RX_DATA0);
    GPIO_setPinConfig(GPIO_115_ENET_MII_RX_DATA1);
    GPIO_setPinConfig(GPIO_116_ENET_MII_RX_DATA2);
    GPIO_setPinConfig(GPIO_117_ENET_MII_RX_DATA3);
    GPIO_setPinConfig(GPIO_113_ENET_MII_RX_ERR);
    GPIO_setPinConfig(GPIO_112_ENET_MII_RX_DV);

    GPIO_setPinConfig(GPIO_44_ENET_MII_TX_CLK);
    GPIO_setPinConfig(GPIO_111_ENET_MII_RX_CLK);

    //
    //Power down pin to bring the external PHY out of Power down
    //
    GPIO_setDirectionMode(108, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(108, GPIO_PIN_TYPE_PULLUP);
    GPIO_writePin(108,1);

    //
    //PHY Reset Pin to be driven High to bring external PHY out of Reset
    //

    GPIO_setDirectionMode(119, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(119, GPIO_PIN_TYPE_PULLUP);
    GPIO_writePin(119,1);

    //
    //Form the unicast Ethernet Packet in Memory
    //
    for(i=0;i<PACKET_LENGTH/4;i++)
    {
        //
        //First 6 bytes of the packet are the MAC Destination Address
        //Bytes, the Destination and CRC shall be inserted by the hardware
        //
        if(i == 0)
            *((uint32_t *)packetData + i) = 0x01020304;
        else if(i == 1)
            *((uint32_t *)packetData + i)  = 0xFFFF0506;
        else
            HWREG((uint32_t *)packetData +i) = i;
    }

    //
    // Clear any IPC flags if set already
    //
    IPC_clearFlagLtoR(IPC_CPU1_L_CM_R, IPC_FLAG_ALL);

    //
    // Synchronize both the cores.
    //
    IPC_sync(IPC_CPU1_L_CM_R, IPC_FLAG31);



    //
    // Send a message without message queue
    // Since C28x and CM does not share the same address space for shared RAM,
    // ADDRESS_CORRECTION is enabled
    // Length of the data to be read is passed as data.
    //
    IPC_sendCommand(IPC_CPU1_L_CM_R, IPC_FLAG0, IPC_ADDR_CORRECTION_ENABLE,
                    IPC_CMD_READ_MEM, (uint32_t)packetData, PACKET_LENGTH);

    //
    // Wait for acknowledgment
    //
    IPC_waitForAck(IPC_CPU1_L_CM_R, IPC_FLAG0);

    //
    // Read response
    //
    if(IPC_getResponse(IPC_CPU1_L_CM_R) == TEST_PASS)
    {
        pass = 1;
    }
    else
    {
        pass = 0;
    }

    //
    // End of example. Loop forever
    //
    while(1);
}
//
// End of File
//
