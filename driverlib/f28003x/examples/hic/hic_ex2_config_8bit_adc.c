//#############################################################################
//
// FILE:   hic_ex2_config_8bit_adc.c
//
// TITLE:  Host Interface Controller 8 bit Data Width Access
//
//! \addtogroup driver_example_list
//! <h1>HIC 8-bit Memory Access Example</h1>
//!
//! Example sets up Host Interface Controller Module in 8-bit mode
//! the data memory of device is accessed by the External Host.
//!
//! - This follows example configuration for pin constrained applications
//! described in the Application note titled Application guide for peripheral 
//! expansion using HIC(SPRACR2).
//! -This example is validated on an TI Internal Validation Platform
//! will not run in F28002x Control Card.
//! This is to be run with a corresponding Host side code
//! emif_ex8_8bit_asram_hic_adc is run on F2838x based host first
//! and then this example is run.
//! - The example initializes the HIC for 8 bit Memory access mode
//! with Single Read and Write Control Pin
//! - DMA is configured to do transfer of the ADC result from ADCRESULT0-15 to
//! HIC D2H buffer.
//! - The example configures
//! CPUTIMER0 to generate an event every second on which the ADC SOC0-15
//! start conversion. 
//! - The timer is enabled on receiving HIC_START_TOKEN
//! on the H2D Token from the host.
//! - The end of ADC_SOC15 will generate a DMA event
//! -  The DMA ISR signals the host with HIC_DATA_TOKEN to
//! signal data write.
//! - The Host is interrupted with HIC_INT on ADC End of conversion event
//! - The DMA Channel is stopped after HIC_TEST_NUM_SAMPLES samples are
//! collected
//! This example can be used as a reference to implement Communication
//! between Host and HIC with minimal number of pins.
//! Please refer to device TRM and application note titled 'Application guide
//! for peripheral expansion using HIC'(SPRACR2) for further details
//! about Host interface Controller applications.
//!
//!\b External \b Connections \n
//!   This is tested on TI Internal validation platform hence no connection
//!  needed on Control card. This has been tested with F2838x EMIF
//! interface with emif_ex8_8bit_asram_hic_adc example
//! Analog channel A7 has been used as Analog Input to Sample
//!
//! \b Watch \b Variables \n
//!     numDMAInterrupts
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

//
//Function Prototypes
//
void initGPIOHIC(void);
void initADC(void);
void initADCSOC(void);
void initDMA(void);
void configCPUTimer(uint32_t, uint32_t);

//
//Interrupt Handlers
//
__interrupt void dmaCh6ISR(void);
__interrupt void hicISR(void);

//
//Global Defines
//
#define HIC_INIT_DONE_TOKEN     0xFAU
#define HIC_START_TOKEN         0xFBU
#define HIC_DATA_TOKEN          0xFCU
#define HIC_TEST_NUM_SAMPLES    100U

//
//Global Variables
//

