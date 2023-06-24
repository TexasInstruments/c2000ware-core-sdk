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

#include <fsi_optimal_delay.h>

//! \brief Maximum and minimum number of delay elements
//!
#define FSI_DELAY_MAX   31
#define FSI_DELAY_MIN   0

//! \brief Values used to check wether FSI communication was successful or not
//!
#define FSI_PASS   1UL
#define FSI_FAIL   0UL

//! \brief Number of CPU cycles used to retry communication before timeout
//!
#define PING_TIMEOUT_VALUE   10000
#define COUNTER_TIMEOUT      200

#define CHECK_TIMEOUT()         if(pingTimeOutCount>=PING_TIMEOUT_VALUE){goto CHECK_RESULT;}


//*****************************************************************************
//
//! \brief Uses a specific number of delay elements on the FSIRX module delay
//!        lines to see if the communication was successful
//!
//! \details Uses a specific number of delay elements on the FSIRX module delay
//!          lines to see if the communication was successful
//!
//! \param[in] rxbase is the FSI Rx module base address
//! \param[in] txbase is the FSI Tx module base address
//! \param[in] lastTag is the last FSI frame tag module
//! \param[in] delayTapRX0 is the number of activated delay elements for RX0
//! \param[in] delayTapRX1 is the number of activated delay elements for RX1
//! \param[in] delayTapCLK is the number of activated delay elements for CLK
//! \param[in] reliableTXPrescalar is the FSI Tx clock prescalar that
//!            that gurauntees successful communication
//!
//! \return true if validation was succesful.
//
//*****************************************************************************
bool FSI_validatePing(uint32_t rxbase, uint32_t txbase,
                  FSI_FrameTag lastTag,
                  uint16_t delayTapRX0,
                  uint16_t delayTapRX1,
                  uint16_t delayTapCLK,
                  uint16_t reliableTXPrescalar);

XYPoint FSI_calculateCenterPoint(uint32_t xAxis, uint32_t yAxis);

//*****************************************************************************
//
//! \brief Adds delay for selected tap line 
//!        (THIS IS A FIX TO C2000WARE v1.01.00.00)
//!
//! \param[in] base is the FSI Rx module base address
//! \param[in] delayTapType the line for which delay needs to be added
//!            it can be either RXCLK,RXD0 or RXD1
//! \param[in] tapValue   5 bit value of the amount of delay to be added
//!
//! \return None.
//
//*****************************************************************************
void
FSI_configRxDelayLine_fix(uint32_t base, FSI_RxDelayTapType delayTapType,
                uint16_t tapValue);



