//###########################################################################
//
//  FILE:  Example_2803xHRPWM_Symmetric_Duty_Cylcle_SFO_V6.c
//
//  TITLE: High Resolution PWM Symmetric Duty Cycle SFO V6 example
//
//!  \addtogroup f2803x_example_list
//!  <h1>High Resolution PWM Symmetric Duty Cycle SFO V6
//!  (Up-Down Count) </h1>
//!
//!  This example modifies the MEP control registers to show edge displacement
//!  for high-resolution period/frequency on two ePWM channels 
//!  (ePWM 1 and ePWM 2) in Up-Down count mode due to the HRPWM control 
//!  extension of the respective ePWM module.
//!
//!  All period and compare register updates occur in an ISR which interrupts 
//!  at ePWM1 TBCTR = 0. This ensures that period and compare register updates
//!  across all ePWM modules occur within the same period.
//!  This example calls the following TI's MEP Scale Factor Optimizer (SFO)
//!  software library V6 functions:
//!
//!  \b int \b SFO();
//!  - updates MEP_ScaleFactor dynamically when HRPWM is in use
//!  - updates HRMSTEP register (exists only in EPwm1Regs register space
//!    but valid for all channels)
//!  with MEP_ScaleFactor value
//!  - \b Returns
//!    - 2 if error: MEP_ScaleFactor is greater than maximum value of 255
//!      (Auto-conversion may not function properly under this condition)
//!    - 1 when complete for the specified channel
//!    - 0 if not complete for the specified channel
//!
//!  Channels ePWM1A and ePWM2A will have fine edge movement due to the HRPWM
//!  logic when the duty cycle is altered.
//!  Channels ePWM1B and ePWM2B have a fixed 50% duty cycle.
//!
//!  \note
//!  - This program requires the DSP2803x header files, which include
//!  the following files required for this example:
//!  SFO_V6.h and SFO_TI_Build_V6.lib
//!  - For more information on using the SFO software library, see the
//!  2803x High-Resolution Pulse Width Modulator (HRPWM) Reference Guide
//!
//!  \b External \b Connections \n
//!  - Monitor ePWM1A, ePWM1B, ePWM2A and ePWM2B (GPIO0-GPIO3) pins on an 
//!    oscilloscope.
//!
//
//###########################################################################
// $TI Release:
// $Release Date:
//###########################################################################

//
// Included Files
//
#include "DSP28x_Project.h"         // DSP280xx Headerfile
#include "SFO_V6.h"

//
//                          IMPORTANT
// UPDATE NUMBER OF HRPWM CHANNELS + 1  USED IN SFO_V6.H
// Configured for 4 HRPWM channels, but F2803x has a maximum of 
// 7 HRPWM channels (8=7+1)
// i.e.: #define PWM_CH 5   
//

//
// Function Prototypes
//
void HRPWM_Config(int);
void error(void);
__interrupt void FreqCtlISR(void);  // frequency modulation & phase sync ISR

//
// Globals - useful for debug
//
Uint16 status;
Uint16 CMP_Reg = 20;
Uint16 CMP_HR = 0;
Uint16 PRD_Reg = 40;
Uint16 PRD_HR = 0;
Uint16 update = 0;
Uint16 isr_cnt = 0;
Uint16 change_dir = 1;
Uint16 update_rate = 10000;
Uint16 CMP_Inc = 0;
Uint16 CMP_HR_INC = 0;
Uint32 InputCMPInc = 2621;
int32 CMP_HR_temp = 0;
Uint16 Period = 50;

//
// The following declarations are required in order to use the SFO
// library functions:
//

//
// Global variable used by the SFO library. Result can be used for all 
// HRPWM channels. This variable is also copied to HRMSTEP register by SFO(0) 
// function.
//
int MEP_ScaleFactor;

//
// Array of pointers to EPwm register structures:
// *ePWM[0] is defined as dummy value not used in the example
//
volatile struct EPWM_REGS *ePWM[PWM_CH] =
             {  &EPwm1Regs, &EPwm1Regs, &EPwm2Regs, &EPwm3Regs, &EPwm4Regs};
//

