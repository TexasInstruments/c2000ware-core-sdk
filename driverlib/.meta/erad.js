let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let config = [
    {
        name: "owner",
        displayName : "Owner",
        description : 'Owner of the ERAD module',
        hidden      : false,
		readOnly    : true,
        default     : "C28x",
        options     : [
            {name: "C28x"},
            {name: "Debugger"}
        ]
    },
    {
        name: "hwbpsUsed",
        displayName : "HWBPs Used",
        description : 'Which HWBPs are used',
        hidden      : false,
        default     : [],
        minSelections: 0,
        options     : [
            {name: "BUSCOMP1"},
            {name: "BUSCOMP2"},
            {name: "BUSCOMP3"},
            {name: "BUSCOMP4"},
            {name: "BUSCOMP5"},
            {name: "BUSCOMP6"},
            {name: "BUSCOMP7"},
            {name: "BUSCOMP8"},
        ]
    },
    {
        name: "ctmsUsed",
        displayName : "CTMs Used",
        description : 'Which CTMs are used',
        hidden      : false,
        default     : [],
        minSelections: 0,
        options     : [
            {name: "COUNTER1"},
            {name: "COUNTER2"},
            {name: "COUNTER3"},
            {name: "COUNTER4"},
        ]
    },
];

if(["F2838x", "F28002x", "F28003x", "F28P65x", "F28P55x", "F28P551x"].includes(system.deviceData.deviceId))
{
    config.push(
        {
            name: "ANDmasksUsed",
            displayName : "AND Masks Used",
            description : 'Which AND Masks are used',
            hidden      : false,
            default     : [],
            minSelections: 0,
            options     : [
                {name: "AND_MASK1"},
                {name: "AND_MASK2"},
                {name: "AND_MASK3"},
                {name: "AND_MASK4"},
            ]
        },
        {
            name: "ORmasksUsed",
            displayName : "OR Masks Used",
            description : 'Which OR Masks are used',
            hidden      : false,
            default     : [],
            minSelections: 0,
            options     : [
                {name: "OR_MASK1"},
                {name: "OR_MASK2"},
                {name: "OR_MASK3"},
                {name: "OR_MASK4"},
            ]
        },
    )
}


function filterHardware(component)
{
    return (Common.typeMatches(component.type, ["ERAD"]));
}


function moduleInstances(inst)
{
    let components = [
    ]

    for (var hwbp_i in inst.hwbpsUsed)
    {
        var hwbp = inst.hwbpsUsed[hwbp_i]
        components.push(
            {
                moduleName: "/driverlib/erad/modules/erad_hwbp.js",
                name: "erad" + hwbp,
                displayName:"ERAD " + hwbp,
                description:"ERAD " + hwbp,
                collapsed: true,
                hidden:  !inst.hwbpsUsed.includes(hwbp)
            }
        )
    }

    for (var ctm_i in inst.ctmsUsed)
    {
        var ctm = inst.ctmsUsed[ctm_i]
        components.push(
            {
                moduleName: "/driverlib/erad/modules/erad_counter.js",
                name: "erad" + ctm,
                displayName:"ERAD " + ctm,
                description:"ERAD " + ctm,
                collapsed: true,
                hidden: !inst.ctmsUsed.includes(ctm)
            }
        )
    }

    for (var and_mask_i in inst.ANDmasksUsed)
    {
        var and_mask = inst.ANDmasksUsed[and_mask_i]
        components.push(
            {
                moduleName: "/driverlib/erad/modules/erad_and_mask.js",
                name: "erad" + and_mask,
                displayName:"ERAD " + and_mask,
                description:"ERAD " + and_mask,
                collapsed: true,
                hidden: !inst.ANDmasksUsed.includes(and_mask)
            }
        )
    }

    for (var or_mask_i in inst.ORmasksUsed)
    {
        var or_mask = inst.ORmasksUsed[or_mask_i]
        components.push(
            {
                moduleName: "/driverlib/erad/modules/erad_or_mask.js",
                name: "erad" + or_mask,
                displayName:"ERAD " + or_mask,
                description:"ERAD " + or_mask,
                collapsed: true,
                hidden: !inst.ORmasksUsed.includes(or_mask)
            }
        )
    }

    return components;
}

var eradModule = {
    peripheralName: "ERAD",
    displayName: "ERAD",
    maxInstances: 1,
    defaultInstanceName: "myERAD",
    description: "Embedded Real-Time Analysis And Diagnostic",
    longDescription: (Common.getCollateralFindabilityList("ERAD")),
    filterHardware : filterHardware,
    config: config,
    templates: {
        boardc : "/driverlib/erad/erad.board.c.xdt",
        boardh : "/driverlib/erad/erad.board.h.xdt"
    },
    moduleInstances     : moduleInstances,
};


exports = eradModule;