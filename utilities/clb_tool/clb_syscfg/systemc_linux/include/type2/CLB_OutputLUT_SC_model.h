#ifndef CLB_OUTPUTLUT_H
#define CLB_OUTPUTLUT_H

#include "systemc.h"

SC_MODULE(POTENZA_CLB_OUTPUT_LUT)
{
  // ports
  sc_in<bool>        I0;
  sc_in<bool>        I1; // This will be used by COMM proc and global to directly load the counter register.
  sc_in<bool>        I2;
  sc_in<sc_uint<8> > OUTPUT_LUT_fn;
  sc_out<bool>       OUT;

  // process definitions
  void lut3_evaluate();

  SC_CTOR(POTENZA_CLB_OUTPUT_LUT)
  {
      SC_METHOD(lut3_evaluate);
      sensitive <<I0 <<I1 <<I2 ;
  }
};

#endif
