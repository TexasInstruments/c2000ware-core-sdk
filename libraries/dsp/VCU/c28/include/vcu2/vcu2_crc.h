#ifndef _VCU2_CRC_H_
#define _VCU2_CRC_H_
//#############################################################################
//! \file include/vcu2/vcu2_crc.h
//!
//! \brief  Cyclic Redundancy Check Header File
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
#include "vcu2_types.h"


//!
//! \defgroup VCU2_CRC Cyclic Redundancy Check (VCU2)

//!
//! \ingroup VCU2_CRC
// @{

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************
#define INIT_CRC8 	 	0x0			//!< Initial CRC Register Value
#define INIT_CRC16 		0x0			//!< Initial CRC Register Value
#define INIT_CRC24 		0x0			//!< Initial CRC Register Value
#define INIT_CRC32 		0x0			//!< Initial CRC Register Value

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
  CRC_parity_even = 0,     //!< Even parity, CRC starts at the low byte of the first word (16-bit)
  CRC_parity_odd  = 1      //!< Odd parity, CRC starts at the high byte of the first word (16-bit)
} CRC_parity_e;

//! \brief CRC structure
//!
typedef struct _CRC_Obj_{
	uint32_t	seedValue;			//!< Initial value of the CRC calculation
	uint16_t	nMsgBytes;			//!< the number of bytes in the message buffer
	CRC_parity_e	parity;			//!< the location, in a word, of the first byte of the CRC calculation
	uint32_t	crcResult;			//!< the calculated CRC
	void		*pMsgBuffer;		//!< Pointer to the message buffer
	void 		*pCrcTable;			//!< Pointer to the CRC lookup table
	uint32_t    nMsgBits;           // provde the data size in bits if the CRC is to be computed bitwise
    uint32_t    polynomial;         // added to ensure customized polynomial can be added by the user
    uint16_t    polySize;           // provide the polynomial size for the customized polynomial
    uint16_t    dataSize;
    uint16_t    reflected;
	void (*init)(void *);			//!< Function pointer to CRC initialization routine
	void (*run)(void *);			//!< Function pointer to CRC computation routine

}CRC_Obj;

//! \brief Handle to the CRC structure
//!
typedef CRC_Obj *CRC_Handle;

//*****************************************************************************
// globals
//*****************************************************************************

//*****************************************************************************
// function prototypes
//*****************************************************************************

//----------------------
// CRC Helper functions
//----------------------
//! \brief Bit-reverse a value
//!
//! Bit reverse a given hex value, The number of bits must be a power of 2
//!
//! \param valToReverse Value to reverse
//! \param bitWidth Bit-width of the input, must be a power of 2
//!
//! \return	bit-reversed value
//
uint32_t CRC_bitReflect(uint32_t valToReverse,int16_t bitWidth);

//
//! \brief power of 2
//!
//! recursive function to calculate a positive integer that is a power of two
//!
//! \param power The exponent of two
//!
//! \returns an integer that is a power of two
//!
//
uint16_t CRC_pow2(uint16_t power);

//! \brief Workaround to the silicon issue of first VCU calculation on power up being
//!  erroneous
//! 
//! Details Due to the internal power-up state of the VCU module, it is possible 
//! that the first CRC result will be incorrect. This condition applies to the 
//! first result from each of the eight CRC instructions. 
//! This rare condition can only occur after a power-on reset, but will not
//! necessarily occur on every power on. A warm reset will not cause this condition 
//! to reappear.
//! Workaround(s): The application can reset the internal VCU CRC logic by 
//! performing a CRC calculation of a single byte in the initialization routine. 
//! This routine only needs to perform one CRC calculation and can use any of the 
//! CRC instructions
//
void CRC_reset(void);

//----------------------
//8-bit CRC functions
//----------------------

//! \brief Initializes the CRC object
//! 
//! Clears the CRCMSGFLIP bit is cleared ensuring the input
//! is interpreted in normal bit-order
//!
//! \param[in] hndCRC handle to the CRC object
//
void CRC_init8Bit(CRC_Handle hndCRC );

