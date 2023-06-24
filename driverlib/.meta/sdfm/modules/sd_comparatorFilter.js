let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_sdfm.js");
		
let sd_device_info = system.getScript("/driverlib/sdfm/sd_device_info.js");

var HTLZ_Enable = 
[
	{name: "Enable" , value : "32768"},
    {name: "Disable", value : "0"},
]

function onChangeComparatorEnable(inst, ui)
{
	for (var channel = 1; channel <= 4; channel++)
	{
		var status;
		if(sd_device_info.peripheralType == "Type1" || sd_device_info.peripheralType == "Type2")
		{
		 status = inst["Ch" + channel.toString() + "_ComparatorEnable"];
		}
		else
		{
		 status = inst["Use_FilterChannel_" + channel.toString()];
		}
		
		ui["Ch" + channel.toString() + "_FilterType"].hidden = !status;
		ui["Ch" + channel.toString() + "_COSR"].hidden = !status;
		ui["Ch" + channel.toString() + "_Datarate_CF"].hidden = !status;
		ui["Ch" + channel.toString() + "_Latency_CF"].hidden  = !status;
		
		
		if (sd_device_info.peripheralType == "Type0" || sd_device_info.peripheralType == "Type1")
		{
			ui["Ch" + channel.toString() + "_HLT"].hidden = !status;
			ui["Ch" + channel.toString() + "_LLT"].hidden = !status;
			
			if(sd_device_info.peripheralType == "Type1")
			{
				ui["Ch" + channel.toString() + "_HLTZ_Enable"].hidden = !status;
				ui["Ch" + channel.toString() + "_HLTZ"].hidden = !status;
			}
		}	
		if(sd_device_info.peripheralType == "Type2")
		{
			ui["Ch" + channel.toString() + "_HLT1"].hidden = !status;
			ui["Ch" + channel.toString() + "_HLT2"].hidden = !status;
			ui["Ch" + channel.toString() + "_HLTZ_Enable"].hidden = !status;
			ui["Ch" + channel.toString() + "_HLTZ"].hidden = !status;
			ui["Ch" + channel.toString() + "_LLT1"].hidden = !status;
			ui["Ch" + channel.toString() + "_LLT2"].hidden = !status;
			
			for(var event = 1; event<=2 ;event++)
			{
			  ui["Ch" + channel.toString() + "_CEVT" + event.toString() + "_SourceSelect"].hidden = !status;
			  ui["Ch" + channel.toString() + "_Use_CEVT" + event.toString() + "_Digital_Filter"].hidden = !status;
			}
		}
	}
	
	var status_compEN;
	var status_use_int = inst.useInterrupts;
	
	if(sd_device_info.peripheralType == "Type1" || sd_device_info.peripheralType == "Type2")
	{
		status_compEN = (inst.Ch1_ComparatorEnable || inst.Ch2_ComparatorEnable || inst.Ch3_ComparatorEnable || inst.Ch4_ComparatorEnable);
	}
	else
	{
		status_compEN = true;
	}
	
	if(sd_device_info.peripheralType == "Type0" || sd_device_info.peripheralType == "Type1")
	{
		ui.IEH.hidden = ((!status_use_int) || (!status_compEN));
		ui.IEL.hidden = ((!status_use_int) || (!status_compEN));
	}
	
	if(sd_device_info.peripheralType == "Type2")
	{
		ui.CEVT1.hidden = ((!status_use_int) || (!status_compEN));
		ui.CEVT2.hidden = ((!status_use_int) || (!status_compEN));
	}	
}

 function onChangeCEVT_Digital_filterSettings(inst, ui)
 {
	for (var channel = 1; channel <= 4; channel++)
	{	
	  for(var event = 1; event <= 2; event++)
	  {	
	    var status = inst["Ch" + channel.toString() + "_Use_CEVT" + event.toString() + "_Digital_Filter"];
		
		ui["Ch" + channel.toString() + "_InitFilterCEVT" + event.toString() +""].hidden = !status;
		ui["Ch" + channel.toString() + "_SamplePrescale_CEVT" + event.toString() +""].hidden = !status;
		ui["Ch" + channel.toString() + "_Threshold_CEVT" + event.toString() +""].hidden = !status;
		ui["Ch" + channel.toString() + "_SampleWindow_CEVT" + event.toString() +""].hidden = !status;
	  }
	}
}



