//###########################################################################
//
// FILE:    emac_eqos_hw.h
//
// TITLE:   Definitions for the EMAC registers.
//
//###########################################################################
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

#ifndef ETHERNET_EQOS_HW_H
#define ETHERNET_EQOS_HW_H

//*****************************************************************************
//
// The following are defines for the EMAC register offsets
//
//*****************************************************************************
#define ETHERNET_O_MAC_CONFIGURATION  0x0U
#define ETHERNET_O_MAC_EXT_CONFIGURATION  0x4U
#define ETHERNET_O_MAC_PACKET_FILTER  0x8U
#define ETHERNET_O_MAC_WATCHDOG_TIMEOUT  0xCU
#define ETHERNET_O_MAC_HASH_TABLE_REG0  0x10U
#define ETHERNET_O_MAC_HASH_TABLE_REG1  0x14U
#define ETHERNET_O_MAC_VLAN_TAG_CTRL  0x50U
#define ETHERNET_O_MAC_VLAN_TAG_DATA  0x54U
#define ETHERNET_O_MAC_VLAN_HASH_TABLE  0x58U
#define ETHERNET_O_MAC_VLAN_INCL      0x60U
#define ETHERNET_O_MAC_INNER_VLAN_INCL  0x64U
#define ETHERNET_O_MAC_Q0_TX_FLOW_CTRL  0x70U
#define ETHERNET_O_MAC_RX_FLOW_CTRL   0x90U
#define ETHERNET_O_MAC_RXQ_CTRL4  0x94U
#define ETHERNET_O_MAC_RXQ_CTRL0      0xA0U
#define ETHERNET_O_MAC_RXQ_CTRL1      0xA4U
#define ETHERNET_O_MAC_RXQ_CTRL2      0xA8U
#define ETHERNET_O_MAC_INTERRUPT_STATUS  0xB0U
#define ETHERNET_O_MAC_INTERRUPT_ENABLE  0xB4U
#define ETHERNET_O_MAC_RX_TX_STATUS   0xB8U
#define ETHERNET_O_MAC_PMT_CONTROL_STATUS  0xC0U
#define ETHERNET_O_MAC_RWK_PACKET_FILTER  0xC4U
#define ETHERNET_O_MAC_LPI_CONTROL_STATUS  0xD0U
#define ETHERNET_O_MAC_LPI_TIMERS_CONTROL  0xD4U
#define ETHERNET_O_MAC_LPI_ENTRY_TIMER  0xD8U
#define ETHERNET_O_MAC_1US_TIC_COUNTER  0xDCU
#define ETHERNET_O_MAC_VERSION        0x110U
#define ETHERNET_O_MAC_DEBUG          0x114U
#define ETHERNET_O_MAC_HW_FEATURE0    0x11CU
#define ETHERNET_O_MAC_HW_FEATURE1    0x120U
#define ETHERNET_O_MAC_HW_FEATURE2    0x124U
#define ETHERNET_O_MAC_HW_FEATURE3    0x128U
#define ETHERNET_O_MAC_MDIO_ADDRESS   0x200U
#define ETHERNET_O_MAC_MDIO_DATA      0x204U
#define ETHERNET_O_MAC_ARP_ADDRESS    0x210U
#define ETHERNET_O_MAC_ADDRESS0_HIGH  0x300U
#define ETHERNET_O_MAC_ADDRESS0_LOW   0x304U
#define ETHERNET_O_MAC_ADDRESS1_HIGH  0x308U
#define ETHERNET_O_MAC_ADDRESS1_LOW   0x30CU
#define ETHERNET_O_MAC_ADDRESS2_HIGH  0x310U
#define ETHERNET_O_MAC_ADDRESS2_LOW   0x314U
#define ETHERNET_O_MAC_ADDRESS3_HIGH  0x318U
#define ETHERNET_O_MAC_ADDRESS3_LOW   0x31CU
#define ETHERNET_O_MAC_ADDRESS4_HIGH  0x320U
#define ETHERNET_O_MAC_ADDRESS4_LOW  0x324U
#define ETHERNET_O_MAC_ADDRESS5_HIGH  0x328U
#define ETHERNET_O_MAC_ADDRESS5_LOW  0x32CU
#define ETHERNET_O_MAC_ADDRESS6_HIGH  0x330U
#define ETHERNET_O_MAC_ADDRESS6_LOW  0x334U
#define ETHERNET_O_MAC_ADDRESS7_HIGH  0x338U
#define ETHERNET_O_MAC_ADDRESS7_LOW  0x33CU
#define ETHERNET_O_MMC_CONTROL        0x700U
#define ETHERNET_O_MMC_RX_INTERRUPT   0x704U
#define ETHERNET_O_MMC_TX_INTERRUPT   0x708U
#define ETHERNET_O_MMC_RX_INTERRUPT_MASK  0x70CU
#define ETHERNET_O_MMC_TX_INTERRUPT_MASK  0x710U
#define ETHERNET_O_TX_OCTET_COUNT_GOOD_BAD  0x714U
#define ETHERNET_O_TX_PACKET_COUNT_GOOD_BAD  0x718U
#define ETHERNET_O_TX_BROADCAST_PACKETS_GOOD  0x71CU
#define ETHERNET_O_TX_MULTICAST_PACKETS_GOOD  0x720U
#define ETHERNET_O_TX_64OCTETS_PACKETS_GOOD_BAD  0x724U
#define ETHERNET_O_TX_65TO127OCTETS_PACKETS_GOOD_BAD  0x728U
#define ETHERNET_O_TX_128TO255OCTETS_PACKETS_GOOD_BAD  0x72CU
#define ETHERNET_O_TX_256TO511OCTETS_PACKETS_GOOD_BAD  0x730U
#define ETHERNET_O_TX_512TO1023OCTETS_PACKETS_GOOD_BAD  0x734U
#define ETHERNET_O_TX_1024TOMAXOCTETS_PACKETS_GOOD_BAD  0x738U
#define ETHERNET_O_TX_UNICAST_PACKETS_GOOD_BAD  0x73CU
#define ETHERNET_O_TX_MULTICAST_PACKETS_GOOD_BAD  0x740U
#define ETHERNET_O_TX_BROADCAST_PACKETS_GOOD_BAD  0x744U
#define ETHERNET_O_TX_UNDERFLOW_ERROR_PACKETS  0x748U
#define ETHERNET_O_TX_SINGLE_COLLISION_GOOD_PACKETS  0x74CU
#define ETHERNET_O_TX_MULTIPLE_COLLISION_GOOD_PACKETS  0x750U
#define ETHERNET_O_TX_DEFERRED_PACKETS  0x754U
#define ETHERNET_O_TX_LATE_COLLISION_PACKETS  0x758U
#define ETHERNET_O_TX_EXCESSIVE_COLLISION_PACKETS  0x75CU
#define ETHERNET_O_TX_CARRIER_ERROR_PACKETS  0x760U
#define ETHERNET_O_TX_OCTET_COUNT_GOOD  0x764U
#define ETHERNET_O_TX_PACKET_COUNT_GOOD  0x768U
#define ETHERNET_O_TX_EXCESSIVE_DEFERRAL_ERROR  0x76CU
#define ETHERNET_O_TX_PAUSE_PACKETS   0x770U
#define ETHERNET_O_TX_VLAN_PACKETS_GOOD  0x774U
#define ETHERNET_O_TX_OSIZE_PACKETS_GOOD  0x778U
#define ETHERNET_O_RX_PACKETS_COUNT_GOOD_BAD  0x780U
#define ETHERNET_O_RX_OCTET_COUNT_GOOD_BAD  0x784U
#define ETHERNET_O_RX_OCTET_COUNT_GOOD  0x788U
#define ETHERNET_O_RX_BROADCAST_PACKETS_GOOD  0x78CU
#define ETHERNET_O_RX_MULTICAST_PACKETS_GOOD  0x790U
#define ETHERNET_O_RX_CRC_ERROR_PACKETS  0x794U
#define ETHERNET_O_RX_ALIGNMENT_ERROR_PACKETS  0x798U
#define ETHERNET_O_RX_RUNT_ERROR_PACKETS  0x79CU
#define ETHERNET_O_RX_JABBER_ERROR_PACKETS  0x7A0U
#define ETHERNET_O_RX_UNDERSIZE_PACKETS_GOOD  0x7A4U
#define ETHERNET_O_RX_OVERSIZE_PACKETS_GOOD  0x7A8U
#define ETHERNET_O_RX_64OCTETS_PACKETS_GOOD_BAD  0x7ACU
#define ETHERNET_O_RX_65TO127OCTETS_PACKETS_GOOD_BAD  0x7B0U
#define ETHERNET_O_RX_128TO255OCTETS_PACKETS_GOOD_BAD  0x7B4U
#define ETHERNET_O_RX_256TO511OCTETS_PACKETS_GOOD_BAD  0x7B8U
#define ETHERNET_O_RX_512TO1023OCTETS_PACKETS_GOOD_BAD  0x7BCU
#define ETHERNET_O_RX_1024TOMAXOCTETS_PACKETS_GOOD_BAD  0x7C0U
#define ETHERNET_O_RX_UNICAST_PACKETS_GOOD  0x7C4U
#define ETHERNET_O_RX_LENGTH_ERROR_PACKETS  0x7C8U
#define ETHERNET_O_RX_OUT_OF_RANGE_TYPE_PACKETS  0x7CCU
#define ETHERNET_O_RX_PAUSE_PACKETS   0x7D0U
#define ETHERNET_O_RX_FIFO_OVERFLOW_PACKETS  0x7D4U
#define ETHERNET_O_RX_VLAN_PACKETS_GOOD_BAD  0x7D8U
#define ETHERNET_O_RX_WATCHDOG_ERROR_PACKETS  0x7DCU
#define ETHERNET_O_RX_RECEIVE_ERROR_PACKETS  0x7E0U
#define ETHERNET_O_RX_CONTROL_PACKETS_GOOD  0x7E4U
#define ETHERNET_O_TX_LPI_USEC_CNTR   0x7ECU
#define ETHERNET_O_TX_LPI_TRAN_CNTR   0x7F0U
#define ETHERNET_O_RX_LPI_USEC_CNTR   0x7F4U
#define ETHERNET_O_RX_LPI_TRAN_CNTR   0x7F8U
#define ETHERNET_O_MMC_IPC_RX_INTERRUPT_MASK  0x800U
#define ETHERNET_O_MMC_IPC_RX_INTERRUPT  0x808U
#define ETHERNET_O_RXIPV4_GOOD_PACKETS  0x810U
#define ETHERNET_O_RXIPV4_HEADER_ERROR_PACKETS  0x814U
#define ETHERNET_O_RXIPV4_NO_PAYLOAD_PACKETS  0x818U
#define ETHERNET_O_RXIPV4_FRAGMENTED_PACKETS  0x81CU
#define ETHERNET_O_RXIPV4_UDP_CHECKSUM_DISABLED_PACKETS  0x820U
#define ETHERNET_O_RXIPV6_GOOD_PACKETS  0x824U
#define ETHERNET_O_RXIPV6_HEADER_ERROR_PACKETS  0x828U
#define ETHERNET_O_RXIPV6_NO_PAYLOAD_PACKETS  0x82CU
#define ETHERNET_O_RXUDP_GOOD_PACKETS  0x830U
#define ETHERNET_O_RXUDP_ERROR_PACKETS  0x834U
#define ETHERNET_O_RXTCP_GOOD_PACKETS  0x838U
#define ETHERNET_O_RXTCP_ERROR_PACKETS  0x83CU
#define ETHERNET_O_RXICMP_GOOD_PACKETS  0x840U
#define ETHERNET_O_RXICMP_ERROR_PACKETS  0x844U
#define ETHERNET_O_RXIPV4_GOOD_OCTETS  0x850U
#define ETHERNET_O_RXIPV4_HEADER_ERROR_OCTETS  0x854U
#define ETHERNET_O_RXIPV4_NO_PAYLOAD_OCTETS  0x858U
#define ETHERNET_O_RXIPV4_FRAGMENTED_OCTETS  0x85CU
#define ETHERNET_O_RXIPV4_UDP_CHECKSUM_DISABLE_OCTETS  0x860U
#define ETHERNET_O_RXIPV6_GOOD_OCTETS  0x864U
#define ETHERNET_O_RXIPV6_HEADER_ERROR_OCTETS  0x868U
#define ETHERNET_O_RXIPV6_NO_PAYLOAD_OCTETS  0x86CU
#define ETHERNET_O_RXUDP_GOOD_OCTETS  0x870U
#define ETHERNET_O_RXUDP_ERROR_OCTETS  0x874U
#define ETHERNET_O_RXTCP_GOOD_OCTETS  0x878U
#define ETHERNET_O_RXTCP_ERROR_OCTETS  0x87CU
#define ETHERNET_O_RXICMP_GOOD_OCTETS  0x880U
#define ETHERNET_O_RXICMP_ERROR_OCTETS  0x884U
#define ETHERNET_O_MAC_L3_L4_CONTROL0  0x900U
#define ETHERNET_O_MAC_LAYER4_ADDRESS0  0x904U
#define ETHERNET_O_MAC_LAYER3_ADDR0_REG0  0x910U
#define ETHERNET_O_MAC_LAYER3_ADDR1_REG0  0x914U
#define ETHERNET_O_MAC_LAYER3_ADDR2_REG0  0x918U
#define ETHERNET_O_MAC_LAYER3_ADDR3_REG0  0x91CU
#define ETHERNET_O_MAC_L3_L4_CONTROL1  0x930U
#define ETHERNET_O_MAC_LAYER4_ADDRESS1  0x934U
#define ETHERNET_O_MAC_LAYER3_ADDR0_REG1  0x940U
#define ETHERNET_O_MAC_LAYER3_ADDR1_REG1  0x944U
#define ETHERNET_O_MAC_LAYER3_ADDR2_REG1  0x948U
#define ETHERNET_O_MAC_LAYER3_ADDR3_REG1  0x94CU
#define ETHERNET_O_MAC_L3_L4_CONTROL2  0x960U
#define ETHERNET_O_MAC_LAYER4_ADDRESS2  0x964U
#define ETHERNET_O_MAC_LAYER3_ADDR0_REG2  0x970U
#define ETHERNET_O_MAC_LAYER3_ADDR1_REG2  0x974U
#define ETHERNET_O_MAC_LAYER3_ADDR2_REG2  0x978U
#define ETHERNET_O_MAC_LAYER3_ADDR3_REG2  0x97CU
#define ETHERNET_O_MAC_L3_L4_CONTROL3  0x990U
#define ETHERNET_O_MAC_LAYER4_ADDRESS3  0x994U
#define ETHERNET_O_MAC_LAYER3_ADDR0_REG3  0x9A0U
#define ETHERNET_O_MAC_LAYER3_ADDR1_REG3  0x9A4U
#define ETHERNET_O_MAC_LAYER3_ADDR2_REG3  0x9A8U
#define ETHERNET_O_MAC_LAYER3_ADDR3_REG3  0x9ACU
#define ETHERNET_O_MAC_TIMESTAMP_CONTROL  0xB00U
#define ETHERNET_O_MAC_SUB_SECOND_INCREMENT  0xB04U
#define ETHERNET_O_MAC_SYSTEM_TIME_SECONDS  0xB08U
#define ETHERNET_O_MAC_SYSTEM_TIME_NANOSECONDS  0xB0CU
#define ETHERNET_O_MAC_SYSTEM_TIME_SECONDS_UPDATE  0xB10U
#define ETHERNET_O_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE  0xB14U
#define ETHERNET_O_MAC_TIMESTAMP_ADDEND  0xB18U
#define ETHERNET_O_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS  0xB1CU
#define ETHERNET_O_MAC_TIMESTAMP_STATUS  0xB20U
#define ETHERNET_O_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS  0xB30U
#define ETHERNET_O_MAC_TX_TIMESTAMP_STATUS_SECONDS  0xB34U
#define ETHERNET_O_MAC_AUXILIARY_CONTROL  0xB40U
#define ETHERNET_O_MAC_AUXILIARY_TIMESTAMP_NANOSECONDS  0xB48U
#define ETHERNET_O_MAC_AUXILIARY_TIMESTAMP_SECONDS  0xB4CU
#define ETHERNET_O_MAC_TIMESTAMP_INGRESS_ASYM_CORR  0xB50U
#define ETHERNET_O_MAC_TIMESTAMP_EGRESS_ASYM_CORR  0xB54U
#define ETHERNET_O_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND  0xB58U
#define ETHERNET_O_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND  0xB5CU
#define ETHERNET_O_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC  0xB60U
#define ETHERNET_O_MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC  0xB64U
#define ETHERNET_O_MAC_PPS_CONTROL    0xB70U
#define ETHERNET_O_MAC_PTO_CONTROL    0xBC0U
#define ETHERNET_O_MAC_SOURCE_PORT_IDENTITY0  0xBC4U
#define ETHERNET_O_MAC_SOURCE_PORT_IDENTITY1  0xBC8U
#define ETHERNET_O_MAC_SOURCE_PORT_IDENTITY2  0xBCCU
#define ETHERNET_O_MAC_LOG_MESSAGE_INTERVAL  0xBD0U
#define ETHERNET_O_DMA_MODE           0x1000U
#define ETHERNET_O_DMA_SYSBUS_MODE    0x1004U
#define ETHERNET_O_DMA_INTERRUPT_STATUS  0x1008U
#define ETHERNET_O_DMA_DEBUG_STATUS0  0x100CU
#define ETHERNET_O_DMA_CH0_CONTROL    0x1100U
#define ETHERNET_O_DMA_CH0_TX_CONTROL  0x1104U
#define ETHERNET_O_DMA_CH0_RX_CONTROL  0x1108U
#define ETHERNET_O_DMA_CH0_TXDESC_LIST_ADDRESS  0x1114U
#define ETHERNET_O_DMA_CH0_RXDESC_LIST_ADDRESS  0x111CU
#define ETHERNET_O_DMA_CH0_TXDESC_TAIL_POINTER  0x1120U
#define ETHERNET_O_DMA_CH0_RXDESC_TAIL_POINTER  0x1128U
#define ETHERNET_O_DMA_CH0_TXDESC_RING_LENGTH  0x112CU
#define ETHERNET_O_DMA_CH0_RXDESC_RING_LENGTH  0x1130U
#define ETHERNET_O_DMA_CH0_INTERRUPT_ENABLE  0x1134U
#define ETHERNET_O_DMA_CH0_RX_INTERRUPT_WATCHDOG_TIMER  0x1138U
#define ETHERNET_O_DMA_CH0_CURRENT_APP_TXDESC  0x1144U
#define ETHERNET_O_DMA_CH0_CURRENT_APP_RXDESC  0x114CU
#define ETHERNET_O_DMA_CH0_CURRENT_APP_TXBUFFER  0x1154U
#define ETHERNET_O_DMA_CH0_CURRENT_APP_RXBUFFER  0x115CU
#define ETHERNET_O_DMA_CH0_STATUS     0x1160U
#define ETHERNET_O_DMA_CH0_MISS_FRAME_CNT  0x116CU
#define ETHERNET_O_DMA_CH1_CONTROL    0x1180U
#define ETHERNET_O_DMA_CH1_TX_CONTROL  0x1184U
#define ETHERNET_O_DMA_CH1_RX_CONTROL  0x1188U
#define ETHERNET_O_DMA_CH1_TXDESC_LIST_ADDRESS  0x1194U
#define ETHERNET_O_DMA_CH1_RXDESC_LIST_ADDRESS  0x119CU
#define ETHERNET_O_DMA_CH1_TXDESC_TAIL_POINTER  0x11A0U
#define ETHERNET_O_DMA_CH1_RXDESC_TAIL_POINTER  0x11A8U
#define ETHERNET_O_DMA_CH1_TXDESC_RING_LENGTH  0x11ACU
#define ETHERNET_O_DMA_CH1_RXDESC_RING_LENGTH  0x11B0U
#define ETHERNET_O_DMA_CH1_INTERRUPT_ENABLE  0x11B4U
#define ETHERNET_O_DMA_CH1_RX_INTERRUPT_WATCHDOG_TIMER  0x11B8U
#define ETHERNET_O_DMA_CH1_CURRENT_APP_TXDESC  0x11C4U
#define ETHERNET_O_DMA_CH1_CURRENT_APP_RXDESC  0x11CCU
#define ETHERNET_O_DMA_CH1_CURRENT_APP_TXBUFFER  0x11D4U
#define ETHERNET_O_DMA_CH1_CURRENT_APP_RXBUFFER  0x11DCU
#define ETHERNET_O_DMA_CH1_STATUS     0x11E0U
#define ETHERNET_O_DMA_CH1_MISS_FRAME_CNT  0x11ECU
#define ETHERNET_O_MTL_OPERATION_MODE  0xC00U
#define ETHERNET_O_MTL_DBG_CTL        0xC08U
#define ETHERNET_O_MTL_DBG_STS        0xC0CU
#define ETHERNET_O_MTL_FIFO_DEBUG_DATA  0xC10U
#define ETHERNET_O_MTL_INTERRUPT_STATUS  0xC20U
#define ETHERNET_O_MTL_RXQ_DMA_MAP0   0xC30U
#define ETHERNET_O_MTL_TXQ0_OPERATION_MODE  0xD00U
#define ETHERNET_O_MTL_TXQ0_UNDERFLOW  0xD04U
#define ETHERNET_O_MTL_TXQ0_DEBUG     0xD08U
#define ETHERNET_O_MTL_TXQ0_ETS_STATUS  0xD14U
#define ETHERNET_O_MTL_TXQ0_QUANTUM_WEIGHT  0xD18U
#define ETHERNET_O_MTL_Q0_INTERRUPT_CONTROL_STATUS  0xD2CU
#define ETHERNET_O_MTL_RXQ0_OPERATION_MODE  0xD30U
#define ETHERNET_O_MTL_RXQ0_MISSED_PACKET_OVERFLOW_CNT  0xD34U
#define ETHERNET_O_MTL_RXQ0_DEBUG     0xD38U
#define ETHERNET_O_MTL_RXQ0_CONTROL   0xD3CU
#define ETHERNET_O_MTL_TXQ1_OPERATION_MODE  0xD40U
#define ETHERNET_O_MTL_TXQ1_UNDERFLOW  0xD44U
#define ETHERNET_O_MTL_TXQ1_DEBUG     0xD48U
#define ETHERNET_O_MTL_TXQ1_ETS_STATUS  0xD54U
#define ETHERNET_O_MTL_TXQ1_QUANTUM_WEIGHT  0xD58U
#define ETHERNET_O_MTL_Q1_INTERRUPT_CONTROL_STATUS  0xD6CU
#define ETHERNET_O_MTL_RXQ1_OPERATION_MODE  0xD70U
#define ETHERNET_O_MTL_RXQ1_MISSED_PACKET_OVERFLOW_CNT  0xD74U
#define ETHERNET_O_MTL_RXQ1_DEBUG     0xD78U
#define ETHERNET_O_MTL_RXQ1_CONTROL   0xD7CU

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_CONFIGURATION register
//
//*****************************************************************************
#define ETHERNET_MAC_CONFIGURATION_RE  0x1U         // Receiver Enable
#define ETHERNET_MAC_CONFIGURATION_TE  0x2U         // Transmitter Enable
#define ETHERNET_MAC_CONFIGURATION_PRELEN_S  2U
#define ETHERNET_MAC_CONFIGURATION_PRELEN_M  0xCU         // Preamble Length for Transmit
                                               // packets
