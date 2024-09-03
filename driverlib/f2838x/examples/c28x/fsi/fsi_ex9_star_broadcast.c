//#############################################################################
//
// FILE:   fsi_ex9_star_broadcast.c
//
// TITLE:  FSI star connection topology example. FSI communication using CPU
//          control.
//! \addtogroup driver_example_list
//! <h1>FSI star connection topology example. FSI communication using CPU control </h1>
//! fsi_ex9_star_broadcast is for the central device in the star topology,
//! fsi_ex16_daisy_handshake_node (CPU Control Only) is used for the N node
//! devices. The fsi_ex16_daisy_handshake_node software example is currently
//! only available for the F28004x devices.
//!
//! In a real scenario two separate devices may power up in arbitrary order and
//! there is a need to establish a clean communication link which ensures that
//! receiver side is flushed to properly interpret the start of a new valid
//! frame.
//!
//! The central device in the star topology initiates and drives the
//! handshake sequence and subsequent broadcast data transmissions.
//! The node devices receive and respond to the broadcasts.
//!
//! After above synchronization steps, FSI Rx can be configured as per use case
//! i.e. nWords, lane width, enabling events, etc and start the infinite
//! transfers. More details on establishing the communication link can be found
//! in the device TRM.
//!
//! Preprocessor Directives FSI_RXA_ENABLE, FSI_RXB_ENABLE, FSI_RXC_ENABLE are
//! used to enable different FSI RX instances. Each node device's FSI TX should
//! be connected to a FSI RX instance of the central device. The FSI TX of the
//! central device should be connected to each node device's FSI RX.
//!
//! User can edit some of configuration parameters as per use case, similar to
//! other examples.
//!
//! \b nWords - Number of words per transfer may be from 1 -16
//! \b nLanes - Choice to select single or double lane for frame transfers
//! \b txUserData - User data to be sent with Data frame
//! \b txDataFrameTag - Frame tag used for Data transfers
//! \b txPingFrameTag - Frame tag used for Ping transfers
//! \b txPingTimeRefCntr - Tx Ping timer reference counter
//! \b rxWdTimeoutRefCntr - Rx Watchdog timeout reference counter
//! \b rxTimeOutCntr - Rx timeout reference counter used in handshake sequence
//!
//!\b External \b Connections \n
//!   For the FSI star connection topology, external connections are required
//!   to be made between the included devices. The FSI TXA pins of the central
//!   device (F2838x) needs to be connected to the FSI RX pins of all node
//!   devices (broadcast to node devices). The FSI RXA, RXB, RXC pins of the
//!   central device should be connected to each individual node device's FSI TX
//!   pins. See below for external connections to include and GPIOs used:
//!
//!  External Connections Required:
//!  - FSIRX_CLK to FSITX_CLK
//!  - FSIRX_RX0 to FSITX_TX0
//!  - FSIRX_RX1 to FSITX_TX1
//!
//!  ControlCard FSI Header GPIOs:
//!
//!  - GPIO_27  ->    FSITXA_CLK
//!  - GPIO_26  ->    FSITXA_TX0
//!  - GPIO_25  ->    FSITXA_TX1
//!
//!  - GPIO_9  ->     FSIRXA_CLK
//!  - GPIO_8  ->     FSIRXA_RX0
//!  - GPIO_10  ->    FSIRXA_RX1
//!
//!  - GPIO_60  ->    FSIRXB_CLK
//!  - GPIO_58  ->    FSIRXB_RX0
//!  - GPIO_59  ->    FSIRXB_RX1
//!
//!  - GPIO_14  ->    FSIRXC_CLK
//!  - GPIO_12  ->    FSIRXC_RX0
//!  - GPIO_13  ->    FSIRXC_RX1
//!
//! FSI TXA of the central device needs to be connected to FSI RX of all node
//! devices (broadcast to nodes). FSI RXA, RXB, RXC of the central device
//! should be connected to each individual node device's FSI TX.
//!
//! \b Watch \b Variables \n
//!  - \b dataFrameCntr_A  Number of Data frame received on FSI RXA
//!  - \b frame_type_error_A  Counts number of RXA frame type errors
//!  - \b frame_tag_error_A  Counts number of RXA frame tag errors
//!  - \b user_data_error_A  Counts number of RXA user data errors
//!  - \b data_error_A  Counts number of RXA data packet errors
//!
//!  - \b dataFrameCntr_B  Number of Data frame received on FSI RXB
//!  - \b frame_type_error_B  Counts number of RXB frame type errors
//!  - \b frame_tag_error_B  Counts number of RXB frame tag errors
//!  - \b user_data_error_B  Counts number of RXB user data errors
//!  - \b data_error_B  Counts number of RXB data packet errors
//!
//!  - \b dataFrameCntr_C  Number of Data frame received on FSI RXC
//!  - \b frame_type_error_C  Counts number of RXC frame type errors
//!  - \b frame_tag_error_C  Counts number of RXC frame tag errors
//!  - \b user_data_error_C  Counts number of RXC user data errors
//!  - \b data_error_C  Counts number of RXC data packet errors
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
#include "driverlib.h"
#include "device.h"

#define COMPARE_FAIL    1
#define COMPARE_PASS    0

#define TX_TIME_OUT_CNTR    0x1000000
#define RX_TIME_OUT_CNTR    0x1000000

// FSI Clock used for transfer
#define PRESCALER_VAL    FSI_PRESCALE_50MHZ

