//#############################################################################
//
// FILE:   hic_ex3_DataWidth16bit_fsi.c
//
// TITLE:  Host Interface Controller 16 bit Data Width FSI Bridge Example
//
//! \addtogroup driver_example_list
//! <h1>HIC 16-bit Memory Access FSI Example</h1>
//!
//! Example sets up Host Interface Controller Module in 16-bit mode
//! the FSI Memory region of device is accessed by the
//! External Host.
//! This follows example configuration for performance critical applications
//! described in the Application note titled "Application guide for peripheral
//! expansion using HIC"(SPRACR2).
//!
//! emif_ex7_16bit_asram_hic_fsi is to be run on the host before running this
//! example on F28003x side.
//!
//! This example is validated on an TI Internal Validation Platform
//! will not run in F28003x Control Card
//! 1. The example initializes the GPIOs for 16 bit HIC Memory access mode
//! with separate Read and Write Control Pins, Extended Wait, and nRDY pin
//! 2. Configures the base address for Region 0 to access FSI Tx Memory region
//! 3. Sets up the FSI module in Loopback mode
//! 4. The EVTTRIG interface of HIC is enabled to route FSI
//! Rx events to the Host through the HIC_INT
//! 5. Sending a message to the Host using Device to Host buffer,Passing a token
//! 6. This sets up the FSI direct bridge over HIC.
//! The host can then access the FSI registers over HIC
//!
//!
//!\b External \b Connections \n
//!   This is tested on TI Internal validation platform hence
//! no connection needed on Control card. This has been tested with F2838x EMIF
//! interface.
//!
//! \b Watch \b Variables \n
//!     None - Use the Host to access FSI region
//!
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com/
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
#include "device.h"
#include "driverlib.h"
#include "hic.h"

#define PRESCALER_VAL           FSI_PRESCALE_60MHZ
#define HIC_INIT_DONE_TOKEN     0xFAU
#define HIC_START_TOKEN         0xFBU
#define HIC_BASE_TOKEN          0xFCU

//
//Function Prototypes
//
void initFSI(void);
void initGPIOHIC(void);

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
    // Initialize GPIO and configure the GPIO pin as a push-pull output
    //
    Device_initGPIO();

    initGPIOHIC();

    HIC_enableHostInterface();

    //
    //Set HIC Configuration
    //16 Bit mode with Separate
    //Read and Write Enable pins
    //with Ready pin
    //H2D Buffer writable by Device
    //D2H buffer writable by host
    //
    HIC_setConfig(HIC_MODE_DW_16BIT |
                   HIC_MODE_RW_PIN_SEPARATE |
                   HIC_MODE_RDY_PRESENT |
                   HIC_MODE_H2DBUF_DEVWREN |
                   HIC_MODE_D2HBUF_HOST_WR_ENABLE |
                   HIC_MODE_DEVICE_HOST_ACCESS_ENABLE |
                   HIC_MODE_HOST_WREALLOW_ENABLE
                  );

    //
    //Enable EALLOW access from Host, with Page selection through BASESEL Pins
    //
    HIC_configureHostAccessMode(HIC_HOST_CONTROL_EALLOW_EN|HIC_HOST_CONTROL_PAGESEL_PIN);

    //
    //Initialize the FSI module for internal loopback
    //
    initFSI();

    //
    //Enable Host to be interrupted on FSI Rx interrupt
    //Bit 0 of Event trigger bus is FSI Rx interrupt
    //Refer Device Technical Reference manual for details
    //
    HIC_enableD2HInterrupt(HIC_EVTTRIG_EVENT_0);

    //
    //Region 0 is configured for FSI TX region access
    //Entire Tx and Rx region of FSI can be done with a
    //Single region in 16 bit mode of HIC
    //
    HIC_setBaseAddress(0,FSITXA_BASE);


    //
    //Flag to the host by writing to the Token
    //This will generate a D2H interrupt
    //
    HIC_setD2HToken(HIC_INIT_DONE_TOKEN);


    //
    //Now the Host side can read and write to the FSI memory region
    //
    ESTOP0;
}

