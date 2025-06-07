const device  = system.deviceData.device
/////////////////////////////////////////////Device Specific Functions//////////////////////////
// For a new device, you need to find out which functions are available for the device
// and add it to the list.
// If a new subcategory is needed, just define a new variable and address that in the related function.xdt file.
// For example, if you need a new Include Header type, you can add Include_Headers_Typex to the list and then go to Include folder and add that
//variable to the Include.xdt. Also, you need to copy and past your content to a new file, let's call Include_Headers_xxx.xdt. 

// Multi-core devices list
const multi_core 																= ["F2837xD", "F2838x", "F28P65x"]

//
// Available Include Header 
//
// General Include Header 
const Include_Headers_Type0														= ["F2838x"]

// Include Header with hw_ipc.h
const Include_Headers_Type1														= ["F2837xD"]

// Include Header with hw_lcm.h
const Include_Headers_Type2														= ["F280015x"]

// Include Header with driverlib.h  
const Include_Headers_Type3														= ["F280013x", "F28002x", "F28003x", "F28004x", "F2837xS", "F2807x", "F28P65x", "F28P55x", "F28E12x"]

//
// Available Boot_CM 
//
// Devices with Boot_CM
const Device_Boot_CM 															= ["F2838x"]

//
// Available Initilization 
//
//Function to initialize the device (suprano dual-core devices, Type0)
const Initilization_General_Type0												= ["F2837xD"]

// Function to initialize the device (suprano single-core device, Type1)
const Initilization_General_Type1												= ["F2807x", "F2837xS"]

//configuring the XTAL for device initilization
const Initilization_XTAL_Type0												= ["F28002x"]

//configuring device initilization with Device_initGPIO()
const Initilization_Device_initGPIO_Type0									= ["F2838x"]

//configuring the AGPIO pins 12, 13, 20, 21, 28 in digital mode for device initilization
const Initilization_AGPIO_Type0													= ["F280013x"]

//configuring the AGPIO pins 12, 13, 20, 21, 28 in digital mode and enabling lockstep module for device initilization
const Initilization_AGPIO_Type1													= ["F280015x"]

//configuring the GPIO pins 22, 23 in digital mode and Disabling DC DC in Analog block for device initilization
const Initilization_GPIO_22_23											= ["F28004x"]

//configuring the GPIO pins 20, 21 in digital mode and Lock VREGCTL Register for device initilization
const Initilization_GPIO_20_21_Type0										= ["F28003x"]

//configuring the Lock VREGCTL Register for device initilization
const Initilization_AGPIO_Dual_Core_Type0										= ["F28P65x"]

//configuring the GPIO pins 11, 12, 13, 16, 17, 20, 21, 24, 
// and 28 in digital mode, turn on all peripherals, and Lock VREGCTL Register for device initilization
const Initilization_GPIO_11_28										= ["F28P55x"]

//configuring the GPIO pins 12, 13 and 28 in digital mode, turn on all peripherals,
//and Lock VREGCTL Register for device initilization
const Initilization_GPIO_12_28										= ["F28E12x"]

//
// Available InitGPIO 
//
// Disabling pin locks and enabling pullups on GPIOs Port A-Port F.
const InitGPIO_PortA_PortF_Type0 											= ["F2838x", "F2837xD", "F2837xS", "F2807x"]

// Disabling pin locks and enabling pullups on GPIOs only Ports A, B, and H.
const InitGPIO_PortA_PortH_Type0 											= ["F28002x", "F28003x", "F28004x", "F280013x", "F280015x","F28E12x"]

// Disabling pin locks and enabling pullups on GPIOs Ports A, B, C, D, E, F, and H.
const InitGPIO_PortA_PortH_Type1 											= ["F28P65x"]

// Disabling pin locks and enabling pullups on GPIOs only Ports A, B, C, G, and H.
const InitGPIO_PortA_PortH_Type2 											= ["F28P55x"]

