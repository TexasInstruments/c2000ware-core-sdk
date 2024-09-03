## <a id="3.0.0"></a> `gc-widget-dialog` v3.0.0 Change Log
This widget is formally known as `ti-widget-dialog` in GCv2, the tag is renamed to `gc-widget-dialog`.

### Properties Changed
- _**`dialogImage`**_ renamed to `icon`, if set `gc-widget-icon` will be used.
- _**`isModal`**_ renamed to `modal`
- _**`noEscKeyHandling`**_ renamed to `closeOnEsc`, and meaning is reversed (ie: closeOnEsc -allows- esc key handling).
- _**(new) `resizable`**_ boolean to enable resizing of the dialog box.
- _**`dialog-dismiss`**_ attribute to a child button is changed to a class for detection.
- _**`dialog-confirm`**_ attribute to a child button is changed to a class for detection.

### Unsupported Properties
- _**`width`**_ support is deprecated, covered by resizable property
- _**`withBackdrop`**_ wrapped into `modal`
- _**`noCloseOnSubmit`**_ support is deprecated, see the `dialog-close` event
- _**`zIndex`**_ support is deprecated
- _**`noEnterKeyHandling`**_ support is deprecated, use the `dialog-dismiss` and `dialog-confirm` event instead
- _**`helpCallback`**_ support is deprecated