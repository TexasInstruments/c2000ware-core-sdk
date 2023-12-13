/* f280015x_link.cmd */

SECTIONS
{
	dclfuncs  		 : > RAMLS0, 		align(2)

	PDataLogSection	 : >> RAMLS0,		align(4)
	QDataLogSection	 : >> RAMLS0,		align(4)
	RDataLogSection	 : >> RAMLS1,		align(4)
	SDataLogSection	 : >> RAMLS1,		align(4)
}

/* end of file */
