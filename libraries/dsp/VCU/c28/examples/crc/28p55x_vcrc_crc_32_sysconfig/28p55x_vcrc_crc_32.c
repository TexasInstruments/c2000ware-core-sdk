//#############################################################################
//! \file /28p55x_vcrc_crc_32.c
//!
//! \brief  Demo code for the 32-bit CRC routine(VCU and C)
//!
//!
//! This example shows how to
//! -# use the vcrc supported 32-bit CRC routines from the library
//! -# use a C based table lookup routine to run a 32-bit CRC check using
//!    any 32-bit polynomial
//! -# demonstrate the link time CRC generation(using the
//!    polynomials 0x04C11DB7 and 0x1EDC6F41) on a specified section of memory
//
//  Group:             C2000
//  Target Family:     F28P55x
//
//#############################################################################
// $Copyright: Copyright (C) 2025 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################

//*****************************************************************************
// includes
//*****************************************************************************
#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "c2000ware_libraries.h"
#include "stdio.h"

#include "crc_tbl.h"
#include "common/crctable0x1edc6f41.h"
#include "common/crctable0x1edc6f41reflected.h"

//!
//! \defgroup CRC32_EXAMPLES Cyclic Redundancy Check 32-bit Example

//!
//! \ingroup CRC32_EXAMPLES
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
#pragma DATA_SECTION(testData,"testInput")
#endif //__cplusplus

//\brief test input
//
// This vector is declared as a static const in order for the linker to
// be able to run the CRC algorithm on it. It needn't be either static
// or const for the C and VCU routines
//
static const uint16_t testData[NWORDS] = {
    0x4001, 0x8002, 0xC003, 0x0004, 0x4005, 0x8006, 0xC007, 0x0008,
    0x4009, 0x800A, 0xC00B, 0x000C, 0x400D, 0x800E, 0xC00F, 0x0010,
    0x4011, 0x8012, 0xC013, 0x0014, 0x4015, 0x8016, 0xC017, 0x0018,
    0x4019, 0x801A, 0xC01B, 0x001C, 0x401D, 0x801E, 0xC01F, 0x0020,
    0x4021, 0x8022, 0xC023, 0x0024, 0x4025, 0x8026, 0xC027, 0x0028,
    0x4029, 0x802A, 0xC02B, 0x002C, 0x402D, 0x802E, 0xC02F, 0x0030,
    0x4031, 0x8032, 0xC033, 0x0034, 0x4035, 0x8036, 0xC037, 0x0038,
    0x4039, 0x803A, 0xC03B, 0x003C, 0x403D, 0x803E, 0xC03F, 0x0040,
};
void* testInput = testData;

// \brief linker generated object(CRC table)
//
extern CRC_TABLE linkerCrcTable;

// \brief pointer to the CRC table object
//
CRC_TABLE *pLinkerCrcTable;

// \brief A single record(element) from the CRC table object
//
CRC_RECORD linkerCrcRecord;

// \brief linker generated variables defining the load and run placements
// of the testInput vector
//
extern uint32_t testInputLoadStart, testInputLoadSize, testInputRunStart;

uint16_t pass = 0;
uint16_t fail = 0;

