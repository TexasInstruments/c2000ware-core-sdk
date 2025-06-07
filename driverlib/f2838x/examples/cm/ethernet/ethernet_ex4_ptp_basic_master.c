//#############################################################################
//
// FILE:   ethernet_ex4_ptp_basic_master.c
//
// TITLE:  Ethernet PTP Basic Master Example
//
//! \addtogroup driver_example_cm_list
//! <h1> Ethernet PTP Basic Master </h1>
//!
//! This example configures the device in IEEE PTPv2 Master mode and then
//! periodically sends Sync packets to the slave. On receiving the DelayReq
//! packets from the slave, the master also sends out the DelayResp packets.
//!
//! \b External \b Connections \n
//! This example programs the Ethernet module in PTP Basic Master mode.
//! The example project \e Ethernet \e PTP \e Basic \e Slave is intended to
//! be used along with this project to see the whole PTP Protocol state in
//! action. The second device is configured as \e Slave and both devices in
//! conjunction exchange Sync, DelayReq and DelayResp packets.
//!
//! Refer to the C28x CPU1 code of ethernet_config_c28x project for configuring
//! the PTP clock that drives the system time counter on the Ethernet module.
//!
//! \b Watch \b Variables \n
//!  - gPtpMasterState
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

#include "driverlib_cm.h"
#include "string.h"
#include "cm.h"
//
// This frequency is actually set in the c28x side code. If it is changed
// there, then the following value also needs to be updated since the
// timestamping module is initialized with the following values.
// Default value is 100 MHz.
//
#define PTP_REF_CLOCK_FREQ   100000000
#define PTP_REF_CLOCK_PERIOD 1000000000/PTP_REF_CLOCK_FREQ

static Ethernet_Handle emac_handle;
#define PACKET_LENGTH 200

#define ETHERNET_NO_OF_RX_PACKETS   8U
#define ETHERNET_MAX_PACKET_LENGTH  PACKET_LENGTH
#define NUM_PACKET_DESC_RX_APPLICATION 8U

#define PTP_HEADER_OFFSET   14U

uint32_t Ethernet_numRxCallbackCustom = 0;
uint32_t releaseTxCount = 0;
Ethernet_Pkt_Desc  pktDescriptorRXCustom[NUM_PACKET_DESC_RX_APPLICATION];
extern uint32_t Ethernet_numGetPacketBufferCallback;
extern Ethernet_Device Ethernet_device_struct;

uint8_t gMsgBuf[PACKET_LENGTH] = {0};
Ethernet_Pkt_Desc gPktDesc;

//
// Globals
//
uint8_t Ethernet_rxBuffer[ETHERNET_NO_OF_RX_PACKETS *
                          ETHERNET_MAX_PACKET_LENGTH];
// Network related definitions as follows
//

//
// Taking care of network byte order conversions using these macros.
//
#define PP_HTONS(x) ((uint16_t)((((x) & (uint16_t)0x00ffU) << 8) |             \
                     (((x) & (uint16_t)0xff00U) >> 8)))
#define PP_NTOHS(x) PP_HTONS(x)
#define PP_HTONL(x) ((((x) & (uint32_t)0x000000ffUL) << 24) |                  \
                     (((x) & (uint32_t)0x0000ff00UL) <<  8) |                  \
                     (((x) & (uint32_t)0x00ff0000UL) >>  8) |                  \
                     (((x) & (uint32_t)0xff000000UL) >> 24))
#define PP_NTOHL(x) PP_HTONL(x)
#define flip16(x) PP_HTONS(x)
#define flip32(x) PP_HTONL(x)


//
// Following definitions and prototypes are specific to the PTP state machine
// and have been adapted from the IEEE 1588 standard spec.
//

#define PTP_TWO_STEP                            0x02
#define PTP_UUID_LENGTH                         6
#define CLOCK_IDENTITY_LENGTH                   8
#define FLAG_FIELD_LENGTH                       2

