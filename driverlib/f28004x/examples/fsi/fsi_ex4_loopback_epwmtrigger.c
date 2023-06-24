//#############################################################################
//
// FILE:   fsi_ex4_loopback_epwmtrigger.c
//
// TITLE:  FSI data frame transfer triggered by ePWM SOC
//
//! \addtogroup driver_example_list
//! <h1>FSI data transfer by external trigger</h1>
//!
//! FSI frame transfer can be triggered by external sources. It can connect up
//! to 32 trigger sources but as of now, only 16 ePWMx-SOCy(x-1:8, y-A:B) are
//! supported. FSI supports external trigger for both PING and DATA frame
//! transfers and in this example we demonstrate how to setup infinite DATA
//! transfers using selectable ePWM-SOC as a trigger source.
//! The TB counter for ePWM operation is in up/down count mode for this example.
//!
//! Automatic(Hw triggered) Ping frame transmission is also setup along
//! with data.
//!
//! If there are any comparison failures during transfers or any of error
//! event occurs, execution will stop.
//!
//!\b External \b Connections \n
//!   For FSI internal loopback (EXTERNAL_FSI_ENABLE == 0), no external
//!     connections needed
//!
//!   For FSI external loopback (EXTERNAL_FSI_ENABLE == 1), external
//!   connections are required. The FSI TX pins should be connected to the
//!   respective FSI RX pins of the same device. See below for external
//!   connections to include and GPIOs used:
//!
//!  External Connections Required between FSI TX and RX of the same device:
//!  - FSIRX_CLK to FSITX_CLK
//!  - FSIRX_RX0 to FSITX_TX0
//!  - FSIRX_RX1 to FSITX_TX1
//!
//!  ControlCard FSI Header GPIOs:
//!     - GPIO_27  ->    FSITX_CLK
//!     - GPIO_26  ->    FSITX_TX0
//!     - GPIO_25  ->    FSITX_TX1
//!     - GPIO_13  ->    FSIRX_CLK
//!     - GPIO_12  ->    FSIRX_RX0
//!     - GPIO_11  ->    FSIRX_RX1
//!  LaunchPad FSI Header GPIOs:
//!     - GPIO_7   ->    FSITX_CLK
//!     - GPIO_6   ->    FSITX_TX0
//!     - GPIO_25   ->    FSITX_TX1
//!     - GPIO_33  ->    FSIRX_CLK
//!     - GPIO_12  ->    FSIRX_RX0
//!     - GPIO_2  ->    FSIRX_RX1
//!
//! \b Watch \b Variables \n
//!  - \b dataFrameCntr  Number of Data frame transfered
//!  - \b error          Non zero for transmit/receive data mismatch
//!
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
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

//
// Defines: User can modify these values as desired
//
#define PRESCALER_VAL    FSI_PRESCALE_50MHZ

//
// Define to enable external FSI configuration
//
// 0 = internal loopback enabled
// 1 = internal loopback disabled, FSI GPIOs configured,
//      external connections required
//
#define EXTERNAL_FSI_ENABLE     0

#define EPWM_TIMER_TBPRD  1000U
#define EPWM_CMPA_VALUE   500U
#define EPWM_CMPB_VALUE   500U

//
// Globals and Typedefs
//

// User can choose any of 16 ePWM SOC event triggers
FSI_ExtFrameTriggerSrc ePWMTrigSel = FSI_EXT_TRIGSRC_EPWM7_SOCB;

// ePWM base addresses to operate on selected module and also Sysctl Clock to
// enable/disable them.
// Need to change base address as per EPWM trigger selection in  \b ePWMTrigSel
uint32_t ePWMBaseAddr = EPWM7_BASE;
SysCtl_PeripheralPCLOCKCR epwmSysCtlClock = SYSCTL_PERIPH_CLK_EPWM7;

// Number of words per transfer may be from 1 -16
uint16_t nWords = 9;

// Transfer can be happen over single or double lane
FSI_DataWidth nLanes = FSI_DATA_WIDTH_1_LANE;

// FSI Clock used for transfer
uint32_t fsiClock = 50000000;

// Frame tag used with Data/Ping transfers
FSI_FrameTag txDataFrameTag, txPingFrameTag;

// User data to be sent with Data frame
uint16_t txUserData = 0U;

