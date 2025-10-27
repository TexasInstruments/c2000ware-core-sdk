//#############################################################################
//! \file /data_output_3.h
//!
//! \brief  Phase of the Output of the real FFT 256 pt Example
//!
//! Run the RFFTforC28xNew.m MATLAB script to get the input/output vectors
//
//#############################################################################
// 
// C2000Ware v6.00.01.00
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
// Note: angle(X(1)) i.e. arctan(0/-1.4913)  in MATLAB gives pi
// However, arctan(0/-1.4913)  = 0.0 , hence the manual correction of the first
// value

 0.0000000,  3.1107831,  3.0801200,  3.0497468,
 3.0198008,  2.9904109,  2.9616954,  2.9337600,
-1.5854463,  2.8805842,  2.8554854,  2.8314504,
 2.8085153,  2.7867042,  2.7660296,  2.7464942,
 2.7280918,  2.7108090,  2.6946259, -0.4620749,
-0.4761369, -0.4891845, -0.5012519, -0.5123745,
-0.5225889, -0.5319318, -0.5404400, -0.5481499,
-0.5550972, -0.5613169, -0.5668427, -0.5717075,
-0.5759427, -0.5795787, -0.5826443, -0.5851672,
-0.5871738, -0.5886893, -0.5897375, -0.5903410,
-0.5905214, -0.5902992, -0.5896936, -0.5887230,
-0.5874048, -0.5857553, -0.5837902, -0.5815242,
-0.5789712, -0.5761445, -0.5730565, -0.5697192,
-0.5661437, -0.5623408, -0.5583204, -0.5540923,
-0.5496654, -0.5450484, -0.5402494, -0.5352764,
-0.5301365, -0.5248369, -0.5193843, -0.5137850,
-0.5080450, -0.5021702, -0.4961659, -0.4900376,
-0.4837901, -0.4774282, -0.4709565, -0.4643794,
-0.4577009, -0.4509252, -0.4440559, -0.4370967,
-0.4300512, -0.4229226, -0.4157142, -0.4084291,
-0.4010702, -0.3936403, -0.3861423, -0.3785786,
-0.3709519, -0.3632646, -0.3555190, -0.3477174,
-0.3398619, -0.3319548, -0.3239979, -0.3159932,
-0.3079427, -0.2998483, -0.2917116, -0.2835344,
-0.2753184, -0.2670652, -0.2587763, -0.2504534,
-0.2420978, -0.2337111, -0.2252947, -0.2168499,
-0.2083780, -0.1998805, -0.1913585, -0.1828133,
-0.1742461, -0.1656582, -0.1570507, -0.1484247,
-0.1397814, -0.1311220, -0.1224474, -0.1137589,
-0.1050573, -0.0963439, -0.0876196, -0.0788855,
-0.0701425, -0.0613917, -0.0526341, -0.0438707,
-0.0351023, -0.0263301, -0.0175550, -0.0087780,

// End of file
