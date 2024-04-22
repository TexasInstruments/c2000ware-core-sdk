***********************************************************************
* Function: _IQNtoa_get_frac_c
*
* Description: Called by _IQNtoa().  Not for user use.
*
* DSP: TMS320F28x
*
* Author: David M. Alter
*
* Include files: stdio.h
*
* Function Prototype: extern char _IQNtoa_get_frac_c(unsigned long);
*
* Usage: character = _IQNtoa_get_frac_c(value);
*
* Input Parameters:
*    value = fraction in I0Q32 format
*
* Return Value:
*    character = the 1st base-10 digit in the fraction
*
* Notes:
*  1) This is an internal function to the IQmath library.  It is not
*     intended to be called by the user.
*
* History: December 23, 2004 - original (D. Alter)
*
***********************************************************************

		.def _IQNtoa_get_frac_c
		.sect "IQmath"

_IQNtoa_get_frac_c:

		MOVB	XAR0, #10				;XAR0 = 10
		MOVL	XT, XAR0				;XT = 10
		QMPYUL	P, XT, @ACC				;P = XT*ACC upper 32-bits
		MOVL	@ACC, P					;ACC = the value we want
		LRETR							;return

		.end
		
;----------------------------------------------------------------------
; End of file
;----------------------------------------------------------------------
