;;*****************************************************************************
;;! \file source/vcu2/vcu2_cfft_utils.asm
;;!
;;! \brief  FFT Utility Routines
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
;;*****************************************************************************
;; global defines
;;*****************************************************************************
;; FFT Routine defines

;; Argument structure defines
ARG_INBUFFER        .set    0
ARG_OUTBUFFER       .set    2
ARG_TFTABLE         .set    4
ARG_NSAMPLES        .set    6
ARG_NSTAGES         .set    7
ARG_TFSKIP          .set    8


;; Stack defines
;;
;;   |_______|
;;   |_______|<- Stack Pointer(SP) <---SP
;;   |_______|<- STK_VR3L     (SP-1)
;;   |_______|<- STK_VR4L     (SP-2)
;;
LOCAL_FRAME_SIZE    .set    2
STK_VR3L            .set    1
STK_VR4L            .set    2

;;*****************************************************************************
;; macros
;;*****************************************************************************
;;
;; MACRO   : 'CFFT_CONTEXT_SAVE'
;; SIZE    : Number of WORDS/Number of Cycles 4
;; USAGE   : Called on entry into FFT routine
;;
CFFT_CONTEXT_SAVE    .macro
    PUSH      XAR1
    PUSH      XAR2
    PUSH      XAR3
    ADDB      SP, #LOCAL_FRAME_SIZE              ; allocate stack space for local frame
    .endm
;;
;; MACRO   : 'CFFT_CONTEXT_RESTORE'
;; SIZE    : Number of WORDS/Number of Cycles 4
;; USAGE   : Called on exit from FFT routine
;;
CFFT_CONTEXT_RESTORE    .macro
    SUBB      SP, #LOCAL_FRAME_SIZE              ; deallocate stack space for local frame
    POP       XAR3
    POP       XAR2
    POP       XAR1
    .endm

;;*****************************************************************************
;; globals
;;*****************************************************************************
    .global _CFFT_unpack
    .global _CFFT_pack
    .global _CFFT_conjugate
    .ref    _vcu0_twiddleFactors
;;*****************************************************************************
;; function definitions
;;*****************************************************************************
    .text
;;
;; \brief Unpack the complex FFT output to get the FFT of two interleaved
;;        real sequences
;;
;; In order to get the FFT of a real N-pt sequences, we treat the input as
;; an N/2 pt complex sequence, take its complex FFT, use the following properties
;; to get the N-pt fourier transform of the real sequence
;; \f[
;; FFT_{n}(k,f) = FFT_{N/2}(k,f_{e}) + e^{\frac{-j2{\pi}k}{N}}FFT_{N/2}(k,f_{o})
;; \f]
;; where \f$f_{e}\f$ is the even elements, \f$f_{o}\f$ the odd elements and
;; \f[
;; F_{e}(k) = \frac{Z(k) + Z(\frac{N}{2}-k)^{\ast}}{2}
;; F_{o}(k) = -j\frac{Z(k) - Z(\frac{N}{2}-k)^{\ast}}{2}
;; \f]
;; We get the first N/2 points of the FFT by combining the above two equations
;; \f[
;; F(k) = F_{e}(k) + e^{\frac{-j2{\pi}k}{N}}F_{o}(k)
;; \f]
;;
;; \param Handle to the structure, CFFT_Obj(passed in XAR4)
;; - *+XAR4[0]:  int16_t *pInBuffer -> input pointer
;; - *+XAR4[2]:  int16_t *pOutBuffer -> work(Output) buffer pointer
;; - *+XAR4[4]:  int16_t *pTwiddleFactors-> twiddle factor table pointer
;; - *+XAR4[6]:  int16_t nSamples-> Number of data points
;; - *+XAR4[7]:  int16_t nStages-> Number of FFT stages
;; - *+XAR4[8]:  int16_t twiddleSkipStep-> Twiddle factor table search step
;;
;; \note
;; - This function actively sets CPACK=1 style complex packing
;;   i.e. [Lo:Hi] => [Real:Imag], the input data must also be arranged in this format
;; - Sign extension is automatically done for right shift operations
;; - VSTATUS.RND=1, rounding is done for the right shift operation
;; - OVFR is set if signed overflow is detected for add/sub calculation in which destination is VRxL
;; - OVFI is set if signed overflow is detected for add/sub calculation in which destination is VRxH
;; - 16-bit signed results (before the shift right) are saturated if SAT = 1
;;
;; \return FFT of the input in the output buffer pointed to by CFFT_Obj.pOutBuffer
;; \sa http://www.engineeringproductivitytools.com/stuff/T0001/PT10.HTM for the entire
;;  derivation
;; 
;; Register Usage:
;;   XAR0:  Twiddle Factor table index (increments in steps of "skip_step")
;;         / Index into the structure
;;   XAR1:  Repeat block index
;;   XAR2:  Points to the beginning of the CFFT buffer
;;   XAR3:  Points to the end of the CFFT buffer
;;   XAR4:  Pointer to the CFFT structure
;;   XAR5:  
;;   XAR6:  Points to the twiddle factor table
;;   XAR7:
;;

