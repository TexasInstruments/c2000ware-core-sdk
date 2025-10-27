/*
 *  ======== Common ========
 *  Common utility functions for /ti/drivers
 */

exports = {
    getInstanceIndex  : getInstanceIndex, // returns mod.$instances array index of inst
    isCName           : isCName,          // validate name is C identifier
    logError          : logError,         // push error onto into validation obj
    logWarning        : logWarning,       // push warning onto into validation obj
    logInfo           : logInfo,          // push remark onto into validation obj
    print             : print,            // debug: print specified object
    validateNames     : validateNames,    // validate inst names are unique C names
    isSimulatedInput  : isSimulatedInput,
    colonName         : colonName,
    used              : used,
    extract_bit       : extract_bit,
    OUTLUT_truth_table: OUTLUT_truth_table,
    LUT_truth_table   : LUT_truth_table,
    FSM_truth_table   : FSM_truth_table,
    which_instance    : which_instance,
    sigName           : sigName,
    getDeviceName     : getDeviceName,
    isType0           : isType0,
    isType1           : isType1,
    isType2           : isType2,
    isType1_Type2     : isType1_Type2,
    isType0_Type1     : isType0_Type1,
    printDebugObject  : printDebugObject,
    zero_to_16        : [
        { name: 0 },
        { name: 1 },
        { name: 2 },
        { name: 3 },
        { name: 4 },
        { name: 5 },
        { name: 6 },
        { name: 7 },
        { name: 8 },
        { name: 9 },
        { name: 10 },
        { name: 11 },
        { name: 12 },
        { name: 13 },
        { name: 14 },
        { name: 15 },
        { name: 16 },
    ],
    zero_to_31        : [
        { name: 0 },
        { name: 1 },
        { name: 2 },
        { name: 3 },
        { name: 4 },
        { name: 5 },
        { name: 6 },
        { name: 7 },
        { name: 8 },
        { name: 9 },
        { name: 10 },
        { name: 11 },
        { name: 12 },
        { name: 13 },
        { name: 14 },
        { name: 15 },
        { name: 16 },
        { name: 17 },
        { name: 18 },
        { name: 19 },
        { name: 20 },
        { name: 21 },
        { name: 22 },
        { name: 23 },
        { name: 24 },
        { name: 25 },
        { name: 26 },
        { name: 27 },
        { name: 28 },
        { name: 29 },
        { name: 30 },
        { name: 31 },
    ],
    allInputsAry      : [
        { name: '0', displayName: "Zero" },
        { name: '1', displayName: "One" },
        { name: 'BOUNDARY.in0', displayName: "Boundary input 0" },
        { name: 'BOUNDARY.in1', displayName: "Boundary input 1" },
        { name: 'BOUNDARY.in2', displayName: "Boundary input 2" },
        { name: 'BOUNDARY.in3', displayName: "Boundary input 3" },
        { name: 'BOUNDARY.in4', displayName: "Boundary input 4" },
        { name: 'BOUNDARY.in5', displayName: "Boundary input 5" },
        { name: 'BOUNDARY.in6', displayName: "Boundary input 6" },
        { name: 'BOUNDARY.in7', displayName: "Boundary input 7" },
        { name: 'LUT_0.OUT', displayName: "LUT 0 Output" },
        { name: 'LUT_1.OUT', displayName: "LUT 1 Output" },
        { name: 'LUT_2.OUT', displayName: "LUT 2 Output" },
        { name: 'FSM_0.OUT', displayName: "FSM 0 Output" },
        { name: 'FSM_0.S0', displayName: "FSM 0 State 0 Value" },
        { name: 'FSM_0.S1', displayName: "FSM 0 State 1 Value" },
        { name: 'FSM_1.OUT', displayName: "FSM 1 Output" },
        { name: 'FSM_1.S0', displayName: "FSM 1 State 0 Value" },
        { name: 'FSM_1.S1', displayName: "FSM 1 State 1 Value" },
        { name: 'FSM_2.OUT', displayName: "FSM 2 Output" },
        { name: 'FSM_2.S0', displayName: "FSM 2 State 0 Value" },
        { name: 'FSM_2.S1', displayName: "FSM 2 State 1 Value" },
        { name: 'COUNTER_0.count_zero', displayName: "Counter 0 Equals Zero" },
        { name: 'COUNTER_0.count_match1', displayName: "Counter 0 Equals Match 1" },
        { name: 'COUNTER_0.count_match2', displayName: "Counter 0 Equals Match 2" },
        { name: 'COUNTER_1.count_zero', displayName: "Counter 1 Equals Zero" },
        { name: 'COUNTER_1.count_match1', displayName: "Counter 1 Equals Match 1" },
        { name: 'COUNTER_1.count_match2', displayName: "Counter 1 Equals Match 2" },
        { name: 'COUNTER_2.count_zero', displayName: "Counter 2 Equals Zero" },
        { name: 'COUNTER_2.count_match1', displayName: "Counter 2 Equals Match 1" },
        { name: 'COUNTER_2.count_match2', displayName: "Counter 2 Equals Match 2" }
    ],

    altInputsAry        : [
        {name: "OUTLUT_0.out", displayName: "Output LUT 0 Output" },
        {name: "OUTLUT_1.out", displayName: "Output LUT 1 Output" },
        {name: "OUTLUT_2.out", displayName: "Output LUT 2 Output" },
        {name: "OUTLUT_3.out", displayName: "Output LUT 3 Output" },
        {name: "OUTLUT_4.out", displayName: "Output LUT 4 Output" },
        {name: "OUTLUT_5.out", displayName: "Output LUT 5 Output" },
        {name: "OUTLUT_6.out", displayName: "Output LUT 6 Output" },
        {name: "OUTLUT_7.out", displayName: "Output LUT 7 Output" },
        {name: "OUTLUT_0_INVERTED", displayName: "Output LUT 0 Inverted Output" },
        {name: "OUTLUT_1_INVERTED", displayName: "Output LUT 1 Inverted Output" },
        {name: "OUTLUT_2_INVERTED", displayName: "Output LUT 2 Inverted Output" },
        {name: "OUTLUT_3_INVERTED", displayName: "Output LUT 3 Inverted Output" },
        {name: "OUTLUT_4_INVERTED", displayName: "Output LUT 4 Inverted Output" },
        {name: "OUTLUT_5_INVERTED", displayName: "Output LUT 5 Inverted Output" },
        {name: "OUTLUT_6_INVERTED", displayName: "Output LUT 6 Inverted Output" },
        {name: "OUTLUT_7_INVERTED", displayName: "Output LUT 7 Inverted Output" },
        {name: "BOUNDARY_OUT.out0", displayName: "AOC 0 Output" },
        {name: "BOUNDARY_OUT.out1", displayName: "AOC 1 Output" },
        {name: "BOUNDARY_OUT.out2", displayName: "AOC 2 Output" },
        {name: "BOUNDARY_OUT.out3", displayName: "AOC 3 Output" },
        {name: "BOUNDARY_OUT.out4", displayName: "AOC 4 Output" },
        {name: "BOUNDARY_OUT.out5", displayName: "AOC 5 Output" },
        {name: "BOUNDARY_OUT.out6", displayName: "AOC 6 Output" },
        {name: "BOUNDARY_OUT.out7", displayName: "AOC 7 Output" },
        {name: "BOUNDARY_OUT_out0_INVERTED", displayName: "AOC 0 Inverted Output" },
        {name: "BOUNDARY_OUT_out1_INVERTED", displayName: "AOC 1 Inverted Output" },
        {name: "BOUNDARY_OUT_out2_INVERTED", displayName: "AOC 2 Inverted Output" },
        {name: "BOUNDARY_OUT_out3_INVERTED", displayName: "AOC 3 Inverted Output" },
        {name: "BOUNDARY_OUT_out4_INVERTED", displayName: "AOC 4 Inverted Output" },
        {name: "BOUNDARY_OUT_out5_INVERTED", displayName: "AOC 5 Inverted Output" },
        {name: "BOUNDARY_OUT_out6_INVERTED", displayName: "AOC 6 Inverted Output" },
        {name: "BOUNDARY_OUT_out7_INVERTED", displayName: "AOC 7 Inverted Output" },
    ],

    inputNameToValue : {
        '0'                     : 0,
        '1'                     : 8,
        'BOUNDARY.in0'          : 24,
        'BOUNDARY.in1'          : 25,
        'BOUNDARY.in2'          : 26,
        'BOUNDARY.in3'          : 27,
        'BOUNDARY.in4'          : 28,
        'BOUNDARY.in5'          : 29,
        'BOUNDARY.in6'          : 30,
        'BOUNDARY.in7'          : 31,
        'LUT_0.OUT'             : 7,
        'LUT_1.OUT'             : 15,
        'LUT_2.OUT'             : 23,
        'FSM_0.OUT'             : 6,
        'FSM_0.S0'              : 4,
        'FSM_0.S1'              : 5,
        'FSM_1.OUT'             : 14,
        'FSM_1.S0'              : 12,
        'FSM_1.S1'              : 13,
        'FSM_2.OUT'             : 22,
        'FSM_2.S0'              : 20,
        'FSM_2.S1'              : 21,
        'COUNTER_0.count_zero'  : 2,
        'COUNTER_0.count_match1': 3,
        'COUNTER_0.count_match2': 1,
        'COUNTER_1.count_zero'  : 10,
        'COUNTER_1.count_match1': 11,
        'COUNTER_1.count_match2': 9,
        'COUNTER_2.count_zero'  : 18,
        'COUNTER_2.count_match1': 19,
        'COUNTER_2.count_match2': 17,

        // Alternates
        "OUTLUT_0.out" : 0 ,
        "OUTLUT_1.out" : 1 ,
        "OUTLUT_2.out" : 2 ,
        "OUTLUT_3.out" : 3 ,
        "OUTLUT_4.out" : 4 ,
        "OUTLUT_5.out" : 5 ,
        "OUTLUT_6.out" : 6 ,
        "OUTLUT_7.out" : 7 ,
        "OUTLUT_0_INVERTED" : 8 ,
        "OUTLUT_1_INVERTED" : 9 ,
        "OUTLUT_2_INVERTED" : 10,
        "OUTLUT_3_INVERTED" : 11,
        "OUTLUT_4_INVERTED" : 12,
        "OUTLUT_5_INVERTED" : 13,
        "OUTLUT_6_INVERTED" : 14,
        "OUTLUT_7_INVERTED" : 15,
        "BOUNDARY_OUT.out0" : 16,
        "BOUNDARY_OUT.out1" : 17,
        "BOUNDARY_OUT.out2" : 18,
        "BOUNDARY_OUT.out3" : 19,
        "BOUNDARY_OUT.out4" : 20,
        "BOUNDARY_OUT.out5" : 21,
        "BOUNDARY_OUT.out6" : 22,
        "BOUNDARY_OUT.out7" : 23,
        "BOUNDARY_OUT_out0_INVERTED" : 24,
        "BOUNDARY_OUT_out1_INVERTED" : 25,
        "BOUNDARY_OUT_out2_INVERTED" : 26,
        "BOUNDARY_OUT_out3_INVERTED" : 27,
        "BOUNDARY_OUT_out4_INVERTED" : 28,
        "BOUNDARY_OUT_out5_INVERTED" : 29,
        "BOUNDARY_OUT_out6_INVERTED" : 30,
        "BOUNDARY_OUT_out7_INVERTED" : 31,
    },

    altInputNames : [
        "OUTLUT_0.out",
        "OUTLUT_1.out",
        "OUTLUT_2.out",
        "OUTLUT_3.out",
        "OUTLUT_4.out",
        "OUTLUT_5.out",
        "OUTLUT_6.out",
        "OUTLUT_7.out",
        "OUTLUT_0_INVERTED",
        "OUTLUT_1_INVERTED",
        "OUTLUT_2_INVERTED",
        "OUTLUT_3_INVERTED",
        "OUTLUT_4_INVERTED",
        "OUTLUT_5_INVERTED",
        "OUTLUT_6_INVERTED",
        "OUTLUT_7_INVERTED",
        "BOUNDARY_OUT.out0",
        "BOUNDARY_OUT.out1",
        "BOUNDARY_OUT.out2",
        "BOUNDARY_OUT.out3",
        "BOUNDARY_OUT.out4",
        "BOUNDARY_OUT.out5",
        "BOUNDARY_OUT.out6",
        "BOUNDARY_OUT.out7",
        "BOUNDARY_OUT_out0_INVERTED",
        "BOUNDARY_OUT_out1_INVERTED",
        "BOUNDARY_OUT_out2_INVERTED",
        "BOUNDARY_OUT_out3_INVERTED",
        "BOUNDARY_OUT_out4_INVERTED",
        "BOUNDARY_OUT_out5_INVERTED",
        "BOUNDARY_OUT_out6_INVERTED",
        "BOUNDARY_OUT_out7_INVERTED",
    ],

    inputs : {
        OUTLUT   : ['i0','i1','i2'],
        LUT      : ['i0','i1','i2','i3'],
        FSM      : ['e0','e1','xe0','xe1'],
        COUNTER  : ['reset','event','mode0','mode1'],
        HLC      : ['e0','e1','e2','e3'],
        BOUNDARY : ['boundaryInput0','boundaryInput1','boundaryInput2','boundaryInput3','boundaryInput4','boundaryInput5','boundaryInput6','boundaryInput7'],
        AOC      : ['in', 'gate', 'release']
    },

    staticSwitchOptions: [
    { name: 0	, displayName: 'Zero'                   },
    { name: 8	, displayName: 'One'                    },
    { name: 24	, displayName: 'Boundary input 0'       },
    { name: 25	, displayName: 'Boundary input 1'       },
    { name: 26	, displayName: 'Boundary input 2'       },
    { name: 27	, displayName: 'Boundary input 3'       },
    { name: 28	, displayName: 'Boundary input 4'       },
    { name: 29	, displayName: 'Boundary input 5'       },
    { name: 30	, displayName: 'Boundary input 6'       },
    { name: 31	, displayName: 'Boundary input 7'       },
    { name: 7	, displayName: 'LUT 0 Output'           },
    { name: 15	, displayName: 'LUT 1 Output'           },
    { name: 23	, displayName: 'LUT 2 Output'           },
    { name: 6	, displayName: 'FSM 0 Output'           },
    { name: 4	, displayName: 'FSM 0 State 0 Value'    },
    { name: 5	, displayName: 'FSM 0 State 1 Value'    },
    { name: 14	, displayName: 'FSM 1 Output'           },
    { name: 12	, displayName: 'FSM 1 State 0 Value'    },
    { name: 13	, displayName: 'FSM 1 State 1 Value'    },
    { name: 22	, displayName: 'FSM 2 Output'           },
    { name: 20	, displayName: 'FSM 2 State 0 Value'    },
    { name: 21	, displayName: 'FSM 2 State 1 Value'    },
    { name: 2	, displayName: 'Counter 0 Equals Zero'   },
    { name: 3	, displayName: 'Counter 0 Equals Match 1' },
    { name: 1	, displayName: 'Counter 0 Equals Match 2' },
    { name: 10	, displayName: 'Counter 1 Equals Zero'   },
    { name: 11	, displayName: 'Counter 1 Equals Match 1' },
    { name: 9	, displayName: 'Counter 1 Equals Match 2' },
    { name: 18	, displayName: 'Counter 2 Equals Zero'   },
    { name: 19	, displayName: 'Counter 2 Equals Match 1' },
    { name: 1	, displayName: 'Counter 2 Equals Match 2' }],
};

