let PinmuxMigrations   = system.getScript("/driverlib/pinmux/pinmux_migration.js");

exports = {
	getDriverlibName : getDriverlibName,
	getGPIODriverlibName : getGPIODriverlibName,
	getInterfaceCCodeName : getInterfaceCCodeName,
};


function getDriverlibName(interfaceName, peripheralInstanceName, peripheralName)
{
	var legacyInclusiveNames = PinmuxMigrations.interfaceInclusiveRename(interfaceName, peripheralName);
	interfaceName = legacyInclusiveNames.inclusiveName;
	interfaceName = interfaceName.toUpperCase()
	interfaceName = interfaceName.replace("-", "_")

	if (peripheralInstanceName.includes("SCI"))
	{
		return getSCIDriverlibName(interfaceName, peripheralInstanceName);
	}
	else if (peripheralInstanceName.includes("UART"))
	{
		return getUARTDriverlibName(interfaceName, peripheralInstanceName);
	}
	else if (peripheralInstanceName.includes("ANALOG"))
	{
		return getANALOGDriverlibName(interfaceName, peripheralInstanceName);
	}
	else if (peripheralInstanceName.includes("SPI"))
	{
		return getSPIDriverlibName(interfaceName, peripheralInstanceName);
	}
	else if (peripheralInstanceName.includes("I2C"))
	{
		if (peripheralInstanceName.includes("CM-I2C"))
		{
			return getCMI2CDriverlibName(interfaceName, peripheralInstanceName);
		}
		else
		{
			return getI2CDriverlibName(interfaceName, peripheralInstanceName);
		}
	}
	else if (peripheralInstanceName.includes("CAN"))
	{
		if (peripheralInstanceName.includes("MCAN"))
		{
			return getMCANDriverlibName(interfaceName, peripheralInstanceName);
		}
		else
		{
			return getCANDriverlibName(interfaceName, peripheralInstanceName);
		}
	}
	else if (peripheralInstanceName.includes("EPWM"))
	{
		return getEPWMDriverlibName(interfaceName, peripheralInstanceName);
	}
	else if (peripheralInstanceName.includes("MCPWM"))
	{
		return getMCPWMDriverlibName(interfaceName, peripheralInstanceName);
	}
	else if (peripheralInstanceName.includes("OUTPUTXBAR"))
	{
		return getOUTPUTXBARDriverlibName(interfaceName, peripheralInstanceName);
	}
	else if (peripheralInstanceName.includes("OTHER"))
	{
		return getOTHERDriverlibName(interfaceName, peripheralInstanceName);
	}
	else if (peripheralInstanceName.includes("FSI"))
	{
		return getFSIDriverlibName(interfaceName, peripheralInstanceName);
	}	
	else if (peripheralInstanceName.includes("EQEP"))
	{
		return getEQEPDriverlibName(interfaceName, peripheralInstanceName);
	}
	else if (peripheralInstanceName.includes("EMIF1"))
	{
		return getEMIF1DriverlibName(interfaceName, peripheralInstanceName);
	}
	else if (peripheralInstanceName.includes("EMIF2"))
	{
		return getEMIF2DriverlibName(interfaceName, peripheralInstanceName);
	}
	else if (peripheralInstanceName.includes("MCBSP"))
	{
		return getMCBSPDriverlibName(interfaceName, peripheralInstanceName);
	}
	else if (peripheralInstanceName.includes("SD"))
	{
		return getSDDriverlibName(interfaceName, peripheralInstanceName);
	}
	else if (peripheralInstanceName.includes("UPP"))
	{
		return getUPPDriverlibName(interfaceName, peripheralInstanceName);
	}
	else if (peripheralInstanceName.includes("LIN"))
	{
		return getLINDriverlibName(interfaceName, peripheralInstanceName);
	}
	else if (peripheralInstanceName.includes("DC-DC"))
	{
		return getDCDCDriverlibName(interfaceName, peripheralInstanceName);
	}
	else if (peripheralInstanceName.includes("PMBUS"))
	{
		return getPMBUSDriverlibName(interfaceName, peripheralInstanceName);
	}
	else if (peripheralInstanceName.includes("SSI"))
	{
		return getSSIDriverlibName(interfaceName, peripheralInstanceName);
	}
	else if (peripheralInstanceName.includes("ECAT"))
	{
		return getECATDriverlibName(interfaceName, peripheralInstanceName);
	}
	else if (peripheralInstanceName.includes("ETHERNET"))
	{
		return getETHERNETDriverlibName(interfaceName, peripheralInstanceName);
	}
	else if (peripheralInstanceName.includes("HIC"))
	{
		return getHICDriverlibName(interfaceName, peripheralInstanceName);
	}
	
	return "";
}


