//#############################################################################
//
// FILE:   flash_programming_f280013x.h
//
// TITLE:  A set of Constant Values for the F280013x Family.
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef FLASH_PROGRAMMING_F280013X_H_
#define FLASH_PROGRAMMING_F280013X_H_

// Bank0 Sector start addresses
#define FlashBank0StartAddress      0x80000U
#define     Bzero_Sector0_start     0x00080000U
#define     Bzero_Sector1_start     0x00080400U
#define     Bzero_Sector2_start     0x00080800U
#define     Bzero_Sector3_start     0x00080C00U
#define     Bzero_Sector4_start     0x00081000U
#define     Bzero_Sector5_start     0x00081400U
#define     Bzero_Sector6_start     0x00081800U
#define     Bzero_Sector7_start     0x00081C00U
#define     Bzero_Sector8_start     0x00082000U
#define     Bzero_Sector9_start     0x00082400U
#define     Bzero_Sector10_start    0x00082800U
#define     Bzero_Sector11_start    0x00082C00U
#define     Bzero_Sector12_start    0x00083000U
#define     Bzero_Sector13_start    0x00083400U
#define     Bzero_Sector14_start    0x00083800U
#define     Bzero_Sector15_start    0x00083C00U
#define     Bzero_Sector16_start    0x00084000U
#define     Bzero_Sector17_start    0x00084400U
#define     Bzero_Sector18_start    0x00084800U
#define     Bzero_Sector19_start    0x00084C00U
#define     Bzero_Sector20_start    0x00085000U
#define     Bzero_Sector21_start    0x00085400U
#define     Bzero_Sector22_start    0x00085800U
#define     Bzero_Sector23_start    0x00085C00U
#define     Bzero_Sector24_start    0x00086000U
#define     Bzero_Sector25_start    0x00086400U
#define     Bzero_Sector26_start    0x00086800U
#define     Bzero_Sector27_start    0x00086C00U
#define     Bzero_Sector28_start    0x00087000U
#define     Bzero_Sector29_start    0x00087400U
#define     Bzero_Sector30_start    0x00087800U
#define     Bzero_Sector31_start    0x00087C00U
#define     Bzero_Sector32_start    0x00088000U
#define     Bzero_Sector33_start    0x00088400U
#define     Bzero_Sector34_start    0x00088800U
#define     Bzero_Sector35_start    0x00088C00U
#define     Bzero_Sector36_start    0x00089000U
#define     Bzero_Sector37_start    0x00089400U
#define     Bzero_Sector38_start    0x00089800U
#define     Bzero_Sector39_start    0x00089C00U
#define     Bzero_Sector40_start    0x0008A000U
#define     Bzero_Sector41_start    0x0008A400U
#define     Bzero_Sector42_start    0x0008A800U
#define     Bzero_Sector43_start    0x0008AC00U
#define     Bzero_Sector44_start    0x0008B000U
#define     Bzero_Sector45_start    0x0008B400U
#define     Bzero_Sector46_start    0x0008B800U
#define     Bzero_Sector47_start    0x0008BC00U
#define     Bzero_Sector48_start    0x0008C000U
#define     Bzero_Sector49_start    0x0008C400U
#define     Bzero_Sector50_start    0x0008C800U
#define     Bzero_Sector51_start    0x0008CC00U
#define     Bzero_Sector52_start    0x0008D000U
#define     Bzero_Sector53_start    0x0008D400U
#define     Bzero_Sector54_start    0x0008D800U
#define     Bzero_Sector55_start    0x0008DC00U
#define     Bzero_Sector56_start    0x0008E000U
#define     Bzero_Sector57_start    0x0008E400U
#define     Bzero_Sector58_start    0x0008E800U
#define     Bzero_Sector59_start    0x0008EC00U
#define     Bzero_Sector60_start    0x0008F000U
#define     Bzero_Sector61_start    0x0008F400U
#define     Bzero_Sector62_start    0x0008F800U
#define     Bzero_Sector63_start    0x0008FC00U
#define     Bzero_Sector64_start    0x00090000U
#define     Bzero_Sector65_start    0x00090400U
#define     Bzero_Sector66_start    0x00090800U
#define     Bzero_Sector67_start    0x00090C00U
#define     Bzero_Sector68_start    0x00091000U
#define     Bzero_Sector69_start    0x00091400U
#define     Bzero_Sector70_start    0x00091800U
#define     Bzero_Sector71_start    0x00091C00U
#define     Bzero_Sector72_start    0x00092000U
#define     Bzero_Sector73_start    0x00092400U
#define     Bzero_Sector74_start    0x00092800U
#define     Bzero_Sector75_start    0x00092C00U
#define     Bzero_Sector76_start    0x00093000U
#define     Bzero_Sector77_start    0x00093400U
#define     Bzero_Sector78_start    0x00093800U
#define     Bzero_Sector79_start    0x00093C00U
#define     Bzero_Sector80_start    0x00094000U
#define     Bzero_Sector81_start    0x00094400U
#define     Bzero_Sector82_start    0x00094800U
#define     Bzero_Sector83_start    0x00094C00U
#define     Bzero_Sector84_start    0x00095000U
#define     Bzero_Sector85_start    0x00095400U
#define     Bzero_Sector86_start    0x00095800U
#define     Bzero_Sector87_start    0x00095C00U
#define     Bzero_Sector88_start    0x00096000U
#define     Bzero_Sector89_start    0x00096400U
#define     Bzero_Sector90_start    0x00096800U
#define     Bzero_Sector91_start    0x00096C00U
#define     Bzero_Sector92_start    0x00097000U
#define     Bzero_Sector93_start    0x00097400U
#define     Bzero_Sector94_start    0x00097800U
#define     Bzero_Sector95_start    0x00097C00U
#define     Bzero_Sector96_start    0x00098000U
#define     Bzero_Sector97_start    0x00098400U
#define     Bzero_Sector98_start    0x00098800U
#define     Bzero_Sector99_start    0x00098C00U
#define     Bzero_Sector100_start   0x00099000U
#define     Bzero_Sector101_start   0x00099400U
#define     Bzero_Sector102_start   0x00099800U
#define     Bzero_Sector103_start   0x00099C00U
#define     Bzero_Sector104_start   0x0009A000U
#define     Bzero_Sector105_start   0x0009A400U
#define     Bzero_Sector106_start   0x0009A800U
#define     Bzero_Sector107_start   0x0009AC00U
#define     Bzero_Sector108_start   0x0009B000U
#define     Bzero_Sector109_start   0x0009B400U
#define     Bzero_Sector110_start   0x0009B800U
#define     Bzero_Sector111_start   0x0009BC00U
#define     Bzero_Sector112_start   0x0009C000U
#define     Bzero_Sector113_start   0x0009C400U
#define     Bzero_Sector114_start   0x0009C800U
#define     Bzero_Sector115_start   0x0009CC00U
#define     Bzero_Sector116_start   0x0009D000U
#define     Bzero_Sector117_start   0x0009D400U
#define     Bzero_Sector118_start   0x0009D800U
#define     Bzero_Sector119_start   0x0009DC00U
#define     Bzero_Sector120_start   0x0009E000U
#define     Bzero_Sector121_start   0x0009E400U
#define     Bzero_Sector122_start   0x0009E800U
#define     Bzero_Sector123_start   0x0009EC00U
#define     Bzero_Sector124_start   0x0009F000U
#define     Bzero_Sector125_start   0x0009F400U
#define     Bzero_Sector126_start   0x0009F800U
#define     Bzero_Sector127_start   0x0009FC00U

#define FlashBank0EndAddress        0x9FFFFU

//Sector length in number of 16bits
#define Sector2KB_u16length   0x400U
#define Bank256KB_u16length   0x20000U

//Sector length in number of 32bits
#define Sector2KB_u32length   0x200U
#define Bank256KB_u32length   0x10000U

/*!
    \brief Define to map the direct access to the FMC registers.
*/
#define FlashTech_CPU0_BASE_ADDRESS ((Fapi_FmcRegistersType *)FLASH_WRAPPER_PROGRAM_BASE)

#endif /* FLASH_PROGRAMMING_F280013X_H_ */
