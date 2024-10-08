/* Note: this linker command file only defines CRC-specific algorithm directives, other parts of the device linker file are generated by sysconfig */

SECTIONS
{
   .TI.crctab	    : > RAMLS3
   /* Test specific sections */
   testInput		: > RAMLS3,
                      crc_table(linkerCrcTable, algorithm = CRC8_PRIME)

}


/*
//===========================================================================
// End of file.
//===========================================================================
*/