//
// Main
//
void main(void)
{
    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the DSP2803x_SysCtrl.c file.
    //
    InitSysCtrl();

    //
    // Step 2. Initialize GPIO:
    // This example function is found in the DSP2803x_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    //
    // InitGpio();  // Skipped for this example
    InitEPwmGpio();

    //
    // Step 3. Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    //
    DINT;

    //
    // Initialize the PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the DSP2803x_PieCtrl.c file.
    //
    InitPieCtrl();

    //
    // Disable CPU interrupts and clear all CPU interrupt flags:
    //
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table, even if the interrupt
    // is not used in this example.  This is useful for debug purposes.
    // The shell ISR routines are found in DSP2803x_DefaultIsr.c.
    // This function is found in DSP2803x_PieVect.c.
    //
    InitPieVectTable();

    //
    // Step 4. Initialize all the Device Peripherals:
    // Not required for this example
    //

    //
    // For this example, only initialize the ePWM
    // Step 5. User specific code, enable interrupts:
    //
    EALLOW;
    PieVectTable.EPWM1_INT = &FreqCtlISR;
    EDIS;

    status = SFO_INCOMPLETE;

    //
    // Calling SFO() updates the HRMSTEP register with calibrated 
    // MEP_ScaleFactor. HRMSTEP must be populated with a scale factor value 
    // prior to enabling high resolution period control.
    //
    while  (status== SFO_INCOMPLETE)
    {
        status = SFO();
        if (status == SFO_ERROR)
        {
            //
            // SFO function returns 2 if an error occurs & # of 
            // MEP steps/coarse step
            //
            error();
        }
    }

    //
    // Some useful PWM period vs Frequency values
    //  TBCLK = 60 MHz
    //
    //  Period   Freq
    //  1000     30 KHz
    //  800    37.5 KHz
    //  600      50 KHz
    //  500      60 KHz
    //  250     120 KHz
    //  200     150 KHz
    //  100     300 KHz
    //  50      600 KHz
    //  30        1 MHz
    //  25      1.2 MHz
    //  20      1.5 MHz
    //  12      2.5 MHz
    //  10        3 MHz
    //  9       3.3 MHz
    //  8       3.8 MHz
    //  7       4.3 MHz
    //  6       5.0 MHz
    //  5       6.0 MHz
    //

    //
    // ePWM and HRPWM register initialization
    //
    HRPWM_Config(Period);

    //
    // configure ePWM1 to generate interrupts on period match
    //
    EPwm1Regs.ETSEL.bit.INTSEL = 1;     // interrupt on counter zero match
    EPwm1Regs.ETSEL.bit.INTEN = 1;      // enable peripheral interrupt
    EPwm1Regs.ETPS.bit.INTPRD = 1;      // generate interrupt on every event
    PieCtrlRegs.PIEIER3.bit.INTx1 = 1;  // enable ePWM1 interrupt in PIE
    IER |= 0x0004;                      // enable core INT #3
    EINT;                               // clear global interrupt mask

    for(;;)
    {
        if (isr_cnt >= update_rate)
        {
            if (CMP_Reg < (PRD_Reg-4) && change_dir == 1)   // Increment CMP
            {
                CMP_Inc = InputCMPInc >> 16;
                CMP_HR_INC = (Uint16) InputCMPInc;
                CMP_Reg = CMP_Reg+CMP_Inc;
                CMP_HR_temp = (Uint32)CMP_HR + (Uint32)CMP_HR_INC;

                if(CMP_HR_temp>=0x10000)
                {
                    CMP_HR_temp = CMP_HR_temp-0x10000;
                    CMP_Reg = CMP_Reg+1;
                }

                CMP_HR = (Uint16) CMP_HR_temp;
            }
            else
            {
                change_dir = 0;                     // Decrement CMP
            }
            if (CMP_Reg > 4 && change_dir == 0)     // Decrement CMP
            {
                CMP_Inc = InputCMPInc >> 16;
                CMP_HR_INC = (Uint16) InputCMPInc;
                CMP_Reg = CMP_Reg-CMP_Inc;
                CMP_HR_temp = (int32)CMP_HR - (int32)CMP_HR_INC;

                if(CMP_HR_temp < 0)
                {
                    CMP_HR_temp = 0x10000 + CMP_HR_temp;
                    CMP_Reg = CMP_Reg-1;
                }

                CMP_HR = (Uint16) CMP_HR_temp;
            }
            else
            {
                change_dir = 1;                     // Increment CMP
            }
            update = 1;
            isr_cnt = 0;
        }
    }
}

