//     
// Add Watch window Variables
//
expRemoveAll
expAdd "Dlog.Xwaveform" getQValue(24)
expAdd "Dlog.Ywaveform" getQValue(24)
expAdd "Dlog.Mag" getQValue(24)
expAdd "Dlog.Phase" getQValue(24)
expAdd "Dlog.Exp" getQValue(24)
expAdd "Dlog.Log" getQValue(24)

//
// Open the graphs
// The path may need to be changed based on the install directory
//
openAnalysisView('Dual Time','C:/ti/controlSUITE/libs/math/IQmath/v160/examples/graph_properties/xy_waveform.graphProp')
openAnalysisView('Dual Time','C:/ti/controlSUITE/libs/math/IQmath/v160/examples/graph_properties/exp_log_waveform.graphProp')
openAnalysisView('Dual Time','C:/ti/controlSUITE/libs/math/IQmath/v160/examples/graph_properties/mag_phase_waveform.graphProp')

