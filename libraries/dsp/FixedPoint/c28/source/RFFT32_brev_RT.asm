;;;#############################################################################
;;! \file source/RFFT32_brev_RT.asm
;;!
;;! \brief  Real-Time storage of acquired data samples in bit reversed order
;;!
;;! \date   Jan 11, 2010
;;! 
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
;;
;;*****************************************************************************
;; includes
;;*****************************************************************************
;;
;;*****************************************************************************
;; globals
;;*****************************************************************************
            .if __TI_EABI__
            .asg RFFT32_brev_RT, _RFFT32_brev_RT
            .endif

            .def    _RFFT32_brev_RT
;;==============================================================================   
;; Routine Type  : C Callable        
;; Description   :
;; void RFFT32_brev_RT(RFFT32_Handle) 
;; This function acquires N samples in bit-reversed order to cater to the complex
;; FFT computation. The buffer should be aligned to 2N words
;;==============================================================================  
;; typedef struct{<------------ XAR4
;;  int16_t acqflag;             // + 0  Acquisition flag
;;  int16_t count;               // + 1  Integer counter
;;  int32_t input;               // + 2  Input data
;;  int32_t *tempptr;            // + 4  Temporary Pointer
;;  int32_t *buffptr;            // + 6  Pointer to the destination buffer
;;  int16_t size;                // + 7  Number of samples
;;  void (*update)(void *);      // + 8  Pointer to the update function
;; }RFFT32_brev_RT_ACQ;  
;;==============================================================================  
;;
                
_RFFT32_brev_RT:
    MOV       ACC,*XAR4++       ; ACC=acqflag
    SBF       noacq,EQ  
                            
    MOV       ACC,*XAR4++       ; ACC=count
    SBF       acqover,EQ        ; if count=0, acquisition is complete
                
    DEC       *--XAR4           ; count=count-1
    MOV       ACC,*+XAR4[7]<<1  ; ACC=2*size
    MOVL      XAR0,ACC          ; AR0=2*size            
                
    MOVL      XAR5,*+XAR4[3]    ; XAR5=tempptr
    MOVL      ACC,*+XAR4[1]     ; ACC=input
    MOVL      *XAR5,ACC         ; *tempptr=input
    NOP       *BR0++    
    MOVL      *+XAR4[3],XAR5    
noacq:          
    LRETR       
                
acqover:        
    MOV       ACC,*+XAR4[6] 
    MOV       *--XAR4,ACC       ; count=size
    MOV       *--XAR4,#0        ; acqflag=0
                
    MOVL      XAR5,*+XAR4[6]    ; XAR5=buffptr
    MOVL      *+XAR4[4],XAR5    ; tempptr=buffptr
    LRETR

;;#############################################################################
;;  End of File
;;#############################################################################
