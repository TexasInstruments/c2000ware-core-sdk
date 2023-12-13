//#############################################################################
//! \file /2837x_vcu2_crc_16/main.c
//!
//! \brief  Demo code for the 16-bit CRC routine(VCU and C)
//!
//! \date   May 21, 2013
//! 
//! This example shows how to
//! -# use the vcu2 supported 16-bit CRC routines from the library
//! -# use a C based table lookup routine to run a 16-bit CRC check using
//!    any 16-bit polynomial
//! -# demonstrate the link time CRC generation(using the
//!    polynomials 0x8005 and 0x1021) on a specified section of memory
//
//  Group:             C2000
//  Target Family:     F2837x
//
//#############################################################################
//
//
// $Copyright: Copyright (C) 2023 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################

//*****************************************************************************
// includes
//*****************************************************************************
#include "crc_tbl.h"
#include "vcu2_types.h"
#include "vcu2_crc.h"
#include "crctable0x8005.h"
#include "crctable0x8005reflected.h"
#include "crctable0x1021.h"
#include "crctable0x1021reflected.h"
#include "examples_setup.h"

//!
//! \defgroup CRC16_EXAMPLES Cyclic Redundancy Check 16-bit Example

//!
//! \ingroup CRC16_EXAMPLES
// @{

//*****************************************************************************
// defines
//*****************************************************************************
#define     NBYTES        (128)
#define     NWORDS        (NBYTES/2)
//*****************************************************************************
// globals
//*****************************************************************************
#ifdef __cplusplus
#pragma DATA_SECTION("testInput")
#else
#pragma DATA_SECTION(testInput,"testInput")
#endif //__cplusplus

//\brief test input
//
// This vector is declared as a static const in order for the linker to
// be able to run the CRC algorithm on it. It needn't be either static
// or const for the C and VCU routines
//
static const uint16_t testInput[NWORDS] = {
    0x4001, 0x8002, 0xC003, 0x0004, 0x4005, 0x8006, 0xC007, 0x0008,
    0x4009, 0x800A, 0xC00B, 0x000C, 0x400D, 0x800E, 0xC00F, 0x0010,
    0x4011, 0x8012, 0xC013, 0x0014, 0x4015, 0x8016, 0xC017, 0x0018,
    0x4019, 0x801A, 0xC01B, 0x001C, 0x401D, 0x801E, 0xC01F, 0x0020,
    0x4021, 0x8022, 0xC023, 0x0024, 0x4025, 0x8026, 0xC027, 0x0028,
    0x4029, 0x802A, 0xC02B, 0x002C, 0x402D, 0x802E, 0xC02F, 0x0030,
    0x4031, 0x8032, 0xC033, 0x0034, 0x4035, 0x8036, 0xC037, 0x0038,
    0x4039, 0x803A, 0xC03B, 0x003C, 0x403D, 0x803E, 0xC03F, 0x0040,
};

// \brief linker generated object(CRC table)
//
extern CRC_TABLE linkerCrcTable;
// \brief linker generated "run" location for the CRC table object
//
extern uint16_t crcTableRun;
// \brief linker generated "load" location for the CRC table object
//
extern uint16_t crcTableLoad;
// \brief linker generated "size" label indicating the size of the CRC table
// object
//
extern uint16_t crcTableSize;
// \brief object of the structure CRC_Obj
//
CRC_Obj    CRC;
// \brief handle(pointer) to the CRC object
//
CRC_Handle handleCRC;
// \brief A single record(element) from the CRC table object
//
CRC_RECORD linkerCrcRecord;
// \brief pointer to the CRC table object
//
CRC_TABLE *pLinkerCrcTable;
// \brief linker generated variables defining the load and run placements
// of the testInput vector
//
extern uint32_t testInputLoadStart, testInputLoadSize, testInputRunStart;


uint16_t pass = 0;
uint16_t fail = 0;
//*****************************************************************************
// Function Prototypes
//*****************************************************************************

//*****************************************************************************
// function definitions
//*****************************************************************************

