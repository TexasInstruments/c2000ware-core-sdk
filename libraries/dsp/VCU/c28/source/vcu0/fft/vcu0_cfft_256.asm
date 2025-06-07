;;*****************************************************************************
;;  \file source/vcu0/vcu0_cfft_256.asm
;; 
;;  \brief  256-pt complex FFT
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

;;*****************************************************************************
;;
;;
;;*****************************************************************************
;;
;;*****************************************************************************
;; includes
;;*****************************************************************************
;;
      ;.cdecls   C,LIST,"fft.h"
;############################################################################
;
;/*! \page CFFT_256 (Complex FFT -- 256 point)
;- This routine implements the 256-pt  complex FFT algorithm
;  The 8 FFT stages are fully unrolled to take advantage of 
;  the repeat block and parallel VCCP instructions.
;- In the first 3 stages, the butterflies are rearranged to 
;  group those whose offset is constant. For examples, the second
;  stage is grouped by even butterflies and odd butterflies.
;- Last 5 stages, butterflies are grouped in sub-FFTs
;  For example , the 7th stage has 2 groups, upper and lower      
;*/
;############################################################################
;/*! \defgroup CFFT_256_FN (256pt CFFT Routines)
;  @{  .....starts the defintion block
;*/
   .if  __TI_EABI__
        .asg cfft16_256p_calc, _cfft16_256p_calc
   .endif
      .global  _cfft16_256p_calc
;//###########################################################################      

      .text

;/*! Calculate the 256 pt Complex FFT
; *
; * \param Handle to the structure, cfft16_t
; *
; *  XAR4 - FFT handle
; *   *+XAR4[0]:  int *ipcbptr -> input pointer
; *   *+XAR4[2]:  int *workptr -> work buffer pointer
; *   *+XAR4[4]:  int *tfptr -> twiddle factor table pointer
; *   *+XAR4[6]:  int size -> Number of data points
; *   *+XAR4[7]:  int nrstage -> Number of FFT stages
; *   *+XAR4[8]:  int step -> Twiddle factor table search step
; *   *+XAR4[9]:  0
; *   *+XAR4[10]: int *brevptr -> Bit reversal table pointer
; * 
; *  Registers
; *    XAR0:         offset address
; *    XAR1:         offset address
; *    XAR2:         FFT input base pointer 
; *    XAR3:         FFT output base pointer 
; *    XAR4:         FFT handler pointer
; *    XAR5:         
; *    XAR6:         Twiddle Factor table base pointer
; *    XAR7:        
; *  
; *    [SP-2]:       Stores twiddle factor pointer
; *
; * \return none
; */        
_cfft16_256p_calc:

          PUSH        XAR0
          PUSH        XAR1
          PUSH        XAR2
          PUSH        XAR3
          ADDB        SP, #18            ; allocate stack space for temperary variables          
          VMOV32      *-SP[2], VR0       ; save VRx to stack
          VMOV32      *-SP[4], VR1
          VMOV32      *-SP[6], VR2
          VMOV32      *-SP[8], VR3
          VMOV32      *-SP[10], VR4
          VMOV32      *-SP[12], VR5
          VMOV32      *-SP[14], VR6
          SETC        SXM                ; sign extension mode
                                 
          VSATON                    	 ; VSTATUS.SAT = 1
          VRNDON                         ; rounding on
          VSETSHR     #16	             ; VSTATUS.SHIFTR = RIGHT_SHIFT
          VSETSHL     #15                ; VSTATUS.SHIFTL = LEFT_SHIFT, each stage output is scaled by2 

