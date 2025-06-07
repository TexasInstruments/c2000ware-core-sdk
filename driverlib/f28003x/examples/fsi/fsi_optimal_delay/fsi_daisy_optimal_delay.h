//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef FSI_DAISY_OPTIMAL_DELAY_H_
#define FSI_DAISY_OPTIMAL_DELAY_H_

#include "device.h"
#include "fsi_optimal_delay.h"


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
//! \param[in] CalibrateTag that when received will end the Pass Through sequence
//!
//! \return None.
//
//*****************************************************************************
void FSI_daisy_calibratePassThrough(uint32_t rxbase, uint32_t txbase,
                                   uint16_t txPrescalar, FSI_FrameTag CalibrateTag);

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
                             uint16_t txPrescalar, FSI_FrameTag CalibrateTag);


#endif /* FSI_DAISY_OPTIMAL_DELAY_H_ */
