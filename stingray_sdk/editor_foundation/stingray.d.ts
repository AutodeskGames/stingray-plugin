declare module "stingray" {
    import "common/js-extensions";
    const stingray: Stingray;
    export = stingray;
}
declare module "app" {
    import 'angular-bootstrap';
    import 'angular-growl';
    var app: any;
    export = app;
}
declare module "base" {
    var baseFileName: string;
    function _initModule(): Promise<any>;
    function _loadModule(): Promise<any>;
    function _keyBinding(): void;
    export { baseFileName as name, _initModule as init, _loadModule as run, _keyBinding as initKeyBinding };
}
declare module "program" {
    const baseFileName: string;
    function loadSystem(): Promise<any>;
    export { baseFileName as name, loadSystem as run };
}
declare module "service" {
    function runService(): Promise<void>;
    const name: string | boolean;
    export { name, runService as run };
}
declare module "foundation/backend-client" {
    export function sendMessage(namespace: any, type: any, data?: any): any;
    export function connect(): Promise<{}>;
    export function start(): Promise<{}>;
    export function addMessageHandler(commandName: any, handler: any): () => any;
    export function connected(): boolean;
    export function close(): Promise<void>;
}
declare module "editor" {
    export function run(doNotRunBaseModule?: boolean): Promise<any>;
    export function initKeyBinding(): void;
    export const name = "editor";
}
declare module "window" {
    import "docking/docking-directive";
}
declare module "foundation/project" {
    class Project {
        settings: any;
        projectFile: any;
        constructor(projectFilePath: any, name?: any);
        name: any;
        description: any;
        readonly dir: string;
        readonly thumbnail: string;
        sourceDirectory: string;
        readonly artDirectory: any;
        readonly reverseForwardAxis: any;
        readonly skipCreateExtraRoot: any;
        dataDirectory: string;
        version: any;
        readonly libraries: any;
        setLibraryConfigPath(libraryName: any, configName: any, absolutePath: any): void;
        setLibraryConfigValue(libraryName: any, configName: any, value: any): void;
        toAbsolute(relativePath: any): string;
        toRelative(absolutePath: any): string;
        save(): boolean;
        static load(projectFilePath: any): Project;
        static createFromTemplate(template: any, projectName: any, destinationFolder: any, description: any): Project;
        static readonly EXTENSION: string;
        static readonly DOT_EXTENSION: string;
    }
    export = Project;
}
declare module "common/project-utils" {
    export function getProjectDirectoryName(): any;
    export function getSettings(settingsName: any): any;
    export function setSettings(settingsName: any, value: any): any;
    export function getProjectFileSettings(): any;
    export function getProjectFileSetting(settingName: any): any;
    export function isDirectory(path: any): boolean;
    export function removeTrailingDirectorySlash(path: any): any;
    export function convertBackwardToForwardSlashes(path: any): any;
    export function pathToResourceName(project: any, path: string): string;
    export function resourceNameToPath(project: any, name: string, extension: string): string;
    export function resourceType(path: any): any;
    export function resourceName(path: any): any;
    export function pathToResourceNameWithType(project: any, path: any): string;
    export function selectResource(projectService: any, hostService: any, resourceTypes: any, dialogSettings?: any, resourceFilter?: any): any;
    export function createResource(resourceName: any, resourceType: any): {
        $resource_name: any;
        $resource_type: any;
    };
    export function resolveResourcePath(currentProject: any, resourceName: any): string;
}
declare module "services/thumbnail-service" {
    namespace ThumbnailService {
        const DISCARDED_REQUEST: Promise<any>;
        const THUMBNAIL_SIZE = 256;
        class ThumbnailError extends Error {
            name: string;
            constructor(name: any, msg: any);
        }
        class Thumbnail {
            path: string;
            url: string;
            time: number;
            constructor(path: any, url: any);
        }
        class ThumbnailJob {
            hash: number;
            resourcePath: string;
            reject: (reason: any) => void;
            resolve: (value?: {} | PromiseLike<{}>) => void;
            promise: Promise<{}>;
            private resourceType;
            private resourceName;
            constructor(resourceName: any, resourceType: any);
            post(): any;
        }
        function generateThumbnail(resourcePath: any): Promise<Thumbnail>;
    }
    export = ThumbnailService;
}
