//#############################################################################
//
// FILE:   aes_ex4_gcm_decrypt.c
//
// TITLE:  AES GCM Decryption
//
//! \addtogroup driver_example_cm_list
//! <h1>AES GCM Decryption Example (CM)</h1>
//!
//! This example decrypts block cipher-text using AES128 in GCM mode. It does
//! the decryption first without uDMA and then with uDMA. The results are
//! checked after each operation.
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//! - \b errorCountGlobal - Error Counter. It should be zero.
//! - \b testStatusGlobal - Test status. It should be equal to PASS.
//!
//
//#############################################################################
//
//
// 
// C2000Ware v5.03.00.00
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

//
// Included Files
//
#include <string.h>
#include "driverlib_cm.h"
#include "cm.h"

//
// Defines
//
#define TEST_PASS 0xABCDABCD
#define TEST_FAIL 0xDEADDEAD

//
// Global variables
//

//
// The DMA control structure table
//
#pragma DATA_ALIGN(ucControlTable, 1024)
UDMA_ControlTable ucControlTable[64];

//
// Variables to provide & gather results from AES module for
// each test case
//
uint32_t plainTextArray[64], tagArray[4], y0Array[4], cnt;
uint32_t *keyArray, ivLength, *ivArray, dataLength;
uint32_t *expPlainTextArray, authDataLength, *authDataArray;
uint32_t *cipherTextArray, *expTagArray;
uint8_t vectorCnt;
AES_KeySize keySize;

//
// Variables to capture error count & test status
//
uint32_t errorCountGlobal, testStatusGlobal;

//
// Interrupt status
//
volatile uint32_t intStatus;

//
// Function Prototypes
//
void performECBEncryption(AES_KeySize keySize, uint32_t *srcArray,
                          uint32_t *dstArray,   uint32_t *keyArray,
                          uint32_t dataLength);

void performGCMDecryption(AES_KeySize keySize, uint32_t *srcArray,
                          uint32_t *dstArray, uint32_t dataLength,
                          uint32_t *keyArray, uint32_t *ivArray,
                          uint32_t *aadArray, uint32_t aadLength,
                          uint32_t *tagArray, bool useDMA);

void performGHASHOperation(AES_KeySize keySize, uint32_t *hashSubkeyArray,
                           uint32_t *ivArray, uint32_t ivLength,
                           uint32_t *resultTagArray);

void getHashSubKey(AES_KeySize keySize, uint32_t *keyArray,
                   uint32_t *hashSubkeyArray);

void getGCMY0(AES_KeySize keySize,   uint32_t *ivArray, uint32_t ivLength,
              uint32_t *keyArray, uint32_t *y0Array);

uint32_t roundUpDataLength(uint32_t dataLength);

//
// ISR for AESINT.
//
__interrupt void localAESIntISR(void);

//
// The AES interrupt handler and interrupt flags
//
static volatile bool contextInIntFlag;
static volatile bool dataInIntFlag;
static volatile bool contextOutIntFlag;
static volatile bool dataOutIntFlag;
static volatile bool contextInDMADoneIntFlag;
static volatile bool dataInDMADoneIntFlag;
static volatile bool contextOutDMADoneIntFlag;
static volatile bool dataOutDMADoneIntFlag;

//
// Structure for NIST AES GCM tests
//
typedef struct
{
    AES_KeySize keySize;
    uint32_t keyArray[8];
    uint32_t ivLength;
    uint32_t ivArray[64];
    uint32_t dataLength;
    uint32_t plainTextArray[64];
    uint32_t authDataLength;
    uint32_t authDataArray[64];
    uint32_t cipherTextArray[64];
    uint32_t tagArray[4];
} testVectorGCM;

