//#############################################################################
// FILE: usbhscsi.h
// TITLE: Definitions for the USB host SCSI layer
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

#ifndef __USBHSCSI_H__
#define __USBHSCSI_H__

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
// Prototypes for the APIs exported by the USB SCSI layer.
//
//*****************************************************************************
extern uint32_t USBHSCSIInquiry(uint32_t ui32InPipe, uint32_t ui32OutPipe,
                                uint8_t *pui8Buffer, uint32_t *pui32Size);
extern uint32_t USBHSCSIReadCapacity(uint32_t ui32InPipe, uint32_t ui32OutPipe,
                                     uint8_t *pui8Data, uint32_t *pui32Size);
extern uint32_t USBHSCSIReadCapacities(uint32_t ui32InPipe,
                                       uint32_t ui32OutPipe, uint8_t *pui8Data,
                                       uint32_t *pui32Size);
extern uint32_t USBHSCSIModeSense6(uint32_t ui32InPipe, uint32_t ui32OutPipe,
                                   uint32_t ui32Flags, uint8_t *pui8Data,
                                   uint32_t *pui32Size);
extern uint32_t USBHSCSITestUnitReady(uint32_t ui32InPipe,
                                      uint32_t ui32OutPipe);
extern uint32_t USBHSCSIRequestSense(uint32_t ui32InPipe, uint32_t ui32OutPipe,
                                     uint8_t *pui8Data, uint32_t *pui32Size);
extern uint32_t USBHSCSIRead10(uint32_t ui32InPipe, uint32_t ui32OutPipe,
                               uint32_t ui32LBA, uint8_t *pui8Data,
                               uint32_t *pui32Size, uint32_t ui32NumBlocks);
extern uint32_t USBHSCSIWrite10(uint32_t ui32InPipe, uint32_t ui32OutPipe,
                                uint32_t ui32LBA, uint8_t *pui8Data,
                                uint32_t *pui32Size, uint32_t ui32NumBlocks);

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

#endif // __USBHSCSI_H__