var hide;

if (sd_device_info.peripheralType == "Type0")
{
	hide = false; //Comparator settings not hidden when SDFM is Type 0
}
else
{
	hide = true; //Comparator settings hidden when SDFM is Type 1 / 2 and get enabled only when Comparator is enabled
}


function iterate(item) 
{
  var settings = [];
  for(var i = 0; i< item.length; i++)
  {
  	settings =  settings.concat((({ name, displayName }) => ({ name, displayName }))(item[i]));
  	//console.log((({ name, displayName }) => ({ name, displayName }))(item[i]));
  }
  	return settings;
}

var Settings = [];



// Comparator Filter settings //
function comparatorSettings(channel)
{	
var order = 0;
	Settings = 
	[
		{
			name: "Ch" + channel.toString() + "_FilterType",
			displayName : "FilterType",
			description : 'Select FilterType for Comparator Filter',
			hidden      : hide,
			default     : iterate(sd_device_info.SDFM_FilterType)[3].name,
			options     : iterate(sd_device_info.SDFM_FilterType),	
		}, 
		{
			name: "Ch" + channel.toString() + "_COSR",
			displayName : "COSR",
			description : 'Select OSR for Comparator Filter (1 to 32)',
			hidden      : hide,
			default     : 32,
		},
		{
			name        : "Ch" + channel.toString() + "_Datarate_CF",
			displayName : "Data rate (us)",
			description : 'Data rate (Data filter) for given DOSR setting and SDmodulator rate',
			hidden      : hide,
		    getValue    : (inst) => {
                var datarate = inst["Ch" + channel.toString() + "_COSR"] / inst["Ch" + channel.toString() + "_SD_modulatorFrequency"];
                return datarate;
            },
            default     : 0,
		},
		{
			name        : "Ch" + channel.toString() + "_Latency_CF",
			displayName : "Latency (us)",
			description : 'Latency (or) settling time (Data filter) for given COSR setting and SDmodulator rate',
			hidden      : hide,
		    getValue    : (inst) => {
				if(inst["Ch" + channel.toString() + "_FilterType"] == "SDFM_FILTER_SINC_FAST" || inst["Ch" + channel.toString() + "_FilterType"] == "SDFM_FILTER_SINC_3")
				{
					order = 3;
				}
				if(inst["Ch" + channel.toString() + "_FilterType"] == "SDFM_FILTER_SINC_2")
				{
					order = 2;
				}
				if(inst["Ch" + channel.toString() + "_FilterType"] == "SDFM_FILTER_SINC_1")
				{
					order = 1;
				}
                var latency = order * inst["Ch" + channel.toString() + "_COSR"] / inst["Ch" + channel.toString() + "_SD_modulatorFrequency"];
                return latency;
            },
            default     : 0,
		},
		
	]
	
	if (sd_device_info.peripheralType == "Type0" || sd_device_info.peripheralType == "Type1")
	{
		Settings = Settings.concat([ 
		{
			name: "Ch" + channel.toString() + "_HLT",
			displayName : "High Level Threshold",
			description : 'High Threshold Level (0 to 32767)',
			hidden      : hide,
			default     : 32767,
		},	
		{
			name: "Ch" + channel.toString() + "_LLT",
			displayName : "Low Level Threshold",
			description : 'Low Threshold Level (0 to 32767)',
			hidden      : hide,
			default     : "0",
		},
		])
	}	

	if (sd_device_info.peripheralType == "Type1")
	{
		Settings = Settings.concat([ 
		{
			name: "Ch" + channel.toString() + "_HLTZ",
			displayName : "High Level Threshold (Z)",
			description : 'High Threshold Level (Z) (0 to 32767)',
			hidden      : hide,
			default     : "32767",
		},	
		{
			name: "Ch" + channel.toString() + "_HLTZ_Enable",
			displayName : "Use High Threshold (Z)",
			description : 'High Threshold Level Z (0 to 32767)',
			hidden      : hide,
			default		: false,
		},
		])
	}	
	
	if (sd_device_info.peripheralType == "Type2")
	{
			Settings = Settings.concat
			(
			  [ 
				{
					name: "Ch" + channel.toString() + "_HLT1",
					displayName : "High Level Threshold 1",
					description : 'High Threshold Level 1 (0 to 32767)',
					hidden      : hide,
					default     : "32767",
				},	
				{
					name: "Ch" + channel.toString() + "_HLT2",
					displayName : "High Level Threshold 2",
					description : 'High Threshold Level 2 (0 to 32767)',
					hidden      : hide,
					default     : "32767",
				},
				{
					name: "Ch" + channel.toString() + "_HLTZ_Enable",
					displayName : "Use High Threshold (Z)",
					description : 'High Threshold Level Z (0 to 32767)',
					hidden      : hide,
					default		: false,
				},
				{
					name: "Ch" + channel.toString() + "_HLTZ",
					displayName : "High Level Threshold (Z)",
					description : 'High Threshold Level (Z) (0 to 32767)',
					hidden      : hide,
					default     : "32767",
				},
				{
					name: "Ch" + channel.toString() + "_LLT1",
					displayName : "Low Level Threshold 1",
					description : 'Low Threshold Level 1  (0 to 32767)',
					hidden      : hide,
					default     : "0",
				},
				{
					name: "Ch" + channel.toString() + "_LLT2",
					displayName : "Low Level Threshold 2",
					description : 'Low Threshold Level 2  (0 to 32767)',
					hidden      : hide,
					default     : "0",
				},	
			  ]
			)
			
			for(var event = 1; event <= 2; event++)
			{
				var eventSource;
				
				if(event == 1)
				{
				  eventSource = sd_device_info.SDFM_CompEvent1Source;
				}
				if(event == 2)
				{
				  eventSource = sd_device_info.SDFM_CompEvent2Source;
				}
				
				Settings = Settings.concat
				(
			      [
    				{
					name: "Ch" + channel.toString() + "_CEVT" + event.toString() + "_SourceSelect",
					displayName : "Comparator Event" + event.toString() + " SourceSelect",
					description : "Select Comparator Event" + event.toString(),
					hidden      : hide,
					default     : eventSource[0].name,
					options		: eventSource,
					},
					{
					name: "Ch" + channel.toString() + "_Use_CEVT" + event.toString() + "_Digital_Filter",
					displayName : "Use CEVT" + event.toString() + " Digital Filter",
					description : "Use CEVT" + event.toString() + " Digital Filter",
					hidden      : hide,
					default     : false,
					onChange	: onChangeCEVT_Digital_filterSettings,
					},
					{
					name        : "GROUP" + event.toString() + "_CEVT_Digital Filter" + channel.toString() +"",
					displayName : "CEVT" + event.toString() + " Digital Filter settings",
					collapsed	: false,
					config      : 
					[
					{
					name        : "Ch" + channel.toString() + "_InitFilterCEVT" + event.toString() + "",
					displayName : "Initialize Digital Filter (CEVT" + event.toString() + ")",
					description : "Initialize Digital Filter (CEVT" + event.toString() + ")",
					hidden      : hide,
					default     : true
					},	
					{
					name        : "Ch" + channel.toString() + "_SamplePrescale_CEVT" + event.toString() + "",
					displayName : "CEVT" + event.toString() + " Prescale",
					description : 'The number of system clock cycles between samples.',
					hidden      : hide,
					default     : 0
					},
					{
					name        : "Ch" + channel.toString() + "_Threshold_CEVT" + event.toString() + "",
					displayName : "CEVT" + event.toString() + " Threshold",
					description : 'The number of FIFO samples to monitor.',
					hidden      : hide,
					default     : 0
					},
					{
					name        : "Ch" + channel.toString() + "_SampleWindow_CEVT" + event.toString() + "",
					displayName : "CEVT" + event.toString() + " Sample Window",
					description : 'The number of FIFO samples to monitor.',
					hidden      : hide,
					default     : 0
					},
					]
				    },
				  ]
                )	
			}
	}
	
	return(Settings);
}
// Comparator Filter settings //



exports = 
{
	comparatorSettings : comparatorSettings,
	onChangeComparatorEnable : onChangeComparatorEnable,
}
