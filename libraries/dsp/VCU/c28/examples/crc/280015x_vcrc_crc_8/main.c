//#############################################################################
//! \file /2838x_vcrc_crc_8/main.c
//!
//! \brief  Demo code for the 8-bit CRC routine(VCU and C)
//!
//! \date   April 9, 2020
//! 
//! This example shows how to
//! -# use the VCRC supported 8-bit CRC routines from the library
//! -# use a C based table lookup routine to run an 8-bit CRC check using
//!    any 8-bit polynomial
//! -# demonstrate the link time CRC generation(using the
//!    polynomial 0x07) on a specified section of memory
//
//  Group:             C2000
//  Target Family:     F2838x
//
//#############################################################################
// $TI Release: C28x VCU Library V2.28.00.00 $
// $Release Date: Aug 25, 2024 $
// $Copyright: Copyright (C) 2019 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################

//*****************************************************************************
// includes
//*****************************************************************************
#include "crc_tbl.h"
#include "vcu2_types.h"
#include "vcu2_crc.h"
#include "crctable0x7.h"
#include "crctable0x7reflected.h"
#include "dsp_examples_setup.h"

//!
//! \defgroup CRC8_EXAMPLES Cyclic Redundancy Check 8-bit Example

//!
//! \ingroup CRC8_EXAMPLES
// @{

//*****************************************************************************
// defines
//*****************************************************************************
#define     NBYTES        (128)
#define     NWORDS        (NBYTES/2)
#define     NBYTESLARGE   (65560UL)
#define     NWORDSLARGE   (NBYTESLARGE/2)
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

#ifdef FLASH
#ifdef __cplusplus
#pragma DATA_SECTION("testInputLarge")
#else
#pragma DATA_SECTION(testInputLarge,"testInputLarge")
#endif //__cplusplus
//!\brief test input (Large)
//!
//! This vector is declared as a static const in order for the linker to
//! be able to run the CRC algorithm on it. It needn't be either static
//! or const for the C and VCU routines. Its size is > 65536 bytes
//!
static const uint16_t testInputLarge[NWORDSLARGE] = {
	#include "data_input.h"
};
#endif //FLASH

//!\brief linker generated object(CRC table)
//!
extern CRC_TABLE linkerCrcTable;

//!\brief linker generated object(CRC table)
//!
extern CRC_TABLE linkerCrcTableLarge;

//!\brief object of the structure CRC_Obj
//!
CRC_Obj    CRC;
//!\brief handle(pointer) to the CRC object
//!
CRC_Handle handleCRC;
//! \brief A single record(element) from the CRC table object
//!
CRC_RECORD linkerCrcRecord;
//! \brief pointer to the CRC table object
//!
CRC_TABLE *pLinkerCrcTable;

uint16_t pass = 0;
uint16_t fail = 0;

