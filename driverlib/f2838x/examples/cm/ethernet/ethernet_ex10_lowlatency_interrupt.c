//#############################################################################
//
// FILE:   ethernet_ex10_lowlatency_interrupt.c
//
// TITLE:  Ethernet Low Latency Interrupt Example
//
//! \addtogroup driver_example_cm_list
//! <h1> Ethernet Low Latency Interrupt  </h1>
//!
//! This example demonstrates the steps to be followed in using the
//! Ethernet of the Communication Manager Subsystem to handle
//! the Ethernet transmit,receive with minimum latency interrupts.
//! The example interrupt handlers provided in the Ethernet driver
//! help to achieve user friendly buffer management and the generic interrupt
//! handler handles different interrupt sources, these factors might be more
//! cycle consuming. This example demonstrates how to achieve lowest possible
//! latency with interrupts and buffer management with the Ethernet Driver.
//! Before running this Communication Manager code the C28x cpu1 code has to be
//! run to configure the clocks to Communication manager
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
//!  - genericISRCount
//!  - transmitISRCount
//!  - receiveISRCount
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

#define PACKET_LENGTH 508
#define NUM_PACKETS 4

//
// Globals
//

static Ethernet_Handle emac_handle;
uint8_t pData[PACKET_LENGTH];
uint8_t rxBuffer[NUM_PACKETS*PACKET_LENGTH];


//
// The Descriptor Ring can be organized as
// Descriptors for TX Channel 0
// Descriptors for TX Channel 1
// Descriptors for RX Channel 0
// Descriptors for RX Channel 1
// Use the Descriptor pool in driver
//
extern Ethernet_HW_descriptor Ethernet_descArray[ETHERNET_DESCRIPTORS_NUM];

uint8_t indexWriteTx=0;
uint8_t indexMaxTx = ETHERNET_DESCRIPTORS_NUM_TX_PER_CHANNEL;
uint8_t indexReadTx=0;

uint8_t indexMaxRx=
        (ETHERNET_DESCRIPTORS_NUM_TX+ETHERNET_DESCRIPTORS_NUM_RX_PER_CHANNEL);
uint8_t indexWriteRx=0;
uint8_t indexReadRx=0;

uint8_t buffIndex=0;

uint32_t genericISRCount,transmitISRCount, receiveISRCount,getBufferCount;

//
//This is a temporary Packet Descriptor passed to the
//Low level driver it is not linked by the driver
//
Ethernet_Pkt_Desc tempDescriptor;

Ethernet_Pkt_Desc *getPacketBuffer(void);

//
//This is a light weight implementation for sending a packet over Ethernet
//It does not maintain any software queue for the packets
//
void SendPacket(uint8_t *pData,uint32_t length)
{
    Ethernet_descArray[indexWriteTx].des0 = (uint32_t)pData;
    Ethernet_descArray[indexWriteTx].des1 = 0;
    Ethernet_descArray[indexWriteTx].des2 = (ETHERNET_TX_DESC_IOC|length);
    Ethernet_descArray[indexWriteTx].des3 = (ETHERNET_DESC_OWNER |
                                             ETHERNET_PKT_FLAG_SOP |
                                             ETHERNET_PKT_FLAG_EOP);
    Ethernet_writeTxDescTailPointer(EMAC_BASE,
                                    ETHERNET_DMA_CHANNEL_NUM_0,
                                    (Ethernet_HW_descriptor *)
                                     (&Ethernet_descArray[indexWriteTx]));

    //
    //End check for last descriptor
    //
    if(++indexWriteTx == ETHERNET_DESCRIPTORS_NUM_TX_PER_CHANNEL)
    {
        indexWriteTx = 0;
    }
}

//
//Transmit interrupt handler only increments the book keeping variable
//and clears the interrupt can be modified as per needs
//
interrupt void transmitISR(void)
{
    transmitISRCount++;
    Ethernet_clearDMAChannelInterrupt(
                EMAC_BASE,
                ETHERNET_DMA_CHANNEL_NUM_0,
                ETHERNET_DMA_CH0_STATUS_TI
                );
}

