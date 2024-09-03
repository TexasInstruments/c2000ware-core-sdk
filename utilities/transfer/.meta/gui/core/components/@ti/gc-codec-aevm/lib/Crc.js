/**
 *  Copyright (c) 2020, Texas Instruments Incorporated
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
 */
/**
 * CRC
 *
 * @example
 * ```typescript
 * import { CRC } from '<path-to>/gc-codec-aevm/lib/Crc';
 *
 * const crc = new CRC({ polynomial: 7 });
 * crc.checksum([1,2,3]);
 * ```
 *
 * @packageDocumentation
 */
/**
 * Some typical constants used for CRC.
 */
var CRC_POLY;
(function (CRC_POLY) {
    CRC_POLY[CRC_POLY["CRC8"] = 213] = "CRC8";
    CRC_POLY[CRC_POLY["CRC8_CCITT"] = 7] = "CRC8_CCITT";
    CRC_POLY[CRC_POLY["CRC8_DALLAS_MAXIM"] = 49] = "CRC8_DALLAS_MAXIM";
    CRC_POLY[CRC_POLY["CRC8_SAE_J1850"] = 29] = "CRC8_SAE_J1850";
    CRC_POLY[CRC_POLY["CRC_8_WCDMA"] = 155] = "CRC_8_WCDMA";
})(CRC_POLY || (CRC_POLY = {}));
class CRC {
    constructor(crcAttributes) {
        this.crcAttributes = crcAttributes;
        // e.g. new CRC({ polynomial: 7 });
        this.table = this.createTable(crcAttributes.polynomial);
    }
    /**
     * Compute crc of the given input data
     * @param byteArray input data
     * @param initial Optional initial value
     * @returns crc
     */
    checksum(byteArray, initial = 0) {
        let c = initial;
        for (let i = 0; i < byteArray.length; i++) {
            c = this.table[(c ^ byteArray[i]) % 256];
        }
        return c;
    }
    createTable(polynomial) {
        const csTable = [];
        for (let i = 0; i < 256; ++i) {
            let curr = i;
            for (let j = 0; j < 8; ++j) {
                if ((curr & 0x80) !== 0) {
                    curr = ((curr << 1) ^ polynomial) % 256;
                }
                else {
                    curr = (curr << 1) % 256;
                }
            }
            csTable[i] = curr;
        }
        return csTable;
    }
    static getSharedInstance(crcAttributes) {
        // e.g. CRC.getSharedInstance({polynomial: 7, width: 8});
        let result = CRC.sharedInstances.get(crcAttributes.polynomial);
        if (result === undefined) {
            result = new CRC(crcAttributes);
            CRC.sharedInstances.set(crcAttributes.polynomial, result);
        }
        return result;
    }
}
CRC.sharedInstances = new Map();

export { CRC, CRC_POLY };
//# sourceMappingURL=Crc.js.map
