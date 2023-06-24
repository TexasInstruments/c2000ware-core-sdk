let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_epwm.js");
var shadowRegisterReloadNumberofTimesOptions = [
    { name : "1", displayName: "One Period"},
    { name : "2", displayName: "Two Periods" },
    { name : "3", displayName: "Three Periods"},
    { name : "4", displayName: "Four Periods"},
    { name : "5", displayName: "Five Periods"},
    { name : "6", displayName: "Six Periods"},
    { name : "7", displayName: "Seven Periods"},
    { name : "8", displayName: "Eight Periods"}
]
function generateActiveRegistersConfig(reg_name)
{
    let xcmp_RegArr = device_driverlib_peripheral.EPWM_XCMPReg.slice(0, 8);
    let xcmp_RegConfig = [];

    for(var xcmp_Reg_Index in xcmp_RegArr)
    {
        xcmp_RegConfig = xcmp_RegConfig.concat(
            {
                name: "epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_Reg_Index].name.replace("EPWM_", ""),
                displayName: xcmp_RegArr[xcmp_Reg_Index].displayName.replace("_ACTIVE", " Active "),
                description: "Set Active Register to a value",
                hidden: true,
                default: 0,
            }
        )
    }
    return xcmp_RegConfig
}
function generateShadowRegisters1Config(reg_name)
{
    let xcmp_RegArr = device_driverlib_peripheral.EPWM_XCMPReg.slice(9, 17);
    let xcmp_RegConfig = [];
    
    for(var xcmp_Reg_Index in xcmp_RegArr)
    {
        xcmp_RegConfig = xcmp_RegConfig.concat(
            {
                name: "epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_Reg_Index].name.replace("EPWM_", ""),
                displayName: xcmp_RegArr[xcmp_Reg_Index].displayName.replace("_SHADOW", " Shadow "),
                description: "Set Active Register to a value",
                hidden: true,
                default: 0,
            }
        )
    }
    return xcmp_RegConfig
}
function generateShadowRegisters2Config(reg_name)
{
    let xcmp_RegArr = device_driverlib_peripheral.EPWM_XCMPReg.slice(18, 26);
    let xcmp_RegConfig = [];
    
    for(var xcmp_Reg_Index in xcmp_RegArr)
    {
        xcmp_RegConfig = xcmp_RegConfig.concat(
            {
                name: "epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_Reg_Index].name.replace("EPWM_", ""),
                displayName: xcmp_RegArr[xcmp_Reg_Index].displayName.replace("_SHADOW", " Shadow "),
                description: "Set Active Register to a value",
                hidden: true,
                default: 0,
            }
        )
    }
    return xcmp_RegConfig
}
function generateShadowRegisters3Config(reg_name)
{
    let xcmp_RegArr = device_driverlib_peripheral.EPWM_XCMPReg.slice(27, 35);
    let xcmp_RegConfig = [];
    
    for(var xcmp_Reg_Index in xcmp_RegArr)
    {
        xcmp_RegConfig = xcmp_RegConfig.concat(
            {
                name: "epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_Reg_Index].name.replace("EPWM_", ""),
                displayName: xcmp_RegArr[xcmp_Reg_Index].displayName.replace("_SHADOW", " Shadow "),
                description: "Set Active Register to a value",
                hidden: true,
                default: 0,
            }
        )
    }
    return xcmp_RegConfig
}
// Generate XAQ events
function generateXAQConfig(reg_name, EPWMxAorB)
{
    let group_xaq = [];
    if(reg_name == "XCMPA"){
        for(var xcmp_set_index in device_driverlib_peripheral.EPWM_XCMP)
        {
            let xcmp_aq_event_config = [];
            let xcmp_set = device_driverlib_peripheral.EPWM_XCMP[xcmp_set_index];
            for(var xcmp_aq_events_index in device_driverlib_peripheral.EPWM_XCMPActionQualifierOutputEvent)
            {
                let xcmp_aq_events = device_driverlib_peripheral.EPWM_XCMPActionQualifierOutputEvent[xcmp_aq_events_index];
                xcmp_aq_event_config = xcmp_aq_event_config.concat([
                    {
                        name: reg_name + "_" + xcmp_set.name.replace("EPWM_XCMP_", "") + xcmp_aq_events.name.replace("EPWM_AQ", ""),
                        displayName: xcmp_aq_events.displayName,
                        description: "",
                        longDescription: "",
                        hidden: true,
                        default: device_driverlib_peripheral.EPWM_ActionQualifierOutput[0].name,
                        options: device_driverlib_peripheral.EPWM_ActionQualifierOutput
                    }
            ])
            }
            group_xaq = group_xaq.concat(
                {
                    name: "GROUP_XAQ_" + EPWMxAorB + "_" + reg_name + "_" + xcmp_set.name,
                    displayName: xcmp_set.displayName,
                    description: "",
                    longDescription: "When XCMP mode is enabled, AQ can now have up to three shadow buffer levels with their own AQ events",
                    config: xcmp_aq_event_config
                }
            )
        }
    }else if (reg_name == "XCMPB"){
        for(var xcmp_set_index in device_driverlib_peripheral.EPWM_XCMP)
        {
            let xcmp_set = device_driverlib_peripheral.EPWM_XCMP[xcmp_set_index];
            let xcmp_aq_event_config = [];
            // Grab only the action qualifiers for XCMP5-8 when XCMP is split between cmpb and cmpa
            let xcmpb_options = device_driverlib_peripheral.EPWM_XCMPActionQualifierOutputEvent.slice(4,9);
            for(var xcmp_aq_events_index in xcmpb_options)
            {
                let xcmp_aq_events = xcmpb_options[xcmp_aq_events_index];
                xcmp_aq_event_config = xcmp_aq_event_config.concat([
                    {
                        name: reg_name + "_" + xcmp_set.name.replace("EPWM_XCMP_", "") + xcmp_aq_events.name.replace("EPWM_AQ", ""),
                        displayName: xcmp_aq_events.displayName,
                        description: "",
                        longDescription: "",
                        hidden: true,
                        default: device_driverlib_peripheral.EPWM_ActionQualifierOutput[0].name,
                        options: device_driverlib_peripheral.EPWM_ActionQualifierOutput
                    }
                ])
            }
            group_xaq = group_xaq.concat(
                {
                    name: "GROUP_XAQ_" + EPWMxAorB + "_" + reg_name + "_" + xcmp_set.name,
                    displayName: xcmp_set.displayName,
                    description: "",
                    longDescription: "When XCMP mode is enabled, AQ can now have up to three shadow buffer levels with their own AQ events",
                    config: xcmp_aq_event_config
                }
            )
        }
    }
    return group_xaq;
}

