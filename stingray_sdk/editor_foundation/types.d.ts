/**
 * Stingray foundation APIs.
 */
interface Stingray {

    config: string;

    env: {
        version: string;
        coreDir: string;
        userDocumentsDir: string;
        tccFilePath: string;
        pluginsDir: string;
        appDir: string;
        editorDir: string;

        config: {
            build_info: {
                project_name: string;
                build_name: string;
                build_version: string;
            }
        }
    }

    /**
     * Indicates if the system is ran through Team City.
     */
    teamCity: any | boolean;

    /**
     * Checks if we are running in development mode.
     */
    isDev: () => boolean;

    /**
     * Checks the framework is running tests.
     * @returns {boolean} true if it is running tests.
     */
    isRunningTests: () => boolean;

    /**
     * Extract query param value for the window URL chain (e.g. from current window to top window)
     * @param {string} name - Name of the query param
     * @param {boolean} [firstLevelOnly] - Only check the URL of the current window.
     */
    getParameterByName: (name: string, firstLevelOnly?: boolean) => string|boolean;

    /**
     * Returns a GUID
     * RFC 4122 Version 4 Compliant solution:
     * http://stackoverflow.com/questions/105034/how-to-create-a-guid-uuid-in-javascript
     */
    guid: () => string;

    /**
     * @deprecated
     * Checks if object is a promise
     */
    isPromise: (promise: Promise<any>) => boolean;

    prependToLogMessage: (type, message) => string;

    /**
     * Hijack logs to prepend [DEBUG|INFO|ERROR] tags
     * @param {string} pageTitle - Page title used if the document don't have any.
     */
    hijackConsole: (pageTitle: string) => void;

    /**
     * Returns an global angular service by name.
     * @param serviceName {string} service to be fetched.
     */
    getService: (serviceName: string) => Promise<any>;

    /**
     * Emit a global event in the system.
     */
    emitEvent: (name: string, ...args) => Promise<any>;

    loadNativeExtension: (path: string) => string;
    unloadNativeExtension: (id: string) => boolean;

    loadAsyncExtension: (path: string) => Promise<string>;
    unloadAsyncExtension: (id: string) => Promise<boolean>;

    hostExecute: (type: string, firstArg?: any) => Promise<any>;

    openDevTools: () => void;

    location: LocationApi;
    host: HostApi;
    fs: FileSystemApi;
    path: PathApi;
    sjson: SJSONApi;
}

/**
 * Generic functions to manipulate page location.
 */
interface LocationApi {
    removeParam: (paramName) => void;
    addParam: (paramName, paramValue) => void;
    toFilePath: (string) => string;
}

/**
 * Various host interaction API.
 */
interface HostApi {
    quit: (exitCode?: number) => Promise<any>;
    getCommandLineSwitch: (name: string) => Promise<boolean | any>;
    createService: (name, path) => Promise<any>;
    setCursorStyle: (style: string) => Promise<boolean>;
    openWindow: (url: string, id?: string, options?: object) => Promise<any>;
    crash: () => {};

    /**
     * Execute a shell command or open an URL in the default browser.
     */
    openUrl(url:string): boolean;
}

interface FileStats {
    exists: boolean;
    dir: boolean;
    url: string;
    size: number;
    readonly: boolean;
    hidden: boolean;
    modified: number;
}

interface FileSystemApi {
    exists (path: string): boolean;
    enumerate (directory:string, searchPattern: any, recursive: boolean): string[];
    stats (path: string): FileStats;
    unlink(path:string): boolean;
    copy(source:string, dest:string): boolean;
    move(source:string, dest:string): boolean;
    read(path:string, asBinary:boolean): string;
    write(path:string, content:any, asBinary:boolean): boolean;
    unzip(path:string, destination:string): boolean;
    mkdir(path:string): boolean;
    toUniqueFileName (name:string, baseFolder:string): string;
    toUniqueDirectoryName (name:string, baseFolder:string): string;

    Filters: any;
    FileNotify: any;
    FileAction: any;
    Permission: any;
}

interface SJSONApi {
    load(path:string): any;
    save(path:string, any): boolean;
    parse(sjson:string): any;
    stringify(obj:any): string;
}

/**
 * Stingray path manipulation API.
 */
interface PathApi {
    sep: string;
    delimiter: string;

    /**
     * @description Extract the filename of a path
     * @param {string} path
     * @param {boolean} [withExtension=true] - Set to false if you want the extension to be omitted.
     */
    basename: (path: string, withExtension?: boolean) => string;

    dirname: (path: string) => string;
    join: (...paths: string[]) => string;

