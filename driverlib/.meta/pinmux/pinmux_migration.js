exports = {
	interfaceMigrationRename : interfaceMigrationRename,
	interfaceInclusiveRename : interfaceInclusiveRename,
	interfacePinMuxMigrationRenameCompleted : interfacePinMuxMigrationRenameCompleted,
	useCaseInclusiveRename: useCaseInclusiveRename
};


function useCaseInclusiveRename(useCaseName, peripheralName)
{
	var inclusiveRenameTable = {
		"SPI" : {
			"3-WIRE MASTER": "3-WIRE CONTROLLER",
			"3-WIRE SLAVE": "3-WIRE PERIPHERAL",
		}
	}

	//Retrieves the inclusive names for the IP's interface
	var renameInclusive = inclusiveRenameTable[peripheralName]
	if (renameInclusive)
	{
		var renameInclusiveName = renameInclusive[useCaseName]
		if (renameInclusiveName)
		{
			return renameInclusiveName
		}
	}

	return useCaseName
}


function interfaceInclusiveRename(interfaceName, peripheralName)
{
	var inclusiveRenameTable = {
		"SPI" : {
			"SPI@_SIMO": "SPI@_PICO",
			"SPI@_SOMI": "SPI@_POCI",
			"SPISIMO@": "SPI@_PICO",
			"SPISOMI@": "SPI@_POCI",
			"SPICLK@" :  "SPI@_CLK",
			"SPI@_STEn" : "SPI@_PTE",
			"SPISTE@" :  "SPI@_PTE",
			"SPI_STE@" :  "SPI@_PTE",
			"SPI@_STE" :  "SPI@_PTE"
		}
	}

	var legacyNameTable = {
		"SPI" : {
			"SPI@_PICO": ["SPI@_SIMO", "SPISIMO@"],
			"SPI@_POCI": ["SPI@_SOMI", "SPISOMI@"],
			"SPI@_CLK" :  ["SPICLK@"],
			"SPI@_PTE" : ["SPI@_STEn", "SPISTE@", "SPI_STE@", "SPI@_STE"]
		}
	}

	//Retrieves the inclusive names for the IP's interface
	var renameInclusive = inclusiveRenameTable[peripheralName]
	//Retrieves the legacy names for the IP's interface
	var renameLegacy = legacyNameTable[peripheralName]

	//If either rename's are null, it does not exist in the table and so must return
	//original names
	if(!renameInclusive || !renameLegacy)
	{
		var originalName = {
			inclusiveName: interfaceName,
			//legacyName: [interfaceName]
		}
		return originalName;
	}

	//The two assignments below will conflict, but this is the only method of checking
	//that one of them returns null to assign it the proper value, since interfaceName
	//is never null
	var legacyInclusiveNames = {
		//inclusiveName uses the interfaceName to find the inclusive name,
		//where interfaceName is assumed to be the legacy name
		inclusiveName: renameInclusive[interfaceName],
		//legacyName uses the interfaceName to find the legacy name, where
		//interfaceName is assumed to be an inclusive name
		legacyName: renameLegacy[interfaceName]
	}

	if(!renameInclusive[interfaceName])
	{
		//inclusiveName uses the interfaceName as the inclusive name,
		//since it could not be found when used as a legacy name
		legacyInclusiveNames.inclusiveName = interfaceName;
	}
	if(!renameLegacy[interfaceName])
	{
		//legacyName uses the interfaceName as the legacy name because
		//it cannot be found when used as an inclusive name
		legacyInclusiveNames.legacyName = [interfaceName];
	}
	//console.log(legacyInclusiveNames)
	return legacyInclusiveNames;
}

