
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_types.h"
#include "debug.h"
#include "usb.h"
#include "include/usblib.h"
#include "include/usblibpriv.h"
#include "include/device/usbdevice.h"
#include "include/usbhid.h"
#include "include/device/usbdhid.h"
#include "include/device/usbdhidcustom.h"

//*****************************************************************************
//
// HID device configuration descriptor.
//
// It is vital that the configuration descriptor bConfigurationValue field
// (byte 6) is 1 for the first configuration and increments by 1 for each
// additional configuration defined here.  This relationship is assumed in the
// device stack for simplicity even though the USB 2.0 specification imposes
// no such restriction on the bConfigurationValue values.
//
// Note that this structure is deliberately located in RAM since we need to
// be able to patch some values in it based on client requirements.
//
//*****************************************************************************
static uint8_t g_pui8CustomDescriptor[] =
{
    //
    // Configuration descriptor header.
    //
    9,                          // Size of the configuration descriptor.
    USB_DTYPE_CONFIGURATION,    // Type of this descriptor.
    USBShort(34),               // The total size of this full structure.
    1,                          // The number of interfaces in this
                                // configuration.
    1,                          // The unique value for this configuration.
    5,                          // The string identifier that describes this
                                // configuration.
    USB_CONF_ATTR_SELF_PWR,     // Bus Powered, Self Powered, remote wake up.
    250,                        // The maximum power in 2mA increments.
};

//*****************************************************************************
//
// The remainder of the configuration descriptor is stored in flash since we
// don't need to modify anything in it at runtime.
//
//*****************************************************************************
static uint8_t g_pui8HIDInterface[HIDINTERFACE_SIZE] =
{
    //
    // HID Device Class Interface Descriptor.
    //
    9,                          // Size of the interface descriptor.
    USB_DTYPE_INTERFACE,        // Type of this descriptor.
    0,                          // The index for this interface.
    0,                          // The alternate setting for this interface.
    1,                          // The number of endpoints used by this
                                // interface.
    USB_CLASS_HID,              // The interface class
    USB_HID_SCLASS_NONE,        // The interface sub-class.
    USB_HID_PROTOCOL_NONE,     // The interface protocol for the sub-class
                                // specified above.
    4,                          // The string index for this interface.
};

static const uint8_t g_pui8HIDInEndpoint[HIDINENDPOINT_SIZE] =
{
    //
    // Interrupt IN endpoint descriptor
    //
    7,                          // The size of the endpoint descriptor.
    USB_DTYPE_ENDPOINT,         // Descriptor type is an endpoint.
    USB_EP_DESC_IN | USBEPToIndex(USB_EP_1),
    USB_EP_ATTR_INT,            // Endpoint is an interrupt endpoint.
    USBShort(USBFIFOSizeToBytes(USB_FIFO_SZ_64)),
                                // The maximum packet size.
    16,                         // The polling interval for this endpoint.
};

