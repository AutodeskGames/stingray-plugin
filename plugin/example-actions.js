define(() => {
    'use strict';

    /**
     * Called when the editor starts or after a new project has been loaded.
     */
    function onEditorStarted () {
        console.info('The editor has started. What a good day!');
    }

    /**
     * Raised when the current level changes in the level editor.
     */
    function onLevelChanged(args) {
        let levelName = args[1].Arg.ResourceName;
        console.info(`The current level has changed to \`${levelName}.level\``);
    }

    return {
        onEditorStarted,
        onLevelChanged
    };
});