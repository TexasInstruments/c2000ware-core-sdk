//###########################################################################
//
// FILE:   ethernet.c
// TITLE:  CM Subsystem Ethernet driver
//
//  Version History Details:
//      24- Mar- 17: Initial Version
//      9 - Jun- 17: 1588(PTP) Support Added
//      1- Aug-17  : Multichannel, Multibuffer, Threshold mode
//                   MDIO Support Added,Other Bug Fixes
//      20-Sep-2017   : VLAN Support Added
//                     MDIO BugFixes,SA insertion and
//                     CRC Pad configurability in TX
//      11- Oct-2017 Added Support for Programming Watchdog,RevMII
//      21- Nov- 2017 Early Tx and Rx buffer Handling, L3, L4 Filter support
//                    More doxygen comments and code cleanup,Fixes
//      9-Mar-2018 : TSO Support, MISRA-C related updates
//                   Few Bug fixes, Energy Efficient Ethernet support addition
//      2-May-2018 : Added support for - PTP Offload, PTP One-step Timestamping,
//                   PTP Higher Word Register and PTP Egress/Ingress Correction.
//      19-Apr-2019 : Changes for VLAN CBTI, Context descriptor, Flow control
//                    cleanups for removing SoC specific content
//      22-Apr-2020 : MAC Filter Configuration added in _getHandle API
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

#include "ethernet.h"
#include "sysctl.h"
#include "inc/hw_types.h"
#include <string.h>
//
//Change this define for Changing No of packets used by this driver
//
#define ETHERNET_NO_OF_RX_PACKETS   2U
//
//Change this define for changing Packet buffer length
//
#define ETHERNET_MAX_PACKET_LENGTH 1538U
#define ETHERNET_DMA_BURST_LENGTH   4U
#define ETHERNET_DEBUG  1U

#ifdef ETHERNET_DEBUG
//
//These variables are for debug purpose
//Number of Time the Tx Packet Free Callback was called
//
uint32_t Ethernet_numTxPktFreeCallback = 0U;
//
//Number of Times Rx Callback while handling RX packets
//
uint32_t Ethernet_numRxCallback = 0U;
//
//Number of time Get packet buffer callback was called
//
uint32_t Ethernet_numGetPacketBufferCallback = 0U ;
//
//Number of times Tx Completion ISR was called
//
uint32_t Ethernet_txInterruptCount = 0U;
//
//Number of times Rx Completion ISR was called
//
uint32_t Ethernet_rxInterruptCount = 0U;
//
//Number of Receive Context Descriptors received
//
uint32_t Ethernet_rxContextTimeStamp = 0U;
//
//Number of times Misc Interrupt ISR was called
//
uint32_t Ethernet_genericInterruptCount = 0U;
//
//Number of times Early Rx interrupt is received
//
uint32_t Ethernet_earlyRxInterruptCount = 0U ;
//
//Number of times Early Tx interrupt is received
//
uint32_t Ethernet_earlyTxInterruptCount = 0U;
//
//Number of times RX Generic interrupt is received for completion
//
uint32_t Ethernet_genericRxCompletionInterruptCount = 0U ;
//
//Number of PHY Status change interrupt from RevMII block
//
uint32_t Ethernet_phyLinkStatusChangeInterruptCount = 0U;
//
//Number of times application did not give replacement Rx buffer
//
uint32_t Ethernet_rxReplacementFailedCount = 0;

//
//Number of EEE Tx LPI count
//
uint32_t Ethernet_eeeTxLPIEntryCount = 0;
//
//Number of EEE Tx LPI count
//
uint32_t Ethernet_eeeTxLPIExitCount = 0;
//
//Number of EEE Rx LPI Count
//
uint32_t Ethernet_eeeRxLPIEntryCount = 0;
//
//Number of EEE Tx LPI count
//
uint32_t Ethernet_eeeRxLPIExitCount = 0;
uint32_t Ethernet_pmtInterruptCount = 0;
uint32_t Ethernet_magicPktReceivedCount = 0;
uint32_t Ethernet_rwakeupPktReceivedCount = 0;

uint32_t Ethernet_txChan0BufUnavail = 0;
uint32_t Ethernet_rxChan0BufUnavail = 0;
uint32_t Ethernet_txChan1BufUnavail = 0;
uint32_t Ethernet_rxChan1BufUnavail = 0;
#endif
//
//Global Book keeping structure of the EMAC driver
//
Ethernet_Device     Ethernet_device_struct;
//
//Packet descriptor that we will use for sending the packet to driver
//
Ethernet_Pkt_Desc   Ethernet_pktDescriptorRX;
Ethernet_HW_descriptor Ethernet_descArray[ETHERNET_DESCRIPTORS_NUM];

//
// Helper functions Declarations
//

//
//These are helper functions called by the Low Level Driver
//while implementing the APIs described above
//
//*************************************************************************
//! Ethernet_addPacketsIntoTxQueue()
//!
//! \param
//! channelDescPtr - Pointer to the Channel Descriptor  Structure
//! to which the Packets should be Enqueued
//! Description:
//! There are two Queues maintained in the driver for each channel
//! 1. Wait Queue where the packets are queued up for software
//! 2. The Desc Queue is one from where it is submitted to Hardware
//! If the DMA Engine can service packets it picks up the packets from
//! Desc Queue
//! This API scans through the Wait Queue and submits to Desc Queue for
//! hardware processing of the Tx Packets. This function prepares the Transmit
//! descriptors for the Ethernet DMA Engine
//! \return none
//************************************************************************

void Ethernet_addPacketsIntoTxQueue(Ethernet_DescCh *channelDescPtr);
//*************************************************************************
//! Ethernet_removePacketsFromTxQueue()
//!
//! \param
//! channelDescPtr - Pointer to the Channel Descriptor  Structure
//! from which the Packet has to be Dequeued
//! Description:
//! This function is called from the Transmit completion ISR to
//! remove a packet from Desc Queue and call the Callback function registered
//! by the higher layer to signal the Transmit Completion
//! After calling the callback if there are packets pending in WaitQueue to be
//! transmitted this routine submits them to the DescQueue and prepare
//!
//! \return none
//************************************************************************

void Ethernet_removePacketsFromTxQueue(Ethernet_DescCh *channelDescPtr,
                                       Ethernet_CompletionMode completionMode);


//***********************************************************************
//! Ethernet_addPacketsIntoRxQueue
//!
//! \param:
//! channelDescPtr - Pointer to Channel Descriptor Structure
//! to which the Receive buffer has to be enqueued
//! This function calls the higher layer callback function to get the buffers
//! for receive from application and queues them up in Desc Queue
//! For the Receive channels the Wait queue is not used only the Desc Queue
//! is used by the driver
//! \return none
//***********************************************************************


void Ethernet_addPacketsIntoRxQueue(Ethernet_DescCh *channelDescPtr);

//**********************************************************************
//! Ethernet_removePacketsFromRxQueue()
//!
//! \param
//! channelDescPtr - Receive channel Desctiptor Pointer from which the
//! Packet has to be Defines
//! completionMode
//!
//! This function is called from the Receive Completion Interrupt Handler
//! This fills the PacketDescriptor Structure for handing over the packet
//! And fills with the received packet details
//! Calls the Receive Packet Callback function provided by higher layer
//! \return None
//**********************************************************************
void Ethernet_removePacketsFromRxQueue(Ethernet_DescCh *channelDescPtr,
                            Ethernet_CompletionMode completionMode);


//*************************************************************************
//!
//! Ethernet_performPushPacketQueueChain()
//!
//!\param
//! pktQueuePtr - Queue to which the packets has to be pushed
//! firstPktHdrPtr - Pointer to first packet
//! lastPktHdrPtr - Pointer to the last packet
//! Count - no of Packets to be pushed to Queue
//!
//! This function is used by the Ethernet_sendPacket() API to push a chain of
//! Packets to the Queue
//!
//! \return none
//! ************************************************************************
static void Ethernet_performPushPacketQueueChain(
        Ethernet_PKT_Queue_T *pktQueuePtr,
        Ethernet_Pkt_Desc *firstPktHdrPtr,
        Ethernet_Pkt_Desc *lastPktHdrPtr,
        uint32_t count);
//**************************************************************************
//! Ethernet_performPopOnPacketQueue()
//!
//! \param
//! pktQueuePtr - Pointer to the Packet Queue
//!
//! This function Dequeues a packet from Queue. This function is called in both
//! Tx and Rx Paths. This function returns the element at the head of Queue
//! \return Pointer to the packet that is popped
//***************************************************************************
static Ethernet_Pkt_Desc *Ethernet_performPopOnPacketQueue(
                    Ethernet_PKT_Queue_T *pktQueuePtr);


/** ==========================================================================
 *  @n@b Ethernet_returnTopOfPacketQueue()
 *
 *  @b Description
 *  @n Return Front element of a queue
 *
 *  @b Arguments
 *  @verbatim
        pktQueuePtr      pointer to packet queue
    @endverbatim
 *
 *  <b> Return Value </b>  Pointer to EMAC packet
 *
 *  <b> Pre Condition </b>
 *  @n  None
 *
 *  <b> Post Condition </b>
 *  @n  None
 *
 *  @b Example
 *  @verbatim
        ETHERNET_PKT_QUEUE_T *pktQueuePtr;
        ETHERNET_returnTopOfPacketQueue( pktQueuePtr );
    @endverbatim
 * ============================================================================
 */
static Ethernet_Pkt_Desc *Ethernet_returnTopOfPacketQueue(
            Ethernet_PKT_Queue_T *pktQueuePtr);
//***************************************************************************
//! Ethernet_performPushOnPacketQueue ()
//!
//! This function does a Enqueue on Packet Queue
//! It does an enqueue which adds a packet to the Rear of the queue
//! This is called in both Tx and Rx Paths
//! \return None
//***************************************************************************
static void Ethernet_performPushOnPacketQueue(Ethernet_PKT_Queue_T *pq,
        Ethernet_Pkt_Desc *pPktHdr);

//**************************************************************************
//!    Ethernet_resetModule()
//!
//! \param
//! baseAddress - Base Address of Ethernet module in the device
//!
//! This function does a Soft Reset of the Ethernet core & waits till the soft
//! Reset is complete
//! \return None
//***************************************************************************
void Ethernet_resetModule(uint32_t baseAddress);


void Ethernet_enableMACInterrupt(
                                uint32_t base,
                                uint32_t flags);
//**************************************************************************
//! Ethernet_setMTLTxQueueOpMode
//!
//! This helper function is used to program the MTL_OPERATION_MODE
//! register
//! \param
//! baseAddress - baseAddress of the Ethernet module
//! txSchedulingAlgoritm - Tx Scheduling Algorithm
//!     ETHERNET_MTL_OPERATON_MODE_SCHALG_WRR
//!     ETHERNET_MTL_OPERATON_MODE_SCHALG_WFQ
//!     ETHERNET_MTL_OPERATON_MODE_SCHALG_DWRR
//!     ETHERNET_MTL_OPERATON_MODE_SCHALG_STRICT_PRIORITY
//! rxAribtrationAlgorithm: Rx Arbitration Algorithm
//!     ETHERNET_MTL_OPERATION_MODE_RAA_SP
//!     ETHERNET_MTL_OPERATION_MODE_RAA_WSP
//! \return None
//************************************************************************
void Ethernet_setMTLOpmode(uint32_t base,
        uint32_t txSchedulingAlgoritm,
        uint32_t rxAribtrationAlgorithm);
//**************************************************************************
//
// Ethernet_setMTLTxQueueOpMode ()
//
//! This helper function is used to program the MTL_TXQ0_OPERATION_MODE
//! register of the given channel
//! \param
//! baseAddress - baseAddress of the Ethernet module
//! queueNum - Queue Number 0 or 1
//! threshold_val - Threshold Value can be any of the following value
//!     ETHERNET_MTL_TXQ0_OPERATION_MODE_TTC_32
//!     ETHERNET_MTL_TXQ0_OPERATION_MODE_TTC_64
//!     ETHERNET_MTL_TXQ0_OPERATION_MODE_TTC_96
//!     ETHERNET_MTL_TXQ0_OPERATION_MODE_TTC_128
//!     ETHERNET_MTL_TXQ0_OPERATION_MODE_TTC_192
//!     ETHERNET_MTL_TXQ0_OPERATION_MODE_TTC_256
//!     ETHERNET_MTL_TXQ0_OPERATION_MODE_TTC_384
//!     ETHERNET_MTL_TXQ0_OPERATION_MODE_TTC_512
//! queue_size:
//!     Size of the Tx Queue
//!     can be any of the following values
//!     ETHERNET_MTL_Q_OP_MODE_QSIZE_256
//!     ETHERNET_MTL_Q_OP_MODE_QSIZE_512
//!     ETHERNET_MTL_Q_OP_MODE_QSIZE_768
//!     ETHERNET_MTL_Q_OP_MODE_QSIZE_1024
//!     ETHERNET_MTL_Q_OP_MODE_QSIZE_1280
//!     ETHERNET_MTL_Q_OP_MODE_QSIZE_1536
//!     ETHERNET_MTL_Q_OP_MODE_QSIZE_1792
//!     ETHERNET_MTL_Q_OP_MODE_QSIZE_2048
//!     ETHERNET_MTL_Q_OP_MODE_QSIZE_4096
//! storeForward
//!      1 for Store and Forward Mode
//!      0 for Threshold Mode
//! \return none
//
//************************************************************************
void Ethernet_setMTLTxQueueOpMode(uint32_t baseAddress, uint32_t queueNum,
        uint32_t threshold_val, uint32_t queue_size, uint32_t storeForward);

//*************************************************************************
//
//! Ethernet_setMTLRxQueueOpMode
//
//! \param
//! baseAddress - baseAddress of the Ethernet module
//! queueNum - can be 0 or 1
//! threshold_val -
//!    can be any of the following values:
//!     ETHERNET_MTL_Q_OP_MODE_QSIZE_256
//!     ETHERNET_MTL_Q_OP_MODE_QSIZE_512
//!     ETHERNET_MTL_Q_OP_MODE_QSIZE_768
//!     ETHERNET_MTL_Q_OP_MODE_QSIZE_1024
//!     ETHERNET_MTL_Q_OP_MODE_QSIZE_1280
//!     ETHERNET_MTL_Q_OP_MODE_QSIZE_1536
//!     ETHERNET_MTL_Q_OP_MODE_QSIZE_1792
//!     ETHERNET_MTL_Q_OP_MODE_QSIZE_2048
//!     ETHERNET_MTL_Q_OP_MODE_QSIZE_4096
//! QueueSize
//!     can be
//!     ETHERNET_DMA_CHx_RX_CONTROL_RBSZ_1K 1024U
//!     ETHERNET_DMA_CHx_RX_CONTROL_RBSZ_2K 2048U
//! storeForward
//!     1 for Store and Forward moe
//!     0 for Threshold
//! \return None
//
//**************************************************************************

void Ethernet_setMTLRxQueueOpMode(uint32_t baseAddress, uint32_t queueNum,
            uint32_t threshold_val, uint32_t queue_size, uint32_t storeForward);
//*************************************************************************
//
// Ethernet_writeTxDescListAddress
//
//!
//! \param
//! baseAddress: Base Address of Ethernet module
//! channelNum : 0 or 1, the channel number of the register to be configured
//! write_data : pointer to the Descriptor
//! Function to write to DMA_CHx_TXDESC_LIST_ADDRESS register
//! This configures the beginning of the Tx Descriptor ring
//! \return none
//*************************************************************************

void Ethernet_writeTxDescListAddress(uint32_t baseAddress,
            uint32_t channelNum, Ethernet_HW_descriptor *write_data);
//*************************************************************************
//
// Ethernet_writeRxDescListAddress
//
//! \param
//! baseAddress: Base Address of Ethernet module
//! channelNum : 0 or 1, the channel number of the register to be configured
//! write_data : pointer to the Descriptor
//! Function to write to DMA_CHx_RXDESC_LIST_ADDRESS register
//! This configures the beginning of Rx Descriptor Ring
//! \return none
//
//*************************************************************************
void Ethernet_writeRxDescListAddress(uint32_t baseAddress,
        uint32_t channelNum, Ethernet_HW_descriptor *write_data);
//*************************************************************************
//
// Ethernet_writeRxDescTailPointer
//
//! \param
//! baseAddress: Base Address of Ethernet module
//! channelNum : 0 or 1, the channel number of the register to be configured
//! write_data : pointer to the Descriptor
//! Function to write to DMA_CHx_RXDESC_TAIL_POINTER register
//! This configures the beginning of Rx Descriptor Ring
//! \return none
//
//*************************************************************************

void Ethernet_writeRxDescTailPointer(uint32_t baseAddress,
        uint32_t channelNum, Ethernet_HW_descriptor *write_data);
//*************************************************************************
//
// Ethernet_writeTxDMAControl
//
//! \param
//! baseAddress: Base Address of Ethernet module
//! channelNum : 0 or 1, the channel number of the register to be configured
//! burst_Length: Burst Length of the Transfers
//!
//! Function to write to DMA_CHx_TX_CONTROL register
//! This configures the end of Rx Descriptor Ring
//! \return none
//
//*************************************************************************

void Ethernet_writeTxDMAControl(
    uint32_t base,
    uint32_t channelNum,
    uint32_t burst_Length,
    Ethernet_EnableTSO tseEnable,
    uint16_t maximumSegmentSize,
    uint8_t earlyTransmitInterruptEnable);
//*************************************************************************
//
// Ethernet_writeRxDMAControl
//
//! \param
//! baseAddress: Base Address of Ethernet module
//! channelNum : 0 or 1, the channel number of the register to be configured
//! burst_Length: Burst Length of the Transfers
//! dmaBufferSize :
//!         ETHERNET_DMA_CHx_RX_CONTROL_RBSZ_1K
//!         ETHERNET_DMA_CHx_RX_CONTROL_RBSZ_2K
//! Function to write to DMA_CHx_RX_CONTROL register
//!
//! \return none
//
//*************************************************************************

void Ethernet_writeRxDMAControl(
            uint32_t baseAddress,
            uint32_t channelNum,
            uint32_t burst_Length,
            uint32_t dmaBufferSize,
            uint8_t earlyReceiveInterruptEnable);

//*************************************************************************
//
// Ethernet_setTxDescRingLength
//
//! \param
//! baseAddress: Base Address of Ethernet module
//! channelNum : 0 or 1, the channel number of the register to be configured
//! ringLength : Length of Descriptor Ring
//! Function to write to DMA_CH0_TXDESC_RING_LENGTH register
//! This configures the length of Tx Descriptor Ring
//! The function subtracts by 1 before programming
//! \return none
//
//*************************************************************************

void Ethernet_setTxDescRingLength(uint32_t baseAddress, uint32_t channelNum,
            uint32_t ringLength);

//*************************************************************************
//
// Ethernet_setRxDescRingLength
//
//! \param
//! baseAddress: Base Address of Ethernet module
//! channelNum : 0 or 1, the channel number of the register to be configured
//! ringLength : Length of Descriptor Ring
//! Function to write to DMA_CH0_RXDESC_RING_LENGTH register
//! This configures the length of Rx Descriptor Ring
//! The function subtracts by 1 before programming
//! \return none
//
//*************************************************************************

void Ethernet_setRxDescRingLength(uint32_t baseAddress, uint32_t channelNum,
            uint32_t ringLength);

//*************************************************************************
//
// Ethernet_initTxChannel
//
//! \param
//! chInfo : Pointer to the Channel info Structure  for the channel to be init
//! \return none
//! Initializes tehe Tx Channel and makes it ready for transmit
//
//************************************************************************

static uint32_t Ethernet_initTxChannel(Ethernet_ChInfo *chInfo);

//*************************************************************************
//
// Ethernet_enableMACRxQ
//
//! \param
//! base - Base Address
//! QueueNumber - queueNumber to be enabled
//! \return none
//! Initializes the Rx Queue at MAC
//
//************************************************************************

void Ethernet_enableMACRxQ(uint32_t base,
                                            uint32_t queueNumber);



//
//Wrapper Substem Routines
//
void Ethernet_setSSControlStatus(uint32_t base, uint32_t phyTypeSel,
        uint32_t loopbackModeClkSel, uint32_t ClkSourceSelect,
        uint32_t flowControlEnable);

void Ethernet_configureRevMIIAddress(uint32_t subSystembase,
                               uint8_t localPHYAddress,
                               uint8_t remotePHYAddress);

void Ethernet_setFixedInnerVLANParams(uint32_t base,
                                                        uint16_t vlanTag,
                                                        uint8_t vlanTagControl,
                                                        uint8_t vlanType
                                                        );

void Ethernet_setFixedOuterVLANParams(uint32_t base,
                                                        uint16_t vlanTag,
                                                        uint8_t vlanTagControl,
                                                        uint8_t vlanType
                                                        );
void Ethernet_setVLANPerfectFilter(uint32_t base,
                                   uint8_t filterId,
                                   uint16_t vlanId,
                                   uint8_t vlanEnable,
                                   uint8_t vlanFilterMode,
                                   uint8_t vlanTypeComparisonEnable,
                                   uint8_t vlanType,
                                   uint8_t innerVLANEnabled,
                                   uint8_t dmaChannelEnable,
                                   uint8_t channelNum);
void Ethernet_setVLANHashFilter(uint32_t base,
    Ethernet_VlanRxFilter_InnerVLANEnable innerVLANEnabled,
    uint16_t hashMap);
void Ethernet_setDualVLAN(uint32_t base);

void Ethernet_enableInnerVLAN(uint32_t base);
void Ethernet_configureVLANCBTI(uint32_t base,
                                    uint8_t channel,
                                    uint16_t tag,
                                    Ethernet_VlanType vlanType
                                    );
void Ethernet_setVlanTagInclusionFromDescriptor(uint32_t base);

void Ethernet_setInnerVlanTagInclusionFromDescriptor(uint32_t base);

void Ethernet_setMACPacketFilter(uint32_t base,
                                 uint32_t flags);
void Ethernet_setDMAMode(
    uint32_t base,
    Ethernet_DmaMode dmaMode);

void Ethernet_disableDMAChannelTransmit(uint32_t base, uint32_t channelNum);

uint32_t Ethernet_configureL3L4Filter(uint32_t base,
                Ethernet_L3_L4_FilterParams filterParams);

void Ethernet_configureIPv6FilterAddress(uint32_t base,
                     uint8_t filterid,
                    uint32_t word0,
                    uint32_t word1,
                    uint32_t word2,
                    uint32_t word3);

void Ethernet_configureIPv4FilterSourceAddress
                    (uint32_t base,
                      uint8_t filterid,
                      uint32_t address);

void Ethernet_configureIPv4FilterDestinationAddress
            (uint32_t base,
            uint8_t filterid,
            uint32_t address);

void Ethernet_configureLayer4FilterDstAddress(
                        uint32_t base,
                        uint8_t filterid,
                        uint16_t dstAddress);

void Ethernet_configureLayer4FilterSrcAddress(
            uint32_t base,
            uint8_t filterid,
            uint16_t srcAddress);

void Ethernet_configureL3L4FilterControl(
                uint32_t base,
                 uint8_t filterid,
                 uint32_t flags);



//
//EEE Related Functions
//

void Ethernet_configureLPILSTimer(uint32_t base,
                                                        uint16_t lsTimer);

void Ethernet_configureLPITWTimer(uint32_t base,
                                                        uint16_t twTimer);

void Ethernet_configureLPIPhyLinkStatus(uint32_t base,
                                                            bool linkStatus);

void Ethernet_configureEEETicCounter(uint32_t base,
                                                            uint16_t counter);

void Ethernet_configureTxEEEAutomaticMode(uint32_t base);


void Ethernet_enableTxEEEMode(uint32_t base);

void Ethernet_disableTxEEEMode(uint32_t base);

void Ethernet_configureTxLpiEntryTimer(uint32_t base, uint32_t timer);

void Ethernet_enableEEEMagicPacketDetection(uint32_t base);

void Ethernet_configureRemoteWakeupFilter(uint32_t base,
                                                 uint32_t *filterSettings
                                                 );
void Ethernet_configureEEEClockGatingControl(uint32_t base,
                                                 bool enableDisable);
void Ethernet_enableRemoteWakeup(uint32_t base);

//
//External Function Definitions
//

Ethernet_InitConfig * Ethernet_initInterface(
                        Ethernet_InitInterfaceConfig interfaceConfig
                                            )
{
    uint32_t phyMode;
    uint32_t clockSel;
    uint8_t i;
    (void)memset(&Ethernet_device_struct, 0, sizeof(Ethernet_Device));
    Ethernet_device_struct.baseAddresses.ss_base = interfaceConfig.ssbase;
    Ethernet_device_struct.baseAddresses.enet_base = interfaceConfig.enet_base;
    Ethernet_device_struct.ptrPlatformInterruptDisable =
                        interfaceConfig.ptrPlatformInterruptDisable;
    Ethernet_device_struct.ptrPlatformInterruptEnable =
                        interfaceConfig.ptrPlatformInterruptEnable;
    Ethernet_device_struct.ptrPlatformPeripheralEnable =
                        interfaceConfig.ptrPlatformPeripheralEnable;
    Ethernet_device_struct.ptrPlatformPeripheralReset =
                        interfaceConfig.ptrPlatformPeripheralReset;
    if(NULL != Ethernet_device_struct.ptrPlatformPeripheralEnable)
    {
        (*Ethernet_device_struct.ptrPlatformPeripheralEnable)
                        (interfaceConfig.peripheralNum);
    }
    for(i = 0; i < ETHERNET_NUM_INTERRUPTS; i++)
    {
        Ethernet_device_struct.interruptNum[i]= interfaceConfig.interruptNum[i];
    }

    phyMode = (uint32_t)interfaceConfig.phyMode;
    clockSel = (uint32_t)interfaceConfig.clockSel;

    HWREG(Ethernet_device_struct.baseAddresses.ss_base + ETHERNETSS_O_CTRLSTS) =
            ((((uint32_t)ETHERNET_SS_CTRLSTS_WRITE_KEY_VALUE <<
               ETHERNETSS_CTRLSTS_WRITE_KEY_S) &
              ETHERNETSS_CTRLSTS_WRITE_KEY_M) |
             (phyMode <<
              ((uint32_t)  ETHERNETSS_CTRLSTS_PHY_INTF_SEL_S)) |
             (clockSel <<
              ((uint32_t)ETHERNET_SS_CTRLSTS_CLK_SRC_SEL_S)));
    //
    //RevMII address is latched on reset of the Ethernet module
    // so configure before releasing reset for Ethernet module
    //
    if(interfaceConfig.phyMode == ETHERNET_SS_PHY_INTF_SEL_REVMII)
    {
        Ethernet_configureRevMIIAddress(EMAC_SS_BASE,
                                interfaceConfig.localPhyAddress,
                                interfaceConfig.remotePhyAddress);
     }
     if(NULL != Ethernet_device_struct.ptrPlatformPeripheralReset)
    {
        (*Ethernet_device_struct.ptrPlatformPeripheralReset)
                        (interfaceConfig.peripheralNum);
    }
    Ethernet_resetModule(Ethernet_device_struct.baseAddresses.enet_base);
    Ethernet_device_struct.rxBuffIndex = 0U;

    //
    //Return the pointer to Init initConfig structure that should be used by
    // the application to provide the Initial configuration in the Open call
    //It can be built with Ethernet_BuildInitConfigAPI
    //
    return(&Ethernet_device_struct.initConfig);
}