;========================================================================
;         FFT stage 1: N/2 groups of 2-pt FFT
;========================================================================
          
          MOVL        XAR2, *+XAR4[0]     ; load FFT input buffer base pointer
          MOVL        XAR3, *+XAR4[2]     ; load FFT work buffer pointer
          MOVL        XAR6, *+XAR4[4]     ; load twiddle factor base pointer
                                          ; pre-load the pipeline
          VMOV32      VR4,*XAR2++         ; VR4 = Ia:Ra(0)
          VMOV32      VR1,*XAR2++         ; VR1 = Ib:Rb(0)
         
          VMOV32      VR0,*XAR6++         ; VR0 = COSn:SINn(0)
          VCMPY       VR3, VR2, VR1, VR0  ; 
          VNOP
          VCDSUB16    VR6, VR4, VR3, VR2                
          VCDADD16    VR5, VR4, VR3, VR2
       || VMOV32      VR4,*XAR2++         ; VR4 = Ia:Ra(1)
          VMOV32      VR1,*XAR2++         ; VR1 = Ib:Rb(1)

          .align      2
          RPTB       _BUTTERFLY_LOOP1, #125 ; 128 butterflies for each stage
          
          VCMPY       VR3, VR2, VR1, VR0 
       || VMOV32      *XAR3++,VR5         ; Ia':Ra'(0) = VR5
          VMOV32      *XAR3++,VR6         ; Ib':Rb'(0) = VR6
       
          VCDSUB16    VR6, VR4, VR3, VR2   

          VCDADD16    VR5, VR4, VR3, VR2 
       || VMOV32      VR4,*XAR2++         ; VR4 = Ia:Ra(2)  
          VMOV32      VR1,*XAR2++         ; VR1 = Ib:Rb(2)
            
_BUTTERFLY_LOOP1:
 
          VCMPY       VR3, VR2, VR1, VR0  
       || VMOV32      *XAR3++,VR5     ; Ia':Ra'(1) = VR5
          VMOV32      *XAR3++,VR6     ; Ib':Rb'(1) = VR6
 
          VCDSUB16    VR6, VR4, VR3, VR2       
          VCDADD16    VR5, VR4, VR3, VR2  
          VMOV32      *XAR3++,VR5     ; Ia':Ra'(2) = VR5
          VMOV32      *XAR3++,VR6     ; Ib':Rb'(2) = VR6

;========================================================================
;         FFT stage 2: N/4 groups 4-pt FFT
;========================================================================
          ZAPA
          MOV         AR0, #1              ; loop twice , even and odd butterflies
_STAGE2_LOOP:
          MOVL        XAR2, *+XAR4[2]      ; load work buffer base pointer, as the input buffer
          MOVL        XAR3, *+XAR4[0]      ; load FFT input buffer base pointer, as the work buffer
 
          MOVL        ACC, XAR2            ; P stores offset between even and odd butterflies
          ADDL        ACC, P               
          MOVL        XAR2, ACC      
          
          MOVL        ACC, XAR3
          ADDL        ACC, P
          MOVL        XAR3, ACC
          
          MOV         AR1, #4              ; butterfy size 2 samples (I/Q)
                                           ; pre-load the pipeline
          VMOV32      VR4,*XAR2            ; VR4 = Ia:Ra(0)
          VMOV32      VR1,*+XAR2[AR1]      ; VR1 = Ib:Rb(0)
         
          VMOV32      VR0,*XAR6++          ; VR0 = COSn:SINn(0)
          VCMPY       VR3, VR2, VR1, VR0   ; 
          ADDB        XAR2, #8             ; move to the next butterfly
          VCDSUB16    VR6, VR4, VR3, VR2                
          VCDADD16    VR5, VR4, VR3, VR2
       || VMOV32      VR4,*XAR2            ; VR4 = Ia:Ra(1)
          VMOV32      VR1,*+XAR2[AR1]      ; VR1 = Ib:Rb(1)

           .align      2
          RPTB       _BUTTERFLY_LOOP2, #61 ;64 butterflies for even butterflies
          
          ADDB        XAR2, #8             ; move to the next butterfly        
          VCMPY       VR3, VR2, VR1, VR0 
       || VMOV32      *XAR3,VR5            ; Ia':Ra'(0) = VR5
          VMOV32      *+XAR3[AR1],VR6      ; Ib':Rb'(0) = VR6
          ADDB        XAR3, #8
          VCDSUB16    VR6, VR4, VR3, VR2   
 
          VCDADD16    VR5, VR4, VR3, VR2 
       || VMOV32      VR4,*XAR2            ; VR4 = Ia:Ra(2)  
          VMOV32      VR1,*+XAR2[AR1]      ; VR1 = Ib:Rb(2)

