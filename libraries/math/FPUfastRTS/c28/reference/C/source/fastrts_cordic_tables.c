//#############################################################################
//! \file FPU_FastRTS_cordicTable.c
//! \brief CORDIC Tables (64) 
//! \author Vishal Coelho 
//! \date   10-Nov-2016
//! 
//
//  Group:			C2000
//  Target Family:	$DEVICE$
//
//#############################################################################
//
//
// 
// C2000Ware v5.03.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
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

#if USE_FPU64 == 1
//This table has 64 entries
const long long FastRTS_CORDIC_atanTbl[64] = {
	0x3fe921fb54442d18,    // arctan(2^-  0)
	0x3fddac670561bb4f,    // arctan(2^-  1)
	0x3fcf5b75f92c80dd,    // arctan(2^-  2)
	0x3fbfd5ba9aac2f6e,    // arctan(2^-  3)
	0x3faff55bb72cfdea,    // arctan(2^-  4)
	0x3f9ffd55bba97625,    // arctan(2^-  5)
	0x3f8fff555bbb729b,    // arctan(2^-  6)
	0x3f7fffd555bbba97,    // arctan(2^-  7)
	0x3f6ffff5555bbbb7,    // arctan(2^-  8)
	0x3f5ffffd5555bbbc,    // arctan(2^-  9)
	0x3f4fffff55555bbc,    // arctan(2^- 10)
	0x3f3fffffd55555bc,    // arctan(2^- 11)
	0x3f2ffffff555555c,    // arctan(2^- 12)
	0x3f1ffffffd555556,    // arctan(2^- 13)
	0x3f0fffffff555555,    // arctan(2^- 14)
	0x3effffffffd55555,    // arctan(2^- 15)
	0x3eeffffffff55555,    // arctan(2^- 16)
	0x3edffffffffd5555,    // arctan(2^- 17)
	0x3ecfffffffff5555,    // arctan(2^- 18)
	0x3ebfffffffffd555,    // arctan(2^- 19)
	0x3eaffffffffff555,    // arctan(2^- 20)
	0x3e9ffffffffffd55,    // arctan(2^- 21)
	0x3e8fffffffffff55,    // arctan(2^- 22)
	0x3e7fffffffffffd5,    // arctan(2^- 23)
	0x3e6ffffffffffff5,    // arctan(2^- 24)
	0x3e5ffffffffffffd,    // arctan(2^- 25)
	0x3e4fffffffffffff,    // arctan(2^- 26)
	0x3e40000000000000,    // arctan(2^- 27)
	0x3e30000000000000,    // arctan(2^- 28)
	0x3e20000000000000,    // arctan(2^- 29)
	0x3e10000000000000,    // arctan(2^- 30)
	0x3e00000000000000,    // arctan(2^- 31)
	0x3df0000000000000,    // arctan(2^- 32)
	0x3de0000000000000,    // arctan(2^- 33)
	0x3dd0000000000000,    // arctan(2^- 34)
	0x3dc0000000000000,    // arctan(2^- 35)
	0x3db0000000000000,    // arctan(2^- 36)
	0x3da0000000000000,    // arctan(2^- 37)
	0x3d90000000000000,    // arctan(2^- 38)
	0x3d80000000000000,    // arctan(2^- 39)
	0x3d70000000000000,    // arctan(2^- 40)
	0x3d60000000000000,    // arctan(2^- 41)
	0x3d50000000000000,    // arctan(2^- 42)
	0x3d40000000000000,    // arctan(2^- 43)
	0x3d30000000000000,    // arctan(2^- 44)
	0x3d20000000000000,    // arctan(2^- 45)
	0x3d10000000000000,    // arctan(2^- 46)
	0x3d00000000000000,    // arctan(2^- 47)
	0x3cf0000000000000,    // arctan(2^- 48)
	0x3ce0000000000000,    // arctan(2^- 49)
	0x3cd0000000000000,    // arctan(2^- 50)
	0x3cc0000000000000,    // arctan(2^- 51)
	0x3cb0000000000000,    // arctan(2^- 52)
	0x3ca0000000000000,    // arctan(2^- 53)
	0x3c90000000000000,    // arctan(2^- 54)
	0x3c80000000000000,    // arctan(2^- 55)
	0x3c70000000000000,    // arctan(2^- 56)
	0x3c60000000000000,    // arctan(2^- 57)
	0x3c50000000000000,    // arctan(2^- 58)
	0x3c40000000000000,    // arctan(2^- 59)
	0x3c30000000000000,    // arctan(2^- 60)
	0x3c20000000000000,    // arctan(2^- 61)
	0x3c10000000000000,    // arctan(2^- 62)
	0x3c00000000000000,    // arctan(2^- 63)
}; 

