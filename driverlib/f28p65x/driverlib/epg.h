//###########################################################################
//
// FILE:   epg.h
//
// TITLE:  C28x EPG driver.
//
//###########################################################################
// $Copyright:
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com
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

#ifndef EPG_H
#define EPG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_epg.h"
#include "debug.h"
#include "cpu.h"

//*****************************************************************************
//
// Useful defines used within the driver functions. Not intended for use by
// application code.
//
//*****************************************************************************
#define EPG_GCTL0_EPGOUTSEL_S               8U
#define EPG_GCTL0_EPGOUTSEL_M               0xFF00U
#define EPG_GCTL3_EPGOUT_SIGOUTSEL_BIT_L    4U
#define EPG_GCTL2_EPGOUT_CLKOUTSEL_BIT_L    4U
#define EPG_GCTL1_SIGGEN_CLKSEL_BIT_L       4U
#define EPG_CLKDIV_REG_OFF                  12U
#define EPG_SIGGEN_REG_OFF                  32U
#define EPG_CLKDIV_CLKOFFSET_BIT_L          8U

//*****************************************************************************
//
//! Values that can be passed to EPG_selectGlobalOutput() as the \e gPinOutSel
//! parameter.
//
//*****************************************************************************
typedef enum
{
    EPG_OUT_SEL_SIG = 0x0U,    //!< Signal Generator mux output
    EPG_OUT_SEL_CLK = 0x1U     //!< Clock Generator mux output
} EPG_OutputSelect;

//*****************************************************************************
//
//! Values that can be passed to EPG_selectSignalOutput() as the
//! \e sigGenOutput parameter.
//
//*****************************************************************************
typedef enum
{
    EPG_SIGGEN0_DATATRANOUT0 = 0x0U, //!< Signal Generator 0 Data Transform out 0
    EPG_SIGGEN0_DATATRANOUT1 = 0x1U, //!< Signal Generator 0 Data Transform out 1
    EPG_SIGGEN0_DATATRANOUT2 = 0x2U, //!< Signal Generator 0 Data Transform out 2
    EPG_SIGGEN0_DATATRANOUT3 = 0x3U, //!< Signal Generator 0 Data Transform out 3
    EPG_SIGGEN0_DATATRANOUT4 = 0x4U, //!< Signal Generator 0 Data Transform out 4
    EPG_SIGGEN0_DATATRANOUT5 = 0x5U, //!< Signal Generator 0 Data Transform out 5
    EPG_SIGGEN0_DATATRANOUT6 = 0x6U, //!< Signal Generator 0 Data Transform out 6
    EPG_SIGGEN0_DATATRANOUT7 = 0x7U, //!< Signal Generator 0 Data Transform out 7
} EPG_SignalGenOut;

//*****************************************************************************
//
//! Values that can be passed to EPG_selectClkOutput()
//! as the \e clkGenOutput parameter.
//
//*****************************************************************************
typedef enum
{
    EPG_CLKGEN0_CLKOUT0_DCLK = 0x0U, //!< Clock Generator 0 Clk output 0 DCLK
    EPG_CLKGEN0_CLKOUT1_DCLK = 0x1U, //!< Clock Generator 0 Clk output 1 DCLK
    EPG_CLKGEN0_CLKOUT2_DCLK = 0x2U, //!< Clock Generator 0 Clk output 2 DCLK
    EPG_CLKGEN0_CLKOUT3_DCLK = 0x3U, //!< Clock Generator 0 Clk output 3 DCLK
    EPG_CLKGEN1_CLKOUT0_DCLK = 0x4U, //!< Clock Generator 1 Clk output 0 DCLK
    EPG_CLKGEN1_CLKOUT1_DCLK = 0x5U, //!< Clock Generator 1 Clk output 1 DCLK
    EPG_CLKGEN1_CLKOUT2_DCLK = 0x6U, //!< Clock Generator 1 Clk output 2 DCLK
    EPG_CLKGEN1_CLKOUT3_DCLK = 0x7U, //!< Clock Generator 1 Clk output 3 DCLK
} EPG_ClockGenOut;

//*****************************************************************************
//
//! Values that can be passed to EPG_selectSigGenClkSource()
//! as the \e clkGenOutput parameter.
//
//*****************************************************************************
typedef enum
{
    EPG_CLKGEN0_CLKOUT0_GCLK = 0x0U, //!< Clock Generator 0 Clk output 0 GCLK
    EPG_CLKGEN0_CLKOUT1_GCLK = 0x1U, //!< Clock Generator 0 Clk output 1 GCLK
    EPG_CLKGEN0_CLKOUT2_GCLK = 0x2U, //!< Clock Generator 0 Clk output 2 GCLK
    EPG_CLKGEN0_CLKOUT3_GCLK = 0x3U, //!< Clock Generator 0 Clk output 3 GCLK
    EPG_CLKGEN1_CLKOUT0_GCLK = 0x4U, //!< Clock Generator 1 Clk output 0 GCLK
    EPG_CLKGEN1_CLKOUT1_GCLK = 0x5U, //!< Clock Generator 1 Clk output 1 GCLK
    EPG_CLKGEN1_CLKOUT2_GCLK = 0x6U, //!< Clock Generator 1 Clk output 2 GCLK
    EPG_CLKGEN1_CLKOUT3_GCLK = 0x7U, //!< Clock Generator 1 Clk output 3 GCLK
} EPG_ClockGenGclkOut;

//*****************************************************************************
//
//! Values that can be passed to EPG_setClkGenStopEdge(),
//! as the \e stopEdge parameter.
//
//*****************************************************************************
typedef enum
{
    EPG_CLK_STOP_EDGE_CLKOUT0 = 0x000U,    //!< Stop on Clk output 0
    EPG_CLK_STOP_EDGE_CLKOUT1 = 0x010U,    //!< Stop on Clk output 1
    EPG_CLK_STOP_EDGE_CLKOUT2 = 0x100U,    //!< Stop on Clk output 2
    EPG_CLK_STOP_EDGE_CLKOUT3 = 0x110U,    //!< Stop on Clk output 3
} EPG_ClockStopEdge;

//*****************************************************************************
//
//! Values that can be passed to EPG_setSignalGenMode(),
//! as the \e sigGenMode parameter.
//
//*****************************************************************************
typedef enum
{
    EPG_SIGGEN_MODE_BIT_BANG            = 0x0U,    //!< BIT BANG MODE
    EPG_SIGGEN_MODE_SHIFT_RIGHT_ONCE    = 0x1U,    //!< SHIFT RIGHT ONCE MODE
    EPG_SIGGEN_MODE_ROTATE_RIGHT_ONCE   = 0x2U,    //!< ROTATE RIGHT ONCE MODE
    EPG_SIGGEN_MODE_ROTATE_RIGHT_REPEAT = 0x3U,    //!< ROTATE RIGHT REPEAT MODE
    EPG_SIGGEN_MODE_SHIFT_LEFT_ONCE     = 0x4U,    //!< SHIFT LEFT ONCE MODE
    EPG_SIGGEN_MODE_ROTATE_LEFT_ONCE    = 0x5U,    //!< ROTATE LEFT ONCE MODE
    EPG_SIGGEN_MODE_ROTATE_LEFT_REPEAT  = 0x6U,    //!< ROTATE LEFT REPEAT
    EPG_SIGGEN_MODE_SHIFT_RIGHT_REPEAT  = 0x7U,    //!< SHIFT RIGHT REPEAT MODE
    EPG_SIGGEN_MODE_SHIFT_LEFT_REPEAT   = 0x8U,    //!< SHIGT LEFT REPEAT MODE
} EPG_SignalGenMode;

