let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let sd_device_info = system.getScript("/driverlib/sdfm/sd_device_info.js");

let sd_clk_config = system.getScript("/driverlib/sdfm/modules/sd_clockConfiguration.js");
let sd_validate = system.getScript("/driverlib/sdfm/modules/sd_validation.js");


let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_sdfm.js");

/* Intro splash on GUI */
let longDescription = "An SDFM peripheral is four channel digital decimation filter typically used for current measurement";


/* Array of CAN configurables that are common across device families */
let config = [];

for(var channel = 1; channel <= 4; channel++)
{
config = config.concat
		(
		   [ 
		     {
				name: "Use_FilterChannel_" + channel.toString(),
				displayName : "Use Filter Channel " + channel.toString(),
				description : 'Enable / Disable Filter Channel',
				hidden      : false,
				default		: false,
				onChange	: onChangeUseFilterChannel,
			 },
		   ]
		)
}

if (sd_device_info.peripheralType == "Type2")
{
	config = config.concat
	(
	  [
	    {
			name: "GROUP_CLOCK",
			displayName: "SDCLK Source Configuration",
			description: "Select SDCLK for respective filter channels",
			collapsed	: false,
			longDescription: "",
			config: sd_clk_config.ClockConfigs,
		},	
	  ]
	)
}

let submodulesComponents = 
[  
	{
        moduleName: "/driverlib/sdfm/modules/sd_FilterConfiguration.js",
		name: "FILTER_CONFIG",
        displayName: "FILTER Configurations",
        description: "Configure Comparator and Data filter",
    },
	{
        moduleName: "/driverlib/sdfm/modules/sd_InterruptConfiguration.js",
		name: "INTERRUPT_CONFIG",
        displayName: "Interrupt Configurations",
        description: "Configure interrupt sources for SDFM",
    },
];

for (var submoduleComponent of submodulesComponents)
{
    var submodule = system.getScript(submoduleComponent.moduleName)
    config = config.concat
	(
	  [
        {
            name: "GROUP_" + submodule.defaultInstanceName,
            displayName: submodule.displayName,
            longDescription: submodule.description,
            description: "",
			collapsed : false,
            config: submodule.config,
        },
      ] 
	)
}

var available_pie_interrupts = []
var moduleInstances = undefined;

if (sd_device_info.peripheralType == "Type0")
{
	available_pie_interrupts.push({
		name: "INT_SD", displayName: "SDFM Interrupt"
	})
}

if (sd_device_info.peripheralType == "Type1" || sd_device_info.peripheralType == "Type2")
{
	available_pie_interrupts.push({
		name: "INT_SDFM", displayName: "SDFM Error Interrupt"
	})

	available_pie_interrupts.push({
		name: "INT_SDFM_DR1", displayName: "SDFM Data Ready (DR) Channel 1 Interrupt"
	})
	available_pie_interrupts.push({
		name: "INT_SDFM_DR2", displayName: "SDFM Data Ready (DR) Channel 2 Interrupt"
	})
	available_pie_interrupts.push({
		name: "INT_SDFM_DR3", displayName: "SDFM Data Ready (DR) Channel 3 Interrupt"
	})
	available_pie_interrupts.push({
		name: "INT_SDFM_DR4", displayName: "SDFM Data Ready (DR) Channel 4 Interrupt"
	})
}

config = config.concat
(
  [
    {
		name        : "registerInterrupts",
	    displayName : "Register Interrupts",
	    description : 'Which interrupts to register in the device interrupt module.',
	    hidden      : false,
		default		: [],
		minSelections: 0,
		options : available_pie_interrupts
	},
	{
        name: "useCase",
        displayName : "PinMux Use Case",
        description : 'Peripheral PinMux use case',
        hidden      : false,
        default     : 'ALL',
        options     : Pinmux.getPeripheralUseCaseNames("SD"),
        onChange    : Pinmux.useCaseChanged,
    },
  ]
)


function onChangeUseFilterChannel(inst, ui)
{
	for (var channel = 1; channel <= 4; channel++)
	{
		var status = inst["Use_FilterChannel_" + channel.toString()];
		
		if(sd_device_info.peripheralType == "Type2")
		{
		ui["Ch" + channel.toString() + "_SDCLKSEL"].hidden = !status;
		}
		
		ui["Ch" + channel.toString() + "_Mode"].hidden = !status;
		
		if (sd_device_info.peripheralType == "Type1" || sd_device_info.peripheralType == "Type2")
		{
			ui["Ch" + channel.toString() + "_ComparatorEnable"].hidden = !status;
		}
		
		ui["Ch" + channel.toString() + "_DataFilterEnable"].hidden = !status;
			
		ui["Ch" + channel.toString() + "_SD_modulatorFrequency"].hidden = !status;
		ui["Ch" + channel.toString() + "_Vclipping"].hidden = !status;
		ui["Ch" + channel.toString() + "_DC_Input"].hidden = !status;
		ui["Ch" + channel.toString() + "_bitstream_1s_density"].hidden = !status;
		ui["Ch" + channel.toString() + "_Theoritical_DataFilterOutput"].hidden = !status;
		ui["Ch" + channel.toString() + "_Theoritical_ComparatorFilterOutput"].hidden = !status;
	}
}


