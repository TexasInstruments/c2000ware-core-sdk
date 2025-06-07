import { GcUtils } from '../components/@ti/gc-core-assets/lib/GcUtils';
import { GcConsole } from '../components/@ti/gc-core-assets/lib/GcConsole';
import { bindingRegistry } from '../components/@ti/gc-core-databind/lib/CoreDatabind';
import { GcWidget } from '../components/@ti/gc-widget-base/lib/GcWidget';
import { connectionManager } from '../components/@ti/gc-target-connection-manager/lib/ConnectionManager';
import { GcLocalStorage } from '../components/@ti/gc-core-assets/lib/GcLocalStorage';
import { AbstractMessageBasedDecoder, AbstractFrameDecoder, connectedStateChangedEventType } from '../components/@ti/gc-target-configuration/lib/TargetConfiguration';
import { streamingCodecDataType } from '../components/@ti/gc-model-streaming/lib/StreamingDataModel';
import { GcFiles } from '../components/@ti/gc-core-assets/lib/GcFiles';
import { ServicesRegistry } from '../components/@ti/gc-core-services/lib/ServicesRegistry';
import { backplaneServiceType } from '../components/@ti/gc-service-backplane/lib/BackplaneService';
import { ActionRegistry } from '../components/@ti/gc-widget-menu/lib/ActionRegistry';

const runAutoset = async () => {
    // Virtual Oscilloscope
    const myVscope = document.querySelector("#test_virtual_oscilloscope_plot");
    // save for later
    const myVscopeCh1 = document.querySelector("#test_channel1_scope_input");
    const myVscopeCh2 = document.querySelector("#test_channel2_scope_input");
    const myVscopeCh3 = document.querySelector("#test_channel3_scope_input");
    const myVscopeCh4 = document.querySelector("#test_channel4_scope_input");
    const myPlotData = await myVscope.copyCaptureBuffer();
    let scopeChArray = [myVscopeCh1, myVscopeCh2, myVscopeCh3, myVscopeCh4];
    let channelMins = [];
    let channelMaxes = [];
    let channelRange = [];
    let channelAvg = [];
    const currTriggerSourceIndex = myVscope.triggerSourceIndex;
    const prevTriggerChannelVertPos = scopeChArray[currTriggerSourceIndex].verticalPos;
    const prevTriggerChannelVertScale = scopeChArray[currTriggerSourceIndex].verticalScale;
    const prevTriggerLevel = myVscope.triggerLevel;
    for (let i = 0; i < myPlotData.length; i++) {
        const filteredVal = myPlotData[i].buffer.filter((value) => value != undefined);
        channelMins[i] = Math.min(...filteredVal);
        channelMaxes[i] = Math.max(...filteredVal);
        channelRange[i] = channelMaxes[i] - channelMins[i];
        channelAvg[i] = channelRange[i] / 2 + channelMins[i];
    }
    const clampValue = (value, min, max) => {
        return Math.min(Math.max(value, min), max);
    };
    const calcVertScale = (chRange, numChannels) => {
        // vert scale eqn
        // y = 8 * e ^ (-0.7x)
        let waveformScale = 0.8; // adjust from 0 to 1 to control how much vertical space the waveforms take up after autoset
        let vertScale = (-1 / 0.7) * Math.log(chRange / ((waveformScale * 8) / numChannels));
        return clampValue(vertScale, -4, 4);
    };
    const calcVertPos = (chAvg, chScale, chIndex, numChannels) => {
        // vert pos eqn
        // y = -p * 2 ^ (-s), where p is pos and s is scale
        let chOffset = (4 / numChannels) * (1 - 2 * chIndex + numChannels);
        let vertPos = -chAvg * Math.pow(2, chScale) + chOffset;
        return clampValue(vertPos, -4, 4);
    };
    let numActiveChannels = 0;
    let counter = myPlotData.length;
    while (counter--) {
        if (myPlotData[counter].buffer[0] != null)
            numActiveChannels++;
    }
    let chIndexCounter = 0;
    for (let i = 0; i < myPlotData.length; i++) {
        if (myPlotData[i].buffer[0] != null) {
            chIndexCounter++;
            scopeChArray[i].verticalScale = calcVertScale(channelRange[i], numActiveChannels);
            scopeChArray[i].verticalPos = calcVertPos(channelAvg[i], scopeChArray[i].verticalScale, chIndexCounter, numActiveChannels);
        }
    }
    // const tempStupid = scopeChArray[currTriggerSourceIndex].verticalScale - prevTriggerChannelVertScale;
    // const logTempFirst = 8 * Math.exp(-0.7 * scopeChArray[currTriggerSourceIndex].verticalScale);
    // const logTempSecond = 8 * Math.exp(-0.7 * prevTriggerChannelVertScale);
    // const logTempStupid = (-1 / 0.7) * Math.log(tempStupid / 8);
    // const eTempStupid = 8 * Math.exp(-0.7 * tempStupid);
    myVscope.triggerLevel = clampValue(prevTriggerLevel +
        (scopeChArray[currTriggerSourceIndex].verticalPos - prevTriggerChannelVertPos) +
        (scopeChArray[currTriggerSourceIndex].verticalScale - prevTriggerChannelVertScale), -4, 4);
};
const updateWaveformAnalyzer = async () => {
    const myVscope = document.querySelector("#test_virtual_oscilloscope_plot");
    const myCh1InputMinimum = document.querySelector("#wa_ch1_minimum");
    const myCh1InputMaximum = document.querySelector("#wa_ch1_maximum");
    const myCh1InputMidpoint = document.querySelector("#wa_ch1_midpoint");
    const myCh1InputAverage = document.querySelector("#wa_ch1_average");
    const myCh1InputPeakToPeak = document.querySelector("#wa_ch1_peak_to_peak");
    const myCh1InputRMS = document.querySelector("#wa_ch1_rms");
    const myCh1InputFrequency = document.querySelector("#wa_ch1_frequency");
    const myCh1InputPulseWidth = document.querySelector("#wa_ch1_pulse_width");
    const myCh2InputMinimum = document.querySelector("#wa_ch2_minimum");
    const myCh2InputMaximum = document.querySelector("#wa_ch2_maximum");
    const myCh2InputMidpoint = document.querySelector("#wa_ch2_midpoint");
    const myCh2InputAverage = document.querySelector("#wa_ch2_average");
    const myCh2InputPeakToPeak = document.querySelector("#wa_ch2_peak_to_peak");
    const myCh2InputRMS = document.querySelector("#wa_ch2_rms");
    const myCh2InputFrequency = document.querySelector("#wa_ch2_frequency");
    const myCh2InputPulseWidth = document.querySelector("#wa_ch2_pulse_width");
    const myCh3InputMinimum = document.querySelector("#wa_ch3_minimum");
    const myCh3InputMaximum = document.querySelector("#wa_ch3_maximum");
    const myCh3InputMidpoint = document.querySelector("#wa_ch3_midpoint");
    const myCh3InputAverage = document.querySelector("#wa_ch3_average");
    const myCh3InputPeakToPeak = document.querySelector("#wa_ch3_peak_to_peak");
    const myCh3InputRMS = document.querySelector("#wa_ch3_rms");
    const myCh3InputFrequency = document.querySelector("#wa_ch3_frequency");
    const myCh3InputPulseWidth = document.querySelector("#wa_ch3_pulse_width");
    const myCh4InputMinimum = document.querySelector("#wa_ch4_minimum");
    const myCh4InputMaximum = document.querySelector("#wa_ch4_maximum");
    const myCh4InputMidpoint = document.querySelector("#wa_ch4_midpoint");
    const myCh4InputAverage = document.querySelector("#wa_ch4_average");
    const myCh4InputPeakToPeak = document.querySelector("#wa_ch4_peak_to_peak");
    const myCh4InputRMS = document.querySelector("#wa_ch4_rms");
    const myCh4InputFrequency = document.querySelector("#wa_ch4_frequency");
    const myCh4InputPulseWidth = document.querySelector("#wa_ch4_pulse_width");
    const myPlotData = await myVscope.copyCaptureBuffer();
    let scopeChMinimumArray = [myCh1InputMinimum, myCh2InputMinimum, myCh3InputMinimum, myCh4InputMinimum];
    let scopeChMaximumArray = [myCh1InputMaximum, myCh2InputMaximum, myCh3InputMaximum, myCh4InputMaximum];
    let scopeChMidpointArray = [myCh1InputMidpoint, myCh2InputMidpoint, myCh3InputMidpoint, myCh4InputMidpoint];
    let scopeChAverageArray = [myCh1InputAverage, myCh2InputAverage, myCh3InputAverage, myCh4InputAverage];
    let scopeChPeakToPeakArray = [myCh1InputPeakToPeak, myCh2InputPeakToPeak, myCh3InputPeakToPeak, myCh4InputPeakToPeak];
    let scopeChRMSArray = [myCh1InputRMS, myCh2InputRMS, myCh3InputRMS, myCh4InputRMS];
    let scopeChFrequencyArray = [myCh1InputFrequency, myCh2InputFrequency, myCh3InputFrequency, myCh4InputFrequency];
    let scopeChPulseWidthArray = [myCh1InputPulseWidth, myCh2InputPulseWidth, myCh3InputPulseWidth, myCh4InputPulseWidth];
    let channelMins = [];
    let channelMaxes = [];
    let channelRange = [];
    let channelMidPoint = [];
    let channelAvg = [];
    let channelRMS = [];
    for (let i = 0; i < myPlotData.length; i++) {
        const filteredVal = myPlotData[i].buffer.filter((value) => value != undefined);
        channelMins[i] = Math.min(...filteredVal);
        channelMaxes[i] = Math.max(...filteredVal);
        channelRange[i] = channelMaxes[i] - channelMins[i];
        channelMidPoint[i] = channelRange[i] / 2 + channelMins[i];
        let accumulatedSum = filteredVal.reduce((partialSum, value) => partialSum + value);
        channelAvg[i] = accumulatedSum / filteredVal.length;
        let squareSum = filteredVal.reduce((partialSquareSum, value) => partialSquareSum + Math.pow(value, 2));
        channelRMS[i] = Math.sqrt(squareSum / filteredVal.length);
    }
    for (let i = 0; i < myPlotData.length; i++) {
        if (myPlotData[i].buffer[0] != null) {
            scopeChMinimumArray[i].value = channelMins[i];
            scopeChMaximumArray[i].value = channelMaxes[i];
            scopeChMidpointArray[i].value = channelMidPoint[i];
            scopeChPeakToPeakArray[i].value = channelRange[i];
            scopeChAverageArray[i].value = channelAvg[i];
            scopeChRMSArray[i].value = channelRMS[i];
        }
    }
};
const clearScopeBuffer = () => {
    const myVscope = document.querySelector("#test_virtual_oscilloscope_plot");
    myVscope.clearCaptureBuffer();
    myVscope.refresh();
};
const initScopeConfig = () => {
    //
    // Query all HTML components and store in variables for easy access
    //
    // Reference to button widgets
    const myAutosetButton = document.querySelector("#autoset_scope_button");
    const myRefreshWaveformAnalyzerButton = document.querySelector("#wa_dialog_refresh_button");
    // Reference to dropdown select widgets
    const myVScopeCh1Select = document.querySelector("#channel1_select");
    const myVScopeCh2Select = document.querySelector("#channel2_select");
    const myVScopeCh3Select = document.querySelector("#channel3_select");
    const myVScopeCh4Select = document.querySelector("#channel4_select");
    // Reference to scope input widgets
    const myVscopeCh1Input = document.querySelector("#test_channel1_scope_input");
    const myVscopeCh2Input = document.querySelector("#test_channel2_scope_input");
    const myVscopeCh3Input = document.querySelector("#test_channel3_scope_input");
    const myVscopeCh4Input = document.querySelector("#test_channel4_scope_input");
    //
    // Create synchronized component arrays for easier binding
    //
    const scopeChSelectArray = [myVScopeCh1Select, myVScopeCh2Select, myVScopeCh3Select, myVScopeCh4Select];
    const scopeChInputArray = [myVscopeCh1Input, myVscopeCh2Input, myVscopeCh3Input, myVscopeCh4Input];
    //
    // Assign event listeners to widget components
    //
    myAutosetButton.addEventListener("click", async () => {
        runAutoset();
    });
    myRefreshWaveformAnalyzerButton.addEventListener("click", () => {
        updateWaveformAnalyzer();
    });
    // Adjust scope y-axis titles based on what is selected in the dropdown widgets
    scopeChSelectArray.forEach((_, index) => {
        scopeChSelectArray[index].addEventListener("selected-label-changed", () => {
            scopeChInputArray[index].yAxisTitle = scopeChSelectArray[index].selectedLabel;
        });
    });
};
const importHashTable = async () => {
    const myImportData = document.querySelector("#import_json_dialog");
    const result = await myImportData.browseAndLoad(false);
    const fileContent = result[0];
    GcLocalStorage.setItem("hash-table", fileContent);
    // await GcFiles.writeJsonFile("./imported_hash_table.json", JSON.parse(fileContent));
    // codecClassObject.hashPath = "./imported_hash_table.json";
    await connectionManager.disconnect();
    await connectionManager.connect();
};

