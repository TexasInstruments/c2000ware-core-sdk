//#############################################################################
//
// FILE:   AFE031_Config.c
//
// TITLE:  AFE Setup Functions
//
//###########################################################################
//
// 
// $Copyright:
// Copyright (C) 2013-2024 Texas Instruments Incorporated - http://www.ti.com/
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
#include "afe031_config.h"
#include "F28x_Project.h"     // Device Headerfile and Examples Include File

/* RX Gain LUT */
UINT16 HAL_afe031_rxGainLut[8] = { 2, 3, 6, 7, 10, 11, 14, 15 };
/* TX Gain LUT */
UINT16 HAL_afe031_txGainLut[4] = { 0, 1, 2, 3 };

HAL_afe031_reg_t HAL_afe031_reg_s;

//
// FUNCTION NAME: HAL_afe031Init()
//
// DESCRIPTION:   AFE031 init function.
//
// Return Value:  None
//
// Input Parameters:
//
// Output Parameters:
// Functions Called:
//
//
void HAL_afe031Init(void)
{
    //
    // Configure GPIO pins for AFE
    //
    HAL_afe031_cfgGpio();

    HAL_spi_cfg();

    HAL_afe031_softReset();
    DELAY_US(2);

    HAL_afe031_biasEnable();
    DELAY_US(2);

    HAL_afe031_bandSelect(1); //0-A; 1-FCC;
    DELAY_US(2);

    HAL_afe031_clrAllInt();
    DELAY_US(2);

    HAL_afe031_cfgInt();
    DELAY_US(2);

    HAL_afe031_zcEnable();
    DELAY_US(2);

    HAL_afe031_writeTxGain(0);
    DELAY_US(2);
}

