#ifndef CLB_LUT4_H
#define CLB_LUT4_H

#include "systemc.h"

SC_MODULE(POTENZA_CLB_LUT4)
{
  // ports
                      // or can be used to prevent updates in a HALTED condition.
  sc_in<bool>  I0;
  sc_in<bool>  I1; // This will be used by COMM proc and global to directly load the counter register.
  sc_in<bool>  I2;
  sc_in<bool>  I3;   /// Set to 1 for add and set to 0 for shift 
  sc_in< sc_uint<16> >  LUT4_fn;   /// Set to 1 for add and set to 0 for shift 
  sc_out<bool> OUT;

  /// Internal data storage and temporary elements used within the System C functions.

  // process definitions
  void lut4_evaluate();

  SC_CTOR(POTENZA_CLB_LUT4) {
    SC_METHOD(lut4_evaluate);
    sensitive <<I0 <<I1 <<I2 <<I3;
  }
};

#endif
