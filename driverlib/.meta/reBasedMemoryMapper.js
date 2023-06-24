//function takes in the device memory and a list of all registers and their associated bitfields and offsets. This is used to map the device memory values into the associated
//registers and returns the data as described below.
function parseMemoryIntoReg(deviceMemory, regMemory){
    var regMemOut = '';
    let regArrayLength = regMemory.length;
    var sizeofregMemory = 0;
    for (let i = 0; i < regArrayLength; i++) {
        //Get data for current register
        let regBits = regMemory[i].bits
        let bitArrayLength = regBits.length;
        let regOffset = regMemory[i].offset;
        regOffset = parseInt(regOffset, 16) + 1; //Convert hex offset to decimal
        let registerName = regMemory[i].name;

        var memoryReg = "";
        var regAdded = 0;
        var syscfgName = "";
        //Register has defined bit fields
        if (bitArrayLength > 0) {
            //Loop through bits of current register
            for (let j = 0; j < bitArrayLength; j++) {  
                //Get data for current bit  
                let bitName = regMemory[i].bits[j].name;
                sizeofregMemory += parseInt(regBits[j].size);
                //Check for 32 bit register
                if (regMemory[i].bits[j].size == 16) {
                    memoryReg = '0x' + deviceMemory[regOffset + 1].trim() + deviceMemory[regOffset].trim() //32 bit register, add next 16 bit memory
                }
                else {
                    memoryReg = '0x' + deviceMemory[regOffset].trim() //Memory at given offset is for current register
                }

                //Check if top-level register has been logged
                if (regAdded == 0) {
                    regMemOut = regMemOut + registerName + ' = ' + memoryReg + '\n'; //Add register name and memory to output
                    regAdded = 1; //Top level register has been logged
                } 
                //below two values are for debug only
                // let regCheck = regMemory[i].bits[j].mask;
                // let shift = regMemory[i].bits[j].shift;

                let memoryBit = (memoryReg & regMemory[i].bits[j].mask) >> regMemory[i].bits[j].shift; //Shift register memory and apply mask to get bit result
                regMemOut = regMemOut + registerName + '.' + bitName + ' = 0x' + memoryBit.toString(16).toUpperCase() + '\n'; //Add bit name and memory to output
            }
        }
        else {
            memoryReg = deviceMemory[regOffset] //Memory at given offset is for current register
            regMemOut = regMemOut + registerName + ' = 0x' + memoryReg + '\n'; //Add register name and memory to output
            sizeofregMemory += 16;
        }
    }
    //cleaning data for return into format of [string object, dictionary object] wherein the dictionary object has been cleaned and seperated into values of 'name' and 'value'
    var regMemoryArray = regMemOut.split('\n');
    var regMemDictName = {};
    let iter = 0;
    while(iter < regMemoryArray.length){;
        regMemoryArray[iter] = regMemoryArray[iter].replace(/\s/g, '').split('=');
        regMemDictName["name"] = regMemoryArray[iter][0];
        regMemDictName["value"] = regMemoryArray[iter][1];
        regMemDictName["mappings"] = 0;
        regMemoryArray[iter] = Object.assign({}, regMemDictName);
        iter++;
    }
    iter = 0;
    //removing unnecessary toplevel registers that cloud the data in future steps
    for(let regis of regMemory){
        while(iter < regMemoryArray.length){
            if(regis.name == regMemoryArray[iter].name){
                if(regis.bits.length != 0){
                    regMemoryArray.splice(iter, 1);
                    break;
                }
                else{
                    iter++
                    break;
                }
            }

            iter++;
        }
    }
    //removing extraneous empty array index at the end of the register mappings
    if (regMemoryArray[regMemoryArray.length-1].name == ''){
        regMemoryArray.pop();
    }
    //returning array where first object is a single string of all mappings seperated by newlines and the 2nd object is an array of dictionaries with each dictionary
    //fitting into the format of 'name' and 'value' for each index with values still in their hex representation
    return [regMemOut, regMemoryArray]
}

