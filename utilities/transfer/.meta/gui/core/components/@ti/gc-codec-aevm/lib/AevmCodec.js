import { EncoderType, NoopDecoderType, AbstractMessageBasedDecoder, AbstractFrameDecoder } from '../../gc-target-configuration/lib/TargetConfiguration';
import { Events } from '../../gc-core-assets/lib/Events';
import { DEFAULT_MAX_CONSECUTIVE_ERRORS, receiveInterruptEventType } from '../../gc-target-configuration/lib/ICodecAnalogControllerBaseParams';
import { GcPromise } from '../../gc-core-assets/lib/GcPromise';
import { GcUtils } from '../../gc-core-assets/lib/GcUtils';
import { GcConsole } from '../../gc-core-assets/lib/GcConsole';

/**
 *  Copyright (c) 2020, 2024 Texas Instruments Incorporated
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
const IAevmEncoderType = new EncoderType('aevmPacket');
class NullAevmEncoder extends Events {
    constructor() {
        super(...arguments);
        this.id = 'nullAevmEncoder';
        this.encoderInputType = IAevmEncoderType;
        this.encoderOutputType = NoopDecoderType;
    }
    sendCommandPacket(interfaceType, unit, cmd, params, payload) {
        throw Error('Null encoder is called.');
    }
    readResponse(packet) {
        throw Error('Null encoder is called.');
    }
    addChildDecoder(child) {
    }
    dispose() {
    }
}
const nullAevmEncoder = new NullAevmEncoder();
const HEADER_SIGNATURE = 0xD402;
const HEADER_SIGNATURE_AS_BYTES = [(HEADER_SIGNATURE & 0xff), (HEADER_SIGNATURE >> 8) & 0xff];
const HEADER_LENGTH = 52;
const HEADER_PAYLOAD_LEN_START = 14;
const HEADER_PAYLOAD_LEN_END = 16;
const MAX_PAYLOAD = 2048;
const INTERRUPT_PACKET = 4;
const getPayloadLength = (bytes, offset) => {
    const ofs = offset ?? 0;
    return GcUtils.bytesToValue(bytes.slice(HEADER_PAYLOAD_LEN_START + ofs, HEADER_PAYLOAD_LEN_END + ofs), 'little');
};
const getPayload = (packet) => {
    return packet.slice(HEADER_LENGTH, HEADER_LENGTH + getPayloadLength(packet));
};
const console = new GcConsole('gc-codec-aevm');
class AevmCodec extends AbstractMessageBasedDecoder {
    constructor(params) {
        super(params.id || 'aevm', console);
        this.params = params;
        this.encoderInputType = IAevmEncoderType;
        this.encoderOutputType = NoopDecoderType;
        this.version = '';
        this.sentPacketCount = 0;
        this.receivedPacketCount = 0;
        this.consecutiveErrorCount = 0;
        this.consecutiveErrorLimit = DEFAULT_MAX_CONSECUTIVE_ERRORS;
        this.frameDecoder = new (class extends AbstractFrameDecoder {
            constructor(packetDecoder) {
                super('aevmPacketFrameDecoder', ...HEADER_SIGNATURE_AS_BYTES);
                this.packetDecoder = packetDecoder;
                this.params = {};
            }
            getPacketLength(buffer, offset) {
                return buffer.length - offset < HEADER_LENGTH ? 0 : HEADER_LENGTH + getPayloadLength(buffer, offset);
            }
            decodePacket(packet) {
                return this.packetDecoder.decodePacket(packet);
            }
        })(this);
    }
    /**
     * @hidden
     */
    addChildDecoder(child) {
        // called by CodecRegistry, after deconfigure but before connect
    }
    /**
     * @hidden
     */
    async onConnect(transport) {
        this.frameDecoder.deconfigure();
        this.transport = transport;
        this.sentPacketCount = 0;
        this.receivedPacketCount = 0;
        this.consecutiveErrorCount = 0;
        this.consecutiveErrorLimit = this.params.maxConsecutiveErrors ?? DEFAULT_MAX_CONSECUTIVE_ERRORS;
        const timeoutInMs = this.params.connectTimeout ?? 250;
        const result = await GcPromise.timeout(this.getControllerInfo(), timeoutInMs, 'No response from AEVM controller.');
        const payload = getPayload(result);
        this.version = payload.slice(8, 12).join('.');
        // Let the logic compare version, prompt user and wait for user's decision, and update firmware if needed. Hence there is no timeout.
        await this.checkFirmware({ detectedFirmwareVersion: this.version, modelID: this.params.id || 'aevm', codec: this, controller: 'aevm' }, this.params.firmwareCheck);
        if (this.params.resetControllerOnConnect === true) {
            await this.resetController();
        }
    }
    decode(data) {
        return this.frameDecoder.detectPackets(data);
    }
    decodePacket(rawData) {
        try {
            // frame decoder already checked header signature, packet size
            const packetType = GcUtils.bytesToValue(rawData.slice(2, 4), 'little');
            const status = new DataView((new Uint8Array(rawData.slice(4, 8)).buffer)).getInt32(0);
            const makeupCommand = this.makeupCommand(rawData);
            const isSuccess = status >= 0 || ((-status & 0x00ff) === 0);
            if (packetType === INTERRUPT_PACKET) {
                // do not increment receivedPacketCount
                this.fireEvent(receiveInterruptEventType, { payload: getPayload(rawData) });
            }
            else if (isSuccess === false) {
                this.receivedPacketCount += 1;
                if (this.transport?.isConnected) {
                    this.consecutiveErrorCount++;
                }
                this.addErrorResponse(String.fromCharCode(...getPayload(rawData)), makeupCommand, 0);
                if (this.consecutiveErrorLimit >= 0 && this.consecutiveErrorCount > this.consecutiveErrorLimit) {
                    throw Error(`Too many consecutive errors (${this.consecutiveErrorCount}) received.`);
                }
            }
            else {
                // aevm has data packet, but does not have payload packet and reply packet.
                // Should we addResponse or should we fireEvent(payload event type)?
                // Our internal codecs take the pattern of promise.then(...) through
                // readResponse. If addResponse either cur.deferred.reject or resolve response,
                // we are done.
                // If external codec does not want to take the pattern of promise.then(...) through
                // readResponse, and instead, want to take the pattern of listening to payload event
                // In this case, there is no 'deferred guy' in the response queue waiting for response.
                // We need to review the line " if (cur.command !== command) cur.deferred!.reject... " in addResponse.
                // because the line pass the rejection to the 'next' guy in the queue who is not waiting for the current
                // response but the next response.
                this.receivedPacketCount += 1;
                this.consecutiveErrorCount = 0;
                this.addResponse(rawData, makeupCommand, 0);
                // when do we need to this.fireEvent(receivePayloadEventType, { payload: getPayload(rawData) }); ?
            }
            return true;
        }
        catch (e) {
            return e;
        }
        finally {
            super.decode(rawData); // must call AbstractMessagedBasedCodec to deal with pending transmissions
        }
    }
    sendCommandPacket(interfaceType, unit, cmd, params, payload) {
        if (payload.length > MAX_PAYLOAD) {
            throw Error('Too much payload data for a single packet.');
        }
        let packet = [...HEADER_SIGNATURE_AS_BYTES,
            1, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
            1, 0, // packet number
        ];
        GcUtils.setBytesLSB(packet, 2, payload.length, packet.length);
        packet.push(unit);
        packet.push(interfaceType);
        GcUtils.setBytesLSB(packet, 2, cmd, packet.length);
        for (let i = 0; i < 8; i++) {
            GcUtils.setBytesLSB(packet, 4, params[i] ?? 0, packet.length);
        }
        packet = packet.concat(payload);
        this.encode(packet);
        return packet;
    }
    readResponse(packet) {
        return this.addCommand(this.makeupCommand(packet), 0);
    }
    makeupCommand(packet) {
        // make up a 'command' from unit (packet[16]), interfaceType (packet[17]),
        // and command (packet[18,19]) for internal command/response queue
        return GcUtils.bytesToValue(packet.slice(16, 20), 'little');
    }
    invokeBSL() {
        return this.sendCommandPacket(0, 0, 0x6, [], []);
    }
    getControllerInfo() {
        return this.readResponse(this.sendCommandPacket(0, 0, 0x9, [], []));
    }
    resetController() {
        return this.readResponse(this.sendCommandPacket(0, 0, 0xe, [], []));
    }
    async ping() {
        await super.ping();
        const pingPromise = this.getControllerInfo();
        return GcPromise.timeout(pingPromise, 250, 'Ping failure: no response of firmware version read from ' + this.id);
    }
    /**
     * @hidden
     */
    shouldPauseTransmission(txPacket) {
        const pause = this.sentPacketCount - this.receivedPacketCount > (this.params.maxOutstandingCommands ?? 0);
        if (!pause) {
            this.sentPacketCount += 1;
        }
        return pause;
    }
}

export { AevmCodec, IAevmEncoderType, getPayload, nullAevmEncoder };
//# sourceMappingURL=AevmCodec.js.map