_BUTTERFLY_LOOP2:
 
          VCMPY       VR3, VR2, VR1, VR0  
       || VMOV32      *XAR3,VR5            ; Ia':Ra'(1) = VR5
          VMOV32      *+XAR3[AR1],VR6      ; Ib':Rb'(1) = VR6
          
          VCDSUB16    VR6, VR4, VR3, VR2    
          VCDADD16    VR5, VR4, VR3, VR2  
          ADDB        XAR3, #8
          VMOV32      *XAR3,VR5            ; Ia':Ra'(2) = VR5
          VMOV32      *+XAR3[AR1],VR6      ; Ib':Rb'(2) = VR6

          MOV         PL, #2
          BANZ        _STAGE2_LOOP, AR0--
            
;========================================================================
;         FFT stage 3: N/8 groups 8-pt FFT
;========================================================================
          ZAPA
          MOV         AR0, #3             ; loop four times 
          MOV         AR1, #8             ; butterfy size 4 samples (I/Q)
_STAGE3_LOOP:
          MOVL        XAR2, *+XAR4[0]     ; load FFT input buffer base pointer        
          MOVL        XAR3, *+XAR4[2]     ; load FFT work buffer pointer
 
          MOVL        ACC, XAR2           ; P stores offset between even and odd butterflies
          ADDL        ACC, P               
          MOVL        XAR2, ACC      
          
          MOVL        ACC, XAR3
          ADDL        ACC, P
          MOVL        XAR3, ACC
                                           ; pre-load the pipeline
          VMOV32      VR4,*XAR2            ; VR4 = Ia:Ra(0)
          VMOV32      VR1,*+XAR2[AR1]      ; VR1 = Ib:Rb(0)
         
          VMOV32      VR0,*XAR6++          ; VR0 = COSn:SINn(0)
          VCMPY       VR3, VR2, VR1, VR0   ; 
          ADDB        XAR2, #16            ; move to the next butterfly
          VCDSUB16    VR6, VR4, VR3, VR2                
          VCDADD16    VR5, VR4, VR3, VR2
       || VMOV32      VR4,*XAR2            ; VR4 = Ia:Ra(1)
          VMOV32      VR1,*+XAR2[AR1]      ; VR1 = Ib:Rb(1)

          .align      2
          RPTB       _BUTTERFLY_LOOP3, #29 ; 32 butterflies for even butterflies
          
          ADDB        XAR2, #16            ; move to the next butterfly        
          VCMPY       VR3, VR2, VR1, VR0 
       || VMOV32      *XAR3,VR5            ; Ia':Ra'(0) = VR5
          VMOV32      *+XAR3[AR1],VR6      ; Ib':Rb'(0) = VR6
          ADDB        XAR3, #16
          VCDSUB16    VR6, VR4, VR3, VR2   
  
          VCDADD16    VR5, VR4, VR3, VR2 
       || VMOV32      VR4,*XAR2            ; VR4 = Ia:Ra(2)  
          VMOV32      VR1,*+XAR2[AR1]      ; VR1 = Ib:Rb(2)
  
_BUTTERFLY_LOOP3:
 
          VCMPY       VR3, VR2, VR1, VR0  
       || VMOV32      *XAR3,VR5            ; Ia':Ra'(1) = VR5
          VMOV32      *+XAR3[AR1],VR6      ; Ib':Rb'(1) = VR6

          VCDSUB16    VR6, VR4, VR3, VR2      
          VCDADD16    VR5, VR4, VR3, VR2  
          ADDB        XAR3, #16
          VMOV32      *XAR3,VR5            ; Ia':Ra'(2) = VR5
          VMOV32      *+XAR3[AR1],VR6      ; Ib':Rb'(2) = VR6

          ADD          PL, #2              ; move to the next butterfly group
          BANZ        _STAGE3_LOOP, AR0--
            
;========================================================================
;         FFT stage 4: N/16 groups 16-pt FFT
;========================================================================
          ZAPA
          MOV         AR0, #15             ; loop 16 times (sub groups) 
          MOV         AR1, #14             ; butterfy size 8 samples (I/Q), excluding one ++ operation
          MOVL        *-SP[16], XAR6       ; save the current twiddle factor pointer
