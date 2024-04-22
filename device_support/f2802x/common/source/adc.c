//#############################################################################
//
//! \file   f2802x_common/source/adc.c
//!
//! \brief  Contains the various functions related to the analog-to-digital 
//!         converter (ADC) object
//
//  Group:          C2000
//  Target Device:  TMS320F2802x
//
//#############################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:
// Copyright (C) 2009-2024 Texas Instruments Incorporated - http://www.ti.com/
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
#include "adc.h"

extern void usDelay(unsigned long Count);

//
// ADC_disable -
//
void
ADC_disable(ADC_Handle adcHandle)
{
    ADC_Obj *adc = (ADC_Obj *)adcHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    adc->ADCCTL1 &= (~ADC_ADCCTL1_ADCENABLE_BITS);

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
} 

//
// ADC_disableBandGap - 
//
void
ADC_disableBandGap(ADC_Handle adcHandle)
{
    ADC_Obj *adc = (ADC_Obj *)adcHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // clear the bits
    //
    adc->ADCCTL1 &= (~ADC_ADCCTL1_ADCBGPWD_BITS);

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// ADC_disableInt - 
//
void
ADC_disableInt(ADC_Handle adcHandle, const ADC_IntNumber_e intNumber)
{
    ADC_Obj *adc = (ADC_Obj *)adcHandle;
    uint_least8_t regNumber = intNumber >> 1;
    uint16_t clearValue = ADC_INTSELxNy_INTE_BITS << 
                          (ADC_INTSELxNy_NUMBITS_PER_REG - ((intNumber & 0x1) 
                          << ADC_INTSELxNy_LOG2_NUMBITS_PER_REG));

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;
    
    //
    // clear the bits
    //
    adc->INTSELxNy[regNumber] &= (~clearValue);

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// ADC_disableRefBuffers -
//
void
ADC_disableRefBuffers(ADC_Handle adcHandle)
{
    ADC_Obj *adc = (ADC_Obj *)adcHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;
    
    //
    // clear the bits
    //
    adc->ADCCTL1 &= (~ADC_ADCCTL1_ADCREFPWD_BITS);

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// ADC_disableTempSensor - 
//
void
ADC_disableTempSensor(ADC_Handle adcHandle)
{
    ADC_Obj *adc = (ADC_Obj *)adcHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;
    
    //
    // Disable Temp Sensor conversion
    //
    adc->ADCCTL1 &= ~ADC_ADCCTL1_TEMPCONV_BITS;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// ADC_enable -
//
void
ADC_enable(ADC_Handle adcHandle)
{
    ADC_Obj *adc = (ADC_Obj *)adcHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // set the bits
    //
    adc->ADCCTL1 |= ADC_ADCCTL1_ADCENABLE_BITS;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// ADC_enableBandGap - 
// 
void
ADC_enableBandGap(ADC_Handle adcHandle)
{
    ADC_Obj *adc = (ADC_Obj *)adcHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // set the bits
    //
    adc->ADCCTL1 |= ADC_ADCCTL1_ADCBGPWD_BITS;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// ADC_enableInt - 
//
void
ADC_enableInt(ADC_Handle adcHandle, const ADC_IntNumber_e intNumber)
{
    ADC_Obj *adc = (ADC_Obj *)adcHandle;
    uint_least8_t regNumber = intNumber >> 1;
    uint_least8_t lShift = ADC_INTSELxNy_NUMBITS_PER_REG - (((intNumber+1) &
                           0x1) << ADC_INTSELxNy_LOG2_NUMBITS_PER_REG);
    uint16_t setValue = ADC_INTSELxNy_INTE_BITS << lShift;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;
    
    //
    // set the value
    //
    adc->INTSELxNy[regNumber] |= setValue;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}
 
//
// ADC_enableRefBuffers -
//
void
ADC_enableRefBuffers(ADC_Handle adcHandle)
{
    ADC_Obj *adc = (ADC_Obj *)adcHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // set the bits
    //
    adc->ADCCTL1 |= ADC_ADCCTL1_ADCREFPWD_BITS;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// ADC_enableTempSensor -
//
void
ADC_enableTempSensor(ADC_Handle adcHandle)
{
    ADC_Obj *adc = (ADC_Obj *)adcHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // Enable Temp Sensor conversion
    //
    adc->ADCCTL1 |= ADC_ADCCTL1_TEMPCONV_BITS;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// ADC_init - current sampled last
//
ADC_Handle
ADC_init(void *pMemory, const size_t numBytes)
{
    ADC_Handle adcHandle;

    if(numBytes < sizeof(ADC_Obj))
    {
        return((ADC_Handle)NULL);
    }
    
    //
    // assign the handle
    //
    adcHandle = (ADC_Handle)pMemory;

    return(adcHandle);
}

//
// ADC_powerDown - 
//
void
ADC_powerDown(ADC_Handle adcHandle)
{
    ADC_Obj *adc = (ADC_Obj *)adcHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // clear the bits
    //
    adc->ADCCTL1 &= (~ADC_ADCCTL1_ADCPWDN_BITS);

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// ADC_powerUp - 
//
void
ADC_powerUp(ADC_Handle adcHandle)
{
    ADC_Obj *adc = (ADC_Obj *)adcHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // set the bits
    //
    adc->ADCCTL1 |= ADC_ADCCTL1_ADCPWDN_BITS;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// ADC_reset
//
void
ADC_reset(ADC_Handle adcHandle)
{
    ADC_Obj *adc = (ADC_Obj *)adcHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // set the bits
    //
    adc->ADCCTL1 |= (uint16_t)ADC_ADCCTL1_RESET_BITS;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// ADC_setIntMode - 
//
void
ADC_setIntMode(ADC_Handle adcHandle, const ADC_IntNumber_e intNumber, 
               const ADC_IntMode_e intMode)
{
    ADC_Obj *adc = (ADC_Obj *)adcHandle;
    uint_least8_t regNumber = intNumber >> 1;
    uint_least8_t lShift = (ADC_INTSELxNy_NUMBITS_PER_REG - (((intNumber+1) &
                            0x1) << ADC_INTSELxNy_LOG2_NUMBITS_PER_REG));
    uint16_t clearValue = ADC_INTSELxNy_INTCONT_BITS << lShift;
    uint16_t setValue = intMode << lShift;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // clear the bits
    //
    adc->INTSELxNy[regNumber] &= ~(clearValue);

    //
    // set the bits
    //
    adc->INTSELxNy[regNumber] |= setValue;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// ADC_setIntPulseGenMode -
//
void
ADC_setIntPulseGenMode(ADC_Handle adcHandle, 
                       const ADC_IntPulseGenMode_e pulseMode)
{
    ADC_Obj *adc = (ADC_Obj *)adcHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // clear the bits
    //
    adc->ADCCTL1 &= (~ADC_ADCCTL1_INTPULSEPOS_BITS);

    //
    // set the bits
    //
    adc->ADCCTL1 |= pulseMode;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// ADC_setIntSrc -
//
void
ADC_setIntSrc(ADC_Handle adcHandle, const ADC_IntNumber_e intNumber, 
              const ADC_IntSrc_e intSrc)
{
    ADC_Obj *adc = (ADC_Obj *)adcHandle;
    uint_least8_t regNumber = intNumber >> 1;
    uint_least8_t lShift = (ADC_INTSELxNy_NUMBITS_PER_REG - (((intNumber+1) & 
                            0x1) << ADC_INTSELxNy_LOG2_NUMBITS_PER_REG));
    uint16_t clearValue = ADC_INTSELxNy_INTSEL_BITS << lShift;
    uint16_t setValue = intSrc << lShift;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // clear the bits
    //
    adc->INTSELxNy[regNumber] &= ~(clearValue);

    //
    // set the bits
    //
    adc->INTSELxNy[regNumber] |= setValue;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// ADC_setSampleMode - 
//
void
ADC_setSampleMode(ADC_Handle adcHandle, const ADC_SampleMode_e sampleMode)
{
    ADC_Obj *adc = (ADC_Obj *)adcHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    if(sampleMode & ADC_ADCSAMPLEMODE_SEPARATE_FLAG) // separate
    {
        adc->ADCSAMPLEMODE &= (~(sampleMode - 
                               ADC_ADCSAMPLEMODE_SEPARATE_FLAG));
    }
    else
    {
        adc->ADCSAMPLEMODE |= sampleMode;
    }

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// ADC_setSocChanNumber -
//
void
ADC_setSocChanNumber(ADC_Handle adcHandle, const ADC_SocNumber_e socNumber, 
                     const ADC_SocChanNumber_e chanNumber)
{
    ADC_Obj *adc = (ADC_Obj *)adcHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // clear the bits
    //
    adc->ADCSOCxCTL[socNumber] &= (~ADC_ADCSOCxCTL_CHSEL_BITS);
    
    //
    // set the bits
    //
    adc->ADCSOCxCTL[socNumber] |= chanNumber;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// ADC_setSocSampleWindow -
//
void
ADC_setSocSampleWindow(ADC_Handle adcHandle, const ADC_SocNumber_e socNumber, 
                            const ADC_SocSampleWindow_e sampleWindow)
{
    ADC_Obj *adc = (ADC_Obj *)adcHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // clear the bits
    //
    adc->ADCSOCxCTL[socNumber] &= (~ADC_ADCSOCxCTL_ACQPS_BITS);

    //
    // set the bits
    //
    adc->ADCSOCxCTL[socNumber] |= sampleWindow;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// ADC_setSocTrigSrc -
//
void
ADC_setSocTrigSrc(ADC_Handle adcHandle, const ADC_SocNumber_e socNumber, 
                  const ADC_SocTrigSrc_e trigSrc)
{
    ADC_Obj *adc = (ADC_Obj *)adcHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;
    
    //
    // clear the bits
    //
    adc->ADCSOCxCTL[socNumber] &= (~ADC_ADCSOCxCTL_TRIGSEL_BITS);

    //
    // set the bits
    //
    adc->ADCSOCxCTL[socNumber] |= trigSrc;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// ADC_setVoltRefSrc -
//
void
ADC_setVoltRefSrc(ADC_Handle adcHandle, const ADC_VoltageRefSrc_e voltSrc)
{
    ADC_Obj *adc = (ADC_Obj *)adcHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // clear the bits
    //
    adc->ADCCTL1 &= (~ADC_ADCCTL1_ADCREFSEL_BITS);
    
    //
    // set the bits
    //
    adc->ADCCTL1 |= voltSrc;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// End of file
//

