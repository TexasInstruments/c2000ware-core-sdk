/* f28e12x_DCL.cmd */

SECTIONS
{
	dclfuncs  		 : > FLASH_BANK0_SEC_0_63, 		align(8)

	PDataLogSection	 : >> FLASH_BANK0_SEC_0_63,		align(8)
	QDataLogSection	 : >> FLASH_BANK0_SEC_0_63,		align(8)
	RDataLogSection	 : >> FLASH_BANK0_SEC_0_63,		align(8)
	SDataLogSection	 : >> FLASH_BANK0_SEC_0_63,		align(8)
}

/* end of file */
