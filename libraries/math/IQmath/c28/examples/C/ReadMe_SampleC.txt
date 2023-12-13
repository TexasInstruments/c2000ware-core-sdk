        IQ math Sample C Program
        =========================

NOTE; The example project uses memory protected by the 
      Code Security Module (CSM).  Make sure the CSM is 
      unlocked before you load the project.  One quick way
      to do this on an erased device is to open a memory
      window to the CSM password locations.  If these locations
      read back 0xFFFF (or non-zero), then the CSM is unlocked:
      
      Device    Password locations
      2812:     0x3F7FF8 - 0x3F7FFF
      2808:     0x3F7FF8 - 0x3F7FFF
      2833x:    0x33FFF8 - 0x33FFFF
      2823x:    0x33FFF8 - 0x33FFFF

Description:
--------------------------------------------------------------
This sample program generates two sine waves called X and Y.
It will then calculate the normalized magnitude and phase of 
the two waveforms using the following formulas:

        Mag   = sqrt(X^2 + Y^2)/sqrt(GainX^2 + GainY^2)
        Phase = (long) (atan2PU(X,Y) * 360)

The program will prompt the user to change the gain and 
frequency of the X and Y waveforms.

The default Q value used is 24. This gives a numerical range
of:

        IQ24 range = -128.0 to 127.999 999 94

To avoid saturation of the Mag value and other calculations,
the following max values are recommended for the user input:

        GainX max = 127.999 999 94/2 = 63.999 999 97
        FreqX max = 127.999 999 94
        GainY max = 127.999 999 94/2 = 63.999 999 97
        FreqY max = 127.999 999 94
        
In addition, a simple exponential waveform is created.

Instructions:
--------------------------------------------------------------
1. Invoke CCS

2. Load the project appropriate for your device.
   The projects are in the "projects" folder.

         Configure the graph displays for the following plots:

         Name                  Address          Size  Q value
         --------------------  ---------------  ----  -------
         X waveform            &Dlog.Xwaveform   64   24
         Y waveform            &Dlog.Xwaveform   64   24
         Normalized Magnitude  &Dlog.Mag         64   24
         Normalized Phase      &Dlog.Phase       64   *
         Exponential           &Dlog.Exp         64   24

         Note: You can also use the GlobalQ variable name
               for the Q value setting.
               * Phase is an integer (long)

3. Load program file 

4. Run. 

5. The program will prompt the user to select the X and Y
   waveform Gain and Freq ratios (default set at 1.0). The
   equations used are:

       X = GainX * sin(X + FreqX*Step)
       Y = GainY * sin(Y + FreqY*Step)

       Step = 0.314159265 = PI/10
   
6. The GLOBAL_Q value used by default is 24. You can change this 
   value and see the effects. The waveform shapes should remain 
   the same until effects like overflow conditions start to 
   impact the calculations. You will need to recompile the
   program when changing this value.

   Note: The Q value in the X, Y and Mag graph windows needs
         to be changed to match. The Phase display is in 
         integer format so it doesn't need changing. 
--------------------------------------------------------------
Have fun, no more.
