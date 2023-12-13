/* f280039c_link.cmd */

SECTIONS
{
	dclfuncs  		 : > RAMLS3, 		align(2)

	pDataLogSection	 : >> RAMLS6_7,		align(4)
	qDataLogSection	 : >> RAMLS6_7,		align(4)
	sDataLogSection	 : >> RAMGS0,		align(4)
}

/* end of file */
