//#############################################################################
//! \file   reference/C/source/$FILENAME$
//! \brief  Sorts a real array
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
DSP_FILENUM(18)

//*****************************************************************************
// prototypes
//*****************************************************************************
static inline void swap_item(fsize_t *, fsize_t *);

//*****************************************************************************
// VECTOR_qsortRV
//*****************************************************************************
void VECTOR_qsortRV(void *base, const uint16_t nmemb)
{
    char   *basep  = base;              // POINTER TO ARRAY OF ELEMENTS 
    uint16_t  i    = 0;                 // left scan index
    // right scan index
    uint16_t  j    = sizeof(fsize_t)*(nmemb - 1);
    // Want closest even value
    uint16_t pivot = (nmemb & 0xFFFE)*(sizeof(fsize_t) / 2);    
    char   *pivp   = basep + pivot ;
   
    if (nmemb <= 1) return;

    while( i < j )
    {
        while(*(fsize_t*)(basep + i) < *(fsize_t*)pivp) 
        {
            i=i+sizeof(fsize_t);
        }
        while(*(fsize_t*)(basep + j) > *(fsize_t*)pivp)
        {
            j=j-sizeof(fsize_t);
        }

        if( i < j )
        {
            swap_item((fsize_t*)(basep + i), (fsize_t*)(basep + j));
            if ( pivot == i ) 
            {
                pivot = j; 
                pivp = basep + pivot; 
            }
            else if( pivot == j ) 
            {
                pivot = i; 
                pivp = basep + pivot; 
            }
            i=i+sizeof(fsize_t); 
            j=j-sizeof(fsize_t);
        }
        else if ( i == j ) 
        {
            i=i+sizeof(fsize_t); 
            j=j-sizeof(fsize_t);  
            break; 
        }
    }

    if(j > 0) 
    {
        VECTOR_qsortRV(basep, (j/sizeof(fsize_t) + 1U)); 
    }
    if((i/sizeof(fsize_t)) < (nmemb - 1))
    {
        VECTOR_qsortRV(basep + i, nmemb - (i/sizeof(fsize_t)));
    }

}

//*****************************************************************************
// swap_item
//*****************************************************************************
static inline void swap_item(fsize_t *src, fsize_t *dest)
{
    fsize_t temp;

    temp = *src;
    *src  = *dest;
    *dest = temp;

}

// End of File