#define FSI_DELAY_LINE_CALIBRATION_ENABLE   0

#define DATA_FRAME_TEST_IO           16
#define DATA_FRAME_TEST_IO_CONF      GPIO_16_GPIO16

//
// Enable FSI RX Instances
//
#define FSI_RXA_ENABLE          1
#define FSI_RXB_ENABLE          0
#define FSI_RXC_ENABLE          1

//
// Globals, User can modify these parameters as per usecase
//
// Number of words per transfer may be from 1 -16
//
uint16_t nWords = 8;

// Transfer can be happen over single or double lane
FSI_DataWidth nLanes = FSI_DATA_WIDTH_1_LANE;

// Frame tag used with Data/Ping transfers
FSI_FrameTag txDataFrameTag = FSI_FRAME_TAG10, txPingFrameTag = FSI_FRAME_TAG15;

// User data to be sent with Data frame(for CPU control)
uint16_t txUserData = 0x47;

// Tx Ping timer and Rx Watchdog reference counter values
uint32_t txPingTimeRefCntr = 0x1000000, rxWdTimeoutRefCntr = 0x1400000;

//
// Globals, these are not config parameters, user are not required to edit them
//
uint16_t txEventSts = 0;
uint16_t *txBufAddr = 0;

uint16_t txBufData[16] = {0};

volatile uint32_t fsiTxInt1Received = 0;
volatile uint32_t fsiRxAInt1Received = 0;
volatile uint32_t fsiRxBInt1Received = 0;
volatile uint32_t fsiRxCInt1Received = 0;

uint32_t txTimeOutCntr = TX_TIME_OUT_CNTR, rxTimeOutCntr = RX_TIME_OUT_CNTR;

// Global Error counters
uint32_t error = 0;                 // General setup error checking

uint32_t fsiTxInt2_error = 0;       // Counts number of TX Int 2 errors

//
// Function Prototypes
//
static inline void compare16(uint16_t val1, uint16_t val2);
static inline uint16_t compare16_return(uint16_t val1, uint16_t val2);

void disableAllFSIInterrupts(void);

void initFSI(void);
void prepareTxBufData(void);
void testGPIO(void);
__interrupt void fsiTxInt1ISR(void);
__interrupt void fsiTxInt2ISR(void);

#if FSI_RXA_ENABLE == 1

uint16_t rxAEventSts = 0, *rxa_BufAddr = 0;

// Counts number of data frames received on RXA
uint32_t dataFrameCntr_A = 0, dataFrameCntr_ui32_A = 0;

uint32_t frame_type_error_A = 0;      // Counts number of RXA frame type errors
uint32_t frame_tag_error_A = 0;       // Counts number of RXA frame tag errors
uint32_t user_data_error_A = 0;       // Counts number of RXA user data errors
uint32_t data_error_A = 0;            // Counts number of RXA data packet errors

uint32_t fsiRxAInt2_error = 0;       // Counts number of RXA Int 2 errors

void compareBufData_A(uint16_t txBufIndex, uint16_t rxBufIndex, uint16_t nWords);
void checkReceivedDataFrameTypeTag_A(FSI_FrameType type, FSI_FrameTag tag);

void checkReceivedFrameTypeTag_RXA(FSI_FrameType type, FSI_FrameTag tag);
__interrupt void fsiRxAInt1ISR(void);
__interrupt void fsiRxAInt2ISR(void);

#endif

#if FSI_RXB_ENABLE == 1

uint16_t rxBEventSts = 0, *rxb_BufAddr = 0;

// Counts number of data frames received on RXB
uint32_t dataFrameCntr_B = 0, dataFrameCntr_ui32_B = 0;

uint32_t frame_type_error_B = 0;      // Counts number of RXB frame type errors
uint32_t frame_tag_error_B = 0;       // Counts number of RXB frame tag errors
uint32_t user_data_error_B = 0;       // Counts number of RXB user data errors
uint32_t data_error_B = 0;            // Counts number of RXB data packet errors

uint32_t fsiRxBInt2_error = 0;       // Counts number of RXB Int 2 errors

void compareBufData_B(uint16_t txBufIndex, uint16_t rxBufIndex, uint16_t nWords);
void checkReceivedDataFrameTypeTag_B(FSI_FrameType type, FSI_FrameTag tag);

void checkReceivedFrameTypeTag_RXB(FSI_FrameType type, FSI_FrameTag tag);
__interrupt void fsiRxBInt1ISR(void);
__interrupt void fsiRxBInt2ISR(void);

#endif

#if FSI_RXC_ENABLE == 1

uint16_t rxCEventSts = 0, *rxc_BufAddr = 0;

// Counts number of data frames received on RXC
uint32_t dataFrameCntr_C = 0, dataFrameCntr_ui32_C = 0;

uint32_t frame_type_error_C = 0;      // Counts number of RXC frame type errors
uint32_t frame_tag_error_C = 0;       // Counts number of RXC frame tag errors
uint32_t user_data_error_C = 0;       // Counts number of RXC user data errors
uint32_t data_error_C = 0;            // Counts number of RXC data packet errors

uint32_t fsiRxCInt2_error = 0;       // Counts number of RXC Int 2 errors

void compareBufData_C(uint16_t txBufIndex, uint16_t rxBufIndex, uint16_t nWords);
void checkReceivedDataFrameTypeTag_C(FSI_FrameType type, FSI_FrameTag tag);