//*****************************************************************************
//
//! Values that can be passed to EPG_setData0In(),
//! as the \e data0Input parameter.
//
//*****************************************************************************
typedef enum
{
    EPG_SIGGEN_DATA0_DATA_NEXT0 = 0x0U,    //!< DATA TRANSFORM NEXT[0]
    EPG_SIGGEN_DATA0_EPGIN0     = 0x1U,    //!< EPG Input 0
    EPG_SIGGEN_DATA0_EPGIN1     = 0x2U,    //!< EPG Input 1
    EPG_SIGGEN_DATA0_EPGIN2     = 0x3U,    //!< EPG Input 2
    EPG_SIGGEN_DATA0_EPGIN3     = 0x4U,    //!< EPG Input 3
    EPG_SIGGEN_DATA0_EPGIN4     = 0x5U,    //!< EPG Input 4
    EPG_SIGGEN_DATA0_EPGIN5     = 0x6U,    //!< EPG Input 5
    EPG_SIGGEN_DATA0_EPGIN6     = 0x7U,    //!< EPG Input 6
    EPG_SIGGEN_DATA0_EPGIN7     = 0x8U,    //!< EPG Input 7
} EPG_SignalGenData0In;

//*****************************************************************************
//
//! Values that can be passed to EPG_setData63In(),
//! as the \e data63Input parameter.
//
//*****************************************************************************
typedef enum
{
    EPG_SIGGEN_DATA63_DATA_NEXT63   = 0x0U,    //!< DATA TRANSFORM NEXT[63]
    EPG_SIGGEN_DATA63_EPGIN0        = 0x1U,    //!< EPG Input 0
    EPG_SIGGEN_DATA63_EPGIN1        = 0x2U,    //!< EPG Input 1
    EPG_SIGGEN_DATA63_EPGIN2        = 0x3U,    //!< EPG Input 2
    EPG_SIGGEN_DATA63_EPGIN3        = 0x4U,    //!< EPG Input 3
    EPG_SIGGEN_DATA63_EPGIN4        = 0x5U,    //!< EPG Input 4
    EPG_SIGGEN_DATA63_EPGIN5        = 0x6U,    //!< EPG Input 5
    EPG_SIGGEN_DATA63_EPGIN6        = 0x7U,    //!< EPG Input 6
    EPG_SIGGEN_DATA63_EPGIN7        = 0x8U,    //!< EPG Input 7
} EPG_SignalGenData63In;

//*****************************************************************************
//
//! Values that can be passed to EPG_selectEPGOutput(), EPG_selectClkOutput,
//! EPG_selectSignalOutput as the \e gPinNum parameter.
//
//*****************************************************************************
typedef enum
{
    EPG_OUT0 = 0x0U,    //!< EPG Output 0
    EPG_OUT1 = 0x1U,    //!< EPG Output 1
    EPG_OUT2 = 0x2U,    //!< EPG Output 2
    EPG_OUT3 = 0x3U,    //!< EPG Output 3
    EPG_OUT4 = 0x4U,    //!< EPG Output 4
    EPG_OUT5 = 0x5U,    //!< EPG Output 5
    EPG_OUT6 = 0x6U,    //!< EPG Output 6
} EPG_OUT;

//*****************************************************************************
//
//! Values that can be used for \e sigGenNum parameter.
//
//*****************************************************************************
typedef enum
{
    EPG_SIGGEN0 = 0x0U,    //!< Signal Generator 0
    EPG_SIGGEN1 = 0x1U,    //!< Signal Generator 1
} EPG_SIGGEN;

//*****************************************************************************
//
//! Values that can be used for \e clkGenNum parameter.
//
//*****************************************************************************
typedef enum
{
    EPG_CLKGEN0 = 0x0U,    //!< Clock Generator 0
    EPG_CLKGEN1 = 0x1U,    //<! Clock Generator 1
} EPG_CLKGEN;

//*****************************************************************************
//
//! Values that can be passed to EPG_selectEPGDataOut(),
//! as the \e dataIn parameter.
//
//*****************************************************************************
typedef enum{
    EPG_DATAIN_CANARX = 0,    //!< CANA Receive input (RX)
    EPG_DATAIN_MCANARX = 1,   //!< MCANA Receive input (RX)
    EPG_DATAIN_LINARX = 2,    //!< LINA Receive input (RX)
    EPG_DATAIN_LINBRX = 3,    //!< LINB Receive input (RX)
    EPG_DATAIN_FSIAD0RX = 4,  //!< FSIA D0 Receive Input (RX)
    EPG_DATAIN_FSIAD1RX = 5,  //!< FSIA D1 Receive Input (RX)
    EPG_DATAIN_FSIBD0RX = 6,  //!< FSIB D0 Receive Input (RX)
    EPG_DATAIN_FSIBD1RX = 7,  //!< FSIB D1 Receive Input (RX)
    EPG_DATAIN_FSIARX_CLK = 8,//!< FSIA Receive Clock Input Signal
    EPG_DATAIN_SPIA_CLK = 9,  //!< SPIA Clock Signal
    EPG_DATAIN_SPIA_PICO = 10,//!< SPIA Peripheral in Controller out Signal
    EPG_DATAIN_SPIA_POCI = 11,//!< SPIA Peripheral out Controller in Signal
    EPG_DATAIN_SPIA_PTE = 12, //!< SPIA Peripheral Transmit Enable Signal
    EPG_DATAIN_SPIB_CLK = 13, //!< SPIB Clock Signal
    EPG_DATAIN_SPIB_PICO = 14,//!< SPIB Peripheral in COntroller out Signal
    EPG_DATAIN_SPIB_POCI = 15,//!< SPIB Peripheral out Controller in Signal
    EPG_DATAIN_SPIB_PTE = 16, //!< SPIB Peripheral Transmit Enable Signal
    EPG_DATAIN_I2CA_SDA = 17,//!< I2CA Serial Data Line
    EPG_DATAIN_I2CA_SCL = 18,//!< I2CA Serial Clock Line
    EPG_DATAIN_I2CB_SDA = 19,//!< I2CB Serial Data Line
    EPG_DATAIN_I2CB_SCL = 20,//!< I2CB Serial Clock Line
    EPG_DATAIN_SDC1 = 21,     //!< SDFM C1 Input
    EPG_DATAIN_SDC2 = 22,     //!< SDFM C2 Input
    EPG_DATAIN_SDC3 = 23,     //!< SDFM C3 Input
    EPG_DATAIN_SDC4 = 24,     //!< SDFM C4 Input
    EPG_DATAIN_SDC5 = 25,     //!< SDFM C5 Input
    EPG_DATAIN_SDC6 = 26,     //!< SDFM C6 Input
    EPG_DATAIN_SDC7 = 27,     //!< SDFM C7 Input
    EPG_DATAIN_SDC8 = 28,     //!< SDFM C8 Input
    EPG_DATAIN_SDC9 = 29,     //!< SDFM C9 Input
    EPG_DATAIN_SDC10 = 30,    //!< SDFM C10 Input
    EPG_DATAIN_SDC11 = 31,    //!< SDFM C11 Input
    EPG_DATAIN_SDC12 = 32,    //!< SDFM C12 Input
    EPG_DATAIN_SDC13 = 33,    //!< SDFM C13 Input
    EPG_DATAIN_SDC14 = 34,    //!< SDFM C14 Input
    EPG_DATAIN_SDC15 = 35,    //!< SDFM C15 Input
    EPG_DATAIN_SDC16 = 36,    //!< SDFM C16 Input
    EPG_DATAIN_SCIARX = 37,   //!< SCIA Receive input (RX)
    EPG_DATAIN_SCIBRX = 38,   //!< SCIB Receive input (RX)
    EPG_DATAIN_EQEP1A = 39,   //!< EQEP1 Signal A
    EPG_DATAIN_EQEP1B = 40,   //!< EQEP1 Signal B
    EPG_DATAIN_EQEP1I = 41,   //!< EQEP1 Index signal
    EPG_DATAIN_EQEP1S = 42,   //!< EQEP1 Strobe input
    EPG_DATAIN_EQEP2A = 43,   //!< EQEP2 Signal A
    EPG_DATAIN_EQEP2B = 44,   //!< EQEP2 Signal B
    EPG_DATAIN_EQEP2I = 45,   //!< EQEP1 Index signal
    EPG_DATAIN_EQEP2S = 46,   //!< EQEP1 Strobe input
    EPG_DATAIN_FSICRX_CLK = 47,//!< FSIC Receive Clock Input Signal
    EPG_DATAIN_FSICD0RX = 48,  //!< FSIC D0 Receive Input (RX)
    EPG_DATAIN_FSICD1RX = 49,  //!< FSIC D1 Receive Input (RX)
    EPG_DATAIN_FSIBRX_CLK = 50,//!< FSIB Receive Clock Input Signal
    EPG_DATAIN_UART0RX = 51,  //!< UART0 Receive input (RX)
    EPG_DATAIN_UART1RX = 52,  //!< UART1 Receive input (RX)
    EPG_DATAIN_ECAP1 = 53,    //!< ECAP 1 Input
    EPG_DATAIN_ECAP2 = 54,    //!< ECAP 2 Input
    EPG_DATAIN_ECAP3 = 55,    //!< ECAP 3 Input
    EPG_DATAIN_ECAP4 = 56,    //!< ECAP 4 Input
    EPG_DATAIN_ECAP5 = 57,    //!< ECAP 5 Input
    EPG_DATAIN_ECAP6 = 58,    //!< ECAP 6 Input
    EPG_DATAIN_ECAP7 = 59,    //!< ECAP 7 Input
    EPG_DATAIN_MCANBRX = 63,  //!< MCANB Receive input (RX)
} EPG_DataIn;

