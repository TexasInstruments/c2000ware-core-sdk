import { GcConsole } from '../../gc-core-assets/lib/GcConsole';
import { streamingCodecDataType } from '../../gc-model-streaming/lib/StreamingDataModel';
import { AbstractDataCodec, bufferOrStringDataType, bufferDataType } from '../../gc-target-configuration/lib/TargetConfiguration';

/**
 *  Copyright (c) 2021, 2022 Texas Instruments Incorporated
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
/* eslint-disable @typescript-eslint/no-loss-of-precision */
/**
 * The original javascript implementation of serialzie and desrialzie of MessagePack
 * is from https://github.com/ygoe/msgpack.js
 *
 * Copyright (c) 2019, Yves Goergen, https://unclassified.software/source/msgpack-js
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
 * NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
const pow32 = 0x100000000; // 2^32
const errorNotEnoughData = Error('Not enough data');
/**
 * MessagePack serializer for encoding data in message pack format.
 * For example, new MsgPackSerializer().serialize(data);
 */
class MsgPackSerializer {
    constructor() {
        this.actualLength = 0;
        this.array = new Uint8Array(128);
        this.options = {};
    }
    /**
     * Serialize (aka encode) data
     * @param data data to be encoded
     * @param options control how encoding works.
     * @returns encoded data
     */
    serialize(data, options) {
        this.options = options ?? {};
        this.append(data);
        return this.array.subarray(0, this.actualLength);
    }
    append(data) {
        switch (typeof data) {
            case 'undefined':
                this.appendNull();
                break;
            case 'boolean':
                this.appendBoolean(data);
                break;
            case 'number':
                this.appendNumber(data);
                break;
            case 'string':
                this.appendString(data);
                break;
            case 'object':
                if (data === null) {
                    this.appendNull();
                }
                else if (data instanceof Date) {
                    this.appendDate(data);
                }
                else if (Array.isArray(data)) {
                    this.appendArray(data);
                }
                else if (data instanceof Uint8Array || data instanceof Uint8ClampedArray) {
                    this.appendBinArray(data);
                }
                else if (data instanceof Int8Array || data instanceof Int16Array || data instanceof Uint16Array ||
                    data instanceof Int32Array || data instanceof Uint32Array ||
                    data instanceof Float32Array || data instanceof Float64Array) {
                    this.appendArray(data);
                }
                else {
                    this.appendObject(data);
                }
                break;
        }
    }
    appendNull() {
        this.appendByte(0xc0);
    }
    appendBoolean(data) {
        this.appendByte(data ? 0xc3 : 0xc2);
    }
    appendNumber(data) {
        if (isFinite(data) && Math.floor(data) === data) {
            const bits = +(this.options.encodeIntegerBitSize ?? 0);
            // Integer
            if (bits === 32) {
                if (data >= 0) { // uint32
                    this.appendBytes([0xce, data >>> 24, data >>> 16, data >>> 8, data]);
                }
                else { // int32
                    this.appendBytes([0xd2, data >>> 24, data >>> 16, data >>> 8, data]);
                }
            }
            else if (bits === 16) {
                if (data >= 0) { // uint16
                    this.appendBytes([0xcd, data >>> 8, data]);
                }
                else { // int16
                    this.appendBytes([0xd1, data >>> 8, data]);
                }
            }
            else if (bits === 8) {
                if (data >= 0) { // uint8
                    this.appendBytes([0xcc, data]);
                }
                else { // int8
                    this.appendBytes([0xd0, data]);
                }
            }
            else if (data >= 0 && data <= 0x7f) {
                this.appendByte(data);
            }
            else if (data < 0 && data >= -0x20) {
                this.appendByte(data);
            }
            else if (data > 0 && data <= 0xff) { // uint8
                this.appendBytes([0xcc, data]);
            }
            else if (data >= -0x80 && data <= 0x7f) { // int8
                this.appendBytes([0xd0, data]);
            }
            else if (data > 0 && data <= 0xffff) { // uint16
                this.appendBytes([0xcd, data >>> 8, data]);
            }
            else if (data >= -0x8000 && data <= 0x7fff) { // int16
                this.appendBytes([0xd1, data >>> 8, data]);
            }
            else if (data > 0 && data <= 0xffffffff) { // uint32
                this.appendBytes([0xce, data >>> 24, data >>> 16, data >>> 8, data]);
            }
            else if (data >= -0x80000000 && data <= 0x7fffffff) { // int32
                this.appendBytes([0xd2, data >>> 24, data >>> 16, data >>> 8, data]);
            }
            else if (data > 0 && data <= 0xffffffffffffffff) { // uint64
                // Split 64 bit number into two 32 bit numbers because JavaScript only regards
                // 32 bits for bitwise operations.
                const hi = data / pow32;
                const lo = data % pow32;
                this.appendBytes([0xd3, hi >>> 24, hi >>> 16, hi >>> 8, hi, lo >>> 24, lo >>> 16, lo >>> 8, lo]);
            }
            else if (data >= -0x8000000000000000 && data <= 0x7fffffffffffffff) { // int64
                this.appendByte(0xd3);
                this.appendInt64(data);
            }
            else if (data < 0) { // below int64
                this.appendBytes([0xd3, 0x80, 0, 0, 0, 0, 0, 0, 0]);
            }
            else { // above uint64
                this.appendBytes([0xcf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff]);
            }
        }
        else {
            // Float
            if (this.floatView === undefined) {
                this.floatView = new DataView(new ArrayBuffer(8));
            }
            this.floatView.setFloat64(0, data);
            this.appendByte(0xcb);
            this.appendBytes(new Uint8Array(this.floatView.buffer));
        }
    }
    appendString(data) {
        const bytes = this.encodeString(data);
        const len = bytes.length;
        if (len <= 0x1f) {
            this.appendByte(0xa0 + len);
        }
        else if (len <= 0xff) {
            this.appendBytes([0xd9, len]);
        }
        else if (len <= 0xffff) {
            this.appendBytes([0xda, len >>> 8, len]);
        }
        else {
            this.appendBytes([0xdb, len >>> 24, len >>> 16, len >>> 8, len]);
        }
        this.appendBytes(bytes);
    }
    appendArray(data) {
        const len = data.length;
        if (len <= 0xf) {
            this.appendByte(0x90 + len);
        }
        else if (len <= 0xffff) {
            this.appendBytes([0xdc, len >>> 8, len]);
        }
        else {
            this.appendBytes([0xdd, len >>> 24, len >>> 16, len >>> 8, len]);
        }
        for (let index = 0; index < len; index++) {
            this.append(data[index]);
        }
    }
    appendBinArray(data) {
        const len = data.length;
        if (len <= 0xf) {
            this.appendBytes([0xc4, len]);
        }
        else if (len <= 0xffff) {
            this.appendBytes([0xc5, len >>> 8, len]);
        }
        else {
            this.appendBytes([0xc6, len >>> 24, len >>> 16, len >>> 8, len]);
        }
        this.appendBytes(data);
    }
    appendObject(data) {
        let len = 0;
        for (const key in data)
            len++;
        if (len <= 0xf) {
            this.appendByte(0x80 + len);
        }
        else if (len <= 0xffff) {
            this.appendBytes([0xde, len >>> 8, len]);
        }
        else {
            this.appendBytes([0xdf, len >>> 24, len >>> 16, len >>> 8, len]);
        }
        for (const key in data) {
            this.append(key);
            this.append(data[key]);
        }
    }
    appendDate(data) {
        const sec = data.getTime() / 1000;
        if (data.getMilliseconds() === 0 && sec >= 0 && sec < 0x100000000) { // 32 bit seconds
            this.appendBytes([0xd6, 0xff, sec >>> 24, sec >>> 16, sec >>> 8, sec]);
        }
        else if (sec >= 0 && sec < 0x400000000) { // 30 bit nanoseconds, 34 bit seconds
            const ns = data.getMilliseconds() * 1000000;
            this.appendBytes([0xd7, 0xff, ns >>> 22, ns >>> 14, ns >>> 6, ((ns << 2) >>> 0) | (sec / pow32), sec >>> 24, sec >>> 16, sec >>> 8, sec]);
        }
        else { // 32 bit nanoseconds, 64 bit seconds, negative values allowed
            const ns = data.getMilliseconds() * 1000000;
            this.appendBytes([0xc7, 12, 0xff, ns >>> 24, ns >>> 16, ns >>> 8, ns]);
            this.appendInt64(sec);
        }
    }
    appendByte(byte) {
        if (this.array.length < this.actualLength + 1) {
            this.growArray(1);
        }
        this.array[this.actualLength] = byte;
        this.actualLength++;
    }
    appendBytes(bytes) {
        if (this.array.length < this.actualLength + bytes.length) {
            this.growArray(bytes.length);
        }
        this.array.set(bytes, this.actualLength);
        this.actualLength += bytes.length;
    }
    growArray(addLen) {
        let newLength = this.array.length * 2;
        while (newLength < this.actualLength + addLen) {
            newLength *= 2;
        }
        const newArray = new Uint8Array(newLength);
        newArray.set(this.array);
        this.array = newArray;
    }
    appendInt64(value) {
        // Split 64 bit number into two 32 bit numbers because JavaScript only regards 32 bits for
        // bitwise operations.
        let hi, lo;
        if (value >= 0) {
            // Same as uint64
            hi = value / pow32;
            lo = value % pow32;
        }
        else {
            // Split absolute value to high and low, then NOT and ADD(1) to restore negativity
            value++;
            hi = Math.abs(value) / pow32;
            lo = Math.abs(value) % pow32;
            hi = ~hi;
            lo = ~lo;
        }
        this.appendBytes([hi >>> 24, hi >>> 16, hi >>> 8, hi, lo >>> 24, lo >>> 16, lo >>> 8, lo]);
    }
    encodeString(str) {
        let ascii = true;
        const length = str.length;
        for (let x = 0; x < length; x++) {
            if (str.charCodeAt(x) > 127) {
                ascii = false;
                break;
            }
        }
        let i = 0;
        const bytes = new Uint8Array(str.length * (ascii ? 1 : 4));
        for (let ci = 0; ci !== length; ci++) {
            let c = str.charCodeAt(ci);
            if (c < 128) {
                bytes[i++] = c;
                continue;
            }
            if (c < 2048) {
                bytes[i++] = c >> 6 | 192;
            }
            else {
                if (c > 0xd7ff && c < 0xdc00) {
                    if (++ci >= length)
                        throw new Error('encode string incomplete surrogate pair');
                    const c2 = str.charCodeAt(ci);
                    if (c2 < 0xdc00 || c2 > 0xdfff)
                        throw new Error(`encode string second surrogate character at index ${ci} out of range`);
                    c = 0x10000 + ((c & 0x03ff) << 10) + (c2 & 0x03ff);
                    bytes[i++] = c >> 18 | 240;
                    bytes[i++] = c >> 12 & 63 | 128;
                }
                else {
                    bytes[i++] = c >> 12 | 224;
                }
                bytes[i++] = c >> 6 & 63 | 128;
            }
            bytes[i++] = c & 63 | 128;
        }
        return ascii ? bytes : bytes.subarray(0, i);
    }
}
/**
 * MessagePack deserializer for decoding data in message pack format.
 * For example, new MsgPackDeserializer(array).deserialize();
 */