//
// Available VerifyXTAL 
//
// verifying the XTAL frequency
const VerifyXTAL_Type0														= ["F2838x"]

// verifying the XTAL frequency with Turning-on XTAL
const VerifyXTAL_Type1 														= ["F28002x", "F28003x", "F28004x", "F28P65x", "F28P55x"]

// verifying the XTAL frequency
const VerifyXTAL_Type2														= ["F28E12x"]

//
// Available BootCPU2 
//
// Boot CPU2 to Flash Sector 0 to Sector 13 
const Boot_CPU2_Type0														=["F2838x"]

// Boot CPU2 to Flash Bank 0 to Bank 4
const Boot_CPU2_Type1														=["F28P65x"]

// Boot CPU2 with different boot mode. It can be from PARALLEL, SCI, SPI, I2C, CAN, RAM, and FLASH.
const Boot_CPU2_Boot_Mode_Type0												=["F2837xD"]

//
// Available Enable_Unbounded_GPIO_Pullups 
//
// enable pullups for the unbonded GPIOs on the 100PZ or 176PTP package.
const Enable_Unbounded_GPIO_Pullups_100PZ_176PTP_Type0						=["F2837xD", "F2837xS", "F2807x"]

// enable pullups for the unbonded GPIOs on the 176PTP package.
const Enable_Unbounded_GPIO_Pullups_176PTP_Type0							=["F2838x"]

// enable pullups for the unbonded GPIOs on the 48PT, 32RHB, 32VFC package.
const Enable_Unbounded_GPIO_Pullups_48PT_32RHB_32VFC_Type0					=["F28E12x"]

//
// Available Configure_TMX_Analog_Trim 
//
// Implementing Analog trim of TMX devices with ADC A, ADC B, and ADC D
const Configure_TMX_Analog_Trim_Type0										=["F2807x"]

// Implementing Analog trim of TMX devices with ADC A, ADC B, ADC C, and ADC D
const Configure_TMX_Analog_Trim_Type1										=["F2837xS"]

// Implementing Analog trim of TMX devices with ADC A, ADC B, ADC C, and ADC D starting with If condition
const Configure_TMX_Analog_Trim_Type2										=["F2837xD"]

//
// Available EnableAllPeripherals 
//
// Enabling HRCAL for F2838x with checking if context is on CPU1. If enabling HRCAL in your device needs 
//to be done only in CPU1, add your device to this list.
const EnableAllPeripherals_CLK_HRCAL								= ["F2838x"]

// Enabling HRPWM for F2837xD with checking if context is on CPU1. If enabling HRPWM in your device needs 
//to be done only in CPU1, add your device to this list.
const EnableAllPeripherals_CLK_HRPWM								= ["F2837xD"]

// Enabling EMIF with checking if context is on CPU1. If enabling EMIF in your device needs 
//to be done only in CPU1, add your device to this list.
const EnableAllPeripherals_CLK_EMIF_With_If									= ["F2837xD", "F2838x", "F28P65x"]

// Checking devices need enabling peripheral EMIF1. If peripheral EMIF1 needs to be enabled 
//in your device, add your device to this list.
const EnableAllPeripherals_CLK_EMIF1										= [ "F2837xS", "F2807x" ]

// Checking devices need enabling peripheral EMIF2. If peripheral EMIF2 needs to be enabled 
//in your device, add your device to this list.
const EnableAllPeripherals_CLK_EMIF2										= ["F2837xS"]

// Enabling USB and UPPA with checking if context is on CPU1. If enabling USB or UPPA in your device needs 
//to be done only in CPU1, add your device to this list.
const EnableAllPeripherals_CLK_USB_UPPA							= ["F2838x", "F2837xD"]

// Checking devices with SysCtl_enablePeripheral for peripheral USBA. If peripheral USBA needs to be enabled 
//in your device, add your device to this list.
const EnableAllPeripherals_CLK_USBA											= ["F2837xS", "F2807x", "F28P65x", "F28P55x"]

