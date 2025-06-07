/*
//###########################################################################
//
// FILE:    F28335_FIXPT_RFFT_2048_lnk.cmd
//
// TITLE:   Linker Command File for the Fixed Point DSP library examples 
//          that run on the 28335 platform
//
//          This file includes all RAM and _FLASH blocks present on the
//          F28335 and depending on the active build configuration(RAM or _FLASH)
//          the appropriate sections will either be loaded into RAM or _FLASH 
//          blocks
//
//#############################################################################
//
//
// $Copyright: Copyright (C) 2014-2025 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################
//=======================================================
// For Code Composer Studio V2.2 and later
// ---------------------------------------
// In addition to this memory linker command file,
// add the header linker command file directly to the project.
// The header linker command file is required to link the
// peripheral structures to the proper locations within
// the memory map.
//
// The header linker files are found in <base>\DSP2833x_Headers\cmd
//
// For BIOS applications add:      DSP2833x_Headers_BIOS.cmd
// For nonBIOS applications add:   DSP2833x_Headers_nonBIOS.cmd
//=======================================================
// For Code Composer Studio prior to V2.2
// --------------------------------------
// 1) Use one of the following -l statements to include the
// header linker command file in the project. The header linker
// file is required to link the peripheral structures to the proper
// locations within the memory map                                    
//
// Uncomment this line to include file only for non-BIOS applications
// -l DSP2833x_Headers_nonBIOS.cmd
//
// Uncomment this line to include file only for BIOS applications
// -l DSP2833x_Headers_BIOS.cmd
//
// 2) In your project add the path to <base>\headers\cmd to the
// library search path under project->build options, linker tab,
// library search path (-i).
//=======================================================
// Define the memory block start/length for the F28335
// PAGE 0 will be used to organize program sections
// PAGE 1 will be used to organize data sections
// 
// NOTES:
// 1. Memory blocks on F28335 are uniform (ie same physical memory) in both 
//    PAGE 0 and PAGE 1. That is the same memory region should not be defined 
//    for both PAGE 0 and PAGE 1. Doing so will result in corruption of program 
//    and/or data. 
//    
// 2. L0/L1/L2 and L3 memory blocks are mirrored - that is they can be accessed 
//    in high memory or low memory. For simplicity only one instance is used in 
//    this linker file. 
//    
// 3. Contiguous SARAM memory blocks can be combined if required to create a 
//    larger memory block. 
//
// 4. RAM sections L0 and L1 are protected by the code security module.
//
//#############################################################################
*/

MEMORY
{
PAGE 0 :
/* Program Memory */
/* Memory (RAM/_FLASH/OTP) blocks can be moved to PAGE1 for data allocation */
/* BEGIN is used for the "boot to SARAM" bootloader mode      */

   RAMM0       : origin = 0x000050,  length = 0x0003B0     /* on-chip RAM block M0 */
   ZONE0       : origin = 0x004000,  length = 0x001000     /* XINTF zone 0 */
   ZONE6       : origin = 0x0100000, length = 0x100000     /* XINTF zone 6 */
   ZONE7A      : origin = 0x0200000, length = 0x00FC00     /* XINTF zone 7 - program space */

   FLASHH      : origin = 0x300000, length = 0x008000     /* on-chip _FLASH */
   FLASHG      : origin = 0x308000, length = 0x008000     /* on-chip _FLASH */
   FLASHF      : origin = 0x310000, length = 0x008000     /* on-chip _FLASH */
   FLASHE      : origin = 0x318000, length = 0x008000     /* on-chip _FLASH */
   FLASHD      : origin = 0x320000, length = 0x008000     /* on-chip _FLASH */
   FLASHC      : origin = 0x328000, length = 0x008000     /* on-chip _FLASH */
   FLASHA      : origin = 0x338000, length = 0x007F80     /* on-chip _FLASH */
   BEGIN       : origin = 0x33FFF6, length = 0x000002     /* Part of FLASHA.  Used for "boot to Flash" bootloader mode. */

   CSM_RSVD    : origin = 0x33FF80, length = 0x000076     /* Part of FLASHA.  Program with all 0x0000 when CSM is in use. */
   CSM_PWL     : origin = 0x33FFF8, length = 0x000008     /* Part of FLASHA.  CSM password locations in FLASHA */
   OTP         : origin = 0x380400, length = 0x000400     /* on-chip OTP */
   ADC_CAL     : origin = 0x380080, length = 0x000009     /* ADC_cal function in Reserved memory */
   
   IQTABLES    : origin = 0x3FE000, length = 0x000b50     /* IQ Math Tables in Boot ROM */
   IQTABLES2   : origin = 0x3FEB50, length = 0x00008c     /* IQ Math Tables in Boot ROM */  
   FPUTABLES   : origin = 0x3FEBDC, length = 0x0006A0     /* FPU Tables in Boot ROM */
   ROM         : origin = 0x3FF27C, length = 0x000D44     /* Boot ROM */        
   RESET       : origin = 0x3FFFC0, length = 0x000002     /* part of boot ROM  */
   VECTORS     : origin = 0x3FFFC2, length = 0x00003E     /* part of boot ROM */

PAGE 1 :
/* Data Memory */
/* Memory (RAM/_FLASH/OTP) blocks can be moved to PAGE0 for program allocation */
/* Registers remain on PAGE1 
/* BOOT_RSVD is used by the boot ROM for stack.               */
/* This section is only reserved to keep the BOOT ROM from    */
/* corrupting this area during the debug process              */

   BOOT_RSVD   : origin = 0x000000, length = 0x000050     /* Part of M0, BOOT rom will use this for stack */
   RAMM1       : origin = 0x000400, length = 0x000400     /* on-chip RAM block M1 */
   FFTIPCB     : origin = 0x008000, length = 0x002000
   FFTIPCBSRC  : origin = 0x00A000, length = 0x002000
   EBSS        : origin = 0x00C000, length = 0x002400
   RAML7       : origin = 0x00FC00, length = 0x000400     /* on-chip RAM block L7 */
   ZONE7B      : origin = 0x20FC00, length = 0x000400     /* XINTF zone 7 - data space */
   FLASHB      : origin = 0x330000, length = 0x008000     /* on-chip _FLASH */
}

