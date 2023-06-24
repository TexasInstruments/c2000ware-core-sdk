let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let useComparator = system.getScript("/driverlib/sdfm/modules/sd_comparatorFilter.js");
let useDatafilter = system.getScript("/driverlib/sdfm/modules/sd_DataFilter.js");

let sd_device_info = system.getScript("/driverlib/sdfm/sd_device_info.js");
let sd_definition  = system.getScript("/driverlib/sdfm/sdfm_board_definition_c.js");	

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_sdfm.js");

var filterConfigs = [];
let density_1s = 0;
let Theoretical_Data_Filter = 0;
let Theoretical_Comparator_Filter = 0;


var hide = true;

// SDModulator settings //
function SDmodulatorSettings(channel)
{	
	var Settings = [];
	
	density_1s = (inst) => {
                var temp= (inst["Ch" + channel.toString() + "_DC_Input"] + inst["Ch" + channel.toString() + "_Vclipping"]) / (2 * inst["Ch" + channel.toString() + "_Vclipping"]);
                return temp;}
	
	Theoretical_Data_Filter = (inst) => {
				var temp = Math.floor((Math.abs(inst["Ch" + channel.toString() + "_DC_Input"]) / inst["Ch" + channel.toString() + "_Vclipping"])*sd_definition.getShiftvalue(inst["Ch" + channel.toString() + "_FilterType_D"], inst["Ch" + channel.toString() + "_DOSR"], 0 , inst["Ch" + channel.toString() + "_DataFilter_Representation"]));
				if(inst["Ch" + channel.toString() + "_DC_Input"] < 0)
				{
					temp = -1 * temp;
				}
				return temp;}
				
	Theoretical_Comparator_Filter = (inst) => {
				var temp = (inst["Ch" + channel.toString() + "_DC_Input"] + inst["Ch" + channel.toString() + "_Vclipping"]) / (2 * inst["Ch" + channel.toString() + "_Vclipping"]) * sd_definition.getShiftvalue(inst["Ch" + channel.toString() + "_FilterType"], inst["Ch" + channel.toString() + "_COSR"], 0 , "SDFM_DATA_FORMAT_32_BIT");
				return temp;}
				
	Settings = 
	[
		{
			name: "Ch" + channel.toString() + "_SD_modulatorFrequency",
			displayName : "SD Modulator Frequency (MHz)",
			description : 'Select SD Modulator Frequency in MHz',
			hidden      : hide,
			default     : 20,
		},
		{
			name        : "Ch" + channel.toString() + "_Vclipping",
			displayName : "Differential clipping voltage (V)",
			description : 'What is the full scale range of SD modulator',
			hidden      : hide,
			default     : 0.32,
		},
		{
			name        : "Ch" + channel.toString() + "_DC_Input",
			displayName : "DC input to SD-modulator (V)",
			description : 'What is the DC input to SD-modulator',
			hidden      : hide,
			default     : 0,
		},
		{
			name        : "Ch" + channel.toString() + "_bitstream_1s_density",
			displayName : "Bitstream 1's density",
			description : 'Density of 1s in SD modulated bitstream',
			hidden      : hide,
 		    getValue    : density_1s,
            default     : 0,
		},
		{
			name        : "Ch" + channel.toString() + "_Theoritical_DataFilterOutput",
			displayName : "Theoritical Data filter Output",
			description : 'Theoritical Data filter Output',
			hidden      : hide,
			getValue    : Theoretical_Data_Filter,
		    default     : 0,
		},
		{
			name        : "Ch" + channel.toString() + "_Theoritical_ComparatorFilterOutput",
			displayName : "Theoritical Comparator filter Output",
			description : 'Theoritical Comparator filter Output',
			hidden      : hide,
			getValue    : Theoretical_Comparator_Filter,
		    default     : 0,
		},

	]
	return(Settings);
}


function fill_filter_array()
{
	var cconfig = 
		[
			{
				name: "Ch" + channel.toString() + "_Mode",
				displayName : "SD Modulator mode",
				description : 'SD Modulator mode',
				hidden      : hide,
				default     : sd_device_info.SDFM_ModulatorClockMode[0].name,
				options     : sd_device_info.SDFM_ModulatorClockMode,	
			},
			{
				name: "Ch" + channel.toString() + "_DataFilterEnable",
				displayName : "Enable Data Filter",
				description : 'Enable / Disable Data Filter',
				hidden      : hide,
				default     : false,
				onChange	: useDatafilter.onChangeDataFilterEnable
			},
		]
		
		if(sd_device_info.peripheralType == "Type1" || sd_device_info.peripheralType == "Type2")
		{
			cconfig = cconfig.concat([
			{
				name: "Ch" + channel.toString() + "_ComparatorEnable",
				displayName : "Enable Comparator",
				description : 'Enable Comparator',
				hidden      : hide,
				default     : false,
				onChange    : useComparator.onChangeComparatorEnable
			},
			])
		}
		
		cconfig = cconfig.concat([
			{
				name        : "GROUP_ComparatorFilter",
				displayName : "ComparatorFilter Settings",
				config      : useComparator.comparatorSettings(channel)
			},
			{
				name        : "GROUP_DataFilter",
				displayName : "DataFilter Settings",
				config      : useDatafilter.datafilterSettings(channel)
			},
			{
				name        : "GROUP_SDMod",
				displayName : "SD_modulator_Settings",
				collapsed	: false,
				config      : SDmodulatorSettings(channel)
			},

			])
	return(cconfig);
}	

for (var channel = 1; channel <= 4; channel++)
{
	filterConfigs = filterConfigs.concat
	(
	  [
	   {
        name: "GROUP_FILTER" + channel.toString(),
        displayName: "Filter" + channel.toString(),
        description: "Configure Filter" + channel.toString(),
		collapsed	: true,
        longDescription: "",
        config: fill_filter_array(),
	   }
	  ]
	);
}

useComparator.onChangeComparatorEnable
useDatafilter.onChangeDataFilterEnable
	
var sdFilterConfigSubmodule = 
{
    displayName: "FILTER Configurations",
	maxInstances: Common.peripheralCount("SD"),
    defaultInstanceName: "SD_FILTER_CONFIG",
    description: "Configure Comparator and Data filter",
    config: filterConfigs,
    templates: 
	{
        boardc : "", 
        boardh : "",
    },
};

exports = sdFilterConfigSubmodule;
