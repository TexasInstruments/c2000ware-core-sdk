//#############################################################################
//! \file /2837x_RFFT_ADC/main.c
//!
//! \brief  Demo code for the 512 pt real-time RFFT with the input from the ADC
//! \author Vishal Coelho (Modified the original)
//! \date   03/26/2015   
//! 
//! This program shows how to compute a real FFT with 12-bit real-time ADC 
//! input and associated spectrum magnitude, phase. EPWM1 and 2 are setup 
//! such that EPWM2 outputs a square wave at a frequency 10 times slower 
//! than EPWM1; EPWM1 serves as the sample clock to the ADC which will 
//! sample EPWM2A (pin 53) through channel A0 (pin 09) and then run the FFT. 
//! The real time FFT is computed frame-by-frame. Once a entire frame is 
//! filled up in the ADC ISR, it sets off a flag to start the FFT. The 
//! flag is reset once the computation is complete
//!
//! \note This example uses the F2837xD controlCARD Rev1.1
//! \note The input buffer must be aligned to a 2N word boundary, N being the
//! size of the real FFT. The user may choose to use an alternative routine, 
//! RFFT_adc_f32u(), if alignment is not possible (or not desired). In that 
//! case, the section alignment #pragma can be commented.  However, using this 
//! function will reduce cycle performance of the algorithm.
//!
//  Group:             C2000
//  Target Family:     F2837x
//
//#############################################################################
//
//
// $Copyright: Copyright (C) 2018 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################

//*****************************************************************************
// includes
//*****************************************************************************
#include "fpu_rfft.h"            // Main include file
#include "math.h"
#include "examples_setup.h"

//!
//! \addtogroup RFFT_EXAMPLES Real FFT of the ADC Input (Real-Time)

// @{
//*****************************************************************************
// defines
//*****************************************************************************
#define RFFT_STAGES     9
#define RFFT_SIZE       (1 << RFFT_STAGES) 
#define F_PER_SAMPLE    (ADC_SAMPLING_FREQ/(float)RFFT_SIZE)
#define USE_TEST_INPUT  1 // If not in test mode, be sure to exclude signal.asm
                          // from the build
#define EPSILON         0.1
//*****************************************************************************
// globals
//*****************************************************************************

#ifdef __cplusplus
#pragma DATA_SECTION("RFFTdata1")
#else
#pragma DATA_SECTION(RFFTin1Buff,"RFFTdata1")
#endif //__cplusplus
//! \brief FFT Calculation Buffer
//! \note The input buffer needs to be aligned to an 2N word boundary
//! \note If the number of FFT stages is odd, the result of the FFT will
//! be written to this buffer
//! \note this buffer takes N 12-bit ADC input, hence its defined as an
//! unsigned int array, but the FFT algorithm ping-pongs between input/
//! output buffers each stage, therefore this buffer needs to be able 
//! to accommodate N floats and should be of size 2*RFFT_SIZE
uint16_t RFFTin1Buff[2*RFFT_SIZE];

#ifdef __cplusplus
#pragma DATA_SECTION("RFFTdata2")
#else
#pragma DATA_SECTION(RFFTmagBuff,"RFFTdata2")
#endif //__cplusplus
//! \brief Magnitude Calculation Buffer
//!
float RFFTmagBuff[RFFT_SIZE/2+1];               

#ifdef __cplusplus
#pragma DATA_SECTION("RFFTdata2")
#else
#pragma DATA_SECTION(RFFTphaseBuff,"RFFTdata2")
#endif //__cplusplus
//! \brief Phase Calculation Buffer
//!
float RFFTphaseBuff[RFFT_SIZE/2]; 

#ifdef __cplusplus
#pragma DATA_SECTION("RFFTdata3")
#else
#pragma DATA_SECTION(RFFToutBuff,"RFFTdata3")
#endif //__cplusplus
//! \brief FFT Calculation Buffer
//! \note If the number of FFT stages is even, the result of the FFT will
//! be written to this buffer
//!
float RFFToutBuff[RFFT_SIZE];

#ifdef __cplusplus
#pragma DATA_SECTION("RFFTdata4")
#else
#pragma DATA_SECTION(RFFTF32Coef,"RFFTdata4")
#endif //__cplusplus
//! \brief Twiddle Factors
//!
float RFFTF32Coef[RFFT_SIZE];

//! \brief RFFT_ADC_F32_STRUCT object
//!
RFFT_ADC_F32_STRUCT rfft_adc;

