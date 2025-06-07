import { EventType, Events } from '../../gc-core-assets/lib/Events';
import { GcPromise } from '../../gc-core-assets/lib/GcPromise';
import { GcConsole } from '../../gc-core-assets/lib/GcConsole';
import { GcFiles } from '../../gc-core-assets/lib/GcFiles';
import { GcLocalStorage } from '../../gc-core-assets/lib/GcLocalStorage';
import { GcUtils } from '../../gc-core-assets/lib/GcUtils';

const NAME = 'gc-core-databind';
const statusChangedEventType = new EventType('statusChangedListener');

/**
 * Value changed event type.  Used when add and remove listeners.
 */
const valueChangedEventType = new EventType('onValueChanged');
/**
 * Stale changed event type.  Used when add and remove listeners.
 */
const staleChangedEventType = new EventType('onStaleChanged');
/**
 * Streaming data event type.  Used when add and remove listeners.
 */
const streamingDataEventType = new EventType('onStreamingDataReceived');

/**
 *  Copyright (c) 2020, 2022 Texas Instruments Incorporated
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
 * Method to test if an instance of a class is disposable or not.
 *
 * @param obj object to test if disposable.
 */
function isDisposable(obj) {
    return 'dispose' in obj;
}

/**
 *  Copyright (c) 2020, 2022 Texas Instruments Incorporated
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
 *  Copyright (c) 2020, 2022 Texas Instruments Incorporated
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
/**
 * Refresh event type.  This is fired when a refresh is required.
 */
const refreshEventType = new EventType('onRefresh');
/**
 * This event is fired some amount of time prior to the refresh event.  The amount of time before the
 * refresh that this event is called is set using the **{@link RefreshIntervaleBindValue.setPreRefreshInterval}** method.  If no
 * pre-refresh interval is set, then no pre-refresh event is fired.
 */
const preRefreshEventType = new EventType('onPreRefresh');

/**
 *  Copyright (c) 2020, 2022 Texas Instruments Incorporated
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
const scriptLogEventType = new EventType('scriptLog');

/**
 *  Copyright (c) 2020, 2022 Texas Instruments Incorporated
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
 * Abstract class that implements IBind interface. Clients should not derive from
 * this class directly. Instead, they need to derive from some of its derived classes:
 * AbstractBindValue or AbstractBindAction.
 */
class AbstractBind extends Events {
    constructor() {
        super(...arguments);
        this._status = null;
    }
    get status() {
        return this._status;
    }
    set status(status) {
        if (status !== this._status) {
            if (!(status && status.equals(this._status))) {
                const details = { newStatus: status, oldStatus: this._status, bind: this };
                this.onStatusChanged(details);
                this._status = status;
                this.fireEvent(statusChangedEventType, details);
            }
        }
    }
    toString() {
        return this.name || '';
    }
}

const nullProgressCounter = new (class {
    constructor() {
        this.promise = Promise.resolve(0);
        this.count = 0;
        this.totalCount = 0;
    }
    // eslint-disable-next-line @typescript-eslint/no-empty-function
    wait() {
    }
    // eslint-disable-next-line @typescript-eslint/no-empty-function
    done() {
    }
    getProgress() {
        return 100;
    }
})();
/**
 * Class that implements IProgressCounter interface to count progress.
 * This class is constructed with a
 * callback that will be called when the progress reaches 100%.
 * A single initial job is added to the progress counter automatically.
 * in the constructor.
 * As a result, the client must call IProgressCounter.done() once to
 * complete the job.  Typically, the client will pass this object
 * around to other parties who may or may not add their own jobs
 * to the progress counter.  Only when all jobs are completed will
 * the client receive the callback.
 *
 */
class ProgressCounter {
    constructor(callback) {
        this.callback = callback;
        this.jobCount = 1;
        this.jobsDone = 0;
        this.deferred = GcPromise.defer();
        this.promise = this.deferred.promise;
    }
    wait(jobs = 1) {
        this.jobCount += jobs;
    }
    done(jobs = 1) {
        this.jobsDone += jobs;
        if (this.jobsDone === this.jobCount) {
            if (this.callback) { // make sure callback is called immediately, instead of waiting for next clock tick for promise.
                this.callback({ jobsCompleted: this.jobCount - 1 });
                this.callback = undefined;
            }
            this.deferred.resolve(this.jobCount - 1);
        }
    }
    getProgress() {
        return 100 * this.jobsDone / this.jobCount;
    }
    get count() {
        return this.jobsDone;
    }
    get totalCount() {
        return this.jobCount;
    }
}

/**
 *  Copyright (c) 2020, 2022 Texas Instruments Incorporated
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
/* eslint-disable @typescript-eslint/no-unused-vars */
let blockNewEditUndoOperationCreation = false;
/**
 * Abstract class that implements IBindValue interface.
 */
class AbstractBindValue extends AbstractBind {
    constructor(defaultType) {
        super();
        this.defaultType = defaultType;
        this.stale = false;
        this.deferredMode = false;
    }
    /**
     * Perform a deep compare on two values to determine if they have changes.
     * written to the committed value
     *
     * @param newValue the value to compare with
     * @returns true if the new value is not the same as the current value.
     */
    isValueNotEqualTo(newValue) {
        const oldValue = this.cachedValue;
        if (Array.isArray(newValue) && Array.isArray(oldValue) && newValue.length === oldValue.length) {
            // compare all elements of the array
            for (let i = newValue.length; i-- > 0;) {
                if (newValue[i] !== oldValue[i]) {
                    return true;
                }
            }
            return false;
        }
        return (newValue !== oldValue && ((typeof newValue !== 'number') || !isNaN(newValue) || (typeof oldValue !== 'number') || !isNaN(oldValue)));
    }
    /**
     * Sets the value of this bindable object. Setting the value can be an
     * asynchronous operation. If the caller is interested in knowing when the
     * operation is complete, they will pass in an
     * {gc.databind.IProgressCounter} object to keep track of the progress till
     * completion. This class implements this method and calls {#onValueChanged}
     * if the new value is in fact different. It also notifies IValueChanged
     * listeners and passes along the progress counter to them as well. Clients
     * should not override this method. Instead they should override
     * {#onValueChanged} instead.
     *
     * @param value - the new value.
     * @param progress - notification when the value is set in the model.
     * @forceWrite - forces value change notification even if the newValue equals the oldValue.
     */
    setValue(value, progress = nullProgressCounter, forceWrite) {
        const blockEditOperation = blockNewEditUndoOperationCreation;
        blockNewEditUndoOperationCreation = true; // tell widget model to not create Undo/Redo actions based on target data changes.
        try {
            if (!this.readOnly && (forceWrite || this.isValueNotEqualTo(value))) {
                const oldValue = this.cachedValue;
                this.cachedValue = value;
                const details = { newValue: value, oldValue: oldValue, progress: progress };
                this.onValueChanged(details);
                this.fireEvent(valueChangedEventType, details);
            }
        }
        catch (e) {
            // eslint-disable-next-line no-console
            console.error(e);
        }
        finally {
            blockNewEditUndoOperationCreation = blockEditOperation;
        }
    }
    /**
     * Updates the value of this bindable object, and notify all listeners. This
     * method is identical to setValue() method except it does not call
     * onValueChanged() even if the value has changed. Derived objects should
     * use this method to update the underlying value instead of setValue().
     * Then derived objects can then use onValueChanged() to detect when the
     * value has been changed by others only.
     *
     * @param value - the new value.
     * @param progress - optional progress
     *        counter if you wish to keep track of when the new value has
     *        propagated through all bindings bound to this one.
     * @param skipStreamingListeners - true, if you do not want
     *        to notify streaming listeners of the new value; for example, if
     *        you are updating the default value before reading the target.
     */
    updateValue(value, progress = nullProgressCounter, skipStreamingListeners) {
        const blockEditOperation = blockNewEditUndoOperationCreation;
        blockNewEditUndoOperationCreation = true; // tell widget model to not create Undo/Redo actions based on target data changes.
        try {
            if (this.isValueNotEqualTo(value)) {
                const oldValue = this.cachedValue;
                this.cachedValue = value;
                const details = { newValue: value, oldValue: oldValue, progress: progress };
                this.fireEvent(valueChangedEventType, details);
            }
            if (!skipStreamingListeners) {
                this.fireEvent(streamingDataEventType, { data: value });
            }
        }
        catch (e) {
            // eslint-disable-next-line no-console
            console.error(e);
        }
        finally {
            blockNewEditUndoOperationCreation = blockEditOperation;
        }
    }
    /**
     * Returns the value of this bindable object. In the case that the model
     * obtains the value asynchronously the value will be returned from an
     * internal cache to conform to a synchronous method.
     *
     * @returns the value of this bindable object. The value will be
     *         returned from an internal cache.
     */
    getValue() {
        return this.cachedValue;
    }
    /**
     * The type of the bindable object's value. Usually the class of the value.
     * If the value's type is not going to change, it can be set in the case the
     * value is null.
     *
     * @return the class of the value, or other class if the value has
     *         not been set yet. null means the values has not been set yet and
     *         also the value can change its type.
     */
    getType() {
        let result = this.defaultType;
        if (this.cachedValue !== undefined && this.cachedValue !== null) {
            result = typeof this.cachedValue;
            if (this.cachedValue instanceof Array) {
                result = 'array';
            }
        }
        return result;
    }
    /**
     * Method to change the bindable object's default type. The default type is
     * used when the current value is undefined or null.
     *
     * @param the new default type of the value.
     */
    setDefaultType(defaultType) {
        this.defaultType = defaultType;
    }
    toString() {
        if (this.cachedValue === undefined) {
            return super.toString();
        }
        else if (this.cachedValue === null) {
            return 'null';
        }
        return this.cachedValue.toString();
    }
    /**
     * This method is used to determine if the value of the binding object is
     * being changed. Stale state means that setValue() has been called, but the
     * real value of the model hasn't been updated yet. The method will be used
     * to determine if changes should be propagated now, or wait until the
     * binding is no longer stale to propagate changes.
     *
     * @returns true if the value is going to change soon; otherwise, false.
     */
    isStale() {
        return this.stale;
    }
    /**
     * Derived classes can call this method to set the stale state of the
     * object.
     *
     * @param stale - if the value of stale or not.
     */
    setStale(stale = false) {
        if (this.stale !== stale) {
            this.stale = stale;
            this.fireEvent(staleChangedEventType, { stale: stale });
        }
    }
    /**
     * This method indicates whether or not the value of this bindable object is
     * modifiable or not. If this method returns true, then calling setValue()
     * will do nothing.
     *
     * @returns true if this binding is read only (can't be modified).
     */
    get readOnly() {
        return false;
    }
    /**
     * This method changes the deferred mode of operation.  In deferred mode, values are not written to the
     * target device.  Values change during deferred mode, are written to the target when the deferred mode
     * is turned off.
     *
     * @param deferredMode - true to defer write, and false to commit writes immediately.
     * @param progress - used when deferred mode is turned off, and monitors progress of writing defefred values to target.
     */
    setDeferredMode(deferredMode = false, progress = nullProgressCounter, forceWrite = false) {
        if (deferredMode !== this.deferredMode) {
            this.deferredMode = deferredMode;
            this.committedValue = this.cachedValue;
        }
    }
    /**
     * This method tests if the new value of the binding has not yet been written to the target due to the
     * deferred mode being on.
     *
     * @returns true if the current value is different from the last committed value.
     */
    isDeferredWritePending() {
        return this.deferredMode && this.isValueNotEqualTo(this.committedValue);
    }
    /**
     * This method retrieves the last committed value written to the target, and not the current value which
     * may be different when deferred mode is on.
     *
     * @returns the value last committed value written to target.
     */
    getValueCommitted() {
        return this.deferredMode ? this.committedValue : this.cachedValue;
    }
    /**
     * This method clears any pending write to the target due to deferred mode, and restores the current value
     * with the last committed value to the target.  Effectively cancelling any changes made during deferred mode.
     */
    clearDeferredWrite() {
        if (this.deferredMode) {
            this.updateValue(this.committedValue, undefined, true);
        }
    }
    onStatusChanged(details) {
        // do nothing here for default implementation.
    }
}

