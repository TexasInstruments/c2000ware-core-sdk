;;*****************************************************************************
;;  \file source/vcu0/vcu0_cfft_utils.asm
;; 
;;  \brief  Initialization and auxilliary functions used in the fft calculations
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
      .cdecls   C,LIST,"VCU0_FFT.h" ;needed as the table CFFT16_TF is defined in fft.h
;;*****************************************************************************
;; global defines

	  .if __TI_EABI__
      .asg CFFT16_TF, _CFFT16_TF
	  .asg cfft16_init,_cfft16_init
      .asg cfft16_brev,_cfft16_brev
      .asg cfft16_tbl_brev,_cfft16_tbl_brev
      .asg cfft16_flip_re_img,_cfft16_flip_re_img
      .asg cfft16_flip_re_img_conj,_cfft16_flip_re_img_conj
      .asg cfft16_unpack_asm,_cfft16_unpack_asm
      .asg cifft16_pack_asm,_cifft16_pack_asm      
	  .endif
;############################################################################
;
;/*! \page CFFT16_UTILS (Initialization and Auxilliary Functions)
; The following initialization and utility functions are available:
; - void cfft16_init(void *fft_handle)
; - void cfft16_brev(void *fft_handle)
; - void cfft16_flip_re_img(void *fft_handle)
; - void cfft16_flip_re_img_conj(void *fft_handle)
; - void cfft16_unpack_asm(void *fft_handle)
; - void cifft16_pack_asm(void *fft_handle)
;*/
;############################################################################
;/*! \defgroup CFFT_128_FN (128pt CFFT Routines)
;  @{  .....starts the defintion block
;*/
		.global _cfft16_init,_cfft16_brev,_cfft16_tbl_brev
		.global _cfft16_flip_re_img,_cfft16_flip_re_img_conj
		.global _cfft16_unpack_asm,_cifft16_pack_asm
;//###########################################################################
     
		.text

;/*! Twiddle Factor Table Initialization
; *
; * \param Handle to the structure, cfft16_t
; *
; * Initializes the tfptr to the start of the twiddle factor
; * table in memory
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
; * \return none
; */                   
_cfft16_init:            
; Twiddle factor Initialisation
            MOVL    XAR5,#_CFFT16_TF     ;
            MOVL    *+XAR4[4],XAR5          ; tfptr->CFFT16_TF
            LRETR

;/*! Bit-Reversed Indexing
; *
; * \param Handle to the structure, cfft16_t
; *
; * Rearranges the input data in bit-reveresed index format. If the number
; * of FFT stages, the data is bit-reversed into the work buffer and then copied
; * back to the input buffer. In this respect the bit reversal is considered to be
; * in-place. For an odd number of stages the bit-reversed output is placed 
; * in the work buffer (off-place). The FFT (not the bit reversal function) 
; * will then transfer the data back to the input buffer pointed to by ipcbptr
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
; * \return none
; */ 
_cfft16_brev:  
            PUSH    XAR0
            PUSH    XAR1            ; Context Save
            PUSH    XAR2
            PUSH    XAR3 
          
            MOVL    XAR2,*XAR4      ; XAR2=ipcbptr, input array
            MOVL    XAR3, *+XAR4[2] ; XAR3=work buffer
            MOVZ    AR0,*+XAR4[6]   ; load FFT size N
            MOV     ACC,*+XAR4[6]   ; load FFT size N-1
            ASR     AL,  #2         ; assuming the input is multiple of 2
            MOV     AR1, AL
			SUBB    XAR1, #1
           
            .align (2)    
            RPTB    _brev_loop, AR1
			
			LPADDR                  ; Make sure AMODE = 1
            .lp_amode               ; Tell assembler that AMODE = 1   
			
            NOP     *,ARP2          ; Set ARP pointer to point to XAR2
            MOVL    ACC,*++,ARP3    ; Load ACC with location pointed to by XAR2,
                                    ; post-increment XAR2 and Set ARP pointer to XAR3
            MOVL    *BR0++,ACC,ARP2 ; Store ACC into location pointed to by XAR3,
                                    ; Set ARP pointer to point to XAR2
            MOVL    ACC,*++,ARP3    ; Load ACC with location pointed to by XAR2,
                                    ; post-increment XAR2 and set ARP pointer to XAR3
            MOVL    *BR0++,ACC,ARP2 ; Store ACC into location pointed to by XAR3,
                                    ; Set ARP pointer to point to XAR2
            MOVL    ACC,*++,ARP3    ; Load ACC with location pointed to by XAR2,
                                    ; post-increment XAR2 and set ARP pointer to XAR3
            MOVL    *BR0++,ACC,ARP2 ; Store ACC into location pointed to by XAR3,
                                    ; Set ARP pointer to point to XAR2
            MOVL    ACC,*++,ARP3    ; Load ACC with location pointed to by XAR2,
                                    ; post-increment XAR2 and set ARP pointer to XAR3
            MOVL    *BR0++,ACC,ARP2 ; Store ACC into location pointed to by XAR3,
			                        ; Set ARP pointer to point to XAR2