function isSimulatedInput(name) {
    return name == 'squareWave';
}

function colonName(name)
{
    return name.replace('.',':');
}

/*!
 *  ======== getInstanceIndex ========
 *  returns module.$instances array index of this inst
 */
function getInstanceIndex(inst)
{
    let instances = inst.$module.$instances;
    for (let i = 0; i < instances.length; i++) {
        if (inst == instances[i]) return (i);
    }
    return (-1);
}

/*
/*
 *  ======== isCName ========
 *  Determine if specified id is either empty or a valid C identifier
 *
 *  @param id  - String that may/may not be a valid C identifier
 *
 *  @returns true if id is a valid C identifier OR is the empty
 *           string; otherwise false.
 */
function isCName(id)
{
    if ((id != null && id.match(/^[a-zA-Z_][0-9a-zA-Z_]*$/) != null)
            || id == '') { /* '' is a special value that means "default" */
        return true;
    }
    return false;
}

/*
 *  ======== logError ========
 *  Log a new error
 *
 *  @param vo     - validation object associated with inst
 *  @param inst   - module instance object
 *  @param field  - instance property name with which this error is associated
 */
function logError(vo, inst, field, msg)
{
    if (typeof(field) === 'string') {
        vo[field].errors.push(msg);
    }
    else {
        for (let i = 0; i < field.length; i++) {
            vo[field[i]].errors.push(msg);
        }
    }
}

