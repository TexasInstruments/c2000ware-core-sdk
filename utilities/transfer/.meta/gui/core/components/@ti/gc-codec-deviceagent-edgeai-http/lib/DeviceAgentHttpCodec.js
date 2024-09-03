import { GcConsole } from '../../gc-core-assets/lib/GcConsole';
import { GcUtils } from '../../gc-core-assets/lib/GcUtils';
import { deviceAgentEncoderType, API_VERSION, DeviceAgentStreamingDataType, DeviceAgentPipeline, sensorErrorEventType, inferenceLogEventType, inferenceValuesEventType } from '../../gc-model-deviceagent-edgeai/lib/DeviceAgentModel';
import { AbstractCodec, nullDataCodec } from '../../gc-target-configuration/lib/TargetConfiguration';
import { multiPartStreamingType, networkTransportType, nullNetworkTransportEncoder } from '../../gc-transport-network/lib/NetworkTransport';

/**
 *  Copyright (c) 2023, Texas Instruments Incorporated
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
class DeviceAgentHttpCodec extends AbstractCodec {
    constructor(params) {
        super(params.id || 'deviceAgentHttp', multiPartStreamingType, networkTransportType, multiPartStreamingType, deviceAgentEncoderType);
        this.params = params;
        this.logger = new GcConsole('gc-codec-deviceagent-edgeai-http');
        this.targetDecoder = nullDataCodec;
        this.targetEncoder = nullNetworkTransportEncoder;
    }
    async getCapabilities() {
        const sensorResponse = await this.targetEncoder.httpRequest('GET', 'sensor', { timeout: 500 });
        return {
            deviceName: sensorResponse.data[0]?.device_name || this.params.defaultDeviceName,
            version: API_VERSION,
            upload: true,
            sdkVersion: sensorResponse.data[0]?.sdk_version,
            biDirectional: false,
            inference: true
        };
    }
    async listSensors() {
        const sensorResponse = await this.targetEncoder.httpRequest('GET', 'sensor', { timeout: 500 });
        const sensorDetails = sensorResponse.data ?? [];
        return sensorDetails.map(sensorDetail => {
            return {
                name: sensorDetail.name ?? 'Device Camera',
                type: DeviceAgentStreamingDataType.image,
                labels: { x: 'image' }
            };
        });
    }
    async startStreaming(imageTagId) {
        if (!this.activePipeline) {
            throw new Error('Pipeline on target device is not configured properly.');
        }
        const sensorResponse = await this.targetEncoder.httpRequest('GET', 'sensor', { timeout: 500 });
        const postSensorBody = sensorResponse.data.find(sensorData => sensorData.name === this.activeSensor);
        if (!postSensorBody) {
            throw new Error(`Device Camera ${this.activeSensor} is no longer available`);
        }
        const postSensorResponse = await this.targetEncoder.httpRequest('POST', 'sensor-session', { payload: postSensorBody });
        this.logger.debug(`postSensorResponse = ${postSensorResponse}`);
        const sensorDetails = postSensorResponse.data.sensor;
        const sessionDetails = { ...postSensorResponse.data.session, stream_type: 'image' };
        const putSensor = `sensor-session/${sessionDetails.id}`;
        const inference = this.activePipeline === DeviceAgentPipeline.SENSOR_DATA_ACQUISITION ? 'false' : 'true';
        const putSensorBody = { sensor: sensorDetails, session: sessionDetails, project: this.project, inference };
        const putSensorResponse = await this.targetEncoder.httpRequest('PUT', putSensor, { payload: putSensorBody, params: { id: sessionDetails.id } });
        this.activeStreamingSessionId = sessionDetails.id;
        // start a web socket to monitor webcam status
        this.activeWebcam = this.targetEncoder.createWebSocket(8000, 'ws/2/usbcam_status');
        this.activeWebcam.onmessage = (e) => {
            try {
                const response = JSON.parse(e.data);
                if (response !== 'AVAILABLE') {
                    throw new Error(`Device Camera ${this.activeSensor} is no longer available`);
                }
            }
            catch (error) {
                this.fireEvent(sensorErrorEventType, { name: this.activeSensor, message: error?.message ?? e.toString() });
            }
        };
        this.activeWebcam.onerror = (err) => {
            this.fireEvent(sensorErrorEventType, { name: this.activeSensor, message: err.message ?? err.data?.message ?? err.toString() });
        };
        this.activeWebcam.onclose = () => {
            this.activeWebcam = undefined;
        };
        if (inference) {
            this.activeInferenceLog = this.targetEncoder.createWebSocket(8000, 'ws/2/log');
            this.activeInferenceLog.onmessage = (e) => {
                const message = JSON.parse(e.data);
                this.fireEvent(inferenceLogEventType, { message });
            };
            this.activeInferenceLog.onerror = (e) => {
                this.logger.error(`Inference log error: ${e.message ?? e.data?.message ?? e.toString()}`);
            };
            this.activeInferenceLog.onclose = () => {
                this.activeInferenceLog = undefined;
            };
            this.activeInferenceValues = this.targetEncoder.createWebSocket(8000, 'ws/2/inference');
            this.activeInferenceValues.onmessage = (e) => {
                this.fireEvent(inferenceValuesEventType, { inferenceValues: JSON.parse(e.data) });
            };
            this.activeInferenceValues.onerror = (e) => {
                this.logger.error(`Inference values error: ${e.message ?? e.data?.message ?? e.toString()}`);
            };
            this.activeInferenceLog.onclose = () => {
                this.activeInferenceValues = undefined;
            };
        }
        const urlPath = `raw_imagestream/${sessionDetails.id}${this.activePipeline === DeviceAgentPipeline.SENSOR_DATA_ACQUISITION ? 'raw' : 'inference'}`;
        const port = 8080;
        const useCloudAgent = GcUtils.isCloud && document.location.protocol.startsWith('https') && document.location.hostname.endsWith('.ti.com');
        if (useCloudAgent || !imageTagId) {
            this.activeImageTagId = imageTagId;
            await this.targetEncoder.startStreaming('GET', urlPath, { port });
        }
        else if (imageTagId) {
            this.activeImageTagId = undefined;
            const imgElement = document.querySelector(imageTagId);
            if (!imgElement) {
                throw new Error(`Programmer error: querySelector('#${imageTagId}' was not found.`);
            }
            // bypass network transport. Let the image element do everything for us.
            imgElement.src = `http://${this.ipAddress}:${port}/${urlPath}`;
        }
    }
    decode(multiPart) {
        const imgElement = this.activeImageTagId && document.querySelector(`#${this.activeImageTagId}`);
        if (imgElement) {
            imgElement.src = `data:${multiPart.type};base64,${btoa(multiPart.data)}`;
            return true;
        }
        return this.targetDecoder.decode(multiPart);
    }
    async stopStreaming() {
        if (!this.activeStreamingSessionId) {
            return;
        }
        if (this.activeWebcam) {
            this.activeWebcam.close();
            this.activeWebcam = undefined;
        }
        if (this.activeInferenceLog) {
            this.activeInferenceLog.close();
            this.activeInferenceLog = undefined;
        }
        if (this.activeInferenceValues) {
            this.activeInferenceValues.close();
            this.activeInferenceValues = undefined;
        }
        const dePipe = `sensor-session/${this.activeStreamingSessionId}/dpipe`;
        const dePipeResp = await this.targetEncoder.httpRequest('DELETE', dePipe, { timeout: 1000 });
        const stopStreamResponse = await this.targetEncoder.httpRequest('GET', 'test', { port: 8080, timeout: 1000 });
        this.activeImageTagId = undefined;
    }
    async configurePipeline(configuration, modelName, sensorName) {
        this.activePipeline = undefined;
        if (modelName && this.activeModel?.name !== modelName) {
            throw new Error(`Target device does not have a model named ${modelName}`);
        }
        switch (configuration) {
            case DeviceAgentPipeline.SENSOR_DATA_ACQUISITION:
            case DeviceAgentPipeline.SENSOR_DATA_INFERENCING: {
                if (sensorName === undefined) {
                    throw new Error('Missing sensorName for configuring the pipeline');
                }
                break;
            }
            default:
                throw new Error('Method not implemented.');
        }
        this.activePipeline = configuration;
        this.activeSensor = sensorName;
    }
    async listModels() {
        // TODO support more than just one model at a time.
        if (this.activeModel) {
            return [this.activeModel];
        }
        return [];
    }
    async uploadModel(model, data) {
        this.activeModel = model;
        const project = this.project;
        const formData = { key: 'file', value: data, options: { filename: 'blob' } };
        await this.targetEncoder.httpRequest('POST', 'project', { payload: project });
        await this.targetEncoder.httpRequest('POST', `project/${project.id}/model`, { formData: [formData] });
    }
    removeModel(name) {
        if (this.activeModel?.name === name) {
            this.activeModel = undefined;
        }
        throw new Error('Removing a model is not yet supported in device agent.');
    }
    setProperty(name, value) {
        throw new Error('Inference properties are not yet supported in device agent.');
    }
    getProperty(name) {
        throw new Error('Inference properties are not yet supported in device agent.');
    }
    encode(data) {
        throw new Error('Bi-directional streaming is not supported in device agent.');
    }
    async ping() {
        await this.getCapabilities();
    }
    async onConnect(logger) {
        try {
            const result = await this.getCapabilities();
            this.deviceName = result.deviceName;
        }
        catch (e) {
            throw new Error(`Cannot connect to device agent at ${this.ipAddress}.  Please ensure device agent is running at this IP address.`);
        }
    }
    get project() {
        return {
            id: this.activeModel?.projectId ?? 'default',
            name: this.activeModel?.projectId ?? 'name',
            sensor: 'sensor',
            task_type: this.activeModel?.task ?? 'classification',
            model: this.activeModel?.name ?? 'unknown',
            target_device: this.deviceName,
            model_file: 'model_file',
            model_file_checksum: 'model_checksum'
        };
    }
    get ipAddress() {
        return this.targetEncoder.ipAddress;
    }
}

export { DeviceAgentHttpCodec };
//# sourceMappingURL=DeviceAgentHttpCodec.js.map
