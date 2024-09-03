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
 *
 */
/**
 * `CssUtils` CSS utility functions.
 *
 * @example
 * ```typescript
 * import { CssUtils } from '<path-to>/gc-widget-base/lib/CssUtils';
 *
 * CssUtils.isCSSHex('fefefe');
 *
 * @packageDocumentation
 */
class CssUtils {
    /**
     * Returns true if the the string given is a properly formed CSS hex value.
     *
     * @param {string} value the supposed CSS hex string
     * @returns {boolean}
     */
    static isCSSHex(value) {
        return (/^#(?:[a-f\d]{3}){1,2}$/i).test(value);
    }
    /**
     * Returns true if the the string given is a properly formed CSS RGB value.
     *
     * @param {string} value the supposed CSS RGB string
     * @returns {boolean}
     */
    static isCSSRgb(value) {
        return (/rgb\((\d{1,3}),(\d{1,3}),(\d{1,3})\)/).test(value);
    }
    /**
     * Convert a CSS Hex string value to its RGB equivalent in a number array, split into the red, green and blue values.
     *
     * @param {string} hex A CSS Hex color
     * @returns {number[]} the RGB values [Red: number, Green: number, Blue: number]
     */
    static CSSHexToRgb(hex) {
        return (hex
            .replace(/^#?([a-f\d])([a-f\d])([a-f\d])$/i, (_m, r, g, b) => '#' + r + r + g + g + b + b)
            .substring(1)
            .match(/.{2}/g) || []).map(x => parseInt(x, 16));
    }
}

export { CssUtils };
//# sourceMappingURL=CssUtils.js.map
