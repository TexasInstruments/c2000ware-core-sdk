//#############################################################################
//
// FILE:   ethernet_ex5_ptp_offload_slave.c
//
// TITLE:  Ethernet PTP Offload Slave Example
//
//! \addtogroup driver_example_cm_list
//! <h1> Ethernet PTP Offload Slave </h1>
//!
//! This example configures the device in IEEE PTPv2 Slave mode and sets the
//! options that are needed by the offload engine to operate such as the
//! \e domainNumber, \e LogSyncInterval among others. After that it enables
//! sending DelayReq messages periodically for every configurable number of
//! Sync packets.
//!
//! \b External \b Connections \n
//! This example programs the Ethernet module in PTP Offload Slave mode.
//! The example project \e Ethernet \e PTP \e Offload \e Master is intended to
//! be used along with this project to see the whole PTP Offload engine in
//! action. The second device is configured as \e Slave and both devices in
//! conjunction exchange Sync, DelayReq and DelayResp packets.
//!
//! Refer to the C28x CPU1 code of ethernet_config_c28x project for configuring
//! the PTP clock that drives the system time counter on the Ethernet module.
//!
//! \b Watch \b Variables \n
//!  - Ethernet_ptpSyncPktCount
//!  - Ethernet_ptpDelayRespPktCount
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

#include "driverlib_cm.h"
#include "cm.h"

//
// This frequency is actually set in the c28x side code. If it is changed
// there, then the following value also needs to be updated since the
// timestamping module is initialized with the following values.
//
#define PTP_REF_CLOCK_FREQ   100000000
#define PTP_REF_CLOCK_PERIOD 1000000000/PTP_REF_CLOCK_FREQ

#define NUM_PACKET_DESC_RX_APPLICATION      8U
#define ETHERNET_NO_OF_RX_PACKETS           8U
#define ETHERNET_MAX_PACKET_LENGTH          100U

static Ethernet_Handle emac_handle;

extern Ethernet_Device Ethernet_device_struct;
extern void Ethernet_enableMACInterrupt(uint32_t base, uint32_t flags);

//
// Prototype definitions for this example
//
interrupt void Ethernet_customGenericISR(void);
// This function is a callback function called by the LLD to
// Get a Packet Buffer. Has to return a ETHERNET_Pkt_Desc Structure filled
// User or upper level stack can rewrite this API for their own use case
//
uint32_t Ethernet_numRxCallbackCustom = 0;
uint32_t Ethernet_ptpSyncPktCount = 0;
uint32_t Ethernet_ptpDelayRespPktCount = 0;
uint32_t Ethernet_customGenericInterruptCount = 0;
uint32_t Ethernet_numGetPacketBufferCallbackCustom;
Ethernet_Pkt_Desc  pktDescriptorRXCustom[NUM_PACKET_DESC_RX_APPLICATION];
uint8_t Ethernet_rxBuffer[ETHERNET_NO_OF_RX_PACKETS *
                          ETHERNET_MAX_PACKET_LENGTH];

Ethernet_Pkt_Desc* Ethernet_getPacketBufferCustom(void)
{

    uint32_t shortIndex = (Ethernet_numGetPacketBufferCallbackCustom + 3) %
                          NUM_PACKET_DESC_RX_APPLICATION;

    Ethernet_numGetPacketBufferCallbackCustom++;

    pktDescriptorRXCustom[shortIndex].bufferLength =
                                  ETHERNET_MAX_PACKET_LENGTH;


    pktDescriptorRXCustom[shortIndex].dataBuffer =
                                      &Ethernet_device_struct.rxBuffer[
            (ETHERNET_MAX_PACKET_LENGTH * Ethernet_device_struct.rxBuffIndex)];

    //
    // Wrap around
    //
    Ethernet_device_struct.rxBuffIndex += 1U;
    Ethernet_device_struct.rxBuffIndex  =
            (Ethernet_device_struct.rxBuffIndex % ETHERNET_NO_OF_RX_PACKETS);

    //
    // Usable from Address 0
    //
    pktDescriptorRXCustom[shortIndex].dataOffset = 0U;

    return (&(pktDescriptorRXCustom[shortIndex]));
}

