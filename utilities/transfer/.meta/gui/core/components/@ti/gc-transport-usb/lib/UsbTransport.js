import { connectionManager } from '../../gc-target-connection-manager/lib/ConnectionManager';
import { usbHidPortType, dataEventType, usbSerialPortType, usbWebSerialPortType, usbServiceType, UsbWebSerialPort, deviceDetachedEventType, deviceAttachedEventType } from '../../gc-service-usb/lib/ServiceUsb';
export { usbHidPortType, usbSerialPortType, usbWebSerialPortType } from '../../gc-service-usb/lib/ServiceUsb';
import { AbstractTransport, bufferOrStringDataType, bufferDataType, AbstractConnectionLogger, TRANSPORT_STATE, codecRegistry, capitalize, connectedStateChangedEventType, connectionLogEventType } from '../../gc-target-configuration/lib/TargetConfiguration';
import { ServicesRegistry } from '../../gc-core-services/lib/ServicesRegistry';
import { EventType } from '../../gc-core-assets/lib/Events';
import { GcLocalStorage } from '../../gc-core-assets/lib/GcLocalStorage';
import { GcUtils } from '../../gc-core-assets/lib/GcUtils';
import { XdsTransport } from '../../gc-transport-xds/lib/XdsTransport';
import { GcPromise } from '../../gc-core-assets/lib/GcPromise';
import { GcConsole } from '../../gc-core-assets/lib/GcConsole';