//*****************************************************************************
//
//! Interrupt Flags that can be passed to EPG_enableInterruptFlag(),
//! EPG_diableInterruptFlag, EPG_forceInterruptFlag, EPG_clearInterruptFlag
//! as \e intFlags parameter.
//
//*****************************************************************************
#define EPG_INT_GLOBAL_INT       0x1U    //!< Global Interrupt Flag
#define EPG_INT_SIGGEN0_DONE     0x2U    //!< Signal Generator 0 Operation Done
#define EPG_INT_SIGGEN0_FILL     0x4U    //!< Signal Generator 0 Data Fill

//*****************************************************************************
//
//! Register Flags that can be passed to EPG_releaseLockReg,
//! EPG_LockReg, EPG_commitRegLock as \e regFlags parameter.
//
//*****************************************************************************
#define EPG_LOCK_REG_GCTL0           0x1U    //!< GCTL0 Register
#define EPG_LOCK_REG_GCTL1           0x2U    //!< GCTL1 Register
#define EPG_LOCK_REG_GCTL2           0x4U    //!< GCTL2 Register
#define EPG_LOCK_REG_GCTL3           0x8U    //!< GCTL3 Register
#define EPG_LOCK_REG_CLKDIV0_CTL0    0x10U   //!< CLK divider 0 CTL0 Register
#define EPG_LOCK_REG_CLKDIV1_CTL0    0x20U   //!< CLK divider 1 CTL0 Register
#define EPG_LOCK_REG_SIGGEN0_CTL0    0x40U   //!< Signal gen 0 CTL0 Register
#define EPG_LOCK_REG_SIGGEN0_CTL1    0x80U   //!< Signal gen 0 CTL1 Register

//*****************************************************************************
//
//! Register Flags that can be passed to EPG_releaseLockMXSelReg,
//! EPG_lockMXSelReg, EPG_commitMXSelRegLock as \e regFlags parameter.
//
//*****************************************************************************
#define EPG_MX_SEL_LOCK_REG_MXSEL0   0x1U    //!< Mux Select 0 Register

//*****************************************************************************
//
//! Values that can be passed to EPG_selectEPGDataOut(),
//! as the \e dataOutSel parameter.
//
//*****************************************************************************
typedef enum
{
   EPG_DATAOUT_DATAIN  = 0x0U,    //!< Input Data
   EPG_DATAOUT_EPGOUT  = 0x1U,    //!< EPG output
} EPG_DataOutSel;

//*****************************************************************************
//
//! \internal
//! Check a EPG base address.
//!
//! \param base is the base address of the EPG.
//!
//! This function determines if a EPG base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool
EPG_isBaseValid(uint32_t base)
{
    return(
           (base == EPG1_BASE)
          );
}
#endif

//*****************************************************************************
//
//! \internal
//! Check a EPGMUX base address.
//!
//! \param muxbase is the base address of the EPG MUX.
//!
//! This function determines if EPGMUX base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool
EPG_isMUXBaseValid(uint32_t muxbase)
{
    return(
           (muxbase == EPG1MUX_BASE)
          );
}
#endif

//*****************************************************************************
//
//! Enable EPG and starts signal and clock generator
//!
//! \param base is the base address of the EPG module.
//!
//! This function enables the EPG module and starts signal and clock generator.
//!
//! \return None.
//
//*****************************************************************************
static inline void
EPG_enableGlobal(uint32_t base)
{
    ASSERT(EPG_isBaseValid(base));

    HWREG(base + EPG_O_GCTL0) |= EPG_GCTL0_EN;
}

//*****************************************************************************
//
//! Disable EPG and stops signal and clock generator
//!
//! \param base is the base address of the EPG module.
//!
//! This function disables the EPG module and stops signal and clock generator.
//!
//! \return None.
//
//*****************************************************************************
static inline void
EPG_disableGlobal(uint32_t base)
{
    ASSERT(EPG_isBaseValid(base));

    HWREG(base + EPG_O_GCTL0) &= ~(uint32_t)EPG_GCTL0_EN;
}