//! \brief Handle to the RFFT_ADC_F32_STRUCT object
//! 
RFFT_ADC_F32_STRUCT_Handle hnd_rfft_adc = &rfft_adc;

//! \brief RFFT_F32_STRUCT object
//!
RFFT_F32_STRUCT rfft;

//! \brief Handle to the RFFT_F32_STRUCT object
//!
RFFT_F32_STRUCT_Handle hnd_rfft = &rfft;

//! \brief Flag to signal the ADC has finished sampling, and storing, 
//! N points in the FFT input buffer
//!
volatile uint16_t flagInputReady = 0;

//! \brief Index into the FFT input buffer
//!
volatile uint16_t sampleIndex = 0;

//*****************************************************************************
// Function Prototypes
//*****************************************************************************
__interrupt void adcaIsr();
//*****************************************************************************
// function definitions
//*****************************************************************************
//!
//! \brief main routine for the 512-sample RFFT ADC example
//! \return returns a 1
//!
//! This program shows how to compute the real FFT, magnitude and phase of 
//! data from the 12-bit ADC input. The input buffer must be aligned to a 
//! 2N word boundary if using RFFT_f32.  
//! Data section alignment (#pragma ...) is not necessary for RFFT_adc_f32u 
//! but necessary when running RFFT_adc_f32.  However, using the unaligned 
//! version will reduce cycle performance of the algorithm.
//!
//! The minimum number of stages is 3. When the number of stages is more 
//! than 9, the quantization error would be significant and not recommended. 
//! This example will sample an EPWM channel over an ADC channel and run the 
//! RFFT on a real signal.
//!
//! RFFT_F32_STRUCT is a structure defined as:
//!
//!    typedef struct {
//!      float  *InBuf;
//!      float  *OutBuf;
//!      float  *CosSinBuf;
//!      float  *MagBuf;
//!      float  *PhaseBuf;
//!      uint16_t FFTSize;
//!      uint16_t FFTStages;
//!    } RFFT_F32_STRUCT;
//! 
//! RFFT_ADC_F32_STRUCT is defined as:
//!    typedef struct {
//!      uint16_t   *InBuf;
//!      void       *Tail; 
//!    } RFFT_ADC_F32_STRUCT;
//!
//!  ASSUMPTIONS:
//!
//! -# OutBuf of RFFT_F32_STRUCT has to be passed to Tail of 
//!    RFFT_ADC_F32_STRUCT
//! -# Input signal is stored in Signal.asm
//! -# FFTSize must be a power of 2 (32, 64, 128, etc)
//! -# FFTSize must be greater or equal to 32
//! -# FFTStages must be log2(FFTSize)
//! -# InBuf, OutBuf, CosSinBuf are FFTSize in length
//! -# Magnitude buffer is FFTSize/2+1 in length
//! -# Phase buffer is FFTSize/2 in length
//!
//! Watch Variables:
//!
//! -# InBuf(RFFT_ADC_F32_STRUCT)    Input buffer
//! -# InBuf(RFFT_F32_STRUCT)        Not used
//! -# Tail                          Stored the address of OutBuf
//! -# OutBuf                        Output buffer
//! -# CosSinBuf                     Twiddle factor buffer
//! -# MagBuf                        Magnitude buffer
//! -# PhaseBuf                      Phase buffer
//! -# j                             Index of normalized digital frequency component
//! -# freq                          Real analog frequency of raw signal
//!
//! External Connections:
//! Connect A0 (pin 9) to EPWM2A (pin 53) on the F2837x controlCARD. Refer to the
//! board schematic for pin positioning.
//! \note  The ADC will sample a 50% duty cycle 1KHz wave (EPWM2A) at 100KHz
//! and run the FFT on it. Since the input is a square wave, you will
//! see the fundamental frequency, 1KHz, at the 5th bin 
//! (5*fs/N = 5*100K/512 = 976.5) and all its odd harmonics. Since the sampled 
//! waveform is not an integer multiple of the FFT_SIZE, you will see some 
//! spectral leakage, a portion of the fundamental will leak into the 6th bin. 
//! One way to overcome this is to window the input before running the FFT on 
//! it.
//!
int16_t main(void)
{
    // Locals
    uint16_t i, j;
    float freq = 0.0;

#ifdef FLASH
    EALLOW;
    Flash0EccRegs.ECC_ENABLE.bit.ENABLE = 0;
    memcpy((uint32_t *)&RamfuncsRunStart, (uint32_t *)&RamfuncsLoadStart,
            (uint32_t)&RamfuncsLoadSize );
    FPU_initFlash();
#endif //FLASH
    
    FPU_initSystemClocks();
    
    FPU_initEpie();

    // Setup ADC-A
    FPU_initADCA();
    
    //Setup EPWM1A as the sampling clock, EPWM2A as the signal to be
    //sampled
    FPU_initEPWM(); 
    
    //Map ISR functions
    EALLOW;
    PieVectTable.ADCA1_INT = &adcaIsr; //function for ADCA interrupt 1
    EDIS;
    //Enable global Interrupts and higher priority real-time debug events:
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1; //Enable ADC1INT
    IER |= M_INT1;  //Enable group 1 interrupts
    EINT;           // Enable Global interrupt INTM
    ERTM;           // Enable Global realtime interrupt DBGM
    
    //Start up the EPWMs
    FPU_startEPWM();
    
    //Link the RFFT_ADC_F32_STRUCT to RFFT_F32_STRUCT. Tail pointer 
    //of RFFT_ADC_F32_STRUCT is passed to the OutBuf pointer of 
    //RFFT_F32_STRUCT 
    hnd_rfft_adc->Tail = &(hnd_rfft->OutBuf);
    
    hnd_rfft->FFTSize   = RFFT_SIZE;         //FFT size
    hnd_rfft->FFTStages = RFFT_STAGES;       //FFT stages

    hnd_rfft_adc->InBuf = &RFFTin1Buff[0];   //Input buffer (12-bit ADC input)
    hnd_rfft->OutBuf    = &RFFToutBuff[0];   //Output buffer
    hnd_rfft->CosSinBuf = &RFFTF32Coef[0];   //Twiddle factor 
    hnd_rfft->MagBuf    = &RFFTmagBuff[0];   //Magnitude output buffer
    hnd_rfft->PhaseBuf  = &RFFTphaseBuff[0]; //Phase output buffer
    
    RFFT_f32_sincostable(hnd_rfft);          //Calculate twiddle factor

    for (i=0; i < RFFT_SIZE; i++){
        RFFToutBuff[i] = 0;                  //Clean up output buffer
    }                                        
                                             
    for (i=0; i <= RFFT_SIZE/2; i++){        
        RFFTmagBuff[i] = 0;                  //Clean up magnitude buffer
    }                                        
                                             
    for (i=0; i < RFFT_SIZE/2; i++){         
        RFFTphaseBuff[i] = 0;                //Clean up phase buffer
    } 
    
    while(1){
        while(flagInputReady == 0){}; // Wait on ADC ISR to set the flag 
                                      // before proceeding
        RFFT_adc_f32(hnd_rfft_adc);   // Calculate real FFT (12-bit ADC input)
        flagInputReady = 0;           // Reset the flag
        
#ifdef __TMS320C28XX_TMU__ //defined when --tmu_support=tmu0 in the project 
                           // properties
        RFFT_f32_mag_TMU0(hnd_rfft);        //Calculate magnitude
        RFFT_f32_phase_TMU0(hnd_rfft);      //Calculate phase
#else                                       
        RFFT_f32_mag(hnd_rfft);             //Calculate magnitude
        RFFT_f32_phase(hnd_rfft);           //Calculate phase
#endif //__TMS320C28XX_TMU__

        //Find out the maximum frequency component of signal frequency 
        //component signal. This algorithm is only used for finding frequency 
        //of one component frequency signal; in this example it gives the
        //fundamental frequency of the sampled square wave
        j = 1;
        freq = RFFTmagBuff[1];
        for(i=2;i<RFFT_SIZE/2+1;i++){
        //Looking for the maximum component of frequency spectrum
            if(RFFTmagBuff[i] > freq){
                j = i;
                freq = RFFTmagBuff[i];
            }
        }

        //Converting normalized digital frequency to real analog frequency
        //f = m * fs/N
        // where m is the bin with the maximum value, fs the sampling
        // frequency and N the number of points in the FFT
        freq = F_PER_SAMPLE * (float)j;     
    }

    // Execution never reaches this point
    return 1;
}

// End of main

//! \brief ADC Interrupt Service Routine
//! The ISR will store each sampled value in the FFT buffer, and
//! raise the flag once the buffer is full
//!
__interrupt void adcaIsr()
{
    RFFTin1Buff[sampleIndex++] = AdcaResultRegs.ADCRESULT0;
    if(sampleIndex == (RFFT_SIZE - 1) ){
        sampleIndex = 0;
        flagInputReady = 1;
    }

    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear INT1 flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

// @} //addtogroup

// End of file
