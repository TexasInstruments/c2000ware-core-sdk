//#############################################################################
//! \file i16byi16Output.c
//! \brief  FID Ouput Vector (256) 
//! \author Vishal Coelho 
//! \date   15-Apr-2016
//! 
//
//  Group:            C2000
//  Target Family:    $DEVICE$
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


#include <stdint.h>

const int16_t test_quotient[256] = {
               0,           -1,            0,           -1, 
               0,           -2,           -3,          -16, 
               0,            0,            0,           -1, 
               0,            4,           -4,           -1, 
              -1,            2,            1,           -1, 
               0,            0,            7,            1, 
               0,            0,            1,            0, 
               0,            0,            0,            0, 
              -2,            0,           -1,            0, 
               0,           -1,           -1,            0, 
               0,            2,            0,            1, 
               0,            0,            0,            0, 
              -2,            0,            2,           -1, 
               0,            0,           -1,            0, 
               0,            0,           -2,            8, 
               0,            1,            3,            0, 
               0,            0,           -1,           -1, 
               0,            0,            0,            0, 
               0,            0,           -1,            3, 
               0,            2,            0,           -1, 
               5,           -2,            0,            0, 
               0,            0,           -1,           35, 
               1,            0,           -1,            0, 
               0,           -4,           -7,            4, 
               1,           -1,            0,            2, 
               0,            0,            0,            0, 
               0,            2,            0,           11, 
               0,            0,            0,            0, 
               1,            0,            0,            0, 
              -2,           -2,            0,            0, 
               1,            0,           -8,            1, 
              -1,            0,            0,           -1, 
               0,            0,            1,            0, 
               0,            1,            0,            2, 
               0,           -1,            3,            0, 
               4,            1,            0,            0, 
               0,            0,            0,            0, 
              -2,            0,           11,            1, 
              -2,            1,            0,           -2, 
               1,            2,            7,           -1, 
               5,            5,            0,            0, 
               0,            2,            2,            0, 
               0,           10,           -1,            1, 
               1,            1,            1,            0, 
              -1,            2,            1,            1, 
               1,            0,            0,           -1, 
               0,            8,           -2,            0, 
               0,            8,            0,            0, 
              -1,           -1,            0,           -6, 
              -2,           -8,           -4,            0, 
               0,           -2,            0,            0, 
               0,            0,            0,            0, 
              -1,           -1,            7,            0, 
               0,            1,            0,            1, 
               1,            0,            2,            4, 
              -2,            0,            0,           -1, 
               0,            0,          -64,           -2, 
               0,            7,            0,           -1, 
               0,            3,            0,            1, 
              -2,           -1,            0,            1, 
              -1,            2,            0,           -1, 
               1,           -1,            0,            3, 
               0,            0,            1,            0, 
              -1,            0,            0,            2, 
}; 

const int16_t test_remainder[256] = {
            2876,          984,         1474,          263, 
          -18437,        -3827,        -5239,        -1241, 
           -6254,        -3384,        -8794,         3373, 
            8381,         2972,         1239,         2249, 
           -1822,        -2379,         5794,       -10810, 
            1664,         1988,          945,          -25, 
           -6983,        11234,          453,         1314, 
           -9981,       -22938,         5642,       -15588, 
           -5777,        16707,        -2261,        -3775, 
           12307,           -5,         4269,        -6901, 
           12020,         2470,        -3782,       -14106, 
          -11085,        -4961,       -15056,       -19854, 
            3575,        -4593,         1162,         -714, 
           17636,        -6764,          952,        16716, 
           -8035,       -18611,         4385,         2301, 
          -11301,         1921,         -967,        21855, 
           17619,       -21807,        10226,        14891, 
             945,        25183,         5768,       -22626, 
          -19670,        -6098,         2638,          982, 
           19002,        -3044,         2232,        -9959, 
           -3372,        -3456,        11707,         -317, 
          -20335,         -328,        -3576,         -710, 
            5357,         3968,        13273,        12888, 
            5425,         2205,         2697,         3244, 
           -3859,        11878,         7377,         6362, 
            1814,        -1342,        19748,       -17836, 
            -125,         5879,         4892,          126, 
           15639,         5635,       -16598,        10906, 
            -990,         8254,        10547,        15056, 
            1683,         7545,        17630,         5337, 
            2319,         5248,        -2439,        -4166, 
            4897,        -1030,        22600,        -5498, 
            3426,         8511,        -8795,         7517, 
           -9017,        -7923,         -684,        -6624, 
          -24702,        -7237,        -3975,       -20377, 
           -4329,          952,       -14296,         2529, 
           12790,          -58,         2346,        -3593, 
            -328,         -632,         1056,         2720, 
           -2276,        -8313,         4258,         2981, 
            -368,         -867,         2608,       -11494, 
           -1045,         -309,       -21859,         7927, 
            4830,        -5437,         8114,        14985, 
           15586,        -1013,         6613,        11174, 
           14750,         7753,         2744,          876, 
           -9231,        -1830,        -5127,        -4432, 
            7574,       -13022,       -13400,          -72, 
           -2159,         1032,        -4547,        22426, 
            3868,         1773,        -9970,        -3538, 
           -8950,        -4868,        10669,        -1241, 
            3286,         -673,         5500,         2620, 
           13560,          672,       -13904,        -5602, 
           -2305,        17298,        20853,       -26200, 
           -1785,        -4127,        -1542,         1434, 
          -10758,        -3474,       -19075,         9032, 
             275,        -2067,         8391,        -4728, 
            1773,        15483,         4054,          -84, 
            6370,       -13112,         -362,        -1055, 
           25882,        -2374,       -16877,        -5211, 
           -3820,        -3403,        26029,        -1803, 
           -6669,        -5745,        -2880,        -2655, 
            1344,         -664,       -13281,       -13906, 
           -4727,        -7346,          355,         3170, 
            8589,       -26877,       -12089,        18168, 
            8447,         2213,       -25615,         2987, 
}; 


// End of File