//*****************************************************************************
//
//! Select the EPG output source
//!
//! \param base is the base address of the EPG module.
//! \param gPinNum is the global EPG Output number.
//! \param gPinOutSel is the mux output of the \e gPinNum.
//!
//! This function selects the global EPG output source to be clock or signal.
//! This output can then be routed to any GPIO through xbar, mux sel.
//!
//! The \e gPinNum can take any of EPG_OUTX. The \e gPinOutSel can
//! take any of the EPG_OUT_SEL_CLK, EPG_OUT_SEL_SIG values.
//!
//! \return None.
//
//*****************************************************************************
static inline void
EPG_selectEPGOutput(uint32_t base, EPG_OUT gPinNum,
                       EPG_OutputSelect gPinOutSel)
{
    uint32_t regValue, bitFieldLoc, bitFieldVal;

    ASSERT(EPG_isBaseValid(base));
    ASSERT((uint16_t)gPinNum <= 7U);

    bitFieldLoc = 1UL << ((uint16_t)gPinNum + EPG_GCTL0_EPGOUTSEL_S);
    bitFieldVal = (uint32_t)gPinOutSel << ((uint16_t)gPinNum +
                                           EPG_GCTL0_EPGOUTSEL_S);

    regValue = (HWREG(base + EPG_O_GCTL0) & (~bitFieldLoc));
    regValue |= bitFieldVal;

    HWREG((base + EPG_O_GCTL0)) = regValue;
}

//*****************************************************************************
//
//! Select the individual EPG pin signal data output
//!
//! \param base is the base address of the EPG module.
//! \param gPinNum is the global EPG Output number.
//! \param sigGenOutput is the mux output of the \e gPinNum signal generators
//!        data output.
//!
//! This function selects the individual EPG pin's signal generator data output.
//! This output can then be routed to EPG global output by selecting signal
//! generator as source for that pin.
//!
//! The \e gPinNum can take any of EPG_OUTX. The \e sigGenOutput
//! can take any of the EPG_SIG_GEN0_DATATRANX values where X is a number
//! from 0 to 7 specifying which data ouput of sig gen to be used.
//!
//! \return None.
//
//*****************************************************************************
static inline void
EPG_selectSignalOutput(uint32_t base, EPG_OUT gPinNum,
                       EPG_SignalGenOut sigGenOutput)
{
    uint32_t regValue, bitFieldLoc, bitFieldVal;

    ASSERT(EPG_isBaseValid(base));
    ASSERT((uint16_t)gPinNum <= 7U);

    bitFieldLoc = (uint32_t)EPG_GCTL3_EPGOUT0_SIGOUTSEL_M <<
                  ((uint32_t)gPinNum * EPG_GCTL3_EPGOUT_SIGOUTSEL_BIT_L);

    bitFieldVal = (uint32_t)sigGenOutput <<
                  ((uint32_t)gPinNum * EPG_GCTL3_EPGOUT_SIGOUTSEL_BIT_L);

    regValue = HWREG(base + EPG_O_GCTL3) & ~bitFieldLoc;
    regValue |= bitFieldVal;

    HWREG(base + EPG_O_GCTL3) = regValue;
}

//*****************************************************************************
//
//! Select the individual EPG pin clock data output
//!
//! \param base is the base address of the EPG module.
//! \param gPinNum is the global EPG Output number.
//! \param clkGenOutput is the mux output of the \e gPinNum clock generator's
//!        data output.
//!
//! This function selects the individual EPG pin's clock generator data output.
//! This output can then be routed to EPG global output by selecting clock
//! generator as source for that pin.
//!
//! The \e gPinNum can take any of EPG_OUTX.
//! The \e clkGenOutput can take any of the EPG_CLK_GENY_CLKOUTX_DCLK values
//! where X is a number from 0 to 3 specifying which data ouput of clock gen
//! and Y can be 0 or 1 specifying which clock generator to be used to be used
//!
//! \return None.
//
//*****************************************************************************
static inline void
EPG_selectClkOutput(uint32_t base, EPG_OUT gPinNum,
                    EPG_ClockGenOut clkGenOutput)
{
    uint32_t regValue, bitFieldLoc, bitFieldVal;

    ASSERT(EPG_isBaseValid(base));
    ASSERT((uint16_t)gPinNum <= 7U);

    bitFieldLoc = (uint32_t)EPG_GCTL2_EPGOUT0_CLKOUTSEL_M <<
                  ((uint32_t)gPinNum * EPG_GCTL2_EPGOUT_CLKOUTSEL_BIT_L);

    bitFieldVal = (uint32_t)clkGenOutput <<
                  ((uint32_t)gPinNum * EPG_GCTL2_EPGOUT_CLKOUTSEL_BIT_L);

    regValue = HWREG(base + EPG_O_GCTL2) & ~bitFieldLoc;
    regValue |= bitFieldVal;

    HWREG(base + EPG_O_GCTL2) = regValue;
}

//*****************************************************************************
//
//! Select the signal generator's clock source
//!
//! \param base is the base address of the EPG module.
//! \param sigGenNum is the Signal generator number whose clk source is being
//!        configured based on the availability.
//! \param clkGenOutput is the mux output of the clock generator's data
//!        output to be selected as source.
//!
//! This function selects the signal generator's clock source.
//! This clock source is used to generate the periodic or aperiodic signals by
//! the signal generator.
//!
//! The \e sigGenNum can take value of 0.
//! The \e clkGenOutput can take any of the EPG_CLK_GENY_CLKOUTX_DCLK values
//! where X is a number from 0 to 3 specifying which data ouput of clock gen
//! to be used and Y can be 0 or 1 specifying which clock generator to be used
//!
//! \return None.
//
//*****************************************************************************
static inline void
EPG_selectSigGenClkSource(uint32_t base, EPG_SIGGEN sigGenNum,
                          EPG_ClockGenGclkOut clkGenOutput)
{
    uint32_t regValue, bitFieldLoc, bitFieldVal;

    ASSERT(EPG_isBaseValid(base));
    ASSERT((uint16_t)sigGenNum <= 0U);

    bitFieldLoc = (uint32_t)EPG_GCTL1_SIGGEN0_CLKSEL_M <<
                  ((uint32_t)sigGenNum * EPG_GCTL1_SIGGEN_CLKSEL_BIT_L);

    bitFieldVal = (uint32_t)clkGenOutput <<
                  ((uint32_t)sigGenNum * EPG_GCTL1_SIGGEN_CLKSEL_BIT_L);

    regValue = HWREG(base + EPG_O_GCTL1) & ~bitFieldLoc;
    regValue |= bitFieldVal;

    HWREG(base + EPG_O_GCTL1) |= regValue;
}

//*****************************************************************************
//
//! Set the clock generator period
//!
//! \param base is the base address of the EPG module.
//! \param clkGenNum is the clock generator number whose period is being set.
//! \param periodValue is the period value in number of system clk cycles
//!
//! This function Sets the clock generator's period
//! Clock divider counter counts up to \e periodValue and snaps back to 0.
//!
//! The \e clkGenNum can take values from 0 to 1 inclusive.
//! The \e periodValue can take a maximum value of EPG_CLKDIV0_CTL0_PRD_M.
//!
//! \return None.
//
//*****************************************************************************
static inline void
EPG_setClkGenPeriod(uint32_t base, EPG_CLKGEN clkGenNum,
                         uint32_t periodValue)
{
    uint32_t regValue, regLoc;

    ASSERT(EPG_isBaseValid(base));
    ASSERT((uint16_t)clkGenNum <= 1U);
    ASSERT(periodValue <= EPG_CLKDIV0_CTL0_PRD_M);

    regLoc = (uint32_t)EPG_O_CLKDIV0_CTL0 + ((uint32_t)clkGenNum *
                                             EPG_CLKDIV_REG_OFF);

    regValue = HWREG(base + regLoc) & ~(uint32_t)EPG_CLKDIV0_CTL0_PRD_M;
    regValue |= periodValue;

    HWREG(base + regLoc) = regValue;
}

