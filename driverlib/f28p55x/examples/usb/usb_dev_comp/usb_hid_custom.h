#ifndef _USB_HID_CUSTOM_H_
#define _USB_HID_CUSTOM_H_

#define TICKS_PER_SECOND        100
//#define MOUSE_MOVE_INC           1    // The incremental update for the mouse.
//#define MOUSE_MOVE_DEC          -1

#define MAX_SEND_DELAY          50   // The number of system ticks to wait for
                                     // each USB packet to be sent before
                                     // we assume the host has disconnected.
                                     // The value 50 equates to half a second.

//extern volatile uint32_t g_ui32CustomCommands;
//extern volatile uint32_t g_ui32SysTickCount;
//extern volatile bool g_bMouseConnected;


void usb_hid_custom_sim_init();
void usb_hid_custom_sim_start();
void usb_hid_custom_sim_handler();

#endif
