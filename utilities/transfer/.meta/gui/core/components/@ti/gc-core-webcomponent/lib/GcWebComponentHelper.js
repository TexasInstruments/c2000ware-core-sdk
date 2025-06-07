import { GcUtils } from '../../gc-core-assets/lib/GcUtils';
import { GcConsole } from '../../gc-core-assets/lib/GcConsole';
import { AbstractBindValue, WidgetModel, DataBinder } from '../../gc-core-databind/lib/CoreDatabind';

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

var gc$1 = gc$1 || {};
gc$1.designer = gc$1.designer || {};
gc$1.designer.editor = gc$1.designer.editor || {};

(function()
{
    var noop = function() {};

    var IDomCommonApi = function()
    {
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

    var IDomElementApi = function()
    {
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

    var IDomApi = function()
    {
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

    var AbstractDomElement = function()
    {
    };

    AbstractDomElement.prototype = new IDomElementApi();

    AbstractDomElement.prototype.getSize = function()
    {
        return {
            width: this.getStyle('width'),
            height: this.getStyle('height')
        };
    };

    AbstractDomElement.prototype.setSize = function(newSize)
    {
        this.setStyle('width', newSize.width);
        this.setStyle('height', newSize.height);
    };

    AbstractDomElement.prototype.getId = function()
    {
        return this.getProperty('id');
    };

    AbstractDomElement.prototype.setId = function(newId)
    {
        this.setProperty('id', newId);
    };

    AbstractDomElement.prototype.getPosition = function()
    {
        return  {
            position: this.getStyle('position'),
            x: this.getStyle('left'),
            y: this.getStyle('top')
        };
    };

    AbstractDomElement.prototype.setPosition = function(newPosition)
    {
        this.setStyle('position', newPosition.position);
        this.setStyle('left', newPosition.x);
        this.setStyle('top', newPosition.y);
    };

    AbstractDomElement.prototype.getAttribute = function(attrName)
    {
        return this.getProperty(attrName);
    };

    AbstractDomElement.prototype.setAttribute = function(attrName, attrValue)
    {
        return this.setProperty(attrName, attrValue);
    };

    AbstractDomElement.prototype.getClass = function()
    {
        return this.getProperty('class');
    };

    AbstractDomElement.prototype.setClass = function(className)
    {
        return this.setProperty('class', className);
    };

    AbstractDomElement.prototype.addRemoveClass = function(name, isAdd)
    {
        var classNames = this.getClass() || '';
        isAdd = isAdd || false;
        classNames = classNames.split(' ');
        var index = classNames.indexOf(name);
        if (isAdd === (index < 0))
        {
            if (isAdd)
            {
                classNames.push(name);
            }
            else
            {
                classNames = classNames.splice(index, 1);
            }
            classNames = classNames.join(' ');
            this.setClass(classNames);
        }
    };

    AbstractDomElement.prototype.getBinding = function(property)
    {
        var result = this.getAttribute(property);
        if (result)
        {
            var start = result.substring(0, 2);
            var end = result.substring(result.length-2);
            if ((start === '{{' && end === '}}') || (start === '[[' && end === ']]'))
            {
                result = result.substring(2, result.length-2);
            }
            else
            {
                result = undefined;
            }
        }
        return result;
    };

    AbstractDomElement.prototype.setBinding = function(property, bindExpression)
    {
        this.setAttribute(property, '{{' + bindExpression + '}}');
    };

    var nullCoordinates = { left: 0, top: 0, right: 0, bottom: 0, scrollLeft: 0, scrollTop: 0, layout: false };

    AbstractDomElement.prototype.getContentCoordinates =
        AbstractDomElement.prototype.getCoordinates = function()
    {
        return nullCoordinates;
    };

    AbstractDomElement.prototype.getClientWidth =
        AbstractDomElement.prototype.getClientHeight = function()
    {
        return 0;
    };

    var getElementsByTagName = function(parent, name, cumulativeResults)
    {
        var results = cumulativeResults || [];
        var isRegEx = name instanceof RegExp;

        for(var i = 0; i < parent.children.length; i++)
        {
            var child = parent.children[i];
            if (isRegEx ? name.test(child.localName) : child.localName === name)
            {
                results.push(child);
            }
            if (child.children.length > 0)
            {
                getElementsByTagName(child, name, results);
            }
        }
        return results;
    };

    AbstractDomElement.prototype.getElementsByTagName = function(name)
    {
        return getElementsByTagName(this, name);
    };

    AbstractDomElement.prototype.getAdditionalProperties = function(prefix)
    {
        return [];
    };

    var AbstractDom = function()
    {
    };

    AbstractDom.prototype = new IDomApi();

    AbstractDom.prototype.root = new AbstractDomElement();

    AbstractDom.prototype.getRoot = function()
    {
        return this.root;
    };

    AbstractDom.prototype.setSelection = function(selection)
    {
        this._activeSelection = selection;
        return this;
    };

    AbstractDom.prototype.getSelection = function()
    {
        return this._activeSelection || [];
    };

    var getter = function(type)
    {
        var fn = 'get' + type;

        return function(arg, arg2)
        {
            var result;
            if (this._activeSelection && this._activeSelection.length > 0)
            {
                result = this._activeSelection[0][fn](arg, arg2);
                for(var i = this._activeSelection.length; i-- > 1; )
                {
                    var property = this._activeSelection[i][fn](arg, arg2);
                    if (result !== property)
                    {
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

    var setter = function(type)
    {
        var fn = 'set' + type;

        return function(arg, arg2)
        {
            if (this._activeSelection)
            {
                for(var i = this._activeSelection.length; i-- > 0; )
                {
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
    var toUpperCase = function(m)
    {
        return m[1].toUpperCase();
    };

    var convertEventToProperty = function(eventName)
    {
        var pos = eventName.lastIndexOf('-changed');
        if (pos)
        {
            eventName = eventName.substring(0, pos);
        }
        return eventName.replace(toCamelCaseRegEx, toUpperCase);
    };

    AbstractDom.prototype.getProxySelection = function()
    {
        var sel = this.getSelection();
        if (sel && sel.length > 1 )
        {
            sel = this;
        }
        else if (sel)
        {
            sel = sel[0];
        }

        if (sel)
        {
            return new window.Proxy(sel,
            {
                get: function(target, name)
                {
                    if (name === 'id')
                    {
                        return target.getId();
                    }
                    return target.getProperty(name);
                },
                set: function(target, name, value)
                {
                    if (name === 'id')
                    {
                        target.setId(value);
                    }
                    else
                    {
                        target.setProperty(name, value);
                    }
                }
            });
        }
    };

    AbstractDom.prototype.getElementsByTagName = function(name)
    {
        var results = [];
        getElementsByTagName(this.getRoot(), name, results);
        return results;
    };

    gc$1.designer.editor.IDomApi = IDomApi;
    gc$1.designer.editor.AbstractDom = AbstractDom;
    gc$1.designer.editor.IDomElementApi = IDomElementApi;
    gc$1.designer.editor.AbstractDomElement = AbstractDomElement;

    window.gc = window.gc || {};
    window.gc.AbstractDomElement = AbstractDomElement;
    window.gc.AbstractDom = AbstractDom;

}());

/**
 *  Copyright (c) 2018, 2025 Texas Instruments Incorporated
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
gc.designer.editor.AbstractDomElement = gc.designer.editor.AbstractDomElement || window.gc.AbstractDomElement;
gc.designer.editor.AbstractDom = gc.designer.editor.AbstractDom || window.gc.AbstractDom;

(function()
{
    var BLOCK_INDENT = '    ';

    var matchWhiteSpaceRegExpr = /\s+/g;

    // #region TextBlock
    var TextBlock = function(leadingWhiteSpace, content)
    {
        if (leadingWhiteSpace !== undefined)
        {
            if (content !== undefined)
            {
                this.content = content;
                this.setIndent(leadingWhiteSpace);
            }
            else
            {
                this.setText(leadingWhiteSpace);
            }
        }
    };

    TextBlock.prototype.leadingWhiteSpace = '';
    TextBlock.prototype.extraBlockIndent = '';
    TextBlock.prototype.content = '';
    TextBlock.prototype.touched = false;

    TextBlock.prototype.setText = function(content)
    {
        var text = content.trim();
        if (text !== '')
        {
            var whiteSpace = content.split(text);
            this.content = text + whiteSpace[1];
            this.setIndent(whiteSpace[0]);
        }
        else
        {
            this.content = '';
            this.setIndent(content);
        }
    };

    TextBlock.prototype.getText = function()
    {
        return this.content;
    };

    TextBlock.prototype.getName = function()
    {
        return this.name;
    };

    TextBlock.prototype.setName = function(name)
    {
        this.name = name;
    };

    TextBlock.prototype.getDocumentPos = function()
    {
        return this.documentOffset;
    };

    TextBlock.prototype.toString = function()
    {
        var text = this.getText();
        if (this.touched && text.trim() === '')
        {
            return '';
        }
        return this.leadingWhiteSpace + text;
    };

    TextBlock.prototype.size = function()
    {
        return this.leadingWhiteSpace.length + this.getText().length;
    };

    TextBlock.prototype.getIndent = function()
    {
        var pos = this.leadingWhiteSpace.lastIndexOf('\n');
        if (pos >= 0)
        {
            if (pos < this.leadingWhiteSpace.length - 1)
            {
                return this.leadingWhiteSpace.substring(pos + 1);
            }
            return "";
        }
        return this.leadingWhiteSpace;
    };

    TextBlock.prototype.setIndent = function(indent)
    {
        this.leadingWhiteSpace = indent;
    };

    TextBlock.prototype.getClosingTag = function()
    {
        return this._closingTag || this;
    };

    TextBlock.prototype.isInline = function()
    {
        return this.leadingWhiteSpace.indexOf('\n') < 0;
    };

    TextBlock.prototype.isTagNotClosed = function()
    {
        return this._closingTag === undefined;
    };

    TextBlock.prototype.insertComment =
        TextBlock.prototype.insertText = function(pos, text)
    {
        if (pos < this.leadingWhiteSpace.length)
        {
            this.content = text + this.leadingWhiteSpace.substring(pos) + this.content;
            this.leadingWhiteSpace = this.leadingWhiteSpace.substring(0, pos);
        }
        else
        {
            pos -= this.leadingWhiteSpace.length;
            if (pos === 0)
            {
                this.content = text + this.content;
            }
            else if (pos === this.content.length)
            {
                this.content += text;
            }
            else
            {
                this.content = this.content.substring(0, pos) + text + this.content.substring(pos);
            }
        }
    };

    TextBlock.prototype.replaceText = function(oldText, newText)
    {
        this.content = this.content.split(oldText).join(newText);
    };

    var startOfLineSpacesRegExpr = /\n[\t ]*/g;
    var applyIndentationToContent = function(text, indent)
    {
        return text.replace(startOfLineSpacesRegExpr, '\n' + indent);
    };

    TextBlock.prototype.applyIndentation = function(indent)
    {
        var pos = this.leadingWhiteSpace.lastIndexOf('\n');
        if (pos >= 0) // only add indent if this block starts on a new line.
        {
            // preserve blank lines, only replace the last '\n' with '\n' + indent.
            if (pos < this.leadingWhiteSpace.length - 1)
            {
                this.leadingWhiteSpace = this.leadingWhiteSpace.substring(0, pos+1) + indent;
            }
            else
            {
                this.leadingWhiteSpace += indent;
            }
        }

        // replace all line terminators with new indentation
        if (this.content)
        {
            if (this.content instanceof Array)
            {
                for(var j = this.content.length; j-- > 0; )
                {
                    this.content[j] = applyIndentationToContent(this.content[j], this.extraBlockIndent + indent);
                }
            }
            else
            {
                this.content = applyIndentationToContent(this.content, this.extraBlockIndent + indent);
            }
        }
    };

    TextBlock.prototype.getAnnotation = function()
    {
    };

    TextBlock.prototype.getErrorLineOffset = function()
    {
        return 0;
    };

    var parseTextBlock = function(content)
    {
        var text = content.trim();
        var tag;
        if (text !== '')
        {
            var whiteSpace = content.split(text);
            tag = new TextBlock(text + whiteSpace[1]);
            tag.setIndent(whiteSpace[0]);
        }
        else
        {
            tag = new TextBlock('');
            tag.setIndent(content);
        }
        return tag;
    };
    // #endregion

    // #region ErrorBlock
    var ErrorBlock = function(errorText, skippedText, message)
    {
        this.errorMessage = message;
        this.setText(errorText + skippedText);
    };

    ErrorBlock.prototype = new TextBlock();

    ErrorBlock.prototype.getAnnotation = function()
    {
        return {
            type: 'error',
            text: this.errorMessage
        };
    };
    // #endregion

    // #region CDCBlock
    var CDATAopenBrace = '[CDATA[';
    var CDATAclosingBrace = ']]>';

    var CDATABlock = function(content)
    {
        if (content)
        {
            this.content = '<!' + CDATAopenBrace + content + CDATAclosingBrace;
        }
    };

    CDATABlock.prototype = new TextBlock();
    CDATABlock.prototype.name = "CDATA";

    CDATABlock.prototype.applyIndentation = function(indent)
    {
    };

    CDATABlock.prototype.getAttribute = function(name) {
        let attr = this.attributes[name];
        return attr && attr.getValue();
    };
    CDATABlock.prototype.getAttributeText = function() {};
    Object.defineProperty(CDATABlock.prototype, 'attributes', {
        get: function() {
            if (!this._attributes) {
                this._attributes = {};

                let text = this.getAttributeText();
                if (text) {
                    let attributeList = text.match(attributesRegExpr) || [];
                    for (let i = 0; i < attributeList.length; ++i) {
                        let attribute = new AttributeBlock(attributeList[i]);
                        this._attributes[attribute.getName()] = attribute;
                    }
                }
            }
            return this._attributes;
        }
    });

    var parseCDATABlock = function(content)
    {
        var pos = content.indexOf(CDATAclosingBrace);
        if (pos >= 0)
        {
            return new CDATABlock(content.substring(0, pos));
        }
        else
        {
            return new ErrorBlock('<!' + CDATAopenBrace, content, 'missing the closing brace "' + CDATAclosingBrace + '"');
        }
    };

    var findPosNotInQuotes = function(content, symbol, start)
    {
        var quote;
        var len = content.length;
        for(var i = start || 0; i < len; i++ )
        {
            var ch = content[i];
            if (quote)
            {
                // skip everything except matching quote symbol
                if (ch === quote)
                {
                    quote = undefined;
                }
            }
            else
            {
                // test for start of quotes
                if (ch === '\'' || ch === '"')
                {
                    quote = ch;
                }
                // test for match
                else if (ch === symbol)
                {
                    return i;
                }
            }
        }
        return -1; // failed to find the symbol.
    };
    // #endregion

    // #region SMGLBlock
    var SGMLBlock = function(content)
    {
        this.content = '<!' + content + '>';
    };

    SGMLBlock.prototype = new CDATABlock();
    SGMLBlock.prototype.name = "SGML";

    var commentDelimiter = '--';

    var parseSGMLBlock = function(content)
    {
        if (content.indexOf(CDATAopenBrace) === 0)
        {
            return parseCDATABlock(content.substring(CDATAopenBrace.length));
        }

        var pos = 0;
        var commentPos;
        var done = false;
        while(!done)
        {
            commentPos = content.indexOf(commentDelimiter, pos);
            pos = content.indexOf('>', pos);

            if (pos >= 0)
            {
                if (commentPos < 0 || commentPos > pos)
                {
                    return new SGMLBlock(content.substring(0, pos));
                }

                // start of comment detected.  Find end of comment
                pos = content.indexOf(commentDelimiter, commentPos+commentDelimiter.length);
                if (pos >= 0)
                {
                    pos += commentDelimiter.length;
                    continue;
                }
            }
            done = true;
        }

        // missing closing brace - it could be hidden in a comment block
        pos = content.lastIndexOf('>');
        if (pos > 0)
        {
            content = content.substring(0, pos+1);
            return new ErrorBlock('<!', content, 'missing closing brace ">" because they were all inside comment block(s) delimited by "--"');
        }
        return new ErrorBlock('<!', content, 'missing the closing brace ">"');
    };

    // camel to dash and dash to camel converters
    var fromCamelCaseRegEx = /([A-Z])/g;
    var toCamelCaseRegEx = /-([a-z])/g;
    var toUpperCase = function(m)
    {
        return m[1].toUpperCase();
    };
    var convertPropertyToAttribute = function(propertyName)
    {
        return propertyName.replace(fromCamelCaseRegEx, '-$1').toLowerCase();
    };

    var convertAttributeToProperty = function(attributeName)
    {
        return attributeName.replace(toCamelCaseRegEx, toUpperCase);
    };

    var inlineBindingRegExpr = /^(\{\{.+\}\}|\[\[.+\]\])$/;

    var AttributeBlock = function(content)
    {
        this.content = content;
        var pos = content.indexOf('=');

        if (pos > 0)
        {
            this.name = content.substring(0, pos);
            this.value = content.substring(pos+1).trim();
            this.quote = this.value[0];
            this.value = this.value.substring(1,this.value.length-1); // strip quotes

            // unescape quote characters.
            if (this.quote === '"')
            {
                if (this.value.indexOf('&quot;') >= 0)
                {
                    this.value = this.value.split('&quot;').join(this.quote);
                }
            }
            else if (this.quote === "'")
            {
                if (this.value.indexOf('&apos;') >= 0)
                {
                    this.value = this.value.split('&apos;').join(this.quote);
                }
            }

            if (this.value.match(inlineBindingRegExpr))
            {
                this._bindExpression = this.value.substring(2, this.value.length - 2);
                this._isBindExpressionOneWay = this.value.charAt(0) === '[';
                this.value = undefined;
            }
        }
        else
        {
            this.name = content;
            this.value = true;
            this.quote = '"';
        }
        this.name = this.name.trim();
    };
    // #endregion

    // #region AttributeBlock
    AttributeBlock.prototype = new TextBlock();

    AttributeBlock.prototype.getValue = function()
    {
        return this.value;
    };

    var escapeAttributeValue = function(value, quote)
    {
        if (typeof value === 'string' && value.indexOf(quote) >= 0)
        {
            value = value.split(quote).join(quote === '"' ? '&quot;' :'&apos;');
        }
        return quote + value + quote;
    };

    AttributeBlock.prototype.rename = function(name)
    {
        this.name = name;
        this.updateContent(this.getValue(), this.getValue());
    };

    AttributeBlock.prototype.updateContent = function(newValue, oldValue)
    {
        if (newValue === true || newValue === undefined)
        {
            this.content = ' ' + this.name;
        }
        else if (oldValue === true || oldValue === undefined)
        {
            this.content = ' ' + this.name + '=' + escapeAttributeValue(newValue, this.quote);
        }
        else
        {
            this.content = ' ' + this.name + '=' + this.content.substring(this.content.indexOf('=')+1);
            this.content = this.content.replace(escapeAttributeValue(oldValue, this.quote), escapeAttributeValue(newValue,this.quote));
        }
    };

    AttributeBlock.prototype.setValue = function(newValue)
    {
        if (!this._bindExpression)
        {
            this.updateContent(newValue, this.value);
        }
        this.value = newValue;
    };

    AttributeBlock.prototype.setBinding = function(newValue)
    {
        var oldValue = this._bindExpression ? '{{' + this._bindExpression + '}}' : this.value;
        this.updateContent('{{' + newValue + '}}', oldValue);
        this._bindExpression = newValue;
        this._isBindExpressionOneWay = false;
    };

    AttributeBlock.prototype.getBinding = function()
    {
        return this._bindExpression;
    };

    AttributeBlock.prototype.removeBinding = function()
    {
        this.updateContent(this.value, '{{' + this._bindExpression + '}}');
        this._bindExpression = undefined;
        this._isBindExpressionOneWay = undefined;
    };

    var createAttributeBlock = function(name, value)
    {
        name = convertPropertyToAttribute(name);

        if (value === undefined || value === true)
        {
            return new AttributeBlock(' ' + name);
        }
        // pick the best quote to use based on value
        var quote = '"';
        if (typeof value === 'string' && value.split(quote).length > 2)
        {
            quote = "'";
        }
        return new AttributeBlock(' ' + name + '=' + escapeAttributeValue(value, quote));
    };
    // #endregion

    // #region ApplyStyleBlock
    var ApplyStyleBlock = function(content)
    {
        TextBlock.call(this, content);

        this.name = content.trim();
    };

    ApplyStyleBlock.prototype = new TextBlock();

    ApplyStyleBlock.prototype.value = true;

    ApplyStyleBlock.prototype.getText = function()
    {
        return this.value ? TextBlock.prototype.getText.call(this) : '';
    };

    ApplyStyleBlock.prototype.getValue = function()
    {
        return this.value;
    };

    ApplyStyleBlock.prototype.setValue = function(newValue)
    {
        this.value = !!newValue;
    };

    var StyleBlock = function(content)
    {
        var pos = content.indexOf(':');
        this.styleName = new TextBlock(content.substring(0, pos));
        this.name = this.styleName.getText().trim();
        this.styleValue = new TextBlock(content.substring(pos+1));
        this.value = this.styleValue.getText().trim() || undefined;  // convert "" to undefined.
    };

    StyleBlock.prototype = new TextBlock();

    StyleBlock.prototype.getText = function()
    {
        var text = this.styleValue.toString();
        if (this.touched && text.trim() === '')
        {
            return '';
        }
        return this.styleName + ':' + text;
    };

    StyleBlock.prototype.getValue = function()
    {
        return this.value;
    };

    StyleBlock.prototype.setValue = function(newValue)
    {
        newValue = newValue || '';
        this.value = newValue.trim();
        this.styleValue = new TextBlock(this.styleValue.leadingWhiteSpace, this.value);
        this.touched = true;
    };

    StyleBlock.prototype.applyIndentation = function(indent)
    {
        this.styleName.applyIndentation(indent);
        this.styleValue.applyIndentation(indent);
    };

    StyleBlock.prototype.insertComment = function(pos, comment)
    {
        var length = this.styleName.size();
        if (pos <= length)
        {
            this.styleName.insertText(pos, comment);
        }
        else
        {
            this.styleValue.insertText(pos - length - 1, comment);
        }
    };
    // #endregion

    // #region StyleRule
    var stylesRegExpr = /\s*[^\s:]+\s*:?\s*(\{[^\}]*\}\s*|[^;]+);/g;
    var stylesTerminatorRegExpr = /\s*}$/m;

    var StyleRule = function(content)
    {
        var pos = content.indexOf('{');
        this.name = content.substring(0, pos);
        this.qualifiers = new TextBlock(this.name);
        this.name = this.name.trim();

        var terminator = content.match(stylesTerminatorRegExpr)[0];
        // strip opening '{' and closing '}' braces plus any trailing whitespace.
        content = content.substring(pos + 1, content.length-terminator.length);

        // check for missing ';' on last style in the rule
        var hasStyles = content.trim().length !== 0;
        var missingSemicolon = hasStyles && content.charAt(content.length-1) !== ';';  // if no semicolon found use the entire content;
        if (missingSemicolon)
        {
            content = content + ';';  // add one to make parsing easier.
        }
        else if (hasStyles)
        {
            // preserve the last semicolon in the terminator if it was not missing.
            terminator = ';' + terminator;
        }

        var styles = hasStyles && content.match(stylesRegExpr) || [];
        this.styles = [];
        this.stylesByName = {};
        pos = 0;
        for(var i = 0; i < styles.length; i++)
        {
            var style = styles[i];
            pos += style.length;
            style = style.substring(0, style.length-1); // remove trailing semicolon ';' from each style definition.
            var styleBlock = style.indexOf(':') < 0 ? new ApplyStyleBlock(style) : new StyleBlock(style);
            this.styles.push(styleBlock);
            this.stylesByName[styleBlock.getName()] = styleBlock;
        }
        this.terminator = new TextBlock(terminator);
    };

    StyleRule.prototype = new TextBlock();

    var getFilteredStyleStrings = function(styles)
    {
        // prevent double separators by filtering out empty strings.
        return styles.map( x => x.toString() ).filter(Boolean);
    };

    StyleRule.prototype.getStyleContent = function()
    {
        var styles = getFilteredStyleStrings(this.styles);
        return styles.length > 0 ? styles.join(';') + ';' : '';
    };

    StyleRule.prototype.getText = function()
    {
        var styles = getFilteredStyleStrings(this.styles).join(';');  // don't use this.getStyleContent() because terminator already includes the last semicolon.
        if (this.touched && styles.trim() === '')
        {
            return '';  // remove rule when no styles are left.
        }
        return this.qualifiers + '{' + styles + this.terminator;
    };

    StyleRule.prototype.applyIndentation = function(indent)
    {
        this.qualifiers.applyIndentation(indent);
        for(var i = this.styles.length; i-- > 0; )
        {
            this.styles[i].applyIndentation(BLOCK_INDENT + indent);  // push style in one block level.
        }
        this.terminator.applyIndentation(indent);
    };

    StyleRule.prototype.insertComment = function(pos, comment)
    {
        var length = this.qualifiers.size();
        if (pos <= length)
        {
            this.qualifiers.insertText(pos, comment);
        }
        else
        {
            length++; // skip opening bracket '{' to get to styles.
            for(var i = 0; i < this.styles.length; i++)
            {
                pos -= length;
                var style = this.styles[i];
                length = style.size();
                if (pos <= length)
                {
                    style.insertComment(pos, comment);
                    return;
                }
                length++;  // skip semicolon ';' separators
            }

            if (this.styles.length > 0)
            {
                length--;  // don't skip last semicolon ';' separator because it is part of the terminator string.
            }

            this.terminator.insertText(pos - length, comment);
        }
    };

    StyleRule.prototype.setName = function(newName)
    {
        this.qualifiers.replaceText(newName, this.name);
        this.name = newName.trim();
    };

    StyleRule.prototype.getStyleByName = function(name)
    {
        var style = this.stylesByName[name];
        return style && style.getValue();
    };

    StyleRule.prototype.setStyleByName = function(name, value)
    {
        var style = this.stylesByName[name];
        if (style)
        {
            style.setValue(value);
            this.touched = true;
        }
        else if (value)
        {
            var styleBlock = name.indexOf('@') === 0 ? new ApplyStyleBlock(name + ';') : new StyleBlock(name + ': ' + value);
            styleBlock.touched = true;
            styleBlock.setIndent('\n' + BLOCK_INDENT + this.qualifiers.getIndent());
            this.styles.push(styleBlock);
            this.stylesByName[styleBlock.getName()] = styleBlock;
            this.touched = true;
        }
    };

    StyleRule.prototype.renameAllQualifiers = function(find, replace)
    {
        var oldQualifiers = this.name;
        var newQualifiers = oldQualifiers.replace(find, replace);
        if (oldQualifiers !== newQualifiers)
        {
            this.name = newQualifiers;
            this.qualifiers.replaceText(oldQualifiers, newQualifiers);
        }
    };
    // #endregion

    // #region StyleElement
    var uniqueStyleId = 1;
    var gAutoGenerateIds = false;

    var StyleElement = function(startTag, rules, endTag)
    {
        this.startTag = startTag;
        this.rules = rules;
        this.endTag = endTag;
        this.ruleById = {};

        for(var i = 0; i < rules.length; i++ )
        {
            var rule = rules[i];
            this.ruleById[rule.getName()] = rule;
        }

        this.id = this.attributes.id;
        if (!this.id)
        {
            // use ids to match parser stylesheets with browser stylesheets.
            this.id = 'gcAppStyle_' + uniqueStyleId++;
            this._autoGeneratedId = true;
        }
    };

    StyleElement.prototype = new TextBlock();

    StyleElement.prototype.name = 'style';
    StyleElement.prototype.localName = 'style';

    StyleElement.prototype.removeAttribute = function(name) {
        delete this.attributes[convertAttributeToProperty(name)];

        const subStartTag = this.startTag.substring(1, this.startTag.length-1);
        const segments = subStartTag.split(' ');
        for (let i = 0; i < segments.length; ++i) {
            const [key] = segments[i].split('=');
            if (key.trim() === name) {
                segments.splice(i, 1);
            }
        }
        this.startTag = '<' + segments.join(' ') + '>';
    };

    StyleElement.prototype.setAttribute = function(name, value) {
        this.attributes[convertAttributeToProperty(name)] = value;

        const subStartTag = this.startTag.substring(1, this.startTag.length-1);
        const segments = subStartTag.split(' ');

        let found = false;
        for (let i = 0; i < segments.length; ++i) {
            const [key] = segments[i].split('=');
            if (key === name) {
                segments[i] = `${name}="${value}"`;
                found = true;
                break;
            }
        }

        if (!found) {
            segments.push(`${name}=${value}`);
        }
        this.startTag = '<' + segments.join(' ') + '>';
    };

    StyleElement.prototype.getText = function()
    {
        var startTag = this.startTag;
        if (gAutoGenerateIds && this._autoGeneratedId)
        {
            startTag = startTag.replace('<style', '<style id="' + this.id + '"');
        }
        return startTag + this.rules.join('') + this.endTag;  // this should call toString() on all the rules;
    };

    StyleElement.prototype.applyIndentation = function(indent)
    {
        for(var i = this.rules; i-- > 0; )
        {
            this.rule[i].applyIndentation(BLOCK_INDENT + indent);  // push style in one block level.
        }
    };

    var insertBefore = function(array, newValues, beforeIndex)
    {
        if (!isNaN(beforeIndex) && beforeIndex >= 0 && beforeIndex < array.length)
        {
            if (newValues instanceof Array)
            {
                var args = [ beforeIndex, 0 ];
                args.push.apply(args, newValues);
                array.splice.apply(array, args);
            }
            else
            {
                array.splice(beforeIndex, 0, newValues);
            }
            return beforeIndex;
        }
        else if (newValues instanceof Array)
        {
            array.push.apply(array, newValues);
            return array.length-1;
        }
        else
        {
            array.push(newValues);
            return array.length-1;
        }
    };

    StyleElement.prototype.insertRule = function(rule /* CSSRule or CSS rule text */, beforeIndex)
    {
        let _rule = rule;
        if (typeof rule === 'string') {
            _rule = new StyleRule('\n' + rule.replace(/\\r/g, '') + '\n');
        }

        _rule.applyIndentation(BLOCK_INDENT + this.getIndent());
        const index = insertBefore(this.rules, _rule, beforeIndex);
        this.ruleById[_rule.getName()] = _rule;
        return index;
    };

    var findRuleByName = function(rules, name)
    {
        for(var i = rules.length; i-- > 0; )
        {
            if(rules[i].getName() === name)
            {
                return rules[i];
            }
        }
    };

    StyleElement.prototype.removeRule = function(rule)
    {
        for(var i = this.rules.length; i-- > 0; )
        {
            if (this.rules[i] === rule)
            {
                this.rules.splice(i, 1);
                var name = rule.getName();
                this.ruleById[name] = findRuleByName(this.rules, name);
                return i;
            }
        }
    };

    StyleElement.prototype.getRuleByName = function(id)
    {
        return this.ruleById[id];
    };

    StyleElement.prototype.getRules = function()
    {
        return this.rules;
    };

    StyleElement.prototype.renameAllQualifiers = function(find, replace)
    {
        for(var i = this.rules.length; i-- > 0; )
        {
            var rule = this.rules[i];
            var oldName = rule.getName();
            rule.renameAllQualifiers(find, replace);
            var newName = rule.getName();
            if (oldName)
            {
                this.ruleById[oldName] = undefined;
            }
            if (newName)
            {
                this.ruleById[newName] = rule;
            }
        }
    };

    Object.defineProperty(StyleElement.prototype, 'textContent',
    {
        get: function()
        {
            return this.rules.join('');
        }
    });

    var attributesRegExpr = /\s*[^\s=]+(\s*=\s*'[^']*'|\s*=\s*"[^"]*")?/g;

    Object.defineProperty(StyleElement.prototype, 'attributes',
    {
        get: function()
        {
            if (!this._attributes)
            {
                var startDelimiter = '<style';
                var endDelimiter = '>';
                var start = this.startTag.indexOf(startDelimiter) + startDelimiter.length;
                var end = this.startTag.lastIndexOf(endDelimiter);
                var attributeText = this.startTag.substring(start, end);
                var attributeList = attributeText.match(attributesRegExpr) || [];
                this._attributes = {};

                for(var i = 0; i < attributeList.length; i++)
                {
                    var attribute = new AttributeBlock(attributeList[i]);
                    this._attributes[attribute.getName()] = attribute.getValue();
                }
            }
            return this._attributes;
        }
    });

    StyleElement.prototype.getAnnotation = function()
    {
        // if there is a error in the rules, it will be the last one in the list.
        if (this.rules && this.rules.length > 0)
        {
            return this.rules[this.rules.length-1].getAnnotation();
        }
    };

    StyleElement.prototype.getErrorLineOffset = function()
    {
        var lineNo = 0;
        lineNo += this.startTag.split('\n').length - 1;

        if (this.rules)
        {
            for(var i = 0; i < this.rules.length-1; i++)
            {
                lineNo += this.rules[i].toString().split('\n').length - 1;
            }
            lineNo += this.rules[this.rules.length-1].leadingWhiteSpace.split('\n').length - 1;
        }
        return lineNo;
    };

    var BEGIN_COMMENT = '/*';
    var END_COMMENT = '*/';

    var testForExtraTerminatingCommentSymbol = function(content, pos, nextChunk)
    {
        var errPos = nextChunk.indexOf(END_COMMENT);
        if (errPos >= 0)
        {
            throw { rules: [new TextBlock(content.substring(0, pos+errPos)),
                            new ErrorBlock(content.substring(pos+errPos), '', "extra terminating '*/' comment symbol, missing corresponding start of comment '/*'.") ]};
        }
    };

    var removeComments = function(text, commentList)
    {
        var result = '';
        var content = text;
        var start = content.indexOf(BEGIN_COMMENT);
        var end = 0;
        var pos = 0;

        while(start >= 0)
        {
            end = content.indexOf(END_COMMENT, start + BEGIN_COMMENT.length);
            if (end > 0)
            {
                end += END_COMMENT.length;

                if (start > 0)
                {
                    var nextChunk = content.substring(0, start);
                    testForExtraTerminatingCommentSymbol(text, pos, nextChunk);
                    result += nextChunk;
                }
                commentList.push( {pos: result.length, comment: content.substring(start, end) } );

                content = content.substring(end);
                start = content.indexOf(BEGIN_COMMENT, 0);
                pos += end;
                end = 0;
            }
            else
            {
                throw { rules: [new TextBlock(text.substring(0, pos+start)),
                                new ErrorBlock(text.substring(pos+start), '', "missing terminating '*/' comment symbol") ]};
            }
        }
        if (end < content.length)
        {
            var trailingText = content.substring(end);
            testForExtraTerminatingCommentSymbol(text, pos, trailingText);
            result += trailingText;
        }
        return result;
    };

    var parseCSSRules = function(text)
    {
        var contentWithoutComments = text;
        var commentBlocks = [];
        var result = [];
        var pos = 0;

        try
        {
            // remove comments before parsing CSS rules within the style block.
            contentWithoutComments = removeComments(text, commentBlocks);

            var unsupportedRules = ['@apply', '@import'];
            for(var j = 0; j < unsupportedRules.length; j++)
            {
                var unsupportedPos = contentWithoutComments.indexOf(unsupportedRules[j]);
                if (unsupportedPos >= 0)
                {
                    throw { message: unsupportedRules[j] + " css rules are not supported in a .gui file(s).", pos: unsupportedPos };
                }
            }

            var rules = contentWithoutComments.split('}');
            var count = rules.length;

            for(var index = 0; index < count - 1; index++ )
            {
                var rule = rules[index];
                var matches = rule.match(/\{/g);
                var openBraces = matches ? matches.length : 0;

                if (openBraces < 1 && index < count-1)
                {
                    throw { rule: rule, pos: pos };
                }
                else
                {
                    // eat nested closing braces.
                    for( ; openBraces > 1; openBraces--)
                    {
                        index++;
                        if (index === count-1)
                        {
                            throw { rule: rule, pos: pos };
                        }
                        matches = rules[index].match(/\{/g);
                        openBraces += (matches ? matches.length: 0);
                        rule = rule + '}' + rules[index];
                    }
                }
                pos = pos + rule.length + 1;
                result.push(new StyleRule(rule + '}'));
            }
            var trailingText = rules[count-1];
            if (trailingText.trim() === '')
            {
                if (result.length > 0)
                {
                    // add any trailing whitespace to the end of the last rule's terminator text.
                    result[result.length - 1].terminator.content += rules[count-1];
                }
            }
            else
            {
                throw { rule: trailingText, pos: pos };
            }
        }
        catch(err)
        {
            if ((err.message || err.rule) && err.pos !== undefined)
            {
                result = [];
                var message = err.message;
                if (err.rule)
                {
                    var openingBrace = err.rule.indexOf('{');
                    if (openingBrace >= 0)
                    {
                        message = 'Missing closing brace "}" for rule: ' + err.rule.substring(0, openingBrace).trim();
                    }
                    else
                    {
                        message = 'Missing opening brace "{" for rule: ' + (err.rule.match(/\s*[^\s,]+/) || [err.rule])[0].trim();
                    }
                }
                if (err.pos > 0)
                {
                    result.push(new TextBlock(contentWithoutComments.substring(0, err.pos)));
                }
                result.push(new ErrorBlock(contentWithoutComments.substring(err.pos), '', message));
            }
            else if (err.rules)
            {
                return err.rules;
            }
            else
            {
                throw err;
            }
        }

        // insert comments back into the style rules to preserve original text.
        var i = result.length;
        pos = contentWithoutComments.length;
        for(var j = commentBlocks.length; j-- > 0; )
        {
            var styleRule;
            var commentBlock = commentBlocks[j];
            while(pos > commentBlock.pos)
            {
                styleRule = result[--i];
                pos -= styleRule.size();
            }
            if (styleRule)
            {
                styleRule.insertComment(commentBlock.pos - pos, commentBlock.comment);
            }
        }

        return result;
    };

    var matchEndStyleRegExpr = /\s*<\/style\s*>/;

    var parseStyleElement = function(content)
    {
        var name = 'style';
        var endTag = "";
        try
        {
            // find terminator with preceding white space.
            var matches = content.match(matchEndStyleRegExpr);
            if (!matches)
            {
                return new ErrorBlock('<' + name, content.substring(name.length), "Missing </style> terminator for <style> tag.");
            }
            endTag = matches[0];
            content = content.substring(0, content.indexOf(endTag));

            // find end of open style tag
            var pos = findPosNotInQuotes(content, '>');
            if (pos < 0)
            {
                return new ErrorBlock('<' + name, content.substring(name.length) + endTag, "Missing closing bracket '>' for style tag.");
            }
            var startTag = '<' + content.substring(0, pos+1);
            var ruleContent = content.substring(pos+1);

            // parse css style rules
            var rules = parseCSSRules(ruleContent);

            var parsedContent = rules.join('');
            if (parsedContent !== ruleContent)
            {
                return new ErrorBlock('<' + content + endTag, '', "Trouble reading styles, there must be a syntax error.");
            }

            return new StyleElement(startTag, rules, endTag);
        }
        catch(e)
        {
            return new ErrorBlock('<' + content.substring(name.length), endTag, e);
        }
    };
    // #endregion

    // #region ScriptBlock
    var ScriptBlock = function(content)
    {
        this.content = '<' + content + '</script>';
    };

    ScriptBlock.prototype = new CDATABlock();

    ScriptBlock.prototype.name = 'script';
    ScriptBlock.prototype.getAttributeText = function() {
        let startDelimiter = '<script';
        let endDelimiter = '>';
        let start = this.content.indexOf(startDelimiter) + startDelimiter.length;
        let end = this.content.indexOf(endDelimiter, start);
        return this.content.substring(start, end);
    };

    var parseScriptBlock = function(content)
    {
        var name = "script";
        var terminator = '</' + name + '>';
        var pos = content.indexOf(terminator);
        if (pos >= 0)
        {
            return new ScriptBlock(content.substring(0, pos));
        }
        return new ErrorBlock('<' + name, content.substring(name.length), 'missing a terminating ' + terminator + ' tag');
    };
    // #endregion

    // #region AbstractElementBlock
    var trailingSpacesInsideTagRegExpr = /\s*\/?$/;

    var AbstractElementBlock = function(content)
    {
        if (content)
        {
            this._bindings = {};

            var selfTerminating = content[content.length-1] === '/';
            this.trailingSpaces = content.match(trailingSpacesInsideTagRegExpr);
            if (this.trailingSpaces)
            {
                this.trailingSpaces = this.trailingSpaces[0];
                content = content.substring(0, content.length-this.trailingSpaces.length);
            }
            else
            {
                this.trailingSpaces = '';
            }

            this.content = content.match(attributesRegExpr);
            this.attributes = {};

            for(var i = 1; i < this.content.length; i++)
            {
                var attribute = new AttributeBlock(this.content[i]);
                this.attributes[convertAttributeToProperty(attribute.getName())] = attribute;
            }

            this.name = this.content[0].trim();
            this._id = this.getAttribute('id');

            if (selfTerminating)
            {
                this.setClosingTag(this);
            }
        }
    };

    AbstractElementBlock.prototype = new TextBlock();

    AbstractElementBlock.prototype.extraBlockIndent = BLOCK_INDENT + BLOCK_INDENT;

    AbstractElementBlock.prototype.getText = function()
    {
        return '<' + this.content.join('') + this.trailingSpaces + '>';
    };

    AbstractElementBlock.prototype.getTextRange = function()
    {
        var closeTag  = this.getClosingTag();
        var startPos  = this.document.getTextPosition(this);
        var endPos    = this.document.getTextPosition(closeTag);

        var segments = closeTag.getText().split('\n');
        var lineCount = segments.length - 1;
        if (lineCount > 0)
        {
            endPos.column = segments[lineCount].length;
            endPos.row += lineCount;
        }
        else
        {
            endPos.column += segments[lineCount].length;
        }

        return {start: startPos, end: endPos};
    };

    AbstractElementBlock.prototype.getAnnotation = function()
    {
        if (this._id && this.document.elementsById[this._id] !== this)
        {
            return {
                type: 'error',
                text: 'This widget does not have a unique id.  Please make the id attribute unique within this design'
            };
        }
    };

    AbstractElementBlock.prototype.applyIndentation = function(indent)
    {
        TextBlock.prototype.applyIndentation.call(this, indent);

        this.trailingSpaces = applyIndentationToContent(this.trailingSpaces, this.extraBlockIndent + indent);
    };

    AbstractElementBlock.prototype.getAttribute = function(name)
    {
        var attr = this.attributes[name];

        return attr && attr.getValue();
    };

    AbstractElementBlock.prototype.updateContent = function(newValue, oldValue)
    {
        var args = this.content;
        for(var i = args.length; i --> 1; )
        {
            if (args[i] === oldValue)
            {
                args[i] = newValue;
                break;
            }
        }
    };

    AbstractElementBlock.prototype.setAttribute = function(name, value, sortedNames)
    {
        var attr = this.attributes[name];
        var inlineBindExpression = attr && attr.getBinding();
        var isValue = value !== undefined && value !== "" && value !== false && value !== null;

        if (inlineBindExpression)
        {
            // don't remove value if an inline binding is present, just set the value to restore if binding is deleted.
            attr.setValue(isValue ? value: undefined);
        }
        else if (isValue)
        {
            if (attr)
            {
                var oldValue = attr.getText();
                attr.setValue(value);
                var newValue = attr.getText();

                this.updateContent(newValue, oldValue);
            }
            else
            {
                this.insertAttribute(name, value, this.computeInsertBeforeIndex(name, sortedNames));
            }
        }
        else
        {
            this.removeAttribute(name);
        }
    };

    AbstractElementBlock.prototype.insertAttribute = function(name, value, beforeIndex)
    {
        var attr = createAttributeBlock(name, value);
        this.attributes[name] = attr;

        insertBefore(this.content, attr.getText(), beforeIndex);
        return attr;
    };

    AbstractElementBlock.prototype.computeInsertBeforeIndex = function(name, sortedNames)
    {
        if (sortedNames && sortedNames.length > 1)  // there has to be at least two things in order to determine which goes before which.
        {
            // 1. find the priority of the property in question.
            var oldValues = {};
            for(var k = 0; k < sortedNames.length && sortedNames[k] !== name; )
            {
                k++;
            }

            // 2. go through all lower priority properties, and cache them in oldValues if they are present.
            for(var j = sortedNames.length; j --> k + 1; )
            {
                var attr = this.attributes[sortedNames[j]];
                if (attr)
                {
                    oldValues[attr.getText()] = true;
                }
            }

            // 3. find the insertion point of first lower priority property in the current ordering of attributes.
            var args = this.content;
            for(var i = 1; i < args.length; i++ ) // first element in this.content is the tag name.
            {
                if (oldValues.hasOwnProperty(args[i]))
                {
                    return i;  // insert new attribute in front of first attribute found with a lower order.
                }
            }
        }
        else if (name === 'id')  // special case, insert id's for newly created elements at the front of the attributes list.
        {
            return 1;
        }
        return -1;  // insert at the end.
    };

    AbstractElementBlock.prototype.findAttributeIndex = function(name)
    {
        var attr = this.attributes[name];
        if (attr)
        {
            var args = this.content;
            var text = attr.getText();
            for(var i = args.length; i --> 1; )
            {
                if (text === args[i])
                {
                    return i;
                }
            }
        }

        return -1;
    };

    AbstractElementBlock.prototype.removeAttribute = function(name)
    {
        var index = this.findAttributeIndex(name);
        if (index >= 0)
        {
            this.content.splice(index, 1);
            delete this.attributes[name];
        }
    };

    AbstractElementBlock.prototype.setClosingTag = function(closingTag)
    {
        this._closingTag = closingTag;
    };

    AbstractElementBlock.prototype.setBinding = function(propertyName, bindingExpression, templateId)
    {
        var attr = this.attributes[propertyName];
        var oldValue, newValue;

        delete this._bindings[propertyName];

        if (bindingExpression && bindingExpression !== '')
        {
            // Add binding
            templateId = templateId || 'template_obj';
            templateId = '$.' + templateId + '.';
            if (bindingExpression.indexOf(templateId) === 0)
            {
                // add inline binding
                if (!attr)
                {
                    attr = this.insertAttribute(propertyName);
                    attr.value = undefined;
                }
                oldValue = attr.getText();
                attr.setBinding(bindingExpression.substring(templateId.length));
                newValue = attr.getText();

                this.updateContent(newValue, oldValue);
            }
            else
            {
                // clear old inline binding first if there was one, then add json binding.
                this.setBinding(propertyName);
                this._bindings[propertyName] = bindingExpression;
            }
        }
        else if (attr)
        {
            // remove inline binding if there is one.
            if (attr.getValue())
            {
                oldValue = attr.getText();
                attr.removeBinding();
                newValue = attr.getText();

                this.updateContent(newValue, oldValue);
            }
            else
            {
                this.removeAttribute(propertyName);
            }
        }
    };

    AbstractElementBlock.prototype.getBinding = function(propertyName, templateId)
    {
        var bindExpression = this._bindings[propertyName];
        if (!bindExpression)
        {
            var attribute = this.attributes[propertyName];
            bindExpression = attribute && attribute.getBinding();
            if (bindExpression)
            {
                bindExpression = '$.' + templateId + '.' + bindExpression;
            }
        }
        return bindExpression;
    };

    AbstractElementBlock.prototype.getBindings = function(templateId)
    {
        var result = {};
        if (templateId)
        {
            for(var attrName in this.attributes)
            {
                if (this.attributes.hasOwnProperty(attrName))
                {
                    var attr = this.attributes[attrName];
                    var binding = attr && attr.getBinding();
                    if (binding)
                    {
                        result[attrName] = '$.' + templateId + '.' + binding;
                    }
                }
            }
        }

        if (this._id && this._bindings)
        {
            for(var propertyName in this._bindings)
            {
                if (this._bindings.hasOwnProperty(propertyName))
                {
                    var bindingExpression = this._bindings[propertyName];
                    if (bindingExpression)
                    {
                        result[propertyName] = bindingExpression;
                    }
                }
            }
        }
        return result;
    };

    AbstractElementBlock.prototype.getAllBindings = function()
    {
        var result = [];
        if (this._id && this._bindings)
        {
            for(var propertyName in this._bindings)
            {
                if (this._bindings.hasOwnProperty(propertyName))
                {
                    var bindingExpression = this._bindings[propertyName];
                    if (bindingExpression)
                    {
                        if (bindingExpression.indexOf('$.') === 0)
                        {
                            bindingExpression = bindingExpression.replace('$.', 'widget.');
                        }
                        result.push(
                        {
                            widgetId: this._id,
                            serverBindName: bindingExpression,
                            propertyName: propertyName
                        });
                    }
                }
            }
        }
        return result;
    };

    AbstractElementBlock.prototype.extractAllTemplateBindings = function() {
        var result = [];
        for(var attrName in this.attributes)
        {
            if (this.attributes.hasOwnProperty(attrName))
            {
                var attr = this.attributes[attrName];
                var bindingExpression = attr && attr.getBinding();
                if (bindingExpression)
                {
                    result.push(
                        {
                            widgetId: this._id,
                            serverBindName: bindingExpression,
                            propertyName: attrName,
                            options:
                            {
                                oneWay: attr._isBindExpressionOneWay
                            }
                        });
                    this.removeAttribute(attrName);
                }
            }
        }
        return result;
    };

    var inLineJsonBindingPostfix = '_bind$';

    AbstractElementBlock.prototype.compressBindingsInline = function(srcElement, useMustacheNotation = false)
    {
        var bindings = srcElement._bindings;
        if (bindings)
        {
            for(var propertyName in bindings)
            {
                if (bindings.hasOwnProperty(propertyName))
                {
                    var bindExpression = bindings[propertyName];
                    if (bindExpression)
                    {
                        if (useMustacheNotation)
                        {
                            var attr = this.attributes[propertyName];
                            if (attr)
                            {
                                attr.setBinding(bindExpression);
                            }
                            else
                            {
                                this.setAttribute(propertyName, '{{' + bindExpression + '}}');
                            }
                        }
                        else
                        {
                            this.setAttribute(propertyName + inLineJsonBindingPostfix, bindExpression);
                        }
                    }
                }
            }
        }
    };

    AbstractElementBlock.prototype.expandInlineBindings = function(srcElement)
    {
        var attributes = srcElement.attributes;
        if (attributes)
        {
            for(var propertyName in attributes)
            {
                if (attributes.hasOwnProperty(propertyName))
                {
                    var len = propertyName.length - inLineJsonBindingPostfix.length;
                    if (len > 0 && propertyName.indexOf(inLineJsonBindingPostfix) === len)
                    {
                        var attribute = attributes[propertyName];
                        if (attribute)
                        {
                            this.setBinding(propertyName.substring(0, len), attribute.getValue());
                            this.removeAttribute(propertyName);
                        }
                    }
                }
            }
        }
    };

    var renameWidgetInBindingExpressions = function(bindings, regex, replaceCallback)
    {
        // rename JSON bindings
        if (bindings)
        {
            for(var propertyName in bindings)
            {
                if (bindings.hasOwnProperty(propertyName))
                {
                    var bindExpression = bindings[propertyName];
                    if (bindExpression)
                    {
                        bindings[propertyName] = bindExpression.replace(regex, replaceCallback);
                    }
                }
            }
        }
    };

    Object.defineProperty(AbstractElementBlock.prototype, 'parentElement',
    {
        get: function()
        {
            return this.document.getParentContainer(this.documentOffset);
        }
    });

    Object.defineProperty(AbstractElementBlock.prototype, 'firstElementChild',
    {
        get: function()
        {
            return this.document.getFirstElementChild(this.documentOffset);
        }
    });

    Object.defineProperty(AbstractElementBlock.prototype, 'nextElementSibling',
    {
        get: function()
        {
            return this.document.getNextElementSibling(this.documentOffset);
        }
    });

    Object.defineProperty(AbstractElementBlock.prototype, 'children',
    {
        get: function()
        {
            return this.document.getChildren(this.documentOffset);
        }
    });

    Object.defineProperty(AbstractElementBlock.prototype, 'textContent',
    {
        get: function()
        {
            return this.document.getTextContent(this.documentOffset);
        }
    });

    AbstractElementBlock.prototype.getOuterHTML = function()
    {
        return this.document.getOuterHTML(this.documentOffset);
    };

    Object.defineProperty(AbstractElementBlock.prototype, 'localName',
    {
        get: function()
        {
            return this.getName();
        }
    });

    Object.defineProperty(AbstractElementBlock.prototype, 'id',
    {
        get: function()
        {
            return this._id;
        }
    });

    var getInlineStyleRule = function(element)
    {
        if (!element._inlineStyleRule)
        {
            var styles = element.getAttribute('style') || '';
            styles = styles.trim();
            if (styles[styles.length-1] !== ';')
            {
                styles += ';';  // ensure trailing semicolon.
            }
            element._inlineStyleRule = new StyleRule('temp {' + styles + '}');
        }
        return element._inlineStyleRule;
    };

    AbstractElementBlock.prototype.getStyle = function(styleName)
    {
        if (this._id)
        {
            return this.document.getStyleByName(this._id, styleName);
        }
        else
        {
            var rule = getInlineStyleRule(this);
            return rule.getStyleByName(styleName);
        }
    };

    // TODO: add protection against invalid input.  currently you can enter anything in a style text box, and we
    // will generate incorrect html as a result, which cannot be parsed back.
    AbstractElementBlock.prototype.setStyle = function(styleName, value)
    {
        if (this._id)
        {
            this.document.setStyleByName(this._id, styleName, value);
        }
        else
        {
            var rule = getInlineStyleRule(this);
            rule.setStyleByName(styleName, value);
            var styles = rule.getStyleContent().replace(matchWhiteSpaceRegExpr, ' ').trim();
            this.setAttribute('style', styles);
        }
    };

    AbstractElementBlock.prototype.getProperty = AbstractElementBlock.prototype.getAttribute;
    AbstractElementBlock.prototype.setProperty = AbstractElementBlock.prototype.setAttribute;

    AbstractElementBlock.prototype.getId = function()
    {
        return this._id;
    };

    AbstractElementBlock.prototype.setId = function(newId)
    {
        return this.document.renameElement(this, newId || this.getName(), this._id);
    };

    AbstractElementBlock.prototype.getPosition = gc.designer.editor.AbstractDomElement.prototype.getPosition;
    AbstractElementBlock.prototype.setPosition = gc.designer.editor.AbstractDomElement.prototype.setPosition;
    AbstractElementBlock.prototype.getSize = gc.designer.editor.AbstractDomElement.prototype.getSize;
    AbstractElementBlock.prototype.setSize = gc.designer.editor.AbstractDomElement.prototype.setSize;
    AbstractElementBlock.prototype.getClass = gc.designer.editor.AbstractDomElement.prototype.getClass;
    AbstractElementBlock.prototype.setClass = gc.designer.editor.AbstractDomElement.prototype.setClass;

    AbstractElementBlock.prototype.getContainer = function()
    {
        return this.document.getParentContainer(this.getDocumentPos());
    };

    AbstractElementBlock.prototype.rename = function(name)
    {
        this.setName(name);
        this.content[0] = name;
        this.getClosingTag().rename(name);
    };

    AbstractElementBlock.prototype.renameAttribute = function(fromName, toName)
    {
        fromName = convertAttributeToProperty(fromName);
        toName = convertAttributeToProperty(toName);
        if (fromName !== toName && this.attributes[fromName]) {
            const oldAttrText = this.attributes[fromName].getText();
            this.attributes[fromName].rename(convertPropertyToAttribute(toName));
            this.attributes[toName] = this.attributes[fromName];
            delete this.attributes[fromName];
            this.updateContent(this.attributes[toName].getText(), oldAttrText);

            var regex = new RegExp('((^|[^\\w\\$\\.])(\\$|widget)\\.)' + this.id + '\\.' + fromName, 'gm');
            var replaceCallback = (match, g1) =>
            {
                return g1 + this.id + '.' + toName;
            };
            this.document.blockList.forEach(block => {
                renameWidgetInBindingExpressions(block._bindings, regex, replaceCallback);
            });
        }
    };

    AbstractElementBlock.prototype.insertText = function(htmlText, before, meta)
    {
        before = before || this.getClosingTag();
        var parserIndex = before.getDocumentPos();

        var newParserElement = this.document.insertText(htmlText, parserIndex, true, meta);

        var newChildren = [];
        parserIndex = before.getDocumentPos();  // get new position after insert.

        while(newParserElement && newParserElement.getDocumentPos() < parserIndex)
        {
            newChildren.push(newParserElement);
            newParserElement = newParserElement.nextElementSibling;
        }
        return newChildren;
    };

    AbstractElementBlock.prototype.isAnOrphan = function()
    {
        return this.document.isAnOrphan(this);
    };

    AbstractElementBlock.prototype.insertBefore = function(child, before)
    {
        // validate we are inserting a child into this container.
        var end = this.getClosingTag().getDocumentPos();
        var start = this.getDocumentPos();
        var beforeIndex = (before || this.getClosingTag()).getDocumentPos();
        if (beforeIndex <= start || beforeIndex > end)
        {
            throw "Programmer Error: before is not a valid index for this container";
        }
        else if (child.isAnOrphan())
        {
            this.document.insertBefore(child._undoInfo, beforeIndex);
        }
        else // move operation
        {
            this.document.move(this, child, before);
        }
    };

    AbstractElementBlock.prototype.removeChild = function(child)
    {
        var endTag = child.getClosingTag();
        var index = child.getDocumentPos();
        var length = child.getClosingTag().getDocumentPos() - index + 1;

        // validate we are removing a child from this container.
        var end = this.getClosingTag().getDocumentPos();
        var start = this.getDocumentPos();
        if (index <= start || index >= end)
        {
            throw "Programmer Error: child is not found wihin this container";
        }

        child._undoInfo = child._undoInfo || {};
        child._undoInfo.blockList = this.document.remove(index, length);
    };

    AbstractElementBlock.prototype.attached = function()
    {
        var undoStyle = this._undoInfo && this._undoInfo.styles;
        this.document.pasteStyles(this.id, undoStyle);
        this.document.registerId(this);

        if (!this._undoInfo)
        {
            console.error("Programmers Error: missing _undoInfo for attached operation");
        }
    };

    AbstractElementBlock.prototype.detached = function()
    {
        this.document.unregisterId(this);
        this._undoInfo = this._undoInfo || {};

        this._undoInfo.styles = this.document.cutStyles(this.id);
    };
    // #endregion

    // #region ClosingElementBlock
    var ClosingElementBlock = function(content)
    {
        this.rename(content);
    };

    ClosingElementBlock.prototype = new TextBlock();

    ClosingElementBlock.prototype.rename = function(name)
    {
        this.content = '</' + name + '>';
        this.name = name.trim();
    };

    ClosingElementBlock.prototype.findMatchingOpeningTag = function(blockList)
    {
        var closeName = this.getName();
        var found = false;
        // find matching opening tag
        for(var i = blockList.length; i --> 0; )
        {
            var openTag = blockList[i];
            if (openTag instanceof AbstractElementBlock && openTag.getName() === closeName && openTag.isTagNotClosed() )
            {
                // found a match
                openTag.setClosingTag(this);
                found = true;
                break;
            }
        }
        if (!found)
        {
            this.missingOpeningTag = true;
        }
    };

    ClosingElementBlock.prototype.getAnnotation = function()
    {
        if (this.missingOpeningTag)
        {
            return {
                type: 'error',
                text: 'Extra closing tag not matched with any opening tags'
            };
        }
    };

    var tagNameRegExpr = /^[^\s\/>]+/;

    var parseElementBlock = function(content, ElementBlock)
    {
        if (content[0] === '!')
        {
            return parseSGMLBlock(content.substring(1));
        }

        var pos = findPosNotInQuotes(content, '>');
        if (pos <= 0)
        {
            return new ErrorBlock('<', content, 'no matching closing brace ">"');
        }

        if (content[0] === '/')
        {
            return new ClosingElementBlock(content.substring(1, pos));
        }

        var name = content.match(tagNameRegExpr);
        if (name)
        {
            name = name[0];
            if (name === 'style')
            {
                return parseStyleElement(content);
            }
            if (name === 'script')
            {
                return parseScriptBlock(content);
            }

            content = content.substring(0, pos);
            var tag = new ElementBlock(content);

            // verify that the generated text is the same as the parsed text.
            content = '<' + content + '>';
            if (tag.getText() !== content)
            {
                return new ErrorBlock(content, '', "Trouble reading attributes, there must be a syntax error.");
            }
            return tag;
        }
        else
        {
            return new ErrorBlock('<', content, "Missing the tag name which must follow immediately without spaces.");
        }
    };
    // #endregion

    // #region HTMLParser
    var HTMLParser = function(htmlContent, ElementBlock, metaVersion)
    {
        htmlContent = htmlContent || "";
        if (!ElementBlock)
        {
            ElementBlock = function(content)
            {
                AbstractElementBlock.call(this, content);
            };
            ElementBlock.prototype = new AbstractElementBlock();
            ElementBlock.prototype.document = this;
        }

        this.metaVersion = metaVersion;
        this.element = {};
        this.element.factory = ElementBlock;
        this.blockList = [];
        this.lineFeed = htmlContent.indexOf('\r') >= 0;
        this.parse(htmlContent.replace(/\r\n/g, '\n'));

        this.elementsById = {};
        this.registerIds();

        this.catelogAllStylesheets();
    };

    HTMLParser.prototype.getText = function()
    {
        return this.addLineFeeds(this.blockList.join(''));
    };

    HTMLParser.prototype.addLineFeeds = function(htmlContent)
    {
        if (this.lineFeed)
        {
            return htmlContent.replace(/\n/g, '\r\n');
        }
        return htmlContent;
    };

    var verifyPushBlock = function(html, content, tag)
    {
        var text = tag.toString();
        if (content.indexOf(text) !== 0)
        {
            console.error("Programmer Error: HTML parsed content doesn't match original");
        }
        tag.documentOffset = html.blockList.length;
        html.blockList.push(tag);
        return content.substring(text.length);
    };

    HTMLParser.prototype.parse = function(content)
    {
        var done = false;
        while(!done)
        {
            var pos = content.indexOf('<');
            if (pos < 0)
            {
                // no tags, one big text block, often it will be the trailing white space for the document or snippet.
                verifyPushBlock(this, content, new TextBlock(content));
            }
            else
            {
                var nextIndent = '';
                if (pos > 0)
                {
                    nextIndent = content.substring(0, pos);
                    var text = nextIndent.trim();
                    if (text !== '')
                    {
                        var whiteSpace = nextIndent.split(text);
                        content = verifyPushBlock(this, content, new TextBlock(whiteSpace[0], text));
                        nextIndent = whiteSpace[1];
                        pos = nextIndent.length;
                    }
                }

                var tag = parseElementBlock(content.substring(pos+1), this.element.factory);
                tag.setIndent(nextIndent);

                if (tag instanceof ClosingElementBlock)
                {
                    tag.findMatchingOpeningTag(this.blockList);
                }

                content = verifyPushBlock(this, content, tag);
                if (content)
                {
                    continue;  // keep going as long as there is content left to parse.
                }
            }
            done = true;
        }
    };

    var findIndentation = function(blockList, beforeIndex)
    {
        while(beforeIndex >= 0)
        {
            var block = blockList[beforeIndex--];
            if (block && !block.isInline())
            {
                return block.getIndent();
            }
        }
        return "";
    };

    HTMLParser.prototype.applyIndentation = function(indent, start, end)
    {
        var indentStack = [];
        var tos = 0;
        var closeTag;
        start = start || 0;
        end = end || this.blockList.length;
        if (indent === undefined || indent === null)
        {
            indent = findIndentation(this.blockList, start - 1);
        }

        for(var i = start; i < end; i++ )
        {
            var element = this.blockList[i];

            if (closeTag === element)
            {
                // pop the stack for closing tag before indenting it.
                tos--;
                indent = indentStack[tos].indent;
                closeTag = indentStack[tos].closeTag;
            }

            element.applyIndentation(indent);

            var endTag = element.getClosingTag();
            if (endTag !== element)
            {
                // push the stack for opening tag after indenting it.
                indentStack[tos++] = { indent: indent, closeTag: closeTag };
                indent = BLOCK_INDENT + indent;
                closeTag = endTag;
            }
        }
    };

    HTMLParser.prototype.insertBefore = function(src, beforeIndex)
    {
        insertBefore(this.blockList, src.blockList, beforeIndex);
        this.reIndex(beforeIndex);
    };

    var stripLeadingRelativePathRegExpr = /^[\.\/]+/;
    var stripLeadingRelativePath = function(path)
    {
        if (path)
        {
            var leadingRelativePath = path.match(stripLeadingRelativePathRegExpr);
            if (leadingRelativePath)
            {
                path = path.substring(leadingRelativePath[0].length);
            }
        }
        return path;
    };

    HTMLParser.prototype.getStartOfGist = function()
    {
        var result = this.getElementByType('head') || this.blockList[0];
        for(var commentTag = result; commentTag; commentTag = this.getElementByType('SGML', commentTag.getDocumentPos()+1))
        {
            if (commentTag.getText() === '<!--gist-begin-->')
            {
                result = commentTag;
                break;
            }
        }
        return result;
    };

    HTMLParser.prototype.updateImportLinks = function(dependencyMap, purge, skipInsert)
    {
        // 1. create mapping from stripped relative path to original path
        var dependencyMapping = {};
        for(var path in dependencyMap)
        {
            if (dependencyMap.hasOwnProperty(path))
            {
                dependencyMapping[stripLeadingRelativePath(path)] = path;
            }
        }

        // 2. filter mapping by those already imported, and remove links no longer needed if purge is true.
        // var lastLink, dependencyPath;
        let lastPath, dependencyPath;
        for(var i = this.blockList.length; i --> 0; )
        {
            var element = this.blockList[i];
            if (element instanceof CDATABlock || element instanceof AbstractElementBlock) {
                let name = element.getName();
                let path = null;

                switch (this.metaVersion) {
                    case 3:
                        if (name === 'script' && element.getAttribute('type') === 'module') {
                            path = stripLeadingRelativePath(element.getAttribute('src'));
                        }
                        break;

                    default:
                        if (name === 'link') {
                            path = stripLeadingRelativePath(element.getAttribute('href'));
                        }

                        break;
                }

                if (path) {
                    dependencyPath = dependencyMapping[path];
                    if (purge && dependencyPath && dependencyMap.hasOwnProperty(dependencyPath) && !dependencyMap[dependencyPath]) {
                        var index = element.getDocumentPos();
                        var length = element.getClosingTag().getDocumentPos() - index + 1;
                        this.blockList.splice(index, length);
                    } else {
                        if (!lastPath) {
                            lastPath = element.getClosingTag();
                        }
                        dependencyMapping[path] = undefined;
                    }
                }
            }
        }
        if (purge)
        {
            this.reIndex();
        }

        // 3. Get missing links that need to be inserted into the document, and insert them if skipInsert !== true
        const gistStart = this.getStartOfGist();
        if (!lastPath || lastPath.getDocumentPos() < gistStart.getDocumentPos())
        {
            lastPath = gistStart;
        }

        var newImports = '';
        var results = [];
        for(path in dependencyMapping)
        {
            if (dependencyMapping.hasOwnProperty(path))
            {
                dependencyPath = dependencyMapping[path];
                if (dependencyMap[dependencyPath])
                {
                    switch (this.metaVersion) {
                        case 3:
                            newImports += '\n<script type="module" src="' + dependencyPath + '"></script>';
                            break;
                        default:
                            newImports += '\n<link rel="import" href="' + dependencyPath + '">';
                            break;
                    }
                    results.push(dependencyPath);
                }
            }
        }
        if (newImports !== '' && !skipInsert) {
            const beforeIndex = lastPath.getDocumentPos();
            if (beforeIndex > gistStart.getDocumentPos()) {
                this.insertText(newImports, beforeIndex + 1, true);
            } else {
                this.insertText(newImports.trim() + '\n', beforeIndex, true);
            }
        }
        return results;
    };

    HTMLParser.prototype.getOuterHTML = function(documentOffset)
    {
        var outerHtml = this.getTextContent(documentOffset, true);
        var copySnippet = new HTMLParser(outerHtml, this.element.factory);
        copySnippet.compressStylesInline(this);
        copySnippet.compressBindingsInline(this);

        return copySnippet.getText();
    };

    // TODO: should try to keep comments with the next tag (cut and paste and move)

    HTMLParser.prototype.insertText = function(text, beforeIndex, autoIndent, meta)
    {
        var newElement;
        if (text)  // don't bother inserting blank text.
        {
            var insertSnippet = new HTMLParser(text, this.element.factory);

            // find first element inserted.
            for(var i = 0; i < insertSnippet.blockList.length; i++)
            {
                if (insertSnippet.blockList[i] instanceof AbstractElementBlock)
                {
                    newElement = insertSnippet.blockList[i];
                    break;
                }
            }

            insertSnippet.removeEmptyAttributeStrings(this, meta);
            insertSnippet.createUniqueIds(this);
            insertSnippet.expandInlineStyles(this);
            insertSnippet.expandInlineBindings();

            beforeIndex = beforeIndex ?? this.blockList.length;
            if (autoIndent)
            {
                insertSnippet.applyIndentation(findIndentation(this.blockList, beforeIndex - 1));
            }
            this.insertBefore(insertSnippet, beforeIndex);

            return newElement;
        }
    };

    HTMLParser.prototype.unregisterId = function(element)
    {
        var id = element.id;
        if (id)
        {
            this.elementsById[id] = undefined;
        }
    };

    HTMLParser.prototype.registerId = function(element)
    {
        var id = element.id;
        if (id)
        {
            if (this.elementsById[id])
            {
                console.log('Warning: ids are not unique.');
            }
            else
            {
                this.elementsById[id] = element;
            }
        }
    };

    HTMLParser.prototype.registerIds = function(element)
    {
        var startIndex = (element && element.getDocumentPos()) || 0;
        var endIndex = (element && element.getClosingTag().getDocumentPos()) || this.blockList.length - 1;

        for(var i = startIndex; i <= endIndex; i++)
        {
            element = this.blockList[i];
            if (element instanceof AbstractElementBlock)
            {
                this.registerId(element);
            }
        }
    };

    HTMLParser.prototype.remove = function(index, length)
    {
        var blocks = this.blockList.splice(index, length);
        this.reIndex(index);
        return blocks;
    };

    HTMLParser.prototype.isAnOrphan = function(child)
    {
        var pos = child.getDocumentPos();
        return pos < 0 || pos >= this.blockList.length || this.blockList[pos] !== child;
    };

    HTMLParser.prototype.move = function(parent, child, before)
    {
        var beforeElement = before || parent.getClosingTag();
        var to = beforeElement.getDocumentPos();
        var from = child.getDocumentPos();

        if (from !== to)
        {
            var length = child.getClosingTag().getDocumentPos() - from + 1;
            var srcContainer = child.getContainer();
            var indent;
            if (srcContainer !== parent)
            {
                indent = findIndentation(this.blockList, to);

                var destInline = parent.getClosingTag().isInline();
                var srcInline = child.isInline();
                if (srcInline !== destInline)
                {
                    // If either is not inline, then add CR to make the other not inline too.
                    if (srcInline)
                    {
                        child.setIndent('\n');
                    }
                    else // destInLine
                    {
                        parent.getClosingTag().setIndent('\n' + indent);
                    }
                }

                if (!before)
                {
                    indent = BLOCK_INDENT + indent;
                }
            }

            // remove from source location
            var blocks = this.blockList.splice(from, length);

            if (to > from)
            {
                // adjust destination for after the removal
                to = to - length;
            }

            // insert at destination location
            insertBefore(this.blockList, blocks, to);

            this.reIndex(Math.min(from, to), Math.max(from, to) + length);

            if (srcContainer !== parent)
            {
                this.applyIndentation(indent, to, to + length);

                if (srcContainer)
                {
                    // clean-up, by make a two line containers inline.
                    var lineCount = this.getLineNumber(srcContainer.getClosingTag(), srcContainer.getDocumentPos());
                    if (lineCount === 2)
                    {
                        srcContainer.getClosingTag().setIndent('');
                    }
                }
            }
        }
    };

    HTMLParser.prototype.copy = function(index, length)
    {
        var result = '';
        if (length === undefined)
        {
            length = this.blockList.length - index;
        }
        for(var i = 0; i < length; i++ )
        {
            result += this.blockList[index+i].toString();
        }
        return this.addLineFeeds(result);
    };

    HTMLParser.prototype.reIndex = function(start, end)
    {
        start = start || 0;
        end = end || this.blockList.length;

        for(var i = start; i < end; i++)
        {
            this.blockList[i].documentOffset = i;
        }
    };

    HTMLParser.prototype.getChildren = function(offset)
    {
        var result = [];
        if (offset !== undefined || offset !== null)
        {
            var element = this.blockList[offset];
            var endTag = element.getClosingTag();
            var end = endTag.documentOffset;

            for(var i = offset+1; i < end; )
            {
                element = this.blockList[i];
                if (element instanceof AbstractElementBlock)
                {
                    result.push(element);
                }
                element = element.getClosingTag();
                i = element.documentOffset + 1;
            }
        }
        return result;
    };

    HTMLParser.prototype.getFirstElementChild = function(offset)
    {
        if (offset !== undefined || offset !== null)
        {
            var element = this.blockList[offset];
            var endTag = element.getClosingTag();
            var end = endTag.documentOffset;

            for(var i = offset+1; i < end; )
            {
                element = this.blockList[i];
                if (element instanceof AbstractElementBlock)
                {
                    return element;
                }
                endTag = element.getClosingTag();
                i = element.documentOffset + 1;
            }
        }
        return null;
    };

    HTMLParser.prototype.getNextElementSibling = function(offset)
    {
        if (offset)
        {
            var element = this.blockList[offset];
            var endTag = element.getClosingTag();
            offset = endTag.documentOffset+1;

            for(var i = offset; i < this.blockList.length; i++)
            {
                element = this.blockList[i];
                if (element instanceof AbstractElementBlock)
                {
                    return element;
                }
                else if (element instanceof ClosingElementBlock)
                {
                    break;
                }
            }
        }
        return null;
    };

    HTMLParser.prototype.getTextContent = function(offset, includeOuterHTML)
    {
        var result = "";
        if (offset)
        {
            var element = this.blockList[offset];
            var endTag = element.getClosingTag();
            var end = endTag.documentOffset;
            if (!includeOuterHTML)
            {
                offset++;
                end--;
            }
            return this.copy(offset, end - offset + 1);
        }
        return "";
    };

    HTMLParser.prototype.getElementByType = function(tagName, startIndex)
    {
        for(var i = startIndex || 0; i < this.blockList.length; i++)
        {
            var element = this.blockList[i];
            if (element.getName() === tagName && !(element instanceof ClosingElementBlock))
            {
                return element;
            }
        }
    };

    HTMLParser.prototype.removeEmptyAttributeStrings = function(srcDocument, meta)
    {
        for(var i = 0; i < this.blockList.length; i++ )
        {
            var element = this.blockList[i];
            if (element instanceof AbstractElementBlock)
            {
                for(var attrName in element.attributes)
                {
                    if (element.attributes.hasOwnProperty(attrName))
                    {
                        var attr = element.attributes[attrName];
                        if (attr && attr.getValue() === "")
                        {
                            if (meta && meta.isBooleanAttribute(element.getName(), attrName))
                            {
                                element.setAttribute(attrName, true);
                            }
                        }
                    }
                }
            }
        }
    };

    HTMLParser.prototype.createUniqueId = function(newId, forceNewId)
    {
        var i = 0;
        var id = newId;
        var currentIndex = newId.match(/_\d+$/);
        if (currentIndex)
        {
            currentIndex = currentIndex[0];
            newId = newId.substring(0, newId.length - currentIndex.length);
            i = +currentIndex.substring(1);

        }

        while(forceNewId || this.elementsById[id])
        {
            id = `${newId}_${++i}`;
            forceNewId = false;
        }

        return id;
    };

    HTMLParser.prototype.renameElement = function(element, newId, oldId)
    {
        if (oldId)
        {
            this.elementsById[oldId] = undefined;
        }
        newId = this.createUniqueId(newId);
        this.elementsById[newId] = element;
        if (newId !== oldId)
        {
            element.setAttribute('id', newId);
            element._id = newId;

            if (oldId && oldId !== newId) // could be equal after element rename due, because user keeps try to set it to something that is taken.
            {
                var find = new RegExp('#' + oldId + '\\b', 'g');
                var replace = '#' + newId;

                // rename all styles in all style tags, not just the one edited by the editor.
                var style = this.getElementByType('style');
                while(style)
                {
                    style.renameAllQualifiers(find, replace);
                    style = this.getElementByType('style', style.getDocumentPos()+1);
                }

                var oldStylesheet = this.stylesheetById['#' + oldId];
                if (oldStylesheet)
                {
                    this.stylesheetById[replace] = oldStylesheet;
                    this.stylesheetById['#' + oldId] = undefined;
                }

                // rename all references in binding expressions
                var regex = new RegExp('((^|[^\\w\\$\\.])(\\$|widget)\\.)' + oldId + '\\.', 'gm');
                var replaceCallback = function(match, g1)
                {
                    return g1 + newId + '.';
                };

                for(var i = 0; i < this.blockList.length; i++ )
                {
                    renameWidgetInBindingExpressions(this.blockList[i]._bindings, regex, replaceCallback);
                }
            }
        }
        return newId;
    };

    var findStylesheetByName = function(parser, name)
    {
        var stylesheet = parser.getElementByType('style');

        while(stylesheet)
        {
            var rules = stylesheet.getRules();
            for(var i = 0; i < rules.length; i++ )
            {
                var rule = rules[i];
                if (rule.getName() === name)
                {
                    return stylesheet;
                }
            }
            stylesheet = parser.getElementByType('style', stylesheet.getDocumentPos()+1);
        }
    };

    HTMLParser.prototype.catelogAllStylesheets = function()
    {
        var stylesheet = this.getElementByType('style');
        this.styleRules = stylesheet || new StyleElement("<style>", [], "</style>");
        this.stylesheetById = {};

        while(stylesheet)
        {
            this.styleRules = stylesheet;  // use the last style section as the place to add new rules.

            var rules = stylesheet.getRules();
            for(var i = 0; i < rules.length; i++ )
            {
                // TODO: warn about multiple style rules for #id in the document.
                var rule = rules[i];
                this.stylesheetById[rule.getName()] = stylesheet;
            }
            stylesheet = this.getElementByType('style', stylesheet.getDocumentPos()+1);
        }
    };

    HTMLParser.prototype.getStyleByName = function(id, styleName)
    {
        id = '#' + id;
        var stylesheet = this.stylesheetById[id];
        var rule = stylesheet && stylesheet.getRuleByName(id);
        return rule && rule.getStyleByName(styleName);
    };

    HTMLParser.prototype.setStyleByName = function(id, styleName, value)
    {
        id = '#' + id;
        var stylesheet = this.stylesheetById[id];
        var rule = stylesheet && stylesheet.getRuleByName(id);
        if (!rule && value)
        {
            rule = new StyleRule('\n' + id + ' {\n}');
            this.styleRules.insertRule(rule);
            this.stylesheetById[id] = this.styleRules;
        }
        if (rule)
        {
            rule.setStyleByName(styleName, value);
        }
    };

    HTMLParser.prototype.getStylesForElement = function(id)
    {
        var styles;
        if (id)
        {
            id = '#' + id;
            var stylesheet = this.stylesheetById[id];
            var rule = stylesheet && stylesheet.getRuleByName(id);
            styles = rule && rule.getStyleContent().replace(matchWhiteSpaceRegExpr, ' ').trim();
        }
        return styles || '';
    };

    HTMLParser.prototype.setStylesForElement = function(id, styles)
    {
        // insert line breaks back into styles
        styles = styles.replace(/;\s?/g, ';\n');

        id = '#' + id;
        var stylesheet = this.stylesheetById[id];
        var rule = stylesheet && stylesheet.getRuleByName(id);
        stylesheet = stylesheet || this.styleRules;
        var newRule = new StyleRule('\n' + id + ' {\n' + styles + '}');
        newRule.applyIndentation(BLOCK_INDENT + stylesheet.getIndent());
        var beforeIndex;

        if (rule)
        {
            // replace rule with new one
            beforeIndex = stylesheet.removeRule(rule);
        }
        stylesheet.insertRule(newRule, beforeIndex);
        this.stylesheetById[id] = stylesheet;
    };

    HTMLParser.prototype.compressStylesInline = function(srcDocument)
    {
        // merge them with any inline styles the user may have set
        for(var i = this.blockList.length; i-- > 0; )
        {
            var element = this.blockList[i];
            if (element instanceof AbstractElementBlock)
            {
                var cssStyles = srcDocument.getStylesForElement(element.id);
                if (cssStyles && cssStyles !== '')
                {
                    var inlineStyles = element.getAttribute('style');
                    if (inlineStyles && inlineStyles !== '')
                    {
                        cssStyles = inlineStyles + ' ' + cssStyles;
                    }
                    element.setAttribute('style', cssStyles);
                }
            }
        }
    };

    HTMLParser.prototype.expandInlineStyles = function(srcDocument)
    {
        for(var i = this.blockList.length; i-- > 0; )
        {
            var element = this.blockList[i];
            if (element instanceof AbstractElementBlock)
            {
                var id = element.id;
                var inlineStyles = element.getAttribute('style');
                if (inlineStyles && id)
                {
                    srcDocument.setStylesForElement(id, inlineStyles);
                    element.setAttribute('style');
                }
            }
        }
    };

    HTMLParser.prototype.compressBindingsInline = function(srcDocument)
    {
        for(var i = this.blockList.length; i-- > 0; )
        {
            var element = this.blockList[i];
            if (element.compressBindingsInline)
            {
                var id = element.id;
                if (id)
                {
                    var srcElement = srcDocument ? srcDocument.elementsById[id] : element;
                    if (srcElement)
                    {
                        element.compressBindingsInline(srcElement);
                    }
                }
            }
        }
    };

    HTMLParser.prototype.expandInlineBindings = function(srcDocument)
    {
        for(var i = this.blockList.length; i-- > 0; )
        {
            var element = this.blockList[i];
            if (element.expandInlineBindings)
            {
                var id = element.id;
                if (id)
                {
                    var srcElement = srcDocument ? srcDocument.elementsById[id] : element;
                    if (srcElement)
                    {
                        element.expandInlineBindings(srcElement);
                    }
                }
            }
        }
    };

    var createNewId = function(element)
    {
        var id = element.id;
        // only create new Id's for components, don't do it for div's, spans, a, etc...
        if (element.localName.indexOf('-') > 0)
        {
            id = element.localName.split('-').pop();
        }
        return id;
    };

    HTMLParser.prototype.createUniqueIds = function(srcDocument)
    {
        for(var i = 0; i < this.blockList.length; i++ )
        {
            var element = this.blockList[i];
            if (element instanceof AbstractElementBlock)
            {
                var oldId = element.id;
                var newId = oldId || createNewId(element);
                if (newId && newId !== '')
                {
                    newId = srcDocument.createUniqueId(newId);
                    if (newId !== oldId)
                    {
                        // widget requires rename, make sure we don't rename it to something in this document
                        while(this.elementsById[newId])
                        {
                            newId = srcDocument.createUniqueId(newId, true);
                        }
                        this.renameElement(element, newId, oldId);
                    }
                    // register newId's immediately so further elements do not use the same name.
                    srcDocument.elementsById[newId] = element;
                }
            }
        }
    };

    HTMLParser.prototype.getParentContainer = function(childPos)
    {
        for(var i = childPos; i-- > 0; )
        {
            var tag = this.blockList[i];
            var parent = tag.getClosingTag();
            if (parent.getDocumentPos() > childPos)
            {
                return tag;
            }
        }
        return undefined;
    };

    HTMLParser.prototype.cutStyles = function(id)
    {
        if (id)
        {
            id = '#' + id;
            var stylesheet = this.stylesheetById[id];
            var rule = stylesheet && stylesheet.getRuleByName(id);
            if (rule)
            {
                var result =
                {
                    index: stylesheet.removeRule(rule),
                    rule: rule,
                    stylesheet: stylesheet
                };
                this.stylesheetById[id] = findStylesheetByName(this, id);
                return result;
            }
        }
    };

    HTMLParser.prototype.pasteStyles = function(id, styles)
    {
        if (id && styles)
        {
            id = '#' + id;
            if (styles.rule.getName() !== id)
            {
                throw "Programmer Error: pasting style rule for the wrong id";
            }
            styles.stylesheet.insertRule(styles.rule, styles.index);
            this.stylesheetById[id] = styles.stylesheet;
        }
    };

    HTMLParser.prototype.getAllBindings = function()
    {
        var result = [];
        for(var i = 0; i < this.blockList.length; i++ )
        {
            var element = this.blockList[i];
            if (element.getAllBindings)
            {
                var bindings = element.getAllBindings();
                if (bindings.length > 0)
                {
                    result.push.apply(result, bindings);
                }
            }
        }
        return result;
    };

    var simpleBindExpressionRegExpr = /^[0-9a-zA-Z_#$\.\[\]\(\)]+$/;

    HTMLParser.prototype.setAllBindings = function(bindings, useMustacheNotation = false)
    {
        for(var i = 0; i < this.blockList.length; i++ )
        {
            var element = this.blockList[i];
            if (element.setBinding)
            {
                var id = element.id;
                if (id)
                {
                    for(var j = bindings.length; j-- > 0; )
                    {
                        var binding = bindings[j];
                        if (binding.widgetId === element.id && binding.propertyName)
                        {
                            var bindingExpression = binding.serverBindName;
                            if (bindingExpression)
                            {
                                if (bindingExpression.indexOf('widget.') === 0)
                                {
                                    bindingExpression = '$.' + bindingExpression.substring('widget.'.length);
                                }
                                else if (bindingExpression.indexOf('prop.') !== 0 && bindingExpression.indexOf('$.') !== 0 &&
                                    bindingExpression.match(simpleBindExpressionRegExpr))
                                {
                                    bindingExpression = '$.' + bindingExpression;
                                }
                                element.setBinding(binding.propertyName, bindingExpression);
                            }
                        }
                    }
                    if (useMustacheNotation)
                    {
                        // compress bindings into attributes (inplace)
                        element.compressBindingsInline(element, true);
                    }
                }
            }
        }
    };

    HTMLParser.prototype.extractAllTemplateBindings = function()
    {
        var result = [];
        for(var i = 0; i < this.blockList.length; i++ )
        {
            var element = this.blockList[i];
            if (element.extractAllTemplateBindings)
            {
                var bindings = element.extractAllTemplateBindings();
                if (bindings.length > 0)
                {
                    result.push.apply(result, bindings);
                }
            }
        }
        return result;
    };

    HTMLParser.prototype.getTextPosition = function(element, startingIndex)
    {
        var lineNo           = 0;
        var columnNo         = 0;
        var foundStartOfLine = false;
        var segments, lineCount;

        var endIndex = startingIndex || 0;
        for (var i = element.getDocumentPos(); i-- > endIndex; )
        {
            // don't include leading whitespace from starting index (if there was one).
            var text = i === startingIndex ? this.blockList[i].getText() : this.blockList[i].toString();
            segments = text.split('\n');
            lineCount = segments.length - 1;
            if (!foundStartOfLine)
            {
                columnNo += segments[lineCount].length;
                foundStartOfLine = lineCount > 0;
            }
            lineNo += lineCount;
        }

        // adjust for leading white space
        segments = element.leadingWhiteSpace.split('\n');
        lineCount = segments.length - 1;
        if (lineCount > 0)
        {
            columnNo = segments[lineCount].length;
            lineNo += lineCount;
        }
        else
        {
            columnNo += segments[lineCount].length;
        }

        return {row: lineNo, column: columnNo};
    };

    HTMLParser.prototype.getLineNumber = function(element, startingIndex)
    {
        return this.getTextPosition(element, startingIndex).row + 1;
    };

    HTMLParser.prototype.getAnnotations = function()
    {
        var annotations = [];
        var prevAnnotation, prevIndex = 0;
        for(var i = 0; i < this.blockList.length; i++ )
        {
            var element = this.blockList[i];
            var annotation = element.getAnnotation();
            if (annotation)
            {
                var position = this.getTextPosition(element, prevIndex);
                annotation.row = position.row + element.getErrorLineOffset();
                annotation.column = position.column;
                if (prevAnnotation)
                {
                    if (annotation.row === 0)
                    {
                        annotation.column += prevAnnotation.column;
                    }
                    else
                    {
                        annotation.row += prevAnnotation.row;
                    }
                }
                prevAnnotation = annotation;
                prevIndex = i;
                annotations.push(annotation);
            }
        }
        return annotations;
    };
    // #endregion

    // #region HTMLDomEditor
    var HTMLDomEditor = function(text, metaVersion)
    {
        this.parser = new HTMLParser(text, undefined, metaVersion);
    };

    HTMLDomEditor.prototype = new gc.designer.editor.AbstractDom();

    HTMLDomEditor.prototype.getRoot = function()
    {
        var result = this.parser.elementsById['editorRoot'];
        if (!result)
        {
            var templateNode = this.parser.getElementByType('template');
            if (templateNode && templateNode.getAttribute('is') === 'dom-bind')
            {
                result = templateNode;
            }
        }
        return result || this.parser.getElementByType('body') || gc.designer.editor.AbstractDom.prototype.getRoot.call(this);
    };

    HTMLDomEditor.prototype.getFirstStylesheet = function()
    {
        return this.parser.getElementByType('style');
    };

    HTMLDomEditor.prototype.getNextStylesheet = function(stylesheet)
    {
        return this.parser.getElementByType('style', stylesheet.getDocumentPos()+1);
    };

    HTMLDomEditor.prototype.getParentContainer = function(element)
    {
        return this.parser.getParentContainer(element.getDocumentPos());
    };

    HTMLDomEditor.prototype.updateImportLinks = function(dependencies, purge)
    {
        return this.parser.updateImportLinks(dependencies, purge);
    };

    HTMLDomEditor.prototype.getMissingImportLinks = function(dependencies)
    {
        return this.parser.updateImportLinks(dependencies, false, true);
    };

    HTMLDomEditor.prototype.getAllBindings = function()
    {
        return this.parser.getAllBindings();
    };

    HTMLDomEditor.prototype.setAllBindings = function(bindings, useMustacheNotation = false)
    {
        return this.parser.setAllBindings(bindings, useMustacheNotation);
    };

    HTMLDomEditor.prototype.extractAllTemplateBindings = function()
    {
        return this.parser.extractAllTemplateBindings();
    };

    HTMLDomEditor.prototype.getAnnotations = function()
    {
        return this.parser.getAnnotations();
    };

    HTMLDomEditor.prototype.getTheme = function()
    {
        var themeWidget = this.parser.getElementByType('ti-widget-theme');
        if (themeWidget) {
            return themeWidget.getProperty('theme');

        } else {
            var body = this.parser.getElementByType('body');
            var className = body && body.getClass();
            return className && className.trim();
        }
    };

    HTMLDomEditor.prototype.setTheme = function(theme)
    {
        var themeWidget = this.parser.getElementByType('ti-widget-theme');
        if (themeWidget) {
            themeWidget.setProperty('theme', theme);

        } else {
            var body = this.parser.getElementByType('body');
            if (body)
            {
                body.setClass(theme);
            }
        }
    };

    HTMLDomEditor.prototype.getText = function(forDesigner)
    {
        try
        {
            gAutoGenerateIds = forDesigner ? true : false;

            return this.parser.getText();
        }
        finally
        {
            gAutoGenerateIds = false;
        }
    };

    Object.defineProperty(HTMLDomEditor.prototype, 'html',
    {
        get: function()
        {
            return this.parser.getElementByType('html');
        }
    });

    gc.designer.editor.htmlParserFactory =
    {
        create: function(text, metaVersion)
        {
            return new HTMLDomEditor(text, metaVersion);
        }
    };

    window.gc = window.gc || {};
    window.gc.htmlParserFactory = gc.designer.editor.htmlParserFactory;
    // #endregion

}());

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
class TemplateBinder {
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

/**
 *  Copyright (c) 2021, Texas Instruments Incorporated
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
const console$1 = new GcConsole('GcWebComponentHelper');
const camelToDashCase = GcUtils.camelToDashCase;
const dashToCamelCase = GcUtils.dashToCamelCase;
/**
 * Returns the module path.
 *
 * @example
 *      getModulePath(import.meta);
 *
 * @param importMeta the import meta
 */
const getModulePath = (importMeta) => {
    return importMeta?.url?.split('/').slice(0, -1).join('/');
};
/**
 * `GcWebComponentHelper` provides an abstract implementation of the standard WebComponent implementation.
 *
 * @example
 *      const helper = new GcWebComponentHelper(htmlElement, ID, MODULE_PATH);
 *      helper.templateHtmlFile = './template.html';
 *      helper.cssFile = './styles.css';
 *      helper.defineProperty({ name: 'on', type: 'boolean' });
 *      helper.bindProperty('on', 'checkbox', 'checked');
 *      helper.init();
 */
class GcWebComponentHelper {
    constructor(htmlElement, componentName, modulePath) {
        this.htmlElement = htmlElement;
        this.componentName = componentName;
        this.modulePath = modulePath;
        this.properties = [];
        this.bindings = [];
        this.propWatchers = [];
        this.setProperties();
    }
    /**
     * Sets the inline template string. This property will have a high priority than `templateHtmlFile` and `cssFile`.
     */
    set template(value) {
        this.templateStr = value;
    }
    /**
     * Sets the template html filepath.
     */
    set templateHtmlFile(value) {
        this.templateHtmlFilePath = value;
    }
    /**
     * Sets the css filepath.
     */
    set cssFile(value) {
        this.cssFilePath = value;
    }
    /**
     * Defines a property.
     *
     * @param property the property
     */
    defineProperty(property) {
        this.properties.push(property);
    }
    /**
     * Creates a binding for this element and the shadow root element.
     *
     * @param hostProp the html host element property
     * @param shadowElId the shadow element id
     * @param shadowElProp the shadow element property
     * @param oneWay if true, data only flows in one direction, from host to shadow element.
     */
    bindProperty(hostProp, shadowElId, shadowElProp, oneWay = false) {
        const binding = {
            serverBindName: hostProp,
            widgetId: shadowElId,
            propertyName: shadowElProp,
            options: {
                oneWay: oneWay
            }
        };
        if (!this.templateBindingModel) {
            this.bindings.push(binding);
        }
        else {
            TemplateBinder.createBindings(this.templateBindingModel, [binding], console$1);
        }
    }
    /**
     * Adds a property change watcher.
     *
     * @param prop the property to watch
     * @param listener the change listener
     */
    watch(prop, listener) {
        this.propWatchers.push({ prop: prop, listener: listener });
    }
    /**
     * Initialize the WebComponent.  This includes creating shadow dom elements from the provided template,
     * creating bindings defined with bindProperty() and from mustache notation within the template, and
     * initializing properties values from the web components attributes.
     */
    async init() {
        this.addPropertyAssessors();
        this.setValuesFromAttributes();
        /* create templated element */
        const htmlFilePath = this.templateHtmlFilePath ? `${this.modulePath}/${this.templateHtmlFilePath}` : undefined;
        const template = await TemplateBinder.getInstance(this.componentName, this.templateStr, htmlFilePath);
        /* create shadow root */
        const shadowRoot = this.htmlElement.attachShadow({ mode: 'open' });
        this.templateBindingModel = template.stampTemplate(shadowRoot, this, console$1, this.bindings);
        this.bindings.splice(0, this.bindings.length);
        /* create external css link */
        if (this.cssFilePath) {
            const cssLinkElm = document.createElement('link');
            cssLinkElm.setAttribute('rel', 'stylesheet');
            cssLinkElm.setAttribute('href', `${this.modulePath}/${this.cssFilePath}`);
            shadowRoot.appendChild(cssLinkElm);
        }
    }
    setProperties() {
        /* get defined properties from html element */
        // @ts-ignore
        const properties = this.htmlElement.constructor.properties;
        if (properties) {
            for (const prop in properties) {
                if (Object.prototype.hasOwnProperty.call(properties, prop)) {
                    const property = {
                        name: prop,
                        type: properties[prop].type,
                    };
                    if (properties[prop].value)
                        property.value = properties[prop].value;
                    if (properties[prop].notify)
                        property.notify = properties[prop].notify;
                    if (properties[prop].readonly)
                        property.readonly = properties[prop].readonly;
                    if (properties[prop].reflect)
                        property.reflect = properties[prop].reflect;
                    this.defineProperty(property);
                }
            }
        }
    }
    /**
     * Method to retrieve property information defined through defineProperty()
     *
     * @param name the name of the property to retrieve info for.
     * @returns the IProperty object for the desired property.
     */
    getProperty(name) {
        return this.properties.find(property => name === property.name);
    }
    /**
     * Method to set a property's value.  Use this for setting read-only properties, because
     * using this.<propertyName> = <newValue> will not work for this case.
     *
     * @param property the reference to the property to set the value for.
     * @param value new value for the property.
     */
    setValue(property, value) {
        this.updatePropertyValue(property, value, true);
    }
    addPropertyAssessors() {
        /* add observed attributes getter */
        const attributes = this.properties.map(property => property.name);
        const attributeObserver = new MutationObserver(mutations => {
            mutations.forEach(mutation => {
                if (mutation.type === 'attributes' && mutation.attributeName) {
                    this.onAttributeChanged(mutation.attributeName, mutation.target.getAttribute(mutation.attributeName));
                }
            });
        });
        attributeObserver.observe(this.htmlElement, {
            attributes: true,
            attributeFilter: attributes
        });
        /* define getter and setter for each property */
        // eslint-disable-next-line @typescript-eslint/no-this-alias
        const self = this;
        for (const property of this.properties) {
            Object.defineProperty(this.htmlElement, property.name, {
                get() {
                    return property.value;
                },
                set(value) {
                    self.updatePropertyValue(property, value);
                }
            });
        }
    }
    setValuesFromAttributes() {
        for (const prop of this.properties) {
            // eslint-disable-next-line @typescript-eslint/no-explicit-any
            let value = prop.value;
            for (let i = this.htmlElement.attributes.length - 1; i >= 0; --i) {
                const attr = this.htmlElement.attributes.item(i)?.name;
                if (attr === camelToDashCase(prop.name)) {
                    value = this.htmlElement.getAttribute(attr);
                    break;
                }
            }
            this.updatePropertyValue(prop, value, true);
        }
    }
    /**
     * Retrieves elements in this components shadow dom by id.
     *
     * @param id the id of the element to find.
     * @returns the shadow dom element or undefined if the element is not found.
     */
    getElement(id) {
        return id === 'this' ? this.htmlElement : this.htmlElement.shadowRoot?.getElementById(id);
    }
    onAttributeChanged(name, value) {
        for (const property of this.properties) {
            if (property.name === dashToCamelCase(name)) {
                // make sure we pass a true value for an empty string and a boolean type.  In all other cases,
                // the string will be converted properly by updatePropertyValue.
                this.updatePropertyValue(property, (property.type === 'boolean' && value === '') ? true : value);
                break;
            }
        }
    }
    setPropertyValue(property, value) {
        if (value === undefined || typeof value === property.type) {
            property.value = value;
        }
        else
            switch (property.type) {
                case 'number':
                    property.value = +value;
                    break;
                case 'boolean':
                    property.value = value === 'false' ? false : Boolean(value);
                    break;
                case 'string':
                    property.value = String(value);
                    break;
            }
    }
    updatePropertyValue(property, value, internal = false) {
        if (!property.readonly || internal) {
            const oldValue = property.value;
            this.setPropertyValue(property, value);
            /*
             * perform updates:
             *  1) attribute
             *  2) fire change events
             */
            if (oldValue !== property.value) {
                /* update attribute */
                if (property.reflect) {
                    const attrName = camelToDashCase(property.name);
                    if (property.type === 'boolean') {
                        if (property.value !== this.htmlElement.hasAttribute(attrName)) {
                            if (property.value) {
                                this.htmlElement.setAttribute(attrName, '');
                            }
                            else {
                                this.htmlElement.removeAttribute(attrName);
                            }
                        }
                    }
                    else {
                        const attrValue = value?.toString() || null;
                        if (this.htmlElement.getAttribute(attrName) !== attrValue) {
                            if (attrValue !== null) {
                                this.htmlElement.setAttribute(attrName, attrValue);
                            }
                            else {
                                this.htmlElement.removeAttribute(attrName);
                            }
                        }
                    }
                }
                /* fire change event */
                if (property.notify) {
                    if (internal || property.notify) {
                        console$1.debug(`Firing ${property.name}-changed event, value=${property.value}`);
                        this.htmlElement.dispatchEvent(new CustomEvent(`${property.name}-changed`, { detail: { value: property.value } }));
                    }
                    for (const watcher of this.propWatchers) {
                        if (watcher.prop === property.name) {
                            console$1.debug(`Notifying watchers '${property.name}' property changed, value=${property.value}`);
                            watcher.listener(property.value, oldValue);
                        }
                    }
                }
            }
        }
    }
}

export { GcWebComponentHelper, getModulePath };
//# sourceMappingURL=GcWebComponentHelper.js.map
