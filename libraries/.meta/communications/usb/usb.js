let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
var HIDMouseConfigNames = ["manufacturerString_mouse", "productString_mouse", "serialNumberString_mouse", "mouseHIDInterfaceString" , "configString_mouse", "usbMouseDeviceStruct","usbMouseHandler","usbMouseMaxPowerConsumption"]
var CDCConfigNames = ["manufacturerString_cdc", "productString_cdc", "serialNumberString_cdc", "controlInterfaceString_cdc", "configString_cdc", "usbCDCTxStruct", "usbCDCRxStruct", "usbCDCTxBuffer", "usbCDCRxBuffer", "usbBufferSize", "usbCDCDeviceStruct", "usbCDCRxHandler", "usbCDCTxHandler","usbCDCControlHandler"]
var HIDKeyboardConfigNames = ["manufacturerString_keyboard", "productString_keyboard", "serialNumberString_keyboard", "keyboardHIDInterfaceString", "configString_keyboard","usbKeyboardDeviceStruct", "usbKeyboardHandler"]
var BulkConfigNames = ["manufacturerString_bulk", "productString_bulk", "dataInterfaceString", "configString_bulk", "usbBulkDeviceStruct", "usbBulkTxStruct", "usbBulkRxStruct", "usbBulkTxBuffer", "usbBulkRxBuffer", "usbBulkBufferSize", "usbBulkRxHandler", "usbBulkTxHandler"]
  
function onValidate(inst, validation)
{
  	for (var configName of CDCConfigNames)
	{
		if (inst.configName == "")
		{
			validation.logError("Value cannot be empty for ", inst.configName);
    	}
	}
    
}

function onchangeUSBMode(inst, ui)
{
    if (inst.usb_mode == "Device")
	{
        ui.deviceClasses.hidden = false;
		ui.hostApplication.hidden = true;
		ui.hcdMemorySize.hidden = true;
		ui.mouseMemorySize.hidden = true;
		ui.keyboardMemorySize.hidden = true;
		if(inst.deviceClasses == "Bulk")
		{
			ui.usb_mode_callback.hidden = false;
		}
		else
		{
			ui.usb_mode_callback.hidden = true;	
		}
		ui.usb_host_mode_power_config.hidden = true;
		ui.usb_host_hcdPool.hidden = true;
		for (var configName of CDCConfigNames)
		{
			ui[configName].hidden = false;
		}
    }
    else if (inst.usb_mode == "Host")	
	{
        ui.deviceClasses.hidden = true;
		ui.hostApplication.hidden = false;
		ui.hcdMemorySize.hidden = false;
		ui.mouseMemorySize.hidden = false;
		ui.usb_mode_callback.hidden = false;
		ui.usb_host_mode_power_config.hidden = false;
		ui.usb_host_hcdPool.hidden = false;
		for (var configName of CDCConfigNames)
		{
			ui[configName].hidden = true;
		}
		for (var configName of HIDMouseConfigNames)
		{
			ui[configName].hidden = true;
		}
		for (var configName of HIDKeyboardConfigNames)
		{
			ui[configName].hidden = true;
		}
		for (var configName of BulkConfigNames)
		{
			ui[configName].hidden = true;
		}
    }
	else if(inst.usb_mode == "Dual")
	{
		ui.deviceClasses.hidden = false;
		ui.hostApplication.hidden = false;
		ui.hcdMemorySize.hidden = false;
		ui.mouseMemorySize.hidden = false;
		ui.usb_mode_callback.hidden = false;
		ui.usb_host_mode_power_config.hidden = false;
		for (var configName of CDCConfigNames)
		{
			ui[configName].hidden = false;
		}		
		onChangeHostApplication(inst, ui)
	
	}
 
} 

function onChangeHostApplication(inst, ui)
{
	if (inst.hostApplication == "Mouse")
	{
		ui.mouseMemorySize.hidden = false;
		ui.keyboardMemorySize.hidden = true;
	}
	else if (inst.hostApplication == "Keyboard")
	{
		ui.mouseMemorySize.hidden = true;
		ui.keyboardMemorySize.hidden = false;
	}
	else if (inst.hostApplication == "Mass Storage")
	{
		ui.mouseMemorySize.hidden = true;
		ui.keyboardMemorySize.hidden = true;
	}
}


