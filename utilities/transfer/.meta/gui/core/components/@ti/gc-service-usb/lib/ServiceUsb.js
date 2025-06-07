import { GcConsole } from '../../gc-core-assets/lib/GcConsole';
import { EventType, Events } from '../../gc-core-assets/lib/Events';
import { backplaneServiceType } from '../../gc-service-backplane/lib/BackplaneService';
import { ServiceType, ServicesRegistry } from '../../gc-core-services/lib/ServicesRegistry';
import { GcUtils } from '../../gc-core-assets/lib/GcUtils';

/**
 *  Copyright (c) 2019, 2024 Texas Instruments Incorporated
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
const openedEventType = new EventType('opened');
const closedEventType = new EventType('closed');
const dataEventType = new EventType('data');
const errorEventType = new EventType('error');
/*
 * Global variables.
 */
const gDeviceOpened = new Map();
/**
 * @hidden
 */
class AbstractDevice extends Events {
    constructor(usbModule, descriptor) {
        super();
        this.usbModule = usbModule;
        this.descriptor = descriptor;
        this.creationTimestamp = Date.now();
        this.onOpenedHandler = (detail) => {
            if (this.getHandle(detail.descriptor) === this.handle) {
                this.console.debug(`USB ${this.displayName} opened.`);
                gDeviceOpened.set(this.handle, true);
                this.fireEvent(openedEventType, {});
            }
        };
        this.onClosedHandler = (detail) => {
            const descriptor = detail.port ?? null;
            if (this.getHandle(descriptor) === this.handle) {
                this.console.debug(`USB ${this.displayName} closed.`);
                gDeviceOpened.set(this.handle, false);
                this.fireEvent(closedEventType, {});
            }
        };
        this.onDataHandler = (detail) => {
            const data = Array.from(atob(detail.data), c => c.charCodeAt(0));
            this.console.debug(() => `USB ${this.displayName} received data=[${data}].`);
            this.fireEvent(dataEventType, { data });
        };
        this.onErrorHandler = (detail) => {
            // serial.js auto-closes on an error.
            const descriptor = detail.port;
            if (this.getHandle(descriptor) === this.handle) {
                this.console.debug(`USB ${this.displayName} received error=[${detail.error}].`);
                this.fireEvent(errorEventType, { error: detail.error });
            }
        };
    }
    get displayName() {
        return this.descriptor.displayName;
    }
    get handle() {
        return this.getHandle(this.descriptor);
    }
    get isOpened() {
        return gDeviceOpened.get(this.handle) || false;
    }
    get name() {
        return this.getName();
    }
    isEqual(device) {
        return this.name === device.name;
    }
}

/**
 *  Copyright (c) 2019, 2024 Texas Instruments Incorporated
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
const DEVICE_ATTACH_WAIT = 1000;
const BAUD_RATES = '50|75|110|134|150|300|600|1200|1800|2400|4800|7200|9600|14400|19200|28800|38400|56000|57600|115200|128000|153600|230400|256000|460800|921600';
const MAX_BAUD = 1000000000;
class UsbPortType {
    asUsbPortType(port) {
        return port;
    }
}
/**
 * @hidden
 */
