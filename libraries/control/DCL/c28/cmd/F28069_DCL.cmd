/* F28069_DCL.cmd
 *
 * Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com/ 
 * ALL RIGHTS RESERVED 
 *
*/
 
SECTIONS
{
	/* 22-bit program sections */
    .reset			: load = RESET,   type = DSECT,  PAGE = 0		/* reset vector in internal boot ROM */
    vectors 		: load = VECTORS, type = DSECT,  PAGE = 0		/* internal ROM vector table */
	codestart      	: > BOOTM0,     PAGE = 0

	/* RAML4 for all program sections */
   	.text    		: > RAML4L,  	PAGE = 0			/* default code section */
   	.pinit   		: > RAML4L,  	PAGE = 0			/* global constructor table */
   	.cinit   		: > RAML3,  	PAGE = 0			/* initialised variables */
   	.code	 		: > RAML4L,  	PAGE = 0			/* assembly code section */
   	.data			: > RAML4L,		PAGE = 0			/* constant data */
   	.switch			: > RAML4L,		PAGE = 0			/* switch tables */
	.init_array		: > RAML4L,  	PAGE = 0			/* for EABI */
   	
   	/* 16-Bit data sections */
   	.const   		: > RAMM0, 		PAGE = 1			/* near constants */
   	.bss     		: > RAMM0,	 	PAGE = 1			/* near variables */
					RUN_START(_bss_start),
					RUN_SIZE(_bss_size)

   	.stack   		: > RAMM1, 		PAGE = 1	align(2)	/* stack: even word alignment */
   	.sysmem  		: > RAMM0, 		PAGE = 1			/* near dynamic memory */
   	.cio			: > RAMM0,		PAGE = 1   			/* string constants */

   	/* 32-bit data sections */
 	.ebss    		: > RAML4H,		PAGE = 1			/* far variables */
					RUN_START(_ebss_start),
					RUN_SIZE(_ebss_size)

 	.econst  		: > RAML4H,		PAGE = 1			/* far constants */
 	.esysmem 		: > RAML4H,	 	PAGE = 1			/* far dynamic memory */

/*	csmpasswds      : > CSM_PWL_P0  PAGE = 0 */
/*	csm_rsvd        : > CSM_RSVD    PAGE = 0 */

	/* Digital Controller Library functions */
	dclfuncs		: > RAML4L,		PAGE = 0
	dcl32funcs		: > RAML4L,		PAGE = 0

	ramfuncs		: > RAML4L,		PAGE = 0
                  	LOAD_START(_RamfuncsLoadStart),
                   	LOAD_END(_RamfuncsLoadEnd),
                   	RUN_START(_RamfuncsRunStart),
					RUN_SIZE(_RamfuncsRUNSize)

   /* data buffers */
   PDataLogSection	: > RAML5,		PAGE = 1	align(2)
   QDataLogSection	: > RAML6,		PAGE = 1	align(2)
   RDataLogSection	: > RAML7,		PAGE = 1	align(2)
   SDataLogSection	: > RAML8,		PAGE = 1	align(2)

    /* IQ math sections */
	IQmath          : > RAML4L,	    PAGE = 0
	IQmathTables	: > IQTABLES,   PAGE = 0, TYPE = NOLOAD


   .scratchpad      : > CLARAM0,   PAGE = 1
   .bss_cla	    	: > CLARAM0,   PAGE = 1
   .const_cla	    : > CLARAM0,   PAGE = 1

   Cla1Prog        	: > RAML3,
                     LOAD_START(_Cla1funcsLoadStart),
                     LOAD_END(_Cla1funcsLoadEnd),
                     LOAD_SIZE(_Cla1funcsLoadSize),
                     RUN_START(_Cla1funcsRunStart),
                     PAGE = 0

   Cla1ToCpuMsgRAM  : > CLA1_MSGRAMLOW,   PAGE = 1
   CpuToCla1MsgRAM  : > CLA1_MSGRAMHIGH,  PAGE = 1
   Cla1DataRam0	    : > CLARAM0,	  PAGE = 1
   Cla1DataRam1	    : > CLARAM1,	  PAGE = 1
   Cla1DataRam2	    : > CLARAM2,	  PAGE = 1

   CLA1mathTables	: > CLARAM1,
                      LOAD_START(_Cla1mathTablesLoadStart),
                      LOAD_END(_Cla1mathTablesLoadEnd),
                      LOAD_SIZE(_Cla1mathTablesLoadSize),
                      RUN_START(_Cla1mathTablesRunStart),
                      PAGE = 1

   CLAscratch       :
                     { *.obj(CLAscratch)
                     . += CLA_SCRATCHPAD_SIZE;
                     *.obj(CLAscratch_end) } > CLARAM0,
					 PAGE = 1

}

/* end of file */
