/*
 *  Created on: Aug 30, 2024
 */
//#############################################################################
//
// FILE:   dap_core.c
//
//!
//! This contains definition of core API functions required to support device
//! agent protocol(dap)
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
//#############################################################################

#include "dap_core.h"

//external variables
int rx_fifo_level_reconfig;
int first_sensor_index;
int second_sensor_index;
int third_sensor_index;
int forth_sensor_index;
int index_of_property;
volatile int start_sending_data = 0;
volatile int payload_length_byte_size = 0;

extern const char Device_name[];
extern volatile uint16_t property_val_uint16;
extern volatile uint32_t property_val_uint32;

volatile uint16_t test_property_uint16 = 0;
volatile uint32_t test_property_uint32 = 0;


/*Initialization Functions*/
void SCI_init(){
    /********* SCI Initialization **********/

    //Register SCI RX Interrupt
    Interrupt_register(INT_SCIA_RX, sciaRXFIFOISR);
    //
    // Initialize SCIA and its FIFO.
    //
    SCI_performSoftwareReset(SCI_INST_BASE_ADDR);

    //
    // Configure SCIA for echoback.
    //
    SCI_setConfig(SCI_INST_BASE_ADDR, DEVICE_LSPCLK_FREQ, SCI_BAUD_RATE, (SCI_CONFIG_WLEN_8 |
                                                        SCI_CONFIG_STOP_ONE |
                                                        SCI_CONFIG_PAR_NONE));

    SCI_setFIFOInterruptLevel(SCI_INST_BASE_ADDR, TX_FIFO_LEVEL, RX_FIFO_LEVEL);
    //SCI_setFIFOInterruptLevel(SCIA_BASE, TX_FIFO_LEVEL, RX_FIFO_LEVEL);
    SCI_resetChannels(SCI_INST_BASE_ADDR);
    SCI_resetRxFIFO(SCI_INST_BASE_ADDR);
    SCI_resetTxFIFO(SCI_INST_BASE_ADDR);
    SCI_clearInterruptStatus(SCI_INST_BASE_ADDR, SCI_INT_RXFF);
    SCI_enableFIFO(SCI_INST_BASE_ADDR);
    SCI_enableModule(SCI_INST_BASE_ADDR);

    rx_fifo_level_reconfig = 4;
    //
    // RX and TX FIFO Interrupts Enabled
    //
    SCI_enableInterrupt(SCI_INST_BASE_ADDR, (SCI_INT_RXFF));
    SCI_disableInterrupt(SCI_INST_BASE_ADDR, SCI_INT_RXERR);

    SCI_performSoftwareReset(SCI_INST_BASE_ADDR);

    Interrupt_enable(INT_SCIA_RX);

    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
}

/* Top Level Functions */
void guiInitialization(){
    SCI_init();
}

void get_capabilites_response()
{
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, START_BYTE);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, get_capabilities);
    int get_capability_payload_length = strlen(Device_name)+4;
    uint32_t payload_length = payload_length_cal(get_capability_payload_length);
    //SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, get_capability_length);
    if(payload_length_byte_size==1)
    {
        uint8_t data_byte1 = payload_length & 0xFF;
        SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, data_byte1);
    }
    else if(payload_length_byte_size==2)
    {
        uint8_t data_byte1 = (payload_length>>8) & 0xFF;
        uint8_t data_byte2 = payload_length & 0xFF;
        SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, data_byte1);
        SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, data_byte2);
    }
    else if(payload_length_byte_size==3)
    {
        uint8_t data_byte1 = (payload_length>>16) & 0xFF;
        uint8_t data_byte2 = (payload_length>>8) & 0xFF;
        uint8_t data_byte3 = payload_length & 0xFF;
        SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, data_byte1);
        SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, data_byte2);
        SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, data_byte3);
    }
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, API_version);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, capability_bits_flag);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, sdk_major_version);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, sdk_minor_version);
    SCI_writeCharArray(SCI_INST_BASE_ADDR, (uint16_t*)Device_name, strlen(Device_name));
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, END_BYTE);
}

