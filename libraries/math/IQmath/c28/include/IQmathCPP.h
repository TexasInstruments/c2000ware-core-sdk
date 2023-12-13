//###########################################################################
//
// FILE:    IQmathCPP.h
//
// TITLE:   IQ Math C++ definitions.
//
//###########################################################################
//
// Ver  | dd-mmm-yyyy |  Who  | Description of changes
// =====|=============|=======|==============================================
//  1.3 | 19 Nov 2001 | A. T. | Original Release.
// -----|-------------|-------|----------------------------------------------
//  1.4 | 17 May 2002 | A. T. | Added new functions and support for
//      |             |       | intrinsics IQmpy, IQxmpy, IQsat.
//      |             |       | Added support for boolean and bit-wise
//      |             |       | operations.
//      |             |       | Expanded Q support range: 15 <= Q <= 30
// -----|-------------|-------|----------------------------------------------
//  1.4d| 30 Mar 2003 | DA/SD | Added macro definition to include header
//      |             |       | file multiple times in the program.
//------|-------------|-------|----------------------------------------------
//  1.4e| 17 Jun 2004 | AT/DA | Added IQexp function.
//      |             |       | Added IQasin & IQacos functions (thanks DA).
// -----|-------------|-------|----------------------------------------------
//  1.4f| 10 Mar 2005 | AT    | Fixed Bug In IQexp function.
// -----|-------------|-------|----------------------------------------------
//  1.5 | 30 Jan 2008 | LH    | 1. Changed the definion of the _IQatan2PU(A,B)
//      |             |       |    macro for FLOAT_MATH so that a call to
//      |             |       |    divide will not occur.
//      |             |       | 2. If MATH_TYPE == FLOAT_MATH, then include the
//      |             |       |    following standard headers: cmath.h
//      |             |       |    cstdlib.h.
//      |             |       | 3. Adding missing definitions for absolute
//      |             |       |    value when MATH_TYPE == FLOAT_MATH
//      |             |       | 4. Added #include <stdlib.h>
//      |             |       | 5. Added macro definitions for IQtoa, IQNtoa
//      |             |       | 6. Changed iq types to const iq & so inline will work
// -----|-------------|-------|----------------------------------------------
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

#ifndef __IQMATHCPP_H_INCLUDED__
#define __IQMATHCPP_H_INCLUDED__

#include  <stdlib.h>

#if MATH_TYPE == FLOAT_MATH
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#endif

//###########################################################################
#if MATH_TYPE == IQ_MATH
//###########################################################################
// If IQ_MATH is used, the following IQmath library definitions are used:
//===========================================================================

struct iq {
    //constructors:
    iq () : val(0) { }
    iq (long x) : val(x) { }

    //copy constructor:
    iq (const iq & x) : val(x.val) { }

    //assignment operators:
    inline iq & operator = (const iq & x);

    //arithmetic operators:
    inline iq & operator += (const iq &x);
    inline iq & operator -= (const iq &x);
    inline iq & operator *= (const iq &x);
    inline iq & operator /= (const iq &x);

    //bitwise operators:
    inline iq & operator &= (const long &x);
    inline iq & operator |= (const long &x);
    inline iq & operator ^= (const long &x);

    long val;
};

struct iq30 {
    //constructors:
    iq30 () : val(0) { }
    iq30 (long x) : val(x) { }

    //copy constructor:
    iq30 (const iq30 & x) : val(x.val) { }

    //assignment operators:
    inline iq30 & operator = (const iq30 & x);

    //arithmetic operators:
    inline iq30 & operator += (const iq30 &x);
    inline iq30 & operator -= (const iq30 &x);
    inline iq30 & operator *= (const iq30 &x);
    inline iq30 & operator /= (const iq30 &x);

    //bitwise operators:
    inline iq30 & operator &= (const long &x);
    inline iq30 & operator |= (const long &x);
    inline iq30 & operator ^= (const long &x);

    long val;
};

struct iq29 {
    //constructors:
    iq29 () : val(0) { }
    iq29 (long x) : val(x) { }

    //copy constructor:
    iq29 (const iq29 & x) : val(x.val) { }

    //assignment operators:
    inline iq29 & operator = (const iq29 & x);

    //arithmetic operators:
    inline iq29 & operator += (const iq29 &x);
    inline iq29 & operator -= (const iq29 &x);
    inline iq29 & operator *= (const iq29 &x);
    inline iq29 & operator /= (const iq29 &x);

    //bitwise operators:
    inline iq29 & operator &= (const long &x);
    inline iq29 & operator |= (const long &x);
    inline iq29 & operator ^= (const long &x);

    long val;
};

struct iq28 {
    //constructors:
    iq28 () : val(0) { }
    iq28 (long x) : val(x) { }

    //copy constructor:
    iq28 (const iq28 & x) : val(x.val) { }

    //assignment operators:
    inline iq28 & operator = (const iq28 & x);

    //arithmetic operators:
    inline iq28 & operator += (const iq28 &x);
    inline iq28 & operator -= (const iq28 &x);
    inline iq28 & operator *= (const iq28 &x);
    inline iq28 & operator /= (const iq28 &x);

    //bitwise operators:
    inline iq28 & operator &= (const long &x);
    inline iq28 & operator |= (const long &x);
    inline iq28 & operator ^= (const long &x);

    long val;
};

struct iq27 {
    //constructors:
    iq27 () : val(0) { }
    iq27 (long x) : val(x) { }

    //copy constructor:
    iq27 (const iq27 & x) : val(x.val) { }

    //assignment operators:
    inline iq27 & operator = (const iq27 & x);

    //arithmetic operators:
    inline iq27 & operator += (const iq27 &x);
    inline iq27 & operator -= (const iq27 &x);
    inline iq27 & operator *= (const iq27 &x);
    inline iq27 & operator /= (const iq27 &x);

    //bitwise operators:
    inline iq27 & operator &= (const long &x);
    inline iq27 & operator |= (const long &x);
    inline iq27 & operator ^= (const long &x);

    long val;
};

struct iq26 {
    //constructors:
    iq26 () : val(0) { }
    iq26 (long x) : val(x) { }

    //copy constructor:
    iq26 (const iq26 & x) : val(x.val) { }

    //assignment operators:
    inline iq26 & operator = (const iq26 & x);

    //arithmetic operators:
    inline iq26 & operator += (const iq26 &x);
    inline iq26 & operator -= (const iq26 &x);
    inline iq26 & operator *= (const iq26 &x);
    inline iq26 & operator /= (const iq26 &x);

    //bitwise operators:
    inline iq26 & operator &= (const long &x);
    inline iq26 & operator |= (const long &x);
    inline iq26 & operator ^= (const long &x);

    long val;
};

struct iq25 {
    //constructors:
    iq25 () : val(0) { }
    iq25 (long x) : val(x) { }

    //copy constructor:
    iq25 (const iq25 & x) : val(x.val) { }

    //assignment operators:
    inline iq25 & operator = (const iq25 & x);

    //arithmetic operators:
    inline iq25 & operator += (const iq25 &x);
    inline iq25 & operator -= (const iq25 &x);
    inline iq25 & operator *= (const iq25 &x);
    inline iq25 & operator /= (const iq25 &x);

    //bitwise operators:
    inline iq25 & operator &= (const long &x);
    inline iq25 & operator |= (const long &x);
    inline iq25 & operator ^= (const long &x);

    long val;
};


struct iq24 {
    //constructors:
    iq24 () : val(0) { }
    iq24 (long x) : val(x) { }

    //copy constructor:
    iq24 (const iq24 & x) : val(x.val) { }

    //assignment operators:
    inline iq24 & operator = (const iq24 & x);

    //arithmetic operators:
    inline iq24 & operator += (const iq24 &x);
    inline iq24 & operator -= (const iq24 &x);
    inline iq24 & operator *= (const iq24 &x);
    inline iq24 & operator /= (const iq24 &x);

    //bitwise operators:
    inline iq24 & operator &= (const long &x);
    inline iq24 & operator |= (const long &x);
    inline iq24 & operator ^= (const long &x);

    long val;
};

struct iq23 {
    //constructors:
    iq23 () : val(0) { }
    iq23 (long x) : val(x) { }

    //copy constructor:
    iq23 (const iq23 & x) : val(x.val) { }

    //assignment operators:
    inline iq23 & operator = (const iq23 & x);

    //arithmetic operators:
    inline iq23 & operator += (const iq23 &x);
    inline iq23 & operator -= (const iq23 &x);
    inline iq23 & operator *= (const iq23 &x);
    inline iq23 & operator /= (const iq23 &x);

    //bitwise operators:
    inline iq23 & operator &= (const long &x);
    inline iq23 & operator |= (const long &x);
    inline iq23 & operator ^= (const long &x);

    long val;
};

struct iq22 {
    //constructors:
    iq22 () : val(0) { }
    iq22 (long x) : val(x) { }

    //copy constructor:
    iq22 (const iq22 & x) : val(x.val) { }

    //assignment operators:
    inline iq22 & operator = (const iq22 & x);

    //arithmetic operators:
    inline iq22 & operator += (const iq22 &x);
    inline iq22 & operator -= (const iq22 &x);
    inline iq22 & operator *= (const iq22 &x);
    inline iq22 & operator /= (const iq22 &x);

    //bitwise operators:
    inline iq22 & operator &= (const long &x);
    inline iq22 & operator |= (const long &x);
    inline iq22 & operator ^= (const long &x);

    long val;
};

struct iq21 {
    //constructors:
    iq21 () : val(0) { }
    iq21 (long x) : val(x) { }

    //copy constructor:
    iq21 (const iq21 & x) : val(x.val) { }

    //assignment operators:
    inline iq21 & operator = (const iq21 & x);

    //arithmetic operators:
    inline iq21 & operator += (const iq21 &x);
    inline iq21 & operator -= (const iq21 &x);
    inline iq21 & operator *= (const iq21 &x);
    inline iq21 & operator /= (const iq21 &x);

    //bitwise operators:
    inline iq21 & operator &= (const long &x);
    inline iq21 & operator |= (const long &x);
    inline iq21 & operator ^= (const long &x);

    long val;
};

struct iq20 {
    //constructors:
    iq20 () : val(0) { }
    iq20 (long x) : val(x) { }

    //copy constructor:
    iq20 (const iq20 & x) : val(x.val) { }

    //assignment operators:
    inline iq20 & operator = (const iq20 & x);

    //arithmetic operators:
    inline iq20 & operator += (const iq20 &x);
    inline iq20 & operator -= (const iq20 &x);
    inline iq20 & operator *= (const iq20 &x);
    inline iq20 & operator /= (const iq20 &x);

    //bitwise operators:
    inline iq20 & operator &= (const long &x);
    inline iq20 & operator |= (const long &x);
    inline iq20 & operator ^= (const long &x);

    long val;
};

struct iq19 {
    //constructors:
    iq19 () : val(0) { }
    iq19 (long x) : val(x) { }

    //copy constructor:
    iq19 (const iq19 & x) : val(x.val) { }

    //assignment operators:
    inline iq19 & operator = (const iq19 & x);

    //arithmetic operators:
    inline iq19 & operator += (const iq19 &x);
    inline iq19 & operator -= (const iq19 &x);
    inline iq19 & operator *= (const iq19 &x);
    inline iq19 & operator /= (const iq19 &x);

    //bitwise operators:
    inline iq19 & operator &= (const long &x);
    inline iq19 & operator |= (const long &x);
    inline iq19 & operator ^= (const long &x);

    long val;
};

struct iq18 {
    //constructors:
    iq18 () : val(0) { }
    iq18 (long x) : val(x) { }

    //copy constructor:
    iq18 (const iq18 & x) : val(x.val) { }

    //assignment operators:
    inline iq18 & operator = (const iq18 & x);

    //arithmetic operators:
    inline iq18 & operator += (const iq18 &x);
    inline iq18 & operator -= (const iq18 &x);
    inline iq18 & operator *= (const iq18 &x);
    inline iq18 & operator /= (const iq18 &x);

    //bitwise operators:
    inline iq18 & operator &= (const long &x);
    inline iq18 & operator |= (const long &x);
    inline iq18 & operator ^= (const long &x);

    long val;
};

struct iq17 {
    //constructors:
    iq17 () : val(0) { }
    iq17 (long x) : val(x) { }

    //copy constructor:
    iq17 (const iq17 & x) : val(x.val) { }

    //assignment operators:
    inline iq17 & operator = (const iq17 & x);

    //arithmetic operators:
    inline iq17 & operator += (const iq17 &x);
    inline iq17 & operator -= (const iq17 &x);
    inline iq17 & operator *= (const iq17 &x);
    inline iq17 & operator /= (const iq17 &x);

    //bitwise operators:
    inline iq17 & operator &= (const long &x);
    inline iq17 & operator |= (const long &x);
    inline iq17 & operator ^= (const long &x);

    long val;
};

struct iq16 {
    //constructors:
    iq16 () : val(0) { }
    iq16 (long x) : val(x) { }

    //copy constructor:
    iq16 (const iq16 & x) : val(x.val) { }

    //assignment operators:
    inline iq16 & operator = (const iq16 & x);

    //arithmetic operators:
    inline iq16 & operator += (const iq16 &x);
    inline iq16 & operator -= (const iq16 &x);
    inline iq16 & operator *= (const iq16 &x);
    inline iq16 & operator /= (const iq16 &x);

    //bitwise operators:
    inline iq16 & operator &= (const long &x);
    inline iq16 & operator |= (const long &x);
    inline iq16 & operator ^= (const long &x);

    long val;
};

struct iq15 {
    //constructors:
    iq15 () : val(0) { }
    iq15 (long x) : val(x) { }

    //copy constructor:
    iq15 (const iq15 & x) : val(x.val) { }

    //assignment operators:
    inline iq15 & operator = (const iq15 & x);

    //arithmetic operators:
    inline iq15 & operator += (const iq15 &x);
    inline iq15 & operator -= (const iq15 &x);
    inline iq15 & operator *= (const iq15 &x);
    inline iq15 & operator /= (const iq15 &x);

    //bitwise operators:
    inline iq15 & operator &= (const long &x);
    inline iq15 & operator |= (const long &x);
    inline iq15 & operator ^= (const long &x);

    long val;
};

struct iq14 {
    //constructors:
    iq14 () : val(0) { }
    iq14 (long x) : val(x) { }

    //copy constructor:
    iq14 (const iq14 & x) : val(x.val) { }

    //assignment operators:
    inline iq14 & operator = (const iq14 & x);

    //arithmetic operators:
    inline iq14 & operator += (const iq14 &x);
    inline iq14 & operator -= (const iq14 &x);
    inline iq14 & operator *= (const iq14 &x);
    inline iq14 & operator /= (const iq14 &x);

    //bitwise operators:
    inline iq14 & operator &= (const long &x);
    inline iq14 & operator |= (const long &x);
    inline iq14 & operator ^= (const long &x);

    long val;
};

struct iq13 {
    //constructors:
    iq13 () : val(0) { }
    iq13 (long x) : val(x) { }

    //copy constructor:
    iq13 (const iq13 & x) : val(x.val) { }

    //assignment operators:
    inline iq13 & operator = (const iq13 & x);

    //arithmetic operators:
    inline iq13 & operator += (const iq13 &x);
    inline iq13 & operator -= (const iq13 &x);
    inline iq13 & operator *= (const iq13 &x);
    inline iq13 & operator /= (const iq13 &x);

    //bitwise operators:
    inline iq13 & operator &= (const long &x);
    inline iq13 & operator |= (const long &x);
    inline iq13 & operator ^= (const long &x);

    long val;
};

struct iq12 {
    //constructors:
    iq12 () : val(0) { }
    iq12 (long x) : val(x) { }

    //copy constructor:
    iq12 (const iq12 & x) : val(x.val) { }

    //assignment operators:
    inline iq12 & operator = (const iq12 & x);

    //arithmetic operators:
    inline iq12 & operator += (const iq12 &x);
    inline iq12 & operator -= (const iq12 &x);
    inline iq12 & operator *= (const iq12 &x);
    inline iq12 & operator /= (const iq12 &x);

    //bitwise operators:
    inline iq12 & operator &= (const long &x);
    inline iq12 & operator |= (const long &x);
    inline iq12 & operator ^= (const long &x);

    long val;
};

struct iq11 {
    //constructors:
    iq11 () : val(0) { }
    iq11 (long x) : val(x) { }

    //copy constructor:
    iq11 (const iq11 & x) : val(x.val) { }

    //assignment operators:
    inline iq11 & operator = (const iq11 & x);

    //arithmetic operators:
    inline iq11 & operator += (const iq11 &x);
    inline iq11 & operator -= (const iq11 &x);
    inline iq11 & operator *= (const iq11 &x);
    inline iq11 & operator /= (const iq11 &x);

    //bitwise operators:
    inline iq11 & operator &= (const long &x);
    inline iq11 & operator |= (const long &x);
    inline iq11 & operator ^= (const long &x);

    long val;
};

struct iq10 {
    //constructors:
    iq10 () : val(0) { }
    iq10 (long x) : val(x) { }

    //copy constructor:
    iq10 (const iq10 & x) : val(x.val) { }

    //assignment operators:
    inline iq10 & operator = (const iq10 & x);

    //arithmetic operators:
    inline iq10 & operator += (const iq10 &x);
    inline iq10 & operator -= (const iq10 &x);
    inline iq10 & operator *= (const iq10 &x);
    inline iq10 & operator /= (const iq10 &x);

    //bitwise operators:
    inline iq10 & operator &= (const long &x);
    inline iq10 & operator |= (const long &x);
    inline iq10 & operator ^= (const long &x);

    long val;
};

struct iq9 {
    //constructors:
    iq9 () : val(0) { }
    iq9 (long x) : val(x) { }

    //copy constructor:
    iq9 (const iq9 & x) : val(x.val) { }

    //assignment operators:
    inline iq9 & operator = (const iq9 & x);

    //arithmetic operators:
    inline iq9 & operator += (const iq9 &x);
    inline iq9 & operator -= (const iq9 &x);
    inline iq9 & operator *= (const iq9 &x);
    inline iq9 & operator /= (const iq9 &x);

    //bitwise operators:
    inline iq9 & operator &= (const long &x);
    inline iq9 & operator |= (const long &x);
    inline iq9 & operator ^= (const long &x);

    long val;
};

struct iq8 {
    //constructors:
    iq8 () : val(0) { }
    iq8 (long x) : val(x) { }

    //copy constructor:
    iq8 (const iq8 & x) : val(x.val) { }

    //assignment operators:
    inline iq8 & operator = (const iq8 & x);

    //arithmetic operators:
    inline iq8 & operator += (const iq8 &x);
    inline iq8 & operator -= (const iq8 &x);
    inline iq8 & operator *= (const iq8 &x);
    inline iq8 & operator /= (const iq8 &x);

    //bitwise operators:
    inline iq8 & operator &= (const long &x);
    inline iq8 & operator |= (const long &x);
    inline iq8 & operator ^= (const long &x);

    long val;
};

struct iq7 {
    //constructors:
    iq7 () : val(0) { }
    iq7 (long x) : val(x) { }

    //copy constructor:
    iq7 (const iq7 & x) : val(x.val) { }

    //assignment operators:
    inline iq7 & operator = (const iq7 & x);

    //arithmetic operators:
    inline iq7 & operator += (const iq7 &x);
    inline iq7 & operator -= (const iq7 &x);
    inline iq7 & operator *= (const iq7 &x);
    inline iq7 & operator /= (const iq7 &x);

    //bitwise operators:
    inline iq7 & operator &= (const long &x);
    inline iq7 & operator |= (const long &x);
    inline iq7 & operator ^= (const long &x);

    long val;
};

struct iq6 {
    //constructors:
    iq6 () : val(0) { }
    iq6 (long x) : val(x) { }

    //copy constructor:
    iq6 (const iq6 & x) : val(x.val) { }

    //assignment operators:
    inline iq6 & operator = (const iq6 & x);

    //arithmetic operators:
    inline iq6 & operator += (const iq6 &x);
    inline iq6 & operator -= (const iq6 &x);
    inline iq6 & operator *= (const iq6 &x);
    inline iq6 & operator /= (const iq6 &x);

    //bitwise operators:
    inline iq6 & operator &= (const long &x);
    inline iq6 & operator |= (const long &x);
    inline iq6 & operator ^= (const long &x);

    long val;
};


struct iq5 {
    //constructors:
    iq5 () : val(0) { }
    iq5 (long x) : val(x) { }

    //copy constructor:
    iq5 (const iq5 & x) : val(x.val) { }

    //assignment operators:
    inline iq5 & operator = (const iq5 & x);

    //arithmetic operators:
    inline iq5 & operator += (const iq5 &x);
    inline iq5 & operator -= (const iq5 &x);
    inline iq5 & operator *= (const iq5 &x);
    inline iq5 & operator /= (const iq5 &x);

    //bitwise operators:
    inline iq5 & operator &= (const long &x);
    inline iq5 & operator |= (const long &x);
    inline iq5 & operator ^= (const long &x);

    long val;
};

struct iq4 {
    //constructors:
    iq4 () : val(0) { }
    iq4 (long x) : val(x) { }

    //copy constructor:
    iq4 (const iq4 & x) : val(x.val) { }

    //assignment operators:
    inline iq4 & operator = (const iq4 & x);

    //arithmetic operators:
    inline iq4 & operator += (const iq4 &x);
    inline iq4 & operator -= (const iq4 &x);
    inline iq4 & operator *= (const iq4 &x);
    inline iq4 & operator /= (const iq4 &x);

    //bitwise operators:
    inline iq4 & operator &= (const long &x);
    inline iq4 & operator |= (const long &x);
    inline iq4 & operator ^= (const long &x);

    long val;
};

struct iq3 {
    //constructors:
    iq3 () : val(0) { }
    iq3 (long x) : val(x) { }

    //copy constructor:
    iq3 (const iq3 & x) : val(x.val) { }

    //assignment operators:
    inline iq3 & operator = (const iq3 & x);

    //arithmetic operators:
    inline iq3 & operator += (const iq3 &x);
    inline iq3 & operator -= (const iq3 &x);
    inline iq3 & operator *= (const iq3 &x);
    inline iq3 & operator /= (const iq3 &x);

    //bitwise operators:
    inline iq3 & operator &= (const long &x);
    inline iq3 & operator |= (const long &x);
    inline iq3 & operator ^= (const long &x);

    long val;
};

struct iq2 {
    //constructors:
    iq2 () : val(0) { }
    iq2 (long x) : val(x) { }

    //copy constructor:
    iq2 (const iq2 & x) : val(x.val) { }

    //assignment operators:
    inline iq2 & operator = (const iq2 & x);

    //arithmetic operators:
    inline iq2 & operator += (const iq2 &x);
    inline iq2 & operator -= (const iq2 &x);
    inline iq2 & operator *= (const iq2 &x);
    inline iq2 & operator /= (const iq2 &x);

    //bitwise operators:
    inline iq2 & operator &= (const long &x);
    inline iq2 & operator |= (const long &x);
    inline iq2 & operator ^= (const long &x);

    long val;
};


struct iq1 {
    //constructors:
    iq1 () : val(0) { }
    iq1 (long x) : val(x) { }

    //copy constructor:
    iq1 (const iq1 & x) : val(x.val) { }

    //assignment operators:
    inline iq1 & operator = (const iq1 & x);

    //arithmetic operators:
    inline iq1 & operator += (const iq1 &x);
    inline iq1 & operator -= (const iq1 &x);
    inline iq1 & operator *= (const iq1 &x);
    inline iq1 & operator /= (const iq1 &x);

    //bitwise operators:
    inline iq1 & operator &= (const long &x);
    inline iq1 & operator |= (const long &x);
    inline iq1 & operator ^= (const long &x);

    long val;
};

//---------------------------------------------------------------------------
// Functions: IQ(A), IQN(A)
//---------------------------------------------------------------------------

#define IQ(A)   (iq)   _IQ(A)
#define IQ30(A) (iq30) _IQ30(A)
#define IQ29(A) (iq29) _IQ29(A)
#define IQ28(A) (iq28) _IQ28(A)
#define IQ27(A) (iq27) _IQ27(A)
#define IQ26(A) (iq26) _IQ26(A)
#define IQ25(A) (iq25) _IQ25(A)
#define IQ24(A) (iq24) _IQ24(A)
#define IQ23(A) (iq23) _IQ23(A)
#define IQ22(A) (iq22) _IQ22(A)
#define IQ21(A) (iq21) _IQ21(A)
#define IQ20(A) (iq20) _IQ20(A)
#define IQ19(A) (iq19) _IQ19(A)
#define IQ18(A) (iq18) _IQ18(A)
#define IQ17(A) (iq17) _IQ17(A)
#define IQ16(A) (iq16) _IQ16(A)
#define IQ15(A) (iq15) _IQ15(A)
#define IQ14(A) (iq14) _IQ14(A)
#define IQ13(A) (iq13) _IQ13(A)
#define IQ12(A) (iq12) _IQ12(A)
#define IQ11(A) (iq11) _IQ11(A)
#define IQ10(A) (iq10) _IQ10(A)
#define IQ9(A)  (iq9)  _IQ9(A)
#define IQ8(A)  (iq8)  _IQ8(A)
#define IQ7(A)  (iq7)  _IQ7(A)
#define IQ6(A)  (iq6)  _IQ6(A)
#define IQ5(A)  (iq5)  _IQ5(A)
#define IQ4(A)  (iq4)  _IQ4(A)
#define IQ3(A)  (iq3)  _IQ3(A)
#define IQ2(A)  (iq2)  _IQ2(A)
#define IQ1(A)  (iq1)  _IQ1(A)

//---------------------------------------------------------------------------
// Functions: IQtoF(A), IQNtoF(A)
//---------------------------------------------------------------------------

inline  float   IQtoF(const iq & x)     { return _IQtoF(x.val);   }
inline  float   IQ30toF(const iq30 & x) { return _IQ30toF(x.val); }
inline  float   IQ29toF(const iq29 & x) { return _IQ29toF(x.val); }
inline  float   IQ28toF(const iq28 & x) { return _IQ28toF(x.val); }
inline  float   IQ27toF(const iq27 & x) { return _IQ27toF(x.val); }
inline  float   IQ26toF(const iq26 & x) { return _IQ26toF(x.val); }
inline  float   IQ25toF(const iq25 & x) { return _IQ25toF(x.val); }
inline  float   IQ24toF(const iq24 & x) { return _IQ24toF(x.val); }
inline  float   IQ23toF(const iq23 & x) { return _IQ23toF(x.val); }
inline  float   IQ22toF(const iq22 & x) { return _IQ22toF(x.val); }
inline  float   IQ21toF(const iq21 & x) { return _IQ21toF(x.val); }
inline  float   IQ20toF(const iq20 & x) { return _IQ20toF(x.val); }
inline  float   IQ19toF(const iq19 & x) { return _IQ19toF(x.val); }
inline  float   IQ18toF(const iq18 & x) { return _IQ18toF(x.val); }
inline  float   IQ17toF(const iq17 & x) { return _IQ17toF(x.val); }
inline  float   IQ16toF(const iq16 & x) { return _IQ16toF(x.val); }
inline  float   IQ15toF(const iq15 & x) { return _IQ15toF(x.val); }
inline  float   IQ14toF(const iq14 & x) { return _IQ14toF(x.val); }
inline  float   IQ13toF(const iq13 & x) { return _IQ13toF(x.val); }
inline  float   IQ12toF(const iq12 & x) { return _IQ12toF(x.val); }
inline  float   IQ11toF(const iq11 & x) { return _IQ11toF(x.val); }
inline  float   IQ10toF(const iq10 & x) { return _IQ10toF(x.val); }
inline  float   IQ9toF(const iq9 & x )  { return _IQ9toF(x.val); }
inline  float   IQ8toF(const iq8 & x)   { return _IQ8toF(x.val); }
inline  float   IQ7toF(const iq7 & x)   { return _IQ7toF(x.val); }
inline  float   IQ6toF(const iq6 & x)   { return _IQ6toF(x.val); }
inline  float   IQ5toF(const iq5 & x)   { return _IQ5toF(x.val); }
inline  float   IQ4toF(const iq4 & x)   { return _IQ4toF(x.val); }
inline  float   IQ3toF(const iq3 & x)   { return _IQ3toF(x.val); }
inline  float   IQ2toF(const iq2 & x)   { return _IQ2toF(x.val); }
inline  float   IQ1toF(const iq1 & x)   { return _IQ1toF(x.val); }

//---------------------------------------------------------------------------
// Functions: IQsat(A, Pos, Neg)
//---------------------------------------------------------------------------

inline  iq      IQsat(const iq & x, const iq & Pos, const iq & Neg)
{
    iq temp;
    temp.val = _IQsat(x.val, Pos.val, Neg.val);
    return temp;
}

inline  iq30    IQsat(const iq30 & x, const iq30 & Pos, const iq30 & Neg)
{
    iq30 temp;
    temp.val = _IQsat(x.val, Pos.val, Neg.val);
    return temp;
}

inline  iq29    IQsat(const iq29 & x, const iq29 & Pos, const iq29 & Neg)
{
    iq29 temp;
    temp.val = _IQsat(x.val, Pos.val, Neg.val);
    return temp;
}

inline  iq28    IQsat(const iq28 & x, const iq28 & Pos, const iq28 & Neg)
{
    iq28 temp;
    temp.val = _IQsat(x.val, Pos.val, Neg.val);
    return temp;
}

inline  iq27    IQsat(const iq27 & x, const iq27 & Pos, const iq27 & Neg)
{
    iq27 temp;
    temp.val = _IQsat(x.val, Pos.val, Neg.val);
    return temp;
}

inline  iq26    IQsat(const iq26 & x, const iq26 & Pos, const iq26 & Neg)
{
    iq26 temp;
    temp.val = _IQsat(x.val, Pos.val, Neg.val);
    return temp;
}

inline  iq25    IQsat(const iq25 & x, const iq25 & Pos, const iq25 & Neg)
{
    iq25 temp;
    temp.val = _IQsat(x.val, Pos.val, Neg.val);
    return temp;
}

inline  iq24    IQsat(const iq24 & x, const iq24 & Pos, const iq24 & Neg)
{
    iq24 temp;
    temp.val = _IQsat(x.val, Pos.val, Neg.val);
    return temp;
}

inline  iq23    IQsat(const iq23 & x, const iq23 & Pos, const iq23 & Neg)
{
    iq23 temp;
    temp.val = _IQsat(x.val, Pos.val, Neg.val);
    return temp;
}

inline  iq22    IQsat(const iq22 & x, const iq22 & Pos, const iq22 & Neg)
{
    iq22 temp;
    temp.val = _IQsat(x.val, Pos.val, Neg.val);
    return temp;
}

inline  iq21    IQsat(const iq21 & x, const iq21 & Pos, const iq21 & Neg)
{
    iq21 temp;
    temp.val = _IQsat(x.val, Pos.val, Neg.val);
    return temp;
}

inline  iq20    IQsat(const iq20 & x, const iq20 & Pos, const iq20 & Neg)
{
    iq20 temp;
    temp.val = _IQsat(x.val, Pos.val, Neg.val);
    return temp;
}

inline  iq19    IQsat(const iq19 & x, const iq19 & Pos, const iq19 & Neg)
{
    iq19 temp;
    temp.val = _IQsat(x.val, Pos.val, Neg.val);
    return temp;
}

inline  iq18    IQsat(const iq18 & x, const iq18 & Pos, const iq18 & Neg)
{
    iq18 temp;
    temp.val = _IQsat(x.val, Pos.val, Neg.val);
    return temp;
}

inline  iq17    IQsat(const iq17 & x, const iq17 & Pos, const iq17 & Neg)
{
    iq17 temp;
    temp.val = _IQsat(x.val, Pos.val, Neg.val);
    return temp;
}

inline  iq16    IQsat(const iq16 & x, const iq16 & Pos, const iq16 & Neg)
{
    iq16 temp;
    temp.val = _IQsat(x.val, Pos.val, Neg.val);
    return temp;
}

inline  iq15    IQsat(const iq15 & x, const iq15 & Pos, const iq15 & Neg)
{
    iq15 temp;
    temp.val = _IQsat(x.val, Pos.val, Neg.val);
    return temp;
}

inline  iq14    IQsat(const iq14 & x, const iq14 & Pos, const iq14 & Neg)
{
    iq14 temp;
    temp.val = _IQsat(x.val, Pos.val, Neg.val);
    return temp;
}

inline  iq13    IQsat(const iq13 & x, const iq13 & Pos, const iq13 & Neg)
{
    iq13 temp;
    temp.val = _IQsat(x.val, Pos.val, Neg.val);
    return temp;
}

inline  iq12    IQsat(const iq12 & x, const iq12 & Pos, const iq12 & Neg)
{
    iq12 temp;
    temp.val = _IQsat(x.val, Pos.val, Neg.val);
    return temp;
}

inline  iq11    IQsat(const iq11 & x, const iq11 & Pos, const iq11 & Neg)
{
    iq11 temp;
    temp.val = _IQsat(x.val, Pos.val, Neg.val);
    return temp;
}

inline  iq10    IQsat(const iq10 & x, const iq10 & Pos, const iq10 & Neg)
{
    iq10 temp;
    temp.val = _IQsat(x.val, Pos.val, Neg.val);
    return temp;
}

inline  iq9    IQsat(const iq9 & x, const iq9 & Pos, const iq9 & Neg)
{
    iq9 temp;
    temp.val = _IQsat(x.val, Pos.val, Neg.val);
    return temp;
}

inline  iq8    IQsat(const iq8 & x, const iq8 & Pos, const iq8 & Neg)
{
    iq8 temp;
    temp.val = _IQsat(x.val, Pos.val, Neg.val);
    return temp;
}

inline  iq7    IQsat(const iq7 & x, const iq7 & Pos, const iq7 & Neg)
{
    iq7 temp;
    temp.val = _IQsat(x.val, Pos.val, Neg.val);
    return temp;
}

inline  iq6    IQsat(const iq6 & x, const iq6 & Pos, const iq6 & Neg)
{
    iq6 temp;
    temp.val = _IQsat(x.val, Pos.val, Neg.val);
    return temp;
}

inline  iq5    IQsat(const iq5 & x, const iq5 & Pos, const iq5 & Neg)
{
    iq5 temp;
    temp.val = _IQsat(x.val, Pos.val, Neg.val);
    return temp;
}

inline  iq4    IQsat(const iq4 & x, const iq4 & Pos, const iq4 & Neg)
{
    iq4 temp;
    temp.val = _IQsat(x.val, Pos.val, Neg.val);
    return temp;
}

inline  iq3    IQsat(const iq3 & x, const iq3 & Pos, const iq3 & Neg)
{
    iq3 temp;
    temp.val = _IQsat(x.val, Pos.val, Neg.val);
    return temp;
}

inline  iq2    IQsat(const iq2 & x, const iq2 & Pos, const iq2 & Neg)
{
    iq2 temp;
    temp.val = _IQsat(x.val, Pos.val, Neg.val);
    return temp;
}

inline  iq1    IQsat(const iq1 & x, const iq1 & Pos, const iq1 & Neg)
{
    iq1 temp;
    temp.val = _IQsat(x.val, Pos.val, Neg.val);
    return temp;
}
//---------------------------------------------------------------------------
// Functions: IQtoIQN(A)
//---------------------------------------------------------------------------

inline iq30 IQtoIQ30(const iq & x)
{
    iq30 temp;
    temp.val = _IQtoIQ30(x.val);
    return temp;
}

inline iq29 IQtoIQ29(const iq & x)
{
    iq29 temp;
    temp.val = _IQtoIQ29(x.val);
    return temp;
}

inline iq28 IQtoIQ28(const iq & x)
{
    iq28 temp;
    temp.val = _IQtoIQ28(x.val);
    return temp;
}

inline iq27 IQtoIQ27(const iq & x)
{
    iq27 temp;
    temp.val = _IQtoIQ27(x.val);
    return temp;
}

inline iq26 IQtoIQ26(const iq & x)
{
    iq26 temp;
    temp.val = _IQtoIQ26(x.val);
    return temp;
}

inline iq25 IQtoIQ25(const iq & x)
{
    iq25 temp;
    temp.val = _IQtoIQ25(x.val);
    return temp;
}

inline iq24 IQtoIQ24(const iq & x)
{
    iq24 temp;
    temp.val = _IQtoIQ24(x.val);
    return temp;
}

inline iq23 IQtoIQ23(const iq & x)
{
    iq23 temp;
    temp.val = _IQtoIQ23(x.val);
    return temp;
}

inline iq22 IQtoIQ22(const iq & x)
{
    iq22 temp;
    temp.val = _IQtoIQ22(x.val);
    return temp;
}

inline iq21 IQtoIQ21(const iq & x)
{
    iq21 temp;
    temp.val = _IQtoIQ21(x.val);
    return temp;
}

inline iq20 IQtoIQ20(const iq & x)
{
    iq20 temp;
    temp.val = _IQtoIQ20(x.val);
    return temp;
}

inline iq19 IQtoIQ19(const iq & x)
{
    iq19 temp;
    temp.val = _IQtoIQ19(x.val);
    return temp;
}

inline iq18 IQtoIQ18(const iq & x)
{
    iq18 temp;
    temp.val = _IQtoIQ18(x.val);
    return temp;
}

inline iq17 IQtoIQ17(const iq & x)
{
    iq17 temp;
    temp.val = _IQtoIQ17(x.val);
    return temp;
}

inline iq16 IQtoIQ16(const iq & x)
{
    iq16 temp;
    temp.val = _IQtoIQ16(x.val);
    return temp;
}

inline iq15 IQtoIQ15(const iq & x)
{
    iq15 temp;
    temp.val = _IQtoIQ15(x.val);
    return temp;
}

inline iq14 IQtoIQ14(const iq & x)
{
    iq14 temp;
    temp.val = _IQtoIQ14(x.val);
    return temp;
}

inline iq13 IQtoIQ13(const iq & x)
{
    iq13 temp;
    temp.val = _IQtoIQ13(x.val);
    return temp;
}

inline iq12 IQtoIQ12(const iq & x)
{
    iq12 temp;
    temp.val = _IQtoIQ12(x.val);
    return temp;
}

inline iq11 IQtoIQ11(const iq & x)
{
    iq11 temp;
    temp.val = _IQtoIQ11(x.val);
    return temp;
}

inline iq10 IQtoIQ10(const iq & x)
{
    iq10 temp;
    temp.val = _IQtoIQ10(x.val);
    return temp;
}


inline iq9 IQtoIQ9(const iq & x)
{
    iq9 temp;
    temp.val = _IQtoIQ9(x.val);
    return temp;
}

inline iq8 IQtoIQ8(const iq & x)
{
    iq8 temp;
    temp.val = _IQtoIQ8(x.val);
    return temp;
}

inline iq7 IQtoIQ7(const iq & x)
{
    iq7 temp;
    temp.val = _IQtoIQ7(x.val);
    return temp;
}

inline iq6 IQtoIQ6(const iq & x)
{
    iq6 temp;
    temp.val = _IQtoIQ6(x.val);
    return temp;
}

inline iq5 IQtoIQ5(const iq & x)
{
    iq5 temp;
    temp.val = _IQtoIQ5(x.val);
    return temp;
}

inline iq4 IQtoIQ4(const iq & x)
{
    iq4 temp;
    temp.val = _IQtoIQ4(x.val);
    return temp;
}

inline iq3 IQtoIQ3(const iq & x)
{
    iq3 temp;
    temp.val = _IQtoIQ3(x.val);
    return temp;
}

inline iq2 IQtoIQ2(const iq & x)
{
    iq2 temp;
    temp.val = _IQtoIQ2(x.val);
    return temp;
}

inline iq1 IQtoIQ1(const iq & x)
{
    iq1 temp;
    temp.val = _IQtoIQ1(x.val);
    return temp;
}
//---------------------------------------------------------------------------
// Functions: IQNtoIQ(A)
//---------------------------------------------------------------------------

inline iq IQ30toIQ(const iq30 & x)
{
    iq temp;
    temp.val = _IQ30toIQ(x.val);
    return temp;
}

inline iq IQ29toIQ(const iq29 & x)
{
    iq temp;
    temp.val = _IQ29toIQ(x.val);
    return temp;
}

inline iq IQ28toIQ(const iq28 & x)
{
    iq temp;
    temp.val = _IQ28toIQ(x.val);
    return temp;
}

inline iq IQ27toIQ(const iq27 & x)
{
    iq temp;
    temp.val = _IQ27toIQ(x.val);
    return temp;
}

inline iq IQ26toIQ(const iq26 & x)
{
    iq temp;
    temp.val = _IQ26toIQ(x.val);
    return temp;
}

inline iq IQ25toIQ(const iq25 & x)
{
    iq temp;
    temp.val = _IQ25toIQ(x.val);
    return temp;
}

inline iq IQ24toIQ(const iq24 & x)
{
    iq temp;
    temp.val = _IQ24toIQ(x.val);
    return temp;
}

inline iq IQ23toIQ(const iq23 & x)
{
    iq temp;
    temp.val = _IQ23toIQ(x.val);
    return temp;
}

inline iq IQ22toIQ(const iq22 & x)
{
    iq temp;
    temp.val = _IQ22toIQ(x.val);
    return temp;
}

inline iq IQ21toIQ(const iq21 & x)
{
    iq temp;
    temp.val = _IQ21toIQ(x.val);
    return temp;
}

inline iq IQ20toIQ(const iq20 & x)
{
    iq temp;
    temp.val = _IQ20toIQ(x.val);
    return temp;
}

inline iq IQ19toIQ(const iq19 & x)
{
    iq temp;
    temp.val = _IQ19toIQ(x.val);
    return temp;
}

inline iq IQ18toIQ(const iq18 & x)
{
    iq temp;
    temp.val = _IQ18toIQ(x.val);
    return temp;
}

inline iq IQ17toIQ(const iq17 & x)
{
    iq temp;
    temp.val = _IQ17toIQ(x.val);
    return temp;
}

inline iq IQ16toIQ(const iq16 & x)
{
    iq temp;
    temp.val = _IQ16toIQ(x.val);
    return temp;
}

inline iq IQ15toIQ(const iq15 & x)
{
    iq temp;
    temp.val = _IQ15toIQ(x.val);
    return temp;
}

inline iq IQ14toIQ(const iq14 & x)
{
    iq temp;
    temp.val = _IQ14toIQ(x.val);
    return temp;
}

inline iq IQ13toIQ(const iq13 & x)
{
    iq temp;
    temp.val = _IQ13toIQ(x.val);
    return temp;
}

inline iq IQ12toIQ(const iq12 & x)
{
    iq temp;
    temp.val = _IQ12toIQ(x.val);
    return temp;
}

inline iq IQ11toIQ(const iq11 & x)
{
    iq temp;
    temp.val = _IQ11toIQ(x.val);
    return temp;
}

inline iq IQ10toIQ(const iq10 & x)
{
    iq temp;
    temp.val = _IQ10toIQ(x.val);
    return temp;
}

inline iq IQ9toIQ(const iq9 & x)
{
    iq temp;
    temp.val = _IQ9toIQ(x.val);
    return temp;
}

inline iq IQ8toIQ(const iq8 & x)
{
    iq temp;
    temp.val = _IQ8toIQ(x.val);
    return temp;
}

inline iq IQ7toIQ(const iq7 & x)
{
    iq temp;
    temp.val = _IQ7toIQ(x.val);
    return temp;
}

inline iq IQ6toIQ(const iq6 & x)
{
    iq temp;
    temp.val = _IQ6toIQ(x.val);
    return temp;
}

inline iq IQ5toIQ(const iq5 & x)
{
    iq temp;
    temp.val = _IQ5toIQ(x.val);
    return temp;
}

inline iq IQ4toIQ(const iq4 & x)
{
    iq temp;
    temp.val = _IQ4toIQ(x.val);
    return temp;
}

inline iq IQ3toIQ(const iq3 & x)
{
    iq temp;
    temp.val = _IQ3toIQ(x.val);
    return temp;
}

inline iq IQ2toIQ(const iq2 & x)
{
    iq temp;
    temp.val = _IQ2toIQ(x.val);
    return temp;
}

inline iq IQ1toIQ(const iq1 & x)
{
    iq temp;
    temp.val = _IQ1toIQ(x.val);
    return temp;
}

//---------------------------------------------------------------------------
// Functions: IQtoQN(A)
//---------------------------------------------------------------------------

inline  long    IQtoQ15(const iq & x)  { return _IQtoQ15(x.val);   }
inline  long    IQtoQ14(const iq & x)  { return _IQtoQ14(x.val);   }
inline  long    IQtoQ13(const iq & x)  { return _IQtoQ13(x.val);   }
inline  long    IQtoQ12(const iq & x)  { return _IQtoQ12(x.val);   }
inline  long    IQtoQ11(const iq & x)  { return _IQtoQ11(x.val);   }
inline  long    IQtoQ10(const iq & x)  { return _IQtoQ10(x.val);   }
inline  long    IQtoQ9(const iq & x)   { return _IQtoQ9(x.val);    }
inline  long    IQtoQ8(const iq & x)   { return _IQtoQ8(x.val);    }
inline  long    IQtoQ7(const iq & x)   { return _IQtoQ7(x.val);    }
inline  long    IQtoQ6(const iq & x)   { return _IQtoQ6(x.val);    }
inline  long    IQtoQ5(const iq & x)   { return _IQtoQ5(x.val);    }
inline  long    IQtoQ4(const iq & x)   { return _IQtoQ4(x.val);    }
inline  long    IQtoQ3(const iq & x)   { return _IQtoQ3(x.val);    }
inline  long    IQtoQ2(const iq & x)   { return _IQtoQ2(x.val);    }
inline  long    IQtoQ1(const iq & x)   { return _IQtoQ1(x.val);    }

//---------------------------------------------------------------------------
// Functions: QNtoIQ(A)
//---------------------------------------------------------------------------

inline  iq  Q15toIQ(long x)
{
   iq temp;
   temp.val = _Q15toIQ(x);
   return temp;
}

inline  iq  Q14toIQ(long x)
{
   iq temp;
   temp.val = _Q14toIQ(x);
   return temp;
}

inline  iq  Q13toIQ(long x)
{
   iq temp;
   temp.val = _Q13toIQ(x);
   return temp;
}

inline  iq  Q12toIQ(long x)
{
   iq temp;
   temp.val = _Q12toIQ(x);
   return temp;
}

inline  iq  Q11toIQ(long x)
{
   iq temp;
   temp.val = _Q11toIQ(x);
   return temp;
}

inline  iq  Q10toIQ(long x)
{
   iq temp;
   temp.val = _Q10toIQ(x);
   return temp;
}

inline  iq  Q9toIQ(long x)
{
   iq temp;
   temp.val = _Q9toIQ(x);
   return temp;
}

inline  iq  Q8toIQ(long x)
{
   iq temp;
   temp.val = _Q8toIQ(x);
   return temp;
}

inline  iq  Q7toIQ(long x)
{
   iq temp;
   temp.val = _Q7toIQ(x);
   return temp;
}

inline  iq  Q6toIQ(long x)
{
   iq temp;
   temp.val = _Q6toIQ(x);
   return temp;
}

inline  iq  Q5toIQ(long x)
{
   iq temp;
   temp.val = _Q5toIQ(x);
   return temp;
}

inline  iq  Q4toIQ(long x)
{
   iq temp;
   temp.val = _Q4toIQ(x);
   return temp;
}

inline  iq  Q3toIQ(long x)
{
   iq temp;
   temp.val = _Q3toIQ(x);
   return temp;
}

inline  iq  Q2toIQ(long x)
{
   iq temp;
   temp.val = _Q2toIQ(x);
   return temp;
}

inline  iq  Q1toIQ(long x)
{
   iq temp;
   temp.val = _Q1toIQ(x);
   return temp;
}
//---------------------------------------------------------------------------
// Functions: IQtoa(A,B,C), IQNtoa(A,B,C)
//---------------------------------------------------------------------------
inline int IQtoa(char *A, const char *B, const iq & C)
{
       return __IQNtoa(A, B, C.val, GLOBAL_Q);
}
inline int IQ1toa(char *A, const char *B, const iq1 & C)
{
       return __IQNtoa(A, B, C.val, 1);
}
inline int IQ2toa(char *A, const char *B, const iq2 & C)
{
       return __IQNtoa(A, B, C.val, 2);
}
inline int IQ3toa(char *A, const char *B, const iq3 & C)
{
       return __IQNtoa(A, B, C.val, 3);
}
inline int IQ4toa(char *A, const char *B, const iq4 & C)
{
       return __IQNtoa(A, B, C.val, 14);
}
inline int IQ5toa(char *A, const char *B, const iq5 & C)
{
       return __IQNtoa(A, B, C.val, 5);
}
inline int IQ6toa(char *A, const char *B, const iq6 & C)
{
       return __IQNtoa(A, B, C.val, 6);
}
inline int IQ7toa(char *A, const char *B, const iq7 & C)
{
       return __IQNtoa(A, B, C.val, 7);
}
inline int IQ8toa(char *A, const char *B, const iq8 & C)
{
       return __IQNtoa(A, B, C.val, 8);
}
inline int IQ9toa(char *A, const char *B, const iq9 & C)
{
       return __IQNtoa(A, B, C.val, 9);
}
inline int IQ10toa(char *A, const char *B, const iq10 & C)
{
       return __IQNtoa(A, B, C.val, 10);
}
inline int IQ11toa(char *A, const char *B, const iq11 & C)
{
       return __IQNtoa(A, B, C.val, 11);
}
inline int IQ12toa(char *A, const char *B, const iq12 & C)
{
       return __IQNtoa(A, B, C.val, 12);
}
inline int IQ13toa(char *A, const char *B, const iq13 & C)
{
       return __IQNtoa(A, B, C.val, 13);
}
inline int IQ14toa(char *A, const char *B, const iq14 & C)
{
       return __IQNtoa(A, B, C.val, 14);
}
inline int IQ15toa(char *A, const char *B, const iq15 & C)
{
       return __IQNtoa(A, B, C.val, 15);
}
inline int IQ16toa(char *A, const char *B, const iq16 & C)
{
       return __IQNtoa(A, B, C.val, 16);
}
inline int IQ17toa(char *A, const char *B, const iq17 & C)
{
       return __IQNtoa(A, B, C.val, 17);
}
inline int IQ18toa(char *A, const char *B, const iq18 & C)
{
       return __IQNtoa(A, B, C.val, 18);
}
inline int IQ19toa(char *A, const char *B, const iq19 & C)
{
       return __IQNtoa(A, B, C.val, 19);
}
inline int IQ20toa(char *A, const char *B, const iq20 & C)
{
       return __IQNtoa(A, B, C.val, 20);
}
inline int IQ21toa(char *A, const char *B, const iq21 & C)
{
       return __IQNtoa(A, B, C.val, 21);
}
inline int IQ22toa(char *A, const char *B, const iq22 & C)
{
       return __IQNtoa(A, B, C.val, 22);
}
inline int IQ23toa(char *A, const char *B, const iq23 & C)
{
       return __IQNtoa(A, B, C.val, 23);
}
inline int IQ24toa(char *A, const char *B, const iq24 & C)
{
       return __IQNtoa(A, B, C.val, 24);
}
inline int IQ25toa(char *A, const char *B, const iq25 & C)
{
       return __IQNtoa(A, B, C.val, 25);
}
inline int IQ26toa(char *A, const char *B, const iq26 & C)
{
       return __IQNtoa(A, B, C.val, 26);
}
inline int IQ27toa(char *A, const char *B, const iq27 & C)
{
       return __IQNtoa(A, B, C.val, 27);
}
inline int IQ28toa(char *A, const char *B, const iq28 & C)
{
       return __IQNtoa(A, B, C.val, 28);
}
inline int IQ29toa(char *A, const char *B, const iq29 & C)
{
       return __IQNtoa(A, B, C.val, 29);
}
inline int IQ30toa(char *A, const char *B, const iq30 & C)
{
       return __IQNtoa(A, B, C.val, 30);
}

//---------------------------------------------------------------------------
// Functions: atoIQ(A), atoIQN(A)
//---------------------------------------------------------------------------
inline  iq  atoIQ(const char *A)
{
   iq temp;
   temp.val = _atoIQ(A);
   return temp;
}

inline  iq30  atoIQ30(const char *A)
{
   iq30 temp;
   temp.val = _atoIQ30(A);
   return temp;
}

inline  iq29  atoIQ29(const char *A)
{
   iq29 temp;
   temp.val = _atoIQ29(A);
   return temp;
}

inline  iq28  atoIQ28(const char *A)
{
   iq28 temp;
   temp.val = _atoIQ28(A);
   return temp;
}

inline  iq27  atoIQ27(const char *A)
{
   iq27 temp;
   temp.val = _atoIQ27(A);
   return temp;
}

inline  iq26  atoIQ26(const char *A)
{
   iq26 temp;
   temp.val = _atoIQ26(A);
   return temp;
}

inline  iq25  atoIQ25(const char *A)
{
   iq25 temp;
   temp.val = _atoIQ25(A);
   return temp;
}

inline  iq24  atoIQ24(const char *A)
{
   iq24 temp;
   temp.val = _atoIQ24(A);
   return temp;
}

inline  iq23  atoIQ23(const char *A)
{
   iq23 temp;
   temp.val = _atoIQ23(A);
   return temp;
}

inline  iq22  atoIQ22(const char *A)
{
   iq22 temp;
   temp.val = _atoIQ22(A);
   return temp;
}

inline  iq21  atoIQ21(const char *A)
{
   iq21 temp;
   temp.val = _atoIQ21(A);
   return temp;
}

inline  iq20  atoIQ20(const char *A)
{
   iq20 temp;
   temp.val = _atoIQ20(A);
   return temp;
}

inline  iq19  atoIQ19(const char *A)
{
   iq19 temp;
   temp.val = _atoIQ19(A);
   return temp;
}

inline  iq18  atoIQ18(const char *A)
{
   iq18 temp;
   temp.val = _atoIQ18(A);
   return temp;
}

inline  iq17  atoIQ17(const char *A)
{
   iq17 temp;
   temp.val = _atoIQ17(A);
   return temp;
}

inline  iq16  atoIQ16(const char *A)
{
   iq16 temp;
   temp.val = _atoIQ16(A);
   return temp;
}

inline  iq15  atoIQ15(const char *A)
{
   iq15 temp;
   temp.val = _atoIQ15(A);
   return temp;
}

inline  iq14  atoIQ14(const char *A)
{
   iq14 temp;
   temp.val = _atoIQ14(A);
   return temp;
}

inline  iq13  atoIQ13(const char *A)
{
   iq13 temp;
   temp.val = _atoIQ13(A);
   return temp;
}

inline  iq12  atoIQ12(const char *A)
{
   iq12 temp;
   temp.val = _atoIQ12(A);
   return temp;
}

inline  iq10  atoIQ10(const char *A)
{
   iq10 temp;
   temp.val = _atoIQ10(A);
   return temp;
}

inline  iq9  atoIQ9(const char *A)
{
   iq9 temp;
   temp.val = _atoIQ9(A);
   return temp;
}

inline  iq8  atoIQ8(const char *A)
{
   iq8 temp;
   temp.val = _atoIQ8(A);
   return temp;
}

inline  iq7  atoIQ7(const char *A)
{
   iq7 temp;
   temp.val = _atoIQ7(A);
   return temp;
}

inline  iq6  atoIQ6(const char *A)
{
   iq6 temp;
   temp.val = _atoIQ6(A);
   return temp;
}

inline  iq5  atoIQ5(const char *A)
{
   iq5 temp;
   temp.val = _atoIQ5(A);
   return temp;
}

inline  iq4  atoIQ4(const char *A)
{
   iq4 temp;
   temp.val = _atoIQ4(A);
   return temp;
}

inline  iq3  atoIQ3(const char *A)
{
   iq3 temp;
   temp.val = _atoIQ3(A);
   return temp;
}

inline  iq2  atoIQ2(const char *A)
{
   iq2 temp;
   temp.val = _atoIQ2(A);
   return temp;
}

inline  iq1  atoIQ1(const char *A)
{
   iq1 temp;
   temp.val = _atoIQ1(A);
   return temp;
}


//---------------------------------------------------------------------------
// Functions: IQint(A), IQNint(A)
//---------------------------------------------------------------------------

inline  long    IQint(const iq & x)     { return _IQint(x.val);   }
inline  long    IQ30int(const iq30 & x) { return _IQ30int(x.val); }
inline  long    IQ29int(const iq29 & x) { return _IQ29int(x.val); }
inline  long    IQ28int(const iq28 & x) { return _IQ28int(x.val); }
inline  long    IQ27int(const iq27 & x) { return _IQ27int(x.val); }
inline  long    IQ26int(const iq26 & x) { return _IQ26int(x.val); }
inline  long    IQ25int(const iq25 & x) { return _IQ25int(x.val); }
inline  long    IQ24int(const iq24 & x) { return _IQ24int(x.val); }
inline  long    IQ23int(const iq23 & x) { return _IQ23int(x.val); }
inline  long    IQ22int(const iq22 & x) { return _IQ22int(x.val); }
inline  long    IQ21int(const iq21 & x) { return _IQ21int(x.val); }
inline  long    IQ20int(const iq20 & x) { return _IQ20int(x.val); }
inline  long    IQ19int(const iq19 & x) { return _IQ19int(x.val); }
inline  long    IQ18int(const iq18 & x) { return _IQ18int(x.val); }
inline  long    IQ17int(const iq17 & x) { return _IQ17int(x.val); }
inline  long    IQ16int(const iq16 & x) { return _IQ16int(x.val); }
inline  long    IQ15int(const iq15 & x) { return _IQ15int(x.val); }
inline  long    IQ14int(const iq14 & x) { return _IQ14int(x.val); }
inline  long    IQ13int(const iq13 & x) { return _IQ13int(x.val); }
inline  long    IQ12int(const iq12 & x) { return _IQ12int(x.val); }
inline  long    IQ11int(const iq11 & x) { return _IQ11int(x.val); }
inline  long    IQ10int(const iq10 & x) { return _IQ10int(x.val); }
inline  long    IQ9int(const iq9 & x)   { return _IQ9int(x.val); }
inline  long    IQ8int(const iq8 & x)   { return _IQ8int(x.val); }
inline  long    IQ7int(const iq7 & x)   { return _IQ7int(x.val); }
inline  long    IQ6int(const iq6 & x)   { return _IQ6int(x.val); }
inline  long    IQ5int(const iq5 & x)   { return _IQ5int(x.val); }
inline  long    IQ4int(const iq4 & x)   { return _IQ4int(x.val); }
inline  long    IQ3int(const iq3 & x)   { return _IQ3int(x.val); }
inline  long    IQ2int(const iq2 & x)   { return _IQ2int(x.val); }
inline  long    IQ1int(const iq1 & x)   { return _IQ1int(x.val); }

//---------------------------------------------------------------------------
// Functions: IQfrac(A), IQNfrac(A)
//---------------------------------------------------------------------------

inline  iq  IQfrac(const iq & x)
{
   iq temp;
   temp.val = _IQfrac(x.val);
   return temp;
}

inline  iq30  IQ30frac(const iq30 & x)
{
   iq30 temp;
   temp.val = _IQ30frac(x.val);
   return temp;
}

inline  iq29  IQ29frac(const iq29 & x)
{
   iq29 temp;
   temp.val = _IQ29frac(x.val);
   return temp;
}

inline  iq28  IQ28frac(const iq28 & x)
{
   iq28 temp;
   temp.val = _IQ28frac(x.val);
   return temp;
}

inline  iq27  IQ27frac(const iq27 & x)
{
   iq27 temp;
   temp.val = _IQ27frac(x.val);
   return temp;
}

inline  iq26  IQ26frac(const iq26 & x)
{
   iq26 temp;
   temp.val = _IQ26frac(x.val);
   return temp;
}

inline  iq25  IQ25frac(const iq25 & x)
{
   iq25 temp;
   temp.val = _IQ25frac(x.val);
   return temp;
}

inline  iq24  IQ24frac(const iq24 & x)
{
   iq24 temp;
   temp.val = _IQ24frac(x.val);
   return temp;
}

inline  iq23  IQ23frac(const iq23 & x)
{
   iq23 temp;
   temp.val = _IQ23frac(x.val);
   return temp;
}

inline  iq22  IQ22frac(const iq22 & x)
{
   iq22 temp;
   temp.val = _IQ22frac(x.val);
   return temp;
}

inline  iq21  IQ21frac(const iq21 & x)
{
   iq21 temp;
   temp.val = _IQ21frac(x.val);
   return temp;
}

inline  iq20  IQ20frac(const iq20 & x)
{
   iq20 temp;
   temp.val = _IQ20frac(x.val);
   return temp;
}

inline  iq19  IQ19frac(const iq19 & x)
{
   iq19 temp;
   temp.val = _IQ19frac(x.val);
   return temp;
}

inline  iq18  IQ18frac(const iq18 & x)
{
   iq18 temp;
   temp.val = _IQ18frac(x.val);
   return temp;
}

inline  iq17  IQ17frac(const iq17 & x)
{
   iq17 temp;
   temp.val = _IQ17frac(x.val);
   return temp;
}

inline  iq16  IQ16frac(const iq16 & x)
{
   iq16 temp;
   temp.val = _IQ16frac(x.val);
   return temp;
}

inline  iq15  IQ15frac(const iq15 & x)
{
   iq15 temp;
   temp.val = _IQ15frac(x.val);
   return temp;
}

inline  iq14  IQ14frac(const iq14 & x)
{
   iq14 temp;
   temp.val = _IQ14frac(x.val);
   return temp;
}

inline  iq13  IQ13frac(const iq13 & x)
{
   iq13 temp;
   temp.val = _IQ13frac(x.val);
   return temp;
}

inline  iq12  IQ12frac(const iq12 & x)
{
   iq12 temp;
   temp.val = _IQ12frac(x.val);
   return temp;
}

inline  iq11  IQ11frac(const iq11 & x)
{
   iq11 temp;
   temp.val = _IQ11frac(x.val);
   return temp;
}

inline  iq10  IQ10frac(const iq10 & x)
{
   iq10 temp;
   temp.val = _IQ10frac(x.val);
   return temp;
}

inline  iq9  IQ9frac(const iq9 & x)
{
   iq9 temp;
   temp.val = _IQ9frac(x.val);
   return temp;
}

inline  iq8  IQ8frac(const iq8 & x)
{
   iq8 temp;
   temp.val = _IQ8frac(x.val);
   return temp;
}

inline  iq7  IQ7frac(const iq7 & x)
{
   iq7 temp;
   temp.val = _IQ7frac(x.val);
   return temp;
}

inline  iq6  IQ6frac(const iq6 & x)
{
   iq6 temp;
   temp.val = _IQ6frac(x.val);
   return temp;
}

inline  iq5  IQ5frac(const iq5 & x)
{
   iq5 temp;
   temp.val = _IQ5frac(x.val);
   return temp;
}

inline  iq4  IQ4frac(const iq4 & x)
{
   iq4 temp;
   temp.val = _IQ4frac(x.val);
   return temp;
}

inline  iq3  IQ3frac(const iq3 & x)
{
   iq3 temp;
   temp.val = _IQ3frac(x.val);
   return temp;
}

inline  iq2  IQ2frac(const iq2 & x)
{
   iq2 temp;
   temp.val = _IQ2frac(x.val);
   return temp;
}

inline  iq1  IQ1frac(const iq1 & x)
{
   iq1 temp;
   temp.val = _IQ1frac(x.val);
   return temp;
}


//---------------------------------------------------------------------------
// Functions: IQrmpy(A,B), IQNrmpy(A,B)
//---------------------------------------------------------------------------

inline  iq  IQrmpy(const iq & x, const iq & y)
{
   iq temp;
   temp.val = _IQrmpy(x.val, y.val);
   return temp;
}

inline  iq30    IQ30rmpy(const iq30 & x, const iq30 & y)
{
   iq30 temp;
   temp.val = _IQ30rmpy(x.val, y.val);
   return temp;
}

inline  iq29    IQ29rmpy(const iq29 & x, const iq29 & y)
{
   iq29 temp;
   temp.val = _IQ29rmpy(x.val, y.val);
   return temp;
}

inline  iq28    IQ28rmpy(const iq28 & x, const iq28 & y)
{
   iq28 temp;
   temp.val = _IQ28rmpy(x.val, y.val);
   return temp;
}

inline  iq27    IQ27rmpy(const iq27 & x, const iq27 & y)
{
   iq27 temp;
   temp.val = _IQ27rmpy(x.val, y.val);
   return temp;
}

inline  iq26    IQ26rmpy(const iq26 & x, const iq26 & y)
{
   iq26 temp;
   temp.val = _IQ26rmpy(x.val, y.val);
   return temp;
}

inline  iq25    IQ25rmpy(const iq25 & x, const iq25 & y)
{
   iq25 temp;
   temp.val = _IQ25rmpy(x.val, y.val);
   return temp;
}

inline  iq24    IQ24rmpy(const iq24 & x, const iq24 & y)
{
   iq24 temp;
   temp.val = _IQ24rmpy(x.val, y.val);
   return temp;
}

inline  iq23    IQ23rmpy(const iq23 & x, const iq23 & y)
{
   iq23 temp;
   temp.val = _IQ23rmpy(x.val, y.val);
   return temp;
}

inline  iq22    IQ22rmpy(const iq22 & x, const iq22 & y)
{
   iq22 temp;
   temp.val = _IQ22rmpy(x.val, y.val);
   return temp;
}

inline  iq21    IQ21rmpy(const iq21 & x, const iq21 & y)
{
   iq21 temp;
   temp.val = _IQ21rmpy(x.val, y.val);
   return temp;
}

inline  iq20    IQ20rmpy(const iq20 & x, const iq20 & y)
{
   iq20 temp;
   temp.val = _IQ20rmpy(x.val, y.val);
   return temp;
}

inline  iq19    IQ19rmpy(const iq19 & x, const iq19 & y)
{
   iq19 temp;
   temp.val = _IQ19rmpy(x.val, y.val);
   return temp;
}

inline  iq18    IQ18rmpy(const iq18 & x, const iq18 & y)
{
   iq18 temp;
   temp.val = _IQ18rmpy(x.val, y.val);
   return temp;
}

inline  iq17    IQ17rmpy(const iq17 & x, const iq17 & y)
{
   iq17 temp;
   temp.val = _IQ17rmpy(x.val, y.val);
   return temp;
}

inline  iq16    IQ16rmpy(const iq16 & x, const iq16 & y)
{
   iq16 temp;
   temp.val = _IQ16rmpy(x.val, y.val);
   return temp;
}

inline  iq15    IQ15rmpy(const iq15 & x, const iq15 & y)
{
   iq15 temp;
   temp.val = _IQ15rmpy(x.val, y.val);
   return temp;
}

inline  iq14    IQ14rmpy(const iq14 & x, const iq14 & y)
{
   iq14 temp;
   temp.val = _IQ14rmpy(x.val, y.val);
   return temp;
}

inline  iq13    IQ13rmpy(const iq13 & x, const iq13 & y)
{
   iq13 temp;
   temp.val = _IQ13rmpy(x.val, y.val);
   return temp;
}

inline  iq12    IQ12rmpy(const iq12 & x, const iq12 & y)
{
   iq12 temp;
   temp.val = _IQ12rmpy(x.val, y.val);
   return temp;
}

inline  iq11    IQ11rmpy(const iq11 & x, const iq11 & y)
{
   iq11 temp;
   temp.val = _IQ11rmpy(x.val, y.val);
   return temp;
}

inline  iq10    IQ10rmpy(const iq10 & x, const iq10 & y)
{
   iq10 temp;
   temp.val = _IQ10rmpy(x.val, y.val);
   return temp;
}

inline  iq9    IQ9rmpy(const iq9 & x, const iq9 & y)
{
   iq9 temp;
   temp.val = _IQ9rmpy(x.val, y.val);
   return temp;
}

inline  iq8    IQ8rmpy(const iq8 & x, const iq8 & y)
{
   iq8 temp;
   temp.val = _IQ8rmpy(x.val, y.val);
   return temp;
}

inline  iq7    IQ7rmpy(const iq7 & x, const iq7 & y)
{
   iq7 temp;
   temp.val = _IQ7rmpy(x.val, y.val);
   return temp;
}

inline  iq6    IQ6rmpy(const iq6 & x, const iq6 & y)
{
   iq6 temp;
   temp.val = _IQ6rmpy(x.val, y.val);
   return temp;
}

inline  iq5    IQ5rmpy(const iq5 & x, const iq5 & y)
{
   iq5 temp;
   temp.val = _IQ5rmpy(x.val, y.val);
   return temp;
}

inline  iq4    IQ4rmpy(const iq4 & x, const iq4 & y)
{
   iq4 temp;
   temp.val = _IQ4rmpy(x.val, y.val);
   return temp;
}

inline  iq3    IQ3rmpy(const iq3 & x, const iq3 & y)
{
   iq3 temp;
   temp.val = _IQ3rmpy(x.val, y.val);
   return temp;
}

inline  iq2    IQ2rmpy(const iq2 & x, const iq2 & y)
{
   iq2 temp;
   temp.val = _IQ2rmpy(x.val, y.val);
   return temp;
}

inline  iq1    IQ1rmpy(const iq1 & x, const iq1 & y)
{
   iq1 temp;
   temp.val = _IQ1rmpy(x.val, y.val);
   return temp;
}

//---------------------------------------------------------------------------
// Functions: IQrsmpy(A,B), IQNrsmpy(A,B)
//---------------------------------------------------------------------------

inline  iq  IQrsmpy(const iq & x, const iq & y)
{
   iq temp;
   temp.val = _IQrsmpy(x.val, y.val);
   return temp;
}

inline  iq30    IQ30rsmpy(const iq30 & x, const iq30 & y)
{
   iq30 temp;
   temp.val = _IQ30rsmpy(x.val, y.val);
   return temp;
}

inline  iq29    IQ29rsmpy(const iq29 & x, const iq29 & y)
{
   iq29 temp;
   temp.val = _IQ29rsmpy(x.val, y.val);
   return temp;
}

inline  iq28    IQ28rsmpy(const iq28 & x, const iq28 & y)
{
   iq28 temp;
   temp.val = _IQ28rsmpy(x.val, y.val);
   return temp;
}

inline  iq27    IQ27rsmpy(const iq27 & x, const iq27 & y)
{
   iq27 temp;
   temp.val = _IQ27rsmpy(x.val, y.val);
   return temp;
}

inline  iq26    IQ26rsmpy(const iq26 & x, const iq26 & y)
{
   iq26 temp;
   temp.val = _IQ26rsmpy(x.val, y.val);
   return temp;
}

inline  iq25    IQ25rsmpy(const iq25 & x, const iq25 & y)
{
   iq25 temp;
   temp.val = _IQ25rsmpy(x.val, y.val);
   return temp;
}

inline  iq24    IQ24rsmpy(const iq24 & x, const iq24 & y)
{
   iq24 temp;
   temp.val = _IQ24rsmpy(x.val, y.val);
   return temp;
}

inline  iq23    IQ23rsmpy(const iq23 & x, const iq23 & y)
{
   iq23 temp;
   temp.val = _IQ23rsmpy(x.val, y.val);
   return temp;
}

inline  iq22    IQ22rsmpy(const iq22 & x, const iq22 & y)
{
   iq22 temp;
   temp.val = _IQ22rsmpy(x.val, y.val);
   return temp;
}

inline  iq21    IQ21rsmpy(const iq21 & x, const iq21 & y)
{
   iq21 temp;
   temp.val = _IQ21rsmpy(x.val, y.val);
   return temp;
}

inline  iq20    IQ20rsmpy(const iq20 & x, const iq20 & y)
{
   iq20 temp;
   temp.val = _IQ20rsmpy(x.val, y.val);
   return temp;
}

inline  iq19    IQ19rsmpy(const iq19 & x, const iq19 & y)
{
   iq19 temp;
   temp.val = _IQ19rsmpy(x.val, y.val);
   return temp;
}

inline  iq18    IQ18rsmpy(const iq18 & x, const iq18 & y)
{
   iq18 temp;
   temp.val = _IQ18rsmpy(x.val, y.val);
   return temp;
}

inline  iq17    IQ17rsmpy(const iq17 & x, const iq17 & y)
{
   iq17 temp;
   temp.val = _IQ17rsmpy(x.val, y.val);
   return temp;
}

inline  iq16    IQ16rsmpy(const iq16 & x, const iq16 & y)
{
   iq16 temp;
   temp.val = _IQ16rsmpy(x.val, y.val);
   return temp;
}

inline  iq15    IQ15rsmpy(const iq15 & x, const iq15 & y)
{
   iq15 temp;
   temp.val = _IQ15rsmpy(x.val, y.val);
   return temp;
}

inline  iq14    IQ14rsmpy(const iq14 & x, const iq14 & y)
{
   iq14 temp;
   temp.val = _IQ14rsmpy(x.val, y.val);
   return temp;
}

inline  iq13    IQ13rsmpy(const iq13 & x, const iq13 & y)
{
   iq13 temp;
   temp.val = _IQ13rsmpy(x.val, y.val);
   return temp;
}

inline  iq12    IQ12rsmpy(const iq12 & x, const iq12 & y)
{
   iq12 temp;
   temp.val = _IQ12rsmpy(x.val, y.val);
   return temp;
}

inline  iq11    IQ11rsmpy(const iq11 & x, const iq11 & y)
{
   iq11 temp;
   temp.val = _IQ11rsmpy(x.val, y.val);
   return temp;
}

inline  iq10    IQ10rsmpy(const iq10 & x, const iq10 & y)
{
   iq10 temp;
   temp.val = _IQ10rsmpy(x.val, y.val);
   return temp;
}

inline  iq9    IQ9rsmpy(const iq9 & x, const iq9 & y)
{
   iq9 temp;
   temp.val = _IQ9rsmpy(x.val, y.val);
   return temp;
}

inline  iq8    IQ8rsmpy(const iq8 & x, const iq8 & y)
{
   iq8 temp;
   temp.val = _IQ8rsmpy(x.val, y.val);
   return temp;
}

inline  iq7    IQ7rsmpy(const iq7 & x, const iq7 & y)
{
   iq7 temp;
   temp.val = _IQ7rsmpy(x.val, y.val);
   return temp;
}

inline  iq6    IQ6rsmpy(const iq6 & x, const iq6 & y)
{
   iq6 temp;
   temp.val = _IQ6rsmpy(x.val, y.val);
   return temp;
}

inline  iq5    IQ5rsmpy(const iq5 & x, const iq5 & y)
{
   iq5 temp;
   temp.val = _IQ5rsmpy(x.val, y.val);
   return temp;
}

inline  iq4    IQ4rsmpy(const iq4 & x, const iq4 & y)
{
   iq4 temp;
   temp.val = _IQ4rsmpy(x.val, y.val);
   return temp;
}

inline  iq3    IQ3rsmpy(const iq3 & x, const iq3 & y)
{
   iq3 temp;
   temp.val = _IQ3rsmpy(x.val, y.val);
   return temp;
}

inline  iq2    IQ2rsmpy(const iq2 & x, const iq2 & y)
{
   iq2 temp;
   temp.val = _IQ2rsmpy(x.val, y.val);
   return temp;
}

inline  iq1    IQ1rsmpy(const iq1 & x, const iq1 & y)
{
   iq1 temp;
   temp.val = _IQ1rsmpy(x.val, y.val);
   return temp;
}

//---------------------------------------------------------------------------
// Functions: IQmpyIQX(A,IQA,B,IQB), IQNmpyIQX(A,IQA,B,IQB)
//---------------------------------------------------------------------------

#define  IQmpyIQX(A, IQA, B, IQB)   ((iq)   __IQxmpy(A.val, B.val, (GLOBAL_Q + 32 - IQA - IQB)))
#define  IQ30mpyIQX(A, IQA, B, IQB) ((iq30) __IQxmpy(A.val, B.val, (30 + 32 - IQA - IQB)))
#define  IQ29mpyIQX(A, IQA, B, IQB) ((iq29) __IQxmpy(A.val, B.val, (29 + 32 - IQA - IQB)))
#define  IQ28mpyIQX(A, IQA, B, IQB) ((iq28) __IQxmpy(A.val, B.val, (28 + 32 - IQA - IQB)))
#define  IQ27mpyIQX(A, IQA, B, IQB) ((iq27) __IQxmpy(A.val, B.val, (27 + 32 - IQA - IQB)))
#define  IQ26mpyIQX(A, IQA, B, IQB) ((iq26) __IQxmpy(A.val, B.val, (26 + 32 - IQA - IQB)))
#define  IQ25mpyIQX(A, IQA, B, IQB) ((iq25) __IQxmpy(A.val, B.val, (25 + 32 - IQA - IQB)))
#define  IQ24mpyIQX(A, IQA, B, IQB) ((iq24) __IQxmpy(A.val, B.val, (24 + 32 - IQA - IQB)))
#define  IQ23mpyIQX(A, IQA, B, IQB) ((iq23) __IQxmpy(A.val, B.val, (23 + 32 - IQA - IQB)))
#define  IQ22mpyIQX(A, IQA, B, IQB) ((iq22) __IQxmpy(A.val, B.val, (22 + 32 - IQA - IQB)))
#define  IQ21mpyIQX(A, IQA, B, IQB) ((iq21) __IQxmpy(A.val, B.val, (21 + 32 - IQA - IQB)))
#define  IQ20mpyIQX(A, IQA, B, IQB) ((iq20) __IQxmpy(A.val, B.val, (20 + 32 - IQA - IQB)))
#define  IQ19mpyIQX(A, IQA, B, IQB) ((iq19) __IQxmpy(A.val, B.val, (19 + 32 - IQA - IQB)))
#define  IQ18mpyIQX(A, IQA, B, IQB) ((iq18) __IQxmpy(A.val, B.val, (18 + 32 - IQA - IQB)))
#define  IQ17mpyIQX(A, IQA, B, IQB) ((iq17) __IQxmpy(A.val, B.val, (17 + 32 - IQA - IQB)))
#define  IQ16mpyIQX(A, IQA, B, IQB) ((iq16) __IQxmpy(A.val, B.val, (16 + 32 - IQA - IQB)))
#define  IQ15mpyIQX(A, IQA, B, IQB) ((iq15) __IQxmpy(A.val, B.val, (15 + 32 - IQA - IQB)))
#define  IQ14mpyIQX(A, IQA, B, IQB) ((iq14) __IQxmpy(A.val, B.val, (14 + 32 - IQA - IQB)))
#define  IQ13mpyIQX(A, IQA, B, IQB) ((iq13) __IQxmpy(A.val, B.val, (13 + 32 - IQA - IQB)))
#define  IQ12mpyIQX(A, IQA, B, IQB) ((iq12) __IQxmpy(A.val, B.val, (12 + 32 - IQA - IQB)))
#define  IQ11mpyIQX(A, IQA, B, IQB) ((iq11) __IQxmpy(A.val, B.val, (11 + 32 - IQA - IQB)))
#define  IQ10mpyIQX(A, IQA, B, IQB) ((iq10) __IQxmpy(A.val, B.val, (10 + 32 - IQA - IQB)))
#define  IQ9mpyIQX(A, IQA, B, IQB)  ((iq9)  __IQxmpy(A.val, B.val, ( 9 + 32 - IQA - IQB)))
#define  IQ8mpyIQX(A, IQA, B, IQB)  ((iq8)  __IQxmpy(A.val, B.val, ( 8 + 32 - IQA - IQB)))
#define  IQ7mpyIQX(A, IQA, B, IQB)  ((iq7)  __IQxmpy(A.val, B.val, ( 7 + 32 - IQA - IQB)))
#define  IQ6mpyIQX(A, IQA, B, IQB)  ((iq6)  __IQxmpy(A.val, B.val, ( 6 + 32 - IQA - IQB)))
#define  IQ5mpyIQX(A, IQA, B, IQB)  ((iq5)  __IQxmpy(A.val, B.val, ( 5 + 32 - IQA - IQB)))
#define  IQ4mpyIQX(A, IQA, B, IQB)  ((iq4)  __IQxmpy(A.val, B.val, ( 4 + 32 - IQA - IQB)))
#define  IQ3mpyIQX(A, IQA, B, IQB)  ((iq3)  __IQxmpy(A.val, B.val, ( 3 + 32 - IQA - IQB)))
#define  IQ2mpyIQX(A, IQA, B, IQB)  ((iq2)  __IQxmpy(A.val, B.val, ( 2 + 32 - IQA - IQB)))
#define  IQ1mpyIQX(A, IQA, B, IQB)  ((iq1)  __IQxmpy(A.val, B.val, ( 1 + 32 - IQA - IQB)))
//---------------------------------------------------------------------------
// Functions: IQmpyI32(A,B), IQNmpyI32(A,B)
//---------------------------------------------------------------------------

inline  iq  IQmpyI32(const iq & y, long x)
{
   iq temp;
   temp.val = (y.val * x);
   return temp;
}

inline  iq  IQmpyI32(long y, const iq & x)
{
   iq temp;
   temp.val = (y * x.val);
   return temp;
}

inline  iq30    IQ30mpyI32(const iq30 & y, long x)
{
   iq30 temp;
   temp.val = (y.val * x);
   return temp;
}

inline  iq30    IQ30mpyI32(long y, const iq30 & x)
{
   iq30 temp;
   temp.val = (y * x.val);
   return temp;
}

inline  iq29    IQ29mpyI32(const iq29 & y, long x)
{
   iq29 temp;
   temp.val = (y.val * x);
   return temp;
}

inline  iq29    IQ29mpyI32(long y, const iq29 & x)
{
   iq29 temp;
   temp.val = (y * x.val);
   return temp;
}

inline  iq28    IQ28mpyI32(const iq28 & y, long x)
{
   iq28 temp;
   temp.val = (y.val * x);
   return temp;
}

inline  iq28    IQ28mpyI32(long y, const iq28 & x)
{
   iq28 temp;
   temp.val = (y * x.val);
   return temp;
}

inline  iq27    IQ27mpyI32(const iq27 & y, long x)
{
   iq27 temp;
   temp.val = (y.val * x);
   return temp;
}

inline  iq27    IQ27mpyI32(long y, const iq27 & x)
{
   iq27 temp;
   temp.val = (y * x.val);
   return temp;
}

inline  iq26    IQ26mpyI32(const iq26 & y, long x)
{
   iq26 temp;
   temp.val = (y.val * x);
   return temp;
}

inline  iq26    IQ26mpyI32(long y, const iq26 & x)
{
   iq26 temp;
   temp.val = (y * x.val);
   return temp;
}

inline  iq25    IQ25mpyI32(const iq25 & y, long x)
{
   iq25 temp;
   temp.val = (y.val * x);
   return temp;
}

inline  iq25    IQ25mpyI32(long y, const iq25 & x)
{
   iq25 temp;
   temp.val = (y * x.val);
   return temp;
}

inline  iq24    IQ24mpyI32(const iq24 & y, long x)
{
   iq24 temp;
   temp.val = (y.val * x);
   return temp;
}

inline  iq24    IQ24mpyI32(long y, const iq24 & x)
{
   iq24 temp;
   temp.val = (y * x.val);
   return temp;
}

inline  iq23    IQ23mpyI32(const iq23 & y, long x)
{
   iq23 temp;
   temp.val = (y.val * x);
   return temp;
}

inline  iq23    IQ23mpyI32(long y, const iq23 & x)
{
   iq23 temp;
   temp.val = (y * x.val);
   return temp;
}

inline  iq22    IQ22mpyI32(const iq22 & y, long x)
{
   iq22 temp;
   temp.val = (y.val * x);
   return temp;
}

inline  iq22    IQ22mpyI32(long y, const iq22 & x)
{
   iq22 temp;
   temp.val = (y * x.val);
   return temp;
}

inline  iq21    IQ21mpyI32(const iq21 & y,long x)
{
   iq21 temp;
   temp.val = (y.val * x);
   return temp;
}

inline  iq21    IQ21mpyI32(long y, const iq21 & x)
{
   iq21 temp;
   temp.val = (y * x.val);
   return temp;
}

inline  iq20    IQ20mpyI32(const iq20 & y,long x)
{
   iq20 temp;
   temp.val = (y.val * x);
   return temp;
}

inline  iq20    IQ20mpyI32(long y, const iq20 & x)
{
   iq20 temp;
   temp.val = (y * x.val);
   return temp;
}

inline  iq19    IQ19mpyI32(const iq19 & y,long x)
{
   iq19 temp;
   temp.val = (y.val * x);
   return temp;
}

inline  iq19    IQ19mpyI32(long y, const iq19 & x)
{
   iq19 temp;
   temp.val = (y * x.val);
   return temp;
}

inline  iq18    IQ18mpyI32(const iq18 & y,long x)
{
   iq18 temp;
   temp.val = (y.val * x);
   return temp;
}

inline  iq18    IQ18mpyI32(long y, const iq18 & x)
{
   iq18 temp;
   temp.val = (y * x.val);
   return temp;
}

inline  iq17    IQ17mpyI32(const iq17 & y,long x)
{
   iq17 temp;
   temp.val = (y.val * x);
   return temp;
}

inline  iq17    IQ17mpyI32(long y, const iq17 & x)
{
   iq17 temp;
   temp.val = (y * x.val);
   return temp;
}

inline  iq16    IQ16mpyI32(const iq16 & y,long x)
{
   iq16 temp;
   temp.val = (y.val * x);
   return temp;
}

inline  iq16    IQ16mpyI32(long y, const iq16 & x)
{
   iq16 temp;
   temp.val = (y * x.val);
   return temp;
}

inline  iq15    IQ15mpyI32(const iq15 & y,long x)
{
   iq15 temp;
   temp.val = (y.val * x);
   return temp;
}

inline  iq15    IQ15mpyI32(long y, const iq15 & x)
{
   iq15 temp;
   temp.val = (y * x.val);
   return temp;
}


inline  iq14    IQ14mpyI32(const iq14 & y,long x)
{
   iq14 temp;
   temp.val = (y.val * x);
   return temp;
}

inline  iq14    IQ14mpyI32(long y, const iq14 & x)
{
   iq14 temp;
   temp.val = (y * x.val);
   return temp;
}

inline  iq13    IQ13mpyI32(const iq13 & y,long x)
{
   iq13 temp;
   temp.val = (y.val * x);
   return temp;
}

inline  iq13    IQ13mpyI32(long y, const iq13 & x)
{
   iq13 temp;
   temp.val = (y * x.val);
   return temp;
}

inline  iq12    IQ12mpyI32(const iq12 & y,long x)
{
   iq12 temp;
   temp.val = (y.val * x);
   return temp;
}

inline  iq12    IQ12mpyI32(long y, const iq12 & x)
{
   iq12 temp;
   temp.val = (y * x.val);
   return temp;
}

inline  iq11    IQ11mpyI32(const iq11 & y,long x)
{
   iq11 temp;
   temp.val = (y.val * x);
   return temp;
}

inline  iq11    IQ11mpyI32(long y, const iq11 & x)
{
   iq11 temp;
   temp.val = (y * x.val);
   return temp;
}

inline  iq10    IQ10mpyI32(const iq10 & y,long x)
{
   iq10 temp;
   temp.val = (y.val * x);
   return temp;
}

inline  iq10    IQ10mpyI32(long y, const iq10 & x)
{
   iq10 temp;
   temp.val = (y * x.val);
   return temp;
}

inline  iq9    IQ9mpyI32(const iq9 & y,long x)
{
   iq9 temp;
   temp.val = (y.val * x);
   return temp;
}

inline  iq9    IQ9mpyI32(long y, const iq9 & x)
{
   iq9 temp;
   temp.val = (y * x.val);
   return temp;
}

inline  iq8    IQ8mpyI32(const iq8 & y,long x)
{
   iq8 temp;
   temp.val = (y.val * x);
   return temp;
}

inline  iq8    IQ8mpyI32(long y, const iq8 & x)
{
   iq8 temp;
   temp.val = (y * x.val);
   return temp;
}

inline  iq7    IQ7mpyI32(const iq7 & y,long x)
{
   iq7 temp;
   temp.val = (y.val * x);
   return temp;
}

inline  iq7    IQ7mpyI32(long y, const iq7 & x)
{
   iq7 temp;
   temp.val = (y * x.val);
   return temp;
}

inline  iq6    IQ6mpyI32(const iq6 & y,long x)
{
   iq6 temp;
   temp.val = (y.val * x);
   return temp;
}

inline  iq6    IQ6mpyI32(long y, const iq6 & x)
{
   iq6 temp;
   temp.val = (y * x.val);
   return temp;
}

inline  iq5    IQ5mpyI32(const iq5 & y,long x)
{
   iq5 temp;
   temp.val = (y.val * x);
   return temp;
}

inline  iq5    IQ5mpyI32(long y, const iq5 & x)
{
   iq5 temp;
   temp.val = (y * x.val);
   return temp;
}

inline  iq4    IQ4mpyI32(const iq4 & y,long x)
{
   iq4 temp;
   temp.val = (y.val * x);
   return temp;
}

inline  iq4    IQ4mpyI32(long y, const iq4 & x)
{
   iq4 temp;
   temp.val = (y * x.val);
   return temp;
}

inline  iq3    IQ3mpyI32(const iq3 & y,long x)
{
   iq3 temp;
   temp.val = (y.val * x);
   return temp;
}

inline  iq3    IQ3mpyI32(long y, const iq3 & x)
{
   iq3 temp;
   temp.val = (y * x.val);
   return temp;
}

inline  iq2    IQ2mpyI32(const iq2 & y,long x)
{
   iq2 temp;
   temp.val = (y.val * x);
   return temp;
}

inline  iq2    IQ2mpyI32(long y, const iq2 & x)
{
   iq2 temp;
   temp.val = (y * x.val);
   return temp;
}

inline  iq1    IQ1mpyI32(const iq1 & y,long x)
{
   iq1 temp;
   temp.val = (y.val * x);
   return temp;
}

inline  iq1    IQ1mpyI32(long y, const iq1 & x)
{
   iq1 temp;
   temp.val = (y * x.val);
   return temp;
}

//---------------------------------------------------------------------------
// Functions: IQmpyI32int(A,B), IQNmpyI32int(A,B)
//---------------------------------------------------------------------------

inline  long    IQmpyI32int(const iq & y,long x)      { return _IQmpyI32int(y.val, x); }
inline  long    IQmpyI32int(long y, const iq & x)     { return _IQmpyI32int(y, x.val); }
inline  long    IQ30mpyI32int(const iq30 & y,long x)  { return _IQ30mpyI32int(y.val, x); }
inline  long    IQ30mpyI32int(long y, const iq30 & x) { return _IQ30mpyI32int(y, x.val); }
inline  long    IQ29mpyI32int(const iq29 & y,long x)  { return _IQ29mpyI32int(y.val, x); }
inline  long    IQ29mpyI32int(long y, const iq29 & x) { return _IQ29mpyI32int(y, x.val); }
inline  long    IQ28mpyI32int(const iq28 & y,long x)  { return _IQ28mpyI32int(y.val, x); }
inline  long    IQ28mpyI32int(long y, const iq28 & x) { return _IQ28mpyI32int(y, x.val); }
inline  long    IQ27mpyI32int(const iq27 & y,long x)  { return _IQ27mpyI32int(y.val, x); }
inline  long    IQ27mpyI32int(long y, const iq27 & x) { return _IQ27mpyI32int(y, x.val); }
inline  long    IQ26mpyI32int(const iq26 & y,long x)  { return _IQ26mpyI32int(y.val, x); }
inline  long    IQ26mpyI32int(long y, const iq26 & x) { return _IQ26mpyI32int(y, x.val); }
inline  long    IQ25mpyI32int(const iq25 & y,long x)  { return _IQ25mpyI32int(y.val, x); }
inline  long    IQ25mpyI32int(long y, const iq25 & x) { return _IQ25mpyI32int(y, x.val); }
inline  long    IQ24mpyI32int(const iq24 & y,long x)  { return _IQ24mpyI32int(y.val, x); }
inline  long    IQ24mpyI32int(long y, const iq24 & x) { return _IQ24mpyI32int(y, x.val); }
inline  long    IQ23mpyI32int(const iq23 & y,long x)  { return _IQ23mpyI32int(y.val, x); }
inline  long    IQ23mpyI32int(long y, const iq23 & x) { return _IQ23mpyI32int(y, x.val); }
inline  long    IQ22mpyI32int(const iq22 & y,long x)  { return _IQ22mpyI32int(y.val, x); }
inline  long    IQ22mpyI32int(long y, const iq22 & x) { return _IQ22mpyI32int(y, x.val); }
inline  long    IQ21mpyI32int(const iq21 & y,long x)  { return _IQ21mpyI32int(y.val, x); }
inline  long    IQ21mpyI32int(long y, const iq21 & x) { return _IQ21mpyI32int(y, x.val); }
inline  long    IQ20mpyI32int(const iq20 & y,long x)  { return _IQ20mpyI32int(y.val, x); }
inline  long    IQ20mpyI32int(long y, const iq20 & x) { return _IQ20mpyI32int(y, x.val); }
inline  long    IQ19mpyI32int(const iq19 & y,long x)  { return _IQ19mpyI32int(y.val, x); }
inline  long    IQ19mpyI32int(long y, const iq19 & x) { return _IQ19mpyI32int(y, x.val); }
inline  long    IQ18mpyI32int(const iq18 & y,long x)  { return _IQ18mpyI32int(y.val, x); }
inline  long    IQ18mpyI32int(long y, const iq18 & x) { return _IQ18mpyI32int(y, x.val); }
inline  long    IQ17mpyI32int(const iq17 & y,long x)  { return _IQ17mpyI32int(y.val, x); }
inline  long    IQ17mpyI32int(long y, const iq17 & x) { return _IQ17mpyI32int(y, x.val); }
inline  long    IQ16mpyI32int(const iq16 & y,long x)  { return _IQ16mpyI32int(y.val, x); }
inline  long    IQ16mpyI32int(long y, const iq16 & x) { return _IQ16mpyI32int(y, x.val); }
inline  long    IQ15mpyI32int(const iq15 & y,long x)  { return _IQ15mpyI32int(y.val, x); }
inline  long    IQ15mpyI32int(long y, const iq15 & x) { return _IQ15mpyI32int(y, x.val); }
inline  long    IQ14mpyI32int(const iq14 & y,long x)  { return _IQ14mpyI32int(y.val, x); }
inline  long    IQ14mpyI32int(long y, const iq14 & x) { return _IQ14mpyI32int(y, x.val); }
inline  long    IQ13mpyI32int(const iq13 & y,long x)  { return _IQ13mpyI32int(y.val, x); }
inline  long    IQ13mpyI32int(long y, const iq13 & x) { return _IQ13mpyI32int(y, x.val); }
inline  long    IQ12mpyI32int(const iq12 & y,long x)  { return _IQ12mpyI32int(y.val, x); }
inline  long    IQ12mpyI32int(long y, const iq12 & x) { return _IQ12mpyI32int(y, x.val); }
inline  long    IQ11mpyI32int(const iq11 & y,long x)  { return _IQ11mpyI32int(y.val, x); }
inline  long    IQ11mpyI32int(long y, const iq11 & x) { return _IQ11mpyI32int(y, x.val); }
inline  long    IQ10mpyI32int(const iq10 & y,long x)  { return _IQ10mpyI32int(y.val, x); }
inline  long    IQ10mpyI32int(long y, const iq10 & x) { return _IQ10mpyI32int(y, x.val); }
inline  long    IQ9mpyI32int(const iq9 & y,long x)    { return _IQ9mpyI32int(y.val, x);  }
inline  long    IQ9mpyI32int(long y, const iq9 & x)   { return _IQ9mpyI32int(y, x.val);  }
inline  long    IQ8mpyI32int(const iq8 & y,long x)    { return _IQ8mpyI32int(y.val, x);  }
inline  long    IQ8mpyI32int(long y, const iq8 & x)   { return _IQ8mpyI32int(y, x.val);  }
inline  long    IQ7mpyI32int(const iq7 & y,long x)    { return _IQ7mpyI32int(y.val, x);  }
inline  long    IQ7mpyI32int(long y, const iq7 & x)   { return _IQ7mpyI32int(y, x.val);  }
inline  long    IQ6mpyI32int(const iq6 & y,long x)    { return _IQ6mpyI32int(y.val, x);  }
inline  long    IQ6mpyI32int(long y, const iq6 & x)   { return _IQ6mpyI32int(y, x.val);  }
inline  long    IQ5mpyI32int(const iq5 & y,long x)    { return _IQ5mpyI32int(y.val, x);  }
inline  long    IQ5mpyI32int(long y, const iq5 & x)   { return _IQ5mpyI32int(y, x.val);  }
inline  long    IQ4mpyI32int(const iq4 & y, long x)   { return _IQ4mpyI32int(y.val, x);  }
inline  long    IQ4mpyI32int(long y, const iq4 & x)   { return _IQ4mpyI32int(y, x.val);  }
inline  long    IQ3mpyI32int(const iq3 & y,long x)    { return _IQ3mpyI32int(y.val, x);  }
inline  long    IQ3mpyI32int(long y, const iq3 & x)   { return _IQ3mpyI32int(y, x.val);  }
inline  long    IQ2mpyI32int(const iq2 & y,long & x)  { return _IQ2mpyI32int(y.val, x);  }
inline  long    IQ2mpyI32int(long y, const iq2 & x)   { return _IQ2mpyI32int(y, x.val);  }
inline  long    IQ1mpyI32int(const iq1 & y,long x)    { return _IQ1mpyI32int(y.val, x);  }
inline  long    IQ1mpyI32int(long y, const iq1 & x)   { return _IQ1mpyI32int(y, x.val);  }

//---------------------------------------------------------------------------
// Functions: IQmpyI32frac(A,B), IQNmpyI32frac(A,B)
//---------------------------------------------------------------------------

inline  iq  IQmpyI32frac(const iq & y, long x)
{
   iq temp;
   temp.val = _IQmpyI32frac(y.val, x);
   return temp;
}

inline  iq  IQmpyI32frac(long y, const iq & x)
{
   iq temp;
   temp.val = _IQmpyI32frac(y, x.val);
   return temp;
}

inline  iq30    IQ30mpyI32frac(const iq30 & y, long x)
{
   iq30 temp;
   temp.val = _IQ30mpyI32frac(y.val, x);
   return temp;
}

inline  iq30    IQ30mpyI32frac(long y, const iq30 & x)
{
   iq30 temp;
   temp.val = _IQ30mpyI32frac(y, x.val);
   return temp;
}

inline  iq29    IQ29mpyI32frac(const iq29 & y, long x)
{
   iq29 temp;
   temp.val = _IQ29mpyI32frac(y.val, x);
   return temp;
}

inline  iq29    IQ29mpyI32frac(long y, const iq29 & x)
{
   iq29 temp;
   temp.val = _IQ29mpyI32frac(y, x.val);
   return temp;
}

inline  iq28    IQ28mpyI32frac(const iq28 & y, long x)
{
   iq28 temp;
   temp.val = _IQ28mpyI32frac(y.val, x);
   return temp;
}

inline  iq28    IQ28mpyI32frac(long y, const iq28 & x)
{
   iq28 temp;
   temp.val = _IQ28mpyI32frac(y, x.val);
   return temp;
}

inline  iq27    IQ27mpyI32frac(const iq27 & y, long x)
{
   iq27 temp;
   temp.val = _IQ27mpyI32frac(y.val, x);
   return temp;
}

inline  iq27    IQ27mpyI32frac(long y, const iq27 & x)
{
   iq27 temp;
   temp.val = _IQ27mpyI32frac(y, x.val);
   return temp;
}

inline  iq26    IQ26mpyI32frac(const iq26 & y, long x)
{
   iq26 temp;
   temp.val = _IQ26mpyI32frac(y.val, x);
   return temp;
}

inline  iq26    IQ26mpyI32frac(long y, const iq26 & x)
{
   iq26 temp;
   temp.val = _IQ26mpyI32frac(y, x.val);
   return temp;
}

inline  iq25    IQ25mpyI32frac(const iq25 & y, long x)
{
   iq25 temp;
   temp.val = _IQ25mpyI32frac(y.val, x);
   return temp;
}

inline  iq25    IQ25mpyI32frac(long y, const iq25 & x)
{
   iq25 temp;
   temp.val = _IQ25mpyI32frac(y, x.val);
   return temp;
}

inline  iq24    IQ24mpyI32frac(const iq24 & y, long x)
{
   iq24 temp;
   temp.val = _IQ24mpyI32frac(y.val, x);
   return temp;
}

inline  iq24    IQ24mpyI32frac(long y, const iq24 & x)
{
   iq24 temp;
   temp.val = _IQ24mpyI32frac(y, x.val);
   return temp;
}

inline  iq23    IQ23mpyI32frac(const iq23 & y, long x)
{
   iq23 temp;
   temp.val = _IQ23mpyI32frac(y.val, x);
   return temp;
}

inline  iq23    IQ23mpyI32frac(long y, const iq23 & x)
{
   iq23 temp;
   temp.val = _IQ23mpyI32frac(y, x.val);
   return temp;
}

inline  iq22    IQ22mpyI32frac(const iq22 & y, long x)
{
   iq22 temp;
   temp.val = _IQ22mpyI32frac(y.val, x);
   return temp;
}

inline  iq22    IQ22mpyI32frac(long y, const iq22 & x)
{
   iq22 temp;
   temp.val = _IQ22mpyI32frac(y, x.val);
   return temp;
}

inline  iq21    IQ21mpyI32frac(const iq21 & y, long x)
{
   iq21 temp;
   temp.val = _IQ21mpyI32frac(y.val, x);
   return temp;
}

inline  iq21    IQ21mpyI32frac(long y, const iq21 & x)
{
   iq21 temp;
   temp.val = _IQ21mpyI32frac(y, x.val);
   return temp;
}

inline  iq20    IQ20mpyI32frac(const iq20 & y, long x)
{
   iq20 temp;
   temp.val = _IQ20mpyI32frac(y.val, x);
   return temp;
}

inline  iq20    IQ20mpyI32frac(long y, const iq20 & x)
{
   iq20 temp;
   temp.val = _IQ20mpyI32frac(y, x.val);
   return temp;
}

inline  iq19    IQ19mpyI32frac(const iq19 & y, long x)
{
   iq19 temp;
   temp.val = _IQ19mpyI32frac(y.val, x);
   return temp;
}

inline  iq19    IQ19mpyI32frac(long y, const iq19 & x)
{
   iq19 temp;
   temp.val = _IQ19mpyI32frac(y, x.val);
   return temp;
}

inline  iq18    IQ18mpyI32frac(const iq18 & y, long x)
{
   iq18 temp;
   temp.val = _IQ18mpyI32frac(y.val, x);
   return temp;
}

inline  iq18    IQ18mpyI32frac(long y, const iq18 & x)
{
   iq18 temp;
   temp.val = _IQ18mpyI32frac(y, x.val);
   return temp;
}

inline  iq17    IQ17mpyI32frac(const iq17 & y, long x)
{
   iq17 temp;
   temp.val = _IQ17mpyI32frac(y.val, x);
   return temp;
}

inline  iq17    IQ17mpyI32frac(long y, const iq17 & x)
{
   iq17 temp;
   temp.val = _IQ17mpyI32frac(y, x.val);
   return temp;
}

inline  iq16    IQ16mpyI32frac(const iq16 & y, long x)
{
   iq16 temp;
   temp.val = _IQ16mpyI32frac(y.val, x);
   return temp;
}

inline  iq16    IQ16mpyI32frac(long y, const iq16 & x)
{
   iq16 temp;
   temp.val = _IQ16mpyI32frac(y, x.val);
   return temp;
}

inline  iq15    IQ15mpyI32frac(const iq15 & y, long x)
{
   iq15 temp;
   temp.val = _IQ15mpyI32frac(y.val, x);
   return temp;
}

inline  iq15    IQ15mpyI32frac(long y, const iq15 & x)
{
   iq15 temp;
   temp.val = _IQ15mpyI32frac(y, x.val);
   return temp;
}

inline  iq14    IQ14mpyI32frac(const iq14 & y, long x)
{
   iq14 temp;
   temp.val = _IQ14mpyI32frac(y.val, x);
   return temp;
}

inline  iq14    IQ14mpyI32frac(long y, const iq14 & x)
{
   iq14 temp;
   temp.val = _IQ14mpyI32frac(y, x.val);
   return temp;
}

inline  iq13    IQ13mpyI32frac(const iq13 & y, long x)
{
   iq13 temp;
   temp.val = _IQ13mpyI32frac(y.val, x);
   return temp;
}

inline  iq13    IQ13mpyI32frac(long y, const iq13 & x)
{
   iq13 temp;
   temp.val = _IQ13mpyI32frac(y, x.val);
   return temp;
}

inline  iq12    IQ12mpyI32frac(const iq12 & y, long x)
{
   iq12 temp;
   temp.val = _IQ12mpyI32frac(y.val, x);
   return temp;
}

inline  iq12    IQ12mpyI32frac(long y, const iq12 & x)
{
   iq12 temp;
   temp.val = _IQ12mpyI32frac(y, x.val);
   return temp;
}

inline  iq11    IQ11mpyI32frac(const iq11 & y, long x)
{
   iq11 temp;
   temp.val = _IQ11mpyI32frac(y.val, x);
   return temp;
}

inline  iq11    IQ11mpyI32frac(long y, const iq11 & x)
{
   iq11 temp;
   temp.val = _IQ11mpyI32frac(y, x.val);
   return temp;
}

inline  iq10    IQ10mpyI32frac(const iq10 & y, long x)
{
   iq10 temp;
   temp.val = _IQ10mpyI32frac(y.val, x);
   return temp;
}

inline  iq10    IQ10mpyI32frac(long y, const iq10 & x)
{
   iq10 temp;
   temp.val = _IQ10mpyI32frac(y, x.val);
   return temp;
}

inline  iq9    IQ9mpyI32frac(const iq9 & y, long x)
{
   iq9 temp;
   temp.val = _IQ9mpyI32frac(y.val, x);
   return temp;
}

inline  iq9    IQ9mpyI32frac(long y, const iq9 & x)
{
   iq9 temp;
   temp.val = _IQ9mpyI32frac(y, x.val);
   return temp;
}

inline  iq8    IQ8mpyI32frac(const iq8 & y, long x)
{
   iq8 temp;
   temp.val = _IQ8mpyI32frac(y.val, x);
   return temp;
}

inline  iq8    IQ8mpyI32frac(long y, const iq8 & x)
{
   iq8 temp;
   temp.val = _IQ8mpyI32frac(y, x.val);
   return temp;
}

inline  iq7    IQ7mpyI32frac(const iq7 & y, long x)
{
   iq7 temp;
   temp.val = _IQ7mpyI32frac(y.val, x);
   return temp;
}

inline  iq7    IQ7mpyI32frac(long y, const iq7 & x)
{
   iq7 temp;
   temp.val = _IQ7mpyI32frac(y, x.val);
   return temp;
}

inline  iq6    IQ6mpyI32frac(const iq6 & y, long x)
{
   iq6 temp;
   temp.val = _IQ6mpyI32frac(y.val, x);
   return temp;
}

inline  iq6    IQ6mpyI32frac(long y, const iq6 & x)
{
   iq6 temp;
   temp.val = _IQ6mpyI32frac(y, x.val);
   return temp;
}

inline  iq5    IQ5mpyI32frac(const iq5 & y, long x)
{
   iq5 temp;
   temp.val = _IQ5mpyI32frac(y.val, x);
   return temp;
}

inline  iq5    IQ5mpyI32frac(long y, const iq5 & x)
{
   iq5 temp;
   temp.val = _IQ5mpyI32frac(y, x.val);
   return temp;
}

inline  iq4    IQ4mpyI32frac(const iq4 & y, long x)
{
   iq4 temp;
   temp.val = _IQ4mpyI32frac(y.val, x);
   return temp;
}

inline  iq4    IQ4mpyI32frac(long y, const iq4 & x)
{
   iq4 temp;
   temp.val = _IQ4mpyI32frac(y, x.val);
   return temp;
}

inline  iq3    IQ3mpyI32frac(const iq3 & y, long x)
{
   iq3 temp;
   temp.val = _IQ3mpyI32frac(y.val, x);
   return temp;
}

inline  iq3    IQ3mpyI32frac(long y, const iq3 & x)
{
   iq3 temp;
   temp.val = _IQ3mpyI32frac(y, x.val);
   return temp;
}

inline  iq2    IQ2mpyI32frac(const iq2 & y, long x)
{
   iq2 temp;
   temp.val = _IQ2mpyI32frac(y.val, x);
   return temp;
}

inline  iq2    IQ2mpyI32frac(long y, const iq2 & x)
{
   iq2 temp;
   temp.val = _IQ2mpyI32frac(y, x.val);
   return temp;
}


inline  iq1    IQ1mpyI32frac(const iq1 & y, long x)
{
   iq1 temp;
   temp.val = _IQ1mpyI32frac(y.val, x);
   return temp;
}

inline  iq1    IQ1mpyI32frac(long y, const iq1 & x)
{
   iq1 temp;
   temp.val = _IQ1mpyI32frac(y, x.val);
   return temp;
}

//---------------------------------------------------------------------------
// Functions: IQsin(A), IQNsin(A)
//---------------------------------------------------------------------------

inline  iq  IQsin(const iq & x)
{
   iq temp;
   temp.val = _IQsin(x.val);
   return temp;
}

inline  iq30    IQ30sin(const iq30 & x)
{
   iq30 temp;
   temp.val = _IQ30sin(x.val);
   return temp;
}

inline  iq29    IQ29sin(const iq29 & x)
{
   iq29 temp;
   temp.val = _IQ29sin(x.val);
   return temp;
}

inline  iq28    IQ28sin(const iq28 & x)
{
   iq28 temp;
   temp.val = _IQ28sin(x.val);
   return temp;
}

inline  iq27    IQ27sin(const iq27 & x)
{
   iq27 temp;
   temp.val = _IQ27sin(x.val);
   return temp;
}

inline  iq26    IQ26sin(const iq26 & x)
{
   iq26 temp;
   temp.val = _IQ26sin(x.val);
   return temp;
}

inline  iq25    IQ25sin(const iq25 & x)
{
   iq25 temp;
   temp.val = _IQ25sin(x.val);
   return temp;
}

inline  iq24    IQ24sin(const iq24 & x)
{
   iq24 temp;
   temp.val = _IQ24sin(x.val);
   return temp;
}

inline  iq23    IQ23sin(const iq23 & x)
{
   iq23 temp;
   temp.val = _IQ23sin(x.val);
   return temp;
}

inline  iq22    IQ22sin(const iq22 & x)
{
   iq22 temp;
   temp.val = _IQ22sin(x.val);
   return temp;
}

inline  iq21    IQ21sin(const iq21 & x)
{
   iq21 temp;
   temp.val = _IQ21sin(x.val);
   return temp;
}

inline  iq20    IQ20sin(const iq20 & x)
{
   iq20 temp;
   temp.val = _IQ20sin(x.val);
   return temp;
}

inline  iq19    IQ19sin(const iq19 & x)
{
   iq19 temp;
   temp.val = _IQ19sin(x.val);
   return temp;
}

inline  iq18    IQ18sin(const iq18 & x)
{
   iq18 temp;
   temp.val = _IQ18sin(x.val);
   return temp;
}

inline  iq17    IQ17sin(const iq17 & x)
{
   iq17 temp;
   temp.val = _IQ17sin(x.val);
   return temp;
}

inline  iq16    IQ16sin(const iq16 & x)
{
   iq16 temp;
   temp.val = _IQ16sin(x.val);
   return temp;
}

inline  iq15    IQ15sin(const iq15 & x)
{
   iq15 temp;
   temp.val = _IQ15sin(x.val);
   return temp;
}

inline  iq14    IQ14sin(const iq14 & x)
{
   iq14 temp;
   temp.val = _IQ14sin(x.val);
   return temp;
}

inline  iq13    IQ13sin(const iq13 & x)
{
   iq13 temp;
   temp.val = _IQ13sin(x.val);
   return temp;
}

inline  iq12    IQ12sin(const iq12 & x)
{
   iq12 temp;
   temp.val = _IQ12sin(x.val);
   return temp;
}

inline  iq11    IQ11sin(const iq11 & x)
{
   iq11 temp;
   temp.val = _IQ11sin(x.val);
   return temp;
}

inline  iq10    IQ10sin(const iq10 & x)
{
   iq10 temp;
   temp.val = _IQ10sin(x.val);
   return temp;
}

inline  iq9    IQ9sin(const iq9 & x)
{
   iq9 temp;
   temp.val = _IQ9sin(x.val);
   return temp;
}

inline  iq8    IQ8sin(const iq8 & x)
{
   iq8 temp;
   temp.val = _IQ8sin(x.val);
   return temp;
}

inline  iq7    IQ7sin(const iq7 & x)
{
   iq7 temp;
   temp.val = _IQ7sin(x.val);
   return temp;
}

inline  iq6    IQ6sin(const iq6 & x)
{
   iq6 temp;
   temp.val = _IQ6sin(x.val);
   return temp;
}

inline  iq5    IQ5sin(const iq5 & x)
{
   iq5 temp;
   temp.val = _IQ5sin(x.val);
   return temp;
}

inline  iq4    IQ4sin(const iq4 & x)
{
   iq4 temp;
   temp.val = _IQ4sin(x.val);
   return temp;
}

inline  iq3    IQ3sin(const iq3 & x)
{
   iq3 temp;
   temp.val = _IQ3sin(x.val);
   return temp;
}

inline  iq2    IQ2sin(const iq2 & x)
{
   iq2 temp;
   temp.val = _IQ2sin(x.val);
   return temp;
}

inline  iq1    IQ1sin(const iq1 & x)
{
   iq1 temp;
   temp.val = _IQ1sin(x.val);
   return temp;
}

//---------------------------------------------------------------------------
// Functions: IQsinPU(A), IQNsinPU(A)
//---------------------------------------------------------------------------

inline  iq  IQsinPU(const iq & x)
{
   iq temp;
   temp.val = _IQsinPU(x.val);
   return temp;
}

inline  iq30    IQ30sinPU(const iq30 & x)
{
   iq30 temp;
   temp.val = _IQ30sinPU(x.val);
   return temp;
}

inline  iq29    IQ29sinPU(const iq29 & x)
{
   iq29 temp;
   temp.val = _IQ29sinPU(x.val);
   return temp;
}

inline  iq28    IQ28sinPU(const iq28 & x)
{
   iq28 temp;
   temp.val = _IQ28sinPU(x.val);
   return temp;
}

inline  iq27    IQ27sinPU(const iq27 & x)
{
   iq27 temp;
   temp.val = _IQ27sinPU(x.val);
   return temp;
}

inline  iq26    IQ26sinPU(const iq26 & x)
{
   iq26 temp;
   temp.val = _IQ26sinPU(x.val);
   return temp;
}

inline  iq25    IQ25sinPU(const iq25 & x)
{
   iq25 temp;
   temp.val = _IQ25sinPU(x.val);
   return temp;
}

inline  iq24    IQ24sinPU(const iq24 & x)
{
   iq24 temp;
   temp.val = _IQ24sinPU(x.val);
   return temp;
}

inline  iq23    IQ23sinPU(const iq23 & x)
{
   iq23 temp;
   temp.val = _IQ23sinPU(x.val);
   return temp;
}

inline  iq22    IQ22sinPU(const iq22 & x)
{
   iq22 temp;
   temp.val = _IQ22sinPU(x.val);
   return temp;
}

inline  iq21    IQ21sinPU(const iq21 & x)
{
   iq21 temp;
   temp.val = _IQ21sinPU(x.val);
   return temp;
}

inline  iq20    IQ20sinPU(const iq20 & x)
{
   iq20 temp;
   temp.val = _IQ20sinPU(x.val);
   return temp;
}

inline  iq19    IQ19sinPU(const iq19 & x)
{
   iq19 temp;
   temp.val = _IQ19sinPU(x.val);
   return temp;
}

inline  iq18    IQ18sinPU(const iq18 & x)
{
   iq18 temp;
   temp.val = _IQ18sinPU(x.val);
   return temp;
}

inline  iq17    IQ17sinPU(const iq17 & x)
{
   iq17 temp;
   temp.val = _IQ17sinPU(x.val);
   return temp;
}

inline  iq16    IQ16sinPU(const iq16 & x)
{
   iq16 temp;
   temp.val = _IQ16sinPU(x.val);
   return temp;
}

inline  iq15    IQ15sinPU(const iq15 & x)
{
   iq15 temp;
   temp.val = _IQ15sinPU(x.val);
   return temp;
}

inline  iq14    IQ14sinPU(const iq14 & x)
{
   iq14 temp;
   temp.val = _IQ14sinPU(x.val);
   return temp;
}

inline  iq13    IQ13sinPU(const iq13 & x)
{
   iq13 temp;
   temp.val = _IQ13sinPU(x.val);
   return temp;
}

inline  iq12    IQ12sinPU(const iq12 & x)
{
   iq12 temp;
   temp.val = _IQ12sinPU(x.val);
   return temp;
}

inline  iq11    IQ11sinPU(const iq11 & x)
{
   iq11 temp;
   temp.val = _IQ11sinPU(x.val);
   return temp;
}

inline  iq10    IQ10sinPU(const iq10 & x)
{
   iq10 temp;
   temp.val = _IQ10sinPU(x.val);
   return temp;
}

inline  iq9    IQ9sinPU(const iq9 & x)
{
   iq9 temp;
   temp.val = _IQ9sinPU(x.val);
   return temp;
}

inline  iq8    IQ8sinPU(const iq8 & x)
{
   iq8 temp;
   temp.val = _IQ8sinPU(x.val);
   return temp;
}

inline  iq7    IQ7sinPU(const iq7 & x)
{
   iq7 temp;
   temp.val = _IQ7sinPU(x.val);
   return temp;
}

inline  iq6    IQ6sinPU(const iq6 & x)
{
   iq6 temp;
   temp.val = _IQ6sinPU(x.val);
   return temp;
}

inline  iq5    IQ5sinPU(const iq5 & x)
{
   iq5 temp;
   temp.val = _IQ5sinPU(x.val);
   return temp;
}

inline  iq4    IQ4sinPU(const iq4 & x)
{
   iq4 temp;
   temp.val = _IQ4sinPU(x.val);
   return temp;
}

inline  iq3    IQ3sinPU(const iq3 & x)
{
   iq3 temp;
   temp.val = _IQ3sinPU(x.val);
   return temp;
}

inline  iq2    IQ2sinPU(const iq2 & x)
{
   iq2 temp;
   temp.val = _IQ2sinPU(x.val);
   return temp;
}

inline  iq1    IQ1sinPU(const iq1 & x)
{
   iq1 temp;
   temp.val = _IQ1sinPU(x.val);
   return temp;
}

//---------------------------------------------------------------------------
// Functions: IQasin(A), IQNasin(A)
//---------------------------------------------------------------------------

inline  iq  IQasin(const iq & x)
{
   iq temp;
   temp.val = _IQasin(x.val);
   return temp;
}

inline  iq29    IQ29asin(const iq29 & x)
{
   iq29 temp;
   temp.val = _IQ29asin(x.val);
   return temp;
}

inline  iq28    IQ28asin(const iq28 & x)
{
   iq28 temp;
   temp.val = _IQ28asin(x.val);
   return temp;
}

inline  iq27    IQ27asin(const iq27 & x)
{
   iq27 temp;
   temp.val = _IQ27asin(x.val);
   return temp;
}

inline  iq26    IQ26asin(const iq26 & x)
{
   iq26 temp;
   temp.val = _IQ26asin(x.val);
   return temp;
}

inline  iq25    IQ25asin(const iq25 & x)
{
   iq25 temp;
   temp.val = _IQ25asin(x.val);
   return temp;
}

inline  iq24    IQ24asin(const iq24 & x)
{
   iq24 temp;
   temp.val = _IQ24asin(x.val);
   return temp;
}

inline  iq23    IQ23asin(const iq23 & x)
{
   iq23 temp;
   temp.val = _IQ23asin(x.val);
   return temp;
}

inline  iq22    IQ22asin(const iq22 & x)
{
   iq22 temp;
   temp.val = _IQ22asin(x.val);
   return temp;
}

inline  iq21    IQ21asin(const iq21 & x)
{
   iq21 temp;
   temp.val = _IQ21asin(x.val);
   return temp;
}

inline  iq20    IQ20asin(const iq20 & x)
{
   iq20 temp;
   temp.val = _IQ20asin(x.val);
   return temp;
}

inline  iq19    IQ19asin(const iq19 & x)
{
   iq19 temp;
   temp.val = _IQ19asin(x.val);
   return temp;
}

inline  iq18    IQ18asin(const iq18 & x)
{
   iq18 temp;
   temp.val = _IQ18asin(x.val);
   return temp;
}

inline  iq17    IQ17asin(const iq17 & x)
{
   iq17 temp;
   temp.val = _IQ17asin(x.val);
   return temp;
}

inline  iq16    IQ16asin(const iq16 & x)
{
   iq16 temp;
   temp.val = _IQ16asin(x.val);
   return temp;
}

inline  iq15    IQ15asin(const iq15 & x)
{
   iq15 temp;
   temp.val = _IQ15asin(x.val);
   return temp;
}

inline  iq14    IQ14asin(const iq14 & x)
{
   iq14 temp;
   temp.val = _IQ14asin(x.val);
   return temp;
}

inline  iq13    IQ13asin(const iq13 & x)
{
   iq13 temp;
   temp.val = _IQ13asin(x.val);
   return temp;
}

inline  iq12    IQ12asin(const iq12 & x)
{
   iq12 temp;
   temp.val = _IQ12asin(x.val);
   return temp;
}

inline  iq11    IQ11asin(const iq11 & x)
{
   iq11 temp;
   temp.val = _IQ11asin(x.val);
   return temp;
}

inline  iq10    IQ10asin(const iq10 & x)
{
   iq10 temp;
   temp.val = _IQ10asin(x.val);
   return temp;
}

inline  iq9    IQ9asin(const iq9 & x)
{
   iq9 temp;
   temp.val = _IQ9asin(x.val);
   return temp;
}

inline  iq8    IQ8asin(const iq8 & x)
{
   iq8 temp;
   temp.val = _IQ8asin(x.val);
   return temp;
}

inline  iq7    IQ7asin(const iq7 & x)
{
   iq7 temp;
   temp.val = _IQ7asin(x.val);
   return temp;
}

inline  iq6    IQ6asin(const iq6 & x)
{
   iq6 temp;
   temp.val = _IQ6asin(x.val);
   return temp;
}

inline  iq5    IQ5asin(const iq5 & x)
{
   iq5 temp;
   temp.val = _IQ5asin(x.val);
   return temp;
}

inline  iq4    IQ4asin(const iq4 & x)
{
   iq4 temp;
   temp.val = _IQ4asin(x.val);
   return temp;
}

inline  iq3    IQ3asin(const iq3 & x)
{
   iq3 temp;
   temp.val = _IQ3asin(x.val);
   return temp;
}

inline  iq2    IQ2asin(const iq2 & x)
{
   iq2 temp;
   temp.val = _IQ2asin(x.val);
   return temp;
}

inline  iq1    IQ1asin(const iq1 & x)
{
   iq1 temp;
   temp.val = _IQ1asin(x.val);
   return temp;
}


//---------------------------------------------------------------------------
// Functions: IQcos(A), IQNcos(A)
//---------------------------------------------------------------------------

inline  iq  IQcos(const iq & x)
{
   iq temp;
   temp.val = _IQcos(x.val);
   return temp;
}

inline  iq30    IQ30cos(const iq30 & x)
{
   iq30 temp;
   temp.val = _IQ30cos(x.val);
   return temp;
}

inline  iq29    IQ29cos(const iq29 & x)
{
   iq29 temp;
   temp.val = _IQ29cos(x.val);
   return temp;
}

inline  iq28    IQ28cos(const iq28 & x)
{
   iq28 temp;
   temp.val = _IQ28cos(x.val);
   return temp;
}

inline  iq27    IQ27cos(const iq27 & x)
{
   iq27 temp;
   temp.val = _IQ27cos(x.val);
   return temp;
}

inline  iq26    IQ26cos(const iq26 & x)
{
   iq26 temp;
   temp.val = _IQ26cos(x.val);
   return temp;
}

inline  iq25    IQ25cos(const iq25 & x)
{
   iq25 temp;
   temp.val = _IQ25cos(x.val);
   return temp;
}

inline  iq24    IQ24cos(const iq24 & x)
{
   iq24 temp;
   temp.val = _IQ24cos(x.val);
   return temp;
}

inline  iq23    IQ23cos(const iq23 & x)
{
   iq23 temp;
   temp.val = _IQ23cos(x.val);
   return temp;
}

inline  iq22    IQ22cos(const iq22 & x)
{
   iq22 temp;
   temp.val = _IQ22cos(x.val);
   return temp;
}

inline  iq21    IQ21cos(const iq21 & x)
{
   iq21 temp;
   temp.val = _IQ21cos(x.val);
   return temp;
}

inline  iq20    IQ20cos(const iq20 & x)
{
   iq20 temp;
   temp.val = _IQ20cos(x.val);
   return temp;
}

inline  iq19    IQ19cos(const iq19 & x)
{
   iq19 temp;
   temp.val = _IQ19cos(x.val);
   return temp;
}

inline  iq18    IQ18cos(const iq18 & x)
{
   iq18 temp;
   temp.val = _IQ18cos(x.val);
   return temp;
}

inline  iq17    IQ17cos(const iq17 & x)
{
   iq17 temp;
   temp.val = _IQ17cos(x.val);
   return temp;
}

inline  iq16    IQ16cos(const iq16 & x)
{
   iq16 temp;
   temp.val = _IQ16cos(x.val);
   return temp;
}

inline  iq15    IQ15cos(const iq15 & x)
{
   iq15 temp;
   temp.val = _IQ15cos(x.val);
   return temp;
}

inline  iq14    IQ14cos(const iq14 & x)
{
   iq14 temp;
   temp.val = _IQ14cos(x.val);
   return temp;
}

inline  iq13    IQ13cos(const iq13 & x)
{
   iq13 temp;
   temp.val = _IQ13cos(x.val);
   return temp;
}

inline  iq12    IQ12cos(const iq12 & x)
{
   iq12 temp;
   temp.val = _IQ12cos(x.val);
   return temp;
}

inline  iq11    IQ11cos(const iq11 & x)
{
   iq11 temp;
   temp.val = _IQ11cos(x.val);
   return temp;
}

inline  iq10    IQ10cos(const iq10 & x)
{
   iq10 temp;
   temp.val = _IQ10cos(x.val);
   return temp;
}

inline  iq9    IQ9cos(const iq9 & x)
{
   iq9 temp;
   temp.val = _IQ9cos(x.val);
   return temp;
}

inline  iq8    IQ8cos(const iq8 & x)
{
   iq8 temp;
   temp.val = _IQ8cos(x.val);
   return temp;
}

inline  iq7    IQ7cos(const iq7 & x)
{
   iq7 temp;
   temp.val = _IQ7cos(x.val);
   return temp;
}

inline  iq6    IQ6cos(const iq6 & x)
{
   iq6 temp;
   temp.val = _IQ6cos(x.val);
   return temp;
}

inline  iq5    IQ5cos(const iq5 & x)
{
   iq5 temp;
   temp.val = _IQ5cos(x.val);
   return temp;
}

inline  iq4    IQ4cos(const iq4 & x)
{
   iq4 temp;
   temp.val = _IQ4cos(x.val);
   return temp;
}

inline  iq3    IQ3cos(const iq3 & x)
{
   iq3 temp;
   temp.val = _IQ3cos(x.val);
   return temp;
}

inline  iq2    IQ2cos(const iq2 & x)
{
   iq2 temp;
   temp.val = _IQ2cos(x.val);
   return temp;
}

inline  iq1    IQ1cos(const iq1 & x)
{
   iq1 temp;
   temp.val = _IQ1cos(x.val);
   return temp;
}


//---------------------------------------------------------------------------
// Functions: IQcosPU(A), IQNcosPU(A)
//---------------------------------------------------------------------------

inline  iq  IQcosPU(const iq & x)
{
   iq temp;
   temp.val = _IQcosPU(x.val);
   return temp;
}

inline  iq30    IQ30cosPU(const iq30 & x)
{
   iq30 temp;
   temp.val = _IQ30cosPU(x.val);
   return temp;
}

inline  iq29    IQ29cosPU(const iq29 & x)
{
   iq29 temp;
   temp.val = _IQ29cosPU(x.val);
   return temp;
}

inline  iq28    IQ28cosPU(const iq28 & x)
{
   iq28 temp;
   temp.val = _IQ28cosPU(x.val);
   return temp;
}

inline  iq27    IQ27cosPU(const iq27 & x)
{
   iq27 temp;
   temp.val = _IQ27cosPU(x.val);
   return temp;
}

inline  iq26    IQ26cosPU(const iq26 & x)
{
   iq26 temp;
   temp.val = _IQ26cosPU(x.val);
   return temp;
}

inline  iq25    IQ25cosPU(const iq25 & x)
{
   iq25 temp;
   temp.val = _IQ25cosPU(x.val);
   return temp;
}

inline  iq24    IQ24cosPU(const iq24 & x)
{
   iq24 temp;
   temp.val = _IQ24cosPU(x.val);
   return temp;
}

inline  iq23    IQ23cosPU(const iq23 & x)
{
   iq23 temp;
   temp.val = _IQ23cosPU(x.val);
   return temp;
}

inline  iq22    IQ22cosPU(const iq22 & x)
{
   iq22 temp;
   temp.val = _IQ22cosPU(x.val);
   return temp;
}

inline  iq21    IQ21cosPU(const iq21 & x)
{
   iq21 temp;
   temp.val = _IQ21cosPU(x.val);
   return temp;
}

inline  iq20    IQ20cosPU(const iq20 & x)
{
   iq20 temp;
   temp.val = _IQ20cosPU(x.val);
   return temp;
}

inline  iq19    IQ19cosPU(const iq19 & x)
{
   iq19 temp;
   temp.val = _IQ19cosPU(x.val);
   return temp;
}

inline  iq18    IQ18cosPU(const iq18 & x)
{
   iq18 temp;
   temp.val = _IQ18cosPU(x.val);
   return temp;
}

inline  iq17    IQ17cosPU(const iq17 & x)
{
   iq17 temp;
   temp.val = _IQ17cosPU(x.val);
   return temp;
}

inline  iq16    IQ16cosPU(const iq16 & x)
{
   iq16 temp;
   temp.val = _IQ16cosPU(x.val);
   return temp;
}

inline  iq15    IQ15cosPU(const iq15 & x)
{
   iq15 temp;
   temp.val = _IQ15cosPU(x.val);
   return temp;
}

inline  iq14    IQ14cosPU(const iq14 & x)
{
   iq14 temp;
   temp.val = _IQ14cosPU(x.val);
   return temp;
}

inline  iq13    IQ13cosPU(const iq13 & x)
{
   iq13 temp;
   temp.val = _IQ13cosPU(x.val);
   return temp;
}

inline  iq12    IQ12cosPU(const iq12 & x)
{
   iq12 temp;
   temp.val = _IQ12cosPU(x.val);
   return temp;
}

inline  iq11    IQ11cosPU(const iq11 & x)
{
   iq11 temp;
   temp.val = _IQ11cosPU(x.val);
   return temp;
}

inline  iq10    IQ10cosPU(const iq10 & x)
{
   iq10 temp;
   temp.val = _IQ10cosPU(x.val);
   return temp;
}

inline  iq9    IQ9cosPU(const iq9 & x)
{
   iq9 temp;
   temp.val = _IQ9cosPU(x.val);
   return temp;
}

inline  iq8    IQ8cosPU(const iq8 & x)
{
   iq8 temp;
   temp.val = _IQ8cosPU(x.val);
   return temp;
}

inline  iq7    IQ7cosPU(const iq7 & x)
{
   iq7 temp;
   temp.val = _IQ7cosPU(x.val);
   return temp;
}

inline  iq6    IQ6cosPU(const iq6 & x)
{
   iq6 temp;
   temp.val = _IQ6cosPU(x.val);
   return temp;
}

inline  iq5    IQ5cosPU(const iq5 & x)
{
   iq5 temp;
   temp.val = _IQ5cosPU(x.val);
   return temp;
}

inline  iq4    IQ4cosPU(const iq4 & x)
{
   iq4 temp;
   temp.val = _IQ4cosPU(x.val);
   return temp;
}

inline  iq3    IQ3cosPU(const iq3 & x)
{
   iq3 temp;
   temp.val = _IQ3cosPU(x.val);
   return temp;
}

inline  iq2    IQ2cosPU(const iq2 & x)
{
   iq2 temp;
   temp.val = _IQ2cosPU(x.val);
   return temp;
}

inline  iq1    IQ1cosPU(const iq1 & x)
{
   iq1 temp;
   temp.val = _IQ1cosPU(x.val);
   return temp;
}


//---------------------------------------------------------------------------
// Functions: IQacos(A), IQNacos(A)
//---------------------------------------------------------------------------

inline  iq  IQacos(const iq & x)
{
   iq temp;
   temp.val = _IQacos(x.val);
   return temp;
}

inline  iq29    IQ29acos(const iq29 & x)
{
   iq29 temp;
   temp.val = _IQ29acos(x.val);
   return temp;
}

inline  iq28    IQ28acos(const iq28 & x)
{
   iq28 temp;
   temp.val = _IQ28acos(x.val);
   return temp;
}

inline  iq27    IQ27acos(const iq27 & x)
{
   iq27 temp;
   temp.val = _IQ27acos(x.val);
   return temp;
}

inline  iq26    IQ26acos(const iq26 & x)
{
   iq26 temp;
   temp.val = _IQ26acos(x.val);
   return temp;
}

inline  iq25    IQ25acos(const iq25 & x)
{
   iq25 temp;
   temp.val = _IQ25acos(x.val);
   return temp;
}

inline  iq24    IQ24acos(const iq24 & x)
{
   iq24 temp;
   temp.val = _IQ24acos(x.val);
   return temp;
}

inline  iq23    IQ23acos(const iq23 & x)
{
   iq23 temp;
   temp.val = _IQ23acos(x.val);
   return temp;
}

inline  iq22    IQ22acos(const iq22 & x)
{
   iq22 temp;
   temp.val = _IQ22acos(x.val);
   return temp;
}

inline  iq21    IQ21acos(const iq21 & x)
{
   iq21 temp;
   temp.val = _IQ21acos(x.val);
   return temp;
}

inline  iq20    IQ20acos(const iq20 & x)
{
   iq20 temp;
   temp.val = _IQ20acos(x.val);
   return temp;
}

inline  iq19    IQ19acos(const iq19 & x)
{
   iq19 temp;
   temp.val = _IQ19acos(x.val);
   return temp;
}

inline  iq18    IQ18acos(const iq18 & x)
{
   iq18 temp;
   temp.val = _IQ18acos(x.val);
   return temp;
}

inline  iq17    IQ17acos(const iq17 & x)
{
   iq17 temp;
   temp.val = _IQ17acos(x.val);
   return temp;
}

inline  iq16    IQ16acos(const iq16 & x)
{
   iq16 temp;
   temp.val = _IQ16acos(x.val);
   return temp;
}

inline  iq15    IQ15acos(const iq15 & x)
{
   iq15 temp;
   temp.val = _IQ15acos(x.val);
   return temp;
}

inline  iq14    IQ14acos(const iq14 & x)
{
   iq14 temp;
   temp.val = _IQ14acos(x.val);
   return temp;
}

inline  iq13    IQ13acos(const iq13 & x)
{
   iq13 temp;
   temp.val = _IQ13acos(x.val);
   return temp;
}

inline  iq12    IQ12acos(const iq12 & x)
{
   iq12 temp;
   temp.val = _IQ12acos(x.val);
   return temp;
}

inline  iq11    IQ11acos(const iq11 & x)
{
   iq11 temp;
   temp.val = _IQ11acos(x.val);
   return temp;
}

inline  iq10    IQ10acos(const iq10 & x)
{
   iq10 temp;
   temp.val = _IQ10acos(x.val);
   return temp;
}

inline  iq9    IQ9acos(const iq9 & x)
{
   iq9 temp;
   temp.val = _IQ9acos(x.val);
   return temp;
}

inline  iq8    IQ8acos(const iq8 & x)
{
   iq8 temp;
   temp.val = _IQ8acos(x.val);
   return temp;
}

inline  iq7    IQ7acos(const iq7 & x)
{
   iq7 temp;
   temp.val = _IQ7acos(x.val);
   return temp;
}

inline  iq6    IQ6acos(const iq6 & x)
{
   iq6 temp;
   temp.val = _IQ6acos(x.val);
   return temp;
}

inline  iq5    IQ5acos(const iq5 & x)
{
   iq5 temp;
   temp.val = _IQ5acos(x.val);
   return temp;
}

inline  iq4    IQ4acos(const iq4 & x)
{
   iq4 temp;
   temp.val = _IQ4acos(x.val);
   return temp;
}

inline  iq3    IQ3acos(const iq3 & x)
{
   iq3 temp;
   temp.val = _IQ3acos(x.val);
   return temp;
}

inline  iq2    IQ2acos(const iq2 & x)
{
   iq2 temp;
   temp.val = _IQ2acos(x.val);
   return temp;
}

inline  iq1    IQ1acos(const iq1 & x)
{
   iq1 temp;
   temp.val = _IQ1acos(x.val);
   return temp;
}


//---------------------------------------------------------------------------
// Functions: IQatan2(A,B), IQNatan2(A,B)
//---------------------------------------------------------------------------

inline  iq  IQatan2(const iq & y, iq & x)
{
   iq temp;
   temp.val = _IQatan2(y.val, x.val);
   return temp;
}

inline  iq30    IQ30atan2(const iq30 & y, iq30 & x)
{
   iq30 temp;
   temp.val = _IQ30atan2(y.val, x.val);
   return temp;
}

inline  iq29    IQ29atan2(const iq29 & y, iq29 & x)
{
   iq29 temp;
   temp.val = _IQ29atan2(y.val, x.val);
   return temp;
}

inline  iq28    IQ28atan2(const iq28 & y, iq28 & x)
{
   iq28 temp;
   temp.val = _IQ28atan2(y.val, x.val);
   return temp;
}

inline  iq27    IQ27atan2(const iq27 & y, iq27 & x)
{
   iq27 temp;
   temp.val = _IQ27atan2(y.val, x.val);
   return temp;
}

inline  iq26    IQ26atan2(const iq26 & y, iq26 & x)
{
   iq26 temp;
   temp.val = _IQ26atan2(y.val, x.val);
   return temp;
}

inline  iq25    IQ25atan2(const iq25 & y, iq25 & x)
{
   iq25 temp;
   temp.val = _IQ25atan2(y.val, x.val);
   return temp;
}

inline  iq24    IQ24atan2(const iq24 & y, iq24 & x)
{
   iq24 temp;
   temp.val = _IQ24atan2(y.val, x.val);
   return temp;
}

inline  iq23    IQ23atan2(const iq23 & y, iq23 & x)
{
   iq23 temp;
   temp.val = _IQ23atan2(y.val, x.val);
   return temp;
}

inline  iq22    IQ22atan2(const iq22 & y, iq22 & x)
{
   iq22 temp;
   temp.val = _IQ22atan2(y.val, x.val);
   return temp;
}

inline  iq21    IQ21atan2(const iq21 & y, iq21 & x)
{
   iq21 temp;
   temp.val = _IQ21atan2(y.val, x.val);
   return temp;
}

inline  iq20    IQ20atan2(const iq20 & y, iq20 & x)
{
   iq20 temp;
   temp.val = _IQ20atan2(y.val, x.val);
   return temp;
}

inline  iq19    IQ19atan2(const iq19 & y, iq19 & x)
{
   iq19 temp;
   temp.val = _IQ19atan2(y.val, x.val);
   return temp;
}

inline  iq18    IQ18atan2(const iq18 & y, iq18 & x)
{
   iq18 temp;
   temp.val = _IQ18atan2(y.val, x.val);
   return temp;
}

inline  iq17    IQ17atan2(const iq17 & y, iq17 & x)
{
   iq17 temp;
   temp.val = _IQ17atan2(y.val, x.val);
   return temp;
}

inline  iq16    IQ16atan2(const iq16 & y, iq16 & x)
{
   iq16 temp;
   temp.val = _IQ16atan2(y.val, x.val);
   return temp;
}

inline  iq15    IQ15atan2(const iq15 & y, iq15 & x)
{
   iq15 temp;
   temp.val = _IQ15atan2(y.val, x.val);
   return temp;
}


inline  iq14    IQ14atan2(const iq14 & y, iq14 & x)
{
   iq14 temp;
   temp.val = _IQ14atan2(y.val, x.val);
   return temp;
}

inline  iq13    IQ13atan2(const iq13 & y, iq13 & x)
{
   iq13 temp;
   temp.val = _IQ13atan2(y.val, x.val);
   return temp;
}

inline  iq12    IQ12atan2(const iq12 & y, iq12 & x)
{
   iq12 temp;
   temp.val = _IQ12atan2(y.val, x.val);
   return temp;
}

inline  iq11    IQ11atan2(const iq11 & y, iq11 & x)
{
   iq11 temp;
   temp.val = _IQ11atan2(y.val, x.val);
   return temp;
}

inline  iq10    IQ10atan2(const iq10 & y, iq10 & x)
{
   iq10 temp;
   temp.val = _IQ10atan2(y.val, x.val);
   return temp;
}

inline  iq9    IQ9atan2(const iq9 & y, iq9 & x)
{
   iq9 temp;
   temp.val = _IQ9atan2(y.val, x.val);
   return temp;
}

inline  iq8    IQ8atan2(const iq8 & y, iq8 & x)
{
   iq8 temp;
   temp.val = _IQ8atan2(y.val, x.val);
   return temp;
}

inline  iq7    IQ7atan2(const iq7 & y, iq7 & x)
{
   iq7 temp;
   temp.val = _IQ7atan2(y.val, x.val);
   return temp;
}

inline  iq6    IQ6atan2(const iq6 & y, iq6 & x)
{
   iq6 temp;
   temp.val = _IQ6atan2(y.val, x.val);
   return temp;
}

inline  iq5    IQ5atan2(const iq5 & y, iq5 & x)
{
   iq5 temp;
   temp.val = _IQ5atan2(y.val, x.val);
   return temp;
}

inline  iq4    IQ4atan2(const iq4 & y, iq4 & x)
{
   iq4 temp;
   temp.val = _IQ4atan2(y.val, x.val);
   return temp;
}

inline  iq3    IQ3atan2(const iq3 & y, iq3 & x)
{
   iq3 temp;
   temp.val = _IQ3atan2(y.val, x.val);
   return temp;
}

inline  iq2    IQ2atan2(const iq2 & y, iq2 & x)
{
   iq2 temp;
   temp.val = _IQ2atan2(y.val, x.val);
   return temp;
}

inline  iq1    IQ1atan2(const iq1 & y, iq1 & x)
{
   iq1 temp;
   temp.val = _IQ1atan2(y.val, x.val);
   return temp;
}


//---------------------------------------------------------------------------
// Functions: IQatan2PU(A,B), IQNatan2PU(A,B)
//---------------------------------------------------------------------------

inline  iq  IQatan2PU(const iq & y, const iq & x)
{
   iq temp;
   temp.val = _IQatan2PU(y.val, x.val);
   return temp;
}

inline  iq30    IQ30atan2PU(const iq30 & y, const iq30 & x)
{
   iq30 temp;
   temp.val = _IQ30atan2PU(y.val, x.val);
   return temp;
}

inline  iq29    IQ29atan2PU(const iq29 & y, const iq29 & x)
{
   iq29 temp;
   temp.val = _IQ29atan2PU(y.val, x.val);
   return temp;
}

inline  iq28    IQ28atan2PU(const iq28 & y, const iq28 & x)
{
   iq28 temp;
   temp.val = _IQ28atan2PU(y.val, x.val);
   return temp;
}

inline  iq27    IQ27atan2PU(const iq27 & y, const iq27 & x)
{
   iq27 temp;
   temp.val = _IQ27atan2PU(y.val, x.val);
   return temp;
}

inline  iq26    IQ26atan2PU(const iq26 & y, const iq26 & x)
{
   iq26 temp;
   temp.val = _IQ26atan2PU(y.val, x.val);
   return temp;
}

inline  iq25    IQ25atan2PU(const iq25 & y, const iq25 & x)
{
   iq25 temp;
   temp.val = _IQ25atan2PU(y.val, x.val);
   return temp;
}

inline  iq24    IQ24atan2PU(const iq24 & y, const iq24 & x)
{
   iq24 temp;
   temp.val = _IQ24atan2PU(y.val, x.val);
   return temp;
}

inline  iq23    IQ23atan2PU(const iq23 & y, const iq23 & x)
{
   iq23 temp;
   temp.val = _IQ23atan2PU(y.val, x.val);
   return temp;
}

inline  iq22    IQ22atan2PU(const iq22 & y, const iq22 & x)
{
   iq22 temp;
   temp.val = _IQ22atan2PU(y.val, x.val);
   return temp;
}

inline  iq21    IQ21atan2PU(const iq21 & y, const iq21 & x)
{
   iq21 temp;
   temp.val = _IQ21atan2PU(y.val, x.val);
   return temp;
}

inline  iq20    IQ20atan2PU(const iq20 & y, const iq20 & x)
{
   iq20 temp;
   temp.val = _IQ20atan2PU(y.val, x.val);
   return temp;
}

inline  iq19    IQ19atan2PU(const iq19 & y, const iq19 & x)
{
   iq19 temp;
   temp.val = _IQ19atan2PU(y.val, x.val);
   return temp;
}

inline  iq18    IQ18atan2PU(const iq18 & y, const iq18 & x)
{
   iq18 temp;
   temp.val = _IQ18atan2PU(y.val, x.val);
   return temp;
}

inline  iq17    IQ17atan2PU(const iq17 & y, const iq17 & x)
{
   iq17 temp;
   temp.val = _IQ17atan2PU(y.val, x.val);
   return temp;
}

inline  iq16    IQ16atan2PU(const iq16 & y, const iq16 & x)
{
   iq16 temp;
   temp.val = _IQ16atan2PU(y.val, x.val);
   return temp;
}

inline  iq15    IQ15atan2PU(const iq15 & y, const iq15 & x)
{
   iq15 temp;
   temp.val = _IQ15atan2PU(y.val, x.val);
   return temp;
}

inline  iq14    IQ14atan2PU(const iq14 & y, const iq14 & x)
{
   iq14 temp;
   temp.val = _IQ14atan2PU(y.val, x.val);
   return temp;
}

inline  iq13    IQ13atan2PU(const iq13 & y, const iq13 & x)
{
   iq13 temp;
   temp.val = _IQ13atan2PU(y.val, x.val);
   return temp;
}

inline  iq12    IQ12atan2PU(const iq12 & y, const iq12 & x)
{
   iq12 temp;
   temp.val = _IQ12atan2PU(y.val, x.val);
   return temp;
}

inline  iq11    IQ11atan2PU(const iq11 & y, const iq11 & x)
{
   iq11 temp;
   temp.val = _IQ11atan2PU(y.val, x.val);
   return temp;
}

inline  iq10    IQ10atan2PU(const iq10 & y, const iq10 & x)
{
   iq10 temp;
   temp.val = _IQ10atan2PU(y.val, x.val);
   return temp;
}

inline  iq9    IQ9atan2PU(const iq9 & y, const iq9 & x)
{
   iq9 temp;
   temp.val = _IQ9atan2PU(y.val, x.val);
   return temp;
}

inline  iq8    IQ8atan2PU(const iq8 & y, const iq8 & x)
{
   iq8 temp;
   temp.val = _IQ8atan2PU(y.val, x.val);
   return temp;
}

inline  iq7    IQ7atan2PU(const iq7 & y, const iq7 & x)
{
   iq7 temp;
   temp.val = _IQ7atan2PU(y.val, x.val);
   return temp;
}

inline  iq6    IQ6atan2PU(const iq6 & y, const iq6 & x)
{
   iq6 temp;
   temp.val = _IQ6atan2PU(y.val, x.val);
   return temp;
}

inline  iq5    IQ5atan2PU(const iq5 & y, const iq5 & x)
{
   iq5 temp;
   temp.val = _IQ5atan2PU(y.val, x.val);
   return temp;
}

inline  iq4    IQ4atan2PU(const iq4 & y, const iq4 & x)
{
   iq4 temp;
   temp.val = _IQ4atan2PU(y.val, x.val);
   return temp;
}

inline  iq3    IQ3atan2PU(const iq3 & y, const iq3 & x)
{
   iq3 temp;
   temp.val = _IQ3atan2PU(y.val, x.val);
   return temp;
}

inline  iq2    IQ2atan2PU(const iq2 & y, const iq2 & x)
{
   iq2 temp;
   temp.val = _IQ2atan2PU(y.val, x.val);
   return temp;
}

inline  iq1    IQ1atan2PU(const iq1 & y, const iq1 & x)
{
   iq1 temp;
   temp.val = _IQ1atan2PU(y.val, x.val);
   return temp;
}


//---------------------------------------------------------------------------
// Functions: IQatan(A), IQNatan(A)
//---------------------------------------------------------------------------

#define  IQatan(A)    IQatan2(A,IQ(1.0))
#define  IQ30atan(A)  IQ30atan2(A,IQ30(1.0))
#define  IQ29atan(A)  IQ29atan2(A,IQ29(1.0))
#define  IQ28atan(A)  IQ28atan2(A,IQ28(1.0))
#define  IQ27atan(A)  IQ27atan2(A,IQ27(1.0))
#define  IQ26atan(A)  IQ26atan2(A,IQ26(1.0))
#define  IQ25atan(A)  IQ25atan2(A,IQ25(1.0))
#define  IQ24atan(A)  IQ24atan2(A,IQ24(1.0))
#define  IQ23atan(A)  IQ23atan2(A,IQ23(1.0))
#define  IQ22atan(A)  IQ22atan2(A,IQ22(1.0))
#define  IQ21atan(A)  IQ21atan2(A,IQ21(1.0))
#define  IQ20atan(A)  IQ20atan2(A,IQ20(1.0))
#define  IQ19atan(A)  IQ19atan2(A,IQ19(1.0))
#define  IQ18atan(A)  IQ18atan2(A,IQ18(1.0))
#define  IQ17atan(A)  IQ17atan2(A,IQ17(1.0))
#define  IQ16atan(A)  IQ16atan2(A,IQ16(1.0))
#define  IQ15atan(A)  IQ15atan2(A,IQ15(1.0))
#define  IQ14atan(A)  IQ14atan2(A,IQ14(1.0))
#define  IQ13atan(A)  IQ13atan2(A,IQ13(1.0))
#define  IQ12atan(A)  IQ12atan2(A,IQ12(1.0))
#define  IQ11atan(A)  IQ11atan2(A,IQ11(1.0))
#define  IQ10atan(A)  IQ10atan2(A,IQ10(1.0))
#define  IQ9atan(A)   IQ9atan2(A,IQ9(1.0))
#define  IQ8atan(A)   IQ8atan2(A,IQ8(1.0))
#define  IQ7atan(A)   IQ7atan2(A,IQ7(1.0))
#define  IQ6atan(A)   IQ6atan2(A,IQ6(1.0))
#define  IQ5atan(A)   IQ5atan2(A,IQ5(1.0))
#define  IQ4atan(A)   IQ4atan2(A,IQ4(1.0))
#define  IQ3atan(A)   IQ3atan2(A,IQ3(1.0))
#define  IQ2atan(A)   IQ2atan2(A,IQ2(1.0))
#define  IQ1atan(A)   IQ1atan2(A,IQ1(1.0))

//---------------------------------------------------------------------------
// Functions: IQsqrt(A), IQNsqrt(A)
//---------------------------------------------------------------------------

inline  iq  IQsqrt(const iq & x)
{
   iq temp;
   temp.val = _IQsqrt(x.val);
   return temp;
}

inline  iq30    IQ30sqrt(const iq30 & x)
{
   iq30 temp;
   temp.val = _IQ30sqrt(x.val);
   return temp;
}

inline  iq29    IQ29sqrt(const iq29 & x)
{
   iq29 temp;
   temp.val = _IQ29sqrt(x.val);
   return temp;
}

inline  iq28    IQ28sqrt(const iq28 & x)
{
   iq28 temp;
   temp.val = _IQ28sqrt(x.val);
   return temp;
}

inline  iq27    IQ27sqrt(const iq27 & x)
{
   iq27 temp;
   temp.val = _IQ27sqrt(x.val);
   return temp;
}

inline  iq26    IQ26sqrt(const iq26 & x)
{
   iq26 temp;
   temp.val = _IQ26sqrt(x.val);
   return temp;
}

inline  iq25    IQ25sqrt(const iq25 & x)
{
   iq25 temp;
   temp.val = _IQ25sqrt(x.val);
   return temp;
}

inline  iq24    IQ24sqrt(const iq24 & x)
{
   iq24 temp;
   temp.val = _IQ24sqrt(x.val);
   return temp;
}

inline  iq23    IQ23sqrt(const iq23 & x)
{
   iq23 temp;
   temp.val = _IQ23sqrt(x.val);
   return temp;
}

inline  iq22    IQ22sqrt(const iq22 & x)
{
   iq22 temp;
   temp.val = _IQ22sqrt(x.val);
   return temp;
}

inline  iq21    IQ21sqrt(const iq21 & x)
{
   iq21 temp;
   temp.val = _IQ21sqrt(x.val);
   return temp;
}

inline  iq20    IQ20sqrt(const iq20 & x)
{
   iq20 temp;
   temp.val = _IQ20sqrt(x.val);
   return temp;
}

inline  iq19    IQ19sqrt(const iq19 & x)
{
   iq19 temp;
   temp.val = _IQ19sqrt(x.val);
   return temp;
}

inline  iq18    IQ18sqrt(const iq18 & x)
{
   iq18 temp;
   temp.val = _IQ18sqrt(x.val);
   return temp;
}

inline  iq17    IQ17sqrt(const iq17 & x)
{
   iq17 temp;
   temp.val = _IQ17sqrt(x.val);
   return temp;
}

inline  iq16    IQ16sqrt(const iq16 & x)
{
   iq16 temp;
   temp.val = _IQ16sqrt(x.val);
   return temp;
}

inline  iq15    IQ15sqrt(const iq15 & x)
{
   iq15 temp;
   temp.val = _IQ15sqrt(x.val);
   return temp;
}

inline  iq14    IQ14sqrt(const iq14 & x)
{
   iq14 temp;
   temp.val = _IQ14sqrt(x.val);
   return temp;
}

inline  iq13    IQ13sqrt(const iq13 & x)
{
   iq13 temp;
   temp.val = _IQ13sqrt(x.val);
   return temp;
}

inline  iq12    IQ12sqrt(const iq12 & x)
{
   iq12 temp;
   temp.val = _IQ12sqrt(x.val);
   return temp;
}

inline  iq11    IQ11sqrt(const iq11 & x)
{
   iq11 temp;
   temp.val = _IQ11sqrt(x.val);
   return temp;
}

inline  iq10    IQ10sqrt(const iq10 & x)
{
   iq10 temp;
   temp.val = _IQ10sqrt(x.val);
   return temp;
}

inline  iq9    IQ9sqrt(const iq9 & x)
{
   iq9 temp;
   temp.val = _IQ9sqrt(x.val);
   return temp;
}

inline  iq8    IQ8sqrt(const iq8 & x)
{
   iq8 temp;
   temp.val = _IQ8sqrt(x.val);
   return temp;
}

inline  iq7    IQ7sqrt(const iq7 & x)
{
   iq7 temp;
   temp.val = _IQ7sqrt(x.val);
   return temp;
}

inline  iq6    IQ6sqrt(const iq6 & x)
{
   iq6 temp;
   temp.val = _IQ6sqrt(x.val);
   return temp;
}

inline  iq5    IQ5sqrt(const iq5 & x)
{
   iq5 temp;
   temp.val = _IQ5sqrt(x.val);
   return temp;
}

inline  iq4    IQ4sqrt(const iq4 & x)
{
   iq4 temp;
   temp.val = _IQ4sqrt(x.val);
   return temp;
}

inline  iq3    IQ3sqrt(const iq3 & x)
{
   iq3 temp;
   temp.val = _IQ3sqrt(x.val);
   return temp;
}

inline  iq2    IQ2sqrt(const iq2 & x)
{
   iq2 temp;
   temp.val = _IQ2sqrt(x.val);
   return temp;
}

inline  iq1    IQ1sqrt(const iq1 & x)
{
   iq1 temp;
   temp.val = _IQ1sqrt(x.val);
   return temp;
}


//---------------------------------------------------------------------------
// Functions: IQisqrt(A), IQNisqrt(A)
//---------------------------------------------------------------------------

inline  iq  IQisqrt(const iq & x)
{
   iq temp;
   temp.val = _IQisqrt(x.val);
   return temp;
}

inline  iq30    IQ30isqrt(const iq30 & x)
{
   iq30 temp;
   temp.val = _IQ30isqrt(x.val);
   return temp;
}

inline  iq29    IQ29isqrt(const iq29 & x)
{
   iq29 temp;
   temp.val = _IQ29isqrt(x.val);
   return temp;
}

inline  iq28    IQ28isqrt(const iq28 & x)
{
   iq28 temp;
   temp.val = _IQ28isqrt(x.val);
   return temp;
}

inline  iq27    IQ27isqrt(const iq27 & x)
{
   iq27 temp;
   temp.val = _IQ27isqrt(x.val);
   return temp;
}

inline  iq26    IQ26isqrt(const iq26 & x)
{
   iq26 temp;
   temp.val = _IQ26isqrt(x.val);
   return temp;
}

inline  iq25    IQ25isqrt(const iq25 & x)
{
   iq25 temp;
   temp.val = _IQ25isqrt(x.val);
   return temp;
}

inline  iq24    IQ24isqrt(const iq24 & x)
{
   iq24 temp;
   temp.val = _IQ24isqrt(x.val);
   return temp;
}

inline  iq23    IQ23isqrt(const iq23 & x)
{
   iq23 temp;
   temp.val = _IQ23isqrt(x.val);
   return temp;
}

inline  iq22    IQ22isqrt(const iq22 & x)
{
   iq22 temp;
   temp.val = _IQ22isqrt(x.val);
   return temp;
}

inline  iq21    IQ21isqrt(const iq21 & x)
{
   iq21 temp;
   temp.val = _IQ21isqrt(x.val);
   return temp;
}

inline  iq20    IQ20isqrt(const iq20 & x)
{
   iq20 temp;
   temp.val = _IQ20isqrt(x.val);
   return temp;
}

inline  iq19    IQ19isqrt(const iq19 & x)
{
   iq19 temp;
   temp.val = _IQ19isqrt(x.val);
   return temp;
}

inline  iq18    IQ18isqrt(const iq18 & x)
{
   iq18 temp;
   temp.val = _IQ18isqrt(x.val);
   return temp;
}

inline  iq17    IQ17isqrt(const iq17 & x)
{
   iq17 temp;
   temp.val = _IQ17isqrt(x.val);
   return temp;
}

inline  iq16    IQ16isqrt(const iq16 & x)
{
   iq16 temp;
   temp.val = _IQ16isqrt(x.val);
   return temp;
}

inline  iq15    IQ15isqrt(const iq15 & x)
{
   iq15 temp;
   temp.val = _IQ15isqrt(x.val);
   return temp;
}

inline  iq14    IQ14isqrt(const iq14 & x)
{
   iq14 temp;
   temp.val = _IQ14isqrt(x.val);
   return temp;
}

inline  iq13    IQ13isqrt(const iq13 & x)
{
   iq13 temp;
   temp.val = _IQ13isqrt(x.val);
   return temp;
}

inline  iq12    IQ12isqrt(const iq12 & x)
{
   iq12 temp;
   temp.val = _IQ12isqrt(x.val);
   return temp;
}

inline  iq11    IQ11isqrt(const iq11 & x)
{
   iq11 temp;
   temp.val = _IQ11isqrt(x.val);
   return temp;
}

inline  iq10    IQ10isqrt(const iq10 & x)
{
   iq10 temp;
   temp.val = _IQ10isqrt(x.val);
   return temp;
}

inline  iq9    IQ9isqrt(const iq9 & x)
{
   iq9 temp;
   temp.val = _IQ9isqrt(x.val);
   return temp;
}

inline  iq8    IQ8isqrt(const iq8 & x)
{
   iq8 temp;
   temp.val = _IQ8isqrt(x.val);
   return temp;
}

inline  iq7    IQ7isqrt(const iq7 & x)
{
   iq7 temp;
   temp.val = _IQ7isqrt(x.val);
   return temp;
}

inline  iq6    IQ6isqrt(const iq6 & x)
{
   iq6 temp;
   temp.val = _IQ6isqrt(x.val);
   return temp;
}

inline  iq5    IQ5isqrt(const iq5 & x)
{
   iq5 temp;
   temp.val = _IQ5isqrt(x.val);
   return temp;
}

inline  iq4    IQ4isqrt(const iq4 & x)
{
   iq4 temp;
   temp.val = _IQ4isqrt(x.val);
   return temp;
}

inline  iq3    IQ3isqrt(const iq3 & x)
{
   iq3 temp;
   temp.val = _IQ3isqrt(x.val);
   return temp;
}

inline  iq2    IQ2isqrt(const iq2 & x)
{
   iq2 temp;
   temp.val = _IQ2isqrt(x.val);
   return temp;
}

inline  iq1    IQ1isqrt(const iq1 & x)
{
   iq1 temp;
   temp.val = _IQ1isqrt(x.val);
   return temp;
}


//---------------------------------------------------------------------------
// Functions: IQexp(A), IQNexp(A)
//---------------------------------------------------------------------------

inline  iq  IQexp(const iq & x)
{
   iq temp;
   temp.val = _IQexp(x.val);
   return temp;
}

inline  iq30    IQ30exp(const iq30 & x)
{
   iq30 temp;
   temp.val = _IQ30exp(x.val);
   return temp;
}

inline  iq29    IQ29exp(const iq29 & x)
{
   iq29 temp;
   temp.val = _IQ29exp(x.val);
   return temp;
}

inline  iq28    IQ28exp(const iq28 & x)
{
   iq28 temp;
   temp.val = _IQ28exp(x.val);
   return temp;
}

inline  iq27    IQ27exp(const iq27 & x)
{
   iq27 temp;
   temp.val = _IQ27exp(x.val);
   return temp;
}

inline  iq26    IQ26exp(const iq26 & x)
{
   iq26 temp;
   temp.val = _IQ26exp(x.val);
   return temp;
}

inline  iq25    IQ25exp(const iq25 & x)
{
   iq25 temp;
   temp.val = _IQ25exp(x.val);
   return temp;
}

inline  iq24    IQ24exp(const iq24 & x)
{
   iq24 temp;
   temp.val = _IQ24exp(x.val);
   return temp;
}

inline  iq23    IQ23exp(const iq23 & x)
{
   iq23 temp;
   temp.val = _IQ23exp(x.val);
   return temp;
}

inline  iq22    IQ22exp(const iq22 & x)
{
   iq22 temp;
   temp.val = _IQ22exp(x.val);
   return temp;
}

inline  iq21    IQ21exp(const iq21 & x)
{
   iq21 temp;
   temp.val = _IQ21exp(x.val);
   return temp;
}

inline  iq20    IQ20exp(const iq20 & x)
{
   iq20 temp;
   temp.val = _IQ20exp(x.val);
   return temp;
}

inline  iq19    IQ19exp(const iq19 & x)
{
   iq19 temp;
   temp.val = _IQ19exp(x.val);
   return temp;
}

inline  iq18    IQ18exp(const iq18 & x)
{
   iq18 temp;
   temp.val = _IQ18exp(x.val);
   return temp;
}

inline  iq17    IQ17exp(const iq17 & x)
{
   iq17 temp;
   temp.val = _IQ17exp(x.val);
   return temp;
}

inline  iq16    IQ16exp(const iq16 & x)
{
   iq16 temp;
   temp.val = _IQ16exp(x.val);
   return temp;
}

inline  iq15    IQ15exp(const iq15 & x)
{
   iq15 temp;
   temp.val = _IQ15exp(x.val);
   return temp;
}

inline  iq14    IQ14exp(const iq14 & x)
{
   iq14 temp;
   temp.val = _IQ14exp(x.val);
   return temp;
}

inline  iq13    IQ13exp(const iq13 & x)
{
   iq13 temp;
   temp.val = _IQ13exp(x.val);
   return temp;
}

inline  iq12    IQ12exp(const iq12 & x)
{
   iq12 temp;
   temp.val = _IQ12exp(x.val);
   return temp;
}

inline  iq11    IQ11exp(const iq11 & x)
{
   iq11 temp;
   temp.val = _IQ11exp(x.val);
   return temp;
}

inline  iq10    IQ10exp(const iq10 & x)
{
   iq10 temp;
   temp.val = _IQ10exp(x.val);
   return temp;
}

inline  iq9    IQ9exp(const iq9 & x)
{
   iq9 temp;
   temp.val = _IQ9exp(x.val);
   return temp;
}

inline  iq8    IQ8exp(const iq8 & x)
{
   iq8 temp;
   temp.val = _IQ8exp(x.val);
   return temp;
}

inline  iq7    IQ7exp(const iq7 & x)
{
   iq7 temp;
   temp.val = _IQ7exp(x.val);
   return temp;
}

inline  iq6    IQ6exp(const iq6 & x)
{
   iq6 temp;
   temp.val = _IQ6exp(x.val);
   return temp;
}

inline  iq5    IQ5exp(const iq5 & x)
{
   iq5 temp;
   temp.val = _IQ5exp(x.val);
   return temp;
}

inline  iq4    IQ4exp(const iq4 & x)
{
   iq4 temp;
   temp.val = _IQ4exp(x.val);
   return temp;
}

inline  iq3    IQ3exp(const iq3 & x)
{
   iq3 temp;
   temp.val = _IQ3exp(x.val);
   return temp;
}

inline  iq2    IQ2exp(const iq2 & x)
{
   iq2 temp;
   temp.val = _IQ2exp(x.val);
   return temp;
}

inline  iq1    IQ1exp(const iq1 & x)
{
   iq1 temp;
   temp.val = _IQ1exp(x.val);
   return temp;
}


//---------------------------------------------------------------------------
// Functions: IQmag(A,B), IQNmag(A,B)
//---------------------------------------------------------------------------

inline  iq  IQmag(const iq & y, const iq & x)
{
   iq temp;
   temp.val = _IQmag(y.val, x.val);
   return temp;
}

inline  iq30    IQ30mag(const iq30 & y, const iq30 & x)
{
   iq30 temp;
   temp.val = _IQ30mag(y.val, x.val);
   return temp;
}

inline  iq29    IQ29mag(const iq29 & y, const iq29 & x)
{
   iq29 temp;
   temp.val = _IQ29mag(y.val, x.val);
   return temp;
}

inline  iq28    IQ28mag(const iq28 & y, const iq28 & x)
{
   iq28 temp;
   temp.val = _IQ28mag(y.val, x.val);
   return temp;
}

inline  iq27    IQ27mag(const iq27 & y, const iq27 & x)
{
   iq27 temp;
   temp.val = _IQ27mag(y.val, x.val);
   return temp;
}

inline  iq26    IQ26mag(const iq26 & y, const iq26 & x)
{
   iq26 temp;
   temp.val = _IQ26mag(y.val, x.val);
   return temp;
}

inline  iq25    IQ25mag(const iq25 & y, const iq25 & x)
{
   iq25 temp;
   temp.val = _IQ25mag(y.val, x.val);
   return temp;
}

inline  iq24    IQ24mag(const iq24 & y, const iq24 & x)
{
   iq24 temp;
   temp.val = _IQ24mag(y.val, x.val);
   return temp;
}

inline  iq23    IQ23mag(const iq23 & y, const iq23 & x)
{
   iq23 temp;
   temp.val = _IQ23mag(y.val, x.val);
   return temp;
}

inline  iq22    IQ22mag(const iq22 & y, const iq22 & x)
{
   iq22 temp;
   temp.val = _IQ22mag(y.val, x.val);
   return temp;
}

inline  iq21    IQ21mag(const iq21 & y, const iq21 & x)
{
   iq21 temp;
   temp.val = _IQ21mag(y.val, x.val);
   return temp;
}

inline  iq20    IQ20mag(const iq20 & y, const iq20 & x)
{
   iq20 temp;
   temp.val = _IQ20mag(y.val, x.val);
   return temp;
}

inline  iq19    IQ19mag(const iq19 & y, const iq19 & x)
{
   iq19 temp;
   temp.val = _IQ19mag(y.val, x.val);
   return temp;
}

inline  iq18    IQ18mag(const iq18 & y, const iq18 & x)
{
   iq18 temp;
   temp.val = _IQ18mag(y.val, x.val);
   return temp;
}

inline  iq17    IQ17mag(const iq17 & y, const iq17 & x)
{
   iq17 temp;
   temp.val = _IQ17mag(y.val, x.val);
   return temp;
}

inline  iq16    IQ16mag(const iq16 & y, const iq16 & x)
{
   iq16 temp;
   temp.val = _IQ16mag(y.val, x.val);
   return temp;
}

inline  iq15    IQ15mag(const iq15 & y, const iq15 & x)
{
   iq15 temp;
   temp.val = _IQ15mag(y.val, x.val);
   return temp;
}

inline  iq14    IQ14mag(const iq14 & y, const iq14 & x)
{
   iq14 temp;
   temp.val = _IQ14mag(y.val, x.val);
   return temp;
}

inline  iq13    IQ13mag(const iq13 & y, const iq13 & x)
{
   iq13 temp;
   temp.val = _IQ13mag(y.val, x.val);
   return temp;
}

inline  iq12    IQ12mag(const iq12 & y, const iq12 & x)
{
   iq12 temp;
   temp.val = _IQ12mag(y.val, x.val);
   return temp;
}

inline  iq11    IQ11mag(const iq11 & y, const iq11 & x)
{
   iq11 temp;
   temp.val = _IQ11mag(y.val, x.val);
   return temp;
}

inline  iq10    IQ10mag(const iq10 & y, const iq10 & x)
{
   iq10 temp;
   temp.val = _IQ10mag(y.val, x.val);
   return temp;
}

inline  iq9    IQ9mag(const iq9 & y, const iq9 & x)
{
   iq9 temp;
   temp.val = _IQ9mag(y.val, x.val);
   return temp;
}

inline  iq8    IQ8mag(const iq8 & y, const iq8 & x)
{
   iq8 temp;
   temp.val = _IQ8mag(y.val, x.val);
   return temp;
}

inline  iq7    IQ7mag(const iq7 & y, const iq7 & x)
{
   iq7 temp;
   temp.val = _IQ7mag(y.val, x.val);
   return temp;
}

inline  iq6    IQ6mag(const iq6 & y, const iq6 & x)
{
   iq6 temp;
   temp.val = _IQ6mag(y.val, x.val);
   return temp;
}

inline  iq5    IQ5mag(const iq5 & y, const iq5 & x)
{
   iq5 temp;
   temp.val = _IQ5mag(y.val, x.val);
   return temp;
}

inline  iq4    IQ4mag(const iq4 & y, const iq4 & x)
{
   iq4 temp;
   temp.val = _IQ4mag(y.val, x.val);
   return temp;
}

inline  iq3    IQ3mag(const iq3 & y, const iq3 & x)
{
   iq3 temp;
   temp.val = _IQ3mag(y.val, x.val);
   return temp;
}

inline  iq2    IQ2mag(const iq2 & y, const iq2 & x)
{
   iq2 temp;
   temp.val = _IQ2mag(y.val, x.val);
   return temp;
}

inline  iq1    IQ1mag(const iq1 & y, const iq1 & x)
{
   iq1 temp;
   temp.val = _IQ1mag(y.val, x.val);
   return temp;
}


//---------------------------------------------------------------------------
// Functions: IQabs(A), IQNabs(A)
//---------------------------------------------------------------------------

inline  iq  IQabs(const iq & y)
{
   iq temp;
   temp.val = labs(y.val);
   return temp;
}

inline  iq30    IQ30abs(const iq30 & y)
{
   iq30 temp;
   temp.val = labs(y.val);
   return temp;
}

inline  iq29    IQ29abs(const iq29 & y)
{
   iq29 temp;
   temp.val = labs(y.val);
   return temp;
}

inline  iq28    IQ28abs(const iq28 & y)
{
   iq28 temp;
   temp.val = labs(y.val);
   return temp;
}

inline  iq27    IQ27abs(const iq27 & y)
{
   iq27 temp;
   temp.val = labs(y.val);
   return temp;
}

inline  iq26    IQ26abs(const iq26 & y)
{
   iq26 temp;
   temp.val = labs(y.val);
   return temp;
}

inline  iq25    IQ25abs(const iq25 & y)
{
   iq25 temp;
   temp.val = labs(y.val);
   return temp;
}

inline  iq24    IQ24abs(const iq24 & y)
{
   iq24 temp;
   temp.val = labs(y.val);
   return temp;
}

inline  iq23    IQ23abs(const iq23 & y)
{
   iq23 temp;
   temp.val = labs(y.val);
   return temp;
}

inline  iq22    IQ22abs(const iq22 & y)
{
   iq22 temp;
   temp.val = labs(y.val);
   return temp;
}

inline  iq21    IQ21abs(const iq21 & y)
{
   iq21 temp;
   temp.val = labs(y.val);
   return temp;
}

inline  iq20    IQ20abs(const iq20 & y)
{
   iq20 temp;
   temp.val = labs(y.val);
   return temp;
}

inline  iq19    IQ19abs(const iq19 & y)
{
   iq19 temp;
   temp.val = labs(y.val);
   return temp;
}

inline  iq18    IQ18abs(const iq18 & y)
{
   iq18 temp;
   temp.val = labs(y.val);
   return temp;
}

inline  iq17    IQ17abs(const iq17 & y)
{
   iq17 temp;
   temp.val = labs(y.val);
   return temp;
}

inline  iq16    IQ16abs(const iq16 & y)
{
   iq16 temp;
   temp.val = labs(y.val);
   return temp;
}

inline  iq15    IQ15abs(const iq15 & y)
{
   iq15 temp;
   temp.val = labs(y.val);
   return temp;
}

inline  iq14    IQ14abs(const iq14 & y)
{
   iq14 temp;
   temp.val = labs(y.val);
   return temp;
}

inline  iq13    IQ13abs(const iq13 & y)
{
   iq13 temp;
   temp.val = labs(y.val);
   return temp;
}

inline  iq12    IQ12abs(const iq12 & y)
{
   iq12 temp;
   temp.val = labs(y.val);
   return temp;
}

inline  iq11    IQ11abs(const iq11 & y)
{
   iq11 temp;
   temp.val = labs(y.val);
   return temp;
}

inline  iq10    IQ10abs(const iq10 & y)
{
   iq10 temp;
   temp.val = labs(y.val);
   return temp;
}

inline  iq9    IQ9abs(const iq9 & y)
{
   iq9 temp;
   temp.val = labs(y.val);
   return temp;
}

inline  iq8    IQ8abs(const iq8 & y)
{
   iq8 temp;
   temp.val = labs(y.val);
   return temp;
}

inline  iq7    IQ7abs(const iq7 & y)
{
   iq7 temp;
   temp.val = labs(y.val);
   return temp;
}

inline  iq6    IQ6abs(const iq6 & y)
{
   iq6 temp;
   temp.val = labs(y.val);
   return temp;
}

inline  iq5    IQ5abs(const iq5 & y)
{
   iq5 temp;
   temp.val = labs(y.val);
   return temp;
}

inline  iq4    IQ4abs(const iq4 & y)
{
   iq4 temp;
   temp.val = labs(y.val);
   return temp;
}

inline  iq3    IQ3abs(const iq3 & y)
{
   iq3 temp;
   temp.val = labs(y.val);
   return temp;
}

inline  iq2    IQ2abs(const iq2 & y)
{
   iq2 temp;
   temp.val = labs(y.val);
   return temp;
}

inline  iq1    IQ1abs(const iq1 & y)
{
   iq1 temp;
   temp.val = labs(y.val);
   return temp;
}


//---------------------------------------------------------------------------
// Functions: IQlog(A), IQNlog(A)
//---------------------------------------------------------------------------

inline  iq  IQlog(const iq & y)
{
   iq temp;
   temp.val = _IQlog(y.val);
   return temp;
}

inline  iq30    IQ30log(const iq30 & y)
{
   iq30 temp;
   temp.val = _IQ30log(y.val);
   return temp;
}

inline  iq29    IQ29log(const iq29 & y)
{
   iq29 temp;
   temp.val = _IQ29log(y.val);
   return temp;
}

inline  iq28    IQ28log(const iq28 & y)
{
   iq28 temp;
   temp.val = _IQ28log(y.val);
   return temp;
}

inline  iq27    IQ27log(const iq27 & y)
{
   iq27 temp;
   temp.val = _IQ27log(y.val);
   return temp;
}

inline  iq26    IQ26log(const iq26 & y)
{
   iq26 temp;
   temp.val = _IQ26log(y.val);
   return temp;
}

inline  iq25    IQ25log(const iq25 & y)
{
   iq25 temp;
   temp.val = _IQ25log(y.val);
   return temp;
}

inline  iq24    IQ24log(const iq24 & y)
{
   iq24 temp;
   temp.val = _IQ24log(y.val);
   return temp;
}

inline  iq23    IQ23log(const iq23 & y)
{
   iq23 temp;
   temp.val = _IQ23log(y.val);
   return temp;
}

inline  iq22    IQ22log(const iq22 & y)
{
   iq22 temp;
   temp.val = _IQ22log(y.val);
   return temp;
}

inline  iq21    IQ21log(const iq21 & y)
{
   iq21 temp;
   temp.val = _IQ21log(y.val);
   return temp;
}

inline  iq20    IQ20log(const iq20 & y)
{
   iq20 temp;
   temp.val = _IQ20log(y.val);
   return temp;
}

inline  iq19    IQ19log(const iq19 & y)
{
   iq19 temp;
   temp.val = _IQ19log(y.val);
   return temp;
}

inline  iq18    IQ18log(const iq18 & y)
{
   iq18 temp;
   temp.val = _IQ18log(y.val);
   return temp;
}

inline  iq17    IQ17log(const iq17 & y)
{
   iq17 temp;
   temp.val = _IQ17log(y.val);
   return temp;
}

inline  iq16    IQ16log(const iq16 & y)
{
   iq16 temp;
   temp.val = _IQ16log(y.val);
   return temp;
}

inline  iq15    IQ15log(const iq15 & y)
{
   iq15 temp;
   temp.val = _IQ15log(y.val);
   return temp;
}

inline  iq14    IQ14log(const iq14 & y)
{
   iq14 temp;
   temp.val = _IQ14log(y.val);
   return temp;
}

inline  iq13    IQ13log(const iq13 & y)
{
   iq13 temp;
   temp.val = _IQ13log(y.val);
   return temp;
}

inline  iq12    IQ12log(const iq12 & y)
{
   iq12 temp;
   temp.val = _IQ12log(y.val);
   return temp;
}

inline  iq11    IQ11log(const iq11 & y)
{
   iq11 temp;
   temp.val = _IQ11log(y.val);
   return temp;
}

inline  iq10    IQ10log(const iq10 & y)
{
   iq10 temp;
   temp.val = _IQ10log(y.val);
   return temp;
}

inline  iq9    IQ9log(const iq9 & y)
{
   iq9 temp;
   temp.val = _IQ9log(y.val);
   return temp;
}

inline  iq8    IQ8log(const iq8 & y)
{
   iq8 temp;
   temp.val = _IQ8log(y.val);
   return temp;
}

inline  iq7    IQ7log(const iq7 & y)
{
   iq7 temp;
   temp.val = _IQ7log(y.val);
   return temp;
}

inline  iq6    IQ6log(const iq6 & y)
{
   iq6 temp;
   temp.val = _IQ6log(y.val);
   return temp;
}

inline  iq5    IQ5log(const iq5 & y)
{
   iq5 temp;
   temp.val = _IQ5log(y.val);
   return temp;
}

inline  iq4    IQ4log(const iq4 & y)
{
   iq4 temp;
   temp.val = _IQ4log(y.val);
   return temp;
}

inline  iq3    IQ3log(const iq3 & y)
{
   iq3 temp;
   temp.val = _IQ3log(y.val);
   return temp;
}

inline  iq2    _IQ2log(const iq2 & y)
{
   iq2 temp;
   temp.val = _IQ2log(y.val);
   return temp;
}

inline  iq1    IQ1log(const iq1 & y)
{
   iq1 temp;
   temp.val = _IQ1log(y.val);
   return temp;
}




//---------------------------------------------------------------------------
// Operators: "*", "*="
//---------------------------------------------------------------------------

inline iq operator * (const iq &x, const iq &y)
{
   iq temp;
   temp.val = _IQmpy(x.val, y.val);
   return temp;
}

inline iq & iq :: operator *= (const iq &x)
{
   val = _IQmpy(val, x.val);
   return *this;
}

inline iq30 operator * (const iq30 &x, const iq30 &y)
{
   iq30 temp;
   temp.val = _IQ30mpy(x.val, y.val);
   return temp;
}

inline iq30 & iq30 :: operator *= (const iq30 &x)
{
   val = _IQ30mpy(val, x.val);
   return *this;
}

inline iq29 operator * (const iq29 &x, const iq29 &y)
{
   iq29 temp;
   temp.val = _IQ29mpy(x.val, y.val);
   return temp;
}

inline iq29 & iq29 :: operator *= (const iq29 &x)
{
   val = _IQ29mpy(val, x.val);
   return *this;
}

inline iq28 operator * (const iq28 &x, const iq28 &y)
{
   iq28 temp;
   temp.val = _IQ28mpy(x.val, y.val);
   return temp;
}

inline iq28 & iq28 :: operator *= (const iq28 &x)
{
   val = _IQ28mpy(val, x.val);
   return *this;
}

inline iq27 operator * (const iq27 &x, const iq27 &y)
{
   iq27 temp;
   temp.val = _IQ27mpy(x.val, y.val);
   return temp;
}

inline iq27 & iq27 :: operator *= (const iq27 &x)
{
   val = _IQ27mpy(val, x.val);
   return *this;
}

inline iq26 operator * (const iq26 &x, const iq26 &y)
{
   iq26 temp;
   temp.val = _IQ26mpy(x.val, y.val);
   return temp;
}

inline iq26 & iq26 :: operator *= (const iq26 &x)
{
   val = _IQ26mpy(val, x.val);
   return *this;
}

inline iq25 operator * (const iq25 &x, const iq25 &y)
{
   iq25 temp;
   temp.val = _IQ25mpy(x.val, y.val);
   return temp;
}

inline iq25 & iq25 :: operator *= (const iq25 &x)
{
   val = _IQ25mpy(val, x.val);
   return *this;
}

inline iq24 operator * (const iq24 &x, const iq24 &y)
{
   iq24 temp;
   temp.val = _IQ24mpy(x.val, y.val);
   return temp;
}

inline iq24 & iq24 :: operator *= (const iq24 &x)
{
   val = _IQ24mpy(val, x.val);
   return *this;
}

inline iq23 operator * (const iq23 &x, const iq23 &y)
{
   iq23 temp;
   temp.val = _IQ23mpy(x.val, y.val);
   return temp;
}

inline iq23 & iq23 :: operator *= (const iq23 &x)
{
   val = _IQ23mpy(val, x.val);
   return *this;
}

inline iq22 operator * (const iq22 &x, const iq22 &y)
{
   iq22 temp;
   temp.val = _IQ22mpy(x.val, y.val);
   return temp;
}

inline iq22 & iq22 :: operator *= (const iq22 &x)
{
   val = _IQ22mpy(val, x.val);
   return *this;
}

inline iq21 operator * (const iq21 &x, const iq21 &y)
{
   iq21 temp;
   temp.val = _IQ21mpy(x.val, y.val);
   return temp;
}

inline iq21 & iq21 :: operator *= (const iq21 &x)
{
   val = _IQ21mpy(val, x.val);
   return *this;
}

inline iq20 operator * (const iq20 &x, const iq20 &y)
{
   iq20 temp;
   temp.val = _IQ20mpy(x.val, y.val);
   return temp;
}

inline iq20 & iq20 :: operator *= (const iq20 &x)
{
   val = _IQ20mpy(val, x.val);
   return *this;
}

inline iq19 operator * (const iq19 &x, const iq19 &y)
{
   iq19 temp;
   temp.val = _IQ19mpy(x.val, y.val);
   return temp;
}

inline iq19 & iq19 :: operator *= (const iq19 &x)
{
   val = _IQ19mpy(val, x.val);
   return *this;
}

inline iq18 operator * (const iq18 &x, const iq18 &y)
{
   iq18 temp;
   temp.val = _IQ18mpy(x.val, y.val);
   return temp;
}

inline iq18 & iq18 :: operator *= (const iq18 &x)
{
   val = _IQ18mpy(val, x.val);
   return *this;
}

inline iq17 operator * (const iq17 &x, const iq17 &y)
{
   iq17 temp;
   temp.val = _IQ17mpy(x.val, y.val);
   return temp;
}

inline iq17 & iq17 :: operator *= (const iq17 &x)
{
   val = _IQ17mpy(val, x.val);
   return *this;
}

inline iq16 operator * (const iq16 &x, const iq16 &y)
{
   iq16 temp;
   temp.val = _IQ16mpy(x.val, y.val);
   return temp;
}

inline iq16 & iq16 :: operator *= (const iq16 &x)
{
   val = _IQ16mpy(val, x.val);
   return *this;
}

inline iq15 operator * (const iq15 &x, const iq15 &y)
{
   iq15 temp;
   temp.val = _IQ15mpy(x.val, y.val);
   return temp;
}

inline iq15 & iq15 :: operator *= (const iq15 &x)
{
   val = _IQ15mpy(val, x.val);
   return *this;
}

inline iq14 operator * (const iq14 &x, const iq14 &y)
{
   iq14 temp;
   temp.val = _IQ14mpy(x.val, y.val);
   return temp;
}

inline iq14 & iq14 :: operator *= (const iq14 &x)
{
   val = _IQ14mpy(val, x.val);
   return *this;
}

inline iq13 operator * (const iq13 &x, const iq13 &y)
{
   iq13 temp;
   temp.val = _IQ13mpy(x.val, y.val);
   return temp;
}

inline iq13 & iq13 :: operator *= (const iq13 &x)
{
   val = _IQ13mpy(val, x.val);
   return *this;
}


inline iq12 operator * (const iq12 &x, const iq12 &y)
{
   iq12 temp;
   temp.val = _IQ12mpy(x.val, y.val);
   return temp;
}

inline iq12 & iq12 :: operator *= (const iq12 &x)
{
   val = _IQ12mpy(val, x.val);
   return *this;
}

inline iq11 operator * (const iq11 &x, const iq11 &y)
{
   iq11 temp;
   temp.val = _IQ11mpy(x.val, y.val);
   return temp;
}

inline iq11 & iq11 :: operator *= (const iq11 &x)
{
   val = _IQ11mpy(val, x.val);
   return *this;
}

inline iq10 operator * (const iq10 &x, const iq10 &y)
{
   iq10 temp;
   temp.val = _IQ10mpy(x.val, y.val);
   return temp;
}

inline iq10 & iq10 :: operator *= (const iq10 &x)
{
   val = _IQ10mpy(val, x.val);
   return *this;
}

inline iq9 operator * (const iq9 &x, const iq9 &y)
{
   iq9 temp;
   temp.val = _IQ9mpy(x.val, y.val);
   return temp;
}

inline iq9 & iq9 :: operator *= (const iq9 &x)
{
   val = _IQ9mpy(val, x.val);
   return *this;
}

inline iq8 operator * (const iq8 &x, const iq8 &y)
{
   iq8 temp;
   temp.val = _IQ8mpy(x.val, y.val);
   return temp;
}

inline iq8 & iq8 :: operator *= (const iq8 &x)
{
   val = _IQ8mpy(val, x.val);
   return *this;
}

inline iq7 operator * (const iq7 &x, const iq7 &y)
{
   iq7 temp;
   temp.val = _IQ7mpy(x.val, y.val);
   return temp;
}

inline iq7 & iq7 :: operator *= (const iq7 &x)
{
   val = _IQ7mpy(val, x.val);
   return *this;
}

inline iq6 operator * (const iq6 &x, const iq6 &y)
{
   iq6 temp;
   temp.val = _IQ6mpy(x.val, y.val);
   return temp;
}

inline iq6 & iq6 :: operator *= (const iq6 &x)
{
   val = _IQ6mpy(val, x.val);
   return *this;
}

inline iq5 operator * (const iq5 &x, const iq5 &y)
{
   iq5 temp;
   temp.val = _IQ5mpy(x.val, y.val);
   return temp;
}

inline iq5 & iq5 :: operator *= (const iq5 &x)
{
   val = _IQ5mpy(val, x.val);
   return *this;
}

inline iq4 operator * (const iq4 &x, const iq4 &y)
{
   iq4 temp;
   temp.val = _IQ4mpy(x.val, y.val);
   return temp;
}

inline iq4 & iq4 :: operator *= (const iq4 &x)
{
   val = _IQ4mpy(val, x.val);
   return *this;
}

inline iq3 operator * (const iq3 &x, const iq3 &y)
{
   iq3 temp;
   temp.val = _IQ3mpy(x.val, y.val);
   return temp;
}

inline iq3 & iq3 :: operator *= (const iq3 &x)
{
   val = _IQ3mpy(val, x.val);
   return *this;
}

inline iq2 operator * (const iq2 &x, const iq2 &y)
{
   iq2 temp;
   temp.val = _IQ2mpy(x.val, y.val);
   return temp;
}

inline iq2 & iq2 :: operator *= (const iq2 &x)
{
   val = _IQ2mpy(val, x.val);
   return *this;
}

inline iq1 operator * (const iq1 &x, const iq1 &y)
{
   iq1 temp;
   temp.val = _IQ1mpy(x.val, y.val);
   return temp;
}

inline iq1 & iq1 :: operator *= (const iq1 &x)
{
   val = _IQ1mpy(val, x.val);
   return *this;
}

//---------------------------------------------------------------------------
// Operator: "="
//---------------------------------------------------------------------------

inline iq & iq :: operator = (const iq & x)
{
   val = x.val;
   return *this;
}

inline iq30 & iq30 :: operator = (const iq30 & x)
{
   val = x.val;
   return *this;
}

inline iq29 & iq29 :: operator = (const iq29 & x)
{
   val = x.val;
   return *this;
}

inline iq28 & iq28 :: operator = (const iq28 & x)
{
   val = x.val;
   return *this;
}

inline iq27 & iq27 :: operator = (const iq27 & x)
{
   val = x.val;
   return *this;
}

inline iq26 & iq26 :: operator = (const iq26 & x)
{
   val = x.val;
   return *this;
}

inline iq25 & iq25 :: operator = (const iq25 & x)
{
   val = x.val;
   return *this;
}

inline iq24 & iq24 :: operator = (const iq24 & x)
{
   val = x.val;
   return *this;
}

inline iq23 & iq23 :: operator = (const iq23 & x)
{
   val = x.val;
   return *this;
}

inline iq22 & iq22 :: operator = (const iq22 & x)
{
   val = x.val;
   return *this;
}

inline iq21 & iq21 :: operator = (const iq21 & x)
{
   val = x.val;
   return *this;
}

inline iq20 & iq20 :: operator = (const iq20 & x)
{
   val = x.val;
   return *this;
}

inline iq19 & iq19 :: operator = (const iq19 & x)
{
   val = x.val;
   return *this;
}

inline iq18 & iq18 :: operator = (const iq18 & x)
{
   val = x.val;
   return *this;
}

inline iq17 & iq17 :: operator = (const iq17 & x)
{
   val = x.val;
   return *this;
}

inline iq16 & iq16 :: operator = (const iq16 & x)
{
   val = x.val;
   return *this;
}

inline iq15 & iq15 :: operator = (const iq15 & x)
{
   val = x.val;
   return *this;
}

inline iq14 & iq14 :: operator = (const iq14 & x)
{
   val = x.val;
   return *this;
}

inline iq13 & iq13 :: operator = (const iq13 & x)
{
   val = x.val;
   return *this;
}

inline iq12 & iq12 :: operator = (const iq12 & x)
{
   val = x.val;
   return *this;
}

inline iq11 & iq11 :: operator = (const iq11 & x)
{
   val = x.val;
   return *this;
}

inline iq10 & iq10 :: operator = (const iq10 & x)
{
   val = x.val;
   return *this;
}

inline iq9 & iq9 :: operator = (const iq9 & x)
{
   val = x.val;
   return *this;
}

inline iq8 & iq8 :: operator = (const iq8 & x)
{
   val = x.val;
   return *this;
}

inline iq7 & iq7 :: operator = (const iq7 & x)
{
   val = x.val;
   return *this;
}

inline iq6 & iq6 :: operator = (const iq6 & x)
{
   val = x.val;
   return *this;
}

inline iq5 & iq5 :: operator = (const iq5 & x)
{
   val = x.val;
   return *this;
}

inline iq4 & iq4 :: operator = (const iq4 & x)
{
   val = x.val;
   return *this;
}

inline iq3 & iq3 :: operator = (const iq3 & x)
{
   val = x.val;
   return *this;
}

inline iq2 & iq2 :: operator = (const iq2 & x)
{
   val = x.val;
   return *this;
}

inline iq1 & iq1 :: operator = (const iq1 & x)
{
   val = x.val;
   return *this;
}

//---------------------------------------------------------------------------
// Operators: "-", "-=":
//---------------------------------------------------------------------------

inline iq operator - (const iq &x, const iq &y)
{
   iq temp;
   temp.val = x.val - y.val;
   return temp;
}

inline iq operator - (const iq &x)
{
   iq temp;
   temp.val = - x.val;
   return temp;
}

inline iq & iq :: operator -= (const iq &x)
{
   val -= x.val;
   return *this;
}

inline iq30 operator - (const iq30 &x, const iq30 &y)
{
   iq30 temp;
   temp.val = x.val - y.val;
   return temp;
}

inline iq30 operator - (const iq30 &x)
{
   iq30 temp;
   temp.val = - x.val;
   return temp;
}

inline iq30 & iq30 :: operator -= (const iq30 &x)
{
   val -= x.val;
   return *this;
}

inline iq29 operator - (const iq29 &x, const iq29 &y)
{
   iq29 temp;
   temp.val = x.val - y.val;
   return temp;
}

inline iq29 operator - (const iq29 &x)
{
   iq29 temp;
   temp.val = - x.val;
   return temp;
}

inline iq29 & iq29 :: operator -= (const iq29 &x)
{
   val -= x.val;
   return *this;
}

inline iq28 operator - (const iq28 &x, const iq28 &y)
{
   iq28 temp;
   temp.val = x.val - y.val;
   return temp;
}

inline iq28 operator - (const iq28 &x)
{
   iq28 temp;
   temp.val = - x.val;
   return temp;
}

inline iq28 & iq28 :: operator -= (const iq28 &x)
{
   val -= x.val;
   return *this;
}

inline iq27 operator - (const iq27 &x, const iq27 &y)
{
   iq27 temp;
   temp.val = x.val - y.val;
   return temp;
}

inline iq27 operator - (const iq27 &x)
{
   iq27 temp;
   temp.val = - x.val;
   return temp;
}

inline iq27 & iq27 :: operator -= (const iq27 &x)
{
   val -= x.val;
   return *this;
}

inline iq26 operator - (const iq26 &x, const iq26 &y)
{
   iq26 temp;
   temp.val = x.val - y.val;
   return temp;
}

inline iq26 operator - (const iq26 &x)
{
   iq26 temp;
   temp.val = - x.val;
   return temp;
}

inline iq26 & iq26 :: operator -= (const iq26 &x)
{
   val -= x.val;
   return *this;
}

inline iq25 operator - (const iq25 &x, const iq25 &y)
{
   iq25 temp;
   temp.val = x.val - y.val;
   return temp;
}

inline iq25 operator - (const iq25 &x)
{
   iq25 temp;
   temp.val = - x.val;
   return temp;
}

inline iq25 & iq25 :: operator -= (const iq25 &x)
{
   val -= x.val;
   return *this;
}

inline iq24 operator - (const iq24 &x, const iq24 &y)
{
   iq24 temp;
   temp.val = x.val - y.val;
   return temp;
}

inline iq24 operator - (const iq24 &x)
{
   iq24 temp;
   temp.val = - x.val;
   return temp;
}

inline iq24 & iq24 :: operator -= (const iq24 &x)
{
   val -= x.val;
   return *this;
}

inline iq23 operator - (const iq23 &x, const iq23 &y)
{
   iq23 temp;
   temp.val = x.val - y.val;
   return temp;
}

inline iq23 operator - (const iq23 &x)
{
   iq23 temp;
   temp.val = - x.val;
   return temp;
}

inline iq23 & iq23 :: operator -= (const iq23 &x)
{
   val -= x.val;
   return *this;
}

inline iq22 operator - (const iq22 &x, const iq22 &y)
{
   iq22 temp;
   temp.val = x.val - y.val;
   return temp;
}

inline iq22 operator - (const iq22 &x)
{
   iq22 temp;
   temp.val = - x.val;
   return temp;
}

inline iq22 & iq22 :: operator -= (const iq22 &x)
{
   val -= x.val;
   return *this;
}

inline iq21 operator - (const iq21 &x, const iq21 &y)
{
   iq21 temp;
   temp.val = x.val - y.val;
   return temp;
}

inline iq21 operator - (const iq21 &x)
{
   iq21 temp;
   temp.val = - x.val;
   return temp;
}

inline iq21 & iq21 :: operator -= (const iq21 &x)
{
   val -= x.val;
   return *this;
}

inline iq20 operator - (const iq20 &x, const iq20 &y)
{
   iq20 temp;
   temp.val = x.val - y.val;
   return temp;
}

inline iq20 operator - (const iq20 &x)
{
   iq20 temp;
   temp.val = - x.val;
   return temp;
}

inline iq20 & iq20 :: operator -= (const iq20 &x)
{
   val -= x.val;
   return *this;
}

inline iq19 operator - (const iq19 &x, const iq19 &y)
{
   iq19 temp;
   temp.val = x.val - y.val;
   return temp;
}

inline iq19 operator - (const iq19 &x)
{
   iq19 temp;
   temp.val = - x.val;
   return temp;
}

inline iq19 & iq19 :: operator -= (const iq19 &x)
{
   val -= x.val;
   return *this;
}

inline iq18 operator - (const iq18 &x, const iq18 &y)
{
   iq18 temp;
   temp.val = x.val - y.val;
   return temp;
}

inline iq18 operator - (const iq18 &x)
{
   iq18 temp;
   temp.val = - x.val;
   return temp;
}

inline iq18 & iq18 :: operator -= (const iq18 &x)
{
   val -= x.val;
   return *this;
}

inline iq17 operator - (const iq17 &x, const iq17 &y)
{
   iq17 temp;
   temp.val = x.val - y.val;
   return temp;
}

inline iq17 operator - (const iq17 &x)
{
   iq17 temp;
   temp.val = - x.val;
   return temp;
}

inline iq17 & iq17 :: operator -= (const iq17 &x)
{
   val -= x.val;
   return *this;
}

inline iq16 operator - (const iq16 &x, const iq16 &y)
{
   iq16 temp;
   temp.val = x.val - y.val;
   return temp;
}

inline iq16 operator - (const iq16 &x)
{
   iq16 temp;
   temp.val = - x.val;
   return temp;
}

inline iq16 & iq16 :: operator -= (const iq16 &x)
{
   val -= x.val;
   return *this;
}

inline iq15 operator - (const iq15 &x, const iq15 &y)
{
   iq15 temp;
   temp.val = x.val - y.val;
   return temp;
}

inline iq15 operator - (const iq15 &x)
{
   iq15 temp;
   temp.val = - x.val;
   return temp;
}

inline iq15 & iq15 :: operator -= (const iq15 &x)
{
   val -= x.val;
   return *this;
}

inline iq14 operator - (const iq14 &x, const iq14 &y)
{
   iq14 temp;
   temp.val = x.val - y.val;
   return temp;
}

inline iq14 operator - (const iq14 &x)
{
   iq14 temp;
   temp.val = - x.val;
   return temp;
}

inline iq14 & iq14 :: operator -= (const iq14 &x)
{
   val -= x.val;
   return *this;
}


inline iq13 operator - (const iq13 &x, const iq13 &y)
{
   iq13 temp;
   temp.val = x.val - y.val;
   return temp;
}

inline iq13 operator - (const iq13 &x)
{
   iq13 temp;
   temp.val = - x.val;
   return temp;
}

inline iq13 & iq13 :: operator -= (const iq13 &x)
{
   val -= x.val;
   return *this;
}


inline iq12 operator - (const iq12 &x, const iq12 &y)
{
   iq12 temp;
   temp.val = x.val - y.val;
   return temp;
}

inline iq12 operator - (const iq12 &x)
{
   iq12 temp;
   temp.val = - x.val;
   return temp;
}

inline iq12 & iq12 :: operator -= (const iq12 &x)
{
   val -= x.val;
   return *this;
}

inline iq11 operator - (const iq11 &x, const iq11 &y)
{
   iq11 temp;
   temp.val = x.val - y.val;
   return temp;
}

inline iq11 operator - (const iq11 &x)
{
   iq11 temp;
   temp.val = - x.val;
   return temp;
}

inline iq11 & iq11 :: operator -= (const iq11 &x)
{
   val -= x.val;
   return *this;
}

inline iq10 operator - (const iq10 &x, const iq10 &y)
{
   iq10 temp;
   temp.val = x.val - y.val;
   return temp;
}

inline iq10 operator - (const iq10 &x)
{
   iq10 temp;
   temp.val = - x.val;
   return temp;
}

inline iq10 & iq10 :: operator -= (const iq10 &x)
{
   val -= x.val;
   return *this;
}

inline iq9 operator - (const iq9 &x, const iq9 &y)
{
   iq9 temp;
   temp.val = x.val - y.val;
   return temp;
}

inline iq9 operator - (const iq9 &x)
{
   iq9 temp;
   temp.val = - x.val;
   return temp;
}

inline iq9 & iq9 :: operator -= (const iq9 &x)
{
   val -= x.val;
   return *this;
}

inline iq8 operator - (const iq8 &x, const iq8 &y)
{
   iq8 temp;
   temp.val = x.val - y.val;
   return temp;
}

inline iq8 operator - (const iq8 &x)
{
   iq8 temp;
   temp.val = - x.val;
   return temp;
}

inline iq8 & iq8 :: operator -= (const iq8 &x)
{
   val -= x.val;
   return *this;
}

inline iq7 operator - (const iq7 &x, const iq7 &y)
{
   iq7 temp;
   temp.val = x.val - y.val;
   return temp;
}

inline iq7 operator - (const iq7 &x)
{
   iq7 temp;
   temp.val = - x.val;
   return temp;
}

inline iq7 & iq7 :: operator -= (const iq7 &x)
{
   val -= x.val;
   return *this;
}

inline iq6 operator - (const iq6 &x, const iq6 &y)
{
   iq6 temp;
   temp.val = x.val - y.val;
   return temp;
}

inline iq6 operator - (const iq6 &x)
{
   iq6 temp;
   temp.val = - x.val;
   return temp;
}

inline iq6 & iq6 :: operator -= (const iq6 &x)
{
   val -= x.val;
   return *this;
}

inline iq5 operator - (const iq5 &x, const iq5 &y)
{
   iq5 temp;
   temp.val = x.val - y.val;
   return temp;
}

inline iq5 operator - (const iq5 &x)
{
   iq5 temp;
   temp.val = - x.val;
   return temp;
}

inline iq5 & iq5 :: operator -= (const iq5 &x)
{
   val -= x.val;
   return *this;
}

inline iq4 operator - (const iq4 &x, const iq4 &y)
{
   iq4 temp;
   temp.val = x.val - y.val;
   return temp;
}

inline iq4 operator - (const iq4 &x)
{
   iq4 temp;
   temp.val = - x.val;
   return temp;
}

inline iq4 & iq4 :: operator -= (const iq4 &x)
{
   val -= x.val;
   return *this;
}

inline iq3 operator - (const iq3 &x, const iq3 &y)
{
   iq3 temp;
   temp.val = x.val - y.val;
   return temp;
}

inline iq3 operator - (const iq3 &x)
{
   iq3 temp;
   temp.val = - x.val;
   return temp;
}

inline iq3 & iq3 :: operator -= (const iq3 &x)
{
   val -= x.val;
   return *this;
}

inline iq2 operator - (const iq2 &x, const iq2 &y)
{
   iq2 temp;
   temp.val = x.val - y.val;
   return temp;
}

inline iq2 operator - (const iq2 &x)
{
   iq2 temp;
   temp.val = - x.val;
   return temp;
}

inline iq2 & iq2 :: operator -= (const iq2 &x)
{
   val -= x.val;
   return *this;
}

inline iq1 operator - (const iq1 &x, const iq1 &y)
{
   iq1 temp;
   temp.val = x.val - y.val;
   return temp;
}

inline iq1 operator - (const iq1 &x)
{
   iq1 temp;
   temp.val = - x.val;
   return temp;
}

inline iq1 & iq1 :: operator -= (const iq1 &x)
{
   val -= x.val;
   return *this;
}

//---------------------------------------------------------------------------
// Operators: "+", "+="
//---------------------------------------------------------------------------

inline iq operator + (const iq &x, const iq &y)
{
   iq temp;
   temp.val = x.val + y.val;
   return temp;
}

inline iq & iq :: operator += (const iq &x)
{
   val += x.val;
   return *this;
}

inline iq30 operator + (const iq30 &x, const iq30 &y)
{
   iq30 temp;
   temp.val = x.val + y.val;
   return temp;
}

inline iq30 & iq30 :: operator += (const iq30 &x)
{
   val += x.val;
   return *this;
}

inline iq29 operator + (const iq29 &x, const iq29 &y)
{
   iq29 temp;
   temp.val = x.val + y.val;
   return temp;
}

inline iq29 & iq29 :: operator += (const iq29 &x)
{
   val += x.val;
   return *this;
}

inline iq28 operator + (const iq28 &x, const iq28 &y)
{
   iq28 temp;
   temp.val = x.val + y.val;
   return temp;
}

inline iq28 & iq28 :: operator += (const iq28 &x)
{
   val += x.val;
   return *this;
}

inline iq27 operator + (const iq27 &x, const iq27 &y)
{
   iq27 temp;
   temp.val = x.val + y.val;
   return temp;
}

inline iq27 & iq27 :: operator += (const iq27 &x)
{
   val += x.val;
   return *this;
}

inline iq26 operator + (const iq26 &x, const iq26 &y)
{
   iq26 temp;
   temp.val = x.val + y.val;
   return temp;
}

inline iq26 & iq26 :: operator += (const iq26 &x)
{
   val += x.val;
   return *this;
}

inline iq25 operator + (const iq25 &x, const iq25 &y)
{
   iq25 temp;
   temp.val = x.val + y.val;
   return temp;
}

inline iq25 & iq25 :: operator += (const iq25 &x)
{
   val += x.val;
   return *this;
}

inline iq24 operator + (const iq24 &x, const iq24 &y)
{
   iq24 temp;
   temp.val = x.val + y.val;
   return temp;
}

inline iq24 & iq24 :: operator += (const iq24 &x)
{
   val += x.val;
   return *this;
}

inline iq23 operator + (const iq23 &x, const iq23 &y)
{
   iq23 temp;
   temp.val = x.val + y.val;
   return temp;
}

inline iq23 & iq23 :: operator += (const iq23 &x)
{
   val += x.val;
   return *this;
}

inline iq22 operator + (const iq22 &x, const iq22 &y)
{
   iq22 temp;
   temp.val = x.val + y.val;
   return temp;
}

inline iq22 & iq22 :: operator += (const iq22 &x)
{
   val += x.val;
   return *this;
}

inline iq21 operator + (const iq21 &x, const iq21 &y)
{
   iq21 temp;
   temp.val = x.val + y.val;
   return temp;
}

inline iq21 & iq21 :: operator += (const iq21 &x)
{
   val += x.val;
   return *this;
}

inline iq20 operator + (const iq20 &x, const iq20 &y)
{
   iq20 temp;
   temp.val = x.val + y.val;
   return temp;
}

inline iq20 & iq20 :: operator += (const iq20 &x)
{
   val += x.val;
   return *this;
}

inline iq19 operator + (const iq19 &x, const iq19 &y)
{
   iq19 temp;
   temp.val = x.val + y.val;
   return temp;
}

inline iq19 & iq19 :: operator += (const iq19 &x)
{
   val += x.val;
   return *this;
}

inline iq18 operator + (const iq18 &x, const iq18 &y)
{
   iq18 temp;
   temp.val = x.val + y.val;
   return temp;
}

inline iq18 & iq18 :: operator += (const iq18 &x)
{
   val += x.val;
   return *this;
}

inline iq17 operator + (const iq17 &x, const iq17 &y)
{
   iq17 temp;
   temp.val = x.val + y.val;
   return temp;
}

inline iq17 & iq17 :: operator += (const iq17 &x)
{
   val += x.val;
   return *this;
}

inline iq16 operator + (const iq16 &x, const iq16 &y)
{
   iq16 temp;
   temp.val = x.val + y.val;
   return temp;
}

inline iq16 & iq16 :: operator += (const iq16 &x)
{
   val += x.val;
   return *this;
}

inline iq15 operator + (const iq15 &x, const iq15 &y)
{
   iq15 temp;
   temp.val = x.val + y.val;
   return temp;
}

inline iq15 & iq15 :: operator += (const iq15 &x)
{
   val += x.val;
   return *this;
}

inline iq14 operator + (const iq14 &x, const iq14 &y)
{
   iq14 temp;
   temp.val = x.val + y.val;
   return temp;
}

inline iq14 & iq14 :: operator += (const iq14 &x)
{
   val += x.val;
   return *this;
}

inline iq13 operator + (const iq13 &x, const iq13 &y)
{
   iq13 temp;
   temp.val = x.val + y.val;
   return temp;
}

inline iq13 & iq13 :: operator += (const iq13 &x)
{
   val += x.val;
   return *this;
}

inline iq12 operator + (const iq12 &x, const iq12 &y)
{
   iq12 temp;
   temp.val = x.val + y.val;
   return temp;
}

inline iq12 & iq12 :: operator += (const iq12 &x)
{
   val += x.val;
   return *this;
}

inline iq11 operator + (const iq11 &x, const iq11 &y)
{
   iq11 temp;
   temp.val = x.val + y.val;
   return temp;
}

inline iq11 & iq11 :: operator += (const iq11 &x)
{
   val += x.val;
   return *this;
}

inline iq10 operator + (const iq10 &x, const iq10 &y)
{
   iq10 temp;
   temp.val = x.val + y.val;
   return temp;
}

inline iq10 & iq10 :: operator += (const iq10 &x)
{
   val += x.val;
   return *this;
}

inline iq9 operator + (const iq9 &x, const iq9 &y)
{
   iq9 temp;
   temp.val = x.val + y.val;
   return temp;
}

inline iq9 & iq9 :: operator += (const iq9 &x)
{
   val += x.val;
   return *this;
}

inline iq8 operator + (const iq8 &x, const iq8 &y)
{
   iq8 temp;
   temp.val = x.val + y.val;
   return temp;
}

inline iq8 & iq8 :: operator += (const iq8 &x)
{
   val += x.val;
   return *this;
}

inline iq7 operator + (const iq7 &x, const iq7 &y)
{
   iq7 temp;
   temp.val = x.val + y.val;
   return temp;
}

inline iq7 & iq7 :: operator += (const iq7 &x)
{
   val += x.val;
   return *this;
}

inline iq6 operator + (const iq6 &x, const iq6 &y)
{
   iq6 temp;
   temp.val = x.val + y.val;
   return temp;
}

inline iq6 & iq6 :: operator += (const iq6 &x)
{
   val += x.val;
   return *this;
}

inline iq5 operator + (const iq5 &x, const iq5 &y)
{
   iq5 temp;
   temp.val = x.val + y.val;
   return temp;
}

inline iq5 & iq5 :: operator += (const iq5 &x)
{
   val += x.val;
   return *this;
}

inline iq4 operator + (const iq4 &x, const iq4 &y)
{
   iq4 temp;
   temp.val = x.val + y.val;
   return temp;
}

inline iq4 & iq4 :: operator += (const iq4 &x)
{
   val += x.val;
   return *this;
}

inline iq3 operator + (const iq3 &x, const iq3 &y)
{
   iq3 temp;
   temp.val = x.val + y.val;
   return temp;
}

inline iq3 & iq3 :: operator += (const iq3 &x)
{
   val += x.val;
   return *this;
}

inline iq2 operator + (const iq2 &x, const iq2 &y)
{
   iq2 temp;
   temp.val = x.val + y.val;
   return temp;
}

inline iq2 & iq2 :: operator += (const iq2 &x)
{
   val += x.val;
   return *this;
}

inline iq1 operator + (const iq1 &x, const iq1 &y)
{
   iq1 temp;
   temp.val = x.val + y.val;
   return temp;
}

inline iq1 & iq1 :: operator += (const iq1 &x)
{
   val += x.val;
   return *this;
}
//---------------------------------------------------------------------------
// Operators: "/", "/="
//---------------------------------------------------------------------------

inline iq operator / (const iq &x, const iq &y)
{
   iq temp;
   temp.val = _IQdiv(x.val, y.val);
   return temp;
}

inline iq & iq :: operator /= (const iq &x)
{
   val = _IQdiv(val, x.val);
   return *this;
}

inline iq30 operator / (const iq30 &x, const iq30 &y)
{
   iq30 temp;
   temp.val = _IQ30div(x.val, y.val);
   return temp;
}

inline iq30 & iq30 :: operator /= (const iq30 &x)
{
   val = _IQ30div(val, x.val);
   return *this;
}

inline iq29 operator / (const iq29 &x, const iq29 &y)
{
   iq29 temp;
   temp.val = _IQ29div(x.val, y.val);
   return temp;
}

inline iq29 & iq29 :: operator /= (const iq29 &x)
{
   val = _IQ29div(val, x.val);
   return *this;
}

inline iq28 operator / (const iq28 &x, const iq28 &y)
{
   iq28 temp;
   temp.val = _IQ28div(x.val, y.val);
   return temp;
}

inline iq28 & iq28 :: operator /= (const iq28 &x)
{
   val = _IQ28div(val, x.val);
   return *this;
}

inline iq27 operator / (const iq27 &x, const iq27 &y)
{
   iq27 temp;
   temp.val = _IQ27div(x.val, y.val);
   return temp;
}

inline iq27 & iq27 :: operator /= (const iq27 &x)
{
   val = _IQ27div(val, x.val);
   return *this;
}

inline iq26 operator / (const iq26 &x, const iq26 &y)
{
   iq26 temp;
   temp.val = _IQ26div(x.val, y.val);
   return temp;
}

inline iq26 & iq26 :: operator /= (const iq26 &x)
{
   val = _IQ26div(val, x.val);
   return *this;
}

inline iq25 operator / (const iq25 &x, const iq25 &y)
{
   iq25 temp;
   temp.val = _IQ25div(x.val, y.val);
   return temp;
}

inline iq25 & iq25 :: operator /= (const iq25 &x)
{
   val = _IQ25div(val, x.val);
   return *this;
}

inline iq24 operator / (const iq24 &x, const iq24 &y)
{
   iq24 temp;
   temp.val = _IQ24div(x.val, y.val);
   return temp;
}

inline iq24 & iq24 :: operator /= (const iq24 &x)
{
   val = _IQ24div(val, x.val);
   return *this;
}

inline iq23 operator / (const iq23 &x, const iq23 &y)
{
   iq23 temp;
   temp.val = _IQ23div(x.val, y.val);
   return temp;
}

inline iq23 & iq23 :: operator /= (const iq23 &x)
{
   val = _IQ23div(val, x.val);
   return *this;
}

inline iq22 operator / (const iq22 &x, const iq22 &y)
{
   iq22 temp;
   temp.val = _IQ22div(x.val, y.val);
   return temp;
}

inline iq22 & iq22 :: operator /= (const iq22 &x)
{
   val = _IQ22div(val, x.val);
   return *this;
}

inline iq21 operator / (const iq21 &x, const iq21 &y)
{
   iq21 temp;
   temp.val = _IQ21div(x.val, y.val);
   return temp;
}

inline iq21 & iq21 :: operator /= (const iq21 &x)
{
   val = _IQ21div(val, x.val);
   return *this;
}

inline iq20 operator / (const iq20 &x, const iq20 &y)
{
   iq20 temp;
   temp.val = _IQ20div(x.val, y.val);
   return temp;
}

inline iq20 & iq20 :: operator /= (const iq20 &x)
{
   val = _IQ20div(val, x.val);
   return *this;
}

inline iq19 operator / (const iq19 &x, const iq19 &y)
{
   iq19 temp;
   temp.val = _IQ19div(x.val, y.val);
   return temp;
}

inline iq19 & iq19 :: operator /= (const iq19 &x)
{
   val = _IQ19div(val, x.val);
   return *this;
}

inline iq18 operator / (const iq18 &x, const iq18 &y)
{
   iq18 temp;
   temp.val = _IQ18div(x.val, y.val);
   return temp;
}

inline iq18 & iq18 :: operator /= (const iq18 &x)
{
   val = _IQ18div(val, x.val);
   return *this;
}

inline iq17 operator / (const iq17 &x, const iq17 &y)
{
   iq17 temp;
   temp.val = _IQ17div(x.val, y.val);
   return temp;
}

inline iq17 & iq17 :: operator /= (const iq17 &x)
{
   val = _IQ17div(val, x.val);
   return *this;
}

inline iq16 operator / (const iq16 &x, const iq16 &y)
{
   iq16 temp;
   temp.val = _IQ16div(x.val, y.val);
   return temp;
}

inline iq16 & iq16 :: operator /= (const iq16 &x)
{
   val = _IQ16div(val, x.val);
   return *this;
}

inline iq15 operator / (const iq15 &x, const iq15 &y)
{
   iq15 temp;
   temp.val = _IQ15div(x.val, y.val);
   return temp;
}

inline iq15 & iq15 :: operator /= (const iq15 &x)
{
   val = _IQ15div(val, x.val);
   return *this;
}

inline iq14 operator / (const iq14 &x, const iq14 &y)
{
   iq14 temp;
   temp.val = _IQ14div(x.val, y.val);
   return temp;
}

inline iq14 & iq14 :: operator /= (const iq14 &x)
{
   val = _IQ14div(val, x.val);
   return *this;
}

inline iq13 operator / (const iq13 &x, const iq13 &y)
{
   iq13 temp;
   temp.val = _IQ13div(x.val, y.val);
   return temp;
}

inline iq13 & iq13 :: operator /= (const iq13 &x)
{
   val = _IQ13div(val, x.val);
   return *this;
}

inline iq12 operator / (const iq12 &x, const iq12 &y)
{
   iq12 temp;
   temp.val = _IQ12div(x.val, y.val);
   return temp;
}

inline iq12 & iq12 :: operator /= (const iq12 &x)
{
   val = _IQ12div(val, x.val);
   return *this;
}

inline iq11 operator / (const iq11 &x, const iq11 &y)
{
   iq11 temp;
   temp.val = _IQ11div(x.val, y.val);
   return temp;
}

inline iq11 & iq11 :: operator /= (const iq11 &x)
{
   val = _IQ11div(val, x.val);
   return *this;
}

inline iq10 operator / (const iq10 &x, const iq10 &y)
{
   iq10 temp;
   temp.val = _IQ10div(x.val, y.val);
   return temp;
}

inline iq10 & iq10 :: operator /= (const iq10 &x)
{
   val = _IQ10div(val, x.val);
   return *this;
}

inline iq9 operator / (const iq9 &x, const iq9 &y)
{
   iq9 temp;
   temp.val = _IQ9div(x.val, y.val);
   return temp;
}

inline iq9 & iq9 :: operator /= (const iq9 &x)
{
   val = _IQ9div(val, x.val);
   return *this;
}

inline iq8 operator / (const iq8 &x, const iq8 &y)
{
   iq8 temp;
   temp.val = _IQ8div(x.val, y.val);
   return temp;
}

inline iq8 & iq8 :: operator /= (const iq8 &x)
{
   val = _IQ8div(val, x.val);
   return *this;
}

inline iq7 operator / (const iq7 &x, const iq7 &y)
{
   iq7 temp;
   temp.val = _IQ7div(x.val, y.val);
   return temp;
}

inline iq7 & iq7 :: operator /= (const iq7 &x)
{
   val = _IQ7div(val, x.val);
   return *this;
}

inline iq6 operator / (const iq6 &x, const iq6 &y)
{
   iq6 temp;
   temp.val = _IQ6div(x.val, y.val);
   return temp;
}

inline iq6 & iq6 :: operator /= (const iq6 &x)
{
   val = _IQ6div(val, x.val);
   return *this;
}

inline iq5 operator / (const iq5 &x, const iq5 &y)
{
   iq5 temp;
   temp.val = _IQ5div(x.val, y.val);
   return temp;
}

inline iq5 & iq5 :: operator /= (const iq5 &x)
{
   val = _IQ5div(val, x.val);
   return *this;
}

inline iq4 operator / (const iq4 &x, const iq4 &y)
{
   iq4 temp;
   temp.val = _IQ4div(x.val, y.val);
   return temp;
}

inline iq4 & iq4 :: operator /= (const iq4 &x)
{
   val = _IQ4div(val, x.val);
   return *this;
}

inline iq3 operator / (const iq3 &x, const iq3 &y)
{
   iq3 temp;
   temp.val = _IQ3div(x.val, y.val);
   return temp;
}

inline iq3 & iq3 :: operator /= (const iq3 &x)
{
   val = _IQ3div(val, x.val);
   return *this;
}

inline iq2 operator / (const iq2 &x, const iq2 &y)
{
   iq2 temp;
   temp.val = _IQ2div(x.val, y.val);
   return temp;
}

inline iq2 & iq2 :: operator /= (const iq2 &x)
{
   val = _IQ2div(val, x.val);
   return *this;
}

inline iq1 operator / (const iq1 &x, const iq1 &y)
{
   iq1 temp;
   temp.val = _IQ1div(x.val, y.val);
   return temp;
}

inline iq1 & iq1 :: operator /= (const iq1 &x)
{
   val = _IQ1div(val, x.val);
   return *this;
}


//---------------------------------------------------------------------------
// Operators: "==", "!=", "<", ">", "<=", ">=", "&&", "||"
//
inline bool operator == (const iq &x, const iq& y)     { return (x.val == y.val); }
inline bool operator == (const iq30 &x, const iq30& y) { return (x.val == y.val); }
inline bool operator == (const iq29 &x, const iq29& y) { return (x.val == y.val); }
inline bool operator == (const iq28 &x, const iq28& y) { return (x.val == y.val); }
inline bool operator == (const iq27 &x, const iq27& y) { return (x.val == y.val); }
inline bool operator == (const iq26 &x, const iq26& y) { return (x.val == y.val); }
inline bool operator == (const iq25 &x, const iq25& y) { return (x.val == y.val); }
inline bool operator == (const iq24 &x, const iq24& y) { return (x.val == y.val); }
inline bool operator == (const iq23 &x, const iq23& y) { return (x.val == y.val); }
inline bool operator == (const iq22 &x, const iq22& y) { return (x.val == y.val); }
inline bool operator == (const iq21 &x, const iq21& y) { return (x.val == y.val); }
inline bool operator == (const iq20 &x, const iq20& y) { return (x.val == y.val); }
inline bool operator == (const iq19 &x, const iq19& y) { return (x.val == y.val); }
inline bool operator == (const iq18 &x, const iq18& y) { return (x.val == y.val); }
inline bool operator == (const iq17 &x, const iq17& y) { return (x.val == y.val); }
inline bool operator == (const iq16 &x, const iq16& y) { return (x.val == y.val); }
inline bool operator == (const iq15 &x, const iq15& y) { return (x.val == y.val); }
inline bool operator == (const iq14 &x, const iq14& y) { return (x.val == y.val); }
inline bool operator == (const iq13 &x, const iq13& y) { return (x.val == y.val); }
inline bool operator == (const iq12 &x, const iq12& y) { return (x.val == y.val); }
inline bool operator == (const iq11 &x, const iq11& y) { return (x.val == y.val); }
inline bool operator == (const iq10 &x, const iq10& y) { return (x.val == y.val); }
inline bool operator == (const iq9  &x, const iq9&  y) { return (x.val == y.val); }
inline bool operator == (const iq8  &x, const iq8&  y) { return (x.val == y.val); }
inline bool operator == (const iq7  &x, const iq7&  y) { return (x.val == y.val); }
inline bool operator == (const iq6  &x, const iq6&  y) { return (x.val == y.val); }
inline bool operator == (const iq5  &x, const iq5&  y) { return (x.val == y.val); }
inline bool operator == (const iq4  &x, const iq4&  y) { return (x.val == y.val); }
inline bool operator == (const iq3  &x, const iq3&  y) { return (x.val == y.val); }
inline bool operator == (const iq2  &x, const iq2&  y) { return (x.val == y.val); }
inline bool operator == (const iq1  &x, const iq1&  y) { return (x.val == y.val); }


inline bool operator != (const iq &x, const iq& y)     { return (x.val != y.val); }
inline bool operator != (const iq30 &x, const iq30& y) { return (x.val != y.val); }
inline bool operator != (const iq29 &x, const iq29& y) { return (x.val != y.val); }
inline bool operator != (const iq28 &x, const iq28& y) { return (x.val != y.val); }
inline bool operator != (const iq27 &x, const iq27& y) { return (x.val != y.val); }
inline bool operator != (const iq26 &x, const iq26& y) { return (x.val != y.val); }
inline bool operator != (const iq25 &x, const iq25& y) { return (x.val != y.val); }
inline bool operator != (const iq24 &x, const iq24& y) { return (x.val != y.val); }
inline bool operator != (const iq23 &x, const iq23& y) { return (x.val != y.val); }
inline bool operator != (const iq22 &x, const iq22& y) { return (x.val != y.val); }
inline bool operator != (const iq21 &x, const iq21& y) { return (x.val != y.val); }
inline bool operator != (const iq20 &x, const iq20& y) { return (x.val != y.val); }
inline bool operator != (const iq19 &x, const iq19& y) { return (x.val != y.val); }
inline bool operator != (const iq18 &x, const iq18& y) { return (x.val != y.val); }
inline bool operator != (const iq17 &x, const iq17& y) { return (x.val != y.val); }
inline bool operator != (const iq16 &x, const iq16& y) { return (x.val != y.val); }
inline bool operator != (const iq15 &x, const iq15& y) { return (x.val != y.val); }
inline bool operator != (const iq14 &x, const iq14& y) { return (x.val != y.val); }
inline bool operator != (const iq13 &x, const iq13& y) { return (x.val != y.val); }
inline bool operator != (const iq12 &x, const iq12& y) { return (x.val != y.val); }
inline bool operator != (const iq11 &x, const iq11& y) { return (x.val != y.val); }
inline bool operator != (const iq10 &x, const iq10& y) { return (x.val != y.val); }
inline bool operator != (const iq9  &x, const iq9&  y) { return (x.val != y.val); }
inline bool operator != (const iq8  &x, const iq8&  y) { return (x.val != y.val); }
inline bool operator != (const iq7  &x, const iq7&  y) { return (x.val != y.val); }
inline bool operator != (const iq6  &x, const iq6&  y) { return (x.val != y.val); }
inline bool operator != (const iq5  &x, const iq5&  y) { return (x.val != y.val); }
inline bool operator != (const iq4  &x, const iq4&  y) { return (x.val != y.val); }
inline bool operator != (const iq3  &x, const iq3&  y) { return (x.val != y.val); }
inline bool operator != (const iq2  &x, const iq2&  y) { return (x.val != y.val); }
inline bool operator != (const iq1  &x, const iq1&  y) { return (x.val != y.val); }



inline bool operator <  (const iq &x, const iq &y)     { return (x.val <  y.val); }
inline bool operator <  (const iq30 &x, const iq30& y) { return (x.val <  y.val); }
inline bool operator <  (const iq29 &x, const iq29& y) { return (x.val <  y.val); }
inline bool operator <  (const iq28 &x, const iq28& y) { return (x.val <  y.val); }
inline bool operator <  (const iq27 &x, const iq27& y) { return (x.val <  y.val); }
inline bool operator <  (const iq26 &x, const iq26& y) { return (x.val <  y.val); }
inline bool operator <  (const iq25 &x, const iq25& y) { return (x.val <  y.val); }
inline bool operator <  (const iq24 &x, const iq24& y) { return (x.val <  y.val); }
inline bool operator <  (const iq23 &x, const iq23& y) { return (x.val <  y.val); }
inline bool operator <  (const iq22 &x, const iq22& y) { return (x.val <  y.val); }
inline bool operator <  (const iq21 &x, const iq21& y) { return (x.val <  y.val); }
inline bool operator <  (const iq20 &x, const iq20& y) { return (x.val <  y.val); }
inline bool operator <  (const iq19 &x, const iq19& y) { return (x.val <  y.val); }
inline bool operator <  (const iq18 &x, const iq18& y) { return (x.val <  y.val); }
inline bool operator <  (const iq17 &x, const iq17& y) { return (x.val <  y.val); }
inline bool operator <  (const iq16 &x, const iq16& y) { return (x.val <  y.val); }
inline bool operator <  (const iq15 &x, const iq15& y) { return (x.val <  y.val); }
inline bool operator <  (const iq14 &x, const iq14& y) { return (x.val <  y.val); }
inline bool operator <  (const iq13 &x, const iq13& y) { return (x.val <  y.val); }
inline bool operator <  (const iq12 &x, const iq12& y) { return (x.val <  y.val); }
inline bool operator <  (const iq11 &x, const iq11& y) { return (x.val <  y.val); }
inline bool operator <  (const iq10 &x, const iq10& y) { return (x.val <  y.val); }
inline bool operator <  (const iq9  &x, const iq9&  y) { return (x.val <  y.val); }
inline bool operator <  (const iq8  &x, const iq8&  y) { return (x.val <  y.val); }
inline bool operator <  (const iq7  &x, const iq7&  y) { return (x.val <  y.val); }
inline bool operator <  (const iq6  &x, const iq6&  y) { return (x.val <  y.val); }
inline bool operator <  (const iq5  &x, const iq5&  y) { return (x.val <  y.val); }
inline bool operator <  (const iq4  &x, const iq4&  y) { return (x.val <  y.val); }
inline bool operator <  (const iq3  &x, const iq3&  y) { return (x.val <  y.val); }
inline bool operator <  (const iq2  &x, const iq2&  y) { return (x.val <  y.val); }
inline bool operator <  (const iq1  &x, const iq1&  y) { return (x.val <  y.val); }


inline bool operator >  (const iq &x, const iq &y)     { return (x.val >  y.val); }
inline bool operator >  (const iq30 &x, const iq30& y) { return (x.val >  y.val); }
inline bool operator >  (const iq29 &x, const iq29& y) { return (x.val >  y.val); }
inline bool operator >  (const iq28 &x, const iq28& y) { return (x.val >  y.val); }
inline bool operator >  (const iq27 &x, const iq27& y) { return (x.val >  y.val); }
inline bool operator >  (const iq26 &x, const iq26& y) { return (x.val >  y.val); }
inline bool operator >  (const iq25 &x, const iq25& y) { return (x.val >  y.val); }
inline bool operator >  (const iq24 &x, const iq24& y) { return (x.val >  y.val); }
inline bool operator >  (const iq23 &x, const iq23& y) { return (x.val >  y.val); }
inline bool operator >  (const iq22 &x, const iq22& y) { return (x.val >  y.val); }
inline bool operator >  (const iq21 &x, const iq21& y) { return (x.val >  y.val); }
inline bool operator >  (const iq20 &x, const iq20& y) { return (x.val >  y.val); }
inline bool operator >  (const iq19 &x, const iq19& y) { return (x.val >  y.val); }
inline bool operator >  (const iq18 &x, const iq18& y) { return (x.val >  y.val); }
inline bool operator >  (const iq17 &x, const iq17& y) { return (x.val >  y.val); }
inline bool operator >  (const iq16 &x, const iq16& y) { return (x.val >  y.val); }
inline bool operator >  (const iq15 &x, const iq15& y) { return (x.val >  y.val); }
inline bool operator >  (const iq14 &x, const iq14& y) { return (x.val >  y.val); }
inline bool operator >  (const iq13 &x, const iq13& y) { return (x.val >  y.val); }
inline bool operator >  (const iq12 &x, const iq12& y) { return (x.val >  y.val); }
inline bool operator >  (const iq11 &x, const iq11& y) { return (x.val >  y.val); }
inline bool operator >  (const iq10 &x, const iq10& y) { return (x.val >  y.val); }
inline bool operator >  (const iq9  &x, const iq9&  y) { return (x.val >  y.val); }
inline bool operator >  (const iq8  &x, const iq8&  y) { return (x.val >  y.val); }
inline bool operator >  (const iq7  &x, const iq7&  y) { return (x.val >  y.val); }
inline bool operator >  (const iq6  &x, const iq6&  y) { return (x.val >  y.val); }
inline bool operator >  (const iq5  &x, const iq5&  y) { return (x.val >  y.val); }
inline bool operator >  (const iq4  &x, const iq4&  y) { return (x.val >  y.val); }
inline bool operator >  (const iq3  &x, const iq3&  y) { return (x.val >  y.val); }
inline bool operator >  (const iq2  &x, const iq2&  y) { return (x.val >  y.val); }
inline bool operator >  (const iq1  &x, const iq1&  y) { return (x.val >  y.val); }

inline bool operator <= (const iq &x, const iq &y)     { return (x.val <= y.val); }
inline bool operator <= (const iq30 &x, const iq30& y) { return (x.val <= y.val); }
inline bool operator <= (const iq29 &x, const iq29& y) { return (x.val <= y.val); }
inline bool operator <= (const iq28 &x, const iq28& y) { return (x.val <= y.val); }
inline bool operator <= (const iq27 &x, const iq27& y) { return (x.val <= y.val); }
inline bool operator <= (const iq26 &x, const iq26& y) { return (x.val <= y.val); }
inline bool operator <= (const iq25 &x, const iq25& y) { return (x.val <= y.val); }
inline bool operator <= (const iq24 &x, const iq24& y) { return (x.val <= y.val); }
inline bool operator <= (const iq23 &x, const iq23& y) { return (x.val <= y.val); }
inline bool operator <= (const iq22 &x, const iq22& y) { return (x.val <= y.val); }
inline bool operator <= (const iq21 &x, const iq21& y) { return (x.val <= y.val); }
inline bool operator <= (const iq20 &x, const iq20& y) { return (x.val <= y.val); }
inline bool operator <= (const iq19 &x, const iq19& y) { return (x.val <= y.val); }
inline bool operator <= (const iq18 &x, const iq18& y) { return (x.val <= y.val); }
inline bool operator <= (const iq17 &x, const iq17& y) { return (x.val <= y.val); }
inline bool operator <= (const iq16 &x, const iq16& y) { return (x.val <= y.val); }
inline bool operator <= (const iq15 &x, const iq15& y) { return (x.val <= y.val); }
inline bool operator <= (const iq14 &x, const iq14& y) { return (x.val <= y.val); }
inline bool operator <= (const iq13 &x, const iq13& y) { return (x.val <= y.val); }
inline bool operator <= (const iq12 &x, const iq12& y) { return (x.val <= y.val); }
inline bool operator <= (const iq11 &x, const iq11& y) { return (x.val <= y.val); }
inline bool operator <= (const iq10 &x, const iq10& y) { return (x.val <= y.val); }
inline bool operator <= (const iq9  &x, const iq9&  y) { return (x.val <= y.val); }
inline bool operator <= (const iq8  &x, const iq8&  y) { return (x.val <= y.val); }
inline bool operator <= (const iq7  &x, const iq7&  y) { return (x.val <= y.val); }
inline bool operator <= (const iq6  &x, const iq6&  y) { return (x.val <= y.val); }
inline bool operator <= (const iq5  &x, const iq5&  y) { return (x.val <= y.val); }
inline bool operator <= (const iq4  &x, const iq4&  y) { return (x.val <= y.val); }
inline bool operator <= (const iq3  &x, const iq3&  y) { return (x.val <= y.val); }
inline bool operator <= (const iq2  &x, const iq2&  y) { return (x.val <= y.val); }
inline bool operator <= (const iq1  &x, const iq1&  y) { return (x.val <= y.val); }


inline bool operator >= (const iq &x, const iq &y)     { return (x.val >= y.val); }
inline bool operator >= (const iq30 &x, const iq30& y) { return (x.val >= y.val); }
inline bool operator >= (const iq29 &x, const iq29& y) { return (x.val >= y.val); }
inline bool operator >= (const iq28 &x, const iq28& y) { return (x.val >= y.val); }
inline bool operator >= (const iq27 &x, const iq27& y) { return (x.val >= y.val); }
inline bool operator >= (const iq26 &x, const iq26& y) { return (x.val >= y.val); }
inline bool operator >= (const iq25 &x, const iq25& y) { return (x.val >= y.val); }
inline bool operator >= (const iq24 &x, const iq24& y) { return (x.val >= y.val); }
inline bool operator >= (const iq23 &x, const iq23& y) { return (x.val >= y.val); }
inline bool operator >= (const iq22 &x, const iq22& y) { return (x.val >= y.val); }
inline bool operator >= (const iq21 &x, const iq21& y) { return (x.val >= y.val); }
inline bool operator >= (const iq20 &x, const iq20& y) { return (x.val >= y.val); }
inline bool operator >= (const iq19 &x, const iq19& y) { return (x.val >= y.val); }
inline bool operator >= (const iq18 &x, const iq18& y) { return (x.val >= y.val); }
inline bool operator >= (const iq17 &x, const iq17& y) { return (x.val >= y.val); }
inline bool operator >= (const iq16 &x, const iq16& y) { return (x.val >= y.val); }
inline bool operator >= (const iq15 &x, const iq15& y) { return (x.val >= y.val); }
inline bool operator >= (const iq14 &x, const iq14& y) { return (x.val >= y.val); }
inline bool operator >= (const iq13 &x, const iq13& y) { return (x.val >= y.val); }
inline bool operator >= (const iq12 &x, const iq12& y) { return (x.val >= y.val); }
inline bool operator >= (const iq11 &x, const iq11& y) { return (x.val >= y.val); }
inline bool operator >= (const iq10 &x, const iq10& y) { return (x.val >= y.val); }
inline bool operator >= (const iq9  &x, const iq9&  y) { return (x.val >= y.val); }
inline bool operator >= (const iq8  &x, const iq8&  y) { return (x.val >= y.val); }
inline bool operator >= (const iq7  &x, const iq7&  y) { return (x.val >= y.val); }
inline bool operator >= (const iq6  &x, const iq6&  y) { return (x.val >= y.val); }
inline bool operator >= (const iq5  &x, const iq5&  y) { return (x.val >= y.val); }
inline bool operator >= (const iq4  &x, const iq4&  y) { return (x.val >= y.val); }
inline bool operator >= (const iq3  &x, const iq3&  y) { return (x.val >= y.val); }
inline bool operator >= (const iq2  &x, const iq2&  y) { return (x.val >= y.val); }
inline bool operator >= (const iq1  &x, const iq1&  y) { return (x.val >= y.val); }

inline bool operator && (const iq &x, const iq &y)     { return (x.val && y.val); }
inline bool operator && (const iq30 &x, const iq30& y) { return (x.val && y.val); }
inline bool operator && (const iq29 &x, const iq29& y) { return (x.val && y.val); }
inline bool operator && (const iq28 &x, const iq28& y) { return (x.val && y.val); }
inline bool operator && (const iq27 &x, const iq27& y) { return (x.val && y.val); }
inline bool operator && (const iq26 &x, const iq26& y) { return (x.val && y.val); }
inline bool operator && (const iq25 &x, const iq25& y) { return (x.val && y.val); }
inline bool operator && (const iq24 &x, const iq24& y) { return (x.val && y.val); }
inline bool operator && (const iq23 &x, const iq23& y) { return (x.val && y.val); }
inline bool operator && (const iq22 &x, const iq22& y) { return (x.val && y.val); }
inline bool operator && (const iq21 &x, const iq21& y) { return (x.val && y.val); }
inline bool operator && (const iq20 &x, const iq20& y) { return (x.val && y.val); }
inline bool operator && (const iq19 &x, const iq19& y) { return (x.val && y.val); }
inline bool operator && (const iq18 &x, const iq18& y) { return (x.val && y.val); }
inline bool operator && (const iq17 &x, const iq17& y) { return (x.val && y.val); }
inline bool operator && (const iq16 &x, const iq16& y) { return (x.val && y.val); }
inline bool operator && (const iq15 &x, const iq15& y) { return (x.val && y.val); }
inline bool operator && (const iq14 &x, const iq14& y) { return (x.val && y.val); }
inline bool operator && (const iq13 &x, const iq13& y) { return (x.val && y.val); }
inline bool operator && (const iq12 &x, const iq12& y) { return (x.val && y.val); }
inline bool operator && (const iq11 &x, const iq11& y) { return (x.val && y.val); }
inline bool operator && (const iq10 &x, const iq10& y) { return (x.val && y.val); }
inline bool operator && (const iq9  &x, const iq9&  y) { return (x.val && y.val); }
inline bool operator && (const iq8  &x, const iq8&  y) { return (x.val && y.val); }
inline bool operator && (const iq7  &x, const iq7&  y) { return (x.val && y.val); }
inline bool operator && (const iq6  &x, const iq6&  y) { return (x.val && y.val); }
inline bool operator && (const iq5  &x, const iq5&  y) { return (x.val && y.val); }
inline bool operator && (const iq4  &x, const iq4&  y) { return (x.val && y.val); }
inline bool operator && (const iq3  &x, const iq3&  y) { return (x.val && y.val); }
inline bool operator && (const iq2  &x, const iq2&  y) { return (x.val && y.val); }
inline bool operator && (const iq1  &x, const iq1&  y) { return (x.val && y.val); }


inline bool operator || (const iq &x, const iq &y)     { return (x.val || y.val); }
inline bool operator || (const iq30 &x, const iq30& y) { return (x.val || y.val); }
inline bool operator || (const iq29 &x, const iq29& y) { return (x.val || y.val); }
inline bool operator || (const iq28 &x, const iq28& y) { return (x.val || y.val); }
inline bool operator || (const iq27 &x, const iq27& y) { return (x.val || y.val); }
inline bool operator || (const iq26 &x, const iq26& y) { return (x.val || y.val); }
inline bool operator || (const iq25 &x, const iq25& y) { return (x.val || y.val); }
inline bool operator || (const iq24 &x, const iq24& y) { return (x.val || y.val); }
inline bool operator || (const iq23 &x, const iq23& y) { return (x.val || y.val); }
inline bool operator || (const iq22 &x, const iq22& y) { return (x.val || y.val); }
inline bool operator || (const iq21 &x, const iq21& y) { return (x.val || y.val); }
inline bool operator || (const iq20 &x, const iq20& y) { return (x.val || y.val); }
inline bool operator || (const iq19 &x, const iq19& y) { return (x.val || y.val); }
inline bool operator || (const iq18 &x, const iq18& y) { return (x.val || y.val); }
inline bool operator || (const iq17 &x, const iq17& y) { return (x.val || y.val); }
inline bool operator || (const iq16 &x, const iq16& y) { return (x.val || y.val); }
inline bool operator || (const iq15 &x, const iq15& y) { return (x.val || y.val); }
inline bool operator || (const iq14 &x, const iq14& y) { return (x.val || y.val); }
inline bool operator || (const iq13 &x, const iq13& y) { return (x.val || y.val); }
inline bool operator || (const iq12 &x, const iq12& y) { return (x.val || y.val); }
inline bool operator || (const iq11 &x, const iq11& y) { return (x.val || y.val); }
inline bool operator || (const iq10 &x, const iq10& y) { return (x.val || y.val); }
inline bool operator || (const iq9  &x, const iq9&  y) { return (x.val || y.val); }
inline bool operator || (const iq8  &x, const iq8&  y) { return (x.val || y.val); }
inline bool operator || (const iq7  &x, const iq7&  y) { return (x.val || y.val); }
inline bool operator || (const iq6  &x, const iq6&  y) { return (x.val || y.val); }
inline bool operator || (const iq5  &x, const iq5&  y) { return (x.val || y.val); }
inline bool operator || (const iq4  &x, const iq4&  y) { return (x.val || y.val); }
inline bool operator || (const iq3  &x, const iq3&  y) { return (x.val || y.val); }
inline bool operator || (const iq2  &x, const iq2&  y) { return (x.val || y.val); }
inline bool operator || (const iq1  &x, const iq1&  y) { return (x.val || y.val); }

//---------------------------------------------------------------------------
// Operators: "&", "&="
//---------------------------------------------------------------------------

inline iq operator & (const iq &x, const long &y)
{
   iq temp;
   temp.val = x.val & y;
   return temp;
}

inline iq & iq :: operator &= (const long &x)
{
   val &= x;
   return *this;
}

inline iq30 operator & (const iq30 &x, const long &y)
{
   iq30 temp;
   temp.val = x.val & y;
   return temp;
}

inline iq30 & iq30 :: operator &= (const long &x)
{
   val &= x;
   return *this;
}

inline iq29 operator & (const iq29 &x, const long &y)
{
   iq29 temp;
   temp.val = x.val & y;
   return temp;
}

inline iq29 & iq29 :: operator &= (const long &x)
{
   val &= x;
   return *this;
}

inline iq28 operator & (const iq28 &x, const long &y)
{
   iq28 temp;
   temp.val = x.val & y;
   return temp;
}

inline iq28 & iq28 :: operator &= (const long &x)
{
   val &= x;
   return *this;
}

inline iq27 operator & (const iq27 &x, const long &y)
{
   iq27 temp;
   temp.val = x.val & y;
   return temp;
}

inline iq27 & iq27 :: operator &= (const long &x)
{
   val &= x;
   return *this;
}

inline iq26 operator & (const iq26 &x, const long &y)
{
   iq26 temp;
   temp.val = x.val & y;
   return temp;
}

inline iq26 & iq26 :: operator &= (const long &x)
{
   val &= x;
   return *this;
}

inline iq25 operator & (const iq25 &x, const long &y)
{
   iq25 temp;
   temp.val = x.val & y;
   return temp;
}

inline iq25 & iq25 :: operator &= (const long &x)
{
   val &= x;
   return *this;
}

inline iq24 operator & (const iq24 &x, const long &y)
{
   iq24 temp;
   temp.val = x.val & y;
   return temp;
}

inline iq24 & iq24 :: operator &= (const long &x)
{
   val &= x;
   return *this;
}

inline iq23 operator & (const iq23 &x, const long &y)
{
   iq23 temp;
   temp.val = x.val & y;
   return temp;
}

inline iq23 & iq23 :: operator &= (const long &x)
{
   val &= x;
   return *this;
}

inline iq22 operator & (const iq22 &x, const long &y)
{
   iq22 temp;
   temp.val = x.val & y;
   return temp;
}

inline iq22 & iq22 :: operator &= (const long &x)
{
   val &= x;
   return *this;
}

inline iq21 operator & (const iq21 &x, const long &y)
{
   iq21 temp;
   temp.val = x.val & y;
   return temp;
}

inline iq21 & iq21 :: operator &= (const long &x)
{
   val &= x;
   return *this;
}

inline iq20 operator & (const iq20 &x, const long &y)
{
   iq20 temp;
   temp.val = x.val & y;
   return temp;
}

inline iq20 & iq20 :: operator &= (const long &x)
{
   val &= x;
   return *this;
}

inline iq19 operator & (const iq19 &x, const long &y)
{
   iq19 temp;
   temp.val = x.val & y;
   return temp;
}

inline iq19 & iq19 :: operator &= (const long &x)
{
   val &= x;
   return *this;
}

inline iq18 operator & (const iq18 &x, const long &y)
{
   iq18 temp;
   temp.val = x.val & y;
   return temp;
}

inline iq18 & iq18 :: operator &= (const long &x)
{
   val &= x;
   return *this;
}

inline iq17 operator & (const iq17 &x, const long &y)
{
   iq17 temp;
   temp.val = x.val & y;
   return temp;
}

inline iq17 & iq17 :: operator &= (const long &x)
{
   val &= x;
   return *this;
}

inline iq16 operator & (const iq16 &x, const long &y)
{
   iq16 temp;
   temp.val = x.val & y;
   return temp;
}

inline iq16 & iq16 :: operator &= (const long &x)
{
   val &= x;
   return *this;
}

inline iq15 operator & (const iq15 &x, const long &y)
{
   iq15 temp;
   temp.val = x.val & y;
   return temp;
}

inline iq15 & iq15 :: operator &= (const long &x)
{
   val &= x;
   return *this;
}

inline iq14 operator & (const iq14 &x, const long &y)
{
   iq14 temp;
   temp.val = x.val & y;
   return temp;
}

inline iq14 & iq14 :: operator &= (const long &x)
{
   val &= x;
   return *this;
}

inline iq13 operator & (const iq13 &x, const long &y)
{
   iq13 temp;
   temp.val = x.val & y;
   return temp;
}

inline iq13 & iq13 :: operator &= (const long &x)
{
   val &= x;
   return *this;
}

inline iq12 operator & (const iq12 &x, const long &y)
{
   iq12 temp;
   temp.val = x.val & y;
   return temp;
}

inline iq12 & iq12 :: operator &= (const long &x)
{
   val &= x;
   return *this;
}

inline iq11 operator & (const iq11 &x, const long &y)
{
   iq11 temp;
   temp.val = x.val & y;
   return temp;
}

inline iq11 & iq11 :: operator &= (const long &x)
{
   val &= x;
   return *this;
}

inline iq10 operator & (const iq10 &x, const long &y)
{
   iq10 temp;
   temp.val = x.val & y;
   return temp;
}

inline iq10 & iq10 :: operator &= (const long &x)
{
   val &= x;
   return *this;
}

inline iq9 operator & (const iq9 &x, const long &y)
{
   iq9 temp;
   temp.val = x.val & y;
   return temp;
}

inline iq9 & iq9 :: operator &= (const long &x)
{
   val &= x;
   return *this;
}

inline iq8 operator & (const iq8 &x, const long &y)
{
   iq8 temp;
   temp.val = x.val & y;
   return temp;
}

inline iq8 & iq8 :: operator &= (const long &x)
{
   val &= x;
   return *this;
}

inline iq7 operator & (const iq7 &x, const long &y)
{
   iq7 temp;
   temp.val = x.val & y;
   return temp;
}

inline iq7 & iq7 :: operator &= (const long &x)
{
   val &= x;
   return *this;
}

inline iq6 operator & (const iq6 &x, const long &y)
{
   iq6 temp;
   temp.val = x.val & y;
   return temp;
}

inline iq6 & iq6 :: operator &= (const long &x)
{
   val &= x;
   return *this;
}

inline iq5 operator & (const iq5 &x, const long &y)
{
   iq5 temp;
   temp.val = x.val & y;
   return temp;
}

inline iq5 & iq5 :: operator &= (const long &x)
{
   val &= x;
   return *this;
}

inline iq4 operator & (const iq4 &x, const long &y)
{
   iq4 temp;
   temp.val = x.val & y;
   return temp;
}

inline iq4 & iq4 :: operator &= (const long &x)
{
   val &= x;
   return *this;
}

inline iq3 operator & (const iq3 &x, const long &y)
{
   iq3 temp;
   temp.val = x.val & y;
   return temp;
}

inline iq3 & iq3 :: operator &= (const long &x)
{
   val &= x;
   return *this;
}

inline iq2 operator & (const iq2 &x, const long &y)
{
   iq2 temp;
   temp.val = x.val & y;
   return temp;
}

inline iq2 & iq2 :: operator &= (const long &x)
{
   val &= x;
   return *this;
}

inline iq1 operator & (const iq1 &x, const long &y)
{
   iq1 temp;
   temp.val = x.val & y;
   return temp;
}

inline iq1 & iq1 :: operator &= (const long &x)
{
   val &= x;
   return *this;
}

//---------------------------------------------------------------------------
// Operators: "|", "|="
//---------------------------------------------------------------------------

inline iq operator | (const iq &x, const long &y)
{
   iq temp;
   temp.val = x.val | y;
   return temp;
}

inline iq & iq :: operator |= (const long &x)
{
   val |= x;
   return *this;
}

inline iq30 operator | (const iq30 &x, const long &y)
{
   iq30 temp;
   temp.val = x.val | y;
   return temp;
}

inline iq30 & iq30 :: operator |= (const long &x)
{
   val |= x;
   return *this;
}

inline iq29 operator | (const iq29 &x, const long &y)
{
   iq29 temp;
   temp.val = x.val | y;
   return temp;
}

inline iq29 & iq29 :: operator |= (const long &x)
{
   val |= x;
   return *this;
}

inline iq28 operator | (const iq28 &x, const long &y)
{
   iq28 temp;
   temp.val = x.val | y;
   return temp;
}

inline iq28 & iq28 :: operator |= (const long &x)
{
   val |= x;
   return *this;
}

inline iq27 operator | (const iq27 &x, const long &y)
{
   iq27 temp;
   temp.val = x.val | y;
   return temp;
}

inline iq27 & iq27 :: operator |= (const long &x)
{
   val |= x;
   return *this;
}

inline iq26 operator | (const iq26 &x, const long &y)
{
   iq26 temp;
   temp.val = x.val | y;
   return temp;
}

inline iq26 & iq26 :: operator |= (const long &x)
{
   val |= x;
   return *this;
}

inline iq25 operator | (const iq25 &x, const long &y)
{
   iq25 temp;
   temp.val = x.val | y;
   return temp;
}

inline iq25 & iq25 :: operator |= (const long &x)
{
   val |= x;
   return *this;
}

inline iq24 operator | (const iq24 &x, const long &y)
{
   iq24 temp;
   temp.val = x.val | y;
   return temp;
}

inline iq24 & iq24 :: operator |= (const long &x)
{
   val |= x;
   return *this;
}

inline iq23 operator | (const iq23 &x, const long &y)
{
   iq23 temp;
   temp.val = x.val | y;
   return temp;
}

inline iq23 & iq23 :: operator |= (const long &x)
{
   val |= x;
   return *this;
}

inline iq22 operator | (const iq22 &x, const long &y)
{
   iq22 temp;
   temp.val = x.val | y;
   return temp;
}

inline iq22 & iq22 :: operator |= (const long &x)
{
   val |= x;
   return *this;
}

inline iq21 operator | (const iq21 &x, const long &y)
{
   iq21 temp;
   temp.val = x.val | y;
   return temp;
}

inline iq21 & iq21 :: operator |= (const long &x)
{
   val |= x;
   return *this;
}

inline iq20 operator | (const iq20 &x, const long &y)
{
   iq20 temp;
   temp.val = x.val | y;
   return temp;
}

inline iq20 & iq20 :: operator |= (const long &x)
{
   val |= x;
   return *this;
}

inline iq19 operator | (const iq19 &x, const long &y)
{
   iq19 temp;
   temp.val = x.val | y;
   return temp;
}

inline iq19 & iq19 :: operator |= (const long &x)
{
   val |= x;
   return *this;
}

inline iq18 operator | (const iq18 &x, const long &y)
{
   iq18 temp;
   temp.val = x.val | y;
   return temp;
}

inline iq18 & iq18 :: operator |= (const long &x)
{
   val |= x;
   return *this;
}

inline iq17 operator | (const iq17 &x, const long &y)
{
   iq17 temp;
   temp.val = x.val | y;
   return temp;
}

inline iq17 & iq17 :: operator |= (const long &x)
{
   val |= x;
   return *this;
}

inline iq16 operator | (const iq16 &x, const long &y)
{
   iq16 temp;
   temp.val = x.val | y;
   return temp;
}

inline iq16 & iq16 :: operator |= (const long &x)
{
   val |= x;
   return *this;
}

inline iq15 operator | (const iq15 &x, const long &y)
{
   iq15 temp;
   temp.val = x.val | y;
   return temp;
}

inline iq15 & iq15 :: operator |= (const long &x)
{
   val |= x;
   return *this;
}


inline iq14 operator | (const iq14 &x, const long &y)
{
   iq14 temp;
   temp.val = x.val | y;
   return temp;
}

inline iq14 & iq14 :: operator |= (const long &x)
{
   val |= x;
   return *this;
}

inline iq13 operator | (const iq13 &x, const long &y)
{
   iq13 temp;
   temp.val = x.val | y;
   return temp;
}

inline iq13 & iq13 :: operator |= (const long &x)
{
   val |= x;
   return *this;
}

inline iq12 operator | (const iq12 &x, const long &y)
{
   iq12 temp;
   temp.val = x.val | y;
   return temp;
}

inline iq12 & iq12 :: operator |= (const long &x)
{
   val |= x;
   return *this;
}

inline iq11 operator | (const iq11 &x, const long &y)
{
   iq11 temp;
   temp.val = x.val | y;
   return temp;
}

inline iq11 & iq11 :: operator |= (const long &x)
{
   val |= x;
   return *this;
}

inline iq10 operator | (const iq10 &x, const long &y)
{
   iq10 temp;
   temp.val = x.val | y;
   return temp;
}

inline iq10 & iq10 :: operator |= (const long &x)
{
   val |= x;
   return *this;
}

inline iq9 operator | (const iq9 &x, const long &y)
{
   iq9 temp;
   temp.val = x.val | y;
   return temp;
}

inline iq9 & iq9 :: operator |= (const long &x)
{
   val |= x;
   return *this;
}

inline iq8 operator | (const iq8 &x, const long &y)
{
   iq8 temp;
   temp.val = x.val | y;
   return temp;
}

inline iq8 & iq8 :: operator |= (const long &x)
{
   val |= x;
   return *this;
}

inline iq7 operator | (const iq7 &x, const long &y)
{
   iq7 temp;
   temp.val = x.val | y;
   return temp;
}

inline iq7 & iq7 :: operator |= (const long &x)
{
   val |= x;
   return *this;
}

inline iq6 operator | (const iq6 &x, const long &y)
{
   iq6 temp;
   temp.val = x.val | y;
   return temp;
}

inline iq6 & iq6 :: operator |= (const long &x)
{
   val |= x;
   return *this;
}

inline iq5 operator | (const iq5 &x, const long &y)
{
   iq5 temp;
   temp.val = x.val | y;
   return temp;
}

inline iq5 & iq5 :: operator |= (const long &x)
{
   val |= x;
   return *this;
}

inline iq4 operator | (const iq4 &x, const long &y)
{
   iq4 temp;
   temp.val = x.val | y;
   return temp;
}

inline iq4 & iq4 :: operator |= (const long &x)
{
   val |= x;
   return *this;
}

inline iq3 operator | (const iq3 &x, const long &y)
{
   iq3 temp;
   temp.val = x.val | y;
   return temp;
}

inline iq3 & iq3 :: operator |= (const long &x)
{
   val |= x;
   return *this;
}

inline iq2 operator | (const iq2 &x, const long &y)
{
   iq2 temp;
   temp.val = x.val | y;
   return temp;
}

inline iq2 & iq2 :: operator |= (const long &x)
{
   val |= x;
   return *this;
}

inline iq1 operator | (const iq1 &x, const long &y)
{
   iq1 temp;
   temp.val = x.val | y;
   return temp;
}

inline iq1 & iq1 :: operator |= (const long &x)
{
   val |= x;
   return *this;
}

//---------------------------------------------------------------------------
// Operators: "^", "^="
//---------------------------------------------------------------------------

inline iq operator ^ (const iq &x, const long &y)
{
   iq temp;
   temp.val = x.val ^ y;
   return temp;
}

inline iq & iq :: operator ^= (const long &x)
{
   val ^= x;
   return *this;
}

inline iq30 operator ^ (const iq30 &x, const long &y)
{
   iq30 temp;
   temp.val = x.val ^ y;
   return temp;
}

inline iq30 & iq30 :: operator ^= (const long &x)
{
   val ^= x;
   return *this;
}

inline iq29 operator ^ (const iq29 &x, const long &y)
{
   iq29 temp;
   temp.val = x.val ^ y;
   return temp;
}

inline iq29 & iq29 :: operator ^= (const long &x)
{
   val ^= x;
   return *this;
}

inline iq28 operator ^ (const iq28 &x, const long &y)
{
   iq28 temp;
   temp.val = x.val ^ y;
   return temp;
}

inline iq28 & iq28 :: operator ^= (const long &x)
{
   val ^= x;
   return *this;
}

inline iq27 operator ^ (const iq27 &x, const long &y)
{
   iq27 temp;
   temp.val = x.val ^ y;
   return temp;
}

inline iq27 & iq27 :: operator ^= (const long &x)
{
   val ^= x;
   return *this;
}

inline iq26 operator ^ (const iq26 &x, const long &y)
{
   iq26 temp;
   temp.val = x.val ^ y;
   return temp;
}

inline iq26 & iq26 :: operator ^= (const long &x)
{
   val ^= x;
   return *this;
}

inline iq25 operator ^ (const iq25 &x, const long &y)
{
   iq25 temp;
   temp.val = x.val ^ y;
   return temp;
}

inline iq25 & iq25 :: operator ^= (const long &x)
{
   val ^= x;
   return *this;
}

inline iq24 operator ^ (const iq24 &x, const long &y)
{
   iq24 temp;
   temp.val = x.val ^ y;
   return temp;
}

inline iq24 & iq24 :: operator ^= (const long &x)
{
   val ^= x;
   return *this;
}

inline iq23 operator ^ (const iq23 &x, const long &y)
{
   iq23 temp;
   temp.val = x.val ^ y;
   return temp;
}

inline iq23 & iq23 :: operator ^= (const long &x)
{
   val ^= x;
   return *this;
}

inline iq22 operator ^ (const iq22 &x, const long &y)
{
   iq22 temp;
   temp.val = x.val ^ y;
   return temp;
}

inline iq22 & iq22 :: operator ^= (const long &x)
{
   val ^= x;
   return *this;
}

inline iq21 operator ^ (const iq21 &x, const long &y)
{
   iq21 temp;
   temp.val = x.val ^ y;
   return temp;
}

inline iq21 & iq21 :: operator ^= (const long &x)
{
   val ^= x;
   return *this;
}

inline iq20 operator ^ (const iq20 &x, const long &y)
{
   iq20 temp;
   temp.val = x.val ^ y;
   return temp;
}

inline iq20 & iq20 :: operator ^= (const long &x)
{
   val ^= x;
   return *this;
}

inline iq19 operator ^ (const iq19 &x, const long &y)
{
   iq19 temp;
   temp.val = x.val ^ y;
   return temp;
}

inline iq19 & iq19 :: operator ^= (const long &x)
{
   val ^= x;
   return *this;
}

inline iq18 operator ^ (const iq18 &x, const long &y)
{
   iq18 temp;
   temp.val = x.val ^ y;
   return temp;
}

inline iq18 & iq18 :: operator ^= (const long &x)
{
   val ^= x;
   return *this;
}

inline iq17 operator ^ (const iq17 &x, const long &y)
{
   iq17 temp;
   temp.val = x.val ^ y;
   return temp;
}

inline iq17 & iq17 :: operator ^= (const long &x)
{
   val ^= x;
   return *this;
}

inline iq16 operator ^ (const iq16 &x, const long &y)
{
   iq16 temp;
   temp.val = x.val ^ y;
   return temp;
}

inline iq16 & iq16 :: operator ^= (const long &x)
{
   val ^= x;
   return *this;
}

inline iq15 operator ^ (const iq15 &x, const long &y)
{
   iq15 temp;
   temp.val = x.val ^ y;
   return temp;
}

inline iq15 & iq15 :: operator ^= (const long &x)
{
   val ^= x;
   return *this;
}

inline iq14 operator ^ (const iq14 &x, const long &y)
{
   iq14 temp;
   temp.val = x.val ^ y;
   return temp;
}

inline iq14 & iq14 :: operator ^= (const long &x)
{
   val ^= x;
   return *this;
}

inline iq13 operator ^ (const iq13 &x, const long &y)
{
   iq13 temp;
   temp.val = x.val ^ y;
   return temp;
}

inline iq13 & iq13 :: operator ^= (const long &x)
{
   val ^= x;
   return *this;
}

inline iq12 operator ^ (const iq12 &x, const long &y)
{
   iq12 temp;
   temp.val = x.val ^ y;
   return temp;
}

inline iq12 & iq12 :: operator ^= (const long &x)
{
   val ^= x;
   return *this;
}

inline iq11 operator ^ (const iq11 &x, const long &y)
{
   iq11 temp;
   temp.val = x.val ^ y;
   return temp;
}

inline iq11 & iq11 :: operator ^= (const long &x)
{
   val ^= x;
   return *this;
}

inline iq10 operator ^ (const iq10 &x, const long &y)
{
   iq10 temp;
   temp.val = x.val ^ y;
   return temp;
}

inline iq10 & iq10 :: operator ^= (const long &x)
{
   val ^= x;
   return *this;
}

inline iq9 operator ^ (const iq9 &x, const long &y)
{
   iq9 temp;
   temp.val = x.val ^ y;
   return temp;
}

inline iq9 & iq9 :: operator ^= (const long &x)
{
   val ^= x;
   return *this;
}

inline iq8 operator ^ (const iq8 &x, const long &y)
{
   iq8 temp;
   temp.val = x.val ^ y;
   return temp;
}

inline iq8 & iq8 :: operator ^= (const long &x)
{
   val ^= x;
   return *this;
}

inline iq7 operator ^ (const iq7 &x, const long &y)
{
   iq7 temp;
   temp.val = x.val ^ y;
   return temp;
}

inline iq7 & iq7 :: operator ^= (const long &x)
{
   val ^= x;
   return *this;
}

inline iq6 operator ^ (const iq6 &x, const long &y)
{
   iq6 temp;
   temp.val = x.val ^ y;
   return temp;
}

inline iq6 & iq6 :: operator ^= (const long &x)
{
   val ^= x;
   return *this;
}

inline iq5 operator ^ (const iq5 &x, const long &y)
{
   iq5 temp;
   temp.val = x.val ^ y;
   return temp;
}

inline iq5 & iq5 :: operator ^= (const long &x)
{
   val ^= x;
   return *this;
}

inline iq4 operator ^ (const iq4 &x, const long &y)
{
   iq4 temp;
   temp.val = x.val ^ y;
   return temp;
}

inline iq4 & iq4 :: operator ^= (const long &x)
{
   val ^= x;
   return *this;
}

inline iq3 operator ^ (const iq3 &x, const long &y)
{
   iq3 temp;
   temp.val = x.val ^ y;
   return temp;
}

inline iq3 & iq3 :: operator ^= (const long &x)
{
   val ^= x;
   return *this;
}

inline iq2 operator ^ (const iq2 &x, const long &y)
{
   iq2 temp;
   temp.val = x.val ^ y;
   return temp;
}

inline iq2 & iq2 :: operator ^= (const long &x)
{
   val ^= x;
   return *this;
}

inline iq1 operator ^ (const iq1 &x, const long &y)
{
   iq1 temp;
   temp.val = x.val ^ y;
   return temp;
}

inline iq1 & iq1 :: operator ^= (const long &x)
{
   val ^= x;
   return *this;
}
//###########################################################################
#else   // MATH_TYPE == FLOAT_MATH
//###########################################################################
// If FLOAT_MATH is used, the IQmath library function are replaced by
// equivalent floating point operations:
//===========================================================================
typedef   float   iq;
typedef   float   iq30;
typedef   float   iq29;
typedef   float   iq28;
typedef   float   iq27;
typedef   float   iq26;
typedef   float   iq25;
typedef   float   iq24;
typedef   float   iq23;
typedef   float   iq22;
typedef   float   iq21;
typedef   float   iq20;
typedef   float   iq19;
typedef   float   iq18;
typedef   float   iq17;
typedef   float   iq16;
typedef   float   iq15;
typedef   float   iq14;
typedef   float   iq13;
typedef   float   iq12;
typedef   float   iq11;
typedef   float   iq10;
typedef   float   iq9;
typedef   float   iq8;
typedef   float   iq7;
typedef   float   iq6;
typedef   float   iq5;
typedef   float   iq4;
typedef   float   iq3;
typedef   float   iq2;
typedef   float   iq1;
//---------------------------------------------------------------------------
#define   IQ(A)         A
#define   IQ30(A)       A
#define   IQ29(A)       A
#define   IQ28(A)       A
#define   IQ27(A)       A
#define   IQ26(A)       A
#define   IQ25(A)       A
#define   IQ24(A)       A
#define   IQ23(A)       A
#define   IQ22(A)       A
#define   IQ21(A)       A
#define   IQ20(A)       A
#define   IQ19(A)       A
#define   IQ18(A)       A
#define   IQ17(A)       A
#define   IQ16(A)       A
#define   IQ15(A)       A
#define   IQ14(A)       A
#define   IQ13(A)       A
#define   IQ12(A)       A
#define   IQ11(A)       A
#define   IQ10(A)       A
#define   IQ9(A)        A
#define   IQ8(A)        A
#define   IQ7(A)        A
#define   IQ6(A)        A
#define   IQ5(A)        A
#define   IQ4(A)        A
#define   IQ3(A)        A
#define   IQ2(A)        A
#define   IQ1(A)        A
//---------------------------------------------------------------------------
#define   IQtoF(A)      A
#define   IQ30toF(A)    A
#define   IQ29toF(A)    A
#define   IQ28toF(A)    A
#define   IQ27toF(A)    A
#define   IQ26toF(A)    A
#define   IQ25toF(A)    A
#define   IQ24toF(A)    A
#define   IQ23toF(A)    A
#define   IQ22toF(A)    A
#define   IQ21toF(A)    A
#define   IQ20toF(A)    A
#define   IQ19toF(A)    A
#define   IQ18toF(A)    A
#define   IQ17toF(A)    A
#define   IQ16toF(A)    A
#define   IQ15toF(A)    A
#define   IQ14toF(A)    A
#define   IQ13toF(A)    A
#define   IQ12toF(A)    A
#define   IQ11toF(A)    A
#define   IQ10toF(A)    A
#define   IQ9toF(A)     A
#define   IQ8toF(A)     A
#define   IQ7toF(A)     A
#define   IQ6toF(A)     A
#define   IQ5toF(A)     A
#define   IQ4toF(A)     A
#define   IQ3toF(A)     A
#define   IQ2toF(A)     A
#define   IQ1toF(A)     A
//---------------------------------------------------------------------------
extern  float _satf(float A, float Pos, float Neg);
#define   IQsat(A, Pos, Neg)    _satf(A, Pos, Neg)
//---------------------------------------------------------------------------
#define   IQtoIQ30(A)   A
#define   IQtoIQ29(A)   A
#define   IQtoIQ28(A)   A
#define   IQtoIQ27(A)   A
#define   IQtoIQ26(A)   A
#define   IQtoIQ25(A)   A
#define   IQtoIQ24(A)   A
#define   IQtoIQ23(A)   A
#define   IQtoIQ22(A)   A
#define   IQtoIQ21(A)   A
#define   IQtoIQ20(A)   A
#define   IQtoIQ19(A)   A
#define   IQtoIQ18(A)   A
#define   IQtoIQ17(A)   A
#define   IQtoIQ16(A)   A
#define   IQtoIQ15(A)   A
#define   IQtoIQ14(A)   A
#define   IQtoIQ13(A)   A
#define   IQtoIQ12(A)   A
#define   IQtoIQ11(A)   A
#define   IQtoIQ10(A)   A
#define   IQtoIQ9(A)    A
#define   IQtoIQ8(A)    A
#define   IQtoIQ7(A)    A
#define   IQtoIQ6(A)    A
#define   IQtoIQ5(A)    A
#define   IQtoIQ4(A)    A
#define   IQtoIQ3(A)    A
#define   IQtoIQ2(A)    A
#define   IQtoIQ1(A)    A
//---------------------------------------------------------------------------
#define   IQ30toIQ(A)   A
#define   IQ29toIQ(A)   A
#define   IQ28toIQ(A)   A
#define   IQ27toIQ(A)   A
#define   IQ26toIQ(A)   A
#define   IQ25toIQ(A)   A
#define   IQ24toIQ(A)   A
#define   IQ23toIQ(A)   A
#define   IQ22toIQ(A)   A
#define   IQ21toIQ(A)   A
#define   IQ20toIQ(A)   A
#define   IQ19toIQ(A)   A
#define   IQ18toIQ(A)   A
#define   IQ17toIQ(A)   A
#define   IQ16toIQ(A)   A
#define   IQ15toIQ(A)   A
#define   IQ14toIQ(A)   A
#define   IQ13toIQ(A)   A
#define   IQ12toIQ(A)   A
#define   IQ11toIQ(A)   A
#define   IQ10toIQ(A)   A
#define   IQ9toIQ(A)    A
#define   IQ8toIQ(A)    A
#define   IQ7toIQ(A)    A
#define   IQ6toIQ(A)    A
#define   IQ5toIQ(A)    A
#define   IQ4toIQ(A)    A
#define   IQ3toIQ(A)    A
#define   IQ2toIQ(A)    A
#define   IQ1toIQ(A)    A
//---------------------------------------------------------------------------
#define   IQtoQ15(A)    (short) (A##L * 32768.0L)
#define   IQtoQ14(A)    (short) (A##L * 16384.0L)
#define   IQtoQ13(A)    (short) (A##L * 8192.0L)
#define   IQtoQ12(A)    (short) (A##L * 4096.0L)
#define   IQtoQ11(A)    (short) (A##L * 2048.0L)
#define   IQtoQ10(A)    (short) (A##L * 1024.0L)
#define   IQtoQ9(A)     (short) (A##L * 512.0L)
#define   IQtoQ8(A)     (short) (A##L * 256.0L)
#define   IQtoQ7(A)     (short) (A##L * 128.0L)
#define   IQtoQ6(A)     (short) (A##L * 64.0L)
#define   IQtoQ5(A)     (short) (A##L * 32.0L)
#define   IQtoQ4(A)     (short) (A##L * 16.0L)
#define   IQtoQ3(A)     (short) (A##L * 8.0L)
#define   IQtoQ2(A)     (short) (A##L * 4.0L)
#define   IQtoQ1(A)     (short) (A##L * 2.0L)
//---------------------------------------------------------------------------
#define   Q15toIQ(A)    (((float) A) * 0.000030518)
#define   Q14toIQ(A)    (((float) A) * 0.000061035)
#define   Q13toIQ(A)    (((float) A) * 0.000122070)
#define   Q12toIQ(A)    (((float) A) * 0.000244141)
#define   Q11toIQ(A)    (((float) A) * 0.000488281)
#define   Q10toIQ(A)    (((float) A) * 0.000976563)
#define   Q9toIQ(A)     (((float) A) * 0.001953125)
#define   Q8toIQ(A)     (((float) A) * 0.003906250)
#define   Q7toIQ(A)     (((float) A) * 0.007812500)
#define   Q6toIQ(A)     (((float) A) * 0.015625000)
#define   Q5toIQ(A)     (((float) A) * 0.031250000)
#define   Q4toIQ(A)     (((float) A) * 0.062500000)
#define   Q3toIQ(A)     (((float) A) * 0.125000000)
#define   Q2toIQ(A)     (((float) A) * 0.250000000)
#define   Q1toIQ(A)     (((float) A) * 0.500000000)
//---------------------------------------------------------------------------
#define   IQrmpy(A,B)        (A * B)
#define   IQ30rmpy(A,B)      (A * B)
#define   IQ29rmpy(A,B)      (A * B)
#define   IQ28rmpy(A,B)      (A * B)
#define   IQ27rmpy(A,B)      (A * B)
#define   IQ26rmpy(A,B)      (A * B)
#define   IQ25rmpy(A,B)      (A * B)
#define   IQ24rmpy(A,B)      (A * B)
#define   IQ23rmpy(A,B)      (A * B)
#define   IQ22rmpy(A,B)      (A * B)
#define   IQ21rmpy(A,B)      (A * B)
#define   IQ20rmpy(A,B)      (A * B)
#define   IQ19rmpy(A,B)      (A * B)
#define   IQ18rmpy(A,B)      (A * B)
#define   IQ17rmpy(A,B)      (A * B)
#define   IQ16rmpy(A,B)      (A * B)
#define   IQ15rmpy(A,B)      (A * B)
#define   IQ15rmpy(A,B)      (A * B)
#define   IQ15rmpy(A,B)      (A * B)
//---------------------------------------------------------------------------
#define   IQrsmpy(A,B)       (A * B)
#define   IQ30rsmpy(A,B)     (A * B)
#define   IQ29rsmpy(A,B)     (A * B)
#define   IQ28rsmpy(A,B)     (A * B)
#define   IQ27rsmpy(A,B)     (A * B)
#define   IQ26rsmpy(A,B)     (A * B)
#define   IQ25rsmpy(A,B)     (A * B)
#define   IQ24rsmpy(A,B)     (A * B)
#define   IQ23rsmpy(A,B)     (A * B)
#define   IQ22rsmpy(A,B)     (A * B)
#define   IQ21rsmpy(A,B)     (A * B)
#define   IQ20rsmpy(A,B)     (A * B)
#define   IQ19rsmpy(A,B)     (A * B)
#define   IQ18rsmpy(A,B)     (A * B)
#define   IQ17rsmpy(A,B)     (A * B)
#define   IQ16rsmpy(A,B)     (A * B)
#define   IQ15rsmpy(A,B)     (A * B)
#define   IQ14rsmpy(A,B)     (A * B)
#define   IQ13rsmpy(A,B)     (A * B)
#define   IQ12rsmpy(A,B)     (A * B)
#define   IQ11rsmpy(A,B)     (A * B)
#define   IQ10rsmpy(A,B)     (A * B)
#define   IQ9rsmpy(A,B)      (A * B)
#define   IQ8rsmpy(A,B)      (A * B)
#define   IQ7rsmpy(A,B)      (A * B)
#define   IQ6rsmpy(A,B)      (A * B)
#define   IQ5rsmpy(A,B)      (A * B)
#define   IQ4rsmpy(A,B)      (A * B)
#define   IQ3rsmpy(A,B)      (A * B)
#define   IQ2rsmpy(A,B)      (A * B)
#define   IQ1rsmpy(A,B)      (A * B)
//---------------------------------------------------------------------------
#define   IQsin(A)           sin(A)
#define   IQ30sin(A)         sin(A)
#define   IQ29sin(A)         sin(A)
#define   IQ28sin(A)         sin(A)
#define   IQ27sin(A)         sin(A)
#define   IQ26sin(A)         sin(A)
#define   IQ25sin(A)         sin(A)
#define   IQ24sin(A)         sin(A)
#define   IQ23sin(A)         sin(A)
#define   IQ22sin(A)         sin(A)
#define   IQ21sin(A)         sin(A)
#define   IQ20sin(A)         sin(A)
#define   IQ19sin(A)         sin(A)
#define   IQ18sin(A)         sin(A)
#define   IQ17sin(A)         sin(A)
#define   IQ16sin(A)         sin(A)
#define   IQ15sin(A)         sin(A)
#define   IQ14sin(A)         sin(A)
#define   IQ13sin(A)         sin(A)
#define   IQ12sin(A)         sin(A)
#define   IQ11sin(A)         sin(A)
#define   IQ10sin(A)         sin(A)
#define   IQ9sin(A)          sin(A)
#define   IQ8sin(A)          sin(A)
#define   IQ7sin(A)          sin(A)
#define   IQ6sin(A)          sin(A)
#define   IQ5sin(A)          sin(A)
#define   IQ4sin(A)          sin(A)
#define   IQ3sin(A)          sin(A)
#define   IQ2sin(A)          sin(A)
#define   IQ1sin(A)          sin(A)
//---------------------------------------------------------------------------
#define   IQsinPU(A)         sin(A*6.283185307)
#define   IQ30sinPU(A)       sin(A*6.283185307)
#define   IQ29sinPU(A)       sin(A*6.283185307)
#define   IQ28sinPU(A)       sin(A*6.283185307)
#define   IQ27sinPU(A)       sin(A*6.283185307)
#define   IQ26sinPU(A)       sin(A*6.283185307)
#define   IQ25sinPU(A)       sin(A*6.283185307)
#define   IQ24sinPU(A)       sin(A*6.283185307)
#define   IQ23sinPU(A)       sin(A*6.283185307)
#define   IQ22sinPU(A)       sin(A*6.283185307)
#define   IQ21sinPU(A)       sin(A*6.283185307)
#define   IQ20sinPU(A)       sin(A*6.283185307)
#define   IQ19sinPU(A)       sin(A*6.283185307)
#define   IQ18sinPU(A)       sin(A*6.283185307)
#define   IQ17sinPU(A)       sin(A*6.283185307)
#define   IQ16sinPU(A)       sin(A*6.283185307)
#define   IQ15sinPU(A)       sin(A*6.283185307)
#define   IQ14sinPU(A)       sin(A*6.283185307)
#define   IQ13sinPU(A)       sin(A*6.283185307)
#define   IQ12sinPU(A)       sin(A*6.283185307)
#define   IQ11sinPU(A)       sin(A*6.283185307)
#define   IQ10sinPU(A)       sin(A*6.283185307)
#define   IQ9sinPU(A)        sin(A*6.283185307)
#define   IQ8sinPU(A)        sin(A*6.283185307)
#define   IQ7sinPU(A)        sin(A*6.283185307)
#define   IQ6sinPU(A)        sin(A*6.283185307)
#define   IQ5sinPU(A)        sin(A*6.283185307)
#define   IQ4sinPU(A)        sin(A*6.283185307)
#define   IQ3sinPU(A)        sin(A*6.283185307)
#define   IQ2sinPU(A)        sin(A*6.283185307)
#define   IQ1sinPU(A)        sin(A*6.283185307)
//---------------------------------------------------------------------------
#define   IQasin(A)          asin(A)
#define   IQ29asin(A)        asin(A)
#define   IQ28asin(A)        asin(A)
#define   IQ27asin(A)        asin(A)
#define   IQ26asin(A)        asin(A)
#define   IQ25asin(A)        asin(A)
#define   IQ24asin(A)        asin(A)
#define   IQ23asin(A)        asin(A)
#define   IQ22asin(A)        asin(A)
#define   IQ21asin(A)        asin(A)
#define   IQ20asin(A)        asin(A)
#define   IQ19asin(A)        asin(A)
#define   IQ18asin(A)        asin(A)
#define   IQ17asin(A)        asin(A)
#define   IQ16asin(A)        asin(A)
#define   IQ15asin(A)        asin(A)
#define   IQ14asin(A)        asin(A)
#define   IQ13asin(A)        asin(A)
#define   IQ12asin(A)        asin(A)
#define   IQ11asin(A)        asin(A)
#define   IQ10asin(A)        asin(A)
#define   IQ9asin(A)         asin(A)
#define   IQ8asin(A)         asin(A)
#define   IQ7asin(A)         asin(A)
#define   IQ6asin(A)         asin(A)
#define   IQ5asin(A)         asin(A)
#define   IQ4asin(A)         asin(A)
#define   IQ3asin(A)         asin(A)
#define   IQ2asin(A)         asin(A)
#define   IQ1asin(A)         asin(A)
//---------------------------------------------------------------------------
#define   IQcos(A)           cos(A)
#define   IQ30cos(A)         cos(A)
#define   IQ29cos(A)         cos(A)
#define   IQ28cos(A)         cos(A)
#define   IQ27cos(A)         cos(A)
#define   IQ26cos(A)         cos(A)
#define   IQ25cos(A)         cos(A)
#define   IQ24cos(A)         cos(A)
#define   IQ23cos(A)         cos(A)
#define   IQ22cos(A)         cos(A)
#define   IQ21cos(A)         cos(A)
#define   IQ20cos(A)         cos(A)
#define   IQ19cos(A)         cos(A)
#define   IQ18cos(A)         cos(A)
#define   IQ17cos(A)         cos(A)
#define   IQ16cos(A)         cos(A)
#define   IQ15cos(A)         cos(A)
#define   IQ14cos(A)         cos(A)
#define   IQ13cos(A)         cos(A)
#define   IQ12cos(A)         cos(A)
#define   IQ11cos(A)         cos(A)
#define   IQ10cos(A)         cos(A)
#define   IQ9cos(A)          cos(A)
#define   IQ8cos(A)          cos(A)
#define   IQ7cos(A)          cos(A)
#define   IQ6cos(A)          cos(A)
#define   IQ5cos(A)          cos(A)
#define   IQ4cos(A)          cos(A)
#define   IQ3cos(A)          cos(A)
#define   IQ2cos(A)          cos(A)
#define   IQ1cos(A)          cos(A)
//---------------------------------------------------------------------------
#define   IQcosPU(A)         cos(A*6.283185307)
#define   IQ30cosPU(A)       cos(A*6.283185307)
#define   IQ29cosPU(A)       cos(A*6.283185307)
#define   IQ28cosPU(A)       cos(A*6.283185307)
#define   IQ27cosPU(A)       cos(A*6.283185307)
#define   IQ26cosPU(A)       cos(A*6.283185307)
#define   IQ25cosPU(A)       cos(A*6.283185307)
#define   IQ24cosPU(A)       cos(A*6.283185307)
#define   IQ23cosPU(A)       cos(A*6.283185307)
#define   IQ22cosPU(A)       cos(A*6.283185307)
#define   IQ21cosPU(A)       cos(A*6.283185307)
#define   IQ20cosPU(A)       cos(A*6.283185307)
#define   IQ19cosPU(A)       cos(A*6.283185307)
#define   IQ18cosPU(A)       cos(A*6.283185307)
#define   IQ17cosPU(A)       cos(A*6.283185307)
#define   IQ16cosPU(A)       cos(A*6.283185307)
#define   IQ15cosPU(A)       cos(A*6.283185307)
#define   IQ14cosPU(A)       cos(A*6.283185307)
#define   IQ13cosPU(A)       cos(A*6.283185307)
#define   IQ12cosPU(A)       cos(A*6.283185307)
#define   IQ11cosPU(A)       cos(A*6.283185307)
#define   IQ10cosPU(A)       cos(A*6.283185307)
#define   IQ9cosPU(A)        cos(A*6.283185307)
#define   IQ8cosPU(A)        cos(A*6.283185307)
#define   IQ7cosPU(A)        cos(A*6.283185307)
#define   IQ6cosPU(A)        cos(A*6.283185307)
#define   IQ5cosPU(A)        cos(A*6.283185307)
#define   IQ4cosPU(A)        cos(A*6.283185307)
#define   IQ3cosPU(A)        cos(A*6.283185307)
#define   IQ2cosPU(A)        cos(A*6.283185307)
#define   IQ1cosPU(A)        cos(A*6.283185307)
//---------------------------------------------------------------------------
#define   IQacos(A)          acos(A)
#define   IQ29acos(A)        acos(A)
#define   IQ28acos(A)        acos(A)
#define   IQ27acos(A)        acos(A)
#define   IQ26acos(A)        acos(A)
#define   IQ25acos(A)        acos(A)
#define   IQ24acos(A)        acos(A)
#define   IQ23acos(A)        acos(A)
#define   IQ22acos(A)        acos(A)
#define   IQ21acos(A)        acos(A)
#define   IQ20acos(A)        acos(A)
#define   IQ19acos(A)        acos(A)
#define   IQ18acos(A)        acos(A)
#define   IQ17acos(A)        acos(A)
#define   IQ16acos(A)        acos(A)
#define   IQ15acos(A)        acos(A)
#define   IQ14acos(A)        acos(A)
#define   IQ13acos(A)        acos(A)
#define   IQ12acos(A)        acos(A)
#define   IQ11acos(A)        acos(A)
#define   IQ10acos(A)        acos(A)
#define   IQ9acos(A)         acos(A)
#define   IQ8acos(A)         acos(A)
#define   IQ7acos(A)         acos(A)
#define   IQ6acos(A)         acos(A)
#define   IQ5acos(A)         acos(A)
#define   IQ4acos(A)         acos(A)
#define   IQ3acos(A)         acos(A)
#define   IQ2acos(A)         acos(A)
#define   IQ1acos(A)         acos(A)
//---------------------------------------------------------------------------
#define   IQatan(A)          atan(A)
#define   IQ30atan(A)        atan(A)
#define   IQ29atan(A)        atan(A)
#define   IQ28atan(A)        atan(A)
#define   IQ27atan(A)        atan(A)
#define   IQ26atan(A)        atan(A)
#define   IQ25atan(A)        atan(A)
#define   IQ24atan(A)        atan(A)
#define   IQ23atan(A)        atan(A)
#define   IQ22atan(A)        atan(A)
#define   IQ21atan(A)        atan(A)
#define   IQ20atan(A)        atan(A)
#define   IQ19atan(A)        atan(A)
#define   IQ18atan(A)        atan(A)
#define   IQ17atan(A)        atan(A)
#define   IQ16atan(A)        atan(A)
#define   IQ15atan(A)        atan(A)
#define   IQ14atan(A)        atan(A)
#define   IQ13atan(A)        atan(A)
#define   IQ12atan(A)        atan(A)
#define   IQ11atan(A)        atan(A)
#define   IQ10atan(A)        atan(A)
#define   IQ9atan(A)         atan(A)
#define   IQ8atan(A)         atan(A)
#define   IQ7atan(A)         atan(A)
#define   IQ6atan(A)         atan(A)
#define   IQ5atan(A)         atan(A)
#define   IQ4atan(A)         atan(A)
#define   IQ3atan(A)         atan(A)
#define   IQ2atan(A)         atan(A)
#define   IQ1atan(A)         atan(A)
//---------------------------------------------------------------------------
#define   IQatan2(A,B)       atan2(A,B)
#define   IQ30atan2(A,B)     atan2(A,B)
#define   IQ29atan2(A,B)     atan2(A,B)
#define   IQ28atan2(A,B)     atan2(A,B)
#define   IQ27atan2(A,B)     atan2(A,B)
#define   IQ26atan2(A,B)     atan2(A,B)
#define   IQ25atan2(A,B)     atan2(A,B)
#define   IQ24atan2(A,B)     atan2(A,B)
#define   IQ23atan2(A,B)     atan2(A,B)
#define   IQ22atan2(A,B)     atan2(A,B)
#define   IQ21atan2(A,B)     atan2(A,B)
#define   IQ20atan2(A,B)     atan2(A,B)
#define   IQ19atan2(A,B)     atan2(A,B)
#define   IQ18atan2(A,B)     atan2(A,B)
#define   IQ17atan2(A,B)     atan2(A,B)
#define   IQ16atan2(A,B)     atan2(A,B)
#define   IQ15atan2(A,B)     atan2(A,B)
#define   IQ14atan2(A,B)     atan2(A,B)
#define   IQ13atan2(A,B)     atan2(A,B)
#define   IQ12atan2(A,B)     atan2(A,B)
#define   IQ11atan2(A,B)     atan2(A,B)
#define   IQ10atan2(A,B)     atan2(A,B)
#define   IQ9atan2(A,B)      atan2(A,B)
#define   IQ8atan2(A,B)      atan2(A,B)
#define   IQ7atan2(A,B)      atan2(A,B)
#define   IQ6atan2(A,B)      atan2(A,B)
#define   IQ5atan2(A,B)      atan2(A,B)
#define   IQ4atan2(A,B)      atan2(A,B)
#define   IQ3atan2(A,B)      atan2(A,B)
#define   IQ2atan2(A,B)      atan2(A,B)
#define   IQ1atan2(A,B)      atan2(A,B)
//---------------------------------------------------------------------------
#define   IQatan2PU(A,B)     ((atan2(A,B)*(1.0/6.283185307)) >= 0.0 ? (atan2(A,B)*(1.0/6.283185307)):1.0 + (atan2(A,B)*(1.0/6.283185307)))
#define   IQ30atan2PU(A,B)   ((atan2(A,B)*(1.0/6.283185307)) >= 0.0 ? (atan2(A,B)*(1.0/6.283185307)):1.0 + (atan2(A,B)*(1.0/6.283185307)))
#define   IQ29atan2PU(A,B)   ((atan2(A,B)*(1.0/6.283185307)) >= 0.0 ? (atan2(A,B)*(1.0/6.283185307)):1.0 + (atan2(A,B)*(1.0/6.283185307)))
#define   IQ28atan2PU(A,B)   ((atan2(A,B)*(1.0/6.283185307)) >= 0.0 ? (atan2(A,B)*(1.0/6.283185307)):1.0 + (atan2(A,B)*(1.0/6.283185307)))
#define   IQ27atan2PU(A,B)   ((atan2(A,B)*(1.0/6.283185307)) >= 0.0 ? (atan2(A,B)*(1.0/6.283185307)):1.0 + (atan2(A,B)*(1.0/6.283185307)))
#define   IQ26atan2PU(A,B)   ((atan2(A,B)*(1.0/6.283185307)) >= 0.0 ? (atan2(A,B)*(1.0/6.283185307)):1.0 + (atan2(A,B)*(1.0/6.283185307)))
#define   IQ25atan2PU(A,B)   ((atan2(A,B)*(1.0/6.283185307)) >= 0.0 ? (atan2(A,B)*(1.0/6.283185307)):1.0 + (atan2(A,B)*(1.0/6.283185307)))
#define   IQ24atan2PU(A,B)   ((atan2(A,B)*(1.0/6.283185307)) >= 0.0 ? (atan2(A,B)*(1.0/6.283185307)):1.0 + (atan2(A,B)*(1.0/6.283185307)))
#define   IQ23atan2PU(A,B)   ((atan2(A,B)*(1.0/6.283185307)) >= 0.0 ? (atan2(A,B)*(1.0/6.283185307)):1.0 + (atan2(A,B)*(1.0/6.283185307)))
#define   IQ22atan2PU(A,B)   ((atan2(A,B)*(1.0/6.283185307)) >= 0.0 ? (atan2(A,B)*(1.0/6.283185307)):1.0 + (atan2(A,B)*(1.0/6.283185307)))
#define   IQ21atan2PU(A,B)   ((atan2(A,B)*(1.0/6.283185307)) >= 0.0 ? (atan2(A,B)*(1.0/6.283185307)):1.0 + (atan2(A,B)*(1.0/6.283185307)))
#define   IQ20atan2PU(A,B)   ((atan2(A,B)*(1.0/6.283185307)) >= 0.0 ? (atan2(A,B)*(1.0/6.283185307)):1.0 + (atan2(A,B)*(1.0/6.283185307)))
#define   IQ19atan2PU(A,B)   ((atan2(A,B)*(1.0/6.283185307)) >= 0.0 ? (atan2(A,B)*(1.0/6.283185307)):1.0 + (atan2(A,B)*(1.0/6.283185307)))
#define   IQ18atan2PU(A,B)   ((atan2(A,B)*(1.0/6.283185307)) >= 0.0 ? (atan2(A,B)*(1.0/6.283185307)):1.0 + (atan2(A,B)*(1.0/6.283185307)))
#define   IQ17atan2PU(A,B)   ((atan2(A,B)*(1.0/6.283185307)) >= 0.0 ? (atan2(A,B)*(1.0/6.283185307)):1.0 + (atan2(A,B)*(1.0/6.283185307)))
#define   IQ16atan2PU(A,B)   ((atan2(A,B)*(1.0/6.283185307)) >= 0.0 ? (atan2(A,B)*(1.0/6.283185307)):1.0 + (atan2(A,B)*(1.0/6.283185307)))
#define   IQ15atan2PU(A,B)   ((atan2(A,B)*(1.0/6.283185307)) >= 0.0 ? (atan2(A,B)*(1.0/6.283185307)):1.0 + (atan2(A,B)*(1.0/6.283185307)))
#define   IQ14atan2PU(A,B)   ((atan2(A,B)*(1.0/6.283185307)) >= 0.0 ? (atan2(A,B)*(1.0/6.283185307)):1.0 + (atan2(A,B)*(1.0/6.283185307)))
#define   IQ13atan2PU(A,B)   ((atan2(A,B)*(1.0/6.283185307)) >= 0.0 ? (atan2(A,B)*(1.0/6.283185307)):1.0 + (atan2(A,B)*(1.0/6.283185307)))
#define   IQ12atan2PU(A,B)   ((atan2(A,B)*(1.0/6.283185307)) >= 0.0 ? (atan2(A,B)*(1.0/6.283185307)):1.0 + (atan2(A,B)*(1.0/6.283185307)))
#define   IQ11atan2PU(A,B)   ((atan2(A,B)*(1.0/6.283185307)) >= 0.0 ? (atan2(A,B)*(1.0/6.283185307)):1.0 + (atan2(A,B)*(1.0/6.283185307)))
#define   IQ10atan2PU(A,B)   ((atan2(A,B)*(1.0/6.283185307)) >= 0.0 ? (atan2(A,B)*(1.0/6.283185307)):1.0 + (atan2(A,B)*(1.0/6.283185307)))
#define   IQ9atan2PU(A,B)    ((atan2(A,B)*(1.0/6.283185307)) >= 0.0 ? (atan2(A,B)*(1.0/6.283185307)):1.0 + (atan2(A,B)*(1.0/6.283185307)))
#define   IQ8atan2PU(A,B)    ((atan2(A,B)*(1.0/6.283185307)) >= 0.0 ? (atan2(A,B)*(1.0/6.283185307)):1.0 + (atan2(A,B)*(1.0/6.283185307)))
#define   IQ7atan2PU(A,B)    ((atan2(A,B)*(1.0/6.283185307)) >= 0.0 ? (atan2(A,B)*(1.0/6.283185307)):1.0 + (atan2(A,B)*(1.0/6.283185307)))
#define   IQ6atan2PU(A,B)    ((atan2(A,B)*(1.0/6.283185307)) >= 0.0 ? (atan2(A,B)*(1.0/6.283185307)):1.0 + (atan2(A,B)*(1.0/6.283185307)))
#define   IQ5atan2PU(A,B)    ((atan2(A,B)*(1.0/6.283185307)) >= 0.0 ? (atan2(A,B)*(1.0/6.283185307)):1.0 + (atan2(A,B)*(1.0/6.283185307)))
#define   IQ4atan2PU(A,B)    ((atan2(A,B)*(1.0/6.283185307)) >= 0.0 ? (atan2(A,B)*(1.0/6.283185307)):1.0 + (atan2(A,B)*(1.0/6.283185307)))
#define   IQ3atan2PU(A,B)    ((atan2(A,B)*(1.0/6.283185307)) >= 0.0 ? (atan2(A,B)*(1.0/6.283185307)):1.0 + (atan2(A,B)*(1.0/6.283185307)))
#define   IQ2atan2PU(A,B)    ((atan2(A,B)*(1.0/6.283185307)) >= 0.0 ? (atan2(A,B)*(1.0/6.283185307)):1.0 + (atan2(A,B)*(1.0/6.283185307)))
#define   IQ1atan2PU(A,B)    ((atan2(A,B)*(1.0/6.283185307)) >= 0.0 ? (atan2(A,B)*(1.0/6.283185307)):1.0 + (atan2(A,B)*(1.0/6.283185307)))
//---------------------------------------------------------------------------
#define   IQsqrt(A)          sqrt(A)
#define   IQ30sqrt(A)        sqrt(A)
#define   IQ29sqrt(A)        sqrt(A)
#define   IQ28sqrt(A)        sqrt(A)
#define   IQ27sqrt(A)        sqrt(A)
#define   IQ26sqrt(A)        sqrt(A)
#define   IQ25sqrt(A)        sqrt(A)
#define   IQ24sqrt(A)        sqrt(A)
#define   IQ23sqrt(A)        sqrt(A)
#define   IQ22sqrt(A)        sqrt(A)
#define   IQ21sqrt(A)        sqrt(A)
#define   IQ20sqrt(A)        sqrt(A)
#define   IQ19sqrt(A)        sqrt(A)
#define   IQ18sqrt(A)        sqrt(A)
#define   IQ17sqrt(A)        sqrt(A)
#define   IQ16sqrt(A)        sqrt(A)
#define   IQ15sqrt(A)        sqrt(A)
#define   IQ14sqrt(A)        sqrt(A)
#define   IQ13sqrt(A)        sqrt(A)
#define   IQ12sqrt(A)        sqrt(A)
#define   IQ11sqrt(A)        sqrt(A)
#define   IQ10sqrt(A)        sqrt(A)
#define   IQ9sqrt(A)         sqrt(A)
#define   IQ8sqrt(A)         sqrt(A)
#define   IQ7sqrt(A)         sqrt(A)
#define   IQ6sqrt(A)         sqrt(A)
#define   IQ5sqrt(A)         sqrt(A)
#define   IQ4sqrt(A)         sqrt(A)
#define   IQ3sqrt(A)         sqrt(A)
#define   IQ2sqrt(A)         sqrt(A)
#define   IQ1sqrt(A)         sqrt(A)
//---------------------------------------------------------------------------
#define   IQisqrt(A)         (1.0/sqrt(A))
#define   IQ30isqrt(A)       (1.0/sqrt(A))
#define   IQ29isqrt(A)       (1.0/sqrt(A))
#define   IQ28isqrt(A)       (1.0/sqrt(A))
#define   IQ27isqrt(A)       (1.0/sqrt(A))
#define   IQ26isqrt(A)       (1.0/sqrt(A))
#define   IQ25isqrt(A)       (1.0/sqrt(A))
#define   IQ24isqrt(A)       (1.0/sqrt(A))
#define   IQ23isqrt(A)       (1.0/sqrt(A))
#define   IQ22isqrt(A)       (1.0/sqrt(A))
#define   IQ21isqrt(A)       (1.0/sqrt(A))
#define   IQ20isqrt(A)       (1.0/sqrt(A))
#define   IQ19isqrt(A)       (1.0/sqrt(A))
#define   IQ18isqrt(A)       (1.0/sqrt(A))
#define   IQ17isqrt(A)       (1.0/sqrt(A))
#define   IQ16isqrt(A)       (1.0/sqrt(A))
#define   IQ15isqrt(A)       (1.0/sqrt(A))
#define   IQ14isqrt(A)       (1.0/sqrt(A))
#define   IQ13isqrt(A)       (1.0/sqrt(A))
#define   IQ12isqrt(A)       (1.0/sqrt(A))
#define   IQ11isqrt(A)       (1.0/sqrt(A))
#define   IQ10isqrt(A)       (1.0/sqrt(A))
#define   IQ9isqrt(A)        (1.0/sqrt(A))
#define   IQ8isqrt(A)        (1.0/sqrt(A))
#define   IQ7isqrt(A)        (1.0/sqrt(A))
#define   IQ6isqrt(A)        (1.0/sqrt(A))
#define   IQ5isqrt(A)        (1.0/sqrt(A))
#define   IQ4isqrt(A)        (1.0/sqrt(A))
#define   IQ3isqrt(A)        (1.0/sqrt(A))
#define   IQ2isqrt(A)        (1.0/sqrt(A))
#define   IQ1isqrt(A)        (1.0/sqrt(A))
//---------------------------------------------------------------------------
#define   IQexp(A)           exp(A)
#define   IQ30exp(A)         exp(A)
#define   IQ29exp(A)         exp(A)
#define   IQ28exp(A)         exp(A)
#define   IQ27exp(A)         exp(A)
#define   IQ26exp(A)         exp(A)
#define   IQ25exp(A)         exp(A)
#define   IQ24exp(A)         exp(A)
#define   IQ23exp(A)         exp(A)
#define   IQ22exp(A)         exp(A)
#define   IQ21exp(A)         exp(A)
#define   IQ20exp(A)         exp(A)
#define   IQ19exp(A)         exp(A)
#define   IQ18exp(A)         exp(A)
#define   IQ17exp(A)         exp(A)
#define   IQ16exp(A)         exp(A)
#define   IQ15exp(A)         exp(A)
#define   IQ14exp(A)         exp(A)
#define   IQ13exp(A)         exp(A)
#define   IQ12exp(A)         exp(A)
#define   IQ11exp(A)         exp(A)
#define   IQ10exp(A)         exp(A)
#define   IQ9exp(A)          exp(A)
#define   IQ8exp(A)          exp(A)
#define   IQ7exp(A)          exp(A)
#define   IQ6exp(A)          exp(A)
#define   IQ5exp(A)          exp(A)
#define   IQ4exp(A)          exp(A)
#define   IQ3exp(A)          exp(A)
#define   IQ2exp(A)          exp(A)
#define   IQ1exp(A)          exp(A)
//---------------------------------------------------------------------------
#define   IQint(A)           ((long) A)
#define   IQ30int(A)         ((long) A)
#define   IQ29int(A)         ((long) A)
#define   IQ28int(A)         ((long) A)
#define   IQ27int(A)         ((long) A)
#define   IQ26int(A)         ((long) A)
#define   IQ25int(A)         ((long) A)
#define   IQ24int(A)         ((long) A)
#define   IQ23int(A)         ((long) A)
#define   IQ22int(A)         ((long) A)
#define   IQ21int(A)         ((long) A)
#define   IQ20int(A)         ((long) A)
#define   IQ19int(A)         ((long) A)
#define   IQ18int(A)         ((long) A)
#define   IQ17int(A)         ((long) A)
#define   IQ16int(A)         ((long) A)
#define   IQ15int(A)         ((long) A)
#define   IQ14int(A)         ((long) A)
#define   IQ13int(A)         ((long) A)
#define   IQ12int(A)         ((long) A)
#define   IQ11int(A)         ((long) A)
#define   IQ10int(A)         ((long) A)
#define   IQ9int(A)          ((long) A)
#define   IQ8int(A)          ((long) A)
#define   IQ7int(A)          ((long) A)
#define   IQ6int(A)          ((long) A)
#define   IQ5int(A)          ((long) A)
#define   IQ4int(A)          ((long) A)
#define   IQ3int(A)          ((long) A)
#define   IQ2int(A)          ((long) A)
#define   IQ1int(A)          ((long) A)
//---------------------------------------------------------------------------
#define   IQfrac(A)          (A - (float)((long) A))
#define   IQ30frac(A)        (A - (float)((long) A))
#define   IQ29frac(A)        (A - (float)((long) A))
#define   IQ28frac(A)        (A - (float)((long) A))
#define   IQ27frac(A)        (A - (float)((long) A))
#define   IQ26frac(A)        (A - (float)((long) A))
#define   IQ25frac(A)        (A - (float)((long) A))
#define   IQ24frac(A)        (A - (float)((long) A))
#define   IQ23frac(A)        (A - (float)((long) A))
#define   IQ22frac(A)        (A - (float)((long) A))
#define   IQ21frac(A)        (A - (float)((long) A))
#define   IQ20frac(A)        (A - (float)((long) A))
#define   IQ19frac(A)        (A - (float)((long) A))
#define   IQ18frac(A)        (A - (float)((long) A))
#define   IQ17frac(A)        (A - (float)((long) A))
#define   IQ16frac(A)        (A - (float)((long) A))
#define   IQ15frac(A)        (A - (float)((long) A))
#define   IQ14frac(A)        (A - (float)((long) A))
#define   IQ13frac(A)        (A - (float)((long) A))
#define   IQ12frac(A)        (A - (float)((long) A))
#define   IQ11frac(A)        (A - (float)((long) A))
#define   IQ10frac(A)        (A - (float)((long) A))
#define   IQ9frac(A)         (A - (float)((long) A))
#define   IQ8frac(A)         (A - (float)((long) A))
#define   IQ7frac(A)         (A - (float)((long) A))
#define   IQ6frac(A)         (A - (float)((long) A))
#define   IQ5frac(A)         (A - (float)((long) A))
#define   IQ4frac(A)         (A - (float)((long) A))
#define   IQ3frac(A)         (A - (float)((long) A))
#define   IQ2frac(A)         (A - (float)((long) A))
#define   IQ1frac(A)         (A - (float)((long) A))
//---------------------------------------------------------------------------
#define   IQmpyIQX(A, IQA, B, IQB)    (A*B)
#define   IQ30mpyIQX(A, IQA, B, IQB)  (A*B)
#define   IQ29mpyIQX(A, IQA, B, IQB)  (A*B)
#define   IQ28mpyIQX(A, IQA, B, IQB)  (A*B)
#define   IQ27mpyIQX(A, IQA, B, IQB)  (A*B)
#define   IQ26mpyIQX(A, IQA, B, IQB)  (A*B)
#define   IQ25mpyIQX(A, IQA, B, IQB)  (A*B)
#define   IQ24mpyIQX(A, IQA, B, IQB)  (A*B)
#define   IQ23mpyIQX(A, IQA, B, IQB)  (A*B)
#define   IQ22mpyIQX(A, IQA, B, IQB)  (A*B)
#define   IQ21mpyIQX(A, IQA, B, IQB)  (A*B)
#define   IQ20mpyIQX(A, IQA, B, IQB)  (A*B)
#define   IQ19mpyIQX(A, IQA, B, IQB)  (A*B)
#define   IQ18mpyIQX(A, IQA, B, IQB)  (A*B)
#define   IQ17mpyIQX(A, IQA, B, IQB)  (A*B)
#define   IQ16mpyIQX(A, IQA, B, IQB)  (A*B)
#define   IQ15mpyIQX(A, IQA, B, IQB)  (A*B)
#define   IQ14mpyIQX(A, IQA, B, IQB)  (A*B)
#define   IQ13mpyIQX(A, IQA, B, IQB)  (A*B)
#define   IQ12mpyIQX(A, IQA, B, IQB)  (A*B)
#define   IQ11mpyIQX(A, IQA, B, IQB)  (A*B)
#define   IQ10mpyIQX(A, IQA, B, IQB)  (A*B)
#define   IQ9mpyIQX(A, IQA, B, IQB)  (A*B)
#define   IQ8mpyIQX(A, IQA, B, IQB)  (A*B)
#define   IQ7mpyIQX(A, IQA, B, IQB)  (A*B)
#define   IQ6mpyIQX(A, IQA, B, IQB)  (A*B)
#define   IQ5mpyIQX(A, IQA, B, IQB)  (A*B)
#define   IQ4mpyIQX(A, IQA, B, IQB)  (A*B)
#define   IQ3mpyIQX(A, IQA, B, IQB)  (A*B)
#define   IQ2mpyIQX(A, IQA, B, IQB)  (A*B)
#define   IQ1mpyIQX(A, IQA, B, IQB)  (A*B)
//---------------------------------------------------------------------------
#define   IQmpyI32(A,B)      (A * (float) B)
#define   IQ30mpyI32(A,B)    (A * (float) B)
#define   IQ29mpyI32(A,B)    (A * (float) B)
#define   IQ28mpyI32(A,B)    (A * (float) B)
#define   IQ27mpyI32(A,B)    (A * (float) B)
#define   IQ26mpyI32(A,B)    (A * (float) B)
#define   IQ25mpyI32(A,B)    (A * (float) B)
#define   IQ24mpyI32(A,B)    (A * (float) B)
#define   IQ23mpyI32(A,B)    (A * (float) B)
#define   IQ22mpyI32(A,B)    (A * (float) B)
#define   IQ21mpyI32(A,B)    (A * (float) B)
#define   IQ20mpyI32(A,B)    (A * (float) B)
#define   IQ19mpyI32(A,B)    (A * (float) B)
#define   IQ18mpyI32(A,B)    (A * (float) B)
#define   IQ17mpyI32(A,B)    (A * (float) B)
#define   IQ16mpyI32(A,B)    (A * (float) B)
#define   IQ15mpyI32(A,B)    (A * (float) B)
#define   IQ14mpyI32(A,B)    (A * (float) B)
#define   IQ13mpyI32(A,B)    (A * (float) B)
#define   IQ12mpyI32(A,B)    (A * (float) B)
#define   IQ11mpyI32(A,B)    (A * (float) B)
#define   IQ10mpyI32(A,B)    (A * (float) B)
#define   IQ9mpyI32(A,B)     (A * (float) B)
#define   IQ8mpyI32(A,B)     (A * (float) B)
#define   IQ7mpyI32(A,B)     (A * (float) B)
#define   IQ6mpyI32(A,B)     (A * (float) B)
#define   IQ5mpyI32(A,B)     (A * (float) B)
#define   IQ4mpyI32(A,B)     (A * (float) B)
#define   IQ3mpyI32(A,B)     (A * (float) B)
#define   IQ2mpyI32(A,B)     (A * (float) B)
#define   IQ1mpyI32(A,B)     (A * (float) B)
//---------------------------------------------------------------------------
#define   IQmpyI32int(A,B)   ((long) (A * (float) B))
#define   IQ30mpyI32int(A,B) ((long) (A * (float) B))
#define   IQ29mpyI32int(A,B) ((long) (A * (float) B))
#define   IQ28mpyI32int(A,B) ((long) (A * (float) B))
#define   IQ27mpyI32int(A,B) ((long) (A * (float) B))
#define   IQ26mpyI32int(A,B) ((long) (A * (float) B))
#define   IQ25mpyI32int(A,B) ((long) (A * (float) B))
#define   IQ24mpyI32int(A,B) ((long) (A * (float) B))
#define   IQ23mpyI32int(A,B) ((long) (A * (float) B))
#define   IQ22mpyI32int(A,B) ((long) (A * (float) B))
#define   IQ21mpyI32int(A,B) ((long) (A * (float) B))
#define   IQ20mpyI32int(A,B) ((long) (A * (float) B))
#define   IQ19mpyI32int(A,B) ((long) (A * (float) B))
#define   IQ18mpyI32int(A,B) ((long) (A * (float) B))
#define   IQ17mpyI32int(A,B) ((long) (A * (float) B))
#define   IQ16mpyI32int(A,B) ((long) (A * (float) B))
#define   IQ15mpyI32int(A,B) ((long) (A * (float) B))
#define   IQ14mpyI32int(A,B) ((long) (A * (float) B))
#define   IQ13mpyI32int(A,B) ((long) (A * (float) B))
#define   IQ12mpyI32int(A,B) ((long) (A * (float) B))
#define   IQ11mpyI32int(A,B) ((long) (A * (float) B))
#define   IQ10mpyI32int(A,B) ((long) (A * (float) B))
#define   IQ9mpyI32int(A,B)  ((long) (A * (float) B))
#define   IQ8mpyI32int(A,B)  ((long) (A * (float) B))
#define   IQ7mpyI32int(A,B)  ((long) (A * (float) B))
#define   IQ6mpyI32int(A,B)  ((long) (A * (float) B))
#define   IQ5mpyI32int(A,B)  ((long) (A * (float) B))
#define   IQ4mpyI32int(A,B)  ((long) (A * (float) B))
#define   IQ3mpyI32int(A,B)  ((long) (A * (float) B))
#define   IQ2mpyI32int(A,B)  ((long) (A * (float) B))
#define   IQ1mpyI32int(A,B)  ((long) (A * (float) B))
//---------------------------------------------------------------------------
#define   _IQmpyI32frac(A,B)    (((A) * (B)) - (float)((long)((A) * (float)(B))))
#define   _IQ30mpyI32frac(A,B)  (((A) * (B)) - (float)((long)((A) * (float)(B))))
#define   _IQ29mpyI32frac(A,B)  (((A) * (B)) - (float)((long)((A) * (float)(B))))
#define   _IQ28mpyI32frac(A,B)  (((A) * (B)) - (float)((long)((A) * (float)(B))))
#define   _IQ27mpyI32frac(A,B)  (((A) * (B)) - (float)((long)((A) * (float)(B))))
#define   _IQ26mpyI32frac(A,B)  (((A) * (B)) - (float)((long)((A) * (float)(B))))
#define   _IQ25mpyI32frac(A,B)  (((A) * (B)) - (float)((long)((A) * (float)(B))))
#define   _IQ24mpyI32frac(A,B)  (((A) * (B)) - (float)((long)((A) * (float)(B))))
#define   _IQ23mpyI32frac(A,B)  (((A) * (B)) - (float)((long)((A) * (float)(B))))
#define   _IQ22mpyI32frac(A,B)  (((A) * (B)) - (float)((long)((A) * (float)(B))))
#define   _IQ21mpyI32frac(A,B)  (((A) * (B)) - (float)((long)((A) * (float)(B))))
#define   _IQ20mpyI32frac(A,B)  (((A) * (B)) - (float)((long)((A) * (float)(B))))
#define   _IQ19mpyI32frac(A,B)  (((A) * (B)) - (float)((long)((A) * (float)(B))))
#define   _IQ18mpyI32frac(A,B)  (((A) * (B)) - (float)((long)((A) * (float)(B))))
#define   _IQ17mpyI32frac(A,B)  (((A) * (B)) - (float)((long)((A) * (float)(B))))
#define   _IQ16mpyI32frac(A,B)  (((A) * (B)) - (float)((long)((A) * (float)(B))))
#define   _IQ15mpyI32frac(A,B)  (((A) * (B)) - (float)((long)((A) * (float)(B))))
#define   _IQ14mpyI32frac(A,B)  (((A) * (B)) - (float)((long)((A) * (float)(B))))
#define   _IQ13mpyI32frac(A,B)  (((A) * (B)) - (float)((long)((A) * (float)(B))))
#define   _IQ12mpyI32frac(A,B)  (((A) * (B)) - (float)((long)((A) * (float)(B))))
#define   _IQ11mpyI32frac(A,B)  (((A) * (B)) - (float)((long)((A) * (float)(B))))
#define   _IQ10mpyI32frac(A,B)  (((A) * (B)) - (float)((long)((A) * (float)(B))))
#define   _IQ9mpyI32frac(A,B)   (((A) * (B)) - (float)((long)((A) * (float)(B))))
#define   _IQ8mpyI32frac(A,B)   (((A) * (B)) - (float)((long)((A) * (float)(B))))
#define   _IQ7mpyI32frac(A,B)   (((A) * (B)) - (float)((long)((A) * (float)(B))))
#define   _IQ6mpyI32frac(A,B)   (((A) * (B)) - (float)((long)((A) * (float)(B))))
#define   _IQ5mpyI32frac(A,B)   (((A) * (B)) - (float)((long)((A) * (float)(B))))
#define   _IQ4mpyI32frac(A,B)   (((A) * (B)) - (float)((long)((A) * (float)(B))))
#define   _IQ3mpyI32frac(A,B)   (((A) * (B)) - (float)((long)((A) * (float)(B))))
#define   _IQ2mpyI32frac(A,B)   (((A) * (B)) - (float)((long)((A) * (float)(B))))
#define   _IQ1mpyI32frac(A,B)   (((A) * (B)) - (float)((long)((A) * (float)(B))))
//---------------------------------------------------------------------------
#define   IQmag(A,B)         sqrt(A*A + B*B)
#define   IQ30mag(A,B)       sqrt(A*A + B*B)
#define   IQ29mag(A,B)       sqrt(A*A + B*B)
#define   IQ28mag(A,B)       sqrt(A*A + B*B)
#define   IQ27mag(A,B)       sqrt(A*A + B*B)
#define   IQ26mag(A,B)       sqrt(A*A + B*B)
#define   IQ25mag(A,B)       sqrt(A*A + B*B)
#define   IQ24mag(A,B)       sqrt(A*A + B*B)
#define   IQ23mag(A,B)       sqrt(A*A + B*B)
#define   IQ22mag(A,B)       sqrt(A*A + B*B)
#define   IQ21mag(A,B)       sqrt(A*A + B*B)
#define   IQ20mag(A,B)       sqrt(A*A + B*B)
#define   IQ19mag(A,B)       sqrt(A*A + B*B)
#define   IQ18mag(A,B)       sqrt(A*A + B*B)
#define   IQ17mag(A,B)       sqrt(A*A + B*B)
#define   IQ16mag(A,B)       sqrt(A*A + B*B)
#define   IQ15mag(A,B)       sqrt(A*A + B*B)
#define   IQ14mag(A,B)       sqrt(A*A + B*B)
#define   IQ13mag(A,B)       sqrt(A*A + B*B)
#define   IQ12mag(A,B)       sqrt(A*A + B*B)
#define   IQ11mag(A,B)       sqrt(A*A + B*B)
#define   IQ10mag(A,B)       sqrt(A*A + B*B)
#define   IQ9mag(A,B)        sqrt(A*A + B*B)
#define   IQ8mag(A,B)        sqrt(A*A + B*B)
#define   IQ7mag(A,B)        sqrt(A*A + B*B)
#define   IQ6mag(A,B)        sqrt(A*A + B*B)
#define   IQ5mag(A,B)        sqrt(A*A + B*B)
#define   IQ4mag(A,B)        sqrt(A*A + B*B)
#define   IQ3mag(A,B)        sqrt(A*A + B*B)
#define   IQ2mag(A,B)        sqrt(A*A + B*B)
#define   IQ1mag(A,B)        sqrt(A*A + B*B)
//---------------------------------------------------------------------------
#define   atoIQ(A)           atof(A)
#define   atoIQ30(A)         atof(A)
#define   atoIQ29(A)         atof(A)
#define   atoIQ28(A)         atof(A)
#define   atoIQ27(A)         atof(A)
#define   atoIQ26(A)         atof(A)
#define   atoIQ25(A)         atof(A)
#define   atoIQ24(A)         atof(A)
#define   atoIQ23(A)         atof(A)
#define   atoIQ22(A)         atof(A)
#define   atoIQ21(A)         atof(A)
#define   atoIQ20(A)         atof(A)
#define   atoIQ19(A)         atof(A)
#define   atoIQ18(A)         atof(A)
#define   atoIQ17(A)         atof(A)
#define   atoIQ16(A)         atof(A)
#define   atoIQ15(A)         atof(A)
#define   atoIQ14(A)         atof(A)
#define   atoIQ13(A)         atof(A)
#define   atoIQ12(A)         atof(A)
#define   atoIQ11(A)         atof(A)
#define   atoIQ10(A)         atof(A)
#define   atoIQ9(A)          atof(A)
#define   atoIQ8(A)          atof(A)
#define   atoIQ7(A)          atof(A)
#define   atoIQ6(A)          atof(A)
#define   atoIQ5(A)          atof(A)
#define   atoIQ4(A)          atof(A)
#define   atoIQ3(A)          atof(A)
#define   atoIQ2(A)          atof(A)
#define   atoIQ1(A)          atof(A)
//---------------------------------------------------------------------------
#define   IQtoa(A, B, C)     sprintf(A, B, C)
#define   IQ30toa(A, B, C)   sprintf(A, B, C)
#define   IQ29toa(A, B, C)   sprintf(A, B, C)
#define   IQ28toa(A, B, C)   sprintf(A, B, C)
#define   IQ27toa(A, B, C)   sprintf(A, B, C)
#define   IQ26toa(A, B, C)   sprintf(A, B, C)
#define   IQ25toa(A, B, C)   sprintf(A, B, C)
#define   IQ24toa(A, B, C)   sprintf(A, B, C)
#define   IQ23toa(A, B, C)   sprintf(A, B, C)
#define   IQ22toa(A, B, C)   sprintf(A, B, C)
#define   IQ21toa(A, B, C)   sprintf(A, B, C)
#define   IQ20toa(A, B, C)   sprintf(A, B, C)
#define   IQ19toa(A, B, C)   sprintf(A, B, C)
#define   IQ18toa(A, B, C)   sprintf(A, B, C)
#define   IQ17toa(A, B, C)   sprintf(A, B, C)
#define   IQ16toa(A, B, C)   sprintf(A, B, C)
#define   IQ15toa(A, B, C)   sprintf(A, B, C)
#define   IQ14toa(A, B, C)   sprintf(A, B, C)
#define   IQ13toa(A, B, C)   sprintf(A, B, C)
#define   IQ12toa(A, B, C)   sprintf(A, B, C)
#define   IQ11toa(A, B, C)   sprintf(A, B, C)
#define   IQ10toa(A, B, C)   sprintf(A, B, C)
#define   IQ9toa(A, B, C)    sprintf(A, B, C)
#define   IQ8toa(A, B, C)    sprintf(A, B, C)
#define   IQ7toa(A, B, C)    sprintf(A, B, C)
#define   IQ6toa(A, B, C)    sprintf(A, B, C)
#define   IQ5toa(A, B, C)    sprintf(A, B, C)
#define   IQ4toa(A, B, C)    sprintf(A, B, C)
#define   IQ3toa(A, B, C)    sprintf(A, B, C)
#define   IQ2toa(A, B, C)    sprintf(A, B, C)
#define   IQ1toa(A, B, C)    sprintf(A, B, C)
//---------------------------------------------------------------------------
#define   IQabs(A)           fabs(A)
#define   IQ30abs(A)         fabs(A)
#define   IQ29abs(A)         fabs(A)
#define   IQ28abs(A)         fabs(A)
#define   IQ27abs(A)         fabs(A)
#define   IQ26abs(A)         fabs(A)
#define   IQ25abs(A)         fabs(A)
#define   IQ24abs(A)         fabs(A)
#define   IQ23abs(A)         fabs(A)
#define   IQ22abs(A)         fabs(A)
#define   IQ21abs(A)         fabs(A)
#define   IQ20abs(A)         fabs(A)
#define   IQ19abs(A)         fabs(A)
#define   IQ18abs(A)         fabs(A)
#define   IQ17abs(A)         fabs(A)
#define   IQ16abs(A)         fabs(A)
#define   IQ15abs(A)         fabs(A)
#define   IQ14abs(A)         fabs(A)
#define   IQ13abs(A)         fabs(A)
#define   IQ12abs(A)         fabs(A)
#define   IQ11abs(A)         fabs(A)
#define   IQ10abs(A)         fabs(A)
#define   IQ9abs(A)          fabs(A)
#define   IQ8abs(A)          fabs(A)
#define   IQ7abs(A)          fabs(A)
#define   IQ6abs(A)          fabs(A)
#define   IQ5abs(A)          fabs(A)
#define   IQ4abs(A)          fabs(A)
#define   IQ3abs(A)          fabs(A)
#define   IQ2abs(A)          fabs(A)
#define   IQ1abs(A)          fabs(A)
//###########################################################################
#endif  // No more.
//###########################################################################

#endif /* __IQMATHLIB_H_INCLUDED__ */