/*
 *  ======== logInfo ========
 *  Log a new remark
 *
 *  @param vo     - validation object associated with inst
 *  @param inst   - module instance object
 *  @param field  - instance property name with which this remark is associated
 */
function logInfo(vo, inst, field, msg)
{
    if (typeof(field) === 'string') {
        vo[field].infos.push(msg);
    }
    else {
        for (let i = 0; i < field.length; i++) {
            vo[field[i]].infos.push(msg);
        }
    }
}

/*
 *  ======== logWarning ========
 *  Log a new warning
 *
 *  @param vo     - validation object associated with inst
 *  @param inst   - module instance object
 *  @param field  - instance prop name with which this warning is associated
 */
function logWarning(vo, inst, field, msg)
{
    if (typeof(field) === 'string') {
        vo[field].warnings.push(msg);
    }
    else {
        for (let i = 0; i < field.length; i++) {
            vo[field[i]].warnings.push(msg);
        }
    }
}

/*
 *  ======== print ========
 *  Print specified obj
 */
function print(obj, header, depth, indent)
{
    if (indent == null) indent = "";
    if (header == null) header = "";
    if (depth == null) depth = 4;
    if (indent.length > 2 * depth) return;

    if (obj == null) {
        console.log(header + (obj === null ? "null" : "undefined"));
        return;
    }
    if (indent == "") {
        if (obj.$name != null) {
            console.log(header + obj.$name + ":");
        }
        else {
            console.log(header + obj + " (nameless):");
        }
    }

    for (let p in obj) {
        /* print the enumerable properties of obj and their value */
        let line = indent + "  " + p + ": ";

        let value = obj[p];

        let fxn = null;
        if (typeof value == "function") {
            try {
                fxn = String(value).match(/.*\n/);
            } catch (x){/* ignore any exception */}
        }
        if (fxn != null) {
            /* only print declaration of functions (not their entire source) */
            console.log(line + fxn);
        }
        else if (value != null && (typeof value == "object")) {
            console.log(line
                + (("$name" in value) ? (" (" + value.$name + ")") : ""));

            if (p[0] != '$') {
                /* recursively print (non-tool) object properties */
                print(value, "", depth, indent + "  ");
            }
        }
        else {
            /* print non-object values */
            console.log(line + value);
        }
    }
}