#define ETHERNET_MAC_CONFIGURATION_DC  0x10U        // Deferral Check
#define ETHERNET_MAC_CONFIGURATION_BL_S  5U
#define ETHERNET_MAC_CONFIGURATION_BL_M  0x60U        // Back-Off Limit
#define ETHERNET_MAC_CONFIGURATION_DR  0x100U       // Disable Retry
#define ETHERNET_MAC_CONFIGURATION_DCRS  0x200U       // Disable Carrier Sense During
                                               // Transmission
#define ETHERNET_MAC_CONFIGURATION_DO  0x400U       // Disable Receive Own
#define ETHERNET_MAC_CONFIGURATION_ECRSFD  0x800U       // Enable Carrier Sense Before
                                               // Transmission in Full-Duplex
                                               // Mode
#define ETHERNET_MAC_CONFIGURATION_LM  0x1000U      // Loopback Mode
#define ETHERNET_MAC_CONFIGURATION_DM  0x2000U      // Duplex Mode
#define ETHERNET_MAC_CONFIGURATION_FES  0x4000U      // Speed
#define ETHERNET_MAC_CONFIGURATION_PS  0x8000U      // Port Select
#define ETHERNET_MAC_CONFIGURATION_JE  0x10000U     // Jumbo Packet Enable
#define ETHERNET_MAC_CONFIGURATION_JD  0x20000U     // Jabber Disable
#define ETHERNET_MAC_CONFIGURATION_WD  0x80000U     // Watchdog Disable
#define ETHERNET_MAC_CONFIGURATION_ACS  0x100000U    // Automatic Pad or CRC
                                               // Stripping
#define ETHERNET_MAC_CONFIGURATION_CST  0x200000U    // CRC stripping for Type
                                               // packets
#define ETHERNET_MAC_CONFIGURATION_S2KP  0x400000U    // IEEE 802.3as Support for 2K
                                               // Packets
#define ETHERNET_MAC_CONFIGURATION_GPSLCE  0x800000U    // Giant Packet Size Limit
                                               // Control Enable
#define ETHERNET_MAC_CONFIGURATION_IPG_S  24U
#define ETHERNET_MAC_CONFIGURATION_IPG_M  0x7000000U   // Inter-Packet Gap
#define ETHERNET_MAC_CONFIGURATION_IPC  0x8000000U   // Checksum Offload
#define ETHERNET_MAC_CONFIGURATION_SARC_S  28U
#define ETHERNET_MAC_CONFIGURATION_SARC_M  0x70000000U  // Source Address Insertion or
                                               // Replacement Control
#define ETHERNET_MAC_CONFIGURATION_ARPEN  0x80000000U  // ARP Offload Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_EXT_CONFIGURATION register
//
//*****************************************************************************
#define ETHERNET_MAC_EXT_CONFIGURATION_GPSL_S  0U
#define ETHERNET_MAC_EXT_CONFIGURATION_GPSL_M  0x3FFFU      // Giant Packet Size Limit
#define ETHERNET_MAC_EXT_CONFIGURATION_DCRCC  0x10000U     // Disable CRC Checking for
                                               // Received Packets
#define ETHERNET_MAC_EXT_CONFIGURATION_SPEN  0x20000U     // Slow Protocol Detection
                                               // Enable
#define ETHERNET_MAC_EXT_CONFIGURATION_USP  0x40000U     // Unicast Slow Protocol Packet
                                               // Detect
#define ETHERNET_MAC_EXT_CONFIGURATION_HDSMS_S  20U
#define ETHERNET_MAC_EXT_CONFIGURATION_HDSMS_M  0x700000U    // Maximum Size for Splitting
                                               // the Header Data
#define ETHERNET_MAC_EXT_CONFIGURATION_EIPGEN  0x1000000U   // Extended Inter-Packet Gap
                                               // Enable
#define ETHERNET_MAC_EXT_CONFIGURATION_EIPG_S  25U
#define ETHERNET_MAC_EXT_CONFIGURATION_EIPG_M  0x3E000000U  // Extended Inter-Packet Gap

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_PACKET_FILTER register
//
//*****************************************************************************
#define ETHERNET_MAC_PACKET_FILTER_PR  0x1U         // Promiscuous Mode
#define ETHERNET_MAC_PACKET_FILTER_HUC  0x2U         // Hash Unicast
#define ETHERNET_MAC_PACKET_FILTER_HMC  0x4U         // Hash Multicast
#define ETHERNET_MAC_PACKET_FILTER_DAIF  0x8U         // DA Inverse Filtering
#define ETHERNET_MAC_PACKET_FILTER_PM  0x10U        // Pass All Multicast
#define ETHERNET_MAC_PACKET_FILTER_DBF  0x20U        // Disable Broadcast Packets
#define ETHERNET_MAC_PACKET_FILTER_PCF_S  6U
#define ETHERNET_MAC_PACKET_FILTER_PCF_M  0xC0U        // Pass Control Packets
#define ETHERNET_MAC_PACKET_FILTER_SAIF  0x100U       // SA Inverse Filtering
#define ETHERNET_MAC_PACKET_FILTER_SAF  0x200U       // Source Address Filter Enable
#define ETHERNET_MAC_PACKET_FILTER_HPF  0x400U       // Hash or Perfect Filter
#define ETHERNET_MAC_PACKET_FILTER_VTFE  0x10000U     // VLAN Tag Filter Enable
#define ETHERNET_MAC_PACKET_FILTER_IPFE  0x100000U    // Layer 3 and Layer 4 Filter
                                               // Enable
#define ETHERNET_MAC_PACKET_FILTER_DNTU  0x200000U    // Drop Non-TCP/UDP over IP
                                               // Packets
#define ETHERNET_MAC_PACKET_FILTER_RA  0x80000000U  // Receive All

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_WATCHDOG_TIMEOUT register
//
//*****************************************************************************
#define ETHERNET_MAC_WATCHDOG_TIMEOUT_WTO_S  0U
#define ETHERNET_MAC_WATCHDOG_TIMEOUT_WTO_M  0xFU         // Watchdog Timeout
#define ETHERNET_MAC_WATCHDOG_TIMEOUT_PWE  0x100U       // Programmable Watchdog Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_VLAN_TAG_CTRL register
//
//*****************************************************************************
#define ETHERNET_MAC_VLAN_TAG_CTRL_OB  0x1U         // Operation Busy
#define ETHERNET_MAC_VLAN_TAG_CTRL_CT  0x2U         // Command Type
#define ETHERNET_MAC_VLAN_TAG_CTRL_OFS_S  2U
#define ETHERNET_MAC_VLAN_TAG_CTRL_OFS_M  0x7CU        // Offset
#define ETHERNET_MAC_VLAN_TAG_CTRL_ETV  0x10000U     // Enable 12-Bit VLAN Tag
                                               // Comparison
#define ETHERNET_MAC_VLAN_TAG_CTRL_VTIM  0x20000U     // VLAN Tag Inverse Match Enable
#define ETHERNET_MAC_VLAN_TAG_CTRL_ESVL  0x40000U     // Enable S-VLAN
#define ETHERNET_MAC_VLAN_TAG_CTRL_ERSVLM  0x80000U     // Enable Receive S-VLAN Match
#define ETHERNET_MAC_VLAN_TAG_CTRL_DOVLTC  0x100000U    // Disable VLAN Type Check
#define ETHERNET_MAC_VLAN_TAG_CTRL_EVLS_S  21U
#define ETHERNET_MAC_VLAN_TAG_CTRL_EVLS_M  0x600000U    // Enable VLAN Tag Stripping on
                                               // Receive
#define ETHERNET_MAC_VLAN_TAG_CTRL_EVLRXS  0x1000000U   // Enable VLAN Tag in Rx status
#define ETHERNET_MAC_VLAN_TAG_CTRL_VTHM  0x2000000U   // VLAN Tag Hash Table Match
                                               // Enable
#define ETHERNET_MAC_VLAN_TAG_CTRL_EDVLP  0x4000000U   // Enable Double VLAN Processing
#define ETHERNET_MAC_VLAN_TAG_CTRL_ERIVLT  0x8000000U   // Enable Inner VLAN Tag
#define ETHERNET_MAC_VLAN_TAG_CTRL_EIVLS_S  28U
#define ETHERNET_MAC_VLAN_TAG_CTRL_EIVLS_M  0x30000000U  // Enable Inner VLAN Tag
                                               // Stripping on Receive
#define ETHERNET_MAC_VLAN_TAG_CTRL_EIVLRXS  0x80000000U  // Enable Inner VLAN Tag in Rx
                                               // Status

//*****************************************************************************
// The following are defines for the bit fields in the MAC_VLAN_TAG_DATA register
//
//*****************************************************************************
#define ETHERNET_MAC_VLAN_TAG_DATA_DATA_15_0_S  0U
#define ETHERNET_MAC_VLAN_TAG_DATA_DATA_15_0_M  0xFFFFU      // VLAN Tag ID
#define ETHERNET_MAC_VLAN_TAG_DATA_DATA_16  0x10000U     // VLAN Tag Enable
#define ETHERNET_MAC_VLAN_TAG_DATA_DATA_17  0x20000U     // 12bits or 16bits VLAN
                                               // comparison
#define ETHERNET_MAC_VLAN_TAG_DATA_DATA_18  0x40000U     // Disable VLAN Type Comparison
#define ETHERNET_MAC_VLAN_TAG_DATA_DATA_19  0x80000U     // Enable S-VLAN Match for
                                               // received Frames
#define ETHERNET_MAC_VLAN_TAG_DATA_DATA_20  0x100000U    // Enable Inner VLAN Tag
                                               // Comparison
#define ETHERNET_MAC_VLAN_TAG_DATA_DATA_24  0x1000000U   // DMA Channel Number Enable
#define ETHERNET_MAC_VLAN_TAG_DATA_DATA_25  0x2000000U   // DMA Channel Number

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_VLAN_HASH_TABLE register
//
//*****************************************************************************
#define ETHERNET_MAC_VLAN_HASH_TABLE_VLHT_S  0U
#define ETHERNET_MAC_VLAN_HASH_TABLE_VLHT_M  0xFFFFU      // VLAN Hash Table

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_VLAN_INCL register
//
//*****************************************************************************
#define ETHERNET_MAC_VLAN_INCL_VLT_S  0U
#define ETHERNET_MAC_VLAN_INCL_VLT_M  0xFFFFU      // VLAN Tag for Transmit Packets
#define ETHERNET_MAC_VLAN_INCL_VLC_S  16U
#define ETHERNET_MAC_VLAN_INCL_VLC_M  0x30000U     // VLAN Tag Control in Transmit
                                               // Packets
#define ETHERNET_MAC_VLAN_INCL_VLP    0x40000U     // VLAN Priority Control
#define ETHERNET_MAC_VLAN_INCL_CSVL   0x80000U     // C-VLAN or S-VLAN
#define ETHERNET_MAC_VLAN_INCL_VLTI   0x100000U    // VLAN Tag Input
#define ETHERNET_MAC_VLAN_INCL_CBTI   0x200000U    // Channel based tag insertion
#define ETHERNET_MAC_VLAN_INCL_ADDR   0x1000000U   // Address
#define ETHERNET_MAC_VLAN_INCL_RDWR   0x40000000U  // Read write control
#define ETHERNET_MAC_VLAN_INCL_BUSY   0x80000000U  // Busy

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_INNER_VLAN_INCL register
//
//*****************************************************************************
#define ETHERNET_MAC_INNER_VLAN_INCL_VLT_S  0U
#define ETHERNET_MAC_INNER_VLAN_INCL_VLT_M  0xFFFFU      // VLAN Tag for Transmit Packets
#define ETHERNET_MAC_INNER_VLAN_INCL_VLC_S  16U
#define ETHERNET_MAC_INNER_VLAN_INCL_VLC_M  0x30000U     // VLAN Tag Control in Transmit
                                               // Packets
#define ETHERNET_MAC_INNER_VLAN_INCL_VLP  0x40000U     // VLAN Priority Control
#define ETHERNET_MAC_INNER_VLAN_INCL_CSVL  0x80000U     // C-VLAN or S-VLAN
#define ETHERNET_MAC_INNER_VLAN_INCL_VLTI  0x100000U    // VLAN Tag Input

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_Q0_TX_FLOW_CTRL register
//
//*****************************************************************************
#define ETHERNET_MAC_Q0_TX_FLOW_CTRL_FCB_BPA  0x1U         // Flow Control Busy or
                                               // Backpressure Activate
#define ETHERNET_MAC_Q0_TX_FLOW_CTRL_TFE  0x2U         // Transmit Flow Control Enable
#define ETHERNET_MAC_Q0_TX_FLOW_CTRL_PLT_S  4U
#define ETHERNET_MAC_Q0_TX_FLOW_CTRL_PLT_M  0x70U        // Pause Low Threshold
#define ETHERNET_MAC_Q0_TX_FLOW_CTRL_DZPQ  0x80U        // Disable Zero-Quanta Pause
#define ETHERNET_MAC_Q0_TX_FLOW_CTRL_PT_S  16U
#define ETHERNET_MAC_Q0_TX_FLOW_CTRL_PT_M  0xFFFF0000U  // Pause Time

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_RX_FLOW_CTRL register
//
//*****************************************************************************
#define ETHERNET_MAC_RX_FLOW_CTRL_RFE  0x1U         // Receive Flow Control Enable
#define ETHERNET_MAC_RX_FLOW_CTRL_UP  0x2U         // Unicast Pause Packet Detect

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_RXQ_CTRL4 register
//
//*****************************************************************************
#define ETHERNET_MAC_RXQ_CTRL4_UFFQE  0x1U         // Unicast Address Filter Fail
                                               // Packets Queuing Enable.

#define ETHERNET_MAC_RXQ_CTRL4_UFFQ  0x2U         // Unicast Address Filter Fail
                                               // Packets Queue.

#define ETHERNET_MAC_RXQ_CTRL4_MFFQE  0x100U       // Multicast Address Filter Fail
                                               // Packets Queuing Enable.

#define ETHERNET_MAC_RXQ_CTRL4_MFFQ  0x200U       // Multicast Address Filter Fail
                                               // Packets Queue.

#define ETHERNET_MAC_RXQ_CTRL4_VFFQE  0x10000U     // VLAN Tag Filter Fail Packets
                                               // Queuing Enable
#define ETHERNET_MAC_RXQ_CTRL4_VFFQ  0x20000U     // VLAN Tag Filter Fail Packets
                                               // Queue

//*****************************************************************************
// The following are defines for the bit fields in the MAC_RXQ_CTRL0 register
//
//*****************************************************************************
#define ETHERNET_MAC_RXQ_CTRL0_RXQ0EN_S  0U
#define ETHERNET_MAC_RXQ_CTRL0_RXQ0EN_M  0x3U         // Receive Queue 0 Enable
#define ETHERNET_MAC_RXQ_CTRL0_RXQ1EN_S  2U
#define ETHERNET_MAC_RXQ_CTRL0_RXQ1EN_M  0xCU         // Receive Queue 1 Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_RXQ_CTRL1 register
//
//*****************************************************************************
#define ETHERNET_MAC_RXQ_CTRL1_PTPQ_S  4U
#define ETHERNET_MAC_RXQ_CTRL1_PTPQ_M  0x70U        // PTP Packets Queue
#define ETHERNET_MAC_RXQ_CTRL1_UPQ_S  12U
#define ETHERNET_MAC_RXQ_CTRL1_UPQ_M  0x7000U      // Untagged Packet Queue
#define ETHERNET_MAC_RXQ_CTRL1_MCBCQ_S  16U
#define ETHERNET_MAC_RXQ_CTRL1_MCBCQ_M  0x70000U     // Multicast and Broadcast Queue
                                               //
#define ETHERNET_MAC_RXQ_CTRL1_MCBCQEN  0x100000U    // Multicast and Broadcast Queue
                                               // Enable
#define ETHERNET_MAC_RXQ_CTRL1_TPQC  0x400000U    // Tagged PTP over Ethernet
                                               // Packets Queuing Control.

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_RXQ_CTRL2 register
//
//*****************************************************************************
#define ETHERNET_MAC_RXQ_CTRL2_PSRQ0_S  0U
#define ETHERNET_MAC_RXQ_CTRL2_PSRQ0_M  0xFFU        // Priorities Selected in the
                                               // Receive Queue 0
#define ETHERNET_MAC_RXQ_CTRL2_PSRQ1_S  8U
#define ETHERNET_MAC_RXQ_CTRL2_PSRQ1_M  0xFF00U      // Priorities Selected in the
                                               // Receive Queue 1

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_INTERRUPT_STATUS register
//
//*****************************************************************************
#define ETHERNET_MAC_INTERRUPT_STATUS_PHYIS  0x8U         // PHY Interrupt
#define ETHERNET_MAC_INTERRUPT_STATUS_PMTIS  0x10U        // PMT Interrupt Status
#define ETHERNET_MAC_INTERRUPT_STATUS_LPIIS  0x20U        // LPI Interrupt Status
#define ETHERNET_MAC_INTERRUPT_STATUS_MMCIS  0x100U       // MMC Interrupt Status
#define ETHERNET_MAC_INTERRUPT_STATUS_MMCRXIS  0x200U       // MMC Receive Interrupt Status
#define ETHERNET_MAC_INTERRUPT_STATUS_MMCTXIS  0x400U       // MMC Transmit Interrupt Status
#define ETHERNET_MAC_INTERRUPT_STATUS_MMCRXIPIS  0x800U       // MMC Receive Checksum Offload
                                               // Interrupt Status
#define ETHERNET_MAC_INTERRUPT_STATUS_TSIS  0x1000U      // Timestamp Interrupt Status
#define ETHERNET_MAC_INTERRUPT_STATUS_TXSTSIS  0x2000U      // Transmit Status Interrupt
#define ETHERNET_MAC_INTERRUPT_STATUS_RXSTSIS  0x4000U      // Receive Status Interrupt

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_INTERRUPT_ENABLE register
//
//*****************************************************************************
#define ETHERNET_MAC_INTERRUPT_ENABLE_PHYIE  0x8U         // PHY Interrupt Enable
#define ETHERNET_MAC_INTERRUPT_ENABLE_PMTIE  0x10U        // PMT Interrupt Enable
#define ETHERNET_MAC_INTERRUPT_ENABLE_LPIIE  0x20U        // LPI Interrupt Enable
#define ETHERNET_MAC_INTERRUPT_ENABLE_TSIE  0x1000U      // Timestamp Interrupt Enable
#define ETHERNET_MAC_INTERRUPT_ENABLE_TXSTSIE  0x2000U      // Transmit Status Interrupt
                                               // Enable
#define ETHERNET_MAC_INTERRUPT_ENABLE_RXSTSIE  0x4000U      // Receive Status Interrupt
                                               // Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_RX_TX_STATUS register
