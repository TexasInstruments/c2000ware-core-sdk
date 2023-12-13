#include <string>
#include "../type2/CLB_FSM_SC_model.h"

using namespace std;

void POTENZA_CLB_FSM::fsm_S0_evaluate()
{

  unsigned int glbl_en_sig, glbl_rst_n_sig;
  unsigned int S0_sig, S1_sig;
  unsigned int E0_sig, E1_sig;

  unsigned int s0_fn_val;
  unsigned int index, s0_nxt_value;

  s0_fn_val  = S0_fn.read().to_uint();

  S0_sig = S0_REG.read();
  S1_sig = S1_REG.read();
  E0_sig = e0.read();
  E1_sig = e1.read();

  glbl_en_sig = glbl_en.read();
  glbl_rst_n_sig = glbl_rst_n.read();


  if ( (glbl_en_sig == false) || (glbl_rst_n_sig == false) ) {
	  S0.write(false);
	  S0_REG.write(false);
	  return;
  }

  	index = (E1_sig<<3) | (E0_sig<<2) | (S1_sig<<1) | S0_sig;
	s0_nxt_value = (s0_fn_val>>index) & 0x1;


  if (s0_nxt_value == 1) {
	  S0.write(true);
	  S0_REG.write(true);
  }
  else {
	  S0.write(false);
	  S0_REG.write(false);
  }


}


void POTENZA_CLB_FSM::fsm_S1_evaluate()
{

  unsigned int glbl_en_sig, glbl_rst_n_sig;
  unsigned int S0_sig, S1_sig;
  unsigned int E0_sig, E1_sig;

  unsigned int s1_fn_val;
  unsigned int index, s1_nxt_value;

  s1_fn_val  = S1_fn.read().to_uint();

  S0_sig = S0_REG.read();
  S1_sig = S1_REG.read();
  E0_sig = e0.read();
  E1_sig = e1.read();

  glbl_en_sig = glbl_en.read();
  glbl_rst_n_sig = glbl_rst_n.read();


  if ( (glbl_en_sig == false) || (glbl_rst_n_sig == false) ) {
	  S1.write(false);
	  S1_REG.write(false);
	  return;
  }

  	index = (E1_sig<<3) | (E0_sig<<2) | (S1_sig<<1) | S0_sig;
	s1_nxt_value = (s1_fn_val>>index) & 0x1;


  if (s1_nxt_value == 1) {
	  S1.write(true);
	  S1_REG.write(true);
  }
  else {
	  S1.write(false);
	  S1_REG.write(false);
  }

}

void POTENZA_CLB_FSM::fsm_OUT_evaluate()
{

  unsigned int glbl_en_sig, glbl_rst_n_sig;
  unsigned int S0_sig, S1_sig;
  unsigned int E0_sig, E1_sig;
  unsigned int E2_sig, E3_sig;
  unsigned int EXT_SEL0_sig, EXT_SEL1_sig;

  unsigned int e2_val, e3_val;
  unsigned int out_fn_val;
  unsigned int index, out_value;

  out_fn_val = OUT_LUT_fn.read().to_uint();

  S0_sig = S0_REG.read();
  S1_sig = S1_REG.read();
  E0_sig = e0.read();
  E1_sig = e1.read();
  E2_sig = xe0.read();
  E3_sig = xe1.read();
  EXT_SEL0_sig = EXT_SEL0.read();
  EXT_SEL1_sig = EXT_SEL1.read();

  glbl_en_sig = glbl_en.read();
  glbl_rst_n_sig = glbl_rst_n.read();


  if ( (glbl_en_sig == false) || (glbl_rst_n_sig == false) ) {
	  OUT.write(false);
	  return;
  }

   if (EXT_SEL0_sig == 1) 
	   e2_val = E2_sig;
   else
	   e2_val = S0_sig;

   if (EXT_SEL1_sig == 1) 
	   e3_val = E3_sig;
   else
	   e3_val = S1_sig;

  	index = (E1_sig<<3) | (E0_sig<<2) | (e3_val<<1) | e2_val;
	out_value = (out_fn_val>>index) & 0x1;


   if (out_value == 1) {
	  OUT.write(true);
  }
  else {
	  OUT.write(false); 
  }


}