void list_sensor_response(uint16_t sensor_count, uint16_t sensor_index, const char sensor_index_info[])
{
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, START_BYTE);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, list_sensors);
    int sensor_info_length = (strlen(sensor_index_info))+2;
    uint32_t payload_length = payload_length_cal(sensor_info_length);
    //SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, sensor_info_length);
    if(payload_length_byte_size==1)
    {
        uint8_t data_byte1 = payload_length & 0xFF;
        SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, data_byte1);
    }
    else if(payload_length_byte_size==2)
    {
        uint8_t data_byte1 = (payload_length>>8) & 0xFF;
        uint8_t data_byte2 = payload_length & 0xFF;
        SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, data_byte1);
        SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, data_byte2);
    }
    else if(payload_length_byte_size==3)
    {
        uint8_t data_byte1 = (payload_length>>16) & 0xFF;
        uint8_t data_byte2 = (payload_length>>8) & 0xFF;
        uint8_t data_byte3 = payload_length & 0xFF;
        SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, data_byte1);
        SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, data_byte2);
        SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, data_byte3);
    }
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, sensor_count);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, sensor_index);
    SCI_writeCharArray(SCI_INST_BASE_ADDR, (uint16_t*)sensor_index_info, sensor_info_length-2);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, END_BYTE);
}

void list_model_response(uint16_t model_count, uint16_t model_index, const char model_index_info[])
{
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, START_BYTE);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, list_models);
    int model_info_length = (strlen(model_index_info))+2;
    uint32_t payload_length = payload_length_cal(model_info_length);
    //SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, model_info_length);
    if(payload_length_byte_size==1)
    {
        uint8_t data_byte1 = payload_length & 0xFF;
        SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, data_byte1);
    }
    else if(payload_length_byte_size==2)
    {
        uint8_t data_byte1 = (payload_length>>8) & 0xFF;
        uint8_t data_byte2 = payload_length & 0xFF;
        SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, data_byte1);
        SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, data_byte2);
    }
    else if(payload_length_byte_size==3)
    {
        uint8_t data_byte1 = (payload_length>>16) & 0xFF;
        uint8_t data_byte2 = (payload_length>>8) & 0xFF;
        uint8_t data_byte3 = payload_length & 0xFF;
        SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, data_byte1);
        SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, data_byte2);
        SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, data_byte3);
    }
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, model_count);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, model_index);
    SCI_writeCharArray(SCI_INST_BASE_ADDR, (uint16_t*)model_index_info, (model_info_length-2));
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, END_BYTE);
}

void RX_FIFO_level_reset_before_pipeline_config()
{
    //**********RX_FIFO level reset for configure_pipeline_cmd*********//
    SCI_disableFIFO(SCI_INST_BASE_ADDR);
    SCI_setFIFOInterruptLevel(SCI_INST_BASE_ADDR, TX_FIFO_LEVEL, SCI_FIFO_RX6);
    SCI_resetRxFIFO(SCI_INST_BASE_ADDR);
    SCI_enableFIFO(SCI_INST_BASE_ADDR);
    rx_fifo_level_reconfig = 6;
}

void configure_pipeline_response()
{
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, START_BYTE);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, configure_pipeline);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, configure_pipeline_length);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, END_BYTE);
}

void RX_FIFO_level_reset_after_pipeline_config()
{
    SCI_disableFIFO(SCI_INST_BASE_ADDR);
    SCI_setFIFOInterruptLevel(SCI_INST_BASE_ADDR, TX_FIFO_LEVEL, SCI_FIFO_RX4);
    SCI_resetRxFIFO(SCI_INST_BASE_ADDR);
    SCI_enableFIFO(SCI_INST_BASE_ADDR);
    rx_fifo_level_reconfig = 4;
}

void start_streaming_response()
{
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, START_BYTE);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, start_streaming);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, start_streaming_length);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, END_BYTE);

    start_sending_data = 1;
}

int payload_length_cal(uint32_t original_data_length)
{
    uint32_t modified_data_length;
    if(original_data_length<=0x7f)
    {
        modified_data_length = original_data_length;
        payload_length_byte_size = 1;
    }
    else if((original_data_length>=0x80) && (original_data_length<=0x3ff))
    {
        modified_data_length = 0x8000 + original_data_length;
        payload_length_byte_size = 2;
    }
    else if(original_data_length>=0x4000)
    {
        modified_data_length = 0xc00000 + original_data_length;
        payload_length_byte_size = 3;
    }
    return modified_data_length;
}

