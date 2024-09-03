//#############################################################################
//! \file   fastrts_logtable.c
//! \brief  Natural Logarithm Lookup Table (32) 
//! \author Vishal Coelho 
//! \date   25-Jan-2017
//! 
//
//  Group:          C2000
//  Target Family:  $DEVICE$
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

#include "fastrts.h"

#if USE_FPU32==1
const fsize_t FPULOG2             =  0.6931471805599F; 
const fsize_t FPUINVLOG10         =  0.4342944819033F; 
const fsize_t FPUEXPBIAS          = 127.0000000000000F; 
const isize_t FPULOG_TABLE_MASK1  = 0x3FFFFFFF; 
const isize_t FPULOG_TABLE_MASK2  = 0x3F800000; 
#else USE_FPU64==1
const fsize_t FPULOG2             =  0.6931471805599L; 
const fsize_t FPUINVLOG10         =  0.4342944819033L; 
const fsize_t FPUEXPBIAS          = 1023.0000000000000L; 
const isize_t FPULOG_TABLE_MASK1  = 0x3FFFFFFFFFFFFFFF; 
const isize_t FPULOG_TABLE_MASK2  = 0x3FF0000000000000; 
#endif //USE_FPU32

//This table has 99 entries
const fsize_t FastRTS_logTable[99] = {
     0.0000000000000,   0.9998427992674,  -0.4847911018021,//   0 -> a0 a1 a2
     0.0000275291995,   0.9980708040346,  -0.4562771546109,//   1 -> a0 a1 a2
     0.0001288044413,   0.9948210100411,  -0.4302069126207,//   2 -> a0 a1 a2
     0.0003380953764,   0.9903481346473,  -0.4063088992594,//   3 -> a0 a1 a2
     0.0006803358416,   0.9848651381166,  -0.3843483167891,//   4 -> a0 a1 a2
     0.0011731595065,   0.9785505884417,  -0.3641212561818,//   5 -> a0 a1 a2
     0.0018284930657,   0.9715546054665,  -0.3454499459991,//   6 -> a0 a1 a2
     0.0026538075361,   0.9640036832441,  -0.3281788325266,//   7 -> a0 a1 a2
     0.0036531040203,   0.9560046214281,  -0.3121713290093,//   8 -> a0 a1 a2
     0.0048276922798,   0.9476477450549,  -0.2973071065684,//   9 -> a0 a1 a2
     0.0061768069432,   0.9390095529690,  -0.2834798260461,//  10 -> a0 a1 a2
     0.0076980959745,   0.9301549052016,  -0.2705952306243,//  11 -> a0 a1 a2
     0.0093880082817,   0.9211388365590,  -0.2585695350951,//  12 -> a0 a1 a2
     0.0112421014268,   0.9120080657950,  -0.2473280602005,//  13 -> a0 a1 a2
     0.0132552858594,   0.9028022558110,  -0.2368040703340,//  14 -> a0 a1 a2
     0.0154220185869,   0.8935550694019,  -0.2269377807187,//  15 -> a0 a1 a2
     0.0177364564779,   0.8842950564587,  -0.2176755063963,//  16 -> a0 a1 a2
     0.0201925772769,   0.8750464017178,  -0.2089689303380,//  17 -> a0 a1 a2
     0.0227842747501,   0.8658295567283,  -0.2007744720005,//  18 -> a0 a1 a2
     0.0255054330825,   0.8566617753623,  -0.1930527408698,//  19 -> a0 a1 a2
     0.0283499846180,   0.8475575687189,  -0.1857680621711,//  20 -> a0 a1 a2
     0.0313119542237,   0.8385290924587,  -0.1788880640520,//  21 -> a0 a1 a2
     0.0343854929130,   0.8295864773384,  -0.1723833173021,//  22 -> a0 a1 a2
     0.0375649028492,   0.8207381118556,  -0.1662270200986,//  23 -> a0 a1 a2
     0.0408446554406,   0.8119908844263,  -0.1603947214664,//  24 -> a0 a1 a2
     0.0442194039060,   0.8033503912691,  -0.1548640781109,//  25 -> a0 a1 a2
     0.0476839914351,   0.7948211151512,  -0.1496146400928,//  26 -> a0 a1 a2
     0.0512334558374,   0.7864065793495,  -0.1446276615129,//  27 -> a0 a1 a2
     0.0548630314249,   0.7781094804378,  -0.1398859329117,//  28 -> a0 a1 a2
     0.0585681487095,   0.7699318029982,  -0.1353736325973,//  29 -> a0 a1 a2
     0.0623444324097,   0.7618749188190,  -0.1310761944828,//  30 -> a0 a1 a2
     0.0661876981423,   0.7539396728045,  -0.1269801903868,//  31 -> a0 a1 a2
     0.0700939481277,   0.7461264574323,  -0.1230732250001,//  32 -> a0 a1 a2
}; 


// End of File
