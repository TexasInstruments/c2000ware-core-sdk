//#############################################################################
//
// FILE:   emif_ex7_16bit_asram_hic_fsi.c
//
// TITLE:  EMIF1 ASYNC module accessing 16bit HIC Controller and FSI
//
//! \addtogroup driver_example_list
//! <h1> EMIF1 ASYNC module accessing 16bit ASRAM HIC FSI </h1>
//!
//! This example configures EMIF1 in 16bit ASYNC mode and uses CS2 as chip
//! enable.
//! This can be run with hic_ex3_config_16bit_fsi example on F28002x device.
//! This is run first followed by the run of F28002x device example.
//! This example configures EMIF1 in 16-bit ASYNC mode and uses CS2 as chip
//! enable to access Host Interface Controller(HIC) on F28002X device
//! 
//! This follows example configuration for performance critical applications
//! described in the Application note titled "Application guide for peripheral 
//! expansion using HIC"(SPRACR2).
//! 
//! -This example sets up the EMIF CS2 for ASRAM interface to access
//! the Host interface Controller. This uses the Direct Access Mode of the 
//! HIC.
//! -The example on F28002x side sets up the FSI module for internal loopback
//! Sets up the Host interface Controller for direct access mode
//! - Sends a HIC_INIT_DONE_TOKEN after which this example 
//! accesses the FSI of the device side over HIC direct access 
//! - Fills the Transmit frame and triggers transmit
//! - Receives an interrupt when the frame is received on the device 
//! side FSI(uses GPIO04 connected to HIC_INT, configured for XINT1)
//! - reads the FSI received frame and checks for correctness
//! This demonstrates the usage of Direct access mode and 16 bit mode of 
//! HIC module.
//! \b External \b Connections \n
//!  - This example will not work on F2838x Control Card and has been tested
//! in TI Internal Validation platform.
//!
//! \b Watch \b Variables \n
//! - \b errCountGlobal - Error counter
//! - \b xint1Count - Number of times HIC Interrupt is received
//! for FSI Receive event
//!
//
//#############################################################################
//
//
// 
// C2000Ware v5.03.00.00
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
#define ASRAM_CS2_START_ADDR        0x100000U
#define ASRAM_CS2_SIZE              0x8000U
#define HIC_INIT_DONE_TOKEN         0xFAU
#define HIC_END_TOKEN               0xFDU
#define DEVICE_FSI_O_TX_BUF_BASE(i)    (0x40U + (i))
#define DEVICE_FSI_O_RX_BUF_BASE(i)    (0x80U + (i))   
#define DEVICE_FSI_O_TX_FRAME_CTRL       0x6U
#define DEVICE_FSI_TX_FRAME_CTRL_START   0x8000U
#define CS2_BASE_ADDR               0x00100000
#define HIC_HOST_BASE CS2_BASE_ADDR

#define HIC_EVTTRIG_EVENT_0         0x010000U //!< EVTTRIG0

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
#define HIC_D2HINTFLG_D2H_FLG       1

//
// Globals
//
uint16_t errCountGlobal = 0;
uint32_t fsiInterruptReceived=0;
uint32_t xint1Count =0;

//
// Function Prototypes
//
void setupEMIF1PinmuxAsync16Bit_HIC(void);
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

static inline void HIC_DEVICE_WR_FIELD16(uint16_t addr, uint16_t value)
{
    HWREGH(CS2_BASE_ADDR + (addr | 0x100)) = value;
}


static uint16_t HIC_DEVICE_REGION_RD_FIELD16(uint8_t region,uint16_t addr)
{
    return( HWREGH(CS2_BASE_ADDR + (addr | (region<<8))));
}

static inline void HIC_Host_selectBaseAddress(uint32_t baseSel)
{
    HIC_MMR_WR_FIELD32( (HIC_HOST_BASE + HIC_O_BASESEL) , baseSel);
}

static inline void HIC_Host_hostConfig(uint32_t hostConfig)
{
    HIC_MMR_WR_FIELD32( (HIC_HOST_BASE + HIC_O_HOSTCR) , (hostConfig|0xA500));
}

static inline void HIC_Host_setH2DToken(uint32_t h2dToken)
{
    HIC_MMR_WR_FIELD32( (HIC_HOST_BASE + HIC_O_H2DTOKEN) , h2dToken );
}

static inline void HIC_Host_enableH2DInterrupt(uint32_t interruptFlags)
{
    HIC_MMR_WR_FIELD32( (HIC_HOST_BASE + HIC_O_H2DINTEN) , interruptFlags) ;
}

static inline void HIC_Host_disableH2DInterrupt(uint32_t interruptFlags)
{
    HIC_MMR_WR_FIELD32( (HIC_HOST_BASE + HIC_O_H2DINTEN) , ~interruptFlags) ;
}

static inline void HIC_Host_clearH2DInterrupt(uint32_t interruptFlagClear)
{
    HIC_MMR_WR_FIELD32( (HIC_HOST_BASE + HIC_O_H2DINTCLR) , interruptFlagClear);
}

