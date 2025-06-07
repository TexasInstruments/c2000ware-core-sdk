//###############################################################################
//! \file /dsp_vcrc_config_poly_f28p55x.c
//!
//! \brief  Demo code for the configurable polynomial and data sizes (VCRC and C)
//!
//! This example shows how to
//! -# use the VCRC supported configurable polynomial and datasizes
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

//!
//! \addtogroup VCRC_EXAMPLES Complex Fast Fourier Transform

// @{

//*****************************************************************************
// defines
//*****************************************************************************
#define NO_OF_TESTS 22
#define NBYTES1 128
#define NWORDS1 NBYTES1/2

//*****************************************************************************
// Sizes - The following defines are used to set the polynomial size and
// data size on which the CRC is computed by the CRC engine
// Polynomial size-size of of 1 bit - indicated by programming a value of 0x0
// Polynomial size-size of of 32bits - indicated by programming a value of 0x1F
// Similarly Data size -size of 1 bit - indicated by programming a value of 0x0
// Data size - size of 8 bits is indicated by programming a value of 0x7
// These are to be set in the VCRCSIZE register - PSIZE and DSIZE fields

#define SIZE_32_BITS  31
#define SIZE_31_BITS  30
#define SIZE_30_BITS  29
#define SIZE_29_BITS  28
#define SIZE_28_BITS  27
#define SIZE_27_BITS  26
#define SIZE_26_BITS  25
#define SIZE_25_BITS  24
#define SIZE_24_BITS  23
#define SIZE_23_BITS  22
#define SIZE_22_BITS  21
#define SIZE_21_BITS  20
#define SIZE_20_BITS  19
#define SIZE_19_BITS  18
#define SIZE_18_BITS  17
#define SIZE_17_BITS  16
#define SIZE_16_BITS  15
#define SIZE_15_BITS  14
#define SIZE_14_BITS  13
#define SIZE_13_BITS  12
#define SIZE_12_BITS  11
#define SIZE_11_BITS  10
#define SIZE_10_BITS  9
#define SIZE_9_BITS   8
#define SIZE_8_BITS   7
#define SIZE_7_BITS   6
#define SIZE_6_BITS   5
#define SIZE_5_BITS   4
#define SIZE_4_BITS   3
#define SIZE_3_BITS   2
#define SIZE_2_BITS   1
#define SIZE_1_BITS   0

//*****************************************************************************
// globals
//*****************************************************************************

uint32_t TestOutput[NO_OF_TESTS];
uint32_t goldenOutput[NO_OF_TESTS];

