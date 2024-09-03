/**
 *  Copyright (c) 2021, Texas Instruments Incorporated
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
import { AbstractTransport, bufferOrStringDataType, bufferDataType } from '../../../gc-target-configuration/lib/TargetConfiguration';
import { usbHidPortType, dataEventType } from '../../../gc-service-usb/lib/ServiceUsb';
const HID_RESERVED = 2; // packet bytes reserved by HID
const MAX_PACKET_SIZE = 64 - HID_RESERVED; // size, in bytes, of a USB packet
export class AbstractUsbTransport extends AbstractTransport {
    constructor() {
        super(...arguments);
        this.encoderInputType = bufferOrStringDataType;
        this.encoderOutputType = bufferDataType;
        this.serialPacketDataHandler = (details) => {
            if (this.codec) {
                this.decodeDataPacket(this.codec, details.data);
            }
        };
        this.hidPacketDataHandler = (details) => {
            if (this.codec) {
                const rawData = details.data;
                const nRead = rawData[1] || 0;
                if (rawData[0] !== 0x3F) {
                    throw Error(`Invalid HID packet header.  Expected the first byte to be 0x3F instead of ${rawData[0]}`);
                }
                else if (nRead > MAX_PACKET_SIZE || nRead < 0) {
                    throw Error('Invalid HID packet.  Too much data');
                }
                else if (nRead > 0) { // ignore zero size packets.
                    this.decodeDataPacket(this.codec, rawData.slice(HID_RESERVED, nRead + HID_RESERVED));
                }
            }
        };
    }
    get id() {
        return this.params.id || 'usb';
    }
    decodeDataPacket(decoder, rawData) {
        let result;
        try {
            result = decoder.decode(rawData);
        }
        catch (e) {
            result = e;
        }
        if (result instanceof Error) {
            this.addErrorMessage(result.message);
            this.disconnect();
        }
    }
    encode(data) {
        if (this.usbPort) {
            if (this.usbPort.type === usbHidPortType) {
                // Add header to HID packets.
                const header = [0x3f, data.length];
                if (typeof data === 'string') {
                    this.usbPort.write(String.fromCharCode(...header) + data);
                }
                else {
                    this.usbPort.write([...header, ...data]);
                }
            }
            else {
                // No header for Serial packets
                this.usbPort.write(data);
            }
        }
    }
    addChildDecoder(decoder) {
        this.codec = decoder;
    }
    deconfigure() {
        this.codec = undefined;
    }
    async doOpenUsbPort(usbPort, baudRate) {
        this.rxDataHandler = usbPort.type === usbHidPortType ? this.hidPacketDataHandler : this.serialPacketDataHandler;
        this.baudRate = baudRate;
        usbPort.addEventListener(dataEventType, this.rxDataHandler);
        await usbPort.open({ baudRate: baudRate });
        this.usbPort = usbPort;
    }
    async onDisconnect(logger) {
        if (this.usbPort) {
            if (this.rxDataHandler) {
                this.usbPort.removeEventListener(dataEventType, this.rxDataHandler);
                this.rxDataHandler = undefined;
            }
            await this.usbPort.close();
            this.usbPort = undefined;
        }
    }
}
//# sourceMappingURL=AbstractUsbTransport.js.map