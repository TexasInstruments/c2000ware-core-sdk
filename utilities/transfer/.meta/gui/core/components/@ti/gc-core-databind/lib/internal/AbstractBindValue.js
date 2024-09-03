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
import { AbstractBind } from './AbstractBind';
import { valueChangedEventType, streamingDataEventType, staleChangedEventType } from './IBindValue';
import { nullProgressCounter } from './ProgressCounter';
/* eslint-disable @typescript-eslint/no-unused-vars */
export let blockNewEditUndoOperationCreation = false;
/**
 * Abstract class that implements IBindValue interface.
 */
export class AbstractBindValue extends AbstractBind {
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
        if (newValue instanceof Array && oldValue instanceof Array && newValue.length === oldValue.length) {
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
//# sourceMappingURL=AbstractBindValue.js.map