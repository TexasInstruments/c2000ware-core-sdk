//#############################################################################
//! \file /2837x_vcu0_crc_genTables/main.c
//!
//! \brief  Demonstrate the use of the CRC functions available in the VCU0 lib
//!
//! \date   Apr 7, 2011
//! 
//! This example shows how to
//! -# use the vcu0 supported CRC routines from the library
//! -# use a C based table lookup routine to run an 8,16,32-bit CRC check using
//!    predefined polynomials
//! -# demonstrate the link time CRC generation(using known 8, 16, 32-bit
//!    polynomials) on a specified section of memory
//
//  Group:             C2000
//  Target Family:     F2837x
//
//#############################################################################
//
//
// $Copyright: Copyright (C) 2024 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################

//*****************************************************************************
// includes
//*****************************************************************************

#include "examples_setup.h"
#include "vcu0_crc.h"
#include "crc_tbl.h"


//!
//! \defgroup VCU0_CRC_EXAMPLES VCU Type 0 Cyclic Redundancy Check Example

//!
//! \ingroup VCU0_CRC_EXAMPLES
// @{

//*****************************************************************************
// defines
//*****************************************************************************
//! Test Packet Length in number of words
#define CRC_TEST_PACKET_LEN		128 
//! Test Packet Length in number of BYTES
#define CRC_TEST_PACKET_BYTES   (CRC_TEST_PACKET_LEN << 1) 
//*****************************************************************************
// globals
//*****************************************************************************
#ifdef __cplusplus
#pragma DATA_SECTION("testInput")
#else
#pragma DATA_SECTION(testInput,"testInput")
#endif //__cplusplus
//!\brief test input
//!
//! This vector is declared as a static const in order for the linker to
//! be able to run the CRC algorithm on it. It needn't be either static
//! or const for the C and VCU routines
//!
static const uint16 testInput[CRC_TEST_PACKET_LEN] = {
	0x0001, 0x0203, 0x0405, 0x0607, 0x0809, 0x0A0B, 0x0C0D, 0x0E0F,
	0x1011, 0x1213, 0x1415, 0x1617, 0x1819, 0x1A1B, 0x1C1D, 0x1E1F,
	0x2021, 0x2223, 0x2425, 0x2627, 0x2829, 0x2A2B, 0x2C2D, 0x2E2F,
	0x3031, 0x3233, 0x3435, 0x3637, 0x3839, 0x3A3B, 0x3C3D, 0x3E3F,
	0x4041, 0x4243, 0x4445, 0x4647, 0x4849, 0x4A4B, 0x4C4D, 0x4E4F,
	0x5051, 0x5253, 0x5455, 0x5657, 0x5859, 0x5A5B, 0x5C5D, 0x5E5F,
	0x6061, 0x6263, 0x6465, 0x6667, 0x6869, 0x6A6B, 0x6C6D, 0x6E6F,
	0x7071, 0x7273, 0x7475, 0x7677, 0x7879, 0x7A7B, 0x7C7D, 0x7E7F,
	0x8081, 0x8283, 0x8485, 0x8687, 0x8889, 0x8A8B, 0x8C8D, 0x8E8F,
	0x9091, 0x9293, 0x9495, 0x9697, 0x9899, 0x9A9B, 0x9C9D, 0x9E9F,
	0xA0A1, 0xA2A3, 0xA4A5, 0xA6A7, 0xA8A9, 0xAAAB, 0xACAD, 0xAEAF,
	0xB0B1, 0xB2B3, 0xB4B5, 0xB6B7, 0xB8B9, 0xBABB, 0xBCBD, 0xBEBF,
	0xC0C1, 0xC2C3, 0xC4C5, 0xC6C7, 0xC8C9, 0xCACB, 0xCCCD, 0xCECF,
	0xD0D1, 0xD2D3, 0xD4D5, 0xD6D7, 0xD8D9, 0xDADB, 0xDCDD, 0xDEDF,
	0xE0E1, 0xE2E3, 0xE4E5, 0xE6E7, 0xE8E9, 0xEAEB, 0xECED, 0xEEEF,
	0xF0F1, 0xF2F3, 0xF4F5, 0xF6F7, 0xF8F9, 0xFAFB, 0xFCFD, 0xFEFF
};

