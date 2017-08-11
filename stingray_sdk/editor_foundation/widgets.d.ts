type MithrilModel = (newValue?: any) => any;

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

interface WidgetSize {
    w?: number;
    h?: number;
}

type FilterSetter = (value: boolean) => void;

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

// TODO TS: need to be put in the same file as JsonModel
interface IJsonModel {
    duplicateProperty: (path: string, key: string) => void;
    convertProperty: (path: string, type: string) => void;
    deleteProperty: (path: string, key: string | number) => void;
    addProperty: (path: string, value: any) => void;
    renameKey: (oldPath: string, newPath: string) => void;
    commitValue: (path: string, newValue: any, oldValue: any) => any;
    setTransientValue: (path: string, value: any) => any;
    getValue: (path?: string) => any;
    setValue: (path: string, value: any) => any;
}

// TODO TS: need to be put in the same file as ViewModel
interface IViewModel {
    synchronizeModel();
    setView(value: any);
    setModel(value: any);
    rollbackViewValue();
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
    header?: string | ColumnHeaderDesc;
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

// TODO TS: property-vector and property transform must use the ModelSynchronizer exported type?
interface ModelSynchronizer {
    addLockGroup(name: string, isGroupLockAccessor: boolean);
    addModel(key: string, model: WidgetModel, isSelectedAccessor: MithrilModel, lockGroup: string): WidgetModel;
}