SECTIONS
{
   /* Setup for "boot to SARAM" mode:
      The codestart section (found in DSP28_CodeStartBranch.asm)
      re-directs execution to the start of user code.  */
      
   /* Allocate program areas: */
   codestart           : > BEGIN,      PAGE = 0
   ramfuncs            : LOAD = FLASHD,
                         RUN = RAMM0,
                         table(_ramfuncsCopyTable),
                         PAGE = 0
   .cinit              : > FLASHA,     PAGE = 0
   .pinit              : > FLASHA,     PAGE = 0
   .text               : > FLASHA,     PAGE = 0
   /* Initalized sections go in Flash */
   /* For SDFlash to program these, they must be allocated to page 0 */
   .econst             : > FLASHA,     PAGE = 0
   .switch             : > FLASHA,     PAGE = 0   
   csmpasswds          : > CSM_PWL,    PAGE = 0
   csm_rsvd            : > CSM_RSVD,   PAGE = 0

   /* Allocate uninitalized data sections: */
   .stack              : > RAMM1,      PAGE = 1
   .ebss               : > EBSS,       PAGE = 1
   .esysmem            : > RAMM1,      PAGE = 1

   /* Copy table overlay section: */
   .ovly			   : > RAML7,      PAGE = 1

   /* Example specific sections */
   FFTtf               : > FLASHB,     PAGE = 1
   SINTBL              : > FLASHB,     PAGE = 1 
   FFTipcb             : > FFTIPCB,    ALIGN = 0x1000, PAGE = 1
   FFTipcbsrc          : > FFTIPCBSRC, PAGE = 1
   
   /* Allocate IQ math areas: */
   IQmath              : > FLASHC,     PAGE = 0                  /* Math Code */
   IQmathTables        : > IQTABLES,   PAGE = 0, TYPE = NOLOAD 
   
   /* Uncomment the section below if calling the IQNexp() or IQexp()
      functions from the IQMath.lib library in order to utilize the 
      relevant IQ Math table in Boot ROM (This saves space and Boot ROM 
      is 1 wait-state). If this section is not uncommented, IQmathTables2
      will be loaded into other memory (SARAM, Flash, etc.) and will take
      up space, but 0 wait-state is possible.
   */
   /*
   IQmathTables2       : > IQTABLES2,  PAGE = 0, TYPE = NOLOAD 
   {
   
              IQmath.lib<IQNexpTable.obj> (IQmathTablesRam)
   
   }
   */
   
   FPUmathTables       : > FPUTABLES,  PAGE = 0, TYPE = NOLOAD 
         
   /* Allocate DMA-accessible RAM sections: */
   /*
   DMARAML4            : > RAML4,      PAGE = 1
   DMARAML5            : > RAML5,      PAGE = 1
   DMARAML6            : > RAML61,     PAGE = 1
   DMARAML7            : > RAML7,      PAGE = 1
   */
   
   /* Allocate 0x400 of XINTF Zone 7 to storing data */
   ZONE7DATA           : > ZONE7B,     PAGE = 1

   /* .reset is a standard section used by the compiler.  It contains the */ 
   /* the address of the start of _c_int00 for C Code.   /*
   /* When using the boot ROM this section and the CPU vector */
   /* table is not needed.  Thus the default type is set here to  */
   /* DSECT  */ 
   .reset              : > RESET,      PAGE = 0, TYPE = DSECT
   vectors             : > VECTORS,    PAGE = 0, TYPE = DSECT
   
   /* Allocate ADC_cal function (pre-programmed by factory into TI reserved memory) */
   .adc_cal            : load = ADC_CAL, PAGE = 0, TYPE = NOLOAD
}
/*
//#############################################################################
// End of file.
//#############################################################################
*/
