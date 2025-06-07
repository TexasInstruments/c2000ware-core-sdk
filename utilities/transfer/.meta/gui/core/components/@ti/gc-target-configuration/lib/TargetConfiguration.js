import { GcPromise } from '../../gc-core-assets/lib/GcPromise';
import { EventType, Events } from '../../gc-core-assets/lib/Events';

class EncoderType {
    constructor(name) {
        this.name = name;
    }
    asEncoder(encoder) {
        if (!this.isCompatible(encoder.encoderInputType)) {
            throw new Error(`Type Mismatch.  ${encoder.id}'s encoder type ${encoder.encoderInputType.name} is not compatible with ${this.name}`);
        }
        return encoder;
    }
    isCompatible(type) {
        return this === type || type === NoopEncoderType;
    }
}
class DecoderType {
    constructor(name) {
        this.name = name;
    }
    asDecoder(decoder) {
        if (!this.isCompatible(decoder.decoderInputType)) {
            throw new Error(`Type Mismatch.  ${decoder.id}'s encoder type ${decoder.decoderInputType.name} is not compatible with ${this.name}`);
        }
        return decoder;
    }
    isCompatible(type) {
        return this === type || type === NoopDecoderType;
    }
}
const NoopEncoderType = new EncoderType('void');
const NoopDecoderType = new DecoderType('void');
const NoopDataEncoderType = new EncoderType('void');
const NoopDataDecoderType = new DecoderType('void');
class PrimitiveDataType extends EncoderType {
    asDecoder(decoder) {
        if (!this.isCompatible(decoder.decoderInputType)) {
            throw new Error(`Type Mismatch.  ${decoder.id}'s encoder type ${decoder.decoderInputType.name} is not compatible with ${this.name}`);
        }
        return decoder;
    }
}
class CompositeDataType extends PrimitiveDataType {
    constructor(...inputTypes) {
        super(`${inputTypes.map((type) => type.name).join('|')}`);
        this.baseTypes = inputTypes;
    }
    isCompatible(outputType) {
        return this.baseTypes.reduce((result, type) => result || type.isCompatible(outputType), false);
    }
}
class CompositeEncoderType extends EncoderType {
    constructor(...inputTypes) {
        super(`${inputTypes.map((type) => type.name).join('|')}`);
        this.baseTypes = inputTypes;
    }
    isCompatible(outputType) {
        return this.baseTypes.reduce((result, type) => result || type.isCompatible(outputType), false);
    }
}
class CompositeDecoderType extends DecoderType {
    constructor(...inputTypes) {
        super(`${inputTypes.map((type) => type.name).join('|')}`);
        this.baseTypes = inputTypes;
    }
    isCompatible(outputType) {
        return this.baseTypes.reduce((result, type) => result || type.isCompatible(outputType), false);
    }
}
const bufferDataType = new PrimitiveDataType('buffer');
const binaryDataType = new PrimitiveDataType('uint8array');
const stringDataType = new PrimitiveDataType('string');
const bufferOrStringDataType = new CompositeDataType(stringDataType, bufferDataType);
const binaryOrBufferDataType = new CompositeDataType(binaryDataType, bufferDataType);

