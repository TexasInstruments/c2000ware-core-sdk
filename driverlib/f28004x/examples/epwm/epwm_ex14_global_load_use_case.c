//#############################################################################
//
// FILE:   epwm_ex14_global_load_use_case.c
//
// TITLE:  Use Case Example Code for EPWM Developers Guide
//
//
// This example contains the solution for the use case described in the
// C2000 ePWM Developer's Guide (www.ti.com/lit/SPRAD12).
//
// The use case described in the application report is the following:
//
// Output frequency of 400 kHz for EPWM1/2/3
// Phase shift of 120 degrees for EPWM2 with respect to EPWM1
// Phase shift of 240 degrees for EPWM3 with respect to EPWM1
// Duty cycle of 45% for EPWM1/2/3
// Active high complementary signal pairs with 200 nsec of rising/falling edge delay for EPWM1/2/3
// Cycle-by-Cycle trip zone protection through comparator signal on EPWM2
// One-Shot trip protection through GPIO on EPWM3
// Interrupt generation everytime the time base counter equals zero on EPWM1
// Global loading to support asynchronous updates of action qualifier settings
// Link CMPA/CMPB of EPWM1 to EPWM2 and EPWM3
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
#include "board.h"

//
// Globals
//
uint16_t  perform_one_shot_load=0;

//
// Function Prototypes
//
__interrupt void INT_myEPWM1_ISR(void);
__interrupt void INT_myEPWM2_TZ_ISR(void);
__interrupt void INT_myEPWM3_TZ_ISR(void);

//
// Main
//
void main(void)
{
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
      // Disable sync(Freeze clock to PWM as well)
      //
      SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

      //
      // Configure ePWM1, ePWM2, and TZ GPIOs
      //
      Board_init();

      //
      // Workaround for Global Loading feature in SysConfig version 1.11 or below
      // Un-comment the following section for a SysConfig version of 1.11 or below (CCS v11 & C2000Ware version 4.01.00.00)
      //
      /*
      EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
      EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
      EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
      EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);

      EPWM_setActionQualifierAction(myEPWM2_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
      EPWM_setActionQualifierAction(myEPWM2_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
      EPWM_setActionQualifierAction(myEPWM2_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
      EPWM_setActionQualifierAction(myEPWM2_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);

      EPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
      EPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
      EPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
      EPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);


      // EPWM1, EPWM2, EPWM3 are linked so this will update both
      EPWM_setGlobalLoadOneShotLatch(myEPWM1_BASE);
      */

      //
      // Enable sync and clock to PWM
      //
      SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

      //
      // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
      //
      EINT;
      ERTM;

      //
      // IDLE loop. Just sit and loop forever (optional):
      //
      for(;;)
      {

          if(perform_one_shot_load==1)
          {
              //
              // EPWM1, EPWM2, EPWM3 are linked so only EPWM1 needs to be updated
              //
              EPWM_setCounterCompareValue(myEPWM1_BASE, EPWM_COUNTER_COMPARE_A, 100);
              EPWM_setCounterCompareValue(myEPWM1_BASE, EPWM_COUNTER_COMPARE_B, 100);

              //
              // Change the Action Qualifier Settings for EPWM1, EPWM2, and EPWM3
              //
              EPWM_setActionQualifierAction(myEPWM1_BASE,EPWM_AQ_OUTPUT_A,EPWM_AQ_OUTPUT_LOW,
                                            EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
              EPWM_setActionQualifierAction(myEPWM1_BASE,EPWM_AQ_OUTPUT_A,EPWM_AQ_OUTPUT_HIGH,
                                            EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
              EPWM_setActionQualifierAction(myEPWM2_BASE,EPWM_AQ_OUTPUT_A,EPWM_AQ_OUTPUT_LOW,
                                            EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
              EPWM_setActionQualifierAction(myEPWM2_BASE,EPWM_AQ_OUTPUT_A,EPWM_AQ_OUTPUT_HIGH,
                                                          EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
              EPWM_setActionQualifierAction(myEPWM3_BASE,EPWM_AQ_OUTPUT_A,EPWM_AQ_OUTPUT_LOW,
                                            EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
              EPWM_setActionQualifierAction(myEPWM3_BASE,EPWM_AQ_OUTPUT_A,EPWM_AQ_OUTPUT_HIGH,
                                            EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);

              // EPWM1, EPWM2, EPWM3 are linked
              EPWM_setGlobalLoadOneShotLatch(myEPWM1_BASE);

              // Clear the setting
              perform_one_shot_load = 0;
          }
      }
}


void INT_myEPWM1_ISR(void){
    //
    // Acknowledge this interrupt to receive more interrupts from group 2
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP2);
}

void INT_myEPWM2_TZ_ISR(void){

     //
     // Clear the flags
     //
     EPWM_clearTripZoneFlag(myEPWM2_BASE, (EPWM_TZ_INTERRUPT | EPWM_TZ_FLAG_CBC));

     //
     // Acknowledge this interrupt to receive more interrupts from group 2
     //
     Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP2);
}

void INT_myEPWM3_TZ_ISR(void){

    //
    // Re-enable the OST Interrupt
    //
     EPWM_clearTripZoneFlag(myEPWM3_BASE, (EPWM_TZ_INTERRUPT | EPWM_TZ_FLAG_OST));

    //
    // Acknowledge this interrupt to receive more interrupts from group 2
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP2);
}

//
// End of File
//

