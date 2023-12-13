//###############################################################################
//! \file /28p65x_vcrc_config_poly/vcrc_configpoly.h
//!
//! \brief  Header file for the configurable polynomial and data sizes (VCRC and C)
//!
//! \date   April 9, 2020
//! 
//
//  Group:             C2000
//  Target Family:     F28p65x
//
//#############################################################################
//
//
// $Copyright: Copyright (C) 2019 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################

//*****************************************************************************
// defines
//*****************************************************************************

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
// function declarations
// specific functions are written to either work on message size that are in 
// bytes or in bits
//*****************************************************************************

//! \brief C table-lookup 4-bit CRC calculation for ENDAT,message size in bytes
//! \param[in] hndCRC handle to the CRC object
void CRC_run4BitENDATTableLookupC(CRC_Handle hndCRC);

//! \brief C table-lookup 4-bit CRC calculation for ENDAT,message size in bits
//! \param[in] hndCRC handle to the CRC object
void CRC_run4BitENDATBitTableLookupC_Generic(CRC_Handle hndCRC);

//! \brief C table-lookup 17-bit CRC for CANFD,message size in bytes
//! \param[in] hndCRC handle to the CRC object
void CRC_run17BitCANFDTableLookupC(CRC_Handle hndCRC);

// error function - this is used in the example to loop forever 
void error(void);
