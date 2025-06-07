//###########################################################################
//
// FILE:   f2802x_examples/LED_Boost_CapTouch/LED_Boost_CapTouch_DevInit_F2802x.c
//
// TITLE:  Device initialization code for the LED Boosterpack CapTouch Example
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:
// Copyright (C) 2009-2025 Texas Instruments Incorporated - http://www.ti.com/
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
#include "DSP28x_Project.h"

//
// Functions that will be run from RAM need to be assigned to
// a different section.  This section will then be mapped to a load and
// run address using the linker cmd file.
//
#pragma CODE_SECTION(InitFlash, "ramfuncs");
#define Device_cal (void   (*)(void))0x3D7C80

void DeviceInit(void);
void PieCntlInit(void);
void PieVectTableInit(void);
void WDogDisable(void);
void PLLset(Uint16);
void ISR_ILLEGAL(void);

//
// DeviceInit - Configure Device for target Application Here
//
void DeviceInit(void)
{
    WDogDisable();   // Disable the watchdog initially
    DINT;            // Global Disable all Interrupts
    IER = 0x0000;    // Disable CPU interrupts
    IFR = 0x0000;    // Clear all CPU interrupt flags

    //
    // The Device_cal function, which copies the ADC & oscillator calibration 
    // values from TI reserved OTP into the appropriate trim registers, occurs 
    // automatically in the Boot ROM. If the boot ROM code is bypassed during 
    // the debug process, the following function MUST be called for the ADC and
    // oscillators to function according to specification.
    //
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1; // Enable ADC peripheral clock
    (*Device_cal)();                      // Auto-calibrate from TI OTP
    SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 0; // Return ADC clock to original state
    EDIS;

    //
    // Switch to Internal Oscillator 1 and turn off all other clock
    // sources to minimize power consumption
    //
    EALLOW;
    SysCtrlRegs.CLKCTL.bit.INTOSC1OFF = 0;
    SysCtrlRegs.CLKCTL.bit.OSCCLKSRCSEL=0;  // Clk Src = INTOSC1
    SysCtrlRegs.CLKCTL.bit.XCLKINOFF=1;     // Turn off XCLKIN
    SysCtrlRegs.CLKCTL.bit.XTALOSCOFF=1;    // Turn off XTALOSC
    SysCtrlRegs.CLKCTL.bit.INTOSC2OFF=1;    // Turn off INTOSC2
    EDIS;

    //
    // SYSTEM CLOCK speed based on internal oscillator = 10 MHz
    // 0xC =  60    MHz        (12)
    // 0xB =  55    MHz        (11)
    // 0xA =  50    MHz        (10)
    // 0x9 =  45    MHz        (9)
    // 0x8 =  40    MHz        (8)
    // 0x7 =  35    MHz        (7)
    // 0x6 =  30    MHz        (6)
    // 0x5 =  25    MHz        (5)
    // 0x4 =  20    MHz        (4)
    // 0x3 =  15    MHz        (3)
    // 0x2 =  10    MHz        (2)
    //
    PLLset(0xC);    // choose from options above

    //
    // Initialise interrupt controller and Vector Table to defaults for now. 
    // Application ISR mapping done later.
    //
    PieCntlInit();        
    PieVectTableInit();

    EALLOW; // below registers are "protected", allow access.

    //
    // LOW SPEED CLOCKS prescale register settings
    //
    SysCtrlRegs.LOSPCP.all = 0x0002;        // Sysclk / 4 (15 MHz)
    SysCtrlRegs.XCLK.bit.XCLKOUTDIV=2;
    
    //
    // PERIPHERAL CLOCK ENABLES 
    //
    // If you are not using a peripheral you may want to switch
    // the clock off to save power, i.e. set to =0 
    // 
    // Note: not all peripherals are available on all 280x derivates.
    // Refer to the datasheet for your particular device. 
    //
    SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;    // ADC
    
    SysCtrlRegs.PCLKCR3.bit.COMP1ENCLK = 0;    // COMP1
    SysCtrlRegs.PCLKCR3.bit.COMP2ENCLK = 0;    // COMP2
    
    SysCtrlRegs.PCLKCR0.bit.I2CAENCLK = 0;   // I2C
    
    SysCtrlRegs.PCLKCR0.bit.SPIAENCLK = 0;    // SPI-A
    
    SysCtrlRegs.PCLKCR0.bit.SCIAENCLK = 1;      // SCI-A
    
    SysCtrlRegs.PCLKCR1.bit.ECAP1ENCLK = 0;    //eCAP1
    
    SysCtrlRegs.PCLKCR1.bit.EPWM1ENCLK = 1;  // ePWM1
    SysCtrlRegs.PCLKCR1.bit.EPWM2ENCLK = 1;  // ePWM2
    SysCtrlRegs.PCLKCR1.bit.EPWM3ENCLK = 0;  // ePWM3
    SysCtrlRegs.PCLKCR1.bit.EPWM4ENCLK = 0;  // ePWM4
    
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;   // Enable TBCLK
    
    //
    // GPIO (GENERAL PURPOSE I/O) CONFIG
    //
    //
    // QUICK NOTES on USAGE:
    //
    // If GpioCtrlRegs.GP?MUX?bit.GPIO?= 1, 2 or 3 (i.e. Non GPIO func), 
    // then leave rest of lines commented
    // If GpioCtrlRegs.GP?MUX?bit.GPIO?= 0 (i.e. GPIO func), then:
    //    1) uncomment GpioCtrlRegs.GP?DIR.bit.GPIO? = ? and choose pin to be 
    //       IN or OUT
    //    2) If IN, can leave next to lines commented
    //    3) If OUT, uncomment line with ..GPACLEAR.. to force pin LOW or
    //               uncomment line with ..GPASET.. to force pin HIGH or
    //
    
    //
    //  GPIO-00 - PIN FUNCTION = Boost 1
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;  // 0=GPIO,  1=EPWM1A,  2=Resv,  3=Resv
    //GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;   // 1=OUTput,  0=INput 
    //GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;// uncomment if --> Set Low initially
    //GpioDataRegs.GPASET.bit.GPIO0 = 1; // uncomment if --> Set High initially

    //
    //  GPIO-01 - PIN FUNCTION = Boost 2
    //
    
    //
    // 0=GPIO,  1=EPWM1B,  2=EMU0,  3=COMP1OUT
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;
    //GpioCtrlRegs.GPADIR.bit.GPIO1 = 1; // 1=OUTput,  0=INput 
    //GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;// uncomment if --> Set Low initially
    //GpioDataRegs.GPASET.bit.GPIO1 = 1; // uncomment if --> Set High initially
    
    //
    //  GPIO-02 - PIN FUNCTION = Boost 3
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;  // 0=GPIO,  1=EPWM2A,  2=Resv,  3=Resv
    //GpioCtrlRegs.GPADIR.bit.GPIO2 = 0;  // 1=OUTput,  0=INput 
    //GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;// uncomment if --> Set Low initially
    //GpioDataRegs.GPASET.bit.GPIO2 = 1; // uncomment if --> Set High initially
    
    //
    //  GPIO-03 - PIN FUNCTION = Boost 4
    //
    
    //
    // 0=GPIO,  1=EPWM2B,  2=Resv,  3=COMP2OUT
    //
    //GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1; 
    //GpioCtrlRegs.GPADIR.bit.GPIO3 = 0;  // 1=OUTput,  0=INput 
    //GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;// uncomment if --> Set Low initially
    //GpioDataRegs.GPASET.bit.GPIO3 = 1; // uncomment if --> Set High initially
    
    //
    //  GPIO-04 - PIN FUNCTION = Cap Touch LED
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 0;  // 0=GPIO,  1=EPWM3A, 2=Resv,  3=Resv
    GpioCtrlRegs.GPADIR.bit.GPIO4 = 1;   // 1=OUTput,  0=INput 
    //GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;// uncomment if --> Set Low initially
    //GpioDataRegs.GPASET.bit.GPIO4 = 1; // uncomment if --> Set High initially
    
    //
    //  GPIO-05 - PIN FUNCTION = Cap Touch Input
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 3;  // 0=GPIO, 1=EPWM3B, 2=Resv, 3=ECAP1
    //GpioCtrlRegs.GPADIR.bit.GPIO5 = 0;    // 1=OUTput,  0=INput 
    //GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;// uncomment if --> Set Low initially
    //GpioDataRegs.GPASET.bit.GPIO5 = 1; // uncomment if --> Set High initially
    
    //
    //  GPIO-06 - PIN FUNCTION = Cap Touch LED
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0; // 0=GPIO, 1=EPWM4A, 2=SYNCI, 3=SYNCO
    GpioCtrlRegs.GPADIR.bit.GPIO6 = 1;  // 1=OUTput,  0=INput 
    //GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;// uncomment if --> Set Low initially
    //GpioDataRegs.GPASET.bit.GPIO6 = 1; // uncomment if --> Set High initially
    
    //
    //  GPIO-07 - PIN FUNCTION = Cap Touch LED
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 0;  // 0=GPIO, 1=EPWM4B, 2=SCIRX-A, 3=Resv
    GpioCtrlRegs.GPADIR.bit.GPIO7 = 1;   // 1=OUTput,  0=INput 
    //GpioDataRegs.GPACLEAR.bit.GPIO7 = 1;// uncomment if --> Set Low initially
    //GpioDataRegs.GPASET.bit.GPIO7 = 1; // uncomment if --> Set High initially
    
    //
    //  GPIO-08 - GPIO-11 Do Not Exist
    //
    
    //
    //  GPIO-12 - PIN FUNCTION = --Spare--
    //
    //GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0; // 0=GPIO, 1=TZ1, 2=SCITX-A, 3=Resv
    //GpioCtrlRegs.GPADIR.bit.GPIO12 = 0;  // 1=OUTput,  0=INput 
    //GpioDataRegs.GPACLEAR.bit.GPIO12 = 1;// uncomment if --> Set Low initially
    //GpioDataRegs.GPASET.bit.GPIO12 = 1;// uncomment if --> Set High initially
    
    //
    //  GPIO-13 - GPIO-15 Do Not Exist
    //
    
    //
    //  GPIO-16 - PIN FUNCTION = Cap Touch LED
    //
    GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 0; // 0=GPIO, 1=SPISIMO-A, 2=Resv, 3=TZ2
    GpioCtrlRegs.GPADIR.bit.GPIO16 = 1;   // 1=OUTput,  0=INput 
    //GpioDataRegs.GPACLEAR.bit.GPIO16 = 1;// uncomment if --> Set Low initially
    //GpioDataRegs.GPASET.bit.GPIO16 = 1;// uncomment if --> Set High initially
    
    //
    //  GPIO-17 - PIN FUNCTION = Cap Touch Address
    //
    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 0; // 0=GPIO, 1=SPISOMI-A, 2=Resv, 3=TZ3
    GpioCtrlRegs.GPADIR.bit.GPIO17 = 1;  // 1=OUTput,  0=INput 
    //GpioDataRegs.GPACLEAR.bit.GPIO17 = 1;// uncomment if --> Set Low initially
    //GpioDataRegs.GPASET.bit.GPIO17 = 1;// uncomment if --> Set High initially
    
    //
    //  GPIO-18 - PIN FUNCTION = Cap Touch Address
    //
    
    //
    // 0=GPIO, 1=SPICLK-A, 2=SCITX-A, 3=XCLKOUT
    //
    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO18 = 1;   // 1=OUTput,  0=INput 
    //GpioDataRegs.GPACLEAR.bit.GPIO18 = 1;// uncomment if --> Set Low initially
    //GpioDataRegs.GPASET.bit.GPIO18 = 1;// uncomment if --> Set High initially
    
    //
    //  GPIO-19 - PIN FUNCTION = Cap Touch Address
    //
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 0; // 0=GPIO,1=SPISTE-A,2=SCIRX-A,3=ECAP1
    GpioCtrlRegs.GPADIR.bit.GPIO19 = 1;  // 1=OUTput,  0=INput 
    //GpioDataRegs.GPACLEAR.bit.GPIO19 = 1;// uncomment if --> Set Low initially
    //GpioDataRegs.GPASET.bit.GPIO19 = 1;// uncomment if --> Set High initially
  
    //
    //  GPIO-20 - GPIO-27 Do Not Exist
    //
    
    //
    //  GPIO-28 - PIN FUNCTION = SCI-RX
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;
    GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1; // 0=GPIO, 1=SCIRX-A, 2=I2C-SDA, 3=TZ2
    //GpioCtrlRegs.GPADIR.bit.GPIO28 = 1;  // 1=OUTput,  0=INput 
    //GpioDataRegs.GPACLEAR.bit.GPIO28 = 1;// uncomment if --> Set Low initially
    //GpioDataRegs.GPASET.bit.GPIO28 = 1;// uncomment if --> Set High initially
    
    //
    //  GPIO-29 - PIN FUNCTION = SCI-TX
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;
    GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;// 0=GPIO, 1=SCITXD-A, 2=I2C-SCL, 3=TZ3
    //GpioCtrlRegs.GPADIR.bit.GPIO29 = 1;  // 1=OUTput,  0=INput 
    //GpioDataRegs.GPACLEAR.bit.GPIO29 = 1;// uncomment if --> Set Low initially
    //GpioDataRegs.GPASET.bit.GPIO29 = 1;// uncomment if --> Set High initially
    
    //
    //  GPIO-30 - GPIO-31 Do Not Exist
    //
    
    //
    //  GPIO-32 - PIN FUNCTION = Cap Touch LED
    //
    
    //
    // 0=GPIO,  1=I2C-SDA,  2=SYNCI,  3=ADCSOCA
    //
    GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0;  
    GpioCtrlRegs.GPBDIR.bit.GPIO32 = 1;   // 1=OUTput,  0=INput 
    //GpioDataRegs.GPBCLEAR.bit.GPIO32 = 1;// uncomment if --> Set Low initially
    //GpioDataRegs.GPBSET.bit.GPIO32 = 1;// uncomment if --> Set High initially
    
    //
    //  GPIO-33 - PIN FUNCTION = Cap Touch LED
    //
    
    //
    // 0=GPIO,  1=I2C-SCL,  2=SYNCO,  3=ADCSOCB
    //
    GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO33 = 1;     // 1=OUTput,  0=INput 
    //GpioDataRegs.GPBCLEAR.bit.GPIO33 = 1;// uncomment if --> Set Low initially
    //GpioDataRegs.GPBSET.bit.GPIO33 = 1;// uncomment if --> Set High initially
    
    //
    //  GPIO-34 - PIN FUNCTION = LED for F28027
    //
    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0; // 0=GPIO, 1=COMP2OUT, 2=EMU1, 3=Resv
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;  // 1=OUTput,  0=INput 
    //GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1;// uncomment if --> Set Low initially
    GpioDataRegs.GPBSET.bit.GPIO34 = 1;  // uncomment if --> Set High initially
    
    EDIS;    // Disable register access
}

