//#############################################################################
//
// FILE:   ethernet_ex3_threshold_mode_phy_loopback.c
//
// TITLE:  Ethernet Threshold Mode Example
//
//! \addtogroup driver_example_cm_list
//! <h1> Ethernet Threshold mode with level PHY loopback  </h1>
//!
//! This example demonstrates the steps to be followed in using the
//! Ethernet of the Communication Manager Subsystem to initialize
//! the Ethernet module in Threshold mode
//! It Configures the module in MII External Loop back mode in which
//! the packet is looped back at external PHY.
//! Prepares a packet to be sent, Sends the packet and reads the staticstics
//! to check if the packet is received by the module
//! It configures the Transmit and Receive queues of Ethernet DMA
//! in Threshold mode.
//! The Transmit threshold mode generates early
//! transmit interrupts when each buffer is transmitted from the memory
//! into the transmit FIFO. The Buffer can be reclaimed by the application.
//! The Receive threshold mode generates early receive interrupts
//! where the module generates Early receive interrupts when programmed
//! threshold buffer size is transferred into receive buffer memory from
//! the receive FIFO.
//! This will be of use when dealing with Time critical receive paths
//! where the application can consume the packets at programmed burstLength
//! unlike the conventional Store and Forward mode(Default) where the module
//! generates the interrupts when the complete packet is transmitted on the Line
//! and when the complete packet is received and checksum validation is succesful
//! This example provides a starting point for configuring the threshold mode.
//! Refer to the Driver API guide for the different callbacks available in the driver.
//! It uses the example Interrupt Service Routines provided in the driver library.
//! Users can modify those ISRs or write another as per their need.
//! Before running this Communication Manager code the C28x cpu1 code has to be run
//! to configure the clocks to Communication manager and required IO pads for Ethernet module
//!
//! \b External \b Connections \n
//!  This example programs the Ethernet module in External Loop back mode (at PHY)
//! and hence needs external connection to the PHY on the MII interface and
//! also the MDIO Pins connected to the PHY. This example assumes DP83822 PHY
//! for the PHY configurations if a different PHY is used the sequences might change.
//! Refer to the C28x CPU1 code of ethernet_config_c28x project
//! for which GPIOs are used for connecting to the PHY
//!
//! \b Watch \b Variables \n
//!  - phyRegContent variable can be checked to know if PHY register
//! read,write is working correctly
//!  - Ethernet_txInterruptCount - this variable available in driver library
//! provides a count of number of times Transmit completion interrupt
//! (on full packet transmission onto the line) occured
//!  - Ethernet_rxInterruptCount - this variable provides a count of
//! number of times the complete Receive completion interrupt occured
//!  - Ethernet_earlyRxInterruptCount - the number of times the early
//! receive interrupt occured. This depends on the burstLength configured
//!  - Ethernet_earlyTxInterruptCount - the number of times the early
//! transmit interrupt occured. This depends on the number of fragments of the
//! packets transmitted
//!
//
//#############################################################################
//
//
// 
// C2000Ware v5.03.00.00
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
#define PACKET_LENGTH 1508
#define NUM_PACKETS 1

#define ETHERNET_NO_OF_RX_PACKETS   1U
//
//Change this define for changing Packet buffer length
//
#define ETHERNET_MAX_PACKET_LENGTH 1538U
//
// Globals
// We are dividing the packet into two fragments
// For demonstration we are using two different buffers
//
uint8_t pData[PACKET_LENGTH/2];
uint8_t pData2[PACKET_LENGTH/2];

//
// Globals
//
uint8_t Ethernet_rxBuffer[ETHERNET_NO_OF_RX_PACKETS *
ETHERNET_MAX_PACKET_LENGTH];

