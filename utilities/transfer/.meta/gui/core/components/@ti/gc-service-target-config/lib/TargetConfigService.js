import { GcUtils } from '../../gc-core-assets/lib/GcUtils';
import { GcConsole } from '../../gc-core-assets/lib/GcConsole';
import { ServiceType, ServicesRegistry } from '../../gc-core-services/lib/ServicesRegistry';
import { Events } from '../../gc-core-assets/lib/Events';

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
const MODULE_NAME = 'gc-service-target-configuration';
const console = new GcConsole(MODULE_NAME);
const targetConfigServiceType = new ServiceType(MODULE_NAME);
class TargetConfigService extends Events {
    constructor() {
        super();
        if (GcUtils.isNodeJS) {
            const path = require('path');
            const TargetConfig = require('./internal/TargetConfig').TargetConfig;
            this.targetConfig = new TargetConfig(path.resolve(__dirname, GcUtils.runtimeRoot));
        }
    }
    async getConnectionXml(connectionName) {
        const configInfo = await this.getConfigInfo();
        const result = configInfo?.connections.find(connection => connection.id === connectionName);
        return result?.xmlFile;
    }
    async getBoardOrDeviceXml(boardOrDeviceName) {
        const boardsAndDevicesList = await this.getBoardsAndDevices();
        const result = boardsAndDevicesList.find(boardOrDevice => boardOrDevice.id === boardOrDeviceName);
        if (!result) {
            return {};
        }
        return { xmlPath: `${result.type}s`, xmlFile: result?.xmlFile };
    }
    get ticloudagentPrefix() {
        let serverUriPrefix = '';
        if (GcUtils.isTheia && GcUtils.isElectron) {
            serverUriPrefix = `http://127.0.0.1:${window.BACKEND_PORT}`;
        }
        return serverUriPrefix + '/ticloudagent';
    }
    async getConfigInfo() {
        console.logAPI(this.getConfigInfo.name, ...arguments);
        if (this.configInfoCache) {
            return this.configInfoCache;
        }
        let jsonText;
        if (GcUtils.isNodeJS && this.targetConfig) {
            jsonText = await this.targetConfig.getConfigInfo(GcUtils.OS);
        }
        else {
            const response = await fetch(`${this.ticloudagentPrefix}/getConfigInfo?os=${GcUtils.OS}`);
            if (!response.ok) {
                throw new Error(response.statusText);
            }
            jsonText = await response.text();
        }
        this.configInfoCache = JSON.parse(jsonText);
        this.configInfoCache.connections.forEach(connection => connection.type = 'connection');
        this.configInfoCache.devices.forEach(device => device.type = 'device');
        this.configInfoCache.boards.forEach(board => board.type = 'board');
        return this.configInfoCache;
    }
    async getConfig(connectionName, deviceName) {
        console.logAPI(this.getConfig.name, ...arguments);
        const connectionXml = connectionName.endsWith('.xml') ? connectionName : await this.getConnectionXml(connectionName);
        const { xmlPath, xmlFile } = await this.getBoardOrDeviceXml(deviceName);
        if (connectionXml && xmlFile && xmlPath) {
            if (GcUtils.isNodeJS && this.targetConfig) {
                return await this.targetConfig?.getConfig(GcUtils.OS, connectionXml, xmlPath, xmlFile);
            }
            else {
                const response = await fetch(`${this.ticloudagentPrefix}/getConfig/${GcUtils.OS}/${connectionXml}/${xmlPath}/${xmlFile}`);
                if (!response.ok) {
                    throw new Error(response.statusText);
                }
                return await response.text();
            }
        }
        else {
            throw Error('Invalid connection, board, or device name');
        }
    }
    async getBoardsAndDevices() {
        console.logAPI(this.getBoardsAndDevices.name, ...arguments);
        if (this.configBoardsAndDevicesCache) {
            return this.configBoardsAndDevicesCache;
        }
        const info = await this.getConfigInfo();
        this.configBoardsAndDevicesCache = [...info.devices, ...info.boards];
        return this.configBoardsAndDevicesCache;
    }
    async getConnections(boardOrDeviceName) {
        console.logAPI(this.getConnections.name, ...arguments);
        const connections = new Array();
        const availableConnections = (await this.getConfigInfo()).connections;
        const boardsAndDevices = await this.getBoardsAndDevices();
        for (let i = 0; i < boardsAndDevices.length; ++i) {
            const device = boardsAndDevices[i];
            if (device.id === boardOrDeviceName) {
                device.connectionIndices.forEach(index => connections.push(availableConnections[index]));
            }
        }
        if (connections.length > 0) {
            return connections;
        }
        throw Error('Invalid board or device name');
    }
    async getDefaultConnection(deviceName) {
        console.logAPI(this.getDefaultConnection.name, ...arguments);
        const info = await this.getConfigInfo();
        for (let i = 0; i < info.devices.length; ++i) {
            const device = info.devices[i];
            if (device.id === deviceName) {
                return info.connections[device.defaultConnectionIndex];
            }
        }
        throw Error('Invalid board or device name');
    }
    addCpuPropertiesToCCxmlFile(ccxmlFileContents, deviceName, cpuProperties) {
        console.logAPI(this.addCpuPropertiesToCCxmlFile.name, ...arguments);
        // only fix up the ccxml file if it doesn't include a <cpu tag
        if (ccxmlFileContents.indexOf('<cpu') < 0) {
            // Split the ccxml file after the <instance ... tag for the device, i.e. before the </platform> tag
            const splitIndex = ccxmlFileContents.indexOf('</platform>');
            if (splitIndex > 0) {
                const ccxmlStrPart1 = ccxmlFileContents.substring(0, splitIndex);
                const ccxmlStrPart2 = ccxmlFileContents.substring(splitIndex);
                let ccxmlStrInsert = '';
                // the id used for the <instance tag must be used for the device tag or the ccxml file will not parse properly
                let instanceId = deviceName;
                const instanceIdIndex = ccxmlStrPart1.lastIndexOf('id="');
                if (instanceIdIndex >= 0) {
                    instanceId = ccxmlStrPart1.substring(instanceIdIndex + 'id="'.length);
                    instanceId = instanceId.substring(0, instanceId.indexOf('"'));
                }
                const deviceNameUC = deviceName.toUpperCase();
                if ((deviceNameUC.indexOf('MSP430') >= 0) || (deviceNameUC.indexOf('RF430') >= 0) || (deviceNameUC.indexOf('CC43') >= 0)) {
                    ccxmlStrInsert = '<device HW_revision="1.0" XML_version="1.2" description="%DEVICE%" id="' + instanceId + '" partnum="%DEVICE%">\n' +
                        '<cpu HW_revision="1.0" XML_version="1.2" description="MSP430 CPU" id="MSP430" isa="MSP430">\n' +
                        '%CPU_PROPERTIES%' +
                        '</cpu>\n' +
                        '</device>\n';
                }
                else if ((deviceNameUC.indexOf('MSP432') >= 0) || (deviceNameUC.indexOf('TM4C') >= 0)) {
                    ccxmlStrInsert = '<device HW_revision="1" XML_version="1.2" description="ARM Cortex-M4F MCU" id="' + instanceId + '" partnum="%DEVICE%">\n' +
                        '<router HW_revision="1.0" XML_version="1.2" description="CS_DAP Router" id="CS_DAP_0" isa="CS_DAP">\n' +
                        '<subpath id="subpath_0">\n' +
                        '<cpu HW_revision="1.0" XML_version="1.2" description="Cortex M4 CPU" id="CORTEX_M4_0" isa="CORTEX_M4">\n' +
                        '%CPU_PROPERTIES%' +
                        '</cpu>\n' +
                        '</subpath>\n' +
                        '</router>\n' +
                        '</device>\n';
                }
                else if (deviceNameUC.indexOf('TMS320F28') >= 0) {
                    ccxmlStrInsert = '<device HW_revision="1" XML_version="1.2" description="" id="' + instanceId + '" partnum="%DEVICE%">\n' +
                        '<router HW_revision="1.0" XML_version="1.2" description="ICEPick_C router" id="IcePick_C_0" isa="ICEPICK_C">\n' +
                        '<subpath id="Subpath_0">\n' +
                        '<cpu HW_revision="1.0" XML_version="1.2" description="C28xx CPU" id="C28xx_CPU1" isa="TMS320C28XX">\n' +
                        '%CPU_PROPERTIES%' +
                        '</cpu>\n' +
                        '</subpath>\n' +
                        '</router>\n' +
                        '</device>\n';
                }
                else if (deviceNameUC.indexOf('TMS320C28') >= 0) {
                    ccxmlStrInsert = '<device HW_revision="1" XML_version="1.2" description="" id="' + instanceId + '" partnum="%DEVICE%">\n' +
                        '<cpu HW_revision="1.0" XML_version="1.2" description="CPU" id="C2800" isa="TMS320C28XX">\n' +
                        '%CPU_PROPERTIES%' +
                        '</cpu>\n' +
                        '</device>\n';
                }
                else if ((deviceNameUC.indexOf('CC13') >= 0) || (deviceNameUC.indexOf('CC26') >= 0)) {
                    ccxmlStrInsert = '<device HW_revision="1" XML_version="1.2" description="SimpleLink(TM) %DEVICE% wireless MCU" id="' + instanceId + '" partnum="%DEVICE%">\n' +
                        '<router HW_revision="1.0" XML_version="1.2" description="ICEPick_C Router" id="IcePick_C_0" isa="ICEPICK_C">\n' +
                        '<subpath id="subpath_0">\n' +
                        '<router HW_revision="1.0" XML_version="1.2" description="CS_DAP Router" id="CS_DAP_0" isa="CS_DAP">\n' +
                        '<subpath id="subpath_1">\n' +
                        '<cpu HW_revision="1.0" XML_version="1.2" description="Cortex_M3 CPU" id="Cortex_M3_0" isa="Cortex_M3">\n' +
                        '%CPU_PROPERTIES%' +
                        '</cpu>\n' +
                        '</subpath>\n' +
                        '</router>\n' +
                        '</subpath>\n' +
                        '</router>\n' +
                        '</device>\n';
                }
                else if (deviceNameUC.indexOf('F28M') >= 0) {
                    ccxmlStrInsert = '<device HW_revision="1" XML_version="1.2" description="" id="' + instanceId + '" partnum="%DEVICE%">\n' +
                        '<router HW_revision="1.0" XML_version="1.2" description="ICEPick_C router" id="IcePick_C_0" isa="ICEPICK_C">\n' +
                        '<subpath id="C28x">\n' +
                        '<property Type="numericfield" Value="0x11" desc="Port Number_0" id="Port Number"/>\n' +
                        '<cpu HW_revision="1.0" XML_version="1.2" description="C28xx CPU" id="C28xx_0" isa="TMS320C28XX">\n' +
                        '%CPU_PROPERTIES%' +
                        '</cpu>\n' +
                        '</subpath>\n' +
                        '</router>\n' +
                        '</device>\n';
                }
                if (ccxmlStrInsert.length > 0 && deviceName) {
                    ccxmlStrInsert = ccxmlStrInsert.replace(/%DEVICE%/g, deviceName);
                    ccxmlStrInsert = ccxmlStrInsert.replace(/%CPU_PROPERTIES%/g, cpuProperties);
                    ccxmlFileContents = ccxmlStrPart1 + ccxmlStrInsert + ccxmlStrPart2;
                }
            }
        }
        return ccxmlFileContents;
    }
    async getFile(resourcePath) {
        console.logAPI(this.getFile.name, ...arguments);
        if (GcUtils.isNodeJS && this.targetConfig) {
            return await this.targetConfig.getFile(GcUtils.OS, resourcePath);
        }
        else {
            const response = await fetch(`${this.ticloudagentPrefix}/getFile/${GcUtils.OS}/${resourcePath}/LATEST`);
            if (!response.ok) {
                throw new Error(response.statusText);
            }
            return await response.text();
        }
    }
    parseConfig(ccxmlFileContents) {
        let result = undefined;
        if (GcUtils.isNodeJS && this.targetConfig) {
            result = this.targetConfig.parseConfig(ccxmlFileContents);
        }
        else {
            result = new DOMParser().parseFromString(ccxmlFileContents, 'text/xml');
        }
        return result;
    }
    formatRoot(doc) {
        const root = doc.documentElement;
        if (root.previousSibling && root.previousSibling.nodeType !== root.TEXT_NODE) {
            doc.insertBefore(doc.createTextNode('\n'), root);
        }
        this.formatChildren(doc, '\n', root);
    }
    formatChildren(doc, indent, node) {
        let child = node.firstChild;
        const childIndent = indent + '    ';
        while (child) {
            if (child.nodeType === node.ELEMENT_NODE && child.previousSibling?.nodeType !== node.TEXT_NODE) {
                node.insertBefore(doc.createTextNode(childIndent), child);
            }
            this.formatChildren(doc, childIndent, child);
            child = child.nextSibling;
        }
        if (node.lastChild?.nodeType === node.ELEMENT_NODE) {
            node.appendChild(doc.createTextNode(indent));
        }
    }
    serializeConfig(ccxmlDocument) {
        let result = undefined;
        this.formatRoot(ccxmlDocument);
        if (GcUtils.isNodeJS && this.targetConfig) {
            result = this.targetConfig.serializeConfig(ccxmlDocument);
        }
        else {
            result = new XMLSerializer().serializeToString(ccxmlDocument);
        }
        return result;
    }
}
ServicesRegistry.register(targetConfigServiceType, TargetConfigService);

export { TargetConfigService, targetConfigServiceType };
//# sourceMappingURL=TargetConfigService.js.map
