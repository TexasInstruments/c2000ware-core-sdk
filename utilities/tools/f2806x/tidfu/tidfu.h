//*****************************************************************************
//
// TIDFU.h : main header file for the TI Device Firmware Upgrade DLL
//
// Copyright (c) 2008-2011 Texas Instruments Incorporated.  All rights reserved.
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
// This is part of revision 7611 of the TI Firmware Development Package.
//
//*****************************************************************************

#ifdef __cplusplus

#pragma once

#endif

#include "resource.h"        // main symbols

#ifdef __cplusplus
//
// Functions exported by this DLL.
//
extern "C" {
#endif

//****************************************************************************
//
// Error codes returned by various API functions.
//
//****************************************************************************
typedef enum
{
    DFU_ERR_VERIFY_FAIL     = -14,
    DFU_ERR_CANT_VERIFY     = -13,
    DFU_ERR_DNLOAD_FAIL     = -12,
    DFU_ERR_STALL           = -11,
    DFU_ERR_TIMEOUT         = -10,
    DFU_ERR_DISCONNECTED    = -9,
    DFU_ERR_INVALID_SIZE    = -8,
    DFU_ERR_INVALID_ADDR    = -7,
    DFU_ERR_INVALID_FORMAT  = -6,
    DFU_ERR_UNSUPPORTED     = -5,
    DFU_ERR_UNKNOWN         = -4,
    DFU_ERR_NOT_FOUND       = -3,
    DFU_ERR_MEMORY          = -2,
    DFU_ERR_HANDLE          = -1,
    DFU_OK = 0,
}
tTIDFUErr;

//*****************************************************************************
//
// The current error status of the DFU device.  These values are reported to
// the host in response to a USBD_DFU_REQUEST_GETSTATUS request and may be
// queried by calling TIDFUGetStatus().
//
//*****************************************************************************
typedef enum
{
   STATUS_OK = 0,
   STATUS_ERR_TARGET,
   STATUS_ERR_FILE,
   STATUS_ERR_WRITE,
   STATUS_ERR_ERASE,
   STATUS_ERR_CHECK_ERASED,
   STATUS_ERR_PROG,
   STATUS_ERR_VERIFY,
   STATUS_ERR_ADDRESS,
   STATUS_ERR_NOTDONE,
   STATUS_ERR_FIRMWARE,
   STATUS_ERR_VENDOR,
   STATUS_ERR_USBR,
   STATUS_ERR_POR,
   STATUS_ERR_UNKNOWN,
   STATUS_ERR_STALLEDPKT
}
tDFUStatus;

//*****************************************************************************
//
// The size of the pcPartNumber array in tTIDFUDeviceInfo.  This field contains
// a NULL terminated ASCII string containing the target part number in the
// form "lm3sxxxx" where "xxxx" is the 4 character part number.  In cases where
// the part number can be represented using hexadecimal digits, it will also be
// encoded into the ulPartNumber field (which is left in the structure for
// backwards compatibility even though recent part numbers break the assumption
// that the part number can be encoded using hex).
//
//*****************************************************************************
#define NUM_PART_STRING_CHARS 10

//****************************************************************************
//
// Device information as returned by TIDFUDeviceOpen().
//
//****************************************************************************
typedef struct
{
    unsigned short usVID;
    unsigned short usPID;
    unsigned short usDevice;
    unsigned short usDetachTimeOut;
    unsigned short usTransferSize;
    unsigned char  ucDFUAttributes;
    unsigned char  ucManufacturerString;
    unsigned char  ucProductString;
    unsigned char  ucSerialString;
    unsigned char  ucDFUInterfaceString;
    bool           bSupportsTIExtensions;
    bool           bDFUMode;
    unsigned long  ulPartNumber;
    char           cRevisionMajor;
    char           cRevisionMinor;
    char           pcPartNumber[NUM_PART_STRING_CHARS];
}
tTIDFUDeviceInfo;

//****************************************************************************
//
// DFU parameter information returned by TIDFUParamsGet().
//
//****************************************************************************
typedef struct
{
    unsigned short usFlashBlockSize;  // The size of a flash block in bytes.
    unsigned short usNumFlashBlocks;  // The number of blocks of flash in the
                                      // device.  Total flash size is
                                      // usNumFlashBlocks * usFlashBlockSize.
    unsigned long ulFlashTop;         // Address 1 byte above the highest
                                      // location the boot loader can access.
    unsigned long ulAppStartAddr;     // Lowest address the boot loader can
                                      // write or erase.
}
tTIDFUParams;

//****************************************************************************
//
// A handle to a DFU device.  This handle is returned from a call to
// TIDFUDeviceOpen().
//
//****************************************************************************
typedef void *tTIDFUHandle;

//****************************************************************************
//
// Bit fields used in the ucDFUAttributes field of tTIDFUDeviceInfo.
//
//****************************************************************************
#define DFU_ATTR_WILL_DETACH        0x08
#define DFU_ATTR_MANIFEST_TOLERANT  0x04
#define DFU_ATTR_CAN_UPLOAD         0x02
#define DFU_ATTR_CAN_DOWNLOAD       0x01

//****************************************************************************
//
// Windows Messages optionally sent during TIDFUDownload and TIDFUUpload.
//
//****************************************************************************

// A download operation is about to begin.  The WPARAM value provides the
// number of transfers will be required to complete the operation.
// WPARAM = transfer count, LPARAM = TIDFUHandle
#define WM_DFU_DOWNLOAD    (WM_USER + 0x200)

// An upload operation is about to begin.  The WPARAM value provides the
// number of transfers will be required to complete the operation.
// WPARAM = transfer count, LPARAM = TIDFUHandle
#define WM_DFU_UPLOAD      (WM_USER + 0x201)

// A verification cycle is beginning following a download.  The WPARAM value
// provides the number of transfers that will be required to read back the
// downloaded image to verify that it is correct.
// WPARAM = transfer count, LPARAM = TIDFUHandle
#define WM_DFU_VERIFY      (WM_USER + 0x202)

// An erase operation about to begin.  The WPARAM value provides the number of
// blocks that are to be erased.
// WPARAM = transfer count, LPARAM = TIDFUHandle
#define WM_DFU_ERASE       (WM_USER + 0x203)

// A download or upload operation has completed successfully
// WPARAM = 0, LPARAM = TIDFUHandle
#define WM_DFU_COMPLETE    (WM_USER + 0x204)

// An error was reported during the operation that was in progress.  The
// operation has been aborted.
// WPARAM = 0, LPARAM = TIDFUHandle
#define WM_DFU_ERROR       (WM_USER + 0x205)

// A download, upload, erase or verify operation is in progress.  This message
// provides information on the progress of the operation. The WPARAM parameter
// increments on each message until it reaches the value passed in the
// WM_DFU_ERASE, WM_DFU_DOWNLOAD, WM_DFU_UPLOAD or WM_DFU_VERIFY message sent
// at the start of the operation.
// WPARAM = transfers completed, LPARAM = TIDFUHandle
#define WM_DFU_PROGRESS    (WM_USER + 0x206)

//****************************************************************************
//
// Exported function prototypes.
//
//****************************************************************************
tTIDFUErr __stdcall TIDFUInit(void);
tTIDFUErr __stdcall TIDFUDeviceOpen(int iDeviceIndex,
                                    tTIDFUDeviceInfo *psDevInfo,
                                    tTIDFUHandle *phHandle);
tTIDFUErr __stdcall TIDFUDeviceClose(tTIDFUHandle hHandle, bool bReset);
tTIDFUErr __stdcall TIDFUDeviceStringGet(tTIDFUHandle hHandle,
                                         unsigned char ucStringIndex,
                                         unsigned short usLanguageID,
                                         char *pcString,
                                         unsigned short *pusStringLen);
tTIDFUErr __stdcall TIDFUDeviceASCIIStringGet(tTIDFUHandle hHandle,
                                              unsigned char ucStringIndex,
                                              char *pcString,
                                              unsigned short *pusStringLen);
tTIDFUErr __stdcall TIDFUParamsGet(tTIDFUHandle hHandle,
                                   tTIDFUParams *psParams);
tTIDFUErr __stdcall TIDFUIsValidImage(tTIDFUHandle hHandle,
                                      unsigned char *pcDFUImage,
                                      unsigned long ulImageLen,
                                      bool *pbTIFormat);
tTIDFUErr __stdcall TIDFUDownload(tTIDFUHandle hHandle,
                                  unsigned char *pcDFUImage,
                                  unsigned long ulImageLen, bool bVerify,
                                  bool bIgnoreIDs, HWND hwndNotify);
tTIDFUErr __stdcall TIDFUDownloadBin(tTIDFUHandle hHandle,
                                     unsigned char *pcBinaryImage,
                                     unsigned long ulImageLen,
                                     unsigned long ulStartAddr,
                                     bool bVerify, HWND hwndNotify);
tTIDFUErr __stdcall TIDFUDownloadHex(tTIDFUHandle hHandle, 
	                                 unsigned char *pcBinaryImage,
                                     unsigned long ulImageLen,
                                     bool bVerify, 
									 HWND hwndNotify);
tTIDFUErr __stdcall TIDFUErase(tTIDFUHandle hHandle, unsigned long ulStartAddr,
                               unsigned long ulEraseLen, bool bVerify,
                               HWND hwndNotify);
tTIDFUErr __stdcall TIDFUBlankCheck(tTIDFUHandle hHandle,
                                    unsigned long ulStartAddr,
                                    unsigned long ulLen);
tTIDFUErr __stdcall TIDFUUpload(tTIDFUHandle hHandle, unsigned char *pcBuffer,
                                unsigned long ulStartAddr,
                                unsigned long ulImageLen, bool bRaw,
                                HWND hwndNotify);
tTIDFUErr __stdcall TIDFUStatusGet(tTIDFUHandle hHandle, tDFUStatus *pStatus);
tTIDFUErr __stdcall TIDFUModeSwitch(tTIDFUHandle hHandle);
char * __stdcall TIDFUErrorStringGet(tTIDFUErr eError);

//****************************************************************************
//
// Typedefs for each of the exported functions.  This helps if applications
// want to link the DLL dynamically using LoadLibrary rather than linking
// directly to the lib file.
//
//****************************************************************************
typedef tTIDFUErr (__stdcall *tTIDFUInit)(void);
typedef tTIDFUErr (__stdcall *tTIDFUDeviceOpen)(int iDeviceIndex,
                                                tTIDFUDeviceInfo *psDevInfo,
                                                tTIDFUHandle *phHandle);
typedef tTIDFUErr (__stdcall *tTIDFUDeviceClose)(tTIDFUHandle hHandle,
                                                 bool bReset);
typedef tTIDFUErr (__stdcall *tTIDFUDeviceStringGet)(tTIDFUHandle hHandle,
                                                  unsigned char ucStringIndex,
                                                  unsigned short usLanguageID,
                                                  char *pcString,
                                                  unsigned short *pusStringLen);
typedef tTIDFUErr (__stdcall *tTIDFUDeviceASCIIStringGet)(tTIDFUHandle hHandle,
                                                  unsigned char ucStringIndex,
                                                  char *pcString,
                                                  unsigned short *pusStringLen);
typedef tTIDFUErr (__stdcall *tTIDFUParamsGet)(tTIDFUHandle hHandle,
                                               tTIDFUParams *psParams);
typedef tTIDFUErr (__stdcall *tTIDFUIsValidImage)(tTIDFUHandle hHandle,
                                                  unsigned char *pcDFUImage,
                                                  unsigned long ulImageLen,
                                                  bool *pbTIFormat);
typedef tTIDFUErr (__stdcall *tTIDFUDownload)(tTIDFUHandle hHandle,
                                              unsigned char *pcDFUImage,
                                              unsigned long ulImageLen,
                                              bool bVerify,
                                              bool bIgnoreIDs,
                                              HWND hwndNotify);
typedef tTIDFUErr (__stdcall *tTIDFUDownloadBin)(tTIDFUHandle hHandle,
                                                 unsigned char *pcBinaryImage,
                                                 unsigned long ulImageLen,
                                                 unsigned long ulStartAddr,
                                                 bool bVerify,
                                                 HWND hwndNotify);
typedef tTIDFUErr (__stdcall *tTIDFUDownloadHex)(tTIDFUHandle hHandle, 
	                                            unsigned char *pcBinaryImage,
                                                unsigned long ulImageLen,
                                                bool bVerify, 
												HWND hwndNotify);
typedef tTIDFUErr (__stdcall *tTIDFUErase)(tTIDFUHandle hHandle,
                                           unsigned long ulStartAddr,
                                           unsigned long ulEraseLen,
                                           bool bVerify,
                                           HWND hwndNotify);
typedef tTIDFUErr (__stdcall *tTIDFUBlankCheck)(tTIDFUHandle hHandle,
                                                unsigned long ulStartAddr,
                                                unsigned long ulLen);
typedef tTIDFUErr (__stdcall *tTIDFUUpload)(tTIDFUHandle hHandle,
                                            unsigned char *pcBuffer,
                                            unsigned long ulStartAddr,
                                            unsigned long ulImageLen,
                                            bool bRaw, HWND hwndNotify);
typedef tTIDFUErr (__stdcall *tTIDFUStatusGet)(tTIDFUHandle hHandle,
                                               tDFUStatus *pStatus);
typedef char * (__stdcall *tTIDFUErrorStringGet)(tTIDFUErr eError);
typedef tTIDFUErr (__stdcall *tTIDFUModeSwitch)(tTIDFUHandle hHandle);

#ifdef __cplusplus
}
#endif

//
// End of File
//

