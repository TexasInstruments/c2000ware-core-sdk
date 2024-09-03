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
import { binaryOrBufferDataType, bufferDataType } from './CodecDataTypes';
import { AbstractDataDecoder, nullDataCodec } from './AbstractCodec';
/**
 * Abstract class for a packet frame decoder.  A frame decoder is used to detect/align the start of packets
 * in a stream of data received over a transport like USB.  The derived class must implement the getPacketLength()
 * method to validate and calculate the length of each possible packet of data.  The base implementations of decode()
 * method will repeatedly call this method to test for possible packets.  Optionally, the derived class can provide
 * a start byte, which the base implementation will use to skip past packets that do not start with the exact byte
 * automatically.
 *
 * @constructor
 * @param id - identifier for this decoder
 * @param {Number} [startByte] - the first byte(s) used to identify the start of a packet header.
 */
export class AbstractFrameDecoder extends AbstractDataDecoder {
    constructor(id, ...startBytes) {
        super(id, binaryOrBufferDataType, bufferDataType);
        this.partialPacket = null;
        this.isReceivingValidPackets = false;
        this.startBytes = startBytes;
    }
    isStartOfPacket(rawData, offset) {
        const length = Math.min(rawData.length - offset, this.startBytes.length);
        for (let i = 0; i < length; i++) {
            if (rawData[i + offset] !== this.startBytes[i]) {
                return false;
            }
        }
        return true;
    }
    /**
     * Detect and align valid packet(s).  This method relies on the getPacketLength()
     * method implemented by the derived class to  perform this function.
     * This method may detect multiple packets, each aligned packet is passed to decodePacket().
     */
    detectPackets(rxData) {
        let result = this.isReceivingValidPackets;
        let data; // = rxData instanceof Buffer ? [...rxData] : rxData;
        if (this.partialPacket) {
            // concatenate new data with saved partial data
            data = this.partialPacket.concat(...rxData);
            this.partialPacket = null;
        }
        else {
            data = [...rxData];
        }
        let i = 0;
        const length = data.length;
        // process one or more packets (whether valid or not).
        while (i < length) {
            // skip till first delimiter(s), if provided.
            while (i < length && !this.isStartOfPacket(data, i)) {
                i++;
                this.isReceivingValidPackets = false;
            }
            if (i < length) {
                // calculate the length of the packet, zero if not enough data to determine, and -1 for error packets
                const packetLength = this.getPacketLength(data, i);
                if (packetLength > 0 && packetLength + i <= length) {
                    // enough data to decode a packet.
                    result = this.decodePacket((i === 0 && length === packetLength) ? data : data.slice(i, i + packetLength));
                    this.isReceivingValidPackets = result === true;
                    if (this.isReceivingValidPackets) {
                        // valid packet processed, skip forward
                        i += packetLength;
                    }
                    else {
                        // invalid packet decoded, skip forward only by one byte to search for start of valid packet.
                        i++;
                    }
                }
                else if (packetLength < 0) {
                    // invalid packet already, skip forward one or more bytes.
                    i -= packetLength;
                    this.isReceivingValidPackets = false;
                    result = new Error('Invalid packet received.');
                }
                else if (i === 0) {
                    // no data consumed, save all data for next pass.
                    this.partialPacket = data;
                    break;
                }
                else if (i < length) {
                    // not enough data remaining for a single packet, defer the partial packet until more data has arrived.
                    this.partialPacket = data.slice(i);
                    break;
                }
            }
        }
        return result;
    }
    deconfigure() {
        super.deconfigure();
        this.partialPacket = null;
        this.isReceivingValidPackets = false;
    }
    /**
     * For use cases like transport <--> frame decoder <--> a codec in v2.
     * For use cases like transport <--> a codec whose base class is AbstractFrameDecoder.
     * the codec can override decodePacket.
     */
    decode(rxData) {
        return this.detectPackets(rxData);
    }
}
/**
 * Abstract class for a data codec using a packet frame decoder.  This is a helper base class to make it easier to implement
 * a data codec with a frame decoder.  @See {@link AbstractFrameDecoder} for more information on the requirements of the
 * frame decoder.
 *
 * @constructor
 * @param id - identifier for this data codec
 * @param encoderInputType - the input type for encoding data going to the target.
 * @param {Number} [startByte] - the first byte(s) used to identify the start of a packet header.
 */
export class AbstractDataCodecWithFrameDecoder extends AbstractFrameDecoder {
    constructor(id, encoderInputType, ...startBytes) {
        super(id, ...startBytes);
        this.encoderInputType = encoderInputType;
        this.targetDecoder = nullDataCodec;
        this.encoderOutputType = this.encoderInputType;
    }
    addChildDecoder(child) {
        this.targetDecoder = child;
    }
}
//# sourceMappingURL=AbstractFrameDecoder.js.map