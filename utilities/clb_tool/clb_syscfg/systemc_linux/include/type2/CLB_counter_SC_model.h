#ifndef CLB_COUNTER_H
#define CLB_COUNTER_H

#include <iostream>
#include "systemc.h"

SC_MODULE(POTENZA_CLB_COUNTER)
{
  // ports
  sc_in<bool>         clk;
  sc_in<bool>         reset;                // Keep this a active high reset. This is a logic generated reset
  sc_in<bool>         global_clk_en;        // This is a signal that allows running the counter at a scaled down frequency.
                                            // or can be used to prevent updates in a HALTED condition.
  sc_in<bool>         event;
  sc_in<bool>         glbl_load_en;         // This will be used by COMM proc and global to directly load the counter register.
  sc_in<sc_uint<32> > event_load_val;
  sc_in<bool>         glbl_en;
  sc_in<bool>         add_shift_mode;       // Set to 1 for add and set to 0 for shift
  sc_in<bool>         add_shift_on_event_en;// Set to 1 to enable the add/shift on event
  sc_in<bool>         add_shift_dir;        // Set to 1 for add and left shift. Set to 0 for subtract and right shift.
  sc_in<bool>         glbl_rst_n;           // This is a global reset
  sc_in<bool>         mode0;
  sc_in<bool>         mode1;
  sc_in<bool>         match_en;
  sc_in<sc_uint<32> > match1_val;           // These are dummy meant only for SystemC simulation
  sc_in<sc_uint<32> > match2_val;           // User has to be able to define these values in SystemC and simulate.
                                            // In Silicon, the match1 and 2 are either loaded by indirect register accesses or by HLC
                                            // Load these values into the match1 and match2 registers during a system reset.
  sc_in<bool>         glbl_serializer_mode;

  sc_in<bool> lfsr_mode;
  sc_in<bool> match1_tap_en;
  sc_in<sc_uint<5> > match1_tap;
  sc_in<bool> match2_tap_en;
  sc_in<sc_uint<5> > match2_tap;

  sc_in<sc_uint<32> > hlc_count_load_val;   // In RTL, this is physically same as the event_load_val.
  sc_in<bool>         hlc_count_load_en;
  sc_in<bool>         hlc_match1_load_en;
  sc_in<bool>         hlc_match2_load_en;

  // These will be outputs
  sc_out<sc_uint<32> >count_out;
  sc_out<sc_uint<32> >match1_reg_out;
  sc_out<sc_uint<32> >match2_reg_out;
  sc_out<bool>        count_zero;
  sc_out<bool>        count_match1;
  sc_out<bool>        count_match2;

  /// Internal data storage and temporary elements used within the System C functions.
  sc_uint<32>         counter_REG_SIG, match1_REG_SIG, match2_REG_SIG;
  bool                event_dly_REG_SIG;

  // process definitions
  void counter_logic();

  SC_CTOR(POTENZA_CLB_COUNTER)
  {
      SC_METHOD(counter_logic);
      sensitive << clk.pos();
  }
};

#endif
