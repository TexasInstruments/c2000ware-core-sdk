;;#############################################################################
;; FILE: CLAeabi.asm
;; 
;; DESCRIPTION: This holds the .asg for EABI
;; 
;;#############################################################################
;;!
;;! Copyright: Copyright (C) 2023 Texas Instruments Incorporated -
;;!	All rights reserved not granted herein.
;;!	Limited License.
;;!
;;! Texas Instruments Incorporated grants a world-wide, royalty-free,
;;! non-exclusive license under copyrights and patents it now or hereafter
;;! owns or controls to make, have made, use, import, offer to sell and sell
;;! ("Utilize") this software subject to the terms herein. With respect to the
;;! foregoing patent license, such license is granted solely to the extent that
;;! any such patent is necessary to Utilize the software alone. The patent
;;! license shall not apply to any combinations which include this software,
;;! other than combinations with devices manufactured by or for TI 
;;! ("TI Devices").
;;! No hardware patent is licensed hereunder.
;;!
;;! Redistributions must preserve existing copyright notices and reproduce this
;;! license (including the above copyright notice and the disclaimer and
;;! (if applicable) source code license limitations below) in the documentation
;;!  and/or other materials provided with the distribution.
;;!
;;! Redistribution and use in binary form, without modification, are permitted
;;! provided that the following conditions are met:
;;!
;;! * No reverse engineering, decompilation, or disassembly of this software is 
;;! permitted with respect to any software provided in binary form.
;;! * Any redistribution and use are licensed by TI for use only 
;;!   with TI Devices.
;;! * Nothing shall obligate TI to provide you with source code for the 
;;!   software licensed and provided to you in object code.
;;!
;;! If software source code is provided to you, modification and redistribution
;;! of the source code are permitted provided that the following conditions 
;;! are met:
;;!
;;! * any redistribution and use of the source code, including any resulting
;;!   derivative works, are licensed by TI for use only with TI Devices.
;;! * any redistribution and use of any object code compiled from the source
;;!   code and any resulting derivative works, are licensed by TI for use 
;;!   only with TI Devices.
;;!
;;! Neither the name of Texas Instruments Incorporated nor the names of its
;;! suppliers may be used to endorse or promote products derived from this 
;;! software without specific prior written permission.
;;#############################################################################

    .if __TI_EABI__
    ;
    ; CLAacos
    ;
    .asg    CLAacos,_CLAacos
	.asg    __claCLAacos_sp,__cla_CLAacos_sp
    .asg    __claCLAacos_spc_sp,__cla_CLAacos_spc_sp
	
	;
	; CLAacosineTable
	;
    .asg    CLAacosinTable,_CLAacosinTable
    .asg    CLAacosinTableEnd,_CLAacosinTableEnd
    .asg    CLAacosinHalfPITable,_CLAacosinHalfPITable
	
	;
	; CLAasin
	;
    .asg    CLAasin,_CLAasin
	.asg    __claCLAasin_sp,__cla_CLAsin_sp
	
	;
	; CLAasineTable
	;
    .asg    CLAasinTable, _CLAasinTable
	.asg    CLAasinTableEnd,_CLAasinTableEnd
    .asg    CLAasinHalfPITable, _CLAasinHalfPITable
	
	;
	; CLAatan
	;
    .asg    CLAatan,_CLAatan
	.asg    __claCLAatan_sp,__cla_CLAatan_sp
	
	;
	; CLAatan2
	;
    .asg    CLAatan2,_CLAatan2
	.asg    __claCLAatan2_sp,__cla_CLAatan2_sp
	
	;
	; CLAatanPU
	;

    .asg    CLAatan2PU,_CLAatan2PU
	.asg    __claCLAatan2PU_sp,__cla_CLAatan2PU_sp
	
	;
	; CLAatanTable
	;
    .asg    CLAatan2Table, _CLAatan2Table
	.asg    CLAatan2TableEnd,_CLAatan2TableEnd
    .asg    CLAatan2HalfPITable, _CLAatan2HalfPITable
    .asg    CLAINV2PI, _CLAINV2PI
	
	;
	; CLAcos
	;
    .asg    CLAcos,_CLAcos
	.asg    __claCLAcos_sp,__cla_CLAcos_sp
	
	;
	; CLAcosPU
	;
    .asg    CLAcosPU,_CLAcosPU
    .asg    __claCLAcosPU_sp,__cla_CLAcosPU_sp
	
	;
	; CLAdiv
	;
    .asg    CLAdiv,_CLAdiv
	.asg    __claCLAdiv_sp,__cla_CLAdiv_sp
	
	;
	; CLAexp
	;
    .asg    CLAexp,_CLAexp
	.asg    __claCLAexp_sp,__cla_CLAexp_sp
	
	;
	; CLAexp2
	;
    .asg    CLAexp2,_CLAexp2
	.asg    __claCLAexp2_sp,__cla_CLAexp2_sp
	
	;
	; CLAexp10
	;
    .asg    CLAexp10,_CLAexp10
	.asg    __claCLAexp10_sp,__cla_CLAexp10_sp
	
	;
	; CLAexpN
	;
    .asg    CLAexpN,_CLAexpN
	.asg    __claCLAexpN_sp,__cla_CLAexpN_sp
	
	;
	; CLAexpTable
	;
	.asg    CLAExpTable, _CLAExpTable
	.asg    CLAExpTableEnd,_CLAExpTableEnd
    .asg    CLAINV1,_CLAINV1
	.asg    CLAINV2,_CLAINV2
    .asg    CLAINV3,_CLAINV3
    .asg    CLAINV4,_CLAINV4    
    .asg    CLAINV5,_CLAINV5
    .asg    CLAINV6,_CLAINV6
    .asg    CLAINV7,_CLAINV7
    .asg    CLALOG10,_CLALOG10
	
	;
	; CLAisqrt
	;
    .asg    CLAisqrt,_CLAisqrt
	.asg    __claCLAisqrt_sp,__cla_CLAisqrt_sp
	
	;
	; CLAln
	;
    .asg    CLAln,_CLAln
    .asg    __claCLAln_sp,__cla_CLAln_sp
	
	;
	; CLAlnTable
	;
    .asg    CLALNV2,_CLALNV2
    .asg    CLALNVe,_CLALNVe
    .asg    CLALNV10,_CLALNV10
    .asg    CLABIAS,_CLABIAS
    .asg    CLALN_TABLE_MASK1,_CLALN_TABLE_MASK1
    .asg    CLALN_TABLE_MASK2,_CLALN_TABLE_MASK2
    .asg    CLALnTable,_CLALnTable
    .asg    CLALnTableEnd,_CLALnTableEnd
	
	;
	; CLAlog10
	;
    .asg    CLAlog10,_CLAlog10
	.asg    __claCLAlog10_sp,__cla_CLAlog10_sp

	;
	; CLAlogN
	;
    .asg    CLAlogN,_CLAlogN
	.asg    __claCLAlogN_sp,__cla_CLAlogN_sp
	
	;
	; CLAsin
	;
    .asg    CLAsin,_CLAsin
	.asg    __claCLAsin_sp,__cla_CLAsin_sp
	
	;
	; CLAsincos
	;
    .asg    CLAsincos,_CLAsincos
    .asg    __claCLAsincos_sp,__cla_CLAsincos_sp

	;
	; CLAsincosTable
	;
    .asg    CLAsincosTable,_CLAsincosTable
    .asg    CLAsinTable,_CLAsinTable
    .asg    CLAsincosTable_Sin0,_CLAsincosTable_Sin0
    .asg    CLAcosTable,_CLAcosTable
    .asg    CLAsincosTable_Cos0,_CLAsincosTable_Cos0
    .asg    CLAsinTableEnd,_CLAsinTableEnd
    .asg    CLAcosTableEnd,_CLAcosTableEnd
    .asg    CLAsincosTable_TABLE_SIZE,_CLAsincosTable_TABLE_SIZE             
    .asg    CLAsincosTable_TABLE_SIZEDivTwoPi,_CLAsincosTable_TABLE_SIZEDivTwoPi    
    .asg    CLAsincosTable_TwoPiDivTABLE_SIZE,_CLAsincosTable_TwoPiDivTABLE_SIZE  
    .asg    CLAsincosTable_TABLE_MASK,_CLAsincosTable_TABLE_MASK       
    .asg    CLAsincosTable_Coef0,_CLAsincosTable_Coef0
    .asg    CLAsincosTable_Coef1,_CLAsincosTable_Coef1
    .asg    CLAsincosTable_Coef1_pos,_CLAsincosTable_Coef1_pos
    .asg    CLAsincosTable_Coef2,_CLAsincosTable_Coef2
    .asg    CLAsincosTable_Coef3,_CLAsincosTable_Coef3
    .asg    CLAsincosTable_Coef3_neg,_CLAsincosTable_Coef3_neg
    .asg    CLAsincosTableEnd,_CLAsincosTableEnd
	
	;
	; CLAsinPU
	;
    .asg    CLAsinPU,_CLAsinPU
	.asg    __claCLAsinPU_sp,__cla_CLAsinPU_sp
	
	;
	; CLAsqrt
	;
	.asg    CLAsqrt,_CLAsqrt
	.asg    __claCLAsqrt_sp,__cla_CLAsqrt_sp
	
	;
	; FFT
	;
	.asg    CLA_CFFT_run256Pt, _CLA_CFFT_run256Pt
	.asg    CLA_CFFT_run1024Pt, _CLA_CFFT_run1024Pt
	.asg    CLA_CFFT_run512Pt, _CLA_CFFT_run512Pt
	.asg    CLA_CFFT_unpack256Pt, _CLA_CFFT_unpack256Pt
	.asg    CLA_CFFT_unpack512Pt, _CLA_CFFT_unpack512Pt
	.asg    cla_twiddleFactors, _cla_twiddleFactors
	.asg    cla_bitReversalTable, _cla_bitReversalTable
	.asg    IOBuffer, _IOBuffer
	.asg    IOBuffer2, _IOBuffer2
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

	
	
	.endif
	