void checkReceivedFrameTypeTag_RXC(FSI_FrameType type, FSI_FrameTag tag);
__interrupt void fsiRxCInt1ISR(void);
__interrupt void fsiRxCInt2ISR(void);

#endif

void handshake_lead(void);

//
// Main
//
void main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();
    //
    // Disable pin locks and enable internal pullups.
    //
    Device_initGPIO();
    testGPIO();

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Initialize basic settings for FSI
    //
    initFSI();

    //
    // Interrupts that are used in this example are re-mapped to ISR functions
    // found within this file. FSI Tx/Rx
    //
    Interrupt_register(INT_FSITXA1, &fsiTxInt1ISR);
    Interrupt_register(INT_FSITXA2, &fsiTxInt2ISR);

#if FSI_RXA_ENABLE == 1
    Interrupt_register(INT_FSIRXA1, &fsiRxAInt1ISR);
    Interrupt_register(INT_FSIRXA2, &fsiRxAInt2ISR);
#endif

#if FSI_RXB_ENABLE == 1
    Interrupt_register(INT_FSIRXB1, &fsiRxBInt1ISR);
    Interrupt_register(INT_FSIRXB2, &fsiRxBInt2ISR);
#endif

#if FSI_RXC_ENABLE == 1
    Interrupt_register(INT_FSIRXC1, &fsiRxCInt1ISR);
    Interrupt_register(INT_FSIRXC2, &fsiRxCInt2ISR);
#endif

    //
    // Enable FSI Tx/Rx interrupts
    //
    Interrupt_enable(INT_FSITXA1);
    Interrupt_enable(INT_FSITXA2);

#if FSI_RXA_ENABLE == 1
    Interrupt_enable(INT_FSIRXA1);
    Interrupt_enable(INT_FSIRXA2);
#endif

#if FSI_RXB_ENABLE == 1
    Interrupt_enable(INT_FSIRXB1);
    Interrupt_enable(INT_FSIRXB2);
#endif

#if FSI_RXC_ENABLE == 1
    Interrupt_enable(INT_FSIRXC1);
    Interrupt_enable(INT_FSIRXC2);
#endif

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Enable normal data receive events to be sent over INT1 line
    //

#if FSI_RXA_ENABLE == 1
    FSI_enableRxInterrupt(FSIRXA_BASE, FSI_INT1, FSI_RX_EVT_PING_FRAME);
#endif

#if FSI_RXB_ENABLE == 1
    FSI_enableRxInterrupt(FSIRXB_BASE, FSI_INT1, FSI_RX_EVT_PING_FRAME);
#endif

#if FSI_RXC_ENABLE == 1
    FSI_enableRxInterrupt(FSIRXC_BASE, FSI_INT1, FSI_RX_EVT_PING_FRAME);
#endif

    //
    // Begin handshake -
    // Wait till interrupts are received on FSIRX INT1 line, verify it's for FRAME
    // DONE event for PING Frame reception
    //
    handshake_lead();

#if FSI_DELAY_LINE_CALIBRATION_ENABLE

    // TODO - Implement FSI RX delay line calibration here
    //          to compensate for channel-to-channel skew.
    //          See Application Report SPRACJ9 and respective
    //          software examples within C2000ware.

#endif

    // Setting for requested nWords and nLanes with transfers
    FSI_setTxFrameType(FSITXA_BASE, FSI_FRAME_TYPE_NWORD_DATA);
    FSI_setTxSoftwareFrameSize(FSITXA_BASE, nWords);
    FSI_setTxDataWidth(FSITXA_BASE, nLanes);

    // RX setting part
#if FSI_RXA_ENABLE == 1
    FSI_setRxSoftwareFrameSize(FSIRXA_BASE, nWords);
    FSI_setRxDataWidth(FSIRXA_BASE, nLanes);
#endif

#if FSI_RXB_ENABLE == 1
    FSI_setRxSoftwareFrameSize(FSIRXB_BASE, nWords);
    FSI_setRxDataWidth(FSIRXB_BASE, nLanes);
#endif

#if FSI_RXC_ENABLE == 1
    FSI_setRxSoftwareFrameSize(FSIRXC_BASE, nWords);
    FSI_setRxDataWidth(FSIRXC_BASE, nLanes);
#endif

    //
    // Enable transmit/receive error events to be sent over INT2 line
    // Overrun and Underrun conditions in Rx are not enabled as buffer pointers
    // are always overwritten to first location for sending data frames.
    //
#if FSI_RXA_ENABLE == 1
    FSI_enableRxInterrupt(FSIRXA_BASE, FSI_INT2, FSI_RX_EVT_CRC_ERR  |
                                                 FSI_RX_EVT_EOF_ERR  |
                                                 FSI_RX_EVT_TYPE_ERR);

    FSI_disableRxInterrupt(FSIRXA_BASE, FSI_INT1, FSI_RX_EVT_PING_FRAME);
    DEVICE_DELAY_US(10);
    FSI_enableRxInterrupt(FSIRXA_BASE, FSI_INT1, FSI_RX_EVT_DATA_FRAME);
    DEVICE_DELAY_US(10);
#endif

