//#############################################################################
//
// FILE:   emif_ex8_8bit_asram_hic_adc.c
//
// TITLE:  EMIF1 ASYNC module accessing 8bit ASRAM based HIC
//
//! \addtogroup driver_example_list
//! <h1> EMIF1 ASYNC module accessing 8bit HIC controller. </h1>
//!
//! This can be run with hic_ex2_config_8bit example on F28002x device.
//! This is run first followed by the run of F28002x device.
//! This example configures EMIF1 in 8 bit ASYNC mode and uses CS2 as chip
//! enable to access Host Interface controller on F28002X device
//! It uses Select Strobe mode of EMIF Controller.
//!
//! This follows example configuration for pin constrained applications
//! described in the Application note titled Application guide for peripheral 
//! expansion using HIC(SPRACR2).
//! - This uses 8 bit ASRAM with control signals as explained in the note.
//! uses the Mailbox access mode of Host interface Controller
//! - This sets up the EMIF waits for HIC_INIT_DONE_TOKEN from device
//! - sends HIC_START_TOKEN to the device to signal the device 
//! to start sampling the Analog channels 
//! - The device sends periodic HIC_DATA_TOKEN token 
//! - The samples are available in the HIC D2H Buffer
//! - Uses the HIC_INT interrupt from device(which is mapped to GPIO4, XINT1)
//! Refer F28002X device TRM for further details on HIC.
//!
//! \b External \b Connections \n
//!  - This example will not work on F2838x Control Card and has been tested
//! in TI Internal Validation platform.
//!
//! \b Watch \b Variables \n
//! - \b sampleCount - Number of samples of data received from device.
//! - \b xint1Count - Number interrupts received from device.
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
#include "device.h"
#include "driverlib.h"
#include "inc/hw_hic.h"

//
// Defines
//
#define ASRAM_CS2_START_ADDR    0x100000U
#define ASRAM_CS2_SIZE          0x8000U
#define CS2_BASE_ADDR           0x00100000U
#define HIC_HOST_BASE           CS2_BASE_ADDR


#define HIC_D2HINTFLG_D2H_FLG     0x1U         // Device to Host Data Ready
                                               // Flag
//
//Defines for EMIF Timings and HIC
//
#define WAIT_POLAR_INV              0
#define WAIT_COUNT                  16

#define TURN_AROUND_TIME            0
#define R_HOLD_TIME                 2
#define R_STROBE_TIME               7
#define R_SETUP_TIME                2

#define W_HOLD_TIME                 2
#define W_STROBE_TIME               7
#define W_SETUP_TIME                2

#define HIC_INIT_DONE_TOKEN     0xFAU
#define HIC_START_TOKEN         0xFBU
#define HIC_DATA_TOKEN          0xFCU
#define HIC_SAMPLE_SIZE         16U
//
// Globals
//
uint16_t errCountGlobal = 0;
uint32_t i;
uint32_t xint1Count = 0;
uint16_t sampleCount = 0;
volatile uint16_t deviceInitDone = 0;
volatile uint16_t deviceDataAvailable = 0;
uint32_t adcData[HIC_SAMPLE_SIZE] = {0};
//
// Function Prototypes
//
void setupEMIF1PinmuxAsync8Bit_HIC(void);
interrupt void xint1ISR(void);

//
//HIC Specific Utility Functions
//
static inline void HIC_MMR_WR_FIELD32(uint32_t addr, uint32_t value)
{
    HWREG(CS2_BASE_ADDR + (addr&0xFF) ) = value;
}


static inline uint32_t HIC_MMR_RD_FIELD32(uint32_t addr)
{
    return(HWREG(CS2_BASE_ADDR + (addr&0xFF)));

}

void HIC_Host_setH2DToken(uint32_t h2dToken)
{
    HIC_MMR_WR_FIELD32( (HIC_HOST_BASE + HIC_O_H2DTOKEN) , h2dToken );
}

void HIC_Host_clearD2HInterrupt(uint32_t interruptFlagClear)
{
    HIC_MMR_WR_FIELD32( (HIC_HOST_BASE + HIC_O_D2HINTCLR) , interruptFlagClear);
}

