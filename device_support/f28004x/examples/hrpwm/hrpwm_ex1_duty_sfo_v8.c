//#############################################################################
//
// FILE:    hrpwm_ex1_duty_sfo_v8.c
//
// TITLE:   HRPWM SFO V8 High-Resolution Period
//          (Up Count) example
//
//! \addtogroup bitfield_example_list
//! <h1>HRPWM Duty Up Count</h1>
//!
//! This example modifies the MEP control registers to show edge displacement
//! for high-resolution period with ePWM in Up count mode
//! due to the HRPWM control extension of the respective ePWM module.
//!
//! This example calls the following TI's MEP Scale Factor Optimizer (SFO)
//! software library V8 functions:
//!
//! \b int \b SFO(); \n
//! updates MEP_ScaleFactor dynamically when HRPWM is in use
//! updates HRMSTEP register (exists only in EPwm1Regs register space)
//! with MEP_ScaleFactor value
//! - returns 2 if error: MEP_ScaleFactor is greater than maximum value of 255
//!   (Auto-conversion may not function properly under this condition)
//! - returns 1 when complete for the specified channel
//! - returns 0 if not complete for the specified channel
//!
//! This example is intended to explain the HRPWM capabilities. The code can be
//! optimized for code efficiency. Refer to TI's Digital power application
//! examples and TI Digital Power Supply software libraries for details.
//!
//! To run this example:
//! -# Run this example at maximum SYSCLKOUT
//! -# Activate Real time mode
//! -# Run the code
//!
//! \b External \b Connections \n
//!  - Monitor ePWM1 A/B pins on an oscilloscope.
//!
//! \b Watch \b Variables \n
//!  - status - Example run status
//!  - UpdateFine - Set to 1 use HRPWM capabilities and observe in fine MEP
//!                 steps(default)
//!                 Set to 0 to disable HRPWM capabilities and observe in
//!                 coarse SYSCLKOUT cycle steps
//!
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com/
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
#include "F28x_Project.h"
#include "SFO_V8.h"

//
// Defines
//
#define PWM_CH            2       // # of PWM channels - 1
#define STATUS_SUCCESS    1
#define STATUS_FAIL       0
#define AUTOCONVERT       0       // 1 = Turn auto-conversion ON
                                  // 0 = Turn auto-conversion OFF

//
// Globals
//
uint16_t UpdateFine;
uint16_t DutyFine;
uint16_t status;
uint16_t CMPA_reg_val;
uint16_t CMPAHR_reg_val;
uint16_t CMPB_reg_val;
uint16_t CMPBHR_reg_val;
int MEP_ScaleFactor; // Global variable used by the SFO library
                     // Result can be used for all HRPWM channels
                     // This variable is also copied to HRMSTEP
                     // register by SFO() function.

// Used by SFO library (ePWM[0] is a dummy value that isn't used)
volatile struct EPWM_REGS *ePWM[PWM_CH] = {&EPwm1Regs, &EPwm1Regs};

//
// Function Prototypes
//
void initHRPWM1GPIO(void);
void configHRPWM(uint16_t period);
void error(void);

