import{r as e,g as s}from"./p-ce1dc307.js";import{RegisterModel as t}from"../gc-model-register/lib/RegisterModel";import{c as i}from"./p-0c6e1a4c.js";let c=class{constructor(s){e(this,s);this.impl=undefined;this.ignoreWriteOperationsWhenDisconnected=false;this.optional=false;this.defaultRefreshInterval=100;this.isDeviceArray=false}async setSymbols(e){this.impl.setSymbols(e)}connectedCallback(){this.impl=new t(i(this.el))}disconnectedCallback(){this.impl.dispose()}onDeviceIdChanged(e,s){this.impl.onDeviceChanged()}get el(){return s(this)}static get watchers(){return{deviceId:["onDeviceIdChanged"]}}};export{c as gc_model_register};
//# sourceMappingURL=p-c3551374.entry.js.map