_STAGE4_LOOP:
          MOVL        XAR6, *-SP[16]       ; reload the twiddle factor base pointer
          MOVL        XAR2, *+XAR4[2]      ; load work buffer base pointer, as the input buffer
          MOVL        XAR3, *+XAR4[0]      ; load FFT input buffer base pointer, as the work buffer
 
          MOVL        ACC, XAR2            ; P stores offset between even and odd butterflies
          ADDL        ACC, P               
          MOVL        XAR2, ACC      
          
          MOVL        ACC, XAR3
          ADDL        ACC, P
          MOVL        XAR3, ACC
                                           ; pre-load the pipeline
          VMOV32      VR4,*XAR2++          ; VR4 = Ia:Ra(0)
          VMOV32      VR1,*+XAR2[AR1]      ; VR1 = Ib:Rb(0)
         
          VMOV32      VR0,*XAR6++          ; VR0 = COSn:SINn(0)
          VCMPY       VR3, VR2, VR1, VR0   ; 
       || VMOV32      VR0,*XAR6++          ; VR0 = COSn:SINn(1)       
          VNOP
          VCDSUB16    VR6, VR4, VR3, VR2
          VCDADD16    VR5, VR4, VR3, VR2
       || VMOV32      VR4,*XAR2++          ; VR4 = Ia:Ra(1)
          VMOV32      VR1,*+XAR2[AR1]      ; VR1 = Ib:Rb(1)

          .align      2
          RPTB       _BUTTERFLY_LOOP4, #5  ; 8 butterflies in one subgroup
          
          VCMPY       VR3, VR2, VR1, VR0 
       || VMOV32      *XAR3++,VR5          ; Ia':Ra'(0) = VR5
          VMOV32      *+XAR3[AR1],VR6      ; Ib':Rb'(0) = VR6
          VCDSUB16    VR6, VR4, VR3, VR2   
       || VMOV32      VR0,*XAR6++          ; VR0 = COSn:SINn(1) 
        
          VCDADD16    VR5, VR4, VR3, VR2 
       || VMOV32      VR4,*XAR2++          ; VR4 = Ia:Ra(2)  
          VMOV32      VR1,*+XAR2[AR1]      ; VR1 = Ib:Rb(2)
       
_BUTTERFLY_LOOP4:
 
          VCMPY       VR3, VR2, VR1, VR0  
       || VMOV32      *XAR3++,VR5          ; Ia':Ra'(1) = VR5
          VMOV32      *+XAR3[AR1],VR6      ; Ib':Rb'(1) = VR6
 
          VCDSUB16    VR6, VR4, VR3, VR2     
          VCDADD16    VR5, VR4, VR3, VR2  
          VMOV32      *XAR3++,VR5          ; Ia':Ra'(2) = VR5
          VMOV32      *+XAR3[AR1],VR6      ; Ib':Rb'(2) = VR6

          ADD          PL, #32             ; move to the next butterfly group
          BANZ        _STAGE4_LOOP, AR0--

;========================================================================
;         FFT stage 5: N/32 groups 32-pt FFT
;========================================================================
          ZAPA
          MOV         AR0, #7              ; loop 8 times (sub groups) 
          MOV         AR1, #30             ; butterfy size 16 samples (I/Q), excluding one ++ operation
          MOVL        *-SP[16], XAR6       ; save the current twiddle factor pointer