//!\brief linker generated object(CRC table)
//!
extern CRC_TABLE linkerCrcTable;

//! \brief A single record(element) from the CRC table object
//!
CRC_RECORD linkerCrcRecord;
//! \brief pointer to the CRC table object
//!
CRC_TABLE *pLinkerCrcTable;
// \brief linker generated variables defining the load and run placements
// of the testInput vector
//
extern uint32_t testInputLoadStart, testInputLoadSize, testInputRunStart;
//! \brief Lookup table for the CRC8 polynomial 0x07
//!
uint16 crc8_table[256];
//! \brief Lookup table for the CRC16 polynomial 0x1021
//!
uint16 crc16p1_table[256];
//! \brief Lookup table for the CRC16 polynomial 0x8005
//!
uint16 crc16p2_table[256];
//! \brief Lookup table for the CRC32 polynomial 0x04C11DB7
//!
uint32 crc32_table[256];

uint16_t pass = 0;
uint16_t fail = 0;
//*****************************************************************************
// Function Prototypes
//*****************************************************************************

//*****************************************************************************
// function definitions
//*****************************************************************************

//!
//! \brief main routine for the 8-bit CRC example
//! \return returns a 1
//!
//! This example shows how to
//! -# use the vcu0 supported CRC routines from the library
//! -# use a C based table lookup routine to run an 8,16,32-bit CRC check using
//!    predefined polynomials
//! -# the tables are generated in software using the genCRC<n>Table() routines
//! -# demonstrate the link time CRC generation(using known 8, 16, 32-bit
//!    polynomials) on a specified section of memory
//!
int main( void )
{
    // Locals
    int16_t i;
    uint32_t crc8ResultC, crc16P1ResultC , crc16P2ResultC, crc32ResultC;
    uint32_t crc8ResultVcu, crc16P1ResultVcu, crc16P2ResultVcu, crc32ResultVcu;
    uint32_t crcResultLnk;

#ifdef FLASH
	EALLOW;
	Flash0EccRegs.ECC_ENABLE.bit.ENABLE = 0;
	memcpy((uint32_t *)&RamfuncsRunStart, (uint32_t *)&RamfuncsLoadStart,
			(uint32_t)&RamfuncsLoadSize );
	VCU2_initFlash();
#endif //FLASH
	
	VCU2_initSystemClocks();
	
	VCU2_initEpie();

    //*************************************************************************
    // Example #1: 128 bytes(x8, even), parity: low byte first
    //*************************************************************************
    //! \b Example \b #1, \b Part \b 1
    //! In this section we run the table lookup CRCs on the vector testInput. 
    //! The parity chosen was CRC_parity_even indicating that the CRC will start
    //! from the low byte of the first word.
    //! \code
    //*************************************************************************
	// Step 1: Copy the test input vector from its load location to the run location.
	// This is necessary since the section was declared within a UNION in the linker
	// command file
	memcpy((uint32_t *)&testInputRunStart, (uint32_t *)&testInputLoadStart,
			(uint32_t)&testInputLoadSize );

    // Step 2: Since the library containing the CRC tables is not included in the
    // project, we will have to generate the tables in code
    genCRC8Table();
	genCRC16P1Table();
	genCRC16P2Table();
	genCRC32Table();
    
	// Step 3: Run the C lookup routines
    crc8ResultC    = getCRC8_cpu(INIT_CRC8, (uint16*)testInput,
    		(CRC_parity_e)CRC_parity_even,CRC_TEST_PACKET_BYTES);
    crc16P1ResultC = getCRC16P1_cpu(INIT_CRC16, (uint16*)testInput,
    		(CRC_parity_e)CRC_parity_even,CRC_TEST_PACKET_BYTES);
    crc16P2ResultC = getCRC16P2_cpu(INIT_CRC16, (uint16*)testInput,
    		(CRC_parity_e)CRC_parity_even,CRC_TEST_PACKET_BYTES);
    crc32ResultC   = getCRC32_cpu(INIT_CRC32, (uint16*)testInput,
    		(CRC_parity_e)CRC_parity_even,CRC_TEST_PACKET_BYTES);
    //*************************************************************************
    //! \endcode
    //!
    //! \b Example \b #1, \b Part \b 2
    //! Now we run the VCU routine on the vector testInput. 
    //! The parity chosen was CRC_parity_even indicating that the CRC will start
    //! from the low byte of the first word.
    //!
    //! \code
    //*************************************************************************
    crc8ResultVcu    = getCRC8_vcu(INIT_CRC8, (uint16*)testInput,
    		(CRC_parity_e)CRC_parity_even,CRC_TEST_PACKET_BYTES);
    crc16P1ResultVcu = getCRC16P1_vcu(INIT_CRC16, (uint16*)testInput,
    		(CRC_parity_e)CRC_parity_even,CRC_TEST_PACKET_BYTES);
    crc16P2ResultVcu = getCRC16P2_vcu(INIT_CRC16, (uint16*)testInput,
    		(CRC_parity_e)CRC_parity_even,CRC_TEST_PACKET_BYTES);
    crc32ResultVcu   = getCRC32_vcu(INIT_CRC32, (uint16*)testInput,
    		(CRC_parity_e)CRC_parity_even,CRC_TEST_PACKET_BYTES);
    //*************************************************************************
    //! \endcode
    //!
    //! \b Example \b #1, \b Part \b 3
    //! The linker will compute the CRC of the section \c testInput
    //! and keep the result as a record in a CRC_TABLE structure
    //! \c linkerCrcTable.
    //!
    //! Each record from this table is an object of type CRC_RECORD. The
    //! elements of this structure are described in detail, at the time of
    //! writing, in SPRU513D, section 7.9
    //!
    //! \note
    //! -# In the event the linker is configured to run multiple algorithms
    //!    on a section of memory, the result of those computations are placed in
    //!    the records in an unspecified order. The user must poll the crc_alg_ID
    //!    field of the record to determine which algorithm was run
    //!
    //*************************************************************************
    // Step 1: Initialize the CRC table pointer.

    pLinkerCrcTable  = &linkerCrcTable;

    // Step 2: Get the CRC results from the linker CRC table
    for(i = 0; i < pLinkerCrcTable->num_recs; i++){
        // Get the current CRC record
        linkerCrcRecord = pLinkerCrcTable->recs[i];
        // Get the linker generated CRC
        crcResultLnk    = linkerCrcRecord.crc_value;
        if(linkerCrcRecord.crc_alg_ID == CRC8_PRIME){ //0x7
            (crcResultLnk == crc8ResultVcu)? pass++ : fail++;
            (crc8ResultVcu == crc8ResultC)? pass++ : fail++;
        }else if(linkerCrcRecord.crc_alg_ID == CRC16_ALT){ //0x1021
            (crcResultLnk == crc16P1ResultVcu)? pass++ : fail++;
            (crc16P1ResultVcu == crc16P1ResultC)? pass++ : fail++;
        }else if(linkerCrcRecord.crc_alg_ID == CRC16_802_15_4){ //0x8005
            (crcResultLnk == crc16P2ResultVcu)? pass++ : fail++;
            (crc16P2ResultVcu == crc16P2ResultC)? pass++ : fail++;
        }else if(linkerCrcRecord.crc_alg_ID == CRC32_PRIME){ //0x04C11DB7
            (crcResultLnk == crc32ResultVcu)? pass++ : fail++;
            (crc32ResultVcu == crc32ResultC)? pass++ : fail++;
        }else{
            fail++;
        }
    }

    //*************************************************************************
    //!
    //! \endcode
    //!
    //*************************************************************************
    // End of test
    done();
    // Execution never reaches this point
    return 1;
}
// End of main

// @} //addtogroup

// End of file
