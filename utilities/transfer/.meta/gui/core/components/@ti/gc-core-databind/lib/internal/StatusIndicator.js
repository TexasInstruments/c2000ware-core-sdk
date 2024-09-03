/**
 * Copyright (c) 2021, Texas Instruments Incorporated
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
import { GcUtils } from '../../../gc-core-assets/lib/GcUtils';
import { GcConsole } from '../../../gc-core-assets/lib/GcConsole';
import { StatusType } from './Status';
import { NAME } from './IBind';
class StatusIndicator {
    constructor(targetWidget, locationHint) {
        this.targetWidget = targetWidget;
        this.locationHint = locationHint;
        this.messages = [];
    }
    addVisibilityListener() {
        this.visibilityObserver = new ResizeObserver(() => {
            if (this.statusWidget) {
                this.statusWidget.setAttribute('style', this.getIndicatorStyles().divStyle);
            }
        });
        this.visibilityObserver.observe(this.targetWidget);
    }
    removeVisibilityListener() {
        if (this.visibilityObserver) {
            this.visibilityObserver.disconnect();
            this.visibilityObserver = undefined;
        }
    }
    createStatusWidget(message, type) {
        const parentElem = this.targetWidget.parentElement;
        if (!parentElem) {
            return;
        }
        const styles = this.getIndicatorStyles();
        const div = document.createElement('div');
        div.setAttribute('style', styles.divStyle);
        // eslint-disable-next-line @typescript-eslint/no-explicit-any
        const img = document.createElement('gc-widget-icon');
        img.src = StatusIndicator.getStatusIndicatorIcon(type);
        img.setAttribute('style', styles.imgStyle);
        img.setAttribute('tooltip', message);
        img.setAttribute('icon', StatusIndicator.getStatusIndicatorIcon(type));
        img.setAttribute('size', 'xs');
        img.setAttribute('appearance', StatusIndicator.getIconAppearance(type));
        div.appendChild(img);
        if (!GcUtils.isInDesigner) { // TODO: eventually we want all bindings to work in designer, and show errors before we run.
            parentElem.insertBefore(div, this.targetWidget);
        }
        return div;
    }
    addMessage(message, type) {
        type = type || StatusType.ERROR;
        this.removeMessage(message, true);
        this.messages.push({ message, type });
        if (this.statusWidget) {
            this.updateStatusIndication();
        }
        else {
            this.statusWidget = this.createStatusWidget(message, type);
            if (this.statusWidget) {
                this.addVisibilityListener();
            }
        }
    }
    updateStatusIndication() {
        if (!this.statusWidget) {
            return;
        }
        const nextMessage = this.getStatusMessage();
        if (nextMessage) {
            const img = this.statusWidget.children[0];
            if (img && img.title !== nextMessage.message) {
                // update the status text with new message.
                img.title = nextMessage.message;
                const iconLocation = StatusIndicator.getStatusIndicatorIcon(nextMessage.type);
                if (img.src.indexOf(iconLocation) < 0) {
                    img.src = iconLocation;
                }
            }
        }
        else {
            // no more status messages, so lets get rid or the
            // status indicator widget.
            const parentElem = this.statusWidget && this.statusWidget.parentElement;
            if (parentElem) {
                parentElem.removeChild(this.statusWidget);
            }
            this.removeVisibilityListener();
            this.statusWidget = undefined;
        }
    }
    getStatusMessage() {
        if (this.messages.length === 0) {
            return;
        }
        return this.messages.reduce((result, item) => {
            return item.type <= result.type ? item : result;
        }, this.messages[0]);
    }
    removeMessage(oldMessage, preventUpdate = false) {
        if (!oldMessage) {
            return;
        }
        this.messages = this.messages.filter(item => item.message !== oldMessage);
        if (!preventUpdate) {
            this.updateStatusIndication();
        }
    }
    static getRelativeIndicatorPosition(rect, hint) {
        hint = hint || 'middle-left';
        let divStyle = '';
        let imgStyle = '';
        let edge = false;
        let fields = hint.split('-');
        if (fields.length !== 2) {
            fields = [
                'middle', 'left'
            ];
        }
        for (let i = 0; i < 2; i++) {
            switch (fields[i].trim().toLowerCase()) {
                // horizontal positions
                case 'left':
                    divStyle += 'left: ' + rect.left + 'px; ';
                    imgStyle += (edge ? 'left: 0px; ' : 'right: 0px; ');
                    edge = true;
                    break;
                case 'right':
                    divStyle += 'left: ' + rect.right + 'px; ';
                    imgStyle += (edge ? 'right :0px;' : 'left :0px; ');
                    edge = true;
                    break;
                case 'center':
                    divStyle += 'left: ' + (rect.left + rect.right) / 2 + 'px; ';
                    imgStyle += 'left: -7px; ';
                    break;
                // vertical positions
                case 'top':
                    divStyle += 'top: ' + rect.top + 'px; ';
                    imgStyle += (edge ? 'top: 0px; ' : 'bottom: 0px; ');
                    edge = true;
                    break;
                case 'bottom':
                    divStyle += 'top: ' + rect.bottom + 'px; ';
                    imgStyle += (edge ? 'bottom: 0px;' : 'top: 0px; ');
                    edge = true;
                    break;
                case 'middle':
                    divStyle += 'top: ' + (rect.top + rect.bottom) / 2 + 'px; ';
                    imgStyle += 'top: -7px; ';
                    break;
                default:
                    GcConsole.error(NAME, `Invalid position found in status indicator location hint = ${hint}`);
                    break;
            }
        }
        return ({
            divStyle: divStyle,
            imgStyle: imgStyle
        });
    }
    getIndicatorStyles() {
        const elemStyle = getComputedStyle(this.targetWidget);
        const positionStyle = elemStyle.position;
        const visibilityStyle = (elemStyle.display === 'none' || elemStyle.visibility === 'hidden') ? 'hidden' : 'visible';
        let styles = null;
        if (positionStyle === 'absolute') {
            // calculate relative size and position in pixels w.r.t parent
            // element.
            const elemRect = {
                left: this.targetWidget.offsetLeft,
                right: this.targetWidget.clientWidth + this.targetWidget.offsetLeft,
                top: this.targetWidget.offsetTop,
                bottom: this.targetWidget.clientHeight + this.targetWidget.offsetTop
            };
            // set styles including position
            styles = StatusIndicator.getRelativeIndicatorPosition(elemRect, this.locationHint);
            styles.divStyle = 'position: absolute; ' + styles.divStyle;
        }
        else if (positionStyle === 'static' || positionStyle === 'relative') {
            styles = {
                divStyle: 'position: relative;',
                imgStyle: 'left: 0px; top: 0px;'
            };
        }
        else { // 'fixed'
            styles = StatusIndicator.getRelativeIndicatorPosition(this.targetWidget.getBoundingClientRect(), this.locationHint);
            styles.divStyle = 'position: fixed; ' + styles.divStyle;
        }
        return {
            divStyle: `${styles.divStyle} overflow: visible; display: inline-block; background-color: var(--theme-background-color, white) visibility: ${visibilityStyle}`,
            imgStyle: `position: absolute; margin: 0; z-index:275; ${styles.imgStyle} background-color: inherit; border-radius: 10px`
        };
    }
    static getStatusIndicatorIcon(type) {
        switch (type) {
            case StatusType.ERROR: return 'navigation:cancel';
            case StatusType.WARNING: return 'alert:error';
            default:
                return 'action:info';
        }
    }
    static getIconAppearance(type) {
        switch (type) {
            case StatusType.ERROR: return 'error';
            case StatusType.WARNING: return 'warn';
            default:
                return '';
        }
    }
}
/**
 * Factory used to retrieve status indicators for a given widget.
 */
export class StatusIndicatorFactory {
    /**
     * Factory method to create/retrieve status indicators for a particular widget The widget
     *
     * @param widget - the the widget to get a status indicator for.
     * @return the status indicator created for this widget, or null if no widget found.
     */
    static get(widget) {
        let statusIndicator = this.activeStatusIndicators.get(widget.id);
        if (statusIndicator === undefined) {
            if (widget) {
                const customHintLocation = widget._statusIndicatorLocationHint;
                const locationHint = typeof customHintLocation === 'function' ? customHintLocation() : customHintLocation;
                statusIndicator = new StatusIndicator(widget, locationHint);
                this.activeStatusIndicators.set(widget.id, statusIndicator);
            }
        }
        else {
            // update target widget in case it has changed, and we need to
            // create a new statusWidget
            statusIndicator.targetWidget = widget;
        }
        return statusIndicator;
    }
}
StatusIndicatorFactory.activeStatusIndicators = new Map();
//# sourceMappingURL=StatusIndicator.js.map