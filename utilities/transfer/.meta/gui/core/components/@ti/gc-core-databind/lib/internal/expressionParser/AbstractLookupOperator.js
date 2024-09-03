import { isDisposable } from '../IDisposable';
import { valueChangedEventType, staleChangedEventType } from '../IBindValue';
import { nullProgressCounter } from '../ProgressCounter';
export class AbstractLookupOperator {
    constructor(lookupBinding, indexBindings) {
        this.lookupBinding = lookupBinding;
        this.indexBindings = indexBindings;
        this.cachedIndecies = [];
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
        const indecies = [];
        let i = 0;
        for (; i < this.indexBindings.length; i++) {
            const indexBinding = this.indexBindings[i];
            if (indexBinding.isStale()) {
                // postpone calling setIndex on lookupBinding until all indecies have
                // non stale values.  We only have to listen to one stale index at a time.
                if (this.staleIndexBinding === undefined) {
                    const listener = () => {
                        indexBinding.removeEventListener(staleChangedEventType, listener);
                        this.setIndex(...this.cachedIndecies);
                    };
                    indexBinding.addEventListener(staleChangedEventType, listener);
                }
                this.cachedIndecies = args;
                return;
            }
            indecies.push(indexBinding.getValue());
        }
        for (i = 0; i < args.length; i++) {
            indecies.push(args[i]);
        }
        this.lookupBinding.setIndex(...indecies);
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
export function testLookupBinding(lookupBinding, operator) {
    if (lookupBinding === null) {
        throw new Error(`Missing the left operand for the ${operator} operator.`);
    }
    if (!(lookupBinding.setIndex)) {
        const text = operator === '()' ? 'a function' : operator === '.' ? 'an object' : 'an array';
        throw new Error(`'${lookupBinding.toString()}' is not ${text} type.  It cannot be used with the ${operator} operator.`);
    }
}
//# sourceMappingURL=AbstractLookupOperator.js.map