class AbstractUsbPort extends AbstractDevice {
    constructor(type, usbModule, descriptor) {
        super(usbModule, descriptor);
        this.type = type;
    }
    getHandle(descriptor) {
        return (descriptor.path /* hid */ || descriptor.comName /* serial */);
    }
    get comName() {
        return this.descriptor.comName;
    }
    getName() {
        return this.comName;
    }
    async open(options) {
        this.console.logAPI(`${AbstractUsbPort.name}::${this.open.name}`, ...arguments);
        this.usbModule.addListener('serialClose', this.onClosedHandler);
        this.usbModule.addListener(`serialout_${this.descriptor.comName}`, this.onDataHandler);
        // The serial module auto-closes on an error, so this event only exists for usb-hid.  However, it doesn't
        // hurt to add a listener in the serial case (it just won't ever fire)
        this.usbModule.addListener('dataError', this.onErrorHandler);
        // If the port is attached and open is called, give enough time for it to be ready.
        const deviceAttachedTimeStamp = AbstractUsbPort.deviceAttachedTimestamp;
        if ((this.creationTimestamp - deviceAttachedTimeStamp < DEVICE_ATTACH_WAIT) && (Date.now() - deviceAttachedTimeStamp < DEVICE_ATTACH_WAIT)) {
            this.console.info(`Open port within ${DEVICE_ATTACH_WAIT}ms after device is attached, pausing for ${DEVICE_ATTACH_WAIT}ms before continuing.`);
            await GcUtils.delay(DEVICE_ATTACH_WAIT);
        }
        const vendorIdFilter = this.descriptor.vendorId;
        await this.usbModule.open({ ...this.descriptor, ...options, eventVersion: 2 }, undefined, vendorIdFilter);
        this.onOpenedHandler({ descriptor: this.descriptor });
    }
    async close() {
        this.console.logAPI(`${AbstractUsbPort.name}::${this.close.name}`, ...arguments);
        this.usbModule.removeListener('serialClose', this.onClosedHandler);
        this.usbModule.removeListener(`serialout_${this.descriptor.comName}`, this.onDataHandler);
        this.usbModule.removeListener('dataError', this.onErrorHandler);
    }
    async write(data) {
        this.console.logAPI(`${AbstractUsbPort.name}::${this.write.name}`, ...arguments);
        await this.usbModule.write(this.descriptor, data);
    }
}
AbstractUsbPort.deviceAttachedTimestamp = 0;

/**
 *  Copyright (c) 2019, 2024 Texas Instruments Incorporated
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
const usbSerialPortType = new UsbPortType();
/**
 * @hidden
 */
class UsbSerialPort extends AbstractUsbPort {
    constructor(usbModule, descriptor) {
        super(usbSerialPortType, usbModule, descriptor);
        this.console = new GcConsole('gc-service-usb', this.getName());
    }
    async open(options) {
        this.console.logAPI(`${UsbSerialPort.name}::${this.open.name}`, ...arguments);
        // TODO: [JIRA???] workaround, USBHID is not throwing error when the port is already opened
        if (this.isOpened) {
            throw Error('Serial port already opened.');
        }
        await super.open(options);
        // TODO: [GC-2233] Remove this hack when serial.js in cloud agent is fixed
        await GcUtils.delay(250);
    }
    async close() {
        this.console.logAPI(`${UsbSerialPort.name}::${this.close.name}`, ...arguments);
        if (this.isOpened) {
            await this.usbModule.close(this.descriptor);
        }
        super.close();
    }
    async setSignals(signals) {
        this.console.logAPI(`${UsbSerialPort}::${this.setSignals.name}`, ...arguments);
        await this.usbModule.setSignals(this.descriptor, signals);
    }
    async getSignals() {
        this.console.logAPI(`${UsbSerialPort}::${this.getSignals.name}`, ...arguments);
        return await this.usbModule.getSignals(this.descriptor);
    }
}

/**
 *  Copyright (c) 2019, 2024 Texas Instruments Incorporated
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
const usbHidPortType = new UsbPortType();
/**
 * @hidden
 */
class UsbHidPort extends AbstractUsbPort {
    constructor(usbModule, descriptor) {
        super(usbHidPortType, usbModule, descriptor);
        this.console = new GcConsole('gc-service-usb', this.getName());
    }
    async open(options) {
        this.console.logAPI(`${UsbHidPort.name}::${this.open.name}`, ...arguments);
        // TODO: [JIRA???] workaround, USBHID is not throwing error when the port is already opened
        if (this.isOpened) {
            throw Error('USBHID port already opened.');
        }
        await super.open(options);
    }
    async close() {
        this.console.logAPI(`${UsbHidPort.name}::${this.close.name}`, ...arguments);
        if (this.isOpened) {
            // TODO: [JIRA???] workaround, usbhid::closePort() is not the same as serial::close(), need to override the base method and call closePort
            await this.usbModule.closePort(this.descriptor);
            // TODO: [JIRA???] workaround, USBHID not firing close event, serial.js is suppressing the event by setting isCloseQuietly
            this.onClosedHandler({ port: this.descriptor });
        }
        super.close();
    }
}

/**
 *  Copyright (c) 2019, 2021 Texas Instruments Incorporated
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
const rxDataEventType = new EventType('rxData');
const rxErrorEventType = new EventType('rxError');
const makeRxDataHdlr = (resolve, reject, decoder) => {
    return (rxData) => {
        let result;
        if (decoder) {
            const retObj = decoder(rxData);
            retObj.error ? reject(retObj.error) : result = retObj.result;
        }
        else {
            result = rxData;
        }
        if (result) {
            resolve(result);
        }
    };
};
/**
 * @hidden
 */
