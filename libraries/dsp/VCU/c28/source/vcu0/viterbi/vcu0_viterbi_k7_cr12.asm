;;*****************************************************************************
;;! \file source/vcu0/vcu0_viterbi_k7_cr12_plc.asm
;;!
;;! \brief  Viterbi Decoding K = 7, CR = 1/2
;;
;;  \date   Feb 12, 2013
;;! 
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
;;
;;
;;*****************************************************************************
;;
;;*****************************************************************************
;; includes
;;*****************************************************************************
      .cdecls   C,LIST,"vcu0_viterbi_decoder.h"
;############################################################################
;
;/*! \page VITERBI (Viterbi Decoder)
; The Viterbi decoder routines implement the  
; PRIME standard (K=7, CR=1/2)
; - G0 = 1 + D + D2 +D3 + D6
;   G1 = 1 + D2 + D3 + D5 + D6 
; It performs;
; - Updated state metric for each state
; - Updates state transition histories
; - Metric scaling
; - Trace back and decode
;*/
;############################################################################
;/*! \defgroup VITERBI_FN (Viterbi Decoder Routines)
;  @{  .....starts the defintion block
;*/
    .if __TI_EABI__
    .asg    cnvDec_asm, _cnvDec_asm
    .asg    cnvDecInit_asm, _cnvDecInit_asm
    .asg    cnvDecMetricRescale_asm, _cnvDecMetricRescale_asm
    .endif

		.global _cnvDec_asm,  _cnvDecInit_asm
		.global  _cnvDecMetricRescale_asm
;//###########################################################################

VIT_OUT_ODD:           .set  0
;===============================================================================
; Viterbi working memory
;===============================================================================
		.global _dold, _trn_tmp

_tran_hist .usect     ".ebss",      560,2  ; 64 states (1bit/state), max 70 IBITS for G3 FCC
_dold      .usect     ".ebss",      64,2   ; old and new metric
_dnew      .usect     ".shadow",    64,2   ; old and new metric must be in different memory bank        
_trn_tmp   .usect     ".ebss",      290,2  ; temp transition for pack, max 70 IBITS for G3 FCC
                                           ; temp trace output
_trn_s1_p  .usect     ".ebss",      2,2    ; ptr to where transition 
_trn_s2_p  .usect     ".ebss",      2,2    ; update start 
_trn_w1_p  .usect     ".ebss",      2,2    ; ptr to where trace ovlp2
_trn_w2_p  .usect     ".ebss",      2,2    ; should go (wrap)

         .text
;======================================================================
; MACRO for flipping the 32-bit transition bits
;  use *XAR7 as temporary memory location
;======================================================================
FLIP32:  .macro

          VMOV32       *XAR7, VR1       ; save transition bits into RAM
           
          MOVL         ACC, *XAR7       
          MOVB         AL.LSB,*+XAR7[1] ; flip 32 bits
          MOVB         AH.LSB,*+XAR7[3]
          MOVB         AL.MSB,*+XAR7[0] 
          MOVB         AH.MSB,*+XAR7[2] 
          FLIP         AH
          FLIP         AL
         .endm 
                            
;/*! Initialize Viterbi Decoder
; *
; * \param Number of Coded bits
; *
; * Initialize state metric table to a large negative value given by
; * CNV_DEC_METRIC_INIT and initialize the transition and wrap pointers
; * 
; *  AL : nTransBits
; *
; * \return none
; */
_cnvDecInit_asm:
              
          SETC        SXM                ; sign extension mode
          MOVW        DP, #_trn_s1_p

          MOVL        XAR4, #_dold       ; XAR4 = _dold 

          MOV         *XAR4++, #0
          RPT         #(CNV_DEC_NUM_STATES-2)
          ||MOV       *XAR4++, #CNV_DEC_METRIC_INIT


          MOVL        XAR4, #_tran_hist  
          MOVL        @_trn_s1_p, XAR4     ; trn_s1_p = tran_hist[0][0]
          LSL         AL, #1             
          ADD         AR4,AL
          MOVL        @_trn_s2_p, XAR4     ; trn_s2_p = tran_hist[nBits/2][0]   
          MOVL        @_trn_w1_p, XAR4     ; trn_w1_p = tran_hist[nBits/2][0]
                                           ; (4 words/bits)               
          ADD         AR4,AL               
          MOVL        @_trn_w2_p, XAR4     ; trn_w2_p = tran_host[nBits][0]
          LRETR         
       