/**
 *  Copyright (c) 2020, 2025 Texas Instruments Incorporated
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
const connectionLogEventType = new EventType('ConnectionLog');
function capitalize(text) {
    return text.charAt(0).toUpperCase() + text.slice(1);
}
class AbstractConnectionLogger extends Events {
    constructor() {
        super(...arguments);
        this.lastLog = {
            message: '',
            type: 'info',
            timestamp: Date.now()
        };
    }
    addProgressMessage(message, tooltip, percent = 0) {
        if (this.lastLog.message !== message) {
            this.console.info(message); // don't pollute the console log with the same message every time the percent is updated.
        }
        if (this.lastLog.type === 'info') {
            this.lastLog.message = message;
            this.lastLog.tooltip = tooltip;
            this.lastLog.timestamp = Date.now();
        }
        this.fireLoggingMessage('info', message, percent);
    }
    addErrorMessage(message, tooltip, fatal = false) {
        if (this.lastLog.type !== 'fatal' || fatal) {
            this.lastLog.message = 'Error: ' + message;
            this.lastLog.tooltip = tooltip;
            this.lastLog.type = fatal ? 'fatal' : 'error';
            this.lastLog.timestamp = Date.now();
        }
        this.console.error(message);
        this.fireLoggingMessage('error', message);
    }
    addWarningMessage(message, tooltip) {
        if (!this.hasErrors) {
            this.lastLog.message = 'Warning: ' + message;
            this.lastLog.tooltip = tooltip;
            this.lastLog.type = 'warning';
            this.lastLog.timestamp = Date.now();
        }
        this.console.warning(message);
        this.fireLoggingMessage('warning', message);
    }
    addDebugMessage(message) {
        this.console.log(message);
        this.fireLoggingMessage('debug', message);
    }
    fireLoggingMessage(type, message, percent) {
        if (message) {
            this.fireEvent(connectionLogEventType, { type: type, message: capitalize(message), transportId: this.id, percent });
        }
    }
    clearProgressMessage() {
        this.lastLog = {
            message: '',
            type: 'info',
            timestamp: Date.now()
        };
    }
    get progressMessage() {
        return this.lastLog.message.split('\n')[0];
    }
    get progressMessageTimestamp() {
        return this.lastLog.timestamp;
    }
    get tooltipMessage() {
        return this.lastLog.tooltip || this.lastLog.message.split('\n').slice(1).join('\n');
    }
    get hasErrors() {
        return this.lastLog.type === 'error' || this.lastLog.type === 'fatal';
    }
    get hasWarnings() {
        return this.lastLog.type === 'warning';
    }
}

function OR(x, y) {
    return (x === 'yes' || y === 'yes') ? 'yes' : (x === 'maybe' || y === 'maybe') ? 'maybe' : 'no';
}
const invalidNameRegEx = /[^0-9a-zA-Z_.$]/;
class CodecInfo {
    constructor(codec) {
        this.codec = codec;
        this.inUse = false;
        this.isConnected = false;
        this.children = [];
        this.order = -1;
    }
    isDeviceRequired(deviceId, recursive = false) {
        let result = 'no';
        if (this.codec.deviceId === deviceId) {
            result = 'yes';
        }
        else if (recursive) {
            result = this.children.reduce((isUsed, child) => OR(isUsed, child.isDeviceRequired(deviceId, recursive)), 'no');
        }
        return this.isOptional() && result === 'yes' ? 'maybe' : result;
    }
    isOptional() {
        if (this.codec.optional) {
            // case 1: specifically marked as optional
            return true;
        }
        else if (this.children.length === 0) {
            // case 2: no children and not optional
            return false;
        }
        else {
            // case 3: not optional, but all children are optional.
            return this.children.reduce((result, child) => result && child.isOptional(), true);
        }
    }
    isPartiallyConnected() {
        return this.isConnected && this.children.reduce((result, child) => {
            return result || !child.isConnected || child.isPartiallyConnected();
        }, false);
    }
    async disconnect(transport) {
        for (let i = 0; i < this.children.length; i++) {
            try {
                const child = this.children[i];
                await child.disconnect(transport);
            }
            catch (err) {
                // ignore errors on child disconnect, there is no recovery for a failed disconnect.
            }
        }
        if (this.codec.onDisconnect && this.isConnected) {
            try {
                transport.addDebugMessage(`Disconnecting ${this.codec.toString()}`);
                await this.codec.onDisconnect(transport);
            }
            catch (err) {
                transport.addWarningMessage(`${this.codec.toString()} failed to disconnect: ${err}`);
            }
        }
        this.isConnected = false;
    }
    async connect(transport, failedDevicesList) {
        this.isConnected = false;
        if (this.codec.onConnect) {
            failedDevicesList.forEach((deviceId) => {
                if (this.isDeviceRequired(deviceId, true) === 'yes' || this.isDeviceRequired(deviceId, false) !== 'no') {
                    throw Error(`Program was not loaded successfully for ${deviceId}.`);
                }
            }, true);
            transport.assertStillConnecting();
            try {
                transport.addDebugMessage(`Connecting ${this.codec.toString()}`);
                await this.codec.onConnect(transport);
            }
            catch (err) {
                transport.addDebugMessage(`${this.codec.toString()} failed to connect: ${err}`);
                await this.codec.onDisconnect?.(transport);
                throw err;
            }
        }
        this.isConnected = true;
        let childConnectCount = 0;
        for (let i = 0; i < this.children.length; i++) {
            const child = this.children[i];
            transport.assertStillConnecting();
            try {
                await child.connect(transport, failedDevicesList);
                childConnectCount++;
            }
            catch (err) {
                transport.assertStillConnecting();
                if (!child.isOptional()) {
                    throw err;
                }
            }
        }
        // when multiple children are all optional, we assume at least one is expected to connect.
        if (childConnectCount === 0 && this.children.length > 1) {
            throw Error('One or more codecs failed to connect without error.');
        }
    }
    async ping() {
        if (this.isConnected) {
            if (this.codec.ping) {
                await this.codec.ping();
            }
            for (let i = 0; i < this.children.length; i++) {
                const child = this.children[i];
                await child.ping();
            }
        }
    }
    doDeconfigure() {
        if (this.inUse && this.codec.deconfigure) {
            this.codec.deconfigure();
        }
        this.inUse = false;
        this.isConnected = false;
        this.children = [];
        this.order = -1;
    }
    doConfigure(children, order) {
        if (this.codec.configure) {
            this.codec.configure();
        }
        this.inUse = true;
        this.children = children;
        this.order = order;
    }
}
class CodecRegistry {
    constructor() {
        this.instances = new Map();
        this.waitForCodecs = new Map();
        this.order = 1;
    }
    configure(configuration) {
        // deconfigure any existing configuration.
        this.instances.forEach((item) => item.doDeconfigure());
        // construct the new configuration.
        configuration = configuration.trim();
        if (configuration.length === 0) {
            throw Error('The config specification was empty.');
        }
        try {
            this.order = 1; // reset the order codec order for the new configuration
            this.parseConfigurationList(configuration);
        }
        catch (e) {
            throw Error(`Invalid configuration specified: ${capitalize(e.message)} in "${configuration}".`);
        }
    }
    parseConfigurationChain(config, children) {
        const pos = config.indexOf('(');
        if (pos >= 0) {
            if (config.endsWith(')')) {
                if (children.length > 0) {
                    throw Error(`The configuration must represent a tree, but child nodes found after: "${config}"`);
                }
                const childConfig = config.substring(pos + 1, config.length - 1).trim();
                if (childConfig.length === 0) {
                    throw Error('Operator () is empty, but was expecting a comma separated list of child nodes');
                }
                children = this.parseConfigurationList(childConfig);
                const parentChain = config.substring(0, pos).trim();
                if (parentChain.length === 0) {
                    throw Error(`Operator () is missing the parent node, which was expected before the opening parentheses of "${config}"`);
                }
                return this.parseConfigurationChain(parentChain, children);
            }
            else {
                throw Error(`Operator () is missing a closing parenthesis ")" at the end of "${config}"`);
            }
        }
        else {
            const nodes = config.split('+');
            let codecInfo;
            for (let i = nodes.length; i-- > 0;) {
                const nodeName = nodes[i].trim();
                if (nodeName.length === 0) {
                    if (i === 0) {
                        throw Error(`Operator + is missing it's left parameter in "${config}"`);
                    }
                    throw Error(`Operator + is missing it's right parameter in "${nodes[i - 1]}+"`);
                }
                codecInfo = this.getInstanceInfo(nodeName);
                if (codecInfo.inUse) {
                    throw Error(`${codecInfo.codec.toString()} is used twice`);
                }
                if (children.length > 0) {
                    const parent = codecInfo.codec;
                    // Got TS2774 when writing as if (!(parent.addChildDecoder && parent.encoderInputType && parent.encoderOutputType))
                    if (parent.addChildDecoder === undefined || parent.encoderInputType === undefined || parent.encoderOutputType === undefined) {
                        throw Error(`Invalid parent node.  "${parent.id}" is not an IEncoder.`);
                    }
                    children.forEach((c) => {
                        const child = c.codec;
                        // Got TS2774 when writing as if (!(child.setParentEncoder && child.decoderInputType && child.decoderOutputType))
                        if (child.setParentEncoder === undefined || child.decoderInputType === undefined || child.decoderOutputType === undefined) {
                            throw Error(`Invalid child node.  "${child.id}" is not an IDecoder`);
                        }
                        if (child.decoderInputType.isCompatible(parent.encoderOutputType)) {
                            if (parent.encoderInputType.isCompatible(child.decoderOutputType)) {
                                parent.addChildDecoder(child);
                                child.setParentEncoder(parent);
                            }
                            else {
                                throw Error(`Type Mismatch: ${parent.id} input type "${parent.encoderInputType.name}" is incompatible with ${child.id} output type "${child.decoderOutputType.name}"`);
                            }
                        }
                        else {
                            throw Error(`Type Mismatch: ${parent.id} output type "${parent.encoderOutputType.name}" is incompatible with ${child.id} input type "${child.decoderInputType.name}"`);
                        }
                    });
                }
                codecInfo.doConfigure(children, this.order++);
                children = [codecInfo];
            }
            return codecInfo;
        }
    }
    parseConfigurationList(config) {
        const segments = config.split(','); // comma delimited including commas inside parentheses.
        const configs = []; // comma delimited excluding commas inside parentheses.
        let indent = 0; // level of nesting within braces, zero for outside, positive for inside.
        let activeSegment = '';
        for (let i = 0; i < segments.length; i++) {
            const nextSegment = segments[i].trim();
            indent += nextSegment.split('(').length - nextSegment.split(')').length;
            activeSegment += nextSegment;
            if (indent === 0) {
                configs.push(activeSegment);
                activeSegment = '';
            }
            else if (indent < 0) { // too many closing braces
                throw Error('Mis-matched parentheses');
            }
            else { // indent > 0
                activeSegment += ','; // current segment needs to be joined to next segment with a comma between.
            }
        }
        if (indent !== 0) {
            throw Error('Mis-matched parentheses');
        }
        if (configs.reduce((state, value) => state || value.length === 0, false)) {
            throw Error(`Missing at least one child in this comma separated list "${config}"`);
        }
        return configs.map((child) => this.parseConfigurationChain(child, []));
    }
    validateCodecName(name) {
        name = name.toLowerCase();
        if (!(name && name.match(invalidNameRegEx) === null)) {
            throw Error(`Bad identifier "${name}".  Identifiers for Codecs, models, and transports must only contain numbers, letters, underscore, period, or $ characters.`);
        }
        return name;
    }
    /**
     * Method for registering codecs for use in active configurations.  Only codecs with id's will be registered.
     *
     * @param instance - the instance of the codec to register.
     */
    register(instance) {
        if (instance.id) {
            const id = this.validateCodecName(instance.id);
            this.instances.set(id, new CodecInfo(instance));
            const promise = this.waitForCodecs.get(id);
            if (promise) {
                promise.resolve();
            }
        }
    }
    /**
     * Method for unregistering codecs no longer to be use in active configurations.
     *
     * @param instance - the instance of the codec to unregister.
     */
    unregister(instance) {
        if (instance.id) {
            const info = this.instances.get(instance.id);
            if (info && info.codec === instance) { // only remove it, if it has been overridden by another instance with the same name already.
                this.instances.delete(instance.id);
                this.waitForCodecs.delete(instance.id);
            }
        }
    }
    getInstanceInfo(name) {
        const id = this.validateCodecName(name);
        const result = this.instances.get(id);
        if (!result) {
            throw Error(`Missing a model, transport, or codec with id="${name}"`);
        }
        return result;
    }
    getInstance(name) {
        return this.getInstanceInfo(name).codec;
    }
    isActive(name) {
        return this.getInstanceInfo(name).inUse;
    }
    isConnected(name) {
        return this.getInstanceInfo(name).isConnected;
    }
    isPartiallyConnected(name) {
        return this.getInstanceInfo(name).isPartiallyConnected();
    }
    ping(name) {
        return this.getInstanceInfo(name).ping();
    }
    connect(name, transport, failedDevicesList = []) {
        return this.getInstanceInfo(name).connect(transport, failedDevicesList);
    }
    disconnect(name, transport) {
        return this.getInstanceInfo(name).disconnect(transport);
    }
    isOptional(name) {
        return this.getInstanceInfo(name).isOptional();
    }
    isDeviceRequired(names, deviceId, recursive = false) {
        if (names instanceof Array) {
            return names.reduce((isUsed, name) => OR(isUsed, this.getInstanceInfo(name).isDeviceRequired(deviceId, recursive)), 'no');
        }
        else {
            return this.getInstanceInfo(names).isDeviceRequired(deviceId, recursive);
        }
    }
    compareOrder(name1, name2) {
        return this.getInstanceInfo(name1).order - this.getInstanceInfo(name2).order;
    }
    async whenConfigurationReady(configuration) {
        const ids = configuration.toLowerCase().split(/[,()+]+/g);
        for (let i = 0; i < ids.length; i++) {
            const id = ids[i].trim();
            if (id && id.match(invalidNameRegEx) === null && !this.instances.get(id)) {
                if (!this.waitForCodecs.get(id)) {
                    this.waitForCodecs.set(id, GcPromise.defer());
                }
                await this.waitForCodecs.get(id).promise;
            }
        }
    }
    dispose() {
        this.instances = new Map();
        this.waitForCodecs = new Map();
    }
}
const codecRegistry = new CodecRegistry();