    absolute: (base: string, relative: string, isFileName?: boolean) => string;
    clean: (path: string, addSeparatorsAtEnd?: boolean) => string;
    resolve: (path: string) => string;
    relative: (from: string, to: string) => string;
    suffix: (path: string, noLeadingDot: boolean) => string;
    ensureValid: (path: string) => string;
    areEquals: (path1: string, path2: string) => boolean;
    getFilePathWithoutExtension: (path: string) => string;
    isFileOrFolderNameValid: (name: string) => boolean;
}

interface BaseService {
    new(id:string, resolveCallback?: Function): BaseService;

    _remoteService: any;
    promise: Promise<any>;
    marshallingService: any;

    ready: () => Promise<boolean>;
    invoke: (methodName:string, ...args) => Promise<any>;
    invokeMethod: (methodName:string, args:any[], options?: any) => Promise<any>;
}

interface ExtensionDynamicString {
    resolve(args:any[], keepAsString?:boolean): Promise<string>;
}

interface IExtension {
    new(data: any): IExtension;

    module:any;

    define(extensionName: string, behaviors: object, parsers: Function[], toBeMerged: object): any;

    wrap (extensionData, pluginName): object;
    expandToPluginDir (fieldName, setDefaultToPluginRoot?): Function;
    toDynamicString (s:string): ExtensionDynamicString;
}

interface EventSource {
    new(): this;
    emit (name:string, ...args): any;
    on (name:string, ...args): any;
    off(name: string, callback): any;
}

interface Promise<T> {
    cancel: () => void;
    spread(a: (...args)=>any, b?:()=>Promise<T>): Promise<T>;
    finally(a, b?): Promise<T>;
}

interface String {
    hashCode: () => number;
    regexIndexOf: (regex: RegExp, startPos?: number) => number;
    regexLastIndexOf: (regex: RegExp, startPos?: number) => number;
}

interface Math {
    between: (min: number, max: number) => number
}

interface PromiseConstructor {
    filter(array, promiseReturningFilter): Promise<any>;
    map(collection, promiseReturningTransformer): Promise<any>;
    series(items:any[]|Object, next:any, initialValue?:any): Promise<any>;
    while(predicate, action, result): Promise<any>;
    require(modules:string[], doNotPrintErrors?:boolean): Promise<any>;
    waterfall(funcs:Function[]): Promise<any>;
    and(a: Promise<any>|any, b: Promise<any>): Promise<any>;
    or(a: Promise<any>, b: Promise<any>): Promise<any>;
    on(eventSource: EventSource, eventName: string, eventHandler: Function): Promise<any>;
    timeout(timeoutMs: number): Promise<any>;
    until(condition: () => Promise<any>, timeoutMs?: number, intervalMs?:number): Promise<any>;
}

interface Console {
    notice: Function;
}

interface CefRequest {
    request: string;
    persistent?: boolean;
    onSuccess: (result: string) => void;
    onFailure: (code:number, msg:string) => void;
}

interface Window {

    $(...args:any[]): any;

    stingray: Stingray;

    /**
     * @typedef {object} CefRequest
     * @property {string} request - JSON string sent to CEF as payload.
     * @property {function} onSuccess - Callback if the CEF request succeeds.
     * @property {function} onFailure - Callback if the CEF request fails.
     *
     * This function queries the CEF widget for a function.
     * @name window.cefQuery
     * @function
     * @param {CefRequest} request - Request with success and failure callbacks
     * @memberof window
     */
    cefQuery: (request: CefRequest) => Promise<any>;

    gc: () => void;

    options: any;
    promise: PromiseLike<any>;
    reject: Function;
    accept: (result) => void;

    module: any;
    global: any;
    jsonpatch: any;

    // Test APIs

    jasmineReporters: any;
    describe: Function;
    stubModules: Function;
    inject: (Function) => void;

    layoutId: string;
    isClosing: boolean;
    isMainWindow: boolean;
    bindLayout: Function;
    saveLayout: Function;
    removeLayout: Function;
    resetLayout: Function;
    reloadTab: Function;
    setTitle: Function;

    id: string;
    root: string;
    rootHref: string;
    coreRootHref: string;
    debugging: boolean;
    runningTest: boolean;

    isProgram: boolean;
    isService: boolean;
    isFocused: boolean;
    aboutToReload: boolean;

    hide: ()=>void;
    show: ()=>void;
    dpiScale: ()=>number;

    stingrayDragEnterFiles: string[];

    ondownloadfileprogress: (id, loaded, total) => void;

    unsavedDocumentsSent: boolean;

    // Used by the node editor
    PIXI: any;
}

interface EventTarget {
    nodeName: string;

    addEventListenerBase(type: string, listener?: EventListenerOrEventListenerObject, useCapture?: boolean): void;
    removeEventListenerBase(type: string, listener?: EventListenerOrEventListenerObject, useCapture?: boolean): void;
}

interface XMLHttpRequestEventTarget {
    status: number;
    response: string|ArrayBuffer|any;
    statusText: string;
}

