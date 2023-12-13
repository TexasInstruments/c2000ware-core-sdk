/* f280025_link.cmd */

SECTIONS
{
   codestart        : > BEGIN,     	PAGE = 0
   .TI.ramfunc      : > RAMM0      	PAGE = 0
/*   .text            : >> FLASH_BANK0_SEC0 | FLASH_BANK0_SEC1,     PAGE = 0 */
   .text            : > RAMLS456    PAGE = 0
   .cinit           : > RAMM0,     	PAGE = 0
   .switch          : > RAMM0,     	PAGE = 0
   .reset           : > RESET,     	PAGE = 0, TYPE = DSECT
   .stack           : > RAMM1,     	PAGE = 1

#if defined(__TI_EABI__)
   	.bss             : > RAMGS0b
   	.bss:output      : > RAMGS0b
   	.bss:cio 		 : > RAMGS0b
   	.init_array      : > RAMGS0b
   	.const           : > RAMGS0b, 		PAGE = 1
   	.data            : > RAMGS0b, 		PAGE = 1
   	.sysmem          : > RAMGS0b, 		PAGE = 1
#else
	.pinit           : > RAMM0,     	PAGE = 0
   	.ebss            : > RAMGS0b,    	PAGE = 1
	.econst          : > RAMGS0b,    	PAGE = 1
   	.esysmem         : > RAMGS0b,    	PAGE = 1
   	.cio             : > RAMLS0,    	PAGE = 0
#endif

	dclfuncs  		 : > RAMM0, 		PAGE = 0	align(2)

	pDataLogSection	 : >> RAMLS7a,		PAGE = 1	align(4)
	qDataLogSection	 : >> RAMLS7b,		PAGE = 1	align(4)
	sDataLogSection	 : >> RAMGS0a,		PAGE = 1	align(4)
}

/* end of file */