class MsgPackDeserializer {
    constructor(array) {
        this.pos = 0;
        this.array = array instanceof Uint8Array ? array : new Uint8Array(array);
    }
    /**
     * Deserialize (aka decode) data
     * @param array data to be decoded
     * @param startIndex optional start index of data to be decoded, default to 0.
     * @returns decoded data and next start index
     */
    deserialize(startIndex) {
        this.pos = startIndex ?? 0;
        const data = this.read();
        return { data, nextIndex: this.pos };
    }
    read() {
        this.hasData(this.array, this.pos, 1);
        const byte = this.array[this.pos++];
        if (byte >= 0x00 && byte <= 0x7f)
            return byte; // positive fixint
        if (byte >= 0x80 && byte <= 0x8f)
            return this.readMap(byte - 0x80, 0); // fixmap
        if (byte >= 0x90 && byte <= 0x9f)
            return this.readArray(byte - 0x90, 0); // fixarray
        if (byte >= 0xa0 && byte <= 0xbf)
            return this.readStr(byte - 0xa0, 0); // fixstr
        if (byte === 0xc0)
            return null; // nil
        if (byte === 0xc1)
            throw Error('Invalid byte code 0xc1 found'); // never used
        if (byte === 0xc2)
            return false; // false
        if (byte === 0xc3)
            return true; // true
        if (byte === 0xc4)
            return this.readBin(-1, 1); // bin 8
        if (byte === 0xc5)
            return this.readBin(-1, 2); // bin 16
        if (byte === 0xc6)
            return this.readBin(-1, 4); // bin 32
        if (byte === 0xc7)
            return this.readExt(-1, 1); // ext 8
        if (byte === 0xc8)
            return this.readExt(-1, 2); // ext 16
        if (byte === 0xc9)
            return this.readExt(-1, 4); // ext 32
        if (byte === 0xca)
            return this.readFloat(4); // float 32
        if (byte === 0xcb)
            return this.readFloat(8); // float 64
        if (byte === 0xcc)
            return this.readUInt(1); // uint 8
        if (byte === 0xcd)
            return this.readUInt(2); // uint 16
        if (byte === 0xce)
            return this.readUInt(4); // uint 32
        if (byte === 0xcf)
            return this.readUInt(8); // uint 64
        if (byte === 0xd0)
            return this.readInt(1); // int 8
        if (byte === 0xd1)
            return this.readInt(2); // int 16
        if (byte === 0xd2)
            return this.readInt(4); // int 32
        if (byte === 0xd3)
            return this.readInt(8); // int 64
        if (byte === 0xd4)
            return this.readExt(1, 0); // fixext 1
        if (byte === 0xd5)
            return this.readExt(2, 0); // fixext 2
        if (byte === 0xd6)
            return this.readExt(4, 0); // fixext 4
        if (byte === 0xd7)
            return this.readExt(8, 0); // fixext 8
        if (byte === 0xd8)
            return this.readExt(16, 0); // fixext 16
        if (byte === 0xd9)
            return this.readStr(-1, 1); // str 8
        if (byte === 0xda)
            return this.readStr(-1, 2); // str 16
        if (byte === 0xdb)
            return this.readStr(-1, 4); // str 32
        if (byte === 0xdc)
            return this.readArray(-1, 2); // array 16
        if (byte === 0xdd)
            return this.readArray(-1, 4); // array 32
        if (byte === 0xde)
            return this.readMap(-1, 2); // map 16
        if (byte === 0xdf)
            return this.readMap(-1, 4); // map 32
        if (byte >= 0xe0 && byte <= 0xff)
            return byte - 256; // negative fixint
    }
    hasData(ary, testPos, testSize) {
        if (testPos + testSize > ary.length)
            throw errorNotEnoughData;
        return true;
    }
    readInt(size) {
        this.hasData(this.array, this.pos, size);
        let value = 0;
        let first = true;
        while (size-- > 0) {
            if (first) {
                const byte = this.array[this.pos++];
                value += byte & 0x7f;
                if (byte & 0x80) {
                    value -= 0x80; // Treat most-significant bit as -2^i instead of 2^i
                }
                first = false;
            }
            else {
                value *= 256;
                value += this.array[this.pos++];
            }
        }
        return value;
    }
    readUInt(size) {
        this.hasData(this.array, this.pos, size);
        let value = 0;
        while (size-- > 0) {
            value *= 256;
            value += this.array[this.pos++];
        }
        return value;
    }
    readFloat(size) {
        this.hasData(this.array, this.pos, size);
        const view = new DataView(this.array.buffer, this.pos + this.array.byteOffset, size);
        this.pos += size;
        if (size === 4)
            return view.getFloat32(0, false);
        if (size === 8)
            return view.getFloat64(0, false);
    }
    readBin(size, lengthSize) {
        if (size < 0)
            size = this.readUInt(lengthSize);
        this.hasData(this.array, this.pos, size);
        const data = this.array.subarray(this.pos, this.pos + size);
        this.pos += size;
        return data;
    }
    readMap(size, lengthSize) {
        if (size < 0)
            size = this.readUInt(lengthSize);
        const data = {};
        while (size-- > 0) {
            const key = this.read();
            data[key] = this.read();
        }
        return data;
    }
    readArray(size, lengthSize) {
        if (size < 0)
            size = this.readUInt(lengthSize);
        const data = [];
        while (size-- > 0) {
            data.push(this.read());
        }
        return data;
    }
    readStr(size, lengthSize) {
        if (size < 0)
            size = this.readUInt(lengthSize);
        this.hasData(this.array, this.pos, size);
        const start = this.pos;
        this.pos += size;
        return this.decodeString(this.array, start, size);
    }
    readExt(size, lengthSize) {
        if (size < 0)
            size = this.readUInt(lengthSize);
        const type = this.readUInt(1);
        const data = this.readBin(size, 0);
        switch (type) {
            case 255:
                return this.readExtDate(data);
        }
        return { type: type, data: data };
    }
    readExtDate(data) {
        if (data.length === 4) {
            const sec = ((data[0] << 24) >>> 0) +
                ((data[1] << 16) >>> 0) +
                ((data[2] << 8) >>> 0) +
                data[3];
            return new Date(sec * 1000);
        }
        if (data.length === 8) {
            const ns = ((data[0] << 22) >>> 0) +
                ((data[1] << 14) >>> 0) +
                ((data[2] << 6) >>> 0) +
                (data[3] >>> 2);
            const sec = ((data[3] & 0x3) * pow32) +
                ((data[4] << 24) >>> 0) +
                ((data[5] << 16) >>> 0) +
                ((data[6] << 8) >>> 0) +
                data[7];
            return new Date(sec * 1000 + ns / 1000000);
        }
        if (data.length === 12) {
            const ns = ((data[0] << 24) >>> 0) +
                ((data[1] << 16) >>> 0) +
                ((data[2] << 8) >>> 0) +
                data[3];
            this.pos -= 8;
            const sec = this.readInt(8);
            return new Date(sec * 1000 + ns / 1000000);
        }
        throw Error('Invalid data length for a date value.');
    }
    decodeString(bytes, start, length) {
        let i = start;
        let str = '';
        length += start;
        while (i < length) {
            let c = bytes[i++];
            if (c > 127) {
                if (c > 191 && c < 224) {
                    if (i >= length)
                        throw new Error('decode string incomplete 2-byte sequence');
                    c = (c & 31) << 6 | bytes[i++] & 63;
                }
                else if (c > 223 && c < 240) {
                    if (i + 1 >= length)
                        throw new Error('decode string incomplete 3-byte sequence');
                    c = (c & 15) << 12 | (bytes[i++] & 63) << 6 | bytes[i++] & 63;
                }
                else if (c > 239 && c < 248) {
                    if (i + 2 >= length)
                        throw new Error('decode string incomplete 4-byte sequence');
                    c = (c & 7) << 18 | (bytes[i++] & 63) << 12 | (bytes[i++] & 63) << 6 | bytes[i++] & 63;
                }
                else {
                    throw new Error(`decode string unknown multibyte start at index ${(i - 1)}`);
                }
            }
            if (c <= 0xffff) {
                str += String.fromCharCode(c);
            }
            else if (c <= 0x10ffff) {
                c -= 0x10000;
                str += String.fromCharCode(c >> 10 | 0xd800);
                str += String.fromCharCode(c & 0x3FF | 0xdc00);
            }
        }
        return str;
    }
}

