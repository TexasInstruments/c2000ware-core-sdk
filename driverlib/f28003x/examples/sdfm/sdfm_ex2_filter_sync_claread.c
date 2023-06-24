//###########################################################################
//
// FILE:   sdfm_ex2_filter_sync_claread.c
//
// TITLE:  SDFM Filter sync CLA Example.
//
//! \addtogroup driver_example_list
//! <h1> SDFM Filter Sync CLA</h1>
//!
//! In this example, SDFM filter data is read by CLA in Cla1Task1. The
//! SDFM configuration is shown below:
//!  - SDFM1 used in this example.For using SDFM2, few modifications
//!    would be needed in the example.
//!  - MODE0 Input control mode selected
//!  - Comparator settings
//!       -    Sinc3 filter selected
//!       -    OSR = 32
//!       -    hlt = 0x7FFF (Higher threshold setting)
//!       -    llt  = 0x0000(Lower threshold setting)
//!  -  Data filter settings
//!      - All the 4 filter modules enabled
//!      - Sinc3 filter selected
//!      - OSR = 256
//!      - All the 4 filters are synchronized by using MFE
//!       (Master Filter enable bit)
//!      - Filter output represented in 16 bit format
//!      - In order to convert 25 bit Data filter
//!        into 16 bit format user needs to right shift by 10 bits for
//!        Sinc3 filter with OSR = 256
//!  - Interrupt module settings for SDFM filter
//!       -    All the 4 higher threshold comparator interrupts disabled
//!       -    All the 4 lower threshold comparator interrupts disabled
//!       -    All the 4 modulator failure interrupts disabled
//!       -    All the 4 filter will generate interrupt when a new filter data
//!         is available
//!
//! \b External \b Connections \n
//!   - SDFM_PIN_MUX_OPTION1 Connect Sigma-Delta streams to
//!     (SDx-D1, SDx-C1 to SDx-D4,SDx-C4) on GPIO16-GPIO31
//!   - SDFM_PIN_MUX_OPTION2 Connect Sigma-Delta streams to
//!     (SDx-D1, SDx-C1 to SDx-D4,SDx-C4) on GPIO46-GPIO61
//!
//! \b Watch \b Variables \n
//! -  \b filter1Result - Output of filter 1
//! -  \b filter2Result - Output of filter 2
//! -  \b filter3Result - Output of filter 3
//! -  \b filter4Result - Output of filter 4
//!
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
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
#include "driverlib.h"
#include "device.h"
#include <stdio.h>
#include "sdfm_claread.h"

//
// Defines
//
#define SDFM_PIN_MUX_OPTION1      1
#define SDFM_PIN_MUX_OPTION2      2
#define WAITSTEP                  asm(" RPT #255 || NOP")

//
// Globals
//
uint32_t sdfmInstance;

//
// Function Prototypes
//
void configureSDFMPins(uint16_t);
void setPinConfig1(void);
void setPinConfig2(void);
void initCLAMemoryMap(void);
void initCPU1CLA(void);

