/*
 *  Created on: Aug 30, 2024
 */

//#############################################################################
//
// FILE:   protocol_packaging.h
//
//!
//! This contains core macro & enum definitions
//!
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

#ifndef PROTOCOL_PACKAGING_H_
#define PROTOCOL_PACKAGING_H_

#include "stdint.h"
#include "driverlib.h"
#include "device.h"
#include"string.h"
#include "dap_interface.h"


//*********SCI Defines*********//
#define START_BYTE 237                   // 0xed in hex = 237 in dec
#define END_BYTE 158                     // 0x9e in hex = 158 in dec
#define SCI_INST_BASE_ADDR SCIA_BASE
#define SCI_RX_ACK INTERRUPT_ACK_GROUP9


//TX SCI Defines
#define TX_FIFO_LEVEL SCI_FIFO_TX1

//RX SCI Defines
#define RX_FIFO_LEVEL SCI_FIFO_RX4





//*********Enumerations*********//
enum RES { //Responses to be sent by target or received from GUI and understood by target
    NO_UPDATE = 20, //not actual command, just default for nextTxCMD
    //bidirectional
    PACKET_ERROR = 0,
    //received commands
    Get_Capabilities = 1
};

enum command_cmd { //Commands sent by host to target MCU
    //reserved = 0x00,
    get_capabilities_cmd = 0x01,
    list_sensors_cmd = 0x02,
    configure_pipeline_cmd = 0x03,
    list_models_cmd = 0x04,
    remove_model_cmd = 0x05,
    start_of_model_upload_cmd = 0x06,
    end_of_model_upload_cmd = 0x07,
    start_streaming_cmd = 0x08,
    stop_streaming_cmd = 0x09,
    //sent_data_cmd = 0x0a,
    list_inferencing_values_cmd = 0x0a,
    //reserved = 0x0b,
    read_property_cmd = 0x0c,
    write_property_cmd = 0x0d,
    list_properties_cmd = 0x0e,
    //sent_data_cmd = 0x10,
};

enum response_cmd { //Responses to be sent by target or received from GUI and understood by target
    //bidirectional
    error = 0x00,
    //received commands
    get_capabilities = 0x01,
    list_sensors = 0x02,
    configure_pipeline = 0x03,
    list_models = 0x04,
    remove_model = 0x05,
    start_of_model_upload = 0x06,
    end_of_model_upload = 0x07,
    start_streaming = 0x08,
    stop_streaming = 0x09,
    //reserved = 0x0a,
    list_inferencing_values = 0x0a,
    //received_data = 0x0b,
    property_read = 0x0c,
    property_written = 0x0d,
    list_properties = 0x0e,
    //received_data = 0x10
};

enum payload_length {
    error_length = 0x03,                    //check
    get_capability_cmd_length = 0x00,           //check
    //get_capability_length = 0x05,           //check
    get_capability_length = 0x0b,             // "Device_name" + 4 = 7 + 4 = 11
    list_sensors_cmd_length = 0x00,             //check
    //list_sensors_length = 0x03,             //check
    configure_pipeline_cmd_length = 0x02,
    configure_pipeline_length = 0x00,
    list_models_cmd_length = 0x00,
    //list_models_length = 0x03,              //check
    list_models_length = 0x03,
    remove_model_length = 0x00,
    start_of_model_upload_length = 0x00,
    end_of_model_upload_length = 0x00,
    start_streaming_cmd_length = 0x00,
    start_streaming_length = 0x00,
    stop_streaming_cmd_length = 0x00,
    stop_streaming_length = 0x00,
    reserved_length = 0x00,
    //received_data_length = 0x02,            //check
    read_property_cmd_length = 0x01,
    write_property_cmd_length = 0x04,
    property_read_length = 0x05,
    property_written_length = 0x01,
    list_properties_cmd_length = 0x00,
    list_properties_length = 0x0e           //check

};

enum error_payload_comp { //Response payload components
    command = 0x01,              //dummy
    error_number = 0x0f,      //dummy
    error_meassage = 0x37     //dummy (Optional now)
};