/**
 *  Copyright (c) 2021, 2024 Texas Instruments Incorporated
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
class MessagePackCodec extends AbstractDataCodec {
    constructor(params) {
        super(params.id || 'messagePackCodec', bufferOrStringDataType, bufferDataType, streamingCodecDataType, streamingCodecDataType);
        this.params = params;
        this.partialData = [];
        // In normal case, the partial data grows when not receiving a complete packet,
        // and shrinks when a complete packet is received and decoded.
        // If the partial data ever grows, the app will crash, and it is better
        // to log this warning. The lastPartialDataWarningSize is set to a high mark (400K),
        // and is doubled after each warning to avoid flood of warnings.
        this.lastPartialDataWarningSize = 400000;
        this.console = new GcConsole('gc-codec-message-pack', this.params.id);
    }
    encode(data) {
        const encodedData = new MsgPackSerializer().serialize(data, this.params);
        // encodedData is Uint8Array, need to change it to number[] for going through cloudagent ws
        // because it uses JSON.stringify(...) on one side and JSON.parse(...) on the other side.
        this.targetEncoder.encode(Array.from(encodedData));
    }
    decode(dataToDecode) {
        const time1 = performance.now();
        let data = []; // type checking needs this explicit type for assigning dataToDecode to data
        if (typeof dataToDecode === 'string') {
            for (let idx = 0; idx < dataToDecode.length; idx++) {
                data.push(dataToDecode.charCodeAt(idx));
            }
        }
        else {
            data = dataToDecode;
        }
        this.partialData = this.partialData.concat(...data);
        let posHint = 0;
        const mpd = new MsgPackDeserializer(this.partialData);
        let deserializeCount = 0;
        let targetDecoderDecodeCount = 0;
        while (posHint < this.partialData.length) {
            try {
                deserializeCount++;
                const decodedResult = mpd.deserialize(posHint);
                posHint = decodedResult.nextIndex;
                if (decodedResult !== undefined) {
                    targetDecoderDecodeCount++;
                    this.targetDecoder.decode(decodedResult.data);
                }
            }
            catch (error) {
                if (error === errorNotEnoughData) {
                    // Wait for next cycle to get more data
                    break;
                }
                else {
                    posHint++;
                }
            }
        }
        if (posHint > 0) {
            this.partialData = this.partialData.slice(posHint);
        }
        else if (posHint === 0 && this.partialData.length > this.lastPartialDataWarningSize) {
            // posHint 0 indicates the so-far partial data is not decodable due to incomplete packet.
            // If partialData.length is really big at the same time and keeps growing, it could be
            // the received data does not conform to messagePacket protocol.
            this.console.warning('Received data but cannot decode it. Please check the content of data.');
            this.lastPartialDataWarningSize = 2 * this.lastPartialDataWarningSize;
        }
        const time2 = performance.now();
        this.console.debug(`decode time ${time2 - time1} ms, deserializeCount ${deserializeCount}, targetDecoderDecodeCount ${targetDecoderDecodeCount}`);
        return true;
    }
}

export { MessagePackCodec };
//# sourceMappingURL=MessagePackCodec.js.map