//using the mapped register memory from the above function, information about all available sysconfig options for the device, and the handler functions, this function will map
//the register memory values into their associated sysconfig option names. (as noted below, some options will have multiple entries of themselves due to some peculiarities but
//will be dealt with in later steps of the mapping process)
function parseRegIntoSyscfgMem(syscfgData1, parsedRegMem, handler_funcs){
    var syscfgMemOut = "";
    //regHits and sysHits are used for debug purposes to track how many registers and syscfg options are having a mapping match them
    var regHits = 0;
    var sysHits = 0;
    //'.mappings' is used for debug purposes while '.MapHit' is used to track failings in the mapping as EVERY syscfg option should be mapped but not every register will be.
    for(let i = 0; i < parsedRegMem.length; i++){
        for(let sysData of syscfgData1){
            //logic for if the 'register' data in the epwm.json only has a single register in it
            if(parsedRegMem[i].name == sysData.register){
                if("handler" in sysData){
                    //call handler that returns a string and boolean of if a match was hit and add to memOut and a 'skip' flag if necessary to skip over future logic blocks
                    if(parsedRegMem[i].mappings < 2){
                        let vals = handler_funcs.handlemap(parsedRegMem[i], sysData, parsedRegMem);
                        if (vals[0] == false){/*console.log("Handler on " + sysData.name + " does not have a case configured, please correct.");*/ continue;} 
                        parsedRegMem[i].mappings += vals[0];
                        syscfgMemOut += vals[1];
                        sysHits++;
                        sysData.MapHit += 1;
                        if (parsedRegMem[i].mappings == 2){break;}
                        continue;
                    }
                }
                //when no handler is present, simple mapping between register value and the associated syscfg option name
                else{
                    syscfgMemOut += sysData.name + " = " + parsedRegMem[i].value + '\n';
                    parsedRegMem[i].mappings++;
                    sysHits++;
                    sysData.MapHit += 1;
                    break;
                }
            }
            //logic for if the 'register' data in the epwm.json has multiple registers in it [all multi-register settings REQUIRE handlers for functionalty]
            else if(Array.isArray(sysData.register) && sysData.register.includes(parsedRegMem[i].name)){
                let vals = handler_funcs.handlemap(parsedRegMem[i], sysData, parsedRegMem); //in many cases, vals[1] (the string of mapped data) WILL be empty due to the register value being not set.
                //if the data mapped and the no return flag was raised with no 'MapHit's yet, then map the value into the final data.
                if (vals[0] == true && vals[2] == true && sysData.MapHit == 0){
                    syscfgMemOut += vals[1];
                }
                //if the data mapped and the no return flag was raised but 'MapHit' has already been incremented, you skip mapping this into the final data.
                else if (vals[0] == true && vals[2] == true && sysData.MapHit != 0){
                    continue;
                }
                //if the data mapped and the no return flag wasn't raised, always map into the final data.
                else if (vals[0] == true && vals[2] == false){
                    syscfgMemOut += vals[1];
                }
                //if none of the above, either the map_handler you've written has broken OR you need to create one for this option
                else{
                    syscfgMemOut += sysData.name + " = " + parsedRegMem[i].value + ' // VALUE HAS/NEEDS HANDLER\n';
                }
                parsedRegMem[i].mappings ++;
                if(sysData.MapHit == 0){sysHits++;}
                sysData.MapHit++;
            }
        }
        if(parsedRegMem[i].mappings > 0){regHits++;}
    }
    //the below loop is predominantly for debug purposes. Helps dev to figure out which syscfg option isn't mapping to a register OR is mapping too many times. 
    for(let sysData of syscfgData1){
        if(sysData.MapHit == 0){
            syscfgMemOut += sysData.name + " // HAS NO MATCHING REGISTER ASSOCIATED, SUPPOSED REGISTER IS: " + sysData.register + '\n';
        }
        else if(sysData.MapHIT > 1){
            syscfgMemOut += sysData.name + " // HAS MAPPED MULTIPLE TIMES, SUPPOSED REGISTER IS: " + sysData.register + '\n';
        }
    }
    //cleaning data for return into format of [string object, dictionary object] wherein the dictionary object has been cleaned and seperated into values of 'name' and 'value'
    var sysMemoryArray = syscfgMemOut.split('\n');
    var sysMemDictName = {};
    let iter = 0;
    while(iter < sysMemoryArray.length){
        //don't want options with errors to be sent into the next stage, as such they are removed from the cleaned data but remain in the printed data
        if(sysMemoryArray[iter].includes("//")){
            sysMemoryArray.splice(iter, 1);
        }
        else{
            sysMemoryArray[iter] = sysMemoryArray[iter].replace(/\s/g, '').split('=');
            sysMemDictName["name"] = sysMemoryArray[iter][0];
            sysMemDictName["value"] = sysMemoryArray[iter][1];
            sysMemoryArray[iter] = Object.assign({}, sysMemDictName);
            iter++;
        }
    }
    //removing extraneous empty array index at the end of the syscfg name mappings
    if (sysMemoryArray[sysMemoryArray.length-1].name == ''){
        sysMemoryArray.pop();
    }
    //returning array where first object is a single string of all mappings seperated by newlines and the 2nd object is an array of dictionaries with each dictionary
    //fitting into the format of 'name' and 'value' for each index with values still in their hex representation
    return [syscfgMemOut, sysMemoryArray];
}