;/*! Viterbi Decoder
; *
; * \param Number of Coded bits
; * \param Address of input buffer
; * \param Address of output buffer
; * \param Mode of operation
; *
; * This routine performs the trellis decoding. It has four modes of
; * operation
; * - 0: Update metrics and transition, trace 
; *   and decodes all (for hdr) 
; * - 1: Update metrics and transition only 
; *   1st symbol in payload)
; * - 2: Update metrics and transition, 
; *   trace curr prv, decodes prv nBits/2 bits
; * - 3: Update metrics and transition, 
; *   trace curr prv, decodes curr+prv nBits/2 bits  
; * 
; * Register Usage
; *     XAR0 - _dnew[32]
; *     XAR1 - _dold
; *     XAR2 - _dnew
; *     XAR3 - trans_hist
; *     XAR4 - data in 
; *     XAR5 - data_out / tran
; *     AL - #input bits
; *
; * \note Decoder produces nBit/2 bits if flag=0/2 and 
; *       prv_blk+nBit/2 bits if flag=3
; *    
; * \return none
; */
_cnvDec_asm:

;
; Save off everything for now.  This can be reduced later
; if possible.
;
          PUSH        XAR0
          PUSH        XAR1
          PUSH        XAR2
          PUSH        XAR3
   
          ADDB        SP, #4
          LSR         AL, #1             ; AL = nBits >> 1
          MOV         *-SP[1], AL        ; Save nBits in stack (-SP[1])
          MOV         *-SP[2], AH        ; Save flag in stack  (-SP[2]) 
          MOVL        *-SP[4], XAR5      ; Save data_out 
        
          SETC        SXM                ; sign extension mode
          SETC        OVM                ; no saturation
          
          CMP         AL, #0
          BF           _none_zero_acs, NEQ
                                         ; if # of output bits is zero, direct trace back 
          MOVW        DP,   #_trn_w1_p   ; switch to previous tran_hist   
          MOVL        XAR3, @_trn_w1_p   
          BF          _cnv_dec_ovlp, UNC
_none_zero_acs:          

        
          SUBB        AL, #1       
          MOVZ        AR6, @AL           ; AR6 = bit_in >> 1  
                                         ; 2-bits per loop

          MOVW        DP, #_trn_s1_p     
          MOVL        XAR2, #_dnew       ; XAR2 = pts to _dnew[0]                 
          MOVL        XAR1, #_dold       ; XAR1 = pts to _dold[0]    
          MOVL        XAR0,#30           ; used for *+XAR2[AR0] addressing mode  
          MOVL        XAR3, #_tran_hist  ; XAR3 = pts to _tran_hist


          CMP         AH, #2             ; Check for flag
                                         ; If (flag = 2/3), start trace w/ trn_s1_p          
          BF          _cnv_metric_update, LT
          MOVL        XAR3, @_trn_s1_p        