// Tx Ping timer and Rx Watchdog reference counter values
uint32_t txPingTimeRefCntr = 0x100000, rxWdTimeoutRefCntr = 0x140000;

// Boolean flag to enable/disable Rx Frame Watchdog
bool isRxFrameWdEnable = true;

//
// This value can be anything suitable to generate a single interrupt event,
// lower values may lead WD to trigger another event even before handler of 1st
// one is not completed
//
uint32_t rxFrameWdRefCntr = 0x1000000;

//
// Globals, these are not config parameters, user are not required to edit them
//
uint16_t txEventSts = 0, rxEventSts = 0;
uint16_t *txBufAddr = 0, *rxBufAddr = 0;

uint16_t txBufData[16] = {0};
volatile uint32_t fsiTxInt1Received = 0,fsiTxInt2Received = 0;
volatile uint32_t fsiRxInt1Received = 0,fsiRxInt2Received = 0;
uint32_t txTimeOutCntr = 0x100000, rxTimeOutCntr = 0x100000;
uint32_t dataFrameCntr = 0;
uint32_t error = 0;

//
// Function Prototypes
//
static inline void compare16(uint16_t val1, uint16_t val2);
void compareBufData(uint16_t txBufIndex, uint16_t rxBufIndex, uint16_t nWords);
void disableAllFSIInterrupts(void);
void checkReceivedFrameTypeTag(FSI_FrameType type, FSI_FrameTag tag);
void initFSI(void);
void prepareTxBufData(void);
__interrupt void fsiTxInt1ISR(void);
__interrupt void fsiTxInt2ISR(void);
__interrupt void fsiRxInt1ISR(void);
__interrupt void fsiRxInt2ISR(void);
void ConfigPWM();

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
    // Interrupts that are used in this example are re-mapped to ISR functions
    // found within this file. Total 4; FSI Tx/Rx :: INT1/INT2
    //
    Interrupt_register(INT_FSITXA_INT1, &fsiTxInt1ISR);
    Interrupt_register(INT_FSITXA_INT2, &fsiTxInt2ISR);
    Interrupt_register(INT_FSIRXA_INT1, &fsiRxInt1ISR);
    Interrupt_register(INT_FSIRXA_INT2, &fsiRxInt2ISR);

    //
    // Initialize basic settings for FSI
    //
    initFSI();

    //
    // Enable FSI Tx/Rx interrupts
    //
    Interrupt_enable(INT_FSITXA_INT1);
    Interrupt_enable(INT_FSITXA_INT2);
    Interrupt_enable(INT_FSIRXA_INT1);
    Interrupt_enable(INT_FSIRXA_INT2);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // First setup Ping transfer and then Data
    //

    //
    // Performing a reset on PING WD counter before its usage is recommended
    // Done on both FSI Tx/Rx sides
    //
    FSI_resetTxModule(FSITXA_BASE, FSI_TX_PING_TIMEOUT_CNT_RESET);
    DEVICE_DELAY_US(1);
    FSI_clearTxModuleReset(FSITXA_BASE, FSI_TX_PING_TIMEOUT_CNT_RESET);

    FSI_resetRxModule(FSIRXA_BASE, FSI_RX_PING_WD_CNT_RESET);
    DEVICE_DELAY_US(1);
    FSI_clearRxModuleReset(FSIRXA_BASE, FSI_RX_PING_WD_CNT_RESET);

    //
    // Enable Rx Ping Watchdog timeout event on INT2 line
    //
    FSI_enableRxInterrupt(FSIRXA_BASE, FSI_INT2, FSI_RX_EVT_PING_WD_TIMEOUT);

    //
    // Now enable PING WD timer in both FSI Tx/Rx sides
    // Keeping reference counter for Rx little wide to ensure its not too sharp
    // to generate a WD timeout
    //
    FSI_enableTxPingTimer(FSITXA_BASE, txPingTimeRefCntr, txPingFrameTag);
    FSI_enableRxPingWatchdog(FSIRXA_BASE, rxWdTimeoutRefCntr);

    //
    // Automatic Ping transmission is setup, now configure for data transfers
    //

    //
    // Setting for requested nWords and nLanes with transfers
    //
    FSI_setTxSoftwareFrameSize(FSITXA_BASE, nWords);
    FSI_setRxSoftwareFrameSize(FSIRXA_BASE, nWords);
    FSI_setTxFrameType(FSITXA_BASE, FSI_FRAME_TYPE_NWORD_DATA);
    FSI_setTxDataWidth(FSITXA_BASE, nLanes);
    FSI_setRxDataWidth(FSIRXA_BASE, nLanes);

    //
    // Enable normal data transfer events to be sent over INT1 line
    //
    FSI_enableTxInterrupt(FSITXA_BASE, FSI_INT1, FSI_TX_EVT_FRAME_DONE);
    FSI_enableRxInterrupt(FSIRXA_BASE, FSI_INT1, FSI_RX_EVT_DATA_FRAME );

    //
    // Enable transmit/receive error events to be sent over INT2 line
    // Overrun and Underrun conditions in Rx are not enabled as buffer pointers
    // are always overwritten to first location for sending data frames.
    //
    FSI_enableRxInterrupt(FSIRXA_BASE, FSI_INT2, FSI_RX_EVT_CRC_ERR  |
                                                 FSI_RX_EVT_EOF_ERR  |
                                                 FSI_RX_EVT_TYPE_ERR);

    if(isRxFrameWdEnable)
    {
        //
        // Performing a reset on frame WD before its usage is recommended
        //
        FSI_resetRxModule(FSIRXA_BASE, FSI_RX_FRAME_WD_CNT_RESET);
        DEVICE_DELAY_US(1);
        FSI_clearRxModuleReset(FSIRXA_BASE, FSI_RX_FRAME_WD_CNT_RESET);

        FSI_enableRxInterrupt(FSIRXA_BASE, FSI_INT2,
                                FSI_RX_EVT_FRAME_WD_TIMEOUT);
        FSI_enableRxFrameWatchdog(FSIRXA_BASE, rxFrameWdRefCntr);
    }

    //
    // Configure the ePWM, requested by user as external trigger source for
    // FSI frame transfers. Setting data frame tag to reflect selected EPWM
    // trigger. Some arithmetic to ensure tag remains in range 0x0 - 0xF.
    //
    txDataFrameTag = (FSI_FrameTag)(ePWMTrigSel - FSI_EXT_TRIGSRC_EPWM1_SOCA);
    ConfigPWM();

    //
    // Set up some FSI frame fields and external trigger source based on
    // selected ePWM
    //
    FSI_setTxFrameTag(FSITXA_BASE, txDataFrameTag);
    FSI_setTxStartMode(FSITXA_BASE, FSI_TX_START_EXT_TRIG );
    FSI_setTxExtFrameTrigger(FSITXA_BASE, ePWMTrigSel );

    //
    // Now, start transmitting data frames
    //
    while(1)
    {
        //
        // Enable peripheral clk for ePWM
        //
        SysCtl_enablePeripheral(epwmSysCtlClock);

        //
        // Setup a GPIO pin, not for operation but for debug/probe purpose
        //
        GPIO_setPinConfig(GPIO_13_EPWM7_B);

        //
        // Write data into Tx buffer and set other Frame specific fields
        //
        prepareTxBufData();
        FSI_writeTxBuffer(FSITXA_BASE, txBufData, nWords, 0U);
        txUserData += 1;
        FSI_setTxUserDefinedData(FSITXA_BASE, (txUserData & 0xFF));

        //
        // Start ePWM to trigger FSI data frames transfer upon SOC event
        //
        EPWM_setEmulationMode(ePWMBaseAddr, EPWM_EMULATION_FREE_RUN);
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

        //
        // Wait till frame done event is received by both Tx/Rx modules
        //
        while(fsiTxInt1Received != 1U);
        fsiTxInt1Received = 0;
        while(fsiRxInt1Received != 1U);
        fsiRxInt1Received = 0;

        //
        // Disable peripheral clk for ePWM and Sync
        //
        SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
        SysCtl_disablePeripheral(epwmSysCtlClock);

        //
        // Verify Frame attributes and data
        //
        checkReceivedFrameTypeTag(FSI_FRAME_TYPE_NWORD_DATA, txDataFrameTag);
        compare16(FSI_getRxUserDefinedData(FSIRXA_BASE), (txUserData & 0xFF));
        compareBufData(0, 0, nWords);

        FSI_setTxBufferPtr(FSITXA_BASE, 0U);
        FSI_setRxBufferPtr(FSIRXA_BASE, 0U);

        if(error)
        {
            break;
        }
    }

    //
    // Coming out of infinite while loop means data comparison test failed.
    // Debug further to root-cause
    //
    ESTOP0;
}