//*****************************************************************************
//
//! Set the clock generator stop value
//!
//! \param base is the base address of the EPG module.
//! \param clkGenNum is the clock generator number which is being configured.
//! \param stopEdge is the Edge signal at which clock stops.
//!
//! This function Sets the clock generator's stop value
//! This Determines on which of the CLKOUTs edge clock generation is stopped
//! following a clear of SIGGEN1_CTL0.EN.
//!
//! The \e clkGenNum can take values from 0 to 1 inclusive.
//! The \e stopEdge can take any of EPG_CLK_STOP_EDGE_CLKOUTX value where X
//! signifies the clock out number varying from 0 to 3 inclusive
//!
//! \return None.
//
//*****************************************************************************
static inline void
EPG_setClkGenStopEdge(uint32_t base, EPG_CLKGEN clkGenNum,
                      EPG_ClockStopEdge stopEdge)
{
    uint32_t regValue, regLoc;

    ASSERT(EPG_isBaseValid(base));
    ASSERT((uint16_t)clkGenNum <= 1U);

    regLoc = (uint32_t)EPG_O_CLKDIV0_CTL0 + ((uint32_t)clkGenNum *
                                             EPG_CLKDIV_REG_OFF);

    regValue = HWREG(base + regLoc) & ~(uint32_t)EPG_CLKDIV0_CTL0_CLKSTOP_M;
    regValue |= ((uint32_t)stopEdge << EPG_CLKDIV0_CTL0_CLKSTOP_S);

    HWREG(base + regLoc) = regValue;
}

//*****************************************************************************
//
//! Set the clock generator clock offset
//!
//! \param base is the base address of the EPG module.
//! \param clkGenNum is the clock generator number which is being configured.
//! \param clkGenOutputNum is the output number of particular clock generator
//!        whose offset is being set.
//! \param offsetValue is the offset value in number of system clk cycles
//!
//! This function Sets the clock generator output's offset.
//! This Determines number of source clock cycles by which the divided clock
//! output is delayed.
//!
//! The \e clkGenNum can take values from 0 to 1 inclusive.
//! The \e clkGenOutputNum can take values from 0 to 3 inclusive.
//! The \e offsetValue can take a maximum value of
//! EPG_CLKDIV0_CLKOFFSET_CLK0OFFSET_M.
//!
//! \return None.
//
//*****************************************************************************
static inline void
EPG_setClkGenOffset(uint32_t base, EPG_CLKGEN clkGenNum,
                    uint32_t clkGenOutputNum, uint32_t offsetValue)
{
    uint32_t regValue, regLoc, bitFieldLoc, bitFieldVal;

    ASSERT(EPG_isBaseValid(base));
    ASSERT((uint16_t)clkGenNum <= 1U);
    ASSERT(clkGenOutputNum <= 3U);
    ASSERT(offsetValue <= EPG_CLKDIV0_CLKOFFSET_CLK0OFFSET_M);

    bitFieldLoc = (uint32_t)EPG_CLKDIV0_CLKOFFSET_CLK0OFFSET_M <<
                  (clkGenOutputNum * EPG_CLKDIV_CLKOFFSET_BIT_L);

    bitFieldVal = offsetValue << (clkGenOutputNum * EPG_CLKDIV_CLKOFFSET_BIT_L);

    regLoc = (uint32_t)EPG_O_CLKDIV0_CLKOFFSET + ((uint32_t)clkGenNum  *
                                                  EPG_CLKDIV_REG_OFF);

    regValue = HWREG(base + regLoc) & ~bitFieldLoc;
    regValue |= bitFieldVal;

    HWREG(base + regLoc) = regValue;
}

//*****************************************************************************
//
//! Enable EPG signal generator
//!
//! \param base is the base address of the EPG module.
//! \param sigGenNum is the Signal generator number which is enabled.
//!
//! This function enables the Signal generator after which the signal generator
//! functions as per the mode definition.
//!
//! The \e sigGenNum can take value of 0.
//! \return None.
//
//*****************************************************************************
static inline void
EPG_enableSignalGen(uint32_t base, EPG_SIGGEN sigGenNum)
{
    ASSERT(EPG_isBaseValid(base));
    ASSERT((uint16_t)sigGenNum <= 0U);

    if(sigGenNum == EPG_SIGGEN0)
    {
        HWREG(base + EPG_O_GCTL0) |= EPG_GCTL0_SIGGEN0_EN;
    }
    else if(sigGenNum == EPG_SIGGEN1)
    {
        HWREG(base + EPG_O_GCTL0) |= EPG_GCTL0_SIGGEN1_EN;
    }
    else
    {
        //
        // For correct inputs, this function is not expected to
        // execute.
        //
        ESTOP0;
    }
}

//*****************************************************************************
//
//! Disable EPG signal generator
//!
//! \param base is the base address of the EPG module.
//! \param sigGenNum is the Signal generator number which is disabled.
//!
//! This function Disables the Signal generator and stops its operation.
//!
//! The \e sigGenNum can take value of 0.
//! \return None.
//
//*****************************************************************************
static inline void
EPG_disableSignalGen(uint32_t base, EPG_SIGGEN sigGenNum)
{
    ASSERT(EPG_isBaseValid(base));
    ASSERT((uint16_t)sigGenNum <= 0U);

    if(sigGenNum == EPG_SIGGEN0)
    {
        HWREG(base + EPG_O_GCTL0) &= ~(uint32_t)EPG_GCTL0_SIGGEN0_EN;
    }
    else if(sigGenNum == EPG_SIGGEN1)
    {
        HWREG(base + EPG_O_GCTL0) &= ~(uint32_t)EPG_GCTL0_SIGGEN1_EN;
    }
    else
    {
        //
        // For correct inputs, this function is not expected to
        // execute.
        //
        ESTOP0;
    }
    
}

//*****************************************************************************
//
//! Set EPG signal generator Mode
//!
//! \param base is the base address of the EPG module.
//! \param sigGenNum is the Signal generator number which is beign configured.
//! \param sigGenMode is the Signal generator mode being set.
//!
//! This function Sets the EPG signal generator's Mode.
//! This mode effects the operation of the signal generator on the DATA input.
//!
//! The \e sigGenNum can take value of 0.
//! The \e sigGenMode can take any of the EPG_SIGGEN_MODE_BIT_BANG,
//! EPG_SIGGEN_MODE_SHIFT_RIGHT_ONCE, EPG_SIGGEN_MODE_ROTATE_RIGHT_ONCE,
//! EPG_SIGGEN_MODE_ROTATE_RIGHT_REPEAT, EPG_SIGGEN_MODE_SHIFT_LEFT_ONCE,
//! EPG_SIGGEN_MODE_ROTATE_LEFT_ONCE, EPG_SIGGEN_MODE_ROTATE_LEFT_REPEAT,
//! EPG_SIGGEN_MODE_SHIFT_RIGHT_REPEAT, EPG_SIGGEN_MODE_SHIFT_LEFT_REPEAT
//! values.
//!
//! \return None.
//
//*****************************************************************************
static inline void
EPG_setSignalGenMode(uint32_t base, EPG_SIGGEN sigGenNum,
                     EPG_SignalGenMode sigGenMode)
{
    uint32_t regValue, regLoc;

    ASSERT(EPG_isBaseValid(base));
    ASSERT((uint16_t)sigGenNum <= 0U);

    regLoc = (uint32_t)EPG_O_SIGGEN0_CTL0 + ((uint32_t)sigGenNum *
                                             EPG_SIGGEN_REG_OFF);

    regValue = HWREG(base + regLoc) & ~(uint32_t)EPG_SIGGEN0_CTL0_MODE_M;
    regValue |= (uint32_t)sigGenMode << EPG_SIGGEN0_CTL0_MODE_S;

    HWREG(base + regLoc) = regValue;
}

