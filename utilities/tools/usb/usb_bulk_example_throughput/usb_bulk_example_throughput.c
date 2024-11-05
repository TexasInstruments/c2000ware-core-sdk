//###########################################################################
//
// FILE:   usb_bulk_example_throughput.c
//
// TITLE:  A very simple command line application that attempts
//         to open the TI Generic Bulk USB device and exchange data
//         with it.
//
// If the device is successfully opened, then data is sent continuously.
//
// Communication with the device is carried out via a simple DLL, tiusbdll(64),
// which is responsible for opening and closing the device and for
// sending and receiving blocks of data.  This structure allows the
// application code to be kept independent of the underlying USB driver
// in use.  In this implementation, Microsoft's WinUSB interface is used
// but a switch to another stack, for example the open source libusb-win32
// interface could be made merely be replacing the tiusbdll(64).dll with
// another version writing to the different USB stack.
//
// One downside to using WinUSB is that it requires you to have the Windows
// Device Driver Kit (DDK) installed to build applications which use the
// interface. This is a very large download making it awkward for people
// with slow internet connections. The use of tiusbdll(64).dll also offers
// the advantage that applications using it can still be modified and
// rebuilt even without the DDK installed on the development system.  To
// update and rebuild tiusbdll itself, however, the DDK is still required.
//
//
//##############################################################################
//
//
// 
// C2000Ware v5.04.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//##############################################################################


//
// Included Files
//
#include <windows.h>
#include <strsafe.h>
#include <initguid.h>
#include "tiusbdll.h"
#include "ti_guids.h"

//
// Buffer size definitions.
//
#define MAX_STRING_LEN 65535
#define MAX_ENTRY_LEN 65535
#define USB_BUFFER_LEN 65535
//
// Defines
//

//
// The build version number
//
#define BLDVER "7611"

//
// The number of bytes we read and write per transaction if in echo mode.
//
#define ECHO_PACKET_SIZE 65535

//
// Globals
//

//
// Buffer into which error messages are written.
//
TCHAR g_pcErrorString[MAX_STRING_LEN];

//
// The number of bytes transferred in the last measurement interval.
//
ULONG g_ulByteCount = 0;

//
// The total number of packets transferred.
//
ULONG g_ulPacketCount = 0;

//
// Functions
//

//****************************************************************************
//
// Return a string describing the supplied system error code.
//
// \param dwError is a Windows system error code.
//
// This function returns a pointer to a string describing the error code
// passed in the dwError parameter. If no description string can be found
// the string "Unknown" is returned.
//
// \return Returns a pointer to a string describing the error.
//
//****************************************************************************
LPTSTR GetSystemErrorString(DWORD dwError)
{
    DWORD dwRetcode;

    //
    // Ask Windows for the error message description.
    //
    dwRetcode = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, "%0", dwError, 0,
                              g_pcErrorString, MAX_STRING_LEN, NULL);

    if(dwRetcode == 0)
    {
        return((LPTSTR)L"Unknown");
    }
    else
    {
        //
        // Remove the trailing "\n\r" if present.
        //
        if(dwRetcode >= 2)
        {
            if(g_pcErrorString[dwRetcode - 2] == '\r')
            {
                g_pcErrorString[dwRetcode - 2] = '\0';
            }
        }

        return(g_pcErrorString);
    }
}

//****************************************************************************
//
// Print the throughput in terms of Kbps once per second.
//
//****************************************************************************
void UpdateThroughput(void)
{
    static ULONG ulStartTime = 0;
    static ULONG ulLast = 0;
    ULONG ulNow;
    ULONG ulElapsed;
    SYSTEMTIME sSysTime;

    //
    // Get the current system time.
    //
    GetSystemTime(&sSysTime);
    ulNow = (((((sSysTime.wHour * 60) +
               sSysTime.wMinute) * 60) +
              sSysTime.wSecond) * 1000) + sSysTime.wMilliseconds;

    //
    // If this is the first call, set the start time.
    //
    if(ulStartTime == 0)
    {
        ulStartTime = ulNow;
        ulLast = ulNow;
        return;
    }

    //
    // How much time has elapsed since the last measurement?
    //
    ulElapsed = (ulNow > ulStartTime) ? (ulNow - ulStartTime) : (ulStartTime - ulNow);

    //
    // We dump a new measurement every second.
    //
    if(ulElapsed > 1000)
    {
        printf("\r%6dKbps Packets: %10d ", ((g_ulByteCount * 8) / ulElapsed),
               g_ulPacketCount);
        g_ulByteCount = 0;
        ulStartTime = ulNow;
    }
}

//****************************************************************************
//
// The main application entry function.
//
// \param None.
//
// This function forms the main entry point of the example application. It
// initializes the USB bulk device, prompts the user for an ASCII string,
// sends this string to the device, reads the response from the device (which
// will be the same string with the character order reversed if using the
// sample device provided) and displays the returned string.
//
// \return Set the exit code to 0 of no errors cause the application to end
// or a non-zero value otherwise.
//
//****************************************************************************
int main(int argc, char *argv[])
{
    BOOL bResult;
    BOOL bDriverInstalled;
    char szBuffer[USB_BUFFER_LEN];
    ULONG ulWritten;
    ULONG ulRead;
    ULONG ulLength;
    DWORD dwError;
    TIUSB_HANDLE hUSB;

    //
    // Print a cheerful welcome.
    //
    printf("\nTI Bulk Throughput USB Device Example\n");
    printf( "---------------------------------\n\n");
    printf("Version %s\n\n", BLDVER);
    printf("This is a partner application to the Bulk Throughput Example\n");
    printf("shipped software releases for USB-enabled boards. \n");
    printf("It sends data and displays the throughput and transmitted data packets\n");

	//
    // Find our USB device and prepare it for communication.
    //
    hUSB = InitializeDevice(BULK_VID, BULK_PID,
                            (LPGUID)&(GUID_DEVINTERFACE_TI_BULK),
                            &bDriverInstalled);

    if(hUSB)
    {

		printf("Press Ctrl+C to exit.\n\n");
		while(1)
        {
			//
            // Read a block of data from the device.
            //
            dwError = ReadUSBPacket(hUSB, szBuffer, ECHO_PACKET_SIZE, &ulRead,
                                    INFINITE, NULL);

            if(dwError != ERROR_SUCCESS)
            {
                //
                // We failed to read from the device.
                //
                printf("\n\nError %d (%S) reading from bulk IN pipe.\n", dwError,
                       GetSystemErrorString(dwError));
               break;
            }
            else
            {
                //
                // Update our byte and packet counters.
                //
                g_ulByteCount += ulRead;
                g_ulPacketCount++;
					
                //
                // Display the throughput.
                //
                UpdateThroughput();
            }
        }
    }
    else
    {
        //
        // An error was reported while trying to connect to the device.
        //
        dwError = GetLastError();

        printf("\nUnable to initialize the TI Bulk USB Device.\n");
        printf("Error code is %d (%S)\n\n", dwError, GetSystemErrorString(dwError));
        printf("Please make sure you have a TI USB-enabled evaluation\n");
        printf("or development kit running the USB Device Bulk Throughput example\n");
        printf("application connected to this system via the \"USB OTG\" or\n");
        printf("\"USB DEVICE\" connectors. Once the device is connected, run\n");
        printf("this application again.\n\n");

        printf("\nPress \"Enter\" to exit: ");
        fgets(szBuffer, MAX_STRING_LEN, stdin);
        printf("\n");
        return(2);
    }

    TerminateDevice(hUSB);

    return(0);
}

//
// End of file
//
