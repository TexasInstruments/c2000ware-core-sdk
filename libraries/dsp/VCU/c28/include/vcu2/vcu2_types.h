#ifndef _VCU2_TYPES_H_
#define _VCU2_TYPES_H_
//#############################################################################
//! \file   include/vcu2/vcu2_types.h
//!
//! \brief  Type definitions for the VCU2 algorithms
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
#include <stdint.h>

//!
//! \defgroup VCU2_DEFINITIONS VCU2 Type Defintions


//!
//! \ingroup VCU2_DEFINITIONS
// @{

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************
#ifndef NULL
#define NULL				0
#endif

#ifndef TRUE
#define	TRUE				1
#define	FALSE				0
#endif
//*****************************************************************************
// typedefs
//*****************************************************************************

#ifndef VCU2_TYPES
#define VCU2_TYPES

//! \brief Boolean enumeration
//!
typedef enum{
	BOOL_FALSE=0,
	BOOL_TRUE
}Bool_e;

//! \brief Complex data (CPACK = 0)
//!
//! On reset the CPACK bit is 0, therefore, this is the
//! default complex structure
//
typedef struct{
	int16_t	real; 			//!< Real Part
	int16_t imag; 			//!< Imaginary Part
}complexShort_t;


typedef union{
//! \brief Complex data (CPACK = 1)
//!
	struct{
		int16_t imag; 			//!< Real Part
		int16_t	real; 			//!< Imaginary Part
	}cplx;
	uint32_t ui32;
}complexCPACKON_t;


typedef union{
//! \brief Complex data (CPACK = 0)
//!
	struct{
		int16_t	real; 			//!< Real Part
		int16_t imag; 			//!< Imaginary Part
	}cplx;
	uint32_t ui32;
}complexCPACKOFF_t;

#endif //VCU2_TYPES

#ifdef __cplusplus
}
#endif // extern "C"

// @} //ingroup

#endif //end of _VCU2_TYPES_H_ definition

// End of File
