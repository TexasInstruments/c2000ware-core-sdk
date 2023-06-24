/*
 * Copyright (c) 2019-2020, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*
 *  ======== LED.syscfg.js ========
 */

"use strict";
let Common   = system.getScript("/driverlib/Common.js");

/* generic configuration parameters for LED instances */
let config = [

];

function _getPinResources(inst)
{
    let mod;
    let pin;

    mod = system.getScript("/driverlib/gpio.js");
    pin = mod._getPinResources(inst.gpioPin);

    return (pin);
}


/*
 *  ========= filterHardware ========
 *  param component - hardware object describing signals and
 *                    resources
 *
 *  returns Boolean indicating whether or not to allow the component to
 *           be assigned to an instance's $hardware config
 */
function filterHardware(component)
{
    if (component.type) {
        if (Common.typeMatches(component.type, ["LED"])) {
            return (true);
        }
    }
    return (false);
}

/*
 *  ======== validate ========
 *  Validate this inst's configuration
 *
 *  param inst       - LED instance to be validated
 *  param validation - object to hold detected validation issues
 */
function validate(inst, validation)
{
    
}

/*
 *  ======== moduleInstances ========
 *  Add a pwm or gpio instance to the module depending on if the LED is
 *  dimmable or not.
 */
function moduleInstances(inst)
{
    
    let devInstance;
    devInstance = {
        displayName: "GPIO",
        name: "gpio",
        description: "This LED is driven by a GPIO",
        moduleName: "/driverlib/gpio.js",
        args: {
            $name: inst.$name + "_GPIO"
        },
        requiredArgs: {
            direction : "GPIO_DIR_MODE_OUT"
        }
    };
    devInstance.hardware = inst.$hardware;
    return ([devInstance]);
}

/*
 *  ======== onHardwareChanged ========
 *  Handle new hardware selection
 *
 *  @param inst - LED instance to be validated
 *  @param ui   - object with properties for each configurable whose value
 *                is an object that allows us to control the GUI display of
 *                the configurable (hidden, readonly, ...)
 */
function onHardwareChanged(inst, ui)
{

}

/*
 *  ======== base ========
 *  Define the base properties and methods
 */
let base = {
    displayName: "LED",
    description: "LED Driver",
    longDescription: "",
    defaultInstanceName: "myBoardLED",

    config: config,

    validate: validate,
    moduleInstances: moduleInstances,
    filterHardware: filterHardware,

    /* make GUI changes in response to HW model changes */
    onHardwareChanged: onHardwareChanged,

    templates: {
        boardc: "/driverlib/board_components/led/led.board.c.xdt",
        boardh: "/driverlib/board_components/led/led.board.h.xdt"
    },

    _getPinResources: _getPinResources
};

exports = base;
