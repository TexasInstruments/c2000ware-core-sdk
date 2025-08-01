//#############################################################################
//
// FILE:   mcpwm_ex2_synchronization.c
//
// TITLE:  MCPWM Synchronization Example
//
//! \addtogroup driver_example_list
//! <h1>MCPWM Basic PWM Generation and Updates</h1>
//!
//! This example configures myMCPWM0 and myMCPWM1 as follows
//!     myMCPWM0 (MCPWM1)
//!         Time Base Configurations 
//!             In Up Count Mode for 10KHz Frequency PWM or 15999 TBCLKs for TBCLK of 160MHz
//!             Enabled Sync in for the InputXbar 5, with phase shift load enabled
//!             Sync Out is configured for every Counter equals Period event
//!         Action Qualifier is configurations
//!             Output A1 : Set High on Counter matches zero, set low on CMPA match
//!             Output B1 : Set High on Counter matches zero, set low on CMPB match
//!         Interrupt
//!             For Updating the Phase Shift Values runtime, Interrupt is configured in synchronous 
//!             with the PWM Counter. 
//!             ET2 is configured to fire at every 5 events of Counter = Period.
//!             ET2 is selected as source for the interrupt generation
//!     
//!     myMCPWM1 (MCPWM3)
//!         Time Base Configurations 
//!             In Up Down Count Mode for 10KHz Frequency PWM or 8000 TBCLKs for TBCLK of 160MHz
//!             Enabled Sync in from myMCPWM0, with phase shift load enabled.
//!             Default Counter Mode after sync is set to counting up. But can be changed.
//!         Action Qualifier is configurations
//!             Output A1 : Set High on Counter matches zero, set low on CMPA match
//!             Output B1 : Set High on Counter matches zero, set low on CMPB match
//!
//!
//!  \b External \b Connections \n
//!     Monitor the MCPWM pins for the waveforms.
//!         Observe J4 40 - GPIO0  - myMCPWM0 Output A1
//!         Observe J4 39 - GPIO1  - myMCPWM0 Output B1
//!         Observe J4 7  - GPIO12 - myMCPWM1 Output A1
//!         Observe J2 19 - GPIO29 - myMCPWM1 Output B1
//! 
//! \b Watch \b Variables \n
//!     - gUsePhaseValueUpdate - set to true to runtime update value for the phase shift value.
//!     - gPhaseShiftValue     - value to be used for the phase shift value.
//!     - gPhaseDirUp          - true to use up phase shift value, false for down phase shift value.
//
//#############################################################################

//
// Included Files
//
#include "f28x_project.h"

// 
// Runtime update value for the phase shift value and observations
// default this value is set to false, and hence the phase shift value 
// is initially taken from the sysconfig configuartions
//
volatile bool gUsePhaseValueUpdate = false;
volatile uint16_t gPhaseShiftValue = 0;
volatile bool gPhaseDirUp = true;

//
// Function Prototypes
//
__interrupt void INT_myMCPWM0_ISR(void);
void initMyMCPWM0(void);
void initMyMCPWM1(void);

void main(void)
{
    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the f2838x_sysctrl.c file.
    //
    InitSysCtrl();

    //
    // For this case just init GPIO pins for mcpwm1, mcpwm3
    // These functions are in the f2838x_mcpwm.c file
    //
    InitGpio();
    InitMcpwm1Gpio();
    InitMcpwm3Gpio();

    //
    // Step 3. Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    //
    DINT;

    //
    // Initialize the PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the f2838x_piectrl.c file.
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
    // The shell ISR routines are found in f2838x_defaultisr.c.
    // This function is found in f2838x_pievect.c.
    //
    InitPieVectTable();

    //
    // Register interrupt handlers
    //
    EALLOW;
    PieVectTable.MCPWM1_INT = &INT_myMCPWM0_ISR;
    EDIS;

    //
    // Disable sync(Freeze clock to PWM as well)
    //
    CpuSysRegs.PERCLKCR.bit.TBCLKSYNC = 0;

    //
    // Initialize MCPWM modules
    //
    initMyMCPWM0();
    initMyMCPWM1();

    //
    // Clear any pending interrupts
    //
    EALLOW;
    Pwm1Regs.INTCLR.bit.ET2 = 1;
    Pwm1Regs.INTCLR.bit.INT = 1;
    EDIS;

    //
    // Enable PWM interrupts
    //
    IER |= M_INT2;  // Enable group 2 interrupts (MCPWM1)

    //
    // Enable MCPWM interrupts
    //
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;          // Enable the PIE block
    PieCtrlRegs.PIEIER2.bit.INTx4 = 1;          // mcpwm1 group 2, int 4

    //
    // Enable global interrupts and real-time debug
    //
    EINT;
    ERTM;

    //
    // Enable sync clock
    //
    CpuSysRegs.PERCLKCR.bit.TBCLKSYNC = 1;

    //
    // IDLE loop
    //
    while(1)
    {
        asm ("  NOP");
    }
}

