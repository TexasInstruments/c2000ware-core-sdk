//###########################################################################
//
// FILE:   usbdevice.h
//
// TITLE:  Types and definitions used during USB enumeration.
//
//###########################################################################
// $TI Release: F2806x C/C++ Header Files and Peripheral Examples V141 $
// $Release Date: January 19, 2015 $
// $Copyright: Copyright (C) 2011-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef __USBDEVICE_H__
#define __USBDEVICE_H__

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
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! The maximum number of independent interfaces that any single device
//! implementation can support.  Independent interfaces means interface
//! descriptors with different bInterfaceNumber values - several interface
//! descriptors offering different alternative settings but the same interface
//! number count as a single interface.
//
//*****************************************************************************
#define USB_MAX_INTERFACES_PER_DEVICE 8

#include "./usbdevicepriv.h"

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! This structure is passed to the USB library on a call to USBDCDInit and
//! provides the library with information about the device that the
//! application is implementing.  It contains functions pointers for the
//! various USB event handlers and pointers to each of the standard device
//! descriptors.
//
//*****************************************************************************
struct tDeviceInfo
{
    //
    //! A pointer to a structure containing pointers to event handler functions
    //! provided by the client to support the operation of this device.
    //
    tCustomHandlers sCallbacks;

    //
    //! A pointer to the device descriptor for this device.
    //
    const unsigned char *pDeviceDescriptor;

    //
    //! A pointer to an array of configuration descriptor pointers.  Each entry
    //! in the array corresponds to one configuration that the device may be set
    //! to use by the USB host.  The number of entries in the array must
    //! match the bNumConfigurations value in the device descriptor
    //! array, pDeviceDescriptor.
    //
    const tConfigHeader * const *ppConfigDescriptors;

    //
    //! A pointer to the string descriptor array for this device.  This array
    //! must be arranged as follows:
    //!
    //!   - [0]   - Standard descriptor containing supported language codes.
    //!   - [1]   - String 1 for the first language listed in descriptor 0.
    //!   - [2]   - String 2 for the first language listed in descriptor 0.
    //!   - ...
    //!   - [n]   - String n for the first language listed in descriptor 0.
    //!   - [n+1] - String 1 for the second language listed in descriptor 0.
    //!   - ...
    //!   - [2n]  - String n for the second language listed in descriptor 0.
    //!   - [2n+1]- String 1 for the third language listed in descriptor 0.
    //!   - ...
    //!   - [3n]  - String n for the third language listed in descriptor 0.
    //!
    //! and so on.
    //
    const unsigned char * const *ppStringDescriptors;

    //
    //! The total number of descriptors provided in the ppStringDescriptors
    //! array.
    //
    unsigned long ulNumStringDescriptors;

    //
    //! A structure defining how the USB controller FIFO is to be partitioned
    //! between the various endpoints.  This member can be set to point to
    //! g_sUSBDefaultFIFOConfig if the default FIFO configuration is acceptable
    //! This configuration sets each endpoint FIFO to be single buffered and
    //! sized to hold the maximum packet size for the endpoint.
    //
    const tFIFOConfig *psFIFOConfig;

    //
    //! This value will be passed back to all call back functions so that
    //! they have access to individual instance data based on the this pointer.
    //
    void *pvInstance;

    //
    //! The generic device instance data for this device.  This will be set
    //! by the call to DCDInit() which is usually made when the applicaiton
    //! calls the class specific initialization function.
    //
    tDeviceInstance *psDevice;
};

//*****************************************************************************
//
// The default USB endpoint FIFO configuration structure.  This structure
// contains definitions to set all USB FIFOs into single buffered mode with
// no DMA use.  Each endpoint's FIFO is sized to hold the largest maximum
// packet size for any interface alternate setting in the current config
// descriptor.  A pointer to this structure may be passed in the psFIFOConfig
// field of the tDeviceInfo structure passed to USBCDCInit if the application
// does not require any special handling of the USB controller FIFO.
//
//*****************************************************************************
    extern const tFIFOConfig g_sUSBDefaultFIFOConfig;

//*****************************************************************************
//
// Public APIs offered by the USB library device control driver.
//
//*****************************************************************************
    extern void USBDCDInit(unsigned long ulIndex, tDeviceInfo *psDevice);
    extern void USBDCDTerm(unsigned long ulIndex);
    extern void USBDCDStallEP0(unsigned long ulIndex);
    extern void USBDCDRequestDataEP0(unsigned long ulIndex, unsigned char *pucData,
                                     unsigned long ulSize);
    extern void USBDCDSendDataEP0(unsigned long ulIndex, unsigned char *pucData,
                                  unsigned long ulSize);
    extern void USBDCDSetDefaultConfiguration(unsigned long ulIndex,
            unsigned long ulDefaultConfig);
    extern unsigned long USBDCDConfigDescGetSize(const tConfigHeader *psConfig);
    extern unsigned long USBDCDConfigDescGetNum(const tConfigHeader *psConfig,
            unsigned long ulType);
    extern tDescriptorHeader *USBDCDConfigDescGet(const tConfigHeader *psConfig,
            unsigned long ulType,
            unsigned long ulIndex,
            unsigned long *pulSection);
    extern unsigned long
    USBDCDConfigGetNumAlternateInterfaces(const tConfigHeader *psConfig,
                                          unsigned char ucInterfaceNumber);
    extern tInterfaceDescriptor *
    USBDCDConfigGetInterface(const tConfigHeader *psConfig,
                             unsigned long ulIndex, unsigned long ulAltCfg,
                             unsigned long *pulSection);
    extern tEndpointDescriptor *
    USBDCDConfigGetInterfaceEndpoint(const tConfigHeader *psConfig,
                                     unsigned long ulInterfaceNumber,
                                     unsigned long ulAltCfg,
                                     unsigned long ulIndex);
    extern void USBDCDPowerStatusSet(unsigned long ulIndex, unsigned char ucPower);
    extern tBoolean USBDCDRemoteWakeupRequest(unsigned long ulIndex);

//*****************************************************************************
//
// Early releases of the USB library had the following function named
// incorrectly.  This macro ensures that any code which used the previous name
// will still operate as expected.
//
//*****************************************************************************
#ifndef DEPRECATED
#define USBCDCConfigGetInterfaceEndpoint(a, b, c, d)                          \
            USBDCDConfigGetInterfaceEndpoint((a), (b), (c), (d))
#endif

//*****************************************************************************
//
// Device mode interrupt handler for controller index 0.
//
//*****************************************************************************
    extern void USB0DeviceIntHandler(void);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __USBENUM_H__