//
// NOTE:
// IN MOST APPLICATIONS THE FUNCTIONS AFTER THIS POINT CAN BE LEFT UNCHANGED
// THE USER NEED NOT REALLY UNDERSTAND THE BELOW CODE TO SUCCESSFULLY RUN THIS
// APPLICATION.
//

//
// WDogDisable - 
//
void WDogDisable(void)
{
    EALLOW;
    SysCtrlRegs.WDCR= 0x0068;
    EDIS;
}

//
// PLLset - This function initializes the PLLCR register.
// void InitPll(Uint16 val, Uint16 clkindiv)
//
void PLLset(Uint16 val)
{
    volatile Uint16 iVol;

    //
    // Make sure the PLL is not running in limp mode
    //
    if (SysCtrlRegs.PLLSTS.bit.MCLKSTS != 0)
    {
        EALLOW;
        
        //
        // OSCCLKSRC1 failure detected. PLL running in limp mode.
        // Re-enable missing clock logic.
        //
        SysCtrlRegs.PLLSTS.bit.MCLKCLR = 1;
        EDIS;
        
        //
        // Replace this line with a call to an appropriate
        // SystemShutdown(); function.
        //
        asm("        ESTOP0");     // Uncomment for debugging purposes
    }

    //
    // DIVSEL MUST be 0 before PLLCR can be changed from 0x0000. 
    // It is set to 0 by an external reset XRSn. This puts us in 1/4.
    //
    if (SysCtrlRegs.PLLSTS.bit.DIVSEL != 0)
    {
        EALLOW;
        SysCtrlRegs.PLLSTS.bit.DIVSEL = 0;
        EDIS;
    }

    //
    // Change the PLLCR
    //
    if (SysCtrlRegs.PLLCR.bit.DIV != val)
    {
        EALLOW;
        
        //
        // Before setting PLLCR turn off missing clock detect logic
        //
        SysCtrlRegs.PLLSTS.bit.MCLKOFF = 1;
        SysCtrlRegs.PLLCR.bit.DIV = val;
        EDIS;

        //
        // Optional: Wait for PLL to lock.
        // During this time the CPU will switch to OSCCLK/2 until
        // the PLL is stable.  Once the PLL is stable the CPU will
        // switch to the new PLL value.
        //
        // This time-to-lock is monitored by a PLL lock counter.
        //
        // Code is not required to sit and wait for the PLL to lock.
        // However, if the code does anything that is timing critical,
        // and requires the correct clock be locked, then it is best to
        // wait until this switching has completed.
        //

        //
        // Wait for the PLL lock bit to be set.
        // The watchdog should be disabled before this loop, or fed within
        // the loop via ServiceDog().
        //

        //
        // Uncomment to disable the watchdog
        //
        WDogDisable();

        while(SysCtrlRegs.PLLSTS.bit.PLLLOCKS != 1)
        {
            
        }

        EALLOW;
        SysCtrlRegs.PLLSTS.bit.MCLKOFF = 0;
        EDIS;
    }

    //
    // divide down SysClk by 2 to increase stability
    //
    EALLOW;
    SysCtrlRegs.PLLSTS.bit.DIVSEL = 2; 
    EDIS;
}

