// nodeEditor.js interfaces
interface EventEmitter {
    on (evtName: string, fn: (source: any, ...args: any[]) => any): void;
    off (evtName: string, fn?: (source: any, ...args: any[]) => any): void;
    fire (evtName: string, ...args: any[]): void;
}

interface NodeEditor extends EventEmitter {
    new (element: HTMLElement, viewSettings: any): NodeEditor;
    addToSelection (id: string|PixiBaseShape|Array<string|PixiBaseShape>, disableEvents?: boolean): void;
    beginCurveDrag (options: {node: string, slot: string, connector?: string}): void;
    clear (): void;
    clearSelection (disableEvents: boolean): void;
    createNodeOptions (options: any): PixiNodeOptions;
    createTag (options: {node: string|PixiNodeShape, slot: string, connector: string, text: string}): PixiTagShape;
    deleteConnection (id: string|PixiLineShape): void;
    deleteGroup (id: string|PixiNodeGroup): void;
    deleteNode (id: string|PixiNodeShape): void;
    disconnect (connectionId: string|PixiLineShape): void;
    findConnector (nodeId: string|PixiNodeShape, slotIdOrName: string, connectorTypeOrId?: string): PixiConnectorShape;
    frameAll (targetShapes?: any[]|string[], doNotScale?: boolean, animTransition?: boolean): void;
    frameSelection (onlyIfPartiallyHidden?: boolean, doNotScale?: boolean, animTransition?: boolean): void;
    getCursorEditorCoords (): { x: number, y: number };
    getLineShapeFromId (lineId: string|PixiLineShape): PixiLineShape;
    getNodeGroupFromId (groupId: string|PixiNodeGroup): PixiNodeGroup;
    getNodeShapeFromId (nodeId: string|PixiNodeShape): PixiNodeShape;
    getShapeFromId (id: string | PixiNodeShape | PixiNodeGroup | PixiLineShape): PixiNodeShape | PixiNodeGroup | PixiLineShape;
    createNode (nodeInfo: any): PixiNodeShape;
    createConnection (connectionInfo: any): PixiLineShape;
    createNodeGroup (groupInfo: any): PixiNodeGroup;
    resize (newWidth: number, newHeight: number): void;
    setSlotText (nodeId: string|PixiNodeShape, slotIdOrName: string, text: string): void;
    setSlotValue (nodeId: string|PixiNodeShape, slotIdOrName: string, value: string|number): void;
    zoom (amount: number): void;
    muteEvents: boolean;
    nodeView: PixiNodeView;
}
declare var NodeEditor: NodeEditor;

interface PixiNodeView {
    BorderedRectangle (pWidth: number, pHeight: number, pBorderColor: string, pBackgroundColor: string, pBorderThickness: number, pCornerRadius: number, pCornerParams: any, pBackgroundAlpha: number): BorderedRectangle;
    isLineBeingDrawn (): boolean;
    clearLiveLines (): void;
    isInLiveStateMachineLineState (): boolean;
    endLiveStateMachineLine (target?: any): void;
    cancelSelectionBox (): void;
    cancelSelectionDrag (): void;
    getConnectionEventManager (cem_type): DefaultConnectionEventManager;
    getOwnedLines (pOwner: any, asCopy: boolean): PixiLineShape[];
    registerCanConnectLineFunction (pFunction: (connectorA: PixiConnectorShape, connectorB: PixiConnectorShape) => boolean): void;
    unregisterCanConnectLineFunction (): void;
    allNodes: PixiNodeShape[];
    renderer: any;
    cursorState: PixiCursorState;
    cursorStyle: any;
}
declare var PixiNodeView: PixiNodeView;

interface PixiCursorState {
    getCurrentCursor (): string;
    pushStateOnce (cursorState: string, owner: any): void;
    lockState (owner: any): void;
    removeState (cursorState: string, owner: any): void;
    unlockState (owner: any): void;
}
declare var PixiCursorState: PixiCursorState;

interface PixiBaseShape {
    id: string;
}
declare var PixiBaseShape: PixiBaseShape;