class UsbDeviceInterface extends Events {
    constructor(usbModule, usbDevice, index, descriptor) {
        super();
        this.usbModule = usbModule;
        this.index = index;
        this.descriptor = descriptor;
        this.key = usbDevice.descriptor.key;
        this.console = new GcConsole('gc-service-usb', this.key.toString());
        this.rxErrorEventName = `rx_error.${this.key}.${this.index}`;
        this.rxDataEventName = `rx_data.${this.key}.${this.index}`;
    }
    addEventListener(type, listener) {
        this.console.logAPI(`${UsbDeviceInterface.name}::${this.addEventListener.name}`, ...arguments);
        switch (type) {
            case rxDataEventType:
                this.usbModule.addListener(this.rxDataEventName, listener);
                break;
            case rxErrorEventType:
                this.usbModule.addListener(this.rxErrorEventName, listener);
                break;
            default:
                super.addEventListener(type, listener);
        }
    }
    removeEventListener(type, listener) {
        this.console.logAPI(`${UsbDeviceInterface.name}::${this.removeEventListener.name}`, ...arguments);
        switch (type) {
            case rxDataEventType:
                this.usbModule.removeListener(this.rxDataEventName, listener);
                break;
            case rxErrorEventType:
                this.usbModule.removeListener(this.rxErrorEventName, listener);
                break;
            default:
                super.removeEventListener(type, listener);
        }
    }
    async claim(startPolling = true, numberBufsToConcat = 1) {
        this.console.logAPI(`${UsbDeviceInterface.name}::${this.claim.name}`, ...arguments);
        await this.usbModule.claimInterface(this.key, this.index, startPolling, numberBufsToConcat);
    }
    async release() {
        this.console.logAPI(`${UsbDeviceInterface.name}::${this.release.name}`, ...arguments);
        await this.usbModule.releaseInterface(this.key, this.index);
    }
    async write(data) {
        this.console.logAPI(`${UsbDeviceInterface.name}::${this.write.name}`, ...arguments);
        await this.usbModule.writeData(this.key, this.index, data);
    }
    async read(numBytesToRead) {
        this.console.logAPI(`${UsbDeviceInterface.name}::${this.read.name}`, ...arguments);
        return await this.usbModule.readData(this.key, this.index, numBytesToRead);
    }
    async sendCmd(cmd, timeout = 0, decoder) {
        this.console.logAPI(`${UsbDeviceInterface.name}::${this.sendCmd.name}`, ...arguments);
        let rxErrorHdlr, rxDataHdlr, hTimeout;
        const _clearTimeout = () => {
            if (hTimeout) {
                clearTimeout(hTimeout);
                hTimeout = undefined;
            }
        };
        return await new Promise(async (resolve, reject) => {
            rxErrorHdlr = (e) => reject(e);
            rxDataHdlr = makeRxDataHdlr((result) => {
                _clearTimeout();
                resolve(result);
            }, reject, decoder);
            this.usbModule.addListener(this.rxDataEventName, rxDataHdlr);
            this.usbModule.addListener(this.rxErrorEventName, rxErrorHdlr);
            await this.usbModule.sendCmd(this.key, this.index, cmd);
            if (timeout > 0) {
                hTimeout = setTimeout(() => {
                    hTimeout = undefined;
                    reject(`Timeout waiting for cmd=${cmd}, after ${timeout}ms.`);
                }, timeout);
            }
        }).finally(() => {
            this.usbModule.removeListener(this.rxDataEventName, rxDataHdlr);
            this.usbModule.removeListener(this.rxErrorEventName, rxErrorHdlr);
            _clearTimeout();
        });
    }
}
/**
 * @hidden
 */