//*****************************************************************************
//
// The report descriptor for the Custom class device.
//
//*****************************************************************************
static const uint8_t g_pui8CustomReportDescriptor[] =
{
     UsagePage(USB_HID_GENERIC_DESKTOP),
     Usage(USB_HID_KEYBOARD),
     Collection(USB_HID_APPLICATION),
         UsagePage(USB_HID_KEYPAD),
         ReportID(HID_REPORT_ID_BUTTON),

         UsageMinimum(HID_KEYB_USAGE_1),
         UsageMaximum(HID_KEYB_USAGE_8),
         LogicalMinimum(0),
         LogicalMaximum(1),

         ReportSize(1),
         ReportCount(8),
         Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),
     EndCollection,

     // Touch screen (2 Point)
     UsagePage(USB_HID_DIGITIZERS),
     Usage(USB_HID_TOUCH_SCREEN),
     Collection(USB_HID_APPLICATION),
         ReportID(HID_REPORT_ID_TOUCH_SCREEN),
         Usage(USB_HID_CONTACT_COUNT),
         LogicalMinimum(0),
         LogicalMaximum(10),
         ReportSize(8),
         ReportCount(1),
         Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),

         // Point 1
         UsagePage(USB_HID_DIGITIZERS),
         Usage(USB_HID_FINGER),
         Collection(USB_HID_LOGICAL),
             Usage(USB_HID_CONTACT_ID),
             LogicalMinimum(0),
             LogicalMaximum(9),
             ReportSize(8),
             ReportCount(1),
             Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),

             Usage(USB_HID_TOUCH_PRESS),
             LogicalMinimum(0),
             LogicalMaximum(1),
             ReportSize(1),
             ReportCount(1),
             Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),

             ReportSize(7),  // Pad to 1byte
             ReportCount(1),
             Input(USB_HID_INPUT_CONSTANT | USB_HID_INPUT_ARRAY | USB_HID_INPUT_ABS),

             UsagePage(USB_HID_GENERIC_DESKTOP),
             Usage(USB_HID_X),
             LogicalMinimum(0),
             LogicalUi16Maximum(4095),
             ReportSize(16),
             ReportCount(1),
             Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),

             Usage(USB_HID_Y),
             LogicalMinimum(0),
             LogicalUi16Maximum(4095),
             ReportSize(16),
             ReportCount(1),
             Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),
         EndCollection,

         // Point 2
         UsagePage(USB_HID_DIGITIZERS),
         Usage(USB_HID_FINGER),
         Collection(USB_HID_LOGICAL),
             Usage(USB_HID_CONTACT_ID),
             LogicalMinimum(0),
             LogicalMaximum(9),
             ReportSize(8),
             ReportCount(1),
             Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),

             Usage(USB_HID_TOUCH_PRESS),
             LogicalMinimum(0),
             LogicalMaximum(1),
             ReportSize(1),
             ReportCount(1),
             Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),

             ReportSize(7),  // Pad to 1byte
             ReportCount(1),
             Input(USB_HID_INPUT_CONSTANT | USB_HID_INPUT_ARRAY | USB_HID_INPUT_ABS),

             UsagePage(USB_HID_GENERIC_DESKTOP),
             Usage(USB_HID_X),
             LogicalMinimum(0),
             LogicalUi16Maximum(4095),
             ReportSize(16),
             ReportCount(1),
             Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),

             Usage(USB_HID_Y),
             LogicalMinimum(0),
             LogicalUi16Maximum(4095),
             ReportSize(16),
             ReportCount(1),
             Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),
         EndCollection,

         // Point 3
          UsagePage(USB_HID_DIGITIZERS),
          Usage(USB_HID_FINGER),
          Collection(USB_HID_LOGICAL),
              Usage(USB_HID_CONTACT_ID),
              LogicalMinimum(0),
              LogicalMaximum(9),
              ReportSize(8),
              ReportCount(1),
              Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),

              Usage(USB_HID_TOUCH_PRESS),
              LogicalMinimum(0),
              LogicalMaximum(1),
              ReportSize(1),
              ReportCount(1),
              Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),

              ReportSize(7),  // Pad to 1byte
              ReportCount(1),
              Input(USB_HID_INPUT_CONSTANT | USB_HID_INPUT_ARRAY | USB_HID_INPUT_ABS),

              UsagePage(USB_HID_GENERIC_DESKTOP),
              Usage(USB_HID_X),
              LogicalMinimum(0),
              LogicalUi16Maximum(4095),
              ReportSize(16),
              ReportCount(1),
              Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),

              Usage(USB_HID_Y),
              LogicalMinimum(0),
              LogicalUi16Maximum(4095),
              ReportSize(16),
              ReportCount(1),
              Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),
          EndCollection,

            // Point 4
            UsagePage(USB_HID_DIGITIZERS),
            Usage(USB_HID_FINGER),
            Collection(USB_HID_LOGICAL),
               Usage(USB_HID_CONTACT_ID),
               LogicalMinimum(0),
               LogicalMaximum(9),
               ReportSize(8),
               ReportCount(1),
               Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),

               Usage(USB_HID_TOUCH_PRESS),
               LogicalMinimum(0),
               LogicalMaximum(1),
               ReportSize(1),
               ReportCount(1),
               Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),

               ReportSize(7),  // Pad to 1byte
               ReportCount(1),
               Input(USB_HID_INPUT_CONSTANT | USB_HID_INPUT_ARRAY | USB_HID_INPUT_ABS),

               UsagePage(USB_HID_GENERIC_DESKTOP),
               Usage(USB_HID_X),
               LogicalMinimum(0),
               LogicalUi16Maximum(4095),
               ReportSize(16),
               ReportCount(1),
               Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),

               Usage(USB_HID_Y),
               LogicalMinimum(0),
               LogicalUi16Maximum(4095),
               ReportSize(16),
               ReportCount(1),
               Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),
            EndCollection,


            // Point 5
            UsagePage(USB_HID_DIGITIZERS),
            Usage(USB_HID_FINGER),
            Collection(USB_HID_LOGICAL),
               Usage(USB_HID_CONTACT_ID),
               LogicalMinimum(0),
               LogicalMaximum(9),
               ReportSize(8),
               ReportCount(1),
               Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),

               Usage(USB_HID_TOUCH_PRESS),
               LogicalMinimum(0),
               LogicalMaximum(1),
               ReportSize(1),
               ReportCount(1),
               Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),

               ReportSize(7),  // Pad to 1byte
               ReportCount(1),
               Input(USB_HID_INPUT_CONSTANT | USB_HID_INPUT_ARRAY | USB_HID_INPUT_ABS),

               UsagePage(USB_HID_GENERIC_DESKTOP),
               Usage(USB_HID_X),
               LogicalMinimum(0),
               LogicalUi16Maximum(4095),
               ReportSize(16),
               ReportCount(1),
               Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),

               Usage(USB_HID_Y),
               LogicalMinimum(0),
               LogicalUi16Maximum(4095),
               ReportSize(16),
               ReportCount(1),
               Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),
            EndCollection,


            // Point 6
            UsagePage(USB_HID_DIGITIZERS),
            Usage(USB_HID_FINGER),
            Collection(USB_HID_LOGICAL),
               Usage(USB_HID_CONTACT_ID),
               LogicalMinimum(0),
               LogicalMaximum(9),
               ReportSize(8),
               ReportCount(1),
               Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),

               Usage(USB_HID_TOUCH_PRESS),
               LogicalMinimum(0),
               LogicalMaximum(1),
               ReportSize(1),
               ReportCount(1),
               Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),

               ReportSize(7),  // Pad to 1byte
               ReportCount(1),
               Input(USB_HID_INPUT_CONSTANT | USB_HID_INPUT_ARRAY | USB_HID_INPUT_ABS),

               UsagePage(USB_HID_GENERIC_DESKTOP),
               Usage(USB_HID_X),
               LogicalMinimum(0),
               LogicalUi16Maximum(4095),
               ReportSize(16),
               ReportCount(1),
               Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),

               Usage(USB_HID_Y),
               LogicalMinimum(0),
               LogicalUi16Maximum(4095),
               ReportSize(16),
               ReportCount(1),
               Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),
            EndCollection,

            // Point 7
            UsagePage(USB_HID_DIGITIZERS),
            Usage(USB_HID_FINGER),
            Collection(USB_HID_LOGICAL),
               Usage(USB_HID_CONTACT_ID),
               LogicalMinimum(0),
               LogicalMaximum(9),
               ReportSize(8),
               ReportCount(1),
               Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),

               Usage(USB_HID_TOUCH_PRESS),
               LogicalMinimum(0),
               LogicalMaximum(1),
               ReportSize(1),
               ReportCount(1),
               Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),

               ReportSize(7),  // Pad to 1byte
               ReportCount(1),
               Input(USB_HID_INPUT_CONSTANT | USB_HID_INPUT_ARRAY | USB_HID_INPUT_ABS),

               UsagePage(USB_HID_GENERIC_DESKTOP),
               Usage(USB_HID_X),
               LogicalMinimum(0),
               LogicalUi16Maximum(4095),
               ReportSize(16),
               ReportCount(1),
               Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),

               Usage(USB_HID_Y),
               LogicalMinimum(0),
               LogicalUi16Maximum(4095),
               ReportSize(16),
               ReportCount(1),
               Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),
            EndCollection,

            // Point 8
            UsagePage(USB_HID_DIGITIZERS),
            Usage(USB_HID_FINGER),
            Collection(USB_HID_LOGICAL),
               Usage(USB_HID_CONTACT_ID),
               LogicalMinimum(0),
               LogicalMaximum(9),
               ReportSize(8),
               ReportCount(1),
               Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),

               Usage(USB_HID_TOUCH_PRESS),
               LogicalMinimum(0),
               LogicalMaximum(1),
               ReportSize(1),
               ReportCount(1),
               Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),

               ReportSize(7),  // Pad to 1byte
               ReportCount(1),
               Input(USB_HID_INPUT_CONSTANT | USB_HID_INPUT_ARRAY | USB_HID_INPUT_ABS),

               UsagePage(USB_HID_GENERIC_DESKTOP),
               Usage(USB_HID_X),
               LogicalMinimum(0),
               LogicalUi16Maximum(4095),
               ReportSize(16),
               ReportCount(1),
               Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),

               Usage(USB_HID_Y),
               LogicalMinimum(0),
               LogicalUi16Maximum(4095),
               ReportSize(16),
               ReportCount(1),
               Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),
            EndCollection,

            // Point 9
            UsagePage(USB_HID_DIGITIZERS),
            Usage(USB_HID_FINGER),
            Collection(USB_HID_LOGICAL),
               Usage(USB_HID_CONTACT_ID),
               LogicalMinimum(0),
               LogicalMaximum(9),
               ReportSize(8),
               ReportCount(1),
               Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),

               Usage(USB_HID_TOUCH_PRESS),
               LogicalMinimum(0),
               LogicalMaximum(1),
               ReportSize(1),
               ReportCount(1),
               Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),

               ReportSize(7),  // Pad to 1byte
               ReportCount(1),
               Input(USB_HID_INPUT_CONSTANT | USB_HID_INPUT_ARRAY | USB_HID_INPUT_ABS),

               UsagePage(USB_HID_GENERIC_DESKTOP),
               Usage(USB_HID_X),
               LogicalMinimum(0),
               LogicalUi16Maximum(4095),
               ReportSize(16),
               ReportCount(1),
               Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),

               Usage(USB_HID_Y),
               LogicalMinimum(0),
               LogicalUi16Maximum(4095),
               ReportSize(16),
               ReportCount(1),
               Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),
            EndCollection,

            // Point 10
            UsagePage(USB_HID_DIGITIZERS),
            Usage(USB_HID_FINGER),
            Collection(USB_HID_LOGICAL),
               Usage(USB_HID_CONTACT_ID),
               LogicalMinimum(0),
               LogicalMaximum(9),
               ReportSize(8),
               ReportCount(1),
               Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),

               Usage(USB_HID_TOUCH_PRESS),
               LogicalMinimum(0),
               LogicalMaximum(1),
               ReportSize(1),
               ReportCount(1),
               Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),

               ReportSize(7),  // Pad to 1byte
               ReportCount(1),
               Input(USB_HID_INPUT_CONSTANT | USB_HID_INPUT_ARRAY | USB_HID_INPUT_ABS),

               UsagePage(USB_HID_GENERIC_DESKTOP),
               Usage(USB_HID_X),
               LogicalMinimum(0),
               LogicalUi16Maximum(4095),
               ReportSize(16),
               ReportCount(1),
               Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),

               Usage(USB_HID_Y),
               LogicalMinimum(0),
               LogicalUi16Maximum(4095),
               ReportSize(16),
               ReportCount(1),
               Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),
            EndCollection,

            UsagePage(USB_HID_DIGITIZERS),
            ReportID(HID_REPORT_ID_MAX_CONTACT),
            Usage(USB_HID_MAX_CONTACT),
            ReportCount(1),
            LogicalMaximum(10),
            Feature(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),

            VENDOR_FEATURE,
     EndCollection,
};

