//#############################################################################
//! \file   reference/C/source/$FILENAME$
//! \brief  Error
//! \author Vishal Coelho 
//! \date   19-Aug-2015
//! 
//
//  Group:            C2000
//  Target Family:    $DEVICE$
//
//#############################################################################
//
//
// 
// C2000Ware v5.03.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//#############################################################################


//*****************************************************************************
// the includes
//*****************************************************************************
#include "fastrts_error.h"
#include "fastrts_assert.h"
//*****************************************************************************
// defines
//*****************************************************************************
FASTRTS_FILENUM(99)

//*****************************************************************************
// FastRTS_error
//*****************************************************************************
void FastRTS_error(errorHandle eh)
{

    
    // Locals
    uint16_t pass = 0U, fail = 0U;
    uint16_t err_ui16;
    int16_t err_i16;
    uint64_t err_ui64;
    int64_t  err_i64;
    uint32_t err_ui32;
    int32_t  err_i32;
    int16_t  i, max_ep = 0U, min_ep =0U, size = error_getSize(eh);
    fsize_t  err_f;
    FASTRTS_ASSERT(size > 0U);
#if USE_FPU64 == 1
    fsize_t min_e = DBL_MAX;
#else
    fsize_t min_e = FLT_MAX;
#endif
    fsize_t tol   = error_getTolerance(eh);
    void *err     = error_getErrPtr(eh);
    void *test    = error_getTestPtr(eh);
    void *gold    = error_getGoldPtr(eh);
    errorType et  = error_getErrType(eh);
    FASTRTS_ASSERT((et == ERRORTYPE_ABSOLUTE) ||
                   (et == ERRORTYPE_RELATIVE) ||
                   (et == ERRORTYPE_UI32)     ||
                   (et == ERRORTYPE_I32)      ||
                   (et == ERRORTYPE_UI64)     ||
                   (et == ERRORTYPE_I64)      ||
                   (et == ERRORTYPE_UI16)     ||
                   (et == ERRORTYPE_I16));
                   
    // Set the max, min errors (and their position), along with the average
    // and span to 0
    fsize_t avg_e = 0.0, isize = 1.0 / size, max_e = 0.0, span_e = 0.0;
    
    if((et == ERRORTYPE_ABSOLUTE) || (et == ERRORTYPE_RELATIVE))
    {
   
        for(i = 0U; i < size; i++)
        {
            if(et == ERRORTYPE_ABSOLUTE)
            {
                ((fsize_t *)err)[i] = fabs_t(((fsize_t *)test)[i] - 
                                             ((fsize_t *)gold)[i]);
            }
            else //et == ERRORTYPE_RELATIVE
            {
                ((fsize_t *)err)[i] =  fabs_t((((fsize_t *)test)[i] - 
                                               ((fsize_t *)gold)[i])/
                                               ((fsize_t *)test)[i]);
            }
            if(((fsize_t *)err)[i] <= tol)
            {
                pass++;
            }
            else
            {
                fail++;
            }
            if(((fsize_t *)err)[i] > max_e)
            {
                max_e = ((fsize_t *)err)[i];
                max_ep = i;
            }
            if(((fsize_t *)err)[i] < min_e)
            {
                min_e = ((fsize_t *)err)[i];
                min_ep = i;
            }
            // Calculate the average
            avg_e += (((fsize_t *)err)[i] * isize);
            #ifdef _DEBUG
                printf("%4d: %20e - %20e,  err_f = %20e\n",
                    i, ((double *)test)[i], ((double *)gold)[i],
                    ((fsize_t *)err)[i]);
            #endif //_DEBUG
        }
        
        span_e = max_e - min_e;
    }
    else // integer types
    {
        for(i = 0U; i < size; i++)
        {
            if(et == ERRORTYPE_UI16)
            {
                err_ui16 = abs(((uint16_t *)test)[i] - ((uint16_t *)gold)[i]);
                ((uint16_t *)err)[i]  = err_ui16;
                err_f = (fsize_t)err_ui16;
            #ifdef _DEBUG
                printf("%4d: %11u - %11u,  err_ui16 = %11u, err_f = %17.10f\n",
                    i, ((uint16_t *)test)[i], ((uint16_t *)gold)[i],
                    err_ui16, err_f);
            #endif //_DEBUG
            }
            else if(et == ERRORTYPE_I16)
            {
                err_i16 = abs(((int16_t *)test)[i] - ((int16_t *)gold)[i]);
                ((int16_t *)err)[i]  = err_i16;
                err_f = (fsize_t)err_i16;
            #ifdef _DEBUG
                printf("%4d: %11d - %11d,  err_i32 = %11d, err_f = %17.10f\n",
                    i, ((int16_t *)test)[i], ((int16_t *)gold)[i],
                    err_i16, err_f);
            #endif //_DEBUG
            }
            else if(et == ERRORTYPE_UI32)
            {
                err_ui32 = abs(((uint32_t *)test)[i] - ((uint32_t *)gold)[i]);
                ((uint32_t *)err)[i]  = err_ui32;
                err_f = (fsize_t)err_ui32;
            #ifdef _DEBUG
                printf("%4d: %11u - %11u,  err_ui32 = %11u, err_f = %17.10f\n",
                    i, ((uint32_t *)test)[i], ((uint32_t *)gold)[i],
                    err_ui32, err_f);
            #endif //_DEBUG
            }
            else if(et == ERRORTYPE_I32)
            {
                err_i32 = abs(((int32_t *)test)[i] - ((int32_t *)gold)[i]);
                ((int32_t *)err)[i]  = err_i32;
                err_f = (fsize_t)err_i32;
            #ifdef _DEBUG
                printf("%4d: %11d - %11d,  err_i32 = %11d, err_f = %17.10f\n",
                    i, ((int32_t *)test)[i], ((int32_t *)gold)[i],
                    err_i32, err_f);
            #endif //_DEBUG
            }
            else if(et == ERRORTYPE_UI64)
            {
                err_ui64 = abs(((uint64_t *)test)[i] - ((uint64_t *)gold)[i]);
                ((uint64_t *)err)[i]  = err_ui64;
                err_f = (fsize_t)err_ui64;
            #ifdef _DEBUG
                printf("%4d: %19lu - %19lu,  err_ui64 = %19lu"
                       ", err_f = %17.10f\n",
                    i, ((uint64_t *)test)[i], ((uint64_t *)gold)[i],
                    err_ui64, err_f);
            #endif //_DEBUG
            }
            else if(et == ERRORTYPE_I64)
            {
                err_i64 = abs(((int64_t *)test)[i] - ((int64_t *)gold)[i]);
                ((int64_t *)err)[i]  = err_i64;
                err_f = (fsize_t)err_i64;
            #ifdef _DEBUG
                printf("%4d: %19ld - %19ld,  err_i64 = %19ld"
                       ", err_f = %17.10f\n",
                    i, ((int64_t *)test)[i], ((int64_t *)gold)[i],
                    err_i64, err_f);
            #endif //_DEBUG
            }
            else
            {
                // et is wrong
                FASTRTS_ASSERT(0U);
            }
        
            if(err_f <= tol)
            {
                pass++;
            }
            else
            {
                fail++;
            }
            if(err_f > max_e)
            {
                max_e = err_f ;
                max_ep = i;
            }
            if(err_f < min_e)
            {
                min_e = err_f;
                min_ep = i;
            }
            // Calculate the average
            avg_e += (err_f * isize);
        }
        
        span_e = max_e - min_e;
    }
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
    // printf("Maximum Error Data Point -> Test=%15.13e, Gold=%15.13e\n", 
    //     test[max_ep], gold[max_ep]);
    printf("Minimum Error =  %15.13e, at position %d\n", min_e, min_ep);
    printf("Average Error =  %15.13e\n",avg_e);
    printf("Error Span    =  %15.13e\n",span_e);
    printf("Data within error tolerance: %d\n", pass);
    printf("Data outside error tolerance: %d\n", fail);
}

// End of File
