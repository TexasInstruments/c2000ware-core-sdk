//#############################################################################
//
// FILE:   aes_ex7_cmac_auth.c
//
// TITLE:  AES CMAC Authentication Example
//
//! \addtogroup driver_example_list
//! <h1>AES CMAC Authentication Example </h1>
//!
//! This example demonstrates AES Cipher-based Message Authentication Code (CMAC)
//! generation using both AES-128 and AES-256 key sizes. The example processes
//! test vectors and verifies the output tags against expected results.
//!
//! The example implements the following operations:
//!  - Generation of CMAC subkeys (k1 and k2) from the encryption key
//!  - CMAC authentication with proper padding for block-aligned data
//!  - Processing of multiple test vectors for verification
//!
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//! - \b errCountGlobal - Error counter. Should be zero for successful verification.
//! - \b testStatusGlobal - Test status. Should be equal to TEST_PASS (0xABCDABCD).
//! - \b TagOutArray - Generated authentication tags for verification.
//!
//
//#############################################################################
//
//
// 
// C2000Ware v26.01.00.00
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
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com
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
#include "driverlib.h"
#include "device.h"

//
// Defines
//
#define TEST_PASS 0xABCDABCD
#define TEST_FAIL 0xDEADDEAD

//
// Global Variables
//

//
// Global error counter & status
//
uint16_t errCountGlobal = 0;
uint32_t testStatusGlobal;

//
// Output tag-out array
//
#pragma DATA_SECTION(TagOutArray,"ramgs0");
uint32_t TagOutArray[4];

//
// Global interrupt status
//
static volatile uint32_t intStatus = 0;

//
// The AES interrupt handler and interrupt flags.
//
static volatile bool contextInIntFlag;
static volatile bool dataInIntFlag;
static volatile bool contextOutIntFlag;
static volatile bool dataOutIntFlag;

//
// Structure for NIST AES CBCMAC tests
//
typedef struct
{
    AES_KeySize keySize;
    uint32_t cmackey[8];
    uint32_t dataLength;
    uint32_t iv[4];
    uint32_t plainTextArray[16];
    uint32_t ExpectedTagOutArray[16];
} testVectorCBCMAC;


//
// Test Cases from NIST ECB Revised Spec.
//
#pragma DATA_SECTION(testVectorCBCMACArray,"ramgs0");
testVectorCBCMAC testVectorCBCMACArray[] =
{
 //
 // Test Case #1 with 128 bit key
 //
 {
  .keySize  = AES_KEY_SIZE_128BIT,
  .cmackey = { 0x16157e2b, 0xa6d2ae28, 0x8815f7ab, 0x3c4fcf09 },
  .dataLength = 64U,
  .iv = { 0x00000000,0x00000000,0x00000000,0x00000000 },
  .plainTextArray  = { 0xe2bec16b, 0x969f402e, 0x117e3de9, 0x2a179373,
                       0x578a2dae, 0x9cac031e, 0xac6fb79e, 0x518eaf45,
                       0x461cc830, 0x11e45ca3, 0x19c1fbe5, 0xef520a1a,
                       0x45249ff6, 0x179b4fdf, 0x7b412bad, 0x10376ce6 },
  .ExpectedTagOutArray = { 0xbfbef051, 0x929d3b7e, 0x177449fc, 0xfe3c3679 },
 },

 //
 // Test Case #2 with 256 bit key
 //
 {
  .keySize  = AES_KEY_SIZE_256BIT,
  .cmackey = { 0x10eb3d60,0xbe71ca15,0xf0ae732b,0x81777d85, 0x072c351f,0xd708613b,0xa310982d,0xf4df1409 },
  .dataLength = 64U,
  .iv = { 0x00000000, 0x00000000, 0x00000000, 0x00000000 },
  .plainTextArray  = { 0xe2bec16b, 0x969f402e, 0x117e3de9, 0x2a179373,
                       0x578a2dae, 0x9cac031e, 0xac6fb79e, 0x518eaf45,
                       0x461cc830, 0x11e45ca3, 0x19c1fbe5, 0xef520a1a,
                       0x45249ff6, 0x179b4fdf, 0x7b412bad, 0x10376ce6 },
  .ExpectedTagOutArray = { 0x902199e1, 0xd56e9f54, 0x052c6a69, 0x1054316c}
 }
};

//
// Function Prototypes
//
void performCMACAuthentication(AES_KeySize keySize, uint32_t *srcArray,
                          uint32_t *dstTagArray,   uint32_t *cmackey,
                          uint32_t *iv, uint32_t dataLength);