//*****************************************************************************
//
// The HID class descriptor table.  For the custom class, we have only a single
// report descriptor.
//
//*****************************************************************************
static const uint8_t * const g_pui8CustomClassDescriptors[] =
{
     g_pui8CustomReportDescriptor
};


//*****************************************************************************
//
// The HID descriptor for the Custom device.
//
//*****************************************************************************
static const tHIDDescriptor g_sCustomHIDDescriptor =
{
    9,                              // bLength
    USB_HID_DTYPE_HID,              // bDescriptorType
#ifdef __TMS320C28XX__
    0x0011,                         // bcdHID (version 1.11 compliant)
    0x0001,
#else
    0x111,                          // bcdHID (version 1.11 compliant)
#endif
    0,                              // bCountryCode (not localized)
    1,                              // bNumDescriptors
    {
        {
            USB_HID_DTYPE_REPORT,   // Report descriptor
#ifdef __TMS320C28XX__
            {
                (sizeof(g_pui8CustomReportDescriptor) & 0xFF),  // Size of report
                                                               // descriptor
                ((sizeof(g_pui8CustomReportDescriptor) & 0xFF00) >> 8)
            }
#else
            sizeof(g_pui8CustomReportDescriptor) // Size of report descriptor
#endif
        }
    }
};

//*****************************************************************************
//
// The HID configuration descriptor is defined as four or five sections
// depending upon the client's configuration choice.  These sections are:
//
// 1.  The 9 byte configuration descriptor (RAM).
// 2.  The interface descriptor (RAM).
// 3.  The HID report and physical descriptors (provided by the client)
//     (FLASH).
// 4.  The mandatory interrupt IN endpoint descriptor (FLASH).
// 5.  The optional interrupt OUT endpoint descriptor (FLASH).
//
//*****************************************************************************
static const tConfigSection g_sHIDConfigSection =
{
    sizeof(g_pui8CustomDescriptor),
    g_pui8CustomDescriptor
};

