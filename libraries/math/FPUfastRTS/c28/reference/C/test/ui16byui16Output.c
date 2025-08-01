//#############################################################################
//! \file ui16byui16Output.c
//! \brief  FID Ouput Vector (256) 
//! \author Vishal Coelho 
//! \date   14-Apr-2016
//! 
//
//  Group:            C2000
//  Target Family:    $DEVICE$
//
//#############################################################################
//
//
// 
// C2000Ware v6.00.00.00
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

const uint16_t test_quotient[256] = {
               1,            2,            0,            0, 
              16,            0,            0,            0, 
               9,            3,            0,            1, 
               7,            0,            7,            0, 
               0,            1,            1,            1, 
               0,            0,            1,            4, 
              22,            1,            1,            0, 
               0,            0,            1,            0, 
               0,            0,            0,            3, 
               0,           11,            1,            0, 
               0,            0,            1,            1, 
               3,            0,           10,            9, 
               1,            7,            0,            0, 
               0,            1,            0,            0, 
               0,            0,            0,            0, 
               1,            0,            6,            5, 
               5,            2,            0,            0, 
               2,            0,            1,            0, 
               1,            0,            3,            0, 
              12,            0,            3,            4, 
               0,            4,            1,            1, 
               0,            0,           14,            1, 
               1,            1,            0,            0, 
               1,            0,            3,            0, 
               0,            0,            0,            0, 
               0,            6,            0,            3, 
               5,            1,            0,            0, 
               3,            2,            0,            0, 
               1,            1,            0,            2, 
               2,            2,            0,            3, 
               0,            4,            0,            1, 
               3,            2,            0,            1, 
               0,            0,            0,            2, 
               0,            2,            0,            0, 
               1,            2,            0,            6, 
               2,            1,            2,            2, 
               0,            0,            0,            0, 
               0,            0,            0,            1, 
              13,            2,            0,            0, 
               0,            1,            0,            0, 
               1,            1,            2,            0, 
               0,            0,           10,            3, 
               3,            0,            0,            0, 
               1,            0,            0,            0, 
               1,            0,            2,            0, 
               1,            0,            1,            2, 
               2,            0,            0,            0, 
               2,            0,            1,          115, 
               0,            1,            0,          267, 
               1,            1,            1,            1, 
               1,            0,            1,           14, 
               1,            1,            1,            3, 
               1,            0,            1,            0, 
               1,            0,            3,            0, 
               1,            0,            2,            0, 
               0,            1,            1,            0, 
               1,            1,            0,            0, 
               1,            0,            2,            2, 
               0,            1,            0,            0, 
               0,            0,            0,            1, 
               0,            0,            3,            0, 
               1,            1,            0,            2, 
               0,            3,            1,            0, 
               1,            0,            0,            0, 
}; 

const uint16_t test_remainder[256] = {
            8886,         7521,         8322,        59858, 
            1874,         6392,        18251,        35840, 
            4529,        11748,        10329,        19062, 
              85,        31809,         3467,         9299, 
           27640,         8958,         5057,         3655, 
           42974,         2340,         9856,         9357, 
             437,          895,        15932,        25705, 
           42957,        11219,         5792,         2086, 
           18148,         3026,         6366,         6793, 
           45536,          112,        30167,         2257, 
           28753,        25005,        17370,        21240, 
             526,        32097,         1391,          218, 
           12302,         5085,        18089,        44544, 
           42932,          836,         7799,        32660, 
           62897,        22307,        38356,        14668, 
           20897,        16718,          338,         2179, 
            1570,        11627,        35862,         9085, 
            1858,        16876,        20567,        16664, 
           10317,        15959,         3494,        22936, 
             704,        16455,         7507,         3173, 
           23046,         2512,         6263,        13777, 
           60108,        18732,         1295,         1040, 
            7296,         9501,         4971,         3536, 
            7409,        51063,         1942,         8513, 
           37278,        30762,          780,        22093, 
           10629,         1719,        20395,          995, 
             176,         2673,        17234,        42865, 
            7728,          676,        29526,         5493, 
            4756,         3789,         9986,         4802, 
           10256,         9150,         5123,         5299, 
            6989,         3746,          304,        12578, 
            4056,        18862,         5534,         8815, 
           17031,        52432,        28273,        14607, 
           11917,         3162,         9538,         8917, 
            3377,         3817,        36035,          650, 
             165,        20272,         1834,        10206, 
           26332,         4978,        15723,         8082, 
           12052,        15725,        27346,         1052, 
             543,        20027,        32169,        32063, 
           22132,         5248,        24199,         7288, 
           16313,         4234,         1995,        26470, 
            6321,         8649,         2217,        10271, 
            7486,         3918,        15386,        23144, 
           23840,         1009,         2820,        11075, 
             748,        47953,        10900,        29551, 
           16904,        19419,         3247,         3471, 
           11612,        12026,        24149,        41000, 
            5984,         5317,        16649,          236, 
           31902,         3217,        29280,           52, 
            3018,         5663,        23377,         1617, 
           21092,        24812,        22297,         2103, 
           11459,        14237,        26375,         6027, 
           18438,        38472,         1048,        19742, 
           14947,        15105,         2433,        12764, 
            2442,        11187,         2978,        28554, 
           20388,        24693,          294,        12112, 
           16859,        19709,        28761,         7282, 
            3219,        26785,         8025,         1534, 
           39507,        17110,        14532,         7695, 
           19443,        20891,        27798,         6009, 
            5604,        17202,         2076,         1915, 
           22714,        12425,        32021,         3210, 
           15550,         6632,         1524,        35835, 
            2731,        15178,        32040,        40898, 
}; 


// End of File
