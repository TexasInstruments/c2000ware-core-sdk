//#############################################################################
//
//! \file   f2802x0/common/source/pwm.c
//!
//! \brief  Contains the various functions related to the 
//!         pulse width modulation (PWM) object
//
//  Group:          C2000
//  Target Device:  TMS320F2802x0
//
//#############################################################################
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
//#############################################################################

//
// Included Files
//
#include "DSP28x_Project.h"
#include "pwm.h"

//
// PWM_clearTripZone
//
void
PWM_clearTripZone(PWM_Handle pwmHandle, const PWM_TripZoneFlag_e tripZoneFlag)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;
    
    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // set the bits
    //
    pwm->TZCLR |= tripZoneFlag;
    
    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// PWM_decrementDeadBandFallingEdgeDelay - 
//
void
PWM_decrementDeadBandFallingEdgeDelay(PWM_Handle pwmHandle)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    pwm->DBFED--;

    return;
}

//
// PWM_decrementDeadBandRisingEdgeDelay - 
//
void
PWM_decrementDeadBandRisingEdgeDelay(PWM_Handle pwmHandle)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    pwm->DBRED--;

    return;
}

//
// PWM_disableChopping -
//
void
PWM_disableChopping(PWM_Handle pwmHandle)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //
    pwm->PCCTL &= (~PWM_PCCTL_CHPEN_BITS);

    return;
}

//
// PWM_disableCounterLoad - 
//
void
PWM_disableCounterLoad(PWM_Handle pwmHandle)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //
    pwm->TBCTL &= (~PWM_TBCTL_PHSEN_BITS);

    return;
}

//
// PWM_disableDeadBand - 
//
void
PWM_disableDeadBand(PWM_Handle pwmHandle)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //
    pwm->DBCTL = 0;

    return;
}

//
// PWM_disableDeadBandHalfCycle -
//
void
PWM_disableDeadBandHalfCycle(PWM_Handle pwmHandle)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;
    
    //
    // clear the bits
    //
    pwm->DBCTL &= (~PWM_DBCTL_HALFCYCLE_BITS);

    return;
}

//
// PWM_disableDigitalCompareBlankingWindow - 
//
void
PWM_disableDigitalCompareBlankingWindow(PWM_Handle pwmHandle)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // set the bits
    //
    pwm->DCFCTL &= ~PWM_DCFCTL_BLANKE_BITS;
    
    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// PWM_disableDigitalCompareBlankingWindowInversion - 
//
void
PWM_disableDigitalCompareBlankingWindowInversion(PWM_Handle pwmHandle)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // set the bits
    //
    pwm->DCFCTL &= ~PWM_DCFCTL_BLANKINV_BITS;
    
    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// PWM_disableInt - 
//
void
PWM_disableInt(PWM_Handle pwmHandle)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //
    pwm->ETSEL &= (~PWM_ETSEL_INTEN_BITS);

    return;
}

//
// PWM_disableSocAPulse -
//
void
PWM_disableSocAPulse(PWM_Handle pwmHandle)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //    
    pwm->ETSEL &= (~PWM_ETSEL_SOCAEN_BITS);

    return;
}

//
// PWM_disableSocBPulse -
//
void
PWM_disableSocBPulse(PWM_Handle pwmHandle)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //
    pwm->ETSEL &= (~PWM_ETSEL_SOCBEN_BITS);

    return;
} 

//
// PWM_disableTripZones - 
//
void
PWM_disableTripZones(PWM_Handle pwmHandle)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // set the bits
    //
    pwm->TZSEL = 0;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// PWM_disableTripZoneInt - 
//
void
PWM_disableTripZoneInt(PWM_Handle pwmHandle,
                       const PWM_TripZoneFlag_e interruptSource)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // set the bits
    //
    pwm->TZEINT &= ~interruptSource;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// PWM_disableTripZoneSrc -
//
void
PWM_disableTripZoneSrc(PWM_Handle pwmHandle, const PWM_TripZoneSrc_e src)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // clear the bits
    //
    pwm->TZSEL &= (~src);

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// PWM_enableChopping -
//
void
PWM_enableChopping(PWM_Handle pwmHandle)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // set the bits
    //
    pwm->PCCTL = (uint16_t)1;

    return;
}