static const tConfigSection g_sHIDInterfaceSection =
{
    sizeof(g_pui8HIDInterface),
    g_pui8HIDInterface
};

static const tConfigSection g_sHIDInEndpointSection =
{
    sizeof(g_pui8HIDInEndpoint),
    g_pui8HIDInEndpoint
};

//*****************************************************************************
//
// Place holder for the user's HID descriptor block.
//
//*****************************************************************************
static tConfigSection g_sHIDDescriptorSection =
{
   sizeof(g_sCustomHIDDescriptor),
   (const uint8_t *)&g_sCustomHIDDescriptor
};

//*****************************************************************************
//
// This array lists all the sections that must be concatenated to make a
// single, complete HID configuration descriptor.
//
//*****************************************************************************
static const tConfigSection *g_psHIDSections[] =
{
    &g_sHIDConfigSection,
    &g_sHIDInterfaceSection,
    &g_sHIDDescriptorSection,
    &g_sHIDInEndpointSection,
};

#define NUM_HID_SECTIONS        (sizeof(g_psHIDSections) /                    \
                                 sizeof(g_psHIDSections[0]))

//*****************************************************************************
//
// The header for the single configuration we support.  This is the root of
// the data structure that defines all the bits and pieces that are pulled
// together to generate the configuration descriptor.  Note that this must be
// in RAM since we need to include or exclude the final section based on
// client supplied initialization parameters.
//
//*****************************************************************************
static tConfigHeader g_sHIDConfigHeader =
{
    NUM_HID_SECTIONS,
    g_psHIDSections
};

//*****************************************************************************
//
// Configuration Descriptor.
//
//*****************************************************************************
static const tConfigHeader * const g_ppsHIDConfigDescriptors[] =
{
    &g_sHIDConfigHeader
};

uint32_t
USBDHIDCustomReportFeature(void *pvCustomDevice)
{
    uint32_t ui32Retcode, ui32Count;
    tHIDCustomInstance *psInst;
    tUSBDHIDCustomDevice *psCustomDevice;
    tUSBDHIDDevice *psHIDDevice;

    //
    // Get a pointer to the device.
    //
    psCustomDevice = (tUSBDHIDCustomDevice *)pvCustomDevice;

    //
    // Get a pointer to the HID device data.
    //
    psHIDDevice = &psCustomDevice->sPrivateData.sHIDDevice;

    //
    // Get a pointer to our instance data
    //
    psInst = &psCustomDevice->sPrivateData;

    //
    // Update the global feature report with the information passed.
    //
    psInst->pui8Report[HID_REPORT_ID] = HID_REPORT_ID_MAX_CONTACT; //Report id
    psInst->pui8Report[HID_REPORT_FEATURE] = 10;

    //
    // If we are not configured, return an error here before trying to send
    // anything.
    //
    if(!psInst->ui8USBConfigured)
    {
        return(CUSTOM_ERR_NOT_CONFIGURED);
    }

    //
    // Only send a report if the transmitter is currently free.
    //
    if(USBDHIDTxPacketAvailable((void *)psHIDDevice))
    {
        //
        // Send the report to the host.
        //
        psInst->iCustomState = eHIDCustomStateSend;
        ui32Count = USBDHIDReportWrite((void *)psHIDDevice,
                                       psInst->pui8Report, FEATURE_REPORT_SIZE,
                                       true);

        //
        // Did we schedule a packet for transmission correctly?
        //
        if(!ui32Count)
        {
            //
            // No - report the error to the caller.
            //
            ui32Retcode = CUSTOM_ERR_TX_ERROR;
        }
        else
        {
            ui32Retcode = CUSTOM_SUCCESS;
        }
    }
    else
    {
        ui32Retcode = CUSTOM_ERR_TX_ERROR;
    }
    //
    // Return the relevant error code to the caller.
    //
    return(ui32Retcode);
}

