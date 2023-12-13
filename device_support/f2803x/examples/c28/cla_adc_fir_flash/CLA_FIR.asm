
;// Include variables and constants that will be shared in the
;// C28x C-code and CLA assembly code.  This is accomplished by
;// using .cdecls to include a C-code header file that contains
;// these variables and constants

      .cdecls   C,LIST,"CLAShared.h"

;// To include an MDEBUGSTOP (CLA breakpoint) as the first instruction
;// of each task, set CLA_DEBUG to 1.  Use any other value to leave out
;// the MDEBUGSTOP instruction.

CLA_DEBUG .set  1

;// CLA code must be within its own assembly section and must be
;// even aligned.  Note: since all CLA instructions are 32-bit
;// this alignment naturally occurs and the .align 2 is most likely
;// redundant

       .sect        "Cla1Prog"
_Cla1Prog_Start
       .align       2


_Cla1Task1:
    MSTOP
    MNOP
    MNOP
    MNOP
_Cla1T1End:


_Cla1Task2:
    MSTOP
    MNOP
    MNOP
    MNOP
_Cla1T2End:

_Cla1Task3:
    MSTOP
    MNOP
    MNOP
    MNOP
_Cla1T3End:
    

_Cla1Task4:
    MSTOP
    MNOP
    MNOP
    MNOP
_Cla1T4End:
    
    
_Cla1Task5:  
    MSTOP
    MNOP
    MNOP
    MNOP
_Cla1T5End:
    
_Cla1Task6:
    MSTOP
    MNOP
    MNOP
    MNOP
_Cla1T6End:    

_Cla1Task7:

        .if CLA_DEBUG == 1
        MDEBUGSTOP
       .endif

;//==============================================
;// CLA Task 7
;//
;// This task:
;// 
;// 1. Is triggered by the early ADC interrupt. 
;//    This interrupt occurs at the end of the
;//    sample & hold window 
;// 2. Reads the ADC RESULT1 register as soon
;//    as it is available
;// 3. It will then run a FIR filter and places the 
;//    result into VoltFilt.
;// 4. The main CPU will take an interrupt at the
;//    end of the task.  It will log the
;//    ADC RESULT1 register for comparison as 
;//    well as the CLA generated VoltFilt value
;// 
;// Before starting the ADC conversions, force 
;// Task 8 to initialize the filter states and 
;// coefficients.
;//
;//==============================================


; X and A are arrays of 32-bit float (i.e. 2 words)
; Use these defines to make the code easier to read
;
_X4  .set _X+8  
_X3  .set _X+6  
_X2  .set _X+4  
_X1  .set _X+2  
_X0  .set _X+0  

_A4  .set _A+8  
_A3  .set _A+6  
_A2  .set _A+4  
_A1  .set _A+2  
_A0  .set _A+0 

; CLA 5-tap FIR Filter
;
; Coefficients A[0, 1, 2, 3, 4]
; Data         X[0, 1, 2, 3, 4] (Delay Line - X[0] is newest value)
;
; Equations
;
; Y = A4 * X4      First Calculation of sum of products.
; X4 = X3          X4 can now be updated, because it has been used.
; Y = Y + A3 * X3  Second product, 1st add.
; X3 = X2          X3 update
; Y = Y + A2 * X2  Third product, 2nd add.
; X2 = X1
; Y = Y + A1 * X1  Fourth product, 3rd add.
; X1 = X0
; Y = Y = A0 * X0
;
    MMOV32     MR0,@_X4                      ;1 Load MR0 with X4
    MMOV32     MR1,@_A4                      ;2 Load MR1 with A4
    MNOP                                     ;3 Wait till I8 to read result
    MNOP                                     ;4 Wait till I8 to read result
    MNOP                                     ;5 Wait till I8 to read result
    MNOP                                     ;6 Wait till I8 to read result
    MNOP                                     ;7 Wait till I8 to read result
    MUI16TOF32 MR2,  @_AdcResult.ADCRESULT1  ;8 Read ADCRESULT1 and convert to float

    MMPYF32    MR2, MR1, MR0                 ; MR2 (Y) = MR1 (A4) * MR0 (X4)
 || MMOV32     @_X0, MR2

    MMOVD32    MR0,@_X3                      ; Load MR0 with X3, Load X4 with X3
    MMOV32     MR1,@_A3                      ; Load MR1 with A3
                                          
    MMPYF32    MR3, MR1, MR0                 ; MR3 (Y) = MR1 (A3) * MR0 (X3)
 || MMOV32     MR1,@_A2                      ; Load MR1 with A2
    MMOVD32    MR0,@_X2                      ; Load MR0 with X2, Load X3 with X2

    MMACF32    MR3, MR2, MR2, MR1, MR0       ; MR3 = A3*X3 + A4*X4
 || MMOV32     MR1,@_A1                      ; MR2 = MR1 (A2) * MR0 (X2)
    MMOVD32    MR0,@_X1                      ; Load MR0 with X1, Load X2 with X1

    MMACF32    MR3, MR2, MR2, MR1, MR0       ; MR3 = A2*X2 + (A3*X3 + A4*X4)
 || MMOV32     MR1,@_A0                      ; MR2 = MR1 (A1) * MR0 (X1)
    MMOVD32    MR0,@_X0                      ; Load MR0 with X0, Load X1 with X0 

    MMACF32    MR3, MR2, MR2, MR1, MR0       ; MR3 = A1*X1 + (A2*X2 +A3*X3 + A4*X4)
 || MMOV32     MR1,@_A0                      ; MR2 = MR1 (A0) * MR0 (X0)

    MADDF32    MR3, MR3, MR2                 ; MR3 = A0*X0 + (A1*X1 + A2*X2 +A3*X3 + A4*X4)

	MF32TOUI16 MR2, MR3                      ; Get back to Uint16 value
    MMOV16     @_VoltFilt, MR2               ; Output
	MSTOP                                    ; End task
_Cla1T7End:
          
_Cla1Task8:

;==============================================
; This task initializes the filter input delay 
; line (X0 to X4) to zero 
;==============================================
    .if CLA_DEBUG == 1
    MDEBUGSTOP
    .endif
    MMOVIZ       MR0, #0.0
    MUI16TOF32   MR0, MR0          
    MMOV32       @_X0, MR0       
    MMOV32       @_X1, MR0       
    MMOV32       @_X2, MR0       
    MMOV32       @_X3, MR0       
    MMOV32       @_X4, MR0
    MSTOP
_Cla1T8End:

    
    
_Cla1Prog_End:


    .end
    .include "CLAShared.h"



