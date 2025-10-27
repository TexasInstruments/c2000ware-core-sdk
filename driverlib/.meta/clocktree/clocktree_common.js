var DualCore 	= system.getTemplate('dualCore/dualCore.xdt');
var DualCore_CPU2 	= system.getTemplate('dualCore/dualCore_CPU2.xdt');
var SingleCore  = system.getTemplate('singleCore/singleCore.xdt');

const multi_core = ["F2837xD", "F2838x", "F28P65x"]
const xtal_x1_macro = ["F2837xS", "F2837xD", "F2807x"]                                      //In Soprano, we do not differentiate between XTAL and X1 macro

const PLL_type1  = ["F2837xS", "F2837xD", "F2807x", "F28004x"]					            //FMULT available 	| REFDIV unavailable
const PLL_type2  = ["F2838x", "F28002x", "F28003x", "F280013x", "F280015x", "F28P65x", "F28P55x", "F28P551x"] //FMULT unavailable	| REFDIV available
const PLL_type3  = ["F28E12x"] //QDIV, PDIV, RDIVCLK0

const AUXPLL_Support 		= ["F2837xS", "F2807x", "F2837xD", "F2838x", "F28P65x"]
const EPWM_div_support 		= ["F2837xS", "F2837xD", "F2807x", "F28P65x"]                   //ePWM clock divider support

const device  = system.deviceData.device
var XTAL_OR_X1 		= system.clockTree.XTAL_OR_X1

exports = {
    DualCore : DualCore,
    DualCore_CPU2 : DualCore_CPU2,
    SingleCore : SingleCore,
    multi_core : multi_core,
    xtal_x1_macro : xtal_x1_macro,
    PLL_type1 : PLL_type1,
    PLL_type2 : PLL_type2,
    PLL_type3 : PLL_type3,
    device : device,
    AUXPLL_Support : AUXPLL_Support,
    EPWM_div_support : EPWM_div_support,
    XTAL_OR_X1 : XTAL_OR_X1
}