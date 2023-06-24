let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

var MaskWrongSettingVal = false;

function onChangeSFEC(inst, ui){
    if(String(inst.sfec).includes("MCAN_STDFILTEC_RXBUFF")){
        ui.sft.hidden = true;
    }
    else{
        ui.sft.hidden = false;
    }
}

function displayMsgObjConf(inst, ui)
{
   if(inst.stdFilts > 0){
      ui.sft.hidden = false;
      ui.sfec.hidden = false;
      ui.sfid1.hidden = false;
      ui.sfid2.hidden = false;
   }
   else {
     ui.sft.hidden = true;
     ui.sfec.hidden = true;
     ui.sfid1.hidden = true;
     ui.sfid2.hidden = true;
   }
}
let config = [
    {
        name        : "sft",
        displayName : "Standard Filter Type",
        description : 'Type of Standard Filter',
        hidden      : false,
        default     : "MCAN_STDFILT_RANGE",
        options     : [
            { name: "MCAN_STDFILT_RANGE", displayName: "Range Filter from SFID1 to SFID2"},
            { name: "MCAN_STDFILT_DUAL", displayName: "Dual ID Filter for SFID1 or SFID2"},
            { name: "MCAN_STDFILT_CLASSIC", displayName: "Classic Filter: SFID1 = filter, SFID2 = mask"},
            { name: "MCAN_STDFILT_DISABLED", displayName: "Filter Element Disabled"},    
        ]
    },
    {
        name        : "sfec",
        displayName : "Standard Filter Element Configuration",
        description : 'Determine where received frame will be stored',
        hidden      : false,
        default     : "MCAN_STDFILTEC_FIFO1",
        options     : [
            { name: "MCAN_STDFILTEC_DISABLE", displayName: "Filter Element Disabled"},
            { name: "MCAN_STDFILTEC_FIFO0", displayName: "Store in RX FIFO 0 if filter matches"},
            { name: "MCAN_STDFILTEC_FIFO1", displayName: "Store in RX FIFO 1 if filter matches"},
            { name: "MCAN_STDFILTEC_REJECT", displayName: "Reject ID if filter matches"},
            { name: "MCAN_STDFILTEC_PRI", displayName: "Set priority if filter matches"},
            { name: "MCAN_STDFILTEC_PRI_FIFO0", displayName: "Set priority and store in RX FIFO 0 if filter matches"},
            { name: "MCAN_STDFILTEC_PRI_FIFO1", displayName: "Set priority and store in RX FIFO 1 if filter matches"},
            { name: "MCAN_STDFILTEC_RXBUFF", displayName: "Store in RX Buffer"},
        ],
        onChange    : onChangeSFEC,
    },
    {
        name        : "sfid1",
        displayName : "Standard Filter ID 1",
        description : "Standard Filter ID 1",
        hidden      : false,
        default     : 0
    },
    {
        name        : "sfid2",
        displayName : "Standard Filter ID 2",
        description : "Standard Filter ID 2",
        hidden      : false,
        default     : 0
    },
]

function onValidate(inst, validation){

}

var stdFiltElem = {
    displayName: "stdFiltElem",
    maxInstances: 128,
    defaultInstanceName : "stdFilt",
    description : "Standard Filter Element",
    config : config,
    validate : onValidate,
};

exports = stdFiltElem;