void received_data_response(uint32_t data_payload_length, uint16_t channel_value, uint16_t* data_array)
{
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, START_BYTE);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, (0x10 | channel_value));
    uint32_t payload_length = payload_length_cal(data_payload_length);
    if(payload_length_byte_size==1)
    {
        uint8_t data_byte1 = payload_length & 0xFF;
        SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, data_byte1);
    }
    else if(payload_length_byte_size==2)
    {
        uint8_t data_byte1 = (payload_length>>8) & 0xFF;
        uint8_t data_byte2 = payload_length & 0xFF;
        SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, data_byte1);
        SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, data_byte2);
    }
    else if(payload_length_byte_size==3)
    {
        uint8_t data_byte1 = (payload_length>>16) & 0xFF;
        uint8_t data_byte2 = (payload_length>>8) & 0xFF;
        uint8_t data_byte3 = payload_length & 0xFF;
        SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, data_byte1);
        SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, data_byte2);
        SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, data_byte3);
    }
    SCI_writeCharArray(SCI_INST_BASE_ADDR, data_array, (data_payload_length));
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, END_BYTE);
}

void stop_streaming_response()
{
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, START_BYTE);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, stop_streaming);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, stop_streaming_length);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, END_BYTE);

    start_sending_data = 0;
}

void property_read_response_uint16(uint16_t property_index, uint16_t property_value)
{
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, START_BYTE);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, property_read);
    //SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, property_read_length);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, 3);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, property_index);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, (property_value>>8) & 0xFF);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, property_value & 0xFF);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, END_BYTE);
}

void property_read_response_uint32(uint16_t property_index, uint32_t property_value)
{
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, START_BYTE);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, property_read);
    //SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, property_read_length);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, 5);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, property_index);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, (property_value>>24) & 0xFF);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, (property_value>>16) & 0xFF);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, (property_value>>8) & 0xFF);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, property_value & 0xFF);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, END_BYTE);
}

void property_written_response(uint16_t property_index)
{
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, START_BYTE);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, property_written);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, property_written_length);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, property_index);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, END_BYTE);
}

void list_property_response(uint16_t property_count, uint16_t property_index, uint16_t property_dataformat, const char property_index_info[])
{
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, START_BYTE);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, list_properties);
    int property_info_length = (strlen(property_index_info))+3;
    uint32_t payload_length = payload_length_cal(property_info_length);
    //SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, property_info_length);
    if(payload_length_byte_size==1)
    {
        uint8_t data_byte1 = payload_length & 0xFF;
        SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, data_byte1);
    }
    else if(payload_length_byte_size==2)
    {
        uint8_t data_byte1 = (payload_length>>8) & 0xFF;
        uint8_t data_byte2 = payload_length & 0xFF;
        SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, data_byte1);
        SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, data_byte2);
    }
    else if(payload_length_byte_size==3)
    {
        uint8_t data_byte1 = (payload_length>>16) & 0xFF;
        uint8_t data_byte2 = (payload_length>>8) & 0xFF;
        uint8_t data_byte3 = payload_length & 0xFF;
        SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, data_byte1);
        SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, data_byte2);
        SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, data_byte3);
    }
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, property_count);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, property_index);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, property_dataformat);
    SCI_writeCharArray(SCI_INST_BASE_ADDR, (uint16_t*)property_index_info, (property_info_length-3));
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, END_BYTE);
}