//Constants
const START_BYTE = 0x73; //'s'.charCodeAt(0);
const END_BYTE = 0x65; //'e'.charCodeAt(0);
const STREAM_1_FRAME_LENGTH = 7;
const STREAM_2_FRAME_LENGTH = 11;
const STREAM_3_FRAME_LENGTH = 15;
const STREAM_4_FRAME_LENGTH = 19;
const POLL_16_FRAME_LENGTH = 6;
const POLL_32_FRAME_LENGTH = 8;
const ACK_MSG_LENGTH = 3;
const PLOT_CAPACITY = 5000;
const dataTypes16bits = ["uint16", "int16", "bool"];
const dataTypes32bits = ["uint32", "int32", "float"];
let BUSY_PROMISE = Promise.resolve();
let connected = false;
/*const DEFAULT_STREAM_A = "speed_Hz";
const DEFAULT_STREAM_B = "mAngleAdjusted";
const DEFAULT_STREAM_C = "I_A";
const DEFAULT_STREAM_D = "IqComp";*/
//var hashTable = {};
//CMD Encodings
const cmds = {
    //bidirectional
    PACKET_ERROR: 0x27,
    //commands
    INIT: 0x28,
    WRITE_VARIABLE: 0x2b,
    INIT_STREAMING_VARIABLES: 0x2c,
    START_STREAM_A: 0x2d,
    START_STREAM_B: 0x2e,
    START_STREAM_C: 0x2f,
    START_STREAM_D: 0x30,
    STOP_STREAM_A: 0x31,
    STOP_STREAM_B: 0x32,
    STOP_STREAM_C: 0x33,
    STOP_STREAM_D: 0x34,
    //responses
    STREAM_DATA_1_VAR: 0x35,
    STREAM_DATA_2_VAR: 0x36,
    STREAM_DATA_3_VAR: 0x37,
    STREAM_DATA_4_VAR: 0x38,
    STREAM_DATA_WRITEACK_1_VAR: 0x39,
    STREAM_DATA_WRITEACK_2_VAR: 0x3a,
    STREAM_DATA_WRITEACK_3_VAR: 0x3b,
    STREAM_DATA_WRITEACK_4_VAR: 0x3c,
    START_POLLING_1: 0x3f,
    START_POLLING_2: 0x40,
    START_POLLING_3: 0x41,
    START_POLLING_4: 0x42,
    START_POLLING_5: 0x43,
    START_POLLING_6: 0x44,
    START_POLLING_7: 0x45,
    START_POLLING_8: 0x46,
    START_POLLING_9: 0x47,
    START_POLLING_10: 0x48,
    START_POLLING_11: 0x49,
    START_POLLING_12: 0x4a,
    START_POLLING_13: 0x4b,
    STOP_POLLING: 0x4c,
    POLLING_DATA: 0x4d,
    CLEAR_STREAMING_PLOT: 0x4e,
};
const cmdVals = {
    //bidirectional
    0x27: "PACKET_ERROR",
    //commands
    0x28: "INIT",
    0x2b: "WRITE_VARIABLE",
    0x2c: "INIT_STREAMING_VARIABLES",
    0x2d: "START_STREAM_A",
    0x2e: "START_STREAM_B",
    0x2f: "START_STREAM_C",
    0x30: "START_STREAM_D",
    0x31: "STOP_STREAM_A",
    0x32: "STOP_STREAM_B",
    0x33: "STOP_STREAM_C",
    0x34: "STOP_STREAM_D",
    //responses
    0x35: "STREAM_DATA_1_VAR",
    0x36: "STREAM_DATA_2_VAR",
    0x37: "STREAM_DATA_3_VAR",
    0x38: "STREAM_DATA_4_VAR",
    0x39: "STREAM_DATA_WRITEACK_1_VAR",
    0x3a: "STREAM_DATA_WRITEACK_2_VAR",
    0x3b: "STREAM_DATA_WRITEACK_3_VAR",
    0x3c: "STREAM_DATA_WRITEACK_4_VAR",
    //tab switches
    0x3f: "START_POLLING_1",
    0x40: "START_POLLING_2",
    0x41: "START_POLLING_3",
    0x42: "START_POLLING_4",
    0x43: "START_POLLING_5",
    0x44: "START_POLLING_6",
    0x45: "START_POLLING_7",
    0x46: "START_POLLING_8",
    0x47: "START_POLLING_9",
    0x48: "START_POLLING_10",
    0x49: "START_POLLING_11",
    0x4a: "START_POLLING_12",
    0x4b: "START_POLLING_13",
    0x4c: "STOP_POLLING",
    0x4d: "POLLING_DATA",
    0x4e: "CLEAR_STREAMING_PLOT",
};
function waitforme(millisec) {
    return new Promise((resolve) => {
        setTimeout(() => {
            resolve("");
        }, millisec);
    });
}
const waitForTargetConnection = async () => {
    const backplaneService = ServicesRegistry.getService(backplaneServiceType);
    const dsModule = await backplaneService.getSubModule("DS");
    const coreList = await dsModule.listCores();
    if (!coreList || coreList.cores.length <= 0) {
        throw Error("no debuggable cores found");
    }
    const core = await dsModule.getSubModule(coreList.cores[0]);
    let currentState = (await core.targetState.getCurrentState()).executionState;
    let timeoutID;
    return new Promise(async (resolve, reject) => {
        if (currentState == "Running") {
            resolve(0);
        }
        await core.targetState.addListener("changed", (event) => {
            console.log(event.state.executionState);
            if (event.state.executionState == "Running") {
                timeoutID = setTimeout(async () => {
                    currentState = (await core.targetState.getCurrentState()).executionState;
                    if (currentState == "Running") {
                        resolve(0);
                    }
                }, 500);
            }
            if (event.state.executionState != "Running") {
                clearTimeout(timeoutID);
            }
        });
    });
};
const initializeCodeHaltingHandler = async () => {
    const selectChannel1 = document.querySelector("#channel1_select");
    const selectChannel2 = document.querySelector("#channel2_select");
    const selectChannel3 = document.querySelector("#channel3_select");
    const selectChannel4 = document.querySelector("#channel4_select");
    const toggleChannel1 = document.querySelector("#channel1_toggle");
    const toggleChannel2 = document.querySelector("#channel2_toggle");
    const toggleChannel3 = document.querySelector("#channel3_toggle");
    const toggleChannel4 = document.querySelector("#channel4_toggle");
    const haltableWidgets = [selectChannel1, selectChannel2, selectChannel3, selectChannel4, toggleChannel1, toggleChannel2, toggleChannel3, toggleChannel4];
    const backplaneService = ServicesRegistry.getService(backplaneServiceType);
    const dsModule = await backplaneService.getSubModule("DS");
    const coreList = await dsModule.listCores();
    if (!coreList || coreList.cores.length <= 0) {
        throw Error("no debuggable cores found");
    }
    const core = await dsModule.getSubModule(coreList.cores[0]);
    await core.targetState.addListener("changed", (event) => {
        if (event.state.executionState == "Running" || event.state.executionState == "Unknown") {
            haltableWidgets.forEach((widget) => {
                widget.disabled = false;
                widget.tooltip = "";
            });
        }
        if (event.state.executionState == "Halted") {
            haltableWidgets.forEach((widget) => {
                widget.disabled = true;
                widget.tooltip = "Widget disabled due to CPU halt";
            });
        }
    });
};
const WAIT_TIME = 0;
var cmdSequenceNumber = 0;
const NUM_CMD_RETRIES = 5;
class asmGUICodec extends AbstractMessageBasedDecoder {
    constructor(params) {
        super(params.id || "custom", params.console, 1);
        this.params = params;
        // private connected = false;
        this.hashTable = {};
        // variables for validation testing
        this.logRawData = false;
        this.rawDataBufferSize = 0;
        this.rawDataBuffer = [];
        this.logDecodedData = false;
        this.decodedDataBufferSize = 0;
        this.decodedDataBuffer = [];
        this.decodedDataJSON = {};
        this.decodedDataFormat = "simple";
        this.encoderInputType = streamingCodecDataType;
        this.encoderOutputType = streamingCodecDataType;
        // this.connected = false;
        // this.hashTable = {};
        this.hashPath = params.hashPath;
        this.currentPollingVariables = [];
        this.currentStreamingVariables = [];
        //this.prevEnabledChannels = { A: false, B: false, C: false, D: false };
        this.enabledChannels = { A: false, B: false, C: false, D: false }; //member of asmGUICodec
        this.frameDecoder = new (class extends AbstractFrameDecoder {
            constructor(packetDecoder) {
                super("", START_BYTE);
                this.packetDecoder = packetDecoder;
                this.params = {};
                this.hashTableInFrameDecoder = {};
            }
            getPacketLength(buffer, offset) {
                if (!connected) {
                    let commandReceived = buffer[offset + 1];
                    if (commandReceived == 0x28) {
                        return ACK_MSG_LENGTH;
                    }
                    else {
                        return -1;
                    }
                }
                else {
                    if (buffer.length > offset + 2) {
                        //return expected length of packet (only called once), will call decodePacket() below when it has this length
                        let commandReceived = buffer[offset + 1];
                        if (commandReceived in cmdVals) {
                            let commandName = cmdVals[commandReceived];
                            if (commandName.includes("ERROR")) {
                                return 3; //need to modify
                            }
                            else if (commandName.includes("STREAM_DATA")) {
                                if (commandName.includes("1")) {
                                    return STREAM_1_FRAME_LENGTH;
                                }
                                else if (commandName.includes("2")) {
                                    return STREAM_2_FRAME_LENGTH;
                                }
                                else if (commandName.includes("3")) {
                                    return STREAM_3_FRAME_LENGTH;
                                }
                                else if (commandName.includes("4")) {
                                    return STREAM_4_FRAME_LENGTH;
                                }
                                else {
                                    return -1;
                                }
                            }
                            else if (commandName.includes("POLLING_DATA")) {
                                let hashReceived = buffer[offset + 2];
                                let varType = "float";
                                for (let hashVar in this.hashTableInFrameDecoder) {
                                    if (this.hashTableInFrameDecoder[hashVar].index === hashReceived) {
                                        varType = this.hashTableInFrameDecoder[hashVar].type;
                                        break;
                                    }
                                }
                                if (dataTypes16bits.includes(varType)) {
                                    return POLL_16_FRAME_LENGTH;
                                }
                                else if (dataTypes32bits.includes(varType)) {
                                    return POLL_32_FRAME_LENGTH;
                                }
                                else {
                                    return -1;
                                }
                            }
                            else {
                                //ack only, no data sent
                                return ACK_MSG_LENGTH;
                            }
                        }
                        else {
                            return -1; //invalid command  (will ignore this packet)
                        }
                    }
                    else {
                        return 0; //not enough data yet
                    }
                }
            }
            decodePacket(packet) {
                //calls this first, then calls frameDecoder decodePacket() (rerouting to current classes function)
                return this.packetDecoder.decodePacket(packet);
            }
        })(this);
    }
    async onDisconnect() {
        connected = false;
    }
    async sendOnePacket(packetData, retryCount) {
        //function calls itself recursively until ack is received and logged
        const retries = retryCount ?? 0; //is itself or 0 if undefined
        //length is always 16
        return new Promise(async (resolve, reject) => {
            try {
                super.encode(packetData); //send 1st cmd packet
                console.log(`${packetData[1].toString()} cmd packet sent to target`);
                resolve(await this.addCommand(packetData[1])); //sit and wait until ack (sends promise back to commandUpdates) or error (goes to catch branch) msg has been received
                console.log("addCommand await completed");
            }
            catch (error) {
                if (retries >= NUM_CMD_RETRIES) {
                    //number of retries
                    console.log(`packet failed: ${error}`);
                    reject(error);
                }
                else {
                    try {
                        resolve(await this.sendOnePacket(packetData, retries + 1)); //will call itself recursively 4 times if ack isn't received
                    }
                    catch (error) {
                        reject(error);
                    }
                }
            }
        });
    }
    async commandUpdates(fullPacketToSend, packetLength) {
        // let cmdsToSend : number[] = [];  //6 at a time should be max
        // let currentPacketToSend : number[]  = fullPacketToSend.slice(0, 16);
        let currentPacketToSend;
        //Get all command bytes to be sent
        // for(let index16 = 0; index16 < packetLength; index16 += 16){
        // 	cmdsToSend.push(fullPacketToSend[index16+1]);
        // }
        try {
            for (let i = 0; i < fullPacketToSend.length; i += 16) {
                currentPacketToSend = fullPacketToSend.slice(i, i + 16);
                await this.sendOnePacket(currentPacketToSend, 0);
                this.console.log("commandUpdates await completed");
            }
            // await this.sendOnePacket(currentPacketToSend, 0) //send 1st cmd packet
            // if(cmdsToSend.length > 1){
            // 	currentPacketToSend = fullPacketToSend.slice(16, 32);
            // 	await this.sendOnePacket(currentPacketToSend, 0) //send 2nd cmd packet (if applicable)
            // 	if(cmdsToSend.length > 2){
            // 		currentPacketToSend = fullPacketToSend.slice(32, 48);
            // 		await this.sendOnePacket(currentPacketToSend, 0) //send 3rd cmd packet (if applicable)
            // 		if(cmdsToSend.length > 3){
            // 			currentPacketToSend = fullPacketToSend.slice(48, 64);
            // 			await this.sendOnePacket(currentPacketToSend, 0) //send 4th cmd packet (if applicable)
            // 			if(cmdsToSend.length > 4){
            // 				currentPacketToSend = fullPacketToSend.slice(64, 80);
            // 				await this.sendOnePacket(currentPacketToSend, 0) //send 5th cmd packet (if applicable)
            // 				if(cmdsToSend.length > 5){
            // 					currentPacketToSend = fullPacketToSend.slice(80, 96);
            // 					await this.sendOnePacket(currentPacketToSend, 0) //send 6th cmd packet (if applicable)
            // 				}
            // 			}
            // 		}
            // 	}
            // }
        }
        catch (error) {
            console.log("GUI was not able to send cmd sequence");
        }
    }
    // async changePollingVariables(sequenceNumber: number, retryCount: number) {
    // 	sequenceNumber = sequenceNumber ?? 0; //is itself or 0 if undefined
    // 	retryCount = retryCount ?? 0;
    // 	try {
    // 		let cmdToSend0;
    // 		let cmdToSend1;
    // 		let cmdToSend2;
    // 		if (sequenceNumber === 0) {
    // 			super.encode(cmdToSend0);
    // 			await this.addCommand(cmdToSend0);
    // 			sequenceNumber++;
    // 		}
    // 		if (sequenceNumber === 1) {
    // 			super.encode(cmdToSend1);
    // 			await this.addCommand(cmdToSend1);
    // 			sequenceNumber++;
    // 		}
    // 		if (sequenceNumber === 2) {
    // 			super.encode(cmdToSend2);
    // 			await this.addCommand(cmdToSend2);
    // 			sequenceNumber++;
    // 		}
    // 	} catch (error) {
    // 		//check retryCount
    // 		if (retryCount >= 1) {
    // 			//number of retries
    // 			console.log(`packet failed: ${error}`);
    // 		} else {
    // 			this.changePollingVariables(sequenceNumber, retryCount + 1);
    // 		}
    // 	}
    // }
    async onConnect() {
        // TODO
        this.console.log("entering onConnect");
        connected = false;
        this.commandQueue.clearAll();
        BUSY_PROMISE = Promise.resolve();
        const hashTableCookie = GcLocalStorage.getItem("hash-table");
        if (hashTableCookie !== null) {
            this.hashTable = JSON.parse(hashTableCookie);
        }
        else {
            this.hashTable = (await GcFiles.readJsonFile(this.hashPath));
        }
        this.frameDecoder.hashTableInFrameDecoder = this.hashTable;
        //this.currentStreamingVariables = [DEFAULT_STREAM_A, DEFAULT_STREAM_B, DEFAULT_STREAM_C, DEFAULT_STREAM_D];
        let streamableArray = [];
        //Get array of all streamable variables
        for (let variable in this.hashTable) {
            if (this.hashTable[variable].streamable) {
                if (this.hashTable[variable]?.display != undefined) {
                    streamableArray.push(this.hashTable[variable].display);
                }
                else {
                    streamableArray.push(variable);
                }
            }
        }
        if (streamableArray.length >= 4) {
            this.currentStreamingVariables = [streamableArray[0], streamableArray[1], streamableArray[2], streamableArray[3]];
        }
        else if (streamableArray.length >= 3) {
            this.currentStreamingVariables = [streamableArray[0], streamableArray[1], streamableArray[2], streamableArray[0]];
        }
        else if (streamableArray.length >= 2) {
            this.currentStreamingVariables = [streamableArray[0], streamableArray[1], streamableArray[0], streamableArray[1]];
        }
        else if (streamableArray.length >= 1) {
            this.currentStreamingVariables = [streamableArray[0], streamableArray[0], streamableArray[0], streamableArray[0]];
        }
        else {
            console.log("error: no streamable variables");
            this.currentStreamingVariables = ["", "", "", ""];
        }
        //Push just the default values first so that the first option isn't defaulted to when streamOptions is pushed
        //(uses display names for currentStreamVariables)
        this.targetDecoder.decode({
            streamVariables: {
                A: this.currentStreamingVariables[0],
                B: this.currentStreamingVariables[1],
                C: this.currentStreamingVariables[2],
                D: this.currentStreamingVariables[3],
            },
        });
        //Replace display names with actual table names (if display name exists) for target packet index access
        for (let hashVar in this.hashTable) {
            if (this.hashTable[hashVar]?.display != undefined) {
                if (this.currentStreamingVariables[0] == this.hashTable[hashVar].display) {
                    this.currentStreamingVariables[0] = hashVar;
                }
                else if (this.currentStreamingVariables[1] == this.hashTable[hashVar].display) {
                    this.currentStreamingVariables[1] = hashVar;
                }
                else if (this.currentStreamingVariables[2] == this.hashTable[hashVar].display) {
                    this.currentStreamingVariables[2] = hashVar;
                }
                else if (this.currentStreamingVariables[3] == this.hashTable[hashVar].display) {
                    this.currentStreamingVariables[3] = hashVar;
                }
            }
        }
        //validate connection with the target
        //const result = this.addCommand(cmds.INIT);
        let packetToSend = [START_BYTE, cmds.INIT, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, END_BYTE];
        let initStreamingVars = [
            START_BYTE,
            cmds.INIT_STREAMING_VARIABLES,
            this.hashTable[this.currentStreamingVariables[0]].index,
            this.hashTable[this.currentStreamingVariables[1]].index,
            this.hashTable[this.currentStreamingVariables[2]].index,
            this.hashTable[this.currentStreamingVariables[3]].index,
            0x00,
            0x00,
            0x00,
            0x00,
            0x00,
            0x00,
            0x00,
            0x00,
            0x00,
            END_BYTE,
        ];
        if (WAIT_TIME) {
            // super.encode([0xaa]);
            // await waitforme(WAIT_TIME);
            super.encode(packetToSend);
            await waitforme(WAIT_TIME);
            super.encode(initStreamingVars);
        }
        else {
            packetToSend = packetToSend.concat(initStreamingVars);
            //this.commandUpdates(packetToSend, 32);
            //super.encode(packetToSend);
        }
        //get all Variables with write permissions, initialize their types
        var rwVariableInit = {};
        for (let variable in this.hashTable) {
            if (this.hashTable[variable].permissions.includes("W") || this.hashTable[variable].permissions.includes("R")) {
                if (this.hashTable[variable]?.bits != undefined) {
                    //add bitfield streaming model variables
                    for (let bitfield in this.hashTable[variable].bits) {
                        rwVariableInit[bitfield] = 0;
                    }
                }
                if (this.hashTable[variable].type === "uint16" ||
                    this.hashTable[variable].type === "uint32" ||
                    this.hashTable[variable].type === "int16" ||
                    this.hashTable[variable].type === "int32") {
                    rwVariableInit[variable] = 0;
                }
                else if (this.hashTable[variable].type === "float") {
                    rwVariableInit[variable] = 0.0;
                }
                else if (this.hashTable[variable].type === "bool") {
                    rwVariableInit[variable] = false;
                }
            }
        }
        //push all init values to define types
        let initObj = {
            streamOptions: streamableArray,
            streamData: { A: 0.0, B: 0.0, C: 0.0, D: 0.0 },
            streamToggles: { A: false, B: false, C: false, D: false },
            rwVariables: rwVariableInit,
        };
        //Initially tell target to start polling variables on page 0
        let streamObj = {};
        streamObj["page"] = document.querySelector("#main_tab_container").index;
        streamObj["initPacket"] = packetToSend;
        // await delay(5000); // omly needed in mcgui bc we need to be able to load the program onto the device
        if (GcUtils.isCCS || GcUtils.isTheia) {
            // console.log("waitingggg");
            // return new Promise((resolve, reject) => {
            // 	const myContinueButton = document.querySelector("#button_import_json_continue") as Components.GcWidgetButton & HTMLElement;
            // 	myContinueButton.addEventListener("click", async () => {
            // 		resolve(0);
            // 	});
            // });
            // await waitForTargetConnection();
            // await initializeCodeHaltingHandler();
        }
        this.encode(streamObj);
        return this.targetDecoder.decode(initObj);
    }
    encode(rawData) {
        // get from parent class, define a custom type
        //data is object with data, loop through
        //const rawData8 = new Uint8Array(4); // If 64b inputs used, change to 8
        //var dataViewObj = new DataView(rawData8.buffer);
        // create a custom interface if needed
        const data = rawData;
        let cmdToSend = cmds.INIT;
        let hashIndexToSend = 0x00;
        let dataToSend3 = 0x00;
        let dataToSend2 = 0x00;
        let dataToSend1 = 0x00;
        let dataToSend0 = 0x00;
        let packetToSend = [];
        //Init packet included - should also have page data
        if (data.initPacket != undefined) {
            packetToSend = data.initPacket;
        }
        else {
            if (!connected) {
                return;
            }
        }
        //Change page -> Update polling variables
        if (data.page != undefined) {
            //variable has been written
            //anytime page changes -> automatically clear polling variable list (stop_polling)
            packetToSend = packetToSend.concat([
                START_BYTE,
                cmds.STOP_POLLING,
                0x00,
                0x00,
                0x00,
                0x00,
                0x00,
                0x00,
                0x00,
                0x00,
                0x00,
                0x00,
                0x00,
                0x00,
                0x00,
                END_BYTE,
            ]);
            //Generate array of all polling variables for this page, in numeric order
            this.currentPollingVariables = [];
            let newPage = data.page;
            let index = 0;
            for (let hashVar in this.hashTable) {
                if (this.hashTable[hashVar].page.length !== 0 &&
                    this.hashTable[hashVar].page != undefined &&
                    this.hashTable[hashVar].page.includes(newPage) &&
                    this.hashTable[hashVar].permissions.includes("R")) {
                    this.currentPollingVariables.push(index);
                }
                index++;
            }
            //Construction of next message to send
            let remainder = 0;
            if (this.currentPollingVariables.length <= 13) {
                remainder = this.currentPollingVariables.length;
            }
            else {
                remainder = this.currentPollingVariables.length % 13; //13 available spots in a frame other than start, end and cmd
            }
            let frames = Math.ceil(this.currentPollingVariables.length / 13);
            let varIndex = 0;
            for (let f = 0; f < frames; f++) {
                //generate cmd byte for current frame
                if (f === frames - 1) {
                    //last frame -> get command to send
                    let cmdString = "START_POLLING_" + remainder.toString();
                    if (cmds[cmdString] != undefined) {
                        cmdToSend = cmds[cmdString];
                    }
                    else {
                        console.log("ERROR: invalid CMD string");
                    }
                }
                else {
                    cmdToSend = cmds.START_POLLING_13;
                }
                packetToSend = packetToSend.concat([START_BYTE, cmdToSend]);
                //generate data to send
                for (let frameByte = 2; frameByte < 15; frameByte++) {
                    if (varIndex === this.currentPollingVariables.length) {
                        //add placeholder values
                        packetToSend.push(0x00);
                    }
                    else {
                        //add next variable hash index
                        packetToSend.push(this.currentPollingVariables[varIndex]);
                        varIndex++;
                    }
                }
                packetToSend.push(END_BYTE);
            }
        }
        //Streaming Enable/Disable
        if (data.streamToggles != undefined) {
            if (data.streamToggles.A != undefined) {
                this.enabledChannels.A = data.streamToggles.A;
                if (data.streamToggles.A) {
                    cmdToSend = cmds.START_STREAM_A;
                }
                else {
                    cmdToSend = cmds.STOP_STREAM_A;
                }
            }
            if (data.streamToggles.B != undefined) {
                this.enabledChannels.B = data.streamToggles.B;
                if (data.streamToggles.B) {
                    cmdToSend = cmds.START_STREAM_B;
                }
                else {
                    cmdToSend = cmds.STOP_STREAM_B;
                }
            }
            if (data.streamToggles.C != undefined) {
                this.enabledChannels.C = data.streamToggles.C;
                if (data.streamToggles.C) {
                    cmdToSend = cmds.START_STREAM_C;
                }
                else {
                    cmdToSend = cmds.STOP_STREAM_C;
                }
            }
            if (data.streamToggles.D != undefined) {
                this.enabledChannels.D = data.streamToggles.D;
                if (data.streamToggles.D) {
                    cmdToSend = cmds.START_STREAM_D;
                }
                else {
                    cmdToSend = cmds.STOP_STREAM_D;
                }
            }
            //Construction of next message to send
            packetToSend = [START_BYTE, cmdToSend];
            for (let i = 2; i < 15; i++) {
                packetToSend.push(0x00);
            }
            packetToSend.push(END_BYTE);
        }
        //Change Streaming Variable
        if (data.streamVariables != undefined) {
            if (data.streamVariables.A != undefined) {
                this.currentStreamingVariables[0] = data.streamVariables.A;
            }
            else if (data.streamVariables.B != undefined) {
                this.currentStreamingVariables[1] = data.streamVariables.B;
            }
            else if (data.streamVariables.C != undefined) {
                this.currentStreamingVariables[2] = data.streamVariables.C;
            }
            else if (data.streamVariables.D != undefined) {
                this.currentStreamingVariables[3] = data.streamVariables.D;
            }
            //Replace display names with actual table names (if display name exists)
            for (let hashVar in this.hashTable) {
                if (this.hashTable[hashVar]?.display != undefined) {
                    if (data.streamVariables.A != undefined) {
                        if (this.hashTable[hashVar].display == data.streamVariables.A) {
                            this.currentStreamingVariables[0] = hashVar;
                        }
                    }
                    else if (data.streamVariables.B != undefined) {
                        if (this.hashTable[hashVar].display == data.streamVariables.B) {
                            this.currentStreamingVariables[1] = hashVar;
                        }
                    }
                    else if (data.streamVariables.C != undefined) {
                        if (this.hashTable[hashVar].display == data.streamVariables.C) {
                            this.currentStreamingVariables[2] = hashVar;
                        }
                    }
                    else if (data.streamVariables.D != undefined) {
                        if (this.hashTable[hashVar].display == data.streamVariables.D) {
                            this.currentStreamingVariables[3] = hashVar;
                        }
                    }
                }
            }
            packetToSend = [
                START_BYTE,
                cmds.INIT_STREAMING_VARIABLES,
                this.hashTable[this.currentStreamingVariables[0]].index,
                this.hashTable[this.currentStreamingVariables[1]].index,
                this.hashTable[this.currentStreamingVariables[2]].index,
                this.hashTable[this.currentStreamingVariables[3]].index,
                0x00,
                0x00,
                0x00,
                0x00,
                0x00,
                0x00,
                0x00,
                0x00,
                0x00,
                END_BYTE,
            ];
        }
        //Write Variable
        if (data.rwVariables != undefined) {
            //variable has been written
            let index = 0;
            for (let hashVar in this.hashTable) {
                if (data.rwVariables[hashVar] != undefined && this.hashTable[hashVar].permissions.includes("W")) {
                    //write the variable with the data
                    cmdToSend = cmds.WRITE_VARIABLE;
                    hashIndexToSend = index;
                    let sendData = data.rwVariables[hashVar];
                    if (dataTypes16bits.includes(this.hashTable[hashVar].type)) {
                        //2 bytes of data
                        const rawData8 = new Uint8Array(2); //
                        const dataViewEncode = new DataView(rawData8.buffer);
                        console.log("2");
                        console.log(data.rwVariables[hashVar]);
                        if (this.hashTable[hashVar].type === "bool") {
                            dataViewEncode.setUint16(0, sendData ? 1 : 0);
                            dataToSend3 = rawData8[0];
                            dataToSend2 = rawData8[1];
                        }
                        else if (this.hashTable[hashVar].type === "uint16") {
                            dataViewEncode.setUint16(0, sendData);
                            dataToSend3 = rawData8[0];
                            dataToSend2 = rawData8[1];
                        }
                        else if (this.hashTable[hashVar].type === "int16") {
                            dataViewEncode.setInt16(0, sendData);
                            dataToSend3 = rawData8[0];
                            dataToSend2 = rawData8[1];
                        }
                    }
                    else if (dataTypes32bits.includes(this.hashTable[hashVar].type)) {
                        //4 bytes of data
                        const rawData8 = new Uint8Array(4); //
                        const dataViewEncode = new DataView(rawData8.buffer);
                        // console.log("4");
                        // console.log(data.rwVariables[hashVar]);
                        if (this.hashTable[hashVar].type === "uint32") {
                            dataViewEncode.setUint32(0, sendData);
                            dataToSend3 = rawData8[0];
                            dataToSend2 = rawData8[1];
                            dataToSend1 = rawData8[2];
                            dataToSend0 = rawData8[3];
                        }
                        else if (this.hashTable[hashVar].type === "int32") {
                            dataViewEncode.setInt32(0, sendData);
                            dataToSend3 = rawData8[0];
                            dataToSend2 = rawData8[1];
                            dataToSend1 = rawData8[2];
                            dataToSend0 = rawData8[3];
                            console.log("data set");
                        }
                        else if (this.hashTable[hashVar].type === "float") {
                            dataViewEncode.setFloat32(0, sendData);
                            dataToSend3 = rawData8[0];
                            dataToSend2 = rawData8[1];
                            dataToSend1 = rawData8[2];
                            dataToSend0 = rawData8[3];
                        }
                    }
                }
                index++;
            }
            //Construction of next message to send
            packetToSend = [START_BYTE, cmdToSend, hashIndexToSend, dataToSend3, dataToSend2, dataToSend1, dataToSend0];
            for (let i = 7; i < 15; i++) {
                packetToSend.push(0x00);
            }
            packetToSend.push(END_BYTE);
        }
        //changePollingVariables();
        //base class will load sent packet and implement flow control
        if (WAIT_TIME) {
            if (!(packetToSend.length % 16)) {
                this.console.log("packet is not a multiple of 16");
            }
            for (let i = 0; i < packetToSend.length; i += 16) {
                waitforme(WAIT_TIME).then(() => {
                    super.encode(packetToSend.slice(i, i + 16));
                });
            }
        }
        else {
            if (packetToSend.length % 16 || packetToSend.length > 96) {
                this.console.log("Full packet length is invalid");
            }
            else {
                BUSY_PROMISE = BUSY_PROMISE.finally(() => this.commandUpdates(packetToSend, packetToSend.length));
            }
            //super.encode(packetToSend);
        }
    }
    decode(data) {
        let decodeReturn;
        try {
            decodeReturn = this.frameDecoder.decode(data);
            if (decodeReturn instanceof Error)
                throw new Error("Invalid packet received, ignore if reconnecting to target.");
            return decodeReturn;
        }
        catch (error) {
            return false;
        }
    }
    deconfigure() {
        //clean up state of frame decoder before next connection
        this.frameDecoder.deconfigure();
    }
    addChildDecoder(child) {
        // type of targetDecoder
        this.targetDecoder = child;
    }
    decodePacket(rawData) {
        //logs the received packet with AbstractMessageBasedDecoder
        super.decode(rawData);
        let messageValid = true;
        let messageIsAck = true;
        let ackCmdID = "";
        const packet = new Uint8Array(rawData);
        const dataView = new DataView(packet.buffer);
        let streamObj = {};
        let cmdByteValue = rawData[1];
        let commandByteName = "INIT";
        let errorResponse = false;
        // data log helper functions
        const LogRawData = () => {
            if (this.logRawData) {
                rawData.forEach((singleRawData) => {
                    if (this.rawDataBuffer.length < this.rawDataBufferSize) {
                        this.rawDataBuffer.push(singleRawData);
                    }
                });
            }
        };
        const LogDecodedData = (decodedDataPoint, decodedDataBucket) => {
            if (this.logDecodedData) {
                if (this.decodedDataFormat == "simple") {
                    if (this.decodedDataBuffer.length < this.decodedDataBufferSize) {
                        this.decodedDataBuffer.push(decodedDataPoint);
                    }
                }
                else if (this.decodedDataFormat == "detailed") {
                    if (this.decodedDataJSON[decodedDataBucket]) {
                        if (this.decodedDataJSON[decodedDataBucket].length < this.decodedDataBufferSize) {
                            this.decodedDataJSON[decodedDataBucket].push(decodedDataPoint);
                        }
                    }
                    else {
                        this.decodedDataJSON[decodedDataBucket] = [decodedDataPoint];
                        console.log(this.decodedDataJSON);
                    }
                }
            }
        };
        // log raw data for validation testing
        LogRawData();
        //check for STOP_BYTE in last character
        if (rawData[rawData.length - 1] != END_BYTE) {
            messageValid = false;
        }
        else {
            //decode message: get originalSentCMD and payload *
            commandByteName = cmdVals[cmdByteValue];
            if (commandByteName.includes("WRITE")) {
                //write acknowledge
                messageIsAck = true;
                ackCmdID = "WRITE_VARIABLE";
            }
            if (commandByteName.includes("ERROR")) {
                //error rx or acknowledge
                //messageIsAck = True;
                errorResponse = true;
                console.log("ERROR");
            }
            else if (commandByteName.includes("STREAM_DATA")) {
                //streaming data -> push to streaming model
                messageIsAck = false;
                streamObj["streamData"] = { A: undefined, B: undefined, C: undefined, D: undefined };
                var data = [0.0, 0.0, 0.0, 0.0];
                if (commandByteName.includes("1")) {
                    //1 variable streaming case
                    data[0] = dataView.getFloat32(2, true);
                    let dataIndex = 0;
                    for (let channel in this.enabledChannels) {
                        if (this.enabledChannels[channel]) {
                            streamObj.streamData[channel] = data[dataIndex];
                            LogDecodedData(data[dataIndex], `channel_${dataIndex + 1}`);
                            dataIndex++;
                        }
                    }
                }
                else if (commandByteName.includes("2")) {
                    //2 variable streaming case
                    data[0] = dataView.getFloat32(2, true);
                    data[1] = dataView.getFloat32(6, true);
                    let dataIndex = 0;
                    for (let channel in this.enabledChannels) {
                        if (this.enabledChannels[channel]) {
                            streamObj.streamData[channel] = data[dataIndex];
                            LogDecodedData(data[dataIndex], `channel_${dataIndex + 1}`);
                            dataIndex++;
                        }
                    }
                }
                else if (commandByteName.includes("3")) {
                    //3 variable streaming case
                    data[0] = dataView.getFloat32(2, true);
                    data[1] = dataView.getFloat32(6, true);
                    data[2] = dataView.getFloat32(10, true);
                    let dataIndex = 0;
                    for (let channel in this.enabledChannels) {
                        if (this.enabledChannels[channel]) {
                            streamObj.streamData[channel] = data[dataIndex];
                            LogDecodedData(data[dataIndex], `channel_${dataIndex + 1}`);
                            dataIndex++;
                        }
                    }
                }
                else if (commandByteName.includes("4")) {
                    data[0] = dataView.getFloat32(2, true);
                    data[1] = dataView.getFloat32(6, true);
                    data[2] = dataView.getFloat32(10, true);
                    data[3] = dataView.getFloat32(14, true);
                    let dataIndex = 0;
                    for (let channel in this.enabledChannels) {
                        if (this.enabledChannels[channel]) {
                            streamObj.streamData[channel] = data[dataIndex];
                            LogDecodedData(data[dataIndex], `channel_${dataIndex + 1}`);
                            dataIndex++;
                        }
                    }
                }
            }
            // polling data -> decode type and push to streaming model
            else if (commandByteName.includes("POLLING_DATA")) {
                messageIsAck = false;
                streamObj["rwVariables"] = {};
                let hashByteValue = rawData[2];
                let index = 0;
                let varType = "float";
                let incomingVariable = "";
                let readData = 0;
                for (let hashVar in this.hashTable) {
                    if (index === hashByteValue) {
                        varType = this.hashTable[hashVar].type;
                        incomingVariable = hashVar;
                        break;
                    }
                    index++;
                }
                if (varType === "bool") {
                    readData = dataView.getUint16(3, true);
                    streamObj.rwVariables[incomingVariable] = readData;
                    LogDecodedData(readData, incomingVariable);
                }
                else if (varType === "uint16") {
                    readData = dataView.getUint16(3, true);
                    streamObj.rwVariables[incomingVariable] = readData;
                    LogDecodedData(readData, incomingVariable);
                }
                else if (varType === "uint32") {
                    readData = dataView.getUint32(3, true);
                    streamObj.rwVariables[incomingVariable] = readData;
                    LogDecodedData(readData, incomingVariable);
                }
                else if (varType === "int16") {
                    readData = dataView.getInt16(3, true);
                    streamObj.rwVariables[incomingVariable] = readData;
                    LogDecodedData(readData, incomingVariable);
                }
                else if (varType === "int32") {
                    readData = dataView.getInt32(3, true);
                    streamObj.rwVariables[incomingVariable] = readData;
                    LogDecodedData(readData, incomingVariable);
                }
                else if (varType === "float") {
                    readData = dataView.getFloat32(3, true);
                    streamObj.rwVariables[incomingVariable] = readData;
                    LogDecodedData(readData, incomingVariable);
                }
                this.incomingBits = this.hashTable[incomingVariable]?.bits; // todo define type in hashtabletype
                if (this.incomingBits != undefined) {
                    for (let bitfield in this.hashTable[incomingVariable].bits) {
                        let mask = 0;
                        if (this.incomingBits[bitfield].length > 1) {
                            //bit range
                            for (let i = this.incomingBits[bitfield][0]; i <= this.incomingBits[bitfield][1]; i++) {
                                mask = mask | (1 << i);
                            }
                        }
                        else {
                            //one bit
                            mask = 1 << this.incomingBits[bitfield][0];
                        }
                        let maskedData = mask & readData;
                        let shiftedData = maskedData >> this.incomingBits[bitfield][0];
                        streamObj.rwVariables[bitfield] = shiftedData;
                        LogDecodedData(shiftedData, bitfield);
                    }
                }
            }
            else {
                //regular acknowledge
                messageIsAck = true;
                ackCmdID = commandByteName;
            }
        }
        //if is ack cmd, check corresponding id to acknowledgement is in the queue *
        //if has corresponding id, pop it from queue
        if (messageIsAck) {
            if (errorResponse) {
                //packet error was received -> resend cmd
                console.log(`cmd ${cmdByteValue.toString()} has returned an error`);
                commandByteName = "PACKET_ERROR";
                this.addErrorResponse("", cmdByteValue);
            }
            else if (messageValid) {
                //valid ack was received -> log response
                console.log(`cmd ${cmdByteValue.toString()} has been acknowledged`);
                if (cmdByteValue == 0x28) {
                    connected = true;
                }
                this.addResponse([], cmdByteValue); //not necessary to send back payload unless error cond
                if (ackCmdID == "CLEAR_STREAMING_PLOT") {
                    //Clear plot for new start of buffered data
                    clearScopeBuffer();
                }
            }
            else {
                //invalid message received -> throw away
                // console.log("message NOT valid: ");
                if (connected) {
                    console.log(`message NOT valid: ${rawData.toString()}`);
                }
                // this.console.log(rawData.toString())
            }
        }
        else {
            if (messageValid) {
                //streaming or polling data received
                return this.targetDecoder.decode(streamObj); //pushing directly to streaming model
            }
            else {
                //case should not happen
                console.log("message NOT valid and not an ack: ");
                console.log(rawData.toString());
            }
        }
        return true;
    }
    directWrite(hashVar, data) {
        let streamObj = {};
        streamObj["rwVariables"] = {};
        streamObj["rwVariables"][hashVar] = data;
        this.encode(streamObj);
    }
}
// Create a new instance of the codec
//new asmGUICodec({ id: "bin" });