//
//*****************************************************************************
#define ETHERNET_MAC_RX_TX_STATUS_TJT  0x1U         // Transmit Jabber Timeout
#define ETHERNET_MAC_RX_TX_STATUS_NCARR  0x2U         // No Carrier
#define ETHERNET_MAC_RX_TX_STATUS_LCARR  0x4U         // Loss of Carrier
#define ETHERNET_MAC_RX_TX_STATUS_EXDEF  0x8U         // Excessive Deferral
#define ETHERNET_MAC_RX_TX_STATUS_LCOL  0x10U        // Late Collision
#define ETHERNET_MAC_RX_TX_STATUS_EXCOL  0x20U        // Excessive Collisions
#define ETHERNET_MAC_RX_TX_STATUS_RWT  0x100U       // Receive Watchdog Timeout

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_PMT_CONTROL_STATUS register
//
//*****************************************************************************
#define ETHERNET_MAC_PMT_CONTROL_STATUS_PWRDWN  0x1U         // Power Down
#define ETHERNET_MAC_PMT_CONTROL_STATUS_MGKPKTEN  0x2U         // Magic Packet Enable
#define ETHERNET_MAC_PMT_CONTROL_STATUS_RWKPKTEN  0x4U         // Remote Wake-Up Packet Enable
#define ETHERNET_MAC_PMT_CONTROL_STATUS_MGKPRCVD  0x20U        // Magic Packet Received
#define ETHERNET_MAC_PMT_CONTROL_STATUS_RWKPRCVD  0x40U        // Remote Wake-Up Packet
                                               // Received
#define ETHERNET_MAC_PMT_CONTROL_STATUS_GLBLUCAST  0x200U       // Global Unicast
#define ETHERNET_MAC_PMT_CONTROL_STATUS_RWKPFE  0x400U       // Remote Wake-up Packet
                                               // Forwarding Enable
#define ETHERNET_MAC_PMT_CONTROL_STATUS_RWKPTR_S  24U
#define ETHERNET_MAC_PMT_CONTROL_STATUS_RWKPTR_M  0x1F000000U  // Remote Wake-up FIFO Pointer
#define ETHERNET_MAC_PMT_CONTROL_STATUS_RWKFILTRST  0x80000000U  // Remote Wake-Up Packet Filter
                                               // Register Pointer Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_LPI_CONTROL_STATUS register
//
//*****************************************************************************
#define ETHERNET_MAC_LPI_CONTROL_STATUS_TLPIEN  0x1U         // Transmit LPI Entry
#define ETHERNET_MAC_LPI_CONTROL_STATUS_TLPIEX  0x2U         // Transmit LPI Exit
#define ETHERNET_MAC_LPI_CONTROL_STATUS_RLPIEN  0x4U         // Receive LPI Entry
#define ETHERNET_MAC_LPI_CONTROL_STATUS_RLPIEX  0x8U         // Receive LPI Exit
#define ETHERNET_MAC_LPI_CONTROL_STATUS_TLPIST  0x100U       // Transmit LPI State
#define ETHERNET_MAC_LPI_CONTROL_STATUS_RLPIST  0x200U       // Receive LPI State
#define ETHERNET_MAC_LPI_CONTROL_STATUS_LPIEN  0x10000U     // LPI Enable
#define ETHERNET_MAC_LPI_CONTROL_STATUS_PLS  0x20000U     // PHY Link Status
#define ETHERNET_MAC_LPI_CONTROL_STATUS_LPITXA  0x80000U     // LPI Tx Automate
#define ETHERNET_MAC_LPI_CONTROL_STATUS_LPIATE  0x100000U    // LPI Timer Enable
#define ETHERNET_MAC_LPI_CONTROL_STATUS_LPITCSE  0x200000U    // LPI Tx Clock Stop Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_LPI_TIMERS_CONTROL register
//
//*****************************************************************************
#define ETHERNET_MAC_LPI_TIMERS_CONTROL_TWT_S  0U
#define ETHERNET_MAC_LPI_TIMERS_CONTROL_TWT_M  0xFFFFU      // LPI TW Timer
#define ETHERNET_MAC_LPI_TIMERS_CONTROL_LST_S  16U
#define ETHERNET_MAC_LPI_TIMERS_CONTROL_LST_M  0x3FF0000U   // LPI LS Timer

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_LPI_ENTRY_TIMER register
//
//*****************************************************************************
#define ETHERNET_MAC_LPI_ENTRY_TIMER_LPIET_S  3U
#define ETHERNET_MAC_LPI_ENTRY_TIMER_LPIET_M  0xFFFF8U     // LPI Entry Timer

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_1US_TIC_COUNTER register
//
//*****************************************************************************
#define ETHERNET_MAC_1US_TIC_COUNTER_TIC_1US_CNTR_S  0U
#define ETHERNET_MAC_1US_TIC_COUNTER_TIC_1US_CNTR_M  0xFFFU       // 1US TIC Counter

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_VERSION register
//
//*****************************************************************************
#define ETHERNET_MAC_VERSION_SNPSVER_S  0U
#define ETHERNET_MAC_VERSION_SNPSVER_M  0xFFU        // Synopsys-defined Version
                                               // (3.7)
#define ETHERNET_MAC_VERSION_USERVER_S  8U
#define ETHERNET_MAC_VERSION_USERVER_M  0xFF00U      // User-defined Version
                                               // (configured with coreConsultant)

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_DEBUG register
//
//*****************************************************************************
#define ETHERNET_MAC_DEBUG_RPESTS     0x1U         // MAC GMII or MII Receive
                                               // Protocol Engine Status
#define ETHERNET_MAC_DEBUG_RFCFCSTS_S  1U
#define ETHERNET_MAC_DEBUG_RFCFCSTS_M  0x6U         // MAC Receive Packet Controller
                                               // FIFO Status
#define ETHERNET_MAC_DEBUG_TPESTS     0x10000U     // MAC GMII or MII Transmit
                                               // Protocol Engine Status
#define ETHERNET_MAC_DEBUG_TFCSTS_S   17U
#define ETHERNET_MAC_DEBUG_TFCSTS_M   0x60000U     // MAC Transmit Packet
                                               // Controller Status

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_HW_FEATURE0 register
//
//*****************************************************************************
#define ETHERNET_MAC_HW_FEATURE0_MIISEL  0x1U         // 10 or 100 Mbps Support
#define ETHERNET_MAC_HW_FEATURE0_GMIISEL  0x2U         // 1000 Mbps Support
#define ETHERNET_MAC_HW_FEATURE0_HDSEL  0x4U         // Half-duplex Support
#define ETHERNET_MAC_HW_FEATURE0_PCSSEL  0x8U         // PCS Registers (TBI, SGMII, or
                                               // RTBI PHY interface)
#define ETHERNET_MAC_HW_FEATURE0_VLHASH  0x10U        // VLAN Hash Filter Selected
#define ETHERNET_MAC_HW_FEATURE0_SMASEL  0x20U        // SMA (MDIO) Interface
#define ETHERNET_MAC_HW_FEATURE0_RWKSEL  0x40U        // PMT Remote Wake-up Packet
                                               // Enable
#define ETHERNET_MAC_HW_FEATURE0_MGKSEL  0x80U        // PMT Magic Packet Enable
#define ETHERNET_MAC_HW_FEATURE0_MMCSEL  0x100U       // RMON Module Enable
#define ETHERNET_MAC_HW_FEATURE0_ARPOFFSEL  0x200U       // ARP Offload Enabled
#define ETHERNET_MAC_HW_FEATURE0_TSSEL  0x1000U      // IEEE 1588-2008 Timestamp
                                               // Enabled
#define ETHERNET_MAC_HW_FEATURE0_EEESEL  0x2000U      // Energy Efficient Ethernet
                                               // Enabled
#define ETHERNET_MAC_HW_FEATURE0_TXCOESEL  0x4000U      // Transmit Checksum Offload
                                               // Enabled
#define ETHERNET_MAC_HW_FEATURE0_RXCOESEL  0x10000U     // Receive Checksum Offload
                                               // Enabled
#define ETHERNET_MAC_HW_FEATURE0_ADDMACADRSEL_S  18U
#define ETHERNET_MAC_HW_FEATURE0_ADDMACADRSEL_M  0x7C0000U    // MAC Addresses 1-31 Selected
#define ETHERNET_MAC_HW_FEATURE0_MACADR32SEL  0x800000U    // MAC Addresses 32-63 Selected
#define ETHERNET_MAC_HW_FEATURE0_MACADR64SEL  0x1000000U   // MAC Addresses 64-127 Selected
#define ETHERNET_MAC_HW_FEATURE0_TSSTSSEL_S  25U
#define ETHERNET_MAC_HW_FEATURE0_TSSTSSEL_M  0x6000000U   // Timestamp System Time Source
#define ETHERNET_MAC_HW_FEATURE0_SAVLANINS  0x8000000U   // Source Address or VLAN
                                               // Insertion Enable
#define ETHERNET_MAC_HW_FEATURE0_ACTPHYSEL_S  28U
#define ETHERNET_MAC_HW_FEATURE0_ACTPHYSEL_M  0x70000000U  // Active PHY Selected

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_HW_FEATURE1 register
//
//*****************************************************************************
#define ETHERNET_MAC_HW_FEATURE1_RXFIFOSIZE_S  0U
#define ETHERNET_MAC_HW_FEATURE1_RXFIFOSIZE_M  0x1FU        // MTL Receive FIFO Size
#define ETHERNET_MAC_HW_FEATURE1_SPRAM  0x20U        // Single Port RAM Enable
#define ETHERNET_MAC_HW_FEATURE1_TXFIFOSIZE_S  6U
#define ETHERNET_MAC_HW_FEATURE1_TXFIFOSIZE_M  0x7C0U       // MTL Transmit FIFO Size
#define ETHERNET_MAC_HW_FEATURE1_OSTEN  0x800U       // One-Step Timestamping Enable
#define ETHERNET_MAC_HW_FEATURE1_PTOEN  0x1000U      // PTP Offload Enable
#define ETHERNET_MAC_HW_FEATURE1_ADVTHWORD  0x2000U      // IEEE 1588 High Word Register
                                               // Enable
#define ETHERNET_MAC_HW_FEATURE1_ADDR64_S  14U
#define ETHERNET_MAC_HW_FEATURE1_ADDR64_M  0xC000U      // Address Width.

#define ETHERNET_MAC_HW_FEATURE1_DCBEN  0x10000U     // DCB Feature Enable
#define ETHERNET_MAC_HW_FEATURE1_SPHEN  0x20000U     // Split Header Feature Enable
#define ETHERNET_MAC_HW_FEATURE1_TSOEN  0x40000U     // TCP Segmentation Offload
                                               // Enable
#define ETHERNET_MAC_HW_FEATURE1_DBGMEMA  0x80000U     // DMA Debug Registers Enable
#define ETHERNET_MAC_HW_FEATURE1_AVSEL  0x100000U    // AV Feature Enable
#define ETHERNET_MAC_HW_FEATURE1_RAVSEL  0x200000U    // Rx Side Only AV Feature
                                               // Enable
#define ETHERNET_MAC_HW_FEATURE1_POUOST  0x800000U    // One Step for PTP over UDP/IP
                                               // Feature Enable
#define ETHERNET_MAC_HW_FEATURE1_HASHTBLSZ_S  24U
#define ETHERNET_MAC_HW_FEATURE1_HASHTBLSZ_M  0x3000000U   // Hash Table Size
#define ETHERNET_MAC_HW_FEATURE1_L3L4FNUM_S  27U
#define ETHERNET_MAC_HW_FEATURE1_L3L4FNUM_M  0x78000000U  // Total number of L3 or L4
                                               // Filters

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_HW_FEATURE2 register
//
//*****************************************************************************
#define ETHERNET_MAC_HW_FEATURE2_RXQCNT_S  0U
#define ETHERNET_MAC_HW_FEATURE2_RXQCNT_M  0xFU         // Number of MTL Receive Queues
#define ETHERNET_MAC_HW_FEATURE2_TXQCNT_S  6U
#define ETHERNET_MAC_HW_FEATURE2_TXQCNT_M  0x3C0U       // Number of MTL Transmit Queues
#define ETHERNET_MAC_HW_FEATURE2_RXCHCNT_S  12U
#define ETHERNET_MAC_HW_FEATURE2_RXCHCNT_M  0xF000U      // Number of DMA Receive
                                               // Channels
#define ETHERNET_MAC_HW_FEATURE2_TXCHCNT_S  18U
#define ETHERNET_MAC_HW_FEATURE2_TXCHCNT_M  0x3C0000U    // Number of DMA Transmit
                                               // Channels
#define ETHERNET_MAC_HW_FEATURE2_PPSOUTNUM_S  24U
#define ETHERNET_MAC_HW_FEATURE2_PPSOUTNUM_M  0x7000000U   // Number of PPS Outputs
#define ETHERNET_MAC_HW_FEATURE2_AUXSNAPNUM_S  28U
#define ETHERNET_MAC_HW_FEATURE2_AUXSNAPNUM_M  0x70000000U  // Number of Auxiliary Snapshot
                                               // Inputs

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_HW_FEATURE3 register
//
//*****************************************************************************
#define ETHERNET_MAC_HW_FEATURE3_NRVF_S  0U
#define ETHERNET_MAC_HW_FEATURE3_NRVF_M  0x7U         // Number of Extended VLAN Tag
                                               // Filters Enabled
#define ETHERNET_MAC_HW_FEATURE3_CBTISEL  0x10U        // Queue/Channel based VLAN tag
                                               // insertion on Tx Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_MDIO_ADDRESS register
//
//*****************************************************************************
#define ETHERNET_MAC_MDIO_ADDRESS_GB  0x1U         // GMII Busy
#define ETHERNET_MAC_MDIO_ADDRESS_C45E  0x2U         // Clause 45 PHY Enable
#define ETHERNET_MAC_MDIO_ADDRESS_GOC_0  0x4U         // GMII Operation Command 0
#define ETHERNET_MAC_MDIO_ADDRESS_GOC_1  0x8U         // GMII Operation Command 1
#define ETHERNET_MAC_MDIO_ADDRESS_SKAP  0x10U        // Skip Address Packet
#define ETHERNET_MAC_MDIO_ADDRESS_CR_S  8U
#define ETHERNET_MAC_MDIO_ADDRESS_CR_M  0xF00U       // CSR Clock Range
#define ETHERNET_MAC_MDIO_ADDRESS_NTC_S  12U
#define ETHERNET_MAC_MDIO_ADDRESS_NTC_M  0x7000U      // Number of Training Clocks
#define ETHERNET_MAC_MDIO_ADDRESS_RDA_S  16U
#define ETHERNET_MAC_MDIO_ADDRESS_RDA_M  0x1F0000U    // Register/Device Address
#define ETHERNET_MAC_MDIO_ADDRESS_PA_S  21U
#define ETHERNET_MAC_MDIO_ADDRESS_PA_M  0x3E00000U   // Physical Layer Address
#define ETHERNET_MAC_MDIO_ADDRESS_BTB  0x4000000U   // Back to Back transactions
#define ETHERNET_MAC_MDIO_ADDRESS_PSE  0x8000000U   // Preamble Suppression Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_MDIO_DATA register
//
//*****************************************************************************
#define ETHERNET_MAC_MDIO_DATA_GD_S   0U
#define ETHERNET_MAC_MDIO_DATA_GD_M   0xFFFFU      // GMII Data
#define ETHERNET_MAC_MDIO_DATA_RA_S   16U
#define ETHERNET_MAC_MDIO_DATA_RA_M   0xFFFF0000U  // Register Address

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_ADDRESS0_HIGH register
//
//*****************************************************************************
#define ETHERNET_MAC_ADDRESS0_HIGH_ADDRHI_S  0U
#define ETHERNET_MAC_ADDRESS0_HIGH_ADDRHI_M  0xFFFFU      // MAC Address0[47:32]
#define ETHERNET_MAC_ADDRESS0_HIGH_DCS  0x10000U     // DMA Channel Select
#define ETHERNET_MAC_ADDRESS0_HIGH_AE  0x80000000U  // Address Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_ADDRESS1_HIGH register
//
//*****************************************************************************
#define ETHERNET_MAC_ADDRESS1_HIGH_ADDRHI_S  0U
#define ETHERNET_MAC_ADDRESS1_HIGH_ADDRHI_M  0xFFFFU      // MAC Address1 [47:32]
#define ETHERNET_MAC_ADDRESS1_HIGH_DCS  0x10000U     // DMA Channel Select
#define ETHERNET_MAC_ADDRESS1_HIGH_MBC_S  24U
#define ETHERNET_MAC_ADDRESS1_HIGH_MBC_M  0x3F000000U  // Mask Byte Control
#define ETHERNET_MAC_ADDRESS1_HIGH_SA  0x40000000U  // Source Address
#define ETHERNET_MAC_ADDRESS1_HIGH_AE  0x80000000U  // Address Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_ADDRESS2_HIGH register
//
//*****************************************************************************
#define ETHERNET_MAC_ADDRESS2_HIGH_ADDRHI_S  0U
#define ETHERNET_MAC_ADDRESS2_HIGH_ADDRHI_M  0xFFFFU      // MAC Address1 [47:32]
#define ETHERNET_MAC_ADDRESS2_HIGH_DCS  0x10000U     // DMA Channel Select
#define ETHERNET_MAC_ADDRESS2_HIGH_MBC_S  24U
#define ETHERNET_MAC_ADDRESS2_HIGH_MBC_M  0x3F000000U  // Mask Byte Control
#define ETHERNET_MAC_ADDRESS2_HIGH_SA  0x40000000U  // Source Address
#define ETHERNET_MAC_ADDRESS2_HIGH_AE  0x80000000U  // Address Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_ADDRESS3_HIGH register
//
//*****************************************************************************
#define ETHERNET_MAC_ADDRESS3_HIGH_ADDRHI_S  0U
#define ETHERNET_MAC_ADDRESS3_HIGH_ADDRHI_M  0xFFFFU      // MAC Address1 [47:32]
#define ETHERNET_MAC_ADDRESS3_HIGH_DCS  0x10000U     // DMA Channel Select
#define ETHERNET_MAC_ADDRESS3_HIGH_MBC_S  24U
#define ETHERNET_MAC_ADDRESS3_HIGH_MBC_M  0x3F000000U  // Mask Byte Control
#define ETHERNET_MAC_ADDRESS3_HIGH_SA  0x40000000U  // Source Address
#define ETHERNET_MAC_ADDRESS3_HIGH_AE  0x80000000U  // Address Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the MMC_CONTROL register
//
//*****************************************************************************
#define ETHERNET_MMC_CONTROL_CNTRST   0x1U         // Counters Reset
#define ETHERNET_MMC_CONTROL_CNTSTOPRO  0x2U         // Counter Stop Rollover
#define ETHERNET_MMC_CONTROL_RSTONRD  0x4U         // Reset on Read
#define ETHERNET_MMC_CONTROL_CNTFREEZ  0x8U         // MMC Counter Freeze
#define ETHERNET_MMC_CONTROL_CNTPRST  0x10U        // Counters Preset
#define ETHERNET_MMC_CONTROL_CNTPRSTLVL  0x20U        // Full-Half Preset
#define ETHERNET_MMC_CONTROL_UCDBC    0x100U       // Update MMC Counters for
                                               // Dropped Broadcast Packets

//*****************************************************************************
//
// The following are defines for the bit fields in the MMC_RX_INTERRUPT register
//
//*****************************************************************************
#define ETHERNET_MMC_RX_INTERRUPT_RXGBPKTIS  0x1U         // MMC Receive Good Bad Packet
                                               // Counter Interrupt Status
#define ETHERNET_MMC_RX_INTERRUPT_RXGBOCTIS  0x2U         // MMC Receive Good Bad Octet
                                               // Counter Interrupt Status
#define ETHERNET_MMC_RX_INTERRUPT_RXGOCTIS  0x4U         // MMC Receive Good Octet
                                               // Counter Interrupt Status
#define ETHERNET_MMC_RX_INTERRUPT_RXBCGPIS  0x8U         // MMC Receive Broadcast Good
                                               // Packet Counter Interrupt Status
#define ETHERNET_MMC_RX_INTERRUPT_RXMCGPIS  0x10U        // MMC Receive Multicast Good
                                               // Packet Counter Interrupt Status
#define ETHERNET_MMC_RX_INTERRUPT_RXCRCERPIS  0x20U        // MMC Receive CRC Error Packet
                                               // Counter Interrupt Status
#define ETHERNET_MMC_RX_INTERRUPT_RXALGNERPIS  0x40U        // MMC Receive Alignment Error
                                               // Packet Counter Interrupt Status
#define ETHERNET_MMC_RX_INTERRUPT_RXRUNTPIS  0x80U        // MMC Receive Runt Packet
                                               // Counter Interrupt Status
#define ETHERNET_MMC_RX_INTERRUPT_RXJABERPIS  0x100U       // MMC Receive Jabber Error
                                               // Packet Counter Interrupt Status
#define ETHERNET_MMC_RX_INTERRUPT_RXUSIZEGPIS  0x200U       // MMC Receive Undersize Good
                                               // Packet Counter Interrupt Status
#define ETHERNET_MMC_RX_INTERRUPT_RXOSIZEGPIS  0x400U       // MMC Receive Oversize Good
                                               // Packet Counter Interrupt Status