//
// PWM_enableCounterLoad -
//
void
PWM_enableCounterLoad(PWM_Handle pwmHandle)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // set the bits
    //
    pwm->TBCTL |= PWM_TBCTL_PHSEN_BITS;

    return;
}

//
// PWM_enableDeadBandHalfCycle - 
//
void
PWM_enableDeadBandHalfCycle(PWM_Handle pwmHandle)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // set the bits
    //
    pwm->DBCTL |= (uint16_t)PWM_DBCTL_HALFCYCLE_BITS;

    return;
}

//
// PWM_enableDigitalCompareBlankingWindow - 
//
void
PWM_enableDigitalCompareBlankingWindow(PWM_Handle pwmHandle)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;
    
    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // set the bits
    //
    pwm->DCFCTL |= PWM_DCFCTL_BLANKE_BITS;
    
    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// PWM_enableDigitalCompareBlankingWindowInversion - 
//
void
PWM_enableDigitalCompareBlankingWindowInversion(PWM_Handle pwmHandle)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // set the bits
    //
    pwm->DCFCTL |= PWM_DCFCTL_BLANKINV_BITS;
    
    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// PWM_enableInt -
//
void
PWM_enableInt(PWM_Handle pwmHandle)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // set the bits
    //
    pwm->ETSEL |= PWM_ETSEL_INTEN_BITS;

    return;
}

//
// PWM_enableSocAPulse - 
//
void
PWM_enableSocAPulse(PWM_Handle pwmHandle)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // set the bits
    //
    pwm->ETSEL |= PWM_ETSEL_SOCAEN_BITS;

    return;
}

//
// PWM_enableSocBPulse - 
//
void
PWM_enableSocBPulse(PWM_Handle pwmHandle)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // set the bits
    //
    pwm->ETSEL |= (uint16_t)PWM_ETSEL_SOCBEN_BITS;

    return;
}

//
// PWM_enableTripZoneInt - 
//
void
PWM_enableTripZoneInt(PWM_Handle pwmHandle, 
                      const PWM_TripZoneFlag_e interruptSource)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // set the bits
    //
    pwm->TZEINT |= interruptSource;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// PWM_enableTripZoneSrc - 
//
void
PWM_enableTripZoneSrc(PWM_Handle pwmHandle, const PWM_TripZoneSrc_e src)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // set the bits
    //
    pwm->TZSEL |= src;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// PWM_getDeadBandFallingEdgeDelay -
//
uint16_t
PWM_getDeadBandFallingEdgeDelay(PWM_Handle pwmHandle)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    return (pwm->DBFED);
}

//
// PWM_getDeadBandRisingEdgeDelay -
//
uint16_t
PWM_getDeadBandRisingEdgeDelay(PWM_Handle pwmHandle)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    return (pwm->DBRED);
}

//
// PWM_getIntCount -
//
uint16_t
PWM_getIntCount(PWM_Handle pwmHandle)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;
    uint16_t intCount;

    intCount = pwm->ETPS & PWM_ETPS_INTCNT_BITS;

    return(intCount);
}

//
// PWM_getSocACount - 
//
uint16_t
PWM_getSocACount(PWM_Handle pwmHandle)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;
    uint16_t intCount;

    intCount = pwm->ETPS & PWM_ETPS_SOCACNT_BITS;

    intCount >>= 10;

    return(intCount);
}

//
// PWM_getSocBCount -
//
uint16_t
PWM_getSocBCount(PWM_Handle pwmHandle)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;
    uint16_t intCount;

    intCount = pwm->ETPS & (uint16_t)PWM_ETPS_SOCBCNT_BITS;

    intCount >>= 14;

    return(intCount);
}

//
// PWM_getShadowStatus_CmpA - 
//
PWM_ShadowStatus_e
PWM_getShadowStatus_CmpA(PWM_Handle pwmHandle)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;
    PWM_ShadowStatus_e status;

    //
    // clear the bits
    //
    status = (PWM_ShadowStatus_e)(pwm->TBCTL & (~PWM_CMPCTL_SHDWAFULL_BITS));

    status >>= 8;
    
    return(status);
}

