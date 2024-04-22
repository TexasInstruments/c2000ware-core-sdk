;******************************************************************************
;******************************************************************************
; 
; FILE: viterbi_data.asm
; 
; DESCRIPTION: Input test data for the Viterbi decoder
; 
;******************************************************************************
;
;
;  $Copyright: Copyright (C) 2024 Texas Instruments Incorporated -
;              http://www.ti.com/ ALL RIGHTS RESERVED $
;******************************************************************************
;  This software is licensed for use with Texas Instruments C28x
;  family DSCs.  This license was provided to you prior to installing
;  the software.  You may review this license by consulting a copy of
;  the agreement in the doc directory of this library.
; ------------------------------------------------------------------------
;******************************************************************************
        .cdecls   C,LIST,"vcu0_viterbi_decoder.h"
;############################################################################
;
;/*! \page VITERBI_DATA (Input test data to the Viterbi decoder)
;
; This file lists a test input to the viterbi decoder and the 
; results for each stage of the decoding are embedded in the comments
; This is useful for debugging purposes 
;*/
;############################################################################

        .sect .econst
;-----------------------------------------------------
_VIT_frame_len     .word    0x006a     ; Frame size before encoding
_VIT_coded_len     .word    0x00d4     ; Coded size
_VIT_encoder_len   .word    0x0007     ; Encoder length (K)
_VIT_states        .word    0x0040     ; For K=7, the viterbi decode has got 2(K-1) states. 2^6 = 64
                                       ;
_VIT_in_data:                          ;
      .word    0     ; BIT[  0]
      .word    0     ; BIT[  1]
      .word    1     ; BIT[  2]
      .word    0     ; BIT[  3]
      .word    0     ; BIT[  4]
      .word    1     ; BIT[  5]
      .word    0     ; BIT[  6]
      .word    0     ; BIT[  7]
      .word    0     ; BIT[  8]
      .word    1     ; BIT[  9]
      .word    1     ; BIT[ 10]
      .word    0     ; BIT[ 11]
      .word    1     ; BIT[ 12]
      .word    0     ; BIT[ 13]
      .word    0     ; BIT[ 14]
      .word    0     ; BIT[ 15]
      .word    1     ; BIT[ 16]
      .word    0     ; BIT[ 17]
      .word    1     ; BIT[ 18]
      .word    0     ; BIT[ 19]
      .word    0     ; BIT[ 20]
      .word    0     ; BIT[ 21]
      .word    1     ; BIT[ 22]
      .word    1     ; BIT[ 23]
      .word    0     ; BIT[ 24]
      .word    1     ; BIT[ 25]
      .word    1     ; BIT[ 26]
      .word    0     ; BIT[ 27]
      .word    0     ; BIT[ 28]
      .word    0     ; BIT[ 29]
      .word    0     ; BIT[ 30]
      .word    1     ; BIT[ 31]
      .word    1     ; BIT[ 32]
      .word    1     ; BIT[ 33]
      .word    0     ; BIT[ 34]
      .word    1     ; BIT[ 35]
      .word    1     ; BIT[ 36]
      .word    0     ; BIT[ 37]
      .word    1     ; BIT[ 38]
      .word    1     ; BIT[ 39]
      .word    1     ; BIT[ 40]
      .word    1     ; BIT[ 41]
      .word    0     ; BIT[ 42]
      .word    0     ; BIT[ 43]
      .word    1     ; BIT[ 44]
      .word    0     ; BIT[ 45]
      .word    0     ; BIT[ 46]
      .word    0     ; BIT[ 47]
      .word    1     ; BIT[ 48]
      .word    0     ; BIT[ 49]
      .word    0     ; BIT[ 50]
      .word    0     ; BIT[ 51]
      .word    1     ; BIT[ 52]
      .word    1     ; BIT[ 53]
      .word    0     ; BIT[ 54]
      .word    1     ; BIT[ 55]
      .word    0     ; BIT[ 56]
      .word    1     ; BIT[ 57]
      .word    1     ; BIT[ 58]
      .word    1     ; BIT[ 59]
      .word    1     ; BIT[ 60]
      .word    1     ; BIT[ 61]
      .word    0     ; BIT[ 62]
      .word    1     ; BIT[ 63]
      .word    0     ; BIT[ 64]
      .word    1     ; BIT[ 65]
      .word    1     ; BIT[ 66]
      .word    1     ; BIT[ 67]
      .word    0     ; BIT[ 68]
      .word    0     ; BIT[ 69]
      .word    1     ; BIT[ 70]
      .word    0     ; BIT[ 71]
      .word    0     ; BIT[ 72]
      .word    0     ; BIT[ 73]
      .word    0     ; BIT[ 74]
      .word    1     ; BIT[ 75]
      .word    0     ; BIT[ 76]
      .word    1     ; BIT[ 77]
      .word    0     ; BIT[ 78]
      .word    1     ; BIT[ 79]
      .word    1     ; BIT[ 80]
      .word    0     ; BIT[ 81]
      .word    0     ; BIT[ 82]
      .word    0     ; BIT[ 83]
      .word    0     ; BIT[ 84]
      .word    1     ; BIT[ 85]
      .word    1     ; BIT[ 86]
      .word    0     ; BIT[ 87]
      .word    0     ; BIT[ 88]
      .word    0     ; BIT[ 89]
      .word    0     ; BIT[ 90]
      .word    0     ; BIT[ 91]
      .word    1     ; BIT[ 92]
      .word    1     ; BIT[ 93]
      .word    0     ; BIT[ 94]
      .word    0     ; BIT[ 95]
      .word    0     ; BIT[ 96]
      .word    0     ; BIT[ 97]
      .word    1     ; BIT[ 98]
      .word    1     ; BIT[ 99]
      .word    0      ; BIT[  0] - terminating zero
      .word    0      ; BIT[  1] - terminating zero
      .word    0      ; BIT[  2] - terminating zero
      .word    0      ; BIT[  3] - terminating zero
      .word    0      ; BIT[  4] - terminating zero
      .word    0      ; BIT[  5] - terminating zero