_brev_loop:
            C28ADDR                 ; Return to C28x address mode
            .c28_amode
			
            MOVB    XAR1, #7
            MOV     ACC,*+XAR4[AR1]  ; load nstage
            ANDB    AL, #0x1         ; Test odd or even
            SBF     _copy_loop, NEQ  ; if odd, do not copy, FFT will transfer data back to the input buffer
                                     ; if even, copy to the input buffer
            MOVL    XAR2, *+XAR4[0]  ; load FFT input buffer base pointer
            MOVL    XAR3, *+XAR4[2]  ; XAR3=work buffer
            MOV     ACC,*+XAR4[6]    ; load FFT size N-1
            ASR     AL,  #3          ; assuming the input is multiple of 8
            MOV     AR1, AL
			SUBB    XAR1, #1
			
            .align (2)
            RPTB    _copy_loop, AR1
            MOVL    ACC, *XAR3++
            MOVL    *XAR2++, ACC
            MOVL    ACC, *XAR3++
            MOVL    *XAR2++, ACC
            MOVL    ACC, *XAR3++
            MOVL    *XAR2++, ACC
            MOVL    ACC, *XAR3++
            MOVL    *XAR2++, ACC
            MOVL    ACC, *XAR3++
            MOVL    *XAR2++, ACC
            MOVL    ACC, *XAR3++
            MOVL    *XAR2++, ACC
            MOVL    ACC, *XAR3++
            MOVL    *XAR2++, ACC
            MOVL    ACC, *XAR3++
            MOVL    *XAR2++, ACC
_copy_loop:
                                    
            POP     XAR3
			POP     XAR2
			POP     XAR1
			POP		XAR0

            LRETR

         
;/*! Table based Bit Reversal
; *
; * \param Handle to the structure, cfft16_t
; *
; * Uses the table, pointed to by brevptr, to rearrange the input data
; * in bit reversed index format 
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
; * \return none
; */ 
_cfft16_tbl_brev:  
            PUSH    XAR0
            PUSH    XAR1            ; Context Save
            PUSH    XAR2
            PUSH    XAR3 
            PUSH    XAR4                       

          
            MOVL    XAR2, *+XAR4[0]     ; load FFT input buffer base pointer
            MOVL    XAR3, *+XAR4[2]     ; load FFT work buffer pointer  
            MOV     AR0, #10          
            MOVL    XAR7, *+XAR4[AR0]     ; load bit reversal table pointer

            .align (2)
            RPTB    _bit_reversal_loop, #15
            MOVZ    AR0, *XAR7++
            MOVL    ACC, *XAR2++
            MOVL    *+XAR3[AR0], ACC
            MOVZ    AR1, *XAR7++
            MOVL    ACC, *XAR2++
            MOVL    *+XAR3[AR1], ACC
            MOVZ    AR0, *XAR7++
            MOVL    ACC, *XAR2++
            MOVL    *+XAR3[AR0], ACC
            MOVZ    AR1, *XAR7++
            MOVL    ACC, *XAR2++
            MOVL    *+XAR3[AR1], ACC
_bit_reversal_loop: 
            MOVL    XAR2, *+XAR4[0]     ; load FFT input buffer base pointer
            MOVL    XAR3, *+XAR4[2]     ; load FFT work buffer pointer  
            .align (2)
            RPTB    _copy_loop2, #7
            MOVL    ACC, *XAR3++
            MOVL    *XAR2++, ACC
            MOVL    ACC, *XAR3++
            MOVL    *XAR2++, ACC
            MOVL    ACC, *XAR3++
            MOVL    *XAR2++, ACC
            MOVL    ACC, *XAR3++
            MOVL    *XAR2++, ACC 
            MOVL    ACC, *XAR3++
            MOVL    *XAR2++, ACC
            MOVL    ACC, *XAR3++
            MOVL    *XAR2++, ACC
            MOVL    ACC, *XAR3++
            MOVL    *XAR2++, ACC
            MOVL    ACC, *XAR3++
            MOVL    *XAR2++, ACC                       
