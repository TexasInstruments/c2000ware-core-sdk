//#############################################################################
//! \file   reference/C/source/$FILENAME$
//! \brief  Error
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
#include "dsp_error.h"
#include "dsp_assert.h"
//*****************************************************************************
// defines
//*****************************************************************************
DSP_FILENUM(1)

//*****************************************************************************
// FastRTS_error
//*****************************************************************************
void DSP_error(errorHandle eh)
{

    
    // Locals
    uint16_t pass = 0U, fail = 0U;
    int16_t i, max_ep = 0U, min_ep =0U, size = error_getSize(eh);
    DSP_ASSERT(size > 0U);
    // Set the max, min errors (and their position), along with the average
    // and span to 0
    fsize_t avg_e = 0.0, isize = 1.0 / size, max_e = 0.0, span_e = 0.0;
#if USE_FPU64 == 1
    fsize_t min_e = DBL_MAX;
#else
    fsize_t min_e = FLT_MAX;
#endif
    fsize_t tol   = error_getTolerance(eh);
    fsize_t *err  = error_getErrPtr(eh);
    fsize_t *test = error_getTestPtr(eh);
    fsize_t *gold = error_getGoldPtr(eh);
    errorType et  = error_getErrType(eh);

    DSP_ASSERT((et == ERRORTYPE_ABSOLUTE) ||
               (et == ERRORTYPE_RELATIVE));

    for(i = 0U; i < size; i++)
    {
        if(et == ERRORTYPE_ABSOLUTE)
        {
            err[i] = fabs_t(test[i] - gold[i]);
        }
        else //et == ERRORTYPE_RELATIVE
        {
            err[i] =  fabs_t((test[i] - gold[i])/test[i]);
        }
        if(err[i] <= tol)
        {
            pass++;
        }
        else
        {
            fail++;
        }
        if(err[i] > max_e)
        {
            max_e = err[i];
            max_ep = i;
        }
        if(err[i] < min_e)
        {
            min_e = err[i];
            min_ep = i;
        }
        // Calculate the average
        avg_e += (err[i] * isize);
    }
    
    span_e = max_e - min_e;
    
    // Write to the object
    error_setMaxErr(eh, max_e);
    error_setMaxErrPos(eh, max_ep);
    error_setMinErr(eh, min_e);
    error_setMinErrPos(eh, min_ep);
    error_setAvgErr(eh, avg_e);
    error_setSpanErr(eh, span_e);
    error_setPass(eh, pass);
    error_setFail(eh, fail);
    
    // Print to the screen
    printf("Maximum Error =  %15.13e, at position %d\n", max_e, max_ep);
    printf("Maximum Error Data Point -> Test=%15.13e, Gold=%15.13e\n", 
           test[max_ep], gold[max_ep]);
    printf("Minimum Error =  %15.13e, at position %d\n", min_e, min_ep);
    printf("Average Error =  %15.13e\n",avg_e);
    printf("Error Span    =  %15.13e\n",span_e);
    printf("Data within error tolerance: %d\n", pass);
    printf("Data outside error tolerance: %d\n", fail);
}

// End of File
