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
/* eslint-disable prefer-rest-params */
/* eslint-disable @typescript-eslint/no-explicit-any */
/**
 * `UsbSerialPorts` provides a higher level abstraction communicating with usb serial port.
 *
 * @example
 * ```typescript
 * import { ServicesRegistry } from '<path-to>/gc-core-service/lib/ServicesRegistry';
 * import { usbServiceType, usbSerialPortType } from '<path-to>/gc-service-usb/lib/ServiceUsb';
 *
 * const service = ServicesRegistry.getService(usbServiceType);
 * const ports = await service.listPorts({ type: usbSerialPortType });
 * ```
 *
 * @packageDocumentation
 */
import { GcConsole } from '../../../gc-core-assets/lib/GcConsole';
import { GcUtils } from '../../../gc-core-assets/lib/GcUtils';
import { AbstractUsbPort, UsbPortType } from './AbstractUsbPort';
export * from './AbstractUsbPort';
export const usbSerialPortType = new UsbPortType();
/**
 * @hidden
 */
export class UsbSerialPort extends AbstractUsbPort {
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
    async setBaudRate(baudRate) {
        this.console.logAPI(`${UsbSerialPort}::${this.setBaudRate.name}`, ...arguments);
        await this.usbModule.overrideBaudRate(this.descriptor, baudRate);
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
//# sourceMappingURL=UsbSerialPort.js.map