//*****************************************************************************
//
//! Perform bit reversal on input of signal generator
//!
//! \param base is the base address of the EPG module.
//! \param sigGenNum is the Signal generator number which is beign configured.
//!
//! This function set's signal generator to Perform bit reversal on input.
//! This results in bit reversal on data input of data transform block.
//!
//! The \e sigGenNum can take value of 0.
//!
//! \return None.
//
//*****************************************************************************
static inline void
EPG_enableBitRevOnDataIn(uint32_t base, EPG_SIGGEN sigGenNum)
{
    uint32_t regLoc;

    ASSERT(EPG_isBaseValid(base));
    ASSERT((uint16_t)sigGenNum <= 0U);

    regLoc = (uint32_t)EPG_O_SIGGEN0_CTL0 + ((uint32_t)sigGenNum *
                                             EPG_SIGGEN_REG_OFF);

    HWREG(base + regLoc) |= EPG_SIGGEN0_CTL0_BRIN;
}

//*****************************************************************************
//
//! Disable bit reversal on input of signal generator
//!
//! \param base is the base address of the EPG module.
//! \param sigGenNum is the Signal generator number which is beign configured.
//!
//! This function set's signal generator to disable bit reversal on input.
//! This results in no bit reversal on data input of data transform block.
//!
//! The \e sigGenNum can take value of 0.
//!
//! \return None.
//
//*****************************************************************************
static inline void
EPG_disableBitRevOnDataIn(uint32_t base, EPG_SIGGEN sigGenNum)
{
    uint32_t regLoc;

    ASSERT(EPG_isBaseValid(base));
    ASSERT((uint16_t)sigGenNum <= 0U);

    regLoc = (uint32_t)EPG_O_SIGGEN0_CTL0 + ((uint32_t)sigGenNum *
                                             EPG_SIGGEN_REG_OFF);

    HWREG(base + regLoc) &= ~(uint32_t)EPG_SIGGEN0_CTL0_BRIN;
}

//*****************************************************************************
//
//! Perform bit reversal on output of signal generator
//!
//! \param base is the base address of the EPG module.
//! \param sigGenNum is the Signal generator number which is beign configured.
//!
//! This function set's signal generator to Perform bit reversal on output.
//! This results in bit reversal on data output of data transform block.
//!
//! The \e sigGenNum can take value of 0.
//!
//! \return None.
//
//*****************************************************************************
static inline void
EPG_enableBitRevOnDataOut(uint32_t base, EPG_SIGGEN sigGenNum)
{
    uint32_t regLoc;

    ASSERT((uint16_t)sigGenNum <= 0U);

    regLoc = (uint32_t)EPG_O_SIGGEN0_CTL0 + ((uint32_t)sigGenNum *
                                             EPG_SIGGEN_REG_OFF);

    HWREG(base + regLoc) |= EPG_SIGGEN0_CTL0_BROUT;
}

//*****************************************************************************
//
//! Disable bit reversal on output of signal generator
//!
//! \param base is the base address of the EPG module.
//! \param sigGenNum is the Signal generator number which is beign configured.
//!
//! This function set's signal generator to disable bit reversal on output.
//! This results in no bit reversal on data output of data transform block.
//!
//! The \e sigGenNum can take value of 0.
//!
//! \return None.
//
//*****************************************************************************
static inline void
EPG_disableBitRevOnDataOut(uint32_t base, EPG_SIGGEN sigGenNum)
{
    uint32_t regLoc;

    ASSERT(EPG_isBaseValid(base));
    ASSERT((uint16_t)sigGenNum <= 0U);

    regLoc = (uint32_t)EPG_O_SIGGEN0_CTL0 + ((uint32_t)sigGenNum *
                                             EPG_SIGGEN_REG_OFF);

    HWREG(base + regLoc) &= ~(uint32_t)EPG_SIGGEN0_CTL0_BROUT;
}

//*****************************************************************************
//
//! Set EPG signal generators data bit length
//!
//! \param base is the base address of the EPG module.
//! \param sigGenNum is the Signal generator number which is beign configured.
//! \param bitLength is the number of bits of the signal generator input data.
//!
//! This function Sets EPG signal generators data bit length.
//! This defines the number bits which participates in the shift rotate
//! operations.
//!
//! The \e sigGenNum can take value of 0.
//! The \e bitLength can have a maximum value of 64.
//!
//! \return None.
//
//*****************************************************************************
static inline void
EPG_setDataBitLen(uint32_t base, EPG_SIGGEN sigGenNum, uint32_t bitLength)
{
    uint32_t regValue, regLoc;

    ASSERT(EPG_isBaseValid(base));
    ASSERT((uint32_t)sigGenNum <= 0U);
    ASSERT(bitLength <= 0xFFU);

    regLoc = (uint32_t)EPG_O_SIGGEN0_CTL0 + ((uint32_t)sigGenNum *
                                             EPG_SIGGEN_REG_OFF);

    regValue = HWREG(base + regLoc) & ~(uint32_t)EPG_SIGGEN0_CTL0_BITLENGTH_M;
    regValue |= (bitLength << EPG_SIGGEN0_CTL0_BITLENGTH_S);

    HWREG(base + regLoc) = regValue;
}

//*****************************************************************************
//
//! Set EPG signal generator data bit 0 input
//!
//! \param base is the base address of the EPG module.
//! \param sigGenNum is the Signal generator number which is beign configured.
//! \param data0Input is the source input of bit 0 of Data Register.
//!
//! This function Sets EPG signal generator data bit 0 input.
//! This provides the ability to capture the data.
//!
//! The \e sigGenNum can take value of 0.
//! The \e data0Input can take any of the EPG_SIGGEN_DATA0_DATA_NEXT0,
//! EPG_SIGGEN_DATA0_EPGINX values where X can be from 0 to 7 which signifies
//! signal input to the EPG.
//!
//! \return None.
//
//*****************************************************************************
static inline void
EPG_setData0In(uint32_t base, EPG_SIGGEN sigGenNum,
               EPG_SignalGenData0In data0Input)
{
    uint32_t regValue, regLoc;

    ASSERT(EPG_isBaseValid(base));
    ASSERT((uint32_t)sigGenNum <= 0U);

    regLoc = (uint32_t)EPG_O_SIGGEN0_CTL1 + ((uint32_t)sigGenNum *
                                             EPG_SIGGEN_REG_OFF);

    regValue = HWREG(base + regLoc) & ~(uint32_t)EPG_SIGGEN0_CTL1_DATA0_INSEL_M;
    regValue |= (uint32_t)data0Input;

    HWREG(base + regLoc) = regValue;
}