/*
 *  ======== filterHardware ========
 *  Control RX, TX Pin usage by the user specified dataDirection.
 *
 *  param component - hardware object describing signals and
 *                     resources they're attached to
 *
 *  returns Boolean indicating whether or not to allow the component to
 *           be assigned to an instance's $hardware config
 */
function filterHardware(component)
{
    return (Common.typeMatches(component.type, ["SD"]));
}

if (Common.onlyPinmux())
{
    config = [config[config.length - 1]];
}

var sdModule = {
    peripheralName: "SD",
    displayName: "SDFM",
    maxInstances: Common.peripheralCount("SD"),
    defaultInstanceName: "mySDFM",
    description: "Sigma Delta Peripheral",
    longDescription: (Common.getCollateralFindabilityList("SDFM")),
    filterHardware : filterHardware,
    config: config,
    moduleInstances: (inst) => {
		var regInterrupts = []

        var pinmuxQualMods = Pinmux.getGpioQualificationModInstDefinitions("SD", inst)
        for (var pinmuxQualMod of pinmuxQualMods)
        {
			if(Common.getDeviceName() == "F28004x")
			{
				pinmuxQualMod.requiredArgs = {
				   qualMode : "GPIO_QUAL_SYNC",
				}
			}
			else if((Common.getDeviceName() == "F2837xD") || (Common.getDeviceName() == "F2837xS") || (Common.getDeviceName() == "F2807x"))
			{
				pinmuxQualMod.requiredArgs = {
				   qualMode : "GPIO_QUAL_3SAMPLE",
				}
			}
			else
			{
				pinmuxQualMod.requiredArgs = {
				   qualMode : "GPIO_QUAL_ASYNC",
				}
			}
        }
        regInterrupts = regInterrupts.concat(pinmuxQualMods)

		if (inst.registerInterrupts)
		{
			var selectedRegisterInterrupts = inst.registerInterrupts;
			for (var selInt of selectedRegisterInterrupts) {
				if (selInt == "INT_SD")
				{
					regInterrupts.push({
			            name: "sdInt",      
			            displayName: "SD Interrupt",
			            moduleName: "/driverlib/interrupt.js",
			            collapsed: true,
			            args: {
			        		$name : inst.$name + "_SD_INT",
			                int : "INT_" + inst.$name,
			                pinmuxPeripheralModule : "sd",
			                driverlibInt: "INT_#"
			            }
			        })
				}
				if (selInt == "INT_SDFM")
				{
					regInterrupts.push({
			            name: "sdfmInt",      
			            displayName: "SDFM Interrupt",
			            moduleName: "/driverlib/interrupt.js",
			            collapsed: true,
			            args: {
			        		$name : inst.$name + "_SDFM_INT",
			                int : "INT_" + inst.$name + "_ERR",
			                pinmuxPeripheralModule : "sd",
			                driverlibInt: "INT_#"
			            }
			        })
				}
				if (selInt.includes("INT_SDFM_DR"))
				{
					var drNumber = selInt.replace("INT_SDFM_DR", "")
					regInterrupts.push({
			            name: "sdfmIntDr" + drNumber,      
			            displayName: "SDFM Interrupt Data Ready " + drNumber,
			            moduleName: "/driverlib/interrupt.js",
			            collapsed: true,
			            args: {
			        		$name : inst.$name + "_SDFMDR" + drNumber + "_INT",
			                int : "INT_" + inst.$name + "_DR" + drNumber,
			                pinmuxPeripheralModule : "sd",
			                driverlibInt: "INT_#DR" + drNumber
			            }
			        })
				}
			}
			

		}
		return regInterrupts;
	},
    templates: {
        boardc : "/driverlib/sdfm/sdfm.board.c.xdt",
        boardh : "/driverlib/sdfm/sdfm.board.h.xdt"
    },
    pinmuxRequirements    : Pinmux.sdPinmuxRequirements,
	validate  : sd_validate.onValidate
};

if (sdModule.maxInstances <= 0)
{
    delete sdModule.pinmuxRequirements;
}
else
{
    Pinmux.addCustomPinmuxEnumToConfig(sdModule)
    Pinmux.addPinMuxQualGroupToConfig(sdModule)
}



exports = sdModule;