//This table has 64 entries
const long long FastRTS_CORDIC_scaleTbl[64] = {
	0x3fe6a09e667f3bcc,    // 1/sqrt(1 + 2^(-2*  0))
	0x3fe43d136248490e,    // 1/sqrt(1 + 2^(-2*  1))
	0x3fe3a261ba6d7a36,    // 1/sqrt(1 + 2^(-2*  2))
	0x3fe37b9141deb3fe,    // 1/sqrt(1 + 2^(-2*  3))
	0x3fe371dac182eef6,    // 1/sqrt(1 + 2^(-2*  4))
	0x3fe36f6cfabd9620,    // 1/sqrt(1 + 2^(-2*  5))
	0x3fe36ed1869f27ea,    // 1/sqrt(1 + 2^(-2*  6))
	0x3fe36eaaa970b210,    // 1/sqrt(1 + 2^(-2*  7))
	0x3fe36ea0f222a6d2,    // 1/sqrt(1 + 2^(-2*  8))
	0x3fe36e9e844efd25,    // 1/sqrt(1 + 2^(-2*  9))
	0x3fe36e9de8da104c,    // 1/sqrt(1 + 2^(-2* 10))
	0x3fe36e9dc1fcd4ef,    // 1/sqrt(1 + 2^(-2* 11))
	0x3fe36e9db8458615,    // 1/sqrt(1 + 2^(-2* 12))
	0x3fe36e9db5d7b25e,    // 1/sqrt(1 + 2^(-2* 13))
	0x3fe36e9db53c3d70,    // 1/sqrt(1 + 2^(-2* 14))
	0x3fe36e9db5156035,    // 1/sqrt(1 + 2^(-2* 15))
	0x3fe36e9db50ba8e6,    // 1/sqrt(1 + 2^(-2* 16))
	0x3fe36e9db5093b12,    // 1/sqrt(1 + 2^(-2* 17))
	0x3fe36e9db5089f9d,    // 1/sqrt(1 + 2^(-2* 18))
	0x3fe36e9db50878c0,    // 1/sqrt(1 + 2^(-2* 19))
	0x3fe36e9db5086f09,    // 1/sqrt(1 + 2^(-2* 20))
	0x3fe36e9db5086c9b,    // 1/sqrt(1 + 2^(-2* 21))
	0x3fe36e9db5086c00,    // 1/sqrt(1 + 2^(-2* 22))
	0x3fe36e9db5086bd9,    // 1/sqrt(1 + 2^(-2* 23))
	0x3fe36e9db5086bcf,    // 1/sqrt(1 + 2^(-2* 24))
	0x3fe36e9db5086bcd,    // 1/sqrt(1 + 2^(-2* 25))
	0x3fe36e9db5086bcd,    // 1/sqrt(1 + 2^(-2* 26))
	0x3fe36e9db5086bcd,    // 1/sqrt(1 + 2^(-2* 27))
	0x3fe36e9db5086bcd,    // 1/sqrt(1 + 2^(-2* 28))
	0x3fe36e9db5086bcd,    // 1/sqrt(1 + 2^(-2* 29))
	0x3fe36e9db5086bcd,    // 1/sqrt(1 + 2^(-2* 30))
	0x3fe36e9db5086bcd,    // 1/sqrt(1 + 2^(-2* 31))
	0x3fe36e9db5086bcd,    // 1/sqrt(1 + 2^(-2* 32))
	0x3fe36e9db5086bcd,    // 1/sqrt(1 + 2^(-2* 33))
	0x3fe36e9db5086bcd,    // 1/sqrt(1 + 2^(-2* 34))
	0x3fe36e9db5086bcd,    // 1/sqrt(1 + 2^(-2* 35))
	0x3fe36e9db5086bcd,    // 1/sqrt(1 + 2^(-2* 36))
	0x3fe36e9db5086bcd,    // 1/sqrt(1 + 2^(-2* 37))
	0x3fe36e9db5086bcd,    // 1/sqrt(1 + 2^(-2* 38))
	0x3fe36e9db5086bcd,    // 1/sqrt(1 + 2^(-2* 39))
	0x3fe36e9db5086bcd,    // 1/sqrt(1 + 2^(-2* 40))
	0x3fe36e9db5086bcd,    // 1/sqrt(1 + 2^(-2* 41))
	0x3fe36e9db5086bcd,    // 1/sqrt(1 + 2^(-2* 42))
	0x3fe36e9db5086bcd,    // 1/sqrt(1 + 2^(-2* 43))
	0x3fe36e9db5086bcd,    // 1/sqrt(1 + 2^(-2* 44))
	0x3fe36e9db5086bcd,    // 1/sqrt(1 + 2^(-2* 45))
	0x3fe36e9db5086bcd,    // 1/sqrt(1 + 2^(-2* 46))
	0x3fe36e9db5086bcd,    // 1/sqrt(1 + 2^(-2* 47))
	0x3fe36e9db5086bcd,    // 1/sqrt(1 + 2^(-2* 48))
	0x3fe36e9db5086bcd,    // 1/sqrt(1 + 2^(-2* 49))
	0x3fe36e9db5086bcd,    // 1/sqrt(1 + 2^(-2* 50))
	0x3fe36e9db5086bcd,    // 1/sqrt(1 + 2^(-2* 51))
	0x3fe36e9db5086bcd,    // 1/sqrt(1 + 2^(-2* 52))
	0x3fe36e9db5086bcd,    // 1/sqrt(1 + 2^(-2* 53))
	0x3fe36e9db5086bcd,    // 1/sqrt(1 + 2^(-2* 54))
	0x3fe36e9db5086bcd,    // 1/sqrt(1 + 2^(-2* 55))
	0x3fe36e9db5086bcd,    // 1/sqrt(1 + 2^(-2* 56))
	0x3fe36e9db5086bcd,    // 1/sqrt(1 + 2^(-2* 57))
	0x3fe36e9db5086bcd,    // 1/sqrt(1 + 2^(-2* 58))
	0x3fe36e9db5086bcd,    // 1/sqrt(1 + 2^(-2* 59))
	0x3fe36e9db5086bcd,    // 1/sqrt(1 + 2^(-2* 60))
	0x3fe36e9db5086bcd,    // 1/sqrt(1 + 2^(-2* 61))
	0x3fe36e9db5086bcd,    // 1/sqrt(1 + 2^(-2* 62))
	0x3fe36e9db5086bcd,    // 1/sqrt(1 + 2^(-2* 63))
}; 
#else
//This table has 64 entries
const long FastRTS_CORDIC_atanTbl[64] = {
	0x3f490fdb,    // arctan(2^-  0)
	0x3eed6338,    // arctan(2^-  1)
	0x3e7adbb0,    // arctan(2^-  2)
	0x3dfeadd5,    // arctan(2^-  3)
	0x3d7faade,    // arctan(2^-  4)
	0x3cffeaae,    // arctan(2^-  5)
	0x3c7ffaab,    // arctan(2^-  6)
	0x3bfffeab,    // arctan(2^-  7)
	0x3b7fffab,    // arctan(2^-  8)
	0x3affffeb,    // arctan(2^-  9)
	0x3a7ffffb,    // arctan(2^- 10)
	0x39ffffff,    // arctan(2^- 11)
	0x39800000,    // arctan(2^- 12)
	0x39000000,    // arctan(2^- 13)
	0x38800000,    // arctan(2^- 14)
	0x38000000,    // arctan(2^- 15)
	0x37800000,    // arctan(2^- 16)
	0x37000000,    // arctan(2^- 17)
	0x36800000,    // arctan(2^- 18)
	0x36000000,    // arctan(2^- 19)
	0x35800000,    // arctan(2^- 20)
	0x35000000,    // arctan(2^- 21)
	0x34800000,    // arctan(2^- 22)
	0x34000000,    // arctan(2^- 23)
	0x33800000,    // arctan(2^- 24)
	0x33000000,    // arctan(2^- 25)
	0x32800000,    // arctan(2^- 26)
	0x32000000,    // arctan(2^- 27)
	0x31800000,    // arctan(2^- 28)
	0x31000000,    // arctan(2^- 29)
	0x30800000,    // arctan(2^- 30)
	0x30000000,    // arctan(2^- 31)
	0x2f800000,    // arctan(2^- 32)
	0x2f000000,    // arctan(2^- 33)
	0x2e800000,    // arctan(2^- 34)
	0x2e000000,    // arctan(2^- 35)
	0x2d800000,    // arctan(2^- 36)
	0x2d000000,    // arctan(2^- 37)
	0x2c800000,    // arctan(2^- 38)
	0x2c000000,    // arctan(2^- 39)
	0x2b800000,    // arctan(2^- 40)
	0x2b000000,    // arctan(2^- 41)
	0x2a800000,    // arctan(2^- 42)
	0x2a000000,    // arctan(2^- 43)
	0x29800000,    // arctan(2^- 44)
	0x29000000,    // arctan(2^- 45)
	0x28800000,    // arctan(2^- 46)
	0x28000000,    // arctan(2^- 47)
	0x27800000,    // arctan(2^- 48)
	0x27000000,    // arctan(2^- 49)
	0x26800000,    // arctan(2^- 50)
	0x26000000,    // arctan(2^- 51)
	0x25800000,    // arctan(2^- 52)
	0x25000000,    // arctan(2^- 53)
	0x24800000,    // arctan(2^- 54)
	0x24000000,    // arctan(2^- 55)
	0x23800000,    // arctan(2^- 56)
	0x23000000,    // arctan(2^- 57)
	0x22800000,    // arctan(2^- 58)
	0x22000000,    // arctan(2^- 59)
	0x21800000,    // arctan(2^- 60)
	0x21000000,    // arctan(2^- 61)
	0x20800000,    // arctan(2^- 62)
	0x20000000,    // arctan(2^- 63)
}; 