function onChangeActiveAndShdwRegistersConfig(inst, ui, reg_name, startIndex, stopIndex)
{
    // this not only sets the active and shadow buffer, but it also shows the action qualifier active and shadow buffers
    let xcmp_RegArr = device_driverlib_peripheral.EPWM_XCMPReg.slice(0,8);
    let xcmp_Shdw1RegArr = device_driverlib_peripheral.EPWM_XCMPReg.slice(9,17);
    let xcmp_Shdw2RegArr = device_driverlib_peripheral.EPWM_XCMPReg.slice(18,26);
    let xcmp_Shdw3RegArr = device_driverlib_peripheral.EPWM_XCMPReg.slice(27,35);
    for(var xcmp_Reg_Index in xcmp_RegArr)
    {
        if(xcmp_Reg_Index >= startIndex && xcmp_Reg_Index < stopIndex)
        {
            ui["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_Reg_Index].name.replace("EPWM_", "")].hidden = false;
            ui["epwmXCMP_set" + reg_name + "_" + xcmp_Shdw1RegArr[xcmp_Reg_Index].name.replace("EPWM_", "")].hidden = false;
            ui["epwmXCMP_set" + reg_name + "_" + xcmp_Shdw2RegArr[xcmp_Reg_Index].name.replace("EPWM_", "")].hidden = false;
            ui["epwmXCMP_set" + reg_name + "_" + xcmp_Shdw3RegArr[xcmp_Reg_Index].name.replace("EPWM_", "")].hidden = false;

        }else
        {
            ui["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_Reg_Index].name.replace("EPWM_", "")].hidden = true; 
            ui["epwmXCMP_set" + reg_name + "_" + xcmp_Shdw1RegArr[xcmp_Reg_Index].name.replace("EPWM_", "")].hidden = true;
            ui["epwmXCMP_set" + reg_name + "_" + xcmp_Shdw2RegArr[xcmp_Reg_Index].name.replace("EPWM_", "")].hidden = true;
            ui["epwmXCMP_set" + reg_name + "_" + xcmp_Shdw3RegArr[xcmp_Reg_Index].name.replace("EPWM_", "")].hidden = true;
        }
    }
    // show action qualifier events when user chooses 
    for(var xcmp_set_index in device_driverlib_peripheral.EPWM_XCMP)
    {
        let xcmp_set = device_driverlib_peripheral.EPWM_XCMP[xcmp_set_index];
        for(var xcmp_aq_events_index in device_driverlib_peripheral.EPWM_XCMPActionQualifierOutputEvent)
        {
            if(xcmp_aq_events_index >= startIndex && xcmp_aq_events_index < stopIndex)
            {
                let xcmp_aq_events = device_driverlib_peripheral.EPWM_XCMPActionQualifierOutputEvent[xcmp_aq_events_index];
                if(reg_name == "XCMPA")
                {
                    ui[reg_name + "_" + xcmp_set.name.replace("EPWM_XCMP_", "") + xcmp_aq_events.name.replace("EPWM_AQ", "")].hidden = false;
                }else if(reg_name == "XCMPB")
                {
                    ui[ reg_name + "_" + xcmp_set.name.replace("EPWM_XCMP_", "") + xcmp_aq_events.name.replace("EPWM_AQ", "")].hidden = false;
                }
            }else
            {
                let xcmp_aq_events = device_driverlib_peripheral.EPWM_XCMPActionQualifierOutputEvent[xcmp_aq_events_index];
                if((xcmp_aq_events.name == "EPWM_AQ_OUTPUT_ON_TIMEBASE_XCMP1" || xcmp_aq_events.name == "EPWM_AQ_OUTPUT_ON_TIMEBASE_XCMP2" ||
                   xcmp_aq_events.name == "EPWM_AQ_OUTPUT_ON_TIMEBASE_XCMP3" || xcmp_aq_events.name == "EPWM_AQ_OUTPUT_ON_TIMEBASE_XCMP4") && reg_name == "XCMPB")
                {
                    continue;
                }
                if(reg_name == "XCMPA")
                {
                    ui[ reg_name + "_" + xcmp_set.name.replace("EPWM_XCMP_", "") + xcmp_aq_events.name.replace("EPWM_AQ", "")].hidden = true;
                }else if(reg_name == "XCMPB")
                {
                    ui[ reg_name + "_" + xcmp_set.name.replace("EPWM_XCMP_", "") + xcmp_aq_events.name.replace("EPWM_AQ", "")].hidden = true;
                }
            }
        }
    }
}
// Add higher level before calling on change allocate registers

function setAllocateRegistersXCMPANoSplitorSplit(inst, ui)
{
    if(inst["epwmXCMP_selectAllocationXCMPA_NoSplitorSplit"] == "EPWM_XCMP_NONE_CMPA")
    {
        onChangeActiveAndShdwRegistersConfig(inst, ui, "XCMPA", 0, 0);
    }
    if(inst["epwmXCMP_selectAllocationXCMPA_NoSplitorSplit"] == "EPWM_XCMP_1_CMPA")
    {
        onChangeActiveAndShdwRegistersConfig(inst, ui, "XCMPA", 0, 1);
    }
    if(inst["epwmXCMP_selectAllocationXCMPA_NoSplitorSplit"] == "EPWM_XCMP_2_CMPA")
    {
        onChangeActiveAndShdwRegistersConfig(inst, ui, "XCMPA", 0, 2);
    }
    if(inst["epwmXCMP_selectAllocationXCMPA_NoSplitorSplit"] == "EPWM_XCMP_3_CMPA")
    {
        onChangeActiveAndShdwRegistersConfig(inst, ui, "XCMPA", 0, 3);
    }
    if(inst["epwmXCMP_selectAllocationXCMPA_NoSplitorSplit"] == "EPWM_XCMP_4_CMPA")
    {
        onChangeActiveAndShdwRegistersConfig(inst, ui, "XCMPA", 0, 4);
    }
    if(inst["epwmXCMP_selectAllocationXCMPA_NoSplitorSplit"] == "EPWM_XCMP_5_CMPA" && !inst.epwmXCMP_RegisterSplit_enable)
    {
        onChangeActiveAndShdwRegistersConfig(inst, ui, "XCMPA", 0, 5);
    }
    if(inst["epwmXCMP_selectAllocationXCMPA_NoSplitorSplit"] == "EPWM_XCMP_6_CMPA" && !inst.epwmXCMP_RegisterSplit_enable)
    {
        onChangeActiveAndShdwRegistersConfig(inst, ui, "XCMPA", 0, 6);
    }
    if(inst["epwmXCMP_selectAllocationXCMPA_NoSplitorSplit"] == "EPWM_XCMP_7_CMPA" && !inst.epwmXCMP_RegisterSplit_enable)
    {
        onChangeActiveAndShdwRegistersConfig(inst, ui, "XCMPA", 0, 7);
    }
    if(inst["epwmXCMP_selectAllocationXCMPA_NoSplitorSplit"] == "EPWM_XCMP_8_CMPA" && !inst.epwmXCMP_RegisterSplit_enable)
    {
        onChangeActiveAndShdwRegistersConfig(inst, ui, "XCMPA", 0, 8);
    }
}

function setAllocateRegistersSplitXCMPB(inst, ui)
{
    if(inst["epwmXCMP_selectAllocationXCMPB_Split"] == "EPWM_XCMP_5_CMPB")
    {
        onChangeActiveAndShdwRegistersConfig(inst, ui, "XCMPB", 4, 5);
    }
    if(inst["epwmXCMP_selectAllocationXCMPB_Split"] == "EPWM_XCMP_6_CMPB")
    {
        onChangeActiveAndShdwRegistersConfig(inst, ui, "XCMPB", 4, 6);
    }
    if(inst["epwmXCMP_selectAllocationXCMPB_Split"] == "EPWM_XCMP_7_CMPB")
    {
        onChangeActiveAndShdwRegistersConfig(inst, ui, "XCMPB", 4, 7);
    }
    if(inst["epwmXCMP_selectAllocationXCMPB_Split"] == "EPWM_XCMP_8_CMPB")
    {
        onChangeActiveAndShdwRegistersConfig(inst, ui, "XCMPB", 4, 8);
    }
}
function hideXCMPregisters(inst, ui, reg_name)
{
    let xcmp_RegArr = device_driverlib_peripheral.EPWM_XCMPReg.slice(0, 8);
    // hide active register
    for(var xcmp_Reg_Index in xcmp_RegArr)
    {
        if(reg_name == "XCMPC" || reg_name == "XCMPD")
        {
            ui["epwmXCMP_set" + reg_name].hidden = true;
            inst["epwmXCMP_set" + reg_name] = 0;
        }else
        {
            ui["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_Reg_Index].name.replace("EPWM_", "")].hidden = true;
            inst["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_Reg_Index].name.replace("EPWM_", "")] = 0;
        }

    }

    xcmp_RegArr = device_driverlib_peripheral.EPWM_XCMPReg.slice(9,17);   
    // hide shadow buffer set 1
    for(var xcmp_Reg_Index in xcmp_RegArr)
    {
        if(reg_name == "XCMPC" || reg_name == "XCMPD")
        {
            ui["epwmXCMP_setShadowRegisters1" + reg_name].hidden = true;
            inst["epwmXCMP_setShadowRegisters1" + reg_name] = 0;
        }else
        {
            ui["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_Reg_Index].name.replace("EPWM_", "")].hidden = true;
            inst["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_Reg_Index].name.replace("EPWM_", "")] = 0;
        }
    }
    xcmp_RegArr = device_driverlib_peripheral.EPWM_XCMPReg.slice(18,26);
    // hide shadow buffer set 2
    for(var xcmp_Reg_Index in xcmp_RegArr)
    {
        if(reg_name == "XCMPC" || reg_name == "XCMPD")
        {
            ui["epwmXCMP_setShadowRegisters2" + reg_name].hidden = true;
            inst["epwmXCMP_setShadowRegisters2" + reg_name] = 0;

        }else
        {
            ui["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_Reg_Index].name.replace("EPWM_", "")].hidden = true;
            inst["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_Reg_Index].name.replace("EPWM_", "")] = 0;
        }
    }
    xcmp_RegArr = device_driverlib_peripheral.EPWM_XCMPReg.slice(27,35); 
    // hide shadow buffer set 3
    for(var xcmp_Reg_Index in xcmp_RegArr)
    {
        if(reg_name == "XCMPC" || reg_name == "XCMPD")
        {
            ui["epwmXCMP_setShadowRegisters3" + reg_name].hidden = true;
            inst["epwmXCMP_setShadowRegisters3" + reg_name] = 0;
        }else
        {
            ui["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_Reg_Index].name.replace("EPWM_", "")].hidden = true;
            inst["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_Reg_Index].name.replace("EPWM_", "")] = 0;
        }
    }

    // Hide action qualifier events 
    for(var xcmp_set_index in device_driverlib_peripheral.EPWM_XCMP)
    {
        let xcmp_set = device_driverlib_peripheral.EPWM_XCMP[xcmp_set_index];
        for(var xcmp_aq_events_index in device_driverlib_peripheral.EPWM_XCMPActionQualifierOutputEvent)
        {
            let xcmp_aq_events = device_driverlib_peripheral.EPWM_XCMPActionQualifierOutputEvent[xcmp_aq_events_index];
            if((xcmp_aq_events.name == "EPWM_AQ_OUTPUT_ON_TIMEBASE_XCMP1" || xcmp_aq_events.name == "EPWM_AQ_OUTPUT_ON_TIMEBASE_XCMP2" ||
                xcmp_aq_events.name == "EPWM_AQ_OUTPUT_ON_TIMEBASE_XCMP3" || xcmp_aq_events.name == "EPWM_AQ_OUTPUT_ON_TIMEBASE_XCMP4") && reg_name == "XCMPB")
            {
                continue;
            }
            // No action qualifiers for cmpc/cmpd
            if(reg_name == "XCMPC" || reg_name == "XCMPD"){
                break;
            }else
            {
                if(reg_name == "XCMPA")
                {
                    ui[ reg_name + "_" + xcmp_set.name.replace("EPWM_XCMP_", "") + xcmp_aq_events.name.replace("EPWM_AQ", "")].hidden = true;
                    inst[ reg_name + "_" + xcmp_set.name.replace("EPWM_XCMP_", "") + xcmp_aq_events.name.replace("EPWM_AQ", "")] = "EPWM_AQ_OUTPUT_NO_CHANGE";
                }else if(reg_name == "XCMPB")
                {
                    ui[reg_name + "_" + xcmp_set.name.replace("EPWM_XCMP_", "") + xcmp_aq_events.name.replace("EPWM_AQ", "")].hidden = true;
                    inst[ reg_name + "_" + xcmp_set.name.replace("EPWM_XCMP_", "") + xcmp_aq_events.name.replace("EPWM_AQ", "")] = "EPWM_AQ_OUTPUT_NO_CHANGE";
                }
            }
        }
    }
}

function onChangeEnableDisable(inst, ui)
{
    if(inst.epwmXCMP_enable)
    {
        
        // show check box to enable split
        ui["epwmXCMP_RegisterSplit_enable"].hidden = false;
        // show XCMPA since that will be default option when split or no split is chosen
        ui["epwmXCMP_selectAllocationXCMPA_NoSplitorSplit"].hidden = false;

        // show XTBPRD options
        ui["epwmXCMP_setRegisters_XTBPRD"].hidden = false;
        ui["epwmXCMP_setShadowRegisters1_XTBPRD"].hidden = false;
        ui["epwmXCMP_setShadowRegisters2_XTBPRD"].hidden = false;
        ui["epwmXCMP_setShadowRegisters3_XTBPRD"].hidden = false;

        // show XMINMAX options
        ui["epwmXCMP_setRegisters_XMIN"].hidden = false;
        ui["epwmXCMP_setShadowRegisters1_XMIN"].hidden = false;
        ui["epwmXCMP_setShadowRegisters2_XMIN"].hidden = false;
        ui["epwmXCMP_setShadowRegisters3_XMIN"].hidden = false;
        ui["epwmXCMP_setRegisters_XMAX"].hidden = false;
        ui["epwmXCMP_setShadowRegisters1_XMAX"].hidden = false;
        ui["epwmXCMP_setShadowRegisters2_XMAX"].hidden = false;
        ui["epwmXCMP_setShadowRegisters3_XMAX"].hidden = false;
        // show xcmpa load options
        ui["epwmXCMP_RegisterFrcLoad_enable"].hidden = false;
        ui["epwmXCMP_selectLoadMode"].hidden = false;
        ui["epwmXCMP_selectShadowRegisterLevelLoad"].hidden = false;
        ui["epwmXCMP_selectNumberShadowRegisterLevels"].hidden = false;
        ui["epwmXCMP_selectRepeatCountShadowRegisterLevel2"].hidden = false;
        ui["epwmXCMP_selectRepeatCountShadowRegisterLevel3"].hidden = false;
        // show xmpc load options
        ui["epwmXCMP_setShadowRegisters1XCMPC"].hidden = false;
        ui["epwmXCMP_setXCMPC"].hidden = false;
        ui["epwmXCMP_setShadowRegisters2XCMPC"].hidden = false;
        ui["epwmXCMP_setShadowRegisters3XCMPC"].hidden = false;

        // show xmpd load options
        ui["epwmXCMP_setShadowRegisters1XCMPD"].hidden = false;
        ui["epwmXCMP_setXCMPD"].hidden = false;
        ui["epwmXCMP_setShadowRegisters2XCMPD"].hidden = false;
        ui["epwmXCMP_setShadowRegisters3XCMPD"].hidden = false;
        // show xcmp loading for all 
        ui["epwmXCMP_RegisterLoad_enable"].hidden = false;
        if(inst.epwmXCMP_RegisterSplit_enable)
        {
            // if split is enabled, show XCMPB options, show XCMPA split options
            ui["epwmXCMP_selectAllocationXCMPA_NoSplitorSplit"].hidden = false;
            ui["epwmXCMP_selectAllocationXCMPB_Split"].hidden = false;
            // show load options for xcmpb
            setAllocateRegistersXCMPANoSplitorSplit(inst, ui);
            setAllocateRegistersSplitXCMPB(inst, ui);
        }else if(!inst.epwmXCMP_RegisterSplit_enable)
        {
            ui["epwmXCMP_selectAllocationXCMPA_NoSplitorSplit"].hidden = false;
            // if split is not enabled, hide XCMPB options
            ui["epwmXCMP_selectAllocationXCMPB_Split"].hidden = true;
            inst.epwmXCMP_selectAllocationXCMPB_Split = "EPWM_XCMP_5_CMPB";
            setAllocateRegistersXCMPANoSplitorSplit(inst, ui);
            hideXCMPregisters(inst, ui, "XCMPB");
            
        }
    }else
    {
    // reset settings
        // hide all the xcmpa split and no split options, set split enabled to false when XCMP mode is disabled
        inst.epwmXCMP_RegisterSplit_enable = false;
        inst.epwmXCMP_selectAllocationXCMPA_NoSplitorSplit = "EPWM_XCMP_NONE_CMPA";
        inst.epwmXCMP_selectAllocationXCMPB_Split = "EPWM_XCMP_5_CMPB";
        ui["epwmXCMP_selectAllocationXCMPA_NoSplitorSplit"].hidden = true;
        // hide all the xcmpb split options
        ui["epwmXCMP_selectAllocationXCMPB_Split"].hidden = true;
        ui["epwmXCMP_RegisterSplit_enable"].hidden = true;
        
        // hide all the loading options XCMPA, set the default load mode to load once for all xcmpc registers
        inst.epwmXCMP_selectAllocationXCMPA_NoSplitorSplit = "EPWM_XCMP_NONE_CMPA";
        inst.epwmXCMP_selectNumberShadowRegisterLevels = "EPWM_XCMP_XLOADCTL_SHDWLEVEL_0";
        inst["epwmXCMP_selectLoadMode"] = "EPWM_XCMP_XLOADCTL_LOADMODE_LOADONCE";
        inst.epwmXCMP_selectShadowRegisterLevelLoad = "EPWM_XCMP_XLOADCTL_SHDWBUFPTR_NULL";
        inst.epwmXCMP_selectRepeatCountShadowRegisterLevel2 = "1";
        inst.epwmXCMP_selectRepeatCountShadowRegisterLevel3 = "1";
        inst.epwmXCMP_RegisterFrcLoad_enable = false;

        ui["epwmXCMP_RegisterFrcLoad_enable"].hidden = true;
        ui["epwmXCMP_selectLoadMode"].hidden = true;
        ui["epwmXCMP_selectShadowRegisterLevelLoad"].hidden = true;
        ui["epwmXCMP_selectNumberShadowRegisterLevels"].hidden = true;
        ui["epwmXCMP_selectRepeatCountShadowRegisterLevel2"].hidden = true;
        ui["epwmXCMP_selectRepeatCountShadowRegisterLevel3"].hidden = true;
        // hide all set register options and hide all AQ event output configurations
        hideXCMPregisters(inst, ui, "XCMPA");
        hideXCMPregisters(inst, ui, "XCMPB");
        hideXCMPregisters(inst, ui, "XCMPC");
        hideXCMPregisters(inst, ui, "XCMPD");       
        // hide all tbprd options
        ui["epwmXCMP_setRegisters_XTBPRD"].hidden = true;
        ui["epwmXCMP_setShadowRegisters1_XTBPRD"].hidden = true;
        ui["epwmXCMP_setShadowRegisters2_XTBPRD"].hidden = true;
        ui["epwmXCMP_setShadowRegisters3_XTBPRD"].hidden = true;
        inst["epwmXCMP_setRegisters_XTBPRD"] = 0;
        inst["epwmXCMP_setShadowRegisters1_XTBPRD"] = 0;
        inst["epwmXCMP_setShadowRegisters2_XTBPRD"] = 0;
        inst["epwmXCMP_setShadowRegisters3_XTBPRD"] = 0;
        // show XMINMAX options
        ui["epwmXCMP_setRegisters_XMIN"].hidden = true;
        ui["epwmXCMP_setShadowRegisters1_XMIN"].hidden = true;
        ui["epwmXCMP_setShadowRegisters2_XMIN"].hidden = true;
        ui["epwmXCMP_setShadowRegisters3_XMIN"].hidden = true;
        ui["epwmXCMP_setRegisters_XMAX"].hidden = true;
        ui["epwmXCMP_setShadowRegisters1_XMAX"].hidden = true;
        ui["epwmXCMP_setShadowRegisters2_XMAX"].hidden = true;
        ui["epwmXCMP_setShadowRegisters3_XMAX"].hidden = true;
        inst["epwmXCMP_setRegisters_XMIN"] = 0;
        inst["epwmXCMP_setShadowRegisters1_XMIN"] = 0;
        inst["epwmXCMP_setShadowRegisters2_XMIN"] = 0;
        inst["epwmXCMP_setShadowRegisters3_XMIN"] = 0;
        inst["epwmXCMP_setRegisters_XMAX"] = 0;
        inst["epwmXCMP_setShadowRegisters1_XMAX"] = 0;
        inst["epwmXCMP_setShadowRegisters2_XMAX"] = 0;
        inst["epwmXCMP_setShadowRegisters3_XMAX"] = 0;
        // hide all xmp load
        ui["epwmXCMP_RegisterLoad_enable"].hidden = true;
        inst.epwmXCMP_RegisterLoad_enable = false;
    }
}

function onChangeLoadMode(inst, ui)
{
    if(inst.epwmXCMP_selectLoadMode == "EPWM_XCMP_XLOADCTL_LOADMODE_LOADONCE" && inst.epwmXCMP_RegisterLoadXCMPA_enable)
    {
        ui["epwmXCMP_selectShadowRegisterLevelLoad"].hidden = false;
    }
    else if(inst.epwmXCMP_selectLoadModeXCMPB == "EPWM_XCMP_XLOADCTL_LOADMODE_LOADONCE" && inst.epwmXCMP_RegisterLoadXCMPB_enable)
    {
        ui["epwmXCMP_selectShadowRegisterLevelLoadXCMPB"].hidden = false;
    }
    else if(inst.epwmXCMP_selectLoadModeXCMPC == "EPWM_XCMP_XLOADCTL_LOADMODE_LOADONCE" && inst.epwmXCMP_RegisterLoadXCMPC_enable)
    {
        ui["epwmXCMP_selectShadowRegisterLevelLoadXCMPC"].hidden = false;
    }
    else if(inst.epwmXCMP_selectLoadModeXCMPD == "EPWM_XCMP_XLOADCTL_LOADMODE_LOADONCE" && inst.epwmXCMP_RegisterLoadXCMPD_enable)
    {
        ui["epwmXCMP_selectShadowRegisterLevelLoadXCMPD"].hidden = false;
    }
    else
    {
        ui["epwmXCMP_selectShadowRegisterLevelLoad"].hidden = true;
        ui["epwmXCMP_selectShadowRegisterLevelLoadXCMPB"].hidden = true;
        ui["epwmXCMP_selectShadowRegisterLevelLoadXCMPC"].hidden = true;
        ui["epwmXCMP_selectShadowRegisterLevelLoadXCMPD"].hidden = true;

    }
}
var config = [
    {
        name: "epwmXCMP_enable",
        displayName: "Enable XCMP Mode",
        description: "If XCMP mode is disabled, EPWM will behave like Type4",
        hidden: false,
        default: false,
        onChange: onChangeEnableDisable
    },
    {
        name: "epwmXCMP_RegisterSplit_enable",
        displayName: "Enable Split XCMP Registers",
        description: "Split the XCMP registers between CMPA and CMPB. CMPA and CMPB can have max of 4 registers allocated. ",
        hidden: true,
        default: false,
        onChange: onChangeEnableDisable
    },
    {
        name: "epwmXCMP_RegisterLoad_enable",
        displayName: "Enable X Load",
        description: "Enables register loading of shadow buffers for all XCMP registers",
        hidden: true,
        default: false,
        onChange: onChangeEnableDisable
    },
    {
        name: "epwmXCMP_RegisterFrcLoad_enable",
        displayName: "Force X Load",
        description: "Software force register loading of shadow buffers for all XCMP registers",
        hidden: true,
        default: false,
    },
    {
        name: "epwmXCMP_selectNumberShadowRegisterLevels",
        displayName : "Number of Shadow Buffer Levels",
        description : 'Number of shadow buffer levels to configure, you can use one or two or all 3 shadow buffer sets',
        hidden      : true,
        default     : device_driverlib_peripheral.EPWM_XCMP_XLOADCTL_SHDWLEVEL[0].name,
        options     : device_driverlib_peripheral.EPWM_XCMP_XLOADCTL_SHDWLEVEL,
    },
    {
        name: "epwmXCMP_selectLoadMode",
        displayName : "Load Mode",
        description : 'Loading once will behave like type4. Loading Multiple will cycle through all shadow buffer sets and load them at the end of period.',
        hidden      : true,
        default     : device_driverlib_peripheral.EPWM_XCMPXloadCtlLoadMode[0].name,
        options     : device_driverlib_peripheral.EPWM_XCMPXloadCtlLoadMode,
    },
    {
        name: "epwmXCMP_selectShadowRegisterLevelLoad",
        displayName : "Shadow Buffer Level to Load Once",
        description : 'Can load to active registers from either shadow buffer set 3, 2 or 1 first',
        hidden      : true,
        default     : device_driverlib_peripheral.EPWM_XCMP_XLOADCTL_SHDWBUFPTR[0].name,
        options     : device_driverlib_peripheral.EPWM_XCMP_XLOADCTL_SHDWBUFPTR,
    },
    {
        name: "epwmXCMP_selectRepeatCountShadowRegisterLevel2",
        displayName : "Number of Times to Repeat Shadow Buffer Set 2",
        description : 'Number of times to repeat a shadow buffer set each PWM cycle, can only be applied to shadow set 2 and 3',
        hidden      : true,
        default     : shadowRegisterReloadNumberofTimesOptions[0].name,
        options     : shadowRegisterReloadNumberofTimesOptions
    },
    {
        name: "epwmXCMP_selectRepeatCountShadowRegisterLevel3",
        displayName : "Number of Times to Repeat Shadow Buffer Set 3",
        description : 'Number of times to repeat a shadow buffer set each PWM cycle, can only be applied to shadow set 2 and 3',
        hidden      : true,
        default     : shadowRegisterReloadNumberofTimesOptions[0].name,
        options     : shadowRegisterReloadNumberofTimesOptions
    },
    {
        name: "GROUP_XCMPA",
        displayName: "XCMPA",
        description: "",
        longDescription: "",
        config: [
            {
                name: "epwmXCMP_selectAllocationXCMPA_NoSplitorSplit",
                displayName : "XCMP Registers to Allocate",
                description : 'XCMP registers can use all 8 XCMPA registers or can use a selection of the 8 XCMPA registers',
                hidden      : true,
                default     : device_driverlib_peripheral.EPWM_XCMP_ALLOC_CMPA[0].name,
                options     : device_driverlib_peripheral.EPWM_XCMP_ALLOC_CMPA,
                onChange    : onChangeEnableDisable
            },
            {
                name: "GROUP_XCMPA_ACTIVE_REGISTERS",
                displayName: "Active Registers",
                description: "",
                longDescription: "",
                config: [
                ]
            },
            {
                name: "GROUP_XCMPA_SHDW_REGISTERS1",
                displayName: "Shadow Buffer Set 1",
                description: "",
                longDescription: "",
                config: [
                ]
            },
            {
                name: "GROUP_XCMPA_SHDW_REGISTERS2",
                displayName: "Shadow Buffer Set 2",
                description: "",
                longDescription: "",
                config: [
                ]
            },
            {
                name: "GROUP_XCMPA_SHDW_REGISTERS3",
                displayName: "Shadow Buffer Set 3",
                description: "",
                longDescription: "",
                config: [
                ]
            },
        ]
    },
    {
        name: "GROUP_XCMPB",
        displayName: "XCMPB",
        description: "",
        longDescription: "",
        config: [
            {
                name: "epwmXCMP_selectAllocationXCMPB_Split",
                displayName : "XCMP Registers to Allocate",
                description : 'XCMP registers can use all 8 XCMPA registers or can use a selection of the 8 XCMPA registers',
                hidden      : true,
                default     : device_driverlib_peripheral.EPWM_XCMP_ALLOC_CMPB[0].name,
                options     : device_driverlib_peripheral.EPWM_XCMP_ALLOC_CMPB,
                onChange    : onChangeEnableDisable
            },
            {
                name: "GROUP_XCMPB_ACTIVE_REGISTERS",
                displayName: "Active Registers",
                description: "",
                longDescription: "",
                config: [
                ]
            },
            {
                name: "GROUP_XCMPB_SHDW_REGISTERS1",
                displayName: "Shadow Buffer Set 1",
                description: "",
                longDescription: "",
                config: [
                ]
            },
            {
                name: "GROUP_XCMPB_SHDW_REGISTERS2",
                displayName: "Shadow Buffer Set 2",
                description: "",
                longDescription: "",
                config: [
                ]
            },
            {
                name: "GROUP_XCMPB_SHDW_REGISTERS3",
                displayName: "Shadow Buffer Set 3",
                description: "",
                longDescription: "",
                config: [
                ]
            },

        ]
    },
    {
        name: "GROUP_XCMPC",
        displayName: "XCMPC",
        description: "",
        longDescription: "",
        config: [
            {
                name: "epwmXCMP_setXCMPC",
                displayName: "XCMPC active register value",
                description: "Set Active Register to a value, XCMPC can only have one active register allocated to it",
                hidden: true,
                default: 0,
            },
            {
                name: "epwmXCMP_setShadowRegisters1XCMPC",
                displayName: "XCMPC Shadow 1",
                description: "Set shadow buffer 1 to a value, this value will be loaded every PWM Cycle",
                hidden: true,
                default: 0,
            },
            {
                name: "epwmXCMP_setShadowRegisters2XCMPC",
                displayName: "XCMPC Shadow 2",
                description: "Set shadow buffer 2 to a value, this value will be loaded every PWM Cycle",
                hidden: true,
                default: 0,
            },
            {
                name: "epwmXCMP_setShadowRegisters3XCMPC",
                displayName: "XCMPC Shadow 3",
                description: "Set shadow buffer 3 to a value, this value will be loaded every PWM Cycle",
                hidden: true,
                default: 0,
            },
            
        ]
    },
    {
        name: "GROUP_XCMPD",
        displayName: "XCMPD",
        description: "",
        longDescription: "",
        config: [
            {
                name: "epwmXCMP_setXCMPD",
                displayName: "XCMPD active register value",
                description: "Set Active Register to a value, XCMPD can only have one active register allocated to it",
                hidden: true,
                default: 0,
            },
            {
                name: "epwmXCMP_setShadowRegisters1XCMPD",
                displayName: "XCMPD Shadow 1",
                description: "Set shadow buffer 1 to a value, this value will be loaded every PWM Cycle",
                hidden: true,
                default: 0,
            },
            {
                name: "epwmXCMP_setShadowRegisters2XCMPD",
                displayName: "XCMPD Shadow 2",
                description: "Set shadow buffer 2 to a value, this value will be loaded every PWM Cycle",
                hidden: true,
                default: 0,
            },
            {
                name: "epwmXCMP_setShadowRegisters3XCMPD",
                displayName: "XCMPD Shadow 3",
                description: "Set shadow buffer 3 to a value, this value will be loaded every PWM Cycle",
                hidden: true,
                default: 0,
            },
            
        ]
    },
    {
        name: "GROUP_XTBPRD",
        displayName: "XTBPRD Configuration",
        description: "",
        longDescription: "XTBPRD will be used instead of TBPRD in type5, this includes having 3 shadow buffer sets and 1 active register",
        config: [
            {
                name: "epwmXCMP_setRegisters_XTBPRD",
                displayName: "Time Base Period",
                description: "Set XTBPRD Register to a value, during XCMP mode TBPRD is replaced with XTBPRD",
                hidden: true,
                default: 0,
            },
            {
                name: "epwmXCMP_setShadowRegisters1_XTBPRD",
                displayName: "Time Base Period Shadow 1",
                description: "Set XTBPRD Shadow Buffer to a value",
                hidden: true,
                default: 0,
            },
            {
                name: "epwmXCMP_setShadowRegisters2_XTBPRD",
                displayName: "Time Base Period Shadow 2",
                description: "Set XTBPRD Shadow Buffer to a value",
                hidden: true,
                default: 0,
            },
            {
                name: "epwmXCMP_setShadowRegisters3_XTBPRD",
                displayName: "Time Base Period Shadow 3",
                description: "Set XTBPRD Shadow Buffer to a value",
                hidden: true,
                default: 0,
            }
        ]
    },
    {
        name: "GROUP_AQ_XCMPA_A",
        displayName: "ePWMxA Event Output Configuration (Action Qualifier)",
        description: "",
        longDescription: "",
        config: [

        ]
    },
    {
        name: "GROUP_AQ_XCMPB_B",
        displayName: "ePWMxB Event Output Configuration (Action Qualifier)",
        description: "",
        longDescription: "",
        config: [

        ]
    },
    {
        name: "GROUP_XMINMAX",
        displayName: "XMINMAX Configuration (Edge Detection)",
        description: "",
        longDescription: "XMIN and XMAX registers will be used to set a defined window to monitor an event and send out a trip event if event does not occur within window. Within Digital Compare, enable Use Event Detection",
        config: [
            {
                name: "epwmXCMP_setRegisters_XMIN",
                displayName: "XMIN",
                description: "Set XMIN Register to a value",
                hidden: true,
                default: 0,
            },
            {
                name: "epwmXCMP_setShadowRegisters1_XMIN",
                displayName: "XMIN Shadow 1",
                description: "Set XMIN Shadow Buffer to a value",
                hidden: true,
                default: 0,
            },
            {
                name: "epwmXCMP_setShadowRegisters2_XMIN",
                displayName: "XMIN Shadow 2",
                description: "Set XMIN Shadow Buffer to a value",
                hidden: true,
                default: 0,
            },
            {
                name: "epwmXCMP_setShadowRegisters3_XMIN",
                displayName: "XMIN Shadow 3",
                description: "Set XMIN Shadow Buffer to a value",
                hidden: true,
                default: 0,
            },
            {
                name: "epwmXCMP_setRegisters_XMAX",
                displayName: "XMAX",
                description: "Set XMINMAX Register to a value",
                hidden: true,
                default: 0,
            },  
            {
                name: "epwmXCMP_setShadowRegisters1_XMAX",
                displayName: "XMAX Shadow 1",
                description: "Set XMINMAX Shadow Buffer to a value",
                hidden: true,
                default: 0,
            },     
            {
                name: "epwmXCMP_setShadowRegisters2_XMAX",
                displayName: "XMAX Shadow 2",
                description: "Set XMINMAX Shadow Buffer to a value",
                hidden: true,
                default: 0,
            },
            {
                name: "epwmXCMP_setShadowRegisters3_XMAX",
                displayName: "XMAX Shadow 3",
                description: "Set XMINMAX Shadow Buffer to a value",
                hidden: true,
                default: 0,
            }
        ]
    },

];
// Generate the configuration for active, shadow buffers 
let start_config_index = 1; 
let start_xcmpa_config_index = 9;
let start_xcmpb_config_index = 10;
let start_xaq_config_index = 14;
config[start_xcmpa_config_index].config[start_config_index].config = config[start_xcmpa_config_index].config[start_config_index].config.concat(generateActiveRegistersConfig("XCMPA"));
config[start_xcmpa_config_index].config[start_config_index + 1].config = config[start_xcmpa_config_index].config[start_config_index + 1].config.concat(generateShadowRegisters1Config("XCMPA"));
config[start_xcmpa_config_index].config[start_config_index + 2].config = config[start_xcmpa_config_index].config[start_config_index + 2].config.concat(generateShadowRegisters2Config("XCMPA"));
config[start_xcmpa_config_index].config[start_config_index + 3].config = config[start_xcmpa_config_index].config[start_config_index + 3].config.concat(generateShadowRegisters3Config("XCMPA"));

config[start_xcmpb_config_index].config[start_config_index].config = config[start_xcmpb_config_index].config[start_config_index].config.concat(generateActiveRegistersConfig("XCMPB"));
config[start_xcmpb_config_index].config[start_config_index + 1].config = config[start_xcmpb_config_index].config[start_config_index + 1].config.concat(generateShadowRegisters1Config("XCMPB"));
config[start_xcmpb_config_index].config[start_config_index + 2].config = config[start_xcmpb_config_index].config[start_config_index + 2].config.concat(generateShadowRegisters2Config("XCMPB"));
config[start_xcmpb_config_index].config[start_config_index + 3].config = config[start_xcmpb_config_index].config[start_config_index + 3].config.concat(generateShadowRegisters3Config("XCMPB"));

// Generate the XAQ configs for epwmxA and epwmxB
config[start_xaq_config_index].config = config[start_xaq_config_index].config.concat(generateXAQConfig("XCMPA", "EPWMXA"));
config[start_xaq_config_index + 1].config = config[start_xaq_config_index + 1].config.concat(generateXAQConfig("XCMPB", "EPWMXB"));
var epwmXCMPmodeSubmodule = {
    displayName: "EPWM XCMP Mode",
    maxInstances: Common.peripheralCount("EPWM"),
    defaultInstanceName: "EPWM_XCMP",
    description: "Enhanced Pulse Width Modulator XCMP Mode Configuration",
    config: config,
    templates: {
        boardc : "", //"/gpio/gpio.board.c.xdt",
        boardh : ""//"/gpio/gpio.board.h.xdt"
    },
};


exports = epwmXCMPmodeSubmodule;
