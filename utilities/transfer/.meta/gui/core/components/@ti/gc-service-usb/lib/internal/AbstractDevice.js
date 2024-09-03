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
/* eslint-disable @typescript-eslint/no-empty-interface */
import { EventType, Events } from '../../../gc-core-assets/lib/Events';
export const openedEventType = new EventType('opened');
export const closedEventType = new EventType('closed');
export const dataEventType = new EventType('data');
export const errorEventType = new EventType('error');
/*
 * Global variables.
 */
const gDeviceOpened = new Map();
/**
 * @hidden
 */
export class AbstractDevice extends Events {
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
            let descriptor = null;
            // TODO: [JIRA???] serial.js: map port to descriptor
            if (detail.port) {
                descriptor = detail.port;
            }
            if (this.getHandle(descriptor) === this.handle) {
                this.console.debug(`USB ${this.displayName} closed.`);
                gDeviceOpened.set(this.handle, false);
                this.fireEvent(closedEventType, {});
            }
        };
        this.onDataHandler = (detail) => {
            let descriptor = null;
            // TODO: [JIRA???] serial.js: map comName to descriptor.comName
            if (detail.comName) {
                descriptor = { comName: detail.comName };
            }
            // TODO: [JIRA???] usbhid.js: returns portInfo rather than descriptor
            if (detail.portInfo) {
                descriptor = detail.portInfo;
            }
            if (this.getHandle(descriptor) === this.handle) {
                this.console.debug(`USB ${this.displayName} received data=[${detail.buffer}].`);
                this.fireEvent(dataEventType, { data: detail.buffer });
            }
        };
        this.onErrorHandler = (detail) => {
            let descriptor = null;
            // TODO: does serial.js has a different way of returning error?
            // TODO: [JIRA???] usbhid.js returns port rather than descriptor
            if (detail.port) {
                descriptor = detail.port;
            }
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
//# sourceMappingURL=AbstractDevice.js.map