//
// initMyMCPWM0 - Initialize MCPWM1 module
//
// Defaults used (not explicitly configured):
// - CLKDIV = TB_DIV1 (No clock division)
// - FREE_SOFT = EMULATION_FREE_RUN (Free run in emulation)
// - TBPHS = 0 (No initial phase offset)
// - PWM1_LOADAMODE/PWM1_LOADBMODE = CC_CTR_ZERO (Load on CTR=Zero)
// - LDAQAMODE/LDAQBMODE = AQ_CTR_ZERO (Load on CTR=Zero)
//
void initMyMCPWM0(void)
{
    //
    // Time Base Control - Only non-default configurations
    //
    Pwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;      
    Pwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW_LOAD_ENABLE; 
    Pwm1Regs.TBCTL.bit.PHSEN = TB_PHASE_ENABLE;    
    Pwm1Regs.TBCTL.bit.SYNCOSEL = SYNCPERSEL_SOURCE_PERIOD;  
    Pwm1Regs.TBCTL.bit.SYNCISEL = SYNC_IN_PULSE_SRC_INPUTXBAR_OUT5; 
    
    //
    // Period and Compare Values - Using shadow registers
    //
    Pwm1Regs.TBPRDS.bit.TBPRDS = 15999;            // 10kHz
    Pwm1Regs.PWM1_CMPAS.bit.PWM1_CMPAS = 8000;     // 50% duty
    Pwm1Regs.PWM1_CMPBS.bit.PWM1_CMPBS = 8000;     // 50% duty

    //
    // Action Qualifier - Only PWM1 used
    //
    Pwm1Regs.PWM1_AQCTLAS.bit.ZRO = AQ_SET;        
    Pwm1Regs.PWM1_AQCTLAS.bit.CAU = AQ_CLEAR;      

    Pwm1Regs.PWM1_AQCTLBS.bit.ZRO = AQ_SET;        
    Pwm1Regs.PWM1_AQCTLBS.bit.CBU = AQ_CLEAR;      

    //
    // Event Trigger Configuration
    //
    Pwm1Regs.ETSEL.bit.ET2_SEL = EVT_TBCTR_PERIOD; 
    Pwm1Regs.ETPERIOD.bit.ET2_PERIOD = 5;          

    //
    // Enable ET2 Interrupt
    //
    EALLOW;
    Pwm1Regs.INTEN.bit.ET2 = INT_ENABLE;
    EDIS;
}

//
// initMyMCPWM1 - Initialize MCPWM3 module
//
// Defaults used (not explicitly configured):
// - CLKDIV = TB_DIV1 (No clock division)
// - FREE_SOFT = EMULATION_FREE_RUN (Free run in emulation)
// - TBPHS = 0 (No initial phase offset)
// - PWM1_LOADAMODE/PWM1_LOADBMODE = CC_CTR_ZERO (Load on CTR=Zero)
// - LDAQAMODE/LDAQBMODE = AQ_CTR_ZERO (Load on CTR=Zero)
//
void initMyMCPWM1(void)
{
    //
    // Time Base Control - Only non-default configurations
    //
    Pwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;    
    Pwm3Regs.TBCTL.bit.PRDLD = TB_SHADOW_LOAD_ENABLE;
    Pwm3Regs.TBCTL.bit.PHSEN = TB_PHASE_ENABLE;    
    Pwm3Regs.TBCTL.bit.PHSDIR = TB_UP;             
    Pwm3Regs.TBCTL.bit.SYNCISEL = SYNC_IN_PULSE_SRC_SYNCOUT_MCPWM1;

    //
    // Period and Compare Values - Using shadow registers
    //
    Pwm3Regs.TBPRDS.bit.TBPRDS = 8000;             // 10kHz
    Pwm3Regs.PWM1_CMPAS.bit.PWM1_CMPAS = 4000;     // 50% duty
    Pwm3Regs.PWM1_CMPBS.bit.PWM1_CMPBS = 4000;     // 50% duty

    //
    // Action Qualifier - Only PWM1 used
    //
    Pwm3Regs.PWM1_AQCTLAS.bit.ZRO = AQ_SET;        
    Pwm3Regs.PWM1_AQCTLAS.bit.CAU = AQ_CLEAR;      

    Pwm3Regs.PWM1_AQCTLBS.bit.ZRO = AQ_SET;        
    Pwm3Regs.PWM1_AQCTLBS.bit.CBU = AQ_CLEAR;      
}

//
// INT_myMCPWM0_ISR - MCPWM0 ISR 
// 
__interrupt void INT_myMCPWM0_ISR(void)
{
    if(true == gUsePhaseValueUpdate)
    {
        // Update phase shift value
        Pwm3Regs.TBPHS.bit.TBPHS = gPhaseShiftValue;

        // Update counter mode after sync if needed
        Pwm3Regs.TBCTL.bit.PHSDIR = (gPhaseDirUp) ? TB_UP : TB_DOWN;
    }

    // Clear interrupt flags
    EALLOW;
    Pwm1Regs.INTCLR.bit.ET2 = 1;
    Pwm1Regs.INTCLR.bit.INT = 1;
    EDIS;

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;
}