#if FSI_RXB_ENABLE == 1
    FSI_enableRxInterrupt(FSIRXB_BASE, FSI_INT2, FSI_RX_EVT_CRC_ERR  |
                                                 FSI_RX_EVT_EOF_ERR  |
                                                 FSI_RX_EVT_TYPE_ERR);

    FSI_disableRxInterrupt(FSIRXB_BASE, FSI_INT1, FSI_RX_EVT_PING_FRAME);
    DEVICE_DELAY_US(10);
    FSI_enableRxInterrupt(FSIRXB_BASE, FSI_INT1, FSI_RX_EVT_DATA_FRAME);
    DEVICE_DELAY_US(10);
#endif

#if FSI_RXC_ENABLE == 1
    FSI_enableRxInterrupt(FSIRXC_BASE, FSI_INT2, FSI_RX_EVT_CRC_ERR  |
                                                 FSI_RX_EVT_EOF_ERR  |
                                                 FSI_RX_EVT_TYPE_ERR);

    FSI_disableRxInterrupt(FSIRXC_BASE, FSI_INT1, FSI_RX_EVT_PING_FRAME);
    DEVICE_DELAY_US(10);
    FSI_enableRxInterrupt(FSIRXC_BASE, FSI_INT1, FSI_RX_EVT_DATA_FRAME);
    DEVICE_DELAY_US(10);
#endif

    FSI_setTxUserDefinedData(FSITXA_BASE, txUserData);
    FSI_setTxFrameTag(FSITXA_BASE, txDataFrameTag);

    FSI_enableTxInterrupt(FSITXA_BASE, FSI_INT1, FSI_TX_EVT_FRAME_DONE);

  while(1)
  {
      // Now, start transmitting data frames

      // Fill TX array with new data
      prepareTxBufData();

      // Write data into Tx buffer and start the first transfer
      FSI_writeTxBuffer(FSITXA_BASE, txBufData, nWords, 0U);
      FSI_startTxTransmit(FSITXA_BASE);

      GPIO_writePin(DEVICE_GPIO_PIN_LED2, 0); // Set LED off

      //
      // Wait for TX frame done event
      //
      while(fsiTxInt1Received != 1U);

      // Set FSI TXA circular buffer pointer back to beginning
      FSI_setTxBufferPtr(FSITXA_BASE, 0U);

      GPIO_writePin(DEVICE_GPIO_PIN_LED2, 1); // Set LED on

      //
      // Wait for RX data frame received event
      //
#if FSI_RXA_ENABLE == 1
      while(fsiRxAInt1Received != 1U);

      // Set FSI RXA circular buffer pointer back to beginning
      FSI_setRxBufferPtr(FSIRXA_BASE, 0U);
#endif

#if FSI_RXB_ENABLE == 1
      while(fsiRxBInt1Received != 1U);

      // Set FSI RXB circular buffer pointer back to beginning
      FSI_setRxBufferPtr(FSIRXB_BASE, 0U);
#endif

#if FSI_RXC_ENABLE == 1
      while(fsiRxCInt1Received != 1U);

      // Set FSI RXC circular buffer pointer back to beginning
      FSI_setRxBufferPtr(FSIRXC_BASE, 0U);
#endif

      fsiTxInt1Received = 0U;
      fsiRxAInt1Received = 0U;
      fsiRxBInt1Received = 0U;
      fsiRxCInt1Received = 0U;
    }
}


