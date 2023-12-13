#ifndef _FPU_TYPES_H_
#define _FPU_TYPES_H_

//#############################################################################
//! \file   include/fpu_types.h
//!
//! \brief  Prototypes and Definitions for the C28x FPU Library
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


//*****************************************************************************
// includes
//*****************************************************************************
#include <stdint.h>
#include "float.h"

//!
//! \defgroup DSP_TYPES_F32 Single Precision DSP Library Data Types

//!
//! \addtogroup DSP_TYPES_F32
// @{
    
#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************
//! Set to 1U if you would like to use legacy names from v1.50.00.00 of the 
//! DSP library; set to 0U (default) to use the new naming convention.
//! It is important to note that not all module elements were updated from the
//! old naming scheme.
//! Rebuild the library and examples after changing this value
//!
#define USE_LEGACY_NAMES    (0U)

//*****************************************************************************
// typedefs
//*****************************************************************************

#ifndef FPU_TYPES
#define FPU_TYPES

//! \brief Complex Float data type for the single precision DSP library
//!
typedef struct {
    //! dat[0] is the real portion while dat[1] is the imaginary part.
    float dat[2]; 
} complex_float;
#endif //FPU_TYPES

// @} //addtogroup

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of _FPU_TYPES_H_

// End of File