#define HEADER_LENGTH                           34
#define ANNOUNCE_LENGTH                         64
#define SYNC_LENGTH                             44
#define FOLLOW_UP_LENGTH                        44
#define PDELAY_REQ_LENGTH                       54
#define DELAY_REQ_LENGTH                        44
#define DELAY_RESP_LENGTH                       54
#define PDELAY_RESP_LENGTH                      54
#define PDELAY_RESP_FOLLOW_UP_LENGTH            54
#define MANAGEMENT_LENGTH                       48

typedef enum {FALSE=0, TRUE} Boolean;
typedef char Octet;
typedef signed char Integer8;
typedef signed short Integer16;
typedef signed int Integer32;
typedef unsigned char UInteger8;
typedef unsigned short UInteger16;
typedef unsigned int UInteger32;
typedef unsigned short Enumeration16;
typedef unsigned char Enumeration8;
typedef unsigned char Enumeration4;
typedef unsigned char UInteger4;
typedef unsigned char Nibble;

//
// brief Implementation specific of Integer64 type
//
typedef struct {
    unsigned int lsb;
    int msb;
} Integer64;

typedef struct {
    unsigned int lsb;
    unsigned short msb;
} UInteger48;

typedef struct  {
    UInteger48 secondsField;
    UInteger32 nanosecondsField;
} Timestamp;

//
// brief Time structure to handle Linux time information
//
typedef struct {
    Integer32 seconds;
    Integer32 nanoseconds;
} TimeInternal;

//
// brief The ClockIdentity type identifies a clock
//
typedef Octet ClockIdentity[CLOCK_IDENTITY_LENGTH];

//
// brief The PortIdentity identifies a PTP port.
//
typedef struct {
    ClockIdentity clockIdentity;
    UInteger16 portNumber;
} PortIdentity;

//
// brief The common header for all PTP messages (Table 18 of the spec)
//

//
// Message header
//
typedef struct {
    Nibble transportSpecific;
    Enumeration4 messageType;
    UInteger4 versionPTP;
    UInteger16 messageLength;
    UInteger8 domainNumber;
    Octet flagField[2];
    Integer64 correctionfield;
    PortIdentity sourcePortIdentity;
    UInteger16 sequenceId;
    UInteger8 controlField;
    Integer8 logMessageInterval;
} MsgHeader;

typedef struct
{
    PortIdentity portIdentity;
    Octet port_uuid_field[PTP_UUID_LENGTH];
    Timestamp syncTimestamp;
    Timestamp delayReqRecvTimestamp;
    uint16_t syncSeqId;
    uint16_t portNumber;
    Boolean syncTimestampAvailable;
    Boolean sendingDelayResp;
    MsgHeader delayReqHeader;
} PTPMasterState;
PTPMasterState gPtpMasterState = {0};

//
// brief PTP Messages
//
enum {
    SYNC=0x0,
    DELAY_REQ=0x1,
    FOLLOW_UP = 0x8,
    DELAY_RESP = 0x9,
};

//
// Function prototypes used in this example
//

void fromInternalTime(TimeInternal * internal, Timestamp * external);

void msgPackHeader(Octet * buf, PTPMasterState *ptpMasterState);

void msgPackSync(Octet * buf, PTPMasterState *ptpMasterState);

void msgPackFollowUp(Octet * buf, PTPMasterState *ptpMasterState);

void msgPackDelayResp(Octet * buf, PTPMasterState *ptpMasterState);

void msgUnpackHeader(Octet * buf, MsgHeader * header);

void InitConstants(PTPMasterState *ptpMasterState);

void sendMessage(Octet * msg,
                 uint32_t messageType,
                 PTPMasterState * ptpMasterState,
                 Ethernet_Pkt_Desc * pktDesc);

Ethernet_Pkt_Desc* Ethernet_getPacketBufferCustom(void);

Ethernet_Pkt_Desc* Ethernet_receivePacketCallbackCustom(
        Ethernet_Handle handleApplication,
        Ethernet_Pkt_Desc *pPacket);

void Ethernet_releaseTxPacketBufferCustom(
        Ethernet_Handle handleApplication,
        Ethernet_Pkt_Desc *pPacket);