uint32_t HIC_Host_getH2DInterruptStatus()
{
    return(HIC_MMR_RD_FIELD32(HIC_HOST_BASE + HIC_O_H2DINTFLG));
}

static inline void HIC_Host_clearD2HInterrupt(uint32_t interruptFlagClear)
{
    HIC_MMR_WR_FIELD32( (HIC_HOST_BASE + HIC_O_D2HINTCLR) , interruptFlagClear);
}

uint32_t HIC_Host_getD2HInterruptStatus()
{
    return(HIC_MMR_RD_FIELD32(HIC_HOST_BASE + HIC_O_D2HINTFLG));
}


static inline void HIC_Host_writeH2DBuffer(uint32_t bufferNo,uint32_t data)
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

#if 0
//
//These routines are not used in this program
//But are provided for reference
//
static inline void HIC_MMR_WR_FIELD16(uint32_t addr, uint16_t value)
{
    HWREGH(CS2_BASE_ADDR + (addr & 0xFE)) = value;
}
static inline void HIC_DEVICE_WR_FIELD32(uint32_t addr, uint32_t value)
{
    HWREG(CS2_BASE_ADDR + ((addr & 0xFF) | 0x100)) = value;
}
static inline void HIC_DEVICE_WR_BASESELFROMPIN_FIELD16(uint16_t addr, uint16_t value)
{
    HWREGH(CS2_BASE_ADDR + addr ) = value;
}

static uint16_t HIC_DEVICE_RD_BASESELFROMPIN_FIELD16(uint16_t addr)
{
    return( HWREGH(CS2_BASE_ADDR + (addr | 0x100)) );
}
static inline void HIC_DEVICE_WR_BASESELFROMPIN_FIELD32(uint32_t addr, uint32_t value)
{
    HWREGH(CS2_BASE_ADDR + (addr & 0xFE )) = value;
    HWREGH(CS2_BASE_ADDR + ((addr & 0xFE) + 1)) = (value >> 16);
}

static uint32_t HIC_DEVICE_RD_BASESELFROMPIN_FIELD32(uint32_t addr)
{
    uint32_t temp1, temp2;
    temp1 = HWREGH(CS2_BASE_ADDR + (addr & 0xFE )) ;
    temp2 = HWREGH(CS2_BASE_ADDR + ((addr & 0xFE) + 1)) ;
    return(temp1 | (temp2 << 16));
}
static uint16_t HIC_DEVICE_RD_FIELD16(uint16_t addr)
{
    return( HWREGH(CS2_BASE_ADDR + (addr | 0x100)) );
}
static inline uint32_t HIC_DEVICE_RD_FIELD32(uint32_t addr)
{
    return( HWREG(CS2_BASE_ADDR + ( (addr & 0xFF) | 0x100)) ) ;
}
#endif

