/**
 *  Copyright (c) 2020, 2023 Texas Instruments Incorporated
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
/**
 * `NamedDataRecord` is a helper class for manipulating binary data as records with fields of
 * various types.  This is helpful when writing codecs that communicate using binary packet data
 * that with binary data fields like checksum, length and payload.  The NamedDataRecord allows you to define the
 * fields, the size of each fields, and it gives access to them as if it were a c struct.
 *
 * @packageDocumentation
 */
/**
 * Numeric integer field enumerated types for 32, 16, and 8-bit, signed and unsigned integer field types
 */
var NamedRecordFieldDataType;
(function (NamedRecordFieldDataType) {
    NamedRecordFieldDataType[NamedRecordFieldDataType["Int32"] = -4] = "Int32";
    NamedRecordFieldDataType[NamedRecordFieldDataType["Int16"] = -2] = "Int16";
    NamedRecordFieldDataType[NamedRecordFieldDataType["Int8"] = -1] = "Int8";
    NamedRecordFieldDataType[NamedRecordFieldDataType["Uint8"] = 1] = "Uint8";
    NamedRecordFieldDataType[NamedRecordFieldDataType["Uint16"] = 2] = "Uint16";
    NamedRecordFieldDataType[NamedRecordFieldDataType["Uint32"] = 4] = "Uint32";
    NamedRecordFieldDataType[NamedRecordFieldDataType["Float32"] = 32] = "Float32";
    NamedRecordFieldDataType[NamedRecordFieldDataType["Float64"] = 64] = "Float64";
})(NamedRecordFieldDataType || (NamedRecordFieldDataType = {}));
/**
 * 32-bit signed integer field type
 */
const Int32 = NamedRecordFieldDataType.Int32;
/**
 * 16-bit signed integer field type
 */
const Int16 = NamedRecordFieldDataType.Int16;
/**
 * 8-bit signed integer field type
 */
const Int8 = NamedRecordFieldDataType.Int8;
/**
 * 32-bit unsigned integer field type
 */
const Uint32 = NamedRecordFieldDataType.Uint32;
/**
 * 16-bit unsigned integer field type
 */
const Uint16 = NamedRecordFieldDataType.Uint16;
/**
 * 8-bit unsigned integer field type
 */
const Uint8 = NamedRecordFieldDataType.Uint8;
/**
 * 32-bit IEEE floating point type
 */
const Float32 = NamedRecordFieldDataType.Float32;
/**
 * 64-bit IEEE floating point type
 */
const Float64 = NamedRecordFieldDataType.Float64;
/**
 * Zero, or null terminated UTF-8 encoded string field type.  Each instance of this class
 * defines a string field with a specific buffer size.
 */