#define ETHERNET_MMC_RX_INTERRUPT_RX64OCTGBPIS  0x800U       // MMC Receive 64 Octet Good Bad
                                               // Packet Counter Interrupt
                                               // Status
#define ETHERNET_MMC_RX_INTERRUPT_RX65T127OCTGBPIS  0x1000U      // MMC Receive 65 to 127 Octet
                                               // Good Bad Packet Counter
                                               // Interrupt Status
#define ETHERNET_MMC_RX_INTERRUPT_RX128T255OCTGBPIS  0x2000U      // MMC Receive 128 to 255 Octet
                                               // Good Bad Packet Counter
                                               // Interrupt Status
#define ETHERNET_MMC_RX_INTERRUPT_RX256T511OCTGBPIS  0x4000U      // MMC Receive 256 to 511 Octet
                                               // Good Bad Packet Counter
                                               // Interrupt Status
#define ETHERNET_MMC_RX_INTERRUPT_RX512T1023OCTGBPIS  0x8000U      // MMC Receive 512 to 1023 Octet
                                               // Good Bad Packet Counter
                                               // Interrupt Status
#define ETHERNET_MMC_RX_INTERRUPT_RX1024TMAXOCTGBPIS  0x10000U     // MMC Receive 1024 to Maximum
                                               // Octet Good Bad Packet Counter
                                               // Interrupt Status
#define ETHERNET_MMC_RX_INTERRUPT_RXUCGPIS  0x20000U     // MMC Receive Unicast Good
                                               // Packet Counter Interrupt Status
#define ETHERNET_MMC_RX_INTERRUPT_RXLENERPIS  0x40000U     // MMC Receive Length Error
                                               // Packet Counter Interrupt Status
#define ETHERNET_MMC_RX_INTERRUPT_RXORANGEPIS  0x80000U     // MMC Receive Out Of Range
                                               // Error Packet Counter Interrupt
                                               // Status.
#define ETHERNET_MMC_RX_INTERRUPT_RXPAUSPIS  0x100000U    // MMC Receive Pause Packet
                                               // Counter Interrupt Status
#define ETHERNET_MMC_RX_INTERRUPT_RXFOVPIS  0x200000U    // MMC Receive FIFO Overflow
                                               // Packet Counter Interrupt Status
#define ETHERNET_MMC_RX_INTERRUPT_RXVLANGBPIS  0x400000U    // MMC Receive VLAN Good Bad
                                               // Packet Counter Interrupt Status
#define ETHERNET_MMC_RX_INTERRUPT_RXWDOGPIS  0x800000U    // MMC Receive Watchdog Error
                                               // Packet Counter Interrupt Status
#define ETHERNET_MMC_RX_INTERRUPT_RXRCVERRPIS  0x1000000U   // MMC Receive Error Packet
                                               // Counter Interrupt Status
#define ETHERNET_MMC_RX_INTERRUPT_RXCTRLPIS  0x2000000U   // MMC Receive Control Packet
                                               // Counter Interrupt Status
#define ETHERNET_MMC_RX_INTERRUPT_RXLPIUSCIS  0x4000000U   // MMC Receive LPI microsecond
                                               // counter interrupt status
#define ETHERNET_MMC_RX_INTERRUPT_RXLPITRCIS  0x8000000U   // MMC Receive LPI transition
                                               // counter interrupt status

//*****************************************************************************
//
// The following are defines for the bit fields in the MMC_TX_INTERRUPT register
//
//*****************************************************************************
#define ETHERNET_MMC_TX_INTERRUPT_TXGBOCTIS  0x1U         // MMC Transmit Good Bad Octet
                                               // Counter Interrupt Status
#define ETHERNET_MMC_TX_INTERRUPT_TXGBPKTIS  0x2U         // MMC Transmit Good Bad Packet
                                               // Counter Interrupt Status
#define ETHERNET_MMC_TX_INTERRUPT_TXBCGPIS  0x4U         // MMC Transmit Broadcast Good
                                               // Packet Counter Interrupt Status
#define ETHERNET_MMC_TX_INTERRUPT_TXMCGPIS  0x8U         // MMC Transmit Multicast Good
                                               // Packet Counter Interrupt Status
#define ETHERNET_MMC_TX_INTERRUPT_TX64OCTGBPIS  0x10U        // MMC Transmit 64 Octet Good
                                               // Bad Packet Counter Interrupt
                                               // Status
#define ETHERNET_MMC_TX_INTERRUPT_TX65T127OCTGBPIS  0x20U        // MMC Transmit 65 to 127 Octet
                                               // Good Bad Packet Counter
                                               // Interrupt Status
#define ETHERNET_MMC_TX_INTERRUPT_TX128T255OCTGBPIS  0x40U        // MMC Transmit 128 to 255 Octet
                                               // Good Bad Packet Counter
                                               // Interrupt Status
#define ETHERNET_MMC_TX_INTERRUPT_TX256T511OCTGBPIS  0x80U        // MMC Transmit 256 to 511 Octet
                                               // Good Bad Packet Counter
                                               // Interrupt Status
#define ETHERNET_MMC_TX_INTERRUPT_TX512T1023OCTGBPIS  0x100U       // MMC Transmit 512 to 1023
                                               // Octet Good Bad Packet Counter
                                               // Interrupt Status
#define ETHERNET_MMC_TX_INTERRUPT_TX1024TMAXOCTGBPIS  0x200U       // MMC Transmit 1024 to Maximum
                                               // Octet Good Bad Packet Counter
                                               // Interrupt Status
#define ETHERNET_MMC_TX_INTERRUPT_TXUCGBPIS  0x400U       // MMC Transmit Unicast Good Bad
                                               // Packet Counter Interrupt
                                               // Status
#define ETHERNET_MMC_TX_INTERRUPT_TXMCGBPIS  0x800U       // MMC Transmit Multicast Good
                                               // Bad Packet Counter Interrupt
                                               // Status
#define ETHERNET_MMC_TX_INTERRUPT_TXBCGBPIS  0x1000U      // MMC Transmit Broadcast Good
                                               // Bad Packet Counter Interrupt
                                               // Status
#define ETHERNET_MMC_TX_INTERRUPT_TXUFLOWERPIS  0x2000U      // MMC Transmit Underflow Error
                                               // Packet Counter Interrupt
                                               // Status
#define ETHERNET_MMC_TX_INTERRUPT_TXSCOLGPIS  0x4000U      // MMC Transmit Single Collision
                                               // Good Packet Counter Interrupt
                                               // Status
#define ETHERNET_MMC_TX_INTERRUPT_TXMCOLGPIS  0x8000U      // MMC Transmit Multiple
                                               // Collision Good Packet Counter
                                               // Interrupt Status
#define ETHERNET_MMC_TX_INTERRUPT_TXDEFPIS  0x10000U     // MMC Transmit Deferred Packet
                                               // Counter Interrupt Status
#define ETHERNET_MMC_TX_INTERRUPT_TXLATCOLPIS  0x20000U     // MMC Transmit Late Collision
                                               // Packet Counter Interrupt Status
#define ETHERNET_MMC_TX_INTERRUPT_TXEXCOLPIS  0x40000U     // MMC Transmit Excessive
                                               // Collision Packet Counter Interrupt
                                               // Status
#define ETHERNET_MMC_TX_INTERRUPT_TXCARERPIS  0x80000U     // MMC Transmit Carrier Error
                                               // Packet Counter Interrupt Status
#define ETHERNET_MMC_TX_INTERRUPT_TXGOCTIS  0x100000U    // MMC Transmit Good Octet
                                               // Counter Interrupt Status
#define ETHERNET_MMC_TX_INTERRUPT_TXGPKTIS  0x200000U    // MMC Transmit Good Packet
                                               // Counter Interrupt Status
#define ETHERNET_MMC_TX_INTERRUPT_TXEXDEFPIS  0x400000U    // MMC Transmit Excessive
                                               // Deferral Packet Counter Interrupt
                                               // Status
#define ETHERNET_MMC_TX_INTERRUPT_TXPAUSPIS  0x800000U    // MMC Transmit Pause Packet
                                               // Counter Interrupt Status
#define ETHERNET_MMC_TX_INTERRUPT_TXVLANGPIS  0x1000000U   // MMC Transmit VLAN Good Packet
                                               // Counter Interrupt Status
#define ETHERNET_MMC_TX_INTERRUPT_TXOSIZEGPIS  0x2000000U   // MMC Transmit Oversize Good
                                               // Packet Counter Interrupt Status
#define ETHERNET_MMC_TX_INTERRUPT_TXLPIUSCIS  0x4000000U   // MMC Transmit LPI microsecond
                                               // counter interrupt status
#define ETHERNET_MMC_TX_INTERRUPT_TXLPITRCIS  0x8000000U   // MMC Transmit LPI transition
                                               // counter interrupt status

//*****************************************************************************
//
// The following are defines for the bit fields in the MMC_RX_INTERRUPT_MASK register
//
//*****************************************************************************
#define ETHERNET_MMC_RX_INTERRUPT_MASK_RXGBPKTIM  0x1U         // MMC Receive Good Bad Packet
                                               // Counter Interrupt Mask
#define ETHERNET_MMC_RX_INTERRUPT_MASK_RXGBOCTIM  0x2U         // MMC Receive Good Bad Octet
                                               // Counter Interrupt Mask
#define ETHERNET_MMC_RX_INTERRUPT_MASK_RXGOCTIM  0x4U         // MMC Receive Good Octet
                                               // Counter Interrupt Mask
#define ETHERNET_MMC_RX_INTERRUPT_MASK_RXBCGPIM  0x8U         // MMC Receive Broadcast Good
                                               // Packet Counter Interrupt Mask
#define ETHERNET_MMC_RX_INTERRUPT_MASK_RXMCGPIM  0x10U        // MMC Receive Multicast Good
                                               // Packet Counter Interrupt Mask
#define ETHERNET_MMC_RX_INTERRUPT_MASK_RXCRCERPIM  0x20U        // MMC Receive CRC Error Packet
                                               // Counter Interrupt Mask
#define ETHERNET_MMC_RX_INTERRUPT_MASK_RXALGNERPIM  0x40U        // MMC Receive Alignment Error
                                               // Packet Counter Interrupt Mask
#define ETHERNET_MMC_RX_INTERRUPT_MASK_RXRUNTPIM  0x80U        // MMC Receive Runt Packet
                                               // Counter Interrupt Mask
#define ETHERNET_MMC_RX_INTERRUPT_MASK_RXJABERPIM  0x100U       // MMC Receive Jabber Error
                                               // Packet Counter Interrupt Mask
#define ETHERNET_MMC_RX_INTERRUPT_MASK_RXUSIZEGPIM  0x200U       // MMC Receive Undersize Good
                                               // Packet Counter Interrupt Mask
#define ETHERNET_MMC_RX_INTERRUPT_MASK_RXOSIZEGPIM  0x400U       // MMC Receive Oversize Good
                                               // Packet Counter Interrupt Mask
#define ETHERNET_MMC_RX_INTERRUPT_MASK_RX64OCTGBPIM  0x800U       // MMC Receive 64 Octet Good Bad
                                               // Packet Counter Interrupt Mask
#define ETHERNET_MMC_RX_INTERRUPT_MASK_RX65T127OCTGBPIM  0x1000U      // MMC Receive 65 to 127 Octet
                                               // Good Bad Packet Counter
                                               // Interrupt Mask
#define ETHERNET_MMC_RX_INTERRUPT_MASK_RX128T255OCTGBPIM  0x2000U      // MMC Receive 128 to 255 Octet
                                               // Good Bad Packet Counter
                                               // Interrupt Mask
#define ETHERNET_MMC_RX_INTERRUPT_MASK_RX256T511OCTGBPIM  0x4000U      // MMC Receive 256 to 511 Octet
                                               // Good Bad Packet Counter
                                               // Interrupt Mask
#define ETHERNET_MMC_RX_INTERRUPT_MASK_RX512T1023OCTGBPIM  0x8000U      // MMC Receive 512 to 1023 Octet
                                               // Good Bad Packet Counter
                                               // Interrupt Mask
#define ETHERNET_MMC_RX_INTERRUPT_MASK_RX1024TMAXOCTGBPIM  0x10000U     // MMC Receive 1024 to Maximum
                                               // Octet Good Bad Packet Counter
                                               // Interrupt Mask.
#define ETHERNET_MMC_RX_INTERRUPT_MASK_RXUCGPIM  0x20000U     // MMC Receive Unicast Good
                                               // Packet Counter Interrupt Mask
#define ETHERNET_MMC_RX_INTERRUPT_MASK_RXLENERPIM  0x40000U     // MMC Receive Length Error
                                               // Packet Counter Interrupt Mask
#define ETHERNET_MMC_RX_INTERRUPT_MASK_RXORANGEPIM  0x80000U     // MMC Receive Out Of Range
                                               // Error Packet Counter Interrupt
                                               // Mask
#define ETHERNET_MMC_RX_INTERRUPT_MASK_RXPAUSPIM  0x100000U    // MMC Receive Pause Packet
                                               // Counter Interrupt Mask
#define ETHERNET_MMC_RX_INTERRUPT_MASK_RXFOVPIM  0x200000U    // MMC Receive FIFO Overflow
                                               // Packet Counter Interrupt Mask
#define ETHERNET_MMC_RX_INTERRUPT_MASK_RXVLANGBPIM  0x400000U    // MMC Receive VLAN Good Bad
                                               // Packet Counter Interrupt Mask
#define ETHERNET_MMC_RX_INTERRUPT_MASK_RXWDOGPIM  0x800000U    // MMC Receive Watchdog Error
                                               // Packet Counter Interrupt Mask
#define ETHERNET_MMC_RX_INTERRUPT_MASK_RXRCVERRPIM  0x1000000U   // MMC Receive Error Packet
                                               // Counter Interrupt Mask
#define ETHERNET_MMC_RX_INTERRUPT_MASK_RXCTRLPIM  0x2000000U   // MMC Receive Control Packet
                                               // Counter Interrupt Mask
#define ETHERNET_MMC_RX_INTERRUPT_MASK_RXLPIUSCIM  0x4000000U   // MMC Receive LPI microsecond
                                               // counter interrupt Mask
#define ETHERNET_MMC_RX_INTERRUPT_MASK_RXLPITRCIM  0x8000000U   // MMC Receive LPI transition
                                               // counter interrupt Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the MMC_TX_INTERRUPT_MASK register
//
//*****************************************************************************
#define ETHERNET_MMC_TX_INTERRUPT_MASK_TXGBOCTIM  0x1U         // MMC Transmit Good Bad Octet
                                               // Counter Interrupt Mask
#define ETHERNET_MMC_TX_INTERRUPT_MASK_TXGBPKTIM  0x2U         // MMC Transmit Good Bad Packet
                                               // Counter Interrupt Mask
#define ETHERNET_MMC_TX_INTERRUPT_MASK_TXBCGPIM  0x4U         // MMC Transmit Broadcast Good
                                               // Packet Counter Interrupt Mask
#define ETHERNET_MMC_TX_INTERRUPT_MASK_TXMCGPIM  0x8U         // MMC Transmit Multicast Good
                                               // Packet Counter Interrupt Mask
#define ETHERNET_MMC_TX_INTERRUPT_MASK_TX64OCTGBPIM  0x10U        // MMC Transmit 64 Octet Good
                                               // Bad Packet Counter Interrupt
                                               // Mask
#define ETHERNET_MMC_TX_INTERRUPT_MASK_TX65T127OCTGBPIM  0x20U        // MMC Transmit 65 to 127 Octet
                                               // Good Bad Packet Counter
                                               // Interrupt Mask
#define ETHERNET_MMC_TX_INTERRUPT_MASK_TX128T255OCTGBPIM  0x40U        // MMC Transmit 128 to 255 Octet
                                               // Good Bad Packet Counter
                                               // Interrupt Mask
#define ETHERNET_MMC_TX_INTERRUPT_MASK_TX256T511OCTGBPIM  0x80U        // MMC Transmit 256 to 511 Octet
                                               // Good Bad Packet Counter
                                               // Interrupt Mask
#define ETHERNET_MMC_TX_INTERRUPT_MASK_TX512T1023OCTGBPIM  0x100U       // MMC Transmit 512 to 1023
                                               // Octet Good Bad Packet Counter
                                               // Interrupt Mask
#define ETHERNET_MMC_TX_INTERRUPT_MASK_TX1024TMAXOCTGBPIM  0x200U       // MMC Transmit 1024 to Maximum
                                               // Octet Good Bad Packet Counter
                                               // Interrupt Mask
#define ETHERNET_MMC_TX_INTERRUPT_MASK_TXUCGBPIM  0x400U       // MMC Transmit Unicast Good Bad
                                               // Packet Counter Interrupt Mask
#define ETHERNET_MMC_TX_INTERRUPT_MASK_TXMCGBPIM  0x800U       // MMC Transmit Multicast Good
                                               // Bad Packet Counter Interrupt
                                               // Mask
#define ETHERNET_MMC_TX_INTERRUPT_MASK_TXBCGBPIM  0x1000U      // MMC Transmit Broadcast Good
                                               // Bad Packet Counter Interrupt
                                               // Mask
#define ETHERNET_MMC_TX_INTERRUPT_MASK_TXUFLOWERPIM  0x2000U      // MMC Transmit Underflow Error
                                               // Packet Counter Interrupt Mask
#define ETHERNET_MMC_TX_INTERRUPT_MASK_TXSCOLGPIM  0x4000U      // MMC Transmit Single Collision
                                               // Good Packet Counter Interrupt
                                               // Mask
#define ETHERNET_MMC_TX_INTERRUPT_MASK_TXMCOLGPIM  0x8000U      // MMC Transmit Multiple
                                               // Collision Good Packet Counter
                                               // Interrupt Mask
#define ETHERNET_MMC_TX_INTERRUPT_MASK_TXDEFPIM  0x10000U     // MMC Transmit Deferred Packet
                                               // Counter Interrupt Mask
#define ETHERNET_MMC_TX_INTERRUPT_MASK_TXLATCOLPIM  0x20000U     // MMC Transmit Late Collision
                                               // Packet Counter Interrupt Mask
#define ETHERNET_MMC_TX_INTERRUPT_MASK_TXEXCOLPIM  0x40000U     // MMC Transmit Excessive
                                               // Collision Packet Counter Interrupt
                                               // Mask
#define ETHERNET_MMC_TX_INTERRUPT_MASK_TXCARERPIM  0x80000U     // MMC Transmit Carrier Error
                                               // Packet Counter Interrupt Mask
#define ETHERNET_MMC_TX_INTERRUPT_MASK_TXGOCTIM  0x100000U    // MMC Transmit Good Octet
                                               // Counter Interrupt Mask
#define ETHERNET_MMC_TX_INTERRUPT_MASK_TXGPKTIM  0x200000U    // MMC Transmit Good Packet
                                               // Counter Interrupt Mask
#define ETHERNET_MMC_TX_INTERRUPT_MASK_TXEXDEFPIM  0x400000U    // MMC Transmit Excessive
                                               // Deferral Packet Counter Interrupt
                                               // Mask
#define ETHERNET_MMC_TX_INTERRUPT_MASK_TXPAUSPIM  0x800000U    // MMC Transmit Pause Packet
                                               // Counter Interrupt Mask
#define ETHERNET_MMC_TX_INTERRUPT_MASK_TXVLANGPIM  0x1000000U   // MMC Transmit VLAN Good Packet
                                               // Counter Interrupt Mask
#define ETHERNET_MMC_TX_INTERRUPT_MASK_TXOSIZEGPIM  0x2000000U   // MMC Transmit Oversize Good
                                               // Packet Counter Interrupt Mask
#define ETHERNET_MMC_TX_INTERRUPT_MASK_TXLPIUSCIM  0x4000000U   // MMC Transmit LPI microsecond
                                               // counter interrupt Mask
#define ETHERNET_MMC_TX_INTERRUPT_MASK_TXLPITRCIM  0x8000000U   // MMC Transmit LPI transition
                                               // counter interrupt Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the MMC_IPC_RX_INTERRUPT_MASK register
//
//*****************************************************************************
#define ETHERNET_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4GPIM  0x1U         // MMC Receive IPV4 Good Packet
                                               // Counter Interrupt Mask
#define ETHERNET_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4HERPIM  0x2U         // MMC Receive IPV4 Header Error
                                               // Packet Counter Interrupt Mask
#define ETHERNET_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4NOPAYPIM  0x4U         // MMC Receive IPV4 No Payload
                                               // Packet Counter Interrupt Mask
#define ETHERNET_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4FRAGPIM  0x8U         // MMC Receive IPV4 Fragmented
                                               // Packet Counter Interrupt Mask
#define ETHERNET_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4UDSBLPIM  0x10U        // MMC Receive IPV4 UDP Checksum
                                               // Disabled Packet Counter
                                               // Interrupt Mask
#define ETHERNET_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6GPIM  0x20U        // MMC Receive IPV6 Good Packet
                                               // Counter Interrupt Mask
#define ETHERNET_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6HERPIM  0x40U        // MMC Receive IPV6 Header Error
                                               // Packet Counter Interrupt Mask
