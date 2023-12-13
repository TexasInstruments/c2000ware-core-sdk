//#############################################################################
//! \file   reference/C/source/$FILENAME$
//! \brief  Multiplication of two Real Matrices
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
// the includes
//*****************************************************************************
#include "vector.h"
#include <math.h>

//*****************************************************************************
// defines
//*****************************************************************************
DSP_FILENUM(39)

//*****************************************************************************
// VECTOR_mpyRMbyRM
//*****************************************************************************
void VECTOR_mpyRMbyRM(fsize_t *y, const fsize_t *w, 
                      const fsize_t *x, const uint16_t m, 
                      const uint16_t n, const uint16_t p)
{
    //Locals
    uint16_t i, j, k;
    
    // Row-Major Order (Matrices are stored row by row)
    //
    // for(i = 0U; i < m; i++)
    // {
    //     for(j = 0U; j < p; j++)
    //     {
    //         *(y + i*m + j) = (fsize_t)0.0;
    //         for(k = 0U; k < n; k++)
    //         {
    //             *(y + i*m + j) += *(w + i*n + k) * *(x + k*p + j);
    //         }
    //     #ifdef _DEBUG
    //         // Debugging message
    //         printf("y[%4d][%4d]=%10.7f\n", i, j, *(y + i*m + j));
    //     #endif
    //     }
    // }
    
    // Column-Major Order (Matrices are stored column by column)
    //
    for(i = 0U; i < m; i++)
    {
        for(j = 0U; j < p; j++)
        {
            *(y + i + j*p) = (fsize_t)0.0;
            for(k = 0U; k < n; k++)
            {
                *(y + i + j*p) += *(w + i + k*m) * *(x + j*n + k);
            }
        #ifdef _DEBUG
            // Debugging message
            printf("y[%4d][%4d]=%10.7f\n", i, j, *(y + i*m + j));
        #endif
        }
    }
}

// End of File