// Checking devices with SysCtl_enablePeripheral for peripheral UPPA. If peripheral UPPA needs to be enabled 
//in your device, add your device to this list.
const EnableAllPeripherals_CLK_UPPA											= ["F2837xS"]

// Enabling DCC and ECAT, and MCAN with checking if context is on CPU1. If enabling DCC and ECAT, and MCAN  
//in your device needs to be done only in CPU1, add your device to this list.
const EnableAllPeripherals_CLK_DCC_ECAT_MCAN							= ["F2838x"]

// Enabling CLA1BGCRC with checking if context is on CPU1. If enabling CLA1BGCRC  
//in your device needs to be done only in CPU1, add your device to this list.
const EnableAllPeripherals_CLK_CLA1BGCRC							= ["F2838x", "F28003x"]

// Enabling PMBUSA with checking if context is on CPU1. If enabling PMBUSA  
//in your device needs to be done only in CPU1, add your device to this list.
const EnableAllPeripherals_CLK_PMBUSA									= [ "F2838x", "F280015x", "F28002x", "F28003x", "F28004x", "F28P55x"]

// Enabling CLA1 with checking if context is on CPU1. If enabling CLA1  
//in your device needs to be done only in CPU1, add your device to this list.
const EnableAllPeripherals_CLK_CLA1									= ["F2838x", "F2837xD", "F2837xS", "F2807x", "F28003x", "F28004x", "F28P55x"]

//
// Clocktree 
//
// clocktree Configuring Analog Trim in case of untrimmed or TMX sample
const clocktree_Analog_Trim_Type0                                         	=["F2837xD", "F2807x", "F2837xS"]

// clocktree Setting up PLL control and clock dividers
const clocktree_PLL_Ctl_Dividers_Type0                                 		=["F2837xD", "F2807x", "F2837xS","F280013x", "F280015x", "F28002x", "F28003x", "F28004x", "F28P55x"]

// clocktree Setting up PLL and AUXPLL control and clock dividers
//and AUXPLL control and clock dividers needed for CMCLK
const clocktree_PLL_Ctl_Dividers_Type1                                  =["F2838x"]

// clocktree Setting up PLL control and clock dividers
//and AUXPLL control and clock dividers needed for CMCLK
const clocktree_PLL_Ctl_Dividers_Type2                                  =["F28P65x"]

// clocktree Setting up PLL control and clock dividers
const clocktree_PLL_Ctl_Dividers_Type3                                 		=["F28E12x"]

// clocktree asserts will check that the #defines for the clock rates in device.h
//set clock source for CANA, CANB, MCAN peripherals and EPWM and EMIF1 clock divider
const clocktree_Asserts_Type0                                          =["F2837xD", "F2807x", "F2837xS"]

// clocktree asserts will check that the #defines for the clock rates in device.h
//set clock source for CANA, CANB, MCAN, ECAT, ENET peripherals and EPWM and EMIF1 clock divider
const clocktree_Asserts_Type1                                          =["F2838x"]

// clocktree asserts will check that the #defines for the clock rates in device.h
//set clock source for CANA, MCANA, MCANB, ECAT peripherals and EPWM and EMIF1 clock divider
const clocktree_Asserts_Type2                                          =["F28P65x"]

// clocktree asserts will check that the #defines for the clock rates in device.h
//set clock source for CANA and MCAN peripherals
const clocktree_Asserts_Type3                                          =["F28003x","F280015x"]

// clocktree asserts will check that the #defines for the clock rates in device.h
//set clock source for CANA peripheral
const clocktree_Asserts_Type4                                          =["F280013x", "F28002x", "F28004x"]

// clocktree asserts will check that the #defines for the clock rates in device.h
// CLK divider for LIN
const clocktree_Asserts_Type5                                          =["F28P55x"]