uint32_t HIC_Host_getD2HInterruptStatus()
{
    return(HIC_MMR_RD_FIELD32(HIC_HOST_BASE + HIC_O_D2HINTFLG));
}


void HIC_Host_writeH2DBuffer(uint32_t bufferNo,uint32_t data)
{
    uint32_t index;
    index = bufferNo * 2;

    HIC_MMR_WR_FIELD32( (HIC_HOST_BASE + HIC_O_H2D_BUF0 + index) , data);
}

uint32_t HIC_Host_readD2HBuffer(uint32_t bufferNo)
{
    uint32_t index;

    index = bufferNo * 2;
    return(HIC_MMR_RD_FIELD32(HIC_O_D2H_BUF0 + index));
}

//
// Main
//
void main(void)
{
    EMIF_AsyncTimingParams tparam;
    uint16_t    i = 0;


    //
    // Initialize device clock and peripherals.
    //
    Device_init();

    //
    // Disable all the interrupts.
    //
    DINT;

    //
    // Setup GPIO by disabling pin locks and enabling pullups.
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
    // Configure EMIF Clock Divider
    //
    SysCtl_setEMIF1ClockDivider(SYSCTL_EMIF1CLK_DIV_2);

    //
    // Grab EMIF1 For CPU1.
    //
    EMIF_selectController(EMIF1CONFIG_BASE, EMIF_CONTROLLER_CPU1_G);

    //
    // Disable Access Protection. (CPU_FETCH/CPU_WR/DMA_WR)
    //
    EMIF_setAccessProtection(EMIF1CONFIG_BASE, 0x0);

    //
    // Commit the configuration related to protection. Till this bit remains
    // set, contents of EMIF1ACCPROT0 register can't be changed.
    //
    EMIF_commitAccessConfig(EMIF1CONFIG_BASE);

    //
    // Lock the configuration so that EMIF1COMMIT register can't be changed
    // any more.
    //
    EMIF_lockAccessConfig(EMIF1CONFIG_BASE);

    //
    // Configure GPIO pins for EMIF1.
    //
    setupEMIF1PinmuxAsync8Bit_HIC();

    //
    // Configures Strobe,Asynchronous Mode of Operation
    // CS Strobing is needed for this mode of operation
    //
    EMIF_setAsyncMode(EMIF1_BASE, EMIF_ASYNC_CS2_OFFSET,
                      EMIF_ASYNC_STROBE_MODE);

    //
    // Async Wait Configurations
    //
    EMIF_setAsyncMaximumWaitCycles(EMIF1_BASE,WAIT_COUNT);
    EMIF_setAsyncWaitPolarity(EMIF1_BASE,EMIF_ASYNC_WAIT_POLARITY_LOW);

    //
    // Configure EMIF1 Data Bus Width.
    //
    EMIF_setAsyncDataBusWidth(EMIF1_BASE, EMIF_ASYNC_CS2_OFFSET,
                              EMIF_ASYNC_DATA_WIDTH_8);

    //
    // Configure the access timing for CS2 space.
    //
    tparam.rSetup = R_SETUP_TIME;
    tparam.rStrobe = R_STROBE_TIME;
    tparam.rHold = R_HOLD_TIME;
    tparam.turnArnd = TURN_AROUND_TIME;
    tparam.wSetup = W_SETUP_TIME;
    tparam.wStrobe = W_STROBE_TIME;
    tparam.wHold = W_HOLD_TIME;
    EMIF_setAsyncTimingParams(EMIF1_BASE, EMIF_ASYNC_CS2_OFFSET, &tparam);

    //
    //Configurations for getting GPIO 10 (HIC_INT)
    //mapped to XINT1
    //
    Interrupt_register(INT_XINT1, &xint1ISR);


    //
    //Configure GPIO 10 for XINT1
    //
    GPIO_setInterruptPin(10,GPIO_INT_XINT1);
    GPIO_enableInterrupt(GPIO_INT_XINT1);
   

    //
    // Configure Rising edge trigger for XINT1
    //
    GPIO_setInterruptType(GPIO_INT_XINT1, GPIO_INT_TYPE_RISING_EDGE);
    Interrupt_enable(INT_XINT1);
    
    //
    //Enable Global Interrupt and Real time Mode
    //
    EINT;
    ERTM;

    //
    //Wait for Init Done Token from HIC (Device to Host Token)
    //This shall be set in xInt ISR when Init token is received
    //
    while(deviceInitDone == 0);

    //
    //Send the Token and this will trigger interrupt H2D interrupt
    //
    HIC_Host_setH2DToken(HIC_START_TOKEN);


    while(1)
    {
        if(deviceDataAvailable)
        {
            //
            //Read ADC data into buffer
            //
            for(i=0;i<HIC_SAMPLE_SIZE;i++)
                adcData[i] = HIC_Host_readD2HBuffer(i);
            sampleCount++;
            deviceDataAvailable = 0;
        }
    }
}