//
// Main
//
int main(void)
{
    uint16_t  pinMuxOption;
    uint16_t  hlt, llt;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Setup GPIO by disabling pin locks and enabling pullups
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
    // Configure SDFM type to 0 and see if data ack generated SDINT.
    //
    SysCtl_configureType(SYSCTL_SDFMTYPE, 0, 1);

    pinMuxOption = SDFM_PIN_MUX_OPTION1;

    //
    // Configure GPIO pins as SDFM pins
    //
    configureSDFMPins(pinMuxOption);

    //
    // Configure the CLA memory spaces
    //
    initCLAMemoryMap();

    //
    // Configure the CLA task vectors & end-of task interrupts
    //
    initCPU1CLA();

    //
    // Force task 8
    //
    CLA_forceTasks(CLA1_BASE,CLA_TASKFLAG_8);
    WAITSTEP;

    //
    // Trigger Source for TASK1 of CLA1 = SDFM1
    //
    CLA_setTriggerSource(CLA_TASK_1, CLA_TRIGGER_SDFM1INT);

    //
    // Trigger Source for TASK2 of CLA1 = SDFM2
    //
    CLA_setTriggerSource(CLA_TASK_2, CLA_TRIGGER_SDFM2INT);

    //
    // Configure SDFM1
    //
    sdfmInstance = SDFM1_BASE;

    //
    // Input Control Module
    //
    // Configure Input Control Mode: Modulator Clock rate = Modulator data rate
    //
    SDFM_setupModulatorClock(sdfmInstance, SDFM_FILTER_1,
                             SDFM_MODULATOR_CLK_EQUAL_DATA_RATE);

    SDFM_setupModulatorClock(sdfmInstance, SDFM_FILTER_2,
                             SDFM_MODULATOR_CLK_EQUAL_DATA_RATE);

    SDFM_setupModulatorClock(sdfmInstance, SDFM_FILTER_3,
                             SDFM_MODULATOR_CLK_EQUAL_DATA_RATE);

    SDFM_setupModulatorClock(sdfmInstance, SDFM_FILTER_4,
                             SDFM_MODULATOR_CLK_EQUAL_DATA_RATE);

    //
    // Comparator Module
    //
    hlt = 0x7FFF;    //Over value threshold settings
    llt = 0x0000;    //Under value threshold settings

    //
    // Configure Comparator module's comparator filter type and comparator's OSR
    // value, higher threshold, lower threshold
    //
    SDFM_configComparator(sdfmInstance,
        (SDFM_FILTER_1 | SDFM_FILTER_SINC_3 | SDFM_SET_OSR(32)),
        (SDFM_GET_LOW_THRESHOLD(llt) | SDFM_GET_HIGH_THRESHOLD(hlt)), 0);
    SDFM_configComparator(sdfmInstance,
        (SDFM_FILTER_2 | SDFM_FILTER_SINC_3 | SDFM_SET_OSR(32)),
        (SDFM_GET_LOW_THRESHOLD(llt) | SDFM_GET_HIGH_THRESHOLD(hlt)), 0);
    SDFM_configComparator(sdfmInstance,
        (SDFM_FILTER_3 | SDFM_FILTER_SINC_3 | SDFM_SET_OSR(32)),
        (SDFM_GET_LOW_THRESHOLD(llt) | SDFM_GET_HIGH_THRESHOLD(hlt)), 0);
    SDFM_configComparator(sdfmInstance,
        (SDFM_FILTER_4 | SDFM_FILTER_SINC_3 | SDFM_SET_OSR(32)),
        (SDFM_GET_LOW_THRESHOLD(llt) | SDFM_GET_HIGH_THRESHOLD(hlt)), 0);

    //
    // Data filter Module
    //
    // Configure Data filter modules filter type, OSR value and
    // enable / disable data filter
    //
    SDFM_configDataFilter(sdfmInstance, (SDFM_FILTER_1 | SDFM_FILTER_SINC_3 |
           SDFM_SET_OSR(256)), (SDFM_DATA_FORMAT_16_BIT | SDFM_FILTER_ENABLE |
           SDFM_SHIFT_VALUE(0x000A)));

    SDFM_configDataFilter(sdfmInstance, (SDFM_FILTER_2 | SDFM_FILTER_SINC_3 |
           SDFM_SET_OSR(256)), (SDFM_DATA_FORMAT_16_BIT | SDFM_FILTER_ENABLE |
           SDFM_SHIFT_VALUE(0x000A)));

    SDFM_configDataFilter(sdfmInstance, (SDFM_FILTER_3 | SDFM_FILTER_SINC_3 |
           SDFM_SET_OSR(256)), (SDFM_DATA_FORMAT_16_BIT | SDFM_FILTER_ENABLE |
           SDFM_SHIFT_VALUE(0x000A)));

    SDFM_configDataFilter(sdfmInstance, (SDFM_FILTER_4 | SDFM_FILTER_SINC_3 |
           SDFM_SET_OSR(256)), (SDFM_DATA_FORMAT_16_BIT | SDFM_FILTER_ENABLE |
           SDFM_SHIFT_VALUE(0x000A)));

    //
    // Enable Master filter bit: Unless this bit is set none of the filter
    // modules can be enabled. All the filter modules are synchronized when
    // master filter bit is enabled after individual filter modules are enabled.
    //
    SDFM_enableMasterFilter(sdfmInstance);

    SDFM_disableExternalReset(sdfmInstance, SDFM_FILTER_1);
    SDFM_disableExternalReset(sdfmInstance, SDFM_FILTER_2);
    SDFM_disableExternalReset(sdfmInstance, SDFM_FILTER_3);
    SDFM_disableExternalReset(sdfmInstance, SDFM_FILTER_4);

    //
    // Enable interrupts
    //
    // Following SDFM interrupts can be enabled / disabled using this function.
    //  Enable / disable comparator high threshold
    //  Enable / disable comparator low threshold
    //  Enable / disable modulator clock failure
    //  Enable / disable filter acknowledge
    //
    SDFM_enableInterrupt(sdfmInstance, SDFM_FILTER_1,
            (SDFM_MODULATOR_FAILURE_INTERRUPT |
             SDFM_DATA_FILTER_ACKNOWLEDGE_INTERRUPT));

    SDFM_enableInterrupt(sdfmInstance, SDFM_FILTER_2,
            (SDFM_MODULATOR_FAILURE_INTERRUPT |
             SDFM_DATA_FILTER_ACKNOWLEDGE_INTERRUPT));

    SDFM_enableInterrupt(sdfmInstance, SDFM_FILTER_3,
            (SDFM_MODULATOR_FAILURE_INTERRUPT |
             SDFM_DATA_FILTER_ACKNOWLEDGE_INTERRUPT));

    SDFM_enableInterrupt(sdfmInstance, SDFM_FILTER_4,
            (SDFM_MODULATOR_FAILURE_INTERRUPT |
             SDFM_DATA_FILTER_ACKNOWLEDGE_INTERRUPT));

    SDFM_disableInterrupt(sdfmInstance, SDFM_FILTER_1,
            (SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT |
             SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT));

    SDFM_disableInterrupt(sdfmInstance, SDFM_FILTER_2,
            (SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT |
             SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT));

    SDFM_disableInterrupt(sdfmInstance, SDFM_FILTER_3,
            (SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT |
             SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT));

    SDFM_disableInterrupt(sdfmInstance, SDFM_FILTER_4,
            (SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT |
             SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT));

    //
    // Enable master interrupt so that any of the filter interrupts can
    // trigger by SDFM interrupt to CPU
    //
    SDFM_enableMasterInterrupt(sdfmInstance);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    while(1);
}