#define ETHERNET_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6NOPAYPIM  0x80U        // MMC Receive IPV6 No Payload
                                               // Packet Counter Interrupt Mask
#define ETHERNET_MMC_IPC_RX_INTERRUPT_MASK_RXUDPGPIM  0x100U       // MMC Receive UDP Good Packet
                                               // Counter Interrupt Mask
#define ETHERNET_MMC_IPC_RX_INTERRUPT_MASK_RXUDPERPIM  0x200U       // MMC Receive UDP Error Packet
                                               // Counter Interrupt Mask
#define ETHERNET_MMC_IPC_RX_INTERRUPT_MASK_RXTCPGPIM  0x400U       // MMC Receive TCP Good Packet
                                               // Counter Interrupt Mask
#define ETHERNET_MMC_IPC_RX_INTERRUPT_MASK_RXTCPERPIM  0x800U       // MMC Receive TCP Error Packet
                                               // Counter Interrupt Mask
#define ETHERNET_MMC_IPC_RX_INTERRUPT_MASK_RXICMPGPIM  0x1000U      // MMC Receive ICMP Good Packet
                                               // Counter Interrupt Mask
#define ETHERNET_MMC_IPC_RX_INTERRUPT_MASK_RXICMPERPIM  0x2000U      // MMC Receive ICMP Error Packet
                                               // Counter Interrupt Mask
#define ETHERNET_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4GOIM  0x10000U     // MMC Receive IPV4 Good Octet
                                               // Counter Interrupt Mask
#define ETHERNET_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4HEROIM  0x20000U     // MMC Receive IPV4 Header Error
                                               // Octet Counter Interrupt Mask
#define ETHERNET_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4NOPAYOIM  0x40000U     // MMC Receive IPV4 No Payload
                                               // Octet Counter Interrupt Mask
#define ETHERNET_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4FRAGOIM  0x80000U     // MMC Receive IPV4 Fragmented
                                               // Octet Counter Interrupt Mask
#define ETHERNET_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4UDSBLOIM  0x100000U    // MMC Receive IPV4 UDP Checksum
                                               // Disabled Octet Counter
                                               // Interrupt Mask
#define ETHERNET_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6GOIM  0x200000U    // MMC Receive IPV6 Good Octet
                                               // Counter Interrupt Mask
#define ETHERNET_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6HEROIM  0x400000U    // MMC Receive IPV6 Good Octet
                                               // Counter Interrupt Mask
#define ETHERNET_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6NOPAYOIM  0x800000U    // MMC Receive IPV6 Header Error
                                               // Octet Counter Interrupt Mask
#define ETHERNET_MMC_IPC_RX_INTERRUPT_MASK_RXUDPGOIM  0x1000000U   // MMC Receive IPV6 No Payload
                                               // Octet Counter Interrupt Mask
#define ETHERNET_MMC_IPC_RX_INTERRUPT_MASK_RXUDPEROIM  0x2000000U   // MMC Receive UDP Good Octet
                                               // Counter Interrupt Mask
#define ETHERNET_MMC_IPC_RX_INTERRUPT_MASK_RXTCPGOIM  0x4000000U   // MMC Receive TCP Good Octet
                                               // Counter Interrupt Mask
#define ETHERNET_MMC_IPC_RX_INTERRUPT_MASK_RXTCPEROIM  0x8000000U   // MMC Receive TCP Error Octet
                                               // Counter Interrupt Mask
#define ETHERNET_MMC_IPC_RX_INTERRUPT_MASK_RXICMPGOIM  0x10000000U  // MMC Receive ICMP Good Octet
                                               // Counter Interrupt Mask
#define ETHERNET_MMC_IPC_RX_INTERRUPT_MASK_RXICMPEROIM  0x20000000U  // MMC Receive ICMP Error Octet
                                               // Counter Interrupt Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the MMC_IPC_RX_INTERRUPT register
//
//*****************************************************************************
#define ETHERNET_MMC_IPC_RX_INTERRUPT_RXIPV4GPIS  0x1U         // MMC Receive IPV4 Good Packet
                                               // Counter Interrupt Status
#define ETHERNET_MMC_IPC_RX_INTERRUPT_RXIPV4HERPIS  0x2U         // MMC Receive IPV4 Header Error
                                               // Packet Counter Interrupt
                                               // Status
#define ETHERNET_MMC_IPC_RX_INTERRUPT_RXIPV4NOPAYPIS  0x4U         // MMC Receive IPV4 No Payload
                                               // Packet Counter Interrupt Status
#define ETHERNET_MMC_IPC_RX_INTERRUPT_RXIPV4FRAGPIS  0x8U         // MMC Receive IPV4 Fragmented
                                               // Packet Counter Interrupt Status
#define ETHERNET_MMC_IPC_RX_INTERRUPT_RXIPV4UDSBLPIS  0x10U        // MMC Receive IPV4 UDP Checksum
                                               // Disabled Packet Counter
                                               // Interrupt Status
#define ETHERNET_MMC_IPC_RX_INTERRUPT_RXIPV6GPIS  0x20U        // MMC Receive IPV6 Good Packet
                                               // Counter Interrupt Status
#define ETHERNET_MMC_IPC_RX_INTERRUPT_RXIPV6HERPIS  0x40U        // MMC Receive IPV6 Header Error
                                               // Packet Counter Interrupt
                                               // Status
#define ETHERNET_MMC_IPC_RX_INTERRUPT_RXIPV6NOPAYPIS  0x80U        // MMC Receive IPV6 No Payload
                                               // Packet Counter Interrupt Status
#define ETHERNET_MMC_IPC_RX_INTERRUPT_RXUDPGPIS  0x100U       // MC Receive UDP Good Packet
                                               // Counter Interrupt Status
#define ETHERNET_MMC_IPC_RX_INTERRUPT_RXUDPERPIS  0x200U       // MMC Receive UDP Error Packet
                                               // Counter Interrupt Status
#define ETHERNET_MMC_IPC_RX_INTERRUPT_RXTCPGPIS  0x400U       // MMC Receive TCP Good Packet
                                               // Counter Interrupt Status
#define ETHERNET_MMC_IPC_RX_INTERRUPT_RXTCPERPIS  0x800U       // MMC Receive TCP Error Packet
                                               // Counter Interrupt Status
#define ETHERNET_MMC_IPC_RX_INTERRUPT_RXICMPGPIS  0x1000U      // MMC Receive ICMP Good Packet
                                               // Counter Interrupt Status
#define ETHERNET_MMC_IPC_RX_INTERRUPT_RXICMPERPIS  0x2000U      // MMC Receive ICMP Error Packet
                                               // Counter Interrupt Status
#define ETHERNET_MMC_IPC_RX_INTERRUPT_RXIPV4GOIS  0x10000U     // MMC Receive IPV4 Good Octet
                                               // Counter Interrupt Status
#define ETHERNET_MMC_IPC_RX_INTERRUPT_RXIPV4HEROIS  0x20000U     // MMC Receive IPV4 Header Error
                                               // Octet Counter Interrupt
                                               // Status
#define ETHERNET_MMC_IPC_RX_INTERRUPT_RXIPV4NOPAYOIS  0x40000U     // MMC Receive IPV4 No Payload
                                               // Octet Counter Interrupt Status
#define ETHERNET_MMC_IPC_RX_INTERRUPT_RXIPV4FRAGOIS  0x80000U     // MMC Receive IPV4 Fragmented
                                               // Octet Counter Interrupt Status
#define ETHERNET_MMC_IPC_RX_INTERRUPT_RXIPV4UDSBLOIS  0x100000U    // MMC Receive IPV4 UDP Checksum
                                               // Disabled Octet Counter
                                               // Interrupt
#define ETHERNET_MMC_IPC_RX_INTERRUPT_RXIPV6GOIS  0x200000U    // MMC Receive IPV6 Good Octet
                                               // Counter Interrupt Status
#define ETHERNET_MMC_IPC_RX_INTERRUPT_RXIPV6HEROIS  0x400000U    // MMC Receive IPV6 Header Error
                                               // Octet Counter Interrupt
                                               // Status
#define ETHERNET_MMC_IPC_RX_INTERRUPT_RXIPV6NOPAYOIS  0x800000U    // MMC Receive IPV6 No Payload
                                               // Octet Counter Interrupt Status
#define ETHERNET_MMC_IPC_RX_INTERRUPT_RXUDPGOIS  0x1000000U   // MMC Receive UDP Good Octet
                                               // Counter Interrupt Status
#define ETHERNET_MMC_IPC_RX_INTERRUPT_RXUDPEROIS  0x2000000U   // MMC Receive UDP Error Octet
                                               // Counter Interrupt Status
#define ETHERNET_MMC_IPC_RX_INTERRUPT_RXTCPGOIS  0x4000000U   // MMC Receive TCP Good Octet
                                               // Counter Interrupt Status
#define ETHERNET_MMC_IPC_RX_INTERRUPT_RXTCPEROIS  0x8000000U   // MMC Receive TCP Error Octet
                                               // Counter Interrupt Status
#define ETHERNET_MMC_IPC_RX_INTERRUPT_RXICMPGOIS  0x10000000U  // MMC Receive ICMP Good Octet
                                               // Counter Interrupt Status
#define ETHERNET_MMC_IPC_RX_INTERRUPT_RXICMPEROIS  0x20000000U  // MMC Receive ICMP Error Octet
                                               // Counter Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_L3_L4_CONTROL0 register
//
//*****************************************************************************
#define ETHERNET_MAC_L3_L4_CONTROL0_L3PEN0  0x1U         // Layer 3 Protocol Enable
#define ETHERNET_MAC_L3_L4_CONTROL0_L3PEN0_DISABLE  0x0U
#define ETHERNET_MAC_L3_L4_CONTROL0_L3PEN0_ENABLE  0x1U
#define ETHERNET_MAC_L3_L4_CONTROL0_L3SAM0  0x4U         // Layer 3 IP SA Match Enable
#define ETHERNET_MAC_L3_L4_CONTROL0_L3SAM0_DISABLE  0x0U
#define ETHERNET_MAC_L3_L4_CONTROL0_L3SAM0_ENABLE  0x1U
#define ETHERNET_MAC_L3_L4_CONTROL0_L3SAIM0  0x8U         // Layer 3 IP SA Inverse Match
                                               // Enable
#define ETHERNET_MAC_L3_L4_CONTROL0_L3SAIM0_DISABLE  0x0U
#define ETHERNET_MAC_L3_L4_CONTROL0_L3SAIM0_ENABLE  0x1U
#define ETHERNET_MAC_L3_L4_CONTROL0_L3DAM0  0x10U        // Layer 3 IP DA Match Enable
#define ETHERNET_MAC_L3_L4_CONTROL0_L3DAM0_DISABLE  0x0U
#define ETHERNET_MAC_L3_L4_CONTROL0_L3DAM0_ENABLE  0x1U
#define ETHERNET_MAC_L3_L4_CONTROL0_L3DAIM0  0x20U        // Layer 3 IP DA Inverse Match
                                               // Enable
#define ETHERNET_MAC_L3_L4_CONTROL0_L3DAIM0_DISABLE  0x0U
#define ETHERNET_MAC_L3_L4_CONTROL0_L3DAIM0_ENABLE  0x1U
#define ETHERNET_MAC_L3_L4_CONTROL0_L3HSBM0_S  6U
#define ETHERNET_MAC_L3_L4_CONTROL0_L3HSBM0_M  0x7C0U       // Layer 3 IP SA Higher Bits
                                               // Match
#define ETHERNET_MAC_L3_L4_CONTROL0_L3HDBM0_S  11U
#define ETHERNET_MAC_L3_L4_CONTROL0_L3HDBM0_M  0xF800U      // Layer 3 IP DA Higher Bits
                                               // Match
#define ETHERNET_MAC_L3_L4_CONTROL0_L4PEN0  0x10000U     // Layer 4 Protocol Enable
#define ETHERNET_MAC_L3_L4_CONTROL0_L4PEN0_DISABLE  0x0U
#define ETHERNET_MAC_L3_L4_CONTROL0_L4PEN0_ENABLE  0x1U
#define ETHERNET_MAC_L3_L4_CONTROL0_L4SPM0  0x40000U     // Layer 4 Source Port Match
                                               // Enable
#define ETHERNET_MAC_L3_L4_CONTROL0_L4SPM0_DISABLE  0x0U
#define ETHERNET_MAC_L3_L4_CONTROL0_L4SPM0_ENABLE  0x1U
#define ETHERNET_MAC_L3_L4_CONTROL0_L4SPIM0  0x80000U     // Layer 4 Source Port Inverse
                                               // Match Enable
#define ETHERNET_MAC_L3_L4_CONTROL0_L4SPIM0_DISABLE  0x0U
#define ETHERNET_MAC_L3_L4_CONTROL0_L4SPIM0_ENABLE  0x1U
#define ETHERNET_MAC_L3_L4_CONTROL0_L4DPM0  0x100000U    // Layer 4 Destination Port
                                               // Match Enable
#define ETHERNET_MAC_L3_L4_CONTROL0_L4DPM0_DISABLE  0x0U
#define ETHERNET_MAC_L3_L4_CONTROL0_L4DPM0_ENABLE  0x1U
#define ETHERNET_MAC_L3_L4_CONTROL0_L4DPIM0  0x200000U    // Layer 4 Destination Port
                                               // Inverse Match Enable
#define ETHERNET_MAC_L3_L4_CONTROL0_L4DPIM0_DISABLE  0x0U
#define ETHERNET_MAC_L3_L4_CONTROL0_L4DPIM0_ENABLE  0x1U
#define ETHERNET_MAC_L3_L4_CONTROL0_DMCHN0  0x1000000U   // DMA Channel Number 
#define ETHERNET_MAC_L3_L4_CONTROL0_DMCHEN0  0x10000000U  // DMA Channel Select Enable
#define ETHERNET_MAC_L3_L4_CONTROL0_DMCHEN0_DISABLE  0x0U
#define ETHERNET_MAC_L3_L4_CONTROL0_DMCHEN0_ENABLE  0x1U


//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_LAYER4_ADDRESS0 register
//
//*****************************************************************************
#define ETHERNET_MAC_LAYER4_ADDRESS0_L4SP0_S  0U
#define ETHERNET_MAC_LAYER4_ADDRESS0_L4SP0_M  0xFFFFU      // Layer 4 Source Port Number
                                               // Field
#define ETHERNET_MAC_LAYER4_ADDRESS0_L4DP0_S  16U
#define ETHERNET_MAC_LAYER4_ADDRESS0_L4DP0_M  0xFFFF0000U  // Layer 4 Destination Port
                                               // Number Field

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_L3_L4_CONTROL1 register
//
//*****************************************************************************
#define ETHERNET_MAC_L3_L4_CONTROL1_L3PEN1  0x1U         // Layer 3 Protocol Enable
#define ETHERNET_MAC_L3_L4_CONTROL1_L3SAM1  0x4U         // Layer 3 IP SA Match Enable
#define ETHERNET_MAC_L3_L4_CONTROL1_L3SAIM1  0x8U         // Layer 3 IP SA Inverse Match
                                               // Enable
#define ETHERNET_MAC_L3_L4_CONTROL1_L3DAM1  0x10U        // Layer 3 IP DA Match Enable
#define ETHERNET_MAC_L3_L4_CONTROL1_L3DAIM1  0x20U        // Layer 3 IP DA Inverse Match
                                               // Enable
#define ETHERNET_MAC_L3_L4_CONTROL1_L3HSBM1_S  6U
#define ETHERNET_MAC_L3_L4_CONTROL1_L3HSBM1_M  0x7C0U       // Layer 3 IP SA Higher Bits
                                               // Match
#define ETHERNET_MAC_L3_L4_CONTROL1_L3HDBM1_S  11U
#define ETHERNET_MAC_L3_L4_CONTROL1_L3HDBM1_M  0xF800U      // Layer 3 IP DA Higher Bits
                                               // Match
#define ETHERNET_MAC_L3_L4_CONTROL1_L4PEN1  0x10000U     // Layer 4 Protocol Enable
#define ETHERNET_MAC_L3_L4_CONTROL1_L4SPM1  0x40000U     // Layer 4 Source Port Match
                                               // Enable
#define ETHERNET_MAC_L3_L4_CONTROL1_L4SPIM1  0x80000U     // Layer 4 Source Port Inverse
                                               // Match Enable
#define ETHERNET_MAC_L3_L4_CONTROL1_L4DPM1  0x100000U    // Layer 4 Destination Port
                                               // Match Enable
#define ETHERNET_MAC_L3_L4_CONTROL1_L4DPIM1  0x200000U    // Layer 4 Destination Port
                                               // Inverse Match Enable
#define ETHERNET_MAC_L3_L4_CONTROL1_DMCHN1  0x1000000U   // DMA Channel Number
#define ETHERNET_MAC_L3_L4_CONTROL1_DMCHEN1  0x10000000U  // DMA Channel Select Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_LAYER4_ADDRESS1 register
//
//*****************************************************************************
#define ETHERNET_MAC_LAYER4_ADDRESS1_L4SP1_S  0U
#define ETHERNET_MAC_LAYER4_ADDRESS1_L4SP1_M  0xFFFFU      // Layer 4 Source Port Number
                                               // Field
#define ETHERNET_MAC_LAYER4_ADDRESS1_L4DP1_S  16U
#define ETHERNET_MAC_LAYER4_ADDRESS1_L4DP1_M  0xFFFF0000U  // Layer 4 Destination Port
                                               // Number Field

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_L3_L4_CONTROL2 register
//
//*****************************************************************************
#define ETHERNET_MAC_L3_L4_CONTROL2_L3PEN2  0x1U         // Layer 3 Protocol Enable
#define ETHERNET_MAC_L3_L4_CONTROL2_L3SAM2  0x4U         // Layer 3 IP SA Match Enable
#define ETHERNET_MAC_L3_L4_CONTROL2_L3SAIM2  0x8U         // Layer 3 IP SA Inverse Match
                                               // Enable
#define ETHERNET_MAC_L3_L4_CONTROL2_L3DAM2  0x10U        // Layer 3 IP DA Match Enable
#define ETHERNET_MAC_L3_L4_CONTROL2_L3DAIM2  0x20U        // Layer 3 IP DA Inverse Match
                                               // Enable
#define ETHERNET_MAC_L3_L4_CONTROL2_L3HSBM2_S  6U
#define ETHERNET_MAC_L3_L4_CONTROL2_L3HSBM2_M  0x7C0U       // Layer 3 IP SA Higher Bits
                                               // Match
#define ETHERNET_MAC_L3_L4_CONTROL2_L3HDBM2_S  11U
#define ETHERNET_MAC_L3_L4_CONTROL2_L3HDBM2_M  0xF800U      // Layer 3 IP DA Higher Bits
                                               // Match
#define ETHERNET_MAC_L3_L4_CONTROL2_L4PEN2  0x10000U     // Layer 4 Protocol Enable
#define ETHERNET_MAC_L3_L4_CONTROL2_L4SPM2  0x40000U     // Layer 4 Source Port Match
                                               // Enable
#define ETHERNET_MAC_L3_L4_CONTROL2_L4SPIM2  0x80000U     // Layer 4 Source Port Inverse
                                               // Match Enable
#define ETHERNET_MAC_L3_L4_CONTROL2_L4DPM2  0x100000U    // Layer 4 Destination Port
                                               // Match Enable
#define ETHERNET_MAC_L3_L4_CONTROL2_L4DPIM2  0x200000U    // Layer 4 Destination Port
                                               // Inverse Match Enable
#define ETHERNET_MAC_L3_L4_CONTROL2_DMCHN2  0x1000000U   // DMA Channel Number
#define ETHERNET_MAC_L3_L4_CONTROL2_DMCHEN2  0x10000000U  // DMA Channel Select Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_LAYER4_ADDRESS2 register
//
//*****************************************************************************
#define ETHERNET_MAC_LAYER4_ADDRESS2_L4SP2_S  0U
#define ETHERNET_MAC_LAYER4_ADDRESS2_L4SP2_M  0xFFFFU      // Layer 4 Source Port Number
                                               // Field
#define ETHERNET_MAC_LAYER4_ADDRESS2_L4DP2_S  16U
#define ETHERNET_MAC_LAYER4_ADDRESS2_L4DP2_M  0xFFFF0000U  // Layer 4 Destination Port
                                               // Number Field

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_L3_L4_CONTROL3 register
//
//*****************************************************************************
#define ETHERNET_MAC_L3_L4_CONTROL3_L3PEN3  0x1U         // Layer 3 Protocol Enable
#define ETHERNET_MAC_L3_L4_CONTROL3_L3SAM3  0x4U         // Layer 3 IP SA Match Enable
#define ETHERNET_MAC_L3_L4_CONTROL3_L3SAIM3  0x8U         // Layer 3 IP SA Inverse Match
                                               // Enable
#define ETHERNET_MAC_L3_L4_CONTROL3_L3DAM3  0x10U        // Layer 3 IP DA Match Enable
#define ETHERNET_MAC_L3_L4_CONTROL3_L3DAIM3  0x20U        // Layer 3 IP DA Inverse Match
                                               // Enable
#define ETHERNET_MAC_L3_L4_CONTROL3_L3HSBM3_S  6U
#define ETHERNET_MAC_L3_L4_CONTROL3_L3HSBM3_M  0x7C0U       // Layer 3 IP SA Higher Bits
                                               // Match
