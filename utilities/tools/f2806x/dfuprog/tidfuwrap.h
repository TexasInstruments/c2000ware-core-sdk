//*****************************************************************************
//
// TIDFUwrap.h : A thin wrapper over the TIDFU.dll library allowing it to be
//               loaded dynamically rather than statically linking to its .lib
//               file.
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

#ifndef __TIDFUWRAP_H__
#define __TIDFUWRAP_H__

//*****************************************************************************
//
// Wrapper function prototypes.
//
//*****************************************************************************
tTIDFUErr __stdcall _TIDFUInit(void);
tTIDFUErr __stdcall _TIDFUDeviceOpen(int iDeviceIndex,
                                    tTIDFUDeviceInfo *psDevInfo,
                                    tTIDFUHandle *phHandle);
tTIDFUErr __stdcall _TIDFUDeviceClose(tTIDFUHandle hHandle, bool bReset);
tTIDFUErr __stdcall _TIDFUDeviceStringGet(tTIDFUHandle hHandle,
                                         unsigned char ucStringIndex,
                                         unsigned short usLanguageID,
                                         char *pcString,
                                         unsigned short *pusStringLen);
tTIDFUErr __stdcall _TIDFUDeviceASCIIStringGet(tTIDFUHandle hHandle,
                                              unsigned char ucStringIndex,
                                              char *pcString,
                                              unsigned short *pusStringLen);
tTIDFUErr __stdcall _TIDFUParamsGet(tTIDFUHandle hHandle,
                                   tTIDFUParams *psParams);
tTIDFUErr __stdcall _TIDFUIsValidImage(tTIDFUHandle hHandle,
                                      unsigned char *pcDFUImage,
                                      unsigned long ulImageLen,
                                      bool *pbStellarisFormat);
tTIDFUErr __stdcall _TIDFUDownload(tTIDFUHandle hHandle,
                                  unsigned char *pcDFUImage,
                                  unsigned long ulImageLen, bool bVerify,
                                  bool bIgnoreIDs, HWND hwndNotify);
tTIDFUErr __stdcall _TIDFUDownloadBin(tTIDFUHandle hHandle,
                                     unsigned char *pcBinaryImage,
                                     unsigned long ulImageLen,
                                     unsigned long ulStartAddr,
                                     bool bVerify, HWND hwndNotify);
tTIDFUErr __stdcall _TIDFUDownloadHex(tTIDFUHandle hHandle, 
	                                  unsigned char *pcBinaryImage,
                                      unsigned long ulImageLen,
                                      bool bVerify, HWND hwndNotify);
tTIDFUErr __stdcall _TIDFUErase(tTIDFUHandle hHandle, unsigned long ulStartAddr,
                               unsigned long ulEraseLen, bool bVerify,
                               HWND hwndNotify);
tTIDFUErr __stdcall _TIDFUBlankCheck(tTIDFUHandle hHandle,
                                    unsigned long ulStartAddr,
                                    unsigned long ulLen);
tTIDFUErr __stdcall _TIDFUUpload(tTIDFUHandle hHandle, unsigned char *pcBuffer,
                                unsigned long ulStartAddr,
                                unsigned long ulImageLen, bool bRaw,
                                HWND hwndNotify);
tTIDFUErr __stdcall _TIDFUStatusGet(tTIDFUHandle hHandle, tDFUStatus *pStatus);
tTIDFUErr __stdcall _TIDFUModeSwitch(tTIDFUHandle hHandle);
char * __stdcall _TIDFUErrorStringGet(tTIDFUErr eError);

#endif

//
// End of File
//

