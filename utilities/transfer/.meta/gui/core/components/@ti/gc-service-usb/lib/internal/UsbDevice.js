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
/* eslint-disable no-async-promise-executor */
/* eslint-disable prefer-rest-params */
/* eslint-disable @typescript-eslint/no-explicit-any */
/* eslint-disable @typescript-eslint/no-empty-interface */
/**
 * `UsbDevice` provides a higher level abstraction for communicating with usb devices.
 *
 * @example
 * ```typescript
 * import { ServiceRegistry } from '<path-to>/gc-core-service/lib/ServiceRegistry';
 * import { usbServiceType } from '<path-to>/gc-service-usb/lib/UsbService';
 *
 * const service = ServiceRegistry.getService(usbServiceType);
 * const devices = await usbService.listDevices();
 * ```
 *
 * @packageDocumentation
 */
import { AbstractDevice } from './AbstractDevice';
import { EventType, Events } from '../../../gc-core-assets/lib/Events';
import { GcConsole } from '../../../gc-core-assets/lib/GcConsole';
export const rxDataEventType = new EventType('rxData');
export const rxErrorEventType = new EventType('rxError');
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
export class UsbDeviceInterface extends Events {
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
export class UsbDevice extends AbstractDevice {
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
//# sourceMappingURL=UsbDevice.js.map