//
// initFSI - Initializes FSI Tx/Rx with internal loopback and also sends FLUSH
//           sequence.
//
void initFSI(void)
{
#if EXTERNAL_FSI_ENABLE == 0

    //
    // Set internalLoopback mode
    //
    FSI_enableRxInternalLoopback(FSIRXA_BASE);

#else

    //
    // Configure for External Loopback
    //
    FSI_disableRxInternalLoopback(FSIRXA_BASE);

    GPIO_setPinConfig(DEVICE_GPIO_CFG_FSI_TXCLK);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_FSI_TX0);

    GPIO_setPinConfig(DEVICE_GPIO_CFG_FSI_RXCLK);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_FSI_RX0);

    if(nLanes == FSI_DATA_WIDTH_2_LANE)
    {
        GPIO_setPinConfig(DEVICE_GPIO_CFG_FSI_TX1);
        GPIO_setPinConfig(DEVICE_GPIO_CFG_FSI_RX1);
    }

    //
    // Set RX GPIO to be asynchronous
    // (pass through without delay)
    // Default setting is to have 2 SYS_CLK cycles delay
    //
    if(nLanes == FSI_DATA_WIDTH_2_LANE)
    {
        GPIO_setQualificationMode(DEVICE_GPIO_PIN_FSI_RX1, GPIO_QUAL_ASYNC);
    }
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_FSI_RX0, GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_FSI_RXCLK, GPIO_QUAL_ASYNC);

