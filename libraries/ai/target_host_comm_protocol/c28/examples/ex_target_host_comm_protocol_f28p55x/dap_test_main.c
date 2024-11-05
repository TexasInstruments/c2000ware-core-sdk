//#############################################################################
//
// FILE:   dap_test_main.c
//
//!
//! This example is shows how to execute device agent protocol(dap) on the target
//! MCU side
//
//#############################################################################
//
//
// 
// C2000Ware v5.04.00.00
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

#include "board.h"
#include "c2000ware_libraries.h"
#include "dap_interface.h"


extern volatile int start_sending_data;


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
    // GPIO28 is the SCI Rx pin.
    //
    GPIO_setPinConfig(DEVICE_GPIO_CFG_SCIRXDA);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_SCIRXDA, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_SCIRXDA, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SCIRXDA, GPIO_QUAL_ASYNC);

    //
    // GPIO29 is the SCI Tx pin.
    //
    GPIO_setPinConfig(DEVICE_GPIO_CFG_SCITXDA);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_SCITXDA, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_SCITXDA, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SCITXDA, GPIO_QUAL_ASYNC);

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
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    guiInitialization();

    //
    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    //
    EINT;
    ERTM;
    //
    // Send starting message (for debugging purposes)
    //
    if(TERMINAL_DEBUGGING_MODE){
        unsigned char *msg;
        msg = "Welcome\n";
        sci_write_char_array((uint16_t*)msg, 8);
    }

    while(1)
    {

        if(start_sending_data==1)
        {

            // For 16 bits sensor data transmission check comment/uncomment below part
            /*
            uint8_t temp_databuff[4*2];
            uint16_t sensor3_data[4] = {0xa1ab,0xb2bc,0xc3cd,0xd4ef};
            int sample_size1 = sizeof(sensor3_data);
            data_conversion_from_16_to_8_bits(sensor3_data, sample_size1, temp_databuff);
            */

            // For 32 bits sensor data transmission check comment/uncomment below part

            uint8_t temp_databuff[4*2*2];
            uint32_t sensor4_data[4] = {0xa1a2a3a4,0xb1b2b3b4,0xc1c2c3c4,0xd1d2d3d4};
            int sample_size2 = sizeof(sensor4_data);
            data_conversion_from_32_to_8_bits(sensor4_data, sample_size2, temp_databuff);

            uint32_t dataLen = sizeof(temp_databuff);
            //uint32_t dataLen = 0x9d;

            uint16_t channelVal = sensor_signal;

            received_data_response(dataLen, channelVal, temp_databuff);
            DEVICE_DELAY_US(4000);
            NOP;

        }
        else
        {
            //start_sending_data=0;
        }
    }
}

//
// End of File
//