//
// Test Cases from NIST GCM Revised Spec
//
testVectorGCM testVectorGCMArray[] =
{
 //
 // Test Case #1
 // This is a special case that cannot use the GCM mode because the
 // data and AAD lengths are both zero.  The work around is to perform
 // an ECB decryption on Y0.
 //
 {
  AES_KEY_SIZE_128BIT,                                      // keySize
  { 0x00000000, 0x00000000, 0x00000000, 0x00000000 },       // keyArray
  12,                                                       // ivLength
  { 0x00000000, 0x00000000, 0x00000000, 0x00000000 },       // ivArray
  0,                                                        // dataLength
  { 0 },                                                    // plainTextArray
  0,                                                        // authDataLength
  { 0 },                                                    // authDataArray
  { 0 },                                                    // cipherTextArray
  { 0xcefce258, 0x61307efa, 0x571d7f36, 0x5a45e7a4 }        // tagArray
 },

 //
 // Test Case #2
 // This is the first test in which the AAD length is zero.
 //
 {
  AES_KEY_SIZE_128BIT,                                      // keySize
  { 0x00000000, 0x00000000, 0x00000000, 0x00000000 },       // keyArray
  12,                                                       // ivLength
  { 0x00000000, 0x00000000, 0x00000000, 0x00000000 },       // ivArray
  16,                                                       // dataLength
  { 0x00000000, 0x00000000, 0x00000000, 0x00000000 },       // plainTextArray
  0,                                                        // authDataLength
  { 0 },                                                    // authDataArray
  { 0xceda8803, 0x92a3b660, 0xb9c228f3, 0x78feb271 },       // cipherTextArray
  { 0xd4476eab, 0xbd13ec2c, 0xb2673af5, 0xdfbd5712 }        // tagArray
 },

 //
 // Test Case #3
 //
 {
  AES_KEY_SIZE_128BIT,                                      // keySize
  { 0x92e9fffe, 0x1c736586, 0x948f6a6d, 0x08833067 },       // keyArray
  12,                                                       // ivLength
  { 0xbebafeca, 0xaddbcefa, 0x88f8cade, 0x00000000 },       // ivArray
  64,                                                       // dataLength
  { 0x253231d9, 0xe50684f8, 0xc50959a5, 0x9a26f5af,         // plainTextArray
    0x53a9a786, 0xdaf73415, 0x3d304c2e, 0x728a318a,
    0x950c3c1c, 0x53096895, 0x240ecf2f, 0x25b5a649,
    0xf5ed6ab1, 0x57e60daa, 0x397b63ba, 0x55d2af1a },
  0,                                                        // authDataLength
  { 0 },                                                    // authDataArray
  { 0xc21e8342, 0x24747721, 0xb721724b, 0x9cd4d084,         // cipherTextArray
    0x2f21aae3, 0xe0a4022c, 0x237ec135, 0x2ea1ac29,
    0xb214d521, 0x1c936654, 0x5a6a8f7d, 0x05aa84ac,
    0x390ba31b, 0x97ac0a6a, 0x91e0583d, 0x85593f47 },
  { 0xf32a5c4d, 0xa664cd27, 0xbd5af32c, 0xb4faa62b }        // tagArray
 },

 //
 // Test Case #4
 // When the data lengths do not align with the block
 // boundary, we need to pad with zeros to ensure unknown
 // data is not copied with uDMA.
 //
 {
  AES_KEY_SIZE_128BIT,                                      // keySize
  { 0x92e9fffe, 0x1c736586, 0x948f6a6d, 0x08833067 },       // keyArray
  12,                                                       // ivLength
  { 0xbebafeca, 0xaddbcefa, 0x88f8cade, 0x00000000 },       // ivArray
  60,                                                       // dataLength
  { 0x253231d9, 0xe50684f8, 0xc50959a5, 0x9a26f5af,         // plainTextArray
    0x53a9a786, 0xdaf73415, 0x3d304c2e, 0x728a318a,
    0x950c3c1c, 0x53096895, 0x240ecf2f, 0x25b5a649,
    0xf5ed6ab1, 0x57e60daa, 0x397b63ba, 0x00000000 },
  20,                                                       // authDataLength
  { 0xcefaedfe, 0xefbeadde, 0xcefaedfe, 0xefbeadde,         // authDataArray
    0xd2daadab, 0x00000000, 0x00000000, 0x00000000 },
  { 0xc21e8342, 0x24747721, 0xb721724b, 0x9cd4d084,         // cipherTextArray
    0x2f21aae3, 0xe0a4022c, 0x237ec135, 0x2ea1ac29,
    0xb214d521, 0x1c936654, 0x5a6a8f7d, 0x05aa84ac,
    0x390ba31b, 0x97ac0a6a, 0x91e0583d, 0x00000000 },
  { 0xbc4fc95b, 0xdba52132, 0x5ae9fa94, 0x471a12e7 }        // tagArray
},

 //
 // Test Case #5
 // This is the first case in which IV is less than
 // 96 bits.
 //
 {
  AES_KEY_SIZE_128BIT,                                      // keySize
    { 0x92e9fffe, 0x1c736586, 0x948f6a6d, 0x08833067 },     // keyArray
    8,                                                      // ivLength
    { 0xbebafeca, 0xaddbcefa, 0x00000000, 0x00000000 },     // ivArray
    60,                                                     // dataLength
    { 0x253231d9, 0xe50684f8, 0xc50959a5, 0x9a26f5af,       // plainTextArray
      0x53a9a786, 0xdaf73415, 0x3d304c2e, 0x728a318a,
      0x950c3c1c, 0x53096895, 0x240ecf2f, 0x25b5a649,
      0xf5ed6ab1, 0x57e60daa, 0x397b63ba, 0x00000000 },
    20,                                                     // authDataLength
    { 0xcefaedfe, 0xefbeadde, 0xcefaedfe, 0xefbeadde,       // authDataArray
      0xd2daadab, 0x00000000, 0x00000000, 0x00000000 },
    { 0x4c3b3561, 0x4a930628, 0x1ff57f77, 0x55472aa2,       // cipherTextArray
      0x712a9b69, 0xf8c6cd4f, 0xf9e56637, 0x23746c7b,
      0x00698073, 0xb2249fe4, 0x4475092b, 0x426b89d4,
      0xe1b58949, 0x070faceb, 0x98453fc2, 0x00000000 },
    { 0xe7d21236, 0x85073b9e, 0x4ae11b56, 0xcbfca2ac }      // tagArray
},

//
// Test Case #6
// This is the first case in which IV is more than
// 96 bits.
//
{
 AES_KEY_SIZE_128BIT,                                       // keySize
    { 0x92e9fffe, 0x1c736586, 0x948f6a6d, 0x08833067 },     // keyArray
    60,                                                     // ivLength
    { 0x5d221393, 0xe50684f8, 0x5a9c9055, 0xaa6952ff,       // ivArray
      0x38957a6a, 0xa17d4f53, 0xd203c3e4, 0x28a718a3,
      0x51c9c0c3, 0x39958056, 0x42e2f0fc, 0x54526b9a,
      0xf5dbae16, 0x576adea0, 0x9bb337a6, 0x00000000 },
    60,                                                     // dataLength
    { 0x253231d9, 0xe50684f8, 0xc50959a5, 0x9a26f5af,       // plainTextArray
      0x53a9a786, 0xdaf73415, 0x3d304c2e, 0x728a318a,
      0x950c3c1c, 0x53096895, 0x240ecf2f, 0x25b5a649,
      0xf5ed6ab1, 0x57e60daa, 0x397b63ba, 0x00000000 },
    20,                                                     // authDataLength
    { 0xcefaedfe, 0xefbeadde, 0xcefaedfe, 0xefbeadde,       // authDataArray
      0xd2daadab },
    { 0x9849e28c, 0xb6155662, 0xac33a003, 0x94b83fa1,       // cipherTextArray
      0xa51291be, 0xa811a2c3, 0x3c2a26ba, 0xa72c7eca,
      0xa4a9e401, 0x903ca4fb, 0x81b2dccc, 0x6f7c8cd4,
      0xd27528d6, 0x0317a4ac, 0xe5ae344c, 0x00000000 },
    { 0xaec59c61, 0xfa0bfeff, 0x3cf42a46, 0x50d09916 }      // tagArray
},

//
// The following test cases use 256bit Keys.
//
// Test Case #7 - Test Case 13 from the doc
// This is a special case that cannot use the GCM mode because the
// data and AAD lengths are both zero.  The work around is to perform
// an ECB decryption on Y0.
//
{
 AES_KEY_SIZE_256BIT,                                       // keySize
    { 0x00000000, 0x00000000, 0x00000000, 0x00000000,       // keyArray
      0x00000000, 0x00000000, 0x00000000, 0x00000000 },
    12,                                                     // ivLength
    { 0x00000000, 0x00000000, 0x00000000, 0x00000000 },     // ivArray
    0,                                                      // dataLength
    { 0 },                                                  // plainTextArray
    0,                                                      // authDataLength
    { 0 },                                                  // authDataArray
    { 0 },                                                  // cipherTextArray
    { 0xfb8a0f53, 0xb93645c7, 0xf1b463a9, 0x8b73cbc4 }      // tagArray
},

//
// Test Case #8, - Test Case 14 from the doc
// This is the first test in which the AAD length is zero.
//
{
 AES_KEY_SIZE_256BIT,                                       // keySize
    { 0x00000000, 0x00000000, 0x00000000, 0x00000000,       // keyArray
      0x00000000, 0x00000000, 0x00000000, 0x00000000 },
    12,                                                     // ivLength
    { 0x00000000, 0x00000000, 0x00000000, 0x00000000 },     // ivArray
    16,                                                     // dataLength
    { 0x00000000, 0x00000000, 0x00000000, 0x00000000 },     // plainTextArray
    0,                                                      // authDataLength
    { 0 },                                                  // authDataArray
    { 0x3d40a7ce, 0x6e6b604d, 0xd3c54e07, 0x189df3ba },     // cipherTextArray
    { 0xa7c8d1d0, 0xf06b9999, 0xb5985b26, 0x19b98ad4 }      // tagArray
},

//
// Test Case #9, - Test Case 15 from the doc
//
{
 AES_KEY_SIZE_256BIT,                                       // keySize
    { 0x92e9fffe, 0x1c736586, 0x948f6a6d, 0x08833067,       // keyArray
      0x92e9fffe, 0x1c736586, 0x948f6a6d, 0x08833067 },
    12,                                                     // ivLength
    { 0xbebafeca, 0xaddbcefa, 0x88f8cade, 0x00000000 },     // ivArray
    64,                                                     // dataLength
    { 0x253231d9, 0xe50684f8, 0xc50959a5, 0x9a26f5af,       // plainTextArray
      0x53a9a786, 0xdaf73415, 0x3d304c2e, 0x728a318a,
      0x950c3c1c, 0x53096895, 0x240ecf2f, 0x25b5a649,
      0xf5ed6ab1, 0x57e60daa, 0x397b63ba, 0x55d2af1a },
    0,                                                      // authDataLength
    { 0 },                                                  // authDataArray
    { 0xf0c12d52, 0x077d5699, 0xa3377ff4, 0x7d42842a,       // cipherTextArray
      0xdc8c3a64, 0xc9c0e5bf, 0xbda29875, 0xaad15525,
      0x488eb08c, 0x3dbb0d59, 0x108bb0a7, 0x38888256,
      0x631ef6c5, 0x0a7aba93, 0x62f6c9bc, 0xad158089 },
    { 0xc5da94b0, 0xbd7134d9, 0x22501aec, 0x6ccce370 }      // tagArray
},

 //
 // Test Case #10 - Test Case 16 from the doc
 // When the data lengths do not align with the block
 // boundary, we need to pad with zeros to ensure unknown
 // data is not copied with uDMA.
 //
 {
  AES_KEY_SIZE_256BIT,                                      // keySize
  { 0x92e9fffe, 0x1c736586, 0x948f6a6d, 0x08833067,         // keyArray
    0x92e9fffe, 0x1c736586, 0x948f6a6d, 0x08833067 },
  12,                                                       // ivLength
  { 0xbebafeca, 0xaddbcefa, 0x88f8cade, 0x00000000 },       // ivArray
  60,                                                       // dataLength
  { 0x253231d9, 0xe50684f8, 0xc50959a5, 0x9a26f5af,         // plainTextArray
    0x53a9a786, 0xdaf73415, 0x3d304c2e, 0x728a318a,
    0x950c3c1c, 0x53096895, 0x240ecf2f, 0x25b5a649,
    0xf5ed6ab1, 0x57e60daa, 0x397b63ba, 0x00000000 },
  20,                                                       // authDataLength
  { 0xcefaedfe, 0xefbeadde, 0xcefaedfe, 0xefbeadde,         // authDataArray
    0xd2daadab, 0x00000000, 0x00000000, 0x00000000 },
  { 0xf0c12d52, 0x077d5699, 0xa3377ff4, 0x7d42842a,         // cipherTextArray
    0xdc8c3a64, 0xc9c0e5bf, 0xbda29875, 0xaad15525,
    0x488eb08c, 0x3dbb0d59, 0x108bb0a7, 0x38888256,
    0x631ef6c5, 0x0a7aba93, 0x62f6c9bc, 0x00000000 },
  { 0xce6efc76, 0x68174e0f, 0x5388dfcd, 0x1b552dbb }        // tagArray
 }
};