#endif

    //
    // Initialize Tx/Rx, reset sequence, clear events
    //

    FSI_performTxInitialization(FSITXA_BASE, PRESCALER_VAL);
    FSI_performRxInitialization(FSIRXA_BASE);

    //
    // Flush Sequence before and after releasing Rx core reset, ensures flushing
    // of Rx data/clock lines and prepares it for reception
    //
    FSI_resetRxModule(FSIRXA_BASE, FSI_RX_MAIN_CORE_RESET);
    FSI_executeTxFlushSequence(FSITXA_BASE, PRESCALER_VAL);
    DEVICE_DELAY_US(1);
    FSI_clearRxModuleReset(FSIRXA_BASE, FSI_RX_MAIN_CORE_RESET);
    FSI_executeTxFlushSequence(FSITXA_BASE, PRESCALER_VAL);

    //
    // Assigning base addresses of Tx/Rx data buffer to globals
    //
    txBufAddr = (uint16_t *)FSI_getTxBufferAddress(FSITXA_BASE);
    rxBufAddr = (uint16_t *)FSI_getRxBufferAddress(FSIRXA_BASE);
}

//
// prepareTxBufData - Update array which is used as source to Tx data buffer
//
void prepareTxBufData(void)
{
    uint16_t i;

    for(i = 0; i < nWords; i++)
    {
        txBufData[i] = txBufData[i] + 1;
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
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);
}

//
// fsiTxInt2ISR - FSI Tx Interrupt on INT2 line
//
__interrupt void fsiTxInt2ISR(void)
{
    fsiTxInt2Received = 1U;

    txEventSts = FSI_getTxEventStatus(FSITXA_BASE);

    //
    // Clear the interrupt flag and issue ACK
    //
    FSI_clearTxEvents(FSITXA_BASE, FSI_TX_EVTMASK);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);

    disableAllFSIInterrupts();

    //
    // INT2 line is set to fire for error events, stop immediately. Actual Error
    // is captured in txEventSts for debug
    //
    ESTOP0;
}

//
// fsiRxInt1ISR - FSI Rx Interrupt on INT1 line
//
__interrupt void fsiRxInt1ISR(void)
{
    rxEventSts = FSI_getRxEventStatus(FSIRXA_BASE);

    fsiRxInt1Received = 1U;
    dataFrameCntr++;

    //
    // Clear the interrupt flag and issue ACK
    //
    FSI_clearRxEvents(FSIRXA_BASE,rxEventSts);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);
}