_cnv_metric_update:

        ;Update branch matrices
         VMOV32 VR0, *XAR4++

         VITBM2 VR0 
      || VMOV32 VR2, *XAR1++

        ;0(M=1,1)
         VITDLADDSUB VR4,VR3,VR2,VR0
         
         VITLSEL VR6,VR5,VR4,VR3 
      || VMOV32 VR2, *XAR1++

        ;1(M=1,-1)
         VITDHADDSUB VR4,VR3,VR2,VR0
         
         VITHSEL VR6,VR5,VR4,VR3 
      || VMOV32 VR2, *XAR1++

        ;2(M=1,1)
         VITDLADDSUB VR4,VR3,VR2,VR0 
      || VMOV32 *XAR2++, VR5
      
         VITLSEL VR8,VR7,VR4,VR3 
      || VMOV32 VR2, *XAR1++

        ;3(M=1,-1)  
         VITDHADDSUB VR4,VR3,VR2,VR0 
      || VMOV32 *+XAR2[AR0], VR6

         VITHSEL VR8,VR7,VR4,VR3
      || VMOV32 VR2, *XAR1++ 
         
         ;4(M=-1,-1)  
         VITDLSUBADD VR4,VR3,VR2,VR0 
      || VMOV32 *XAR2++, VR7

         VITLSEL VR6,VR5,VR4,VR3 
      || VMOV32 VR2, *XAR1++
         
        ;5(M=-1,1)  
         VITDHSUBADD VR4,VR3,VR2,VR0 
      || VMOV32 *+XAR2[AR0], VR8

         VITHSEL VR6,VR5,VR4,VR3 
      || VMOV32 VR2, *XAR1++

        ;6(M=-1,-1)  
         VITDLSUBADD VR4,VR3,VR2,VR0 
      || VMOV32 *XAR2++, VR5

         VITLSEL VR8,VR7,VR4,VR3 
      || VMOV32 VR2, *XAR1++
           
        ;7(M=-1,1)  
         VITDHSUBADD VR4,VR3,VR2,VR0 
     ||  VMOV32 *+XAR2[AR0], VR6

         VITHSEL VR8,VR7,VR4,VR3 
     ||  VMOV32 VR2, *XAR1++

        ;8(M=-1,-1)  
         VITDLSUBADD VR4,VR3,VR2,VR0 
     ||  VMOV32 *XAR2++, VR7

         VITLSEL VR6,VR5,VR4,VR3 
     ||  VMOV32 VR2, *XAR1++

       ;9(M=-1,1)  
         VITDHSUBADD VR4,VR3,VR2,VR0 
     ||  VMOV32 *+XAR2[AR0], VR8

         VITHSEL VR6,VR5,VR4,VR3
     ||  VMOV32 VR2, *XAR1++

       ;10(M=-1,-1)  
         VITDLSUBADD VR4,VR3,VR2,VR0
     ||  VMOV32 *XAR2++, VR5

         VITLSEL VR8,VR7,VR4,VR3
     ||  VMOV32 VR2, *XAR1++

       ;11(M=-1,1)  
         VITDHSUBADD VR4,VR3,VR2,VR0
     ||  VMOV32 *+XAR2[AR0], VR6

         VITHSEL VR8,VR7,VR4,VR3
     ||  VMOV32 VR2, *XAR1++

       ;12(M=1,1)
         VITDLADDSUB VR4,VR3,VR2,VR0
     ||  VMOV32 *XAR2++, VR7

         VITLSEL VR6,VR5,VR4,VR3 
     ||  VMOV32 VR2, *XAR1++ 

       ;13(M=1,-1)  
         VITDHADDSUB VR4,VR3,VR2,VR0 
     ||  VMOV32 *+XAR2[AR0], VR8

         VITHSEL VR6,VR5,VR4,VR3
     ||  VMOV32 VR2, *XAR1++

       ;14(M=1,1)
         VITDLADDSUB VR4,VR3,VR2,VR0 
     ||  VMOV32 *XAR2++, VR5

         VITLSEL VR8,VR7,VR4,VR3 
     ||   VMOV32 VR2, *XAR1++

        ;15(M=1,-1)  
         VITDHADDSUB VR4,VR3,VR2,VR0 
     ||  VMOV32 *+XAR2[AR0], VR6

         VITHSEL VR8,VR7,VR4,VR3 
     ||  VMOV32 VR2, *XAR1++

        ;16(M=-1,1)  
         VITDHSUBADD VR4,VR3,VR2,VR0
     ||  VMOV32 *XAR2++, VR7

         VITLSEL VR6,VR5,VR4,VR3 
     ||  VMOV32 VR2, *XAR1++

        ;17(M=-1,-1)  
         VITDLSUBADD VR4,VR3,VR2,VR0
     ||  VMOV32 *+XAR2[AR0], VR8

         VITHSEL VR6,VR5,VR4,VR3
     ||  VMOV32 VR2, *XAR1++

        ;18(M=-1,1)  
         VITDHSUBADD VR4,VR3,VR2,VR0
     ||  VMOV32 *XAR2++, VR5

         VITLSEL VR8,VR7,VR4,VR3 
     ||  VMOV32 VR2, *XAR1++

        ;19(M=-1,-1)  
         VITDLSUBADD VR4,VR3,VR2,VR0
     ||  VMOV32 *+XAR2[AR0], VR6

         VITHSEL VR8,VR7,VR4,VR3 
     ||  VMOV32 VR2, *XAR1++

       ;20(M=1,-1)  
         VITDHADDSUB VR4,VR3,VR2,VR0 
     ||  VMOV32 *XAR2++, VR7

         VITLSEL VR6,VR5,VR4,VR3 
     ||  VMOV32 VR2, *XAR1++

       ;21(M=1,1)
         VITDLADDSUB VR4,VR3,VR2,VR0 
     ||  VMOV32 *+XAR2[AR0], VR8

         VITHSEL VR6,VR5,VR4,VR3
     ||  VMOV32 VR2, *XAR1++

       ;22(M=1,-1)  
         VITDHADDSUB VR4,VR3,VR2,VR0 
     ||  VMOV32 *XAR2++, VR5

         VITLSEL VR8,VR7,VR4,VR3
     ||  VMOV32 VR2, *XAR1++

       ;23(M=1,1)
         VITDLADDSUB VR4,VR3,VR2,VR0
     ||  VMOV32 *+XAR2[AR0], VR6

         VITHSEL VR8,VR7,VR4,VR3 
     ||  VMOV32 VR2, *XAR1++

       ;24(M=1,-1)  
         VITDHADDSUB VR4,VR3,VR2,VR0
     ||  VMOV32 *XAR2++, VR7

         VITLSEL VR6,VR5,VR4,VR3 
     ||  VMOV32 VR2, *XAR1++

       ;25(M=1,1)
         VITDLADDSUB VR4,VR3,VR2,VR0 
     ||  VMOV32 *+XAR2[AR0], VR8

         VITHSEL VR6,VR5,VR4,VR3
     ||  VMOV32 VR2, *XAR1++

       ;26(M=1,-1)  
         VITDHADDSUB VR4,VR3,VR2,VR0 
     ||  VMOV32 *XAR2++, VR5

         VITLSEL VR8,VR7,VR4,VR3 
     ||  VMOV32 VR2, *XAR1++

       ;27(M=1,1)
         VITDLADDSUB VR4,VR3,VR2,VR0
     ||  VMOV32 *+XAR2[AR0], VR6

         VITHSEL VR8,VR7,VR4,VR3 
     ||  VMOV32 VR2, *XAR1++

        ;28(M=-1,1)  
         VITDHSUBADD VR4,VR3,VR2,VR0
     ||  VMOV32 *XAR2++, VR7

         VITLSEL VR6,VR5,VR4,VR3 
     ||  VMOV32 VR2, *XAR1++

        ;29(M=-1,-1)  
         VITDLSUBADD VR4,VR3,VR2,VR0
     ||  VMOV32 *+XAR2[AR0], VR8

         VITHSEL VR6,VR5,VR4,VR3
     ||  VMOV32 VR2, *XAR1++

        ;30(M=-1,1)  
         VITDHSUBADD  VR4,VR3,VR2,VR0
     ||  VMOV32       *XAR2++, VR5

         VITLSEL      VR8,VR7,VR4,VR3
     ||  VMOV32       VR2, *XAR1++

        ;31(M=-1,-1)  
         VITDLSUBADD  VR4,VR3,VR2,VR0
     ||  VMOV32       *+XAR2[AR0], VR6

         VITHSEL      VR8,VR7,VR4,VR3


         VMOV32       *XAR2++, VR7
         VMOV32       *+XAR2[AR0], VR8

        ;Store the Transition bits in Trans[] Array
       
         VMOV32       *XAR3++, VT1
         VMOV32       *XAR3++, VT0

        ;Swap XAR1 and XAR2(old and new state pointers)
         SUBB         XAR1,#64
         MOVL         @XAR7,XAR1
         SUBB         XAR2,#32
         MOVL         @XAR1,XAR2
         MOVL         @XAR2,XAR7
        
        ;set the LOOP count
         BANZ         _cnv_metric_update,AR6--
    