/**
 *  Copyright (c) 2020, 2022 Texas Instruments Incorporated
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
class AbstractLiteralBinding extends AbstractBindValue {
    constructor(literalValue) {
        super(typeof literalValue);
        this.cachedValue = literalValue;
    }
    // eslint-disable-next-line @typescript-eslint/no-empty-function
    setValue() {
    }
    get readOnly() {
        return true;
    }
    // eslint-disable-next-line @typescript-eslint/no-empty-function
    onValueChanged() {
    }
}

/**
 *  Copyright (c) 2020, 2022 Texas Instruments Incorporated
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
class NumberLiteral extends AbstractLiteralBinding {
    constructor(literal) {
        super(literal);
    }
    static parse(literal) {
        const value = Number(literal);
        if (!isNaN(value)) {
            return value;
        }
        return null;
    }
    static parseLiteral(uri) {
        const result = NumberLiteral.parse(uri);
        return result === null ? null : new NumberLiteral(result);
    }
}

/**
 *  Copyright (c) 2020, 2022 Texas Instruments Incorporated
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
class ExpressionParserUtils {
    static isDigit(c) {
        return (c >= '0' && c <= '9') || c === '.';
    }
    static composeUnrecognizedTextErrMsg(text, literalErrorMessage) {
        // Unrecognized character
        let msg = 'Unexpected character';
        if (text.length > 1) {
            msg += 's "' + text + '" were';
        }
        else {
            msg += ' "' + text + '" was';
        }
        msg += ' found.  If this was suppose to be an operator, it is not supported.';
        if (literalErrorMessage !== null) {
            msg += '  Also, I do not recognize this as part of a literal.  ' + literalErrorMessage;
        }
        throw new Error(msg);
    }
    static composeUnexpectedWhiteSpaceErrMsg(text) {
        // spaces are not allowed in identifiers
        throw new Error('Unexpected white space was found in the following expression "' + text +
            '".  To be honest, I was expecting an operator, or something other than blank.');
    }
    static composeUnrecognizedIdentifier(unrecognizedText, literalErrorMessage) {
        if (unrecognizedText.trim().length === 0) {
            this.composeUnexpectedWhiteSpaceErrMsg(unrecognizedText);
        }
        else {
            this.composeUnrecognizedTextErrMsg(unrecognizedText, literalErrorMessage);
        }
    }
    static composeMissingClosingBraceErrMsg(uri, brace) {
        throw new Error('To be honest, I was expecting to find a terminating ' + brace + ' after "' + uri + '".');
    }
    static composeMissingOperatorErrMsg(uri) {
        throw new Error('To be honest, I was expecting to find an operator at the beginning of this expression: ' + uri);
    }
    static testIdentifier(text, errMessageContext) {
        if (!this.isDigit(text.charAt(0))) {
            const unexpectedCharacters = this.notIdentifierRegExp.exec(text);
            if (unexpectedCharacters !== null) {
                this.composerInvalidIdentifierErrorMessage(text, `I was not expecting to find "${unexpectedCharacters[0]}"`, errMessageContext);
            }
        }
        else if (text.charAt(0) === '.') {
            this.composerInvalidIdentifierErrorMessage(text, 'I was not expecting it to begin with a period.', errMessageContext);
        }
        else {
            this.composerInvalidIdentifierErrorMessage(text, 'I was not expecting it to begin with a number.', errMessageContext);
        }
    }
    static getIdentifiers(text) {
        const matches = text.match(this.identifierSearch);
        return matches?.filter(match => this.firstCharacterInIdentifier.test(match)) || [];
    }
    static composerInvalidIdentifierErrorMessage(text, errDetailMessage, errMessageContext = '') {
        throw new Error('Invalid identifier found' + errMessageContext + ': "' + text + '".  To be honest, ' + errDetailMessage);
    }
}
// eslint-disable-next-line no-useless-escape
ExpressionParserUtils.notIdentifierRegExp = /[^A-Za-z$_.0-9]+/;
ExpressionParserUtils.identifierSearch = /[A-Za-z$_.0-9]+|'[^']*'|"[^"]"/g;
ExpressionParserUtils.firstCharacterInIdentifier = /^[A-Za-z$_]/;

/**
 *  Copyright (c) 2020, 2022 Texas Instruments Incorporated
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
const singleQuote = '\'';
class StringLiteral extends AbstractLiteralBinding {
    constructor(literal) {
        super(literal);
        this.cachedValue = literal.split('\\\'').join(singleQuote);
        this.cachedValue = this.cachedValue.split('\\\\').join('\\');
    }
    static parseLiteral(uri) {
        if (uri.indexOf(singleQuote) === 0) {
            // find end pos skipping escaped quotes preceded by backslash character.
            let endPos = 0;
            let escaped;
            do {
                endPos = uri.indexOf(singleQuote, endPos + 1);
                escaped = false;
                for (let i = endPos; i > 0 && uri.charAt(i - 1) === '\\'; i--) {
                    escaped = !escaped;
                }
            } while (escaped);
            if (endPos <= 0) {
                ExpressionParserUtils.composeMissingClosingBraceErrMsg(uri, 'single quote');
            }
            else if (endPos !== uri.length - 1) {
                ExpressionParserUtils.composeMissingOperatorErrMsg(uri.substring(endPos + 1));
            }
            else {
                // strip quotes
                uri = uri.substring(1, uri.length - 1);
                return new StringLiteral(uri);
            }
        }
        return null;
    }
}

/**
 *  Copyright (c) 2020, 2022 Texas Instruments Incorporated
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
class BooleanLiteral extends AbstractLiteralBinding {
    constructor(literal) {
        super(literal);
    }
    static parse(literal) {
        const upperCaseValue = literal.toUpperCase();
        if (upperCaseValue === 'TRUE' || upperCaseValue === 'FALSE') {
            return upperCaseValue === 'TRUE';
        }
        return null;
    }
    static parseLiteral(literal) {
        const booleanValue = this.parse(literal);
        if (booleanValue !== null) {
            return new BooleanLiteral(booleanValue);
        }
        return null;
    }
}

class OperatorList {
    constructor(samePrecedenceOperators) {
        this.samePrecedenceOperators = samePrecedenceOperators;
        this.operator = '';
    }
    parse(uri, factory, precedence) {
        // search for first operator from right to left order
        let firstOperator = -1;
        let operator = null;
        for (let i = 0; i < this.samePrecedenceOperators.length; i++) {
            const parser = this.samePrecedenceOperators[i];
            const pos = factory.findLastIndexOf(uri, parser.operator);
            if (pos > firstOperator) {
                firstOperator = pos;
                operator = parser;
            }
        }
        if (operator !== null) {
            return operator.parse(uri, factory, precedence);
        }
        return null;
    }
}

// below is a regular expression. It has three alternatives to match
// 1. ^\s+ this matches all leading spaces
// 2. this matches two alternatives plus the optional spaces around it
// 2a. [^A-Za-z0-9$_ ']+ this matches anything that is not an identifier or
// anything in quotes.
// The space is a terminator for the character group. Dots are not included
// because we can
// remove the spaces around them.
// 2b. '[^']' this matches quoted text and includes spaces in between quotes
// 3. \s+$ this matches trailing spaces
// Alternative 1 & 3 have an empty capture group, and alternative 2's
// capture group excludes the
// surrounding spaces.
const stripSpacesMatchString = /^\s+|\s*([^A-Za-z0-9$_ ']+|'[^']*')\s*|\s+$/g;
class Bracket {
    constructor(openingBrace, closingBrace, link) {
        this.openingBrace = openingBrace;
        this.closingBrace = closingBrace;
        this.link = link;
    }
    countBraces(text, brace, endingPos) {
        let count = 0;
        for (let pos = 0; pos <= endingPos;) {
            pos = text.indexOf(brace, pos);
            if (pos < 0 || pos > endingPos) {
                break;
            }
            else if (pos === 0 || (text.charAt(pos - 1) !== '\\' &&
                (this.link === undefined || !this.link.isInBracket(text, pos)))) {
                count++;
            }
            pos = pos + brace.length;
        }
        return count;
    }
    isInBracket(text, endingPos) {
        let count = this.countBraces(text, this.openingBrace, endingPos);
        if (count > 0) {
            if (this.closingBrace !== this.openingBrace) {
                count -= this.countBraces(text, this.closingBrace, endingPos);
                return count !== 0;
            }
            else if ((count & 1) !== 0) { // if odd count, then we are in a bracket; otherwise we are not.
                return true;
            }
        }
        // if not in this bracket, try the next one
        if (this.link !== undefined) {
            return this.link.isInBracket(text, endingPos);
        }
        return false; // we are not in any of the brackets.
    }
}
class AbstractBindExpressionParser {
    constructor(bindings = new Map()) {
        this.bindings = bindings;
        this.operatorFactories = [];
        this.brackets = new Bracket('(', ')');
    }
    addOperatorFactory(...factories) {
        if (factories.length > 1) {
            this.operatorFactories.push(new OperatorList(factories));
        }
        else if (factories.length > 0) {
            this.operatorFactories.push(factories[0]);
        }
    }
    addBraces(openingBrace, closingBrace) {
        // ensure parenthesis () are kept at front of list, because order matters.
        this.brackets.link = new Bracket(openingBrace, closingBrace, this.brackets.link);
    }
    static parseLiteral(uri) {
        let result = NumberLiteral.parseLiteral(uri);
        if (result === null) {
            result = BooleanLiteral.parseLiteral(uri);
        }
        if (result === null) {
            result = StringLiteral.parseLiteral(uri);
        }
        return result;
    }
    findFirstIndexOf(text, operator, startingPos = 0) {
        let pos = startingPos;
        const len = operator.length - 2;
        // eslint-disable-next-line no-constant-condition
        while (true) {
            pos = text.indexOf(operator, pos);
            if (pos > 0 && this.brackets.isInBracket(text, pos + len)) {
                pos = pos + operator.length;
                if (pos >= text.length) {
                    pos = -1; // ran out of text, so indicate no match found.
                    break;
                }
            }
            else {
                break;
            }
        }
        return pos;
    }
    findLastIndexOf(text, operator, includeOperator) {
        let pos = text.lastIndexOf(operator);
        const len = includeOperator ? operator.length - 1 : -1;
        while (pos > 0 && this.brackets.isInBracket(text, pos + len)) {
            pos = text.lastIndexOf(operator, pos - operator.length);
        }
        return pos;
    }
    findMatchingBrace(text, openingBrace, closingBrace) {
        let pos = -1;
        let nestedBracePos = -1;
        do {
            pos = this.findFirstIndexOf(text, closingBrace, pos + 1);
            nestedBracePos = this.findFirstIndexOf(text, openingBrace, nestedBracePos + 1);
        } while (nestedBracePos >= 0 && pos > nestedBracePos);
        return pos;
    }
    parseExpression(uri, precedence, isLookupBinding = false) {
        if (uri.length === 0) {
            return null;
        }
        if (precedence === undefined) {
            // first time strip extra spaces in the expression so that
            // expressions that
            // differ only in extra spaces can be matched by string compares.
            // second time (called from expressionParser) there will be a hint
            // provided.
            uri = uri.replace(stripSpacesMatchString, '$1');
            precedence = 0;
        }
        if (!isLookupBinding && this.bindings.has(uri)) {
            return this.bindings.get(uri) || null;
        }
        let result = null;
        const unrecognizedText = ExpressionParserUtils.notIdentifierRegExp.exec(uri);
        // parse operators first
        if (unrecognizedText !== null) {
            for (let i = precedence; i < this.operatorFactories.length && result === null; i++) {
                const operatorFactory = this.operatorFactories[i];
                result = operatorFactory.parse(uri, this, i);
            }
        }
        // no operators found, try parsing literal
        let literalErrorMessage = null;
        if (result === null) {
            try {
                result = AbstractBindExpressionParser.parseLiteral(uri);
            }
            catch (e) {
                if (ExpressionParserUtils.isDigit(uri.charAt(0))) {
                    // identifiers can't start with a digit, so re throw this exception.
                    // hopefully this error message will be more meaningful that the identifier error message.
                    throw e;
                }
                literalErrorMessage = e.toString();
            }
        }
        // try parsing config variable references
        if (result === null) {
            if (unrecognizedText === null) {
                result = this.bindValue(uri, isLookupBinding);
            }
            else {
                ExpressionParserUtils.composeUnrecognizedIdentifier(unrecognizedText[0], literalErrorMessage);
            }
        }
        if (result) {
            result.uri = uri;
            if (typeof result.setIndex === 'function') {
                result.setIndex(); // kick start index lookups if parseLookupExpression returns a lookup operator.
            }
        }
        if (!isLookupBinding) {
            this.bindings.set(uri, result);
        }
        return result;
    }
    dispose() {
        this.bindings.forEach((bind) => {
            if (bind !== null && isDisposable(bind)) {
                bind.dispose();
            }
        });
        this.bindings.clear();
    }
    getBindingCount() {
        return this.bindings.size;
    }
}

const openingBrace = '?';
const closingBrace = ':';
const OP$k = openingBrace + closingBrace;
class Factory$k {
    constructor() {
        this.operator = OP$k;
    }
    parse(uri, factory, precedence) {
        let pos = factory.findFirstIndexOf(uri, openingBrace, 0);
        if (pos === 0) {
            // empty condition paramenter
            throw new Error('I found a \'?\' operator but nothing in front of it.  ' +
                `To be honest, I was expecting to find something before the '?' in the following text: ${uri}`);
        }
        else if (pos > 0) {
            const conditionText = uri.substring(0, pos);
            const remainingText = uri.substring(pos + 1);
            pos = factory.findMatchingBrace(remainingText, openingBrace, closingBrace);
            if (pos < 0) {
                // missing matching ':' operator.
                throw new Error('I found a \'?\' operator, but I couldn\'t find the matching \':\' operator.  ' +
                    `To be honest I was expecting one in the following text: ${remainingText}`);
            }
            else if (pos === 0) {
                // empty middle paramenter
                throw new Error('I found a \':\' imediately following a \'?\' operator.  To be honest, I was expecting to find something between them.');
            }
            else if (pos >= remainingText.length - 1) {
                // empty right paramenter
                throw new Error('I found a \'?\' operator a with matching \':\', but nothing after the \':\' operator.  ' +
                    `To be honest, I was expecting to find something after the ':' in the following text: ${remainingText}`);
            }
            else {
                const trueText = remainingText.substring(0, pos);
                const falseText = remainingText.substring(pos + 1);
                const condition = factory.parseExpression(conditionText, precedence);
                const trueOperand = factory.parseExpression(trueText, precedence);
                const falseOperand = factory.parseExpression(falseText, precedence);
                if (condition === null || trueOperand === null || falseOperand === null) {
                    throw new Error('Missing operands for the conditional (?:) operator.');
                }
                // eslint-disable-next-line @typescript-eslint/no-use-before-define
                return new ConditionalOperator(condition, trueOperand, falseOperand);
            }
        }
        return null;
    }
}
class ConditionalOperator {
    constructor(condition, trueOperand, falseOperand) {
        this.condition = condition;
        this.trueOperand = trueOperand;
        this.falseOperand = falseOperand;
        this.operator = OP$k;
        this.streamingListenerMap = new Map();
    }
    addEventListener(type, listener) {
        if (type === streamingDataEventType) {
            let streamingOperand = this.getConditionalBranch();
            streamingOperand.addEventListener(type, listener);
            const valueChangedListener = () => {
                streamingOperand.removeEventListener(type, listener);
                streamingOperand = this.getConditionalBranch();
                streamingOperand.addEventListener(type, listener);
            };
            this.streamingListenerMap.set(listener, valueChangedListener);
            this.condition.addEventListener(valueChangedEventType, valueChangedListener);
        }
        else {
            this.condition.addEventListener(type, listener);
            this.trueOperand.addEventListener(type, listener);
            this.falseOperand.addEventListener(type, listener);
        }
    }
    removeEventListener(type, listener) {
        if (type === streamingDataEventType) {
            const valueChangedListener = this.streamingListenerMap.get(listener);
            if (valueChangedListener && listener) {
                this.condition.removeEventListener(valueChangedEventType, valueChangedListener);
                this.streamingListenerMap.delete(listener);
            }
        }
        else {
            this.condition.removeEventListener(type, listener);
        }
        this.trueOperand.removeEventListener(type, listener);
        this.falseOperand.removeEventListener(type, listener);
    }
    dispose() {
        if (isDisposable(this.condition)) {
            this.condition.dispose();
        }
        if (isDisposable(this.trueOperand)) {
            this.trueOperand.dispose();
        }
        if (isDisposable(this.falseOperand)) {
            this.falseOperand.dispose();
        }
    }
    getConditionalBranch() {
        const value = this.condition.getValue();
        return (value ? this.trueOperand : this.falseOperand);
    }
    getValue() {
        return this.getConditionalBranch().getValue();
    }
    setValue(value, progress, forceWrite) {
        this.getConditionalBranch().setValue(value, progress, forceWrite);
    }
    updateValue(value, progress, skipStreamingListeners) {
        this.getConditionalBranch().updateValue(value, progress, skipStreamingListeners);
    }
    getType() {
        return this.getConditionalBranch().getType();
    }
    get status() {
        return this.getConditionalBranch().status;
    }
    set status(status) {
        this.getConditionalBranch().status = status;
    }
    toString() {
        return ' ? ' + this.trueOperand.toString() + ' : ' + this.falseOperand.toString();
    }
    isStale() {
        return this.condition.isStale() || this.getConditionalBranch().isStale();
    }
    get readOnly() {
        return this.getConditionalBranch().readOnly;
    }
    setDeferredMode(deferredMode, progress = nullProgressCounter, forceWrite = false) {
        this.getConditionalBranch().setDeferredMode(deferredMode, progress, forceWrite);
    }
    getValueCommitted() {
        this.getConditionalBranch().getValueCommitted();
    }
    clearDeferredWrite() {
        this.getConditionalBranch().clearDeferredWrite();
    }
    isDeferredWritePending() {
        return this.getConditionalBranch().isDeferredWritePending();
    }
}
ConditionalOperator.factory = new Factory$k();

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
var StatusType;
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
class Status {
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
class DataConverter {
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

class AbstractBinaryOperatorFactory {
    parse(uri, factory, precedence) {
        const pos = factory.findLastIndexOf(uri, this.operator);
        if (pos > 0 && pos < uri.length - 1) { // can't be first or last character, because it's not a unary operator
            let operandText = uri.substring(0, pos);
            const leftOperand = factory.parseExpression(operandText, precedence);
            operandText = uri.substring(pos + this.operator.length);
            // there are no operators to the right of this one at the same precedence level
            const rightOperand = factory.parseExpression(operandText, precedence + 1);
            if (leftOperand === null || rightOperand === null) {
                throw new Error(`Missing operands for the ${this.operator} operator.`);
            }
            return this.createOperator(leftOperand, rightOperand);
        }
        return null;
    }
}
class AbstractBinaryOperator extends Events {
    constructor(leftOperand, rightOperand) {
        super();
        this.leftOperand = leftOperand;
        this.rightOperand = rightOperand;
        this._status = null;
    }
    toString() {
        return this.leftOperand.toString() + ' ' + this.operator + ' ' + this.rightOperand.toString();
    }
    setValue(value, progress, forceWrite) {
        if (!this.readOnly) {
            try {
                if (this.leftOperand.readOnly) {
                    value = this.doSetValue(value, this.leftOperand.getValue(), true);
                    const rightType = this.rightOperand.getType();
                    value = DataConverter.convert(value, typeof value, rightType);
                    this.rightOperand.setValue(value, progress, forceWrite);
                }
                else {
                    value = this.doSetValue(value, this.rightOperand.getValue(), false);
                    const leftType = this.leftOperand.getType();
                    value = DataConverter.convert(value, typeof value, leftType);
                    this.leftOperand.setValue(value, progress, forceWrite);
                }
            }
            catch (e) {
                this.status = Status.createErrorStatus(e.message);
            }
        }
    }
    updateValue() {
        throw new Error('Cannot updateValue on expressions');
    }
    dispose() {
        if (isDisposable(this.leftOperand)) {
            this.leftOperand.dispose();
        }
        if (isDisposable(this.rightOperand)) {
            this.rightOperand.dispose();
        }
    }
    get status() {
        return this._status || this.leftOperand.status || this.rightOperand.status;
    }
    set status(status) {
        if (this.status !== status) {
            const oldStatus = this._status;
            this._status = status;
            this.fireEvent(statusChangedEventType, { newStatus: status, oldStatus: oldStatus, bind: this });
        }
    }
    doBooleanOperation(leftValue, rightValue) {
        if (this.evalBoolean !== undefined) {
            return this.evalBoolean(leftValue, rightValue);
        }
        else {
            throw new Error(`Operator '${this.operator}' does not support boolean types`);
        }
    }
    doNumericOperation(leftValue, rightValue) {
        if (this.evalNumber !== undefined) {
            return this.evalNumber(leftValue, rightValue);
        }
        else {
            throw new Error(`Operator '${this.operator}' does not support numeric types`);
        }
    }
    doArrayOperation(leftValue, rightValue) {
        if (this.evalArray !== undefined) {
            return this.evalArray(leftValue, rightValue);
        }
        else {
            throw new Error(`Operator '${this.operator}' does not support array types`);
        }
    }
    doStringOperation(leftValue, rightValue) {
        if (this.evalString !== undefined) {
            return this.evalString(leftValue, rightValue);
        }
        else {
            throw new Error(`Operator '${this.operator}' does not support string types`);
        }
    }
    doObjectOperation(leftValue, rightValue) {
        if (this.evalObject !== undefined) {
            return this.evalObject(leftValue, rightValue);
        }
        else {
            throw new Error(`Operator '${this.operator}' does not support object types`);
        }
    }
    doGetValue(leftValue, rightValue) {
        if (leftValue === null || rightValue === null) {
            return null; // one side or the other cannot be evaluated, so pass this information along.
        }
        else if (leftValue === undefined || rightValue === undefined) {
            return undefined;
        }
        const leftType = this.leftOperand.getType();
        const rightType = this.rightOperand.getType();
        try {
            if (leftType === 'boolean' && rightType === 'boolean') {
                return this.doBooleanOperation(leftValue, rightValue);
            }
            else if (leftType === 'array') {
                return this.doArrayOperation(leftValue, rightType === 'array' ? rightValue : [rightValue]);
            }
            else if (rightType === 'array') {
                return this.doArrayOperation([leftValue], rightValue);
            }
            else if (leftType === 'string') {
                return this.doStringOperation(leftValue, rightType === 'string' ? rightValue : rightValue.toString());
            }
            else if (rightType === 'string') {
                return this.doStringOperation(leftValue.toString(), rightValue);
            }
            else if (leftType === 'number' && rightType === 'number') {
                return this.doNumericOperation(leftValue, rightValue);
            }
            else if (leftType === 'number' && typeof rightValue.valueOf() === 'number') {
                return this.doNumericOperation(leftValue, rightValue.valueOf());
            }
            else if (leftType === 'number' && rightType === 'boolean') {
                return this.doNumericOperation(leftValue, rightValue ? 1 : 0);
            }
            else if (rightType === 'number' && typeof leftValue.valueOf() === 'number') {
                return this.doNumericOperation(leftValue.valueOf(), rightValue);
            }
            else if (rightType === 'number' && leftType === 'boolean') {
                return this.doNumericOperation(leftValue ? 1 : 0, rightValue);
            }
            else if (this.evalString !== undefined) {
                return this.doStringOperation(leftValue.toString(), rightValue.toString());
            }
            else if (leftType === 'object' && rightType === 'object') {
                return this.doObjectOperation(leftValue, rightValue);
            }
            else {
                let type = 'object';
                if (this.evalBoolean === undefined && (leftType === 'boolean' || rightType === 'boolean')) {
                    type = 'boolean';
                }
                if (this.evalNumber === undefined && (leftType === 'number' || rightType === 'number')) {
                    type = 'numeric';
                }
                throw new Error(`Operator '${this.operator}' does not support ${type} types`);
            }
        }
        catch (e) {
            this.status = Status.createErrorStatus(e.message);
            return null;
        }
    }
    getValue() {
        const leftValue = this.leftOperand.getValue();
        const rightValue = this.rightOperand.getValue();
        return this.doGetValue(leftValue, rightValue);
    }
    getType() {
        const value = this.getValue();
        if (value !== null && value !== undefined) {
            let result = typeof value;
            if (result === 'object' && value instanceof Array) {
                result = 'array';
            }
            return result;
        }
        const leftType = this.leftOperand.getType();
        const rightType = this.rightOperand.getType();
        if (leftType === rightType) {
            return leftType;
        }
        else if (leftType === 'array' || rightType === 'array') {
            return 'array';
        }
        else if (leftType === 'string' || rightType === 'string') {
            return 'string';
        }
        else if (leftType === 'number' || rightType === 'number') {
            return 'number';
        }
        else {
            return 'object';
        }
    }
    isStale() {
        return this.leftOperand.isStale() || this.rightOperand.isStale();
    }
    get readOnly() {
        return ((this.leftOperand.readOnly ? 1 : 0) ^ (this.rightOperand.readOnly ? 1 : 0)) === 0;
    }
    // eslint-disable-next-line @typescript-eslint/no-empty-function
    onValueChanged() {
    }
    addEventListener(type, listener) {
        this.leftOperand.addEventListener(type, listener);
        this.rightOperand.addEventListener(type, listener);
        if (type === statusChangedEventType) {
            super.addEventListener(type, listener);
        }
    }
    removeEventListener(type, listener) {
        this.leftOperand.removeEventListener(type, listener);
        this.rightOperand.removeEventListener(type, listener);
        if (type === statusChangedEventType) {
            super.removeEventListener(type, listener);
        }
    }
    setDeferredMode(deferredMode, progress = nullProgressCounter, forceWrite = false) {
        this.leftOperand.setDeferredMode(deferredMode, progress, forceWrite);
        this.rightOperand.setDeferredMode(deferredMode, progress, forceWrite);
    }
    getValueCommitted() {
        const leftValue = this.leftOperand.getValueCommitted();
        const rightValue = this.rightOperand.getValueCommitted();
        return this.doGetValue(leftValue, rightValue);
    }
    clearDeferredWrite() {
        this.leftOperand.clearDeferredWrite();
        this.rightOperand.clearDeferredWrite();
    }
    isDeferredWritePending() {
        return this.leftOperand.isDeferredWritePending() || this.rightOperand.isDeferredWritePending();
    }
}

/**
 *  Copyright (c) 2020, 2022 Texas Instruments Incorporated
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
class AbstractComparisonOperatorFactory extends AbstractBinaryOperatorFactory {
}
class AbstractComparisonOperator extends AbstractBinaryOperator {
    getType() {
        return 'boolean';
    }
    get readOnly() {
        return true;
    }
    // eslint-disable-next-line @typescript-eslint/no-empty-function
    doSetValue() {
    }
}

const OP$j = '==';
class Factory$j extends AbstractComparisonOperatorFactory {
    constructor() {
        super(...arguments);
        this.operator = OP$j;
    }
    createOperator(leftOperand, rightOperand) {
        // eslint-disable-next-line @typescript-eslint/no-use-before-define
        return new EqualsOperator(leftOperand, rightOperand);
    }
}
function doEvalEquals(left, right) {
    // eslint-disable-next-line eqeqeq
    return left == right;
}
class EqualsOperator extends AbstractComparisonOperator {
    constructor() {
        super(...arguments);
        this.operator = OP$j;
        this.evalNumber = doEvalEquals;
        this.evalBoolean = doEvalEquals;
        this.evalString = doEvalEquals;
    }
}
EqualsOperator.factory = new Factory$j();

/**
 *  Copyright (c) 2020, 2022 Texas Instruments Incorporated
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
const OP$i = '+';
class Factory$i extends AbstractBinaryOperatorFactory {
    constructor() {
        super(...arguments);
        this.operator = OP$i;
    }
    createOperator(leftOperand, rightOperand) {
        // eslint-disable-next-line @typescript-eslint/no-use-before-define
        return new AdditionOperator(leftOperand, rightOperand);
    }
}
function doAdd(left, right) {
    return left + right;
}
class AdditionOperator extends AbstractBinaryOperator {
    constructor() {
        super(...arguments);
        this.operator = OP$i;
        this.evalArray = function (left, right) {
            let result;
            if (left.length === 0) {
                result = right;
            }
            else if (right.length === 0) {
                result = left;
            }
            else {
                result = [];
                let i;
                for (i = 0; i < left.length; i++) {
                    result.push(left[i]);
                }
                for (i = 0; i < right.length; i++) {
                    result.push(right[i]);
                }
            }
            return result;
        };
        this.evalString = doAdd;
        this.evalNumber = doAdd;
    }
    doSetValue(value, constant, isLeftParamConstant) {
        const type = this.getType();
        if (type === 'string') {
            const match = constant.toString();
            if (isLeftParamConstant) {
                if (value.indexOf(match) === 0) {
                    return value.substring(match.length);
                }
            }
            else if (value.lastIndexOf(match) + match.length === value.length) {
                return value.substring(0, value.length - match.length);
            }
        }
        else if (type === 'number') {
            return value - constant;
        }
        return value;
    }
}
AdditionOperator.factory = new Factory$i();

/**
 *  Copyright (c) 2020, 2022 Texas Instruments Incorporated
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
const OP$h = '!=';
class Factory$h extends AbstractComparisonOperatorFactory {
    constructor() {
        super(...arguments);
        this.operator = OP$h;
    }
    createOperator(leftOperand, rightOperand) {
        // eslint-disable-next-line @typescript-eslint/no-use-before-define
        return new NotEqualsOperator(leftOperand, rightOperand);
    }
}
function evalFunction(left, right) {
    // eslint-disable-next-line eqeqeq
    return left != right;
}
class NotEqualsOperator extends AbstractComparisonOperator {
    constructor() {
        super(...arguments);
        this.operator = OP$h;
        this.evalNumber = evalFunction;
        this.evalBoolean = evalFunction;
        this.evalString = evalFunction;
    }
}
NotEqualsOperator.factory = new Factory$h();

/**
 *  Copyright (c) 2020, 2022 Texas Instruments Incorporated
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
const OP$g = '/';
class Factory$g extends AbstractBinaryOperatorFactory {
    constructor() {
        super(...arguments);
        this.operator = OP$g;
    }
    createOperator(leftOperand, rightOperand) {
        // eslint-disable-next-line @typescript-eslint/no-use-before-define
        return new DivisionOperator(leftOperand, rightOperand);
    }
}
class DivisionOperator extends AbstractBinaryOperator {
    constructor() {
        super(...arguments);
        this.operator = OP$g;
        this.evalNumber = function (left, right) {
            return left / right;
        };
        this.getType = function () {
            return 'number';
        };
    }
    doSetValue(value, constant, isLeftParamConstant) {
        return isLeftParamConstant ? constant / value : value * constant;
    }
}
DivisionOperator.factory = new Factory$g();

class AbstractUnaryOperatorFactory {
    parse(uri, factory, precedence = 0) {
        if (uri.indexOf(this.operator) === 0) {
            const operandText = uri.substring(this.operator.length);
            const operand = factory.parseExpression(operandText, precedence);
            if (operand !== null) {
                return this.createOperator(operand);
            }
        }
        return null;
    }
}
class AbstractUnaryOperator extends Events {
    constructor(operand) {
        super();
        this.operand = operand;
        this._status = null;
    }
    addEventListener(type, listener) {
        this.operand.addEventListener(type, listener);
        super.addEventListener(type, listener);
    }
    removeEventListener(type, listener) {
        this.operand.removeEventListener(type, listener);
        super.removeEventListener(type, listener);
    }
    get status() {
        return this._status || this.operand.status;
    }
    set status(status) {
        if (this._status !== status) {
            const oldStatus = this._status;
            this._status = status;
            this.fireEvent(statusChangedEventType, { newStatus: status, oldStatus: oldStatus, bind: this });
        }
    }
    dispose() {
        if (isDisposable(this.operand)) {
            this.operand.dispose();
        }
    }
    setValue(value, progress, forceWrite) {
        if (value === null || value === undefined) {
            return; // ignore null values
        }
        const type = this.operand.getType();
        let result;
        try {
            if (type === 'boolean') {
                result = this.doBooleanOperation(value, true);
            }
            else if (type === 'number') {
                result = this.doNumericOperation(value, true);
            }
            else if (type === 'array') {
                result = this.doArrayOperation(value, true);
            }
            else if (type === 'string') {
                result = this.doStringOperation(value, true);
            }
            else if (type === 'object') {
                result = this.doObjectOperation(value, true);
            }
            else {
                throw new Error(`Operator '${this.operator}' does not support ${type} types`);
            }
            this.operand.setValue(result, progress, forceWrite);
        }
        catch (e) {
            this.status = Status.createErrorStatus(e.message);
        }
    }
    updateValue() {
        throw new Error('Cannot updateValue on expressions');
    }
    getValue() {
        const value = this.operand.getValue();
        if (value === null || value === undefined) {
            return value; // parameter is not available, pass this on.
        }
        const type = this.operand.getType();
        try {
            if (type === 'boolean') {
                return this.doBooleanOperation(value, false);
            }
            else if (type === 'number') {
                return this.doNumericOperation(value, false);
            }
            else if (type === 'array') {
                return this.doArrayOperation(value, false);
            }
            else if (type === 'string') {
                return this.doStringOperation(value, false);
            }
            else if (type === 'object') {
                return this.doObjectOperation(value, false);
            }
            else {
                throw new Error(`Operator '${this.operator}' does not support ${type} types`);
            }
        }
        catch (e) {
            this.status = Status.createErrorStatus(e.message);
            return null;
        }
    }
    doBooleanOperation(value, write) {
        if (this.evalBoolean !== undefined) {
            return this.evalBoolean(value, write);
        }
        else {
            throw new Error(`Operator '${this.operator}' does not support boolean types`);
        }
    }
    doNumericOperation(value, write) {
        if (this.evalNumber !== undefined) {
            return this.evalNumber(value, write);
        }
        else {
            throw new Error(`Operator '${this.operator}' does not support numeric types`);
        }
    }
    doArrayOperation(valueArray, write) {
        if (this.evalArray !== undefined) {
            if (valueArray instanceof Array) {
                return this.evalArray(valueArray, write);
            }
            else {
                return this.evalArray([valueArray], write);
            }
        }
        else {
            throw new Error(`Operator '${this.operator}' does not support array types`);
        }
    }
    doStringOperation(value, write) {
        if (this.evalString !== undefined) {
            return this.evalString(value, write);
        }
        else {
            throw new Error(`Operator '${this.operator}' does not support string types`);
        }
    }
    doObjectOperation(value, write) {
        if (this.evalObject !== undefined) {
            return this.evalObject(value, write);
        }
        else { // try converting using number or string conversion if available before reporting object types not supported.
            value = value.valueOf(); // Object.valueOf() returns this (so unchanged if not overridden).
            const type = typeof value;
            if (type === 'number' && this.evalNumber !== undefined) {
                return this.evalNumber(value, write);
            }
            else if (this.evalString !== undefined) {
                return this.evalString(value.toString(), write);
            }
            else {
                throw new Error(`Operator '${this.operator}' does not support object types`);
            }
        }
    }
    getType() {
        return this.operand.getType();
    }
    toString() {
        return this.operator + this.operand.toString();
    }
    isStale() {
        return this.operand.isStale();
    }
    get readOnly() {
        return this.operand.readOnly;
    }
    // eslint-disable-next-line @typescript-eslint/no-empty-function
    onValueChanged() {
    }
    setDeferredMode(deferredMode, progress = nullProgressCounter, forceWrite = false) {
        this.operand.setDeferredMode(deferredMode, progress, forceWrite);
    }
    getValueCommitted() {
        this.operand.getValueCommitted();
    }
    clearDeferredWrite() {
        this.operand.clearDeferredWrite();
    }
    isDeferredWritePending() {
        return this.operand.isDeferredWritePending();
    }
}

/**
 *  Copyright (c) 2020, 2022 Texas Instruments Incorporated
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
const OP$f = '-';
class Factory$f extends AbstractUnaryOperatorFactory {
    constructor() {
        super(...arguments);
        this.operator = OP$f;
    }
    createOperator(operand) {
        // eslint-disable-next-line @typescript-eslint/no-use-before-define
        return new NegationOperator(operand);
    }
}
class NegationOperator extends AbstractUnaryOperator {
    constructor(operand) {
        super(operand);
        this.operator = OP$f;
        this.evalNumber = function (value) {
            return -value;
        };
    }
}
NegationOperator.factory = new Factory$f();

class AbstractLookupOperator {
    constructor(lookupBinding, indexBindings) {
        this.lookupBinding = lookupBinding;
        this.indexBindings = indexBindings;
        this.cachedIndices = [];
        this.onValueChangedListener = this.onValueChanged.bind(this);
        for (let j = indexBindings.length; j-- > 0;) {
            // add listeners to index changes.
            indexBindings[j].addEventListener(valueChangedEventType, this.onValueChangedListener);
        }
    }
    get status() {
        let status = this.lookupBinding.status;
        for (let i = 0; status === null && i < this.indexBindings.length; i++) {
            status = this.indexBindings[i].status;
        }
        return status;
    }
    set status(status) {
        this.lookupBinding.status = status;
    }
    dispose() {
        if (isDisposable(this.lookupBinding)) {
            this.lookupBinding.dispose();
        }
        for (let i = this.indexBindings.length; i-- > 0;) {
            const indexBinding = this.indexBindings[i];
            indexBinding.removeEventListener(valueChangedEventType, this.onValueChangedListener);
            if (isDisposable(indexBinding)) {
                indexBinding.dispose();
            }
        }
    }
    getType() {
        return this.lookupBinding.getType();
    }
    isStale() {
        let result = this.lookupBinding.isStale();
        for (let i = this.indexBindings.length; result === false && i-- > 0;) {
            result = this.indexBindings[i].isStale();
        }
        return result;
    }
    get readOnly() {
        return this.lookupBinding.readOnly;
    }
    addEventListener(type, listener) {
        this.lookupBinding.addEventListener(type, listener);
    }
    removeEventListener(type, listener) {
        this.lookupBinding.removeEventListener(type, listener);
    }
    setIndex(...args) {
        const indices = [];
        let i = 0;
        for (; i < this.indexBindings.length; i++) {
            const indexBinding = this.indexBindings[i];
            if (indexBinding.isStale()) {
                // postpone calling setIndex on lookupBinding until all !indices have
                // non stale values.  We only have to listen to one stale index at a time.
                if (this.staleIndexBinding === undefined) {
                    const listener = () => {
                        indexBinding.removeEventListener(staleChangedEventType, listener);
                        this.setIndex(...this.cachedIndices);
                    };
                    indexBinding.addEventListener(staleChangedEventType, listener);
                }
                this.cachedIndices = args;
                return;
            }
            indices.push(indexBinding.getValue());
        }
        for (i = 0; i < args.length; i++) {
            indices.push(args[i]);
        }
        this.lookupBinding.setIndex(...indices);
    }
    // eslint-disable-next-line @typescript-eslint/no-empty-function
    onIndexChanged() {
    }
    getValue() {
        return this.lookupBinding.getValue();
    }
    setValue(value, progress, forceWrite) {
        this.lookupBinding.setValue(value, progress, forceWrite);
    }
    updateValue(value, progress, skipStreamingListeners) {
        this.lookupBinding.updateValue(value, progress, skipStreamingListeners);
    }
    onValueChanged() {
        this.setIndex();
    }
    toString() {
        let result = this.lookupBinding.toString() + this.operator.charAt(0) + this.indexBindings[0].toString();
        for (let i = 1; i < this.indexBindings.length; i++) {
            result += ', ' + this.indexBindings[i].toString();
        }
        return result + this.operator.charAt(1);
    }
    setDeferredMode(deferredMode, progress = nullProgressCounter, forceWrite = false) {
        this.lookupBinding.setDeferredMode(deferredMode, progress, forceWrite);
    }
    getValueCommitted() {
        return this.lookupBinding.getValueCommitted();
    }
    clearDeferredWrite() {
        this.lookupBinding.clearDeferredWrite();
    }
    isDeferredWritePending() {
        return this.lookupBinding.isDeferredWritePending();
    }
}
function testLookupBinding(lookupBinding, operator) {
    if (lookupBinding === null) {
        throw new Error(`Missing the left operand for the ${operator} operator.`);
    }
    if (!(lookupBinding.setIndex)) {
        const text = operator === '()' ? 'a function' : operator === '.' ? 'an object' : 'an array';
        throw new Error(`'${lookupBinding.toString()}' is not ${text} type.  It cannot be used with the ${operator} operator.`);
    }
}

/**
 *  Copyright (c) 2020, 2022 Texas Instruments Incorporated
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
class AbstractDataFormatter extends AbstractUnaryOperator {
    constructor() {
        super(...arguments);
        this.formattedType = 'string';
    }
    getType() {
        return this.formattedType;
    }
    getValue() {
        let value = this.operand.getValue();
        if (value !== null && value !== undefined) {
            if (this.unFormattedType) {
                value = DataConverter.convert(value, this.operand.getType(), this.unFormattedType);
            }
            value = this.formatValue(value, this.precision);
        }
        return value;
    }
    setValue(value, progress, forceWrite) {
        if (value !== null && value !== undefined) {
            if (this.unFormatValue) {
                value = this.unFormatValue(value, this.precision);
            }
            value = DataConverter.convert(value, undefined, this.operand.getType());
        }
        this.operand.setValue(value, progress, forceWrite);
    }
    toString() {
        return this.operand.toString() + '.$' + this.operator;
    }
}

/**
 *  Copyright (c) 2020, 2024 Texas Instruments Incorporated
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
const QUALIFIER_PREFIX = '.$';
const QUALIFIER_PARAM_REGEX = /\d+$/;
class QualifierFactoryMap {
    constructor() {
        this.instanceQualifierFactoryMap = {};
    }
    static add(name, factory) {
        this.globalQualifierFactoryMap[QUALIFIER_PREFIX + name] = factory;
    }
    add(name, factory) {
        this.instanceQualifierFactoryMap[QUALIFIER_PREFIX + name] = factory;
    }
    static getQualifier(name, instanceQualifierFactoryMap) {
        const pos = name.lastIndexOf(QUALIFIER_PREFIX);
        if (pos > 0) {
            let qualifierName = name.substring(pos).toLowerCase();
            const paramArray = qualifierName.match(QUALIFIER_PARAM_REGEX);
            let param;
            if (paramArray) {
                qualifierName = qualifierName.substring(0, qualifierName.length - paramArray[0].length);
                param = +paramArray[0];
            }
            let qualifierFactory = this.globalQualifierFactoryMap[qualifierName];
            if (instanceQualifierFactoryMap) {
                qualifierFactory = instanceQualifierFactoryMap[qualifierName] || qualifierFactory;
            }
            if (qualifierFactory) {
                return { bindName: name.substring(0, pos), qualifier: qualifierFactory, param: param };
            }
        }
        return { bindName: name };
    }
    getQualifier(name) {
        return QualifierFactoryMap.getQualifier(name, this.instanceQualifierFactoryMap);
    }
}
QualifierFactoryMap.globalQualifierFactoryMap = {};
function doPrecision(value, precision = 0) {
    if (precision > 0) {
        if (value.length > precision) {
            value = value.substring(value.length - precision);
        }
        else {
            for (let len = value.length; len < precision; len++) {
                value = '0' + value;
            }
        }
    }
    return value;
}
class HexFormatter extends AbstractDataFormatter {
    constructor(operand, precision) {
        super(operand);
        this.precision = precision;
        this.operator = 'hex';
    }
    static create(operand, precision) {
        return new HexFormatter(operand, precision);
    }
    formatValue(input, precision) {
        input = +input;
        if (isNaN(input)) {
            return '0x' + input;
        }
        if (input < 0) {
            input = Number(1n << BigInt((precision ?? 8) * 4)) + input;
        }
        const inputText = input.toString(16).toUpperCase();
        return '0x' + doPrecision(inputText, precision);
    }
}
DataConverter.register({ convert: HexFormatter.prototype.formatValue }, 'hex');
QualifierFactoryMap.add('hex', HexFormatter);
class DecimalFormatter extends AbstractDataFormatter {
    constructor(operand, precision) {
        super(operand);
        this.precision = precision;
        this.operator = 'dec';
    }
    static create(operand, precision) {
        return new DecimalFormatter(operand, precision);
    }
    formatValue(input, precision) {
        input = +input;
        if (isNaN(input) || precision === undefined) {
            return '' + input;
        }
        return input.toFixed(precision);
    }
}
DataConverter.register({ convert: DecimalFormatter.prototype.formatValue }, 'dec');
QualifierFactoryMap.add('dec', DecimalFormatter);
class ScientificFormatter extends AbstractDataFormatter {
    constructor(operand, precision) {
        super(operand);
        this.precision = precision;
        this.operator = 'exp';
    }
    static create(operand, precision) {
        return new ScientificFormatter(operand, precision);
    }
    formatValue(input, precision) {
        input = +input;
        if (isNaN(input)) {
            return '' + input;
        }
        return input.toExponential(precision);
    }
}
DataConverter.register({ convert: ScientificFormatter.prototype.formatValue }, 'exp');
QualifierFactoryMap.add('exp', ScientificFormatter);
class BinaryFormatter extends AbstractDataFormatter {
    constructor(operand, precision) {
        super(operand);
        this.precision = precision;
        this.operator = 'binary';
        this.unFormattedType = 'number';
    }
    static create(operand, precision) {
        return new BinaryFormatter(operand, precision);
    }
    formatValue(input, precision) {
        input = +input;
        if (isNaN(input)) {
            return '' + input;
        }
        if (input < 0) {
            input = 0xFFFFFFFF + input + 1;
        }
        return doPrecision(input.toString(2), precision);
    }
    unFormatValue(input) {
        return Number.parseInt(input, 2);
    }
}
DataConverter.register({ convert: BinaryFormatter.prototype.formatValue }, 'binary');
DataConverter.register({ convert: BinaryFormatter.prototype.unFormatValue }, 'number', 'binary');
QualifierFactoryMap.add('binary', BinaryFormatter);

/**
 *  Copyright (c) 2020, 2022 Texas Instruments Incorporated
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
/* eslint-disable @typescript-eslint/no-unused-vars */
const OP$e = 'Q()';
class Factory$e extends AbstractBinaryOperatorFactory {
    constructor() {
        super(...arguments);
        this.operator = OP$e;
    }
    parse(uri, factory, precedence) {
        const pos = factory.findFirstIndexOf(uri, ',');
        if (pos <= 0 || pos >= uri.length - 1 || pos !== factory.findLastIndexOf(uri, ',')) {
            throw new Error('Invalid number of parameters for Q() function.  The Q() function requires two and only two parameters separated by a single comma.');
        }
        let operandText = uri.substring(0, pos);
        const leftOperand = factory.parseExpression(operandText, precedence);
        operandText = uri.substring(pos + ','.length);
        const rightOperand = factory.parseExpression(operandText, precedence);
        if (leftOperand === null || rightOperand === null) {
            throw new Error(`Missing operands for the ${this.operator} operator.`);
        }
        return this.createOperator(leftOperand, rightOperand);
    }
    createOperator(leftOperand, rightOperand) {
        // eslint-disable-next-line @typescript-eslint/no-use-before-define
        return new QFunctionOperator(leftOperand, rightOperand);
    }
}
class QFunctionOperator extends AbstractBinaryOperator {
    constructor(leftOperand, rightOperand) {
        super(leftOperand, rightOperand);
        this.operator = OP$e;
    }
    getValue() {
        const value = +this.leftOperand.getValue();
        const q = +this.rightOperand.getValue();
        // eslint-disable-next-line @typescript-eslint/no-use-before-define
        return formatValue(value, q);
    }
    setValue(newValue, progress, forceWrite) {
        newValue = +newValue;
        const q = +this.rightOperand.getValue();
        // eslint-disable-next-line @typescript-eslint/no-use-before-define
        this.leftOperand.setValue(unFormatValue(newValue, q), progress, forceWrite);
    }
    toString() {
        return 'Q(' + this.leftOperand.toString() + ', ' + this.rightOperand.toString() + ')';
    }
    // eslint-disable-next-line @typescript-eslint/no-empty-function
    doSetValue(lparam, rparam, write) {
    }
    getType() {
        return 'number';
    }
}
QFunctionOperator.factory = new Factory$e();
function formatValue(value, q) {
    if (isNaN(value)) {
        return value;
    }
    if (isNaN(q)) {
        return q;
    }
    return value / (Math.pow(2, q));
}
function unFormatValue(value, q) {
    if (isNaN(q)) {
        value = q;
    }
    else if (!isNaN(value)) {
        value = Math.round(value * Math.pow(2, q));
    }
    return value;
}
DataConverter.register({ convert: formatValue }, 'q');
DataConverter.register({ convert: unFormatValue }, 'number', 'q');
QualifierFactoryMap.add('q', class extends QFunctionOperator {
    constructor(leftOperand, qValue = 0) {
        super(leftOperand, new NumberLiteral(qValue));
    }
    static create(leftOperand, qValue = 0) {
        return new this(leftOperand, qValue);
    }
});

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
const OP$d = '.';
class Factory$d {
    constructor() {
        this.operator = OP$d;
    }
    parseQualifiers(leftOperand, operandText) {
        const { bindName, qualifier, param } = QualifierFactoryMap.getQualifier('.' + operandText);
        if (qualifier) {
            const bind = this.parseQualifiers(leftOperand, bindName.substring(1));
            return bind && qualifier.create(bind, param);
        }
        if (operandText.length > 0) {
            // eslint-disable-next-line @typescript-eslint/no-use-before-define
            return new DotOperator(leftOperand, operandText);
        }
        return leftOperand;
    }
    parse(uri, factory, precedence) {
        // dot operator is only allowed after array or function syntax.  Otherwise it is just part of the identifier for the model binding.
        let pos = factory.findLastIndexOf(uri, '].', true);
        if (pos < 0) {
            pos = factory.findLastIndexOf(uri, ').', true);
        }
        // can't be first or last character, because it's not a unary operator
        if (pos > 0 && pos < uri.length - 1) {
            pos++;
            let operandText = uri.substring(0, pos);
            const leftOperand = factory.parseExpression(operandText, precedence, true);
            if (leftOperand) {
                testLookupBinding(leftOperand, this.operator);
                operandText = uri.substring(pos + this.operator.length);
                ExpressionParserUtils.testIdentifier(operandText, ' in dot operator field name'); // throws exception if invalid identifier.
                return this.parseQualifiers(leftOperand, operandText);
            }
        }
        return null;
    }
}
class DotOperator extends AbstractLookupOperator {
    constructor(lookupBinding, fieldNameBinding) {
        super(lookupBinding, [new StringLiteral(fieldNameBinding)]);
        this.operator = OP$d;
    }
    toString() {
        return this.lookupBinding.toString() + '.' + this.indexBindings[0];
    }
}
DotOperator.factory = new Factory$d();