uint16_t   hicISRCount = 0;
volatile uint16_t startReceived = 0;
volatile uint16_t numDMAInterrupts = 0;

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
    //Do HIC GPIO Initialization
    //
    initGPIOHIC();

    //
    //Configure ADC and ADC SOC
    //
    initADC();
    initADCSOC();

    //
    //Configure CPU Timer 0 for 1 second interrupt
    //
    configCPUTimer(CPUTIMER0_BASE, 1000000);

    //
    //Initialize DMA for this use case
    //
    initDMA();


    //
    //Initialize and Enable interrupt for DMA Channel
    //
    Interrupt_register(INT_DMA_CH6, &dmaCh6ISR);
    Interrupt_enable(INT_DMA_CH6);

    //
    //Initialize interrupts for HIC
    //
    Interrupt_register(INT_HICA, &hicISR);
    Interrupt_enable(INT_HICA);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;


    HIC_enableHostInterface();

    //
    //Set HIC Configuration
    //8 Bit mode with Separate
    //Read and Write Enable pins
    //with Ready pin
    //H2D Buffer writable by Device
    //D2H buffer writable by host
    //Device memory access is not accessible to Host
    //
    HIC_setConfig(HIC_MODE_DW_8BIT |
                   HIC_MODE_RW_PIN_SINGLE |
                   HIC_MODE_H2DBUF_DEVWREN |
                   HIC_MODE_D2HBUF_HOST_WR_ENABLE |
                   HIC_MODE_HOST_WREALLOW_ENABLE
                  );

    //
    //Enable HIC_INT for D2H Data ready event
    //
    HIC_enableD2HInterrupt(HIC_D2HINTEN_D2H_INTEN);

    //
    //Enable Interrupt for Host to Device Data ready
    //
    HIC_enableH2DInterrupt(HIC_H2DINTEN_H2D_INTEN);



    //
    //Flag to the host by writing to the Token
    //This will generate a D2H interrupt
    //
    HIC_setD2HToken(HIC_INIT_DONE_TOKEN);

    //
    //Wait for Message from Host Containing the Base address
    //to be configured
    //
    while(0U == startReceived);

    //
    //Start the timer which will trigger the ADC sampling
    //The completion of ADC sampling will trigger DMA event
    //The DMA interrupt handler will then notify the host
    //
    CPUTimer_startTimer(CPUTIMER0_BASE);


    //
    //Now the Host side will be interrupted for each ADC result message
    //
    while(numDMAInterrupts != HIC_TEST_NUM_SAMPLES)
    {
    }

    //
    //Halt the execution here after HIC_TEST_NUM_SAMPLES of data
    //
    ESTOP0;
}
void
configCPUTimer(uint32_t cpuTimer, uint32_t period)
{
    uint32_t temp, freq = DEVICE_SYSCLK_FREQ;

    //
    // Initialize pre-scale counter to divide by 1 (SYSCLKOUT)
    //
    CPUTimer_setPreScaler(CPUTIMER0_BASE, 0);

    //
    // Make sure timer is stopped
    //
    CPUTimer_stopTimer(CPUTIMER0_BASE);

    //
    // Reload all counter register with period value
    //
    CPUTimer_reloadTimerCounter(CPUTIMER0_BASE);

    //
    // Initialize timer period:
    //
    temp = ((freq / 1000000U) * period);
    CPUTimer_setPeriod(cpuTimer, temp - 1);

    //
    // Set pre-scale counter to divide by 1 (SYSCLKOUT):
    //
    CPUTimer_setPreScaler(cpuTimer, 0);

    //
    // Initializes timer control register. The timer is stopped, reloaded,
    // free run disabled, and interrupt enabled.
    // Additionally, the free and soft bits are set
    //
    CPUTimer_stopTimer(cpuTimer);
    CPUTimer_reloadTimerCounter(cpuTimer);
    CPUTimer_setEmulationMode(cpuTimer,
                              CPUTIMER_EMULATIONMODE_STOPAFTERNEXTDECREMENT);
    CPUTimer_enableInterrupt(cpuTimer);
}