//
// PWM_getShadowStatus_CmpB -
//
PWM_ShadowStatus_e
PWM_getShadowStatus_CmpB(PWM_Handle pwmHandle)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;
    PWM_ShadowStatus_e status;

    //
    // clear the bits
    //
    status = (PWM_ShadowStatus_e)(pwm->TBCTL & (~PWM_CMPCTL_SHDWAFULL_BITS));

    status >>= 9;
    
    return(status);
}

//
// PWM_incrementDeadBandFallingEdgeDelay - 
//
void
PWM_incrementDeadBandFallingEdgeDelay(PWM_Handle pwmHandle)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    pwm->DBFED++;

    return;
}

//
// PWM_incrementDeadBandRisingEdgeDelay -
// 
void
PWM_incrementDeadBandRisingEdgeDelay(PWM_Handle pwmHandle)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


    pwm->DBRED++;

    return;
}

//
// PWM_init -
//
PWM_Handle
PWM_init(void *pMemory, const size_t numBytes)
{
    PWM_Handle pwmHandle;

    if(numBytes < sizeof(PWM_Obj))
    {
        return((PWM_Handle)NULL);
    }

    //
    // assign the handle
    //
    pwmHandle = (PWM_Handle)pMemory;

    return(pwmHandle);
}

//
// PWM_setActionQual_CntDown_CmpA_PwmA - 
//
void
PWM_setActionQual_CntDown_CmpA_PwmA(PWM_Handle pwmHandle, 
                                    const PWM_ActionQual_e actionQual)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //
    pwm->AQCTLA &= (~PWM_AQCTL_CAD_BITS);

    //
    // set the bits
    //
    pwm->AQCTLA |= (actionQual << 6);

    return;
}

//
// PWM_setActionQual_CntDown_CmpA_PwmB - 
//
void
PWM_setActionQual_CntDown_CmpA_PwmB(PWM_Handle pwmHandle, 
                                    const PWM_ActionQual_e actionQual)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //
    pwm->AQCTLB &= (~PWM_AQCTL_CAD_BITS);

    //
    // set the bits
    //
    pwm->AQCTLB |= (actionQual << 6);

    return;
}

//
// PWM_setActionQual_CntDown_CmpB_PwmA -
//
void
PWM_setActionQual_CntDown_CmpB_PwmA(PWM_Handle pwmHandle,
                                    const PWM_ActionQual_e actionQual)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //
    pwm->AQCTLA &= (~PWM_AQCTL_CBD_BITS);

    //
    // set the bits
    //
    pwm->AQCTLA |= (actionQual << 10);

    return;
}

//
// PWM_setActionQual_CntDown_CmpB_PwmB - 
//
void
PWM_setActionQual_CntDown_CmpB_PwmB(PWM_Handle pwmHandle,
                                    const PWM_ActionQual_e actionQual)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //
    pwm->AQCTLB &= (~PWM_AQCTL_CBD_BITS);

    //
    // set the bits
    //
    pwm->AQCTLB |= (actionQual << 10);

    return;
}

//
// PWM_setActionQual_CntUp_CmpA_PwmA - 
//
void
PWM_setActionQual_CntUp_CmpA_PwmA(PWM_Handle pwmHandle,
                                  const PWM_ActionQual_e actionQual)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //
    pwm->AQCTLA &= (~PWM_AQCTL_CAU_BITS);

    //
    // set the bits
    //
    pwm->AQCTLA |= (actionQual << 4);

    return;
}

//
// PWM_setActionQual_CntUp_CmpA_PwmB - 
//
void
PWM_setActionQual_CntUp_CmpA_PwmB(PWM_Handle pwmHandle,
                                  const PWM_ActionQual_e actionQual)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //
    pwm->AQCTLB &= (~PWM_AQCTL_CAU_BITS);

    //
    // set the bits
    //
    pwm->AQCTLB |= (actionQual << 4);

    return;
}

