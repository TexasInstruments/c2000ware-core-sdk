//#############################################################################
//
// FILE:   transfer_signal_sight_basic_demo.c
//
// TITLE:  Transfer: Signal Sight Basic Demo
//
//! \addtogroup driver_example_list
//! <h1> GUI-based solution for real-time variable plotting  </h1>
//!
//! This example demonstrates how to use SysConfig to enable real-time
//! plotting of application variables in a virtual oscilloscope GUI
//!
//! For this example, you can use the already built-in
//! XDS UART or SCI to USB on a launchpad or controlCARD to view the output.
//! 
//! In this example, we are using SCI to export data out of the device and
//! plot this data in the MCU Signal Sight virtual oscilloscope tool.
//! If you're using a LaunchPad or control CARD, you can enable board components
//! to select the correct SCI GPIOs in Sysconfig under:
//! MCU Signal Sight >> Exporter >> SCI Transfer Communication Link >> PinMux
//! 
//! 1. Set GUI_SUPPORT to 1 in Project Properties >> Variables
//! 2. Build the project
//! 3. In CCS click Help >> Reload Window
//! 4. Launch the project and run
//! 5. In CCS click View >> Plugins >> myMCUSignalSight0 to launch the GUI
//! 6. Toggle on all channels and set the trigger mode to auto to
//!    plot the waveforms!
//!
//!  \note This example project has support for migration across our C2000 
//!  device families. If you are wanting to build this project from launchpad
//!  or controlCARD, please specify in the .syscfg file the board you're using.
//!  At any time you can select another device to migrate this example.
//!
//!
//
//#############################################################################
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
#include <math.h>
#include <signalsight/signalsight.h>
#include "board.h"

//
// Globals used to simulate variable changes
//
int dataIndex = 0;

#define SAMPLE_RESOLUTION 200
float sine1Snapshot[SAMPLE_RESOLUTION] = {0};
float square1Snapshot[SAMPLE_RESOLUTION] = {0};
float triangle1Snapshot[SAMPLE_RESOLUTION] = {0};
float sine2Snapshot[SAMPLE_RESOLUTION] = {0};
float square2Snapshot[SAMPLE_RESOLUTION] = {0};
float triangle2Snapshot[SAMPLE_RESOLUTION] = {0};

//
// Example Streaming Global Variables - must be float type
//
float sineWave1 = 2.2;
float squareWave1 = 0.0;
float triangleWave1 = 0.25;
float sineWave2 = 0.0;
float squareWave2 = 2.5;
float triangleWave2 = 1.5;

__interrupt void cpuTimer1ISR(void);

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
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // PinMux and Peripheral Initialization
    //
    Board_init();

    //
    // Initialize Signal Sight tool state
    //
    SIGNALSIGHT_init();

    //
    // Set up arrays of fake data for demo
    //
    float twoPi = 6.283185307f;
    int i;
    for(i = 0; i < SAMPLE_RESOLUTION; i++){

        //
        // Sine waves
        //
        sine1Snapshot[i] = sinf((i)*twoPi/SAMPLE_RESOLUTION)*3.0f;
        sine2Snapshot[i] = sinf((i)*twoPi/SAMPLE_RESOLUTION)*6.0f + 1.0f;

        //
        // Triangle waves
        //
        if(i == 0){
            triangle1Snapshot[i] = 0.0f;
            triangle2Snapshot[i] = 0.0f;
        }
        else if(i == SAMPLE_RESOLUTION-1){
            triangle1Snapshot[i] = 0.0f;
            triangle2Snapshot[i] = 0.0f;
        }
        else if(i == ((SAMPLE_RESOLUTION-1)/2)){
            triangle1Snapshot[i] = triangle1Snapshot[i-1] + 0.01f;
            triangle2Snapshot[i] = 0.0f;

        }
        else{
            triangle1Snapshot[i] = triangle1Snapshot[i-1] + 0.01f;
            triangle2Snapshot[i] = triangle2Snapshot[i-1] + 0.04f;
        } 

        //
        // Square waves
        //
        if(i < ((SAMPLE_RESOLUTION-1)/2)){
            square1Snapshot[i] = 0.0f;
            if(i < ((SAMPLE_RESOLUTION-1)/4)){
                square2Snapshot[i] = 0.0f;
            }
            else{
                square2Snapshot[i] = 2.0f;
            }
        }
        else{
            square1Snapshot[i] = 5.0f;
            if(i > ((SAMPLE_RESOLUTION-1)/4)){
                square2Snapshot[i] = 2.0f;
            }
            else{
                square2Snapshot[i] = 0.0f;
            }
        }
    }

    //
    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Start the CPU timer to beging getting periodic interrupts
    //
    CPUTimer_startTimer(myCPUTIMER0_BASE);
    
    while(1)
    {
        //
        // Send all streaming data from the temporary buffer when full
        //
        SIGNALSIGHT_sendPlotData();
    }
}

//
// cpuTimer1ISR - CpuTimer1  ISR every 1 ms
//
__interrupt void
cpuTimer1ISR(void)
{
    //
    // Update all Global variables with new data
    //
    sineWave1 = sine1Snapshot[dataIndex];
    squareWave1 = square1Snapshot[dataIndex];
    triangleWave1 = triangle1Snapshot[dataIndex];
    sineWave2 = sine2Snapshot[dataIndex];
    squareWave2 = square2Snapshot[dataIndex];
    triangleWave2 = triangle2Snapshot[dataIndex];

    //
    // Increment or wrap index for next sample
    //
    if(dataIndex == SAMPLE_RESOLUTION-1){
        dataIndex = 0;
    }
    else{
        dataIndex++;
    }

    //
    // Sample current values of the streaming variables and write them to a
    // temporary buffer
    //
    SIGNALSIGHT_capturePlotData();

    //
    // Acknowledge the CPU Timer interrupt
    //
    Interrupt_clearACKGroup(INT_myCPUTIMER0_INTERRUPT_ACK_GROUP);
    
}
//
// End of File
//