//
// fsiRxInt2ISR - FSI Rx Interrupt on INT2 line
//
__interrupt void fsiRxInt2ISR(void)
{
    rxEventSts = FSI_getRxEventStatus(FSIRXA_BASE);

    fsiRxInt2Received = fsiRxInt2Received + 1U;

    //
    // Clear the interrupt flag and issue ACK
    //
    FSI_clearRxEvents(FSIRXA_BASE,rxEventSts);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);

    disableAllFSIInterrupts();

    //
    // INT2 line is set to fire for error events, stop immediately. Error
    // is captured in rxEventSts for debug
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

//
// compareBufData - Compares if received data is same as transmitted ones
//                  It doesn't consider wrap-up cases, but, can be enhanced
//
void compareBufData(uint16_t txBufIndex, uint16_t rxBufIndex, uint16_t nWords)
{
    uint16_t i;
    uint16_t rxDataArray[16];

    FSI_readRxBuffer(FSIRXA_BASE, rxDataArray, nWords, rxBufIndex);

    for(i = 0; i < nWords; i++)
    {
        if(rxDataArray[i] != txBufAddr[txBufIndex])
        {
            error++;
            return;
        }
        txBufIndex++;
    }
}

//
// checkReceivedFrameTypeTag - Checks received frame type/tag and updates global
//                             error flag
//
void checkReceivedFrameTypeTag(FSI_FrameType type, FSI_FrameTag tag)
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
// ConfigPWM - Configures requested ePWM
//             TB counter is in up/down count mode for this example
//
void ConfigPWM()
{
    //
    // Set-up TBCLK
    //
    EPWM_setTimeBasePeriod(ePWMBaseAddr, EPWM_TIMER_TBPRD);
    EPWM_setPhaseShift(ePWMBaseAddr, 0U);
    EPWM_setTimeBaseCounter(ePWMBaseAddr, 0U);

    //
    // Set Compare values
    //
    EPWM_setCounterCompareValue(ePWMBaseAddr,
                                EPWM_COUNTER_COMPARE_A,
                                EPWM_CMPA_VALUE);

    EPWM_setCounterCompareValue(ePWMBaseAddr,
                                EPWM_COUNTER_COMPARE_B,
                                EPWM_CMPB_VALUE);

    EPWM_setTimeBaseCounterMode(ePWMBaseAddr, EPWM_COUNTER_MODE_UP_DOWN);
    EPWM_disablePhaseShiftLoad(ePWMBaseAddr);
    EPWM_setClockPrescaler(ePWMBaseAddr,
                           EPWM_CLOCK_DIVIDER_1,
                           EPWM_HSCLOCK_DIVIDER_1);

    //
    // Set up shadowing
    //
    EPWM_setCounterCompareShadowLoadMode(ePWMBaseAddr,
                                         EPWM_COUNTER_COMPARE_A,
                                         EPWM_COMP_LOAD_ON_CNTR_ZERO);

    EPWM_setCounterCompareShadowLoadMode(ePWMBaseAddr,
                                         EPWM_COUNTER_COMPARE_B,
                                         EPWM_COMP_LOAD_ON_CNTR_ZERO);

    //
    // Set actions
    //
    EPWM_setActionQualifierAction(ePWMBaseAddr,
                                  EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(ePWMBaseAddr,
                                  EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    EPWM_setActionQualifierAction(ePWMBaseAddr,
                                  EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    EPWM_setActionQualifierAction(ePWMBaseAddr,
                                  EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);

    //
    // Setup ePWM SOC trigger
    //
    EPWM_setADCTriggerEventPrescale(ePWMBaseAddr, EPWM_SOC_A, 1);
    EPWM_setADCTriggerEventPrescale(ePWMBaseAddr, EPWM_SOC_B, 1);
    EPWM_enableADCTrigger(ePWMBaseAddr,EPWM_SOC_A);
    EPWM_enableADCTrigger(ePWMBaseAddr,EPWM_SOC_B);
    EPWM_setADCTriggerSource(ePWMBaseAddr,EPWM_SOC_A,EPWM_SOC_TBCTR_PERIOD);
    EPWM_setADCTriggerSource(ePWMBaseAddr,EPWM_SOC_B,EPWM_SOC_TBCTR_PERIOD);
}

//
// End of File
//