//*****************************************************************************
//
//! Set EPG signal generator data bit 63 input
//!
//! \param base is the base address of the EPG module.
//! \param sigGenNum is the Signal generator number which is beign configured.
//! \param data0Input is the source input of bit 63 of Data Register.
//!
//! This function Sets EPG signal generator data bit 63 input.
//! This provides the ability to capture the data.
//!
//! The \e sigGenNum can take value of 0.
//! The \e data63Input can take any of the EPG_SIGGEN_DATA63_DATA_NEXT63,
//! EPG_SIGGEN_DATA63_EPGINX values where X can be from 0 to 7 which signifies
//! signal input to the EPG.
//!
//! \return None.
//
//*****************************************************************************
static inline void
EPG_setData63In(uint32_t base, EPG_SIGGEN sigGenNum,
                EPG_SignalGenData63In data63Input)
{
    uint32_t regValue, regLoc;

    ASSERT(EPG_isBaseValid(base));
    ASSERT((uint32_t)sigGenNum <= 0U);

    regLoc = (uint32_t)EPG_O_SIGGEN0_CTL1 + ((uint32_t)sigGenNum *
                                             EPG_SIGGEN_REG_OFF);

    regValue = HWREG(base + regLoc) & ~(uint32_t)EPG_SIGGEN0_CTL1_DATA63_INSEL_M;
    regValue |= (uint32_t)data63Input << EPG_SIGGEN0_CTL1_DATA63_INSEL_S;

    HWREG(base + regLoc) = regValue;
}

//*****************************************************************************
//
//! Write EPG signal generator data 0 [0:31] input
//!
//! \param base is the base address of the EPG module.
//! \param sigGenNum is the Signal generator number which is beign configured.
//! \param data0 is the first 32 bits of Data Register.
//!
//! This function Writes EPG signal generator data 0 [0:31] input.
//! This is the Data used in signal bit stream.
//!
//! The \e sigGenNum can take value of 0.
//! The \e data0 can take any 32 bit value.
//!
//! \return None.
//
//*****************************************************************************
static inline void
EPG_setData0Word(uint32_t base, EPG_SIGGEN sigGenNum, uint32_t data0)
{
    ASSERT(EPG_isBaseValid(base));

    HWREG(base + EPG_O_SIGGEN0_DATA0 + ((uint32_t)sigGenNum *
                                        EPG_SIGGEN_REG_OFF)) = data0;
}

//*****************************************************************************
//
//! Write EPG signal generator data 1 [32:63] input
//!
//! \param base is the base address of the EPG module.
//! \param sigGenNum is the Signal generator number which is beign configured.
//! \param data0 is the last 32 bits of 63 bit Data Register.
//!
//! This function Writes EPG signal generator data 1 [32:63] input.
//! This is the Data used in signal bit stream.
//!
//! The \e sigGenNum can take value of 0.
//! The \e data1 can take any 32 bit value.
//!
//! \return None.
//
//*****************************************************************************
static inline void
EPG_setData1Word(uint32_t base, EPG_SIGGEN sigGenNum, uint32_t data1)
{
    ASSERT(EPG_isBaseValid(base));

    HWREG(base + EPG_O_SIGGEN0_DATA1 + ((uint32_t)sigGenNum *
                                        EPG_SIGGEN_REG_OFF)) = data1;
}

//*****************************************************************************
//
//! Get EPG signal generator data 0 active register [0:31] value
//!
//! \param base is the base address of the EPG module.
//! \param sigGenNum is the Signal generator number which is beign configured.
//!
//! This function Reads EPG signal generator data 0 active [0:31] value
//! which is the Data resulted from the transformation.
//!
//! The \e sigGenNum can take value of 0.
//!
//! \return Returns the Data 0 Active register value.
//
//*****************************************************************************
static inline uint32_t
EPG_getData0ActiveReg(uint32_t base, EPG_SIGGEN sigGenNum)
{
    ASSERT(EPG_isBaseValid(base));

    return(HWREG(base + EPG_O_SIGGEN0_DATA0_ACTIVE +
                 ((uint32_t)sigGenNum * EPG_SIGGEN_REG_OFF)));
}

//*****************************************************************************
//
//! Get EPG signal generator data 1 active register [32:64] value
//!
//! \param base is the base address of the EPG module.
//! \param sigGenNum is the Signal generator number which is beign configured.
//!
//! This function Reads EPG signal generator data 1 active [32:64] value
//! which is the Data resulted from the transformation.
//!
//! The \e sigGenNum can take value of 0.
//!
//! \return Returns the Data 1 Active register value.
//
//*****************************************************************************
static inline uint32_t
EPG_getData1ActiveReg(uint32_t base, EPG_SIGGEN sigGenNum)
{
    ASSERT(EPG_isBaseValid(base));

    return(HWREG(base + EPG_O_SIGGEN0_DATA1_ACTIVE +
                 ((uint32_t)sigGenNum * EPG_SIGGEN_REG_OFF)));
}

//*****************************************************************************
//
//! Enable the EPG interrupt sources
//!
//! \param base is the base address of the EPG module.
//! \param intFlags is a bit mask of the interrupt sources to be enabled.
//!
//! This function enables the indicated EPG interrupt sources. Only the
//! sources that are enabled can be reflected to the processor interrupt.
//! Disabled sources have no effect on the processor.
//!
//! The \e intFlags parameter can be any of the \b EPG_INT_GLOBAL_INT,
//! \b EPG_INT_SIGGEN0_DONE, or \b EPG_INT_SIGGEN0_FILL values.
//!
//! \return None.
//
//*****************************************************************************
static inline void
EPG_enableInterruptFlag(uint32_t base, uint32_t intFlags)
{
    ASSERT(EPG_isBaseValid(base));

    HWREG(base + EPG_O_GINTEN) |= intFlags;
}

//*****************************************************************************
//
//! Disables the EPG interrupt sources
//!
//! \param base is the base address of the EPG module.
//! \param intFlags is a bit mask of the interrupt sources to be disabled.
//!
//! This function enables the indicated EPG interrupt sources. Only the
//! sources that are enabled can be reflected to the processor interrupt.
//! Disabled sources have no effect on the processor.
//!
//! The \e intFlags parameter can be any of the \b EPG_INT_GLOBAL_INT,
//! \b EPG_INT_SIGGEN0_DONE, or \b EPG_INT_SIGGEN0_FILL values.
//!
//! \return None.
//
//*****************************************************************************
static inline void
EPG_disableInterruptFlag(uint32_t base, uint32_t intFlags)
{
    ASSERT(EPG_isBaseValid(base));

    HWREG(base + EPG_O_GINTEN) &= ~intFlags;
}

//*****************************************************************************
//
//! Get the EPG interrupt sources
//!
//! \param base is the base address of the EPG module.
//!
//! This function returns the EPG interrupt sources that are active.
//!
//! \return Returns the bit mask of the interrupt sources which are currently
//!         triggered.
//
//*****************************************************************************
static inline uint32_t
EPG_getInterruptStatus(uint32_t base)
{
    uint32_t status = 0U;

    ASSERT(EPG_isBaseValid(base));

    status = HWREG(base + EPG_O_GINTSTS);

    return(status);
}

//*****************************************************************************
//
//! Clear EPG Interrupt Sources
//!
//! \param base is the base address of the EPG module.
//! \param intFlags is a bit mask of the interrupt sources to be clear.
//!
//! This function clears the indicated EPG interrupt sources if pending.
//!
//! The \e intFlags parameter can be any of the \b EPG_INT_GLOBAL_INT,
//! \b EPG_INT_SIGGEN0_DONE, or \b EPG_INT_SIGGEN0_FILL values.
//!
//! \return None.
//
//*****************************************************************************
static inline void
EPG_clearInterruptFlag(uint32_t base, uint32_t intFlags)
{
    ASSERT(EPG_isBaseValid(base));

    HWREG(base + EPG_O_GINTCLR) = intFlags;
}