_copy_loop2:                    
            POP     XAR4                       
            POP     XAR3
			POP     XAR2
			POP     XAR1
			POP     XAR0

            LRETR

;/*! Flip real and imaginary parts of complex number
; *
; * \param Handle to the structure, cfft16_t
; *
; * This functions is needed in the computation of real FFTs to ensure that
; * the real part of the complex number always ends up at the high word of 
; * a 32 bit address
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
; * \return none
; */ 

_cfft16_flip_re_img:   
          PUSH        XAR1      
          PUSH        XAR2
          
          MOVL        XAR2, *+XAR4[0]     ; load FFT input buffer base pointer
          MOVL        ACC, *+XAR4[6]    ; 
          ASR         AL,  #2            ; assuming the input is multiple of 4
          MOV         AR1, AL
          SUB         AR1, #1 

          .align (2)
          RPTB        FLIP_LOOP, AR1
          MOV         AH, *+XAR2[0];
          MOV         AL, *+XAR2[1];
          MOVL        *XAR2++, ACC
          
          MOV         AH, *+XAR2[0];
          MOV         AL, *+XAR2[1];
          MOVL        *XAR2++, ACC
          
          MOV         AH, *+XAR2[0];
          MOV         AL, *+XAR2[1];
          MOVL        *XAR2++, ACC
          
          MOV         AH, *+XAR2[0];
          MOV         AL, *+XAR2[1];
          MOVL        *XAR2++, ACC
FLIP_LOOP:
          
          POP         XAR2
          POP         XAR1
          
          LRETR
          
;/*! Flip real and imaginary parts of complex number and conjugate
; *
; * \param Handle to the structure, cfft16_t
; *
; * This functions is needed in the computation of real IFFTs to ensure that
; * the real part of the complex number always ends up at the high word of 
; * a 32 bit address
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
; * \return none
; */ 
_cfft16_flip_re_img_conj:   
          PUSH        XAR1      
          PUSH        XAR2
          
          MOVL        XAR2, *+XAR4[0]     ; load FFT input buffer base pointer
          MOVL        XAR1, *+XAR4[6]    ; 
          SUB         AR1, #1 
FLIP_LOOP_CONJ:
          MOV         AH, *+XAR2[0];
          NEG         AH                 ; conjugate the imaginary part
          MOV         AL, *+XAR2[1];
          MOVL        *XAR2++, ACC
          BANZ        FLIP_LOOP_CONJ,AR1--
          
          POP         XAR2
          POP         XAR1
          
          LRETR
          