function interfaceMigrationRename(interfaceName, peripheralName)
{
	//console.log(system.deviceData)
	var migrationRenameTable = {
		"SCI" : {
			"SCIRXD@": "SCI@_RX",
			"SCITXD@": "SCI@_TX",
		},
		"I2C" : {
			"SCL@": "I2C@_SCL",
			"SDA@": "I2C@_SDA",
		},
		"SPI" : {
			"SPISIMO@" : "SPI@_SIMO",
			"SPISOMI@" : "SPI@_SOMI",
			"SPICLK@" :  "SPI@_CLK",
			"SPISTE@" :  "SPI@_STE",
			"SPI@_STEn" : "SPI@_STE",
			"SPI_STE@" : "SPI@_STE"
		},
		"EPWM" : {
			"EPWM#A" : "EPWM#_A",
			"EPWM#B" : "EPWM#_B",
		},
		"EQEP" : {
			"EQEP#A" : "EQEP#_A", 
			"EQEP#B" : "EQEP#_B", 
			"EQEP#S" : "EQEP#_STROBE", 
			"EQEP#I" : "EQEP#_INDEX", 
		},
		"CAN" : {
			"CANRX@" : "CAN@_RX", 
			"CANTX@" : "CAN@_TX", 
		},
		"EMIF1": {
			"EM1A0" : "EMIF1_A0",
			"EM1A1" : "EMIF1_A1",
			"EM1A2" : "EMIF1_A2",
			"EM1A3" : "EMIF1_A3",
			"EM1A4" : "EMIF1_A4",
			"EM1A5" : "EMIF1_A5",
			"EM1A6" : "EMIF1_A6",
			"EM1A7" : "EMIF1_A7",
			"EM1A8" : "EMIF1_A8",
			"EM1A9" : "EMIF1_A9",
			"EM1A10" : "EMIF1_A10",
			"EM1A11" : "EMIF1_A11",
			"EM1A12" : "EMIF1_A12",
			"EM1A13" : "EMIF1_A13",
			"EM1A14" : "EMIF1_A14",
			"EM1A15" : "EMIF1_A15",
			"EM1A16" : "EMIF1_A16",
			"EM1A17" : "EMIF1_A17",
			"EM1A18" : "EMIF1_A18",
			"EM1A19" : "EMIF1_A19",
			"EM1BA0" : "EMIF1_BA0",
			"EM1BA1" : "EMIF1_BA1",
			"EM1CAS" : "EMIF1_CAS",
			"EM1CLK" : "EMIF1_CLK",
			"EM1CS0n" : "EMIF1_CS0n",
			"EM1CS2n" : "EMIF1_CS2n",
			"EM1CS3n" : "EMIF1_CS3n",
			"EM1CS4n" : "EMIF1_CS4n",
			"EM1D0" : "EMIF1_D0",
			"EM1D1" : "EMIF1_D1",
			"EM1D2" : "EMIF1_D2",
			"EM1D3" : "EMIF1_D3",
			"EM1D4" : "EMIF1_D4",
			"EM1D5" : "EMIF1_D5",
			"EM1D6" : "EMIF1_D6",
			"EM1D7" : "EMIF1_D7",
			"EM1D8" : "EMIF1_D8",
			"EM1D9" : "EMIF1_D9",
			"EM1D10" : "EMIF1_D10",
			"EM1D11" : "EMIF1_D11",
			"EM1D12" : "EMIF1_D12",
			"EM1D13" : "EMIF1_D13",
			"EM1D14" : "EMIF1_D14",
			"EM1D15" : "EMIF1_D15",
			"EM1D16" : "EMIF1_D16",
			"EM1D17" : "EMIF1_D17",
			"EM1D18" : "EMIF1_D18",
			"EM1D19" : "EMIF1_D19",
			"EM1D20" : "EMIF1_D20",
			"EM1D21" : "EMIF1_D21",
			"EM1D22" : "EMIF1_D22",
			"EM1D23" : "EMIF1_D23",
			"EM1D24" : "EMIF1_D24",
			"EM1D25" : "EMIF1_D25",
			"EM1D26" : "EMIF1_D26",
			"EM1D27" : "EMIF1_D27",
			"EM1D28" : "EMIF1_D28",
			"EM1D29" : "EMIF1_D29",
			"EM1D30" : "EMIF1_D30",
			"EM1D31" : "EMIF1_D31",
			"EM1DQM0" : "EMIF1_DQM0",
			"EM1DQM1" : "EMIF1_DQM1",
			"EM1DQM2" : "EMIF1_DQM2",
			"EM1DQM3" : "EMIF1_DQM3",
			"EM1OEn" : "EMIF1_OEn",
			"EM1RAS" : "EMIF1_RAS",
			"EM1RNW" : "EMIF1_RNW",
			"EM1SDCKE" :"EMIF1_SDCKE",
			"EM1WAIT" : "EMIF1_WAIT",
			"EM1WEn" : "EMIF1_WEn",
		},
		"EMIF2": {
			"EM2A0" : "EMIF2_A0",
			"EM2A1" : "EMIF2_A1",
			"EM2A2" : "EMIF2_A2",
			"EM2A3" : "EMIF2_A3",
			"EM2A4" : "EMIF2_A4",
			"EM2A5" : "EMIF2_A5",
			"EM2A6" : "EMIF2_A6",
			"EM2A7" : "EMIF2_A7",
			"EM2A8" : "EMIF2_A8",
			"EM2A9" : "EMIF2_A9",
			"EM2A10" : "EMIF2_A10",
			"EM2A11" : "EMIF2_A11",
			"EM2A12" : "EMIF2_A12",
			"EM2A13" : "EMIF2_A13",
			"EM2A14" : "EMIF2_A14",
			"EM2A15" : "EMIF2_A15",
			"EM2A16" : "EMIF2_A16",
			"EM2A17" : "EMIF2_A17",
			"EM2A18" : "EMIF2_A18",
			"EM2A19" : "EMIF2_A19",
			"EM2BA0" : "EMIF2_BA0",
			"EM2BA1" : "EMIF2_BA1",
			"EM2CAS" : "EMIF2_CAS",
			"EM2CLK" : "EMIF2_CLK",
			"EM2CS0n" : "EMIF2_CS0n",
			"EM2CS2n" : "EMIF2_CS2n",
			"EM2CS3n" : "EMIF2_CS3n",
			"EM2CS4n" : "EMIF2_CS4n",
			"EM2D0" : "EMIF2_D0",
			"EM2D1" : "EMIF2_D1",
			"EM2D2" : "EMIF2_D2",
			"EM2D3" : "EMIF2_D3",
			"EM2D4" : "EMIF2_D4",
			"EM2D5" : "EMIF2_D5",
			"EM2D6" : "EMIF2_D6",
			"EM2D7" : "EMIF2_D7",
			"EM2D8" : "EMIF2_D8",
			"EM2D9" : "EMIF2_D9",
			"EM2D10" : "EMIF2_D10",
			"EM2D11" : "EMIF2_D11",
			"EM2D12" : "EMIF2_D12",
			"EM2D13" : "EMIF2_D13",
			"EM2D14" : "EMIF2_D14",
			"EM2D15" : "EMIF2_D15",
			"EM2D16" : "EMIF2_D16",
			"EM2D17" : "EMIF2_D17",
			"EM2D18" : "EMIF2_D18",
			"EM2D19" : "EMIF2_D19",
			"EM2D20" : "EMIF2_D20",
			"EM2D21" : "EMIF2_D21",
			"EM2D22" : "EMIF2_D22",
			"EM2D23" : "EMIF2_D23",
			"EM2D24" : "EMIF2_D24",
			"EM2D25" : "EMIF2_D25",
			"EM2D26" : "EMIF2_D26",
			"EM2D27" : "EMIF2_D27",
			"EM2D28" : "EMIF2_D28",
			"EM2D29" : "EMIF2_D29",
			"EM2D30" : "EMIF2_D30",
			"EM2D31" : "EMIF2_D31",
			"EM2DQM0" : "EMIF2_DQM0",
			"EM2DQM1" : "EMIF2_DQM1",
			"EM2DQM2" : "EMIF2_DQM2",
			"EM2DQM3" : "EMIF2_DQM3",
			"EM2OEn" : "EMIF2_OEn",
			"EM2RAS" : "EMIF2_RAS",
			"EM2RNW" : "EMIF2_RNW",
			"EM2SDCKE" :"EMIF2_SDCKE",
			"EM2WAIT" : "EMIF2_WAIT",
			"EM2WEn" : "EMIF2_WEn",
		}
	}

	var rename = migrationRenameTable[peripheralName]
	if (rename)
	{
		if (rename[interfaceName])
		{
			return rename[interfaceName]
		}
	}

	return interfaceName
}

//
// This function is only called in pinmux.board.c.xdt for those modules that we manually
// Fix their pinmux config names. We only do this for EPWM right now outside fo the 
// inclusive terminology
//
function interfacePinMuxMigrationRenameCompleted(interfaceName, peripheralName)
{
	//console.log(system.deviceData)
	var migrationRenameTable = {
		"EPWM" : {
			"EPWM#A" : "EPWM#_A",
			"EPWM#B" : "EPWM#_B",
		},
	}

	var rename = migrationRenameTable[peripheralName]
	if (rename)
	{
		if (rename[interfaceName])
		{
			return rename[interfaceName]
		}
	}

	return interfaceName
}
