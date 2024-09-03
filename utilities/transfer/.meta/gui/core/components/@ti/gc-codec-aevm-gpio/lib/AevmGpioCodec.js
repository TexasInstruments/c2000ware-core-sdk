import { AbstractCodec, NoopDecoderType, nullDataCodec } from '../../gc-target-configuration/lib/TargetConfiguration';
import { modeMap, resistorMap } from '../../gc-target-configuration/lib/ICodecGpioBaseParams';
import { IAevmEncoderType, nullAevmEncoder, getPayload } from '../../gc-codec-aevm/lib/AevmCodec';
import { RefreshIntervalBindValue, refreshEventType } from '../../gc-core-databind/lib/CoreDatabind';
import { streamingCodecDataType } from '../../gc-model-streaming/lib/StreamingDataModel';
import { GcUtils } from '../../gc-core-assets/lib/GcUtils';

/**
 *  Copyright (c) 2020, 2021 Texas Instruments Incorporated
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
const pinStateMap = { 'high': 1, 'low': 0 };
const triggerTypeMap = {
    'rising': 0,
    'falling': 1,
    'bothEdge': 2,
    'high': 3,
    'low': 4
};
const maxPinCount = 32;
const GPIO_TYPE = 0x04;
const GPIO_CMD_NOTIFY_INTERRUPT = 0x5; // the command used by controller to notify us that an interrupt is occurred.
const pinMasks = (pin) => ({ pinMask1: (1 << pin) & 0xFFFF, pinMask2: (1 << pin) >>> 16 });
class AevmGpioCodec extends AbstractCodec {
    constructor(params) {
        super(params.id || 'gpio', NoopDecoderType, IAevmEncoderType, streamingCodecDataType, streamingCodecDataType);
        this.params = params;
        this.targetEncoder = nullAevmEncoder;
        this.targetDecoder = nullDataCodec;
        this.refreshListener = () => {
            this.read();
        };
        this.inputPins = [];
        this.pinNameMap = {};
        this.nameToPinMap = {};
        this.readMask1 = 0;
        this.readMask2 = 0;
    }
    /**
     * @hidden
     */
    async onDisconnect(transport) {
        this.removeRefreshListener();
    }
    /**
     * @hidden
     */
    onConnect(transport) {
        return this.configureFirmware();
    }
    configureFirmware() {
        const params = this.params;
        const pinParams = params.pins ?? [];
        this.inputPins = [];
        this.pinNameMap = {};
        const promises = [];
        const interruptMasks = [0, 0];
        const triggerTypes = [];
        for (const pinParm of pinParams) {
            if (pinParm.pin === undefined) {
                throw Error('GPIO missing required pin number');
            }
            const pin = GcUtils.parseNumberProperty('pin, in the GPIO interface', pinParm.pin, 0, maxPinCount - 1);
            if (pinParm.id !== undefined) {
                this.pinNameMap[pin] = pinParm.id;
                this.nameToPinMap[pinParm.id] = pin;
            }
            const { pinMask1, pinMask2 } = pinMasks(pin);
            // mode (ref ocf_defs.h): 1: GPIO_Output; 2: GPIO_InputNoResistor; 3: GPIO_InputPullup; 4: GPIO_InputPullDown; 5: GPIO_OutputOpenDrain
            let pinFunction = GcUtils.parseStringProperty('mode', pinParm.mode ?? '', modeMap);
            if (pinFunction === modeMap.input) {
                this.inputPins.push(pin);
                if (pinParm.resistor !== undefined) {
                    pinFunction += GcUtils.parseStringProperty('resistor', pinParm.resistor, resistorMap);
                }
                this.readMask1 |= pinMask1;
                this.readMask2 |= pinMask2;
            }
            else if (pinParm.openDrain) {
                pinFunction += 4;
            }
            promises.push(this.targetEncoder.readResponse(this.targetEncoder.sendCommandPacket(GPIO_TYPE, 0, 0 /* Enable */, [pinMask1, 1, pinMask2], [])));
            promises.push(this.targetEncoder.readResponse(this.targetEncoder.sendCommandPacket(GPIO_TYPE, 0, 1 /* Config */, [pinMask1, pinFunction, pinMask2], [])));
            if (pinParm.state !== undefined) {
                const state = GcUtils.parseStringProperty('state, in the GPIO interface', pinParm.state, pinStateMap);
                promises.push(this.targetEncoder.readResponse(this.targetEncoder.sendCommandPacket(GPIO_TYPE, 0, 2 /* Write */, [pinMask1, state === 1 ? pinMask1 : 0, pinMask2, state === 1 ? pinMask2 : 0], [])));
            }
            if (pinParm.triggerType !== undefined) {
                interruptMasks[0] |= pinMask1;
                interruptMasks[1] |= pinMask2;
                triggerTypes.push(GcUtils.parseStringProperty('', pinParm.triggerType, triggerTypeMap));
            }
        }
        if (triggerTypes.length > 0) {
            const params = [interruptMasks[0]];
            for (let i = 0; i < 3; i++) {
                params[i] = triggerTypes[i] ?? 0;
                params[i + 4] = triggerTypes[i] !== undefined ? 1 : 0;
            }
            params.push(interruptMasks[1]);
            promises.push(this.targetEncoder.readResponse(this.targetEncoder.sendCommandPacket(GPIO_TYPE, 0, 4 /* RegisterInterrupt */, params, [])));
        }
        if (this.inputPins.length > 0) {
            const refereshInterval = params.refereshInterval ?? 100;
            if (this.refreshBinding === undefined) {
                this.refreshBinding = new RefreshIntervalBindValue(refereshInterval);
                this.refreshBinding.addEventListener(refreshEventType, this.refreshListener);
            }
            else {
                this.refreshBinding.setValue(refereshInterval);
            }
        }
        else {
            this.removeRefreshListener();
        }
        return Promise.all(promises);
    }
    removeRefreshListener() {
        if (this.refreshBinding !== undefined) {
            this.refreshBinding.removeEventListener(refreshEventType, this.refreshListener);
            this.refreshBinding = undefined;
        }
    }
    encode(data) {
        let writeMask1 = 0, writeMask2 = 0, value1 = 0, value2 = 0;
        for (const pinName in data) {
            const pinNumber = this.nameToPinMap[pinName];
            if (pinNumber !== undefined) {
                const { pinMask1, pinMask2 } = pinMasks(pinNumber);
                writeMask1 |= pinMask1;
                writeMask2 |= pinMask2;
                if (data[pinName]) {
                    value1 |= pinMask1;
                    value2 |= pinMask2;
                }
            }
        }
        this.targetEncoder.readResponse(this.targetEncoder.sendCommandPacket(GPIO_TYPE, 0, 2 /* Write */, [writeMask1, value1, writeMask2, value2], []));
    }
    async read() {
        try {
            let result = await this.targetEncoder.readResponse(this.targetEncoder.sendCommandPacket(GPIO_TYPE, 0, 3 /* Read */, [this.readMask1, this.readMask2], []));
            result = getPayload(result);
            const value1 = GcUtils.bytesToValue(result.slice(0, 4));
            const value2 = GcUtils.bytesToValue(result.slice(4, 8));
            const data = {};
            for (const pinNumber of this.inputPins) {
                const pinName = this.pinNameMap[pinNumber];
                if (pinName !== undefined) {
                    const { pinMask1, pinMask2 } = pinMasks(pinNumber);
                    data[pinName] = (value1 & pinMask1) > 0 || (value2 & pinMask2) > 0;
                }
            }
            this.targetDecoder.decode(data);
        }
        catch (e) {
            // If the command packet is just sent, and its response has not arrived before disconnect,
            // the message queue will reject the response promise.
            // Catch error here and it is fine not to do anything.
        }
    }
}

export { AevmGpioCodec };
//# sourceMappingURL=AevmGpioCodec.js.map
