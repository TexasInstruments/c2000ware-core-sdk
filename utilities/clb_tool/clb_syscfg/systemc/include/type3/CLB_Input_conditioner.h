#ifndef CLB_INPUT_COND_H
#define CLB_INPUT_COND_H

#include "systemc.h"

SC_MODULE(CLB_INPUT_CONDITIONER) {


  sc_in<bool>  clk;

  sc_in<bool>  in0;
  sc_in<bool>  in1;
  sc_in<bool>  in2;
  sc_in<bool>  in3;
  sc_in<bool>  in4;
  sc_in<bool>  in5;
  sc_in<bool>  in6;
  sc_in<bool>  in7;

  sc_in < sc_uint<32> > in0_ctrl; // These ports will be hidden and set through properties.
  sc_in < sc_uint<32> > in1_ctrl;
  sc_in < sc_uint<32> > in2_ctrl;
  sc_in < sc_uint<32> > in3_ctrl;
  sc_in < sc_uint<32> > in4_ctrl;
  sc_in < sc_uint<32> > in5_ctrl;
  sc_in < sc_uint<32> > in6_ctrl;
  sc_in < sc_uint<32> > in7_ctrl;

  sc_out<bool>  out0;
  sc_out<bool>  out1;
  sc_out<bool>  out2;
  sc_out<bool>  out3;
  sc_out<bool>  out4;
  sc_out<bool>  out5;
  sc_out<bool>  out6;
  sc_out<bool>  out7;

  sc_signal <bool> in0_dly1_REG, in0_dly2_REG, in0_dly3_REG, in0_dly4_REG, in0_pipe0_REG, in0_pipe1_REG, in0_dly5_REG;
  sc_signal <bool> in1_dly1_REG, in1_dly2_REG, in1_dly3_REG, in1_dly4_REG, in1_pipe0_REG, in1_pipe1_REG, in1_dly5_REG;
  sc_signal <bool> in2_dly1_REG, in2_dly2_REG, in2_dly3_REG, in2_dly4_REG, in2_pipe0_REG, in2_pipe1_REG, in2_dly5_REG;
  sc_signal <bool> in3_dly1_REG, in3_dly2_REG, in3_dly3_REG, in3_dly4_REG, in3_pipe0_REG, in3_pipe1_REG, in3_dly5_REG;
  sc_signal <bool> in4_dly1_REG, in4_dly2_REG, in4_dly3_REG, in4_dly4_REG, in4_pipe0_REG, in4_pipe1_REG, in4_dly5_REG;
  sc_signal <bool> in5_dly1_REG, in5_dly2_REG, in5_dly3_REG, in5_dly4_REG, in5_pipe0_REG, in5_pipe1_REG, in5_dly5_REG;
  sc_signal <bool> in6_dly1_REG, in6_dly2_REG, in6_dly3_REG, in6_dly4_REG, in6_pipe0_REG, in6_pipe1_REG, in6_dly5_REG;
  sc_signal <bool> in7_dly1_REG, in7_dly2_REG, in7_dly3_REG, in7_dly4_REG, in7_pipe0_REG, in7_pipe1_REG, in7_dly5_REG;

  void input_filter_fn();
  void input_final_select();

  SC_CTOR(CLB_INPUT_CONDITIONER) {
	  SC_METHOD(input_filter_fn);
	  sensitive << clk.pos();
	  SC_METHOD(input_final_select);
	  sensitive << in0 << in1 <<in2 <<in3 <<in4 <<in5 <<in6 <<in7
			 <<in0_dly1_REG <<in1_dly1_REG<<in2_dly1_REG<<in3_dly1_REG<<in4_dly1_REG<<in5_dly1_REG<<in6_dly1_REG<< in7_dly1_REG
			 <<in0_dly2_REG <<in1_dly2_REG<<in2_dly2_REG<<in3_dly2_REG<<in4_dly2_REG<<in5_dly2_REG<<in6_dly2_REG<< in7_dly2_REG
			 <<in0_dly3_REG <<in1_dly3_REG<<in2_dly3_REG<<in3_dly3_REG<<in4_dly3_REG<<in5_dly3_REG<<in6_dly3_REG<< in7_dly3_REG
			 <<in0_dly4_REG <<in1_dly4_REG<<in2_dly1_REG<<in3_dly4_REG<<in4_dly4_REG<<in5_dly4_REG<<in6_dly4_REG<< in7_dly4_REG
			 <<in0_pipe0_REG <<in1_pipe0_REG<<in2_pipe0_REG<<in3_pipe0_REG<<in4_pipe0_REG<<in5_pipe0_REG<<in6_pipe0_REG<< in7_pipe0_REG
			 <<in0_pipe1_REG <<in1_pipe1_REG<<in2_pipe1_REG<<in3_pipe1_REG<<in4_pipe1_REG<<in5_pipe1_REG<<in6_pipe1_REG<< in7_pipe1_REG
			  << clk.pos();
	}
};

