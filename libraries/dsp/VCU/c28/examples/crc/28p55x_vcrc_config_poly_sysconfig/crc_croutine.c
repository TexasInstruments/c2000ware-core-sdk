//###############################################################################
//! \file /crc_croutine.c
//!
//! \brief  Demo code for the configurable polynomial and data sizes (VCRC and C)
//!
//!
//! This example shows how to
//! -# use the VCRC supported configurable polynomial and datasizes
//
//  Group:             C2000
//  Target Family:     F28P55x
//
//#############################################################################
// $Copyright: Copyright (C) 2025 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################

#include "c2000ware_libraries.h"

//C computation of CRC for 4 bit, 16 bit and 32 bit polynomial

void CRC_run4BitENDATTableLookupC(CRC_Handle hndCRC)
{
    int16_t  i,j;
    uint16_t data;
    uint16_t parity        = (uint16_t)hndCRC->parity;
    uint16_t accumulator   = hndCRC->seedValue;
    uint16_t *pInputVector = (uint16_t *)hndCRC->pMsgBuffer;
    uint16_t poly = 0x0003;
    uint16_t polySize = 4;

    // The assumption is the message bytes are packed into 16-bit words
    // and the calculation starts from either the high or low byte
    // The memory arrangement is as follows:
    // Address|_LB__|_HB__|
    // 0x0000 |_D0L_|_D0H_|
    // 0x0001 |_D1L_|_D1H_|
    // 0x0002 |_D2L_|_D2H_|
    // 0x0003 |_D3L_|_D3H_|
    // 0x0004 |_D4L_|_D4H_|
    // ...

    poly <<= (8 - polySize);

    for(i = 0; i < hndCRC->nMsgBytes; i++, parity++){
        // __byte selects either the low(0) or high(1) byte in a word
        // the initial selection provided by the enumeration parity
        // the table index is calculated from the high byte of the accumulator
        // XOR'd with the low and high bytes of each word in the input vector
        data = (uint16_t) __byte((int *)pInputVector, parity);
        accumulator ^= data;
        for (j = 0; j < 8; j++) {
            accumulator <<= 1;
            if (accumulator & 0x0100) {
                accumulator ^= poly;
            }
        }
        accumulator &= 0x00FF;
    }
    // Save the CRC result
    hndCRC->crcResult = (uint32_t)accumulator >> (8 - polySize);
}

void CRC_run4BitENDATBitTableLookupC_Generic(CRC_Handle hndCRC)
{
    int16_t  i;
    uint16_t data;

    uint16_t parity        = (uint16_t)hndCRC->parity;
    uint16_t accumulator   = hndCRC->seedValue;
    uint16_t *pInputVector = (uint16_t *)hndCRC->pMsgBuffer;

    uint16_t poly = 0x0003;
    uint32_t NumOfBits = hndCRC->nMsgBits;
    uint16_t bitPlace = 7;
    uint16_t newWordNext = 1;

    // The assumption is the message bytes are packed into 16-bit words
    // and the calculation starts from either the high or low byte
    // The memory arrangement is as follows:
    // Address|_LB__|_HB__|
    // 0x0000 |_D0L_|_D0H_|
    // 0x0001 |_D1L_|_D1H_|
    // 0x0002 |_D2L_|_D2H_|
    // 0x0003 |_D3L_|_D3H_|
    // 0x0004 |_D4L_|_D4H_|
    // ...

    for(i = 0; i < NumOfBits; i++){
        // __byte selects either the low(0) or high(1) byte in a word
        // the initial selection provided by the enumeration parity
        // the table index is calculated from the high byte of the accumulator
        // XOR'd with the low and high bytes of each word in the input vector
        if (newWordNext) {
            data = (uint16_t) __byte((int *)pInputVector, parity);
            parity++;
            newWordNext = 0;
            if ((NumOfBits - i) <= 8) {
                bitPlace = NumOfBits - i - 1;
            }
        }
        accumulator <<= 1;
        if (((accumulator & 0x0010)>>4) != (((data & (1<<bitPlace)))>>bitPlace)) {
            accumulator ^= poly;
        }
        accumulator &= 0x00F;
        if (!bitPlace) {
            newWordNext = 1;
            bitPlace = 7;
        } else {
            bitPlace--;
        }
    }
    // Save the CRC result
    hndCRC->crcResult = (uint32_t)accumulator;
}


