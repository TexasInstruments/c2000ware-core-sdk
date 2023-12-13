//#############################################################################
//! \file qsort_SP_RV.c
//!
//! \brief  Sorts an array of floats.
//! \author David M. Alter
//! \date   07/01/11
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



#include "fpu_vector.h"

//===========================================================================
// Function: void qsort_SP_RV(void *, uint16_t)
//===========================================================================
//
// Sorts an array of floats. This function is a partially 
// optmized version of qsort.c from the C28x cgtools lib qsort() v6.0.1.
//
// Dependencies:      none
// Useage:            qsort_SP_RV(x, N);
// Passed Parameters: void *x = input array of floats
//                    uint16_t N = size of a array
// Return value:      none
// Notes:
// 1) Performance is best with -o1, -mf3 compiler options (cgtools v6.0.1)
//
//---------------------------------------------------------------------------

inline static void swap_item(float *, float *);

//***************************************************************************
void qsort_SP_RV(void *base, const uint16_t nmemb)
{
    char   *basep  = base;              /* POINTER TO ARRAY OF ELEMENTS */
    uint16_t  i      = 0;                 /* left scan index  */
    uint16_t  j      = 2*(nmemb - 1);     /* right scan index */
    uint16_t pivot = nmemb & 0xFFFE;      /* Want closest even value */
    char   *pivp   = basep + pivot;
   
    if (nmemb <= 1) return;

    while( i < j )
    {
        while(*(float*)(basep + i) < *(float*)pivp) i=i+2;
        while(*(float*)(basep + j) > *(float*)pivp) j=j-2;

        if( i < j )
        {
            swap_item((float*)(basep + i), (float*)(basep + j));
            if ( pivot == i ) { pivot = j; pivp = basep + pivot; }
            else if( pivot == j ) { pivot = i; pivp = basep + pivot; }
            i=i+2; j=j-2;
        }
        else if ( i == j ) { i=i+2; j=j-2;  break; }
    }

    if(j > 0) qsort_SP_RV(basep, (j>>1) + 1);
    if((i>>1) < nmemb-1) qsort_SP_RV(basep + i, nmemb - (i>>1));

} // end of qsort_SP_RV()


//***************************************************************************
inline static void swap_item(float *src, float *dest)
{
    float temp;

    temp = *src;
    *src  = *dest;
    *dest = temp;

} // end of swap_item()

// End of file