/**
 *  Copyright (c) 2021, 2024 Texas Instruments Incorporated
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
const HID_RESERVED = 2; // packet bytes reserved by HID
const MAX_PACKET_SIZE = 64 - HID_RESERVED; // size, in bytes, of a USB packet
class AbstractUsbTransport extends AbstractTransport {
    constructor() {
        super(...arguments);
        this.encoderInputType = bufferOrStringDataType;
        this.encoderOutputType = bufferDataType;
        this.serialPacketDataHandler = (details) => {
            if (this.codec) {
                this.decodeDataPacket(this.codec, details.data);
            }
        };
        this.hidPacketDataHandler = (details) => {
            if (this.codec) {
                const rawData = details.data;
                const nRead = rawData[1] || 0;
                if (rawData[0] !== 0x3F) {
                    throw Error(`Invalid HID packet header.  Expected the first byte to be 0x3F instead of ${rawData[0]}`);
                }
                else if (nRead > MAX_PACKET_SIZE || nRead < 0) {
                    throw Error('Invalid HID packet.  Too much data');
                }
                else if (nRead > 0) { // ignore zero size packets.
                    this.decodeDataPacket(this.codec, rawData.slice(HID_RESERVED, nRead + HID_RESERVED));
                }
            }
        };
    }
    get id() {
        return this.params.id || 'usb';
    }
    decodeDataPacket(decoder, rawData) {
        let result;
        try {
            result = decoder.decode(rawData);
        }
        catch (e) {
            result = e;
        }
        if (result instanceof Error) {
            this.addErrorMessage(result.message);
            this.disconnect();
        }
    }
    encode(data) {
        if (this.usbPort) {
            if (this.usbPort.type === usbHidPortType) {
                // Add header to HID packets.
                const header = [0x3f, data.length];
                if (typeof data === 'string') {
                    this.usbPort.write(String.fromCharCode(...header) + data);
                }
                else {
                    this.usbPort.write([...header, ...data]);
                }
            }
            else {
                // No header for Serial packets
                this.usbPort.write(data);
            }
        }
    }
    addChildDecoder(decoder) {
        this.codec = decoder;
    }
    deconfigure() {
        this.codec = undefined;
    }
    async doOpenUsbPort(usbPort, options) {
        this.rxDataHandler = usbPort.type === usbHidPortType ? this.hidPacketDataHandler : this.serialPacketDataHandler;
        this.baudRate = options.baudRate;
        usbPort.addEventListener(dataEventType, this.rxDataHandler);
        await usbPort.open({ baudRate: options.baudRate, highWaterMark: options.bufferSize, rtscts: options.flowControl });
        this.usbPort = usbPort;
    }
    async onDisconnect(logger) {
        if (this.usbPort) {
            if (this.rxDataHandler) {
                this.usbPort.removeEventListener(dataEventType, this.rxDataHandler);
                this.rxDataHandler = undefined;
            }
            await this.usbPort.close();
            this.usbPort = undefined;
        }
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
class ConnectionLogger extends AbstractConnectionLogger {
    constructor() {
        super(...arguments);
        this.state = TRANSPORT_STATE.CONNECTED;
        this.id = 'progress';
        this.console = new GcConsole('gc-transport-usb');
        this.isXdsTransport = false;
    }
    async connect(failedDevicesList) {
    }
    async disconnect() {
    }
    get isConnected() {
        return true;
    }
    get canConnect() {
        return false;
    }
    get isDisconnected() {
        return false;
    }
    get canDisconnect() {
        return true;
    }
    get isPartiallyConnected() {
        return false;
    }
    assertStillConnecting() {
        return true;
    }
}
class TargetConfigurationBuilder {
    constructor(targetEncoder) {
        this.targetEncoder = targetEncoder;
        this.activeCodecList = [];
        this.logger = new ConnectionLogger();
    }
    async dispose() {
        for (let i = this.activeCodecList.length; i-- > 0;) {
            const codec = this.activeCodecList[i];
            if (codec.onDisconnect) {
                await codec.onDisconnect(this.logger);
            }
        }
        if (this.targetEncoder.onDisconnect) {
            await this.targetEncoder.onDisconnect(this.logger);
        }
        this.activeCodecList.reverse().forEach(codec => codec.deconfigure && codec.deconfigure());
        this.targetEncoder.deconfigure && this.targetEncoder.deconfigure();
    }
    async appendCodec(decoderFactory, params, parent) {
        const child = this.clone(decoderFactory, params);
        await this.append(child, parent);
        return child;
    }
    clone(decoderFactory, params) {
        params = { ...params }; // copy parameters so I can modify the id without change the caller's object;
        if (params.id) {
            try {
                const codecToClone = codecRegistry.getInstance(params.id);
                params = { ...codecToClone.params, ...params }; // use params as overrides for the real codecs parameters.
            }
            catch (e) {
                // nothing to do if no registered codec found.
            }
        }
        else {
            params.id = decoderFactory.name;
        }
        params.id += '_$_transient'; // make sure we don't register this in place of the real codec.
        const result = new decoderFactory(params);
        codecRegistry.unregister(result); // don't need to keep this registered, it's only temporary.
        return result;
    }
    async append(child, parent) {
        if (!parent) {
            parent = this.targetEncoder;
        }
        else if (!this.activeCodecList.includes(parent)) {
            throw Error(`Parent encoder ${parent.id} was not found.`);
        }
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
        if (child.configure) {
            child.configure();
        }
        if (child.onConnect) {
            await child.onConnect(this.logger);
        }
        this.activeCodecList.push(child);
    }
}

/**
 *  Copyright (c) 2021, 2024 Texas Instruments Incorporated
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
const console = new GcConsole('gc-transport-usb');
class UsbPortIdentityTransport extends AbstractUsbTransport {
    constructor(selectedUsbPort, options) {
        super();
        this.selectedUsbPort = selectedUsbPort;
        this.options = options;
        this.params = {};
        this.console = new GcConsole('gc-transport-usb');
    }
    doConnect(failedDevicesList = []) {
        const options = typeof this.options === 'number' ? { baudRate: this.options } : this.options;
        return this.doOpenUsbPort(this.selectedUsbPort, options);
    }
    dispose() {
    }
    toString() {
        return `transport port="${this.selectedUsbPort.comName}"`;
    }
}
class AutoDetectPortIdentityHelper {
    constructor(usbPort, elapsedTimeSinceLastPortIdentityAttempt) {
        this.usbPort = usbPort;
        this.elapsedTimeSinceLastPortIdentityAttempt = elapsedTimeSinceLastPortIdentityAttempt;
        this.isUsb = usbPort.type === usbSerialPortType;
        this.isHid = usbPort.type === usbHidPortType;
    }
    async serialPortConnect(options) {
        if (!this.usbTransport) {
            const portOptions = typeof options === 'number' ? { baudRate: options } : options ?? {};
            portOptions.baudRate = portOptions.baudRate || 9600;
            this.usbTransport = new UsbPortIdentityTransport(this.usbPort, portOptions);
        }
        await this.usbTransport.connect();
        this.configBuilder = new TargetConfigurationBuilder(this.usbTransport);
        return this.usbTransport;
    }
    async serialPortDisconnect() {
        if (this.configBuilder) {
            await this.configBuilder.dispose();
            this.configBuilder = undefined;
        }
    }
    appendCodec(decoderFactory, params, parent) {
        if (this.configBuilder) {
            return this.configBuilder.appendCodec(decoderFactory, params, parent);
        }
        throw 'Invocation Error: Cannot call appendCodec() before calling open()';
    }
}
/**
 * Helper class for registering auto detect port identity handlers, and accessing port identity information.
 *
 * Applications can use this to perform device detection or port identification on usb transports by registering a callback.
 * This callback is called once for each unique USB serial port found on the users machine, and the result is cached.
 * Note that this may occur any time
 * the users serial ports are listed, and there are new serial ports found.  For multiple serial ports, this method will be
 * called multiple times, and in parallel which means that more that one com port may be open at one time.
 * When this callback is called, the serial port is not opened, no codec has been created, and the app has not tried to connect
 * to the target yet.
 *
 * The callback should return one of the following:
 * <ul>
 * <li>string - used to identify the serial port, perhaps by device name.</li>
 * <li>object - as object that has a toString() method that returns a string to identify the serial port to the user.</li>
 * <li>undefined - null or undefined to indicate that the serial port could not be recognized.</li>
 * <li>promise - a promise that resolves to one of the above.  In this case, an exception is just a failed promise.</li>
 * </ul>
 *
 * @example
 * ```typescript
 * import { AutoDetectPortIdentityRegistry, IUsbPort, IAutoDetectPortIdentityHelper } from '<path-to>/gc-transport-usb/lib/UsbTransport';
 * import { Usb2anyCodec } from '<path-to>/gc-codec-usb2any/lib/Usb2anyCodec';
 *
 * function async myPortIdentityHandler(port: IUsbPort, helperAPI: IAutoDetectPortIdentityHelper) {
 *     if (!helperAPI.isUsb || port.descriptor.vendorId === 769) {
 *         return 'myDeviceName';
 *     }
 * };
 * AutoDetectPortIdentityRegistry.registerPortIdentityHandler(myPortIdentityHandler);
 */