void handshake_lead(void)
{

    while(1)
    {
        //
        // Send the flush sequence
        //
        FSI_executeTxFlushSequence(FSITXA_BASE, PRESCALER_VAL);

        //
        // Send a ping frame with frame tag 0000b
        //
        FSI_setTxFrameTag(FSITXA_BASE, FSI_FRAME_TAG0);
        FSI_setTxFrameType(FSITXA_BASE, FSI_FRAME_TYPE_PING);
        FSI_startTxTransmit(FSITXA_BASE);

    #if FSI_RXA_ENABLE == 1
        while(fsiRxAInt1Received != 1U && rxTimeOutCntr != 0U)
        {
            DEVICE_DELAY_US(1);
            rxTimeOutCntr--;
        }
    #endif

    #if FSI_RXB_ENABLE == 1
        while(fsiRxBInt1Received != 1U && rxTimeOutCntr != 0U)
        {
            DEVICE_DELAY_US(1);
            rxTimeOutCntr--;
        }
    #endif

    #if FSI_RXC_ENABLE == 1
        while(fsiRxCInt1Received != 1U && rxTimeOutCntr != 0U)
        {
            DEVICE_DELAY_US(1);
            rxTimeOutCntr--;
        }
    #endif

        if(rxTimeOutCntr == 0)
        {
            GPIO_togglePin(DEVICE_GPIO_PIN_LED1);
            rxTimeOutCntr = RX_TIME_OUT_CNTR;
            continue;
        }
        else
        {
        #if FSI_RXA_ENABLE == 1
            compare16(rxAEventSts, (FSI_RX_EVT_PING_FRAME | FSI_RX_EVT_FRAME_DONE));
            checkReceivedFrameTypeTag_RXA(FSI_FRAME_TYPE_PING, FSI_FRAME_TAG0);
        #endif

        #if FSI_RXB_ENABLE == 1
            compare16(rxBEventSts, (FSI_RX_EVT_PING_FRAME | FSI_RX_EVT_FRAME_DONE));
            checkReceivedFrameTypeTag_RXB(FSI_FRAME_TYPE_PING, FSI_FRAME_TAG0);
        #endif

        #if FSI_RXC_ENABLE == 1
            compare16(rxCEventSts, (FSI_RX_EVT_PING_FRAME | FSI_RX_EVT_FRAME_DONE));
            checkReceivedFrameTypeTag_RXC(FSI_FRAME_TYPE_PING, FSI_FRAME_TAG0);
        #endif

            fsiRxAInt1Received = 0;
            fsiRxBInt1Received = 0;
            fsiRxCInt1Received = 0;

            //
            // If received frame type and tag matches, exit this loop and proceed
            // to next step by sending flush sequence, otherwise clear error and
            // interrupt flag and continue looping.
            //
            if(error == 0)
            {
                GPIO_writePin(DEVICE_GPIO_PIN_LED1, 0);
                break;
            }

            error = 0;
        }
    }

    while(1)
    {
        //
        // Send a ping frame with frame tag 0001b
        //
        FSI_setTxFrameTag(FSITXA_BASE, FSI_FRAME_TAG1);
        FSI_setTxFrameType(FSITXA_BASE, FSI_FRAME_TYPE_PING);
        FSI_startTxTransmit(FSITXA_BASE);

    #if FSI_RXA_ENABLE == 1
        while(fsiRxAInt1Received != 1U && rxTimeOutCntr != 0U)
        {
            DEVICE_DELAY_US(1);
            rxTimeOutCntr--;
        }
    #endif

    #if FSI_RXB_ENABLE == 1
        while(fsiRxBInt1Received != 1U && rxTimeOutCntr != 0U)
        {
            DEVICE_DELAY_US(1);
            rxTimeOutCntr--;
        }
    #endif

    #if FSI_RXC_ENABLE == 1
        while(fsiRxCInt1Received != 1U && rxTimeOutCntr != 0U)
        {
            DEVICE_DELAY_US(1);
            rxTimeOutCntr--;
        }
    #endif

        if(rxTimeOutCntr == 0)
        {
            GPIO_togglePin(DEVICE_GPIO_PIN_LED1);
            rxTimeOutCntr = RX_TIME_OUT_CNTR;
            continue;
        }
        else
        {
        #if FSI_RXA_ENABLE == 1
            compare16(rxAEventSts, (FSI_RX_EVT_PING_FRAME | FSI_RX_EVT_FRAME_DONE));
            checkReceivedFrameTypeTag_RXA(FSI_FRAME_TYPE_PING, FSI_FRAME_TAG1);
        #endif

        #if FSI_RXB_ENABLE == 1
            compare16(rxBEventSts, (FSI_RX_EVT_PING_FRAME | FSI_RX_EVT_FRAME_DONE));
            checkReceivedFrameTypeTag_RXB(FSI_FRAME_TYPE_PING, FSI_FRAME_TAG1);
        #endif

        #if FSI_RXC_ENABLE == 1
            compare16(rxCEventSts, (FSI_RX_EVT_PING_FRAME | FSI_RX_EVT_FRAME_DONE));
            checkReceivedFrameTypeTag_RXC(FSI_FRAME_TYPE_PING, FSI_FRAME_TAG1);
        #endif

            fsiRxAInt1Received = 0;
            fsiRxBInt1Received = 0;
            fsiRxCInt1Received = 0;

            //
            // If received frame type and tag matches, exit this loop and proceed
            // to next step by sending flush sequence, otherwise clear error and
            // interrupt flag and continue looping.
            //
            if(error == 0)
            {
                GPIO_writePin(DEVICE_GPIO_PIN_LED1, 0);
                break;
            }

            error = 0;
        }
    }
}

//
// initFSI - Initializes FSI Tx/Rx with internal loopback and also sends FLUSH
//           sequence.
//
void initFSI(void)
{
    //
    // NOTE: External loopback, Modify GPIO settings as per setup
    //
    GPIO_setPinConfig(DEVICE_GPIO_CFG_FSI_TXCLK);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_FSI_TX0);
    if(nLanes == FSI_DATA_WIDTH_2_LANE)
    {
        GPIO_setPinConfig(DEVICE_GPIO_CFG_FSI_TX1);
    }

#if FSI_RXA_ENABLE == 1
    FSI_disableRxInternalLoopback(FSIRXA_BASE);

    GPIO_setPinConfig(DEVICE_GPIO_CFG_FSI_RXCLKA);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_FSI_RX0A);
    if(nLanes == FSI_DATA_WIDTH_2_LANE)
    {
        GPIO_setPinConfig(DEVICE_GPIO_CFG_FSI_RX1A);
    }

    //
    // Set RX GPIO to be asynchronous
    // (pass through without delay)
    // Default setting is to have 2 SYS_CLK cycles delay
    //

    GPIO_setQualificationMode(DEVICE_GPIO_PIN_FSI_RX0A, GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_FSI_RXCLKA, GPIO_QUAL_ASYNC);
    if(nLanes == FSI_DATA_WIDTH_2_LANE)
    {
        GPIO_setQualificationMode(DEVICE_GPIO_PIN_FSI_RX1A, GPIO_QUAL_ASYNC);
    }

    FSI_performRxInitialization(FSIRXA_BASE);
    rxa_BufAddr = (uint16_t *)FSI_getRxBufferAddress(FSIRXA_BASE);

#endif

