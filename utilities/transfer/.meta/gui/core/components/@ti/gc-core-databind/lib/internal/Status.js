/**
 *  Copyright (c) 2020, Texas Instruments Incorporated
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
 *  There are two status types - error or warning.
 *  Different types are displayed with different visual cues in the widgets.
 */
export var StatusType;
(function (StatusType) {
    /** An error status type */
    StatusType[StatusType["ERROR"] = 0] = "ERROR";
    /** A warning status type */
    StatusType[StatusType["WARNING"] = 1] = "WARNING";
    /** An informational status type */
    StatusType[StatusType["INFO"] = 2] = "INFO";
})(StatusType || (StatusType = {}));
/**
 * A factory for creating IStatus objects.
 *
 * @constructor
 * @implements gc.databind.IStatus
 */
export class Status {
    constructor(type, message, id) {
        this.type = type;
        this.message = message;
        this.id = id;
    }
    equals(status) {
        return (status && status.message === this.message && status.type === this.type && status.id === this.id) || false;
    }
    /**
     * Factory method to create an IStatus object
     *
     */
    static createStatus(type, message, id) {
        // if no error message, then return OK status for all types.
        if (message === undefined) {
            return null;
        }
        type = type || StatusType.ERROR;
        return new Status(type, message, id);
    }
    /**
     * Factory method to create an ERROR IStatus object
     *
     */
    static createErrorStatus(message, id) {
        return this.createStatus(StatusType.ERROR, message, id);
    }
    /**
     * Factory method to create a WARNING IStatus object
     *
     */
    static createWarningStatus(message, id) {
        return this.createStatus(StatusType.WARNING, message, id);
    }
}
//# sourceMappingURL=Status.js.map