//
// PWM_setActionQual_CntUp_CmpB_PwmA -
//
void
PWM_setActionQual_CntUp_CmpB_PwmA(PWM_Handle pwmHandle,
                                  const PWM_ActionQual_e actionQual)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //
    pwm->AQCTLA &= (~PWM_AQCTL_CBU_BITS);

    //
    // set the bits
    //
    pwm->AQCTLA |= (actionQual << 8);

    return;
}

//
// PWM_setActionQual_CntUp_CmpB_PwmB -
//
void
PWM_setActionQual_CntUp_CmpB_PwmB(PWM_Handle pwmHandle,
                                  const PWM_ActionQual_e actionQual)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //
    pwm->AQCTLB &= (~PWM_AQCTL_CBU_BITS);

    //
    // set the bits
    //
    pwm->AQCTLB |= (actionQual << 8);

    return;
}

//
// PWM_setActionQual_Period_PwmA - 
//
void
PWM_setActionQual_Period_PwmA(PWM_Handle pwmHandle,
                              const PWM_ActionQual_e actionQual)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //
    pwm->AQCTLA &= (~PWM_AQCTL_PRD_BITS);

    //
    // set the bits
    //
    pwm->AQCTLA |= (actionQual << 2);

    return;
}

//
// PWM_setActionQual_Period_PwmB - 
//
void
PWM_setActionQual_Period_PwmB(PWM_Handle pwmHandle,
                              const PWM_ActionQual_e actionQual)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //
    pwm->AQCTLB &= (~PWM_AQCTL_PRD_BITS);

    //
    // set the bits
    //
    pwm->AQCTLB |= (actionQual << 2);

    return;
}

//
// PWM_setActionQual_Zero_PwmA -
//
void
PWM_setActionQual_Zero_PwmA(PWM_Handle pwmHandle,
                            const PWM_ActionQual_e actionQual)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //
    pwm->AQCTLA &= (~PWM_AQCTL_ZRO_BITS);

    //
    // set the bits
    //
    pwm->AQCTLA |= actionQual;

    return;
}

//
// PWM_setActionQual_Zero_PwmB - 
//
void
PWM_setActionQual_Zero_PwmB(PWM_Handle pwmHandle, 
                            const PWM_ActionQual_e actionQual)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //
    pwm->AQCTLB &= (~PWM_AQCTL_ZRO_BITS);

    //
    // set the bits
    //
    pwm->AQCTLB |= actionQual;

    return;
}

//
// PWM_setChoppingClkFreq - 
//
void
PWM_setChoppingClkFreq(PWM_Handle pwmHandle,
                       const PWM_ChoppingClkFreq_e clkFreq)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //
    pwm->PCCTL &= (~PWM_PCCTL_CHPFREQ_BITS);

    //
    // set the bits
    //
    pwm->PCCTL |= clkFreq;

    return;
}

//
// PWM_setChoppingDutyCycle -
//
void
PWM_setChoppingDutyCycle(PWM_Handle pwmHandle,
                         const PWM_ChoppingDutyCycle_e dutyCycle)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //
    pwm->PCCTL &= (~PWM_PCCTL_CHPDUTY_BITS);

    //
    // set the bits
    //
    pwm->PCCTL |= dutyCycle;

    return;
}

//
// PWM_setChoppingPulseWidth - 
//
void
PWM_setChoppingPulseWidth(PWM_Handle pwmHandle, 
                          const PWM_ChoppingPulseWidth_e pulseWidth)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //
    pwm->PCCTL &= (~PWM_PCCTL_OSHTWTH_BITS);

    //
    // set the bits
    //
    pwm->PCCTL |= pulseWidth;

    return;
}

//
// PWM_setClkDiv - 
//
void
PWM_setClkDiv(PWM_Handle pwmHandle, const PWM_ClkDiv_e clkDiv)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //
    pwm->TBCTL &= (~PWM_TBCTL_CLKDIV_BITS);

    //
    // set the bits
    //
    pwm->TBCTL |= clkDiv;

    return;
}

//
// PWM_setCount 
//
void
PWM_setCount(PWM_Handle pwmHandle, const uint16_t count)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // set the bits
    //
    pwm->TBCTR = count;

    return;
}

