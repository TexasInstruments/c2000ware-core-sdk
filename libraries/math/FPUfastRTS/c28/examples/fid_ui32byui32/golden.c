//#############################################################################
//! \file   golden.c
//! \brief  FID Ouput Vector (256) 
//! \author Vishal Coelho 
//! \date   24-Mar-2016
//! 
//
//  Group:          C2000
//  Target Family:  $DEVICE$
//
//#############################################################################
//
//
// $Copyright: Copyright (C) 2024 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################


#include <stdint.h>

const uint32_t test_quotient[256] = {
               2,            0,            1,            0, 
               1,            0,            0,            2, 
               1,            0,            0,            0, 
               6,            1,            1,            1, 
               1,            0,            0,          142, 
               2,            0,            1,            0, 
               0,            0,            0,            1, 
               0,            2,            0,            0, 
               0,            0,            0,            0, 
               1,           23,            0,            0, 
               1,            4,            0,            2, 
               0,            0,            1,            0, 
               0,            4,            0,            0, 
               1,            0,            0,            1, 
               0,            0,            0,            0, 
               2,            0,            0,            0, 
               0,            1,            2,            0, 
               0,            0,            1,            8, 
               1,            1,            0,            0, 
               1,            0,            0,            2, 
               4,            0,            0,            1, 
               1,            1,            2,           50, 
               3,            0,            0,            2, 
               3,            0,            2,            1, 
               0,            7,            0,            1, 
               0,            1,            1,            1, 
               0,            1,            0,            0, 
               0,            0,            0,            8, 
               1,            0,            1,            2, 
               0,            0,            1,            2, 
               0,            0,            2,            1, 
               0,            0,            1,            2, 
               1,            3,            0,          268, 
               3,            0,            1,            1, 
               0,            0,            1,            1, 
               0,           18,            0,            7, 
               3,            2,            1,            1, 
               0,            0,            1,            2, 
             420,            0,            0,           11, 
               1,            1,            0,           38, 
               1,            2,            0,            1, 
               0,            1,            0,            0, 
               1,            0,            0,            0, 
               0,            1,            0,            1, 
               1,            1,            0,            0, 
               0,            0,            1,            2, 
               0,            0,            1,            0, 
               0,            1,            0,            0, 
               1,            0,            0,            1, 
              80,            3,            1,            0, 
               3,            0,            0,            0, 
               0,            2,            0,            0, 
               2,            2,            1,            0, 
               4,           24,            0,            0, 
               1,            0,            0,            3, 
               1,            2,          173,            4, 
               1,            1,            1,           15, 
               1,            0,            0,            0, 
               0,            1,            0,            1, 
               0,            1,            0,            0, 
               1,            4,            0,            0, 
               2,            2,            0,           17, 
               0,            0,            0,           21, 
               1,            0,            1,            0, 
}; 

const uint32_t test_remainder[256] = {
        61008086,   2445881345,   1662063788,    621509392, 
       852961941,   1567126978,   3508235013,    730800427, 
       498608317,   2805008168,    855575791,    365831096, 
        47481158,   1175834114,   1886222702,    610291034, 
      1014860273,   2444075778,    236611111,      6649229, 
       418542353,   1893336265,    122435733,   1107433726, 
       660874951,    116385912,   1011213420,   1604955947, 
       243876905,    557929373,   1604167472,    857437080, 
      1315895005,    437956592,    925234654,   1422705240, 
      1287052238,     63966394,   1355790241,    332903134, 
       313905441,    235944837,   3177162200,   1252427397, 
        26638809,    693761611,   1143789079,    359043039, 
      1520217485,    126792286,    838481778,   1536549403, 
       251671608,    385087660,    534331382,    772413296, 
      2247014443,   1474215865,   2503740426,   1466577428, 
      1080530831,   3699902843,   1121805092,    154883906, 
      1581158931,    967544820,    466471132,   3001579581, 
      1289103679,   1073017241,   1077309038,     33202996, 
      1372728618,    804403183,    433115180,   2476601623, 
       818689117,   2897071698,   1228582357,    243651184, 
       654963828,    144152612,   3199534718,     77051050, 
       568490015,    408104125,    403325370,     34740258, 
       302527590,    407671731,   2718624191,    976015629, 
       120125526,   1111155474,    578837428,   1576890970, 
      3179912812,     87817663,   3655924207,   1134590928, 
       298524546,   1161042649,   1036038803,    580356965, 
      1396671284,    126969774,   1297789259,    906835871, 
       648788580,    427042936,    776635041,    235617924, 
       183424500,   3227065992,    540962520,    705248842, 
      1841794549,    982807906,    789941516,    282712211, 
      1235466678,    564858975,    198142434,    219590178, 
      1358687275,    272073801,   1255618397,    922375572, 
       244184877,    325447821,    832184427,      3368606, 
       129464118,   2317339585,     29958522,    586223180, 
        21108976,   1656834617,    542657386,   1558861967, 
      1123064298,    151492000,    226805188,       357934, 
       202644054,    267737879,    474166345,    144747727, 
      1582415544,   3121265634,    939488791,    657112621, 
         6322022,   2515810539,   1404874891,     32424548, 
      1055636431,     17462217,    891890890,     24617067, 
       643113472,    292196110,   1650449686,   2048263951, 
      2228286574,    684189845,   1111364150,   4141883776, 
        48959027,    690745700,    317686765,    876412906, 
      2332394837,    347588335,   1221762487,    237509467, 
       481999002,   1077809056,    319533296,   1905751565, 
      2967811852,    282833223,    679313827,    441758991, 
        76389638,   3294486002,   1156057177,     81437221, 
      1464717674,    360999712,    618420702,     61591107, 
       954880180,   2665984803,   2575622513,    402219423, 
        29537027,    171388691,   1515279783,     18020908, 
       469491188,   1484176790,   1319949004,   1269093043, 
      1069877529,    157176833,   1079993142,   1738123948, 
       354914182,     23580556,    425733363,   2320029382, 
        34287353,    127638854,   1380907916,    214742914, 
        29423519,    315431484,   2588531266,    495983480, 
      1689892968,    138525684,      2728429,    335997089, 
       865163260,    102225836,    172160883,     78023992, 
       174748368,   1652535779,   1103792784,   2219230557, 
      2061015850,    372351695,    374397914,    162205892, 
       800193748,    240351302,   1308671851,   2391568731, 
       207818239,    304484804,   1765259745,    281711753, 
       298947502,     83868507,    243021541,    193830548, 
       414895530,    786441513,    274969153,     50346872, 
      1079776566,   1310830228,    240572166,    959881198, 
}; 


// End of File