//
// configureSDFMPins - Configure SDFM GPIOs
//
void configureSDFMPins(uint16_t sdfmPinOption)
{
    uint16_t pin;

    switch (sdfmPinOption)
    {
        case SDFM_PIN_MUX_OPTION1:
            for(pin = 16; pin <= 31; pin++)
            {
                GPIO_setDirectionMode(pin, GPIO_DIR_MODE_IN);
                GPIO_setMasterCore(pin, GPIO_CORE_CPU1);
                GPIO_setPadConfig(pin, GPIO_PIN_TYPE_STD);
                GPIO_setQualificationMode(pin, GPIO_QUAL_ASYNC);
            }
            setPinConfig1();
            break;

        case SDFM_PIN_MUX_OPTION2:
            for(pin = 46; pin <= 61; pin++)
            {
                GPIO_setDirectionMode(pin, GPIO_DIR_MODE_IN);
                GPIO_setMasterCore(pin, GPIO_CORE_CPU1);
                GPIO_setPadConfig(pin, GPIO_PIN_TYPE_STD);
                GPIO_setQualificationMode(pin, GPIO_QUAL_ASYNC);
            }
            setPinConfig2();
            break;
    }
}

//
// setPinConfig1 - sets the pin configuration for pins 16-21
//
void setPinConfig1()
{
    GPIO_setPinConfig(GPIO_16_SD1_D1);
    GPIO_setPinConfig(GPIO_17_SD1_C1);
    GPIO_setPinConfig(GPIO_18_SD1_D2);
    GPIO_setPinConfig(GPIO_19_SD1_C2);
    GPIO_setPinConfig(GPIO_20_SD1_D3);
    GPIO_setPinConfig(GPIO_21_SD1_C3);
    GPIO_setPinConfig(GPIO_22_SD1_D4);
    GPIO_setPinConfig(GPIO_23_SD1_C4);
    GPIO_setPinConfig(GPIO_24_SD2_D1);
    GPIO_setPinConfig(GPIO_25_SD2_C1);
    GPIO_setPinConfig(GPIO_26_SD2_D2);
    GPIO_setPinConfig(GPIO_27_SD2_C2);
    GPIO_setPinConfig(GPIO_28_SD2_D3);
    GPIO_setPinConfig(GPIO_29_SD2_C3);
    GPIO_setPinConfig(GPIO_30_SD2_D4);
    GPIO_setPinConfig(GPIO_31_SD2_C4);
}