//
//Receive interrupt handler called when complete packet is received
//
interrupt void receiveISR(void)
{

    Ethernet_Pkt_Desc *ptrNewPacket=NULL;


    //
    //Clear the interrupt
    //
    Ethernet_clearDMAChannelInterrupt(EMAC_BASE,
                                      ETHERNET_DMA_CHANNEL_NUM_0,
                                      ETHERNET_DMA_CH0_STATUS_RI);


    //
    // Callback - Invoke any application specific callback here
    //Just incrementing the indexRead here we are not consuming the buffers here
    //
    if(++indexReadRx >= (ETHERNET_DESCRIPTORS_NUM_TX +
                         ETHERNET_DESCRIPTORS_NUM_RX_PER_CHANNEL))
    {
        indexReadRx = ETHERNET_DESCRIPTORS_NUM_TX;
    }

    //
    //Refill the packet buffer
    //
    if(Ethernet_descArray[indexReadRx].des3 & ETHERNET_DESC_OWNER )
    {

        ptrNewPacket = getPacketBuffer();
        Ethernet_descArray[indexWriteRx].des0 =
                    (uint32_t)ptrNewPacket->dataBuffer;
        Ethernet_descArray[indexWriteRx].des1 =0;
        Ethernet_descArray[indexWriteRx].des2 = 0;
        Ethernet_descArray[indexWriteRx].des3 = (ETHERNET_DESC_OWNER |
                                                 ETHERNET_RX_DESC_IOC |
                                                 ETHERNET_RX_DESC_BUF1_VALID);

        if(++indexWriteRx == ETHERNET_DESCRIPTORS_NUM_TX +
                              ETHERNET_DESCRIPTORS_NUM_RX_PER_CHANNEL)
        {
            indexWriteRx = ETHERNET_DESCRIPTORS_NUM_TX;
        }
    }
    receiveISRCount++;
}

void IntermediateFragmentCallback(uint8_t segmentnumber)
{

    //
    //Add contents here to service the received chunk (of partial packet)
    //

}

//
//This generic ISR handles only the Early Rx completion interrupt
//If Early Transmit interrupt needs to be handled it can be added here as well
//
interrupt void genericISR(void)
{
    uint16_t fragNumber;
    genericISRCount++;

    //
    //Get the count of how many chunks of packets have come in
    //If the Progammable Buffer length 32 bytes
    //In threshold mode for each 32 bytes of DMA an early Rx interrupt
    //is asserted by hardware which is serviced in this Generic ISR
    //
    fragNumber = Ethernet_getRxERICount(
                    EMAC_BASE,
                    ETHERNET_DMA_CHANNEL_NUM_0);

    //
    //Callback for signalling the arrival of chunk
    //
    IntermediateFragmentCallback(fragNumber);

    //
    //Clear the interrupts at hardware
    //
    Ethernet_clearDMAChannelInterrupt(
                        EMAC_BASE,
                        ETHERNET_DMA_CHANNEL_NUM_0,
                        ETHERNET_DMA_CH0_STATUS_ETI |
                        ETHERNET_DMA_CH0_STATUS_AIS);
    Ethernet_clearDMAChannelInterrupt(
                EMAC_BASE,
                ETHERNET_DMA_CHANNEL_NUM_0,
                ETHERNET_DMA_CH0_STATUS_ERI | ETHERNET_DMA_CH0_STATUS_NIS);
}

