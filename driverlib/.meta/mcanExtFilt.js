let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

var MaskWrongSettingVal = false;

function onChangeEFEC(inst, ui){
    if(String(inst.efec).includes("MCAN_EXTFILTEC_RXBUFF")){
        ui.eft.hidden = true;
    }
    else{
        ui.eft.hidden = false;
    }
}

function displayMsgObjConf(inst, ui)
{
   if(inst.extFilts > 0){
      ui.eft.hidden = false;
      ui.efec.hidden = false;
      ui.efid1.hidden = false;
      ui.efid2.hidden = false;
   }
   else {
     ui.eft.hidden = true;
     ui.efec.hidden = true;
     ui.efid1.hidden = true;
     ui.efid2.hidden = true;
   }
}
let config = [
    {
        name        : "eft",
        displayName : "Extended Filter Type",
        description : 'Type of Extended Filter',
        hidden      : false,
        default     : "MCAN_EXTFILT_RANGE",
        options     : [
            { name: "MCAN_EXTFILT_RANGE", displayName: "Range Filter from EFID1 to EFID2"},
            { name: "MCAN_EXTFILT_DUAL", displayName: "Dual ID Filter for EFID1 or EFID2"},
            { name: "MCAN_EXTFILT_CLASSIC", displayName: "Classic Filter: EFID1 = filter, EFID2 = mask"},
            { name: "MCAN_EXTFILT_RANGE_NO_XIDAM", displayName: "Range Filter from EFID1 to EFID2 without XIDAM Mask"},    
        ]
    },
    {
        name        : "efec",
        displayName : "Extended Filter Element Configuration",
        description : 'Determine where received frame will be stored',
        hidden      : false,
        default     : "MCAN_EXTFILTEC_FIFO1",
        options     : [
            { name: "MCAN_EXTFILTEC_DISABLE", displayName: "Filter Element Disabled"},
            { name: "MCAN_EXTFILTEC_FIFO0", displayName: "Store in RX FIFO 0 if filter matches"},
            { name: "MCAN_EXTFILTEC_FIFO1", displayName: "Store in RX FIFO 1 if filter matches"},
            { name: "MCAN_EXTFILTEC_REJECT", displayName: "Reject ID if filter matches"},
            { name: "MCAN_EXTFILTEC_PRI", displayName: "Set priority if filter matches"},
            { name: "MCAN_EXTFILTEC_PRI_FIFO0", displayName: "Set priority and store in RX FIFO 0 if filter matches"},
            { name: "MCAN_EXTFILTEC_PRI_FIFO1", displayName: "Set priority and store in RX FIFO 1 if filter matches"},
            { name: "MCAN_EXTFILTEC_RXBUFF", displayName: "Store in RX Buffer"},
        ],
        onChange    : onChangeEFEC,
    },
    {
        name        : "efid1",
        displayName : "Extended Filter ID 1",
        description : "Extended Filter ID 1",
        hidden      : false,
        default     : 0
    },
    {
        name        : "efid2",
        displayName : "Extended Filter ID 2",
        description : "Extended Filter ID 2",
        hidden      : false,
        default     : 0
    },
]

function onValidate(inst, validation){

}

var extFiltElem = {
    displayName: "extFiltElem",
    maxInstances: 128,
    defaultInstanceName : "extFilt",
    description : "Extended Filter Element",
    config : config,
    validate : onValidate,
};

exports = extFiltElem;
