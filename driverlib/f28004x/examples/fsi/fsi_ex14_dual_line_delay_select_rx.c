//#############################################################################
//
// FILE:   fsi_dual_line_delay_select_rx.c
//
// TITLE:  FSI Skew Calibration in Dual Data Line Mode (RX Device)
//
//! \addtogroup driver_example_list
//! <h1>FSI Skew Calibration in Dual Data Line Mode (RX Device)</h1>
//!
//! In order to understand this example better and visualize the results
//! please refer to: [Fast Serial Interface (FSI) Skew 
//! Compensation](http://www.ti.com/lit/an/spracj9/spracj9.pdf)
//!
//! Companion: fsi_dual_line_delay_select_tx
//! In this example, the FSI module is configured to listen for a ping at dual data rate
//! (using both RXD0 and RXD1). The software tests whether the ping sent from the TX
//! device is correctly received against all combinations of delay elements activated.
//! RXD0: 0-31 delay elements activated
//! RXD1: 0-31 delay elements activated
//! RXCLK: 0-31 delay elements activated
//! The software stores the status of the ping received (fail/pass) for each of the
//! 32x32x32 combinations of the delay line elements. This result can be graphed using
//! the FSI Skew Compensation Utility.
//!
//!\b External \b Connections \n
//!   For FSI external connection, make below GPIO settings in
//!   example code.
//!
//!  ControlCard FSI Header GPIOs:
//!     - GPIO_27  ->    FSITX_CLK
//!     - GPIO_26  ->    FSITX_TX0
//!     - GPIO_25  ->    FSITX_TX1
//!     - GPIO_13  ->    FSIRX_CLK
//!     - GPIO_12  ->    FSIRX_RX0
//!     - GPIO_11  ->    FSIRX_RX1
//!
//!  LaunchPad FSI Header GPIOs:
//!     - GPIO_7   ->    FSITX_CLK
//!     - GPIO_6   ->    FSITX_TX0
//!     - GPIO_25   ->    FSITX_TX1
//!     - GPIO_33  ->    FSIRX_CLK
//!     - GPIO_12  ->    FSIRX_RX0
//!     - GPIO_2  ->    FSIRX_RX1
//!
//! \b Watch \b Variables \n
//!  - \b pingAndDataStatus  The success/failure status for each config
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

#define PRESCALER_VAL           16U

#define COUNTER_TIMEOUT         200
#define PING_TIMEOUT_VALUE      1
#define PING_ERROR_MAX          10

#define FSI_DELAY_MAX   31
#define FSI_DELAY_MIN   0

#define FSI_PASS   1UL
#define FSI_FAIL   0UL

#define FSI_PACKAGE_COUNT   16
#define FSI_NUM_WORDS       6


uint32_t delayTapRX0 = 0;
uint32_t delayTapRX1 = 0;
uint32_t delayTapCLK = 0;
uint32_t totalRX2Interrupts = 0;

// In order to understand this example better and visualize the results
// please refer to: http://www.ti.com/lit/an/spracj9/spracj9.pdf
// You can use the GUI in the application report above to visualize the
// pingAndDataStatus variable on a graph.
// This variable contains the success/failure of communication using
// all 32x32x32 options of the RXD0, RXD1 and CLK delay elements.
uint32_t pingAndDataStatus [32][32] = {0};
uint16_t cpuTimer0IntCount = 0;

FSI_DataWidth nLanes = FSI_DATA_WIDTH_2_LANE;

uint16_t txEventSts = 0, rxEventSts = 0;

uint16_t txBufData[16] = {0};
volatile uint32_t fsiTxInt1Received = 0,fsiTxInt2Received = 0;
volatile uint32_t fsiRxInt1Received = 0,fsiRxInt2Received = 0;
uint32_t rxTimeOutCntr = COUNTER_TIMEOUT;
uint32_t error = 0;