//
// Setup EMIF1 Pinmux Async 16Bit - This function configures pins for 16 bit
// Asynchronous EMIF1.
//
void setupEMIF1PinmuxAsync8Bit_HIC(void)
{
    uint16_t i;

    GPIO_setPinConfig(GPIO_31_EMIF1_RNW);
    GPIO_setPinConfig(GPIO_34_EMIF1_CS2N);
    
    //
    // Selecting address lines.
    //
    GPIO_setPinConfig(GPIO_38_EMIF1_A0);
    GPIO_setPinConfig(GPIO_39_EMIF1_A1);
    GPIO_setPinConfig(GPIO_40_EMIF1_A2);
    GPIO_setPinConfig(GPIO_41_EMIF1_A3);
    GPIO_setPinConfig(GPIO_44_EMIF1_A4);
    GPIO_setPinConfig(GPIO_45_EMIF1_A5);
    GPIO_setPinConfig(GPIO_21_EMIF1_BA1);
    GPIO_setPinConfig(GPIO_20_EMIF1_BA0);

    //
    // Selecting data lines.
    //
    GPIO_setPinConfig(GPIO_77_EMIF1_D7);
    GPIO_setPinConfig(GPIO_78_EMIF1_D6);
    GPIO_setPinConfig(GPIO_79_EMIF1_D5);
    GPIO_setPinConfig(GPIO_80_EMIF1_D4);
    GPIO_setPinConfig(GPIO_81_EMIF1_D3);
    GPIO_setPinConfig(GPIO_82_EMIF1_D2);
    GPIO_setPinConfig(GPIO_83_EMIF1_D1);
    GPIO_setPinConfig(GPIO_85_EMIF1_D0);

    //
    //Setup async mode and enable pull-ups for Data pins.
    //GPIO 77 to 85,excluding 84 are used for HIC Data Pins
    //
    for(i=77; i<=85;i++)
    {
        if(i != 84)
        {
            GPIO_setPadConfig(i, GPIO_PIN_TYPE_PULLUP);
            GPIO_setQualificationMode(i, GPIO_QUAL_ASYNC);
        }
    }

      //
      // Make GPIO10 an input on GPIO10 for HIC_INT from Device
      //
      GPIO_setPadConfig(10, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO10
      GPIO_setPinConfig(GPIO_10_GPIO10);               // GPIO10 = GPIO10
      GPIO_setDirectionMode(10, GPIO_DIR_MODE_IN);     // GPIO10 = input
      GPIO_setQualificationMode(10, GPIO_QUAL_ASYNC);
}

//
// xint1ISR - External Interrupt 1 ISR
//
interrupt void xint1ISR(void)
{

    xint1Count++;

    if((HIC_Host_getD2HInterruptStatus() & HIC_D2HINTFLG_D2H_FLG))
    {
        if(HIC_MMR_RD_FIELD32(HIC_HOST_BASE + HIC_O_D2HTOKEN) == HIC_INIT_DONE_TOKEN)
            deviceInitDone = 1;
         //
         //Read the Token from HIC (Device to Host Token)
         //
         if( HIC_MMR_RD_FIELD32(HIC_HOST_BASE + HIC_O_D2HTOKEN) == HIC_DATA_TOKEN)
              deviceDataAvailable =1;
         HIC_Host_clearD2HInterrupt(HIC_D2HINTFLG_D2H_FLG);
    }

    //
    // Acknowledge this interrupt to get more from group 1
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}
//
// End of File
//