/**
 *  Copyright (c) 2020, 2025 Texas Instruments Incorporated
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
/**
 * Null codec to be used in lieu of null pointers.
 */
const nullDataCodec = new (class {
    constructor() {
        this.decoderInputType = NoopDataDecoderType;
        this.decoderOutputType = NoopDataEncoderType;
        this.encoderInputType = NoopDataEncoderType;
        this.encoderOutputType = NoopDataDecoderType;
        this.id = '';
    }
    addChildDecoder() {
    }
    setParentEncoder() {
    }
    dispose() {
    }
    encode(data) {
    }
    decode(data) {
        return false;
    }
})();
/**
 * Abstract Encoder implementation that manages the targetDecoder pointer.
 */
class AbstractEncoder extends Events {
    constructor(id, encoderInputType, encoderOutputType) {
        super();
        this.id = id;
        this.encoderInputType = encoderInputType;
        this.encoderOutputType = encoderOutputType;
        codecRegistry.register(this);
    }
    addChildDecoder(child) {
        this.targetDecoder = child;
    }
    get optional() {
        return this.params.optional;
    }
    get deviceId() {
        return this.params.deviceId;
    }
    toString() {
        return `codec id="${this.id}"`;
    }
    dispose() {
    }
}
/**
 * Abstract decoder implementation that manages the targetEncoder pointer.
 */
