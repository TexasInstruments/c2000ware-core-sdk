/* f28p65x_link.cmd */

SECTIONS
{
	dclfuncs  		 : > RAMLS0, 		align(2)

	PDataLogSection	 : >> RAMLS8,		align(4)
	QDataLogSection	 : >> RAMLS8,		align(4)
	RDataLogSection	 : >> RAMLS9,		align(4)
	SDataLogSection	 : >> RAMLS9,		align(4)
}

/* end of file */
