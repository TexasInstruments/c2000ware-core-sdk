//#############################################################################
//
// FILE:   aes_ex7_cmac_auth.c
//
// TITLE:  AES CBCMAC Encryption
//
//! \addtogroup driver_example_list
//! <h1>AES CMAC Authentication Example </h1>
//!
//! This example encrypts block cipher-text using AES128 and AES256 in CMAC mode and authenticates the result. It does
//! the encryption first without uDMA and then with uDMA. The results are
//! checked after each operation.
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//! - \b errCountGlobal - Error Counter. It should be zero.
//! - \b testStatusGlobal - Test status. It should be equal to PASS.
//!
//
//#############################################################################
//
//
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

#define BURST_SIZE         0x8
#define BURST_SRCSTEP      0x2
#define BURST_DESTSTEP     0x2
#define TRANSFER_SIZE      0x4
#define TRANSFER_SRCSTEP   0x2
#define TRANSFER_DESTSTEP  0x2
#define SRCWRAPSIZE        0x100
#define WRAP_SRCSTEP       0x10
#define DESTWRAPSIZE       0x100
#define WRAP_DESTSTEP      0x10
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
static volatile bool contextInDMADoneIntFlag;
static volatile bool dataInDMADoneIntFlag;
static volatile bool contextOutDMADoneIntFlag;
static volatile bool dataOutDMADoneIntFlag;

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
  .cmackey = { 0x10eb3d60,0xbe71ca15,0xf0ae732b,0x81777d85 },
  .dataLength = 64U,
  .iv = { 0x00000000,0x00000000,0x00000000,0x00000000 },
  .plainTextArray  = { 0xe2bec16b, 0x969f402e, 0x117e3de9, 0x2a179373,
                       0x578a2dae, 0x9cac031e, 0xac6fb79e, 0x518eaf45,
                       0x461cc830, 0x11e45ca3, 0x19c1fbe5, 0xef520a1a,
                       0x45249ff6, 0x179b4fdf, 0x7b412bad, 0x10376ce6 },
  .ExpectedTagOutArray = { 0x34D9A0D0,0x9C30F216,0xD67F99F6,0x7FCA511E }
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
  .ExpectedTagOutArray = { 0x7498147E,0x55F594D9,0x6DD6CB0B,0xD6157391 }
 }
};

//
// Function Prototypes
//
void performCMACAuthentication(AES_KeySize keySize, uint32_t *srcArray,
                          uint32_t *dstTagArray,   uint32_t *cmackey,
                          uint32_t *iv, uint32_t dataLength, bool useDMA);
uint32_t roundUpDataLength(uint32_t dataLength);
void initializeDMACH1(void);
void initializeDMACH2(void);
void configureDMACH1(const void *src, const void *dst, uint32_t transferSize);
void configureDMACH2(const void *src, const void *dst, uint32_t transferSize);
void configurreDMAInterruptCH1(void);
void configureDMAInteruptCH2(void);
void initilizeAES(void);
void startAES(void);

interrupt void AESDMADataInISR(void)
{
    AES_disableDMARequest(AESA_BASE, AES_DMA_EN_DATA_IN);
    dataInDMADoneIntFlag = true;
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);
}

interrupt void AESDMADataOutISR(void)
{
    AES_disableDMARequest(AESA_BASE, AES_DMA_EN_CONTEXT_OUT );
    dataOutDMADoneIntFlag = true;
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);
}

void initializeDMACH1(void)
{
    DMA_disableTrigger(DMA_CH1_BASE);
    DMA_clearTriggerFlag(DMA_CH1_BASE);
    DMA_clearErrorFlag(DMA_CH1_BASE);
}

void initializeDMACH2(void)
{
    DMA_disableTrigger(DMA_CH2_BASE);
    DMA_clearTriggerFlag(DMA_CH2_BASE);
    DMA_clearErrorFlag(DMA_CH2_BASE);
}

void configureDMACH1(const void *src, const void *dst, uint32_t transferSize)
{
    //
    //Configure DMA Channel 1 as needed
    //
    DMA_configAddresses(DMA_CH1_BASE,dst,src);
    //
    // Burst configuration with 4 32 bit words/burst. Destination is not moving.
    //
    DMA_configBurst(DMA_CH1_BASE,BURST_SIZE,BURST_SRCSTEP,0);
    //
    // Transfer configuration with 4 bursts/transfer. Destination is not moving.
    //
    DMA_configTransfer(DMA_CH1_BASE,transferSize,TRANSFER_SRCSTEP,0);
    //
    // Wrap condition enabled if more than 256 bursts/transfer
    //
    DMA_configWrap(DMA_CH1_BASE,SRCWRAPSIZE,WRAP_SRCSTEP,DESTWRAPSIZE,WRAP_DESTSTEP);
    DMA_configMode(DMA_CH1_BASE,DMA_TRIGGER_AESA_DATAIN,DMA_CFG_ONESHOT_DISABLE |
                   DMA_CFG_CONTINUOUS_DISABLE | DMA_CFG_SIZE_32BIT);
    DMA_enableTrigger(DMA_CH1_BASE);
}

