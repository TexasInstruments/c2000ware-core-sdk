let EPG_OutputSelect = [
	{ name: "EPG_OUT_SEL_SIG", displayName: "Signal Generator mux output" },
	{ name: "EPG_OUT_SEL_CLK", displayName: "Clock Generator mux output" },
]
let EPG_SignalGenOut = [
	{ name: "EPG_SIGGEN0_DATATRANOUT0", displayName: "Signal Generator 0 Data Transform out 0" },
	{ name: "EPG_SIGGEN0_DATATRANOUT1", displayName: "Signal Generator 0 Data Transform out 1" },
	{ name: "EPG_SIGGEN0_DATATRANOUT2", displayName: "Signal Generator 0 Data Transform out 2" },
	{ name: "EPG_SIGGEN0_DATATRANOUT3", displayName: "Signal Generator 0 Data Transform out 3" },
	{ name: "EPG_SIGGEN0_DATATRANOUT4", displayName: "Signal Generator 0 Data Transform out 4" },
	{ name: "EPG_SIGGEN0_DATATRANOUT5", displayName: "Signal Generator 0 Data Transform out 5" },
	{ name: "EPG_SIGGEN0_DATATRANOUT6", displayName: "Signal Generator 0 Data Transform out 6" },
	{ name: "EPG_SIGGEN0_DATATRANOUT7", displayName: "Signal Generator 0 Data Transform out 7" },
]
let EPG_ClockGenOut = [
	{ name: "EPG_CLKGEN0_CLKOUT0_DCLK", displayName: "Clock Generator 0 Clk output 0 DCLK" },
	{ name: "EPG_CLKGEN0_CLKOUT1_DCLK", displayName: "Clock Generator 0 Clk output 1 DCLK" },
	{ name: "EPG_CLKGEN0_CLKOUT2_DCLK", displayName: "Clock Generator 0 Clk output 2 DCLK" },
	{ name: "EPG_CLKGEN0_CLKOUT3_DCLK", displayName: "Clock Generator 0 Clk output 3 DCLK" },
	{ name: "EPG_CLKGEN1_CLKOUT0_DCLK", displayName: "Clock Generator 1 Clk output 0 DCLK" },
	{ name: "EPG_CLKGEN1_CLKOUT1_DCLK", displayName: "Clock Generator 1 Clk output 1 DCLK" },
	{ name: "EPG_CLKGEN1_CLKOUT2_DCLK", displayName: "Clock Generator 1 Clk output 2 DCLK" },
	{ name: "EPG_CLKGEN1_CLKOUT3_DCLK", displayName: "Clock Generator 1 Clk output 3 DCLK" },
]
let EPG_ClockGenGclkOut = [
	{ name: "EPG_CLKGEN0_CLKOUT0_GCLK", displayName: "Clock Generator 0 Clk output 0 GCLK" },
	{ name: "EPG_CLKGEN0_CLKOUT1_GCLK", displayName: "Clock Generator 0 Clk output 1 GCLK" },
	{ name: "EPG_CLKGEN0_CLKOUT2_GCLK", displayName: "Clock Generator 0 Clk output 2 GCLK" },
	{ name: "EPG_CLKGEN0_CLKOUT3_GCLK", displayName: "Clock Generator 0 Clk output 3 GCLK" },
	{ name: "EPG_CLKGEN1_CLKOUT0_GCLK", displayName: "Clock Generator 1 Clk output 0 GCLK" },
	{ name: "EPG_CLKGEN1_CLKOUT1_GCLK", displayName: "Clock Generator 1 Clk output 1 GCLK" },
	{ name: "EPG_CLKGEN1_CLKOUT2_GCLK", displayName: "Clock Generator 1 Clk output 2 GCLK" },
	{ name: "EPG_CLKGEN1_CLKOUT3_GCLK", displayName: "Clock Generator 1 Clk output 3 GCLK" },
]
let EPG_ClockStopEdge = [
	{ name: "EPG_CLK_STOP_EDGE_CLKOUT0", displayName: "Stop on Clk output 0" },
	{ name: "EPG_CLK_STOP_EDGE_CLKOUT1", displayName: "Stop on Clk output 1" },
	{ name: "EPG_CLK_STOP_EDGE_CLKOUT2", displayName: "Stop on Clk output 2" },
	{ name: "EPG_CLK_STOP_EDGE_CLKOUT3", displayName: "Stop on Clk output 3" },
]
let EPG_SignalGenMode = [
	{ name: "EPG_SIGGEN_MODE_BIT_BANG", displayName: "BIT BANG MODE" },
	{ name: "EPG_SIGGEN_MODE_SHIFT_RIGHT_ONCE", displayName: "SHIFT RIGHT ONCE MODE" },
	{ name: "EPG_SIGGEN_MODE_ROTATE_RIGHT_ONCE", displayName: "ROTATE RIGHT ONCE MODE" },
	{ name: "EPG_SIGGEN_MODE_ROTATE_RIGHT_REPEAT", displayName: "ROTATE RIGHT REPEAT MODE" },
	{ name: "EPG_SIGGEN_MODE_SHIFT_LEFT_ONCE", displayName: "SHIFT LEFT ONCE MODE" },
	{ name: "EPG_SIGGEN_MODE_ROTATE_LEFT_ONCE", displayName: "ROTATE LEFT ONCE MODE" },
	{ name: "EPG_SIGGEN_MODE_ROTATE_LEFT_REPEAT", displayName: "ROTATE LEFT REPEAT" },
	{ name: "EPG_SIGGEN_MODE_SHIFT_RIGHT_REPEAT", displayName: "SHIFT RIGHT REPEAT MODE" },
	{ name: "EPG_SIGGEN_MODE_SHIFT_LEFT_REPEAT", displayName: "SHIGT LEFT REPEAT MODE" },
]
let EPG_SignalGenData0In = [
	{ name: "EPG_SIGGEN_DATA0_DATA_NEXT0", displayName: "DATA TRANSFORM NEXT[0]" },
	{ name: "EPG_SIGGEN_DATA0_EPGIN0", displayName: "EPG Input 0" },
	{ name: "EPG_SIGGEN_DATA0_EPGIN1", displayName: "EPG Input 1" },
	{ name: "EPG_SIGGEN_DATA0_EPGIN2", displayName: "EPG Input 2" },
	{ name: "EPG_SIGGEN_DATA0_EPGIN3", displayName: "EPG Input 3" },
	{ name: "EPG_SIGGEN_DATA0_EPGIN4", displayName: "EPG Input 4" },
	{ name: "EPG_SIGGEN_DATA0_EPGIN5", displayName: "EPG Input 5" },
	{ name: "EPG_SIGGEN_DATA0_EPGIN6", displayName: "EPG Input 6" },
	{ name: "EPG_SIGGEN_DATA0_EPGIN7", displayName: "EPG Input 7" },
]
let EPG_SignalGenData63In = [
	{ name: "EPG_SIGGEN_DATA63_DATA_NEXT63", displayName: "DATA TRANSFORM NEXT[63]" },
	{ name: "EPG_SIGGEN_DATA63_EPGIN0", displayName: "EPG Input 0" },
	{ name: "EPG_SIGGEN_DATA63_EPGIN1", displayName: "EPG Input 1" },
	{ name: "EPG_SIGGEN_DATA63_EPGIN2", displayName: "EPG Input 2" },
	{ name: "EPG_SIGGEN_DATA63_EPGIN3", displayName: "EPG Input 3" },
	{ name: "EPG_SIGGEN_DATA63_EPGIN4", displayName: "EPG Input 4" },
	{ name: "EPG_SIGGEN_DATA63_EPGIN5", displayName: "EPG Input 5" },
	{ name: "EPG_SIGGEN_DATA63_EPGIN6", displayName: "EPG Input 6" },
	{ name: "EPG_SIGGEN_DATA63_EPGIN7", displayName: "EPG Input 7" },
]
let EPG_OUT = [
	{ name: "EPG_OUT0", displayName: "EPG Output 0" },
	{ name: "EPG_OUT1", displayName: "EPG Output 1" },
	{ name: "EPG_OUT2", displayName: "EPG Output 2" },
	{ name: "EPG_OUT3", displayName: "EPG Output 3" },
	{ name: "EPG_OUT4", displayName: "EPG Output 4" },
	{ name: "EPG_OUT5", displayName: "EPG Output 5" },
	{ name: "EPG_OUT6", displayName: "EPG Output 6" },
]
let EPG_SIGGEN = [
	{ name: "EPG_SIGGEN0", displayName: "Signal Generator 0" },
	{ name: "EPG_SIGGEN1", displayName: "Signal Generator 1" },
]
let EPG_CLKGEN = [
	{ name: "EPG_CLKGEN0", displayName: "Clock Generator 0" },
	{ name: "EPG_CLKGEN1", displayName: "<! Clock Generator 1" },
]
let EPG_DataIn = [
	{ name: "EPG_DATAIN_MCANARX", displayName: "MCANA Receive input (RX)" },
	{ name: "EPG_DATAIN_MCANBRX", displayName: "MCANB Receive input (RX)" },
	{ name: "EPG_DATAIN_LINARX", displayName: "LINA Receive input (RX)" },
	{ name: "EPG_DATAIN_FSIAD0RX", displayName: "FSI AD0 Receive Input (RX)" },
	{ name: "EPG_DATAIN_FSIAD1RX", displayName: "FSI AD1 Receive Input (RX)" },
	{ name: "EPG_DATAIN_FSIARX_CLK", displayName: "FSI Receive Clock Input Signal" },
	{ name: "EPG_DATAIN_SPIA_CLK", displayName: "SPIA Clock Signal" },
	{ name: "EPG_DATAIN_SPIA_PICO", displayName: "SPIA Peripheral in Controller out Signal" },
	{ name: "EPG_DATAIN_SPIA_POCI", displayName: "SPIA Peripheral out Controller in Signal" },
	{ name: "EPG_DATAIN_SPIA_PTE", displayName: "SPIA Peripheral Transmit Enable Signal" },
	{ name: "EPG_DATAIN_SPIB_CLK", displayName: "SPIB Clock Signal" },
	{ name: "EPG_DATAIN_SPIB_PICO", displayName: "SPIB Peripheral in COntroller out Signal" },
	{ name: "EPG_DATAIN_SPIB_POCI", displayName: "SPIB Peripheral out Controller in Signal" },
	{ name: "EPG_DATAIN_SPIB_PTE", displayName: "SPIB Peripheral Transmit Enable Signal" },
	{ name: "EPG_DATAIN_I2CA_SDA", displayName: "I2CA Serial Data Line" },
	{ name: "EPG_DATAIN_I2CA_SCL", displayName: "I2CA Serial Clock Line" },
	{ name: "EPG_DATAIN_I2CB_SDA", displayName: "I2CB Serial Data Line" },
	{ name: "EPG_DATAIN_I2CB_SCL", displayName: "I2CB Serial Clock Line" },
	{ name: "EPG_DATAIN_SCIARX", displayName: "SCIA Receive input (RX)" },
	{ name: "EPG_DATAIN_SCIBRX", displayName: "SCIB Receive input (RX)" },
	{ name: "EPG_DATAIN_SCICRX", displayName: "SCIC Receive input (RX)" },
	{ name: "EPG_DATAIN_EQEP1A", displayName: "EQEP1 Signal A" },
	{ name: "EPG_DATAIN_EQEP1B", displayName: "EQEP1 Signal B" },
	{ name: "EPG_DATAIN_EQEP1I", displayName: "EQEP1 Index signal" },
	{ name: "EPG_DATAIN_EQEP1S", displayName: "EQEP1 Strobe input" },
	{ name: "EPG_DATAIN_EQEP2A", displayName: "EQEP2 Signal A" },
	{ name: "EPG_DATAIN_EQEP2B", displayName: "EQEP2 Signal B" },
	{ name: "EPG_DATAIN_EQEP2I", displayName: "EQEP1 Index signal" },
	{ name: "EPG_DATAIN_EQEP2S", displayName: "EQEP1 Strobe input" },
	{ name: "EPG_DATAIN_ECAP1", displayName: "ECAP 1 Input" },
	{ name: "EPG_DATAIN_ECAP2", displayName: "ECAP 2 Input" },
]
let EPG_DataOutSel = [
	{ name: "EPG_DATAOUT_DATAIN", displayName: "Input Data" },
	{ name: "EPG_DATAOUT_EPGOUT", displayName: "EPG output" },
]
let EPG_INT = [
	{ name: "EPG_INT_GLOBAL_INT", displayName: "Global Interrupt Flag" },
	{ name: "EPG_INT_SIGGEN0_DONE", displayName: "Signal Generator 0 Operation Done" },
	{ name: "EPG_INT_SIGGEN0_FILL", displayName: "Signal Generator 0 Data Fill" },
]
let EPG_LOCK_REG = [
	{ name: "EPG_LOCK_REG_GCTL0", displayName: "GCTL0 Register" },
	{ name: "EPG_LOCK_REG_GCTL1", displayName: "GCTL1 Register" },
	{ name: "EPG_LOCK_REG_GCTL2", displayName: "GCTL2 Register" },
	{ name: "EPG_LOCK_REG_GCTL3", displayName: "GCTL3 Register" },
	{ name: "EPG_LOCK_REG_CLKDIV0_CTL0", displayName: "CLK divider 0 CTL0 Register" },
	{ name: "EPG_LOCK_REG_CLKDIV1_CTL0", displayName: "CLK divider 1 CTL0 Register" },
	{ name: "EPG_LOCK_REG_SIGGEN0_CTL0", displayName: "Signal gen 0 CTL0 Register" },
	{ name: "EPG_LOCK_REG_SIGGEN0_CTL1", displayName: "Signal gen 0 CTL1 Register" },
]
let EPG_MX_SEL_LOCK_REG_MXSEL0 = [
	{ name: "EPG_MX_SEL_LOCK_REG_MXSEL0", displayName: "Mux Select 0 Register" },
]
module.exports = {
	EPG_OutputSelect: EPG_OutputSelect,
	EPG_SignalGenOut: EPG_SignalGenOut,
	EPG_ClockGenOut: EPG_ClockGenOut,
	EPG_ClockGenGclkOut: EPG_ClockGenGclkOut,
	EPG_ClockStopEdge: EPG_ClockStopEdge,
	EPG_SignalGenMode: EPG_SignalGenMode,
	EPG_SignalGenData0In: EPG_SignalGenData0In,
	EPG_SignalGenData63In: EPG_SignalGenData63In,
	EPG_OUT: EPG_OUT,
	EPG_SIGGEN: EPG_SIGGEN,
	EPG_CLKGEN: EPG_CLKGEN,
	EPG_DataIn: EPG_DataIn,
	EPG_DataOutSel: EPG_DataOutSel,
	EPG_INT: EPG_INT,
	EPG_LOCK_REG: EPG_LOCK_REG,
	EPG_MX_SEL_LOCK_REG_MXSEL0: EPG_MX_SEL_LOCK_REG_MXSEL0,
}
