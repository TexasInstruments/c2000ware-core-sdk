/* eslint-disable @typescript-eslint/indent */
/* eslint-disable spaced-comment */
const RuntimeScriptURL = window.URL.createObjectURL(new Blob([
    `/****************************************************
* Synchronization Logic
***************************************************/
var box = this;
var Runtime = (function() {
    var buffer   = null;
    var lock     = null;
    var _timeout = 10000;
    var _command = null;

    box.onmessage = function(event) {
        var detail = event.data;
        switch (detail.cmd) {
            case 'init':
                lock   = new Int32Array(detail.lock);
                buffer = new Uint8Array(detail.buffer);
                break;

            case 'main':
                try {
                    main();
                } catch (err) {
                    box.postMessage({event: 'Console', detail: {message: err.toString(), type: 'error'}});
                }
                box.postMessage({event: 'MainCompleted'});
                break;

            case 'eval':
                try {
                    var result = eval(detail.expression);
                    box.postMessage({event: 'EvalCompleted', detail: {result: result}});
                } catch (err) {
                    box.postMessage({event: 'EvalFailed', detail: {error: err.toString()}});
                    box.postMessage({event: 'Console', detail: {message: err.toString(), type: 'error'}});
                }

                break;
        }
    };

    function reset() {
        Atomics.store(lock, 0, 0);
        buffer.fill(0);
    };

    function getResult() {
        if (Atomics.wait(lock, 0, 0, _timeout) != 'ok') {
            console.error('Script timeout while waiting for result!');
        }

        if (Atomics.load(lock, 0) != 0) {
            throw new Error('Error executing ' + JSON.stringify(_command));
        }

        return buffer;
    };

    function Runtime(timeout) {
        if (timeout) {
            _timeout = timeout;
        }
    }

    Runtime.prototype.execute = function(command) {
        _command = command;

        reset();
        box.postMessage(command);
        return getResult();
    };

    return Runtime;
})();`
], { type: 'text/javascript' }));
const APIScriptURL = window.URL.createObjectURL(new Blob([
    `/****************************************************
* Common Scripting API
***************************************************/
var Runtime = new Runtime();

function byteArrayToLong(/*byte[]*/byteArray) {
    var value = 0;
    for (var i = byteArray.length - 1; i >= 0; i--) {
        value = (value * 256) + byteArray[i];
    }

    return value;
}

function read(name) {
    var result = byteArrayToLong(Runtime.execute({
        cmd: 'read',
        name: name
    }));

    box.postMessage({event: 'Console', detail: {message: 'read(' + name + ') => ' + result}});
    return result;
}

function write(name, value) {
    var result = byteArrayToLong(Runtime.execute({
        cmd: 'write',
        name: name,
        value: value
    }));
    box.postMessage({event: 'Console', detail: {message: 'write(' + name + ', ' +  value + ') => ' + result}});
    return result;
}

function invoke(name, args, inf) {
    /* move inf from first argument to the last argument, backward compatible support */
    var hasInf = false;
    if (arguments.length === 3 && Array.isArray(arguments[2])) {
        // inf, name, args
        var _inf = name;
        name = args;
        args = inf;
        inf = _inf;
        hasInf = true;
    }

    var result = Runtime.execute({
        cmd: 'invoke',
        inf: inf,
        name: name,
        args: args
    });

    var _result = result;
    if (!hasInf) {
        result =  byteArrayToLong(result.slice(0, 8));
        _result = '0x' + result.toString(16);

    }
    box.postMessage({event: 'Console', detail: {message: 'invoke(' + name + ', [' + args + '], ' + inf + ') => ' + _result}});
    return result;
};

function log(text, clear) {
    box.postMessage({event: 'Log', detail: {text: text, clear: clear}});
}

function exit() {
    box.postMessage({event: 'Exit'});
}
`
], { type: 'text/javascript' }));
/**
 * Class that can load and run target scripting.
 *
 * @example
 * ```javascript
 *  // handles button click to call the sayHello function
 *  document.querySelector("#my_btn").addEventListener("click", function() {
 *       var script = registerModel.getModel().newScriptInstance();
 *       gc.fileCache.readTextFile('app/scripts/myscript.js').then(function(text) {
 *           script.load(text);
 *           return script.eval("sayHello('patrick')");
 *       }).then(function(result) {
 *           console.log(result);
 *       }).fail(function(error) {
 *           console.error(error);
 *       }).finally(function() {
 *           script.stop();
 *       });
 *   });
 * ```
 */