//
// PieCntlInit - This function initializes the PIE control registers to a 
// known state.
//
void PieCntlInit(void)
{
    //
    // Disable Interrupts at the CPU level:
    //
    DINT;

    //
    // Disable the PIE
    //
    PieCtrlRegs.PIECTRL.bit.ENPIE = 0;

    //
    // Clear all PIEIER registers:
    //
    PieCtrlRegs.PIEIER1.all = 0;
    PieCtrlRegs.PIEIER2.all = 0;
    PieCtrlRegs.PIEIER3.all = 0;    
    PieCtrlRegs.PIEIER4.all = 0;
    PieCtrlRegs.PIEIER5.all = 0;
    PieCtrlRegs.PIEIER6.all = 0;
    PieCtrlRegs.PIEIER7.all = 0;
    PieCtrlRegs.PIEIER8.all = 0;
    PieCtrlRegs.PIEIER9.all = 0;
    PieCtrlRegs.PIEIER10.all = 0;
    PieCtrlRegs.PIEIER11.all = 0;
    PieCtrlRegs.PIEIER12.all = 0;

    //
    // Clear all PIEIFR registers:
    //
    PieCtrlRegs.PIEIFR1.all = 0;
    PieCtrlRegs.PIEIFR2.all = 0;
    PieCtrlRegs.PIEIFR3.all = 0;    
    PieCtrlRegs.PIEIFR4.all = 0;
    PieCtrlRegs.PIEIFR5.all = 0;
    PieCtrlRegs.PIEIFR6.all = 0;
    PieCtrlRegs.PIEIFR7.all = 0;
    PieCtrlRegs.PIEIFR8.all = 0;
    PieCtrlRegs.PIEIFR9.all = 0;
    PieCtrlRegs.PIEIFR10.all = 0;
    PieCtrlRegs.PIEIFR11.all = 0;
    PieCtrlRegs.PIEIFR12.all = 0;
}    

