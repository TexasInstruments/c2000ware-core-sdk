//###########################################################################
//
// FILE:   usbddfu_rt.h
//
// TITLE:  Definitions used by runtime DFU class devices.
//
//###########################################################################
// $TI Release: F2806x C/C++ Header Files and Peripheral Examples V141 $
// $Release Date: January 19, 2015 $
// $Copyright: Copyright (C) 2011-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef __USBDDFURT_H__
#define __USBDDFURT_H__

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
//! \addtogroup dfu_device_class_api
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! The size of the memory that should be allocated to create a configuration
//! descriptor for a single instance of the DFU runtime device.  This does not
//! include the configuration descriptor which is automatically ignored by the
//! composite device class.
//!
//! This label is used to compute the value which will be passed to the
//! USBDCompositeInit function in the ulSize parameter.
//
// For reference this is sizeof(g_pDFUInterface) + sizeof(g_pDFUFunctionalDesc)
//
//*****************************************************************************
#define COMPOSITE_DDFU_SIZE     (9 + 9)

//*****************************************************************************
//
//! This value is passed to the client via the callback function provided in
//! the tUSBDDFUDevice structure and indicates that the host has sent a DETACH
//! request to the DFU interface. This request indicates that the device detach
//! from the USB bus and reattach in DFU mode in preparation for a firmware
//! upgrade.  Currently, this is the only event that the DFU runtime class
//! reports to the client.
//!
//! When this event is received, the client should call USBDDFUUpdateBegin()
//! from a non-interrupt context at its earliest opportunity.
//
//*****************************************************************************
#define USBD_DFU_EVENT_DETACH (USBD_DFU_EVENT_BASE + 0)

//*****************************************************************************
//
// PRIVATE
//
// This structure defines the private instance data and state variables for
// DFU devices.  The memory for this structure is pointed to by the
// psPrivateDFUData field in the tUSBDDFUDevice structure passed in the
// USBDDFUCompositeInit() function.
//
//*****************************************************************************
typedef struct
{
    unsigned long ulUSBBase;
    tDeviceInfo *psDevInfo;
    unsigned char ucInterface;
    tBoolean bConnected;
}
tDFUInstance;

//*****************************************************************************
//
//! The structure used by the application to define operating parameters for
//! the DFU device.  Note that, unlike all other devices, this structure does
//! not contain any fields which configure the device descriptor sent back to
//! the host.  The DFU runtime device class must be used as part of a composite
//! device since all it provides is the capability to signal the device to
//! switch into DFU mode in preparation for a firmware upgrade.  Creating a
//! device with nothing but DFU runtime mode capability is rather pointless
//! so this is not supported.
//
//*****************************************************************************
typedef struct
{
    //
    //! A pointer to the callback function which will be called to notify
    //! the application of DETACH requests.
    //
    tUSBCallback pfnCallback;

    //
    //! A client-supplied pointer which will be sent as the first
    //! parameter in all calls made to the pfnCallback function.
    //
    void *pvCBData;

    //
    //! A pointer to private instance data for this device instance.  This
    //! memory must remain accessible for as long as the DFU device is in use
    //! and must not be modified by any code outside the DFU class driver.
    //
    tDFUInstance *psPrivateDFUData;
}
tUSBDDFUDevice;

//*****************************************************************************
//
// Device information structure required to construct the composite device.
//
//*****************************************************************************
extern tDeviceInfo g_sDFUDeviceInfo;

//*****************************************************************************
//
// API Function Prototypes
//
//*****************************************************************************
extern void *USBDDFUCompositeInit(unsigned long ulIndex,
                                  const tUSBDDFUDevice *psDevice);
extern void USBDDFUCompositeTerm(void *pvInstance);
extern void USBDDFUUpdateBegin(void);

//*****************************************************************************
//
// Close the Doxygen group.
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

#endif // __USBDDFURT_H__
