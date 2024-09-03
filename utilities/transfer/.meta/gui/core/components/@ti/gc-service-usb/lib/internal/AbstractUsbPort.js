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
/* eslint-disable @typescript-eslint/no-explicit-any */
/* eslint-disable prefer-rest-params */
/* eslint-disable @typescript-eslint/no-empty-interface */
import { AbstractDevice } from './AbstractDevice';
export * from './AbstractDevice';
import { GcUtils } from '../../../gc-core-assets/lib/GcUtils';
const DEVICE_ATTACH_WAIT = 1000;
export const BAUD_RATES = '50|75|110|134|150|300|600|1200|1800|2400|4800|7200|9600|14400|19200|28800|38400|56000|57600|115200|128000|153600|230400|256000|460800|921600';
export const MAX_BAUD = 1000000000;
export class UsbPortType {
    asUsbPortType(port) {
        return port;
    }
}
/**
 * @hidden
 */
export class AbstractUsbPort extends AbstractDevice {
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
        this.usbModule.addListener('serialOpen', this.onOpenedHandler);
        this.usbModule.addListener('serialClose', this.onClosedHandler);
        this.usbModule.addListener('serialout', this.onDataHandler);
        this.usbModule.addListener('dataError', this.onErrorHandler);
        // If the port is attached and open is called, give enough time for it to be ready.
        const deviceAttachedTimeStamp = AbstractUsbPort.deviceAttachedTimestamp;
        if ((this.creationTimestamp - deviceAttachedTimeStamp < DEVICE_ATTACH_WAIT) && (Date.now() - deviceAttachedTimeStamp < DEVICE_ATTACH_WAIT)) {
            this.console.info(`Open port within ${DEVICE_ATTACH_WAIT}ms after device is attached, pausing for ${DEVICE_ATTACH_WAIT}ms before continuing.`);
            await GcUtils.delay(DEVICE_ATTACH_WAIT);
        }
        await this.usbModule.open({ ...this.descriptor, ...options });
        // TODO: [GC-2278] Remove this call when serial.js/usbhid.js cloud agent is fixed
        this.onOpenedHandler({ descriptor: this.descriptor });
    }
    async close() {
        this.console.logAPI(`${AbstractUsbPort.name}::${this.close.name}`, ...arguments);
        this.usbModule.removeListener('serialOpen', this.onOpenedHandler);
        this.usbModule.removeListener('serialClose', this.onClosedHandler);
        this.usbModule.removeListener('serialout', this.onDataHandler);
        this.usbModule.removeListener('dataError', this.onErrorHandler);
    }
    async write(data) {
        this.console.logAPI(`${AbstractUsbPort.name}::${this.write.name}`, ...arguments);
        await this.usbModule.write(this.descriptor, data);
    }
}
AbstractUsbPort.deviceAttachedTimestamp = 0;
//# sourceMappingURL=AbstractUsbPort.js.map