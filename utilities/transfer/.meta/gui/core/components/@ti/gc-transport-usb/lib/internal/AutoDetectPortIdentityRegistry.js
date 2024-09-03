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
import { TargetConfigurationBuilder } from './TargetConfigurationBuilder';
import { usbSerialPortType, usbHidPortType } from '../../../gc-service-usb/lib/ServiceUsb';
import { AbstractUsbTransport } from './AbstractUsbTransport';
import { GcPromise } from '../../../gc-core-assets/lib/GcPromise';
import { GcConsole } from '../../../gc-core-assets/lib/GcConsole';
const console = new GcConsole('gc-transport-usb');
class UsbPortIdentityTransport extends AbstractUsbTransport {
    constructor(selectedUsbPort, selectedBaudRate) {
        super();
        this.selectedUsbPort = selectedUsbPort;
        this.selectedBaudRate = selectedBaudRate;
        this.params = {};
        this.console = new GcConsole('gc-transport-usb');
    }
    doConnect(failedDevicesList = []) {
        return this.doOpenUsbPort(this.selectedUsbPort, this.selectedBaudRate);
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
    async serialPortConnect(baudRate) {
        if (!this.usbTransport) {
            this.usbTransport = new UsbPortIdentityTransport(this.usbPort, baudRate || 9600);
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
export class AutoDetectPortIdentityRegistry {
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
//# sourceMappingURL=AutoDetectPortIdentityRegistry.js.map