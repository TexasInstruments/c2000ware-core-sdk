//###########################################################################
//
// FILE:   bulk_libusb.c
//
// TITLE: Implementation of the bulk_usb interface using the linusb-win32 API.
//
//##############################################################################
//
// $Release Date: $
// $Copyright:
// Copyright (C) 2014-2024 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef USE_WINUSB

//
// Included Files
//
#include "libusb-win32\include\usb.h"

//
// Structure containing handles and information required to communicate with
// the USB bulk device.
//
typedef struct
{
    usb_dev_handle *hDevice;

} tDeviceInfo;

tDeviceInfo devInfo;

//
// Functions
//

//****************************************************************************
//
// Determines that the required USB device is present, opens it and gathers
// required information to allow us to read and write it.
//
// \param None.
//
// This function is called to initialize the USB device and perform one-off
// setup required to allocate handles allowing the application to read and
// write the device endpoints.
//
// \return Returns \e TRUE on success or \e FALSE on failure. In failing
// cases, GetLastError() can be called to determine the cause.
//
//****************************************************************************
BOOL InitializeDevice(void)
{
    //
    // Initialize the libusb-win32 subsystem.
    //
    usb_init();

    return(TRUE);
}

//****************************************************************************
//
// Cleans up and free resources associated with the USB device communication
// prior to exiting the application.
//
// \param None.
//
// This function should be called prior to exiting the application to free
// the resources allocated during InitializeDevice().
//
// \return Returns \e TRUE on success or \e FALSE on failure.
//
//****************************************************************************
BOOL TerminateDevice(void)
{
    return(TRUE);
}

//****************************************************************************
//
// Writes a buffer of data to the USB device via the bulk OUT endpoint.
//
// \param pcBuffer points to the first byte of data to send.
// \param ulSize contains the number of bytes of data to send.
// \param pulWritten is a pointer which will be written with the number of
// bytes of data actually written to the device.
//
// This function is used to send data to the USB device via its bulk OUT endpoint.
//
// \return Returns \e TRUE on success or \e FALSE on failure.
//
//****************************************************************************
BOOL WriteUSBPacket(unsigned char *pcBuffer, unsigned long ulSize,
                           unsigned long *pulWritten)
{
    return(TRUE);
}

//****************************************************************************
//
// Reads data from the USB device via the bulk IN endpoint.
//
// \param pcBuffer points to a buffer into which the data from the device will
// be written.
// \param ulSize contains the number of bytes that are requested from the
// device.
// \param pulRead is a pointer which will be written with the number of
// bytes of data actually read from the device.
//
// This function is used to receivedata from the USB device via its bulk IN
// endpoint.
//
// \return Returns \e TRUE on success or \e FALSE on failure.
//
//****************************************************************************
BOOL ReadUSBPacket(unsigned char *pcBuffer, unsigned long ulSize,
                          unsigned long *pulRead)
{
    return(TRUE);
}

#endif // not defined USE_WINUSB

//
// End of file
//
