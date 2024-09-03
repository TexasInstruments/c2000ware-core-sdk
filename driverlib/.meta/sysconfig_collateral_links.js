exports = {
    getCollateralData : getCollateralData,
};

function getCollateralData()
{
    return collateral;
}

var collateral = {
    "ADC":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"ADC Input Circuit Evaluation for C2000 MCUs (TINA-TI) Application Report",
                    url:"https://ti.com/lit/SPRACT6",
                    appNote:true,
                },
                {
                    name:"C2000 Academy - ADC",
                    url:"https://dev.ti.com/tirex/local?id=source_c2000_analog_subsystem_c2000_analog_to_digital_converter&amp;packageId=C2000-ACADEMY",
                    devices:[
                        "F280013x",
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                },
                {
                    name:"PSpice for TI design and simulation tool",
                    url:"https://www.ti.com/tool/PSPICE-FOR-TI",
                },
                {
                    name:"Real-Time Control Reference Guide",
                    url:"https://www.ti.com/lit/eb/slyy211/slyy211.pdf",
                    description:"Refer to the ADC section",
                },
                {
                    name:"TI Precision Labs - ADCs",
                    url:"https://www.ti.com/tool/TINA-TI",
                },
                {
                    name:"TI Precision Labs: Driving the reference input on a SAR ADC",
                    url:"https://www.ti.com/video/5783793652001",
                    video:true,
                },
                {
                    name:"TI Precision Labs: Introduction to analog-to-digital converters (ADCs)",
                    url:"https://www.ti.com/video/6163538486001",
                    video:true,
                },
                {
                    name:"TI Precision Labs: SAR ADC input driver design",
                    url:"https://www.ti.com/video/5476574757001",
                    video:true,
                },
                {
                    name:"TI e2e: Connecting VDDA to VREFHI ",
                    url:"https://e2e.ti.com/support/microcontrollers/c2000-microcontrollers-group/c2000/f/c2000-microcontrollers-forum/967811/tms320f28388d-connecting-both-vdda-and-vrefhi-to-3-3v/3575387?tisearch=e2e-sitesearch&amp;keymatch=ADC%252520VREFHI%252520driver#3575387",
                },
                {
                    name:"TI e2e: Topologies for ADC Input Protection",
                    url:"https://e2e.ti.com/support/microcontrollers/c2000-microcontrollers-group/c2000/f/c2000-microcontrollers-forum/1065493/tms320f280049-q1-opamp-powered-by-5v-to-buffer-gpio",
                },
                {
                    name:"TI e2e: Why does the ADC Input Voltage drop with sampling?",
                    url:"https://e2e.ti.com/support/microcontrollers/c2000-microcontrollers-group/c2000/f/c2000-microcontrollers-forum/1024667/tms320f280049c-why-does-the-adc-input-voltage-drop-with-sampling/3787995?tisearch=e2e-sitesearch&amp;keymatch=ADC%25252525252520voltage%25252525252520divider#3787995",
                    description:"Sampling a high impedance voltage divider with ADC",
                },
                {
                    name:"Understanding Data Converters Application Report",
                    url:"https://www.ti.com/lit/SLAA013",
                    appNote:true,
                },
            ]
        },
        {
            category_displayName: "Getting Started Materials",
            content:[
                {
                    name:"ADC-PWM Synchronization Using ADC Interrupt",
                    url:"https://www.mathworks.com/help/supportpkg/texasinstrumentsc2000/ug/adc-pwm-synchronization-via-adc-interrupt.html",
                    description:"NOTE: This is a non-TI (third party) site.",
                },
                {
                    name:"Analog-to-Digital Converter (ADC) Training for C2000 MCUs",
                    url:"https://www.ti.com/video/series/C2000-analog-to-digital-converter.html",
                    devices:[
                        "F280013x",
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2837x",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                    video:true,
                },
                {
                    name:"C2000 ADC (Type-3) Performance Versus ACQPS Application Report",
                    url:"https://ti.com/lit/SPRACP5",
                    devices:[
                        "LEGACY",
                    ],
                    appNote:true,
                },
                {
                    name:"Hardware Design Guide for F2800x C2000 Real-Time MCU Series",
                    url:"https://www.ti.com/lit/spracz9",
                },
                {
                    name:"Interfacing the ADS8364 to the TMS320F2812 DSP Application Report",
                    url:"https://ti.com/lit/SLAA163",
                    devices:[
                        "LEGACY",
                    ],
                    appNote:true,
                },
            ]
        },
        {
            category_displayName: "Expert Materials",
            content:[
                {
                    name:"An Overview of Designing Analog Interface With TM320F28xx/28xxx DSCs Application Report",
                    url:"https://ti.com/lit/SPRAAP6",
                    devices:[
                        "LEGACY",
                    ],
                    appNote:true,
                },
                {
                    name:"Analog Engineer\u0027s Calculator",
                    url:"https://www.ti.com/tool/ANALOG-ENGINEER-CALC",
                },
                {
                    name:"Analog Engineer\u0027s Pocket Reference",
                    url:"https://www.ti.com/seclit/eb/slyw038c/slyw038c.pdf",
                },
                {
                    name:"Charge-Sharing Driving Circuits for C2000 ADCs (using PSPICE-FOR-TI) Application Report",
                    url:"https://ti.com/lit/SPRACZ0",
                    devices:[
                        "F280013x",
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                    appNote:true,
                },
                {
                    name:"Charge-Sharing Driving Circuits for C2000 ADCs (using TINA-TI) Application Report",
                    url:"https://ti.com/lit/SPRACV0",
                    devices:[
                        "F280013x",
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                    appNote:true,
                },
                {
                    name:"Debugging an integrated ADC in a microcontroller using an oscilloscope",
                    url:"https://e2e.ti.com/blogs_/b/analogwire/archive/2017/08/17/debugging-an-integrated-adc-in-a-microcontroller-using-an-oscilloscope",
                },
                {
                    name:"Methods for Mitigating ADC Memory Cross-Talk Application Report",
                    url:"https://ti.com/lit/SPRACW9",
                    devices:[
                        "F280013x",
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                    appNote:true,
                },
                {
                    name:"TI Precision Labs: ADC AC specifications",
                    url:"https://www.ti.com/video/5466126729001",
                    video:true,
                },
                {
                    name:"TI Precision Labs: ADC Error sources",
                    url:"https://www.ti.com/video/5438477774001",
                    video:true,
                },
                {
                    name:"TI Precision Labs: ADC Noise",
                    url:"https://www.ti.com/video/6114701198001",
                    video:true,
                },
                {
                    name:"TI Precision Labs: Analog-to-digital converter (ADC) drive topologies",
                    url:"https://www.ti.com/video/6279972316001",
                    video:true,
                },
                {
                    name:"TI Precision Labs: Electrical overstress on data converters",
                    url:"https://www.ti.com/video/6025680789001",
                    video:true,
                },
                {
                    name:"TI Precision Labs: High-speed ADC fundamentals",
                    url:"https://www.ti.com/video/5527915856001",
                    video:true,
                },
                {
                    name:"TI Precision Labs: SAR \u0026 Delta-Sigma: Understanding the Difference",
                    url:"https://www.ti.com/video/6228191712001",
                    video:true,
                },
                {
                    name:"TI e2e: ADC Bandwidth Clarification",
                    url:"https://e2e.ti.com/support/microcontrollers/c2000-microcontrollers-group/c2000/f/c2000-microcontrollers-forum/902366/tms320f28377d-ep-adc-bandwidth-clarification/3335570?tisearch=e2e-sitesearch&amp;keymatch=aperture%20jitter#3335570",
                },
                {
                    name:"TI e2e: ADC Calibration and Total Unadjusted Error",
                    url:"https://e2e.ti.com/support/microcontrollers/c2000-microcontrollers-group/c2000/f/c2000-microcontrollers-forum/587441/faq-tms320f28035-adc-calibration-and-total-unadjusted-error",
                },
                {
                    name:"TI e2e: ADC Reference Driver Options",
                    url:"https://e2e.ti.com/support/microcontrollers/c2000-microcontrollers-group/c2000/f/c2000-microcontrollers-forum/477506/faq-adc-reference-in-tms320f28377dzwt",
                },
                {
                    name:"TI e2e: ADC Resolution with Oversampling",
                    url:"https://e2e.ti.com/support/microcontrollers/c2000-microcontrollers-group/c2000/f/c2000-microcontrollers-forum/815285/tms320f280049-about-the-actual-adc-resolution/3017272#3017272",
                },
                {
                    name:"TI e2e: ADC configuration for interleaved mode",
                    url:"https://e2e.ti.com/support/microcontrollers/c2000-microcontrollers-group/c2000/f/c2000-microcontrollers-forum/757435/tms320f28379d-adc-configuration-for-interleaved-mode/2799102?tisearch=e2e-sitesearch&amp;keymatch=aperture%2525252520jitter#2799102",
                },
                {
                    name:"TI e2e: Simultaneous Sampling with Single ADC",
                    url:"https://e2e.ti.com/support/microcontrollers/c2000-microcontrollers-group/c2000/f/c2000-microcontrollers-forum/930245/tms320f280049-simultaneous-sampling-with-single-adc/3437033?tisearch=e2e-sitesearch&amp;keymatch=burst%2520mode#3437033",
                },
                {
                    name:"TMS320280x and TMS320F2801x ADC Calibration Application Report",
                    url:"https://ti.com/lit/SPRAAD8",
                    devices:[
                        "LEGACY",
                    ],
                    appNote:true,
                },
                {
                    name:"TMS320F2810, TMS320F2811, TMS320F2812 ADC Calibration Application Report",
                    url:"https://ti.com/lit/SPRA989",
                    devices:[
                        "LEGACY",
                    ],
                    appNote:true,
                },
            ]
        },
    ],
    "BGCRC":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"C2000 Academy - BGCRC",
                    url:"https://dev.ti.com/tirex/local?id=source_c2000_security_safety_c2000_bgcrc&amp;packageId=C2000-ACADEMY",
                    devices:[
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2838x",
                        "F28P65x",
                    ],
                },
            ]
        },
        {
            category_displayName: "Getting Started Materials",
            content:[
                {
                    name:"CRC Engines in C2000 Devices Application Report",
                    url:"https://www.ti.com/lit/spracr3",
                    appNote:true,
                },
            ]
        },
    ],
    "BootROM":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"C2000 Academy - BootROM",
                    url:"https://dev.ti.com/tirex/local?id=source_c2000_system_c2000_boot&amp;packageId=C2000-ACADEMY",
                    devices:[
                        "F280013x",
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                },
            ]
        },
    ],
    "C28X":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"C2000 Academy - C28x",
                    url:"https://dev.ti.com/tirex/local?id=source_c2000_overview_c2000_device_overview&amp;packageId=C2000-ACADEMY",
                    devices:[
                        "F280013x",
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                },
                {
                    name:"C2000 C28x Migration from COFF to EABI",
                    url:"https://software-dl.ti.com/ccs/esd/documents/C2000_c28x_migration_from_coff_to_eabi.html",
                },
                {
                    name:"C2000 C28x Optimization Guide",
                    url:"https://software-dl.ti.com/C2000/docs/optimization_guide/index.html",
                },
                {
                    name:"C2000 Performance Tips and Tricks ",
                    url:"http://software-dl.ti.com/ccs/esd/documents/c2000_c2000-performance-tips-and-tricks.html",
                },
                {
                    name:"C2000 Software Guide",
                    url:"https://software-dl.ti.com/C2000/docs/software_guide/index.html",
                },
                {
                    name:"CGT Data Blocking C2000",
                    url:"https://software-dl.ti.com/ccs/esd/documents/cgt_data-blocking-c2000.html",
                },
                {
                    name:"Enhancing the Computational Performance of the C2000\u2122 Microcontroller Family Application Report",
                    url:"https://ti.com/lit/SPRY288",
                    appNote:true,
                },
                {
                    name:"How fast is your 32-bit MCU?",
                    url:"https://e2e.ti.com/blogs_/b/industrial_strength/archive/2015/07/15/how-fast-is-your-32-bit-mcu",
                    devices:[
                        "F2807x",
                        "F2837x",
                        "LEGACY",
                    ],
                },
            ]
        },
        {
            category_displayName: "Getting Started Materials",
            content:[
                {
                    name:"C2000 Multicore Development User Guide",
                    url:"https://software-dl.ti.com/C2000/docs/C2000_Multicore_Development_User_Guide/index.html",
                },
                {
                    name:"C2000 VCU, Viterbi, Complex Math, and CRC",
                    url:"https://www.ti.com/video/3869897798001",
                    devices:[
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F28P55x",
                        "F28P65x",
                        "LEGACY",
                    ],
                    video:true,
                },
                {
                    name:"C2000Ware - CLAMath",
                    url:"https://dev.ti.com/tirex/explore/node?node=AJQZotxCdtXD4hGbOZrXXA__gYkahfz__LATEST",
                },
                {
                    name:"C2000Ware - FPU Fast RTS",
                    url:"https://dev.ti.com/tirex/explore/node?node=AMKkBMCf2i6vcDt9cLSJ0A__gYkahfz__LATEST",
                },
                {
                    name:"C2000Ware - FPU Library",
                    url:"https://dev.ti.com/tirex/explore/node?node=AKg0a8h-.vTGXaCZThPhkQ__gYkahfz__LATEST",
                },
                {
                    name:"C2000Ware - Fast Integer Division",
                    url:"https://dev.ti.com/tirex/explore/node?node=AJvCpzFT6CVD21-BTdLCJg__gYkahfz__LATEST",
                },
                {
                    name:"C2000Ware - Fixed Point Library",
                    url:"https://dev.ti.com/tirex/explore/node?node=ALuZdvMDhSsqxHVeb595ZQ__gYkahfz__LATEST",
                },
                {
                    name:"C2000Ware - IQMath",
                    url:"https://dev.ti.com/tirex/explore/node?node=AOg.3PQHvLDA2Ap18Lmjpg__gYkahfz__LATEST",
                },
                {
                    name:"C2000Ware - VCU Library",
                    url:"https://dev.ti.com/tirex/explore/node?node=AMXKlFPARdBiAwrbthDVyQ__gYkahfz__LATEST",
                },
                {
                    name:"C28x Context Save and Restore",
                    url:"https://software-dl.ti.com/C2000/docs/c28x_context_save_restore/html/index.html",
                },
                {
                    name:"CRC Engines in C2000 Devices Application Report",
                    url:"https://ti.com/lit/SPRACR3",
                    appNote:true,
                },
                {
                    name:"Migrating Software From 8-Bit (Byte) Addressable CPU\u0027s to C28x CPU Application Report",
                    url:"https://www.ti.com/lit/sprad88",
                    devices:[
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F28P55x",
                        "F28P65x",
                    ],
                    appNote:true,
                },
                {
                    name:"TMS320C28x Extended Instruction Sets Application Report",
                    url:"https://ti.com/lit/SPRUHS1C",
                    appNote:true,
                },
                {
                    name:"TMS320C28x FPU Primer Application Report",
                    url:"https://ti.com/lit/SPRAAN9",
                    appNote:true,
                },
                {
                    name:"Texas Instruments F28002x Peripheral Driver Library",
                    url:"https://software-dl.ti.com/C2000/docs/C2000_driverlib_api_guide/f28002x/html/index.html",
                    devices:[
                        "F28002x",
                    ],
                },
                {
                    name:"Texas Instruments F28004x Peripheral Driver Library",
                    url:"https://software-dl.ti.com/C2000/docs/C2000_driverlib_api_guide/f28004x/html/index.html",
                    devices:[
                        "F28004x",
                    ],
                },
                {
                    name:"Texas Instruments F2807x Peripheral Driver Library",
                    url:"https://software-dl.ti.com/C2000/docs/C2000_driverlib_api_guide/f2807x/html/index.html",
                    devices:[
                        "F2807x",
                    ],
                },
                {
                    name:"Texas Instruments F2837xD Peripheral Driver Library",
                    url:"https://software-dl.ti.com/C2000/docs/C2000_driverlib_api_guide/f2837xd/html/index.html",
                    devices:[
                        "F2837xD",
                    ],
                },
                {
                    name:"Texas Instruments F2837xS Peripheral Driver Library",
                    url:"https://software-dl.ti.com/C2000/docs/C2000_driverlib_api_guide/f2837xs/html/index.html",
                    devices:[
                        "F2837xS",
                    ],
                },
                {
                    name:"Texas Instruments F2838x Peripheral Driver Library",
                    url:"https://software-dl.ti.com/C2000/docs/C2000_driverlib_api_guide/f2838x/html/index.html",
                    devices:[
                        "F2838x",
                    ],
                },
            ]
        },
        {
            category_displayName: "Expert Materials",
            content:[
                {
                    name:"Fast Integer Division - A Differentiated Offering From C2000 Product Family Application Report",
                    url:"https://ti.com/lit/SPRACN6",
                    devices:[
                        "F28002x",
                        "F28003x",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                    appNote:true,
                },
            ]
        },
    ],
    "CLA":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"C2000 Academy - CLA",
                    url:"https://dev.ti.com/tirex/local?id=source_c2000_advanced_topics_c2000_control_law_accelerator&amp;packageId=C2000-ACADEMY",
                    devices:[
                        "F280013x",
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                },
                {
                    name:"C2000 CLA C Compiler Series",
                    url:"https://www.ti.com/video/3871287205001",
                    video:true,
                },
                {
                    name:"CLA Hands On Workshop",
                    url:"https://www.ti.com/video/5432122168001",
                    video:true,
                },
                {
                    name:"CLA usage in Valley Switching Boost Power Factor Correction (PFC) Reference Design",
                    url:"https://www.ti.com/video/6050578280001",
                    video:true,
                },
                {
                    name:"Control Law Accelerator Debug in CCS 4",
                    url:"https://www.ti.com/video/4878221673001",
                    devices:[
                        "LEGACY",
                    ],
                    video:true,
                },
                {
                    name:"Control Law Accelerator Example Framework",
                    url:"https://www.ti.com/video/3869582778001",
                    devices:[
                        "LEGACY",
                    ],
                    video:true,
                },
                {
                    name:"Enhancing the Computational Performance of the C2000\u2122 Microcontroller Family Application Report",
                    url:"https://ti.com/lit/SPRY288",
                    appNote:true,
                },
            ]
        },
        {
            category_displayName: "Getting Started Materials",
            content:[
                {
                    name:"CLA Software Development Guide",
                    url:"https://software-dl.ti.com/C2000/docs/cla_software_dev_guide/index.html",
                },
                {
                    name:"Software Examples to Showcase Unique Capabilities of TI\u0027s C2000\u2122 CLA Application Report",
                    url:"https://ti.com/lit/SPRACS0",
                    appNote:true,
                },
            ]
        },
        {
            category_displayName: "Expert Materials",
            content:[
                {
                    name:"Digital Control of Two Phase Interleaved PFC and Motor Drive Using MCU With CLA Application Report",
                    url:"https://ti.com/lit/SPRABS5",
                    appNote:true,
                },
                {
                    name:"Sensorless Field Oriented Control:3-Phase Perm.Magnet Synch. Motors With CLA Application Report",
                    url:"https://ti.com/lit/SPRABQ5",
                    appNote:true,
                },
            ]
        },
    ],
    "CLB":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"C2000 Academy - CLB ",
                    url:"https://dev.ti.com/tirex/local?id=source_c2000_advanced_topics_c2000_configurable_logic_block&amp;packageId=C2000-ACADEMY",
                    devices:[
                        "F280013x",
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                },
                {
                    name:"C2000\u2122 Configurable Logic Block (CLB) Series",
                    url:"https://www.ti.com/video/series/C2000-configurable-logic-block.html",
                    video:true,
                },
                {
                    name:"Customizing on-chip peripherals defies conventional logic",
                    url:"https://e2e.ti.com/blogs_/b/industrial_strength/archive/2020/01/13/customizing-on-chip-peripherals-defies-conventional-logic",
                },
                {
                    name:"Enable Differentiation and win with CLB in various applications Application Report",
                    url:"https://www.ti.com/lit/slyp681",
                    appNote:true,
                },
                {
                    name:"Enable Differentiation with Configurable Logic in Various Automotive Applications",
                    url:"https://www.ti.com/video/6195168576001",
                    video:true,
                },
            ]
        },
        {
            category_displayName: "Getting Started Materials",
            content:[
                {
                    name:"C2000\u2122 Position Manager PTO API Reference Guide Application Report",
                    url:"www.ti.com/lit/SPRAC77",
                    appNote:true,
                },
                {
                    name:"CLB Tool User Guide",
                    url:"http://www.ti.com/lit/SPRUIR8",
                    description:"Basic examples are 7 - 15 (start with these). More involved examples are 1-6.",
                },
                {
                    name:"Designing With The C2000 Configurable Logic Block Application Report",
                    url:"https://ti.com/lit/SPRACL3",
                    appNote:true,
                },
                {
                    name:"How do I add SYSCONFIG support (Pinmux and Peripheral Initialization) to an existing driverlib project?",
                    url:"https://e2e.ti.com/support/microcontrollers/c2000-microcontrollers-group/c2000/f/c2000-microcontrollers-forum/910829/faq-how-do-i-add-sysconfig-support-pinmux-and-peripheral-initialization-to-an-existing-driverlib-project",
                },
                {
                    name:"How to Migrate Custom Logic From an FPGA/CPLD to C2000 Microcontrollers Application Report",
                    url:"https://ti.com/lit/SPRACO2",
                    description:"Chpaters 1-3 are very useful for getting started and learning the CLB. Later chapters are very useful Expert materials for migrating from FPGA/CPLD to C2000\u0027s CLB.",
                    appNote:true,
                },
            ]
        },
        {
            category_displayName: "Expert Materials",
            content:[
                {
                    name:"Achieve Delayed Protection for Three-Level Inverter With CLB Application Report",
                    url:"https://ti.com/lit/SPRACY3",
                    appNote:true,
                },
                {
                    name:"Diagnosing Delta-Sigma Modulator Bitstream Using C2000\u2122 Configurable Logic Block Application Report",
                    url:"https://www.ti.com/lit/SPRAD53",
                    appNote:true,
                },
                {
                    name:"How to Implement Custom Serial Interfaces Using Configurable Logic Block (CLB) Application Report",
                    url:"https://www.ti.com/lit/SPRAD62",
                    appNote:true,
                },
                {
                    name:"Tamagawa T-Format Absolute-Encoder Master Interface Reference Design for C2000\u2122 MCUs",
                    url:"www.ti.com/lit/TIDUE74",
                },
            ]
        },
    ],
    "CMPSS":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"C2000 Academy - CMPSS",
                    url:"https://dev.ti.com/tirex/local?id=source_c2000_analog_subsystem_c2000_comparator_subsystem&amp;packageId=C2000-ACADEMY",
                    devices:[
                        "F280013x",
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                },
                {
                    name:"Real-Time Control Reference Guide",
                    url:"https://www.ti.com/lit/eb/slyy211/slyy211.pdf",
                    description:"Refer to the Comparator section",
                },
            ]
        },
        {
            category_displayName: "Getting Started Materials",
            content:[
                {
                    name:"Utilizing MCU integrated analog comparators to provide power protection",
                    url:"https://ti.com/lit/SPRY206",
                    devices:[
                        "LEGACY",
                    ],
                },
            ]
        },
        {
            category_displayName: "Expert Materials",
            content:[
                {
                    name:"Peak Current Control Realization for Boost Circuit Based On C2000\u2122 MCU Application Report",
                    url:"https://ti.com/lit/SPRABU2",
                    appNote:true,
                },
                {
                    name:"Peak Current Mode Controlled PSFB Converter Reference Design Using C2000\u2122 Real-time MCU",
                    url:"https://ti.com/lit/TIDUEO1",
                },
                {
                    name:"Understanding and Applying Current-Mode Control Theory Application Report",
                    url:"https://ti.com/lit/SNVA555",
                    appNote:true,
                },
            ]
        },
    ],
    "DAC":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"C2000 Academy - DAC",
                    url:"https://dev.ti.com/tirex/local?id=source_c2000_analog_subsystem_c2000_digital_to_analog_converter&amp;packageId=C2000-ACADEMY",
                    devices:[
                        "F280013x",
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                },
                {
                    name:"High Speed, Digital to Analog Converters Basics Application Report",
                    url:"https://www.ti.com/lit/SLAA523A",
                    appNote:true,
                },
                {
                    name:"Real-Time Control Reference Guide",
                    url:"https://www.ti.com/lit/eb/slyy211/slyy211.pdf",
                    description:"Refer to the DAC section",
                },
                {
                    name:"Understanding Data Converters Application Report",
                    url:"https://www.ti.com/lit/SLAA013",
                    appNote:true,
                },
            ]
        },
        {
            category_displayName: "Getting Started Materials",
            content:[
                {
                    name:"MathWorks F2807x/F2837xD/F2837xS/F28004x/F2838x DAC",
                    url:"https://www.mathworks.com/help/supportpkg/texasinstrumentsc2000/ref/f2807xf2837xdf2837xsf28004xf28003xf2838xdac.html",
                    description:"NOTE: This is a non-TI (third party) site.",
                    devices:[
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P65x",
                    ],
                },
            ]
        },
    ],
    "DCAN":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"Automotive CAN Overview and Training",
                    url:"https://www.ti.com/video/5236633580001",
                    video:true,
                },
                {
                    name:"C2000 Academy - CAN",
                    url:"https://dev.ti.com/tirex/local?id=source_c2000_communications_c2000_can&amp;packageId=C2000-ACADEMY",
                    description:"Refer to the DCAN section",
                    devices:[
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                },
                {
                    name:"CAN Physical layer",
                    url:"https://www.ti.com/video/6078637405001",
                    video:true,
                },
                {
                    name:"CAN and CAN FD Overview",
                    url:"https://www.ti.com/video/6078637459001",
                    video:true,
                },
                {
                    name:"CAN and CAN FD Protocol",
                    url:"https://www.ti.com/video/6078640832001",
                    devices:[
                        "F280013x",
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                    video:true,
                },
            ]
        },
        {
            category_displayName: "Getting Started Materials",
            content:[
                {
                    name:"Programming Examples and Debug Strategies for the DCAN Module Application Report",
                    url:"https://ti.com/lit/SPRACE5",
                    devices:[
                        "F28002x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P65x",
                    ],
                    appNote:true,
                },
            ]
        },
        {
            category_displayName: "Expert Materials",
            content:[
                {
                    name:"Configurable Error Generator for Controller Area Network Application Report",
                    url:"https://ti.com/lit/SPRACQ3",
                    devices:[
                        "F28002x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                    appNote:true,
                },
            ]
        },
    ],
    "DCSM":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"C2000 Academy - DCSM",
                    url:"https://dev.ti.com/tirex/local?id=source_c2000_security_safety_c2000_dcsm&amp;packageId=C2000-ACADEMY",
                    devices:[
                        "F280013x",
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                },
            ]
        },
        {
            category_displayName: "Getting Started Materials",
            content:[
                {
                    name:"C2000 DCSM Security Tool Application Report",
                    url:"https://ti.com/lit/SPRACP8",
                    appNote:true,
                },
                {
                    name:"C2000 Unique Device Number Application Report",
                    url:"https://ti.com/lit/SPRACD0",
                    appNote:true,
                },
                {
                    name:"Enhancing Device Security by Using JTAGLOCK Feature Application Report",
                    url:"https://ti.com/lit/SPRACS4",
                    appNote:true,
                },
                {
                    name:"Secure BOOT On C2000 Device Application Report",
                    url:"https://ti.com/lit/SPRACT3",
                    devices:[
                        "F280013x",
                        "F280015x",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                    appNote:true,
                },
            ]
        },
        {
            category_displayName: "Expert Materials",
            content:[
                {
                    name:"Updating Firmware on Security Enabled TMS320F2837xx or TMS320F2807x Devices Application Report",
                    url:"https://www.ti.com/lit/spraci5",
                    devices:[
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                    ],
                    appNote:true,
                },
            ]
        },
    ],
    "DMA":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"C2000 Academy - DMA",
                    url:"https://dev.ti.com/tirex/local?id=source_c2000_advanced_topics_c2000_direct_memory_access&amp;packageId=C2000-ACADEMY",
                    devices:[
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                },
            ]
        },
    ],
    "ECAN":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"Automotive CAN Overview and Training",
                    url:"https://www.ti.com/video/5236633580001",
                    video:true,
                },
                {
                    name:"CAN Physical layer",
                    url:"https://www.ti.com/video/6078637405001",
                    video:true,
                },
                {
                    name:"CAN and CAN FD Overview",
                    url:"https://www.ti.com/video/6078637459001",
                    video:true,
                },
                {
                    name:"CAN and CAN FD Protocol",
                    url:"https://www.ti.com/video/6078640832001",
                    devices:[
                        "F280013x",
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                    video:true,
                },
            ]
        },
        {
            category_displayName: "Getting Started Materials",
            content:[
                {
                    name:"MCU CAN Module Operation Using the On-Chip Zero-Pin Oscillator Application Report",
                    url:"https://ti.com/lit/SPRABI7",
                    devices:[
                        "LEGACY",
                    ],
                    appNote:true,
                },
                {
                    name:"Programming Examples for the TMS320x28xx eCAN Application Report",
                    url:"https://ti.com/lit/SPRA876",
                    devices:[
                        "LEGACY",
                    ],
                    appNote:true,
                },
                {
                    name:"Using the CAN Bootloader at High Temperature Application Report",
                    url:"https://ti.com/lit/SPRABY7",
                    devices:[
                        "LEGACY",
                    ],
                    appNote:true,
                },
            ]
        },
    ],
    "ECAP":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"C2000 Academy - ECAP",
                    url:"https://dev.ti.com/tirex/local?id=source_c2000_control_peripherals_c2000_enhanced_capture_module&amp;packageId=C2000-ACADEMY",
                    devices:[
                        "F280013x",
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                },
            ]
        },
        {
            category_displayName: "Getting Started Materials",
            content:[
                {
                    name:"Leveraging High Resolution Capture (HRCAP) for Single Wire Data Transfer Application Report",
                    url:"https://ti.com/lit/SPRACO5",
                    appNote:true,
                },
            ]
        },
    ],
    "ECAT":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"C2000 Academy - EtherCAT",
                    url:"https://dev.ti.com/tirex/local?id=source_c2000_communications_c2000_ethercat&amp;packageId=C2000-ACADEMY",
                    devices:[
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P65x",
                    ],
                },
                {
                    name:"EtherCAT Device Protocol Poster",
                    url:"https://www.ethercat.org/download/documents/EtherCAT_Device_Protocol_Poster.pdf",
                    devices:[
                        "F2838x",
                        "F28P65x",
                    ],
                },
                {
                    name:"EtherCAT Protocol Series",
                    url:"https://training.ti.com/ethercat-protocol-c2000-real-time-controller?context=1137766-1147233",
                    devices:[
                        "F2838x",
                        "F28P65x",
                    ],
                    video:true,
                },
            ]
        },
        {
            category_displayName: "Getting Started Materials",
            content:[
                {
                    name:"EtherCAT User\u0027s Guide",
                    url:"https://dev.ti.com/tirex/explore/node?node=AJlv0LZ8NvH0gPlyyf27-Q__gYkahfz__LATEST",
                    devices:[
                        "F2838x",
                        "F28P65x",
                    ],
                },
                {
                    name:"Real-time control meets real-time industrial communications development - part 4",
                    url:"https://e2e.ti.com/blogs_/b/industrial_strength/archive/2019/07/15/real-time-control-meets-real-time-industrial-communications-development-part-4",
                    devices:[
                        "F2838x",
                        "F28P65x",
                    ],
                },
            ]
        },
        {
            category_displayName: "Expert Materials",
            content:[
                {
                    name:"Design Guide: TIDM-02006 Distributed Multi-axis Servo Drive Over Fast Serial Interface (FSI) Reference Design",
                    url:"https://www.ti.com/lit/TIDUEV1",
                },
                {
                    name:"EtherCAT Based Connected Servo Drive using Fast Current Loop on PMSM Application Report",
                    url:"https://ti.com/lit/SPRACM9",
                    devices:[
                        "F2838x",
                        "F28P65x",
                    ],
                    appNote:true,
                },
                {
                    name:"EtherCAT Technology Group - Download Section Landing Page",
                    url:"https://www.ethercat.org/en/downloads.html",
                    devices:[
                        "F2838x",
                        "F28P65x",
                    ],
                },
                {
                    name:"Hardware Data Sheet Section I - Technology",
                    url:"https://download.beckhoff.com/download/Document/io/ethercat-development-products/ethercat_esc_datasheet_sec1_technology_2i3.pdf",
                    devices:[
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                },
                {
                    name:"Hardware Data Sheet Section II - Register Description",
                    url:"https://download.beckhoff.com/download/Document/io/ethercat-development-products/ethercat_esc_datasheet_sec2_registers_3i0.pdf",
                    devices:[
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                },
                {
                    name:"PHY Selection Guide",
                    url:"https://download.beckhoff.com/download/document/io/ethercat-development-products/an_phy_selection_guidev3.0.pdf",
                    devices:[
                        "F2838x",
                        "F28P65x",
                    ],
                },
            ]
        },
    ],
    "EMIF":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"C2000 Academy - EMIF",
                    url:"https://dev.ti.com/tirex/local?id=source_c2000_system_c2000_emif&amp;packageId=C2000-ACADEMY",
                    devices:[
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                },
            ]
        },
        {
            category_displayName: "Getting Started Materials",
            content:[
                {
                    name:"Design and Usage Guidelines for the C2000 External Memory Interface (EMIF) Application Report",
                    url:"https://ti.com/lit/SPRAC96",
                    devices:[
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P65x",
                    ],
                    appNote:true,
                },
            ]
        },
        {
            category_displayName: "Expert Materials",
            content:[
                {
                    name:"Accessing External SDRAM on the TMS320F2837x/2807x Microcontrollers Using C/C++ Application Report",
                    url:"https://www.ti.com/lit/spraby4",
                    description:"In addition to the devices in the title, this material also applies to other devices with EMIF.",
                    devices:[
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                    ],
                    appNote:true,
                },
            ]
        },
    ],
    "EPG":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"C2000 Academy - EPG",
                    url:"https://dev.ti.com/tirex/local?id=source_c2000_debug_systems_c2000_epg&amp;packageId=C2000-ACADEMY",
                    devices:[
                        "F280013x",
                        "F280015x",
                        "F28003x",
                        "F28P55x",
                        "F28P65x",
                    ],
                },
                {
                    name:"C2000 Embedded Pattern Generator",
                    url:"https://www.ti.com/video/6280114167001",
                    video:true,
                },
            ]
        },
        {
            category_displayName: "Getting Started Materials",
            content:[
                {
                    name:"Designing With the C2000\u2122 Embedded Pattern Generator (EPG) Application Report",
                    url:"https://www.ti.com/lit/spracy7",
                    appNote:true,
                },
            ]
        },
    ],
    "EPWM":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"C2000 Academy - EPWM",
                    url:"https://dev.ti.com/tirex/local?id=source_c2000_control_peripherals_c2000_enhanced_pulse_width_modulation&amp;packageId=C2000-ACADEMY",
                    devices:[
                        "F280013x",
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                },
                {
                    name:"Real-Time Control Reference Guide",
                    url:"https://www.ti.com/lit/eb/slyy211/slyy211.pdf",
                    description:"Refer to the EPWM section",
                },
            ]
        },
        {
            category_displayName: "Getting Started Materials",
            content:[
                {
                    name:"C2000 Enhanced Pulse Width Modulator (ePWM): Type-5 Feature Set",
                    url:"https://www.ti.com/video/6337559794112",
                    devices:[
                        "F28P65x",
                    ],
                    video:true,
                },
                {
                    name:"C2000 ePWM Developer\u0027s Guide Application Report",
                    url:"https://www.ti.com/lit/sprad12",
                    devices:[
                        "F280013x",
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837x",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                    appNote:true,
                },
                {
                    name:"Enhanced Pulse Width Modulator (ePWM) Training for C2000 MCUs",
                    url:"https://www.ti.com/video/series/C2000-enhanced-pulse-width-modulator.html",
                    devices:[
                        "F280013x",
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2837x",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                    video:true,
                },
                {
                    name:"Flexible PWMs Enable Multi-Axis Drives, Multi-Level Inverters Application Report",
                    url:"https://ti.com/lit/SPRT723",
                    appNote:true,
                },
                {
                    name:"Getting Started with the C2000 ePWM Module",
                    url:"https://www.ti.com/video/5775904537001",
                    video:true,
                },
                {
                    name:"Using PWM Output as a Digital-to-Analog Converter on a TMS320F280x Digital Signal Control Application Report",
                    url:"https://ti.com/lit/SPRAA88",
                    description:"Chapters 1 to 6 are Fundamental material, derivations, and explanations that are useful for learning about how PWM can be used to implement a DAC. Subsequent chapters are Getting Started and Expert material for implementing in a system.",
                    appNote:true,
                },
                {
                    name:"Using the Enhanced Pulse Width Modulator (ePWM) Module Application Report",
                    url:"https://ti.com/lit/SPRAAI1",
                    appNote:true,
                },
            ]
        },
        {
            category_displayName: "Expert Materials",
            content:[
                {
                    name:"C2000 real-time microcontrollers - Reference designs",
                    url:"https://www.ti.com/reference-designs/index.html#search?famid=4,5014",
                    description:"See TI designs related to specific end applications used.",
                },
                {
                    name:"CRM/ZVS PFC Implementation Based on C2000 Type-4 PWM Module Application Report",
                    url:"https://ti.com/lit/SPRACX0",
                    devices:[
                        "F280013x",
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2837x",
                        "F2838x",
                        "F28P55x",
                    ],
                    appNote:true,
                },
                {
                    name:"Leverage New Type ePWM Features for Multiple Phase Control Application Report",
                    url:"https://ti.com/lit/SPRACY1",
                    devices:[
                        "F280013x",
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2837x",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                    appNote:true,
                },
            ]
        },
    ],
    "EQEP":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"C2000 Academy - EQEP",
                    url:"https://dev.ti.com/tirex/local?id=source_c2000_control_peripherals_c2000_enhanced_quadrature_encoder_pulse&amp;packageId=C2000-ACADEMY",
                    devices:[
                        "F280013x",
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                },
                {
                    name:"Interfacing with Quadrature Encoders",
                    url:"https://www.ti.com/video/6308652805112",
                    video:true,
                },
                {
                    name:"Real-Time Control Reference Guide",
                    url:"https://www.ti.com/lit/eb/slyy211/slyy211.pdf",
                    description:"Refer to the Encoders section",
                },
            ]
        },
        {
            category_displayName: "Getting Started Materials",
            content:[
                {
                    name:"C2000\u2122 Position Manager PTO API Reference Guide Application Report",
                    url:"www.ti.com/lit/SPRAC77",
                    appNote:true,
                },
            ]
        },
        {
            category_displayName: "Expert Materials",
            content:[
                {
                    name:"CW/CCW Support on the C2000 eQEP Module Application Report",
                    url:"https://ti.com/lit/SPRABX2",
                    appNote:true,
                },
            ]
        },
    ],
    "ERAD":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"C2000 Academy - ERAD",
                    url:"https://dev.ti.com/tirex/local?id=source_c2000_debug_systems_c2000_erad&amp;packageId=C2000-ACADEMY",
                    devices:[
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P65x",
                    ],
                },
                {
                    name:"Embedded Real-Time Analysis \u0026 Diagnostics (ERAD) on C2000\u2122 Devices",
                    url:"https://www.ti.com/video/5745571666001",
                    devices:[
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                    video:true,
                },
            ]
        },
        {
            category_displayName: "Getting Started Materials",
            content:[
                {
                    name:"Embedded Real-Time Analysis \u0026 Diagnostics (ERAD) on C2000 MCUs",
                    url:"https://www.ti.com/video/6292444674001",
                    video:true,
                },
                {
                    name:"Embedded Real-Time Analysis and Response for Control Applications Application Report",
                    url:"https://ti.com/lit/SPRACM7",
                    devices:[
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                    appNote:true,
                },
            ]
        },
    ],
    "FLASH":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"C2000 Academy - FLASH",
                    url:"https://dev.ti.com/tirex/local?id=source_c2000_system_c2000_flash&amp;packageId=C2000-ACADEMY",
                    devices:[
                        "F280013x",
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                },
                {
                    name:"Embedded Flash Memory",
                    url:"https://www.ti.com/video/6308729698112",
                    video:true,
                },
            ]
        },
        {
            category_displayName: "Getting Started Materials",
            content:[
                {
                    name:"Copying Compiler Sections from Flash to RAM on the TMS320F28xxx DSCs Application Report",
                    url:"https://ti.com/lit/SPRAAU8",
                    devices:[
                        "LEGACY",
                    ],
                    appNote:true,
                },
                {
                    name:"Running an Application from Internal Flash Memory on the TMS320F28xxx DSP Application Report",
                    url:"https://ti.com/lit/SPRA958",
                    devices:[
                        "LEGACY",
                    ],
                    appNote:true,
                },
                {
                    name:"Serial Flash Programming of C2000 Microcontrollers Application Report",
                    url:"https://ti.com/lit/SPRABV4",
                    devices:[
                        "F280013x",
                        "F280015x",
                        "F28002x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                    appNote:true,
                },
                {
                    name:"[FAQ] F05 Flash: Frequently Asked Questions",
                    url:"https://e2e.ti.com/support/microcontrollers/c2000-microcontrollers-group/c2000/f/c2000-microcontrollers-forum/757585/faq-f05-flash-frequently-asked-questions",
                    devices:[
                        "LEGACY",
                    ],
                },
                {
                    name:"[FAQ] FAQ for Flash ECC usage in C2000 devices - Includes ECC test mode, Linker ECC options: ",
                    url:"https://e2e.ti.com/support/microcontrollers/c2000/f/171/t/951658",
                },
                {
                    name:"[FAQ] FAQ on Flash API usage for C2000 devices",
                    url:"https://e2e.ti.com/support/microcontrollers/c2000-microcontrollers-group/c2000/f/c2000-microcontrollers-forum/951668/faq-faq-on-flash-api-usage-for-c2000-devices",
                    devices:[
                        "F280013x",
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                        "LEGACY",
                    ],
                },
                {
                    name:"[FAQ] Flash - How to modify an application from RAM configuration to Flash configuration?",
                    url:"https://e2e.ti.com/support/microcontrollers/c2000/f/171/t/878674",
                },
                {
                    name:"[FAQ] How can we improve the Flash tool performance?",
                    url:"https://e2e.ti.com/support/microcontrollers/c2000/f/171/t/904312",
                },
                {
                    name:"[FAQ] TI C2000 Device Programming Tools and Services",
                    url:"https://e2e.ti.com/support/microcontrollers/c2000/f/171/t/914024",
                },
            ]
        },
        {
            category_displayName: "Expert Materials",
            content:[
                {
                    name:"EEPROM Emulation for Gen 2 C2000 Real-Time MCUs Application Report",
                    url:"https://www.ti.com/lit/sprab69",
                    devices:[
                        "LEGACY",
                    ],
                    appNote:true,
                },
                {
                    name:"TMS320F281x Boot ROM Serial Flash Programming Application Report",
                    url:"https://ti.com/lit/SPRAAQ2",
                    devices:[
                        "LEGACY",
                    ],
                    appNote:true,
                },
                {
                    name:"Updating Firmware on Security Enabled TMS320F2837xx or TMS320F2807x Devices Application Report",
                    url:"https://www.ti.com/lit/spraci5",
                    devices:[
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                    ],
                    appNote:true,
                },
            ]
        },
    ],
    "FSI":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"C2000 Academy - FSI",
                    url:"https://dev.ti.com/tirex/local?id=source_c2000_communications_c2000_fsi&amp;packageId=C2000-ACADEMY",
                    devices:[
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                },
            ]
        },
        {
            category_displayName: "Getting Started Materials",
            content:[
                {
                    name:"Fast Serial Interface (FSI) Skew Compensation Application Report",
                    url:"https://ti.com/lit/SPRACJ9",
                    appNote:true,
                },
                {
                    name:"Fast serial interface (FSI) adapter board evaluation module",
                    url:"https://www.ti.com/tool/TMDSFSIADAPEVM",
                },
                {
                    name:"Using the Fast Serial Interface (FSI) With Multiple Devices in an Application Application Report",
                    url:"https://ti.com/lit/SPRACM3",
                    appNote:true,
                },
            ]
        },
        {
            category_displayName: "Expert Materials",
            content:[
                {
                    name:"Design Guide: TIDM-02006 Distributed Multi-axis Servo Drive Over Fast Serial Interface (FSI) Reference Design",
                    url:"https://www.ti.com/lit/TIDUEV1",
                },
                {
                    name:"The Essential Guide for Developing With C2000 Real-Time Microcontrollers Application Report",
                    url:"https://ti.com/lit/SPRACN0",
                    description:"Refer to the See sections \u0027Distributed Real-Time Control Across an Isolation Boundary\u0027 and \u0027Solving Event Synchronization Across Multiple Controllers in Decentralized Control Systems\u0027. section",
                    appNote:true,
                },
            ]
        },
    ],
    "Functional Safety":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"C2000 Academy - Functional Safety",
                    url:"https://dev.ti.com/tirex/local?id=source_c2000_security_safety_c2000_fusa&amp;packageId=C2000-ACADEMY",
                    devices:[
                        "F280013x",
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                },
            ]
        },
    ],
    "GPIO":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"C2000 Academy - GPIO",
                    url:"https://dev.ti.com/tirex/local?id=source_c2000_system_c2000_gpio_xbar&amp;packageId=C2000-ACADEMY",
                    devices:[
                        "F280013x",
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                },
            ]
        },
        {
            category_displayName: "Getting Started Materials",
            content:[
                {
                    name:"How to Maximize GPIO Usage in C2000 Devices Application Report",
                    url:"https://ti.com/lit/SPRACP6",
                    appNote:true,
                },
                {
                    name:"[FAQ] C2000 GPIO FAQ",
                    url:"https://e2e.ti.com/support/microcontrollers/c2000-microcontrollers-group/c2000/f/c2000-microcontrollers-forum/942389/faq-c2000-gpio-faq",
                },
            ]
        },
    ],
    "HIC":[
        {
            category_displayName: "Getting Started Materials",
            content:[
                {
                    name:"Design Guide for Enabling Peripheral Expansion Applications Using the HIC Application Report",
                    url:"https://ti.com/lit/SPRACR2",
                    devices:[
                        "F28002x",
                        "F28003x",
                    ],
                    appNote:true,
                },
            ]
        },
    ],
    "HRCAP":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"C2000 Academy - Control Peripherals",
                    url:"https://dev.ti.com/tirex/local?id=source_c2000_control_peripherals_c2000_enhanced_capture_module&amp;packageId=C2000-ACADEMY#hrcap",
                    devices:[
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                },
            ]
        },
        {
            category_displayName: "Getting Started Materials",
            content:[
                {
                    name:"Leveraging High Resolution Capture (HRCAP) for Single Wire Data Transfer Application Report",
                    url:"https://ti.com/lit/SPRACO5",
                    appNote:true,
                },
            ]
        },
    ],
    "I2C":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"C2000 Academy - I2C",
                    url:"https://dev.ti.com/tirex/local?id=source_c2000_communications_c2000_i2c&amp;packageId=C2000-ACADEMY",
                    devices:[
                        "F280013x",
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                },
                {
                    name:"I2C Hardware Overview",
                    url:"https://www.ti.com/video/6048454601001",
                    video:true,
                },
                {
                    name:"I2C Protocol Overview",
                    url:"https://www.ti.com/video/6047548123001",
                    video:true,
                },
                {
                    name:"Understanding the I2C Bus Application Report",
                    url:"https://www.ti.com/lit/pdf/slva704",
                    appNote:true,
                },
            ]
        },
        {
            category_displayName: "Getting Started Materials",
            content:[
                {
                    name:"Configuring the TMS320F280x DSP as an I2C Processor Application Report",
                    url:"https://ti.com/lit/SPRAAN8",
                    appNote:true,
                },
                {
                    name:"I2C Buffers Overview",
                    url:"https://www.ti.com/video/6049695096001",
                    video:true,
                },
                {
                    name:"I2C Dynamic Addressing Application Report",
                    url:"https://www.ti.com/lit/pdf/scaa137",
                    appNote:true,
                },
                {
                    name:"I2C translators overview",
                    url:"https://www.ti.com/video/6048453246001",
                    video:true,
                },
                {
                    name:"Interfacing EEPROM Using C2000 I2C Module Application Report",
                    url:"https://www.ti.com/lit/spracs8",
                    appNote:true,
                },
                {
                    name:"Why, When, and How to use I2C Buffers Application Report",
                    url:"https://www.ti.com/lit/pdf/scpa054",
                    appNote:true,
                },
            ]
        },
        {
            category_displayName: "Expert Materials",
            content:[
                {
                    name:"I2C Bus Pull-Up Resistor Calculation Application Report",
                    url:"https://www.ti.com/lit/pdf/slva689",
                    appNote:true,
                },
                {
                    name:"Maximum Clock Frequency of I2C Bus Using Repeaters Application Report",
                    url:"https://www.ti.com/lit/pdf/slva695",
                    appNote:true,
                },
            ]
        },
    ],
    "IPC":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"C2000 Academy - IPC",
                    url:"https://dev.ti.com/tirex/local?id=source_c2000_advanced_topics_c2000_interprocessor_communications&amp;packageId=C2000-ACADEMY",
                    devices:[
                        "F2837xD",
                        "F2838x",
                        "F28P65x",
                    ],
                },
            ]
        },
    ],
    "Interrupts":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"C2000 Academy - Interrupts",
                    url:"https://dev.ti.com/tirex/local?id=source_c2000_system_c2000_interrupt&amp;packageId=C2000-ACADEMY",
                    devices:[
                        "F280013x",
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                },
            ]
        },
    ],
    "LIN":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"C2000 Academy - LIN",
                    url:"https://dev.ti.com/tirex/local?id=source_c2000_communications_c2000_lin&amp;packageId=C2000-ACADEMY",
                    devices:[
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F28P55x",
                        "F28P65x",
                        "LEGACY",
                    ],
                },
                {
                    name:"LIN Protocol and Physical Layer Requirements Application Report",
                    url:"https://www.ti.com/lit/slla383",
                    devices:[
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F28P55x",
                        "F28P65x",
                        "LEGACY",
                    ],
                    appNote:true,
                },
                {
                    name:"Local Interconnect Network (LIN) Overview and Training",
                    url:"https://www.ti.com/video/5741358648001",
                    devices:[
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F28P55x",
                        "F28P65x",
                        "LEGACY",
                    ],
                    video:true,
                },
            ]
        },
    ],
    "MCAN":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"C2000 Academy - MCAN",
                    url:"https://dev.ti.com/tirex/local?id=source_c2000_communications_c2000_mcan&amp;packageId=C2000-ACADEMY",
                    devices:[
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                },
                {
                    name:"CAN and CAN FD Overview",
                    url:"https://www.ti.com/video/6078637459001",
                    video:true,
                },
                {
                    name:"CAN and CAN FD Protocol",
                    url:"https://www.ti.com/video/6078640832001",
                    devices:[
                        "F280013x",
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                    video:true,
                },
            ]
        },
        {
            category_displayName: "Getting Started Materials",
            content:[
                {
                    name:"Getting Started with the MCAN (CAN FD) Module Application Report",
                    url:"https://www.ti.com/lit/spracu9",
                    devices:[
                        "F280015x",
                        "F28003x",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                    appNote:true,
                },
            ]
        },
    ],
    "MCBSP":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"C2000 Academy - McBSP",
                    url:"https://dev.ti.com/tirex/local?id=source_c2000_communications_c2000_mcbsp&amp;packageId=C2000-ACADEMY",
                    devices:[
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P65x",
                    ],
                },
                {
                    name:"KeyStone Architecture Multichannel Buffered Serial Port (McBSP)",
                    url:"https://www.ti.com/lit/ug/spruhh0/spruhh0.pdf",
                    devices:[
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P65x",
                    ],
                },
            ]
        },
        {
            category_displayName: "Expert Materials",
            content:[
                {
                    name:"Interfacing the TMS320F2833x to the AIC23B Stereo Audio Codec Application Report",
                    url:"https://ti.com/lit/SPRAAJ2",
                    devices:[
                        "LEGACY",
                    ],
                    appNote:true,
                },
            ]
        },
    ],
    "Memory":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"C2000 Academy - Memory Controller",
                    url:"https://dev.ti.com/tirex/local?id=source_c2000_system_c2000_memory&amp;packageId=C2000-ACADEMY",
                    devices:[
                        "F280013x",
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                },
            ]
        },
    ],
    "PGA":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"An Engineer\u0027s Guide to Designing with Precision Amplifiers",
                    url:"https://www.ti.com/lit/eb/slyy209/slyy209.pdf",
                    devices:[
                        "F28004x",
                        "F28P55x",
                    ],
                },
                {
                    name:"C2000 Academy - PGA",
                    url:"https://dev.ti.com/tirex/local?id=source_c2000_analog_subsystem_c2000_programmable_gain_amplifier&amp;packageId=C2000-ACADEMY",
                    devices:[
                        "F28004x",
                        "F28P55x",
                        "LEGACY",
                    ],
                },
            ]
        },
        {
            category_displayName: "Getting Started Materials",
            content:[
                {
                    name:"Inverting op amp with non-inverting positive reference voltage circuit Application Report",
                    url:"https://www.ti.com/lit/sboa264",
                    devices:[
                        "F28004x",
                        "F28P55x",
                    ],
                    appNote:true,
                },
                {
                    name:"Non-inverting op amp with inverting positive reference voltage circuit Application Report",
                    url:"https://www.ti.com/lit/sboa262",
                    devices:[
                        "F28004x",
                        "F28P55x",
                    ],
                    appNote:true,
                },
            ]
        },
        {
            category_displayName: "Expert Materials",
            content:[
                {
                    name:"AN-20 An Applications Guide for Op Amps Application Report",
                    url:"https://www.ti.com/lit/snoa621",
                    devices:[
                        "F28004x",
                        "F28P55x",
                    ],
                    appNote:true,
                },
                {
                    name:"Using An Op Amp for High-Side Current Sensing Application Report",
                    url:"https://www.ti.com/lit/sboa347",
                    devices:[
                        "F28004x",
                        "F28P55x",
                    ],
                    appNote:true,
                },
            ]
        },
    ],
    "PMBUS":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"C2000 Academy - PMBUS",
                    url:"https://dev.ti.com/tirex/local?id=source_c2000_communications_c2000_pmbus&amp;packageId=C2000-ACADEMY",
                    devices:[
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                },
                {
                    name:"Seven things to know about PMBus",
                    url:"https://www.ti.com/video/5097829453001",
                    video:true,
                },
            ]
        },
        {
            category_displayName: "Getting Started Materials",
            content:[
                {
                    name:"C28x PMBus Communications Stack User\u0027s Guide Application Report",
                    url:"https://dev.ti.com/tirex/explore/node?node=AIS0ctl.bh6PlfjdZFKNiw__gYkahfz__LATEST",
                    appNote:true,
                },
                {
                    name:"Software Implementation of PMBus over I2C for TMS320F2803x Application Report",
                    url:"https://ti.com/lit/SPRABJ6",
                    appNote:true,
                },
            ]
        },
        {
            category_displayName: "Expert Materials",
            content:[
                {
                    name:"9 things you need to know about PMBus Point-of-Load Power",
                    url:"https://www.ti.com/video/4649804908001",
                    video:true,
                },
            ]
        },
    ],
    "ROM":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"Bootloading 101",
                    url:"https://www.ti.com/video/3871889296001",
                    video:true,
                },
                {
                    name:"C2000 Academy - BootROM",
                    url:"https://dev.ti.com/tirex/local?id=source_c2000_system_c2000_boot&amp;packageId=C2000-ACADEMY",
                    devices:[
                        "F280013x",
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                },
            ]
        },
        {
            category_displayName: "Getting Started Materials",
            content:[
                {
                    name:"Secure BOOT On C2000 Device Application Report",
                    url:"https://ti.com/lit/SPRACT3",
                    devices:[
                        "F280013x",
                        "F280015x",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                    appNote:true,
                },
                {
                    name:"TMS320F28004x Boot Features and Configurations Application Report",
                    url:"https://ti.com/lit/SPRACA2",
                    devices:[
                        "F28004x",
                    ],
                    appNote:true,
                },
            ]
        },
        {
            category_displayName: "Expert Materials",
            content:[
                {
                    name:"C2000 Software Controlled Firmware Update Process Application Report",
                    url:"https://www.ti.com/lit/pdf/spracn1",
                    appNote:true,
                },
                {
                    name:"Updating Firmware on Security Enabled TMS320F2837xx or TMS320F2807x Devices Application Report",
                    url:"https://www.ti.com/lit/spraci5",
                    devices:[
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                    ],
                    appNote:true,
                },
            ]
        },
    ],
    "SCI":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"C2000 Academy - SCI",
                    url:"https://dev.ti.com/tirex/local?id=source_c2000_communications_c2000_sci&amp;packageId=C2000-ACADEMY",
                    devices:[
                        "F280013x",
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                },
                {
                    name:"One Minute RS-485 Introduction",
                    url:"https://www.ti.com/video/3870842977001",
                    video:true,
                },
                {
                    name:"RS-232, RS-422, RS-485: What Are the Differences?",
                    url:"https://www.ti.com/video/3869819873001",
                    video:true,
                },
            ]
        },
        {
            category_displayName: "Getting Started Materials",
            content:[
                {
                    name:"[FAQ] My C2000 SCI is not Transmitting and/or Receiving data correctly, how do I fix this?",
                    url:"https://e2e.ti.com/support/microcontrollers/c2000-microcontrollers-group/c2000/f/c2000-microcontrollers-forum/1031947/faq-my-c2000-sci-is-not-transmitting-and-or-receiving-data-correctly-how-do-i-fix-this",
                },
            ]
        },
    ],
    "SDFM":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"C2000 Academy - SDFM",
                    url:"https://dev.ti.com/tirex/local?id=source_c2000_control_peripherals_c2000_sigma_delta_filter&amp;packageId=C2000-ACADEMY",
                    devices:[
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P65x",
                    ],
                },
                {
                    name:"How delta-sigma ADCs work, Part 1 Application Report",
                    url:"https://www.ti.com/lit/slyt423",
                    appNote:true,
                },
                {
                    name:"How delta-sigma ADCs work, Part 2 Application Report",
                    url:"https://www.ti.com/lit/slyt438",
                    appNote:true,
                },
                {
                    name:"Nuts and Bolts of the Delta-Sigma Converter",
                    url:"https://www.ti.com/video/3888145066001",
                    video:true,
                },
                {
                    name:"Sigma Delta Filter Module (SDFM) Training for C2000\u2122 MCUs",
                    url:"https://www.ti.com/video/series/C2000-sigma-delta-filter-modulator.html",
                    video:true,
                },
            ]
        },
        {
            category_displayName: "Getting Started Materials",
            content:[
                {
                    name:"Achieving Better Signal Integrity With Isolated Delta-Sigma Modulators in Motor Drives Application Report",
                    url:"https://www.ti.com/lit/tida033",
                    description:"Critical information for a hardware designer",
                    appNote:true,
                },
                {
                    name:"Using Sigma Delta Filter Module (SDFM) to Measure the Analog Input Signal",
                    url:"https://www.mathworks.com/help/ti-c2000/ug/sdfm-example.html",
                    description:"NOTE: This is a non-TI (third party) site.",
                },
            ]
        },
        {
            category_displayName: "Expert Materials",
            content:[
                {
                    name:"C2000 DesignDRIVE Development Kit for Industrial Motor Control",
                    url:"https://www.ti.com/tool/TMDXIDDK379D",
                    devices:[
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2838x",
                        "F28P65x",
                    ],
                },
                {
                    name:"Clock Edge Delay Compensation With Isolated Modulators Digital Interface to MCUs Application Report",
                    url:"https://www.ti.com/lit/sbaa607",
                    devices:[
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P65x",
                    ],
                    appNote:true,
                },
                {
                    name:"Diagnosing Delta-Sigma Modulator Bitstream Using C2000\u2122 Configurable Logic Block Application Report",
                    url:"https://www.ti.com/lit/SPRAD53",
                    appNote:true,
                },
                {
                    name:"Isolated Current Shunt and Voltage Measurement Kit Application Report",
                    url:"https://www.ti.com/lit/tidu499",
                    appNote:true,
                },
                {
                    name:"Isolated, Shunt-Based Current Sensing Reference Design",
                    url:"https://www.ti.com/tool/TIPD165",
                },
                {
                    name:"Quick Response Control of PMSM Using Fast Current Loop Application Report",
                    url:"https://www.ti.com/lit/spracl1",
                    appNote:true,
                },
                {
                    name:"Single-Phase Inverter Reference Design With Voltage Source and Grid Connected Modes",
                    url:"https://www.ti.com/tool/TIDM-HV-1PH-DCAC",
                    devices:[
                        "F28004x",
                        "F2807x",
                        "F2837xS",
                    ],
                },
                {
                    name:"The case for isolated delta-sigma modulators: Is my system fast enough for short-circuit detection?",
                    url:"https://e2e.ti.com/blogs_/archives/b/precisionhub/archive/2014/11/10/the-case-for-isolated-delta-sigma-modulators-is-my-system-fast-enough-for-short-circuit-detection",
                },
                {
                    name:"Vienna Rectifier-Based Three Phase Power Factor Correction Reference Design Using C2000 MCU",
                    url:"https://www.ti.com/tool/TIDM-1000",
                    devices:[
                        "F280015x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P65x",
                    ],
                },
            ]
        },
    ],
    "SOFTWARE":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"C2000 C28x Migration from COFF to EABI",
                    url:"https://software-dl.ti.com/ccs/esd/documents/C2000_c28x_migration_from_coff_to_eabi.html",
                },
                {
                    name:"C2000 C28x Optimization Guide",
                    url:"https://software-dl.ti.com/C2000/docs/optimization_guide/index.html",
                },
                {
                    name:"C2000 Performance Tips and Tricks ",
                    url:"http://software-dl.ti.com/ccs/esd/documents/c2000_c2000-performance-tips-and-tricks.html",
                },
                {
                    name:"C2000 Software Guide",
                    url:"https://software-dl.ti.com/C2000/docs/software_guide/index.html",
                },
                {
                    name:"CGT Data Blocking C2000",
                    url:"https://software-dl.ti.com/ccs/esd/documents/cgt_data-blocking-c2000.html",
                },
            ]
        },
        {
            category_displayName: "Getting Started Materials",
            content:[
                {
                    name:"C2000 Multicore Development User Guide",
                    url:"https://software-dl.ti.com/C2000/docs/C2000_Multicore_Development_User_Guide/index.html",
                },
                {
                    name:"C28x Context Save and Restore",
                    url:"https://software-dl.ti.com/C2000/docs/c28x_context_save_restore/html/index.html",
                },
                {
                    name:"Development Tool Versions for C2000 Support",
                    url:"https://software-dl.ti.com/C2000/docs/sprac01/html/index.html",
                },
                {
                    name:"Texas Instruments F28002x Peripheral Driver Library",
                    url:"https://software-dl.ti.com/C2000/docs/C2000_driverlib_api_guide/f28002x/html/index.html",
                    devices:[
                        "F28002x",
                    ],
                },
                {
                    name:"Texas Instruments F28004x Peripheral Driver Library",
                    url:"https://software-dl.ti.com/C2000/docs/C2000_driverlib_api_guide/f28004x/html/index.html",
                    devices:[
                        "F28004x",
                    ],
                },
                {
                    name:"Texas Instruments F2807x Peripheral Driver Library",
                    url:"https://software-dl.ti.com/C2000/docs/C2000_driverlib_api_guide/f2807x/html/index.html",
                    devices:[
                        "F2807x",
                    ],
                },
                {
                    name:"Texas Instruments F2837xD Peripheral Driver Library",
                    url:"https://software-dl.ti.com/C2000/docs/C2000_driverlib_api_guide/f2837xd/html/index.html",
                    devices:[
                        "F2837xD",
                    ],
                },
                {
                    name:"Texas Instruments F2837xS Peripheral Driver Library",
                    url:"https://software-dl.ti.com/C2000/docs/C2000_driverlib_api_guide/f2837xs/html/index.html",
                    devices:[
                        "F2837xS",
                    ],
                },
                {
                    name:"Texas Instruments F2838x Peripheral Driver Library",
                    url:"https://software-dl.ti.com/C2000/docs/C2000_driverlib_api_guide/f2838x/html/index.html",
                    devices:[
                        "F2838x",
                    ],
                },
            ]
        },
    ],
    "SPI":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"C2000 Academy - SPI",
                    url:"https://dev.ti.com/tirex/local?id=source_c2000_communications_c2000_spi&amp;packageId=C2000-ACADEMY",
                    devices:[
                        "F280013x",
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                },
                {
                    name:"KeyStone Architecture Serial Peripheral Interface (SPI)",
                    url:"https://www.ti.com/lit/ug/sprugp2a/sprugp2a.pdf",
                    devices:[
                        "F280013x",
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                },
            ]
        },
        {
            category_displayName: "Getting Started Materials",
            content:[
                {
                    name:"SPI: Microcontroller overview",
                    url:"https://www.ti.com/video/6288330712001",
                    devices:[
                        "F280013x",
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                    video:true,
                },
            ]
        },
    ],
    "SYSCTL":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"C2000 MCU JTAG Connectivity Debug Application Report",
                    url:"https://ti.com/lit/SPRACF0",
                    appNote:true,
                },
            ]
        },
        {
            category_displayName: "Getting Started Materials",
            content:[
                {
                    name:"C28x Interrupt Nesting",
                    url:"https://software-dl.ti.com/C2000/docs/c28x_interrupt_nesting/html/index.html",
                },
                {
                    name:"Debugging JTAG",
                    url:"https://software-dl.ti.com/ccs/esd/documents/ccs_debugging_jtag_connectivity_issues.html",
                },
                {
                    name:"Enhancing Device Security by Using JTAGLOCK Feature Application Report",
                    url:"https://ti.com/lit/SPRACS4",
                    appNote:true,
                },
                {
                    name:"Interrupt FAQ for C2000",
                    url:"https://software-dl.ti.com/C2000/docs/c28x_interrupt_faq/html/index.html",
                },
                {
                    name:"XDS Target Connection Guide",
                    url:"https://dev.ti.com/tirex/explore/node?node=AOi9Jj0vmBMJ0KQKaKITgg__FUz-xrs__LATEST",
                },
            ]
        },
        {
            category_displayName: "Expert Materials",
            content:[
                {
                    name:"C2000 CPU Memory Built-In Self-Test Application Report",
                    url:"https://ti.com/lit/SPRACB9",
                    appNote:true,
                },
                {
                    name:"C2000 Memory Power-On Self-Test (M-POST) Application Report",
                    url:"https://ti.com/lit/SPRACI7",
                    appNote:true,
                },
                {
                    name:"Live Firmware Update With Device Reset on C2000 MCUs Application Report",
                    url:"https://ti.com/lit/SPRUIU8",
                    devices:[
                        "F28003x",
                        "F28004x",
                    ],
                    appNote:true,
                },
                {
                    name:"Live Firmware Update Without Device Reset on C2000 MCUs Application Report",
                    url:"https://ti.com/lit/SPRUIU9",
                    devices:[
                        "F28003x",
                        "F28P55x",
                        "F28P65x",
                    ],
                    appNote:true,
                },
                {
                    name:"Programming of External Nonvolatile Memory Using SDFlash for TMS320C28x Devices Application Report",
                    url:"https://ti.com/lit/SPRAAW0",
                    appNote:true,
                },
                {
                    name:"Software Phased-Locked Loop (PLL) Design Using C2000 Microcontrollers Application Report",
                    url:"https://ti.com/lit/SPRABT3",
                    appNote:true,
                },
            ]
        },
    ],
    "Timers":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"C2000 Academy - Timers",
                    url:"https://dev.ti.com/tirex/local?id=source_c2000_system_c2000_timers&amp;packageId=C2000-ACADEMY",
                    devices:[
                        "F280013x",
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                },
            ]
        },
    ],
    "USB":[
        {
            category_displayName: "Foundational Materials",
            content:[
                {
                    name:"C2000 Academy - USB",
                    url:"https://dev.ti.com/tirex/local?id=source_c2000_communications_c2000_usb&amp;packageId=C2000-ACADEMY",
                    devices:[
                        "F280013x",
                        "F280015x",
                        "F28002x",
                        "F28003x",
                        "F28004x",
                        "F2807x",
                        "F2837xD",
                        "F2837xS",
                        "F2838x",
                        "F28P55x",
                        "F28P65x",
                    ],
                },
                {
                    name:"USB Precision Labs",
                    url:"https://www.ti.com/video/series/ti-precision-labs-usb.html",
                    video:true,
                },
            ]
        },
        {
            category_displayName: "Expert Materials",
            content:[
                {
                    name:"High-Speed Interface Layout Guidelines Application Report",
                    url:"https://www.ti.com/lit/spraar7",
                    appNote:true,
                },
                {
                    name:"USB Flash Programming of C2000 Microcontrollers Application Report",
                    url:"https://www.ti.com/lit/spraco7",
                    appNote:true,
                },
            ]
        },
    ],
}