class UsbDevice extends AbstractDevice {
    constructor(usbModule, descriptor) {
        super(usbModule, descriptor);
        this.usbModule = usbModule;
        this.descriptor = descriptor;
        this._interfaces = new Array();
        this.key = descriptor.key;
        this.console = new GcConsole('gc-service-usb', this.getName());
    }
    getHandle(descriptor) {
        return descriptor.key;
    }
    getName() {
        return this.displayName;
    }
    get interfaces() {
        return this._interfaces;
    }
    async open() {
        this.console.logAPI(`${UsbDevice.name}::${this.open.name}`, ...arguments);
        await this.usbModule.open(this.key);
        // query for interfaces
        const infDescriptions = await this.getDescriptors();
        this._interfaces = infDescriptions.interfaceDescriptors.map((desc, index) => {
            return new UsbDeviceInterface(this.usbModule, this, index, desc);
        });
        // usb.js doesn't fire any opened event
        this.onOpenedHandler({ descriptor: this.descriptor });
    }
    isEqual(device) {
        return this.key === device.key;
    }
    async close() {
        this.console.logAPI(`${UsbDevice.name}::${this.close.name}`, ...arguments);
        await this.usbModule.close(this.key);
        // usb.js doesn't fire closed event
        this.onClosedHandler({ port: this.descriptor });
    }
    async reset() {
        this.console.logAPI(`${UsbDevice.name}::${this.reset.name}`, ...arguments);
        await this.usbModule.reset(this.key);
    }
    async getDescriptors() {
        this.console.logAPI(`${UsbDevice.name}::${this.getDescriptors.name}`, ...arguments);
        return await this.usbModule.getDescriptors(this.key);
    }
    async getStringDescriptor(index, maxLength = 64) {
        this.console.logAPI(`${UsbDevice.name}::${this.getStringDescriptor.name}`, ...arguments);
        if (index === 0) {
            throw Error('stringIndex == 0 is not supported');
        }
        const result = await this.controlTransfer(0x80, /* IN_STANDARD_DEVICE     = 0x80 */ 6, /* GET_DESCRIPTOR         = 6    */ 3 << 8 | index & 0x0FF, /* STRING_DESCRIPTOR_TYPE = 3    */ 0x0409, maxLength);
        /**
         * Ignore the first 2 bytes, byte swap, and convert to UTF-16
         */
        const transformation = [];
        for (let i = 2; i < result.length; i = i + 2) {
            transformation.push(result[i + 1] << 8 | result[i]);
        }
        return String.fromCharCode(...transformation);
    }
    async controlTransfer(bmRequestType, bRequest, wValue, wIndex, dataOrLength) {
        this.console.logAPI(`${UsbDevice.name}::${this.controlTransfer.name}`, ...arguments);
        let resultObj = await this.usbModule.controlTransfer(this.key, bmRequestType, bRequest, wValue, wIndex, dataOrLength);
        if (resultObj && resultObj.data) {
            resultObj = resultObj.data;
        }
        return resultObj;
    }
    async uploadTestPackets(numPackets, packetSize, decoder) {
        this.console.logAPI(`${UsbDevice.name}::${this.uploadTestPackets.name}`, ...arguments);
        let rxDataHdlr;
        return await new Promise(async (resolve, reject) => {
            rxDataHdlr = makeRxDataHdlr(resolve, reject, decoder);
            this.usbModule.addListener('rx_test_data', rxDataHdlr);
            await this.usbModule.uploadTestPackets(numPackets, packetSize).fail(reject);
        }).finally(() => {
            this.usbModule.removeListener('rx_test_data', rxDataHdlr);
        });
    }
}

/**
 *  Copyright (c) 2024, 2025 Texas Instruments Incorporated
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
const usbWebSerialPortType = new UsbPortType();
/**
 * @hidden
 */
