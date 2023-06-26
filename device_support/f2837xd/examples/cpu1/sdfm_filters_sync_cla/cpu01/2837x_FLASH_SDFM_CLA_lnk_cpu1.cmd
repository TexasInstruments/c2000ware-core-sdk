// The user must define CLA_C in the project linker settings if using the
// CLA C compiler
// Project Properties -> C2000 Linker -> Advanced Options -> Command File
// Preprocessing -> --define
#ifdef CLA_C
// Define a size for the CLA scratchpad area that will be used
// by the CLA compiler for local symbols and temps
// Also force references to the special symbols that mark the
// scratchpad are.
CLA_SCRATCHPAD_SIZE = 0x100;
--undef_sym=__cla_scratchpad_end
--undef_sym=__cla_scratchpad_start
#endif //CLA_C

MEMORY
{
PAGE 0 :  /* Program Memory */
          /* Memory (RAM/FLASH) blocks can be moved to PAGE1 for data allocation */
          /* BEGIN is used for the "boot to SARAM" bootloader mode   */

   BEGIN            : origin = 0x080000, length = 0x000002
   RAMM0            : origin = 0x000122, length = 0x0002DE
   RAMD0            : origin = 0x00B000, length = 0x000800
   RAMLS4           : origin = 0x00A000, length = 0x000800
   RAMLS5           : origin = 0x00A800, length = 0x000800
   RESET            : origin = 0x3FFFC0, length = 0x000002

   /* Flash sectors */
   FLASHA           : origin = 0x080002, length = 0x001FFE  /* on-chip Flash */
   FLASHB           : origin = 0x082000, length = 0x002000  /* on-chip Flash */
   FLASHC           : origin = 0x084000, length = 0x002000  /* on-chip Flash */
   FLASHD           : origin = 0x086000, length = 0x002000  /* on-chip Flash */
   FLASHE           : origin = 0x088000, length = 0x008000  /* on-chip Flash */
   FLASHF           : origin = 0x090000, length = 0x008000  /* on-chip Flash */
   FLASHG           : origin = 0x098000, length = 0x008000  /* on-chip Flash */
   FLASHH           : origin = 0x0A0000, length = 0x008000  /* on-chip Flash */
   FLASHI           : origin = 0x0A8000, length = 0x008000  /* on-chip Flash */
   FLASHJ           : origin = 0x0B0000, length = 0x008000  /* on-chip Flash */
   FLASHK           : origin = 0x0B8000, length = 0x002000  /* on-chip Flash */
   FLASHL           : origin = 0x0BA000, length = 0x002000  /* on-chip Flash */
   FLASHM           : origin = 0x0BC000, length = 0x002000  /* on-chip Flash */
   FLASHN           : origin = 0x0BE000, length = 0x001FF0	/* on-chip Flash */
   
//   FLASHN_RSVD     : origin = 0x0BFFF0, length = 0x000010    /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */

PAGE 1 : /* Data Memory */
         /* Memory (RAM/FLASH) blocks can be moved to PAGE0 for program allocation */

   BOOT_RSVD       : origin = 0x000002, length = 0x000121     /* Part of M0, BOOT rom will use this for stack */
   RAMM1           : origin = 0x000400, length = 0x0003F8     /* on-chip RAM block M1 */
//   RAMM1_RSVD      : origin = 0x0007F8, length = 0x000008     /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */
   RAMD1           : origin = 0x00B800, length = 0x000800
   RAMLS0          : origin = 0x008000, length = 0x000800
   RAMLS1          : origin = 0x008800, length = 0x000800
   RAMLS2_1        : origin = 0x009000, length = 0x000400
   RAMLS2_2        : origin = 0x009400, length = 0x000400
   RAMLS3_1        : origin = 0x009800, length = 0x000400
   RAMLS3_2        : origin = 0x009C00, length = 0x000400

   RAMGS0          : origin = 0x00C000, length = 0x001000
   RAMGS1          : origin = 0x00D000, length = 0x001000
   RAMGS2          : origin = 0x00E000, length = 0x001000
   RAMGS3          : origin = 0x00F000, length = 0x001000
   RAMGS4          : origin = 0x010000, length = 0x001000
   RAMGS5          : origin = 0x011000, length = 0x001000
   RAMGS6          : origin = 0x012000, length = 0x001000
   RAMGS7          : origin = 0x013000, length = 0x001000
   RAMGS8          : origin = 0x014000, length = 0x001000
   RAMGS9          : origin = 0x015000, length = 0x001000
   RAMGS10         : origin = 0x016000, length = 0x001000
   
//   RAMGS11          : origin = 0x017000, length = 0x000FF8   /* Uncomment for F28374D, F28376D devices */

//   RAMGS11_RSVD     : origin = 0x017FF8, length = 0x000008    /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */

   RAMGS11          : origin = 0x017000, length = 0x001000     /* Only Available on F28379D/_, F28377D/F28377S, F28375D/F28375S devices. Remove line on other devices. */
   RAMGS12          : origin = 0x018000, length = 0x001000     /* Only Available on F28379D/_, F28377D/F28377S, F28375D/F28375S devices. Remove line on other devices. */
   RAMGS13          : origin = 0x019000,   length = 0x001000     /* Only Available on F28379D/_, F28377D/F28377S, F28375D/F28375S devices. Remove line on other devices. */
   RAMGS14          : origin = 0x01A000,   length = 0x001000     /* Only Available on F28379D/_, F28377D/F28377S, F28375D/F28375S devices. Remove line on other devices. */
   RAMGS15          : origin = 0x01B000, length = 0x000FF8     /* Only Available on F28379D/_, F28377D/F28377S, F28375D/F28375S devices. Remove line on other devices. */

//   RAMGS15_RSVD     : origin = 0x01BFF8, length = 0x000008    /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */

   CLA1_MSGRAMLOW   : origin = 0x001480, length = 0x000080
   CLA1_MSGRAMHIGH  : origin = 0x001500, length = 0x000080

   CPU2TOCPU1RAM   : origin = 0x03F800, length = 0x000400
   CPU1TOCPU2RAM   : origin = 0x03FC00, length = 0x000400
}


