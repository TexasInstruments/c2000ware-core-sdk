#ifndef __USBDHIDCUSTOM_H__
#define __USBDHIDCUSTOM_H__
#include <stdint.h>
#include "inc/hw_types.h"
#include "usbdhid.h"

//*****************************************************************************
//
// PRIVATE
//
// This enumeration holds the various states that the Custom can be in during
// normal operation.
//
//*****************************************************************************
typedef enum
{
    //
    // Unconfigured.
    //
    eHIDCustomStateUnconfigured,

    //
    // No keys to send and not waiting on data.
    //
    eHIDCustomStateIdle,

    //
    // Waiting on report data from the host.
    //
    eHIDCustomStateWaitData,

    //
    // Waiting on data to be sent out.
    //
    eHIDCustomStateSend
}
tCustomState;

//*****************************************************************************
//
// PRIVATE
//
// The size of the Custom input report sent to the host.
//
//*****************************************************************************
#define VENDOR_FEATURE              0x85, 0x44,                     \
                                    0x06, 0x00, 0xff,               \
                                    0x09, 0xC5,                     \
                                    0x15, 0x00,                     \
                                    0x26, 0xff, 0x00,               \
                                    0x75, 0x08,                     \
                                    0x96, 0x00,  0x01,              \
                                    0xb1, 0x02

#define MAX_REPORT_SIZE             (256 + 1)

#define FEATURE_REPORT_SIZE         2
#define CUSTOM_REPORT_SIZE          (61 + 1) //13 + Report id
#define CUSTOM_REPORT_BUTTON_SIZE   (1 + 1)  //1 + Report id

#define HID_REPORT_ID               0
#define HID_REPORT_CONTACT_COUNT    1

#define HID_REPORT_FINGER_BASE      2
#define HID_REPORT_FINGER_SIZE      6

#define HID_REPORT_FINGER(x)        ((HID_REPORT_FINGER_BASE + (x * HID_REPORT_FINGER_SIZE)))
//
#define HID_REPORT_FINGER_CONTACT_ID(x)  (0 + HID_REPORT_FINGER(x))
#define HID_REPORT_FINGER_PRESS(x)       (1 + HID_REPORT_FINGER(x))
#define HID_REPORT_FINGER_X_LSB(x)       (2 + HID_REPORT_FINGER(x))
#define HID_REPORT_FINGER_X_MSB(x)       (3 + HID_REPORT_FINGER(x))
#define HID_REPORT_FINGER_Y_LSB(x)       (4 + HID_REPORT_FINGER(x))
#define HID_REPORT_FINGER_Y_MSB(x)       (5 + HID_REPORT_FINGER(x))

#define HID_REPORT_KEY              1

#define HID_REPORT_FEATURE          1

#define HID_REPORT_ID_BUTTON            1
#define HID_REPORT_ID_TOUCH_SCREEN      2
#define HID_REPORT_ID_MAX_CONTACT       3

#define UI16_LSB(x) ((uint8_t)(((uint16_t)x) & 0xFF))
#define UI16_MSB(x) ((uint8_t)((((uint16_t)x) & 0xFF00) >> 8))


//*****************************************************************************
//
//! This return code from USBDHIDMouseStateChange indicates success.
//
//*****************************************************************************
#define CUSTOM_SUCCESS           0

//*****************************************************************************
//
//! This return code from USBDHIDMouseStateChange indicates that an error was
//! reported while attempting to send a report to the host.  A client should
//! assume that the host has disconnected if this return code is seen.
//
//*****************************************************************************
#define CUSTOM_ERR_TX_ERROR      2


//*****************************************************************************
//
//! USBDHIDMouseStateChange returns this value if it is called before the
//! USB host has connected and configured the device.  All mouse state
//! information passed on the call is been ignored.
//
//*****************************************************************************
#define CUSTOM_ERR_NOT_CONFIGURED \
                                4

