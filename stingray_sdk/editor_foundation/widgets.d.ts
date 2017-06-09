interface MithrilModel {
    (newValue?: any): any;
}

interface WidgetModel extends MithrilModel {
    setTransientValue(newValue: any): any;
    commitValue(newValue: any, oldValue: any): any;
}

interface NumberModel extends WidgetModel {
    getValidValue: (value: number) => number;
    min: number;
    max: number;
    nbDecimal: number;
}

interface AccordionDesc {
    title: string;
    isExpanded: boolean;
    collapsible?: boolean;
    content: object;
    checkbox: any;
}

interface CheckboxDesc {
    model: WidgetModel;
    id: string;
    disabled: boolean;
    title: string;
    trueValue: any;
}

interface ChoiceDesc {
    model: WidgetModel;
    getOptions(): any;
    id?: string;
    disabled?: boolean;
    required?: boolean;
    multiple?: boolean;
    defaultValue?: string;
    defaultValueName?: string;
    size?: number;
    emptyMessage?: string;
    useDictValueForLabel?: boolean;
    invalid?: boolean;
    name?: string;
}

interface ColorGradientDesc {
    collectionModel: any;
    disabled?: boolean;
}

interface WidgetSize {
    w: number;
    h: number;
}

interface TempSliderDesc {
    model: WidgetModel;
    numberModel: NumberModel;
    min?: number;
    max?: number;
    step?: number;
}

interface ColorDesc {
    model: WidgetModel;
    isHdr: boolean;
    customStyle?: string;
    size?: WidgetSize;
    disabled?: boolean;
}

interface FilterSetter {
    (value: boolean): void;
}

interface FilterDesc {
    label: string;
    id: string | number;
    model?: WidgetModel;
    value: boolean;
}

interface FilterViewDesc {
    title: string;
    onValueChanged: (labels, ids, enabled, filters) => void;
    filters: FilterDesc[];
}

interface GraphDirectionDesc {
    num: number;
    delta: number;
}

interface MousePos {
    x: number;
    y: number;
}

interface GraphDesc {
    graphModel: any;

}

interface ToolbarItem {
    img: string;
    title: string;
    separator?: boolean;
    empty_space?: boolean;
    class?: string;
    component?: any;
    enabled?: () => boolean;
    action?: () => void;
}

interface ToolbarDesc {
    items: ToolbarItem[];
}

interface JsonComponentDesc {
    jsonModel?: IJsonModel;
    jsonObj?: any;
    defaultCollapsed?: boolean;
    nbDecimals?: number;
    supportsKeyEditing?: boolean;
}

interface IJsonModel {
    duplicateProperty: (path: string, key: string) => void;
    convertProperty: (path: string, type: string) => void;
    deleteProperty: (path: string, key: string | number) => void;
    addProperty: (path: string, value: any) => void;
    renameKey: (oldPath: string, newPath: string) => void;
    commitValue: (path: string, newValue: any, oldValue: any) => any;
    setTransientValue: (path: string, value: any) => any;
    getValue: (path: string) => any;
    setValue: (path: string, value: any) => any;
}

interface ColumnDesc {
    property: string;
    uniqueId: string;
    dataType?: any;
    displayProperty?: string;
    tooltipProperty?: string;
    type?: string;
    defaultWidth?: number;
    image?: string;
    tooltip?: string;
    hidden?: boolean;
    sortable?: boolean;
    editable?: boolean;
    disabled?: boolean | (() => boolean);
    rightToLeftOverflow?: boolean;
    editableRejectedCharacters?: string;
    format?: any;
    onClick?: any;
    onChange?: any;
    header?: string | ColumnHeaderDesc
    condition?: ColumnConditionDef;
}

interface ColumnHeaderDesc {
    text?: string;
    tooltip?: string;
    image?: string;
    faIcon?: string;
    hideCheckbox?: boolean;
}

interface BadgeDesc {
    property: string;
    position: string;
    tooltip?: string;
    faIcon?: string;
    image?: string;
    customClass?: string;
    format: any;
}

interface ColumnConditionDef {
    property: string;
    tooltip?: string;
    faIcon?: string;
    image?: string;
}

interface SortDef {
    property: string;
    uniqueId: string;
    reverse?: boolean;
    caseSensitive?: boolean;
}

interface PathDesc {
    model: WidgetModel;
    browseType: string;
    browseTitle: string;
    browseFilter: string;
    isReadOnly: boolean;
    hasResourceSelect?: boolean;
    isRightToLeft?: boolean;
    suffixLabel?: string;
    placeholder: MithrilModel | string;
    clearable?: boolean;
}

interface ResourceDesc {
    model: WidgetModel;
    resourceTypes: string[]; string;
    defaultValue: string;
    placeholder: string | MithrilModel;
    resourceType: string | string[];
    hasResourceSelect: boolean;
    hasElementSelect: boolean;
    suffixLabel?: string;
    isReadOnly?: boolean;
    isInvalid?: boolean;
    isClearableEnabled?: boolean;
    showCustomContentBrowser?: any;
    disallowedResourceNames?: string[];
    title: string;
}

interface SliderDesc {
    numberModel?: NumberModel;
    model?: WidgetModel;
    min?: number;
    max?: number;
    decimal?: number;
    step?: number;
    disabled?: boolean;
    showLabel?: boolean;
    label?: string;
    placeholder?: string;
}

interface SpinnerDesc {
    numberModel?: NumberModel;
    model?: WidgetModel;
    defaultValue?: number;
    min?: number;
    max?: number;
    decimal?: number;
    increment?: number;
    disabled?: boolean;
    showLabel?: boolean;
    label?: string;
    placeholder?: string;
    readOnly?: boolean;
    invalid?: boolean;
    onCommitValue: any;
    onmousedown: any;
    onmouseup: any;
    onmousemove: any;
    backgroundHighlight: any;
    textHighlight: any;
    selectOnClick: any;
}

interface TextboxDesc {
    numberModel?: NumberModel;
    model?: WidgetModel;
    title?: string;
    disabled?: boolean;
    readOnly?: boolean;
    placeholder?: string;
    inputType?: string;
    min?: number;
    max?: number;
    increment?: number;
    step?: number;
    textHighlight?: () => boolean;
    backgroundHighlight?: () => boolean;
    onCommitValue?: (newValue, oldValue) => void;
    onclick?: (event) => void;
    onfocus?: (event) => void;
    onblur?: (event) => void;
    triggerCharacters?: any;
    rejectedCharacters?: any;
    liveUpdate?: boolean;
    focusMe?: boolean;
    config?: Function;
    dropConfig?: any;
    rightToLeftOverflow?: boolean;
    clearable?: boolean;
    invalid?: boolean;
    lineRows?: string;
    multiLines?: boolean;
    class?: string;
    onmousedown?: (event) => void;
    onmousemove?: (event) => void;
    onmouseup?: (event) => void;
    selectOnClick?: boolean;
    clearableClass?: string;
    onClear?: () => void;
}

interface TypeAheadDesc {
    model: MithrilModel;
    choices: any;
    caseSensitive?: boolean;
    getLabel?: (choice) => string;
    getTitle?: (choice) => string;
    rows?: number;
}

interface ModelSynchronizer {
    addLockGroup(name: string, isGroupLockAccessor: boolean);
    addModel(key: string, model: WidgetModel, isSelectedAccessor: MithrilModel, lockGroup: string) : WidgetModel;
}