void CRC_run16BitTableLookupC(CRC_Handle hndCRC)
{
    int16_t  i;
//  uint16_t nextWord;
//  uint16_t tableEntry;
    uint16_t tableIndex;
    uint16_t parity        = (uint16_t)hndCRC->parity;
    uint16_t accumulator   = hndCRC->seedValue;
    uint16_t *pInputVector = (uint16_t *)hndCRC->pMsgBuffer;
    uint16_t *pCrcTable    = (uint16_t *)hndCRC->pCrcTable;

    // The assumption is the message bytes are packed into 16-bit words
    // and the calculation starts from either the high or low byte
    // The memory arrangement is as follows:
    // Address|_LB__|_HB__|
    // 0x0000 |_D0L_|_D0H_|
    // 0x0001 |_D1L_|_D1H_|
    // 0x0002 |_D2L_|_D2H_|
    // 0x0003 |_D3L_|_D3H_|
    // 0x0004 |_D4L_|_D4H_|
    // ...

    for(i = 0; i < hndCRC->nMsgBytes; i++, parity++){
        // __byte selects either the low(0) or high(1) byte in a word
        // the initial selection provided by the enumeration parity
        // the table index is calculated from the high byte of the accumulator
        // XOR'd with the low and high bytes of each word in the input vector
        tableIndex  = (accumulator >> 8) ^ __byte((int *)pInputVector, parity);
        accumulator = (accumulator << 8) ^ pCrcTable[tableIndex];
    }

    // Save the CRC result
    hndCRC->crcResult = (uint32_t)accumulator;
}

void CRC_run16BitReflectedTableLookupC(CRC_Handle hndCRC)
{
    int16_t  i;
//  uint16_t nextWord;
//  uint16_t tableEntry;
    uint16_t tableIndex;
    uint16_t parity        = (uint16_t)hndCRC->parity;
    uint16_t accumulator   = hndCRC->seedValue;
    uint16_t *pInputVector = (uint16_t *)hndCRC->pMsgBuffer;
    uint16_t *pCrcTable    = (uint16_t *)hndCRC->pCrcTable;

    // The assumption is the message bytes are packed into 16-bit words
    // and the calculation starts from either the high or low byte
    // The memory arrangement is as follows:
    // Address|_LB__|_HB__|
    // 0x0000 |_D0L_|_D0H_|
    // 0x0001 |_D1L_|_D1H_|
    // 0x0002 |_D2L_|_D2H_|
    // 0x0003 |_D3L_|_D3H_|
    // 0x0004 |_D4L_|_D4H_|
    // ...

    for(i = 0; i < hndCRC->nMsgBytes; i++, parity++){
        // __byte selects either the low(0) or high(1) byte in a word
        // the initial selection provided by the enumeration parity
        // the table index is calculated from the low byte of the accumulator
        // XOR'd with the low and high bytes of each word in the input vector
        tableIndex  = (accumulator & 0x00FF) ^ __byte((int *)pInputVector, parity);
        accumulator = (accumulator >> 8) ^ pCrcTable[tableIndex];
    }

    // Save the CRC result
    hndCRC->crcResult = (uint32_t)accumulator;
}

void CRC_run32BitTableLookupC(CRC_Handle hndCRC)
{
    int16_t  i;
//  uint32_t nextWord;
//  uint32_t tableEntry;
    uint32_t tableIndex;
    uint16_t parity        = hndCRC->parity;
    uint32_t accumulator   = hndCRC->seedValue;
    uint32_t *pInputVector = (uint32_t *)hndCRC->pMsgBuffer;
    uint32_t *pCrcTable    = (uint32_t *)hndCRC->pCrcTable;

    // The assumption is the message bytes are packed into 32-bit words
    // and the calculation starts from either the high or low byte
    // The memory arrangement is as follows:
    // Address|_LB__|_HB__|
    // 0x0000 |_D01_|_D02_|
    // 0x0001 |_D03_|_D04_|
    // 0x0002 |_D11_|_D12_|
    // 0x0003 |_D13_|_D14_|
    // 0x0004 |_D21_|_D22_|
    // ...

    for(i = 0; i < hndCRC->nMsgBytes; i++, parity++){
        // __byte selects either the low(0) or high(1) byte in a word
        // the initial selection provided by the enumeration parity
        // the table index is calculated from the high byte of the accumulator
        // XOR'd with the low and high bytes of each word in the input vector
        tableIndex  = (accumulator >> 24) ^ __byte((int *)pInputVector, parity);
        accumulator = (accumulator << 8) ^ pCrcTable[tableIndex];
    }
    // Save the CRC result
    hndCRC->crcResult = (uint32_t)accumulator;
}