//
// setPinConfig2 - sets the pin configuration for
// pins 46-61
//
void setPinConfig2()
{
    GPIO_setPinConfig(GPIO_46_SD2_C4);
    GPIO_setPinConfig(GPIO_47_SD2_D4);
    GPIO_setPinConfig(GPIO_48_SD1_D1);
    GPIO_setPinConfig(GPIO_49_SD1_C1);
    GPIO_setPinConfig(GPIO_50_SD1_D2);
    GPIO_setPinConfig(GPIO_51_SD1_C2);
    GPIO_setPinConfig(GPIO_52_SD1_D3);
    GPIO_setPinConfig(GPIO_53_SD1_C3);
    GPIO_setPinConfig(GPIO_54_SD1_D4);
    GPIO_setPinConfig(GPIO_55_SD1_C4);
    GPIO_setPinConfig(GPIO_56_SD2_D1);
    GPIO_setPinConfig(GPIO_57_SD2_C1);
    GPIO_setPinConfig(GPIO_58_SD2_D2);
    GPIO_setPinConfig(GPIO_59_SD2_C2);
    GPIO_setPinConfig(GPIO_60_SD2_D3);
    GPIO_setPinConfig(GPIO_61_SD2_C3);
}


//
// initCLAMemoryMap - Initialize Memory map
//
void initCLAMemoryMap(void)
{
    //
    // Initialize and wait for CPUToCLA1MsgRAM
    //
    MemCfg_initSections(MEMCFG_SECT_MSGCLA1TOCPU);
    while(MemCfg_getInitStatus(MEMCFG_SECT_MSGCLA1TOCPU) != true);

    //
    // Copy the program and constants from FLASH to RAM before configuring
    // the CLA
    //
#if defined(_FLASH)
    memcpy((uint32_t *)&Cla1ProgRunStart, (uint32_t *)&Cla1ProgLoadStart,
        (uint32_t)&Cla1ProgLoadSize );
    memcpy((uint32_t *)&Cla1ConstRunStart, (uint32_t *)&Cla1ConstLoadStart,
        (uint32_t)&Cla1ConstLoadSize );
#endif //defined(_FLASH)

    //
    // Select LS0 and LS1 RAM to be data RAM for the CLA and LS5 to be
    // programming space for the CLA as per linker cmd file used in this
    // example. This configuration should be updated as per the linker cmd file
    // used in the application.
    //
    MemCfg_setCLAMemType(MEMCFG_SECT_LS5, MEMCFG_CLA_MEM_PROGRAM);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS0, MEMCFG_CLA_MEM_DATA);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS1, MEMCFG_CLA_MEM_DATA);
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS5, MEMCFG_LSRAMMASTER_CPU_CLA1);
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS0, MEMCFG_LSRAMMASTER_CPU_CLA1);
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS1, MEMCFG_LSRAMMASTER_CPU_CLA1);


    //
    // Initialize and wait for CPUToCLA1MsgRAM
    //
    MemCfg_initSections(MEMCFG_SECT_MSGCPUTOCLA1);
    while(MemCfg_getInitStatus(MEMCFG_SECT_MSGCPUTOCLA1) != true);

    //
    // Filter1 and Filter2 data memory is mapped to LS6 RAM in linker cmd file
    // used in this example. This configuration should be updated as per the
    // linker cmd file used in the application.
    //
    MemCfg_setCLAMemType(MEMCFG_SECT_LS6, MEMCFG_CLA_MEM_DATA);
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS6, MEMCFG_LSRAMMASTER_CPU_CLA1);

    //
    // Filter3 and Filter4 data memory is mapped to LS7 RAM in linker cmd file
    // used in this example. This configuration should be updated as per the
    // linker cmd file used in the application.
    //
    MemCfg_setCLAMemType(MEMCFG_SECT_LS7, MEMCFG_CLA_MEM_DATA);
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS7, MEMCFG_LSRAMMASTER_CPU_CLA1);
}