#define ETHERNET_MAC_L3_L4_CONTROL3_L3HDBM3_S  11U
#define ETHERNET_MAC_L3_L4_CONTROL3_L3HDBM3_M  0xF800U      // Layer 3 IP DA Higher Bits
                                               // Match
#define ETHERNET_MAC_L3_L4_CONTROL3_L4PEN3  0x10000U     // Layer 4 Protocol Enable
#define ETHERNET_MAC_L3_L4_CONTROL3_L4SPM3  0x40000U     // Layer 4 Source Port Match
                                               // Enable
#define ETHERNET_MAC_L3_L4_CONTROL3_L4SPIM3  0x80000U     // Layer 4 Source Port Inverse
                                               // Match Enable
#define ETHERNET_MAC_L3_L4_CONTROL3_L4DPM3  0x100000U    // Layer 4 Destination Port
                                               // Match Enable
#define ETHERNET_MAC_L3_L4_CONTROL3_L4DPIM3  0x200000U    // Layer 4 Destination Port
                                               // Inverse Match Enable
#define ETHERNET_MAC_L3_L4_CONTROL3_DMCHN3  0x1000000U   // DMA Channel Number
#define ETHERNET_MAC_L3_L4_CONTROL3_DMCHEN3  0x10000000U  // DMA Channel Select Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_LAYER4_ADDRESS3 register
//
//*****************************************************************************
#define ETHERNET_MAC_LAYER4_ADDRESS3_L4SP3_S  0U
#define ETHERNET_MAC_LAYER4_ADDRESS3_L4SP3_M  0xFFFFU      // Layer 4 Source Port Number
                                               // Field
#define ETHERNET_MAC_LAYER4_ADDRESS3_L4DP3_S  16U
#define ETHERNET_MAC_LAYER4_ADDRESS3_L4DP3_M  0xFFFF0000U  // Layer 4 Destination Port
                                               // Number Field

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_TIMESTAMP_CONTROL register
//
//*****************************************************************************
#define ETHERNET_MAC_TIMESTAMP_CONTROL_TSENA  0x1U         // Enable Timestamp
#define ETHERNET_MAC_TIMESTAMP_CONTROL_TSCFUPDT  0x2U         // Fine or Coarse Timestamp
                                               // Update
#define ETHERNET_MAC_TIMESTAMP_CONTROL_TSINIT  0x4U         // Initialize Timestamp
#define ETHERNET_MAC_TIMESTAMP_CONTROL_TSUPDT  0x8U         // Update Timestamp
#define ETHERNET_MAC_TIMESTAMP_CONTROL_TSTRIG  0x10U        // Enable Timestamp Interrupt
                                               // Trigger
#define ETHERNET_MAC_TIMESTAMP_CONTROL_TSADDREG  0x20U        // Update Addend Register
#define ETHERNET_MAC_TIMESTAMP_CONTROL_TSENALL  0x100U       // Enable Timestamp for All
                                               // Packets
#define ETHERNET_MAC_TIMESTAMP_CONTROL_TSCTRLSSR  0x200U       // Timestamp Digital or Binary
                                               // Rollover Control
#define ETHERNET_MAC_TIMESTAMP_CONTROL_TSVER2ENA  0x400U       // Enable PTP Packet Processing
                                               // for Version 2 Format
#define ETHERNET_MAC_TIMESTAMP_CONTROL_TSIPENA  0x800U       // Enable Processing of PTP over
                                               // Ethernet Packets
#define ETHERNET_MAC_TIMESTAMP_CONTROL_TSIPV6ENA  0x1000U      // Enable Processing of PTP
                                               // Packets Sent over IPv6-UDP
#define ETHERNET_MAC_TIMESTAMP_CONTROL_TSIPV4ENA  0x2000U      // Enable Processing of PTP
                                               // Packets Sent over IPv4-UDP
#define ETHERNET_MAC_TIMESTAMP_CONTROL_TSEVNTENA  0x4000U      // Enable Timestamp Snapshot for
                                               // Event Messages
#define ETHERNET_MAC_TIMESTAMP_CONTROL_TSMSTRENA  0x8000U      // Enable Snapshot for Messages
                                               // Relevant to Master
#define ETHERNET_MAC_TIMESTAMP_CONTROL_SNAPTYPSEL_S  16U
#define ETHERNET_MAC_TIMESTAMP_CONTROL_SNAPTYPSEL_M  0x30000U     // Select PTP packets for Taking
                                               // Snapshots
#define ETHERNET_MAC_TIMESTAMP_CONTROL_TSENMACADDR  0x40000U     // Enable MAC Address for PTP
                                               // Packet Filtering
#define ETHERNET_MAC_TIMESTAMP_CONTROL_CSC  0x80000U     // Enable checksum correction
                                               // during OST for PTP over UDP/IPv4
                                               // packets
#define ETHERNET_MAC_TIMESTAMP_CONTROL_ESTI  0x100000U    // External System Time Input
#define ETHERNET_MAC_TIMESTAMP_CONTROL_TXTSSTSM  0x1000000U   // Transmit Timestamp Status
                                               // Mode
#define ETHERNET_MAC_TIMESTAMP_CONTROL_AV8021ASMEN  0x10000000U  // AV 802.1AS Mode Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_SUB_SECOND_INCREMENT register
//
//*****************************************************************************
#define ETHERNET_MAC_SUB_SECOND_INCREMENT_SNSINC_S  8U
#define ETHERNET_MAC_SUB_SECOND_INCREMENT_SNSINC_M  0xFF00U      // Sub-nanosecond Increment
                                               // Value
#define ETHERNET_MAC_SUB_SECOND_INCREMENT_SSINC_S  16U
#define ETHERNET_MAC_SUB_SECOND_INCREMENT_SSINC_M  0xFF0000U    // Sub-second Increment Value

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_SYSTEM_TIME_NANOSECONDS register
//
//*****************************************************************************
#define ETHERNET_MAC_SYSTEM_TIME_NANOSECONDS_TSSS_S  0U
#define ETHERNET_MAC_SYSTEM_TIME_NANOSECONDS_TSSS_M  0x7FFFFFFFU  // Timestamp Sub Seconds

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_SYSTEM_TIME_NANOSECONDS_UPDATE register
//
//*****************************************************************************
#define ETHERNET_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_TSSS_S  0U
#define ETHERNET_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_TSSS_M  0x7FFFFFFFU  // Timestamp Sub Seconds
#define ETHERNET_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_ADDSUB  0x80000000U  // Add or Subtract Time

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS register
//
//*****************************************************************************
#define ETHERNET_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS_TSHWR_S  0U
#define ETHERNET_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS_TSHWR_M  0xFFFFU      // Timestamp Higher Word
                                               // Register

//*****************************************************************************
// The following are defines for the bit fields in the MAC_TIMESTAMP_STATUS register
//
//*****************************************************************************
#define ETHERNET_MAC_TIMESTAMP_STATUS_TSSOVF  0x1U         // Timestamp Seconds Overflow
#define ETHERNET_MAC_TIMESTAMP_STATUS_TSTARGT0  0x2U         // Timestamp Target Time Reached
#define ETHERNET_MAC_TIMESTAMP_STATUS_AUXTSTRIG  0x4U         // Auxiliary Timestamp Trigger
                                               // Snapshot
#define ETHERNET_MAC_TIMESTAMP_STATUS_TSTRGTERR0  0x8U         // Timestamp Target Time Error
#define ETHERNET_MAC_TIMESTAMP_STATUS_TSTARGT1  0x10U        // Timestamp Target Time Reached
                                               // for Target Time PPS1
#define ETHERNET_MAC_TIMESTAMP_STATUS_TSTRGTERR1  0x20U        // Timestamp Target Time Error
#define ETHERNET_MAC_TIMESTAMP_STATUS_TSTARGT2  0x40U        // Timestamp Target Time Reached
                                               // for Target Time PPS2
#define ETHERNET_MAC_TIMESTAMP_STATUS_TSTRGTERR2  0x80U        // Timestamp Target Time Error
#define ETHERNET_MAC_TIMESTAMP_STATUS_TSTARGT3  0x100U       // Timestamp Target Time Reached
                                               // for Target Time PPS3
#define ETHERNET_MAC_TIMESTAMP_STATUS_TSTRGTERR3  0x200U       // Timestamp Target Time Error
#define ETHERNET_MAC_TIMESTAMP_STATUS_TXTSSIS  0x8000U      // Tx Timestamp Status Interrupt
                                               // Status
#define ETHERNET_MAC_TIMESTAMP_STATUS_ATSSTN_S  16U
#define ETHERNET_MAC_TIMESTAMP_STATUS_ATSSTN_M  0xF0000U     // Auxiliary Timestamp Snapshot
                                               // Trigger Identifier
#define ETHERNET_MAC_TIMESTAMP_STATUS_ATSSTM  0x1000000U   // Auxiliary Timestamp Snapshot
                                               // Trigger Missed
#define ETHERNET_MAC_TIMESTAMP_STATUS_ATSNS_S  25U
#define ETHERNET_MAC_TIMESTAMP_STATUS_ATSNS_M  0x3E000000U  // Number of Auxiliary Timestamp
                                               // Snapshots

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_TX_TIMESTAMP_STATUS_NANOSECONDS register
//
//*****************************************************************************
#define ETHERNET_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_TXTSSLO_S  0U
#define ETHERNET_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_TXTSSLO_M  0x7FFFFFFFU  // Transmit Timestamp Status Low
#define ETHERNET_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_TXTSSMIS  0x80000000U  // Transmit Timestamp Status
                                               // Missed

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_AUXILIARY_CONTROL register
//
//*****************************************************************************
#define ETHERNET_MAC_AUXILIARY_CONTROL_ATSFC  0x1U         // Auxiliary Snapshot FIFO Clear
#define ETHERNET_MAC_AUXILIARY_CONTROL_ATSEN0  0x10U        // Auxiliary Snapshot 0 Enable
#define ETHERNET_MAC_AUXILIARY_CONTROL_ATSEN1  0x20U        // Auxiliary Snapshot 1 Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_AUXILIARY_TIMESTAMP_NANOSECONDS register
//
//*****************************************************************************
#define ETHERNET_MAC_AUXILIARY_TIMESTAMP_NANOSECONDS_AUXTSLO_S  0U
#define ETHERNET_MAC_AUXILIARY_TIMESTAMP_NANOSECONDS_AUXTSLO_M  0x7FFFFFFFU  // Auxiliary Timestamp

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC register
//
//*****************************************************************************
#define ETHERNET_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC_TSICSNS_S  8U
#define ETHERNET_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC_TSICSNS_M  0xFF00U      // Timestamp Ingress Correction,
                                               // sub-nanoseconds

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC register
//
//*****************************************************************************
#define ETHERNET_MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC_TSECSNS_S  8U
#define ETHERNET_MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC_TSECSNS_M  0xFF00U      // Timestamp Egress Correction,
                                               // sub-nanoseconds

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_PPS_CONTROL register
//
//*****************************************************************************
#define ETHERNET_MAC_PPS_CONTROL_PPSCTRL_PPSCMD_S  0U
#define ETHERNET_MAC_PPS_CONTROL_PPSCTRL_PPSCMD_M  0xFU         // PPS Output Frequency Control

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_PTO_CONTROL register
//
//*****************************************************************************
#define ETHERNET_MAC_PTO_CONTROL_PTOEN  0x1U         // PTP Offload Enable
#define ETHERNET_MAC_PTO_CONTROL_ASYNCEN  0x2U         // Automatic PTP SYNC message
                                               // Enable
#define ETHERNET_MAC_PTO_CONTROL_APDREQEN  0x4U         // Automatic PTP Pdelay_Req
                                               // message Enable
#define ETHERNET_MAC_PTO_CONTROL_ASYNCTRIG  0x10U        // Automatic PTP SYNC message
                                               // Trigger
#define ETHERNET_MAC_PTO_CONTROL_APDREQTRIG  0x20U        // Automatic PTP Pdelay_Req
                                               // message Trigger
#define ETHERNET_MAC_PTO_CONTROL_DRRDIS  0x40U        // Disable PTO Delay
                                               // Request/Response response generation
#define ETHERNET_MAC_PTO_CONTROL_PDRDIS  0x80U        // Reserved
#define ETHERNET_MAC_PTO_CONTROL_DN_S  8U
#define ETHERNET_MAC_PTO_CONTROL_DN_M  0xFF00U      // Domain Number

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_SOURCE_PORT_IDENTITY2 register
//
//*****************************************************************************
#define ETHERNET_MAC_SOURCE_PORT_IDENTITY2_SPI2_S  0U
#define ETHERNET_MAC_SOURCE_PORT_IDENTITY2_SPI2_M  0xFFFFU      // Source Port Identity 2

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_LOG_MESSAGE_INTERVAL register
//
//*****************************************************************************
#define ETHERNET_MAC_LOG_MESSAGE_INTERVAL_LSI_S  0U
#define ETHERNET_MAC_LOG_MESSAGE_INTERVAL_LSI_M  0xFFU        // Log Sync Interval
#define ETHERNET_MAC_LOG_MESSAGE_INTERVAL_DRSYNCR_S  8U
#define ETHERNET_MAC_LOG_MESSAGE_INTERVAL_DRSYNCR_M  0x700U       // Delay_Req to SYNC Ratio

#define ETHERNET_MAC_LOG_MESSAGE_INTERVAL_LMPDRI_S  24U
#define ETHERNET_MAC_LOG_MESSAGE_INTERVAL_LMPDRI_M  0xFF000000U  // Log Min Pdelay_Req Interval

//*****************************************************************************
//
// The following are defines for the bit fields in the DMA_MODE register
//
//*****************************************************************************
#define ETHERNET_DMA_MODE_SWR         0x1U         // Software Reset
#define ETHERNET_DMA_MODE_DA          0x2U         // DMA Tx or Rx Arbitration
                                               // Scheme
#define ETHERNET_DMA_MODE_TAA_S       2U
#define ETHERNET_DMA_MODE_TAA_M       0x1CU        // Transmit Arbitration
                                               // Algorithm
#define ETHERNET_DMA_MODE_TXPR        0x800U       // Transmit Priority
#define ETHERNET_DMA_MODE_PR_S        12U
#define ETHERNET_DMA_MODE_PR_M        0x7000U      // Priority Ratio
#define ETHERNET_DMA_MODE_INTM_S      16U
#define ETHERNET_DMA_MODE_INTM_M      0x30000U     // Interrupt Mode

//*****************************************************************************
//
// The following are defines for the bit fields in the DMA_SYSBUS_MODE register
//
//*****************************************************************************
#define ETHERNET_DMA_SYSBUS_MODE_FB   0x1U         // Fixed Burst Length
#define ETHERNET_DMA_SYSBUS_MODE_AAL  0x1000U      // Address-Aligned Beats
#define ETHERNET_DMA_SYSBUS_MODE_MB   0x4000U      // Mixed Burst
#define ETHERNET_DMA_SYSBUS_MODE_RB   0x8000U      // Rebuild INCRx Burst

//*****************************************************************************
//
// The following are defines for the bit fields in the DMA_INTERRUPT_STATUS register
//
//*****************************************************************************
#define ETHERNET_DMA_INTERRUPT_STATUS_DC0IS  0x1U         // DMA Channel 0 Interrupt
                                               // Status
#define ETHERNET_DMA_INTERRUPT_STATUS_DC1IS  0x2U         // DMA Channel 1 Interrupt
                                               // Status
#define ETHERNET_DMA_INTERRUPT_STATUS_MTLIS  0x10000U     // MTL Interrupt Status
#define ETHERNET_DMA_INTERRUPT_STATUS_MACIS  0x20000U     // MAC Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the DMA_DEBUG_STATUS0 register
//
//*****************************************************************************
#define ETHERNET_DMA_DEBUG_STATUS0_AXWHSTS  0x1U         // AHB Master Status
#define ETHERNET_DMA_DEBUG_STATUS0_RPS0_RSVD  0x2U
#define ETHERNET_DMA_DEBUG_STATUS0_RPS0_RUN_CRD  0x5U
#define ETHERNET_DMA_DEBUG_STATUS0_RPS0_RUN_FRTD  0x1U
#define ETHERNET_DMA_DEBUG_STATUS0_RPS0_RUN_TRP  0x7U
#define ETHERNET_DMA_DEBUG_STATUS0_RPS0_RUN_WRP  0x3U
#define ETHERNET_DMA_DEBUG_STATUS0_RPS0_STOP  0x0U
#define ETHERNET_DMA_DEBUG_STATUS0_RPS0_SUSPND  0x4U
#define ETHERNET_DMA_DEBUG_STATUS0_RPS0_TSTMP  0x6U
#define ETHERNET_DMA_DEBUG_STATUS0_RPS0_S  8U
#define ETHERNET_DMA_DEBUG_STATUS0_RPS0_M  0xF00U       // DMA Channel 0 Receive Process
                                               // State
#define ETHERNET_DMA_DEBUG_STATUS0_TPS0_RUN_CTD  0x7U
#define ETHERNET_DMA_DEBUG_STATUS0_TPS0_RUN_FTTD  0x1U
#define ETHERNET_DMA_DEBUG_STATUS0_TPS0_RUN_RDS  0x3U
#define ETHERNET_DMA_DEBUG_STATUS0_TPS0_RUN_WS  0x2U
#define ETHERNET_DMA_DEBUG_STATUS0_TPS0_STOP  0x0U
#define ETHERNET_DMA_DEBUG_STATUS0_TPS0_SUSPND  0x6U
#define ETHERNET_DMA_DEBUG_STATUS0_TPS0_TSTMP_WS  0x4U
#define ETHERNET_DMA_DEBUG_STATUS0_TPS0_S  12U
#define ETHERNET_DMA_DEBUG_STATUS0_TPS0_M  0xF000U      // DMA Channel 0 Transmit
                                               // Process State
#define ETHERNET_DMA_DEBUG_STATUS0_RPS1_S  16U
#define ETHERNET_DMA_DEBUG_STATUS0_RPS1_M  0xF0000U     // DMA Channel 1 Receive Process
                                               // State
#define ETHERNET_DMA_DEBUG_STATUS0_TPS1_S  20U
#define ETHERNET_DMA_DEBUG_STATUS0_TPS1_M  0xF00000U    // DMA Channel 1 Transmit
                                               // Process State

//*****************************************************************************
//
// The following are defines for the bit fields in the DMA_CH0_CONTROL register
//
//*****************************************************************************
#define ETHERNET_DMA_CH0_CONTROL_MSS_S  0U
#define ETHERNET_DMA_CH0_CONTROL_MSS_M  0x3FFFU      // Maximum Segment Size
#define ETHERNET_DMA_CH0_CONTROL_PBLX8  0x10000U     // 8xPBL mode
#define ETHERNET_DMA_CH0_CONTROL_DSL_S  18U
#define ETHERNET_DMA_CH0_CONTROL_DSL_M  0x1C0000U    // Descriptor Skip Length
#define ETHERNET_DMA_CH0_CONTROL_SPH  0x1000000U   // Split Headers

//*****************************************************************************
//
// The following are defines for the bit fields in the DMA_CH0_TX_CONTROL register
//
//*****************************************************************************
#define ETHERNET_DMA_CH0_TX_CONTROL_ST  0x1U         // Start or Stop Transmission
                                               // Command
#define ETHERNET_DMA_CH0_TX_CONTROL_TCW_S  1U
#define ETHERNET_DMA_CH0_TX_CONTROL_TCW_M  0xEU         // Transmit Channel Weight
#define ETHERNET_DMA_CH0_TX_CONTROL_OSF  0x10U        // Operate on Second Packet
#define ETHERNET_DMA_CH0_TX_CONTROL_TSE  0x1000U      // TCP Segmentation Enabled
#define ETHERNET_DMA_CH0_TX_CONTROL_TXPBL_S  16U
#define ETHERNET_DMA_CH0_TX_CONTROL_TXPBL_M  0x3F0000U    // Transmit Programmable Burst
                                               // Length
#define ETHERNET_DMA_CH0_TX_CONTROL_ETIC  0x400000U    // Early Transmit Interrupt
                                               // Control
#define ETHERNET_DMA_CH0_TX_CONTROL_ETIC_S 22U
#define ETHERNET_DMA_CH0_TX_CONTROL_ETIC_DISABLE  0x0U
#define ETHERNET_DMA_CH0_TX_CONTROL_ETIC_ENABLE  0x1U

#define ETHERNET_DMA_CH0_TX_CONTROL_TSE_M  0x1000U      // TCP Segmentation Enabled

//*****************************************************************************
//
// The following are defines for the bit fields in the DMA_CH0_RX_CONTROL register
//
//*****************************************************************************
#define ETHERNET_DMA_CH0_RX_CONTROL_SR  0x1U         // Start or Stop Receive
#define ETHERNET_DMA_CH0_RX_CONTROL_RBSZ_S  3U
#define ETHERNET_DMA_CH0_RX_CONTROL_RBSZ_M  0x7FF8U      // Receive Buffer size
#define ETHERNET_DMA_CH0_RX_CONTROL_RXPBL_S  16U
#define ETHERNET_DMA_CH0_RX_CONTROL_RXPBL_M  0x3F0000U    // Receive Programmable Burst
                                               // Length