const scopeJSONtoCSV_horizontal = (data) => {
    const replacer = (key, value) => (value == null ? "" : value); // specify how you want to handle null values here
    const header = Object.keys(data[0]);
    const csv = [...data.map((row) => header.map((fieldName) => JSON.stringify(row[fieldName], replacer)).join(","))].join("\r\n");
    const cleanedCsv = csv.replace(/\[|\]/g, "");
    return cleanedCsv;
};
const scopeJSONtoCSV_vertical = (data, capacity) => {
    let csv = "";
    for (let i = 0; i < data.length; i++) {
        csv += data[i].id + ",";
    }
    csv += "\r\n";
    for (let bufferIndex = 0; bufferIndex < capacity; bufferIndex++) {
        for (let channelIndex = 0; channelIndex < data.length; channelIndex++) {
            csv += (data[channelIndex].buffer[bufferIndex] === undefined ? "" : data[channelIndex].buffer[bufferIndex]) + ",";
        }
        csv += "\r\n";
    }
    return csv;
};
const labelArrayToString = (data) => {
    let tempString = "";
    data.forEach((item) => {
        tempString += `${item},`;
    });
    return tempString.replace(/,\s*$/, "");
};
const importCsv = (csv_data) => {
    const strDelimiter = ",";
    var objPattern = new RegExp(
    // Delimiters.
    "(\\" +
        strDelimiter +
        "|\\r?\\n|\\r|^)" +
        // Quoted fields.
        '(?:"([^"]*(?:""[^"]*)*)"|' +
        // Standard fields.
        '([^"\\' +
        strDelimiter +
        "\\r\\n]*))", "gi");
    var arrData = [[]];
    var arrMatches = null;
    // Keep looping over the regular expression matches
    // until we can no longer find a match.
    while ((arrMatches = objPattern.exec(csv_data))) {
        // Get the delimiter that was found.
        var strMatchedDelimiter = arrMatches[1];
        // Check to see if the given delimiter has a length
        // (is not the start of string) and if it matches
        // field delimiter. If id does not, then we know
        // that this delimiter is a row delimiter.
        if (strMatchedDelimiter.length && strMatchedDelimiter !== strDelimiter) {
            // Since we have reached a new row of data,
            // add an empty row to our data array.
            arrData.push([]);
        }
        var strMatchedValue;
        // Now that we have our delimiter out of the way,
        // let's check to see which kind of value we
        // captured (quoted or unquoted).
        if (arrMatches[2]) {
            // We found a quoted value. When we capture
            // this value, unescape any double quotes.
            strMatchedValue = arrMatches[2].replace(new RegExp('""', "g"), '"');
        }
        else {
            // We found a non-quoted value.
            strMatchedValue = arrMatches[3];
        }
        // Now that we have our value string, let's add
        // it to the data array.
        arrData[arrData.length - 1].push(strMatchedValue);
    }
    return arrData;
};
const scopeCSVtoArray = (csv_data) => {
    let arr = [];
    let quote = false; // 'true' means we're inside a quoted field
    // Iterate over each character, keep track of current row and column (of the returned array)
    for (let row = 0, col = 0, c = 0; c < csv_data.length; c++) {
        let cc = csv_data[c], nc = csv_data[c + 1]; // Current character, next character
        arr[row] = arr[row] || []; // Create a new row if necessary
        arr[row][col] = arr[row][col] || ""; // Create a new column (start with empty string) if necessary
        // If the current character is a quotation mark, and we're inside a
        // quoted field, and the next character is also a quotation mark,
        // add a quotation mark to the current column and skip the next character
        if (cc == '"' && quote && nc == '"') {
            arr[row][col] += cc;
            ++c;
            continue;
        }
        // If it's just one quotation mark, begin/end quoted field
        if (cc == '"') {
            quote = !quote;
            continue;
        }
        // If it's a comma and we're not in a quoted field, move on to the next column
        if (cc == "," && !quote) {
            ++col;
            continue;
        }
        // If it's a newline (CRLF) and we're not in a quoted field, skip the next character
        // and move on to the next row and move to column 0 of that new row
        if (cc == "\r" && nc == "\n" && !quote) {
            ++row;
            col = 0;
            ++c;
            continue;
        }
        // If it's a newline (LF or CR) and we're not in a quoted field,
        // move on to the next row and move to column 0 of that new row
        if (cc == "\n" && !quote) {
            ++row;
            col = 0;
            continue;
        }
        if (cc == "\r" && !quote) {
            ++row;
            col = 0;
            continue;
        }
        // Otherwise, append the current character to the current column
        arr[row][col] += cc;
    }
    let newArray = [];
    for (let col = 0; col < arr[0].length - 1; col++) {
        for (let row = 0; row < arr.length; row++) {
            newArray[row] = newArray[row] || []; // Create a new row if necessary
            newArray[col][row] = arr[row][col];
        }
        newArray[col].shift();
    }
    newArray = newArray.filter((value) => Object.keys(value).length !== 0);
    return newArray;
};
// const myCsvData = `Channel 1,Channel 2,Channel 3,Channel 4,
// 30,0.11920166015625,11.32220458984375,30.107816696166992,
// 30,0.08289337158203125,11.874977111816406,30.147125244140625,
// 30,0.0465850830078125,6.8430938720703125,29.82864761352539,
// 30,0.01027679443359375,-0.02419281005859375,29.731304168701172,
// 30,-0.08957290649414062,-8.805328369140625,29.779386520385742,
// 30,-1,-8,29,
// `
const delay = (time) => {
    return new Promise((resolve) => setTimeout(resolve, time));
};
const numDefinedElements = (record) => {
    let numDefined = 0;
    for (let key in record) {
        if (record[key] != undefined) {
            numDefined++;
        }
    }
    return numDefined;
};