void Ethernet_getInitConfig(Ethernet_InitConfig *configPtr)
{

    uint32_t i;

    //
    //EMAC Subsystem Wrapper Settings
    //
    configPtr->emacSSConfig.clkSrcSel =
                ETHERNET_SS_CTRLSTS_CLK_SRC_SEL_EXTERNAL;
    configPtr->emacSSConfig.flowControlEn =
                ETHERNET_SS_CTRLSTS_FLOW_CTRL_EN_DISABLED;
    configPtr->emacSSConfig.LoopBackModeClkSel =
        ETHERNET_SS_CTRLSTS_LMCLKSEL_NORMAL;
    configPtr->emacSSConfig.phyIntfSel = ETHERNET_SS_CTRLSTS_PHY_INTF_SEL_GMII;

    //
    //DMA Settings
    //1:1 Ratio
    //
    configPtr->priorityRatio = ETHERNET_DMA_OPERATION_MODE_PR_TX1_RX1;
    configPtr->transmitArbitrationAlgorithm =
                    ETHERNET_DMA_OPERATION_MODE_DA_ROUND_ROBIN;
    //
    //MTL Operation Settings
    //
    configPtr->txSchedulingAlgoritm =
                            ETHERNET_MTL_OPERATON_MODE_SCHALG_STRICT_PRIORITY;
    //
    //Strict Priority
    //
    configPtr->receiveArbitrationAlgorithm =
                            ETHERNET_MTL_OPERATION_MODE_RAA_SP;

    //
    //MAC Configuration Settings
    //
    configPtr->linkMode = ETHERNET_MAC_CONFIGURATION_DM_FULL_DUPLEX;
    configPtr->loopbackMode = ETHERNET_MAC_CONFIGURATION_LM_LOOPBACK_DISABLED;

    //
    //MAC Filter Configuration Seetings
    //
    configPtr->macFilterConfig.promiscuousMode    =   ETHERNET_DISABLE;
    configPtr->macFilterConfig.hashUnicast            =   ETHERNET_DISABLE;
    configPtr->macFilterConfig.hashMulticast      =   ETHERNET_DISABLE;
    configPtr->macFilterConfig.daInverseFilter        =   ETHERNET_DISABLE;
    configPtr->macFilterConfig.passAllMulticast       =   ETHERNET_DISABLE;
    configPtr->macFilterConfig.disableBroadCastPackets = ETHERNET_DISABLE;
    configPtr->macFilterConfig.passControlPackets =
                        ETHERNET_MAC_PACKET_FILTER_PCF_FILTER_ALL_CTRL;
    configPtr->macFilterConfig.saInverseFilter    =       ETHERNET_DISABLE;
    configPtr->macFilterConfig.saFilterEnable =       ETHERNET_DISABLE;
    configPtr->macFilterConfig.hashPerfectFilter  =       ETHERNET_DISABLE;
    configPtr->macFilterConfig.vlanFilterEnable =         ETHERNET_DISABLE;
    configPtr->macFilterConfig.l3L4FilterEnable =         ETHERNET_DISABLE;
    configPtr->macFilterConfig.dropNonTCP =            ETHERNET_DISABLE;
    configPtr->macFilterConfig.receiveAll =           ETHERNET_DISABLE;

    /*
    Assign number of Packets for Buffer Allocation
    These values should be changed as per application needs
    Ideally the buffers should be provided by the upper layer
    But here we maintain packet buffer for Receive path
    TX Path is provided by Application

    */
    configPtr->noofPacketsRxBuffer        =   ETHERNET_NO_OF_RX_PACKETS;
    configPtr->maxPacketLengthRxBuffer = ETHERNET_MAX_PACKET_LENGTH;

    /*Tx and RX DMA Burst Length*/

    //
    //Max Packet Size
    //
    configPtr->pktMTU = ETHERNET_MAX_PACKET_LENGTH;
    configPtr->numChannels = ETHERNET_MAX_NUM_DMA_CHANNELS;
    /*Init of TX DMA Channels*/
    for(i = 0U;i < configPtr->numChannels;i++)
    {
        configPtr->chInfo[ETHERNET_CH_DIR_TX][i].burstLength =
                            ETHERNET_DMA_BURST_LENGTH;
        configPtr->chInfo[ETHERNET_CH_DIR_TX][i].queueThreshold =
                            ETHERNET_MTL_TXQ0_OPERATION_MODE_TTC_32;
        configPtr->chInfo[ETHERNET_CH_DIR_TX][i].dmaQueueSize =
                            ETHERNET_MTL_Q_OP_MODE_QSIZE_512;
        configPtr->chInfo[ETHERNET_CH_DIR_TX][i].storeNForward =
                            ETHERNET_MTL_TXQ_OPMODE_TSF_ENABLE ;
        configPtr->chInfo[ETHERNET_CH_DIR_TX][i].chDir = ETHERNET_CH_DIR_TX;
        configPtr->chInfo[ETHERNET_CH_DIR_TX][i].numBD =
                            ETHERNET_DESCRIPTORS_NUM_TX_PER_CHANNEL;
        configPtr->chInfo[ETHERNET_CH_DIR_TX][i].chNum = i;
    }
    /*Init of Rx DMA Channels*/
    for(i = 0U;i < configPtr->numChannels;i++)
    {
        configPtr->chInfo[ETHERNET_CH_DIR_RX][i].burstLength =
                            ETHERNET_DMA_BURST_LENGTH;
        configPtr->chInfo[ETHERNET_CH_DIR_RX][i].queueThreshold =
                            ETHERNET_MTL_RXQ0_OPERATION_MODE_RTC_32;
        configPtr->chInfo[ETHERNET_CH_DIR_RX][i].dmaQueueSize =
                            ETHERNET_MTL_Q_OP_MODE_QSIZE_2048;
        configPtr->chInfo[ETHERNET_CH_DIR_RX][i].dmaBufferSize =
                            ETHERNET_DMA_CHX_RX_CONTROL_RBSZ_2K;
        configPtr->chInfo[ETHERNET_CH_DIR_RX][i].storeNForward =
                            ETHERNET_MTL_RX_Q_OP_MODE_RSF_ENABLE ;
        configPtr->chInfo[ETHERNET_CH_DIR_RX][i].chDir = ETHERNET_CH_DIR_RX;
        configPtr->chInfo[ETHERNET_CH_DIR_RX][i].numBD =
                            ETHERNET_DESCRIPTORS_NUM_RX_PER_CHANNEL;
        configPtr->chInfo[ETHERNET_CH_DIR_RX][i].chNum = i;
    }

    //
    //PerCh interrupts are not routed to sbd_intr
    //
    configPtr->dmaMode.InterruptMode = ETHERNET_DMA_MODE_INTM_MODE1;

    //
    // Similar call backs should be assigned by application as following
    //
    //
    // RX Get Buffer Callback
    //
    //configPtr->pfcbGetPacket = &Ethernet_getPacketBuffer;
    //
    // Tx Packet completion callback
    //
    //configPtr->pfcbFreePacket = &Ethernet_releaseTxPacketBuffer;
    //
    // Rx Packet Completion callback
    //
    //configPtr->pfcbRxPacket = &Ethernet_receivePacketCallback;
    //
    //
    //Callback called during Receive Buffer Unavailable handling
    //
    configPtr->pfcbDeletePackets = NULL;
    //
    //Callback for LPI Events
    //
    configPtr->pfcbLPIPacketReceived = NULL;
}

uint32_t Ethernet_sendPacket(Ethernet_Handle hEMAC, Ethernet_Pkt_Desc *pktPtr)
{
    Ethernet_Device *devicePtr;
    uint32_t          fragcnt, pktlen;
    Ethernet_Pkt_Desc        *pktLastPtr;
    Ethernet_DescCh     *channelDescPtr;
    Ethernet_DmaObj *dmaObj;
    Ethernet_ChInfo   *txChan;



    devicePtr = (Ethernet_Device *)hEMAC;

    if((0U == devicePtr) || (devicePtr->devMagic != ETHERNET_DRV_DEVMAGIC))
    {
         return(ETHERNET_ERR_INVALID_HANDLE);
    }
    if(0U == pktPtr)
    {
        return(ETHERNET_ERR_INVALID_PARAM);
    }
    /* Do some packet validation*/
    if(0U == (pktPtr->flags & ETHERNET_PKT_FLAG_SOP))
     {
        return(ETHERNET_ERR_BAD_PACKET);
      }

    if(pktPtr->pktLength > devicePtr->pktMTU)
     {
        return(ETHERNET_ERR_BAD_PACKET);
      }
    /* Count the number of frags in this packet*/
    fragcnt = 1;
    pktlen  = pktPtr->pktLength;

    pktLastPtr = pktPtr;
    while(0U == (pktLastPtr->flags & ETHERNET_PKT_FLAG_EOP))
    {
        if(0U == pktLastPtr->nextPacketDesc)
        {
            return(ETHERNET_ERR_INVALID_PARAM);
        }
        pktlen -= pktLastPtr->bufferLength;
        pktLastPtr = pktLastPtr->nextPacketDesc;
        fragcnt++;

        /* At this point we can't have another SOP*/
        if(0U != (pktLastPtr->flags & ETHERNET_PKT_FLAG_SOP))
         {
            return(ETHERNET_ERR_BAD_PACKET);
          }
    }
    /* The final packet frag must be the last in the list*/
    if(0U != pktLastPtr->nextPacketDesc)
    {
        return(ETHERNET_ERR_BAD_PACKET);
    }

    /* The frag count must be correct*/
    if(fragcnt != pktPtr->numPktFrags)
    {
        return(ETHERNET_ERR_BAD_PACKET);
    }

    dmaObj  = &devicePtr->dmaObj;
    txChan  =
    &devicePtr->initConfig.chInfo[ETHERNET_CH_DIR_TX][pktPtr->pktChannel];
    /* Get a local pointer to the descriptor channel*/
    ASSERT(NULL != dmaObj);
    channelDescPtr = &(dmaObj->txDma[pktPtr->pktChannel]);
    ASSERT(NULL != channelDescPtr);
    channelDescPtr->chInfo = txChan;

    /* Make sure this packet does not have too many frags to fit */
    if(fragcnt > channelDescPtr->descMax)
     {
        return(ETHERNET_ERR_BAD_PACKET);
      }
    /*
     * Queue and packet and service transmitter
     */

    Ethernet_performPushPacketQueueChain(&channelDescPtr->waitQueue, pktPtr,
                            pktLastPtr, fragcnt);
    Ethernet_addPacketsIntoTxQueue(channelDescPtr);

    return(ETHERNET_RET_SUCCESS);

}

interrupt void Ethernet_transmitISR(void)
{

    Ethernet_TxChDesc *txChan;
        if(0U != (HWREG(Ethernet_device_struct.baseAddresses.enet_base +
                        ETHERNET_O_DMA_CH0_STATUS) &
                  ETHERNET_DMA_CH0_STATUS_TI))
        {
            txChan =
            &Ethernet_device_struct.dmaObj.txDma[ETHERNET_DMA_CHANNEL_NUM_0];
            Ethernet_removePacketsFromTxQueue(txChan,
                ETHERNET_COMPLETION_NORMAL);
            //
            //Clear the interrupt at Module
            //
            Ethernet_clearDMAChannelInterrupt(
            Ethernet_device_struct.baseAddresses.enet_base,
            ETHERNET_DMA_CHANNEL_NUM_0,
            ETHERNET_DMA_CH0_STATUS_TI
            );
        }
        if(0U != (HWREG(Ethernet_device_struct.baseAddresses.enet_base +
                        ETHERNET_CHANNEL_OFFSET +
                        ETHERNET_O_DMA_CH0_STATUS) &
                  ETHERNET_DMA_CH0_STATUS_TI))
        {
            txChan = &Ethernet_device_struct.dmaObj.txDma[1];
            Ethernet_removePacketsFromTxQueue(txChan,
                        ETHERNET_COMPLETION_NORMAL);
           //
           //Clear the interrupt at module
           //
           Ethernet_clearDMAChannelInterrupt(
            Ethernet_device_struct.baseAddresses.enet_base,
            ETHERNET_DMA_CHANNEL_NUM_1,
            ETHERNET_DMA_CH0_STATUS_TI
            );
        }
#ifdef ETHERNET_DEBUG
    Ethernet_txInterruptCount++;
#endif
}

interrupt void Ethernet_receiveISR(void)
{
    //
    //Call the callback function
    //It is expected to replenish the Buffer for the packet just received
    //

    Ethernet_RxChDesc *rxChan;
        if(0U != (HWREG(Ethernet_device_struct.baseAddresses.enet_base +
                        ETHERNET_O_DMA_CH0_STATUS) &
                  ETHERNET_DMA_CH0_STATUS_RI))
        {
            rxChan =
             &Ethernet_device_struct.dmaObj.rxDma[ETHERNET_DMA_CHANNEL_NUM_0];
            Ethernet_removePacketsFromRxQueue(rxChan,
                        ETHERNET_COMPLETION_NORMAL);

            Ethernet_clearDMAChannelInterrupt(
                Ethernet_device_struct.baseAddresses.enet_base,
                ETHERNET_DMA_CHANNEL_NUM_0,
                ETHERNET_DMA_CH0_STATUS_RI
                );
        }
        if(0U != (HWREG(Ethernet_device_struct.baseAddresses.enet_base +
                        ETHERNET_CHANNEL_OFFSET +
                        ETHERNET_O_DMA_CH0_STATUS) &
                  ETHERNET_DMA_CH0_STATUS_RI))
        {
            rxChan =
              &Ethernet_device_struct.dmaObj.rxDma[ETHERNET_DMA_CHANNEL_NUM_1];
            Ethernet_removePacketsFromRxQueue(rxChan,
                                              ETHERNET_COMPLETION_NORMAL);

            Ethernet_clearDMAChannelInterrupt(
                Ethernet_device_struct.baseAddresses.enet_base,
                ETHERNET_DMA_CHANNEL_NUM_1,
                ETHERNET_DMA_CH0_STATUS_RI
                );
        }
#ifdef ETHERNET_DEBUG
    Ethernet_rxInterruptCount++;
#endif
}

/*
* This is a Generic Interrupt Service Routine
* Handler for sbd_intr
* Currently it handles the
* Early Transmit for Channel 0
* Early Receive for Channel 0
* Receive Interrupt for Channel 0
* Transmit Buffer Unavailable for Channel 0
* Receive Buffer Unavailable Interrupt for Channel 0
* Early Transmit for Channel 1
* Early Receive for Channel 1
* Receive Interrupt for Channel 1
* Transmit Buffer Unavailable for Channel 1
* Receive Buffer Unavailable Interrupt for Channel 1
* Mac interrupt Status for Magic Packet, Remote Wakeup Packets
* Timestamp interrupt
* RevMII link status interrupt
*
* This assumes the INTM interrupt mode 1
*
*/
interrupt void Ethernet_genericISR(void)
{
    Ethernet_RxChDesc *rxChan;
    Ethernet_TxChDesc *txChan;
    Ethernet_HW_descriptor    *descPtr;
    Ethernet_HW_descriptor    *tailPtr;
#ifdef ETHERNET_DEBUG
    Ethernet_genericInterruptCount++;
#endif

    uint16_t revmiiIntStatus;

    uint32_t lpiStatus;
    uint32_t pmtStatus;

        if(0U != (HWREG(Ethernet_device_struct.baseAddresses.enet_base +
                        ETHERNET_O_DMA_CH0_STATUS) &
                  (uint32_t)ETHERNET_DMA_CH0_STATUS_ETI))
        {
            //
            //Early Tx Interrupt
            //Handle the interrupt only when the Interrupt was enabled by
            //Otherwise we do not want unintentional Tx Processing
            //Unlike the Early Rx Interrupt the Tx Early interrupt
            //stays active even after the Tx Completion interrupt is asserted
            //Hence we do not want to POP the twice from
            //Tx Queue
            //
            if(0U != (HWREG(Ethernet_device_struct.baseAddresses.enet_base +
                            ETHERNET_O_DMA_CH0_INTERRUPT_ENABLE) &
                      (uint32_t)ETHERNET_DMA_CH0_INTERRUPT_ENABLE_ETIE))
                {
                    txChan =
                       &Ethernet_device_struct.dmaObj.txDma[
                                                ETHERNET_DMA_CHANNEL_NUM_0];

                    Ethernet_removePacketsFromTxQueue(txChan,
                      (Ethernet_CompletionMode) ETHERNET_COMPLETION_EARLY);

                    Ethernet_clearDMAChannelInterrupt(
                            Ethernet_device_struct.baseAddresses.enet_base,
                            ETHERNET_DMA_CHANNEL_NUM_0,
                            (ETHERNET_DMA_CH0_STATUS_ETI |
                             ETHERNET_DMA_CH0_STATUS_AIS));
#ifdef ETHERNET_DEBUG
                    Ethernet_earlyTxInterruptCount++;
#endif
                }
        }
        if(0U != (HWREG(Ethernet_device_struct.baseAddresses.enet_base +
                        ETHERNET_O_DMA_CH0_STATUS ) &
                 (uint32_t) ETHERNET_DMA_CH0_STATUS_ERI))
        {
              //
              //Early Rx Interrupt
              //Remove the packet from queue and notify to application
              //
              rxChan =
              &Ethernet_device_struct.dmaObj.rxDma[ETHERNET_DMA_CHANNEL_NUM_0];
              Ethernet_removePacketsFromRxQueue(rxChan,
                      ETHERNET_COMPLETION_EARLY);

            Ethernet_clearDMAChannelInterrupt(
                Ethernet_device_struct.baseAddresses.enet_base,
                ETHERNET_DMA_CHANNEL_NUM_0,
                (ETHERNET_DMA_CH0_STATUS_ERI | ETHERNET_DMA_CH0_STATUS_NIS));
#ifdef ETHERNET_DEBUG
            Ethernet_earlyRxInterruptCount++;
#endif
        }
        else if(0U != (HWREG(Ethernet_device_struct.baseAddresses.enet_base +
                             ETHERNET_O_DMA_CH0_STATUS) &
                       (uint32_t) ETHERNET_DMA_CH0_STATUS_RI))
        {
            //
            //Receive Interrupt
            //In some cases towards the end of the Buffer the Early receive
            //Notification might be cleared
            //Handle it only in Per Channel interrupt
            //
#ifdef ETHERNET_DEBUG
            Ethernet_genericRxCompletionInterruptCount++;
#endif
            Ethernet_clearDMAChannelInterrupt(
                Ethernet_device_struct.baseAddresses.enet_base,
                ETHERNET_DMA_CHANNEL_NUM_0,
                ETHERNET_DMA_CH0_STATUS_NIS);
        }
       /*  Check for Normal Interrupt (NIS) and TX Buffer Unavailable (TBU) */
        else if((ETHERNET_DMA_CH0_STATUS_NIS | ETHERNET_DMA_CH0_STATUS_TBU) ==
                (HWREG(Ethernet_device_struct.baseAddresses.enet_base +
                        ETHERNET_O_DMA_CH0_STATUS) &
                        (uint32_t)(ETHERNET_DMA_CH0_STATUS_NIS |
                                   ETHERNET_DMA_CH0_STATUS_TBU)))
            {
#ifdef ETHERNET_DEBUG
                Ethernet_txChan0BufUnavail++;
#endif

                /*
                 * Clear the NIS and TBU status bit. These MUST be
                 * cleared together!
                 */
                Ethernet_clearDMAChannelInterrupt(
                    Ethernet_device_struct.baseAddresses.enet_base,
                    ETHERNET_DMA_CHANNEL_NUM_0,
                    ETHERNET_DMA_CH0_STATUS_NIS | ETHERNET_DMA_CH0_STATUS_TBU);
            }
       /*  Check for Abnormal Interrupt (AIS) and RX Buffer Unavailable (RBU) */
        else  if((ETHERNET_DMA_CH0_STATUS_AIS |
                   ETHERNET_DMA_CH0_STATUS_RBU) ==
                 (HWREG(Ethernet_device_struct.baseAddresses.enet_base +
                        ETHERNET_O_DMA_CH0_STATUS) &
                        (uint32_t)(ETHERNET_DMA_CH0_STATUS_AIS |
                                   ETHERNET_DMA_CH0_STATUS_RBU)))
        {

#ifdef ETHERNET_DEBUG
            Ethernet_rxChan0BufUnavail++;
#endif

            /*
             * Clear the AIS and RBU status bit. These MUST be
             * cleared together!
             */
            Ethernet_clearDMAChannelInterrupt(
                    Ethernet_device_struct.baseAddresses.enet_base,
                    ETHERNET_DMA_CHANNEL_NUM_0,
                    ETHERNET_DMA_CH0_STATUS_AIS |
                    ETHERNET_DMA_CH0_STATUS_RBU);

            /*
           *Recover from Receive Buffer Unavailable (and hung DMA)
         *
         * All descriptor buffers are owned by the application, and
         * in result the DMA cannot transfer incoming frames to the
         * buffers (RBU condition). DMA has also entered suspend
         * mode at this point, too.
         *
         * Drain the RX queues
         */

            /* Upon RBU error, discard all previously received packets */
            if(Ethernet_device_struct.initConfig.pfcbDeletePackets != NULL)
                (*Ethernet_device_struct.initConfig.pfcbDeletePackets)();

            rxChan =
               &Ethernet_device_struct.dmaObj.rxDma[ETHERNET_DMA_CHANNEL_NUM_0];

    /*
     * Need to disable multiple interrupts, so protect the code to do so within
     * a global disable block (to prevent getting interrupted in between)
     */

            if(NULL!= Ethernet_device_struct.ptrPlatformInterruptDisable)
            {
                (*Ethernet_device_struct.ptrPlatformInterruptDisable)(
                    Ethernet_device_struct.interruptNum[
                        ETHERNET_RX_INTR_CH0 + rxChan->chInfo->chNum]);

                (*Ethernet_device_struct.ptrPlatformInterruptDisable)(
                    Ethernet_device_struct.interruptNum[
                        ETHERNET_GENERIC_INTERRUPT]);
            }

            /* verify we have full capacity in the descriptor queue */
            if(rxChan->descQueue.count < rxChan->descMax) {
              /* The queue is not at full capacity due to OOM errors.
              Try to fill it again */
                Ethernet_addPacketsIntoRxQueue(rxChan);
            }

    /*
     * Need to re-enable multiple interrupts. Again, protect the code to do so
     * within a global disable block (to prevent getting interrupted in between)
     */

            if(NULL!= Ethernet_device_struct.ptrPlatformInterruptEnable)
            {
                (*Ethernet_device_struct.ptrPlatformInterruptEnable)(
                    Ethernet_device_struct.interruptNum[
                        ETHERNET_RX_INTR_CH0 + rxChan->chInfo->chNum]);
                (*Ethernet_device_struct.ptrPlatformInterruptEnable)(
                    Ethernet_device_struct.interruptNum[
                        ETHERNET_GENERIC_INTERRUPT]);
            }
            Ethernet_removePacketsFromRxQueue(rxChan,
                    ETHERNET_COMPLETION_NORMAL);

            /* To un-suspend the DMA:
             *
             * 1. Change ownership of current RX descriptor to DMA
             *
             * 2. Issue a receive poll demand command
             *
             * 3. Issue a write to the descriptor tail pointer register
             */

            /* 1. Change current descriptor owernship back to DMA */
            descPtr = (Ethernet_HW_descriptor *)(HWREG(
                    Ethernet_device_struct.baseAddresses.enet_base +
                    (uint32_t)ETHERNET_O_DMA_CH0_CURRENT_APP_RXDESC));

            descPtr->des3 = ETHERNET_DESC_OWNER | ETHERNET_RX_DESC_IOC |
                              ETHERNET_RX_DESC_BUF1_VALID;

            /* 2. Issue a receive poll demand command */

            /* 3. Issue a write to the descriptor tail pointer register */
            tailPtr = (Ethernet_HW_descriptor *)(HWREG(
                        Ethernet_device_struct.baseAddresses.enet_base +
                        (uint32_t)ETHERNET_O_DMA_CH0_RXDESC_TAIL_POINTER));

            Ethernet_writeRxDescTailPointer(
                    Ethernet_device_struct.baseAddresses.enet_base,
                    ETHERNET_DMA_CHANNEL_NUM_0,
                    tailPtr);

        }
    //
    //Channel1 interrupts and ETI interrupt
    //
     else if(0U != (HWREG(Ethernet_device_struct.baseAddresses.enet_base +
                          ETHERNET_O_DMA_CH1_STATUS) &
                    (uint32_t)ETHERNET_DMA_CH1_STATUS_ETI))
        {
            //
            //In some cases towards the end of the Buffer the Early receive
            //Notification might be cleared
            //Handle it only in Per Channel interrupt
            //
            if(0U != (HWREG(Ethernet_device_struct.baseAddresses.enet_base +
                            ETHERNET_O_DMA_CH1_INTERRUPT_ENABLE) &
                      (uint32_t)ETHERNET_DMA_CH1_INTERRUPT_ENABLE_ETIE))
            {
                txChan =
                    &Ethernet_device_struct.dmaObj.txDma[
                                            ETHERNET_DMA_CHANNEL_NUM_1];
                Ethernet_removePacketsFromTxQueue(txChan,
                                                  ETHERNET_COMPLETION_EARLY);
                Ethernet_clearDMAChannelInterrupt(
                    Ethernet_device_struct.baseAddresses.enet_base,
                    ETHERNET_DMA_CHANNEL_NUM_1,
                    (ETHERNET_DMA_CH1_STATUS_ETI |
                     ETHERNET_DMA_CH1_STATUS_AIS));
#ifdef ETHERNET_DEBUG
                Ethernet_earlyTxInterruptCount++;
#endif
            }
        }
        //
        //Channel1 ERI
        //
        else if(0U !=
                (HWREG(Ethernet_device_struct.baseAddresses.enet_base +
                       ETHERNET_O_DMA_CH1_STATUS) &
                 (uint32_t)ETHERNET_DMA_CH1_STATUS_ERI))
        {
              //
              //Remove the packet from queue and notify to application
              //
              rxChan =
              &Ethernet_device_struct.dmaObj.rxDma[
               ETHERNET_DMA_CHANNEL_NUM_1];
              Ethernet_removePacketsFromRxQueue(rxChan,
                      ETHERNET_COMPLETION_EARLY);

            Ethernet_clearDMAChannelInterrupt(
                Ethernet_device_struct.baseAddresses.enet_base,
                ETHERNET_DMA_CHANNEL_NUM_1,
                (ETHERNET_DMA_CH1_STATUS_ERI | ETHERNET_DMA_CH1_STATUS_NIS));
#ifdef ETHERNET_DEBUG
            Ethernet_earlyRxInterruptCount++;
#endif
        }
        //
        //Channel 1 RI
        //
        else if(0U != (HWREG(Ethernet_device_struct.baseAddresses.enet_base +
                             ETHERNET_O_DMA_CH1_STATUS) &
                       (uint32_t)ETHERNET_DMA_CH1_STATUS_RI))
        {
            //
            //In some cases towards the end of the Buffer the Early receive
            //Notification might be cleared
            //Handle it only in Perchannel interrupt
            //
#ifdef ETHERNET_DEBUG
            Ethernet_genericRxCompletionInterruptCount++;
#endif
            Ethernet_clearDMAChannelInterrupt(
            Ethernet_device_struct.baseAddresses.enet_base,
            ETHERNET_DMA_CHANNEL_NUM_1,
            ETHERNET_DMA_CH1_STATUS_NIS);
        }
        /*Check for Normal Interrupt (NIS) and TX Buffer Unavailable (TBU) */
        else if((ETHERNET_DMA_CH1_STATUS_NIS |
                  ETHERNET_DMA_CH1_STATUS_TBU) ==
                (HWREG(Ethernet_device_struct.baseAddresses.enet_base +
                       ETHERNET_O_DMA_CH1_STATUS) &
                        (uint32_t)(ETHERNET_DMA_CH1_STATUS_NIS |
                                   ETHERNET_DMA_CH1_STATUS_TBU)))
            {
#ifdef ETHERNET_DEBUG
                Ethernet_txChan1BufUnavail++;
#endif
                /*
                 * Clear the NIS and TBU status bit. These MUST be
                 * cleared together!
                 */
                Ethernet_clearDMAChannelInterrupt(
                    Ethernet_device_struct.baseAddresses.enet_base,
                    ETHERNET_DMA_CHANNEL_NUM_1,
                    ETHERNET_DMA_CH1_STATUS_NIS | ETHERNET_DMA_CH1_STATUS_TBU);
            }
        /*Check for Abnormal Interrupt (AIS) and RX Buffer Unavailable (RBU) */
        else  if((ETHERNET_DMA_CH1_STATUS_AIS |
                   ETHERNET_DMA_CH1_STATUS_RBU) ==
                  (HWREG(Ethernet_device_struct.baseAddresses.enet_base +
                         ETHERNET_O_DMA_CH1_STATUS) &
                         (uint32_t)(ETHERNET_DMA_CH1_STATUS_AIS |
                                    ETHERNET_DMA_CH1_STATUS_RBU)))
         {

#ifdef ETHERNET_DEBUG
                Ethernet_rxChan1BufUnavail++;
#endif

            /*
             * Clear the AIS and RBU status bit. These MUST be
             * cleared together!
             */
            Ethernet_clearDMAChannelInterrupt(
                    Ethernet_device_struct.baseAddresses.enet_base,
                    ETHERNET_DMA_CHANNEL_NUM_1,
                    ETHERNET_DMA_CH1_STATUS_AIS |
                    ETHERNET_DMA_CH1_STATUS_RBU);

         /*
         * Recover from Receive Buffer Unavailable (and hung DMA)
         *
         * All descriptor buffers are owned by the application, and
         * in result the DMA cannot transfer incoming frames to the
         * buffers (RBU condition). DMA has also entered suspend
         * mode at this point, too.
         *
         * Drain the RX queues
         */

            /* Upon RBU error, discard all previously received packets */
            if(Ethernet_device_struct.initConfig.pfcbDeletePackets != NULL)
                (*Ethernet_device_struct.initConfig.pfcbDeletePackets)();

            rxChan =
               &Ethernet_device_struct.dmaObj.rxDma[ETHERNET_DMA_CHANNEL_NUM_1];

    /*
     * Need to disable multiple interrupts, so protect the code to do so within
     * a global disable block (to prevent getting interrupted in between)
     */

            if(NULL!= Ethernet_device_struct.ptrPlatformInterruptDisable)
            {
                (*Ethernet_device_struct.ptrPlatformInterruptDisable)(
                    Ethernet_device_struct.interruptNum[
                        ETHERNET_RX_INTR_CH0 + rxChan->chInfo->chNum]);

                (*Ethernet_device_struct.ptrPlatformInterruptDisable)(
                    Ethernet_device_struct.interruptNum[
                        ETHERNET_GENERIC_INTERRUPT]);
            }

            /* verify we have full capacity in the descriptor queue */
            if(rxChan->descQueue.count < rxChan->descMax) {
            /* The queue is not at full capacity due to OOM errors.
            Try to fill it again */
                Ethernet_addPacketsIntoRxQueue(rxChan);
            }

    /*
     * Need to re-enable multiple interrupts. Again, protect the code to do so
     * within a global disable block (to prevent getting interrupted in between)
     */
            if(NULL!= Ethernet_device_struct.ptrPlatformInterruptEnable)
            {
                (*Ethernet_device_struct.ptrPlatformInterruptEnable)(
                    Ethernet_device_struct.interruptNum[
                        ETHERNET_RX_INTR_CH0 + rxChan->chInfo->chNum]);
                (*Ethernet_device_struct.ptrPlatformInterruptEnable)(
                    Ethernet_device_struct.interruptNum[
                        ETHERNET_GENERIC_INTERRUPT]);
            }

            Ethernet_removePacketsFromRxQueue(rxChan,
                    ETHERNET_COMPLETION_NORMAL);

            /* To un-suspend the DMA:
             *
             * 1. Change ownership of current RX descriptor to DMA
             *
             * 2. Issue a receive poll demand command
             *
             * 3. Issue a write to the descriptor tail pointer register
             */

            /* 1. Change current descriptor owernship back to DMA */
            descPtr = (Ethernet_HW_descriptor *)(HWREG(
                    Ethernet_device_struct.baseAddresses.enet_base +
                    (uint32_t)ETHERNET_O_DMA_CH1_CURRENT_APP_RXDESC));

            descPtr->des3 = ETHERNET_DESC_OWNER | ETHERNET_RX_DESC_IOC |
                            ETHERNET_RX_DESC_BUF1_VALID;

            /* 2. Issue a receive poll demand command */

            /* 3. Issue a write to the descriptor tail pointer register */
            tailPtr = (Ethernet_HW_descriptor *)(HWREG(
                    Ethernet_device_struct.baseAddresses.enet_base +
                    (uint32_t)ETHERNET_O_DMA_CH1_RXDESC_TAIL_POINTER));

            Ethernet_writeRxDescTailPointer(
                    Ethernet_device_struct.baseAddresses.enet_base,
                    ETHERNET_DMA_CHANNEL_NUM_1,
                    tailPtr);

         }
        //
        //Check if any MAC interrupt caused this interrupt at sbd line
        //
        else if(0U != (HWREG(Ethernet_device_struct.baseAddresses.enet_base +
                             ETHERNET_O_DMA_INTERRUPT_STATUS) &
                       (uint32_t)ETHERNET_DMA_INTERRUPT_STATUS_MACIS))
        {
            if(0U != (HWREG(Ethernet_device_struct.baseAddresses.enet_base +
                            ETHERNET_O_MAC_INTERRUPT_STATUS) &
                      ETHERNET_MAC_INTERRUPT_STATUS_LPIIS))
                {
                    //
                    //Check for EEE/LPI Interrupts
                    //
                   lpiStatus =
                       HWREG(Ethernet_device_struct.baseAddresses.enet_base +
                             ETHERNET_O_MAC_LPI_CONTROL_STATUS);
                   if(ETHERNET_MAC_LPI_CONTROL_STATUS_TLPIEN ==
                       (lpiStatus &
                        ETHERNET_MAC_LPI_CONTROL_STATUS_TLPIEN))
                   {
           #ifdef ETHERNET_DEBUG
                        Ethernet_eeeTxLPIEntryCount++;
           #endif
                    }
                   if(ETHERNET_MAC_LPI_CONTROL_STATUS_TLPIEX ==
                      (lpiStatus &
                       ETHERNET_MAC_LPI_CONTROL_STATUS_TLPIEX))
                   {
           #ifdef ETHERNET_DEBUG
                    Ethernet_eeeTxLPIExitCount++;
           #endif
                   }
                   if(ETHERNET_MAC_LPI_CONTROL_STATUS_RLPIEN ==
                      (lpiStatus &
                       ETHERNET_MAC_LPI_CONTROL_STATUS_RLPIEN))
                   {
           #ifdef ETHERNET_DEBUG
                       Ethernet_eeeRxLPIEntryCount++;
           #endif
                   }

                   if(ETHERNET_MAC_LPI_CONTROL_STATUS_RLPIEX ==
                      (lpiStatus &
                       ETHERNET_MAC_LPI_CONTROL_STATUS_RLPIEX))
                    {
           #ifdef ETHERNET_DEBUG
                        Ethernet_eeeRxLPIExitCount++;
           #endif
                    }

                }
            else if(0U !=
                    (HWREG(Ethernet_device_struct.baseAddresses.enet_base +
                           ETHERNET_O_MAC_INTERRUPT_STATUS) &
                     ETHERNET_MAC_INTERRUPT_STATUS_PMTIS))
                {
                   #ifdef ETHERNET_DEBUG
                        Ethernet_pmtInterruptCount++;
                   #endif
                     pmtStatus =
                     HWREG(Ethernet_device_struct.baseAddresses.enet_base +
                           ETHERNET_O_MAC_PMT_CONTROL_STATUS);
                   if(0U !=
                      (pmtStatus &
                       (uint32_t)ETHERNET_MAC_PMT_CONTROL_STATUS_MGKPRCVD))
                    {
                        #ifdef ETHERNET_DEBUG
                            Ethernet_magicPktReceivedCount++;
                        #endif
                        //
                        //Turn off TX Clock Gating
                        //
                        Ethernet_configureEEEClockGatingControl(
                            Ethernet_device_struct.baseAddresses.enet_base,
                            false);
                        //
                        //With just the EEE Clock gating setting the
                        //Clocks are not turned On. Hence Exiting EEE mode
                        //
                        Ethernet_disableTxEEEMode(
                            Ethernet_device_struct.baseAddresses.enet_base);
                        if(NULL !=
                        Ethernet_device_struct.initConfig.pfcbLPIPacketReceived)
                         {
                            //
                            //Call the callback function to notify application
                            //Second parameter NULL and intended for future use
                            //
                            (*Ethernet_device_struct.initConfig.pfcbLPIPacketReceived)(
                                   ETHERNET_EEE_RX_LPI_MAGICPKT_RECEIVED, NULL);
                         }
                    }
                   else if(0U !=
                           (pmtStatus &
                            (uint32_t)ETHERNET_MAC_PMT_CONTROL_STATUS_RWKPRCVD))
                    {
                    #ifdef ETHERNET_DEBUG
                        Ethernet_rwakeupPktReceivedCount++;
                    #endif
                        //
                        //Turn off TX Clock Gating
                        //
                        Ethernet_configureEEEClockGatingControl(
                            Ethernet_device_struct.baseAddresses.enet_base,
                            false);
                       //
                       //With just the EEE Clock gating setting the
                       //Clocks are not turned On. Hence turning OFF EEE mode
                       //
                        Ethernet_disableTxEEEMode(
                            Ethernet_device_struct.baseAddresses.enet_base);
                       if(NULL != Ethernet_device_struct.initConfig.pfcbLPIPacketReceived)
                         {
                            //
                            //Call the callback function to notify application
                            //Second parameter NULL and intended for future use
                            //
                            (*Ethernet_device_struct.initConfig.pfcbLPIPacketReceived)(
                               ETHERNET_EEE_RX_LPI_RMTWKUP_PKT_RECEIVED, NULL);
                         }
                    }

                }
            }
           else if(true == Ethernet_isTimestampIntActive())
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
           else
            {
            //
            //Check for RevMII link status change interrupt
            //Read RevMII Interrupt Status Mask Register
            //
               revmiiIntStatus =
                    Ethernet_readPHYRegister(
                        Ethernet_device_struct.baseAddresses.enet_base,
                        ETHERNET_REVMII_INTERRUPT_STATUS_MASK);
               if(ETHERNET_REVMII_INTERRUPT_STATUS_MASK_LSI_M ==
                  (revmiiIntStatus &
                   ETHERNET_REVMII_INTERRUPT_STATUS_MASK_LSI_M))
                {
                    //
                    //Clear the interrupt by writing to
                    //LSI field of RevMII Interrupt
                    //Status Mask Register
                    //
                    revmiiIntStatus &=
                    ETHERNET_REVMII_INTERRUPT_STATUS_MASK_LSI_M;
#ifdef ETHERNET_DEBUG
                    Ethernet_phyLinkStatusChangeInterruptCount++;
#endif
                    Ethernet_writePHYRegister(
                    Ethernet_device_struct.baseAddresses.enet_base,
                    ETHERNET_REVMII_INTERRUPT_STATUS_MASK,
                    revmiiIntStatus);
                }
            }

}