//
// PieVectTableInit -
//
void PieVectTableInit(void)
{
    int16 i;
    volatile PINT *Dest = &PieVectTable.TINT1;

    EALLOW;
    for(i=0; i < 115; i++) 
    {
       *Dest++ = &ISR_ILLEGAL;
    }
    EDIS;

    //
    // Enable the PIE Vector Table
    //
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;     
}

//
// ISR_ILLEGAL - Illegal operation TRAP
//
interrupt void ISR_ILLEGAL(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm("          ESTOP0");
    for(;;);
}

//
// InitFlash - This function initializes the Flash Control registers
//
//                   CAUTION
// This function MUST be executed out of RAM. Executing it
// out of OTP/Flash will yield unpredictable results
//
void InitFlash(void)
{
    EALLOW;
    
    //
    // Enable Flash Pipeline mode to improve performance of code executed from 
    // Flash.
    //
    FlashRegs.FOPT.bit.ENPIPE = 1;

    //
    //                CAUTION
    // Minimum waitstates required for the flash operating
    // at a given CPU rate must be characterized by TI.
    // Refer to the datasheet for the latest information.
    //

    //
    // Set the Paged Waitstate for the Flash
    //
    FlashRegs.FBANKWAIT.bit.PAGEWAIT = 3;

    //
    // Set the Random Waitstate for the Flash
    // 
    FlashRegs.FBANKWAIT.bit.RANDWAIT = 3;

    //
    // Set the Waitstate for the OTP
    // 
    FlashRegs.FOTPWAIT.bit.OTPWAIT = 5;

    //
    //                CAUTION
    // ONLY THE DEFAULT VALUE FOR THESE 2 REGISTERS SHOULD BE USED
    //
    FlashRegs.FSTDBYWAIT.bit.STDBYWAIT = 0x01FF;
    FlashRegs.FACTIVEWAIT.bit.ACTIVEWAIT = 0x01FF;
    EDIS;

    //
    // Force a pipeline flush to ensure that the write to the last register 
    // configured occurs before returning.
    //
    asm(" RPT #7 || NOP");
}

//
// MemCopy - This function will copy the specified memory contents from
// one location to another. 
// 
//    Uint16 *SourceAddr        Pointer to the first word to be moved
//                          SourceAddr < SourceEndAddr
//    Uint16* SourceEndAddr     Pointer to the last word to be moved
//    Uint16* DestAddr          Pointer to the first destination word
//
// No checks are made for invalid memory locations or that the
// end address is > then the first start address.
//
void MemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr)
{
    while(SourceAddr < SourceEndAddr)
    { 
        *DestAddr++ = *SourceAddr++;
    }
    return;
}
    
//
// End of file
//