const virtualScopeChannel1Color = "#ff7f0e";
const virtualScopeChannel2Color = "#2ca02c";
const virtualScopeChannel3Color = "#d62728";
const virtualScopeChannel4Color = "#9467bd";
const GUI_Layout = {
    "Home Page": { tab_number: 0 },
    "Firmware Build Page": { tab_number: 1 },
    "Advanced Motor Startup Page": { tab_number: 2 },
    "Tuning Page": { tab_number: 3 },
    "SysConfig Page": { tab_number: 4 },
    "Software Export Page": { tab_number: 5 },
};
const navigateToHomePage = () => {
    document.querySelector("#main_tab_container").index =
        GUI_Layout["Home Page"].tab_number;
};
const navigateToBuildPage = () => {
    document.querySelector("#main_tab_container").index =
        GUI_Layout["Firmware Build Page"].tab_number;
};
const navigateToAdvancedStartupPage = () => {
    document.querySelector("#main_tab_container").index =
        GUI_Layout["Advanced Motor Startup Page"].tab_number;
};
const navigateToTuningPage = () => {
    document.querySelector("#main_tab_container").index =
        GUI_Layout["Tuning Page"].tab_number;
};
const navigateToSysConfigPage = () => {
    document.querySelector("#main_tab_container").index =
        GUI_Layout["SysConfig Page"].tab_number;
};
const navigateToSoftwareExportPage = () => {
    document.querySelector("#main_tab_container").index =
        GUI_Layout["Software Export Page"].tab_number;
};

