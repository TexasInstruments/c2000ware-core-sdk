function handlemap(assocReg, sysData, allRegs){ 
    var match = false;
    var doNotFlag = false;
    var sysMem = "";
    var numStore = parseInt(assocReg.value, 16);
    numStore = numStore.toString(2);
    numStore = numStore.padStart(2, "0");
    switch(sysData.handler){
        case "epwmDeadband_InputX_Handler":
            if (sysData.name == "epwmDeadband_inputRED"){
                sysMem += sysData.name + " = 0x" + numStore[1] + '\n';
                match = true;
            }
            else if (sysData.name == "epwmDeadband_inputFED"){
                let LOADMODE = '';
                for(let i = 0; i < allRegs.length; i++){
                    if(allRegs[i].name.includes("DEDB_MODE")){
                        LOADMODE = allRegs[i].value;
                        break;
                    }
                }
                if (LOADMODE == "0x1"){
                    sysMem += sysData.name + " = 0x2\n";
                    match = true;
                }    
                else{
                    sysMem += sysData.name + " = 0x" + numStore[0] + '\n';
                    match = true;
                }
            }
            break;
        case "epwmDeadband_OutputX_Handler":
            if (sysData.name == "epwmDeadband_enableRED"){
                sysMem += sysData.name + " = 0x" + numStore[0] + '\n';
                match = true;
            }
            else if (sysData.name == "epwmDeadband_enableFED"){
                sysMem += sysData.name + " = 0x" + numStore[1] + '\n';
                match = true;
            }
            break;
        case "epwmDeadband_OutputSwapX_Handler":
            if (sysData.name == "epwmDeadband_outputSwapOutA"){
                sysMem += sysData.name + " = 0x" + numStore[1]  + '\n';
                match = true;
            }
            else if (sysData.name == "epwmDeadband_outputSwapOutB"){
                sysMem += sysData.name + " = 0x" + numStore[0] + '\n';
                match = true;
            }
            break;
        case "epwmDeadband_PolarityX_Handler":
            if (sysData.name == "epwmDeadband_polarityRED"){
                sysMem += sysData.name + " = 0x" + numStore[1] + '\n';
                match = true;
            }
            else if (sysData.name == "epwmDeadband_polarityFED"){
                sysMem += sysData.name + " = 0x" + numStore[0] + '\n';
                match = true;
            }
            break;
        case "epwmAQ_Output_X_Source_handler":
            sysMem += sysData.name + " = " + assocReg.value + '\n';
            match = true;
            break;
        case "epwmTimebase_syncOutPulseMode_handler":
            if (assocReg.name == "TBCTL.SYNCOSEL"){
                if (assocReg.value == "0x3"){
                    //has to wait for TBCTL2.SYNCOSELX to get value
                    match = true;
                }
                else{
                    sysMem += sysData.name + " = " + assocReg.value + '\n';
                    match = true;
                    doNotFlag = true;
                }
            }
            else if (assocReg.name == "TBCTL2.SYNCOSELX"){
                if (assocReg.value == "0x0"){
                    sysMem += sysData.name + " = 0x4\n";
                    doNotFlag = true;
                    match = true;
                }
                else{
                    sysMem += sysData.name + " = 0x" + (parseInt(assocReg.value, 16) + 4) + '\n';
                    doNotFlag = true;
                    match = true;
                }
            }
            break;
        case "epwmTimebase_syncOutPulseModeExpanded_handler":
            if (assocReg.name == "SYNCOUTEN.SWEN"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = EPWM_SYNCOUTEN_SWEN\n"
                    match = true;
                }
                else{
                    match = true;
                }
            }
            if (assocReg.name == "SYNCOUTEN.ZEROEN"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = EPWM_SYNCOUTEN_ZEROEN\n"
                    match = true;
                }
                else{
                    match = true;
                }
            }
            if (assocReg.name == "SYNCOUTEN.CMPBEN"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = EPWM_SYNCOUTEN_CMPBEN\n"
                    match = true;
                }
                else{
                    match = true;
                }
            }
            if (assocReg.name == "SYNCOUTEN.CMPCEN"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = EPWM_SYNCOUTEN_CMPCEN\n"
                    match = true;
                }
                else{
                    match = true;
                }
            }
            if (assocReg.name == "SYNCOUTEN.CMPDEN"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = EPWM_SYNCOUTEN_CMPDEN\n"
                    match = true;
                }
                else{
                    match = true;
                }
            }
            if (assocReg.name == "SYNCOUTEN.DCAEVT1EN"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = EPWM_SYNCOUTEN_DCAEVT1EN\n"
                    match = true;
                }
                else{
                    match = true;
                }
            }
            if (assocReg.name == "SYNCOUTEN.DCBEVT1EN"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = EPWM_SYNCOUTEN_DCBEVT1EN\n"
                    match = true;
                }
                else{
                    match = true;
                }
            }
            break;
        case "epwmCounterCompare_ShadowLoadMode_Handler":
            if(assocReg.name == "CMPCTL.LOADAMODE" || assocReg.name == "CMPCTL.LOADBMODE" || assocReg.name == "CMPCTL2.LOADCMODE" || assocReg.name == "CMPCTL2.LOADDMODE"){
                match = true;
            }
            else if(assocReg.name == "CMPCTL.LOADASYNC" || assocReg.name == "CMPCTL.LOADBSYNC" || assocReg.name == "CMPCTL2.LOADCSYNC" || assocReg.name == "CMPCTL2.LOADDSYNC"){
                if (assocReg.value == "0x2"){
                    sysMem += sysData.name + " = 0x8\n";
                }
                else{
                    let LOADMODE = '';
                    let nameFormat = assocReg.name.replace("SYNC", '');
                    for(let i = 0; i < allRegs.length; i++){
                        if(allRegs[i].name.includes(nameFormat)){
                            LOADMODE = allRegs[i].value;
                            break;
                        }
                    }
                    if (LOADMODE == "0x3"){
                        sysMem += sysData.name + " = " + LOADMODE + "\n";
                    }
                    else if (assocReg.value == "0x0"){
                        sysMem += sysData.name + " = " + LOADMODE + "\n";
                        match = true;
                    }
                    else if(assocReg.value == "0x1"){
                        LOADMODE = parseInt(LOADMODE, 16) + 4;
                        sysMem += sysData.name + " = " + LOADMODE + "\n";
                    }
                }
                match = true;
            }
            break;
        case "epwmEventTrigger_SOC_triggerSource_Handler":
            if(assocReg.name == "ETSEL.SOCASELCMP" || assocReg.name == "ETSEL.SOCBSELCMP"){
                match = true;
            }
            else if(assocReg.name == "ETSEL.SOCASEL" || assocReg.name == "ETSEL.SOCBSEL"){
                if(assocReg.value == "0x0" || assocReg.value == "0x1" || assocReg.value == "0x2" || assocReg.value == "0x3"){
                    sysMem += sysData.name + " = " + assocReg.value + '\n';
                }
                else{
                    let LOADMODE = '';
                    let nameFormat = '';
                    if(assocReg.name == "ETSEL.SOCASEL"){
                        nameFormat = "SOCASELCMP";
                    }
                    else if(assocReg.name == "ETSEL.SOCBSEL")
                        nameFormat = "SOCBSELCMP";
                    for(let i = 0; i < allRegs.length; i++){
                        if(allRegs[i].name.includes(nameFormat)){
                            LOADMODE = allRegs[i].value;
                            break;
                        }
                    }
                    if (LOADMODE == "0x0"){
                        //for CMPA and CMPB
                        sysMem += sysData.name + " = " + assocReg.value + '\n';
                        match = true;
                    }
                    else if (LOADMODE = "0x1"){
                        //for CMPC and CMPD
                        let value_hold = parseInt(assocReg.value, 16) * 2;
                        sysMem += sysData.name + " = 0x" + value_hold.toString(16) + '\n';
                        match = true;
                    }
                }
            }
            break;
        case "epwmTripZone_cbcSource_handler":
            if (assocReg.name == "TZSEL.CBC1"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x1\n";
                }
                match = true;
            }
            else if (assocReg.name == "TZSEL.CBC2"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x2\n";
                }
                match = true;
            }
            else if (assocReg.name == "TZSEL.CBC3"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x4\n";
                }
                match = true;
            }
            else if (assocReg.name == "TZSEL.CBC4"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x8\n";
                }
                match = true;
            }
            else if (assocReg.name == "TZSEL.CBC5"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x10\n";
                }
                match = true;
            }
            else if (assocReg.name == "TZSEL.CBC6"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x20\n";
                }
                match = true;
            }
            else if (assocReg.name == "TZSEL.DCAEVT2"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x40\n";
                }
                match = true;
            }
            else if (assocReg.name == "TZSEL.DCBEVT2"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x80\n";
                }
                match = true;
            }
            break;
        case "epwmTripZone_oneShotSource_handler":
            if (assocReg.name == "TZSEL.OSHT1"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x100\n";
                }
                match = true;
            }
            else if (assocReg.name == "TZSEL.OSHT2"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x200\n";
                }
                match = true;
            }
            else if (assocReg.name == "TZSEL.OSHT3"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x400\n";
                }
                match = true;
            }
            else if (assocReg.name == "TZSEL.OSHT4"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x800\n";
                }
                match = true;
            }
            else if (assocReg.name == "TZSEL.OSHT5"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x1000\n";
                }
                match = true;
            }
            else if (assocReg.name == "TZSEL.OSHT6"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x2000\n";
                }
                match = true;
            }
            else if (assocReg.name == "TZSEL.DCAEVT1"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x4000\n";
                }
                match = true;
            }
            else if (assocReg.name == "TZSEL.DCBEVT1"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x8000\n";
                }
                match = true;
            }
            break;
        case "epwmDigitalCompare_combinationInputConfigHandler":
            assocReg.name = assocReg.name.split(".")[1]
            if (assocReg.name == "TRIPINPUT1"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x1\n";
                }
                match = true;
            }
            else if (assocReg.name == "TRIPINPUT2"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x2\n";
                }
                match = true;
            }
            else if (assocReg.name == "TRIPINPUT3"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x4\n";
                }
                match = true;
            }
            else if (assocReg.name == "TRIPINPUT4"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x8\n";
                }
                match = true;
            }
            else if (assocReg.name == "TRIPINPUT5"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x10\n";
                }
                match = true;
            }
            else if (assocReg.name == "TRIPINPUT6"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x20\n";
                }
                match = true;
            }
            else if (assocReg.name == "TRIPINPUT7"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x40\n";
                }
                match = true;
            }
            else if (assocReg.name == "TRIPINPUT8"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x80\n";
                }
                match = true;
            }
            else if (assocReg.name == "TRIPINPUT9"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x100\n";
                }
                match = true;
            }
            else if (assocReg.name == "TRIPINPUT10"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x200\n";
                }
                match = true;
            }
            else if (assocReg.name == "TRIPINPUT11"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x400\n";
                }
                match = true;
            }
            else if (assocReg.name == "TRIPINPUT12"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x800\n";
                }
                match = true;
            }
            else if (assocReg.name == "TRIPINPUT13"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x1000\n";
                }
                match = true;
            }
            else if (assocReg.name == "TRIPINPUT14"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x2000\n";
                }
                match = true;
            }
            else if (assocReg.name == "TRIPINPUT15"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x4000\n";
                }
                match = true;
            }
            break;
        case "epwmTripZone_tzISHandler":
            if (assocReg.name == "TZEINT.CBC"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x2\n";
                }
                match = true;
            }
            else if (assocReg.name == "TZEINT.OST"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x4\n";
                }
                match = true;
            }
            else if (assocReg.name == "TZEINT.DCAEVT1"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x8\n";
                }
                match = true;
            }
            else if (assocReg.name == "TZEINT.DCAEVT2"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x10\n";
                }
                match = true;
            }
            else if (assocReg.name == "TZEINT.DCBEVT1"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x20\n";
                }
                match = true;
            }
            else if (assocReg.name == "TZEINT.DCBEVT2"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x40\n";
                }
                match = true;
            }
        case "epwmLock_handler":
            if (assocReg.name == "EPWMLOCK.HRLOCK"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x1\n";
                }
                match = true;
            }
            else if (assocReg.name == "EPWMLOCK.GLLOCK"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x2\n";
                }
                match = true;
            }
            else if (assocReg.name == "EPWMLOCK.TZCFGLOCK"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x4\n";
                }
                match = true;
            }
            else if (assocReg.name == "EPWMLOCK.TZCLRLOCK"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x8\n";
                }
                match = true;
            }
            else if (assocReg.name == "EPWMLOCK.DCLOCK"){
                if (assocReg.value == "0x1"){
                    sysMem += sysData.name + " = 0x10\n";
                }
                match = true;
            }
            break;
    }
    return [match, sysMem, doNotFlag];
}


module.exports = {
    handlemap: handlemap,
}