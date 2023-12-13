MEMORY
{
   /* BEGIN is used for the "boot to SARAM" bootloader mode   */
   BEGIN            : origin = 0x000000, length = 0x000002
   BOOT_RSVD        : origin = 0x000002, length = 0x0001AF     /* Part of M0, BOOT rom will use this for stack */
   RAMM0            : origin = 0x0001B1, length = 0x00024F
   RAMM1            : origin = 0x000400, length = 0x000400

   // RAMD2            : origin = 0x008000, length = 0x002000  // Can be mapped to either CPU1 or CPU2. When configured to CPU1, use the address 0x01A000. User should comment/uncomment based on core selection
   // RAMD3            : origin = 0x00A000, length = 0x002000  // Can be mapped to either CPU1 or CPU2. When configured to CPU1, use the address 0x01C000. User should comment/uncomment based on core selection
   // RAMD4            : origin = 0x00C000, length = 0x002000  // Can be mapped to either CPU1 or CPU2. When configured to CPU1, use the address 0x01E000. User should comment/uncomment based on core selection
   // RAMD5            : origin = 0x00E000, length = 0x002000  // Can be mapped to either CPU1 or CPU2. When configured to CPU1, use the address 0x020000. User should comment/uncomment based on core selection

   RAMGS0           : origin = 0x010000, length = 0x002000
   RAMGS1           : origin = 0x012000, length = 0x002000
   RAMGS2           : origin = 0x014000, length = 0x002000
   RAMGS3           : origin = 0x016000, length = 0x002000
   RAMGS4           : origin = 0x018000, length = 0x002000

   /* Flash Banks (128 sectors each) */
   // FLASH_BANK0     : origin = 0x080000, length = 0x20000  // Can be mapped to either CPU1 or CPU2. User should comment/uncomment based on core selection
   // FLASH_BANK1     : origin = 0x0A0000, length = 0x20000  // Can be mapped to either CPU1 or CPU2. User should comment/uncomment based on core selection
   // FLASH_BANK2     : origin = 0x0C0000, length = 0x20000  // Can be mapped to either CPU1 or CPU2. User should comment/uncomment based on core selection
   // FLASH_BANK3     : origin = 0x0E0000, length = 0x20000  // Can be mapped to either CPU1 or CPU2. User should comment/uncomment based on core selection
   // FLASH_BANK4     : origin = 0x100000, length = 0x20000  // Can be mapped to either CPU1 or CPU2. User should comment/uncomment based on core selection



   CPU1TOCPU2RAM    : origin = 0x03A000, length = 0x000400
   CPU2TOCPU1RAM    : origin = 0x03B000, length = 0x000400

   CLATOCPURAM      : origin = 0x001480,   length = 0x000080
   CPUTOCLARAM      : origin = 0x001500,   length = 0x000080
   CLATODMARAM      : origin = 0x001680,   length = 0x000080
   DMATOCLARAM      : origin = 0x001700,   length = 0x000080

   CANA_MSG_RAM     : origin = 0x049000, length = 0x000800
   CANB_MSG_RAM     : origin = 0x04B000, length = 0x000800
   RESET            : origin = 0x3FFFC0, length = 0x000002
}


SECTIONS
{
   codestart        : > BEGIN
   .text            : > RAMGS4
   .cinit           : > RAMM0
   .switch          : > RAMM0
   .reset           : > RESET, TYPE = DSECT /* not used, */

   .stack           : > RAMM1
#if defined(__TI_EABI__)
   .bss             : > RAMGS4
   .bss:output      : > RAMGS4
   .init_array      : > RAMM0
   .const           : > RAMGS4
   .data            : > RAMGS4
   .sysmem          : > RAMGS4
#else
   .pinit           : > RAMM0
   .ebss            : > RAMGS4
   .econst          : > RAMGS4
   .esysmem         : > RAMGS4
#endif

   ramgs0 : > RAMGS0, type=NOINIT
   ramgs1 : > RAMGS1, type=NOINIT
   ramgs2 : > RAMGS2, type=NOINIT

   MSGRAM_CPU1_TO_CPU2 > CPU1TOCPU2RAM, type=NOINIT
   MSGRAM_CPU2_TO_CPU1 > CPU2TOCPU1RAM, type=NOINIT

    .TI.ramfunc : {} > RAMM0

}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
