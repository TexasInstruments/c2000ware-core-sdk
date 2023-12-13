/* DCL_MLOG32.h - Multi-channel data logger (32-bit fixed point version)
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

#ifndef _C_DCL_MLOG32_H
#define _C_DCL_MLOG32_H

#ifdef __cplusplus
extern "C" {
#endif

//! \file           DCL_MLOG32.h
//! \brief          Contains the public interface to the multi-channel data log module (MLOG32)
//!

#include <stdint.h>
#include "DCL_log32.h"

//! \brief          Defines the number of MLOG32 channels
//!
#define MLOG32_CHANS   4

//! \brief          Defines the MLOG32 structure
//!
typedef volatile struct dcl_mlog32 {
    LOG32 captFrame[MLOG32_CHANS];  //!< Capture data frames
    int32_t *data[MLOG32_CHANS];    //!< Data channel pointers
    int32_t trigMax;                //!< Upper trigger threshold
    int32_t trigMin;                //!< Lower trigger threshold
    uint16_t tScale;                //!< Number of samples per log write
    uint16_t sCount;                //!< Sample counter
    uint16_t mode;                  //!< Operating mode
} MLOG32;

//! \brief          Defines default values to initialise the MLOG32 structure
//!                 Note: modify to match number of channels defined above
//!
#define MLOG32_DEFAULTS { { LOG32_DEFAULTS, LOG32_DEFAULTS, LOG32_DEFAULTS, LOG32_DEFAULTS }, \
                          { 0x00000000, 0x00000000, 0x00000000, 0x00000000 }, \
                            0.1, -0.1, 1, 1, 0 }

//! \brief          Enumerated MLOG32 operating modes
//!
typedef enum
{
    MLOG32_invalid = 0,     //!< Buffer pointers not initialised
    MLOG32_idle,            //!< Memory initialised but module not armed
    MLOG32_armed,           //!< Armed: capturing monitor frame data and waiting for trigger
    MLOG32_capture,         //!< Triggered: logging data into capture frame
    MLOG32_complete,        //!< Full data frame captured and available for read-out
    MLOG32_numStates        //!< Number of MLOG states
} MLOG32_states;


//! \brief          Initializes the MLOG32 module
//! \param[in] q    The MLOG32 structure
//! \param[in] addr The start address of the memory block
//! \param[in] size The size of the memory block in 32-bit words
//! \param[in] tmin The upper trigger threshold
//! \param[in] tmax The lower trigger threshold
//!
static inline void DCL_initMLOG32(MLOG32 *q, int32_t *addr, uint16_t size, int32_t tmax, int32_t tmin, uint16_t div)
{
    int i;

    for (i=0; i<MLOG32_CHANS; i++)
    {
        // assign and clear capture frame, and initialize index to end of lead frame
        DCL_initLog32(&(q->captFrame[i]), (addr + i*size), size);
        DCL_clearLog32(&(q->captFrame[i]));
    }

    q->trigMax = tmax;
    q->trigMin = tmin;
    q->tScale = div;
    q->sCount = div;
    q->mode = MLOG32_idle;
}


//! \brief          Resets the MLOG32 module: clears all frame buffers and sets idle mode
//! \param[in] q    The MLOG32 structure
//! \return         The operating mode
//!
static inline void DCL_resetMLOG32(MLOG32 *q)
{
    int i;

    for (i=0; i<MLOG32_CHANS; i++)
    {
        DCL_clearLog32(&(q->captFrame[i]));
    }

    q->mode = MLOG32_idle;
}


//! \brief          Changes the MLOG32 mode to "MLOG32_armed".  Only valid if current operating mode is "MLOG32_idle"
//! \param[in] q    The MLOG32 structure
//! \return         The operating mode
//!
static inline uint16_t DCL_armMLOG32(MLOG32 *q)
{
    q->mode = (q->mode == MLOG32_idle) ? MLOG32_armed : MLOG32_idle;
    return(q->mode);
}


//! \brief          Runs the MLOG32 module
//! \param[in] q    The MLOG32 structure
//! \return         The operating mode
//!
static inline uint16_t DCL_runMLOG32(MLOG32 *q)
{
    int i;

    // skip sample unless counter reaches zero
    if (--(q->sCount) == 0)
    {
        switch(q->mode)
        {
        // MLOG32 not initialised
        case MLOG32_invalid:
            break;

        // idle: do nothing
        case MLOG32_idle:
            break;

        // armed: ready to begin capturing when either trigger threshold is crossed
        case MLOG32_armed:
            // check for trigger condition
            if ((*(q->data[0]) > q->trigMax) || (*(q->data[0]) < q->trigMin))
            {
                for (i=0; i<MLOG32_CHANS; i++)
                {
                    DCL_writeLog32(&(q->captFrame[i]), *(q->data[i]));
                }
                q->mode = MLOG32_capture;
            }
            break;

        // capture mode: acquiring data
        case MLOG32_capture:
            // check for full capture frame
            if (q->captFrame[0].dptr == q->captFrame[0].fptr)
            {
                q->mode = MLOG32_complete;
            }
            else
            {
                // log data channels
                for (i=0; i<MLOG32_CHANS; i++)
                {
                    DCL_writeLog32(&(q->captFrame[i]), *(q->data[i]));
                }
            }
            break;

        // complete: do nothing - results available in capture buffer
        case MLOG32_complete:
            break;

        default:
            ;
        }

        q->sCount = q->tScale;
    }

    return(q->mode);
}

//----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif // extern "C"

#endif // _C_DCL_MLOG32_H

/* end of file */
