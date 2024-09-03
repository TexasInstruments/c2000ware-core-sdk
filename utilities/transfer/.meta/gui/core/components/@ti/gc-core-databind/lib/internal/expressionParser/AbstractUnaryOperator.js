import { Events } from '../../../../gc-core-assets/lib/Events';
import { Status } from '../Status';
import { isDisposable } from '../IDisposable';
import { nullProgressCounter } from '../ProgressCounter';
import { statusChangedEventType } from '../IBind';
export class AbstractUnaryOperatorFactory {
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
export class AbstractUnaryOperator extends Events {
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
//# sourceMappingURL=AbstractUnaryOperator.js.map