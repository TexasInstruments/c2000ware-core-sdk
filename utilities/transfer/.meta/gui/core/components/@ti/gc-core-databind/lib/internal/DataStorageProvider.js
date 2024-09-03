export class DataStorageProvider {
    static addDataModel(dataProvider) {
        this.dataModels.set(dataProvider.id, dataProvider);
    }
    static removeDataModel(dataProvider) {
        this.dataModels.delete(dataProvider.id);
    }
    static readDataForSave() {
        const data = {};
        this.dataModels.forEach((dataProvider, providerName) => {
            data[providerName] = this.readData(dataProvider);
        });
        return data;
    }
    static writeDataForLoad(data) {
        this.dataModels.forEach((dataProvider, providerName) => {
            const modelData = data[providerName];
            if (modelData) {
                this.writeData(dataProvider, modelData);
            }
        });
    }
    static readData(model) {
        const data = {};
        model.getAllBindings().forEach((bind, bindName) => {
            if (bind && !bind.readOnly && !bind.excludeFromStorageProviderData) {
                data[bindName] = bind.getValue();
            }
        });
        return data;
    }
    static writeData(model, data) {
        for (const bindName in data) {
            // eslint-disable-next-line no-prototype-builtins
            if (data.hasOwnProperty(bindName)) {
                const bind = model.getAllBindings().get(bindName);
                if (bind) {
                    bind.setValue(data[bindName]);
                }
            }
        }
    }
}
DataStorageProvider.dataModels = new Map();
//# sourceMappingURL=DataStorageProvider.js.map