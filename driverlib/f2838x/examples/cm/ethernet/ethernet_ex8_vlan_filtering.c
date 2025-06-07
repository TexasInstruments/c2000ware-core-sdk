//#############################################################################
//
// FILE:   ethernet_ex8_vlan_filtering.c
//
// TITLE:  Ethernet VLAN and VLAN Filter Example
//
//! \addtogroup driver_example_cm_list
//! <h1> Ethernet MAC Internal Loopback </h1>
//!
//! This example demonstrates the steps to be followed in using the
//! Ethernet of the Communication Manager Subsystem to initialize
//! the Ethernet module and Configure the module in MAC Loop back mode
//! The packet sent is inserted with a VLAN tag.
//! A VLAN filter is configured to route it to a different channel
//! Prepares a packet to be sent, Sends the packet and reads the statistics
//! to check if the packet is received by the module
//! Before running this Communication Manager code the C28x cpu1 code has to be run
//! to configure the clocks to Communication manager
//!	and required IO pads for Ethernet module
//!
//! \b External \b Connections \n
//!  This example programs the Ethernet module in Internal Loop back mode
//!	and hence needs no external connection on the MII Data lines.
//!	But it needs the MII Tx and Rx clocks to be input on those pins
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
#define ETHERNET_MAX_PACKET_LENGTH 1538U
uint8_t Ethernet_rxBuffer[ETHERNET_NO_OF_RX_PACKETS *
                          ETHERNET_MAX_PACKET_LENGTH];

//
// Globals
//
#define PACKET_LENGTH 1508
uint8_t pData[PACKET_LENGTH];


//
// Main
//
void main(void)
{
    Ethernet_InitInterfaceConfig initInterfaceConfig;
    Ethernet_InitConfig *pInitCfg;
    Ethernet_Pkt_Desc pktDesc;
    uint32_t i;
    Ethernet_Statistics stats;
    Ethernet_VlanConfig vLANConfig;
    Ethernet_VLAN_Perfect_FilterParams vlanPerfectFilterParams;
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
    Interrupt_registerHandler(INT_EMAC_TX1, Ethernet_transmitISR);
    Interrupt_registerHandler(INT_EMAC_RX0, Ethernet_receiveISR);
    Interrupt_registerHandler(INT_EMAC_RX1, Ethernet_receiveISR);
    //
    //Enable the default interrupt handlers
    //
    Interrupt_enable(INT_EMAC_TX0);
    Interrupt_enable(INT_EMAC_RX0);
    Interrupt_enable(INT_EMAC_TX1);
    Interrupt_enable(INT_EMAC_RX1);
    //
    //Setup VLAN Parameters
    //
    vLANConfig.vlan_tag =0x0B0B;
    vLANConfig.vlanType = ETHERNET_VLAN_TYPE_C;
    vLANConfig.vlanTagControl = ETHERNET_VLAN_TX_INSERT;
    //
    //This sets a VLAN Tag insertion for all the packets going out of the MAC
    //
    Ethernet_setConfig(emac_handle,ETHERNET_SET_CONFIG_VLAN_TX_OUTER,
                       &vLANConfig,sizeof(vLANConfig));

    //
    //Make the Queues to assign based on dynamic Queues
    //Hence the DMA channels will be selected as programmed in the VLAN Filter
    //This is needed for any Dynamic Queue handling based on incoming parameter
    //

    Ethernet_setDMARxQueueMode(EMAC_BASE, ETHERNET_RX_DMA_QUEUE_DYNAMIC, \
                                   ETHERNET_QUEUE_0, ETHERNET_CHANNEL_1);
    Ethernet_setDMARxQueueMode(EMAC_BASE, ETHERNET_RX_DMA_QUEUE_DYNAMIC, \
                                   ETHERNET_QUEUE_1, ETHERNET_CHANNEL_1);


    //
    //Now Set up the VLAN Filter Parameters
    //
    vlanPerfectFilterParams.dmaChannelEnable = ETHERNET_DMA_CHANNELNUM_ENABLED;
    //
    //Let the packet come into dma Channel 1 for a matching VLAN tag
    //
    vlanPerfectFilterParams.dmaChannelNum = ETHERNET_CHANNEL_1;
    vlanPerfectFilterParams.filterid = 1;
    vlanPerfectFilterParams.vlanid =0x0B0B;
    vlanPerfectFilterParams.vlanEnableDisable = (Ethernet_VlanRxPerfectFilterEnable)ETHERNET_VLAN_RX_FILTER_INNER_VLAN_ENABLED;
    vlanPerfectFilterParams.vlanFilterMode = ETHERNET_VLAN_PERFECT_FILTER_COMPARE_12BITS;
    vlanPerfectFilterParams.vlanPerfectTypeComparisonDisable = ETHERNET_VLAN_PERFECT_FILTER_TYPE_COMPARISON_ENABLED;
    //Check for 0x8100
    vlanPerfectFilterParams.vlanType = ETHERNET_VLAN_TYPE_C;
    //Check only OuterVLAN
    vlanPerfectFilterParams.innerVLANEnabled = ETHERNET_VLAN_RX_FILTER_INNER_VLAN_DISABLED;

    Ethernet_setConfig(emac_handle,ETHERNET_SET_CONFIG_FILTER_VLAN_PERFECT,
                        &vlanPerfectFilterParams,sizeof(vlanPerfectFilterParams));

    //
    //Form the Packet in Memory
    //
    for(i=0;i<PACKET_LENGTH/4;i++)
    {
        if(i == 0)
            *((uint32_t *)pData + i) = 0x01020304;
        else if(i == 1)
            *((uint32_t *)pData + i)  = 0xFFFF0506;
        else
            HWREG((uint32_t *)pData +i) = 0xFFFFFFFF;
    }

    //
    //Prepare a Packet Descriptor structure to send a packet
    //This contains a single buffer packet
    //
    pktDesc.bufferLength = PACKET_LENGTH;
    pktDesc.dataOffset = 0;
    pktDesc.dataBuffer = pData;
    pktDesc.nextPacketDesc = 0;
    //
    //The Source address shall be inserted by the MAC
    //Packet CRC is auto computed by the module and appended in the packet
    //Please OR these values to achieve required CRC offloading
    //ETHERNET_PKT_FLAG_CRC_PAD_INS value is zero which corresponds to CRC
    //Insertion and Pad enabling
    //Use ETHERNET_PKT_FLAG_CRC_INS_NO_PAD to insert CRC but no padding
    //Use ETHERNET_PKT_FLAG_CRC_PAD_DIS to disable CRC and Disable padding
    //Use ETHERNET_PKT_FLAG_CRC_REPL_NO_PAD to replace CRC and disable padding
    //

    pktDesc.flags = (ETHERNET_PKT_FLAG_SOP | ETHERNET_PKT_FLAG_EOP |
                     ETHERNET_PKT_FLAG_SA_INS );
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
    //The packet should have come through Receive DMA Channel 1
    //
    if(!stats.rxUnicastPacketsGood)
         __asm("   bkpt #0");

}


