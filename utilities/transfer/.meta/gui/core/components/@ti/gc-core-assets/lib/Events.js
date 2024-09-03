import { GcConsole } from './GcConsole';

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
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 'AS IS'
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
const MODULE_NAME = 'Events';
const console = new GcConsole(MODULE_NAME);
class ListenerList {
    constructor() {
        this.listeners = new Array();
    }
    add(listener) {
        if (!this.listeners.includes(listener)) {
            this.listeners.push(listener);
        }
    }
    remove(listener) {
        if (listener) {
            this.listeners = this.listeners.filter((l) => listener !== l);
        }
    }
    fire(type, details) {
        this.listeners.forEach((listener) => {
            try {
                listener(details);
            }
            catch (e) {
                GcConsole.error(MODULE_NAME, e);
            }
        });
    }
    get isEmpty() {
        return this.listeners.length === 0;
    }
    forEach(callback) {
        this.listeners.forEach((listener) => {
            try {
                callback(listener);
            }
            catch (e) {
                console.error(e);
            }
        });
    }
}
class EventType {
    constructor(eventName) {
        this.eventName = eventName;
        this.id = Symbol(eventName);
    }
    asEventType(listener) {
        return listener;
    }
}
class Events {
    constructor() {
        // eslint-disable-next-line @typescript-eslint/no-explicit-any
        this.eventMap = new Map();
        this.firstAddedEventMap = new Map();
        this.lastRemovedEventMap = new Map();
    }
    hasAnyListeners(type) {
        const listeners = this.eventMap.get(type.id);
        return listeners ? !listeners.isEmpty : false;
    }
    addEventListener(type, listener) {
        const first = this.doAddEventListener(this.eventMap, type, listener);
        if (first) {
            this.doFireEvent(this.firstAddedEventMap, type, {});
        }
    }
    removeEventListener(type, listener) {
        const last = this.doRemoveEventListener(this.eventMap, type, listener);
        if (last) {
            this.doFireEvent(this.lastRemovedEventMap, type, {});
        }
    }
    fireEvent(type, details) {
        this.doFireEvent(this.eventMap, type, details);
    }
    // Helper functions
    addEventListenerOnFirstAdded(type, listener) {
        this.doAddEventListener(this.firstAddedEventMap, type, listener);
        // Automatically fire first listener added event if there are already listeners when added.
        const listeners = this.eventMap.get(type.id);
        if (listeners && !listeners.isEmpty) {
            listener({});
        }
    }
    removeEventListenerOnFirstAdded(type, listener) {
        this.doRemoveEventListener(this.firstAddedEventMap, type, listener);
    }
    addEventListenerOnLastRemoved(type, listener) {
        this.doAddEventListener(this.lastRemovedEventMap, type, listener);
    }
    removeEventListenerOnLastRemoved(type, listener) {
        this.doRemoveEventListener(this.lastRemovedEventMap, type, listener);
    }
    doAddEventListener(map, type, listener) {
        let listeners = map.get(type.id);
        if (!listeners) {
            listeners = new ListenerList();
            map.set(type.id, listeners);
        }
        const first = listeners.isEmpty;
        listeners.add(listener);
        return first;
    }
    doRemoveEventListener(map, type, listener) {
        const listeners = map.get(type.id);
        let last = false;
        if (listeners && !listeners.isEmpty) {
            listeners.remove(listener);
            last = listeners.isEmpty;
        }
        return last;
    }
    doFireEvent(map, type, details) {
        const listeners = map.get(type.id);
        if (listeners) {
            listeners.fire(type, details);
        }
    }
    forEachEventListener(type, callback) {
        const listeners = this.eventMap.get(type.id);
        if (listeners) {
            listeners.forEach(callback);
        }
    }
}

export { EventType, Events };
//# sourceMappingURL=Events.js.map