//
// Main
//
void main(void)
{
    //
    // Initialize device clock and peripherals
    //
    CM_init();

    //
    // Initialize variables
    //
    errorCountGlobal = 0U;
    for(cnt = 0; cnt < 64; cnt++)
    {
        plainTextArray[cnt] = 0U;
    }
    for(cnt = 0; cnt < 4; cnt++)
    {
        tagArray[cnt] = 0U;
    }

    //
    // Enable AES interrupts
    //
    Interrupt_enable(INT_AES);
    AES_registerInterrupt(INT_AES, localAESIntISR);

    //
    // Setup the control table
    //
    UDMA_enable(UDMA_BASE);
    UDMA_setControlBase(UDMA_BASE, ucControlTable);

    //
    // Perform AES Soft Reset
    //
    AES_performSoftReset(AES_BASE);

    //
    // Loop through all the given vectors
    //
    for(vectorCnt = 0;
        (vectorCnt < (sizeof(testVectorGCMArray) /
         sizeof(testVectorGCMArray[0]))) && (errorCountGlobal == 0U); vectorCnt++)
    {
        //
        // Get the current vector's data members
        //
        keySize  = testVectorGCMArray[vectorCnt].keySize;
        keyArray = testVectorGCMArray[vectorCnt].keyArray;
        ivLength = testVectorGCMArray[vectorCnt].ivLength;
        ivArray  = testVectorGCMArray[vectorCnt].ivArray;
        dataLength         = testVectorGCMArray[vectorCnt].dataLength;
        expPlainTextArray  = testVectorGCMArray[vectorCnt].plainTextArray;
        authDataLength     = testVectorGCMArray[vectorCnt].authDataLength;
        authDataArray      = testVectorGCMArray[vectorCnt].authDataArray;
        cipherTextArray = testVectorGCMArray[vectorCnt].cipherTextArray;
        expTagArray        = testVectorGCMArray[vectorCnt].tagArray;

        //
        // Clear the arrays containing the plain-text and tag to ensure things
        // are working correctly
        //
        for(cnt = 0; cnt < (dataLength / 4U); cnt++)
        {
            plainTextArray[cnt] = 0U;
        }
        for(cnt = 0; cnt < 4; cnt++)
        {
            tagArray[cnt] = 0U;
        }

        //
        // If both the data lengths are zero, then it's a special case
        //
        if((dataLength == 0U) && (authDataLength == 0U))
        {
            //
            // Performing decryption without uDMA
            //

            //
            // Figure out the value of Y0 depending on the IV length
            //
            getGCMY0(keySize, ivArray, ivLength, keyArray, y0Array);

            //
            // Perform the basic encryption
            //
            performECBEncryption(keySize, y0Array, tagArray, keyArray, 16U);
        }
        else
        {
            //
            // Figure out the value of Y0 depending on the IV length
            //
            getGCMY0(keySize, ivArray, ivLength, keyArray, y0Array);

            //
            // Perform the decryption without uDMA
            //
            performGCMDecryption(keySize, cipherTextArray, plainTextArray,
                          dataLength, keyArray, y0Array, authDataArray,
                          authDataLength, tagArray, false);
        }

        //
        // Check the results
        //
        for(cnt = 0; cnt < (dataLength / 4U); cnt++)
        {
            if(expPlainTextArray[cnt] != plainTextArray[cnt])
            {
                //
                // Plain-text mismatch on word
                //
                errorCountGlobal |= ((cnt << 16U) | 0x00000004U);
            }
        }
        for(cnt = 0; cnt < 4; cnt++)
        {
            if(expTagArray[cnt] != tagArray[cnt])
            {
                //
                // Tag mismatch on word
                //
                errorCountGlobal |= ((cnt << 16U) | 0x00000003U);
            }
        }

        //
        // Clear the arrays containing the plain-text and tag to ensure things
        // are working correctly
        //
        for(cnt = 0; cnt < (dataLength / 4U); cnt++)
        {
            plainTextArray[cnt] = 0U;
        }
        for(cnt = 0; cnt < 4; cnt++)
        {
            tagArray[cnt] = 0U;
        }

        //
        // Only use DMA with the vectors that have data
        //
        if((dataLength != 0U) || (authDataLength != 0U))
        {
            //
            // Perform the decryption with uDMA
            //
            performGCMDecryption(keySize, cipherTextArray, plainTextArray,
                          dataLength, keyArray, y0Array, authDataArray,
                          authDataLength, tagArray, true);

            //
            // Check the result
            //
            for(cnt = 0; cnt < (dataLength / 4U); cnt++)
            {
                if(expPlainTextArray[cnt] != plainTextArray[cnt])
                {
                    //
                    // Plain-text mismatch on word
                    //
                    errorCountGlobal |= ((cnt << 16U) | 0x00000004U);
                }
            }
            for(cnt = 0; cnt < 4; cnt++)
            {
                if(expTagArray[cnt] != tagArray[cnt])
                {
                    //
                    // Tag mismatch on word
                    //
                    errorCountGlobal |= ((cnt << 16U) | 0x00000003U);
                }
            }
        }
    }

    //
    // Clean up AES Data registers
    //
    AES_performSoftReset(AES_BASE);

    //
    // Update test status variable
    //
    if(errorCountGlobal == 0U)
    {
        testStatusGlobal = TEST_PASS;
    }
    else
    {
        testStatusGlobal = TEST_FAIL;
    }

    //
    // Wait forever
    //
    while(1)
    {
    }
}