class AutoDetectPortIdentityRegistry {
    /**
     * Method to register a callback to perform application specific usb port identification.
     *
     * @param handler - the callback that will be called for each usb port, for the purposes of device or port identification.
     */
    static registerPortIdentityHandler(handler) {
        if (!this.portIdentityHandlers.includes(handler)) {
            this.portIdentityHandlers.push(handler);
        }
    }
    /**
     * Method to unregister a callback to perform application specific usb port identification.
     *
     * @param handler - the callback, previously registered, for unregistering.
     */
    static unRegisterPortIdentityHandler(handler) {
        const i = this.portIdentityHandlers.indexOf(handler);
        if (i >= 0) {
            this.portIdentityHandlers.splice(i, 1);
        }
    }
    static async doPortIdentity(port, portInfo) {
        let newPortIdentity;
        const elapsedTm = Date.now() - (portInfo.timeStamp || 0);
        console.log(`Starting port identification on ${port.comName}, ${portInfo.timeStamp ? `${portInfo.timeStamp / 1000} seconds since last try.` : 'for the first time.'}`);
        for (let i = 0; i < this.portIdentityHandlers.length; i++) {
            const handler = this.portIdentityHandlers[i];
            const helper = new AutoDetectPortIdentityHelper(port, elapsedTm);
            try {
                newPortIdentity = await Promise.resolve(handler(port, helper));
                if (newPortIdentity) {
                    portInfo.portIdentity = newPortIdentity;
                    break;
                }
            }
            catch (e) { // log error and continue, since we support multiple port identity handlers.
                console.error(`Exception caught in auto detect port identity handler: ${e.message || e.toString()}`);
            }
            finally {
                await helper.serialPortDisconnect();
            }
        }
        portInfo.timeStamp = Date.now(); // update timestamp to reflect the last attempt to detect identity of port.
        console.log(`Finished port identification on ${port.comName}, ${newPortIdentity ? `identified as ${newPortIdentity}` : 'no identity found'}.`);
    }
    /**
     * Helper method used by the UsbTransport to update port identities as part of its allocating serial ports.  It is not
     * necessary to call this method manually.  Normally, the UsbTransport will take care of this.
     *
     * @param ports - a list of serial ports to update the port identities for.
     */
    static updateAllPortIdentities(ports) {
        if (this.portIdentityHandlers.length > 0) {
            const promises = ports.map((port) => {
                const portInfo = this.getAutoDetectPortIdentityInfo(port);
                if (portInfo.promise === undefined && !port.isOpened) {
                    portInfo.promise = this.doPortIdentity(port, portInfo).finally(() => portInfo.promise = undefined);
                }
                return portInfo.promise;
            });
            return GcPromise.all(promises);
        }
        return Promise.resolve();
    }
    static getAutoDetectPortIdentityInfo(port) {
        let portInfo = this.portIdentityMap.get(port.comName);
        if (!portInfo) {
            portInfo = { portIdentity: '' };
            this.portIdentityMap.set(port.comName, portInfo);
        }
        return portInfo;
    }
    /**
     * Helper method to retrieve the port identity information returned by an auto detect port identity handler.
     *
     * @param port - The serial port from which to retrieve the port identity.
     */
    static getAutoDetectPortIdentity(port) {
        return this.getAutoDetectPortIdentityInfo(port).portIdentity;
    }
    /**
     * Helper method to retrieve the display name for a usb port.  The display name is comprised of the comName followed by
     * the port identity, if available, in brackets.
     *
     * @param port - The serial port from which to retrieve the display name.
     */
    static getDisplayName(port) {
        const portIdentity = this.getAutoDetectPortIdentity(port);
        const deviceName = portIdentity.toString();
        if (deviceName) { // test for empty or missing string.
            return `${port.comName} (${deviceName})`;
        }
        return port.comName;
    }
}
AutoDetectPortIdentityRegistry.portIdentityHandlers = [];
AutoDetectPortIdentityRegistry.portIdentityMap = new Map();

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
const MODULE_NAME = 'gc-transport-usb';
var StorageKeys;
(function (StorageKeys) {
    StorageKeys["baudRate"] = "baudRate";
    StorageKeys["comPort"] = "comPort";
})(StorageKeys || (StorageKeys = {}));
/**
 * An event called by UsbTransport during acquisition of serial ports during connect.  This event is intended
 * to provide the app an opportunity to filter the available ports for a particular transport.  This way only appropriate
 * usb ports are shown to the user for any particular transport.  Usually, this is used in conjunction with
 * @see {@link AutoDetectPortIdentityRegistry}
 * to identify each port, and then filter the ones that are known to know be supported.
 *
 * @example
 * ```typescript
 * import { AutoDetectPortIdentityRegistry, IUsbPort, filterPortsEventType, IFilterUsbPorts } from '<path-to>/gc-transport-usb/lib/UsbTransport';
 *
 * function async myPortFilter(details: IFilterUsbPorts) {
 *     details.ports = details.ports.filter( port => {
 *         id = AutoDetectPortIdentityRegistry.getAutoDetectPortIdentityInfo(port).toString();
 *         return id === 'TMP117' || id === 'TMP116';
 *     });
 *     details.recommendedPort = details.ports.reduce( (found: IUsbPort, port) => {
 *         return AutoDetectPortIdentityRegistry.getAutoDetectPortIdentityInfo(port) === 'TMP117' ? port : found);
 *     }, undefined);
 * };
 * usbTransport.addEventListener(filterPortsEventType, myPortFilter);
 * ```
 */
