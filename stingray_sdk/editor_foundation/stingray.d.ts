declare module "common/lodash-ext" {
    import * as _ from 'lodash';
    export = _;
}
declare module "stingray" {
    import 'common/js-extensions';
    const stingray: Stingray;
    export = stingray;
}
declare module "common/dom-updater" {
    export function requestUpdate(context?: any, updatedRemoteObject?: any, propertyUpdated?: any): any;
    export function registerUpdater(name: any, updateCallback: any): void;
    export function unregisterUpdater(name: any): void;
    export function isUpdating(): boolean;
    export function isModelUpdated(remoteObject: any): boolean;
}
declare module "app" {
    import 'angular-bootstrap';
    import 'angular-growl';
    var app: any;
    export = app;
}
declare module 'services/event-service' {
    function on(eventName: string, callback: Function): any;
    function on(eventName: string, offerCondition: Function, callback: Function): any;
    function emit(event: string, ...args: any[]): any;
    function offer(event: string, ...args: any[]): any;
}
declare module "base" {
    var baseFileName: string;
    function _initModule(): Promise<any>;
    function _loadModule(): Promise<any>;
    function _keyBinding(): void;
    export { baseFileName as name, _initModule as init, _loadModule as run, _keyBinding as initKeyBinding };
}
declare module 'services/channel-service' {
    function on(ns: string, eventName: string, callback: Function): any;
    function openChannel(namespaces: string[]): any;
    function request(ns: string, methodName: string, param: any, noDomUpdate?: boolean): any;
    function send(ns: string, type: string, data: {
        id: string;
        propertyName: string;
        value: any;
    }): any;
    function suppressPropertyChanged(remoteObjectId: string, propertyName: string): any;
    function unsuppressPropertyChanged(remoteObjectId: string, propertyName: string): any;
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
    export interface RequestObjectConfig {
        propertyPath: string;
        proxy: boolean;
    }
    export function requestRemoteObject(remoteObject: any, remoteObjectInstanceName?: string, remoteObjectAdditionalData?: any, options?: any): any;
    export function createRemoteObject(remoteObjectTypeName: any, genericTypes: any, args: any): any;
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
declare module "services/remote-service" {
    import { RemoteObject } from "services/marshalling-service";
    export { RemoteObject } from "services/marshalling-service";
    export class RemoteService {
        promise: Promise<RemoteObject>;
        private _remoteService;
        constructor(remoteServiceId: any, onRemoteServiceResolved?: Function);
        on(event: any, handler: any): OffHandler;
        off(event: any, handler: any): Promise<RemoteObject>;
        invoke(methodName: any): Promise<RemoteObject>;
        invokeMethod(methodName: any, args: any, methodParams: any): Promise<any>;
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
        SaveNewFile: string;
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
    export function startProcess(processPath: any, args: any, options: any): Promise<any>;
    export function executeCustomUrl(href: any): Promise<any>;
    export function getMenuItems(): Promise<any>;
    export function executeMenuItem(menuActionPath: any): Promise<any>;
    export function updateMenuItem(menuActionPath: any, newLabel: any, disable: any): Promise<any>;
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
    var baseFileName: string;
    function loadSystem(): Promise<any>;
    export { baseFileName as name, loadSystem as run };
}
declare module "service" {
    function runService(): Promise<void>;
    const name: string | boolean;
    export { name, runService as run };
}
declare module "editor" {
    export function run(doNotRunBaseModule?: boolean): any;
    export function initKeyBinding(): void;
    export const name = "editor";
}
declare module "window" {
    import 'docking/docking-service';
    import 'docking/docking-directive';
}
declare module "common/context-menu-utils" {
    const _default: (context: any, event: any, items: any, hostService: any) => any;
    export = _default;
}
declare module "common/event" {
    class Event {
        _events: {};
        constructor();
        static makeEventHandler(owner: any): any;
        on(event: any, condition?: any, callback?: any): any;
        off(event: any, callback: any): this;
        once(event: any, condition: any, callback: any): this;
        removeAllListeners(event: any): this;
        emit(event: string, ...args: any[]): boolean;
        listeners(event: any): any;
    }
    export = Event;
}
declare var Matrix: any;
declare var Vector: any;
declare var $V: Function;
declare var $M: Function;
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
declare module "common/import-defaults" {
    export const defaults: {
        pick_texture_template_by_material: boolean;
        pick_texture_template_by_pixels: boolean;
        pick_texture_template_by_suffix: boolean;
        reverse_forward_axis: boolean;
    };
    export function getSetting(settings: any, keyName: any): any;
}
declare module "common/interpolate" {
    export namespace number {
        function linear(start: number, end: number, t: number): number;
    }
}
declare module "common/lua-utils" {
    export function toSyntax(obj: any): any;
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
        invoke(methodName: any): Promise<any>;
        invokeMethod(methodName: any, args: any, methodParams: any): Promise<any>;
        ready(): Promise<any>;
    }
    export = BaseService;
}
declare module "services/engine-service" {
    import { RemoteObject } from "services/remote-service";
    export class CompilationError extends Error {
        result: any;
        constructor(msg: any, compilationResult: any);
    }
    export interface IEngine {
        Id: string;
        Name: string;
        IsRunning: boolean;
        IsSlaving: boolean;
    }
    export interface EngineCallback {
        (IEngine: any): any;
    }
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
    export function editorEngineReady(): Promise<{}[]>;
    export function addEngineMessageHandler(engine: any, messageType: any, callback: any): any;
    export function addEditorEngineMessageHandler(messageType: any, callback: any): any;
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
    export function postEditorCallback(callback: any): Promise<{}>;
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
    export function enqueueDataCompile(): Promise<any>;
    export function compile(assets?: string[]): Promise<any>;
    export function isCompiling(): Promise<any>;
    export function suspendDataCompile(isSuspended: boolean): Promise<any>;
    export function getEngineConnection(engine: any): any;
    export function getEngineConnections(engines: any): Promise<{}[]>;
    export function getEngineById(id: string): any;
    export function getEngineByName(name: string): any;
    export function evaluateScript(script: any, engine: any, timeoutMs?: number): Promise<{}>;
    export function on(...args: any[]): any;
    export function off(...args: any[]): any;
    export function invoke(...args: any[]): any;
    export function invokeMethod(...args: any[]): any;
    export function ready(): Promise<RemoteObject>;
}
declare module "common/preview-utils" {
    export function sendToViewport(viewportName: any, methodName: any, ...args: any[]): any;
    export function sendToViewportWithEngine(engine: any, viewportName: any, methodName: any, ...args: any[]): any;
    export function isAssetAvailable(asset: any): Promise<{}>;
}
declare module "common/timer" {
    export class Timer {
        _timerId: any;
        _interval: any;
        _callback: any;
        constructor(callback: any, interval: any);
        start(): void;
        cancel(): void;
    }
    export function now(): Date;
    export function time(): number;
}
declare module "common/tree-view-utils" {
    import Event = require("common/event");
    export function compareStrings(str1: any, str2: any): boolean | -1;
    export function createWrapperFromViewModel(marshallingService: any, treeViewModel: any, callback: any): void;
    export function createRemoteTreeModelWrapper(marshallingService: any, remoteObjectName: any, callback: any): void;
    export class TreeModel extends Event {
        _id: number;
        SelectedNodes: any[];
        nodeRemoved: any;
        FlatList: any[];
        _root: any;
        _nodeOrderSelector: any;
        _rootOptions: any;
        _rootTitle: any;
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
        addNode(parent: any, title: any, type: any, options: any, doNotUpdateTree?: boolean): any;
        removeNode(nodeToRemove: any, doNotCleanup?: boolean): void;
        removeNodes(nodesToRemove: any): any;
        modifyNode(node: any, parent: any, title: any, type: any, options: any, doNotUpdateTree: any): any;
        canBeSelected(node: any): boolean;
        clear(): void;
        refresh(): void;
        _createNode(title: any, type: any, options: any): any;
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
        onClick(): void;
        onDoubleClick(event: any): void;
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
declare module "services/data-service" {
    import 'external/json-patch';
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
        rollback(iterations?: number): Promise<never>;
        reroll(iterations?: number): Promise<never>;
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
        constructor(code: any, msg: any);
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
        "ini": SJSONSerializer;
        "unit": SJSONSerializer;
        "entity": SJSONSerializer;
        "material": SJSONSerializer;
        "s2d": PassthroughSerializer;
        "lua": PassthroughSerializer;
    };
    export function mount(base: any): Database;
    export function fetchOptions(options: any): any;
    export { AssetGlob as Glob };
    export { AssetUri as Uri };
}
declare module "services/file-system-service" {
    export function pathExists(path: any): Promise<boolean>;
    export function directoryPathIsValid(path: any): Promise<boolean>;
    export function filePathIsValid(path: any): Promise<boolean>;
    export function isFileOrFolderNameValid(name: any): boolean;
    export function getDocumentFolder(): Promise<string>;
    export function isPathRooted(path: any): any;
    export function getExtension(path: any, noLeadingDot: any): any;
    export function getFileName(path: any, withoutExtension: any): any;
    export function extractDir(path: any): any;
    export function getFilePathWithoutExtension(path: any): any;
    export function cleanPath(path: any): any;
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
    export function readFile(path: any, asBinary: any): Promise<string>;
    export function writeFile(path: any, content: any): any;
    export function unzip(zipPath: any, extractPath: any, overwrite: any): Promise<boolean>;
    export function createDirectory(path: any): Promise<boolean>;
    export function renameFile(filePath: any, newFilePath: any): Promise<boolean>;
}
declare module "flow/flow-utils" {
    export const CLASS_PREFIX = "Stingray.Foundation.Flow";
    export const FLOW_NODE_DEFINITION_FILE_EXTENSION = ".flow_node_definitions";
    export const SCRIPT_FLOW_NODE_DEFINITION_FILES_EXTENSION = ".script_flow_nodes";
    export const FLOW_EDITOR_GRAPH_FILE_EXTENSION = ".flow_editor";
    export const FLOW_NODE_RESOURCE_KEY = "flow_nodes_resource";
    export const enum FLOW_TYPES {
        UNIT = 0,
        LEVEL = 1,
        SUBFLOW = 2,
    }
    export function completeClassName(className: string): string;
    export function shortClassName(className: string): string;
    export function getVariableDefinition(definitionList: any, variableName: string): any;
    export function fixLegacyFlowNodes(graph: any, nodeDefinitions: any): void;
    export function fixSpawnEntityFlowNodes(graph: any, nodesDefinition: any): void;
    export function fixConnections(graph: any): void;
    export function convertOldClassToStingray(graph: any): void;
    export function replaceStringForElementRecursively(object: any, key: any, find: any, replace: any): void;
    export function getNodeColor(node: any): any;
    export function getNodeCategoryColor(categoryName: any): any;
    export function getConnectorColor(connectorType: any): any;
    export function getColorFromHashCode(hashCode: any): string;
    export function variableClassToType(className: string): any;
    export function getInputClassNameFromType(type: string): string;
    export function getOutputClassNameFromType(type: string): string;
    export function runtimeTypeToConnectionType(type: string): any;
    export function connectionTypeToRuntimeType(type: string): any;
    export function getCustomTypeDefinition(variableDefinition: any, globalDefinition: any): any;
    export function getCustomTypeName(variableDefinition: any, globalDefinition: any): any;
    export function getBrowsableSpec(elementDefinition: any, globals: any): any;
    export function getEnumSpec(elementDefinition: any, globals: any): any;
    export function getBrowsableUITypesTitle(elementDefinition: any, globals: any): any;
}
declare module "services/flow-service" {
    export let scriptFlowNodes: any[];
    export let flowNodeDefinitions: any[];
    export function loadAndValidateFlowNodeDefinition(resources: any, filePaths: any): any[];
    export function loadFlowNodeDefinitionFile(resource: any, filePath: any): any[];
    export function loadAndValidateScriptFlowNodes(resources: any, filePaths: any): any;
    export function loadScriptFlowNodeDefinitionFile(resource: any, filePath: any): any[];
    export function on(name: string, condition?: (...args: any[]) => boolean, callback?: (...args: any[]) => void): any;
    export function ready(): Promise<any>;
}
declare module 'services/object-creator-service' {
    function clearSelection(): Promise<void>;
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
declare module "node-editor/node-editor-adapter-factory" {
    import '3rdparty/node-editor/node-editor';
    export function createGraph(nodeEditorViewModel: any): any;
    export function createNode(node: any): any;
    export function createConnection(connection: any): any;
    export function createGroup(group: any): any;
    export function setStyling(styling: any): void;
    export function ready(): any;
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
declare module "node-editor/node-editor-view" {
    import '3rdparty/node-editor/node-editor';
    import { NodeEditorGraph, INodeAutoCompleteData } from "node-editor/node-editor-graph";
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
    import { INodeEditorViewConfig } from "node-editor/node-editor-view";
    import { NodeEditorGraph } from "node-editor/node-editor-graph";
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
declare module "components/loading" {
    class Loading {
        static view(): any;
    }
    export default Loading;
}
declare module "flow/flow-variable" {
    import { VariableDefinition } from "node-editor/variable-definition";
    export interface IFlowVariableModel {
        Value: any;
        Hidden?: boolean;
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
        exportRuntimeModel(exportContext: any): any;
        clear(): void;
        getExportName(): string;
        isEvent(): boolean;
    }
}
declare module "flow/variables/flow-variable-definitions" {
    import { FlowVariable, IFlowVariableModel } from "flow/flow-variable";
    import { FlowNode } from "flow/flow-node";
    export interface IUnitVariableMode extends IFlowVariableModel {
        UseMyUnit: boolean;
    }
    export class UnitVariable extends FlowVariable {
        model: IUnitVariableMode;
        constructor(model: IUnitVariableMode, context: any, definition?: any);
        readonly Value: string;
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
        browse(context: any, types: any): any;
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
    }
    export function createVariableFromType(type: string, model: IFlowVariableModel, node: FlowNode, definition?: any): any;
}
declare module "flow/flow-node" {
    import { NodeDefinition } from "node-editor/node-definition";
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
        exportRuntimeModel(exportContext: any): {
            type: any;
            id: string;
        };
        getExportName(): any;
        isDataDrivenFlowNodeType(type: any): boolean;
        getVariableBrowserStrings(element: any): Promise<any[]>;
        getVariableTypes(element: any): any[];
        getVariableBrowserTitle(element: any): string;
        getVariableEnumChoices(element: any): any[];
        static defaultEditorModel(): IFlowNodeModel;
        _exportVariables(exportContext: any, model: any): void;
        _exportConnections(exportContext: any, model: any): void;
        _exportCustoms(exportContext: any, model: any): void;
    }
}
declare module "flow/flow-node-browse-functions" {
    export function invokeBrowseFunction(browseFuncName: any, args: any): Promise<any>;
}
declare module "flow/nodes/data-driven-flow-node" {
    import { FlowNode, IFlowNodeModel } from "flow/flow-node";
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
        getVariableTypes(element: any): any;
        getVariableBrowserTitle(element: any): any;
        getVariableEnumChoices(element: any): any;
        isDataDrivenFlowNodeType(type: any): boolean;
        static defaultEditorModel(): IDataDrivenFlowNodeModel;
    }
}
declare module "flow/nodes/built-in-nodes" {
    import { FlowNode, IFlowNodeModel } from "flow/flow-node";
    import { IFlowVariableModel } from "flow/flow-variable";
    export interface INestedFlowModel extends IFlowNodeModel {
        InEvents: string[];
        OutEvents: string[];
        InVariableNames: string[];
        InVariables: any[];
        OutVariableNames: string[];
        OutVariables: any[];
    }
    export type PrefixAndPath = {
        prefix: string;
        path: string;
    };
    export class NestedFlow extends FlowNode {
        model: INestedFlowModel;
        constructor(model: INestedFlowModel, flowContext: any);
        clear(): void;
        loadElements(model: INestedFlowModel): void;
        getFlowResourcePath(): Promise<PrefixAndPath[]>;
        parseEvents(flowContext: any): Promise<boolean>;
        appendSlots(flowPath: string, nodeDefinitions: any, prefix?: string): void;
        parseSlots(flowPrefixAndPaths: PrefixAndPath[], nodeDefinitions: any): boolean;
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
        getFlowResourcePath(): Promise<PrefixAndPath[]>;
        parseEvents(flowContext: any): Promise<boolean>;
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
        static defaultEditorModel(): ICustomScriptNodeModel;
    }
}
declare module "flow/flow-migration" {
    export function getScriptArgumentType(scriptArgumentDefinition: any): any;
    export function migrate(graph: any, nodeDefinitions?: any): any;
    export function validate(graph: any): any;
    export function patchDataDrivenFlowNodes(nodes: any, nodeDefinitions: any, nodesToUpdate: any): boolean;
    export function patchDataDrivenFlowNode(node: any, nodeDefinition: any): number;
    export function patchNestedFlowNodes(nodes: any, nodesToUpdate: any, flowContext: any): Promise<any>;
    export function importProjectChangesForNode(node: any, flowContext: any): any;
    export function patchScriptFlowNodes(nodes: any, scriptFlowNodeDefinitions: any, nodesToUpdate: any): boolean;
    export function patchScriptFlowNode(node: any, scriptFlowNodeDefinition: any): boolean;
    export function updateScriptFlowNode(node: any, scriptFlowNodeDefinition: any): boolean;
    export function parseScriptNodeArgumentDefinition(argumentName: any, scriptNodeArgumentDefinition: any): {
        rawName: any;
        type: any;
        defaultValue: any;
        choices: any[];
        filter: any;
    };
}
declare module "flow/flow-commands" {
    export function registerCommand(command: any): void;
    export function getCommandsFromPatch(patch: any, context: any): any[];
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
        static defaultEditorModel(): IFlowConnectionModel;
    }
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
    import { FlowNode } from "flow/flow-node";
    import { FlowGroup } from "flow/flow-group";
    import { FlowConnection } from "flow/flow-connection";
    import * as builtInNodes from "flow/nodes/built-in-nodes";
    import { DataDrivenFlowNode } from "flow/nodes/data-driven-flow-node";
    export class FlowGraph extends NodeEditorGraph {
        nodes: FlowNode[];
        groups: FlowGroup[];
        connections: FlowConnection[];
        model: any;
        flowContext: any;
        _nodeRegistryCreationDictionary: any;
        _offHandlers: any[];
        constructor(graphModel: any, flowContext: any);
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
        updateSlot(node: any, slot: any, rebuildSlots: any, withUndo: any): Promise<void>;
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
        createNodeFromModel(model: any): any;
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
        static create(graphModel: any, flowContext: any): Promise<FlowGraph>;
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
        _addConnection(flowConnection: any, emitModelChange?: boolean): void;
        _addGroup(flowGroup: any, emitModelChange?: boolean): void;
        _createGroup(groupName: any): FlowGroup;
        _updateDataDrivenFlowNodeAutoComplete(nodeDefinitions: any, showNodeFilter?: any): void;
        _updateScriptFlowNodeAutoComplete(nodeDefinitions: any, showNodeFilter?: any): void;
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
        _handleFlowNodeDefinitionChanged(): void;
        _handleScriptFlowNodeDefinitionChanged(): void;
        _handleFlowEditorGraphsChanged(flowGraphPaths: any): void;
    }
}
