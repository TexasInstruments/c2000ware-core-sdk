//#############################################################################
// FILE: usbhaudio.h
// TITLE: USB host audio class driver
//#############################################################################
//!
//! Copyright: Copyright (C) 2023 Texas Instruments Incorporated -
//!	All rights reserved not granted herein.
//!	Limited License.
//!
//! Texas Instruments Incorporated grants a world-wide, royalty-free,
//! non-exclusive license under copyrights and patents it now or hereafter
//! owns or controls to make, have made, use, import, offer to sell and sell
//! ("Utilize") this software subject to the terms herein. With respect to the
//! foregoing patent license, such license is granted solely to the extent that
//! any such patent is necessary to Utilize the software alone. The patent
//! license shall not apply to any combinations which include this software,
//! other than combinations with devices manufactured by or for TI 
//! ("TI Devices").
//! No hardware patent is licensed hereunder.
//!
//! Redistributions must preserve existing copyright notices and reproduce this
//! license (including the above copyright notice and the disclaimer and
//! (if applicable) source code license limitations below) in the documentation
//!  and/or other materials provided with the distribution.
//!
//! Redistribution and use in binary form, without modification, are permitted
//! provided that the following conditions are met:
//!
//! * No reverse engineering, decompilation, or disassembly of this software is 
//! permitted with respect to any software provided in binary form.
//! * Any redistribution and use are licensed by TI for use only 
//!   with TI Devices.
//! * Nothing shall obligate TI to provide you with source code for the 
//!   software licensed and provided to you in object code.
//!
//! If software source code is provided to you, modification and redistribution
//! of the source code are permitted provided that the following conditions 
//! are met:
//!
//! * any redistribution and use of the source code, including any resulting
//!   derivative works, are licensed by TI for use only with TI Devices.
//! * any redistribution and use of any object code compiled from the source
//!   code and any resulting derivative works, are licensed by TI for use 
//!   only with TI Devices.
//!
//! Neither the name of Texas Instruments Incorporated nor the names of its
//! suppliers may be used to endorse or promote products derived from this 
//! software without specific prior written permission.
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