#if FSI_RXB_ENABLE == 1
    FSI_disableRxInternalLoopback(FSIRXB_BASE);

    GPIO_setPinConfig(DEVICE_GPIO_CFG_FSI_RXCLKB);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_FSI_RX0B);
    if(nLanes == FSI_DATA_WIDTH_2_LANE)
    {
        GPIO_setPinConfig(DEVICE_GPIO_CFG_FSI_RX1B);
    }

    GPIO_setQualificationMode(DEVICE_GPIO_PIN_FSI_RX0B, GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_FSI_RXCLKB, GPIO_QUAL_ASYNC);
    if(nLanes == FSI_DATA_WIDTH_2_LANE)
    {
        GPIO_setQualificationMode(DEVICE_GPIO_PIN_FSI_RX1B, GPIO_QUAL_ASYNC);
    }

    FSI_performRxInitialization(FSIRXB_BASE);
    rxb_BufAddr = (uint16_t *)FSI_getRxBufferAddress(FSIRXB_BASE);

#endif

#if FSI_RXC_ENABLE == 1
    FSI_disableRxInternalLoopback(FSIRXC_BASE);

    GPIO_setPinConfig(DEVICE_GPIO_CFG_FSI_RXCLKC);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_FSI_RX0C);
    if(nLanes == FSI_DATA_WIDTH_2_LANE)
    {
        GPIO_setPinConfig(DEVICE_GPIO_CFG_FSI_RX1C);
    }

    GPIO_setQualificationMode(DEVICE_GPIO_PIN_FSI_RX0C, GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_FSI_RXCLKC, GPIO_QUAL_ASYNC);
    if(nLanes == FSI_DATA_WIDTH_2_LANE)
    {
        GPIO_setQualificationMode(DEVICE_GPIO_PIN_FSI_RX1C, GPIO_QUAL_ASYNC);
    }

    FSI_performRxInitialization(FSIRXC_BASE);
    rxc_BufAddr = (uint16_t *)FSI_getRxBufferAddress(FSIRXC_BASE);

#endif

    // Could add logic to calculate PRESCALER_VAL based on user input FSI CLK
    FSI_performTxInitialization(FSITXA_BASE, PRESCALER_VAL);
    txBufAddr = (uint16_t *)FSI_getTxBufferAddress(FSITXA_BASE);
}

//
// prepareTxBufData - Increment values in array which is used as source to Tx data buffer
//
void prepareTxBufData(void)
{
    uint16_t i;
    uint16_t value = txBufData[nWords-1];

    for(i = 0; i < nWords; i++)
    {
        txBufData[i] = value + i + 1;
    }
}

//
// fsiTxInt1ISR - FSI Tx Interrupt on INsT1 line
//
__interrupt void fsiTxInt1ISR(void)
{
    fsiTxInt1Received = 1U;

    txEventSts = FSI_getTxEventStatus(FSITXA_BASE);

    //
    // Clear the interrupt flag and issue ACK
    //
    FSI_clearTxEvents(FSITXA_BASE, FSI_TX_EVTMASK);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP4);
}

//
// fsiTxInt2ISR - FSI Tx Interrupt on INT2 line
//
__interrupt void fsiTxInt2ISR(void)
{
    txEventSts = FSI_getTxEventStatus(FSITXA_BASE);

    fsiTxInt2_error++;

    //
    // Clear the interrupt flag and issue ACK
    //
    FSI_clearTxEvents(FSITXA_BASE, FSI_TX_EVTMASK);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP4);

    disableAllFSIInterrupts();

    //
    // INT2 line is set to fire for error events, stop immediately. Actual Error
    // is captured in txEventSts for debug
    //
    ESTOP0;
}

//
// disableAllFSIInterrupts - Disables all event interrupts in both FSI Tx/Rx,
//                           also clear them
//
void disableAllFSIInterrupts(void)
{
    FSI_disableTxInterrupt(FSITXA_BASE, FSI_INT1, FSI_TX_EVTMASK);
    FSI_disableTxInterrupt(FSITXA_BASE, FSI_INT2, FSI_TX_EVTMASK);
    FSI_disableRxInterrupt(FSIRXA_BASE, FSI_INT1, FSI_RX_EVTMASK);
    FSI_disableRxInterrupt(FSIRXA_BASE, FSI_INT2, FSI_RX_EVTMASK);
    FSI_disableRxInterrupt(FSIRXB_BASE, FSI_INT1, FSI_RX_EVTMASK);
    FSI_disableRxInterrupt(FSIRXB_BASE, FSI_INT2, FSI_RX_EVTMASK);
    FSI_disableRxInterrupt(FSIRXC_BASE, FSI_INT1, FSI_RX_EVTMASK);
    FSI_disableRxInterrupt(FSIRXC_BASE, FSI_INT2, FSI_RX_EVTMASK);

    FSI_clearTxEvents(FSITXA_BASE, FSI_TX_EVTMASK);
    FSI_clearRxEvents(FSIRXA_BASE, FSI_RX_EVTMASK);
}

//
// compare16 - Compares two 16 bit values and increments global error flag by 1
//             for mismatch
//
static inline void compare16(uint16_t val1, uint16_t val2)
{
    if(val1 != val2)
    {
        error++;
    }
}



#if FSI_RXA_ENABLE == 1

