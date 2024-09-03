#ifndef _FASTRTS_ERROR_H_
#define _FASTRTS_ERROR_H_
//#############################################################################
//! \file   reference/C/include/$FILENAME$
//! \brief  Fast RTS Error Header File
//! \author Vishal Coelho 
//! \date   14-Sep-2015
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
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "fastrts.h"

//!
//! \defgroup FASTRTS_ERROR Error Metrics

//!
//! \ingroup FASTRTS_ERROR
//@{

#ifdef __cplusplus
extern "C" {
#endif
//*****************************************************************************
// typedefs
//*****************************************************************************
//! \brief The error type enumeration
//!
typedef enum{
    ERRORTYPE_ABSOLUTE = 0, //!< Absolute error
    ERRORTYPE_RELATIVE = 1, //!< Relative error
    ERRORTYPE_UI32     = 2, //!< unsigned 32-bit error
    ERRORTYPE_I32      = 3, //!< signed 32-bit error
    ERRORTYPE_UI64     = 4, //!< unsigned 64-bit error
    ERRORTYPE_I64      = 5, //!< signed 64-bit error
    ERRORTYPE_UI16     = 6, //!< unsigned 16-bit error
    ERRORTYPE_I16      = 7, //!< signed 16-bit error
}errorType;

//! \brief The Error Structure
//!
typedef struct _error_Obj_{
    void *testPtr;     //!< Pointer to the test vector
    void *goldPtr;     //!< Pointer to the Reference vector
    void *errPtr;      //!< Pointer to the error buffer
    errorType et;      //!< The error type enumeration
    fsize_t tolerance; //!< Error Tolerance
    fsize_t maxErr;    //!< The maximum error
    uint16_t maxErrPos;//!< The index into the error buffer (for max error)
    fsize_t minErr;    //!< The minimum error
    uint16_t minErrPos;//!< The index into the error buffer (for min error)
    fsize_t avgErr;    //!< The average error
    fsize_t spanErr;   //!< Difference between the min and max erro
    int16_t size;      //!< The size of the buffers
    uint16_t pass;     //!< Number of data points within the error tolerance
    uint16_t fail;     //!< Number of data points outside the error tolerance
}error;

//! \brief The Handle to the Error Object
//!
typedef error *errorHandle;

//*****************************************************************************
// 'inline' function
//*****************************************************************************
//! \brief Set the Error Object Test Pointer
//! \param[in] eh , handle to the 'error' object
//! \param[in] tp , pointer to the test array
//!
static inline void error_setTestPtr(errorHandle eh, const void *tp)
{
    eh->testPtr = (void *)tp;
}

//! \brief Get the Error Object Test Pointer
//! \param[in] eh , handle to the 'error' object
//! \return pointer to the test array
//!
static inline void* error_getTestPtr(errorHandle eh)
{
    return(eh->testPtr);
}

//! \brief Set the Error Object Gold Pointer
//! \param[in] eh , handle to the 'error' object
//! \param[in] tp , pointer to the gold array
//!
static inline void error_setGoldPtr(errorHandle eh, const void *gp)
{
    eh->goldPtr = (void *)gp;
}

//! \brief Get the Error Object Gold Pointer
//! \param[in] eh , handle to the 'error' object
//! \return pointer to the gold array
//!
static inline void* error_getGoldPtr(errorHandle eh)
{
    return(eh->goldPtr);
}

//! \brief Set the Error Object Error Pointer
//! \param[in] eh , handle to the 'error' object
//! \param[in] ep , pointer to the gold array
//!
static inline void error_setErrPtr(errorHandle eh, const void *ep)
{
    eh->errPtr = (void *)ep;
}

//! \brief Get the Error Object Error Pointer
//! \param[in] eh , handle to the 'error' object
//! \return pointer to the error array
//!
static inline void* error_getErrPtr(errorHandle eh)
{
    return(eh->errPtr);
}

//! \brief Set the Error Object Error Type
//! \param[in] eh , handle to the 'error' object
//! \param[in] et , Error Type
//!
static inline void error_setErrType(errorHandle eh, const errorType et)
{
    eh->et = (errorType)et;
}

//! \brief Get the Error Object Error Type
//! \param[in] eh , handle to the 'error' object
//! \return Error Type
//!
static inline errorType error_getErrType(errorHandle eh)
{
    return(eh->et);
}

//! \brief Set the Error Object Error Tolerance
//! \param[in] eh , handle to the 'error' object
//! \param[in] tolerance , Error Tolerance
//!
static inline void error_setTolerance(errorHandle eh, const fsize_t tolerance)
{
    eh->tolerance = (fsize_t)tolerance;
}

//! \brief Get the Error Object Error Tolerance
//! \param[in] eh , handle to the 'error' object
//! \return Error Tolerance
//!
static inline fsize_t error_getTolerance(errorHandle eh)
{
    return(eh->tolerance);
}

//! \brief Set the Error Object Max Error
//! \param[in] eh , handle to the 'error' object
//! \param[in] maxErr , Maximum Error
//!
static inline void error_setMaxErr(errorHandle eh, const fsize_t maxErr)
{
    eh->maxErr = (fsize_t)maxErr;
}

//! \brief Get the Error Object Max Error
//! \param[in] eh , handle to the 'error' object
//! \return Maximum Error
//!
static inline fsize_t error_getMaxErr(errorHandle eh)
{
    return(eh->maxErr);
}

//! \brief Set the Error Object Max Error Position
//! \param[in] eh , handle to the 'error' object
//! \param[in] maxErrPos , Maximum Error Position
//!
static inline void error_setMaxErrPos(errorHandle eh, const uint16_t maxErrPos)
{
    eh->maxErrPos = (int16_t)maxErrPos;
}

//! \brief Get the Error Object Max Error Position
//! \param[in] eh , handle to the 'error' object
//! \return Maximum Error Position
//!
static inline uint16_t error_getMaxErrPos(errorHandle eh)
{
    return(eh->maxErrPos);
}

//! \brief Set the Error Object Min Error
//! \param[in] eh , handle to the 'error' object
//! \param[in] minErr , Minimum Error Position
//!
static inline void error_setMinErr(errorHandle eh, const fsize_t minErr)
{
    eh->minErr = (fsize_t)minErr;
}

//! \brief Get the Error Object Min Error
//! \param[in] eh , handle to the 'error' object
//! \return Minimum Error
//!
static inline fsize_t error_getMinErr(errorHandle eh)
{
    return(eh->minErr);
}

//! \brief Set the Error Object Min Error Position
//! \param[in] eh , handle to the 'error' object
//! \param[in] minErrPos , Minimum Error Position
//!
static inline void error_setMinErrPos(errorHandle eh, const uint16_t minErrPos)
{
    eh->minErrPos = (int16_t)minErrPos;
}

//! \brief Get the Error Object Min Error Position
//! \param[in] eh , handle to the 'error' object
//! \return Minimum Error Position
//!
static inline uint16_t error_getMinErrPos(errorHandle eh)
{
    return(eh->minErrPos);
}

//! \brief Set the Error Object Avg Error
//! \param[in] eh , handle to the 'error' object
//! \param[in] avgErr , Average Error
//!
static inline void error_setAvgErr(errorHandle eh, const fsize_t avgErr)
{
    eh->avgErr = (fsize_t)avgErr;
}

//! \brief Get the Error Object Avg Error
//! \param[in] eh , handle to the 'error' object
//! \return Average Error
//!
static inline fsize_t error_getAvgErr(errorHandle eh)
{
    return(eh->avgErr);
}

//! \brief Set the Error Object Span Error
//! \param[in] eh , handle to the 'error' object
//! \param[in] spanErr , Error Span
//!
static inline void error_setSpanErr(errorHandle eh, const fsize_t spanErr)
{
    eh->spanErr = (fsize_t)spanErr;
}

//! \brief Get the Error Object error span
//! \param[in] eh , handle to the 'error' object
//! \return Error Span (difference between man and min error)
//!
static inline fsize_t error_getSpanErr(errorHandle eh)
{
    return(eh->spanErr);
}

//! \brief Set the Error Object Array Size
//! \param[in] eh , handle to the 'error' object
//! \param[in] sz , size of the three arrays (test, gold, err)
//!
static inline void error_setSize(errorHandle eh, const int16_t sz)
{
    eh->size = (int16_t)sz;
}

//! \brief Get the Error Object Array Size
//! \param[in] eh , handle to the 'error' object
//! \return size of the three arrays (test, gold, err)
//!
static inline int16_t error_getSize(errorHandle eh)
{
    return(eh->size);
}

//! \brief Reset the Error Object Pass Count
//! \param[in] eh , handle to the 'error' object
//! \param[in] pc , pass count
static inline void error_setPass(errorHandle eh, const uint16_t pc)
{
    eh->pass = (uint16_t)pc;
}

//! \brief Get the Error Object Pass Count
//! \param[in] eh , handle to the 'error' object
//! \return the pass count
static inline uint16_t error_getPass(errorHandle eh)
{
    return(eh->pass);
}

//! \brief Reset the Error Object Fail Count
//! \param[in] eh , handle to the 'error' object
//! \param[in] fc , fail count
static inline void error_setFail(errorHandle eh, const uint16_t fc)
{
    eh->fail = (uint16_t)fc;
}


//! \brief Get the Error Object Fail Count
//! \param[in] eh , handle to the 'error' object
//! \return the fail count
static inline uint16_t error_getFail(errorHandle eh)
{
    return(eh->pass);
}

//*****************************************************************************
// 'extern' function prototypes
//*****************************************************************************
//! \brief The Error Function
//! \param[in] eh , Handle to the Error Object
//!
//! This function will calculate the error (the type is given in the object) 
//! between the test and gold (reference) arrays.
//!
//! \return None
extern void FastRTS_error(errorHandle eh);

#ifdef __cplusplus
}
#endif // extern "C"
//@}  // ingroup

#endif // end of _FASTRTS_ERROR_H_ definition