_STAGE5_LOOP:
          MOVL        XAR6, *-SP[16]       ; reload the twiddle factor base pointer
          MOVL        XAR2, *+XAR4[0]      ; load FFT input buffer base pointer        
          MOVL        XAR3, *+XAR4[2]      ; load FFT work buffer pointer
 
          MOVL        ACC, XAR2            ; P stores offset between even and odd butterflies
          ADDL        ACC, P               
          MOVL        XAR2, ACC      
          
          MOVL        ACC, XAR3
          ADDL        ACC, P
          MOVL        XAR3, ACC
                                           ; pre-load the pipeline
          VMOV32      VR4,*XAR2++          ; VR4 = Ia:Ra(0)
          VMOV32      VR1,*+XAR2[AR1]      ; VR1 = Ib:Rb(0)
         
          VMOV32      VR0,*XAR6++          ; VR0 = COSn:SINn(0)
          VCMPY       VR3, VR2, VR1, VR0   ; 
       || VMOV32      VR0,*XAR6++          ; VR0 = COSn:SINn(1)       
          VNOP
          VCDSUB16    VR6, VR4, VR3, VR2
          VCDADD16    VR5, VR4, VR3, VR2
       || VMOV32      VR4,*XAR2++          ; VR4 = Ia:Ra(1)
          VMOV32      VR1,*+XAR2[AR1]      ; VR1 = Ib:Rb(1)

          .align      2
          RPTB       _BUTTERFLY_LOOP5, #13 ; 16 butterflies in one subgroup
          
          VCMPY       VR3, VR2, VR1, VR0 
       || VMOV32      *XAR3++,VR5          ; Ia':Ra'(0) = VR5
          VMOV32      *+XAR3[AR1],VR6      ; Ib':Rb'(0) = VR6
          VCDSUB16    VR6, VR4, VR3, VR2   
       || VMOV32      VR0,*XAR6++          ; VR0 = COSn:SINn(1) 
        
 
          VCDADD16    VR5, VR4, VR3, VR2 
       || VMOV32      VR4,*XAR2++          ; VR4 = Ia:Ra(2)  
          VMOV32      VR1,*+XAR2[AR1]      ; VR1 = Ib:Rb(2)
       
_BUTTERFLY_LOOP5:
 
          VCMPY       VR3, VR2, VR1, VR0  
       || VMOV32      *XAR3++,VR5          ; Ia':Ra'(1) = VR5
          VMOV32      *+XAR3[AR1],VR6      ; Ib':Rb'(1) = VR6
  
          VCDSUB16    VR6, VR4, VR3, VR2    
          VCDADD16    VR5, VR4, VR3, VR2  
          VMOV32      *XAR3++,VR5          ; Ia':Ra'(2) = VR5
          VMOV32      *+XAR3[AR1],VR6      ; Ib':Rb'(2) = VR6

          ADD          PL, #64             ; move to the next butterfly group
          BANZ        _STAGE5_LOOP, AR0--

;========================================================================
;         FFT stage 6: N/64 groups 64-pt FFT
;========================================================================
          ZAPA
          MOV         AR0, #3              ; loop 4 times (sub groups) 
          MOV         AR1, #62             ; butterfy size 32 samples (I/Q), excluding one ++ operation
          MOVL        *-SP[16], XAR6       ; save the current twiddle factor pointer
_STAGE6_LOOP:
          MOVL        XAR6, *-SP[16]       ; reload the twiddle factor base pointer
          MOVL        XAR2, *+XAR4[2]      ; load work buffer base pointer, as the input buffer
          MOVL        XAR3, *+XAR4[0]      ; load FFT input buffer base pointer, as the work buffer
 
          MOVL        ACC, XAR2            ; P stores offset between even and odd butterflies
          ADDL        ACC, P               
          MOVL        XAR2, ACC      
          
          MOVL        ACC, XAR3
          ADDL        ACC, P
          MOVL        XAR3, ACC
                                           ; pre-load the pipeline
          VMOV32      VR4,*XAR2++          ; VR4 = Ia:Ra(0)
          VMOV32      VR1,*+XAR2[AR1]      ; VR1 = Ib:Rb(0)
         
          VMOV32      VR0,*XAR6++          ; VR0 = COSn:SINn(0)
          VCMPY       VR3, VR2, VR1, VR0   ; 
       || VMOV32      VR0,*XAR6++          ; VR0 = COSn:SINn(1)       
          VNOP
          VCDSUB16    VR6, VR4, VR3, VR2
          VCDADD16    VR5, VR4, VR3, VR2
       || VMOV32      VR4,*XAR2++          ; VR4 = Ia:Ra(1)
          VMOV32      VR1,*+XAR2[AR1]      ; VR1 = Ib:Rb(1)

          .align      2
          RPTB       _BUTTERFLY_LOOP6, #29 ; 32 butterflies in one subgroup
          
          VCMPY       VR3, VR2, VR1, VR0 
       || VMOV32      *XAR3++,VR5          ; Ia':Ra'(0) = VR5
          VMOV32      *+XAR3[AR1],VR6      ; Ib':Rb'(0) = VR6
          VCDSUB16    VR6, VR4, VR3, VR2   
       || VMOV32      VR0,*XAR6++          ; VR0 = COSn:SINn(1) 
        
 
          VCDADD16    VR5, VR4, VR3, VR2 
       || VMOV32      VR4,*XAR2++          ; VR4 = Ia:Ra(2)  
          VMOV32      VR1,*+XAR2[AR1]      ; VR1 = Ib:Rb(2)
       