//
// PWM_setCounterMode
//
void
PWM_setCounterMode(PWM_Handle pwmHandle, const PWM_CounterMode_e counterMode)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //
    pwm->TBCTL &= (~PWM_TBCTL_CTRMODE_BITS);

    //
    // set the bits
    //
    pwm->TBCTL |= counterMode;

    return;
}

//
// PWM_setDeadBandFallingEdgeDelay - 
//
void
PWM_setDeadBandFallingEdgeDelay(PWM_Handle pwmHandle, const uint16_t delay)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    pwm->DBFED |= delay;

    return;
}

//
// PWM_setDeadBandInputMode - 
//
void
PWM_setDeadBandInputMode(PWM_Handle pwmHandle,
                         const PWM_DeadBandInputMode_e inputMode)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //
    pwm->DBCTL &= (~PWM_DBCTL_INMODE_BITS);
    
    //
    // set the bits
    //
    pwm->DBCTL |= inputMode;

    return;
}

//
// PWM_setDeadBandOutputMode - 
//
void
PWM_setDeadBandOutputMode(PWM_Handle pwmHandle,
                          const PWM_DeadBandOutputMode_e outputMode)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //
    pwm->DBCTL &= (~PWM_DBCTL_OUTMODE_BITS);
    
    //
    // set the bits
    //
    pwm->DBCTL |= outputMode;

    return;
}

//
// PWM_setDeadBandPolarity - 
//
void
PWM_setDeadBandPolarity(PWM_Handle pwmHandle,
                        const PWM_DeadBandPolarity_e polarity)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //
    pwm->DBCTL &= (~PWM_DBCTL_POLSEL_BITS);
    
    //
    // set the bits
    //
    pwm->DBCTL |= polarity;

    return;
}

//
// PWM_setDeadBandRisingEdgeDelay - 
//
void
PWM_setDeadBandRisingEdgeDelay(PWM_Handle pwmHandle, const uint16_t delay)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    pwm->DBRED |= delay;

    return;
}

//
// PWM_setDigitalCompareFilterSource -
//
void
PWM_setDigitalCompareFilterSource(PWM_Handle pwmHandle, 
                                const PWM_DigitalCompare_FilterSrc_e input)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;
    
    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //    
    // Clear any old values
    //
    pwm->DCFCTL &= ~PWM_DCFCTL_SRCSEL_BITS;
    
    //
    // Set the new value
    //
    pwm->DCFCTL |= input;
    
    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// PWM_setDigitalCompareBlankingPulse - 
//
void
PWM_setDigitalCompareBlankingPulse(PWM_Handle pwmHandle, 
                                const PWM_DigitalCompare_PulseSel_e pulseSelect)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;
    
    ENABLE_PROTECTED_REGISTER_WRITE_MODE;
    
    //
    // Clear any old values
    //
    pwm->DCFCTL &= ~PWM_DCFCTL_PULSESEL_BITS;
    
    //
    // Set the new value
    //
    pwm->DCFCTL |= pulseSelect << 4;
    
    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// PWM_setDigitalCompareFilterOffset - 
//
void
PWM_setDigitalCompareFilterOffset(PWM_Handle pwmHandle, const uint16_t offset)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // Set the filter offset
    //
    pwm->DCFOFFSET = offset;

    return;
}

//
// PWM_setDigitalCompareFilterWindow -
//
void
PWM_setDigitalCompareFilterWindow(PWM_Handle pwmHandle, const uint16_t window)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // Set the window
    //
    pwm->DCFWINDOW = window;

    return;
}

//
// PWM_setDigitalCompareInput -
//
void
PWM_setDigitalCompareInput(PWM_Handle pwmHandle, 
                           const PWM_DigitalCompare_Input_e input, 
                           const PWM_DigitalCompare_InputSel_e inputSel)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;
    
    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // Clear any old values
    //
    pwm->DCTRIPSEL &= ~(0x000F << input);

    //
    // Set the new value
    //
    pwm->DCTRIPSEL |= (inputSel << input);
    
    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// PWM_setDigitalCompareAEvent1 -
