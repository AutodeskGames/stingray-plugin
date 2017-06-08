/**
 * Stingray foundation APIs.
 */
interface Stingray {

    config: string;

    env: {
        version: string;
        coreDir: string;
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
}

interface FileStats {
    exists: boolean;
    dir: string;
    url: string;
    size: number;
    readonly: boolean;
    hidden: boolean;
    modified: number;
}

interface FileSystemApi {
    exists: (path: string) => boolean;
    stats: (path: string) => FileStats;

    Filters: any;
    FileNotify: any;
    FileAction: any;
    Permission: any;
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
    basename: (path: string, withExtension: boolean) => string;

    dirname: (path: string) => string;
    join: (path: string, ...paths: string[]) => string;

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

interface Promise<T> {
    spread(a: (...args)=>PromiseLike<T>, b?:()=>Promise<T>): Promise<T>;
    finally(a, b): Promise<T>;
}

interface String {
    hashCode: () => number;
}

interface PromiseConstructor {
    filter(array, promiseReturningFilter): Promise<any>;
    map(collection, promiseReturningTransformer): Promise<any>;
    series(items:any[]|Object, next:any, initialValue?:Promise<any>): Promise<any>;
    while(predicate, action, result): Promise<any>;
    require(modules:string[]): Promise<any>;
    waterfall(funcs:Function[]):Promise<any>;
}

interface Console {
    notice: Function;
}

interface CefRequest {
    request: string;
    persistent: boolean;
    onSuccess: (result: string) => void;
    onFailure: (code:number, msg:string) => void;
}

interface Window {

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
}

interface Document {
    // Document Editing Model Extensions
    getParentTab: Function;
    getToolName: () => string;
}

interface RequireInternals {
    contexts: {_:{config:{paths:object}}};
}

interface Require {
    s: RequireInternals;
    resolvable: Function;
}

interface WindowEventMap extends GlobalEventHandlersEventMap {
    "ConsoleMessage": CustomEvent;
}

interface OffHandler { (): any; promise: Promise<any>; }

// Module not (yet) ported to TypeScript
declare module 'lodash';

declare module 'common/asset-utils';
declare module 'common/keycodes';
declare module 'common/context-menu-utils';

declare module 'components/mithril-ext';
declare module 'components/button';
declare module 'components/textbox';

declare module 'extensions/parser-utils';
declare module 'extensions/services';
declare module 'extensions/events';

declare module 'extensions/menus';

declare module 'services/host-service';
declare module 'services/level-editing-service';
declare module 'services/log-service';
declare module 'services/settings-service';
declare module 'services/plugin-service';
declare module 'services/event-service';
