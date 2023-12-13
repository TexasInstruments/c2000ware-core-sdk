/* F280049_DCL.cmd
 *
 * Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED 
 *
*/
 
SECTIONS
{
	/* 22-bit program sections */
    .reset			: load = RESET,   type = DSECT,  PAGE = 0		/* reset vector in internal boot ROM */
	codestart      	: > BEGIN,      PAGE = 0

	/* program sections */
   	.text    		: > RAMLS02,  	PAGE = 0			/* default code section */
   	.code	 		: > RAMLS02,  	PAGE = 0			/* assembly code section */

   	.pinit   		: > RAMLS4,  	PAGE = 0			/* global constructor table */
   	.cinit   		: > RAMLS4,  	PAGE = 0			/* initialised variables */
   	.data			: > RAMLS4,		PAGE = 0			/* constant data */
   	.switch			: > RAMLS4,		PAGE = 0			/* switch tables */
	.init_array		: > RAMLS4,  	PAGE = 0			/* for EABI */
   	
   	/* 16-Bit data sections */
   	.const   		: > RAMLS5, 	PAGE = 1			/* near constants */
   	.bss     		: > RAMLS5,	 	PAGE = 1			/* near variables */
   	.stack   		: > RAMM1, 		PAGE = 1	align(2)	/* stack: even word alignment */
   	.sysmem  		: > RAMLS6,		PAGE = 1			/* near dynamic memory */
   	.cio			: > RAMLS6,		PAGE = 1   			/* string constants */

   	/* 32-bit data sections */
 	.ebss    		: > RAMLS5,		PAGE = 1			/* far variables [RAMM0] */
 	.econst  		: > RAMLS7,		PAGE = 1			/* far constants [RAMM0] */
 	.esysmem 		: > RAMLS7,	 	PAGE = 1			/* far dynamic memory [RAMM0] */

	/* DCL functions */
	dclfuncs		: > RAMLS02		PAGE = 0
	dcl32funcs		: > RAMLS02		PAGE = 0
	.TI.ramfunc		: > RAMLS02		PAGE = 0

   /* data buffers */
   pDataLogSection	: > RAMGS0,		PAGE = 1	align(2)
   qDataLogSection	: > RAMGS1,		PAGE = 1	align(2)
   rDataLogSection	: > RAMGS2,		PAGE = 1	align(2)
   sDataLogSection	: > RAMGS3,		PAGE = 1	align(2)

   interruptSection	: > RAMLS3, 	PAGE = 0

}

/* end of file */