#define ETHERNET_DMA_CH0_RX_CONTROL_RPF  0x80000000U  // DMA Rx Channel0 Packet Flush

#define ETHERNET_DMA_CH0_RX_CONTROL_ERIC  0x400000U    // Early Receive Interrupt
                                               // Control
#define ETHERNET_DMA_CH0_TX_CONTROL_ERIC_S 22U

#define ETHERNET_DMA_CH0_RX_CONTROL_ERIC_DISABLE  0x0U
#define ETHERNET_DMA_CH0_RX_CONTROL_ERIC_ENABLE  0x1U



//*****************************************************************************
//
// The following are defines for the bit fields in the DMA_CH0_TXDESC_LIST_ADDRESS register
//
//*****************************************************************************
#define ETHERNET_DMA_CH0_TXDESC_LIST_ADDRESS_TDESLA_S  2U
#define ETHERNET_DMA_CH0_TXDESC_LIST_ADDRESS_TDESLA_M  0xFFFFFFFCU  // Start of Transmit List

//*****************************************************************************
//
// The following are defines for the bit fields in the DMA_CH0_RXDESC_LIST_ADDRESS register
//
//*****************************************************************************
#define ETHERNET_DMA_CH0_RXDESC_LIST_ADDRESS_RDESLA_S  2U
#define ETHERNET_DMA_CH0_RXDESC_LIST_ADDRESS_RDESLA_M  0xFFFFFFFCU  // Start of Receive List

//*****************************************************************************
//
// The following are defines for the bit fields in the DMA_CH0_TXDESC_TAIL_POINTER register
//
//*****************************************************************************
#define ETHERNET_DMA_CH0_TXDESC_TAIL_POINTER_TDTP_S  2U
#define ETHERNET_DMA_CH0_TXDESC_TAIL_POINTER_TDTP_M  0xFFFFFFFCU  // Transmit Descriptor Tail
                                               // Pointer

//*****************************************************************************
//
// The following are defines for the bit fields in the DMA_CH0_RXDESC_TAIL_POINTER register
//
//*****************************************************************************
#define ETHERNET_DMA_CH0_RXDESC_TAIL_POINTER_RDTP_S  2U
#define ETHERNET_DMA_CH0_RXDESC_TAIL_POINTER_RDTP_M  0xFFFFFFFCU  // Receive Descriptor Tail
                                               // Pointer

//*****************************************************************************
//
// The following are defines for the bit fields in the DMA_CH0_TXDESC_RING_LENGTH register
//
//*****************************************************************************
#define ETHERNET_DMA_CH0_TXDESC_RING_LENGTH_TDRL_S  0U
#define ETHERNET_DMA_CH0_TXDESC_RING_LENGTH_TDRL_M  0x3FFU       // Transmit Descriptor Ring
                                               // Length

//*****************************************************************************
//
// The following are defines for the bit fields in the DMA_CH0_RXDESC_RING_LENGTH register
//
//*****************************************************************************
#define ETHERNET_DMA_CH0_RXDESC_RING_LENGTH_RDRL_S  0U
#define ETHERNET_DMA_CH0_RXDESC_RING_LENGTH_RDRL_M  0x3FFU       // Receive Descriptor Ring
                                               // Length

//*****************************************************************************
//
// The following are defines for the bit fields in the DMA_CH0_INTERRUPT_ENABLE register
//
//*****************************************************************************
#define ETHERNET_DMA_CH0_INTERRUPT_ENABLE_TIE  0x1U         // Transmit Interrupt Enable
#define ETHERNET_DMA_CH0_INTERRUPT_ENABLE_TXSE  0x2U         // Transmit Stopped Enable
#define ETHERNET_DMA_CH0_INTERRUPT_ENABLE_TBUE  0x4U         // Transmit Buffer Unavailable
                                               // Enable
#define ETHERNET_DMA_CH0_INTERRUPT_ENABLE_RIE  0x40U        // Receive Interrupt Enable
#define ETHERNET_DMA_CH0_INTERRUPT_ENABLE_RBUE  0x80U        // Receive Buffer Unavailable
                                               // Enable
#define ETHERNET_DMA_CH0_INTERRUPT_ENABLE_RSE  0x100U       // Receive Stopped Enable
#define ETHERNET_DMA_CH0_INTERRUPT_ENABLE_RWTE  0x200U       // Receive Watchdog Timeout
                                               // Enable
#define ETHERNET_DMA_CH0_INTERRUPT_ENABLE_ETIE  0x400U       // Early Transmit Interrupt
                                               // Enable
#define ETHERNET_DMA_CH0_INTERRUPT_ENABLE_ERIE  0x800U       // Early Receive Interrupt
                                               // Enable
#define ETHERNET_DMA_CH0_INTERRUPT_ENABLE_FBEE  0x1000U      // Fatal Bus Error Enable
#define ETHERNET_DMA_CH0_INTERRUPT_ENABLE_CDEE  0x2000U      // Context Descriptor Error
                                               // Enable
#define ETHERNET_DMA_CH0_INTERRUPT_ENABLE_AIE  0x4000U      // Abnormal Interrupt Summary
                                               // Enable
#define ETHERNET_DMA_CH0_INTERRUPT_ENABLE_NIE  0x8000U      // Normal Interrupt Summary
                                               // Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the DMA_CH0_RX_INTERRUPT_WATCHDOG_TIMER register
//
//*****************************************************************************
#define ETHERNET_DMA_CH0_RX_INTERRUPT_WATCHDOG_TIMER_RWT_S  0U
#define ETHERNET_DMA_CH0_RX_INTERRUPT_WATCHDOG_TIMER_RWT_M  0xFFU        // Receive Interrupt Watchdog
                                               // Timer Count
#define ETHERNET_DMA_CH0_RX_INTERRUPT_WATCHDOG_TIMER_RWTU_S  16U
#define ETHERNET_DMA_CH0_RX_INTERRUPT_WATCHDOG_TIMER_RWTU_M  0x30000U     // Receive Interrupt Watchdog
                                               // Timer Count Units

//*****************************************************************************
//
// The following are defines for the bit fields in the DMA_CH0_STATUS register
//
//*****************************************************************************
#define ETHERNET_DMA_CH0_STATUS_TI    0x1U         // Transmit Interrupt
#define ETHERNET_DMA_CH0_STATUS_TPS   0x2U         // Transmit Process Stopped
#define ETHERNET_DMA_CH0_STATUS_TBU   0x4U         // Transmit Buffer Unavailable
#define ETHERNET_DMA_CH0_STATUS_RI    0x40U        // Receive Interrupt
#define ETHERNET_DMA_CH0_STATUS_RBU   0x80U        // Receive Buffer Unavailable
#define ETHERNET_DMA_CH0_STATUS_RPS   0x100U       // Receive Process Stopped
#define ETHERNET_DMA_CH0_STATUS_RWT   0x200U       // Receive Watchdog Timeout
#define ETHERNET_DMA_CH0_STATUS_ETI   0x400U       // Early Transmit Interrupt
#define ETHERNET_DMA_CH0_STATUS_ERI   0x800U       // Early Receive Interrupt
#define ETHERNET_DMA_CH0_STATUS_FBE   0x1000U      // Fatal Bus Error
#define ETHERNET_DMA_CH0_STATUS_CDE   0x2000U      // Context Descriptor Error
#define ETHERNET_DMA_CH0_STATUS_AIS   0x4000U      // Abnormal Interrupt Summary
#define ETHERNET_DMA_CH0_STATUS_NIS   0x8000U      // Normal Interrupt Summary
#define ETHERNET_DMA_CH0_STATUS_TEB_S  16U
#define ETHERNET_DMA_CH0_STATUS_TEB_M  0x70000U     // Tx DMA Error Bits
#define ETHERNET_DMA_CH0_STATUS_REB_S  19U
#define ETHERNET_DMA_CH0_STATUS_REB_M  0x380000U    // Rx DMA Error Bits

//*****************************************************************************
//
// The following are defines for the bit fields in the DMA_CH0_MISS_FRAME_CNT register
//
//*****************************************************************************
#define ETHERNET_DMA_CH0_MISS_FRAME_CNT_MFC_S  0U
#define ETHERNET_DMA_CH0_MISS_FRAME_CNT_MFC_M  0x7FFU       // Dropped Packet Counters
#define ETHERNET_DMA_CH0_MISS_FRAME_CNT_MFCO  0x8000U      // Overflow status of the MFC
                                               // Counter

//*****************************************************************************
//
// The following are defines for the bit fields in the DMA_CH1_CONTROL register
//
//*****************************************************************************
#define ETHERNET_DMA_CH1_CONTROL_PBLX8  0x10000U     // 8xPBL mode
#define ETHERNET_DMA_CH1_CONTROL_DSL_S  18U
#define ETHERNET_DMA_CH1_CONTROL_DSL_M  0x1C0000U    // Descriptor Skip Length
#define ETHERNET_DMA_CH1_CONTROL_SPH  0x1000000U   // Split Headers

//*****************************************************************************
//
// The following are defines for the bit fields in the DMA_CH1_TX_CONTROL register
//
//*****************************************************************************
#define ETHERNET_DMA_CH1_TX_CONTROL_ST  0x1U         // Start or Stop Transmission
                                               // Command
#define ETHERNET_DMA_CH1_TX_CONTROL_TCW_S  1U
#define ETHERNET_DMA_CH1_TX_CONTROL_TCW_M  0xEU         // Transmit Channel Weight
#define ETHERNET_DMA_CH1_TX_CONTROL_OSF  0x10U        // Operate on Second Packet
#define ETHERNET_DMA_CH1_TX_CONTROL_TSE  0x1000U      // TCP Segmentation Enabled
#define ETHERNET_DMA_CH1_TX_CONTROL_TXPBL_S  16U
#define ETHERNET_DMA_CH1_TX_CONTROL_TXPBL_M  0x3F0000U    // Transmit Programmable Burst
                                               // Length

//*****************************************************************************
//
// The following are defines for the bit fields in the DMA_CH1_RX_CONTROL register
//
//*****************************************************************************
#define ETHERNET_DMA_CH1_RX_CONTROL_SR  0x1U         // Start or Stop Receive
#define ETHERNET_DMA_CH1_RX_CONTROL_RBSZ_S  3U
#define ETHERNET_DMA_CH1_RX_CONTROL_RBSZ_M  0x7FF8U      // Receive Buffer size
#define ETHERNET_DMA_CH1_RX_CONTROL_RXPBL_S  16U
#define ETHERNET_DMA_CH1_RX_CONTROL_RXPBL_M  0x3F0000U    // Receive Programmable Burst
                                               // Length
#define ETHERNET_DMA_CH1_RX_CONTROL_RPF  0x80000000U  // DMA Rx Channel0 Packet Flush

//*****************************************************************************
//
// The following are defines for the bit fields in the DMA_CH1_TXDESC_LIST_ADDRESS register
//
//*****************************************************************************
#define ETHERNET_DMA_CH1_TXDESC_LIST_ADDRESS_TDESLA_S  2U
#define ETHERNET_DMA_CH1_TXDESC_LIST_ADDRESS_TDESLA_M  0xFFFFFFFCU  // Start of Transmit List

//*****************************************************************************
//
// The following are defines for the bit fields in the DMA_CH1_RXDESC_LIST_ADDRESS register
//
//*****************************************************************************
#define ETHERNET_DMA_CH1_RXDESC_LIST_ADDRESS_RDESLA_S  2U
#define ETHERNET_DMA_CH1_RXDESC_LIST_ADDRESS_RDESLA_M  0xFFFFFFFCU  // Start of Receive List

//*****************************************************************************
//
// The following are defines for the bit fields in the DMA_CH1_TXDESC_TAIL_POINTER register
//
//*****************************************************************************
#define ETHERNET_DMA_CH1_TXDESC_TAIL_POINTER_TDTP_S  2U
#define ETHERNET_DMA_CH1_TXDESC_TAIL_POINTER_TDTP_M  0xFFFFFFFCU  // Transmit Descriptor Tail
                                               // Pointer

//*****************************************************************************
//
// The following are defines for the bit fields in the DMA_CH1_RXDESC_TAIL_POINTER register
//
//*****************************************************************************
#define ETHERNET_DMA_CH1_RXDESC_TAIL_POINTER_RDTP_S  2U
#define ETHERNET_DMA_CH1_RXDESC_TAIL_POINTER_RDTP_M  0xFFFFFFFCU  // Receive Descriptor Tail
                                               // Pointer

//*****************************************************************************
//
// The following are defines for the bit fields in the DMA_CH1_TXDESC_RING_LENGTH register
//
//*****************************************************************************
#define ETHERNET_DMA_CH1_TXDESC_RING_LENGTH_TDRL_S  0U
#define ETHERNET_DMA_CH1_TXDESC_RING_LENGTH_TDRL_M  0x3FFU       // Transmit Descriptor Ring
                                               // Length

//*****************************************************************************
//
// The following are defines for the bit fields in the DMA_CH1_RXDESC_RING_LENGTH register
//
//*****************************************************************************
#define ETHERNET_DMA_CH1_RXDESC_RING_LENGTH_RDRL_S  0U
#define ETHERNET_DMA_CH1_RXDESC_RING_LENGTH_RDRL_M  0x3FFU       // Receive Descriptor Ring
                                               // Length

//*****************************************************************************
//
// The following are defines for the bit fields in the DMA_CH1_INTERRUPT_ENABLE register
//
//*****************************************************************************
#define ETHERNET_DMA_CH1_INTERRUPT_ENABLE_TIE  0x1U         // Transmit Interrupt Enable
#define ETHERNET_DMA_CH1_INTERRUPT_ENABLE_TXSE  0x2U         // Transmit Stopped Enable
#define ETHERNET_DMA_CH1_INTERRUPT_ENABLE_TBUE  0x4U         // Transmit Buffer Unavailable
                                               // Enable
#define ETHERNET_DMA_CH1_INTERRUPT_ENABLE_RIE  0x40U        // Receive Interrupt Enable
#define ETHERNET_DMA_CH1_INTERRUPT_ENABLE_RBUE  0x80U        // Receive Buffer Unavailable
                                               // Enable
#define ETHERNET_DMA_CH1_INTERRUPT_ENABLE_RSE  0x100U       // Receive Stopped Enable
#define ETHERNET_DMA_CH1_INTERRUPT_ENABLE_RWTE  0x200U       // Receive Watchdog Timeout
                                               // Enable
#define ETHERNET_DMA_CH1_INTERRUPT_ENABLE_ETIE  0x400U       // Early Transmit Interrupt
                                               // Enable
#define ETHERNET_DMA_CH1_INTERRUPT_ENABLE_ERIE  0x800U       // Early Receive Interrupt
                                               // Enable
#define ETHERNET_DMA_CH1_INTERRUPT_ENABLE_FBEE  0x1000U      // Fatal Bus Error Enable
#define ETHERNET_DMA_CH1_INTERRUPT_ENABLE_CDEE  0x2000U      // Context Descriptor Error
                                               // Enable
#define ETHERNET_DMA_CH1_INTERRUPT_ENABLE_AIE  0x4000U      // Abnormal Interrupt Summary
                                               // Enable
#define ETHERNET_DMA_CH1_INTERRUPT_ENABLE_NIE  0x8000U      // Normal Interrupt Summary
                                               // Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the DMA_CH1_RX_INTERRUPT_WATCHDOG_TIMER register
//
//*****************************************************************************
#define ETHERNET_DMA_CH1_RX_INTERRUPT_WATCHDOG_TIMER_RWT_S  0U
#define ETHERNET_DMA_CH1_RX_INTERRUPT_WATCHDOG_TIMER_RWT_M  0xFFU        // Receive Interrupt Watchdog
                                               // Timer Count
#define ETHERNET_DMA_CH1_RX_INTERRUPT_WATCHDOG_TIMER_RWTU_S  16U
#define ETHERNET_DMA_CH1_RX_INTERRUPT_WATCHDOG_TIMER_RWTU_M  0x30000U     // Receive Interrupt Watchdog
                                               // Timer Count Units

//*****************************************************************************
//
// The following are defines for the bit fields in the DMA_CH1_STATUS register
//
//*****************************************************************************
#define ETHERNET_DMA_CH1_STATUS_TI    0x1U         // Transmit Interrupt
#define ETHERNET_DMA_CH1_STATUS_TPS   0x2U         // Transmit Process Stopped
#define ETHERNET_DMA_CH1_STATUS_TBU   0x4U         // Transmit Buffer Unavailable
#define ETHERNET_DMA_CH1_STATUS_RI    0x40U        // Receive Interrupt
#define ETHERNET_DMA_CH1_STATUS_RBU   0x80U        // Receive Buffer Unavailable
#define ETHERNET_DMA_CH1_STATUS_RPS   0x100U       // Receive Process Stopped
#define ETHERNET_DMA_CH1_STATUS_RWT   0x200U       // Receive Watchdog Timeout
#define ETHERNET_DMA_CH1_STATUS_ETI   0x400U       // Early Transmit Interrupt
#define ETHERNET_DMA_CH1_STATUS_ERI   0x800U       // Early Receive Interrupt
#define ETHERNET_DMA_CH1_STATUS_FBE   0x1000U      // Fatal Bus Error
#define ETHERNET_DMA_CH1_STATUS_CDE   0x2000U      // Context Descriptor Error
#define ETHERNET_DMA_CH1_STATUS_AIS   0x4000U      // Abnormal Interrupt Summary
#define ETHERNET_DMA_CH1_STATUS_NIS   0x8000U      // Normal Interrupt Summary
#define ETHERNET_DMA_CH1_STATUS_TEB_S  16U
#define ETHERNET_DMA_CH1_STATUS_TEB_M  0x70000U     // Tx DMA Error Bits
#define ETHERNET_DMA_CH1_STATUS_REB_S  19U
#define ETHERNET_DMA_CH1_STATUS_REB_M  0x380000U    // Rx DMA Error Bits

//*****************************************************************************
//
// The following are defines for the bit fields in the DMA_CH1_MISS_FRAME_CNT register
//
//*****************************************************************************
#define ETHERNET_DMA_CH1_MISS_FRAME_CNT_MFC_S  0U
#define ETHERNET_DMA_CH1_MISS_FRAME_CNT_MFC_M  0x7FFU       // Dropped Packet Counters
#define ETHERNET_DMA_CH1_MISS_FRAME_CNT_MFCO  0x8000U      // Overflow status of the MFC
                                               // Counter

//*****************************************************************************
//
// The following are defines for the bit fields in the MTL_OPERATION_MODE register
//
//*****************************************************************************
#define ETHERNET_MTL_OPERATION_MODE_DTXSTS  0x2U         // Drop Transmit Status
#define ETHERNET_MTL_OPERATION_MODE_RAA  0x4U         // Receive Arbitration Algorithm
#define ETHERNET_MTL_OPERATION_MODE_SCHALG_S  5U
#define ETHERNET_MTL_OPERATION_MODE_SCHALG_M  0x60U        // Tx Scheduling Algorithm
#define ETHERNET_MTL_OPERATION_MODE_CNTPRST  0x100U       // Counters Preset
#define ETHERNET_MTL_OPERATION_MODE_CNTCLR  0x200U       // Counters Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the MTL_DBG_CTL register
//
//*****************************************************************************
#define ETHERNET_MTL_DBG_CTL_FDBGEN   0x1U         // FIFO Debug Access Enable
#define ETHERNET_MTL_DBG_CTL_DBGMOD   0x2U         // Debug Mode Access to FIFO
#define ETHERNET_MTL_DBG_CTL_BYTEEN_S  2U
#define ETHERNET_MTL_DBG_CTL_BYTEEN_M  0xCU         // Byte Enables
#define ETHERNET_MTL_DBG_CTL_PKTSTATE_S  5U
#define ETHERNET_MTL_DBG_CTL_PKTSTATE_M  0x60U        // Encoded Packet State
#define ETHERNET_MTL_DBG_CTL_RSTALL   0x100U       // Reset All Pointers
#define ETHERNET_MTL_DBG_CTL_RSTSEL   0x200U       // Reset Pointers of Selected
                                               // FIFO
#define ETHERNET_MTL_DBG_CTL_FIFORDEN  0x400U       // FIFO Read Enable
#define ETHERNET_MTL_DBG_CTL_FIFOWREN  0x800U       // FIFO Write Enable
#define ETHERNET_MTL_DBG_CTL_FIFOSEL_S  12U
#define ETHERNET_MTL_DBG_CTL_FIFOSEL_M  0x3000U      // FIFO Selected for Access
#define ETHERNET_MTL_DBG_CTL_PKTIE    0x4000U      // Receive Packet Available
                                               // Interrupt Status Enable
#define ETHERNET_MTL_DBG_CTL_STSIE    0x8000U      // Transmit Status Available
                                               // Interrupt Status Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the MTL_DBG_STS register