//
// Main
//
void main(void)
{
    uint16_t i;
    uint32_t temp, temp1;

    //
    // Initialize device clock and peripherals
    //
    InitSysCtrl();

    //
    // Initialize GPIO
    //
    InitGpio();
    initHRPWM1GPIO();

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    DINT;
    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    InitPieVectTable();

    //
    // Setup example variables
    //
    UpdateFine = 1;
    DutyFine = 0;
    status = SFO_INCOMPLETE;

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // ePWM and HRPWM register initialization
    //
    for(i=1; i<PWM_CH; i++)
    {
        // Change clock divider to /1
        // (PWM clock needs to be > 60MHz)
        (*ePWM[i]).TBCTL.bit.HSPCLKDIV = 0;
    }
    configHRPWM(10);  
    
    //
    // Calling SFO() updates the HRMSTEP register with calibrated
    // MEP_ScaleFactor. HRMSTEP must be populated with a scale factor value
    // prior to enabling high resolution period control.
    //
    while(status == SFO_INCOMPLETE)
    {
        status = SFO();
        if(status == SFO_ERROR)
        {
            error();   // SFO function returns 2 if an error occurs & # of MEP
        }              // steps/coarse step exceeds maximum of 255.
    }

    EALLOW;

    for(;;)
    {
        //
        // Sweep DutyFine as a Q15 number from 0.2 - 0.999
        //
        for(DutyFine = 0x199A; DutyFine < 0x7FDF; DutyFine++)
        {

            if(UpdateFine)
            {
                /*
                // all below calculation apply for CMPB as well
                // CMPA_reg_val , CMPA_reg_val is calculated as a Q0.
                // Since DutyFine is a Q15 number, and the period is Q0
                // the product is Q15. So to store as a Q0, we shift right
                // 15 bits.

                CMPA_reg_val = ((long)DutyFine * (EPwm1Regs.TBPRD + 1)) >> 15;

                // This next step is to obtain the remainder which was
                // truncated during our 15 bit shift above.
                // compute the whole value, and then subtract CMPA_reg_val
                // shifted LEFT 15 bits:
                temp = ((long)DutyFine * (EPwm1Regs.TBPRD + 1)) ;
                temp = temp - ((long)CMPA_reg_val<<15);

                // If auto-conversion is disabled, the following step can be
                // skipped. If autoconversion is enabled, the SFO function will
                // write the MEP_ScaleFactor to the HRMSTEP register and the
                // hardware will automatically scale the remainder in the
                // CMPAHR register by the MEP_ScaleFactor.
                // Because the remainder calculated above (temp) is in Q15
                // format, it must be shifted left by 1 to convert to Q16
                // format for the hardware to properly convert.
                CMPAHR_reg_val = temp<<1;

                // If auto-conversion is enabled, the following step is
                // performed automatically in hardware and can be skipped
                // This obtains the MEP count in digits, from
                // 0,1, .... MEP_Scalefactor.
                // 0x0080 (0.5 in Q8) is converted to 0.5 in Q15 by shifting
                // left 7. This is added to fractional duty*MEP_SF product in
                // order to round the decimal portion of the product up to the
                // next integer if the decimal portion is >=0.5.
                //
                //Once again since this is Q15
                // convert to Q0 by shifting:
                CMPAHR_reg_val = (temp*MEP_ScaleFactor+(0x0080<<7))>>15;

                // If auto-conversion is enabled, the following step is
                // performed automatically in hardware and can be skipped
                // Now the lower 8 bits contain the MEP count.
                // Since the MEP count needs to be in the upper 8 bits of
                // the 16 bit CMPAHR register, shift left by 8.
                CMPAHR_reg_val = CMPAHR_reg_val << 8;

                // If auto-conversion is enabled, the following step is
                // performed automatically in hardware and can be skipped
                // Add the offset and rounding
                CMPAHR_reg_val += 0x0080;

                // Write the values to the registers as one 32-bit
                // or two 16-bits
                EPwm1Regs.CMPA.bit.CMPA = CMPA_reg_val;
                EPwm1Regs.CMPA.bit.CMPAHR = CMPAHR_reg_val;
                */

                //
                // All the above operations may be condensed into
                // the following form:
                // EPWM1 calculations
                //
                for(i=1; i<PWM_CH; i++)
                {
                    CMPA_reg_val = ((long)DutyFine * ((*ePWM[i]).TBPRD + 1)) >> 15;
                    CMPB_reg_val = ((long)DutyFine * ((*ePWM[i]).TBPRD + 1)) >> 15;
                    temp = ((long)DutyFine * ((*ePWM[i]).TBPRD + 1)) ;
                    temp1 = ((long)DutyFine * ((*ePWM[i]).TBPRD + 1)) ;
                    temp = temp - ((long)CMPA_reg_val << 15);
                    temp1 = temp1 - ((long)CMPB_reg_val << 15);

                   #if(AUTOCONVERT)
                    CMPAHR_reg_val = temp << 1; // convert to Q16
                    CMPBHR_reg_val = temp << 1; // convert to Q16
                   #else
                    CMPAHR_reg_val = ((temp * MEP_ScaleFactor) +
                                      (0x0080 << 7)) >> 15;
                    CMPAHR_reg_val = CMPAHR_reg_val << 8;
                    CMPBHR_reg_val = ((temp1 * MEP_ScaleFactor) +
                                      (0x0080 << 7)) >> 15;
                    CMPBHR_reg_val = CMPBHR_reg_val << 8;
                   #endif

                   //
                   // Example for a 32 bit write to CMPA:CMPAHR
                   //
                    (*ePWM[i]).CMPA.all = ((long)CMPA_reg_val) << 16 |
                                          CMPAHR_reg_val; // loses lower 8-bits
                   //
                   // Example for a 32 bit write to CMPB:CMPBHR
                   //
                    (*ePWM[i]).CMPB.all = ((long)CMPB_reg_val) << 16 |
                                          CMPBHR_reg_val; // loses lower 8-bits
                }
            }
            else
            {
                //
                // CMPA_reg_val is calculated as a Q0.
                // Since DutyFine is a Q15 number, and the period is Q0
                // the product is Q15. So to store as a Q0, we shift right
                // 15 bits.
                //
                for(i=1; i<PWM_CH; i++)
                {
                    (*ePWM[i]).CMPA.bit.CMPA = (((long)DutyFine *
                                                ((*ePWM[i]).TBPRD + 1)) >> 15);
                    (*ePWM[i]).CMPB.bit.CMPB = (((long)DutyFine *
                                                ((*ePWM[i]).TBPRD + 1)) >> 15);
                }
            }

            //
            // Call the scale factor optimizer lib function SFO()
            // periodically to track for any change due to temp/voltage.
            // This function generates MEP_ScaleFactor by running the
            // MEP calibration module in the HRPWM logic. This scale
            // factor can be used for all HRPWM channels. The SFO()
            // function also updates the HRMSTEP register with the
            // scale factor value.
            //
            status = SFO(); // in background, MEP calibration module
                            // continuously updates MEP_ScaleFactor

            if (status == SFO_ERROR)
            {
                error();   // SFO function returns 2 if an error occurs & #
                           // of MEP steps/coarse step exceeds maximum of 255.
            }
        } // end DutyFine for loop
    } // end infinite for loop
}