enum get_capabilities_payload_comp { //Response payload components
    API_version = 0x01,
    capability_bits_flag = 0x0f,      //0-2 bits:-reserved=000, 3rd bit:-crc checksum=0, 4th bit:-bi-directional=1(enabled), 5th bit:-big endian=1(yes, else little endian), 6th bit:- upload=1(enabled), 7th bit:-inference=1(enabled)
    sdk_major_version = 0x05,         // sdk_major_version = 5
    sdk_minor_version = 0x04         // sdk_minor_version = 4
};

enum list_sensor_payload_comp { //Response payload components
    //sensor_count = 0x04,              //dummy
    //sensor_count = 0x05,              //dummy
    sensor_index1 = 0x00,           //dummy
    sensor_index2 = 0x01,           //dummy
    sensor_index3 = 0x02,           //dummy
    sensor_index4 = 0x03,           //dummy
    sensor_index5 = 0x04,           //dummy
    sensor1_info = 0x37,      //dummy (Optional now)
    sensor2_info = 0x37,      //dummy (Optional now)
    sensor3_info = 0x37,      //dummy (Optional now)
    sensor4_info = 0x37,      //dummy (Optional now)
};


enum configure_pipeline_cmd_payload_mode { //Response payload components
    Data_Acquisition = 0x01,
    Sensor_Inferencing = 0x02,
    Host_Inferencing = 0x03,
    Loopback = 0x04
};


enum list_models_payload_comp { //Response payload components
    //model_count = 0x03,              //dummy
    model_index1 = 0x00,
    model_index2 = 0x01,
    model_index3 = 0x02
    //model_descriptor = 0x37      //dummy
};

enum remove_model_payload_comp { //Response payload components
    remove_model_index = 0x01,              //dummy
};

//enum start_of_model_payload_comp { //Response payload components
    //remove_model_index = 0x01,              //dummy
//};

//enum end_of_model_upload_payload_comp { //Response payload components
    //remove_model_index = 0x01,              //dummy
//};

//enum start_streaming_payload_comp { //Response payload components
    //remove_model_index = 0x01,              //dummy
//};

//enum stop_streaming_payload_comp { //Response payload components
    //remove_model_index = 0x01,              //dummy
//};



enum list_properiess_payload_comp { //Response payload components
    //property_count = 0x01,              //dummy
    property_index1 = 0x00,
    property_index2 = 0x01,
    property_index3 = 0x02,
    property_index4 = 0x03,
    property_index5 = 0x04,
    property_index6 = 0x05,
    property_index7 = 0x06,
    property_index8 = 0x07,
    property_dataformat1 = 0x01,        //data format: Int8
    property_dataformat2 = 0x02,        //data format: Int16
    property_dataformat3 = 0x03,        //data format: Int32
    property_dataformat4 = 0x04,        //data format: Uint8
    property_dataformat5 = 0x05,        //data format: Uint16
    property_dataformat6 = 0x06,        //data format: Uint32
    property_dataformat7 = 0x07,        //data format: Float16
    property_dataformat8 = 0x08,        //data format: Float32
    property_dataformat9 = 0x09,        //data format: Float64
    //model_descriptor = 0x37      //dummy
};

enum list_inferences_payload_comp { //Response payload components
    //property_count = 0x01,              //dummy
    inference_index1 = 0x00,
    inference_index2 = 0x01,
    inference_index3 = 0x02,
    inference_index4 = 0x03,
    inference_index5 = 0x04,
    inference_index6 = 0x05,
    inference_index7 = 0x06,
    inference_index8 = 0x07,
    //property_index2 = 0x01,
    inference_dataformat1 = 0x01,        //data format: Int8
    inference_dataformat2 = 0x02,        //data format: Int16
    inference_dataformat3 = 0x03,        //data format: Int32
    inference_dataformat4 = 0x04,        //data format: Uint8
    inference_dataformat5 = 0x05,        //data format: Uint16
    inference_dataformat6 = 0x06,        //data format: Uint32
    inference_dataformat7 = 0x07,        //data format: Float16
    inference_dataformat8 = 0x08,        //data format: Float32
    inference_dataformat9 = 0x09,        //data format: Float64
    //model_descriptor = 0x37      //dummy
};

//Function Prototypes
//void SCI_writeCharArrayFixed(uint32_t base, const uint16_t * const array, uint16_t length);
//void SCI_writeConstVal(uint32_t base, const uint16_t val, uint16_t length);
//void payload_formation(void);


#endif /* PROTOCOL_PACKAGING_H_ */
