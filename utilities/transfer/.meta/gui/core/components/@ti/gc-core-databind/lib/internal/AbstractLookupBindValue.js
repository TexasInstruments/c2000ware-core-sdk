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
import { AbstractBindValue } from './AbstractBindValue';
/**
 * Abstract class that implements ILookupBindValue interface. Clients can either
 * instantiate this class directly or create classes derived from it for
 * their value bindable object.
 */
export class AbstractLookupBindValue extends AbstractBindValue {
    /**
     * Constructor for new AbstractBindValue
     *
     * @param defaultType the default type, used only if value is null.
     */
    constructor(defaultType) {
        super(defaultType);
        this.indexValues = [];
    }
    /**
     * Implementation of the ILookupBindValue.setIndex.  This implementation keeps track of the
     * index(es) and calls the abstract method onIndexChanged() when any
     * index value(s) change.  The getIndex() method can be used to retrieve the index
     * values inside the onIndexChanged() method to re-evaluate the model data's location
     * and possibly it's new value.
     *
     * @param indices one or more new index values to use for lookup
     */
    setIndex(...indices) {
        let changed = false;
        let i = 0;
        for (; i < indices.length && i < this.indexValues.length; i++) {
            const oldIndex = this.indexValues[i];
            const newIndex = indices[i];
            // eslint-disable-next-line eqeqeq
            if (oldIndex != newIndex) {
                this.indexValues[i] = newIndex;
                changed = true;
            }
        }
        for (; i < indices.length; i++) {
            this.indexValues.push(indices[i]);
            changed = true;
        }
        if (changed) {
            this.onIndexChanged(this.indexValues);
        }
    }
    getIndex() {
        return this.indexValues;
    }
    assertNotNull(index) {
        if (index === null || index === undefined) {
            throw new Error('The index value is null.');
        }
    }
    assertValidArrayIndex(index, size = 1, startIndex = 0) {
        this.assertNotNull(index);
        const indexValue = +index;
        if (isNaN(indexValue)) {
            throw new Error(`The index is not valid. Cannot convert '${index}' to an integer.`);
        }
        const endIndex = size + startIndex - 1;
        if (indexValue < startIndex || indexValue > endIndex) {
            throw new Error(`The index ${indexValue} is out of bounds.  It must be between ${startIndex} and ${endIndex}`);
        }
        return indexValue;
    }
    assertValidFieldName(fieldName, possibleFieldNames) {
        this.assertNotNull(fieldName);
        fieldName = fieldName.toString();
        // eslint-disable-next-line no-prototype-builtins
        if (possibleFieldNames === undefined || !possibleFieldNames.hasOwnProperty(fieldName)) {
            throw new Error(`The index '${fieldName}' was not found.`);
        }
        return fieldName;
    }
    assertValidData(index, data) {
        this.assertNotNull(index);
        if (data === undefined) {
            throw new Error(`The index '${index}' was not found.`);
        }
    }
}
//# sourceMappingURL=AbstractLookupBindValue.js.map