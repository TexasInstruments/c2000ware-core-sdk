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
/* eslint-disable @typescript-eslint/no-empty-interface */
/* eslint-disable prefer-rest-params */
/* eslint-disable @typescript-eslint/no-explicit-any */
/**
 * `UsbHidPort` provides a higher level abstraction for communicating with usb hid port.
 *
 * @example
 * ```typescript
 * import { ServiceRegistry } from '<path-to>/gc-core-service/lib/ServiceRegistry';
 * import { usbServiceType } from '<path-to>/gc-service-usb/lib/UsbService';
 * import { usbHidPortType } from '<path-to>/gc-service-usb/lib/UsbHidPort';
 *
 * const service = ServiceRegistry.getService(usbServiceType);
 * const ports = await service.listPorts({ type: usbHidPortType });
 * ```
 *
 * @packageDocumentation
 */
import { GcConsole } from '../../../gc-core-assets/lib/GcConsole';
import { AbstractUsbPort, UsbPortType } from './AbstractUsbPort';
export * from './AbstractUsbPort';
export const usbHidPortType = new UsbPortType();
/**
 * @hidden
 */
export class UsbHidPort extends AbstractUsbPort {
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
        // TODO: [JIRA???] workaround, usbhid::closePort() is not the same as serial::close(), need to override the base method and call closePort
        await this.usbModule.closePort(this.descriptor);
        // TODO: [JIRA???] workaround, USBHID not firing close event, serial.js is suppressing the event by setting isCloseQuietly
        this.onClosedHandler({ port: this.descriptor });
        super.close();
    }
}
//# sourceMappingURL=UsbHidPort.js.map