void configureDMACH2(const void *src, const void *dst, uint32_t transferSize)
{
    //
    //Configure DMA Channel 2 as needed
    //
    DMA_configAddresses(DMA_CH2_BASE,dst,src);
    //
    // Burst configuration with 4 32 words/burst. Source is moving.
    //
    DMA_configBurst(DMA_CH2_BASE,16,1,1);
    //
    // Transfer configuration with 4 bursts/transfer. Source is not moving.
    //
    DMA_configTransfer(DMA_CH2_BASE,transferSize,0,TRANSFER_DESTSTEP);
    //
    // Wrap condition enabled if more than 256 bursts/transfer
    //
    DMA_configWrap(DMA_CH2_BASE,SRCWRAPSIZE,WRAP_SRCSTEP,DESTWRAPSIZE,WRAP_DESTSTEP);
    DMA_configMode(DMA_CH2_BASE,DMA_TRIGGER_AESA_CONTEXTOUT,DMA_CFG_ONESHOT_DISABLE |
                   DMA_CFG_CONTINUOUS_DISABLE | DMA_CFG_SIZE_32BIT);
    DMA_enableTrigger(DMA_CH2_BASE);
}

void configureDMAInterruptCH1(void)
{
    //
    // Register the interrupt handler.
    //
    Interrupt_register(INT_DMA_CH1, AESDMADataInISR);

    //
    // Enable the DMA interrupt.
    //
    Interrupt_enable(INT_DMA_CH1);
    Interrupt_enableGlobal();
    DMA_enableInterrupt(DMA_CH1_BASE);
    //
    // generate the interrupt at the end of the transfer.
    //
    DMA_setInterruptMode(DMA_CH1_BASE,DMA_INT_AT_END);
}

void configureDMAInterruptCH2(void)
{
    //
    // Register the interrupt handler.
    //
    Interrupt_register(INT_DMA_CH2, AESDMADataOutISR);

    //
    // Enable the DMA interrupt.
    //
    Interrupt_enable(INT_DMA_CH2);
    Interrupt_enableGlobal();
    DMA_enableInterrupt(DMA_CH2_BASE);
    //
    // generate the interrupt at the end of the transfer.
    //
    DMA_setInterruptMode(DMA_CH2_BASE,DMA_INT_AT_END);
}

void initilizeAES(void)
{
    Interrupt_disableGlobal();
    AES_disableGlobalInterrupt(AESA_SS_BASE);
    AES_performSoftReset(AESA_BASE);
}

void startAES(void)
{
    //
    //start the DMA Channel and wait for the trigger event.
    //
    DMA_startChannel(DMA_CH1_BASE);
    //
    //start the DMA Channel and wait for the trigger event.
    //
    DMA_startChannel(DMA_CH2_BASE);

    AES_enableDMARequest(AESA_BASE, AES_DMA_EN_DATA_IN | AES_DMA_EN_CONTEXT_OUT);
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
        // Perform Encryption without DMA.

        performCMACAuthentication(keySize, plainTextArray, TagOutArray, cmackey, iv, dataLength, false);

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

        //
        // Clear the array containing the cipher text.
        //
        for(cnt = 0; cnt < 4; cnt++)
        {
            TagOutArray[cnt] = 0;
        }

        //
        // Perform Encryption with DMA.
        //
        performCMACAuthentication(keySize, plainTextArray, TagOutArray, cmackey, iv, dataLength, true);

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
                          uint32_t *iv, uint32_t dataLength, bool useDMA)
{
    //
    // Clear the interrupt flags.
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
    // Depending on the argument, perform the decryption
    // with or without uDMA.
    //
    if(useDMA)
    {

        DMA_initController();

        initializeDMACH1();
        configureDMACH1((const void*)srcArray,
                        (const void*)(AESA_BASE + AES_O_DATA_IN_OUT_0),
                        (roundUpDataLength(dataLength) / 16U));
        configureDMAInterruptCH1();

        initializeDMACH2();
        configureDMACH2((const void*)(AESA_BASE + AES_O_TAG_OUT_0),
                        (const void*)TagOutArray,
                        1);
        configureDMAInterruptCH2();

        AES_setDataLength(AESA_BASE, dataLength);

        /*trigger dma*/
        startAES();

        //
        // Wait for the data in DMA done interrupt.
        //
        while(!dataInDMADoneIntFlag)
        {
        }

        //
        // Wait for the data out DMA done interrupt.
        //
        while(!dataOutDMADoneIntFlag)
        {
        }
    }
    else
    {
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
// End of File
//
