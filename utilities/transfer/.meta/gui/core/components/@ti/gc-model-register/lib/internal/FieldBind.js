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
import { GcUtils } from '../../../gc-core-assets/lib/GcUtils';
import { AbstractBindValue, valueChangedEventType, streamingDataEventType, Status, staleChangedEventType, statusChangedEventType } from '../../../gc-core-databind/lib/CoreDatabind';
const typeParser = /\s*(unsigned\s|signed\s)?\s*(int|q(\d+))\s*/i;
export class FieldBind extends AbstractBindValue {
    constructor(symbolName, parentBind, symbolData, parentModel) {
        super(parentBind.getType());
        this.symbolName = symbolName;
        this.parentBind = parentBind;
        this.excludeFromStorageProviderData = true;
        this.mask = 1;
        this.shift = 0;
        this._readOnly = false;
        this.parentValueChangedListener = () => {
            this.onParentValueChangedHandler();
        };
        parentBind.addEventListener(valueChangedEventType, this.parentValueChangedListener);
        this.parentStreamingDataListener = () => {
            this.onDataReceived();
        };
        this.addEventListenerOnFirstAdded(streamingDataEventType, () => {
            this.parentBind.addEventListener(streamingDataEventType, this.parentStreamingDataListener);
        });
        this.addEventListenerOnLastRemoved(streamingDataEventType, () => {
            this.parentBind.removeEventListener(streamingDataEventType, this.parentStreamingDataListener);
        });
        this.doUpdateRegisterInfo(symbolData, parentModel);
    }
    dispose() {
        this.parentBind.removeEventListener(valueChangedEventType, this.parentValueChangedListener);
    }
    onParentValueChangedHandler() {
        let regValue = this.parentBind.getValue();
        const isArrayType = this.parentBind.getType() === 'array';
        if (!isArrayType) {
            regValue = [regValue];
        }
        let newValue = [];
        for (let i = 0; i < regValue.length; i++) {
            let value = GcUtils.bitField.readField(regValue[i], this.mask, this.shift, this.signBit);
            if (this.q && !isNaN(value)) {
                value = value / (Math.pow(2, this.q));
            }
            if (this.getConvertedValue) {
                value = this.getConvertedValue(value);
            }
            newValue[i] = value;
        }
        if (!isArrayType) {
            newValue = newValue[0];
        }
        this.updateValue(newValue, undefined, true);
    }
    static calcShiftMaskAndSignBit(symbolData) {
        // setup default mask, shift and bitWidth for when no symbol data is available.
        let shift = 0;
        let mask = 1;
        let signBit = undefined;
        let q = undefined;
        if (symbolData) {
            const startBit = symbolData.start;
            const stopBit = symbolData.stop;
            mask = GcUtils.bitField.getMask(startBit, stopBit);
            shift = startBit;
            const type = symbolData.type;
            if (type) {
                const match = typeParser.exec(type);
                if (match && match.index === 0) {
                    const isSigned = !(match[1] && match[1].toLowerCase() === 'unsigned');
                    if (isSigned) {
                        signBit = GcUtils.bitField.getMask(stopBit, stopBit);
                    }
                    if (match[3] !== undefined) {
                        q = +match[3];
                        if (q === undefined || isNaN(q) || q < 0) {
                            throw 'invalid type declaration for field: ' + symbolData.name;
                        }
                    }
                }
                else {
                    throw 'invalid type declaration for field: ' + symbolData.name;
                }
            }
        }
        return { shift: shift, mask: mask, signBit: signBit, q: q };
    }
    doUpdateRegisterInfo(symbolData, model) {
        var _a;
        try {
            const { mask, shift, signBit, q } = FieldBind.calcShiftMaskAndSignBit(symbolData);
            this.mask = mask;
            this.shift = shift;
            this.signBit = signBit;
            this.q = q;
            // Some of this is for backwards compatibility since we no longer generate bit fields that have a mode property
            this._readOnly = !symbolData || this.parentBind.readOnly || ((_a = symbolData.attrs) === null || _a === void 0 ? void 0 : _a.isLocked) || symbolData.mode === 'R';
            if (symbolData) {
                if (symbolData.getter || symbolData.setter) {
                    this.getConvertedValue = value => model.getConvertedValue(value, symbolData.getter, symbolData.setter);
                    this.setConvertedValue = value => model.getConvertedValue(value, symbolData.setter, symbolData.getter);
                }
                else {
                    this.getConvertedValue = undefined;
                    this.setConvertedValue = undefined;
                }
                // initialize value based on default register value.
                this.onParentValueChangedHandler();
                this.status = null; // clear any errors,
            }
            else {
                throw 'Bit field "' + this.symbolName + '" is not recognized for this device.';
            }
        }
        catch (e) {
            this.status = Status.createErrorStatus(e);
        }
    }
    updateRegisterInfo(parentModel) {
        const symbolData = parentModel.getRegisterInfo(this.symbolName);
        return this.doUpdateRegisterInfo(symbolData, parentModel);
    }
    onValueChanged(details) {
        let newValue = details.newValue;
        if (!Array.isArray(newValue)) {
            newValue = [newValue];
        }
        let regValue = this.parentBind.getValue();
        const isArrayType = this.parentBind.getType() === 'array';
        if (isArrayType) {
            regValue = regValue ? regValue.slice() : [];
        }
        else {
            regValue = [regValue];
        }
        for (let i = 0; i < regValue.length; i++) {
            let value = newValue[i];
            if (value !== undefined) {
                if (this.setConvertedValue) {
                    value = this.setConvertedValue(value);
                }
                if (this.q && !isNaN(value)) {
                    value = Math.round(value * Math.pow(2, this.q));
                }
                regValue[i] = GcUtils.bitField.writeField(regValue[i], this.mask, this.shift, value);
            }
        }
        if (!isArrayType) {
            regValue = regValue[0];
        }
        this.parentBind.setValue(regValue);
    }
    onDataReceived() {
        this.fireEvent(streamingDataEventType, { data: this.cachedValue });
    }
    isStale() {
        return this.parentBind.isStale();
    }
    addEventListener(type, listener) {
        if (type.id === staleChangedEventType.id) {
            this.parentBind.addEventListener(type, listener);
        }
        else {
            super.addEventListener(type, listener);
            if (type.id === statusChangedEventType.id) {
                this.parentBind.addEventListener(type, listener);
            }
        }
    }
    removeEventListener(type, listener) {
        if (type.id === staleChangedEventType.id && this.parentBind) {
            this.parentBind.removeEventListener(type, listener);
        }
        else {
            super.removeEventListener(type, listener);
            if (type.id === statusChangedEventType.id) {
                super.removeEventListener(type, listener);
            }
        }
    }
    get status() {
        let status = super.status;
        if (!status && this.parentBind) {
            status = this.parentBind.status;
        }
        return status;
    }
    set status(status) {
        super.status = status;
    }
    get readOnly() {
        return this._readOnly;
    }
}
//# sourceMappingURL=FieldBind.js.map