main(void)
{
    Ethernet_InitConfig *pInitCfg;
    uint32_t i;
    uint32_t varPtpConfig = 0;
    Ethernet_InitInterfaceConfig initInterfaceConfig;
    uint32_t timeSec;
    uint32_t timeNanosec;
    float subSecondInc;

    //
    // Initialize device clock and peripherals
    //
    CM_init();

    initInterfaceConfig.ssbase = EMAC_SS_BASE;
    initInterfaceConfig.enet_base = EMAC_BASE;
    initInterfaceConfig.phyMode = ETHERNET_SS_PHY_INTF_SEL_MII;
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

    pInitCfg->pfcbFreePacket = &Ethernet_releaseTxPacketBufferCustom;
    pInitCfg->pfcbRxPacket = &Ethernet_receivePacketCallbackCustom;
    pInitCfg->pfcbGetPacket = &Ethernet_getPacketBufferCustom;

    varPtpConfig = (0 << ETHERNET_MAC_TIMESTAMP_CONTROL_SNAPTYPSEL_S) |
                    ETHERNET_MAC_TIMESTAMP_CONTROL_TSCTRLSSR |
                    ETHERNET_MAC_TIMESTAMP_CONTROL_TSMSTRENA |
                    ETHERNET_MAC_TIMESTAMP_CONTROL_TSEVNTENA |
                    ETHERNET_MAC_TIMESTAMP_CONTROL_TSVER2ENA |
                    ETHERNET_MAC_TIMESTAMP_CONTROL_TSIPENA;

    //
    // Subsecond increment is added to the systime counter every ptp clock tick
    // hence for Digital rollover, it is simply the time period of the clock
    // tick.
    //
    subSecondInc = PTP_REF_CLOCK_PERIOD;

    Ethernet_setConfigTimestampPTP(EMAC_BASE, varPtpConfig, subSecondInc);
    Ethernet_enableSysTimePTP(EMAC_BASE);

    //
    // Start the system with a random value.
    //
    Ethernet_setSysTimePTP(EMAC_BASE, 0x4132EDCA, 0x25a5a5a5);

    //
    //Assign the Buffer to be used by the Low level driver for receiving
    //Packets. This should be accessible by the Ethernet DMA
    //
    pInitCfg->rxBuffer = Ethernet_rxBuffer;
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

    Ethernet_setMACAddr(EMAC_BASE,
                        0,
                        0x00000506U,
                        0x01030304U,
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

    Ethernet_selectTargetInterruptOrPulsePPS(
                        EMAC_BASE,
                        ETHERNET_MAC_PPS_OUT_INSTANCE_0,
                        ETHERNET_MAC_PPS_CONTROL_TRGTMODSEL_INTERRUPT);

    //
    // We need to set a standard defined Multicast address : 01:1B:19:00:00:00
    // as the Destination address in the ethernet frame and that is how the
    // receiver will recognize it as a valid PTP over Ethernet packet.
    //
    i=0; *((uint32_t *)gMsgBuf + i) = 0x00191B01;
    i++; *((uint32_t *)gMsgBuf + i)  = 0xF7880000;

    InitConstants(&gPtpMasterState);

    while(1)
    {
        //
        // Use the system time counter to send the sync + followup messages
        // every one second.
        //
        Ethernet_getSysTimePTP(EMAC_BASE, &timeSec, &timeNanosec);
        Ethernet_setTargetTimePPS(EMAC_BASE, ETHERNET_MAC_PPS_OUT_INSTANCE_0,
                                  timeSec + 1, timeNanosec);

        //
        // Waiting till the target time that we set above is reached.
        // We're using the PPSOUT instance 0 as the timer.
        //
        while(((HWREG(EMAC_BASE + ETHERNET_O_MAC_TIMESTAMP_STATUS)) &
                (ETHERNET_MAC_TIMESTAMP_STATUS_TSTARGT0)) == 0);

        //
        // Save the state. We want to capture the timestamp of the next SYNC
        // packet that is being sent.
        //
        gPtpMasterState.syncTimestampAvailable = FALSE;

        //
        // Send out the SYNC packet.
        //
        sendMessage((Octet *)gMsgBuf, SYNC, &gPtpMasterState, &gPktDesc);

        //
        //  Wait till the latest sync timestamp is captured. As soon as the
        //  timestamp for the SYNC packet going out is captured, this flag
        //  will be set to TRUE by the application.
        //
        while(gPtpMasterState.syncTimestampAvailable == FALSE);

        //
        // Since the timestamp for the last SYNC packet has been captured,
        // send out the associated FOLLOW-UP packet.
        //
        sendMessage((Octet *)gMsgBuf, FOLLOW_UP, &gPtpMasterState, &gPktDesc);
    }
}

void
fromInternalTime(TimeInternal * internal, Timestamp * external)
{
    external->secondsField.lsb = internal->seconds;
    external->nanosecondsField = internal->nanoseconds;
    external->secondsField.msb = 0;
}

//
// Pack header message into OUT buffer of ptpClock
//
void
msgPackHeader(Octet * buf, PTPMasterState *ptpMasterState)
{
    Nibble transport = 0x80;

    //
    // (spec annex D)
    //
    *(UInteger8 *) (buf + 0) = transport;

    //
    // PTPv2
    //
    *(UInteger4 *) (buf + 1) = 0x2;

    //
    // Default domain number is 0.
    //
    *(UInteger8 *) (buf + 4) = 0;

    if (PTP_TWO_STEP)
        *(UInteger8 *) (buf + 6) = PTP_TWO_STEP;

    //
    // correctionField
    //
    memset((buf + 8), 0, 8);

    //
    // sourcePortIdentity first 8 octets
    //
    memcpy((buf + 20), ptpMasterState->portIdentity.clockIdentity,
           CLOCK_IDENTITY_LENGTH);

    //
    // sourcePortIdentity last 2 octets
    //
    *(UInteger16 *) (buf + 28) =
            flip16(ptpMasterState->portIdentity.portNumber);

    //
    // Default value(spec Table 24)
    //
    *(UInteger8 *) (buf + 33) = 0x7F;
}

//
// Pack SYNC message into OUT buffer of ptpClock
//
void
msgPackSync(Octet * buf, PTPMasterState *ptpMasterState)
{
    msgPackHeader(buf, ptpMasterState);

    //
    // changes in header
    //
    *(char *)(buf + 0) = *(char *)(buf + 0) & 0xF0;

    //
    // RAZ messageType
    //
    *(char *)(buf + 0) = *(char *)(buf + 0) | 0x00; /* Table 19 */

    //
    // messageLength
    //
    *(UInteger16 *) (buf + 2) = flip16(SYNC_LENGTH);

    //
    // Sequence Id
    //
    *(UInteger16 *) (buf + 30) =
            flip16(ptpMasterState->syncSeqId);

    //
    // controlField
    //
    *(UInteger8 *) (buf + 32) = 0x00;   /* Table 23 */

    //
    // logMessageInterval
    //
    *(Integer8 *) (buf + 33) = 0; // We'll send sync every second

    if(!PTP_TWO_STEP)
    {
        //
        // Sync message
        //
        *(UInteger16 *) (buf + 34) =
                flip16(ptpMasterState->syncTimestamp.secondsField.msb);
        *(UInteger32 *) (buf + 36) =
                flip32(ptpMasterState->syncTimestamp.secondsField.lsb);
        *(UInteger32 *) (buf + 40) =
                flip32(ptpMasterState->syncTimestamp.nanosecondsField);
    }
}

//
// pack Follow_up message into OUT buffer of ptpClock
//
void
msgPackFollowUp(Octet * buf, PTPMasterState *ptpMasterState)
{
    msgPackHeader(buf, ptpMasterState);

    //
    // changes in header
    //
    *(char *)(buf + 0) = *(char *)(buf + 0) & 0xF0;

    //
    // RAZ messageType
    //
    *(char *)(buf + 0) = *(char *)(buf + 0) | 0x08; /* Table 19 */

    //
    // messageLength
    //
    *(UInteger16 *) (buf + 2) = flip16(FOLLOW_UP_LENGTH);

    //
    // Sequence Id
    //
    *(UInteger16 *) (buf + 30) =
            flip16(ptpMasterState->syncSeqId);

    //
    // controlField
    //
    *(UInteger8 *) (buf + 32) = 0x02;   /* Table 23 */

    //
    // logMessageInterval
    //
    *(Integer8 *) (buf + 33) = 0;   // we're sending sync every one second.

    //
    // Follow_up message
    //
    *(UInteger16 *) (buf + 34) =
            flip16(ptpMasterState->syncTimestamp.secondsField.msb);
    *(UInteger32 *) (buf + 36) =
            flip32(ptpMasterState->syncTimestamp.secondsField.lsb);
    *(UInteger32 *) (buf + 40) =
            flip32(ptpMasterState->syncTimestamp.nanosecondsField);
}

//
// pack delayResp message into OUT buffer of ptpClock
//
void
msgPackDelayResp(Octet * buf, PTPMasterState *ptpMasterState)
{
    msgPackHeader(buf, ptpMasterState);

    //
    // changes in header
    // Transport | messageType
    //
    *(char *)(buf + 0) = *(char *)(buf + 0) & 0xF0;

    //
    // RAZ messageType
    //
    *(char *)(buf + 0) = *(char *)(buf + 0) | 0x09; /* Table 19 */

    //
    // messageLength
    //
    *(UInteger16 *) (buf + 2) = flip16(DELAY_RESP_LENGTH);

    //
    // domain Number
    //
    *(UInteger8 *) (buf + 4) = ptpMasterState->delayReqHeader.domainNumber;

    //
    // Sequence Id
    //
    *(UInteger16 *) (buf + 30) =
            flip16(ptpMasterState->delayReqHeader.sequenceId);

    //
    // controlField
    //
    *(UInteger8 *) (buf + 32) = 0x03; /* Table 23 */

    //
    // logMessageInterval
    //
    *(Integer8 *) (buf + 33) = 0; /* Table 24 */

    *(UInteger16 *) (buf + 34) =
        flip16(ptpMasterState->delayReqRecvTimestamp.secondsField.msb);
    *(UInteger32 *) (buf + 36) =
        flip32(ptpMasterState->delayReqRecvTimestamp.secondsField.lsb);
    *(UInteger32 *) (buf + 40) =
       flip32(ptpMasterState->delayReqRecvTimestamp.nanosecondsField);
    memcpy((buf + 44),
           ptpMasterState->delayReqHeader.sourcePortIdentity.clockIdentity,
           CLOCK_IDENTITY_LENGTH);
    *(UInteger16 *) (buf + 52) =
        flip16(ptpMasterState->delayReqHeader.sourcePortIdentity.portNumber);
}

//
// Unpack Header from IN buffer to msgTmpHeader field
//
void
msgUnpackHeader(Octet * buf, MsgHeader * header)
{
    header->transportSpecific = (*(Nibble *) (buf + 0)) >> 4;
    header->messageType = (*(Enumeration4 *) (buf + 0)) & 0x0F;
    header->versionPTP = (*(UInteger4 *) (buf + 1)) & 0x0F;

    //
    // force reserved bit to zero if not
    //
    header->messageLength = flip16(*(UInteger16 *) (buf + 2));
    header->domainNumber = (*(UInteger8 *) (buf + 4));
    memcpy(header->flagField, (buf + 6), FLAG_FIELD_LENGTH);
    memcpy(&header->correctionfield.msb, (buf + 8), 4);
    memcpy(&header->correctionfield.lsb, (buf + 12), 4);
    header->correctionfield.msb = flip32(header->correctionfield.msb);
    header->correctionfield.lsb = flip32(header->correctionfield.lsb);
    memcpy(header->sourcePortIdentity.clockIdentity, (buf + 20),
           CLOCK_IDENTITY_LENGTH);
    header->sourcePortIdentity.portNumber =
        flip16(*(UInteger16 *) (buf + 28));
    header->sequenceId = flip16(*(UInteger16 *) (buf + 30));
    header->controlField = (*(UInteger8 *) (buf + 32));
    header->logMessageInterval = (*(Integer8 *) (buf + 33));
}

void InitConstants(PTPMasterState *ptpMasterState)
{
    uint32_t mac_low,mac_high, i, j;
    uint8_t *pucTemp;

    Ethernet_getMACAddr(EMAC_BASE, 0, &mac_high, &mac_low);

    pucTemp = (uint8_t *)&mac_low;
    ptpMasterState->port_uuid_field[0] = pucTemp[0];
    ptpMasterState->port_uuid_field[1] = pucTemp[1];
    ptpMasterState->port_uuid_field[2] = pucTemp[2];
    ptpMasterState->port_uuid_field[3] = pucTemp[3];

    pucTemp = (uint8_t *)&mac_high;
    ptpMasterState->port_uuid_field[4] = pucTemp[0];
    ptpMasterState->port_uuid_field[5] = pucTemp[1];

    //
    // Init global constants.
    //
    for (i = 0, j = 0; i < CLOCK_IDENTITY_LENGTH; i++)
    {
       if (i == 3) ptpMasterState->portIdentity.clockIdentity[i] = 0xFF;
       else if (i == 4) ptpMasterState->portIdentity.clockIdentity[i] = 0xFE;
       else
       {
           ptpMasterState->portIdentity.clockIdentity[i] =
                   ptpMasterState->port_uuid_field[j];
           j++;
       }
    }
}


void sendMessage(Octet * msg,
                 uint32_t messageType,
                 PTPMasterState * ptpMasterState,
                 Ethernet_Pkt_Desc * pktDesc)
{
    uint32_t pktLen;

    //
    // We can't trust if the supplied descriptor is clean. Hence reset it.
    //
    memset(pktDesc, 0, sizeof(Ethernet_Pkt_Desc));

    pktDesc->bufferLength = PACKET_LENGTH;
    pktDesc->dataOffset = 0;
    pktDesc->dataBuffer = (uint8_t *)msg;
    pktDesc->nextPacketDesc = 0;
    pktDesc->flags = ETHERNET_PKT_FLAG_SOP |
                    ETHERNET_PKT_FLAG_EOP |
                    ETHERNET_PKT_FLAG_SA_INS |
                    ETHERNET_PKT_FLAG_CRC_PAD_INS;
    pktDesc->pktChannel = ETHERNET_DMA_CHANNEL_NUM_0;
    pktDesc->numPktFrags = 1;

    //
    // Reset the buffer
    //
    memset(msg + 8, 0, PACKET_LENGTH - 8);

    switch(messageType)
    {
    case SYNC:
        pktDesc->flags |= ETHERNET_PKT_FLAG_TTSE;
        msgPackSync(msg + 8, ptpMasterState);
        pktLen = SYNC_LENGTH;
        break;
    case FOLLOW_UP:
        msgPackFollowUp(msg + 8, ptpMasterState);
        pktLen = FOLLOW_UP_LENGTH;
        gPtpMasterState.syncSeqId++;
        break;
    case DELAY_RESP:
        msgPackDelayResp(msg + 8, ptpMasterState);
        pktLen = DELAY_RESP_LENGTH;
        break;
    default:
        //
        // Error condition, the code should never reach here
        //
        break;
    }

    pktDesc->pktLength = pktLen + 6 + 2;
    pktDesc->validLength = pktDesc->pktLength;

    Ethernet_sendPacket(emac_handle, pktDesc);
}

//*****************************************************************************
//
//  This function is a callback function called by the example to
//  get a Packet Buffer. Has to return a ETHERNET_Pkt_Desc Structure.
//  Rewrite this API for custom use case.
//
//*****************************************************************************
Ethernet_Pkt_Desc* Ethernet_getPacketBufferCustom(void)
{
    //
    // Get the next packet descriptor from the descriptor pool
    //
    uint32_t shortIndex = (Ethernet_numGetPacketBufferCallback + 3)
                % NUM_PACKET_DESC_RX_APPLICATION;

    //
    // Increment the book-keeping pointer which acts as a head pointer
    // to the circular array of packet descriptor pool.
    //
    Ethernet_numGetPacketBufferCallback++;

    //
    // Update buffer length information to the newly procured packet
    // descriptor.
    //
    pktDescriptorRXCustom[shortIndex].bufferLength =
                                  ETHERNET_MAX_PACKET_LENGTH;

    //
    // Update the receive buffer address in the packer descriptor.
    //
    pktDescriptorRXCustom[shortIndex].dataBuffer =
                                      &Ethernet_device_struct.rxBuffer [
               (ETHERNET_MAX_PACKET_LENGTH*Ethernet_device_struct.rxBuffIndex)];

    //
    // Update the receive buffer pool index.
    //
    Ethernet_device_struct.rxBuffIndex += 1U;
    Ethernet_device_struct.rxBuffIndex  =
            (Ethernet_device_struct.rxBuffIndex%ETHERNET_NO_OF_RX_PACKETS);

    //
    // Receive buffer is usable from Address 0
    //
    pktDescriptorRXCustom[shortIndex].dataOffset = 0U;

    //
    // Return this new descriptor to the driver.
    //
    return (&(pktDescriptorRXCustom[shortIndex]));
}

//*****************************************************************************
//
//  This is a hook function and called by the driver when it receives a
//  packet. Application is expected to replenish the buffer after consuming it.
//  Has to return a ETHERNET_Pkt_Desc Structure.
//  Rewrite this API for custom use case.
//
//*****************************************************************************
Ethernet_Pkt_Desc* Ethernet_receivePacketCallbackCustom(
        Ethernet_Handle handleApplication,
        Ethernet_Pkt_Desc *pPacket)
{
    //
    // Need to unpack the header to check which packet is received.
    // We expect a Delay Request packet from the slave. Ignore others.
    //
    msgUnpackHeader((Octet*)(pPacket->dataBuffer + PTP_HEADER_OFFSET),
                    &gPtpMasterState.delayReqHeader);

    switch(gPtpMasterState.delayReqHeader.messageType)
    {
    case DELAY_REQ:
        //
        // Simply get the timestamp and send the delay response packet asap.
        //
        gPtpMasterState.delayReqRecvTimestamp.nanosecondsField =
                pPacket->timeStampLow;
        gPtpMasterState.delayReqRecvTimestamp.secondsField.lsb =
                pPacket->timeStampHigh;
        gPtpMasterState.delayReqRecvTimestamp.secondsField.msb = 0;

        //
        // Save this state that we are sending Delay Resp packet so that it
        // doesn't affect other packets which are being sent.
        //
        gPtpMasterState.sendingDelayResp = TRUE;

        //
        // Send the corresponding Delay Response packet.
        //
        sendMessage((Octet *)gMsgBuf, DELAY_RESP, &gPtpMasterState, &gPktDesc);
        break;
    default:
        //
        // Error condition, the code should never reach here
        //
        break;
    }

    //
    // Book-keeping to maintain number of callbacks received.
    //
#ifdef ETHERNET_DEBUG
    Ethernet_numRxCallbackCustom++;
#endif
    return Ethernet_getPacketBufferCustom();
}

void Ethernet_releaseTxPacketBufferCustom(
        Ethernet_Handle handleApplication,
        Ethernet_Pkt_Desc *pPacket)
{

    //
    // We would like to capture the timestamp for the SYNC packet only.
    //
    if(gPtpMasterState.sendingDelayResp == TRUE)
    {
        gPtpMasterState.sendingDelayResp = FALSE;
    }
    else if(gPtpMasterState.syncTimestampAvailable == FALSE)
    {
        gPtpMasterState.syncTimestamp.nanosecondsField = pPacket->timeStampLow;
        gPtpMasterState.syncTimestamp.secondsField.lsb = pPacket->timeStampHigh;
        gPtpMasterState.syncTimestamp.secondsField.msb = 0;

        gPtpMasterState.syncTimestampAvailable = TRUE;
    }

    //
    // Increment the book-keeping counter.
    //
#if ETHERNET_DEBUG
    Ethernet_releaseTxCount++;
#endif
}
