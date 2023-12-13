#ifndef CLB_FSM_H
#define CLB_FSM_H

#include "systemc.h"


SC_MODULE(TENOR_CLB_FSM)
{
  // ports
                   
  sc_in<bool>  clk;
  sc_in<bool>  glbl_en;
  sc_in<bool>  glbl_rst_n;

  sc_in<bool>  e0;
  sc_in<bool>  e1;
  sc_in<bool>  xe0;
  sc_in<bool>  xe1;
  sc_in<bool>  EXT_SEL0;
  sc_in<bool>  EXT_SEL1;

  sc_in <sc_uint<16> > S0_fn;
  sc_in <sc_uint<16> > S1_fn;
  sc_in <sc_uint<16> > OUT_LUT_fn;

  sc_out<bool> S0;
  sc_out<bool> S1;
  sc_out<bool> OUT;

  sc_signal <bool> S0_REG, S1_REG;

  /// Internal data storage and temporary elements used within the System C functions.

  // process definitions
  void fsm_S0_evaluate();
  void fsm_S1_evaluate();
  void fsm_OUT_evaluate();

  SC_CTOR(TENOR_CLB_FSM) {
	SC_METHOD(fsm_S0_evaluate);
    sensitive << clk.pos();
	SC_METHOD(fsm_S1_evaluate);
    sensitive << clk.pos();
	SC_METHOD(fsm_OUT_evaluate);
    /** Old code  sensitive <<E0 <<E1 <<EXTRA_E0 <<EXTRA_E1 << clk.pos(); **/
	// Modifying to add S0_REG and S1_REG to sensitivity list - This was a bug - May 14 2015 - Venki
    sensitive <<e0 <<e1 <<xe0 <<xe1 << S0_REG << S1_REG << clk.pos();
  }
};

#endif
