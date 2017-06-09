declare module "stingray" {
    import 'common/js-extensions';
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
        function generateThumbnail(resourcePath: any): Promise<Thumbnail | ThumbnailError>;
    }
    export = ThumbnailService;
}