;/*! Real FFT Unpack
; *
; * \param Handle to the structure, cfft16_t
; *
; * When using an N/2 pt complex FFT to compute the N-pt real FFT. The
; * result of the complex FFT must be unpacked to get the real value. Refer
; * to http://www.engineeringproductivitytools.com/stuff/T0001/PT10.HTM
; * for more info
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
; * Registers used
; *   AR1: FFT size
; *   XAR2: FFT buffer upper pointer
; *   XAR3:  FFT buffer lower pointer
; *   XAR4:  FFT handle pointer
; *   XAR5
; *   XAR6:  twiddle factor pointer
; * 
; * \return none
; */ 
_cfft16_unpack_asm:   
          PUSH        XAR1      
          PUSH        XAR2
          PUSH        XAR3
		  
          ADDB        SP, #18              ; allocate stack space for temperary variables
          VMOV32      *-SP[6], VR0         ; save VRx to stack
          VMOV32      *-SP[8], VR1
          VMOV32      *-SP[10], VR2
          VMOV32      *-SP[12], VR3
          VMOV32      *-SP[14], VR4
          VMOV32      *-SP[16], VR5
          VMOV32      *-SP[18], VR6
		  
          SETC        SXM                  ; sign extension mode
          ZAPA
                    
          VSATON                    	   ; VSTATUS.SAT = 1
          VRNDON                           ; rounding on
          VSETSHR     #17	               ; VSTATUS.SHIFTR = RIGHT_SHIFT, scale by 4
          VSETSHL     #15                  ; VSTATUS.SHIFTL = LEFT_SHIFT
          
          MOVL        XAR2, *+XAR4[0]      ; load FFT input buffer base pointer
         
          MOVL        XAR6, *+XAR4[4]      ; load twiddle factor
          
          MOVL        ACC, *+XAR4[6]       ; load number of points
          MOV         PL, AL               ; save length
          LSR         AL, #1
          SUB         AL, #2               ; loop N/2-1 times
          MOVZ        AR1, AL              
 
          MOVL        ACC, P      
          LSL         ACC, #1              ; sin/cos pair         
          ADDL        ACC, XAR6
          MOVL        XAR6, ACC            ; twiddle factor offset by N         
          
          MOVL        ACC, P               ; load number of points
          LSL         ACC, #1              ; real/imag pair        
          ADDL        ACC, XAR2            ; calculate lower half 
          SUB         ACC, #2
          MOVL        XAR3, ACC
          
          ; process the first point X(0)
          MOVL        ACC, *XAR2
          ADD         AH, AL
          ADD         AH, #1
          ASR         AH, #1               ; (real+imag)/2 with rounding
          MOV         AL, #0
          MOVL        *XAR2++, ACC
          .align   (2)
          RPTB      _UNPACK_LOOP, AR1      ; loop for pairs 
          
          MOVL        ACC, *XAR6++         ; load the twiddle factor  
          NEG         AL                   ; conjugate
          MOV         *-SP[2], AH          ; flip sin and cos
          MOV         *-SP[1], AL 
          VMOV32      VR0, *-SP[2]         

          VMOV32      VR2, *XAR2           ; load the upper point
          VMOV32      VR1, *XAR3           ; load the lower point
          
          VITDLADDSUB	VR4, VR3, VR2, VR1 ; Fe(k) = {Z(k)+Z(N/2-k)*}/2
          VMOV32       *-SP[2], VR4
          VMOV32       *-SP[4], VR3
          
          VITDHADDSUB	VR4, VR3, VR2, VR1  ; Fo(k) = -j{Z(k)-Z(N/2-k)*}/2
          VMOV16        VR4L, *-SP[2]       ; reassemble Fe(k) and Fo(k)
          VMOV16        VR3L, *-SP[4]
          
          VMOV32        *-SP[2], VR3
          VMOV32        VR1, *-SP[2]
          
          VCMPY         VR3, VR2, VR1, VR0  ; F(k) = Fe(k) - W(N,k)Fo(k)
          VNOP
          VCDADD16      VR5, VR4, VR3, VR2  
          VCDSUB16      VR6, VR4, VR3, VR2
       
          VMOV32      *XAR3, VR5             ; lower half conjugate
          MOV         AL, *XAR3
          NEG         AL
          MOV         *XAR3, AL
          SUBB        XAR3, #2              ; move to the next lower point
          VMOV32      *XAR2++, VR6  
_UNPACK_LOOP: 
          MOVL        ACC, *XAR3            ; the center point, X(N/2) = 0.5*conj(X(N/2))
          NEG         AL
          ASR         AL, #1                
          ASR         AH, #1
          MOVL        *XAR3, ACC
          

          VMOV32      VR0, *-SP[6]        ; restore VR registers
          VMOV32      VR1, *-SP[8]
          VMOV32      VR2, *-SP[10]
          VMOV32      VR3, *-SP[12]
          VMOV32      VR4, *-SP[14]
          VMOV32      VR5, *-SP[16]
          VMOV32      VR6, *-SP[18]
          SUBB        SP, #18            ; restore SP 
		  
          POP         XAR3
          POP         XAR2
          POP         XAR1
          
          LRETR
                   