void list_inference_values_response(uint16_t inference_count, uint16_t inference_index, uint16_t inference_dataformat, const char inference_index_info[])
{
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, START_BYTE);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, list_inferencing_values);
    int inference_info_length = (strlen(inference_index_info))+3;
    uint32_t payload_length = payload_length_cal(inference_info_length);
    //SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, inference_info_length);
    if(payload_length_byte_size==1)
    {
        uint8_t data_byte1 = payload_length & 0xFF;
        SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, data_byte1);
    }
    else if(payload_length_byte_size==2)
    {
        uint8_t data_byte1 = (payload_length>>8) & 0xFF;
        uint8_t data_byte2 = payload_length & 0xFF;
        SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, data_byte1);
        SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, data_byte2);
    }
    else if(payload_length_byte_size==3)
    {
        uint8_t data_byte1 = (payload_length>>16) & 0xFF;
        uint8_t data_byte2 = (payload_length>>8) & 0xFF;
        uint8_t data_byte3 = payload_length & 0xFF;
        SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, data_byte1);
        SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, data_byte2);
        SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, data_byte3);
    }
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, inference_count);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, inference_index);
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, inference_dataformat);
    SCI_writeCharArray(SCI_INST_BASE_ADDR, (uint16_t*)inference_index_info, (inference_info_length-3));
    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, END_BYTE);
}

void data_conversion_from_16_to_8_bits(uint16_t* input_buf, int input_buf_size, uint8_t* output_buf)
{
    int i = 0;

    for(i=0;i<input_buf_size;i++)
    {
        uint8_t byte1 = (input_buf[i]>>8) & 0xFF;
        uint8_t byte2 = input_buf[i] & 0xFF;
        output_buf[i*2] =  byte1 ;
        output_buf[i*2+1] =  byte2;

        //input_buf[i] = ((byte1 << 8) | byte2)   --> In Big_endian format
    }
}


void data_conversion_from_32_to_8_bits(uint32_t* input_buf, int input_buf_size, uint8_t* output_buf)
{
    int i = 0;

    for(i=0;i<input_buf_size;i++)
    {
        uint8_t byte1 = (input_buf[i]>>24) & 0xFF;
        uint8_t byte2 = (input_buf[i]>>16) & 0xFF;
        uint8_t byte3 = (input_buf[i]>>8) & 0xFF;
        uint8_t byte4 = input_buf[i] & 0xFF;
        output_buf[i*4] =  byte1 ;
        output_buf[i*4+1] =  byte2;
        output_buf[i*4+2] =  byte3;
        output_buf[i*4+3] =  byte4;

        //input_buf[i] = ((byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4)   --> In Big_endian format
    }
}

/* Interrupt Service Routines */
//
// sciaRXFIFOISR - SCIA Receive FIFO ISR
//
volatile uint16_t temp = 0;