XYPoint FSI_calculateCenterPoint(uint32_t xAxis, uint32_t yAxis)
{
    XYPoint centerPoint = {
       .X = -1,
       .Y = -1
    };

    uint32_t x = 0;
    uint32_t y = 0;

    uint16_t xIntercepts [2] = {0};
    uint16_t yIntercepts [2] = {0};

    uint16_t xNumberOfIntercepts = 0;
    uint16_t yNumberOfIntercepts = 0;

    bool previousValue = false;

    for (x = 0; x < 32; x++)
    {
        bool currentValue = (xAxis >> x) & 0x1;
        if (previousValue != currentValue)
        {
            xIntercepts[xNumberOfIntercepts] = x;
            xNumberOfIntercepts++;
        }
        previousValue = currentValue;
        if(xNumberOfIntercepts == 2)
        break;
    }

    previousValue = false;
    for (y = 0; y < 32; y++)
    {
        bool currentValue = (yAxis >> y) & 0x1;
        if (previousValue != currentValue)
        {
            yIntercepts[yNumberOfIntercepts] = y;
            yNumberOfIntercepts++;
        }
        previousValue = currentValue;
        if(yNumberOfIntercepts == 2)
        break;
    }


    if (xNumberOfIntercepts == 2 && yNumberOfIntercepts ==2
            && xIntercepts[0] == yIntercepts[0]
            && xIntercepts[0] == 0)
    {
        //Scenario 1, Data passes through the center
        int passRangeWidth = xIntercepts[1] + yIntercepts[1];
        int xval = xIntercepts[1] - (int)(passRangeWidth/2);
        int yval = 0;
        if (xval < 0)
        {
            int offset = 0 - xval;
            yval = yval + offset;
            xval = xval + offset;
        }

        centerPoint.X = xval;
        centerPoint.Y = yval;

    }
    else if (xNumberOfIntercepts == 2 && yNumberOfIntercepts == 0)
    {
        //Scenatio 2 Passes through the x-axis twice
        int passRangeWidth = xIntercepts[1] - xIntercepts[0];
        centerPoint.X = xIntercepts[0] + (int)(passRangeWidth/2);
        centerPoint.Y = 0;
    }
    else if (xNumberOfIntercepts == 1 && yNumberOfIntercepts == 0)
    {
        //Scenario 3, Data passes through the x-axis once at the right corner!
        int passRangeWidth = 31 - xIntercepts[0];
        centerPoint.X = xIntercepts[0] + (int)(passRangeWidth/2);
        centerPoint.Y = 0;
    }
    else if (xNumberOfIntercepts == 0 && yNumberOfIntercepts == 2)
    {
        //Scenario 4, Data passes through the y-axis twice
        int passRangeWidth = yIntercepts[1] - yIntercepts[0];
        centerPoint.X = 0;
        centerPoint.Y = yIntercepts[0] + (int)(passRangeWidth/2);
    }
    else if (xNumberOfIntercepts == 0 && yNumberOfIntercepts == 1)
    {
        //Scenario 5, Data passes through the y-axis once at the top corner!
        int passRangeWidth = 31 - yIntercepts[0];
        centerPoint.X = 0;
        centerPoint.Y = yIntercepts[0] + (int)(passRangeWidth/2);
    }
    else if (xNumberOfIntercepts == 1 && yNumberOfIntercepts == 2
            && xIntercepts[0] == 0)
    {
        //Scenario 6, x-axis all pass. y-axis crossed!
        int passRangeWidth = 32 + yIntercepts[1];
        centerPoint.X = 32 - passRangeWidth/2;
        centerPoint.Y = 0;
    }
    else if (xNumberOfIntercepts == 2 && yNumberOfIntercepts == 1
            && yIntercepts[0] == 0)
    {
        //Scenario 7, y-axis all pass. x-axis crossed.
        int passRangeWidth = 32 + xIntercepts[1];
        centerPoint.X = 0;
        centerPoint.Y = 32 - passRangeWidth/2;
    }
    else if (xNumberOfIntercepts == 1 && yNumberOfIntercepts == 1
            && xIntercepts[0] == 0 && yIntercepts[0] == 0)
    {
        //Scenario 8, the whole data set passes!
        centerPoint.X = 0;
        centerPoint.Y = 0;
    }


    return  centerPoint;
}