/*
 *  ======== validateNames ========
 *  Validate that all names defined by inst are globally unique and
 *  valid C identifiers.
 */
function validateNames(inst, validation)
{
    let myNames = {}; /* all C identifiers defined by inst) */

    /* check that $name is a C identifier */
    if (inst.$name != "") {
        let token = inst.$name;
        if (!isCName(token)) {
            logError(validation, inst, "$name",
                "'" + token + "' is not a valid a C identifier");
        }
        myNames[token] = 1;
    }

    /* check that cAliases are all C identifiers and there are no dups */
    let tokens = [];
    if ("cAliases" in inst && inst.cAliases != "") {
        tokens = inst.cAliases.split(/[,;\s]+/);
    }

    for (let i = 0; i < tokens.length; i++) {
        let token = tokens[i];
        if (!isCName(token)) {
            logError(validation, inst, "cAliases",
                "'" + token + "' is not a valid a C identifier");
        }
        if (myNames[token] != null) {
            logError(validation, inst, "cAliases",
                "'" + token + "' is defined twice");
        }
        myNames[token] = 1;
    }

    /* ensure all inst C identifiers are globally unique */
    let mods = system.modules;
    for (let i in mods) {
        /* for all instances in all modules in /ti/drivers ... */
        let instances = mods[i].$instances;
        for (let j = 0; j < instances.length; j++) {
            let other = instances[j];

            /* skip self */
            if (inst.$name == other.$name) {
                continue;
            }

            /* compute all other names */
            let name = other.$name;
            if (name != "" && name in myNames) {
                logError(validation, inst, "cAliases",
                    "multiple instances with the same name: '"
                         + name + "': " + inst.$name + " and " + other.$name);
                break;
            }
            if (other.cAliases != null && other.cAliases != "") {
                let tokens = other.cAliases.split(/[,;\s]+/);
                for (let k = 0; k < tokens.length; k++) {
                    name = tokens[k];
                    if (name != "" && name in myNames) {
                        logError(validation, inst, "cAliases",
                            "multiple instances with the same name: '" + name
                                 + "': " + inst.$name + " and " + other.$name);
                        break;
                    }
                }
            }
        }
    }
}

