import { VariableBindValue } from './VariableBindValue';
import { QualifierFactoryMap } from './QualifierFactoryMap';
import { scriptLogEventType } from './IScriptingTarget';
import { AbstractBindProvider } from './AbstractBindProvider';
import { ProgressCounter } from './ProgressCounter';
import { Events } from '../../../gc-core-assets/lib/Events';
import { GcPromise } from '../../../gc-core-assets/lib/GcPromise';
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
export class AbstractBindFactory extends Events {
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
//# sourceMappingURL=AbstractBindFactory.js.map