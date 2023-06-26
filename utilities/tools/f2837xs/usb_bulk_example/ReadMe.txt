-----------------------------------
USB Bulk Example (usb_bulk_example)
-----------------------------------

This Windows command line application is written using C for Windows
and should be built using Microsoft Visual Studio 2010.  Project
file usb_bulk_example.vxcproj is provided to build the application.

USB communication with the board running the usb_dev_bulk sample application
is performed using the TIUSBDLL interface which is a thin wrapper over the 
Microsoft WinUSB API.  The relevant WinUSB subsystem files and the 
TIUSBDLL.dll are installed when you  first connect the board to a Windows
host via USB and install the drivers. Device drivers for the usb_dev_bulk
device can be found in the MWare\windows_drivers directory.

The TIUSBDLL interface is provided purely to allow the sample applications
to be compiled and run in the absence of the Windows Device Driver Kit
(DDK).  The WinUSB API header and library files are not included in the
Windows SDK shipped with Visual Studio 2010 so any code which uses this
interface requires access to the DDK to build.  TIUSBDLL contains all
the application code requiring WinUSB so applications may link to it
without the need for the Windows DDK.