//-------------------------------------------------------------------------
// Is this instance used. Used is defined by any input being connected.
//-------------------------------------------------------------------------
function used(inst, inputs)
{
    for (let j = 0; j < inputs.length; ++j) {
        if (inst[inputs[j]] != '0') { return true; }
    }
    return false;
}

//-------------------------------------------------------------------------
function extract_bit(val, pos) {
    return (val >> pos) & 1;
}

//-------------------------------------------------------------------------
function OUTLUT_truth_table(expr) {
    let tt = 0;
    for (let i=7; i >= 0; i--) {
        let i2 = extract_bit(i,2);
        let i1 = extract_bit(i,1);
        let i0 = extract_bit(i,0);
        tt = (tt << 1) | (eval(expr) & 0x1);
    }
    return '0x' + tt.toString(16);
}

//-------------------------------------------------------------------------
function LUT_truth_table(expr) {
    let tt = 0;
    for (let i=15; i >= 0; i--) {
        let i3 = extract_bit(i,3);
        let i2 = extract_bit(i,2);
        let i1 = extract_bit(i,1);
        let i0 = extract_bit(i,0);
        tt = (tt << 1) | (eval(expr) & 0x1);
    }
    return '0x' + tt.toString(16);
}

//-------------------------------------------------------------------------
function FSM_truth_table(expr) {
    let tt = 0;
    for (let i=15; i >= 0; i--) {
        let e1 = extract_bit(i,3);
        let e0 = extract_bit(i,2);
        let s1 = extract_bit(i,1);
        let s0 = extract_bit(i,0);
        let xe1 = extract_bit(i,1);
        let xe0 = extract_bit(i,0);
 
        tt = (tt << 1) | (eval(expr) & 0x1);
    }
    return '0x' + tt.toString(16);
}

