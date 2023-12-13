//#############################################################################
//! \file   reference/C/source/$FILENAME$
//! \brief  Mean of Real and Imaginary Parts of a Complex Vector
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
DSP_FILENUM(10)

#define ELEM_SWAP(a,b) { fsize_t t=(a);                      \
                         (a)=(b);                            \
                         (b)=t;}

static fsize_t _median_find_average_RV(fsize_t *x, fsize_t median_low, 
                                       uint16_t n);

//*****************************************************************************
// VECTOR_medianRV
// Median of a real array of fsize_ts.  Input array is NOT 
// preserved. This routine uses a Quickselect method based on the algorithm 
// described in "Numerical recipes in C", Second Edition, Cambridge University 
// Press, 1992, Section 8.5, ISBN 0-521-43108-5
// Notes:
// 1) This function is destructive to the input array x in that it will be
//    sorted during function execution.  If this is not allowable, use
//    median_noreorder_CV().
// 2) For even length arrays, the median does not exist as a value in the 
//    array. The function returns the average of the 'median_low' and 
//    'median_high'. To do this, the sub-function _median_find_average_RV() 
//    is called.
//*****************************************************************************
fsize_t VECTOR_medianRV(fsize_t *x, const uint16_t n)
{
    fsize_t* p;
    uint16_t low, high;
    uint16_t median;
    uint16_t middle, ll, hh;

    //--- Initialization
    low = 0;
    high = n-1;
    median = (low + high)/2;

    //--- Main loop
    for(;;)
    {

        if (high <= low)                            // One element only
        {
            if(n%2 == 0)                            // Array length is even
            {
                return(_median_find_average_RV(x, x[median], n));
            }
            else                                    // Array length is odd
            {
                return x[median];
            }
        }
        if (high == low + 1)                        // Two elements only
        {
            if (x[low] > x[high]) ELEM_SWAP(x[low], x[high]) ;
            {
                if(n%2 == 0)                        // Array length is even
                {
                    return(_median_find_average_RV(x, x[median], n));
                }
                else                                // Array length is odd
                {
                    return x[median];
                }
            }
        }
        //--- Find median of low, middle and high items; swap into position low
        middle = (low + high) / 2;
        if (x[middle] > x[high])    ELEM_SWAP(x[middle], x[high]) ;
        if (x[low] > x[high])        ELEM_SWAP(x[low], x[high]) ;
        if (x[middle] > x[low])        ELEM_SWAP(x[middle], x[low]) ;
        //--- Swap low item (now in position middle) into position (low+1)
        ELEM_SWAP(x[middle], x[low+1]) ;

        //--- Nibble from each end towards middle, swapping items when stuck
        ll = low + 1;
        hh = high;
        for(;;)
        {
            p = &x[ll]; *p++;                            // Setup the pointer
            do ll++; while (x[low] > *p++) ;
            p = &x[hh]; *p--;                            // Setup the pointer
            do hh--; while (*p-- > x[low]) ;

            if (hh < ll) break;
            ELEM_SWAP(x[ll], x[hh]) ;
        }

        //--- Swap middle item (in position low) back into correct position
        ELEM_SWAP(x[low], x[hh]) ;

        //--- Re-set active partition
        if (hh <= median) low = ll;
        if (hh >= median) high = hh - 1;

    } // end of for(;;)

}


