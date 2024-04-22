;;###########################################################################
;;
;; FILE:	atoIQN.asm
;;
;; TITLE:	C Callable IQ Math Function
;;
;;###########################################################################
;;
;; Ver  |     Date    | Who   | Description of changes
;; =====|=============|=======|==============================================
;; 1.2  | 11 Oct 2001 | A. T. | Original Release.
;; -----|-------------|-------|----------------------------------------------
;; 1.3  | 19 Nov 2001 | A. T. | No changes.
;; -----|-------------|-------|----------------------------------------------
;; 1.4  | 17 May 2002 | A. T. | Fixed bug (thanks Settu) with input char
;;      |             |       | range comparison.
;; -----|-------------|-------|----------------------------------------------
;;      |             |       |
;;
;;###########################################################################

;;===========================================================================
;; Function:   _atoIQN
;;===========================================================================
;;
;; C Usage:    extern long _atoIQN(const char *st, long q_value);
;;
;;---------------------------------------------------------------------------
;;
;; On Entry:   XAR4 = pointer to character string
;;             ACC  = q_value 
;;
;; Regs Used:  ACC, P, XT
;;             XAR7, XAR6, XAR5
;;
;; On Exit:    ACC  = IQ value from string (0 if an error occured)
;;
;; Q Range:    30 to 1
;;
;;---------------------------------------------------------------------------
;; Algorithm:  The input string must only contain decimal characters
;;             '0' to '9' and the characters '-' for negative value
;;             if applicable and '.' character for delimiting integer and
;;             fraction components. Some examples of valid inputs are:
;;
;;                        12.23456
;;                       -12.23456
;;                         0.2345
;;                         0.0
;;                         0
;;                       127
;;                       -89 
;;              
;;             If the input string converts to a number greater then
;;             the max/min values for the given Q value, then the returned
;;             value will be limited to the min/max values.
;;
;;             If the string contains illegal characters, it will return 
;;             the value zero.
;;
;;---------------------------------------------------------------------------
;; Benchmark:
;;      Cycles = Can be approximately from 200 to 800 cycles based on number 
;;               of characters in string.
;;
;;===========================================================================

		.sect	"IQmath"
		.def 	_atoIQN	
_atoIQN:
		NEG		ACC				; ACC = - q_value
		ADDB	ACC,#32			; ACC = 32 - q_value
		MOV		AH,@AL			; AH  = 32 - q_value
		MOVL	*SP++,ACC		; Save on stack
		ADDB	SP,#8
		CMP		@AH,#31			; Check to make sure that q_value range
		SB		_atoIQerror,GT	; is 30 to 1
		CMP		@AH,#2
		SB		_atoIQerror,LT
		
		MOVB	ACC,#0
		MOVL	*-SP[8],ACC		; I64l
		MOVL	*-SP[6],ACC		; I64h, I64 = integer portion
		MOVL	*-SP[4],ACC		; F64l
		MOVL	*-SP[2],ACC		; F64h, F64 = fraction portion
		MOV		AL,#0x999A
		MOV		AH,#0x1999
		MOVL	XAR7,@ACC		; XAR7 = 0.1 * 2^32 = scale frac
		MOVB	XAR6,#10		; XAR6 = 10         = scale int
		ZAPA					; ACC, P = 0
		CLRC	TC				; TC = 0 = sign flag (default +ve)

_atoIQloop:
		MOVZ	AR0,*XAR4++		; AR0 = char
		CMP		@AR0,#0x00
		SB		_atoIQend,EQ	; Exit if zero (end of string)
		CMP		@AR0,#'-'		
		SB		_atoIQneg,EQ	; Set sign flag if char == "-"
		CMP		@AR0,#'.'
		SB		_atoIQdot,EQ	; End of integer component if char == "."
		SUB		@AR0,#'0'
		SB		_atoIQerror,LT	
		CMP		@AR0,#9
		SB		_atoIQerror,GT	; Error if char not between "0".."9"

		MOVL	XT,@XAR6
		IMPYXUL	P,XT,*-SP[8]
		ADDUL	P,@XAR0
		MOVL	ACC,@P
		QMPYXUL	P,XT,*-SP[8]
		MOVL	*-SP[8],ACC
		IMPYL	ACC,XT,*-SP[6]			
		ADDCL	ACC,@P				
		MOVL	*-SP[6],ACC		; I64 = I64*10 + char dec value

		SB		_atoIQloop,UNC	