class UsbWebSerialPort extends Events {
    constructor(serialPort) {
        super();
        this.serialPort = serialPort;
        this._isOpened = false;
        this.type = usbWebSerialPortType;
        this.comName = 'unknown';
        this.name = 'unknown';
        this.busy = Promise.resolve();
        this.console = new GcConsole('gc-service-usb', this.comName);
        this.descriptor = serialPort.getInfo();
    }
    isEqual(port) {
        return this.serialPort === port.serialPort;
    }
    get isOpened() {
        return this._isOpened;
    }
    async open(options) {
        this.console.logAPI(`${UsbWebSerialPort.name}::${this.open.name}`, ...arguments);
        if (this._isOpened) {
            throw Error('Serial port already opened.');
        }
        await this.serialPort.open({ baudRate: options.baudRate ?? 9600, bufferSize: options.highWaterMark ?? 64000, flowControl: options.rtscts ? 'hardware' : 'none' });
        this._isOpened = true;
        this.fireEvent(openedEventType, {});
        this.busy = this.doReadAll();
    }
    async doReadAll() {
        while (this._isOpened && this.serialPort.readable) {
            this.reader = this.serialPort.readable.getReader();
            try {
                while (this._isOpened) {
                    const { value, done } = await this.reader.read();
                    if (done) {
                        break;
                    }
                    else if (value) {
                        this.fireEvent(dataEventType, { data: Array.from(value) });
                    }
                }
            }
            catch (error) {
                this.fireEvent(errorEventType, { error });
            }
            finally {
                this.reader.releaseLock();
                this.reader = undefined;
            }
        }
    }
    async write(data) {
        if (!this.writer) {
            this.encoder = new TextEncoder();
            this.writer = this.serialPort.writable.getWriter();
        }
        if (typeof data === 'string') {
            if (this.encoder && this.writer) {
                const bytes = this.encoder.encode(data);
                await this.writer.write(bytes);
            }
        }
        else {
            await this.writer?.write(new Uint8Array(data));
        }
    }
    async close() {
        this.console.logAPI(`${UsbWebSerialPort.name}::${this.close.name}`, ...arguments);
        if (this._isOpened) {
            this._isOpened = false;
            await this.reader?.cancel();
            await this.busy;
            this.writer?.releaseLock();
            this.writer = undefined;
            await this.serialPort.close();
            this.fireEvent(closedEventType, {});
        }
    }
    async setSignals(signals) {
        this.console.logAPI(`${UsbWebSerialPort}::${this.setSignals.name}`, ...arguments);
        //@ts-ignore
        await this.serialPort.setSignals({
            dataTerminalReady: signals.dtr,
            requestToSend: signals.rts,
            break: signals.brk
        });
    }
    async getSignals() {
        this.console.logAPI(`${UsbWebSerialPort}::${this.getSignals.name}`, ...arguments);
        //@ts-ignore
        const result = await this.serialPort.getSignals();
        return { cts: result.clearToSend, dcd: result.dataCarrierDetect, dsr: result.dataSetReady };
    }
}

/**
 *  Copyright (c) 2019, 2024 Texas Instruments Incorporated
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
 * Device attached event type.
 */
const deviceAttachedEventType = new EventType('deviceAttachedEvent');
/**
 * Device detached event type.
 */
const deviceDetachedEventType = new EventType('deviceDetachedEvent');
/*
 * Global variables.
 */
const MODULE_NAME = 'gc-service-usb';
const console = new GcConsole(MODULE_NAME);
const usbServiceType = new ServiceType(MODULE_NAME);
const mergeDeviceLists = (existingDevices, newDevices) => {
    /* remove non existing device from the new device list */
    const result = existingDevices.filter(existingDevice => newDevices.find(newDevice => existingDevice.isEqual(newDevice)));
    /* add new device into existing device list */
    const length = result.length;
    for (let i = 0; i < newDevices.length; ++i) {
        let exist = false;
        for (let j = length - 1; j >= 0; --j) {
            if (newDevices[i].isEqual(result[j])) {
                exist = true;
                break;
            }
        }
        if (!exist) {
            result.push(newDevices[i]);
        }
    }
    return result;
};
const deviceIdentificationMap = new Map([
    ['MSP432P401R', { vendorId: 0x0451, productId: 0xbef3, interfaceNumber: 0, hid: false }],
    ['MSP430F5529', { vendorId: 0x2047, productId: 0x0013, interfaceNumber: 2, hid: false }],
    ['CC3220SF', { vendorId: 0x0451, productId: 0xbef3, interfaceNumber: 0, hid: false }],
    ['TDA4VM', { vendorId: 0x10C4, productId: 0xea71, interfaceNumber: 2, hid: false }],
    ['AM62A', { vendorId: 0x0403, productId: 0x6011, interfaceNumber: 0, hid: false }]
]);
function compareDescriptorStringToNumber(a, b) {
    if (typeof a === 'string') {
        const lparam = a.toLowerCase();
        const rparam = ('0000' + b.toString(16).toLowerCase()).slice(-4);
        return lparam.localeCompare(rparam);
    }
    return a - b;
}
/**
 * @hidden
 */
