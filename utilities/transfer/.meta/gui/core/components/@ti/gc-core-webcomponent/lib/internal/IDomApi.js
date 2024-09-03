/**
 *  Copyright (c) 2018, 2021 Texas Instruments Incorporated
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
var gc = gc || {};
gc.designer = gc.designer || {};
gc.designer.editor = gc.designer.editor || {};
(function () {
    var noop = function () { };
    var IDomCommonApi = function () {
    };
    IDomCommonApi.prototype.getSize = noop;
    IDomCommonApi.prototype.setSize = noop;
    IDomCommonApi.prototype.getProperty = noop;
    IDomCommonApi.prototype.setProperty = noop;
    IDomCommonApi.prototype.getStyle = noop;
    IDomCommonApi.prototype.setStyle = noop;
    IDomCommonApi.prototype.getClass = noop;
    IDomCommonApi.prototype.setClass = noop;
    IDomCommonApi.prototype.getPosition = noop;
    IDomCommonApi.prototype.setPosition = noop;
    IDomCommonApi.prototype.getId = noop;
    IDomCommonApi.prototype.setId = noop;
    IDomCommonApi.prototype.getLayout = noop;
    IDomCommonApi.prototype.setLayout = noop;
    IDomCommonApi.prototype.getBinding = noop;
    IDomCommonApi.prototype.setBinding = noop;
    IDomCommonApi.prototype.getElementsByTagName = noop;
    IDomCommonApi.prototype.onWindowResize = noop;
    var IDomElementApi = function () {
    };
    IDomElementApi.prototype = new IDomCommonApi();
    IDomElementApi.prototype.getLabel = noop;
    IDomElementApi.prototype.firstElementChild = null;
    IDomElementApi.prototype.nextElementSibling = null;
    IDomElementApi.prototype.children = [];
    IDomElementApi.prototype.id = "";
    IDomElementApi.prototype.localName = "";
    IDomElementApi.prototype.textContent = "";
    IDomElementApi.prototype.getCoordinates = noop;
    IDomElementApi.prototype.getClientWidth = noop;
    IDomElementApi.prototype.getClientHeight = noop;
    IDomElementApi.prototype.setSelected = noop;
    IDomElementApi.prototype.getContainer = noop;
    IDomElementApi.prototype.addRemoveClass = noop;
    IDomElementApi.prototype.addEventListener = noop;
    IDomElementApi.prototype.removeEventListener = noop;
    IDomElementApi.prototype.insertBefore = noop;
    IDomElementApi.prototype.removeChild = noop;
    IDomElementApi.prototype.getOuterHTML = noop;
    IDomElementApi.prototype.attached = noop;
    IDomElementApi.prototype.detached = noop;
    IDomElementApi.prototype.getFunction = noop;
    IDomElementApi.prototype.getAdditionalProperties = noop;
    IDomElementApi.prototype.getTextRange = noop;
    IDomElementApi.prototype.isPropertyReadOnly = noop;
    IDomElementApi.prototype.onResizedByDesigner = noop;
    IDomElementApi.prototype.designerGetSelectedOnPointerDown = noop;
    IDomElementApi.prototype.getPropertyAutoFillOptions = noop;
    IDomElementApi.prototype.isVisible = noop;
    IDomElementApi.prototype.isContainer = noop;
    var IDomApi = function () {
    };
    IDomApi.prototype = new IDomCommonApi();
    IDomApi.prototype.getSelection = noop;
    IDomApi.prototype.setSelection = noop;
    IDomApi.prototype.getSelectedName = noop;
    IDomApi.prototype.getSelectedParent = noop;
    IDomApi.prototype.getRoot = noop;
    IDomApi.prototype.html = undefined;
    IDomApi.prototype.updateStyles = noop;
    IDomApi.prototype.isDirty = noop;
    IDomApi.prototype.getElementById = noop;
    var AbstractDomElement = function () {
    };
    AbstractDomElement.prototype = new IDomElementApi();
    AbstractDomElement.prototype.getSize = function () {
        return {
            width: this.getStyle('width'),
            height: this.getStyle('height')
        };
    };
    AbstractDomElement.prototype.setSize = function (newSize) {
        this.setStyle('width', newSize.width);
        this.setStyle('height', newSize.height);
    };
    AbstractDomElement.prototype.getId = function () {
        return this.getProperty('id');
    };
    AbstractDomElement.prototype.setId = function (newId) {
        this.setProperty('id', newId);
    };
    AbstractDomElement.prototype.getPosition = function () {
        return {
            position: this.getStyle('position'),
            x: this.getStyle('left'),
            y: this.getStyle('top')
        };
    };
    AbstractDomElement.prototype.setPosition = function (newPosition) {
        this.setStyle('position', newPosition.position);
        this.setStyle('left', newPosition.x);
        this.setStyle('top', newPosition.y);
    };
    AbstractDomElement.prototype.getAttribute = function (attrName) {
        return this.getProperty(attrName);
    };
    AbstractDomElement.prototype.setAttribute = function (attrName, attrValue) {
        return this.setProperty(attrName, attrValue);
    };
    AbstractDomElement.prototype.getClass = function () {
        return this.getProperty('class');
    };
    AbstractDomElement.prototype.setClass = function (className) {
        return this.setProperty('class', className);
    };
    AbstractDomElement.prototype.addRemoveClass = function (name, isAdd) {
        var classNames = this.getClass() || '';
        isAdd = isAdd || false;
        classNames = classNames.split(' ');
        var index = classNames.indexOf(name);
        if (isAdd === (index < 0)) {
            if (isAdd) {
                classNames.push(name);
            }
            else {
                classNames = classNames.splice(index, 1);
            }
            classNames = classNames.join(' ');
            this.setClass(classNames);
        }
    };
    AbstractDomElement.prototype.getBinding = function (property) {
        var result = this.getAttribute(property);
        if (result) {
            var start = result.substring(0, 2);
            var end = result.substring(result.length - 2);
            if ((start === '{{' && end === '}}') || (start === '[[' && end === ']]')) {
                result = result.substring(2, result.length - 2);
            }
            else {
                result = undefined;
            }
        }
        return result;
    };
    AbstractDomElement.prototype.setBinding = function (property, bindExpression) {
        this.setAttribute(property, '{{' + bindExpression + '}}');
    };
    var nullCoordinates = { left: 0, top: 0, right: 0, bottom: 0, scrollLeft: 0, scrollTop: 0, layout: false };
    AbstractDomElement.prototype.getContentCoordinates =
        AbstractDomElement.prototype.getCoordinates = function () {
            return nullCoordinates;
        };
    AbstractDomElement.prototype.getClientWidth =
        AbstractDomElement.prototype.getClientHeight = function () {
            return 0;
        };
    var getElementsByTagName = function (parent, name, cumulativeResults) {
        var results = cumulativeResults || [];
        var isRegEx = name instanceof RegExp;
        for (var i = 0; i < parent.children.length; i++) {
            var child = parent.children[i];
            if (isRegEx ? name.test(child.localName) : child.localName === name) {
                results.push(child);
            }
            if (child.children.length > 0) {
                getElementsByTagName(child, name, results);
            }
        }
        return results;
    };
    AbstractDomElement.prototype.getElementsByTagName = function (name) {
        return getElementsByTagName(this, name);
    };
    AbstractDomElement.prototype.getAdditionalProperties = function (prefix) {
        return [];
    };
    var AbstractDom = function () {
    };
    AbstractDom.prototype = new IDomApi();
    AbstractDom.prototype.root = new AbstractDomElement();
    AbstractDom.prototype.getRoot = function () {
        return this.root;
    };
    AbstractDom.prototype.setSelection = function (selection) {
        this._activeSelection = selection;
        return this;
    };
    AbstractDom.prototype.getSelection = function () {
        return this._activeSelection || [];
    };
    var getter = function (type) {
        var fn = 'get' + type;
        return function (arg, arg2) {
            var result;
            if (this._activeSelection && this._activeSelection.length > 0) {
                result = this._activeSelection[0][fn](arg, arg2);
                for (var i = this._activeSelection.length; i-- > 1;) {
                    var property = this._activeSelection[i][fn](arg, arg2);
                    if (result !== property) {
                        return '';
                    }
                }
            }
            return result;
        };
    };
    AbstractDom.prototype.getSize = getter('Size');
    AbstractDom.prototype.getProperty = getter('Property');
    AbstractDom.prototype.getStyle = getter('Style');
    AbstractDom.prototype.getClass = getter('Class');
    AbstractDom.prototype.getPosition = getter('Position');
    AbstractDom.prototype.getId = getter('Id');
    AbstractDom.prototype.getLayout = getter('Layout');
    AbstractDom.prototype.getBinding = getter('Binding');
    AbstractDom.prototype.getSelectedName = getter('Label');
    AbstractDom.prototype.getSelectedParent = getter('Container');
    var setter = function (type) {
        var fn = 'set' + type;
        return function (arg, arg2) {
            if (this._activeSelection) {
                for (var i = this._activeSelection.length; i-- > 0;) {
                    this._activeSelection[i][fn](arg, arg2);
                }
            }
        };
    };
    AbstractDom.prototype.setSize = setter('Size');
    AbstractDom.prototype.setProperty = setter('Property');
    AbstractDom.prototype.setStyle = setter('Style');
    AbstractDom.prototype.setClass = setter('Class');
    AbstractDom.prototype.setPosition = setter('Position');
    AbstractDom.prototype.setId = setter('Id');
    AbstractDom.prototype.setLayout = setter('Layout');
    AbstractDom.prototype.setBinding = setter('Binding');
    var toCamelCaseRegEx = /-([a-z])/g;
    var toUpperCase = function (m) {
        return m[1].toUpperCase();
    };
    var convertEventToProperty = function (eventName) {
        var pos = eventName.lastIndexOf('-changed');
        if (pos) {
            eventName = eventName.substring(0, pos);
        }
        return eventName.replace(toCamelCaseRegEx, toUpperCase);
    };
    AbstractDom.prototype.getProxySelection = function () {
        var sel = this.getSelection();
        if (sel && sel.length > 1) {
            sel = this;
        }
        else if (sel) {
            sel = sel[0];
        }
        if (sel) {
            return new window.Proxy(sel, {
                get: function (target, name) {
                    if (name === 'id') {
                        return target.getId();
                    }
                    return target.getProperty(name);
                },
                set: function (target, name, value) {
                    if (name === 'id') {
                        target.setId(value);
                    }
                    else {
                        target.setProperty(name, value);
                    }
                }
            });
        }
    };
    AbstractDom.prototype.getElementsByTagName = function (name) {
        var results = [];
        getElementsByTagName(this.getRoot(), name, results);
        return results;
    };
    gc.designer.editor.IDomApi = IDomApi;
    gc.designer.editor.AbstractDom = AbstractDom;
    gc.designer.editor.IDomElementApi = IDomElementApi;
    gc.designer.editor.AbstractDomElement = AbstractDomElement;
    window.gc = window.gc || {};
    window.gc.AbstractDomElement = AbstractDomElement;
    window.gc.AbstractDom = AbstractDom;
}());
//# sourceMappingURL=IDomApi.js.map