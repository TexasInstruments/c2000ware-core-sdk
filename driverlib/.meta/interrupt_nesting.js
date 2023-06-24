let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_interrupt.js");

/* Intro splash on GUI */
let longDescription = "For more details about interrupt nesting, please refer to https://software-dl.ti.com/C2000/docs/c28x_interrupt_nesting/html/index.html";
longDescription += "\n\nNote that the ISR functions need to be updated to enable nesting. Please use the template ISR functions available in sw_prioritized_defaultisr.c as reference"


/* Array of CAN configurables that are common across device families */
var Priorities = []
var GlobalPriorities = []
var GroupPriorities = []

// List of all priority levels. Used for dropdown
for (var i = 0; i <= 16; i++)
{
    Priorities.push({name:i})
}


// Function returns all interrupts within specified PIE group
function getInterruptsInGroup(group)
{
    var ints = []
    for (var int of device_driverlib_peripheral.interrupts)
    {
        if(int.int_group_number == group.toString())
            ints.push(int)
    }
    return ints
}

function getInterrupt(group, channel)
{
    for (var int of device_driverlib_peripheral.interrupts)
    {
        if((int.int_group_number == group.toString()) && (int.int_channel_number == channel.toString()))
            return int
    }
    return undefined
}

function getInterruptChannel(intName)
{
}

for (var i = 1; i <= 16; i++)
{
    var display_name = ""
    switch(i)
    {
        case 13 :
            display_name = "Global Priority for INT13 (Timer 1 Interrupt)"
            break;
        case 14 :
            display_name = "Global Priority for INT14 (Timer 2 Interrupt)"
            break;
        case 15 :
            display_name = "Global Priority for DATALOG"
            break;
        case 16 :
            display_name = "Global Priority for RTOSINT"
            break;
        default :
            display_name = "Global Priority for Group " + i.toString() + " interrupts"
            break;
    }

    GlobalPriorities.push(
        {
            name       : "IntPri_Global_" + i.toString(),
            displayName: display_name,
            options    : Priorities,
            default    : 0,
        }
    )
}


for (var i = 1; i <= 12; i++)
{
    var groupInterrupts = []

    for (var int of getInterruptsInGroup(i))
    {
        groupInterrupts.push({
            name       : "IntPri_Group_" + int.int_define_name,
            displayName: int.int_description + " (PIE Channel " + int.int_group_channel_number + ")",
            description: int.int_define_name,
            options    : Priorities,
            default    : 0,
        })
    }

    GroupPriorities.push(
        {
            name       : "GroupPriorities_" + i.toString(),
            displayName: "Group Priority for Group " + i.toString() + " interrupts",
            config     : groupInterrupts
        }
    )
}

let staticConfig = [
    {
        name           : "GlobalPriorities",
        displayName    : "Global Priorities",
        config         : GlobalPriorities,
        longDescription: `Set "Global" Interrupt Priority Level (IER register):

The user must set the appropriate priority level for each of the CPU
interrupts. This is termed as the "global" priority. The priority level
must be a number between 1 (highest) to 16 (lowest). A value of 0 must
be entered for reserved interrupts or interrupts that are not used.

Note: The priority levels below are used to calculate the IER register
        interrupt masks MINT1 to MINT16.

Priority Levels:

    0  = not used
    1  = highest priority
    ...
    16 = lowest priority`,
    },

    {
        name           : "GroupPriorities",
        displayName    : "Group Priorities",
        config         : GroupPriorities,
        longDescription: `Set "Group" Interrupt Priority Level (PIEIER1 to PIEIER12 registers):

The user must set the appropriate priority level for each of the PIE
interrupts. This is termed as the "group" priority. The priority level
must be a number between 1 (highest) to 16 (lowest). A value of 0 must
be entered for reserved interrupts or interrupts that are not used.

Note: The priority levels below are used to calculate the following
        PIEIER register interrupt masks:

        MG1_1 to MG1_16
        MG2_1 to MG2_16
        MG3_1 to MG3_16
        MG4_1 to MG4_16
        MG5_1 to MG5_16
        MG6_1 to MG6_16
        MG7_1 to MG7_16
        MG8_1 to MG8_16
        MG9_1 to MG9_16
        MG10_1 to MG10_16
        MG11_1 to MG11_16
        MG12_1 to MG12_16

Priority Levels:

        0  = not used
        1  = highest priority
        ...
        16  = lowest priority`,
    },

    {
        name : "traceBuffer",
        displayName : "Trace ISR Buffer",
        config : [
            {
                name       : "traceEnable",
                displayName: "Enable Trace ISR buffer (for Debugging)",
                default    : true
            },
            {
                name       : "traceLength",
                displayName: "Length of the trace ISR buffer",
                default    : 50
            }
        ]
    },
];


function onValidate(inst, validation) {

    // If global priority is 0 and the group priority is non zero, throw an error
    for (var i = 1; i <= 12; i++)
    {
        var globalPri = inst["IntPri_Global_" + i.toString()]
        if(globalPri == 0)
        {
            for (var int of getInterruptsInGroup(i))
            {
                var groupPri  = inst["IntPri_Group_" + int.int_define_name]
                if(groupPri > 0)
                    validation.logError("Global priority is not set for this group", inst, "IntPri_Group_" + int.int_define_name);
            }
        }

    }
}


var intNestModule = {
    displayName        : "Software Prioritized Interrupt Nesting",
    defaultInstanceName: "myInterruptNesting",
    longDescription    : longDescription,
    moduleStatic       : {
        config: staticConfig,
        validate: onValidate,
    },
    templates: {
        "/driverlib/interrupt_nesting/sw_prioritized_defaultisr.c.xdt" : "",
        "/driverlib/interrupt_nesting/sw_prioritized_isr_levels.h.xdt" : ""
    },
    functions : {
        getInterruptsInGroup : getInterruptsInGroup,
        getInterrupt : getInterrupt
    }
};

exports = intNestModule;