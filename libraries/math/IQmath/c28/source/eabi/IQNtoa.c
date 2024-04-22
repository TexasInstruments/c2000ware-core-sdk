/**********************************************************************
* Function: IQNtoa()
*
* Description: Converts IQ number to an ASCII string
*
* DSP: TMS320F28x
*
* Author: David M. Alter
*
* Include files: stdio.h
*
* Function Prototype: int __IQNtoa(char *, const char *, long, int)
*
* Usage: error = __IQNtoa(char *string, const char *format,
*                                               long x, int qvalue);
*
* Input Parameters:
*    string = output string
*    format = conversion format.  Must be of form "%xx.yyf" with
*             xx and yy at most 2 characters in length.
*               Examples: "%10.12f", "%2.4f", "%11.6f"
*             Maximum supported integer field width (xx) is 11
*             (including any negative sign).  This captures the full
*             integer range for I2Q30 to I31Q1 numbers.
*         x = input value (IQ format)
*    qvalue = IQ format of x (e.g., 24 means I8Q24)
*
* Return Value:
*     error = error code:
*               0 = no error
*               1 = iwidth too small to hold integer characters
*               2 = illegal format specified
*
* Notes:
*
* 1) Leading zeros are not printed for the integer part.  Hence, format
*    specifies the maximum width of the integer field.  The field may
*    be smaller.
* 2) The output string is terminated with the null character.
* 3) The integer width in "format" includes the negative sign for
*    negative numbers, e.g. -12.3456 is "%3.5f"
* 4) The decimal width in "format" includes the decimal point, e.g.
*    -12.3456 is "%3.5f"
* 5) "string" must be large enough to hold the output (including the
*    negative sign, and the terminating null character).  The program
*    does not check for overrun.  Memory corruption will occur if
*    "string" is too small.
* 6) A non-zero return value indicates that the output string is invalid.
* 7) Benchmark is roughly 200 to 800 cycles, depending on the format and
*    the input value.
*
* History: December 23, 2004 - original (D. Alter)
*             : April 27, 2019 - fixed bug for not handling 0x80000000 (Arav)
**********************************************************************/

// Function prototypes
extern char _IQNtoa_get_frac_c(unsigned long);


/**********************************************************************/
#pragma CODE_SECTION(__IQNtoa, "IQmath");

int __IQNtoa(char *string, const char *format, long x, int qvalue)
{
	unsigned long uval;				// working variable
	char *bufptr;					// buffer pointer
	char buf[11];					// temporary char buffer (worst case length)
	int count;						// conversion character counter
	int error = 0;					// error value
	int neg = 0;					// negative flag
	int iwidth;						// integer format width
	int dwidth;						// decimal format width
	int scale;						// format parsing scaling value


//--------------------------------------------------------------------
// Parse the format parameter
//

// Check if x == 0x80000000 and return error if yes 
	if(x == 0x80000000) return(2);		// error: cannot handle 0x80000000

// Check that 1st character is "%"
	if(*format++ != '%') return(2);		// error: missing the leading '%'

// Extract iwidth
	if(*format == '.') return(2);		// error: no iwidth field
	count = 0;							// zero the counter
	scale = 1;							// init scale
	iwidth = 0;							// init iwidth

	while(*format != '.')				// find the '.'
	{
		count++;						// increment the count
		iwidth = iwidth*scale + (*format++ - '0');
		scale = scale * 10;

		// If we don't find the '.' after, say, 4 counts, something is wrong
		if(count > 2) return(2);		// error: iwidth field too many characters
	}

	if(iwidth > 11) return(2);			// error: iwidth too large
	if(iwidth < 0) return(2);			// error: iwidth negative

// Extract dwidth
	format++;							// advance format off the '.'
	if(*format == 0) return(2);			// error: no dwidth field
	count = 0;							// zero the counter
	scale = 1;							// init scale
	dwidth = 0;							// init dwidth

	while((*format != 'f') && (*format != 'F'))	// find the conversion character
	{
		count++;						// increment the count
		dwidth = dwidth*scale + (*format++ - '0');
		scale = scale * 10;

		// If we don't find the conversion character after, say, 4 counts, something is wrong
		if(count > 2) return(2);		// error: dwidth field too large
	}

	if(dwidth < 0) return(2);			// error: dwidth negative

// Check that the next character is the NULL string terminator
	if(*++format != 0) return(2);		// error: missing null terminator


//--------------------------------------------------------------------
// Check for negative value
//
	if(x < 0)
	{
		x = -x;						// make it positive
		neg = 1;					// set negative flag
	}


//--------------------------------------------------------------------
// Process the integer part
//

// Isolate the integer part
	uval = x >> qvalue;

// Convert the integer part
	bufptr = buf;					// init the pointer
	count = 0;						// zero the counter

	do
	{
		*bufptr++ = (uval % 10) + '0';		// extract the next character
		count++;							// increment the counter
	} while(uval = uval/10);				// remove the character value from uval

	if(neg)
	{
		*bufptr++ = '-';					// insert a '-'
		count++;							// increment the counter
	}

	if(count > iwidth)
	{
		count = iwidth;						// set count = iwidth
		error = 1;							// error: integer format too small
	}

	while(count--)
	{
		*string++ = *--bufptr;				// copy the character to the string
	}


//--------------------------------------------------------------------
// Process the fractional part
//
	if(dwidth > 0)
	{

	// Insert the decimal point
		*string++ = '.';								// insert the decimal point
		dwidth--;										// decrement the fraction length

	// Isolate the fractional part
		uval = x << (32-qvalue);						// I0Q32 format

	// Convert the fractional part
		for(count = 0; count < dwidth; count++)
		{
			*string++ = _IQNtoa_get_frac_c(uval) + '0';	// extract the character
			uval = uval * 10;							// remove the character value from uval
		}

	} // end if


//--------------------------------------------------------------------
// Finish up
//
	*string = 0;								// add the NUL character to terminate string
	return(error);								// return


} // end of __IQNtoa()

/*** end of file *****************************************************/
