let FSI_DataWidth = [
	{ name: "FSI_DATA_WIDTH_1_LANE", displayName: "DATA WIDTH 1 LANE" },
	{ name: "FSI_DATA_WIDTH_2_LANE", displayName: "DATA WIDTH 2 LANE" },
]
let FSI_TxSubmoduleInReset = [
	{ name: "FSI_TX_MAIN_CORE_RESET", displayName: "TX MAIN CORE RESET", legacyNames: ["FSI_TX_MASTER_CORE_RESET"]},
	{ name: "FSI_TX_CLOCK_RESET", displayName: "TX CLOCK RESET" },
	{ name: "FSI_TX_PING_TIMEOUT_CNT_RESET", displayName: "TX PING TIMEOUT CNT RESET" },
]
let FSI_TxStartMode = [
	{ name: "FSI_TX_START_FRAME_CTRL", displayName: "TX START FRAME CTRL" },
	{ name: "FSI_TX_START_EXT_TRIG", displayName: "TX START EXT TRIG" },
	{ name: "FSI_TX_START_FRAME_CTRL_OR_UDATA_TAG", displayName: "TX START FRAME CTRL OR UDATA TAG" },
]
let FSI_FrameType = [
	{ name: "FSI_FRAME_TYPE_PING", displayName: "FRAME TYPE PING" },
	{ name: "FSI_FRAME_TYPE_ERROR", displayName: "FRAME TYPE ERROR" },
	{ name: "FSI_FRAME_TYPE_1WORD_DATA", displayName: "FRAME TYPE 1WORD DATA" },
	{ name: "FSI_FRAME_TYPE_2WORD_DATA", displayName: "FRAME TYPE 2WORD DATA" },
	{ name: "FSI_FRAME_TYPE_4WORD_DATA", displayName: "FRAME TYPE 4WORD DATA" },
	{ name: "FSI_FRAME_TYPE_6WORD_DATA", displayName: "FRAME TYPE 6WORD DATA" },
	{ name: "FSI_FRAME_TYPE_NWORD_DATA", displayName: "FRAME TYPE NWORD DATA" },
]
let FSI_FrameTag = [
	{ name: "FSI_FRAME_TAG0", displayName: "FRAME TAG0" },
	{ name: "FSI_FRAME_TAG1", displayName: "FRAME TAG1" },
	{ name: "FSI_FRAME_TAG2", displayName: "FRAME TAG2" },
	{ name: "FSI_FRAME_TAG3", displayName: "FRAME TAG3" },
	{ name: "FSI_FRAME_TAG4", displayName: "FRAME TAG4" },
	{ name: "FSI_FRAME_TAG5", displayName: "FRAME TAG5" },
	{ name: "FSI_FRAME_TAG6", displayName: "FRAME TAG6" },
	{ name: "FSI_FRAME_TAG7", displayName: "FRAME TAG7" },
	{ name: "FSI_FRAME_TAG8", displayName: "FRAME TAG8" },
	{ name: "FSI_FRAME_TAG9", displayName: "FRAME TAG9" },
	{ name: "FSI_FRAME_TAG10", displayName: "FRAME TAG10" },
	{ name: "FSI_FRAME_TAG11", displayName: "FRAME TAG11" },
	{ name: "FSI_FRAME_TAG12", displayName: "FRAME TAG12" },
	{ name: "FSI_FRAME_TAG13", displayName: "FRAME TAG13" },
	{ name: "FSI_FRAME_TAG14", displayName: "FRAME TAG14" },
	{ name: "FSI_FRAME_TAG15", displayName: "FRAME TAG15" },
]
let FSI_PingTimeoutMode = [
	{ name: "FSI_PINGTIMEOUT_ON_HWINIT_PING_FRAME", displayName: "PINGTIMEOUT ON HWINIT PING FRAME" },
	{ name: "FSI_PINGTIMEOUT_ON_HWSWINIT_PING_FRAME", displayName: "PINGTIMEOUT ON HWSWINIT PING FRAME" },
]
let FSI_ECCComputeWidth = [
	{ name: "FSI_32BIT_ECC_COMPUTE", displayName: "32BIT ECC COMPUTE" },
	{ name: "FSI_16BIT_ECC_COMPUTE", displayName: "16BIT ECC COMPUTE" },
]
let FSI_InterruptNum = [
	{ name: "FSI_INT1", displayName: "INT1" },
	{ name: "FSI_INT2", displayName: "INT2" },
]
let FSI_RxSubmoduleInReset = [
	{ name: "FSI_RX_MAIN_CORE_RESET", displayName: "RX MAIN CORE RESET", legacyNames: ["FSI_RX_MASTER_CORE_RESET"]},
	{ name: "FSI_RX_FRAME_WD_CNT_RESET", displayName: "RX FRAME WD CNT RESET" },
	{ name: "FSI_RX_PING_WD_CNT_RESET", displayName: "RX PING WD CNT RESET" },
]
let FSI_RxDelayTapType = [
	{ name: "FSI_RX_DELAY_CLK", displayName: "RX DELAY CLK" },
	{ name: "FSI_RX_DELAY_D0", displayName: "RX DELAY D0" },
	{ name: "FSI_RX_DELAY_D1", displayName: "RX DELAY D1" },
]
let FSI_ExtFrameTriggerSrc = [
	{ name: "FSI_EXT_TRIGSRC_EPWM_XBARTRIP4", displayName: "EXT TRIGSRC EPWM XBARTRIP4" },
	{ name: "FSI_EXT_TRIGSRC_EPWM_XBARTRIP5", displayName: "EXT TRIGSRC EPWM XBARTRIP5" },
	{ name: "FSI_EXT_TRIGSRC_EPWM_XBARTRIP7", displayName: "EXT TRIGSRC EPWM XBARTRIP7" },
	{ name: "FSI_EXT_TRIGSRC_EPWM_XBARTRIP8", displayName: "EXT TRIGSRC EPWM XBARTRIP8" },
	{ name: "FSI_EXT_TRIGSRC_EPWM_XBARTRIP9", displayName: "EXT TRIGSRC EPWM XBARTRIP9" },
	{ name: "FSI_EXT_TRIGSRC_EPWM_XBARTRIP10", displayName: "EXT TRIGSRC EPWM XBARTRIP10" },
	{ name: "FSI_EXT_TRIGSRC_EPWM_XBARTRIP11", displayName: "EXT TRIGSRC EPWM XBARTRIP11" },
	{ name: "FSI_EXT_TRIGSRC_EPWM_XBARTRIP12", displayName: "EXT TRIGSRC EPWM XBARTRIP12" },
	{ name: "FSI_EXT_TRIGSRC_EPWM1_SOCA", displayName: "EXT TRIGSRC EPWM1 SOCA" },
	{ name: "FSI_EXT_TRIGSRC_EPWM1_SOCB", displayName: "EXT TRIGSRC EPWM1 SOCB" },
	{ name: "FSI_EXT_TRIGSRC_EPWM2_SOCA", displayName: "EXT TRIGSRC EPWM2 SOCA" },
	{ name: "FSI_EXT_TRIGSRC_EPWM2_SOCB", displayName: "EXT TRIGSRC EPWM2 SOCB" },
	{ name: "FSI_EXT_TRIGSRC_EPWM3_SOCA", displayName: "EXT TRIGSRC EPWM3 SOCA" },
	{ name: "FSI_EXT_TRIGSRC_EPWM3_SOCB", displayName: "EXT TRIGSRC EPWM3 SOCB" },
	{ name: "FSI_EXT_TRIGSRC_EPWM4_SOCA", displayName: "EXT TRIGSRC EPWM4 SOCA" },
	{ name: "FSI_EXT_TRIGSRC_EPWM4_SOCB", displayName: "EXT TRIGSRC EPWM4 SOCB" },
	{ name: "FSI_EXT_TRIGSRC_EPWM5_SOCA", displayName: "EXT TRIGSRC EPWM5 SOCA" },
	{ name: "FSI_EXT_TRIGSRC_EPWM5_SOCB", displayName: "EXT TRIGSRC EPWM5 SOCB" },
	{ name: "FSI_EXT_TRIGSRC_EPWM6_SOCA", displayName: "EXT TRIGSRC EPWM6 SOCA" },
	{ name: "FSI_EXT_TRIGSRC_EPWM6_SOCB", displayName: "EXT TRIGSRC EPWM6 SOCB" },
	{ name: "FSI_EXT_TRIGSRC_EPWM7_SOCA", displayName: "EXT TRIGSRC EPWM7 SOCA" },
	{ name: "FSI_EXT_TRIGSRC_EPWM7_SOCB", displayName: "EXT TRIGSRC EPWM7 SOCB" },
	{ name: "FSI_EXT_TRIGSRC_EPWM8_SOCA", displayName: "EXT TRIGSRC EPWM8 SOCA" },
	{ name: "FSI_EXT_TRIGSRC_EPWM8_SOCB", displayName: "EXT TRIGSRC EPWM8 SOCB" },
	{ name: "FSI_EXT_TRIGSRC_EPWM9_SOCA", displayName: "EXT TRIGSRC EPWM9 SOCA" },
	{ name: "FSI_EXT_TRIGSRC_EPWM9_SOCB", displayName: "EXT TRIGSRC EPWM9 SOCB" },
	{ name: "FSI_EXT_TRIGSRC_EPWM10_SOCA", displayName: "EXT TRIGSRC EPWM10 SOCA" },
	{ name: "FSI_EXT_TRIGSRC_EPWM10_SOCB", displayName: "EXT TRIGSRC EPWM10 SOCB" },
	{ name: "FSI_EXT_TRIGSRC_EPWM11_SOCA", displayName: "EXT TRIGSRC EPWM11 SOCA" },
	{ name: "FSI_EXT_TRIGSRC_EPWM11_SOCB", displayName: "EXT TRIGSRC EPWM11 SOCB" },
	{ name: "FSI_EXT_TRIGSRC_EPWM12_SOCA", displayName: "EXT TRIGSRC EPWM12 SOCA" },
	{ name: "FSI_EXT_TRIGSRC_EPWM12_SOCB", displayName: "EXT TRIGSRC EPWM12 SOCB" },
	{ name: "FSI_EXT_TRIGSRC_EPWM13_SOCA", displayName: "EXT TRIGSRC EPWM13 SOCA" },
	{ name: "FSI_EXT_TRIGSRC_EPWM13_SOCB", displayName: "EXT TRIGSRC EPWM13 SOCB" },
	{ name: "FSI_EXT_TRIGSRC_EPWM14_SOCA", displayName: "EXT TRIGSRC EPWM14 SOCA" },
	{ name: "FSI_EXT_TRIGSRC_EPWM14_SOCB", displayName: "EXT TRIGSRC EPWM14 SOCB" },
	{ name: "FSI_EXT_TRIGSRC_EPWM15_SOCA", displayName: "EXT TRIGSRC EPWM15 SOCA" },
	{ name: "FSI_EXT_TRIGSRC_EPWM15_SOCB", displayName: "EXT TRIGSRC EPWM15 SOCB" },
	{ name: "FSI_EXT_TRIGSRC_EPWM16_SOCA", displayName: "EXT TRIGSRC EPWM16 SOCA" },
	{ name: "FSI_EXT_TRIGSRC_EPWM16_SOCB", displayName: "EXT TRIGSRC EPWM16 SOCB" },
	{ name: "FSI_EXT_TRIGSRC_CLB1_CLBOUT30", displayName: "EXT TRIGSRC CLB1 CLBOUT30" },
	{ name: "FSI_EXT_TRIGSRC_CLB1_CLBOUT31", displayName: "EXT TRIGSRC CLB1 CLBOUT31" },
	{ name: "FSI_EXT_TRIGSRC_CLB2_CLBOUT30", displayName: "EXT TRIGSRC CLB2 CLBOUT30" },
	{ name: "FSI_EXT_TRIGSRC_CLB2_CLBOUT31", displayName: "EXT TRIGSRC CLB2 CLBOUT31" },
	{ name: "FSI_EXT_TRIGSRC_CLB3_CLBOUT30", displayName: "EXT TRIGSRC CLB3 CLBOUT30" },
	{ name: "FSI_EXT_TRIGSRC_CLB3_CLBOUT31", displayName: "EXT TRIGSRC CLB3 CLBOUT31" },
	{ name: "FSI_EXT_TRIGSRC_CLB4_CLBOUT30", displayName: "EXT TRIGSRC CLB4 CLBOUT30" },
	{ name: "FSI_EXT_TRIGSRC_CLB4_CLBOUT31", displayName: "EXT TRIGSRC CLB4 CLBOUT31" },
	{ name: "FSI_EXT_TRIGSRC_CLB5_CLBOUT30", displayName: "EXT TRIGSRC CLB5 CLBOUT30" },
	{ name: "FSI_EXT_TRIGSRC_CLB5_CLBOUT31", displayName: "EXT TRIGSRC CLB5 CLBOUT31" },
	{ name: "FSI_EXT_TRIGSRC_CLB6_CLBOUT30", displayName: "EXT TRIGSRC CLB6 CLBOUT30" },
	{ name: "FSI_EXT_TRIGSRC_CLB6_CLBOUT31", displayName: "EXT TRIGSRC CLB6 CLBOUT31" },
	{ name: "FSI_EXT_TRIGSRC_ADC_SOCA", displayName: "EXT TRIGSRC ADC SOCA" },
	{ name: "FSI_EXT_TRIGSRC_ADC_SOCB", displayName: "EXT TRIGSRC ADC SOCB" },
	{ name: "FSI_EXT_TRIGSRC_CPU1_TIMER0INT", displayName: "EXT TRIGSRC CPU1 TIMER0INT" },
	{ name: "FSI_EXT_TRIGSRC_CPU1_TIMER1INT", displayName: "EXT TRIGSRC CPU1 TIMER1INT" },
	{ name: "FSI_EXT_TRIGSRC_CPU1_TIMER2INT", displayName: "EXT TRIGSRC CPU1 TIMER2INT" },
	{ name: "FSI_EXT_TRIGSRC_CPU2_TIMER0INT", displayName: "EXT TRIGSRC CPU2 TIMER0INT" },
	{ name: "FSI_EXT_TRIGSRC_CPU2_TIMER1INT", displayName: "EXT TRIGSRC CPU2 TIMER1INT" },
	{ name: "FSI_EXT_TRIGSRC_CPU2_TIMER2INT", displayName: "EXT TRIGSRC CPU2 TIMER2INT" },
	{ name: "FSI_EXT_TRIGSRC_CPU1_CLATASKRUN1", displayName: "EXT TRIGSRC CPU1 CLATASKRUN1" },
	{ name: "FSI_EXT_TRIGSRC_CPU1_CLATASKRUN2", displayName: "EXT TRIGSRC CPU1 CLATASKRUN2" },
	{ name: "FSI_EXT_TRIGSRC_CPU1_CLATASKRUN3", displayName: "EXT TRIGSRC CPU1 CLATASKRUN3" },
	{ name: "FSI_EXT_TRIGSRC_CPU1_CLATASKRUN4", displayName: "EXT TRIGSRC CPU1 CLATASKRUN4" },
	{ name: "FSI_EXT_TRIGSRC_CPU2_CLATASKRUN5", displayName: "EXT TRIGSRC CPU2 CLATASKRUN5" },
	{ name: "FSI_EXT_TRIGSRC_CPU2_CLATASKRUN6", displayName: "EXT TRIGSRC CPU2 CLATASKRUN6" },
	{ name: "FSI_EXT_TRIGSRC_CPU2_CLATASKRUN7", displayName: "EXT TRIGSRC CPU2 CLATASKRUN7" },
	{ name: "FSI_EXT_TRIGSRC_CPU2_CLATASKRUN8", displayName: "EXT TRIGSRC CPU2 CLATASKRUN8" },
	{ name: "FSI_EXT_TRIGSRC_CPU1_DMACH1", displayName: "EXT TRIGSRC CPU1 DMACH1" },
	{ name: "FSI_EXT_TRIGSRC_CPU1_DMACH2", displayName: "EXT TRIGSRC CPU1 DMACH2" },
	{ name: "FSI_EXT_TRIGSRC_CPU1_DMACH3", displayName: "EXT TRIGSRC CPU1 DMACH3" },
	{ name: "FSI_EXT_TRIGSRC_CPU1_DMACH4", displayName: "EXT TRIGSRC CPU1 DMACH4" },
	{ name: "FSI_EXT_TRIGSRC_CPU1_DMACH5", displayName: "EXT TRIGSRC CPU1 DMACH5" },
	{ name: "FSI_EXT_TRIGSRC_CPU1_DMACH6", displayName: "EXT TRIGSRC CPU1 DMACH6" },
	{ name: "FSI_EXT_TRIGSRC_CPU2_DMACH1", displayName: "EXT TRIGSRC CPU2 DMACH1" },
	{ name: "FSI_EXT_TRIGSRC_CPU2_DMACH2", displayName: "EXT TRIGSRC CPU2 DMACH2" },
	{ name: "FSI_EXT_TRIGSRC_CPU2_DMACH3", displayName: "EXT TRIGSRC CPU2 DMACH3" },
	{ name: "FSI_EXT_TRIGSRC_CPU2_DMACH4", displayName: "EXT TRIGSRC CPU2 DMACH4" },
	{ name: "FSI_EXT_TRIGSRC_CPU2_DMACH5", displayName: "EXT TRIGSRC CPU2 DMACH5" },
	{ name: "FSI_EXT_TRIGSRC_CPU2_DMACH6", displayName: "EXT TRIGSRC CPU2 DMACH6" },
	{ name: "FSI_EXT_TRIGSRC_FSIABRX_TRIG0", displayName: "EXT TRIGSRC FSIABRX TRIG0" },
	{ name: "FSI_EXT_TRIGSRC_FSIABRX_TRIG1", displayName: "EXT TRIGSRC FSIABRX TRIG1" },
	{ name: "FSI_EXT_TRIGSRC_FSIABRX_TRIG2", displayName: "EXT TRIGSRC FSIABRX TRIG2" },
	{ name: "FSI_EXT_TRIGSRC_FSIABRX_TRIG3", displayName: "EXT TRIGSRC FSIABRX TRIG3" },
	{ name: "FSI_EXT_TRIGSRC_FSICDRX_TRIG0", displayName: "EXT TRIGSRC FSICDRX TRIG0" },
	{ name: "FSI_EXT_TRIGSRC_FSICDRX_TRIG1", displayName: "EXT TRIGSRC FSICDRX TRIG1" },
	{ name: "FSI_EXT_TRIGSRC_FSICDRX_TRIG2", displayName: "EXT TRIGSRC FSICDRX TRIG2" },
	{ name: "FSI_EXT_TRIGSRC_FSICDRX_TRIG3", displayName: "EXT TRIGSRC FSICDRX TRIG3" },
	{ name: "FSI_EXT_TRIGSRC_EPWM17_SOCA", displayName: "EXT TRIGSRC EPWM17 SOCA" },
	{ name: "FSI_EXT_TRIGSRC_EPWM17_SOCB", displayName: "EXT TRIGSRC EPWM17 SOCB" },
	{ name: "FSI_EXT_TRIGSRC_EPWM18_SOCA", displayName: "EXT TRIGSRC EPWM18 SOCA" },
	{ name: "FSI_EXT_TRIGSRC_EPWM18_SOCB", displayName: "EXT TRIGSRC EPWM18 SOCB" },
]
let FSI_TX_EVT = [
	{ name: "FSI_TX_EVT_FRAME_DONE", displayName: "Frame transmission done" },
	{ name: "FSI_TX_EVT_BUF_UNDERRUN", displayName: "Transmit buffer is underrun" },
	{ name: "FSI_TX_EVT_BUF_OVERRUN", displayName: "Transmit buffer is overrun" },
	{ name: "FSI_TX_EVT_PING_TIMEOUT", displayName: "Ping Timer event" },
]
let FSI_TX_EVT_PING_HW_TRIG = [
	{ name: "FSI_TX_EVT_PING_HW_TRIG", displayName: "TX EVT PING HW TRIG" },
]
let FSI_TX_EVTMASK = [
	{ name: "FSI_TX_EVTMASK", displayName: "TX EVTMASK" },
]
let FSI_TX_MAX_NUM_EXT_TRIGGERS = [
	{ name: "FSI_TX_MAX_NUM_EXT_TRIGGERS", displayName: "TX MAX NUM EXT TRIGGERS" },
]
let FSI_TX_INT2_CTRL_S = [
	{ name: "FSI_TX_INT2_CTRL_S", displayName: "TX INT2 CTRL S" },
]
let FSI_RX_EVT = [
	{ name: "FSI_RX_EVT_PING_WD_TIMEOUT", displayName: "Ping Watchdog times out" },
	{ name: "FSI_RX_EVT_FRAME_WD_TIMEOUT", displayName: "Frame Watchdog times out" },
	{ name: "FSI_RX_EVT_CRC_ERR", displayName: "Hardware computed CRC error" },
	{ name: "FSI_RX_EVT_TYPE_ERR", displayName: "Invalid Frame type detected" },
	{ name: "FSI_RX_EVT_EOF_ERR", displayName: "Invalid EndofFrame bit-pattern" },
	{ name: "FSI_RX_EVT_OVERRUN", displayName: "Buffer Overrun in Rx buffer" },
	{ name: "FSI_RX_EVT_FRAME_DONE", displayName: "Received frame without errors" },
	{ name: "FSI_RX_EVT_UNDERRUN", displayName: "Software reads empty Rx buffer" },
	{ name: "FSI_RX_EVT_ERR_FRAME", displayName: "Received error frame" },
	{ name: "FSI_RX_EVT_PING_FRAME", displayName: "Received ping frame" },
	{ name: "FSI_RX_EVT_FRAME_OVERRUN", displayName: "FRAME_DONE not cleared on receiving new frame" },
	{ name: "FSI_RX_EVT_DATA_FRAME", displayName: "Received data frame" },
	{ name: "FSI_RX_EVT_PING_FRAME_TAG_MATCH", displayName: "Recieved ping frame with matched tag" },
	{ name: "FSI_RX_EVT_DATA_FRAME_TAG_MATCH", displayName: "Recieved data frame with matched tag" },
	{ name: "FSI_RX_EVT_ERR_FRAME_TAG_MATCH", displayName: "Recieved error frame with tag match" },
]
let FSI_RX_EVTMASK = [
	{ name: "FSI_RX_EVTMASK", displayName: "RX EVTMASK" },
]
let FSI_RX_MAX_DELAY_LINE_VAL = [
	{ name: "FSI_RX_MAX_DELAY_LINE_VAL", displayName: "RX MAX DELAY LINE VAL" },
]
let FSI_MAX_LEN_NWORDS_DATA = [
	{ name: "FSI_MAX_LEN_NWORDS_DATA", displayName: "MAX LEN NWORDS DATA" },
]
let FSI_MAX_VALUE_USERDATA = [
	{ name: "FSI_MAX_VALUE_USERDATA", displayName: "MAX VALUE USERDATA" },
]
let FSI_MAX_VALUE_BUF_PTR_OFF = [
	{ name: "FSI_MAX_VALUE_BUF_PTR_OFF", displayName: "MAX VALUE BUF PTR OFF" },
]
let FSI_CTRL_REG_KEY = [
	{ name: "FSI_CTRL_REG_KEY", displayName: "CTRL REG KEY" },
]
module.exports = {
	FSI_DataWidth: FSI_DataWidth,
	FSI_TxSubmoduleInReset: FSI_TxSubmoduleInReset,
	FSI_TxStartMode: FSI_TxStartMode,
	FSI_FrameType: FSI_FrameType,
	FSI_FrameTag: FSI_FrameTag,
	FSI_PingTimeoutMode: FSI_PingTimeoutMode,
	FSI_ECCComputeWidth: FSI_ECCComputeWidth,
	FSI_InterruptNum: FSI_InterruptNum,
	FSI_RxSubmoduleInReset: FSI_RxSubmoduleInReset,
	FSI_RxDelayTapType: FSI_RxDelayTapType,
	FSI_ExtFrameTriggerSrc: FSI_ExtFrameTriggerSrc,
	FSI_TX_EVT: FSI_TX_EVT,
	FSI_TX_EVT_PING_HW_TRIG: FSI_TX_EVT_PING_HW_TRIG,
	FSI_TX_EVTMASK: FSI_TX_EVTMASK,
	FSI_TX_MAX_NUM_EXT_TRIGGERS: FSI_TX_MAX_NUM_EXT_TRIGGERS,
	FSI_TX_INT2_CTRL_S: FSI_TX_INT2_CTRL_S,
	FSI_RX_EVT: FSI_RX_EVT,
	FSI_RX_EVTMASK: FSI_RX_EVTMASK,
	FSI_RX_MAX_DELAY_LINE_VAL: FSI_RX_MAX_DELAY_LINE_VAL,
	FSI_MAX_LEN_NWORDS_DATA: FSI_MAX_LEN_NWORDS_DATA,
	FSI_MAX_VALUE_USERDATA: FSI_MAX_VALUE_USERDATA,
	FSI_MAX_VALUE_BUF_PTR_OFF: FSI_MAX_VALUE_BUF_PTR_OFF,
	FSI_CTRL_REG_KEY: FSI_CTRL_REG_KEY,
}