function onchangeDeviceClass(inst, ui)
{
  
	if (inst.deviceClasses == "CDC")
	{
		for (var configName of CDCConfigNames)
		{
			ui[configName].hidden = false;
		}
		for (var configName of HIDMouseConfigNames)
		{
			ui[configName].hidden = true;
		}
		for (var configName of HIDKeyboardConfigNames)
		{
			ui[configName].hidden = true;
		}
		for (var configName of BulkConfigNames)
		{
			ui[configName].hidden = true;
		}
		

	}
	else if(inst.deviceClasses == "Mouse")
	{
		for (var configName of HIDMouseConfigNames)
		{
			ui[configName].hidden = false;
		}
		for (var configName of CDCConfigNames)
		{
			ui[configName].hidden = true;
		}
		for (var configName of HIDKeyboardConfigNames)
		{
			ui[configName].hidden = true;
		}
		for (var configName of BulkConfigNames)
		{
			ui[configName].hidden = true;
		}
	}
	else if(inst.deviceClasses == "Keyboard")
	{
		for (var configName of HIDKeyboardConfigNames)
		{
			ui[configName].hidden = false;
		}
		for (var configName of HIDMouseConfigNames)
		{
			ui[configName].hidden = true;
		}
		for (var configName of CDCConfigNames)
		{
			ui[configName].hidden = true;
		}
		for (var configName of BulkConfigNames)
		{
			ui[configName].hidden = true;
		}
	}
	else if(inst.deviceClasses == "Bulk")
	{
		for (var configName of BulkConfigNames)
		{
			ui[configName].hidden = false;
		}
		for (var configName of HIDMouseConfigNames)
		{
			ui[configName].hidden = true;
		}
		for (var configName of HIDKeyboardConfigNames)
		{
			ui[configName].hidden = true;
		}
		for (var configName of CDCConfigNames)
		{
			ui[configName].hidden = true;
		}
	}
} 


let staticConfig = [
	{
        name        : "usb_mode",
        displayName : "USB Mode",
        description : 'Configure USB mode: Device/Host/Dual',
        hidden      : false,
		onChange    : onchangeUSBMode,
        default     : 'Device',
        options     : [
            { name: "Device", displayName : "Device Mode" },
            { name: "Host", displayName : "Host Mode"  },
			{ name: "Dual", displayName : "Dual Mode"  },
        ]
    },
	{
        name        : "usb_mode_callback",
        displayName : "USB Mode CallBack",
        description : 'Function called by the USB library whenever a mode change occurs',
        hidden      : true,
        default     : 'ModeCallback',
    },
	{
        name        : "usb_host_mode_power_config",
        displayName : "USB Host Mode Power Fault Configuration",
        description : 'Initialize the power fault configuration',
        hidden      : true,
        default     : ['USBHCD_VBUS_AUTO_HIGH', 'USBHCD_VBUS_FILTER'],
		options     : [
            { name: "USBHCD_FAULT_LOW", displayName : "Driver the power pin low on fault" },
            { name: "USBHCD_FAULT_HIGH", displayName : "Driver the power pin low on fault"  },
			{ name: "USBHCD_FAULT_VBUS_NONE", displayName : "No automatic action when power fault detected"  },
			{ name: "USBHCD_FAULT_VBUS_TRI", displayName : " Tri-state the pin on a power fault." },
            { name: "USBHCD_FAULT_VBUS_DIS", displayName : "Drive the USBnEPEN pin to it's inactive state on a power fault."  },
			{ name: "USBHCD_VBUS_MANUAL", displayName : "Power control is completely managed by the application"  },
			{ name: "USBHCD_VBUS_AUTO_LOW", displayName : "Set the power pin to active high" },
            { name: "USBHCD_VBUS_AUTO_HIGH", displayName : "Set the power pin to active low"  },
			{ name: "USBHCD_VBUS_FILTER", displayName : "Filter power fault"  },
			
        ]	
    },

	{
        name        : "deviceClasses",
        displayName : "Device classes",
        description : 'Device Classes supported: CDC/Mouse/Keyboard/Bulk',
        hidden      : false,
        default     : 'CDC',
		onChange    : onchangeDeviceClass,
        options     : [
            { name: "CDC", displayName : "CDC Device class" },
            { name: "Mouse", displayName : "HID Mouse Device Class"  },
			{ name: "Keyboard", displayName : "HID Keyboard Device Class"  },
			{ name: "Bulk", displayName : "Bulk Device Class"}
        ]			
		
	},
	{
        name        : "hcdMemorySize",
        displayName : "HCD Memory Size",
        description : "The size of the host controller's memory pool in bytes.",
        hidden      : true,
		default     : 128
    },

	{
        name        : "mouseMemorySize",
        displayName : "Mouse Memory Size",
        description : "The size of the mouse device interface's memory pool in bytes.",
        hidden      : true,
		default     : 128
    },
	{
        name        : "keyboardMemorySize",
        displayName : "Keyboard Memory Size",
        description : "The memory pool to provide to the keyboard device.",
        hidden      : true,
		default     : 128
    },
	{
		name 		: "hostApplication",
		displayName : "Host Application",
		description : "Host Application",
		hidden		: true,
		onChange	: onChangeHostApplication,
		default		: "Mouse",
		options     : [
            { name: "Mouse", displayName : "Host Mouse Application" },
			{ name: "Keyboard", displayName : "Host Keyboard Application"  },
			{ name: "Mass Storage", displayName : "Host Mass Storage Application"}
        ]
	},
	{
        name        : "usb_host_hcdPool",
        displayName : "HCD Pool Array name",
        description : "The memory pool to provide to the Host controller driver..",
        hidden      : true,
		default     : "g_pui8HCDPool"
    },

   	
		
]