class AbstractLookupOperatorFactory {
    parse(uri, factory, precedence) {
        const openingBrace = this.operator.charAt(0);
        const closingBrace = this.operator.charAt(1);
        const endPos = factory.findLastIndexOf(uri, closingBrace, true);
        if (endPos >= 0) {
            if (endPos === uri.length - 1) {
                // valid lookup operation
                const pos = factory.findLastIndexOf(uri, openingBrace);
                if (pos === 0) {
                    // literal array or just plain parentheses
                    return this.parseLiteral(uri.substring(1, uri.length - 1), factory, precedence);
                }
                else if (pos < 0) {
                    // missing matching '[' or '(' operator.
                    throw new Error(`I found a '${closingBrace}' operator, but I couldn't find the matching '${openingBrace}' operator.  ` +
                        `To be honest I was expecting one in the following text: ${uri.substring(0, endPos + 1)}`);
                }
                else if (pos === endPos - 1) {
                    // empty middle paramenter
                    throw new Error(`I found an empty operator '${this.operator}'.  To be honest, I was expecting to find something inside.`);
                }
                else {
                    // empty right paramenter, this is the normal case, nothing following the <expression>[].
                    let arrayText = uri.substring(0, pos);
                    const indexText = uri.substring(pos + 1, endPos);
                    if (arrayText === 'Q') {
                        return QFunctionOperator.factory.parse(indexText, factory, 0);
                    }
                    // strip parenthesis (since we are not registering lookup bindings in binding Registry)
                    while (arrayText.charAt(0) === '(' && arrayText.charAt(arrayText.length - 1) === ')') {
                        precedence = 0; // reset precedence do to parentheses found
                        arrayText = arrayText.substring(1, arrayText.length - 1);
                    }
                    const lookupBinding = factory.parseExpression(arrayText, precedence, true);
                    if (lookupBinding) {
                        testLookupBinding(lookupBinding, this.operator); // throw exception if invalid binding found.
                        const indexBindings = [];
                        const parameters = indexText.split(',');
                        for (let i = 0; i < parameters.length; i++) {
                            const parameter = parameters[i];
                            if (parameter.length === 0) {
                                throw new Error('Empty array index or function parameter.  ' +
                                    'To be honest, I was expecting one or more parameters separated by commas, ' +
                                    'but found that one of the parameters was empty in: ' + indexText);
                            }
                            const indexBinding = factory.parseExpression(parameter, 0);
                            if (!indexBinding) {
                                throw new Error(`Index binding "${parameter}" does not exist`);
                            }
                            indexBindings.push(indexBinding);
                        }
                        return this.createOperator(lookupBinding, indexBindings);
                    }
                    else {
                        throw new Error(`Array binding '${arrayText}[] does not exist.`);
                    }
                }
            }
            else if (uri.charAt(endPos + 1) === '.' && endPos < uri.length - 2) {
                // dot operator found
                return DotOperator.factory.parse(uri, factory, precedence);
            }
            else { // extra trailing text.
                throw new Error(`I found an operator '${this.operator}' with unexpected characters following it.  ` +
                    `To be honest, I was not expecting to find another operator after the last '${closingBrace}` +
                    ` in the following text: ${uri.substring(endPos + 1)}`);
            }
        }
        return null;
    }
}

