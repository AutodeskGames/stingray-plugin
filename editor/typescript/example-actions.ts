import * as stingray from 'stingray';

declare const example: any;

/**
 * Called when the editor starts or after a new project has been loaded.
 */
export function onEditorStarted () {
    console.info('The editor has started. What a good day!');
}

/**
 * Raised when the current level changes in the level editor.
 */
export function onLevelChanged(args) {
    let levelName = args[1].Arg.ResourceName;
    console.info(`The current level has changed to \`${levelName}.level\``);
}

/**
 * Test the editor example native extension.
 */
export function testEditorNativeExtension() {
    // Dynamically load the version of native extension DLL
    const nativePluginDllPath = require.toUrl('@example/binaries/editor/win64/dev/editor_plugin_w64_dev.dll');
    if (!stingray.fs.exists(nativePluginDllPath))
        throw new Error('Example editor native extension does not exists at `' + nativePluginDllPath + '`. Was it compiled?');

    // Load this native extension will expose the global namespace `example`.
    let pluginId = stingray.loadNativeExtension(nativePluginDllPath);
        
    // Call our native functions.
    let resultArgs = example.test_log_arguments({pluginId, nativePluginDllPath}, null, true, "this is a string", ["an array element", "another array element"]);
    console.log(JSON.stringify(resultArgs));
    let specialObject = example.test_custom_allocator();
    specialObject = undefined;
    if (window.gc)
        window.gc();

    // We do not need the plugin anymore, let's dispose of it.
    stingray.unloadNativeExtension(pluginId);
}