const registerClearWorkspaceCommand = (vScopeOnly) => {
    ActionRegistry.registerAction("cmd_clear_workspace", {
        run() {
            const myImportDialog = document.querySelector("#dialog_import");
            const myImportProgressBar = document.querySelector("#dialog_import_progressbar");
            myImportDialog.heading = "Deleting Project";
            myImportDialog.icon = "action:delete";
            myImportProgressBar.indeterminate = true;
            myImportProgressBar.message = "Deleting current project from workspace";
            myImportDialog.hidden = false;
            myImportDialog.open();
            let path = require("path");
            const fs = require("fs");
            const fsPromises = require("fs").promises;
            let processPathRuntime = path.join(process.execPath, "..", "..");
            let AppPath;
            if (GcUtils.isInDesigner || GcUtils.isInPreview) {
                AppPath = path.join(processPathRuntime, "..", "workspace", "asm-motorcontrol-gc-project");
            }
            else {
                AppPath = path.join(processPathRuntime, "..", "asm-motorcontrol-gc-project");
            }
            var app_workspace_path = path.join(AppPath, "build_workspace");
            fsPromises
                .rmdir(app_workspace_path, { recursive: true, force: true }, (err) => {
                if (err) {
                    throw err;
                }
                console.log(`${app_workspace_path} is deleted!`);
            })
                .then(() => {
                location.reload();
            });
        },
        isVisible() {
            return !vScopeOnly || false;
        },
    });
};
const registerOpenSoftwareExporter = (vScopeOnly) => {
    ActionRegistry.registerAction("cmd_software_exporter", {
        run() {
            const mySoftwareExportDialog = document.querySelector("#dialog_software_exporter");
            mySoftwareExportDialog.hidden = false;
            mySoftwareExportDialog.open();
            const myCloseDialogIcon = mySoftwareExportDialog.shadowRoot?.querySelector("#heading-icon");
            myCloseDialogIcon.style.cursor = "pointer";
        },
        isVisible() {
            return !vScopeOnly || false;
        },
    });
};
const registerImportHashTableCommand = (codecClassObject, vScopeOnly) => {
    ActionRegistry.registerAction("cmd_import_hash_table", {
        async run() {
            importHashTable();
        },
        isVisible() {
            return vScopeOnly || false;
        },
    });
};
const registerRestartCommand = () => {
    ActionRegistry.registerAction("cmd_restart", {
        run() {
            location.reload();
        },
    });
};
const registerExitCommand = () => {
    ActionRegistry.registerAction("cmd_exit", {
        run() {
            GcUtils.isNW ? require("nw.gui").Window.get().close() : window.close();
        },
    });
};
const registerEnableAllScopeChannelsCommand = () => {
    ActionRegistry.registerAction("cmd_toggle_on_all_channels", {
        run() {
            const myVScopeCh1Toggle = document.querySelector("#channel1_toggle");
            const myVScopeCh2Toggle = document.querySelector("#channel2_toggle");
            const myVScopeCh3Toggle = document.querySelector("#channel3_toggle");
            const myVScopeCh4Toggle = document.querySelector("#channel4_toggle");
            let scopeChToggleArray = [myVScopeCh1Toggle, myVScopeCh2Toggle, myVScopeCh3Toggle, myVScopeCh4Toggle];
            for (let scopeChToggleIdx = 0; scopeChToggleIdx < scopeChToggleArray.length; scopeChToggleIdx++) {
                scopeChToggleArray[scopeChToggleIdx].checked = true;
            }
            const myVScope = document.querySelector("#test_virtual_oscilloscope_plot");
            myVScope.triggerArmed = true;
            myVScope.triggerMode = "auto";
        },
    });
};
const registerDisableAllScopeChannelsCommand = () => {
    ActionRegistry.registerAction("cmd_toggle_off_all_channels", {
        run() {
            const myVScopeCh1Toggle = document.querySelector("#channel1_toggle");
            const myVScopeCh2Toggle = document.querySelector("#channel2_toggle");
            const myVScopeCh3Toggle = document.querySelector("#channel3_toggle");
            const myVScopeCh4Toggle = document.querySelector("#channel4_toggle");
            let scopeChToggleArray = [myVScopeCh1Toggle, myVScopeCh2Toggle, myVScopeCh3Toggle, myVScopeCh4Toggle];
            for (let scopeChToggleIdx = 0; scopeChToggleIdx < scopeChToggleArray.length; scopeChToggleIdx++) {
                scopeChToggleArray[scopeChToggleIdx].checked = false;
            }
        },
    });
};
const registerRunAutosetCommand = () => {
    ActionRegistry.registerAction("cmd_autoset", {
        run() {
            runAutoset();
        },
    });
};
const registerResetScopeViewCommand = () => {
    ActionRegistry.registerAction("cmd_reset_scope_view", {
        run() {
            const myVscope = document.querySelector("#test_virtual_oscilloscope_plot");
            const myVscopeCh1 = document.querySelector("#test_channel1_scope_input");
            const myVscopeCh2 = document.querySelector("#test_channel2_scope_input");
            const myVscopeCh3 = document.querySelector("#test_channel3_scope_input");
            const myVscopeCh4 = document.querySelector("#test_channel4_scope_input");
            let scopeChArray = [myVscopeCh1, myVscopeCh2, myVscopeCh3, myVscopeCh4];
            myVscope.horizontalPos = 0.0;
            myVscope.horizontalZoom = 0.0;
            myVscope.triggerLevel = 0.0;
            for (let scopeChIdx = 0; scopeChIdx < scopeChArray.length; scopeChIdx++) {
                scopeChArray[scopeChIdx].verticalPos = 0.0;
                scopeChArray[scopeChIdx].verticalScale = 0.0;
            }
            myVscope.refresh();
        },
    });
};
const registerClearScopeDataCommand = () => {
    ActionRegistry.registerAction("cmd_clear_scope_data", {
        run() {
            clearScopeBuffer();
        },
    });
};
const registerOpenWaveformAnalyzerCommand = () => {
    ActionRegistry.registerAction("cmd_waveform_analyzer", {
        run() {
            const myWaveformAnalyzer = document.querySelector("#waveform_analyzer_dialog");
            updateWaveformAnalyzer();
            myWaveformAnalyzer.hidden = false;
            myWaveformAnalyzer.open();
        },
    });
};
const registerImportScopeDataCommand = () => {
    ActionRegistry.registerAction("cmd_import_scope_data", {
        async run() {
            const myVscope = document.querySelector("#test_virtual_oscilloscope_plot");
            // const myGCWidgetPlot = myVscope.shadowRoot.querySelector("gc-widget-plot")!;
            // const myPlotlyBuffer = myGCWidgetPlot.shadowRoot.querySelector("#plot-div")!;
            const myImportData = document.querySelector("#export_data_dialog");
            const result = await myImportData.browseAndLoad(false);
            const fileContent = result[0];
            const scopeData = scopeCSVtoArray(fileContent);
            console.log(scopeData);
            // const myPlotData = await myVscope.copyCaptureBuffer();
            // let csv = scopeJSONtoCSV_vertical(myPlotData, myVscope.capacity);
            // myExportData.browseAndSave(csv, "motor_waveform_data.csv", "text/csv");
        },
        isVisible() {
            return false;
        },
    });
};
const registerExportScopeDataCommand = () => {
    ActionRegistry.registerAction("cmd_export_scope_data", {
        async run() {
            const myVscope = document.querySelector("#test_virtual_oscilloscope_plot");
            const myExportData = document.querySelector("#export_data_dialog");
            const myPlotData = await myVscope.copyCaptureBuffer();
            let csv = scopeJSONtoCSV_vertical(myPlotData, myVscope.capacity);
            myExportData.browseAndSave(csv, "motor_waveform_data.csv", "text/csv");
        },
    });
};
const registerDownloadScopeImageCommand = () => {
    ActionRegistry.registerAction("cmd_download_scope_image", {
        run() {
            alert("Image export not supported at this time.");
        },
        isVisible() {
            return false;
        },
    });
};
const registerOpenScopeSettingsCommand = () => {
    ActionRegistry.registerAction("cmd_scope_options", {
        run() {
            const myScopeSettingsDialog = document.querySelector("#scope_settings_dialog");
            myScopeSettingsDialog.hidden = false;
            myScopeSettingsDialog.open();
        },
    });
};
const registerOpenHelpGuideCommand = (vScopeOnly) => {
    ActionRegistry.registerAction("cmd_open_help_guide", {
        run() {
            const myHelpTabContainer = document.querySelector("#tab_container_help");
            const myHelpDialogContainer = document.querySelector("#dialog_help");
            myHelpTabContainer.index = 0;
            myHelpDialogContainer.hidden = false;
            myHelpDialogContainer.open();
        },
        isVisible() {
            return !vScopeOnly || false;
        },
    });
};
const initMenuBarConfig = () => {
    //
    // Query all HTML components and store in variables for easy access
    //
    const myMainTabContainer = document.querySelector("#main_tab_container");
    const myOscilloscopeMenuItem = document.querySelector("#mm_scope");
    //
    // Define util functions used later
    //
    const showMenuItem = (menuItem) => {
        menuItem.hidden = false;
    };
    const hideMenuItem = (menuItem) => {
        menuItem.hidden = true;
    };
    //
    // Initialize HTML elements to default states
    //
    // Hide Oscilloscope menu item on GUI launch
    hideMenuItem(myOscilloscopeMenuItem);
    //
    // Assign event listeners to widget components
    //
    myMainTabContainer.addEventListener("index-changed", () => {
        if (myMainTabContainer.index == GUI_Layout["Tuning Page"].tab_number) {
            // If tab is on scope page, then show Oscilloscope menu item
            showMenuItem(myOscilloscopeMenuItem);
        }
        else {
            // otherwise, hide Oscilloscope menu item
            hideMenuItem(myOscilloscopeMenuItem);
        }
    });
};
const registerOpenSettingsCommand = () => {
    ActionRegistry.registerAction("cmd_options", {
        run() {
            const mySettingsDialog = document.querySelector("#dialog_settings");
            mySettingsDialog.hidden = false;
            mySettingsDialog.open();
        },
    });
};

