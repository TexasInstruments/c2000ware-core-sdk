//#############################################################################
//
//  File:   f2802x_examples/LED_Boost_PC/LED_Boost_PC_Main.c
//
//  Title:  PC GUI Controlled LED Lighting Demo.
//
//  Group:          C2000
//  Target Device:  TMS320F2802x
//
//! \addtogroup example_list
//!  <h1>LED BoosterPack PC GUI Demo</h1>
//!
//!   This example allows the user to control the LED Boosterpack's color and
//!   intensity via a GUI application on a host PC.
//!
//!   For this example to work S4 on the C2000 LaunchPad should be in the up
//!   position, while S1 on the LED Boosterpack should be in the down position.
//!
//!   This example uses the same control techniques used in the other LED
//!   BoosterPack examples and uses a serial communications link to communicate
//!   with a PC Gui application to allow for control of the BoosterPack's LEDs.
//!
//!   After loading and running this example, open up the PC GUI application and
//!   connect to the XDS100's USB/Serial Port.  Move the slides to turn on and
//!   off the LEDs and adjust the color.
//
//
//#############################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:
// Copyright (C) 2009-2023 Texas Instruments Incorporated - http://www.ti.com/
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
#include "DSP28x_Project.h"
#include "LED_Boost_PC_Settings.h"
#include "f2802x_epwm_defines.h"

#include "DPlib.h"
#include "IQmathLib.h"

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// FUNCTION PROTOTYPES
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// -------------------------------- FRAMEWORK ---------------------------------
void DeviceInit(void);
#ifdef FLASH        
void InitFlash();
#endif
void SCIA_Init();
void SerialHostComms();

//
// State Machine function prototypes
//

//
// Alpha states
//
void A0(void);    //state A0
void B0(void);    //state B0
void C0(void);    //state C0

//
// A branch states
//
void A1(void);    //state A1
void A2(void);    //state A2

//
// B branch states
//
void B1(void);    //state B1
void B2(void);    //state B2

//
// C branch states
//
void C1(void);    //state C1
void C2(void);    //state C2

//
// Variable declarations
//
void (*Alpha_State_Ptr)(void);   // Base States pointer
void (*A_Task_Ptr)(void);        // State pointer A branch
void (*B_Task_Ptr)(void);        // State pointer B branch
void (*C_Task_Ptr)(void);        // State pointer C branch

// ---------------------------------- USER ------------------------------------
void ADC_SOC_CNF(int ChSel[], int Trigsel[], int ACQPS[], int IntChSel, 
                 int mode);
void PWM_1ch_UpDwnCnt_CNF(int16 n, int16 period, int16 mode, int16 phase);
void PWM_DualUpDwnCnt_CNF(int16 n, int16 Period, int16 Mode, int16 Phase);

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// VARIABLE DECLARATIONS - GENERAL
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// -------------------------------- FRAMEWORK ---------------------------------

//
// Virtual Timers slaved off CPU Timer 0 (A events)
//
int16    VTimer0[4]={0,0,0,0};  

//
// Virtual Timers slaved off CPU Timer 1 (B events)
//
int16    VTimer1[4]={0,0,0,0};         

//
// Virtual Timers slaved off CPU Timer 2 (C events)
//
int16    VTimer2[4]={0,0,0,0};         

int16    SerialCommsTimer=0;
int16     CommsOKflg=0;

// ---------------------------------- USER ------------------------------------
int16    Gui_LEDPrd=1000;
int16    temp_LEDDelay=0;

//
// C address variables for use with ASM module terminals
//