//
void
PWM_setDigitalCompareAEvent1(PWM_Handle pwmHandle, const bool_t selectFilter,
                             const bool_t disableSync, const bool_t enableSoc,
                             const bool_t generateSync)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;
    
    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // Clear any old values
    //
    pwm->DCACTL &= ~0x000F;
    
    //
    // Set the new value
    //
    pwm->DCACTL |= selectFilter | (disableSync << 1) | (enableSoc << 2) | 
                   (generateSync << 3);
    
    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
//
//
void PWM_setDigitalCompareAEvent2(PWM_Handle pwmHandle, 
                                  const bool_t selectFilter,
                                  const bool_t disableSync)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;
    
    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // Clear any old values
    //
    pwm->DCACTL &= ~0x0300;
    
    //
    // Set the new value
    //
    pwm->DCACTL |= (selectFilter << 8) | (disableSync << 9) ;
    
    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// PWM_setDigitalCompareBEvent1 - 
//
void
PWM_setDigitalCompareBEvent1(PWM_Handle pwmHandle, const bool_t selectFilter,
                             const bool_t disableSync, const bool_t enableSoc,
                             const bool_t generateSync)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;
    
    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // Clear any old values
    //
    pwm->DCBCTL &= ~0x000F;
    
    //
    // Set the new value
    //
    pwm->DCBCTL |= selectFilter | (disableSync << 1) | (enableSoc << 2) | 
                   (generateSync << 3);
    
    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// PWM_setDigitalCompareBEvent2 - 
//
void
PWM_setDigitalCompareBEvent2(PWM_Handle pwmHandle, const bool_t selectFilter,
                             const bool_t disableSync)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;
    
    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // Clear any old values
    //
    pwm->DCBCTL &= ~0x0300;
    
    //
    // Set the new value
    //
    pwm->DCBCTL |= (selectFilter << 8) | (disableSync << 9) ;
    
    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// PWM_setPeriod -
//
void
PWM_setPeriod(PWM_Handle pwmHandle, const uint16_t period)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;
    
    //
    // initialize the Time-Base Period Register (TBPRD). 
    // These bits determine the period of the time-base counter.
    //
    pwm->TBPRD = period;
    return;
}

//
// PWM_setHighSpeedClkDiv - 
//
void
PWM_setHighSpeedClkDiv(PWM_Handle pwmHandle, const PWM_HspClkDiv_e clkDiv)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //
    pwm->TBCTL &= (~PWM_TBCTL_HSPCLKDIV_BITS);

    //
    // set the bits
    //
    pwm->TBCTL |= clkDiv;

    return;
}

//
// PWM_setIntMode - 
//
void
PWM_setIntMode(PWM_Handle pwmHandle, const PWM_IntMode_e intMode)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //
    pwm->ETSEL &= (~PWM_ETSEL_INTSEL_BITS);

    //
    // set the bits
    //
    pwm->ETSEL |= intMode;

    return;
}

//
// PWM_setIntPeriod - 
//
void
PWM_setIntPeriod(PWM_Handle pwmHandle, const PWM_IntPeriod_e intPeriod)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //
    pwm->ETPS &= (~PWM_ETPS_INTPRD_BITS);

    //
    // set the bits
    //
    pwm->ETPS |= intPeriod;

    return;
}

//
// PWM_setLoadMode_CmpA - 
//
void
PWM_setLoadMode_CmpA(PWM_Handle pwmHandle, const PWM_LoadMode_e loadMode)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //
    pwm->CMPCTL &= (~PWM_CMPCTL_LOADAMODE_BITS);

    //
    // set the bits
    //
    pwm->CMPCTL |= loadMode;

    return;
}

//
// PWM_setLoadMode_CmpB -
//
void
PWM_setLoadMode_CmpB(PWM_Handle pwmHandle, const PWM_LoadMode_e loadMode)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //
    pwm->CMPCTL &= (~PWM_CMPCTL_LOADBMODE_BITS);

    //
    // set the bits
    //
    pwm->CMPCTL |= (loadMode << 2);

    return;
}

//
// PWM_setPhase - 
//
void
PWM_setPhase(PWM_Handle pwmHandle, const uint16_t phase)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    pwm->TBPHS = phase;

    return;
}

