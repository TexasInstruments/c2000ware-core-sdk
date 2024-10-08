//#############################################################################
//
// FILE:   ethernet_ex5_ptp_offload_master.c
//
// TITLE:  Ethernet PTP Offload Master Example
//
//! \addtogroup driver_example_cm_list
//! <h1> Ethernet PTP Offload Master </h1>
//!
//! This example configures the device in IEEE PTPv2 Master mode and sets the
//! options that are needed by the offload engine to operate such as the
//! \e domainNumber, \e LogSyncInterval among others. After that it enables
//! sending SYNC messages periodically according to the interval already set
//! previously.
//!
//! \b External \b Connections \n
//! This example programs the Ethernet module in PTP Offload Master mode.
//! The example project \e Ethernet \e PTP \e Offload \e Slave is intended to
//! be used along with this project to see the whole PTP Offload engine in
//! action. The second device is configured as \e Slave and both devices in
//! conjunction exchange Sync, DelayReq and DelayResp packets.
//!
//! Refer to the C28x CPU1 code of ethernet_config_c28x project for configuring
//! the PTP clock that drives the system time counter on the Ethernet module.
//!
//! \b Watch \b Variables \n
//!  - Ethernet_ptpDelayReqPktCount
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

#include "driverlib_cm.h"
#include "cm.h"

//
// This frequency is actually set in the c28x side code. If it is changed
// there, then the following value also needs to be updated since the
// timestamping module is initialized with the following values.
// Default value is 100 MHz.
//
#define PTP_REF_CLOCK_FREQ   100000000
#define PTP_REF_CLOCK_PERIOD 1000000000/PTP_REF_CLOCK_FREQ

#define NUM_PACKET_DESC_RX_APPLICATION      8U
#define ETHERNET_NO_OF_RX_PACKETS           8U
#define ETHERNET_MAX_PACKET_LENGTH          100U

static Ethernet_Handle emac_handle;
extern Ethernet_Device Ethernet_device_struct;
//
// Globals
//
uint8_t Ethernet_rxBuffer[ETHERNET_NO_OF_RX_PACKETS *
                          ETHERNET_MAX_PACKET_LENGTH];

//
// This function is a callback function called by the LLD to
// Get a Packet Buffer. Has to return a ETHERNET_Pkt_Desc Structure filled
// User or upper level stack can rewrite this API for their own use case
//
uint32_t Ethernet_numGetPacketBufferCallbackCustom = 0;
uint32_t Ethernet_numRxCallbackCustom = 0;
uint32_t Ethernet_ptpDelayReqPktCount = 0;
Ethernet_Pkt_Desc  pktDescriptorRXCustom[NUM_PACKET_DESC_RX_APPLICATION];

Ethernet_Pkt_Desc* Ethernet_getPacketBufferCustom(void)
{

    uint32_t shortIndex = (Ethernet_numGetPacketBufferCallbackCustom + 3) %
                          NUM_PACKET_DESC_RX_APPLICATION;

    Ethernet_numGetPacketBufferCallbackCustom++;

    pktDescriptorRXCustom[shortIndex].bufferLength =
                                  ETHERNET_MAX_PACKET_LENGTH;


    pktDescriptorRXCustom[shortIndex].dataBuffer =
                                      &Ethernet_device_struct.rxBuffer [
            (ETHERNET_MAX_PACKET_LENGTH * Ethernet_device_struct.rxBuffIndex)];

    //
    // Wrap around
    //
    Ethernet_device_struct.rxBuffIndex += 1U;
    Ethernet_device_struct.rxBuffIndex  =
                (Ethernet_device_struct.rxBuffIndex%ETHERNET_NO_OF_RX_PACKETS);

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
    // messageType == 0x1 indicates "DelayReq" packet.
    //
    if ((pPacket->dataBuffer[14] & 0x0F) == 0x1)
        Ethernet_ptpDelayReqPktCount++;

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
    // Initialize device clock and peripherals
    //
    CM_init();

    //
    // Hardcoded MAC Address
    //
    uint32_t mac_lower = 0x00F363A8;
    uint32_t mac_higher = 0x00800000;

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
    pInitCfg->pfcbRxPacket = &Ethernet_receivePacketCallbackCustom;
    pInitCfg->pfcbGetPacket = &Ethernet_getPacketBufferCustom;
    pInitCfg->rxBuffer = Ethernet_rxBuffer;
    //
    //Do global Interrupt Enable
    //
    (void)Interrupt_enableInProcessor();

    Ethernet_getHandle((Ethernet_Handle)1,pInitCfg , &emac_handle);
    //
    //Assign default ISRs
    //
    Interrupt_registerHandler(INT_EMAC_TX0, Ethernet_transmitISR);
    Interrupt_registerHandler(INT_EMAC_RX0, Ethernet_receiveISR);
    Interrupt_registerHandler(INT_EMAC,Ethernet_genericISR);
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
    // - Master
    // - Identify event messages (Sync, DelayReq)
    // - Identify PTP over Ethernet packets
    // - PTP version 2
    // - Digital Rollover
    //
    varPtpConfig = 0x0 |
            ETHERNET_MAC_TIMESTAMP_CONTROL_TSEVNTENA |
            ETHERNET_MAC_TIMESTAMP_CONTROL_TSMSTRENA |
            ETHERNET_MAC_TIMESTAMP_CONTROL_TSIPENA |
            ETHERNET_MAC_TIMESTAMP_CONTROL_TSVER2ENA |
            ETHERNET_MAC_TIMESTAMP_CONTROL_TSCTRLSSR;

    subSecondInc = PTP_REF_CLOCK_PERIOD;

    Ethernet_setConfigTimestampPTP(EMAC_BASE, varPtpConfig, subSecondInc);

    Ethernet_enableSysTimePTP(EMAC_BASE);

    Ethernet_setSysTimePTP(EMAC_BASE, 0x4132EDCA, 0x25a5a5a5);

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
    ptoConfigParams.srcPortId.id2 = 0xFFFF;

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
    // This is Master code, so enable sending of Sync packets.
    //
    ptoConfigParams.ptoAutoPtpSyncMode =
            ETHERNET_PTO_AUTO_SYNC_MESSAGE_ENABLE;

    //
    // Since this is Master code, enabling this switch will result in sending
    // of automatic DelayResp messages in response to the DelayReq messages
    // sent by the slave.
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

    while(1)
    {
    }
}