//-------------------------------------------------------------------------
function which_instance(inst) {
    let instType   = inst.$module.displayName;
    let owningTile = inst.$ownedBy;

    for (let i=0; i < 8; i++) {
        if (owningTile[instType+'_'+i] == inst) { return (i); }
    }
}

//-------------------------------------------------------------------------
function sigName(outName, tileName) {
    let outPort = tileName + "_" + outName;

    if (outName == '0') return 'sc_zero';
    if (outName == '1') return 'sc_one';
    return 'sig_' + outPort.replace('.','_');
}

//-------------------------------------------------------------------------
function getDeviceName()
{
	var deviceName = system.deviceData.device;
	return deviceName
}

function isType0() {
    return ["F2807x", "F2837xS", "F2837xD"].includes(getDeviceName());
}

function isType1() {
    return ["F28004x"].includes(getDeviceName());
}

function isType2() {
    return ["F28002x", "F2838x", "F28003x", "F28P65x", "F28P55x", "F28P551x"].includes(getDeviceName());
}

function isType0_Type1(){
    return (isType0() | isType1());
}

function isType1_Type2(){
    return (isType1() | isType2());
}


function printDebugObject(obj)
{
	if (obj == null)
	{
		console.log("Object is null");
		return;
	}
    var keys = Object.keys(obj);
    for (var key in keys)
	{
    	console.log(keys[key] + " : " + obj[keys[key]]);
    }
}