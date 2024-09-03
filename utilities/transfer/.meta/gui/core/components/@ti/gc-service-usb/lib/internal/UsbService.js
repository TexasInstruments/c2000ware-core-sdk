/**
 *  Copyright (c) 2019, 2023 Texas Instruments Incorporated
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
/* eslint-disable @typescript-eslint/no-explicit-any */
/* eslint-disable prefer-rest-params */
/**
 * `UsbService` handles communications with the low level USB-Serial/USB-HID/USB-Device modules.
 * For USB-Serial and USB-HID devices, use the `listPorts` API to get a list of ports and
 * use the `listDevices` API to get a list of devices. Device handles communication with
 * TI USB devices and USB hub using low-level USB APIs such as controlTransfer. Device also
 * supports USB-BULK data transfer.
 *
 * @example
 * ```typescript
 * import { ServicesRegistry } from '<path-to>/gc-core-service/lib/ServicesRegistry';
 * import { usbServiceType, usbSerialPortType, usbHidPortType  } from '<path-to>/gc-service-usb/lib/UsbService';
 *
 * const service = ServicesRegistry.getService(usbServiceType);
 * const serialPorts = await service.listPorts(usbSerialPortType);
 * const hidPorts = await service.listPorts(usbHidPortType);
 * const devices = await service.listDevices();
 * ```
 *
 * @packageDocumentation
 */
import { GcConsole } from '../../../gc-core-assets/lib/GcConsole';
import { Events, EventType } from '../../../gc-core-assets/lib/Events';
import { backplaneServiceType } from '../../../gc-service-backplane/lib/BackplaneService';
import { ServicesRegistry, ServiceType } from '../../../gc-core-services/lib/ServicesRegistry';
import { AbstractUsbPort } from './AbstractUsbPort';
import { UsbSerialPort, usbSerialPortType } from './UsbSerialPort';
import { UsbHidPort, usbHidPortType } from './UsbHidPort';
import { UsbDevice } from './UsbDevice';
/**
 * Device attached event type.
 */
export const deviceAttachedEventType = new EventType('deviceAttachedEvent');
/**
 * Device detached event type.
 */
export const deviceDetachedEventType = new EventType('deviceDetachedEvent');
/*
 * Global variables.
 */
const MODULE_NAME = 'gc-service-usb';
const console = new GcConsole(MODULE_NAME);
export const usbServiceType = new ServiceType(MODULE_NAME);
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
export class UsbService extends Events {
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
            if (device) {
                this.fireEvent(deviceDetachedEventType, { device: device });
            }
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
            const vendorId = vendorIdFilter !== null && vendorIdFilter !== void 0 ? vendorIdFilter : 8263;
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
//# sourceMappingURL=UsbService.js.map