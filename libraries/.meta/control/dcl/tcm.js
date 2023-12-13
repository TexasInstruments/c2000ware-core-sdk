let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let references = system.getScript("/libraries/C2000WARELibraryReferences.js");
let tcm_data = system.getScript("/libraries/control/dcl/tcm_data.js");

let config = [
    {
        name:"fdlogName",
        hidden:false,
        default:"",
        displayName:"Re-Name FDLOG Structure",
        description:"Name of the FDLOG structure for the logger, default name provided if left blank",
        longDescription:"Name of the data array for the logger, default name provided if left blank"
    },
    {
        name:"arrName",
        hidden:false,
        default:"",
        displayName:"Re-Name Data Array",
        description:"Name of the data array for the logger, default name provided if left blank",
        longDescription:"Name of the data array for the logger, default name provided if left blank. If the array already exists in memory, this will be used to point to that array."
    },
    {
        name:"arrEn",
        hidden:false,
        default:true,
        displayName:"Create Array Object",
        description:"Create the array object, for cases where the array does not already exist.",
        longDescription:"Create the array object, for cases where the array does not already exist. NOTE: if this is unchecked the array must exist somewhere in the code, otherwise a compile error will occur."
    },
    {
        name:"linkerEn",
        hidden:false,
        default:false,
        displayName:"Enable Linker Location",
        description:"Linker command file used for declaring the array directly",
        longDescription:"This creates a pragma to point to the given location in memory",
        onChange:(inst, ui) => {ui["linkerVal"].hidden=!inst["linkerEn"];}
    },
    {
        name:"linkerVal",
        hidden:true,
        default:"",
        displayName:"Re-Name Linker Pragma",
        description:"Pragma name of the location of the array in the linker command file, default name provided if left blank",
        longDescription:"Pragma name of the location of the array in the linker command file, default name provided if left blank"
    },
    {
        name:"lead",
        hidden:false,
        default:100,
        displayName:"Lead Frame Size",
        description:"Amount of data samples to save ahead of the trigger point, in 32-bit words",
        longDescription:"Amount of data samples to save ahead of the trigger point, in 32-bit words.\nTrigger crossing index."
    },
    {
        name:"captSize",
        hidden:false,
        default:300,
        displayName:"Capture Frame Size",
        description:"Amount of data samples to save after the lead frame is captured, in 32-bit words",
        longDescription:"Amount of data samples to save after the lead frame is captured, in 32-bit words"
    },
    {
        name:"totSize",
        hidden:false,
        default:0,
        displayName:"Calculated Total Size",
        description:"Total number of samples of the lead frame and capture frame together.",
        longDescription:"Total number of samples of the lead frame and capture frame together.",
        getValue: (inst) => {return inst["lead"]+inst["captSize"];}
    },
    {
        name:"trigMax",
        hidden:false,
        default:"0",
        displayName:"Upper Trigger Threshold",
        description:"Upper trigger threshold",
        longDescription:"Upper trigger threshold. Can include variable names."
    },
    {
        name:"trigMin",
        hidden:false,
        default:"0",
        displayName:"Lower Trigger Threshold",
        description:"Lower trigger threshold",
        longDescription:"Lower trigger threshold. Can include variable names."
    },
    {
        name:"armTCM",
        hidden:false,
        default:false,
        displayName:"Arm TCM During Init",
        description:"Arm the TCM module so it is ready to capture immediately upon initialization",
        longDescription:"Arm the TCM module so it is ready to capture immediately upon initialization"
    },
]

function onValidate(inst, validation){
    // TCM only has FPU32 support, which is compatible with both FPU32 and FPU64, so no checks needed
}

