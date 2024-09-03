/**
 *  Copyright (c) 2020, 2023 Texas Instruments Incorporated
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
import { valueChangedEventType, streamingDataEventType, staleChangedEventType } from './IBindValue';
import { nullProgressCounter } from './ProgressCounter';
import { statusChangedEventType } from './IBind';
import { bindingRegistry } from './BindingRegistry';
import { Status } from './Status';
import { ConstantBindValue } from './ConstantBindValue';
import { AbstractUnaryOperator } from './expressionParser/AbstractUnaryOperator';
const errorBind = new ConstantBindValue();
export class ReferenceBindValue extends AbstractUnaryOperator {
    constructor(name) {
        super(errorBind);
        this.name = name;
        this.operator = '&';
        this.operand = errorBind;
        this.excludeFromStorageProviderData = true;
        this.name = name;
        this.updateReferenceBinding();
    }
    getValue() {
        return this.operand.getValue();
    }
    setValue(value, progress, force) {
        this.operand.setValue(value, progress, force);
    }
    moveListeners(oldBind, newBind) {
        this.forEachEventListener(statusChangedEventType, (listener) => {
            if (oldBind) {
                oldBind.removeEventListener(statusChangedEventType, listener);
            }
            if (newBind) {
                newBind.addEventListener(statusChangedEventType, listener);
            }
        });
        this.forEachEventListener(staleChangedEventType, (listener) => {
            if (oldBind) {
                oldBind.removeEventListener(staleChangedEventType, listener);
            }
            if (newBind) {
                newBind.addEventListener(staleChangedEventType, listener);
            }
        });
        this.forEachEventListener(valueChangedEventType, (listener) => {
            if (oldBind) {
                oldBind.removeEventListener(valueChangedEventType, listener);
            }
            if (newBind) {
                newBind.addEventListener(valueChangedEventType, listener);
            }
        });
        this.forEachEventListener(streamingDataEventType, (listener) => {
            if (oldBind) {
                oldBind.removeEventListener(streamingDataEventType, listener);
            }
            if (newBind) {
                newBind.addEventListener(streamingDataEventType, listener);
            }
        });
    }
    updateReferenceBinding(bindExpression, model) {
        // create new reference bind from expression
        const oldBind = this.operand;
        let newBind = null;
        const oldValue = oldBind.getValue();
        const oldIsStale = oldBind.isStale();
        const oldStatus = oldBind.status;
        this.bindExpression = bindExpression;
        try {
            if (bindExpression) {
                if (model) {
                    newBind = model.parseModelSpecificBindExpression(bindExpression);
                }
                else {
                    newBind = bindingRegistry.getBinding(bindExpression);
                }
            }
            if (newBind === null) {
                throw new Error(`The calculated binding "${this.toString()}" is not defined for this device.`);
            }
        }
        catch (e) {
            // create error bind for reference if no binding exists.
            newBind = new ConstantBindValue();
            newBind.status = Status.createErrorStatus(e.message);
        }
        // move listeners from the old reference binding to the new reference binding.
        if (oldBind === newBind) {
            return;
        }
        this.moveListeners(oldBind, newBind);
        this.operand = newBind;
        const newValue = this.operand.getValue();
        const newIsStale = this.operand.isStale();
        const newStatus = this.operand.status;
        // fire events to update to new state
        if (oldStatus !== newStatus) {
            this.fireEvent(statusChangedEventType, { oldStatus, newStatus, bind: this });
        }
        if (oldIsStale !== newIsStale) {
            this.fireEvent(staleChangedEventType, { stale: newIsStale });
        }
        if (oldValue !== newValue) {
            this.fireEvent(valueChangedEventType, { oldValue, newValue, progress: nullProgressCounter });
        }
    }
}
//# sourceMappingURL=ReferenceBindValue.js.map