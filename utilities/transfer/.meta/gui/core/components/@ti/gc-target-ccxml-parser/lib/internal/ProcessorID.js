/**
 *  Copyright (c) 2022, Texas Instruments Incorporated
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  *   Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the distribution.
 *  *   Neither the name of Texas Instruments Incorporated nor the names of
 *  its contributors may be used to endorse or promote products derived
 *  from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/* eslint-disable no-console */
var DriverType;
(function (DriverType) {
    DriverType[DriverType["EMU"] = 0] = "EMU";
    DriverType[DriverType["SIM"] = 1] = "SIM";
    DriverType[DriverType["DSK"] = 2] = "DSK";
    DriverType[DriverType["MOD"] = 3] = "MOD";
    DriverType[DriverType["NONDEBUG"] = 4] = "NONDEBUG";
    DriverType[DriverType["ROUTER"] = 5] = "ROUTER";
})(DriverType || (DriverType = {}));
export class ProcessorID {
    constructor(procID = 0) {
        this.procID = procID;
    }
    getFamily() {
        return (this.procID >> ProcessorID.SHIFT_FAMILY) & ProcessorID.MASK_FAMILY;
    }
    setFamily(family) {
        this.procID = (this.procID & ~(ProcessorID.MASK_FAMILY << ProcessorID.SHIFT_FAMILY)) | ((family & ProcessorID.MASK_FAMILY) << ProcessorID.SHIFT_FAMILY);
    }
    getSubFamily() {
        return (this.procID >> ProcessorID.SHIFT_SUBFAMILY) & ProcessorID.MASK_SUBFAMILY;
    }
    setSubFamily(subFamily) {
        this.procID = (this.procID & ~(ProcessorID.MASK_SUBFAMILY << ProcessorID.SHIFT_SUBFAMILY)) | ((subFamily & ProcessorID.MASK_SUBFAMILY) << ProcessorID.SHIFT_SUBFAMILY);
    }
    getRevision() {
        return (this.procID >> ProcessorID.SHIFT_REV) & ProcessorID.MASK_REV;
    }
    setRevision(revision) {
        this.procID = (this.procID & ~(ProcessorID.MASK_REV << ProcessorID.SHIFT_REV)) | ((revision & ProcessorID.MASK_REV) << ProcessorID.SHIFT_REV);
    }
    getType() {
        return (this.procID >> ProcessorID.SHIFT_TYPE) & ProcessorID.MASK_TYPE;
    }
    setType(type) {
        this.procID = (this.procID & ~(ProcessorID.MASK_TYPE << ProcessorID.SHIFT_TYPE)) | ((type & ProcessorID.MASK_TYPE) << ProcessorID.SHIFT_TYPE);
    }
    getProcessorID() {
        return this.procID;
    }
    setProcessorID(newProcID) {
        this.procID = newProcID;
    }
    isNonDebug() {
        return (this.getType() === DriverType.NONDEBUG);
    }
    isRouter() {
        return (this.getType() === DriverType.ROUTER);
    }
    toString() {
        let cstrOut = '';
        // process the family
        const family = this.getFamily();
        let subFamily = this.getSubFamily();
        if (family === 240) {
            cstrOut += `${ProcessorID.ICEPick}A${subFamily}`;
        }
        else if (family === 100) { // DRP Script processors have the family 100
            cstrOut += `${ProcessorID.DRP_SCRIPT}${subFamily}`;
        }
        else if (family === 430) { // MSP430
            cstrOut += ProcessorID.MSP430;
        }
        else if (family === 470 && subFamily === 0) {
            cstrOut += ProcessorID.ARM;
        }
        else if (family === 470 && subFamily <= 3) { // arm devices
            cstrOut += `${ProcessorID.ARM}${subFamily * 2 + 5}`;
        }
        else if (family === 470 && subFamily === 13) {
            cstrOut += `${ProcessorID.CORTEX}R`;
        }
        else if (family === 470 && (subFamily === 10 || subFamily === 14 || subFamily === 0x33)) { // cortexM devices
            cstrOut += `${ProcessorID.CORTEX}M`;
        }
        else if (family === 470 && [0x5, 0x7, 0xC, 0x9, 0x12, 0x15, 0x17, 0x32, 0x35, 0x53, 0x57, 0x72, 0x73].includes(subFamily)) { // cortexA devices
            cstrOut += `${ProcessorID.CORTEX}A`;
        }
        else if (family === 700) {
            cstrOut += ProcessorID.ARP32;
        }
        else {
            cstrOut += `${ProcessorID.TMS}${family}`;
            // TMS470R (RISC), TMS370P (MCU), and TMS320C (DSP)
            cstrOut += `${family === 470 ? 'R' : family === 370 ? 'P' : 'C'}`;
            // hide 56xx and 29xx under 55xx and 28xx
            if (family === 320) {
                if (subFamily === 0x56)
                    subFamily = 0x55;
                if (subFamily === 0x29)
                    subFamily = 0x28;
            }
            // process the sub-family
            let bFoundNonZero = false;
            for (let i = 2; i >= 0; i--) {
                // grab digit at hex position i
                const nDigit = (subFamily >> (i * 4)) & 0xF;
                // display all non-leading zeros and leading zeros for MCU's
                if (nDigit === 0) {
                    if (bFoundNonZero || family === 370)
                        cstrOut += '0';
                }
                else if (nDigit >= 0x1 && nDigit <= 0x9) {
                    cstrOut += '0' + nDigit;
                    bFoundNonZero = true;
                }
                else if (nDigit === 0xF) {
                    cstrOut += 'X';
                    bFoundNonZero = true;
                }
                else {
                    cstrOut += 'A' + (nDigit - 0xA);
                    bFoundNonZero = true;
                }
            }
            // process the revision
            const revision = this.getRevision();
            if (subFamily >= 0x001 && subFamily <= 0x009) { // single-digit revision
                if (revision >= 0 && revision <= 9)
                    cstrOut += '0' + revision;
                else
                    cstrOut += 'X';
            }
            else { // two-digit revision
                if (revision < 10)
                    cstrOut += '0';
                if (revision < 100) // ##
                    cstrOut += revision;
                else if (revision < 110) // #x
                    cstrOut += (revision - 100) + 'X';
                else if (revision < 120) // x#
                    cstrOut += 'X' + (revision - 110);
                else // xx
                    cstrOut += 'XX';
            }
        }
        return cstrOut.toString();
    }
    toStringProjectType() {
        const saveProcId = this.procID;
        let mask;
        const family = this.getFamily();
        if (family === 240) {
            return 'ICEPick';
        }
        else if (family === 100) {
            return 'DRP_SCRIPT';
        }
        else if (family === 192) {
            const result = toString();
            if (result === 'TMS192C2026')
                return 'PRU';
            else if (result === 'TMS192C2006' || result === 'TMS192C2007')
                return 'CLA';
            else
                mask = 0;
        }
        else if (family === 320) {
            const subFamily = this.getSubFamily();
            if (subFamily < 0x50 || subFamily >= 0x5F) {
                // Except for TMS320C5000, the project type is the family and subFamily with last digit changed to 0.
                mask = 0xF << ProcessorID.SHIFT_SUBFAMILY | ProcessorID.MASK_REV << ProcessorID.SHIFT_REV;
            }
            else {
                // Use both the family and subFamily to distinguish between C5400 and C5500 projects.
                mask = ProcessorID.MASK_REV << ProcessorID.SHIFT_REV;
            }
        }
        else {
            // for ARM or MSP430, the family is used for the project type
            mask = ProcessorID.MASK_SUBFAMILY << ProcessorID.SHIFT_SUBFAMILY | ProcessorID.MASK_REV << ProcessorID.SHIFT_REV;
        }
        this.procID = this.procID & (~mask);
        const result = toString();
        this.procID = saveProcId;
        if (result.startsWith('TMS320')) {
            return result.substring(6);
        }
        return result;
    }
    parse(processorName) {
        this.procID = 0;
        if (processorName.startsWith(ProcessorID.ICEPick)) {
            this.setFamily(240);
            this.setSubFamily(processorName.charCodeAt(ProcessorID.ICEPick.length) - 'A'.charCodeAt(0));
        }
        else if (processorName.startsWith(ProcessorID.DRP_SCRIPT)) {
            this.setFamily(100);
            this.setSubFamily(Number.parseInt(processorName.substring(ProcessorID.DRP_SCRIPT.length), 10));
        }
        else if (processorName.startsWith(ProcessorID.MSP430)) {
            this.setFamily(430);
        }
        else if (processorName.startsWith(ProcessorID.ARM)) {
            this.setFamily(470);
            const subFamily = Number.parseInt(processorName.substring(ProcessorID.ARM.length), 10);
            this.setSubFamily((subFamily - 5) / 2);
        }
        else if (processorName.startsWith(ProcessorID.CORTEX)) {
            this.setFamily(470);
            const subFamilyText = processorName.substring(ProcessorID.CORTEX.length).trim();
            if (subFamilyText.startsWith('A'))
                this.setSubFamily(12);
            else if (subFamilyText.startsWith('R'))
                this.setSubFamily(13);
            else if (subFamilyText.startsWith('M'))
                this.setSubFamily(14);
            else
                this.setSubFamily(0);
        }
        else if (processorName.startsWith(ProcessorID.ARP32)) {
            this.setFamily(700);
            this.setSubFamily(0x40);
        }
        else if (processorName.startsWith(ProcessorID.TMS)) {
            if (processorName.startsWith(ProcessorID.TMS470R)) {
                this.setFamily(470);
                processorName = processorName.substring(ProcessorID.TMS470R.length);
            }
            else if (processorName.startsWith(ProcessorID.TMS370P)) {
                this.setFamily(370);
                processorName = processorName.substring(ProcessorID.TMS370P.length);
            }
            else if (processorName.startsWith(ProcessorID.TMS320C)) {
                this.setFamily(320);
                processorName = processorName.substring(ProcessorID.TMS320C.length);
            }
            else {
                this.setFamily(Number.parseInt(processorName.substring(ProcessorID.TMS.length, ProcessorID.TMS.length + 3)));
                processorName = processorName.substring(ProcessorID.TMS.length + 3);
            }
            // read sub family and revision as hexadecimal with 'x' representing 'F'.
            processorName = processorName.toUpperCase();
            let revision = Number.parseInt(processorName.split('X').join('F'), 16);
            // now try to figure out where the division is  between sub family and revision
            if (revision <= 0x9F) {
                // single digit sub-family and revision.
                this.setSubFamily(revision >> 4);
                this.setRevision(revision & 0xF);
            }
            else { // two digit revision
                this.setSubFamily(revision >> 8);
                revision = revision & 0xFF;
                if (revision === 0xFF) {
                    this.setRevision(revision);
                }
                else if (revision >= 0xF0) {
                    this.setRevision(110 + revision - 0xF0);
                }
                else if ((revision & 0xF) === 0xF) {
                    this.setRevision(100 + (revision >> 4));
                }
                else {
                    // reinterpret hex as decimal
                    this.setRevision((revision >> 4) * 10 + (revision & 0xF));
                }
            }
        }
    }
    static test() {
        let passed = true;
        const family = [240, 100, 470, 370, 320, 430, 700];
        const subFamily = [1, 2, 3, 4, 5, 7, 9, 10, 11, 0x15, 0x54, 0x55, 0x56, 0x62, 0x64, 0x27, 0x24, 0x60, 0x50, 0x52, 0x6F, 0x5f, 0x2f];
        const revision = [0, 1, 2, 9, 10, 11, 99, 100, 101, 109, 110, 111, 119, 120, 121, 256];
        const procID = new ProcessorID();
        for (let i = family.length; i-- > 0;) {
            for (let j = subFamily.length; j-- > 0;) {
                for (let k = revision.length; k-- > 0;) {
                    procID.setFamily(family[i]);
                    procID.setSubFamily(subFamily[j]);
                    procID.setRevision(revision[k]);
                    const name = procID.toString();
                    procID.parse(name);
                    const nameAgain = procID.toString();
                    if (name.localeCompare(nameAgain) !== 0) {
                        const errorMessage = `Test Case Failed: family=${family[i]}, subFamily=${subFamily[j]}, revision=${revision[k]} name should be ${name} but was ${nameAgain}`;
                        console.error(errorMessage);
                        passed = false;
                    }
                    const familyGroup = procID.toStringProjectType();
                    let shouldBe = '';
                    if (family[i] === 470) {
                        shouldBe = 'ARM';
                    }
                    else if (family[i] === 320 && subFamily[j] > 15) {
                        if (subFamily[j] >= 0x50 && subFamily[j] < 0x5F) {
                            if (subFamily[j] !== 0x56) {
                                shouldBe = `C${subFamily[j].toString(16)}00`;
                            }
                            else {
                                shouldBe = 'C5500';
                            }
                        }
                        else {
                            shouldBe = `C${subFamily[j] >>> 4}000`;
                        }
                    }
                    else if (family[i] === 430) {
                        shouldBe = 'MSP430';
                    }
                    else if (family[i] === 240) {
                        shouldBe = 'ICEPick';
                    }
                    else if (family[i] === 100) {
                        shouldBe = 'DRP_SCRIPT';
                    }
                    if (shouldBe.length > 0 && shouldBe.localeCompare(familyGroup) !== 0) {
                        const errorMessage = `Test Case Failed: family=${family[i]}, subFamily=${subFamily[j]}, revision=${revision[k]} family group should be ${shouldBe} but was ${familyGroup}`;
                        console.error(errorMessage);
                        passed = false;
                    }
                }
            }
        }
        if (passed) {
            console.log('Test Cases Passed');
        }
    }
}
ProcessorID.BITS_TYPE = 3;
ProcessorID.BITS_REV = 7;
ProcessorID.BITS_SUBFAMILY = 12;
ProcessorID.BITS_FAMILY = 10;
ProcessorID.MASK_TYPE = (1 << ProcessorID.BITS_TYPE) - 1;
ProcessorID.MASK_REV = (1 << ProcessorID.BITS_REV) - 1;
ProcessorID.MASK_SUBFAMILY = (1 << ProcessorID.BITS_SUBFAMILY) - 1;
ProcessorID.MASK_FAMILY = (1 << ProcessorID.BITS_FAMILY) - 1;
ProcessorID.SHIFT_TYPE = 0;
ProcessorID.SHIFT_REV = ProcessorID.SHIFT_TYPE + ProcessorID.BITS_TYPE;
ProcessorID.SHIFT_SUBFAMILY = ProcessorID.SHIFT_REV + ProcessorID.BITS_REV;
ProcessorID.SHIFT_FAMILY = ProcessorID.SHIFT_SUBFAMILY + ProcessorID.BITS_SUBFAMILY;
ProcessorID.ICEPick = 'ICEPick_';
ProcessorID.DRP_SCRIPT = 'DRP_SCRIPT_';
ProcessorID.TMS470R = 'TMS470R';
ProcessorID.TMS370P = 'TMS370P';
ProcessorID.TMS320C = 'TMS320C';
ProcessorID.TMS = 'TMS';
ProcessorID.MSP430 = 'MSP430';
ProcessorID.ARM = 'ARM';
ProcessorID.CORTEX = 'Cortex ';
ProcessorID.ARP32 = 'ARP32';
//# sourceMappingURL=ProcessorID.js.map