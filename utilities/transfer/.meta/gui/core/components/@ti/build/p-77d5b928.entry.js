import{r as s,g as t}from"./p-84e39b72.js";import{GcPromise as e}from"../gc-core-assets/lib/GcPromise";import{GcUtils as i}from"../gc-core-assets/lib/GcUtils";import{ParentRegistry as a}from"../gc-widget-base/lib/GcWidget";import{G as r}from"./p-37ae55a5.js";import"./p-7b70dbb4.js";import"../gc-core-assets/lib/GcFiles";import"../gc-core-assets/lib/GcConsole";import"../gc-core-assets/lib/GcLocalStorage";import"../gc-widget-message-dialog/lib/GcMessageDialog";let h=class{constructor(t){s(this,t);this.id="";this.series={type:"pie",values:[],labels:[]};this.parentRegistry=new a(r.widgetType);this.childIndex=-1;this.valuesStreamingDataListener=s=>{if(Array.isArray(s[0])){const t=i.transposeMatrix(s);this.series.labels=t[0];this.series.values=t[1];this.fireData()}return};this.deferredWidgetReady=e.defer();this.capacity=200;this.legend="auto"}get sortingOrder(){return a.getChildElementIndex(this.el)}valuesHandler(s){this.valuesStreamingDataListener(s)}showLegendHandler(s){this.restyle({showlegend:s})}legendNameHandler(s){this.restyle({name:s})}fireData(){this.parentRegistry.parent?.replot()}async waitForWidgetReady(){return this.deferredWidgetReady.promise}async restyle(s){if(!this.parentRegistry.parent){r.mergeRecords(r.flattenRecord(s),this.series)}else{this.parentRegistry.parent.restyle(this,s)}}connectedCallback(){this.el["valuesStreamingDataListener"]=this.valuesStreamingDataListener;if(this.deferredWidgetReady.promise.isPending){this.deferredWidgetReady.resolve()}this.id=this.el.id;this.parentRegistry.register(this.el.parentElement,this)}disconnectedCallback(){this.parentRegistry.unregister(this)}async componentWillLoad(){if(this.values){this.valuesStreamingDataListener(this.values)}this.series.name=this.legendName??this.el.id;this.series.showlegend=this.legend==="hide"?false:this.legend==="show"?true:undefined;this.el["series"]=this.series}get el(){return t(this)}static get watchers(){return{values:["valuesHandler"],legend:["showLegendHandler"],legendName:["legendNameHandler"]}}};export{h as gc_widget_plot_data_piechart};
//# sourceMappingURL=p-77d5b928.entry.js.map