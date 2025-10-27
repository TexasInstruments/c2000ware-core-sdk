exports = {
	getExtraInputOptions : getExtraInputOptions
};

function getExtraInputOptions()
{
	var deviceName = system.deviceData.deviceId;
	if (["F28003x", "F28002x", "F28004x", "F2838x", "F280013x", "F280015x","F28P65x","F28P55x","F28P551x","F28E12x"].includes(deviceName))
	{
		return [
			{name: "0xFFFE", displayName : "LOGIC HIGH ('1' selected input)"},
			{name: "0xFFFF", displayName : "LOGIC LOW ('0' selected input)"}
		];
	}
	else
	{
		return [];
	}
}