//
// performECBEncryption - Perform an AES-ECB decryption operation.
//
void performECBEncryption(AES_KeySize keySize, uint32_t *srcArray,
                          uint32_t *dstArray,   uint32_t *keyArray,
                          uint32_t dataLength)
{
    //
    // Perform a soft reset
    //
    AES_performSoftReset(AES_BASE);

    //
    // Configure the AES module
    //
    AES_ConfigParams aesConfig;
    memset(&aesConfig, 0U, sizeof(AES_ConfigParams));
    aesConfig.direction = AES_DIRECTION_ENCRYPT;
    aesConfig.keySize = keySize;
    aesConfig.opMode = AES_OPMODE_ECB;
    AES_configureModule(AES_BASE, &aesConfig);

    //
    // Write the key
    //
    AES_setKey1(AES_BASE, keyArray, keySize);

    //
    // Perform the encryption
    //
    AES_processData(AES_BASE, srcArray, dstArray, dataLength);
}

//
// getGCMY0 - Calculate the Y0 value that needs to be written into the IV
// registers. Note: Y0 will always be 128 bits.
//
void getGCMY0(AES_KeySize keySize, uint32_t *ivArray, uint32_t ivLength,
              uint32_t *keyArray, uint32_t *y0Array)
{
    uint32_t hashSubkeyArray[8U];

    //
    // If the length is 96 bits, then just set the last bit of the IV to 1
    //
    if(ivLength == 12U)
    {
        y0Array[0] = ivArray[0];
        y0Array[1] = ivArray[1];
        y0Array[2] = ivArray[2];
        y0Array[3] = 0x01000000U;
    }

    //
    // If the length is not 96 bits, then perform a basic GHASH on the IV
    //
    else
    {
        //
        // First, get the hash subkey or H
        //
        getHashSubKey(keySize, keyArray, hashSubkeyArray);

        //
        // Next, perform the GHASH operation
        //
        performGHASHOperation(keySize, hashSubkeyArray, ivArray, ivLength,
                              y0Array);
    }
}