//
// Function Prototypes
//
static inline void compare16(uint16_t val1, uint16_t val2);
void disableAllFSIInterrupts(void);
void checkReceivedFrameTypeTag(FSI_FrameType type, FSI_FrameTag tag);
void initFSI(void);
void prepareTxBufData(void);
bool checkFSIPackageData();
void
FSI_configRxDelayLine_fix(uint32_t base, FSI_RxDelayTapType delayTapType,
                uint16_t tapValue);
void initCPUTimer(void);
void configCPUTimer(uint32_t, float, float);

__interrupt void cpuTimer0ISR(void);
__interrupt void fsiTxInt1ISR(void);
__interrupt void fsiTxInt2ISR(void);
__interrupt void fsiRxInt1ISR(void);
__interrupt void fsiRxInt2ISR(void);


#define CHECK_TIMEOUT()         if(cpuTimer0IntCount>=PING_TIMEOUT_VALUE || fsiRxInt2Received > PING_ERROR_MAX){goto CHECK_RESULT;}
#define CHECK_TIMEOUT_DATA()    if(cpuTimer0IntCount>=PING_TIMEOUT_VALUE || fsiRxInt2Received > 0){goto CHECK_RESULT_DATA;}

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
    // ISRs for each CPU Timer interrupt
    //
    Interrupt_register(INT_TIMER0, &cpuTimer0ISR);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    // Loop through all 32x32x32 delay line possibilities!
    for (delayTapCLK = FSI_DELAY_MIN;
            delayTapCLK <= FSI_DELAY_MAX; delayTapCLK++)
    {
        for (delayTapRX0 = FSI_DELAY_MIN;
                delayTapRX0 <= FSI_DELAY_MAX; delayTapRX0++)
        {
            for (delayTapRX1 = FSI_DELAY_MIN;
                    delayTapRX1 <= FSI_DELAY_MAX; delayTapRX1++)
            {
                uint16_t packageCount = 0;
                bool packageVerificationResult = false;

                //
                // Initialize the timer for making sure we timeout incase to frame is received
                //
                initCPUTimer();

                //
                // Configure CPU-Timer 0
                //
                configCPUTimer(CPUTIMER0_BASE, DEVICE_SYSCLK_FREQ, 10000);

                // Enable Timer Interrupt
                CPUTimer_enableInterrupt(CPUTIMER0_BASE);

                //
                // Enable TINT0 in the PIE: Group 1 interrupt 7
                //
                Interrupt_enable(INT_TIMER0);

                //
                // Starts CPU-Timer 0.
                //
                CPUTimer_startTimer(CPUTIMER0_BASE);

                //
                // Initialize basic settings for FSI
                //
                initFSI();
                FSI_setRxDataWidth(FSIRXA_BASE, nLanes);
                FSI_setTxDataWidth(FSITXA_BASE, nLanes);

                //
                // Setup the delay Taps
                //
                FSI_configRxDelayLine_fix(FSIRXA_BASE, FSI_RX_DELAY_D1, delayTapRX1);
                FSI_configRxDelayLine_fix(FSIRXA_BASE, FSI_RX_DELAY_D0, delayTapRX0);
                FSI_configRxDelayLine_fix(FSIRXA_BASE, FSI_RX_DELAY_CLK, delayTapCLK);

                //
                // Enable FSI Tx/Rx interrupts
                //
                Interrupt_enable(INT_FSITXA_INT1);
                Interrupt_enable(INT_FSITXA_INT2);
                Interrupt_enable(INT_FSIRXA_INT1);
                Interrupt_enable(INT_FSIRXA_INT2);

                //
                // Enable normal data transfer events to be sent over INT1 line
                //
                FSI_enableTxInterrupt(FSITXA_BASE, FSI_INT1, FSI_TX_EVT_FRAME_DONE);
                FSI_enableRxInterrupt(FSIRXA_BASE, FSI_INT1, FSI_RX_EVT_PING_FRAME);

                //
                // Now Check for Error
                //
                FSI_enableRxInterrupt(FSIRXA_BASE, FSI_INT2, FSI_RX_EVT_CRC_ERR  |
                                                             FSI_RX_EVT_EOF_ERR  |
                                                             FSI_RX_EVT_TYPE_ERR);


                fsiRxInt1Received = 0;
                fsiRxInt2Received = 0;

                while(1)
                {

                    //
                    // Wait till interrupt is received on FSIRX INT1 line, verify it's for FRAME
                    // DONE event for PING Frame reception
                    //
                    while(fsiRxInt1Received != 1)
                    {
                        //Time out and exit if the timer reaches timeout value
                        CHECK_TIMEOUT();
                    }

                    compare16(rxEventSts, (FSI_RX_EVT_PING_FRAME | FSI_RX_EVT_FRAME_DONE));
                    checkReceivedFrameTypeTag(FSI_FRAME_TYPE_PING, FSI_FRAME_TAG0);

                    //
                    // If received frame type and tag matches, exit this loop and proceed to
                    // next step by sending flush sequence, otherwise clear error and
                    // interrupt flag and continue looping.
                    //
                    if(error == 0)
                    {
                        fsiRxInt1Received = 0;
                        break;
                    }

                    fsiRxInt1Received = 0;
                    error = 0;
                }

                fsiRxInt1Received = 0;
                fsiRxInt2Received = 0;
                while(1)
                {
                    //
                    // Send the flush sequence
                    //
                    FSI_executeTxFlushSequence(FSITXA_BASE, PRESCALER_VAL);

                    //
                    // Send a ping frame with frame tag 0001b
                    //
                    FSI_setTxFrameTag(FSITXA_BASE, FSI_FRAME_TAG1);
                    FSI_setTxFrameType(FSITXA_BASE, FSI_FRAME_TYPE_PING);
                    FSI_startTxTransmit(FSITXA_BASE);

                    while(fsiRxInt1Received != 1U && rxTimeOutCntr != 0U)
                    {
                        CHECK_TIMEOUT();
                        DEVICE_DELAY_US(1);
                        rxTimeOutCntr--;
                    }

                    if(rxTimeOutCntr == 0)
                    {
                        rxTimeOutCntr = COUNTER_TIMEOUT;
                        continue;
                    }
                    else
                    {
                        compare16(rxEventSts, (FSI_RX_EVT_PING_FRAME | FSI_RX_EVT_FRAME_DONE));
                        checkReceivedFrameTypeTag(FSI_FRAME_TYPE_PING, FSI_FRAME_TAG1);

                        //
                        // If received frame type and tag matches, exit this loop and proceed
                        // to next step by sending flush sequence, otherwise clear error and
                        // interrupt flag and continue looping.
                        //
                        if(error == 0)
                        {
                            fsiRxInt1Received = 0;
                            break;
                        }

                        fsiRxInt1Received = 0;
                        error = 0;
                    }
                }

                CHECK_RESULT:

                packageCount = 0;
                if (cpuTimer0IntCount >= PING_TIMEOUT_VALUE || fsiRxInt2Received > PING_ERROR_MAX)
                {
                    // ESTOP0;
                    // If ping failed!
                }
                else
                {
                    cpuTimer0IntCount = 0;

                    //
                    // Now that ping has passed check data transfer of 16 data packages
                    //
                    FSI_enableRxInterrupt(FSIRXA_BASE, FSI_INT2, FSI_RX_EVT_CRC_ERR  |
                                                                 FSI_RX_EVT_EOF_ERR  |
                                                                 FSI_RX_EVT_TYPE_ERR);

                    FSI_disableRxInterrupt(FSIRXA_BASE, FSI_INT1, FSI_RX_EVT_PING_FRAME);
                    FSI_enableRxInterrupt(FSIRXA_BASE, FSI_INT1, FSI_RX_EVT_DATA_FRAME);

                    fsiRxInt1Received = 0U;
                    fsiRxInt2Received = 0U;
                    packageCount = 0;

                    DEVICE_DELAY_US(10);

                    FSI_setRxSoftwareFrameSize(FSIRXA_BASE, FSI_NUM_WORDS);
                    FSI_setRxDataWidth(FSIRXA_BASE, nLanes);
                    FSI_setRxBufferPtr(FSIRXA_BASE, 0U);

                    //
                    // Now, start Receiving data frames
                    //
                    while(packageCount < FSI_PACKAGE_COUNT)
                    {
                        while(fsiRxInt1Received != 1U){
                            CHECK_TIMEOUT_DATA();
                        }


                        packageVerificationResult = checkFSIPackageData();
                        packageCount++;
                        if (!packageVerificationResult)
                        {
                            goto CHECK_RESULT_DATA;
                        }

                        //
                        // Re-initialize flags and buffer pointer before next transmission
                        //
                        fsiRxInt1Received = 0U;
                        fsiRxInt2Received = 0U;
                        FSI_setRxBufferPtr(FSIRXA_BASE, 0U);
                    }
                }

                CHECK_RESULT_DATA:
                disableAllFSIInterrupts();
                CPUTimer_stopTimer(CPUTIMER0_BASE);

                // If Data verification passed and timeouts didnt occurre, then pass
                if (packageVerificationResult == true &&
                        cpuTimer0IntCount < PING_TIMEOUT_VALUE &&
                        packageCount >= FSI_PACKAGE_COUNT)
                {
                    // In order to understand this example better and visualize the results
                    // please refer to: http://www.ti.com/lit/an/spracj9/spracj9.pdf
                    // You can use the GUI in the application report above to visualize the
                    // pingAndDataStatus variable on a graph.
                    // This variable contains the success/failure of communication using
                    // all 32x32x32 options of the RXD0, RXD1 and CLK delay elements.
                    pingAndDataStatus[delayTapCLK][delayTapRX0] |= (FSI_PASS << delayTapRX1);
                }
            }
        }
    }

    // The system has completed gathering data
    // In order to understand this example better and visualize the results
    // please refer to: http://www.ti.com/lit/an/spracj9/spracj9.pdf
    // You can use the GUI in the application report above to visualize the
    // pingAndDataStatus variable on a graph.
    // This variable contains the success/failure of communication using
    // all 32x32x32 options of the RXD0, RXD1 and CLK delay elements.
    ESTOP0;
    while(1);
}