//
//This is a simple implementation of Buffer management it returns
//a new buffer pointer from the given packet buffer pool
//
Ethernet_Pkt_Desc *getPacketBuffer(void)
{
    tempDescriptor.dataBuffer = &rxBuffer[buffIndex++ * PACKET_LENGTH];
    if(buffIndex == NUM_PACKETS)
    {
        buffIndex= 0;
    }
    getBufferCount++;
   return &tempDescriptor;
}
main(void)
{
    Ethernet_InitInterfaceConfig initInterfaceConfig;
    Ethernet_InitConfig *pInitCfg;
    uint32_t i;
    
    //
    // Initialize device clock and peripherals
    //
    CM_init();

    //
    //Initialize the indexes for Descriptor Ring access
    //
    indexMaxTx = ETHERNET_DESCRIPTORS_NUM_TX_PER_CHANNEL;
    indexMaxRx = ETHERNET_DESCRIPTORS_NUM_TX +
                    ETHERNET_DESCRIPTORS_NUM_RX_PER_CHANNEL;
    indexWriteTx= indexReadTx = 0;
    indexWriteRx = indexReadRx = ETHERNET_DESCRIPTORS_NUM_TX;

    //
    //Book keeping Watch variables initialized to zero
    //
    genericISRCount = transmitISRCount = receiveISRCount= getBufferCount= 0;


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

    initInterfaceConfig.ssbase = EMAC_SS_BASE;
    initInterfaceConfig.enet_base = EMAC_BASE;
    initInterfaceConfig.phyMode = ETHERNET_SS_PHY_INTF_SEL_MII;

    //
    //Assign SoC specific functions for Enabling,Disabling interrupts
    //and for enabling the Peripheral at system level
    //
    initInterfaceConfig.ptrPlatformInterruptDisable =
                        &Platform_disableInterrupt;
    initInterfaceConfig.ptrPlatformInterruptEnable = &Platform_enableInterrupt;
    initInterfaceConfig.ptrPlatformPeripheralEnable =
                        &Platform_enablePeripheral;
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

    Ethernet_getInitConfig(pInitCfg);

    pInitCfg->numChannels = 1;
    for(i=0;i<pInitCfg->numChannels;i++)
    {
        //
        //Configure the TX in Threshold mode
        //
        pInitCfg->chInfo[ETHERNET_CH_DIR_TX][i].storeNForward = \
                                  ETHERNET_MTL_TXQ_OPMODE_TSF_DISABLE;
        pInitCfg->chInfo[ETHERNET_CH_DIR_TX][i].dmaQueueSize =
                                    ETHERNET_MTL_Q_OP_MODE_QSIZE_2048;

        //
        //Configure the IP in threshold mode
        //For the RX Size
        //
        pInitCfg->chInfo[ETHERNET_CH_DIR_RX][i].storeNForward =
                                    ETHERNET_MTL_RX_Q_OP_MODE_RSF_DISABLE;

    }

    //
    //Enable the Loopback mode of MAC
    //
    pInitCfg->loopbackMode = ETHERNET_MAC_CONFIGURATION_LM_LOOPBACK_ENABLED;


    pInitCfg->dmaMode.InterruptMode = ETHERNET_DMA_MODE_INTM_MODE1;

    //
    //We are implementing our own ISR and hence this callback is not needed
    //
    pInitCfg->pfcbRxPacket = NULL;
    pInitCfg->pfcbGetPacket = &getPacketBuffer;

    Ethernet_getHandle((Ethernet_Handle)1,pInitCfg , &emac_handle);

    //
    //Register the interrupt handlers and enable interrupts
    //
    Interrupt_registerHandler(INT_EMAC_TX0, transmitISR);
    Interrupt_registerHandler(INT_EMAC_RX0, receiveISR);
    Interrupt_registerHandler(INT_EMAC, genericISR);
    Interrupt_enable(INT_EMAC_TX0);
    Interrupt_enable(INT_EMAC_RX0);
    Interrupt_enable(INT_EMAC);

    //
    //Enable Early receive and Early Transmit interrupts
    //Abnormal interrupt is to be enabled for Early recive handling
    //
    Ethernet_enableDmaInterrupt(EMAC_BASE,
                                0,
                                (ETHERNET_DMA_CH0_INTERRUPT_ENABLE_AIE |
                                 ETHERNET_DMA_CH0_INTERRUPT_ENABLE_ETIE |
                                 ETHERNET_DMA_CH0_INTERRUPT_ENABLE_ERIE));

    Ethernet_setDMAChannelTransmitStart(EMAC_BASE,ETHERNET_DMA_CHANNEL_NUM_0);


    SendPacket(pData,PACKET_LENGTH);

    while(1);

}

