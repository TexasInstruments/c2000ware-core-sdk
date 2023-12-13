//#############################################################################
//! \file CFFT_f32_sincostable.c
//!
//! \brief  32-bit floating point Complex FFT Sin/Cos Table Generation
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



//-----------------------------------------------------------------------------
// Function To Generate Complex FFT Coefficient (twiddle) Table:
//-----------------------------------------------------------------------------
// CFFT  Stages Address  Table Value                  
// SIZE           x16
//------+------+-------+------------------------------------------------
//  256 |   8  |     0 | SIN(   0*pi/128 )                    
//      .      .       .
//      |      |   128 | SIN(  64*pi/128 ) = COS(  0*pi/128)  
//      .      .       .
//      |      |   254 | SIN( 127*pi/128 ) = COS( 63*pi/128)
//      |      |   256 | SIN( 128*pi/128 ) = COS( 64*pi/128)
//      .      .       .
//      |      |   382 | SIN( 191*pi/128 ) = COS(127*pi/128)
//------+------+-------+------------------------------------------------
//  512 |   9  |     0 | SIN(   0*pi/256 )                    
//      .      .       .
//      |      |   256 | SIN( 128*pi/256 ) = COS(  0*pi/256)  
//      .      .       .
//      |      |   510 | SIN( 255*pi/256 ) = COS(127*pi/256)
//      |      |   512 | SIN( 256*pi/256 ) = COS(128*pi/256)
//      .      .       .
//      |      |   766 | SIN( 383*pi/256 ) = COS(255*pi/256)
//------+------+-------+------------------------------------------------
// 1024 |  10  |     0 | SIN(   0*pi/512 )                   
//      .      .       .
//      |      |   512 | SIN( 256*pi/512 ) = COS(  0*pi/512)  
//      .      .       .
//      |      |  1022 | SIN( 511*pi/512 ) = COS(255*pi/512)
//      |      |  1024 | SIN( 512*pi/512 ) = COS(256*pi/512)
//      .      .       .
//      |      |  1534 | SIN( 767*pi/512 ) = COS(511*pi/512)
//------+------+-------+------------------------------------------------

#include "math.h"
#include "fpu_cfft.h"

void CFFT_f32_sincostable(CFFT_F32_STRUCT_Handle cfft)
{
    int16_t    i;
    int16_t    TableSize;
    float    Rad;
    float    RadStep;
    
    RadStep = 1.57079632795f;    // RadStep = pi/2

    Rad = 0.0f;

    for(i=0; i < (cfft->Stages - 2); i++)
    {
        RadStep = RadStep * 0.5f;
    }

    TableSize = (1 << (cfft->Stages - 1));
    TableSize = TableSize + (TableSize >> 1);
    for(i=0; i < TableSize; i++)
    {
        cfft->CoefPtr[i] = sinf(Rad);
        Rad = Rad + RadStep;
    }

}

// End of file