function parseSyscfgMemToValues(parsedSyscfgData, enumData, sysOptions){
    var mappedMemoryOut = "";
    //mappedHits is used for debug and testing purposes to help devs see what total percentage of syscfg options with register mappings have value mappings
    var mappedHits = 0;
    for(let sysData of parsedSyscfgData){
        let reset = 0;
        let hit = 0;
        let selOption = sysOptions[sysData.name];
        //the process for mapping does NOT work without a default value, so creating a temporary default for this without one and then resetting it afterwards
        if(selOption.default.length == 0){
            selOption.default = selOption.options[0].name;
            reset = 1;
        }
        //dealing with mapping values with a default value that is an integer or string representation of one
        if(selOption.default === 0 || selOption.default === '0'){
            let decValue = parseInt(sysData.value, 16);
            mappedMemoryOut += sysData.name + " = " + decValue + '\n';
            mappedHits++;
            hit = 1;
        }
        //due to the mapping only currently working for a single peripheral at a time right now (for example, can only map EPWM1 or EPWM2, not both at once), the linking setting
        //is impossible to match though hopefully will be added back in with future functionality increases
        else if(selOption.default == 'EPWM_LINK_WITH_DISABLE'){
            mappedMemoryOut += sysData.name + " = " + selOption.default + '\n';
            mappedHits++;
            hit = 1;
        }
        //dealing with mapping values with a default value that is a boolean
        else if(selOption.default === false){
            if(parseInt(sysData.value, 16) == 0){
                mappedMemoryOut += sysData.name + " = " + "false\n";
                mappedHits++;
                hit = 1;
            }
            else if(parseInt(sysData.value, 16) == 1){
                mappedMemoryOut += sysData.name + " = " + "true\n";
                mappedHits++;
                hit = 1;
            }
            //debugging failures in mapping boolean values
            else{
                console.log("Error. Issue with boolean value register setting.")
            }
        }
        //dealing with mapping values with a default value that is a boolean (same logic as above but 'flipped')
        else if(selOption.default === true){
            if(parseInt(sysData.value, 16) == 0){
                mappedMemoryOut += sysData.name + " = " + "true\n";
                mappedHits++;
                hit = 1;
            }
            else if(parseInt(sysData.value, 16) == 1){
                mappedMemoryOut += sysData.name + " = " + "false\n";
                mappedHits++;
                hit = 1;
            }
            //debugging failures in mapping boolean values
            else{
                console.log("Error. Issue with boolean value register setting.")
            }
        }
        //for all other cases, as in default values that are not integers or booleans, the process consists of finding the default value of a setting within the enumerated values
        //as their is no simple direct mapping and then, by using the value stored with each setting name, mapping the correct syscfg option value to name.
        else{
            for(let enums in enumData){
                let selEnums = enumData[enums];
                for(let i = 0; i < selEnums.length; i++){
                    let checker = selEnums[i]
                    if (selEnums[i].name == selOption.default){
                        for(let j = 0; j < selEnums.length; j++){
                            if(parseInt(sysData.value, 16) == selEnums[j].value){
                                mappedMemoryOut += sysData.name + " = " + selEnums[j].name + '\n';
                                mappedHits++;
                                hit = 1;
                                break;
                            }
                            else if (sysData.value == selEnums[j].value){
                                mappedMemoryOut += sysData.name + " = " + selEnums[j].name + '\n';
                                mappedHits++;
                                hit = 1;
                                break;
                            }
                        }
                    }
                //the 'hit == 1' breaks are to make the logic function quicker once its found a match rather than going through every piece of data every time
                    if(hit == 1){break;}
                }
                if(hit == 1){break;}
            }
        }
        //debug setting to help devs figure out which syscfg options didn't map to an enumerated value
        if(hit != 1){
            //console.log("This setting did NOT map to any non-boolean value: " + sysData.name);
        }
        //resetting the defaults for those without a default as mentioned above
        if(reset == 1){
            selOption.default = [];
        }
    }
    //cleaning data for return into format of [string object, dictionary object] wherein the dictionary object has been cleaned and seperated into values of 'name' and 'value'
    var mapMemoryArray = mappedMemoryOut.split('\n');
    var mapMemDictName = {};
    let iter = 0;
    while(iter < mapMemoryArray.length){;
        mapMemoryArray[iter] = mapMemoryArray[iter].replace(/\s/g, '').split('=');
        mapMemDictName["name"] = mapMemoryArray[iter][0];
        mapMemDictName["value"] = mapMemoryArray[iter][1];
        if(mapMemDictName["value"] == "false"){mapMemDictName["value"] = false;}
        else if(mapMemDictName["value"] == "true"){mapMemDictName["value"] = true;}
        mapMemoryArray[iter] = Object.assign({}, mapMemDictName);
        //because some values have multiple mappings that require them to be stored within an array, we must check every step of the way for multiple options with the same name
        //and either create the array to store them OR if this has already been done, push the value onto the array
        if(iter > 0 && mapMemoryArray[iter].name == mapMemoryArray[iter-1].name){
            if(typeof (mapMemoryArray[iter-1].value) == "string"){
                let arrayHold = [];
                mapMemoryArray[iter-1].value = mapMemoryArray[iter-1].value.replace(';', '');
                mapMemoryArray[iter].value = mapMemoryArray[iter].value.replace(';', '');
                arrayHold.push(mapMemoryArray[iter-1].value);
                arrayHold.push(mapMemoryArray[iter].value);
                mapMemoryArray[iter-1].value = Object.assign([], arrayHold);
            }
            else{
                mapMemoryArray[iter].value = mapMemoryArray[iter].value.replace(';', '');
                mapMemoryArray[iter-1].value.push(mapMemoryArray[iter].value);
            }
            mapMemoryArray.splice(iter, 1);
            continue;
        }
        iter++;
    }
    //removing extraneous empty array index at the end of the syscfg value mappings
    if (mapMemoryArray[mapMemoryArray.length-1].name == ''){
        mapMemoryArray.pop();
    }
    //for the VAST majority of syscfg options in most cases, they will still be in their default value. We ONLY care about the non-default values as those are what will be put
    //into sysconfig AND be used for testing purposes against the testbank of data. As a result, the below block checks default values against the mapped values to see if they
    //should be mapped through to the final step. For options with NO default (typically shown as an empty array), if ANYTHING is set, then consider it non-default. Every other
    //default type uses direct matching to check. 
    let mappedMemNoDefaults = [];
    for(let mapDicts of mapMemoryArray){
        let options = sysOptions[mapDicts.name].default;
        if (Array.isArray(mapDicts.value)){mappedMemNoDefaults.push(mapDicts);}
        if (options === [] && !(mapDicts.value)){
            mappedMemNoDefaults.push(mapDicts);
        }
        else if (mapDicts.value === false || mapDicts.value === true){
            if(options === mapDicts.value){
                continue;
            }
            else{
                mappedMemNoDefaults.push(mapDicts);
            }
        }
        else if ( typeof mapDicts.value == 'string'){
            if (options == mapDicts.value){
                continue;
            }
            else if(options.toString() == mapDicts.value){
                continue;
            }
            else{
                mappedMemNoDefaults.push(mapDicts);
            }
        }
    }
    //for debug purposes, all of the non-default data is stored within a string with newlines in the exact same format as the string of default and non-default data.
    var noDefaults = '';
    for(let mapDicts of mappedMemNoDefaults){
        noDefaults += mapDicts.name + " = " + mapDicts.value + '\n';
    }
    // console.log("Percentage Final Mapped = " + (mappedHits/parsedSyscfgData.length)*100 + "%");
    //returning array where first object is a single string of all mappings seperated by newlines and the 2nd object is an array of dictionaries with each dictionary
    //fitting into the format of 'name' and 'value' for each index with values still in their hex representation. The 3rd object is an array of dictionaries with the exact same
    //structure as the 2nd object but for ONLY non-default values and the 4th object is a string of all non-default mappigns seperated by newlines.
    return [mappedMemoryOut, mapMemoryArray, mappedMemNoDefaults, noDefaults];
}

//The mapping process has been split into three different functions as described above.
module.exports = { 
    parseMemoryIntoReg : parseMemoryIntoReg,
    parseRegIntoSyscfgMem : parseRegIntoSyscfgMem, 
    parseSyscfgMemToValues : parseSyscfgMemToValues
};