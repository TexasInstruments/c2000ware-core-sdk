let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let references = system.getScript("/libraries/C2000WARELibraryReferences.js");
let refgen_data = system.getScript("/libraries/control/dcl/refgen_data.js");

// decide whether to show duty cycle option
function onChangeMode(inst, ui)
{
    // hide the duty cycle option if not using PULSE type
    if (inst.mode == "PULSE")   {ui.duty.hidden = false;}
    else                        {ui.duty.hidden = true; }
}

function onValidate(inst, validation) {
    //**********************************************************************
    // general checks
    //**********************************************************************
    // make sure name is not ref, which is a keyword but probably would be common mistake
    if (inst.$name == "ref")
    {
        validation.logWarning(
            "\"ref\" is a keyword and should not be used for the name of the reference generator.",
            inst, "refgenPrecision");
    }
    // // make sure nothing is empty
    // for(var e of inst)
    // {
    //     if(inst[e].length<=0)
    //     {
    //         validation.logError("A value must be provided.", inst, e);
    //     }
    // }

    //**********************************************************************
    // hard coded checks for specific parameters
    //**********************************************************************
    // ensure duty cycle between 0 and 1
    var val = inst["duty"];
    if (val<0 || val>1)
    {
        validation.logError(
            "Value must be between 0 and 1.",
            inst, 
            "duty"
        );
    }
    // ensure min is less than max
    if (inst["umax"] < inst["umin"])
    {
        validation.logError(
            "Max must be greater than or equal to min.",
            inst, 
            "umax"
        );
    }

    // only do this check if one of the floating point precisions are chosen
    if (inst.refgenPrecision == "F32" || inst.refgenPrecision == "F64") {
        // check if refgenPrecision matches the precision being used by FPU.js in the "Other Dependencies" section
        var fpuMod = system.modules["/libraries/math/FPU/FPU.js"];
        if(fpuMod)
        {
            if(fpuMod.$static.fpuType.replace("PU","") != inst.refgenPrecision)
            {
                // when controller precision == F64, and the FPU.js file has FPU32 chosen, then warn the user that performance loss will occur
                if (inst.refgenPrecision == "F64" && fpuMod.$static.fpuType == "FPU32") {
                    // for devices that can actually support F64, tell user that they can fix the issue
                    let fpu_obj = system.getScript("/libraries/.meta/math/FPU/FPU.js").moduleStatic.config;
                    var fpu_types = fpu_obj.filter(fpu_or_tmu_list => fpu_or_tmu_list.name === "fpuType")[0].options;
                    var fpu64_supported = false;
                    if (fpu_types.length >= 2) {
                        // 2 options available means that both FPU32 (all Sysconfig devices) and FPU64 (some Sysconfig devices) are supported
                        fpu64_supported = true;
                    }
                    if (fpu64_supported)
                    {
                        validation.logWarning("Double-precision data type chosen with single-precision floating-point processor chosen. Relatively poor cycle performance should be expected. To improve performance, precision can be updated here or in 'Other Dependencies' below.", inst, "refgenPrecision");
                    }
                    // for devices that can't support F64, tell the user that performance loss should be expected
                    else
                    {
                        validation.logWarning("Double-precision data type chosen with single-precision floating-point processor chosen. Relatively poor cycle performance should be expected.", inst, "refgenPrecision");
                    }
                }
                else
                {
                    // when controller precision == F32, and the FPU.js file has FPU64 chosen, there should be no issue as FPU64 is backwards compatible with FPU32 instructions and C code
                }
            }
        }
    }
}