//
// getHashSubKey - Calculate hash subkey(H) with the given key.
// This is performed by encrypting 128 zeroes with the key.
//
void getHashSubKey(AES_KeySize keySize, uint32_t *keyArray,
                   uint32_t *hashSubkeyArray)
{
    uint32_t zeroArray[8];

    //
    // Put zeroes into the first 4 words of the array
    //
    zeroArray[0] = 0x0U;
    zeroArray[1] = 0x0U;
    zeroArray[2] = 0x0U;
    zeroArray[3] = 0x0U;

    //
    // Put zeroes into the next 4 words if the key size is 256bit
    //
    if(keySize == AES_KEY_SIZE_256BIT)
    {
        zeroArray[4] = 0x0U;
        zeroArray[5] = 0x0U;
        zeroArray[6] = 0x0U;
        zeroArray[7] = 0x0U;
    }

    //
    // Perform the decryption
    //
    performECBEncryption(keySize, zeroArray, hashSubkeyArray, keyArray,
                  (keySize == AES_KEY_SIZE_128BIT ? 16U : 32U));
}

//
// performGHASHOperation - Perform a basic GHASH operation with the hashsubkey
// and IV. This is used to get Y0 when the IV is not 96 bits.  To use this GCM
// mode, the operation direction must not be set and the counter should be
// disabled.
//
void performGHASHOperation(AES_KeySize keySize, uint32_t *hashSubkeyArray,
                           uint32_t *ivArray, uint32_t ivLength,
                           uint32_t *resultTagArray)
{
    uint32_t ghashCnt;

    //
    // Perform a soft reset
    //
    AES_performSoftReset(AES_BASE);

    //
    // Configure the AES module
    //
    AES_ConfigParams aesConfig;
    memset(&aesConfig, 0U, sizeof(AES_ConfigParams));
    aesConfig.keySize = (AES_KeySize)keySize;
    aesConfig.opMode = AES_OPMODE_GCM_HLY0ZERO;
    AES_configureModule(AES_BASE, &aesConfig);

    //
    // Set the hash subkey
    //
    AES_setKey2(AES_BASE, hashSubkeyArray, keySize);

    //
    // Write the lengths
    //
    AES_setDataLength(AES_BASE, ivLength);
    AES_setAuthDataLength(AES_BASE, 0U);

    //
    // Write the data
    //
    for(ghashCnt = 0; ghashCnt < ivLength; ghashCnt += 16)
    {
        //
        // Write the data registers
        //
        AES_writeDataBlocking(AES_BASE, (ivArray + (ghashCnt / 4U)));
    }

    //
    // Read the hash tag value
    //
    AES_readTag(AES_BASE, resultTagArray);
}