//*******************************************************************
// _median_find_average_RV() - supplemental function for median_RV().
//   Finds the average of the median_low and median_high values given
//   the median_low value in an array.  This is used for even length arrays.
//   In an even array, the median does not exist in the array, but instead
//   is here defined as the average of the two middle elements.  Median_low
//   is defined here as the lower such middle value, and median_high as the
//   upper middle value.
// Device: C28x
// External Dependencies: none
// Function Prototype: fsize_t _median_find_average_RV(fsize_t *, fsize_t, 
//                                                      uint16_t);
// Usage: z = _median_find_average_RV(x, median_low, n)
// Passed Parameters: fsize_t *x = pointer to input array
//                    fsize_t median_low = lower median value for array x[]
//                    uint16_t n = length of x array
// Return value: fsize_t z = result
// Author: David M. Alter   Texas Instruments, Inc.
// History:
//   August 28, 2012 - original
//
// Notes:
// 1) n is known to be even, since this function is only called for even N.
//    The loop can therefore be unrolled once without placing any further
//    restrictions on n.
// 2) The function needs to compute median_ave = (median_low + median_high)/2.
//    The task at hand is therefore to find median_high, given median_low.
//    In general, this can be done by searching sequentially through the array
//    to find the closest higher value to median_low.  However, the possibility
//    the median_low is repeated in the array complicates the task.  There
//    are several cases:
//
//    case a) median_low does NOT repeat in the array.  An example of this is:
//            {1, 2, 3, 4, 5, 6}, median_low=3, median_high=4, median=3.5
//    case b) median_low repeats in the array, but is a distinct value
//            from median high.  An example of this is:
//            {1, 3, 3, 4, 5, 6}, median_low=3, median_high=4, median=3.5
//    case c) median_low repeats in the array and is the same value as
//            median high.  An example of this is:
//            {1, 2, 3, 3, 5, 6}, median_low=3, median_high=3, median=3
//
//    The three cases can be identified by counting the number of values in
//    the array that are strictly greater than median_low.  If this number
//    equals n/2, then the array is either case (a) or (b).  If this number is
//    less than n/2, then the array is case (c).  This number being greater 
//    than n/2 is not a possibility.  At most, n/2 values can exist that are 
//    greater than median_low.
//
//    Once the case (a), (b), or (c) is identified, median_high can be found
//    as follows.  For cases (a) and (b), find the closest value to median_low
//    that is strictly greater than median_low.  For case (c), median_high
//    is equal to median_low.
//*******************************************************************
fsize_t _median_find_average_RV(fsize_t *x, fsize_t median_low, uint16_t n)
{
    fsize_t delta;         // Distance from median_low to current value
    fsize_t median_delta;  // Distance from median_low to median_high
    fsize_t median_high;   // Upper median value
    uint16_t higher_count; // Number of values strictly greater than median_low
    uint16_t i;            // General purpose
    
    //--- Assign initial values
    median_high = FLT_MAX;                   // Largest fsize_t value. 
                                             // Defined in math.h.
    median_delta = median_high - median_low; // Compute initial value
    higher_count = 0;                        // Initialize to zero

    //--- Sequence through the array.  Find how many values are strictly 
    //    greater than median_low.
    //--- Also find the closest strictly higher value to median_low.
    //--- Unroll the loop once.
    for(i=0; i<n/2; i++)
    {
        //--- Unrolled loop iteration #1
        if(*x > median_low)
        {
            higher_count++;             // Increment the counter
            delta = *x - median_low;    // Compute delta
            if(delta < median_delta)    // Current value is closer to 
                                        // median_low than current median_high
            {
                median_high = *x;       // New median_high is current array 
                                        // value
                median_delta = delta;   // New median_high_low_delta is current 
                                        // delta
            }
        }
        x++;                            // Increment the pointer

        //--- Unrolled loop iteration #2
        if(*x > median_low)
        {
            higher_count++;             // Increment the counter
            delta = *x - median_low;    // Compute delta
            if(delta < median_delta)    // Current value is closer to 
                                        // median_low than current median_high
            {
                median_high = *x;       // New median_high is current array 
                                        // value
                median_delta = delta;   // New median_high_low_delta is current 
                                        // delta
            }
        }
        x++;                            // Increment the pointer

    } // end for()

    //--- Now determine if array is case (a), (b), or (c)
    if(higher_count < n/2)    // It is case (c)
    {
        return(median_low);   // median_high=median_low, so median_ave also 
                              // equals median_low
    }
    else                      // It is case (a) or (b)
    {
        return( (median_low + median_high)/2 );
    }

} // end of median_find_median_ave_RV()

// End of File
