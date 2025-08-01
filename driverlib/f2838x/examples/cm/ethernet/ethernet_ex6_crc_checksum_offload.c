//#############################################################################
//
// FILE:   ethernet_ex6_basic_crc_checksum_offload.c
//
// TITLE:  Ethernet CRC and Checksum Offloading Example
//
//! \addtogroup driver_example_cm_list
//! <h1> Ethernet MAC CRC and Checksum Offload </h1>
//!
//! This example demonstrates the steps to be followed in using the
//! Ethernet of the Communication Manager Subsystem to initialize
//! the Ethernet module and Configure the module in MAC Loop back mode.
//! Demonstrates how to program the CRC offload
//! and Checksum Offload(IP Checksum)
//! Prepares a packet to be sent, Sends the packet and reads the statistics
//! to check if the packet is received by the module
//! Before running this Communication Manager code the C28x cpu1 code has to be run
//! to configure the clocks to Communication manager
//! and required IO pads for Ethernet module
//!
//! \b External \b Connections \n
//!  This example programs the Ethernet module in Internal Loop back mode
//! and hence needs no external connection on the MII Data lines.
//! But it needs the MII Tx and Rx clocks to be input on those pins
//! Refer to the C28x CPU1 code of ethernet_config_c28x project
//! for which GPIOs are used for connecting to the PHY
//!
//! \b Watch \b Variables \n
//!  - None
//!
//
//#############################################################################
//
//
// 
// C2000Ware v6.00.00.00
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
//#############################################################################

//
// Included Files
//
#include "driverlib_cm.h"
#include "cm.h"

//
// Defines
//


#define ETHERNET_NO_OF_RX_PACKETS   1U
//
//Change this define for changing Packet buffer length
//
#define ETHERNET_MAX_PACKET_LENGTH 128U


//
// Globals
//
uint8_t Ethernet_rxBuffer[ETHERNET_NO_OF_RX_PACKETS *
                          ETHERNET_MAX_PACKET_LENGTH];
//
//This is an example IP protocol packet
//
uint8_t icmp98[92] = {
//0xa8, 0x63, 0xf2, 0x00, 0x00, 0x80,
0x04, 0x03, 0x02, 0x01, 0x06, 0x05,
/* Since the sender MAC address is going to be embedded
 * before sending the packet, we comment the following 6 bytes
 */
/*0x78, 0xa5, // .c....x. // 0x04, 0xc8, 0xa5, 0x0b,*/
0x08, 0x00, 0x45, 0x00, /* ......E. */
0x00, 0x54, 0xb1, 0xa2, 0x40, 0x00, 0x40, 0x01, /* .T..@.@. */
0x07, 0xae, 0xc0, 0xa8, 0x00, 0x03, 0xc0, 0xa8, /* ........ */
0x00, 0x04, 0x07, 0x00, 0x32, 0x4a, 0x57, 0xe8, /* ....2JW. */
0x00, 0x01, 0x73, 0x84, 0xfe, 0x58, 0x04, 0xec, /* ..s..X.. */
0x0c, 0x00, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, /* ........ */
0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, /* ........ */
0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, /* ........ */
0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, /* .. !"#$% */
0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, /* &'()*+,- */
0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, /* ./012345 */
0x36, 0x38                                      /* 67 */
};

#define PACKET_LENGTH sizeof(icmp98)

