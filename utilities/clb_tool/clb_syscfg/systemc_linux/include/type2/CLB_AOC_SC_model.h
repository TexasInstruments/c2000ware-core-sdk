#ifndef CLB_AOC_H
#define CLB_AOC_H

#include "systemc.h"

SC_MODULE(POTENZA_CLB_AOC) {
  sc_in<bool>  clk;
  sc_in<bool>  boundary_in, clb_tile_output, aoc_gate_signal, aoc_release_signal;           //AOC can choose either boundary[n] or CLB tile output[n] for input
  sc_in < sc_uint<16> > aoc_mux_ctrl;                                                       //These signals control the muxes for the AOC (follows CLB_OUTPUT_COND_CTRL_n format)

  sc_out<bool>  aoc_out;                                                                    //AOC output after all 3 stages

  sc_signal<bool>  aoc_stage1_out, aoc_stage2_out, aoc_stage3_out;                          //AOC output for each stage
  sc_signal<bool>  gate_clb_output_delay, release_clb_output_delay;                         //Delayed signal for when CLB output is selected
  sc_signal<bool>  aoc_stage3_delay_out, clb_tile_output_delay;                             //AOC synchronous signals

  void aoc_clocked_logic();
  void aoc_nonclocked_logic();

  SC_CTOR(POTENZA_CLB_AOC) {
	  SC_METHOD(aoc_clocked_logic);
	  sensitive << clk.pos();
	  SC_METHOD(aoc_nonclocked_logic);
	  sensitive <<  boundary_in << clb_tile_output_delay << aoc_gate_signal << aoc_release_signal << aoc_mux_ctrl
              << aoc_stage1_out << aoc_stage2_out << aoc_stage3_out << gate_clb_output_delay << release_clb_output_delay
              << aoc_stage3_delay_out << clb_tile_output;
	}
};
#endif