//*****************************************************************************
//
// PRIVATE
//
// This structure provides the private instance data structure for the USB
// HID Custom device.  This structure forms the RAM workspace used by each
// instance of the Custom.
//
//*****************************************************************************
typedef struct
{
    //
    // The USB configuration number set by the host or 0 of the device is
    // currently unconfigured.
    //
    uint8_t ui8USBConfigured;

    //
    // The protocol requested by the host, USB_HID_PROTOCOL_BOOT or
    // USB_HID_PROTOCOL_REPORT.
    //
    uint8_t ui8Protocol;

    //
    // A buffer used to hold the last input report sent to the host.
    //
    uint8_t pui8Report[MAX_REPORT_SIZE];

    //
    // The current state of the Custom interrupt IN endpoint.
    //
    volatile tCustomState iCustomState;

    //
    // The idle timeout control structure for our input report.  This is
    // required by the lower level HID driver.
    //
    tHIDReportIdle sReportIdle;

    //
    // This is needed for the lower level HID driver.
    //
    tUSBDHIDDevice sHIDDevice;
}
tHIDCustomInstance;

//*****************************************************************************
//
//! This structure is used by the application to define operating parameters
//! for the HID Custom device.
//
//*****************************************************************************
typedef struct
{
    //
    //! The vendor ID that this device is to present in the device descriptor.
    //
    const uint16_t ui16VID;

    //
    //! The product ID that this device is to present in the device descriptor.
    //
    const uint16_t ui16PID;

    //
    //! The maximum power consumption of the device, expressed in milliamps.
    //
    const uint16_t ui16MaxPowermA;

    //
    //! Indicates whether the device is self- or bus-powered and whether or not
    //! it supports remote wakeup.  Valid values are USB_CONF_ATTR_SELF_PWR or
    //! USB_CONF_ATTR_BUS_PWR, optionally ORed with USB_CONF_ATTR_RWAKE.
    //
    const uint8_t ui8PwrAttributes;

    //
    //! A pointer to the callback function which is called to notify
    //! the application of events relating to the operation of the Custom.
    //
    const tUSBCallback pfnCallback;

    //
    //! A client-supplied pointer which is sent as the first
    //! parameter in all calls made to the Custom callback, pfnCallback.
    //
    void *pvCBData;

    //
    //! A pointer to the string descriptor array for this device.  This array
    //! must contain the following string descriptor pointers in this order.
    //! Language descriptor, Manufacturer name string (language 1), Product
    //! name string (language 1), Serial number string (language 1),HID
    //! Interface description string (language 1), Configuration description
    //! string (language 1).
    //!
    //! If supporting more than 1 language, the descriptor block (except for
    //! string descriptor 0) must be repeated for each language defined in the
    //! language descriptor.
    //
    const uint8_t * const *ppui8StringDescriptors;

    //
    //! The number of descriptors provided in the ppStringDescriptors
    //! array.  This must be (1 + (5 * (num languages))).
    //
    const uint32_t ui32NumStringDescriptors;

    //
    //! The private instance data for this device.  This memory must
    //! remain accessible for as long as the Custom device is in use and must
    //! not be modified by any code outside the HID Custom driver.
    //
    tHIDCustomInstance sPrivateData;
}
tUSBDHIDCustomDevice;

typedef struct {
    uint8_t press;
    uint16_t x;
    uint16_t y;
}tUSBHIDCustomTouchFinger;

typedef struct {
    uint8_t press_count;
    tUSBHIDCustomTouchFinger fingers[10];
}tUSBHIDCustomTouchEvent;

void *
USBDHIDCustomCompositeInit(uint32_t ui32Index,
                          tUSBDHIDCustomDevice *psCustomDevice,
                          tCompositeEntry *psCompEntry);

uint32_t
USBDHIDCustomPointStateChange(void *pvMouseDevice, uint16_t ui16DeltaX, uint16_t ui16DeltaY);

uint32_t
USBDHIDCustomReportFeature(void *pvMouseDevice);

uint32_t
USBDHIDCustomTouchEvent(void *pvMouseDevice, tUSBHIDCustomTouchEvent *psEvent);

uint32_t
USBDHIDCustomReportKey(void *pvMouseDevice, uint8_t ui8Key);

#endif