const initSettingsConfig = async () => {
    const mySettingsGrid = (await GcWidget.querySelector("#grid_settings"));
    const mySettingsSaveButton = document.querySelector("#dialog_settings_button_save");
    const myTheme = document.querySelector("#theme");
    const supportedThemes = ["GC Light Theme", "GC Dark Theme", "ASM Dark Theme"];
    const settingsProperties = [
        {
            id: "theme",
            caption: "Dark Mode",
            widgetType: "toggle",
            format: "boolean",
        },
        // {
        // 	id: "themeSelect",
        // 	caption: "Theme",
        // 	widgetType: "select",
        // 	options: supportedThemes,
        // 	format: "text",
        // },
    ];
    mySettingsGrid.propertyInfo = settingsProperties;
    // allow time for settingsGrid property to receive the settingsProperties
    await delay(100);
    const initDarkMode = GcLocalStorage.getItem("dark-mode");
    if (initDarkMode == "1") {
        setDarkTheme();
        mySettingsGrid.values.theme = true;
    }
    else {
        setLightTheme();
        mySettingsGrid.values.theme = false;
    }
    // mySettingsGrid.values.themeSelect = "GC Light Theme"
    const handlePropertyChange = () => {
        if (mySettingsGrid.values.theme == true) {
            setDarkTheme();
            GcLocalStorage.setItem("dark-mode", "1");
        }
        else {
            setLightTheme();
            GcLocalStorage.setItem("dark-mode", "0");
        }
        // console.log(`mySettingsGrid.values.themeSelect: ${mySettingsGrid.values.themeSelect}`);
        // myTheme.selectedThemeIndex = supportedThemes.indexOf(mySettingsGrid.values.themeSelect as string);
    };
    mySettingsGrid.addEventListener("property-value-changed", () => {
        handlePropertyChange();
    });
};
const setDarkTheme = () => {
    const documentRoot = document.querySelector(":root");
    documentRoot.style.setProperty("--styled-container-theme", "#333333");
    documentRoot.style.setProperty("--styled-container-shadow-theme", "#3c3c3c");
    documentRoot.style.setProperty("--disable-container-gray-theme", "rgba(20,20,20,0.5)");
    documentRoot.style.setProperty("--disable-container-white-theme", "rgba(256,256,256,0.25)");
    documentRoot.style.setProperty("--background-container-theme", "#1e1e1e");
    documentRoot.style.setProperty("--home-background-container-theme", "#1e1e1e");
    documentRoot.style.setProperty("--theme-font-color", "#cccccc");
    documentRoot.style.setProperty("--invert-image-theme", "invert(0)");
    documentRoot.style.setProperty("--dialog-background-theme", "#1e1e1e");
    /* Menubar */
    // documentRoot.style.setProperty("--menubar-text-theme", "#4d4d4d");
    documentRoot.style.setProperty("--menubar-theme", "#4d4d4d");
    // documentRoot.style.setProperty("--menubar-text-hover-theme", "#4d4d4d");
    // documentRoot.style.setProperty("--menubar-hover-theme", "#4d4d4d");
    /* Button */
    documentRoot.style.setProperty("--button-text-theme", "#fff");
    documentRoot.style.setProperty("--button-text-disabled-theme", "#fff");
    documentRoot.style.setProperty("--button-text-hover-theme", "#fff");
    documentRoot.style.setProperty("--button-background-theme", "#189");
    documentRoot.style.setProperty("--button-background-disabled-theme", "#555");
    documentRoot.style.setProperty("--button-background-hover-theme", "#3ab"); // TODO
    documentRoot.style.setProperty("--button-border-theme", "#189");
    documentRoot.style.setProperty("--button-border-disabled-theme", "#555");
    documentRoot.style.setProperty("--button-border-hover-theme", "#3ab"); // TODO
    documentRoot.style.setProperty("--theme-background-color", "#333333");
    documentRoot.style.setProperty("--gc-menuitem-background-color-hover", "#000");
    // documentRoot.style.setProperty("--gc-menuitem-color-hover", "");
    // documentRoot.style.setProperty("--gc-input-background-color", "");
    // documentRoot.style.setProperty("--gc-input-color", "");
    //--theme-background-color
    //--gc-background-color
};
const setLightTheme = () => {
    const documentRoot = document.querySelector(":root");
    documentRoot.style.setProperty("--styled-container-theme", "#fff");
    documentRoot.style.setProperty("--styled-container-shadow-theme", "#00000033");
    documentRoot.style.setProperty("--disable-container-gray-theme", "rgba(249,249,249,0.5)");
    documentRoot.style.setProperty("--disable-container-white-theme", "rgba(256,256,256,0.75)");
    documentRoot.style.setProperty("--background-container-theme", "#f9f9f9");
    documentRoot.style.setProperty("--home-background-container-theme", "#189");
    documentRoot.style.setProperty("--theme-font-color", "#555555");
    documentRoot.style.setProperty("--invert-image-theme", "invert(1)");
    documentRoot.style.setProperty("--dialog-background-theme", "#f9f9f9");
    /* Menubar */
    // documentRoot.style.setProperty("--menubar-text-theme", "#f9f9f9");
    documentRoot.style.setProperty("--menubar-theme", "#c00");
    // documentRoot.style.setProperty("--menubar-text-hover-theme", "#555");
    // documentRoot.style.setProperty("--menubar-hover-theme", "#f9f9f9");
    /* Button */
    documentRoot.style.setProperty("--button-text-theme", "#fff");
    documentRoot.style.setProperty("--button-text-disabled-theme", "#fff");
    documentRoot.style.setProperty("--button-text-hover-theme", "#fff");
    documentRoot.style.setProperty("--button-background-theme", "#c00");
    documentRoot.style.setProperty("--button-background-disabled-theme", "#ccc");
    documentRoot.style.setProperty("--button-background-hover-theme", "#e00");
    documentRoot.style.setProperty("--button-border-theme", "#c00");
    documentRoot.style.setProperty("--button-border-disabled-theme", "#ccc");
    documentRoot.style.setProperty("--button-border-hover-theme", "#e00");
    documentRoot.style.setProperty("--theme-background-color", "#fff");
    documentRoot.style.setProperty("--gc-menuitem-background-color-hover", "#eee");
    // documentRoot.style.setProperty("--gc-menuitem-color-hover", "");
    // documentRoot.style.setProperty("--gc-input-background-color", "");
    // documentRoot.style.setProperty("--gc-input-color", "");
};