/**
 *  Copyright (c) 2020, 2022 Texas Instruments Incorporated
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
const openingBracket = '[';
const closingBracket = ']';
const separator = ',';
class ArrayLiteral extends AbstractLiteralBinding {
    constructor(valueArray) {
        super(valueArray);
    }
    toString() {
        let text = openingBracket + (this.cachedValue.length === 0 ? '' : this.cachedValue[0].toString());
        for (let i = 1; i < this.cachedValue.length; i++) {
            text += separator + this.cachedValue[i].toString();
        }
        return text + closingBracket;
    }
    static parseLiteral(uri) {
        const values = uri.split(separator);
        if (values === null || values.length === 0) {
            return new ArrayLiteral([]);
        }
        else if (values.length === 1) {
            return new ArrayLiteral([values[0]]);
        }
        const stringLiterals = [];
        let numberLiterals = [];
        let booleanLiterals = [];
        for (let i = 0; i < values.length; i++) {
            const value = values[i].trim();
            if (value.length > 0) {
                stringLiterals.push(value);
                if (booleanLiterals !== null) {
                    const booleanLiteral = BooleanLiteral.parse(value);
                    if (booleanLiteral !== null) {
                        booleanLiterals.push(booleanLiteral);
                    }
                    else {
                        booleanLiterals = null;
                    }
                }
                if (numberLiterals !== null) {
                    const numberLiteral = NumberLiteral.parse(value);
                    if (numberLiteral !== null) {
                        numberLiterals.push(numberLiteral);
                    }
                    else {
                        numberLiterals = null;
                    }
                }
            }
            else {
                // empty item
                stringLiterals.push('');
                if (numberLiterals !== null) {
                    numberLiterals.push(0);
                }
                if (booleanLiterals !== null) {
                    booleanLiterals.push(false);
                }
            }
        }
        return new ArrayLiteral(booleanLiterals || numberLiterals || stringLiterals);
    }
}

/**
 *  Copyright (c) 2020, 2022 Texas Instruments Incorporated
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
const OP$c = '[]';
class Factory$c extends AbstractLookupOperatorFactory {
    constructor() {
        super(...arguments);
        this.operator = OP$c;
    }
    createOperator(lookupBinding, indexBinding) {
        // eslint-disable-next-line @typescript-eslint/no-use-before-define
        return new ArrayOperator(lookupBinding, indexBinding);
    }
    // eslint-disable-next-line @typescript-eslint/no-unused-vars
    parseLiteral(uri, factory, precedence) {
        return ArrayLiteral.parseLiteral(uri);
    }
}
class ArrayOperator extends AbstractLookupOperator {
    constructor(lookupBinding, indexBinding) {
        super(lookupBinding, indexBinding);
        this.operator = OP$c;
    }
}
ArrayOperator.factory = new Factory$c();

/**
 *  Copyright (c) 2020, 2022 Texas Instruments Incorporated
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
const OP$b = '>=';
class Factory$b extends AbstractComparisonOperatorFactory {
    constructor() {
        super(...arguments);
        this.operator = OP$b;
    }
    createOperator(leftOperand, rightOperand) {
        // eslint-disable-next-line @typescript-eslint/no-use-before-define
        return new GreaterThanOrEqualsOperator(leftOperand, rightOperand);
    }
}
function doEval$3(left, right) {
    return left >= right;
}
class GreaterThanOrEqualsOperator extends AbstractComparisonOperator {
    constructor() {
        super(...arguments);
        this.operator = OP$b;
        this.evalNumber = doEval$3;
        this.evalString = doEval$3;
    }
}
GreaterThanOrEqualsOperator.factory = new Factory$b();

/**
 *  Copyright (c) 2020, 2022 Texas Instruments Incorporated
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
const OP$a = '>';
class Factory$a extends AbstractComparisonOperatorFactory {
    constructor() {
        super(...arguments);
        this.operator = OP$a;
    }
    createOperator(leftOperand, rightOperand) {
        // eslint-disable-next-line @typescript-eslint/no-use-before-define
        return new GreaterThanOperator(leftOperand, rightOperand);
    }
}
function doEval$2(left, right) {
    return left > right;
}
class GreaterThanOperator extends AbstractComparisonOperator {
    constructor() {
        super(...arguments);
        this.operator = OP$a;
        this.evalNumber = doEval$2;
        this.evalString = doEval$2;
    }
}
GreaterThanOperator.factory = new Factory$a();

/**
 *  Copyright (c) 2020, 2022 Texas Instruments Incorporated
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
const OP$9 = '()';
class Factory$9 extends AbstractLookupOperatorFactory {
    constructor() {
        super(...arguments);
        this.operator = OP$9;
    }
    createOperator(lookupBinding, indexBinding) {
        // eslint-disable-next-line @typescript-eslint/no-use-before-define
        return new FunctionOperator(lookupBinding, indexBinding);
    }
    parseLiteral(uri, factory) {
        return factory.parseExpression(uri, 0); // reset precedence to look for operators inside parentheses.
    }
}
class FunctionOperator extends AbstractLookupOperator {
    constructor() {
        super(...arguments);
        this.operator = OP$9;
    }
}
FunctionOperator.factory = new Factory$9();

const OP$8 = '||';
class Factory$8 extends AbstractBinaryOperatorFactory {
    constructor() {
        super(...arguments);
        this.operator = OP$8;
    }
    createOperator(leftOperand, rightOperand) {
        // eslint-disable-next-line @typescript-eslint/no-use-before-define
        return new LogicalOrOperator(leftOperand, rightOperand);
    }
}
class LogicalOrOperator extends AbstractComparisonOperator {
    constructor() {
        super(...arguments);
        this.operator = OP$8;
        this.evalBoolean = function (left, right) {
            return left || right;
        };
        this.evalNumber = function (left, right) {
            // eslint-disable-next-line eqeqeq
            return left != 0 || right != 0;
        };
    }
}
LogicalOrOperator.factory = new Factory$8();

/**
 *  Copyright (c) 2020, 2022 Texas Instruments Incorporated
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
const OP$7 = '&&';
class Factory$7 extends AbstractComparisonOperatorFactory {
    constructor() {
        super(...arguments);
        this.operator = OP$7;
    }
    createOperator(leftOperand, rightOperand) {
        // eslint-disable-next-line @typescript-eslint/no-use-before-define
        return new LogicalAndOperator(leftOperand, rightOperand);
    }
}
class LogicalAndOperator extends AbstractComparisonOperator {
    constructor() {
        super(...arguments);
        this.operator = OP$7;
        this.evalBoolean = function (left, right) {
            return left && right;
        };
        this.evalNumber = function (left, right) {
            // eslint-disable-next-line eqeqeq
            return left != 0 && right != 0;
        };
    }
}
LogicalAndOperator.factory = new Factory$7();

const OP$6 = '<=';
class Factory$6 extends AbstractComparisonOperatorFactory {
    constructor() {
        super(...arguments);
        this.operator = OP$6;
    }
    createOperator(leftOperand, rightOperand) {
        // eslint-disable-next-line @typescript-eslint/no-use-before-define
        return new LessThanOrEqualsOperator(leftOperand, rightOperand);
    }
}
function doEval$1(left, right) {
    return left <= right;
}
class LessThanOrEqualsOperator extends AbstractComparisonOperator {
    constructor() {
        super(...arguments);
        this.operator = OP$6;
        this.evalNumber = doEval$1;
        this.evalString = doEval$1;
    }
}
LessThanOrEqualsOperator.factory = new Factory$6();

const OP$5 = '<';
class Factory$5 extends AbstractComparisonOperatorFactory {
    constructor() {
        super(...arguments);
        this.operator = OP$5;
    }
    createOperator(leftOperand, rightOperand) {
        // eslint-disable-next-line @typescript-eslint/no-use-before-define
        return new LessThanOperator(leftOperand, rightOperand);
    }
}
function doEval(left, right) {
    return left < right;
}
class LessThanOperator extends AbstractComparisonOperator {
    constructor() {
        super(...arguments);
        this.operator = OP$5;
        this.evalNumber = doEval;
        this.evalString = doEval;
    }
}
LessThanOperator.factory = new Factory$5();

const OP$4 = '-';
class Factory$4 extends AbstractBinaryOperatorFactory {
    constructor() {
        super(...arguments);
        this.operator = OP$4;
    }
    createOperator(leftOperand, rightOperand) {
        // eslint-disable-next-line @typescript-eslint/no-use-before-define
        return new SubtractionOperator(leftOperand, rightOperand);
    }
}
class SubtractionOperator extends AbstractBinaryOperator {
    constructor() {
        super(...arguments);
        this.operator = OP$4;
        this.evalNumber = function (left, right) {
            return left - right;
        };
    }
    doSetValue(value, constant, isLeftParamConstant) {
        return isLeftParamConstant ? constant - value : value + constant;
    }
    getType() {
        return 'number';
    }
}
SubtractionOperator.factory = new Factory$4();

const OP$3 = '*';
class Factory$3 extends AbstractBinaryOperatorFactory {
    constructor() {
        super(...arguments);
        this.operator = OP$3;
    }
    createOperator(leftOperand, rightOperand) {
        // eslint-disable-next-line @typescript-eslint/no-use-before-define
        return new MultiplicationOperator(leftOperand, rightOperand);
    }
}
class MultiplicationOperator extends AbstractBinaryOperator {
    constructor() {
        super(...arguments);
        this.operator = OP$3;
        this.evalNumber = function (left, right) {
            return left * right;
        };
    }
    // eslint-disable-next-line @typescript-eslint/no-unused-vars
    doSetValue(value, constant, isLeftParamConstant) {
        return value / constant;
    }
    getType() {
        return 'number';
    }
}
MultiplicationOperator.factory = new Factory$3();

/* eslint-disable @typescript-eslint/no-unused-vars */
const OP$2 = '%';
class Factory$2 extends AbstractBinaryOperatorFactory {
    constructor() {
        super(...arguments);
        this.operator = OP$2;
    }
    createOperator(leftOperand, rightOperand) {
        // eslint-disable-next-line @typescript-eslint/no-use-before-define
        return new RemainderOperator(leftOperand, rightOperand);
    }
}
class RemainderOperator extends AbstractBinaryOperator {
    constructor() {
        super(...arguments);
        this.operator = OP$2;
        this.evalNumber = function (left, right) {
            return left % right;
        };
    }
    getType() {
        return 'number';
    }
    // eslint-disable-next-line @typescript-eslint/no-empty-function
    doSetValue(value, constant, isLeftParamConstant) {
    }
    get readOnly() {
        return true;
    }
}
RemainderOperator.factory = new Factory$2();

const OP$1 = '!';
class Factory$1 extends AbstractUnaryOperatorFactory {
    constructor() {
        super(...arguments);
        this.operator = OP$1;
    }
    createOperator(operand) {
        // eslint-disable-next-line @typescript-eslint/no-use-before-define
        return new LogicalNotOperator(operand);
    }
}
class LogicalNotOperator extends AbstractUnaryOperator {
    constructor() {
        super(...arguments);
        this.operator = OP$1;
        // eslint-disable-next-line @typescript-eslint/no-unused-vars
        this.evalBoolean = function (value, write) {
            return !value;
        };
        this.evalNumber = function (value, write) {
            if (write) {
                return value ? 0 : 1;
            }
            return !value;
        };
    }
    getType() {
        return 'boolean';
    }
}
LogicalNotOperator.factory = new Factory$1();

const OP = '~';
class Factory extends AbstractUnaryOperatorFactory {
    constructor() {
        super(...arguments);
        this.operator = OP;
    }
    createOperator(operand) {
        // eslint-disable-next-line @typescript-eslint/no-use-before-define
        return new ArithmeticNotOperator(operand);
    }
}
class ArithmeticNotOperator extends AbstractUnaryOperator {
    constructor() {
        super(...arguments);
        this.operator = OP;
        // eslint-disable-next-line @typescript-eslint/no-unused-vars
        this.evalNumber = function (value, write) {
            return Number(~BigInt(Math.trunc(value)));
        };
    }
}
ArithmeticNotOperator.factory = new Factory();

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
class ExpressionParser extends AbstractBindExpressionParser {
    constructor(bindProvider, bindings) {
        super(bindings);
        this.bindProvider = bindProvider;
        // add brackets that exclude operators
        this.addBraces('[', ']'); // array operator
        this.addBraces('\'', '\''); // string literal single quotes
        // add operator factories for parser here in reverse precedence order
        // Priority 13: conditional ?: operator
        this.addOperatorFactory(ConditionalOperator.factory);
        // Priority 12: logical or || operator.
        this.addOperatorFactory(LogicalOrOperator.factory);
        // Priority 11: logical and && operator.
        this.addOperatorFactory(LogicalAndOperator.factory);
        // Priority 10: bit wise or | operator.
        // Priority 9: bit wise xor ^ operator.
        // Priority 8: bit wise and & operator.
        // Priority 7: equality == and != operators
        this.addOperatorFactory(EqualsOperator.factory, NotEqualsOperator.factory);
        // Priority 6: comparison >, >=, <, <= operators
        this.addOperatorFactory(GreaterThanOrEqualsOperator.factory, LessThanOrEqualsOperator.factory, GreaterThanOperator.factory, LessThanOperator.factory);
        // Priority 5: shift >>, <<, >>> operators
        // Priority 4: arithmetic +, - operators
        this.addOperatorFactory(AdditionOperator.factory, SubtractionOperator.factory);
        // Priority 3: arithmetic *, /, % operators
        this.addOperatorFactory(MultiplicationOperator.factory, DivisionOperator.factory, RemainderOperator.factory);
        // Priority 2: unary operators
        this.addOperatorFactory(NegationOperator.factory, ArithmeticNotOperator.factory, LogicalNotOperator.factory);
        // Priority 1: array index [] operator, and function() operator
        this.addOperatorFactory(ArrayOperator.factory);
        this.addOperatorFactory(FunctionOperator.factory);
    }
    parseQualifiers(model, modelName, uri, isLookupBinding) {
        const { bindName, qualifier, param } = model.parseQualifier(uri);
        if (qualifier) {
            let bind = isLookupBinding ? null : this.bindings.get(modelName + bindName) || null;
            bind = bind || this.parseQualifiers(model, modelName, bindName, isLookupBinding);
            return bind ? qualifier.create(bind, param) : null;
        }
        if (isLookupBinding) {
            return model.createNewBind(bindName);
        }
        return model.getBinding(bindName);
    }
    bindValue(uri, isLookupBinding = false) {
        if (uri.length === 0) {
            throw new Error('Empty Param');
        }
        const { model, bindName } = this.bindProvider.parseModelFromBinding(uri);
        const modelName = uri.substring(0, uri.length - bindName.length);
        return this.parseQualifiers(model, modelName, bindName, isLookupBinding);
    }
}

/**
 * Abstract class that provides default implementation of IBindFactory.  This class
 * implements the getName() method for IBindFactory.
*/
class AbstractBindProvider {
    /**
     * Constructor for AbstractBindProvider.
     *
     * @param bindings initial bindings to start with.
     */
    constructor(bindings) {
        this.expressionParser = new ExpressionParser(this, bindings);
    }
    /**
     * If the cache contains an IBindValue with the given name, this method will
     * returns it. Otherwise the binding is created by first evaluating any
     * expression then by using the registered models to create the appropriate
     * bindings to satisfy the bind expression.
     *
     * @param name the name of the binding.
     * @returns  the binding if found in the cache or created; otherwise, null.
     */
    getBinding(name) {
        return this.expressionParser.parseExpression(name);
    }
    dispose() {
        this.expressionParser.dispose();
    }
    /**
     * Method primarily used for testing.  It returns a count of the total number of data bindings.
     *
     * @private
     * @returns number of data bindings
     */
    getBindingCount() {
        return this.expressionParser.getBindingCount();
    }
}