//*****************************************************************************
// function definitions
//*****************************************************************************
//!
//! \brief main routine for the 32-bit CRC example
//! \return returns a 1
//!
//! This example shows how to
//! -# use the vcrc/vcu2 supported 32-bit CRC routines from the library
//! -# use a C based table lookup routine to run a 32-bit CRC check using
//!    any 32-bit polynomial
//! -# demonstrate the link time CRC generation(using the
//!    polynomials 0x04C11DB7 and 0x1EDC6F41) on a specified section of memory
//!
//! \note The variables used in the example are the same used in the CRC-8
//! example and are not documented here again.
//!
int run_vcrc_32(void)
{
    // Locals
    int16_t i;
    uint32_t crcResultC_1, crcResultC_2 ;
    uint32_t crcResultVcu_1, crcResultVcu_2;
    uint32_t crcResultLnk;

    //*************************************************************************
    // Example #1: 128 bytes(x8, even), parity: low byte first
    //*************************************************************************
    //! \b Example \b #1, \b Part \b 1
    //! In this section we run a table lookup CRC on the vector testInput. The
    //! table is specified in the header files "CrcTable0x04C11DB7.h" and
    //! "CrcTable0x1EDC6F41.h"respectively and the entries were generated from the
    //! polynomials \f$ x^{32}+x^{26}+x^{23}+x^{22}+x^{16}+x^{12}+x^{11}+x^{10}+x^{8}+x^{7}+x^{5}+x^{4}+x^{2}+x^{1}+1 \f$(CCITT-32, 0x04C11DB7) and
    //! \f$ x^{32}+x^{28}+x^{27}+x^{26}+x^{25}+x^{23}+x^{22}+x^{20}+x^{19}+x^{18}+x^{14}+x^{13}+x^{11}+x^{10}+x^{9}+x^{8}+x^{6}+1 \f$(0x1EDC6F41) respectively.
    //! The parity chosen was CRC_parity_even indicating that the CRC will start
    //! from the low byte of the first word.
    //! \code
    //*************************************************************************
    // Step 1: Copy the test input vector from its load location to the run location.
    // This is necessary since the section was declared within a UNION in the linker
    // command file
    memcpy((uint32_t *)&testInputRunStart, (uint32_t *)&testInputLoadStart,
                    (uint32_t)&testInputLoadSize );

    // Initialize CRC objects
    extern CRC_Handle VCRC_Ex1_Handle; // Declared and intialized in syscfg

    // Step 2: Run the 32-bit table look-up CRC routine and save the first result
    VCRC_Ex1_Handle->run = VCRC_Ex1_CROUTINE;
    VCRC_Ex1_Handle->run(VCRC_Ex1_Handle);
    crcResultC_1 = VCRC_Ex1_Handle->crcResult;

    // Step 3: Load the second lookup table and run the C routine

    VCRC_Ex1_Handle->pCrcTable = (uint16_t*)crc32P2Table;
    VCRC_Ex1_Handle->crcResult = 0;
    VCRC_Ex1_Handle->run(VCRC_Ex1_Handle);
    crcResultC_2 = VCRC_Ex1_Handle->crcResult;

    //*************************************************************************
    //! \endcode
    //!
    //! \b Example \b #1, \b Part \b 2
    //! Now we run the VCU routine on the vector testInput. The two
    //! polynomials employed by the VCU are  fixed i.e.
    //! \f$ x^{32}+x^{26}+x^{23}+x^{22}+x^{16}+x^{12}+x^{11}+x^{10}+x^{8}+x^{7}+x^{5}+x^{4}+x^{2}+x^{1}+1 \f$(CCITT-32, 0x04C11DB7) and
    //! \f$ x^{32}+x^{28}+x^{27}+x^{26}+x^{25}+x^{23}+x^{22}+x^{20}+x^{19}+x^{18}+x^{14}+x^{13}+x^{11}+x^{10}+x^{9}+x^{8}+x^{6}+1 \f$(0x1EDC6F41) respectively
    //! The parity chosen was CRC_parity_even indicating that the CRC will start
    //! from the low byte of the first word.
    //!
    //! Most of the object elements remain unchanged from the initial setup
    //!
    //! \note The VCU routine does not require a lookup table; pCrcTable can be
    //! reset to NULL or left as-is
    //! \code
    //*************************************************************************

    // Step 1: Load and Run the VCU 32-bit CRC routine and save the result
    VCRC_Ex1_Handle->crcResult = 0;
    VCRC_Ex1_Handle->run       = (void (*)(void *))CRC_run32BitPoly1; // Using polynomial 0x04c11db7
    VCRC_Ex1_Handle->run(VCRC_Ex1_Handle);
    crcResultVcu_1   = VCRC_Ex1_Handle->crcResult;

    // Step 2: Load and Run another VCU 32-bit CRC routine and save the result
    VCRC_Ex1_Handle->crcResult = 0;
    VCRC_Ex1_Handle->run       = (void (*)(void *))CRC_run32BitPoly2; // Using polynomial 0x1edc6f41
    VCRC_Ex1_Handle->run(VCRC_Ex1_Handle);
    crcResultVcu_2   = VCRC_Ex1_Handle->crcResult;

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
    //!    32-bit CRCs for the same memory block
    //!
    //!  \code
    //*************************************************************************
    // Step 1: Initialize the CRC table pointer.
    pLinkerCrcTable = &linkerCrcTable;

    // Step 2: Get the CRC results from the linker CRC table
    for(i = 0; i < pLinkerCrcTable->num_recs; i++){
        // Get the current CRC record
        linkerCrcRecord = pLinkerCrcTable->recs[i];
        // Get the linker generated CRC
        crcResultLnk    = linkerCrcRecord.crc_value;
        if(linkerCrcRecord.crc_alg_ID == CRC32_PRIME){ //0x04C11DB7
            (crcResultLnk == crcResultVcu_1)? pass++ : fail++;
            (crcResultVcu_1 == crcResultC_1)? pass++ : fail++;
        }else if(linkerCrcRecord.crc_alg_ID == CRC32_C){ //0x1EDC6F41
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
    //! table is specified in the header files "CrcTable0x04C11DB7Reflected.h" and
    //! "CrcTable0x1EDC6F41Reflected.h"; the entries were generated from the table
    //! indices 0,1,...255 by shifting out the LSB of the index and XOR'ing the
    //! remainder with the polynomial if the LSB was a 1
    //! The parity chosen was CRC_parity_even indicating that the CRC will start
    //! from the low byte of the first word.
    //! \code
    //*************************************************************************

    // Initialize CRC objects
    extern CRC_Handle VCRC_Ex2_Handle; // Declared and intialized in syscfg

    // Step 1: Run the C routine, reflect and save the result
    VCRC_Ex2_Handle->run = VCRC_Ex2_CROUTINE;
    VCRC_Ex2_Handle->run(VCRC_Ex2_Handle);
    crcResultC_1     = (uint32_t)(CRC_bitReflect((uint32_t)VCRC_Ex2_Handle->crcResult, 32));

    // Step 2: Replace the lookup table with that of the second polynomial

    VCRC_Ex2_Handle->crcResult    = 0;
    VCRC_Ex2_Handle->pCrcTable    = (uint16_t *)&crc32P2TableReflected[0];
    VCRC_Ex2_Handle->run(VCRC_Ex2_Handle);
    crcResultC_2     = (uint32_t)(CRC_bitReflect((uint32_t)VCRC_Ex2_Handle->crcResult, 32));

    // Step 3: Assign the VCU routine to the object and run it
    VCRC_Ex2_Handle->crcResult    = 0;
    VCRC_Ex2_Handle->run          = (void (*)(void *))CRC_run32BitPoly1Reflected;
    VCRC_Ex2_Handle->run(VCRC_Ex2_Handle);
    crcResultVcu_1   = VCRC_Ex2_Handle->crcResult;

    // Step 4: Assign the VCU routine(2nd polynomial) to the object and run it
    VCRC_Ex2_Handle->crcResult    = 0;
    VCRC_Ex2_Handle->run          = (void (*)(void *))CRC_run32BitPoly2Reflected;
    VCRC_Ex2_Handle->run(VCRC_Ex2_Handle);
    crcResultVcu_2   = VCRC_Ex2_Handle->crcResult;

    // Step 6: Compare the results of steps 2/3 with 4/5
    (crcResultC_1 == crcResultVcu_1)? pass++ : fail++ ;
    (crcResultC_2 == crcResultVcu_2)? pass++ : fail++ ;

    //*************************************************************************
    //!
    //! \endcode
    //!
    //*************************************************************************
    // End of test

    printf("Total of %d tests pass, and %d failure",pass,fail);

    return 1;
}

//
// Main
//
void main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pull-ups.
    //
    Device_initGPIO();

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // PinMux and Peripheral Initialization
    //
    Board_init();

    //
    // C2000Ware Library initialization
    //
    C2000Ware_libraries_init();

    //
    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    //
    EINT;
    ERTM;

    run_vcrc_32();

    while(1)
    {

    }
}

// End of main

// @} //addtogroup

// End of file