//
// PWM_setPhaseDir -
//
void
PWM_setPhaseDir(PWM_Handle pwmHandle, const PWM_PhaseDir_e phaseDir)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //
    pwm->TBCTL &= (~PWM_TBCTL_PHSDIR_BITS);

    //
    // set the bits
    //
    pwm->TBCTL |= phaseDir;

    return;
}

//
// PWM_setPeriodLoad - 
//
void
PWM_setPeriodLoad(PWM_Handle pwmHandle, const PWM_PeriodLoad_e periodLoad)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //
    pwm->TBCTL &= (~PWM_TBCTL_PRDLD_BITS);

    //
    // set the bits
    //
    pwm->TBCTL |= periodLoad;

    return;
}

//
// PWM_setRunMode -
//
void
PWM_setRunMode(PWM_Handle pwmHandle, const PWM_RunMode_e runMode)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //
    pwm->TBCTL &= (~PWM_TBCTL_FREESOFT_BITS);

    //
    // set the bits
    //
    pwm->TBCTL |= runMode;

    return;
}

//
// PWM_setSocAPeriod -
//
void
PWM_setSocAPeriod(PWM_Handle pwmHandle, const PWM_SocPeriod_e intPeriod)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //
    pwm->ETPS &= (~PWM_ETPS_SOCAPRD_BITS);

    //
    // set the bits
    //
    pwm->ETPS |= (intPeriod << 8);

    return;
}

//
// PWM_setSocAPulseSrc -
//
void
PWM_setSocAPulseSrc(PWM_Handle pwmHandle, const PWM_SocPulseSrc_e pulseSrc)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //
    pwm->ETSEL &= (~PWM_ETSEL_SOCASEL_BITS);

    //
    // set the bits
    //
    pwm->ETSEL |= (pulseSrc << 8);

    return;
}

//
// PWM_setSocBPeriod -
//
void
PWM_setSocBPeriod(PWM_Handle pwmHandle, const PWM_SocPeriod_e intPeriod)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //
    pwm->ETPS &= (~PWM_ETPS_SOCBPRD_BITS);

    //
    // set the bits
    //
    pwm->ETPS |= (intPeriod << 12);

    return;
}

//
// PWM_setSocBPulseSrc -
// 
void
PWM_setSocBPulseSrc(PWM_Handle pwmHandle, const PWM_SocPulseSrc_e pulseSrc)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //
    pwm->ETSEL &= (~PWM_ETSEL_SOCBSEL_BITS);

    //
    // set the bits
    //
    pwm->ETSEL |= (pulseSrc << 12);

    return;
}

//
// PWM_setShadowMode_CmpA -
//
void
PWM_setShadowMode_CmpA(PWM_Handle pwmHandle, const PWM_ShadowMode_e shadowMode)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //
    pwm->CMPCTL &= (~PWM_CMPCTL_SHDWAMODE_BITS);

    //
    // set the bits
    //
    pwm->CMPCTL |= (shadowMode << 4);

    return;
}

//
// PWM_setShadowMode_CmpB - 
// 
void
PWM_setShadowMode_CmpB(PWM_Handle pwmHandle, const PWM_ShadowMode_e shadowMode)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //
    pwm->CMPCTL &= (~PWM_CMPCTL_SHDWBMODE_BITS);

    //
    // set the bits
    //
    pwm->CMPCTL |= (shadowMode << 6);

    return;
}

//
// PWM_setSwSync - 
//
void
PWM_setSwSync(PWM_Handle pwmHandle)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // set the bits
    //
    pwm->TBCTL |= 1 << 6;

    return;
}

//
// PWM_setSyncMode -
//
void
PWM_setSyncMode(PWM_Handle pwmHandle, const PWM_SyncMode_e syncMode)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    //
    // clear the bits
    //
    pwm->TBCTL &= (~PWM_TBCTL_SYNCOSEL_BITS);

    //
    // set the bits
    //
    pwm->TBCTL |= syncMode;

    return;
}

//
// PWM_setTripZoneDCEventSelect_DCAEVT1 -
// 
void
PWM_setTripZoneDCEventSelect_DCAEVT1(PWM_Handle pwmHandle, 
                                  const PWM_TripZoneDCEventSel_e tripZoneEvent)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // clear the bits
    //
    pwm->TZDCSEL &= (~PWM_TZDCSEL_DCAEVT1_BITS);

    //
    // set the bits
    //
    pwm->TZDCSEL |= tripZoneEvent << 0;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}  