;-----------------------------------------------------
;_VIT_encoded_data:                          ;
;      .word    0     ; BIT[  0]
;      .word    0     ; BIT[  1]
;      .word    0     ; BIT[  2]
;      .word    0     ; BIT[  3]
;      .word    1     ; BIT[  4]
;      .word    1     ; BIT[  5]
;      .word    1     ; BIT[  6]
;      .word    0     ; BIT[  7]
;      .word    1     ; BIT[  8]
;      .word    1     ; BIT[  9]
;      .word    0     ; BIT[ 10]
;      .word    0     ; BIT[ 11]
;      .word    1     ; BIT[ 12]
;      .word    0     ; BIT[ 13]
;      .word    1     ; BIT[ 14]
;      .word    0     ; BIT[ 15]
;      .word    0     ; BIT[ 16]
;      .word    0     ; BIT[ 17]
;      .word    1     ; BIT[ 18]
;      .word    1     ; BIT[ 19]
;      .word    0     ; BIT[ 20]
;      .word    0     ; BIT[ 21]
;      .word    1     ; BIT[ 22]
;      .word    0     ; BIT[ 23]
;      .word    1     ; BIT[ 24]
;      .word    1     ; BIT[ 25]
;      .word    0     ; BIT[ 26]
;      .word    1     ; BIT[ 27]
;      .word    1     ; BIT[ 28]
;      .word    0     ; BIT[ 29]
;      .word    0     ; BIT[ 30]
;      .word    1     ; BIT[ 31]
;      .word    0     ; BIT[ 32]
;      .word    0     ; BIT[ 33]
;      .word    1     ; BIT[ 34]
;      .word    1     ; BIT[ 35]
;      .word    1     ; BIT[ 36]
;      .word    1     ; BIT[ 37]
;      .word    0     ; BIT[ 38]
;      .word    1     ; BIT[ 39]
;      .word    1     ; BIT[ 40]
;      .word    1     ; BIT[ 41]
;      .word    1     ; BIT[ 42]
;      .word    0     ; BIT[ 43]
;      .word    0     ; BIT[ 44]
;      .word    0     ; BIT[ 45]
;      .word    0     ; BIT[ 46]
;      .word    0     ; BIT[ 47]
;      .word    1     ; BIT[ 48]
;      .word    0     ; BIT[ 49]
;      .word    1     ; BIT[ 50]
;      .word    1     ; BIT[ 51]
;      .word    1     ; BIT[ 52]
;      .word    0     ; BIT[ 53]
;      .word    0     ; BIT[ 54]
;      .word    0     ; BIT[ 55]
;      .word    1     ; BIT[ 56]
;      .word    0     ; BIT[ 57]
;      .word    0     ; BIT[ 58]
;      .word    0     ; BIT[ 59]
;      .word    0     ; BIT[ 60]
;      .word    1     ; BIT[ 61]
;      .word    0     ; BIT[ 62]
;      .word    1     ; BIT[ 63]
;      .word    1     ; BIT[ 64]
;      .word    0     ; BIT[ 65]
;      .word    1     ; BIT[ 66]
;      .word    0     ; BIT[ 67]
;      .word    1     ; BIT[ 68]
;      .word    0     ; BIT[ 69]
;      .word    1     ; BIT[ 70]
;      .word    1     ; BIT[ 71]
;      .word    1     ; BIT[ 72]
;      .word    1     ; BIT[ 73]
;      .word    1     ; BIT[ 74]
;      .word    1     ; BIT[ 75]
;      .word    0     ; BIT[ 76]
;      .word    1     ; BIT[ 77]
;      .word    0     ; BIT[ 78]
;      .word    1     ; BIT[ 79]
;      .word    1     ; BIT[ 80]
;      .word    1     ; BIT[ 81]
;      .word    1     ; BIT[ 82]
;      .word    1     ; BIT[ 83]
;      .word    0     ; BIT[ 84]
;      .word    1     ; BIT[ 85]
;      .word    0     ; BIT[ 86]
;      .word    1     ; BIT[ 87]
;      .word    1     ; BIT[ 88]
;      .word    0     ; BIT[ 89]
;      .word    0     ; BIT[ 90]
;      .word    0     ; BIT[ 91]
;      .word    0     ; BIT[ 92]
;      .word    1     ; BIT[ 93]
;      .word    0     ; BIT[ 94]
;      .word    0     ; BIT[ 95]
;      .word    1     ; BIT[ 96]
;      .word    1     ; BIT[ 97]
;      .word    1     ; BIT[ 98]
;      .word    1     ; BIT[ 99]
;      .word    0     ; BIT[100]
;      .word    0     ; BIT[101]
;      .word    1     ; BIT[102]
;      .word    1     ; BIT[103]
;      .word    1     ; BIT[104]
;      .word    1     ; BIT[105]
;      .word    0     ; BIT[106]
;      .word    0     ; BIT[107]
;      .word    1     ; BIT[108]
;      .word    0     ; BIT[109]
;      .word    1     ; BIT[110]
;      .word    1     ; BIT[111]
;      .word    0     ; BIT[112]
;      .word    1     ; BIT[113]
;      .word    0     ; BIT[114]
;      .word    1     ; BIT[115]
;      .word    0     ; BIT[116]
;      .word    0     ; BIT[117]
;      .word    0     ; BIT[118]
;      .word    1     ; BIT[119]
;      .word    0     ; BIT[120]
;      .word    0     ; BIT[121]
;      .word    1     ; BIT[122]
;      .word    0     ; BIT[123]
;      .word    1     ; BIT[124]
;      .word    1     ; BIT[125]
;      .word    0     ; BIT[126]
;      .word    1     ; BIT[127]
;      .word    1     ; BIT[128]
;      .word    1     ; BIT[129]
;      .word    1     ; BIT[130]
;      .word    0     ; BIT[131]
;      .word    0     ; BIT[132]
;      .word    0     ; BIT[133]
;      .word    0     ; BIT[134]
;      .word    1     ; BIT[135]
;      .word    1     ; BIT[136]
;      .word    1     ; BIT[137]
;      .word    1     ; BIT[138]
;      .word    1     ; BIT[139]
;      .word    0     ; BIT[140]
;      .word    1     ; BIT[141]
;      .word    0     ; BIT[142]
;      .word    0     ; BIT[143]
;      .word    0     ; BIT[144]
;      .word    1     ; BIT[145]
;      .word    0     ; BIT[146]
;      .word    0     ; BIT[147]
;      .word    0     ; BIT[148]
;      .word    0     ; BIT[149]
;      .word    1     ; BIT[150]
;      .word    0     ; BIT[151]
;      .word    0     ; BIT[152]
;      .word    1     ; BIT[153]
;      .word    0     ; BIT[154]
;      .word    0     ; BIT[155]
;      .word    0     ; BIT[156]
;      .word    1     ; BIT[157]
;      .word    0     ; BIT[158]
;      .word    0     ; BIT[159]
;      .word    1     ; BIT[160]
;      .word    1     ; BIT[161]
;      .word    1     ; BIT[162]
;      .word    0     ; BIT[163]
;      .word    0     ; BIT[164]
;      .word    1     ; BIT[165]
;      .word    0     ; BIT[166]
;      .word    0     ; BIT[167]
;      .word    0     ; BIT[168]
;      .word    1     ; BIT[169]
;      .word    0     ; BIT[170]
;      .word    1     ; BIT[171]
;      .word    1     ; BIT[172]
;      .word    0     ; BIT[173]
;      .word    0     ; BIT[174]
;      .word    1     ; BIT[175]
;      .word    0     ; BIT[176]
;      .word    0     ; BIT[177]
;      .word    1     ; BIT[178]
;      .word    1     ; BIT[179]
;      .word    0     ; BIT[180]
;      .word    1     ; BIT[181]
;      .word    1     ; BIT[182]
;      .word    0     ; BIT[183]
;      .word    0     ; BIT[184]
;      .word    0     ; BIT[185]
;      .word    0     ; BIT[186]
;      .word    1     ; BIT[187]
;      .word    0     ; BIT[188]
;      .word    1     ; BIT[189]
;      .word    0     ; BIT[190]
;      .word    0     ; BIT[191]
;      .word    1     ; BIT[192]
;      .word    1     ; BIT[193]
;      .word    0     ; BIT[194]
;      .word    1     ; BIT[195]
;      .word    0     ; BIT[196]
;      .word    1     ; BIT[197]
;      .word    1     ; BIT[198]
;      .word    0     ; BIT[199]
;      .word    0     ; BIT[200]
;      .word    1     ; BIT[201]
;      .word    0     ; BIT[202]
;      .word    0     ; BIT[203]
;      .word    1     ; BIT[204]
;      .word    1     ; BIT[205]
;      .word    0     ; BIT[206]
;      .word    1     ; BIT[207]
;      .word    1     ; BIT[208]
;      .word    0     ; BIT[209]
;      .word    1     ; BIT[210]
;      .word    1     ; BIT[211]
;-----------------------------------------------------
      .if __TI_EABI__
	  .asg VIT_quant_data,_VIT_quant_data
	  .endif
