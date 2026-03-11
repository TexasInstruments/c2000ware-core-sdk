/*
 *  Created on: Aug 30, 2024
 */
//#############################################################################
//
// FILE:   dap_interface.h
//
//!
//! This contains function prototyping of top level user accessible APIs and
//! user define macros
//
//#############################################################################
//
//
// $Copyright:  $
//#############################################################################

#ifndef USER_INTERFACE_H_
#define USER_INTERFACE_H_

//Whether to debug in the terminal (1) or in the GC application (0)
//#define TERMINAL_DEBUGGING_MODE 1
#define TERMINAL_DEBUGGING_MODE 0

#define SCI_BAUD_RATE 2343750         // 37.5Mhz/16
//#define SCI_BAUD_RATE 9375000         // 37.5Mhz/16 *4
//#define SCI_BAUD_RATE 4687500         // 37.5Mhz/16 *2

#define PROPERTY_VAL_TYPE_UINT16    1   //default value is 1
#define PROPERTY_VAL_TYPE_UINT32    0   //default value is 0

enum receive_data_reponse_payload_channel_value_comp { //Response payload components
    sensor_signal = 0x01,
    inferencing_signal = 0x03,
    inferencing_result = 0x04,
    inferencing_value = 0x05,
    inferencing_log = 0x06
};

/***********Main Functions************/
void guiInitialization();
void received_data_response(uint32_t data_payload_length, uint16_t channel_value, uint16_t* data_array);
void data_conversion_from_16_to_8_bits(uint16_t* input_buf, int input_buf_size, uint8_t* output_buf);
void data_conversion_from_32_to_8_bits(uint32_t* input_buf, int input_buf_size, uint8_t* output_buf);
void sci_write_char_array(uint16_t* msg, int len);


/***********Other Functions************/
void list_all_sensors();
void list_all_models();
void list_all_properties();
void list_all_inferences();

#endif /* USER_INTERFACE_H_ */