class Scripting {
    constructor(messageHdlr, bufferLength, logfile) {
        this.messageHdlr = messageHdlr;
        this.logfile = logfile;
        this.evalQueue = [];
        this.logs = [];
        /* detect SharedArrayBuffer support */
        if (typeof SharedArrayBuffer === 'undefined') {
            throw new Error('SharedArrayBuffer');
        }
        this.lock = new SharedArrayBuffer(4);
        this.lockArray = new Int32Array(this.lock);
        this.userscriptURL = null;
        this.buffer = new SharedArrayBuffer(bufferLength);
        this.bufferArray = new Uint8Array(this.buffer);
    }
    load(script) {
        /* clean up existing user script object and terminate existing worker */
        if (this.userscriptURL)
            window.URL.revokeObjectURL(this.userscriptURL);
        if (this.worker)
            this.worker.terminate();
        /* create user script object url */
        this.userscriptURL = window.URL.createObjectURL(new Blob([
            'importScripts("' + RuntimeScriptURL + '")\n' +
                'importScripts("' + APIScriptURL + '")\n\n' +
                script
        ]));
        /* create a worker */
        this.worker = new Worker(this.userscriptURL);
        /* add worker message listener */
        this.worker.onmessage = (event) => {
            if (event.data.cmd) {
                this.commandHandler(event.data).then((data) => {
                    /* array data type */
                    if (Array.isArray(data)) {
                        this.bufferArray.set(data); // only 8 bytes are used on the receiver side
                        /* boolean data type */
                    }
                    else if (typeof data === 'boolean') {
                        this.bufferArray.set(Scripting.longToByteArray(data ? 1 : 0));
                        /* number data type */
                    }
                    else if (typeof data === 'number') {
                        this.bufferArray.set(Scripting.longToByteArray(data));
                    }
                    Atomics.store(this.lockArray, 0, 0);
                }).catch(() => {
                    Atomics.store(this.lockArray, 0, -1);
                }).finally(() => {
                    Atomics.notify(this.lockArray, 0, +Infinity);
                });
            }
            else if (event.data.event) {
                this.eventHandler(event.data);
            }
        };
        /* initialize the worker */
        this.worker.postMessage({
            cmd: 'init',
            buffer: this.buffer,
            lock: this.lock
        });
        return this;
    }
    main() {
        if (!this.worker)
            return;
        this.worker.postMessage({
            cmd: 'main'
        });
    }
    stop() {
        if (!this.worker)
            return;
        this.evalQueue = [];
        this.worker.terminate();
        this.saveLog();
    }
    eval(expression) {
        if (!this.worker) {
            this.load(''); // create an empty script
        }
        return new Promise((resolve, reject) => {
            this.evalQueue.push({ deferred: { resolve: resolve, reject: reject }, expression: expression });
            if (this.worker && this.evalQueue.length === 1) {
                this.worker.postMessage({
                    cmd: 'eval',
                    expression: expression
                });
            }
        });
    }
    commandHandler(event) {
        switch (event.cmd) {
            case 'read': {
                const readEvent = event;
                return this.messageHdlr.scriptRead(readEvent.name);
            }
            case 'write': {
                const writeEvent = event;
                return this.messageHdlr.scriptWrite(writeEvent.name, writeEvent.value);
            }
            case 'invoke': {
                const invokeEvent = event;
                return this.messageHdlr.invokeMethod(invokeEvent.name, invokeEvent.args, invokeEvent.inf);
            }
            default:
                return Promise.reject('Unsupported command: ' + event.cmd);
        }
    }
    eventHandler(event) {
        switch (event.event) {
            case 'Exit':
                this.saveLog().then(function () {
                    window.close();
                });
                break;
            case 'Log':
                this.onLog(event);
                break;
            case 'MainCompleted':
                this.saveLog();
                break;
            case 'EvalCompleted':
            case 'EvalFailed':
                this.onEvalCompleted(event);
                break;
        }
    }
    onLog(event) {
        if (event.detail.clear) {
            this.logs = [];
        }
        if (event.detail.text) {
            this.logs.push(event.detail.text);
        }
    }
    saveLog() {
        return new Promise((resolve) => {
            if (this.logs && this.logs.length > 0) {
                if (typeof process === 'undefined') {
                    // TODO: supprt file save
                    // gc.File.saveBrowserFile(this.logs.join('\n'), { filename: this.logfile || 'scripting.log' });
                    this.logs = [];
                    resolve();
                }
                else {
                    // TODO: support file save
                    // gc.File.save(this.logs.join('\n'), { localPath: this.logfile || 'scripting.log' }, null, () => {
                    this.logs = [];
                    resolve();
                }
            }
            else {
                resolve(); // nothing to save.
            }
        });
    }
    onEvalCompleted(event) {
        const curEval = this.evalQueue.shift();
        if (curEval) {
            const deferred = curEval.deferred;
            event.event === 'EvalCompleted' ? deferred.resolve(event.detail.result) : deferred.reject(event.detail.error);
            if (this.worker && this.evalQueue.length >= 1) {
                this.worker.postMessage({
                    cmd: 'eval',
                    expression: this.evalQueue[0].expression
                });
            }
        }
    }
}
Scripting.longToByteArray = function (long) {
    const byteArray = [0, 0, 0, 0, 0, 0, 0, 0];
    for (let index = 0; index < byteArray.length; index++) {
        const byte = long & 0xff;
        byteArray[index] = byte;
        long = (long - byte) / 256;
    }
    return byteArray;
};
Scripting.byteArrayToLong = function (byteArray) {
    let value = 0;
    for (let i = byteArray.length - 1; i >= 0; i--) {
        value = (value * 256) + byteArray[i];
    }
    return value;
};

export { Scripting };
//# sourceMappingURL=Scripting.js.map