//! \brief Calculate the 8-bit CRC using polynomial 0x7
//!
//! Calculates the 8-bit CRC using polynomial 0x7 on the VCU.
//! Depending on the parity chosen the CRC begins at either 
//! the low byte (PARITY_LOWBYTE) or the high byte (PARITY_HIGHBYTE) 
//! of the first word (16-bit).
//! \note the size of the message (bytes) is limited to 65535 bytes.
//! If attempting to process a larger message, the user must break
//! it into pieces of size 65535 or smaller, and successively run
//! the CRC on each block, with the CRC result of one block becoming the
//! seed value for the next block. An example of this is shown in the 
//! FLASH build configuration of the example \b 2837x_vcu2_crc_8.
//!
//! \param[in] hndCRC handle to the CRC object
//
void CRC_run8Bit(CRC_Handle hndCRC);

//! \brief Runs the 8-bit CRC routine using polynomial 0x7 
//!        with the input bits reversed
//!
//! By setting the CRCMSGFLIP bit, the input is fed through the
//! VCU 8-bit CRC calculator (polynomial 0x7) in reverse bit order
//!
//! \note the size of the message (bytes) is limited to 65535 bytes
//! Please see the notes for the function \b CRC_run8Bit for details
//!
//! \param[in] hndCRC handle to the CRC object
//
void CRC_run8BitReflected(CRC_Handle hndCRC);

//! \brief C table-lookup 8-bit CRC calculation
//!
//! The CRC is calculated using a table lookup method, where 
//! each byte of the input is an index into the table. The value
//! at that index is XOR'd into a variable called the accumulator. 
//! Once the final byte's CRC is looked up and accumulated we get
//! the CRC for the entire message block
//!
//! \note the size of the message (bytes) is limited to 65535 bytes
//! Please see the notes for the function \b CRC_run8Bit for details
//!
//! \param[in] hndCRC handle to the CRC object
//! \sa http://www.ross.net/crc/download/crc_v3.txt
//
void CRC_run8BitTableLookupC(CRC_Handle hndCRC);

//----------------------
//16-bit CRC functions
//----------------------

//! \brief Initializes the CRC object
//! 
//! Clears the CRCMSGFLIP bit is cleared ensuring the input
//! is interpreted in normal bit-order
//!
//! \param[in] hndCRC handle to the CRC object
//
void CRC_init16Bit(CRC_Handle hndCRC);

//! \brief Runs the CRC routine using polynomial 0x8005
//!
//! Calculates the 16-bit CRC using polynomial 0x8005 on the VCU.
//! Depending on the parity chosen the CRC begins at either 
//! the low byte (PARITY_LOWBYTE) or the high byte (PARITY_HIGHBYTE) 
//! of the first word (16-bit).
//!
//! \note the size of the message (bytes) is limited to 65535 bytes
//! Please see the notes for the function \b CRC_run8Bit for details
//!
//! \param[in] hndCRC handle to the CRC object
//
void CRC_run16BitPoly1(CRC_Handle hndCRC);

//! \brief Runs the CRC routine using polynomial 0x1021
//!
//! Calculates the 16-bit CRC using polynomial 0x1021 on the VCU.
//! Depending on the parity chosen the CRC begins at either 
//! the low byte (PARITY_LOWBYTE) or the high byte (PARITY_HIGHBYTE) 
//! of the first word (16-bit).
//!
//! \note the size of the message (bytes) is limited to 65535 bytes
//! Please see the notes for the function \b CRC_run8Bit for details
//!
//! \param[in] hndCRC handle to the CRC object
//
void CRC_run16BitPoly2(CRC_Handle hndCRC);

//! \brief Runs the 16-bit CRC routine using polynomial 0x8005
//!        with the input bits reversed
//!
//! By setting the CRCMSGFLIP bit, the input is fed through the
//! VCU 16-bit CRC calculator (polynomial 0x8005) in reverse bit order
//!
//! \note the size of the message (bytes) is limited to 65535 bytes
//! Please see the notes for the function \b CRC_run8Bit for details
//!
//! \param[in] hndCRC handle to the CRC object
//
void CRC_run16BitPoly1Reflected(CRC_Handle hndCRC);

//! \brief Runs the 16-bit CRC routine using polynomial 0x1021
//!        with the input bits reversed
//!
//! By setting the CRCMSGFLIP bit, the input is fed through the
//! VCU 16-bit CRC calculator (polynomial 0x1021) in reverse bit order
//!
//! \note the size of the message (bytes) is limited to 65535 bytes
//! Please see the notes for the function \b CRC_run8Bit for details
//!
//! \param[in] hndCRC handle to the CRC object
//
void CRC_run16BitPoly2Reflected(CRC_Handle hndCRC);

