#if defined(__C29__) || defined(__TMS320C2000__)
    #include "device.h"
#else
    #include <stdint.h>
#endif

// //////////////////////////////////////////////////////////////////////////////////////////////////////
// 1. Please uncomment one (and only one) of the below sets at a time. (Remove /* and */ only)
// 2. Do not uncomment random lines from random sets. It will not serve your purpose
// //////////////////////////////////////////////////////////////////////////////////////////////////////

// SET 0
//(Index: 2619): ADC Data
float raw_input_test[10]= { 2.268508, 0.740996, 2.478352, 1.197120, 1.239631, 0.937242, 2.512989, 0.328744, 1.197023, 1.920796, } ;

//(Index: 2619): Extracted Features
float model_test_input[10] = { 2.26851, 0.74100, 2.47835, 1.19712, 1.23963, 0.93724, 2.51299, 0.32874, 1.19702, 1.92080, } ;

//(Index: 2619): Expected Model Output
float golden_output[1] = { 1.134732, } ;


/*
// SET 1
//(Index: 456): ADC Data
float raw_input_test[10]= { 2.454172, 0.649880, 0.175982, 0.566386, 1.778207, 1.140333, 2.200235, 2.926613, 2.458536, 0.207544, } ;

//(Index: 456): Extracted Features
float model_test_input[10] = { 2.45417, 0.64988, 0.17598, 0.56639, 1.77821, 1.14033, 2.20023, 2.92661, 2.45854, 0.20754, } ;

//(Index: 456): Expected Model Output
float golden_output[1] = { 0.863965, } ;
*/

/*
// SET 2
//(Index: 102): ADC Data
float raw_input_test[10]= { 0.466449, 0.383900, 1.450203, 1.269037, 1.181441, 1.097969, 0.313072, 2.431673, 1.284295, 2.786176, } ;

//(Index: 102): Extracted Features
float model_test_input[10] = { 0.46645, 0.38390, 1.45020, 1.26904, 1.18144, 1.09797, 0.31307, 2.43167, 1.28429, 2.78618, } ;

//(Index: 102): Expected Model Output
float golden_output[1] = { 1.647627, } ;
*/

/*
// SET 3
//(Index: 3037): ADC Data
float raw_input_test[10]= { 0.348680, 0.748005, 0.149836, 1.068083, 1.760075, 0.604553, 0.354770, 0.168132, 1.220811, 0.628943, } ;

//(Index: 3037): Extracted Features
float model_test_input[10] = { 0.34868, 0.74801, 0.14984, 1.06808, 1.76007, 0.60455, 0.35477, 0.16813, 1.22081, 0.62894, } ;

//(Index: 3037): Expected Model Output
float golden_output[1] = { 2.742673, } ;
*/

/*
// SET 4
//(Index: 1126): ADC Data
float raw_input_test[10]= { 1.542563, 1.328236, 1.472885, 2.542411, 1.550190, 1.794747, 0.325305, 1.058457, 2.400592, 1.593871, } ;

//(Index: 1126): Extracted Features
float model_test_input[10] = { 1.54256, 1.32824, 1.47288, 2.54241, 1.55019, 1.79475, 0.32531, 1.05846, 2.40059, 1.59387, } ;

//(Index: 1126): Expected Model Output
float golden_output[1] = { 1.033639, } ;
*/

/*
// SET 5
//(Index: 1003): ADC Data
float raw_input_test[10]= { 2.155676, 1.051035, 2.801803, 0.855812, 2.179436, 1.711399, 2.332776, 1.727931, 2.745307, 2.510792, } ;

//(Index: 1003): Extracted Features
float model_test_input[10] = { 2.15568, 1.05104, 2.80180, 0.85581, 2.17944, 1.71140, 2.33278, 1.72793, 2.74531, 2.51079, } ;

//(Index: 1003): Expected Model Output
float golden_output[1] = { -0.105175, } ;
*/

/*
// SET 6
//(Index: 914): ADC Data
float raw_input_test[10]= { 0.410359, 1.091822, 2.379650, 0.886692, 1.864700, 2.545810, 2.063801, 2.824835, 0.089325, 2.502234, } ;

//(Index: 914): Extracted Features
float model_test_input[10] = { 0.41036, 1.09182, 2.37965, 0.88669, 1.86470, 2.54581, 2.06380, 2.82483, 0.08932, 2.50223, } ;

//(Index: 914): Expected Model Output
float golden_output[1] = { 0.525494, } ;
*/

/*
// SET 7
//(Index: 571): ADC Data
float raw_input_test[10]= { 2.782494, 1.224285, 0.384724, 2.687905, 1.741697, 1.193098, 0.208807, 1.022724, 1.714534, 2.519640, } ;

//(Index: 571): Extracted Features
float model_test_input[10] = { 2.78249, 1.22429, 0.38472, 2.68791, 1.74170, 1.19310, 0.20881, 1.02272, 1.71453, 2.51964, } ;

//(Index: 571): Expected Model Output
float golden_output[1] = { 0.961451, } ;
*/
