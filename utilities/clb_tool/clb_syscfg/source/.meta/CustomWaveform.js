const commentRe = /^\/\//;
const repeatCmdRe = /^rpt\s*\(\s*(?<cycles>\w+)\s*\)/i;
const repeatEndCmdRe = /^rpt_end/i;
const highCmdRe = /^high\s*\(\s*(?<cycles>\w+)\s*\)/i;	
const lowCmdRe = /^low\s*\(\s*(?<cycles>\w+)\s*\)/i;	
const macroCmdRe = /^#define\s*(?<pattern>\w+)\s*(?<replacer>\w+)\s*/i;
    
function macroReplace(str,mapObj){
    let keys = [...mapObj.keys()];
    //var re = new RegExp(Object.keys(mapObj).join("|"),"gi");
    var re = new RegExp(keys.join("|"),"gi");

    return str.replace(re, function(matched){
        //return mapObj[matched.toLowerCase()];
        //return mapObj.get(matched).toLowerCase();
        return mapObj.get(matched);
    });
}

function stringToDec(inputString) {
    const inputStringHexRe = /^0x(?<hexString>\w+)/;
    const inputStringDecRe = /^(?<decString>\w+)/;
    var inputNumber = 0;
    
    // hex number
    if(inputStringHexRe.test(inputString)){
        const hexNumInput = inputStringHexRe.exec(inputString);
        
        inputNumber = parseInt(hexNumInput.groups.hexString,16);
    }
    // decimal number
    else {
        const decNumInput = inputStringDecRe.exec(inputString);
        
        inputNumber = parseInt(decNumInput.groups.decString,10);
    }
                    
    // check the result
    if (isNaN(inputNumber) || inputNumber < 0) { 
        return -1; 
    }
    else {
        return inputNumber;
    }
}

//
// Syntax:
//
// #define pattern replacer, used to define macros  
// high(n), sets waveform high for n CLB cycles
// low(n), sets waveform low for n CLB cycles
// rpt(n), starts a repeat block, code encapsulated by rpt_end will be repeated a total of n times
// rpt_end, denotes the end of a repeat block
//
// n can be defined as hex number using 0xN format
//
function genWaveData(waveProgString) {
    if((waveProgString.length <= 0) || (!waveProgString))
    {
        return "Error: Please enter valid code"
    }
    const arrayOfLines = waveProgString.split("\n"); // arrayOfLines is array where every element is string of one line
    var outputStatus = 0;
    var repeat = 0, repeatCount = 0;
    var repeatString = '';
    var waveOutputDataString = '';

    var mapMacros = new Map();
    
    for(var i = 0;i < arrayOfLines.length;i++){
    
        if(mapMacros.size !== 0){
            // replace all macros
            //console.log("macro replacement for: " + arrayOfLines[i]);
            arrayOfLines[i] = macroReplace(arrayOfLines[i],mapMacros);
            //console.log("macro replacement result: " + arrayOfLines[i]);
        }
    
        // remove whitespace from beginning and end of string
        arrayOfLines[i] = arrayOfLines[i].trim();
        
        // check for comment line
        if(commentRe.test(arrayOfLines[i]))
        {
            //console.log("comment: " + arrayOfLines[i]);
        }
        // check for macro definition
        else if(macroCmdRe.test(arrayOfLines[i])){
            // extract the pattern and replacer from the command
            const match = macroCmdRe.exec(arrayOfLines[i]);

            // add macro to map
            mapMacros.set(match.groups.pattern, match.groups.replacer);
        }
        // check for high command
        else if(highCmdRe.test(arrayOfLines[i])){
            const match = highCmdRe.exec(arrayOfLines[i]);
            const waitCycles = stringToDec(match.groups.cycles);
            var j = 0;
            
            if (waitCycles < 1){
                console.log('invalid cycle count: ' + match.groups.cycles);
                console.log(arrayOfLines[i]);
                return 'Error, line ' + (i+1) + ': Invalid cycle count (' + match.groups.cycles + ')';
            }
            
            outputStatus = 1;
            
            for(j = 0; j<waitCycles; j++){
                if(repeat)
                    repeatString += outputStatus;	
                else
                    waveOutputDataString += outputStatus;
            }
        }			
        // check for low command
        else if(lowCmdRe.test(arrayOfLines[i])){
            const match = lowCmdRe.exec(arrayOfLines[i]);
            const waitCycles = stringToDec(match.groups.cycles);
            var j = 0;
            
            if (waitCycles < 1){
                console.log('invalid cycle count: ' + match.groups.cycles);
                console.log(arrayOfLines[i]);
                return 'Error, line ' + (i+1) + ': Invalid cycle count (' + match.groups.cycles + ')';
            }
            
            outputStatus = 0;
            
            for(j = 0; j<waitCycles; j++){
                if(repeat)
                    repeatString += outputStatus;	
                else
                    waveOutputDataString += outputStatus;
            }
        }
        // check for repeat command
        else if(repeatCmdRe.test(arrayOfLines[i])) {
            const match = repeatCmdRe.exec(arrayOfLines[i]);
            
            // check for nested repeat instructions
            if(repeat === 1) {
                console.log('error: nested repeats not allowed');
                return 'Error, line ' + (i+1) + ': Nested repeat not allowed';
            } else {
                repeat = 1;
            }
            
            repeatCount = stringToDec(match.groups.cycles);
            
            if (repeatCount < 1){
                console.log('invalid repeat command count:' + match.groups.cycles);
                console.log(arrayOfLines[i]);
                return 'Error, line ' + (i+1) + ': Invalid repeat command count (' + match.groups.cycles + ')';
            }
        }
        // check for repeat end command
        else if(repeatEndCmdRe.test(arrayOfLines[i])) {
            var j = 0;
            
            // verify active repeat
            if(repeat ===0){
                console.log('error: repeat_end without rpt instruction');
                //console.log(arrayOfLines[i]);
                return 'Error, line ' + (i+1) + ': Unexpected rpt_end';
            }
            
            for(j = 0; j< repeatCount; j++){
                waveOutputDataString += repeatString;
            }
            
            repeatString = '';
            repeat = 0;
        }
        // blank line
        else if(!/\S/.test(arrayOfLines[i])) {
            // didn't find something other than a space which means it's empty
        }
        // invalid command
        else {
            console.log('unknown command: ' + arrayOfLines[i]);
            //console.log(arrayOfLines[i]);
            return 'Error, line ' + (i+1) + ': Unknown command';
        }
    }
    
    return waveOutputDataString;
}

exports = {
    genWaveData  : genWaveData,
}

//Example text:
//Correct output:
//
/*
#define HALFCYCLE 0xA
  
// Delayed sim start
high( 4   )

// START bit
low(1   )
		
// DATA (0xAAAA)
rpt(16)
	high(HALFCYCLE)
	low(HALFCYCLE)
rpt_end

// CHECK bit
high(1)

// DATA (0x5555)
rpt(16)
	low(1)
	high(1)
rpt_end

// CHECK bit
low(1)

// DATA (0x5555)
rpt(16)
	low(1)
	high(1)
rpt_end

// CHECK bit
low(1)

// DATA (0x5555)
rpt(16)
	low(1)
	high(1)
rpt_end

// CHECK bit
low(1)

// STOP bit
high(1)

high(8)
*/