_VIT_quant_data:                          ;
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    32 
       .word    -32 
       .word    -32 
       .word    -32 


;-----------------------------------------------------
        .sect .econst
        .align 2
_VIT_gold_vt_data:                          ;
      .long    0x755faffa     ;T1: k = 0
      .long    0x5ff5faaf     ;T0: k = 0
      .long    0x205f05fa     ;T1: k = 1
      .long    0x0af550af     ;T0: k = 1
      .long    0x5a255a25     ;T1: k = 2
      .long    0x255a255a     ;T0: k = 2
      .long    0x25522552     ;T1: k = 3
      .long    0x52255225     ;T0: k = 3
      .long    0x14145005     ;T1: k = 4
      .long    0x10150550     ;T0: k = 4
      .long    0x00000000     ;T1: k = 5
      .long    0x00000000     ;T0: k = 5
      .long    0x1c58c049     ;T1: k = 6
      .long    0x581c49c0     ;T0: k = 6
      .long    0xa59aa59a     ;T1: k = 7
      .long    0x52a71aa5     ;T0: k = 7
      .long    0xfd1acfda     ;T1: k = 8
      .long    0x5bb1daaf     ;T0: k = 8
      .long    0x8cf4948f     ;T1: k = 9
      .long    0x849e84d4     ;T0: k = 9
      .long    0x258fa50a     ;T1: k = 10
      .long    0x02ad108f     ;T0: k = 10
      .long    0xa5dee5da     ;T1: k = 11
      .long    0x5a85da85     ;T0: k = 11
      .long    0x07b07003     ;T1: k = 12
      .long    0xf2070772     ;T0: k = 12
      .long    0x500708b5     ;T1: k = 13
      .long    0x0550a00f     ;T0: k = 13
      .long    0x8fc0b408     ;T1: k = 14
      .long    0xfe031e60     ;T0: k = 14
      .long    0xf08f4ff0     ;T1: k = 15
      .long    0x0fd2f51f     ;T0: k = 15
      .long    0xa55ae558     ;T1: k = 16
      .long    0x7b257aa5     ;T0: k = 16
      .long    0x1ab41225     ;T1: k = 17
      .long    0xb01a3770     ;T0: k = 17
      .long    0xd29792df     ;T1: k = 18
      .long    0xa1df83db     ;T0: k = 18
      .long    0x469872a5     ;T1: k = 19
      .long    0xe6182758     ;T0: k = 19
      .long    0x5884508d     ;T1: k = 20
      .long    0xc04e0458     ;T0: k = 20
      .long    0xa15ba01a     ;T1: k = 21
      .long    0x0aa93ab1     ;T0: k = 21
      .long    0xf2afaff2     ;T1: k = 22
      .long    0x2ff4f28f     ;T0: k = 22
      .long    0xa00e04e0     ;T1: k = 23
      .long    0x03a29007     ;T0: k = 23
      .long    0x85fce48d     ;T1: k = 24
      .long    0xf08d4cf1     ;T0: k = 24
      .long    0x87949697     ;T1: k = 25
      .long    0x86168696     ;T0: k = 25
      .long    0x0d78ad5d     ;T1: k = 26
      .long    0x59ad09fd     ;T0: k = 26
      .long    0xa24ecec0     ;T1: k = 27
      .long    0x0ec0da8d     ;T0: k = 27
      .long    0x07feb14e     ;T1: k = 28
      .long    0x53fe1bf4     ;T0: k = 28
      .long    0xf20ffff8     ;T1: k = 29
      .long    0x0ff8fa8f     ;T0: k = 29
      .long    0x42a508a1     ;T1: k = 30
      .long    0x85d8a04a     ;T0: k = 30
      .long    0xda475ef5     ;T1: k = 31
      .long    0xef52f55f     ;T0: k = 31
      .long    0x9f92f7ca     ;T1: k = 32
      .long    0xda87df84     ;T0: k = 32
      .long    0x4920602b     ;T1: k = 33
      .long    0x48274970     ;T0: k = 33
      .long    0xa51385f2     ;T1: k = 34
      .long    0x87a3d0a7     ;T0: k = 34
      .long    0x58a55085     ;T1: k = 35
      .long    0xa51805d8     ;T0: k = 35
      .long    0x0a800206     ;T1: k = 36
      .long    0xa00a0612     ;T0: k = 36
      .long    0x5af55abd     ;T1: k = 37
      .long    0xe5dfe55b     ;T0: k = 37
      .long    0xfc9d87d5     ;T1: k = 38
      .long    0x9db4f1cf     ;T0: k = 38
      .long    0xf2074eb0     ;T1: k = 39
      .long    0xa652e61a     ;T0: k = 39
      .long    0xa7f0f00d     ;T1: k = 40
      .long    0xf0051fa4     ;T0: k = 40
      .long    0x5ef4f887     ;T1: k = 41
      .long    0xb55ea556     ;T0: k = 41
      .long    0x7aaf0bb6     ;T1: k = 42
      .long    0xaf7aa1de     ;T0: k = 42
      .long    0xf88d1fe4     ;T1: k = 43
      .long    0x8fd0b14e     ;T0: k = 43
      .long    0xed08ed48     ;T1: k = 44
      .long    0xff25ff85     ;T0: k = 44
      .long    0xddc8377a     ;T1: k = 45
      .long    0xdecc1bb1     ;T0: k = 45
      .long    0xd2434bf3     ;T1: k = 46
      .long    0x87f2e15f     ;T0: k = 46
      .long    0xbd1aad5a     ;T1: k = 47
      .long    0x5aa5daa5     ;T0: k = 47
      .long    0x0bd0510d     ;T1: k = 48
      .long    0xc01f05f5     ;T0: k = 48
      .long    0x0bf0b00f     ;T1: k = 49
      .long    0xb00e0ff2     ;T0: k = 49
      .long    0xa49b85d2     ;T1: k = 50
      .long    0x0eb1d8a7     ;T0: k = 50
      .long    0x02b552a7     ;T1: k = 51
      .long    0xa01f07f3     ;T0: k = 51
      .long    0x0294108f     ;T1: k = 52
      .long    0x908f01b3     ;T0: k = 52
      .long    0xb00b177a     ;T1: k = 53
      .long    0x1aa1122f     ;T0: k = 53
      .long    0xa5dbe5db     ;T1: k = 54
      .long    0xdacdcaa5     ;T0: k = 54
      .long    0x13855a00     ;T1: k = 55
      .long    0xb512e552     ;T0: k = 55
      .long    0x500519e5     ;T1: k = 56
      .long    0x11523548     ;T0: k = 56
      .long    0xc0854da0     ;T1: k = 57
      .long    0x85c0e508     ;T0: k = 57
      .long    0xedcfed5c     ;T1: k = 58
      .long    0xcfa5fce5     ;T0: k = 58
      .long    0xe7e76f6f     ;T1: k = 59
      .long    0xa7f6ef6f     ;T0: k = 59
      .long    0x70090b59     ;T1: k = 60
      .long    0x0ab17009     ;T0: k = 60
      .long    0x3ff3b37f     ;T1: k = 61
      .long    0x7a3f3ff2     ;T0: k = 61
      .long    0x0a804204     ;T1: k = 62
      .long    0xa00a0750     ;T0: k = 62
      .long    0x716d577d     ;T1: k = 63
      .long    0x2579f57f     ;T0: k = 63
      .long    0x7bf1f97b     ;T1: k = 64
      .long    0xf90debf9     ;T0: k = 64
      .long    0x9fdad41f     ;T1: k = 65
      .long    0xdb9f5eb7     ;T0: k = 65
      .long    0xf41fbff4     ;T1: k = 66
      .long    0x5ef5f6af     ;T0: k = 66
      .long    0xfaff7bff     ;T1: k = 67
      .long    0xaffbbb7f     ;T0: k = 67
      .long    0x0eb0f003     ;T1: k = 68
      .long    0xf00b0f50     ;T0: k = 68
      .long    0x0ff2d2af     ;T1: k = 69
      .long    0xf01f0ff2     ;T0: k = 69
      .long    0x0c8f847f     ;T1: k = 70
      .long    0x58af04ff     ;T0: k = 70
      .long    0xb61eb6d6     ;T1: k = 71
      .long    0x1e94b69e     ;T0: k = 71
      .long    0xcb4f4be1     ;T1: k = 72
      .long    0xcfdae34f     ;T0: k = 72
      .long    0xfe8fafe9     ;T1: k = 73
      .long    0xdef8fc8f     ;T0: k = 73
      .long    0xc01f0570     ;T1: k = 74
      .long    0x4375d007     ;T0: k = 74
      .long    0x05d0900e     ;T1: k = 75
      .long    0x900707b0     ;T0: k = 75
      .long    0xd8858ea4     ;T1: k = 76
      .long    0x8dd8a50a     ;T0: k = 76
      .long    0xe508ad50     ;T1: k = 77
      .long    0x5b205a05     ;T0: k = 77
      .long    0x96de17b3     ;T1: k = 78
      .long    0x16dc9313     ;T0: k = 78
      .long    0xf04b07d0     ;T1: k = 79
      .long    0x0bc0528f     ;T0: k = 79
      .long    0x0ff2f00b     ;T1: k = 80
      .long    0x706f0bf2     ;T0: k = 80
      .long    0xaffae3be     ;T1: k = 81
      .long    0xfaaf4bb4     ;T0: k = 81
      .long    0x6a010a29     ;T1: k = 82
      .long    0xa802a028     ;T0: k = 82
      .long    0xa772f77a     ;T1: k = 83
      .long    0xd3e75ff7     ;T0: k = 83
      .long    0xeaa12aa4     ;T1: k = 84
      .long    0xa5eaac2a     ;T0: k = 84
      .long    0x7ffd7edf     ;T1: k = 85
      .long    0xef59ff5b     ;T0: k = 85
      .long    0xaffae54f     ;T1: k = 86
      .long    0xfaafcff5     ;T0: k = 86
      .long    0x5a015a20     ;T1: k = 87
      .long    0x0352b018     ;T0: k = 87
      .long    0xa343a52a     ;T1: k = 88
      .long    0x5ba37a25     ;T0: k = 88
      .long    0x69e170a5     ;T1: k = 89
      .long    0xe14925e1     ;T0: k = 89
      .long    0x4aa54aa5     ;T1: k = 90
      .long    0xa55ae44f     ;T0: k = 90
      .long    0xcff0f60f     ;T1: k = 91
      .long    0xfc0faff0     ;T0: k = 91
      .long    0xa06f8c76     ;T1: k = 92
      .long    0x8ef5d83f     ;T0: k = 92
      .long    0x583742b5     ;T1: k = 93
      .long    0x2912611e     ;T0: k = 93
      .long    0x70255e25     ;T1: k = 94
      .long    0x2558a55a     ;T0: k = 94
      .long    0xb700f510     ;T1: k = 95
      .long    0xf7055f10     ;T0: k = 95
      .long    0x8cf0b803     ;T1: k = 96
      .long    0xf8030cf0     ;T0: k = 96
      .long    0x4aa5daa5     ;T1: k = 97
      .long    0xa54a855a     ;T0: k = 97
      .long    0x702f0eb5     ;T1: k = 98
      .long    0x0cf2f00f     ;T0: k = 98
      .long    0xafdaf71a     ;T1: k = 99
      .long    0xfe87ffb3     ;T0: k = 99
      .long    0xd0441e30     ;T1: k = 100
      .long    0x0440b016     ;T0: k = 100
      .long    0xb43b3539     ;T1: k = 101
      .long    0x1eb13835     ;T0: k = 101
      .long    0x0ff1f0ad     ;T1: k = 102
      .long    0xf05f8df0     ;T0: k = 102
      .long    0x68e31aaf     ;T1: k = 103
      .long    0x21fa204b     ;T0: k = 103
      .long    0x0ff0f11e     ;T1: k = 104
      .long    0xfa8d4bb4     ;T0: k = 104
      .long    0xffa0f783     ;T1: k = 105
      .long    0xf70ae7c2     ;T0: k = 105