SECTIONS
{
  /* Allocate program areas: */
   .cinit              : > FLASHB      PAGE = 0
   .pinit              : > FLASHB,     PAGE = 0
   .text               : > FLASHB      PAGE = 0
   codestart           : > BEGIN       PAGE = 0

#ifdef __TI_COMPILER_VERSION__
    #if __TI_COMPILER_VERSION__ >= 15009000
       .TI.ramfunc       : LOAD = FLASHD,
                         RUN = RAMLS4,
                         LOAD_START(_RamfuncsLoadStart),
                         LOAD_SIZE(_RamfuncsLoadSize),
                         LOAD_END(_RamfuncsLoadEnd),
                         RUN_START(_RamfuncsRunStart),
                         RUN_SIZE(_RamfuncsRunSize),
                         RUN_END(_RamfuncsRunEnd),
                         PAGE = 0, ALIGN(8)
    #else
       ramfuncs          : LOAD = FLASHD,
                         RUN = RAMLS4,
                         LOAD_START(_RamfuncsLoadStart),
                         LOAD_SIZE(_RamfuncsLoadSize),
                         LOAD_END(_RamfuncsLoadEnd),
                         RUN_START(_RamfuncsRunStart),
                         RUN_SIZE(_RamfuncsRunSize),
                         RUN_END(_RamfuncsRunEnd),
                         PAGE = 0, ALIGN(8)
    #endif
#endif

   /* Allocate uninitalized data sections: */
   .stack              : > RAMM1        PAGE = 1
   .ebss               : > RAMGS1       PAGE = 1
   .esysmem            : > RAMGS1       PAGE = 1

   /* Initalized sections go in Flash */
   .econst             : > FLASHB      PAGE = 0
   .switch             : > FLASHB      PAGE = 0

   .reset              : > RESET,     PAGE = 0, TYPE = DSECT /* not used, */

   Filter_RegsFile     : > RAMGS0,     PAGE = 1

   /* The following section definitions are required when using the IPC API Drivers */
    GROUP : > CPU1TOCPU2RAM, PAGE = 1
    {
        PUTBUFFER
        PUTWRITEIDX
        GETREADIDX
    }

    GROUP : > CPU2TOCPU1RAM, PAGE = 1
    {
        GETBUFFER :    TYPE = DSECT
        GETWRITEIDX :  TYPE = DSECT
        PUTREADIDX :   TYPE = DSECT
    }


   /* CLA specific sections */
   Cla1Prog         :   LOAD = FLASHC,
                        RUN = RAMLS5,
                        LOAD_START(_Cla1funcsLoadStart),
                        LOAD_END(_Cla1funcsLoadEnd),
                        RUN_START(_Cla1funcsRunStart),
                        LOAD_SIZE(_Cla1funcsLoadSize),
                        ALIGN(8),
                        PAGE = 0

   CLADataLS0       : > RAMLS0, PAGE=1
   CLADataLS1       : > RAMLS1, PAGE=1

   Cla1ToCpuMsgRAM  : > CLA1_MSGRAMLOW,   PAGE = 1
   CpuToCla1MsgRAM  : > CLA1_MSGRAMHIGH,  PAGE = 1

   /* The following section definition are for SDFM examples */
   Filter1_RegsFile : > RAMLS2_1,   PAGE = 1, fill=0x1111
   Filter2_RegsFile : > RAMLS2_2,   PAGE = 1, fill=0x2222
   Filter3_RegsFile : > RAMLS3_1,   PAGE = 1, fill=0x3333
   Filter4_RegsFile : > RAMLS3_2,   PAGE = 1, fill=0x4444

#ifdef CLA_C
   /* CLA C compiler sections */
   //
   // Must be allocated to memory the CLA has write access to
   //
   CLAscratch       :
                     { *.obj(CLAscratch)
                     . += CLA_SCRATCHPAD_SIZE;
                     *.obj(CLAscratch_end) } >  RAMLS1,  PAGE = 1

   .scratchpad      : > RAMLS1,       PAGE = 1
   .bss_cla         : > RAMLS1,       PAGE = 1
   .const_cla       :  LOAD = FLASHB,
                       RUN = RAMLS1,
                       RUN_START(_Cla1ConstRunStart),
                       LOAD_START(_Cla1ConstLoadStart),
                       LOAD_SIZE(_Cla1ConstLoadSize),
                       PAGE = 1

#endif //CLA_C
}


/*
//===========================================================================
// End of file.
//===========================================================================
*/
