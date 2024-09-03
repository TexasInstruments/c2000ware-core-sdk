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
import { Status } from './Status';
import { AbstractLookupBindValue } from './AbstractLookupBindValue';
/**
 * Class that implements ILookupBindValue interface for an arbitrary javascript function.
 * The binding is read-only and updates its value whenever the indices change.
 * The indices are used as parameters to the function, whose return value is used as
 * the value for this binding.
 *
 * @constructor
 * @extends gc.databind.AbstractLookupBindValue
 *
 * @param functionMethod a function object whose return value is used as this binding's value.
 * @param thisPointer 'this' object to use when calling the function.
 */
export class FunctionBindValue extends AbstractLookupBindValue {
    constructor(functionMethod, thisPointer) {
        super();
        this.functionMethod = functionMethod;
        this.thisPointer = thisPointer;
    }
    // eslint-disable-next-line @typescript-eslint/no-empty-function
    setValue() {
    }
    get readOnly() {
        return true;
    }
    onIndexChanged(indices) {
        try {
            this.updateValue(this.functionMethod.apply(this.thisPointer, indices));
            this.status = null; // clear pre-existing error messages
        }
        catch (e) {
            // report exceptions as errors.
            this.status = Status.createErrorStatus(e.message);
        }
    }
    // eslint-disable-next-line @typescript-eslint/no-empty-function
    onValueChanged() {
    }
}
//# sourceMappingURL=FunctionBindValue.js.map