/**
 *  Copyright (c) 2020, 2022 Texas Instruments Incorporated
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
class AbstractBindListener {
    constructor(srcBinding, destBinding) {
        this.srcBinding = srcBinding;
        this.destBinding = destBinding;
        this.statusChangedHandler = () => this.destBinding.status = this.srcBinding.status;
    }
}
class StreamingListener extends AbstractBindListener {
    constructor(srcBinding, destBinding, computeValue) {
        super(srcBinding, destBinding);
        this.computeValue = computeValue;
        this.dataReceivedHandler = () => this.onDataReceived();
    }
    enable() {
        this.srcBinding.addEventListener(statusChangedEventType, this.statusChangedHandler);
        this.srcBinding.addEventListener(streamingDataEventType, this.dataReceivedHandler);
    }
    disable() {
        this.srcBinding.removeEventListener(statusChangedEventType, this.statusChangedHandler);
        this.srcBinding.removeEventListener(streamingDataEventType, this.dataReceivedHandler);
    }
    onDataReceived() {
        let newValue = this.srcBinding.getValue(); // always calculate new value in case srcBinding is an expression that needs to be evaluated.
        let srcType = this.srcBinding.getType();
        if (this.computeValue) {
            newValue = this.computeValue(newValue);
            srcType = undefined;
        }
        newValue = DataConverter.convert(newValue, srcType, this.destBinding.getType());
        this.destBinding.onStreamingDataReceived(newValue);
    }
}
class BindingListener extends AbstractBindListener {
    constructor(srcBinding, destBinding, computeValue) {
        super(srcBinding, destBinding);
        this.computeValue = computeValue;
        this.valueChangedHandler = (details) => this.onValueChanged(details.progress);
        this.staleChangedHandler = () => this.onStaleChanged();
    }
    onValueChanged(progress) {
        if (this.srcBinding.isStale()) {
            // defer passing the data along until the value has fully changed.
            this.srcBinding.addEventListener(staleChangedEventType, this.staleChangedHandler);
        }
        else {
            let newValue = this.srcBinding.getValue();
            const oldValue = this.destBinding.getValue();
            let srcType = this.srcBinding.getType();
            if (this.computeValue) {
                newValue = this.computeValue(newValue);
                srcType = undefined;
            }
            const destType = this.destBinding.getType();
            // protect against writing back values changed solely due to their conversion to and back again.
            // eslint-disable-next-line eqeqeq
            if (newValue != DataConverter.convert(oldValue, destType, srcType)) {
                newValue = DataConverter.convert(newValue, srcType, destType);
                this.destBinding.setValue(newValue, progress);
            }
        }
    }
    onStaleChanged() {
        if (!this.srcBinding.isStale()) {
            this.srcBinding.removeEventListener(staleChangedEventType, this.staleChangedHandler);
            this.onValueChanged(); // force the value to be synced
        }
    }
    enable() {
        this.srcBinding.addEventListener(statusChangedEventType, this.statusChangedHandler);
        this.srcBinding.addEventListener(valueChangedEventType, this.valueChangedHandler);
    }
    disable() {
        this.srcBinding.removeEventListener(statusChangedEventType, this.statusChangedHandler);
        this.srcBinding.removeEventListener(valueChangedEventType, this.valueChangedHandler);
    }
    get status() {
        return this.srcBinding.status;
    }
}
const nullListener = new (class {
    enable() {
        // do nothing
    }
    disable() {
        // do nothing
    }
    statusChangedHandler() {
        // do nothing
    }
});
class DataBinder {
    constructor(targetBinding, modelBinding, getter, setter, oneWay = false) {
        this.targetBinding = targetBinding;
        this.modelBinding = modelBinding;
        this.getter = getter;
        this.setter = setter;
        this.targetListener = nullListener;
        this.modelListener = nullListener;
        this._enabled = false;
        // support for readOnly bindings, don't write values.
        if (oneWay || (getter && !setter)) {
            this.modelListener = DataBinder.createListener(modelBinding, targetBinding, getter);
        }
        else if (setter && !getter) {
            // switch model and target, so model gets initialized from the target.
            this.modelListener = DataBinder.createListener(targetBinding, modelBinding, setter);
        }
        else {
            // two-way binding support (with both getter or setter, or neither getter or setter (no computation)
            this.targetListener = DataBinder.createListener(targetBinding, modelBinding, setter);
            this.modelListener = DataBinder.createListener(modelBinding, targetBinding, getter);
        }
        this.enabled = true;
    }
    set enabled(enable) {
        if (this._enabled !== enable) {
            this._enabled = enable;
            if (enable) {
                this.targetListener.enable();
                this.modelListener.enable();
                // force model to sync the target value in case it changed
                // between disable() and subsequent enable() calls.
                if (typeof this.modelListener.onValueChanged === 'function') {
                    this.modelListener.onValueChanged();
                }
                // force status to be reflected in target as it now is in the
                // model, in case it change between time.
                this.modelListener.statusChangedHandler();
            }
            else {
                this.targetListener.disable();
                this.modelListener.disable();
            }
        }
    }
    get enabled() {
        return this._enabled;
    }
    dispose() {
        this.enabled = false;
    }
    static bind(targetBinding, modelBinding, getter, setter, oneWay = false) {
        if (targetBinding !== null && modelBinding !== null) {
            return new DataBinder(targetBinding, modelBinding, getter, setter, oneWay);
        }
        GcConsole.error(NAME, 'Cannot bind target and model bindings together because one of them is not an IBindValue.');
        return null;
    }
}
DataBinder.createListener = function (srcBinding, targetBinding, computeValue) {
    if (targetBinding.onStreamingDataReceived) {
        return new StreamingListener(srcBinding, targetBinding, computeValue);
    }
    else {
        return new BindingListener(srcBinding, targetBinding, computeValue);
    }
};

class CollectionBindValue {
    constructor(bindings) {
        this.bindings = bindings;
        this._status = null;
    }
    getValue() {
        const values = {};
        this.bindings.forEach((binding, bindName) => {
            values[bindName] = binding.getValue();
        });
        return values;
    }
    setValue(value, progress, forceWrite) {
        this.bindings.forEach((binding, bindName) => {
            let newValue = value[bindName];
            if (newValue !== undefined) {
                newValue = DataConverter.convert(newValue, undefined, binding.getType());
                binding.setValue(newValue, progress, forceWrite);
            }
        });
    }
    updateValue(value, progress, skipStreamingListeners) {
        this.bindings.forEach((binding, bindName) => {
            let newValue = value[bindName];
            if (newValue !== undefined) {
                newValue = DataConverter.convert(newValue, undefined, binding.getType());
                binding.updateValue(value, progress, skipStreamingListeners);
            }
        });
    }
    getType() {
        return 'object';
    }
    addEventListener(type, listener) {
        this.bindings.forEach((binding) => {
            binding.addEventListener(type, listener);
        });
    }
    removeEventListener(type, listener) {
        this.bindings.forEach((binding) => {
            binding.removeEventListener(type, listener);
        });
    }
    isStale() {
        for (const binding of this.bindings.values()) {
            if (binding.isStale()) {
                return true;
            }
        }
        return false;
    }
    get readOnly() {
        for (const binding of this.bindings.values()) {
            if (binding.readOnly) {
                return true;
            }
        }
        return false;
    }
    get status() {
        if (this._status) {
            return this._status;
        }
        else {
            for (const binding of this.bindings.values()) {
                const status = binding.status;
                if (status) {
                    return status;
                }
            }
            return null;
        }
    }
    set status(status) {
        this._status = status;
    }
    setDeferredMode(deferredMode, progress = nullProgressCounter, forceWrite = false) {
        this.bindings.forEach((binding) => {
            binding.setDeferredMode(deferredMode, progress, forceWrite);
        });
    }
    getValueCommitted() {
        const values = {};
        this.bindings.forEach((binding, bindName) => {
            values[bindName] = binding.getValueCommitted();
        });
        return values;
    }
    clearDeferredWrite() {
        this.bindings.forEach((binding) => {
            binding.clearDeferredWrite();
        });
    }
    isDeferredWritePending() {
        for (const binding of this.bindings.values()) {
            if (binding.isDeferredWritePending()) {
                return true;
            }
        }
        return false;
    }
    onDisconnected() {
        this.bindings.forEach((binding) => {
            if (binding.onDisconnected) {
                binding.onDisconnected();
            }
        });
    }
}

class DataFormatterRegistry {
    static add(formatter) {
        const CustomDataFormatter = class extends AbstractDataFormatter {
            constructor(operand, precision) {
                super(operand);
                this.precision = precision;
                this.operator = formatter.operator;
                this.formattedType = formatter.formattedType;
                this.unFormattedType = formatter.unFormattedType;
                this.formatValue = formatter.formatValue;
                this.unFormatValue = formatter.unFormatValue;
            }
            static create(bind, param) {
                return new CustomDataFormatter(bind, param);
            }
        };
        QualifierFactoryMap.add(formatter.operator, CustomDataFormatter);
    }
}

/**
 *  Copyright (c) 2020, 2022 Texas Instruments Incorporated
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
/* eslint-disable @typescript-eslint/no-unused-vars */
/**
 * Class that implements IBindValue interface for a variable value binding.
 */
class VariableBindValue extends AbstractBindValue {
    /**
     * Constructor for VariableBindValue
     *
     * @param initialValue the constant value returned by this binding.
     * @param readOnly flag indicating if this binding is a constant (not writable by setValue()).
     */
    constructor(initialValue, readOnly = false) {
        super();
        this.cachedValue = initialValue;
        this._readOnly = readOnly;
    }
    setValue(value, progress, forceWrite) {
        if (!this.readOnly) {
            super.setValue(value, progress, forceWrite);
        }
    }
    get readOnly() {
        return this._readOnly;
    }
    // eslint-disable-next-line @typescript-eslint/no-empty-function
    onValueChanged(details) {
    }
}

const TARGET_CONNECTED_BIND_NAME = '$target_connected';
class ModelBindProvider extends AbstractBindProvider {
    constructor(model) {
        super(new Map([['this', new VariableBindValue(undefined)]]));
        this.model = model;
    }
    parseModelFromBinding(name) {
        return { model: this.model, bindName: name };
    }
}
/**
 * Abstract class that provides default implementation of IBindFactory.  This class
 * implements the getName() method for IBindFactory.
*/
class AbstractBindFactory extends Events {
    /*
     * @param id uniquely identifiable name for this bind factory.
    */
    constructor(id) {
        super();
        this.id = id;
        this.modelQualifiers = new QualifierFactoryMap();
        this.modelBindings = new Map();
        this.modelBindings.set(TARGET_CONNECTED_BIND_NAME, new VariableBindValue(false, true));
    }
    getBinding(name) {
        // ensure aliased bindings like "uart.temp" and "target_dev.temp" return the same instance of the model's binding.
        // We do this by storing model bindings in the model factory so we can lookup aliased bindings.
        let bind = this.modelBindings.get(name) || null;
        if (!bind) {
            bind = this.createNewBind(name);
            if (bind) {
                bind.name = name;
            }
            this.modelBindings.set(name, bind);
        }
        return bind;
    }
    hasBinding(bindingName) {
        return this.modelBindings.has(bindingName);
    }
    getAllBindings() {
        return this.modelBindings;
    }
    parseModelFromBinding(uri) {
        return { model: this, bindName: uri };
    }
    parseQualifier(uri) {
        return this.modelQualifiers.getQualifier(uri);
    }
    /**
     * Method to set the connected or disconnected state of the model.  This method
     * is called by the transport when a connecting is established or broken.  The connected
     * state is available as a binding, "$target_connected", to app developers if they
     * need to show the connected state of a transport.
     *
     * @param newState true if to set state to connected, otherwise new state is disconnected.
     */
    setConnectedState(newState) {
        // eslint-disable-next-line @typescript-eslint/no-non-null-assertion
        this.modelBindings.get(TARGET_CONNECTED_BIND_NAME).updateValue(newState);
        if (newState && this.connectDeferred) {
            this.connectDeferred.resolve();
            this.connectDeferred = undefined;
        }
    }
    /**
     * Query method to determine if the model is connected or disconnected from a target.
     *
     * @returns true if the model is connected to a target, otherwise false.
     */
    isConnected() {
        // eslint-disable-next-line @typescript-eslint/no-non-null-assertion
        return this.modelBindings.get(TARGET_CONNECTED_BIND_NAME).getValue();
    }
    /**
     * Method to register model specific qualifiers.  Qualifiers are registered by name with a factory method
     * for creating the qualifier on demand.  To use a qualifier on a binding, append '.$' plus the name of the
     * qualifier with an optional numeric argument; for example, "mybind.$q7" would apply the "q" value qualifier with 7 fractional bits.
     * All qualifiers can have an optional single value numeric argument.  This means that the qualifier name cannot end with numeric characters;
     * otherwise, they will be parsed as an argument instead of the qualifier name.  All models have the default "q", "hex", "dec", etc..., number
     * formatting qualifiers already registered.  Use this method to register additional, model specific qualifiers.
     *
     * @param name the name of the qualifier, without the '.$' prefix.
     * @param factory the factory method to create the qualifier on a specific binding.
     */
    addQualifier(name, factory) {
        this.modelQualifiers.add(name, factory);
    }
    /**
     * Helper method to get a promise that is resolved when the model is connected to a target.
     * Derived classes should use this to delay accessing the target until the model is connected.
     *
     * @returns a promise that is either already resolved, or will resolve the next time
     * the model is connected to a target through a transport.
     */
    whenConnected() {
        this.connectDeferred = this.connectDeferred || GcPromise.defer();
        return this.connectDeferred.promise;
    }
    /**
     * Implementation for reading value from the target.
     *
     * @param uri the name of the binding to read
     * @returns a promise that resolves to the value read.
     */
    scriptRead(uri) {
        const binding = this.getBinding(uri);
        if (binding) {
            return Promise.resolve(binding.getValue());
        }
        else {
            return Promise.reject(`Failed to read value since bind "${uri}" does not exist.`);
        }
    }
    /**
     * Implementation for writing value to the target.
     *
     * @param uri - the name of the binding to write
     * @param value - the value to write
     * @returns that resolves when the write operation has completed.
     */
    async scriptWrite(uri, value) {
        const binding = this.getBinding(uri);
        const progress = new ProgressCounter();
        if (binding) {
            binding.setValue(value, progress, true);
            progress.done();
            await progress.promise;
        }
        else {
            return Promise.reject(`Failed to write value since bind "${uri}" does not exist.`);
        }
    }
    /**
     * Sub-class can override this method to expose method that can be invoked by the scripting engine.
     *
     * @param method name of the method to invoke from the script
     * @param args array of arguments to pass to the method
     * @param interfaceName - optional name of the interface to invoke the method, if appropriate.
     *
     * @returns a promise that resolves to a value.
     */
    // eslint-disable-next-line @typescript-eslint/no-unused-vars
    invokeMethod(method, args, interfaceName) {
        return Promise.reject(`Failed to invoke ${method} method.`);
    }
    /**
     * Helper method to parse a binding expression using this model as the default for all binding URI's.
     * The resulting bind expression will not be store in the global registry, but rather in a private one.
     * Therefore, you must use this API to retrieve existing model specific bind expressions.
     *
     * @param expression the binding expression to parse.
     *
     * @returns the existing or newly created bindable object, or null if this name is not supported by this model.
     */
    parseModelSpecificBindExpression(expression) {
        this.bindProvider = this.bindProvider || new ModelBindProvider(this);
        return this.bindProvider.getBinding(expression);
    }
    /**
     * Helper method clear all private model specific bind expressions that have been created.  Use this to clear bindings
     * created with the parseModelSpecificBindExpression() helper method.
     */
    clearAllModelSpecificBindExpressions() {
        if (this.bindProvider) {
            this.bindProvider = undefined;
        }
    }
    dispose() {
        if (this.bindProvider) {
            this.bindProvider.dispose();
        }
    }
    async onConnect(transport) {
        this.setConnectedState(true);
    }
    /**
     * Method called when a transport is disconnected from the target.  The default implementation is to iterate through
     * all the bindings and call onDisconnected() on each binding if it supports such a method.  The purpose is for those
     * bindings to clear any critical errors that might have incurred.
     */
    async onDisconnect() {
        this.setConnectedState(false);
        const bindings = this.getAllBindings();
        bindings.forEach((bind) => {
            if (bind && bind.onDisconnected) {
                bind.onDisconnected();
            }
        });
    }
    toString() {
        return `model id="${this.id}"`;
    }
    fireScriptLogEvent(event) {
        this.fireEvent(scriptLogEventType, event);
    }
    /**
     * <p>Helper method that can be used to do custom conversion of values based on getter and setter bind expressions.  It is not
     * necessary to provide both a getter and setter for this conversion to work.  The getter and setter expressions are model
     * specific bind expressions that can use other model bindings and a 'this' variable.  The 'this' variable is expected
     * to be used in these expressions because it represents the value to be converted.  If a 'this' variable is not used, then
     * the result of the conversion will be independent of the input value.</p>
     *
     * <p>If a getter expression is specified, the 'this' variable is assigned the value passed in, and the return value is
     * calculated by calling getValue() on this getter expression.</p>
     * <p>If a setter expression is specified, the setValue() of setter bind expression is called with the value passed in, and
     * the value of the 'this' variable is returned as the result.  In this situation, the setter expression must be a bi-directional
     * expression since it will be evaluated inversely.  A bi-directional expression is an expression that contains only one
     * variable bind and uses simple scale and shift operations; for example, 'this*9/5+32'.  This example could be used to
     * convert Celsius values to Fahrenheit if passed in as the getter expression.  When passed in as the setter expression it
     * performs the inverse operation and converts Fahrenheit to Celsius.</p>
     *
     * @param value the value that is to be converted
     * @param getterExpression the getter expression to do the conversion.  If specified, the setter expression is not used.
     * @param setterExpression the setter expression to do the inverse conversion if no getter is specified..
     * @returns the converted value based on the getter expression, or if not provided, then the setter expression.
     */
    getConvertedValue(value, getterExpression, setterExpression) {
        if (getterExpression) {
            const expr = this.parseModelSpecificBindExpression(getterExpression);
            this.bindProvider.getBinding('this').setValue(value);
            return expr && expr.getValue();
        }
        else if (setterExpression) {
            const expr = this.parseModelSpecificBindExpression(setterExpression);
            if (expr) {
                const thisBind = this.bindProvider.getBinding('this');
                thisBind.setValue(undefined);
                expr.setValue(value);
                return thisBind.getValue();
            }
            return undefined;
        }
        else {
            return value;
        }
    }
}

/**
 *  Copyright (c) 2020, 2022 Texas Instruments Incorporated
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
 * Class that implements IBindValue interface for a constant value binding.
 *
 * @param initialValue the constant value returned by this binding.
 */
class ConstantBindValue extends VariableBindValue {
    constructor(initialValue) {
        super(initialValue, true);
    }
}

/**
 *  Copyright (c) 2020, 2024 Texas Instruments Incorporated
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
 * Abstract class that implements ILookupBindValue interface. Clients can either
 * instantiate this class directly or create classes derived from it for
 * their value bindable object.
 */
class AbstractLookupBindValue extends AbstractBindValue {
    /**
     * Constructor for new AbstractBindValue
     *
     * @param defaultType the default type, used only if value is null.
     */
    constructor(defaultType) {
        super(defaultType);
        this.indexValues = [];
    }
    /**
     * Implementation of the ILookupBindValue.setIndex.  This implementation keeps track of the
     * index(es) and calls the abstract method onIndexChanged() when any
     * index value(s) change.  The getIndex() method can be used to retrieve the index
     * values inside the onIndexChanged() method to re-evaluate the model data's location
     * and possibly it's new value.
     *
     * @param indices one or more new index values to use for lookup
     */
    setIndex(...indices) {
        let changed = false;
        let i = 0;
        for (; i < indices.length && i < this.indexValues.length; i++) {
            const oldIndex = this.indexValues[i];
            const newIndex = indices[i];
            // eslint-disable-next-line eqeqeq
            if (oldIndex != newIndex) {
                this.indexValues[i] = newIndex;
                changed = true;
            }
        }
        for (; i < indices.length; i++) {
            this.indexValues.push(indices[i]);
            changed = true;
        }
        if (changed) {
            this.onIndexChanged(this.indexValues);
        }
    }
    getIndex() {
        return this.indexValues;
    }
    assertNotNull(index) {
        if (index === null || index === undefined) {
            throw new Error('The index value is null.');
        }
    }
    assertValidArrayIndex(index, size = 1, startIndex = 0) {
        this.assertNotNull(index);
        const indexValue = +index;
        if (isNaN(indexValue)) {
            throw new Error(`The index is not valid. Cannot convert '${index}' to an integer.`);
        }
        const endIndex = size + startIndex - 1;
        if (indexValue < startIndex || indexValue > endIndex) {
            throw new Error(`The index ${indexValue} is out of bounds.  It must be between ${startIndex} and ${endIndex}`);
        }
        return indexValue;
    }
    assertValidFieldName(fieldName, possibleFieldNames) {
        this.assertNotNull(fieldName);
        fieldName = fieldName.toString();
        // eslint-disable-next-line no-prototype-builtins
        if (possibleFieldNames === undefined || !possibleFieldNames.hasOwnProperty(fieldName)) {
            throw new Error(`The index '${fieldName}' was not found.`);
        }
        return fieldName;
    }
    assertValidData(index, data) {
        this.assertNotNull(index);
        if (data === undefined) {
            throw new Error(`The index '${index}' was not found.`);
        }
    }
}

/**
 *  Copyright (c) 2020, 2022 Texas Instruments Incorporated
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
 * Class that implements ILookupBindValue interface for an arbitrary javascript function.
 * The binding is read-only and updates its value whenever the indices change.
 * The indices are used as parameters to the function, whose return value is used as
 * the value for this binding.
 *
 * @constructor
 * @extends gc.databind.AbstractLookupBindValue
 *
 * @param functionMethod a function object whose return value is used as this binding's value.
 * @param thisPointer 'this' object to use when calling the function.
 */
class FunctionBindValue extends AbstractLookupBindValue {
    constructor(functionMethod, thisPointer) {
        super();
        this.functionMethod = functionMethod;
        this.thisPointer = thisPointer;
    }
    // eslint-disable-next-line @typescript-eslint/no-empty-function
    setValue() {
    }
    get readOnly() {
        return true;
    }
    onIndexChanged(indices) {
        try {
            this.updateValue(this.functionMethod.apply(this.thisPointer, indices));
            this.status = null; // clear pre-existing error messages
        }
        catch (e) {
            // report exceptions as errors.
            this.status = Status.createErrorStatus(e.message);
        }
    }
    // eslint-disable-next-line @typescript-eslint/no-empty-function
    onValueChanged() {
    }
}

/**
 *  Copyright (c) 2020, 2022 Texas Instruments Incorporated
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
class MathModel extends AbstractBindFactory {
    constructor() {
        super('Math');
    }
    createNewBind(name) {
        // eslint-disable-next-line no-prototype-builtins
        if (Math.hasOwnProperty(name)) {
            // eslint-disable-next-line @typescript-eslint/no-explicit-any
            const result = Math[name];
            if (typeof result === 'function') {
                return new FunctionBindValue(result, Math);
            }
            else {
                return new ConstantBindValue(result);
            }
        }
        return null;
    }
}

/**
 *  Copyright (c) 2020, 2024 Texas Instruments Incorporated
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
/**
 * Class that extends AbstractBindValue for a variable value binding that
 * is persisted in the user's preferences.  Each binding
 * requires a set of keys that make it unique within the users preferences.
 * One or more keys may be provided as additional attributes to this
 * constructor.  These attributes may either be string literals (constant key),
 * or IBindValues where the key value is provided by another binding.  In this
 * case, when any key changes value, this binding's value is updated with the
 * stored user preference for the new keys.  All keys are joined together to
 * form a single user preference key with '_' delimiters inserted between key values.
 */
class UserPreferenceBindValue extends AbstractBindValue {
    /**
     * Constructor for AbstractBindValue
     *
     * @param keys one or more key values or key bindings.
     */
    constructor(...keys) {
        super(typeof String);
        this.storageKey = '';
        this.excludeFromStorageProviderData = true;
        this.storageKeyPrefix = GcUtils.appName;
        // eslint-disable-next-line @typescript-eslint/no-unused-vars
        this.storageKeyChangeHandler = (details) => this.keyValueChangeHandler();
        this.indexBindings = keys.map((key) => {
            if (typeof key === 'string') {
                return new ConstantBindValue(key);
            }
            else {
                key.addEventListener(valueChangedEventType, this.storageKeyChangeHandler);
                return key;
            }
        });
        // trigger key value change to initialize binding value from user preferences.
        this.keyValueChangeHandler();
    }
    onValueChanged(details) {
        if (!this.readOnly) {
            // save new value in local storage
            GcLocalStorage.setItem(this.storageKey, details.newValue);
        }
    }
    dispose() {
        for (let i = this.indexBindings.length; i-- > 0;) {
            const indexBinding = this.indexBindings[i];
            indexBinding.removeEventListener(valueChangedEventType, this.storageKeyChangeHandler);
            if (isDisposable(indexBinding)) {
                indexBinding.dispose();
            }
        }
    }
    set defaultValue(defaultValue) {
        if (this.readOnly) {
            this.updateValue(defaultValue);
        }
        else if (this._defaultValue !== defaultValue) {
            this._defaultValue = defaultValue;
            // trigger key value change to initialize binding value from user preferences.
            this.keyValueChangeHandler();
        }
    }
    get defaultValue() {
        return this._defaultValue;
    }
    keyValueChangeHandler() {
        if (!this.readOnly) {
            // ignore localStorage, because if it has a value, its wrong because we don't store constant values there.
            // calculate new key value
            this.storageKey = this.indexBindings.reduce((result, key) => result + '_' + (key.getValue() ?? ''), this.storageKeyPrefix);
            // load preference value from local storage
            this.updateValue(GcLocalStorage.getItem(this.storageKey) || this.defaultValue);
        }
    }
}

