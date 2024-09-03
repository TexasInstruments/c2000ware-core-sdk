import { nullProgressCounter } from './ProgressCounter';
import { DataConverter } from './DataConverter';
export class CollectionBindValue {
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
//# sourceMappingURL=CollectionBindValue.js.map