bool Ethernet_isTimestampIntActive(void)
{
    bool status;

    if(ETHERNET_MAC_INTERRUPT_STATUS_TSIS ==
       (HWREG(Ethernet_device_struct.baseAddresses.enet_base +
             ETHERNET_O_MAC_INTERRUPT_STATUS) &
        ETHERNET_MAC_INTERRUPT_STATUS_TSIS))
        status = true;
    else
        status = false;

    return(status);
}

bool Ethernet_isTransmitTimestampStatusSet(void)
{
    bool status;

    if(ETHERNET_MAC_TIMESTAMP_STATUS_TXTSSIS ==
       (HWREG(Ethernet_device_struct.baseAddresses.enet_base +
             ETHERNET_O_MAC_TIMESTAMP_STATUS) &
        ETHERNET_MAC_TIMESTAMP_STATUS_TXTSSIS))
        status = true;
    else
        status = false;

    return(status);
}

uint32_t Ethernet_getStatistics(Ethernet_Handle hEMAC,
                                Ethernet_Statistics *statisticsPtr)
{
    uint32_t i;
    volatile uint32_t *regAddrPtr;
    uint32_t *statAddrPtr;
    uint32_t statval;
    Ethernet_Device *devicePtr;
    devicePtr = (Ethernet_Device *)hEMAC;

    if((0U == devicePtr) || (ETHERNET_DRV_DEVMAGIC != devicePtr->devMagic ))
    {
        return(ETHERNET_ERR_INVALID_HANDLE);
    }
    regAddrPtr = (uint32_t *)(devicePtr->baseAddresses.enet_base +
                 ETHERNET_O_TX_OCTET_COUNT_GOOD_BAD);



    statAddrPtr = (uint32_t *)statisticsPtr;
    for (i = 0U; i < ETHERNET_NUMSTATS; i++)
    {
        statval = *regAddrPtr;
        *regAddrPtr = statval;
        regAddrPtr = regAddrPtr + 1U;
        statval += *statAddrPtr;
        *statAddrPtr = statval;
        statAddrPtr = statAddrPtr + 1U;
    }
    return(ETHERNET_RET_SUCCESS);

}
uint32_t Ethernet_getHandle(Ethernet_Handle handleApplication,
                Ethernet_InitConfig *ethernetInitConfigPtr,
                Ethernet_Handle *ethernetHandlePtr)
{

    uint32_t i;

    //
    //Do validation of inputs
    //
    if(0U == ethernetInitConfigPtr)
    {
        return(ETHERNET_ERR_INVALID_PARAM);
    }


    Ethernet_device_struct.descs =
                (Ethernet_HW_descriptor *)Ethernet_descArray;

    (void)memset(Ethernet_device_struct.descs, 0U,
        ETHERNET_DESCRIPTORS_NUM * sizeof(Ethernet_HW_descriptor));

    Ethernet_device_struct.txDesc = Ethernet_device_struct.descs;

    Ethernet_device_struct.rxDesc =
        &Ethernet_device_struct.descs [ETHERNET_DESCRIPTORS_NUM_TX];

    if(NULL!= ethernetInitConfigPtr->rxBuffer)
        Ethernet_device_struct.rxBuffer = ethernetInitConfigPtr->rxBuffer;

    Ethernet_setMACConfiguration(
         Ethernet_device_struct.baseAddresses.enet_base,
           ((((uint32_t)ethernetInitConfigPtr->linkMode <<
              ETHERNET_MAC_CONFIGURATION_DM_S)) |
           (((uint32_t)ethernetInitConfigPtr->loopbackMode <<
             ETHERNET_MAC_CONFIGURATION_LM_S)))
          );

    HWREG(Ethernet_device_struct.baseAddresses.enet_base +
          ETHERNET_O_DMA_SYSBUS_MODE ) |=
        ETHERNET_DMA_SYSBUS_MODE_FB;//Fixed Burst Length DMA

    /* This fixes the RX and TX DMA Channels to have the same Burst length
     Change here for different Burst Length experiments*/
        for(i = 0U;(i < ethernetInitConfigPtr->numChannels) &&
            (i < ETHERNET_MAX_NUM_DMA_CHANNELS);i++)
        {
         /*TBD Make all these per channel based
         InitConfig Structure inputs based*/
            (void)Ethernet_initTxChannel(
             &Ethernet_device_struct.initConfig.chInfo[ETHERNET_CH_DIR_TX][i]);

            Ethernet_writeTxDescTailPointer(
                    Ethernet_device_struct.baseAddresses.enet_base,
                    i,
                    (&Ethernet_device_struct.txDesc [
                     (ETHERNET_DESCRIPTORS_NUM_TX_PER_CHANNEL * i  ) + 1U]));

            (void)Ethernet_initRxChannel(
            &Ethernet_device_struct.initConfig.chInfo[ETHERNET_CH_DIR_RX][i]);

            Ethernet_writeRxDescTailPointer(
                Ethernet_device_struct.baseAddresses.enet_base,
                i,
                (&Ethernet_device_struct.rxDesc[
                 ((uint32_t)ETHERNET_DESCRIPTORS_NUM_RX_PER_CHANNEL) *
                  (i + (uint32_t)1U)]));

            Ethernet_enableDmaInterrupt(
                               Ethernet_device_struct.baseAddresses.enet_base,
                                i,
                               (ETHERNET_DMA_CH0_INTERRUPT_ENABLE_NIE |
                                ETHERNET_DMA_CH0_INTERRUPT_ENABLE_AIE |
                                ETHERNET_DMA_CH0_INTERRUPT_ENABLE_RBUE |
                                ETHERNET_DMA_CH0_INTERRUPT_ENABLE_TBUE |
                                ETHERNET_DMA_CH0_INTERRUPT_ENABLE_TIE |
                                ETHERNET_DMA_CH0_INTERRUPT_ENABLE_RIE));
         }
    Ethernet_setMTLOpmode(Ethernet_device_struct.baseAddresses.enet_base,
                         ethernetInitConfigPtr->txSchedulingAlgoritm ,
                         ethernetInitConfigPtr->receiveArbitrationAlgorithm
                         );
    Ethernet_setDMAMode(Ethernet_device_struct.baseAddresses.enet_base,
                        ethernetInitConfigPtr->dmaMode);
    //
    //Configure the MAC Address
    //

    Ethernet_setMACAddr(Ethernet_device_struct.baseAddresses.enet_base,
                                0U,
                                0x00000506U,
                                0x01020304U,
                                ETHERNET_CHANNEL_0);

    Ethernet_device_struct.pktMTU = ethernetInitConfigPtr->pktMTU;
    Ethernet_setMACConfiguration(
        Ethernet_device_struct.baseAddresses.enet_base,
        (((uint32_t)(ethernetInitConfigPtr->linkMode <<
         (uint32_t) ETHERNET_MAC_CONFIGURATION_DM_S)) |
         ((uint32_t)(ethernetInitConfigPtr->loopbackMode <<
          (uint32_t)ETHERNET_MAC_CONFIGURATION_LM_S)))
        );
     Ethernet_setMACConfiguration(
        Ethernet_device_struct.baseAddresses.enet_base,
        ETHERNET_MAC_CONFIGURATION_TE);
    //
    //MAC Filter configuration
    //
    Ethernet_setMACPacketFilter(Ethernet_device_struct.baseAddresses.enet_base,
                                *(uint32_t *)&ethernetInitConfigPtr->macFilterConfig);
    //
    //MDIO Configurations
    //
    Ethernet_configureMDIO(Ethernet_device_struct.baseAddresses.enet_base,
                            1U, 0U, 0U);
    Ethernet_configurePHYAddress(Ethernet_device_struct.baseAddresses.enet_base,
                                  0U);
    Ethernet_device_struct.devMagic = ETHERNET_DRV_DEVMAGIC;
    *ethernetHandlePtr = &Ethernet_device_struct;
    return(ETHERNET_RET_SUCCESS);
}

uint32_t Ethernet_setConfig(Ethernet_Handle hEMAC,
            Ethernet_SetConfigParam setParam,
            void *buffPtr,
            uint32_t size)
{
    Ethernet_VlanConfig *vlanConfig;
    Ethernet_DoubleVLANConfig *dvlanConfig;

    Ethernet_VLAN_Perfect_FilterParams *vlanPerfectParams;
    Ethernet_Vlan_Hash_FilterParams *vLanHashFilterParams;
    Ethernet_L3_L4_FilterParams *l3l4FilterParams;
    Ethernet_VLANCBTIConfig *vlanCBTIConfig;


    Ethernet_EEE_Tx_Params *eeeTxControl;
    Ethernet_RemoteWakeUp_Filter_Config *wakeupFilterConfig;
    uint32_t returnCode = ETHERNET_RET_SUCCESS;

    switch(setParam)
    {
        case ETHERNET_SET_CONFIG_VLAN_TX_OUTER:

            vlanConfig = (Ethernet_VlanConfig *)buffPtr;
            Ethernet_setFixedOuterVLANParams(
                Ethernet_device_struct.baseAddresses.enet_base,
                vlanConfig->vlan_tag,
                vlanConfig->vlanTagControl,
                vlanConfig->vlanType);
            break;
        case ETHERNET_SET_CONFIG_VLAN_TX_INNER:
             vlanConfig = (Ethernet_VlanConfig *)buffPtr;
            Ethernet_setFixedInnerVLANParams(
                Ethernet_device_struct.baseAddresses.enet_base,
                vlanConfig->vlan_tag,
                vlanConfig->vlanTagControl,
                vlanConfig->vlanType);
            break;
        case ETHERNET_SET_CONFIG_VLAN_TX_DOUBLE_VLAN:

             dvlanConfig =  (Ethernet_DoubleVLANConfig *)buffPtr;
            //
            //Configure Outer VLAN Parameters
            //
            Ethernet_setFixedOuterVLANParams(
                Ethernet_device_struct.baseAddresses.enet_base,
                dvlanConfig->outerVLANConfig.vlan_tag,
                dvlanConfig->outerVLANConfig.vlanTagControl,
                dvlanConfig->outerVLANConfig.vlanType);

            //
            //Configure Inner VLAN Parameters
            //
            Ethernet_setFixedInnerVLANParams(
                Ethernet_device_struct.baseAddresses.enet_base,
                dvlanConfig->innerVLANConfig.vlan_tag,
                dvlanConfig->innerVLANConfig.vlanTagControl,
                dvlanConfig->innerVLANConfig.vlanType);
            //
            //Set the Dual VLAN mode and also the Inner VLAN
            //has to be enabled to make both tags work on Transmit path
            //
            Ethernet_setDualVLAN(
                Ethernet_device_struct.baseAddresses.enet_base);
            Ethernet_enableInnerVLAN(
                Ethernet_device_struct.baseAddresses.enet_base);
            break;
        case ETHERNET_SET_CONFIG_FILTER_VLAN_PERFECT:
            vlanPerfectParams = (Ethernet_VLAN_Perfect_FilterParams *)buffPtr;
            Ethernet_setVLANPerfectFilter(
                        Ethernet_device_struct.baseAddresses.enet_base,
                      vlanPerfectParams->filterid,
                      vlanPerfectParams->vlanid,
                      vlanPerfectParams->vlanEnableDisable,
                      vlanPerfectParams->vlanFilterMode,
                      vlanPerfectParams->vlanPerfectTypeComparisonDisable,
                      vlanPerfectParams->vlanType,
                      vlanPerfectParams->innerVLANEnabled,
                      vlanPerfectParams->dmaChannelEnable,
                      vlanPerfectParams->dmaChannelNum);
            //
            //Enable VLAN Tag Filtering
            //
            Ethernet_setMACPacketFilter(
                    Ethernet_device_struct.baseAddresses.enet_base,
                    ETHERNET_MAC_PACKET_FILTER_VTFE
                    );
            break;
        case ETHERNET_SET_CONFIG_FILTER_VLAN_HASH:
            vLanHashFilterParams = (Ethernet_Vlan_Hash_FilterParams *)buffPtr;
            Ethernet_setVLANHashFilter(
                    Ethernet_device_struct.baseAddresses.enet_base,
                    vLanHashFilterParams->innerVLANEnabled,
                    vLanHashFilterParams->hashFilterMap);
            //
            //Enable VLAN Tag Filtering
            //
            Ethernet_setMACPacketFilter(
                    Ethernet_device_struct.baseAddresses.enet_base,
                    ETHERNET_MAC_PACKET_FILTER_VTFE
                    );
            break;
        case ETHERNET_SET_CONFIG_VLAN_TX_PACKET_BASED:
            Ethernet_setVlanTagInclusionFromDescriptor(
                    Ethernet_device_struct.baseAddresses.enet_base);
            break;
        case ETHERNET_SET_CONFIG_VLAN_INNER_TX_PACKET_BASED:
            Ethernet_setInnerVlanTagInclusionFromDescriptor(
                    Ethernet_device_struct.baseAddresses.enet_base);
            //
            //Set the Dual VLAN mode and also the Inner VLAN
            //has to be enabled to make both tags work on Transmit path
            //
            Ethernet_setDualVLAN(
                Ethernet_device_struct.baseAddresses.enet_base);
            break;
        case ETHERNET_SET_CONFIG_DOUBLE_VLAN:
            //
            //Set the Dual VLAN mode and also the Inner VLAN
            //has to be enabled to make both tags work on Transmit and
            //Receive path
            //
            Ethernet_setDualVLAN(
                Ethernet_device_struct.baseAddresses.enet_base);
            Ethernet_enableInnerVLAN(
                Ethernet_device_struct.baseAddresses.enet_base);
            break;
        case ETHERNET_SET_CONFIG_VLAN_TX_CHANNEL_BASED:
            vlanCBTIConfig = (Ethernet_VLANCBTIConfig *)buffPtr;
             Ethernet_configureVLANCBTI(
                            Ethernet_device_struct.baseAddresses.enet_base,
                            vlanCBTIConfig->channelNum,
                            vlanCBTIConfig->vlan_tag,
                            vlanCBTIConfig->vlanType
                            );
            break;
        case ETHERNET_SET_CONFIG_FILTER_L3_L4:
            l3l4FilterParams = (Ethernet_L3_L4_FilterParams *)buffPtr;
            (void)Ethernet_configureL3L4Filter(
                Ethernet_device_struct.baseAddresses.enet_base,
                *l3l4FilterParams);
            break;


       case ETHERNET_SET_CONFIG_EEE_TX:
          eeeTxControl = (Ethernet_EEE_Tx_Params *) buffPtr;
          if(ETHERNET_EEE_TX_CONTROL_LST_VALID ==
            (eeeTxControl->flags & ETHERNET_EEE_TX_CONTROL_LST_VALID))
            {
              (void)Ethernet_configureLPILSTimer(
                Ethernet_device_struct.baseAddresses.enet_base,
                     eeeTxControl->linkStatusTimer);
            }
          if(ETHERNET_EEE_TX_CONTROL_TWT_VALID ==
              (eeeTxControl->flags & ETHERNET_EEE_TX_CONTROL_TWT_VALID))
            {
                (void)Ethernet_configureLPITWTimer(
                    Ethernet_device_struct.baseAddresses.enet_base,
                    eeeTxControl->transitionWaitTimer);
            }
          if(ETHERNET_EEE_TX_CONTROL_PLS_VALID ==
              (eeeTxControl->flags & ETHERNET_EEE_TX_CONTROL_PLS_VALID))
            {
                if(ETHERNET_EEE_TX_CONTROL_PLS_UP ==
                    (eeeTxControl->flags & ETHERNET_EEE_TX_CONTROL_PLS_UP))
                {
                    (void)Ethernet_configureLPIPhyLinkStatus(
                                Ethernet_device_struct.baseAddresses.enet_base,
                                true
                                );
                }
                else
                {
                    (void)Ethernet_configureLPIPhyLinkStatus(
                            Ethernet_device_struct.baseAddresses.enet_base,
                            false
                            );
                }
            }
          if(ETHERNET_EEE_TX_CONTROL_LET_VALID ==
            (eeeTxControl->flags & ETHERNET_EEE_TX_CONTROL_LET_VALID))
            {
                Ethernet_configureTxLpiEntryTimer(
                        Ethernet_device_struct.baseAddresses.enet_base,
                        eeeTxControl->entryTimer
                        );
            }
          if(ETHERNET_EEE_TX_CONTROL_AUTOEEE_ENABLED ==
            (eeeTxControl->flags & ETHERNET_EEE_TX_CONTROL_AUTOEEE_ENABLED))
            {
                Ethernet_configureTxEEEAutomaticMode(
                    Ethernet_device_struct.baseAddresses.enet_base);
            }
          if(ETHERNET_EEE_TX_CONTROL_TMICRO_VALID ==
            (eeeTxControl->flags & ETHERNET_EEE_TX_CONTROL_TMICRO_VALID))
            {
                Ethernet_configureEEETicCounter(
                                Ethernet_device_struct.baseAddresses.enet_base,
                                eeeTxControl->tickOneMicroSecCounter);
            }
          if(ETHERNET_EEE_TX_CONTROL_TXCLKGATE_ENABLED ==
             (eeeTxControl->flags & ETHERNET_EEE_TX_CONTROL_TXCLKGATE_ENABLED))
            {
                //
                //Enable Automatic Tx Clock Gating
                //
                Ethernet_configureEEEClockGatingControl(
                            Ethernet_device_struct.baseAddresses.enet_base,
                            true);
            }
            //
            //Configure the interrupts at MAC Level
            //These interrupts shall result in Generic (SBD) interrupt
            //if they are asserted, Combined at SoC Level
            //PMT Interrupt when Magic Packet is received
            //LPI Interrupt is asserted when entry/exit from Tx and Rx
            //LPI States are detected hence enabling both here
            //
            Ethernet_enableMACInterrupt(
                Ethernet_device_struct.baseAddresses.enet_base,
                          (ETHERNET_MAC_INTERRUPT_ENABLE_LPIIE |
                          ETHERNET_MAC_INTERRUPT_ENABLE_PMTIE));
        //
        //TBD TX and RX Interrupt handling code
        //TBD Wake on LAN
        //TBD Magic packet detection
        //
            break;
        case ETHERNET_SET_CONFIG_EEE_TX_ENABLE:
            (void)Ethernet_enableTxEEEMode(
                Ethernet_device_struct.baseAddresses.enet_base);
            break;
        case ETHERNET_SET_CONFIG_EEE_TX_DISABLE:
            (void)Ethernet_disableTxEEEMode(
                Ethernet_device_struct.baseAddresses.enet_base);
             break;
        case ETHERNET_SET_CONFIG_RX_MAGIC_DETECT_ENABLE:
            (void)Ethernet_enableEEEMagicPacketDetection(
                        Ethernet_device_struct.baseAddresses.enet_base);
            break;
        case ETHERNET_SET_CONFIG_RX_REMOTE_WAKEUP_FILTER:
            wakeupFilterConfig =
              (Ethernet_RemoteWakeUp_Filter_Config *) buffPtr;
            uint32_t remoteFilter[ETHERNET_RWKUP_FILTER_NUM_WORDS];
            uint32_t i;
            for(i = 0;i < ETHERNET_RWKUP_FILTER_NUM_WORDS;i++)
                remoteFilter[i] = 0;
           //
          //All the filter settings must be written one after another as per
          //specified format
          //Refer TRM for details
          //
            if(ETHERNET_RWKUP_FILTER_CONFIG0_ENABLED ==
                (wakeupFilterConfig->flags &
                 ETHERNET_RWKUP_FILTER_CONFIG0_ENABLED))
            {
                remoteFilter[0] = wakeupFilterConfig->filterByteMask0;
                remoteFilter[4] = wakeupFilterConfig->filterCommand0;
                remoteFilter[5] = wakeupFilterConfig->filterOffset0;
                remoteFilter[6] = wakeupFilterConfig->filterCRC0;
            }
           if(ETHERNET_RWKUP_FILTER_CONFIG1_ENABLED ==
              (wakeupFilterConfig->flags &
               ETHERNET_RWKUP_FILTER_CONFIG1_ENABLED))
            {
                remoteFilter[1] =
                    wakeupFilterConfig->filterByteMask1;
                remoteFilter[4] |=
                    ((uint32_t)(wakeupFilterConfig->filterCommand1<<  8U));
                remoteFilter[5] |=
                    ((uint32_t)(wakeupFilterConfig->filterOffset1 << 8U));
                remoteFilter[6] |=
                    ((uint32_t)(wakeupFilterConfig->filterCRC1 << 16U));
            }
           if(ETHERNET_RWKUP_FILTER_CONFIG2_ENABLED ==
              (wakeupFilterConfig->flags &
               ETHERNET_RWKUP_FILTER_CONFIG2_ENABLED))
            {
                remoteFilter[2] = wakeupFilterConfig->filterByteMask2;
                remoteFilter[4] |=
                    ((uint32_t)(wakeupFilterConfig->filterCommand2 << 16U));
                remoteFilter[5] |=
                    ((uint32_t)(wakeupFilterConfig->filterOffset2 << 16U));
                remoteFilter[7] |= ((uint32_t)(wakeupFilterConfig->filterCRC2));
            }
           if(ETHERNET_RWKUP_FILTER_CONFIG3_ENABLED ==
              (wakeupFilterConfig->flags &
               ETHERNET_RWKUP_FILTER_CONFIG3_ENABLED))
            {
                remoteFilter[3] = wakeupFilterConfig->filterByteMask3;
                remoteFilter[4] |=
                    ((uint32_t)(wakeupFilterConfig->filterCommand3<<  24U));
                remoteFilter[5] |=
                    ((uint32_t)(wakeupFilterConfig->filterOffset3 << 24U));
                remoteFilter[7] |=
                    ((uint32_t)(wakeupFilterConfig->filterCRC3 << 16U));
            }
            Ethernet_configureRemoteWakeupFilter(
                            Ethernet_device_struct.baseAddresses.enet_base,
                            remoteFilter);
            break;
        case ETHERNET_SET_CONFIG_RX_REMOTE_WAKEUP_ENABLE:
            Ethernet_enableRemoteWakeup(
                Ethernet_device_struct.baseAddresses.enet_base);
            //
            //Enabling MAC interrupt to enable it to be handled in
            //Generic SBD Interrupt
            //
             Ethernet_enableMACInterrupt(
                        Ethernet_device_struct.baseAddresses.enet_base,
                          (ETHERNET_MAC_INTERRUPT_ENABLE_LPIIE |
                          ETHERNET_MAC_INTERRUPT_ENABLE_PMTIE));
            break;

        default:
            //
            //Default case
            //
            break;
    }
    return(returnCode);
}