const REGRESSION_HTML_HEADER = `
<!DOCTYPE html>
<html lang="en">
	<head>
		<meta charset="UTF-8">
		<style>
			.accordion > input[type="checkbox"] {
			position: absolute;
			left: -100vw;
			}
			.accordion .content {
			overflow-y: hidden;
			height: 0;
			transition: height 0.3s ease;
			}
			.accordion > input[type="checkbox"]:checked ~ .content {
			height: auto;
			overflow: visible;
			}
			.accordion label {
			display: block;
			}
			/*
			Styling
			*/
			body {
			font: 16px/1.5em "Overpass", "Open Sans", Helvetica, sans-serif;
			color: #333;
			font-weight: 300;
			}
			.accordion {
			margin-bottom: 1em;
			max-width: 65em;
			}
			.accordion > input[type="checkbox"]:checked ~ .content {
			padding: 15px;
			border: 2px solid #e8e8e8;
			border-top: 0;
			}
			.accordion .handle {
			margin: 0;
			font-size: 1.125em;
			line-height: 1.2em;
			}
			.accordion label {
			color: #333;
			cursor: pointer;
			font-weight: normal;
			padding: 15px;
			background: #e8e8e8;
			}
			.accordion label:hover,
			.accordion label:focus {
			background: #d8d8d8;
			}
			.accordion .handle label:before {
			font-family: 'fontawesome';
			content: "\f054";
			display: inline-block;
			margin-right: 10px;
			font-size: .58em;
			line-height: 1.556em;
			vertical-align: middle;
			}
			.accordion > input[type="checkbox"]:checked ~ .handle label:before {
			content: "\f078";
			}
		</style>
		<title>MCU Signal Sight Regression Report</title>
	</head>
	<body>
		<h1>MCU Signal Sight Regression Report</h1>
`;
const REGRESSION_HTML_FOOTER = `
</body>
</html>
`;
const custom_readJsonFile = async (file) => {
    return new Promise((resolve, reject) => {
        const reader = new FileReader();
        reader.onload = (event) => {
            try {
                resolve(JSON.parse(event.target?.result));
            }
            catch (error) {
                reject(new Error(`Error parsing JSON from ${file.name}`));
            }
        };
        reader.readAsText(file);
    });
};
const formatDate = (date) => {
    let hours = date.getHours();
    let minutes = date.getMinutes();
    let ampm = hours >= 12 ? "pm" : "am";
    hours = hours % 12;
    hours = hours ? hours : 12;
    minutes = minutes < 10 ? "0" + minutes : minutes;
    var strTime = hours + ":" + minutes + " " + ampm;
    return date.getMonth() + 1 + "/" + date.getDate() + "/" + date.getFullYear() + "  " + strTime;
};
const acceptMessageDialog = () => {
    const messageDialog = document.querySelector("gc-widget-message-dialog");
    const okButton = messageDialog?.shadowRoot?.querySelector(".message-ok");
    okButton.click();
};
const changeBaudRate = async (baudRate) => {
    const serialPortMenuAction = document.querySelector("#ma_serial_port");
    serialPortMenuAction.click();
    await delay(500);
    const portDialog = document.querySelector("gc-widget-port-selection-dialog");
    const baudRateSelect = portDialog?.shadowRoot?.querySelector(".baud-select");
    await delay(1000);
    for (let i = 0; i < 2; i++) {
        // baudRateSelect.click();
        // baudRateSelect.shadowRoot!.querySelector("gc-widget-input-filter")!.shadowRoot!.querySelector("gc-widget-input")!.value = baudRate;
        baudRateSelect.selectedValue = baudRate;
        const enterEvent = new KeyboardEvent("keydown", {
            key: "Enter",
            code: "Enter",
            which: 13,
            keyCode: 13,
            bubbles: true,
            cancelable: true,
        });
        baudRateSelect.shadowRoot.querySelector("gc-widget-input-filter").shadowRoot.querySelector("gc-widget-input").dispatchEvent(enterEvent);
        baudRateSelect.selectedValue = baudRate;
    }
    await delay(1000);
    const okButton = portDialog?.shadowRoot?.querySelector(".dialog-confirm");
    okButton.click();
};
const initRegressionValidation = () => {
    const myDevSettingsContainer = document.querySelector("#container_developer_settings");
    const myDevInput = document.querySelector("#dev_settings_pw_input");
    const myDevEnter = document.querySelector("#dev_settings_pw_button");
    const regressionReadWrites = document.querySelector("#page_validation_rw_container");
    const progressBar = document.querySelector("#page_validation_progressbar");
    const loader = document.querySelector("#loader");
    const myMainTabContainer = document.querySelector("#main_tab_container");
    const channel1Toggle = document.querySelector("#validation_channel1_toggle");
    const channel2Toggle = document.querySelector("#validation_channel2_toggle");
    const channel3Toggle = document.querySelector("#validation_channel3_toggle");
    const channel4Toggle = document.querySelector("#validation_channel4_toggle");
    setTimeout(() => {
        myDevInput.shadowRoot.querySelector("input")?.setAttribute("type", "password");
    }, 1000);
    const myValidationTestingPanel = document.querySelector("#page_validation_testing");
    if (GcUtils.isInDesigner || GcUtils.isInPreview) {
        myValidationTestingPanel.hidden = false;
    }
    else {
        myValidationTestingPanel.hidden = true;
    }
    myDevInput.addEventListener("keypress", (evt) => {
        if (evt.key === "Enter") {
            evt.preventDefault();
            myDevEnter.click();
        }
    });
    myDevEnter.onclick = () => {
        while (myDevSettingsContainer.childElementCount > 1) {
            myDevSettingsContainer.removeChild(myDevSettingsContainer.lastChild);
        }
        if (myDevInput.value == "MadeInSugarLand") {
            const myLabel = document.createElement("gc-widget-label");
            myLabel.label = "Correct password entered!";
            myLabel.style.margin = "7.5px 15px";
            myLabel.style.color = "green";
            myLabel.style.fontWeight = "bold";
            myDevSettingsContainer.appendChild(myLabel);
            myDevEnter.disabled = true;
            myMainTabContainer.position = "bottom";
            myValidationTestingPanel.hidden = false;
            setTimeout(() => {
                myDevSettingsContainer.removeChild(myLabel);
            }, 1000);
        }
        else {
            const myLabel = document.createElement("gc-widget-label");
            myLabel.label = "Incorrect Password";
            myLabel.style.margin = "7.5px 15px";
            myLabel.style.color = "red";
            myLabel.style.fontWeight = "bold";
            myDevSettingsContainer.appendChild(myLabel);
            setTimeout(() => {
                myDevSettingsContainer.removeChild(myLabel);
            }, 1000);
        }
    };
    //
    // Data Logging
    //
    const CheckboxRawData = document.querySelector("#page_validation_datalog_check_raw");
    const CheckboxDecodedData = document.querySelector("#page_validation_datalog_check_decoded");
    const InputRawDataPoints = document.querySelector("#page_validation_datalog_input_raw");
    const InputDecodedDataPoints = document.querySelector("#page_validation_datalog_input_decoded");
    const ButtonExportLoggedData = document.querySelector("#page_validation_datalog_button_export");
    const ExportValidationData = document.querySelector("#export_validation_data_dialog");
    const RadioGroup = document.querySelector("#page_validation_datalog_radio");
    const RadioSimple = document.querySelector("#page_validation_datalog_radio_simple");
    const RadioDetailed = document.querySelector("#page_validation_datalog_radio_detailed");
    CheckboxRawData.addEventListener("checked-changed", () => {
        if (CheckboxRawData.checked === true) {
            InputRawDataPoints.hidden = false;
            codec.logRawData = true;
            codec.rawDataBufferSize = 0;
        }
        else if (CheckboxRawData.checked === false) {
            InputRawDataPoints.hidden = true;
            codec.logRawData = false;
            InputRawDataPoints.value = "";
            codec.rawDataBufferSize = 0;
            codec.rawDataBuffer.length = 0;
        }
    });
    CheckboxDecodedData.addEventListener("checked-changed", () => {
        if (CheckboxDecodedData.checked === true) {
            InputDecodedDataPoints.hidden = false;
            codec.logDecodedData = true;
            codec.decodedDataBufferSize = 0;
            RadioGroup.hidden = false;
        }
        else if (CheckboxDecodedData.checked === false) {
            InputDecodedDataPoints.hidden = true;
            codec.logDecodedData = false;
            InputDecodedDataPoints.value = "";
            codec.decodedDataBufferSize = 0;
            codec.decodedDataBuffer.length = 0;
            for (let bucket in codec.decodedDataJSON) {
                codec.decodedDataJSON[bucket].length = 0;
            }
            RadioGroup.hidden = true;
        }
    });
    InputRawDataPoints.addEventListener("value-changed", () => {
        codec.rawDataBufferSize = InputRawDataPoints.value;
        if (codec.rawDataBuffer.length > codec.rawDataBufferSize) {
            codec.rawDataBuffer.length = InputRawDataPoints.value;
        }
    });
    InputDecodedDataPoints.addEventListener("value-changed", () => {
        codec.decodedDataBufferSize = InputDecodedDataPoints.value;
        if (codec.decodedDataBuffer.length > codec.decodedDataBufferSize) {
            codec.decodedDataBuffer.length = InputDecodedDataPoints.value;
        }
        for (let bucket in codec.decodedDataJSON) {
            codec.decodedDataJSON[bucket].length = InputDecodedDataPoints.value;
        }
    });
    RadioGroup.addEventListener("radio-button-changed", () => {
        codec.decodedDataFormat = RadioGroup.selectedLabel;
    });
    ButtonExportLoggedData.addEventListener("click", () => {
        if (CheckboxRawData.checked) {
            console.log(codec.rawDataBuffer);
            ExportValidationData.browseAndSave(codec.rawDataBuffer.join(), `SignalSight_RawData_${new Date().toJSON().slice(0, 10)}.txt`, "text/plain");
        }
        if (CheckboxDecodedData.checked) {
            if (RadioGroup.selectedLabel == "simple") {
                console.log(codec.decodedDataBuffer);
                ExportValidationData.browseAndSave(codec.decodedDataBuffer.join(), `SignalSight_DecodedData_${new Date().toJSON().slice(0, 10)}.txt`, "text/plain");
            }
            else if (RadioGroup.selectedLabel == "detailed") {
                console.log(codec.decodedDataJSON);
                ExportValidationData.browseAndSave(JSON.stringify(codec.decodedDataJSON), `SignalSight_DetailedDecodedData_${new Date().toJSON().slice(0, 10)}.json`, "application/json");
            }
        }
    });
    //
    // Test Customization
    //
    const TestCustomizationContainer = document.querySelector("#page_validation_custom_container");
    const CheckAll = document.querySelector("#page_validation_check_all");
    CheckAll.addEventListener("checked-changed", (evt) => {
        if (CheckAll.checked === true) {
            TestCustomizationContainer.querySelectorAll("gc-widget-checkbox").forEach((check) => {
                check.checked = true;
            });
        }
        else if (CheckAll.checked === false) {
            TestCustomizationContainer.querySelectorAll("gc-widget-checkbox").forEach((check) => {
                check.checked = false;
            });
        }
    });
    const folderInput = document.querySelector("#folderInput");
    const runRegressionTestButton = document.querySelector("#page_validation_run_button");
    runRegressionTestButton.disabled = true;
    folderInput.addEventListener("change", (evt) => {
        const files = folderInput.files;
        if (files?.length === 0) {
            runRegressionTestButton.disabled = true;
            console.log("No files selected.");
            return;
        }
        runRegressionTestButton.disabled = false;
    });
    runRegressionTestButton.addEventListener("click", async () => {
        // import fs and path modules
        const fs = require("fs");
        const path = require("path");
        // determine current path to gc runtime
        let processPathRuntime = path.join(process.execPath, "..", "..");
        let AppPath;
        if (GcUtils.isInDesigner || GcUtils.isInPreview) {
            AppPath = path.join(processPathRuntime, "..", "workspace", "MCU-Signal-Sight");
        }
        else {
            AppPath = path.join(processPathRuntime, "..", "MCU-Signal-Sight");
        }
        // in current director, create a fresh regressionBinaries folder
        // this folder will hold all the regression files that we copy into the gui
        if (fs.existsSync(`${AppPath}/regressionBinaries`))
            fs.rmdirSync(`${AppPath}/regressionBinaries`, { recursive: true, force: true });
        fs.mkdirSync(`${AppPath}/regressionBinaries`);
        // start progress bar for indicating status of regression test
        // todo - add deterministic progress
        progressBar.indeterminate = true;
        progressBar.message = "Running regression test...";
        const files = folderInput.files;
        if (files?.length === 0) {
            console.log("No files selected.");
            return;
        }
        // create folder object indexable by file name
        const folders = {};
        Array.from(files).forEach((file) => {
            const parts = file.webkitRelativePath.split("/");
            if (parts.length < 3)
                return;
            const subfolderName = parts[1];
            if (!folders[subfolderName]) {
                folders[subfolderName] = { files: {}, subfolderName };
            }
            folders[subfolderName].files[file.name] = file;
        });
        // console.log(folders);
        // configure the decoded data buffer so that we can compare data from each test in test suite
        codec.logDecodedData = true;
        codec.decodedDataFormat = "detailed";
        // define html output
        let htmlOutput = REGRESSION_HTML_HEADER;
        let currentDateTime = new Date();
        let dateTime = formatDate(currentDateTime);
        htmlOutput += `<p>Report Generated: ${dateTime}</p>`;
        let testNum = 1;
        if (!fs.existsSync(`${AppPath}/regressionLogs`))
            fs.mkdirSync(`${AppPath}/regressionLogs`);
        // for loop running through each of the test folders
        // each run of the loop is a single test containing 4 files
        // expected_data.json		- array containing the data that is being sent from the mcu, all channels send the same data
        // project.json				- information about the current test folder
        // signalsight_hash.json	- hash table that is read by the codec
        // binary.out				- project binary that is loaded onto the device using the program loader
        for (const folder in folders) {
            // console.log(`Processing folder: ${folder}`);
            const reader = new FileReader();
            let numDataPoints = 0;
            // get name of files based on the folder object
            const projectJson = folders[folder].files["project.json"];
            const signalSightJson = folders[folder].files["signalsight_hash.json"];
            const expectedDataJson = folders[folder].files["expected_data.json"];
            const programOut = folders[folder].files[`${folders[folder].subfolderName}.out`];
            htmlOutput += `<h2>Test No. ${testNum}: ${folders[folder].subfolderName}</h2>`;
            // read through project.json file
            if (projectJson) {
                const projectInfo = (await custom_readJsonFile(projectJson));
                // changeBaudRate(projectInfo.BAUD_RATE);
                numDataPoints = projectInfo.DEMO_DATA_POINTS;
                regressionReadWrites.innerHTML = "";
                // for (let i = 0; i < projectInfo.POLLING_TOTAL; i++) {
                // 	const inputElement = document.createElement("gc-widget-input");
                // 	inputElement.id = `input_${i}`;
                // 	regressionReadWrites.appendChild(inputElement);
                // }
                const hashTableInfo = (await custom_readJsonFile(signalSightJson));
                for (const hashVariable in hashTableInfo) {
                    if (hashTableInfo[hashVariable].page[0]) {
                        const inputElement = document.createElement("gc-widget-input");
                        inputElement.id = `input_${hashVariable}`;
                        regressionReadWrites.appendChild(inputElement);
                        // await bindingRegistry.waitForModelReady(`widget.${hashVariable}`);
                        // await bindingRegistry.waitForModelReady("rwVariables");
                        bindingRegistry.bind(`widget.input_${hashVariable}.value`, `streaming.rwVariables.${hashVariable}`);
                    }
                }
                if (regressionReadWrites.childElementCount != projectInfo.POLLING_TOTAL) {
                    console.error("Incorrect number of read/write variables found!");
                }
                htmlOutput += `
				<ul>
					<li>Streaming Channels: ${projectInfo.STREAMING_CHANNELS}</li>
					<li>32-Bit Polling Variables: ${projectInfo.POLLING_VARIABLES_32BIT}</li>
					<li>16-Bit Polling Variables: ${projectInfo.POLLING_VARIABLES_16BIT}</li>
					<li>Total Polling Variables: ${projectInfo.POLLING_TOTAL}</li>
					<li>Baud Rate: ${projectInfo.BAUD_RATE}</li>
					<li>Buffer Size: ${projectInfo.BUFFER_SIZE}</li>
					<li>Demo Data Points: ${projectInfo.DEMO_DATA_POINTS}</li>
					<li>Total Variables: ${projectInfo.TOTAL_VARIABLES}</li>
				</ul>
				`;
                console.log(projectInfo);
            }
            // assign hash table to codec
            if (signalSightJson) {
                codec.hashPath = signalSightJson.path;
            }
            // clear decoded data buffer and then assign buffer size equal to the number of data points being received
            codec.decodedDataJSON = {};
            codec.decodedDataBufferSize = numDataPoints;
            // load binary program onto the target device
            if (programOut) {
                fs.cpSync(programOut.path, `${AppPath}/regressionBinaries/${folder}.out`, { recursive: true });
                loader.programOrBinPath = `./regressionBinaries/${folder}.out`;
                setTimeout(() => {
                    acceptMessageDialog();
                }, 500);
                await loader.loadProgram();
                connectionManager.connect();
                await delay(6000);
            }
            // enable all toggles to trigger
            channel1Toggle.checked = true;
            channel2Toggle.checked = true;
            channel3Toggle.checked = true;
            channel4Toggle.checked = true;
            await delay(7500);
            connectionManager.disconnect();
            await delay(1000);
            htmlOutput += `
			<section class="accordion">
				<input type="checkbox" name="collapse" id="handle_${testNum}">
				<h2 class="handle">
					<label for="handle_${testNum}">Datapoints for ${folders[folder].subfolderName}</label>
				</h2>
				<div class="content">
			`;
            // read through project.json file
            // compare data from decoded data buffer with the expected data.json
            if (expectedDataJson) {
                const expectedData = (await custom_readJsonFile(expectedDataJson));
                for (let bucket in codec.decodedDataJSON) {
                    let numErrors = 0;
                    htmlOutput += `
					<section class="accordion">
						<input type="checkbox" name="collapse" id="handle_${testNum}_${bucket}">
						<h2 class="handle">
							<label for="handle_${testNum}_${bucket}">${bucket}</label>
						</h2>
						<div class="content">
							<table>
								<style>
									table { border-collapse: collapse; width: 100%; }
									th, td { padding: 8px 12px; border: 1px; solid #ccc; text-align: center; }
									tr { border: 1px solid black; }
									th { background-color: #f4f4f4; }
									.match { background-color: #d4edda; }
									.mismatch { background-color: #f8d7da; }
								</style>
								<thead>
									<tr>
										<td><strong>Label</strong></td>
										<td><strong>Index</strong></td>
										<td><strong>Expected</strong></td>
										<td><strong>Received</strong></td>
										<td><strong>Match (✅/❌)</strong></td>
									</tr>
								</thead>
								<tbody>

					`;
                    for (let i = 0; i < numDataPoints; i++) {
                        // compare the received data point with the expected data point. If they are not within 0.01 of each other, mark as error
                        if (Math.abs(codec.decodedDataJSON[bucket][i] - expectedData[i]) > 0.01) {
                            numErrors++;
                            htmlOutput += `
							<tr class="mismatch">
								<td>${bucket}</td>
								<td>${i}</td>
								<td>${expectedData[i]}</td>
								<td>${codec.decodedDataJSON[bucket][i]}</td>
								<td>❌</td>
							</tr>
						`;
                        }
                        else {
                            htmlOutput += `
							<tr class="match">								
								<td>${bucket}</td>
								<td>${i}</td>
								<td>${expectedData[i]}</td>
								<td>${codec.decodedDataJSON[bucket][i]}</td>
								<td>✅</td>
							</tr>
						`;
                        }
                    }
                    htmlOutput += `
								</tbody>
							</table>
						</div>
					</section>
					<p>Data mismatch on ${bucket}. Number of mismatches: ${numErrors}</p>
					`;
                    if (numErrors) {
                        console.error(`Data mismatch on ${bucket}. Number of mismatches: ${numErrors}`);
                    }
                }
            }
            htmlOutput += `
				</div>
			</section>
			`;
            testNum++;
        }
        htmlOutput += REGRESSION_HTML_FOOTER;
        const now = new Date();
        const formattedDateTime = now.toISOString().replace(/T/, "_").replace(/:/g, "-").replace(/\..+/, "");
        fs.writeFileSync(`${AppPath}/regressionLogs/SignalSight_RegressionLog_${formattedDateTime}.html`, htmlOutput);
        progressBar.indeterminate = false;
        progressBar.value = 100;
        progressBar.message = "Regression test completed";
    });
};
const RegressionTestProcedure = () => { };

