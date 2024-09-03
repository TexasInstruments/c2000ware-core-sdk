import { GcPromise } from '../../../gc-core-assets/lib/GcPromise';
import { capitalize } from './AbstractConnectionLogger';
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
export const codecRegistry = new CodecRegistry();
//# sourceMappingURL=CodecRegistry.js.map