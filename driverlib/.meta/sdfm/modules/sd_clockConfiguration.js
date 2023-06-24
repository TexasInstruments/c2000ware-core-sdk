let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_sdfm.js");
		
let sd_device_info = system.getScript("/driverlib/sdfm/sd_device_info.js");

var ClockConfigs = [];

let Ch1_ClockSource = 
	[
		{ name: "SDFM_CLK_SOURCE_SD1_CLK", displayName: "SD1 channel clock" },
	]
	
let Ch2_ClockSource = 
	[
		{ name: "SDFM_CLK_SOURCE_CHANNEL_CLK", displayName: "SD2 channel clock" },
		{ name: "SDFM_CLK_SOURCE_SD1_CLK", displayName: "SD1 channel clock" },
	]
	
let Ch3_ClockSource = 
	[
		{ name: "SDFM_CLK_SOURCE_CHANNEL_CLK", displayName: "SD3 channel clock" },
		{ name: "SDFM_CLK_SOURCE_SD1_CLK", displayName: "SD1 channel clock" },
	]
	
let Ch4_ClockSource = 
	[
		{ name: "SDFM_CLK_SOURCE_CHANNEL_CLK", displayName: "SD3 channel clock" },
		{ name: "SDFM_CLK_SOURCE_SD1_CLK", displayName: "SD1 channel clock" },
	]

var hide = true;

if (sd_device_info.peripheralType == "Type2")
{
ClockConfigs = ClockConfigs.concat
(
  [
	{
		name: "Ch1_SDCLKSEL",
		displayName : "Channel 1 SDCLK source",
		description : "Channel 1 SDCLK source",
		hidden      : hide,
		default     : Ch1_ClockSource[0].name,
		options     : Ch1_ClockSource,	
	},
	{
		name: "Ch2_SDCLKSEL",
		displayName : "Channel 2 SDCLK source",
		description : "Channel 2 SDCLK source",
		hidden      : hide,
		default     : Ch2_ClockSource[0].name,
		options     : Ch2_ClockSource,	
	},
	{
		name: "Ch3_SDCLKSEL",
		displayName : "Channel 3 SDCLK source",
		description : "Channel 3 SDCLK source",
		hidden      : hide,
		default     : Ch3_ClockSource[0].name,
		options     : Ch3_ClockSource,	
	},
	{
		name: "Ch4_SDCLKSEL",
		displayName : "Channel 4 SDCLK source",
		description : "Channel 4 SDCLK source",
		hidden      : hide,
		default     : Ch4_ClockSource[0].name,
		options     : Ch4_ClockSource,		
	},
  ]
);
}	
var sdClockConfigSubmodule = 
{
    displayName: "SDCLK Source Configuration",
	maxInstances: Common.peripheralCount("SD"),
    defaultInstanceName: "SDCLK_CLOCK_CONFIG",
    description: "Select SDCLK for respective filter channels",
    config: ClockConfigs,
    templates: 
	{
        boardc : "", 
        boardh : "",
    },
};

exports = 
{
	ClockConfigs : ClockConfigs,
}