//
// initFSI - Initializes FSI Tx/Rx with internal loopback and also sends FLUSH
//           sequence.
//
void initFSI(void)
{
    FSI_disableRxInternalLoopback(FSIRXA_BASE);

    //
    // NOTE: External loopback, Modify GPIO settings as per setup
    //
	GPIO_setPinConfig(DEVICE_GPIO_CFG_FSI_TXCLK);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_FSI_TX0);
    if(nLanes == FSI_DATA_WIDTH_2_LANE)
    {
        GPIO_setPinConfig(DEVICE_GPIO_CFG_FSI_TX1);
    }

    GPIO_setPinConfig(DEVICE_GPIO_CFG_FSI_RXCLK);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_FSI_RX0);
    if(nLanes == FSI_DATA_WIDTH_2_LANE)
    {
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

    FSI_performTxInitialization(FSITXA_BASE, PRESCALER_VAL);
    FSI_performRxInitialization(FSIRXA_BASE);
}


void
FSI_configRxDelayLine_fix(uint32_t base, FSI_RxDelayTapType delayTapType,
                uint16_t tapValue)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));
    ASSERT(tapValue <= FSI_RX_MAX_DELAY_LINE_VAL);

    EALLOW;
    switch(delayTapType)
    {
        case FSI_RX_DELAY_CLK:
            HWREGH(base + FSI_O_RX_DLYLINE_CTRL) = (HWREGH(base + FSI_O_RX_DLYLINE_CTRL) &
                                                   (~FSI_RX_DLYLINE_CTRL_RXCLK_DLY_M)) |
                                                   (tapValue <<
                                                   FSI_RX_DLYLINE_CTRL_RXCLK_DLY_S);
            break;

        case FSI_RX_DELAY_D0:
            HWREGH(base + FSI_O_RX_DLYLINE_CTRL) = (HWREGH(base + FSI_O_RX_DLYLINE_CTRL) &
                                                   (~FSI_RX_DLYLINE_CTRL_RXD0_DLY_M)) |
                                                   (tapValue <<
                                                   FSI_RX_DLYLINE_CTRL_RXD0_DLY_S);
            break;

        case FSI_RX_DELAY_D1:
            HWREGH(base + FSI_O_RX_DLYLINE_CTRL) = (HWREGH(base + FSI_O_RX_DLYLINE_CTRL) &
                                                    (~FSI_RX_DLYLINE_CTRL_RXD1_DLY_M)) |
                                                    (tapValue <<
                                                    FSI_RX_DLYLINE_CTRL_RXD1_DLY_S);
            break;

        default:
            //
            // Invalid tap selection input
            //
            ASSERT(false);
            break;
    }
    EDIS;
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

    //
    // Increment number of data frames received
    //
    if((rxEventSts & FSI_RX_EVT_DATA_FRAME) != 0)
    {
        //Data Frame was received
    }


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
    totalRX2Interrupts++;

    //
    // Clear the interrupt flag and issue ACK
    //
    FSI_clearRxEvents(FSIRXA_BASE,rxEventSts);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);

    //
    // INT2 line is set to fire for error events, stop immediately. Error
    // is captured in rxEventSts for debug
    //
    // ESTOP0;
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
// Check the data package received by FSI
//
bool checkFSIPackageData()
{
    uint16_t i;
    uint16_t rxDataArray[FSI_NUM_WORDS];

    FSI_readRxBuffer(FSIRXA_BASE, rxDataArray, FSI_NUM_WORDS, 0);
    for (i = 0; i < FSI_NUM_WORDS; i++)
    {
        if (rxDataArray[i] != i)
        {
            return false;
        }
    }

    return true;
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
// initCPUTimers - This function initializes timer0
//
void
initCPUTimer(void)
{
    //
    // Initialize timer period to maximum
    //
    CPUTimer_setPeriod(CPUTIMER0_BASE, 0xFFFFFFFF);

    //
    // Initialize pre-scale counter to divide by 1 (SYSCLKOUT)
    //
    CPUTimer_setPreScaler(CPUTIMER0_BASE, 0);

    //
    // Make sure timer is stopped
    //
    CPUTimer_stopTimer(CPUTIMER0_BASE);

    //
    // Reload all counter register with period value
    //
    CPUTimer_reloadTimerCounter(CPUTIMER0_BASE);

    //
    // Reset interrupt counter
    //
    cpuTimer0IntCount = 0;
}

//
// configCPUTimer - This function initializes the selected timer to the
// period specified by the "freq" and "period" parameters. The "freq" is
// entered as Hz and the period in uSeconds. The timer is held in the stopped
// state after configuration.
//
void
configCPUTimer(uint32_t cpuTimer, float freq, float period)
{
    uint32_t temp;

    //
    // Initialize timer period:
    //
    temp = (uint32_t)(freq / 1000000 * period);
    CPUTimer_setPeriod(cpuTimer, temp);

    //
    // Set pre-scale counter to divide by 1 (SYSCLKOUT):
    //
    CPUTimer_setPreScaler(cpuTimer, 0);

    //
    // Initializes timer control register. The timer is stopped, reloaded,
    // free run disabled, and interrupt enabled.
    // Additionally, the free and soft bits are set
    //
    CPUTimer_stopTimer(cpuTimer);
    CPUTimer_reloadTimerCounter(cpuTimer);
    CPUTimer_setEmulationMode(cpuTimer,
                              CPUTIMER_EMULATIONMODE_STOPAFTERNEXTDECREMENT);
    CPUTimer_enableInterrupt(cpuTimer);

    //
    // Resets interrupt counters for the three cpuTimers
    //
    if (cpuTimer == CPUTIMER0_BASE)
    {
        cpuTimer0IntCount = 0;
    }
}

//
// cpuTimer0ISR - Counter for CpuTimer0
//
__interrupt void
cpuTimer0ISR(void)
{
    if (cpuTimer0IntCount < PING_TIMEOUT_VALUE)
    {
        cpuTimer0IntCount++;
    }
    //
    // Acknowledge this interrupt to receive more interrupts from group 1
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}

//
// End of File
//