;===============================================================================
; Check if (flag==1), then no trace back
;===============================================================================        

          CMP         *-SP[2], #1         ; If (flag==1), no trace/decode
          BF          _cnv_dec_toggle_trn_s_p, EQ

;===============================================================================
; Check if (flag==0), then trace/decode all current blk
;                          o/p ptr  = data_out[bits_out-6]
;                          loop cnt = bits_out-6
;
; Check if (flag==2), then trace all curr+prv blk
;                          o/p ptr  = data_out[2*bits_out-6]
;                          loop cnt = 2*bits_out-6
;
; Check if (flag==3), then trace all curr+prv blk
;                          o/p ptr  = data_out[bits_out+prv_blk_bits-6]
;                          loop cnt = bits_out+prv_blk_bits-6   
;===============================================================================                
                 
          ZAPA

          CMP         *-SP[2], #0        ; If (flag==0), go trace/decode
          BF          _cnv_dec_ovlp, NEQ
         
          MOV         AL,  *-SP[1]       ; AR6  = #output bits
          MOVZ        AR6, @AL             
          SUBB        XAR6, #7           ;  AR6  = (output_bits - 6) - 1 loop cnt 
          
          LSL         AL, #1             ; 32-bit per output bit
          MOVL        XAR7, #_trn_tmp
          ADDL        XAR7, ACC          ; XAR7 -> trn_tmp[out_bit]  

          RPT         #11                 ; Zero out the last 6 tail bits 
          ||MOV       *--XAR7, AH
                                         ;  XAR7 = pts to data_out[bits_out-6]
                                         ;  If (flag == 0)

        ;====================================================================== 
        ; Trace back all, 1 shot, to RAM (32-bit word per output bit)
        ;======================================================================    
         VCLEAR      VR0
         VCLEAR      VR1         
