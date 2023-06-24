

var device_info = 
[
{device: "F280049", addInstance: ["PLL_FMULT","PLL_ADD"]},
{device: "F2837xD", addInstance: ["PLL_FMULT","PLL_ADD"]},




let FreqLabels = ["OSCCLK","VCOCLK", "PLLRAWCLK", "PLLSYSCLK", "CPUCLK", "SYSCLK", "LSPCLK", "CANBITCLK"]

let All_Instance_Entries = [
	"INTOSC1","INTOSC2","XTAL","X1","XTAL_OR_X1","OSCCLKSRCSEL","Watchdog_domain",
	"PLL_IMULT","PLL_FMULT","PLL_ADD","PLL_ODIV","SYSPLLCTL1","SYSCLKDIVSEL",
	"CPU","NMIWD_domain","LOSPCP","CLKSRCCTL2",	"CAN_CLOCK_domain",	"PERx_SYSCLK_GATE",
	"PERx_SYSCLK_domain","CPUCLK_domain","PERx_LSPCLK_GATE","LSPCLK_domain",
	"SYSCLK_domain"
]

let OSCCLK_Entries = [
	"INTOSC1","INTOSC2","XTAL","X1","XTAL_OR_X1","OSCCLKSRCSEL", "OSCCLK"
]

let PLL_Entries = [
	"OSCCLK", "PLL_IMULT","PLL_FMULT","PLL_ADD","PLL_ODIV", "VCOCLK", "PLLRAWCLK"
]

let PLLSYSCLK_Entries = ["OSCCLK", "PLLRAWCLK", "SYSPLLCTL1","SYSCLKDIVSEL", "NMIWD_domain", "PLLSYSCLK"]

let CPUCLK_Entries = ["PLLSYSCLK", "CPU", "CPUCLK", "CPUCLK_domain"]

let SYSCLK_Entries = ["XTAL","X1","XTAL_OR_X1", "PLLSYSCLK", "CPU", "SYSCLK", "CLKSRCCTL2",	"CAN_CLOCK_domain",	"PERx_SYSCLK_GATE",
"PERx_SYSCLK_domain","PERx_LSPCLK_GATE","LSPCLK_domain","SYSCLK_domain", "CANBITCLK", "LOSPCP", "LSPCLK"]


All_Instance_Entries = All_Instance_Entries.concat(FreqLabels)