//
// Main
//
void main(void)
{
    EMIF_AsyncTimingParams tparam;
    uint32_t index = 0U;
    uint16_t frameControl = 0;


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
    // Configure to run EMIF1 on full Rate. (EMIF1CLK = CPU1SYSCLK)
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
    // TBD GPIO10 as input for HINT interrupt
    //
    setupEMIF1PinmuxAsync16Bit_HIC();

    //
    // Configures Normal Asynchronous Mode of Operation.
    //
    EMIF_setAsyncMode(EMIF1_BASE, EMIF_ASYNC_CS2_OFFSET,
                      EMIF_ASYNC_NORMAL_MODE);

    //
    // Enable Extended Wait Mode.
    //
    EMIF_setAsyncMaximumWaitCycles(EMIF1_BASE,WAIT_COUNT);

    //
    //Active Low Polarity for Wait Signal
    //
    EMIF_setAsyncWaitPolarity(EMIF1_BASE,EMIF_ASYNC_WAIT_POLARITY_LOW);
    EMIF_enableAsyncExtendedWait(EMIF1_BASE,EMIF_ASYNC_CS2_OFFSET);

    //
    // Configure EMIF1 Data Bus Width.
    //
    EMIF_setAsyncDataBusWidth(EMIF1_BASE, EMIF_ASYNC_CS2_OFFSET,
                              EMIF_ASYNC_DATA_WIDTH_16);

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

    Interrupt_register(INT_XINT1, &xint1ISR);

    GPIO_setQualificationMode(10, GPIO_QUAL_ASYNC);

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
    EINT;
    ERTM;

    //
    //Wait till the Flag is set by the HIC module
    //
    while(HIC_Host_getD2HInterruptStatus() != HIC_D2HINTFLG_D2H_FLG);

    //
    //Clear the flag to process further commands
    //
    HIC_Host_clearD2HInterrupt(HIC_D2HINTFLG_D2H_FLG);


    //
    //Use the first Base Address Region
    //
    HIC_Host_selectBaseAddress(0);

    //
    //Using 6 word per Frame
    //Fill the Transmit buffer
    //
    for(index = 0;index < 6;index++)
    {
        HIC_DEVICE_WR_FIELD16(DEVICE_FSI_O_TX_BUF_BASE(index),index);
    }

    //
    //Read the Frame control register of Device FSI
    //Set the Frame Start to trigger Transmit
    //
    frameControl = HIC_DEVICE_REGION_RD_FIELD16(1,DEVICE_FSI_O_TX_FRAME_CTRL);
    frameControl = (frameControl | DEVICE_FSI_TX_FRAME_CTRL_START);
    HIC_DEVICE_WR_FIELD16(DEVICE_FSI_O_TX_FRAME_CTRL,frameControl);
    
    //
    //Check if the read data is same as what is written
    //
    while(0U == fsiInterruptReceived);
        
    //
    //Check received data correctness
    //
    for(index = 0;index < 6;index++)
    {
        if(HIC_DEVICE_REGION_RD_FIELD16(1,
                                        DEVICE_FSI_O_RX_BUF_BASE(index)) !=
           index)
            errCountGlobal++;
    }

    ESTOP0;

}
//
// Setup EMIF1 Pinmux Async 16Bit - This function configures pins for 16 bit
// Asynchronous EMIF1.
//
void setupEMIF1PinmuxAsync16Bit_HIC(void)
{
    uint16_t index;

    GPIO_setPinConfig(GPIO_31_EMIF1_WEN);
    GPIO_setPinConfig(GPIO_34_EMIF1_CS2N);
    GPIO_setPinConfig(GPIO_36_EMIF1_WAIT);
    GPIO_setPinConfig(GPIO_37_EMIF1_OEN);

    //
    // Selecting address lines.
    //
    GPIO_setPinConfig(GPIO_38_EMIF1_A0);
    GPIO_setPinConfig(GPIO_39_EMIF1_A1);
    GPIO_setPinConfig(GPIO_40_EMIF1_A2);
    GPIO_setPinConfig(GPIO_41_EMIF1_A3);
    GPIO_setPinConfig(GPIO_44_EMIF1_A4);
    GPIO_setPinConfig(GPIO_45_EMIF1_A5);
    GPIO_setPinConfig(GPIO_46_EMIF1_A6);
    GPIO_setPinConfig(GPIO_47_EMIF1_A7);

    //
    // Selecting data lines.
    //
    GPIO_setPinConfig(GPIO_69_EMIF1_D15);
    GPIO_setPinConfig(GPIO_70_EMIF1_D14);
    GPIO_setPinConfig(GPIO_71_EMIF1_D13);
    GPIO_setPinConfig(GPIO_72_EMIF1_D12);
    GPIO_setPinConfig(GPIO_73_EMIF1_D11);
    GPIO_setPinConfig(GPIO_74_EMIF1_D10);
    GPIO_setPinConfig(GPIO_75_EMIF1_D9);
    GPIO_setPinConfig(GPIO_76_EMIF1_D8);
    GPIO_setPinConfig(GPIO_77_EMIF1_D7);
    GPIO_setPinConfig(GPIO_78_EMIF1_D6);
    GPIO_setPinConfig(GPIO_79_EMIF1_D5);
    GPIO_setPinConfig(GPIO_80_EMIF1_D4);
    GPIO_setPinConfig(GPIO_81_EMIF1_D3);
    GPIO_setPinConfig(GPIO_82_EMIF1_D2);
    GPIO_setPinConfig(GPIO_83_EMIF1_D1);
    GPIO_setPinConfig(GPIO_85_EMIF1_D0);

    //
    // Setting DQM and Bank Select lines
    //
    GPIO_setPinConfig(GPIO_24_EMIF1_DQM0);
    GPIO_setPinConfig(GPIO_25_EMIF1_DQM1);
    GPIO_setPinConfig(GPIO_21_EMIF1_BA1);

    //
    // Setup async mode and enable pull-ups for Data pins.
    //
    for(index = 69; index <= 85;index++)
    {
        if(index != 84)
        {
            GPIO_setPadConfig(index, GPIO_PIN_TYPE_PULLUP);
            GPIO_setQualificationMode(index, GPIO_QUAL_ASYNC);
        }
    }

    //
    // Make GPIO10 an input on GPIO10
    //
    GPIO_setPadConfig(10, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO10
    GPIO_setPinConfig(GPIO_10_GPIO10);               // GPIO10 = GPIO10
    GPIO_setDirectionMode(10, GPIO_DIR_MODE_IN);     // GPIO10 = input
}

//
// xint1ISR - External Interrupt 1 ISR
//
interrupt void xint1ISR(void)
{

    xint1Count++;

    if((HIC_Host_getD2HInterruptStatus() & HIC_EVTTRIG_EVENT_0))
    {
        fsiInterruptReceived = 1;
        HIC_Host_clearD2HInterrupt(HIC_EVTTRIG_EVENT_0);
    }

    //
    // Acknowledge this interrupt to get more from group 1
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}
//
// End of File
//