//
// fsiRxAInt1ISR - FSI RxA Interrupt on INT1 line
//
__interrupt void fsiRxAInt1ISR(void)
{
    rxAEventSts = FSI_getRxEventStatus(FSIRXA_BASE);

    fsiRxAInt1Received = 1U;

     if((rxAEventSts & FSI_RX_EVT_DATA_FRAME) != 0)
    {
         //
         // Verify TX data is same as RX data
         //
         checkReceivedDataFrameTypeTag_A(FSI_FRAME_TYPE_NWORD_DATA, txDataFrameTag);
         user_data_error_A += compare16_return(FSI_getRxUserDefinedData(FSIRXA_BASE), txUserData);
         compareBufData_A(0, 0, nWords);

         dataFrameCntr_A++;

         if(dataFrameCntr_A >= 0xFFFFFFFF)
         {
             dataFrameCntr_ui32_A++;
             dataFrameCntr_A = 0;
         }
    }

    //
    // Clear the interrupt flag and issue ACK
    //
    FSI_clearRxEvents(FSIRXA_BASE,rxAEventSts);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP4);
}

//
// fsiRxAInt2ISR - FSI RxA Interrupt on INT2 line
//
__interrupt void fsiRxAInt2ISR(void)
{
    rxAEventSts = FSI_getRxEventStatus(FSIRXA_BASE);

    fsiRxAInt2_error++;

    //
    // Clear the interrupt flag and issue ACK
    //
    FSI_clearRxEvents(FSIRXA_BASE,rxAEventSts);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP4);

    disableAllFSIInterrupts();

    //
    // INT2 line is set to fire for error events, stop immediately. Error
    // is captured in rxAEventSts for debug
    //11.24
  ESTOP0;
}

//
// checkReceivedFrameTypeTag_RXA - Checks received frame type/tag and updates global
//                             error flag
//
void checkReceivedFrameTypeTag_RXA(FSI_FrameType type, FSI_FrameTag tag)
{
    compare16((uint16_t)FSI_getRxFrameType(FSIRXA_BASE), (uint16_t)type);

    if(type == FSI_FRAME_TYPE_PING)
    {
        compare16(FSI_getRxPingTag(FSIRXA_BASE), (uint16_t)tag);
    }
    else
    {
        compare16(FSI_getRxFrameTag(FSIRXA_BASE), (uint16_t)tag);
    }
}

//
// compareBufData_A - Compares if received data is same as transmitted ones
//                  It doesn't consider wrap-up cases, but, can be enhanced
//
void compareBufData_A(uint16_t txBufIndex, uint16_t rxBufIndex, uint16_t nWords)
{
    uint16_t i;
    uint16_t rxDataArray[16];

    FSI_readRxBuffer(FSIRXA_BASE, rxDataArray, nWords, rxBufIndex);

    for(i = 0; i < nWords; i++)
    {
        if(rxDataArray[i] != txBufAddr[txBufIndex])
        {
            data_error_A++;
            return;
        }

        txBufIndex++;
    }
}

//
// checkReceivedDataFrameTypeTag_A - Checks received data frame type/tag and updates global
//                             error flag
//
void checkReceivedDataFrameTypeTag_A(FSI_FrameType type, FSI_FrameTag tag)
{
    frame_type_error_A += compare16_return((uint16_t)FSI_getRxFrameType(FSIRXA_BASE), (uint16_t)type);

    frame_tag_error_A += compare16_return(FSI_getRxFrameTag(FSIRXA_BASE), (uint16_t)tag);
}

#endif

#if FSI_RXB_ENABLE == 1

//
// fsiRxAInt1ISR - FSI RxB Interrupt on INT1 line
//
__interrupt void fsiRxBInt1ISR(void)
{
    rxBEventSts = FSI_getRxEventStatus(FSIRXB_BASE);

    fsiRxBInt1Received = 1U;

     if((rxBEventSts & FSI_RX_EVT_DATA_FRAME) != 0)
    {
         //
         // Verify TX data is same as RX data
         //
         checkReceivedDataFrameTypeTag_B(FSI_FRAME_TYPE_NWORD_DATA, txDataFrameTag);
         user_data_error_B += compare16_return(FSI_getRxUserDefinedData(FSIRXB_BASE), txUserData);
         compareBufData_B(0, 0, nWords);

         dataFrameCntr_B++;

         if(dataFrameCntr_B >= 0xFFFFFFFF)
         {
             dataFrameCntr_ui32_B++;
             dataFrameCntr_B = 0;
         }
    }

    //
    // Clear the interrupt flag and issue ACK
    //
    FSI_clearRxEvents(FSIRXB_BASE,rxBEventSts);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP4);
}

//
// fsiRxBInt2ISR - FSI RxB Interrupt on INT2 line
//
__interrupt void fsiRxBInt2ISR(void)
{
    rxBEventSts = FSI_getRxEventStatus(FSIRXB_BASE);

    fsiRxBInt2_error++;

    //
    // Clear the interrupt flag and issue ACK
    //
    FSI_clearRxEvents(FSIRXB_BASE,rxBEventSts);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP4);

    disableAllFSIInterrupts();

    //
    // INT2 line is set to fire for error events, stop immediately. Error
    // is captured in rxAEventSts for debug
    //11.24
  ESTOP0;
}

//
// checkReceivedFrameTypeTag_RXB - Checks received frame type/tag and updates global
//                             error flag
//
void checkReceivedFrameTypeTag_RXB(FSI_FrameType type, FSI_FrameTag tag)
{
    compare16((uint16_t)FSI_getRxFrameType(FSIRXB_BASE), (uint16_t)type);

    if(type == FSI_FRAME_TYPE_PING)
    {
        compare16(FSI_getRxPingTag(FSIRXB_BASE), (uint16_t)tag);
    }
    else
    {
        compare16(FSI_getRxFrameTag(FSIRXB_BASE), (uint16_t)tag);
    }
}

