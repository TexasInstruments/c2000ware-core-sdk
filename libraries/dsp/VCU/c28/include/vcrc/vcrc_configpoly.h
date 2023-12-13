//###############################################################################
//! \file /2838x_vcrc_config_poly/vcrc_configpoly.h
//!
//! \brief  Header file for the configurable polynomial and data sizes (VCRC and C)
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

//!
//! \defgroup VCRC_APIS VCRC Configurable Polynomial APIs

//!
//! \ingroup VCRC_APIS
// @{

//*****************************************************************************
// function prototypes
//*****************************************************************************

//! \brief Runs the CRC routine using provided polynomial
//!        with the input bits reversed, message size in bytes. 
//!
//!  The polynomial to be used is set by the element \b polynomial in the \b CRC_Obj.
//!  The size of the polynomial is set by the element \b polySize in the \b CRC_Obj.
//!  For example - to use a 1 bit polynomial \b polySize must be set to 0x0 and 
//!  to use a 32 bit polynomial \b polySize must be set to 0x1F. The size of the data is set 
//!  by the element \b dataSize in \b the CRC_Obj. \b Datasize refers to the integral unit 
//!  on which the CRC is computed. For example - to use data size of 1 bit \b dataSize must be set
//!  to 0x0 and data size of 8 bit is set by setting \b dataSize to a value of 0x7. These values
//!  finally translate to elements in the \b VCRCSIZE register - \b PSIZE and \b DSIZE fields and they are 
//!  set in the functions \b _CRC_runConfigPolyBytes implemented in the asm file \b vcrc_configpoly_asm.asm.
//!  Total size of the message on which the CRC to be computed is specified by the element \b MsgBytes 
//!  in the \b CRC_Obj.
//!
//! \param[in] hndCRC handle to the CRC object
//
void CRC_runConfigPolyBytesReflected(CRC_Handle hndCRC);

//! \brief Runs the CRC routine using provided polynomial
//!        with the input bits reversed, message size in bits. 
//!
//!  The polynomial to be used is set by the element \b polynomial in the \b CRC_Obj.
//!  The size of the polynomial is set by the element \b polySize in the \b CRC_Obj.
//!  For example - to use a 1 bit polynomial \b polySize must be set to 0x0 and 
//!  to use a 32 bit polynomial \b polySize must be set to 0x1F. The size of the data is set 
//!  by the element \b dataSize in \b the CRC_Obj. \b Datasize refers to the integral unit 
//!  on which the CRC is computed. For example - to use data size of 1 bit \b dataSize must be set
//!  to 0x0 and data size of 8 bit is set by setting \b dataSize to a value of 0x7. These values
//!  finally translate to elements in the \b VCRCSIZE register - \b PSIZE and \b DSIZE fields and they are 
//!  set in the functions \b _CRC_runConfigPolyBytes implemented in the asm file \b vcrc_configpoly_asm.asm.
//!  Total size of the message on which the CRC to be computed is specified by the element \b MsgBytes 
//!  in the \b CRC_Obj.
//!
//! \param[in] hndCRC handle to the CRC object
//
void CRC_runConfigPolyBitsReflected(CRC_Handle hndCRC);

//! \brief Runs the CRC routine using provided polynomial with message size in bytes. 
//!
//!  The polynomial to be used is set by the element \b polynomial in the \b CRC_Obj.
//!  The size of the polynomial is set by the element \b polySize in the \b CRC_Obj.
//!  For example - to use a 1 bit polynomial \b polySize must be set to 0x0 and 
//!  to use a 32 bit polynomial \b polySize must be set to 0x1F. The size of the data is set 
//!  by the element \b dataSize in \b the CRC_Obj. \b Datasize refers to the integral unit 
//!  on which the CRC is computed. For example - to use data size of 1 bit \b dataSize must be set
//!  to 0x0 and data size of 8 bit is set by setting \b dataSize to a value of 0x7. These values
//!  finally translate to elements in the \b VCRCSIZE register - \b PSIZE and \b DSIZE fields and they are 
//!  set in the functions \b _CRC_runConfigPolyBytes implemented in the asm file \b vcrc_configpoly_asm.asm.
//!  Total size of the message on which the CRC to be computed is specified by the element \b MsgBytes 
//!  in the \b CRC_Obj.
//!
//! \param[in] hndCRC handle to the CRC object
//
void CRC_runConfigPolyBytes(CRC_Handle hndCRC);

//! \brief Runs the CRC routine using provided polynomial with message size in bits. 
//!
//!  The polynomial to be used is set by the element \b polynomial in the \b CRC_Obj.
//!  The size of the polynomial is set by the element \b polySize in the \b CRC_Obj.
//!  For example - to use a 1 bit polynomial \b polySize must be set to 0x0 and 
//!  to use a 32 bit polynomial \b polySize must be set to 0x1F. The size of the data is set 
//!  by the element \b dataSize in \b the CRC_Obj. \b Datasize refers to the integral unit 
//!  on which the CRC is computed. For example - to use data size of 1 bit \b dataSize must be set
//!  to 0x0 and data size of 8 bit is set by setting \b dataSize to a value of 0x7. These values
//!  finally translate to elements in the \b VCRCSIZE register - \b PSIZE and \b DSIZE fields and they are 
//!  set in the functions \b _CRC_runConfigPolyBytes implemented in the asm file \b vcrc_configpoly_asm.asm.
//!  Total size of the message on which the CRC to be computed is specified by the element \b MsgBytes 
//!  in the \b CRC_Obj.
//!
//! \param[in] hndCRC handle to the CRC object
//
void CRC_runConfigPolyBits(CRC_Handle hndCRC);

// @} //ingroup
