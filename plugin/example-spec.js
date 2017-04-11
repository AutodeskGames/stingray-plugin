/* jshint jasmine: true */
/* globals example, it, describe, expect */
describe("Plugin Example", function(require){
    "use strict";

    const stingray = require('stingray');

    const CONFIG = 'dev';
    //const CONFIG = 'debug'; // Uncomment this line if you want to test the debug version of your DLL.
    const DLL_PATH = require.toUrl(`example/binaries/editor/win64/${CONFIG}/editor_plugin_w64_${CONFIG}.dll`);

    var pluginId = null;

    it("load native extension", function () {
        expect(stingray.fs.exists(DLL_PATH)).toBeTruthy();
        pluginId = stingray.loadNativeExtension(DLL_PATH);
        
        expect(pluginId).toBeDefined();
        expect(example).toBeDefined();
    });

    it("native function call tests", function () {
        expect(example.test_dll_dependency).toBeDefined();
        let result = example.test_dll_dependency('Hello Plugin', 'This is a message from an external DLL dependency');
        expect(result).toEqual(1);
    });

    it("unload native extension", function () {
        expect(stingray.unloadNativeExtension(pluginId)).toBeTruthy();
    });
});