/**
 *  Copyright (c) 2020, 2024 Texas Instruments Incorporated
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
 * A data binding model where arbitrary data (or properties) are only stored locally and are not written to any target device.
 * Optionally, this property model may be configured to persist all its data in the user's local storage.
 * In this case, you may want to create two property models, one for persistent storage, and one
 * for non-persistent storage.
 */
class PropertyModel extends AbstractBindFactory {
    constructor(params = {}) {
        super(params.id || 'prop');
        this.params = params;
        this._defaultValues = {};
    }
    createNewBind(name) {
        if (this.params.persist) {
            return new UserPreferenceBindValue(this.id, name);
        }
        return new VariableBindValue(undefined);
    }
    /**
     * Default values for all properties in this model.  Default values are only used when
     * this model has the persist parameter set.  In this case, the default value will be
     * used when there is no user persisted value stored yet.
     */
    get defaultValues() {
        return this._defaultValues;
    }
    set defaultValues(defaultValues) {
        this._defaultValues = defaultValues;
        // apply defaults
        for (const [k, v] of Object.entries(defaultValues)) {
            const bind = this.getBinding(k);
            if (bind instanceof UserPreferenceBindValue) {
                bind.defaultValue = v;
            }
            if (bind.getValue() === undefined) {
                bind.updateValue(v);
            }
        }
    }
}

/**
 * Copyright (c) 2021, Texas Instruments Incorporated
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
class StatusIndicator {
    constructor(targetWidget, locationHint) {
        this.targetWidget = targetWidget;
        this.locationHint = locationHint;
        this.messages = [];
    }
    addVisibilityListener() {
        this.visibilityObserver = new ResizeObserver(() => {
            if (this.statusWidget) {
                this.statusWidget.setAttribute('style', this.getIndicatorStyles().divStyle);
            }
        });
        this.visibilityObserver.observe(this.targetWidget);
    }
    removeVisibilityListener() {
        if (this.visibilityObserver) {
            this.visibilityObserver.disconnect();
            this.visibilityObserver = undefined;
        }
    }
    createStatusWidget(message, type) {
        const parentElem = this.targetWidget.parentElement;
        if (!parentElem) {
            return;
        }
        const styles = this.getIndicatorStyles();
        const div = document.createElement('div');
        div.setAttribute('style', styles.divStyle);
        // eslint-disable-next-line @typescript-eslint/no-explicit-any
        const img = document.createElement('gc-widget-icon');
        img.src = StatusIndicator.getStatusIndicatorIcon(type);
        img.setAttribute('style', styles.imgStyle);
        img.setAttribute('tooltip', message);
        img.setAttribute('icon', StatusIndicator.getStatusIndicatorIcon(type));
        img.setAttribute('size', 'xs');
        img.setAttribute('appearance', StatusIndicator.getIconAppearance(type));
        div.appendChild(img);
        if (!GcUtils.isInDesigner) { // TODO: eventually we want all bindings to work in designer, and show errors before we run.
            parentElem.insertBefore(div, this.targetWidget);
        }
        return div;
    }
    addMessage(message, type) {
        type = type || StatusType.ERROR;
        this.removeMessage(message, true);
        this.messages.push({ message, type });
        if (this.statusWidget) {
            this.updateStatusIndication();
        }
        else {
            this.statusWidget = this.createStatusWidget(message, type);
            if (this.statusWidget) {
                this.addVisibilityListener();
            }
        }
    }
    updateStatusIndication() {
        if (!this.statusWidget) {
            return;
        }
        const nextMessage = this.getStatusMessage();
        if (nextMessage) {
            const img = this.statusWidget.children[0];
            if (img && img.title !== nextMessage.message) {
                // update the status text with new message.
                img.title = nextMessage.message;
                const iconLocation = StatusIndicator.getStatusIndicatorIcon(nextMessage.type);
                if (img.src.indexOf(iconLocation) < 0) {
                    img.src = iconLocation;
                }
            }
        }
        else {
            // no more status messages, so lets get rid or the
            // status indicator widget.
            const parentElem = this.statusWidget && this.statusWidget.parentElement;
            if (parentElem) {
                parentElem.removeChild(this.statusWidget);
            }
            this.removeVisibilityListener();
            this.statusWidget = undefined;
        }
    }
    getStatusMessage() {
        if (this.messages.length === 0) {
            return;
        }
        return this.messages.reduce((result, item) => {
            return item.type <= result.type ? item : result;
        }, this.messages[0]);
    }
    removeMessage(oldMessage, preventUpdate = false) {
        if (!oldMessage) {
            return;
        }
        this.messages = this.messages.filter(item => item.message !== oldMessage);
        if (!preventUpdate) {
            this.updateStatusIndication();
        }
    }
    static getRelativeIndicatorPosition(rect, hint) {
        hint = hint || 'middle-left';
        let divStyle = '';
        let imgStyle = '';
        let edge = false;
        let fields = hint.split('-');
        if (fields.length !== 2) {
            fields = [
                'middle', 'left'
            ];
        }
        for (let i = 0; i < 2; i++) {
            switch (fields[i].trim().toLowerCase()) {
                // horizontal positions
                case 'left':
                    divStyle += 'left: ' + rect.left + 'px; ';
                    imgStyle += (edge ? 'left: 0px; ' : 'right: 0px; ');
                    edge = true;
                    break;
                case 'right':
                    divStyle += 'left: ' + rect.right + 'px; ';
                    imgStyle += (edge ? 'right :0px;' : 'left :0px; ');
                    edge = true;
                    break;
                case 'center':
                    divStyle += 'left: ' + (rect.left + rect.right) / 2 + 'px; ';
                    imgStyle += 'left: -7px; ';
                    break;
                // vertical positions
                case 'top':
                    divStyle += 'top: ' + rect.top + 'px; ';
                    imgStyle += (edge ? 'top: 0px; ' : 'bottom: 0px; ');
                    edge = true;
                    break;
                case 'bottom':
                    divStyle += 'top: ' + rect.bottom + 'px; ';
                    imgStyle += (edge ? 'bottom: 0px;' : 'top: 0px; ');
                    edge = true;
                    break;
                case 'middle':
                    divStyle += 'top: ' + (rect.top + rect.bottom) / 2 + 'px; ';
                    imgStyle += 'top: -7px; ';
                    break;
                default:
                    GcConsole.error(NAME, `Invalid position found in status indicator location hint = ${hint}`);
                    break;
            }
        }
        return ({
            divStyle: divStyle,
            imgStyle: imgStyle
        });
    }
    getIndicatorStyles() {
        const elemStyle = getComputedStyle(this.targetWidget);
        const positionStyle = elemStyle.position;
        const visibilityStyle = (elemStyle.display === 'none' || elemStyle.visibility === 'hidden') ? 'hidden' : 'visible';
        let styles = null;
        if (positionStyle === 'absolute') {
            // calculate relative size and position in pixels w.r.t parent
            // element.
            const elemRect = {
                left: this.targetWidget.offsetLeft,
                right: this.targetWidget.clientWidth + this.targetWidget.offsetLeft,
                top: this.targetWidget.offsetTop,
                bottom: this.targetWidget.clientHeight + this.targetWidget.offsetTop
            };
            // set styles including position
            styles = StatusIndicator.getRelativeIndicatorPosition(elemRect, this.locationHint);
            styles.divStyle = 'position: absolute; ' + styles.divStyle;
        }
        else if (positionStyle === 'static' || positionStyle === 'relative') {
            styles = {
                divStyle: 'position: relative;',
                imgStyle: 'left: 0px; top: 0px;'
            };
        }
        else { // 'fixed'
            styles = StatusIndicator.getRelativeIndicatorPosition(this.targetWidget.getBoundingClientRect(), this.locationHint);
            styles.divStyle = 'position: fixed; ' + styles.divStyle;
        }
        return {
            divStyle: `${styles.divStyle} overflow: visible; display: inline-block; background-color: var(--theme-background-color, white) visibility: ${visibilityStyle}`,
            imgStyle: `position: absolute; margin: 0; z-index:275; ${styles.imgStyle} background-color: inherit; border-radius: 10px`
        };
    }
    static getStatusIndicatorIcon(type) {
        switch (type) {
            case StatusType.ERROR: return 'navigation:cancel';
            case StatusType.WARNING: return 'alert:error';
            default:
                return 'action:info';
        }
    }
    static getIconAppearance(type) {
        switch (type) {
            case StatusType.ERROR: return 'error';
            case StatusType.WARNING: return 'warn';
            default:
                return '';
        }
    }
}
/**
 * Factory used to retrieve status indicators for a given widget.
 */
class StatusIndicatorFactory {
    /**
     * Factory method to create/retrieve status indicators for a particular widget The widget
     *
     * @param widget - the the widget to get a status indicator for.
     * @return the status indicator created for this widget, or null if no widget found.
     */
    static get(widget) {
        let statusIndicator = this.activeStatusIndicators.get(widget.id);
        if (statusIndicator === undefined) {
            if (widget) {
                const customHintLocation = widget._statusIndicatorLocationHint;
                const locationHint = typeof customHintLocation === 'function' ? customHintLocation() : customHintLocation;
                statusIndicator = new StatusIndicator(widget, locationHint);
                this.activeStatusIndicators.set(widget.id, statusIndicator);
            }
        }
        else {
            // update target widget in case it has changed, and we need to
            // create a new statusWidget
            statusIndicator.targetWidget = widget;
        }
        return statusIndicator;
    }
}
StatusIndicatorFactory.activeStatusIndicators = new Map();

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
const userEditEvent = new EventType('user edit');
class EditOperation {
    constructor(bind, oldValue, newValue, time) {
        this.bind = bind;
        this.oldValue = oldValue;
        this.newValue = newValue;
        this.time = time;
    }
    undo() {
        this.bind.setValue(this.oldValue);
    }
    redo() {
        this.bind.setValue(this.newValue);
    }
    toString() {
        return 'edit';
    }
    canMergeOperation(bind, newValue, now) {
        // make sure it's also different from original value; e.g.,
        // checkbox toggled quickly.
        return bind === this.bind && now - this.time < 250 && this.oldValue !== newValue;
    }
    mergeOperation(newValue, time) {
        this.newValue = newValue;
        this.time = time;
        this.redo(); // perform action now.
    }
}
class WidgetBindValue extends AbstractBindValue {
    constructor(widgetId, widget, widgetProperty, initialValue, parent) {
        super();
        this.widgetProperty = widgetProperty;
        this.parent = parent;
        this.excludeFromStorageProviderData = true;
        this.doUserEditOperation = () => {
            const widget = this.widget;
            if (widget) {
                const oldValue = this.getValue();
                const newValue = this.readPropertyValue(widget);
                if (oldValue !== newValue) {
                    // eslint-disable-next-line @typescript-eslint/no-use-before-define
                    WidgetModel.doUserEditOperation(this, newValue, oldValue);
                    this.excludeFromStorageProviderData = false;
                }
            }
        };
        this.onFirstValueChangedListenerAdded = () => {
            const widget = this.widget;
            if (widget) {
                widget.addEventListener(this.changedPropertyEventName, this.doUserEditOperation);
                const oldStatus = this.status;
                if (oldStatus) {
                    // restore status indicators for the new widget.
                    widget.errorMessage = oldStatus.message;
                }
            }
        };
        this.onLastValueChangedListenerRemoved = () => {
            const widget = this.widget;
            if (widget) {
                widget.removeEventListener(this.changedPropertyEventName, this.doUserEditOperation);
                const oldStatus = this.status;
                if (oldStatus) {
                    // remove status indicators that are tied to this widget
                    widget.errorMessage = undefined;
                }
                // next time we have to bind to the widget, lets use a fresh widget pointer
                // this way we support unbind from widgets, recreate widgets, then bind to new widgets.
                this._widget = undefined;
            }
        };
        this.widgetId = widgetId;
        this._widget = widget;
        this.cachedValue = initialValue;
        this.changedPropertyEventName = GcUtils.camelToDashCase(widgetProperty) + '-changed';
        this.addEventListenerOnFirstAdded(valueChangedEventType, this.onFirstValueChangedListenerAdded);
        this.addEventListenerOnLastRemoved(valueChangedEventType, this.onLastValueChangedListenerRemoved);
        const streamingListener = widget[widgetProperty + 'StreamingDataListener'];
        if (streamingListener && typeof streamingListener === 'function') {
            this.onStreamingDataReceived = streamingListener.bind(widget);
        }
    }
    writePropertyValue(widget, newValue) {
        widget[this.widgetProperty] = newValue;
    }
    onValueChanged(details) {
        this.excludeFromStorageProviderData = true;
        const widget = this.widget;
        if (widget) {
            // widget available, so update property
            this.writePropertyValue(widget, details.newValue);
        }
    }
    get widget() {
        this._widget = this._widget || WidgetModel.findWidget(this.widgetId, this.parent || document) || undefined;
        return this._widget;
    }
    onStatusChanged(details) {
        const statusIndicator = StatusIndicatorFactory.get(this.widget);
        if (!statusIndicator) {
            return;
        }
        if (details.oldStatus) {
            statusIndicator.removeMessage(details.oldStatus.message);
        }
        if (details.newStatus) {
            statusIndicator.addMessage(details.newStatus.message, details.newStatus.type);
        }
    }
    readPropertyValue(widget) {
        return widget[this.widgetProperty];
    }
}
class WidgetStyleLookupBind extends WidgetBindValue {
    constructor(widgetId, widget, parent) {
        super(widgetId, widget, 'cssProperty', parent);
    }
    setIndex(...index) {
        this.cssPropertyName = '' + (index[0] || '');
        const widget = this.widget;
        if (widget) {
            this.updateValue(this.readPropertyValue(widget));
        }
    }
    readPropertyValue(widget) {
        if (this.cssPropertyName) {
            // using getComputedStyle(widget).getPropertyValue(name) because widget.getCSSProperty(name) returns a promise
            // and I need the value now.
            // eslint-disable-next-line @typescript-eslint/no-explicit-any
            return getComputedStyle(widget).getPropertyValue(this.cssPropertyName)?.trim() || '';
        }
        return undefined;
    }
    writePropertyValue(widget, newValue) {
        if (this.cssPropertyName && typeof newValue === 'string') {
            if (widget.setCSSProperty) {
                widget.setCSSProperty?.(this.cssPropertyName, newValue);
            }
            else {
                widget.style.setProperty(this.cssPropertyName, newValue.trim());
            }
        }
    }
}
class WidgetModel extends AbstractBindFactory {
    constructor(rootElement) {
        super('widget');
        this.rootElement = rootElement;
    }
    static findWidgetShallow(parent, uri) {
        const query = `[id="${uri.split('.').join('"] [id="')}"]`;
        const result = parent.querySelector(query);
        return result;
    }
    static findWidget(deepUri, from) {
        const shallowUri = deepUri.split('.$.');
        let result = this.findWidgetShallow(from, shallowUri[0]);
        for (let i = 1; result && i < shallowUri.length; i++) {
            if (result.shadowRoot) {
                result = this.findWidgetShallow(result.shadowRoot, shallowUri[i]);
            }
            else {
                GcConsole.error(NAME, `Cannot access shadow dom of widget ${shallowUri[i - 1]} in ${deepUri}`);
                return null;
            }
        }
        if (!result) {
            GcConsole.error(NAME, `Failed to find widget ${deepUri}.`);
        }
        return result;
    }
    createNewBind(name) {
        let bind = null;
        const pos = name.lastIndexOf('.');
        if (pos > 0) {
            const widgetName = name.substring(0, pos);
            const widgetProperty = name.substring(pos + 1);
            const widget = WidgetModel.findWidget(widgetName, this.rootElement || document);
            if (widget) {
                if (widgetProperty === 'style') {
                    bind = new WidgetStyleLookupBind(widgetName, widget, this.rootElement);
                }
                else {
                    bind = new WidgetBindValue(widgetName, widget, widgetProperty, widget[widgetProperty], this.rootElement);
                }
            }
        }
        return bind;
    }
    static clearLastUserEditOperation() {
        this.lastUndoOperation = undefined;
    }
    static doUserEditOperation(bind, newValue, oldValue) {
        const lastOperation = this.lastUndoOperation;
        const now = Date.now();
        if (lastOperation && lastOperation.canMergeOperation(bind, newValue, now)) {
            lastOperation.mergeOperation(newValue, now);
        }
        else if (oldValue !== undefined && newValue !== undefined && !blockNewEditUndoOperationCreation) {
            const operation = new EditOperation(bind, oldValue, newValue, now);
            this.instance.fireEvent(userEditEvent, { operation: operation });
            operation.redo();
            this.lastUndoOperation = operation;
        }
        else {
            bind.setValue(newValue);
        }
    }
    static async whenWidgetReady(widgetId) {
        if (GcUtils.isNodeJS) {
            return;
        }
        await this.documentContentLoaded;
        const shallowUri = widgetId.split('.$.')[0];
        const widget = this.findWidgetShallow(document, shallowUri);
        if (widget) {
            const customComponentName = widget.tagName.toLowerCase();
            if (customComponentName.indexOf('-') > 0) {
                await customElements.whenDefined(customComponentName);
                const waitForWidget = widget;
                if (typeof waitForWidget.waitForWidgetReady === 'function') {
                    const promise = waitForWidget.waitForWidgetReady();
                    if (promise instanceof Promise) {
                        await promise;
                    }
                }
            }
            else {
                throw Error(`Widget id="${widgetId} was not found in html document.`);
            }
        }
        return widget;
    }
}
WidgetModel.instance = new WidgetModel();
WidgetModel.documentContentLoaded = !GcUtils.isNodeJS && document.readyState === 'loading' ? new Promise(resolve => {
    document.addEventListener('DOMContentLoaded', () => resolve());
}) : Promise.resolve();

/**
 *  Copyright (c) 2020, 2022 Texas Instruments Incorporated
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
const nullDataBinder = new (class {
    constructor() {
        this.enabled = false;
    }
    dispose() {
        // do nothing
    }
});
const matchIDRegEx = /\s+id="([^"]+)"/;
class BinderCollection {
    constructor() {
        this.binders = [];
        this._enabled = false;
    }
    set enabled(enable) {
        if (this._enabled !== enable) {
            this._enabled = enable;
            this.binders.forEach((binder) => binder.enabled = enable);
        }
    }
    get enabled() {
        return this._enabled;
    }
    add(binder) {
        if (binder) {
            this.binders.push(binder);
            binder.enabled = this.enabled;
        }
    }
    dispose() {
        this.enabled = false;
    }
}
/**
 * Singleton class where all bindings, and binding expressions are
 * registered. This is also where data model {@link IBindFactory}
 * instances are registered.
 */