void CRC_run32BitReflectedTableLookupC(CRC_Handle hndCRC)
{
    int16_t  i;
//  uint32_t nextWord;
//  uint32_t tableEntry;
    uint32_t tableIndex;
    uint16_t parity        = hndCRC->parity;
    uint32_t accumulator   = hndCRC->seedValue;
    uint32_t *pInputVector = (uint32_t *)hndCRC->pMsgBuffer;
    uint32_t *pCrcTable    = (uint32_t *)hndCRC->pCrcTable;

    // The assumption is the message bytes are packed into 32-bit words
    // and the calculation starts from either the high or low byte
    // The memory arrangement is as follows:
    // Address|_LB__|_HB__|
    // 0x0000 |_D01_|_D02_|
    // 0x0001 |_D03_|_D04_|
    // 0x0002 |_D11_|_D12_|
    // 0x0003 |_D13_|_D14_|
    // 0x0004 |_D21_|_D22_|
    // ...

    for(i = 0; i < hndCRC->nMsgBytes; i++, parity++){
        // __byte selects either the low(0) or high(1) byte in a word
        // the initial selection provided by the enumeration parity
        // the table index is calculated from the high byte of the accumulator
        // XOR'd with the low and high bytes of each word in the input vector
        tableIndex  = (accumulator & 0x000000FF) ^ __byte((int *)pInputVector, parity);
        accumulator = (accumulator >> 8) ^ pCrcTable[tableIndex];
    }

    // Save the CRC result
    hndCRC->crcResult = (uint32_t)accumulator;
}

void CRC_run17BitCANFDTableLookupC(CRC_Handle hndCRC)
{
    int16_t  i,j;
    uint16_t data;

    uint16_t parity        = (uint16_t)hndCRC->parity;
    uint32_t accumulator   = hndCRC->seedValue;
    uint16_t *pInputVector = (uint16_t *)hndCRC->pMsgBuffer;

    // The assumption is the message bytes are packed into 16-bit words
    // and the calculation starts from either the high or low byte
    // The memory arrangement is as follows:
    // Address|_LB__|_HB__|
    // 0x0000 |_D0L_|_D0H_|
    // 0x0001 |_D1L_|_D1H_|
    // 0x0002 |_D2L_|_D2H_|
    // 0x0003 |_D3L_|_D3H_|
    // 0x0004 |_D4L_|_D4H_|
    // ...

    for(i = 0; i < hndCRC->nMsgBytes; i++, parity++){
        // __byte selects either the low(0) or high(1) byte in a word
        // the initial selection provided by the enumeration parity
        // the table index is calculated from the high byte of the accumulator
        // XOR'd with the low and high bytes of each word in the input vector
        data = (uint16_t) __byte((int *)pInputVector, parity);
        accumulator ^= (uint32_t)data << 9;
        for (j = 0; j < 8; j++) {
            accumulator <<= 1;
            if (accumulator & 0x20000) {
                accumulator ^= 0x1685B;
            }
        }
        accumulator &= 0x1FFFF;
    }

    // Save the CRC result
    hndCRC->crcResult = (uint32_t)accumulator;
}

void CRC_run8BitTableLookupC(CRC_Handle hndCRC)
{
    int16_t  i;
//  uint16_t nextWord;
//  uint16_t tableEntry;
    uint16_t tableIndex;
    uint16_t accumulator   = hndCRC->seedValue;
    uint16_t parity        = (uint16_t)hndCRC->parity;
    uint16_t *pInputVector = (uint16_t *)hndCRC->pMsgBuffer;
    uint16_t *pCrcTable    = (uint16_t *)hndCRC->pCrcTable;

    // The assumption is the message bytes are packed into 16-bit words
    // and the calculation starts from from either the high or low byte
    // The memory arrangement is as follows
    // Address|__LB__|__HB__|
    // 0x0000 |__D0__|__D1__|
    // 0x0001 |__D2__|__D3__|
    // 0x0002 |__D4__|__D5__|
    // 0x0003 |__D6__|__D7__|
    // 0x0004 |__D8__|__D9__|
    // ...

    for(i = 0; i < hndCRC->nMsgBytes; i++, parity++){
        // __byte selects either the low(0) or high(1) byte in a word
        // the initial selection provided by the enumeration parity
        tableIndex = accumulator ^ __byte((int *)pInputVector, parity);
        accumulator = pCrcTable[tableIndex];
    }
    // Save the CRC result
    hndCRC->crcResult = (uint32_t)(accumulator & 0x00FF);
}
// End of file


// End of main

// @} //addtogroup

// End of file
