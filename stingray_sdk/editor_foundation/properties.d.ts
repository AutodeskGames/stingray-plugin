interface Property {
    childProperties: Property[];
    $i: number;
    label: string;
    displayType: string;
    path: string;

    title?: string;
    placeholder?: string;

    control?: string;

    consensusProperty?: PropertyConsensus;

    model?: WidgetModel;
    collectionModel?: CollectionModel;
    graphModel?: GraphModel;

    isMultiEditSupported?: boolean;
    isMultiline?: boolean;
    dictKey?: string;
    suffixLabel?: string;
    iconName?: string;
    description?: string;
    showValue?: boolean;
    isReadOnly?: boolean;
    isResettable?: boolean;

    min?: number;
    max?: number;
    increment?: number;

    elementType?: string;
    resourceType?: string;
    hasResourceSelect?: boolean;
    hasResourceCallback?: boolean;
    typeResourceName?: string;

    browseTitle?: string;
    browseFilter?: string;
    browseType?: string;

    lineRows?: string;

    data?: any;

    columnPropertyDescriptors?: any[];

    defaultValueName?: string;
    defaultValue?: string;

    case_labels?: any;

    config?: any;

    supportedExtension?: string;

    options?: any;

    typeDesc?: any;
    childType?: any;

    rootProperty?: PropertyNotifier;

    columns?: any[];

    supportsLock?: boolean;
}

interface PropertyNotifier extends Property, EventSource {

}

interface BackendGraphAxisDesc {
    X: number;
    Y: number;
}

interface BackendPropertyDescriptor {
    $i: number;
    Category: PropertyCategory;
    DisplayType: string;
    IsMultiEditSupported: boolean;
    IsMultiline: boolean;
    Description: string;
    HasMin: boolean;
    Min: number;
    HasMax: boolean;
    Max: number;
    Increment: number;
    ElementType: string;
    ResourceType: string;
    BrowseTitle: string;
    BrowseFilter: string;
    BrowseType: string;
    DictKey: string;
    SuffixLabel; string;
    IconName: string;
    LineRows: number;
    ShowValue: boolean;
    Data: any;
    ColumnPropertyDescriptors: any[];
    HasResourceSelect: boolean;
    HasResourceCallback: boolean;
    DefaultValueName: string;
    DefaultValue: string;
    IsReadOnly: boolean;
    InvalidData: boolean;
    OnChangeNotifier: any;
    MaxElements: any;
    AxesMin: BackendGraphAxisDesc;
    AxesMax: BackendGraphAxisDesc;
    LabelX: string;
    LabelY: string;
    InfinitePositiveY: number;
    Label: string;
}

interface BackendProperty {
    PropertyDescriptor: BackendPropertyDescriptor;
    ConsensusValue: any;
}

interface PropertyConsensus {
    PropertyDescriptor: BackendPropertyDescriptor;
    ChildProperties: BackendProperty[];
    IsReadOnly: boolean;
}

interface PropertyCategory {

}

interface CreatePropertyFunctor {
    (property: Property, propertyPath: string, propertyDocument: PropertyDocument): any;
}

// TODO: temporary for now. When implement property-editor-utils as a proper namespace
// we can have each properties inject its property creator in the namespace.
declare module 'properties/property-editor-utils' {
    function generateCategories(categories: PropertyCategory[], catType: string, propertyDocument: PropertyDocument) : any;
    function generateCategory(category: PropertyCategory, categoryKey: string, catType: string, propertyDocument: PropertyDocument): any;
    function generatePropertyContainer(property: Property, propertyPath: string, propertyDocument: PropertyDocument);
    function generateAdskProperty(property: Property, propertyPath: string, propertyDocument: PropertyDocument);
    function generateProperty(property: Property, propertyPath: string, propertyDocument: PropertyDocument);

    function registerPropertyComponent(displayTypes: string | string[], creationFunctor: CreatePropertyFunctor, metaData: any);
    function registerContainerMenu(property: Property);
    function registerPropertyHelper(propertyId: string, propertyCreator: () => Property);

    function iterateCategoryProperties(category: PropertyCategory, transformer: any);
    function iteratePropertyTree(property: Property, transformer: any, parentPath: string, propertyKEy?: string);

    function category(label: string, args: any, properties: Property[]) : PropertyCategory;
    function defaultProperty(propArgs: any, userArgs: any) : Property;
    function property(label: string, propArgs: any, userAgrs: any) : Property;

    // Property creators helper functions:
    function action(label: string, action: () => void, userArgs: any): Property;

    function bool(label: string, model: WidgetModel, userArgs: any): Property;

    function carousel(label: string, config: CarouselConfig, collectionModel: CollectionModel, userArgs: any): Property;

    function choice(label: string, model: MithrilModel, options: any, userArgs: any): Property;

    function gradient(label: string, collectionModel: CollectionModel, userArgs: any): Property;

    function colorTemperatureSlider(label: string, model: WidgetModel, min: number, max: number, increment: number, userArgs: any): Property;

    function color(label:string, model:WidgetModel, userArgs:any) : Property;

    function hdrColor(label: string, model: WidgetModel, intensityModel:WidgetModel, userArgs: any): Property;

    function graph(label: string, graphModel: GraphModel, userAgrs: any) : Property

    function number(label: string, model: WidgetModel, userArgs: any) : Property;

    function path(label: string, model: MithrilModel, browseType: string, title: string, filter: string, userArgs: any): Property;
    function file(label: string, model: MithrilModel, title: string, filter: string, userArgs: any): Property;
    function directory(label: string, model: MithrilModel, title: string, userArgs: any): Property;

    function range(label: string, minLabel: string, minModel: WidgetModel, maxLabel: string, maxModel: WidgetModel, userArgs: any): Property;
    function range(label: string, minConfig: any, maxConfig: any, userArgs: any): Property;

    function slider(label: string, model: WidgetModel, min: number, max: number, increment: number, userArgs: any): Property;

    function string(label: string, model: MithrilModel, userArgs: any): Property;

    function table(label: string, columns: any[], collectionModel: CollectionModel, userArgs: any) : Property;
}

interface GraphAxis {
    x: number;
    y: number;
}

interface GraphModel {
    synchronizeModel(isInit?: boolean) : void;
    insertNode(nodeIndex: number, newNode: any) : void;
    removeNode(nodeIndex: number) : void;
    setTransientNodePosition(nodeIndex: number, node: any, x: number, y: number) : void;
    commitNodePosition(nodeIndex: number, node: any) : void;
    refreshGraph: (nodes: any[]) => void;
}

interface CarouselConfig {
    thumbnailSourceProperty: (element) => string;
    displayNameProperty: (element) => string;
}

interface CollectionModel {
    synchronizeModel() : void;
    addElement(elementData?: any, index?: number);
    removeElement(index: number);
    getElements() : any[];
}

interface PropertyDocument {
    groupEditing(commandName: string, groupEditingFunctor: () => void);
    getSettings(keys: string[], defaultValue?: any);
}

interface PropertyTypeGenerator {
    genProperty(model: MithrilModel, rootPath: string, modelType: any);
}