class Utf8cString {
    /**
     * Create a field definition to hold a zero, or null terminated UTF-8 encoded string with a given maximum buffer size.
     * This size must be one larger than the longest string to make room for the zero, or null terminator character.
     *
     * @param size size of the buffer allocated to hold the string including the zero, or null terminator.
     */
    constructor(size) {
        this.size = size;
        if (size <= 1) {
            throw new Error('Programmer Error: Utf8cString must have a size greater than 1');
        }
    }
}
/**
 * A Union declaration for overlapping fields.  This class allows you to define multiple fields that are all
 * overlapped in one memory region within the data record.  This is similar to a union in c structs.
 *
 * @typeParam T interface defining all the member fields in the union.
 *
 * ### Usage
 * ```typescript
 * interface IMyRecord {
 *     startByte: number;
 *     data: number;
 *     dataLowWord: number;
 *     dataLowByte: number;
 *     dataHighWord: number;
 *     dataHightByte: number;
 * }
 * class MyRecord extends NamedDataRecord<IMyRecord> {
 *     static fieldDescriptors:  NamedRecordFieldDescriptor<IMyRecord>[] = [
 *         ['startByte', Int8],
 *         new Union([
 *             ['data', Uint32]
 *         ], [
 *             ['dataHighWord, Uint16],  // big endian
 *             ['dataLowWord, Uint16]
 *         ], [
 *             ['dataHighByte, Uint8],
 *             ['padding', Uint8, 2],  // two bytes of padding
 *             ['dataLowByte, Uint8]
 *         ])
 *     ]
 * }
 * const r = MyRecord.create();
 * r.data = 0xBABEFACE;
 * assert(r.dataLowByte === 0xCE);
 * assert(r.dataLowWord === 0xFACE);
 * ```
*/
class Union {
    /**
     * Create a Union from two or more **{@link NamedRecordFieldDescriptor}** arrays.  Each field descriptor list
     * will be overlapped in the same space within this union.  The size of the union will
     * be calculated using the largest **{@link NamedRecordFieldDescriptor}** array specified, and will take up
     * space within the record.
     *
     * @param fieldDescriptors two or more field descriptor arrays to overlap within this Union.
     */
    constructor(...fieldDescriptors) {
        this.unionDescriptors = fieldDescriptors;
        // eslint-disable-next-line @typescript-eslint/no-use-before-define
        this.size = this.unionDescriptors.reduce((result, descriptors) => Math.max(result, sizeOf(descriptors)), 0);
    }
}
class ExtendedFactoryImpl {
    constructor(parent, base, basePadding = 0) {
        this.parent = parent;
        this.base = base;
        this.basePadding = basePadding;
    }
    getSize() {
        return this.parent.getSize() + this.base.getSize() + this.basePadding;
    }
    extends(base) {
        const baseSize = this.basePadding + this.base.getSize();
        return new ExtendedFactoryImpl(this, base, baseSize);
    }
    create(buffer, basePadding = 0) {
        const baseSize = basePadding + this.base.getSize();
        const result = this.parent.create(buffer, baseSize);
        result.defineFields(baseSize, this.base.fieldDescriptors);
        return result;
    }
}
function sizeOf(fieldDescriptors) {
    return fieldDescriptors.reduce((result, fieldDescriptor) => {
        if (fieldDescriptor instanceof Union) {
            return result + fieldDescriptor.size;
        }
        const [key, type, count = 1] = fieldDescriptor;
        const size = type instanceof Utf8cString ? type.size : type >= Float32 ? type / 8 : Math.abs(type);
        return result + size * count;
    }, 0);
}
/**
 * A helper class for manipulating binary data as records with fields of
 * various types.  A `NamedDataRecord`
 * represents a fixed size chunk of data, in bytes, containing named fields.  Fields can vary in type and include
 * numeric, array, string, and unions these types.  All fields have a fixed size based on their type, thereby constraining
 * `NamedDataRecord` to a fixed size.
 *
 * @typeParam T interface defining all the member fields in this NamedDataRecord.
 *
 * ### Usage
 * ```typescript
 * // define an interface to use to access (read and write) the data.
 * interface IHeader {
 *     startByte: number;
 *     command: number;
 *     len: number;
 * };
 *
 * class Header extends NamedDataRecord<IHeader> {
 *     // optionally use littleEndian instead of the default big endian.
 *     littleEndian = true;
 *     // define the order of the fields, their type, and size.
 *     static fieldDescriptors: NamedRecordFieldDescriptor<IHeader>[] = [
 *         ['startByte', Uint8],
 *         ['command', Int16],
 *         ['len', Uint16]
 *     ];
 * };
 *
 * // create an instance of the NamedDataRecord
 * const header = Header.create();
 * header.startByte = ...
 * etc.
 * ```
*/
class NamedDataRecord {
    /**
     * Create a NamedDataRecord with the fields provided.  Although it is possible to create named records this way, it is
     * not recommended.  The preferred method is to extend this `NamedDataRecord` class, and use the static create()
     * method to create instances of your extended class.
     *
     * @param fieldDescriptors an order list of **{@link NamedRecordFieldDescriptor}** objects that define the fields in this named record.
     * @param buffer initial data to populate this named record with.  Used to decode raw data into field values.
     * @param basePadding this is intended for internal use only.  You should not specify this, but if you do it will create empty space
     * at the start of your record.
     */
    constructor(fieldDescriptors, buffer, basePadding = 0) {
        this.littleEndian = false;
        const offset = sizeOf(fieldDescriptors) + basePadding;
        buffer = buffer || new Uint8Array(offset);
        this.rawData = buffer instanceof Uint8Array ? buffer : new Uint8Array(buffer);
        if (offset !== this.rawData.length) {
            throw new Error('Programmer Error, the size of the buffer passed in the constructor of NamedDataRecord does not match the NamedRecordField descriptors.');
        }
        this.dataView = new DataView(this.rawData.buffer);
        this.defineFields(offset, fieldDescriptors);
    }
    /**
     * @hidden
     */
    defineFields(offset, fieldDescriptors) {
        for (let i = fieldDescriptors.length; i-- > 0;) {
            const descriptor = fieldDescriptors[i];
            if (descriptor instanceof Union) {
                const union = descriptor;
                offset = offset - union.size;
                union.unionDescriptors.forEach((unionDescriptor) => {
                    this.defineFields(offset + sizeOf(unionDescriptor), unionDescriptor);
                });
            }
            else {
                const [key, type, count = 1] = descriptor;
                const size = type instanceof Utf8cString ? type.size : type >= Float32 ? type / 8 : Math.abs(type);
                offset = offset - size * count;
                if (key !== 'reserved' && key !== 'padding') {
                    if (key in this) {
                        throw new Error(`Programmer Error, the field name ${key} has already been used.  Either it is a duplicate, or it is a reserved keyword`);
                    }
                    if (type instanceof Utf8cString) {
                        this.defineStringField(key, type, offset, count);
                    }
                    else if (count && count > 1) {
                        this.defineArrayField(key, type, offset, count);
                    }
                    else {
                        this.defineField(key, type, offset);
                    }
                }
            }
        }
    }
    defineField(key, size, offset) {
        switch (size) {
            case 1:
                Object.defineProperty(this, key, {
                    get: () => {
                        return this.dataView.getUint8(offset);
                    },
                    set: (value) => {
                        this.dataView.setUint8(offset, value);
                    }
                });
                break;
            case 2:
                Object.defineProperty(this, key, {
                    get: () => {
                        return this.dataView.getUint16(offset, this.littleEndian);
                    },
                    set: (value) => {
                        this.dataView.setUint16(offset, value, this.littleEndian);
                    }
                });
                break;
            case 4:
                Object.defineProperty(this, key, {
                    get: () => {
                        return this.dataView.getUint32(offset, this.littleEndian);
                    },
                    set: (value) => {
                        this.dataView.setUint32(offset, value, this.littleEndian);
                    }
                });
                break;
            case -1:
                Object.defineProperty(this, key, {
                    get: () => {
                        return this.dataView.getInt8(offset);
                    },
                    set: (value) => {
                        this.dataView.setInt8(offset, value);
                    }
                });
                break;
            case -2:
                Object.defineProperty(this, key, {
                    get: () => {
                        return this.dataView.getInt16(offset, this.littleEndian);
                    },
                    set: (value) => {
                        this.dataView.setInt16(offset, value, this.littleEndian);
                    }
                });
                break;
            case -4:
                Object.defineProperty(this, key, {
                    get: () => {
                        return this.dataView.getInt32(offset, this.littleEndian);
                    },
                    set: (value) => {
                        this.dataView.setInt32(offset, value, this.littleEndian);
                    }
                });
                break;
            case 32:
                Object.defineProperty(this, key, {
                    get: () => {
                        return this.dataView.getFloat32(offset, this.littleEndian);
                    },
                    set: (value) => {
                        this.dataView.setFloat32(offset, value, this.littleEndian);
                    }
                });
                break;
            case 64:
                Object.defineProperty(this, key, {
                    get: () => {
                        return this.dataView.getFloat64(offset, this.littleEndian);
                    },
                    set: (value) => {
                        this.dataView.setFloat64(offset, value, this.littleEndian);
                    }
                });
                break;
            default:
                throw new Error(`Programmer Error, the size for field ${key} is not supported.`);
        }
    }
    assertArrayLength(key, expected, actual) {
        if (expected !== actual) {
            throw `Programmer Error, cannot set array field ${key} of size ${expected} because the array size does not match.`;
        }
    }
    defineArrayField(key, type, offset, count) {
        const size = Math.abs(type);
        switch (type) {
            case 1:
                Object.defineProperty(this, key, {
                    get: () => {
                        return new Uint8Array(this.rawData.slice(offset, offset + count * size));
                    },
                    set: (value) => {
                        this.assertArrayLength(key, count, value.length);
                        this.rawData.set(value, offset);
                    }
                });
                break;
            case 2:
                Object.defineProperty(this, key, {
                    get: () => {
                        if (this.littleEndian) {
                            const data = this.rawData.slice(offset, offset + count * size);
                            return new Uint16Array(data.buffer);
                        }
                        const result = new Uint16Array(count * size);
                        for (let i = 0; i < count; i++) {
                            result.set([this.dataView.getUint16(offset + i * size)], i);
                        }
                        return result;
                    },
                    set: (value) => {
                        this.assertArrayLength(key, count, value.length);
                        if (this.littleEndian) {
                            this.rawData.set(value, offset);
                        }
                        else {
                            for (let i = 0; i < count; i++) {
                                this.dataView.setUint16(offset + i * size, value[i]);
                            }
                        }
                    }
                });
                break;
            case 4:
                Object.defineProperty(this, key, {
                    get: () => {
                        if (this.littleEndian) {
                            const data = this.rawData.slice(offset, offset + count * size);
                            return new Uint32Array(data.buffer);
                        }
                        const result = new Uint32Array(count * size);
                        for (let i = 0; i < count; i++) {
                            result.set([this.dataView.getUint32(offset + i * size)], i);
                        }
                        return result;
                    },
                    set: (value) => {
                        this.assertArrayLength(key, count, value.length);
                        if (this.littleEndian) {
                            this.rawData.set(value, offset);
                        }
                        else {
                            for (let i = 0; i < count; i++) {
                                this.dataView.setUint32(offset + i * size, value[i]);
                            }
                        }
                    }
                });
                break;
            case -1:
                Object.defineProperty(this, key, {
                    get: () => {
                        const data = this.rawData.slice(offset, offset + count * size);
                        return new Int8Array(data.buffer);
                    },
                    set: (value) => {
                        this.assertArrayLength(key, count, value.length);
                        this.rawData.set(value, offset);
                    }
                });
                break;
            case -2:
                Object.defineProperty(this, key, {
                    get: () => {
                        if (this.littleEndian) {
                            const data = this.rawData.slice(offset, offset + count * size);
                            return new Int16Array(data.buffer);
                        }
                        const result = new Int16Array(count * size);
                        for (let i = 0; i < count; i++) {
                            result.set([this.dataView.getInt16(offset + i * size)], i);
                        }
                        return result;
                    },
                    set: (value) => {
                        this.assertArrayLength(key, count, value.length);
                        if (this.littleEndian) {
                            this.rawData.set(value, offset);
                        }
                        else {
                            for (let i = 0; i < count; i++) {
                                this.dataView.setInt16(offset + i * size, value[i]);
                            }
                        }
                    }
                });
                break;
            case -4:
                Object.defineProperty(this, key, {
                    get: () => {
                        if (this.littleEndian) {
                            const data = this.rawData.slice(offset, offset + count * size);
                            return new Int32Array(data.buffer);
                        }
                        const result = new Int32Array(count * size);
                        for (let i = 0; i < count; i++) {
                            result.set([this.dataView.getInt32(offset + i * size)], i);
                        }
                        return result;
                    },
                    set: (value) => {
                        this.assertArrayLength(key, count, value.length);
                        if (this.littleEndian) {
                            return this.rawData.set(value, offset);
                        }
                        else {
                            for (let i = 0; i < count; i++) {
                                this.dataView.setInt32(offset + i * size, value[i]);
                            }
                        }
                    }
                });
                break;
        }
    }
    getStringFieldValue(offset, size) {
        let len = 0;
        while (len < size - 1 && this.rawData[offset + len] !== 0) {
            len++;
        }
        if (len > 0) {
            return this.utf8Decoder.decode(this.rawData.slice(offset, offset + len));
        }
        return '';
    }
    setStringFieldValue(value, offset, size, key) {
        const utf8Value = this.utf8Encoder.encode(value);
        if (!utf8Value) {
            throw new Error(`Programmer Error: Cannot convert string ${value} to a utf-8 string`);
        }
        if (utf8Value.length >= size) {
            throw new Error(`Programmer Error: Cannot set string field ${key} because of buffer overrun`);
        }
        this.rawData.set(utf8Value, offset);
        this.rawData.fill(0, offset + utf8Value.length, offset + size);
    }
    defineStringField(key, type, offset, count = 1) {
        if (!this.utf8Decoder) {
            this.utf8Decoder = new TextDecoder();
        }
        if (!this.utf8Encoder) {
            this.utf8Encoder = new TextEncoder();
        }
        if (count > 1) {
            Object.defineProperty(this, key, {
                get: () => {
                    const result = new Array(count);
                    for (let i = 0; i < count; i++) {
                        result[i] = this.getStringFieldValue(offset + i * type.size, type.size);
                    }
                    return result;
                },
                set: (value) => {
                    this.assertArrayLength(key, count, value.length);
                    for (let i = 0; i < count; i++) {
                        this.setStringFieldValue(value[i], offset + i * type.size, type.size, key);
                    }
                }
            });
        }
        else {
            Object.defineProperty(this, key, {
                get: () => this.getStringFieldValue(offset, type.size),
                set: (value) => {
                    this.setStringFieldValue(value, offset, type.size, key);
                }
            });
        }
    }
    /**
     * This provides access to the raw binary data in this named record.  Typically, this is used
     * to retrieve the raw binary data after setting specific field values.
     */
    get asUint8Array() {
        return this.rawData;
    }
    /**
     * Size of this named record in bytes.
     */
    get length() {
        return this.dataView.buffer.byteLength;
    }
    /**
     * Static method to calculate the size of this named record without having to create an instance first.
     * This method can only be called on a class derived from **{@link NamedDataRecord}** that has defined a static
     * fieldDescriptors member that describes the fields in this named record.
     *
     * @typeParam T interface for the fields defined in this class
     * @param this class with a static fieldDescription member defining the fields in this `NamedDataRecord`.
     * @return the size of this named record data in bytes..
     *
     * ### Usage
     * ```typescript
     * interface IMyFields {
     *    data: number;
     * }
     * class MyRecord extends NamedDataRecord<IMyFields> {
     *     fieldDescriptors = [
     *         ['data', Uint32]
     *     ]
     * }
     * assert(MyRecord.getSize() === 4);
     * ```
     */
    static getSize() {
        return sizeOf(this.fieldDescriptors);
    }
    /**
     * Factory method to create an instance of a particular named record.
     * This method can only be called on a class derived from **{@link NamedDataRecord}** that has defined a static
     * fieldDescriptors member that describes the fields in this named record.
     *
     * @typeParam T interface for the fields defined in this `NamedDataRecord`.
     * @param this the `NamedDataRecord` class to create an instance of.
     * @param buffer optional buffer of initial raw binary data.  If not provided, a named record is created and filled with zero values.
     * @param basePadding this is for internal use only.  It is needed for the implementation of the **{@link extends}** method.
     * @return an instance of NamedDataRecord that implements the interface T
     */
    static create(buffer, basePadding = 0) {
        return new this(this.fieldDescriptors, buffer, basePadding);
    }
    /**
     * Helper method to create a new NamedDataRecord from two or more NamedDataRecord's where one extends the other.
     * For example, you can create a NamedDataRecord to represent the header of a packet and re-use the definition
     * to create multiple NamedDataRecord's with different payloads.
     *
     * @typeParam T interface for the extended fields
     * @typeParam B interface for the base fields
     * @param this NamedDataRecord class to extend from the base NamedDataRecord class
     * @param base NamedDataRecord class
     * @return a factory instance with extends and create methods for either further extending the record, or creating an instance of.
     *
     * ### Usage
     * ```typescript
     * PacketTypeA.extends(Header).create();
     * PacketTypeB.extends(Header).create();
     * ```
     */
    static extends(base) {
        return new ExtendedFactoryImpl(this, base);
    }
}

export { Float32, Float64, Int16, Int32, Int8, NamedDataRecord, NamedRecordFieldDataType, Uint16, Uint32, Uint8, Union, Utf8cString };
//# sourceMappingURL=NamedDataRecord.js.map
