The SFO library implements Scale Factor Optimization routine to drive the micro-edge positioner (MEP) calibration
module to run SFO diagnostics and determine the appropriate MEP scale factor (number of MEP steps per coarse EPWMCLK
step) for a device at any given time. Both driverlib & bit-field based libs are added in COFF & EABI format for
legacy reasons.

FILES INCLUDED:
1. SFO lib Bit-field implementation in COFF format  - SFO_v8_fpu_lib_build_c28_coff.lib
2. SFO lib Bit-field implementation in EABI format  - SFO_v8_fpu_lib_build_c28_eabi.lib
3. Index lib for Bit-field based SFO lib            - SFO_v8_fpu_lib_build_c28.lib
4. SFO lib Driverlib implementation in COFF format  - SFO_v8_fpu_lib_build_c28_driverlib_coff.lib
5. SFO lib Driverlib implementation in EABI format  - SFO_v8_fpu_lib_build_c28_driverlib_eabi.lib
6. Index lib for Driverlib based SFO lib            - SFO_v8_fpu_lib_build_c28_driverlib.lib

INDEX LIBRARY USAGE
User can link to either Bit-field or Driverlib based Index SFO library in
their example wherein, based on the example build configuration(eabi or coff)
appropriate library will be linked.

SOFTWARE USAGE DETAILS FOR DRIVERLIB BASED SFO LIB
1. Add "Include" Files:
   Include sfo_v8.h header file in application code apart for the other device
   specific files.
   E.g. #include "sfo_v8.h"
   
2. Variable Declarations:
   The application needs to declare below variables to provide EPWM instance
   addresses used in SFO lib and to capture calibration status & output.  
   E.g. uint16_t status = SFO_INCOMPLETE;
        uint32_t MEP_ScaleFactor = 0; //scale factor value
        volatile uint32_t ePWM[(PWM_CH + 1)] = {0, EPWM1_BASE, EPWM2_BASE};
        
3. MEP_ScaleFactor Initialization:
   Prior to using the MEP_ScaleFactor variable in application code, SFO() should
   be called to drive the MEP calibration module to calculate an initial
   MEP_ScaleFactor value.
   E.g.
   while(status == SFO_INCOMPLETE)
    {
        status = SFO();
        if(status == SFO_ERROR)
        {
            //
            // SFO function returns 2 if an error occurs & # of MEP
            // steps/coarse step exceeds maximum of 255.
            //
            error();
        }
    }
    
4. Application Code
   While the application is running, fluctuations in both device temperature and supply voltage may be
   expected. To be sure that optimal Scale Factors are used for each ePWM module, the SFO function
   should be re-run periodically as part of a slower back-ground loop. Some examples of this are shown
   here. E.g.
   void main ()
   {
    int status;
    // User code
    // ePWM1, 2, 3, 4 are running in HRPWM mode
    // The status variable returns 1 once a new MEP_ScaleFactor has been
    // calculated by the MEP Calibration Module running SFO
    // diagnostics.
    status = SFO();
    if(status == SFO_ERROR)
    {
     //
     // SFO function returns 2 if an error occurs & # of
     // MEP steps/coarse step exceeds maximum of 255.
     //
     error();
    }
   }
   

SOFTWARE USAGE DETAILS FOR BIT-FIELD BASED SFO LIB
1. Add "Include" Files:
   Include sfo_v8.h header file in application code apart for the other device
   specific files.
   E.g. #include "sfo_v8.h"
   
2. Variable Declarations:
   The application needs to declare below variables to provide EPWM instance
   addresses used in SFO lib and to capture calibration status & output.  
   E.g. Uint16 status = SFO_INCOMPLETE; 
        int MEP_ScaleFactor = 0; //scale factor value
        volatile struct EPWM_REGS *ePWM[] = {0, &EPwm1Regs, &EPwm2Regs};
        
3. MEP_ScaleFactor Initialization:
   Refer to Driverlib section
   
4. Application Code
   Refer to Driverlib section