void performECBEncryption(AES_KeySize keySize, uint32_t *srcArray,
                          uint32_t *dstArray,   uint32_t *keyArray,
                          uint32_t dataLength);
void generateSubKey(AES_KeySize keySize, uint32_t *cmackey, uint32_t *iv, uint32_t* subKey1, uint32_t* subKey2);

void array_shift_and_generate(const uint32_t input[], uint32_t output[]);

void array_xor_inplace_generic(uint32_t* data, const uint32_t* xor, uint32_t size);
void initilizeAES(void);

void initilizeAES(void)
{
    Interrupt_disableGlobal();
    AES_disableGlobalInterrupt(AESA_SS_BASE);
    AES_performSoftReset(AESA_BASE);
}
//
// Main
//
void main(void)
{
    uint32_t errCountLocal, cnt;
    uint32_t *cmackey, dataLength;
    uint32_t *ExpectedTagOutArray, *plainTextArray;
    uint32_t vectorCnt;
    uint32_t *iv;
    AES_KeySize keySize;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Initialize GPIO and configure the GPIO pin as a push-pull output
    //
    Device_initGPIO();

    //
    // Disable global interrupts.
    //
    DINT;

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
    // Initialize local variables.
    //
    errCountLocal = 0;

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;


    //
    // Loop through all the given vectors.
    //
    for(vectorCnt = 0;
        (vectorCnt < (sizeof(testVectorCBCMACArray) /
         sizeof(testVectorCBCMACArray[0]))); vectorCnt++)
    {
        //
        // Get the current vector's data members.
        //
        keySize  = testVectorCBCMACArray[vectorCnt].keySize;
        cmackey = testVectorCBCMACArray[vectorCnt].cmackey ;
        dataLength         = testVectorCBCMACArray[vectorCnt].dataLength;
        plainTextArray     = testVectorCBCMACArray[vectorCnt].plainTextArray;
        ExpectedTagOutArray = testVectorCBCMACArray[vectorCnt].ExpectedTagOutArray;
        iv                 = testVectorCBCMACArray[vectorCnt].iv;

        //
        // Clear the array containing the Tag.
        //
        for(cnt = 0; cnt < 4; cnt++)
        {
            TagOutArray[cnt] = 0;
        }

        //
        // Perform Encryption
        //

        performCMACAuthentication(keySize, plainTextArray, TagOutArray, cmackey, iv, dataLength);

        //
        // Check the results
        //
        for(cnt = 0; cnt < 4U; cnt++)
        {
            if(TagOutArray[cnt] != ExpectedTagOutArray[cnt])
            {
                errCountLocal++;
            }
        }

        //
        // Update the global error counter.
        //
        if(errCountLocal > 0)
        {
            errCountGlobal++;
        }

        //
        // Clear the local error counter.
        //
        errCountLocal = 0;
    }

    //
    // Clean up AES Data registers
    //
    AES_performSoftReset(AESA_BASE);

    //
    // Update test status variable
    //
    if(errCountGlobal == 0)
    {
        testStatusGlobal = TEST_PASS;
    }
    else
    {
        testStatusGlobal = TEST_FAIL;
    }

    //
    // Infinite Loop to keep the core running
    //
    while(1)
    {
        asm(" ESTOP0");
    }
}