interface PixiNodeShape extends PixiBaseShape {
    new (view: any, options: any): PixiNodeShape;
    addElement (elementDefinition: PixiElementDefinition, index: number): void;
    brief (value?: string): string;
    doLayout (): void;
    hasSlot (slotIdOrName: string): boolean;
    position (pArgs?: {x: number, y: number}, pOffset?: {x: number, y: number}): {x: number, y: number};
    removeElement (element: PixiElementShape): void;
    setState (state: string, addState: boolean): void;
    setError (state: boolean): void;
    setLayoutWidth (width: number): void;
    title (value?: string): string;
    autoLayout: boolean;
    displayState: StateWatcher;
    LOD: any[];
    options: any;
    leftResizeHandle: any;
    rightResizeHandle: any;
}
declare var PixiNodeShape: PixiNodeShape;

interface PixiNodeGroup extends PixiBaseShape {
    new (view: any, pTitle: string, options: any, pChildrenToGroup: any[]): PixiNodeGroup;
    addGroupableChild (pGroupableChild: PixiNodeShape|PixiNodeGroup, pNotify: boolean): boolean;
    removeGroupableChild (pGroupableChild: PixiNodeShape | PixiNodeGroup): void;
    setExpandedMode (state: boolean, disableEvents: boolean): void;
    setState (state: string, addState: boolean): void;
    setTitle (title: string): void;
    container: any;
    expandedContainer: any;
}
declare var PixiNodeGroup: PixiNodeGroup;

interface PixiLineShape extends PixiBaseShape {
    new (view: any, pStartStrategy: any, pEndStrategy: any, options: any, pParentContainer: any, containerIndex: number): PixiLineShape;
    setError (state: boolean): void;
    startStrategy: any;
    endStrategy: any;
}
declare var PixiLineShape: PixiLineShape;

interface PixiElementShape extends PixiBaseShape {

}
declare var PixiElementShape: PixiElementShape;

interface PixiConnectorShape extends PixiBaseShape {
    new (view: any, options: any): PixiConnectorShape;
    displayState: StateWatcher;
    parentNode: PixiNodeShape;
    parentElement: PixiElementShape;
    tag: PixiTagShape;
}
declare var PixiConnectorShape: PixiConnectorShape;

interface DefaultConnectionEventManager {
    new (nodeView: any): DefaultConnectionEventManager;
    insertLiveLine (connector: any, index: number): PixiLineShape;
}
declare var DefaultConnectionEventManager: DefaultConnectionEventManager;

interface PixiStateMachineLine extends PixiBaseShape {
    new (nodeView: any): PixiStateMachineLine;
    setTitle (title: string): void;
    displayState: any;
}
declare var PixiStateMachineLine: PixiStateMachineLine;

interface PixiTagShape extends PixiBaseShape {
    displayState: StateWatcher;
}
declare var PixiTagShape: PixiTagShape;

interface StateWatcher extends EventEmitter {
    applyInheritanceFromColor (color: any, newStateLookup: any): void;
    _applyStateStack (delayBatchCall?: boolean): void;
    pushState (stateName: string, delayBatchCall?: boolean): void;
    removeState (stateName: string, delayBatchCall?: boolean): void;
    stateLookup: any;
    stateStack: string[];
}
declare var StateWatcher: StateWatcher;

interface PixiNodeDefinition {
    title: string;
    brief: string;
    elements: PixiElementDefinition[];
    category: string;
    shape: typeof PixiNodeShape;
}

interface PixiNodeOptions {
    id: string;
    typeDefinition: PixiNodeDefinition;
    nodeStyle: any;
    position: {x: number, y: number};
}

interface PixiElementDefinition {
    name: string;
    id: string;
    interactive: boolean;
    value: string|number;
    type: string;
    allowMultiple: boolean;
    alignment: string;
    inConnector: {color: any};
    outConnector: {color: any};
    bitmap: string;
}

interface BorderedRectangle {
    setPosition (x: number, y: number): void;
}
declare var BorderedRectangle: BorderedRectangle;

declare var isFunction: (f: Function) => boolean;
declare var generateGradient: Function;
declare var clone: Function;
declare var mergeDicts: Function;