#ifdef __cplusplus
#pragma DATA_SECTION("testInput")
#else
#pragma DATA_SECTION(testInput,"testInput")
#endif //__cplusplus
uint16_t testData[NWORDS1] = {
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

uint16_t pass = 0;
uint16_t fail = 0;

//*****************************************************************************
// Extern function for C compuations of CRC
//*****************************************************************************
extern void CRC_run4BitENDATTableLookupC(CRC_Handle);
extern void CRC_run4BitENDATBitTableLookupC_Generic(CRC_Handle);
extern void CRC_run16BitTableLookupC(CRC_Handle);
extern void CRC_run16BitReflectedTableLookupC(CRC_Handle);
extern void CRC_run32BitTableLookupC(CRC_Handle);
extern void CRC_run32BitReflectedTableLookupC(CRC_Handle);
extern void CRC_run17BitCANFDTableLookupC(CRC_Handle);
extern void CRC_run8BitTableLookupC(CRC_Handle);

int run_vcrc_examples(void)
{
    //******************************************************************************************************
    // Note -
    // Polynomial size - size of of 1 bit - indicated by programming a value of 0x0
    // Polynomial size - size of of 32bits - indicated by programming a value of 0x1F
    // Datasize refers to the integral unit on which the CRC is computed
    // Data size - size of 1 bit - indicated by programming a value of 0x0
    // Data size - size of 8 bits is indicated by programming a value of 0x7
    // These are to be set in the VCRCSIZE register - PSIZE and DSIZE fields and they are
    // set in the functions _CRC_runConfigPolyBytes and _CRC_runConfigPolyBits implemented in the asm file
    // vcrc_configpoly_asm.asm
    // Total size of the message on which the CRC to be computed is specified by 2 elements MsgBytes and MsgBits
    // If the size of the message is in bytes - then set the value of CRC.nMsgBytes to the size of the message
    // and call the function - CRC_runConfigPolyBytes
    // if the size of the message cannot be specified in bytes - then set the value of CRC.nMsgBits to the size
    // of the message in bits and call the function - _CRC_runConfigPolyBits

    int index = 0;

    //******************************************************************************************************
    //EXAMPLE 1 and 2 - Byte wise 4 bit CRC computation for different Msg Sizes -> 128, 7 bytes respectively

    //*****************************************************************************************
    // FIRST EXAMPLE: 128 bytes, Parity is low byte first and CRC computation in reflected mode
    //*****************************************************************************************

    // Initialize CRC objects
    extern CRC_Handle VCRC_Ex1_Handle; // Declared and intialized in syscfg

    // Step 1: Calculate the golden value using the C routine
    VCRC_Ex1_Handle->run = VCRC_Ex1_CROUTINE;
    VCRC_Ex1_Handle->run(VCRC_Ex1_Handle);
    goldenOutput[index] = (uint16_t)VCRC_Ex1_Handle->crcResult;

    // Step 2: run the CRC module with the VCRC assembly code
    VCRC_Ex1_Handle->run = VCRC_Ex1_CRCRUN;
    VCRC_Ex1_Handle->run(VCRC_Ex1_Handle);
    TestOutput[index++] = (uint16_t)VCRC_Ex1_Handle->crcResult;

    //*************************************************************************************************
    // SECOND EXAMPLE: 7 bytes(<8, odd), Parity is low byte first and CRC computation in reflected mode
    //*************************************************************************************************

    // Initialize CRC objects
    extern CRC_Handle VCRC_Ex2_Handle; // Declared and intialized in syscfg

    // Step 1: Calculate the golden value using the C routine
    VCRC_Ex2_Handle->run = VCRC_Ex2_CROUTINE;
    VCRC_Ex2_Handle->run(VCRC_Ex2_Handle);
    goldenOutput[index] = (uint16_t)VCRC_Ex2_Handle->crcResult;

    // Step 2: run the CRC module with the VCRC assembly code
    VCRC_Ex2_Handle->run = VCRC_Ex2_CRCRUN;
    VCRC_Ex2_Handle->run(VCRC_Ex2_Handle);
    TestOutput[index++] = (uint16_t)VCRC_Ex2_Handle->crcResult;

    //****************************************************************************************************
    //Example 3 and 4 - Bit wise 4 bit CRC computation for different Msg Sizes -> 13, 51 bits respectively

    //**************************************************************************************************
    // THIRD EXAMPLE: 13 bits, Parity is low byte first and CRC computation in reflected mode
    //**************************************************************************************************

    // Initialize CRC objects
    extern CRC_Handle VCRC_Ex3_Handle; // Declared and intialized in syscfg

    // Step 1: Calculate the golden value using the C routine
    VCRC_Ex3_Handle->run = VCRC_Ex3_CROUTINE;
    VCRC_Ex3_Handle->run(VCRC_Ex3_Handle);
    goldenOutput[index] = (uint16_t)VCRC_Ex3_Handle->crcResult;

    // Step 2: run the CRC module with the VCRC assembly code
    VCRC_Ex3_Handle->run = VCRC_Ex3_CRCRUN;
    VCRC_Ex3_Handle->run(VCRC_Ex3_Handle);
    TestOutput[index++] = (uint16_t)VCRC_Ex3_Handle->crcResult;

    //*************************************************************************
    // FOURTH EXAMPLE: 51 bits, parity: low byte first
    //*************************************************************************

    // Initialize CRC objects
    extern CRC_Handle VCRC_Ex4_Handle; // Declared and intialized in syscfg

    // Step 1: Calculate the golden value using the C routine
    VCRC_Ex4_Handle->run = VCRC_Ex4_CROUTINE;
    VCRC_Ex4_Handle->run(VCRC_Ex4_Handle);
    goldenOutput[index] = (uint16_t)VCRC_Ex4_Handle->crcResult;

    // Step 2: run the CRC module with the VCRC assembly code
    VCRC_Ex4_Handle->run = VCRC_Ex4_CRCRUN;
    VCRC_Ex4_Handle->run(VCRC_Ex4_Handle);
    TestOutput[index++] = (uint16_t)VCRC_Ex4_Handle->crcResult;

    //***************************************************************************************
    //Example 5 and 6 - Byte wise 16 bit CRC computation for Msg Sizes - 8, 128 bytes of data

    //***************************************************************************************
    // FIFTH EXAMPLE: 8 Bytes, Parity is low byte first and CRC computation in reflected mode
    //***************************************************************************************

    // Initialize CRC objects
    extern CRC_Handle VCRC_Ex5_Handle; // Declared and intialized in syscfg

    // Step 1: Calculate the golden value using the C routine
    VCRC_Ex1_Handle->run = VCRC_Ex5_CROUTINE;
    VCRC_Ex5_Handle->run(VCRC_Ex5_Handle);
    goldenOutput[index] = (uint16_t)VCRC_Ex5_Handle->crcResult;

    // Step 2: run the CRC module with the VCRC assembly code
    VCRC_Ex5_Handle->run = VCRC_Ex5_CRCRUN;
    VCRC_Ex5_Handle->run(VCRC_Ex5_Handle);
    TestOutput[index++] = (uint16_t)VCRC_Ex5_Handle->crcResult;

    //*********************************************************************************************
    // SIXTH EXAMPLE: 128 bytes, Parity is low byte first and CRC computation in non-reflected mode
    //*********************************************************************************************

    // Initialize CRC objects
    extern CRC_Handle VCRC_Ex6_Handle; // Declared and intialized in syscfg

    // Step 1: Calculate the golden value using the C routine
    VCRC_Ex6_Handle->run = VCRC_Ex6_CROUTINE;
    VCRC_Ex6_Handle->run(VCRC_Ex6_Handle);
    goldenOutput[index] = (uint16_t)VCRC_Ex6_Handle->crcResult;

    // Step 2: run the CRC module with the VCRC assembly code
    VCRC_Ex6_Handle->run = VCRC_Ex6_CRCRUN;
    VCRC_Ex6_Handle->run(VCRC_Ex6_Handle);
    TestOutput[index++] = (uint16_t)VCRC_Ex6_Handle->crcResult;

    //******************************************************************************************
    // Example 7 and 8 - Bit wise 16 bit CRC computation for Msg Sizes - 48, 128 bits of data

    //******************************************************************************************************
    // SEVENTH EXAMPLE: 48 bits(i.e 6 bytes), Parity is low byte first and CRC computation in reflected mode
    //******************************************************************************************************

    // Initialize CRC objects
    extern CRC_Handle VCRC_Ex7_Handle; // Declared and intialized in syscfg

    // Step 1: Calculate the golden value using the C routine
    VCRC_Ex7_Handle->run = VCRC_Ex7_CROUTINE;
    VCRC_Ex7_Handle->run(VCRC_Ex7_Handle);
    goldenOutput[index] = (uint16_t)VCRC_Ex7_Handle->crcResult;

    // Step 2: run the CRC module with the VCRC assembly code
    VCRC_Ex7_Handle->run = VCRC_Ex7_CRCRUN;
    VCRC_Ex7_Handle->run(VCRC_Ex7_Handle);
    TestOutput[index++] = (uint16_t)VCRC_Ex7_Handle->crcResult;

    //********************************************************************************************
    // EIGHTH EXAMPLE: 128 bits, Parity is low byte first and CRC computation in non-reflected mode
    //********************************************************************************************

    // Initialize CRC objects
    extern CRC_Handle VCRC_Ex8_Handle; // Declared and intialized in syscfg

    // Step 1: Calculate the golden value using the C routine
    VCRC_Ex8_Handle->run = VCRC_Ex8_CROUTINE;
    VCRC_Ex8_Handle->run(VCRC_Ex8_Handle);
    goldenOutput[index] = (uint16_t)VCRC_Ex8_Handle->crcResult;

    // Step 2: run the CRC module with the VCRC assembly code
    VCRC_Ex8_Handle->run = VCRC_Ex8_CRCRUN;
    VCRC_Ex8_Handle->run(VCRC_Ex8_Handle);
    TestOutput[index++] = (uint16_t)VCRC_Ex8_Handle->crcResult;

    //***************************************************************************************************
    // Example 9 and 10 - Byte wise 16 bit CRC computation for different Msg Sizes - 10, 15 bytes of data
    //***************************************************************************************************
    // NINETH EXAMPLE: 10 bytes, Parity is high byte first and CRC computation in reflected mode
    //******************************************************************************************

    // Initialize CRC objects
    extern CRC_Handle VCRC_Ex9_Handle; // Declared and intialized in syscfg

    // Step 1: Calculate the golden value using the C routine
    VCRC_Ex9_Handle->run = VCRC_Ex9_CROUTINE;
    VCRC_Ex9_Handle->run(VCRC_Ex9_Handle);
    goldenOutput[index] = (uint16_t)VCRC_Ex9_Handle->crcResult;

    // Step 2: run the CRC module with the VCRC assembly code
    VCRC_Ex9_Handle->run = VCRC_Ex9_CRCRUN;
    VCRC_Ex9_Handle->run(VCRC_Ex9_Handle);
    TestOutput[index++] = (uint16_t)VCRC_Ex9_Handle->crcResult;

    //*********************************************************************************************
    // TENTH EXAMPLE: 15 bytes, Parity is high byte first and CRC computation in non-reflected mode
    //*********************************************************************************************

    // Initialize CRC objects
    extern CRC_Handle VCRC_Ex10_Handle; // Declared and intialized in syscfg

    // Step 1: Calculate the golden value using the C routine
    VCRC_Ex10_Handle->run = VCRC_Ex10_CROUTINE;
    VCRC_Ex10_Handle->run(VCRC_Ex10_Handle);
    goldenOutput[index] = (uint16_t)VCRC_Ex10_Handle->crcResult;

    // Step 2: run the CRC module with the VCRC assembly code
    VCRC_Ex10_Handle->run = VCRC_Ex10_CRCRUN;
    VCRC_Ex10_Handle->run(VCRC_Ex10_Handle);
    TestOutput[index++] = (uint16_t)VCRC_Ex10_Handle->crcResult;

    //*************************************************************************************
    // Example 11 and 12 - Bit wise 16 bit CRC computation for Msg Sizes - 6 bytes of data

    //*******************************************************************************************
    // ELEVENTH EXAMPLE: 48 bits, Parity is high byte first and CRC computation in reflected mode
    //*******************************************************************************************

    // Initialize CRC objects
    extern CRC_Handle VCRC_Ex11_Handle; // Declared and intialized in syscfg

    // Step 1: Calculate the golden value using the C routine
    VCRC_Ex11_Handle->run = VCRC_Ex11_CROUTINE;
    VCRC_Ex11_Handle->run(VCRC_Ex11_Handle);
    goldenOutput[index] = (uint16_t)VCRC_Ex11_Handle->crcResult;

    // Step 2: run the CRC module with the VCRC assembly code
    VCRC_Ex11_Handle->run = VCRC_Ex11_CRCRUN;
    VCRC_Ex11_Handle->run(VCRC_Ex11_Handle);
    TestOutput[index++] = (uint16_t)VCRC_Ex11_Handle->crcResult;

    //***********************************************************************************************
    // TWELVETH EXAMPLE: 48 bits, Parity is high byte first and CRC computation in non-reflected mode
    //***********************************************************************************************

    // Initialize CRC objects
    extern CRC_Handle VCRC_Ex12_Handle; // Declared and intialized in syscfg

    // Step 1: Calculate the golden value using the C routine
    VCRC_Ex12_Handle->run = VCRC_Ex12_CROUTINE;
    VCRC_Ex12_Handle->run(VCRC_Ex12_Handle);
    goldenOutput[index] = (uint16_t)VCRC_Ex12_Handle->crcResult;

    // Step 2: run the CRC module with the VCRC assembly code
    VCRC_Ex12_Handle->run = VCRC_Ex12_CRCRUN;
    VCRC_Ex12_Handle->run(VCRC_Ex12_Handle);
    TestOutput[index++] = (uint16_t)VCRC_Ex12_Handle->crcResult;

    //***************************************************************************************************************
    // Example 13 and 14 - Bit wise 16 bit CRC computation for MODBUS protocol with P2 polynomial for 48 bits of data

    //************************************************************************************************
    // THIRTEENTH EXAMPLE: 48 bits, Parity is low byte first and CRC computation in non-reflected mode
    //************************************************************************************************

    // Initialize CRC objects
    extern CRC_Handle VCRC_Ex13_Handle; // Declared and intialized in syscfg

    // Step 1: Calculate the golden value using the C routine
    VCRC_Ex13_Handle->run = VCRC_Ex13_CROUTINE;
    VCRC_Ex13_Handle->run(VCRC_Ex13_Handle);
    goldenOutput[index] = (uint16_t)VCRC_Ex13_Handle->crcResult;

    // Step 2: run the CRC module with the VCRC assembly code
    VCRC_Ex13_Handle->run = VCRC_Ex13_CRCRUN;
    VCRC_Ex13_Handle->run(VCRC_Ex13_Handle);
    TestOutput[index++] = (uint16_t)VCRC_Ex13_Handle->crcResult;

    //*********************************************************************************************
    // FOURTEENTH EXAMPLE : 48 bits, Parity is low byte first and CRC computation in reflected mode
    //*********************************************************************************************

    // Initialize CRC objects
    extern CRC_Handle VCRC_Ex14_Handle; // Declared and intialized in syscfg

    // Step 1: Calculate the golden value using the C routine
    VCRC_Ex14_Handle->run = VCRC_Ex14_CROUTINE;
    VCRC_Ex14_Handle->run(VCRC_Ex14_Handle);
    goldenOutput[index] = (uint16_t)VCRC_Ex14_Handle->crcResult;

    // Step 2: run the CRC module with the VCRC assembly code
    VCRC_Ex14_Handle->run = VCRC_Ex14_CRCRUN;
    VCRC_Ex14_Handle->run(VCRC_Ex14_Handle);
    TestOutput[index++] = (uint16_t)VCRC_Ex14_Handle->crcResult;

    //***************************************************************************************************
    // Example 15 and 16 - Byte wise 32 bit CRC computation for P1 polynomial for Msg Sizes - 16, 6 bytes

    //************************************************************************************************
    // FIFTEENTH EXAMPLE: 16 bytes, Parity is low byte first and CRC computation in non reflected mode
    //************************************************************************************************

    // Initialize CRC objects
    extern CRC_Handle VCRC_Ex15_Handle; // Declared and intialized in syscfg

    // Step 1: Calculate the golden value using the C routine
    VCRC_Ex15_Handle->run = VCRC_Ex15_CROUTINE;
    VCRC_Ex15_Handle->run(VCRC_Ex15_Handle);
    goldenOutput[index] = (uint16_t)VCRC_Ex15_Handle->crcResult;

    // Step 2: run the CRC module with the VCRC assembly code
    VCRC_Ex15_Handle->run = VCRC_Ex15_CRCRUN;
    VCRC_Ex15_Handle->run(VCRC_Ex15_Handle);
    TestOutput[index++] = (uint16_t)VCRC_Ex15_Handle->crcResult;

    //*******************************************************************************************
    // SIXTEENTH EXAMPLE: 6 bytes, Parity is low byte first and CRC computation in reflected mode
    //*******************************************************************************************

    // Initialize CRC objects
    extern CRC_Handle VCRC_Ex16_Handle; // Declared and intialized in syscfg

    // Step 1: Calculate the golden value using the C routine
    VCRC_Ex16_Handle->run = VCRC_Ex16_CROUTINE;
    VCRC_Ex16_Handle->run(VCRC_Ex16_Handle);
    goldenOutput[index] = (uint16_t)VCRC_Ex16_Handle->crcResult;

    // Step 2: run the CRC module with the VCRC assembly code
    VCRC_Ex16_Handle->run = VCRC_Ex16_CRCRUN;
    VCRC_Ex16_Handle->run(VCRC_Ex16_Handle);
    TestOutput[index++] = (uint16_t)VCRC_Ex16_Handle->crcResult;

    //***************************************************************************************************
    // Example 17 and 18 - Bit wise 32 bit CRC computation for P1 polynomial for Msg Sizes - 48, 128 bits

    //*************************************************************************************************
    // SEVENTEENTH EXAMPLE: 48 bits, Parity is low byte first and CRC computation in non reflected mode
    //*************************************************************************************************

    // Initialize CRC objects
    extern CRC_Handle VCRC_Ex17_Handle; // Declared and intialized in syscfg

    // Step 1: Calculate the golden value using the C routine
    VCRC_Ex17_Handle->run = VCRC_Ex17_CROUTINE;
    VCRC_Ex17_Handle->run(VCRC_Ex17_Handle);
    goldenOutput[index] = (uint16_t)VCRC_Ex17_Handle->crcResult;

    // Step 2: run the CRC module with the VCRC assembly code
    VCRC_Ex17_Handle->run = VCRC_Ex17_CRCRUN;
    VCRC_Ex17_Handle->run(VCRC_Ex17_Handle);
    TestOutput[index++] = (uint16_t)VCRC_Ex17_Handle->crcResult;

    //*********************************************************************************************
    // EIGHTEENTH EXAMPLE: 128 bits, Parity is low byte first and CRC computation in reflected mode
    //*********************************************************************************************

    // Initialize CRC objects
    extern CRC_Handle VCRC_Ex18_Handle; // Declared and intialized in syscfg

    // Step 1: Calculate the golden value using the C routine
    VCRC_Ex18_Handle->run = VCRC_Ex18_CROUTINE;
    VCRC_Ex18_Handle->run(VCRC_Ex18_Handle);
    goldenOutput[index] = (uint16_t)VCRC_Ex18_Handle->crcResult;

    // Step 2: run the CRC module with the VCRC assembly code
    VCRC_Ex18_Handle->run = VCRC_Ex18_CRCRUN;
    VCRC_Ex18_Handle->run(VCRC_Ex18_Handle);
    TestOutput[index++] = (uint16_t)VCRC_Ex18_Handle->crcResult;

    //*********************************************************************************************
    // Example 19 and 20 - Byte wise 17 bit CRC computation for Msg Size - 16 bytes
    //*********************************************************************************************
    // NINETEENTH EXAMPLE: 128 bits, Parity is low byte first and CRC computation in reflected mode
    //*********************************************************************************************

    // Initialize CRC objects
    extern CRC_Handle VCRC_Ex19_Handle; // Declared and intialized in syscfg

    // Step 1: Calculate the golden value using the C routine
    VCRC_Ex19_Handle->run = VCRC_Ex19_CROUTINE;
    VCRC_Ex19_Handle->run(VCRC_Ex19_Handle);
    goldenOutput[index] = (uint16_t)VCRC_Ex19_Handle->crcResult;

    // Step 2: run the CRC module with the VCRC assembly code
    VCRC_Ex19_Handle->run = VCRC_Ex19_CRCRUN;
    VCRC_Ex19_Handle->run(VCRC_Ex19_Handle);
    TestOutput[index++] = (uint16_t)VCRC_Ex19_Handle->crcResult;

    //******************************************************************************************
    // Bit wise 17 bit CRC computation for Msg Size - 128 bits
    //*******************************************************************************************
    // TWENTYTH EXAMPLE: 128 bits, Parity is low byte first and CRC computation in reflected mode
    //*******************************************************************************************
    // Initialize CRC objects
    extern CRC_Handle VCRC_Ex20_Handle; // Declared and intialized in syscfg

    // Step 1: Calculate the golden value using the C routine
    VCRC_Ex20_Handle->run = VCRC_Ex20_CROUTINE;
    VCRC_Ex20_Handle->run(VCRC_Ex20_Handle);
    goldenOutput[index] = (uint16_t)VCRC_Ex20_Handle->crcResult;

    // Step 2: run the CRC module with the VCRC assembly code
    VCRC_Ex20_Handle->run = VCRC_Ex20_CRCRUN;
    VCRC_Ex20_Handle->run(VCRC_Ex20_Handle);
    TestOutput[index++] = (uint16_t)VCRC_Ex20_Handle->crcResult;

    //*************************************************************************
    // Example 21 and 2 - Bit wise 8 bit CRC computation for Msg Size - 32 bits
    //*************************************************************************

    // TWENTYONETH EXAMPLE: 32 bits, Parity is low byte first and CRC computation in reflected mode
    //*********************************************************************************************
    // Initialize CRC objects
    extern CRC_Handle VCRC_Ex21_Handle; // Declared and intialized in syscfg

    // Step 1: Calculate the golden value using the C routine
    VCRC_Ex21_Handle->run = VCRC_Ex21_CROUTINE;
    VCRC_Ex21_Handle->run(VCRC_Ex21_Handle);
    goldenOutput[index] = (uint16_t)VCRC_Ex21_Handle->crcResult;

    // Step 2: run the CRC module with the VCRC assembly code
    VCRC_Ex21_Handle->run = VCRC_Ex21_CRCRUN;
    VCRC_Ex21_Handle->run(VCRC_Ex21_Handle);
    TestOutput[index++] = (uint16_t)VCRC_Ex21_Handle->crcResult;

    //*****************************************************
    // Byte wise 8 bit CRC computation for Msg Size 56 bits

    //*********************************************************************************************
    // TWENTYTWOTH EXAMPLE: 32 bits, Parity is low byte first and CRC computation in reflected mode
    //*********************************************************************************************
    // Initialize CRC objects
    extern CRC_Handle VCRC_Ex22_Handle; // Declared and intialized in syscfg

    // Step 1: Calculate the golden value using the C routine
    VCRC_Ex22_Handle->run = VCRC_Ex22_CROUTINE;
    VCRC_Ex22_Handle->run(VCRC_Ex22_Handle);
    goldenOutput[index] = (uint16_t)VCRC_Ex22_Handle->crcResult;

    // Step 2: run the CRC module with the VCRC assembly code
    VCRC_Ex22_Handle->run = VCRC_Ex22_CRCRUN;
    VCRC_Ex22_Handle->run(VCRC_Ex22_Handle);
    TestOutput[index++] = (uint16_t)VCRC_Ex22_Handle->crcResult;

    for(index = 0; index < NO_OF_TESTS; index ++){
       if(TestOutput[index] == goldenOutput[index]){
           pass++;
       }else{
           fail++;
       }
    }

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

    run_vcrc_examples();

    while(1)
    {

    }
}

// End of main

// @} //addtogroup

// End of file
