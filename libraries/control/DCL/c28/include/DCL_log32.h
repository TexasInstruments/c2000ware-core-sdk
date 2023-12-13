/* DCL_log32.h - 32-bit fixed-point data buffer utility
 *
 */
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

#ifndef _C_DCL_LOG32_H
#define _C_DCL_LOG32_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//! \file           DCL_log32.h
//!
//! \brief          Defines the 32-bit fixed-point data buffer structure
//!
//! \details        The LOG32 structure contains three pointers which define the
//!                 start and end of a memory block, and index into it.
//!                 Manipulation of the indexing pointer permits linear and
//!                 circular buffers, stacks, data logs, etc. to be implemented
//!                 with a common data structure.  An example of initialisation
//!                 and use is shown below:
//!
//! \code
//! #pragma DATA_SECTION(r_Array, "DataLogSection")
//! int32_t r_Array[FDLOG_DEFAULT_SIZE];
//! LOG32 rBuf = LOG32_DEFAULTS;
//! int32_t x, y = 0x12345678;
//!
//! DCL_createLOG32(&rBuf, r_Array, LOG32_DEFAULT_SIZE);
//! DCL_clearLOG32(&rBuf);
//!
//! DCL_writeLOG32(&rBuf, y);
//! x = readLOG32(&rBuf);
//! \endcode
//!
typedef volatile struct dcl_log32 {
    int32_t *fptr;  //!< Pointer to first buffer element
    int32_t *lptr;  //!< Pointer to last buffer element
    int32_t *dptr;  //!< Data index pointer
} LOG32;


//! \brief          Function name compatibility with DCL version 1
//!
#define DCL_createLog32 DCL_initLog32

//! \brief          Defines a default size for the FDLOG buffer
//!
#define LOG32_DEFAULT_SIZE  0x0400

//! \brief          Defines default values to initialise the FDLOG structure
//!
#define LOG32_DEFAULTS {    0x00000000, \
                            0x00000000, \
                            0x00000000  \
                        }


/******************** macro definitions ********************/

//! \brief          Distance from indexed element to end of buffer
//!
#define LOG32_SPACE(buf)        ((buf)->lptr - (buf)->dptr + 1)

//! \brief          Total buffer size in 32-bit words
//!
#define LOG32_SIZE(buf)         ((buf)->lptr - (buf)->fptr + 1)

//! \brief          Current indexed element
//!
#define LOG32_ELEMENT(buf)      ((buf)->dptr - (buf)->fptr + 1)

//! \brief          Index pointer is at start of buffer
//!
#define LOG32_START(buf)        ((buf)->dptr == (buf)->fptr)

//! \brief          Index pointer is at end of buffer
//!
#define LOG32_END(buf)          ((buf)->dptr == (buf)->lptr)

//! \brief          Indexed pointer not in buffer range
//!
#define LOG32_OUT_OF_RANGE(buf) (((buf)->dptr < (buf)->fptr) || ((buf)->dptr > (buf)->lptr))

//! \brief          Check if the buffer has a non-zero size
//!
#define LOG32_EXISTS(buf)       ((buf)->lptr != (buf)->fptr)


/******************** inline functions ********************/

//! \brief          Resets all structure pointers to null value
//! \param[in] p    The LOG32 structure
//!
static inline void DCL_deleteLog32(LOG32 *p) { p->dptr = p->lptr = p->fptr = 0; }

//! \brief          Resets the data index pointer to start of buffer
//! \param[in] p    The LOG32 structure
//!
static inline void DCL_resetLog32(LOG32 *p) { p->dptr = p->fptr; }

//! \brief          Assigns the buffer pointers to a memory block or array and sets
//!                 the data index pointer to the first address
//! \param[in] p    The LOG32 structure
//! \param[in] addr The start address of the memory block
//! \param[in] size The length of the memory block in 32-bit words
//!
static inline void DCL_initLog32(LOG32 *p, int32_t *addr, uint16_t size)
{
    p->fptr = addr;
    p->lptr = addr + size - 1;
    p->dptr = p->fptr;
}

//! \brief          Writes a data point into the buffer and advances the indexing
//!                 pointer, wrapping if necessary.
//!                 Returns the over-written data value for delay line or FIFO
//!                 implementation.
//! \param[in] p    The LOG32 structure
//! \param[in] data The input data value
//! \return         The over-written data value
//!
static inline int32_t DCL_writeLog32(LOG32 *p, int32_t data)
{
    int32_t rv = *(p->dptr);        // save existing data

    // write new data to log
    *(p->dptr++) = data;

    // check for end of buffer & wrap if necessary
    if (p->dptr > p->lptr)
    {
        p->dptr = p->fptr;
    }

    return(rv);
}

//! \brief          Fills the buffer with a given data value and resets the data
//!                 index pointer to the start of the buffer
//! \param[in] p    The LOG32 structure
//! \param[in] data The fill data value
//!
static inline void DCL_fillLog32(LOG32 *p, int32_t data)
{
    p->dptr = p->lptr;
    *(p->dptr) = data;
    while (p->dptr > p->fptr)
    {
        *(--p->dptr) = data;
    }
}

//! \brief          Clears the buffer contents by writing 0 to all elements and
//!                 resets the data index pointer to the start of the buffer.
//!
#define DCL_clearLog32(bufAddr)     DCL_fillLog32(bufAddr, 0L)


//! \brief          Reads a data point from the buffer and then advances the
//!                 indexing pointer, wrapping if necessary
//! \param[in] p    The LOG32 structure
//! \return         The indexed data value
//!
static inline int32_t DCL_readLog32(LOG32 *p)
{
    int32_t rv = *(p->dptr++);

    if (p->dptr > p->lptr)
    {
        p->dptr = p->fptr;
    }

    return(rv);
}

//! \brief          Copies the contents of one log (q) into another (p) and resets
//!                 both buffer index pointers.  The function assumes both logs
//!                 have the same length.
//! \param[in] p    The destination LOG32 structure
//! \param[in] q    The source LOG32 structure
//!
static inline void DCL_copyLog32(LOG32 *p, LOG32 *q)
{
    p->dptr = p->lptr;
    q->dptr = q->lptr;
    *(p->dptr) = *(q->dptr);
    while (p->dptr > p->fptr)
    {
        *(--p->dptr) = *(--q->dptr);
    }
}

//----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif // extern "C"

#endif // _C_DCL_LOG32_H

/* end of file */
