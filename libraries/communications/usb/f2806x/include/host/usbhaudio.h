//#############################################################################
// FILE: usbhaudio.h
// TITLE: USB host audio class driver
//#############################################################################
// $TI Release: $
// $Release Date: $
// $Copyright:
// Copyright (C) 2009-2024 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef __USBHAUDIO_H__
#define __USBHAUDIO_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \addtogroup usblib_host_class
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
// USB host audio specific events
//
//*****************************************************************************

//*****************************************************************************
//
//! This USB host audio event indicates that the device is connected and
//! ready to send or receive buffers.  The \e pvBuffer and \e ui32Param
//! values are not used in this event.
//
//*****************************************************************************
#define USBH_AUDIO_EVENT_OPEN   (USBH_AUDIO_EVENT_BASE + 0)

//*****************************************************************************
//
//! This USB host audio event indicates that the previously connected device
//! has been disconnected. The \e pvBuffer and \e ui32Param values are not used
//! in this event.
//
//*****************************************************************************
#define USBH_AUDIO_EVENT_CLOSE  (USBH_AUDIO_EVENT_BASE + 1)

//*****************************************************************************
//
// This definition is used with the USBHostAudioFormatGet() and
// USBHostAudioFormatSet() API's to determine if the audio input is being
// accesses(USBH_AUDIO_FORMAT_IN set) or audio output(USBH_AUDIO_FORMAT clear).
//
//*****************************************************************************
#define USBH_AUDIO_FORMAT_IN    0x00000001
#define USBH_AUDIO_FORMAT_OUT   0x00000000

typedef struct
{
    uint8_t ui8Channels;
    uint8_t ui8Bits;
    uint32_t ui32SampleRate;
}
tUSBAudioFormat;

typedef struct tUSBHostAudioInstance tUSBHostAudioInstance;

//*****************************************************************************
//
// The prototype for the host USB Audio driver callback function.
//
//*****************************************************************************
typedef void (*tUSBHostAudioCallback)(tUSBHostAudioInstance *psAudioInstance,
                                      uint32_t ui32Event,
                                      uint32_t ui32MsgParam,
                                      void *pvMsgData);

//*****************************************************************************
//
// API Function Prototypes
//
//*****************************************************************************
extern tUSBHostAudioInstance * USBHostAudioOpen(uint32_t ui32Index,
                                           tUSBHostAudioCallback pfnCallback);
extern void USBHostAudioClose(tUSBHostAudioInstance *psAudioInstance);
extern int32_t USBHostAudioPlay(tUSBHostAudioInstance *psAudioInstance,
                                void *pvBuffer, uint32_t ui32Size,
                                tUSBHostAudioCallback pfnCallback);

extern uint32_t USBHostAudioFormatGet(tUSBHostAudioInstance *psAudioInstance,
                                      uint32_t ui32SampleRate,
                                      uint32_t ui32Bits, uint32_t ui32Channels,
                                      uint32_t ui32Flags);
extern uint32_t USBHostAudioFormatSet(tUSBHostAudioInstance *psAudioInstance,
                                      uint32_t ui32SampleRate,
                                      uint32_t ui32Bits, uint32_t ui32Channels,
                                      uint32_t ui32Flags);

extern int32_t USBHostAudioRecord(tUSBHostAudioInstance *psAudioInstance,
                                  void *pvBuffer, uint32_t ui32Size,
                                  tUSBHostAudioCallback pfnAudioCallback);

extern uint32_t USBHostAudioVolumeGet(tUSBHostAudioInstance *psAudioInstance,
                                      uint32_t ui32Interface,
                                      uint32_t ui32Channel);

extern void USBHostAudioVolumeSet(tUSBHostAudioInstance *psAudioInstance,
                                  uint32_t ui32Interface, uint32_t ui32Channel,
                                  uint32_t ui32Value);

extern uint32_t USBHostAudioVolumeMaxGet(tUSBHostAudioInstance *psAudioInstance,
                                         uint32_t ui32Interface,
                                         uint32_t ui32Channel);

extern uint32_t USBHostAudioVolumeMinGet(tUSBHostAudioInstance *psAudioInstance,
                                         uint32_t ui32Interface,
                                         uint32_t ui32Channel);

extern uint32_t USBHostAudioVolumeResGet(tUSBHostAudioInstance *psAudioInstance,
                                           uint32_t ui32Interface,
                                           uint32_t ui32Channel);

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif

