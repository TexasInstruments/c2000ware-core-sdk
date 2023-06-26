//*****************************************************************************
//
// TIDFUwrap.cpp : A thin wrapper over the TIDFU.dll library allowing it to be
//                 loaded dynamically rather than statically linking to its .lib
//                 file.
//
// Copyright (c) 2009-2011 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 7611 of the Stellaris Firmware Development Package.
//
//*****************************************************************************

#include <windows.h>
#include "tidfu.h"
#include "tidfuwrap.h"

//*****************************************************************************
//
// DLL module handle.
//
//*****************************************************************************
HINSTANCE hLMUSB = (HINSTANCE)NULL;

//*****************************************************************************
//
// Function pointers for each DLL entry point.
//
//*****************************************************************************
tTIDFUInit pfnTIDFUInit = NULL;
tTIDFUDeviceOpen pfnTIDFUDeviceOpen = NULL;
tTIDFUDeviceClose pfnTIDFUDeviceClose = NULL;
tTIDFUDeviceStringGet pfnTIDFUDeviceStringGet = NULL;
tTIDFUDeviceASCIIStringGet pfnTIDFUDeviceASCIIStringGet = NULL;
tTIDFUParamsGet pfnTIDFUParamsGet = NULL;
tTIDFUIsValidImage pfnTIDFUIsValidImage = NULL;
tTIDFUDownload pfnTIDFUDownload = NULL;
tTIDFUDownloadBin pfnTIDFUDownloadBin = NULL;
tTIDFUDownloadHex pfnTIDFUDownloadHex = NULL;
tTIDFUErase pfnTIDFUErase = NULL;
tTIDFUBlankCheck pfnTIDFUBlankCheck = NULL;
tTIDFUUpload pfnTIDFUUpload = NULL;
tTIDFUStatusGet pfnTIDFUStatusGet = NULL;
tTIDFUErrorStringGet pfnTIDFUErrorStringGet = NULL;
tTIDFUModeSwitch pfnTIDFUModeSwitch = NULL;

tTIDFUErr __stdcall _TIDFUInit(void)
{
    //
    // Try to load the USB DLL.
    //
    hLMUSB = LoadLibrary(TEXT("TIDFU.dll"));

    //
    // Did we find it?
    //
    if(hLMUSB)
    {
        //
        // Yes - query all the entry point addresses.
        //
        pfnTIDFUInit = (tTIDFUInit)GetProcAddress(hLMUSB, "TIDFUInit");
        pfnTIDFUDeviceOpen = (tTIDFUDeviceOpen)GetProcAddress(hLMUSB, "TIDFUDeviceOpen");
        pfnTIDFUDeviceClose = (tTIDFUDeviceClose)GetProcAddress(hLMUSB, "TIDFUDeviceClose");
        pfnTIDFUDeviceStringGet = (tTIDFUDeviceStringGet)GetProcAddress(hLMUSB, "TIDFUDeviceStringGet");
        pfnTIDFUDeviceASCIIStringGet = (tTIDFUDeviceASCIIStringGet)GetProcAddress(hLMUSB, "TIDFUDeviceASCIIStringGet");
        pfnTIDFUParamsGet = (tTIDFUParamsGet)GetProcAddress(hLMUSB, "TIDFUParamsGet");
        pfnTIDFUIsValidImage = (tTIDFUIsValidImage)GetProcAddress(hLMUSB, "TIDFUIsValidImage");
        pfnTIDFUDownload = (tTIDFUDownload)GetProcAddress(hLMUSB, "TIDFUDownload");
        pfnTIDFUDownloadBin = (tTIDFUDownloadBin)GetProcAddress(hLMUSB, "TIDFUDownloadBin");
        pfnTIDFUDownloadHex = (tTIDFUDownloadHex)GetProcAddress(hLMUSB, "TIDFUDownloadHex");
        pfnTIDFUErase = (tTIDFUErase)GetProcAddress(hLMUSB, "TIDFUErase");
        pfnTIDFUBlankCheck = (tTIDFUBlankCheck)GetProcAddress(hLMUSB, "TIDFUBlankCheck");
        pfnTIDFUUpload = (tTIDFUUpload)GetProcAddress(hLMUSB, "TIDFUUpload");
        pfnTIDFUStatusGet = (tTIDFUStatusGet)GetProcAddress(hLMUSB, "TIDFUStatusGet");
        pfnTIDFUErrorStringGet = (tTIDFUErrorStringGet)GetProcAddress(hLMUSB, "TIDFUErrorStringGet");
        pfnTIDFUModeSwitch = (tTIDFUModeSwitch)GetProcAddress(hLMUSB, "TIDFUModeSwitch");

        //
        // Make sure we actually queried all the expected entry points.
        //
        if(!pfnTIDFUInit || !pfnTIDFUDeviceOpen ||  !pfnTIDFUDeviceClose ||
           !pfnTIDFUDeviceStringGet || !pfnTIDFUDeviceASCIIStringGet ||
           !pfnTIDFUParamsGet || !pfnTIDFUIsValidImage || !pfnTIDFUDownload ||
           !pfnTIDFUDownloadBin || !pfnTIDFUDownloadHex || !pfnTIDFUErase ||
		   !pfnTIDFUBlankCheck || !pfnTIDFUUpload || !pfnTIDFUStatusGet || 
		   !pfnTIDFUErrorStringGet || !pfnTIDFUModeSwitch)
        {
            //
            // We failed to query at least one entry point.  Return
            // DFU_ERR_INVALID_ADDR to signal to the caller that the driver
            // is likely the wrong version.
            //
            return(DFU_ERR_INVALID_ADDR);
        }
        else
        {
            //
            // We got all the expected function pointers so call the library
            // init function and return it's response.
            //
            return(pfnTIDFUInit());
        }
    }
    else
    {
        //
        // The DLL could not be found.  This tends to suggest that the driver
        // is not installed.  Return an appropriate error code to the caller
        // so that they can provide helpful information to the user.
        //
        return(DFU_ERR_NOT_FOUND);
    }
}

tTIDFUErr __stdcall _TIDFUDeviceOpen(int iDeviceIndex,
                                    tTIDFUDeviceInfo *psDevInfo,
                                    tTIDFUHandle *phHandle)
{
    if(pfnTIDFUDeviceOpen)
    {
        return(pfnTIDFUDeviceOpen(iDeviceIndex, psDevInfo, phHandle));
    }

    return(DFU_ERR_HANDLE);
}

tTIDFUErr __stdcall _TIDFUDeviceClose(tTIDFUHandle hHandle, bool bReset)
{
    if(pfnTIDFUDeviceClose)
    {
        return(pfnTIDFUDeviceClose(hHandle, bReset));
    }

    return(DFU_ERR_HANDLE);
}

tTIDFUErr __stdcall _TIDFUDeviceStringGet(tTIDFUHandle hHandle,
                                         unsigned char ucStringIndex,
                                         unsigned short usLanguageID,
                                         char *pcString,
                                         unsigned short *pusStringLen)
{
    if(pfnTIDFUDeviceStringGet)
    {
        return(pfnTIDFUDeviceStringGet(hHandle, ucStringIndex, usLanguageID,
                                       pcString, pusStringLen));
    }

    return(DFU_ERR_HANDLE);
}

tTIDFUErr __stdcall _TIDFUDeviceASCIIStringGet(tTIDFUHandle hHandle,
                                              unsigned char ucStringIndex,
                                              char *pcString,
                                              unsigned short *pusStringLen)
{
    if(pfnTIDFUDeviceASCIIStringGet)
    {
        return(pfnTIDFUDeviceASCIIStringGet(hHandle, ucStringIndex, pcString,
                                            pusStringLen));
    }

    return(DFU_ERR_HANDLE);
}

tTIDFUErr __stdcall _TIDFUParamsGet(tTIDFUHandle hHandle,
                                   tTIDFUParams *psParams)
{
    if(pfnTIDFUParamsGet)
    {
        return(pfnTIDFUParamsGet(hHandle, psParams));
    }

    return(DFU_ERR_HANDLE);
}

tTIDFUErr __stdcall _TIDFUIsValidImage(tTIDFUHandle hHandle,
                                      unsigned char *pcDFUImage,
                                      unsigned long ulImageLen,
                                      bool *pbStellarisFormat)
{
    if(pfnTIDFUIsValidImage)
    {
        return(pfnTIDFUIsValidImage(hHandle, pcDFUImage, ulImageLen,
                                    pbStellarisFormat));
    }

    return(DFU_ERR_HANDLE);
}

tTIDFUErr __stdcall _TIDFUDownload(tTIDFUHandle hHandle,
                                  unsigned char *pcDFUImage,
                                  unsigned long ulImageLen, bool bVerify,
                                  bool bIgnoreIDs, HWND hwndNotify)
{
    if(pfnTIDFUDownload)
    {
        return(pfnTIDFUDownload(hHandle, pcDFUImage, ulImageLen, bVerify,
                                bIgnoreIDs, hwndNotify));
    }

    return(DFU_ERR_HANDLE);
}

tTIDFUErr __stdcall _TIDFUDownloadBin(tTIDFUHandle hHandle,
                                     unsigned char *pcBinaryImage,
                                     unsigned long ulImageLen,
                                     unsigned long ulStartAddr,
                                     bool bVerify, HWND hwndNotify)
{
    if(pfnTIDFUDownloadBin)
    {
        return(pfnTIDFUDownloadBin(hHandle, pcBinaryImage, ulImageLen,
                                   ulStartAddr, bVerify, hwndNotify));
    }

    return(DFU_ERR_HANDLE);
}

tTIDFUErr __stdcall _TIDFUDownloadHex(tTIDFUHandle hHandle,
                                     unsigned char *pcBinaryImage,
                                     unsigned long ulImageLen,
                                     bool bVerify, HWND hwndNotify)
{
    if(pfnTIDFUDownloadHex)
    {
        return(pfnTIDFUDownloadHex(hHandle, pcBinaryImage, ulImageLen,
                                   bVerify, hwndNotify));
    }

    return(DFU_ERR_HANDLE);
}

tTIDFUErr __stdcall _TIDFUErase(tTIDFUHandle hHandle, unsigned long ulStartAddr,
                               unsigned long ulEraseLen, bool bVerify,
                               HWND hwndNotify)
{
    if(pfnTIDFUErase)
    {
        return(pfnTIDFUErase(hHandle, ulStartAddr, ulEraseLen, bVerify,
                             hwndNotify));
    }

    return(DFU_ERR_HANDLE);
}

tTIDFUErr __stdcall _TIDFUBlankCheck(tTIDFUHandle hHandle,
                                    unsigned long ulStartAddr,
                                    unsigned long ulLen)
{
    if(pfnTIDFUBlankCheck)
    {
        return(pfnTIDFUBlankCheck(hHandle, ulStartAddr, ulLen));
    }

    return(DFU_ERR_HANDLE);
}

tTIDFUErr __stdcall _TIDFUUpload(tTIDFUHandle hHandle, unsigned char *pcBuffer,
                                unsigned long ulStartAddr,
                                unsigned long ulImageLen, bool bRaw,
                                HWND hwndNotify)
{
    if(pfnTIDFUUpload)
    {
        return(pfnTIDFUUpload(hHandle, pcBuffer, ulStartAddr, ulImageLen,
                              bRaw, hwndNotify));
    }

    return(DFU_ERR_HANDLE);
}

tTIDFUErr __stdcall _TIDFUStatusGet(tTIDFUHandle hHandle, tDFUStatus *pStatus)
{
    if(pfnTIDFUStatusGet)
    {
        return(pfnTIDFUStatusGet(hHandle, pStatus));
    }

    return(DFU_ERR_HANDLE);
}

tTIDFUErr __stdcall _TIDFUModeSwitch(tTIDFUHandle hHandle)
{
    if(pfnTIDFUStatusGet)
    {
        return(pfnTIDFUModeSwitch(hHandle));
    }

    return(DFU_ERR_HANDLE);
}

char * __stdcall _TIDFUErrorStringGet(tTIDFUErr eError)
{
    if(pfnTIDFUErrorStringGet)
    {
        return(pfnTIDFUErrorStringGet(eError));
    }

    return("Driver not installed");
}

//
// End of File
//

