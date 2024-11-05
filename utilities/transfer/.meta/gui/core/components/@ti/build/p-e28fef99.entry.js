import{r as t,c as e,h as o,g as r}from"./p-5bb37414.js";import{GcUtils as i}from"../gc-core-assets/lib/GcUtils";import{W as s}from"./p-fbbff519.js";import{W as n}from"./p-efd2e5c1.js";import"../gc-core-assets/lib/GcFiles";import"../gc-core-assets/lib/GcConsole";import"../gc-core-assets/lib/GcLocalStorage";import"../gc-widget-message-dialog/lib/GcMessageDialog";const c=':host::-webkit-scrollbar,::-webkit-scrollbar{width:var(--gc-scrollbar-width, var(--theme-scrollbar-width, 8px));height:var(--gc-scrollbar-width, var(--theme-scrollbar-width, 8px))}:host::-webkit-scrollbar-track,::-webkit-scrollbar-track{background:var(--gc-scrollbar-track-background-color, var(--theme-scroll-track-color, rgba(35, 31, 32, 0.2)))}:host::-webkit-scrollbar-thumb,::-webkit-scrollbar-thumb{background:var(--gc-scrollbar-thumb-background-color, var(--theme-scroll-thumb-color, rgba(35, 31, 32, 0.65)))}:host::-webkit-scrollbar-thumb:hover,::-webkit-scrollbar-thumb:hover{background:var(--gc-scrollbar-thumb-background-color-hover, var(--theme-scroll-thumb-color-hover, rgba(35, 31, 32, 0.8)))}:host::-webkit-scrollbar-corner,::-webkit-scrollbar-corner{background:rgba(0, 0, 0, 0)}:host(:focus),:host *:focus{outline:none}:host{-webkit-user-select:none;-khtml-user-select:none;-moz-user-select:none;-ms-user-select:none;-o-user-select:none;user-select:none;font-family:var(--gc-font-family, var(--theme-font-family, "Roboto", "Open Sans", "Segoe UI", "Tahoma", "sans-serif"));font-size:var(--gc-font-size, var(--theme-font-size, 14px));font-weight:400;color:var(--gc-font-color, var(--gc-font-color, var(--theme-font-color, #555555)));margin:var(--gc-margin, var(--theme-margin, 5px));display:inline-block;box-sizing:border-box}:host .user-select{-webkit-user-select:text;-khtml-user-select:text;-moz-user-select:text;-ms-user-select:text;-o-user-select:text;user-select:text}:host .text-link{color:var(--gc-link-color, var(--gc-link-color, var(--theme-link-color, #333333)));--gc-color:var(--gc-link-color, var(--gc-link-color, var(--theme-link-color, #333333)));--gc-text-decoration-hover:underline;--gc-cursor-hover:pointer}:host .text-link:not([disabled]):hover{text-decoration:underline;cursor:pointer}:host([hidden]){display:none !important}:host([readonly]) *{pointer-events:none}:host([disabled]) *{cursor:not-allowed}:host([caption]:not([caption=""])){margin-top:calc(var(--gc-margin, var(--theme-margin, 5px)) + var(--gc-caption-font-size, var(--theme-caption-font-size, 14px)) + 8px)}:host([caption]:not([caption=""])),:host([info-text]:not([info-text=""])){overflow:visible;position:relative}:host([caption=""][info-text]:not([info-text=""])),:host([info-text]:not([info-text=""]):not([caption])){margin-right:calc(var(--gc-margin, var(--theme-margin, 5px)) + 22px)}#elementWrapper{box-sizing:content-box;height:100%;width:100%;display:flex;align-items:center;min-height:inherit;max-height:inherit;min-width:inherit;max-width:inherit}.root-container{position:relative;display:flex;flex-direction:column;width:100%;height:100%;min-height:inherit;max-height:inherit;min-width:inherit;max-width:inherit}.root-container .header-container.top{top:var(--gc-header-container-top, calc(0px - 8px - var(--gc-caption-font-size, var(--theme-caption-font-size, 14px))));flex-direction:row}.root-container .header-container.side{right:-22px;flex-direction:column;height:inherit}.root-container .header-container{position:absolute;display:flex;align-items:center}.root-container .header-container .icon,.root-container .header-container gc-widget-icon{cursor:default;margin:auto;height:18px;width:18px;display:block;--gc-color:var(--gc-caption-info-color, var(--theme-caption-info-color, #98999b))}.root-container .header-container .caption{flex:1;cursor:default;white-space:nowrap;margin-right:2px;font-weight:var(--gc-caption-font-weight, var(--theme-caption-font-weight, 400));font-size:var(--gc-caption-font-size, var(--theme-caption-font-size, 14px));color:var(--gc-caption-font-color, var(--theme-caption-font-color, #999999))}.invisible{visibility:hidden}:host{height:220px;width:100}:host svg #face-layer #meter-background{fill:var(--gc-meter-background-color, var(--theme-tertiary-color, #63666a))}:host svg #face-layer #meter-internal{fill:var(--gc-meter-internal-color, #cc0000)}:host svg #scale-layer path{stroke:var(--gc-minor-tick-color, #555555)}:host svg #scale-layer path.major{stroke:var(--gc-major-tick-color, #555555)}:host svg #scale-layer text{font-size:var(--gc-label-font-size, 4.75px);fill:var(--gc-font-color, var(--theme-font-color, #555555))}:host svg #label-layer{fill:var(--gc-font-color, var(--theme-font-color, #555555));text-anchor:middle}:host svg #label-layer #main-title{font-size:8px;font-weight:500}:host svg #label-layer #sub-title{font-size:7px}:host svg #label-layer #value{font-size:8px;font-weight:500}:host svg #label-layer #units{font-size:8px;font-weight:500}:host([disabled]) svg #face-layer #meter-background{fill:var(--gc-background-color-disabled, var(--theme-background-color-disabled, #e5e5e5))}:host([disabled]) svg #face-layer #meter-internal{fill:#cccccc}:host([disabled]) svg #label-layer{fill:var(--gc-font-color-disabled, var(--theme-font-color-disabled, #999999))}';let a=class{constructor(o){t(this,o);this.cssPropertyChanged=e(this,"css-property-changed",7);this.base=new class extends s{get thermometer(){return this.parent}get element(){return this.thermometer.el}}(this);this.labels="";this.minorTicks=4;this.units="C";this.hideValue=false;this.value=0;this.minValue=0;this.maxValue=100;this.precision=0;this._refresh=0;this.hidden=false;this.disabled=false}render(){const t=this.createTicks();return n.doRender(o("svg",{width:"100%",height:"100%",viewBox:"0 0 50 110",preserveAspectRatio:"xMidYMid meet"},o("g",{id:"face-layer"},o("g",{id:"meter-background"},o("circle",{cx:"25",cy:"90",r:"10"}),o("rect",{width:"14",height:"60",x:"18",y:"24.5"}),o("path",{d:"M18 25 a7 7 0 0 1 14 0 Z"})),o("g",{id:"meter-internal"},o("circle",{cx:"25",cy:"90",r:"7"}),o("path",{d:this.createMeterPath(this.base.value)}))),o("g",{id:"scale-layer"},t===null||t===void 0?void 0:t.map((t=>[o("path",{class:t.major?"major":undefined,d:t.tick,"stroke-width":t.tickStrokeWidth}),t.label?o("text",{x:t.labelX,y:t.labelY,"text-anchor":t.labelAnchor},t.label):undefined]))),o("g",{id:"label-layer"},o("text",{id:"main-title",x:"25",y:"8"},this.mainTitle),o("text",{id:"sub-title",x:"25",y:"15"},this.subTitle),o("text",{id:"value",x:"25",y:"110"},!this.hideValue?this.base.value.toFixed(this.precision):""),o("text",{id:"units",x:30+2.2*(""+this.base.value.toFixed(this.precision)).length,y:"110"},this.units&&!this.hideValue?"°"+this.units:""))),{caption:this.caption,infoText:this.infoText,tooltip:this.tooltip})}componentWillLoad(){this.onValueChanged()}onValueChanged(){this.setCSSProperty("--gc-meter-internal-color",this.getMeterFillColor())}onCSSPropertyChanged(t){this.setCSSProperty("--gc-meter-internal-color",this.getMeterFillColor());this.setCSSProperty("--gc-label-font-size",this.getFontSize());this.refresh()}getTickProperties(t,e,o,r,i,s){const n="start";let c=.2;let a=6;if(!o){a=2}else{switch(i){case"bold":a=2;c=.9;break;default:a=4}}const l=56.5;const h=25+t/(e-1)*l;const g=32;const d=g;const f=g+a;const m=h;const b=m;return{tick:`M ${d} ${m} L ${f} ${b} z`,tickStrokeWidth:c,major:o,label:o?r:"",labelAnchor:n,labelX:g+4,labelY:h+ +s/3}}trimHexColor(t){return t.charAt(0)==="#"?t.substring(1,7):t}getArcFillColor(){const t=[];const e=this.base.getCSSProperty("--gc-meter-low-color");const o=this.base.getCSSProperty("--gc-meter-mid-color");const r=this.base.getCSSProperty("--gc-meter-high-color");if(e)t.push(e);if(o)t.push(o);if(r)t.push(r);return t}getMeterFillColor(t=true){const e=(this.base.value-this.base.minValue)/(this.base.maxValue-this.base.minValue);const o=this.getArcFillColor();const r=o.length>0?o:["#329b46 ","#f3cd34 ","#dd0000"];const i=r.length;if(i===1)return r[0];const s=t?1/(i-1):1/i;const n=[];for(let e=0;e<i;++e){const o=t?s*e:s*(e+1);const i=parseInt(this.trimHexColor(r[e]).substring(0,2),16);const c=parseInt(this.trimHexColor(r[e]).substring(2,4),16);const a=parseInt(this.trimHexColor(r[e]).substring(4,6),16);n[e]={pct:o,color:{r:i,g:c,b:a}}}if(e===0){return`rgb(${n[0].color.r}, ${n[0].color.g}, ${n[0].color.b})`}for(let o=0;o<n.length;++o){if(e<=n[o].pct){if(t){const t=n[o-1];const r=n[o];const i=r.pct-t.pct;const s=(e-t.pct)/i;const c=1-s;const a=s;const l={r:Math.floor(t.color.r*c+r.color.r*a),g:Math.floor(t.color.g*c+r.color.g*a),b:Math.floor(t.color.b*c+r.color.b*a)};return`rgb(${l.r}, ${l.g}, ${l.b})`}else{return`rgb(${n[o].color.r}, ${n[o].color.g}, ${n[o].color.b})`}}}}getFontSize(){const t=this.base.getCSSProperty("--gc-font-size");switch(t){case"small":return"4.75px";case"medium":return"6px";case"large":return"8px";default:return"4.75px"}}createMeterPath(t){const e=8;const o=21;const r=84.5;const i=56.5;let s=t;if(this.base.minValue===this.base.maxValue){s=s<this.base.minValue?0:1}else if(this.base.minValue>this.base.maxValue){s=Math.max(s,this.base.maxValue);s=Math.min(s,this.base.minValue);s=(this.base.minValue-s)/(this.base.minValue-this.base.maxValue)}else{s=Math.max(s,this.base.minValue);s=Math.min(s,this.base.maxValue);s=(s-this.base.minValue)/(this.base.maxValue-this.base.minValue)}const n=s*i+3;const c=r-n;return`M ${o} ${r} `+`H ${o+e} `+`V ${c} `+`H ${o} Z`}createTicks(){const t=[];const e=this.base.getCSSProperty("--gc-tick-style");const o=+(this.base.getCSSProperty("--gc-label-font-size")||"4.75px").replace(/px/,"");if(this.labels&&this.labels.length>0){const r=i.parseArrayProperty(this.labels);if(r){const i=(r.length-1)*(this.minorTicks+1)+1;let s=false;let n=r[0];let c=0;for(let a=0;a<i;a++){if(a%(this.minorTicks+1)===0){s=true;n=r[c];c++}else{s=false;n=""}t.push(this.getTickProperties(a,i,s,n,e,o))}}}else{if(this.base.minValue!==undefined&&this.base.maxValue!==undefined){const r=+this.base.minValue;const i=+this.base.maxValue;let s=(i-r)*1e3;let n=4;if(s%1===0){const t=[2,3,5,10,100,1e3];for(let e=t.length-1;e>=0;e--){const o=t[e];while(s>o&&s%o===0){s/=o}}if(s>=3&&s<=9||s===2&&(i-r)/s%2!==0){n=s}}const c=n*(this.minorTicks+1)+1;let a=false;let l=""+i;let h=0;for(let s=0;s<c;s++){if(s%(this.minorTicks+1)===0){a=true;l=""+(h*(i-r)/n+r);h++}else{a=false;l=""}t.push(this.getTickProperties(c-s-1,c,a,l,e,o))}}}return t}async setCSSProperty(t,e){e=e.trim();if(await this.getCSSProperty(t)!==e){this.el.style.setProperty(t,e);this.cssPropertyChanged.emit({name:t,value:e})}}async getCSSProperty(t){return getComputedStyle(this.el).getPropertyValue(t).trim()}async refresh(){this._refresh++}get el(){return r(this)}static get watchers(){return{value:["onValueChanged"],minValue:["onValueChanged"],maxValue:["onValueChanged"],precision:["onValueChanged"]}}};a.style=c;export{a as gc_widget_thermometer};
//# sourceMappingURL=p-e28fef99.entry.js.map