/*
 * TODO: This api is only configuring the PTP related stuff and that too very
 * blatantly. Need to refine this api to call apt sub-routines.
 * Still to be implemented
 */
uint32_t Ethernet_configurePTP(Ethernet_Handle hEMAC)
{
    return(0);
}

void Ethernet_clearHandle(Ethernet_Handle *phEMAC)
{
//
//Disable Tx and Rx DMA
//Turn off the Tx and RX
//Deregister the ISR
//
}
void Ethernet_clearStatistics(Ethernet_Handle *ethernetHandlePtr)
{
}

void Ethernet_addPacketsIntoTxQueue(Ethernet_DescCh *channelDescPtr)
{
    Ethernet_HW_descriptor      *descPtr;
    Ethernet_Pkt_Desc      *pktPtr;
    uint32_t          numPktFrags;

    //
    //descWrite is in initialized to 0xffffffff to indicate 1st time
    //tx enqueue, starting point
    //
    if(0xffffffffU == channelDescPtr->indexWrite)
    {
        channelDescPtr->indexWrite = channelDescPtr->indexFirst;
    }
    //
    //Disable the interrupts when operating on Queue
    //Sometimes the reentrant call from ISR and main thread
    //results in stale pointer getting operated on
    //Hence disabling interrupts for operating on Critical
    //Queue Data structure
    //
    if(NULL!= Ethernet_device_struct.ptrPlatformInterruptDisable)
    {
        (*Ethernet_device_struct.ptrPlatformInterruptDisable)(
            Ethernet_device_struct.interruptNum[ETHERNET_TX_INTR_CH0 +
            channelDescPtr->chInfo->chNum]);
    }

    //
    //Try to post any waiting packets
    //
    while(0U != channelDescPtr->waitQueue.count)
    {
        //
        //See if we have enough room for a new packet
        //
        pktPtr = channelDescPtr->waitQueue.head;
        if(0U == pktPtr)
        {
            return;
        }
        else
        {
            numPktFrags = pktPtr->numPktFrags;
        }

        /* If we don't have room, break out */
        if((numPktFrags + channelDescPtr->descQueue.count) >
         channelDescPtr->descMax)
        {
            break;
        }
        descPtr =
                &channelDescPtr->descFirst[channelDescPtr->indexWrite];
        if((descPtr->des3 & ETHERNET_DESC_OWNER) != 0U)
        {
            //
            //The descriptor is still queued on hardware hence we should not
            //overwrite
            //
            break;
        }

        /* The next packet will fit, post it. */
        while(0U != numPktFrags)
        {
            /* Pop the next frag off the wait queue */
            pktPtr = Ethernet_performPopOnPacketQueue(
                        &channelDescPtr->waitQueue);

            /* If its a null packet do not proceed further. */
            if(0x0U == pktPtr)
                    return;


            /*
             *  Check if Context descriptor is needed.
             */
            if(ETHERNET_PKT_EXTENDED_FLAG_CTXT ==
                  (pktPtr->extendedFlags & ETHERNET_PKT_EXTENDED_FLAG_CTXT))
            {
               /* Get a descriptor from the queue. */

                /* Assign the pointer to "this" desc */
                descPtr =
                &channelDescPtr->descFirst[channelDescPtr->indexWrite];


                /* Move the write pointer and bump count
                 * Since buffer is a ring, we can use modular arithmetic to
                 * update the buffer's write index.
                 */
                channelDescPtr->indexWrite =
                    (channelDescPtr->indexWrite + 1U) %
                     channelDescPtr->descMax;

                /*
                 * Program the context descriptor
                 * Todo: Currently hardcoding for One-step Timestamping. Need
                 * to make it generic for VLAN Tagging and MSS for TSO
                 */

                /*
                 *          Transmit Context Descriptor for dummies
                 *
                 *       |--------------------------------------------------|
                 * TDES0 |              Timestamp Low [31:0]                |
                 *       |--------------------------------------------------|
                 * TDES1 |              Timestamp Low [31:0]                |
                 *       |--------------------------------------------------|
                 *       |          31:16            | 15:14 |         13:0 |
                 * TDES2 |     Inner VLAN Tag        |  Rsvd | Max Seg Size|
                 *|-----------------------------------------------------------|
                 *TDES3 | 31 | 30 |29:28| 27 |  26|25:24|23 |22:18|17|16|15:0|
                 *| OWN|CTXT|Rsvd |OSTC|TCMSSV| Rsvd|CDE|Rsvd |IVLTV|VLTV| VT |
                 *|---------------------------------------------------------|*
                 *
                 * Note : The Transmit Context descriptor can be provided any
                 * time before a packet descriptor. The context is valid
                 * for the current packet and subsequent packets.
                 * TODO: Add description how context descriptor's context ends.
                 */

                /*
                 * If the context descriptor is to be programmed for
                 * One-Step Timestamp Corrections.
                 */
                if(ETHERNET_PKT_EXTENDED_FLAG_OST ==
                     (pktPtr->extendedFlags & ETHERNET_PKT_EXTENDED_FLAG_OST))
                {
                    /*
                     * If it is sync packet, get current time for
                     * originTimestamp field
                     * Todo: Figure out other packet scenarios here.
                     */

                    /*
                     * Check if the timestamp is provided by the application.
                     * TODO: This needed for end-to-end transparent clocks or
                     *      for PDelay_Resp messages. This support needs to be
                     *      added and tested
                     *
                     */

                    if(pktPtr->timeStampLow || pktPtr->timeStampHigh)
                    {
                        //
                        //TDES0
                        //
                        descPtr->des0  = pktPtr->timeStampLow;

                        //
                        //TDES1
                        //
                        descPtr->des1  = pktPtr->timeStampHigh;

                    }


                    //
                    //TDES2
                    //Todo :
                    //This value will actually be used for VLAN tagging and
                    //MSS for TCP Segmentation
                    //Programming dummy value for now
                    //
                                         descPtr->des2  = 0x00000000;

                    //
                    //TDES3
                    //Both OSTC (TDES3[27]) and TCMSSV (TDES3[26])
                    //bit need to be
                    //set to indicate to the hardware that timestamp correction
                    //input provided in TDES0 and TDES1 are valid
                    //
                    descPtr->des3  = ETHERNET_DESC_OWNER |
                                     ETHERNET_PKT_EXTENDED_FLAG_CTXT |
                                     ETHERNET_PKT_EXTENDED_FLAG_OSTC |
                                     ETHERNET_PKT_EXTENDED_FLAG_TCMSSV;
                }

                //
                //If the context descriptor is to be programmed for
                //Max. Segment Size need for TCP segmentation offload
                //
                if(ETHERNET_PKT_EXTENDED_FLAG_TSO ==
                      (pktPtr->extendedFlags & ETHERNET_PKT_EXTENDED_FLAG_TSO))
                {

                }
                //
                //If the context descriptor is to be programmed for
                //VLAN related items
                //
                if(ETHERNET_PKT_EXTENDED_FLAG_VLTV ==
                     (pktPtr->extendedFlags & ETHERNET_PKT_EXTENDED_FLAG_VLTV))
                {
                    //
                    //Set the VLAN Tag Valid of Des3 of Transmit
                    //Context Descriptor
                    //
                    descPtr->des3 |= ETHERNET_PKT_EXTENDED_FLAG_VLTV;
                    //
                    //Set the VLAN Tag value from incoming Packet Descriptor
                    //into the Hardware Descriptor
                    //
                    descPtr->des3 |=
                            ((uint16_t) pktPtr->vlanTag |
                              ETHERNET_DESC_OWNER |
                              ETHERNET_PKT_EXTENDED_FLAG_CTXT);
                    //
                    //Check for inner VLAN tag and fill it if provided
                    //
                    if(ETHERNET_PKT_EXTENDED_FLAG_IVLTV ==
                       (pktPtr->extendedFlags &
                        ETHERNET_PKT_EXTENDED_FLAG_IVLTV))
                    {

                        descPtr->des3 |= ETHERNET_PKT_EXTENDED_FLAG_IVLTV;
                        //
                        //Set wheter the inner VLAN Tag should be inserted
                        //Stripped off/replaced. Taken from incoming packet
                        //descriptor
                        //
                        descPtr->des3 |=
                            ((pktPtr->extendedFlags &
                              ETHERNET_PKT_EXTENDED_FLAG_VTIR_M) |
                             (pktPtr->extendedFlags &
                              ETHERNET_PKT_EXTENDED_FLAG_IVTIR_S));
                        //
                        //Program the inner VLAN Tag in Des 2
                        //
                        descPtr->des2 |=
                            (pktPtr ->innerVlanTag <<
                             ETHERNET_TX_CTXT_DESC_IVLAN_TAG_S);
                    }
                }
            }

            //
            // Normal descriptor related code follows
            //

            //
            //Assign the pointer to this desc
            //
            descPtr = &channelDescPtr->descFirst[channelDescPtr->indexWrite];
            //
            //Move the write pointer and bump count
            //
            if(channelDescPtr->indexWrite == channelDescPtr->indexLast)
            {
                channelDescPtr->indexWrite = channelDescPtr->indexFirst;
            }
            else
            {
                channelDescPtr->indexWrite = channelDescPtr->indexWrite + 1U;
            }
            if(ETHERNET_PKT_FLAG_TSE == (pktPtr->flags &
                ETHERNET_PKT_FLAG_TSE))
            {

                descPtr->des0  =
                (uint32_t)(&pktPtr->dataBuffer [pktPtr->dataOffset]);
                //
                //IOC Set for interrupt completion which is needed for
                //Dequeueing the packet
                //


                descPtr->des1 = (uint32_t)(pktPtr->dataBuffer2);
                //
                //Set the header length in Buffer 1
                //
                descPtr->des2 =
                pktPtr->validLength |
                ETHERNET_TX_DESC_IOC |
                ETHERNET_TX_DESC_TTSE;
                //
                //Set the Payload length in Buffer 2
                //
                descPtr->des2  |= pktPtr->buffer2Length <<
                        ETHERNET_TX_DESC_BUF2LENGTH_S;


                if(ETHERNET_PKT_FLAG_SOP ==
                    (pktPtr->flags & ETHERNET_PKT_FLAG_SOP))
                {
                    descPtr->des3 =
                      ((pktPtr->flags &
                        (ETHERNET_PKT_FLAG_SOP | ETHERNET_PKT_FLAG_EOP)) |
                      pktPtr->pktLength |
                      ETHERNET_DESC_OWNER |
                      (((pktPtr->flags & ETHERNET_PKT_FLAG_SAIC) >>
                        ETHERNET_PKT_FLAG_SAIC_S) <<
                       ETHERNET_TX_DESC_SAIC_S) |
                      (((pktPtr->flags & ETHERNET_PKT_FLAG_CPC) >>
                       ETHERNET_PKT_FLAG_CPC_S) << ETHERNET_TX_DESC_CPC_S) |
                      (pktPtr->flags & ETHERNET_PKT_FLAG_CIC) |
                      ETHERNET_TX_DESC_TSE_ENABLE
                      );

                }
                else
                {
                    descPtr->des3 = (pktPtr->flags & ETHERNET_PKT_FLAG_EOP) |
                                    ETHERNET_DESC_OWNER;
                }
            }
            else
            {


                descPtr->des0  =
                (uint32_t)(&pktPtr->dataBuffer [pktPtr->dataOffset]);
                //
                //IOC Set for interrupt completion which is needed for
                //Dequeueing the packet
                //
                descPtr->des2 =
                        pktPtr->validLength | ETHERNET_TX_DESC_IOC;

                if(ETHERNET_PKT_FLAG_SOP ==
                   (pktPtr->flags & ETHERNET_PKT_FLAG_SOP))
                 {
                    //
                    // Notify the DMA that transmit timestamp needs to be
                    // captured for this packet. The DMA will capture the
                    // timestamp if "TTSE" bit is set in the first descr-
                    // iptor of the packet.
                    //
                    descPtr->des2 |= pktPtr->flags &
                                     ETHERNET_PKT_FLAG_TTSE;

                    descPtr->des3 = ((pktPtr->flags &
                                     (ETHERNET_PKT_FLAG_SOP |
                                      ETHERNET_PKT_FLAG_EOP)) |
                                     pktPtr->pktLength |
                                     ETHERNET_DESC_OWNER |
                                     (((pktPtr->flags &
                                        ETHERNET_PKT_FLAG_SAIC) >>
                                       ETHERNET_PKT_FLAG_SAIC_S) <<
                                      ETHERNET_TX_DESC_SAIC_S) |
                                     (((pktPtr->flags &
                                        ETHERNET_PKT_FLAG_CPC) >>
                                       ETHERNET_PKT_FLAG_CPC_S) <<
                                      ETHERNET_TX_DESC_CPC_S) |
                                     (pktPtr->flags & ETHERNET_PKT_FLAG_CIC));

                }
                else
                {
                    descPtr->des3 =
                            (pktPtr->flags & ETHERNET_PKT_FLAG_EOP) |
                            ETHERNET_DESC_OWNER;
                 }
                //
                //Check if VLAN Tag is passed in the packet descriptor
                //
                if(ETHERNET_PKT_EXTENDED_FLAG_VLTV ==
                    (pktPtr->extendedFlags &
                     ETHERNET_PKT_EXTENDED_FLAG_VLTV))
                {
                    //
                    //Transmit Descriptor DES2 VTIR configures
                    //Insert/Replace/Delete of VLAN Tags
                    //
                    descPtr->des2 |=
                            (((pktPtr->extendedFlags &
                               ETHERNET_PKT_EXTENDED_FLAG_VTIR_M) >>
                              ETHERNET_PKT_EXTENDED_FLAG_VTIR_S) <<
                             ETHERNET_TX_DESC_VTIR_S);
                }
            }
            Ethernet_performPushOnPacketQueue(&channelDescPtr->descQueue,
                                            pktPtr);
            numPktFrags--;

            channelDescPtr->dmaInProgress = 1U;
            HWREG(channelDescPtr->devicePtr->baseAddresses.enet_base +
                  ETHERNET_O_DMA_CH0_TX_CONTROL +
                  (ETHERNET_CHANNEL_OFFSET * channelDescPtr->chInfo->chNum)) |=
                ETHERNET_DMA_CH0_TX_CONTROL_ST;
            Ethernet_writeTxDescTailPointer(
                    channelDescPtr->devicePtr->baseAddresses.enet_base,
                    channelDescPtr->chInfo->chNum,
                    (Ethernet_HW_descriptor *)(&descPtr[1U] ));
        }
    }
    //
    //At the end of Critical section where this function might
    //reenter with ISR enabling the interrupts
    //

    if(NULL!= Ethernet_device_struct.ptrPlatformInterruptEnable)
    {
        (*Ethernet_device_struct.ptrPlatformInterruptEnable)(
            Ethernet_device_struct.interruptNum[ETHERNET_TX_INTR_CH0 +
            channelDescPtr->chInfo->chNum]);
    }
}



void Ethernet_removePacketsFromTxQueue
                                    (Ethernet_DescCh *channelDescPtr,
                                    Ethernet_CompletionMode earlyFlag)
{
    Ethernet_Pkt_Desc *pktPtr = NULL;
    Ethernet_HW_descriptor *descRead, *newDescRead;

    //
    //we now own the packet meaning its been transferred to the port
    //
    pktPtr = Ethernet_performPopOnPacketQueue(&channelDescPtr->descQueue);
    if(0U != pktPtr)
    {
        pktPtr->flags |= ETHERNET_INTERRUPT_FLAG_TRANSMIT;
        if(ETHERNET_COMPLETION_EARLY == earlyFlag )
        {
            pktPtr->flags = ETHERNET_INTERRUPT_FLAG_EARLY;
        }

        descRead = &channelDescPtr->descFirst[channelDescPtr->indexRead];
        //
        //   Timestamp is not written back on context descriptors, so skip
        //until we have a non-context transmit descriptor
        //
        while((descRead->des3 & ETHERNET_PKT_EXTENDED_FLAG_CTXT) != 0)
        {
            channelDescPtr->indexRead = (channelDescPtr->indexRead + 1U) %
                                        channelDescPtr->descMax;
            descRead = &channelDescPtr->descFirst[channelDescPtr->indexRead];
        }
        newDescRead = descRead;

        do {
            //
            // Capture the timestamp if "last descriptor" and "timestamp
            // captured" bit is set in the descriptor.
            //
            if((ETHERNET_TX_DESC_LAST_DESC ==
                (descRead->des3 & ETHERNET_TX_DESC_LAST_DESC)) &&
               (ETHERNET_TX_DESC_TTSS ==
                (descRead->des3 & ETHERNET_TX_DESC_TTSS)))
            {
                pktPtr->timeStampLow = descRead->des0;
                pktPtr->timeStampHigh = descRead->des1;
            }

            //
            // Save the descriptor which will be checked for condition
            // "whether this is the last sengment of the packet" at the
            // end of this do while loop.
            //
            descRead = newDescRead;
            (void)((channelDescPtr->devicePtr->initConfig.pfcbFreePacket)
                   (channelDescPtr->devicePtr->handleApplication[0U],
                    pktPtr));
            channelDescPtr->descCount--;
            if(channelDescPtr->indexRead == channelDescPtr->indexLast)
            {
              channelDescPtr->indexRead = channelDescPtr->indexFirst;
            }
            else
            {
              channelDescPtr->indexRead = channelDescPtr->indexRead + 1U ;
            }

            //
            // Fetch the nest descriptor from the descriptor array
            //
            newDescRead = &channelDescPtr->descFirst[channelDescPtr->indexRead];

            //
            //we now own the packet meaning its been transferred to the port
            //
            pktPtr = Ethernet_performPopOnPacketQueue(
                                                &channelDescPtr->descQueue);
            if(0U != pktPtr)
            {
                pktPtr->flags |= ETHERNET_INTERRUPT_FLAG_TRANSMIT;
                if(ETHERNET_COMPLETION_EARLY == earlyFlag )
                {
                    pktPtr->flags = ETHERNET_INTERRUPT_FLAG_EARLY;
                }
            }
        //
        // Need to clear the desc array for all the packets until
        // the last packet segment is encountered, so repeat.
        //
       }while(ETHERNET_TX_DESC_LAST_DESC !=
               (descRead->des3 & ETHERNET_TX_DESC_LAST_DESC));
    }

    channelDescPtr->dmaInProgress = 0U;
    //
    //Try to post any waiting TX packets
    //
    if((0U != channelDescPtr->waitQueue.count) &&
        (channelDescPtr->dmaInProgress == 0U))
    {
        Ethernet_addPacketsIntoTxQueue(channelDescPtr);
    }
}
void Ethernet_addPacketsIntoRxQueue(Ethernet_DescCh *channelDescPtr)
{
        Ethernet_Pkt_Desc           *pktPtr;
        Ethernet_HW_descriptor    *descPtr;
        //
        //Fill RX Packets Until Full
        //
        while(channelDescPtr->descCount < channelDescPtr->descMax)
        {
            //
            // Get a buffer from the application
            //
            pktPtr = (*Ethernet_device_struct.initConfig.pfcbGetPacket)();
            //
            // If no more buffers are available, break out of loop
            //
            if(0U == pktPtr)
            {
                break;
            }
            //
            //Fill in the descriptor for this buffer
            //
            descPtr = &channelDescPtr->descFirst[channelDescPtr->indexWrite];
            //
            // Move the write pointer and bump count
            //
            if(channelDescPtr->indexWrite == channelDescPtr->indexLast)
            {
                channelDescPtr->indexWrite = channelDescPtr->indexFirst;
            }
            else
            {
                channelDescPtr->indexWrite = channelDescPtr->indexWrite + 1U;
            }
            channelDescPtr->descCount++;
            //
            //Supply buffer pointer with application supplied offset
            //
            descPtr->des0 =
            (uint32_t)(&pktPtr->dataBuffer[ pktPtr->dataOffset]);
            descPtr->des1 = 0U; //We are not using 64 bit addresses
            descPtr->des2 = 0U;//Not using Buffer 2 Address
            descPtr->des3 = ETHERNET_DESC_OWNER | ETHERNET_RX_DESC_IOC |
                            ETHERNET_RX_DESC_BUF1_VALID;
            //
            //Push the packet buffer on the local descriptor queue
            //
            Ethernet_performPushOnPacketQueue(&channelDescPtr->descQueue,
                                              pktPtr);
        }

}

void Ethernet_removePacketsFromRxQueue(Ethernet_DescCh *channelDescPtr,
                                       Ethernet_CompletionMode earlyFlag)
{
    Ethernet_Pkt_Desc    *pktPtr = 0U;
    Ethernet_Pkt_Desc    *unusedPktPtr = 0U;
    Ethernet_Pkt_Desc    *newPktPtr = 0U;

    Ethernet_HW_descriptor   *descNewRxLastPtr=0U;


    uint32_t      PktFlgLen;
    uint8_t       contextTStampAvailable;
    Ethernet_HW_descriptor       *descRead;

    contextTStampAvailable = 0U;


    /*
     * Pop & Free Buffers 'till the last Descriptor
     * One thing we know for sure is that all the decriptors from
     * the read pointer to pDescAsk are linked to each other via
     * their pNext field
    */
    if(earlyFlag == ETHERNET_COMPLETION_EARLY)
        {
            pktPtr = Ethernet_returnTopOfPacketQueue(
                            &channelDescPtr->descQueue);

            ASSERT(NULL != pktPtr);
            pktPtr->bufferLength = channelDescPtr->chInfo->burstLength;
            pktPtr->pktChannel = channelDescPtr->chInfo->chNum;
            pktPtr->numPktFrags = Ethernet_getRxERICount(
                Ethernet_device_struct.baseAddresses.enet_base,
                channelDescPtr->chInfo->chNum);
            pktPtr->flags |= ETHERNET_INTERRUPT_FLAG_RECEIVE;
            if(earlyFlag == ETHERNET_COMPLETION_EARLY)
            {
                pktPtr->flags |= ETHERNET_INTERRUPT_FLAG_EARLY;
            }
                    /* Pass the packet to the application*/
            newPktPtr = (*Ethernet_device_struct.initConfig.pfcbRxPacket)
                          (channelDescPtr->devicePtr->handleApplication[0],
                           pktPtr);
        }
        else
         {
                descRead =
                    &channelDescPtr->descFirst[channelDescPtr->indexRead];
                /* Get the status of this descriptor*/
                PktFlgLen = descRead->des3;
                if(0U != (descRead->des1 &
                         (1U<< ETHERNET_RX_NORMAL_DESC_RDES1_TSA_LBIT_POS)))
                {
                    contextTStampAvailable = 1U;
                }
                /* Bit 16,17 and 18 indicate the port number(ingress)
                 * Passcrc bit is always set in the received packets
                 *Clear it before putting the
                 * packet in receive queue*/
                PktFlgLen = PktFlgLen & 0x0BFFFFFFU;

                /* Check the ownership of the packet*/
                if(0x0U == (PktFlgLen & ETHERNET_DESC_OWNER))
                {
                    /* Recover the buffer and free it*/
                    pktPtr = Ethernet_performPopOnPacketQueue(
                        &channelDescPtr->descQueue);
                    if(0U != pktPtr)
                    {
                        /* Fill in the necessary packet header fields*/
                        pktPtr->flags = PktFlgLen & 0xFFFF8000U;
                        //
                        //Payload Length is Least 14 bits in Receive Descriptor
                        //Writeback
                        //
                        pktPtr->pktLength = (PktFlgLen & 0x7FFFU);
                        pktPtr->validLength = pktPtr->pktLength;
                        pktPtr->pktChannel = channelDescPtr->chInfo->chNum;
                        pktPtr->numPktFrags = 1U;
                        pktPtr->flags |= ETHERNET_INTERRUPT_FLAG_RECEIVE;
                        pktPtr->flags &= ~ETHERNET_INTERRUPT_FLAG_EARLY;
                        if(earlyFlag == ETHERNET_COMPLETION_EARLY)
                        {
                            pktPtr->flags |= ETHERNET_INTERRUPT_FLAG_EARLY;
                        }
                        if(0U != contextTStampAvailable)
                        {
                            //
                            //Read the Next Descriptor to read the time stamp
                            // Move the read pointer and decrement count
                            //
                            if(channelDescPtr->indexRead ==
                                channelDescPtr->indexLast)
                            {
                                channelDescPtr->indexRead =
                                    channelDescPtr->indexFirst;
                            }
                            else
                            {
                                channelDescPtr->indexRead =
                                    channelDescPtr->indexRead + 1U;
                            }
                            channelDescPtr->descCount--;
                            descRead =
                                &channelDescPtr->descFirst[
                                channelDescPtr->indexRead];
                            if(0U != (descRead->des3 &
                                      (1U <<
                              ETHERNET_RX_CONTEXT_DESC_RDES3_CTXT_HBIT_POS)))
                              {
                                pktPtr->timeStampLow = descRead->des0;
                                pktPtr->timeStampHigh = descRead->des1;
                                pktPtr->nextBufferDiscarded = 1;
#ifdef ETHERNET_DEBUG
                                Ethernet_rxContextTimeStamp++;
#endif
                              }
                        }

                        /* Pass the packet to the application*/
                    newPktPtr =
                            (*Ethernet_device_struct.initConfig.pfcbRxPacket)
                            (channelDescPtr->devicePtr->handleApplication[0],
                            pktPtr);
                    /* Move the read pointer and decrement count*/
                        if(channelDescPtr->indexRead ==
                            channelDescPtr->indexLast)
                        {
                            channelDescPtr->indexRead =
                                channelDescPtr->indexFirst;
                        }
                        else
                        {
                            channelDescPtr->indexRead =
                                channelDescPtr->indexRead + 1U;
                        }
                        channelDescPtr->descCount--;
                    }
         }
      }
        /* See if we got a replacement packet*/
        if(0U != newPktPtr)
        {
            /* We know we can immediately queue this packet*/

            /* Fill in the descriptor for this buffer*/

            descNewRxLastPtr =
            &channelDescPtr->descFirst[channelDescPtr->indexWrite];

            /* Move the write pointer and bump count*/
            if( channelDescPtr->indexWrite == channelDescPtr->indexLast )
             {
                channelDescPtr->indexWrite = channelDescPtr->indexFirst;
              }
            else
            {
                channelDescPtr->indexWrite = channelDescPtr->indexWrite + 1U;
            }
            channelDescPtr->descCount++;

            /* Supply buffer pointer with application supplied offset*/
            descNewRxLastPtr->des0 =
             (uint32_t)(&newPktPtr->dataBuffer [newPktPtr->dataOffset]);
            descNewRxLastPtr->des1 = 0U;
            descNewRxLastPtr->des2 = 0U;
            descNewRxLastPtr->des3 = ETHERNET_DESC_OWNER
                                    | ETHERNET_RX_DESC_IOC
                                    | ETHERNET_RX_DESC_BUF1_VALID;

            /* Push the packet buffer on the local descriptor queue */
            Ethernet_performPushOnPacketQueue(&channelDescPtr->descQueue,
                                               newPktPtr);
        }
        else
            {
 #ifdef ETHERNET_DEBUG
                 Ethernet_rxReplacementFailedCount++;
 #endif
            }

        /*
         * Context Descriptor results in the loss of one packet descriptor and
         * it's corresponding buffer, so handle it here.
         */
        if(0 != contextTStampAvailable)
        {
            /*
             * This packet corresponding to the context descriptor is unused
             * but still needs to be discarded to maintain one-to-one mapping
             * between the "Packet Descriptor Queue" passed by the application
             * and the "DMA Hardware Ring".
             */
            unusedPktPtr = Ethernet_performPopOnPacketQueue(
                                                   &channelDescPtr->descQueue);

            /*
             * Get a replacement buffer from the application
             */
            unusedPktPtr = (*Ethernet_device_struct.initConfig.pfcbGetPacket)();

           /* Supply buffer pointer with application supplied offset */
            descNewRxLastPtr =
            &channelDescPtr->descFirst[channelDescPtr->indexWrite];


           descNewRxLastPtr->des0 =
               (uint32_t)(&unusedPktPtr->dataBuffer[unusedPktPtr->dataOffset]);
           descNewRxLastPtr->des1 = 0U;
           descNewRxLastPtr->des2 = 0U;
           descNewRxLastPtr->des3 = ETHERNET_DESC_OWNER
                                   | ETHERNET_RX_DESC_IOC
                                   | ETHERNET_RX_DESC_BUF1_VALID;

            /* Push the packet buffer again on
           the local descriptor queue*/
           Ethernet_performPushOnPacketQueue(
                   &channelDescPtr->descQueue,
                   unusedPktPtr);

           /* Move the write pointer and bump count*/
           if( channelDescPtr->indexWrite == channelDescPtr->indexLast )
           {
               channelDescPtr->indexWrite = channelDescPtr->indexFirst;
           }
           else
           {
               channelDescPtr->indexWrite = channelDescPtr->indexWrite + 1U;
           }
           channelDescPtr->descCount++;

        }
}
void Ethernet_shutdownInterface(void)
{
    uint32_t i = 0U;
    uint32_t processState = 0U;

    //
    //Shutting down receive DMA
    //
    for(i = 0U;i < Ethernet_device_struct.initConfig.numChannels;i++)
    {
        Ethernet_disableRxDMAReception(
              Ethernet_device_struct.baseAddresses.enet_base,
              i);

        do
        {
            //
            //This will work only for Channel 0,1,2 which is good
            //for F2838x. Beyond Channel 0,1,2, the bit fields will be
            //in different registers.RPS is offset by 8 bits for each channel
            //
            processState =
                ((HWREG(Ethernet_device_struct.baseAddresses.enet_base +
                        ETHERNET_O_DMA_DEBUG_STATUS0)) >>
                        (ETHERNET_DMA_DEBUG_STATUS0_RPS0_S +
                         (8U * i)) & 0xFU);

        //
        //Wait till the DMA is in suspended state or Waiting for receive
        //Packets
        //
        }while((processState != ETHERNET_DMA_DEBUG_STATUS0_RPS0_RUN_WRP) &&
               (processState != ETHERNET_DMA_DEBUG_STATUS0_RPS0_SUSPND) &&
               (processState != ETHERNET_DMA_DEBUG_STATUS0_RPS0_STOP));
    }

    //
    //Shutting down transmit DMA
    //
    for(i = 0U;i < Ethernet_device_struct.initConfig.numChannels;i++)
    {
        Ethernet_disableDMAChannelTransmit(
                Ethernet_device_struct.baseAddresses.enet_base,
                i);

        do
        {
            //
            //This will work only for Channel 0,1,2 which is good
            //for F2838x. Beyond Channel 0,1,2, the bit fields will be
            //in different registers.
            //Transmit Process State 0 and 1 are offset by 8 bits
            //
            processState = ((HWREG(
                                Ethernet_device_struct.baseAddresses.enet_base +
                                ETHERNET_O_DMA_DEBUG_STATUS0)) >>
                                (ETHERNET_DMA_DEBUG_STATUS0_TPS0_S + (8U *
                                   i)) & 0xFU);

        //
        //Wait till the DMA is in suspended state or Waiting for receive
        //Packets
        //
         }while((processState !=
                        ETHERNET_DMA_DEBUG_STATUS0_TPS0_STOP) &&
                        (processState !=
                        ETHERNET_DMA_DEBUG_STATUS0_TPS0_SUSPND));
    }

    //
    //Disable MAC Transmission and Reception
    //
    Ethernet_clearMACConfiguration(
            Ethernet_device_struct.baseAddresses.enet_base,
            (ETHERNET_MAC_CONFIGURATION_RE | ETHERNET_MAC_CONFIGURATION_TE));

    //
    //Clear the device structure handle
    //
    Ethernet_device_struct.devMagic = 0U;
}

