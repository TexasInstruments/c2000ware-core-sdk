//##############################################################################
//
// FILE:   usb_ex8_descriptors.h
//
// TITLE:  The USB descriptor information for this project.
//
//##############################################################################
//
//
// $Copyright:
// Copyright (C) 2014-2023 Texas Instruments Incorporated - http://www.ti.com/
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
//##############################################################################

#ifndef USB_EX8_DESCRIPTORS_H
#define USB_EX8_DESCRIPTORS_H

//
// Globals
//
extern uint32_t const g_ui32ReportDescriptorSize;
extern uint8_t const g_pucReportDescriptor[];
extern tDeviceInfo g_sMouseDeviceInfo;

//
// Function Prototypes
//
extern void HandleHIDDescriptor(uint32_t ui32Index,
                                tUSBRequest *pUSBRequest);
extern void HandleRequests(uint32_t ui32Index, tUSBRequest *pUSBRequest);
extern void ConfigurationChange(uint32_t ui32Index, uint32_t ui32Info);
extern void EP1Handler(uint32_t ui32Index, uint32_t ui32Status);
extern void HandleReset(uint32_t ui32Index);
extern void HandleDisconnect(uint32_t ui32Index);

#endif // USB_EX8_DESCRIPTORS_H

//
// End of file
//