//SCI
function getSCIDriverlibName(interfaceName, peripheralInstanceName)
{
	var driverlibName = "";

	driverlibName = interfaceName.replace("@", peripheralInstanceName[3]);

	return driverlibName;
}
//ANALOG
function getANALOGDriverlibName(interfaceName, peripheralInstanceName)
{
	var driverlibName = "";

	driverlibName = interfaceName.replace(/[^a-z0-9]|\s+|\r?\n|\r/gi, " ").replace(/\s+/gi, "_");

	return driverlibName;
}
//SPI
function getSPIDriverlibName(interfaceName, peripheralInstanceName)
{
	var driverlibName = "";

	driverlibName = interfaceName.replace("@", peripheralInstanceName[3]);

	return driverlibName;
}

//I2C
function getI2CDriverlibName(interfaceName, peripheralInstanceName)
{
	var driverlibName = "";

	driverlibName = interfaceName.replace("@", peripheralInstanceName[3]);

	return driverlibName;
}


//CAN
function getCANDriverlibName(interfaceName, peripheralInstanceName)
{
	var driverlibName = "";
	
	driverlibName = interfaceName.replace("@", peripheralInstanceName[3]);

	return driverlibName;
}


//EPWM
function getEPWMDriverlibName(interfaceName, peripheralInstanceName)
{
	var driverlibName = "";
	
	driverlibName = interfaceName.replace("#", peripheralInstanceName.substring(4));

	return driverlibName;
}

//MCPWM
function getMCPWMDriverlibName(interfaceName, peripheralInstanceName)
{
	var driverlibName = "";
	
	driverlibName = interfaceName.replace("#", peripheralInstanceName.substring(5));

	return driverlibName;
}

//OUTPUTXBAR
function getOUTPUTXBARDriverlibName(interfaceName, peripheralInstanceName)
{
	let driverlibName = peripheralInstanceName;
	
	return driverlibName;
}

//OTHERS
function getOTHERDriverlibName(interfaceName, peripheralInstanceName)
{
	let driverlibName = interfaceName;
	if (interfaceName == "X2")
	{
		if (["F28004x", "F28002x"].includes(system.deviceData.deviceId))
		{
			driverlibName = "GPIO18_X2"
		}
		else if (["F28P65x"].includes(system.deviceData.deviceId))
		{
			driverlibName = "GPIO221"
		}
		else
		{
			driverlibName = "GPIO18"
		}
	}
	else if (interfaceName == "X1")
	{
		if (["F28P65x"].includes(system.deviceData.deviceId))
		{
    		driverlibName = "GPIO220"
		}
		else if (["F28002x"].includes(system.deviceData.deviceId))
		{
			driverlibName = "GPIO19_X1"
		}
		else
		{
            driverlibName = "GPIO19"
		}
	}
	return driverlibName;
}

//SPECIAL NAMING
function getGPIODriverlibName(number)
{
	var driverlibName = "GPIO" + number.toString();
	if (number == "18")
	{
		if (["F28004x", "F28002x"].includes(system.deviceData.deviceId))
		{
			driverlibName = "GPIO18_X2"
		}
		else
		{
			driverlibName = "GPIO18"
		}
	}
	else if (number == "19")
	{
		driverlibName = "GPIO19"
		if (["F28002x"].includes(system.deviceData.deviceId))
		{
			driverlibName = "GPIO19_X1"
		}
	}
	return driverlibName;
}

//FSI
function getFSIDriverlibName(interfaceName, peripheralInstanceName)
{
	var driverlibName = "";
	
	driverlibName = interfaceName.replace("@", peripheralInstanceName[5])

	return driverlibName;
}


