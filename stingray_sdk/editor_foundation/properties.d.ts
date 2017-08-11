interface PropertyMap {
    [key: string]: Property;
}

interface Property {
    childProperties: PropertyMap;
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
    showLabel?: boolean;
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

    order?: number;

    reset?: () => void;

    invokeAction?: () => any;
    trigger?: () => any;

    carouselResourceProperty?: string;

    fetch_options?: any;

    intensityModel?: WidgetModel;

    showAxisLabels?: boolean;

    jsonModel?: IJsonModel;
    jsonPropertyConstructed?: () => void;
    jsonPropertyDestroyed?: () => void;

    getPropertyValue?: (path: string) => any;

    minLabel?: string;
    maxLabel?: string;

    showCustomContentBrowser?: MithrilModel;
    resourceTypes?: string[]; string;
    hasElementSelect?: boolean;
    isClearableEnabled?: boolean;

    document?: any;
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
    invokeMethod(...args): any;
}

interface BackendProperty {
    PropertyDescriptor: BackendPropertyDescriptor;
    ConsensusValue: any;
}

interface BackendPropertyMap {
    [key: string]: BackendProperty;
}

interface PropertyConsensus {
    PropertyDescriptor: BackendPropertyDescriptor;
    ChildProperties: BackendPropertyMap;
    IsReadOnly: boolean;
    ConsensusValue: any;
    isValid(): boolean;
}

interface PropertyCategory {
    label: string;
    properties: Property[];

    childProperties?: PropertyMap;

    path?: string;
    isEnabled?: MithrilModel;
    isChecked?: MithrilModel;
    isCollapsible?: boolean;

    isTransformLayout?: boolean;
    checkModel?: boolean;
}

interface GraphAxis {
    x: number;
    y: number;
}

interface GraphModel {
    synchronizeModel(isInit?: boolean): void;
    insertNode(nodeIndex: number, newNode: any): void;
    removeNode(nodeIndex: number): void;
    setTransientNodePosition(nodeIndex: number, node: any, x: number, y: number): void;
    commitNodePosition(nodeIndex: number, node: any): void;
    refreshGraph: (nodes: any[]) => void;
}

interface CarouselConfig {
    thumbnailSourceProperty: (element) => string;
    displayNameProperty: (element) => string;
}

interface CollectionModel {
    synchronizeModel(): void;
    addElement(elementData?: any, index?: number);
    removeElement(index: number);
    getElements(): any[];
}

interface PropertyTypeGenerator {
    genProperty(model: MithrilModel, rootPath: string, modelType: any);
}

interface PropertyCreatorHelper {
    // Property creators helper functions:
    action(label: string, action: () => void, userArgs?: any): Property;

    bool(label: string, model: MithrilModel, userArgs?: any): Property;

    carousel(label: string, config: CarouselConfig, collectionModel: CollectionModel, userArgs?: any): Property;

    choice(label: string, model: MithrilModel, options: any, userArgs?: any): Property;

    gradient(label: string, collectionModel: CollectionModel, userArgs?: any): Property;

    colorTemperatureSlider(label: string, model: WidgetModel, min: number, max: number, increment: number, userArgs?: any): Property;

    color(label: string, model: WidgetModel, userArgs?: any): Property;

    hdrColor(label: string, model: WidgetModel, intensityModel: WidgetModel, userArgs?: any): Property;

    graph(label: string, graphModel: GraphModel, userAgrs: any): Property;

    number(label: string, model: WidgetModel, userArgs?: any): Property;

    path(label: string, model: MithrilModel, browseType: string, title: string, filter: string, userArgs?: any): Property;
    file(label: string, model: MithrilModel, title: string, filter: string, userArgs?: any): Property;
    directory(label: string, model: MithrilModel, title: string, userArgs?: any): Property;

    range(label: string, minLabel: string, minModel: WidgetModel, maxLabel: string, maxModel: WidgetModel, userArgs?: any): Property;
    range(label: string, minConfig: any, maxConfig: any, userArgs?: any): Property;

    resource(label: string, model: MithrilModel, resourceType: string | string[], userArgs?: any): Property;

    slider(label: string, model: WidgetModel, min: number, max: number, increment: number, userArgs?: any): Property;

    string(label: string, model: MithrilModel, userArgs?: any): Property;

    table(label: string, columns: any[], collectionModel: CollectionModel, userArgs?: any): Property;

    vector2(label: string, model: WidgetModel, userArgs?: any);
    vector2(label: string, userArgs?: any);

    vector3(label: string, model: WidgetModel, userArgs?: any);
    vector3(label: string, userArgs?: any);

    vector4(label: string, model: WidgetModel, userArgs?: any);
    vector4(label: string, userArgs?: any);

    rotation(label: string, model: WidgetModel, userArgs?: any);
    rotation(label: string, userArgs?: any);
}