FSIExecutionPoint FSI_calibrateExecutionPoint(uint32_t rxbase, uint32_t txbase, FSI_DataWidth nLanes,
                                              uint16_t reliableTXPrescalar)
{
    uint32_t rx0Axis_singleLine = 0;
    uint32_t clkAxis_singleLine = 0;
    uint32_t rx1Axis_dualLine = 0;
    uint32_t clkAxis_dualLine = 0;
    XYPoint centerPoint;

    uint32_t delayTapRX0 = 0;
    uint32_t delayTapRX1 = 0;
    uint32_t delayTapCLK = 0;

    FSIExecutionPoint singleLineExePoint = {
        .RX0Delay = 0,
        .RX1Delay = 0,
        .CLKDelay = 0,
        .Valid = true
    };

    FSIExecutionPoint dualLineExePoint = {
        .RX0Delay = 0,
        .RX1Delay = 0,
        .CLKDelay = 0,
        .Valid = true
    };

    FSI_FrameTag restoreTag = FSI_getTxFrameTag(txbase);
    FSI_FrameType restoreType = FSI_getTxFrameType(txbase);
    uint16_t restorePrescale = FSI_getTxPrescale(txbase);
    uint16_t restoreTXInt1 = FSI_getTxInterrupt(txbase, FSI_INT1);
    uint16_t restoreTXInt2 = FSI_getTxInterrupt(txbase, FSI_INT2);
    uint16_t restoreRXInt1 = FSI_getRxInterrupt(rxbase, FSI_INT1);
    uint16_t restoreRXInt2 = FSI_getRxInterrupt(rxbase, FSI_INT2);



    // Begin with single line FSI pings
    FSI_setRxDataWidth(rxbase, FSI_DATA_WIDTH_1_LANE);
    FSI_setTxDataWidth(txbase, FSI_DATA_WIDTH_1_LANE);

    // Set delay tap for CLK to zero
    // Loop through the 32 delay taps for RX0
    delayTapCLK = 0;
    for (delayTapRX0 = 0;
            delayTapRX0 <= FSI_DELAY_MAX; delayTapRX0++)
    {
        bool check = FSI_validatePing(
                rxbase, txbase, FSI_FRAME_TAG3,
                delayTapRX0, delayTapRX1, delayTapCLK, reliableTXPrescalar);
        if (check)
        {
            // Bit pack the rx0Axis
            rx0Axis_singleLine |= (FSI_PASS << delayTapRX0);
        }
    }

    // Set delay tap for RX0 to zero
    // Loop through the 32 delay taps for CLK
    delayTapRX0 = 0;
    for (delayTapCLK = 0;
            delayTapCLK <= FSI_DELAY_MAX; delayTapCLK++)
    {
        bool check = FSI_validatePing(
                rxbase, txbase, FSI_FRAME_TAG3,
                delayTapRX0, delayTapRX1, delayTapCLK, reliableTXPrescalar);
        if (check)
        {
            // Bit pack the clk0Axis
            clkAxis_singleLine |= (FSI_PASS << delayTapCLK);
        }
    }

    // calculate the best point based on the rx0 and clk axies.
    centerPoint = FSI_calculateCenterPoint(rx0Axis_singleLine, clkAxis_singleLine);
    if (centerPoint.X < 0  || centerPoint.Y < 0)
    {
        // if x or y are negative, no optimal point was found
        singleLineExePoint.Valid = false;

        //
        // Restore
        //

        FSI_setTxFrameTag(txbase, restoreTag);
        FSI_setTxFrameType(txbase, restoreType);
        FSI_setTxPrescale(txbase, restorePrescale);
        FSI_enableTxInterrupt(txbase, FSI_INT1, restoreTXInt1);
        FSI_enableTxInterrupt(txbase, FSI_INT2, restoreTXInt2);
        FSI_enableRxInterrupt(rxbase, FSI_INT1, restoreRXInt1);
        FSI_enableRxInterrupt(rxbase, FSI_INT2, restoreRXInt2);

        return singleLineExePoint;
    }

    // Populate the new single line execution point
    singleLineExePoint.Valid = true;
    singleLineExePoint.RX0Delay = centerPoint.X;
    singleLineExePoint.CLKDelay = centerPoint.Y;

    // Set the delay taps for RX0 and CLk to new single line optimal values.
    delayTapRX0 = singleLineExePoint.RX0Delay;
    delayTapCLK = singleLineExePoint.CLKDelay;

    if (nLanes == FSI_DATA_WIDTH_1_LANE)
    {
        // Double check to make sure the single line execution point passes
        // Signal the TX device to stop sending pins and exit calibration algorithm.
        bool check = FSI_validatePing(
                rxbase, txbase, FSI_FRAME_TAG4,
                delayTapRX0, delayTapRX1, delayTapCLK, reliableTXPrescalar);
        if (!check)
        {
            // if x or y are negative, no optimal point was found
            singleLineExePoint.Valid = false;

            //
            // Restore
            //

            FSI_setTxFrameTag(txbase, restoreTag);
            FSI_setTxFrameType(txbase, restoreType);
            FSI_setTxPrescale(txbase, restorePrescale);
            FSI_enableTxInterrupt(txbase, FSI_INT1, restoreTXInt1);
            FSI_enableTxInterrupt(txbase, FSI_INT2, restoreTXInt2);
            FSI_enableRxInterrupt(rxbase, FSI_INT1, restoreRXInt1);
            FSI_enableRxInterrupt(rxbase, FSI_INT2, restoreRXInt2);

            return singleLineExePoint;
        }

        // Set the new delay taps
        FSI_configRxDelayLine_fix(rxbase, FSI_RX_DELAY_D0, delayTapRX0);
        FSI_configRxDelayLine_fix(rxbase, FSI_RX_DELAY_D1, delayTapRX1);
        FSI_configRxDelayLine_fix(rxbase, FSI_RX_DELAY_CLK, delayTapCLK);

        //
        // Restore
        //

        FSI_setTxFrameTag(txbase, restoreTag);
        FSI_setTxFrameType(txbase, restoreType);
        FSI_setTxPrescale(txbase, restorePrescale);
        FSI_enableTxInterrupt(txbase, FSI_INT1, restoreTXInt1);
        FSI_enableTxInterrupt(txbase, FSI_INT2, restoreTXInt2);
        FSI_enableRxInterrupt(rxbase, FSI_INT1, restoreRXInt1);
        FSI_enableRxInterrupt(rxbase, FSI_INT2, restoreRXInt2);

        return singleLineExePoint;
    }
    else //Data Width = 2
    {
        // If calculating dual line
        // Double check single line execution point.
        // Signal the TX device to switch to dual line ping transmission.
        bool check = FSI_validatePing(
                rxbase, txbase, FSI_FRAME_TAG2,
                delayTapRX0, delayTapRX1, delayTapCLK, reliableTXPrescalar);
        if (!check)
        {

            dualLineExePoint.Valid = false;

            //
            // Restore
            //

            FSI_setTxFrameTag(txbase, restoreTag);
            FSI_setTxFrameType(txbase, restoreType);
            FSI_setTxPrescale(txbase, restorePrescale);
            FSI_enableTxInterrupt(txbase, FSI_INT1, restoreTXInt1);
            FSI_enableTxInterrupt(txbase, FSI_INT2, restoreTXInt2);
            FSI_enableRxInterrupt(rxbase, FSI_INT1, restoreRXInt1);
            FSI_enableRxInterrupt(rxbase, FSI_INT2, restoreRXInt2);

            return dualLineExePoint;
        }

        // Switch to 2 lanes
        FSI_setRxDataWidth(rxbase, FSI_DATA_WIDTH_2_LANE);
        FSI_setTxDataWidth(txbase, FSI_DATA_WIDTH_2_LANE);

        // This variable is used to skip over the CLK delays that are invalid
        // due to single line execution point calculation
        uint32_t clkOffset = singleLineExePoint.CLKDelay;

        // Set RX0 to execution point
        // Set RX1 to 0
        // Loop through the CLK delay taps starting at the single line execution
        // point
        delayTapRX0 = singleLineExePoint.RX0Delay;
        delayTapRX1 = 0;
        for (delayTapCLK = singleLineExePoint.CLKDelay;
                delayTapCLK <= FSI_DELAY_MAX; delayTapCLK++)
        {
            if (delayTapRX0 <= FSI_DELAY_MAX)
            {
                bool check = FSI_validatePing(
                        rxbase, txbase, FSI_FRAME_TAG3,
                        delayTapRX0, delayTapRX1, delayTapCLK, reliableTXPrescalar);
                if (check)
                {
                    //Shift CLK data to the left to start at bit 0
                    clkAxis_dualLine |= (FSI_PASS << (delayTapCLK - clkOffset));
                }
            }
            delayTapRX0++;
        }

        // Set RX0 and CLK to single line execution point.
        // Loop through all 32 RX1 delay taps.
        delayTapRX0 = singleLineExePoint.RX0Delay;
        delayTapCLK = singleLineExePoint.CLKDelay;
        for (delayTapRX1 = 0;
                delayTapRX1 <= FSI_DELAY_MAX; delayTapRX1++)
        {
            bool check = FSI_validatePing(
                    rxbase, txbase, FSI_FRAME_TAG3,
                    delayTapRX0, delayTapRX1, delayTapCLK, reliableTXPrescalar);
            if (check)
            {
                // Bit pack passing results
                rx1Axis_dualLine |= (FSI_PASS << delayTapRX1);
            }
        }

        centerPoint = FSI_calculateCenterPoint(clkAxis_dualLine, rx1Axis_dualLine);
        //centerPoint.X is shifted CLK center. Must add singleLineExePoint.CLKDelay to get correct clock.
        //singleLine.RX0Delay must also be shifted to match the new CLK. Must add centerPoint.X to get correct RX0
        //centerPoint.Y is RX1Delay
        if (centerPoint.X < 0  || centerPoint.Y < 0)
        {
            dualLineExePoint.Valid = false;

            //
            // Restore
            //

            FSI_setTxFrameTag(txbase, restoreTag);
            FSI_setTxFrameType(txbase, restoreType);
            FSI_setTxPrescale(txbase, restorePrescale);
            FSI_enableTxInterrupt(txbase, FSI_INT1, restoreTXInt1);
            FSI_enableTxInterrupt(txbase, FSI_INT2, restoreTXInt2);
            FSI_enableRxInterrupt(rxbase, FSI_INT1, restoreRXInt1);
            FSI_enableRxInterrupt(rxbase, FSI_INT2, restoreRXInt2);

            return dualLineExePoint;
        }
        dualLineExePoint.CLKDelay = singleLineExePoint.CLKDelay + centerPoint.X;
        dualLineExePoint.RX0Delay = singleLineExePoint.RX0Delay + centerPoint.X;
        dualLineExePoint.RX1Delay = centerPoint.Y;

        // Set the delay taps
        delayTapRX0 = dualLineExePoint.RX0Delay;
        delayTapRX1 = dualLineExePoint.RX1Delay;
        delayTapCLK = dualLineExePoint.CLKDelay;

        // Double check execution point
        check = FSI_validatePing(
                rxbase, txbase, FSI_FRAME_TAG4,
                delayTapRX0, delayTapRX1, delayTapCLK, reliableTXPrescalar);
        if (!check)
        {

            dualLineExePoint.Valid = false;

            //
            // Restore
            //

            FSI_setTxFrameTag(txbase, restoreTag);
            FSI_setTxFrameType(txbase, restoreType);
            FSI_setTxPrescale(txbase, restorePrescale);
            FSI_enableTxInterrupt(txbase, FSI_INT1, restoreTXInt1);
            FSI_enableTxInterrupt(txbase, FSI_INT2, restoreTXInt2);
            FSI_enableRxInterrupt(rxbase, FSI_INT1, restoreRXInt1);
            FSI_enableRxInterrupt(rxbase, FSI_INT2, restoreRXInt2);

            return dualLineExePoint;
        }

        FSI_configRxDelayLine_fix(rxbase, FSI_RX_DELAY_D0, delayTapRX0);
        FSI_configRxDelayLine_fix(rxbase, FSI_RX_DELAY_D1, delayTapRX1);
        FSI_configRxDelayLine_fix(rxbase, FSI_RX_DELAY_CLK, delayTapCLK);

        //
        // Restore
        //

        FSI_setTxFrameTag(txbase, restoreTag);
        FSI_setTxFrameType(txbase, restoreType);
        FSI_setTxPrescale(txbase, restorePrescale);
        FSI_enableTxInterrupt(txbase, FSI_INT1, restoreTXInt1);
        FSI_enableTxInterrupt(txbase, FSI_INT2, restoreTXInt2);
        FSI_enableRxInterrupt(rxbase, FSI_INT1, restoreRXInt1);
        FSI_enableRxInterrupt(rxbase, FSI_INT2, restoreRXInt2);

        return dualLineExePoint;
    }

}