void error(void);

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
//! -# use the vcu2 supported 8-bit CRC routine from the library
//! -# use a C based table lookup routine to run an 8-bit CRC check using
//!    any 8-bit polynomial
//! -# demonstrate the link time CRC generation(using the
//!    polynomial 0x07) on a specified section of memory
//!
int main( void )
{
    // Locals
    int16_t i;
    uint32_t crcResultC;
    uint32_t crcResultVcu;
    uint32_t crcResultLnk;

#if defined(_FLASH)
    //
    // Setup the FLASH Banks
    //
    DSP_Example_setupFlash();
#endif //defined(_FLASH)

    //
    // Setup system clocking
    //
    DSP_Example_setupSysCtrl();

    //*************************************************************************
    // Example #1: 128 bytes(x8, even), parity: low byte first
    //*************************************************************************
    //! \b Example \b #1, \b Part \b 1
    //! In this section we run a table lookup CRC on the vector testInput. The
    //! table is specified in the header file "CrcTable0x7.h" and the entries
    //! were generated from the polynomial \f$ x^{8}+x^{2}+x^{1}+1 \f$ (0x07)
    //! The parity chosen was CRC_parity_even indicating that the CRC will start
    //! from the low byte of the first word.
    //! \code
    //*************************************************************************
    // Step 1: Initialize the CRC object
    CRC.seedValue    = INIT_CRC8;
    CRC.nMsgBytes    = NBYTES;
    CRC.parity       = CRC_parity_even;
    CRC.crcResult    = 0;
    CRC.pMsgBuffer   = (uint16_t *)&testInput[0];
    CRC.pCrcTable    = (uint16_t *)&crc8Table[0];
    CRC.init         = (void (*)(void *))CRC_init8Bit;
    CRC.run          = (void (*)(void *))CRC_run8BitTableLookupC;

    // Step 2: Initialize the handle
    handleCRC = &CRC;

    // Step 3: Run the 8-bit table look-up CRC routine and save the result
    CRC.init(handleCRC);
    CRC.run(handleCRC);
    crcResultC = CRC.crcResult;
    //*************************************************************************
    //! \endcode
    //!
    //! \b Example \b #1, \b Part \b 2
    //! Now we run the VCU routine on the vector testInput. The
    //! polynomial employed by the VCU is fixed i.e.
    //! \f$ x^{8}+x^{2}+x^{1}+1 \f$ (0x07)
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
    CRC.run          = (void (*)(void *))CRC_run8Bit;

    // Step 2: Run the VCU 8-bit CRC routine and save the result
    CRC.run(handleCRC);
    crcResultVcu     = CRC.crcResult;
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
            (crcResultLnk == crcResultVcu)? pass++ : fail++;
            (crcResultVcu == crcResultC)? pass++ : fail++;
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
    //! table is specified in the header file "CrcTable0x7Reflected.h"; the
    //! entries were generated from the table indices 0,1,...255 by shifting out
    //! the LSB of the index and XOR'ing the remainder with the polynomial if the
    //! LSB was a 1
    //! The parity chosen was CRC_parity_even indicating that the CRC will start
    //! from the low byte of the first word.
    //! \code
    //*************************************************************************
    // Step 1: For the C routine, assign the correct look-up table and function
    // to the object and reset the CRC result
    CRC.crcResult    = 0;
    CRC.pCrcTable    = (uint16_t *)&crc8TableReflected[0];
    CRC.run          = (void (*)(void *))CRC_run8BitTableLookupC;

    // Step 2: Run the C routine, reflect and save the result
    CRC.run(handleCRC);
    crcResultC       = (uint32_t)(CRC_bitReflect((uint32_t)CRC.crcResult, 8));

    // Step 3: Assign the VCU routine to the object and run it
    CRC.crcResult    = 0;
    CRC.run          = (void (*)(void *))CRC_run8BitReflected;
    CRC.run(handleCRC);
    crcResultVcu     = CRC.crcResult;

    // Step 4: Compare the results of steps 2 and 3
    if(crcResultC == crcResultVcu){
        pass++;
    }else{
        fail++;
    }

    //*************************************************************************
    //!
    //! \endcode
    //!
    //*************************************************************************
#ifdef FLASH
    //*************************************************************************
	// Example #3: 65560 bytes(x8, even), parity: low byte first
	//*************************************************************************
	//! \b Example \b #3, \b Part \b 1
	//! In this section we run a table lookup CRC on the vector testInputLarge,
	//! whose size exceeds the 16-bit boundary.
	//! The table is specified in the header file "CrcTable0x7.h" and the entries
	//! were generated from the polynomial \f$ x^{8}+x^{2}+x^{1}+1 \f$ (0x07)
	//! The parity chosen was CRC_parity_even indicating that the CRC will start
	//! from the low byte of the first word.
	//! \code
	//*************************************************************************
	// Step 1: Initialize the CRC object
    CRC.pMsgBuffer   = (uint16_t *)&testInputLarge[0];
    CRC.parity       = CRC_parity_even;
	CRC.crcResult    = 0;
	CRC.pCrcTable    = (uint16_t *)&crc8Table[0];
	CRC.init         = (void (*)(void *))CRC_init8Bit;
	CRC.run          = (void (*)(void *))CRC_run8BitTableLookupC;

	CRC.seedValue    = INIT_CRC8;
    q = (uint16_t)((uint32_t)(NBYTESLARGE & 0xFFFF0000) >> 16); // multiples of 65536
    // Since we can do a max of 65535 bytes at a time, we need to add q
    // to r to do the remainder
    r = (uint16_t)((NBYTESLARGE & 0x0000FFFF)) + q; // modulus 65535

	// Step 2: Initialize the handle
	handleCRC = &CRC;

	// Step 3: Run the 8-bit table look-up CRC routine and save the result
	CRC.init(handleCRC);

	// Run the CRC for 65535 bytes q times
	for(i = 0; i < q; i++){
		//When CRC starts on low byte, it ends on a low byte, the next
		// set of 65535 bytes must start with high byte of the last address
		CRC.nMsgBytes    = 0xFFFF; // 65535 bytes
		CRC.run(handleCRC);
		CRC.seedValue    = CRC.crcResult;
		CRC.parity       ^= 1;
		CRC.pMsgBuffer   = (uint16_t *)&testInputLarge[(i+1)*0x8000 - CRC.parity];
	}
	// Run the CRC on the remaining r bytes
	CRC.nMsgBytes    = r; // <= 65535 bytes
	CRC.run(handleCRC);

	crcResultC = CRC.crcResult;
	//*************************************************************************
	//! \endcode
	//!
	//! \b Example \b #3, \b Part \b 2
	//! Now we run the VCU routine on the vector testInput. The
	//! polynomial employed by the VCU is fixed i.e.
	//! \f$ x^{8}+x^{2}+x^{1}+1 \f$ (0x07)
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
	CRC.pMsgBuffer   = (uint16_t *)&testInputLarge[0];
	CRC.parity       = CRC_parity_even;
	CRC.crcResult    = 0;
	CRC.seedValue    = INIT_CRC8;
	CRC.run          = (void (*)(void *))CRC_run8Bit;

	// Step 2: Run the VCU 8-bit CRC routine and save the result
	// Run the CRC for 65535 bytes q times
	for(i = 0; i < q; i++){
		CRC.nMsgBytes    = 0xFFFF; // 65535 bytes
		CRC.run(handleCRC);
		CRC.seedValue    = CRC.crcResult;
		CRC.parity       ^= 1;
		CRC.pMsgBuffer   = (uint16_t *)&testInputLarge[(i+1)*0x8000 - CRC.parity];
	}
	// Run the CRC on the remaining r bytes
	CRC.nMsgBytes    = r; // <= 65535 bytes
	CRC.run(handleCRC);

	crcResultVcu     = CRC.crcResult;
	//*************************************************************************
	//! \endcode
	//!
	//! \b Example \b #3, \b Part \b 3
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

	pLinkerCrcTable  = &linkerCrcTableLarge;

	// Step 2: Get the CRC results from the linker CRC table
	for(i = 0; i < pLinkerCrcTable->num_recs; i++){
		// Get the current CRC record
		linkerCrcRecord = pLinkerCrcTable->recs[i];
		// Get the linker generated CRC
		crcResultLnk    = linkerCrcRecord.crc_value;
		if(linkerCrcRecord.crc_alg_ID == CRC8_PRIME){ //0x7
			(crcResultLnk == crcResultVcu)? pass++ : fail++;
			(crcResultVcu == crcResultC)? pass++ : fail++;
		}else{
			fail++;
		}
	}

	//*************************************************************************
	//!
	//! \endcode
	//!
	//*************************************************************************
#endif //FLASH
    // End of test
	
	//if the any of the example fails - code will loop forever in error function
	if (fail > 0) {
		error();
	}
	
	//if all the examples pass code will loop forever in the while below 
	 while(1);
	
    // Execution never reaches this point
    return 1;
}
// End of main

void error(void)
{
    ESTOP0;  //Test failed!! Stop!
    for (;;);
}

// @} //addtogroup

// End of file
