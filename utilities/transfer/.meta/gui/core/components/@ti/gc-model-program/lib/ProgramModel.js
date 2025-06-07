import { AbstractAsyncBindValue, Status, AbstractPollingDataModel, VariableBindValue, valueChangedEventType, QUALIFIER, bindingRegistry } from '../../gc-core-databind/lib/CoreDatabind';
import { DecoderType, EncoderType, codecRegistry, connectedStateChangedEventType } from '../../gc-target-configuration/lib/TargetConfiguration';
import { EventType } from '../../gc-core-assets/lib/Events';

/**
 *  Copyright (c) 2020, 2025 Texas Instruments Incorporated
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
class DSEvalBind extends AbstractAsyncBindValue {
    constructor(name, refreshIntervalProvider, parentModel) {
        super('number');
        this.name = name;
        this.parentModel = parentModel;
        this.onFailure = (err) => {
            const errMsg = err.message || err.toString();
            if (this.isConnected() && errMsg.toLowerCase().indexOf('target failed') < 0) {
                this.reportErrorStatus(errMsg);
            }
            return this.cachedValue; // don't record a new value, keep the same value as before.
        };
        this.onSuccess = (result) => {
            // clear errors on successful read
            this.reportCriticalError(null);
            return result;
        };
        this.setRefreshIntervalProvider(refreshIntervalProvider);
    }
    async writeValue() {
        if (!this.parentModel.isConnected()) {
            await this.parentModel.whenConnected();
        }
        return this.parentModel.codec?.writeValue(this.getTargetExpression(), this.cachedValue, this.parentModel.coreName).catch(this.onFailure);
    }
    async readValue() {
        if (!this.parentModel.isConnected()) {
            await this.parentModel.whenConnected();
        }
        return this.parentModel.codec?.readValue(this.getTargetExpression(), this.parentModel.coreName).then(this.onSuccess).catch(this.onFailure);
    }
    getTargetExpression() {
        let result = this.name;
        const indecies = this.getIndex();
        if (indecies) {
            for (let i = 0; i < indecies.length; i++) {
                const index = indecies[i];
                const number = +index;
                if (isNaN(number)) {
                    result += '.' + index;
                }
                else {
                    result += '[' + number + ']';
                }
            }
        }
        return result;
    }
    reportErrorStatus(dsErrorMessage) {
        let status = null;
        if (dsErrorMessage && dsErrorMessage.length > 0) {
            if (dsErrorMessage.indexOf('identifier not found') >= 0 && dsErrorMessage.indexOf(this.getTargetExpression()) >= 0) {
                dsErrorMessage = `Missing identifier: ${this.getTargetExpression()}, it cannot be found in the target program's symbols.`;
            }
            status = Status.createErrorStatus(dsErrorMessage, 'target');
        }
        this.reportCriticalError(status);
    }
    isConnected() {
        return this.parentModel.isConnected();
    }
}

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
const activeCoreChangedEventType = new EventType('activeCoreChanged');
const nullProgramModelEncoder = new (class {
    addEventListener(type, listener) {
        throw new Error('Method not implemented.');
    }
    removeEventListener(type, listener) {
        throw new Error('Method not implemented.');
    }
    async readValue() {
        throw new Error('Method not implemented.');
    }
    async writeValue() {
        throw new Error('Method not implemented.');
    }
    async initCore() {
        throw new Error('Method not implemented.');
    }
})();
const nullProgramModelDecoder = {};
const ProgramModelDecoderType = new DecoderType('pm');
const ProgramModelEncoderType = new EncoderType('GEL');
const ACTIVE_CONTEXT_NAME = '$active_context_name';
class QualifiedBindFactory {
    constructor(qualifier) {
        this.qualifier = qualifier;
    }
    create(bind) {
        if (!bind.setQualifier) {
            return null;
        }
        else {
            bind.setQualifier(this.qualifier);
            return bind;
        }
    }
}
class ProgramModel extends AbstractPollingDataModel {
    constructor(params) {
        super(params.id || 'pm', params.defaultRefreshInterval);
        this.params = params;
        this.decoderInputType = ProgramModelDecoderType;
        this.decoderOutputType = ProgramModelEncoderType;
        this.programAlreadyLoaded = false;
        this.transportStateChangeListener = (details) => {
            if (!this.initPromise && details.newState === 'connecting' && this.codec) {
                this.initPromise = this.codec.initCore(this.params, this.programAlreadyLoaded).finally(() => this.initPromise = undefined);
            }
        };
        this.activeCoreChangedListener = (details) => {
            this.modelBindings.get(ACTIVE_CONTEXT_NAME)?.setValue(details.coreName, undefined, true);
        };
        const activeDebugContext = new VariableBindValue('');
        this.modelBindings.set(ACTIVE_CONTEXT_NAME, activeDebugContext);
        activeDebugContext.addEventListener(valueChangedEventType, () => {
            // clear out critical errors on every context change
            const bindings = this.getAllBindings();
            bindings.forEach((bind) => {
                if (bind && bind.onDisconnected) {
                    bind.onDisconnected();
                }
            });
            // force a read on all bindings for the new context.
            this.refreshAllBindings();
        });
        for (const qualifier in QUALIFIER) {
            this.addQualifier(qualifier, new QualifiedBindFactory(qualifier));
        }
        bindingRegistry.registerModel(this);
        codecRegistry.register(this);
    }
    dispose() {
        super.dispose();
        codecRegistry.unregister(this);
    }
    createNewBind(uri) {
        let result = super.createNewBind(uri);
        result = result || new DSEvalBind(uri, this.defaultRefreshBinding, this);
        return result;
    }
    async invokeMethod(method, args) {
        let expression = method.trim();
        if (expression.startsWith('GEL_')) {
            expression = expression + '(' + (args ? args.join(', ') : '') + ')';
        }
        if (!this.isConnected()) {
            await this.whenConnected();
        }
        return this.codec?.readValue(expression, this.coreName).then(function (data) {
            try {
                return Number.parseInt(data, 16);
            }
            catch (e) {
                return -1;
            }
        });
    }
    setParentEncoder(parent) {
        this.codec = parent;
        this.codec.addEventListener?.(connectedStateChangedEventType, this.transportStateChangeListener);
        this.codec.addEventListener?.(activeCoreChangedEventType, this.activeCoreChangedListener);
    }
    deconfigure() {
        this.codec?.removeEventListener?.(connectedStateChangedEventType, this.transportStateChangeListener);
        this.codec?.removeEventListener?.(activeCoreChangedEventType, this.activeCoreChangedListener);
        this.codec = undefined;
    }
    async onConnect(transport) {
        if (this.codec) {
            await (this.initPromise || this.codec.initCore(this.params, this.programAlreadyLoaded));
            if (!this.params.sram) {
                this.programAlreadyLoaded = true;
            }
            await super.onConnect(transport);
        }
        else {
            throw Error('Missing a parent codec.');
        }
    }
    get coreName() {
        return this.params.coreName;
    }
}

export { ProgramModel, ProgramModelDecoderType, ProgramModelEncoderType, activeCoreChangedEventType, nullProgramModelDecoder, nullProgramModelEncoder };
//# sourceMappingURL=ProgramModel.js.map