console.log('types.ts is loaded...');

// async function main() {
const console$1 = new GcConsole("myapp"); // creates a console instance with name 'myapp'
GcConsole.setLevel("myapp", 4); // enable console output for myapp console instance
console$1.info("index.js is loaded...");
/**
 -------------------------------------------------------------------------------------------------------------------------------
Boilerplate code for databinding

Add custom computed value databindings here, using the following method:

syntax: bindingRegistry.bind(targetBinding, sourceBinding, [getter], [setter]);
    param targetBinding - single binding string or expression, or array of binding strings for multi-way binding.
    param sourceBinding - single binding string or expression, or array of binding strings for multi-way binding.
    param getter - (optional) - custom getter function for computing the targetBinding value(s) based on sourceBinding value(s).
    param setter - (optional) - custom setter function for computing the sourceBinding value(s) based on targetBinding value(s).

  (async () => {
      await bindingRegistry.waitForModelReady('widget');        // widget model, a built-in model
      await bindingRegistry.waitForModelReady('targetModelId'); // target model, gc-model-program, gc-model-streaming, etc...
      bindingRegistry.bind('widget.inputWidgetId.value', 'model.targetModelId.targetVariable');
      bindingRegistry.bind('widget.labelWidgetId.label', 'widget.inputWidgetId.value');
   })();
-------------------------------------------------------------------------------------------------------------------------------
**/
// just updated
// Example code:
//
const tempArray = [];
const listener = (event) => {
    {
        if (tempArray.length > 100)
            tempArray.shift();
        tempArray.push(event.data);
    }
};
(async () => {
    //     /* Wait for widget and target models to be ready */
    await bindingRegistry.waitForModelReady("widget");
    await bindingRegistry.waitForModelReady("streaming");
    //
    // bindingRegistry.getBinding(‘model.streaming.counter’).addEventListener(streamingDataEventType, listener);
    //     /* A simple computed values based on simple expression */
    //     bindingRegistry.bind('widget.id.propertyName', "targetModelId.targetVariable == 1 ? 'binding is one' : 'binding is not one'");
    //
    //     /* A custom two-way binding with custom getter and setter functions */
    //     /* (setter is optional and getter only indicates one-way binding)   */
    //     bindingRegistry.bind('widget.id.propertyName', 'targetModelId.targetVariable',
    //         value => { return value*5/9 + 32; }, /* getter */
    //         value => { return (value-32)*9/5; }  /* setter */
    //     );
    //
    //     /* 1 to n bindings */
    //     bindingRegistry.bind('widget.date.value', {
    //         /* Dependant bindings needed in order to compute the date, in name/value pairs */
    //             weekday: 'widget.dayOfWeek.selectedLabel',
    //             day: 'widget.dayOfMonth.value',
    //             month: 'widget.month.selectedLabel',
    //             year: 'widget.year.value'
    //         },
    //         /* Getter for date computation */
    //         function(values) {
    //             /* compute and return the string value to bind to the widget with id 'date' */
    //             return values.weekday + ', ' + values.month + ' ' + values.day + ', ' + values.year;
    //         }
    //     );
})();
/**
 -------------------------------------------------------------------------------------------------------------------------------
Boilerplate code for working with webcomponents in the application
-------------------------------------------------------------------------------------------------------------------------------
**/
const initVirtualOscopeOnly = async (codecClassObject) => {
    document.querySelector("#main_tab_container").addEventListener("index-changed", () => (document.querySelector("#mm_scope").hidden = false));
    document.querySelector("#mm_scope").hidden = false;
    const myDialogImportJSON = document.querySelector("#dialog_import_json");
    const myImportJSONButton = document.querySelector("#button_import_json");
    const myContinueButton = document.querySelector("#button_import_json_continue");
    const mySelectComPortButton = document.querySelector("#button_serial_port");
    myDialogImportJSON.open();
    myDialogImportJSON.hidden = false;
    myImportJSONButton.addEventListener("click", async () => {
        importHashTable();
    });
    myContinueButton.addEventListener("click", async () => {
        if (GcUtils.isCCS || GcUtils.isTheia) {
            myDialogImportJSON.close();
            myDialogImportJSON.hidden = true;
        }
        await connectionManager.disconnect();
        await connectionManager.connect();
    });
    mySelectComPortButton.addEventListener("click", async () => {
        const serialPortMenuAction = document.querySelector("#ma_serial_port");
        await connectionManager.disconnect();
        await connectionManager.connect();
        serialPortMenuAction.click();
    });
    // for (let activeTransport of connectionManager.getActiveTransports()) {
    // 	if (activeTransport.id == "xds") {
    // 		xdsTransport = activeTransport;
    // 		activeTransport.addEventListener(connectedStateChangedEventType, xdsTransportConnectionChangeHandler);
    // 	}
    // 	if (activeTransport.id == "usb") {
    // 		// console.log("activetransport: " + activeTransport.id + " " + activeTransport.state);
    // 		usbTransport = activeTransport;
    // 		activeTransport.addEventListener(connectedStateChangedEventType, usbTransportConnectionChangeHandler);
    // 	}
    // }
    connectionManager.addEventListener(connectedStateChangedEventType, (event) => {
        if (GcUtils.isCCS || GcUtils.isTheia) {
            // myDialogImportJSON.close();
            // myDialogImportJSON.hidden = true;
        }
        else {
            for (let activeTransport of connectionManager.getActiveTransports()) {
                if (activeTransport.id == "usb") {
                    if (event.newState === "connected" && activeTransport.isConnected) {
                        console$1.log("USB connected");
                        myDialogImportJSON.close();
                        myDialogImportJSON.hidden = true;
                    }
                }
            }
        }
        // if (event.newState === "connected") {
        // 	myDialogImportJSON.close();
        // 	myDialogImportJSON.hidden = true;
        // }
    });
    const hashTableCookie = GcLocalStorage.getItem("hash-table");
    // const path = require("path");
    // const fs = require("fs");
    // const processPathRuntime = path.join(process.execPath, "..", "..");
    let hashPath;
    const myPageTuning = document.querySelector("#page_tuning");
    const myMainTabContainer = document.querySelector("#main_tab_container");
    const myVScopeParentContainer = document.querySelector("#container_virtual_oscilloscope_parent");
    const myStatusBar = document.querySelector("#statusbar");
    // Remove unnecessary UI elements when in CCS due to space limitations
    if (GcUtils.isCCS || GcUtils.isTheia) {
        myPageTuning.hasHeading = false;
        myMainTabContainer.position = "none";
        myVScopeParentContainer.style.width = "100%";
        myVScopeParentContainer.style.margin = "0";
        myStatusBar.hidden = true;
    }
    else {
        myPageTuning.hasHeading = true;
        myMainTabContainer.position = "bottom";
        myVScopeParentContainer.style.width = "calc(100% - 30px)";
        myVScopeParentContainer.style.margin = "15px";
    }
    if (GcUtils.isInDesigner || GcUtils.isInPreview) {
        // hashPath = path.join(processPathRuntime, "..", "workspace", "MCU-Signal-Sight", "signalsight_hash.json");
    }
    else {
        // hashPath = path.join(processPathRuntime, "..", "MCU-Signal-Sight", "signalsight_hash.json");
    }
    let foundHash = true;
    let tryReadJson;
    try {
        tryReadJson = await GcFiles.readJsonFile("./signalsight_hash.json");
    }
    catch (error) {
        if (error == `Can't read file: ./signalsight_hash.json.  Status Code = 404`) {
            foundHash = false;
        }
    }
    if (foundHash) {
        myImportJSONButton.hidden = true;
        const fileContent = await GcFiles.readJsonFile("./signalsight_hash.json");
        GcLocalStorage.setItem("hash-table", JSON.stringify(fileContent));
        if (GcUtils.isCCS || GcUtils.isTheia) {
            myDialogImportJSON.heading = "Connect to the Device";
            myContinueButton.label = "Connect";
            myContinueButton.hidden = false;
            myDialogImportJSON.style.height = "500px";
            myDialogImportJSON.style.width = "700px";
            document.querySelector("#container_import_json").innerHTML =
                `<strong><ol>` +
                    `<li>Find the COM port number associated with the UART connection to the device <br><br></li>` +
                    `<ul>- This is often labeled as "USB Serial Port (COM#)" or "Application/User UART (COM#)" in your Device Manager application<br><br></ul>` +
                    `<li>Click the SELECT COM PORT button below<br><br></li>` +
                    `<li>Choose the COM port number associated with the UART connection from Step 1<br><br></li>` +
                    `<li>Ensure the baud rate matches the value supplied in the SysConfig tool<br><br></li>` +
                    `<li>Confirm the COM port and baud rate by clicking OK<br><br></li>` +
                    `<li>Click the CONNECT button to begin communicating with the device<br><br></li>` +
                    `</ol></strong>`;
        }
        else {
            myContinueButton.label = "Continue";
            myContinueButton.hidden = false;
            myDialogImportJSON.style.height = "300px";
            document.querySelector("#container_import_json").innerHTML =
                "<strong>Hash table file detected. Press the Continue button to connect to the device</strong><br>Ensure that your device is plugged into your computer and powered. If connection fails (in lower left hand corner), re-inspect setup to ensure proper hardware connection and attempt to reconnect.";
        }
    }
    else if (hashTableCookie !== null) {
        myDialogImportJSON.style.height = "300px";
        myContinueButton.hidden = false;
        document.querySelector("#container_import_json").innerHTML =
            "<strong>Continue with previous session or import a new .json hash table file?</strong><br>Ensure that your device is plugged into your computer and powered. If connection fails (in lower left hand corner), re-inspect setup to ensure proper hardware connection and attempt to reconnect.";
    }
    else {
        myContinueButton.hidden = true;
        document.querySelector("#container_import_json").innerHTML =
            "To utilize TI Signal Sight, a .json file containing the Hash Table needs to be imported. This file can be automatically generated through SysConfig.<br><br><img src='./assets/hashtable_sysconfig.png' alt='Hashtable SysConfig' width='375'><br>Ensure that your device is plugged into your computer and powered prior to importing the .json file. If connection fails (in lower left hand corner), re-inspect setup to ensure proper hardware connection and re-import the .json file.";
    }
};
const codec = new asmGUICodec({ id: "bin", hashPath: "./hash_table_build4_vib_comp.json", console: console$1 });
const init = () => {
    // window.moveTo(0, 0);
    // window.resizeTo(screen.availWidth, screen.availHeight);
    const VIRTUAL_OSCILLOSCOPE_ONLY = true;
    // Add menubar product-name-clicked event listener
    GcWidget.querySelector("gc-widget-menubar").then((menubar) => {
        menubar.addEventListener("product-name-clicked", () => window.open("https://dev.ti.com/gc", "gc"));
    });
    initScopeConfig();
    initMenuBarConfig();
    initSettingsConfig();
    registerAllMenuActions(codec, VIRTUAL_OSCILLOSCOPE_ONLY);
    initVirtualOscopeOnly(codec);
    initRegressionValidation();
    bindingRegistry.bind("widget.main_tab_container.index", "streaming.page");
};
document.readyState === "complete" ? init() : document.addEventListener("DOMContentLoaded", init);
/**
 -------------------------------------------------------------------------------------------------------------------------------
Boilerplate code for registering menu and toolbar action callback
-------------------------------------------------------------------------------------------------------------------------------
**/
const registerAllMenuActions = (customCodec, vScopeOnly) => {
    registerClearWorkspaceCommand(vScopeOnly);
    registerOpenSoftwareExporter(vScopeOnly);
    registerImportHashTableCommand(customCodec, vScopeOnly);
    registerRestartCommand();
    registerExitCommand();
    registerEnableAllScopeChannelsCommand();
    registerDisableAllScopeChannelsCommand();
    registerRunAutosetCommand();
    registerResetScopeViewCommand();
    registerClearScopeDataCommand();
    registerOpenWaveformAnalyzerCommand();
    registerImportScopeDataCommand();
    registerExportScopeDataCommand();
    registerDownloadScopeImageCommand();
    registerOpenScopeSettingsCommand();
    registerOpenHelpGuideCommand(vScopeOnly);
    registerOpenSettingsCommand();
};

export { codec };
//# sourceMappingURL=index.js.map