//This table has 64 entries
const long FastRTS_CORDIC_scaleTbl[64] = {
	0x3f3504f3,    // 1/sqrt(1 + 2^(-2*  0))
	0x3f21e89b,    // 1/sqrt(1 + 2^(-2*  1))
	0x3f1d130e,    // 1/sqrt(1 + 2^(-2*  2))
	0x3f1bdc8a,    // 1/sqrt(1 + 2^(-2*  3))
	0x3f1b8ed6,    // 1/sqrt(1 + 2^(-2*  4))
	0x3f1b7b68,    // 1/sqrt(1 + 2^(-2*  5))
	0x3f1b768c,    // 1/sqrt(1 + 2^(-2*  6))
	0x3f1b7555,    // 1/sqrt(1 + 2^(-2*  7))
	0x3f1b7507,    // 1/sqrt(1 + 2^(-2*  8))
	0x3f1b74f4,    // 1/sqrt(1 + 2^(-2*  9))
	0x3f1b74ef,    // 1/sqrt(1 + 2^(-2* 10))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 11))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 12))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 13))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 14))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 15))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 16))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 17))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 18))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 19))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 20))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 21))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 22))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 23))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 24))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 25))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 26))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 27))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 28))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 29))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 30))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 31))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 32))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 33))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 34))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 35))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 36))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 37))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 38))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 39))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 40))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 41))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 42))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 43))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 44))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 45))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 46))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 47))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 48))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 49))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 50))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 51))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 52))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 53))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 54))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 55))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 56))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 57))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 58))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 59))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 60))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 61))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 62))
	0x3f1b74ee,    // 1/sqrt(1 + 2^(-2* 63))
}; 
#endif

// End of File
