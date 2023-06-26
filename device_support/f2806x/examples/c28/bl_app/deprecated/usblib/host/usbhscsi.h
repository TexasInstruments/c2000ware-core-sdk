//###########################################################################
//
// FILE:   usbhscsi.h
//
// TITLE:  Definitions for the USB host SCSI layer.
//
//###########################################################################
// $TI Release: F2806x C/C++ Header Files and Peripheral Examples V141 $
// $Release Date: January 19, 2015 $
// $Copyright: Copyright (C) 2011-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

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
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
// Prototypes for the APIs exported by the USB SCSI layer.
//
//*****************************************************************************
    extern unsigned long USBHSCSIInquiry(unsigned long ulInPipe,
                                         unsigned long ulOutPipe,
                                         unsigned char *pucBuffer,
                                         unsigned long *pulSize);
    extern unsigned long USBHSCSIReadCapacity(unsigned long ulInPipe,
            unsigned long ulOutPipe,
            unsigned char *pData,
            unsigned long *pulSize);
    extern unsigned long USBHSCSIReadCapacities(unsigned long ulInPipe,
            unsigned long ulOutPipe,
            unsigned char *pData,
            unsigned long *pulSize);
    extern unsigned long USBHSCSIModeSense6(unsigned long ulInPipe,
                                            unsigned long ulOutPipe,
                                            unsigned long ulFlags,
                                            unsigned char *pData,
                                            unsigned long *pulSize);
    extern unsigned long USBHSCSITestUnitReady(unsigned long ulInPipe,
            unsigned long ulOutPipe);
    extern unsigned long USBHSCSIRequestSense(unsigned long ulInPipe,
            unsigned long ulOutPipe,
            unsigned char *pucData,
            unsigned long *pulSize);
    extern unsigned long USBHSCSIRead10(unsigned long ulInPipe,
                                        unsigned long ulOutPipe,
                                        unsigned long ulLBA,
                                        unsigned char *pucData,
                                        unsigned long *pulSize,
                                        unsigned long ulNumBlocks);
    extern unsigned long USBHSCSIWrite10(unsigned long ulInPipe,
                                         unsigned long ulOutPipe,
                                         unsigned long ulLBA,
                                         unsigned char *pucData,
                                         unsigned long *pulSize,
                                         unsigned long ulNumBlocks);

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