// clocktree asserts will check that the #defines for the clock rates in device.h
const clocktree_Asserts_Type6                                          =["F28E12x"]

///////////////////////////List of Template Files For Different Functions///////////////////////////
// If you want to add a new sub-function from available functions, you need to create a .xdt file in related function folder
// and add it here.

// Template for General Header
var Include 	= system.getTemplate('Include/Include.xdt');

// Template for Boot_CM
var Boot_CM = system.getTemplate('BootCM/Boot_CM.xdt');

// Template for device initilization
var Initilization = system.getTemplate('Initilization/Initilization.xdt');

// Template for disabling pin locks and enabling pullups on GPIOs Port A-Port F.
var InitGPIO = system.getTemplate('InitGPIO/InitGPIO.xdt');

// Template for verifying the XTAL frequency
var VerifyXTAL = system.getTemplate('VerifyXTAL/VerifyXTAL.xdt');

// Template for Error handling function
var Error_Handling = system.getTemplate('ErrorChecking/Error_Handling.xdt');

// Template for boot CPU2 
var Boot_CPU2 = system.getTemplate('BootCPU2/Boot_CPU2.xdt');

// Template for enable unbounded GPIO pullups
var Enable_Unbounded_GPIO_Pullups = system.getTemplate('EnableUnboundedGPIOPullups/Enable_Unbounded_GPIO_Pullups.xdt');

// Template for implementing Analog trim of TMX devices 
var Configure_TMX_Analog_Trim = system.getTemplate('ConfigureTMXAnalogTrim/Configure_TMX_Analog_Trim.xdt');

// Template for enabling all the peripherals
var Enable_All_Peripherals 	= system.getTemplate('EnableAllPeripherals/Enable_All_Peripherals.xdt');


