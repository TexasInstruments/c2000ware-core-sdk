import { GcUtils } from './GcUtils';
import { GcLocalStorage } from './GcLocalStorage';

/**
 *  Copyright (c) 2019, 2024 Texas Instruments Incorporated
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
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 'AS IS'
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
let outputListener = console;
const STORAGE_NAME = 'GcConsole';
const OFF_LEVEL = -1;
const ERROR_LEVEL = 0;
const WARNING_LEVEL = 1;
const INFO_LEVEL = 2;
const LOG_LEVEL = 3;
const DEBUG_LEVEL = 4;
const ALL_LEVEL = DEBUG_LEVEL;
const getStorageItem = () => JSON.parse(GcLocalStorage.getItem(STORAGE_NAME) || '{}');
let moduleLogLevels = getStorageItem();
const getModuleLogLevel = (moduleName) => {
    for (const module in moduleLogLevels) {
        if (Object.prototype.hasOwnProperty.call(moduleLogLevels, module)) {
            if (moduleName.match(new RegExp(module))) {
                return moduleLogLevels[module];
            }
        }
    }
    if (moduleLogLevels.all) {
        return moduleLogLevels.all;
    }
    return 0;
};
const trace = (options, message, params) => {
    const { moduleName, type, level, style } = options;
    const moduleErrorLevel = getModuleLogLevel(moduleName);
    if (moduleErrorLevel === OFF_LEVEL) {
        return;
    }
    if (moduleErrorLevel >= level) {
        const msg = '[' + moduleName + '] ' + type + ': ' + (typeof message === 'function' ? message.call(null, ...params) : message);
        if (!GcUtils.isNodeJS && typeof outputListener.groupCollapsed !== 'undefined' && typeof outputListener.trace !== 'undefined' && typeof outputListener.groupEnd !== 'undefined') {
            outputListener.groupCollapsed('%c' + msg, style);
            outputListener.trace('%c[' + moduleName + ' - callstack', 'font-weight: 100;');
            outputListener.groupEnd();
        }
        else {
            outputListener.log(msg);
        }
    }
};
class GcConsole {
    constructor(moduleName, instanceName) {
        this.name = `${moduleName}${instanceName ? '::' + instanceName : ''}`;
    }
    /**
     * Helper method to log an API.
     *
     * @param methodName the name of the method
     * @param params the method parameters
     */
    logAPI(methodName, ...params) {
        this.debug(() => {
            const _params = params.filter((e) => e !== undefined).map((p) => {
                if (typeof p === 'string' && p.length > 128) {
                    return `${p.substr(0, 128)}...`;
                }
                else if (Array.isArray(p)) {
                    return '[' + p.reduce((data, item, index, array) => {
                        const text = item.toString();
                        return index === 0 ? text :
                            data + ',' + ((index === array.length - 1) ? text : text);
                    }, '') + ']';
                }
                else if (typeof p === 'object') {
                    return JSON.stringify(p);
                }
                else if (typeof p === 'function') {
                    return p.name || '() => {}';
                }
                else {
                    return p.toString();
                }
            });
            return `${methodName}(${Array.prototype.slice.call(_params)})`;
        });
    }
    /**
     * Logs a `log` message to the console.
     *
     * @param {string|MessageCallback} message the message or a callback function that returns the message
     * @param {...any} params the message callback function parameters
     */
    log(message, ...params) {
        GcConsole.log(this.name, message, ...params);
    }
    /**
     * Logs an `info` message to the console.
     *
     * @param {string|MessageCallback} message the message or a callback function that returns the message
     * @param {...any} params the message callback function parameters
     */
    info(message, ...params) {
        GcConsole.info(this.name, message, ...params);
    }
    /**
     * Logs an `error` message to the console.
     *
     * @param {string|MessageCallback} message the message or a callback function that returns the message
     * @param {...any} params the message callback function parameters
     */
    error(message, ...params) {
        GcConsole.error(this.name, message, ...params);
    }
    /**
     * Log a `warning` message to the console.
     *
     * @param {string|MessageCallback} message the message or a callback function that returns the message
     * @param {...any} params the message callback function parameters
     */
    warning(message, ...params) {
        GcConsole.warning(this.name, message, ...params);
    }
    /**
     * Logs a `debug` message to the console.
     *
     * @param {string|MessageCallback} message the message or a callback function that returns the message
     * @param {...any} params the message callback function parameters
     */
    debug(message, ...params) {
        GcConsole.debug(this.name, message, ...params);
    }
    /**
     * Sets the logging level for a specific module.
     *
     * @param {string|number} level one of the supported log level, errors|warnings|info|logs|debug|off or 0-4
     */
    setLevel(level) {
        GcConsole.setLevel(`^${this.name}$`, level);
    }
    /**
     * Logs a `log` message to the console.
     *
     * @param {string} moduleName the name of the module
     * @param {string|MessageCallback} message the message or a callback function that returns the message
     * @param {...any} params the message callback function parameters
     */
    static log(moduleName, message, ...params) {
        trace({ moduleName: moduleName, style: 'font-weight: 100;', type: 'log', level: LOG_LEVEL }, message, params);
    }
    /**
     * Logs an `info` message to the console.
     *
     * @param {string} moduleName the name of the module
     * @param {string|MessageCallback} message the message or a callback function that returns the message
     * @param {...any} params the message callback function parameters
     */
    static info(moduleName, message, ...params) {
        trace({ moduleName: moduleName, style: 'font-weight: 100;', type: 'info', level: INFO_LEVEL }, message, params);
    }
    /**
     * Logs an `error` message to the console.
     *
     * @param {string} moduleName the name of the module
     * @param {string|MessageCallback} message the message or a callback function that returns the message
     * @param {...any} params the message callback function parameters
     */
    static error(moduleName, message, ...params) {
        trace({ moduleName: moduleName, style: 'color: #ff4444; font-weight: 100;', type: 'error', level: ERROR_LEVEL }, message, params);
    }
    /**
     * Logs a `warning` message to the console.
     *
     * @param {string} moduleName the name of the module
     * @param {string|MessageCallback} message the message or a callback function that returns the message
     * @param {...any} params the message callback function parameters
     */
    static warning(moduleName, message, ...params) {
        trace({ moduleName: moduleName, style: 'color: #ffbb33; font-weight: 100;', type: 'warn', level: WARNING_LEVEL }, message, params);
    }
    /**
     * Logs a `debug` message to the console.
     *
     * @param {string} moduleName the name of the module
     * @param {string|MessageCallback} message the message or a callback function that returns the message
     * @param {...any} params the message callback function parameters
     */
    static debug(moduleName, message, ...params) {
        trace({ moduleName: moduleName, style: 'color: #0099cc; font-weight: 100;', type: 'debug', level: DEBUG_LEVEL }, message, params);
    }
    /**
     * Clears all module log levels.
     */
    static clearLogLevels() {
        GcLocalStorage.removeItem(STORAGE_NAME);
        moduleLogLevels = {};
    }
    /**
     * Returns the log level for all the modules.
     *
     * @returns { Array<string> } the log levels
     */
    static getLevels() {
        const result = [];
        const item = getStorageItem();
        for (const [key, value] of Object.entries(item)) {
            let tmp = key + '=' + value;
            switch (value) {
                case OFF_LEVEL:
                    tmp += ' (off)';
                    break;
                case ERROR_LEVEL:
                    tmp += ' (errors)';
                    break;
                case WARNING_LEVEL:
                    tmp += ' (warnings)';
                    break;
                case INFO_LEVEL:
                    tmp += ' (warnings and info)';
                    break;
                case LOG_LEVEL:
                    tmp += ' (warnings, info, and logs)';
                    break;
                case DEBUG_LEVEL:
                    tmp += ' (all logs, including debug)';
                    break;
            }
            result.push(tmp);
        }
        return result;
    }
    /**
     * Sets the logging level for a specific module.
     *
     * @param {string} moduleName the module name (can be regex) to enable logging, `all` to enable for all modules.
     * @param {string|number} level one of the supported log level, errors|warnings|info|log|debug|off or -1 to 4
     */
    static setLevel(moduleName, level) {
        let val = ERROR_LEVEL; // default == 'error'
        if (typeof level === 'number') {
            val = Math.max(-1, Math.min(4, level));
        }
        else {
            switch (level) {
                case 'off':
                    val = OFF_LEVEL;
                    break;
                case 'warning':
                    val = WARNING_LEVEL;
                    break;
                case 'info':
                    val = INFO_LEVEL;
                    break;
                case 'log':
                    val = LOG_LEVEL;
                    break;
                case 'debug':
                    val = DEBUG_LEVEL;
                    break;
            }
        }
        if (val === ERROR_LEVEL)
            delete moduleLogLevels[moduleName];
        else
            moduleLogLevels[moduleName] = val;
        GcLocalStorage.setItem(STORAGE_NAME, JSON.stringify(moduleLogLevels));
    }
    /**
     * Sets the output listener, can be use to override the default STDOUT behavior.
     *
     * @param listener the listener
     */
    static setOutputListener(listener) {
        outputListener = listener || console;
    }
    /**
     * Prints the help text in the console.
     */
    static help() {
        outputListener.log('Help for GcConsole:\n' +
            '  - To see logs for a particular module, set a logging level for that module name (e.g. gc.console.setLevel("gc-core-databind.*", 4)).\n' +
            '  - To see logs for a particular module instance, set a logging level for that module name with instance (e.g. gc.console.setLevel("gc-core-databind::instance", 4)).\n' +
            '  - To see logs for all modules, use a module name of "all" (e.g. gc.console.setLevel("all", 4) ).\n' +
            '  - To see the location that logged the message, click on the triangle to the left of the message to expand the stack trace.\n\n' +
            'Colors: Red: error, Yellow: warning, Black: info or log, Blue: debug.\n\n' +
            'Commands: the following function calls can be called from the browser dev tools console window command line:\n' +
            'gc.console.setLevel(moduleName, value)\n' +
            '  - moduleName: sets a logging level for the specified module name, can be regular expression. Use "all" for all modules.\n' +
            '  - value: 0 = errors only, 1 = errors and warnings, 2 = errors, warnings, and info, 3 = errors, warnings, info, and logs, 4 = all\n' +
            'gc.console.getLevels()\n' +
            '  - returns a list of all currently active module with logging enabled and its levels.\n');
    }
}
if (!GcUtils.isCCS && !GcUtils.isNodeJS) {
    outputListener.log('Enter "gc.console.help() + <enter>" to see help info for GcConsole logging.');
}
if (typeof window !== 'undefined') {
    window.gc = window.gc || {};
    window.gc.console = window.gc.console || GcConsole;
}

export { ALL_LEVEL, DEBUG_LEVEL, ERROR_LEVEL, GcConsole, INFO_LEVEL, LOG_LEVEL, OFF_LEVEL, WARNING_LEVEL };
//# sourceMappingURL=GcConsole.js.map