var CDCConfig =[
    {
        name        : "manufacturerString_cdc",
        displayName : "Manufacturer string descriptor",
        description : 'Specify the Manufacturer string',
        hidden      : false,
        default     : "Texas Instruments"
    },
    {
        name        : "productString_cdc",
        displayName : "Product String descriptor",
        description : 'Specify the product string',
        hidden      : false,
        default     : "Virtual Com Port"
    },
    {
        name        : "serialNumberString_cdc",
        displayName : "Serial Number String",
        description : 'Specify the serial number string',
        hidden      : false,
        default     : "12345678"
    },
    {
        name        : "controlInterfaceString_cdc",
        displayName : "Control Interface String",
        description : 'Specify the control interface string',
        hidden      : false,
        default     : "ACM Control Interface"
    },
    {
        name        : "configString_cdc",
        displayName : "Specify the config string",
        description : 'Specify the config string',
        hidden      : false,
        default     : "Self Powered Configuration"
       
    },
	{
        name        : "usbCDCTxStruct",
        displayName : "USB CDC Tx Struct name for initialization of buffer object for transmit",
        description : "The structure used by the application to initialize a buffer object for transmit",
        hidden      : false,
		default     : "g_sTxBuffer"
    },
	{
        name        : "usbCDCRxStruct",
        displayName : "USB CDC Rx Struct name for initialization of buffer object for receive",
        description : "The structure used by the application to initialize a buffer object for receive",
        hidden      : false,
		default     : "g_sRxBuffer"
    },
	{
        name        : "usbCDCTxBuffer",
        displayName : "USB CDC Tx Buffer",
        description : "Transmit buffer name.",
        hidden      : false,
		default     : "g_pi8USBTxBuffer"
    },
	{
        name        : "usbCDCRxBuffer",
        displayName : "USB CDC Tx Buffer",
        description : "Receive buffer name",
        hidden      : false,
		default     : "g_pi8USBRxBuffer"
    },
	{
        name        : "usbBufferSize",
        displayName : "USB CDC Buffer Size",
        description : "CDC Buffer size in bytes.",
        hidden      : false,
		default     : 256
    },	
	{
        name        : "usbCDCDeviceStruct",
        displayName : "USB CDC Device Struct Name",
        description : "Structure to define operating parameters for the CDC device",
        hidden      : false,
		default     : "g_sCDCDevice"
    },
	{
        name        : "usbCDCRxHandler",
        displayName : "USB CDC Device Receive Handler",
        description : "Callback function name for CDC Receive Events",
        hidden      : false,
		default     : "RxHandler"
    },
	{
        name        : "usbCDCTxHandler",
        displayName : "USB CDC Device Transmit Handler",
        description : "Callback function name for CDC Transmit Events",
        hidden      : false,
		default     : "TxHandler"
    },
	{
        name        : "usbCDCControlHandler",
        displayName : "USB CDC Device Control Handler",
        description : "Callback function name for CDC Control Events",
        hidden      : false,
		default     : "ControlHandler"
    },	
	
]

