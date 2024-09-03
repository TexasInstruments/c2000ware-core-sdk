import { valueChangedEventType } from './IBindValue';
import { bindingRegistry } from './BindingRegistry';
/**
 * Concrete Class for a Trigger that fires a user callback when a condition is met.
 */
export class Trigger {
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
//# sourceMappingURL=Trigger.js.map