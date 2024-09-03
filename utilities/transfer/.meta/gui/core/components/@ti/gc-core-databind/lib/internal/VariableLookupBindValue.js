/**
 *  Copyright (c) 2020, 2022 Texas Instruments Incorporated
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
import { AbstractLookupBindValue } from './AbstractLookupBindValue';
import { Status } from './Status';
/* eslint-disable @typescript-eslint/no-unused-vars */
/**
 * Class that implements ILookupBindValue interface for a variable lookup value binding.
 * Use this class if you wish to create a lookup binding based on a given array or struct data pointer.
 */
export class VariableLookupBindValue extends AbstractLookupBindValue {
    /**
     * Constructor for AbstractLookupBindValue.
     *
     * @param data the constant array or object data to use for lookups.
     * @param readOnly flag to indicate if setValue() method should be allowed to modify the data.
     */
    constructor(data, readOnly = false) {
        super();
        this._readOnly = readOnly;
        this.setData(data);
    }
    get readOnly() {
        return this._readOnly;
    }
    setValue(value, progress, forceWrite) {
        if (!this.readOnly) {
            // allow this value to be modified.
            super.setValue(value, progress, forceWrite);
        }
    }
    /**
     * Implemented to use the data provided to lookup values based on index changes.
     * The data must be an array or object type with nested arrays or objects as needed.
     * The index must be numeric for array types and string for object types.
     * This method calls setValue() to update this bindings
     * value and notify listeners based on the new index values.
     *
     * @param indices the multi-dimensional index values to use for lookup.
     */
    onIndexChanged(indices) {
        let value = this.data;
        try {
            for (let i = 0; value !== undefined && indices !== undefined && i < indices.length; i++) {
                let index = indices[i];
                if (index === null || index === undefined) {
                    throw new Error('The index value is null.');
                }
                if (value instanceof Array) {
                    value = value[this.assertValidArrayIndex(index, value.length)];
                }
                else if (typeof value === 'object') {
                    const fields = index.toString().split('.');
                    for (let j = 0; j < fields.length; j++) {
                        index = fields[j];
                        value = value[index];
                        if (value === undefined) {
                            this.assertValidFieldName(index);
                        }
                    }
                }
                else {
                    this.assertValidData(index);
                }
            }
            this.status = null; // if no exceptions clear errors
        }
        catch (e) {
            value = undefined;
            this.status = Status.createErrorStatus(e.message);
        }
        this.updateValue(value);
    }
    setData(data) {
        this.data = data;
        this.onIndexChanged(this.indexValues);
    }
    getData() {
        return this.data;
    }
    toString() {
        try {
            return JSON.stringify(this.data);
        }
        catch (e) {
            return '' + this.data;
        }
    }
    // eslint-disable-next-line @typescript-eslint/no-empty-function
    onValueChanged(details) {
    }
}
//# sourceMappingURL=VariableLookupBindValue.js.map