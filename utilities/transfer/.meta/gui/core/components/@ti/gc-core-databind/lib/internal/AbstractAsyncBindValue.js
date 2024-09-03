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
import { AbstractLookupBindValue } from './AbstractLookupBindValue';
import { nullProgressCounter } from './ProgressCounter';
import { NAME } from './IBind';
import { GcConsole as console } from '../../../gc-core-assets/lib/GcConsole';
import { valueChangedEventType, streamingDataEventType } from './IBindValue';
import { refreshEventType } from './IRefreshIntervalProvider';
var STATE;
(function (STATE) {
    STATE[STATE["IDLE"] = 0] = "IDLE";
    STATE[STATE["READ"] = 1] = "READ";
    STATE[STATE["WRITE"] = 2] = "WRITE";
    STATE[STATE["DELAYED_WRITE"] = 3] = "DELAYED_WRITE";
    STATE[STATE["DELAYED_READ"] = 4] = "DELAYED_READ";
    STATE[STATE["ERROR_STATE"] = 99] = "ERROR_STATE";
})(STATE || (STATE = {}));
export var QUALIFIER;
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
export class AbstractAsyncBindValue extends AbstractLookupBindValue {
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
                        console.error(NAME, 'An array buffer is being reused for readValue() operations.  Please call slice() on the array before returning it.');
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
            console.error(NAME, `Invalid qualifier .$ QUALIFIER.WRITEONLY added to binding "${this.toString()}" that already has an existing .$readonly or .$const qualifier.`);
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
            console.log(NAME, `${this.toString()} state = ${this.getState()} value = ${newValue || this.cachedValue}`);
        }
    }
    getState() {
        return STATE[this.state];
    }
    onValueChanged(details) {
        var _a;
        this.setStale(false); // ensure no longer stale if value set first before reading from target.
        let allowWriteOperation = true;
        if (this.parentModel && this.parentModel._ignoreWriteOperationsWhenDisconnected) {
            // when _ignoreWriteOperationsWhenDisconnected is true, allow write operation only when connected.
            allowWriteOperation = this.isConnected();
        }
        if (this.writable && !this.deferredMode && allowWriteOperation) {
            // dispatch a custom event to log the write command for script recording
            (_a = this.parentModel) === null || _a === void 0 ? void 0 : _a.fireScriptLogEvent({
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
        var _a;
        // dispatch a custom event to log the read command for script script recording
        (_a = this.parentModel) === null || _a === void 0 ? void 0 : _a.fireScriptLogEvent({
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
//# sourceMappingURL=AbstractAsyncBindValue.js.map