//EQEP
function getEQEPDriverlibName(interfaceName, peripheralInstanceName)
{
	var driverlibName = "";

	var EQEPInstance = peripheralInstanceName.substring(4)
	driverlibName = interfaceName.replace("#", EQEPInstance)

	return driverlibName;
}


//MCBSP
function getMCBSPDriverlibName(interfaceName, peripheralInstanceName)
{
	var driverlibName = "";

	var MCBSPInstance = peripheralInstanceName.substring(5);
	driverlibName = interfaceName.replace("@", MCBSPInstance)

	return driverlibName;
}

//EMIF1
function getEMIF1DriverlibName(interfaceName, peripheralInstanceName)
{
	var driverlibName = "";
	driverlibName = "";

	driverlibName = interfaceName

	return driverlibName;
}

//EMIF2
function getEMIF2DriverlibName(interfaceName, peripheralInstanceName)
{
	var driverlibName = "";
	driverlibName = "";

	driverlibName = interfaceName

	return driverlibName;
}


//SD
function getSDDriverlibName(interfaceName, peripheralInstanceName)
{
	var driverlibName = "";
	
	driverlibName = interfaceName.replace("#", peripheralInstanceName[2])

	return driverlibName;
}

//UPP
function getUPPDriverlibName(interfaceName, peripheralInstanceName)
{
	var driverlibName = "";
	
	driverlibName = interfaceName.replace("@", peripheralInstanceName[3]);	

	return driverlibName;
}


//LIN
function getLINDriverlibName(interfaceName, peripheralInstanceName)
{
	var driverlibName = "";

	driverlibName = interfaceName.replace("@", peripheralInstanceName[3]);

	return driverlibName;
}

//DC-DC
function getDCDCDriverlibName(interfaceName, peripheralInstanceName)
{
	var driverlibName = "";
	if(interfaceName.includes("VFBSW"))
	{
		driverlibName = "GPIO22";
	}
	if(interfaceName.includes("VSW"))
	{
		driverlibName = "GPIO23";
	}

	return driverlibName;
}


//PMBUS
function getPMBUSDriverlibName(interfaceName, peripheralInstanceName)
{
	var driverlibName = "";
	
	driverlibName = interfaceName.replace("@", peripheralInstanceName[5])

	return driverlibName;
}

//CMI2C
function getCMI2CDriverlibName(interfaceName, peripheralInstanceName)
{
	var driverlibName = "";
	driverlibName = interfaceName.replace("@" , peripheralInstanceName[6]);

	return driverlibName;
}


//MCAN
function getMCANDriverlibName(interfaceName, peripheralInstanceName)
{
	var driverlibName = "";
	
	driverlibName = interfaceName.replace("@" , peripheralInstanceName[4]);

	return driverlibName;
}

//UART
function getUARTDriverlibName(interfaceName, peripheralInstanceName)
{
	var driverlibName = "";
	
	driverlibName = interfaceName.replace("@", peripheralInstanceName[4])

	return driverlibName;
}

//SSI
function getSSIDriverlibName(interfaceName, peripheralInstanceName)
{
	var driverlibName = "";
	driverlibName = interfaceName.replace("@", peripheralInstanceName[3]);

	return driverlibName;
}


//ETHERNET
function getETHERNETDriverlibName(interfaceName, peripheralInstanceName)
{
	var driverlibName = "";
	driverlibName = interfaceName.toUpperCase();
	return driverlibName;
}

//ECAT
function getECATDriverlibName(interfaceName, peripheralInstanceName)
{
	var driverlibName = "";
	driverlibName = interfaceName;
	return driverlibName;
}

//HIC
function getHICDriverlibName(interfaceName, peripheralInstanceName)
{
	var driverlibName = "";
	driverlibName = interfaceName;
	return driverlibName;
}

function getInterfaceCCodeName(interfaceName, peripheralName){
	var interfaceName = PinmuxMigrations.interfaceMigrationRename(interfaceName, peripheralName)
	var legacyInclusiveNames = PinmuxMigrations.interfaceInclusiveRename(interfaceName, peripheralName);
	var interfaceName = legacyInclusiveNames.inclusiveName;
	return interfaceName.toUpperCase().replace("@", "").replace("#", "").replace("_", "").replace("-", "")
}