//
// configHRPWM - Configures all ePWM channels and sets up HRPWM
//                on ePWMxA / ePWMxB  channels
//
void configHRPWM(uint16_t period)
{
    uint16_t j;

    for (j=1;j<PWM_CH;j++)
    {
        (*ePWM[j]).TBCTL.bit.PRDLD = TB_SHADOW;  // set Immediate load
        (*ePWM[j]).TBPRD = period-1;             // PWM frequency = 1 / period
        (*ePWM[j]).CMPA.bit.CMPA = period / 2;   // set duty 50% initially
        (*ePWM[j]).CMPA.bit.CMPAHR = (1 << 8);   // initialize HRPWM extension
        (*ePWM[j]).CMPB.bit.CMPB = period / 2;   // set duty 50% initially
        (*ePWM[j]).CMPB.all |= (1 << 8);         // initialize HRPWM extension
        (*ePWM[j]).TBPHS.all = 0;
        (*ePWM[j]).TBCTR = 0;

        (*ePWM[j]).TBCTL.bit.CTRMODE = TB_COUNT_UP;
        (*ePWM[j]).TBCTL.bit.PHSEN = TB_DISABLE;
        (*ePWM[j]).TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
        (*ePWM[j]).TBCTL.bit.HSPCLKDIV = TB_DIV1;
        (*ePWM[j]).TBCTL.bit.CLKDIV = TB_DIV1;
        (*ePWM[j]).TBCTL.bit.FREE_SOFT = 11;

        (*ePWM[j]).CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
        (*ePWM[j]).CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
        (*ePWM[j]).CMPCTL.bit.SHDWAMODE = CC_SHADOW;
        (*ePWM[j]).CMPCTL.bit.SHDWBMODE = CC_SHADOW;

        (*ePWM[j]).AQCTLA.bit.ZRO = AQ_SET;      // PWM toggle high/low
        (*ePWM[j]).AQCTLA.bit.CAU = AQ_CLEAR;
        (*ePWM[j]).AQCTLB.bit.ZRO = AQ_SET;
        (*ePWM[j]).AQCTLB.bit.CBU = AQ_CLEAR;

        EALLOW;
        (*ePWM[j]).HRCNFG.all = 0x0;
        (*ePWM[j]).HRCNFG.bit.EDGMODE = HR_FEP;  // MEP control on falling edge
        (*ePWM[j]).HRCNFG.bit.CTLMODE = HR_CMP;
        (*ePWM[j]).HRCNFG.bit.HRLOAD  = HR_CTR_ZERO;
        (*ePWM[j]).HRCNFG.bit.EDGMODEB = HR_FEP; // MEP control on falling edge
        (*ePWM[j]).HRCNFG.bit.CTLMODEB = HR_CMP;
        (*ePWM[j]).HRCNFG.bit.HRLOADB  = HR_CTR_ZERO;
        #if (AUTOCONVERT)
        (*ePWM[j]).HRCNFG.bit.AUTOCONV = 1;     // Enable auto-conversion
                                                // logic
        #endif
        (*ePWM[j]).HRPCTL.bit.HRPE = 0; // Turn off high-resolution period
                                        // control.
        EDIS;
    }
}

//
// initHRPWM1GPIO - Initialize HRPWM1 GPIOs
//
void initHRPWM1GPIO(void)
{
    EALLOW;

    //
    // Disable internal pull-up for the selected output pins
    // for reduced power consumption
    // Pull-ups can be enabled or disabled by the user.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1;    // Disable pull-up on GPIO0 (EPWM1A)
    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1;    // Disable pull-up on GPIO1 (EPWM1B)

    //
    // Configure EPWM-1 pins using GPIO regs
    // This specifies which of the possible GPIO pins will be EPWM1 functional
    // pins.
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;   // Configure GPIO0 as EPWM1A
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;   // Configure GPIO1 as EPWM1B

    EDIS;
}

//
// error - Halt debugger when called
//
void error(void)
{
    ESTOP0;         // Stop here and handle error
}

//
// End of file
//

