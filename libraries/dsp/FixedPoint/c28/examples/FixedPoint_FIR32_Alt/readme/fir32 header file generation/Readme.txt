a)	Run the script "C28xFixedPointLib_FIR.m" in MATLAB
b)  It will ask you to choose between 16 and 32-bit operation, choose the first 
    option
c)  It will then request the size of the input - this is used during the test phase
    when it will generate a test signal of this size
d)  Find and alter these values per your needs
      samplingFreq 
      attenStop    
      attenPass    
      freqPass     
      freqStop     
e)  The script will list out the different design methods available and ask for a 
    choice. It then proceeds to generate a low pass filter that matches these 
    constraints using the fdesign.lowpass(). The user may choose to implement a
    different filter: bandpass, bandstop or highpass using the fdesign class with
    the appropriate arguments (please see the help menu in MATLAB for more details
    on what parameters are required for the different class objects)\
f)  It will then create a mex function that takes the input, applies the filter
    and generates the output. It proceeds to write these arrays, in the chosen fixed 
    point format, to data_input.txt, coeffs.txt and data_output.txt respectively.
g)  You may use the coeffs.txt file in your code as follows
    const int32_t coeffs[SIZE] = {
       #include "coeffs.txt"
    }