_BUTTERFLY_LOOP6:
 
          VCMPY       VR3, VR2, VR1, VR0  
       || VMOV32      *XAR3++,VR5          ; Ia':Ra'(1) = VR5
          VMOV32      *+XAR3[AR1],VR6      ; Ib':Rb'(1) = VR6
  
          VCDSUB16    VR6, VR4, VR3, VR2    
          VCDADD16    VR5, VR4, VR3, VR2  
          VMOV32      *XAR3++,VR5          ; Ia':Ra'(2) = VR5
          VMOV32      *+XAR3[AR1],VR6      ; Ib':Rb'(2) = VR6

          ADD          PL, #128            ; move to the next butterfly group
          BANZ        _STAGE6_LOOP, AR0--

;========================================================================
;         FFT stage 7: N/128 groups 128-pt FFT
;========================================================================
          ZAPA
          MOV         AR0, #1              ; loop 2 times (sub groups) 
          MOV         AR1, #126            ; butterfy size 64 samples (I/Q), excluding one ++ operation
          MOVL        *-SP[16], XAR6       ; save the current twiddle factor pointer
_STAGE7_LOOP:
          MOVL        XAR6, *-SP[16]       ; reload the twiddle factor base pointer
          MOVL        XAR2, *+XAR4[0]      ; load FFT input buffer base pointer        
          MOVL        XAR3, *+XAR4[2]      ; load FFT work buffer pointer
 
          MOVL        ACC, XAR2            ; P stores offset between even and odd butterflies
          ADDL        ACC, P               
          MOVL        XAR2, ACC      
          
          MOVL        ACC, XAR3
          ADDL        ACC, P
          MOVL        XAR3, ACC
                                           ; pre-load the pipeline
          VMOV32      VR4,*XAR2++          ; VR4 = Ia:Ra(0)
          VMOV32      VR1,*+XAR2[AR1]      ; VR1 = Ib:Rb(0)
         
          VMOV32      VR0,*XAR6++          ; VR0 = COSn:SINn(0)
          VCMPY       VR3, VR2, VR1, VR0   ; 
       || VMOV32      VR0,*XAR6++          ; VR0 = COSn:SINn(1)       
          VNOP
          VCDSUB16    VR6, VR4, VR3, VR2
          VCDADD16    VR5, VR4, VR3, VR2
       || VMOV32      VR4,*XAR2++          ; VR4 = Ia:Ra(1)
          VMOV32      VR1,*+XAR2[AR1]      ; VR1 = Ib:Rb(1)

          .align      2
          RPTB       _BUTTERFLY_LOOP7, #61 ; 64 butterflies in one subgroup
          
          VCMPY       VR3, VR2, VR1, VR0 
       || VMOV32      *XAR3++,VR5          ; Ia':Ra'(0) = VR5
          VMOV32      *+XAR3[AR1],VR6      ; Ib':Rb'(0) = VR6
          VCDSUB16    VR6, VR4, VR3, VR2   
       || VMOV32      VR0,*XAR6++          ; VR0 = COSn:SINn(1) 
        
 
          VCDADD16    VR5, VR4, VR3, VR2 
       || VMOV32      VR4,*XAR2++          ; VR4 = Ia:Ra(2)  
          VMOV32      VR1,*+XAR2[AR1]      ; VR1 = Ib:Rb(2)
       
_BUTTERFLY_LOOP7:
 
          VCMPY       VR3, VR2, VR1, VR0  
       || VMOV32      *XAR3++,VR5          ; Ia':Ra'(1) = VR5
          VMOV32      *+XAR3[AR1],VR6      ; Ib':Rb'(1) = VR6
  
          VCDSUB16    VR6, VR4, VR3, VR2    
          VCDADD16    VR5, VR4, VR3, VR2  
          VMOV32      *XAR3++,VR5          ; Ia':Ra'(2) = VR5
          VMOV32      *+XAR3[AR1],VR6      ; Ib':Rb'(2) = VR6

          ADD          PL, #256            ; move to the next butterfly group
          BANZ        _STAGE7_LOOP, AR0--