/*These Routines are functions that touch the Ethernet Registers */
void Ethernet_resetModule(uint32_t base)
{
    //
    //DMA Initialization
    //
    HWREG(base + ETHERNET_O_DMA_MODE)  =  ETHERNET_DMA_MODE_SWR;
    //
    //Wait till the Soft Reset is done
    //
    while((HWREG(base + ETHERNET_O_DMA_MODE) &  ETHERNET_DMA_MODE_SWR) ==
        ETHERNET_DMA_MODE_SWR)
        {
        }
}
//**************************************************************************
//! Ethernet_setMTLTxQueueOpMode ()
//! This helper function is used to program the MTL_OPERATION_MODE
//! register
//! Arguments:
//! baseAddress - baseAddress of the Ethernet module
//! txSchedulingAlgoritm - Tx Scheduling Algorithm
//!     ETHERNET_MTL_OPERATON_MODE_SCHALG_WRR
//!     ETHERNET_MTL_OPERATON_MODE_SCHALG_WFQ
//!     ETHERNET_MTL_OPERATON_MODE_SCHALG_DWRR
//!     ETHERNET_MTL_OPERATON_MODE_SCHALG_STRICT_PRIORITY
//! rxAribtrationAlgorithm: Rx Arbitration Algorithm
//!     ETHERNET_MTL_OPERATION_MODE_RAA_SP
//!     ETHERNET_MTL_OPERATION_MODE_RAA_WSP
//************************************************************************

void Ethernet_setMTLOpmode(uint32_t base,
        uint32_t txSchedulingAlgoritm,
        uint32_t rxAribtrationAlgorithm)
{
        HWREG(base + ETHERNET_O_MTL_OPERATION_MODE) =
            ((txSchedulingAlgoritm << ETHERNET_MTL_OPERATION_MODE_SCHALG_S) |
             (rxAribtrationAlgorithm << ETHERNET_MTL_OPERATION_MODE_RAA_S));
}
void Ethernet_setMTLTxQueueOpMode(uint32_t base,
        uint32_t queueNum,
        uint32_t threshold_val,
        uint32_t queue_size, uint32_t storeForward)
{
    HWREG(base + (queueNum * ETHERNET_QUEUE_OFFSET) +
            ETHERNET_O_MTL_TXQ0_OPERATION_MODE) =
             (threshold_val << ETHERNET_MTL_TXQ0_OPERATION_MODE_TTC_S ) |
             (queue_size << ETHERNET_MTL_TXQ0_OPERATION_MODE_TQS_S ) |
             (storeForward << ETHERNET_MTL_TXQ0_OPERATION_MODE_TSF_S) |
             (ETHERNET_MTL_TXQ0_OPERATION_MODE_TXQ_ENABLED <<
             ETHERNET_MTL_TXQ0_OPERATION_MODE_TXQEN_S) ;
}

void Ethernet_setMTLRxQueueOpMode(
    uint32_t base,
    uint32_t queueNum,
    uint32_t threshold_val,
    uint32_t queue_size,
    uint32_t storeForward)
{
    HWREG(base + (queueNum * ETHERNET_QUEUE_OFFSET) +
          ETHERNET_O_MTL_RXQ0_OPERATION_MODE) =
     (threshold_val << ETHERNET_MTL_RXQ0_OPERATION_MODE_RTC_S) |
     (queue_size << ETHERNET_MTL_RXQ0_OPERATION_MODE_RQS_S ) |
     (storeForward << ETHERNET_MTL_RXQ0_OPERATION_MODE_RSF_S);

}

void Ethernet_setDMAMode(
    uint32_t base,
    Ethernet_DmaMode dmaMode)
{

    //
    // This is one-shot approach for the above solution
    //
    HWREG(base + ETHERNET_O_DMA_MODE ) = *((uint32_t *) (&dmaMode));
}
//
//Interrupt Enable related routines
//
void Ethernet_enableDmaInterrupt(
          uint32_t base,
        uint32_t channelNum,
        uint32_t flags)
{
    HWREG(base + (channelNum * ETHERNET_CHANNEL_OFFSET) +
          ETHERNET_O_DMA_CH0_INTERRUPT_ENABLE) |= flags;
}
void Ethernet_disableDmaInterrupt(
          uint32_t base,
        uint32_t channelNum,
        uint32_t flags)
{
    HWREG(base + (channelNum * ETHERNET_CHANNEL_OFFSET) +
          ETHERNET_O_DMA_CH0_INTERRUPT_ENABLE) &= ~flags;
}
void Ethernet_enableMTLInterrupt(
    uint32_t base,
    uint32_t queueNum,
    uint32_t flags)
{
    HWREG(base + (queueNum * ETHERNET_QUEUE_OFFSET) +
          ETHERNET_O_MTL_Q0_INTERRUPT_CONTROL_STATUS) |= flags;
}
void Ethernet_enableMACInterrupt(
    uint32_t base,
    uint32_t flags)
{
    HWREG(base +
          ETHERNET_O_MAC_INTERRUPT_ENABLE) |= flags;
}
void Ethernet_clearDMAChannelInterrupt(
    uint32_t base,
    uint32_t channelNum,
    uint32_t flags)
{
    HWREG(base + (channelNum * ETHERNET_CHANNEL_OFFSET) +
          ETHERNET_O_DMA_CH0_STATUS) = flags;
}
void Ethernet_writeTxDescListAddress(
    uint32_t base,
    uint32_t channelNum,
    Ethernet_HW_descriptor *write_data)
{

    HWREG(base + (channelNum * (uint32_t)ETHERNET_CHANNEL_OFFSET) +
          (uint32_t)ETHERNET_O_DMA_CH0_TXDESC_LIST_ADDRESS) =
         ((uint32_t)write_data);
}
void Ethernet_writeTxDescTailPointer(
        uint32_t base,
        uint32_t channelNum,
        Ethernet_HW_descriptor *write_data)
{

    HWREG(base + (channelNum * ETHERNET_CHANNEL_OFFSET) +
          ETHERNET_O_DMA_CH0_TXDESC_TAIL_POINTER) =
        ((uint32_t)write_data);
}
void Ethernet_writeRxDescListAddress(
    uint32_t base,
    uint32_t channelNum,
    Ethernet_HW_descriptor *write_data)
{

    HWREG(base + (channelNum * ETHERNET_CHANNEL_OFFSET) +
          ETHERNET_O_DMA_CH0_RXDESC_LIST_ADDRESS) = ((uint32_t)write_data);
}
void Ethernet_writeRxDescTailPointer(
    uint32_t base,
    uint32_t channelNum,
    Ethernet_HW_descriptor *write_data)
{

    HWREG(base + (channelNum * ETHERNET_CHANNEL_OFFSET) +
          ETHERNET_O_DMA_CH0_RXDESC_TAIL_POINTER) = ((uint32_t)write_data);
}
//
//Subsystem Routines
//
void Ethernet_setSSControlStatus(
    uint32_t base,
    uint32_t phyTypeSel,
    uint32_t loopbackModeClkSrcSel,
    uint32_t clkSourceSelect,
    uint32_t flowControlEnable)
{
    HWREG(base + ETHERNETSS_O_CTRLSTS) =
        (phyTypeSel << ETHERNETSS_CTRLSTS_PHY_INTF_SEL_S) |
         (loopbackModeClkSrcSel << ETHERNET_SS_CTRLSTS_CLK_LM_S) |
         (clkSourceSelect << ETHERNET_SS_CTRLSTS_CLK_SRC_SEL_S) |
         (flowControlEnable << ETHERNETSS_CTRLSTS_FLOW_CTRL_EN_S);
}

void Ethernet_writeTxDMAControl(
    uint32_t base,
    uint32_t channelNum,
    uint32_t burst_Length,
    Ethernet_EnableTSO tseEnable,
    uint16_t maximumSegmentSize,
    uint8_t earlyTransmitInterruptEnable)
{
    if(burst_Length > 32U)
    {
        //
        //Turn on 8xPBL
        //
        HWREG(base + ETHERNET_O_DMA_CH0_CONTROL +
                (ETHERNET_CHANNEL_OFFSET * channelNum)) |=
          ETHERNET_DMA_CH0_CONTROL_PBLX8;
        //
        //Divide the burst length by 8 and store in the TX PBL field
        //
        HWREG(base + ETHERNET_O_DMA_CH0_TX_CONTROL +
            (ETHERNET_CHANNEL_OFFSET * channelNum)) |=
                ((burst_Length / 8U) <<  ETHERNET_DMA_CH0_TX_CONTROL_TXPBL_S);
    }
    else
    {
        //
        //Turn OFF 8xPBL
        //
        HWREG(base + ETHERNET_O_DMA_CH0_CONTROL +
              (ETHERNET_CHANNEL_OFFSET * channelNum)) &=
              ~ETHERNET_DMA_CH0_CONTROL_PBLX8;
        HWREG(base + ETHERNET_O_DMA_CH0_TX_CONTROL +
              (ETHERNET_CHANNEL_OFFSET * channelNum)) |=
              (burst_Length <<  ETHERNET_DMA_CH0_TX_CONTROL_TXPBL_S );
    }

    if(ETHERNET_TX_CHANNEL_TSE_ENABLE == tseEnable)
    {
        HWREG(base + ETHERNET_O_DMA_CH0_TX_CONTROL +
              (ETHERNET_CHANNEL_OFFSET * channelNum)) |=
                   ETHERNET_DMA_CH0_TX_CONTROL_TSE_M;
        HWREG(base + ETHERNET_O_DMA_CH0_CONTROL +
              (ETHERNET_CHANNEL_OFFSET * channelNum)) |=
                   maximumSegmentSize;
    }
    else
    {
        HWREG(base + ETHERNET_O_DMA_CH0_TX_CONTROL +
              (ETHERNET_CHANNEL_OFFSET * channelNum)) &=
               ~ETHERNET_DMA_CH0_TX_CONTROL_TSE_M;
    }

    HWREG(base + ETHERNET_O_DMA_CH0_TX_CONTROL +
          (ETHERNET_CHANNEL_OFFSET * channelNum)) |=
               ((uint32_t)earlyTransmitInterruptEnable <<
                (uint32_t)ETHERNET_DMA_CH0_TX_CONTROL_ETIC_S );
}

void Ethernet_enableMACRxQ(uint32_t base,
                                            uint32_t queueNumber)
{
    if(queueNumber == ETHERNET_DMA_CHANNEL_NUM_0)
    {
        HWREG(base + ETHERNET_O_MAC_RXQ_CTRL0) |=
              ETHERNET_MAC_RXQ_CONTROL_RXQEN_ENABLED_GENERIC <<
              ETHERNET_MAC_RXQ_CTRL0_RXQ0EN_S;
    }
    else if(queueNumber == ETHERNET_DMA_CHANNEL_NUM_1)
    {
        HWREG(base + ETHERNET_O_MAC_RXQ_CTRL0) |=
            ETHERNET_MAC_RXQ_CONTROL_RXQEN_ENABLED_GENERIC <<
            ETHERNET_MAC_RXQ_CTRL0_RXQ1EN_S;
    }
    else
    {
         //
        //Do nothing
        //
    }
}
void Ethernet_enableRxDMAReception(uint32_t base,
                uint8_t channelNum)
{

    HWREG(base +
          ETHERNET_O_DMA_CH0_RX_CONTROL +
          (ETHERNET_CHANNEL_OFFSET * channelNum)) |=
           ETHERNET_DMA_CH0_RX_CONTROL_SR;
}
void Ethernet_disableRxDMAReception(uint32_t base,
                uint8_t channelNum)
{

    HWREG(base +
          ETHERNET_O_DMA_CH0_RX_CONTROL +
          (ETHERNET_CHANNEL_OFFSET * channelNum)) &=
           ~ETHERNET_DMA_CH0_RX_CONTROL_SR;
}

#define ETHERNET_RX_DMA_QUEUE_DYNAMIC_VALUE 0x1U


void Ethernet_setDMARxQueueMode(uint32_t base,
            Ethernet_RxDMAQueueMode mode,
            Ethernet_QueueNum queueNum,
            Ethernet_ChannelNum mappedChannel)
{

    if(mode == ETHERNET_RX_DMA_QUEUE_DYNAMIC )
    {

        HWREG(base + ETHERNET_O_MTL_RXQ_DMA_MAP0) |=
                    (((uint32_t)ETHERNET_RX_DMA_QUEUE_DYNAMIC_VALUE) <<
                     (((uint32_t) ETHERNET_MTL_RXQ_DMA_MAP0_DDMACH_S) *
                     ((uint32_t)queueNum + 1U)));
    }
    else
    {
        //
        //Clear the DDMACH which configures the channel in Static mode
        //to be mapped with the channel number provided
        //
        HWREG(base +
              ETHERNET_O_MTL_RXQ_DMA_MAP0) &=
                            ~(((uint32_t)ETHERNET_RX_DMA_QUEUE_DYNAMIC_VALUE) <<
                            (ETHERNET_MTL_RXQ_DMA_MAP0_QDMACH_S *
                             (uint32_t)queueNum));

        HWREG(base +
              ETHERNET_O_MTL_RXQ_DMA_MAP0) |=
                ((uint32_t)mappedChannel <<
                 (ETHERNET_MTL_RXQ_DMA_MAP0_QDMACH_S *
                  (uint32_t)queueNum));

    }
}

void Ethernet_setMultiQueueRxQueueControl(uint32_t base,
                Ethernet_RxQControl rxqControl)
{

    HWREG(base +
          ETHERNET_O_MAC_RXQ_CTRL1) = *((uint32_t *)&rxqControl);
}
void Ethernet_writeRxDMAControl(
     uint32_t base,
     uint32_t channelNum,
     uint32_t burst_Length,
     uint32_t dmaBufferSize,
     uint8_t earlyReceiveInterruptEnable)
{
    if(burst_Length > 32U)
    {
        //
        //Turn on 8xPBL
        //
        HWREG(base + ETHERNET_O_DMA_CH0_CONTROL +
              (ETHERNET_CHANNEL_OFFSET * channelNum)) |=
              ETHERNET_DMA_CH0_CONTROL_PBLX8;
        //
        //Divide the burst length by 8 and store in the TX PBL field
        //
        HWREG(base + ETHERNET_O_DMA_CH0_RX_CONTROL +
              (ETHERNET_CHANNEL_OFFSET * channelNum)) |=
            (((burst_Length / 8U )<<  ETHERNET_DMA_CH0_RX_CONTROL_RXPBL_S ) |
             (dmaBufferSize<< ETHERNET_DMA_CH0_RX_CONTROL_RBSZ_S));
    }
    else
    {
        //
        //Turn OFF 8xPBL
        //
        HWREG(base + ETHERNET_O_DMA_CH0_CONTROL +
              (ETHERNET_CHANNEL_OFFSET * channelNum)) &=
             ~ETHERNET_DMA_CH0_CONTROL_PBLX8;
        HWREG(base + ETHERNET_O_DMA_CH0_RX_CONTROL +
             (ETHERNET_CHANNEL_OFFSET * channelNum)) |=
            ((burst_Length <<  ETHERNET_DMA_CH0_RX_CONTROL_RXPBL_S ) |
             (dmaBufferSize << ETHERNET_DMA_CH0_RX_CONTROL_RBSZ_S));
    }

         HWREG(base + ETHERNET_O_DMA_CH0_RX_CONTROL +
              (ETHERNET_CHANNEL_OFFSET * channelNum)) |=
              ((uint32_t)earlyReceiveInterruptEnable<<
               ETHERNET_DMA_CH0_TX_CONTROL_ERIC_S) ;
}

uint16_t Ethernet_getRxERICount(uint32_t base, uint32_t channelNum)
{

    uint16_t earlyInterruptCount;
    earlyInterruptCount = HWREG(base + ETHERNET_O_DMA_CH0_MISS_FRAME_CNT +
                                (ETHERNET_CHANNEL_OFFSET * channelNum)) &
                                ETHERNET_DMA_CH0_MISS_FRAME_CNT_MFC_M ;
    return(earlyInterruptCount);
}

void Ethernet_setDMAChannelTransmitStart(uint32_t base, uint32_t channelNum)
{
    HWREG(EMAC_BASE + ETHERNET_O_DMA_CH0_TX_CONTROL +
          (ETHERNET_CHANNEL_OFFSET * channelNum )) |=
           ETHERNET_DMA_CH0_TX_CONTROL_ST;
}
void Ethernet_disableDMAChannelTransmit(uint32_t base, uint32_t channelNum)
{
    HWREG(EMAC_BASE + ETHERNET_O_DMA_CH0_TX_CONTROL +
          (ETHERNET_CHANNEL_OFFSET * channelNum )) &=
           ~ETHERNET_DMA_CH0_TX_CONTROL_ST;
}

void Ethernet_setTxDescRingLength(
        uint32_t base,
        uint32_t channelNum,
        uint32_t ringLength)
{
//
//Higher layer software is expected to give the number of descriptors
// the Ethernet module expects x-1 to be programmed if descriptor length is X
//
    HWREG(base + ETHERNET_O_DMA_CH0_TXDESC_RING_LENGTH +
          (ETHERNET_CHANNEL_OFFSET * channelNum)) |=
          (ringLength - 1U);

}
void Ethernet_setRxDescRingLength(
    uint32_t base,
    uint32_t channelNum,
    uint32_t ringLength)
{
    //
    //Higher layer software is expected to give the number of descriptors
    // the Ethernet module expects x-1 to be programmed if descriptor length is X
    //
    HWREG(base + ETHERNET_O_DMA_CH0_RXDESC_RING_LENGTH +
         (ETHERNET_CHANNEL_OFFSET * channelNum)) |=
           (ringLength - 1U);

}
void Ethernet_setMACAddr(
    uint32_t base,
    uint8_t instanceNum,
    uint32_t MACAddrHigh,
    uint32_t MACAddrLow,
    Ethernet_ChannelNum channelNumber)
{
      HWREG(base + ETHERNET_O_MAC_ADDRESS0_HIGH +
            ((uint32_t)instanceNum*0x8U)) =
        (MACAddrHigh | ETHERNET_MAC_ADDRESS0_HIGH_AE |
        (((uint32_t)channelNumber) << ETHERNET_MAC_ADDRESS0_HIGH_DCS_S));

      HWREG(base + ETHERNET_O_MAC_ADDRESS0_LOW +
            ((uint32_t)instanceNum*0x8U)) = MACAddrLow;

}
/** ==========================================================================
 *  @n@b Ethernet_performPushPacketQueueChain()
 *
 *  @b Description
 *  @n Push a desc buffer chain onto a queue
 *
 *  @b Arguments
 *  @verbatim
        pktQueuePtr              pointer to packet queue
        firstPktHdrPtr    pointer to the first element of the EMAC Packet.
        lastPktHdrPtr     pointer to the last element of the EMAC Packet.
        Count           count of elements to push
    @endverbatim
 *
 *
 *  <b> Return Value </b>  None
 *
 *  <b> Pre Condition </b>
 *  @n  None
 *
 *  <b> Post Condition </b>
 *  @n  A chain of descriptor buffers are added to the Queue
 *
 *  @b Example
 *  @verbatim
        ETHERNET_PKT_QUEUE_T *pktQueuePtr;
        ETHERNET_PKT_DESC_T *firstPktHdrPtr, *lastPktHdrPtr;
        uint32_t count;

        Ethernet_performPushPacketQueueChain( pktQueuePtr, firstPktHdrPtr,
        lastPktHdrPtr, Count );
    @endverbatim
 * ============================================================================
 */
static void Ethernet_performPushPacketQueueChain(
        Ethernet_PKT_Queue_T *pktQueuePtr,
        Ethernet_Pkt_Desc *firstPktHdrPtr,
        Ethernet_Pkt_Desc *lastPktHdrPtr,
        uint32_t count)
{
    lastPktHdrPtr->nextPacketDesc = 0U;

    if(0U == pktQueuePtr->head)
    {
        //
        // Queue is empty - Initialize it with this packet chain
        //
        pktQueuePtr->head = firstPktHdrPtr;
        pktQueuePtr->tail = lastPktHdrPtr;
    }
    else
    {
        //
        // Queue is not empty - Push onto END
        //
        pktQueuePtr->tail->nextPacketDesc = firstPktHdrPtr;
        pktQueuePtr->tail        = lastPktHdrPtr;
    }
    pktQueuePtr->count += count;
}


/** ==========================================================================
 *  @n@b Ethernet_performPopOnPacketQueue()
 *
 *  @b Description
 *  @n Pop a desc buffer off a queue
 *
 *  @b Arguments
 *  @verbatim
        pktQueuePtr      pointer to packet queue
    @endverbatim
 *
 *  <b> Return Value </b>  Pointer to EMAC packet
 *
 *  <b> Pre Condition </b>
 *  @n  None
 *
 *  <b> Post Condition </b>
 *  @n  Descriptor buffer from the Queue is removed
 *
 *  @b Example
 *  @verbatim
        ETHERNET_PKT_QUEUE_T *pktQueuePtr;
        ETHERNET_performPopOnPacketQueue( pktQueuePtr );
    @endverbatim
 * ============================================================================
 */
static Ethernet_Pkt_Desc *Ethernet_performPopOnPacketQueue(
            Ethernet_PKT_Queue_T *pktQueuePtr)
{
    Ethernet_Pkt_Desc *pktDescHdrPtr;

    pktDescHdrPtr = pktQueuePtr->head;

    if(0U != pktDescHdrPtr)
    {
        pktQueuePtr->head = pktDescHdrPtr->nextPacketDesc;
        pktQueuePtr->count--;
    }

    return(pktDescHdrPtr);
}

/** ==========================================================================
 *  @n@b Ethernet_returnTopOfPacketQueue()
 *
 *  @b Description
 *  @n Return Front element of a queue
 *
 *  @b Arguments
 *  @verbatim
        pktQueuePtr      pointer to packet queue
    @endverbatim
 *
 *  <b> Return Value </b>  Pointer to EMAC packet
 *
 *  <b> Pre Condition </b>
 *  @n  None
 *
 *  <b> Post Condition </b>
 *  @n  None
 *
 *  @b Example
 *  @verbatim
        ETHERNET_PKT_QUEUE_T *pktQueuePtr;
        ETHERNET_returnTopOfPacketQueue( pktQueuePtr );
    @endverbatim
 * ============================================================================
 */
static Ethernet_Pkt_Desc *Ethernet_returnTopOfPacketQueue(
            Ethernet_PKT_Queue_T *pktQueuePtr)
{
    return(pktQueuePtr->head);
}

/** ==========================================================================
 *  @n@b Ethernet_performPushOnPacketQueue()
 *
 *  @b Description
 *  @n Push a desc buffer onto a queue
 *
 *  @b Arguments
 *  @verbatim
        pktQueuePtr      pointer to packet queue
        pktDescHdrPtr pointer to the EMAC packet
    @endverbatim
 *
 *
 *  <b> Return Value </b>  None
 *
 *  <b> Pre Condition </b>
 *  @n  None
 *
 *  <b> Post Condition </b>
 *  @n  Descriptor buffer from the Queue is added
 *
 *  @b Example
 *  @verbatim
        ETHERNET_PKT_QUEUE_T *pktQueuePtr;
        ETHERNET_PKT_DESC_T *pktDescHdrPtr

        Ethernet_performPushOnPacketQueue( pktQueuePtr, pktDescHdrPtr );
    @endverbatim
 * ============================================================================
 */
static void Ethernet_performPushOnPacketQueue(
        Ethernet_PKT_Queue_T *pktQueuePtr,
        Ethernet_Pkt_Desc *pktDescHdrPtr)
{
    pktDescHdrPtr->nextPacketDesc = 0U;

    if(0U == pktQueuePtr->head)
    {
        //
        // Queue is empty - Initialize it with this one packet
        //
        pktQueuePtr->head = pktDescHdrPtr;
        pktQueuePtr->tail = pktDescHdrPtr;
    }
    else
    {
        //
        // Queue is not empty - Push onto END
        //
        pktQueuePtr->tail->nextPacketDesc = pktDescHdrPtr;
        pktQueuePtr->tail        = pktDescHdrPtr;
    }
    pktQueuePtr->count++;
}
static uint32_t Ethernet_initTxChannel(Ethernet_ChInfo *chInfo)
{
    Ethernet_DmaObj *dmaObj = &Ethernet_device_struct.dmaObj;
    Ethernet_TxChDesc *txChan = &dmaObj->txDma[chInfo->chNum];
    Ethernet_HW_descriptor *descPtr;

    descPtr = &Ethernet_device_struct.txDesc [chInfo->chNum * chInfo->numBD];
        /* zero init the book keeping structure */
    (void)memset(txChan, 0U, sizeof(Ethernet_TxChDesc));
    txChan->chInfo = chInfo;
    txChan->devicePtr = &Ethernet_device_struct;
    txChan->descMax = chInfo->numBD;
    txChan->descFirst = descPtr;
    //
    //The descriptor pointer shall be pointing to first descriptor
    //Hence first index should be zero
    //
    txChan->indexFirst = 0;
    txChan->indexRead = 0;
    txChan->indexWrite = 0xffffffffU;
    txChan->indexLast = (chInfo->numBD - 1U);
    txChan->dmaInProgress = 0U;
    dmaObj->chIsInit[ETHERNET_CH_DIR_TX][chInfo->chNum] = true;

    Ethernet_writeTxDescListAddress(
                    Ethernet_device_struct.baseAddresses.enet_base,
                    chInfo->chNum ,
                    (&Ethernet_device_struct.txDesc[(chInfo->chNum *
                     ETHERNET_DESCRIPTORS_NUM_TX_PER_CHANNEL)]));

    if(chInfo->storeNForward == ETHERNET_MTL_TXQ_OPMODE_TSF_DISABLE)
    {
        //
        //if it is Threshold mode then Enable Early Transmit interrupt
        //
        Ethernet_writeTxDMAControl(
                Ethernet_device_struct.baseAddresses.enet_base,
                chInfo->chNum,
                chInfo->burstLength,
                chInfo->enableTSE,
                chInfo->maximumSegmentSize,
                ETHERNET_DMA_CH0_TX_CONTROL_ETIC_ENABLE);
     }
    else
     {
        Ethernet_writeTxDMAControl(
            Ethernet_device_struct.baseAddresses.enet_base,
            chInfo->chNum,
            chInfo->burstLength,
            chInfo->enableTSE,
            chInfo->maximumSegmentSize,
            ETHERNET_DMA_CH0_TX_CONTROL_ETIC_DISABLE);
      }
    Ethernet_setTxDescRingLength(
                Ethernet_device_struct.baseAddresses.enet_base,
                chInfo->chNum,
                chInfo->numBD
                );
     Ethernet_setMTLTxQueueOpMode(
            Ethernet_device_struct.baseAddresses.enet_base,
            chInfo->chNum,
            chInfo->queueThreshold,
            chInfo->dmaQueueSize,
            chInfo->storeNForward);
    return(ETHERNET_RET_SUCCESS);

}
uint32_t Ethernet_initRxChannel(Ethernet_ChInfo *chInfo)
{
    Ethernet_DmaObj *       dmaObj = &Ethernet_device_struct.dmaObj;
    Ethernet_RxChDesc *rxChan = &dmaObj->rxDma[chInfo->chNum];
    Ethernet_HW_descriptor       *descPtr;

    /* zero init the book keeping structure */
    (void)memset(rxChan, 0U, sizeof(Ethernet_RxChDesc));

    /* store pointer to channel info structure */
    rxChan->chInfo = chInfo;

    /*
     * Setup Receive Buffers
     */
    /*
     * We give the first descriptors to RX. The rest of the descriptors
     * will be divided evenly among the TX channels. Odds are this
     * will leave TX with a very large number of TX descriptors, but
     * we'll only use what we need (driven from the application send
     * requests). The RX descriptors are always kept fully populated.
     */

    /* Pointer to first descriptor to use on RX */

     descPtr = &Ethernet_device_struct.rxDesc[(chInfo->chNum *
                    chInfo->numBD)];

    /* Init the Rx channel */
    rxChan->devicePtr         = &Ethernet_device_struct;
    rxChan->descMax    = chInfo->numBD;
    rxChan->descFirst = descPtr;
    rxChan->indexLast = (chInfo->numBD - 1U);
    rxChan->dmaInProgress = 0U;
    Ethernet_writeRxDescListAddress(
        Ethernet_device_struct.baseAddresses.enet_base,
        chInfo->chNum,
        &Ethernet_device_struct.rxDesc[(chInfo->chNum *
        ETHERNET_DESCRIPTORS_NUM_RX_PER_CHANNEL)]);

   if(chInfo->storeNForward == ETHERNET_MTL_RX_Q_OP_MODE_RSF_DISABLE)
    {
        Ethernet_writeRxDMAControl(
        Ethernet_device_struct.baseAddresses.enet_base,
        chInfo->chNum,
        chInfo->burstLength,
        chInfo->dmaBufferSize,
        ETHERNET_DMA_CH0_RX_CONTROL_ERIC_ENABLE);
    }
   else
    {
     Ethernet_writeRxDMAControl(Ethernet_device_struct.baseAddresses.enet_base,
                                    chInfo->chNum,
                                    chInfo->burstLength,
                                    chInfo->dmaBufferSize,
                                    ETHERNET_DMA_CH0_RX_CONTROL_ERIC_DISABLE);
    }
    Ethernet_setRxDescRingLength(
                Ethernet_device_struct.baseAddresses.enet_base,
                chInfo->chNum,
                chInfo->numBD
                );
    Ethernet_setMTLRxQueueOpMode(
            Ethernet_device_struct.baseAddresses.enet_base,
            chInfo->chNum,
            chInfo->queueThreshold,
            chInfo->dmaQueueSize,
            chInfo->storeNForward);
        /* Fill the descriptor table */
    Ethernet_addPacketsIntoRxQueue(rxChan);
    Ethernet_enableMACRxQ(Ethernet_device_struct.baseAddresses.enet_base,
                                                chInfo->chNum);
    Ethernet_enableRxDMAReception(
        Ethernet_device_struct.baseAddresses.enet_base ,
        (uint8_t)chInfo->chNum);
    Ethernet_setMACConfiguration(
            Ethernet_device_struct.baseAddresses.enet_base ,
            ETHERNET_MAC_CONFIGURATION_RE);
    if(rxChan->descCount < (chInfo->numBD))
    {
        /* Free all RX descriptors */


        /* Return the error condition */
        return(ETHERNET_ERR_INVALID_PARAM);
    }
    dmaObj->chIsInit[ETHERNET_CH_DIR_RX][chInfo->chNum] = true;

    return(0);

}