//! \brief C table-lookup 16-bit CRC calculation
//!
//! The CRC is calculated using a table lookup method, where 
//! each byte of the input is an index into the table. The value
//! at that index is XOR'd into a variable called the accumulator. 
//! Once the final byte's CRC is looked up and accumulated we get
//! the CRC for the entire message block
//!
//! \note the size of the message (bytes) is limited to 65535 bytes
//! Please see the notes for the function \b CRC_run8Bit for details
//!
//! \param[in] hndCRC handle to the CRC object
//! \sa http://www.ross.net/crc/download/crc_v3.txt
//
void CRC_run16BitTableLookupC(CRC_Handle hndCRC);

//! \brief C table-lookup 16-bit CRC calculation(reflected algorithm)
//!
//! The CRC is calculated using a table lookup method, where 
//! each byte of the input is an index into the table. The value
//! at that index is XOR'd into a variable called the accumulator. 
//! Once the final byte's CRC is looked up and accumulated we get
//! the CRC for the entire message block
//!
//! \note the size of the message (bytes) is limited to 65535 bytes
//! Please see the notes for the function \b CRC_run8Bit for details
//!
//! \param[in] hndCRC handle to the CRC object
//! \sa http://www.ross.net/crc/download/crc_v3.txt
//
void CRC_run16BitReflectedTableLookupC(CRC_Handle hndCRC);

//----------------------
//24-bit CRC functions
//----------------------
//! \brief Initializes the CRC object
//! 
//! Clears the CRCMSGFLIP bit is cleared ensuring the input
//! is interpreted in normal bit-order
//!
//! \param[in] hndCRC handle to the CRC object
//
void CRC_init24Bit(CRC_Handle hndCRC);

//! \brief Runs the CRC routine
//!
//! Calculates the 24-bit CRC using polynomial 0x5d6dcb on the VCU.
//! Depending on the parity chosen the CRC begins at either 
//! the low byte (PARITY_LOWBYTE) or the high byte (PARITY_HIGHBYTE) 
//! of the first word (16-bit).
//!
//! \note the size of the message (bytes) is limited to 65535 bytes
//! Please see the notes for the function \b CRC_run8Bit for details
//!
//! \param[in] hndCRC handle to the CRC object
//
void CRC_run24Bit(CRC_Handle hndCRC);

//! \brief Runs the 24-bit CRC routine using polynomial 0x5d6dcb 
//!        with the input bits reversed
//!
//! By setting the CRCMSGFLIP bit, the input is fed through the
//! VCU 24-bit CRC calculator (polynomial 0x5d6dcb) in reverse bit order
//!
//! \note the size of the message (bytes) is limited to 65535 bytes
//! Please see the notes for the function \b CRC_run8Bit for details
//!
//! \param[in] hndCRC handle to the CRC object
//
void CRC_run24BitReflected(CRC_Handle hndCRC);

//! \brief C table-lookup 24-bit CRC calculation
//!
//! The CRC is calculated using a table lookup method, where 
//! each byte of the input is an index into the table. The value
//! at that index is XOR'd into a variable called the accumulator. 
//! Once the final byte's CRC is looked up and accumulated we get
//! the CRC for the entire message block
//!
//! \note the size of the message (bytes) is limited to 65535 bytes
//! Please see the notes for the function \b CRC_run8Bit for details
//!
//! \param[in] hndCRC handle to the CRC object
//! \sa http://www.ross.net/crc/download/crc_v3.txt
//
void CRC_run24BitTableLookupC(CRC_Handle hndCRC);

//! \brief C table-lookup 24-bit CRC calculation(reflected algorithm)
//!
//! The CRC is calculated using a table lookup method, where 
//! each byte of the input is an index into the table. The value
//! at that index is XOR'd into a variable called the accumulator. 
//! Once the final byte's CRC is looked up and accumulated we get
//! the CRC for the entire message block
//!
//! \note the size of the message (bytes) is limited to 65535 bytes
//! Please see the notes for the function \b CRC_run8Bit for details
//!
//! \param[in] hndCRC handle to the CRC object
//! \sa http://www.ross.net/crc/download/crc_v3.txt
//
void CRC_run24BitReflectedTableLookupC(CRC_Handle hndCRC);

