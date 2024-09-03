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
import { streamingDataEventType, staleChangedEventType, valueChangedEventType } from './IBindValue';
import { GcConsole as console } from '../../../gc-core-assets/lib/GcConsole';
import { statusChangedEventType, NAME } from './IBind';
import { DataConverter } from './DataConverter';
class AbstractBindListener {
    constructor(srcBinding, destBinding) {
        this.srcBinding = srcBinding;
        this.destBinding = destBinding;
        this.statusChangedHandler = () => this.destBinding.status = this.srcBinding.status;
    }
}
class StreamingListener extends AbstractBindListener {
    constructor(srcBinding, destBinding, computeValue) {
        super(srcBinding, destBinding);
        this.computeValue = computeValue;
        this.dataReceivedHandler = () => this.onDataReceived();
    }
    enable() {
        this.srcBinding.addEventListener(statusChangedEventType, this.statusChangedHandler);
        this.srcBinding.addEventListener(streamingDataEventType, this.dataReceivedHandler);
    }
    disable() {
        this.srcBinding.removeEventListener(statusChangedEventType, this.statusChangedHandler);
        this.srcBinding.removeEventListener(streamingDataEventType, this.dataReceivedHandler);
    }
    onDataReceived() {
        let newValue = this.srcBinding.getValue(); // always calculate new value in case srcBinding is an expression that needs to be evaluated.
        let srcType = this.srcBinding.getType();
        if (this.computeValue) {
            newValue = this.computeValue(newValue);
            srcType = undefined;
        }
        newValue = DataConverter.convert(newValue, srcType, this.destBinding.getType());
        this.destBinding.onStreamingDataReceived(newValue);
    }
}
class BindingListener extends AbstractBindListener {
    constructor(srcBinding, destBinding, computeValue) {
        super(srcBinding, destBinding);
        this.computeValue = computeValue;
        this.valueChangedHandler = (details) => this.onValueChanged(details.progress);
        this.staleChangedHandler = () => this.onStaleChanged();
    }
    onValueChanged(progress) {
        if (this.srcBinding.isStale()) {
            // defer passing the data along until the value has fully changed.
            this.srcBinding.addEventListener(staleChangedEventType, this.staleChangedHandler);
        }
        else {
            let newValue = this.srcBinding.getValue();
            const oldValue = this.destBinding.getValue();
            let srcType = this.srcBinding.getType();
            if (this.computeValue) {
                newValue = this.computeValue(newValue);
                srcType = undefined;
            }
            const destType = this.destBinding.getType();
            // protect against writing back values changed solely due to their conversion to and back again.
            // eslint-disable-next-line eqeqeq
            if (newValue != DataConverter.convert(oldValue, destType, srcType)) {
                newValue = DataConverter.convert(newValue, srcType, destType);
                this.destBinding.setValue(newValue, progress);
            }
        }
    }
    onStaleChanged() {
        if (!this.srcBinding.isStale()) {
            this.srcBinding.removeEventListener(staleChangedEventType, this.staleChangedHandler);
            this.onValueChanged(); // force the value to be synced
        }
    }
    enable() {
        this.srcBinding.addEventListener(statusChangedEventType, this.statusChangedHandler);
        this.srcBinding.addEventListener(valueChangedEventType, this.valueChangedHandler);
    }
    disable() {
        this.srcBinding.removeEventListener(statusChangedEventType, this.statusChangedHandler);
        this.srcBinding.removeEventListener(valueChangedEventType, this.valueChangedHandler);
    }
    get status() {
        return this.srcBinding.status;
    }
}
const nullListener = new (class {
    enable() {
        // do nothing
    }
    disable() {
        // do nothing
    }
    statusChangedHandler() {
        // do nothing
    }
});
export class DataBinder {
    constructor(targetBinding, modelBinding, getter, setter, oneWay = false) {
        this.targetBinding = targetBinding;
        this.modelBinding = modelBinding;
        this.getter = getter;
        this.setter = setter;
        this.targetListener = nullListener;
        this.modelListener = nullListener;
        this._enabled = false;
        // support for readOnly bindings, don't write values.
        if (oneWay || (getter && !setter)) {
            this.modelListener = DataBinder.createListener(modelBinding, targetBinding, getter);
        }
        else if (setter && !getter) {
            // switch model and target, so model gets initialized from the target.
            this.modelListener = DataBinder.createListener(targetBinding, modelBinding, setter);
        }
        else {
            // two-way binding support (with both getter or setter, or neither getter or setter (no computation)
            this.targetListener = DataBinder.createListener(targetBinding, modelBinding, setter);
            this.modelListener = DataBinder.createListener(modelBinding, targetBinding, getter);
        }
        this.enabled = true;
    }
    set enabled(enable) {
        if (this._enabled !== enable) {
            this._enabled = enable;
            if (enable) {
                this.targetListener.enable();
                this.modelListener.enable();
                // force model to sync the target value in case it changed
                // between disable() and subsequent enable() calls.
                if (typeof this.modelListener.onValueChanged === 'function') {
                    this.modelListener.onValueChanged();
                }
                // force status to be reflected in target as it now is in the
                // model, in case it change between time.
                this.modelListener.statusChangedHandler();
            }
            else {
                this.targetListener.disable();
                this.modelListener.disable();
            }
        }
    }
    get enabled() {
        return this._enabled;
    }
    dispose() {
        this.enabled = false;
    }
    static bind(targetBinding, modelBinding, getter, setter, oneWay = false) {
        if (targetBinding !== null && modelBinding !== null) {
            return new DataBinder(targetBinding, modelBinding, getter, setter, oneWay);
        }
        console.error(NAME, 'Cannot bind target and model bindings together because one of them is not an IBindValue.');
        return null;
    }
}
DataBinder.createListener = function (srcBinding, targetBinding, computeValue) {
    if (targetBinding.onStreamingDataReceived) {
        return new StreamingListener(srcBinding, targetBinding, computeValue);
    }
    else {
        return new BindingListener(srcBinding, targetBinding, computeValue);
    }
};
//# sourceMappingURL=DataBinder.js.map