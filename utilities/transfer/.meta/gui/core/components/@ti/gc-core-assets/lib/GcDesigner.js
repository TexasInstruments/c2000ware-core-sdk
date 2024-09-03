import { GcUtils } from './GcUtils';

/**
 *  Copyright (c) 2021 Texas Instruments Incorporated
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
class PropertyAutoFillImpl {
    constructor(element) {
        this.handlers = new Map();
        if (GcUtils.isInDesigner) {
            // @ts-ignore
            element['designerGetPropertyAutoFillOptions'] = async (propertyName) => {
                const handler = this.handlers.get(propertyName);
                if (handler) {
                    return await handler();
                }
            };
        }
    }
    register(propertyName, handler) {
        if (this.handlers.get(propertyName)) {
            throw Error(`${propertyName} is already registered.`);
        }
        this.handlers.set(propertyName, handler);
        return this;
    }
    unregister(propertyName) {
        this.handlers.delete(propertyName);
        return this;
    }
}
/**
 * Creates a property autofill object to handle Designer property autofill callback.
 * @param element the HTML element
 */
const createPropertyAutoFill = (element) => {
    return new PropertyAutoFillImpl(element);
};

export { createPropertyAutoFill };
//# sourceMappingURL=GcDesigner.js.map
