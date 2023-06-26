
MEMORY
{
PAGE 0 :
   /* BEGIN is used for the "boot to SARAM" bootloader mode   */

   BEGIN			: origin = 0x000000, length = 0x000002
   RAMM0           	: origin = 0x000123, length = 0x0002DD
   RAMD0           	: origin = 0x00B000, length = 0x000800
   RAMLS0          	: origin = 0x008000, length = 0x000800
   RAMLS1          	: origin = 0x008800, length = 0x000800
   RAMLS2          	: origin = 0x009000, length = 0x000800
   RAMLS3      		: origin = 0x009800, length = 0x000800
   RAMLS4      		: origin = 0x00A000, length = 0x000800
   RAMLS5      		: origin = 0x00A800, length = 0x000800
   RESET           	: origin = 0x3FFFC0, length = 0x000002

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
   FLASHN           : origin = 0x0BE000, length = 0x002000	/* on-chip Flash */

PAGE 1 :

   BOOT_RSVD       : origin = 0x000002, length = 0x000121     /* Part of M0, BOOT rom will use this for stack */
   RAMM1           : origin = 0x000400, length = 0x0003F8     /* on-chip RAM block M1 */
//   RAMM1_RSVD      : origin = 0x0007F8, length = 0x000008     /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */
   RAMD1			: origin = 0x00B800, length = 0x000800

   RAMGS0      		: origin = 0x00C000, length = 0x001000
   RAMGS1			: origin = 0x00D000, length = 0x001000
   RAMGS2			: origin = 0x00E000, length = 0x001000
   RAMGS3			: origin = 0x00F000, length = 0x001000
   RAMGS4			: origin = 0x010000, length = 0x001000
   RAMGS5			: origin = 0x011000, length = 0x001000
   RAMGS6			: origin = 0x012000, length = 0x001000
   RAMGS7			: origin = 0x013000, length = 0x001000
   RAMGS8			: origin = 0x014000, length = 0x001000
   RAMGS9			: origin = 0x015000, length = 0x001000
   RAMGS10			: origin = 0x016000, length = 0x001000

//   RAMGS11     : origin = 0x017000, length = 0x000FF8   /* Uncomment for F28374D, F28376D devices */

//   RAMGS11_RSVD : origin = 0x017FF8, length = 0x000008    /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */

   RAMGS11         : origin = 0x017000, length = 0x001000     /* Only Available on F28379D, F28377D, F28375D devices. Remove line on other devices. */
   RAMGS12         : origin = 0x018000, length = 0x001000     /* Only Available on F28379D, F28377D, F28375D devices. Remove line on other devices. */
   RAMGS13         : origin = 0x019000, length = 0x001000     /* Only Available on F28379D, F28377D, F28375D devices. Remove line on other devices. */
   RAMGS14         : origin = 0x01A000, length = 0x001000     /* Only Available on F28379D, F28377D, F28375D devices. Remove line on other devices. */
   RAMGS15         : origin = 0x01B000, length = 0x000FF8     /* Only Available on F28379D, F28377D, F28375D devices. Remove line on other devices. */

//   RAMGS15_RSVD : origin = 0x01BFF8, length = 0x000008    /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */
                                                            /* Only on F28379D, F28377D, F28375D devices. Remove line on other devices. */

   CPU2TOCPU1RAM	: origin = 0x03F800, length = 0x000400
   CPU1TOCPU2RAM	: origin = 0x03FC00, length = 0x000400

   CANA_MSG_RAM     : origin = 0x049000, length = 0x000800
   CANB_MSG_RAM     : origin = 0x04B000, length = 0x000800
}


SECTIONS
{
   codestart        : > BEGIN,		PAGE = 0
   .text            : >> RAMLS0 | RAMLS1 | RAMLS2 | RAMLS3 | RAMLS4,   PAGE = 0
   .cinit           : > RAMM0,		PAGE = 0
   .pinit           : > RAMM0,		PAGE = 0
   .switch          : > RAMM0,		PAGE = 0
   .reset           : > RESET,		PAGE = 0, TYPE = DSECT /* not used, */

   .stack           : > RAMM1,		PAGE = 1
   .ebss            : >> RAMGS0,	PAGE = 1
   .econst          : >> RAMLS5,	PAGE = 0
   .esysmem         : > RAMGS4,		PAGE = 1
   Filter_RegsFile  : > RAMGS0,		PAGE = 1

   ramgs0           : > RAMGS0,		PAGE = 1
   ramgs1           : > RAMGS3,		PAGE = 1

   SINETABLE        : > RAMGS6		PAGE = 1	/* Ram block for SINETABLE data */
   fsk_corr_lib_data : > RAMGS5		PAGE = 1	/* Flash block for lib data */

   FlashAPIDataSection : > RAMM1, PAGE = 1, ALIGN(8)

#ifdef __TI_COMPILER_VERSION__
   #if __TI_COMPILER_VERSION__ >= 15009000
    .TI.ramfunc : {} > RAMD0,		PAGE = 0
   #else
    ramfuncs    : > RAMD0			PAGE = 0
   #endif
#endif

   /* The following section definitions are required when using the IPC API Drivers */
    GROUP : > CPU1TOCPU2RAM,		PAGE = 1
    {
        PUTBUFFER
        PUTWRITEIDX
        GETREADIDX
    }

    GROUP : > CPU2TOCPU1RAM,		PAGE = 1
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
