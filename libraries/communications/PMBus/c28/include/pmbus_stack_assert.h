//###########################################################################
//
// FILE:   pmbus_stack_assert.h
//
// TITLE:  Defines the PMBUS_STACK_ASSERT function macro
//
// Work in this file is based on the article:
// http://www.embedded.com/electronics-blogs/other/4023329/Assert-Yourself
//
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

#ifndef PMBUS_STACK_ASSERT_H
#define PMBUS_STACK_ASSERT_H

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
//!
//! \defgroup PMBUS_STACK_ASSERT Code Development with Assertion
//
//!
//! \ingroup PMBUS_STACK_ASSERT
// @{
//
//*****************************************************************************

//
// Includes
//
#include <stdint.h>
#include <stdbool.h>

//
// Defines
//

//! Assign a "unique" number to each file, compiler error
//! on duplicates
#define PMBUS_STACK_FILENUM(number)   \
    enum{FILE_NUM = number};    \
    void _nullFunction##number(void){}

//! The assert() for the PMBus communications stack
#define PMBUS_STACK_ASSERT(expr) \
    if (expr)              \
    {}                     \
    else                   \
    PMBusStack_assertionFailed(FILE_NUM, __LINE__)

//*****************************************************************************
//
//! Error Handler Function Pointer
//!
//! In the \e Release Mode, the user must define an error handler, and assign
//! it to this function pointer which gets called when PMBUS_STACK_ASSERT
//! fails in the state machine.
//!
//! \note If the library was built in debug mode, i.e. the macro \b _DEBUG
//! defined then it is unnecessary for the user to define this function in
//! their project. It is only required when using the release version of the
//! library; failure to define this will result in a linker error
//!
//! \return none
//
//*****************************************************************************
extern void (*PMBusStack_errorHandler)(void);

//*****************************************************************************
//
//! Handles failed assertions
//!
//! \param file is the file number where the assertion failed
//! \param line is the line number where the assertion failed
//!
//! This function handles any failed assertions within the stack library.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PMBusStack_assertionFailed(int16_t file, int16_t line)
{
#if defined(_DEBUG)
    __asm("    ESTOP0");
#else
    PMBusStack_errorHandler();
#endif //defined(_DEBUG)
}

//*****************************************************************************
//
// Close the Doxygen group.
// @}
//
//*****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif // extern "C"

#endif  // PMBUS_STACK_ASSERT_H