class AbstractDecoder extends Events {
    constructor(id, decoderInputType, decoderOutputType) {
        super();
        this.id = id;
        this.decoderInputType = decoderInputType;
        this.decoderOutputType = decoderOutputType;
        codecRegistry.register(this);
    }
    setParentEncoder(parent) {
        this.targetEncoder = parent;
    }
    get optional() {
        return this.params.optional;
    }
    get deviceId() {
        return this.params.deviceId;
    }
    toString() {
        return `codec id="${this.id}"`;
    }
    dispose() {
        codecRegistry.unregister(this);
    }
}
/**
 * Abstract codec implementation that manages both the targetEncoder, and the targetDecoder, pointers.
 */
class AbstractCodec extends AbstractDecoder {
    constructor(id, decoderInputType, decoderOutputType, encoderOutputType, encoderInputType) {
        super(id, decoderInputType, decoderOutputType);
        this.encoderOutputType = encoderOutputType;
        this.encoderInputType = encoderInputType;
    }
    addChildDecoder(child) {
        this.targetDecoder = child;
    }
}
/**
 * Abstract data decoder implementation that manages the targetEncoder pointer.
 */
class AbstractDataDecoder extends AbstractDecoder {
    constructor(id, decoderInputType, decoderOutputType) {
        super(id, decoderInputType, decoderOutputType);
        this.targetEncoder = nullDataCodec;
    }
    deconfigure() {
        this.targetEncoder = nullDataCodec;
    }
}
/**
 * Abstract data encoder implementation that manages the targetDecoder pointer.
 */
class AbstractDataEncoder extends AbstractEncoder {
    constructor(id, encoderInputType, encoderOutputType) {
        super(id, encoderInputType, encoderOutputType);
        this.targetDecoder = nullDataCodec;
    }
    deconfigure() {
        this.targetDecoder = nullDataCodec;
    }
}
/**
 * Abstract data codec implementation that manages both the targetEncoder, and the targetDecoder pointers.
 */