//
// compareBufData_B - Compares if received data is same as transmitted ones
//                  It doesn't consider wrap-up cases, but, can be enhanced
//
void compareBufData_B(uint16_t txBufIndex, uint16_t rxBufIndex, uint16_t nWords)
{
    uint16_t i;
    uint16_t rxDataArray[16];

    FSI_readRxBuffer(FSIRXB_BASE, rxDataArray, nWords, rxBufIndex);

    for(i = 0; i < nWords; i++)
    {
        if(rxDataArray[i] != txBufAddr[txBufIndex])
        {
            data_error_B++;
            return;
        }

        txBufIndex++;
    }
}

//
// checkReceivedDataFrameTypeTag_A - Checks received data frame type/tag and updates global
//                             error flag
//
void checkReceivedDataFrameTypeTag_B(FSI_FrameType type, FSI_FrameTag tag)
{
    frame_type_error_B += compare16_return((uint16_t)FSI_getRxFrameType(FSIRXB_BASE), (uint16_t)type);

    frame_tag_error_B += compare16_return(FSI_getRxFrameTag(FSIRXB_BASE), (uint16_t)tag);
}

#endif

#if FSI_RXC_ENABLE == 1

//
// fsiRxAInt1ISR - FSI RxC Interrupt on INT1 line
//
__interrupt void fsiRxCInt1ISR(void)
{
    rxCEventSts = FSI_getRxEventStatus(FSIRXC_BASE);

    fsiRxCInt1Received = 1U;

     if((rxCEventSts & FSI_RX_EVT_DATA_FRAME) != 0)
    {
         //
         // Verify TX data is same as RX data
         //
         checkReceivedDataFrameTypeTag_C(FSI_FRAME_TYPE_NWORD_DATA, txDataFrameTag);
         user_data_error_C += compare16_return(FSI_getRxUserDefinedData(FSIRXC_BASE), txUserData);
         compareBufData_C(0, 0, nWords);

         dataFrameCntr_C++;

         if(dataFrameCntr_C >= 0xFFFFFFFF)
         {
             dataFrameCntr_ui32_C++;
             dataFrameCntr_C = 0;
         }
    }

    //
    // Clear the interrupt flag and issue ACK
    //
    FSI_clearRxEvents(FSIRXC_BASE,rxCEventSts);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);
}

//
// fsiRxBInt2ISR - FSI RxC Interrupt on INT2 line
//
__interrupt void fsiRxCInt2ISR(void)
{
    rxCEventSts = FSI_getRxEventStatus(FSIRXC_BASE);

    fsiRxCInt2_error++;

    //
    // Clear the interrupt flag and issue ACK
    //
    FSI_clearRxEvents(FSIRXC_BASE,rxCEventSts);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);

    disableAllFSIInterrupts();

    //
    // INT2 line is set to fire for error events, stop immediately. Error
    // is captured in rxAEventSts for debug
    //11.24
  ESTOP0;
}

//
// checkReceivedFrameTypeTag_RXC - Checks received frame type/tag and updates global
//                             error flag
//
void checkReceivedFrameTypeTag_RXC(FSI_FrameType type, FSI_FrameTag tag)
{
    compare16((uint16_t)FSI_getRxFrameType(FSIRXC_BASE), (uint16_t)type);

    if(type == FSI_FRAME_TYPE_PING)
    {
        compare16(FSI_getRxPingTag(FSIRXC_BASE), (uint16_t)tag);
    }
    else
    {
        compare16(FSI_getRxFrameTag(FSIRXC_BASE), (uint16_t)tag);
    }
}

//
// compareBufData_C - Compares if received data is same as transmitted ones
//                  It doesn't consider wrap-up cases, but, can be enhanced
//
void compareBufData_C(uint16_t txBufIndex, uint16_t rxBufIndex, uint16_t nWords)
{
    uint16_t i;
    uint16_t rxDataArray[16];

    FSI_readRxBuffer(FSIRXC_BASE, rxDataArray, nWords, rxBufIndex);

    for(i = 0; i < nWords; i++)
    {
        if(rxDataArray[i] != txBufAddr[txBufIndex])
        {
            data_error_C++;
            return;
        }

        txBufIndex++;
    }
}

//
// checkReceivedDataFrameTypeTag_C - Checks received data frame type/tag and updates global
//                             error flag
//
void checkReceivedDataFrameTypeTag_C(FSI_FrameType type, FSI_FrameTag tag)
{
    frame_type_error_C += compare16_return((uint16_t)FSI_getRxFrameType(FSIRXC_BASE), (uint16_t)type);

    frame_tag_error_C += compare16_return(FSI_getRxFrameTag(FSIRXC_BASE), (uint16_t)tag);
}

#endif

static inline uint16_t compare16_return(uint16_t val1, uint16_t val2)
{
    if(val1 != val2)
    {
        return COMPARE_FAIL; // compared values don't match
    }

    return COMPARE_PASS; // compared values match
}

void testGPIO(void)
{
    // LED config
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED1,GPIO_DIR_MODE_OUT);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_LED1);

    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED2,GPIO_DIR_MODE_OUT);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_LED2);

    GPIO_setDirectionMode(DATA_FRAME_TEST_IO,GPIO_DIR_MODE_OUT);
    GPIO_setQualificationMode(DATA_FRAME_TEST_IO,GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(DATA_FRAME_TEST_IO_CONF);

    GPIO_writePin(DATA_FRAME_TEST_IO,1);
}

//
// End of File
//