const filterPortsEventType = new EventType('filterUsbPorts');
const selectedPortEventType = new EventType('selectedUsbPort');
class UsbTransport extends AbstractUsbTransport {
    constructor(params) {
        super();
        this.params = params;
        this.availablePorts = [];
        this.webSerialOnDisconnect = () => {
            this.disconnect();
            // The web serialPort.connected state is false at this point, and so it cannot be re-opened.
            // There is a need to enforce acquirePort to go through navigator.serial.getPorts() to obtain a valid object.
            this.recentlyAcquiredPort = undefined;
        };
        this.console = new GcConsole(MODULE_NAME, this.id);
        if (params.web) {
            if (params.pm) {
                this.console.warning('Ignoring pm flag.  This is not supported in conjunction with the web parameter.');
            }
            if (params.hid) {
                this.console.warning('Ignoring hid flag.  This is not supported in conjunction with the web parameter.');
            }
        }
        else if (params.pm) {
            this.pmTransport = new XdsTransport(params, async () => {
                if (params.hid) {
                    throw Error(`${capitalize(this.toString())} cannot have both pm and hid properties set.`);
                }
                const acquiredPortSelection = await UsbTransport.acquirePort(this);
                if (!acquiredPortSelection) {
                    throw Error('No port found.');
                }
                return [acquiredPortSelection.port.comName, acquiredPortSelection.baudRate];
            });
        }
        connectionManager.registerTransport(this.pmTransport || this);
        codecRegistry.register(this.pmTransport || this);
        if (!UsbTransport.instances.includes(this)) {
            UsbTransport.instances.push(this);
        }
    }
    get selectedPort() {
        return this.usbPort || this.recentlyAcquiredPort;
    }
    get selectedBaudRate() {
        return this.baudRate;
    }
    get state() {
        if (this.pmTransport) {
            return this.pmTransport.state;
        }
        return super.state;
    }
    connect(failedDevicesList) {
        if (this.pmTransport) {
            return this.pmTransport.connect(failedDevicesList);
        }
        else {
            return super.connect(failedDevicesList);
        }
    }
    get useWebSerial() {
        return (this.params.web && !GcUtils.isNodeJS && navigator?.serial !== undefined) ?? false;
    }
    get disableDeviceDetection() {
        return this.params.disableDeviceDetection || this.useWebSerial;
    }
    async onConnect(logger) {
        if (!this.disableDeviceDetection) {
            UsbTransport.startDeviceDetection();
        }
        const acquiredPortSelection = await UsbTransport.acquirePort(this);
        this.recentlyAcquiredPort = acquiredPortSelection?.port;
        this.assertStillConnecting();
        if (!acquiredPortSelection) {
            throw Error('No port found.  Please plug your target device into your computer\'s USB port, and click the connect icon on the left.');
        }
        const selectedPort = acquiredPortSelection.port;
        const selectedBaudRate = acquiredPortSelection.baudRate;
        let description = selectedPort?.comName || '';
        if (selectedPort.type !== usbHidPortType && selectedBaudRate) {
            description += ':' + selectedBaudRate;
        }
        this.setConnectionDescription(description);
        if (selectedPort.type === usbWebSerialPortType) {
            selectedPort.serialPort.addEventListener('disconnect', this.webSerialOnDisconnect);
        }
        this.fireEvent(selectedPortEventType, {
            port: selectedPort,
            baudRate: selectedBaudRate,
            availablePorts: this.availablePorts,
            transport: this
        });
        await this.doOpenUsbPort(selectedPort, { baudRate: selectedBaudRate, bufferSize: this.params.bufferSize, flowControl: this.params.flowControl });
    }
    disconnect() {
        if (this.recentlyAcquiredPort?.type === usbWebSerialPortType) {
            this.recentlyAcquiredPort?.serialPort.removeEventListener('disconnect', this.webSerialOnDisconnect);
        }
        if (this.pmTransport) {
            return this.pmTransport.disconnect();
        }
        else {
            return super.disconnect();
        }
    }
    dispose() {
        const i = UsbTransport.instances.indexOf(this);
        if (i >= 0) {
            UsbTransport.instances.splice(i, 1);
            UsbTransport.stopDeviceDetection();
        }
        connectionManager.unregisterTransport(this.pmTransport || this);
        codecRegistry.unregister(this.pmTransport || this);
    }
    filterPorts(ports) {
        // filter ports based on hid and usb flags.  If usb and hid both are true, then filter by usb.
        if (this.params.usb || this.params.pm) {
            ports = ports.filter(port => port.type === usbSerialPortType);
        }
        else if (this.params.hid) {
            ports = ports.filter(port => port.type === usbHidPortType);
        } // else both usb, and hid are true, so no filtering required.
        const usbService = ServicesRegistry.getService(usbServiceType);
        ports = usbService.filterPortsByDescriptorInfo(ports, { vendorId: this.params.vendorId, productId: this.params.productId, interfaceNumber: this.params.interfaceNumber });
        if (this.params.filter !== undefined) {
            ports = this.params.filter(ports);
        }
        const details = { ports: ports, recommendedPort: undefined, recommendedBaudRate: undefined };
        this.fireEvent(filterPortsEventType, details);
        return details;
    }
    onDeviceDetachedEvent(ports) {
        if (!this.disableDeviceDetection && codecRegistry.isActive(this.id) && this.canDisconnect) {
            const inUsePort = this.usbPort;
            if (inUsePort && ports.reduce((notFound, port) => notFound && UsbTransport.comparePortsByComName(inUsePort, port) !== 0, true)) {
                this.disconnect();
            }
        }
    }
    get storageKeyPrefix() {
        return `${GcUtils.appName}_${this.params.id}_`;
    }
    get userSelectedPortName() {
        if (!this._userSelectedPortName) {
            this._userSelectedPortName = GcLocalStorage.getItem(this.storageKeyPrefix + StorageKeys.comPort) || undefined;
        }
        return this._userSelectedPortName;
    }
    set userSelectedPortName(comPort) {
        if (comPort) {
            GcLocalStorage.setItem(this.storageKeyPrefix + StorageKeys.comPort, comPort);
        }
        else {
            GcLocalStorage.removeItem(this.storageKeyPrefix + StorageKeys.comPort);
        }
        this._userSelectedPortName = comPort || undefined;
    }
    get userSelectedBaudRate() {
        if (!this._userSelectedBaudRate) {
            const baudRateName = GcLocalStorage.getItem(this.storageKeyPrefix + StorageKeys.baudRate);
            if (baudRateName) {
                this._userSelectedBaudRate = Number.parseInt(baudRateName);
            }
        }
        return this._userSelectedBaudRate;
    }
    set userSelectedBaudRate(baudRate) {
        if (baudRate) {
            GcLocalStorage.setItem(this.storageKeyPrefix + StorageKeys.baudRate, baudRate.toString());
        }
        else {
            GcLocalStorage.removeItem(this.storageKeyPrefix + StorageKeys.baudRate);
        }
        this._userSelectedBaudRate = baudRate || undefined;
    }
    computeScoreForPortAllocation(comName, recommendedPortName) {
        let result = codecRegistry.isOptional(this.id) ? 0 : 1;
        if (comName === this.userSelectedPortName) {
            result += 8;
        }
        if (comName === this.preferredPortName) {
            result += 4;
        }
        if (comName === recommendedPortName) {
            result += 2;
        }
        return result;
    }
    static async computeScoresForPortAllocation(ports, transports) {
        const scores = [];
        const usbService = ServicesRegistry.getService(usbServiceType);
        for (let i = 0; i < transports.length; i++) {
            const transport = transports[i];
            // eslint-disable-next-line prefer-const
            let { ports: filteredPorts, recommendedPort: recommendedPort, recommendedBaudRate: recommendedBaudRate } = transport.filterPorts(ports);
            if (!recommendedPort) {
                const defaultPort = await usbService.getDefaultPort(filteredPorts, transport.params.deviceName);
                if (defaultPort) {
                    recommendedPort = defaultPort.port;
                    recommendedBaudRate = transport.params.defaultBaudRate || defaultPort.baudRate;
                }
            }
            const recommendedComName = recommendedPort ? recommendedPort.comName : undefined;
            if (transport.usbPort) { // transport is already using this port.
                scores.push({ port: transport.usbPort, transport, score: 100, baudRate: transport.baudRate || transport.params.defaultBaudRate || 9600 });
            }
            else {
                filteredPorts.forEach((port) => {
                    if (!port.isOpened) { // don't allocate open ports used by other transports, but leave in list of available ports.
                        scores.push({
                            port: port,
                            transport: transport,
                            score: transport.computeScoreForPortAllocation(port.comName, recommendedComName),
                            baudRate: transport.userSelectedBaudRate || recommendedBaudRate || transport.params.defaultBaudRate || 9600
                        });
                    }
                });
            }
            transport.availablePorts = [...filteredPorts];
        }
        return scores;
    }
    static async allocatePorts(ports, transports) {
        let scores = await this.computeScoresForPortAllocation(ports, transports);
        scores = scores.sort((a, b) => b.score - a.score);
        const picks = [];
        while (scores.length > 0) {
            const pick = scores[0];
            scores = scores.filter((score) => score.port !== pick.port && score.transport !== pick.transport);
            picks.push(pick);
        }
        return picks;
    }
    /**
     * Helper method to compare usb ports two usb ports by their name, for the purposes of finding or sorting usb ports.
     *
     * @param portA usb port to compare with port B
     * @param portB usb port to compare with port A
     * @returns -1 if port A is less than port B for the purposes of sorting, +1 if port A is greater than port B, and zero if they are equal.
     *
     */
    static comparePortsByComName(portA, portB) {
        if (!portA) {
            return portB ? -1 : 0; // handle the case where both ports are undefined, since this is public method.
        }
        else if (!portB) {
            return 1;
        }
        else if (portA.type !== portB.type) {
            return portA.type === usbHidPortType ? -1 : 1;
        }
        else {
            return portA.comName.localeCompare(portB.comName);
        }
    }
    static listPorts() {
        if (!this.listPortsPromise) {
            const usbService = ServicesRegistry.getService(usbServiceType);
            const activeTransports = this.activeTransports;
            const usbOnly = activeTransports.reduce((usb, transport) => usb && (transport.params.usb || false), true);
            const hidOnly = activeTransports.reduce((hid, transport) => hid && (transport.params.hid || false), true);
            const filter = usbOnly ? usbSerialPortType : hidOnly ? usbHidPortType : undefined;
            // Usb-hid module only supports filtering on one vendor id.  If not provided then default 8263 is used, so
            // we need to make sure all transports are ok with this; otherwise, report an error.
            const hidTransports = activeTransports.filter(transport => transport.params.hid);
            let vendorId;
            if (hidTransports.length > 0) {
                const vendorIds = hidTransports.map(transport => transport.params.vendorId || 8263);
                vendorId = vendorIds[0];
                const same = vendorIds.reduce((same, vid) => same && vid === vendorId, true);
                if (!same) {
                    GcConsole.error(MODULE_NAME, 'Multiple HID transports are requesting different vendor id\'s which is not currently supported.');
                    // don't stop, keep going.  Worst case is that user will not see all the hid ports they need.
                }
            }
            this.listPortsPromise = (async () => {
                try {
                    let ports;
                    if (filter) {
                        ports = await usbService.listPorts(filter, vendorId);
                    }
                    else {
                        const usb = usbService.listPorts(usbSerialPortType);
                        const hid = usbService.listPorts(usbHidPortType, vendorId);
                        ports = [...await usb, ...await hid];
                    }
                    UsbTransport.instances.forEach(transport => {
                        if (transport.recentlyAcquiredPort && !ports.includes(transport.recentlyAcquiredPort)) {
                            transport.recentlyAcquiredPort = undefined;
                        }
                    });
                    return ports;
                }
                finally {
                    this.listPortsPromise = undefined;
                }
            })();
        }
        return this.listPortsPromise;
    }
    static async acquirePort(forTransport) {
        if (forTransport.useWebSerial) {
            let port = forTransport.recentlyAcquiredPort;
            port = port && port.type === usbWebSerialPortType ? port : undefined;
            // special case, only one active transport and one paired web serial port.  Use this until user changes.
            if (!port && this.activeTransports.length === 1) {
                const ports = await navigator.serial.getPorts();
                if (ports.length === 1) {
                    port = new UsbWebSerialPort(ports[0]);
                }
            }
            if (!port) {
                return undefined;
            }
            return {
                port,
                transport: forTransport,
                score: 1,
                baudRate: forTransport.userSelectedBaudRate || forTransport.params.defaultBaudRate || 9600
            };
        }
        if (!this.acquirePortsForList.includes(forTransport)) {
            this.acquirePortsForList.push(forTransport);
        }
        if (!this.acquirePortPromise) {
            this.acquirePortPromise = (async () => {
                try {
                    const ports = await this.listPorts();
                    // do port identification
                    await AutoDetectPortIdentityRegistry.updateAllPortIdentities(ports);
                    return await this.allocatePorts(ports, this.acquirePortsForList);
                }
                finally {
                    this.previouslyAcquiredPorts = this.acquirePortPromise;
                    this.acquirePortPromise = undefined;
                    this.acquirePortsForList = [];
                }
            })();
        }
        const allocatedPorts = await this.acquirePortPromise;
        return allocatedPorts.reduce((port, item) => item.transport === forTransport ? item : port, undefined);
    }
    async doConnect(failedDevicesList = []) {
        await super.doConnect(failedDevicesList);
        // if we successfully connect (including codes and models), then remember this port as the preferred port for next time.
        if (this.usbPort) {
            this.preferredPortName = this.usbPort.comName;
        }
    }
    addEventListener(type, listener) {
        super.addEventListener(type, listener);
        if (this.pmTransport && (type === connectedStateChangedEventType || type === connectionLogEventType)) {
            this.pmTransport.addEventListener(type, listener);
        }
    }
    removeEventListener(type, listener) {
        super.removeEventListener(type, listener);
        if (this.pmTransport && (type === connectedStateChangedEventType || type === connectionLogEventType)) {
            this.pmTransport.removeEventListener(type, listener);
        }
    }
    static async onDeviceAttachedEvent() {
        if (UsbTransport.pauseConnectingOnNewPortsFound) {
            // skip
        }
        else if (connectionManager.isConnected) {
            // connect any optional transports that are not already connected, but only if they acquired a different port.
            if (connectionManager.isPartiallyConnected) {
                const acquiredPorts = await UsbTransport.acquireAllPorts();
                const transportsToConnect = acquiredPorts.reduce((transports, portSelection) => {
                    const transport = portSelection.transport;
                    if (!transport.disableDeviceDetection && codecRegistry.isActive(transport.id) && (transport.isDisconnected || transport.isDisconnecting)) {
                        if (portSelection.port && portSelection.port !== transport.recentlyAcquiredPort) {
                            transports.push(transport);
                        }
                    }
                    return transports;
                }, []);
                if (transportsToConnect.length > 0) {
                    try {
                        UsbTransport.acquirePortPromise = UsbTransport.previouslyAcquiredPorts; // don't list ports, with port identity twice in a row.
                        await GcPromise.all(transportsToConnect.map(transport => transport.connect()));
                    }
                    finally {
                        UsbTransport.acquirePortPromise = undefined;
                    }
                }
            }
        }
        else if (connectionManager.allowAutoConnectOnDeviceDetection && connectionManager.isDisconnected) { // do full connect only if enough ports were allocated.
            const acquiredPorts = await UsbTransport.acquireAllPorts();
            const requiredPorts = acquiredPorts.filter(portSelection => !codecRegistry.isOptional(portSelection.transport.id));
            const missingRequiredPorts = requiredPorts.filter(portSelection => portSelection.port === undefined || portSelection.transport.disableDeviceDetection);
            const changedPorts = requiredPorts.filter(portSelection => portSelection.port !== portSelection.transport.recentlyAcquiredPort);
            if (changedPorts.length > 0 && missingRequiredPorts.length === 0) {
                try {
                    UsbTransport.acquirePortPromise = UsbTransport.previouslyAcquiredPorts; // don't list ports, with port identity twice in a row.
                    await connectionManager.connect();
                }
                finally {
                    UsbTransport.acquirePortPromise = undefined;
                }
            }
        }
    }
    static async onDeviceDetachedEvent() {
        const ports = await UsbTransport.listPorts();
        UsbTransport.instances.forEach(transport => transport.onDeviceDetachedEvent(ports));
    }
    static startDeviceDetection() {
        if (!this.autoDetectDeviceEnabled) {
            const usbService = ServicesRegistry.getService(usbServiceType);
            usbService.addEventListener(deviceDetachedEventType, this.onDeviceDetachedEvent);
            usbService.addEventListener(deviceAttachedEventType, this.onDeviceAttachedEvent);
            this.autoDetectDeviceEnabled = true;
        }
    }
    static stopDeviceDetection() {
        if (this.autoDetectDeviceEnabled && this.instances.reduce((off, transport) => transport.disableDeviceDetection ? off : false, true)) {
            const usbService = ServicesRegistry.getService(usbServiceType);
            usbService.removeEventListener(deviceDetachedEventType, this.onDeviceDetachedEvent);
            usbService.removeEventListener(deviceAttachedEventType, this.onDeviceAttachedEvent);
            this.autoDetectDeviceEnabled = false;
        }
    }
    static get activeTransports() {
        return this.instances.filter(transport => {
            try {
                return codecRegistry.isActive(transport.id);
            }
            catch (e) {
                return false;
            }
        });
    }
    static acquireAllPorts() {
        this.previouslyAcquiredPorts = undefined;
        const allTransports = this.activeTransports;
        const promises = [];
        for (let i = 0; i < allTransports.length; i++) {
            const transport = allTransports[i];
            promises.push((async () => {
                const result = await this.acquirePort(allTransports[i]);
                return {
                    availablePorts: transport.availablePorts,
                    port: result && result.port,
                    baudRate: (result && result.baudRate) ?? transport.params.defaultBaudRate,
                    transport: transport
                };
            })());
        }
        return GcPromise.all(promises);
    }
    static async doReconnect(transport, autoConnect) {
        if (transport.canDisconnect) {
            await transport.disconnect();
            await transport.connect();
        }
        else if (autoConnect && transport.canConnect) {
            await transport.connect();
        }
    }
    static async applyUserPortSelections(userPortSelections, autoConnect) {
        userPortSelections.forEach(userSelection => {
            userSelection.transport.userSelectedPortName = userSelection.port?.comName;
            userSelection.transport.userSelectedBaudRate = userSelection.baudRate;
            userSelection.transport.recentlyAcquiredPort = userSelection.port;
        });
        const allOptional = userPortSelections.reduce((optional, selection) => optional && (selection.transport.params.optional || false), true);
        try {
            if (connectionManager.canConnect && autoConnect) {
                await connectionManager.connect();
            }
            else if (!allOptional) {
                await this.doReconnect(connectionManager, autoConnect);
            }
            else {
                await Promise.all(userPortSelections.map(userSelection => this.doReconnect(userSelection.transport, autoConnect)));
            }
        }
        catch (e) {
            // prevent unhandled exceptions messages in console log.
        }
    }
}
UsbTransport.instances = [];
UsbTransport.acquirePortsForList = [];
UsbTransport.autoDetectDeviceEnabled = false;

export { AutoDetectPortIdentityRegistry, UsbTransport, filterPortsEventType, selectedPortEventType };
//# sourceMappingURL=UsbTransport.js.map