let config = [
    {
        name        : "refgenPrecision",
        displayName : "Precision",
        description : 'Choice of Precision.',
        hidden      : false,
        default     : "F32",
        options     : [{name:"F32",displayName:"Floating-Point (32-bit)"},{name:"F64",displayName:"Floating-Point (64-bit)"}],
    },
    {
        name        : "structDisplay",
        displayName : "Refgen Structure Chosen",
        description : 'Visualization of the chosen DCL structure.',
        hidden      : false,
        getValue    : (inst) => {
            // return REFGEN if 32-bit, REFGEN64 if 64-bit
            return ((inst.refgenPrecision == "F32") ? "REFGEN" : "REFGEN64" );
        },
        default     : "REFGEN"
    },
    {name:"mode",       hidden:false, default:"SINE",   displayName:"Operating Mode",               description:"Operating mode", onChange:onChangeMode, options:[{name:"OFF",displayName:"OFF"},{name:"STATIC",displayName:"STATIC"},{name:"SINE",displayName:"SINE"},{name:"SQUARE",displayName:"SQUARE"},{name:"SAW",displayName:"SAW"},{name:"TRIANGLE",displayName:"TRIANGLE"},{name:"PULSE",displayName:"PULSE"},{name:"SINE2",displayName:"SINE2"},{name:"SINE3",displayName:"SINE3"}]},
    {name:"sampPer",    hidden:false, default:0.00001,  displayName:"Sample Period (s)",            description:"Sample period in seconds, rate at which DCL_runRefgen* is called", longDescription: "Typically DCL_runRefgen* and DCL_getRefgenPhase* functions would be called in an interrupt service routine to ensure they are executed at a deterministic rate. This value should match the ISR frequency."},
    {
        name        : "signalPropertiesGroup",
        displayName : "Signal Properties",
        description : 'Reference signal settings',
        collapsed   : false,
        config      : [
            {name:"duty",       hidden:true,  default:0.5,      displayName:"Duty Cycle",                   description:"Per-unit duty cycle value of the signal"},        
            {name:"freq",       hidden:false, default:7700,     displayName:"Frequency (Hz)",               description:"Signal frequency in Hz"},
            {name:"freqTr",     hidden:false, default:0,        displayName:"Frequency Change Time",        description:"Transition time (s) to reach the new frequency"},
            {name:"ampl",       hidden:false, default:1,        displayName:"Amplitude",                    description:"Signal amplitude - half of peak-to-peak if sine, peak-to-peak if other types"},
            {name:"amplTr",     hidden:false, default:0,        displayName:"Amplitude Change Time",        description:"Transition time (s) to reach the new amplitude"},
            {name:"offs",       hidden:false, default:1,        displayName:"Static Offset",                description:"Value above or below zero that the generated signal will be referenced to"},
            {name:"offsTr",     hidden:false, default:0,        displayName:"Offset Change Time",           description:"Transition time (s) to reach the new offset"},
            {name:"umax",       hidden:false, default:2,        displayName:"Maximum Signal Value",         description:"Maximum allowable output"},
            {name:"umin",       hidden:false, default:0,        displayName:"Minimum Signal Value",         description:"Minimum allowable output"},
        ]
    },
]