//
// performGCMDecryption - Perform GCM decryption operation.
//
void performGCMDecryption(AES_KeySize keySize, uint32_t *srcArray,
                          uint32_t *dstArray, uint32_t dataLength,
                          uint32_t *keyArray, uint32_t *ivArray,
                          uint32_t *aadArray, uint32_t aadLength,
                          uint32_t *tagArray, bool useDMA)
{
    //
    // Perform a soft reset
    //
    AES_performSoftReset(AES_BASE);

    //
    // Clear the interrupt flags
    //
    contextInIntFlag = false;
    dataInIntFlag = false;
    contextOutIntFlag = false;
    dataOutIntFlag = false;
    contextInDMADoneIntFlag = false;
    dataInDMADoneIntFlag = false;
    contextOutDMADoneIntFlag = false;
    dataOutDMADoneIntFlag = false;

    //
    // Configure the AES module
    //
    AES_ConfigParams aesConfig;
    memset(&aesConfig, 0, sizeof(AES_ConfigParams));
    aesConfig.direction = AES_DIRECTION_DECRYPT;
    aesConfig.keySize = keySize;
    aesConfig.opMode = AES_OPMODE_GCM_HY0CALC;
    AES_configureModule(AES_BASE, &aesConfig);

    //
    // Write the initialization value
    //
    AES_setInitializationVector(AES_BASE, ivArray);

    //
    // Write the keys
    //
    AES_setKey1(AES_BASE, keyArray, keySize);

    //
    // Depending on the argument, perform the decryption
    // with or without uDMA
    //
    if(useDMA)
    {
        //
        // Disable Non-DMA interrupts
        //
        AES_disableInterrupt(AES_BASE, AESW_BASE, (AES_INT_CONTEXT_IN |
                             AES_INT_CONTEXT_OUT | AES_INT_DATA_IN    |
                             AES_INT_DATA_OUT));

        //
        // Enable DMA interrupts
        //
        AES_enableInterrupt(AES_BASE, AESW_BASE, (AES_INT_DMA_CONTEXT_IN  |
                                                  AES_INT_DMA_DATA_IN     |
                                                  AES_INT_DMA_CONTEXT_OUT |
                                                  AES_INT_DMA_DATA_OUT));

        if(aadLength != 0U)
        {
            //
            // Setup the DMA module to copy auth data in
            //
            UDMA_changeChannelMapping(UDMA_BASE, UDMA_CHANNEL_AES_DIN,
                                      UDMA_CH_MAPPING_0);

            UDMA_disableChannelAttribute(UDMA_BASE, UDMA_CHANNEL_AES_DIN,
                                        UDMA_CH_ATTR_ALL);

            UDMA_setChannelControlParams(UDMA_BASE, (UDMA_CHANNEL_AES_DIN    |
                                        UDMA_PRI_SELECT), (UDMA_SIZE_32      |
                                                           UDMA_SRC_INC_32   |
                                                           UDMA_DST_INC_NONE |
                                                           UDMA_ARB_4        |
                                                           UDMA_DST_PROT_PRIV));

            UDMA_setChannelTransferParams(UDMA_BASE, (UDMA_CHANNEL_AES_DIN   |
                         UDMA_PRI_SELECT), (void*)aadArray,
                         (void*)(AES_BASE + AES_O_DATA_IN_OUT_0),
                         UDMA_MODE_BASIC, (roundUpDataLength(aadLength) / 4U));
        }

        //
        // Setup the DMA module to copy the data out
        //
        UDMA_changeChannelMapping(UDMA_BASE, UDMA_CHANNEL_AES_DOUT,
                                  UDMA_CH_MAPPING_0);

        UDMA_disableChannelAttribute(UDMA_BASE, UDMA_CHANNEL_AES_DOUT,
                                    UDMA_CH_ATTR_ALL);

        UDMA_setChannelControlParams(UDMA_BASE, (UDMA_CHANNEL_AES_DOUT    |
                                     UDMA_PRI_SELECT), (UDMA_SIZE_32      |
                                                        UDMA_SRC_INC_NONE |
                                                        UDMA_DST_INC_32   |
                                                        UDMA_ARB_4        |
                                                        UDMA_SRC_PROT_PRIV));

        UDMA_setChannelTransferParams(UDMA_BASE, (UDMA_CHANNEL_AES_DOUT |
                                 UDMA_PRI_SELECT),
                                 (void*)(AES_BASE + AES_O_DATA_IN_OUT_0),
                                 (void*)dstArray, UDMA_MODE_BASIC,
                                 roundUpDataLength(dataLength) / 4U);

        //
        // Write the cipher-text length
        //
        AES_setDataLength(AES_BASE, (uint64_t)(dataLength));

        //
        // Write the auth length registers to start the process
        //
        AES_setAuthDataLength(AES_BASE, aadLength);

        //
        // Enable the DMA channels to start the transfers. This must be done
        // after writing the length to prevent data from copying before the
        // context is truly ready
        //
        if(aadLength != 0U)
        {
            UDMA_enableChannel(UDMA_BASE, UDMA_CHANNEL_AES_DIN);
        }

        UDMA_enableChannel(UDMA_BASE, UDMA_CHANNEL_AES_DOUT);

        //
        // Enable DMA requests
        //
        AES_enableDMARequest(AES_BASE,(AES_DMA_EN_DATA_IN |
                                       AES_DMA_EN_DATA_OUT));

        if(aadLength != 0U)
        {
            //
            // Wait for the data in DMA done interrupt
            //
            while(!dataInDMADoneIntFlag)
            {
            }
        }

        if(dataLength != 0U)
        {
            //
            // Setup the uDMA to copy the cipher-text data
            //
            UDMA_changeChannelMapping(UDMA_BASE, UDMA_CHANNEL_AES_DIN,
                                      UDMA_CH_MAPPING_0);

            UDMA_disableChannelAttribute(UDMA_BASE, UDMA_CHANNEL_AES_DIN,
                                        UDMA_CH_ATTR_ALL);

            UDMA_setChannelControlParams(UDMA_BASE, (UDMA_CHANNEL_AES_DIN    |
                                        UDMA_PRI_SELECT), (UDMA_SIZE_32      |
                                                           UDMA_SRC_INC_32   |
                                                           UDMA_DST_INC_NONE |
                                                           UDMA_ARB_4        |
                                                           UDMA_DST_PROT_PRIV));

            UDMA_setChannelTransferParams(UDMA_BASE, (UDMA_CHANNEL_AES_DIN  |
                           UDMA_PRI_SELECT), (void*)srcArray,
                           (void*)(AES_BASE + AES_O_DATA_IN_OUT_0),
                           UDMA_MODE_BASIC, roundUpDataLength(dataLength) / 4U);

            UDMA_enableChannel(UDMA_BASE, UDMA_CHANNEL_AES_DIN);

            //
            // Enable DMA requests
            //
            AES_enableDMARequest(AES_BASE,(AES_DMA_EN_DATA_IN |
                                           AES_DMA_EN_DATA_OUT));

            //
            // Wait for the data out DMA done interrupt
            //
            while(!dataOutDMADoneIntFlag)
            {
            }
        }

        //
        // Read out the tag.
        //
        AES_readTag(AES_BASE, tagArray);
    }
    else
    {
        //
        // Enable all interrupts
        //
        AES_enableInterrupt(AES_BASE, AESW_BASE, (AES_INT_CONTEXT_IN |
                            AES_INT_CONTEXT_OUT | AES_INT_DATA_IN    |
                            AES_INT_DATA_OUT));

        //
        // Perform the decryption
        //
        AES_processDatainAuthMode(AES_BASE, srcArray, dstArray, dataLength,
                                  aadArray, aadLength, tagArray);
    }
}

