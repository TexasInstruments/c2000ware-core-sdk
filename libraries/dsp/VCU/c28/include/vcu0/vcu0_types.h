#ifndef _VCU0_TYPES_H_
#define _VCU0_TYPES_H_
//#############################################################################
//! \file   include/vcu0/vcu0_types.h
//!
//! \brief  Type definitions for the VCU0 algorithms
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
// includes
//*****************************************************************************
//#include <string.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>

//!
//! \defgroup VCU0_DEFINITIONS VCU0 Type Defintions


//!
//! \ingroup VCU0_DEFINITIONS
// @{

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************
#ifndef TRUE
#define TRUE                    (1)
#define FALSE                   (0)
#endif //TRUE

#define PARITY(a) ((a) % 2)

#define ALIGN16(len)    (((len) + 1) & ~1)

/* size of, in octets */
#define OCTETS(x)   ((sizeof(x)) * (CHAR_BIT >> 3))

#define SIZEOF_SINT16         2
#define SIZEOF_UINT16         2
#define SIZEOF_SINT32         4
#define SIZEOF_UINT32         4


//*****************************************************************************
// typedefs
//*****************************************************************************
//! \brief Parity enumeration
//!
//! The parity is used by the CRC algorithm to determine whether to begin
//! calculations from the low byte (EVEN) or from the high byte (ODD) of the
//! first word (16-bit) in the message. \n
//! For example, if your message had 10 bytes and started at the address 0x8000
//! but the first byte was at the high byte position of the first 16-bit word, 
//! the user would call the CRC function with odd parity i.e. CRC_parity_odd \n
//! Address: HI  LO \n
//! 0x8000 : B0  XX \n
//! 0x8001 : B2  B1 \n
//! 0x8002 : B4  B3 \n
//! 0x8003 : B6  B5 \n
//! 0x8004 : B8  B7 \n
//! 0x8005 : XX  B9 \n
//! However, if the first byte was at the low byte position of the first 16-bit word, 
//! the user would call the CRC function with even parity i.e. CRC_parity_even \n
//! Address: HI  LO \n
//! 0x8000 : B1  B0 \n
//! 0x8001 : B3  B2 \n
//! 0x8002 : B5  B4 \n
//! 0x8003 : B7  B6 \n
//! 0x8004 : B9  B8 \n
//
typedef enum {
  CRC_parity_even = 0,     //!< Even parity, CRC starts at the low byte of the first word
  CRC_parity_odd  = 1      //!< Odd parity, CRC starts at the high byte of the first word
} CRC_parity_e;

//typedef unsigned char      uint8;
typedef unsigned int       uint16;
typedef unsigned long      uint32;
typedef unsigned long long uint64;

#ifndef F28_DATA_TYPES
#define F28_DATA_TYPES
typedef int             	int16;
typedef long            	int32;
typedef long long			int64;
typedef unsigned int    	Uint16;
typedef unsigned long   	Uint32;
typedef unsigned long long	Uint64;
typedef float           	float32;
typedef long double     	float64;
#endif //F28_DATA_TYPES

#ifndef VCU0_TYPES
#define VCU0_TYPES
typedef long               RCODE;

#ifndef _STDBOOL
#define _STDBOOL
//typedef unsigned long      bool;
#endif /* _STDBOOL */

// Read-Write Data Types
typedef signed int            SINT16;     // Signed 16-bit integer (15-bit magnitude)
typedef unsigned int          UINT16;     // Unsigned 16-bit integer
typedef signed long           SINT32;     // Signed 32-bit integer (31-bit magnitude)
typedef unsigned long         UINT32;     // Unsigned 32-bit integer
typedef signed long long      SINT64;     // Signed 64-bit integer
typedef unsigned long long    UINT64;     // Unsigned 64-bit integer
typedef int                   BOOL;       // Only TRUE/FALSE applied

// All pointers are 32 bits long
typedef SINT16                *PSINT16;   // Pointer to SINT16
typedef UINT16                *PUINT16;   // Pointer to UINT16
typedef SINT32                *PSINT32;   // Pointer to SINT32
typedef UINT32                *PUINT32;   // Pointer to UINT32
//----------------------------------------------------------------------------
//                      Complex data Typedef Declarations
//----------------------------------------------------------------------------
//! \brief Complex data
//!
typedef struct
{
  SINT16 real; 			//!< Real Part
  SINT16 imag; 			//!< Imaginary Part

}cplx16, ComplexShort;

//----------------------------------------------------------------------------
//                      Circular buffer Typedef Declarations
//----------------------------------------------------------------------------
typedef struct
{
  SINT16 *buf_p;   // buffer base addr
  UINT16 rdIdx;    // read index
  UINT16 wtIdx;    // write index
  UINT16 bufSize;  // buf size in 16-bits words

}Buffer_t;

#endif //VCU0_TYPES

#ifdef __cplusplus
}
#endif // extern "C"

// @} //ingroup

#endif //end of _VCU0_TYPES_H_ definition

// End of File
