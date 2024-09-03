import { GcUtils } from '../../gc-core-assets/lib/GcUtils';

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
const INFO_ICON = 'action:info';
const WARNING_ICON = 'alert:warning';
const ALERT_ICON = 'action:notification_important';
const ERROR_ICON = 'alert:error';
const MINIMUM_DURATION_BEFORE_AUTO_CLOSE = 1000; // 1 second minimum time to show progress before auto closing when complete.
/**
 * Creates a `gc-widget-message-dialog` and add it into the document.
 * @param heading dialog heading
 * @param message dialog message string, can be a HTML markup string
 * @param icon icon string
 * @param resolve the promise to resolve when the dialog is closed
 * @param hasCancel default false, if true includes dismiss button
 * @param hasOk default false, if true includes confirm button
 * @param customButtons optional list of custom buttons to add between cancel and ok buttons, if provided.
 * @return the message dialog
 */
const makeDialog = (heading, message, icon = '', resolve, hasCancel = false, hasOk = true, customButtons) => {
    const dialog = document.createElement('gc-widget-message-dialog');
    const messageDialog = dialog;
    messageDialog.heading = heading;
    messageDialog.message = message;
    messageDialog.hasCancel = hasCancel;
    messageDialog.hasOk = hasOk;
    messageDialog.customButtons = customButtons || '';
    messageDialog.icon = icon ?? undefined;
    document.body.appendChild(dialog);
    dialog.addEventListener('dialog-close', (e) => {
        const detail = e.detail;
        if (detail && detail.canClose && dialog.parentNode) {
            dialog.parentNode.removeChild(dialog);
            resolve(detail.closeReason);
        }
    });
    return messageDialog;
};
/**
 * `MessageDialog` is used to instantiate and attach to the document a `gc-message-dialog` in a specific styled format: alert, info, warning, error, progress and prompt.
 *
 *  On close, the dialog element detaches from the DOM.
 */
class GcMessageDialog {
    /**
     * Open an alert style dialog.
     *
     * @param message message content string.
     */
    static async alert(message) {
        await new Promise((resolve, reject) => {
            try {
                makeDialog('Alert', message, ALERT_ICON, resolve).open();
            }
            catch (error) {
                reject(error);
            }
        });
    }
    /**
     * Open an info style dialog.
     *
     * @param message message content string.
     */
    static async info(message) {
        await new Promise((resolve, reject) => {
            try {
                makeDialog('Info', message, INFO_ICON, resolve).open();
            }
            catch (error) {
                reject(error);
            }
        });
    }
    /**
     * Open a warning style dialog.
     *
     * @param message message content string.
     */
    static async warning(message) {
        await new Promise((resolve, reject) => {
            try {
                makeDialog('Warning', message, WARNING_ICON, resolve).open();
            }
            catch (error) {
                reject(error);
            }
        });
    }
    /**
     * Open an error style dialog.
     *
     * @param message message content string.
     */
    static async error(message) {
        await new Promise((resolve, reject) => {
            try {
                makeDialog('Error', message, ERROR_ICON, resolve).open();
            }
            catch (error) {
                reject(error);
            }
        });
    }
    /**
     * Open a prompt dialog with a choice to initialize a cancel button and a ok button.
     *
     * @param heading dialog title
     * @param message message string
     * @param icon icon string
     * @param hasCancel `true` to include CANCEL button
     * @param hasOK `true` to include OK button
     * @param customButtons optional list of custom buttons to add between cancel and ok buttons, if provided.
     * @return 'dismiss' for cancel, 'confirm' for ok, or the name of any custom button that was clicked to close the prompt.
     */
    static async prompt(heading, message, icon = '', hasCancel = true, hasOk = true, customButtons) {
        return new Promise((resolve, reject) => {
            try {
                makeDialog(heading || 'Prompt', message, icon, resolve, hasCancel, hasOk, customButtons).open();
            }
            catch (error) {
                reject(error);
            }
        });
    }
    /**
    * Open a progress dialog with a progressbar.
    *
    * Usage for progress dialog:
    *
    * ```
    * (async () => {
    *   const {progress, result} = await GcMessageDialog.progress('Backup', 'Uploading all files on your hard drive to somewhere in the cloud.');
    *   result.then(e => console.log(e));
    *
    *   let value = 0;
    *   const intervalHdlr = setInterval(() => {
    *      value += 1;
    *      progress.setValue(value);
    *      progress.setMessage(`Uploaded: ${value}%`);
    *      if (value >= 100) clearInterval(intervalHdlr);
    *
    *      // cancel progress
    *      // if (value === 40) {
    *      //     progress.cancel();
    *      //     clearInterval(intervalHdlr);
    *      // }
    *   }, 100);
    * })();
    * ```
    *
    * @param heading dialog title
    * @param message message content string.
    * @param icon icon string.
    * @param hasCancel `false` if the progress can not be cancel
    * @param minValue
    * @param maxValue
    * @param autoClose default true; close if the progressbar percentage is at 100%
    * @returns a promise that contains progress interface and the dialog result promise, the progress interface can be use to interact with the progress bar
    */
    static async progress(heading, message, icon = '', hasCancel = true, minValue = 0, maxValue = 100, autoClose = false) {
        let defResolve;
        const defer = new Promise(resolve => {
            defResolve = resolve;
        });
        return new Promise((resolve, reject) => {
            try {
                const messageDialog = makeDialog(heading, message, icon, defResolve, hasCancel, !autoClose);
                // init dialog properties
                messageDialog.minValue = minValue;
                messageDialog.maxValue = maxValue;
                messageDialog.hasProgress = true;
                messageDialog.disableCancelButton = !hasCancel;
                const startTime = autoClose ? new Date().getTime() : 0;
                const progress = {
                    setMessage: async function (message) {
                        messageDialog.setProgressMessage(message);
                    },
                    setValue: async function (value) {
                        await messageDialog.setProgressValue(value);
                        if (value >= maxValue) {
                            messageDialog.disableOKButton = false;
                            messageDialog.disableCancelButton = true;
                            if (autoClose) {
                                const extraTime = startTime + MINIMUM_DURATION_BEFORE_AUTO_CLOSE - new Date().getTime();
                                if (extraTime > 0) {
                                    await GcUtils.delay(extraTime);
                                }
                                await messageDialog.close('confirm');
                            }
                        }
                    },
                    cancel: async function () {
                        return messageDialog.close('dismiss');
                    }
                };
                messageDialog.open();
                resolve({ progress, result: defer });
            }
            catch (error) {
                reject(error);
            }
        });
    }
}
if (typeof window !== 'undefined') {
    window.gc = window.gc || {};
    window.gc.dialog = window.gc.dialog || GcMessageDialog;
}

export { GcMessageDialog };
//# sourceMappingURL=GcMessageDialog.js.map
