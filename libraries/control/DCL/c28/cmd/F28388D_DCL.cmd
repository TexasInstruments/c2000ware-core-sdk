/* F28388D_DCL.cmd
 *
 * Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com/ 
 * ALL RIGHTS RESERVED 
 *
*/

SECTIONS
{
   codestart        : > BEGIN
   .text            : >> RAMD0 | RAMD1 | RAMLS0 | RAMLS1 | RAMLS2 | RAMLS3
   .cinit           : > RAMM0
   .switch          : > RAMM0
   .reset           : > RESET, TYPE = DSECT /* not used, */

   .stack           : > RAMM1
#if defined(__TI_EABI__)
   .bss             : > RAMLS5
   .bss:output      : > RAMLS3
   .init_array      : > RAMM0
   .const           : > RAMLS5
   .data            : > RAMLS5
   .sysmem          : > RAMLS4
#else
   .pinit           : > RAMM0
   .ebss            : >> RAMLS5 | RAMLS6
   .econst          : > RAMLS5
   .esysmem         : > RAMLS5
#endif

   ramgs0 : > RAMGS0
   ramgs1 : > RAMGS1

   MSGRAM_CPU1_TO_CPU2 > CPU1TOCPU2RAM
   MSGRAM_CPU2_TO_CPU1 > CPU2TOCPU1RAM
   MSGRAM_CPU_TO_CM   > CPUTOCMRAM
   MSGRAM_CM_TO_CPU   > CMTOCPURAM

#ifdef __TI_COMPILER_VERSION__
   #if __TI_COMPILER_VERSION__ >= 15009000
    .TI.ramfunc : {} > RAMM0
   #else
    ramfuncs    : > RAMM0
   #endif
#endif

	dclfuncs  		 : > RAMGS2, 		align(2)
   PDataLogSection	: > RAMGS12,	align(4)
     				LOAD_START(pData_start),
					LOAD_SIZE(pData_size)

   QDataLogSection	: > RAMGS13,	align(4)
        			LOAD_START(qData_start),
					LOAD_SIZE(qData_size)


   RDataLogSection	: > RAMGS14,	align(4)
        			LOAD_START(rData_start),
					LOAD_SIZE(rData_size)

   SDataLogSection	: > RAMGS15,	align(4)
        			LOAD_START(sData_start),
					LOAD_SIZE(sData_size)

}

/* end of file */