var HIDMouseConfig =[
    {
        name        : "manufacturerString_mouse",
        displayName : "Manufacturer string descriptor",
        description : 'Specify the Manufacturer string',
        hidden      : true,
        default     : "Texas Instruments"
    },
    {
        name        : "productString_mouse",
        displayName : "Product String descriptor",
        description : 'Specify the product string',
        hidden      : true,
        default     : "MouseExample"
    },
    {
        name        : "serialNumberString_mouse",
        displayName : "Serial Number String",
        description : 'Specify the serial number string',
        hidden      : true,
        default     : "12345678"
    },
	{
        name        : "mouseHIDInterfaceString",
        displayName : "Mouse HID Interface String",
        description : 'Specify the mouse HID interface string',
        hidden      : true,
        default     : "HID Mouse Interface"
    },
    {
        name        : "configString_mouse",
        displayName : "Specify the config string",
        description : 'Specify the config string',
        hidden      : true,
        default     : "HID Mouse Configuration"
       
    },
	{
        name        : "usbMouseDeviceStruct",
        displayName : "USB Mouse Device Struct Name",
        description : "Structure to define operating parameters for the Mouse device",
        hidden      : true,
		default     : "g_sMouseDevice"
    },
	
	{
        name        : "usbMouseMaxPowerConsumption",
        displayName : "USB Mouse Max Power Consumption in milliamps",
        description : "The maximum power consumption of the device, expressed in milliamps.",
        hidden      : true,
		default     : 500
    },
	{
        name        : "usbMouseHandler",
        displayName : "USB Mouse Device Handler",
        description : "Callback function name for Mouse Events",
        hidden      : true,
		default     : "MouseHandler"
    }
	
]

var HIDKeyboardConfig =[
    {
        name        : "manufacturerString_keyboard",
        displayName : "Manufacturer string descriptor",
        description : 'Specify the Manufacturer string',
        hidden      : true,
        default     : "Texas Instruments"
    },
    {
        name        : "productString_keyboard",
        displayName : "Product String descriptor",
        description : 'Specify the product string',
        hidden      : true,
        default     : "Keyboard Example"
    },
    {
        name        : "serialNumberString_keyboard",
        displayName : "Serial Number String",
        description : 'Specify the serial number string',
        hidden      : true,
        default     : "12345678"
    },
	{
        name        : "keyboardHIDInterfaceString",
        displayName : "Keyboard HID Interface String",
        description : 'Specify the Keyboard HID interface string',
        hidden      : true,
        default     : "HID Keyboard Interface"
    },
    {
        name        : "configString_keyboard",
        displayName : "Specify the config string",
        description : 'Specify the config string',
        hidden      : true,
        default     : "HID Keyboard Configuration"
       
    },
	{
        name        : "usbKeyboardDeviceStruct",
        displayName : "USB Mouse Device Struct Name",
        description : "Structure to define operating parameters for the Keyboard device",
        hidden      : true,
		default     : "g_sKeyboardDevice"
    },
	{
        name        : "usbKeyboardHandler",
        displayName : "USB Mouse Device Handler",
        description : "Callback function name for Keyboard Events",
        hidden      : true,
		default     : "KeyboardHandler"
    }
]

