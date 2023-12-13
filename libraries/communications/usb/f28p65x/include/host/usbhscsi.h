//#############################################################################
// FILE: usbhscsi.h
// TITLE: Definitions for the USB host SCSI layer
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