class BindingRegistry extends AbstractBindProvider {
    /**
     * This constructor should not be used.  Instead, use {@link bindingRegistry} to obtain
     * the singleton instance of this class.
     *
     * @private
     */
    constructor() {
        super();
        this.models = new Map();
        this.waitForModelPromises = new Map();
        this.bindingCollections = new Map();
    }
    addModel(name, model) {
        this.models.set(name, model);
        if (this.waitForModelPromises.has(name)) {
            this.waitForModelPromises.get(name).resolve(model);
            this.waitForModelPromises.delete(name);
            GcConsole.log(NAME, `Model id=${name} is ready.`);
        }
    }
    /**
     * Register a data model with the binding registry. At least one model must
     * be registered in order for this class to be able to create bindings.
     *
     * @param model the models binding factory to
     *        create new bindings.
     * @param makedefault optional flag to make this the new
     *        default model.
     * @param alias optional alias that can be used in place of the model name, for example, $ for widget
     */
    registerModel(model, makeDefault = false, alias) {
        const name = model.id;
        // use first registered model as default, if not already specified.
        this.defaultModelName = this.defaultModelName || name;
        if (makeDefault) {
            this.defaultModelName = name;
        }
        this.addModel(name, model);
        if (alias && !this.models.has(alias)) { // don't overwrite a real model name with an alias.
            this.addModel(alias, model);
        }
    }
    /**
     * Helper method to ensure a model is ready, before you create bindings for that model.  If
     * bindings are created before the model is registered, it will be in an error state.
     * @example
     * ```typescript
     * import { bindingRegistry } from '<path-to>/gc-core-databind/lib/CoreDatabind';
     *
     * await bindingRegistry.waitForModelReady('streaming');
     * const bind = bindingRegistry.getBinding('model.streaming.data.member');
     * ```
     *
     * @param name the name of the model that is expected to be registered.
     * @param timeout optional time limit to wait for the model to be registered.  By default, this timeout is unlimited.
     */
    waitForModelReady(name, timeout = 0) {
        const model = this.getModel(name);
        if (model) {
            return Promise.resolve(model);
        }
        let defer = this.waitForModelPromises.get(name);
        if (!defer) {
            defer = GcPromise.defer();
            defer.promise = timeout > 0 ? GcPromise.timeout(defer.promise, timeout, `Timeout waiting for model id="${name}" to be ready`) : defer.promise;
            this.waitForModelPromises.set(name, defer);
        }
        return defer.promise;
    }
    /**
     * Get a data model that has already been registered with this binding provider.
     *
     * @param name identifier for the model. E.g. widget. If missing returns the default model.
     * @returns the model found or undefined if it is not registered.
     */
    getModel(name) {
        name = name || this.defaultModelName; // use default if not specified.
        return name ? this.models.get(name) || null : null;
    }
    /**
     * The default model, which is usually the widget model.
     */
    get defaultModel() {
        return this.defaultModelName;
    }
    set defaultModel(name) {
        this.defaultModelName = name;
    }
    /**
     * Method to delete and dispose of all bindings and models in the binding registry.
     */
    dispose() {
        super.dispose();
        this.models.forEach((model) => {
            if (isDisposable(model)) {
                model.dispose();
            }
        });
        this.models.clear();
        this.waitForModelPromises.clear();
        this.defaultModelName = undefined;
        bindingRegistry.registerModel(new MathModel());
        bindingRegistry.registerModel(new PropertyModel());
        bindingRegistry.registerModel(WidgetModel.instance, true, '$');
    }
    /**
     * Parse the model specific binding expression.
     *
     * @private
     * @param expression the expression to parse the model from
     */
    parseModelFromBinding(uri) {
        let modelFactory = null;
        let pos = uri.indexOf('.');
        if (pos > 0) {
            let modelName = uri.substring(0, pos);
            // Handle explicit model.<id>.* case.
            let explicitModelPrefix = false;
            if (modelName === 'model') {
                const endPos = uri.indexOf('.', pos + 1);
                if (endPos <= 0) {
                    throw Error(`Invalid binding: there is no model name after 'model.' in ${uri}, `);
                }
                modelName = uri.substring(pos + 1, endPos);
                pos = endPos;
                explicitModelPrefix = true;
            }
            modelFactory = this.getModel(modelName);
            if (modelFactory) {
                uri = uri.substring(pos + 1);
            }
            else if (explicitModelPrefix) {
                // if the model doesn't exist we don't use the default because we explicitly specified the model by id.
                throw Error(`Missing the model specified by the binding ${uri}`);
            }
        }
        // lookup the default model if no model specified
        modelFactory = modelFactory || this.getModel();
        if (!modelFactory) {
            throw Error('There is no default model for bindings');
        }
        return { model: modelFactory, bindName: uri };
    }
    /**
     * Method to disable a binding previously created using the bind() method.
     * This will also unregister the two bind values that are being bound together.
     * If no other binding or expression is using the bind values, then garbage collection
     * will dispose of them.  Otherwise, new bindings may create additional bindValues
     * and you will end up with multiple bindValues for the same model or target data.
     * This will not cause problems, but is less efficient.
     *
     * @param binder the binding to delete.
     */
    unbind(binder) {
        binder.enabled = false;
    }
    createBindingCollection(bindings) {
        if (typeof bindings === 'object') {
            const result = new Map();
            for (const name in bindings) {
                // eslint-disable-next-line no-prototype-builtins
                if (bindings.hasOwnProperty(name)) {
                    let binding;
                    const bindName = bindings[name];
                    try {
                        binding = this.getBinding(bindName);
                    }
                    catch (e) {
                        throw Error(`Can't parse binding "${bindName}".\n${e}`);
                    }
                    if (binding !== null) {
                        result.set(name, binding);
                    }
                    else {
                        throw Error(`Binding "${bindName}" could not be found.`);
                    }
                }
            }
            return new CollectionBindValue(result);
        }
        else {
            try {
                return this.getBinding(bindings);
            }
            catch (message) {
                throw Error(`Can't parse binding "${bindings}".\n${message}`);
            }
        }
    }
    /**
     * <p>
     * Method to bind together a target and a model binding.
     * </p>
     * <p>
     * The difference between the target binding and the model binding is
     * subtle. The modelBinding contains the initial value. Otherwise there is
     * no distinction between model and target. Once the bindings are bound
     * together, their value and status will forever be the same. If either
     * value of status changes on one binding, the other will be updated to
     * reflect the change. This is typically used to keep widget and model data
     * in sync.
     * </p>
     * <p>
     * This method returns a binder object that can be used to control the
     * enabled disabled state of this two-way data binding between target and
     * model bindings.
     * </p>
     *
     * @param targetBinding name or expression for the target
     *        binding.
     * @param modelBinding name or expression for the model
     *        binding.
     * @param getter getter/preprocessing for a computed value
     * @param setter setter/postprocessing for a computed value
     * @returns interface to control the binding created between
     *          the the target and model bindings.
     */
    bind(targetBinding, modelBinding, getter, setter) {
        let targetBind = null;
        let modelBind = null;
        try {
            targetBind = this.createBindingCollection(targetBinding);
            modelBind = this.createBindingCollection(modelBinding);
            if (!targetBind || !modelBind) {
                throw Error(`Binding ${modelBind ? targetBinding : modelBinding} does not exist.`);
            }
            return DataBinder.bind(targetBind, modelBind, getter, setter);
        }
        catch (e) {
            const errorStatus = Status.createErrorStatus(e.message);
            if (targetBind) {
                targetBind.status = errorStatus;
            }
            else {
                try {
                    if (!modelBind) {
                        modelBind = typeof modelBinding === 'object' ? this.createBindingCollection(modelBinding) : this.getBinding(modelBinding);
                    }
                    if (modelBind) {
                        modelBind.status = errorStatus;
                    }
                }
                catch (err) {
                    // ignore errors on the second binding, just use the error generated on the first.
                }
            }
            GcConsole.error(NAME, e);
            return nullDataBinder;
        }
    }
    getDefaultBindingFile() {
        try {
            let path = document.querySelector('meta[name="gc-databinding-json-path"]')?.content;
            if (path) {
                return path;
            }
            else {
                path = window.location.pathname;
                const pos = path.lastIndexOf('/');
                if (pos !== path.length - 1) {
                    path = path.substring(pos + 1);
                    return path.replace('.html', '.json');
                }
            }
        }
        catch (e) { /* do nothing */ }
        return 'index.json';
    }
    getDefaultPropertyFile() {
        return 'index_prop.json';
    }
    /**
     * Method to disable all bindings that were previously loaded from .json file
     * using {@link BindingRegistry.loadBindingsFromFile}
     *
     * @param jsonFile file path for .json file containing the data bindings that were previously loaded.
     */
    async unloadBindingsFromFile(jsonFile) {
        jsonFile = jsonFile || this.getDefaultBindingFile();
        const binder = this.bindingCollections.get(jsonFile);
        if (binder) {
            (await binder).enabled = false;
        }
    }
    async loadBinding(wb) {
        let serverBindName = wb.serverBindName;
        // This section of code will wait for widgets and models to be ready, before creating the binding
        try {
            if (wb.widgetId) {
                await WidgetModel.whenWidgetReady(wb.widgetId);
            }
            if (serverBindName) {
                let widgetPrefixWasRemoved = false;
                // strip leading 'widget.' prefix since it is the default anyway.
                if (serverBindName.indexOf('widget.') === 0) {
                    serverBindName = serverBindName.substring('widget.'.length);
                    widgetPrefixWasRemoved = true;
                }
                // support waiting for all bind variables to be ready, especially when parsing expressions, rather than simple bindings.
                const bindNames = ExpressionParserUtils.getIdentifiers(serverBindName);
                for (let i = 0; i < bindNames.length; i++) {
                    const bindSegments = bindNames[i].split('.');
                    if (bindSegments.length > 1) {
                        let modelId = bindSegments[0];
                        if ((modelId === 'widget' && !widgetPrefixWasRemoved) || modelId === '$') {
                            // Explicit widget binding
                            await WidgetModel.whenWidgetReady(bindSegments.slice(1, -1).join('.'));
                        }
                        else if (modelId === 'model' && !widgetPrefixWasRemoved) {
                            // Explicit model binding
                            modelId = bindSegments[1];
                        }
                        else {
                            // implicit widget or model binding
                            try {
                                const widget = await WidgetModel.whenWidgetReady(modelId);
                                if (widget &&
                                    ((widget.tagName.split('-')[1]?.toLowerCase() !== 'model') ||
                                        // @ts-ignore
                                        (widgetPrefixWasRemoved && bindSegments.length === 2 && Object.getOwnPropertyDescriptor(widget.__proto__, bindSegments[1])?.get))) {
                                    // modelId must have been a widget.
                                    modelId = 'widget';
                                    if (widgetPrefixWasRemoved) {
                                        // put widget. prefix back to make it explicit.
                                        serverBindName = wb.serverBindName;
                                    }
                                }
                            }
                            catch (e) {
                                // widget not found, so must be model contributed from .js instead of .html.
                            }
                        }
                        await this.waitForModelReady(modelId, 10000);
                    }
                    widgetPrefixWasRemoved = false; // we can only remove the prefix from the first bindName in this for loop.
                }
            }
        }
        catch (e) {
            // ignore timeout errors, missing widget error messages will be generated below
        }
        // set the default type for the widget binding
        const widgetBindName = `widget.${wb.widgetId}.${wb.propertyName}`;
        if (wb.options && wb.options.dataType) {
            const widgetBind = this.getBinding(widgetBindName);
            let defaultType = wb.options.dataType.toLowerCase();
            if (defaultType === 'long' || defaultType === 'short' || defaultType === 'int' || defaultType === 'double' || defaultType === 'float') {
                defaultType = 'number';
            }
            if (widgetBind && widgetBind.setDefaultType) {
                widgetBind.setDefaultType(defaultType);
            }
            else {
                GcConsole.error(NAME, `Cannot set default type on binding "${widgetBindName}" because it does not exist.`);
            }
        }
        // Binding records with no widgetId are used to initialize backplane bindings.
        if (!wb.widgetId && serverBindName && wb.options && (typeof wb.options.defaultValue !== 'undefined')) {
            const bind = this.getBinding(serverBindName);
            if (bind) {
                bind.setValue(wb.options.defaultValue);
            }
            else {
                GcConsole.error(NAME, `Cannot set default binding value because the binding "${wb.serverBindName}" does not exist.`);
            }
        }
        else {
            const binder = this.bind(widgetBindName, serverBindName) ?? undefined;
            return binder;
        }
    }
    async doLoadBindingsFromFile(jsonFile) {
        const results = new BinderCollection();
        try {
            const data = await GcFiles.readJsonFile(jsonFile);
            GcConsole.log(NAME, () => `Started loading bindings from file ${jsonFile}`);
            if (data) {
                const promises = data.widgetBindings.map(wb => this.loadBinding(wb));
                const binders = await Promise.all(promises);
                binders.forEach(binder => results.add(binder));
            }
            GcConsole.log(NAME, () => `Finished loading bindings from file ${jsonFile}`);
        }
        catch (error) {
            GcConsole.error(NAME, error);
            return nullDataBinder;
        }
        results.enabled = true;
        return results;
    }
    /**
     * Method to load bindings from a .json file.
     *
     * @param jsonFile file path for .json file containing the data bindings to load.
     */
    loadBindingsFromFile(jsonFile) {
        jsonFile = jsonFile || this.getDefaultBindingFile();
        let results = this.bindingCollections.get(jsonFile);
        if (!results) {
            results = this.doLoadBindingsFromFile(jsonFile);
            this.bindingCollections.set(jsonFile, results);
        }
        return results;
    }
    /**
     * Method to load model properties from a .json file.
     *
     * @private
     * @param jsonFile file path for .json file containing the model properties to load.
     */
    async loadPropertiesFromFile(model, jsonFile) {
        jsonFile = jsonFile || this.getDefaultPropertyFile();
        try {
            // eslint-disable-next-line @typescript-eslint/no-explicit-any
            const jsonData = await GcFiles.readJsonFile(jsonFile);
            return jsonData ? jsonData[model] : undefined;
        }
        catch (error) {
            GcConsole.error(NAME, error);
            return undefined;
        }
    }
    /**
     * Method used by the designer to parse bindings embedded in html.
     *
     * @private
     * @param modelName the name of the model to parse bindings for
     * @param arrayOfLines html text to parse from
     * @param modelID: the id of the model to use for the bindings found.
     */
    parseBindingsFromGist(modelName, arrayOfLines, modelID) {
        const re = new RegExp('\\s+(\\w+)\\s*=\\s*"\\s*{{\\s*\\$\\.' + modelName + '\\.([a-zA-Z0-9_\\.$]+)', 'g');
        const bindingsData = [];
        if (this.defaultModel === modelID) {
            modelID = '';
        }
        else {
            modelID = modelID + '.';
        }
        for (let i = 0; i < arrayOfLines.length; i++) {
            const pos = arrayOfLines[i].indexOf('$.' + modelName + '.');
            if (pos >= 0) {
                // parse binding expression and property name
                const matches = arrayOfLines[i].match(matchIDRegEx);
                if (matches) {
                    const widgetId = matches[1];
                    let match = re.exec(arrayOfLines[i]);
                    while (match) {
                        const bindingExpression = match[2];
                        const propertyName = match[1];
                        bindingsData.push({
                            propertyName: propertyName,
                            serverBindName: modelID + bindingExpression,
                            widgetId: widgetId
                        });
                        match = re.exec(arrayOfLines[i]);
                    }
                }
            }
        }
        return bindingsData;
    }
    saveJsonFile(jsonFile, jsonObject) {
        return GcFiles.writeJsonFile(jsonFile, jsonObject);
    }
    /**
     * Method to save model properties from a .json file.
     *
     * @private
     * @param jsonFile the path name of the json file to write to.
     * @param properties all model properties to save.
     */
    savePropertiesToFile(jsonFile, properties) {
        jsonFile = jsonFile || this.getDefaultPropertyFile();
        return this.saveJsonFile(jsonFile, properties);
    }
    /**
     * Method used by designer to save bindings to a json file.
     *
     * @private
     * @param jsonFile the path name of the json file to write to.
     * @param bindings all bindings to save.
     */
    saveBindingsToFile(jsonFile, bindings) {
        let jsonObject = bindings;
        if (bindings instanceof Array) {
            jsonObject = {
                widgetBindings: bindings
            };
        }
        jsonFile = jsonFile || this.getDefaultBindingFile();
        return this.saveJsonFile(jsonFile, jsonObject);
    }
}
/**
 * Singleton instance of the BindingRegistry, for everyone to share.
 */
const bindingRegistry = new BindingRegistry();
bindingRegistry.dispose();
if (!GcUtils.isNodeJS) {
    (async function init() {
        await WidgetModel.documentContentLoaded;
        // Fire legacy ready event for gc.databind.ready
        document.dispatchEvent(new CustomEvent('gc-databind-ready', { detail: { registry: bindingRegistry } }));
        if (!GcUtils.isInDesigner) {
            bindingRegistry.loadBindingsFromFile();
        }
    })();
}

/**
 * Concrete Class for a Trigger that fires a user callback when a condition is met.
 */
class Trigger {
    constructor(triggerEventCallback, condition) {
        this.triggerEventCallback = triggerEventCallback;
        this.conditionBind = null;
        this._enabled = true;
        this.onChangedListener = (details) => this.onValueChanged(details);
        this.condition = condition;
    }
    get enabled() {
        return this._enabled;
    }
    set enabled(enabled) {
        enabled = !!enabled;
        if (this._enabled !== enabled) {
            if (enabled && this.conditionBind) {
                this.conditionBind.addEventListener(valueChangedEventType, this.onChangedListener);
            }
            else if (this.conditionBind) {
                this.conditionBind.removeEventListener(valueChangedEventType, this.onChangedListener);
            }
            this._enabled = enabled;
        }
    }
    onValueChanged(details) {
        if (this.conditionBind) {
            const newValue = !!this.conditionBind.getValue();
            if (this.cachedValue !== newValue) {
                this.cachedValue = newValue;
                if (newValue && this._enabled) {
                    this.triggerEventCallback(details);
                }
            }
        }
    }
    set condition(newCondition) {
        // remove listener from old condition if there was one.
        if (this.conditionBind && this._enabled) {
            this.conditionBind.removeEventListener(valueChangedEventType, this.onChangedListener);
        }
        // get new condition binding
        this.conditionBind = newCondition && bindingRegistry.getBinding(newCondition) || null;
        // add listener if we are enabled
        if (this.conditionBind && this._enabled) {
            this.conditionBind.addEventListener(valueChangedEventType, this.onChangedListener);
        }
        // initialize fCachedValue so we can detect changes going forward in order to fire events.
        this.cachedValue = !!(this.conditionBind && this.conditionBind.getValue());
    }
    dispose() {
        if (this.conditionBind) {
            this.conditionBind.removeEventListener(valueChangedEventType, this.onChangedListener);
            this.conditionBind = null;
        }
    }
}

/**
 *  Copyright (c) 2020, 2022 Texas Instruments Incorporated
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
/**
 * Factory method to create instances of event triggers.
 *
 * @example
 * ```typescript
 * import { createTrigger } from '<path-to>/gc-core-databind/lib/CoreDatabind';
 *
 * const trigger = createTrigger( () => console.log('event triggered), 'widget.checkbox_1.checked === false');
 * trigger.enabled = false;  // if you wish to stop the callbacks for any reason.
 * ```
 *
 * @param callback callback method for when trigger condition is met.
 * @param condition a binding expression, that evaluates to a boolean result, to be used as the condition.
 * @returns newly created ITrigger instance.
 */
function createTrigger(callback, condition) {
    return new Trigger(callback, condition);
}

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
var STATE;
(function (STATE) {
    STATE[STATE["IDLE"] = 0] = "IDLE";
    STATE[STATE["READ"] = 1] = "READ";
    STATE[STATE["WRITE"] = 2] = "WRITE";
    STATE[STATE["DELAYED_WRITE"] = 3] = "DELAYED_WRITE";
    STATE[STATE["DELAYED_READ"] = 4] = "DELAYED_READ";
    STATE[STATE["ERROR_STATE"] = 99] = "ERROR_STATE";
})(STATE || (STATE = {}));
var QUALIFIER;
(function (QUALIFIER) {
    QUALIFIER["READONLY"] = "readonly";
    QUALIFIER["WRITEONLY"] = "writeonly";
    QUALIFIER["NONVOLATILE"] = "nonvolatile";
    QUALIFIER["CONST"] = "const";
    QUALIFIER["INTERRUPT"] = "interrupt";
    QUALIFIER["NOVERIFY"] = "noverify"; // skip verify on write.
})(QUALIFIER || (QUALIFIER = {}));
/**
 * Abstract class that implements IBindValue interface for clients that need
 * asynchronous access to values for the purposes of reading and writing.
 * This class assumes polling is required to read the value. If this is not
 * the case, you probably do not need to derive from this abstract class.
 * This class implements a IDLE/READ/WRITE/DELAYED_WRITE state machine to
 * keep reads and write synchronous and to prevent a build up of pending
 * operations if the backend process cannot keep up. Clients need only
 * implement readValue() and writeValue() to perform the asynchronous
 * actions and use the callbacks provided to signal when operation is
 * complete. To trigger a refresh of the read value there is an onRefresh()
 * api to call. This should be called in the constructor as well to kick
 * start the state machine to read the initial value. This constructor needs
 * to be called from the derived classes constructor as well. For example,
 * gc.databind.AbstractAsyncBindValue.call(this);
 *
 * @constructor
 * @extends gc.databind.AbstractLookupBindValue
 * @implements gc.databind.IDisposable
 */
