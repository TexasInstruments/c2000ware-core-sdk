import { PrimitiveDataType, codecRegistry, abortEventType } from '../../gc-target-configuration/lib/TargetConfiguration';
import { VariableLookupBindValue, streamingDataEventType, AbstractBindFactory, DataStorageProvider, bindingRegistry } from '../../gc-core-databind/lib/CoreDatabind';
import { GcPromise } from '../../gc-core-assets/lib/GcPromise';

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
class StreamingDataBind extends VariableLookupBindValue {
    constructor(parentBind, fieldName) {
        super();
        this.parentBind = parentBind;
        this.fieldName = fieldName;
        this.setStale(true);
        // try to initialize value if parent is not stale.
        const stale = parentBind.isStale();
        if (!stale) {
            this.onDataReceived(parentBind.getValue());
        }
        this.parentBind.addEventListener(streamingDataEventType, (details) => this.onDataReceived(details.data));
    }
    onDataReceived(newValue) {
        try {
            const value = newValue[this.fieldName];
            if (value !== undefined) {
                this.setData(value);
                this.setStale(false);
            }
            // eslint-disable-next-line no-empty
        }
        catch (e) {
        }
    }
    onValueChanged(details) {
        this.sendValue(details.newValue);
    }
    sendValue(value) {
        const data = {};
        data[this.fieldName] = value;
        this.parentBind.sendValue(data);
    }
    receiveValue(value) {
        this.updateValue(value);
    }
}
class RawStreamingDataBind extends VariableLookupBindValue {
    constructor(model) {
        super();
        this.model = model;
    }
    sendValue(value) {
        this.model.sendValue(value);
    }
    receiveValue(value) {
        this.updateValue(value);
    }
}
const streamingCodecDataType = new PrimitiveDataType('object');
/**
 * class that provides default implementation of IBindFactory for a streaming data model.  This class
 * implements the createNewBind() method for IBindFactory.  This model provides a $rawData binding that
 * stores the raw decoded object data received over the transport, and it provides value bindings to nested members within
 * that structure.  Binding names represent members within the raw data, and nested members are supported with the dot operator;
 * for example, "parent.child" would bind to a child member of the parent member within the raw data object.
 * Bindings are only updated when the member exists in the raw data.  That means that the transport does not need to send the
 * entire raw data structure every time, and can only send a raw data structure that only contains the changed members if it
 * so chooses.  However, if the data needs to be plotted against time, then that data needs to be transmitted on a periodic basis
 * regardless of whether or not it has changed.
*/
class StreamingDataModel extends AbstractBindFactory {
    /**
     * Constructor for streaming model
     *
     * @param params parameters for constructing the streaming model.
    */
    constructor(params) {
        super(params.id || 'uart');
        this.params = params;
        this.decoderInputType = streamingCodecDataType;
        this.decoderOutputType = streamingCodecDataType;
        this.onAbortEventHandler = () => {
            if (this.connectPromise) {
                this.connectPromise.reject('Aborted.');
                this.connectPromise = undefined;
            }
        };
        this.channelName = params.channelName;
        DataStorageProvider.addDataModel(this);
        this.streamingDataBind = new RawStreamingDataBind(this);
        this.streamingDataBind.setIndex();
        bindingRegistry.registerModel(this);
        codecRegistry.register(this);
    }
    dispose() {
        super.dispose();
        codecRegistry.unregister(this);
    }
    createNewBind(name) {
        if (name === '$rawData') {
            return this.streamingDataBind;
        }
        const pos = name.lastIndexOf('.');
        let parentBind;
        if (pos > 0) {
            parentBind = this.getBinding(name.substring(0, pos));
            name = name.substring(pos + 1);
        }
        else {
            parentBind = this.streamingDataBind;
        }
        return new StreamingDataBind(parentBind, name);
    }
    sendValue(nextValue) {
        if (this.streamingCodec) {
            const data = nextValue;
            if (this.channelName) {
                const data = {};
                data[this.channelName] = nextValue;
            }
            this.streamingCodec.encode(data);
        }
    }
    decode(nextValue) {
        if (this.connectPromise) {
            this.connectPromise.resolve();
            this.connectPromise = undefined;
        }
        const data = this.channelName ? nextValue[this.channelName] : nextValue;
        if (data) {
            this.streamingDataBind.receiveValue(data);
            return true;
        }
        return false;
    }
    /**
     * Implementation for reading value from the target, by waiting for next streaming data event.
     *
     * @param uri the name of the binding to read
     * @return a promise that resolves to the value read.
     */
    scriptRead(uri) {
        return new Promise((resolve, reject) => {
            const binding = this.getBinding(uri);
            if (binding) {
                const listener = (params) => {
                    binding.removeEventListener(streamingDataEventType, listener);
                    resolve(params.data);
                };
                binding.addEventListener(streamingDataEventType, listener);
            }
            else {
                reject(`Failed to read value since bind "${uri}" does not exist.`);
            }
        });
    }
    setParentEncoder(parent) {
        this.streamingCodec = parent;
    }
    deconfigure() {
        this.streamingCodec = undefined;
    }
    async onConnect(transport) {
        transport.addEventListener(abortEventType, this.onAbortEventHandler);
        try {
            if (this.params.timeout !== 0) { // skip waiting for data if app specifically wants a zero timeout.
                this.connectPromise = GcPromise.defer();
                transport.addProgressMessage('Waiting for data ...', 'Please ensure your hardware is actually transmitting data on the same USB port.');
                await GcPromise.timeout(this.connectPromise.promise, (this.params.timeout || 3000), `Timeout waiting for data from ${this.params.deviceId || 'target'}`);
            }
            super.onConnect(transport);
        }
        finally {
            transport.removeEventListener(abortEventType, this.onAbortEventHandler);
        }
    }
    get optional() {
        return this.params.optional;
    }
    get deviceId() {
        return this.params.deviceId;
    }
}

export { StreamingDataModel, streamingCodecDataType };
//# sourceMappingURL=StreamingDataModel.js.map