void CLB_INPUT_CONDITIONER::input_filter_fn() {

    sc_uint<32>   in0_ctrl_val;    
    sc_uint<32>   in1_ctrl_val;    
    sc_uint<32>   in2_ctrl_val;    
    sc_uint<32>   in3_ctrl_val;    
    sc_uint<32>   in4_ctrl_val;    
    sc_uint<32>   in5_ctrl_val;    
    sc_uint<32>   in6_ctrl_val;    
    sc_uint<32>   in7_ctrl_val;    

	in0_ctrl_val = in0_ctrl.read();
	in1_ctrl_val = in1_ctrl.read();
	in2_ctrl_val = in2_ctrl.read();
	in3_ctrl_val = in3_ctrl.read();
	in4_ctrl_val = in4_ctrl.read();
	in5_ctrl_val = in5_ctrl.read();
	in6_ctrl_val = in6_ctrl.read();
	in7_ctrl_val = in7_ctrl.read();

	in0_dly5_REG.write(in0_dly4_REG.read());
	in1_dly5_REG.write(in1_dly4_REG.read());
	in2_dly5_REG.write(in2_dly4_REG.read());
	in3_dly5_REG.write(in3_dly4_REG.read());
	in4_dly5_REG.write(in4_dly4_REG.read());
	in5_dly5_REG.write(in5_dly4_REG.read());
	in6_dly5_REG.write(in6_dly4_REG.read());
	in7_dly5_REG.write(in7_dly4_REG.read());

	in0_dly4_REG.write(in0_dly3_REG.read());
	in1_dly4_REG.write(in1_dly3_REG.read());
	in2_dly4_REG.write(in2_dly3_REG.read());
	in3_dly4_REG.write(in3_dly3_REG.read());
	in4_dly4_REG.write(in4_dly3_REG.read());
	in5_dly4_REG.write(in5_dly3_REG.read());
	in6_dly4_REG.write(in6_dly3_REG.read());
	in7_dly4_REG.write(in7_dly3_REG.read());

	in0_dly3_REG.write(in0_dly2_REG.read());
	in1_dly3_REG.write(in1_dly2_REG.read());
	in2_dly3_REG.write(in2_dly2_REG.read());
	in3_dly3_REG.write(in3_dly2_REG.read());
	in4_dly3_REG.write(in4_dly2_REG.read());
	in5_dly3_REG.write(in5_dly2_REG.read());
	in6_dly3_REG.write(in6_dly2_REG.read());
	in7_dly3_REG.write(in7_dly2_REG.read());

	in0_dly2_REG.write(in0_dly1_REG.read());
	in1_dly2_REG.write(in1_dly1_REG.read());
	in2_dly2_REG.write(in2_dly1_REG.read());
	in3_dly2_REG.write(in3_dly1_REG.read());
	in4_dly2_REG.write(in4_dly1_REG.read());
	in5_dly2_REG.write(in5_dly1_REG.read());
	in6_dly2_REG.write(in6_dly1_REG.read());
	in7_dly2_REG.write(in7_dly1_REG.read());

	in0_dly1_REG.write(in0.read());
	in1_dly1_REG.write(in1.read());
	in2_dly1_REG.write(in2.read());
	in3_dly1_REG.write(in3.read());
	in4_dly1_REG.write(in4.read());
	in5_dly1_REG.write(in5.read());
	in6_dly1_REG.write(in6.read());
	in7_dly1_REG.write(in7.read());
	
    in0_pipe0_REG = ((in0_ctrl_val & 0x1C) == 0x4)  ? in0.read() : 	//Pipeline
		  		  	((in0_ctrl_val & 0x1C) == 0xC)  ? in0_dly2_REG.read() : 	//Pipeline with 2-cycle synchronization
		  		  	((in0_ctrl_val & 0x1C) == 0x14) ? in0_dly3_REG.read() : 0;	//Pipeline with 3-cycle synchronization
    in1_pipe0_REG = ((in1_ctrl_val & 0x1C) == 0x4)  ? in1.read() : 
		  		  	((in1_ctrl_val & 0x1C) == 0xC)  ? in1_dly2_REG.read() : 
		  		  	((in1_ctrl_val & 0x1C) == 0x14) ? in1_dly3_REG.read() : 0;
    in2_pipe0_REG = ((in2_ctrl_val & 0x1C) == 0x4)  ? in2.read() : 
		  		  	((in2_ctrl_val & 0x1C) == 0xC)  ? in2_dly2_REG.read() : 
		  		  	((in2_ctrl_val & 0x1C) == 0x14) ? in2_dly3_REG.read() : 0;
    in3_pipe0_REG = ((in3_ctrl_val & 0x1C) == 0x4)  ? in3.read() : 
		  		  	((in3_ctrl_val & 0x1C) == 0xC)  ? in3_dly2_REG.read() : 
		  		  	((in3_ctrl_val & 0x1C) == 0x14) ? in3_dly3_REG.read() : 0;
    in4_pipe0_REG = ((in4_ctrl_val & 0x1C) == 0x4)  ? in4.read() : 
		  		  	((in4_ctrl_val & 0x1C) == 0xC)  ? in4_dly2_REG.read() : 
		  		  	((in4_ctrl_val & 0x1C) == 0x14) ? in4_dly3_REG.read() : 0;
    in5_pipe0_REG = ((in5_ctrl_val & 0x1C) == 0x4)  ? in5.read() : 
		  		  	((in5_ctrl_val & 0x1C) == 0xC)  ? in5_dly2_REG.read() : 
		  		  	((in5_ctrl_val & 0x1C) == 0x14) ? in5_dly3_REG.read() : 0;
    in6_pipe0_REG = ((in6_ctrl_val & 0x1C) == 0x4)  ? in6.read() : 
		  		  	((in6_ctrl_val & 0x1C) == 0xC)  ? in6_dly2_REG.read() : 
		  		  	((in6_ctrl_val & 0x1C) == 0x14) ? in6_dly3_REG.read() : 0;
    in7_pipe0_REG = ((in7_ctrl_val & 0x1C) == 0x4)  ? in7.read() : 
		  		  	((in7_ctrl_val & 0x1C) == 0xC)  ? in7_dly2_REG.read() : 
		  		  	((in7_ctrl_val & 0x1C) == 0x14) ? in7_dly3_REG.read() : 0;
	
    in0_pipe1_REG = ((in0_ctrl_val & 0x1C) == 0x4)  ? in0_dly1_REG.read() : 
		  		  	((in0_ctrl_val & 0x1C) == 0xC)  ? in0_dly3_REG.read() : 
		  		  	((in0_ctrl_val & 0x1C) == 0x14) ? in0_dly4_REG.read() : 0;
    in1_pipe1_REG = ((in1_ctrl_val & 0x1C) == 0x4)  ? in1_dly1_REG.read() : 
		  		  	((in1_ctrl_val & 0x1C) == 0xC)  ? in1_dly3_REG.read() : 
		  		  	((in1_ctrl_val & 0x1C) == 0x14) ? in1_dly4_REG.read() : 0;
    in2_pipe1_REG = ((in2_ctrl_val & 0x1C) == 0x4)  ? in2_dly1_REG.read() : 
		  		  	((in2_ctrl_val & 0x1C) == 0xC)  ? in2_dly3_REG.read() : 
		  		  	((in2_ctrl_val & 0x1C) == 0x14) ? in2_dly4_REG.read() : 0;
    in3_pipe1_REG = ((in3_ctrl_val & 0x1C) == 0x4)  ? in3_dly1_REG.read() : 
		  		  	((in3_ctrl_val & 0x1C) == 0xC)  ? in3_dly3_REG.read() : 
		  		  	((in3_ctrl_val & 0x1C) == 0x14) ? in3_dly4_REG.read() : 0;
    in4_pipe1_REG = ((in4_ctrl_val & 0x1C) == 0x4)  ? in4_dly1_REG.read() : 
		  		  	((in4_ctrl_val & 0x1C) == 0xC)  ? in4_dly3_REG.read() : 
		  		  	((in4_ctrl_val & 0x1C) == 0x14) ? in4_dly4_REG.read() : 0;
    in5_pipe1_REG = ((in5_ctrl_val & 0x1C) == 0x4)  ? in5_dly1_REG.read() : 
		  		  	((in5_ctrl_val & 0x1C) == 0xC)  ? in5_dly3_REG.read() : 
		  		  	((in5_ctrl_val & 0x1C) == 0x14) ? in5_dly4_REG.read() : 0;
    in6_pipe1_REG = ((in6_ctrl_val & 0x1C) == 0x4)  ? in6_dly1_REG.read() : 
		  		  	((in6_ctrl_val & 0x1C) == 0xC)  ? in6_dly3_REG.read() : 
		  		  	((in6_ctrl_val & 0x1C) == 0x14) ? in6_dly4_REG.read() : 0;
    in7_pipe1_REG = ((in7_ctrl_val & 0x1C) == 0x4)  ? in7_dly1_REG.read() : 
		  		  	((in7_ctrl_val & 0x1C) == 0xC)  ? in7_dly3_REG.read() : 
		  		  	((in7_ctrl_val & 0x1C) == 0x14) ? in7_dly4_REG.read() : 0;
}