_tb_loop1:                                   ; 
         ;;For Viterbi stage = k
         VMOV32      VT0, *--XAR3
         VMOV32      VT1, *--XAR3
         VTRACE      *--XAR7,VR0,VT0,VT1
            
         BANZ        _tb_loop1, AR6--
        
         BF          _cnv_dec_op, UNC    ; exit

;===============================================================================
; Trace back (overlap) 
;===============================================================================   

_cnv_dec_ovlp:
                                          ; If (flag=2/3) 
          MOV         AL,   *-SP[1]       ; AR6  = #output bits
          MOVZ        AR6,  @AL           ;  output_bits 
          SUBB        XAR6, #1            ;  AR6  = (output_bits - 6) - 1 loop cntr 
 
          MOVL        XAR7, #_trn_tmp
          
          VCLEAR      VR0
          VCLEAR      VR1          
          CMP         *-SP[2], #3        ; If (flag==2), go trace/decode, regular block
          BF          _tb_loop_ovlp1, NEQ 
          
                                         ; If (flag==3), go trace/decode, irregular block
          ADDB        XAR6, #58          ; add the previous block, compensate for subb 1
          MOV         AL, @AR6
          AND         AL, #0x1F         ; find modulo of 32 and use it as the first trace back
          
          MOV         @AR0, AL          ; accumulate 32 bits for output 
          
_tb_loop_ovlp0: 
          VMOV32      VT0,  *--XAR3
          VMOV32      VT1,  *--XAR3
          VTRACE      VR1,VR0,VT0,VT1
          
          BANZ        _tb_loop_ovlp0_end, AR0--
                                         ; after 32 bits are accumulated output
          VMOV32       *XAR7, VR1
          FLIP32                                 ; flip 32bits in VR1 to ACC
         
          MOVL         *--XAR5, ACC        ; output
          MOVB         XAR0, #31         ; accumulate 32 bits for output         
          
_tb_loop_ovlp0_end:   
          MOV          AL, AR6
          CMPB         AL, #58
          BF          _tb_loop_ovlp0_end1, NEQ 
 
          MOVW        DP,   #_trn_w1_p   ; switch to previous tran_hist   
          MOVL        XAR3, @_trn_w1_p                
_tb_loop_ovlp0_end1:
          BANZ        _tb_loop_ovlp0, AR6--
          
          BF          _cnv_dec_toggle_trn_s_p, UNC

_tb_loop_ovlp1:                                   ; 
          ;;For Viterbi stage = k
          VMOV32      VT0, *--XAR3
          VMOV32      VT1, *--XAR3
          VTRACE      VR1,VR0,VT0,VT1
            
          BANZ        _tb_loop_ovlp1, AR6--
         
        ;====================================================================== 
        ; Second half of the block actually produces decode bits to o/p when ovlp
        ;======================================================================                 

          MOVW        DP,   #_trn_w1_p      
          MOVL        XAR3, @_trn_w1_p
 
        ;======================================================================     
          .align       2            
          RPTB         _tb_loop_ovlp2, #12         ; the first word, the other 3 bits are already in VR1 from  _tb_loop_ovlp1
          VMOV32       VT0,  *--XAR3
          VMOV32       VT1,  *--XAR3
          VTRACE       VR1,VR0,VT0,VT1
          VMOV32       VT0,  *--XAR3
          VMOV32       VT1,  *--XAR3
          VTRACE       VR1,VR0,VT0,VT1
