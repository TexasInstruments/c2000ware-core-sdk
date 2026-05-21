// TI File $Revision: /main/4 $
// Checkin $Date: March 25, 2011   10:55:12 $
//###########################################################################
//
// FILE:   HCCal_Type0_V1.H
//
// TITLE:  HRCAP Calibration Library Interface Header
//
//
//###########################################################################
//
//  Ver | dd mmm yyyy | Who  | Description of changes
// =====|=============|======|===============================================
//  0.01| 12 May 2009 | TI   | New module
//  0.50| 11 Feb 2011 | TI   | Update to Library
//###########################################################################
// $TI Release: $
// $Release Date:  $
//###########################################################################

//============================================================================
// Description:		This header provides the function call interface
// 			        for the HRCAP calibration library
//============================================================================


//============================================================================
// Multiple include Guard
//============================================================================
#ifndef _HCCal_Type0_V1_H
#define _HCCal_Type0_V1_H

//============================================================================
// C++ namespace
//============================================================================
#ifdef __cplusplus
extern "C" {
#endif

//============================================================================
// Function prototypes for HRCAP CAL
//============================================================================
extern Uint32 HighPulseWidth0 (Uint16 *ptrHRCAPmodule);
extern Uint32 HighPulseWidth1 (Uint16 *ptrHRCAPmodule);
extern Uint32 LowPulseWidth0 (Uint16 *ptrHRCAPmodule);
extern Uint32 PeriodWidthRise0 (Uint16 *ptrHRCAPmodule);
extern Uint32 PeriodWidthFall0 (Uint16 *ptrHRCAPmodule);
extern Uint16 HRCAP_Cal(Uint16 HRCapModule, Uint16 PLLClk, volatile struct EPWM_REGS *ePWMModule);       // HRCAP Calibration Function

//============================================================================
// Useful Defines when Using HCCAL FUNCTIONS
//============================================================================
#define HCCAL_IN_PROGRESS 0
#define HCCAL_ERROR       1
#define HCCAL_COMPLETE    2


//============================================================================
// Multiple include Guard
//============================================================================
#endif // End: Multiple include Guard

//============================================================================
// C++ namespace
//============================================================================
#ifdef __cplusplus
}
#endif /* extern "C" */