void CLB_INPUT_CONDITIONER::input_final_select() {
	bool in0_final, in0_final_dly, in0_pos, in0_neg, in0_tog, in0_out_val;
	bool in1_final, in1_final_dly, in1_pos, in1_neg, in1_tog, in1_out_val;
	bool in2_final, in2_final_dly, in2_pos, in2_neg, in2_tog, in2_out_val;
	bool in3_final, in3_final_dly, in3_pos, in3_neg, in3_tog, in3_out_val;
	bool in4_final, in4_final_dly, in4_pos, in4_neg, in4_tog, in4_out_val;
	bool in5_final, in5_final_dly, in5_pos, in5_neg, in5_tog, in5_out_val;
	bool in6_final, in6_final_dly, in6_pos, in6_neg, in6_tog, in6_out_val;
	bool in7_final, in7_final_dly, in7_pos, in7_neg, in7_tog, in7_out_val;

    sc_uint<32>   in0_ctrl_val;    
    sc_uint<32>   in1_ctrl_val;    
    sc_uint<32>   in2_ctrl_val;    
    sc_uint<32>   in3_ctrl_val;    
    sc_uint<32>   in4_ctrl_val;    
    sc_uint<32>   in5_ctrl_val;    
    sc_uint<32>   in6_ctrl_val;    
    sc_uint<32>   in7_ctrl_val;    

	in0_ctrl_val = in0_ctrl.read();
	in1_ctrl_val = in1_ctrl.read();
	in2_ctrl_val = in2_ctrl.read();
	in3_ctrl_val = in3_ctrl.read();
	in4_ctrl_val = in4_ctrl.read();
	in5_ctrl_val = in5_ctrl.read();
	in6_ctrl_val = in6_ctrl.read();
	in7_ctrl_val = in7_ctrl.read();

	if ( (in0_ctrl_val & 0x4))					//Pipeline Input (1 cycle delay)
	{
		in0_final = in0_pipe0_REG.read();
		in0_final_dly = in0_pipe1_REG.read();
	}
	else if ( (in0_ctrl_val & 0x10))			//Synchronization (3 cycle delay)
	{
		in0_final = in0_dly3_REG.read();
		in0_final_dly = in0_dly4_REG.read();
	}
	else if ( (in0_ctrl_val & 0x8))				//Synchronization (2 cycle delay)
	{
		in0_final = in0_dly2_REG.read();
		in0_final_dly = in0_dly3_REG.read();
	}
	else										//No Synchronization
	{
		in0_final = in0.read();
		in0_final_dly = in0_dly1_REG.read();
	}

	if ( (in1_ctrl_val & 0x4))
	{
		in1_final = in1_pipe0_REG.read();
		in1_final_dly = in1_pipe1_REG.read();
	}
	else if ( (in1_ctrl_val & 0x10))
	{
		in1_final = in1_dly3_REG.read();
		in1_final_dly = in1_dly4_REG.read();
	}
	else if ( (in1_ctrl_val & 0x8))
	{
		in1_final = in1_dly2_REG.read();
		in1_final_dly = in1_dly3_REG.read();
	}
	else
	{
		in1_final = in1.read();
		in1_final_dly = in1_dly1_REG.read();
	}

	if ( (in2_ctrl_val & 0x4))
	{
		in2_final = in2_pipe0_REG.read();
		in2_final_dly = in2_pipe1_REG.read();
	}
	else if ( (in2_ctrl_val & 0x10))
	{
		in2_final = in2_dly3_REG.read();
		in2_final_dly = in2_dly4_REG.read();
	}
	else if ( (in2_ctrl_val & 0x8))
	{
		in2_final = in2_dly2_REG.read();
		in2_final_dly = in2_dly3_REG.read();
	}
	else
	{
		in2_final = in2.read();
		in2_final_dly = in2_dly1_REG.read();
	}

	if ( (in3_ctrl_val & 0x4))
	{
		in3_final = in3_pipe0_REG.read();
		in3_final_dly = in3_pipe1_REG.read();
	}
	else if ( (in3_ctrl_val & 0x10))
	{
		in3_final = in3_dly3_REG.read();
		in3_final_dly = in3_dly4_REG.read();
	}
	else if ( (in3_ctrl_val & 0x8))
	{
		in3_final = in3_dly2_REG.read();
		in3_final_dly = in3_dly3_REG.read();
	}
	else
	{
		in3_final = in3.read();
		in3_final_dly = in3_dly1_REG.read();
	}

	if ( (in4_ctrl_val & 0x4))
	{
		in4_final = in4_pipe0_REG.read();
		in4_final_dly = in4_pipe1_REG.read();
	}
	else if ( (in4_ctrl_val & 0x10))
	{
		in4_final = in4_dly3_REG.read();
		in4_final_dly = in4_dly4_REG.read();
	}
	else if ( (in4_ctrl_val & 0x8))
	{
		in4_final = in4_dly2_REG.read();
		in4_final_dly = in4_dly3_REG.read();
	}
	else
	{
		in4_final = in4.read();
		in4_final_dly = in4_dly1_REG.read();
	}

	if ( (in5_ctrl_val & 0x4))
	{
		in5_final = in5_pipe0_REG.read();
		in5_final_dly = in5_pipe1_REG.read();
	}
	else if ( (in5_ctrl_val & 0x10))
	{
		in5_final = in5_dly3_REG.read();
		in5_final_dly = in5_dly4_REG.read();
	}
	else if ( (in5_ctrl_val & 0x8))
	{
		in5_final = in5_dly2_REG.read();
		in5_final_dly = in5_dly3_REG.read();
	}
	else
	{
		in5_final = in5.read();
		in5_final_dly = in5_dly1_REG.read();
	}

	if ( (in6_ctrl_val & 0x4))
	{
		in6_final = in6_pipe0_REG.read();
		in6_final_dly = in6_pipe1_REG.read();
	}
	else if ( (in6_ctrl_val & 0x10))
	{
		in6_final = in6_dly3_REG.read();
		in6_final_dly = in6_dly4_REG.read();
	}
	else if ( (in6_ctrl_val & 0x8))
	{
		in6_final = in6_dly2_REG.read();
		in6_final_dly = in6_dly3_REG.read();
	}
	else
	{
		in6_final = in6.read();
		in6_final_dly = in6_dly1_REG.read();
	}

	if ( (in7_ctrl_val & 0x4))
	{
		in7_final = in7_pipe0_REG.read();
		in7_final_dly = in7_pipe1_REG.read();
	}
	else if ( (in7_ctrl_val & 0x10))
	{
		in7_final = in7_dly3_REG.read();
		in7_final_dly = in7_dly4_REG.read();
	}
	else if ( (in7_ctrl_val & 0x8))
	{
		in7_final = in7_dly2_REG.read();
		in7_final_dly = in7_dly3_REG.read();
	}
	else
	{
		in7_final = in7.read();
		in7_final_dly = in7_dly1_REG.read();
	}


	in0_pos = ((in0_final_dly == 0) && (in0_final == 1)) ? 1 : 0;
	in1_pos = ((in1_final_dly == 0) && (in1_final == 1)) ? 1 : 0;
	in2_pos = ((in2_final_dly == 0) && (in2_final == 1)) ? 1 : 0;
	in3_pos = ((in3_final_dly == 0) && (in3_final == 1)) ? 1 : 0;
	in4_pos = ((in4_final_dly == 0) && (in4_final == 1)) ? 1 : 0;
	in5_pos = ((in5_final_dly == 0) && (in5_final == 1)) ? 1 : 0;
	in6_pos = ((in6_final_dly == 0) && (in6_final == 1)) ? 1 : 0;
	in7_pos = ((in7_final_dly == 0) && (in7_final == 1)) ? 1 : 0;

	in0_neg = ((in0_final_dly == 1) && (in0_final == 0)) ? 1 : 0;
	in1_neg = ((in1_final_dly == 1) && (in1_final == 0)) ? 1 : 0;
	in2_neg = ((in2_final_dly == 1) && (in2_final == 0)) ? 1 : 0;
	in3_neg = ((in3_final_dly == 1) && (in3_final == 0)) ? 1 : 0;
	in4_neg = ((in4_final_dly == 1) && (in4_final == 0)) ? 1 : 0;
	in5_neg = ((in5_final_dly == 1) && (in5_final == 0)) ? 1 : 0;
	in6_neg = ((in6_final_dly == 1) && (in6_final == 0)) ? 1 : 0;
	in7_neg = ((in7_final_dly == 1) && (in7_final == 0)) ? 1 : 0;

	in0_tog = (in0_pos || in0_neg);
	in1_tog = (in1_pos || in1_neg);
	in2_tog = (in2_pos || in2_neg);
	in3_tog = (in3_pos || in3_neg);
	in4_tog = (in4_pos || in4_neg);
	in5_tog = (in5_pos || in5_neg);
	in6_tog = (in6_pos || in6_neg);
	in7_tog = (in7_pos || in7_neg);

    in0_out_val = ((in0_ctrl_val & 0x3) == 0) ? in0_final : 
		  		  ((in0_ctrl_val & 0x3) == 1) ? in0_pos : 
		  		  ((in0_ctrl_val & 0x3) == 2) ? in0_neg : in0_tog;

    in1_out_val = ((in1_ctrl_val & 0x3) == 0) ? in1_final : 
		  		  ((in1_ctrl_val & 0x3) == 1) ? in1_pos : 
		  		  ((in1_ctrl_val & 0x3) == 2) ? in1_neg : in1_tog;

    in2_out_val = ((in2_ctrl_val & 0x3) == 0) ? in2_final : 
		  		  ((in2_ctrl_val & 0x3) == 1) ? in2_pos : 
		  		  ((in2_ctrl_val & 0x3) == 2) ? in2_neg : in2_tog;

    in3_out_val = ((in3_ctrl_val & 0x3) == 0) ? in3_final : 
		  		  ((in3_ctrl_val & 0x3) == 1) ? in3_pos : 
		  		  ((in3_ctrl_val & 0x3) == 2) ? in3_neg : in3_tog;

    in4_out_val = ((in4_ctrl_val & 0x3) == 0) ? in4_final : 
		  		  ((in4_ctrl_val & 0x3) == 1) ? in4_pos : 
		  		  ((in4_ctrl_val & 0x3) == 2) ? in4_neg : in4_tog;

    in5_out_val = ((in5_ctrl_val & 0x3) == 0) ? in5_final : 
		  		  ((in5_ctrl_val & 0x3) == 1) ? in5_pos : 
		  		  ((in5_ctrl_val & 0x3) == 2) ? in5_neg : in5_tog;

    in6_out_val = ((in6_ctrl_val & 0x3) == 0) ? in6_final : 
		  		  ((in6_ctrl_val & 0x3) == 1) ? in6_pos : 
		  		  ((in6_ctrl_val & 0x3) == 2) ? in6_neg : in6_tog;

    in7_out_val = ((in7_ctrl_val & 0x3) == 0) ? in7_final : 
		  		  ((in7_ctrl_val & 0x3) == 1) ? in7_pos : 
		  		  ((in7_ctrl_val & 0x3) == 2) ? in7_neg : in7_tog;

     out0.write(in0_out_val);
     out1.write(in1_out_val);
     out2.write(in2_out_val);
     out3.write(in3_out_val);
     out4.write(in4_out_val);
     out5.write(in5_out_val);
     out6.write(in6_out_val);
     out7.write(in7_out_val);
}
#endif