/* This function is a callback function called by the LLD to
Get a Packet Buffer. Has to return a ETHERNET_Pkt_Desc Structure filled
User or upper level stack can rewrite this API for their own use case
*/
Ethernet_Pkt_Desc *Ethernet_getPacketBuffer(void)
{

#ifdef ETHERNET_DEBUG
    Ethernet_numGetPacketBufferCallback++;
#endif
    Ethernet_pktDescriptorRX.bufferLength       = ETHERNET_MAX_PACKET_LENGTH;
    Ethernet_pktDescriptorRX.dataBuffer = &Ethernet_device_struct.rxBuffer [
               (ETHERNET_MAX_PACKET_LENGTH *
               Ethernet_device_struct.rxBuffIndex)];
    //
    //Wrap around
    //
    Ethernet_device_struct.rxBuffIndex += 1U;
    Ethernet_device_struct.rxBuffIndex =
     (Ethernet_device_struct.rxBuffIndex%ETHERNET_NO_OF_RX_PACKETS);
    Ethernet_pktDescriptorRX.dataOffset         = 0U; //Usable from Address 0
    return(&Ethernet_pktDescriptorRX);
}


void Ethernet_releaseTxPacketBuffer(
        Ethernet_Handle handleApplication,
        Ethernet_Pkt_Desc *pPacket)
{
#ifdef ETHERNET_DEBUG
    Ethernet_numTxPktFreeCallback++;
#endif
}

Ethernet_Pkt_Desc *Ethernet_receivePacketCallback(
    Ethernet_Handle handleApplication,
    Ethernet_Pkt_Desc *pPacket)
{
#ifdef ETHERNET_DEBUG
    Ethernet_numRxCallback++;
#endif
//
// This is a placeholder for Application specific handling
// We are replenishing the buffer received with another buffer
//
    return  Ethernet_getPacketBuffer();
}

//**********************************************************************
//
// Ethernet_setConfigTimestampPTP().
//
//**********************************************************************
void Ethernet_setConfigTimestampPTP(uint32_t base, uint32_t config,
                                    float subSecondInc)
{
    uint32_t subNanosecPart;
    uint32_t subSecPart;

    //
    // Parameter sanity check.
    //
    ASSERT(EMAC_BASE == base);

    //
    // If Rollover is Binary, scale the subsecond increment.
    //
    if(ETHERNET_MAC_TIMESTAMP_CONTROL_BINARY_ROLLOVER ==
       (config & ETHERNET_MAC_TIMESTAMP_CONTROL_TSCTRLSSR))
        subSecondInc /= ETHERNET_MAC_BINARY_ROLLOVER_ACCURACY;

    //
    // Save the Integer part of the subsecond increment.
    //
    subSecPart = (uint32_t)subSecondInc;

    //
    // Extract subnanosecond component of the subsecond increment.
    //
    subNanosecPart =
            (uint32_t)((subSecondInc - (float)subSecPart) *
                       (float)ETHERNET_MAC_SUBNANOSECONDS_INC_MULTIPLIER);

    //
    // Write the subsecond increment value (The integer part saved above) and
    // the sub nanosecond increment value (fractional part).
    //
    HWREG(base + ETHERNET_O_MAC_SUB_SECOND_INCREMENT) =
            ((subSecPart << ETHERNET_MAC_SUB_SECOND_INCREMENT_SSINC_S) &
             ETHERNET_MAC_SUB_SECOND_INCREMENT_SSINC_M) |
            ((subNanosecPart << ETHERNET_MAC_SUB_SECOND_INCREMENT_SNSINC_S) &
             ETHERNET_MAC_SUB_SECOND_INCREMENT_SNSINC_M);

    //
    // Set the timestamp configuration.
    //
    HWREG(base + ETHERNET_O_MAC_TIMESTAMP_CONTROL) = config;
}

//**********************************************************************
//
// Ethernet_setConfigTimestampPTP().
//
//**********************************************************************
uint32_t Ethernet_getConfigTimestampPTP(uint32_t base, float *subSecondInc)
{
    uint32_t subNanosecPart;
    uint32_t subSecPart;
    //
    // Parameter sanity check.
    //
    ASSERT(EMAC_BASE == base);
    ASSERT(subSecondInc);

    //
    // Read the current subsecond increment value.
    //
    subSecPart = (HWREG(base + ETHERNET_O_MAC_SUB_SECOND_INCREMENT) &
                  ETHERNET_MAC_SUB_SECOND_INCREMENT_SSINC_M) >>
                  ETHERNET_MAC_SUB_SECOND_INCREMENT_SSINC_S;

    //
    // Read the subnanosecond part (fractional part).
    //
    subNanosecPart = (HWREG(base + ETHERNET_O_MAC_SUB_SECOND_INCREMENT) &
                      ETHERNET_MAC_SUB_SECOND_INCREMENT_SNSINC_M) >>
                     ETHERNET_MAC_SUB_SECOND_INCREMENT_SNSINC_S;

    //
    // Form the subsecond increment from integer and fractional parts.
    //
    *subSecondInc = (float)subSecPart +
                    (((float)subNanosecPart) /
                     ((float)ETHERNET_MAC_SUBNANOSECONDS_INC_MULTIPLIER));
    //
    // Return the current timestamp configuration.
    //
    return(HWREG(base + ETHERNET_O_MAC_TIMESTAMP_CONTROL));
}

//**********************************************************************
//
// Ethernet_enableSysTimePTP().
//
//**********************************************************************
void Ethernet_enableSysTimePTP(uint32_t base)
{
    //
    // Parameter sanity check.
    //
    ASSERT(EMAC_BASE == base);

    //
    // Enable IEEE 1588 timestamping.
    //
    HWREG(base + ETHERNET_O_MAC_TIMESTAMP_CONTROL) |=
                                         ETHERNET_MAC_TIMESTAMP_CONTROL_TSENA;

    //
    // If necessary, initialize the timestamping system.  This bit self-clears
    // once the system time is loaded.  Only do this if initialization is not
    // currently ongoing.
    //
    if(0U == (HWREG(base + ETHERNET_O_MAC_TIMESTAMP_CONTROL) &
         ETHERNET_MAC_TIMESTAMP_CONTROL_TSINIT))
    {
        HWREG(base + ETHERNET_O_MAC_TIMESTAMP_CONTROL) |=
                                        ETHERNET_MAC_TIMESTAMP_CONTROL_TSINIT;
    }
}

//**********************************************************************
//
// Ethernet_disableSysTimePTP().
//
//**********************************************************************
void Ethernet_disableSysTimePTP(uint32_t base)
{
    //
    // Parameter sanity check.
    //
    ASSERT(EMAC_BASE == base);

    //
    // Disable IEEE 1588 timestamping.
    //
    HWREG(base + ETHERNET_O_MAC_TIMESTAMP_CONTROL) &=
                                        ~ETHERNET_MAC_TIMESTAMP_CONTROL_TSENA;
}

//**********************************************************************
//
// Ethernet_setSysTimePTP().
//
//**********************************************************************
void Ethernet_setSysTimePTP(uint32_t base, uint32_t seconds,
                            uint32_t subSeconds)
{
    //
    // Parameter sanity check.
    //
    ASSERT(EMAC_BASE == base);

    //
    // Write the new time to the system time update registers.
    // TODO: Take care of the bit 31 in the nanoseconds update register.
    //
    HWREG(base + ETHERNET_O_MAC_SYSTEM_TIME_SECONDS_UPDATE) = seconds;
    HWREG(base + ETHERNET_O_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE) = subSeconds;

    //
    // Wait for any previous update to complete.
    //
    while(0U != (HWREG(base + ETHERNET_O_MAC_TIMESTAMP_CONTROL) &
          ETHERNET_MAC_TIMESTAMP_CONTROL_TSINIT))
    {
        //
        // Spin for a while.
        //
    }

    //
    // Force the system clock to reset.
    //
    HWREG(base + ETHERNET_O_MAC_TIMESTAMP_CONTROL) |=
                                       ETHERNET_MAC_TIMESTAMP_CONTROL_TSINIT;
}

//**********************************************************************
//
// Ethernet_getSysTimePTP().
//
//**********************************************************************
void Ethernet_getSysTimePTP(uint32_t base, uint32_t *seconds,
                            uint32_t *subSeconds)
{
    //
    // Parameter sanity check.
    //
    ASSERT(EMAC_BASE == base);
    ASSERT(NULL != seconds);
    ASSERT(NULL != subSeconds);

    //
    // Read the two-part system time from the seconds and nanoseconds
    // registers.  We do this in a way that should guard against us reading
    // the registers across a nanosecond wrap.
    //
    do
    {
        *seconds = HWREG(base + ETHERNET_O_MAC_SYSTEM_TIME_SECONDS);
        *subSeconds = HWREG(base + ETHERNET_O_MAC_SYSTEM_TIME_NANOSECONDS);
    }
    while(*subSeconds > HWREG(base + ETHERNET_O_MAC_SYSTEM_TIME_NANOSECONDS));
}

//**********************************************************************
//
// Ethernet_updateSysTimePTP().
//
//**********************************************************************
void Ethernet_updateSysTimePTP(uint32_t base, uint32_t seconds,
                               uint32_t subSeconds, bool addSub)
{
    //
    // Parameter sanity check.
    //
    ASSERT(EMAC_BASE == base);

    //
    // Write the new time to the system time update registers.
    //
    HWREG(base + ETHERNET_O_MAC_SYSTEM_TIME_SECONDS_UPDATE) = seconds;
    HWREG(base + ETHERNET_O_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE) =
         ((subSeconds & ETHERNET_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_TSSS_M) <<
          ETHERNET_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_TSSS_S) |
         (addSub ? 0U : ETHERNET_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_ADDSUB);

    //
    // Wait for any previous update to complete.
    //
    while(0U != (HWREG(base + ETHERNET_O_MAC_TIMESTAMP_CONTROL) &
          ETHERNET_MAC_TIMESTAMP_CONTROL_TSUPDT))
    {
        //
        // Spin for a while.
        //
    }

    //
    // Force the system clock to update by the value provided.
    //
    HWREG(base + ETHERNET_O_MAC_TIMESTAMP_CONTROL) |=
                                        ETHERNET_MAC_TIMESTAMP_CONTROL_TSUPDT;
}

//**********************************************************************
//
// Ethernet_getOneStepTransmitTimestampPTP().
//
//**********************************************************************
uint32_t Ethernet_getOneStepTransmitTimestampPTP(uint32_t base,
                                                 uint32_t *seconds,
                                                 uint32_t *nanoSeconds)
{
    //
    // Parameter sanity check.
    //
    ASSERT(EMAC_BASE == base);
    ASSERT(NULL != seconds);
    ASSERT(NULL != nanoSeconds);

    //
    // Fetch the timestamp that was captured for the transmitted packet.
    //
    *nanoSeconds =
            (HWREG(base + ETHERNET_O_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS) &
             ETHERNET_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_TXTSSLO_M) >>
            ETHERNET_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_TXTSSLO_S;
    *seconds = HWREG(base + ETHERNET_O_MAC_TX_TIMESTAMP_STATUS_SECONDS);

    //
    // Return the Tx Timestamp Status Missed indicator bit.
    //
    return(HWREG(base + ETHERNET_O_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS) &
            ETHERNET_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_TXTSSMIS);
}

//**********************************************************************
//
// Ethernet_setAddend().
//
//**********************************************************************
void Ethernet_setAddend(uint32_t base, uint32_t addend)
{
    //
    // Parameter sanity check.
    //
    ASSERT(base == EMAC_BASE);

    HWREG(base + ETHERNET_O_MAC_TIMESTAMP_ADDEND) = addend;

    //
    // Force the system clock to update by the value provided.
    //
    HWREG(base + ETHERNET_O_MAC_TIMESTAMP_CONTROL) |=
    ETHERNET_MAC_TIMESTAMP_CONTROL_TSADDREG;

    //
    // Wait for the update to complete.
    //
    while(0U != (HWREG(base + ETHERNET_O_MAC_TIMESTAMP_CONTROL) &
                ETHERNET_MAC_TIMESTAMP_CONTROL_TSADDREG))
    {
        //
        // Spin for a while.
        //
    }

}

//**********************************************************************
//
// Ethernet_getDepthAuxSnapshotFIFO().
//
//**********************************************************************
uint32_t Ethernet_getDepthAuxSnapshotFIFO(uint32_t base)
{
    //
    // Parameter sanity check
    //
    ASSERT(EMAC_BASE == base);

    return((HWREG(base + ETHERNET_O_MAC_TIMESTAMP_STATUS) &
             ETHERNET_MAC_TIMESTAMP_STATUS_ATSNS_M) >>
            ETHERNET_MAC_TIMESTAMP_STATUS_ATSNS_S);
}

//**********************************************************************
//
// Ethernet_setTimestampSWTrigger().
//
//**********************************************************************
void Ethernet_setTimestampSWTrigger(uint32_t base, uint32_t trigSelect)
{
    //
    // Parameter sanity check
    //
    ASSERT(EMAC_SS_BASE == base);
    ASSERT(ETHERNET_SS_PTPTSSWTRIG_PTP_AUX_TS_SW_TRIG1 >= trigSelect);


    switch(trigSelect)
    {
    case ETHERNET_SS_PTPTSSWTRIG_PTP_AUX_TS_SW_TRIG0:
        HWREG(base + ETHERNETSS_O_PTPTSSWTRIG0) =
                                   ETHERNETSS_PTPTSSWTRIG0_PTP_AUX_TS_SW_TRIG0;
        break;
    case ETHERNET_SS_PTPTSSWTRIG_PTP_AUX_TS_SW_TRIG1:
        HWREG(base + ETHERNETSS_O_PTPTSSWTRIG1) =
                                   ETHERNETSS_PTPTSSWTRIG1_PTP_AUX_TS_SW_TRIG1;
        break;
    default:

        //
        // Wrong PTP SW Trig select.
        //
        break;
        //
    }

    //
    // Triggering might not be captured if the FIFO is full.
    // Return state info to indicate the same.
    //
    if(Ethernet_getDepthAuxSnapshotFIFO(base) <
       ETHERNET_MAC_AUX_TIMESTAMP_FIFO_DEPTH)
    {
        //
        // TODO: Return status info like FIFO_FULL
        //
    }
}

//**********************************************************************
//
// Ethernet_configAuxTimestampTrigger().
//
//**********************************************************************
void Ethernet_configAuxTimestampTrigger(uint32_t base, uint32_t trigSelect,
                                        uint32_t trigValue)
{
    //
    // Parameter sanity check
    //
    ASSERT(EMAC_SS_BASE == base);
    ASSERT(ETHERNET_SS_PTPTSTRIGSEL_AUX_TRIG_SEL_MAX_VALUE >= trigValue);
    ASSERT(ETHERNET_SS_PTPTSTRIGSEL_AUX_TRIG_SEL1 >= trigSelect);

    //
    // TODO : Decide what to do with the magic number.
    //          Should it be provided with the the arguments?
    //
    switch(trigSelect)
    {
    case ETHERNET_SS_PTPTSTRIGSEL_AUX_TRIG_SEL0:
        HWREG(base + ETHERNETSS_O_PTPTSTRIGSEL0) =
              (((uint32_t)ETHERNET_SS_CTRLSTS_WRITE_KEY_VALUE <<
              ETHERNETSS_PTPTSTRIGSEL0_WRITE_KEY_S) &
               ETHERNETSS_PTPTSTRIGSEL0_WRITE_KEY_M) |
              ((trigValue << ETHERNETSS_PTPTSTRIGSEL0_PTP_AUX_TS_TRIG_SEL0_S) &
               ETHERNETSS_PTPTSTRIGSEL0_PTP_AUX_TS_TRIG_SEL0_M);
        break;
    case ETHERNET_SS_PTPTSTRIGSEL_AUX_TRIG_SEL1:
        HWREG(base + ETHERNETSS_O_PTPTSTRIGSEL1) =
              (((uint32_t)ETHERNET_SS_CTRLSTS_WRITE_KEY_VALUE <<
              ETHERNETSS_PTPTSTRIGSEL1_WRITE_KEY_S) &
               ETHERNETSS_PTPTSTRIGSEL1_WRITE_KEY_M) |
              ((trigValue & ETHERNETSS_PTPTSTRIGSEL1_PTP_AUX_TS_TRIG_SEL1_S) <<
               ETHERNETSS_PTPTSTRIGSEL1_PTP_AUX_TS_TRIG_SEL1_M);
        break;
    default:

        //
        // Wrong Timestamp TRIG select.
        //
        break;
    }
}

//**********************************************************************
//
// Ethernet_clearAuxSnapshotFIFO().
//
//**********************************************************************
void Ethernet_clearAuxSnapshotFIFO(uint32_t base)
{
    //
    // Parameter sanity check
    //
    ASSERT(EMAC_BASE == base);

    //
    // TODO : value is 1 and if 1 is programmed, the FIFO is cleared,
    //          Not sure how.
    //
    HWREG(base + ETHERNET_O_MAC_AUXILIARY_CONTROL) |=
                                          ETHERNET_MAC_AUXILIARY_CONTROL_ATSFC;
}

//**********************************************************************
//
// Ethernet_disableAuxSnapshot().
//
//**********************************************************************
void Ethernet_disableAuxSnapshot(uint32_t base, uint32_t trigInstance)
{
    uint32_t val;

    //
    // Parameter sanity check
    //
    ASSERT(EMAC_BASE == base);
    ASSERT((trigInstance & (ETHERNET_MAC_AUXILIARY_CONTROL_ATSEN0 |
                            ETHERNET_MAC_AUXILIARY_CONTROL_ATSEN1)) > 0U);

    val = HWREG(base + ETHERNET_O_MAC_AUXILIARY_CONTROL);

    //
    // Write 0 to already reset bit will not make any difference.
    //
    val &= ~trigInstance;

    HWREG(base + ETHERNET_O_MAC_AUXILIARY_CONTROL) |= val;
}

//**********************************************************************
//
// Ethernet_enableAuxSnapshot().
//
//**********************************************************************
void Ethernet_enableAuxSnapshot(uint32_t base, uint32_t trigInstance)
{
    uint32_t val;

    //
    // Parameter sanity check
    //
    ASSERT(EMAC_BASE == base);
    ASSERT((trigInstance & (ETHERNET_MAC_AUXILIARY_CONTROL_ATSEN0 |
                            ETHERNET_MAC_AUXILIARY_CONTROL_ATSEN1)) > 0U);

    val = HWREG(base + ETHERNET_O_MAC_AUXILIARY_CONTROL);

    //
    // Writing 1 to already set bit will not make any difference.
    //
    val |= trigInstance;

    HWREG(base + ETHERNET_O_MAC_AUXILIARY_CONTROL) = val;
}




//**********************************************************************
//
// Ethernet_dequeueAuxSnapshotFIFO().
//
//**********************************************************************
void Ethernet_dequeueAuxSnapshotFIFO(uint32_t base, uint32_t *seconds,
                                     uint32_t *nanoSeconds)
{


    //
    // Parameter sanity check
    //
    ASSERT(EMAC_BASE == base);

    //
    // Return the snapshots if FIFO is not empty.
    // TODO: return a status to indicate FIFO_EMPTY
    //
    if(Ethernet_getDepthAuxSnapshotFIFO(base) > 0U)
    {
        *seconds = HWREG(base + ETHERNET_O_MAC_AUXILIARY_TIMESTAMP_SECONDS);
        *nanoSeconds = HWREG(base +
            ETHERNET_O_MAC_AUXILIARY_TIMESTAMP_NANOSECONDS);
    }
}

//**********************************************************************
//
// Ethernet_getAuxSnapshot().
//
//**********************************************************************
void Ethernet_getAuxSnapshotTrigId(uint32_t base, uint32_t *id)
{
    //
    // Parameter sanity check
    //
    ASSERT(EMAC_BASE == base);

    //
    // Trigger Identifier is only valid if the FIFO is not empty.
    // TODO: Confirm that the id and last aux remain programmed.
    //
    if(Ethernet_getDepthAuxSnapshotFIFO(base) > 0U)
    {
       *id = (HWREG(base + ETHERNET_O_MAC_TIMESTAMP_STATUS) &
             ETHERNET_MAC_TIMESTAMP_STATUS_ATSSTN_M) >>
            ETHERNET_MAC_TIMESTAMP_STATUS_ATSSTN_S;
    }
}

//**********************************************************************
//
// Ethernet_selectTargetInterruptOrPulsePPS().
//
//**********************************************************************
void Ethernet_selectTargetInterruptOrPulsePPS(uint32_t base,
                                              uint32_t ppsNum,
                                              uint32_t target)
{
    //
    // Parameter sanity check
    //
    ASSERT(EMAC_BASE == base);
    ASSERT(ETHERNET_MAC_PPS_OUT_INSTANCE_1 >= ppsNum);

    //
    // Program the target
    //
    switch(ppsNum)
    {
    case ETHERNET_MAC_PPS_OUT_INSTANCE_0:
        HWREG(base + ETHERNET_O_MAC_PPS_CONTROL) |=
             ((target & ETHERNET_MAC_PPS_CONTROL_TRGTMODSEL0_M) <<
              ETHERNET_MAC_PPS_CONTROL_TRGTMODSEL0_S);
        break;
    case ETHERNET_MAC_PPS_OUT_INSTANCE_1:
        HWREG(base + ETHERNET_O_MAC_PPS_CONTROL) |=
             ((target & ETHERNET_MAC_PPS_CONTROL_TRGTMODSEL1_M) <<
              ETHERNET_MAC_PPS_CONTROL_TRGTMODSEL1_S);
        break;
    }
}

//**********************************************************************
//
// Ethernet_setFixedModePPS().
//
//**********************************************************************
void Ethernet_setFixedModePPS(uint32_t base,
                              uint32_t freq)
{
    bool rollover;

    //
    // Parameter sanity check
    //
    ASSERT(EMAC_BASE == base);
    ASSERT(freq <= ETHERNET_MAC_PPS_CONTROL_PPSCTRL_PPS_OUTPUT_32768HZ);

    //
    // Program the fixed mode
    //
    HWREG(base + ETHERNET_O_MAC_PPS_CONTROL) |=
                            (ETHERNET_MAC_PPS_CONTROL_PPSEN0_PPS_FIXED_MODE <<
                             ETHERNET_MAC_PPS_CONTROL_PPSEN0);

    //
    // Is the clock running in digital or binary rollover mode?
    //
    rollover = ((bool)((uint32_t)0U !=
            (HWREG(base + (uint32_t)ETHERNET_O_MAC_TIMESTAMP_CONTROL) &
               (uint32_t) ETHERNET_MAC_TIMESTAMP_CONTROL_TSCTRLSSR)) ?
               true : false);

    //
    // Weed out some unsupported frequencies.  The hardware can't produce a
    // 1Hz output when we are in binary rollover mode and can't produce a
    // 32KHz output when we are digital rollover mode.
    //
    ASSERT(rollover ||
           (freq != ETHERNET_MAC_PPS_CONTROL_PPSCTRL_PPS_OUTPUT_1HZ));
    ASSERT(!rollover ||
           (freq != ETHERNET_MAC_PPS_CONTROL_PPSCTRL_PPS_OUTPUT_32768HZ));

    //
    // Adjust the supplied frequency if we are currently in binary rollover
    // mode where the control value generates an output that is twice as fast
    // as in digital rollover mode.
    //
    if((freq != ETHERNET_MAC_PPS_CONTROL_PPSCTRL_PPS_OUTPUT_SINGLE_PULSE) &&
       (!rollover))
    {
        freq--;
    }


    //
    // Program the intended frequency.
    //
    HWREG(base + ETHERNET_O_MAC_PPS_CONTROL) |=
        (freq << ETHERNET_MAC_PPS_CONTROL_PPSCTRL_PPSCMD_S);
}

//**********************************************************************
//
// Ethernet_setFlexibleModePPS().
//
//**********************************************************************
void Ethernet_setFlexibleModePPS(uint32_t base)
{
    //
    // Parameter sanity check
    //
    ASSERT(EMAC_BASE == base);

    //
    // Program flexible mode configuration
    //
    HWREG(base + ETHERNET_O_MAC_PPS_CONTROL) |=
                          (ETHERNET_MAC_PPS_CONTROL_PPSEN0_PPS_FLEXIBLE_MODE <<
                           ETHERNET_MAC_PPS_CONTROL_PPSEN0);
}

//**********************************************************************
//
// Ethernet_configurePPS().
//
//**********************************************************************
void Ethernet_configurePPS(uint32_t base,
                           uint32_t target,
                           uint32_t mode,
                           uint32_t fixedFreq)
{
    //
    // Save this instance number which will be used as argument in other
    // function calls later.
    //
    uint32_t instance = ETHERNET_MAC_PPS_OUT_INSTANCE_0;

    switch(target)
    {
    //
    // Target Interrupt only. No further configuration needed.
    //
    case ETHERNET_MAC_PPS_CONTROL_TRGTMODSEL_INTERRUPT:

        Ethernet_selectTargetInterruptOrPulsePPS(base, instance, target);
     break;

    //
    //  Target Pulse only and Pulse-Interrupt both.
    //  Further configuration for Fixed mode and Flexible mode needed.
    //
    case ETHERNET_MAC_PPS_CONTROL_TRGTMODSEL_PULSE:
    case ETHERNET_MAC_PPS_CONTROL_TRGTMODSEL_INTERRUPT_PULSE:

     //
     // Set target as pulse-only or pulse-interrupt.
     //
        Ethernet_selectTargetInterruptOrPulsePPS(base, instance, target);

     //
     // Set the pulse mode.
     //
     switch(mode)
     {
     case ETHERNET_MAC_PPS_CONTROL_PPSEN0_PPS_FIXED_MODE:

         Ethernet_setFixedModePPS(base, fixedFreq);
         break;

     case ETHERNET_MAC_PPS_CONTROL_PPSEN0_PPS_FLEXIBLE_MODE:

         Ethernet_setFlexibleModePPS(base);
         break;

     default:

         //
         // Erroneous Mode configuration
         //
         break;
     }


    default:

     //
     // Erroneous Target configuration.
     //
        break;
    }
}