//!
//! \brief main routine for the 16-bit CRC example
//! \return returns a 1
//!
//! This example shows how to
//! -# use the vcu2 supported 16-bit CRC routines from the library
//! -# use a C based table lookup routine to run a 16-bit CRC check using
//!    any 16-bit polynomial
//! -# demonstrate the link time CRC generation(using the
//!    polynomials 0x8005 and 0x1021) on a specified section of memory
//!
//! \note The variables used in the example are the same used in the CRC-8
//! example and are not documented here again.
//!
int main( void )
{
    // Locals
    int16_t i;
    uint32_t crcResultC_1, crcResultC_2 ;
    uint32_t crcResultVcu_1, crcResultVcu_2;
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
    //! In this section we run a table lookup CRC on the vector testInput. The
    //! table is specified in the header files "CrcTable0x8005.h" and
    //! "CrcTable0x1021.h"respectively and the entries were generated from the
    //! polynomials \f$ x^{16}+x^{15}+x^{2}+1 \f$ (CRC16 802.15.4, 0x8005) and
    //! \f$ x^{16}+x^{12}+x^{5}+1 \f$ (CRC-CCITT, 0x1021) respectively.
    //! The parity chosen was CRC_parity_even indicating that the CRC will start
    //! from the low byte of the first word.
    //! \code
    //************************************************************************
	// Step 1: Copy the test input vector from its load location to the run location.
	// This is necessary since the section was declared within a UNION in the linker
	// command file
	memcpy((uint32_t *)&testInputRunStart, (uint32_t *)&testInputLoadStart,
			(uint32_t)&testInputLoadSize );

    // Step 2: Initialize the CRC object
    CRC.seedValue    = INIT_CRC16;
    CRC.nMsgBytes    = NBYTES;
    CRC.parity       = CRC_parity_even;
    CRC.crcResult    = 0;
    CRC.pMsgBuffer   = (uint16_t *)&testInput[0];
    CRC.pCrcTable    = (uint16_t *)&crc16P1Table[0];
    CRC.init         = (void (*)(void *))CRC_init16Bit;
    CRC.run          = (void (*)(void *))CRC_run16BitTableLookupC;

    // Step 3: Initialize the handle
    handleCRC = &CRC;

    // Step 4: Run the 16-bit table look-up CRC routine and save the first result
    CRC.init(handleCRC);
    CRC.run(handleCRC);
    crcResultC_1 = CRC.crcResult;

    // Step 5: Load the second lookup table and run the C routine
    CRC.pCrcTable    = (uint16_t *)&crc16P2Table[0];
    CRC.crcResult    = 0;
    CRC.run(handleCRC);
    crcResultC_2 = CRC.crcResult;

    //*************************************************************************
    //! \endcode
    //!
    //! \b Example \b #1, \b Part \b 2
    //! Now we run the VCU routine on the vector testInput. The two
    //! polynomials employed by the VCU are  fixed i.e.
    //! \f$ x^{16}+x^{15}+x^{2}+1 \f$ (0x8005) and \f$ x^{16}+x^{12}+x^{5}+1 \f$
    //! (0x1021) respectively
    //! The parity chosen was CRC_parity_even indicating that the CRC will start
    //! from the low byte of the first word.
    //!
    //! Most of the object elements remain unchanged from the initial setup
    //!
    //! \note The VCU routine does not require a lookup table; pCrcTable can be
    //! reset to NULL or left as-is
    //! \code
    //*************************************************************************
    // Step 1: Reset a few elements of the CRC object
    CRC.crcResult    = 0;
    CRC.run          = (void (*)(void *))CRC_run16BitPoly1;

    // Step 2: Run the VCU 16-bit CRC routine and save the result
    CRC.run(handleCRC);
    crcResultVcu_1   = CRC.crcResult;

    // Step 3: Now for the other polynomial
    CRC.crcResult    = 0;
    CRC.run          = (void (*)(void *))CRC_run16BitPoly2;

    // Step 4: Run the VCU 16-bit CRC routine and save the result
    CRC.run(handleCRC);
    crcResultVcu_2   = CRC.crcResult;
    //*************************************************************************
    //! \endcode
    //!
    //! \b Example \b #1, \b Part \b 3
    //! The linker will compute the CRC(s) of the section \c testInput
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
    //! -# Note the use of the \b UNION keyword in the linker command file around
    //!    the \b testInput section to allow the linker to calculate two different
    //!    16-bit CRCs for the same memory block
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
        if(linkerCrcRecord.crc_alg_ID == CRC16_ALT){ //0x8005
            (crcResultLnk == crcResultVcu_1)? pass++ : fail++;
            (crcResultVcu_1 == crcResultC_1)? pass++ : fail++;
        }else if(linkerCrcRecord.crc_alg_ID == CRC16_802_15_4){ //0x1021
            (crcResultLnk == crcResultVcu_2)? pass++ : fail++;
            (crcResultVcu_2 == crcResultC_2)? pass++ : fail++;
        }else{
            fail++;
        }
    }
    //*************************************************************************
    //! \endcode
    //!
    //! \b Example \b #2
    //! We now run the reflected algorithm using both a table lookup method and
    //! compare it against its equivalent VCU routine. The reflected CRC
    //! table is specified in the header files "CrcTable0x8005Reflected.h" and
    //! "CrcTable0x1021Reflected.h"; the entries were generated from the table
    //! indices 0,1,...255 by shifting out the LSB of the index and XOR'ing the
    //! remainder with the polynomial if the LSB was a 1
    //! The parity chosen was CRC_parity_even indicating that the CRC will start
    //! from the low byte of the first word.
    //! \code
    //*************************************************************************
    // Step 1: For the C routine, assign the correct look-up table and function
    // to the object and reset the CRC result
    CRC.crcResult    = 0;
    CRC.pCrcTable    = (uint16_t *)&crc16P1TableReflected[0];
    CRC.run          = (void (*)(void *))CRC_run16BitReflectedTableLookupC;

    // Step 2: Run the C routine, reflect and save the result
    CRC.run(handleCRC);
    crcResultC_1     = (uint16_t)(CRC_bitReflect((uint32_t)CRC.crcResult, 16));

    // Step 3: Replace the lookup table with that of the second polynomial
    CRC.crcResult    = 0;
    CRC.pCrcTable    = (uint16_t *)&crc16P2TableReflected[0];
    CRC.run(handleCRC);
    crcResultC_2     = (uint16_t)(CRC_bitReflect((uint32_t)CRC.crcResult, 16));

    // Step 4: Assign the VCU routine to the object and run it
    CRC.crcResult    = 0;
    CRC.run          = (void (*)(void *))CRC_run16BitPoly1Reflected;
    CRC.run(handleCRC);
    crcResultVcu_1   = CRC.crcResult;

    // Step 5: Assign the VCU routine(2nd polynomial) to the object and run it
    CRC.crcResult    = 0;
    CRC.run          = (void (*)(void *))CRC_run16BitPoly2Reflected;
    CRC.run(handleCRC);
    crcResultVcu_2   = CRC.crcResult;

    // Step 6: Compare the results of steps 2/3 with 4/5
    (crcResultC_1 == crcResultVcu_1)? pass++ : fail++ ;
    (crcResultC_2 == crcResultVcu_2)? pass++ : fail++ ;

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