var longDescription = `# ***DCL Reference Generator***
See the DCL Reference Generator User's Guide for more details:

[DCL Reference Generator User's Guide](https://dev.ti.com/tirex/explore/node?node=APmkmKXTQzc2tUCl049v4A__gYkahfz__LATEST)

The DCL reference generator module is capable of producing up to three channels each made up of a dynamic waveform superimposed on a common static offset. Dynamic waveforms include a single phase sine, square, saw-tooth, triangular, or pulse output; and two or three phase sine waves.

The reference generator consists of five sub-modules: a static offset generator, a three phase waveform generator, a frequency modulator, an amplitude modulator, and an output clamp. The relationship between these sub-modules is set out below.

Figure: Reference generator architecture



![](../../libraries/.meta/control/dcl/images/figures_scaled/REFGEN_Reference_generator_architecture-Figure1.png)



## ***Static Offset Generator***

The static offset generator produces an adjustable offset onto which the dynamic component of the outputs is superimposed. The transition between two offsets is achieved using a linear ramp, the duration of which can be determined by the user.

The ramp is implemented by adding an increment to the offset each time the reference generator is run, the increment being computed when the ramp is loaded. In the floating point numerical format, resolution is lost as the size of the number increases, so adding a small number to a much larger number can result in the larger number not changing. For this reason there is an upper limit to the ramp transition time and a lower limit to the offset change which can be achieved. It is recommended that the reference generator module be used to generate outputs in the range ±1. This allows the computed ramp increment is checked against a lower limit (defined near the top of DCL_refgen.h) which is known to maintain accumulation up to the maximum accumulator value.

The function DCL_setRefgenRamp() allows the user to change both the static level and the transition time between level changes. When the user specifies a new target level, the generator outputs a linear ramp between the new and old levels in the specified time interval. Figure 2 shows an example of a static level change taking place over a specific time interval (tr).

Figure: Static level ramp

The ramp interval is programmable in units of seconds, and the function uses the generator update rate held in the CSS sub-structure to compute the incremental change in level on each update during the adjustment interval. For this reason, the update rate must be loaded into the CSS sub-structure before the level change function is called. To force an immediate (step) change to a new offset level, the ramp interval should be set to zero.

![](../../libraries/.meta/control/dcl/images/figures_scaled/REFGEN_Static_level_ramp-Figure2.png)




## ***Waveform Generator***

The waveform generator produces the dynamic component of the reference (sine waves, square waves, and so on). The frequency of the dynamic component is determined by two factors: the frequency of the desired waveform, and the update rate of the generator. Each time the DCL_runRefgen() function is called, the REFGEN generator determines a normalized angle from which the next waveform point is computed. This is done by adding a fixed angular increment to the angle variable. The increment is computed in the DCL_setRefgenFreq() function. At very low frequencies or very high update rates, the increment may violate the smallest allowable value defined in DCL_REFGEN_MIN_INC. In this case, if error handling is enabled an error will be generated, or if error handling is disabled the angle increment will be clamped to DCL_REFGEN_MIN_INC. The maximum recommended frequency of the generated waveform is one quarter of the update rate.

Prior to using the waveform generator, the user must load the correct update period into the CSS sub-structure before calling any of the REFGEN functions. This can be done using the DCL_SET_SAMPLE_RATE macro (see the example code in the function descriptions section).

The waveform generator produces three outputs denoted phase A, phase B, and phase C. The generator can produce the following waveforms.
* sinusoidal
* square
* saw-tooth
* triangular
* pulse
* 2 phase sine
* 3 phase sine

The waveform type is selected by the DCL_setRefgenMode() function which takes as an argument an enumerated 16-bit integer denoting the mode. In all cases, the frequency and amplitude of the waveforms are freely adjustable by the user.

On TMU equipped devices, sinusoidal waveform generation modes make use of TMU C intrinsics to accelerate the run function. Devices which do not have a TMU must use RTS library support functions so will execute more slowly. None of the waveforms use look-up tables so the data memory footprint of the REFGEN module is very small.

The table below shows the operating modes available in the reference generator. The mode number is in the leftmost column and the enumerated mode name in the second column from the left. Double precision modes have a '64' appended to the 'REFGEN', for example 'REFGEN64_STATIC'.

No | Mode Name       | Type               | Phase A   | Phase B       | Phase C
---|-----------------|--------------------|-----------|---------------|----------------
0  | REFGEN_OFF      | No output          | 0         | 0             | 0
1  | REFGEN_STATIC   | Static offset only | Static    | Static        | Static
2  | REFGEN_SINE     | Sine wave          | Sine      | Static        | Static
3  | REFGEN_SQUARE   | Square wave        | Square    | Static        | Static
4  | REFGEN_SAW      | Saw tooth wave     | Saw tooth | Static        | Static
5  | REFGEN_TRIANGLE | Triangle wave      | Triangle  | Static        | Static
6  | REFGEN_PULSE    | Pulsed wave        | Pulse     | Static        | Static
7  | REFGEN_SINE2    | 2 phase sine wave  | Sine      | Cosine        | Static
8  | REFGEN_SINE3    | 3 phase sine wave  | Sine      | 120 deg. sine | 240 deg. sine

The same amplitude adjustment is applied to all phases prior to their addition to the static offset. Amplitude adjustment is made using the DCL_setRefgenAmpl() function.



### ***OFF Mode***
In this mode all three outputs are forced to zero. This is the default mode.

### ***STATIC Mode***
In this mode all outputs are controlled by the static reference generator only. The waveform generator is not used.

### ***SINE Mode***
In this mode phase A is a sinewave of configurable frequency and amplitude, while phases B & C are static outputs.

*Figure: Sine wave mode*

![](../../libraries/.meta/control/dcl/images/figures_scaled/REFGEN_Sine_wave_mode-Figure3.png)


### ***SQUARE Mode***
In this mode phase A is a square wave of configurable frequency and amplitude, superimposed on the static generator output. Phases B & C are static outputs.

*Figure: Square wave mode*

![](../../libraries/.meta/control/dcl/images/figures_scaled/REFGEN_Square_wave_mode-Figure4.png)


### ***SAW Mode***
In this mode phase A is a saw-tooth wave of configurable frequency and amplitude superimposed on the output of the static generator. Phases B & C are static outputs. The saw-tooth output is zero when the angle is zero, and rises to the amplitude when the angle is 1.

*Figure: Saw tooth mode*

![](../../libraries/.meta/control/dcl/images/figures_scaled/REFGEN_Saw_tooth_mode-Figure5.png)


### ***TRIANGLE Mode***
In this mode phase A is a triangle wave of configurable frequency and amplitude superimposed on the output of the static generator. Phases B & C are static outputs. The saw-tooth output is zero when the angle is zero, and increases linearly to the commanded amplitude when the angle is 0.5.

*Figure: Triangle mode*

![](../../libraries/.meta/control/dcl/images/figures_scaled/REFGEN_Triangle_mode-Figure6.png)


### ***PULSE Mode***
In this mode phase A is a pulsed wave of configurable frequency and amplitude superimposed on the output of the static generator. Phases B & C are static outputs. The pulse width is controlled by the duty cycle setting in the DCL_REFGEN structure, which may be set using the DCL_setRefgenDuty() function. The pulse output is one when the angle is below the normalized duty cycle, and zero when the angle is greater than the normalized duty cycle value.

*Figure: Pulse mode*

![](../../libraries/.meta/control/dcl/images/figures_scaled/REFGEN_Pulse_mode-Figure7.png)


### ***SINE2 Mode***
In this mode, phases A & B are two sine waves of similar frequency and amplitude superimposed on the static reference generator output. The phases are separated by 90 degrees, so that the outputs form a sine/cosine pair. Phase C is the static generator output.

*Figure: 2-phase sine mode*

![](../../libraries/.meta/control/dcl/images/figures_scaled/REFGEN_2-phase_sine_mode-Figure8.png)


### ***SINE3 Mode***
In this mode, the three output phases are sine waves of similar frequency and amplitude superimposed on the static reference generator output. The angular separation of the phases is 120 degrees.

*Figure: 3-phase sine mode*

![](../../libraries/.meta/control/dcl/images/figures_scaled/REFGEN_3-phase_sine_mode-Figure9.png)

# ***Amplitude Modulation***
Amplitude modulation is implemented in a similar fashion to frequency modulation. The transition interval is the last argument in the function DCL_setRefgenAmpl(). Similarly, an attempt to force large transition time together with a small amplitude change will result in either an error or the minimum increment being adopted, according to whether error handling is enabled.

# ***Output Clamp***
All three reference outputs are clamped to the same upper and lower limits. Limits are loaded by the user using the DCL_setRefgenClamp() function with the only restriction that the upper limit be equal to or greater than the lower limit.

`
var refgenModule = {
    c2000wareLibraryName: "REFGEN",
    displayName: "REFGEN",
    defaultInstanceName: "myREFGEN",
    description: "REFGEN",
    longDescription:longDescription,
    config: config,
    references : [],
    templates: {
        c2000ware_libraries_c           : "/libraries/control/dcl/templates/refgen.c2000ware_libraries.c.xdt",
        c2000ware_libraries_h           : "/libraries/control/dcl/templates/refgen.c2000ware_libraries.h.xdt",
    },
    validate : onValidate,
    modules: (inst) => {
        var mods = [];
        var refFilesArr = refgen_data.getRefFilesModuleArrFromControlStruct(inst.structDisplay);
        mods = refFilesArr;
        return mods;
    }
};

exports = refgenModule;