//
// used as consecutive addresses for ADC_Rslts
//
long    AdcNetBus[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
long    VinNetBus=0;               // used as address for Vin

long    IrefNetBus1=0;             // used as address for Iref1
long    UoutNetBus1=0;             // used as address for Uout1
#pragma DATA_SECTION(CNTL_2P2Z_CoefStruct1, "CNTL_2P2Z_Coef");
struct CNTL_2P2Z_CoefStruct CNTL_2P2Z_CoefStruct1;

long    IrefNetBus2=0;             // used as address for Iref2
long    UoutNetBus2=0;             // used as address for Uout2
#pragma DATA_SECTION(CNTL_2P2Z_CoefStruct2, "CNTL_2P2Z_Coef");
struct CNTL_2P2Z_CoefStruct CNTL_2P2Z_CoefStruct2;

long    IrefNetBus3=0;             // used as address for Iref3
long    UoutNetBus3=0;             // used as address for Uout3
#pragma DATA_SECTION(CNTL_2P2Z_CoefStruct3, "CNTL_2P2Z_Coef");
struct CNTL_2P2Z_CoefStruct CNTL_2P2Z_CoefStruct3;

//
// ASM module terminal pointers
// Boost channel 1 terminal pointers
//
extern long    *ADCDRV_1ch_Rlt1;
extern long    *CNTL_2P2Z_Ref1, *CNTL_2P2Z_Fdbk1, *CNTL_2P2Z_Out1;
extern long    *CNTL_2P2Z_Coef1;
extern long    *PWMDRV_DualUpDwnCnt_Duty1A;

//
// Boost channel 2 terminal pointers
//
extern long    *ADCDRV_1ch_Rlt2;
extern long    *CNTL_2P2Z_Ref2, *CNTL_2P2Z_Fdbk2, *CNTL_2P2Z_Out2;
extern long    *CNTL_2P2Z_Coef2;
extern long    *PWMDRV_DualUpDwnCnt_Duty1B;

//
// Boost channel 3 terminal pointers
//
extern long    *ADCDRV_1ch_Rlt3;
extern long    *CNTL_2P2Z_Ref3, *CNTL_2P2Z_Fdbk3, *CNTL_2P2Z_Out3;
extern long    *CNTL_2P2Z_Coef3;
extern long    *PWMDRV_1ch_UpDwnCnt_Duty2;

//
// Voltage terminal pointers
//
extern long    *ADCDRV_1ch_Rlt9;
extern long    *ADCDRV_1ch_Rlt10;
extern long    *ADCDRV_1ch_Rlt11;
extern long    *ADCDRV_1ch_Rlt12;

//
// ADC configuration variables
//
int16    ChSel[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int16    TrigSel[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int16    ACQPS[16]={6,25,25,25,6,6,6,6,6,6,6,6,6,6,6,6};

//
// Used to indirectly access all EPWM modules
//
volatile struct EPWM_REGS *ePWM[] = 
                  { &EPwm1Regs,         //intentional: (ePWM[0] not used)
                    &EPwm1Regs,
                    &EPwm2Regs,
                    &EPwm3Regs,
                    &EPwm4Regs
                  };
//
// Slew control
//
long    Iset1=0;               // Control loop 1 target
long    Iset2=0;               // Control loop 2 target
long    Iset3=0;               // Control loop 3 target

long    Itarget1=0;            // Control loop 1 target adjusted for Slew rate
long    Itarget2=0;            // Control loop 2 target adjusted for Slew rate
long    Itarget3=0;            // Control loop 3 target adjusted for Slew rate

int16    SlewStep1=_IQ15(0.1);            // 0.05A/ms, see Excel spreadsheet
int16    SlewStep2=_IQ15(0.1);            // 0.05A/ms, see Excel spreadsheet
int16    SlewStep3=_IQ15(0.1);            // 0.05A/ms, see Excel spreadsheet

long    SlewError=0;              // Difference between Vset and Vtarget
int16    SlewStepAll=_IQ15(0.1);  // 0.05A/ms, see Excel spreadsheet

//
// Forces update of individual SlewSteps with SlewStepAll
//
int16    ResetSlew=0;             

//
// System control
//
int16    StopAll=0;
int16    EnableAll=0;
int16    MergeLEDs=0;
int16    AutoColor=0;
int16    SetColor1=0;
int16    SetColor2=0;
int16    ChannelEnable1=1;          // Flag [ 0="off", 1="on" ]
int16    ChannelEnable2=1;          // Flag [ 0="off", 1="on" ]
int16    ChannelEnable3=1;          // Flag [ 0="off", 1="on" ]

long    Duty1=0;                    // Open-loop duty
long    Duty2=0;                    // Open-loop duty
long    Duty3=0;                    // Open-loop duty

int16    OCtrip=0;                  // Over-current protection trip flag
int16    OC_limit=4915;             // 0.160A in Q15

//
// Boost channel 1 2P2Z Control loop gains
//
long    Pgain1=50;                   //
long    Igain1=1;                    //
long    Dgain1=5;                    //

//
// Boost channel 2 2P2Z Control loop gains
//
long    Pgain2=50;                   //
long    Igain2=1;                    //
long    Dgain2=5;                    //

//
// Boost channel 3 2P2Z Control loop gains
//
long    Pgain3=50;                   //
long    Igain3=1;                    //
long    Dgain3=5;                    //

//
// Variables for background support only (no need to access)
//
int16    i=0;                    // common use incrementer
int16    temp_Scratch=0;         // Temp here means Temporary

//
// History arrays are used for Running Average calculation (boxcar filter)
// Used for CCS display and GUI only, not part of control loop processing
//
int16    HistPtr=0;                // Index for History arrays
long    Hist_Vin[HistorySize];
long    Hist_Vout1[HistorySize];
long    Hist_Vout2[HistorySize];
long    Hist_Vout3[HistorySize];
long    Hist_Vout8[HistorySize];
long    Hist_Iout1[HistorySize];
long    Hist_Iout2[HistorySize];
long    Hist_Iout3[HistorySize];

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// VARIABLE DECLARATIONS - CCS WatchWindow / GUI support
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// -------------------------------- FRAMEWORK ---------------------------------

//
// GUI support variables
// sets a limit on the amount of external GUI controls - increase as necessary
//
int16     *varSetTxtList[7];                //16 textbox controlled variables
int16     *varSetBtnList[1];                //16 button controlled variables
int16     *varSetSldrList[8];            //16 slider controlled variables
int16     *varGetList[10];                //16 variables sendable to GUI
int16     *arrayGetList[1];                //16 arrays sendable to GUI

// ---------------------------------- USER ------------------------------------

int16    FlashID=0x5055;

//
// Variables for easier "human" use
//
int16    Gui_Vin=0;      //Q09
int16    Gui_Vout1=0;    //Q08
int16    Gui_Vout2=0;    //Q08
int16    Gui_Vout3=0;    //Q08
int16    Gui_Vout8=0;    //Q08
int16    Gui_Iset1=0;    //Q15
int16    Gui_Iset2=0;    //Q15
int16    Gui_Iset3=0;    //Q15
int16    Gui_Iout1=0;    //Q15
int16    Gui_Iout2=0;    //Q15
int16    Gui_Iout3=0;    //Q15

//
// Scaling Constants (values found via spreadsheet; exact value calibrated per 
// board)
//
int16    K_Vin=19439;    // 0.593 in Q15
int16    K_Vout=20452;   // 0.625 in Q15
int16    iK_Iset=24824;  // 1.515 in Q14
int16    K_Iout=21627;   // 0.660 in Q15

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// MAIN CODE - starts here
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//
// Main
//
void main(void)
{
//
//    INITIALISATION - General
//

//-------------------------------- FRAMEWORK ----------------------------------

    DeviceInit();     // Device Life support & GPIO
    SCIA_Init();      // Initalize the Serial Comms A peripheral        

//
// Only used if running from FLASH
// Note that the variable FLASH is defined by the build configuration
//
#ifdef FLASH
    //
    // Copy time critical code and Flash setup code to RAM
    // The  RamfuncsLoadStart, RamfuncsLoadSize, and RamfuncsRunStart
    // symbols are created by the linker. Refer to the linker files.
    //
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);

    //
    // Call Flash Initialization to setup flash waitstates
    // This function must reside in RAM
    //
    InitFlash();    // Call the flash wrapper init function
#endif //(FLASH)

    //
    // Timing sync for background loops
    // Timer period definitions found in device specific F2802x_device.h
    //
    CpuTimer0Regs.PRD.all =  mSec1;         // A tasks
    CpuTimer1Regs.PRD.all =  mSec10;        // B tasks
    CpuTimer2Regs.PRD.all =  mSec50;        // C tasks

    //
    // Tasks State-machine init
    //
    Alpha_State_Ptr = &A0;
    A_Task_Ptr = &A1;
    B_Task_Ptr = &B1;
    C_Task_Ptr = &C1;

// ---------------------------------- USER ------------------------------------

//
// 2 pole / 2 Zero compensator coefficients (B2, B1, B0, A2, A1) are mapped to 
// the simpler 3 coefficients P, I, D  to allow for trial & error intuitive 
// tuning via CCS WatchWindow or GUI Sliders.  Note: User can modify if needed 
// and assign full set of 5 coef.
//

    //
    // Boost channel 1 2P2Z Coefficient init
    //
    CNTL_2P2Z_CoefStruct1.b2 = _IQ16(Dgain1);
    CNTL_2P2Z_CoefStruct1.b1 = _IQ16(Igain1 - Pgain1 - Dgain1 - Dgain1);
    CNTL_2P2Z_CoefStruct1.b0 = _IQ16(Pgain1 + Igain1 + Dgain1);
    CNTL_2P2Z_CoefStruct1.a2 = _IQ26(0.0);
    CNTL_2P2Z_CoefStruct1.a1 = _IQ26(1.0);
    CNTL_2P2Z_CoefStruct1.max = _IQ14(DMAX);
    CNTL_2P2Z_CoefStruct1.min = _IQ14(DMIN);

    //
    // Boost channel 2 2P2Z Coefficient init
    //
    CNTL_2P2Z_CoefStruct2.b2 = _IQ16(Dgain2);
    CNTL_2P2Z_CoefStruct2.b1 = _IQ16(Igain2 - Pgain2 - Dgain2 - Dgain2);
    CNTL_2P2Z_CoefStruct2.b0 = _IQ16(Pgain2 + Igain2 + Dgain2);
    CNTL_2P2Z_CoefStruct2.a2 = _IQ26(0.0);
    CNTL_2P2Z_CoefStruct2.a1 = _IQ26(1.0);
    CNTL_2P2Z_CoefStruct2.max = _IQ14(DMAX);
    CNTL_2P2Z_CoefStruct2.min = _IQ14(DMIN);

    //
    // Boost channel 3 2P2Z Coefficient init
    //
    CNTL_2P2Z_CoefStruct3.b2 = _IQ16(Dgain3);
    CNTL_2P2Z_CoefStruct3.b1 = _IQ16(Igain3 - Pgain3 - Dgain3 - Dgain3);
    CNTL_2P2Z_CoefStruct3.b0 = _IQ16(Pgain3 + Igain3 + Dgain3);
    CNTL_2P2Z_CoefStruct3.a2 = _IQ26(0.0);
    CNTL_2P2Z_CoefStruct3.a1 = _IQ26(1.0);
    CNTL_2P2Z_CoefStruct3.max = _IQ14(DMAX);
    CNTL_2P2Z_CoefStruct3.min = _IQ14(DMIN);

    for(i=0; i<HistorySize; i++)
    {
        Hist_Iout1[i] = 0;    //Q12 * 8 = Q15
    }
    for(i=0; i<HistorySize; i++)
    {
        Hist_Iout2[i] = 0;    //Q12 * 8 = Q15
    }
    for(i=0; i<HistorySize; i++)
    {
        Hist_Iout3[i] = 0;    //Q12 * 8 = Q15
    }

//
//    INITIALISATION - GUI connections
//
// Use this section only if you plan to "Instrument" your application using the 
// Microsoft C# freeware GUI Template provided by TI
//
    varSetTxtList[0] = &MergeLEDs;
    varSetTxtList[1] = &SlewStepAll;
    varSetTxtList[2] = &AutoColor;
    varSetTxtList[3] = &SetColor1;
    varSetTxtList[4] = 0;
    varSetTxtList[5] = &StopAll;
    varSetTxtList[6] = &EnableAll;

    varSetSldrList[0] = &Gui_Iset1;
    varSetSldrList[1] = &Gui_Iset2;
    varSetSldrList[2] = &Gui_Iset3;
    varSetSldrList[3] = 0;
    varSetSldrList[4] = 0;
    varSetSldrList[5] = 0;
    varSetSldrList[6] = 0;
    varSetSldrList[7] = 0;

    varGetList[0] = &FlashID;
    varGetList[1] = &Gui_Vin;
    varGetList[2] = &Gui_Iout1;
    varGetList[3] = &Gui_Iout2;
    varGetList[4] = &Gui_Iout3;
    varGetList[5] = 0;
    varGetList[6] = 0;
    varGetList[7] = 0;
    varGetList[8] = 0;
    varGetList[9] = 0;

//
//    INITIALISATION - Peripherals used for support
//

//
//    INCREMENTAL BUILD OPTIONS - NOTE: select via ProjectSettings.h
//

// ---------------------------------- USER ------------------------------------
#define        prd            1200    // 1200 Period count = 50 KHz @ 60 MHz
//#define        prd            600    // 600 Period count = 100 KHz @ 60 MHz
//#define        prd            300    // 300 Period count = 200 KHz @ 60 MHz
//#define        prd            200    // 200 Period count = 300 KHz @ 60 MHz
//#define        prd            150    // 150 Period count = 400 KHz @ 60 MHz

#define        Iout1R    AdcResult.ADCRESULT1        //Q12
#define        Iout2R    AdcResult.ADCRESULT2        //Q12
#define        Iout3R    AdcResult.ADCRESULT3        //Q12
#define        Vout1R    AdcResult.ADCRESULT9        //Q12
#define        Vout2R    AdcResult.ADCRESULT10       //Q12
#define        Vout3R    AdcResult.ADCRESULT11       //Q12
#define        VinR      AdcResult.ADCRESULT12       //Q12

    //
    // ADC Channel Selection
    //
    ChSel[0] = 2;        // Dummy read for first sample bug
    ChSel[1] = 2;        // A2 - Iout1 - blue
    ChSel[2] = 1;        // A1 - Iout2 - green
    ChSel[3] = 6;        // A6 - Iout3 - red
    ChSel[9] = 9;        // B1 - Vout1
    ChSel[10] = 10;      // B2 - Vout2
    ChSel[11] = 12;      // B3 - Vout3
    ChSel[12] = 14;      // B6 - Vin / Vout8

    //
    // ADC Trigger Selection
    //
    TrigSel[0] = 5;        // ePWM1, ADCSOCA
    TrigSel[1] = 5;        // ePWM1, ADCSOCA
    TrigSel[2] = 5;        // ePWM1, ADCSOCA
    TrigSel[3] = 5;        // ePWM1, ADCSOCA
    TrigSel[9] = 5;        // ePWM1, ADCSOCA
    TrigSel[10] = 5;       // ePWM1, ADCSOCA
    TrigSel[11] = 5;       // ePWM1, ADCSOCA
    TrigSel[12] = 5;       // ePWM1, ADCSOCA

    ADC_SOC_CNF(ChSel, TrigSel, ACQPS, 16, 0);
    PWM_DualUpDwnCnt_CNF(1, prd, 1, 0);
    PWM_DualUpDwnCnt_CNF(2, prd, 0, 400);
    PWM_1ch_UpDwnCnt_CNF(3, prd, 0, 400);

    //
    // Configure ePWMs to generate ADC SOC pulses
    //
    EPwm1Regs.ETSEL.bit.SOCAEN = 1;               // Enable ePWM1 SOCA pulse
    EPwm1Regs.ETSEL.bit.SOCASEL = ET_CTR_PRD;     // SOCA from ePWM1 Zero event
    
    //
    // Trigger ePWM1 SOCA on every 3rd event
    //
    EPwm1Regs.ETPS.bit.SOCAPRD = ET_3RD;           

    DPL_Init();                                   // DPL ASM ISR init

//----------------------------------------------------------------------
#if (INCR_BUILD == 1)     // Open-Loop
//----------------------------------------------------------------------

//
// Lib Module connection to "nets" 
//

    //
    // Boost 1 connections
    //
    ADCDRV_1ch_Rlt1 = &AdcNetBus[1];
    PWMDRV_DualUpDwnCnt_Duty1A = &Duty1;
    
    //
    // Boost 2 connections
    //
    ADCDRV_1ch_Rlt2 = &AdcNetBus[2];
    PWMDRV_DualUpDwnCnt_Duty1B = &Duty2;
    
    //
    // Boost 3 connections
    //
    ADCDRV_1ch_Rlt3 = &AdcNetBus[3];
    PWMDRV_1ch_UpDwnCnt_Duty2 = &Duty3;
    
    //
    // Voltage connections
    //
    ADCDRV_1ch_Rlt9 = &AdcNetBus[9];
    ADCDRV_1ch_Rlt10 = &AdcNetBus[10];
    ADCDRV_1ch_Rlt11 = &AdcNetBus[11];
    ADCDRV_1ch_Rlt12 = &AdcNetBus[12];
#endif // (INCR_BUILD == 1)

//----------------------------------------------------------------------
#if (INCR_BUILD == 2) // Closed-Loop Current
//----------------------------------------------------------------------

//
// Lib Module connection to "nets" 
//

    //
    // Boost 1 connections
    //
    ADCDRV_1ch_Rlt1 = &AdcNetBus[1];
    CNTL_2P2Z_Ref1 = &IrefNetBus1;                // point to Iref1
    CNTL_2P2Z_Fdbk1 = &AdcNetBus[1];              // point to Iout1
    
    //
    // point to first coeff of 1st loop
    //
    CNTL_2P2Z_Coef1 = &CNTL_2P2Z_CoefStruct1.b2;
    
    CNTL_2P2Z_Out1 = &UoutNetBus1;                // point to 2P2Z Uout1
    PWMDRV_DualUpDwnCnt_Duty1A = &UoutNetBus1;

    //
    // Boost 2 connections
    //
    ADCDRV_1ch_Rlt2 = &AdcNetBus[2];
    CNTL_2P2Z_Ref2 = &IrefNetBus2;                // point to Iref2
    CNTL_2P2Z_Fdbk2 = &AdcNetBus[2];              // point to Iout2
    
    //
    // point to first coeff of 1st loop
    //
    CNTL_2P2Z_Coef2 = &CNTL_2P2Z_CoefStruct2.b2;  
    
    CNTL_2P2Z_Out2 = &UoutNetBus2;                // point to 2P2Z Uout2
    PWMDRV_DualUpDwnCnt_Duty1B = &UoutNetBus2;

    //
    // Boost 3 connections
    //
    ADCDRV_1ch_Rlt3 = &AdcNetBus[3];
    CNTL_2P2Z_Ref3 = &IrefNetBus3;                // point to Iref3
    CNTL_2P2Z_Fdbk3 = &AdcNetBus[3];              // point to Iout3
    
    //
    // point to first coeff of 1st loop
    //
    CNTL_2P2Z_Coef3 = &CNTL_2P2Z_CoefStruct3.b2;  
    
    CNTL_2P2Z_Out3 = &UoutNetBus3;                // point to 2P2Z Uout3
    PWMDRV_1ch_UpDwnCnt_Duty2 = &UoutNetBus3;

    //
    // Voltage connections
    //
    ADCDRV_1ch_Rlt9 = &AdcNetBus[9];
    ADCDRV_1ch_Rlt10 = &AdcNetBus[10];
    ADCDRV_1ch_Rlt11 = &AdcNetBus[11];
    ADCDRV_1ch_Rlt12 = &AdcNetBus[12];

#endif // (INCR_BUILD == 2)

//----------------------------------------------------------------------
#if (INCR_BUILD == 3) //
//----------------------------------------------------------------------
#endif // (INCR_BUILD == 3)

//
// INTERRUPT & ISR INITIALIZATION (best to run this section after other 
// initialization)
//
    EALLOW;
    PieVectTable.EPWM1_INT = &DPL_ISR;   // Map Interrupt
    EDIS;
    PieCtrlRegs.PIEIER3.bit.INTx1 = 1;   // PIE level enable, Grp3 / Int1

    //
    // Configure ISR trigger
    //
    EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;    // INT on Period event
    EPwm1Regs.ETSEL.bit.INTEN = 1;              // Enable INT
    
    //
    // Generate ISR INT on every 3rd event
    //
    EPwm1Regs.ETPS.bit.INTPRD = ET_3RD;         
    
    //
    // Enable Peripheral, global Ints and higher priority real-time debug 
    // events:
    //
    IER |= M_INT3;    // Enable CPU INT3 connected to EPWM1-6 INTs:
    EINT;             // Enable Global interrupt INTM
    ERTM;             // Enable Global realtime interrupt DBGM

//
//    BACKGROUND (BG) LOOP
//

//--------------------------------- FRAMEWORK ---------------------------------
    for(;;)
    {
        //
        // State machine entry & exit point
        //
        
        //===========================================================
        (*Alpha_State_Ptr)();    // jump to an Alpha state (A0,B0,...)
        //===========================================================
    }
} //END MAIN CODE


//
//    STATE-MACHINE SEQUENCING AND SYNCRONIZATION
//

//--------------------------------- FRAMEWORK -------------------------------------

//
// A0 - 
//
void A0(void)
{
    //
    // loop rate synchronizer for A-tasks
    //
    if(CpuTimer0Regs.TCR.bit.TIF == 1)
    {
        CpuTimer0Regs.TCR.bit.TIF = 1;    // clear flag
        //-----------------------------------------------------------
        (*A_Task_Ptr)();         // jump to an A Task (A1,A2,A3,...)
        //-----------------------------------------------------------
        VTimer0[0]++;            // virtual timer 0, instance 0 (spare)
        SerialCommsTimer++;      // used by DSP280x_SciCommsGui.c
    }
    Alpha_State_Ptr = &B0;       // Comment out to allow only A tasks
}

//
// B0 - 
//
void B0(void)
{
    //
    // loop rate synchronizer for B-tasks
    //
    if(CpuTimer1Regs.TCR.bit.TIF == 1)
    {
        CpuTimer1Regs.TCR.bit.TIF = 1;                // clear flag
        //-----------------------------------------------------------
        (*B_Task_Ptr)();        // jump to a B Task (B1,B2,B3,...)
        //-----------------------------------------------------------
        
        //
        // virtual timer 1, instance 0 (used to control SPI LEDs)
        //
        VTimer1[0]++;
    }
    Alpha_State_Ptr = &C0;
}

//
// C0 - 
//
void C0(void)
{
    //
    // loop rate synchronizer for C-tasks
    //
    if(CpuTimer2Regs.TCR.bit.TIF == 1)
    {
        CpuTimer2Regs.TCR.bit.TIF = 1;                // clear flag
        //-----------------------------------------------------------
        (*C_Task_Ptr)();        // jump to a C Task (C1,C2,C3,...)
        //-----------------------------------------------------------
        VTimer2[0]++;           // virtual timer 2, instance 0 (spare)
    }
    Alpha_State_Ptr = &A0;      // Back to State A0
}


//
//    A - TASKS
//

//
// A1 - Over-current protection, On/Off Control
//
void A1(void)
{
    //
    // Over-current protection
    //
    if (Gui_Iout1 > OC_limit)
    {
        OCtrip = 1;
    }
    if (Gui_Iout2 > OC_limit)
    {
        OCtrip = 1;
    }
    if (Gui_Iout3 > OC_limit)
    {
        OCtrip = 1;
    }
    
    if (OCtrip)
    {
        StopAll = 1;
    }

    //
    // All Channel shut-down control (no sequencing)
    //
    if(StopAll == 1)
    {
        IrefNetBus1 = 0;
        IrefNetBus2 = 0;
        IrefNetBus3 = 0;
        ChannelEnable1 = 0;
        ChannelEnable2 = 0;
        ChannelEnable3 = 0;
        Gui_Iset1 = 0;
        Gui_Iset2 = 0;
        Gui_Iset3 = 0;
        MergeLEDs = 0;
        AutoColor = 0;
        SetColor1 = 0;
        SetColor2 = 0;
        StopAll = 0;
    }
    
    if (EnableAll == 1)
    {
        ChannelEnable1 = 1;
        ChannelEnable2 = 1;
        ChannelEnable3 = 1;
        EnableAll = 0;
    }

    //
    // Channel 1 On/Off control
    //
    if(ChannelEnable1 == 1)
    {
        Itarget1 = Iset1;
    }
    else
    {
        Itarget1 = 0;
    }
    
    //
    // Channel 2 On/Off control
    //
    if(ChannelEnable2 == 1)
    {
        Itarget2 = Iset2;
    }
    else
    {
        Itarget2 = 0;
    }
    
    //
    // Channel 3 On/Off control
    //
    if(ChannelEnable3 == 1)
    {
        Itarget3 = Iset3;
    }
    else
    {
        Itarget3 = 0;
    }

    //-------------------
    A_Task_Ptr = &A2;
    //-------------------
}

//
// A2 - SCI GUI, Slew control, LED current control
//
void A2(void) 
{
    SerialHostComms();    //found in SciCommsGui.c

    //
    // This code ensures that each channel's current ramps at a given slew rate
    // at a rate defined by SlewStep.
    // Derivation shown in attached Excel Spreadsheet
    //
    SlewError = (IrefNetBus1 - Itarget1);
    if (SlewError > SlewStep1)
    {
        IrefNetBus1 = IrefNetBus1 - SlewStep1;
    }
    else if (SlewError < (-SlewStep1) )
    {
        IrefNetBus1 = IrefNetBus1 + SlewStep1;
    }
    else
    {
        IrefNetBus1 = Itarget1;
    }

    SlewError = (IrefNetBus2 - Itarget2);
    if (SlewError > SlewStep2)
    {
        IrefNetBus2 = IrefNetBus2 - SlewStep2;
    }
    else if (SlewError < (-SlewStep2) )
    {
        IrefNetBus2 = IrefNetBus2 + SlewStep2;
    }
    else
    {
        IrefNetBus2 = Itarget2;
    }

    SlewError = (IrefNetBus3 - Itarget3);
    if (SlewError > SlewStep3)
    {
        IrefNetBus3 = IrefNetBus3 - SlewStep3;
    }
    else if (SlewError < (-SlewStep3) )
    {
        IrefNetBus3 = IrefNetBus3 + SlewStep3;
    }
    else
    {
        IrefNetBus3 = Itarget3;
    }

    //
    // Current setting calculated by:
    // Iset = Gui_Iset * iK_Iout, where iK_Iout = 1/K_Iout 
    // (i.e. inverse K_Iout) view and set following variables in Watch Window 
    // as:
    // Gui_Iset = Q15
    //

    //
    // Multiply with longs to get proper result then shift by 14 to turn it 
    // back into an int16
    //
    Iset1 = ((long)Gui_Iset1*(long)iK_Iset) >> 5;
    Iset2 = ((long)Gui_Iset2*(long)iK_Iset) >> 5;
    Iset3 = ((long)Gui_Iset3*(long)iK_Iset) >> 5;

    //-------------------
    A_Task_Ptr = &A1;
    //-------------------
}

//
// comp - Hardware fix for poor feedback path on LED Boosterpack
//
void comp(void) 
{
    if((Gui_Iset1 == 0) && (AdcNetBus[1] == 0) && (UoutNetBus1 >= _IQ24(0.001)))
    {
        AdcNetBus[1] = 40960;
    }
    if((Gui_Iset2 == 0) && (AdcNetBus[2] == 0) && (UoutNetBus2 >= _IQ24(0.001)))
    {
        AdcNetBus[2] = 40960;
    }
    if((Gui_Iset3 == 0) && (AdcNetBus[3] == 0) && (UoutNetBus3 >= _IQ24(0.001)))
    {
        AdcNetBus[3] = 40960;
    }
}

//
//    B - TASKS
//

//----------------------------------- USER ------------------------------------

//
// B1 - Current Dashboard measurements
//
void B1(void) 
{
    //
    // Measurement code expandable to multiple channels, defined by 
    // "NumChannels"
    // Voltage measurement calculated by:
    // Gui_Vout = VoutAvg * K_Vout, where VoutAvg = sum of 8 VoutR samples
    //
    HistPtr++;
    if (HistPtr >= HistorySize)
    {
        HistPtr = 0;
    }

    //
    // BoxCar Averages - Input Raw samples into BoxCar arrays
    //
    Hist_Iout1[HistPtr] = Iout1R;
    Hist_Iout2[HistPtr] = Iout2R;
    Hist_Iout3[HistPtr] = Iout3R;
    Hist_Vout1[HistPtr] = Vout1R;
    Hist_Vout2[HistPtr] = Vout2R;
    Hist_Vout3[HistPtr] = Vout3R;
    Hist_Vin[HistPtr] = VinR;

    //
    // Current Measurement
    //
    // view following variables in Watch Window as:
    //        Gui_Vout = Q10
    //
    temp_Scratch=0;
    for(i=0; i<HistorySize; i++)
    {
        temp_Scratch = temp_Scratch + Hist_Iout1[i];     // Q12 * 8 = Q15
    }
    Gui_Iout1 = ((long)temp_Scratch*(long)K_Iout) >> 15; // Q15*Q15 >> 15 = Q15

    temp_Scratch=0;
    for(i=0; i<HistorySize; i++)
    {
        temp_Scratch = temp_Scratch + Hist_Iout2[i];     // Q12 * 8 = Q15
    }
    Gui_Iout2 = ((long)temp_Scratch*(long)K_Iout) >> 15; // Q15*Q15 >> 15 = Q15

    temp_Scratch=0;
    for(i=0; i<HistorySize; i++)
    {
        temp_Scratch = temp_Scratch + Hist_Iout3[i];     // Q12 * 8 = Q15
    }
    Gui_Iout3 = ((long)temp_Scratch*(long)K_Iout) >> 15; // Q15*Q15 >> 15 = Q15

    //-----------------
    B_Task_Ptr = &B2;    
    //-----------------
}

//
// B2 - Voltage Dashboard measurements
//
void B2(void)
{
    //
    // Measurement code expandable to multiple channels, defined by 
    // "NumChannels"
    // Voltage measurement calculated by:
    // Gui_Vout = VoutAvg * K_Vout, where VoutAvg = sum of 8 VoutR samples
    //
    HistPtr++;
    if (HistPtr >= HistorySize)
    {
        HistPtr = 0;
    }

    //
    // BoxCar Averages - Input Raw samples into BoxCar arrays
    //
    Hist_Iout1[HistPtr] = Iout1R;
    Hist_Iout2[HistPtr] = Iout2R;
    Hist_Iout3[HistPtr] = Iout3R;
    Hist_Vout1[HistPtr] = Vout1R;
    Hist_Vout2[HistPtr] = Vout2R;
    Hist_Vout3[HistPtr] = Vout3R;
    Hist_Vin[HistPtr] = VinR;

    //
    // Voltage Measurement
    //
    // view following variables in Watch Window as:
    //        Gui_Vout = Q10
    //
    temp_Scratch=0;
    for(i=0; i<HistorySize; i++)
    {
        temp_Scratch = temp_Scratch + Hist_Vout1[i];     // Q12 * 8 = Q15
    }
    Gui_Vout1 = ((long)temp_Scratch*(long)K_Vout) >> 15; // Q15*Q15 >> 15 = Q15

    temp_Scratch=0;
    for(i=0; i<HistorySize; i++)
    {
        temp_Scratch = temp_Scratch + Hist_Vout2[i];     // Q12 * 8 = Q15
    }
    Gui_Vout2 = ((long)temp_Scratch*(long)K_Vout) >> 15; // Q15*Q15 >> 15 = Q15

    temp_Scratch=0;
    for(i=0; i<HistorySize; i++)
    {
        temp_Scratch = temp_Scratch + Hist_Vout3[i];     // Q12 * 8 = Q15
    }
    Gui_Vout3 = ((long)temp_Scratch*(long)K_Vout) >> 15; // Q15*Q15 >> 15 = Q15

    temp_Scratch=0;
    for(i=0; i<HistorySize; i++)
    {
        temp_Scratch = temp_Scratch + Hist_Vin[i];      // Q12 * 8 = Q15
    }
    Gui_Vin = ((long)temp_Scratch*(long)K_Vin) >> 15;   // Q15*Q15 >> 15 = Q15

    //-----------------
    B_Task_Ptr = &B1;    
    //-----------------
}

//
//    C - TASKS
//

//----------------------------- USER ------------------------------------------

//
// C1 - Blinking LED control
//
void C1(void) 
{
    //-----------------
    C_Task_Ptr = &C2;    
    //-----------------
}

//
// C2- Automatic color control, Manual color control
//
void C2(void) 
{
    #define AutoColorMIN 253670
    
    if (AutoColor)
    {
		SlewStep1 = 3*60;
		SlewStep2 = 1*60;
		SlewStep3 = 5*60;
		
		if (IrefNetBus1 <= AutoColorMIN)
		{
            Gui_Iset1 = 0.03*32768;
        }
		else if (IrefNetBus1 == Itarget1)
        {
            Gui_Iset1 = 0.01*32768;
        }
		if (IrefNetBus2 <= AutoColorMIN)
        {
            Gui_Iset2 = 0.05*32768;
        }
		else if (IrefNetBus2 == Itarget2)
        {
            Gui_Iset2 = 0.01*32768;
        }
		if (IrefNetBus3 <= AutoColorMIN)
        {
            Gui_Iset3 = 0.06*32768;
        }
		else if (IrefNetBus3 == Itarget3)
        {
            Gui_Iset3 = 0.01*32768;
        }

		ResetSlew = 1;
    }
    else
    {
        if (ResetSlew == 1)
        {
            SlewStep1 = SlewStepAll;
            SlewStep2 = SlewStepAll;
            SlewStep3 = SlewStepAll;
            ResetSlew = 0;
        }    
    }

    if (!AutoColor)
    {    
        switch(SetColor1)
        {
            case 0:
                break;
            case 99:    // Off
                Gui_Iset1 = 0;
                Gui_Iset2 = 0;
                Gui_Iset3 = 0;
                break;
            case 1:        // Red
                Gui_Iset1 = 0;
                Gui_Iset2 = 0;
                Gui_Iset3 = 0.03*32768;
                break;
            case 2:        // Orange
                Gui_Iset1 = 0;
                Gui_Iset2 = 0.01*32768;
                Gui_Iset3 = 0.035*32768;
                break;
            case 3:        // Yellow
                Gui_Iset1 = 0;;
                Gui_Iset2 = 0.025*32768;
                Gui_Iset3 = 0.035*32768;
                break;
            case 4:        // Green
                Gui_Iset1 = 0;
                Gui_Iset2 = 0.03*32768;
                Gui_Iset3 = 0;
                break;
            case 5:        // Blue
                Gui_Iset1 = 0.03*32768;
                Gui_Iset2 = 0;
                Gui_Iset3 = 0;
                break;
            case 6:        // Purple
                Gui_Iset1 = 0.025*32768;
                Gui_Iset2 = 0;
                Gui_Iset3 = 0.025*32768;
                break;
            case 7:        // White
                Gui_Iset1 = 0.015*32768;
                Gui_Iset2 = 0.02*32768;
                Gui_Iset3 = 0.025*32768;
                break;
            case 8:           // Black
                Gui_Iset1 = 0;
                Gui_Iset2 = 0;
                Gui_Iset3 = 0;
                break;

            default:
                break;
        } // SetColor1
        SetColor1 = 0;

    } // !AutoColor

    //-----------------
    C_Task_Ptr = &C1;    
    //-----------------
}

//
// End of File
//