let longDescription = `The Transient Capture Module (TCM) is a triggered data logger which captures a burst of
incoming data. A typical use is the capture of a transient response following a step input
to a control system. The trigger conditions are a pair of user defined limits on the
incoming data. The capture process is triggered by the first data point which exceeds
either limit.

A feature of the TCM is that it captures a programmable length lead frame, allowing the
user to inspect conditions immediately prior to the trigger condition. This is accomplished
with three FDLOG structures which are elements in the TCM data structure, together with
the limit pair.

Once initialized, the status of the TCM is captured in one of four
enumerated operating modes:
* TCM_idle
* TCM_armed
* TCM_capture
* TCM_complete

The current mode is available in the mode element in the TCM structure. To use the
TCM, the user must do the following in their code:
1. Arm the TCM using DCL_armTCM()
2. Log data into the TCM using DCL_runTCM()
3. Monitor the mode element in the TCM structure to determine when the capture is complete.

In the following diagrams, lead, capture, and monitor frames are indexed using the
FDLOG structures x, y, & z respectively (note that these are not the names used in the
TCM structure). FDLOG pointers are color coded blue, green, and red, respectively. To
help visualize the sequence of events, the diagram shows in light gray the data which will
eventually be logged into the TCM, and in blue the current frame contents in each mode.


## ***TCM_idle Mode***

In TCM_idle mode the TCM buffers are as shown below. All buffer contents are zero, all
frame data pointers are at the start of their respective frames and no data is being logged.
This is the condition after the DCL_initTCM() function has been called.

*Figure: TCM operation in TCM_idle mode*

![](../../libraries/.meta/control/dcl/images/figures_scaled/TCM_operation_in_TCM_idle_mode.png)

## ***TCM_armed Mode***

The TCM is armed by a call to DCL_armTCM(). In this mode, incoming data is
continually logged in the monitor frame. The monitor frame acts as a circular buffer, the
index pointer wrapping to the start of the monitor frame when it reaches the end.

Each data point is compared with the upper and lower trigger thresholds to determine
whether to initiate a capture sequence. As long as the incoming data remains within the
specified limits, the TCM remains in TCM_armed mode.

*Figure: TCM operation in TCM_armed mode*

![](../../libraries/.meta/control/dcl/images/figures_scaled/TCM_operation_in_TCM_armed_mode.png)

## ***TCM_capture Mode***

The first data point which exceeds either trigger threshold initiates a capture sequence.
The TCM automatically enters TCM_capture mode and incoming data is logged into the
capture frame. Meanwhile, the monitor frame stops collecting data and starts to un-wind
its contents into the lead frame. Notice that the monitor frame contains the lead data
sequence, but the starting point is not aligned with the frame.

*Figure: TCM operation in capture mode (monitor frame un-winding)*

![](../../libraries/.meta/control/dcl/images/figures_scaled/TCM_operation_in_capture_mode_monitor_frame_un-winding.png)

Once the lead frame is full, the monitor frame stops copying out its data. Incoming data
continues being logged into the capture frame until it is full. The monitor frame contents
have now been completely loaded into the lead frame and will be over-written.

*Figure: TCM operation in TCM_capture mode (lead frame complete)*

![](../../libraries/.meta/control/dcl/images/figures_scaled/TCM_operation_in_TCM_capture_mode_lead_frame_complete.png)

## ***TCM_complete Mode***

Once the capture frame is full, data logging stops and the TCM enters TCM_complete
mode. The capture frame pointers are adjusted to span the entire TCM buffer.

*Figure: TCM capture complete*

![](../../libraries/.meta/control/dcl/images/figures_scaled/TCM_capture_complete.png)

The buffer contents may now be read out using DCL_readLog() or DCL_freadLog().

See the DCL User's Guide for more details:

[Digital Control Library User's Guide](https://dev.ti.com/tirex/explore/node?node=AKZRbh4oxv98HaO0YKjygQ__gYkahfz__LATEST)`

var sfoModule = {
    c2000wareLibraryName: "TCM",
    displayName: "TCM",
    defaultInstanceName: "myTCM",
    description: "Transient Capture Module",
    longDescription: longDescription,
    config: config,
    validate:onValidate,
    references : [],
    templates: {
        c2000ware_libraries_c           : "/libraries/control/dcl/templates/tcm.c2000ware_libraries.c.xdt",
        c2000ware_libraries_h           : "/libraries/control/dcl/templates/tcm.c2000ware_libraries.h.xdt",
    },
    modules: (inst) => {
        var mods = [];
        var refFilesArr = tcm_data.getRefFilesModuleArrFromControlStruct("TCM");
        mods = refFilesArr;
        return mods;
    },
};

exports = sfoModule;