Ethernet_Pkt_Desc* Ethernet_receivePacketCallbackCustom(
        Ethernet_Handle handleApplication,
        Ethernet_Pkt_Desc *pPacket)
{
    //
    // 14th byte in the received packet is 'messageType' field of
    // ptp frame format.
    //
    // messageType == 0x0 indicates "Sync" packet.
    // messageType == 0x9 indicates "DelayResp" packet.
    //
    if ((pPacket->dataBuffer[14] & 0x0F) == 0x0)
        Ethernet_ptpSyncPktCount++;
    else if ((pPacket->dataBuffer[14] & 0x0F) == 0x9)
        Ethernet_ptpDelayRespPktCount++;

    Ethernet_numRxCallbackCustom++;

    //
    // This is a placeholder for Application specific handling
    // We are replenishing the buffer received with another buffer
    //
    return  Ethernet_getPacketBufferCustom();
}

main(void)
{
    Ethernet_InitConfig *pInitCfg;
    Ethernet_InitInterfaceConfig initInterfaceConfig;
    uint32_t varPtpConfig = 0;
    float subSecondInc;

    //
    // Hardcoded MAC Address
    //
    uint32_t mac_lower = 0x00F263A8;
    uint32_t mac_higher = 0x00800000;

    //
    // Initialize device clock and peripherals
    //
    CM_init();

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

    Ethernet_getInitConfig(pInitCfg);

    pInitCfg->pfcbRxPacket=&Ethernet_receivePacketCallbackCustom;
    pInitCfg->pfcbGetPacket = &Ethernet_getPacketBufferCustom;
    //
    //Assign the Buffer to be used by the Low level driver for receiving
    //Packets. This should be accessible by the Ethernet DMA
    //
    pInitCfg->rxBuffer = Ethernet_rxBuffer;

    Ethernet_getHandle((Ethernet_Handle)1,pInitCfg, &emac_handle);
    //
    //Assign default ISRs
    //
    Interrupt_registerHandler(INT_EMAC_TX0, Ethernet_transmitISR);
    Interrupt_registerHandler(INT_EMAC_RX0, Ethernet_receiveISR);
    Interrupt_registerHandler(INT_EMAC, Ethernet_customGenericISR);

    //
    //Enable the default interrupt handlers
    //
    Interrupt_enable(INT_EMAC_TX0);
    Interrupt_enable(INT_EMAC_RX0);
    Interrupt_enable(INT_EMAC);

    Ethernet_setMACAddr(EMAC_BASE,
                        0,
                        mac_higher,
                        mac_lower,
                        ETHERNET_CHANNEL_0);

    //
    // We need to program this standard multicast address so that this device
    // identifies PTP over Ethernet packets correctly. "01:1B:19:00:00:00"
    //
    Ethernet_setMACAddr(EMAC_BASE,
                        1,
                        0x00000000,
                        0x00191B01,
                        ETHERNET_CHANNEL_0);

    //
    // Ethernet PTP module is configured with:
    // - Slave
    // - Identify event messages (Sync, DelayReq)
    // - Identify PTP over Ethernet packets
    // - PTP version 2
    // - Digital Rollover
    //
    varPtpConfig = ETHERNET_MAC_TIMESTAMP_CONTROL_TSEVNTENA |
                   ETHERNET_MAC_TIMESTAMP_CONTROL_TSIPENA |
                   ETHERNET_MAC_TIMESTAMP_CONTROL_TSVER2ENA |
                   ETHERNET_MAC_TIMESTAMP_CONTROL_TSCTRLSSR;

    subSecondInc = PTP_REF_CLOCK_PERIOD;

    Ethernet_setConfigTimestampPTP(EMAC_BASE, varPtpConfig, subSecondInc);

    Ethernet_enableSysTimePTP(EMAC_BASE);

    Ethernet_setSysTimePTP(EMAC_BASE, 0x4132EDCA, 0x25a5a5a5);

    //
    // Enable the timestamp interrupt to get an interrupt when timestamp is
    // captured for the outgoing DelayReq packet.
    //
    Ethernet_enableMACInterrupt(EMAC_BASE, ETHERNET_MAC_INTERRUPT_ENABLE_TSIE);

    //
    // PTP Offlad related configuration follows. This is used to automatically
    // assemble the PTP Header for the packets which will be ultimately sent
    // out by the PTP Offload engine.
    //

    Ethernet_PTPOffloadConfigParams ptoConfigParams = {0};

    //
    // "sourcePortIdentity" field in the PTP Header.
    //
    ptoConfigParams.srcPortId.id0 = 0xFFFFFFFF;
    ptoConfigParams.srcPortId.id1 = 0xFFFFFFFF;
    ptoConfigParams.srcPortId.id2 = 0x0000;

    //
    // "logMessageInterval" field in the PTP Header.
    //
    ptoConfigParams.logMsgIntervalConf.delayReqToSyncRatio = 2;
    ptoConfigParams.logMsgIntervalConf.logMinPdelayReqInterval= 0;
    ptoConfigParams.logMsgIntervalConf.logSyncInterval = 0;

    //
    // "domainNumber" field in the PTP Header.
    //
    ptoConfigParams.domainNumber = 0x00;

    //
    // Automatic Message reply switches follow
    //

    //
    // Peer to Peer mechanism not required, so disable sending of PDelayReq
    // packet.
    //
    ptoConfigParams.ptoAutoPDelayReqMode =
            ETHERNET_PTO_AUTO_P_DELAY_REQ_MESSAGE_DISABLE;

    //
    // This is slave code, so disable sending of Sync packets.
    //
    ptoConfigParams.ptoAutoPtpSyncMode =
            ETHERNET_PTO_AUTO_SYNC_MESSAGE_DISABLE;

    //
    // Since this is slave code, enabling this switch will result in sending
    // of automatic DelayReq messages in response to a configurable number of
    // Sync packets.
    //
    ptoConfigParams.ptoDelayReqRespMode =
            ETHERNET_PTO_DELAY_REQ_DELAY_RESP_ENABLE;

    //
    // Peer to Peer mechanism not required, so disable sending of PDelayResp
    // packet.
    //
    ptoConfigParams.ptoPDelayRespMode =
            ETHERNET_PTO_P_DELAY_RESP_MESSAGE_DISABLE;

    //
    // Pass the configuration to the Ethernet driver to program the hardware
    // with this.
    //
    Ethernet_setConfigPTPOffload(EMAC_BASE, ptoConfigParams);

    //
    // Finally, enable the PTP offload engine for above configuration to take
    // effect.
    //
    Ethernet_enableDisablePTPOffload(EMAC_BASE, ETHERNET_PTP_OFFLOAD_ENABLE);

    //
    // Wait forever. Sending of the messages is handled by the PTP Offload
    // hardware.
    //
    while(1)
    {
    }
}
interrupt void Ethernet_customGenericISR(void)
{
    //
    // Increment the generic interrupt receive count
    //
    Ethernet_customGenericInterruptCount++;

    if(true == Ethernet_isTimestampIntActive())
    {
        //
        // Placeholder to call any Timestamp Interrupt Handler API.
        //
        // Following is a dummy implementation for a case
        // when tx timestamp is captured for an outgoing packet
        // in PTP Offload mode. Refer to
        // individual APIs for more information.
        // Note: For this particular case, when the interrupt
        // is generated for transmit timestamp capture
        // in PTP offload mode the Interrupt is cleared
        // only when the actual timestamp
        // is read from the Timestamp Status
        // Seconds and Nanoseconds registers
        //
        uint32_t seconds, nanoSeconds;

        //
        // Check if the transmit timestamp status is set.
        //
        if(true == Ethernet_isTransmitTimestampStatusSet())
        {
           //
           // Read the timestamp for the transmitted packet to
           //clear this interrupt
           //
           Ethernet_getOneStepTransmitTimestampPTP(
                       Ethernet_device_struct.baseAddresses.enet_base,
                       &seconds,
                       &nanoSeconds);
        }
   }

}
