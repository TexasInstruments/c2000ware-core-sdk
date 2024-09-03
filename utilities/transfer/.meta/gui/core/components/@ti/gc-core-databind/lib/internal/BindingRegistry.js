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
import { AbstractBindProvider } from './AbstractBindProvider';
import { isDisposable } from './IDisposable';
import { DataBinder } from './DataBinder';
import { NAME } from './IBind';
import { CollectionBindValue } from './CollectionBindValue';
import { Status } from './Status';
import { GcFiles } from '../../../gc-core-assets/lib/GcFiles';
import './DataFormatter'; // this is required to register $hex formatters for example.
import { MathModel } from './MathModel';
import { PropertyModel } from './PropertyModel';
import { GcConsole as console } from '../../../gc-core-assets/lib/GcConsole';
import { WidgetModel } from './WidgetModel';
import { GcUtils } from '../../../gc-core-assets/lib/GcUtils';
import { GcPromise } from '../../../gc-core-assets/lib/GcPromise';
import { ExpressionParserUtils } from './expressionParser/ExpressionParserUtils';
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
export class BindingRegistry extends AbstractBindProvider {
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
            console.log(NAME, `Model id=${name} is ready.`);
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
            console.error(NAME, e);
            return nullDataBinder;
        }
    }
    getDefaultBindingFile() {
        var _a;
        try {
            let path = (_a = document.querySelector('meta[name="gc-databinding-json-path"]')) === null || _a === void 0 ? void 0 : _a.content;
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
        var _a, _b, _c;
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
                                    ((((_a = widget.tagName.split('-')[1]) === null || _a === void 0 ? void 0 : _a.toLowerCase()) !== 'model') ||
                                        // @ts-ignore
                                        (widgetPrefixWasRemoved && bindSegments.length === 2 && ((_b = Object.getOwnPropertyDescriptor(widget.__proto__, bindSegments[1])) === null || _b === void 0 ? void 0 : _b.get)))) {
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
                console.error(NAME, `Cannot set default type on binding "${widgetBindName}" because it does not exist.`);
            }
        }
        // Binding records with no widgetId are used to initialize backplane bindings.
        if (!wb.widgetId && serverBindName && wb.options && (typeof wb.options.defaultValue !== 'undefined')) {
            const bind = this.getBinding(serverBindName);
            if (bind) {
                bind.setValue(wb.options.defaultValue);
            }
            else {
                console.error(NAME, `Cannot set default binding value because the binding "${wb.serverBindName}" does not exist.`);
            }
        }
        else {
            const binder = (_c = this.bind(widgetBindName, serverBindName)) !== null && _c !== void 0 ? _c : undefined;
            return binder;
        }
    }
    async doLoadBindingsFromFile(jsonFile) {
        const results = new BinderCollection();
        try {
            const data = await GcFiles.readJsonFile(jsonFile);
            console.log(NAME, () => `Started loading bindings from file ${jsonFile}`);
            if (data) {
                const promises = data.widgetBindings.map(wb => this.loadBinding(wb));
                const binders = await Promise.all(promises);
                binders.forEach(binder => results.add(binder));
            }
            console.log(NAME, () => `Finished loading bindings from file ${jsonFile}`);
        }
        catch (error) {
            console.error(NAME, error);
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
            console.error(NAME, error);
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
export const bindingRegistry = new BindingRegistry();
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
//# sourceMappingURL=BindingRegistry.js.map