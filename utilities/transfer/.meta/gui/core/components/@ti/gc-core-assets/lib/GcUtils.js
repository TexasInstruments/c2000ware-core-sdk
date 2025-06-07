/**
 *  Copyright (c) 2019, 2024 Texas Instruments Incorporated
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
/* eslint-disable @typescript-eslint/no-explicit-any */
/**
* Helper class with static methods for bit field manipulation.
*/
class BitField {
    /**
    * Returns a bit mask with the bits from startBit to stopBit set to 1
    * and all other bits set to 0.  This only works for up to 52-bit integers.
    *
    * @param startBit lsb of the mask
    * @param stopBit msb of the mask
    * @returns mask value
    */
    static getMask(startBit, stopBit) {
        return Number((1n << BigInt(stopBit + 1)) - (1n << BigInt(startBit)));
    }
    /**
    * Returns the field value from within a larger numeric value.  The mask is used to define which bits are part of the field.
    * The shift is optional and is applied directly to the field before returning it.  Typically the shift is equivalent to the lsb of the mask.
    * If a negativeBit is provided, then the result will be a signed integer, otherwise an unsigned value will always be returned.
    * The negativeBit also represents the mask for the sign bit, and should equal the most significant bit of the mask value.  This only works for
    * up to 52-bit integers.
    *
    * @param dataValue the larger numeric value from which the field is to be retrieved
    * @param mask value for masking out the field from within the larger numeric value
    * @param shift number of times to shift the resulting field to the right, typically to remove zeros created with the mask
    * @param negativeBit if specified this represent the mask for the sign bit, and the return value will be signed accordingly; otherwise an unsigned value is always returned
    * @returns the value of the field after being masked and shifted to the right.
    */
    static readField(dataValue, mask, shift = 0, negativeBit) {
        const shiftBig = BigInt(shift);
        let result = Number((BigInt(dataValue) & BigInt(mask)) >> shiftBig);
        if (negativeBit) {
            if (shift) {
                negativeBit = Number(BigInt(negativeBit) >> shiftBig);
            }
            if (result >= negativeBit) {
                result = result - 2 * negativeBit;
            }
        }
        return result;
    }
    /**
    * Sets a field value within a larger numeric value, without modifying the bits outside the field.  The mask is used to define
    * which bits are part of the field, and which bits should not be touched.  The return value is always unsigned.  The field value
    * to set may be signed or unsigned since the sign extension will be masked off in either event.
    * The shift is applied to the field value before being masked into the final result.  This is typically set to the number of
    * least significant zero bit in the mask value, and is used to align the field value with the mask value.  This only works for
    * up to 52-bit integers.
    *
    * @param dataValue the larger numeric value containing the field that is to be replaced with the one provided
    * @param mask value indicating mask bits for the dataValue that define which bits will be replaced in the returned value
    * @param shift number of times to shift the new field value to the left, before being or'ed into the dataValue
    * @param bitFieldValue the new bit field value to replace the old field value in the input dataValue
    * @returns the input dataValue with the field defined by the mask replaced with the new bitFieldValue input.
    */
    static writeField(dataValue, mask, shift, bitFieldValue) {
        bitFieldValue = Math.round(bitFieldValue);
        const bigMask = BigInt(mask);
        const result = Number(((BigInt(bitFieldValue) << BigInt(shift)) & bigMask) | (BigInt(dataValue) & ~bigMask));
        return result >= 0 ? result : 0x10000000000000 + result;
    }
}
// camel to dash and dash to camel conversion helpers
const fromCamelCaseRegEx = /([A-Z])/g;
const toCamelCaseRegEx = /-([a-z])/g;
class GcUtils {
    /**
     * Returns the root window object.
     */
    static get rootWin() {
        let root = undefined;
        if (typeof window !== 'undefined') {
            while (root !== window.parent)
                root = window.parent;
        }
        return root;
    }
    /**
     * Returns the application name.
     */
    static get appName() {
        if (GcUtils.isNodeJS) {
            return 'NodeJS';
        }
        else {
            const pathname = window.location.pathname;
            /* Gallery App */
            if (pathname.match(/\/gallery\/view\/.*\//)) {
                return pathname.split('/gallery/view/')[1].split('/')[1];
                /* CCS GC App */
            }
            else if (pathname.match(/\/guicomposer\/.*\//)) {
                return pathname.split('/')[2];
                /* GC Designer Preview */
            }
            else if (pathname.match(/\/gc\/preview\/.*/)) {
                return pathname.split('/gc/preview/default/')[1].split('/')[0];
                /* Component Demo */
            }
            else if (pathname.match(/\/v3\/components\/@ti\/.*\/demo\//)) {
                return pathname.split('/')[4];
            }
            else if (pathname.match(/\/gc\/v3\/components\/index.html/)) {
                return 'components';
                /* GC Designer */
            }
            else if (pathname.indexOf('/gc') === 0) {
                return 'GCDesigner';
                /* GC Designer Editor */
            }
            else if (document.title) {
                return document.title;
                /* others */
            }
            else {
                return pathname.split('/')[0] || 'unknown';
            }
        }
    }
    /**
     * Returns `true` if the application is running in the GC Designer preview;
     */
    static get isInPreview() {
        return GcUtils.rootWin && GcUtils.rootWin.location.pathname.indexOf('/gc/preview') === 0;
    }
    /**
     * Returns `true` if the application is running in the GC Designer.
     */
    static get isInDesigner() {
        if (this.isNodeJS) {
            return false;
        }
        /*
         * We can't use appName to check, the iframe used by the designer editor doesn't have
         * a valid path to use for determining if running within the designer context.
         *
         * TODO: use meta or set a global variable with the designer index.html
         */
        return GcUtils.rootWin && GcUtils.rootWin.location.pathname.indexOf('/gc') === 0
            && GcUtils.rootWin.location.pathname.indexOf('/gc/preview') !== 0
            && !GcUtils.rootWin.location.pathname.match(/\/v3\/components\/@ti\/.*\/demo\//)
            && !GcUtils.rootWin.location.pathname.match(/\/v3\/components\/index.html/);
    }
    /**
     * Returns `true` if the application is running in the cloud environment.
     */
    static get isCloud() {
        return !GcUtils.isCCS && !GcUtils.isNW && !GcUtils.isElectron && !this.isNodeJS && (location && location.hostname.indexOf('127.0.0.1') !== 0);
    }
    /**
     * Returns `true` if the application is running in the mobile environment.
     */
    static get isMobile() {
        return navigator && (navigator.app || navigator.device);
    }
    /**
     * Returns `true` if the application is running in the Node Webkit environment.
     */
    static get isNW() {
        return (typeof window !== 'undefined') &&
            (typeof window.process !== 'undefined') &&
            (typeof window.process.versions !== 'undefined') &&
            !!window.process.versions['node-webkit'];
    }
    /**
     * Returns `true` if the application is running in the Electron environment.
     */
    static get isElectron() {
        // Detect electron exist in the process object
        if (typeof window !== 'undefined' && typeof window.process !== 'undefined' && typeof window.process.versions !== 'undefined' && !!window.process.versions['electron']) {
            return true;
        }
        // Detect the user agent when the `nodeIntegration` option is set to false
        if (typeof navigator !== 'undefined' && typeof navigator.userAgent === 'string' && navigator.userAgent.indexOf('Electron') >= 0) {
            return true;
        }
        return false;
    }
    /**
     * Returns `true` if the application is running in the NodeJS environment.
     */
    static get isNodeJS() {
        return !GcUtils.isNW && !GcUtils.isElectron &&
            (typeof process !== 'undefined') &&
            (typeof process.versions !== 'undefined') &&
            !!process.versions['node'];
    }
    /**
     * Returns `true` if the application is running in the Code Composer Studio environment.
     */
    static get isCCS() {
        return ((typeof navigator !== 'undefined') &&
            (typeof navigator.userAgent !== 'undefined') &&
            (navigator.userAgent.indexOf('CCStudio') !== -1)) || GcUtils.isTheia;
    }
    /**
     * Returns `true` if the application nis running in the CCS-Theia environment.
     */
    static get isTheia() {
        // @ts-ignore
        return GcUtils.rootWin && typeof GcUtils.rootWin['theia'] !== 'undefined';
    }
    /**
     * The relative path to the root of the runtime directory.  This only works when running in NodeJS.
     */
    static get runtimeRoot() {
        if (GcUtils.isNodeJS) {
            /*
             * Sets runtimeRoot in the following cases
             *    Running from a standalone package
             *    Running from source
             */
            // eslint-disable-next-line @typescript-eslint/no-var-requires
            const fs = require('fs');
            let runtimeRoot = '../../../../../../runtime';
            if (fs.existsSync(__dirname + '/../../../runtime')) {
                runtimeRoot = '../../../runtime';
            }
            return runtimeRoot;
        }
        else if (GcUtils.isNW) {
            // eslint-disable-next-line @typescript-eslint/no-var-requires
            const path = require('path');
            let execPath = process.execPath;
            if (GcUtils.OS === 'osx') {
                execPath = execPath.slice(0, execPath.indexOf('nwjs.app'));
                execPath += '/../../';
            }
            else {
                execPath += '/../../../';
            }
            return path.join(path.normalize(execPath), 'runtime');
        }
        throw Error('runtimeRoot is only available for NodeJS, or NodeWebkit');
    }
    /**
     * The relative path to the root of the GC app.
     */
    static getApplicationRoot(projectName) {
        if (GcUtils.isNW) {
            if (GcUtils.isInPreview || GcUtils.isInDesigner) {
                return GcUtils.runtimeRoot + `/../workspace/${projectName}`;
            }
            return GcUtils.runtimeRoot + `/../${projectName}`;
        }
        throw Error('applicationRoot is only available for NodeWebkit');
    }
    /**
     * Helper method to map relative paths to the application server to URL.  This method is not available for NodeJS, where
     * there is no concept of an application root.
     * If the relative path points starts with workspace, it will be converted to absolute URL starting with /workspaceserver/app/Default/.
     * Otherwise the relative path is unchanged.
     *
     * @param relativePath path relative to the application's root
     * @param getProjectName asynchronous method to retrieve the name of the project if necessary.
     */
    static async resolveApplicationRelativePath(relativePath, getProjectName) {
        if (GcUtils.isNodeJS) {
            throw Error('resolveApplicationRelativePath is not available for NodeJS');
        }
        if (relativePath.startsWith('./workspace/') || relativePath.startsWith('workspace/')) {
            const pos = relativePath.startsWith('./') ? './workspace/'.length : 'workspace/'.length;
            relativePath = relativePath.substring(pos);
            const projectName = await getProjectName();
            return `/workspaceserver/app/Default/${projectName}/${relativePath}`;
        }
        return relativePath;
    }
    /**
     * Returns the current OS.
     */
    static get OS() {
        if (navigator.appVersion.indexOf('Mac') !== -1) {
            return 'osx';
        }
        else if (navigator.appVersion.indexOf('Win') !== -1) {
            return 'win';
        }
        else {
            return 'linux';
        }
    }
    /**
     * The path helper object.
     */
    static get path() {
        return {
            basename: (url) => {
                const tmp = url.replace(new RegExp('\\\\', 'g'), '/');
                const segments = tmp.split('/');
                return segments[tmp.length - 1];
            },
            // For ES6 module, prefer rest parameters over arguments object.
            // see https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Functions/arguments
            join: (...theArgs) => {
                let result = theArgs[0];
                for (let i = 1, j = theArgs.length; i < j; i++) {
                    if (result.length > 0) {
                        result += `/${theArgs[i]}`;
                    }
                    else {
                        result = theArgs[i];
                    }
                }
                return result;
            }
        };
    }
    /**
     * Converts the input from camel case to dash case.
     *
     * @param input the input value
     * @return the dash case string value
     */
    static camelToDashCase(input) {
        return input.replace(fromCamelCaseRegEx, '-$1').toLowerCase();
    }
    /**
     * Converts the input from dash case to camel case.
     *
     * @param input the input value
     * @returns the camel case string value
     */
    static dashToCamelCase(input) {
        return input.replace(toCamelCaseRegEx, m => m[1].toUpperCase());
    }
    /**
    * Helper function to convert numeric input in the form of a number or a string into a number.
    * JSon files do not support hexadecimal by default, so hex values must be
    * entered as strings. This function will aide in converting the values back to a number.
    *
    * @param value an optional numeric value in the form of either a number or a string
    * @returns the numeric value of the input, or undefined if the input is blank, or NaN if the input string could not be converted to a number.
    */
    static string2value(value) {
        let result;
        if (typeof value === 'string') {
            value = value.trim();
            if (value.indexOf('"') === 0 || value.indexOf('\'') === 0) {
                // literal string - remove quotes
                value = value.substring(1, value.length - 1);
            }
            if (value.toLowerCase() === 'true') {
                result = 1;
            }
            else if (value.toLowerCase() === 'false') {
                result = 0;
            }
            else if (value.startsWith('-0x')) {
                result = parseInt(value);
            }
            else {
                result = +value;
            }
        }
        else {
            result = value;
        }
        return result;
    }
    /**
    * Helper function to convert boolean input in the form of a number or a string into a boolean.
    * JSon files sometimes use "1" and "0" to represent boolean values, even though boolean types are supported.
    * This helper function is used when parsing .json files to help convert as many non boolean values to boolean as possible.
    *
    * @param value an optional boolean value that is either in the form of a boolean, a number or a string
    * @returns the boolean value of the input, and false if the value was undefined.
    */
    static string2boolean(value) {
        if (typeof value === 'string') {
            value = this.string2value(value);
        }
        if (typeof value === 'number') {
            return value !== 0;
        }
        return value ? true : false; // need this to convert undefined to false.
    }
    /**
    * Convert an array of bytes into a number.
    *
    * @param bytes an array of bytes
    * @param endian an optional endianness, of choices 'little' or 'big'. Default is 'little'
    * @returns the number.
    */
    static bytesToValue(bytes, endian) {
        let value = 0;
        const byteSize = bytes.length;
        if (endian === 'big') {
            for (let b = 0; b < byteSize; b++) {
                value = (value * 256) + (bytes[b] & 0xff);
            }
        }
        else { // (endian === 'little')
            for (let b = byteSize; --b >= 0;) {
                value = (value * 256) + (bytes[b] & 0xff);
            }
        }
        return value;
    }
    /**
     * Returns true if the value given is a finite number or a string representation of one.
     * @param value number
     */
    static isNumber(value) {
        return Number.isFinite(value) || (Number.isFinite(+value) && typeof value === 'string');
    }
    /**
     * Convert a value into bytes using big endianness.
     *
     * @param array an in-place array for storing the converted bytes
     * @param size byte size of a given value
     * @param value the given value
     * @param offset an offset in array to store the converted bytes
     */
    static setBytes(array, size, value, offset) {
        const ofs = offset ?? 0;
        for (let i = size; i-- > 0;) {
            array[ofs + i] = value & 0xff;
            value = Number(BigInt(value) >> 8n);
        }
    }
    /**
     * Convert a value into bytes using little endianness.
     *
     * @param array an in-place array for storing the converted bytes
     * @param size byte size of a given value
     * @param value the given value
     * @param offset an offset in array to store the converted bytes
     */
    static setBytesLSB(array, size, value, offset) {
        const ofs = offset ?? 0;
        for (let i = 0; i < size; i++) {
            array[ofs + i] = value & 0xff;
            value = Number(BigInt(value) >> 8n);
        }
    }
    /**
     * Compute parity bit from a given number.
     *
     * @param data the given number
     * @param bits bit size of the given number
     * @returns the parity.
     */
    static computeParity(data, bits = 8) {
        let parity = 0n;
        data = BigInt(data);
        for (let i = 0; i < bits; i++) {
            parity = parity ^ (data & 1n);
            data = data >> 1n;
        }
        return Number(parity);
    }
    /**
     * Parse and validate a numeric property.
     *
     * @param message the name of the numeric property
     * @param value the property value to be parsed
     * @param min optional minimum number
     * @param max optional maximum number
     * @returns the number.
     */
    static parseNumberProperty(message, value, min, max) {
        const result = +value;
        const theValueForEntry = `The value ${value} for entry ${message}`;
        if (isNaN(result)) {
            throw Error(`${theValueForEntry} is not a number.`);
        }
        if (min && result < min) {
            throw Error(`${theValueForEntry} must be greater than ${min}.`);
        }
        if (max && result > max) {
            throw Error(`${theValueForEntry} must be less than ${max}.`);
        }
        return result;
    }
    /**
     * Parse and map a string property to a numeric value.
     *
     * @param message the name of the string property
     * @param value the string value to be parsed
     * @param valueMap a map of property values that maps a string value to a numeric value
     * @returns the numeric value corresponds to the string value.
     */
    static parseStringProperty(message, value, valueMap) {
        const stringValue = ('' + value).toLowerCase();
        if (stringValue in valueMap) {
            return valueMap[stringValue];
        }
        else {
            message = `The value ${value} for entry ${message} is not supported. Valid entries are`;
            let delimiter = ' "';
            let lastOption;
            for (const option in valueMap) {
                if (lastOption) {
                    message = message + delimiter + lastOption;
                    delimiter = '", "';
                }
                lastOption = option;
            }
            throw Error(`${message}", or "${lastOption}".`);
        }
    }
    /**
     * Parse a string representing an array of values separated by one of a set of possible of delimiters.  If there is
     * ambiguity between which delimiter to use, the last character in the string can be set to a delimiter to
     * force that delimiter to be used.  For example, 1,000,000|2,000,000|3,000,000|.  Here we explicitly use the pipe character
     * instead of the comma as the delimiter.  If the last character is not a delimiter, then the delimiter that occurs the most
     * will be used.  In the example above, that would be the comma.
     *
     * @param text the string property value to be parsed as an array, or if the property is already an Array it will be returned unaltered
     * @param delimiters a list of possible delimiters to try.  Only one delimiter will be used to split the value into a list of values
     * @returns returns a list of values, which may be an array of only one element if no delimiters are found, or undefined if the input was undefined.
     */
    static parseArrayProperty(text, delimiters = ['|', ',', ';']) {
        // support arrays as well
        if (text instanceof Array) {
            return text;
        }
        if (text) {
            const delimiter = GcUtils.parseDelimiter(text, delimiters);
            if (delimiter) {
                if (text.endsWith(delimiter)) {
                    text = text.substring(0, text.length - delimiter.length);
                }
                return text.split(delimiter).map(e => e.trim());
            }
        }
    }
    /**
     * Parse the delimited character for the input text. If the last character is a delimiter, then this character will be return.
     * Otherwise, the delimiter that occurs the most will be return.
     *
     * @param text the input string
     * @param delimiters the list of possible delimiters to try
     * @returns the delimiter character or undefined if no delimiters are found.
     */
    static parseDelimiter(text, delimiters = ['|', ',', ';']) {
        if (text) {
            const lastCharacter = text[text.length - 1];
            if (delimiters.includes(lastCharacter)) {
                return lastCharacter;
            }
            return delimiters[delimiters.map(delimiter => text.split(delimiter).length)
                .reduce((iMax, x, i, arr) => x > arr[iMax] ? i : iMax, 0)];
        }
    }
    /**
     * Resolves the returned promise after the given time in millisecond.
     *
     * @param time the time to delay in millisecond
     */
    static async delay(time = 0) {
        await new Promise((resolve) => {
            setTimeout(resolve, time);
        });
    }
    /**
     * Helper method for doing find and replace operations on a string.  The result is a new string,
     * even if no text is found to replace.  The original string is not touched.
     *
     * @param target text to perform the find and replace operation on
     * @param find text to find in the target string for replacement
     * @param replaceWith text to replace with when found.
     *
     * @returns a new string with any occurrences of the found text replaced.
     */
    static findAndReplace(target, find, replaceWith) {
        return target.split(find).join(replaceWith);
    }
    /**
     * Helper method for shifting values through a fixed size buffer or array.  All the new values
     * will be appended to the end of the buffer, and if the resulting buffer exceeds the capacity,
     * the buffer will be shifted, and old values discarded.  This operation is performed in place
     * on the targetBuffer parameter.
     *
     * @param targetBuffer array that will be modified in place.
     * @param newValues array of new values to append to the buffer.
     * @param capacity limit for the size of the resulting buffer.
     * @returns the targetBuffer that was modified in place
     */
    static shiftAndAppendInPlace(targetBuffer, newValues, capacity) {
        // Case 1: The number of new values exceeds the capacity.  We need to throw away all old values in buffer, and some from the start of new values array.
        const throwAway = newValues.length - capacity;
        if (throwAway > 0) {
            targetBuffer.splice(0, Infinity, ...newValues.slice(throwAway));
            return targetBuffer;
        }
        const space = capacity - targetBuffer.length;
        // negative space means the buffer needs to be trimmed because it is longer than the capacity, so the delete count should be more than just the number of new values
        const deleteCount = newValues.length - space;
        // Case 2: The resulting buffer will be filled to full capacity, which means some old values will need to be deleted.
        if (deleteCount > 0) {
            targetBuffer.copyWithin(0, deleteCount);
            targetBuffer.splice(capacity - newValues.length, Infinity, ...newValues);
            return targetBuffer;
        }
        // Case 3: The space is greater than the number of new values
        targetBuffer.push(...newValues);
        return targetBuffer;
    }
    /**
     * Helper method transposing a 2D array or Matrix.
     *
     * @param matrix 2-d array that needs transposing.
     * @returns a new array that has been transposed
     */
    static transposeMatrix(matrix) {
        return matrix[0].map((_, colIndex) => matrix.map(row => row[colIndex]));
    }
    /**
     * Helper method to round a numerical value to fixed increment size.
     *
     * @param increment the size to the increment to round values to
     * @param minValue the starting value to apply the increment multiple.
     *
     * returns the value rounded to the nearest multiple of increment from minValue.
     */
    static roundToNearestIncrement(value, increment, minValue) {
        minValue = minValue || 0;
        increment = increment || 1;
        value = Math.round((value - minValue) / increment) * increment + minValue;
        // round value due to precision limitations in float numbers using the scale (# of decimal places) of the increment.
        const scale = (('' + increment).split('.')[1] ?? '').length;
        value = +value.toFixed(scale + 1);
        return value;
    }
    /**
     * Helper method to convert an IEEE-754 half precision floating point number (Float16) to a number value.
     * The IEEE-754 standard defines a 2 byte, half precision, floating point number with
     * - radix of 2 (ie mantissa * 2 ^ exponent)
     * - 1 sign bit (most significant bit)
     * - 5 digit exponent, with offset bias of 15, that ranges from -14 (00001) to 15 (11110).
     * - 11 digits mantissa, stored as 10 bits with an implied leading 1 bit, unless the exponent is zero (see below)
     * - +/- Infinity represented with zero mantissa, and exponent all ones (11111 - special case)
     * - NaN represented with non zero mantissa, and exponent all ones (11111 - special case)
     * - zero represented with zero mantissa, and exponent of zero (00000 - special case)
     * - subnormal values represented with exponent of zero(0000 - special case), non zero mantissa using the formula (sign) * 0.mantissa * 2 ^ -14.
     *
     * @param input 16 bit integer value to interpret as 16-bit floating point
     * @returns the input converted from float16 to javascript floating point number.
     */
    static float16ToValue(input) {
        const exponent = (input & 0x7C00) >> 10;
        const fraction = input & 0x3FF;
        const sign = input >> 15 ? -1 : 1;
        if (exponent) {
            if (exponent === 0x1F) {
                return fraction ? NaN : sign * Infinity;
            }
            return sign * Math.pow(2, exponent - 15) * (1 + fraction / 0x400);
        }
        return sign * 6.103515625e-5 * (fraction / 0x400); // Math.pow(2, -14) = 6.103515625e-5
    }
    static closeWindow() {
        if (GcUtils.isNW) {
            // @ts-ignore
            nw.Window.get().close();
        }
    }
}
/**
 * The bitfield helper class.
 */
GcUtils.bitField = BitField;
if (typeof window !== 'undefined') {
    window.gc = window.gc || {};
    window.gc.util = window.gc.util || GcUtils;
}

export { BitField, GcUtils };
//# sourceMappingURL=GcUtils.js.map