exports = {
	Include : Include ,
	Boot_CM : Boot_CM,
	Initilization : Initilization,
	InitGPIO : InitGPIO,
	VerifyXTAL : VerifyXTAL,
	Error_Handling : Error_Handling,
	Boot_CPU2 : Boot_CPU2,
	Enable_Unbounded_GPIO_Pullups : Enable_Unbounded_GPIO_Pullups,
	Configure_TMX_Analog_Trim : Configure_TMX_Analog_Trim,
	Enable_All_Peripherals : Enable_All_Peripherals,
	device : device,
	multi_core : multi_core,
	Include_Headers_Type0 : Include_Headers_Type0,
	Include_Headers_Type1 : Include_Headers_Type1,
	Include_Headers_Type2 : Include_Headers_Type2,
	Include_Headers_Type3 : Include_Headers_Type3,
	Device_Boot_CM  : Device_Boot_CM ,
	Initilization_General_Type0 : Initilization_General_Type0,
	Initilization_General_Type1 : Initilization_General_Type1,
	Initilization_AGPIO_Type0	 : Initilization_AGPIO_Type0	,
	Initilization_AGPIO_Type1 : Initilization_AGPIO_Type1	,
	Initilization_GPIO_22_23 : Initilization_GPIO_22_23,
	Initilization_GPIO_20_21_Type0 : Initilization_GPIO_20_21_Type0,
	Initilization_AGPIO_Dual_Core_Type0 : Initilization_AGPIO_Dual_Core_Type0,
	Initilization_GPIO_11_28 : Initilization_GPIO_11_28,
	Initilization_GPIO_12_28 : Initilization_GPIO_12_28,
	Initilization_XTAL_Type0 : Initilization_XTAL_Type0,
	Initilization_Device_initGPIO_Type0 : Initilization_Device_initGPIO_Type0,
	InitGPIO_PortA_PortF_Type0 : InitGPIO_PortA_PortF_Type0,
	InitGPIO_PortA_PortH_Type0 : InitGPIO_PortA_PortH_Type0,
	InitGPIO_PortA_PortH_Type1 : InitGPIO_PortA_PortH_Type1,
	InitGPIO_PortA_PortH_Type2 : InitGPIO_PortA_PortH_Type2,
	VerifyXTAL_Type0 : VerifyXTAL_Type0,
	VerifyXTAL_Type1 : VerifyXTAL_Type1,
	VerifyXTAL_Type2 : VerifyXTAL_Type2,
    Boot_CPU2_Type0 : Boot_CPU2_Type0,
	Boot_CPU2_Type1 : Boot_CPU2_Type1,
	Boot_CPU2_Boot_Mode_Type0 : Boot_CPU2_Boot_Mode_Type0,
	Enable_Unbounded_GPIO_Pullups_100PZ_176PTP_Type0 : Enable_Unbounded_GPIO_Pullups_100PZ_176PTP_Type0,
	Enable_Unbounded_GPIO_Pullups_176PTP_Type0 : Enable_Unbounded_GPIO_Pullups_176PTP_Type0,
	Enable_Unbounded_GPIO_Pullups_48PT_32RHB_32VFC_Type0 : Enable_Unbounded_GPIO_Pullups_48PT_32RHB_32VFC_Type0,
	Configure_TMX_Analog_Trim_Type0 : Configure_TMX_Analog_Trim_Type0,
	Configure_TMX_Analog_Trim_Type1 : Configure_TMX_Analog_Trim_Type1,
	Configure_TMX_Analog_Trim_Type2 : Configure_TMX_Analog_Trim_Type2,
	EnableAllPeripherals_CLK_HRCAL : EnableAllPeripherals_CLK_HRCAL,
	EnableAllPeripherals_CLK_HRPWM : EnableAllPeripherals_CLK_HRPWM,
	EnableAllPeripherals_CLK_EMIF_With_If : EnableAllPeripherals_CLK_EMIF_With_If,
	EnableAllPeripherals_CLK_EMIF1 : EnableAllPeripherals_CLK_EMIF1,
	EnableAllPeripherals_CLK_EMIF2: EnableAllPeripherals_CLK_EMIF2,
	EnableAllPeripherals_CLK_USB_UPPA : EnableAllPeripherals_CLK_USB_UPPA,
	EnableAllPeripherals_CLK_USBA : EnableAllPeripherals_CLK_USBA,
	EnableAllPeripherals_CLK_UPPA : EnableAllPeripherals_CLK_UPPA,
	EnableAllPeripherals_CLK_DCC_ECAT_MCAN : EnableAllPeripherals_CLK_DCC_ECAT_MCAN,
	EnableAllPeripherals_CLK_CLA1BGCRC : EnableAllPeripherals_CLK_CLA1BGCRC,
	EnableAllPeripherals_CLK_PMBUSA : EnableAllPeripherals_CLK_PMBUSA,
	EnableAllPeripherals_CLK_CLA1 : EnableAllPeripherals_CLK_CLA1,
	clocktree_Analog_Trim_Type0 : clocktree_Analog_Trim_Type0,
	clocktree_PLL_Ctl_Dividers_Type0 : clocktree_PLL_Ctl_Dividers_Type0,
	clocktree_PLL_Ctl_Dividers_Type1 : clocktree_PLL_Ctl_Dividers_Type1,
	clocktree_PLL_Ctl_Dividers_Type2 : clocktree_PLL_Ctl_Dividers_Type2,
	clocktree_PLL_Ctl_Dividers_Type3 : clocktree_PLL_Ctl_Dividers_Type3,
	clocktree_Asserts_Type0 : clocktree_Asserts_Type0,
	clocktree_Asserts_Type1 : clocktree_Asserts_Type1,
	clocktree_Asserts_Type2 : clocktree_Asserts_Type2, 
	clocktree_Asserts_Type3 : clocktree_Asserts_Type3,
	clocktree_Asserts_Type4 : clocktree_Asserts_Type4,
	clocktree_Asserts_Type5 : clocktree_Asserts_Type5,
	clocktree_Asserts_Type6 : clocktree_Asserts_Type6 

}