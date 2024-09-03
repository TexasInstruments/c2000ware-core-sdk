const nullConverter = {
    convert: function (input) {
        return input;
    }
};
function jsonStringifyConverter(input) {
    try {
        return JSON.stringify(input);
    }
    catch (e) {
        return '' + input;
    }
}
function stringToJsonConverter(input) {
    try {
        return JSON.parse(input);
    }
    catch (e) {
        return {};
    }
}
function stringOrHexToNumberConverter(input) {
    const str = input.toLocaleLowerCase();
    if (!str.startsWith('0x') && str.endsWith('h')) {
        input = `0x${input.substring(0, input.length - 1)}`;
    }
    return +input;
}
const converters = {
    'object': {
        'string': { convert: stringToJsonConverter }
    },
    'string': {
        any: {
            convert: function (input) {
                return '' + input;
            }
        },
        'object': { convert: jsonStringifyConverter },
        'array': {
            convert: function (input) {
                return input.map(el => (typeof el === 'object' && !Array.isArray(el)) ? jsonStringifyConverter(el) : '' + el).join(',');
            }
        }
    },
    'boolean': {
        any: {
            convert: function (input) {
                return !!input;
            }
        },
        'string': {
            convert: function (input) {
                return isNaN(+input) ? input.toLowerCase().trim() === 'true' : +input !== 0;
            }
        }
    },
    'number': {
        any: {
            convert: function (input) {
                return +input;
            }
        },
        'string': { convert: stringOrHexToNumberConverter },
        'hex': { convert: stringOrHexToNumberConverter }
    },
    'array': {
        'string': {
            convert: function (input) {
                if (!input) {
                    return [];
                }
                input = input.trim();
                if (input.startsWith('{') && input.endsWith('}')) {
                    return stringToJsonConverter('[' + input + ']');
                }
                return input.split(',').map((e) => {
                    const value = e.trim();
                    return isNaN(+value) ? value : +value;
                });
            }
        },
        any: {
            convert: function (input) {
                return [input];
            }
        }
    }
};
/**
 * Singleton Class to register data converters that will be used by the DataBinder to
 * convert data between bindings of different types.
 */
export class DataConverter {
    /**
     * Method to register custom data converters to be used by the DataBinder singleton
     * to convert data between bindings of different types.
     *
     * @param converter data converter to use to convert between the srcType and destType.
     * @param srcType the type of the source that this converter is to be used on.  If not supplied, then it will
     * be the default converter for all source types if a specific one cannot be found.
     * @param destType the type of the output value from this converter.
     */
    static register(converter, destType, srcType = 'any') {
        if (destType !== null) {
            let destConverters = converters[destType];
            if (!destConverters) {
                destConverters = {};
                converters[destType] = destConverters;
            }
            destConverters[srcType] = converter;
        }
    }
    /**
     * Method to retrieve the converter for converting one source type to another destination type.
     *
     * @param srcType the type of the source that this converter is to be used on.  If not supplied, then it will
     * be the default converter for all source types if a specific one cannot be found.
     * @param destType the type of the output value from this converter.
     * @returns the converter found or undefined if not found.
     */
    static getConverter(srcType, destType) {
        let converter = nullConverter;
        const destConverters = converters[destType];
        if (destConverters !== undefined) {
            converter = destConverters[srcType || 'any'];
            if (converter === undefined) {
                converter = destConverters.any;
            }
        }
        return converter;
    }
    /**
     * Method to convert an element of data from one data type to another.
     *
     * @param data the value to convert
     * @param srcType the type of the source that this converter is to be used on.  If not supplied, then it will
     * be the default converter for all source types if a specific one cannot be found.
     * @param destType the type of the output value required from this conversion.
     * @param param optional numeric parameter to control the conversion like the precision for decimal and q values.
     * @returns the converted data or undefined if no converter found.
     */
    static convert(data, srcType, destType, param) {
        if (data === null || data === undefined) {
            return data; // null is null independent of type, so no conversion required.
        }
        srcType = srcType || typeof data;
        let converter;
        if (srcType !== destType && destType !== undefined && destType !== null) {
            converter = this.getConverter(srcType, destType);
        }
        return converter ? converter.convert(data, param) : data;
    }
}
//# sourceMappingURL=DataConverter.js.map