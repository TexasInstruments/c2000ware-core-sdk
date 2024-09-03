import { GcConsole } from '../../gc-core-assets/lib/GcConsole';
import { GcUtils } from '../../gc-core-assets/lib/GcUtils';

/**
 *  Copyright (c) 2020, 2024 Texas Instruments Incorporated
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
 *
 */
/**
 * `GcWidget` utility functions to query select element(s) and wait for the custom
 * element to be defined. Use these helpers to query GUI Composer element(s) only.
 * Use the browser's native querySelector functions to query other element(s).
 *
 * @example
 * ```typescript
 * import { GcWidget } from '<path-to>/gc-widget-base/lib/GcWidget';
 *
 * const domReady = async () => {
 *     const menubar = await GcWidget.querySelector('gc-widget-menubar');
 *     const button = await GcWidget.querySelector('#my-button-id');
 * };
 * document.readyState === 'complete' ?
 *   domReady() : document.addEventListener('DOMContentLoaded', domReady);
 * ```
 *
 * @packageDocumentation
 */
class GcWidget {
    /**
     * Returns the first element that matches the selectors in the document.
     *
     * @param selectors the CSS selector string
     * @returns the first element matching the selector, or null if none found.
     */
    static async querySelector(selectors) {
        const element = document.querySelector(selectors);
        if (element) {
            await customElements.whenDefined(element.tagName.toLowerCase());
            return element;
        }
        else {
            return null;
        }
    }
    /**
     * Returns all element that match the selectors in the document.
     *
     * @param selectors the CSS selector string
     * @returns array of elements matching the selector.  If nothing found, the result is an empty array.
     */
    static async querySelectorAll(selectors) {
        const elements = document.querySelectorAll(selectors);
        const definedPromises = [];
        elements.forEach(element => definedPromises.push(customElements.whenDefined(element.tagName.toLowerCase())));
        await Promise.all(definedPromises);
        return elements;
    }
}
/**
 * Instance of this class are runtime types for a parent child relationship based on specific interfaces between parent and children.  The first
 * template parameter is the parent interface type, and the second is the child interface type.
 */
class ParentWidgetType {
    constructor(widgetName) {
        this.widgetName = widgetName;
    }
    /**
     * Helper method to cast anything to the parent interface type.
     */
    asParent(parent) {
        return parent;
    }
    /**
     * Helper method to cast anything to the child interface type.
     */
    asChild(child) {
        return child;
    }
}
/**
 * Concrete helper class for parent widgets to keep track of their registered child widgets in a parent child relationship.
 */
class ChildRegistry {
    /**
     * Constructor
     *
     * @param type type of the parent child relationship
     * @param indexed true if the children managed by this class should be sorted by the child's sortingOrder of not.  Sometimes
     * child widgets are registered with more than one parent, in which case, only one parent should be responsible for sorting the children.
     */
    constructor(type, indexed = true) {
        this.type = type;
        this.indexed = indexed;
        /**
         * Array of register child widgets;
         */
        this.children = [];
    }
    /**
     * Method to add children
     *
     * @param type type of the parent child relationship for the purpose of runtime type checking the type of the child widget.
     * @param child widget to add to the children array
     */
    register(type, child) {
        if (type.widgetName !== this.type.widgetName) {
            if (!GcUtils.isInDesigner) {
                GcConsole.error('gc-widget-base', `Parent of type=${this.type.widgetName}, cannot register a child of type ${type.widgetName}.`);
            }
            return;
        }
        if (!this.children.includes(child)) {
            this.children.push(child);
            this.children.sort((a, b) => a.sortingOrder - b.sortingOrder);
            if (this.indexed) {
                this.children.forEach((child, i) => child.childIndex = i);
            }
        }
    }
    /**
     * Method to remove children
     *
     * @param type type of the parent child relationship for the purpose of runtime type checking the type of the child widget.
     * @param child widget to remove from the children array.  If the child was not added in the first place, this method does nothing.
     */
    unregister(type, childToRemove) {
        if (type.widgetName !== this.type.widgetName) {
            throw new Error('Parent of type=${this.type.widgetName}, cannot unregister a child of type ${type.widgetName}.');
        }
        this.children = this.children.filter(child => child !== childToRemove);
        if (this.indexed) {
            this.children.forEach((child, i) => child.childIndex = i);
        }
    }
}
/**
 * Concrete helper class for child widgets to keep track of their parent widget in a parent child relationship.
 */
class ParentRegistry {
    /**
     * Constructor
     *
     * @param type type of the parent child relationship for the purpose of runtime type checking the type of the parent widget.
     */
    constructor(type) {
        this.type = type;
    }
    /**
     * Method to register the child widget with the parent, and update the parent when registration is complete.  The child
     * widget does not have to be a direct descendant of the parent in the HTML dom.    It is recommended that the child widget
     * call this during the onConnected() event within the Stencil component lifecycle.
     *
     * @param parentElement the parent widget to register with.
     * @Param child the child widget to register with the parent.
     */
    async register(parentElement, child) {
        const parent = parentElement;
        if (!parent?.registerChildWidget) {
            GcConsole.warning('gc-widget-base', () => `Cannot register child=${child.id} with parent=${parentElement.id}`);
            return;
        }
        this.parentElement = parent;
        this.parent = await parent.registerChildWidget(this.type, child);
    }
    /**
     * Method to unregister the child widget from the parent, and clear the parent property of this class.  It is recommended that the child widget
     * call this during the onDisconnected() event within the Stencil component lifecycle.
     *
     * @Param child the child widget to unregister from the parent.
     */
    async unregister(child) {
        const oldParentElement = this.parentElement;
        this.parentElement = undefined;
        this.parent = undefined;
        if (oldParentElement) {
            await oldParentElement.unregisterChildWidget(this.type, child);
        }
    }
    /**
     * Method to to compute the child index of a widget within it's direct parent.  If all children are expected to be within the same container within
     * the HTML dom, then this method can be used as the sortedOrder for a child in a parent child relationship.  However, do not call this once to pick
     * a sorting order, rather implement the sortedOrder property with a getter that calls this method.  This way the sorting order used to sort changes
     * as sibling child widgets are added and removed.  For example, get sortedOrder() { return ParentRegistry.getChildElementIndex(this.el) };
     * call this during the onDisconnected() event within the Stencil component lifecycle.
     *
     * @Param child the child widget to calculate this index for.
     */
    static getChildElementIndex(child) {
        let result = 0;
        let element = child;
        while ((element = element.previousElementSibling)) {
            result++;
        }
        return result;
    }
}

export { ChildRegistry, GcWidget, ParentRegistry, ParentWidgetType };
//# sourceMappingURL=GcWidget.js.map
