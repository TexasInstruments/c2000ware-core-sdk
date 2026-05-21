//=============================================================================
// export_mod_usb.js - USB Export Module for CDT
//=============================================================================
// Purpose: Expose USB diagnostic information for CDT
// Devices: F2807x, F2837xD, F2837xS, F2838x
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { getDeviceName } = exportCommon;
const deviceName = getDeviceName();

const DEVICES_WITH_USB = [
    "F2807x", "F2837xD", "F2837xS", "F2838x"
];

let exportsInfo = [
    {
        name: "CONNECTED",
        displayName: "USB Connected",
        type: 'led',
        register: "USBPOWER.SOFTCONN",
        updateFunc: (instBase) => `((HWREGB(${instBase} + USB_O_POWER) & USB_POWER_SOFTCONN) == USB_POWER_SOFTCONN)`,
        applicable: (inst) => {
            return DEVICES_WITH_USB.includes(deviceName);
        }
    },
    {
        name: "SUSPEND",
        displayName: "USB Suspended",
        type: 'led',
        register: "USBPOWER.SUSPEND",
        updateFunc: (instBase) => `((HWREGB(${instBase} + USB_O_POWER) & USB_POWER_SUSPEND) == USB_POWER_SUSPEND)`,
        applicable: (inst) => {
            return DEVICES_WITH_USB.includes(deviceName);
        }
    },
    {
        name: "VBUSERR",
        displayName: "VBUS Error",
        type: 'led',
        register: "USBDEVCTL.VBUSERR",
        updateFunc: (instBase) => `((HWREGB(${instBase} + USB_O_DEVCTL) & USB_DEVCTL_VBUSERR) == USB_DEVCTL_VBUSERR)`,
        applicable: (inst) => {
            return DEVICES_WITH_USB.includes(deviceName);
        }
    },
    {
        name: "HOSTMODE",
        displayName: "Host Mode",
        type: 'led',
        register: "USBDEVCTL.HOST",
        updateFunc: (instBase) => `((HWREGB(${instBase} + USB_O_DEVCTL) & USB_DEVCTL_HOST) == USB_DEVCTL_HOST)`,
        applicable: (inst) => {
            return DEVICES_WITH_USB.includes(deviceName);
        }
    },
];

let bitfieldInstanceNames = {
    "default": (instName) => { return "UsbRegs" },
};

let exportsRegisterSkips = [];

exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
