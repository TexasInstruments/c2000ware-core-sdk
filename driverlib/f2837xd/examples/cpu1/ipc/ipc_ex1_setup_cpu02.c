//###########################################################################
//
// FILE:   ipc_ex1_setup_cpu02.c
//
// TITLE:  Example to setup peripherals for control by CPU02.
//
//! \addtogroup driver_example_list
//! <h1> Setup CPU02 for Control </h1>
//!
//! This example gives control of all shared GPIOs and peripherals to CPU02
//!
//
//###########################################################################
//
// $Release Date:  $
// $Copyright:
// Copyright (C) 2013-2024 Texas Instruments Incorporated - http://www.ti.com/
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
//###########################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"

void main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable interrupt pullups.
    //
    Device_initGPIO();

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Enable global Interrupts and higher priority real-time debug events:
    //
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

    //
    // Transfer ownership of all GPIOs to CPU02
    //
    EALLOW;
    int gpioPin = 0;
    for(gpioPin=0; gpioPin<=168; gpioPin++)
    {
        GPIO_setMasterCore(gpioPin, GPIO_CORE_CPU2);
    }


    //
    // Transfer ownership of all peripherals to CPU02
    //
    uint16_t i;
    for (i=1;i<=12;i++)
    {
        SysCtl_selectCPUForPeripheral(SYSCTL_CPUSEL0_EPWM, i,
                                      SYSCTL_CPUSEL_CPU2);
    }
    for(i=1;i<=6;i++)
    {
        SysCtl_selectCPUForPeripheral(SYSCTL_CPUSEL1_ECAP, i,
                                      SYSCTL_CPUSEL_CPU2);
    }
    for (i=1;i<=3;i++)
    {
    SysCtl_selectCPUForPeripheral(SYSCTL_CPUSEL2_EQEP, i, SYSCTL_CPUSEL_CPU2);
    }
    for (i=1;i<=2;i++)
    {
        SysCtl_selectCPUForPeripheral(SYSCTL_CPUSEL4_SD, i,
                                      SYSCTL_CPUSEL_CPU2);
    }
    for (i=1;i<=4;i++)
    {
        SysCtl_selectCPUForPeripheral(SYSCTL_CPUSEL5_SCI, i,
                                      SYSCTL_CPUSEL_CPU2);
    }
    for (i=1;i<=3;i++)
    {
        SysCtl_selectCPUForPeripheral(SYSCTL_CPUSEL6_SPI, i,
                                      SYSCTL_CPUSEL_CPU2);
    }
    for (i=1;i<=2;i++)
    {
        SysCtl_selectCPUForPeripheral(SYSCTL_CPUSEL7_I2C, i,
                                      SYSCTL_CPUSEL_CPU2);
    }
    for (i=1;i<=2;i++)
    {
        SysCtl_selectCPUForPeripheral(SYSCTL_CPUSEL8_CAN, i,
                                      SYSCTL_CPUSEL_CPU2);
    }
    for (i=1;i<=2;i++)
    {
        SysCtl_selectCPUForPeripheral(SYSCTL_CPUSEL9_MCBSP, i,
                                      SYSCTL_CPUSEL_CPU2);
    }
    for (i=1;i<=4;i++)
    {
        SysCtl_selectCPUForPeripheral(SYSCTL_CPUSEL11_ADC, i,
                                      SYSCTL_CPUSEL_CPU2);
    }
    for (i=1;i<=8;i++)
    {
        SysCtl_selectCPUForPeripheral(SYSCTL_CPUSEL12_CMPSS, i,
                                      SYSCTL_CPUSEL_CPU2);
    }
    for (i=1;i<=3;i++)
    {
        SysCtl_selectCPUForPeripheral(SYSCTL_CPUSEL14_DAC, i,
                                      SYSCTL_CPUSEL_CPU2);
    }

    EDIS;

#ifdef _STANDALONE
#ifdef _FLASH
    //
    //  Send boot command (from FLASH) to allow the CPU02 application
    //  to begin execution
    //
#else
    //
    //  Send boot command (from RAM) to allow the CPU02 application
    //  to begin execution
    //
#endif
#endif

    //
    // IDLE loop. Just sit and loop forever (optional):
    //
    while(1)
    {
        asm(" nop");
    }
}

//
// End of file
//