//**********************************************************************
//
// Ethernet_setTargetTimePPS().
//
//**********************************************************************
void
Ethernet_setTargetTimePPS(uint32_t base, uint32_t ppsNum,
                          uint32_t seconds, uint32_t subSeconds)
{
    //
    // Parameter sanity check
    //
    ASSERT(EMAC_BASE == base);
    ASSERT(ETHERNET_MAC_PPS_OUT_INSTANCE_1 >= ppsNum);

    //
    // Wait for any previous write to complete.
    //
    while((uint32_t)0U !=
        (HWREG(base + ETHERNET_MAC_PPS_TARGET_TIME_NANOSECONDS +
                (ppsNum * 0x10U)) &
          ETHERNET_MAC_PPS_TARGET_TIME_NANOSECONDS_TRGTBUSY))
    {
        //
        // Wait a bit.
        //
    }

    //
    // Program the seconds and subseconds.
    //
    HWREG(base + ETHERNET_MAC_PPS_TARGET_TIME_NANOSECONDS +
          (ppsNum * (0x10U))) = subSeconds;
    HWREG(base + ETHERNET_MAC_PPS_TARGET_TIME_SECONDS +
          (ppsNum * (0x10U))) = seconds;

}

//**********************************************************************
//
// Ethernet_setPeriodPPS().
//
//**********************************************************************
void Ethernet_setPeriodPPS(uint32_t base,
                           uint32_t ppsNum,
                           uint32_t width,
                           uint32_t interval)
{
    //
    // Parameter sanity check
    //
    ASSERT(EMAC_BASE == base);
    ASSERT(ETHERNET_MAC_PPS_OUT_INSTANCE_1 >= ppsNum);

    //
    // Write the desired interval and width.
    //
    HWREG(base + ETHERNET_MAC_PPS_WIDTH + (ppsNum * (0x10U))) = width;
    HWREG(base + ETHERNET_MAC_PPS_INTERVAL + (ppsNum * (0x10U))) = interval;
}

//**********************************************************************
//
// Ethernet_setPeriodPPS().
//
//**********************************************************************
void Ethernet_setCmdPPS(uint32_t base,
                        uint32_t ppsNum,
                        uint32_t ppsCmd)
{
    //
    // Parameter sanity check
    //
    ASSERT(EMAC_BASE == base);
    ASSERT(ETHERNET_MAC_PPS_OUT_INSTANCE_1 >= ppsNum);
    ASSERT(ETHERNET_MAC_PPS_CONTROL_PPSCMD_COMMAND_CANCEL_STOP >= ppsCmd);


    //
    // Wait for any previous command to execute.
    //
    while(0U != (HWREG(base + ETHERNET_O_MAC_PPS_CONTROL) &
          ETHERNET_MAC_PPS_CONTROL_PPSCTRL_PPSCMD_M))
    {
        //
        // Wait a bit.
        //
    }

    //
    // Write the command to the PPS control register.
    //
    HWREG(base + ETHERNET_O_MAC_PPS_CONTROL) |= ppsCmd << ((ppsNum) * 8U);
}
//
//MDIO Related functions
//
void Ethernet_configureMDIO(uint32_t base,
                            uint32_t clockHigh,
                            uint32_t clockRange,
                            uint32_t clause45Enable
                            )
{
    HWREG(base + ETHERNET_O_MAC_MDIO_ADDRESS) =
                (clockRange << ETHERNET_MAC_MDIO_ADDRESS_CR_S) |
                (clockHigh << ETHERNET_MDIO_ADDRESS_HIGHCLK_ENABLE_S) |
                (clause45Enable << ETHERNET_MDIO_ADDRESS_C45E_S);
}

void Ethernet_configurePHYAddress(uint32_t base,
                                  uint8_t phyAddr)
{
    HWREG(base + ETHERNET_O_MAC_MDIO_ADDRESS) =
                        ((uint32_t)phyAddr <<
                         (uint32_t) ETHERNET_MAC_MDIO_ADDRESS_PA_S);
}
uint8_t Ethernet_getPHYMode(uint32_t base)
{
    uint8_t clause45enable;
    clause45enable = (HWREG(base +
                      ETHERNET_O_MAC_MDIO_ADDRESS) &
                      ETHERNET_MAC_MDIO_ADDRESS_C45E) >>
                      ETHERNET_MDIO_ADDRESS_C45E_S;
    return(clause45enable);
}
uint16_t Ethernet_readPHYRegister(uint32_t base,
                                 uint16_t regAddress)
{
    //
    //If this is a Clause45 PHY or Clause 22 PHY
    //
    if(0U != Ethernet_getPHYMode(base))
    {
        //
        //Clause 45 PHY
        // This shall also clear the existing Data before read
        //
        HWREG(base + ETHERNET_O_MAC_MDIO_DATA) =
                ((uint32_t)regAddress << (uint32_t)ETHERNET_MAC_MDIO_DATA_RA_S);
    }
    else
    {
        //
        //Clause 22 PHY
        //
        HWREG(base + ETHERNET_O_MAC_MDIO_ADDRESS) &=
                    ~ETHERNET_MAC_MDIO_ADDRESS_RDA_M;
        HWREG(base + ETHERNET_O_MAC_MDIO_ADDRESS) |=
                ((uint32_t)regAddress <<
                (uint32_t) ETHERNET_MAC_MDIO_ADDRESS_RDA_S);
    }
    //
    //Set the command as Read
    //
    HWREG(base + ETHERNET_O_MAC_MDIO_ADDRESS) |=
                ETHERNET_MAC_MDIO_ADDRESS_GOC_READ <<
                ETHERNET_MAC_MDIO_ADDRESS_GOC_0_S;
    //
    //Send the command to the PHY
    //
    HWREG(base + ETHERNET_O_MAC_MDIO_ADDRESS) |=
                ETHERNET_MAC_MDIO_ADDRESS_GB ;
    //
    //Wait till the GMII Busy is cleared by Module
    //
    while(0U != (HWREG(base + ETHERNET_O_MAC_MDIO_ADDRESS) &
                 ETHERNET_MAC_MDIO_ADDRESS_GB))
    {
    }
    return(HWREG(base + ETHERNET_O_MAC_MDIO_DATA) &
           ETHERNET_MAC_MDIO_DATA_GD_M);
}

void Ethernet_writePHYRegister(uint32_t base,
                               uint8_t regAddress,
                               uint16_t writeData)
{
     if(0U != Ethernet_getPHYMode(base))
    {
        //
        //Clause 45 PHY
        //
        HWREG(base + ETHERNET_O_MAC_MDIO_DATA) =
              ((uint32_t)regAddress << (uint32_t)ETHERNET_MAC_MDIO_DATA_RA_S);
    }
    else
    {
        //
        //Clause 22 PHY
        //
        HWREG(base + ETHERNET_O_MAC_MDIO_ADDRESS) &=
                                ~ETHERNET_MAC_MDIO_ADDRESS_RDA_M;
        HWREG(base + ETHERNET_O_MAC_MDIO_ADDRESS) |=
               ((uint32_t)regAddress  <<
               (uint32_t) ETHERNET_MAC_MDIO_ADDRESS_RDA_S);
    }
    //
    //Clear the existing data
    //
   HWREG(base + ETHERNET_O_MAC_MDIO_DATA) &= ~ETHERNET_MAC_MDIO_DATA_GD_M ;
   HWREG(base + ETHERNET_O_MAC_MDIO_DATA) |= writeData;
   //
   //Clearing GOC_0 and GOC_1
   //
   HWREG(base + ETHERNET_O_MAC_MDIO_ADDRESS) &=
   ~(ETHERNET_MAC_MDIO_ADDRESS_GOC_1 | ETHERNET_MAC_MDIO_ADDRESS_GOC_0);
    //
    //Set the command as Write
    //
    HWREG(base + ETHERNET_O_MAC_MDIO_ADDRESS) |=
                ETHERNET_MAC_MDIO_ADDRESS_GOC_WRITE <<
                ETHERNET_MAC_MDIO_ADDRESS_GOC_0_S;
    //
    //Send the command to the PHY
    //
    HWREG(base + ETHERNET_O_MAC_MDIO_ADDRESS) |=
                ETHERNET_MAC_MDIO_ADDRESS_GB ;
    //
    //Wait till the GMII Busy is cleared by Module
    //
    while(0U != (HWREG(base + ETHERNET_O_MAC_MDIO_ADDRESS) &
                 ETHERNET_MAC_MDIO_ADDRESS_GB))
    {
    }
}

void Ethernet_configureRevMIIAddress(uint32_t subSystembase,
                               uint8_t localPHYAddress,
                               uint8_t remotePHYAddress)
{


    HWREG( subSystembase + ETHERNETSS_O_REVMII_CTRL) =
                       ((((uint32_t)ETHERNET_SS_CTRLSTS_WRITE_KEY_VALUE <<
                         ETHERNETSS_REVMII_CTRL_WRITE_KEY_S) &
                         ETHERNETSS_REVMII_CTRL_WRITE_KEY_M) |
                        ((uint32_t)localPHYAddress <<
                         ETHERNETSS_REVMII_CTRL_REVMII_CORE_PHY_ADDR_S) |
                        ((uint32_t)remotePHYAddress <<
                         ETHERNETSS_REVMII_CTRL_REVMII_REMOTE_PHY_ADDR_S));

}
//
//VLAN Related Routines
//Function used to Set Register based VLAN Inclusion
//For Outer VLAN
//

void Ethernet_setFixedOuterVLANParams(uint32_t base,
                                                        uint16_t vlanTag,
                                                        uint8_t vlanTagControl,
                                                        uint8_t vlanType
                                                        )
{

//
//Clear the VLTI Field
//
    HWREG(base + ETHERNET_O_MAC_VLAN_INCL) &= ~ETHERNET_MAC_VLAN_INCL_VLTI;
//
//Program with the provided parameters
//
    HWREG(base + ETHERNET_O_MAC_VLAN_INCL) =
             (((vlanTag << ETHERNET_MAC_VLAN_INCL_VLT_S) &
                ETHERNET_MAC_VLAN_INCL_VLT_M ) |
              (ETHERNET_MAC_VLAN_INCL_VLP_STATIC <<
                ETHERNET_MAC_VLAN_INCL_VLP_S) |
              ((uint32_t )((uint32_t)vlanTagControl <<
                           ETHERNET_MAC_VLAN_INCL_VLC_S) &
                           ETHERNET_MAC_VLAN_INCL_VLC_M) |
              ((uint32_t)((uint32_t)vlanType <<
                           ETHERNET_MAC_VLAN_INCL_CSVL_S) &
                          ETHERNET_MAC_VLAN_INCL_CSVL));
}

//
//Function used to Set Register based VLAN Inclusion
//For Inner VLAN
//
void Ethernet_setFixedInnerVLANParams(uint32_t base,
                                        uint16_t vlanTag,
                                        uint8_t vlanTagControl,
                                        uint8_t vlanType
                                        )
{
    //
    //Clear the VLTI Field
    //
        HWREG(base + ETHERNET_O_MAC_INNER_VLAN_INCL) &=
        ~ETHERNET_MAC_INNER_VLAN_INCL_VLTI;
    //
    //Program with the provided parameters
    //
    HWREG(base + ETHERNET_O_MAC_INNER_VLAN_INCL) =
           (((((uint32_t)vlanTag) <<
             (uint32_t) ETHERNET_MAC_INNER_VLAN_INCL_VLT_S) &
             (uint32_t)ETHERNET_MAC_INNER_VLAN_INCL_VLT_M) |
            (((uint32_t)ETHERNET_MAC_VLAN_INCL_VLP_STATIC) <<
             (uint32_t)ETHERNET_MAC_INNER_VLAN_INCL_VLP_S) |
            ((((uint32_t)vlanTagControl) <<
             ((uint32_t) ETHERNET_MAC_INNER_VLAN_INCL_VLC_S)) &
              (uint32_t)ETHERNET_MAC_INNER_VLAN_INCL_VLC_M) |
            ((((uint32_t)vlanType) <<
                (uint32_t)ETHERNET_MAC_INNER_VLAN_INCL_CSVL_S) &
                ETHERNET_MAC_INNER_VLAN_INCL_CSVL));
}

//
//Routine to Set Outer VLAN in Descriptor based inclusion
//
void Ethernet_setOuterVLANTagSourceDynamic(uint32_t base)
{
    //
    //Set the VLTI Bit to select Context Descriptor source
    //
    HWREG(base + ETHERNET_O_MAC_VLAN_INCL) = ETHERNET_MAC_VLAN_INCL_VLTI;
  //
  //Also clear the VLP field to make the VLAN Tag control picked
  //from the context Descriptor
  //
      HWREG(base + ETHERNET_O_MAC_VLAN_INCL) &= ~ETHERNET_MAC_VLAN_INCL_VLP;
}
//
//Routine to Set Inner VLAN in Descriptor based inclusion
//

void Ethernet_setInnerVLANTagSourceDynamic(uint32_t base)
{
    //
    //Set the VLTI Bit to select Context Descriptor source
    //
    HWREG(base + ETHERNET_O_MAC_INNER_VLAN_INCL) =
    ETHERNET_MAC_INNER_VLAN_INCL_VLTI;
    //
    //Also clear the VLP field to make the VLAN Tag control picked
    //from the context Descriptor
    //
    HWREG(base + ETHERNET_O_MAC_INNER_VLAN_INCL) &=
    ~ETHERNET_MAC_INNER_VLAN_INCL_VLP;
}



void Ethernet_setVLANPerfectFilter(
    uint32_t base,
    uint8_t filterId,
    uint16_t vlanId,
    uint8_t vlanEnable,
    uint8_t vlanFilterMode,
    uint8_t vlanTypeComparisonEnable,
    uint8_t vlanType,
    uint8_t innerVLANEnabled,
    uint8_t dmaChannelEnable,
    uint8_t channelNum)
{
    //
    //First Write Filter configuration in to VLAN Tag Data Register
    //
     HWREG(base + ETHERNET_O_MAC_VLAN_TAG_DATA) =
                (((((uint32_t)vlanId) <<
                   ETHERNET_MAC_VLAN_TAG_DATA_DATA_15_0_S) &
                  (uint32_t)ETHERNET_MAC_VLAN_TAG_DATA_DATA_15_0_M) |
                 ((((uint32_t)vlanEnable) <<
                   (uint32_t) ETHERNET_MAC_VLAN_TAG_DATA_DATA_16_S) &
                   (uint32_t) ETHERNET_MAC_VLAN_TAG_DATA_DATA_16) |
                 ((((uint32_t) vlanFilterMode) <<
                   (uint32_t)ETHERNET_MAC_VLAN_TAG_DATA_DATA_17_S) &
                    (uint32_t)ETHERNET_MAC_VLAN_TAG_DATA_DATA_17) |
                 (((uint32_t)vlanTypeComparisonEnable <<
                   (uint32_t)ETHERNET_MAC_VLAN_TAG_DATA_DATA_18_S ) &
                   (uint32_t)ETHERNET_MAC_VLAN_TAG_DATA_DATA_18) |
                 ((((uint32_t)vlanType) <<
                   (uint32_t) ETHERNET_MAC_VLAN_TAG_DATA_DATA_19_S) &
                   (uint32_t)ETHERNET_MAC_VLAN_TAG_DATA_DATA_19) |
                 ((((uint32_t)innerVLANEnabled) <<
                   (uint32_t)ETHERNET_MAC_VLAN_TAG_DATA_DATA_20_S ) &
                    (uint32_t)ETHERNET_MAC_VLAN_TAG_DATA_DATA_20) |
                 ((((uint32_t)dmaChannelEnable) <<
                   (uint32_t)ETHERNET_MAC_VLAN_TAG_DATA_DATA_24_S) &
                   (uint32_t)ETHERNET_MAC_VLAN_TAG_DATA_DATA_24) |
                 ((((uint32_t)channelNum) <<
                   (uint32_t)ETHERNET_MAC_VLAN_TAG_DATA_DATA_25_S ) &
                   (uint32_t)ETHERNET_MAC_VLAN_TAG_DATA_DATA_25));
    //
    //Program the offset of the filter
    //
    HWREG(base + ETHERNET_O_MAC_VLAN_TAG_CTRL) |=
                   ((filterId << ETHERNET_MAC_VLAN_TAG_CTRL_OFS_S) &
                     ETHERNET_MAC_VLAN_TAG_CTRL_OFS_M);
//
//Set the Command Type to Write
//
 HWREG(base + ETHERNET_O_MAC_VLAN_TAG_CTRL) &= ~ETHERNET_MAC_VLAN_TAG_CTRL_CT;

//
//Give the command to Write
//
  HWREG(base + ETHERNET_O_MAC_VLAN_TAG_CTRL) |=
                ETHERNET_MAC_VLAN_TAG_CTRL_OB;

   //
  //Wait for the write to get over
  //
    while((HWREG(base + ETHERNET_O_MAC_VLAN_TAG_CTRL) &
           ETHERNET_MAC_VLAN_TAG_CTRL_OB) == ETHERNET_MAC_VLAN_TAG_CTRL_OB)
        {
        }
}
void Ethernet_setVLANHashFilter(
    uint32_t base,
    Ethernet_VlanRxFilter_InnerVLANEnable innerVLANEnabled,
    uint16_t hashMap
    )
{
    //
    //First Write Filter configuration in to VLAN Tag Data Register
    //
    HWREG(base + ETHERNET_O_MAC_VLAN_TAG_CTRL) |=
            (((((uint32_t)innerVLANEnabled) <<
              (uint32_t)ETHERNET_MAC_VLAN_TAG_CTRL_ERIVLT_S) &
              (uint32_t)ETHERNET_MAC_VLAN_TAG_CTRL_ERIVLT_M) |
             ETHERNET_MAC_VLAN_TAG_CTRL_VTHM_M);
    //
    //Program the Hash bit map in MAC_VLAN_Tag_Hash_Table
    //A bit of one implies that matching CRC will be filtered in
    //
    HWREG(base + ETHERNET_O_MAC_VLAN_HASH_TABLE) |=
            (hashMap << ETHERNET_MAC_VLAN_HASH_TABLE_VLHT_S);
}
void Ethernet_setDualVLAN(uint32_t base)
{
    //
    //MAC VLAN Tag Control Register setting
    //
    HWREG(base + ETHERNET_O_MAC_VLAN_TAG_CTRL) |=
            ETHERNET_MAC_VLAN_TAG_CTRL_EDVLP;
}
void Ethernet_enableInnerVLAN(uint32_t base)
{
    HWREG(base + ETHERNET_O_MAC_VLAN_TAG_CTRL) |=
            ETHERNET_MAC_VLAN_TAG_CTRL_ESVL;
}

void Ethernet_configureVLANCBTI(uint32_t base,
                                uint8_t channel,
                                uint16_t tag,
                                Ethernet_VlanType vlanType)
{
       //
       //First Enable Channel Based Tag insertion
       // Only then we can write to individual Tag registers
       //
       HWREG(base + ETHERNET_O_MAC_VLAN_INCL) |=
                       ETHERNET_MAC_VLAN_INCL_CBTI;
       //
       //Set the Tag Type C-VLAN(0x8100) or S-VLAN(0x88A8)
       //
       HWREG(base + ETHERNET_O_MAC_VLAN_INCL) &=
                   ~ETHERNET_MAC_VLAN_INCL_CSVL;
       HWREG(base + ETHERNET_O_MAC_VLAN_INCL) |=
                   vlanType << ETHERNET_MAC_VLAN_INCL_CSVL_S;
       //
       //Set the Command as Write
       //
       HWREG(base + ETHERNET_O_MAC_VLAN_INCL) |=
                     ETHERNET_MAC_VLAN_INCL_RDWR;
      //
      //The ADDR is the channel number to be Programmed
      //
      HWREG(base + ETHERNET_O_MAC_VLAN_INCL) &=
                  ~ETHERNET_MAC_VLAN_INCL_ADDR_M;
      HWREG(base + ETHERNET_O_MAC_VLAN_INCL) |=
                  channel << ETHERNET_MAC_VLAN_INCL_ADDR_S;
       //
       //Set the Tag value.This triggers write to the register
       //
       HWREG(base + ETHERNET_O_MAC_VLAN_INCL) &=
                       ~ETHERNET_MAC_VLAN_INCL_VLT_M;
       HWREG(base + ETHERNET_O_MAC_VLAN_INCL) |=
                       tag;
       //
       //Wait till the hardware finishes the write
       //
       while((HWREG(base + ETHERNET_O_MAC_VLAN_INCL) &
              ETHERNET_MAC_VLAN_INCL_BUSY) == ETHERNET_MAC_VLAN_INCL_BUSY)
       {
       }

}

uint32_t Ethernet_readVLANCBTI(uint32_t base,
                                    uint8_t channel,
                                    uint16_t tag,
                                    Ethernet_VlanType vlanType
                                    )
{
   //
   //First Enable Channel Based Tag insertion
   // Only then we can write to individual Tag registers
   //
   HWREG(base + ETHERNET_O_MAC_VLAN_INCL) |=
                   ETHERNET_MAC_VLAN_INCL_CBTI;

    //
    //The ADDR is the channel number to be Programmed
    //
    HWREG(base + ETHERNET_O_MAC_VLAN_INCL) &=
                ~ETHERNET_MAC_VLAN_INCL_ADDR_M;
    HWREG(base + ETHERNET_O_MAC_VLAN_INCL) |=
                channel << ETHERNET_MAC_VLAN_INCL_ADDR_S;
  //
  //Set the Command as Read
  //
   HWREG(base + ETHERNET_O_MAC_VLAN_INCL) &=
               ~ETHERNET_MAC_VLAN_INCL_RDWR;

   //
   //Wait till the hardware finishes the read
   //
   while((HWREG(base + ETHERNET_O_MAC_VLAN_INCL) &
          ETHERNET_MAC_VLAN_INCL_BUSY) == ETHERNET_MAC_VLAN_INCL_BUSY)
   {
   }
   return  (HWREG(base + ETHERNET_O_MAC_VLAN_INCL) &
                   ETHERNET_MAC_VLAN_INCL_VLT_M);
}

void Ethernet_setVlanTagInclusionFromDescriptor(uint32_t base)
{
    HWREG(base + ETHERNET_O_MAC_VLAN_INCL) |= ETHERNET_MAC_VLAN_INCL_VLTI;
}

void Ethernet_clearVlanTagInclusionFromDescriptor(uint32_t base)
{
    HWREG(base + ETHERNET_O_MAC_VLAN_INCL) &= ~ETHERNET_MAC_VLAN_INCL_VLTI;
}

void Ethernet_setInnerVlanTagInclusionFromDescriptor(uint32_t base)
{
    HWREG(base + ETHERNET_O_MAC_INNER_VLAN_INCL) |=
        ETHERNET_MAC_INNER_VLAN_INCL_VLTI;
}

void Ethernet_clearInnerVlanTagInclusionFromDescriptor(uint32_t base)
{
    HWREG(base + ETHERNET_O_MAC_INNER_VLAN_INCL) &=
        ~ETHERNET_MAC_INNER_VLAN_INCL_VLTI;
}

void Ethernet_setMACPacketFilter(uint32_t base,
                                 uint32_t flags)
{
    HWREG(base + ETHERNET_O_MAC_PACKET_FILTER) |= flags;
}

void Ethernet_clearMACPacketFilter(uint32_t base,
                                   uint32_t flags)
{
    HWREG(base + ETHERNET_O_MAC_PACKET_FILTER ) &= ~flags;
}

void Ethernet_setProgrammableWDTimeout(uint32_t base,
                                       uint8_t timeout)
{
    HWREG(base + ETHERNET_O_MAC_WATCHDOG_TIMEOUT) &=
        ~ETHERNET_MAC_WATCHDOG_TIMEOUT_WTO_M;
    HWREG(base + ETHERNET_O_MAC_WATCHDOG_TIMEOUT) |=
        (timeout | ETHERNET_MAC_WATCHDOG_TIMEOUT_PWE);
}

void Ethernet_setMACConfiguration(uint32_t base, uint32_t flags)
{
    HWREG(base + ETHERNET_O_MAC_CONFIGURATION) |= flags;
}
void Ethernet_clearMACConfiguration(uint32_t base, uint32_t flags)
{
    HWREG(base + ETHERNET_O_MAC_CONFIGURATION) &= ~flags;

}

uint32_t Ethernet_configureL3L4Filter(uint32_t base,
                Ethernet_L3_L4_FilterParams filterParams)
{
    Ethernet_L3_L4_Control  l3l4Control;
    if((0U != filterParams.layer3IPSrcAddressMatchEnable) ||
        (0U != filterParams.layer3IPDestAddressMatchEnable))
    {
    //
    //Check for IPV6
    //
            if(0U != filterParams.layer3ProtocolSel)
            {
                if((0U != filterParams.layer3IPDestAddressMatchEnable) &&
                   (0U != filterParams.layer3IPSrcAddressMatchEnable))
                {
                        //
                        //Both Source and Destination Filtering not possible
                        //for IPv6 in Ethernet Module
                        //only one 128 bit address configuration possible
                        //
                        return(ETHERNET_ERR_INVALID_PARAM);
                }
                else
                {
                    Ethernet_configureIPv6FilterAddress(base,
                        filterParams.filterid,
                        filterParams.layer3Address0,
                        filterParams.layer3Address1,
                        filterParams.layer3Address2,
                        filterParams.layer3Address3
                        );
                }

            }
            else
            {
                //
                //IPv4 Filter
                //
                if(0U !=  filterParams.layer3IPSrcAddressMatchEnable)
                {
                    Ethernet_configureIPv4FilterSourceAddress(base,
                        filterParams.filterid,
                        filterParams.layer3Address0);
                }
                if(0U != filterParams.layer3IPDestAddressMatchEnable)
                {
                    Ethernet_configureIPv4FilterDestinationAddress(base,
                        filterParams.filterid,
                        filterParams.layer3Address1);
                 }
            }
    }
    if(0U != filterParams.layer4SourcePortMatchEnable)
    {
        //
        //Program L4
        //
         Ethernet_configureLayer4FilterSrcAddress(base,
                filterParams.filterid,
                filterParams.layer4SourcePort
                );
    }
    if(0U != filterParams.layer4DestinationPortMatchEnable)
    {
         Ethernet_configureLayer4FilterDstAddress(base,
                filterParams.filterid,
                filterParams.layer4DestinationPort
                );
    }
    //
    //Program L3L4Filter control register structure
    //
    (void)memset(&l3l4Control, 0, sizeof(Ethernet_L3_L4_Control));

    //
    //There are no bit Shift and Mask Values so better to
    //in the xml file it is better to use structures to achieve
    //the programming easily
    //
    if(0U != filterParams.layer3ProtocolSel)
    {
        l3l4Control.L3PEN |= ETHERNET_MAC_L3_L4_CONTROL0_L3PEN0_ENABLE;
    }
    if(0U != filterParams.layer3IPSrcAddressMatchEnable)
    {
        l3l4Control.L3SAM = ETHERNET_MAC_L3_L4_CONTROL0_L3SAM0_ENABLE;
    }
    if(0U != filterParams.layer3IPDestAddressMatchEnable)
    {
        l3l4Control.L3DAM = ETHERNET_MAC_L3_L4_CONTROL0_L3DAM0_ENABLE;
    }
    //
    //For IPv4 Packets you can program both Layer3 and
    //
    if(0U == filterParams.layer3ProtocolSel)
    {
        l3l4Control.L3HSBM = filterParams.layer3SrcHigherBitsMask;
        l3l4Control.L3HDBM = filterParams.layer3DestHigherBitsMask;
    }
    else
     {
        //
        //For IPv6 Packets it is only one bit field
        //Lower 5 bits will go into HSBM register
        //
        if(0U != filterParams.layer3IPSrcAddressMatchEnable)
        {
            l3l4Control.L3HSBM = filterParams.layer3SrcHigherBitsMask & 0x1FU;
            l3l4Control.L3HDBM =
                ((filterParams.layer3SrcHigherBitsMask & 0x60U) >> 5U);
        }
        else if(0U != filterParams.layer3IPDestAddressMatchEnable)
        {
            l3l4Control.L3HSBM = filterParams.layer3DestHigherBitsMask & 0x1FU;
            l3l4Control.L3HDBM =
                ((filterParams.layer3DestHigherBitsMask & 0x60U) >> 5U);
        }
        else
            {
            //
            //Do Nothing
            //
            }
     }
    if(0U != filterParams.layer4ProtocolSel)
    {
        l3l4Control.L4PEN = ETHERNET_MAC_L3_L4_CONTROL0_L4PEN0_ENABLE;
    }
    if(0U != filterParams.layer4SourcePortMatchEnable)
    {
        l3l4Control.L4SPM = ETHERNET_MAC_L3_L4_CONTROL0_L4SPM0_ENABLE;
    }
    if(0U != filterParams.layer4DestinationPortMatchEnable)
    {
        l3l4Control.L4DPM = ETHERNET_MAC_L3_L4_CONTROL0_L4DPM0_ENABLE;
    }
    if(ETHERNET_DMA_CHANNELNUM_DISABLED != filterParams.dmaChannelEnable)
    {
        l3l4Control.DMACHEN = ETHERNET_MAC_L3_L4_CONTROL0_DMCHEN0_ENABLE;
    }
    l3l4Control.DMACHN = filterParams.dmaChannelNum;


    Ethernet_configureL3L4FilterControl(base,
                    filterParams.filterid,
                    *(uint32_t * ) &l3l4Control);
    return(ETHERNET_RET_SUCCESS);
}

void Ethernet_configureIPv6FilterAddress(uint32_t base,
                uint8_t filterid,
                uint32_t word0,
                uint32_t word1,
                uint32_t word2,
                uint32_t word3)
{
    HWREG(base + (ETHERNET_O_MAC_LAYER3_ADDR0_REG0 +
          ((uint32_t)filterid * 0x30U))) = word0;
    HWREG(base + (ETHERNET_O_MAC_LAYER3_ADDR1_REG0 +
          ((uint32_t)filterid * 0x30U))) = word1;
    HWREG(base + (ETHERNET_O_MAC_LAYER3_ADDR2_REG0 +
          ((uint32_t)filterid * 0x30U))) = word2;
    HWREG(base + (ETHERNET_O_MAC_LAYER3_ADDR3_REG0 +
          ((uint32_t)filterid * 0x30U))) = word3;
}