//*****************************************************************************
//
//! Force EPG Interrupt Sources
//!
//! \param base is the base address of the EPG module.
//! \param intFlags is a bit mask of the interrupt sources to be trigger.
//!
//! This function triggers the indicated EPG interrupt sources. Only the
//! sources that are enabled can be reflected to the processor interrupt.
//! Disabled sources have no effect on the processor.
//!
//! The \e intFlags parameter can be any of the \b EPG_INT_GLOBAL_INT,
//! \b EPG_INT_SIGGEN0_DONE, or \b EPG_INT_SIGGEN0_FILL values.
//!
//! \return None.
//
//*****************************************************************************
static inline void
EPG_forceInterruptFlag(uint32_t base, uint32_t intFlags)
{
    ASSERT(EPG_isBaseValid(base));

    HWREG(base + EPG_O_GINTFRC) = intFlags;
}

//*****************************************************************************
//
//! Lock EPG Register
//!
//! \param base is the base address of the EPG module.
//! \param regFlags is a bit mask of the EPG registers that need to locked.
//!
//! This function Locks EPG Register from being written further.
//!
//! The \e regFlags parameter can be any of the \b EPG_LOCK_REG_GCTL0,
//! \b EPG_LOCK_REG_GCTL1, \b EPG_LOCK_REG_GCTL2 \b EPG_LOCK_REG_GCTL3,
//! \b EPG_LOCK_REG_CLKDIV0_CTL0, \b EPG_LOCK_REG_CLKDIV1_CTL0,
//! \b EPG_LOCK_REG_SIGGEN0_CTL0, \b EPG_LOCK_REG_SIGGEN0_CTL1 values.
//!
//! \return None.
//
//*****************************************************************************
static inline void
EPG_lockReg(uint32_t base, uint32_t regFlags)
{
    ASSERT(EPG_isBaseValid(base));

    HWREG(base + EPG_O_LOCK) |= regFlags;
}

//*****************************************************************************
//
//! Release Locks of EPG Register
//!
//! \param base is the base address of the EPG module.
//! \param regFlags is a bit mask of EPG registers whose lock to be released.
//!
//! This function Releases Locks of EPG Register so they can be overwritten.
//!
//! The \e regFlags parameter can be any of the \b EPG_LOCK_REG_GCTL0,
//! \b EPG_LOCK_REG_GCTL1, \b EPG_LOCK_REG_GCTL2 \b EPG_LOCK_REG_GCTL3,
//! \b EPG_LOCK_REG_CLKDIV0_CTL0, \b EPG_LOCK_REG_CLKDIV1_CTL0,
//! \b EPG_LOCK_REG_SIGGEN0_CTL0, \b EPG_LOCK_REG_SIGGEN0_CTL1 values.
//!
//! \return None.
//
//*****************************************************************************
static inline void
EPG_releaseLockReg(uint32_t base, uint32_t regFlags)
{
    ASSERT(EPG_isBaseValid(base));

    HWREG(base + EPG_O_LOCK) &= ~regFlags;
}

//*****************************************************************************
//
//! Commit EPG registers Lock
//!
//! \param base is the base address of the EPG module.
//! \param regFlags is a bit mask of EPG registers whose locks to be commited.
//!
//! This function Commits Locks of EPG lock register so that the EPG locks
//! cannot be removed.
//!
//! The \e regFlags parameter can be any of the \b EPG_LOCK_REG_GCTL0,
//! \b EPG_LOCK_REG_GCTL1, \b EPG_LOCK_REG_GCTL2 \b EPG_LOCK_REG_GCTL3,
//! \b EPG_LOCK_REG_CLKDIV0_CTL0, \b EPG_LOCK_REG_CLKDIV1_CTL0,
//! \b EPG_LOCK_REG_SIGGEN0_CTL0, \b EPG_LOCK_REG_SIGGEN0_CTL1 values.
//!
//! \return None.
//
//*****************************************************************************
static inline void
EPG_commitRegLock(uint32_t base, uint32_t regFlags)
{
    ASSERT(EPG_isBaseValid(base));

    HWREG(base + EPG_O_COMMIT) |= regFlags;
}

//*****************************************************************************
//
//! Lock EPG Mux Select Register
//!
//! \param muxbase is the base address of the EPG Mux module.
//! \param regFlags is a bit mask of the EPG Mux Select registers.
//!
//! This function Locks EPG Mux Select Register from being written further.
//!
//! The \e regFlags parameter can be of the \b EPG_MX_SEL_LOCK_REG_MXSEL0
//!
//! \return None.
//
//*****************************************************************************
static inline void
EPG_lockMXSelReg(uint32_t muxbase, uint32_t regFlags)
{
    ASSERT(EPG_isMUXBaseValid(muxbase));

    HWREG(muxbase + EPG_O_MXSELLOCK) |= regFlags;
}

//*****************************************************************************
//
//! Release Locks of EPG Mux Select Register
//!
//! \param muxbase is the base address of the EPG Mux module.
//! \param regFlags is a bit mask of the EPG Mux Select registers.
//!
//! This function Releases Locks of EPG Mux Sel Registers to allow overwriting
//! the registers.
//!
//! The \e regFlags parameter can be of the \b EPG_MX_SEL_LOCK_REG_MXSEL0
//!
//! \return None.
//
//*****************************************************************************
static inline void
EPG_releaseLockMXSelReg(uint32_t muxbase, uint32_t regFlags)
{
    ASSERT(EPG_isMUXBaseValid(muxbase));

    HWREG(muxbase + EPG_O_MXSELLOCK) &= ~regFlags;
}

//*****************************************************************************
//
//! Commit EPG Mux Select Registers Lock
//!
//! \param muxbase is the base address of the EPG Mux module.
//! \param regFlags is a bit mask of the EPG Mux Select registers.
//!
//! This function Commits the Locks of EPG Mux Sel Registers so that the locks
//! cannot be updated further.
//!
//! The \e regFlags parameter can be of the \b EPG_MX_SEL_LOCK_REG_MXSEL0
//!
//! \return None.
//
//*****************************************************************************
static inline void
EPG_commitMXSelRegLock(uint32_t muxbase, uint32_t regFlags)
{
    ASSERT(EPG_isMUXBaseValid(muxbase));

    HWREG(muxbase + EPG_O_MXSELCOMMIT) |= regFlags;
}

//*****************************************************************************
//
//! Select EPG Data Output
//!
//! \param muxbase is the base address of the EPG MUX module.
//! \param dataIn is the bit of EPG Data Input to be configured.
//! \param dataOutSel is the source of \e dataOutBit to configure.
//!
//! This function selects EPG Modules's Final Data Output which can be used to
//! feed EPG outputs to inputs of certain IPs or bypass the IP's input as is.
//!
//! The \e dataIn can take EPG_DATAIN.
//! The \e dataOutSel can take any of the EPG_DATA_OUT_DATA_IN,
//! EPG_DATA_OUT_EPG_OUT values.
//!
//! \return None.
//
//*****************************************************************************
extern void
EPG_selectEPGDataOut(uint32_t muxbase, EPG_DataIn dataIn,
                     EPG_DataOutSel dataOutSel);

//
// EPG External References & Function Declarations:
//
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif //EPG_H
