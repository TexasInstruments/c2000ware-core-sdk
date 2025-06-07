//#############################################################################
//! \file  /dsp_vcrc_crc24_f28p55x.c
//!
//! \brief  Demo code for the 24-bit CRC routine(VCU and C)
//!
//!
//! This example shows how to
//! -# use the vcrc supported 24-bit CRC routines from the library
//! -# use a C based table lookup routine to run a 24-bit CRC check using
//!    any 24-bit polynomial
//! -# demonstrate the link time CRC generation(using the
//!    polynomials 0x8005 and 0x1021) on a specified section of memory
//
//  Group:             C2000
//  Target Family:     F28P55x
//
//#############################################################################
// 
// C2000Ware v5.05.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
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

//!
//! \defgroup CRC24_EXAMPLES Cyclic Redundancy Check 24-bit Example

//!
//! \ingroup CRC24_EXAMPLES
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

uint16_t pass = 0;
uint16_t fail = 0;

//*****************************************************************************
// function definitions
//*****************************************************************************
//!
//! \brief main routine for the 24-bit CRC example
//! \return returns a 1
//!
//! This example shows how to
//! -# use the vcu2 supported 24-bit CRC routines from the library
//! -# use a C based table lookup routine to run a 24-bit CRC check using
//!    any 24-bit polynomial
//! -# demonstrate the link time CRC generation(using the
//!    polynomial 0x5d6dcb) on a specified section of memory
//!
//! \note The variables used in the example are the same used in the CRC-8
//! example and are not documented here again.
//!
void run_vcrc_24(void)
{
    // Locals
    int16_t i;
    uint32_t crcResultC;
    uint32_t crcResultVcu;
    uint32_t crcResultLnk;

    //*************************************************************************
    // Example #1: 128 bytes(x8, even), parity: low byte first
    //*************************************************************************
    //! \b Example \b #1, \b Part \b 1
    //! In this section we run a table lookup CRC on the vector testInput. The
    //! table is specified in the header file "CrcTable0x5D6DCB.h" and
    //! the entries were generated from the polynomial
    //! \f$ x^{23}+x^{22}+x^{20}+x^{19}+x^{18}+x^{16}+x^{14}+x^{13}+x^{11}+x^{10}+x^{8}+x^{7}+x^{6}+x^{3}+x^{1}+1 \f$
    //! The parity chosen was CRC_parity_even indicating that the CRC will start
    //! from the low byte of the first word.
    //! \code
    //*************************************************************************

    // Initialize CRC objects
    extern CRC_Handle VCRC_Ex1_Handle; // Declared and intialized in syscfg

    // Step 1: Run the 24-bit table look-up CRC routine and save the first result
    VCRC_Ex1_Handle->run = VCRC_Ex1_CROUTINE;
    VCRC_Ex1_Handle->run(VCRC_Ex1_Handle);
    crcResultC = VCRC_Ex1_Handle->crcResult;

    //*************************************************************************
    //! \endcode
    //!
    //! \b Example \b #1, \b Part \b 2
    //! Now we run the VCU routine on the vector testInput. The polynomial
    //! employed by the VCU are fixed i.e.
    //! \f$ x^{23}+x^{22}+x^{20}+x^{19}+x^{18}+x^{16}+x^{14}+x^{13}+x^{11}+x^{10}+x^{8}+x^{7}+x^{6}+x^{3}+x^{1}+1 \f$
    //! (0x5d6dcb)
    //! The parity chosen was CRC_parity_even indicating that the CRC will start
    //! from the low byte of the first word.
    //!
    //! Most of the object elements remain unchanged from the initial setup
    //!
    //! \note The VCU routine does not require a lookup table; pCrcTable can be
    //! reset to NULL or left as-is
    //! \code
    //*************************************************************************
    // Step 1: Load and Run the VCU 24-bit CRC routine and save the result
    VCRC_Ex1_Handle->crcResult    = 0;
    VCRC_Ex1_Handle->run          = (void (*)(void *))CRC_run24Bit; // polynomial 0x5d6dcb
    VCRC_Ex1_Handle->run(VCRC_Ex1_Handle);
    crcResultVcu     = VCRC_Ex1_Handle->crcResult;

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
        if(linkerCrcRecord.crc_alg_ID == CRC24_FLEXRAY){ //0x5d6dcb
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
    //! table is specified in the header files "CrcTable0x5d6dcbReflected.h" and
    //! "CrcTable0x5d6dcbReflected.h"; the entries were generated from the table
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
    crcResultC = ((uint32_t)(CRC_bitReflect((uint32_t)VCRC_Ex2_Handle->crcResult, 32))) >> 8;

    // Step 3: Assign the VCU routine to the object and run it
    VCRC_Ex2_Handle->crcResult = 0;
    VCRC_Ex2_Handle->run       = (void (*)(void *))CRC_run24BitReflected; // polynomial 0x5d6dcb
    VCRC_Ex2_Handle->run(VCRC_Ex2_Handle);
    crcResultVcu     = VCRC_Ex2_Handle->crcResult;

    // Step 4: Compare the results of steps 2 and 3
    (crcResultC == crcResultVcu)? pass++ : fail++ ;

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

    run_vcrc_24();

    while(1)
    {

    }
}

// End of main

// @} //addtogroup

// End of file
