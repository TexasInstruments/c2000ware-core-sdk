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
 *
*/
import { EventType, Events } from '../../../gc-core-assets/lib/Events';
export const connectionLogEventType = new EventType('ConnectionLog');
export function capitalize(text) {
    return text.charAt(0).toUpperCase() + text.slice(1);
}
export class AbstractConnectionLogger extends Events {
    constructor() {
        super(...arguments);
        this.lastLog = {
            message: '',
            type: 'info'
        };
    }
    addProgressMessage(message, tooltip) {
        if (this.lastLog.type === 'info') {
            this.lastLog.message = message;
            this.lastLog.tooltip = tooltip;
        }
        this.console.info(message);
        this.fireLoggingMessage('info', message);
    }
    addErrorMessage(message, tooltip) {
        this.lastLog.message = 'Error: ' + message;
        this.lastLog.tooltip = tooltip;
        this.lastLog.type = 'error';
        this.console.error(message);
        this.fireLoggingMessage('error', message);
    }
    addWarningMessage(message, tooltip) {
        if (this.lastLog.type !== 'error') {
            this.lastLog.message = 'Warning: ' + message;
            this.lastLog.tooltip = tooltip;
            this.lastLog.type = 'warning';
        }
        this.console.warning(message);
        this.fireLoggingMessage('warning', message);
    }
    addDebugMessage(message) {
        this.console.log(message);
        this.fireLoggingMessage('debug', message);
    }
    fireLoggingMessage(type, message) {
        if (message) {
            this.fireEvent(connectionLogEventType, { type: type, message: capitalize(message), transportId: this.id });
        }
    }
    clearProgressMessage() {
        this.lastLog = {
            message: '',
            type: 'info'
        };
    }
    get progressMessage() {
        return this.lastLog.message.split('\n')[0];
    }
    get tooltipMessage() {
        return this.lastLog.tooltip || this.lastLog.message.split('\n').slice(1).join('\n');
    }
    get hasErrors() {
        return this.lastLog.type === 'error';
    }
    get hasWarnings() {
        return this.lastLog.type === 'warning';
    }
}
//# sourceMappingURL=AbstractConnectionLogger.js.map