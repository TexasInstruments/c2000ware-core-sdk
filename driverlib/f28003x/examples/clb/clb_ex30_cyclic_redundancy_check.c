//#############################################################################
//
// FILE:   clb_ex30_Cylic_Redundancy_Check.c
//
// TITLE:  CLB Cyclic Redundancy Check(C.R.C./CRC)
//
//! \addtogroup driver_example_list
//! <h1>CLB CRC</h1>
//!
//! For the detailed description of this example, please refer to: 
//! `C2000Ware_PATH\utilities\clb_tool\clb_syscfg\doc\CLB Tool Users Guide.pdf`
//!
//! In this example, the CLB module is used to perform the cyclic redundancy check (C.R.C.)
//! with twelve messages in bits checked with ten different CRC polynomials.
//! 
//! First element passed in is message length, second is the message stored in input_data
//!
//! This example is only available for CLB types 2 and up.
//!
//! The known values in the output_data are compared with expected values from the CLB-based 
//! CRC calculation. A total of 120 messages are verified, and the number of matching messages 
//! are displayed in passCount
//!
//! Variables to add to Watch Expressions in debug view:
//! passCount - number of messages that match between generated and known CRC values
//! failCount - number of messages that fail the CRC value verification
//!
//#############################################################################
// $TI Release: F28003x Support Library v5.03.00.00 $
// 
// $Copyright:
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com/
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



#include "driverlib.h"
#include "device.h"
#include "clb_config.h"
#include "clb.h"
#include "board.h"

#define NUM_MESSAGES       12  // Number of input messages
#define NUM_CRC_POLY       10  // Number of CRC Polynomials in the test
#define BIT_LIMIT (5ul)
//
// Bit count is limited to 32 bits which denoted as << BIT_LIMIT
//
#define CLB_GPREG_RESET (1ul<<1)
#define CLB_GPREG_ASSERT (1ul<<2)
//
typedef struct CRC_DATA
{
    uint16_t crcSize;
    uint32_t crcMask;
    uint32_t crcPoly;
} CRC_DATA;
//
    uint16_t passCount = 0 ;
    uint16_t failCount = 0 ;
//
// The CRC_data includes ten different CRC polynomials for test
//
struct CRC_DATA myCRC[NUM_CRC_POLY] =
{
    // 0 Parity   x^1 + x^0
    {1u, 0x01ul, 0b11ul},
    // 1 CRC3_GSM x^3 + x^1 + x^0
    {3u, 0x07ul, 0b1011ul},
    // 2 CRC4_ITU x^4 + X^1 + X^0 = BiSS-C 0x13
    {4u, 0x0Ful, 0b10011ul},
    // 3 CRC5_ITU x^5 + x^4 + x^2 + x^0
    {5u, 0x1Ful, 0b110101ul},
    // 4 CRC5_USB x^5 + x^2 + 1 = BiSS-C 0x25
    {5u, 0x1Ful, 0b100101ul},
    // 5 CRC6_GSM x^6 + x^5 + x^3 + x^2 + x^1 + x^0
    {6u, 0x3Ful, 0b1101111ul},
    // 6 CRC6_ITU x^6 + x^1 + x^0 = BiSS-C 0x43
    {6u, 0x3Ful, 0b1000011ul},
    // 7 CRC7  x^7 + x^3 + x^0
    {7u, 0x7Ful, 0b10001001ul},
    // 8 CRC8_AUTOSAR x^8 + x^5 + x^3 + x^2 + x + 1
    {8u, 0xFFul, 0b100101111ul},
    // 9 CRC30 CDMA x^30 + x^29 + x^21 + x^20 + x^15 +
    //    x^13 + x^12 + x^11 + x^8 + x^7 + x^6 + x^2 + x^1 + x0
    {30u, 0x3FFFFFFFul, 0b1100000001100001011100111000111ul}
};