uint32_t
USBDHIDCustomReportKey(void *pvCustomDevice, uint8_t ui8Key)
{
    uint32_t ui32Retcode, ui32Count;
    tHIDCustomInstance *psInst;
    tUSBDHIDCustomDevice *psCustomDevice;
    tUSBDHIDDevice *psHIDDevice;

    //
    // Get a pointer to the device.
    //
    psCustomDevice = (tUSBDHIDCustomDevice *)pvCustomDevice;

    //
    // Get a pointer to the HID device data.
    //
    psHIDDevice = &psCustomDevice->sPrivateData.sHIDDevice;

    //
    // Get a pointer to our instance data
    //
    psInst = &psCustomDevice->sPrivateData;

    //
    // Update the global key report with the information passed.
    //
    psInst->pui8Report[HID_REPORT_ID] = HID_REPORT_ID_BUTTON; //Report id
    psInst->pui8Report[HID_REPORT_KEY] = ui8Key; //Report id

    //
    // If we are not configured, return an error here before trying to send
    // anything.
    //
    if(!psInst->ui8USBConfigured)
    {
        return(CUSTOM_ERR_NOT_CONFIGURED);
    }

    //
    // Only send a report if the transmitter is currently free.
    //
    if(USBDHIDTxPacketAvailable((void *)psHIDDevice))
    {
        //
        // Send the report to the host.
        //
        psInst->iCustomState = eHIDCustomStateSend;
        ui32Count = USBDHIDReportWrite((void *)psHIDDevice,
                                       psInst->pui8Report, CUSTOM_REPORT_BUTTON_SIZE,
                                       true);

        //
        // Did we schedule a packet for transmission correctly?
        //
        if(!ui32Count)
        {
            //
            // No - report the error to the caller.
            //
            ui32Retcode = CUSTOM_ERR_TX_ERROR;
        }
        else
        {
            ui32Retcode = CUSTOM_SUCCESS;
        }
    }
    else
    {
        ui32Retcode = CUSTOM_ERR_TX_ERROR;
    }
    //
    // Return the relevant error code to the caller.
    //
    return(ui32Retcode);
}

//*****************************************************************************
//
//! Reports a touch screen state change, pointer movement , to the USB
//! host.
//!
//! \param pvCustomDevice is the pointer to the hid device instance structure.
//! \param psEvent is the relative touch pointer movement that the
//! application wishes to report.
//!
//
//*****************************************************************************
uint32_t
USBDHIDCustomTouchEvent(void *pvCustomDevice, tUSBHIDCustomTouchEvent *psEvent)
{
    uint32_t ui32Retcode, ui32Count;
    tHIDCustomInstance *psInst;
    tUSBDHIDCustomDevice *psCustomDevice;
    tUSBDHIDDevice *psHIDDevice;
    uint8_t finger_iter = 0;

    //
    // Get a pointer to the device.
    //
    psCustomDevice = (tUSBDHIDCustomDevice *)pvCustomDevice;

    //
    // Get a pointer to the HID device data.
    //
    psHIDDevice = &psCustomDevice->sPrivateData.sHIDDevice;

    //
    // Get a pointer to our instance data
    //
    psInst = &psCustomDevice->sPrivateData;

    //
    // Update the global touch report with the information passed.
    //
    psInst->pui8Report[HID_REPORT_ID] = HID_REPORT_ID_TOUCH_SCREEN; //Report id
    psInst->pui8Report[HID_REPORT_CONTACT_COUNT] = psEvent->press_count;

    for (finger_iter = 0; finger_iter < 10; finger_iter++) {
        if (finger_iter < psEvent->press_count) {
            psInst->pui8Report[HID_REPORT_FINGER_CONTACT_ID(finger_iter)] = (uint8_t)finger_iter;
            psInst->pui8Report[HID_REPORT_FINGER_PRESS(finger_iter)] = (uint8_t)psEvent->fingers[finger_iter].press;
            psInst->pui8Report[HID_REPORT_FINGER_X_LSB(finger_iter)] = (uint8_t)UI16_LSB(psEvent->fingers[finger_iter].x);
            psInst->pui8Report[HID_REPORT_FINGER_X_MSB(finger_iter)] = (uint8_t)UI16_MSB(psEvent->fingers[finger_iter].x);
            psInst->pui8Report[HID_REPORT_FINGER_Y_LSB(finger_iter)] = (uint8_t)UI16_LSB(psEvent->fingers[finger_iter].y);
            psInst->pui8Report[HID_REPORT_FINGER_Y_MSB(finger_iter)] = (uint8_t)UI16_MSB(psEvent->fingers[finger_iter].y);
        } else {
            psInst->pui8Report[HID_REPORT_FINGER_CONTACT_ID(finger_iter)] = 0;
            psInst->pui8Report[HID_REPORT_FINGER_PRESS(finger_iter)] = 0;
            psInst->pui8Report[HID_REPORT_FINGER_X_LSB(finger_iter)] = 0;
            psInst->pui8Report[HID_REPORT_FINGER_X_MSB(finger_iter)] = 0;
            psInst->pui8Report[HID_REPORT_FINGER_Y_LSB(finger_iter)] = 0;
            psInst->pui8Report[HID_REPORT_FINGER_Y_MSB(finger_iter)] = 0;
        }
    }

    //
    // If we are not configured, return an error here before trying to send
    // anything.
    //
    if(!psInst->ui8USBConfigured)
    {
        return(CUSTOM_ERR_NOT_CONFIGURED);
    }

    //
    // Only send a report if the transmitter is currently free.
    //
    if(USBDHIDTxPacketAvailable((void *)psHIDDevice))
    {
        //
        // Send the report to the host.
        //
        psInst->iCustomState = eHIDCustomStateSend;
        ui32Count = USBDHIDReportWrite((void *)psHIDDevice,
                                       psInst->pui8Report, CUSTOM_REPORT_SIZE,
                                       true);

        //
        // Did we schedule a packet for transmission correctly?
        //
        if(!ui32Count)
        {
            //
            // No - report the error to the caller.
            //
            ui32Retcode = CUSTOM_ERR_TX_ERROR;
        }
        else
        {
            ui32Retcode = CUSTOM_SUCCESS;
        }
    }
    else
    {
        ui32Retcode = CUSTOM_ERR_TX_ERROR;
    }
    //
    // Return the relevant error code to the caller.
    //
    return(ui32Retcode);
}

