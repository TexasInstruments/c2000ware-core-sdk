; TI File $Revision: /main/3 $
; Checkin $Date: November 1, 2010   13:05:11 $
; ========================================================================
;  This software is licensed for use with Texas Instruments C28x
;  family DSCs.  This license was provided to you prior to installing
;  the software.  You may review this license by consulting a copy of
;  the agreement in the doc directory of this library.
; ------------------------------------------------------------------------
;          Copyright (C) 2010-2011 Texas Instruments, Incorporated.
;                          All Rights Reserved.
; ========================================================================
;
;
; Module definition for external referance
; ###########################################################################
; 
; 
; ###########################################################################

a)	Open Matlab command window, click “fdatool”, the FDATool GUI will pop out.
	Select the parameters, filter type and other options which you prefer, click 
	Design Filter. The design process is finished.
b)	Go to Targets-> Generate C header;
c)	After b), the Generate C header dialogue box pops out and in ‘Data type to use 
	in export’, check ‘Export as’ Signed 16-bit or 32-bit integer (depends on 16 bit 
	FIR or 32 bit FIR). Click ‘Generate’;
d)	Save the header file. The coefficient can directly port to ‘fft.h’.