class AbstractAsyncBindValue extends AbstractLookupBindValue {
    constructor(defaultType = 'string') {
        super(defaultType);
        this.state = STATE.IDLE;
        this.hasListeners = false;
        this.readable = true;
        this.writable = true;
        this.volatile = true;
        this.verifiable = true;
        this.onDone = (newValue) => {
            if (this.state === STATE.DELAYED_WRITE) {
                this.changeState(STATE.WRITE);
                return this.writeValue(this.committedValue).then(() => {
                    if (this.delayedProgress) {
                        this.delayedProgress.done();
                        this.delayedProgress = undefined;
                    }
                    return this.onDone();
                });
            }
            else if (this.state === STATE.WRITE || this.state === STATE.DELAYED_READ || (this.state === STATE.READ && this.isConnected() === false)) {
                if (this.readable && !this.isDeferredWritePending() && (this.state !== STATE.WRITE || this.verifiable)) {
                    // read back the value to see if the value we wrote stuck.
                    this.changeState(STATE.READ);
                    return this.readValue().then((newValue) => {
                        if (this.delayedProgress) {
                            this.delayedProgress.done();
                            this.delayedProgress = undefined;
                        }
                        return this.onDone(newValue);
                    });
                }
                else {
                    this.changeState(STATE.IDLE);
                }
            }
            else if (this.state === STATE.READ) {
                this.changeState(STATE.IDLE, newValue);
                // ignore newly read value if a deferred value is pending to be written
                if (!this.isDeferredWritePending()) {
                    // Ensure readValue() implementation is not reusing array buffers which will cause problems.
                    if (newValue === this.cachedValue && Array.isArray(newValue)) {
                        GcConsole.error(NAME, 'An array buffer is being reused for readValue() operations.  Please call slice() on the array before returning it.');
                    }
                    this.committedValue = newValue; // make sure fCachedValue === fCommittedValue is maintained.
                    this.updateValue(newValue);
                    this.setStale(false);
                }
            }
        };
        this.refreshPromise = Promise.resolve();
        this.setStale(true);
        this.onRefresh = (details) => {
            this.refresh(details.progress, false); // don't force a read operation if there aren't any listeners
        };
        const firstAddedHandler = () => {
            if (!this.hasListeners) {
                this.hasListeners = true;
                if (this.isRefreshable()) {
                    this.kickStartAReadOperation(true); // kick start an update
                }
            }
        };
        const lastRemovedHandler = () => {
            this.hasListeners = this.hasAnyListeners(valueChangedEventType) || this.hasAnyListeners(streamingDataEventType);
        };
        this.addEventListenerOnFirstAdded(valueChangedEventType, firstAddedHandler);
        this.addEventListenerOnFirstAdded(streamingDataEventType, firstAddedHandler);
        this.addEventListenerOnLastRemoved(valueChangedEventType, lastRemovedHandler);
        this.addEventListenerOnLastRemoved(streamingDataEventType, lastRemovedHandler);
    }
    /**
     * Method to set a qualifier to this binding.  Valid qualifiers for AbstractAsyncBindValue are:
     * <ul>
     * <li>const - assumes the binding will not change so read once, and prevent modification.</li>
     * <li>readonly - assumes the binding will change, but prevent modification.</li>
     * <li>writeonly - assumes the binding value cannot be read back, and allow modification</li>
     * <li>nonvolatile - assumes the binding can only be modified by the user, so read once and allow modification.</li>
     * <li>noverify - skips verifying writes by reading back the value immediately after a write.
     * </ul>
     *
     * Nonvolatile and noverify can be combined by calling setQuailifer() twice, once for each.  Other combinations are not
     * really applicable.
     *
     * @param {string} qualifier - the name of the qualifier to add: 'readonly', 'const', 'writeonly', or 'nonvolatile'.
     *        called when the read operation has finished.
     */
    setQualifier(qualifier) {
        // const = readable
        // readOnly = readable, volatile
        // writeOnly = writable
        // nonvolatile = readable, writable
        //  QUALIFIER.INTERRUPT = readable
        const wasVolatileBefore = this.volatile;
        if (qualifier === QUALIFIER.CONST || qualifier === QUALIFIER.READONLY || qualifier === QUALIFIER.INTERRUPT) {
            this.writable = false;
        }
        if (qualifier === QUALIFIER.WRITEONLY) {
            this.readable = false;
        }
        if (qualifier === QUALIFIER.NONVOLATILE || qualifier === QUALIFIER.CONST || qualifier === QUALIFIER.WRITEONLY || qualifier === QUALIFIER.INTERRUPT) {
            this.volatile = false;
        }
        if (qualifier === QUALIFIER.NOVERIFY || !this.readable || !this.writable) {
            this.verifiable = false;
        }
        // validate multiple qualifiers haven't created an invalid state
        if (!(this.readable || this.writable)) {
            // can't read or write the target
            GcConsole.error(NAME, `Invalid qualifier .$ QUALIFIER.WRITEONLY added to binding "${this.toString()}" that already has an existing .$readonly or .$const qualifier.`);
        }
        // kick start the read-once option
        if (wasVolatileBefore) {
            this.kickStartAReadOperation();
        }
    }
    changeState(newState, newValue) {
        this.state = newState;
        if (AbstractAsyncBindValue.DEBUG_BINDING && this.toString().indexOf(AbstractAsyncBindValue.DEBUG_BINDING) >= 0) {
            // the following code converts state number to a readable description, but it also
            // provides an opportunity to set breakpoints when entering particular states for a particular binding.
            GcConsole.log(NAME, `${this.toString()} state = ${this.getState()} value = ${newValue || this.cachedValue}`);
        }
    }
    getState() {
        return STATE[this.state];
    }
    onValueChanged(details) {
        this.setStale(false); // ensure no longer stale if value set first before reading from target.
        let allowWriteOperation = true;
        if (this.parentModel && this.parentModel._ignoreWriteOperationsWhenDisconnected) {
            // when _ignoreWriteOperationsWhenDisconnected is true, allow write operation only when connected.
            allowWriteOperation = this.isConnected();
        }
        if (this.writable && !this.deferredMode && allowWriteOperation) {
            // dispatch a custom event to log the write command for script recording
            this.parentModel?.fireScriptLogEvent({
                command: 'write',
                name: this.name || '',
                value: details.newValue
            });
            this.committedValue = this.cachedValue;
            if (this.state === STATE.IDLE || this.state === STATE.ERROR_STATE) {
                this.changeState(STATE.WRITE);
                details.progress.wait();
                this.refreshPromise = this.writeValue(this.cachedValue).then(() => {
                    details.progress.done();
                    return this.onDone();
                });
            }
            else {
                this.changeState(STATE.DELAYED_WRITE);
                if (this.delayedProgress) {
                    this.delayedProgress.done();
                }
                details.progress.wait();
                this.delayedProgress = details.progress;
            }
        }
    }
    refreshAndLog(progress) {
        // dispatch a custom event to log the read command for script script recording
        this.parentModel?.fireScriptLogEvent({
            command: 'read',
            name: this.name || ''
        });
        return this.refresh(progress);
    }
    /**
     * Helper method to test if this binding can be refreshed.  For example,
     * is it volatile, does it have listeners, etc...
     *
     * @protected
     */
    isRefreshable() {
        // volatile implies readable, so we don't have to test for this.readable as well here.
        return this.state === STATE.IDLE && this.volatile && !this.isDeferredWritePending();
    }
    refresh(progress = nullProgressCounter, force = true) {
        if (this.isRefreshable() && (this.hasListeners || force)) {
            progress.wait();
            this.changeState(STATE.READ);
            this.refreshPromise = this.readValue().then((result) => {
                progress.done();
                return this.onDone(result);
            });
        }
        return this.refreshPromise;
    }
    /**
     * Method to initiate a read operation, if appropriate, separate from onRefresh() handling.
     * This is use, for example, to read nonvolatile values once at the start, or when critical
     * errors have been cleared for example.
     *
     * @param {boolean} [force] - flag to force a read operation.
     */
    kickStartAReadOperation(force) {
        // kick start the read for nonvolatile readable bindings.
        if (force || (this.state === STATE.IDLE && !this.volatile && this.readable && !this.isDeferredWritePending())) {
            // we need to read this variable at least once in the beginning,
            // because it will
            // not be triggered by adding listeners or refresh timeouts.
            this.changeState(STATE.READ);
            this.refreshPromise = this.readValue().then(this.onDone);
        }
    }
    onDisconnected() {
        // clear any critical errors, which should restart the state machine
        this.reportCriticalError(null);
        this.kickStartAReadOperation();
    }
    /**
     * Method to set critical errors on this binding.  Critical errors are handled
     * differently in that the polling of a binding that has a critical error is suspended.
     * Normal errors do not suspend polling and therefore the error may get cleared when
     * the problem goes away.  This method is also used to clear critical errors when they are no
     * longer a problem by passing in a null or undefined parameter.
     *
     * @param {gc.databind.IStatus} [criticalError] - an error status to report as critical,
     * if absent or null, the previous critical error is cleared.
     */
    reportCriticalError(criticalError) {
        if (criticalError) {
            // prevent further target access until the critical error is
            // cleared.
            this.changeState(STATE.ERROR_STATE);
        }
        else if (this.state === STATE.ERROR_STATE) {
            this.changeState(STATE.IDLE);
            this.kickStartAReadOperation(this.readable);
        }
        this.status = criticalError;
    }
    get readOnly() {
        return !this.writable;
    }
    onIndexChanged() {
        if (this.hasListeners && this.volatile) {
            if (this.state === STATE.READ) {
                this.changeState(STATE.DELAYED_READ);
            }
            else {
                this.refresh();
            }
        }
    }
    setDeferredMode(deferredMode = false, progress = nullProgressCounter, forceWrite = false) {
        if (deferredMode !== this.deferredMode) {
            const oldValue = this.committedValue;
            const newValue = this.cachedValue;
            const doWrite = !deferredMode && (forceWrite || this.isValueNotEqualTo(oldValue));
            super.setDeferredMode(deferredMode);
            // write deferred value when transitioning out of deferred mode, if appropriate.
            if (doWrite) {
                this.onValueChanged({ oldValue, newValue, progress });
            }
        }
    }
    setRefreshIntervalProvider(refreshIntervalProvider) {
        // remove listener from existing provider, if there is one.
        if (this.refreshIntervalProvider) {
            this.refreshIntervalProvider.removeEventListener(refreshEventType, this.onRefresh);
        }
        // assign new provider
        this.refreshIntervalProvider = refreshIntervalProvider;
        // add listener for new provider, if there is one.
        if (this.refreshIntervalProvider) {
            this.refreshIntervalProvider.addEventListener(refreshEventType, this.onRefresh);
        }
    }
    dispose() {
        // clear any refresh interval providers if there are any.
        this.setRefreshIntervalProvider();
    }
}

class DataStorageProvider {
    static addDataModel(dataProvider) {
        this.dataModels.set(dataProvider.id, dataProvider);
    }
    static removeDataModel(dataProvider) {
        this.dataModels.delete(dataProvider.id);
    }
    static readDataForSave() {
        const data = {};
        this.dataModels.forEach((dataProvider, providerName) => {
            data[providerName] = this.readData(dataProvider);
        });
        return data;
    }
    static writeDataForLoad(data) {
        this.dataModels.forEach((dataProvider, providerName) => {
            const modelData = data[providerName];
            if (modelData) {
                this.writeData(dataProvider, modelData);
            }
        });
    }
    static readData(model) {
        const data = {};
        model.getAllBindings().forEach((bind, bindName) => {
            if (bind && !bind.readOnly && !bind.excludeFromStorageProviderData) {
                data[bindName] = bind.getValue();
            }
        });
        return data;
    }
    static writeData(model, data) {
        for (const bindName in data) {
            // eslint-disable-next-line no-prototype-builtins
            if (data.hasOwnProperty(bindName)) {
                const bind = model.getAllBindings().get(bindName);
                if (bind) {
                    bind.setValue(data[bindName]);
                }
            }
        }
    }
}
DataStorageProvider.dataModels = new Map();

/**
 * Class that implements IBindValue for a refresh interval value.  Clients can
 * set the interval (in milliseconds) by calling setValue().  Also, clients can
 * register for onRefresh() listeners that will be called periodically based on
 * the current refresh interval.  This class is useful for providing the polling
 * events other bindings that need to poll to detect changes.
 *
 * @constructor
 * @extends gc.databind.VariableBindValue
 * @implements gc.databind.IValueBind
 */
class RefreshIntervalBindValue extends VariableBindValue {
    constructor(defaultValue = 100) {
        super(defaultValue);
        this.hasListeners = false;
        this.excludeFromStorageProviderData = true;
        this.doOnRefresh = this.onRefresh.bind(this);
        this.doOnResetTimer = this.onResetTimer.bind(this);
        this.addEventListenerOnFirstAdded(refreshEventType, () => {
            this.hasListeners = true;
            this.onResetTimer();
        });
        this.removeEventListenerOnLastRemoved(refreshEventType, () => {
            this.hasListeners = false;
        });
    }
    // eslint-disable-next-line @typescript-eslint/no-unused-vars
    onValueChanged(details) {
        this.excludeFromStorageProviderData = false;
        this.onResetTimer(); // kick start timer in case new value is not negative.
    }
    dispose() {
        if (this.timer) {
            clearTimeout(this.timer);
            this.timer = undefined;
        }
    }
    async onRefresh(progressCounter) {
        // clear outstanding timer if there is one.
        if (this.timer) {
            clearTimeout(this.timer);
            this.timer = undefined;
        }
        let progress = new ProgressCounter();
        this.fireEvent(preRefreshEventType, { progress });
        progress.done();
        if (progress.getProgress() < 100) { // test if promise is resolve without waiting for next clock tick.
            await progress.promise;
        }
        progress = progressCounter ?? new ProgressCounter(this.doOnResetTimer);
        this.fireEvent(refreshEventType, { progress });
        progress.done();
        return await progress.promise;
    }
    onResetTimer() {
        // only restart the timer if we have listeners and a timer is not pending.
        if (this.timer === undefined && this.hasListeners) {
            const delay = this.getValue();
            if (delay >= 0) {
                this.timer = setTimeout(this.doOnRefresh, delay);
            }
        }
    }
    onDisconnected() {
        if (this.timer === undefined && this.hasListeners) {
            const delay = this.getValue();
            if (delay < 0) {
                // kick start a refresh in case we aren't polling, and we need to queue up one read operation for the next
                // time we connect.
                this.onRefresh();
            }
        }
    }
}

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
/**
 * Abstract class that provides default implementation of IBindFactory for a polling data model.  This class
 * provides a "$refresh_interval" binding can be used to control the polling interval any bindings that are created.
 * Alternatively, each binding could have it's own polling interval as needed.  The $refresh_interval is available
 * to app developers so that they could allow end users to control the polling interval.  The refresh interval represents
 * a delay between polling cycles, and does not reflect real time constraints.  This way if refresh interval is too short
 * it doesn't backlog polling operations, instead it simply polls as fast as possible.
*/
class AbstractPollingDataModel extends AbstractBindFactory {
    /**
     * @param name uniquely identifiable name for this bind factory.
     * @param defaultRefreshInterval the default interval for polling in milliseconds.
     */
    constructor(name, defaultRefreshInterval = 100) {
        super(name);
        this.defaultRefreshInterval = defaultRefreshInterval;
        DataStorageProvider.addDataModel(this);
        this.defaultRefreshBinding = new RefreshIntervalBindValue(defaultRefreshInterval);
        this.modelBindings.set('$refresh_interval', this.defaultRefreshBinding);
        this.refreshIntervalBindList = [this.defaultRefreshBinding];
    }
    createNewBind(uri) {
        let result = null;
        if (uri.indexOf('$refresh_interval.') === 0) {
            result = new RefreshIntervalBindValue(this.defaultRefreshInterval);
            this.refreshIntervalBindList.push(result);
        }
        return result;
    }
    /**
     * Helper method to refresh, or re-read, all bindings associated with this model.  This method goes through
     * all refresh interval providers created by this model and forces them to refresh all their bindings that are
     * registered with them.
     *
     * @param progress a progress counter to optionally use for this operation.
     * @returns a promise that resolves to the number of registers refreshed by this method.
     */
    async refreshAllBindings(progress) {
        const results = await Promise.all(this.refreshIntervalBindList.map(refreshBind => refreshBind.onRefresh(progress)));
        return results.reduce((total, result) => total + result);
    }
    /**
     * Implementation for reading value from the target.
     *
     * @param uri the name of the binding to read
     * @returns a promise that resolves to the value read.
     */
    async scriptRead(uri) {
        const binding = this.getBinding(uri);
        if (binding && binding.refresh) {
            await binding.refresh();
            return binding.getValue();
        }
        else {
            return super.scriptRead(uri);
        }
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
const errorBind = new ConstantBindValue();
class ReferenceBindValue extends AbstractUnaryOperator {
    constructor(name) {
        super(errorBind);
        this.name = name;
        this.operator = '&';
        this.operand = errorBind;
        this.excludeFromStorageProviderData = true;
        this.name = name;
        this.updateReferenceBinding();
    }
    getValue() {
        return this.operand.getValue();
    }
    setValue(value, progress, force) {
        this.operand.setValue(value, progress, force);
    }
    moveListeners(oldBind, newBind) {
        this.forEachEventListener(statusChangedEventType, (listener) => {
            if (oldBind) {
                oldBind.removeEventListener(statusChangedEventType, listener);
            }
            if (newBind) {
                newBind.addEventListener(statusChangedEventType, listener);
            }
        });
        this.forEachEventListener(staleChangedEventType, (listener) => {
            if (oldBind) {
                oldBind.removeEventListener(staleChangedEventType, listener);
            }
            if (newBind) {
                newBind.addEventListener(staleChangedEventType, listener);
            }
        });
        this.forEachEventListener(valueChangedEventType, (listener) => {
            if (oldBind) {
                oldBind.removeEventListener(valueChangedEventType, listener);
            }
            if (newBind) {
                newBind.addEventListener(valueChangedEventType, listener);
            }
        });
        this.forEachEventListener(streamingDataEventType, (listener) => {
            if (oldBind) {
                oldBind.removeEventListener(streamingDataEventType, listener);
            }
            if (newBind) {
                newBind.addEventListener(streamingDataEventType, listener);
            }
        });
    }
    updateReferenceBinding(bindExpression, model) {
        // create new reference bind from expression
        const oldBind = this.operand;
        let newBind = null;
        const oldValue = oldBind.getValue();
        const oldIsStale = oldBind.isStale();
        const oldStatus = oldBind.status;
        this.bindExpression = bindExpression;
        try {
            if (bindExpression) {
                if (model) {
                    newBind = model.parseModelSpecificBindExpression(bindExpression);
                }
                else {
                    newBind = bindingRegistry.getBinding(bindExpression);
                }
            }
            if (newBind === null) {
                throw new Error(`The calculated binding "${this.toString()}" is not defined for this device.`);
            }
        }
        catch (e) {
            // create error bind for reference if no binding exists.
            newBind = new ConstantBindValue();
            newBind.status = Status.createErrorStatus(e.message);
        }
        // move listeners from the old reference binding to the new reference binding.
        if (oldBind === newBind) {
            return;
        }
        this.moveListeners(oldBind, newBind);
        this.operand = newBind;
        const newValue = this.operand.getValue();
        const newIsStale = this.operand.isStale();
        const newStatus = this.operand.status;
        // fire events to update to new state
        if (oldStatus !== newStatus) {
            this.fireEvent(statusChangedEventType, { oldStatus, newStatus, bind: this });
        }
        if (oldIsStale !== newIsStale) {
            this.fireEvent(staleChangedEventType, { stale: newIsStale });
        }
        if (oldValue !== newValue) {
            this.fireEvent(valueChangedEventType, { oldValue, newValue, progress: nullProgressCounter });
        }
    }
}

/**
 *  Copyright (c) 2020, 2022 Texas Instruments Incorporated
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
/* eslint-disable @typescript-eslint/no-unused-vars */
/**
 * Class that implements ILookupBindValue interface for a variable lookup value binding.
 * Use this class if you wish to create a lookup binding based on a given array or struct data pointer.
 */
class VariableLookupBindValue extends AbstractLookupBindValue {
    /**
     * Constructor for AbstractLookupBindValue.
     *
     * @param data the constant array or object data to use for lookups.
     * @param readOnly flag to indicate if setValue() method should be allowed to modify the data.
     */
    constructor(data, readOnly = false) {
        super();
        this._readOnly = readOnly;
        this.setData(data);
    }
    get readOnly() {
        return this._readOnly;
    }
    setValue(value, progress, forceWrite) {
        if (!this.readOnly) {
            // allow this value to be modified.
            super.setValue(value, progress, forceWrite);
        }
    }
    /**
     * Implemented to use the data provided to lookup values based on index changes.
     * The data must be an array or object type with nested arrays or objects as needed.
     * The index must be numeric for array types and string for object types.
     * This method calls setValue() to update this bindings
     * value and notify listeners based on the new index values.
     *
     * @param indices the multi-dimensional index values to use for lookup.
     */
    onIndexChanged(indices) {
        let value = this.data;
        try {
            for (let i = 0; value !== undefined && indices !== undefined && i < indices.length; i++) {
                let index = indices[i];
                if (index === null || index === undefined) {
                    throw new Error('The index value is null.');
                }
                if (value instanceof Array) {
                    value = value[this.assertValidArrayIndex(index, value.length)];
                }
                else if (typeof value === 'object') {
                    const fields = index.toString().split('.');
                    for (let j = 0; j < fields.length; j++) {
                        index = fields[j];
                        value = value[index];
                        if (value === undefined) {
                            this.assertValidFieldName(index);
                        }
                    }
                }
                else {
                    this.assertValidData(index);
                }
            }
            this.status = null; // if no exceptions clear errors
        }
        catch (e) {
            value = undefined;
            this.status = Status.createErrorStatus(e.message);
        }
        this.updateValue(value);
    }
    setData(data) {
        this.data = data;
        this.onIndexChanged(this.indexValues);
    }
    getData() {
        return this.data;
    }
    toString() {
        try {
            return JSON.stringify(this.data);
        }
        catch (e) {
            return '' + this.data;
        }
    }
    // eslint-disable-next-line @typescript-eslint/no-empty-function
    onValueChanged(details) {
    }
}

/**
 *  Copyright (c) 2020, 2022 Texas Instruments Incorporated
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

export { AbstractAsyncBindValue, AbstractBind, AbstractBindFactory, AbstractBindValue, AbstractLookupBindValue, AbstractPollingDataModel, ArrayOperator, BindingRegistry, ConstantBindValue, DataBinder, DataConverter, DataFormatterRegistry, DataStorageProvider, FunctionBindValue, MathModel, NAME, ProgressCounter, PropertyModel, QUALIFIER, ReferenceBindValue, RefreshIntervalBindValue, Status, StatusType, UserPreferenceBindValue, VariableBindValue, VariableLookupBindValue, WidgetModel, bindingRegistry, blockNewEditUndoOperationCreation, createTrigger, isDisposable, nullProgressCounter, preRefreshEventType, refreshEventType, scriptLogEventType, staleChangedEventType, statusChangedEventType, streamingDataEventType, userEditEvent, valueChangedEventType };
//# sourceMappingURL=CoreDatabind.js.map
