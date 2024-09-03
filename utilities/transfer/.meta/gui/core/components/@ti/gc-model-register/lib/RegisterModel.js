import { GcPromise } from '../../gc-core-assets/lib/GcPromise';
import { GcUtils } from '../../gc-core-assets/lib/GcUtils';
import { AbstractAsyncBindValue, valueChangedEventType, streamingDataEventType, nullProgressCounter, Status, statusChangedEventType, ArrayOperator, AbstractBindValue, staleChangedEventType, AbstractBindFactory, UserPreferenceBindValue, ReferenceBindValue, AbstractPollingDataModel, VariableBindValue, bindingRegistry, ConstantBindValue } from '../../gc-core-databind/lib/CoreDatabind';
import { GcConsole } from '../../gc-core-assets/lib/GcConsole';
import { EncoderType, DecoderType, codecRegistry } from '../../gc-target-configuration/lib/TargetConfiguration';
import { GcFiles } from '../../gc-core-assets/lib/GcFiles';
import { connectionManager, activeConfigurationChangedEvent } from '../../gc-target-connection-manager/lib/ConnectionManager';
export * from './IRegisterInfo';

/**
 *  Copyright (c) 2020, 2021 Texas Instruments Incorporated
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
class RegisterBind extends AbstractAsyncBindValue {
    constructor(symbolName, parentModel, refreshIntervalProvider, symbolData, registerAllBind, defaultType = 'number') {
        super(defaultType);
        this.symbolName = symbolName;
        this.parentModel = parentModel;
        this.coreIndex = 0;
        this.onFailure = (errMsg) => {
            if (this.parentModel.isConnected()) {
                this.reportErrorStatus(errMsg.message || errMsg.toString());
            }
            return this.cachedValue; // don't record a new value, keep the same value as before.
        };
        this.onSuccess = (result) => {
            // clear errors on successful read
            this.reportCriticalError(null);
            if (this.coreCountBind) {
                // must be RegisterAllBind
                // support single core case where readValue returns non array value, and we need to convert to array.
                if (!Array.isArray(result)) {
                    result = [result];
                }
                // update the $cores.length binding as needed.
                this.coreCountBind.updateValue(result.length);
            }
            return result;
        };
        this.setRefreshIntervalProvider(refreshIntervalProvider);
        this.updateRegisterInfo();
        this.parentBind = registerAllBind;
        if (this.parentBind) {
            this.addEventListenerOnFirstAdded(valueChangedEventType, () => {
                this.getValue(); // update cached value without generating a changed event to newly added listener.
                this.onParentValueChangedHandler = () => {
                    this.doUpdateRegisterValue(true);
                };
                this.parentBind.addEventListener(valueChangedEventType, this.onParentValueChangedHandler);
            });
            this.addEventListenerOnLastRemoved(valueChangedEventType, () => {
                if (this.onParentValueChangedHandler) {
                    this.parentBind.removeEventListener(valueChangedEventType, this.onParentValueChangedHandler);
                    this.onParentValueChangedHandler = undefined;
                }
            });
            this.addEventListenerOnFirstAdded(streamingDataEventType, () => {
                this.onDataReceivedHandler = () => {
                    this.doUpdateRegisterValue(false);
                };
                this.parentBind.addEventListener(streamingDataEventType, this.onDataReceivedHandler);
            });
            this.addEventListenerOnLastRemoved(streamingDataEventType, () => {
                if (this.onDataReceivedHandler) {
                    this.parentBind.removeEventListener(streamingDataEventType, this.onDataReceivedHandler);
                    this.onDataReceivedHandler = undefined;
                }
            });
        }
    }
    dispose() {
        super.dispose();
        if (this.parentBind) {
            if (this.onParentValueChangedHandler) {
                this.parentBind.removeEventListener(valueChangedEventType, this.onParentValueChangedHandler);
                this.onParentValueChangedHandler = undefined;
            }
            if (this.onDataReceivedHandler) {
                this.parentBind.removeEventListener(streamingDataEventType, this.onDataReceivedHandler);
                this.onDataReceivedHandler = undefined;
            }
            this.parentBind = undefined;
        }
    }
    doUpdateRegisterValue(skipStreamingListeners) {
        this.updateValue(this.parentBind.getValueFor(this.coreIndex), undefined, skipStreamingListeners);
        this.setStale(false);
    }
    getValue() {
        if (this.parentBind && !this.onParentValueChangedHandler) {
            this.cachedValue = this.parentBind.getValueFor(this.coreIndex);
        }
        return super.getValue();
    }
    onValueChanged(details) {
        super.onValueChanged(details);
        if (this.parentBind) {
            this.parentBind.updateValueFor(this.coreIndex, details.newValue);
        }
    }
    updateValue(value, progress = nullProgressCounter, skipStreamingListeners) {
        super.updateValue(value, progress, skipStreamingListeners);
        if (this.parentBind) {
            this.parentBind.updateValueFor(this.coreIndex, this.getValue());
        }
    }
    async writeValue() {
        try {
            await this.parentModel.writeValue(this.symbolName, this.cachedValue, this.coreIndex);
        }
        catch (err) {
            this.onFailure(err);
        }
    }
    readValue() {
        return this.parentModel.readValue(this.symbolName, this.coreIndex).then(this.onSuccess).catch(this.onFailure);
    }
    reportErrorStatus(errorMessage) {
        let status = null;
        if (errorMessage && errorMessage.length > 0) {
            status = Status.createErrorStatus(errorMessage, 'target');
        }
        this.reportCriticalError(status);
    }
    getRegisterInfo() {
        return this.parentModel.getRegisterInfo(this.symbolName);
    }
    updateRegisterInfo() {
        const symbolData = this.getRegisterInfo();
        if (symbolData) {
            this.defaultValue = symbolData.default;
            // restore default for the new device, before reading the actual value.
            if (this.defaultValue !== undefined) {
                this.updateValue(this.defaultValue, undefined, true);
                this.setStale(false);
            }
            else {
                this.setStale(true);
            }
            // support for qualifiers in register symbol data
            // remove existing qualifiers
            if (!this.readable) {
                this.readable = true;
            }
            if (!this.writable) {
                this.writable = true;
            }
            if (!this.volatile) {
                this.volatile = true;
            }
            if (!this.verifiable) {
                this.verifiable = true;
            }
            if (symbolData.attrs) {
                let qualifier;
                for (qualifier in symbolData.attrs) {
                    if (symbolData.attrs[qualifier]) {
                        this.setQualifier(qualifier);
                    }
                }
            }
            // clear errors on successful read
            this.reportCriticalError(null);
        }
        else {
            this.reportCriticalError(Status.createErrorStatus('Register named "' + this.symbolName + '" is not recognized for this device.'));
        }
    }
    onIndexChanged() {
        const index = this.getIndex();
        if (index) {
            this.coreIndex = Math.max(0, +index[0]); // make sure index >= 0
            if (this.parentBind && !this.parentBind.isStale()) {
                // use parent bind to update value because it is not stale
                this.doUpdateRegisterValue(true);
            }
            else if (this.defaultValue !== undefined) {
                // binding never stale if there is a default value defined.
                this.updateValue(this.defaultValue, undefined, true);
            }
            else {
                // no default value and parent (it there is one) is stale.
                this.setStale(true);
            }
            // discard any deferred write operations when index is changed.  The register view will
            // prompt user before switching active cores to allow the user to commit or clear the deferred writes.
            this.committedValue = this.cachedValue;
        }
    }
    isConnected() {
        return this.parentModel.isConnected();
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
    addEventListener(type, listener) {
        super.addEventListener(type, listener);
        if (type.id === statusChangedEventType.id && this.parentBind) {
            this.parentBind.addEventListener(type, listener);
        }
    }
    removeEventListener(type, listener) {
        super.removeEventListener(type, listener);
        if (type.id === statusChangedEventType.id && this.parentBind) {
            this.parentBind.removeEventListener(type, listener);
        }
    }
    kickStartAReadOperation(force) {
        // prevent automatic reads when there is a RegisterAll parent binding, but still allow manual onRefresh() calls.
        if (!this.parentBind) {
            super.kickStartAReadOperation(force);
        }
    }
}
class RegisterAllBind extends RegisterBind {
    constructor(symbolName, model, refreshIntervalProvider, symbolData) {
        super(symbolName, model, refreshIntervalProvider, symbolData, undefined, 'array');
        this.coreIndex = -1;
        this.coreCountBind = model.getBinding('$cores.length');
    }
    getValueFor(index) {
        return (this.cachedValue && Array.isArray(this.cachedValue) && this.cachedValue[index]) || this.defaultValue || 0;
    }
    static updateValueInArrayByIndex(array, index, newValue, defaultValue) {
        const result = array ? array.slice() : [];
        for (let i = result.length; i < index; i++) {
            result.push(defaultValue);
        }
        result[index] = newValue;
        return result;
    }
    updateValueFor(index, newValue) {
        if (this.getType() === 'array' && newValue !== this.getValueFor(index)) {
            const newValues = RegisterAllBind.updateValueInArrayByIndex(this.cachedValue, index, newValue, this.defaultValue);
            if (this.deferredMode) {
                this.committedValue = RegisterAllBind.updateValueInArrayByIndex(this.committedValue, index, newValue, this.defaultValue);
            }
            this.updateValue(newValues, undefined, true); // skip streaming data listeners.
        }
    }
}
class RegisterArrayOperator extends ArrayOperator {
    constructor(registerBind, indexBind) {
        // binary operator adds listeners to figure out when either the registerBind or indexBind changes
        // when array operator changes it will call setIndex on the registerBind.  (the first param specifies the new index)
        super(registerBind, [indexBind]);
    }
    refresh(progress, force = true) {
        return this.lookupBinding.refresh(progress, force);
    }
    refreshAndLog(progress) {
        return this.lookupBinding.refreshAndLog(progress);
    }
    setDeferredMode(deferredMode = false, progress = nullProgressCounter, forceWrite = false) {
        return this.lookupBinding.setDeferredMode(deferredMode, progress, forceWrite);
    }
    isConnected() {
        return this.lookupBinding.isConnected();
    }
    clearDeferredWrite() {
        return this.lookupBinding.clearDeferredWrite();
    }
    get readOnly() {
        return this.lookupBinding.readOnly;
    }
    isDeferredWritePending() {
        return this.lookupBinding.isDeferredWritePending();
    }
    getValueCommitted() {
        return this.lookupBinding.getValueCommitted();
    }
    updateRegisterInfo() {
        return this.lookupBinding.updateRegisterInfo();
    }
    onDisconnected() {
        return this.lookupBinding.onDisconnected();
    }
    updateValue(value, progress = nullProgressCounter, skipStreamingListeners) {
        return this.lookupBinding.updateValue(value, progress, skipStreamingListeners);
    }
}

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
const typeParser = /\s*(unsigned\s|signed\s)?\s*(int|q(\d+))\s*/i;
class FieldBind extends AbstractBindValue {
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
        try {
            const { mask, shift, signBit, q } = FieldBind.calcShiftMaskAndSignBit(symbolData);
            this.mask = mask;
            this.shift = shift;
            this.signBit = signBit;
            this.q = q;
            // Some of this is for backwards compatibility since we no longer generate bit fields that have a mode property
            this._readOnly = !symbolData || this.parentBind.readOnly || symbolData.attrs?.isLocked || symbolData.mode === 'R';
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

/**
 *  Copyright (c) 2020, 2024 Texas Instruments Incorporated
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
var BIND_TYPE;
(function (BIND_TYPE) {
    BIND_TYPE[BIND_TYPE["CALCULATED"] = 0] = "CALCULATED";
    BIND_TYPE[BIND_TYPE["FIELD"] = 1] = "FIELD";
    BIND_TYPE[BIND_TYPE["CORE_REGISTER"] = 2] = "CORE_REGISTER";
    BIND_TYPE[BIND_TYPE["USER"] = 3] = "USER";
    BIND_TYPE[BIND_TYPE["REGISTER_ALL"] = 4] = "REGISTER_ALL";
    BIND_TYPE[BIND_TYPE["ACTIVE_REGISTER"] = 5] = "ACTIVE_REGISTER";
    BIND_TYPE[BIND_TYPE["BAD"] = 6] = "BAD";
})(BIND_TYPE || (BIND_TYPE = {}));
const notIdentifierRegExp = /[^A-Za-z$_.0-9]+/;
const REGISTER_DEFINITIONS_BIND_NAME = '$registerDefinitions';
const DEVICE_BLOCK_ADDRESS_BASE = '$deviceAddrs.';
/**
 * An implementation of **{@link IRegisterModelEncoder}** that does nothing.
 */
const nullRegisterModelEncoder = new (class {
    readValue() {
        throw new Error('Method not implemented.');
    }
    writeValue() {
        throw new Error('Method not implemented.');
    }
    multiRegisterRead() {
        throw new Error('Method not implemented.');
    }
})();
/**
 * An implementation of **{@link IRegisterModelDecoder}** that does nothing.
 */
const nullRegisterModelDecoder = new (class extends AbstractBindFactory {
    getDeviceAddressForRegister() {
        return undefined;
    }
    createNewBind() {
        throw new Error('Method not implemented.');
    }
})('null');
/**
 * Runtime type identifier for all Register Model encoders.
 */
const RegisterModelEncoderType = new EncoderType('regInfo');
/**
 * Runtime type identifier for all Register Model decoders.
 */
const RegisterModelDecoderType = new DecoderType('regModel');
function resolveBlockRead(promises, offset, size, results) {
    for (let i = 0; i < size; i++) {
        promises[i + offset].resolve(results[i]);
    }
}
function failBlockRead(promises, offset, size, reason) {
    for (let i = 0; i < size; i++) {
        promises[i + offset].reject(reason);
    }
}
class RegisterBlock {
    constructor(registerModel, info, next) {
        this.len = 1;
        this.registerModel = registerModel;
        this.addr = info.addr;
        this.next = next;
        this.regs = [info];
    }
    prependRegister(regInfo) {
        this.len++;
        this.addr--;
        this.regs.unshift(regInfo);
    }
    appendRegister(regInfo) {
        this.len++;
        this.regs.push(regInfo);
        if (this.next && regInfo.addr === this.next.addr - 1) {
            // combine next register block into this one.
            this.len += this.next.len;
            this.regs.push(...this.next.regs);
            this.next = this.next.next;
        }
    }
    doReadRegisters(coreIndex) {
        const promises = this.promises || [];
        for (let i = 0; i < promises.length; i++) {
            if (promises[i]) {
                let size = 1;
                while (promises[i + size]) {
                    size++;
                }
                const codec = this.registerModel.codec;
                if (codec) {
                    if (size > 1) {
                        const regmap = this.regs[i];
                        (function (i, size) {
                            // block read values
                            codec.multiRegisterRead(regmap, size, coreIndex).then((results) => {
                                resolveBlockRead(promises, i, size, results);
                            }).catch((err) => {
                                failBlockRead(promises, i, size, err);
                            });
                        })(i, size);
                        i += size - 1;
                    }
                    else {
                        // single value read
                        codec.readValue(this.regs[i], coreIndex).then(promises[i].resolve).catch(promises[i].reject);
                    }
                }
            }
        }
        this.promises = undefined;
    }
    readRegister(regInfo, coreIndex) {
        if (!this.promises) {
            this.promises = [];
            setTimeout(() => {
                this.doReadRegisters(coreIndex);
            }, 0);
        }
        const deferred = GcPromise.defer();
        this.promises[regInfo.addr - this.addr] = deferred;
        return deferred.promise;
    }
}
class RegisterBlocks {
    constructor(registerModel) {
        this.registerModel = registerModel;
    }
    findRegisterBlock(info) {
        const addr = info.addr;
        if (addr !== undefined) {
            let cur = this.first;
            while (cur && addr >= cur.addr + cur.len) {
                cur = cur.next;
            }
            if (cur && addr >= cur.addr && cur.len > 1) {
                return cur;
            }
        }
    }
    addRegister(info) {
        const addr = info.addr;
        if (addr !== undefined) {
            let cur = this.first;
            if (!cur) {
                // first element
                this.first = new RegisterBlock(this.registerModel, info);
            }
            else if (addr < cur.addr - 1) {
                // insert before first element
                this.first = new RegisterBlock(this.registerModel, info, cur);
            }
            else {
                // find insert point
                while (cur.next && addr >= cur.next.addr - 1 && addr !== cur.addr + cur.len) {
                    cur = cur.next;
                }
                if (addr === cur.addr - 1) {
                    // insert at beginning of block
                    cur.prependRegister(info);
                }
                else if (addr === cur.addr + cur.len) {
                    // insert at end of block
                    cur.appendRegister(info);
                }
                else {
                    // insert new block after current element.
                    cur.next = new RegisterBlock(this.registerModel, info, cur.next);
                }
            }
        }
    }
    readRegister(codec, info, coreIndex) {
        const block = this.findRegisterBlock(info);
        if (block && codec.multiRegisterRead) {
            return block.readRegister(info, coreIndex);
        }
        return codec.readValue(info, coreIndex);
    }
}
class UserPreferenceRefBindValue extends UserPreferenceBindValue {
    constructor(...keys) {
        super(...keys);
        this.defaultBind = new ReferenceBindValue('');
        this.defaultBind.addEventListener(valueChangedEventType, (details) => {
            this.defaultValue = details.newValue;
        });
    }
    updateReferenceBinding(bindingExpression, model) {
        this.defaultBind.updateReferenceBinding(bindingExpression, model);
    }
}
const calculatedBindingsPrefix = '_';
const NotDeviceArrayMessage = 'Must set is-device-array="true" on gc-model-register in order to use URIs that start with $cores';
/**
 * Data binding Model for registers, and register bit fields, read and written to a target device.  This is a polling model
 * where the rate of polling can be controlled.  Reading and writing or register values done through the
 * **{@link IRegisterModelEncoder}** interface.
 */
class RegisterModel extends AbstractPollingDataModel {
    constructor(params) {
        super(params.id || 'reg', params.defaultRefreshInterval);
        this.params = params;
        this.decoderInputType = RegisterModelDecoderType;
        this.decoderOutputType = RegisterModelEncoderType;
        this.symbols = new Map();
        this.uriPrefix = '';
        this.registerBlocksMap = new Map();
        this.deviceAddrsDefault = null;
        this.deviceAddrsUserPreferenceDefaults = new Map();
        this.console = new GcConsole('gc-register-model', params.id);
        this.setSymbols();
        this.selectedConfigurationBind = new VariableBindValue(connectionManager.activeConfigurationId);
        connectionManager.addEventListener(activeConfigurationChangedEvent, () => {
            this.selectedConfigurationBind.setValue(connectionManager.activeConfigurationId);
        });
        this.selectedDeviceBind = new VariableBindValue(this.params.deviceId);
        this.deviceAddrs = new VariableBindValue(this.params.deviceAddress === undefined ? undefined : +(this.params.deviceAddress ?? 0));
        if (this.isDeviceArray) {
            this.modelBindings.set('$selectedCore', new UserPreferenceBindValue(this.id, 'configuration', this.selectedConfigurationBind, 'device', this.selectedDeviceBind, 'core'));
            this.modelBindings.set('$cores.length', new VariableBindValue(undefined, true));
        }
        codecRegistry.register(this);
        bindingRegistry.registerModel(this);
        this.loadRegisterInfo();
    }
    dispose() {
        super.dispose();
        codecRegistry.unregister(this);
    }
    /**
     * True if this register model is configured to support an array of similar devices, rather that a single device.
     */
    get isDeviceArray() {
        return this.params.isDeviceArray || false;
    }
    getBinding(uri) {
        // use a prefix for looking up bindings, but only if a symbol exists for the prefix + uri, otherwise just use uri.
        if (this.uriPrefix) {
            if (this.deviceAddrsUserPreferenceDefaults.has(this.uriPrefix + uri)) {
                uri = this.uriPrefix + uri;
            }
        }
        return super.getBinding(uri);
    }
    createNewBind(uri) {
        const customRefreshBind = super.createNewBind(uri);
        if (customRefreshBind) {
            return customRefreshBind;
        }
        if (uri === REGISTER_DEFINITIONS_BIND_NAME) {
            return new VariableBindValue(undefined);
        }
        let bindResult;
        let registerAllBind;
        let registerBind;
        try {
            const segments = uri.split('.');
            switch (RegisterModel.getBindingTypeFromUri(uri, segments)) {
                case BIND_TYPE.FIELD: {
                    const pos = uri.lastIndexOf('.');
                    const parentBind = this.getBinding(uri.substring(0, pos));
                    if (parentBind instanceof RegisterBind || parentBind instanceof RegisterArrayOperator) {
                        const bitNumber = uri.substring(pos + 1);
                        let symbolName = uri;
                        let symbolData = this.symbols.get(symbolName);
                        if (!isNaN(+bitNumber)) {
                            symbolData = { start: +bitNumber, stop: +bitNumber, name: uri };
                            symbolName = '';
                        }
                        else if (segments.length === 4) {
                            // strip $cores.xxx.  from the uri.
                            symbolName = segments[2] + '.' + segments[3];
                            symbolData = this.symbols.get(symbolName);
                        }
                        bindResult = new FieldBind(symbolName, parentBind, symbolData, this);
                    }
                    else {
                        throw parentBind?.status?.message || NotDeviceArrayMessage;
                    }
                    break;
                }
                case BIND_TYPE.USER: {
                    bindResult = new UserPreferenceRefBindValue(this.id, 'configuration', this.selectedConfigurationBind, 'device', this.selectedDeviceBind, uri);
                    break;
                }
                case BIND_TYPE.CALCULATED: {
                    bindResult = new ReferenceBindValue(uri);
                    this.updateCalculatedBind(bindResult);
                    break;
                }
                case BIND_TYPE.ACTIVE_REGISTER: {
                    const symbolData = this.symbols.get(uri);
                    if (this.isDeviceArray) {
                        registerAllBind = this.getBinding('$cores.all.' + uri);
                        registerBind = new RegisterBind(uri, this, undefined, symbolData, registerAllBind);
                        registerBind.name = uri;
                        const activeRegisterBind = this.getBinding('$selectedCore');
                        bindResult = new RegisterArrayOperator(registerBind, activeRegisterBind);
                    }
                    else {
                        bindResult = new RegisterBind(uri, this, this.defaultRefreshBinding, symbolData);
                    }
                    break;
                }
                case BIND_TYPE.REGISTER_ALL: {
                    if (this.isDeviceArray) {
                        const symbolName = segments[2];
                        const symbolData = this.symbols.get(symbolName);
                        bindResult = new RegisterAllBind(symbolName, this, this.defaultRefreshBinding, symbolData);
                    }
                    else {
                        throw NotDeviceArrayMessage;
                    }
                    break;
                }
                // eslint-disable-next-line no-fallthrough
                case BIND_TYPE.CORE_REGISTER: {
                    if (this.isDeviceArray) {
                        const symbolName = segments[2];
                        const symbolData = this.symbols.get(symbolName);
                        registerAllBind = this.getBinding('$cores.all.' + symbolName);
                        bindResult = new RegisterBind(symbolName, this, undefined, symbolData, registerAllBind);
                        bindResult.setIndex(segments[1]);
                    }
                    else {
                        throw NotDeviceArrayMessage;
                    }
                    break;
                }
                default: {
                    throw `Invalid register bind name: ${uri}`;
                }
            }
        }
        catch (e) {
            bindResult = new ConstantBindValue();
            bindResult.status = Status.createErrorStatus(e);
        }
        return bindResult;
    }
    updateAllBindings() {
        this.modelBindings.forEach((bind, bindName) => {
            if (bind) {
                if (bind instanceof FieldBind) {
                    bind.updateRegisterInfo(this);
                }
                else if (bind instanceof RegisterBind) {
                    bind.updateRegisterInfo();
                }
                else if (bind instanceof RegisterArrayOperator) {
                    bind.updateRegisterInfo();
                }
                else if (bind instanceof ReferenceBindValue) {
                    this.updateCalculatedBind(bind);
                }
                else if (bind instanceof UserPreferenceRefBindValue) {
                    this.updateUserPreferenceBind(bind, bind.name ?? '');
                }
            }
        });
    }
    addSymbol(symbolName, symbolData, isRegister) {
        /* truth table
         *                       new entry
         * existing entry | Register |  Field   |
         * ===============+=====================+
         *      undefined | replace  | replace  |
         *           null | replace  |   skip   |
         *       Register | replace  |   skip   |
         *          Field | replace  | set null |
         */
        symbolName = symbolName.split(' ').join('_'); // convert spaces to underscores
        const symbolEntry = this.symbols.get(symbolName);
        if (symbolEntry === undefined || isRegister) {
            this.symbols.set(symbolName, symbolData); // replace
        }
        else if (symbolEntry && !isRegister) {
            this.symbols.set(symbolName, null); // remove duplicates from the symbol table, unless field is trying to override a register.
        }
        return symbolName;
    }
    /**
     * Method to set or change the register.json information programmatically, as opposed to providing a filename as a parameter
     * to the constructor of the register model.
     */
    setSymbols(deviceInfo) {
        this.registerBlocksMap = new Map();
        this.symbols.clear();
        this.clearAllModelSpecificBindExpressions();
        if (deviceInfo) {
            const groups = (deviceInfo.regblocks || []).map((groupInfo) => {
                const attrs = groupInfo.attrs ? {
                    ...groupInfo.attrs,
                    isHidden: GcUtils.string2boolean(groupInfo.attrs.isHidden),
                } : undefined;
                const regs = (groupInfo.registers || []).map((regInfo) => {
                    const size = GcUtils.string2value(regInfo.size);
                    const id = (regInfo.id || regInfo.name).split(' ').join('_');
                    let regInfoAttrs = regInfo.attrs;
                    // convert deprecated mode to new attrs flogs.
                    switch (regInfo.mode) {
                        case 'R':
                            regInfoAttrs = { readonly: true };
                            break;
                        case 'W':
                            regInfoAttrs = { writeonly: true };
                            break;
                        case 'nonvolatile':
                            regInfoAttrs = { nonvolatile: true };
                    }
                    const attrs = regInfoAttrs ? {
                        ...regInfoAttrs,
                        readonly: GcUtils.string2boolean(regInfoAttrs?.readonly),
                        writeonly: GcUtils.string2boolean(regInfoAttrs?.writeonly),
                        nonvolatile: GcUtils.string2boolean(regInfoAttrs?.nonvolatile),
                        noverify: GcUtils.string2boolean(regInfoAttrs?.noverify),
                        isHidden: GcUtils.string2boolean(regInfoAttrs?.isHidden)
                    } : undefined;
                    const reg = {
                        ...regInfo,
                        id,
                        attrs,
                        size,
                        nBytes: Math.ceil((size === undefined ? 8 : size) / 8),
                        addr: GcUtils.string2value(regInfo.addr) || 0,
                        writeAddr: GcUtils.string2value(regInfo.writeAddr),
                        default: GcUtils.string2value(regInfo.value) ?? GcUtils.string2value(regInfo.default),
                        deviceAddrs: regInfo.deviceAddrs || groupInfo.deviceAddrs || deviceInfo.deviceAddrsDefault,
                        fields: [],
                        groupName: groupInfo.name,
                        registerModel: this
                    };
                    reg.fields = (regInfo.fields || []).map((fieldInfo) => {
                        const id = (fieldInfo.id || fieldInfo.name).split(' ').join('_');
                        const fieldOptions = fieldInfo.widget?.options ?? fieldInfo.options;
                        const options = fieldOptions ? fieldOptions.map((option, i) => {
                            return { ...option, value: GcUtils.string2value(option.value) ?? i };
                        }) : undefined;
                        const start = GcUtils.string2value(fieldInfo.start) ?? 0;
                        const stop = GcUtils.string2value(fieldInfo.stop) ?? GcUtils.string2value(fieldInfo.start) ?? 0;
                        const widget = fieldInfo.widget ? {
                            ...fieldInfo.widget,
                            min: GcUtils.string2value(fieldInfo.widget.min) ?? 0,
                            max: GcUtils.string2value(fieldInfo.widget.max) ?? ((1 << stop - start + 1) - 1),
                            step: GcUtils.string2value(fieldInfo.widget.step) ?? 1,
                        } : undefined;
                        const attrs = fieldInfo.attrs ? {
                            ...fieldInfo.attrs,
                            isHidden: GcUtils.string2boolean(fieldInfo.attrs.isHidden),
                            isLocked: GcUtils.string2boolean(fieldInfo.attrs.isLocked),
                            isReserved: GcUtils.string2boolean(fieldInfo.attrs.isReserved),
                        } : undefined;
                        const field = {
                            ...fieldInfo,
                            id,
                            start,
                            stop,
                            options,
                            widget,
                            attrs
                        };
                        const symbolName = (reg.id || reg.name) + '.' + (field.id || field.name);
                        this.addSymbol(symbolName.trim(), field, false);
                        return field;
                    });
                    // add registers to registerBlockMap to support Multi-register read operations.
                    if (reg.nBytes === 1) {
                        const blockName = reg.deviceAddrs || '.default';
                        let block = this.registerBlocksMap.get(blockName);
                        if (!block) {
                            block = new RegisterBlocks(this);
                            this.registerBlocksMap.set(blockName, block);
                        }
                        block.addRegister(reg);
                    }
                    const symbolName = reg.id || reg.name;
                    this.addSymbol(symbolName, reg, true);
                    return reg;
                });
                return {
                    ...groupInfo,
                    registers: regs,
                    attrs
                };
            });
            // @ts-ignore
            const calculatedBindings = deviceInfo.calculatedBindings ?? deviceInfo['calculated bindings'];
            this.registerJsonData = {
                ...deviceInfo,
                calculatedBindings,
                regblocks: groups
            };
            if (this.registerJsonData) {
                this.console.log('New register information ready.');
            }
            if (calculatedBindings) {
                Object.keys(calculatedBindings).forEach((calcBindName) => {
                    if (calcBindName.indexOf(calculatedBindingsPrefix) !== 0) {
                        const errorBind = new ConstantBindValue();
                        const errorMessage = `The calculated binding "${calcBindName}" must begin with the prefix "${calculatedBindingsPrefix}".  Please edit your register.json and ensure you prefix all your calculated binding definitions with this.`;
                        errorBind.status = Status.createErrorStatus(errorMessage);
                        this.modelBindings.set(calcBindName, errorBind);
                    }
                    else {
                        // add symbols for calculated bindings
                        this.symbols.set(calcBindName, null);
                    }
                });
            }
            this.readDeviceAddressMap(deviceInfo);
        }
        else {
            if (this.registerJsonData) {
                this.console.log('Old register information purged.');
            }
            this.registerJsonData = undefined;
        }
        this.updateAllBindings(); // update bindings to reflect new symbols available or not.
        this.getBinding(REGISTER_DEFINITIONS_BIND_NAME).setValue(this.registerJsonData);
    }
    getSymbolSuggestions(prefix) {
        prefix = prefix || '';
        const result = [];
        this.symbols.forEach((value, key) => {
            if (key.indexOf(prefix) === 0) {
                result.push(key);
            }
        });
        return result;
    }
    /**
     * Read a register value directly from the target, without going through databinding.
     *
     * @param uri binding name for register to read a value from the target.
     * @param coreIndex specific core to read the register from.
     * @returns value read for a specific core, or all values across all cores if device array is enabled.
     */
    async readValue(uri, coreIndex) {
        if (!this.isConnected()) {
            await this.whenConnected();
        }
        if (this.isDeviceArray && coreIndex === undefined) {
            // assumption is that this is coming from _scriptRead api and we should be using the active core.
            coreIndex = +this.getBinding('$selectedCore').getValue();
        }
        else {
            coreIndex = coreIndex || 0;
        }
        const symbolData = this.symbols.get(uri);
        if (symbolData) {
            if (this.codec) {
                const blockName = symbolData.deviceAddrs || '.default';
                const block = this.registerBlocksMap.get(blockName);
                if (block) {
                    return block.readRegister(this.codec, symbolData, coreIndex);
                }
                return this.codec.readValue(symbolData, coreIndex);
            }
        }
        throw `Register "${uri}" is not recognized for this device.  Please check the spelling.`;
    }
    /**
     * Read a register bit field directly from the target, without going through databinding.
     *
     * @param uri binding name for register bit field to read a value from the target.
     * @param coreIndex specific core to read the bit field from.
     * @returns value read for a specific core, or all values across all cores if device array is enabled.
     */
    async readBitfieldValue(uri, coreIndex) {
        const segments = uri.split('.');
        const symbolData = this.symbols.get(uri);
        if (segments.length > 1 && symbolData) {
            const value = await this.readValue(segments[segments.length - 2], coreIndex);
            const { mask, shift, signBit } = FieldBind.calcShiftMaskAndSignBit(symbolData);
            if (value instanceof Array) {
                return value.map((val) => GcUtils.bitField.readField(val, mask, shift, signBit));
            }
            return GcUtils.bitField.readField(value, mask, shift, signBit);
        }
        else {
            throw `Invalid register bitfield expression: ${uri}.`;
        }
    }
    /**
     * Write a register value directly to the target, without going through databinding.
     *
     * @param uri binding name for register to write the value to the target.
     * @param value value to write
     * @param coreIndex specific core to write the value to.
     */
    async writeValue(uri, value, coreIndex) {
        if (!this.isConnected()) {
            await this.whenConnected();
        }
        if (this.isDeviceArray && coreIndex === undefined) {
            // assumption is that this is coming from _scriptWrite api and we should be using the active core.
            coreIndex = +this.getBinding('$selectedCore').getValue();
        }
        else {
            coreIndex = coreIndex || 0;
        }
        const symbolData = this.symbols.get(uri);
        if (symbolData) {
            if (this.codec) {
                return this.codec.writeValue(symbolData, value, coreIndex);
            }
        }
        throw `Register "${uri}" is not recognized for this device.  Please check the spelling.`;
    }
    /**
     * Write a register bit field value directly to the target, without going through databinding.
     *
     * @param uri binding name for register bit field to write the value to the target.
     * @param value value to write
     * @param coreIndex specific core to write the value to.
     */
    async writeBitfieldValue(uri, value, coreIndex) {
        const segments = uri.split('.');
        const symbolData = this.symbols.get(uri);
        if (segments.length > 1 && symbolData && symbolData) {
            const oldValue = await this.readValue(segments[segments.length - 2], coreIndex);
            if (oldValue instanceof Array) {
                throw 'writeBitfield() method does not supported multi-core.  coreIndex must not be -1.';
            }
            const { shift, mask } = FieldBind.calcShiftMaskAndSignBit(symbolData);
            const newValue = GcUtils.bitField.writeField(oldValue, mask, shift, value);
            await this.writeValue(segments[segments.length - 2], newValue, coreIndex);
        }
        else {
            throw `Invalid register bitfield expression: ${uri}`;
        }
    }
    readDeviceAddressMap(settings) {
        this.deviceAddrsUserPreferenceDefaults.clear();
        this.deviceAddrsDefault = null;
        const deviceAddrsMap = settings.deviceAddrsMap;
        if (deviceAddrsMap) {
            Object.keys(deviceAddrsMap).forEach((blockName) => {
                const bindName = DEVICE_BLOCK_ADDRESS_BASE + blockName;
                const bind = this.getBinding(bindName);
                this.deviceAddrsUserPreferenceDefaults.set(bindName, deviceAddrsMap[blockName]);
                if (blockName === settings.deviceAddrsDefault) {
                    this.deviceAddrsDefault = bind;
                }
            });
            if (!settings.deviceAddrsDefault) {
                this.console.error('deviceAddrsMap is missing required deviceAddrsDefault member in the register.json file.');
            }
            else if (!(settings.deviceAddrsDefault in deviceAddrsMap)) {
                this.console.error('deviceAddrsDefault value does not match members in the deviceAddrsMap in the register.json file.');
            }
        }
    }
    getDeviceAddressForRegister(info) {
        let bind = info.__deviceAddressBinding;
        if (!bind) {
            const registerModel = info.registerModel ?? this;
            bind = registerModel.deviceAddrsDefault ?? registerModel.deviceAddrs;
            if (info.deviceAddrs) {
                registerModel.uriPrefix = DEVICE_BLOCK_ADDRESS_BASE;
                bind = registerModel.parseModelSpecificBindExpression(info.deviceAddrs) ?? bind;
                registerModel.uriPrefix = '';
            }
            info.__deviceAddressBinding = bind;
        }
        return bind.getValue();
    }
    /**
     * Retrieve the symbolic register information for a particular register or register field.
     *
     * @param uri binding name of the resister to retrieve the symbolic information for.
     */
    getRegisterInfo(uri) {
        return this.symbols.get(uri) || undefined;
    }
    static getBindingTypeFromUri(uri, segments) {
        const unexpectedCharacters = notIdentifierRegExp.exec(uri);
        if (unexpectedCharacters !== null || !uri) {
            return BIND_TYPE.BAD;
        }
        segments = segments || uri.split('.');
        if (segments[0] === '$cores') {
            switch (segments.length) {
                case 4: {
                    return (segments[1] === 'all' || !isNaN(+segments[1])) ? BIND_TYPE.FIELD : BIND_TYPE.BAD;
                }
                case 3: {
                    return segments[1] === 'all' ? BIND_TYPE.REGISTER_ALL : isNaN(+segments[1]) ? BIND_TYPE.BAD : BIND_TYPE.CORE_REGISTER;
                }
                default: {
                    return BIND_TYPE.BAD;
                }
            }
        }
        const firstSegmentFirstChar = segments[0].charAt(0);
        if (firstSegmentFirstChar === '$') {
            return BIND_TYPE.USER; // any uri beginning with a $
        }
        else if (firstSegmentFirstChar === calculatedBindingsPrefix) {
            return BIND_TYPE.CALCULATED;
        }
        else if (segments.length === 2) {
            return BIND_TYPE.FIELD;
        }
        else if (segments.length > 2) {
            return BIND_TYPE.BAD;
        }
        return BIND_TYPE.ACTIVE_REGISTER;
    }
    updateUserPreferenceBind(bind, bindName) {
        if (!bindName?.startsWith(DEVICE_BLOCK_ADDRESS_BASE)) {
            return;
        }
        const deviceAddrsBlockUri = this.deviceAddrsUserPreferenceDefaults.get(bindName);
        if (deviceAddrsBlockUri !== undefined) {
            this.uriPrefix = DEVICE_BLOCK_ADDRESS_BASE;
            bind.updateReferenceBinding('' + deviceAddrsBlockUri, this);
            this.uriPrefix = '';
            bind.status = null;
        }
        else {
            bind.status = Status.createErrorStatus(`Unknown User Preference Binding named: ${bind.toString()}`);
        }
    }
    updateCalculatedBind(bind) {
        let bindExpression;
        const bindName = bind.name;
        if (this.registerJsonData?.calculatedBindings && bindName) {
            bindExpression = this.registerJsonData?.calculatedBindings[bindName];
        }
        bind.updateReferenceBinding(bindExpression, this);
    }
    setParentEncoder(parent) {
        this.codec = parent;
    }
    deconfigure() {
        this.codec = undefined;
    }
    get _ignoreWriteOperationsWhenDisconnected() {
        return this.params.ignoreWriteOperationsWhenDisconnected || false;
    }
    loadRegisterInfo() {
        if (this.registerJsonFilename !== this.params.registerInfo) {
            this.registerJsonFilename = this.params.registerInfo;
            if (this.registerJsonFilename) {
                this.console.log(`Loading register information from file ${this.registerJsonFilename}`);
                this.readRegisterInfoPromise = GcFiles.readJsonFile(this.registerJsonFilename).then((symbols) => {
                    this.setSymbols(symbols);
                }).catch((err) => {
                    const message = `Failed to load register information form file ${this.registerJsonFilename}: ${err.message || err.toString()}`;
                    this.console.error(message);
                    throw Error(message);
                });
            }
        }
    }
    /**
     * Method used to let the register model know that the deviceId parameter passed ot the construct has been changed.
     * This will cause the selected device binding to notify listeners of changes to the deviceId.
     */
    onDeviceChanged() {
        this.selectedDeviceBind.setValue(this.params.deviceId);
    }
    async onConnect(transport) {
        super.onConnect(transport);
        this.deviceAddrs.setValue(this.params.deviceAddress === undefined ? undefined : +(this.params.deviceAddress ?? 0));
        this.loadRegisterInfo();
        // wait for register information to be read, if not already
        if (this.readRegisterInfoPromise) {
            await this.readRegisterInfoPromise;
            transport.assertStillConnecting();
        }
        if (this.params.verifyRegisterName) {
            transport.addProgressMessage('Verifying device ...');
            if (this.params.verifyDeviceAddress) {
                const deviceAddresses = GcUtils.parseArrayProperty(this.params.verifyDeviceAddress, [',']);
                if (!deviceAddresses || deviceAddresses.length < 2) {
                    throw Error(`Verification failed: Invalid property ${deviceAddresses} specified for "verifyDeviceAddress", which must contain two or more addresses separated by commas.`);
                }
                const badDeviceAddress = deviceAddresses.find(deviceAddress => isNaN(+deviceAddress));
                if (badDeviceAddress) {
                    throw Error(`Verification failed: Invalid device address ${badDeviceAddress} specified in "verifyDeviceAddress" property.`);
                }
                let foundAddress = '';
                for (let i = 0; i < deviceAddresses.length; i++) {
                    const deviceAddress = deviceAddresses[i].trim();
                    try {
                        this.deviceAddrs.setValue(+deviceAddress);
                        await this.doVerifyRegister(this.params, transport);
                        foundAddress = deviceAddress;
                        break;
                    }
                    catch (e) {
                        transport.addDebugMessage(`${e.message || e.toString()} for device address ${deviceAddress}`);
                    }
                }
                if (foundAddress) {
                    transport.addProgressMessage(`Verification successful using device address ${foundAddress}.`);
                }
                else {
                    throw Error(`Verification failed:  No device found at any of the following addresses ${deviceAddresses.join(',')}.`);
                }
            }
            else {
                await this.doVerifyRegister(this.params, transport);
            }
        }
    }
    async doVerifyRegister(params, transport) {
        const expectedValue = params.verifyValue;
        const value = await this.readValue(params.verifyRegisterName, 0);
        transport.assertStillConnecting();
        // if no verifyValue provided, assume we just want to verify the register can be read, and don't care about the value we get.
        if (expectedValue !== undefined) {
            const mask = BigInt(+(params.verifyMask ?? -1));
            if ((BigInt(value) & mask) !== (BigInt(+expectedValue) & mask)) {
                throw Error(`Verification failed.  Value read was ${value}, but it did not match the expected value of ${expectedValue}.`);
            }
        }
    }
    /**
     * Method to retrieve all register values in either csv, or json format.  This is typically used for saving registers to file at the request of the end user.
     *
     * @param format the format to save the register values into.
     * @returns string containing either the csv or json formatted register structure.
     */
    getRegisterData(format) {
        const registerBlocks = this.registerJsonData?.regblocks;
        if (!registerBlocks) {
            throw new Error('Cannot get registers because the register.json data are missing.');
        }
        const registerData = {
            signature: 'register-data',
            data: registerBlocks.filter(block => !block.attrs?.isHidden).reduce((result, block) => {
                const regs = block.registers.filter(reg => !reg.attrs?.writeonly).map(register => {
                    const symbolName = register.id || register.name;
                    return {
                        id: symbolName,
                        address: register.addr,
                        value: this.getBinding(symbolName)?.getValue() ?? undefined
                    };
                });
                result.push(...regs);
                return result;
            }, [])
        };
        if (format === 'csv') {
            const x = registerData.data.map(regInfo => `${regInfo.id}, ${regInfo.address}, ${regInfo.value}`).join('\n');
            return 'register, address, value\n' + registerData.data.map(regInfo => `${regInfo.id}, ${regInfo.address}, ${regInfo.value}`).join('\n');
        }
        return JSON.stringify(registerData, null, 4);
    }
    /**
     * Method to set all register values provided by either a csv, or json format text file.
     * This is typically used for loading registers from a text file at the request of the end user.
     *
     * @params jsonOrCsvContents text contents either in csv or json format.
     */
    setRegisterData(jsonOrCsvContents) {
        jsonOrCsvContents = jsonOrCsvContents.trim();
        let registerData;
        if (jsonOrCsvContents.startsWith('{') && jsonOrCsvContents.endsWith('}')) {
            try {
                const json = JSON.parse(jsonOrCsvContents);
                registerData = json.data ?? [];
            }
            catch (e) {
                throw new Error(`Failed to parse contents as a JSON file: ${e.message || e.toString()}`);
            }
        }
        else if (jsonOrCsvContents.startsWith('register,')) {
            const lines = jsonOrCsvContents.split('\n');
            if (lines.length < 2) {
                throw new Error('Failed to parse contents as csv file: expected more than one line with commas');
            }
            const titleRow = lines.splice(0, 1); // remove first element
            const fieldCount = titleRow[0].split(',').length;
            if (fieldCount < 2) {
                throw new Error('Failed to pares contents as csv file: expected first row to contain at least on comma separator');
            }
            registerData = lines.map(line => {
                line = line.trim();
                const fields = line.split(',');
                if (fields.length === 1) {
                    return {}; // go easy on extra lines with no commas, could just be blank line like at the end.
                }
                else if (fields.length !== fieldCount) {
                    throw new Error('Failed to parse contents as csv file: expected each row to have the same number of comma separators');
                }
                const id = fields[0].trim();
                const value = +fields[fieldCount - 1];
                return { id, value };
            });
        }
        else {
            throw new Error('Failed to parse contents as either JSON file or a csv file.');
        }
        registerData.forEach(({ id, value }) => {
            if (id && value !== undefined && !isNaN(value) && this.symbols.has(id) && !(this.symbols.get(id).attrs?.readonly)) {
                this.getBinding(id)?.setValue(value);
            }
        });
    }
}

export { RegisterModel, RegisterModelDecoderType, RegisterModelEncoderType, nullRegisterModelDecoder, nullRegisterModelEncoder };
//# sourceMappingURL=RegisterModel.js.map