class AbstractDataCodec extends AbstractDataDecoder {
    constructor(id, decoderInputType, decoderOutputType, encoderOutputType, encoderInputType) {
        super(id, decoderInputType, decoderOutputType);
        this.encoderOutputType = encoderOutputType;
        this.encoderInputType = encoderInputType;
        this.targetDecoder = nullDataCodec;
    }
    addChildDecoder(child) {
        if (this.targetDecoder && this.targetDecoder !== nullDataCodec) {
            // eslint-disable-next-line @typescript-eslint/no-use-before-define
            this.targetDecoder = new DataDecoderTap(child, this.targetDecoder, this.encoderOutputType, this.encoderInputType);
        }
        else {
            this.targetDecoder = child;
        }
    }
    deconfigure() {
        super.deconfigure();
        this.targetDecoder = nullDataCodec;
    }
}
class DataDecoderTap extends AbstractDataDecoder {
    constructor(targetDecoder, next, decoderInputType, decoderOutputType) {
        super('tap', decoderInputType, decoderOutputType);
        this.targetDecoder = targetDecoder;
        this.next = next;
        this.params = {};
    }
    decode(data) {
        const result1 = this.targetDecoder.decode(data);
        const result2 = this.next.decode(data);
        return result1 instanceof Error ? result1 : result2 instanceof Error ? result2 : result1 && result2;
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
/**
 * Abstract class for a packet frame decoder.  A frame decoder is used to detect/align the start of packets
 * in a stream of data received over a transport like USB.  The derived class must implement the getPacketLength()
 * method to validate and calculate the length of each possible packet of data.  The base implementations of decode()
 * method will repeatedly call this method to test for possible packets.  Optionally, the derived class can provide
 * a start byte, which the base implementation will use to skip past packets that do not start with the exact byte
 * automatically.
 *
 * @constructor
 * @param id - identifier for this decoder
 * @param {Number} [startByte] - the first byte(s) used to identify the start of a packet header.
 */
class AbstractFrameDecoder extends AbstractDataDecoder {
    constructor(id, ...startBytes) {
        super(id, binaryOrBufferDataType, bufferDataType);
        this.partialPacket = null;
        this.isReceivingValidPackets = false;
        this.startBytes = startBytes;
    }
    isStartOfPacket(rawData, offset) {
        const length = Math.min(rawData.length - offset, this.startBytes.length);
        for (let i = 0; i < length; i++) {
            if (rawData[i + offset] !== this.startBytes[i]) {
                return false;
            }
        }
        return true;
    }
    /**
     * Detect and align valid packet(s).  This method relies on the getPacketLength()
     * method implemented by the derived class to  perform this function.
     * This method may detect multiple packets, each aligned packet is passed to decodePacket().
     */
    detectPackets(rxData) {
        let result = this.isReceivingValidPackets;
        let data = rxData instanceof Uint8Array ? [...rxData] : rxData;
        if (this.partialPacket) {
            // concatenate new data with saved partial data
            // FYI  _.push.apply(_, data) is faster than _.concat([...data])
            // eslint-disable-next-line prefer-spread
            Array.prototype.push.apply(this.partialPacket, data);
            data = this.partialPacket;
            this.partialPacket = null;
        }
        let i = 0;
        const length = data.length;
        // process one or more packets (whether valid or not).
        while (i < length) {
            // skip till first delimiter(s), if provided.
            while (i < length && !this.isStartOfPacket(data, i)) {
                i++;
                this.isReceivingValidPackets = false;
            }
            if (i < length) {
                // calculate the length of the packet, zero if not enough data to determine, and -1 for error packets
                const packetLength = this.getPacketLength(data, i);
                if (packetLength > 0 && packetLength + i <= length) {
                    // enough data to decode a packet.
                    result = this.decodePacket((i === 0 && length === packetLength) ? data : data.slice(i, i + packetLength));
                    this.isReceivingValidPackets = result === true;
                    if (this.isReceivingValidPackets) {
                        // valid packet processed, skip forward
                        i += packetLength;
                    }
                    else {
                        // invalid packet decoded, skip forward only by one byte to search for start of valid packet.
                        i++;
                    }
                }
                else if (packetLength < 0) {
                    // invalid packet already, skip forward one or more bytes.
                    i -= packetLength;
                    this.isReceivingValidPackets = false;
                    result = new Error('Invalid packet received.');
                }
                else if (i === 0) {
                    // no data consumed, save all data for next pass.
                    this.partialPacket = data;
                    break;
                }
                else if (i < length) {
                    // not enough data remaining for a single packet, defer the partial packet until more data has arrived.
                    this.partialPacket = data.slice(i);
                    break;
                }
            }
        }
        return result;
    }
    deconfigure() {
        super.deconfigure();
        this.partialPacket = null;
        this.isReceivingValidPackets = false;
    }
    /**
     * For use cases like transport <--> frame decoder <--> a codec in v2.
     * For use cases like transport <--> a codec whose base class is AbstractFrameDecoder.
     * the codec can override decodePacket.
     */
    decode(rxData) {
        return this.detectPackets(rxData);
    }
}
/**
 * Abstract class for a data codec using a packet frame decoder.  This is a helper base class to make it easier to implement
 * a data codec with a frame decoder.  @See {@link AbstractFrameDecoder} for more information on the requirements of the
 * frame decoder.
 *
 * @constructor
 * @param id - identifier for this data codec
 * @param encoderInputType - the input type for encoding data going to the target.
 * @param {Number} [startByte] - the first byte(s) used to identify the start of a packet header.
 */
class AbstractDataCodecWithFrameDecoder extends AbstractFrameDecoder {
    constructor(id, encoderInputType, ...startBytes) {
        super(id, ...startBytes);
        this.encoderInputType = encoderInputType;
        this.targetDecoder = nullDataCodec;
        this.encoderOutputType = this.encoderInputType;
    }
    addChildDecoder(child) {
        this.targetDecoder = child;
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
class FIFOCommandResponseQueue {
    constructor(name) {
        this.name = name;
        this.first = this.last = {};
    }
    addCommand(command, sequenceNumber) {
        const deferred = GcPromise.defer();
        this.last.next =
            {
                seqNo: sequenceNumber,
                command: command,
                deferred: deferred
            };
        this.last = this.last.next;
        return deferred.promise;
    }
    addResponse(response, command, sequenceNumber, isError = false) {
        let step = -1;
        let missingResponseLimit = sequenceNumber === this.last.seqNo ? 0 : -2;
        for (let prev = this.first, cur = prev.next; cur && step < 0; prev = cur, cur = cur.next) {
            step = sequenceNumber === undefined ? 0 : cur.seqNo - sequenceNumber;
            if (step < -100) {
                step += 255;
            }
            else if (step > 100) {
                step -= 255;
            }
            if (step < missingResponseLimit) {
                cur.deferred?.reject(this.name + ' error: missing response for command sequence #' + cur.seqNo);
                // remove item from list
                prev.next = cur.next;
                if (!cur.next) {
                    this.last = prev; // move end pointer when removing the last element.
                }
                cur = prev;
                missingResponseLimit = -2;
            }
            else if (step === 0) {
                if (cur.command !== command) {
                    cur.deferred.reject(this.name + ' error: Command Mismatch.  Expected ' + cur.command + ', but received ' + command);
                    if (sequenceNumber === undefined) {
                        step = -1; // continue looping until we find a command that matches
                    }
                }
                else if (isError) {
                    cur.deferred.reject(response);
                }
                else {
                    cur.deferred.resolve(response);
                }
                // remove item from list
                prev.next = cur.next; // remove item from list
                if (!cur.next) {
                    this.last = prev; // move end pointer when removing the last element.
                }
                cur = prev;
            }
        }
    }
    clearAll() {
        for (let cur = this.first.next; cur !== undefined; cur = cur.next) {
            cur.deferred.reject('Skipping response from ' + this.name + ' due to reset operation');
        }
        this.first = this.last = {};
    }
    isEmpty() {
        return this.first.next === undefined;
    }
    get length() {
        let count = 0;
        for (let cur = this.first.next; cur !== undefined; cur = cur.next) {
            count++;
        }
        return count;
    }
}
/**
 * Abstract class for command/response, message based, packet codecs.  This class manages messages
 * sent and received from a controller/firmware.  This class provides helper methods for adding
 * commands to a queue waiting for responses from the controller/firmware and associating responses with
 * the appropriate command.  Messages can optionally have command id's as well as sequence numbers to aid in
 * matching up responses to commands.  If not provided, all commands are expected to have responses, and then must
 * be processed in order.  If sequence numbers are provided, commands will be matched up by sequence number, but
 * they still must be processed in order.  Out of order responses, with sequence numbers, are not supported.
 */
class AbstractMessageBasedDecoder extends AbstractDataDecoder {
    /**
     * Base constructor that must be called from the concrete class's constructor using super();
     *
     * @param name the id of this codec
     * @param console a console instance to write logs to
     * @param maxOutstandingCommands maximum number of commands that can be sent before any response.
     */
    constructor(name, console, maxOutstandingCommands = 0) {
        super(name, binaryOrBufferDataType, bufferDataType);
        this.console = console;
        this.maxOutstandingCommands = maxOutstandingCommands;
        this.pendingTransmissions = undefined;
        this.commandQueue = new FIFOCommandResponseQueue(name);
        // this.initAnalytics();
    }
    /**
     * Implementation of the disconnect method.  This method clears the command/response queue on disconnect.
     * If you override this method, be sure to call this base method in addition to other cleanup activities.
     */
    onDisconnect() {
        this.commandQueue.clearAll();
        this.pendingTransmissions = undefined;
        return Promise.resolve();
    }
    logPacket(name, message, buffer, len) {
        this.console.debug(function () {
            len = len || buffer.length;
            for (let i = 0; i < len; i++) {
                message = message + buffer[i].toString(16) + ', ';
            }
            return message;
        });
    }
    /**
     * Implementation of the IPacketCodec.encode() method.  This implementation logs the encoded packet using
     * GcConsole.debug() method for debug purposes before forwarding the packet to the next
     * encoder in the packet encoding chain.  The derived implementation should call this
     * method to send packets to the target.
     *
     * @param data the packet for transmission.
     */
    encode(data) {
        if (this.pendingTransmissions !== undefined) {
            this.pendingTransmissions.push(data);
        }
        else if (this.shouldPauseTransmission(data, this.commandQueue.length)) {
            this.console.log('pausing transmissions');
            this.pendingTransmissions = [data];
        }
        else {
            this.logPacket(this.id, 'send    ', data);
            this.targetEncoder.encode(data);
        }
    }
    /**
     * Implementation of the IPacketCodec.decode() method.  This implementation logs the incoming packet
     * to GcConsole.debug().  The derived implementation should override this method to implement the
     * necessary decoding of incoming packet, and it should call this base method first to perform the
     * logging function, before decoding the incoming and passing it along to the target decoder/model.
     *
     * @param value the packet received for decoding.
     */
    decode(data) {
        this.logPacket(this.id, 'receive ', data);
        if (this.pendingTransmissions !== undefined) {
            let pending = this.pendingTransmissions;
            const commandQueueCount = this.commandQueue.length;
            this.pendingTransmissions = undefined;
            while (!this.shouldPauseTransmission(pending[0], commandQueueCount - pending.length)) {
                const pendingData = pending.shift();
                pendingData && this.targetEncoder.encode(pendingData); // get ts error about undefined if using pending.shift() inline directly.
                if (pending.length <= 0) {
                    this.console.log('resuming transmissions');
                    pending = undefined;
                    break;
                }
            }
            this.pendingTransmissions = pending;
        }
        return true;
    }
    /**
     * Helper method to add a command to the command/response queue.  This method returns a promise that can be used
     * to process the response received by this method.  Only messages that require response handling need be
     * added to the command/response queue.  Messages that are sent that do not require handling may be omitted.
     *
     * @param command the specific command sent that requires a response.
     * @param sequence the sequence number of the packet that requires a response.
     * @returns promise of command's response
     */
    addCommand(command, sequenceNumber) {
        return this.commandQueue.addCommand(command, sequenceNumber);
    }
    /**
     * Helper method to process responses in command/response queue.  This method will find the appropriate
     * command in the command/response queue and reject any pending commands that did not receive a response, based
     * on the optional sequence numbers provided.
     *
     * @param response the raw response message received.
     * @param toCommand the specific command that this response is for.
     * @param sequenceNumber the sequence number of the packet received, if there is one.
     */
    addResponse(response, toCommand, sequenceNumber) {
        return this.commandQueue.addResponse(response, toCommand, sequenceNumber, false);
    }
    /**
     * Helper method to process error responses in command/response queue.  This method will find the appropriate
     * command in the command/response queue and reject it.  Any pending commands that did not receive a response,
     * based on the optional sequence numbers provided, will also be rejected.
     *
     * @param response the error message for the command.
     * @param toCommand the specific command that this error is for.
     * @param sequenceNumber the sequence number of the packet received, if there is one.
     */
    addErrorResponse(response, toCommand, sequenceNumber) {
        return this.commandQueue.addResponse(response, toCommand, sequenceNumber, true);
    }
    /**
     * Method to determine if the target is still connected.  The gc-transport-usb calls this api to
     * determine if there has been a loss of connection when it has not received any data in a while.  This method returns
     * a promise that either resolves if there are no commands in the queue expecting a response; otherwise, if returns fails, indicating that
     * there are commands that have not been responded to.  Derived classes should call the base class, and if it succeeds, they should
     * attempt to ping the target to ensure that the connection is indeed valid.  Just because there are no outstanding messages
     * does not imply the connection is good.
     *
     * @returns promise that resolves if still connected, or fails if the connection is lost with an error message.
     */
    ping() {
        if (!this.commandQueue.isEmpty()) {
            return Promise.reject('No response from ' + this.id + ' controller');
        }
        return Promise.resolve();
    }
    /**
     * Abstract method to determine if the transmission of packets should be paused or not.
     * This method is optional, and if implemented can return true to temporarily pause transmission of packets.
     * Each packet sent by the base classes encode() method will be test to see if transmission should be paused.
     * Once paused, the decode() method will test if the pending packet(s) should remain paused, or if transmission
     * can resume.  In other words, each packet sent will be tested repeatedly until this method returns false, at which point the
     * packet is transmitted to the target.
     *
     * @params packet the packet to test if it should be paused/delayed before sending to the target.
     * @params estimated outstanding commands based on command queue length minus pending count.
     * @returns {boolean}
     */
    shouldPauseTransmission(packet, outstandingCommands) {
        if (this.maxOutstandingCommands > 0 && outstandingCommands > this.maxOutstandingCommands) {
            return true;
        }
        return false;
    }
    static registerFirmwareCheck(impl, name) {
        AbstractMessageBasedDecoder.firmwareChecks[name] = impl;
    }
    checkFirmware(info, behaviorControl) {
        const promises = [];
        for (const x in AbstractMessageBasedDecoder.firmwareChecks) {
            promises.push(AbstractMessageBasedDecoder.firmwareChecks[x](info, behaviorControl));
        }
        return Promise.all(promises);
    }
    // eslint-disable-next-line @typescript-eslint/no-explicit-any
    static register_crc_user(impl, interfaceName) {
        // impl (required) - provides customized logic to embed crc bytes in data, and verify crc bytes and extract data
        // impl is an object  {
        //  embed_crc_data: function(crc, arg) {
        //      return {payload: crc_embedded_payload, num_read_bytes: num_byes_to_read_include_crc}
        //  }
        //  , verify_crc_data: function(crc, arg) {
        //      return {valid: true, payload: payload_without_crc};
        //  }
        // }
        // interface_name (required) - specific interfaces that needs the given crc implementation, e.g. 'i2c'
        AbstractMessageBasedDecoder.crcUsers[interfaceName] = impl;
    }
    static getCrcUser(interfaceName) {
        return AbstractMessageBasedDecoder.crcUsers[interfaceName];
    }
}
AbstractMessageBasedDecoder.firmwareChecks = {};
// eslint-disable-next-line @typescript-eslint/no-explicit-any
AbstractMessageBasedDecoder.crcUsers = {}; // TODO (next PR cycle define crcUser type)

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
const abortEventType = new EventType('abort');
var TRANSPORT_STATE;
(function (TRANSPORT_STATE) {
    TRANSPORT_STATE["DISCONNECTED"] = "disconnected";
    TRANSPORT_STATE["CONNECTED"] = "connected";
    TRANSPORT_STATE["CONNECTING"] = "connecting";
    TRANSPORT_STATE["DISCONNECTING"] = "disconnecting";
})(TRANSPORT_STATE || (TRANSPORT_STATE = {}));
/**
 * Connected state change event type.
 */
const connectedStateChangedEventType = new EventType('ConnectedStateChanged');

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
 *
*/
/**
 * Base class for all transports, and the connection manager, to manage connected, connecting, disconnected, and disconnecting states.
 */
class AbstractTransport extends AbstractConnectionLogger {
    constructor() {
        super(...arguments);
        this.disconnectPromise = Promise.resolve();
        this._state = TRANSPORT_STATE.DISCONNECTED;
        this._connectionDescription = '';
    }
    get isXdsTransport() {
        return false;
    }
    /**
     * current connection state of the transport.
     */
    get state() {
        return this._state;
    }
    get isConnected() {
        return this.state === TRANSPORT_STATE.CONNECTED;
    }
    /**
     * True if the transport is in the process of connecting to the target.
     */
    get isConnecting() {
        return this.state === TRANSPORT_STATE.CONNECTING;
    }
    get canConnect() {
        return this.isDisconnected || this.isDisconnecting;
    }
    get isDisconnected() {
        return this.state === TRANSPORT_STATE.DISCONNECTED;
    }
    /**
     * True if the transport is in the process of disconnecting from the target.
     */
    get isDisconnecting() {
        return this.state === TRANSPORT_STATE.DISCONNECTING;
    }
    get canDisconnect() {
        return this.isConnected || this.isConnecting;
    }
    get isPartiallyConnected() {
        return this.isConnected && codecRegistry.isPartiallyConnected(this.id);
    }
    assertStillConnecting() {
        if (this.isDisconnecting || this.isDisconnected) {
            throw Error('Connecting to target was aborted by the user.');
        }
    }
    setState(newState, didPartiallyConnectedStateChange = false) {
        if (this._state !== newState || didPartiallyConnectedStateChange) {
            if (this.canDisconnect && newState === TRANSPORT_STATE.CONNECTED) {
                this._state = newState; // state needs to be updated before calling isPartiallyConnected
                this.addProgressMessage(`Hardware ${this.isPartiallyConnected ? 'partially ' : ''}connected.`);
            }
            else if (this.isDisconnecting && newState === TRANSPORT_STATE.DISCONNECTED) {
                this.addProgressMessage('Hardware not connected.');
            }
            this._state = newState;
            this.fireEvent(connectedStateChangedEventType, { newState: this.state, transport: this });
            this.console.debug(`${capitalize(this.toString())} state changed to ${newState}.`);
        }
    }
    disconnect() {
        if (this.canDisconnect) {
            this.setState(TRANSPORT_STATE.DISCONNECTING);
            // eslint-disable-next-line no-async-promise-executor
            this.disconnectPromise = new Promise(async (resolve, reject) => {
                try {
                    await this.doAbort();
                    await this.doDisconnect();
                    if (this.state === TRANSPORT_STATE.DISCONNECTING) {
                        this.setState(TRANSPORT_STATE.DISCONNECTED);
                    }
                    resolve();
                }
                catch (e) {
                    reject(e);
                }
            });
        }
        return this.disconnectPromise;
    }
    connect(failedDevicesList = []) {
        if (this.canConnect) {
            // eslint-disable-next-line no-async-promise-executor
            this.connectPromise = this.connectPromise || new Promise(async (resolve, reject) => {
                try {
                    if (this.isDisconnecting) {
                        this.console.debug('Waiting for disconnect to complete before connecting.');
                    }
                    await this.disconnectPromise;
                    // clear logger every time we connect, but not on disconnect to preserve last error/warning message.
                    this.clearProgressMessage();
                    this.setConnectionDescription();
                    this.setState(TRANSPORT_STATE.CONNECTING);
                    await this.doConnect(failedDevicesList);
                    if (this.isConnecting) {
                        this.setState(TRANSPORT_STATE.CONNECTED);
                    }
                    resolve();
                }
                catch (e) {
                    if (this.isConnecting) {
                        let errMsg = e.message || e.toString();
                        if (errMsg.indexOf('failed to connect') < 0) {
                            errMsg = 'Failed to connect: ' + errMsg;
                        }
                        this.addErrorMessage(errMsg);
                        this.disconnect();
                    }
                    reject(e);
                }
                finally {
                    this.connectPromise = undefined;
                }
            });
        }
        return this.connectPromise || Promise.resolve();
    }
    async doConnect(failedDevicesList = []) {
        this.addProgressMessage('Connecting to target ...');
        await codecRegistry.connect(this.id, this, failedDevicesList);
    }
    doDisconnect() {
        return codecRegistry.disconnect(this.id, this);
    }
    async doAbort() {
        if (this.connectPromise) {
            this.console.debug('Aborting connection.');
            this.fireEvent(abortEventType, {});
            try {
                await (this.connectPromise || Promise.resolve());
            }
            catch {
                // not looking for errors here, just trying to serialize operations.
            }
        }
    }
    get connectionDescription() {
        return this._connectionDescription;
    }
    setConnectionDescription(description = '') {
        if (this._connectionDescription !== description) {
            this._connectionDescription = description;
            if (description) {
                this.addProgressMessage(`Connecting to ${description} ...`);
            }
        }
    }
    get optional() {
        return this.params.optional;
    }
    get deviceId() {
        return this.params.deviceId;
    }
    toString() {
        return `transport id="${this.id}"`;
    }
}

/**
 *  Copyright (c) 2021, Texas Instruments Incorporated
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

export { AbstractCodec, AbstractConnectionLogger, AbstractDataCodec, AbstractDataCodecWithFrameDecoder, AbstractDataDecoder, AbstractDataEncoder, AbstractDecoder, AbstractEncoder, AbstractFrameDecoder, AbstractMessageBasedDecoder, AbstractTransport, CompositeDataType, CompositeDecoderType, CompositeEncoderType, DecoderType, EncoderType, NoopDataDecoderType, NoopDataEncoderType, NoopDecoderType, NoopEncoderType, PrimitiveDataType, TRANSPORT_STATE, abortEventType, binaryDataType, binaryOrBufferDataType, bufferDataType, bufferOrStringDataType, capitalize, codecRegistry, connectedStateChangedEventType, connectionLogEventType, nullDataCodec, stringDataType };
//# sourceMappingURL=TargetConfiguration.js.map