_CFFT_unpack:
	;; NOTE: N is the number of complex samples
    CFFT_CONTEXT_SAVE
    SETC      SXM                                ; Set sign extension mode
    ZAPA
    VSETCPACK                                    ; VSTATUS.CPACK = 1
    VSATON                    	                 ; Turn on saturation
    VRNDON                                       ; Turn on rounding
    VSETSHR   #17	                             ; VSTATUS.SHIFTR = RIGHT_SHIFT (divide by 4)
    VSETSHL   #15                                ; VSTATUS.SHIFTL = LEFT_SHIFT
    MOVL      XAR2, *+XAR4[ARG_OUTBUFFER]        ; XAR2 -> Complex FFT output buffer
    MOVL      XAR6, #_vcu0_twiddleFactors+160    ; XAR6 -> Twiddle factor table(VCU-0) for stage 9
    MOVL      ACC, *+XAR4[ARG_NSAMPLES]          ; ACC := N (number of complex samples)
    MOV       PL, AL                             ; PL  := N
    LSR	      AL, #1                             ; AL  := N/2 (the mid point)
    SUB       AL, #2                             ; AL  := (N/2 - 1) - 1(for RPTB)
    MOVZ      AR1, AL                            ; AR1 := (N/2 - 2)
    MOV       ACC, PL << 1                       ; ACC := 2N
    ADDL      ACC, XAR2                          ; ACC := 2N + ptr->output buffer (in words)
    MOVL      XAR3, ACC                          ; XAR3 -> end of output buffer

    ;; Process the first point X(0)
    MOVL      ACC, *XAR2                         ; ACC := X(0)
    ADD       AL, AH                             ; AL := Xr(0) + Xi(0)
    ADD       AL, #1                             ; AL := Xr(0) + Xi(0) + 1
    ASR       AL, #1                             ; AL := (Xr(0) + Xi(0) + 1)/2
    MOV       AH, #0
    MOVL      *XAR2++, ACC                       ; X(0) := (Xr(0) + Xi(0) + 1)/2
	;; Setup twiddle factor index
	MOV		  AR0, #ARG_TFSKIP
	MOV		  AH, *+XAR4[AR0]				     ; AH := Twiddle Skip Factor
	LSR		  AH, 1                              ; We want to go through all the W_N(n,k) twiddles and not the W_N/2(n,k) twiddles
	MOV	      AR0, AH                            ; AR0 := AH, we want to start with the twiddle W(n,1)
    ;; Process points X(1)..X(N/2-1)
    ;;
    ;; W(k)   = e^(-j*2*pi*k/N)
    ;;        = cos(2*pi*k/N) - j sin(2*pi*k/N)
    ;; -jW(k) = e^-j*pi/2 x e^(-j*2*pi*k/N)
    ;; W'(k)  = -sin(2*pi*k/N) + j(-cos(2*pi*k/N))
    ;; Take the original twiddle, flip Re and Im parts
    ;; and conjugate
    ;; W'(k) = (flip(W(k))*
    ;;
    ;; F_e(k) = 1/2{Z(k) + Z(N/2-k)*}
    ;;        = 1/2{(VR2L+VR1L) + j(VR2H-VR1H)}
    ;; F_o(k) = -j{Z(k) - Z(N/2-k)*}/2
    ;;        = -j{(VR2L-VR1L)+j(VR2H+VR1H)}/2
    ;; F_o(k) = -jF'_o(k)
    ;; F(k)   = F_e(k) + W(k)F_o(k)
    ;;        = F_e(k) - jW(k)F'_o(k)
    ;;        = F_e(k) + W'(k)F'_o(k), for k = 0:N/2-1
    ;; F(k)   = (F_e(k) - jW(k)F'_o(k))*
    ;;        =  F_e(k) + jW(k)F'_o(k)
    ;;        =  F_e(k) - W'(k)F'_o(k), for k = N/2+1:N-1
    .align    2
    RPTB      _CFFT_unpack_loop, AR1
    VMOV32    VR0, *+XAR6[AR0]                   ; VR0 := Twiddle Factor
    ADD		  AR0, AH							 ; AR0 += AH (incrementing TF offset by the skip step)
	VCFLIP	  VR0								 ; VR0L + jVR0H -> VR0H + jVR0L
	;VCCON	  VR0								 ; W'(k) = VR0H - jVR0L / done with the VCCMPY later
    VMOV32    VR2, *XAR2                         ; Load the upper point
    VMOV32    VR1, *--XAR3                       ; Load the N/2 - k point
    VITDLADDSUB VR4, VR3, VR2, VR1               ; [VR3L:VR3H] := [VR2L+VR1L:VR2H-VR1L]
                                                 ; [VR4L:VR4H] := [VR2L-VR1L:VR2H+VR1L]
    VMOV16    *-SP[STK_VR3L], VR3L               ; Save VR3L, discard VR3H
    VMOV16    *-SP[STK_VR4L], VR4L               ; Save VR4L, discard VR4H
    VITDHADDSUB VR4, VR3, VR2, VR1               ; [VR3L:VR3H] := [VR2L+VR1H:VR2H-VR1H]
                                                 ; [VR4L:VR4H] := [VR2L-VR1H:VR2H+VR1H]
    VMOV16    VR3L, *-SP[STK_VR3L]               ; Discard VR3L, load with previous VR3L
    VMOV16    VR4L, *-SP[STK_VR4L]               ; Discard VR4L, load with previous VR4L
    VMOV32    VR1, VR4                           ; VR1 := VR4
    VMOV32    VR4, VR3                           ; VR4 := F_e(k)
    VCCMPY    VR3, VR2, VR1, VR0                 ; VR3+jVR2 =    (VR0L*VR1L + VR0H*VR1H)
    VNOP                                         ;            + j(VR0L*VR1H - VR0H*VR1L)
    VCDADD16  VR5, VR4, VR3, VR2                 ; [VR5L:VR5H] = [(VR4L<<SHL+VR3)>>SHR:(VR4H<<SHL+VR2)>>SHR]
    VCDSUB16  VR6, VR4, VR3, VR2                 ; [VR6L:VR6H] = [(VR4L<<SHL-VR3)>>SHR:(VR4H<<SHL-VR2)>>SHR]
    VCCON	  VR6
    VMOV32    *XAR2++, VR5                       ; Store (F_e(k) + W'(k)F'_o(k))
    VMOV32    *XAR3, VR6                         ; Store (F_e(k) - W'(k)F'_o(k)) at the back end of buffer

_CFFT_unpack_loop: 

    ;; Process point F(N/4)
    ;; F(N/4) = 1/2({Z(N/4) +Z(N/2-N/4)*} -je^(-j*2*pi*N/4N){Z(N/4) -Z(N/2-N/4)*})
    ;;        = 1/2({Z(N/4) +Z(N/4)*} -je^(-jpi/2){Z(N/4) -Z(N/4)*})
    ;;        = 1/2({2 Re(Z(N/4)) } -j(-j){2 j Im(Z(N/4)) })
    ;;        = Re(Z(N/4)) - j Im(Z(N/4))
    ;;        = F(N/4)*
    MOVL      ACC, *--XAR3                       ; Load the point F(N/4)
    NEG       AH
    ASR       AL, #1
    ASR       AH, #1
    MOVL      *XAR3, ACC
    
    VCLRCPACK                                    ; VSTATUS.CPACK = 0
    CFFT_CONTEXT_RESTORE
    LRETR
    
;;*****************************************************************************
;;
;; \brief Take the complex conjugate of the entries in an array of complex
;; numbers
;;
;; \param pBuffer Pointer to the buffer of complex data to be conjugated
;; \paran[in] size Size of the buffer (multiple of 2 32-bits locations)
;;
;; Register Usage:
;;   XAR0:
;;   XAR1: counter of the repeat block
;;   XAR2:
;;   XAR3:
;;   XAR4: Pointer to the complex buffer
;;   XAR5:
;;   XAR6:
;;   XAR7:
;;     AH:
;;     AL: Size of buffer(argument to the function)
_CFFT_conjugate:
	PUSH      XAR1
	MOV		  AH, AL							 ; AH := size of buffer
	ANDB	  AL, #0x0001						 ; AL := remainder
	TBIT	  AL, #0							 ; Is the 0th bit 1? Set TC :  Clear TC
	ASR		  AH, #1							 ; AH := size of buffer / 2
	MOVZ	  AR1, AH
	SUBB	  XAR1, #1							 ; counter for RPTB
	.align 	  2
	RPTB      _CFFT_conjugate_loop, AR1
	VMOV32	  VR0, *+XAR4[0]
	VCCON	  VR0
	VMOV32	  *XAR4++, VR0
	NOP
	VMOV32	  VR0, *+XAR4[0]
	VCCON	  VR0
	VMOV32	  *XAR4++, VR0
	NOP
_CFFT_conjugate_loop:
	SB		  _CFFT_conjugate_end, NTC           ;If TC Clear then  jump to end
	VMOV32	  VR0, *+XAR4[0]                     ; else do one last complex conjugate
	VCCON	  VR0
	VMOV32	  *XAR4++, VR0
_CFFT_conjugate_end:
	POP       XAR1
	LRETR

;;*****************************************************************************
;; \brief Pack the input prior to running the inverse complex FFT to get
;;        the real inverse FFT
;;
;; In order to reverse the process of the forward real FFT,
;;
;; \f[
;; F_{e}(k) = \frac{F(k) + F(\frac{N}{2}-k)^{\ast}}{2}
;; F_{o}(k) = \frac{F(k) - F(\frac{N}{2}-k)^{\ast}}{2} e^{\frac{j2{\pi}k}{N}}
;; \f]
;; where \f$f_{e}\f$ is the even elements, \f$f_{o}\f$ the odd elements.
;; The array for the IFFT then becomes:
;; \f[
;; Z(k) = F_{e}(k) + jF_{o}(k), \ k = 0...\frac{N}{2}-1
;; \f]
;;
;; \param Handle to the structure, CFFT_Obj(passed in XAR4)
;; - *+XAR4[0]:  int16_t *pInBuffer -> input pointer
;; - *+XAR4[2]:  int16_t *pOutBuffer -> work(Output) buffer pointer
;; - *+XAR4[4]:  int16_t *pTwiddleFactors-> twiddle factor table pointer
;; - *+XAR4[6]:  int16_t nSamples-> Number of data points
;; - *+XAR4[7]:  int16_t nStages-> Number of FFT stages
;; - *+XAR4[8]:  int16_t twiddleSkipStep-> Twiddle factor table search step
;;
;; \note
;; - This function actively sets CPACK=1 style complex packing
;;   i.e. [Lo:Hi] => [Real:Imag], the input data must also be arranged in this format
;; - Sign extension is automatically done for right shift operations
;; - VSTATUS.RND=1, rounding is done for the right shift operation
;; - OVFR is set if signed overflow is detected for add/sub calculation in which destination is VRxL
;; - OVFI is set if signed overflow is detected for add/sub calculation in which destination is VRxH
;; - 16-bit signed results (before the shift right) are saturated if SAT = 1
;; - This is an in-place algorithm; the routine writes the output to the input buffer itself
;;
;; \return packed input ready for the IFFT in the input buffer pointed 
;;         to by CFFT_Obj.pInBuffer
;; \sa http://www.engineeringproductivitytools.com/stuff/T0001/PT10.HTM for the entire
;;  derivation
;; 
;; Register Usage:
;;   XAR0:  Index into the structure
;;   XAR1:  RPTB counter
;;   XAR2:  Pointer to the input buffer
;;   XAR3:  Points to lower half of the input buffer
;;   XAR4:  Pointer to the CFFT structure
;;   XAR5:  
;;   XAR6:  Pointer to twiddle factor table
;;   XAR7:
;;
_CFFT_pack:
    CFFT_CONTEXT_SAVE
    VSETCPACK                                    ; set CPACK bit to 1 [Lo:Hi] = [Re:Im]
    SETC      SXM                                ; Turn on sign extension mode
    ZAPA
    VSATON                                       ; VSTATUS.SAT = 1
    VRNDON                                       ; VSTATUS.RND = 1
    VSETSHR   #17                                ; VSTATUS.SHIFTR = RIGHT_SHIFT, scale by 4
    VSETSHL   #15                                ; VSTATUS.SHIFTL = LEFT_SHIFT
    MOVL      XAR2, *+XAR4[ARG_INBUFFER]         ; load input buffer base pointer
    MOV       AL, *+XAR4[ARG_NSAMPLES]           ; load number of points (#complex_points)
    MOV       PL, AL                             ; save length
    LSR       AL, #1
    SUB       AL, #2                             ; loop N/2-1 times (the -2 accounts for RPTB which loops N + 1 times)
    MOVZ      AR1, AL
    
    MOV       ACC, PL << 1                       ; load number of points
    ADDL      ACC, XAR2                          ; calculate lower half 
    MOVL      XAR3, ACC             

    MOVL      XAR6, #_vcu0_twiddleFactors+160    ; XAR6 -> Twiddle factor table(VCU-0) for stage 9

    ; process the first point X(0)
    VMOV32    VR0, *XAR2                         ; VR0 := X(0)
    VCCON     VR0                                ;[VR0L:VR0H] = [VR0L:-VR0H] ([Re:-Im])
    VMOV32    *XAR2++, VR0                       ; Store back to memory
                                               
    ; set up twiddle factor index              
    MOV       AR0, #ARG_TFSKIP               
    MOV       AH, *+XAR4[AR0]                    ; AH := Twiddle Skip Factor
    LSR		  AH, #1                             ; Reduce skip factor by a factor of 2 (skip factor calculated
                                                 ; based on 1024 entries, vcu0 twiddles only have 512 entries max)    
    MOV       AR0, AH                            ; AR0 := AH, we want to start with the twiddle W(n,1)
    
    ;; Process points X(1)..X(N/2-1)
    ;;
    ;; W(k)   = e^(+j*2*pi*k/N)
    ;; jW(k)  = j(cos(2*pi*k/N) + jsin(2*pi*k/N))
    ;;  W'(k) = -sin(2*pi*k/N) + j(cos(2*pi*k/N))
    ;; Take the original twiddle, conjugate it then flip Re and Im parts
    ;; W'(k) = (flip(W*(k))
	;;
    ;; F_e(k) = 1/2{F(k) + F(N/2-k)*}
    ;;        = 1/2{(VR2L+VR1L) + j(VR2H-VR1H)}
    ;; F_o'(k)= F_o(k)W'(k)
    ;;        = +j/2{F(k) - F(N/2-k)*}e^{j*2*pi*k/N}
    ;;        = 1/2{F(k) - F(N/2-k)*}W'(k)
    ;;        = 1/2{(VR2L-VR1L) + j(VR2H+VR1H)}*{VR0L + jVR0H}
    ;; Z(k)   = F_e(k) + jF_o(k) or F_e(k) + F_o'(k)
    ;;
    .align    2                         
    RPTB      _CFFT_pack_loop, AR1                   
                                               
    VMOV32    VR0, *+XAR6[AR0]                   ; VR0 := Twiddle Factor
    ;VCCON	  VR0                                ; VR0L + jVR0H -> VR0L - jVR0H
	VCFLIP	  VR0								 ; VR0L - jVR0H -> -VR0H + jVR0L
    ADD       AR0, AH                            ; AR0 += AH (incrementing TF offset by the skip step)
                                               
    VMOV32    VR2, *XAR2                         ; Load the upper point
    VMOV32    VR1, *--XAR3                       ; Load the N/2 - k point 
                                               
    VITDLADDSUB VR4, VR3, VR2, VR1               ;[VR3L:VR3H] := [VR2L+VR1L:VR2H-VR1L]
                                                 ;[VR4L:VR4H] := [VR2L-VR1L:VR2H+VR1L]
    VMOV16    *-SP[STK_VR3L], VR3L               ; Save VR3L, discard VR3H
    VMOV16    *-SP[STK_VR4L], VR4L               ; Save VR4L, discard VR4H
    VITDHADDSUB VR4, VR3, VR2, VR1               ;[VR3L:VR3H] := [VR2L+VR1H:VR2H-VR1H]
                                                 ;[VR4L:VR4H] := [VR2L-VR1H:VR2H+VR1H]
    VMOV16    VR3L, *-SP[STK_VR3L]               ; Discard VR3L, load with previous VR3L
    VMOV16    VR4L, *-SP[STK_VR4L]               ; Discard VR4L, load with previous VR4L
    VMOV32    VR1, VR4                           ; VR1 := VR4 (F_o(k))
    VMOV32    VR4, VR3                           ; VR4 := F_e(k)
                                                 ; Calculate F_o'(k) = F_o(k)*(jW(k))
    VCMPY    VR3, VR2, VR1, VR0                  ; VR3+jVR2 =    (VR0L*VR1L + VR0H*VR1H)
    VNOP                                         ;            + j(VR0L*VR1H - VR0H*VR1L)
    VCDSUB16  VR6, VR4, VR3, VR2                 ;[VR6L:VR6H] = [(VR4L<<SHL-VR3)>>SHR:(VR4H<<SHL-VR2)>>SHR]
    VCDADD16  VR5, VR4, VR3, VR2                 ;[VR5L:VR5H] = [(VR4L<<SHL+VR3)>>SHR:(VR4H<<SHL+VR2)>>SHR]
    VMOV32    *XAR3, VR6
    VCCON	  VR5                                ; VR5L + jVR5H -> VR5L - jVR5H
    VMOV32    *XAR2++, VR5

_CFFT_pack_loop: 
    ;; Process point X(N/2)
    ;; X(N/2) = 0.5*X(N/2)
    VMOV32    VR1, *XAR2                         ; the center point, X(N/2) = 0.5(X(N/2))
    VCSHR16   VR1 >> #1                          
    VMOV32    *XAR2, VR1
    CFFT_CONTEXT_RESTORE
    LRETR
;; End of file