;-----------------------------------------------------
;For debug of traceback
; === BIT[105] ===
;     T0 = 0xf70ae7c2     
;     T1 = 0xffa0f783     
;     S =  0
;     S < 32: use T0[31-S] = T0[31]
;     tran[105][  0]=1    next VR0 = 1
; === BIT[104] ===
;     T0 = 0xfa8d4bb4     
;     T1 = 0x0ff0f11e     
;     S =  1
;     S < 32: use T0[31-S] = T0[30]
;     tran[104][  1]=1    next VR0 = 3
; === BIT[103] ===
;     T0 = 0x21fa204b     
;     T1 = 0x68e31aaf     
;     S =  3
;     S < 32: use T0[31-S] = T0[28]
;     tran[103][  3]=0    next VR0 = 6
; === BIT[102] ===
;     T0 = 0xf05f8df0     
;     T1 = 0x0ff1f0ad     
;     S =  6
;     S < 32: use T0[31-S] = T0[25]
;     tran[102][  6]=0    next VR0 = 12
; === BIT[101] ===
;     T0 = 0x1eb13835     
;     T1 = 0xb43b3539     
;     S = 12
;     S < 32: use T0[31-S] = T0[19]
;     tran[101][ 12]=0    next VR0 = 24
; === BIT[100] ===
;     T0 = 0x0440b016     
;     T1 = 0xd0441e30     
;     S = 24
;     S < 32: use T0[31-S] = T0[ 7]
;     tran[100][ 24]=0    next VR0 = 48
; === BIT[ 99] ===
;     T0 = 0xfe87ffb3     
;     T1 = 0xafdaf71a     
;     S = 48
;     S >= 32: use T1[63-S] = T1[15]
;     tran[ 99][ 48]=1    next VR0 = 33
; === BIT[ 98] ===
;     T0 = 0x0cf2f00f     
;     T1 = 0x702f0eb5     
;     S = 33
;     S >= 32: use T1[63-S] = T1[30]
;     tran[ 98][ 33]=1    next VR0 = 3
; === BIT[ 97] ===
;     T0 = 0xa54a855a     
;     T1 = 0x4aa5daa5     
;     S =  3
;     S < 32: use T0[31-S] = T0[28]
;     tran[ 97][  3]=0    next VR0 = 6
; === BIT[ 96] ===
;     T0 = 0xf8030cf0     
;     T1 = 0x8cf0b803     
;     S =  6
;     S < 32: use T0[31-S] = T0[25]
;     tran[ 96][  6]=0    next VR0 = 12
; === BIT[ 95] ===
;     T0 = 0xf7055f10     
;     T1 = 0xb700f510     
;     S = 12
;     S < 32: use T0[31-S] = T0[19]
;     tran[ 95][ 12]=0    next VR0 = 24
; === BIT[ 94] ===
;     T0 = 0x2558a55a     
;     T1 = 0x70255e25     
;     S = 24
;     S < 32: use T0[31-S] = T0[ 7]
;     tran[ 94][ 24]=0    next VR0 = 48
; === BIT[ 93] ===
;     T0 = 0x2912611e     
;     T1 = 0x583742b5     
;     S = 48
;     S >= 32: use T1[63-S] = T1[15]
;     tran[ 93][ 48]=0    next VR0 = 32
; === BIT[ 92] ===
;     T0 = 0x8ef5d83f     
;     T1 = 0xa06f8c76     
;     S = 32
;     S >= 32: use T1[63-S] = T1[31]
;     tran[ 92][ 32]=1    next VR0 = 1
; === BIT[ 91] ===
;     T0 = 0xfc0faff0     
;     T1 = 0xcff0f60f     
;     S =  1
;     S < 32: use T0[31-S] = T0[30]
;     tran[ 91][  1]=1    next VR0 = 3
; === BIT[ 90] ===
;     T0 = 0xa55ae44f     
;     T1 = 0x4aa54aa5     
;     S =  3
;     S < 32: use T0[31-S] = T0[28]
;     tran[ 90][  3]=0    next VR0 = 6
; === BIT[ 89] ===
;     T0 = 0xe14925e1     
;     T1 = 0x69e170a5     
;     S =  6
;     S < 32: use T0[31-S] = T0[25]
;     tran[ 89][  6]=0    next VR0 = 12
; === BIT[ 88] ===
;     T0 = 0x5ba37a25     
;     T1 = 0xa343a52a     
;     S = 12
;     S < 32: use T0[31-S] = T0[19]
;     tran[ 88][ 12]=0    next VR0 = 24
; === BIT[ 87] ===
;     T0 = 0x0352b018     
;     T1 = 0x5a015a20     
;     S = 24
;     S < 32: use T0[31-S] = T0[ 7]
;     tran[ 87][ 24]=0    next VR0 = 48
; === BIT[ 86] ===
;     T0 = 0xfaafcff5     
;     T1 = 0xaffae54f     
;     S = 48
;     S >= 32: use T1[63-S] = T1[15]
;     tran[ 86][ 48]=1    next VR0 = 33
; === BIT[ 85] ===
;     T0 = 0xef59ff5b     
;     T1 = 0x7ffd7edf     
;     S = 33
;     S >= 32: use T1[63-S] = T1[30]
;     tran[ 85][ 33]=1    next VR0 = 3
; === BIT[ 84] ===
;     T0 = 0xa5eaac2a     
;     T1 = 0xeaa12aa4     
;     S =  3
;     S < 32: use T0[31-S] = T0[28]
;     tran[ 84][  3]=0    next VR0 = 6
; === BIT[ 83] ===
;     T0 = 0xd3e75ff7     
;     T1 = 0xa772f77a     
;     S =  6
;     S < 32: use T0[31-S] = T0[25]
;     tran[ 83][  6]=1    next VR0 = 13
; === BIT[ 82] ===
;     T0 = 0xa802a028     
;     T1 = 0x6a010a29     
;     S = 13
;     S < 32: use T0[31-S] = T0[18]
;     tran[ 82][ 13]=0    next VR0 = 26
; === BIT[ 81] ===
;     T0 = 0xfaaf4bb4     
;     T1 = 0xaffae3be     
;     S = 26
;     S < 32: use T0[31-S] = T0[ 5]
;     tran[ 81][ 26]=1    next VR0 = 53
; === BIT[ 80] ===
;     T0 = 0x706f0bf2     
;     T1 = 0x0ff2f00b     
;     S = 53
;     S >= 32: use T1[63-S] = T1[10]
;     tran[ 80][ 53]=0    next VR0 = 42
; === BIT[ 79] ===
;     T0 = 0x0bc0528f     
;     T1 = 0xf04b07d0     
;     S = 42
;     S >= 32: use T1[63-S] = T1[21]
;     tran[ 79][ 42]=0    next VR0 = 20
; === BIT[ 78] ===
;     T0 = 0x16dc9313     
;     T1 = 0x96de17b3     
;     S = 20
;     S < 32: use T0[31-S] = T0[11]
;     tran[ 78][ 20]=0    next VR0 = 40
; === BIT[ 77] ===
;     T0 = 0x5b205a05     
;     T1 = 0xe508ad50     
;     S = 40
;     S >= 32: use T1[63-S] = T1[23]
;     tran[ 77][ 40]=0    next VR0 = 16
; === BIT[ 76] ===
;     T0 = 0x8dd8a50a     
;     T1 = 0xd8858ea4     
;     S = 16
;     S < 32: use T0[31-S] = T0[15]
;     tran[ 76][ 16]=1    next VR0 = 33
; === BIT[ 75] ===
;     T0 = 0x900707b0     
;     T1 = 0x05d0900e     
;     S = 33
;     S >= 32: use T1[63-S] = T1[30]
;     tran[ 75][ 33]=0    next VR0 = 2
; === BIT[ 74] ===
;     T0 = 0x4375d007     
;     T1 = 0xc01f0570     
;     S =  2
;     S < 32: use T0[31-S] = T0[29]
;     tran[ 74][  2]=0    next VR0 = 4
; === BIT[ 73] ===
;     T0 = 0xdef8fc8f     
;     T1 = 0xfe8fafe9     
;     S =  4
;     S < 32: use T0[31-S] = T0[27]
;     tran[ 73][  4]=1    next VR0 = 9
; === BIT[ 72] ===
;     T0 = 0xcfdae34f     
;     T1 = 0xcb4f4be1     
;     S =  9
;     S < 32: use T0[31-S] = T0[22]
;     tran[ 72][  9]=1    next VR0 = 19
; === BIT[ 71] ===
;     T0 = 0x1e94b69e     
;     T1 = 0xb61eb6d6     
;     S = 19
;     S < 32: use T0[31-S] = T0[12]
;     tran[ 71][ 19]=1    next VR0 = 39
; === BIT[ 70] ===
;     T0 = 0x58af04ff     
;     T1 = 0x0c8f847f     
;     S = 39
;     S >= 32: use T1[63-S] = T1[24]
;     tran[ 70][ 39]=0    next VR0 = 14
; === BIT[ 69] ===
;     T0 = 0xf01f0ff2     
;     T1 = 0x0ff2d2af     
;     S = 14
;     S < 32: use T0[31-S] = T0[17]
;     tran[ 69][ 14]=1    next VR0 = 29
; === BIT[ 68] ===
;     T0 = 0xf00b0f50     
;     T1 = 0x0eb0f003     
;     S = 29
;     S < 32: use T0[31-S] = T0[ 2]
;     tran[ 68][ 29]=0    next VR0 = 58
; === BIT[ 67] ===
;     T0 = 0xaffbbb7f     
;     T1 = 0xfaff7bff     
;     S = 58
;     S >= 32: use T1[63-S] = T1[ 5]
;     tran[ 67][ 58]=1    next VR0 = 53
; === BIT[ 66] ===
;     T0 = 0x5ef5f6af     
;     T1 = 0xf41fbff4     
;     S = 53
;     S >= 32: use T1[63-S] = T1[10]
;     tran[ 66][ 53]=1    next VR0 = 43
; === BIT[ 65] ===
;     T0 = 0xdb9f5eb7     
;     T1 = 0x9fdad41f     
;     S = 43
;     S >= 32: use T1[63-S] = T1[20]
;     tran[ 65][ 43]=1    next VR0 = 23
; === BIT[ 64] ===
;     T0 = 0xf90debf9     
;     T1 = 0x7bf1f97b     
;     S = 23
;     S < 32: use T0[31-S] = T0[ 8]
;     tran[ 64][ 23]=1    next VR0 = 47
; === BIT[ 63] ===
;     T0 = 0x2579f57f     
;     T1 = 0x716d577d     
;     S = 47
;     S >= 32: use T1[63-S] = T1[16]
;     tran[ 63][ 47]=1    next VR0 = 31
; === BIT[ 62] ===
;     T0 = 0xa00a0750     
;     T1 = 0x0a804204     
;     S = 31
;     S < 32: use T0[31-S] = T0[ 0]
;     tran[ 62][ 31]=0    next VR0 = 62
; === BIT[ 61] ===
;     T0 = 0x7a3f3ff2     
;     T1 = 0x3ff3b37f     
;     S = 62
;     S >= 32: use T1[63-S] = T1[ 1]
;     tran[ 61][ 62]=1    next VR0 = 61
; === BIT[ 60] ===
;     T0 = 0x0ab17009     
;     T1 = 0x70090b59     
;     S = 61
;     S >= 32: use T1[63-S] = T1[ 2]
;     tran[ 60][ 61]=0    next VR0 = 58
; === BIT[ 59] ===
;     T0 = 0xa7f6ef6f     
;     T1 = 0xe7e76f6f     
;     S = 58
;     S >= 32: use T1[63-S] = T1[ 5]
;     tran[ 59][ 58]=1    next VR0 = 53
; === BIT[ 58] ===
;     T0 = 0xcfa5fce5     
;     T1 = 0xedcfed5c     
;     S = 53
;     S >= 32: use T1[63-S] = T1[10]
;     tran[ 58][ 53]=1    next VR0 = 43
; === BIT[ 57] ===
;     T0 = 0x85c0e508     
;     T1 = 0xc0854da0     
;     S = 43
;     S >= 32: use T1[63-S] = T1[20]
;     tran[ 57][ 43]=0    next VR0 = 22
; === BIT[ 56] ===
;     T0 = 0x11523548     
;     T1 = 0x500519e5     
;     S = 22
;     S < 32: use T0[31-S] = T0[ 9]
;     tran[ 56][ 22]=0    next VR0 = 44
; === BIT[ 55] ===
;     T0 = 0xb512e552     
;     T1 = 0x13855a00     
;     S = 44
;     S >= 32: use T1[63-S] = T1[19]
;     tran[ 55][ 44]=0    next VR0 = 24
; === BIT[ 54] ===
;     T0 = 0xdacdcaa5     
;     T1 = 0xa5dbe5db     
;     S = 24
;     S < 32: use T0[31-S] = T0[ 7]
;     tran[ 54][ 24]=1    next VR0 = 49
; === BIT[ 53] ===
;     T0 = 0x1aa1122f     
;     T1 = 0xb00b177a     
;     S = 49
;     S >= 32: use T1[63-S] = T1[14]
;     tran[ 53][ 49]=0    next VR0 = 34
; === BIT[ 52] ===
;     T0 = 0x908f01b3     
;     T1 = 0x0294108f     
;     S = 34
;     S >= 32: use T1[63-S] = T1[29]
;     tran[ 52][ 34]=0    next VR0 = 4
; === BIT[ 51] ===
;     T0 = 0xa01f07f3     
;     T1 = 0x02b552a7     
;     S =  4
;     S < 32: use T0[31-S] = T0[27]
;     tran[ 51][  4]=0    next VR0 = 8
; === BIT[ 50] ===
;     T0 = 0x0eb1d8a7     
;     T1 = 0xa49b85d2     
;     S =  8
;     S < 32: use T0[31-S] = T0[23]
;     tran[ 50][  8]=1    next VR0 = 17
; === BIT[ 49] ===
;     T0 = 0xb00e0ff2     
;     T1 = 0x0bf0b00f     
;     S = 17
;     S < 32: use T0[31-S] = T0[14]
;     tran[ 49][ 17]=0    next VR0 = 34
; === BIT[ 48] ===
;     T0 = 0xc01f05f5     
;     T1 = 0x0bd0510d     
;     S = 34
;     S >= 32: use T1[63-S] = T1[29]
;     tran[ 48][ 34]=0    next VR0 = 4
; === BIT[ 47] ===
;     T0 = 0x5aa5daa5     
;     T1 = 0xbd1aad5a     
;     S =  4
;     S < 32: use T0[31-S] = T0[27]
;     tran[ 47][  4]=1    next VR0 = 9
; === BIT[ 46] ===
;     T0 = 0x87f2e15f     
;     T1 = 0xd2434bf3     
;     S =  9
;     S < 32: use T0[31-S] = T0[22]
;     tran[ 46][  9]=1    next VR0 = 19
; === BIT[ 45] ===
;     T0 = 0xdecc1bb1     
;     T1 = 0xddc8377a     
;     S = 19
;     S < 32: use T0[31-S] = T0[12]
;     tran[ 45][ 19]=1    next VR0 = 39
; === BIT[ 44] ===
;     T0 = 0xff25ff85     
;     T1 = 0xed08ed48     
;     S = 39
;     S >= 32: use T1[63-S] = T1[24]
;     tran[ 44][ 39]=1    next VR0 = 15
; === BIT[ 43] ===
;     T0 = 0x8fd0b14e     
;     T1 = 0xf88d1fe4     
;     S = 15
;     S < 32: use T0[31-S] = T0[16]
;     tran[ 43][ 15]=0    next VR0 = 30
; === BIT[ 42] ===
;     T0 = 0xaf7aa1de     
;     T1 = 0x7aaf0bb6     
;     S = 30
;     S < 32: use T0[31-S] = T0[ 1]
;     tran[ 42][ 30]=1    next VR0 = 61
; === BIT[ 41] ===
;     T0 = 0xb55ea556     
;     T1 = 0x5ef4f887     
;     S = 61
;     S >= 32: use T1[63-S] = T1[ 2]
;     tran[ 41][ 61]=1    next VR0 = 59
; === BIT[ 40] ===
;     T0 = 0xf0051fa4     
;     T1 = 0xa7f0f00d     
;     S = 59
;     S >= 32: use T1[63-S] = T1[ 4]
;     tran[ 40][ 59]=0    next VR0 = 54
; === BIT[ 39] ===
;     T0 = 0xa652e61a     
;     T1 = 0xf2074eb0     
;     S = 54
;     S >= 32: use T1[63-S] = T1[ 9]
;     tran[ 39][ 54]=1    next VR0 = 45
; === BIT[ 38] ===
;     T0 = 0x9db4f1cf     
;     T1 = 0xfc9d87d5     
;     S = 45
;     S >= 32: use T1[63-S] = T1[18]
;     tran[ 38][ 45]=1    next VR0 = 27
; === BIT[ 37] ===
;     T0 = 0xe5dfe55b     
;     T1 = 0x5af55abd     
;     S = 27
;     S < 32: use T0[31-S] = T0[ 4]
;     tran[ 37][ 27]=1    next VR0 = 55
; === BIT[ 36] ===
;     T0 = 0xa00a0612     
;     T1 = 0x0a800206     
;     S = 55
;     S >= 32: use T1[63-S] = T1[ 8]
;     tran[ 36][ 55]=0    next VR0 = 46
; === BIT[ 35] ===
;     T0 = 0xa51805d8     
;     T1 = 0x58a55085     
;     S = 46
;     S >= 32: use T1[63-S] = T1[17]
;     tran[ 35][ 46]=0    next VR0 = 28
; === BIT[ 34] ===
;     T0 = 0x87a3d0a7     
;     T1 = 0xa51385f2     
;     S = 28
;     S < 32: use T0[31-S] = T0[ 3]
;     tran[ 34][ 28]=0    next VR0 = 56
; === BIT[ 33] ===
;     T0 = 0x48274970     
;     T1 = 0x4920602b     
;     S = 56
;     S >= 32: use T1[63-S] = T1[ 7]
;     tran[ 33][ 56]=0    next VR0 = 48
; === BIT[ 32] ===
;     T0 = 0xda87df84     
;     T1 = 0x9f92f7ca     
;     S = 48
;     S >= 32: use T1[63-S] = T1[15]
;     tran[ 32][ 48]=1    next VR0 = 33
; === BIT[ 31] ===
;     T0 = 0xef52f55f     
;     T1 = 0xda475ef5     
;     S = 33
;     S >= 32: use T1[63-S] = T1[30]
;     tran[ 31][ 33]=1    next VR0 = 3
; === BIT[ 30] ===
;     T0 = 0x85d8a04a     
;     T1 = 0x42a508a1     
;     S =  3
;     S < 32: use T0[31-S] = T0[28]
;     tran[ 30][  3]=0    next VR0 = 6
; === BIT[ 29] ===
;     T0 = 0x0ff8fa8f     
;     T1 = 0xf20ffff8     
;     S =  6
;     S < 32: use T0[31-S] = T0[25]
;     tran[ 29][  6]=1    next VR0 = 13
; === BIT[ 28] ===
;     T0 = 0x53fe1bf4     
;     T1 = 0x07feb14e     
;     S = 13
;     S < 32: use T0[31-S] = T0[18]
;     tran[ 28][ 13]=1    next VR0 = 27
; === BIT[ 27] ===
;     T0 = 0x0ec0da8d     
;     T1 = 0xa24ecec0     
;     S = 27
;     S < 32: use T0[31-S] = T0[ 4]
;     tran[ 27][ 27]=0    next VR0 = 54
; === BIT[ 26] ===
;     T0 = 0x59ad09fd     
;     T1 = 0x0d78ad5d     
;     S = 54
;     S >= 32: use T1[63-S] = T1[ 9]
;     tran[ 26][ 54]=0    next VR0 = 44
; === BIT[ 25] ===
;     T0 = 0x86168696     
;     T1 = 0x87949697     
;     S = 44
;     S >= 32: use T1[63-S] = T1[19]
;     tran[ 25][ 44]=0    next VR0 = 24
; === BIT[ 24] ===
;     T0 = 0xf08d4cf1     
;     T1 = 0x85fce48d     
;     S = 24
;     S < 32: use T0[31-S] = T0[ 7]
;     tran[ 24][ 24]=1    next VR0 = 49
; === BIT[ 23] ===
;     T0 = 0x03a29007     
;     T1 = 0xa00e04e0     
;     S = 49
;     S >= 32: use T1[63-S] = T1[14]
;     tran[ 23][ 49]=0    next VR0 = 34
; === BIT[ 22] ===
;     T0 = 0x2ff4f28f     
;     T1 = 0xf2afaff2     
;     S = 34
;     S >= 32: use T1[63-S] = T1[29]
;     tran[ 22][ 34]=1    next VR0 = 5
; === BIT[ 21] ===
;     T0 = 0x0aa93ab1     
;     T1 = 0xa15ba01a     
;     S =  5
;     S < 32: use T0[31-S] = T0[26]
;     tran[ 21][  5]=0    next VR0 = 10
; === BIT[ 20] ===
;     T0 = 0xc04e0458     
;     T1 = 0x5884508d     
;     S = 10
;     S < 32: use T0[31-S] = T0[21]
;     tran[ 20][ 10]=0    next VR0 = 20
; === BIT[ 19] ===
;     T0 = 0xe6182758     
;     T1 = 0x469872a5     
;     S = 20
;     S < 32: use T0[31-S] = T0[11]
;     tran[ 19][ 20]=0    next VR0 = 40
; === BIT[ 18] ===
;     T0 = 0xa1df83db     
;     T1 = 0xd29792df     
;     S = 40
;     S >= 32: use T1[63-S] = T1[23]
;     tran[ 18][ 40]=1    next VR0 = 17
; === BIT[ 17] ===
;     T0 = 0xb01a3770     
;     T1 = 0x1ab41225     
;     S = 17
;     S < 32: use T0[31-S] = T0[14]
;     tran[ 17][ 17]=0    next VR0 = 34
; === BIT[ 16] ===
;     T0 = 0x7b257aa5     
;     T1 = 0xa55ae558     
;     S = 34
;     S >= 32: use T1[63-S] = T1[29]
;     tran[ 16][ 34]=1    next VR0 = 5
; === BIT[ 15] ===
;     T0 = 0x0fd2f51f     
;     T1 = 0xf08f4ff0     
;     S =  5
;     S < 32: use T0[31-S] = T0[26]
;     tran[ 15][  5]=1    next VR0 = 11
; === BIT[ 14] ===
;     T0 = 0xfe031e60     
;     T1 = 0x8fc0b408     
;     S = 11
;     S < 32: use T0[31-S] = T0[20]
;     tran[ 14][ 11]=0    next VR0 = 22
; === BIT[ 13] ===
;     T0 = 0x0550a00f     
;     T1 = 0x500708b5     
;     S = 22
;     S < 32: use T0[31-S] = T0[ 9]
;     tran[ 13][ 22]=0    next VR0 = 44
; === BIT[ 12] ===
;     T0 = 0xf2070772     
;     T1 = 0x07b07003     
;     S = 44
;     S >= 32: use T1[63-S] = T1[19]
;     tran[ 12][ 44]=0    next VR0 = 24
; === BIT[ 11] ===
;     T0 = 0x5a85da85     
;     T1 = 0xa5dee5da     
;     S = 24
;     S < 32: use T0[31-S] = T0[ 7]
;     tran[ 11][ 24]=1    next VR0 = 49
; === BIT[ 10] ===
;     T0 = 0x02ad108f     
;     T1 = 0x258fa50a     
;     S = 49
;     S >= 32: use T1[63-S] = T1[14]
;     tran[ 10][ 49]=0    next VR0 = 34
; === BIT[  9] ===
;     T0 = 0x849e84d4     
;     T1 = 0x8cf4948f     
;     S = 34
;     S >= 32: use T1[63-S] = T1[29]
;     tran[  9][ 34]=0    next VR0 = 4
; === BIT[  8] ===
;     T0 = 0x5bb1daaf     
;     T1 = 0xfd1acfda     
;     S =  4
;     S < 32: use T0[31-S] = T0[27]
;     tran[  8][  4]=1    next VR0 = 9
; === BIT[  7] ===
;     T0 = 0x52a71aa5     
;     T1 = 0xa59aa59a     
;     S =  9
;     S < 32: use T0[31-S] = T0[22]
;     tran[  7][  9]=0    next VR0 = 18
; === BIT[  6] ===
;     T0 = 0x581c49c0     
;     T1 = 0x1c58c049     
;     S = 18
;     S < 32: use T0[31-S] = T0[13]
;     tran[  6][ 18]=0    next VR0 = 36
;-----------------------------------------------------
; Decoder output vs input: Use for debug
;BIT[  0] : output=0,input=0
;BIT[  1] : output=0,input=0
;BIT[  2] : output=1,input=1
;BIT[  3] : output=0,input=0
;BIT[  4] : output=0,input=0
;BIT[  5] : output=1,input=1
;BIT[  6] : output=0,input=0
;BIT[  7] : output=0,input=0
;BIT[  8] : output=0,input=0
;BIT[  9] : output=1,input=1
;BIT[ 10] : output=1,input=1
;BIT[ 11] : output=0,input=0
;BIT[ 12] : output=1,input=1
;BIT[ 13] : output=0,input=0
;BIT[ 14] : output=0,input=0
;BIT[ 15] : output=0,input=0
;BIT[ 16] : output=1,input=1
;BIT[ 17] : output=0,input=0
;BIT[ 18] : output=1,input=1
;BIT[ 19] : output=0,input=0
;BIT[ 20] : output=0,input=0
;BIT[ 21] : output=0,input=0
;BIT[ 22] : output=1,input=1
;BIT[ 23] : output=1,input=1
;BIT[ 24] : output=0,input=0
;BIT[ 25] : output=1,input=1
;BIT[ 26] : output=1,input=1
;BIT[ 27] : output=0,input=0
;BIT[ 28] : output=0,input=0
;BIT[ 29] : output=0,input=0
;BIT[ 30] : output=0,input=0
;BIT[ 31] : output=1,input=1
;BIT[ 32] : output=1,input=1
;BIT[ 33] : output=1,input=1
;BIT[ 34] : output=0,input=0
;BIT[ 35] : output=1,input=1
;BIT[ 36] : output=1,input=1
;BIT[ 37] : output=0,input=0
;BIT[ 38] : output=1,input=1
;BIT[ 39] : output=1,input=1
;BIT[ 40] : output=1,input=1
;BIT[ 41] : output=1,input=1
;BIT[ 42] : output=0,input=0
;BIT[ 43] : output=0,input=0
;BIT[ 44] : output=1,input=1
;BIT[ 45] : output=0,input=0
;BIT[ 46] : output=0,input=0
;BIT[ 47] : output=0,input=0
;BIT[ 48] : output=1,input=1
;BIT[ 49] : output=0,input=0
;BIT[ 50] : output=0,input=0
;BIT[ 51] : output=0,input=0
;BIT[ 52] : output=1,input=1
;BIT[ 53] : output=1,input=1
;BIT[ 54] : output=0,input=0
;BIT[ 55] : output=1,input=1
;BIT[ 56] : output=0,input=0
;BIT[ 57] : output=1,input=1
;BIT[ 58] : output=1,input=1
;BIT[ 59] : output=1,input=1
;BIT[ 60] : output=1,input=1
;BIT[ 61] : output=1,input=1
;BIT[ 62] : output=0,input=0
;BIT[ 63] : output=1,input=1
;BIT[ 64] : output=0,input=0
;BIT[ 65] : output=1,input=1
;BIT[ 66] : output=1,input=1
;BIT[ 67] : output=1,input=1
;BIT[ 68] : output=0,input=0
;BIT[ 69] : output=0,input=0
;BIT[ 70] : output=1,input=1
;BIT[ 71] : output=0,input=0
;BIT[ 72] : output=0,input=0
;BIT[ 73] : output=0,input=0
;BIT[ 74] : output=0,input=0
;BIT[ 75] : output=1,input=1
;BIT[ 76] : output=0,input=0
;BIT[ 77] : output=1,input=1
;BIT[ 78] : output=0,input=0
;BIT[ 79] : output=1,input=1
;BIT[ 80] : output=1,input=1
;BIT[ 81] : output=0,input=0
;BIT[ 82] : output=0,input=0
;BIT[ 83] : output=0,input=0
;BIT[ 84] : output=0,input=0
;BIT[ 85] : output=1,input=1
;BIT[ 86] : output=1,input=1
;BIT[ 87] : output=0,input=0
;BIT[ 88] : output=0,input=0
;BIT[ 89] : output=0,input=0
;BIT[ 90] : output=0,input=0
;BIT[ 91] : output=0,input=0
;BIT[ 92] : output=1,input=1
;BIT[ 93] : output=1,input=1
;BIT[ 94] : output=0,input=0
;BIT[ 95] : output=0,input=0
;BIT[ 96] : output=0,input=0
;BIT[ 97] : output=0,input=0
;BIT[ 98] : output=1,input=1
;BIT[ 99] : output=1,input=1
;BIT[100] : output=0,input=0
;BIT[101] : output=0,input=0
;BIT[102] : output=0,input=0
;BIT[103] : output=0,input=0
;BIT[104] : output=0,input=0
;BIT[105] : output=0,input=0