class UsbService extends Events {
    constructor() {
        super();
        this.initialized = false;
        this.backplane = ServicesRegistry.getService(backplaneServiceType);
        this.usbPorts = new Array();
        this.hidPorts = new Array();
        this.devices = new Array();
        this.deviceAttachedHdlr = (key) => {
            (async () => {
                const devices = await this.listDevices(); // get an update list of device
                // find device in the devices list and fire event
                const device = devices.find(device => device.key === key);
                if (device) {
                    // Hack, store the time stamp when the device attached.
                    // Any open() call will need to be defer to let the
                    // port to be ready.
                    AbstractUsbPort.deviceAttachedTimestamp = Date.now();
                    this.fireEvent(deviceAttachedEventType, { device: device });
                }
            })();
        };
        this.deviceDetachedHdlr = (key) => {
            // find device in existing list and fire event
            const device = this.devices.find(device => device.key === key);
            this.fireEvent(deviceDetachedEventType, { device: device });
        };
    }
    async init() {
        if (!this.initialized) {
            this.initialized = true;
            this.usbModule = await this.backplane.getSubModule('USB');
            this.usbModule.addListener('attach', this.deviceAttachedHdlr);
            this.usbModule.addListener('detach', this.deviceDetachedHdlr);
            this.listDevices();
        }
    }
    addEventListener(type, listener) {
        console.logAPI(`${UsbService.name}::${this.addEventListener.name}`, ...arguments);
        this.init();
        super.addEventListener(type, listener);
    }
    removeEventListener(type, listener) {
        console.logAPI(`${UsbService.name}::${this.removeEventListener.name}`, ...arguments);
        super.removeEventListener(type, listener);
    }
    async listPorts(type, vendorIdFilter) {
        console.logAPI(`${UsbService.name}::${this.listPorts.name}`, ...arguments);
        if (type === usbWebSerialPortType) {
            const ports = await navigator?.serial?.getPorts() ?? [];
            return ports.map(port => new UsbWebSerialPort(port));
        }
        await this.init();
        /* list serial ports */
        if (type === usbSerialPortType) {
            const ports = Array();
            if (!this.serialModule) {
                this.serialModule = await this.backplane.getSubModule('Serial');
            }
            const mySerialPorts = (await this.serialModule.list()).ports;
            mySerialPorts && mySerialPorts.forEach((port) => {
                ports.push(new UsbSerialPort(this.serialModule, port));
            });
            /*
            * Merge new ports to the existing list of ports, by adding new ports to the existing list
            * and removing ports that are no longer exist in the new list. This is to ensure that
            * the same port object is returned to multiple clients and event will be fire to all
            * listeners with the same port object.
            */
            this.usbPorts = mergeDeviceLists(this.usbPorts, ports);
            if (vendorIdFilter !== undefined) {
                return this.usbPorts.filter(port => compareDescriptorStringToNumber(port.descriptor.vendorId, vendorIdFilter) === 0);
            }
            return this.usbPorts;
        }
        /* list USB-HID ports */
        if (type === usbHidPortType) {
            const ports = Array();
            if (!this.usbHidModule) {
                this.usbHidModule = await this.backplane.getSubModule('USB-HID');
            }
            const vendorId = vendorIdFilter ?? 8263;
            const myHidPorts = (await this.usbHidModule.list(vendorId)).ports;
            myHidPorts && myHidPorts.forEach((port) => {
                ports.push(new UsbHidPort(this.usbHidModule, port));
            });
            /*
            * Merge new ports to the existing list of ports, by adding new ports to the existing list
            * and removing ports that are no longer exist in the new list. This is to ensure that
            * the same port object is returned to multiple clients and event will be fire to all
            * listeners with the same port object.
            */
            let hidPortsByVendorId = this.hidPorts.filter(port => compareDescriptorStringToNumber(port.descriptor.vendorId, vendorId) === 0);
            const hidPortsByOtherVendorIds = this.hidPorts.filter(port => compareDescriptorStringToNumber(port.descriptor.vendorId, vendorId) !== 0);
            hidPortsByVendorId = mergeDeviceLists(hidPortsByVendorId, ports);
            this.hidPorts = [...hidPortsByVendorId, ...hidPortsByOtherVendorIds];
            return hidPortsByVendorId;
        }
        throw Error('Invalid type parameter.  The type parameter must be either usbSerialPortType, or usbHidPortType');
    }
    async listDevices(vendorId) {
        console.logAPI(`${UsbService.name}::${this.listDevices.name}`, ...arguments);
        await this.init();
        if (!this.usbModule) {
            this.usbModule = await this.backplane.getSubModule('USB');
        }
        const devices = Array();
        const myDevices = (await this.usbModule.list(vendorId || '')).deviceInfoList;
        myDevices && myDevices.forEach((device) => {
            devices.push(new UsbDevice(this.usbModule, device));
        });
        this.devices = mergeDeviceLists(this.devices, devices);
        return this.devices;
    }
    async getDefaultPort(ports, deviceName) {
        console.logAPI(`${UsbService.name}::${this.getDefaultPort.name}`, ...arguments);
        await this.init();
        if (deviceName) {
            const filterOptions = deviceIdentificationMap.get(deviceName);
            if (filterOptions) {
                const filteredPorts = this.filterPortsByDescriptorInfo(ports, filterOptions);
                if (filteredPorts.length > 0) {
                    // only update ports if we found a useful default, otherwise let backplane pick from full list.
                    ports = filteredPorts;
                }
            }
        }
        const serialPorts = ports.filter(port => port.type === usbSerialPortType).map(port => port.descriptor);
        const util = await this.backplane.getUtil();
        if (serialPorts.length > 0) {
            await util.selectDefaultPort({ ports: serialPorts, targetName: deviceName });
        }
        const baudRates = await util.getBaudRates();
        for (let i = 0; i < ports.length; ++i) {
            if (ports[i].type === usbSerialPortType && ports[i].descriptor.selected) {
                ports[i].descriptor.selected = false; // clear selected flag for next time.
                for (let j = 0; j < baudRates.length; ++j) {
                    if (baudRates[j].selected) {
                        return { port: ports[i], baudRate: (+baudRates[j].rate) };
                    }
                }
                return { port: ports[i] };
            }
        }
        const hidPorts = ports.filter(port => port.type === usbHidPortType);
        if (hidPorts.length > 0 && serialPorts.length > 0) {
            return { port: hidPorts[0] }; // for mixed serial and hid default to hid over usb, since hid ports are filtered by Texas Instruments manufacture id.
        }
    }
    filterPortsByDescriptorInfo(ports, filterBy) {
        console.logAPI(`${UsbService.name}::${this.filterPortsByDescriptorInfo.name}`, ...arguments);
        if (filterBy.hid !== undefined) {
            ports = ports.filter(port => port.type === (filterBy.hid ? usbHidPortType : usbSerialPortType));
        }
        if (filterBy.vendorId !== undefined) {
            ports = ports.filter(port => compareDescriptorStringToNumber(port.descriptor.vendorId, filterBy.vendorId) === 0);
        }
        if (filterBy.productId !== undefined) {
            ports = ports.filter(port => compareDescriptorStringToNumber(port.descriptor.productId, filterBy.productId) === 0);
        }
        if (filterBy.interfaceNumber !== undefined) {
            ports = ports.filter(port => {
                if (port.descriptor.pnpId) {
                    // convert machineInterface to a 2 digit hex number and look for it as suffix to pnpId
                    // this is the same as what agent.js does for windows and linux.  Mac is different.
                    // Updated: seeing pnpId ending in -ifXX-port0 on linux, so adding extra check for -ifXX- to also match the interface number
                    const mi = ('00' + filterBy.interfaceNumber.toString(16).toLowerCase()).slice(-2);
                    return port.descriptor.pnpId.toLowerCase().endsWith(mi) || port.descriptor.pnpId.toLowerCase().indexOf(`-if${mi}-`) > 0;
                }
                return true;
            });
        }
        return ports;
    }
}
ServicesRegistry.register(usbServiceType, UsbService);

/**
 *  Copyright (c) 2021 Texas Instruments Incorporated
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

export { AbstractDevice, AbstractUsbPort, BAUD_RATES, MAX_BAUD, UsbDevice, UsbDeviceInterface, UsbHidPort, UsbPortType, UsbSerialPort, UsbService, UsbWebSerialPort, closedEventType, dataEventType, deviceAttachedEventType, deviceDetachedEventType, errorEventType, openedEventType, rxDataEventType, rxErrorEventType, usbHidPortType, usbSerialPortType, usbServiceType, usbWebSerialPortType };
//# sourceMappingURL=ServiceUsb.js.map
