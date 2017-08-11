declare module "common/js-extensions" {
}
declare module "common/lodash-ext" {
    import _ = require("lodash");
    export = _;
}
declare module "stingray" {
    import "common/js-extensions";
    const stingray: Stingray;
    export = stingray;
}
declare module "common/math-utils" {
    export const max32Bits = 2147483647;
    export const min32Bits = -2147483648;
    export const epsilon: number;
    export const epsilon32 = 5e-7;
    export const epsilon64 = 5e-16;
    export const epsilon128 = 4.999999999999999e-34;
    export function rectContains(point: any, tl: any, br: any): boolean;
    export function nearlyEqual(a: any, b: any, epsilon?: any): boolean;
    export function arrayNearlyEqual(a: any, b: any, epsilon: any): boolean;
    export function toDegrees(radians: any): number;
    export function toRadians(degrees: any): number;
    export function toFixedNum(value: any, prec: any): number;
    export function clamp(v: any, min: any, max: any): number;
    export function isFloat(n: any): boolean;
    export function isInteger(n: any): boolean;
    export function numberTruncate(n: any, precision: any): number;
    export function bytesToSize(bytes: any): string;
    export class Vector {
        static isVector(possibleVector: any): any;
        static toString(vector: any, nbDecimals?: number): string;
    }
    export function getNumberOfDecimals(num: any): number;
    export function sortedIndexCompare(array: any, value: any, compare: any): number;
}
declare module "common/timer" {
    export class Timer {
        private _timerId;
        private _interval;
        private _callback;
        constructor(callback: any, interval: any);
        start(): void;
        cancel(): void;
    }
    export function now(): Date;
    export function time(): number;
}
declare module "common/profiler" {
    const _default: {
        registerInfo: (infoId: any, config: any) => {
            start: any;
            end: any;
            mark: any;
            refresh: any;
        };
        open: () => void;
        close: () => void;
        refresh: (configName: any) => void;
        startPerformanceMark: (configId: any, perfId: any) => void;
        endPerformanceMark: (configId: any, perfId: any) => void;
        toggle: () => void;
    };
    export = _default;
}
declare module "common/dom-updater" {
    export function requestUpdate(context?: any, updatedRemoteObject?: any, propertyUpdated?: any): any;
    export function registerUpdater(name: any, updateCallback: any): void;
    export function unregisterUpdater(name: any): void;
    export function isUpdating(): boolean;
    export function isModelUpdated(remoteObject: any): boolean;
}
declare module "app" {
    import "angular-bootstrap";
    import "angular-growl";
    const app: any;
    export = app;
}
declare module "common/file-system-utils" {
    export function isPathRooted(path: any): boolean;
    export let getExtension: (path: string, noLeadingDot?: boolean) => string;
    export function getFileName(path: any, withoutExtension?: any): any;
    export function extractDir(path: any): string;
    export function getFilePathWithoutExtension(path: any): any;
    export function cleanPath(path: any): string;
    export function makeRelativePath(path: any, rootPath: any): any;
    export function join(pathA: any, pathB: any): any;
    export function changeExtension(path: any, newExtension: any): any;
    export function b64toBlob(b64Data: any, contentType: any, sliceSize: any): Blob;
    export function b64toab(base64: any): ArrayBuffer;
    export function ab2str(buf: any): any;
    export function ab2b64(buffer: any): string;
    export function str2ab(str: any): ArrayBuffer;
    export function toUniqueFileName(name: any, extension: any, entries: any): any;
}
declare module "common/keycodes" {
    export let KEYCODE_BACKSPACE: number;
    export let KEYCODE_TAB: number;
    export let KEYCODE_CTRL_ENTER: number;
    export let KEYCODE_ENTER: number;
    export let KEYCODE_SHIFT: number;
    export let KEYCODE_CTRL: number;
    export let KEYCODE_ALT: number;
    export let KEYCODE_PAUSE: number;
    export let KEYCODE_CAPSLOCK: number;
    export let KEYCODE_ESCAPE: number;
    export let KEYCODE_SPACE: number;
    export let KEYCODE_PAGEUP: number;
    export let KEYCODE_PAGEDOWN: number;
    export let KEYCODE_END: number;
    export let KEYCODE_HOME: number;
    export let KEYCODE_LEFT: number;
    export let KEYCODE_UP: number;
    export let KEYCODE_RIGHT: number;
    export let KEYCODE_DOWN: number;
    export let KEYCODE_INS: number;
    export let KEYCODE_DEL: number;
    export let KEYCODE_0: number;
    export let KEYCODE_1: number;
    export let KEYCODE_2: number;
    export let KEYCODE_3: number;
    export let KEYCODE_4: number;
    export let KEYCODE_5: number;
    export let KEYCODE_6: number;
    export let KEYCODE_7: number;
    export let KEYCODE_8: number;
    export let KEYCODE_9: number;
    export let KEYCODE_A: number;
    export let KEYCODE_B: number;
    export let KEYCODE_C: number;
    export let KEYCODE_D: number;
    export let KEYCODE_E: number;
    export let KEYCODE_F: number;
    export let KEYCODE_G: number;
    export let KEYCODE_H: number;
    export let KEYCODE_I: number;
    export let KEYCODE_J: number;
    export let KEYCODE_K: number;
    export let KEYCODE_L: number;
    export let KEYCODE_M: number;
    export let KEYCODE_N: number;
    export let KEYCODE_O: number;
    export let KEYCODE_P: number;
    export let KEYCODE_Q: number;
    export let KEYCODE_R: number;
    export let KEYCODE_S: number;
    export let KEYCODE_T: number;
    export let KEYCODE_U: number;
    export let KEYCODE_V: number;
    export let KEYCODE_W: number;
    export let KEYCODE_X: number;
    export let KEYCODE_Y: number;
    export let KEYCODE_Z: number;
    export let KEYCODE_NUMPAD_0: number;
    export let KEYCODE_NUMPAD_1: number;
    export let KEYCODE_NUMPAD_2: number;
    export let KEYCODE_NUMPAD_3: number;
    export let KEYCODE_NUMPAD_4: number;
    export let KEYCODE_NUMPAD_5: number;
    export let KEYCODE_NUMPAD_6: number;
    export let KEYCODE_NUMPAD_7: number;
    export let KEYCODE_NUMPAD_8: number;
    export let KEYCODE_NUMPAD_9: number;
    export let KEYCODE_NUMPAD_MULTIPLY: number;
    export let KEYCODE_NUMPAD_ADD: number;
    export let KEYCODE_NUMPAD_DASH: number;
    export let KEYCODE_NUMPAD_DOT: number;
    export let KEYCODE_F1: number;
    export let KEYCODE_F2: number;
    export let KEYCODE_F3: number;
    export let KEYCODE_F4: number;
    export let KEYCODE_F5: number;
    export let KEYCODE_F6: number;
    export let KEYCODE_F7: number;
    export let KEYCODE_F8: number;
    export let KEYCODE_F9: number;
    export let KEYCODE_F10: number;
    export let KEYCODE_F11: number;
    export let KEYCODE_F12: number;
    export let KEYCODE_SEMICOLON: number;
    export let KEYCODE_EQUAL: number;
    export let KEYCODE_COMMA: number;
    export let KEYCODE_DASH: number;
    export let KEYCODE_DOT: number;
    export let KEYCODE_SLASH: number;
    export let KEYCODE_TILDE: number;
    export let KEYCODE_BRACKETOPEN: number;
    export let KEYCODE_BACKSLASH: number;
    export let KEYCODE_BRACKETCLOSE: number;
    export let KEYCODE_QUOTE: number;
    export class KeyCodeHelper {
        keyCodeToString: any;
        stringToKeycode: any;
        constructor();
        keycodeToString(keycode: any): any;
        stringToKeyCode(s: any): any;
        isEnterKey(keycode: any): boolean;
        isAlphaNumericKey(keycode: any): boolean;
        isCharacterKey(keycode: any): boolean;
        isNavigationKey(keycode: any): boolean;
        isArrowKey(keycode: any): boolean;
        haveModifierKey(event: any): any;
    }
    export let helper: KeyCodeHelper;
}
declare module "extensions/generic-parser" {
    export let FatalError: (message: any, pluginName: any, extension: any, more: any) => void;
    export function addResolver(name: any, resolver: any): void;
    export function create(extensionName: any, behaviors: any, parsers: any, toBeMerged?: any): any;
    export function toDynamicString(s: any): any;
}
declare module "extensions/parser-utils" {
    export function relativeToPluginDir(fieldName: any, setDefaultToPluginRoot?: any): any;
    export function resolveModulePath(path: any, pluginName: any, getters: any): any;
    export function createPluginEvents(pluginService: any, selector: any): {
        onLoad: any;
        onUnload: any;
    };
    export function wrap(extensionData: any, pluginName?: string): {};
    export function testParseExtension(extensionParser: any, pluginGetters: any, extensionData: any): any;
    export function initManager(pluginService: any, extensionModule: any): any;
}
declare module "common/web-socket" {
    class WebSocketWithArguments {
        private _receivedCallback;
        private _onopenCallback;
        private _socket;
        constructor(connectionUrl: any, receivedCallback: any, onopenCallback: any, options?: any);
        private _onMessageDebug(evt);
        private _onMessage(evt);
        private _onOpen();
        private _onClose();
        private _onError(e);
        bufferedAmount(): number;
        send(data: any): void;
        isReady(): boolean;
    }
    export = WebSocketWithArguments;
}
declare module "common/channel" {
    export class Channel {
        _namespaces: any[];
        _onopenCallback: any;
        _socket: any;
        _callbacks: any[];
        _bufferedMessages: any[];
        constructor(connectionUrl: any, namespaces: any, receivedCallback: any, onopenCallback: any);
        _onOpen(): void;
        isReady(): any;
        hasNamespace(namespace: any): boolean;
        bufferedAmount(): any;
        send(namespaceName: any, typeName: any, data: any): void;
    }
}
declare module "common/url-utils" {
    export function deparam(params: any, coerce?: any): any;
    export function queryString(): any;
    export class URLObject {
        querystring: string;
        port: any;
        base: any;
        constructor(base: any, port: any);
        addQuerystring(key: any, value: any): void;
        addQuerystrings(query: any): void;
        getURL(protocol: any): URL;
    }
}
declare module "common/channel-manager" {
    class ChannelManager {
        ip: any;
        port: any;
        private _callbacks;
        private _catchAllCallback;
        private _channels;
        private _suppressedPropertyChangedMessages;
        constructor(ip: any, port: any);
        isReady(namespace: any): boolean;
        openChannel(namespaces: any): Promise<{}>;
        bufferedAmount(): number;
        _received(messageData: any): void;
        send(namespaceName: any, typeName: any, data: any): void;
        on(namespaceName: any, typeName: any, callbackFunc: any): void;
        off(namespaceName: any, typeName: any, callbackFunc: any): void;
        _isSuppressedPropertyChangedMessage(namespace: any, type: any, data: any): boolean;
        suppressPropertyChanged(remoteObjectId: any, propertyName: any): void;
        unsuppressPropertyChanged(remoteObjectId: any, propertyName: any): void;
        setCatchAllCallback(callback: any): void;
    }
    export = ChannelManager;
}
declare module "services/channel-service" {
    export let send: any;
    export let openChannel: any;
    export let on: any;
    export let off: any;
    export let isReady: any;
    export let suppressPropertyChanged: any;
    export let unsuppressPropertyChanged: any;
    export let bufferedAmount: any;
    export function request(namespaceName: any, typeName: any, data: any, noDomUpdate?: any): any;
}
declare module "services/marshalling-service" {
    export interface RemoteValue {
        _adskRemoteObjectId: string;
        _adskBackingValue: any;
        _adskAvailableProperties: string[];
        _adskInitialized: boolean;
        _adskInternalType: string;
        _propertyChanged: Function[];
        _collectionChanged: Function[];
        _invokeDelegateCallbacks: {
            [methodName: string]: Function;
        };
        _eventHandlers: {
            [eventName: string]: Function[];
        };
    }
    export class MarshallingException extends Error {
        more: string;
        source: string;
        constructor(message: any, name: any, source: any, more: any);
    }
    export class RemoteObject {
        $i: number;
        static _nextInstanceId: number;
        constructor(remoteObjectId: any, initialValue: any, internalType: any);
        id(): string;
        isValid(): boolean;
        addProperty(name: any, value: any): void;
        removeProperty(name: any): void;
        hasProperty(name: any): boolean;
        getProperty(name: any): any;
        setProperty(name: any, value: any, doNotRaise?: any): void;
        clear(): void;
        isInitialized(): boolean;
        setInitialized(b: any): void;
        invokeMethod(methodName: any, args: any, options: any): any;
        invokeMethodAndProcessResult(methodName: any): any;
        onPropertyChanged(callback: any): void;
        offPropertyChanged(callback: any): void;
        raisePropertyChanged(propertyName: any, newValue: any, oldValue?: any): void;
        onCollectionChanged(callback: any): void;
        offCollectionChanged(callback: any): void;
        raiseCollectionChanged(addedItems: any, removedItems: any, changedItems: any, action: any): void;
        raiseInvokeViewDelegate(methodName: any, args: any): void;
        release(): void;
        on(event: any, handler: any): () => void;
        off(event?: any, handler?: any): void;
        raiseRemoteEvent(event: any, args: any): void;
        _addCallback(callbackCollection: any, callback: any): void;
        _removeCallback(callbackCollection: any, callback: any): void;
        dispose(): void;
        internalType(): string;
        hasRemoteEventHandler(event: any): boolean;
    }
    export interface RemoteCollection extends Array<any>, RemoteObject {
        itemsAdded: Function[];
        itemsRemoved: Function[];
        collectionReplaced: Function[];
        collectionCleared: Function[];
    }
    export interface RemoteDelegate extends RemoteObject {
        (value?: {} | PromiseLike<{}>): void;
    }
    export class RemoteObjectHandle {
        adskRemoteObjectId: string;
        constructor(remoteObject: RemoteObject);
        id(): string;
    }
    export const _guidToRemoteObjects: Map<string, RemoteObject>;
    export const stats: {
        lastGC: any;
        lastObjectsRemovedCount: number;
    };
    export interface RequestObjectConfig {
        propertyPath: string;
        proxy: boolean;
    }
    export function requestRemoteObject(remoteObject: any, remoteObjectInstanceName?: string, remoteObjectAdditionalData?: any, options?: any): any;
    export function createRemoteObject(remoteObjectTypeName: any, genericTypes?: any, args?: any): any;
    export function releaseRemoteObjects(objs: any): any;
    export function invokeMethod(remoteObject: any, methodName: any, args: any, options: any): any;
    export function invokeMethodAndProcessResult(remoteObject: any, methodName: any): any;
    export function invokeMethodAndProcessTransientResult(remoteObject: any, methodName: any): any;
    export function invokeAsynchronousMethod(remoteObject: any, methodName: any): any;
    export function invokeStaticMethod(className: any, methodName: any): any;
    export function invokeStaticMethodAndProcessResult(className: any, methodName: any): any;
    export function invokeStaticMethodAndProcessTransientResult(className: any, methodName: any): any;
    export function invokeStaticAsynchronousMethod(className: any, methodName: any): any;
    export function registerRemoteEventHandler(remoteObject: any, event: any): void;
    export function on(eventName: string, callback: Function): any;
    export function off(eventName?: string, callback?: Function): any;
}
declare module "services/base-service" {
    class BaseService {
        promise: Promise<any>;
        _remoteService: any;
        marshallingService: any;
        onRemoteServiceResolved: Function;
        constructor(remoteServiceId: any, onRemoteServiceResolved?: any);
        on(event: any, handler: any): OffHandler;
        off(event: any, handler: any): Promise<any>;
        invoke(methodName: any, ...args: any[]): Promise<any>;
        invokeMethod(methodName: any, args: any, methodParams: any): Promise<any>;
        ready(): Promise<any>;
    }
    export = BaseService;
}
declare module "services/plugin-service" {
    export function rescan(projectPath: any): Promise<any>;
    export function getPlugin(pluginName: any): Promise<any>;
    export function getPlugins(): Promise<any>;
    export function isPluginLoaded(pluginName: any): Promise<any>;
    export function registerPlugin(pluginPath: any): Promise<any>;
    export function unregisterPlugin(pluginName: any): Promise<any>;
    export function loadPlugin(pluginName: any): Promise<any>;
    export function unloadPlugin(pluginName: any): Promise<any>;
    export function on(event: any, handler: any): OffHandler;
    export function off(event: any, handler: any): Promise<any>;
    export function getExtensions(selector: any, pluginName?: any): any;
    export function parseExtensions(pluginName: any, extensionParser: any, rawExtensions: any): any;
    export function searchExtension(extensionType: any, extensionName: any, pluginName?: any): Promise<any>;
}
declare module "common/event" {
    class Event {
        _events: {};
        constructor();
        static makeEventHandler(owner: any): any;
        on(event: any, condition?: any, callback?: any): any;
        off(event: any, callback?: any): this;
        once(event: any, condition: any, callback: any): this;
        removeAllListeners(event: any): this;
        emit(event: string, ...args: any[]): boolean;
        listeners(event: any): any;
    }
    export = Event;
}
declare module "services/event-service" {
    import Event = require("common/event");
    export function emit(event: string, ...args: any[]): Promise<any>;
    export function offer(eventName: any, ...args: any[]): Promise<{}>;
    export function on(eventName: string, offerCondition?: Function, callback?: Function): any;
    export function makeEventHandler(owner: any): any;
    export function off(event: any, callback?: any): Event;
    export function once(event: any, condition: any, callback: any): Event;
    export function removeAllListeners(event: any): Event;
    export function listeners(event: any): any;
    export function getPort(): number | [number, number];
    export function events(eventName: string, event: any): any;
}
declare module "extensions/services" {
    const services: any;
    export = services;
}
declare module "base" {
    const baseFileName: string;
    function _initModule(): Promise<any>;
    function _loadModule(): Promise<any>;
    function _keyBinding(): void;
    export { baseFileName as name, _initModule as init, _loadModule as run, _keyBinding as initKeyBinding };
}
declare module "docking/docking-utils" {
    export const LAYOUT_VERSION: any;
    export function isValidLayoutVersion(layout: any): any;
    export function showFrame(tab: any, refreshCounter: any): void;
    export function getWindowTitle(currentTabName: any, currentTabId: any): any;
    export function fadeFrame(fade: any, thing: any): void;
    export function getSize(element: any, includePosition: any, includeOffset: any): {
        pos: any;
        offset: any;
        width: any;
        height: any;
    };
    export function getScreenPosition(event: any): {
        x: any;
        y: any;
    };
    export function validateDragDistance(dragPos: any, dropPos: any): boolean;
    export function clearActiveTab(tab: any): void;
    export function resetRegionsSizes(regionContainer: any): void;
    export function registerTabActions(actionDescriptors: any): void;
    export function addTabActionHandler(handler: any): void;
    export function activateIframeEvents(activate: any): void;
    export function getAllFrames(): any;
    export function getAllFrameDocuments(): any;
    export function getAllFrameWindows(): any;
    export function changeWindowCursor(cursor?: any): void;
    export function captureMouseEvents(mouseDownEvent: any, config: any): void;
    export function isCapturing(): boolean;
    export function purify(thing: any, options: any): any;
    export function findTabs(displayName: any, regionContainer: any): any[];
    export function findResourceTabs(resource: any, editor: any, regionContainer: any): any[];
    export function getAllTabs(regionContainer: any): any[];
    export function emitTabEvent(tab: any, name: any, details?: any): any;
    export function createTabLayout(id: any, title: any, url: any): {
        version: any;
        docking: {
            regionContainer: {
                direction: string;
                regions: {
                    size: number;
                    tabs: {
                        id: any;
                        displayName: any;
                        order: number;
                        url: any;
                    }[];
                }[];
            };
        };
    };
}
declare module "extensions/views" {
    const views: any;
    export = views;
}
declare module "common/version" {
    export class Version {
        major: any;
        minor: any;
        patch: any;
        build: any;
        constructor(major: any, minor: any, patch: any, build: any);
        equals(rhs: any): boolean;
        valueOf(): {
            major: any;
            minor: any;
            patch: any;
            build: any;
        };
        toString(): string;
    }
    export function parse(versionString: any): Version;
    export function tryParse(versionString: any): Version;
    export function equals(lhs: any, rhs: any): boolean;
    export function less(lhs: any, rhs: any): boolean;
    export function compare(lhs: any, rhs: any): 0 | 1 | -1;
    export const zero: Readonly<Version>;
}
declare module "foundation/project" {
    import version = require("common/version");
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
        version: version.Version;
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
declare module "services/project-service" {
    import Project = require("foundation/project");
    export let promise: Promise<any>;
    export let CurrentProject: any;
    export let ToolChainConfiguration: any;
    export let ShowCreateExtraRoot: any;
    export function getCurrentProjectPath(): Promise<any>;
    export function getToolChainConfiguration(): Promise<any>;
    export function getSourceMaps(): Promise<any>;
    export function getResourceNames(resourceTypes: any, onlyProjectResources?: any, callback?: any): Promise<any>;
    export function getCurrentProject(): Promise<any>;
    export function getResourceNamesForProject(tccProjectIndex: any, resourceTypes: any): Promise<any>;
    export function getProjectDescription(tccProjectIndex: any): Promise<any>;
    export function getProjectName(tccProjectIndex: any): Promise<any>;
    export function getProjectVersion(tccProjectIndex: any): Promise<any>;
    export function getProjectVersionString(projectEntry: any): Promise<any>;
    export function addProject(projectSourcePath: any): Promise<any>;
    export function createDirectory(path: any): Promise<any>;
    export function removeProjectFromToolchain(index: any, noDomUpdate: any): Promise<any>;
    export function switchProjectFromPath(projectPath: any, levelName: any): Promise<any>;
    export function getMinimalProjectTemplate(): Promise<Project>;
    export function getEditorProjectVersion(): Promise<any>;
    export function mapDirectory(name: any, root: any): Promise<any>;
    export function unmapDirectory(name: any): Promise<any>;
    export function pathToResourceName(path: any): Promise<any>;
    export function resourceNameToPath(path: any, extension: any): Promise<any>;
    export function absolutePathToRelative(path: any): Promise<any>;
    export function relativePathToAbsolute(path: any): Promise<any>;
    export function appendProjectSettingsIni(projectFilePath: any, contents: any): Promise<any>;
    export function getProjectSettingsIni(): Promise<any>;
    export function getSettingFileSystemPath(...keys: any[]): Promise<any>;
    export function setProjectSettings(projectFilePath: any, value: any, ...keys: any[]): Promise<any>;
    export function waitForFileEventsDone(): Promise<any>;
    export function getAllFilesPath(): Promise<any>;
    export function on(event: any, handler: any): OffHandler;
    export function off(event: any, handler: any): Promise<any>;
}
declare module "services/remote-service" {
    import { RemoteObject } from "services/marshalling-service";
    export { RemoteObject } from "services/marshalling-service";
    export class RemoteService {
        promise: Promise<RemoteObject>;
        private _remoteService;
        constructor(remoteServiceId: any, onRemoteServiceResolved?: Function);
        on(event: any, handler: any): OffHandler;
        off(event: any, handler: any): Promise<RemoteObject>;
        invoke(methodName: any, ...invokeArgs: any[]): Promise<any>;
        invokeMethod(methodName: any, args: any, methodParams?: any): Promise<any>;
        ready(): Promise<RemoteObject>;
    }
}
declare module "services/host-service" {
    export const DialogAlreadyOpenedError: Error;
    export const DialogType: {
        FolderSelect: string;
        OpenFile: string;
        OpenMultipleFiles: string;
        SaveFile: string;
    };
    export function getClipboardTextData(): Promise<any>;
    export function setClipboardTextData(text: any): Promise<any>;
    export function openModalTextInputDialog(title: any, defaultValue: any, options: any): Promise<any>;
    export function openModalTextPickDialog(title: any, values: any, options: any): Promise<any>;
    export function openMessageBoxDialog(title: any, message: any, options: any, callback?: Function): any;
    export function getFolder(title: any, currentPath: any, type: any): Promise<string>;
    export type FilterExpression = any | string | string[];
    export function openNativeDialog(dialogType: string, currentPath: string, dialogName: string, filter: FilterExpression, allowPathOutsideProject?: boolean): Promise<any>;
    export function openDialog(dialogName: any, args: any, pathToView: any, dimensions: any): any;
    export function parseGotoLink(evtOrString: any): any;
    export function isGotoLink(elementOrString: any): boolean;
    export function showInExplorer(path: any): Promise<any>;
    export function openUrl(path: any): Promise<boolean>;
    export function startProcess(processPath: any, args: any, options?: any): Promise<any>;
    export function executeCustomUrl(href: any): Promise<any>;
    export function getMenuItems(): Promise<any>;
    export function executeMenuItem(menuActionPath: any): Promise<any>;
    export function updateMenuItem(menuActionPath: any, newLabel: any, disable: any): Promise<any>;
    export function updateMenuCheckStatus(path: string, checkable: boolean, checked: boolean): Promise<any>;
    export function showMenu(menuItems: any): Promise<any>;
    export function registerMenuItem(path: any, order: any, separator: any, section: any): Promise<any>;
    export function registerMenuAction(path: any, order: any, checkable: any, checked: any, shortcut: any): Promise<any>;
    export function removeMenu(path: any): Promise<any>;
    export function on(eventName: string, callback: Function): OffHandler;
    export function off(eventName?: string, callback?: Function): Promise<any>;
    export function invoke(...args: any[]): any;
    export function invokeMethod(...args: any[]): any;
    export function ready(...args: any[]): any;
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
declare module "extensions/base-extension" {
    class Extension {
        $plugin_name: string;
        $plugin: any;
        constructor(data: any);
        static toDynamicString(s: any): any;
        static define(extensionName: any, behaviors: any, parsers: any, toBeMerged: any): any;
        static wrap(extensionData: any, pluginName: any): {};
        static expandToPluginDir(fieldName: any, setDefaultToPluginRoot?: any): any;
        static mergeStaticMethods(behaviors: any, toBeMerged: any): void;
    }
    export = Extension;
}
declare module "services/file-system-service" {
    export function pathExists(path: any): Promise<boolean>;
    export function directoryPathIsValid(path: any): Promise<boolean>;
    export function filePathIsValid(path: any): Promise<boolean>;
    export function isFileOrFolderNameValid(name: any): boolean;
    export function getDocumentFolder(): Promise<string>;
    export function isPathRooted(path: any): boolean;
    export function getExtension(path: any, noLeadingDot?: any): string;
    export function getFileName(path: any, withoutExtension?: any): any;
    export function extractDir(path: any): string;
    export function getFilePathWithoutExtension(path: any): any;
    export function cleanPath(path: any): string;
    export function makeRelativePath(path: any, rootPath: any): any;
    export function join(...parts: string[]): string;
    export function normalizePath(path: any): Promise<string>;
    export function toUniqueFileName(name: any, baseFolder: any): Promise<string>;
    export function toUniqueDirectoryName(name: any, baseFolder: any): Promise<string>;
    export function enumerateFiles(directory: any, searchPattern: any, recursive: any): Promise<string[]>;
    export function deletePath(path: any): Promise<boolean>;
    export function isDirectory(path: any): Promise<boolean>;
    export function copy(source: any, destination: any): Promise<boolean>;
    export function readJSON(path: any): Promise<any>;
    export function writeJSON(path: any, json: any): Promise<boolean>;
    export function readFile(path: any, asBinary: any): Promise<any>;
    export function writeFile(path: any, content: any): any;
    export function unzip(zipPath: any, extractPath: any, overwrite: any): Promise<boolean>;
    export function createDirectory(path: any): Promise<boolean>;
    export function renameFile(filePath: any, newFilePath: any): Promise<boolean>;
}
declare module "extensions/actions" {
    const actions: any;
    export = actions;
}
declare module "extensions/events" {
    const events: any;
    export = events;
}
declare module "extensions/menus" {
    const menus: any;
    export = menus;
}
declare module "extensions/resources" {
    const resources: any;
    export = resources;
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
declare module "services/settings-service" {
    export function save(): Promise<any>;
    export function getNumber(keys: any, callback?: any): Promise<any>;
    export function getString(keys: any, callback?: any): Promise<any>;
    export function getBoolean(keys: any, callback?: any): Promise<any>;
    export function getObject(keys: any, callback?: any): Promise<any>;
    export function getArray(keys: any, callback?: any): Promise<any>;
    export function setNumber(keys: any, value: any): Promise<any>;
    export function setString(keys: any, value: any): Promise<any>;
    export function setBoolean(keys: any, value: any): Promise<any>;
    export function setObject(keys: any, value: any): Promise<any>;
    export function setArray(keys: any, value: any): Promise<any>;
    export function clear(keys: any): Promise<any>;
    export function on(event: any, handler: any): OffHandler;
    export function off(event: any, handler: any): Promise<any>;
    export function ready(): Promise<any>;
}
declare module "docking/docking-service" {
    export const templates: {
        region: {
            size: number;
            tabs: any[];
            type: string;
        };
        regionContainer: {
            direction: string;
            regions: any[];
            type: string;
        };
        tab: {
            displayName: string;
            order: number;
            url: string;
            type: string;
        };
        emptyConfig: any;
    };
    export const emptyLayout: any;
    export const defaultLayout: any;
    export const helpLinks: any;
    export let customActions: {
        actions: any[];
        subMenus: {};
    };
    export function loadUrlLayout(url: any): Promise<{}>;
    export function loadDefaultLayout(): Promise<{}>;
    export function loadEmptyLayout(): Promise<{}>;
    export function loadConfigLayout(configName: any): Promise<any>;
    export function loadSpecificLayout(layout: any): Promise<any>;
    export function saveLayout(name: any, layout: any): Promise<any>;
    export function removeLayout(name: any): Promise<any>;
    export function openWindow(layout: any, options: any): any;
    export function getAvailableTabs(): any;
    export function addTabActions(tab: any, menu: any): void;
}
declare module "docking/docking-drag" {
}
declare module "docking/docking-drop" {
}
declare module "common/context-menu-utils" {
    const _default: (context: any, event: any, items: any, hostService: any) => any;
    export = _default;
}
declare module "directives/context-menu" {
    import "jquery-context-menu";
}
declare module "docking/region-tab-directive" {
}
declare module "docking/region-tab-name-directive" {
    import "directives/context-menu";
}
declare module "docking/resizer-directive" {
}
declare module "docking/region-directive" {
    import "directives/context-menu";
    import "docking/region-drop-locations-directive";
    import "docking/region-tab-directive";
    import "docking/region-tab-name-directive";
    import "docking/resizer-directive";
}
declare module "docking/region-container-directive" {
    import "angular-recursion";
    import "docking/region-directive";
}
declare module "docking/docking-directive" {
    import "docking/docking-drag";
    import "docking/docking-drop";
    import "docking/docking-utils";
    import "docking/region-container-directive";
}
declare module "window" {
    import "docking/docking-directive";
}
declare module "common/console-connection" {
    import "sprintf";
    class ConsoleConnection {
        _ws: any;
        _utf8Decoder: any;
        _onMessageCallbacks: any[];
        _onOpenCallbacks: any[];
        _onCloseCallbacks: any[];
        _onErrorCallbacks: any[];
        _engine: any;
        constructor(ip: any, port: any, engine: any);
        close(): void;
        _onMessage(evt: any): void;
        _onOpen(): void;
        _onClose(): void;
        _onError(err: any): void;
        _send(data: any): void;
        onMessage(callback: any): void;
        onOpen(callback: any): void;
        onClose(callback: any): void;
        onError(callback: any): void;
        isReady(): boolean;
        isClosed(): boolean;
        sendScript(format: any, ...args: any[]): void;
        sendCommand(command: any, ...args: any[]): void;
        sendDebuggerCommand(command: any, data: any): void;
        engine(): any;
    }
    export = ConsoleConnection;
}
declare module "common/lua-utils" {
    export function toSyntax(obj: any): any;
}
declare module "services/engine-service" {
    import ConsoleConnection = require("common/console-connection");
    import { RemoteObject } from "services/remote-service";
    export class CompilationError extends Error {
        result: any;
        constructor(msg: any, compilationResult: any);
    }
    export interface IEngine extends RemoteObject {
        Id: string;
        Name: string;
        IsRunning: boolean;
        IsSlaving: boolean;
        IsConnected: boolean;
    }
    export interface EngineCallbackData {
        [fieldName: string]: any;
    }
    export type EngineCallback = (engine: IEngine, data: EngineCallbackData, binary: ArrayBuffer) => any;
    export let _engineConnections: {};
    export let _engineConnectionPromises: {};
    export let _postCallbacks: {};
    export let _engineMessageHandlers: WeakMap<IEngine, {
        [messageType: string]: Function[];
    }>;
    export let _luaDebuggerMessageHandlers: any[];
    export let _remoteMessageHandlers: {
        engineStartupHandlers: any[];
        engineRefreshedHandlers: any[];
        engineShutdownHandlers: any[];
        dataCompileStartedHandlers: any[];
        dataCompileFinishedHandlers: any[];
    };
    export let Engines: IEngine[];
    export let EditorControlledEngines: any[];
    export const EditorEngine: IEngine;
    export const TestEngine: IEngine;
    export const RunProjectEngine: IEngine;
    export const RemoteEngines: IEngine[];
    export const IsTestEngineRunning: boolean;
    export const DataCompiler: any;
    export function editorEngineReady(): Promise<ConsoleConnection[]>;
    export function addEngineMessageHandler(engine: any, messageType: any, callback: any): any;
    export function addEditorEngineMessageHandler(messageType: string, callback: EngineCallback): any;
    export function addLuaDebuggerMessageHandler(callback: any): any;
    export function getRunningEngines(): Promise<any>;
    export function addEngineStartupHandler(callback: any): any;
    export function addEngineRefreshedHandler(callback: any): any;
    export function addEngineShutdownHandler(callback: any): any;
    export function isEditorEngine(engine: any): Promise<any>;
    export function isTestEngine(engine: any): Promise<any>;
    export function registerOnDataCompileFileStatusChanged(onCompileStart: any, onCompileFinished: any): {
        compileStart: any;
        compileFinished: any;
    };
    export function getEngineTarget(engine: any): Promise<any>;
    export function postEditorCallback(callback?: Function): Promise<{}>;
    export function postCallback(engine: any, callback?: Function): Promise<{}>;
    export function stopEngine(engine: any): Promise<any>;
    export function sendToEditors(...args: any[]): Promise<any[]>;
    export function sendToConnections(args: any, connections: any): Promise<any>;
    export function sendToLocalEditors(...args: any[]): Promise<any>;
    export function sendToSlavingEngines(...args: any[]): Promise<any>;
    export function sendToEngine(engine: any, ...args: any[]): Promise<any>;
    export function sendDebuggerCommand(engine: any, command: any, data: any): Promise<{}>;
    export function sendCommand(engine: any, command: any, ...args: any[]): Promise<void>;
    export function restartEditorEngine(): Promise<any>;
    export function terminateEditorEngine(): Promise<any>;
    export function enqueueDataCompile(): Promise<any>;
    export function compile(assets?: string[]): Promise<any>;
    export function isCompiling(): Promise<any>;
    export function suspendDataCompile(isSuspended: boolean): Promise<any>;
    export function getEngineConnection(engine: any): any;
    export function getEngineConnections(engines: any): Promise<ConsoleConnection[]>;
    export function getEngineById(id: string): any;
    export function getEngineByName(name: string): any;
    export function evaluateScript(script: any, engine: any, timeoutMs?: number): Promise<{}>;
    export function waitDataCompileIdle(): Promise<any>;
    export function runProject(): Promise<any>;
    export function on(event: string, handler: Function): OffHandler;
    export function off(event?: string, handler?: Function): Promise<RemoteObject>;
    export function invoke(methodName: string, ...args: any[]): Promise<any>;
    export function invokeMethod(methodName: string, args: any[], methodParams?: object): Promise<any>;
    export function ready(): Promise<RemoteObject>;
}
declare module "extensions/imports" {
    const imports: any;
    export = imports;
}
declare module "extensions/templates" {
    const template: any;
    export = template;
}
declare module "common/http-client" {
    const _default: (url: any) => {
        get: any;
        post: any;
        put: any;
        delete: any;
        download: any;
        downloadFile: (endPoint: any, localFilePath: any, progress: any) => Promise<{}>;
        uploadFile: (endPoint: any, localFilePath: any) => Promise<{}>;
    };
    export = _default;
}
declare module "services/progress-service" {
    import { RemoteObject } from "services/marshalling-service";
    export interface ProgressWorkerRemoteObject extends RemoteObject {
        Description: string;
        Title: string;
        IsIndeterminate: boolean;
        Value: any;
        Maximum: number;
        PercentValue: number;
        IsCancelled: boolean;
        IsOngoing: boolean;
        AllowCancel: boolean;
    }
    export const CurrentProgressWorker: ProgressWorkerRemoteObject;
    export function startTask(title: any): Promise<any>;
    export function cancel(): Promise<any>;
    export function getAllProgressWorkers(): Promise<ProgressWorkerRemoteObject[]>;
    export function on(eventName: string, callback: Function): OffHandler;
    export function off(eventName?: string, callback?: Function): Promise<RemoteObject>;
}
declare module "foundation/plugin" {
    class Plugin {
        scope: string | number;
        type: string | number;
        thumbnailUrl: any;
        author: {
            name: any;
        };
        qaVerified: any;
        verified: any;
        deprecated: any;
        category: any;
        dependencies: any;
        extensions: any;
        newVersion: any;
        disabled: any;
        lastUpdated: any;
        isUserPlugin: any;
        isLoaded: any;
        size: any;
        infoUrl: any;
        downloadUrl: any;
        keywords: any;
        name: any;
        description: any;
        version: any;
        path: any;
        id: any;
        constructor(id: any, pluginInfo: any);
        dir(): string;
        getPackageDependencies(): any[];
        readonly formattedSize: string;
        static load(pluginDescriptorFilePath: any): Plugin;
        static readonly DEFAULT_EXTENSION: string;
        static readonly ASSET_CONTENT_PLUGIN_EXTENSION: string;
        static readonly PLUGIN_EXTENSIONS: string[];
        static readonly PLUGIN_WILD_CARD_EXTENSIONS: string[];
        static enumerate(dirPath: any): string[];
        static readonly USER_PLUGIN: number;
        static readonly PROJECT_PLUGIN: number;
        static readonly CONTENT_PLUGIN: number;
        static readonly SYSTEM_PLUGIN: number;
        static getTypeScope(plugin: any): (string | number)[];
    }
    export = Plugin;
}
declare module "foundation/spm-registry" {
    import Plugin = require("foundation/plugin");
    export function status(): any;
    export function getPlugins(): any;
    export function getPackage(name: any, version: any): Promise<Plugin>;
    export function getPackages(types: any): any;
    export function getPackageReadme(pluginInfo: any, parse: any): any;
    export function getProjectPackages(): Promise<{
        id: string;
        filePath: string;
    }[]>;
    export function isPackageAlreadyInstalled(pck: any): Promise<any>;
    export function downloadZipFile(pluginId: any, pluginName: any, downloadUrl: any, onProgress: any): Promise<string[]>;
    export function downloadPackage(pluginPackage: any, onProgress?: any): Promise<any>;
    export function previewPackage(pluginPackage: any, templateTypes?: any[], templateName?: any): any;
    export function installPackage(pluginPackage: any, templateTypes?: any[], templateName?: any): any;
    export function getCategories(): any;
}
declare module "services/asset-service" {
    import { RemoteObject } from "services/remote-service";
    export const SelectedAssets: string[];
    export function checkForDeleteImpact(paths: any): Promise<any>;
    export function checkForMoveFilesImpact(srcs: any, dstPath: any): Promise<any>;
    export function checkForRenameFilesImpact(srcPath: any, dstPath: any): Promise<any>;
    export function clearSelection(): Promise<any>;
    export function createAsset(type: any, directoryPath: any, name: any, settings: any): Promise<any>;
    export function deletePaths(paths: any, doNotDeleteFiles: any): Promise<any>;
    export function duplicatePath(src: any, dst: any): Promise<any>;
    export function duplicatePaths(paths: any): Promise<any>;
    export function discardChanges(path: any): Promise<any>;
    export function loadAsset(path: any): Promise<any>;
    export function getAllEntries(): Promise<any>;
    export function getAssetEntry(path: any): Promise<any>;
    export function getAssetEntries(assets: any): Promise<any>;
    export function getAssetsContent(assets: any): Promise<any>;
    export function getAssetClosure(asset_path: any): Promise<any>;
    export function getAssetUniqueName(directory: any, type: any, prefix: any): Promise<any>;
    export function getFolderEntries(folder: any): Promise<any>;
    export function getMissingResources(): Promise<any>;
    export function getDanglingResources(): Promise<any>;
    export function getConcreteResources(): Promise<any>;
    export function getRootEntries(): Promise<any>;
    export function getUniqueDirectory(directory: any, baseName: any): Promise<any>;
    export function invokeAsset(assetPath: any): Promise<any>;
    export function isAssetEditable(resourceName: any): Promise<any>;
    export function isClosureReadOnly(asset_path: any): Promise<any>;
    export function move(srcs: any, dstPath: any): Promise<any>;
    export function parseDependencies(): Promise<any>;
    export function referencesBy(resourceName: any): Promise<any>;
    export function rename(srcPath: any, dstPath: any): Promise<any>;
    export function resourceReport(resourceName: any): Promise<any>;
    export function safeMove(srcs: any, dstPath: any): Promise<any>;
    export function safeRename(srcPath: any, dstPath: any): Promise<any>;
    export function safeReplace(fromResourceName: any, toResourceName: any): Promise<any>;
    export function saveAsset(path: any): Promise<any>;
    export function search(searchQuery: any, location?: any): Promise<any>;
    export function setMultipleSelection(paths: any, add: any, noDomUpdate: any): Promise<any>;
    export function setSelection(path: any): Promise<any>;
    export function toRelativeNormalPath(path: any): Promise<any>;
    export function toggleSelection(path: any): Promise<any>;
    export function isEntriesReadOnly(paths: any): Promise<any>;
    export function getFilesState(source: any, target: any): Promise<any>;
    export function exportAssets(to: any, paths: any): Promise<any>;
    export function getManagedAsset(path: any): Promise<any>;
    export function isAssetCompiling(path: any): Promise<any>;
    export function isValidPackage(path: any): Promise<any>;
    export function getLegacyAssetTypeActions(path: any): Promise<any>;
    export function getLegacyAssetCreators(): Promise<any>;
    export function clearManagedAssets(): Promise<any>;
    export function on(event: string, handler: Function): OffHandler;
    export function off(event?: string, handler?: Function): Promise<RemoteObject>;
    export function ready(): Promise<RemoteObject>;
}
declare module "services/savable-service" {
    export function saveAll(no_ui?: boolean): Promise<any>;
    export function on(event: any, handler: any): OffHandler;
    export function off(event: any, handler: any): Promise<any>;
}
declare module "services/animation-editing-service" {
    export function canCreateAnimationControllerForUnit(unit_resource_path: any): Promise<any>;
    export function createAnimationControllerFromPath(skeleton_path: any): Promise<any>;
    export function createSkeletonTreeViewModel(skeletonDataModel: any): any;
    export function getDataRoot(name: any, genericType: any): Promise<any>;
    export function importCompleted(filesImported: any): Promise<any>;
    export function getUnitAnimControllerResourceName(unitResource: any): Promise<any>;
    export function getAnimControllerEventNames(animationResource: any): Promise<any>;
    export function getAnimControllerVariableNames(animationResource: any): Promise<any>;
    export function on(event: any, handler: any): OffHandler;
    export function off(event: any, handler: any): Promise<any>;
    export function ready(): Promise<any>;
    export const promise: Promise<any>;
    export const StaticGeometry: any;
}
declare module "common/asset-utils" {
    export let emptyMaterialDescription: {
        label: string;
        type: string;
    };
    export function renameAsset(asset: any, newName: any): Promise<any>;
    export function moveAsset(possibleMultipleSrcs: any, dstRelativePath: any, isRename: any): Promise<{
        success: any;
        path: any;
    }>;
    export function deleteDirectory(directory: any, $event: any): Promise<any>;
    export function deleteAssets(assets: any): Promise<any>;
    export function saveAsset(asset: any): void;
    export function discardChanges(asset: any): void;
    export function importAssets(files: any, importFolder: any, reImport: any): any;
    export function duplicateSinglePath(asset: any): any;
    export function duplicatePaths(assets: any): Promise<any>;
    export function getUniqueName(asset: any, type: any, prefix: any): Promise<any>;
    export function getAssetCreationTypes(): Promise<any[]>;
    export function createAssetType(assetCreationItem: any, directory: any): Promise<any>;
    export function createMaterialEmpty(directory: any): Promise<any>;
    export function createAsset(path: any, assetCreationItem: any, isMaterial?: any): Promise<any>;
    export function createDirectory(directory: any): Promise<any>;
    export function createDirectoryPlaceholder(directory: any): Promise<any>;
    export function showImportAssetDialog(directory: any, srcImportFolder: any): Promise<any>;
    export function exportAssets(assets: any): any;
    export function downloadAndInstallPackage(spmAssetPackage: any): Promise<any>;
    export function focusAndInvoke(document: any, path: any): void;
    export function trackFileSystemChanges(startCallback: any): Promise<({}[] | {
        added: {};
        removed: {};
        changed: {};
    })[]>;
    export function getCustomActions(asset: any): Promise<{}>;
    export function handleBackendException(ex: any): void;
    export function focusResource(resourcePath: any): void;
    export function gotoResource(resourcePath: any): Promise<{}>;
    export function selectAssetsWhenReady(assets: any, context: any): Promise<any>;
}
declare module "common/color-utils" {
    export function hsvToRgb(hsv: any): any[];
    export function rgbToHsv(rgb: any, lastKnownHue: any, lastKnownSaturation: any): any[];
    export function rgbToCssColor(rgb: any, alpha: any): string;
    export function cssColorToRgb(cssColor: any): number[];
    export function cssColorAlpha(cssColor: any): number;
    export function simpleRgbToCss(rgb: any): string;
    export function simpleCssToRgb(css: any): any[];
    export function rgbToHsl(red: any, green: any, blue: any): any[];
    export function hslToRgb(H: any, S: any, L: any): number[];
    export function simpleRgbToInt32(rgb: any): number;
    export function int32ToSimpleRgb(int32: any): any[];
    export function rgbEqual(op1: any, op2: any): boolean;
    export function rgb1Equal(op1: any, op2: any): boolean;
    export function convertColor(color: any, scheme: any): any;
    export function toColorPickerFormat(color: any): any;
    export function toColorProxyFormat(color: any): any;
    export function hueDegToRgb(h: any): number[];
    export function hslToHsv(hsl: any): any[];
    export function hsvToHsl(hsv: any): any[];
    export function rgbToHex(rgb: any): string;
    export function hexToRgb(hex: any): number[];
    export function rgbTosRgb(rgb: any): any[];
    export function rgbTosRgbChannel(c: any): number;
    export function sRgbToRgb(rgb: any): any[];
    export function sRgbToRgbChannel(c: any): number;
    export class Color {
        _alpha: number;
        _hex: string;
        _hslSaturation: number;
        _lightness: number;
        _value: number;
        _saturation: number;
        _hue: number;
        _sBlue: number;
        _sGreen: number;
        _sRed: number;
        _blue: number;
        _green: number;
        _red: number;
        _blue1: number;
        _green1: number;
        _red1: number;
        fix_num: number;
        constructor();
        red1(val: any): number;
        green1(val: any): number;
        blue1(val: any): number;
        red(val: any): number;
        green(val: any): number;
        blue(val: any): number;
        sRed(val: any): number;
        sGreen(val: any): number;
        sBlue(val: any): number;
        hue(val: any): number;
        saturation(val: any): number;
        value(val: any): number;
        lightness(val: any): number;
        hslSaturation(val: any): number;
        alpha(val: any): number;
        HEX(val: any): string;
        RGB(rgb: any): number[];
        HSV(hsv: any): number[];
        RGB1(rgb: any): number[];
        sRGB(sRgb: any): number[];
        HSL(hsl: any): number[];
    }
}
declare module "common/default-viewport-mouse-behavior" {
    class DefaultViewportMouseBehavior {
        engineViewportInterops: any;
        viewportId: any;
        engineService: any;
        constructor(engineService: any, engineViewportId: any, engineViewportInterops: any);
        mouseDown(e: any, viewportId: any, x: any, y: any): void;
        mouseUp(e: any, viewportId: any, x: any, y: any): void;
        mouseMove(e: any, viewportId: any, x: any, y: any, deltaX: any, deltaY: any): void;
        mouseWheel(e: any, viewportId: any, deltaY: any): void;
        keyDown(e: any, viewportId: any): void;
        keyUp(e: any, viewportId: any): void;
        setCameraControlStyle(style: any): void;
        static modifiersFromMouseEvent(e: any): {
            alt: any;
            ctrl: any;
            shift: any;
        };
    }
    export = DefaultViewportMouseBehavior;
}
declare module "common/default-viewport-controller" {
    import Event = require("common/event");
    class DefaultViewportController extends Event {
        engineViewportInterops: any;
        viewportId: any;
        mouseBehavior: any;
        engineService: any;
        constructor(engineService: any);
        setup(engineViewportId: any, engineViewportInterops: any): void;
        clear(): void;
        setMouseBehavior(behavior: any): void;
        mouseDown(): void;
        mouseUp(evt: any): void;
        mouseMove(evt: any): void;
        mouseWheel(evt: any): void;
        keyDown(evt: any): void;
        keyUp(evt: any): void;
        viewportResized(): void;
        viewportDrop(e: any): void;
    }
    export = DefaultViewportController;
}
declare module "common/drag-utils" {
    export const stingrayMimeTypeBase = "application/stingray-";
    export const stingrayMimeTypeJson = "application/stingray+json";
    export const assetPathDropType = "asset-path";
    export const wwiseEventType = "wwise-event";
    export const plainTextMimeType = "text/plain";
    export const uriListMimeType = "text/uri-list";
    export const listViewMimeType = "application/stingray-listviewdragdata+json";
    export function createStingrayDragData(type: any, items: any): {
        type: any;
        items: any;
    };
    export function isStingrayDragData(possibleDragData: any): any;
    export function isDragDataList(data: any): any;
    export function hasFileList(dataTransfer: any): any;
    export function getFileList(dataTransfer: any): string[];
    export function createDragDataList(...args: any[]): any[];
    export function addToDragDataList(mimeType: any, data: any, dragDataList: any): void;
    export function createAssetTypeMimeType(file: any): any;
    export function containsAssetType(dataTransfer: any, extension: any): any;
    export function containsAnyAssetTypes(dataTransfer: any, extensions: any): any;
    export function containsStingrayDragDataOfType(dataTransfer: any, type: any, isJson: any): any;
    export function containsAnyStingrayDragDataOfTypes(dataTransfer: any, extensions: any, isJson?: any): any;
    export function extractStingrayTypeFromMimeType(mimeType: any): any;
    export function addToDragDataTransfer(dataTransfer: any, data: any, possibleType: any, img?: any): any;
    export function getStingrayDragDataOfType(dataTransfer: any, type: any): any;
}
declare module "services/engine-viewport-service" {
    export let promise: Promise<any>;
    export let FocusedViewportId: string;
    export let AllEditorCameras: any;
    export let AllVisualizationModes: any;
    export function createViewport(behaviorClass: any, name: any, viewportId: any, parentHandle: any, levelContext: any): any;
    export function destroyViewport(viewportId: any): any;
    export function setFocusedViewportId(viewportId: any): void;
    export function setFocusedViewportName(viewportName: any): void;
    export function setCameraControlStyle(viewportId: any, cameraControlStyle: any, doNotSelectViewport: any): void;
    export function keyDown(keyCode: any, altKey?: any, ctrlKey?: any, shiftKey?: any): void;
    export function keyUp(keyCode: any, altKey?: any, ctrlKey?: any, shiftKey?: any): void;
    export function mouseDown(viewportId: any, viewportX: any, viewportY: any, buttonIndex: any): void;
    export function mouseMove(viewportId: any, viewportX: any, viewportY: any, deltaX: any, deltaY: any): void;
    export function mouseUp(viewportId: any, viewportX: any, viewportY: any, buttonIndex: any): void;
    export function mouseWheel(viewportId: any, wheelDeltaY: any): void;
    export function mouseLeave(viewportId: any): void;
    export function dragStart(dragData: any): void;
    export function dragEnd(): void;
    export function viewportDragEnd(viewportId: any): void;
    export function viewportDrop(viewportId: any, viewportX: any, viewportY: any): void;
    export function getViewportIdsFromName(viewportName: any): Promise<any>;
    export function getViewportSettingsFromId(viewportId: any): Promise<any>;
    export function getViewportNameFromId(viewportId: any): Promise<any>;
    export function setActiveCamera(viewportName: any, camera: any): Promise<any>;
    export function getActiveCameraForViewport(viewportName: any): Promise<any>;
    export function setViewportUpdateMode(viewportName: any, mode: any): Promise<any>;
    export function getViewportCameraState(viewportName: any): any;
    export function setVisualizationModeForViewport(viewportName: any, mode: any): Promise<any>;
    export function anyViewportHasHiddenGizmos(): Promise<any>;
    export function updateViewport(viewportId: any): Promise<any>;
    export function on(event: any, callback: any): OffHandler;
    export function off(event: any, callback: any): Promise<any>;
}
declare module "services/object-editing-service" {
    export function getEditors(): Promise<any>;
    export function performSetSelectionCommand(objects: any): Promise<any>;
    export function performChangePropertyScopeCommand(object: any, scope: any): Promise<any>;
    export function tryOpenPropertyEditor(launchToolIfNeeded?: boolean): any;
    export function clearSelection(): Promise<any>;
    export function on(event: any, handler: any): OffHandler;
    export function off(event: any, handler: any): Promise<any>;
}
declare module "services/level-editing-service" {
    import { RemoteObject } from "services/remote-service";
    export const LevelEditingConstantNames: {
        PlaceToolName: string;
        SelectToolName: string;
        MoveToolName: string;
        RotateToolName: string;
        ScaleToolName: string;
        ScatterToolName: string;
        ManipulatorToolName: string;
        SelectionWindowName: string;
        SelectionCrossingName: string;
        ReferenceWorldName: string;
        ReferenceLocalName: string;
        SnapAbsoluteName: string;
        SnapRelativeName: string;
        VolumeToolName: string;
        MarkerToolName: string;
        PrototypeToolName: string;
        TriggerToolName: string;
        SplineToolName: string;
        TerrainToolName: string;
        TerrainCreateToolName: string;
    };
    export interface LevelObject extends RemoteObject {
        Id: string;
        Type: string;
        Name: string;
    }
    export interface Level extends RemoteObject {
        ShowGridAtOrigin: boolean;
        AreGizmosVisible: boolean;
        Layers: string[];
    }
    export const SelectedScatterBrush: string;
    export function setSelectedScatterBrush(name: string): any;
    export const SelectedToolName: string;
    export function setSelectedToolName(name: string): any;
    export const SelectionModeName: string;
    export function setSelectionModeName(name: string): any;
    export const MaximizedViewportName: string;
    export const CoordReferenceSystemTranslationName: string;
    export function setCoordReferenceSystemTranslationName(name: string): any;
    export const CoordReferenceSystemRotationName: string;
    export function setCoordReferenceSystemRotationName(name: string): any;
    export const IsSubObjectModeActive: boolean;
    export function setIsSubObjectModeActive(active: boolean): any;
    export const IsLoadingLevel: boolean;
    export const NeedsSaving: boolean;
    export const EditedLevel: RemoteObject;
    export const GridSize: number;
    export function setGridSize(size: number): any;
    export function setSelection(levelIds: any): Promise<any>;
    export function modifySelection(levelIdsToSelected: any, levelIdsToUnselect: any): Promise<any>;
    export function loadLevel(levelPath: any): Promise<any>;
    export function createNewLevel(): Promise<any>;
    export function testEditedLevel(): Promise<any>;
    export function getLightBakingSettings(): Promise<any>;
    export function setEditedLevelNeedsSaving(needsSaving: any): Promise<any>;
    export function isLevelLoaded(): Promise<any>;
    export function captureEditedLevel(captureBootIni: any): Promise<any>;
    export function getEditedLevelSettingsKey(): Promise<any>;
    export function getEditedLevelSaveFilePath(): Promise<any>;
    export function removeLightmaps(): Promise<any>;
    export function saveAs(levelPath: any): Promise<any>;
    export function save(): Promise<any>;
    export function invokeLevelObjects(objectIds: any): Promise<any>;
    export function renameLevelObject(objectId: any, newName: any): Promise<any>;
    export function deleteLevelObjects(objectIds: any): Promise<any>;
    export function cutSelectedLevelObjects(): Promise<any>;
    export function copySelectedLevelObjects(): Promise<any>;
    export function copyLevelObjects(objectIds: any, unspawnSelection: any): Promise<any>;
    export function pasteFromClipboard(doPasteAtCursorPos?: boolean): Promise<any>;
    export function cloneSelection(): Promise<any>;
    export function isLevelLoading(): Promise<any>;
    export function selectElement(element: any): Promise<any>;
    export function spawnEntity(entityName: string, entityResourceName: string): Promise<any>;
    export function deleteSelectedObjects(): Promise<any>;
    export function getEditedLevel(): Promise<Level>;
    export function unhideAll(): Promise<any>;
    export function hideUnselected(): Promise<any>;
    export function toggleSelectedObjectsVisibility(): Promise<any>;
    export function frameLevelObjectsInFocusedViewport(ids: string[]): Promise<any>;
    export function isTestingLevel(): Promise<any>;
    export function stopTesting(bootInit?: string): Promise<any>;
    export function clearReflectionProbes(): Promise<any>;
    export function bakeReflectionProbes(): Promise<any>;
    export function getSelectedObjectIds(): Promise<string[]>;
    export function getObjectById(levelObjectId: string): Promise<LevelObject>;
    export function on(eventName: string, callback: Function): OffHandler;
    export function off(eventName?: string, callback?: Function): Promise<any>;
    export function ready(): Promise<RemoteObject>;
}
declare module "common/engine-viewport" {
    import Event = require("common/event");
    class EngineViewport extends Event {
        bsy: any;
        bsx: any;
        mouseEventActive: any;
        destroyed: boolean;
        _throttledViewportResized: any;
        orphanKeyUpEvent: any;
        dy: number;
        dx: number;
        sy: number;
        sx: number;
        offEventHandlers: any[];
        opacity: number;
        visible: any;
        height: number;
        width: number;
        viewport: any;
        pointerLockPosition: any;
        pointerLocked: boolean;
        clearOnWindowUnload: any;
        simplifiedControls: any;
        viewportDroppable: any;
        suppressViewportDropEventToBackend: boolean;
        viewportId: any;
        behaviorClass: any;
        viewportName: any;
        _keyUp: (e) => void;
        _mouseMove: (e) => void;
        _mouseLeave: (e) => void;
        _mouseUp: (e) => void;
        _contextMenu: (e) => void;
        constructor(opts: any);
        createViewport(element: any): Promise<void>;
        refresh(): void;
        clearViewport(): void;
        _bindToElement(element: any): void;
        _raiseViewportEvent(evt: any): boolean;
        _syncViewportLayeredState(width: any, height: any, visible: any, opacity: any): Promise<any>;
        _resetViewport(): Promise<void>;
        _viewportResized(e?: any): void;
        _viewportHandleReceived(data: any): void;
        _mx(e: any): number;
        _my(e: any): number;
        _viewportDragStart(): void;
        _viewportDragEnd(): void;
    }
    export = EngineViewport;
}
declare module "common/entry-collection" {
    export interface EntryCollectionOptions {
        uniqueProperty: string;
        cacheUpdateProperties: string[];
    }
    export class EntryCollection {
        entries: object[];
        filteredEntries: object[];
        cacheUpdateProperties: string[];
        uniqueProperty: string;
        cache: Map<string, object>;
        constructor(options: EntryCollectionOptions);
        add(entries: object[]): void;
        set(entries: object[]): object[];
        remove(entries: object[]): void;
        update(entries: object[]): any;
        updateEntryValues(key: string, values: object): object;
        clear(): void;
        filter(filterFunc: Function): void;
        clearFilter(): void;
        unique(entries: any): any;
        find(id: string): any;
        private _validateEntries(entries);
        private _find(entry);
        private _findIndex(entry);
        private _inCache(entry);
        private _getOrSetInCache(entry);
        private _updateInCache(entry);
        private _updateCacheValues(key, updatedInfo);
        private _removeFromCache(entry);
    }
}
declare module "common/even-number" {
    class EvenNumber {
        exponent: any;
        digit: any;
        constructor(digit: any, exponent: any);
        value(): number;
        next(): EvenNumber;
        prev(): EvenNumber;
        static ONE(): EvenNumber;
        static floor(d: any): EvenNumber;
        static ceil(d: any): EvenNumber;
    }
    export = EvenNumber;
}
declare module "common/gl-utils" {
    import "sylvester";
    export function makeLookAt(ex: any, ey: any, ez: any, cx: any, cy: any, cz: any, ux: any, uy: any, uz: any): any;
    export function makePerspective(fovy: any, aspect: any, znear: any, zfar: any): any;
    export function makeFrustum(left: any, right: any, bottom: any, top: any, znear: any, zfar: any): any;
    export function makeOrtho(left: any, right: any, bottom: any, top: any, znear: any, zfar: any): any;
    export function getShader(gl: any, url: any, type: any): Promise<{}>;
}
declare module "common/import-defaults" {
    export const defaults: {
        pick_texture_template_by_material: boolean;
        pick_texture_template_by_pixels: boolean;
        pick_texture_template_by_suffix: boolean;
        reverse_forward_axis: boolean;
    };
    export function getSetting(settings: any, keyName: any): any;
}
declare module "common/project-utils" {
    export function getProjectDirectoryName(): any;
    export function getSettings(settingsName: any): Promise<any>;
    export function setSettings(settingsName: any, value: any): Promise<any>;
    export function getProjectFileSettings(): Promise<any>;
    export function getProjectFileSetting(settingName: any): Promise<any>;
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
declare module "services/data-type-service" {
    export class DataTypeResource {
        isProcessed: boolean;
        extension: any;
        exportedType: any;
        types: any;
        constructor(types: any, exportedType: any, extension: any);
        static load(data: any, internalTypeLookup?: {}): DataTypeResource;
    }
    export class DataTypeRegistry {
        private _extensionTypeLookup;
        private _typeResources;
        private _builtInTypes;
        constructor();
        loadTypeResources(resourceNames: any, readResource: any): Promise<{}[]>;
        loadTypeResource(resourceName: any, readResource: any): Promise<any>;
        private registerTypeDefinition(resourceName, typeDefinition);
        private clear();
        isTypeResourceLoaded(resourceName: any): boolean;
        getTypeByResourceName(resourceName: any): any;
        getTypeByExtension(extension: any): any;
        private _processTypeResource(resourceName, getTypeResource);
    }
    export const typeRegistry: DataTypeRegistry;
    export function isTypeProcessed(type: any): boolean;
    export function processType(type: any): any;
    export function resolveTypeFile(resourceName: any): Promise<any>;
    export function resolveTypeFiles(resourceNames: any): Promise<{}[]>;
    export function createDefaultValue(typeDef: any): any;
}
declare module "services/import-service" {
    export let supportedReImportExtension: string[];
    export let textureTemplateCache: any;
    export let assetServer: any;
    export function batchImport(): Promise<any>;
    export function checkForExportImpact(paths: any): Promise<any>;
    export function getSceneFileToReimport(file: any): Promise<any>;
    export function importSceneAnimation(file: any, sceneImportOptions: any): Promise<any>;
    export function importPackage(filePath: any, selectedItems: any, destination: any): Promise<any>;
    export function raiseImportEvent(files: any, userInteraction: any): Promise<any>;
    export function javascriptImportJobsCompleted(files: any): Promise<any>;
    export function on(event: any, handler: any): OffHandler;
    export function off(event: any, handler: any): Promise<any>;
    export function ready(): Promise<any>;
    export function setTemplateCache(cache: any): void;
    export function setAssetServer(instance: any): void;
    export function runImports(assetToImport: any): Promise<any>;
}
declare module "foundation/asset-server" {
    class AssetServer {
        _callbacks: {};
        connectionReady: Promise<{}>;
        _connectionReadyReject: any;
        _connectionReadyResolve: any;
        connection: any;
        constructor();
        close(): void;
        updateVirtualFile(path: any, data: any): Promise<any>;
        removeVirtualFile(path: any): Promise<any>;
        ready(): Promise<{}>;
        isClosed(): any;
        sendVirtualFileCommand(commandData: any, path: any, removeCachedFile?: any): Promise<any>;
        checkTextureCompression(files: any, data: any): Promise<{}>;
        sendCheckTextureCompressionCommand(commandData: any, files: any): Promise<{}>;
        convertScene(commandData: any, files: any, options: any, wantSceneData: any, extractEmbedded: any): Promise<any>;
        compile(platform: any, files: any): Promise<any>;
        _handleEngineMessage(assetServer: any, data: any): void;
        _triggerCallbacksWithError(error: any): void;
        _handleConnectionClosed(): void;
        _handleConnectionOpened(payload: any): void;
    }
    export = AssetServer;
}
declare module "services/scene-service" {
    export function generateImportOptions(): Promise<any>;
    export function setSourceAssetPath(project: any, path: any, sourceFileAbs: any, sourceArtPath: any): any;
    export function readScenes(scenes: any, wantSceneData: any, extractEmbedded: any): Promise<any>;
    export function findSharedResource(objectName: any, fileExtension: any, directories: any): Promise<any>;
    export function getAssetServer(): any;
    export function loadScene(sceneFilename: any, importOptions: any, extractEmbedded: any): any;
}
declare module "common/import-utils" {
    import "extensions/views";
    import "services/file-system-service";
    export class ImportDialog {
        processImportOption: any;
        invalidOptions: boolean;
        categories: any[];
        postProcessCategories: Function;
        hideDialog: boolean;
        files: any;
        setDefaultValues: any;
        options: any;
        pluginName: any;
        importOptions: any;
        constructor(importOptions: any, pluginName: any, options: any, files: any, destination: any, setDefaultValues: any, hideDialog?: boolean, postProcessCategories?: Function);
        private _prepareImportOptions();
        private _prepareImportOption(importType);
        show(): any;
    }
    export function getTypeFiles(types: any, extension: any): any;
    export function getImportOptionsTypes(extension: any): any;
    export function genericImport(importOptions: any, pluginName: any, options: any, files: any, destination: any, setDefaultValues: any): ImportDialog;
    export function writeAssetSJSONFile(destination: any, content: any, files_changed: any): Promise<boolean>;
    export function copyFileIntoProject(file: any, destinationDirectory: any, overwrite: any): Promise<any>;
    export function syncFileMakeWritable(source: any, dest: any, files_changed: any): boolean;
    export function writeFileIfChanged(path: any, text: any): void;
    export function sceneImportOptionsExtensions(): string[];
    export function readImportOptionsForScene(path: any): any;
    export function gatherImportSettings(importState: any, imports: any): Promise<any>;
    export function getSkeletonPath(relativePath: any): Promise<any>;
    export function dirnameWithoutDirDot(path: any): string;
    export function animationStaticGeometryMessage(): string;
    export function animationCreateSkeletonMessage(): string;
}
declare module "common/input-utils" {
    export let InputType: {
        keydown: number;
        keyup: number;
        keypress: number;
        mousedown: number;
        mouseup: number;
        mousemove: number;
        mousewheel: number;
    };
    export class InputForwarder {
        canvas: any;
        context: any;
        opts: any;
        eventQueue: any[];
        constructor(canvas: any, opts: any);
        initEvents(): void;
        registerEvent(type: any, handler: any, capture: any): void;
        captureEvent(type: any, payload: any): any;
        flushQueue(): void;
    }
}
declare module "common/interpolate" {
    export namespace number {
        function linear(start: number, end: number, t: number): number;
    }
}
declare module "common/jquery-ext" {
}
declare module "common/json-path" {
    export function arrayToPath(pointerArray: any, prependDelimiter?: boolean, appendDelimiter?: boolean, delimiter?: string): any;
    export function arrayToPointer(pointerArray: any): any;
    export function pathToArray(path: any): any;
    export function pointerToPath(pointer: any): any;
}
declare module "common/key-validator" {
    export function keydown(options: any): void;
}
declare module "common/preview-utils" {
    export function sendToViewport(viewportName: any, methodName: any, ...args: any[]): Promise<{}[]>;
    export function sendToViewportWithEngine(engine: any, viewportName: any, methodName: any, ...args: any[]): Promise<{}[]>;
    export function isAssetAvailable(asset: any): Promise<{}>;
}
declare module "common/recursion-provider" {
}
declare module "common/semver" {
    export class SemVer {
        constructor(obj: any);
        toString(): string;
        static parse(version: any): SemVer;
        static stringify(...args: any[]): string;
        static readonly Range: typeof SemVerRange;
    }
    export class SemVerRange {
        conditions: any;
        constructor(arr: any);
        satisfies(version: any): boolean;
        toString(): string;
        static parse(str: any): SemVerRange;
        static stringify(...args: any[]): string;
    }
}
declare module "common/string-utils" {
    export function isDigit(chr: string): boolean;
    export function isUpper(chr: string): boolean;
    export function isLower(chr: string): boolean;
    export function isLetter(chr: string): boolean;
    export function toTitleCase(str: string): string;
    export function toSpaceCamelCase(str: string): string;
}
declare module "common/team-city" {
    export function padThree(n: any): any;
    export function pad(n: any): any;
    export function isoDateString(d: any): string;
    export function escape(str: any): string;
    export function log(message: any, attrs: any): string;
}
declare module "common/test-utils" {
    export const customMatchers: {
        toBeArray: () => {
            compare: (actual: any) => {
                pass: any;
                message: any;
            };
        };
        toStartWith: () => {
            compare: (actual: any, expected: any) => {
                pass: any;
                message: any;
            };
        };
        toEndWith: () => {
            compare: (actual: any, expected: any) => {
                pass: any;
                message: any;
            };
        };
        toBeValid: () => {
            compare: (actual: any) => {
                pass: any;
                message: any;
            };
        };
        toBeInstanceOf: () => {
            compare: (value: any, klass: any) => {
                pass: any;
                message: any;
            };
        };
        toBeAlmostEqual: () => {
            compare: (lhs: any, rhs: any) => {
                pass: boolean;
                message: string;
            };
        };
        toBeGreaterThanOrEqual: () => {
            compare: (actual: any, expected: any) => {
                pass: boolean;
                message: string;
            };
        };
    };
    export function runTestSpec(rootHref: any, testSpec: any): void;
    export function good(): any;
    export function validatePromise(promise: any, successHandler: any, done: any): void;
    export function validatePromiseAsync(promise: any, successHandler: any, done: any): void;
    export function compile($compile: any, scope: any, template: any): Promise<{}>;
    export function waitFor(condCallback: any, timeoutMs: any): Promise<{}>;
    export function waitForPromise(condCallback: any, timeoutMs: any): Promise<{}>;
    export function initializeSpec(spec: any, onInit: any): void;
    export function itValidExtension(parser: any, name: any, data: any, testCallback: any): void;
    export function itInvalidExtension(parser: any, name: any, data: any, errMsg: any): void;
}
declare module "common/tree-utils" {
    export function getNode(isNodeForPathToken: any, nodes: any, pathToken: any): any;
    export function removeNode(isNodeForPathToken: any, nodes: any, pathToken: any): void;
    export function getOrAddNode(isNodeForPathToken: any, isNodeLessThanPathToken: any, createNodeForPathToken: any, nodes: any, path: any, pathToken: any, isLastToken: any, meta: any): any;
    export function getPathTrees(insertPathsInTrees: any, getOrAddChildNodeArray: any, separator: any, paths: any): any[];
}
declare module "common/tree-view-utils" {
    import Event = require("common/event");
    export function compareStrings(str1: any, str2: any): boolean | -1;
    export function createWrapperFromViewModel(marshallingService: any, treeViewModel: any, callback: any): void;
    export function createRemoteTreeModelWrapper(marshallingService: any, remoteObjectName: any, callback: any): void;
    export interface ITreeModelNode {
        IsExpanded: boolean;
        IsHiddenWhenChildrenEmpty: boolean;
        Name: string;
        Type: string;
        NodeId: number;
        Children: ITreeModelNode[];
        ChildrenIds: number[];
        ParentNodeId: number;
        parent: ITreeModelNode;
        deleteMe: boolean;
        lostChildren: boolean;
    }
    export class TreeModel extends Event {
        private _id;
        SelectedNodes: any[];
        nodeRemoved: any;
        FlatList: any[];
        private _root;
        private _nodeOrderSelector;
        private _rootOptions;
        private _rootTitle;
        constructor(title: string, options?: any);
        setNodeOrderSelector(nodeOrderSelector: any): void;
        getNodeName(node: any): any;
        getNodeType(node: any): any;
        isRootNode(node: any): boolean;
        isGroupNode(node: any): boolean;
        getRoot(): any;
        getChildByName(node: any, name: any): any;
        defaultNode(): {
            IsExpanded: boolean;
            IsHiddenWhenChildrenEmpty: boolean;
            Name: string;
            Type: string;
            NodeId: number;
            ParentNodeId: number;
            Children: any[];
            ChildrenIds: any[];
        };
        buildFlatList(): void;
        traverseTree(node: any, callback: any): void;
        getParentNode(node: any): any;
        addNode(parent: any, title: any, type: any, options: any, doNotUpdateTree?: boolean): ITreeModelNode;
        removeNode(nodeToRemove: any, doNotCleanup?: boolean): void;
        removeNodes(nodesToRemove: any): any;
        modifyNode(node: any, parent: any, title: any, type: any, options: any, doNotUpdateTree: any): any;
        canBeSelected(node: any): boolean;
        clear(): void;
        refresh(forceRedraw: any, scrollToName?: any): void;
        private _createNode(title, type, options);
    }
    export function createTree(title: any, children: any, options: any): TreeModel;
    export function createNode(title: any, type: any, children: any, options: any): {
        title: any;
        type: any;
        children: any;
        options: any;
    };
    export class TreeNodeAction {
        icon: any;
        imgIcon: string;
        imgIconClass: string;
        label: string;
        parentNodeId: any;
        tooltip: string;
        constructor(parentNodeId: number);
        getIcon(): any;
        getImgIcon(): string;
        getImgIconClass(): string;
        getLabel(): string;
        getTooltip(): string;
        onClick(event: any): void;
        onDoubleClick(event: any): void;
    }
}
declare module "common/vector" {
    export function angle(a: any, b: any): number;
    export function between(a: any, b: any): number[];
    export function distance(a: any, b: any): number;
    export function dot(a: any, b: any): number;
    export function length(a: any): number;
    export function normalize(a: any): any;
    export function scale(a: any, b: any): number[];
    export function divide(a: any, b: any): number[];
    export function add(a: any, b: any): any[];
    export function subtract(a: any, b: any): number[];
    export function min(a: any, b: any): number[];
    export function max(a: any, b: any): number[];
    export class Vector3 {
        x: number;
        y: number;
        z: number;
        constructor(x?: number, y?: number, z?: number);
        toSyntax(): string;
    }
    export class Quaternion extends Vector3 {
        w: number;
        constructor(x: any, y: any, z: any, w?: number);
        toSyntax(): string;
    }
}
declare module "foundation/bsi-exporter" {
    export const ChannelName: {
        position: string;
        normal: string;
        texcoord: string;
        tangent: string;
        binormal: string;
        color: string;
        blendweights: string;
        blendindices: string;
        alpha: string;
    };
    export const ChannelType: {
        float1: string;
        float2: string;
        float3: string;
        float4: string;
        matrix4x4: string;
        quaternion: string;
        float3_cmp_11_11_10: string;
        half1: string;
        half2: string;
        half3: string;
        half4: string;
        ubyte4: string;
        short1: string;
        short2: string;
        short3: string;
        short4: string;
    };
    export class Node {
        local: number[];
        parent: string;
        _name: string;
        geometries: Geometry[];
        children: any;
        constructor(name: string, local: number[], parent?: string);
        addGeometry(name: any): Node;
        addChild(name: any, local: any): Node;
    }
    export class Indices {
        size: number;
        type: string;
        streams: number[][];
        constructor(size: number);
        addStream(stream: number[]): Indices;
    }
    export interface Channel {
        index: number;
        name: string;
        type: string;
    }
    export class Stream {
        size: number;
        stride: number;
        channels: Channel[];
        data: number[];
        constructor(size: number, stride: number);
        addChannel(name: any, type: any): Stream;
        setData(data: number[]): Stream;
    }
    export interface MaterialDesc {
        name: string;
        primitives: number[];
    }
    export class Geometry {
        materials: MaterialDesc[];
        streams: Stream[];
        indices: Indices;
        constructor();
        addMaterial(name: string, primitives: number[]): Geometry;
        addStream(size: number, stride: number): Stream;
        setIndices(size: number): Indices;
    }
    export class Bsi {
        source_path: string;
        geometries: any;
        nodes: any;
        constructor();
        addGeometry(id: string | number): Geometry;
        addNode(name: string, local: number[]): Node;
        sourcePath: string;
    }
}
declare module "foundation/command-history" {
    export enum CommandType {
        Command = 0,
        Script = 1,
        Snippet = 2,
    }
    export class CommandHistoryItem {
        Type: CommandType;
        Command: string;
        constructor(command: string, type: CommandType);
    }
    export enum CommandModes {
        Command,
        Lua,
    }
    export class CommandHistory {
        static MaxHistoryItemsToSave: number;
        private static ModeKeyName;
        private static SettingsKeyName;
        private historyIndex;
        mode: string | CommandModes;
        items: CommandHistoryItem[];
        constructor();
        add(item: CommandHistoryItem): void;
        save(): void;
        getPreviousHistoryCommand(): CommandHistoryItem;
        getNextHistoryCommand(): CommandHistoryItem;
        private load();
        private setHistoryIndexPosition(position);
    }
}
declare module "services/data-service" {
    import "external/json-patch";
    export const NO_DIR = "";
    export const GLOB_GROUP_RX: RegExp;
    export const DEFAULT_FETCH_OPTIONS: {
        content: boolean;
        serializer: any;
    };
    export const PatchOperation: {
        Replace: string;
        Add: string;
        Remove: string;
    };
    export class AssetGlob {
        value: any;
        filter: boolean;
        constructor(pattern: any);
        isNot(): boolean;
        hasGroup(): boolean;
        hasAny(): boolean;
        isRecursive(): boolean;
        parts(): any;
        regex(): RegExp;
        static hasGroupTokens(s: any): boolean;
        static hasWildCards(s: any): boolean;
        static readonly NOT: string;
        static readonly ANY: string;
        static readonly GROUP_BEGIN: string;
        static readonly GROUP_END: string;
        static readonly GROUP_SEPARATOR: string;
        static readonly ALL_RECURSIVE: string;
        static readonly GROUP_TOKENS: string[];
        static readonly WILD_CARD_CHARS: string[];
    }
    export class AssetUri {
        selector: any;
        type: any;
        name: any;
        constructor(name: any, type: any, selector?: any);
        path(): any;
        dir(): any;
        fileName(withoutExtension: any): any;
        isGlob(): boolean;
        isComplete(): boolean;
        walk(): IterableIterator<any>;
        match(rhs: any): boolean;
        static parse(query: any): AssetUri;
        static tryParse(uri: any): AssetUri;
        static isValid(uri: any): boolean;
        static isValidPart(s: any): boolean;
        static readonly PATH_SEPARATOR: string;
        static readonly SECTION_SEPARATOR: string;
        static readonly TYPE_SEPARATOR: string;
        static readonly INVALID_CHARS: string[];
    }
    export class Serializer {
        read(value: any): void;
        write(value: any, asBinary?: boolean): void;
        static find(assetType: any, options?: {
            content: boolean;
            serializer: any;
        }, defaultSerializer?: any, throwIfNotExists?: boolean): any;
    }
    export class PassthroughSerializer extends Serializer {
        read(value: any): any;
        write(value: any): any;
    }
    export class SJSONSerializer extends Serializer {
        read(value: any): any;
        write(value: any, asBinary: any): any;
    }
    export class Asset {
        serializer: any;
        lock: any;
        stats: any;
        value: any;
        revision: any;
        uri: AssetUri;
        constructor(uri: any, value?: any, stats?: any, serializer?: any);
        updateRevision(): void;
        serializedValue(overriddenSerializer: any): any;
        setRevision(revision: any): any;
        duplicate(uri: any): Asset;
        alias(uri: any): Asset;
    }
    export class Value {
        constructor(v: any);
        static purify(v: any): any;
        static areEquals(a: any, b: any): any;
    }
    export class AssetLock {
        handle: any;
        constructor(handle: any);
    }
    export class AssetDiff {
        to: any;
        from: any;
        patch: any;
        uri: any;
        constructor(uri: any, patch: any, from: any, to?: any);
        isDirty(): boolean;
        affects(propertyPath: any): boolean;
        apply(obj: any, validate?: boolean): any;
        compare(value: any): boolean;
        rollback(obj: any, validate: any): any;
        _reversedPatched(): any;
        static generate(base: any, value: any): any;
    }
    export class Command {
        applied: boolean;
        info: any;
        diffs: any;
        assets: any;
        name: any;
        id: any;
        constructor(name: any, assets: any, diffs: any, info: any);
        static createFromPatches(name: any, assets: any, patches: any, info: any): Command;
        undo(): any;
        redo(): any;
    }
    export class Journal {
        lastPost: Promise<void>;
        transactionCursor: number;
        transactions: any[];
        db: any;
        observes: Map<any, any>;
        assets: any[];
        id: any;
        constructor(db: any, assets: any);
        observeAssets(assets: any): void;
        log(name?: any, transient?: boolean, details?: any): Promise<any>;
        logCommand(command: any, details: any): Promise<any>;
        logAssets(assets: any, name?: any, transient?: boolean, details?: any): Promise<any>;
        applyDiffs(assets: any, diffs: any, name?: any, isTransient?: boolean, details?: any): Promise<any>;
        applyPatches(assets: any, patches: any, name?: any, isTransient?: boolean, details?: any): Promise<any>;
        isEmpty(): any;
        canUndo(): boolean;
        canRedo(): boolean;
        commit(assets: any): any;
        rollback(iterations?: number): Promise<any[]>;
        reroll(iterations?: number): Promise<any[]>;
        flush(): Promise<void>;
        stopRecording(): Promise<void>;
        syncObservedAssets(updatedAssets: any): void;
        _post(assets: any): Promise<any>;
        static readonly ROLLBACK_ALL: number;
    }
    export class Candidate {
        children: any;
        value: any;
        name: any;
        constructor(name: any, value: any);
    }
    export class Status {
        msg: any;
        code: any;
        constructor(code: any, msg?: any);
        static readonly OK: number;
        static readonly CLOSED: number;
        static readonly NOT_READY: number;
        static readonly INITIALIZING: number;
        static readonly FAILED: number;
        static readonly UNKNOWN: number;
    }
    export class DataStore {
        url: URL;
        events: any[];
        constructor(url: any);
        close(): void;
        get(uri: any, options: any): void;
        post(asset: any): void;
        lock(asset: any): Promise<any>;
        unlock(asset: any): Promise<any>;
        save(asset: any): void;
        list(uri: any): void;
        remove(uri: any): void;
        status(): void;
        on(name: any, uri: any, callback: any): () => any;
        findEvent(name: any, uri: any): any;
        static findRecursiveCandidates(match: any, candidates: any, enumCallback: any): any[];
        static findCandidates(glob: any, candidates: any, enumCallback: any): any[];
        static getCandidates(uri: any, initialCandidate: any, enumerator?: any): any[];
    }
    export class Database {
        store: DataStore;
        base: URL;
        constructor(base: any);
        close(): void;
        url(): string;
        get(uris: any, options?: {
            content: boolean;
            serializer: any;
        }): Promise<any>;
        post(assets: any): Promise<void[]>;
        save(assets: any): Promise<void[]>;
        commit(assets: any): Promise<void[]>;
        diff(asset: any, base?: any): Promise<any>;
        record(assets: any, diffs: any): Journal;
        list(uri: any): void;
        info(uris: any): Promise<any>;
        status(): void;
        remove(uris: any): Promise<any>;
        changes(assets: any, callback: any): () => void;
        _post(assets: Asset[], hooks?: any): Promise<void[]>;
        static registerProtocolStore(protocol: any, handler: any): void;
        static unregisterProtocolStore(protocol: any): void;
        static registerTypeSerializer(typeName: any, serializer: any): any;
        static unregisterTypeSerializer(typeName: any): any;
        static readonly IN_MEMORY_PROTOCOL: string;
    }
    export const SerializerByType: {
        ini: SJSONSerializer;
        unit: SJSONSerializer;
        entity: SJSONSerializer;
        material: SJSONSerializer;
        s2d: PassthroughSerializer;
        lua: PassthroughSerializer;
    };
    export function mount(base: any): Database;
    export function fetchOptions(options: any): any;
    export { AssetGlob as Glob };
    export { AssetUri as Uri };
}
declare module "foundation/data-server-store" {
    import dataService = require("services/data-service");
    export const DataStore: typeof dataService.DataStore;
    export const LOCAL_DATA_SERVER_IP = "127.0.0.1";
    export const LOCAL_DATA_SERVER_PORT: number | [number, number];
    export const LOCAL_DATA_SERVER_NAME = "dataserver";
    export class DataServerStore extends DataStore {
        promise: Promise<{}>;
        mounts: any;
        sourceDirectory: any;
        userSecretKey: any;
        connected: boolean;
        _socket: any;
        _nextRequestId: number;
        _pendingRequests: {};
        constructor(url: any);
        handshake(e: any): Promise<void>;
        close(): void;
        sendMessage(msg: any): Promise<any>;
        onmessage(msg: any): void;
        get(uri: any, options: any): Promise<{}[]>;
        list(uri: any): Promise<any>;
        post(asset: any): Promise<any>;
        save(asset: any): Promise<any>;
        remove(uri: any): Promise<{}[]>;
        status(): dataService.Status;
        lock(): Promise<boolean>;
        unlock(): Promise<boolean>;
        _getLocalAsset(uri: any, options: any): dataService.Asset;
        _buildAsset(uri: any, data: any, options: any): dataService.Asset;
        _getStats(uri: any): FileStats;
        _getRoot(uri: any): any;
        _getLocalFilePath(uri: any): string;
        _list_paths(uri: any): Promise<any>;
        _writeInMemory(asset: any, options?: any): Promise<any>;
        _emitChangeNotifForPaths(paths: any, actions: any): void;
        _onChangeNotifications(msg: any): void;
        static createFileAccessToken(dir: any): void;
        static readUserSecretKey(): string;
    }
    export function mount(host: any, port: any, name: any): Promise<any>;
    export function defaultDb(): Promise<any>;
}
declare module "foundation/document-editing" {
    export function updateTabResourceName(assetName: string, dirty?: boolean): void;
    export function openResourceEditor(viewName: string, resource: any, opts?: any): Promise<any>;
    export function focusResourceEditorEvent(viewName: any): string;
    export function focusResourceEditor(): void;
    export function handleOpenResourceEditor(viewName: any, resource: any, opts: any): Promise<void | {}>;
    export const DocumentEditingAPI: {
        updateTabResourceName: (assetName: string, dirty?: boolean) => void;
        updateTabName: (name: any, dirty?: any) => void;
        getToolName: any;
        getDocking: any;
        getParentTab: any;
        isDirty: any;
        save: any;
        discard: any;
        getDocumentName: any;
        getResourcePath: any;
        EventNames: {
            UNDO: string;
            REDO: string;
            SAVE: string;
            OPEN: string;
        };
    };
    export function validateResourceEditor(): void;
    export function setupMultiResourceEditor(): void;
    export function setupSingleResourceEditor(viewName: string, ignoreValidation?: boolean, ignoreShortcuts?: boolean): void;
}
declare module "foundation/file-system-watcher" {
    class FileSystemWatcher {
        idleId: number;
        watcher: any;
        callback: any;
        path: any;
        constructor(path: any, callback: any);
        poll(): void;
        deferPoll(): void;
        stop(): void;
    }
    export = FileSystemWatcher;
}
declare module "foundation/file-system-store" {
    import * as dataService from "services/data-service";
    export const DataStore: typeof dataService.DataStore;
    export const FILE_SYSTEM_PROTOCOL = "file:";
    export class FileSystemStore extends DataStore {
        watcher: any;
        SJSONFileSerializer: any;
        root: string;
        constructor(url: any);
        get(uri: any, options: any): Promise<dataService.Asset[]>;
        list(path: any): Promise<dataService.Asset[]>;
        lock(asset: any): Promise<dataService.AssetLock>;
        unlock(asset: any): Promise<any>;
        post(asset: any): Promise<any>;
        save(asset: any): Promise<boolean>;
        _onFileSystemNotification(changes: any): void;
        _resolvePath(asset: any): string;
        _resolveUriPath(uri: any): string;
        _ensureDirectoryExists(asset: any): void;
        static _enumerateItems(path: any): string[];
    }
}
declare module "foundation/level-editing-utils" {
    import { Quaternion, Vector3 } from "common/vector";
    export class LevelUnit {
        id: string;
        name: string;
        type: string;
        pos: Vector3;
        rot: Quaternion;
        scale: Vector3;
        pivot: Vector3;
        script_data: any;
        constructor(name: string, type: string, pos: Vector3, rot: Quaternion, scale: Vector3, pivot: Vector3, script_data?: any);
    }
    export function spawn(units: LevelUnit[]): Promise<any[]>;
    export function unspawn(units: LevelUnit[]): Promise<any[]>;
}
declare module "foundation/project-store" {
    import "foundation/file-system-store";
    export const STINGRAY_PROJECT_PROTOCOL = "sr:";
    export function mount(stingrayProjectPath: any, directoryMaps: any): any;
    export function current(): any;
}
declare module "foundation/unit-exporter" {
    export class Unit {
        sections: any;
        constructor();
        addRenderable(nodeId: any, nodeParams: any): void;
        addMaterial(slotName: any, materialName: any): void;
        save(baseFile: any): void;
    }
    export default Unit;
}
declare module "extensions/asset-types" {
    const assetTypes: any;
    export = assetTypes;
}
declare module "extensions/contextual-actions" {
    const contextualActions: any;
    export = contextualActions;
}
declare module "extensions/migrations" {
    const migrations: any;
    export = migrations;
}
declare module "extensions/node-customizers" {
    const nodeCustomizers: any;
    export = nodeCustomizers;
}
declare module "extensions/preview-behaviors" {
    const previews: any;
    export = previews;
}
declare module "extensions/viewports" {
    const viewports: any;
    export = viewports;
}
declare module "services/command-service" {
    import BaseService = require("services/base-service");
    export interface IUndoManager {
        CanUndo: boolean;
        CanRedo: boolean;
        LastUndoableName: string;
        FirstRedoableName: string;
        invokeMethod(methodName: any, args: any, options: any): Promise<any>;
    }
    export class CommandService extends BaseService {
        UndoManager: IUndoManager;
        constructor();
        undo(): Promise<any>;
        redo(): Promise<any>;
    }
    const _default: CommandService;
    export default _default;
}
declare module "services/content-database-service" {
    export function getLevelCameraNamesByObjectId(absoluteLevelPath: any): Promise<any>;
    export function loadLevelCameraNamesByObjectId(absoluteLevelPath: any): Promise<any>;
    export function getUnit(resourceName: any): Promise<any>;
    export function getMaterial(resourceName: any): Promise<any>;
    export function reload(): Promise<any>;
    export function on(event: any, handler: any): OffHandler;
    export function off(event: any, handler: any): Promise<any>;
    export function ready(): Promise<any>;
}
declare module "services/data-locator-service" {
    export function getEditorCoreViewPath(): Promise<any>;
    export function getStingrayBackEndPath(): Promise<any>;
    export function getStingrayRepositoryPath(): Promise<any>;
    export function getEditorCoreViewUrl(viewPath: any, args: any): Promise<any>;
    export function getEditorModulePath(): Promise<any>;
    export function getEditorCorePath(): Promise<any>;
    export function getEditorPluginPath(viewPath: any, args?: any): Promise<any>;
    export function getToolChainDirectory(): Promise<any>;
    export function getViewUrl(viewPath: any, args?: any): Promise<any>;
    export function getRootPath(): Promise<any>;
    export function getTestDataPath(): Promise<any>;
    export function on(event: any, handler: any): OffHandler;
    export function off(event: any, handler: any): Promise<any>;
    export function ready(): Promise<any>;
}
declare module "services/dcc-link-service" {
    export function getSourceArtFileFilter(): Promise<any>;
    export function on(event: any, handler: any): OffHandler;
    export function off(event: any, handler: any): Promise<any>;
    export function setCamera(channel: any, data: any): Promise<any>;
    export function editAssetAttemptCmdPortMaya(sessionId: any, mayaCommandPort: any): Promise<any>;
    export function handleUpdateLevel(data: any): Promise<any>;
    export function incrementMetric(metricId: any, applicationName: any, applicationVersion: any): Promise<any>;
}
declare module "services/debug-service" {
    export function watchesReport(): {
        nbWatches: number;
        nbScopes: number;
        scopes: {};
    };
    export function profileScopeDigest(selector: any): void;
    export function profileScopeMethod(selector: any, methodName: any): void;
    export function findExpensiveDigest(): void;
    export function countWatches(): void;
    export function profileIdleDigest(): void;
    export function openDevTools(): void;
    export function openProfiler(): Promise<any>;
    export function requestDomUpdate(): Promise<any>;
}
declare module "services/element-service" {
    export function getElementNames(elementType: any): Promise<any>;
    export function getElementBrowserTitle(elementType: any): Promise<any>;
}
declare module "services/entity-service" {
    export function changeSelection(entity: any, component: any): Promise<any>;
    export function editProperties(editorId: any, entityEditableModel: any): Promise<any>;
    export function saveAsAsset(entity: any, saveFilePath: any): Promise<any>;
    export function addComponent(entity: any, componentType: any): Promise<any>;
    export function deleteComponent(component: any): Promise<any>;
    export function restoreDeletedInheritedComponent(deletedComponent: any): Promise<any>;
    export function addChildEntity(entity: any, initialName: any): Promise<any>;
    export function transferOverridesToInheritedEntity(entity: any): Promise<any>;
    export function resetToInheritedEntity(entity: any): Promise<any>;
    export function makeUnique(entity: any): Promise<any>;
    export function renameEntity(entity: any, name: any): Promise<any>;
    export function renameComponent(component: any, name: any): Promise<any>;
}
declare module "node-editor/connection-definition" {
    export class ConnectionDefinition {
        id: string;
        fromNode: string;
        fromSlot: string;
        toNode: string;
        toSlot: string;
        invalid: boolean;
        label: string;
        constructor();
        readonly Id: string;
        readonly FromNode: string;
        readonly FromSlot: string;
        readonly ToNode: string;
        readonly ToSlot: string;
        readonly Invalid: boolean;
        readonly Label: string;
    }
}
declare module "node-editor/group-definition" {
    export class GroupDefinition {
        id: string;
        title: string;
        nodes: string[];
        groups: string[];
        notify: boolean;
        constructor();
        readonly Id: string;
        readonly Title: string;
        readonly Nodes: string[];
        readonly Groups: string[];
    }
}
declare module "node-editor/variable-definition" {
    export class VariableDefinition {
        id: string;
        name: string;
        value: any;
        type: string;
        isInput: boolean;
        isOutput: boolean;
        color: string;
        canEdit: boolean;
        allowMultiple: boolean;
        constructor();
        readonly Id: string;
        readonly Name: string;
        readonly Value: any;
        readonly Type: string;
        readonly IsInput: boolean;
        readonly IsOutput: boolean;
        readonly Color: string;
        readonly CanEdit: boolean;
        readonly AllowMultiple: boolean;
        getId(): string;
    }
}
declare module "node-editor/node-definition" {
    import { VariableDefinition } from "node-editor/variable-definition";
    export type PositionType = {
        x: number;
        y: number;
    } | {
        X: number;
        Y: number;
    };
    export class NodeDefinition {
        constructor();
        readonly Id: string;
        readonly Title: string;
        readonly Category: string;
        readonly Type: string;
        readonly Color: string;
        readonly Position: PositionType;
        readonly Width: number;
        readonly Invalid: boolean;
        readonly Elements: VariableDefinition[];
    }
}
declare module "node-editor/node-editor-graph" {
    import Event = require("common/event");
    import { ConnectionDefinition } from "node-editor/connection-definition";
    import { GroupDefinition } from "node-editor/group-definition";
    import { NodeDefinition } from "node-editor/node-definition";
    export interface INodeAutoCompleteData {
        id: string;
        label: string;
        tooltip?: string;
    }
    export interface INodeGraphContextMenuOptions {
        mousePosition: {
            x: number;
            y: number;
        };
        clipboardText: string;
        idUnderMouse: string;
        considerAsBackground: boolean;
    }
    export interface INodePositionByIdMap {
        [index: string]: {
            x: number;
            y: number;
        };
    }
    export class NodeEditorGraph extends Event {
        id: string;
        nodes: NodeDefinition[];
        groups: GroupDefinition[];
        connections: ConnectionDefinition[];
        selectedNodes: NodeDefinition[];
        selectedGroups: GroupDefinition[];
        selectedConnections: ConnectionDefinition[];
        nodeAutoCompleteData: INodeAutoCompleteData[];
        constructor(id: string);
        destroy(): void;
        clearSelection(): void;
        canConnect(fromNodeId: string, fromSlotId: string, toNodeId: string, toSlotId: string, ignoreCurrentConnections: boolean): boolean;
        readonly Nodes: NodeDefinition[];
        readonly Groups: GroupDefinition[];
        readonly Connections: ConnectionDefinition[];
        readonly Id: string;
        readonly SelectedNodes: NodeDefinition[];
        readonly SelectedGroups: GroupDefinition[];
        readonly SelectedConnections: ConnectionDefinition[];
        readonly NodeAutoCompleteData: INodeAutoCompleteData[];
        NodeAutoCompleteSelected(nodeId: string, x: number, y: number): void;
        DeleteSelected(): void;
        CutSelected(): void;
        CopySelected(): void;
        Paste(x: number, y: number): void;
        DuplicateSelected(x: number, y: number): void;
        GroupSelected(): void;
        UngroupSelected(): void;
        ShowContextMenu(options: INodeGraphContextMenuOptions): void;
        MoveNodesTo(newPositions: INodePositionByIdMap): void;
        Connect(fromNodeId: string, fromSlotId: string, toNodeId: string, toSlotId: string): void;
        DeleteConnections(connectionIds: string[]): void;
        ConnectionDoubleClicked(connectionId: string): void;
        SetSelection(objectIds: string[]): void;
        DragIntoGroup(groupId: string, childIds: string[], positions: INodePositionByIdMap): void;
        SetCollapsed(groupId: string, collapsed: boolean): void;
        ElementClicked(nodeId: string, slotId: string): void;
        ElementDoubleClicked(nodeId: string, slotId: string): void;
        GroupDoubleClicked(groupId: string): void;
        NodeDoubleClicked(nodeId: string): void;
        NodeResized(nodeId: string, width: number, x: number, y: number): void;
        PopulateCreateMenuFromNode(nodeId: string, slotId: string, x: number, y: number): void;
        DragNodesOnNode(nodeId: string, nodeIds: string[], positions: INodePositionByIdMap): void;
        BackgroundDoubleClicked(x: number, y: number): void;
        ConnectStateMachine(fromNodeId: string, fromTarget: string, toNodeId: string, toTarget: string): void;
        TagDoubleClicked(nodeId: string, slotId: string): void;
    }
}
declare module "flow/flow-connection" {
    import { ConnectionDefinition } from "node-editor/connection-definition";
    export interface IFlowConnectionModel {
        Id: string;
        Class: string;
        FromItem: string;
        FromNode: string;
        ToItem: string;
        ToNode: string;
        Priority?: number;
        FromEvent?: string;
        FromVariable?: string;
        ToEvent?: string;
        ToVariable?: string;
        Type?: string;
    }
    export class FlowConnection extends ConnectionDefinition {
        model: IFlowConnectionModel;
        flowContext: any;
        constructor(model: IFlowConnectionModel, flowContext: any);
        readonly Id: string;
        readonly FromNode: string;
        readonly FromSlot: any;
        readonly ToNode: string;
        readonly ToSlot: any;
        getId(): string;
        getFromNode(): string;
        getFromSlot(): any;
        getToNode(): string;
        getToSlot(): any;
        getFromItem(): string;
        getToItem(): string;
        static defaultEditorModel(): IFlowConnectionModel;
    }
}
declare module "flow/flow-variable" {
    import { VariableDefinition } from "node-editor/variable-definition";
    import { IExportContext } from "flow/flow-node";
    export interface IFlowVariableModel {
        Class?: string;
        Value?: any;
    }
    export class FlowVariable extends VariableDefinition {
        model: IFlowVariableModel;
        definition: any;
        displayName: string;
        flowContext: any;
        exportName: string;
        hidden: boolean;
        rebuildSlot: boolean;
        constructor(variableModel: IFlowVariableModel, flowContext: any, definition?: any);
        readonly Value: any;
        readonly DisplayName: string;
        readonly CanEdit: boolean;
        readonly AllowMultiple: boolean;
        init(node: any): void;
        getDisplayName(): string;
        getType(): string;
        getAllowMultiple(): boolean;
        setValue(value: any): void;
        getValue(): any;
        isHidden(): boolean;
        edit(editContext: any): void;
        update(context: any, withUndo?: boolean): void;
        exportRuntimeModel(exportContext: IExportContext): any;
        clear(): void;
        getExportName(): string;
        isEvent(): boolean;
        static defaultEditorModel(): IFlowVariableModel;
    }
}
declare module "flow/variables/flow-variable-definitions" {
    import { IFlowContext } from "flow/flow-graph";
    import { FlowNode, IExportContext } from "flow/flow-node";
    import { FlowVariable, IFlowVariableModel } from "flow/flow-variable";
    export interface IUnitVariableMode extends IFlowVariableModel {
        UseMyUnit: boolean;
    }
    export class UnitVariable extends FlowVariable {
        model: IUnitVariableMode;
        constructor(model: IUnitVariableMode, context: any, definition?: any);
        readonly CanEdit: boolean;
        setValue(value: boolean): void;
        getValue(): string;
        edit(context: any): void;
        exportRuntimeModel(): any;
        clear(): void;
    }
    export class ResourceVariable extends FlowVariable {
        types: string[];
        title: string;
        constructor(model: IFlowVariableModel, flowContext: any, definition?: any);
        init(node: any): void;
        readonly CanEdit: boolean;
        edit(context: any): void;
        browse(context: any, types: any): Promise<any>;
    }
    export class StringVariable extends FlowVariable {
        title: string;
        constructor(model: IFlowVariableModel, context: any, definition: any);
        init(node: any): void;
        edit(context: any): void;
    }
    export class CompileTimeStringVariable extends StringVariable {
        constructor(model: IFlowVariableModel, context: any, definition: any);
    }
    export class FloatVariable extends FlowVariable {
        constructor(model: IFlowVariableModel, context: any, definition: any);
        edit(context: any): void;
    }
    export class BooleanVariable extends FlowVariable {
        constructor(model: IFlowVariableModel, context: any, definition: any);
        edit(context: any): void;
    }
    export class Vector3Variable extends FlowVariable {
        constructor(model: IFlowVariableModel, context: any, definition: any);
        edit(context: any): void;
        exportRuntimeModel(): any;
    }
    export class QuaternionVariable extends FlowVariable {
        constructor(model: IFlowVariableModel, context: any, definition: any);
        readonly Value: string | void;
        edit(context: any): void;
        exportRuntimeModel(): any;
    }
    export class CustomTypeVariable extends FlowVariable {
        constructor(model: IFlowVariableModel, context: any, definition: any);
        init(node: any): void;
    }
    export class ResourceIdVariable extends StringVariable {
        constructor(model: IFlowVariableModel, flowContext: any, definition: any);
    }
    export class EnumVariable extends FlowVariable {
        title: string;
        choices: string[];
        constructor(model: IFlowVariableModel, context: any, definition: any);
        init(node: any): void;
        edit(context: any): void;
    }
    export class FlowResourceVariable extends ResourceVariable {
        constructor(model: IFlowVariableModel, flowContext: any, definition?: any);
        edit(context: any): void;
        browse(context: any, types: any): Promise<any[]>;
        static defaultEditorModel(): any;
    }
    export class EventVariable extends FlowVariable {
        constructor(model: IFlowVariableModel, flowContext: any, definition?: any);
        readonly CanEdit: boolean;
        isEvent(): boolean;
    }
    export interface ILevelObjectVariableModel extends IFlowVariableModel {
        Id: string;
    }
    export class LevelObjectVariable extends FlowVariable {
        levelObjectId: string;
        levelObjectType: string;
        constructor(model: ILevelObjectVariableModel, flowContext: IFlowContext, definition?: any);
        readonly CanEdit: boolean;
        getValue(): string;
        edit(context: any): void;
        exportRuntimeModel(exportContext: IExportContext): any;
        static defaultEditorModel(): ILevelObjectVariableModel;
    }
    export function createVariableFromType(type: string, model: IFlowVariableModel, node: FlowNode, definition?: any): any;
}
declare module "flow/flow-node" {
    import { NodeDefinition } from "node-editor/node-definition";
    import { FlowConnection } from "flow/flow-connection";
    import { FlowGraph, IFlowContext } from "flow/flow-graph";
    import { IValidationError } from "flow/flow-graph-validation";
    import * as flowUtils from "flow/flow-utils";
    import { FlowVariable } from "flow/flow-variable";
    export interface IFlowNodeModel {
        Class: string;
        Id: string;
        Category: string;
        Title: string;
        Width: number;
        NodeLocation: {
            X: number;
            Y: number;
        };
        Brief?: string;
        ColorCategory?: string;
    }
    export interface IExportContext {
        flow: FlowGraph;
        context: IFlowContext;
    }
    export class FlowNode extends NodeDefinition {
        model: IFlowNodeModel;
        flowContext: any;
        definition: any;
        elements: FlowVariable[];
        invalid: boolean;
        constructor(model: IFlowNodeModel, flowContext: any);
        readonly Id: string;
        readonly Title: string;
        readonly Category: string;
        readonly Type: string;
        readonly Color: any;
        readonly Position: {
            X: number;
            Y: number;
        };
        readonly Width: number;
        readonly Invalid: boolean;
        readonly Elements: any[];
        readonly Brief: string;
        getColorCategory(): string;
        setColorCategory(category: any): void;
        loadElements(model: any): void;
        reloadElements(): void;
        parseEvents(flowContext: any): Promise<boolean>;
        getId(): string;
        setId(id: any): void;
        getTitle(): string;
        setTitle(title: any): void;
        getCategory(): string;
        setCategory(category: any): void;
        getType(): string;
        setType(type: any): void;
        getPosition(): {
            X: number;
            Y: number;
        };
        setPosition(position: any): void;
        getWidth(): number;
        setWidth(width: any): void;
        setInvalid(invalid: any): void;
        getBrief(): string;
        setBrief(brief: any): void;
        exportRuntimeModel(exportContext: IExportContext): {
            type: any;
            id: string;
        };
        getExportName(): any;
        isDataDrivenFlowNodeType(type: any): boolean;
        getVariableBrowserStrings(element: any): Promise<any[]>;
        getVariableTypes(element: any): any[];
        getVariableBrowserTitle(element: any): string;
        getVariableEnumChoices(element: any): any[];
        visibleInEditor(editorType: flowUtils.FLOW_TYPES): boolean;
        getElementByName(name: string): FlowVariable;
        validate(context: IFlowContext, nodes: FlowNode[], connections: FlowConnection[]): IValidationError;
        static defaultEditorModel(): IFlowNodeModel;
        protected _isInputConnected(varName: string, connections: FlowConnection[]): boolean;
        protected _isInputSetOrConnected(input: FlowVariable, inputName: string, connections: FlowConnection[]): boolean;
        _exportVariables(exportContext: IExportContext, model: any): void;
        _exportConnections(exportContext: IExportContext, model: any): void;
        _exportCustoms(exportContext: any, model: any): void;
    }
}
declare module "flow/flow-script-node-validation" {
    export interface IScriptFlowNodeDocumentFormat {
        nodes: IScriptFlowNodeDefinition[];
    }
    export interface IScriptFlowNodeDefinition {
        name: string;
        category?: string;
        brief?: string;
        visibility?: "level" | "unit" | "all";
        query?: boolean;
        function?: string;
        function_map?: Array<[string, string]>;
        args?: IScriptFlowNodeArgumentsDefinition;
        returns?: IScriptFlowNodeReturnsDefinition;
    }
    export type ScriptFlowNodeSimpleArgumentType = "unit" | "entity" | "actor" | "mover" | "generic" | "vector3" | "quaternion" | "float" | "bool" | "string" | "instance_id" | "camera" | "material" | "id" | "light" | "mesh";
    export type ScriptFlowNodeReturnType = "unit" | "entity" | "actor" | "mover" | "vector3" | "quaternion" | "float" | "bool" | "string" | "instance_id" | "camera" | "material" | "id" | "light" | "mesh" | "event";
    export type ScriptFlowNodeDetailedArgumentType = ScriptFlowNodeSimpleArgumentType | "enum" | "resource" | "element";
    export type ScriptFlowNodeArgumentType = ScriptFlowNodeSimpleArgumentType | IScriptFlowNodeDetailedArgumentDefinition | string[];
    export interface IScriptFlowNodeArgumentsDefinition {
        [key: string]: ScriptFlowNodeArgumentType;
    }
    export interface IScriptFlowNodeReturnsDefinition {
        [key: string]: ScriptFlowNodeReturnType;
    }
    export interface IScriptFlowNodeDetailedArgumentDefinition {
        type: ScriptFlowNodeDetailedArgumentType;
        default?: string | number | boolean;
        choices?: string[];
        extension?: string;
        filter?: string;
    }
    export function invalidArgumentDeclaration(nodeName: string, argumentName: string, propertyName: string, error: string): string;
    export function invalidPropertyDeclaration(name: string, property: string, error: string): string;
    export function invalidReturnDeclaration(nodeName: string, returnName: string, error: string): string;
    export function undeclaredFunctionDeclaration(nodeName: string): string;
    export function isSimpleArgumentType(type: string): boolean;
    export function isReturnValueType(type: string, isQueryNode?: boolean): boolean;
    export function isValidDefaultForSimpleArgument(type: string, value: any): boolean;
    export function getIssuesWithResourceArgumentDeclaration(nodeName: string, argumentName: string, argumentDeclaration: IScriptFlowNodeDetailedArgumentDefinition): string[];
    export function getIssuesWithElementArgumentDeclaration(nodeName: string, argumentName: string, argumentDeclaration: IScriptFlowNodeDetailedArgumentDefinition): string[];
    export function getIssuesWithEnumArgumentDeclaration(nodeName: string, argumentName: string, argumentDeclaration: IScriptFlowNodeDetailedArgumentDefinition): string[];
    export function getIssuesWithSimpleArgumentDeclaration(nodeName: string, argumentName: string, argumentDeclaration: IScriptFlowNodeDetailedArgumentDefinition): string[];
    export function getIssuesWithArgumentDeclaration(nodeName: string, argumentName: string, argumentDeclaration: IScriptFlowNodeDetailedArgumentDefinition): string[];
    export function getIssuesWithScriptNodeDeclaration(node: IScriptFlowNodeDefinition): any[];
    export function validateScriptNodeReplacement(oldFlowNodes: IScriptFlowNodeDefinition[], newFlowNodes: IScriptFlowNodeDefinition[], issuesByPath: {}): IScriptFlowNodeDefinition[];
}
declare module "flow/nodes/flow-node-registry" {
    import { FlowNode } from "flow/flow-node";
    export function registerNodeType(type: string, constructor: typeof FlowNode, builtIn?: boolean): void;
    export function hasNodeType(type: string): boolean;
    export function getNodeConstructor(type: any): typeof FlowNode;
    export function getBuiltInNodes(): Array<typeof FlowNode>;
}
declare module "flow/nodes/built-in-nodes" {
    import { FlowConnection } from "flow/flow-connection";
    import { IFlowContext } from "flow/flow-graph";
    import { IValidationError } from "flow/flow-graph-validation";
    import { FlowNode, IFlowNodeModel } from "flow/flow-node";
    import * as flowUtils from "flow/flow-utils";
    import { IFlowVariableModel } from "flow/flow-variable";
    import * as flowVariableDefinitions from "flow/variables/flow-variable-definitions";
    export interface INestedFlowModel extends IFlowNodeModel {
        InEvents: string[];
        OutEvents: string[];
        InVariableNames: string[];
        InVariables: any[];
        OutVariableNames: string[];
        OutVariables: any[];
    }
    export interface IPrefixAndPath {
        prefix?: string;
        path: string;
    }
    export abstract class NestedFlow extends FlowNode {
        model: INestedFlowModel;
        constructor(model: INestedFlowModel, flowContext: any);
        clear(): void;
        loadElements(model: INestedFlowModel): void;
        getFlowResourcePath(): Promise<IPrefixAndPath[]>;
        parseEvents(flowContext: any): Promise<boolean>;
        appendSlots(flowPath: string, nodeDefinitions: any, prefix?: string): void;
        parseSlots(flowPrefixAndPaths: IPrefixAndPath[], nodeDefinitions: any): boolean;
        static defaultEditorModel(): INestedFlowModel;
        _sortTogether(names: any, vars: any): any;
        _mergeVariable(newNames: any, newVars: any, oldNames: any, oldVars: any): void;
        _prependPrefix(prefix: any, list: any, startIndex: any): void;
    }
    export interface IFlowSubroutineModel extends INestedFlowModel {
        Flow: IFlowVariableModel;
        Enable: IFlowVariableModel;
        Disable: IFlowVariableModel;
    }
    export class FlowSubroutine extends NestedFlow {
        model: IFlowSubroutineModel;
        constructor(model: IFlowSubroutineModel, flowContext: any);
        loadElements(model: IFlowSubroutineModel): void;
        getFlowResourcePath(): Promise<IPrefixAndPath[]>;
        parseEvents(flowContext: any): Promise<boolean>;
        validate(context: IFlowContext, nodes: FlowNode[], connections: FlowConnection[]): IValidationError;
        static defaultEditorModel(): any;
    }
    export interface ICustomScriptNodeModel extends IFlowNodeModel {
        Name: string;
        FlowNodesResource: string;
        Arguments: any[];
        ReturnValues: any[];
        InEvents: string[];
        OutEvents: string[];
        IsQuery: boolean;
    }
    export class CustomScriptNode extends FlowNode {
        model: ICustomScriptNodeModel;
        constructor(model: ICustomScriptNodeModel, flowContext: any);
        readonly Title: string;
        loadElements(model: any): void;
        getTitle(): string;
        setTitle(title: any): void;
        getFlowNodesResource(): string;
        setFlowNodesResource(flowNodesResource: any): void;
        getArguments(): any[];
        setArguments(args: any): void;
        getReturnValues(): any[];
        setReturnValues(returnValues: any): void;
        getInEvents(): string[];
        setInEvents(inEvents: any): void;
        getOutEvents(): string[];
        setOutEvents(outEvents: any): void;
        getIsQuery(): boolean;
        setIsQuery(isQuery: any): void;
        visibleInEditor(flowType: flowUtils.FLOW_TYPES): boolean;
        validate(context: IFlowContext, nodes: FlowNode[], connections: FlowConnection[]): IValidationError;
        static defaultEditorModel(): ICustomScriptNodeModel;
    }
    export interface ILevelObjectInstanceNode {
        allowDuplicateLevelObject: boolean;
    }
    export interface ILevelUnitModel extends INestedFlowModel {
        SetUnit: flowVariableDefinitions.ILevelObjectVariableModel;
        Unit: IFlowVariableModel;
        Type: string;
    }
    export class LevelUnit extends NestedFlow implements ILevelObjectInstanceNode {
        allowDuplicateLevelObject: boolean;
        constructor(model: ILevelUnitModel, flowContext: any);
        loadElements(model: ILevelUnitModel): void;
        getFlowResourcePath(): Promise<IPrefixAndPath[]>;
        getColorCategory(): string;
        visibleInEditor(flowType: flowUtils.FLOW_TYPES): boolean;
        static defaultEditorModel(): any;
    }
    export interface IExternalEventModel extends IFlowNodeModel {
        EventName: IFlowVariableModel;
        Out: IFlowVariableModel;
    }
    export class ExternalEvent extends FlowNode {
        constructor(model: IExternalEventModel, context: IFlowContext);
        loadElements(model: IExternalEventModel): void;
        validate(context: IFlowContext, nodes: FlowNode[], connections: FlowConnection[]): IValidationError;
        static defaultEditorModel(): any;
    }
    export interface ILevelFlowEventModel extends IFlowNodeModel {
        Event: IFlowVariableModel;
        In: IFlowVariableModel;
    }
    export class LevelFlowEvent extends FlowNode {
        constructor(model: ILevelFlowEventModel, context: IFlowContext);
        loadElements(model: ILevelFlowEventModel): void;
        visibleInEditor(flowType: flowUtils.FLOW_TYPES): boolean;
        validate(context: IFlowContext, nodes: FlowNode[], connections: FlowConnection[]): IValidationError;
        static defaultEditorModel(): ILevelFlowEventModel;
    }
    export interface IExternalInputModel extends IFlowNodeModel {
        Name: IFlowVariableModel;
    }
    export abstract class ExternalInput extends FlowNode {
        constructor(model: IExternalInputModel, context: IFlowContext);
        loadElements(model: IExternalInputModel): void;
        validate(context: IFlowContext, nodes: FlowNode[], connections: FlowConnection[]): IValidationError;
        static defaultEditorModel(): IExternalInputModel;
    }
    export interface IExternalOutputModel extends IFlowNodeModel {
        Name: IFlowVariableModel;
    }
    export abstract class ExternalOutput extends FlowNode {
        constructor(model: IExternalOutputModel, context: IFlowContext);
        loadElements(model: IExternalOutputModel): void;
        validate(context: IFlowContext, nodes: FlowNode[], connections: FlowConnection[]): IValidationError;
        static defaultEditorModel(): IExternalOutputModel;
    }
}
declare module "flow/flow-node-browse-functions" {
    export function invokeBrowseFunction(browseFuncName: any, args: any): Promise<any>;
}
declare module "flow/nodes/data-driven-flow-node" {
    import { FlowConnection } from "flow/flow-connection";
    import { IDataDrivenEnumDefinition } from "flow/flow-data-driven-node-validation";
    import { IFlowContext } from "flow/flow-graph";
    import { IValidationError } from "flow/flow-graph-validation";
    import { FlowNode, IFlowNodeModel } from "flow/flow-node";
    import * as flowUtils from "flow/flow-utils";
    import { IFlowVariableModel } from "flow/flow-variable";
    export interface IDataDrivenInputModel {
        Class: string;
        Hidden: boolean;
        RawName: string;
        Type: string;
        UIName: string;
        Variable: IFlowVariableModel;
    }
    export interface IDataDrivenOutputModel {
        RawName: string;
        UIName: string;
        Type: string;
        Variable: IFlowVariableModel;
    }
    export interface IDataDrivenFlowNodeModel extends IFlowNodeModel {
        ExportTypeName: string;
        Inputs: IDataDrivenInputModel[];
        Outputs: IDataDrivenOutputModel[];
        FlowNodesResourceKey: string;
    }
    export class DataDrivenFlowNode extends FlowNode {
        model: IDataDrivenFlowNodeModel;
        globals: any;
        constructor(model: IDataDrivenFlowNodeModel, flowContext: any);
        getExportName(): string;
        getExportTypeName(): string;
        setExportTypeName(exportTypeName: any): void;
        getColorCategory(): string;
        setColorCategory(colorCategory: any): void;
        getInputs(): IDataDrivenInputModel[];
        setInputs(inputs: IDataDrivenInputModel[]): void;
        getOutputs(): IDataDrivenOutputModel[];
        setOutputs(outputs: IDataDrivenOutputModel[]): void;
        loadElements(model: IDataDrivenFlowNodeModel): void;
        getVariableBrowserStrings(element: any): Promise<any>;
        getVariableTypes(element: any): string[];
        getVariableBrowserTitle(element: any): string;
        getVariableEnumChoices(element: any): IDataDrivenEnumDefinition[];
        isDataDrivenFlowNodeType(type: any): boolean;
        visibleInEditor(flowType: flowUtils.FLOW_TYPES): boolean;
        validate(context: IFlowContext, nodes: FlowNode[], connections: FlowConnection[]): IValidationError;
        static defaultEditorModel(): IDataDrivenFlowNodeModel;
        private _isRequiredInputSet(input, connections);
    }
}
declare module "flow/flow-migration" {
    import { IDataDrivenFlowNodeDefinitionInternal } from "flow/flow-data-driven-node-validation";
    import { IFlowContext, IFlowGraphModel } from "flow/flow-graph";
    import { FlowNode } from "flow/flow-node";
    import { IScriptFlowNodeDefinition, ScriptFlowNodeArgumentType, ScriptFlowNodeDetailedArgumentType } from "flow/flow-script-node-validation";
    import { CustomScriptNode } from "flow/nodes/built-in-nodes";
    import { DataDrivenFlowNode } from "flow/nodes/data-driven-flow-node";
    export const enum UPDATE_MODE {
        NO_UPDATE = 0,
        UPDATE = 1,
        UPDATE_AND_DIRTY = 2,
    }
    export function getScriptArgumentType(scriptArgumentDefinition: ScriptFlowNodeArgumentType): ScriptFlowNodeDetailedArgumentType;
    export function migrate(graph: IFlowGraphModel, nodeDefinitions: IDataDrivenFlowNodeDefinitionInternal[]): IFlowGraphModel;
    export function patchFlowNodes(nodes: FlowNode[], nodesToUpdate: FlowNode[], flowContext: IFlowContext): Promise<boolean>;
    export function patchDataDrivenFlowNodes(nodes: FlowNode[], nodeDefinitions: any[], nodesToUpdate: FlowNode[]): boolean;
    export function patchDataDrivenFlowNode(node: DataDrivenFlowNode, nodeDefinition: IDataDrivenFlowNodeDefinitionInternal): UPDATE_MODE;
    export function patchNestedFlowNodes(nodes: FlowNode[], nodesToUpdate: FlowNode[], flowContext: IFlowContext): Promise<boolean>;
    export function importProjectChangesForNode(node: FlowNode, flowContext: IFlowContext): Promise<boolean>;
    export function patchScriptFlowNodes(nodes: FlowNode[], scriptFlowNodeDefinitions: IScriptFlowNodeDefinition[], nodesToUpdate: FlowNode[]): boolean;
    export function patchScriptFlowNode(node: CustomScriptNode, scriptFlowNodeDefinition: IScriptFlowNodeDefinition): boolean;
    export function updateScriptFlowNode(node: CustomScriptNode, scriptFlowNodeDefinition: IScriptFlowNodeDefinition): boolean;
    export function parseScriptNodeArgumentDefinition(argumentName: string, scriptNodeArgumentDefinition: ScriptFlowNodeArgumentType): {
        rawName: string;
        type: ScriptFlowNodeDetailedArgumentType;
        defaultValue: string | number | boolean;
        choices: any[];
        filter: any;
    };
}
declare module "flow/flow-graph-validation" {
    import { FlowGraph, IFlowContext } from "flow/flow-graph";
    import { FlowNode } from "flow/flow-node";
    export interface IValidationError {
        nodes: FlowNode[];
        title: string;
        message: string;
    }
    export function validate(flowGraph: FlowGraph, flowContext: IFlowContext): Promise<IValidationError[]>;
    export function validateInvalidNodes(nodes: FlowNode[], context: IFlowContext): Promise<IValidationError[]>;
    export function validateDuplicateLevelObjects(nodes: FlowNode[], context: IFlowContext): Promise<IValidationError[]>;
    export function validateExternalSameNames(nodes: FlowNode[], context: IFlowContext): Promise<IValidationError[]>;
    export function validateNodes(nodes: FlowNode[], context: IFlowContext): Promise<IValidationError[]>;
    export function validateNestedConnections(nodes: FlowNode[], context: IFlowContext): Promise<IValidationError[]>;
    export function validateFlowType(nodes: FlowNode[], context: IFlowContext): Promise<IValidationError[]>;
    export function removeDuplicateConnections(nodes: FlowNode[], context: IFlowContext): Promise<IValidationError[]>;
    export function removeInvalidConnections(nodes: FlowNode[], context: IFlowContext): Promise<IValidationError[]>;
}
declare module "flow/flow-group" {
    import { GroupDefinition } from "node-editor/group-definition";
    export interface IFlowGroupModel {
        Id: string;
        Title: string;
        Collapsed: boolean;
        Nodes: string[];
        Groups: string[];
    }
    export class FlowGroup extends GroupDefinition {
        model: IFlowGroupModel;
        constructor(model: IFlowGroupModel);
        readonly Id: string;
        readonly Title: string;
        readonly Nodes: string[];
        readonly Groups: string[];
        readonly Collapsed: boolean;
        readonly IsEmpty: boolean;
        getId(): string;
        getTitle(): string;
        setTitle(title: any): void;
        getNodes(): string[];
        getGroups(): string[];
        getCollapsed(): boolean;
        setCollapsed(collapsed: any): void;
        static defaultEditorModel(): IFlowGroupModel;
    }
}
declare module "flow/flow-graph" {
    import { NodeEditorGraph } from "node-editor/node-editor-graph";
    import { FlowConnection, IFlowConnectionModel } from "flow/flow-connection";
    import { IDataDrivenFlowNodeDefinition } from "flow/flow-data-driven-node-validation";
    import { FlowGroup, IFlowGroupModel } from "flow/flow-group";
    import { FlowNode, IFlowNodeModel } from "flow/flow-node";
    import { IScriptFlowNodeDefinition } from "flow/flow-script-node-validation";
    import * as flowUtils from "flow/flow-utils";
    import { FlowVariable } from "flow/flow-variable";
    import * as builtInNodes from "flow/nodes/built-in-nodes";
    import { DataDrivenFlowNode } from "flow/nodes/data-driven-flow-node";
    export interface IFlowGraphModel {
        Nodes: IFlowNodeModel[];
        Groups: IFlowGroupModel[];
        Connections: IFlowConnectionModel[];
    }
    export interface IFlowContext {
        flowType: flowUtils.FLOW_TYPES;
        flowGraph: FlowGraph;
        flowNodeDefinitions: IDataDrivenFlowNodeDefinition[];
        scriptNodeDefinitions: IScriptFlowNodeDefinition[];
        objectIdsForVariable: (variable: FlowVariable) => string[];
        objectExists: (id: string) => boolean;
        objectName: (id: string) => string;
        objectType: (id: string) => string;
        exportObject: (variable: FlowVariable, id: string) => any;
        getObject: (id: string) => any;
    }
    export interface INodeCreationMap {
        [key: string]: (position: {
            x: number;
            y: number;
        }) => void;
    }
    export interface IRegistryCreationDictionary {
        dataDriven: INodeCreationMap;
        script: INodeCreationMap;
        builtin: INodeCreationMap;
    }
    export class FlowGraph extends NodeEditorGraph {
        nodes: FlowNode[];
        groups: FlowGroup[];
        connections: FlowConnection[];
        model: IFlowGraphModel;
        flowContext: IFlowContext;
        _nodeRegistryCreationDictionary: IRegistryCreationDictionary;
        _offHandlers: any[];
        constructor(graphModel: IFlowGraphModel, flowContext: IFlowContext);
        destroy(): void;
        canConnect(fromNodeId: any, fromSlotId: any, toNodeId: any, toSlotId: any, ignoreCurrentConnections?: boolean): boolean;
        NodeAutoCompleteSelected(nodeId: any, x: any, y: any): void;
        DeleteSelected(): void;
        GroupSelected(): void;
        UngroupSelected(): void;
        ShowContextMenu(options: any): void;
        MoveNodesTo(newPositions: any): void;
        Connect(fromNodeId: any, fromSlotId: any, toNodeId: any, toSlotId: any): void;
        DeleteConnections(connectionIds: any): void;
        SetSelection(objectIds: any): void;
        DragIntoGroup(groupId: any, childIds: any, positions: any): void;
        SetCollapsed(groupId: any, collapsed: any): void;
        ElementClicked(nodeId: any, slotId: any): void;
        DragNodesOnNode(nodeId: any, nodeIds: any, positions: any): void;
        updateSlot(node: FlowNode, slot: FlowVariable, rebuildSlots: boolean, withUndo: boolean): Promise<void>;
        exportRuntimeModel(): {
            nodes: any[];
        };
        emitNodeChanged(node: any): void;
        emitNodesAdded(nodes: any): void;
        emitNodesRemoved(nodeIds: any): void;
        emitGroupsAdded(groups: any): void;
        emitGroupsRemoved(groupIds: any): void;
        emitGroupChanged(group: any): void;
        emitGroupNodesAdded(groupId: any, nodeIds: any): void;
        emitGroupNodesRemoved(groupId: any, nodeIds: any): void;
        emitGroupGroupsAdded(groupId: any, groupIds: any): void;
        emitGroupGroupsRemoved(groupId: any, groupIds: any): void;
        emitConnectionsAdded(connections: any): void;
        emitConnectionsRemoved(connectionIds: any): void;
        emitSelectionChanged(nodesSelected: any, groupsSelected: any, connectionsSelected: any): void;
        emitFrameAll(): void;
        emitFrameSelected(): void;
        createNodeFromModel(model: IFlowNodeModel): FlowNode;
        createConnectionFromModel(model: any): FlowConnection;
        createGroupFromModel(model: any): FlowGroup;
        setSelection(objectIds: any, emitChanged?: boolean): void;
        deleteObjects(objectsToDelete: any): void;
        removeConnections(connectionsToRemove: any, withModel?: boolean, emitModelChange?: boolean): void;
        removeNodes(nodesToRemove: any, withModel?: boolean, emitModelChange?: boolean): void;
        removeGroups(groupsToRemove: any, withModel?: boolean, emitModelChange?: boolean): void;
        removeNodesFromParentGroups(nodesToRemove: any, emitModelChange?: boolean): void;
        removeGroupsFromParentGroups(groupsToRemove: any, emitModelChange?: boolean): void;
        addItemsToGroup(group: any, childIds: any, emitModelChange?: boolean): void;
        addNodeIdsToGroup(group: any, nodeIds: any, emitModelChange?: boolean): void;
        removeNodeIdsFromGroup(group: any, nodeIds: any, emitModelChange?: boolean): void;
        addGroupIdsToGroup(group: any, groupIds: any, emitModelChange?: boolean): void;
        removeGroupIdsFromGroup(group: any, groupIds: any, emitModelChange?: boolean): void;
        deleteOrphanedGroups(): void;
        groupObjects(objectsToGroup: any): void;
        ungroupObjects(objectsToUngroup: any): void;
        renameGroup(flowGroup: any, title: any, emitModelChange?: boolean): void;
        removeItemsFromGroup(objectsToRemove: any, emitModelChange?: boolean): void;
        setGroupCollapsed(groupIds: any, collapsed: any, emitModelChange?: boolean): void;
        validateFlow(): Promise<boolean>;
        static create(graphModel: IFlowGraphModel, flowContext: IFlowContext): Promise<FlowGraph>;
        _emitGraphChanged(msg: any, transient?: boolean): void;
        _getRebuildableSlot(node: any): any[];
        _areSlotsConnected(fromNode: any, fromSlot: any, toNode: any, toSlot: any): any;
        _populateMenuWithNodes(menu: any, position: any, onClickCb?: any, showNodeFilterCb?: any): void;
        _isDataDrivenFlowNodeVisible(nodeDefinition: any, showNodeFilterCb: any): any;
        _isScriptFlowNodeVisible(nodeDefinition: any, showNodeFilterCb: any): any;
        _insertMenuAction(category: any, name: any, tooltip: any, enabled: any, categoryToMenu: any, onClick: any): void;
        _buildMenuFromCategories(categoryToMenu: any, menu: any): void;
        _addNode(flowNode: any, emitModelChanged?: boolean): void;
        _addNodeToGroup(flowNode: any, flowGroup: any, emitModelChange?: boolean): void;
        _createDataDrivenFlowNode(nodeDefinition: any, position: any): DataDrivenFlowNode;
        _createScriptFlowNode(nodeDefinition: any, position: any): builtInNodes.CustomScriptNode;
        _createBuiltInNode(nodeClass: typeof FlowNode, position: any): FlowNode;
        _addConnection(flowConnection: any, emitModelChange?: boolean): void;
        _addGroup(flowGroup: any, emitModelChange?: boolean): void;
        _createGroup(groupName: any): FlowGroup;
        _updateDataDrivenFlowNodeAutoComplete(nodeDefinitions: any, showNodeFilter?: any): void;
        _updateScriptFlowNodeAutoComplete(nodeDefinitions: any, showNodeFilter?: any): void;
        _updateBuiltInNodeAutoComplete(showNodeFilter?: any): void;
        _isConnectedAsInput(node: any, variable: any): any;
        _isConnected(node: any, variable: any): any;
        _getConnectionsToSlot(toNode: any, toSlot: any): any;
        _getConnectionsOnNode(node: any): any;
        _createConnection(fromNode: any, fromSlot: any, toNode: any, toSlot: any): FlowConnection;
        _getCurrentSelection(selectChildren: any): any[];
        _canGroup(objectsToGroup: any): any;
        _showRenameGroup(flowGroup: any): Promise<void>;
        _getGroupDescendant(group: any): any[];
        _getIdToObjectMap(objectList: any): Map<{}, {}>;
        _handleFlowNodeDefinitionChanged(): Promise<boolean>;
        _handleScriptFlowNodeDefinitionChanged(): Promise<boolean>;
        _handleFlowEditorGraphsChanged(flowGraphPaths: any): void;
        _handleFlowNodeDefinitionRemoved(): void;
        _handleScriptFlowNodeDefinitionRemoved(): void;
        _handleFlowEditorGraphsRemoved(flowGraphPaths: any): void;
        private _processValidationError(results);
    }
}
declare module "flow/flow-utils" {
    import { IDataDrivenCustomTypeDefinition, IDataDrivenEnumDefinition, IDataDrivenFlowNodeDefinitionInternal, IDataDrivenGlobalsDefinition, IDataDrivenInputDefinition, IDataDrivenOutputDefinition, IDataDrivenUIBrowseSpecDefinition } from "flow/flow-data-driven-node-validation";
    import { IFlowContext, IFlowGraphModel } from "flow/flow-graph";
    import { FlowNode, IFlowNodeModel } from "flow/flow-node";
    import { IDataDrivenFlowNodeModel } from "flow/nodes/data-driven-flow-node";
    export const CLASS_PREFIX = "Stingray.Foundation.Flow";
    export const FLOW_NODE_DEFINITION_FILE_EXTENSION = ".flow_node_definitions";
    export const SCRIPT_FLOW_NODE_DEFINITION_FILES_EXTENSION = ".script_flow_nodes";
    export const FLOW_EDITOR_GRAPH_FILE_EXTENSION = ".flow_editor";
    export const FLOW_NODE_RESOURCE_KEY = "flow_nodes_resource";
    export class FlowError extends Error {
        constructor(name: string, message: string);
    }
    export const enum FLOW_TYPES {
        UNIT = 0,
        LEVEL = 1,
        SUBFLOW = 2,
    }
    export const VALID_FLOW_UI_SCOPES: Set<string>;
    export const URL_ACTIONS: {
        FOCUS: string;
    };
    export function completeClassName(className: string): string;
    export function shortClassName(className: string): string;
    export function getVariableDefinition(definitionList: any[], variableName: string): any;
    export function fixLegacyFlowNodes(graph: IFlowGraphModel, nodeDefinitions: IDataDrivenFlowNodeDefinitionInternal[]): void;
    export function fixSpawnEntityFlowNodes(graph: IFlowGraphModel, nodesDefinition: IDataDrivenFlowNodeDefinitionInternal[]): void;
    export function fixConnections(graph: IFlowGraphModel): void;
    export function convertOldClassToStingray(graph: IFlowGraphModel): void;
    export function replaceMigratedNodes(graph: IFlowGraphModel, nodeDefinitions: IDataDrivenFlowNodeDefinitionInternal[]): void;
    export function replaceInvalidNodes(graph: IFlowGraphModel): void;
    export function performFlowNodeRenames(graph: IFlowGraphModel): void;
    export function performFlowVariableRenames(graph: IFlowGraphModel): void;
    export function performFlowTitleRenames(graph: IFlowGraphModel): void;
    export function performFlowVariableRename(graph: IFlowGraphModel, nodeName: string, originalvariableName: string, newVariableName: string): void;
    export function replaceStringForElementRecursively(object: any, key: string, find: string | RegExp, replace: string): void;
    export function replaceKeyValuePairSiblingKeyForElementRecursively(obj: any, key: string, value: string, siblingKey: string, newSiblingKey: string): void;
    export function getKeyValuePairSiblingValues(obj: any, key: string, value: string, siblingKey: string, siblingValues: string[]): void;
    export function replaceKeyValuePairSiblingValueForElementRecursively(obj: any, key: string, value: string, siblingKey: string, siblingValue: string, newSiblingValue: string): void;
    export type ReplaceElementPredicate = (element: string) => boolean;
    export function replaceElementOnPredicateRecursively(obj: any, key: string, predicate: ReplaceElementPredicate, newValue: string): void;
    export type IsLegacyPredicate = (element: string, legacyNames: Map<string, any>) => boolean;
    export function migrateLegacyNodeClassRecursively(obj: any, key: string, predicate: IsLegacyPredicate, legacyNames: Map<string, any>): any[];
    export function migrateLegacyClassType(node: IDataDrivenFlowNodeModel, legacyNames: Map<string, IDataDrivenFlowNodeDefinitionInternal>): void;
    export type InputOrOutputType = "input" | "output";
    export function convertSlots(node: IFlowNodeModel, slotDefinitions: any[], slotsListName: string, slotClass: string, type: InputOrOutputType): void;
    export function getNodeColor(node: FlowNode): any;
    export function getNodeCategoryColor(categoryName: string): any;
    export function getConnectorColor(connectorType: string): any;
    export function getColorFromHashCode(hashCode: number): string;
    export function variableClassToType(className: string): any;
    export function getInputClassNameFromType(type: string): string;
    export function getOutputClassNameFromType(type: string): string;
    export function runtimeTypeToConnectionType(type: string): any;
    export function connectionTypeToRuntimeType(type: string): any;
    export function getCustomTypeDefinition(variableDefinition: IDataDrivenInputDefinition | IDataDrivenOutputDefinition, globalDefinition: IDataDrivenGlobalsDefinition): IDataDrivenCustomTypeDefinition;
    export function getCustomTypeName(variableDefinition: IDataDrivenInputDefinition | IDataDrivenOutputDefinition, globalDefinition: IDataDrivenGlobalsDefinition): string;
    export function getBrowsableSpec(elementDefinition: IDataDrivenInputDefinition, globals: IDataDrivenGlobalsDefinition): IDataDrivenUIBrowseSpecDefinition;
    export function getEnumSpec(elementDefinition: IDataDrivenInputDefinition, globals: IDataDrivenGlobalsDefinition): IDataDrivenEnumDefinition[];
    export function getBrowsableUITypesTitle(elementDefinition: IDataDrivenInputDefinition, globals: IDataDrivenGlobalsDefinition): string;
    export function areTypesConnectable(fromType: string, toType: string): boolean;
    export function getUIName(elementDefinition: IDataDrivenInputDefinition | IDataDrivenOutputDefinition): string;
    export function isValidInputType(type: string): any;
    export function isValidOutputType(type: string): any;
    export function createFocusLink(objectIds: string[], text: string, flowContext: IFlowContext): string;
}
declare module "flow/flow-data-driven-node-validation" {
    export interface IDataDrivenGlobalsDefinition {
        enums?: IDataDrivenGlobalEnumDefinition;
        ui_browse_specs?: IDataDrivenGlobalUIBrowseSpecDefinition;
        custom_types?: IDataDrivenGlobalCustomTypeDefinition;
    }
    export interface IDataDrivenFlowNodeDocumentFormat extends IDataDrivenGlobalsDefinition {
        nodes: IDataDrivenFlowNodeDefinition[];
    }
    export interface IDataDrivenGlobalEnumDefinition {
        [key: string]: IDataDrivenEnumDefinition[];
    }
    export interface IDataDrivenEnumDefinition {
        name: string;
        value?: number;
    }
    export interface IDataDrivenGlobalUIBrowseSpecDefinition {
        [key: string]: IDataDrivenUIBrowseSpecDefinition;
    }
    export interface IDataDrivenUIBrowseSpecDefinition {
        ui_browse_function?: string;
        ui_browse_title?: string;
        ui_browse_resource_input?: string;
        ui_types?: string[];
        [key: string]: any;
    }
    export interface IDataDrivenGlobalCustomTypeDefinition {
        [key: string]: IDataDrivenCustomTypeDefinition;
    }
    export interface IDataDrivenCustomTypeDefinition {
        type: string;
        ui_name: string;
        size: number;
        align?: number;
    }
    export interface IDataDrivenFlowNodeDefinition {
        name: string;
        ui_legacy_class?: string;
        ui_custom_backend_implementation?: boolean;
        ui_name: string;
        ui_category: string;
        ui_brief: string;
        ui_color_category?: string;
        type: "simple" | "standard";
        ui_scopes?: {
            UnitFlowEditor?: boolean;
            LevelFlowEditor?: boolean;
        };
        ui_spawnable?: boolean;
        inputs: IDataDrivenInputDefinition[];
        outputs: IDataDrivenOutputDefinition[];
    }
    export type DataDrivenInputType = "event" | "unit" | "actor" | "mover" | "vector3" | "float" | "bool" | "string" | "id" | "quaternion" | "camera" | "light" | "mesh" | "material" | "resource" | "enum" | "generic" | "compiletime_string";
    export interface IDataDrivenInputDefinition {
        type: DataDrivenInputType;
        resource_type?: string;
        ui_browse_spec?: string | IDataDrivenUIBrowseSpecDefinition;
        is_required?: boolean;
        custom_type?: string | IDataDrivenCustomTypeDefinition;
        enum?: string | IDataDrivenEnumDefinition[];
        ui_name: string;
        ui_hidden?: boolean;
        name: string;
        external?: boolean;
        ui_initial_value?: any;
    }
    export type DataDrivenOutputType = "event" | "unit" | "actor" | "mover" | "vector3" | "float" | "bool" | "string" | "id" | "quaternion" | "camera" | "light" | "mesh" | "material" | "event_array" | "custom";
    export interface IDataDrivenOutputDefinition {
        type: DataDrivenOutputType;
        ui_name: string;
        name: string;
        data_update?: "push" | "query";
        external?: boolean;
        default_value?: any;
        custom_type?: string | IDataDrivenCustomTypeDefinition;
        data_node?: string;
    }
    export interface IDataDrivenFlowNodeDefinitionInternal extends IDataDrivenFlowNodeDefinition {
        globals: IDataDrivenGlobalsDefinition;
    }
    export function illegalPropertyForBuiltInImplementation(name: string, property: string): string;
    export function missingPropertyDeclaration(name: string, optionalSubContext: string, property: string): string;
    export function invalidPropertyDeclaration(name: string, optionalSubContext: string, property: string | number, requiredType: string): string;
    export function illegalPropertyDeclaration(name: string, optionalSubContext: string, property: string): string;
    export function invalidTypeDeclaration(name: string, optionalSubContext: string, property: string | number, invalidType: string): string;
    export function getIssuesWithFlowNodeDeclaration(node: IDataDrivenFlowNodeDefinition): string[];
    export function validateFlowNodeReplacement(nodes: IDataDrivenFlowNodeDefinition[], issuesByPath: {}): IDataDrivenFlowNodeDefinition[];
}
declare module "flow/flow-definitions" {
    import { IDataDrivenFlowNodeDefinitionInternal } from "flow/flow-data-driven-node-validation";
    import { IScriptFlowNodeDefinition } from "flow/flow-script-node-validation";
    export interface ResourceAndPath {
        resource: string;
        path: string;
    }
    export function getFlowFilePaths(sourceDirectory: string, extension: string): Promise<ResourceAndPath[]>;
    export function loadFlowNodeDefinitionFiles(resourcesAndPaths: ResourceAndPath[]): IDataDrivenFlowNodeDefinitionInternal[];
    export function loadScriptFlowNodeDefinitionFiles(resourcesAndPaths: ResourceAndPath[], oldScriptNodes: IScriptFlowNodeDefinition[]): IScriptFlowNodeDefinition[];
    export function loadAndValidateFlowNodeDefinition(resources: string[], filePaths: string[]): IDataDrivenFlowNodeDefinitionInternal[];
    export function loadFlowNodeDefinitionFile(resource: string, filePath: string): IDataDrivenFlowNodeDefinitionInternal[];
    export function loadAndValidateScriptFlowNodes(resources: string[], filePaths: string[], oldScriptNodes: IScriptFlowNodeDefinition[]): IScriptFlowNodeDefinition[];
    export function loadScriptFlowNodeDefinitionFile(resource: string, filePath: string): IScriptFlowNodeDefinition[];
}
declare module "services/flow-service" {
    import { IDataDrivenFlowNodeDefinitionInternal } from "flow/flow-data-driven-node-validation";
    import { IScriptFlowNodeDefinition } from "flow/flow-script-node-validation";
    export let scriptFlowNodes: IScriptFlowNodeDefinition[];
    export let flowNodeDefinitions: IDataDrivenFlowNodeDefinitionInternal[];
    export function loadAllFlowNodeDefinitionFiles(): Promise<void>;
    export function loadFlowNodeDefinitionFiles(paths: string[]): Promise<void>;
    export function loadAllScriptFlowNodeDefinitionFiles(): Promise<void>;
    export function loadScriptFlowNodeDefinitionFiles(paths: string[]): Promise<void>;
    export function on(name: string, condition?: (...args: any[]) => boolean, callback?: (...args: any[]) => void): any;
    export function ready(): Promise<any>;
}
declare module "services/log-service" {
    export function error(...args: any[]): Promise<any>;
    export function getLogFilePath(): Promise<any>;
    export function getMessages(): Promise<any>;
    export function log(...args: any[]): Promise<any>;
    export function warn(...args: any[]): Promise<any>;
    export function clearLog(): Promise<any>;
    export function on(event: any, handler: any): OffHandler;
    export function off(event: any, handler: any): Promise<any>;
}
declare module "services/object-creator-service" {
    export function clearSelection(): Promise<void>;
    export function selectItem(item: string): Promise<any>;
    export function getAllItems(): Promise<any>;
    export function on(event: any, handler: any): OffHandler;
    export function off(event: any, handler: any): Promise<any>;
}
declare module "services/preview-service" {
    export const FocusedViewportId: string;
    export function focusViewport(viewportName: any): Promise<any>;
    export function update(): Promise<any>;
    export function bindAssetToViewport(viewportName: any, assetPath: any): Promise<any>;
    export function unbindViewport(viewportName: any): Promise<any>;
    export function on(...args: any[]): any;
    export function off(...args: any[]): any;
}
declare module "services/terrain-editing-service" {
    import { RemoteObject } from "services/remote-service";
    export const MIN_HEIGHTMAP_RESOLUTION = 0;
    export const MAX_HEIGHTMAP_RESOLUTION = 4096;
    export interface TerrainUndergrowthModel extends RemoteObject {
        UnitResourceName: string;
        Density: number;
        MeshName: string;
    }
    export interface TerrainLayerModel extends RemoteObject {
    }
    export interface TerrainModel extends RemoteObject {
    }
    export interface TerrainResource extends RemoteObject {
    }
    export interface TerrainMaterial extends RemoteObject {
    }
    export enum BrushModeEnum {
        Pencil = 0,
        Smooth = 1,
        Flatten = 2,
        None = 3,
    }
    export const BrushMode: string;
    export function setBrushMode(brushMode: string): any;
    export const SelectedMaterialChannel: number;
    export function setSelectedMaterialChannel(channel: number): any;
    export const SelectedUndergrowthUnit: TerrainUndergrowthModel;
    export function setSelectedUndergrowthUnit(unit: TerrainUndergrowthModel): any;
    export const UndergrowthVisible: boolean;
    export function setUndergrowthVisible(visible: boolean): any;
    export const BrushStrength: number;
    export function setBrushStrength(v: number): any;
    export const BrushRadius: number;
    export function setBrushRadius(v: number): any;
    export const BrushFalloff: number;
    export function setBrushFalloff(v: number): any;
    export function createNewTerrain(position: any, radius: any, resolution: any, defaultTerrainName?: string): Promise<any>;
    export function getUnitMeshNames(unitType: string): Promise<string[]>;
    export function performAddUndergrowthUnit(terrainId: string, materialMapLayer: TerrainLayerModel, materialChannel: number, unit_type: string): Promise<any>;
    export function performRemoveUndergrowthUnit(terrainId: string, materialMapLayer: TerrainLayerModel, materialChannel: number, undergrowthModel: TerrainUndergrowthModel): Promise<any>;
    export function performSetSelectedBrush(brushMode: any): Promise<any>;
    export function performSetSelectedMaterialChannel(terrainId: string, materialChannel: number): Promise<any>;
    export function performSetSelectedUndergrowthUnit(terrain_id: string, undergrowth_model: TerrainUndergrowthModel): Promise<any>;
    export function performSetUndergrowthUnitDensity(terrain_id: string, undergrowth_model: TerrainUndergrowthModel, old_density: number, new_density: number): Promise<any>;
    export function performSetUndergrowthUnitMesh(terrain_id: string, undergrowth_model: TerrainUndergrowthModel, mesh_name: string): Promise<any>;
    export function performImportCommand(terrainId: string, layer: string, sourceImageFilePath: string, flipY: boolean): Promise<any>;
    export function performExport(terrainId: string, layer: string, exportImageFilePath: string): Promise<any>;
    export function getTerrainModel(terrainId: string): Promise<any>;
    export function getTerrainResource(terrainId: string): Promise<any>;
    export function getTerrainMaterial(terrainId: string): Promise<any>;
    export function setSelectedTerrain(terrainId: string): Promise<any>;
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
            post(): Promise<{}>;
        }
        function generateThumbnail(resourcePath: any): Promise<Thumbnail>;
    }
    export = ThumbnailService;
}
declare module "node-editor/node-editor-adapter-factory" {
    import "3rdparty/node-editor/node-editor";
    export function createGraph(nodeEditorViewModel: any): any;
    export function createNode(node: any): any;
    export function createConnection(connection: any): any;
    export function createGroup(group: any): any;
    export function setStyling(styling: any): void;
    export function ready(): any;
}
declare module "components/mithril-ext" {
    import m = require("mithril");
    import "jquery-resize";
    export = m;
}
declare module "components/button" {
    export type onClickEvent = (event: any) => void;
    export interface ButtonDesc {
        onclick: onClickEvent;
        text?: string;
        type?: string;
        icon?: string;
        faIcon?: string;
        class?: string;
        disabled?: boolean;
        flex?: string;
        title?: string;
        onmouseleave?: (event: any) => void;
        id?: string;
        color?: string;
        style?: any;
        children?: any;
    }
    export { ButtonDesc as Desc };
    export function component(opts: ButtonDesc): any;
}
declare module "components/dom-tools" {
    export function focus(element: any): void;
    export function selectAllText(element: any): void;
    export function loadCss(url: any): HTMLLinkElement;
    export function requireCss(urls: any): Promise<{}[]>;
}
declare module "components/event-helpers" {
}
declare module "components/textbox" {
    import "common/jquery-ext";
    import "components/event-helpers";
    interface TextboxDesc {
        numberModel?: NumberModel;
        model?: WidgetModel;
        title?: string;
        disabled?: boolean;
        readOnly?: boolean;
        placeholder?: string;
        inputType?: string;
        min?: number;
        max?: number;
        increment?: number;
        step?: number;
        textHighlight?: () => boolean;
        backgroundHighlight?: () => boolean;
        onCommitValue?: (newValue, oldValue) => void;
        onclick?: (event) => void;
        onfocus?: (event) => void;
        onblur?: (event) => void;
        triggerCharacters?: any;
        rejectedCharacters?: any;
        liveUpdate?: boolean;
        focusMe?: boolean;
        config?: Function;
        dropConfig?: any;
        rightToLeftOverflow?: boolean;
        clearable?: boolean;
        invalid?: boolean;
        lineRows?: string;
        multiLines?: boolean;
        class?: string;
        onmousedown?: (event) => void;
        onmousemove?: (event) => void;
        onmouseup?: (event) => void;
        selectOnClick?: boolean;
        clearableClass?: string;
        onClear?: () => void;
    }
    export { TextboxDesc as Desc };
    export function component(opts: TextboxDesc): any;
}
declare module "components/arrow-navigation" {
}
declare module "components/typeahead" {
    import "components/arrow-navigation";
    interface TypeAheadDesc {
        model: MithrilModel;
        choices: any;
        caseSensitive?: boolean;
        getLabel?: (choice) => string;
        getTitle?: (choice) => string;
        rows?: number;
    }
    export { TypeAheadDesc as Desc };
    export function component(opts: TypeAheadDesc): any;
}
declare module "node-editor/node-editor-view" {
    import "3rdparty/node-editor/node-editor";
    import { INodeAutoCompleteData, NodeEditorGraph } from "node-editor/node-editor-graph";
    export type VoidCallback = () => void;
    export type NodeEditorCallback = (args: any) => any;
    export type GraphCallback = (args: any) => any;
    export interface INodeEditorViewConfig {
        viewSettings?: any;
        nodeAutoCompleteEnabled?: boolean;
    }
    export class NodeEditorView {
        nodeAutoCompleteEnabled: boolean;
        userViewSettings: any;
        config: INodeEditorViewConfig;
        element: HTMLElement;
        nodeEditor: NodeEditor;
        graph: NodeEditorGraph;
        shiftPressed: boolean;
        _click: VoidCallback;
        _mouseWheel: (e: WheelEvent) => any;
        _mouseDown: (e: MouseEvent) => any;
        _keyDown: (e: KeyboardEvent) => any;
        _keyUp: (e: KeyboardEvent) => any;
        _resize: VoidCallback;
        _rightClick: NodeEditorCallback;
        _nodesMoved: NodeEditorCallback;
        _validateConnection: NodeEditorCallback;
        _connectorClicked: NodeEditorCallback;
        _lineDoubleClicked: NodeEditorCallback;
        _selectionChanged: NodeEditorCallback;
        _groupChildrenAdded: NodeEditorCallback;
        _groupExpanded: NodeEditorCallback;
        _groupCollapsed: NodeEditorCallback;
        _elementButtonClicked: NodeEditorCallback;
        _elementButtonDoubleClicked: NodeEditorCallback;
        _groupDoubleClicked: NodeEditorCallback;
        _nodeDoubleClicked: NodeEditorCallback;
        _validateStateMachineConnection: NodeEditorCallback;
        _nodeResized: NodeEditorCallback;
        _connectionDragCreate: NodeEditorCallback;
        _nodesDragEndOnNode: NodeEditorCallback;
        _deny: VoidCallback;
        _retain: VoidCallback;
        _backgroundDoubleClicked: NodeEditorCallback;
        _tagDoubleClicked: NodeEditorCallback;
        _canConnect: (connectorA: PixiConnectorShape, connectorB: PixiConnectorShape) => boolean;
        _nodesAdded: GraphCallback;
        _nodesRemoved: GraphCallback;
        _connectionsAdded: GraphCallback;
        _connectionsRemoved: GraphCallback;
        _groupsAdded: GraphCallback;
        _groupsRemoved: GraphCallback;
        _reconnectConnection: GraphCallback;
        _nodeChanged: GraphCallback;
        _connectionChanged: GraphCallback;
        _groupChanged: GraphCallback;
        _groupNodesAdded: GraphCallback;
        _groupNodesRemoved: GraphCallback;
        _groupGroupsAdded: GraphCallback;
        _groupGroupsRemoved: GraphCallback;
        _newSelection: GraphCallback;
        _contextMenuHide: GraphCallback;
        _contextMenuClicked: GraphCallback;
        _frameAll: VoidCallback;
        _frameSelected: GraphCallback;
        _graphRebuild: GraphCallback;
        constructor(config: INodeEditorViewConfig);
        destroy(): void;
        createEditorView(elem: HTMLElement): void;
        setGraph(graph: NodeEditorGraph, frameAll: boolean): any;
        resize(): void;
        getNodeAutoCompleteData(): INodeAutoCompleteData[];
        bindElementEvents(): void;
        unbindElementEvents(): void;
        registerEditorEvents(): void;
        unregisterEditorEvents(): void;
        registerGraphEvents(): void;
        unregisterGraphEvents(): void;
        nodeAutoCompleteSelected(id: any, x: any, y: any): void;
        _emitGraphEvent(eventName: any, eventParams?: any, afterEventCb?: any): void;
    }
}
declare module "node-editor/node-editor-component" {
    import { NodeEditorGraph } from "node-editor/node-editor-graph";
    import { INodeEditorViewConfig } from "node-editor/node-editor-view";
    export interface INodeEditorComponentConfig extends INodeEditorViewConfig {
        resize?: () => void;
        setGraph?: (graph: NodeEditorGraph, frameAll: boolean) => Promise<void>;
        setComponent?: (component: any) => void;
        nodeEditorComponent: NodeEditor;
    }
    export class Search {
        nodeEditorView: any;
        isCaseSensitive: boolean;
        ignoreInputsOutputs: boolean;
        ignoreGroups: boolean;
        showConfig: boolean;
        results: any;
        resultIds: any[];
        current: any;
        previous: any;
        query: string;
        bbox: any[];
        resultsCount: number;
        currentIndex: number;
        elementIndex: number;
        currentBox: number;
        constructor(opts: any);
        _compare(text: any): any[];
        _createMatchBoundingBox(start: any, end: any, text: any, fullText: any, container: any): any;
        _indexStartOnTruncatedText(start: any, end: any, text: any, value: any, container: any): any;
        _indexStartOnTruncatedValue(start: any, end: any, text: any, value: any, container: any): any;
        _indexStartOnTheTextWithNoValue(start: any, end: any, text: any, container: any): any;
        _onlyValueTruncated(start: any, end: any, text: any, value: any, container: any): any;
        _resetBbox(): void;
        keypress(event: any): void;
        getCurrentNode(): any;
        highlightTitle(container: any, data: any, title: any): void;
        search(): void;
        searchModel(val: any): any;
        selectNode(): void;
        selectNext(): void;
        selectPrevious(): void;
        toggleCaseSensitive(): void;
        toggleIgnoreGroup(): void;
        toggleIgnoreInputsOutputs(): void;
        toggleFlyoutMenu(): void;
        unselectPrevious(): void;
        view(): any;
    }
    export class NodeEditor {
        config: any;
        nodeEditorView: any;
        showTypeahead: boolean;
        search: Search;
        cursorPosition: any;
        nodePosition: any;
        typeAheadArgs: any;
        cleanup: () => void;
        bindNodeEditorView: (HTMLElement) => void;
        onKeyDown: (KeyboardEvent) => any;
        containerConfig: (elem: HTMLElement, isInit: boolean, context: any) => void;
        constructor(config: INodeEditorComponentConfig);
        redrawSelf(): void;
        toggleTypeAhead(show: boolean): void;
        view(): any;
    }
    export class NodeEditorApp {
        static controller(options: INodeEditorComponentConfig): NodeEditor;
        static view(ctrl: NodeEditor): any;
        static component(opts: INodeEditorViewConfig): any;
        static config(opts: INodeEditorViewConfig): INodeEditorComponentConfig;
    }
}
declare module "node-editor/node-editor-directive-controller" {
}
declare module "node-editor/node-editor-directive" {
    import "3rdparty/node-editor/node-editor";
    import "node-editor/node-editor-directive-controller";
}
declare module "node-editor/node-editor-search-helper" {
    class NodeEditorSearchHelper {
        _defaultColor: string;
        _defaultThickness: number;
        _currentBoundingBoxSelected: any;
        _previousNodeSelected: any;
        _nodes: PixiNodeShape[];
        _matchFoundInNode: any[];
        _selectedNodeIndex: number;
        _matchTotal: number;
        _localMatchIndex: number;
        _globalMatchIndex: number;
        _foundNodeInViewport: boolean;
        offHandlers: Function[];
        currentIndex: number;
        elementIndex: number;
        search: string;
        matchInfo: string;
        wantCaseSensitive: boolean;
        searchNodeTitleOnly: boolean;
        baseFilters: any[];
        results: any[];
        nodeGraph: any;
        nodeEditor: NodeEditor;
        constructor(editor: any);
        _handleEditorEvents(): void;
        _handleNodeChanged(): void;
        _indexStartOnTruncatedText(startAtIndex: any, endAtIndex: any, textGraphics: any, valueGraphics: any, container: any): BorderedRectangle;
        _indexStartOnTruncatedValue(startAtIndex: any, endAtIndex: any, textGraphics: any, valueGraphics: any, container: any): BorderedRectangle;
        _indexStartOnTheTextWithNoValue(startAtIndex: any, endAtIndex: any, textGraphics: any, container: any): BorderedRectangle;
        _onlyValueTruncated(startAtIndex: any, endAtIndex: any, textGraphics: any, valueGraphics: any, container: any): BorderedRectangle;
        _computeHighlightRegion(node: any, regex: any, strLength: any): any[];
        _manageHighlightedRegions(node: any, bboxArray: any, nodeId?: any): void;
        _resetValues(nodeId?: any): void;
        _setBackOriginalResizeEvent(nodeId: any): void;
        _removeBBox(bboxArray: any): void;
        _updateMatchCount(): void;
        _selectCurrentNode(doNotFrameSelection?: any): void;
        _createMatchBoundingBox(startAtIndex: any, endAtIndex: any, textGraphics: any, fullText: any, container: any): BorderedRectangle;
        _updateMatchBoundingBox(): void;
        _isNodeStillExist(nodeId: any): boolean;
        setGraph(graph: any): void;
        queryInfo(nodeId?: any, doNotFrameSelection?: any): void;
        isNodeInMatchList(nodeId: any): boolean;
        getMatchIndexes(string: any, regex: any): any[];
        keypress(event: any): void;
        selectPreviousMatch(): void;
        selectNextMatch(): void;
    }
    export = NodeEditorSearchHelper;
}
declare module "node-editor/node-editor-utils" {
    export function showHelp(type: string, name: string, category: string): void;
}
declare module "components/accordion" {
    interface AccordionDesc {
        title: string;
        isExpanded: boolean;
        isEnabled?: boolean | Function;
        collapsible?: boolean;
        content?: object;
        checkbox?: any;
    }
    export { AccordionDesc as Desc };
    export function component(opts: AccordionDesc[] | AccordionDesc): any;
}
declare module "components/busy" {
    export function show(): void;
    export function hide(): void;
    export function view(): any;
}
declare module "components/checkbox" {
    interface CheckboxDesc {
        model: MithrilModel;
        id?: string;
        disabled?: boolean;
        title?: string;
        trueValue?: any;
    }
    export { CheckboxDesc as Desc };
    export function component(opts: CheckboxDesc): any;
}
declare module "components/choice" {
    interface ChoiceDesc {
        model: WidgetModel;
        getOptions(): any;
        id?: string;
        disabled?: boolean;
        required?: boolean;
        multiple?: boolean;
        defaultValue?: string;
        defaultValueName?: string;
        size?: number;
        emptyMessage?: string;
        useDictValueForLabel?: boolean;
        invalid?: boolean;
        name?: string;
    }
    export { ChoiceDesc as Desc };
    export class Choice {
        static view(ctrl: any, args: ChoiceDesc): any;
    }
    export function component(opts: ChoiceDesc): any;
}
declare module "components/color" {
    interface ColorDesc {
        model: WidgetModel;
        isHdr: boolean;
        customStyle?: string;
        size?: WidgetSize;
        disabled?: boolean;
    }
    export { ColorDesc as Desc };
    export function component(opts: ColorDesc): any;
}
declare module "components/color-gradient" {
    interface ColorGradientDesc {
        collectionModel: any;
        disabled?: boolean;
    }
    export { ColorGradientDesc as Desc };
    export function createGradientElement(colorModel: WidgetModel, posModel: WidgetModel, stopId?: string | number, isReadOnly?: boolean): {
        remoteId: string | number;
        Color: {
            disabled: boolean;
            model: WidgetModel;
        };
        X: {
            disabled: boolean;
            model: WidgetModel;
        };
    };
    export function component(opts: ColorGradientDesc): any;
}
declare module "components/color-temperature-slider" {
    interface TempSliderDesc {
        model?: WidgetModel;
        numberModel?: NumberModel;
        min?: number;
        max?: number;
        step?: number;
        disabled?: boolean;
        placeholder?: string;
        showLabel?: boolean;
        label?: string;
    }
    export { TempSliderDesc as Desc };
    export function component(opts: TempSliderDesc): any;
}
declare module "components/component-harness" {
}
declare module "components/engine-viewport" {
    export function component(opts: any): any;
    export function config(opts: any): any;
}
declare module "components/filter-view" {
    import * as Accordion from "components/accordion";
    export interface FilterDesc {
        label: string;
        id: string;
        value: boolean;
        model: MithrilModel;
    }
    interface FilterViewDesc {
        title: string;
        onValueChanged: (labels: any, ids: any, enabled: any, filters: any) => void;
        filters: FilterDesc[];
    }
    export { FilterViewDesc as Desc };
    export class FilterController {
        headerCheckBox: MithrilModel;
        allEnabled: boolean;
        ids: Array<string | number>;
        labels: string[];
        filters: FilterDesc[];
        filterHandlers: FilterSetter[];
        accordionConfig: Accordion.Desc;
        onValueChanged: (labels: any, ids: any, enabled: any, filters: any) => void;
        constructor(options: FilterViewDesc);
        view(): any;
        enableAll(isEnabled: any): void;
        checkFiltersConsensus(): any;
    }
    export class FilterView {
        static controller(args: FilterViewDesc): FilterController;
        static view(ctrl: FilterController): any;
    }
    export { FilterView as Component };
    export function component(opts: FilterViewDesc): any;
}
declare module "components/graph" {
    interface GraphDirectionDesc {
        num: number;
        delta: number;
    }
    export { GraphDirectionDesc as DirectionDesc };
    interface GraphDesc {
        graphModel: any;
    }
    export { GraphDesc as Desc };
    export function component(opts: GraphDesc): any;
}
declare module "components/toolbar" {
    interface ToolbarItem {
        img: string;
        title: string;
        separator?: boolean;
        empty_space?: boolean;
        class?: string;
        component?: any;
        enabled?: () => boolean;
        action?: () => void;
    }
    export { ToolbarItem as Item };
    interface ToolbarDesc {
        items: ToolbarItem[];
    }
    export { ToolbarDesc as Desc };
    export function component(opts: ToolbarDesc): any;
}
declare module "components/journal-view" {
    import * as dataService from "services/data-service";
    interface JournalDesc {
        journal: dataService.Journal;
        showToolbar?: boolean;
    }
    export { JournalDesc as Desc };
    export function component(opts: JournalDesc): any;
}
declare module "components/spinner" {
    interface SpinnerDesc {
        numberModel?: NumberModel;
        model?: WidgetModel;
        defaultValue?: number;
        min?: number;
        max?: number;
        decimal?: number;
        increment?: number;
        disabled?: boolean;
        showLabel?: boolean;
        label?: string;
        placeholder?: string;
        readOnly?: boolean;
        invalid?: boolean;
        onCommitValue?: any;
        onmousedown?: any;
        onmouseup?: any;
        onmousemove?: any;
        backgroundHighlight?: any;
        textHighlight?: any;
        selectOnClick?: any;
    }
    export { SpinnerDesc as Desc };
    export function component(opts: SpinnerDesc): any;
}
declare module "components/json-component" {
    import "components/event-helpers";
    interface JsonComponentDesc {
        jsonModel?: IJsonModel;
        jsonObj?: any;
        defaultCollapsed?: boolean;
        nbDecimals?: number;
        supportsKeyEditing?: boolean;
    }
    export { JsonComponentDesc as Desc };
    export function component(opts: JsonComponentDesc): any;
}
declare module "components/loading" {
    class Loading {
        static view(): any;
    }
    export default Loading;
}
declare module "components/model-synchronizer" {
    class ModelSynchronizer {
        modelDescs: any;
        editorContext: any;
        lockGroups: any;
        constructor(editorContext: any);
        addLockGroup(name: any, isGroupLockAccessor: any): void;
        addModel(key: any, model: any, isSelectedAccessor: any, lockGroup: any): any;
        isGroupLocked(lockGroup: any): any;
        _setTransientValue(key: any, newValue: any): void;
        _commitValue(key: any, originalValue: any, newValue: any): void;
        _applyModel(key: any, newValue: any): any;
        _getModelsToSynced(modelDescs: any, srcDesc: any): any[];
        _getLockGroupModels(modelDescs: any, lockGroup: any): any;
    }
    export default ModelSynchronizer;
}
declare module "properties/mithril-property-ext" {
    import m = require("components/mithril-ext");
    export = m;
}
declare module "components/path" {
    interface PathDesc {
        model: WidgetModel;
        browseType: string;
        browseTitle: string;
        browseFilter: string;
        isReadOnly: boolean;
        hasResourceSelect?: boolean;
        isRightToLeft?: boolean;
        suffixLabel?: string;
        placeholder: MithrilModel | string;
        clearable?: boolean;
    }
    export { PathDesc as Desc };
    export function component(opts: PathDesc): any;
}
declare module "components/resizer" {
    export interface ResizerDesc {
        direction: string;
        flex?: string[];
        lineclass?: string;
        lineshadow?: boolean;
        collapsible?: boolean;
        onUpdate?: (args: any) => void;
        redrawOnResize?: boolean;
    }
}
declare module "components/resource" {
    interface ResourceDesc {
        model: WidgetModel;
        resourceTypes: string[];
        string: any;
        defaultValue: string;
        placeholder: string | MithrilModel;
        resourceType: string | string[];
        hasResourceSelect: boolean;
        hasElementSelect: boolean;
        suffixLabel?: string;
        isReadOnly?: boolean;
        isInvalid?: boolean;
        isClearableEnabled?: boolean;
        showCustomContentBrowser?: any;
        disallowedResourceNames?: string[];
        title: string;
    }
    export { ResourceDesc as Desc };
    export function component(opts: ResourceDesc): any;
}
declare module "components/slider" {
    interface SliderDesc {
        numberModel?: NumberModel;
        model?: WidgetModel;
        min?: number;
        max?: number;
        decimal?: number;
        step?: number;
        disabled?: boolean;
        showLabel?: boolean;
        label?: string;
        placeholder?: string;
    }
    export { SliderDesc as Desc };
    export function component(opts: SliderDesc): any;
}
declare module "directives/arrow-navigation" {
}
declare module "directives/clearable" {
}
declare module "components/tree-view" {
    import "common/context-menu-utils";
    import "components/arrow-navigation";
    import "directives/arrow-navigation";
    import "directives/clearable";
    import "directives/context-menu";
    export class TreeViewController {
        opts: any;
        containerLoaded: boolean;
        disableAutoExpandSelected: boolean;
        disableMultiSelect: boolean;
        disableRightClickSelect: boolean;
        disableSelectedNodes: boolean;
        displayAsTree: boolean;
        hideFilterButton: boolean;
        hideSearchBox: boolean;
        hideRoot: boolean;
        mustRebuild: boolean;
        arrowNavigationConfig: any;
        arrowNavigation: any;
        externalFilterFunc: any;
        lastSelectedNode: any;
        onTreeViewReady: any;
        onDomReady: any;
        search: any;
        showTreeToggleButton: any;
        treeViewModel: any;
        useCheckboxNode: any;
        virtualScroll: any;
        containerIdentifier: string;
        lastSelectedIndex: number;
        displayList: any[];
        filteredListIds: number[];
        flatLookup: any[];
        sortedList: any[];
        visibleTree: any[];
        selectedIds: number[];
        selectedAncestorIds: number[];
        dragConfig: any;
        dropConfig: any;
        IsDraggable: any;
        GetDragType: any;
        GetDragData: any;
        CanDropOnNode: any;
        DropOnNode: any;
        GetSupportedDropTypes: any;
        private container;
        private connectorHash;
        private depthList;
        private domContainer;
        private expanderConnectorHash;
        private lastVisibleChild;
        private originalTreeViewModel;
        private frameSelectionRequest;
        private rangeSelectPivotNodeId;
        private treeViewId;
        private scrollToName;
        readonly rowHeight: number;
        constructor(opts: any);
        _initTreeViewModel(treeViewModel: any): void;
        _initDragAndDrop(): void;
        _setConnectors(node: any, depth: any, index: any, visibleNodeLookup: any): void;
        _synchronizeModel(treeViewModel: any): void;
        _validateTreeViewModel(treeViewModel: any): void;
        addToSelection(node: any, doNotNotify?: any): void;
        buildNodeLookup(): void;
        buildRenderTree(): void;
        checkboxWalker(ctrl: any, node: any, checked: any): void;
        doubleClick(node: any, e: any): void;
        expandSelectedNodesAncestors(): boolean;
        expandToggle(item: any, event?: any): void;
        expandToggleFunc(item: any, propagate: any, expand: any): void;
        filterNodes(): void;
        filterNode(node: any, filterFunc: any): any;
        findTargetNode(target: any): any;
        findTargetElement(target: any): any;
        frameSelection(): void;
        frameNodes(ids: any): void;
        generateSearchResults(): void;
        getIcon(node: any): any;
        getImgIcon(node: any): any;
        getSecondaryImgIcon(node: any): any;
        getLastSelectedNode(): any;
        getNodeById(nodeId: any): any;
        getNodeDisplay(node: any): any;
        getNodeIsVisible(node: any): any;
        getAdditionalClasses(node: any): string;
        getNodeName(node: any): any;
        getRangeNodes(pivotNode: any, endNode: any): any[];
        getToolTip(node: any): any;
        getVisibleNodeByNodeId(nodeId: any): any;
        hasAction(node: any): any;
        highlightAncestorsOfSelected(): void;
        isBold(node: any): any;
        isDimmed(node: any): any;
        isFilteredVisible(node: any): boolean;
        isLastVisibleSibling(node: any, visibleNodeLookup: any): boolean;
        isNodeInSearch(node: any): boolean;
        isSelected(node: any): boolean;
        isSelectedAncestor(node: any): boolean;
        isVisible(node: any): boolean;
        keyPress(event: any): void;
        mithrilConfig(): void;
        multiSelection(addNodes: any, removeNodes: any): void;
        nodeStyle(node: any): any;
        onScroll(event: any): any;
        onToggleDisplayMode(toggle: any): void;
        propagateExpandToChildrenRecursive(node: any): void;
        removeFromSelection(node: any, doNotNotify?: any): void;
        renameNode(node: any, newName: any): any;
        scrollToNodeId(nodeId: any): void;
        scrollToIndex(nodeIndex: any): void;
        searchForName(nodeId: any, query: any): boolean;
        searchModel(newValue: any): any;
        select(node: any, event: any): void;
        setDomContainer(): void;
        setElementHighlight(target: any, remove: any): void;
        setParentCheckboxState(ctrl: any, node: any): void;
        showItemContextualMenu(node: any, event: any): any;
        showContextualMenu(event: any): any;
        singleSelection(node: any, selectNode?: any): Promise<any>;
        sortFunction(a: any, b: any): 1 | -1;
        sortList(): void;
        _prepareTreeData(): void;
    }
    const TreeViewComponent: {
        controller: (opts: any) => TreeViewController;
        composeItem: (item: any) => any;
        view: (ctrl: any, args: any) => any;
        _genItems: (ctrl: any) => any;
        _getSearchBox: (ctrl: any) => any;
        _getTree: (ctrl: any) => any;
    };
    export { TreeViewComponent as Component };
    export function component(opts: any): any;
}
declare module "directives/checkbox" {
}
declare module "directives/accordion-panel" {
    import "directives/checkbox";
}
declare module "directives/busy-wait" {
}
declare module "directives/core-src" {
}
declare module "directives/draggable" {
    import "jquery";
}
declare module "directives/droppable" {
    import "jquery";
}
declare module "directives/editable-label" {
    import "jquery";
}
declare module "directives/engine-viewport-mouse" {
    export const MouseButton: {
        Left: number;
        Middle: number;
        Right: number;
    };
    export class IdleMouseBehaviour {
        _leftButtonMouseCapture: boolean;
        constructor(engineAndPluginStateSetter: any);
        mouseDown(viewportId: any, x: any, y: any, buttonNumber: any, modifiers: any, engineAndPluginStateSetter: any, engineViewportService: any, simplifiedControls: any, requestFocus: any): this | MayaStyleTurntableRotationMouseBehaviour | RightClickDraggingMouseBehaviour;
        mouseUp(viewportId: any, x: any, y: any, buttonNumber: any, modifiers: any, engineAndPluginStateSetter: any, engineViewportService: any): this;
        mouseMove(viewportId: any, x: any, y: any, dx: any, dy: any, engineAndPluginStateSetter: any, engineViewportService: any): this;
        dragOver(viewportId: any, x: any, y: any, dx: any, dy: any, engineAndPluginStateSetter: any, engineViewportService: any): this;
        keyDown(): this;
        mouseLeave(viewportId: any, engineViewportService: any): this;
    }
    export class MayaStyleTurntableRotationMouseBehaviour {
        constructor(engineAndPluginStateSetter: any);
        mouseDown(): this;
        mouseUp(viewportId: any, x: any, y: any, buttonNumber: any, modifiers: any, engineAndPluginStateSetter: any, engineViewportService: any): IdleMouseBehaviour | this;
        mouseMove(viewportId: any, x: any, y: any, dx: any, dy: any, engineAndPluginStateSetter: any, engineViewportService: any): this;
        dragOver(viewportId: any, x: any, y: any, dx: any, dy: any, engineAndPluginStateSetter: any, engineViewportService: any): this;
        keyDown(): this;
        mouseLeave(): this;
    }
    export class MayaStylePanMouseBehaviour {
        constructor(engineAndPluginStateSetter: any);
        mouseDown(): this;
        mouseUp(viewportId: any, x: any, y: any, buttonNumber: any, modifiers: any, engineAndPluginStateSetter: any): IdleMouseBehaviour | this;
        mouseMove(viewportId: any, x: any, y: any, dx: any, dy: any, engineAndPluginStateSetter: any, engineViewportService: any): this;
        dragOver(viewportId: any, x: any, y: any, dx: any, dy: any, engineAndPluginStateSetter: any, engineViewportService: any): this;
        keyDown(): this;
        mouseLeave(): this;
    }
    export class MayaStyleDollyMouseBehaviour {
        constructor(engineAndPluginStateSetter: any);
        mouseDown(): this;
        mouseUp(viewportId: any, x: any, y: any, buttonNumber: any, modifiers: any, engineAndPluginStateSetter: any): IdleMouseBehaviour | this;
        mouseMove(viewportId: any, x: any, y: any, dx: any, dy: any, engineAndPluginStateSetter: any, engineViewportService: any): this;
        dragOver(viewportId: any, x: any, y: any, dx: any, dy: any, engineAndPluginStateSetter: any, engineViewportService: any): this;
        keyDown(): this;
        mouseLeave(): this;
    }
    export class LeftClickDraggingMouseBehaviour {
        _startPos: number[];
        _switchBehaviorDeadZone: number;
        _dragBehaviour: any;
        constructor(dragBehaviour: any, startX: any, startY: any);
        mouseDown(): this;
        mouseUp(viewportId: any, x: any, y: any, buttonNumber: any, modifiers: any, engineAndPluginStateSetter: any, engineViewportService: any): IdleMouseBehaviour | this;
        mouseMove(viewportId: any, x: any, y: any, dx: any, dy: any, engineAndPluginStateSetter: any): any;
        keyDown(): this;
        mouseLeave(): this;
    }
    export class RightClickDraggingMouseBehaviour {
        _startPos: number[];
        _switchBehaviorDeadZone: number;
        _dragBehaviour: any;
        constructor(engineAndPluginStateSetter: any, dragBehaviour: any, startX: any, startY: any);
        mouseDown(): this;
        mouseUp(viewportId: any, x: any, y: any, buttonNumber: any, modifiers: any, engineAndPluginStateSetter: any, engineViewportService: any): IdleMouseBehaviour | this;
        mouseMove(viewportId: any, x: any, y: any, dx: any, dy: any, engineAndPluginStateSetter: any): any;
        keyDown(engineAndPluginStateSetter: any): any;
        mouseLeave(): this;
    }
    export class QuakeStyleMouseLookMouseBehaviour {
        constructor(engineAndPluginStateSetter: any);
        mouseDown(): this;
        mouseUp(viewportId: any, x: any, y: any, buttonNumber: any, modifiers: any, engineAndPluginStateSetter: any): IdleMouseBehaviour | this;
        mouseMove(viewportId: any, x: any, y: any, dx: any, dy: any, engineAndPluginStateSetter: any, engineViewportService: any): this;
        dragOver(viewportId: any, x: any, y: any, dx: any, dy: any, engineAndPluginStateSetter: any, engineViewportService: any): this;
        keyDown(): this;
        mouseLeave(): this;
    }
}
declare module "directives/engine-viewport" {
}
declare module "directives/focus-me" {
}
declare module "directives/goto-link-handler" {
}
declare module "directives/inner-label" {
}
declare module "directives/loading" {
    import "directives/core-src";
}
declare module "directives/modal-dialog" {
}
declare module "directives/number-keydown" {
}
declare module "directives/resizer" {
}
declare module "directives/spinner" {
    import "directives/number-keydown";
}
declare module "directives/tab-view" {
}
declare module "directives/time-line" {
    import "directives/context-menu";
    import "directives/droppable";
}
declare module "directives/toggleable-options" {
}
declare module "directives/trust" {
}
declare module "flow/flow-commands" {
    import { FlowGraph } from "flow/flow-graph";
    export function registerCommand(command: typeof FlowCommand): void;
    export function getCommandsFromPatch(patch: any, context: IFlowCommandContext): FlowCommand[];
    export interface IFlowCommandContext {
        flowGraph: FlowGraph;
    }
    export class FlowCommand {
        context: IFlowCommandContext;
        patches: any[];
        requiredPaths: string[];
        constructor(patch: any, context: any);
        isComplete(possibleCommands: any): boolean;
        supportsPatch(patch: any): boolean;
        addPatch(patch: any): void;
        apply(): void;
        compare(otherCommand: any): boolean;
        _getRequiredPaths(): any[];
        static canSelect(patch: any): boolean;
    }
}
declare module "properties/property-type-generator" {
    export class PropertyTypeGenerator {
        dataTypeService: any;
        propertyInitializer: (property: Property, path: string, typeDesc: any, defaultPropArgs: any, defaultDisplayType: string) => void;
        constructor(dataTypeService: any, propertyInitializer: any);
        genProperty(data: any, propertyPath: string, typeDesc: any): any;
        _initProperty(path: string, typeDesc: any, defaultPropArgs: any, defaultDisplayType?: string): any;
        ":array"(data: any, propertyPath: any, typeDesc: any): any;
        ":value"(data: any, propertyPath: any, typeDesc: any): any;
        ":dict"(data: any, propertyPath: any, typeDesc: any): any;
        ":set"(): void;
        ":switch"(data: any, propertyPath: any, typeDesc: any): any;
        ":struct"(data: any, propertyPath: any, typeDesc: any): any;
        ":bool"(data: any, propertyPath: any, typeDesc: any): any;
        ":number"(data: any, propertyPath: any, typeDesc: any): any;
        ":string"(data: any, propertyPath: any, typeDesc: any): any;
        ":enum"(data: any, propertyPath: any, typeDesc: any): any;
        ":resource"(data: any, propertyPath: any, typeDesc: any): any;
    }
    export default PropertyTypeGenerator;
}
declare module "properties/property-document" {
    import Emitter = require("common/event");
    import PropertyTypeGenerator from "properties/property-type-generator";
    class PropertyDocument extends Emitter {
        editorId: string;
        propertyTypeGenerator: PropertyTypeGenerator;
        dataModel: any;
        _categories: PropertyCategory[];
        properties: any;
        nbProperties: number;
        collapsedLogs: any;
        settings: any;
        _settingsCache: any;
        config: any;
        editedObjectsCount: number;
        groupEditing: (commandName, editingFunctor) => void;
        constructor(categories?: PropertyCategory[], opts?: any);
        categories: PropertyCategory[];
        addCategory(name: any, categoryOpts: any, initialValue: any, typeDesc: any, categoryDeactivatable: any): any;
        getProperty(path: any): any;
        getPropertyValue(path: any): any;
        getSettings(keys: string[], defaultValue?: any): any;
        setSettings(keys: any, value: any): void;
        updateCategoryCache(category: any): void;
        updatePropertyCache(property: any): void;
        _updatePropertyCache(property: any, propertyPath: any): void;
        _initProperty(property: any, path: any): void;
        static _defaultGroupEditing(commandName: any, editingFunctor: any): void;
    }
    export = PropertyDocument;
}
declare module "properties/property-editor-utils" {
    import PropertyDocument = require("properties/property-document");
    export function generateCategories(categories: PropertyCategory[], catType: string, propertyDocument: PropertyDocument): any;
    export function generateCategory(category: PropertyCategory, categoryKey: string, catType: string, propertyDocument: PropertyDocument): any;
    export function registerContainerMenu(property: Property): any;
    export function generatePropertyContainer(property: Property, propertyPath: string, propertyDocument: PropertyDocument, args?: any): any;
    export function generateAdskProperty(property: Property, propertyPath: string, propertyDocument: PropertyDocument): any;
    export function generateProperty(property: Property, propertyPath: string, propertyDocument: PropertyDocument): any;
    export function comparePropertyOrder(p1: Property, p2: Property): number;
    export type CreateTransformComponent = (properties: Property[], propertyDocument: PropertyDocument, categoryKey: string) => any;
    export function registerTransformComponent(creationFunctor: CreateTransformComponent): void;
    export type CreatePropertyFunctor = (property: Property, propertyPath: string, propertyDocument: PropertyDocument) => any;
    export let propertyComponents: Map<string, any>;
    export function registerPropertyComponent(dt: string | string[], creationFunctor: CreatePropertyFunctor, metaData?: any): void;
    export type PropertyHelperCreator = (...args) => Property;
    export let helpers: PropertyCreatorHelper;
    export function registerPropertyHelper(helperName: string, propertyHelperCreator: PropertyHelperCreator): void;
    export type PropertyTransformer = (property: Property, propertyPath: string) => void;
    export function iterateCategoryProperties(category: PropertyCategory, transformer: PropertyTransformer): void;
    export function iteratePropertyTree(property: Property, transformer: PropertyTransformer, parentPath?: string, propertyKey?: string): void;
    export function category(label: string, args: any, properties: Property[]): any;
    export function defaultProperty(propArgs: any, userArgs?: any): any;
    export function property(label: string, propArgs: any, userArgs?: any): any;
}
declare module "properties/property-action" {
}
declare module "properties/property-models" {
}
declare module "properties/property-boolean" {
    import "properties/property-models";
}
declare module "properties/property-carousel" {
}
declare module "properties/property-child" {
}
declare module "properties/property-choice" {
    import "properties/property-models";
}
declare module "properties/property-color-gradient" {
}
declare module "properties/property-color-temperature-slider" {
    import "properties/property-models";
}
declare module "properties/property-color" {
}
declare module "properties/property-custom-view" {
}
declare module "properties/property-data-object" {
}
declare module "properties/property-dict" {
}
declare module "properties/property-from-type" {
}
declare module "properties/property-graph" {
}
declare module "properties/property-json" {
}
declare module "properties/property-number" {
    import "properties/property-models";
}
declare module "properties/property-path" {
}
declare module "properties/property-prefix" {
}
declare module "properties/property-range" {
    import "properties/property-models";
}
declare module "properties/property-resource" {
}
declare module "properties/property-slider" {
    import "properties/property-models";
}
declare module "properties/property-string" {
    import "properties/property-models";
}
declare module "properties/property-struct" {
}
declare module "properties/property-switch" {
    import "properties/property-type-generator";
}
declare module "properties/property-table" {
}
declare module "properties/property-tag" {
}
declare module "properties/property-transform" {
}
declare module "properties/property-vector" {
    import "properties/property-models";
}
declare module "properties/property-components" {
    import "properties/property-action";
    import "properties/property-boolean";
    import "properties/property-carousel";
    import "properties/property-child";
    import "properties/property-choice";
    import "properties/property-color";
    import "properties/property-color-gradient";
    import "properties/property-color-temperature-slider";
    import "properties/property-custom-view";
    import "properties/property-data-object";
    import "properties/property-dict";
    import "properties/property-from-type";
    import "properties/property-graph";
    import "properties/property-json";
    import "properties/property-number";
    import "properties/property-path";
    import "properties/property-prefix";
    import "properties/property-range";
    import "properties/property-resource";
    import "properties/property-slider";
    import "properties/property-string";
    import "properties/property-struct";
    import "properties/property-switch";
    import "properties/property-table";
    import "properties/property-tag";
    import "properties/property-transform";
    import "properties/property-vector";
}
declare module "properties/property-editor-component" {
    import "properties/property-components";
    import PropertyDocument = require("properties/property-document");
    interface PropertyEditorDesc {
        document: PropertyDocument;
    }
    export { PropertyEditorDesc as Desc };
    export function component(opts: PropertyEditorDesc): any;
    export function loadCustomViews(): Promise<any>;
}