;-------------------------------------------------------------------------

		; Search for end of string and count frac characters:
_atoIQdot:
		MOVB	XAR5,#0			; clear frac character counter
_atoIQdotloop:
		INC		@AR5			; Increment character counter
		MOVZ	AR0,*XAR4++		; AR0 = char
		CMP		@AR0,#0x00
		SB		_atoIQfrac,EQ	; Exit if end of string	
		SUB		@AR0,#'0'
		SB		_atoIQerror,LT	
		CMP		@AR0,#9
		SB		_atoIQerror,GT	; Error if char not between "0".."9"
		SB		_atoIQdotloop,UNC
		
;-------------------------------------------------------------------------
		
_atoIQfrac:
		SUBB	XAR4,#1
		CMP		@AR5,#10
		SB		_atoIQfracloop,LT
		SUBB	XAR5,#10		
		MOVL	ACC,@XAR4
		SUBL	ACC,@XAR5
		MOVL	@XAR4,ACC
_atoIQfracloop:
		MOVZ	AR0,*--XAR4		; AR0 = char
		CMP		@AR0,#'.'
		SB		_atoIQend,EQ	; Exit if char == "."		
		SUB		@AR0,#'0'
		SB		_atoIQerror,LT	
		CMP		@AR0,#9
		SB		_atoIQerror,GT	; Error if char not between "0".."9"

		MOVL	ACC,*-SP[2]
		MOV		AH,@AR0
		MOVL	*-SP[2],ACC
		MOVL	XT,@XAR7
		QMPYXUL	P,XT,*-SP[4]
		IMPYL	ACC,XT,*-SP[2]
		ADDUL	P,@ACC
		MOVL	*-SP[4],P
		MPYB	P,T,#0
		QMPYL	ACC,XT,*-SP[2]
		ADDCL	ACC,@P				
		MOVL	*-SP[2],ACC		; F64 = F64*0.1 + char dec value

		SB		_atoIQfracloop,UNC

;-------------------------------------------------------------------------

_atoIQneg:
		SB		_atoIQerror,TC	; Error if more then one -ve sign detected
		SETC	TC				; Set -ve sign value
		SB		_atoIQloop,UNC	

;-------------------------------------------------------------------------
		
_atoIQerror:
		MOV		AH,#0x0000
		MOV		AL,#0x0000		; Return zero if error detected
		SUBB	SP,#10
		LRETR

;-------------------------------------------------------------------------

_atoIQend:
		MOVL	P,*-SP[4]
		MOVL	ACC,*-SP[2]
		LSR64	ACC:P,#16
		MOVL	ACC,*-SP[8]		; ACC = int, P =frac
		
		MOVL	XT,*-SP[10]		; T = 32 - q_value
		LSR64	ACC:P,T			; P = IQ value, ACC = overflow
		SB		_atoIQendPos,NTC
		NEG64	ACC:P	
_atoIQendPos:
		; Set saturation limits:
		MOV		*-SP[8],#0xFFFF
		MOV		*-SP[7],#0x7FFF
		MOV		*-SP[6],#0x0000
		MOV		*-SP[5],#0x0000
		MOV		*-SP[4],#0x0000
		MOV		*-SP[3],#0x8000
		MOV		*-SP[2],#0xFFFF
		MOV		*-SP[1],#0xFFFF
		; Saturate result:
		MINL	ACC,*-SP[6]
		MINCUL	P,*-SP[8]
		MAXL	ACC,*-SP[2]
		MAXCUL	P,*-SP[4]
		; Return value in ACC:
		MOVL	ACC,@P
		SUBB	SP,#10
		LRETR
					
;;###########################################################################
;; No More.
;;###########################################################################