uint32_t
USBDHIDCustomPointStateChange(void *pvCustomDevice, uint16_t ui16DeltaX, uint16_t ui16DeltaY)
{
    tUSBHIDCustomTouchEvent sEvent = {0};

    sEvent.press_count = 1;
    sEvent.fingers[0].press = 1;
    sEvent.fingers[0].x = ui16DeltaX;
    sEvent.fingers[0].y = ui16DeltaY;

#if 0
    sEvent.fingers[1].press = 1;
    sEvent.fingers[1].x = ui16DeltaX + 500;
    sEvent.fingers[1].y = ui16DeltaY;
#endif
    //
    // Return the relevant error code to the caller.
    //
    return USBDHIDCustomTouchEvent(pvCustomDevice, &sEvent);
}

//*****************************************************************************
//
// Main HID device class event handler function.
//
// \param pvCustomDevice is the event callback pointer provided during
// USBDHIDInit().  This is a pointer to our HID device structure
// (&g_sHIDCustomDevice).
// \param ui32Event identifies the event we are being called back for.
// \param ui32MsgData is an event-specific value.
// \param pvMsgData is an event-specific pointer.
//
// This function is called by the HID device class driver to inform the
// application of particular asynchronous events related to operation of the
// Custom HID device.
//
// \return Returns a value which is event-specific.
//
//*****************************************************************************
static uint32_t
HIDCustomRxHandler(void *pvCustomDevice, uint32_t ui32Event,
                  uint32_t ui32MsgData, void *pvMsgData)
{
    tHIDCustomInstance *psInst;
    tUSBDHIDCustomDevice *psCustomDevice;

    //
    // Make sure we did not get a NULL pointer.
    //
    ASSERT(pvCustomDevice);

    //
    // Get a pointer to our instance data
    //
    psCustomDevice = (tUSBDHIDCustomDevice *)pvCustomDevice;
    psInst = &psCustomDevice->sPrivateData;

    //
    // Which event were we sent?
    //
    switch(ui32Event)
    {
        //
        // The host has connected to us and configured the device.
        //
        case USB_EVENT_CONNECTED:
        {
            psInst->ui8USBConfigured = true;

            //
            // Pass the information on to the client.
            //
            psCustomDevice->pfnCallback(psCustomDevice->pvCBData,
                                       USB_EVENT_CONNECTED, 0, (void *)0);

            break;
        }

        //
        // The host has disconnected from us.
        //
        case USB_EVENT_DISCONNECTED:
        {
            psInst->ui8USBConfigured = false;

            //
            // Pass the information on to the client.
            //
            psCustomDevice->pfnCallback(psCustomDevice->pvCBData,
                                       USB_EVENT_DISCONNECTED, 0, (void *)0);

            break;
        }

        //
        // The host is polling us for a particular report and the HID driver
        // is asking for the latest version to transmit.
        //
        case USBD_HID_EVENT_IDLE_TIMEOUT:
        case USBD_HID_EVENT_GET_REPORT:
        {
            //
            // We only support a single input report so we don't need to check
            // the ui32MsgValue parameter in this case.  Set the report pointer
            // in *pvMsgData and return the length of the report in bytes.
            //
            *(uint8_t **)pvMsgData = psInst->pui8Report;
            return(8);
        }

        //
        // The device class driver has completed sending a report to the
        // host in response to a Get_Report request.
        //
        case USBD_HID_EVENT_REPORT_SENT:
        {
            //
            // We have nothing to do here.
            //
            break;
        }

        //
        // This event is sent in response to a host Set_Report request.  The
        // Custom device has no output reports so we return a NULL pointer and
        // zero length to cause this request to be stalled.
        //
        case USBD_HID_EVENT_GET_REPORT_BUFFER:
        {
            //
            // We are being asked for a report that does not exist for
            // this device.  Return 0 to indicate that we are not providing
            // a buffer.
            //
            return(0);
        }

        //
        // The host is asking us to set either boot or report protocol (not
        // that it makes any difference to this particular Custom).
        //
        case USBD_HID_EVENT_SET_PROTOCOL:
        {
            psInst->ui8Protocol = ui32MsgData;
            break;
        }

        //
        // The host is asking us to tell it which protocol we are currently
        // using, boot or request.
        //
        case USBD_HID_EVENT_GET_PROTOCOL:
        {
            return(psInst->ui8Protocol);
        }

        //
        // Pass ERROR, SUSPEND and RESUME to the client unchanged.
        //
        case USB_EVENT_ERROR:
        case USB_EVENT_SUSPEND:
        case USB_EVENT_RESUME:
        {
            return(psCustomDevice->pfnCallback(psCustomDevice->pvCBData,
                                              ui32Event, ui32MsgData,
                                              pvMsgData));
        }

        //
        // We ignore all other events.
        //
        default:
        {
            break;
        }
    }
    return(0);
}

