import { QualifierFactoryMap } from './QualifierFactoryMap';
import { AbstractDataFormatter } from './AbstractDataFormatter';
export class DataFormatterRegistry {
    static add(formatter) {
        const CustomDataFormatter = class extends AbstractDataFormatter {
            constructor(operand, precision) {
                super(operand);
                this.precision = precision;
                this.operator = formatter.operator;
                this.formattedType = formatter.formattedType;
                this.unFormattedType = formatter.unFormattedType;
                this.formatValue = formatter.formatValue;
                this.unFormatValue = formatter.unFormatValue;
            }
            static create(bind, param) {
                return new CustomDataFormatter(bind, param);
            }
        };
        QualifierFactoryMap.add(formatter.operator, CustomDataFormatter);
    }
}
//# sourceMappingURL=DataFormatter.js.map