_tb_loop_ovlp2:

          FLIP32                                 ; flip 32bits in VR1 to ACC

		  .if (VIT_OUT_ODD == 0)
          MOVL         *+XAR5[2], ACC                ; output
		  .else

	  	  ADDB         XAR5, #1
          MOVB         *+XAR5[6], AH.MSB
          SUBB         XAR5, #1
	
          MOVB         *+XAR5[7], AH.LSB
          MOVB         *+XAR5[6], AL.MSB
          MOVB         *+XAR5[5], AL.LSB
          .endif
         
         ;======================================================================                 
          .align       2            
          RPTB         _tb_loop_ovlp3, #15         ; the second word 
          VMOV32       VT0,  *--XAR3
          VMOV32       VT1,  *--XAR3
          VTRACE       VR1,VR0,VT0,VT1
          VMOV32       VT0,  *--XAR3
          VMOV32       VT1,  *--XAR3
          VTRACE       VR1,VR0,VT0,VT1
_tb_loop_ovlp3:

          FLIP32                                 ; flip 32bits in VR1 to ACC

          .if (VIT_OUT_ODD == 0)
          MOVL         *XAR5, ACC                ; output

          .else
          MOVB         *+XAR5[4], AH.MSB
          MOVB         *+XAR5[3], AH.LSB
          MOVB         *+XAR5[2], AL.MSB
          MOVB         *+XAR5[1], AL.LSB        
          .endif
;====================================================================== 
; Toggle  trn_w1_p/trn_w2_p
;======================================================================
_cnv_dec_op:
          MOVL       XAR3, @_trn_w1_p
          MOVL       XAR4, @_trn_w2_p
          MOVL       @_trn_w1_p, XAR4
          MOVL       @_trn_w2_p, XAR3
        
;====================================================================== 
; Toggle trn_s1_p/trn_s2_p 
;======================================================================
_cnv_dec_toggle_trn_s_p:
                
          MOVL       XAR3, @_trn_s1_p
          MOVL       XAR4, @_trn_s2_p
          MOVL       @_trn_s1_p, XAR4
          MOVL       @_trn_s2_p, XAR3
          SUBB       SP, #4   ; restore stack pointer

          
         POP XAR3
         POP XAR2
         POP XAR1
         POP XAR0
        
         LRETR

;/*! State Metrics Rescale
; *
; * \param none
; *
; * Rescale the state metrics by finding the lowest metric and dividing the
; * rest by it. This prevents overflow between successive decoder stages
; *
; * \return none
; */    
_cnvDecMetricRescale_asm:

          PUSH        XAR2               ; save on stack
          SETC        SXM,  OVM          ; sign extention mode
          MOV         AL,   #0x7FFF      ; minimal metrics
          MOVL        XAR4, #_dold

          RPT         #63
          ||MIN       AL, *XAR4++        ; find the minimal

          MOVL        XAR4, #_dold
          MOV         AR2, #3            ; offset for 64 samples
          
_cnvDecMetricRescale:
          SUB         *XAR4++, AL
          SUB         *XAR4++, AL
          SUB         *XAR4++, AL
          SUB         *XAR4++, AL
          SUB         *XAR4++, AL
          SUB         *XAR4++, AL
          SUB         *XAR4++, AL
          SUB         *XAR4++, AL
          SUB         *XAR4++, AL
          SUB         *XAR4++, AL
          SUB         *XAR4++, AL
          SUB         *XAR4++, AL
          SUB         *XAR4++, AL
          SUB         *XAR4++, AL
          SUB         *XAR4++, AL
          SUB         *XAR4++, AL

          BANZ        _cnvDecMetricRescale, AR2--
          
          POP         XAR2
          LRETR
;############################################################################
;  Close the Doxygen group.
;//! @}
;############################################################################

;;  End of File