//
// Perform an AES-CBCMAC encryption operation.
//
void performCMACAuthentication(AES_KeySize keySize, uint32_t *srcArray,
                          uint32_t *dstTagArray,   uint32_t *cmackey,
                          uint32_t *iv, uint32_t dataLength)
{
    uint32_t subKey1[4] = {0};
    uint32_t subKey2[4] = {0};
    bool dataSizeAligned = true;// Set this to false if data is not 16 byte aligned. Padding with 0x80 is required.

    generateSubKey(keySize, cmackey, iv, subKey1, subKey2);

    if(dataSizeAligned)
    {

        array_xor_inplace_generic(srcArray + ((dataLength/4U) - 4U), subKey1, 4U );
    }
    else 
    {
        array_xor_inplace_generic(srcArray + ((dataLength/4U) - 4U), subKey2, 4U );
    }
    //
    // Clear the interrupt flags.
    //
    contextInIntFlag = false;
    dataInIntFlag = false;
    contextOutIntFlag = false;
    dataOutIntFlag = false;

    //
    // Perform a soft reset.
    //
    initilizeAES();

    //
    // Configure the AES module.
    //
    AES_ConfigParams aesConfig;
    memset(&aesConfig, 0, sizeof(AES_ConfigParams));
    aesConfig.direction = AES_DIRECTION_ENCRYPT;
    aesConfig.keySize = keySize;
    aesConfig.opMode = AES_OPMODE_CBCMAC;
    aesConfig.ctrWidth = AES_CTR_WIDTH_32BIT;
    aesConfig.ccmLenWidth = AES_CCM_L_1;
    aesConfig.ccmAuthLenWidth = AES_CCM_M_16;


    AES_configureModule(AESA_BASE, &aesConfig);

    //
    // Write the initialization value
    //
    AES_setInitializationVector(AESA_BASE, iv);

    //
    // Write the keys.
    //
    AES_setKey1(AESA_BASE,cmackey,keySize);

    //
    // Enable all interrupts.
    //
    AES_enableInterrupt(AESA_BASE, (AES_INT_CONTEXT_IN |
                        AES_INT_CONTEXT_OUT | AES_INT_DATA_IN    |
                        AES_INT_DATA_OUT));

    //
    // Perform the authentication.
    //
    AES_authenticateData(AESA_BASE, srcArray, dataLength, dstTagArray);


}
void performECBEncryption(AES_KeySize keySize, uint32_t *srcArray,
                          uint32_t *dstArray,   uint32_t *keyArray,
                          uint32_t dataLength)
{
    //
    // Clear the interrupt flags.
    //
    contextInIntFlag = false;
    dataInIntFlag = false;
    contextOutIntFlag = false;
    dataOutIntFlag = false;

    //
    // Perform a soft reset.
    //
    initilizeAES();

    //
    // Configure the AES module.
    //
    AES_ConfigParams aesConfig;
    memset(&aesConfig, 0, sizeof(AES_ConfigParams));
    aesConfig.direction = AES_DIRECTION_ENCRYPT;
    aesConfig.keySize = keySize;
    aesConfig.opMode = AES_OPMODE_ECB;
    aesConfig.ctrWidth = AES_CTR_WIDTH_32BIT;
    aesConfig.ccmLenWidth = AES_CCM_L_1;
    aesConfig.ccmAuthLenWidth = AES_CCM_M_0;


    AES_configureModule(AESA_BASE, &aesConfig);

    //
    // Write the key.
    //
    AES_setKey1(AESA_BASE, keyArray, keySize);

    //
    //
    // Enable all interrupts.
    //
    AES_enableInterrupt(AESA_BASE, (AES_INT_CONTEXT_IN |
                        AES_INT_CONTEXT_OUT | AES_INT_DATA_IN    |
                        AES_INT_DATA_OUT));

    //
    // Perform the encryption.
    //
    AES_processData(AESA_BASE, srcArray, dstArray, dataLength);
}
void generateSubKey(AES_KeySize keySize, uint32_t *cmackey, uint32_t *iv, uint32_t* subKey1, uint32_t* subKey2){
    uint32_t L[4];
    performECBEncryption(keySize, iv, L, cmackey, 16U);

    array_shift_and_generate(L, subKey1);

    array_shift_and_generate(subKey1, subKey2);

}
void array_shift_and_generate(const uint32_t input[], uint32_t output[]) {
    uint32_t temp[4];
    uint32_t carry = 0;
    int i;
    uint32_t msbCheck = 0x80;
    uint32_t Rb = 0x87;
    
    // Copy and convert endianness
    for (i = 0; i < 4; i++) {
        temp[i] = ((input[i] & 0xFF000000) >> 24) |
                  ((input[i] & 0x00FF0000) >> 8)  |
                  ((input[i] & 0x0000FF00) << 8)  |
                  ((input[i] & 0x000000FF) << 24);
    }
    
    // Left shift the entire 128-bit value by 1
    for (i = 3; i >= 0; i--) {
        uint32_t next_carry = (temp[i] & 0x80000000U) ? 1U : 0U;
        temp[i] = (temp[i] << 1) | carry;
        carry = next_carry;
    }

    if((input[0] & msbCheck) == msbCheck){
        temp[3] = temp[3] ^ Rb;
    }
    
    // Convert back to original endianness
    for (i = 0; i < 4; i++) {
        output[i] = ((temp[i] & 0xFF000000) >> 24) |
                    ((temp[i] & 0x00FF0000) >> 8)  |
                    ((temp[i] & 0x0000FF00) << 8)  |
                    ((temp[i] & 0x000000FF) << 24);
    }
}
void array_xor_inplace_generic(uint32_t* array1, const uint32_t* array2, uint32_t size) {
    uint32_t i;
    for (i = 0; i < size; i++) {
        array1[i] ^= array2[i];
    }
}
//
// End of File
//
