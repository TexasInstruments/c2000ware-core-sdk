//#############################################################################
// FILE: usbhhidkeyboard.h
// TITLE: This file holds the application interfaces for USB
//#############################################################################
// $TI Release: $
// $Release Date: $
// $Copyright:
// Copyright (C) 2009-2025 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef __USBHHIDKEYBOARD_H__
#define __USBHHIDKEYBOARD_H__

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
//! \addtogroup usblib_host_device
//! @{
//
//*****************************************************************************

typedef struct tUSBHKeyboard tUSBHKeyboard;

//*****************************************************************************
//
// The prototype for the host USB Keyboard driver callback function.
//
//*****************************************************************************
typedef void (*tUSBHIDKeyboardCallback)(tUSBHKeyboard *psKbInstance,
                                        uint32_t ui32Event,
                                        uint32_t ui32MsgParam,
                                        void *pvMsgData);

extern tUSBHKeyboard * USBHKeyboardOpen(tUSBHIDKeyboardCallback pfnCallback,
                                        uint8_t *pui8Buffer,
                                        uint32_t ui32BufferSize);
extern uint32_t USBHKeyboardClose(tUSBHKeyboard *psKbInstance);
extern uint32_t USBHKeyboardInit(tUSBHKeyboard *psKbInstance);
extern uint32_t USBHKeyboardModifierSet(tUSBHKeyboard *psKbInstance,
                                        uint32_t ui32Modifiers);
extern uint32_t USBHKeyboardPollRateSet(tUSBHKeyboard *psKbInstance,
                                        uint32_t ui32PollRate);
extern uint32_t USBHKeyboardUsageToChar(tUSBHKeyboard *psKbInstance,
                                        const tHIDKeyboardUsageTable *psTable,
                                        uint8_t ui8UsageID);

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
