#ifndef _FASTRTS_ASSERT_H_
#define _FASTRTS_ASSERT_H_
//#############################################################################
//! \file   reference/C/include/$FILENAME$
//! \brief  Fast RTS Assert Header File
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
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
//!
//! \defgroup FASTRTS_ASSERT Code Development with Assertion

//!
//! \ingroup FASTRTS_ASSERT
//@{

#ifdef __cplusplus
extern "C" {
#endif
//*****************************************************************************
//defines
//*****************************************************************************
//! \brief Assign a "unique" number to each file, compiler error
//! on duplicates
//!
#define FASTRTS_FILENUM(number) \
    enum{FILE_NUM = number};    \
    void _nullFunction##number(void){}

//! \brief The assert() for the PMBus communications stack
//!
#define FASTRTS_ASSERT(expr) \
    if (expr)                \
    {}                       \
    else                     \
    FastRTS_assertionFailed(FILE_NUM, __LINE__)

//*****************************************************************************
// the function prototypes
//*****************************************************************************
//! \brief Handles failed assertions
//! \param[in] file File number where the assertion failed
//! \param[in] line Line number where the assertion failed
//!
static inline void FastRTS_assertionFailed(int16_t file, int16_t line)
{
#if defined(_DEBUG)
    printf("Error in file %d on line %d\n",file,line );
    abort();
#else
    printf("Error in file %d on line %d\n",file,line );
    // User must define some failure mechanism here instead (or in addition to)
    // of abort
    abort();
#endif //defined(_DEBUG)
}

#ifdef __cplusplus
}
#endif // extern "C"
//@}  // ingroup

#endif // end of _FASTRTS_ASSERT_H_ definition
