/**
 *  Copyright (c) 2020, 2023 Texas Instruments Incorporated
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
import { valueChangedEventType } from './IBindValue';
import { AbstractBindValue, blockNewEditUndoOperationCreation } from './AbstractBindValue';
import { AbstractBindFactory } from './AbstractBindFactory';
import { NAME } from './IBind';
import { EventType } from '../../../gc-core-assets/lib/Events';
import { GcUtils } from '../../../gc-core-assets/lib/GcUtils';
import { GcConsole } from '../../../gc-core-assets/lib/GcConsole';
import { StatusIndicatorFactory } from './StatusIndicator';
export const userEditEvent = new EventType('user edit');
class EditOperation {
    constructor(bind, oldValue, newValue, time) {
        this.bind = bind;
        this.oldValue = oldValue;
        this.newValue = newValue;
        this.time = time;
    }
    undo() {
        this.bind.setValue(this.oldValue);
    }
    redo() {
        this.bind.setValue(this.newValue);
    }
    toString() {
        return 'edit';
    }
    canMergeOperation(bind, newValue, now) {
        // make sure it's also different from original value; e.g.,
        // checkbox toggled quickly.
        return bind === this.bind && now - this.time < 250 && this.oldValue !== newValue;
    }
    mergeOperation(newValue, time) {
        this.newValue = newValue;
        this.time = time;
        this.redo(); // perform action now.
    }
}
class WidgetBindValue extends AbstractBindValue {
    constructor(widgetId, widget, widgetProperty, initialValue, parent) {
        super();
        this.widgetProperty = widgetProperty;
        this.parent = parent;
        this.excludeFromStorageProviderData = true;
        this.doUserEditOperation = () => {
            const widget = this.widget;
            if (widget) {
                const oldValue = this.getValue();
                const newValue = this.readPropertyValue(widget);
                if (oldValue !== newValue) {
                    // eslint-disable-next-line @typescript-eslint/no-use-before-define
                    WidgetModel.doUserEditOperation(this, newValue, oldValue);
                    this.excludeFromStorageProviderData = false;
                }
            }
        };
        this.onFirstValueChangedListenerAdded = () => {
            const widget = this.widget;
            if (widget) {
                widget.addEventListener(this.changedPropertyEventName, this.doUserEditOperation);
                const oldStatus = this.status;
                if (oldStatus) {
                    // restore status indicators for the new widget.
                    widget.errorMessage = oldStatus.message;
                }
            }
        };
        this.onLastValueChangedListenerRemoved = () => {
            const widget = this.widget;
            if (widget) {
                widget.removeEventListener(this.changedPropertyEventName, this.doUserEditOperation);
                const oldStatus = this.status;
                if (oldStatus) {
                    // remove status indicators that are tied to this widget
                    widget.errorMessage = undefined;
                }
                // next time we have to bind to the widget, lets use a fresh widget pointer
                // this way we support unbind from widgets, recreate widgets, then bind to new widgets.
                this._widget = undefined;
            }
        };
        this.widgetId = widgetId;
        this._widget = widget;
        this.cachedValue = initialValue;
        this.changedPropertyEventName = GcUtils.camelToDashCase(widgetProperty) + '-changed';
        this.addEventListenerOnFirstAdded(valueChangedEventType, this.onFirstValueChangedListenerAdded);
        this.addEventListenerOnLastRemoved(valueChangedEventType, this.onLastValueChangedListenerRemoved);
        const streamingListener = widget[widgetProperty + 'StreamingDataListener'];
        if (streamingListener && typeof streamingListener === 'function') {
            this.onStreamingDataReceived = streamingListener.bind(widget);
        }
    }
    writePropertyValue(widget, newValue) {
        widget[this.widgetProperty] = newValue;
    }
    onValueChanged(details) {
        this.excludeFromStorageProviderData = true;
        const widget = this.widget;
        if (widget) {
            // widget available, so update property
            this.writePropertyValue(widget, details.newValue);
        }
    }
    get widget() {
        this._widget = this._widget || WidgetModel.findWidget(this.widgetId, this.parent || document) || undefined;
        return this._widget;
    }
    onStatusChanged(details) {
        const statusIndicator = StatusIndicatorFactory.get(this.widget);
        if (!statusIndicator) {
            return;
        }
        if (details.oldStatus) {
            statusIndicator.removeMessage(details.oldStatus.message);
        }
        if (details.newStatus) {
            statusIndicator.addMessage(details.newStatus.message, details.newStatus.type);
        }
    }
    readPropertyValue(widget) {
        return widget[this.widgetProperty];
    }
}
class WidgetStyleLookupBind extends WidgetBindValue {
    constructor(widgetId, widget, parent) {
        super(widgetId, widget, 'cssProperty', parent);
    }
    setIndex(...index) {
        this.cssPropertyName = '' + (index[0] || '');
        const widget = this.widget;
        if (widget) {
            this.updateValue(this.readPropertyValue(widget));
        }
    }
    readPropertyValue(widget) {
        var _a;
        if (this.cssPropertyName) {
            // using getComputedStyle(widget).getPropertyValue(name) because widget.getCSSProperty(name) returns a promise
            // and I need the value now.
            // eslint-disable-next-line @typescript-eslint/no-explicit-any
            return ((_a = getComputedStyle(widget).getPropertyValue(this.cssPropertyName)) === null || _a === void 0 ? void 0 : _a.trim()) || '';
        }
        return undefined;
    }
    writePropertyValue(widget, newValue) {
        var _a;
        if (this.cssPropertyName && typeof newValue === 'string') {
            if (widget.setCSSProperty) {
                (_a = widget.setCSSProperty) === null || _a === void 0 ? void 0 : _a.call(widget, this.cssPropertyName, newValue);
            }
            else {
                widget.style.setProperty(this.cssPropertyName, newValue.trim());
            }
        }
    }
}
export class WidgetModel extends AbstractBindFactory {
    constructor(rootElement) {
        super('widget');
        this.rootElement = rootElement;
    }
    static findWidgetShallow(parent, uri) {
        const query = `[id="${uri.split('.').join('"] [id="')}"]`;
        const result = parent.querySelector(query);
        return result;
    }
    static findWidget(deepUri, from) {
        const shallowUri = deepUri.split('.$.');
        let result = this.findWidgetShallow(from, shallowUri[0]);
        for (let i = 1; result && i < shallowUri.length; i++) {
            if (result.shadowRoot) {
                result = this.findWidgetShallow(result.shadowRoot, shallowUri[i]);
            }
            else {
                GcConsole.error(NAME, `Cannot access shadow dom of widget ${shallowUri[i - 1]} in ${deepUri}`);
                return null;
            }
        }
        if (!result) {
            GcConsole.error(NAME, `Failed to find widget ${deepUri}.`);
        }
        return result;
    }
    createNewBind(name) {
        let bind = null;
        const pos = name.lastIndexOf('.');
        if (pos > 0) {
            const widgetName = name.substring(0, pos);
            const widgetProperty = name.substring(pos + 1);
            const widget = WidgetModel.findWidget(widgetName, this.rootElement || document);
            if (widget) {
                if (widgetProperty === 'style') {
                    bind = new WidgetStyleLookupBind(widgetName, widget, this.rootElement);
                }
                else {
                    bind = new WidgetBindValue(widgetName, widget, widgetProperty, widget[widgetProperty], this.rootElement);
                }
            }
        }
        return bind;
    }
    static clearLastUserEditOperation() {
        this.lastUndoOperation = undefined;
    }
    static doUserEditOperation(bind, newValue, oldValue) {
        const lastOperation = this.lastUndoOperation;
        const now = Date.now();
        if (lastOperation && lastOperation.canMergeOperation(bind, newValue, now)) {
            lastOperation.mergeOperation(newValue, now);
        }
        else if (oldValue !== undefined && newValue !== undefined && !blockNewEditUndoOperationCreation) {
            const operation = new EditOperation(bind, oldValue, newValue, now);
            this.instance.fireEvent(userEditEvent, { operation: operation });
            operation.redo();
            this.lastUndoOperation = operation;
        }
        else {
            bind.setValue(newValue);
        }
    }
    static async whenWidgetReady(widgetId) {
        if (GcUtils.isNodeJS) {
            return;
        }
        await this.documentContentLoaded;
        const shallowUri = widgetId.split('.$.')[0];
        const widget = this.findWidgetShallow(document, shallowUri);
        if (widget) {
            const customComponentName = widget.tagName.toLowerCase();
            if (customComponentName.indexOf('-') > 0) {
                await customElements.whenDefined(customComponentName);
                const waitForWidget = widget;
                if (typeof waitForWidget.waitForWidgetReady === 'function') {
                    const promise = waitForWidget.waitForWidgetReady();
                    if (promise instanceof Promise) {
                        await promise;
                    }
                }
            }
            else {
                throw Error(`Widget id="${widgetId} was not found in html document.`);
            }
        }
        return widget;
    }
}
WidgetModel.instance = new WidgetModel();
WidgetModel.documentContentLoaded = !GcUtils.isNodeJS && document.readyState === 'loading' ? new Promise(resolve => {
    document.addEventListener('DOMContentLoaded', () => resolve());
}) : Promise.resolve();
//# sourceMappingURL=WidgetModel.js.map