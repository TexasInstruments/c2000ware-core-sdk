/*
 * Copyright (c) 2021 Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */




//
// Included Files
//
#include "usb_structs.h"

//******************************************************************************
//
// CDC device callback function prototypes.
//
//*****************************************************************************
uint32_t USBDCDCRxHandler(void *pvCBData, uint32_t ui32Event,
                   uint32_t ui32MsgValue, void *pvMsgData);
uint32_t USBDCDCTxHandler(void *pvCBData, uint32_t ui32Event,
                   uint32_t ui32MsgValue, void *pvMsgData);
uint32_t USBDCDCControlHandler(void *pvCBData, uint32_t ui32Event,
                        uint32_t ui32MsgValue, void *pvMsgData);



extern tUSBBuffer g_sTxBuffer;
extern tUSBBuffer g_sRxBuffer;

//*****************************************************************************
//
//! The structure used by the application to define operating parameters for
//! the CDC device.
//
//*****************************************************************************
tUSBDCDCDevice g_sCDCDevice =
{
    USB_VID_TI_1CBE,
    USB_PID_SERIAL,
    0,
    USB_CONF_ATTR_SELF_PWR,
    USBDCDCControlHandler,
    (void *)&g_sCDCDevice,
    USBBufferEventCallback,
    (void *)&g_sRxBuffer,
    USBBufferEventCallback,
    (void *)&g_sTxBuffer,
    g_pui8StringDescriptors,
    0
};

//******************************************************************************
//
// Receive buffer (from the USB perspective).
//
//******************************************************************************
uint8_t g_pi8USBRxBuffer[256];
uint8_t g_pui8RxBufferWorkspace[USB_BUFFER_WORKSPACE_SIZE];
tUSBBuffer g_sRxBuffer =
{
    false,                                  // This is a receive buffer.
    USBDCDCRxHandler,          // pfnCallback
    (void *)&g_sCDCDevice, // Callback data is our device pointer.
    USBDCDCPacketRead,                      // pfnTransfer
    USBDCDCRxPacketAvailable,               // pfnAvailable
    (void *)&g_sCDCDevice,  // pvHandle
    g_pi8USBRxBuffer,               // pi8Buffer
    myUSB0_LIB_SCI_BUFFER_SIZE          // ui32BufferSize
};

//******************************************************************************
//
// Transmit buffer (from the USB perspective).
//
//******************************************************************************
uint8_t g_pi8USBTxBuffer[256];
uint8_t g_pui8TxBufferWorkspace[USB_BUFFER_WORKSPACE_SIZE];
tUSBBuffer g_sTxBuffer =
{
    true,                                   // This is a transmit buffer.
    USBDCDCTxHandler,              // pfnCallback
    (void *)&g_sCDCDevice,  // Callback data is our device pointer.
    USBDCDCPacketWrite,                     // pfnTransfer
    USBDCDCTxPacketAvailable,               // pfnAvailable
    (void *)&g_sCDCDevice,  // pvHandle
    g_pi8USBTxBuffer,               // pi8Buffer
    myUSB0_LIB_SCI_BUFFER_SIZE      // ui32BufferSize
};



//
// End of file
//