//*****************************************************************************
//
// HID device class transmit channel event handler function.
//
// \param pvCustomDevice is the event callback pointer provided during
// USBDHIDInit(). This is a pointer to our HID device structure
// (&g_sHIDCustomDevice).
// \param ui32Event identifies the event we are being called back for.
// \param ui32MsgData is an event-specific value.
// \param pvMsgData is an event-specific pointer.
//
// This function is called by the HID device class driver to inform the
// application of particular asynchronous events related to report
// transmissions made using the interrupt IN endpoint.
//
// \return Returns a value which is event-specific.
//
//*****************************************************************************
static uint32_t
HIDCustomTxHandler(void *pvCustomDevice, uint32_t ui32Event,
                  uint32_t ui32MsgData, void *pvMsgData)
{
    tHIDCustomInstance *psInst;
    tUSBDHIDCustomDevice *psCustomDevice;

    //
    // Make sure we did not get a NULL pointer.
    //
    ASSERT(pvCustomDevice);

    //
    // Get a pointer to our instance data
    //
    psCustomDevice = (tUSBDHIDCustomDevice *)pvCustomDevice;
    psInst = &psCustomDevice->sPrivateData;

    //
    // Which event were we sent?
    //
    switch (ui32Event)
    {
        //
        // A report transmitted via the interrupt IN endpoint was acknowledged
        // by the host.
        //
        case USB_EVENT_TX_COMPLETE:
        {
            //
            // Our last transmission is complete.
            //
            psInst->iCustomState = eHIDCustomStateIdle;

            //
            // Pass the event on to the client.
            //
            psCustomDevice->pfnCallback(psCustomDevice->pvCBData,
                                       USB_EVENT_TX_COMPLETE, ui32MsgData,
                                       (void *)0);

            break;
        }

        //
        // We ignore all other events related to transmission of reports via
        // the interrupt IN endpoint.
        //
        default:
        {
            break;
        }
    }

    return(0);
}