interface Document {
    // Document Editing Model Extensions
    getParentTab: Function;
    getToolName: () => string;
    isDirty: (value: boolean) => any;
    save: (resourcePath: string) => any;
    discard: (resourcePath: string) => any;
    getDocumentName: () => string;
    getResourcePath: () => any;
    getDocking(): any;
    focusTab(): void;
    close(): any;
    updateTabName: (tabName: string, isDirty?: boolean) => any;
    updateTabResourceName: (tabRessourceName: string) => any;
}

interface Element {
    contentDocument: Document;
}

interface RequireInternals {
    contexts: {_:{config:{paths:object}}};
}

interface Require {
    s: RequireInternals;
    resolvable: Function;

    (config: any, modules: string[], ready: Function, errback: Function): void;
}

interface Performance {
    memory: {
        usedJSHeapSize: number;
        totalJSHeapSize: number;
        jsHeapSizeLimit: number;
    };
}

interface WindowEventMap extends GlobalEventHandlersEventMap {
    "ConsoleMessage": CustomEvent;
    "ContextMenuAction": CustomEvent;
    "ContextMenuDismiss": CustomEvent;
    "ContextMenuHide": CustomEvent;
    "MenuAction": CustomEvent;
    "running": CustomEvent;
}

interface ErrorConstructor {
    captureStackTrace(thisArg: any, func: any): void
}

interface OffHandler { (): any; promise: Promise<any>; }
interface NestedCallbackHandler { (): any; callback: () => any; }

interface IDataStore
{
    new(url:string): IDataStore;
    findEvent (name, uri): any;
    getCandidates (uri, initialCandidate, enumerator?): any[];
    url: URL;
}

interface ITreeModel {
    new (name: string);
}

interface IDefaultViewportMouseBehavior {
    new (engineService: any, engineViewportId: string, engineViewportInterops: any)
}

interface IDefaultViewportController {
    new (engineService: any)
}

interface Vector2Object {
    x: number;
    y: number;
}

interface Vector3Object {
    x: number;
    y: number;
    z: number;
}


// Module not (yet) ported to TypeScript
declare module 'lodash';
declare module 'ace';
declare module 'pixi';

declare module 'core/views/viewport-context-menus';

declare module 'common/asset-utils';
declare module 'common/keycodes';
declare module 'common/context-menu-utils';
declare module 'common/file-system-utils';
declare module 'common/profiler';
declare module 'common/lodash-ext';
declare module 'common/console-connection';
declare module 'common/math-utils';
declare module 'common/project-utils';
declare module 'common/default-viewport-controller';
declare module 'common/default-viewport-mouse-behavior';
declare module 'common/console-connection';
declare module 'common/color-utils';
declare module 'common/drag-utils';
declare module 'common/string-utils';

declare module 'components/mithril-ext';
declare module 'components/button';
declare module 'components/textbox';
declare module 'components/dom-tools';
declare module 'components/journal-view';
declare module 'components/list-view';
declare module 'components/accordion';
declare module 'components/filter-view';
declare module 'components/resizer';
declare module 'components/tree-view';
declare module 'components/accordion';
declare module 'components/color-gradient';
declare module 'components/engine-viewport';
declare module 'components/toolbar';
declare module 'components/typeahead';
declare module 'components/loading';
declare module 'components/spinner';

declare module '3rdparty/marked/marked.min';

declare module 'properties/mithril-property-ext';
declare module 'properties/property-editor-utils';
declare module 'properties/property-editor-component';
declare module 'properties/property-document';
declare module 'properties/property-models';

declare module 'docking/docking-utils';

declare module 'foundation/spm-registry';
declare module 'foundation/project';
declare module 'foundation/backend-client';
declare module 'foundation/data-server-store';
declare module 'foundation/file-system-store';
declare module 'foundation/document-editing';
declare module 'foundation/asset-server';

declare module 'extensions/actions';
declare module 'extensions/asset-types';
declare module 'extensions/contextual-actions';
declare module 'extensions/events';
declare module 'extensions/generic-parser';
declare module 'extensions/menus';
declare module 'extensions/migrations';
declare module 'extensions/parser-utils';
declare module 'extensions/preview-behaviors';
declare module 'extensions/resources';
declare module 'extensions/services';
declare module 'extensions/views';
declare module 'extensions/node-customizers';

declare module 'services/level-editing-service';
declare module 'services/log-service';
declare module 'services/settings-service';
declare module 'services/plugin-service';
declare module 'services/project-service';
declare module 'services/asset-service';
declare module 'services/file-system-service';
declare module 'services/savable-service';
declare module 'services/asset-service';
declare module 'services/content-database-service';
declare module 'services/object-editing-service';
declare module 'services/data-service';
declare module 'services/engine-viewport-service';
declare module 'services/object-creator-service';
declare module 'services/animation-editing-service';