//
// roundUpDataLength - Round up length to nearest 16 byte boundary.  This is
// needed because all four data registers must be written at once.  This is
// handled in the AES driver, but if using uDMA, the length must rounded up.
//
uint32_t roundUpDataLength(uint32_t dataLength)
{
    uint32_t remainder;

    remainder = dataLength % 16U;
    if(remainder == 0U)
    {
        return(dataLength);
    }
    else
    {
        return(dataLength + (16U - remainder));
    }
}

//
// localAESIntISR - local AES Int ISR
//
void localAESIntISR(void)
{
    //
    // Read the AES masked interrupt status
    //
    intStatus = AES_getInterruptStatus(AES_BASE, AESW_BASE, false);

    //
    // Print a different message depending on the interrupt source
    //
    if(intStatus & AES_INT_CONTEXT_IN)
    {
        //
        // Context input registers are ready
        //
        AES_disableInterrupt(AES_BASE, AESW_BASE, AES_INT_CONTEXT_IN);
        contextInIntFlag = true;
    }
    if(intStatus & AES_INT_DATA_IN)
    {
        //
        // Data FIFO is ready to receive data
        //
        AES_disableInterrupt(AES_BASE, AESW_BASE, AES_INT_DATA_IN);
        dataInIntFlag = true;
    }
    if(intStatus & AES_INT_CONTEXT_OUT)
    {
        //
        // Context output registers are ready
        //
        AES_disableInterrupt(AES_BASE, AESW_BASE, AES_INT_CONTEXT_OUT);
        contextOutIntFlag = true;
    }
    if(intStatus & AES_INT_DATA_OUT)
    {
        //
        // Data FIFO is ready to provide data
        //
        AES_disableInterrupt(AES_BASE, AESW_BASE, AES_INT_DATA_OUT);
        dataOutIntFlag = true;
    }
    if(intStatus & AES_INT_DMA_CONTEXT_IN)
    {
        //
        // DMA completed a context write to the internal registers.
        // Clear interrupt flag and disable requests from
        // the AES peripheral to DMA
        //
        AES_clearInterruptStatus(AESW_BASE, AES_INT_DMA_CONTEXT_IN);
        AES_disableDMARequest(AES_BASE, AES_DMA_EN_CONTEXT_IN);
        contextInDMADoneIntFlag = true;
    }
    if(intStatus & AES_INT_DMA_DATA_IN)
    {
        //
        // DMA has written the last word of input data to the internal FIFO of
        // the engine. Clear interrupt flag and disable requests from
        // the AES peripheral to DMA
        //
        AES_clearInterruptStatus(AESW_BASE, AES_INT_DMA_DATA_IN);
        AES_disableDMARequest(AES_BASE, AES_DMA_EN_DATA_IN);
        dataInDMADoneIntFlag = true;
    }
    if(intStatus & AES_INT_DMA_CONTEXT_OUT)
    {
        //
        // DMA completed the output context movement from the internal
        // registers. Clear interrupt flag and disable requests from
        // the AES peripheral to DMA
        //
        AES_clearInterruptStatus(AESW_BASE, AES_INT_DMA_CONTEXT_OUT);
        AES_disableDMARequest(AES_BASE, AES_DMA_EN_CONTEXT_OUT);
        contextOutDMADoneIntFlag = true;
    }
    if(intStatus & AES_INT_DMA_DATA_OUT)
    {
        //
        // DMA has written the last word of process result.
        // Clear interrupt flag and disable requests from
        // the AES peripheral to DMA
        //
        AES_clearInterruptStatus(AESW_BASE, AES_INT_DMA_DATA_OUT);
        AES_disableDMARequest(AES_BASE, AES_DMA_EN_DATA_OUT);
        dataOutDMADoneIntFlag = true;
    }
}

//
// End of File
//