//
// initCPU1CLA - Initialize CLA1 task vectors and end of task interrupts
//
void initCPU1CLA(void)
{
    //
    // Compute all CLA task vectors
    // Beyond Type-1 CLAs the MVECT registers accept full 16-bit task addresses
    // as opposed to offsets used on older Type-0 CLAs
    //
#pragma diag_suppress=770
    CLA_mapTaskVector(CLA1_BASE,CLA_MVECT_1,(uint16_t)&Cla1Task1);
    CLA_mapTaskVector(CLA1_BASE,CLA_MVECT_2,(uint16_t)&Cla1Task2);
    CLA_mapTaskVector(CLA1_BASE,CLA_MVECT_3,(uint16_t)&Cla1Task3);
    CLA_mapTaskVector(CLA1_BASE,CLA_MVECT_4,(uint16_t)&Cla1Task4);
    CLA_mapTaskVector(CLA1_BASE,CLA_MVECT_5,(uint16_t)&Cla1Task5);
    CLA_mapTaskVector(CLA1_BASE,CLA_MVECT_6,(uint16_t)&Cla1Task6);
    CLA_mapTaskVector(CLA1_BASE,CLA_MVECT_7,(uint16_t)&Cla1Task7);
    CLA_mapTaskVector(CLA1_BASE,CLA_MVECT_8,(uint16_t)&Cla1Task8);
#pragma diag_warning=770

    //
    // Enable IACK instruction to start a task on CLA in software
    // for all  8 CLA tasks
    //
    asm("   RPT #3 || NOP");
    CLA_enableIACK(CLA1_BASE);
    CLA_enableTasks(CLA1_BASE, CLA_TASKFLAG_ALL);

    //
    // Configure the vectors for the end-of-task interrupt for all
    // 8 tasks
    //
    Interrupt_register(INT_CLA1_1, &cla1Isr1);
    Interrupt_register(INT_CLA1_2, &cla1Isr2);
    Interrupt_register(INT_CLA1_3, &cla1Isr3);
    Interrupt_register(INT_CLA1_4, &cla1Isr4);
    Interrupt_register(INT_CLA1_5, &cla1Isr5);
    Interrupt_register(INT_CLA1_6, &cla1Isr6);
    Interrupt_register(INT_CLA1_7, &cla1Isr7);
    Interrupt_register(INT_CLA1_8, &cla1Isr8);

    //
    // Enable CLA interrupts at the group and subgroup levels
    //
    Interrupt_enable(INT_CLA1_1);
    Interrupt_enable(INT_CLA1_2);
    Interrupt_enable(INT_CLA1_3);
    Interrupt_enable(INT_CLA1_4);
    Interrupt_enable(INT_CLA1_5);
    Interrupt_enable(INT_CLA1_6);
    Interrupt_enable(INT_CLA1_7);
    Interrupt_enable(INT_CLA1_8);

    EINT;   // Enable Global interrupt INTM
    ERTM;   // Enable Global realtime interrupt DBGM
}

//
// cla1Isr1 - CLA1 ISR 1
//
interrupt void cla1Isr1 ()
{
    //
    // Acknowledge the end-of-task interrupt for task 1
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP11);

    //
    // Halt debugger and stop here
    //
    asm(" ESTOP0");
}

//
// cla1Isr1 - CLA1 ISR 2
//
interrupt void cla1Isr2 ()
{
    //
    // Acknowledge the end-of-task interrupt for task 2
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP11);

    //
    // Halt debugger and stop here
    //
    asm(" ESTOP0");
}

//
// cla1Isr1 - CLA1 ISR 3
//
interrupt void cla1Isr3 ()
{
    //
    // Halt debugger and stop here
    //
    asm(" ESTOP0");
}

//
// cla1Isr1 - CLA1 ISR 4
//
interrupt void cla1Isr4 ()
{
    //
    // Halt debugger and stop here
    //
    asm(" ESTOP0");
}

//
// cla1Isr1 - CLA1 ISR 5
//
interrupt void cla1Isr5 ()
{
    //
    // Halt debugger and stop here
    //
    asm(" ESTOP0");
}

//
// cla1Isr1 - CLA1 ISR 6
//
interrupt void cla1Isr6 ()
{
    //
    // Halt debugger and stop here
    //
    asm(" ESTOP0");
}

//
// cla1Isr1 - CLA1 ISR 7
//
interrupt void cla1Isr7 ()
{
    //
    // Halt debugger and stop here
    //
    asm(" ESTOP0");
}

//
// cla1Isr1 - CLA1 ISR 8
//
interrupt void cla1Isr8 ()
{
    //
    // Acknowledge the end-of-task interrupt for task 8
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP11);

//    //
//    // Uncomment to halt debugger and stop here
//    //
//    asm(" ESTOP0");
}

//
// End of file
//
