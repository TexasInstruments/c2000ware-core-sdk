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
#include "F28x_Project.h"     // Device Header File and Examples Include File

//
// Platform-dependent GPIO
//
#define GPIO_INT    1
#define GPIO_DAC    2
#define GPIO_SD     3

/* RX Gain LUT */
UINT16 HAL_afe031_rxGainLut[] = { 0, 1, 2, 3, 6, 7, 10, 11, 14, 15 };
/* TX Gain LUT */
UINT16 HAL_afe031_txGainLut[] = { 0, 1, 2, 3 };

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
    HAL_afe031_cfgGpio();

    HAL_spi_cfg();

    HAL_afe031_softReset();
    DELAY_US(2);

    HAL_afe031_biasEnable();
    DELAY_US(2);

    HAL_afe031_bandSelect(1);
    DELAY_US(2);

    HAL_afe031_clrAllInt();
    DELAY_US(2);

    HAL_afe031_zcEnable();
    DELAY_US(2);

    HAL_afe031_writeGain(4, 1);
    DELAY_US(2);
}

//
// FUNCTION NAME: HAL_afe031_intAsserted()
//
// DESCRIPTION:   Return INT pin state.
//
// Return Value:  0 = Not Asserted, 1 = Asserted
//
// Input Parameters:
//
// Output Parameters:
// Functions Called:
//
//
UINT16 HAL_afe031_intAsserted(void)
{
    return GPIO_ReadPin(GPIO_INT) ? 0 : 1;
}

//
// FUNCTION NAME: HAL_afe031_shutdown(sd)
//
// DESCRIPTION:   AFE031 Shutdown Control
//
// Return Value:  None
//
// Input Parameters:
//
// Output Parameters:
// Functions Called:
//
//
void HAL_afe031_shutdown(UINT16 sd)
{
    GPIO_WritePin(GPIO_SD, sd);
}

//
// FUNCTION NAME: HAL_afe031_cfgGpio()
//
// DESCRIPTION:   Configure GPIO for AFE031.
//
//                GPIO Profile for AFE031 Module:
//                  GPIO3 - SD  (1-SD; 0-normal)
//                  GPIO2 - DAC (1-DAC; 0-normal)
//                  GPIO1 - INT (1-INT; 0-no INT)
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
    GPIO_SetupPinMux(GPIO_SD, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(GPIO_SD, GPIO_OUTPUT, GPIO_PUSHPULL);
    // SD=0
    GPIO_WritePin(GPIO_SD, 0);

    //DAC Pin Enable
    GPIO_SetupPinMux(GPIO_DAC, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(GPIO_DAC, GPIO_OUTPUT, GPIO_PUSHPULL);
    // DAC=0
    GPIO_WritePin(GPIO_DAC, 0);

    // INT Pin
    GPIO_SetupPinMux(GPIO_INT, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(GPIO_INT, GPIO_INPUT, GPIO_OPENDRAIN | GPIO_PULLUP);
    // NOTE: For RevE2 BoosterPack, jumper from J2.18 to J4.39
    GPIO_SetupPinMux(123, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(123, GPIO_INPUT, GPIO_OPENDRAIN | GPIO_PULLUP);
}

//
// FUNCTION NAME: HAL_afe031_writeGain()
//
// DESCRIPTION:   Write RX and TX Gain.
//
// Return Value:  None
//
// Input Parameters:
//
// Output Parameters:
// Functions Called:
//
//
void HAL_afe031_writeGain(UINT16 rxgain, UINT16 txgain)
{
    UINT16 rxGainSetting, txGainSetting;

    rxGainSetting = HAL_afe031_rxGainLut[rxgain];
    HAL_afe031_reg_s.gain_sel.bits.RXG = rxGainSetting;
    txGainSetting = HAL_afe031_txGainLut[txgain];
    HAL_afe031_reg_s.gain_sel.bits.TXG = txGainSetting;
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
// Return Value:  Register value
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
    // NOTE: Disable/clear interrupts before enabling
    HAL_afe031_clrAllInt();
    DELAY_US(2);
    HAL_afe031_regWrite(HAL_AFE031_RESET_REG, 0);
    DELAY_US(2);
    // Enable both TFlag and IFlag
    HAL_afe031_reg_s.control2.bits.IFLAG_EN = 1;
    HAL_afe031_reg_s.control2.bits.TFLAG_EN = 1;
    HAL_afe031_regWrite(HAL_AFE031_CTRL2_REG, HAL_afe031_reg_s.control2.all);
    DELAY_US(2);
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
