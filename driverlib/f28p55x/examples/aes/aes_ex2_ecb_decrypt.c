//#############################################################################
//
// FILE:   aes_ex2_ecb_decrypt.c
//
// TITLE:  AES ECB Decryption
//
//! \addtogroup driver_example_list
//! <h1>AES ECB De-cryption Example </h1>
//!
//! This example de-crypts block cipher-text using AES128 in ECB mode. It does
//! the de-cryption first without uDMA and then with uDMA. The results are
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
// C2000Ware v6.00.00.00
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
// Output plain-text array
//
#pragma DATA_SECTION(plainTextArray,"ramgs0");
uint32_t plainTextArray[16];

//
// Global interrupt status
//
static volatile uint32_t intStatus;

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
// Structure for NIST AES ECB tests
//
typedef struct
{
    AES_KeySize keySize;
    uint32_t keyArray[8];
    uint32_t dataLength;
    uint32_t plainTextArray[16];
    uint32_t cipherTextArray[16];
} testVectorECB;

//
// Test Cases from NIST ECB Revised Spec.
//
#pragma DATA_SECTION(testVectorECBArray,"ramgs0");
testVectorECB testVectorECBArray[] =
{
 //
 // Test Case #1 with 128 bit key
 //
 {
  .keySize = AES_KEY_SIZE_128BIT,
  .keyArray = { 0x16157e2b, 0xa6d2ae28, 0x8815f7ab, 0x3c4fcf09 },
  .dataLength = 64U,
  .plainTextArray  = { 0xe2bec16b, 0x969f402e, 0x117e3de9, 0x2a179373,
                       0x578a2dae, 0x9cac031e, 0xac6fb79e, 0x518eaf45,
                       0x461cc830, 0x11e45ca3, 0x19c1fbe5, 0xef520a1a,
                       0x45249ff6, 0x179b4fdf, 0x7b412bad, 0x10376ce6 },
  .cipherTextArray = { 0xb47bd73a, 0x60367a0d, 0xf3ca9ea8, 0x97ef6624,
                       0x85d5d3f5, 0x9d69b903, 0x5a8985e7, 0xafbafd96,
                       0x7fcdb143, 0x23ce8e59, 0xe3001b88, 0x880603ed,
                       0x5e780c7b, 0x3fade827, 0x71202382, 0xd45d7204 }
 },

 //
 // Test Case #2 with 256 bit key
 //
 {
  .keySize  = AES_KEY_SIZE_256BIT,
  .keyArray = { 0x10eb3d60, 0xbe71ca15, 0xf0ae732b, 0x81777d85,
                0x072c351f, 0xd708613b, 0xa310982d, 0xf4df1409 },
  .dataLength = 64U,
  .plainTextArray  = { 0xe2bec16b, 0x969f402e, 0x117e3de9, 0x2a179373,
                      0x578a2dae, 0x9cac031e, 0xac6fb79e, 0x518eaf45,
                      0x461cc830, 0x11e45ca3, 0x19c1fbe5, 0xef520a1a,
                      0x45249ff6, 0x179b4fdf, 0x7b412bad, 0x10376ce6 },
  .cipherTextArray = { 0xbdd1eef3, 0x3ca0d2b5, 0x7e5a4b06, 0xf881b13d,
                       0x10cb1c59, 0x26ed10d4, 0x4aa75bdc, 0x70283631,
                       0xb921edb6, 0xf9f4a69c, 0xb1e753f1, 0x1dedafbe,
                       0x7a4b3023, 0xfff3f939, 0x8f8d7d06, 0xc7ec249e }
 }
};

//
// Function Prototypes
//
void performECBDecryption(AES_KeySize keySize, uint32_t *srcArray,
                     uint32_t *dstArray,   uint32_t *keyArray,
                     uint32_t dataLength, bool useDMA);