//
//*****************************************************************************
#define ETHERNET_MTL_DBG_STS_FIFOBUSY  0x1U         // FIFO Busy
#define ETHERNET_MTL_DBG_STS_PKTSTATE_S  1U
#define ETHERNET_MTL_DBG_STS_PKTSTATE_M  0x6U         // Encoded Packet State
#define ETHERNET_MTL_DBG_STS_BYTEEN_S  3U
#define ETHERNET_MTL_DBG_STS_BYTEEN_M  0x18U        // Byte Enables
#define ETHERNET_MTL_DBG_STS_PKTI     0x100U       // Receive Packet Available
                                               // Interrupt Status
#define ETHERNET_MTL_DBG_STS_STSI     0x200U       // Transmit Status Available
                                               // Interrupt Status
#define ETHERNET_MTL_DBG_STS_LOCR_S   15U
#define ETHERNET_MTL_DBG_STS_LOCR_M   0xFFFF8000U  // Remaining Locations in the
                                               // FIFO

//*****************************************************************************
//
// The following are defines for the bit fields in the MTL_INTERRUPT_STATUS register
//
//*****************************************************************************
#define ETHERNET_MTL_INTERRUPT_STATUS_Q0IS  0x1U         // Queue 0 Interrupt status
#define ETHERNET_MTL_INTERRUPT_STATUS_Q1IS  0x2U         // Queue 1 Interrupt status
#define ETHERNET_MTL_INTERRUPT_STATUS_DBGIS  0x20000U     // Debug Interrupt status

//*****************************************************************************
//
// The following are defines for the bit fields in the MTL_RXQ_DMA_MAP0 register
//
//*****************************************************************************
#define ETHERNET_MTL_RXQ_DMA_MAP0_Q0MDMACH  0x1U         // Queue 0 Mapped to DMA Channel
#define ETHERNET_MTL_RXQ_DMA_MAP0_Q0DDMACH  0x10U        // Queue 0 Enabled for DA-based
                                               // DMA Channel Selection
#define ETHERNET_MTL_RXQ_DMA_MAP0_Q1MDMACH  0x100U       // Queue 1 Mapped to DMA Channel
#define ETHERNET_MTL_RXQ_DMA_MAP0_Q1DDMACH  0x1000U      // Queue 1 Enabled for DA-based
                                               // DMA Channel Selection

//*****************************************************************************
//
// The following are defines for the bit fields in the MTL_TXQ0_OPERATION_MODE register
//
//*****************************************************************************
#define ETHERNET_MTL_TXQ0_OPERATION_MODE_FTQ  0x1U         // Flush Transmit Queue
#define ETHERNET_MTL_TXQ0_OPERATION_MODE_TSF  0x2U         // Transmit Store and Forward
#define ETHERNET_MTL_TXQ0_OPERATION_MODE_TXQEN_S  2U
#define ETHERNET_MTL_TXQ0_OPERATION_MODE_TXQEN_M  0xCU         // Transmit Queue Enable
#define ETHERNET_MTL_TXQ0_OPERATION_MODE_TTC_S  4U
#define ETHERNET_MTL_TXQ0_OPERATION_MODE_TTC_M  0x70U        // Transmit Threshold Control
#define ETHERNET_MTL_TXQ0_OPERATION_MODE_TQS_S  16U
#define ETHERNET_MTL_TXQ0_OPERATION_MODE_TQS_M  0xF0000U     // Transmit Queue Size

//*****************************************************************************
//
// The following are defines for the bit fields in the MTL_TXQ0_UNDERFLOW register
//
//*****************************************************************************
#define ETHERNET_MTL_TXQ0_UNDERFLOW_UFFRMCNT_S  0U
#define ETHERNET_MTL_TXQ0_UNDERFLOW_UFFRMCNT_M  0x7FFU       // Underflow Packet Counter
#define ETHERNET_MTL_TXQ0_UNDERFLOW_UFCNTOVF  0x800U       // Overflow Bit for Underflow
                                               // Packet Counter

//*****************************************************************************
//
// The following are defines for the bit fields in the MTL_TXQ0_DEBUG register
//
//*****************************************************************************
#define ETHERNET_MTL_TXQ0_DEBUG_TXQPAUSED  0x1U         // Transmit Queue in Pause
#define ETHERNET_MTL_TXQ0_DEBUG_TRCSTS_S  1U
#define ETHERNET_MTL_TXQ0_DEBUG_TRCSTS_M  0x6U         // MTL Tx Queue Read Controller
                                               // Status
#define ETHERNET_MTL_TXQ0_DEBUG_TWCSTS  0x8U         // MTL Tx Queue Write Controller
                                               // Status
#define ETHERNET_MTL_TXQ0_DEBUG_TXQSTS  0x10U        // MTL Tx Queue Not Empty Status
#define ETHERNET_MTL_TXQ0_DEBUG_TXSTSFSTS  0x20U        // MTL Tx Status FIFO Full
                                               // Status
#define ETHERNET_MTL_TXQ0_DEBUG_PTXQ_S  16U
#define ETHERNET_MTL_TXQ0_DEBUG_PTXQ_M  0x70000U     // Number of Packets in the
                                               // Transmit Queue
#define ETHERNET_MTL_TXQ0_DEBUG_STXSTSF_S  20U
#define ETHERNET_MTL_TXQ0_DEBUG_STXSTSF_M  0x700000U    // Number of Status Words in Tx
                                               // Status FIFO of Queue

//*****************************************************************************
//
// The following are defines for the bit fields in the MTL_TXQ0_ETS_STATUS register
//
//*****************************************************************************
#define ETHERNET_MTL_TXQ0_ETS_STATUS_ABS_S  0U
#define ETHERNET_MTL_TXQ0_ETS_STATUS_ABS_M  0xFFFFFFU    // Average Bits per Slot

//*****************************************************************************
//
// The following are defines for the bit fields in the MTL_TXQ0_QUANTUM_WEIGHT register
//
//*****************************************************************************
#define ETHERNET_MTL_TXQ0_QUANTUM_WEIGHT_ISCQW_S  0U
#define ETHERNET_MTL_TXQ0_QUANTUM_WEIGHT_ISCQW_M  0x1FFFFFU    // Quantum or Weights

//*****************************************************************************
//
// The following are defines for the bit fields in the MTL_Q0_INTERRUPT_CONTROL_STATUS register
//
//*****************************************************************************
#define ETHERNET_MTL_Q0_INTERRUPT_CONTROL_STATUS_TXUNFIS  0x1U         // Transmit Queue Underflow
                                               // Interrupt Status
#define ETHERNET_MTL_Q0_INTERRUPT_CONTROL_STATUS_ABPSIS  0x2U         // Average Bits Per Slot
                                               // Interrupt Status
#define ETHERNET_MTL_Q0_INTERRUPT_CONTROL_STATUS_TXUIE  0x100U       // Transmit Queue Underflow
                                               // Interrupt Enable
#define ETHERNET_MTL_Q0_INTERRUPT_CONTROL_STATUS_ABPSIE  0x200U       // Average Bits Per Slot
                                               // Interrupt Enable
#define ETHERNET_MTL_Q0_INTERRUPT_CONTROL_STATUS_RXOVFIS  0x10000U     // Receive Queue Overflow
                                               // Interrupt Status
#define ETHERNET_MTL_Q0_INTERRUPT_CONTROL_STATUS_RXOIE  0x1000000U   // Receive Queue Overflow
                                               // Interrupt Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the MTL_RXQ0_OPERATION_MODE register
//
//*****************************************************************************
#define ETHERNET_MTL_RXQ0_OPERATION_MODE_RTC_S  0U
#define ETHERNET_MTL_RXQ0_OPERATION_MODE_RTC_M  0x3U         // Receive Queue Threshold
                                               // Control
#define ETHERNET_MTL_RXQ0_OPERATION_MODE_FUP  0x8U         // Forward Undersized Good
                                               // Packets
#define ETHERNET_MTL_RXQ0_OPERATION_MODE_FEP  0x10U        // Forward Error Packets
#define ETHERNET_MTL_RXQ0_OPERATION_MODE_RSF  0x20U        // Receive Queue Store and
                                               // Forward
#define ETHERNET_MTL_RXQ0_OPERATION_MODE_DIS_TCP_EF  0x40U        // Disable Dropping of TCP/IP
                                               // Checksum Error Packets
#define ETHERNET_MTL_RXQ0_OPERATION_MODE_EHFC  0x80U        // Enable Hardware Flow Control
#define ETHERNET_MTL_RXQ0_OPERATION_MODE_RFA_S  8U
#define ETHERNET_MTL_RXQ0_OPERATION_MODE_RFA_M  0x700U       // Threshold for Activating Flow
                                               // Control (in half-duplex and
                                               // full-duplex
#define ETHERNET_MTL_RXQ0_OPERATION_MODE_RFD_S  14U
#define ETHERNET_MTL_RXQ0_OPERATION_MODE_RFD_M  0x1C000U     // Threshold for Deactivating
                                               // Flow Control (in half-duplex and
                                               // full-duplex modes)
#define ETHERNET_MTL_RXQ0_OPERATION_MODE_RQS_S  20U
#define ETHERNET_MTL_RXQ0_OPERATION_MODE_RQS_M  0xF00000U    // Receive Queue Size

//*****************************************************************************
//
// The following are defines for the bit fields in the MTL_RXQ0_MISSED_PACKET_OVERFLOW_CNT register
//
//*****************************************************************************
#define ETHERNET_MTL_RXQ0_MISSED_PACKET_OVERFLOW_CNT_OVFPKTCNT_S  0U
#define ETHERNET_MTL_RXQ0_MISSED_PACKET_OVERFLOW_CNT_OVFPKTCNT_M  0x7FFU       // Overflow Packet Counter
#define ETHERNET_MTL_RXQ0_MISSED_PACKET_OVERFLOW_CNT_OVFCNTOVF  0x800U       // Overflow Counter Overflow Bit
#define ETHERNET_MTL_RXQ0_MISSED_PACKET_OVERFLOW_CNT_MISPKTCNT_S  16U
#define ETHERNET_MTL_RXQ0_MISSED_PACKET_OVERFLOW_CNT_MISPKTCNT_M  0x7FF0000U   // Missed Packet Counter
#define ETHERNET_MTL_RXQ0_MISSED_PACKET_OVERFLOW_CNT_MISCNTOVF  0x8000000U   // Missed Packet Counter
                                               // Overflow Bit

//*****************************************************************************
//
// The following are defines for the bit fields in the MTL_RXQ0_DEBUG register
//
//*****************************************************************************
#define ETHERNET_MTL_RXQ0_DEBUG_RWCSTS  0x1U         // MTL Rx Queue Write Controller
                                               // Active Status
#define ETHERNET_MTL_RXQ0_DEBUG_RRCSTS_S  1U
#define ETHERNET_MTL_RXQ0_DEBUG_RRCSTS_M  0x6U         // MTL Rx Queue Read Controller
                                               // State
#define ETHERNET_MTL_RXQ0_DEBUG_RXQSTS_S  4U
#define ETHERNET_MTL_RXQ0_DEBUG_RXQSTS_M  0x30U        // MTL Rx Queue Fill-Level
                                               // Status
#define ETHERNET_MTL_RXQ0_DEBUG_PRXQ_S  16U
#define ETHERNET_MTL_RXQ0_DEBUG_PRXQ_M  0x3FFF0000U  // Number of Packets in Receive
                                               // Queue

//*****************************************************************************
//
// The following are defines for the bit fields in the MTL_RXQ0_CONTROL register
//
//*****************************************************************************
#define ETHERNET_MTL_RXQ0_CONTROL_RXQ_WEGT_S  0U
#define ETHERNET_MTL_RXQ0_CONTROL_RXQ_WEGT_M  0x7U         // Receive Queue Weight
#define ETHERNET_MTL_RXQ0_CONTROL_RXQ_FRM_ARBIT  0x8U         // Receive Queue Packet
                                               // Arbitration

//*****************************************************************************
//
// The following are defines for the bit fields in the MTL_TXQ1_OPERATION_MODE register
//
//*****************************************************************************
#define ETHERNET_MTL_TXQ1_OPERATION_MODE_FTQ  0x1U         // Flush Transmit Queue
#define ETHERNET_MTL_TXQ1_OPERATION_MODE_TSF  0x2U         // Transmit Store and Forward
#define ETHERNET_MTL_TXQ1_OPERATION_MODE_TXQEN_S  2U
#define ETHERNET_MTL_TXQ1_OPERATION_MODE_TXQEN_M  0xCU         // Transmit Queue Enable
#define ETHERNET_MTL_TXQ1_OPERATION_MODE_TTC_S  4U
#define ETHERNET_MTL_TXQ1_OPERATION_MODE_TTC_M  0x70U        // Transmit Threshold Control
#define ETHERNET_MTL_TXQ1_OPERATION_MODE_TQS_S  16U
#define ETHERNET_MTL_TXQ1_OPERATION_MODE_TQS_M  0xF0000U     // Transmit Queue Size

//*****************************************************************************
//
// The following are defines for the bit fields in the MTL_TXQ1_UNDERFLOW register
//
//*****************************************************************************
#define ETHERNET_MTL_TXQ1_UNDERFLOW_UFFRMCNT_S  0U
#define ETHERNET_MTL_TXQ1_UNDERFLOW_UFFRMCNT_M  0x7FFU       // Underflow Packet Counter
#define ETHERNET_MTL_TXQ1_UNDERFLOW_UFCNTOVF  0x800U       // Overflow Bit for Underflow
                                               // Packet Counter

//*****************************************************************************
//
// The following are defines for the bit fields in the MTL_TXQ1_DEBUG register
//
//*****************************************************************************
#define ETHERNET_MTL_TXQ1_DEBUG_TXQPAUSED  0x1U         // Transmit Queue in Pause
#define ETHERNET_MTL_TXQ1_DEBUG_TRCSTS_S  1U
#define ETHERNET_MTL_TXQ1_DEBUG_TRCSTS_M  0x6U         // MTL Tx Queue Read Controller
                                               // Status
#define ETHERNET_MTL_TXQ1_DEBUG_TWCSTS  0x8U         // MTL Tx Queue Write Controller
                                               // Status
#define ETHERNET_MTL_TXQ1_DEBUG_TXQSTS  0x10U        // MTL Tx Queue Not Empty Status
#define ETHERNET_MTL_TXQ1_DEBUG_TXSTSFSTS  0x20U        // MTL Tx Status FIFO Full
                                               // Status
#define ETHERNET_MTL_TXQ1_DEBUG_PTXQ_S  16U
#define ETHERNET_MTL_TXQ1_DEBUG_PTXQ_M  0x70000U     // Number of Packets in the
                                               // Transmit Queue
#define ETHERNET_MTL_TXQ1_DEBUG_STXSTSF_S  20U
#define ETHERNET_MTL_TXQ1_DEBUG_STXSTSF_M  0x700000U    // Number of Status Words in Tx
                                               // Status FIFO of Queue

//*****************************************************************************
//
// The following are defines for the bit fields in the MTL_TXQ1_ETS_STATUS register
//
//*****************************************************************************
#define ETHERNET_MTL_TXQ1_ETS_STATUS_ABS_S  0U
#define ETHERNET_MTL_TXQ1_ETS_STATUS_ABS_M  0xFFFFFFU    // Average Bits per Slot

//*****************************************************************************
//
// The following are defines for the bit fields in the MTL_TXQ1_QUANTUM_WEIGHT register
//
//*****************************************************************************
#define ETHERNET_MTL_TXQ1_QUANTUM_WEIGHT_ISCQW_S  0U
#define ETHERNET_MTL_TXQ1_QUANTUM_WEIGHT_ISCQW_M  0x1FFFFFU    // idleSlopeCredit, Quantum or
                                               // Weights

//*****************************************************************************
//
// The following are defines for the bit fields in the MTL_Q1_INTERRUPT_CONTROL_STATUS register
//
//*****************************************************************************
#define ETHERNET_MTL_Q1_INTERRUPT_CONTROL_STATUS_TXUNFIS  0x1U         // Transmit Queue Underflow
                                               // Interrupt Status
#define ETHERNET_MTL_Q1_INTERRUPT_CONTROL_STATUS_ABPSIS  0x2U         // Average Bits Per Slot
                                               // Interrupt Status
#define ETHERNET_MTL_Q1_INTERRUPT_CONTROL_STATUS_TXUIE  0x100U       // Transmit Queue Underflow
                                               // Interrupt Enable
#define ETHERNET_MTL_Q1_INTERRUPT_CONTROL_STATUS_ABPSIE  0x200U       // Average Bits Per Slot
                                               // Interrupt Enable
#define ETHERNET_MTL_Q1_INTERRUPT_CONTROL_STATUS_RXOVFIS  0x10000U     // Receive Queue Overflow
                                               // Interrupt Status
#define ETHERNET_MTL_Q1_INTERRUPT_CONTROL_STATUS_RXOIE  0x1000000U   // Receive Queue Overflow
                                               // Interrupt Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the MTL_RXQ1_OPERATION_MODE register
//
//*****************************************************************************
#define ETHERNET_MTL_RXQ1_OPERATION_MODE_RTC_S  0U
#define ETHERNET_MTL_RXQ1_OPERATION_MODE_RTC_M  0x3U         // Receive Queue Threshold
                                               // Control
#define ETHERNET_MTL_RXQ1_OPERATION_MODE_FUP  0x8U         // Forward Undersized Good
                                               // Packets
#define ETHERNET_MTL_RXQ1_OPERATION_MODE_FEP  0x10U        // Forward Error Packets
#define ETHERNET_MTL_RXQ1_OPERATION_MODE_RSF  0x20U        // Receive Queue Store and
                                               // Forward
#define ETHERNET_MTL_RXQ1_OPERATION_MODE_DIS_TCP_EF  0x40U        // Disable Dropping of TCP/IP
                                               // Checksum Error Packets
#define ETHERNET_MTL_RXQ1_OPERATION_MODE_EHFC  0x80U        // Enable Hardware Flow Control
#define ETHERNET_MTL_RXQ1_OPERATION_MODE_RFA_S  8U
#define ETHERNET_MTL_RXQ1_OPERATION_MODE_RFA_M  0x700U       // Threshold for Activating Flow
                                               // Control (in half-duplex and
                                               // full-duplex
#define ETHERNET_MTL_RXQ1_OPERATION_MODE_RFD_S  14U
#define ETHERNET_MTL_RXQ1_OPERATION_MODE_RFD_M  0x1C000U     // Threshold for Deactivating
                                               // Flow Control (in half-duplex and
                                               // full-duplex modes)
#define ETHERNET_MTL_RXQ1_OPERATION_MODE_RQS_S  20U
#define ETHERNET_MTL_RXQ1_OPERATION_MODE_RQS_M  0xF00000U    // Receive Queue Size

//*****************************************************************************
//
// The following are defines for the bit fields in the MTL_RXQ1_MISSED_PACKET_OVERFLOW_CNT register
//
//*****************************************************************************
#define ETHERNET_MTL_RXQ1_MISSED_PACKET_OVERFLOW_CNT_OVFPKTCNT_S  0U
#define ETHERNET_MTL_RXQ1_MISSED_PACKET_OVERFLOW_CNT_OVFPKTCNT_M  0x7FFU       // Overflow Packet Counter
#define ETHERNET_MTL_RXQ1_MISSED_PACKET_OVERFLOW_CNT_OVFCNTOVF  0x800U       // Overflow Counter Overflow Bit
#define ETHERNET_MTL_RXQ1_MISSED_PACKET_OVERFLOW_CNT_MISPKTCNT_S  16U
#define ETHERNET_MTL_RXQ1_MISSED_PACKET_OVERFLOW_CNT_MISPKTCNT_M  0x7FF0000U   // Missed Packet Counter
#define ETHERNET_MTL_RXQ1_MISSED_PACKET_OVERFLOW_CNT_MISCNTOVF  0x8000000U   // Missed Packet Counter
                                               // Overflow Bit

//*****************************************************************************
//
// The following are defines for the bit fields in the MTL_RXQ1_DEBUG register
//
//*****************************************************************************
#define ETHERNET_MTL_RXQ1_DEBUG_RWCSTS  0x1U         // MTL Rx Queue Write Controller
                                               // Active Status
#define ETHERNET_MTL_RXQ1_DEBUG_RRCSTS_S  1U
#define ETHERNET_MTL_RXQ1_DEBUG_RRCSTS_M  0x6U         // MTL Rx Queue Read Controller
                                               // State
#define ETHERNET_MTL_RXQ1_DEBUG_RXQSTS_S  4U
#define ETHERNET_MTL_RXQ1_DEBUG_RXQSTS_M  0x30U        // MTL Rx Queue Fill-Level
                                               // Status
#define ETHERNET_MTL_RXQ1_DEBUG_PRXQ_S  16U
#define ETHERNET_MTL_RXQ1_DEBUG_PRXQ_M  0x3FFF0000U  // Number of Packets in Receive
                                               // Queue

//*****************************************************************************
//
// The following are defines for the bit fields in the MTL_RXQ1_CONTROL register
//
//*****************************************************************************
#define ETHERNET_MTL_RXQ1_CONTROL_RXQ_WEGT_S  0U
#define ETHERNET_MTL_RXQ1_CONTROL_RXQ_WEGT_M  0x7U         // Receive Queue Weight
#define ETHERNET_MTL_RXQ1_CONTROL_RXQ_FRM_ARBIT  0x8U         // Receive Queue Packet
                                               // Arbitration
#endif
