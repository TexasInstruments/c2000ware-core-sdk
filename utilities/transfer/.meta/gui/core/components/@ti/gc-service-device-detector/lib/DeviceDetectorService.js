import { EventType, Events } from '../../gc-core-assets/lib/Events';
import { GcConsole } from '../../gc-core-assets/lib/GcConsole';
import { ServiceType, ServicesRegistry } from '../../gc-core-services/lib/ServicesRegistry';
import { backplaneServiceType } from '../../gc-service-backplane/lib/BackplaneService';

/**
 *  Copyright (c) 2022 Texas Instruments Incorporated
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
const MODULE_NAME = 'gc-service-device-detector';
const console = new GcConsole(MODULE_NAME);
const deviceAttachedEventType = new EventType('deviceDetectorAttachedEvent');
const deviceDetachedEventType = new EventType('deviceDetectorDetachedEvent');
const progressEventType = new EventType('deviceDetectorProgressEvent');
class DetectedDeviceImpl {
    constructor(probe, device) {
        this.probe = probe;
        this.device = device;
        this.isLaunchPad = !!this.device.id;
    }
    get id() {
        // determine if this is a launchPad, if not a launchpad then id is undefined, null, or "", so use name instead
        if (!this.isLaunchPad && this.device.name) {
            return this.device.name;
        }
        else {
            return this.device.id;
        }
    }
    get name() {
        return this.device.name;
    }
    get family() {
        return this.device.family;
    }
    get deviceXml() {
        return this.device.deviceXml;
    }
    get debugProbeSerial() {
        return this.probe.serialNumber;
    }
}
const deviceDetectorServiceType = new ServiceType(MODULE_NAME);
class DeviceDetectorService extends Events {
    constructor() {
        super();
        this.deviceDetector = undefined;
        this.detectedDevices = [];
        this.progressListener = (eventData) => {
            console.debug(() => JSON.stringify(eventData));
            this.fireEvent(progressEventType, eventData);
        };
        this.attachedListener = () => {
            this.doDetect(true);
        };
        this.detachedListener = () => {
            this.doDetect(true);
        };
        this.init();
    }
    init() {
        const backplaneService = ServicesRegistry.getService(backplaneServiceType);
        this.whenReady = backplaneService.getSubModule('DeviceDetector').then(deviceDetector => {
            this.deviceDetector = deviceDetector;
            this.deviceDetector?.addListener('progress', this.progressListener);
            this.deviceDetector?.addListener('attach', this.attachedListener);
            this.deviceDetector?.addListener('detach', this.detachedListener);
        });
    }
    async detect() {
        const detectedDevices = await this.doDetect(false);
        console.debug(`detected devices = ${this.detectedDevices.map(d => d.name)}`);
        return detectedDevices;
    }
    async doDetect(notify = false) {
        const existingDetectedDevices = this.detectedDevices;
        this.detectedDevices = [];
        await this.whenReady;
        if (this.deviceDetector) {
            const { probes } = await this.deviceDetector.detectDebugProbes();
            if (probes.length > 0) {
                for (const probe of probes) {
                    const device = await this.deviceDetector.detectDeviceWithProbe(probe);
                    const detectedDevice = new DetectedDeviceImpl(probe, device);
                    this.detectedDevices.push(detectedDevice);
                }
            }
        }
        this.onAfterDetectDebugProbes();
        if (notify) {
            // devices attached
            const attachedDevices = this.detectedDevices.filter(detectedDevice => {
                return !existingDetectedDevices.find(oldDevice => oldDevice.id === detectedDevice.id);
            });
            // devices detached
            const detachedDevices = existingDetectedDevices.filter(oldDevice => {
                return !this.detectedDevices.find(detectedDevice => detectedDevice.id === oldDevice.id);
            });
            // fire attached devices
            if (attachedDevices.length > 0) {
                this.fireEvent(deviceAttachedEventType, { attachedDevices, allDevices: this.detectedDevices });
                console.debug(`device attached ${attachedDevices.map(d => d.name)}`);
            }
            // fire detached devices
            if (detachedDevices.length > 0) {
                this.fireEvent(deviceDetachedEventType, { detachedDevices, allDevices: this.detectedDevices });
                console.debug(`device detached ${detachedDevices.map(d => d.name)}`);
            }
        }
        return this.detectedDevices;
    }
    onAfterDetectDebugProbes() {
        // noop, this is to enable test to override behavior in the doDetect method.
    }
}
ServicesRegistry.register(deviceDetectorServiceType, DeviceDetectorService);

export { DeviceDetectorService, MODULE_NAME, deviceAttachedEventType, deviceDetachedEventType, deviceDetectorServiceType, progressEventType };
//# sourceMappingURL=DeviceDetectorService.js.map