uint32_t roundUpDataLength(uint32_t dataLength);
void initializeDMACH1(void);
void initializeDMACH2(void);
void configureDMACH1(const void *src, const void *dst, uint32_t transferSize);
void configureDMACH2(const void *src, const void *dst, uint32_t transferSize);
void configureDMAInterruptCH1(void);
void configureDMAInterruptCH2(void);
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
    AES_disableDMARequest(AESA_BASE, AES_DMA_EN_DATA_OUT);
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
    // Burst configuration with 4 32 words/burst. Source is not moving.
    //
    DMA_configBurst(DMA_CH2_BASE,BURST_SIZE,0,BURST_DESTSTEP);
    //
    // Transfer configuration with 4 bursts/transfer. Source is not moving.
    //
    DMA_configTransfer(DMA_CH2_BASE,transferSize,0,TRANSFER_DESTSTEP);
    //
    // Wrap condition enabled if more than 256 bursts/transfer
    //
    DMA_configWrap(DMA_CH2_BASE,SRCWRAPSIZE,WRAP_SRCSTEP,DESTWRAPSIZE,WRAP_DESTSTEP);
    DMA_configMode(DMA_CH2_BASE,DMA_TRIGGER_AESA_DATAOUT,DMA_CFG_ONESHOT_DISABLE |
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

    AES_enableDMARequest(AESA_BASE, AES_DMA_EN_DATA_IN | AES_DMA_EN_DATA_OUT);
}

//
// Main
//
void main(void)
{
    uint32_t errCountLocal, cnt;
    uint32_t *keyArray, dataLength;
    uint32_t *expPlainTextArray, *cipherTextArray;
    uint32_t vectorCnt;
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
        (vectorCnt < (sizeof(testVectorECBArray) /
         sizeof(testVectorECBArray[0]))); vectorCnt++)
    {
        //
        // Get the current vector's data members.
        //
        keySize  = testVectorECBArray[vectorCnt].keySize;
        keyArray = testVectorECBArray[vectorCnt].keyArray;
        dataLength         = testVectorECBArray[vectorCnt].dataLength;
        expPlainTextArray     = testVectorECBArray[vectorCnt].plainTextArray;
        cipherTextArray = testVectorECBArray[vectorCnt].cipherTextArray;

        //
        // Clear the array containing the plain text.
        //
        for(cnt = 0; cnt < 16; cnt++)
        {
            plainTextArray[cnt] = 0;
        }

        //
        // Perform decryption without DMA.
        //
        performECBDecryption(keySize, cipherTextArray, plainTextArray, keyArray,
                             dataLength, false);

        //
        // Check the results
        //
        for(cnt = 0; cnt < 16U; cnt++)
        {
            if(plainTextArray[cnt] != expPlainTextArray[cnt])
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
        // Clear the array containing the plain text.
        //
        for(cnt = 0; cnt < 16; cnt++)
        {
            plainTextArray[cnt] = 0;
        }

        //
        // Perform decryption with DMA.
        //
        performECBDecryption(keySize, cipherTextArray, plainTextArray, keyArray,
                             dataLength, true);

        //
        // Check the results.
        //
        for(cnt = 0; cnt < 16U; cnt++)
        {
            if(plainTextArray[cnt] != expPlainTextArray[cnt])
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
    }
}

//
// Perform an AES-ECB decryption operation.
//
void performECBDecryption(AES_KeySize keySize, uint32_t *srcArray,
                          uint32_t *dstArray,   uint32_t *keyArray,
                          uint32_t dataLength, bool useDMA)
{
    //
    // Perform a soft reset.
    //
    AES_performSoftReset(AESA_BASE);

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
    aesConfig.direction = AES_DIRECTION_DECRYPT;
    aesConfig.keySize = keySize;
    aesConfig.opMode = AES_OPMODE_ECB;
    AES_configureModule(AESA_BASE, &aesConfig);

    //
    // Write the key.
    //
    AES_setKey1(AESA_BASE, keyArray, keySize);

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
       configureDMACH2((const void*)(AESA_BASE + AES_O_DATA_IN_OUT_0),
                       (const void*)dstArray,
                       (roundUpDataLength(dataLength) / 16U));
       configureDMAInterruptCH2();

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
       // Perform the decryption.
       //
       AES_processData(AESA_BASE, srcArray, dstArray, dataLength);
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
