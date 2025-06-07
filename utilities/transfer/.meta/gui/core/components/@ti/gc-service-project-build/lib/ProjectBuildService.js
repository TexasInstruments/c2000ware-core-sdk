import { ServiceType, ServicesRegistry } from '../../gc-core-services/lib/ServicesRegistry';
import { GcUtils } from '../../gc-core-assets/lib/GcUtils';
import { GcFiles } from '../../gc-core-assets/lib/GcFiles';
import { GcConsole } from '../../gc-core-assets/lib/GcConsole';

/**
 *  Copyright (c) 2024 Texas Instruments Incorporated
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
class DesktopProjectBuildService {
    constructor() {
        this.logger = new GcConsole('gc-service-project-build');
        this.child_process = require('child_process');
        this.path = require('path');
        this.fs = require('fs');
        this.workspaceDirectory = 'workspace';
        this.testWorkspaceDirectory = 'test_workspace';
    }
    async getPathToProjectWorkspace() {
        return GcUtils.isNodeJS ? this.path.resolve(__dirname, '..', '..', 'test', this.testWorkspaceDirectory) : this.path.join(GcUtils.getApplicationRoot(await GcFiles.getProjectName()), this.workspaceDirectory);
    }
    async getPaths() {
        let pathToCcsProjectCli = GcUtils.OS === 'osx' ? this.path.join(GcUtils.runtimeRoot, '..', 'deskdb', 'content', 'TICloudAgent', 'osx', 'ccs-server.app', 'Contents', 'MacOS') :
            `${GcUtils.runtimeRoot}/deskdb/content/TICloudAgent/${GcUtils.OS}/eclipse`;
        if (GcUtils.isNodeJS) {
            // for testing
            pathToCcsProjectCli = this.path.resolve(__dirname, '..', pathToCcsProjectCli);
        }
        const pathToProjectWorkspace = await this.getPathToProjectWorkspace();
        return { pathToProjectWorkspace, pathToCcsProjectCli };
    }
    async runCommand(commandToRun, pathToCcsProjectCli, loggerHandler) {
        const runCommand = this.child_process.exec(commandToRun, { cwd: pathToCcsProjectCli });
        runCommand.stdout.on('data', (data) => {
            loggerHandler(data);
        });
        runCommand.stderr.on('data', (data) => {
            loggerHandler(data);
        });
        return new Promise((resolve, reject) => {
            runCommand.on('error', (err) => reject(err));
            runCommand.on('exit', () => {
                resolve();
            });
        });
    }
    async importProject(sdkPath, projectSpec, loggerHandler) {
        const { pathToProjectWorkspace, pathToCcsProjectCli } = await this.getPaths();
        if (!this.fs.existsSync(pathToProjectWorkspace)) {
            this.fs.mkdir(pathToProjectWorkspace, (err) => {
                if (err) {
                    return new Error('Could not create workspace directory');
                }
            });
        }
        const SDKProjectLocation = this.path.join(sdkPath, projectSpec);
        const importCommand = GcUtils.OS === 'win' ? `ccs-server-cli -workspace ${pathToProjectWorkspace} -application com.ti.ccs.apps.importProject -ccs.location ${SDKProjectLocation} -ccs.overwrite` :
            `./ccs-server-cli.sh -workspace ${pathToProjectWorkspace} -application com.ti.ccs.apps.importProject -ccs.location ${SDKProjectLocation} -ccs.overwrite`;
        this.logger.log('Running command: ' + importCommand);
        return this.runCommand(importCommand, pathToCcsProjectCli, loggerHandler);
    }
    async buildProject(projectName, buildConfiguration, loggerHandler) {
        const { pathToProjectWorkspace, pathToCcsProjectCli } = await this.getPaths();
        const buildCommand = GcUtils.OS === 'win' ? `ccs-server-cli -workspace ${pathToProjectWorkspace} -application com.ti.ccs.apps.buildProject -ccs.projects ${projectName} -ccs.configuration ${buildConfiguration}` :
            `./ccs-server-cli.sh -workspace ${pathToProjectWorkspace} -application com.ti.ccs.apps.buildProject -ccs.projects ${projectName} -ccs.configuration ${buildConfiguration}`;
        this.logger.log('Running command: ' + buildCommand);
        return this.runCommand(buildCommand, pathToCcsProjectCli, loggerHandler);
    }
    async projectExists(projectName) {
        return this.fs.existsSync(this.path.join(await this.getPathToProjectWorkspace(), projectName));
    }
}

/**
 *  Copyright (c) 2024 Texas Instruments Incorporated
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
class CloudProjectBuildService {
    constructor() {
        this.logger = new GcConsole('gc-service-cloud-project-build');
        this.workspaceServerPath = '/workspaceserver/app/Default';
    }
    async getPathToProjectWorkspace() {
        return `${this.workspaceServerPath}/${await GcFiles.getProjectName()}`;
    }
    async createFolderInWorkspaceServer(folderPath) {
        const folderExistsCommand = `${folderPath}?command=exists`;
        const folderCreateCommand = `${folderPath}?command=create&directory=true`;
        if (await (await fetch(folderExistsCommand)).text() === 'false') {
            const response = await fetch(folderCreateCommand);
            if (!response.ok) {
                throw new Error('Workspace not created');
            }
        }
    }
    async runCommand(URLtoRun, loggerHandler) {
        const pathToProjectWorkspace = await this.getPathToProjectWorkspace();
        this.logger.log('Running command: ' + URLtoRun);
        const response = await fetch(pathToProjectWorkspace + URLtoRun);
        loggerHandler((await response.json())['output']);
        return new Promise((resolve, reject) => {
            if (!response.ok) {
                reject(response.statusText);
            }
            resolve();
        });
    }
    async importProject(sdkPath, projectSpec, loggerHandler) {
        // if app/default folder does not exist, create one
        await this.createFolderInWorkspaceServer(this.workspaceServerPath);
        // if workspace folder does not exists in app, create one
        await this.createFolderInWorkspaceServer(await this.getPathToProjectWorkspace());
        const importURL = `/?command=ccs:import&location=${sdkPath}/${projectSpec}`;
        return this.runCommand(importURL, loggerHandler);
    }
    async buildProject(projectName, buildConfiguration, loggerHandler) {
        const buildCommandURL = `/${projectName}?command=ccs:build&configuration=${buildConfiguration}`;
        return this.runCommand(buildCommandURL, loggerHandler);
    }
    async projectExists(projectName) {
        const pathToProjectWorkspace = await this.getPathToProjectWorkspace();
        const folderExistsCommand = `${pathToProjectWorkspace}/${projectName}?command=exists`;
        const returnValue = await (await fetch(folderExistsCommand)).text() === 'true';
        return new Promise((resolve) => {
            resolve(returnValue);
        });
    }
}

/**
 *  Copyright (c) 2024 Texas Instruments Incorporated
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
const MODULE_NAME = 'gc-service-project-build';
/**
 * Service type for ProjectBuildService.
 */
const projectBuildServiceType = new ServiceType(MODULE_NAME);
const projectBuilderHelper = GcUtils.isCloud ? CloudProjectBuildService : DesktopProjectBuildService;
ServicesRegistry.register(projectBuildServiceType, projectBuilderHelper);

export { projectBuildServiceType };
//# sourceMappingURL=ProjectBuildService.js.map