void initGPIOHIC(void)
{
    //
    //This routine does PinMux for 16 Bit configuration
    //of HIC module.These are for a TI Internal Board
    //

    //
    //For Chip Select Pin
    //
    GPIO_setPinConfig(GPIO_29_HIC_NCS);
    GPIO_setQualificationMode(29,GPIO_QUAL_ASYNC);

    //
    //For Base Select Pins
    //
    GPIO_setPinConfig(GPIO_232_HIC_BASESEL0);
    GPIO_setQualificationMode(232,GPIO_QUAL_ASYNC);
    GPIO_setAnalogMode(232, GPIO_ANALOG_DISABLED);
    //
    //HINT Pin
    //
    GPIO_setPinConfig(GPIO_32_HIC_INT);

    //
    //Output Enable
    //
    GPIO_setPinConfig(GPIO_28_HIC_NOE);
    GPIO_setQualificationMode(28,GPIO_QUAL_ASYNC);

    //
    //Write Enable pin
    //
    GPIO_setPinConfig(GPIO_225_HIC_NWE);
    GPIO_setQualificationMode(225,GPIO_QUAL_ASYNC);
    GPIO_setAnalogMode(225, GPIO_ANALOG_DISABLED);

    //
    //Byte Enables
    //
    GPIO_setPinConfig(GPIO_227_HIC_NBE0);
    GPIO_setPinConfig(GPIO_241_HIC_NBE1);
    GPIO_setQualificationMode(227,GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(241,GPIO_QUAL_ASYNC);
    GPIO_setAnalogMode(227, GPIO_ANALOG_DISABLED);
    GPIO_setAnalogMode(241, GPIO_ANALOG_DISABLED);

    //
    //Ready Pin
    //
    GPIO_setPinConfig(GPIO_9_HIC_NRDY);
    GPIO_setQualificationMode(9,GPIO_QUAL_ASYNC);

    //
    //HIC Data Pins
    //
    GPIO_setPinConfig(GPIO_33_HIC_D0);
    GPIO_setPinConfig(GPIO_16_HIC_D1);
    GPIO_setPinConfig(GPIO_17_HIC_D2);
    GPIO_setPinConfig(GPIO_24_HIC_D3);
    GPIO_setPinConfig(GPIO_5_HIC_D4);
    GPIO_setPinConfig(GPIO_44_HIC_D5);
    GPIO_setPinConfig(GPIO_45_HIC_D6);
    GPIO_setPinConfig(GPIO_39_HIC_D7);
    GPIO_setPinConfig(GPIO_8_HIC_D8);
    GPIO_setPinConfig(GPIO_34_HIC_D9);
    GPIO_setPinConfig(GPIO_1_HIC_D10);
    GPIO_setPinConfig(GPIO_23_HIC_D11);
    GPIO_setPinConfig(GPIO_15_HIC_D12);
    GPIO_setPinConfig(GPIO_22_HIC_D13);
    GPIO_setPinConfig(GPIO_7_HIC_D14);
    GPIO_setPinConfig(GPIO_14_HIC_D15);
    GPIO_setQualificationMode(33,GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(16,GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(17,GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(24,GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(5,GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(44,GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(45,GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(39,GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(8,GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(34,GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(1,GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(23,GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(15,GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(22,GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(7,GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(14,GPIO_QUAL_ASYNC);

    //
    //HIC Address Pins
    //
    GPIO_setPinConfig(GPIO_228_HIC_A0);
    GPIO_setPinConfig(GPIO_226_HIC_A1);
    GPIO_setPinConfig(GPIO_242_HIC_A2);
    GPIO_setPinConfig(GPIO_224_HIC_A3);
    GPIO_setPinConfig(GPIO_233_HIC_A4);
    GPIO_setPinConfig(GPIO_239_HIC_A5);
    GPIO_setPinConfig(GPIO_237_HIC_A6);
    GPIO_setPinConfig(GPIO_244_HIC_A7);
    GPIO_setQualificationMode(228,GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(226,GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(242,GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(224,GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(233,GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(239,GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(237,GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(244,GPIO_QUAL_ASYNC);
    GPIO_setAnalogMode(228, GPIO_ANALOG_DISABLED);
    GPIO_setAnalogMode(226, GPIO_ANALOG_DISABLED);
    GPIO_setAnalogMode(242, GPIO_ANALOG_DISABLED);
    GPIO_setAnalogMode(224, GPIO_ANALOG_DISABLED);
    GPIO_setAnalogMode(233, GPIO_ANALOG_DISABLED);
    GPIO_setAnalogMode(239, GPIO_ANALOG_DISABLED);
    GPIO_setAnalogMode(237, GPIO_ANALOG_DISABLED);
    GPIO_setAnalogMode(244, GPIO_ANALOG_DISABLED);
}
//
// initFSI - Initializes FSI Tx/Rx for loopback and also sends FLUSH
//           sequence.
//
void initFSI(void)
{
    // Tx Ping timer and Rx Watchdog reference counter values
    uint32_t txPingTimeRefCntr = 0x10000, rxWdTimeoutRefCntr = 0x14000;
    // Frame tag used with Data/Ping transfers
    FSI_FrameTag txDataFrameTag = FSI_FRAME_TAG10;
    FSI_FrameTag txPingFrameTag = FSI_FRAME_TAG15;
    //
    // Number of words per transfer may be from 1 -16
    uint16_t nWords = 6;
    // Transfer can be happen over single or double lane
    FSI_DataWidth nLanes = FSI_DATA_WIDTH_1_LANE;
    // User data to be sent with Data frame
    uint16_t txUserData = 0x47;
    //
    // This value can be anything suitable to generate a single interrupt event,
    // lower values may lead WD to trigger another event even before handler of 1st
    // one is not completed
    //
    uint32_t rxFrameWdRefCntr = 0x1000000;
    uint16_t i;

    //
    // Set internalLoopback mode
    //
    FSI_enableRxInternalLoopback(FSIRXA_BASE);


    //
    // Initialize Tx/Rx, reset sequence, clear events
    //
    FSI_performTxInitialization(FSITXA_BASE, PRESCALER_VAL);
    FSI_performRxInitialization(FSIRXA_BASE);

    //
    // Flush Sequence before and after releasing Rx core reset, ensures flushing
    // of Rx data/clock lines and prepares it for reception
    //
    FSI_resetRxModule(FSIRXA_BASE, FSI_RX_MASTER_CORE_RESET);
    FSI_executeTxFlushSequence(FSITXA_BASE, PRESCALER_VAL);
    DEVICE_DELAY_US(1);
    FSI_clearRxModuleReset(FSIRXA_BASE, FSI_RX_MASTER_CORE_RESET);
    FSI_executeTxFlushSequence(FSITXA_BASE, PRESCALER_VAL);


    //
    // First setup Ping transfer and then Data
    //

    //
    // Performing a reset on PING WD counter before its usage is recommended
    // Done on both FSI Tx/Rx sides
    //
    FSI_resetTxModule(FSITXA_BASE, FSI_TX_PING_TIMEOUT_CNT_RESET);
    DEVICE_DELAY_US(1);
    FSI_clearTxModuleReset(FSITXA_BASE, FSI_TX_PING_TIMEOUT_CNT_RESET);

    FSI_resetRxModule(FSIRXA_BASE, FSI_RX_PING_WD_CNT_RESET);
    DEVICE_DELAY_US(1);
    FSI_clearRxModuleReset(FSIRXA_BASE, FSI_RX_PING_WD_CNT_RESET);

    //
    // Enable Rx Ping Watchdog timeout event on INT2 line
    //
    FSI_enableRxInterrupt(FSIRXA_BASE, FSI_INT2, FSI_RX_EVT_PING_WD_TIMEOUT);

    //
    // Now enable PING WD timer in both FSI Tx/Rx sides
    // Keeping reference counter for Rx little wide to ensure its not too sharp
    // to generate a WD timeout
    //
    FSI_enableTxPingTimer(FSITXA_BASE, txPingTimeRefCntr, txPingFrameTag);
    FSI_enableRxPingWatchdog(FSIRXA_BASE, rxWdTimeoutRefCntr);

    //
    // Automatic Ping transmission is setup, now configure for data transfers
    //

    //
    // Setting for requested nWords and nLanes with transfers
    //
    FSI_setTxSoftwareFrameSize(FSITXA_BASE, nWords);
    FSI_setRxSoftwareFrameSize(FSIRXA_BASE, nWords);
    FSI_setTxDataWidth(FSITXA_BASE, nLanes);
    FSI_setRxDataWidth(FSIRXA_BASE, nLanes);

    //
    // Enable normal data transfer events to be sent over INT1 line
    //
    FSI_enableTxInterrupt(FSITXA_BASE, FSI_INT1, FSI_TX_EVT_FRAME_DONE);
    FSI_enableRxInterrupt(FSIRXA_BASE, FSI_INT1, FSI_RX_EVT_DATA_FRAME );

    //
    // Enable transmit/receive error events to be sent over INT2 line
    // Overrun and Underrun conditions in Rx are not enabled as buffer pointers
    // are always overwritten to first location for sending data frames.
    //
    FSI_enableRxInterrupt(FSIRXA_BASE, FSI_INT2, FSI_RX_EVT_CRC_ERR  |
                                                 FSI_RX_EVT_EOF_ERR  |
                                                 FSI_RX_EVT_TYPE_ERR);
    FSI_setTxUserDefinedData(FSITXA_BASE, txUserData);
    FSI_setTxFrameTag(FSITXA_BASE, txDataFrameTag);
    FSI_setTxFrameType(FSITXA_BASE, FSI_FRAME_TYPE_NWORD_DATA);

    //
    // Performing a reset on frame WD before its usage is recommended
    //
    FSI_resetRxModule(FSIRXA_BASE, FSI_RX_FRAME_WD_CNT_RESET);
    DEVICE_DELAY_US(1);
    FSI_clearRxModuleReset(FSIRXA_BASE, FSI_RX_FRAME_WD_CNT_RESET);

    FSI_enableRxInterrupt(FSIRXA_BASE, FSI_INT2,
                        FSI_RX_EVT_FRAME_WD_TIMEOUT);
    FSI_enableRxFrameWatchdog(FSIRXA_BASE, rxFrameWdRefCntr);
}
//
// End of File
//
