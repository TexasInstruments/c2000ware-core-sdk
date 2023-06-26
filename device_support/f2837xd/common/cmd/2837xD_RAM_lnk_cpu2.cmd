
MEMORY
{
PAGE 0 :
   /* BEGIN is used for the "boot to SARAM" bootloader mode   */

   BEGIN           	: origin = 0x000000, length = 0x000002
   RAMM0           	: origin = 0x0000A2, length = 0x00035E
   RAMD0           	: origin = 0x00B000, length = 0x000800
   RAMLS0          : origin = 0x008000, length = 0x000800
   RAMLS1          	: origin = 0x008800, length = 0x000800
   RAMLS2      		: origin = 0x009000, length = 0x000800
   RAMLS3      		: origin = 0x009800, length = 0x000800
   RAMLS4      		: origin = 0x00A000, length = 0x000800
   RESET           : origin = 0x3FFFC0, length = 0x000002

   /* Flash sectors */
   FLASHA           : origin = 0x080002, length = 0x001FFE	/* on-chip Flash */
   FLASHB           : origin = 0x082000, length = 0x002000	/* on-chip Flash */
   FLASHC           : origin = 0x084000, length = 0x002000	/* on-chip Flash */
   FLASHD           : origin = 0x086000, length = 0x002000	/* on-chip Flash */
   FLASHE           : origin = 0x088000, length = 0x008000	/* on-chip Flash */
   FLASHF           : origin = 0x090000, length = 0x008000	/* on-chip Flash */
   FLASHG           : origin = 0x098000, length = 0x008000	/* on-chip Flash */
   FLASHH           : origin = 0x0A0000, length = 0x008000	/* on-chip Flash */
   FLASHI           : origin = 0x0A8000, length = 0x008000	/* on-chip Flash */
   FLASHJ           : origin = 0x0B0000, length = 0x008000	/* on-chip Flash */
   FLASHK           : origin = 0x0B8000, length = 0x002000	/* on-chip Flash */
   FLASHL           : origin = 0x0BA000, length = 0x002000	/* on-chip Flash */
   FLASHM           : origin = 0x0BC000, length = 0x002000	/* on-chip Flash */
   FLASHN           : origin = 0x0BE000, length = 0x001FF0	/* on-chip Flash */

//   FLASHN_RSVD     : origin = 0x0BFFF0, length = 0x000010    /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */


PAGE 1 :

   BOOT_RSVD       : origin = 0x000002, length = 0x0000A0     /* Part of M0, BOOT rom will use this for stack */
   RAMM1           : origin = 0x000400, length = 0x0003F8     /* on-chip RAM block M1 */
//   RAMM1_RSVD      : origin = 0x0007F8, length = 0x000008     /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */
   RAMD1           : origin = 0x00B800, length = 0x000800

   RAMLS5      : origin = 0x00A800, length = 0x000800

   CANA_MSG_RAM     : origin = 0x049000, length = 0x000800
   CANB_MSG_RAM     : origin = 0x04B000, length = 0x000800

   CPU2TOCPU1RAM   : origin = 0x03F800, length = 0x000400
   CPU1TOCPU2RAM   : origin = 0x03FC00, length = 0x000400
}


SECTIONS
{
   codestart        : > BEGIN,     PAGE = 0
   .text            : >>RAMD0 |  RAMLS0 | RAMLS1 | RAMLS2 | RAMLS3 | RAMLS4,   PAGE = 0
   .cinit           : > RAMM0,     PAGE = 0
   .switch          : > RAMM0,     PAGE = 0
   .reset           : > RESET,     PAGE = 0, TYPE = DSECT /* not used, */
   .stack           : > RAMM1,     PAGE = 1
   
#if defined(__TI_EABI__)
   .bss             : > RAMLS5,    PAGE = 1
   .bss:output      : > RAMLS3,    PAGE = 0
   .init_array      : > RAMM0,     PAGE = 0
   .const           : > RAMLS5,    PAGE = 1
   .data            : > RAMLS5,    PAGE = 1
   .sysmem          : > RAMLS5,    PAGE = 1
#else
   .pinit           : > RAMM0,     PAGE = 0
   .ebss            : > RAMLS5,    PAGE = 1
   .econst          : > RAMLS5,    PAGE = 1
   .esysmem         : > RAMLS5,    PAGE = 1
#endif

#ifdef __TI_COMPILER_VERSION__
   #if __TI_COMPILER_VERSION__ >= 15009000
    .TI.ramfunc : {} > RAMM0,      PAGE = 0
   #else
   ramfuncs         : > RAMM0      PAGE = 0   
   #endif
#endif

   /* The following section definitions are required when using the IPC API Drivers */
    GROUP : > CPU2TOCPU1RAM, PAGE = 1
    {
        PUTBUFFER
        PUTWRITEIDX
        GETREADIDX
    }

    GROUP : > CPU1TOCPU2RAM, PAGE = 1
    {
        GETBUFFER :    TYPE = DSECT
        GETWRITEIDX :  TYPE = DSECT
        PUTREADIDX :   TYPE = DSECT
    }
}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
