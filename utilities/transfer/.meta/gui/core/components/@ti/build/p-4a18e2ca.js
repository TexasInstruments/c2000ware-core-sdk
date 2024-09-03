/*!
 * © Copyright 1995-2020 Texas Instruments Incorporated. All rights reserved.
 */
class t{static getInstance(){if(!t._INSTANCE){t._INSTANCE=new t}return t._INSTANCE}static async show(i="",n="",s="",e=false){t.getInstance()._getSnackbarElement().show(i,n,s,e)}_getSnackbarElement(){if(this._snackbarElement&&this._snackbarElement.isConnected){return this._snackbarElement}this._snackbarElement=document.querySelector("ti-snackbar");if(this._snackbarElement){return this._snackbarElement}this._snackbarElement=document.createElement("ti-snackbar");document.querySelector("body").appendChild(this._snackbarElement);return this._snackbarElement}}
/*!
 * © Copyright 1995-2020 Texas Instruments Incorporated. All rights reserved.
 */function i(){const i=typeof window!=="undefined"?window:{};if(!i.com){i.com={}}if(!i.com.TI){i.com.TI={}}if(!i.com.TI.SnackbarService){i.com.TI.SnackbarService=t}}const n=i;export{n as g};
//# sourceMappingURL=p-4a18e2ca.js.map