//
// Main
//
void main(void)
{
    Ethernet_InitInterfaceConfig initInterfaceConfig;
    Ethernet_InitConfig *pInitCfg;
    Ethernet_Pkt_Desc pktDesc;
    Ethernet_Statistics stats;
    Ethernet_Handle emac_handle;

    //
    // Initialize device clock and peripherals
    //
    CM_init();

    //
    //Select the MII interface of the module
    //
    initInterfaceConfig.ssbase = EMAC_SS_BASE;
    initInterfaceConfig.enet_base = EMAC_BASE;
    initInterfaceConfig.phyMode = ETHERNET_SS_PHY_INTF_SEL_MII;
    //
    //Assign SoC specific functions for Enabling,Disabling interrupts
    //and for enabling the Peripheral at system level
    //
    initInterfaceConfig.ptrPlatformInterruptDisable = &Platform_disableInterrupt;
    initInterfaceConfig.ptrPlatformInterruptEnable = &Platform_enableInterrupt;
    initInterfaceConfig.ptrPlatformPeripheralEnable = &Platform_enablePeripheral;
    initInterfaceConfig.ptrPlatformPeripheralReset = &Platform_resetPeripheral;
    //
    //Assign the peripheral number at the SoC
    //
    initInterfaceConfig.peripheralNum = SYSCTL_PERIPH_CLK_ENET;
    //
    //Assign the default SoC specific interrupt numbers of Ethernet interrupts
    //
    initInterfaceConfig.interruptNum[0] = INT_EMAC;
    initInterfaceConfig.interruptNum[1] = INT_EMAC_TX0;
    initInterfaceConfig.interruptNum[2] = INT_EMAC_TX1;
    initInterfaceConfig.interruptNum[3] = INT_EMAC_RX0;
    initInterfaceConfig.interruptNum[4] = INT_EMAC_RX1;

    pInitCfg = Ethernet_initInterface(initInterfaceConfig);

    //
    // Get an initial configuration of known good parameters
    //
    Ethernet_getInitConfig(pInitCfg);

    //
    //Configure the Loopback mode
    //
    pInitCfg->loopbackMode = ETHERNET_MAC_CONFIGURATION_LM_LOOPBACK_ENABLED;
    //
    //Assign the callbacks for Getting packet buffer when needed
    //Releasing the TxPacketBuffer on Transmit interrupt callbacks
    //Receive packet callback on Receive packet completion interrupt
    //
    pInitCfg->pfcbGetPacket = &Ethernet_getPacketBuffer;
    pInitCfg->pfcbFreePacket = &Ethernet_releaseTxPacketBuffer;
    pInitCfg->pfcbRxPacket = &Ethernet_receivePacketCallback;
    //
    //Assign the Buffer to be used by the Low level driver for receiving
    //Packets. This should be accessible by the Ethernet DMA
    //
    pInitCfg->rxBuffer = Ethernet_rxBuffer;
    //
    //The Application handle is not used by this application
    //Hence using a dummy value of 1
    //
    Ethernet_getHandle((Ethernet_Handle)1,pInitCfg , &emac_handle);

    //
    //Do global Interrupt Enable
    //
    (void)Interrupt_enableInProcessor();
    //
    //Assign default ISRs
    //
    Interrupt_registerHandler(INT_EMAC_TX0, Ethernet_transmitISR);
    Interrupt_registerHandler(INT_EMAC_RX0, Ethernet_receiveISR);
    //
    //Enable the default interrupt handlers
    //
    Interrupt_enable(INT_EMAC_TX0);
    Interrupt_enable(INT_EMAC_RX0);

    //
    //Prepare a Packet Descriptor structure to send a packet
    //This contains a single buffer packet
    pktDesc.bufferLength = PACKET_LENGTH;
    pktDesc.dataOffset = 0;
    pktDesc.dataBuffer = icmp98;
    pktDesc.nextPacketDesc = 0;
    //The Source address shall be inserted by the MAC
    //Packet CRC is auto computed by the module and appended in the packet
    //Please OR these values to achieve required CRC offloading
    //ETHERNET_PKT_FLAG_CRC_PAD_INS value is zero which corresponds to CRC
    //Insertion and Pad enabling
    //Use ETHERNET_PKT_FLAG_CRC_INS_NO_PAD to insert CRC but no padding
    //Use ETHERNET_PKT_FLAG_CRC_PAD_DIS to disable CRC and Disable padding
    //Use ETHERNET_PKT_FLAG_CRC_REPL_NO_PAD to replace CRC and disable padding
    //
    //ETHERNET_PKT_FLAG_CIC flag enables the Checksum offload feature at driver
    //which turns on the Hardware Checksum feature with this flag being set
    //
    pktDesc.flags = (ETHERNET_PKT_FLAG_SOP | ETHERNET_PKT_FLAG_EOP |
                     ETHERNET_PKT_FLAG_SA_INS | ETHERNET_PKT_FLAG_CIC);
    pktDesc.pktChannel = ETHERNET_DMA_CHANNEL_NUM_0;
    pktDesc.pktLength = PACKET_LENGTH;
    pktDesc.validLength = PACKET_LENGTH;
    pktDesc.numPktFrags = 1;

    //
    //Send the packet prepared
    //
    Ethernet_sendPacket(emac_handle,&pktDesc);

    //
    //Delay for the MAC to send the packet on the wire and receive it
    //
    SysCtl_delay(3000);

    //
    //Read the statistics of the Module
    //
    Ethernet_getStatistics(emac_handle, &stats);

    //
    //Check if a packet has been received
    //
    if(!stats.rxUnicastPacketsGood)
         __asm("   bkpt #0");

}


