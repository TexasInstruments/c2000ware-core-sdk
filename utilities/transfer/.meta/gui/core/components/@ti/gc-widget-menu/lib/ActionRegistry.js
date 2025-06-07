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
 */
const console = new GcConsole('ActionRegistry');
const registry = {};
window.addEventListener('gc-command-run', ((ev) => {
    try {
        registry[ev.detail.id]?.run({ id: ev.detail.id });
        window.dispatchEvent(new CustomEvent('gc-command-update', { detail: { id: ev.detail.id } }));
    }
    catch (e) {
        console.error(`Failed to execute action run() method for id="${ev.detail.id}" (${e.toString()})`);
    }
}));
class ActionRegistry {
    static registerAction(id, runnable) {
        if (registry[id]) {
            console.error(`Action ${id} is already registered.`);
            return;
        }
        registry[id] = runnable;
        window.dispatchEvent(new CustomEvent('gc-command-update', { detail: { id: id } }));
    }
    static unregisterAction(id) {
        delete registry[id];
    }
    static registerActionGroup(ids, runnable) {
        ids.forEach(id => {
            ActionRegistry.registerAction(id, {
                run(detail) {
                    runnable.run(detail);
                },
                isEnabled() {
                    return runnable?.isEnabled ? runnable.isEnabled(id) : true;
                },
                isVisible() {
                    return runnable?.isVisible ? runnable.isVisible(id) : true;
                },
                isChecked() {
                    return runnable?.isChecked ? runnable.isChecked(id) : true;
                }
            });
        });
    }
    static isEnabled(id) {
        const runnable = registry[id];
        if (!runnable) {
            return false;
        }
        return runnable?.isEnabled ? runnable.isEnabled() : true;
    }
    static isVisible(id) {
        const runnable = registry[id];
        if (!runnable) {
            return GcUtils.isInDesigner;
        }
        return runnable?.isVisible ? runnable.isVisible() : true;
    }
    static isChecked(id) {
        const runnable = registry[id];
        return runnable?.isChecked ? runnable.isChecked() : false;
    }
    static run(detail) {
        const runnable = registry[detail.id];
        if (runnable && this.isEnabled(detail.id) && this.isVisible(detail.id) && !GcUtils.isInDesigner) {
            runnable.run(detail);
        }
    }
}

export { ActionRegistry };
//# sourceMappingURL=ActionRegistry.js.map