var BulkConfig =[
    {
        name        : "manufacturerString_bulk",
        displayName : "Manufacturer string descriptor",
        description : 'Specify the Manufacturer string',
        hidden      : true,
        default     : "Texas Instruments"
    },
    {
        name        : "productString_bulk",
        displayName : "Product String descriptor",
        description : 'Specify the product string',
        hidden      : true,
        default     : "Generic Bulk Device"
    },
    {
        name        : "serialNumberString_bulk",
        displayName : "Serial Number String",
        description : 'Specify the serial number string',
        hidden      : true,
        default     : "12345678"
    },
	{
        name        : "dataInterfaceString",
        displayName : "Bulk Data Interface String",
        description : 'Specify the bulk data interface string',
        hidden      : true,
        default     : "Bulk Data Interface"
    },
    {
        name        : "configString_bulk",
        displayName : "Specify the config string",
        description : 'Specify the config string',
        hidden      : true,
        default     : "Bulk Data Configuration"
       
    },
	{
        name        : "usbBulkDeviceStruct",
        displayName : "USB Bulk Device Struct Name",
        description : "Structure to define operating parameters for the Bulk device",
        hidden      : true,
		default     : "g_sBulkDevice"
    },
	{
        name        : "usbBulkTxStruct",
        displayName : "USB Bulk Tx Struct name for initialization of buffer object for transmit",
        description : "The structure used by the application to initialize a buffer object for transmit",
        hidden      : true,
		default     : "g_sTxBuffer"
    },
	{
        name        : "usbBulkRxStruct",
        displayName : "USB Bulk Rx Struct name for initialization of buffer object for receive",
        description : "The structure used by the application to initialize a buffer object for receive",
        hidden      : true,
		default     : "g_sRxBuffer"
    },
	{
        name        : "usbBulkTxBuffer",
        displayName : "USB Bulk Tx Buffer",
        description : "Transmit buffer name.",
        hidden      : true,
		default     : "g_pui8USBTxBuffer"
    },
	{
        name        : "usbBulkRxBuffer",
        displayName : "USB Bulk Rx Buffer",
        description : "Receive buffer name.",
        hidden      : true,
		default     : "g_pui8USBRxBuffer"
    },
	{
        name        : "usbBulkBufferSize",
        displayName : "USB CDC Buffer Size",
        description : "Buffer size in bytes.",
        hidden      : true,
		default     : 256
    },	
	{
        name        : "usbBulkRxHandler",
        displayName : "USB Bulk Device Receive Handler",
        description : "Callback function name for Bulk Receive Events",
        hidden      : true,	
		default     : "RxHandler"
    },
	{
        name        : "usbBulkTxHandler",
        displayName : "USB Bulk Device Transmit Handler",
        description : "Callback function name for Bulk Transmit Events",
        hidden      : true,
		default     : "TxHandler"
    },
]

staticConfig = staticConfig.concat([
    // Group for CDC Device Class
    {
        name: "GROUP_CDC_DEVICE",
        displayName: "CDC Device Class Configuration",
        description: "",
        longDescription: "",
        config: CDCConfig,
		collapsed: true
    }
])

staticConfig = staticConfig.concat([
	// Group for HID Mouse Device Class
    {
        name: "GROUP_MOUSE_DEVICE",
        displayName: "HID Mouse Device Class Configuration",
        description: "",
        longDescription: "",
        config: HIDMouseConfig,
		collapsed: true
    }
])

staticConfig = staticConfig.concat([
	// Group for HID Keyboard Device Class
    {
        name: "GROUP_KEYBOARD_DEVICE",
        displayName: "HID Keyboard Device Class Configuration",
        description: "",
        longDescription: "",
        config: HIDKeyboardConfig,
		collapsed: true
    }
])

staticConfig = staticConfig.concat([
    // Group for Bulk Device Class
    {
        name: "GROUP_BULK_DEVICE",
        displayName: "Bulk Device Class Configuration",
        description: "",
        longDescription: "",
        config: BulkConfig,
		collapsed: true
    }
])

var USBLibModule = {
    c2000wareLibraryName: "USBLib",
    displayName: "USB Library",
    defaultInstanceName: "myUSBLib",
    description: "USB Library",
	//moduleInstances: moduleInstances,
	maxInstances : 1,
	modules : modules,
	config          : staticConfig,
    templates: {
        c2000ware_libraries_h           : "/libraries/communications/usb/templates/usb.c2000ware_libraries.h.xdt",
        c2000ware_libraries_c           : "/libraries/communications/usb/templates/usb.c2000ware_libraries.c.xdt",
        c2000ware_libraries_opt         : "/libraries/communications/usb/templates/usb.c2000ware_libraries.opt.xdt",
        c2000ware_libraries_cmd_genlibs : "/libraries/communications/usb/templates/usb.c2000ware_libraries.cmd.genlibs.xdt",
    },
	validate : onValidate
};

function modules(inst)
{
	if(inst.usb_mode == "Device" || inst.usb_mode == "Dual")
	{
		return [
                {
                    name: "pullInTemplateUSBStructsC",
                    moduleName: "/libraries/communications/usb/templates/usb_structs.c.dynamic.js",
                },
                {
                    name: "pullInTemplateUSBStructsH",
                    moduleName: "/libraries/communications/usb/templates/usb_structs.h.dynamic.js",
                }
            ];  
	}
	else
	{
		return [];
	}
}


exports = USBLibModule;