//
// First element in each input_data is the message length in bits
// Second element is the message.
//
// Note: bit count > 31 is not supported by this
//       implementation
//
uint32_t input_data[NUM_MESSAGES][2] =
{
      {1, 0x00000000},  // 0
      {1, 0x00000001},  // 1
      {2, 0x00000002},  // 2
      {8, 0x00000025},  // 3
      {16, 0x00002516},  // 4
      {24, 0x00106612},  // 5
      {18, 0x0002ADCB},  // 6
      {31, 0x251478AD},  // 7
      {23, 0x0003F737},  // 8
      {23, 0x0003FB43},  // 9
      {23, 0x0003FE13},  // 10
      {23, 0x0003FFA3}   // 11
};
//
// Expected CRC results for each polynomial
// Here output will be in rows that is Row_1 indicates first polynomial with all 12 messages
//
uint32_t output_data[NUM_CRC_POLY][NUM_MESSAGES] = {
    {0x0ul, 0x1ul, 0x1ul, 0x1ul, 0x0ul, 0x1ul, 0x1ul, 0x0ul, 0x0ul, 0x0ul, 0x0ul, 0x0ul},               // 0
    {0x0ul, 0x3ul, 0x6ul, 0x6ul, 0x7ul, 0x6ul, 0x2ul, 0x0ul, 0x4ul, 0x0ul, 0x6ul, 0x0ul},               // 1
    {0x0ul, 0x3ul, 0x6ul, 0x5ul, 0xDul, 0x1ul, 0xBul, 0xAul, 0xAul, 0x6ul, 0x2ul, 0xCul},               // 2
    {0x00ul, 0x15ul, 0x1Ful, 0x19ul, 0x09ul, 0x02ul, 0x16ul, 0x14ul, 0x14ul, 0x0Cul, 0x17ul, 0x18ul},   // 3
    {0x00ul, 0x05ul, 0x0aul, 0x00ul, 0x04ul, 0x0Eul, 0x09ul, 0x18ul, 0x19ul, 0x05ul, 0x1Bul, 0x02ul},   // 4
    {0x00ul, 0x2Ful, 0x31ul, 0x25ul, 0x2Dul, 0x1Cul, 0x37ul, 0x30ul, 0x17ul, 0x0aul, 0x36ul, 0x21ul},   // 5
    {0x00ul, 0x03ul, 0x06ul, 0x2Cul, 0x23ul, 0x28ul, 0x3ful, 0x12ul, 0x3Ful, 0x10ul, 0x22ul, 0x2Ful},   // 6
    {0x00ul, 0x09ul, 0x12ul, 0x1Ful, 0x7Aul, 0x73ul, 0x76ul, 0x6Ful, 0x21ul, 0x3Eul, 0x64ul, 0x05ul},   // 7
    {0x00ul, 0x2Ful, 0x5Eul, 0xe0ul, 0x3Aul, 0xE6ul, 0xCBul, 0x21ul, 0x3Ful, 0xE8ul, 0x9Cul, 0x4Bul},   // 8
    {0x00ul, 0x2030b9c7ul, 0x2051ca49ul, 0x24a9d36ful, 0x393897e8ul, 0x3f90cada, 0x269a9339, 0x356b051c,
     0x03f87CEDul, 0x08548079ul, 0x01a89110ul, 0x37066ef0ul  }                                          // 9
};

uint32_t calculate_crc(uint32_t *data, uint16_t bitCount, uint16_t crcSize, uint32_t crcPoly);

void main(void)
{
     
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pull ups.
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
    // Board Initialization
    //
    Board_init();

    //
    // Initialize CLB1 Tile
    //
    initTILE1(myTILE1_BASE);

    //
    // Enabling CLB1
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CLB1);
    CLB_enableCLB(myTILE1_BASE);

    uint16_t myPoly;


    for(myPoly = 0; myPoly < NUM_CRC_POLY; myPoly++)
    {
        uint16_t myMessage;

        for(myMessage = 0; myMessage < NUM_MESSAGES; myMessage++ )
        {
            uint16_t bitCount;
            uint32_t crc;

            //
            // CRC verification is done based on bit specified in bitCount
            //
            bitCount = input_data[myMessage][0]; 

            crc = 0x00;
            crc = calculate_crc(&input_data[myMessage][1], bitCount,
                myCRC[myPoly].crcSize, myCRC[myPoly].crcPoly);

            crc &= myCRC[myPoly].crcMask;
            if (crc == output_data[myPoly][myMessage])
            {
                passCount++;
            }
            else
            {
                failCount++;
            }
        }

    }
//
// Passcount displays - number which satisfies the CRC
// Failcount displays - number which fails the CRC
//
    if( passCount == (NUM_MESSAGES * NUM_CRC_POLY)  && failCount == 0)
    {
        // all passed
        asm(" ESTOP0");
    }
    else
    {
        // failures
        asm(" ESTOP0");
    }
}

uint32_t calculate_crc(uint32_t * data, uint16_t bitCount,
            uint16_t crcSize, uint32_t crcPoly)
{
    uint32_t crc;
    uint32_t msg;
    //
    // RESET and STOP (reset = 1, mode0 = 0)
    //
    CLB_setGPREG(myTILE1_BASE, (0 << 2 ) | (1 << 0));
    msg = *data;
    //
    // Using COUNTER_0 as Linear Feedback Shift Register (LFSR)
    // to calculate the CRC of the input
    //
    // Initialize the CRC polynomial and polynomial power.
    //    match2 -> polynomial
    //    match1 -> crc size - 1
    //    mode_1 -> 1
    //

    // CRC generator
    //
    CLB_writeInterface(myTILE1_BASE, CLB_ADDR_COUNTER_0_MATCH1, crcSize - 1);
    CLB_writeInterface(myTILE1_BASE, CLB_ADDR_COUNTER_0_MATCH2, crcPoly);

    //
    // Serialize Data - feeds the data to the CRC generator input
    //
    CLB_configCounterTapSelects(myTILE1_BASE, (bitCount) << BIT_LIMIT);
    CLB_writeInterface(myTILE1_BASE, CLB_ADDR_COUNTER_1_LOAD, msg);

    //
    // Bit count is limited to 32 bits which denoted as << BIT_LIMIT
    // Counts the number of shifts required to serialize the data
    // to the CRC generator.
    // When the count is matched, the CRC and serializer are halted
    //
    CLB_writeInterface(myTILE1_BASE, CLB_ADDR_COUNTER_2_MATCH1, (bitCount + crcSize + 1) );

    //
    //  Release RESET and assert RUN
    //  Wait for the CRC to complete, then read the CRC Result on the passcount and failcount
    //
    CLB_setGPREG(myTILE1_BASE, CLB_GPREG_ASSERT);
    while(CLB_getInterruptTag(myTILE1_BASE) != 1)
    {
    }
    crc = CLB_getRegister(myTILE1_BASE, CLB_REG_CTR_C0);
    CLB_clearInterruptTag(myTILE1_BASE);
    return(crc);
}


//