void Ethernet_configureIPv4FilterSourceAddress
                    (uint32_t base,
                      uint8_t filterid,
                      uint32_t address)
{
    //
    //Address 0 Register configures the Source addres filter
    //
    HWREG(base + (ETHERNET_O_MAC_LAYER3_ADDR0_REG0 +
          ((uint32_t)filterid * 0x30U))) = address;
}
void Ethernet_configureIPv4FilterDestinationAddress
            (uint32_t base,
            uint8_t filterid,
            uint32_t address)
{
    //
    //Address 1 Register configures the Destination addres filter
    //
    HWREG(base + (ETHERNET_O_MAC_LAYER3_ADDR1_REG0 +
          ((uint32_t)filterid * 0x30U))) = address;
}

void Ethernet_configureLayer4FilterSrcAddress(
            uint32_t base,
            uint8_t filterid,
            uint16_t srcAddress)
{
    HWREG(base + (ETHERNET_O_MAC_LAYER4_ADDRESS0 +
          ((uint32_t)filterid * 0x30U))) |=
                srcAddress << ETHERNET_MAC_LAYER4_ADDRESS0_L4SP0_S ;
}
void Ethernet_configureLayer4FilterDstAddress(
                        uint32_t base,
                        uint8_t filterid,
                        uint16_t dstAddress)
{
    HWREG(base + (ETHERNET_O_MAC_LAYER4_ADDRESS0 +
          ((uint32_t)filterid *0x30U)))|=
                ((uint32_t)dstAddress <<
                 (uint32_t)ETHERNET_MAC_LAYER4_ADDRESS0_L4DP0_S);
}

void Ethernet_configureL3L4FilterControl(
                uint32_t base,
                 uint8_t filterid,
                 uint32_t flags)
{
    HWREG(base + (ETHERNET_O_MAC_L3_L4_CONTROL0 +
          ((uint32_t)filterid *0x30U))) = flags;
}



void Ethernet_configureLPILSTimer(uint32_t base,
                                                        uint16_t lsTimer)
{
    HWREG(base + ETHERNET_O_MAC_LPI_TIMERS_CONTROL) &=
                        ((uint32_t)~ETHERNET_MAC_LPI_TIMERS_CONTROL_LST_M);


    HWREG(base + ETHERNET_O_MAC_LPI_TIMERS_CONTROL) |=
                    (((uint32_t)lsTimer <<
                      (uint32_t)ETHERNET_MAC_LPI_TIMERS_CONTROL_LST_S) &
                      ETHERNET_MAC_LPI_TIMERS_CONTROL_LST_M);
}

void Ethernet_configureLPITWTimer(uint32_t base,
                                                        uint16_t twTimer)
{

    HWREG(base + ETHERNET_O_MAC_LPI_TIMERS_CONTROL) &=
                        ( (uint32_t)(~ETHERNET_MAC_LPI_TIMERS_CONTROL_TWT_M));


    HWREG(base + ETHERNET_O_MAC_LPI_TIMERS_CONTROL) |=
                    (((uint32_t)twTimer <<
                      (uint32_t)ETHERNET_MAC_LPI_TIMERS_CONTROL_TWT_S) &
                     ETHERNET_MAC_LPI_TIMERS_CONTROL_TWT_M);
}

void Ethernet_configureLPIPhyLinkStatus(uint32_t base,
                                                                bool linkStatus)
{
    if(true == linkStatus)
    {
        HWREG(base + ETHERNET_O_MAC_LPI_CONTROL_STATUS) |=
                                ETHERNET_MAC_LPI_CONTROL_STATUS_PLS;
    }
    else
        {
        //
        //Clear PLS Bit
        //
            HWREG(base + ETHERNET_O_MAC_LPI_CONTROL_STATUS) &=
                                ~ETHERNET_MAC_LPI_CONTROL_STATUS_PLS;
        }
}

void Ethernet_configureEEETicCounter(uint32_t base,
                                                            uint16_t counter)
{
    HWREG(base + ETHERNET_O_MAC_1US_TIC_COUNTER) = counter;
}

void Ethernet_configureTxEEEAutomaticMode(uint32_t base)
{
    HWREG(base + ETHERNET_O_MAC_LPI_CONTROL_STATUS) |=
                           ETHERNET_MAC_LPI_CONTROL_STATUS_LPITXA;
    HWREG(base + ETHERNET_O_MAC_LPI_CONTROL_STATUS) |=
                           ETHERNET_MAC_LPI_CONTROL_STATUS_LPIATE;
}

void Ethernet_enableTxEEEMode(uint32_t base)
{
    HWREG(base + ETHERNET_O_MAC_LPI_CONTROL_STATUS) |=
                               ETHERNET_MAC_LPI_CONTROL_STATUS_LPIEN;

}

void Ethernet_disableTxEEEMode(uint32_t base)
{
    HWREG(base + ETHERNET_O_MAC_LPI_CONTROL_STATUS) &=
                               ~ETHERNET_MAC_LPI_CONTROL_STATUS_LPIEN;

}

void Ethernet_configureTxLpiEntryTimer(uint32_t base, uint32_t timer)
{
    HWREG(base + ETHERNET_O_MAC_LPI_ENTRY_TIMER) =
                    (timer & ETHERNET_MAC_LPI_ENTRY_TIMER_LPIET_M);

}

void Ethernet_enableEEEMagicPacketDetection(uint32_t base)
{
    HWREG(base + ETHERNET_O_MAC_PMT_CONTROL_STATUS) |=
        ETHERNET_MAC_PMT_CONTROL_STATUS_MGKPKTEN;
}

void Ethernet_disableEEEMagicPacketDetection(uint32_t base)
{
      HWREG(base + ETHERNET_O_MAC_PMT_CONTROL_STATUS) &=
            ~ETHERNET_MAC_PMT_CONTROL_STATUS_MGKPKTEN;
 }

void Ethernet_configureEEEClockGatingControl(uint32_t base,
        bool enableDisable)
{
    if(true == enableDisable)
        {
             HWREG(base + ETHERNET_O_MAC_LPI_CONTROL_STATUS) |=
                                   ETHERNET_MAC_LPI_CONTROL_STATUS_LPITCSE;
        }
    else
        {
            //
            //Disable TX Clock Gating
            //
           HWREG(base + ETHERNET_O_MAC_LPI_CONTROL_STATUS) &=
                                   ~ETHERNET_MAC_LPI_CONTROL_STATUS_LPITCSE;
        }
}

void Ethernet_configureRemoteWakeupFilter(uint32_t base,
                        uint32_t *filterSettings
                        )
{
    uint8_t i;
    ASSERT(filterSettings!= NULL);
    for(i = 0;i < ETHERNET_RWKUP_FILTER_NUM_WORDS;i++)
        {
            HWREG(base + ETHERNET_O_MAC_RWK_PACKET_FILTER) =
                filterSettings[i];
         }
}

void Ethernet_enableRemoteWakeup(uint32_t base)
{
    //
    //MAC Drops all the packets other than Remote Wakeup
    //When this API is called
    //
    HWREG(base + ETHERNET_O_MAC_PMT_CONTROL_STATUS) |=
        ETHERNET_MAC_PMT_CONTROL_STATUS_RWKPFE;
    //
    //This enables the event to be generated when the
    //Remote wake up packet is received
    //
   HWREG(base + ETHERNET_O_MAC_PMT_CONTROL_STATUS) |=
        ETHERNET_MAC_PMT_CONTROL_STATUS_RWKPKTEN;
    //
    //MAC Drops all packets till EEE Magic Packet or
    //Remote Wakeup packet is received
    //
       HWREG(base + ETHERNET_O_MAC_PMT_CONTROL_STATUS) |=
            ETHERNET_MAC_PMT_CONTROL_STATUS_PWRDWN;
}
void Ethernet_writeConfigPTPOffload(uint32_t base, uint32_t config)
{
    //
    // Parameter sanity check.
    //
    ASSERT(base == EMAC_BASE);

    HWREG(base + ETHERNET_O_MAC_PTO_CONTROL) = config;
}

uint32_t Ethernet_readConfigPTPOffload(uint32_t base)
{
    //
    // Parameter sanity check.
    //
    ASSERT(base == EMAC_BASE);

    return(HWREG(base + ETHERNET_O_MAC_PTO_CONTROL));
}

void Ethernet_writeLogMsgIntervalPTPOffload(uint32_t base, uint32_t config)
{
    //
    // Parameter sanity check.
    //
    ASSERT(base == EMAC_BASE);

    HWREG(base + ETHERNET_O_MAC_LOG_MESSAGE_INTERVAL) = config;
}

uint32_t Ethernet_readLogMsgIntervalPTPOffload(uint32_t base)
{
    //
    // Parameter sanity check.
    //
    ASSERT(base == EMAC_BASE);
    return(HWREG(base + ETHERNET_O_MAC_LOG_MESSAGE_INTERVAL));
}

void Ethernet_setPDelayReqMsgTriggerPTPOffload(uint32_t base)
{
    //
    // Parameter sanity check.
    //
    ASSERT(base == EMAC_BASE);

    HWREG(base + ETHERNET_O_MAC_PTO_CONTROL) |=
                                            ETHERNET_MAC_PTO_CONTROL_APDREQTRIG;
}

void Ethernet_setSyncMsgTriggerPTPOffload(uint32_t base)
{
    //
    // Parameter sanity check.
    //
    ASSERT(base == EMAC_BASE);

    HWREG(base + ETHERNET_O_MAC_PTO_CONTROL) |=
                                             ETHERNET_MAC_PTO_CONTROL_ASYNCTRIG;
}

void
Ethernet_enableDisablePTPOffload(uint32_t base,
                                 Ethernet_PTPOffloadEnableMode enableDisable)
{
    //
    // Parameter sanity check.
    //
    ASSERT(base == EMAC_BASE);

    uint32_t ptoConf = HWREG(base + ETHERNET_O_MAC_PTO_CONTROL);

    ptoConf = (ptoConf & (~ETHERNET_MAC_PTO_CONTROL_PTOEN)) | enableDisable;

    HWREG(base + ETHERNET_O_MAC_PTO_CONTROL) = ptoConf;
}

void Ethernet_setMsgSwitchesPTPOffload(uint32_t base,
                                       Ethernet_PTPOffloadModeType ptoModeType,
                                       void *ptoModeConf)
{

    uint32_t ptoConf;

    //
    // Parameter sanity check.
    //
    ASSERT(base == EMAC_BASE);
    ASSERT(NULL != ptoModeConf);

    ptoConf = Ethernet_readConfigPTPOffload(base);

    switch(ptoModeType)
    {
    case ETHERNET_PTO_DELAY_REQ_DELAY_RESP_GENERATION:
        ptoConf = (ptoConf & (~ETHERNET_MAC_PTO_CONTROL_DRRDIS)) |
                    (*((Ethernet_PTPOffloadDelayReqRespMode *) ptoModeConf));
        break;
    case ETHERNET_PTO_AUTO_SYNC_MESSAGE:
        ptoConf = (ptoConf & (~ETHERNET_MAC_PTO_CONTROL_ASYNCEN)) |
                    (*((Ethernet_PTPOffloadAutoSyncMode *) ptoModeConf));
        break;
    case ETHERNET_PTO_AUTO_P_DELAY_REQ_MESSAGE:
        ptoConf = (ptoConf & (~ETHERNET_MAC_PTO_CONTROL_APDREQEN)) |
                    (*((Ethernet_PTPOffloadAutoPDelayReqMode *) ptoModeConf));
        break;
    case ETHERNET_PTO_P_DELAY_RESP_GENERATION:
        ptoConf = (ptoConf & (~ETHERNET_MAC_PTO_CONTROL_PDRDIS)) |
                    (*((Ethernet_PTPOffloadPDelayRespMode *) ptoModeConf));
        break;
    default:
        //
        // Code should never hit this case.
        //
        break;
    }

    Ethernet_writeConfigPTPOffload(base, ptoConf);
}

void Ethernet_setDomainNumberPTPOffload(uint32_t base, uint8_t domainNumber)
{
    //
    // Parameter sanity check.
    //
    ASSERT(base == EMAC_BASE);

    uint32_t ptoConf;

    ptoConf = HWREG(base + ETHERNET_O_MAC_PTO_CONTROL);

    ptoConf = (ptoConf & (~ETHERNET_MAC_PTO_CONTROL_DN_M)) |
                ((domainNumber << ETHERNET_MAC_PTO_CONTROL_DN_S) &
                 ETHERNET_MAC_PTO_CONTROL_DN_M);

    HWREG(base + ETHERNET_O_MAC_PTO_CONTROL) = ptoConf;
}

void Ethernet_setSourcePortIdPTPOffload(uint32_t base,
                                        uint32_t spi0,
                                        uint32_t spi1,
                                        uint32_t spi2)
{
    //
    // Parameter sanity check.
    //
    ASSERT(base == EMAC_BASE);

    HWREG(base + ETHERNET_O_MAC_SOURCE_PORT_IDENTITY0) = spi0;

    HWREG(base + ETHERNET_O_MAC_SOURCE_PORT_IDENTITY1) = spi1;

    HWREG(base + ETHERNET_O_MAC_SOURCE_PORT_IDENTITY2) =
                                    (spi2 &
                                     ETHERNET_MAC_SOURCE_PORT_IDENTITY2_SPI2_M);
}

void Ethernet_setLogSyncIntervalPTPOffload(uint32_t base, uint8_t value)
{
    //
    // Parameter sanity check.
    //
    ASSERT(base == EMAC_BASE);

    uint32_t ptoConf;

    ptoConf = HWREG(base + ETHERNET_O_MAC_LOG_MESSAGE_INTERVAL);

    ptoConf = (ptoConf & (~ETHERNET_MAC_LOG_MESSAGE_INTERVAL_LSI_M)) |
                  ((value << ETHERNET_MAC_LOG_MESSAGE_INTERVAL_LSI_S) &
                   ETHERNET_MAC_LOG_MESSAGE_INTERVAL_LSI_M);

    HWREG(base + ETHERNET_O_MAC_LOG_MESSAGE_INTERVAL) = ptoConf;
}

void Ethernet_setDelaySyncRatioPTPOffload(uint32_t base, uint8_t value)
{
    //
    // Parameter sanity check.
    //
    ASSERT(base == EMAC_BASE);

    uint32_t ptoConf;

    ptoConf = HWREG(base + ETHERNET_O_MAC_LOG_MESSAGE_INTERVAL);

    ptoConf = (ptoConf & (~ETHERNET_MAC_LOG_MESSAGE_INTERVAL_DRSYNCR_M)) |
                  ((value << ETHERNET_MAC_LOG_MESSAGE_INTERVAL_DRSYNCR_S) &
                   ETHERNET_MAC_LOG_MESSAGE_INTERVAL_DRSYNCR_M);

    HWREG(base + ETHERNET_O_MAC_LOG_MESSAGE_INTERVAL) = ptoConf;
}

void Ethernet_setLogMinPDelayReqIntervalPTPOffload(uint32_t base, uint8_t value)
{
    //
    // Parameter sanity check.
    //
    ASSERT(base == EMAC_BASE);

    uint32_t ptoConf;

    ptoConf = HWREG(base + ETHERNET_O_MAC_LOG_MESSAGE_INTERVAL);

    ptoConf = (ptoConf & (~ETHERNET_MAC_LOG_MESSAGE_INTERVAL_LMPDRI_M)) |
              ((value << ETHERNET_MAC_LOG_MESSAGE_INTERVAL_LMPDRI_S) &
                ETHERNET_MAC_LOG_MESSAGE_INTERVAL_LMPDRI_M);

    HWREG(base + ETHERNET_O_MAC_LOG_MESSAGE_INTERVAL) = ptoConf;
}

void Ethernet_setConfigPTPOffload(uint32_t base,
        Ethernet_PTPOffloadConfigParams ptoConfigParams)
{
    Ethernet_setDomainNumberPTPOffload(base, ptoConfigParams.domainNumber);

    Ethernet_setMsgSwitchesPTPOffload(base,
                                      ETHERNET_PTO_AUTO_SYNC_MESSAGE,
                                      &ptoConfigParams.ptoAutoPtpSyncMode);
    Ethernet_setMsgSwitchesPTPOffload(base,
                                      ETHERNET_PTO_AUTO_P_DELAY_REQ_MESSAGE,
                                      &ptoConfigParams.ptoAutoPDelayReqMode);
    Ethernet_setMsgSwitchesPTPOffload(base,
        ETHERNET_PTO_DELAY_REQ_DELAY_RESP_GENERATION,
        &ptoConfigParams.ptoDelayReqRespMode);
    Ethernet_setMsgSwitchesPTPOffload(base,
        ETHERNET_PTO_P_DELAY_RESP_GENERATION,
        &ptoConfigParams.ptoPDelayRespMode);

    Ethernet_setSourcePortIdPTPOffload(base,
                                       ptoConfigParams.srcPortId.id0,
                                       ptoConfigParams.srcPortId.id1,
                                       ptoConfigParams.srcPortId.id2);

    Ethernet_setLogSyncIntervalPTPOffload(base,
            ptoConfigParams.logMsgIntervalConf.logSyncInterval);
    Ethernet_setDelaySyncRatioPTPOffload(base,
            ptoConfigParams.logMsgIntervalConf.delayReqToSyncRatio);

    Ethernet_setLogMinPDelayReqIntervalPTPOffload(base,
            ptoConfigParams.logMsgIntervalConf.logMinPdelayReqInterval);

}


void Ethernet_enableUDPChecksumUpdatePTP(uint32_t base)
{
    //
    // Parameter sanity check
    //
    ASSERT(EMAC_BASE == base);

    //
    // Program the target
    //
    HWREG(base + ETHERNET_O_MAC_TIMESTAMP_CONTROL) |=
                                        ETHERNET_MAC_TIMESTAMP_CONTROL_CSC;
}

void Ethernet_setSubNanosecIngressCorrectionPTP(uint32_t base,
                                                float nanoSeconds)
{
    uint32_t val;
    int32_t integerPart;
    float fractionPart;

    //
    // Parameter sanity check
    //
    ASSERT(EMAC_BASE == base);

    //
    // Ingress correction is always negative.
    //
    if(0  > nanoSeconds)
    {
        integerPart = (int) nanoSeconds;
        fractionPart = nanoSeconds - (float)integerPart;

        //
        // Programming the integer part using nanosecond ingress correction API
        //
        Ethernet_setIngressCorrectionPTP(base, integerPart);

        //
        // Sub nanosecond part (fraction part of the parameter) needs to be
        // processed separately.
        // Also, Ingress correction is always negative,
        // so complement form needs to
        // be programmed.
        //

        //
        // Fractional part (10^9 - nanoSeconds) or
        // Fractional part (2^31 - nanoSeconds) is equal to
        // (1 - fractional part of (nanoSeconds))
        // [Note: Here fractionPart will already be a negative value and
        // nanoSeconds is the absolute value.]
        // So in effect, there is no real dependency on Rollover Control.
        //
        fractionPart = (float) 1 + fractionPart;

        //
        // Scale the fraction part by 2^8
        //
        fractionPart *=
        (float) ETHERNET_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC_SCALAR;

        //
        // Get the integer part of the scaled value.
        //
        integerPart = (int) fractionPart;

        //
        // The least significant 8 bits of the fractional part
        // of the nanoSeconds value should be programmed
        // in the sub-nanoseconds register
        // Basically, Least significant 8 bits of the integer
        // part of the scaled
        // value needs to be programmed.
        //

        val = ((uint32_t)integerPart <<
               ETHERNET_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC_TSICSNS_S) &
              ETHERNET_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC_TSICSNS_M;

        HWREG(base + ETHERNET_O_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC) = val;
    }
}

void Ethernet_setSubNanosecEgressCorrectionPTP(uint32_t base,
                                               float nanoSeconds)
{
    uint32_t val;
    int32_t integerPart;
    float fractionPart;

    //
    // Parameter sanity check
    //
    ASSERT(EMAC_BASE == base);

    integerPart = (int) nanoSeconds;
    fractionPart = nanoSeconds - (float)integerPart;

    //
    // Programming the integer part using nanosecond ingress correction API
    //
    Ethernet_setEgressCorrectionPTP(base, integerPart);

    //
    // Sub nanosecond part (fraction part of the parameter) needs to be
    // processed separately.
    //

    //
    // Check if the nanoSeconds value is positive or negative. Accordingly,
    // complement form needs to be programmed.
    //
    if(0  > nanoSeconds)
    {
        //
        // Fractional part (10^9 - nanoSeconds) or
        // Fractional part (2^31 - nanoSeconds) is equal to
        // (1 - fractional part of (nanoSeconds))
        // [Note: Here fractionPart will already be a negative value and
        // nanoSeconds is the absolute value.]
        // So in effect, there is no real dependency on Rollover Control.
        //
        fractionPart = (float) 1 + fractionPart;
    }

    //
    // Scale the fraction part by 2^8
    //
    fractionPart *=
                  (float) ETHERNET_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC_SCALAR;

    //
    // Get the integer part of the scaled value.
    //
    integerPart = (int) fractionPart;

    //
    // The least significant 8 bits of the fractional part of the nanoSeconds
    // value should be programmed in the sub-nanoseconds register.
    // Basically, Least significant 8 bits of the integer part of the scaled
    // value needs to be programmed.
    //

    val = ((uint32_t)integerPart <<
           ETHERNET_MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC_TSECSNS_S) &
           ETHERNET_MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC_TSECSNS_M;

    HWREG(base + ETHERNET_O_MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC) = val;
}

void Ethernet_setIngressCorrectionPTP(uint32_t base, int32_t nanoSeconds)
{
    uint32_t rollOver;
    uint32_t val = 0x0U;

    //
    // Parameter sanity check
    //
    ASSERT(EMAC_BASE == base);

    //
    // Determine the type of Timestamp Rollover Control.
    //
    rollOver = HWREG(base + ETHERNET_O_MAC_TIMESTAMP_CONTROL) &
               ETHERNET_MAC_TIMESTAMP_CONTROL_TSCTRLSSR;

    //
    // Since Ingress Correction value is always negative,
    // if the value is zero or greater than zero,
    // then this API won't do anything
    //
    // TODO: If the value is positive or zero, there should be way to report
    // this error to the application.
    //
    if(0 > nanoSeconds)
    {
        //
        // Get the absolute value of the Ingress Correction value. Using
        // complement operation here.
        //
        nanoSeconds = ~nanoSeconds + 1;

        //
        // Ingress Correction is always negative. So set MSB to 1.
        //
        val = 0x80000000U;

        if(ETHERNET_MAC_TIMESTAMP_CONTROL_DIGITAL_ROLLOVER == rollOver)
        {
            //
            // 10^9 - <Ingress Correction value in nanoseconds (absolute)>
            //
            val |= (ETHERNET_MAC_TIMESTAMP_CONTROL_DIGITAL_ROLLOVER_MAX + 1) -
                   (uint32_t)(nanoSeconds);
        }
        else if(ETHERNET_MAC_TIMESTAMP_CONTROL_BINARY_ROLLOVER == rollOver)
        {
            //
            // 2^31 - <Ingress Correction value in nanoseconds>
            //
            val |= (ETHERNET_MAC_TIMESTAMP_CONTROL_BINARY_ROLLOVER_MAX + 1) -
                   (uint32_t)(nanoSeconds);
        }
    }
    else if(0 == nanoSeconds)
    {
       //
       // This is to make sure setting the ingress correction value to
       // 0 works.
       //
       val |= 0;
    }

    //
    // Program the target
    //
    HWREG(base + ETHERNET_O_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND) = val;
}

void Ethernet_setEgressCorrectionPTP(uint32_t base, int32_t nanoSeconds)
{
    uint32_t rollOver;
    uint32_t val = 0x0U;

    //
    // Parameter sanity check
    //
    ASSERT(EMAC_BASE == base);

    //
    // Determine the type of Timestamp Rollover Control.
    //
    rollOver = HWREG(base + ETHERNET_O_MAC_TIMESTAMP_CONTROL) &
              ETHERNET_MAC_TIMESTAMP_CONTROL_TSCTRLSSR;

    //
    // Egress Correction value is can be positive or negative.
    //
    if(0 > nanoSeconds)
    {
        //
        // Get the absolute value of the Egress Correction value, if it is
        // negative. Complementing the negative number to get a positive value.
        //
        nanoSeconds = ~nanoSeconds + 1;

        //
        // If the Egress Correction value is negative, set MSB of the value
        // to be programmed in the Register to 1.
        //
        val = 0x80000000U;

        if(ETHERNET_MAC_TIMESTAMP_CONTROL_DIGITAL_ROLLOVER == rollOver)
        {
            //
            // 10^9 - <Egress Correction value in nanoseconds>
            //
            val |= (ETHERNET_MAC_TIMESTAMP_CONTROL_DIGITAL_ROLLOVER_MAX + 1) -
                   (uint32_t)(nanoSeconds);
        }
        else if(ETHERNET_MAC_TIMESTAMP_CONTROL_BINARY_ROLLOVER == rollOver)
        {
            //
            // 2^31 - <Egress Correction value in nanoseconds>
            //
            val |= (ETHERNET_MAC_TIMESTAMP_CONTROL_BINARY_ROLLOVER_MAX + 1) -
                   (uint32_t)(nanoSeconds);
        }
    }
    else
    {
        /*
         * TODO: Range check for Digital and Binary Rollover is not implemented
         */
        val|= nanoSeconds;
    }

    //
    // Program the target
    //
    HWREG(base + ETHERNET_O_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND) = val;
}

void Ethernet_setAsymEgressCorrectionPTP(uint32_t base,
                                         float nanoSeconds)
{
    uint32_t val;

    //
    // Parameter sanity check
    //
    ASSERT(EMAC_BASE == base);
    ASSERT(0 != nanoSeconds);

    //
    // Egress asymmetry value is always subtracted from the correction
    // field in the outgoing packet.
    //
    if(0 > nanoSeconds)
    {
        val = (-nanoSeconds) * ETHERNET_MAC_TIMESTAMP_ASYM_CORR_SCALAR;
    }
    else
    {
        val = nanoSeconds * ETHERNET_MAC_TIMESTAMP_ASYM_CORR_SCALAR;
        val = ~val + 1;
    }

    HWREG(base + ETHERNET_O_MAC_TIMESTAMP_EGRESS_ASYM_CORR) = val;
}

void Ethernet_setAsymIngressCorrectionPTP(uint32_t base,
                                          float nanoSeconds)
{
    uint32_t val;

    //
    // Parameter sanity check
    //
    ASSERT(EMAC_BASE == base);
    ASSERT(0 != nanoSeconds);

    //
    // Egress asymmetry value is always subtracted from the correction
    // field in the outgoing packet.
    //
    if(0 > nanoSeconds)
    {
        val = (-nanoSeconds) * ETHERNET_MAC_TIMESTAMP_ASYM_CORR_SCALAR;
        val = ~val + 1;
    }
    else
    {
        val = nanoSeconds * ETHERNET_MAC_TIMESTAMP_ASYM_CORR_SCALAR;
    }

    HWREG(base + ETHERNET_O_MAC_TIMESTAMP_INGRESS_ASYM_CORR) = val;
}

void Ethernet_getSysTimeWithHigherWordPTP(uint32_t base,
                                          uint32_t *higherWord,
                                          uint32_t *seconds,
                                          uint32_t *subSeconds)
{
    uint32_t timeSource;

    //
    // Parameter sanity check
    //
    ASSERT(EMAC_BASE == base);
    ASSERT(NULL != higherWord);
    ASSERT(NULL != seconds);
    ASSERT(NULL != subSeconds);

    //
    // Determine the System Time Source.
    //
    timeSource = HWREG(base + ETHERNET_O_MAC_TIMESTAMP_CONTROL) &
                 ETHERNET_MAC_TIMESTAMP_CONTROL_ESTI;

    if(ETHERNET_MAC_TIMESTAMP_SYSTEM_TIME_SOURCE_INTERNAL == timeSource)
    {
        //
        // For Internal time source, Higher Word Register is also valid.
        // So, read the Higher Word Register.
        //
        *higherWord =
                (HWREG(base + ETHERNET_O_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS) &
                 ETHERNET_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS_TSHWR_M) >>
                ETHERNET_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS_TSHWR_S ;

    }
    else if(ETHERNET_MAC_TIMESTAMP_SYSTEM_TIME_SOURCE_EXTERNAL == timeSource)
    {
        //
        // For external time source, only 64 bits are valid. Flag this to the
        // application in the higherWord variable itself.
        //
        *higherWord = ETHERNET_MAC_SYSTEM_TIME_HIGHER_WORD_NOT_VALID;

    }

    //
    // Get the seconds and sub-seconds values with the standard driver.
    //
    Ethernet_getSysTimePTP(base, seconds, subSeconds);
}

void Ethernet_getMACAddr(uint32_t base,
    uint8_t instanceNum,
    uint32_t *MACAddrHigh,
    uint32_t *MACAddrLow)
{
    //
    //Return the Address alone.Mask out Enable bit
    //MAC Address registers are offset by 8 bytes
    //
      *MACAddrHigh = HWREG(base + ETHERNET_O_MAC_ADDRESS0_HIGH +
                           instanceNum * 0x8) & ~ETHERNET_MAC_ADDRESS0_HIGH_AE;
      *MACAddrLow = HWREG(base + ETHERNET_O_MAC_ADDRESS0_LOW +
                          instanceNum * 0x8);
}