;/*! complex IFFT pack
; *
; * \param Handle to the structure, cfft16_t
; *
; * When calculating the IFFT of a Real FFT, the data must be packed before 
; * using the complex IFFT to get the result. Refer to 
; * http://www.engineeringproductivitytools.com/stuff/T0001/PT10.HTM
; * for more info
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
; * Registers used
; *   AR1: FFT size
; *   XAR2: FFT buffer upper pointer
; *   XAR3:  FFT buffer lower pointer
; *   XAR4:  FFT handle pointer
; *   XAR5
; *   XAR6:  twiddle factor pointer
; * 
; * \return none
; */ 
_cifft16_pack_asm:   
          PUSH        XAR1      
          PUSH        XAR2
          PUSH        XAR3
          ADDB        SP, #18              ; allocate stack space for temperary variables
          VMOV32      *-SP[6], VR0         ; save VRx to stack
          VMOV32      *-SP[8], VR1
          VMOV32      *-SP[10], VR2
          VMOV32      *-SP[12], VR3
          VMOV32      *-SP[14], VR4
          VMOV32      *-SP[16], VR5
          VMOV32      *-SP[18], VR6
          
          SETC        SXM                  ; sign extension mode
          ZAPA
                    
          VSATON                    	   ; VSTATUS.SAT = 1
          VRNDON                           ; rounding on
          VSETSHR     #17	               ; VSTATUS.SHIFTR = RIGHT_SHIFT, scale by 4
          VSETSHL     #15                  ; VSTATUS.SHIFTL = LEFT_SHIFT
          
          MOVL        XAR2, *+XAR4[0]      ; load FFT input buffer base pointer
         
          MOVL        XAR6, *+XAR4[4]      ; load twiddle factor
          
          MOVL        ACC, *+XAR4[6]       ; load number of points
          MOV         PL, AL               ; save length
          LSR         AL, #1
          SUB         AL, #2               ; loop N/2-1 times
          MOVZ        AR1, AL              
 
          MOVL        ACC, P      
          LSL         ACC, #1              ; sin/cos pair         
          ADDL        ACC, XAR6
          MOVL        XAR6, ACC            ; twiddle factor offset by N         
          
          MOVL        ACC, P               ; load number of points
          LSL         ACC, #1              ; real/imag pair        
          ADDL        ACC, XAR2            ; calculate lower half 
          SUB         ACC, #2
          MOVL        XAR3, ACC
          
          ; process the first point X(0)
          MOVL        ACC, *XAR2           ; conjugate
          NEG         AL
          MOVL        *XAR2++, ACC
          
          .align      (2)
          ; loop for pairs 
          RPTB      _PACK_LOOP, AR1        
          
          MOVL        ACC, *XAR6++         ; load the twiddle factor  
          MOV         *-SP[2], AH          ; flip sin and cos
          MOV         *-SP[1], AL 
          VMOV32      VR0, *-SP[2]         

          VMOV32      VR2, *XAR2           ; load the upper point
          VMOV32      VR1, *XAR3           ; load the lower point
          
          VITDLADDSUB	VR4, VR3, VR2, VR1 ; Fe(k) = {Z(k)+Z(N/2-k)*}/2
          VMOV32       *-SP[2], VR4        ; VR4L=VR2L-VR1L=SP[1]=imag(Fe(k))
          VMOV32       *-SP[4], VR3        ; VR3L=VR2L+VR1L=SP[3]=imag(Fo(k))
          
          VITDHADDSUB	VR4, VR3, VR2, VR1 ; Fo(k) = -j{Z(k)-Z(N/2-k)*}/2
          VMOV16        VR4L, *-SP[2]      ; reassemble Fe(k) and Fo(k) VR4H =VR2H+VR1H= real(Fe(k))
          VMOV16        VR3L, *-SP[4]      ; VR3H = VR2H-VR1H=real(Fo(k))
          
          VMOV32        *-SP[2], VR3
          VMOV32        VR1, *-SP[2]
          
          VCMPY         VR3, VR2, VR1, VR0 ; F(k) = Fe(k) - W(N,k)Fo(k)
          VNOP
          VCDADD16      VR5, VR4, VR3, VR2  
          VCDSUB16      VR6, VR4, VR3, VR2
       
       
          VMOV32      *XAR2, VR5           ; upper half conjugate
          MOVL        ACC, *XAR2
          NEG         AL
          MOVL        *XAR2++, ACC
          VMOV32      *XAR3, VR6  
          SUBB        XAR3, #2             ; move to the next lower point
          
_PACK_LOOP: 
          MOVL        ACC, *XAR3           ; the center point, X(N/2) = 0.5(X(N/2))
          ASR         AL, #1                
          ASR         AH, #1
          MOVL        *XAR3, ACC
		  
          VMOV32      VR0, *-SP[6]         ; restore VR registers
          VMOV32      VR1, *-SP[8]
          VMOV32      VR2, *-SP[10]
          VMOV32      VR3, *-SP[12]
          VMOV32      VR4, *-SP[14]
          VMOV32      VR5, *-SP[16]
          VMOV32      VR6, *-SP[18]
          SUBB        SP, #18              ; restore SP
		  
          POP         XAR3
          POP         XAR2
          POP         XAR1
          
          LRETR
;############################################################################
;  Close the Doxygen group.
;//! @}
;############################################################################

;; End of file