//
// This function initializes the GPIOs for
// HIC module in 8 bit mode
//
void initGPIOHIC(void)
{
    //
    //This routine does PinMux for 8 Bit configuration
    //of HIC module.These are for a TI Internal Board
    //

    //
    //For Chip Select Pin
    //
    GPIO_setPinConfig(GPIO_29_HIC_NCS);
    GPIO_setQualificationMode(29,GPIO_QUAL_ASYNC);

    //
    //Output Enable
    //
    GPIO_setPinConfig(GPIO_28_HIC_NOE);
    GPIO_setQualificationMode(28,GPIO_QUAL_ASYNC);


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
    GPIO_setQualificationMode(33,GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(16,GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(17,GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(24,GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(5,GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(44,GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(45,GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(39,GPIO_QUAL_ASYNC);

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

    //
    //HIC_INT Pin
    //
    GPIO_setPinConfig(GPIO_32_HIC_INT);
}

//
// initADC - Function to configure and power up ADCA.
//
void initADC(void)
{
    //
    // Setup VREF as internal
    //
    ADC_setVREF(ADCA_BASE, ADC_REFERENCE_INTERNAL, ADC_REFERENCE_3_3V);

    //
    // Set ADCCLK divider to /4
    //
    ADC_setPrescaler(ADCA_BASE, ADC_CLK_DIV_4_0);

    //
    // Set pulse positions to late
    //
    ADC_setInterruptPulseMode(ADCA_BASE, ADC_PULSE_END_OF_CONV);


    //
    // Power up the ADC and then delay for 1 ms
    //
    ADC_enableConverter(ADCA_BASE);
    DEVICE_DELAY_US(1000);
}

//
// initADCSOCs - Function to configure SOC
//
void initADCSOC(void)
{
    uint16_t i;
    //
    // Configure SOCs of ADCA
    // - SOC0-15 will convert pin A7 with a sample window of 15 SYSCLK cycles.
    //
    for(i = 0; i < 16; i++)
   {
        ADC_setupSOC(ADCA_BASE, (ADC_SOCNumber)i, ADC_TRIGGER_CPU1_TINT0,
                      ADC_CH_ADCIN7, 15);
   }

    //
    // Set SOC15 to set the interrupt 1 flag. Enable the interrupt and make
    // sure its flag is cleared.
    //
    ADC_setInterruptSource(ADCA_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER15);
    ADC_enableInterrupt(ADCA_BASE, ADC_INT_NUMBER1);
    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);
    //
    // Enable continuous mode
    //
    ADC_enableContinuousMode(ADCA_BASE, ADC_INT_NUMBER1);
}

//
// DMA setup
//
void initDMA(void)
{
    //
    // Initialize DMA
    //
    DMA_initController();


    //
    // Configure DMA Ch6
    // Copy ADC Result(s) to HIC D2H Buffer
    //
    DMA_configAddresses(DMA_CH6_BASE, (uint16_t *) (HIC_BASE + HIC_O_D2H_BUF0),
                        (uint16_t *)(ADCARESULT_BASE));
    //
    //Configure the 16 SOC Results of ADC
    //Each D2H buffer is of size 32 bits
    //Hence destination step size is 2
    //Source is 16 bit wide hence step size is 1
    //
    DMA_configBurst(DMA_CH6_BASE, 16, 1, 2);

    //
    //At the end of each burst adjust Offset to point to first
    //locations of ADCRESULT0 and HIC D2H Buffer
    //
    DMA_configTransfer(DMA_CH6_BASE, 1, -15, -30);

    //
    //Configure Continuous mode to enable the channel after each transfer
    //
    DMA_configMode(DMA_CH6_BASE, DMA_TRIGGER_ADCA1, DMA_CFG_ONESHOT_DISABLE |
                   DMA_CFG_CONTINUOUS_ENABLE | DMA_CFG_SIZE_16BIT);
    DMA_disableOverrunInterrupt(DMA_CH1_BASE);

    //
    // Configure DMA Ch6 interrupts
    //
    DMA_setInterruptMode(DMA_CH6_BASE, DMA_INT_AT_END);
    DMA_enableInterrupt(DMA_CH6_BASE);
    DMA_enableTrigger(DMA_CH6_BASE);

    //
    // Start the DMA channels
    //
    DMA_startChannel(DMA_CH6_BASE);
}

//
// DMA Channel 6 ISR
//
 __interrupt void dmaCh6ISR(void)
{
     numDMAInterrupts++;

     if(HIC_TEST_NUM_SAMPLES == numDMAInterrupts)
     {
        //
        //Stop the DMA Channel and Timer after required
        //number of samples/iterations
        //
        DMA_stopChannel(DMA_CH6_BASE);
        CPUTimer_stopTimer(CPUTIMER0_BASE);
     }

    //
    //Clear the ADC interrupt Status
    //
    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);

    //
    //Flag to the host by writing to the Token
    //This will generate a D2H interrupt
    //
    HIC_setD2HToken(HIC_DATA_TOKEN);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);

}

//
//HIC ISR
//
__interrupt void hicISR(void)
{
    hicISRCount++;
    if(HIC_getH2DInterruptStatus() == HIC_H2DINTFLG_H2D_FLG)
    {
        if(HIC_getH2DToken() == HIC_START_TOKEN)
            startReceived = 1;
        HIC_clearH2DInterrupt(HIC_H2DINTFLG_H2D_FLG);
    }
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
}
//
// End of File
//
