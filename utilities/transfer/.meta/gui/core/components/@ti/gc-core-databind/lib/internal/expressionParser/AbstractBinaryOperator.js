import { nullProgressCounter } from '../ProgressCounter';
import { isDisposable } from '../IDisposable';
import { Status } from '../Status';
import { DataConverter } from '../DataConverter';
import { Events } from '../../../../gc-core-assets/lib/Events';
import { statusChangedEventType } from '../IBind';
export class AbstractBinaryOperatorFactory {
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
export class AbstractBinaryOperator extends Events {
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
//# sourceMappingURL=AbstractBinaryOperator.js.map