;========================================================================
;         FFT stage 8: N/256 groups 256-pt FFT
;========================================================================
          ZAPA
          MOV         AR1, #254            ; butterfy size 128 samples (I/Q), excluding one ++ operation

          MOVL        XAR2, *+XAR4[2]      ; load work buffer base pointer, as the input buffer
          MOVL        XAR3, *+XAR4[0]      ; load FFT input buffer base pointer, as the work buffer
                                           ; pre-load the pipeline
          VMOV32      VR4,*XAR2++          ; VR4 = Ia:Ra(0)
          VMOV32      VR1,*+XAR2[AR1]      ; VR1 = Ib:Rb(0)
         
          VMOV32      VR0,*XAR6++          ; VR0 = COSn:SINn(0)
          VCMPY       VR3, VR2, VR1, VR0   ; 
       || VMOV32      VR0,*XAR6++          ; VR0 = COSn:SINn(1)       
          VNOP
          VCDSUB16    VR6, VR4, VR3, VR2
          VCDADD16    VR5, VR4, VR3, VR2
       || VMOV32      VR4,*XAR2++          ; VR4 = Ia:Ra(1)
          VMOV32      VR1,*+XAR2[AR1]      ; VR1 = Ib:Rb(1)

          .align      2
          RPTB       _BUTTERFLY_LOOP7A, #63 ; 128 butterflies in one subgroup, broken into 2 RPTB blocks
          
          VCMPY       VR3, VR2, VR1, VR0 
       || VMOV32      *XAR3++,VR5          ; Ia':Ra'(0) = VR5
          VMOV32      *+XAR3[AR1],VR6      ; Ib':Rb'(0) = VR6
          VCDSUB16    VR6, VR4, VR3, VR2   
       || VMOV32      VR0,*XAR6++          ; VR0 = COSn:SINn(1) 

          VCDADD16    VR5, VR4, VR3, VR2 
       || VMOV32      VR4,*XAR2++          ; VR4 = Ia:Ra(2)  
          VMOV32      VR1,*+XAR2[AR1]      ; VR1 = Ib:Rb(2)
       
_BUTTERFLY_LOOP7A:

          .align      2
          RPTB       _BUTTERFLY_LOOP7B, #61; 
          
          VCMPY       VR3, VR2, VR1, VR0 
       || VMOV32      *XAR3++,VR5          ; Ia':Ra'(0) = VR5
          VMOV32      *+XAR3[AR1],VR6      ; Ib':Rb'(0) = VR6
          VCDSUB16    VR6, VR4, VR3, VR2   
       || VMOV32      VR0,*XAR6++          ; VR0 = COSn:SINn(1) 

          VCDADD16    VR5, VR4, VR3, VR2 
       || VMOV32      VR4,*XAR2++          ; VR4 = Ia:Ra(2)  
          VMOV32      VR1,*+XAR2[AR1]      ; VR1 = Ib:Rb(2)
       
_BUTTERFLY_LOOP7B:
 
          VCMPY       VR3, VR2, VR1, VR0  
       || VMOV32      *XAR3++,VR5          ; Ia':Ra'(1) = VR5
          VMOV32      *+XAR3[AR1],VR6      ; Ib':Rb'(1) = VR6
          VCDSUB16    VR6, VR4, VR3, VR2    

          VCDADD16    VR5, VR4, VR3, VR2  
          VMOV32      *XAR3++,VR5          ; Ia':Ra'(2) = VR5
          VMOV32      *+XAR3[AR1],VR6      ; Ib':Rb'(2) = VR6

          VMOV32      VR0, *-SP[2]        ; restore VR registers
          VMOV32      VR1, *-SP[4]
          VMOV32      VR2, *-SP[6]
          VMOV32      VR3, *-SP[8]
          VMOV32      VR4, *-SP[10]
          VMOV32      VR5, *-SP[12]
          VMOV32      VR6, *-SP[14]
          SUBB        SP, #18            ; restore SP   
          POP         XAR3
          POP         XAR2
          POP         XAR1
          POP         XAR0
        
         LRETR

;############################################################################
;  Close the Doxygen group.
;//! @}
;############################################################################

;; End of file