//----------------------
//32-bit CRC functions
//----------------------

//! \brief Initializes the CRC object
//! 
//! Clears the CRCMSGFLIP bit is cleared ensuring the input
//! is interpreted in normal bit-order
//!
//! \param[in] hndCRC handle to the CRC object
//
void CRC_init32Bit(CRC_Handle hndCRC);

//! \brief Runs the 32-bit CRC routine using polynomial 0x04c11db7
//!
//! Calculates the 32-bit CRC using polynomial 0x04c11db7 on the VCU.
//! Depending on the parity chosen the CRC begins at either 
//! the low byte (PARITY_LOWBYTE) or the high byte (PARITY_HIGHBYTE) 
//! of the first word (16-bit).
//!
//! \note the size of the message (bytes) is limited to 65535 bytes
//! Please see the notes for the function \b CRC_run8Bit for details
//!
//! \param[in] hndCRC handle to the CRC object
//
void CRC_run32BitPoly1(CRC_Handle hndCRC);

//! \brief Runs the 32-bit CRC routine using polynomial 0x1edc6f41
//!
//! Calculates the 32-bit CRC using polynomial 0x1edc6f41 on the VCU.
//! Depending on the parity chosen the CRC begins at either 
//! the low byte (PARITY_LOWBYTE) or the high byte (PARITY_HIGHBYTE) 
//! of the first word (16-bit).
//!
//! \note the size of the message (bytes) is limited to 65535 bytes
//! Please see the notes for the function \b CRC_run8Bit for details
//!
//! \param[in] hndCRC handle to the CRC object
//
void CRC_run32BitPoly2(CRC_Handle hndCRC);

//! \brief Runs the 32-bit CRC routine using polynomial 0x04c11db7
//!        with the input bits reversed
//!
//! By setting the CRCMSGFLIP bit, the input is fed through the
//! VCU 32-bit CRC calculator (polynomial 0x04c11db7) in reverse bit order
//!
//! \note the size of the message (bytes) is limited to 65535 bytes
//! Please see the notes for the function \b CRC_run8Bit for details
//!
//! \param[in] hndCRC handle to the CRC object
//
void CRC_run32BitPoly1Reflected(CRC_Handle hndCRC);

//! \brief Runs the 32-bit CRC routine using polynomial 0x1edc6f41
//!        with the input bits reversed
//!
//! By setting the CRCMSGFLIP bit, the input is fed through the
//! VCU 32-bit CRC calculator (polynomial 0x1edc6f41) in reverse bit order
//!
//! \note the size of the message (bytes) is limited to 65535 bytes
//! Please see the notes for the function \b CRC_run8Bit for details
//!
//! \param[in] hndCRC handle to the CRC object
//
void CRC_run32BitPoly2Reflected(CRC_Handle hndCRC);

//! \brief C table-lookup 32-bit CRC calculation
//!
//! The CRC is calculated using a table lookup method, where 
//! each byte of the input is an index into the table. The value
//! at that index is XOR'd into a variable called the accumulator. 
//! Once the final byte's CRC is looked up and accumulated we get
//! the CRC for the entire message block
//!
//! \note the size of the message (bytes) is limited to 65535 bytes
//! Please see the notes for the function \b CRC_run8Bit for details
//!
//! \param[in] hndCRC handle to the CRC object
//! \sa http://www.ross.net/crc/download/crc_v3.txt
//
void CRC_run32BitTableLookupC(CRC_Handle hndCRC);

//! \brief C table-lookup 32-bit CRC calculation(reflected algorithm)
//!
//! The CRC is calculated using a table lookup method, where 
//! each byte of the input is an index into the table. The value
//! at that index is XOR'd into a variable called the accumulator. 
//! Once the final byte's CRC is looked up and accumulated we get
//! the CRC for the entire message block
//!
//! \note the size of the message (bytes) is limited to 65535 bytes
//! Please see the notes for the function \b CRC_run8Bit for details
//!
//! \param[in] hndCRC handle to the CRC object
//! \sa http://www.ross.net/crc/download/crc_v3.txt
//
void CRC_run32BitReflectedTableLookupC(CRC_Handle hndCRC);

#ifdef __cplusplus
}
#endif // extern "C"

// @} //ingroup

#endif //end of _VCU2_CRC_H_ definition

// End of File