//
// Main
//
void main(void)
{
    Ethernet_InitInterfaceConfig initInterfaceConfig;
    Ethernet_InitConfig *pInitCfg;
    Ethernet_Pkt_Desc pktDesc[2];
    uint32_t i;
    Ethernet_Handle emac_handle;
    uint16_t phyRegContent=0;


    //
    // Initialize device clock and peripherals
    //
    CM_init();

    //
    //Form the unicast Packet in Memory
    //First 6 bytes of the packet are the MAC Destination Address
    //Bytes, the Destination and CRC shall be inserted by the hardware
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
    //Second Fragment shall not contain MAC header but just data
    //
    for(i=0;i<PACKET_LENGTH/8;i++)
    {
        HWREG((uint32_t *)pData2 +i) = 0xFFFFFFFF;
    }

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
    //Configure a single channel for Tx and Rx
    //
    pInitCfg->numChannels = 1;

    //
    // The default mode chosen by getInitConfig shall be Store and Forward
    //In that mode the interrupts are generated when the complete packet is sent out
    //on the line and received on the line in Receive side
    //
    for(i=0;i<pInitCfg->numChannels;i++)
    {
        //
        //Configure the TX Queue in Threshold mode
        //Disabling Store and Forward mode will configure Threshold mode
        //
        pInitCfg->chInfo[ETHERNET_CH_DIR_TX][i].storeNForward =
        ETHERNET_MTL_TXQ_OPMODE_TSF_DISABLE;

        //
        //Configure the Rx Queue in threshold mode
        //Disabling Store and Forward mode will configure Threshold mode
        //
        pInitCfg->chInfo[ETHERNET_CH_DIR_RX][i].storeNForward =
        ETHERNET_MTL_RX_Q_OP_MODE_RSF_DISABLE;

        //
        //Burst Length is the number of beats(32 bits/one word)
        //Configuring 32 burstLength will generate an interrupt for every
        //128 bytes of data pushed into Receive Queue from the Rx line
        //Please program this to a value based on the ISR latency for the
        //Ethernet Combined Interrupt (SBD) handler.The value of 32 is
        //chosen based on the interrrupt handler example provided in the
        //driver library
        //
        pInitCfg->chInfo[ETHERNET_CH_DIR_RX][i].burstLength = 32;

    }

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
    //Get the handle for the module configured with the
    //chosen parameters as configured above in addition
    //to default parameters
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
    Interrupt_registerHandler(INT_EMAC, Ethernet_genericISR);
    //
    //Enable the default interrupt handlers
    //
    Interrupt_enable(INT_EMAC_TX0);
    Interrupt_enable(INT_EMAC_RX0);
    Interrupt_enable(INT_EMAC);
    //
    //For Channel 0
    //Enable the Abnormal Interrupt
    //The Early Transmit interrupt and Early Receive interrupt
    //which are key for handling Threshold mode of the module
    //By default these interrupts are not enabled in the driver
    //Generic SBD interrupt shall be generated for these events
    //For this example we are relying on the example ISR provided by
    //the Low level driver
    //
    Ethernet_enableDmaInterrupt(EMAC_BASE,
                                0,
                                ETHERNET_DMA_CH0_INTERRUPT_ENABLE_AIE
                                |ETHERNET_DMA_CH0_INTERRUPT_ENABLE_ETIE
                                |ETHERNET_DMA_CH0_INTERRUPT_ENABLE_ERIE);


    //
    //Low Frequency
    //value of 5 for selecting the slowest possible MDIO Clock
    //Clause 22 mode
    //
    Ethernet_configureMDIO(EMAC_BASE,0,5,0);

    //
    //The DP83822 External PHY in Control Card
    //takes a PHY address of 1 by default
    //Configure the MDIO module to use PHY address of 0x1
    //
    Ethernet_configurePHYAddress(EMAC_BASE,1);

    //
    //Address 0 of PHY corresponds to Basic Mode Control Register(BMCR)
    //Read the register to know the state
    //
    phyRegContent= Ethernet_readPHYRegister(EMAC_BASE,0);

    //
    //Bit 14 of BMCR configures the MII Loopback
    //
    phyRegContent |= 0x4000;

    Ethernet_writePHYRegister(EMAC_BASE,0,phyRegContent);

    //
    //Read back the BMCR register to confirm that the MII Loopback
    //is configured properly
    //
    phyRegContent= Ethernet_readPHYRegister(EMAC_BASE,0);

    //
    //Prepare a Packet Descriptor structure to send a packet
    //This contains a single buffer single packet
    //The Source address shall be inserted by the MAC
    //Packet CRC is auto computed by the module and appended in the packet
    //
    //In Threshold mode Transmit side the MAC shall generate early interrupt
    //as when the buffer is pushed into the FIFO  by the internal DMA
    //the buffer can be reclaimed by the application
    //With the first interrupt the buffer 0 can be reclaimed
    //For the second interrupt the buffer 1 can be reclaimed by the application
    //

    pktDesc[0].bufferLength = PACKET_LENGTH/2;
    pktDesc[0].dataOffset = 0;
    pktDesc[0].dataBuffer = pData;

    //
    //Point to the next descriptor for forming a chain
    //
    pktDesc[0].nextPacketDesc =&pktDesc[1];

    //
    //This fragment has only SOP EOP shall be in next fragment
    //
    pktDesc[0].flags = ETHERNET_PKT_FLAG_SOP ;
    pktDesc[0].pktChannel = ETHERNET_DMA_CHANNEL_NUM_0;
    pktDesc[0].pktLength = PACKET_LENGTH;
    pktDesc[0].validLength = PACKET_LENGTH/2;

    //
    //This packet is split into two fragments
    //
    pktDesc[0].numPktFrags = 2;
    pktDesc[1].bufferLength = PACKET_LENGTH/2;
    pktDesc[1].dataOffset = 0;
    pktDesc[1].dataBuffer = pData2;
    pktDesc[1].nextPacketDesc =0;
    pktDesc[1].flags = ETHERNET_PKT_FLAG_EOP;
    pktDesc[1].pktChannel = ETHERNET_DMA_CHANNEL_NUM_0;
    pktDesc[1].pktLength = PACKET_LENGTH;
    pktDesc[1].validLength = PACKET_LENGTH/2;

    //
    //Send the packet prepared
    //
    Ethernet_sendPacket(emac_handle,&pktDesc[0]);

    //
    //Transmit Path Interrupts:
    //While the packet is being sent we should observe two early Transmit interrupts
    //and one transmit completion interrupt when the packet is completely transferred
    //on the wire
    //On the Receive Side:
    //As and when the burstLength*4 bytes are transferred from the line to the
    //Memory by the Ethernet DMA there will be an early interrupt
    //
    while(1);

}


