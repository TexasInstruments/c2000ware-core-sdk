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


#include <fsi_daisy_optimal_delay.h>


//*****************************************************************************
//
//! \brief Forwards frames to next device in daisy-chain topology
//!
//! \details Handles the forwarding of frames to the next device in chain. Used
//!     when calibrating other devices in a daisy-chain topology. Will look for
//!     configured ping Tag to know when to stop forwarding and begin calibrating
//!     or transmittng.
//!
//! \param[in] rxbase is the FSI Rx module base address
//! \param[in] txbase is the FSI Tx module base address
//! \param[in] reliableTXPrescalar is the FSI Tx clock prescalar that
//!            that gurauntees successful communication
//! \param[in] CalibrateTag to transmit for signaling next calibration device
//!
//! \return None.
//
//*****************************************************************************

void FSI_daisy_calibratePassThrough(uint32_t rxbase, uint32_t txbase,
                                   uint16_t txPrescalar, FSI_FrameTag CalibrateTag)
{
    uint16_t rxEventSts = 0;
    uint16_t RX_frameTag = 0;

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

    while(1)
    {
        // Loop until data frame is received
        while(!(rxEventSts & FSI_RX_EVT_DATA_FRAME))
        {
            rxEventSts = FSI_getRxEventStatus(rxbase);

            if(rxEventSts & FSI_RX_EVT_PING_FRAME)
            {
                // Save ping frame tag
                RX_frameTag = FSI_getRxPingTag(rxbase);

                // Forward ping frame to next device
                FSI_setTxFrameType(txbase, FSI_FRAME_TYPE_PING);
                FSI_setTxFrameTag(txbase, (FSI_FrameTag)RX_frameTag);
                FSI_startTxTransmit(txbase);

                // Check if Tag 4 was received
                if(RX_frameTag == (uint16_t)FSI_FRAME_TAG4)
                {
                    // Switch to single data line, if not already set
                    FSI_setRxDataWidth(rxbase, FSI_DATA_WIDTH_1_LANE);
                    FSI_setTxDataWidth(txbase, FSI_DATA_WIDTH_1_LANE);
                }

                // Check if Tag 2 was received
                if(RX_frameTag == (uint16_t)FSI_FRAME_TAG2)
                {
                    // Switch to dual data line mode
                    FSI_setRxDataWidth(rxbase, FSI_DATA_WIDTH_2_LANE);
                    FSI_setTxDataWidth(txbase, FSI_DATA_WIDTH_2_LANE);
                }

                RX_frameTag = 0;

                // Clear ping frame event
                FSI_clearRxEvents(rxbase,FSI_RX_EVT_PING_FRAME);

            }
        }

        //
        // Send the flush sequence
        //
        FSI_executeTxFlushSequence(txbase, txPrescalar);

        DEVICE_DELAY_US(10); // Wait some time for devices to get ready

        // Save data frame tag
        RX_frameTag = FSI_getRxFrameTag(rxbase);

        //
        // Forward data frame to next device
        //
        FSI_setTxFrameType(txbase, FSI_FRAME_TYPE_1WORD_DATA);
        FSI_setTxFrameTag(txbase, (FSI_FrameTag)RX_frameTag);

        FSI_startTxTransmit(txbase);

        FSI_clearRxEvents(rxbase,FSI_RX_EVTMASK);
        rxEventSts = 0;

        // Check if received data frame tag is equal to CalibrateTag
        if(RX_frameTag == (uint16_t)CalibrateTag)
        {
            break; // Exit pass through function
        }

        RX_frameTag = 0;

    }

}

//*****************************************************************************
//
//! \brief Sends data packet with tag to indicate completion of event
//!
//! \details This function sends a 1-word data packet with a provided tag
//! to indicate devices in the signal chain the completion of a predefined event.
//!
//! \param[in] rxbase is the FSI Rx module base address
//! \param[in] txbase is the FSI Tx module base address
//! \param[in] reliableTXPrescalar is the FSI Tx clock prescalar that
//!            that gurauntees successful communication
//! \param[in] CalibrateTag to transmit for signaling next calibration device
//!
//! \return None.
//
//*****************************************************************************

void FSI_signalNextCalibrate(uint32_t rxbase, uint32_t txbase,
                             uint16_t txPrescalar, FSI_FrameTag CalibrateTag)
{
    uint16_t rxEventSts = 0;

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
    // Send the flush sequence
    //
    FSI_executeTxFlushSequence(txbase, txPrescalar);

    DEVICE_DELAY_US(1000);

    //
    // Send a 1 word data frame with frame tag CalibrateTag
    //
    FSI_setTxFrameTag(txbase, CalibrateTag);
    FSI_setTxFrameType(txbase, FSI_FRAME_TYPE_1WORD_DATA);

    FSI_startTxTransmit(txbase);

    // Wait to receive transmitted frame back
    // Loop until data frame is received
    while(!(rxEventSts & FSI_RX_EVT_DATA_FRAME))
    {
        rxEventSts = FSI_getRxEventStatus(rxbase);
    }
}
