let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

var interruptRename = {
	F28004x: {
		sd: {
			name: "SD",
			rename: "SDFM"
		}
	},
	F2838x: {
		sd: {
			name: "SD",
			rename: "SDFM"
		}
	},
	F28003x: {
		sd: {
			name: "SD",
			rename: "SDFM"
		}
	},
	F280013x: {
		sd: {
			name: "SD",
			rename: "SDFM"
		}
	},
	F28P65x: {
		sd: {
			name: "SD",
			rename: "SDFM"
		}
	}

}

function renameInterrupt(pinmuxPeripheralModule, ownerSolutionPeripheralName)
{
	var deviceInterruptRename = interruptRename[Common.getDeviceName()]
	if (deviceInterruptRename)
	{
		var devIntRenPinMuxPeriphMod = deviceInterruptRename[pinmuxPeripheralModule]
		if (devIntRenPinMuxPeriphMod)
		{
			return ownerSolutionPeripheralName.replace(devIntRenPinMuxPeriphMod.name, devIntRenPinMuxPeriphMod.rename)
		}
	}
	return ownerSolutionPeripheralName
}

exports = {
	renameInterrupt : renameInterrupt
}