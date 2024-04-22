//###########################################################################
//
// FILE:   ti_guids.h
//
// TITLE:  GUIDs associated with TI Micro USB examples
//
//###########################################################################
//
// $Release Date:  $
// $Copyright:
// Copyright (C) 2013-2024 Texas Instruments Incorporated - http://www.ti.com/
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
//###########################################################################

#ifndef _TI_GUIDS_
#define _TI_GUIDS_

//
// Vendor and Product IDs for the generic bulk device.
//
#define BULK_VID 0x1cbe
#define BULK_PID 0x0003

//
// TI Bulk Device Class GUID
// {F5450C06-EB58-420e-8F98-A76C5D4AFB18}
//
DEFINE_GUID(GUID_DEVCLASS_TI_BULK,
0xF5450C06, 0xEB5B, 0x420E, 0x8F, 0x98, 0xA7, 0x6C, 0x5D, 0x4A, 0xFB, 0x18);

//
// TI Bulk Device Interface GUID
// {6E45736A-2B1B-4078-B772-B3AF2B6FDE1C}
//
DEFINE_GUID(GUID_DEVINTERFACE_TI_BULK,
0x6E45736A, 0x2B1B, 0x4078, 0xB7, 0x72, 0xb3, 0xAF, 0x2B, 0x6F, 0xDE, 0x1C);

#endif

//
// End of file
//