//
// PWM_setTripZoneDCEventSelect_DCAEVT2  -
//
void
PWM_setTripZoneDCEventSelect_DCAEVT2(PWM_Handle pwmHandle, 
                                  const PWM_TripZoneDCEventSel_e tripZoneEvent)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // clear the bits
    //
    pwm->TZDCSEL &= (~PWM_TZDCSEL_DCAEVT2_BITS);

    //
    // set the bits
    //
    pwm->TZDCSEL |= tripZoneEvent << 3;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// PWM_setTripZoneDCEventSelect_DCBEVT1 -
//
void
PWM_setTripZoneDCEventSelect_DCBEVT1(PWM_Handle pwmHandle, 
                                  const PWM_TripZoneDCEventSel_e tripZoneEvent)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // clear the bits
    //
    pwm->TZDCSEL &= (~PWM_TZDCSEL_DCBEVT1_BITS);

    //
    // set the bits
    //
    pwm->TZDCSEL |= tripZoneEvent << 6;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// PWM_setTripZoneDCEventSelect_DCBEVT2 - 
//
void
PWM_setTripZoneDCEventSelect_DCBEVT2(PWM_Handle pwmHandle,
                                  const PWM_TripZoneDCEventSel_e tripZoneEvent)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // clear the bits
    //
    pwm->TZDCSEL &= (~PWM_TZDCSEL_DCBEVT2_BITS);

    //
    // set the bits
    //
    pwm->TZDCSEL |= tripZoneEvent << 9;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// PWM_setTripZoneState_DCAEVT1 -
//
void
PWM_setTripZoneState_DCAEVT1(PWM_Handle pwmHandle,
                             const PWM_TripZoneState_e tripZoneState)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // clear the bits
    //
    pwm->TZCTL &= (~PWM_TZCTL_DCAEVT1_BITS);

    //
    // set the bits
    //
    pwm->TZCTL |= tripZoneState << 4;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// PWM_setTripZoneState_DCAEVT2 - 
//
void
PWM_setTripZoneState_DCAEVT2(PWM_Handle pwmHandle,
                             const PWM_TripZoneState_e tripZoneState)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // clear the bits
    //
    pwm->TZCTL &= (~PWM_TZCTL_DCAEVT2_BITS);

    //
    // set the bits
    //
    pwm->TZCTL |= tripZoneState << 6;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// PWM_setTripZoneState_DCBEVT1 - 
//
void
PWM_setTripZoneState_DCBEVT1(PWM_Handle pwmHandle,
                             const PWM_TripZoneState_e tripZoneState)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // clear the bits
    //
    pwm->TZCTL &= (~PWM_TZCTL_DCBEVT1_BITS);

    //
    // set the bits
    //
    pwm->TZCTL |= tripZoneState << 8;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// PWM_setTripZoneState_DCBEVT2 - 
//
void
PWM_setTripZoneState_DCBEVT2(PWM_Handle pwmHandle,
                             const PWM_TripZoneState_e tripZoneState)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // clear the bits
    //
    pwm->TZCTL &= (~PWM_TZCTL_DCBEVT2_BITS);

    //
    // set the bits
    //
    pwm->TZCTL |= tripZoneState << 10;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// PWM_setTripZoneState_TZA -
//
void
PWM_setTripZoneState_TZA(PWM_Handle pwmHandle,
                         const PWM_TripZoneState_e tripZoneState)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // clear the bits
    //
    pwm->TZCTL &= (~PWM_TZCTL_TZA_BITS);

    //
    // set the bits
    //
    pwm->TZCTL |= tripZoneState << 0;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// PWM_setTripZoneState_TZB - 
//
void
PWM_setTripZoneState_TZB(PWM_Handle pwmHandle,
                         const PWM_TripZoneState_e tripZoneState)
{
    PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // clear the bits
    //
    pwm->TZCTL &= (~PWM_TZCTL_TZB_BITS);

    //
    // set the bits
    //
    pwm->TZCTL |= tripZoneState << 2;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// End of file
//