__interrupt void sciaRXFIFOISR(void)
{
    uint16_t rxTempBuffer[16] = {};
    unsigned char *msg;
    uint16_t delay = 0;
    //Delay before reading into RXbuff
    //for(delay=0;delay<7500;delay++)
    //for(delay=0;delay<500;delay++)              //Minimum delay tested for Sysclk/4
    for(delay=0;delay<18000;delay++)              //For Sysclk/4
    //for(delay=0;delay<40000;delay++)              //For Sysclk/2
    //for(delay=0;delay<35000;delay++)                //For Sysclk/2
    //for(delay=0;delay<50000;delay++)                //For Sysclk/1
    {
        temp++;
    }


    {
        if(SCI_getRxFIFOStatus(SCI_INST_BASE_ADDR) == 0xa)
        {
            SCI_readCharArray(SCI_INST_BASE_ADDR, rxTempBuffer, 10);
        }
        else if(SCI_getRxFIFOStatus(SCI_INST_BASE_ADDR) == 0x9)
        {
            SCI_readCharArray(SCI_INST_BASE_ADDR, rxTempBuffer, 9);
        }
        else if(SCI_getRxFIFOStatus(SCI_INST_BASE_ADDR) == 0x8)
        {
            SCI_readCharArray(SCI_INST_BASE_ADDR, rxTempBuffer, 8);
        }
        else if(SCI_getRxFIFOStatus(SCI_INST_BASE_ADDR) == 0x7)
        {
            SCI_readCharArray(SCI_INST_BASE_ADDR, rxTempBuffer, 7);
        }
        else if(SCI_getRxFIFOStatus(SCI_INST_BASE_ADDR) == 0x6)
        {
            SCI_readCharArray(SCI_INST_BASE_ADDR, rxTempBuffer, 6);
        }
        else if(SCI_getRxFIFOStatus(SCI_INST_BASE_ADDR) == 0x5)
        {
            SCI_readCharArray(SCI_INST_BASE_ADDR, rxTempBuffer, 5);
        }
        else if(SCI_getRxFIFOStatus(SCI_INST_BASE_ADDR) == 0x4)
        {
            SCI_readCharArray(SCI_INST_BASE_ADDR, rxTempBuffer, 4);
        }
    }

    if(rxTempBuffer[0]==START_BYTE)
    {
        if(rxTempBuffer[1]==get_capabilities_cmd)
        {
            if(rxTempBuffer[2]==get_capability_cmd_length)
            {
                if(rxTempBuffer[3]==END_BYTE)
                {

                    get_capabilites_response();

                }
                else
                {
                    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, START_BYTE);
                    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, error);
                    msg = "Invalid end byte\n";
                    SCI_writeCharArray(SCI_INST_BASE_ADDR, (uint16_t*)msg, 17);
                    SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, END_BYTE);
                }
            }
            else
            {
                SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, START_BYTE);
                SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, error);
                msg = "Invalid length\n";
                SCI_writeCharArray(SCI_INST_BASE_ADDR, (uint16_t*)msg, 15);
                SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, END_BYTE);
            }
        }
        else if (rxTempBuffer[1]==list_sensors_cmd)
        {
            if(rxTempBuffer[2]==list_sensors_cmd_length)
            {
                if(rxTempBuffer[3]==END_BYTE)
                {

                    list_all_sensors();

                }
            }

        }
        else if (rxTempBuffer[1]==configure_pipeline_cmd)
        {
            if(rxTempBuffer[2]>=configure_pipeline_cmd_length)
            {
                if(rxTempBuffer[3]==Data_Acquisition)
                {
                    if((rxTempBuffer[5]==sensor_index1) || (rxTempBuffer[5]==sensor_index2) || (rxTempBuffer[5]==sensor_index3) || (rxTempBuffer[5]==sensor_index4))
                    {
                        if(rxTempBuffer[6]==END_BYTE)
                        {
                            first_sensor_index = rxTempBuffer[5];        // ID of 1st sensor in pipeline

                            configure_pipeline_response();

                        }
                        else if((rxTempBuffer[6]==sensor_index1) || (rxTempBuffer[6]==sensor_index2) || (rxTempBuffer[6]==sensor_index3) || (rxTempBuffer[6]==sensor_index4))
                        {
                            if(rxTempBuffer[7]==END_BYTE)
                            {
                                first_sensor_index = rxTempBuffer[5];        // ID of 1st sensor in pipeline
                                second_sensor_index = rxTempBuffer[6];       // ID of 2nd sensor in pipeline

                                configure_pipeline_response();

                            }
                            else if((rxTempBuffer[7]==sensor_index1) || (rxTempBuffer[7]==sensor_index2) || (rxTempBuffer[7]==sensor_index3) || (rxTempBuffer[7]==sensor_index4))
                            {
                                if(rxTempBuffer[8]==END_BYTE)
                                {
                                    first_sensor_index = rxTempBuffer[5];        // ID of 1st sensor in pipeline
                                    second_sensor_index = rxTempBuffer[6];       // ID of 2nd sensor in pipeline
                                    third_sensor_index = rxTempBuffer[7];        // ID of 3rd sensor in pipeline

                                    configure_pipeline_response();

                                }
                                else if((rxTempBuffer[8]==sensor_index1) || (rxTempBuffer[8]==sensor_index2) || (rxTempBuffer[8]==sensor_index3) || (rxTempBuffer[8]==sensor_index4))
                                {
                                    if(rxTempBuffer[9]==END_BYTE)
                                    {
                                        first_sensor_index = rxTempBuffer[5];        // ID of 1st sensor in pipeline
                                        second_sensor_index = rxTempBuffer[6];       // ID of 2nd sensor in pipeline
                                        third_sensor_index = rxTempBuffer[7];        // ID of 3rd sensor in pipeline
                                        forth_sensor_index = rxTempBuffer[8];        // ID of 3rd sensor in pipeline

                                        configure_pipeline_response();

                                    }
                                }
                            }
                        }
                    }
                }
                if(rxTempBuffer[3]==Sensor_Inferencing)
                {
                    if((rxTempBuffer[4]==model_index1) || (rxTempBuffer[4]==model_index2) || (rxTempBuffer[4]==model_index3))      //Assuming only model will be used at a time
                    {
                        if((rxTempBuffer[5]==sensor_index1) || (rxTempBuffer[5]==sensor_index2) || (rxTempBuffer[5]==sensor_index3) || (rxTempBuffer[5]==sensor_index4))
                        {
                            if(rxTempBuffer[6]==END_BYTE)
                            {
                                first_sensor_index = rxTempBuffer[5];        // ID of 1st sensor in pipeline

                                configure_pipeline_response();

                            }
                            else if ((rxTempBuffer[6]==sensor_index1) || (rxTempBuffer[6]==sensor_index2) || (rxTempBuffer[6]==sensor_index3) || (rxTempBuffer[6]==sensor_index4))
                            {
                                if(rxTempBuffer[7]==END_BYTE)
                                {
                                    first_sensor_index = rxTempBuffer[5];        // ID of 1st sensor in pipeline
                                    second_sensor_index = rxTempBuffer[6];       // ID of 2nd sensor in pipeline

                                    configure_pipeline_response();

                                }
                                else if((rxTempBuffer[7]==sensor_index1) || (rxTempBuffer[7]==sensor_index2) || (rxTempBuffer[7]==sensor_index3) || (rxTempBuffer[7]==sensor_index4))
                                {
                                    if(rxTempBuffer[8]==END_BYTE)
                                    {
                                        first_sensor_index = rxTempBuffer[5];        // ID of 1st sensor in pipeline
                                        second_sensor_index = rxTempBuffer[6];       // ID of 2nd sensor in pipeline
                                        third_sensor_index = rxTempBuffer[7];        // ID of 3rd sensor in pipeline

                                        configure_pipeline_response();

                                    }
                                    else if((rxTempBuffer[8]==sensor_index1) || (rxTempBuffer[8]==sensor_index2) || (rxTempBuffer[8]==sensor_index3) || (rxTempBuffer[8]==sensor_index4))
                                    {
                                        if(rxTempBuffer[9]==END_BYTE)
                                        {
                                            first_sensor_index = rxTempBuffer[5];        // ID of 1st sensor in pipeline
                                            second_sensor_index = rxTempBuffer[6];       // ID of 2nd sensor in pipeline
                                            third_sensor_index = rxTempBuffer[7];        // ID of 3rd sensor in pipeline
                                            forth_sensor_index = rxTempBuffer[8];         // ID of 4th sensor in pipeline

                                            configure_pipeline_response();

                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                if(rxTempBuffer[3]==Host_Inferencing)
                {
                    if((rxTempBuffer[4]==model_index1) || (rxTempBuffer[4]==model_index2) || (rxTempBuffer[4]==model_index3))      //Assuming only model will be used at a time
                    {
                        if(rxTempBuffer[5]==END_BYTE)
                        {
                            configure_pipeline_response();

                        }
                    }
                }
            }
        }

        else if (rxTempBuffer[1]==list_models_cmd)
        {
            if(rxTempBuffer[2]==list_models_cmd_length)
            {
                if(rxTempBuffer[3]==END_BYTE)
                {
                    list_all_models();
                }
            }

        }

        else if (rxTempBuffer[1]==start_streaming_cmd)
        {
            if(rxTempBuffer[2]==start_streaming_cmd_length)
            {
                if(rxTempBuffer[3]==END_BYTE)
                {

                    start_streaming_response();

                    //****Assumption:-Data has to be sent from target side after this****//
                }
            }

        }
        else if (rxTempBuffer[1]==stop_streaming_cmd)
        {
            if(rxTempBuffer[2]==stop_streaming_cmd_length)
            {
                if(rxTempBuffer[3]==END_BYTE)
                {

                    stop_streaming_response();

                    //****Assumption:-Data has to be stopped from target side after this****//
                }
            }

        }
        else if (rxTempBuffer[1]==read_property_cmd)
        {
            if(rxTempBuffer[2]==read_property_cmd_length)
            {
                if((rxTempBuffer[3]==property_index1) || (rxTempBuffer[3]==property_index2) || (rxTempBuffer[3]==property_index3) || (rxTempBuffer[3]==property_index4) || (rxTempBuffer[3]==property_index5) || (rxTempBuffer[3]==property_index6) || (rxTempBuffer[3]==property_index7) || (rxTempBuffer[3]==property_index8))
                {
                    if(rxTempBuffer[4]==END_BYTE)
                    {
                        index_of_property = rxTempBuffer[3];

                        if(PROPERTY_VAL_TYPE_UINT16==1)
                        {

                            property_read_response_uint16(index_of_property, test_property_uint16);
                        }
                        else if(PROPERTY_VAL_TYPE_UINT32==1)
                        {

                            property_read_response_uint32(index_of_property, test_property_uint32);
                        }
                    }
                }
            }
        }
        else if (rxTempBuffer[1]==write_property_cmd)
        {
            //if(rxTempBuffer[2]==write_property_cmd_length)
            if(rxTempBuffer[2]==3)       // For uint16 value
            {
                if((rxTempBuffer[3]==property_index1) || (rxTempBuffer[3]==property_index2) || (rxTempBuffer[3]==property_index3) || (rxTempBuffer[3]==property_index4) || (rxTempBuffer[3]==property_index5) || (rxTempBuffer[3]==property_index6) || (rxTempBuffer[3]==property_index7) || (rxTempBuffer[3]==property_index8))
                {
                    if(rxTempBuffer[6]==END_BYTE)
                    {
                        index_of_property = rxTempBuffer[3];
                        uint16_t byte1 = rxTempBuffer[4];
                        uint16_t byte2 = rxTempBuffer[5];
                        uint16_t property_value = ((byte1 << 8) | byte2);
                        test_property_uint16 = property_value;

                        property_written_response(index_of_property);
                    }
                }
            }
            else if(rxTempBuffer[2]==5)  // For uint32 value
            {
                if((rxTempBuffer[3]==property_index1) || (rxTempBuffer[3]==property_index2) || (rxTempBuffer[3]==property_index3) || (rxTempBuffer[3]==property_index4) || (rxTempBuffer[3]==property_index5) || (rxTempBuffer[3]==property_index6) || (rxTempBuffer[3]==property_index7) || (rxTempBuffer[3]==property_index8))
                {
                    if(rxTempBuffer[8]==END_BYTE)
                    {
                        index_of_property = rxTempBuffer[3];
                        uint32_t byte1 = rxTempBuffer[4];
                        uint32_t byte2 = rxTempBuffer[5];
                        uint32_t byte3 = rxTempBuffer[6];
                        uint32_t byte4 = rxTempBuffer[7];
                        uint32_t property_value = ((byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4);
                        test_property_uint32 = property_value;

                        property_written_response(index_of_property);
                    }
                }
            }
        }
        else if (rxTempBuffer[1]==list_properties_cmd)
        {
            if(rxTempBuffer[2]==list_properties_cmd_length)
            {
                if(rxTempBuffer[3]==END_BYTE)
                {
                    list_all_properties();
                }
            }
        }
        else if (rxTempBuffer[1]==list_inferencing_values_cmd)
        {
            if(rxTempBuffer[2]==list_properties_cmd_length)
            {
                if(rxTempBuffer[3]==END_BYTE)
                {
                    list_all_inferences();
                }
            }
        }
        else
        {
            /*
            SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, START_BYTE);
            SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, error);
            msg = "Invalid Command\n";
            SCI_writeCharArray(SCI_INST_BASE_ADDR, (uint16_t*)msg, 16);
            SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, END_BYTE);
            */
        }
    }
    else
    {
        /*
        SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, START_BYTE);
        SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, error);
        msg = "Invalid Start\n";
        SCI_writeCharArray(SCI_INST_BASE_ADDR, (uint16_t*)msg, 14);
        SCI_writeCharBlockingNonFIFO(SCI_INST_BASE_ADDR, END_BYTE);
        */
    }

    SCI_clearOverflowStatus(SCI_INST_BASE_ADDR);

    SCI_clearInterruptStatus(SCI_INST_BASE_ADDR, SCI_INT_RXFF);

    //
    // Issue PIE ack
    //
    Interrupt_clearACKGroup(SCI_RX_ACK);
}