//
// HRPWM_Config - Configures all ePWM channels and sets up HRPWM on ePWMxA 
// channels. Paramters are the period - desired PWM period in TBCLK counts
//
void 
HRPWM_Config(period)
{
    Uint16 j;
    
    //
    // ePWM channel register configuration with HRPWM
    // ePWMxA toggle low/high with MEP control on Rising edge
    //
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;     // Disable TBCLK within the EPWM
    EDIS;

    for (j=1;j<3;j++)
    {
        (*ePWM[j]).TBCTL.bit.PRDLD = TB_SHADOW; // set Shadow load
        (*ePWM[j]).TBPRD = period;              // PWM frequency = 1/(2*TBPRD)
        (*ePWM[j]).CMPA.half.CMPA = period / 2; // set duty 50% initially
        (*ePWM[j]).CMPA.half.CMPAHR = (0 << 8); // initialize HRPWM extension
        (*ePWM[j]).TBPHS.all = 0;

        (*ePWM[j]).TBCTR = 0;

        //
        // Select up-down count mode
        //
        (*ePWM[j]).TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;    
        
        (*ePWM[j]).TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
        (*ePWM[j]).TBCTL.bit.HSPCLKDIV = TB_DIV1;
        (*ePWM[j]).TBCTL.bit.CLKDIV = TB_DIV1;          // TBCLK = SYSCLKOUT
        (*ePWM[j]).TBCTL.bit.FREE_SOFT = 0;

        (*ePWM[j]).CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;  // LOAD CMPA on CTR = 0
        (*ePWM[j]).CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
        (*ePWM[j]).CMPCTL.bit.SHDWAMODE = CC_SHADOW;
        (*ePWM[j]).CMPCTL.bit.SHDWBMODE = CC_SHADOW;

        (*ePWM[j]).AQCTLA.bit.CAU = AQ_SET;       // PWM toggle high/low
        (*ePWM[j]).AQCTLA.bit.CAD = AQ_CLEAR;
        (*ePWM[j]).AQCTLB.bit.ZRO = AQ_SET;       // PWM toggle high/low
        (*ePWM[j]).AQCTLB.bit.PRD = AQ_CLEAR;
        EALLOW;
        (*ePWM[j]).HRCNFG.all = 0x0;
        (*ePWM[j]).HRCNFG.bit.EDGMODE = HR_BEP;    // MEP control on both edges
        
        //
        // CMPAHR and TBPRDHR HR control
        //
        (*ePWM[j]).HRCNFG.bit.CTLMODE = HR_CMP;     
        
        //
        // load on CTR = 0 and CTR = TBPRD
        //
        (*ePWM[j]).HRCNFG.bit.HRLOAD  = HR_CTR_ZERO_PRD; 
        
        //
        // Enable autoconversion for HR period
        //
        (*ePWM[j]).HRCNFG.bit.AUTOCONV = 1;              
        
        //
        // Turn on high-resolution period control
        //
        (*ePWM[j]).HRPCTL.bit.HRPE = 1;                  
        
        (*ePWM[j]).TBCTL.bit.PHSEN = 1;
        
        //
        // Enable TBPHSHR sync (required for updwn count HR control)
        //
        (*ePWM[j]).HRPCTL.bit.TBPHSHRLOADE = 1;
        EDIS;
    }
    
    EALLOW;
    
    //
    // disable ePWM1 SYNC output [3]
    //
    EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;	
    
    EPwm2Regs.TBCTL.bit.PHSEN = 1;
    EPwm2Regs.TBCTL.bit.PHSDIR = 1;     // count up after SYNC event
    
    //
    // initial - coarse phase offset relative to ePWM1
    //
    EPwm2Regs.TBPHS.half.TBPHS = 2;

    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;  // Enable TBCLK within the EPWM
    
    //
    // Synchronize high resolution phase to start HR period
    //
    EPwm1Regs.TBCTL.bit.SWFSYNC = 1;            

    EDIS;
}

//
// FreqCtlISR - interrupts at ePWM1 TBCTR = 0. This ISR updates the compare and
// period registers for ePWM modules within the same period.
//
__interrupt void 
FreqCtlISR(void)
{
    EALLOW;
    EPwm2Regs.TBCTL.bit.PHSEN = 0;
    EDIS;

    isr_cnt++;

    if (update == 1)
    {
        EPwm1Regs.CMPA.half.CMPA = CMP_Reg;
        EPwm1Regs.CMPA.half.CMPAHR = CMP_HR;  // change duty cycle

        EPwm2Regs.CMPA.half.CMPA = CMP_Reg;  
        EPwm2Regs.CMPA.half.CMPAHR = CMP_HR;  // change duty cycle

        update = 0;
    }

    //
    // re-initialise for next PWM interrupt
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;   // acknowledge PIE interrupt

    EPwm1Regs.ETCLR.bit.INT = 1;              // clear interrupt bit
}

//
// error - Error handling function
//
void 
error (void)
{
    ESTOP0;         // Stop here and handle error
}

//
// End of File
//

