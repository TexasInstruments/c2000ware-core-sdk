import { streamingDataEventType, valueChangedEventType } from '../IBindValue';
import { isDisposable } from '../IDisposable';
import { nullProgressCounter } from '../ProgressCounter';
const openingBrace = '?';
const closingBrace = ':';
const OP = openingBrace + closingBrace;
class Factory {
    constructor() {
        this.operator = OP;
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
export class ConditionalOperator {
    constructor(condition, trueOperand, falseOperand) {
        this.condition = condition;
        this.trueOperand = trueOperand;
        this.falseOperand = falseOperand;
        this.operator = OP;
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
ConditionalOperator.factory = new Factory();
//# sourceMappingURL=ConditionalOperator.js.map