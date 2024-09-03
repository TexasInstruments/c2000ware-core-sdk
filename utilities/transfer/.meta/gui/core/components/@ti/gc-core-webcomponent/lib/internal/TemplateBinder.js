/**
 *  Copyright (c) 2021, 2022 Texas Instruments Incorporated
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
import { AbstractBindValue, WidgetModel, DataBinder } from '../../../gc-core-databind/lib/CoreDatabind';
import './IDomApi.js';
import './htmlParser.js';
class HostPropertyValueBind extends AbstractBindValue {
    constructor(property, propertyHelper) {
        super(property.type);
        this.property = property;
        this.propertyHelper = propertyHelper;
        propertyHelper.watch(property.name, (newValue) => {
            this.updateValue(newValue);
        });
        this.cachedValue = property.value;
    }
    onValueChanged(details) {
        this.propertyHelper.setValue(this.property, details.newValue);
    }
}
class TemplateBindingModel extends WidgetModel {
    constructor(shadowRoot, propertyManager) {
        super(shadowRoot);
        this.propertyManager = propertyManager;
    }
    createNewBind(uri) {
        if (uri.startsWith('$.')) {
            return super.createNewBind(uri.substring('$.'.length));
        }
        else {
            const property = this.propertyManager.getProperty(uri);
            if (property) {
                return new HostPropertyValueBind(property, this.propertyManager);
            }
        }
        return null;
    }
}
export class TemplateBinder {
    constructor(componentName, htmlText) {
        this.template = document.createElement('template');
        this.bindings = [];
        const parser = window.gc.htmlParserFactory.create(htmlText, 3);
        const annotations = parser.getAnnotations();
        if (annotations && annotations.length > 0) {
            const details = annotations[0];
            const errorMessage = `&lt;${componentName}&gt; has syntax ${details.type} on line ${details.row + 1}: ${details.text}`;
            this.template.innerHTML = `<gc-widget-icon icon="action:error_outline" appearance="error" size="l" tooltip="${errorMessage}"></gc-widget-icon>`;
        }
        else {
            this.bindings = parser.extractAllTemplateBindings();
            this.template.innerHTML = parser.getText();
        }
    }
    stampTemplate(shadowRoot, propertyManager, console, extraBindings) {
        // clone template
        const templateInstance = this.template.content.cloneNode(true);
        shadowRoot.appendChild(templateInstance);
        // create bindings
        const model = new TemplateBindingModel(shadowRoot, propertyManager);
        TemplateBinder.createBindings(model, this.bindings, console);
        if (extraBindings) {
            TemplateBinder.createBindings(model, extraBindings, console);
        }
        return model;
    }
    static createBindings(model, bindings, console) {
        bindings.forEach((binding) => {
            try {
                const modelBind = model.parseModelSpecificBindExpression(binding.serverBindName);
                if (!modelBind) {
                    console.error(`Can't bind to missing property: ${binding.serverBindName}`);
                }
                const targetBind = model.getBinding(`$.${binding.widgetId}.${binding.propertyName}`);
                if (!targetBind) {
                    console.error(`Can't bind to property: ${binding.propertyName}, on widget: ${binding.widgetId}`);
                }
                if (modelBind && targetBind) {
                    DataBinder.bind(targetBind, modelBind, undefined, undefined, binding.options && binding.options.oneWay);
                }
            }
            catch (error) {
                console.error(`Bind expression "${binding.serverBindName}" parsing error: ${error.message || error.toString()}`);
            }
        });
    }
    static async getInstance(componentName, htmlText, htmlFilepath) {
        let result = this.instances.get(componentName);
        if (!result) {
            if (!htmlText) {
                if (htmlFilepath) {
                    htmlText = await (await fetch(htmlFilepath)).text();
                }
                else {
                    throw Error('Missing template for custom component');
                }
            }
            result = new TemplateBinder(componentName, htmlText || '');
            this.instances.set(componentName, result);
        }
        return result;
    }
}
TemplateBinder.instances = new Map();
//# sourceMappingURL=TemplateBinder.js.map