//
// FUNCTION NAME: HAL_afe031_cfgGpio()
//
// DESCRIPTION:   Configure GPIO for AFE031.
//
//                GPIO Profile for AFE031 Module:
//                  GPIO3 - SD (1-SD; 0-normal)
//                  GPIO123  - INT (1-INT; 0-no INT)
//                  GPIO2  - DAC (1-DAC; 0-normal)
// Return Value:  None
//
// Input Parameters:
//
// Output Parameters:
// Functions Called:
//
//
void HAL_afe031_cfgGpio(void)
{
    //SD PIN
    GPIO_SetupPinMux(3, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(3, GPIO_OUTPUT, GPIO_PUSHPULL);
    // SD=0
    GPIO_WritePin(3, 0);

    //DAC Pin Enable
    GPIO_SetupPinMux(2, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(2, GPIO_OUTPUT, GPIO_PUSHPULL);
    // DAC=0
    GPIO_WritePin(2, 0);

    // INT Pin
    GPIO_SetupPinMux(123, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(123, GPIO_OUTPUT, GPIO_PUSHPULL);
}

//
// FUNCTION NAME: HAL_afe031_writeRxGain()
//
// DESCRIPTION:   Write RX Gain.
//
// Return Value:  None
//
// Input Parameters:
//
// Output Parameters:
// Functions Called:
//
//
void HAL_afe031_writeRxGain(UINT16 gain)
{
    UINT16 gainSetting;

    gainSetting = HAL_afe031_rxGainLut[gain];
    HAL_afe031_reg_s.gain_sel.bits.RXG = gainSetting;
    HAL_afe031_regWrite(HAL_AFE031_GAINSEL_REG, HAL_afe031_reg_s.gain_sel.all);
}

//
// FUNCTION NAME: HAL_afe031_writeTxGain()
//
// DESCRIPTION:   Write TX Gain.
//
// Return Value:  None
//
// Input Parameters:
//
// Output Parameters:
// Functions Called:
//
//
void HAL_afe031_writeTxGain(UINT16 gain)
{
    UINT16 gainSetting;
    gainSetting = HAL_afe031_txGainLut[gain];
    HAL_afe031_reg_s.gain_sel.bits.TXG = gainSetting;
    HAL_afe031_regWrite(HAL_AFE031_GAINSEL_REG, HAL_afe031_reg_s.gain_sel.all);
}

//
// FUNCTION NAME: HAL_afe031_regWrite(addr, data)
//
// DESCRIPTION:   AFE031 Register Write
//
// Return Value:  None
//
// Input Parameters:
//
// Output Parameters:
// Functions Called:
//
//
void HAL_afe031_regWrite(UINT16 addr, UINT16 data)
{
    UINT16 cmd, data16;

    cmd = (HAL_AFE031_CMD_WR << HAL_AFE031_CMD_RW_SHIFT) | addr;
    data16 = (cmd << HAL_AFE031_CMD_SHIFT) | (data & HAL_AFE031_DATA_MASK);
    /* For F28035, use SPI; all others, use McBSPA */

    HAL_spi_xmt(data16);

    DELAY_US(1);
}

//
// FUNCTION NAME: HAL_afe031_regRead(addr)
//
// DESCRIPTION:   AFE031 Register Write
//
// Return Value:  None
//
// Input Parameters:
//
// Output Parameters:
// Functions Called:
//
//
UINT16 HAL_afe031_regRead(UINT16 addr)
{
    UINT16 cmd;

    cmd = (HAL_AFE031_CMD_RD << HAL_AFE031_CMD_RW_SHIFT) | addr;
    cmd = (cmd << HAL_AFE031_CMD_SHIFT);
    /* For F28035, use SPI; all others, use McBSPA */

    return HAL_spi_read(cmd);
}

//
// FUNCTION NAME: HAL_afe031_clrAllInt
//
// DESCRIPTION:   AFE031 Clear All Interrupts
//
// Return Value:  None
//
// Input Parameters:
//
// Output Parameters:
// Functions Called:
//
//
void HAL_afe031_clrAllInt(void)
{
    HAL_afe031_reg_s.control2.all = 0;
    HAL_afe031_regWrite(HAL_AFE031_CTRL2_REG, 0);
}

//
// FUNCTION NAME: HAL_afe031_clrInt
//
// DESCRIPTION:   AFE031 Clear All Interrupts
//
// Return Value:  None
//
// Input Parameters:
//
// Output Parameters:
// Functions Called:
//
//
void HAL_afe031_clrInt(UINT16 flag)
{
    HAL_afe031_reg_s.control2.all &= (~flag);
    HAL_afe031_regWrite(HAL_AFE031_CTRL2_REG, HAL_afe031_reg_s.control2.all);
}

//
// FUNCTION NAME: HAL_afe031_readIntFlag
//
// DESCRIPTION:   AFE031 Read Interrupt Flag
//
// Return Value:  None
//
// Input Parameters:
//
// Output Parameters:
// Functions Called:
//
//
UINT16 HAL_afe031_readIntFlag(void)
{
    return HAL_afe031_regRead(HAL_AFE031_RESET_REG);
}

//
// FUNCTION NAME: HAL_afe031_cfgInt
//
// DESCRIPTION:   AFE031 Configure Interrupts
//
// Return Value:  None
//
// Input Parameters:
//
// Output Parameters:
// Functions Called:
//
//
void HAL_afe031_cfgInt(void)
{
    //
    // For now only enable TFlag
    //
    HAL_afe031_reg_s.control2.bits.TFLAG_EN = 1;
    HAL_afe031_regWrite(HAL_AFE031_CTRL2_REG, HAL_afe031_reg_s.control2.all);
}

//
// FUNCTION NAME: HAL_afe031_cfgWdLen
//
// DESCRIPTION:   Configure word length
//
// Return Value:  None
//
// Input Parameters:
//
// Output Parameters:
// Functions Called:
//
//
void HAL_afe031_cfgWdLen(UINT16 len)
{
    HAL_spi_cfgWdLen(len);
}

//
// End of file
//