bool FSI_validatePing(uint32_t rxbase, uint32_t txbase,
                  FSI_FrameTag lastTag,
                  uint16_t delayTapRX0,
                  uint16_t delayTapRX1,
                  uint16_t delayTapCLK,
                  uint16_t reliableTXPrescalar)
{
    uint16_t error = 0;
    uint16_t txEventSts = 0, rxEventSts = 0;
    uint32_t rxTimeOutCntr = COUNTER_TIMEOUT;
    uint16_t pingTimeOutCount = 0;


    //
    // Initialize basic settings for FSI
    //
    FSI_disableTxInterrupt(txbase, FSI_INT1, FSI_TX_EVTMASK);
    FSI_disableTxInterrupt(txbase, FSI_INT2, FSI_TX_EVTMASK);
    FSI_disableRxInterrupt(rxbase, FSI_INT1, FSI_RX_EVTMASK);
    FSI_disableRxInterrupt(rxbase, FSI_INT2, FSI_RX_EVTMASK);

    FSI_clearTxEvents(txbase, FSI_TX_EVTMASK);
    FSI_clearRxEvents(rxbase, FSI_RX_EVTMASK);

    // Disable internal loopback
    FSI_disableRxInternalLoopback(rxbase);

    FSI_performTxInitialization(txbase, reliableTXPrescalar);
    FSI_performRxInitialization(rxbase);

    //Set Delay taps
    FSI_configRxDelayLine_fix(rxbase, FSI_RX_DELAY_D0, delayTapRX0);
    FSI_configRxDelayLine_fix(rxbase, FSI_RX_DELAY_D1, delayTapRX1);
    FSI_configRxDelayLine_fix(rxbase, FSI_RX_DELAY_CLK, delayTapCLK);

    //
    // Wait till interrupt is received on FSIRX INT1 line, verify it's for FRAME
    // DONE event for PING Frame reception
    //
    while(1)
    {
        FSI_clearRxEvents(rxbase,FSI_RX_EVTMASK);
        rxEventSts = 0;
        while(!(rxEventSts & FSI_RX_EVT_PING_FRAME))
        {
            DEVICE_DELAY_US(1);
            pingTimeOutCount++;
            CHECK_TIMEOUT();
            rxEventSts = FSI_getRxEventStatus(rxbase);
        }

        if(rxEventSts != (FSI_RX_EVT_PING_FRAME | FSI_RX_EVT_FRAME_DONE))
        {
            (error)++;
        }

        if((uint16_t)FSI_getRxFrameType(rxbase) != (uint16_t)FSI_FRAME_TYPE_PING)
        {
            (error)++;
        }

        if(FSI_getRxFrameType(rxbase) == FSI_FRAME_TYPE_PING)
        {
            if((uint16_t)FSI_getRxPingTag(rxbase) != (uint16_t)FSI_FRAME_TAG0)
            {
                (error)++;
            }
        }
        else
        {
            if((uint16_t)FSI_getRxFrameTag(rxbase) != (uint16_t)FSI_FRAME_TAG0)
            {
                (error)++;
            }
        }
        //
        // If received frame type and tag matches, exit this loop and proceed to
        // next step by sending flush sequence, otherwise clear error and
        // interrupt flag and continue looping.
        //
        if(error == 0)
        {
            break;
        }

        error = 0;
    }
    while(1)
    {
        //
        // Send the flush sequence
        //
        FSI_executeTxFlushSequence(txbase, reliableTXPrescalar);

        //
        // Send a ping frame with frame tag 0001b
        //

        FSI_setTxFrameTag(txbase, FSI_FRAME_TAG1);
        FSI_setTxFrameType(txbase, FSI_FRAME_TYPE_PING);
        FSI_startTxTransmit(txbase);

        FSI_clearRxEvents(rxbase,FSI_RX_EVTMASK);
        rxEventSts = 0;

        while(!(rxEventSts & FSI_RX_EVT_PING_FRAME) && rxTimeOutCntr != 0U)
        {
            CHECK_TIMEOUT();
            DEVICE_DELAY_US(1);
            pingTimeOutCount++;
            rxTimeOutCntr--;
            rxEventSts = FSI_getRxEventStatus(rxbase);
        }

        if(rxTimeOutCntr == 0)
        {
            rxTimeOutCntr = COUNTER_TIMEOUT;
            continue;
        }
        else
        {
            if(rxEventSts != (FSI_RX_EVT_PING_FRAME | FSI_RX_EVT_FRAME_DONE))
            {
                (error)++;
            }

            if((uint16_t)FSI_getRxFrameType(rxbase) != (uint16_t)FSI_FRAME_TYPE_PING)
            {
                (error)++;
            }

            if(FSI_getRxFrameType(rxbase) == FSI_FRAME_TYPE_PING)
            {
                if((uint16_t)FSI_getRxPingTag(rxbase) != (uint16_t)FSI_FRAME_TAG1)
                {
                    (error)++;
                }
            }
            else
            {
                if((uint16_t)FSI_getRxFrameTag(rxbase) != (uint16_t)FSI_FRAME_TAG1)
                {
                    (error)++;
                }
            }
            //
            // If received frame type and tag matches, exit this loop and proceed
            // to next step by sending flush sequence, otherwise clear error and
            // interrupt flag and continue looping.
            //
            if(error == 0)
            {
                break;
            }

            error = 0;
        }
    }

    CHECK_RESULT:
    if (pingTimeOutCount < PING_TIMEOUT_VALUE)
    {

        FSI_setTxFrameTag(txbase, lastTag);
        txEventSts = 0;
        FSI_clearTxEvents(txbase, FSI_TX_EVTMASK);
        FSI_setTxFrameType(txbase, FSI_FRAME_TYPE_PING);
        FSI_startTxTransmit(txbase);
        while(!(txEventSts & FSI_TX_EVT_FRAME_DONE))
        {
            txEventSts = FSI_getTxEventStatus(txbase);
        }
    }

    if (pingTimeOutCount < PING_TIMEOUT_VALUE)
    {
        return true;
    }
    return false;
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


void FSI_transmitToCalibrate(uint32_t rxbase, uint32_t txbase, uint16_t txPrescalar)
{
    uint16_t rxEventSts = 0;
    uint32_t rxTimeOutCntr = COUNTER_TIMEOUT;
    uint16_t error = 0;

    FSI_FrameTag restoreTag = FSI_getTxFrameTag(txbase);
    FSI_FrameType restoreType = FSI_getTxFrameType(txbase);
    uint16_t restorePrescale = FSI_getTxPrescale(txbase);
    uint16_t restoreTXInt1 = FSI_getTxInterrupt(txbase, FSI_INT1);
    uint16_t restoreTXInt2 = FSI_getTxInterrupt(txbase, FSI_INT2);
    uint16_t restoreRXInt1 = FSI_getRxInterrupt(rxbase, FSI_INT1);
    uint16_t restoreRXInt2 = FSI_getRxInterrupt(rxbase, FSI_INT2);

    FSI_disableTxInterrupt(txbase, FSI_INT1, FSI_TX_EVTMASK);
    FSI_disableTxInterrupt(txbase, FSI_INT2, FSI_TX_EVTMASK);
    FSI_disableRxInterrupt(rxbase, FSI_INT1, FSI_RX_EVTMASK);
    FSI_disableRxInterrupt(rxbase, FSI_INT2, FSI_RX_EVTMASK);

    FSI_clearTxEvents(txbase, FSI_TX_EVTMASK);
    FSI_clearRxEvents(rxbase, FSI_RX_EVTMASK);

    //
    // Initialize basic settings for FSI
    //
    FSI_disableRxInternalLoopback(rxbase);

    FSI_performTxInitialization(txbase, txPrescalar);
    FSI_performRxInitialization(rxbase);

    // Begin with single lane
    FSI_setRxDataWidth(rxbase, FSI_DATA_WIDTH_1_LANE);
    FSI_setTxDataWidth(txbase, FSI_DATA_WIDTH_1_LANE);

    //
    // Wait till interrupt is received on FSIRX INT1 line, verify it's for FRAME
    // DONE event for PING Frame reception
    //
    while(1)
    {
        while(1)
        {
            //
            // Send the flush sequence
            //
            FSI_executeTxFlushSequence(txbase, txPrescalar);

            //
            // Send a ping frame with frame tag 0000b
            //
            FSI_setTxFrameTag(txbase, FSI_FRAME_TAG0);
            FSI_setTxFrameType(txbase, FSI_FRAME_TYPE_PING);
            FSI_startTxTransmit(txbase);

            FSI_clearRxEvents(rxbase,FSI_RX_EVTMASK);
            rxEventSts = 0;
            while(!(rxEventSts & FSI_RX_EVT_PING_FRAME) && rxTimeOutCntr != 0U)
            {
                DEVICE_DELAY_US(1);
                rxTimeOutCntr--;
                rxEventSts = FSI_getRxEventStatus(rxbase);
            }

            if(rxTimeOutCntr == 0)
            {
                rxTimeOutCntr = COUNTER_TIMEOUT;
                continue;
            }
            else
            {
                if(rxEventSts != (FSI_RX_EVT_PING_FRAME | FSI_RX_EVT_FRAME_DONE))
                {
                    (error)++;
                }

                if((uint16_t)FSI_getRxFrameType(rxbase) != (uint16_t)FSI_FRAME_TYPE_PING)
                {
                    (error)++;
                }

                if(FSI_getRxFrameType(rxbase) == FSI_FRAME_TYPE_PING)
                {
                    if((uint16_t)FSI_getRxPingTag(rxbase) != (uint16_t)FSI_FRAME_TAG1)
                    {
                        (error)++;
                    }
                }
                else
                {
                    if((uint16_t)FSI_getRxFrameTag(rxbase) != (uint16_t)FSI_FRAME_TAG1)
                    {
                        (error)++;
                    }
                }
                //
                // If received frame type and tag matches, exit this loop and proceed
                // to next step by sending flush sequence, otherwise clear error and
                // interrupt flag and continue looping.
                //
                if(error == 0)
                {
                    break;
                }

                error = 0;
            }
        }

        //
        // Send a ping frame with frame tag 0001b
        //
        FSI_setTxFrameTag(txbase, FSI_FRAME_TAG1);
        FSI_setTxFrameType(txbase, FSI_FRAME_TYPE_PING);
        FSI_startTxTransmit(txbase);

        FSI_clearRxEvents(rxbase,FSI_RX_EVTMASK);
        rxEventSts = 0;
        while(!(rxEventSts & FSI_RX_EVT_PING_FRAME) && rxTimeOutCntr != 0U)
        {
            DEVICE_DELAY_US(1);
            rxTimeOutCntr--;
            rxEventSts = FSI_getRxEventStatus(rxbase);
        }

        if(rxTimeOutCntr == 0)
        {
            rxTimeOutCntr = COUNTER_TIMEOUT;
            continue;
        }
        else
        {
            // If the TAG recieved is TAG2, switch to dual lane
            if (FSI_getRxPingTag(rxbase) == (uint16_t)FSI_FRAME_TAG2)
            {
                FSI_setRxDataWidth(rxbase, FSI_DATA_WIDTH_2_LANE);
                FSI_setTxDataWidth(txbase, FSI_DATA_WIDTH_2_LANE);
            }

            // If the TAG recieved is TAG4, end calibration
            if (FSI_getRxPingTag(rxbase) == (uint16_t)FSI_FRAME_TAG4)
            {
                break;
            }
            error = 0;
        }

    }


    //
    // Restore
    //

    FSI_setTxFrameTag(txbase, restoreTag);
    FSI_setTxFrameType(txbase, restoreType);
    FSI_setTxPrescale(txbase, restorePrescale);
    FSI_enableTxInterrupt(txbase, FSI_INT1, restoreTXInt1);
    FSI_enableTxInterrupt(txbase, FSI_INT2, restoreTXInt2);
    FSI_enableRxInterrupt(rxbase, FSI_INT1, restoreRXInt1);
    FSI_enableRxInterrupt(rxbase, FSI_INT2, restoreRXInt2);
}