//*****************************************************************************
//
//! Initializes HID Custom device operation for a given USB controller.
//!
//! \param ui32Index is the index of the USB controller which is to be
//! initialized for HID Custom device operation.
//! \param psCustomDevice points to a structure containing parameters
//! customizing the operation of the HID Custom device.
//! \param psCompEntry is the composite device entry to initialize when
//! creating a composite device.
//!
//! This call is very similar to USBDHIDCustomInit() except that it is used for
//! initializing an instance of the HID Custom device for use in a composite
//! device.  If this HID Custom is part of a composite device, then the
//! \e psCompEntry should point to the composite device entry to initialize.
//! This is part of the array that is passed to the USBDCompositeInit()
//! function.
//!
//! \return Returns zero on failure or a non-zero instance value that should be
//! used with the remaining USB HID Custom APIs.
//
//*****************************************************************************
void *
USBDHIDCustomCompositeInit(uint32_t ui32Index,
                          tUSBDHIDCustomDevice *psCustomDevice,
                          tCompositeEntry *psCompEntry)
{
    tHIDCustomInstance *psInst;
    tUSBDHIDDevice *psHIDDevice;


    //
    // Check parameter validity.
    //
    ASSERT(psCustomDevice);

    ASSERT(psCompEntry);

    ASSERT(psCustomDevice->ppui8StringDescriptors);

    ASSERT(psCustomDevice->pfnCallback);

    //
    // Get a pointer to our instance data
    //
    psInst = &psCustomDevice->sPrivateData;

    //
    // Get a pointer to the HID device data.
    //
    psHIDDevice = &psCustomDevice->sPrivateData.sHIDDevice;

    //
    // Initialize the various fields in our instance structure.
    //
    psInst->ui8USBConfigured = 0;
    psInst->ui8Protocol = USB_HID_PROTOCOL_REPORT;
    psInst->sReportIdle.ui8Duration4mS = 0;
    psInst->sReportIdle.ui8ReportID = 0;
    psInst->sReportIdle.ui32TimeSinceReportmS = 0;
    psInst->sReportIdle.ui16TimeTillNextmS = 0;
    psInst->iCustomState = eHIDCustomStateUnconfigured;

    //
    // Initialize the HID device class instance structure based on input from
    // the caller.
    //
    psHIDDevice->ui16PID = psCustomDevice->ui16PID;
    psHIDDevice->ui16VID = psCustomDevice->ui16VID;
    psHIDDevice->ui16MaxPowermA = psCustomDevice->ui16MaxPowermA;
    psHIDDevice->ui8PwrAttributes = psCustomDevice->ui8PwrAttributes;
    psHIDDevice->ui8Subclass = USB_HID_SCLASS_BOOT;
    psHIDDevice->ui8Protocol = USB_HID_PROTOCOL_MOUSE;
    psHIDDevice->ui8NumInputReports = 1;
    psHIDDevice->psReportIdle = &psInst->sReportIdle;
    psHIDDevice->pfnRxCallback = HIDCustomRxHandler;
    psHIDDevice->pvRxCBData = (void *)psCustomDevice;
    psHIDDevice->pfnTxCallback = HIDCustomTxHandler;
    psHIDDevice->pvTxCBData = (void *)psCustomDevice;
    psHIDDevice->bUseOutEndpoint = false;
    psHIDDevice->psHIDDescriptor = &g_sCustomHIDDescriptor;
    psHIDDevice->ppui8ClassDescriptors = g_pui8CustomClassDescriptors;
    psHIDDevice->ppui8StringDescriptors =
                                    psCustomDevice->ppui8StringDescriptors;
    psHIDDevice->ui32NumStringDescriptors =
                                    psCustomDevice->ui32NumStringDescriptors;
    psHIDDevice->ppsConfigDescriptor = g_ppsHIDConfigDescriptors;

    //
    // Initialize the lower layer HID driver and pass it the various structures
    // and descriptors necessary to declare that we are a keyboard.
    //
    return(USBDHIDCompositeInit(ui32Index, psHIDDevice, psCompEntry));
}

//*****************************************************************************
//
//! Initializes HID Custom device operation for a given USB controller.
//!
//! \param ui32Index is the index of the USB controller which is to be
//! initialized for HID Custom device operation.
//! \param psCustomDevice points to a structure containing parameters
//! customizing the operation of the HID Custom device.
//!
//! An application wishing to offer a USB HID Custom interface to a USB host
//! must call this function to initialize the USB controller and attach the
//! Custom device to the USB bus.  This function performs all required USB
//! initialization.
//!
//! On successful completion, this function returns the \e psCustomDevice
//! pointer passed to it.  This must be passed on all future calls to the HID
//! Custom device driver.
//!
//! When a host connects and configures the device, the application callback
//! receives \b USB_EVENT_CONNECTED after which calls can be made to
//! USBDHIDCustomStateChange() to report pointer movement and button presses
//! to the host.
//!
//! \note The application must not make any calls to the lower level USB device
//! interfaces if interacting with USB via the USB HID Custom device API.
//! Doing so causes unpredictable (though almost certainly unpleasant)
//! behavior.
//!
//! \return Returns NULL on failure or the psCustomDevice pointer on success.
//
//*****************************************************************************
void *
USBDHIDCustomInit(uint32_t ui32Index, tUSBDHIDCustomDevice *psCustomDevice)
{
    void *pvRetcode;
    tUSBDHIDDevice *psHIDDevice;
    tConfigDescriptor *pConfigDesc;

    //
    // Check parameter validity.
    //
    ASSERT(psCustomDevice);
    ASSERT(psCustomDevice->ppui8StringDescriptors);
    ASSERT(psCustomDevice->pfnCallback);

    //
    // Get a pointer to the HID device data.
    //
    psHIDDevice = &psCustomDevice->sPrivateData.sHIDDevice;

    pConfigDesc = (tConfigDescriptor *)g_pui8CustomDescriptor;
    pConfigDesc->bmAttributes = psCustomDevice->ui8PwrAttributes;
    pConfigDesc->bMaxPower =  (uint8_t)(psCustomDevice->ui16MaxPowermA / 2);

    //
    // Call the common initialization routine.
    //
    pvRetcode = USBDHIDCustomCompositeInit(ui32Index, psCustomDevice, 0);

    //
    // If we initialized the HID layer successfully, pass our device pointer
    // back as the return code, otherwise return NULL to indicate an error.
    //
    if(pvRetcode)
    {
        //
        // Initialize the lower layer HID driver and pass it the various
        // structures and descriptors necessary to declare that we are a
        // keyboard.
        //
        pvRetcode = USBDHIDInit(ui32Index, psHIDDevice);

        return((void *)psCustomDevice);
    }
    else
    {
        return((void *)0);
    }
}
