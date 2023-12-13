#include <iostream>
#include <systemc.h>
#include "../type2/CLB_HLC_SC_model.h"
#include "../type2/hlc_c_model_oper.h"

POTENZA_CLB_HLC::POTENZA_CLB_HLC(sc_core::sc_module_name _nm,
								 unsigned long R0_init_param,
								 unsigned long R1_init_param,
								 unsigned long R2_init_param,
								 unsigned long R3_init_param,
                 unsigned long fifo0_init,
                 unsigned long fifo1_init,
                 unsigned long fifo2_init,
                 unsigned long fifo3_init,
                 unsigned long fifo0_refill,
                 unsigned long fifo1_refill,
                 unsigned long fifo2_refill,
                 unsigned long fifo3_refill):
			sc_module(_nm)
 {
    SC_METHOD(hlc_logic);
    sensitive << P_clk.pos() ;
    SC_METHOD(hlc_mem_init);
    sensitive << P_rst_n.neg() ;

	  lcl_R0_init = R0_init_param;
	  lcl_R1_init = R1_init_param;
	  lcl_R2_init = R2_init_param;
	  lcl_R3_init = R3_init_param;

    //The FIFO refill values act as additional elements in the same FIFO
    //for the simulation, meaning they need to be below the init values
    //in terms of depth (once init values are all pulled, then refill
    //values become available)
    hlc_pull_fifo[0] = fifo3_refill;
    hlc_pull_fifo[1] = fifo2_refill;
    hlc_pull_fifo[2] = fifo1_refill;
    hlc_pull_fifo[3] = fifo0_refill;

    hlc_pull_fifo[4] = fifo3_init;
    hlc_pull_fifo[5] = fifo2_init;
    hlc_pull_fifo[6] = fifo1_init;
    hlc_pull_fifo[7] = fifo0_init;

    pull_fifo_output[0] = hlc_pull_fifo[7];
    pull_fifo_output[1] = hlc_pull_fifo[6];
    pull_fifo_output[2] = hlc_pull_fifo[5];
    pull_fifo_output[3] = hlc_pull_fifo[4];

    for(int i = 0; i < 3; i++)
    {
      hlc_push_fifo[i] = 0;
    }
}

void POTENZA_CLB_HLC::hlc_mem_init(void) {

	  int i = 0;
    for (i=0; i<32; i++)
	  {
		  INSTR_ARRAY[i] = hlc_instructions[i].read();
	  }
	
    hlc_fifo_read_ptr = 7;
    hlc_fifo_write_ptr = 0;
		comm_R0 = lcl_R0_init;
		comm_R1 = lcl_R1_init;
		comm_R2 = lcl_R2_init;
		comm_R3 = lcl_R3_init;
}

void POTENZA_CLB_HLC::hlc_logic(void) {
  int i;
  unsigned int event_mux_sel[4];
  unsigned int event_mux_alt[4];
  sc_uint<8> output_event_wire_local_reg_7_0;
  sc_uint<8> output_event_wire_local_reg_15_8;
  sc_uint<8> output_event_wire_local_reg_23_16;
  sc_uint<8> output_event_wire_local_reg_31_24;

  pull_fifo_refill_enable = fifo_refill_enable.read();
  rst_n = P_rst_n.read();
  counter_in_0 = P_counter_in_0.read().to_uint();
  counter_in_1 = P_counter_in_1.read().to_uint();
  counter_in_2 = P_counter_in_2.read().to_uint();
  EVENT_MUX_SEL_0 = e0.read().to_uint();
  EVENT_MUX_SEL_1 = e1.read().to_uint();
  EVENT_MUX_SEL_2 = e2.read().to_uint();
  EVENT_MUX_SEL_3 = e3.read().to_uint();

  EVENT_MUX_ALT_0 = ae0.read();
  EVENT_MUX_ALT_1 = ae1.read();
  EVENT_MUX_ALT_2 = ae2.read();
  EVENT_MUX_ALT_3 = ae3.read();

   if (rst_n == 0) {
          for (i=0; i<=3; i++) {
        	  REG_event_dly[i] = 0;
        	  event_pending_REG[i] = 0;
          }
	  current_instr_PTR = 0;
          instr_active_T = 0;
		  R0_write_en = 0;
		  R1_write_en = 0;
		  R2_write_en = 0;
		  R3_write_en = 0;
		  dummy_state_T = 0;

   } else {
          for (i=0; i<=3; i++)
               REG_event_dly[i] = active_event_in[i];

	   dest_port_DLY = dest_port;
	   current_instr_PTR = next_instr_PTR;
       instr_active_T   = instr_active_next_state;
       dummy_state_T = next_cycle_dummy_state;

           if (R0_write_en)
             comm_R0 =   comm_write_bus;
           if (R1_write_en)
             comm_R1 =   comm_write_bus;
           if (R2_write_en)
             comm_R2 =   comm_write_bus;
           if (R3_write_en)
             comm_R3 =   comm_write_bus;

	    for (i = 0; i<=3; i=i+1) {
       	         if (set_pending_event[i] == 1)
              	      event_pending_REG[i] = 1;
         	 else if  (clr_pending_event[i]  == 1)
                     event_pending_REG[i] = 0;
            }
    }

    for (i = 0; i<=7; i=i+1) {
			output_event_wire_local_reg_7_0[i] = clb_result_in[i].read();
			output_event_wire_local_reg_15_8[i] = ~clb_result_in[i].read();
			output_event_wire_local_reg_23_16[i] = clb_async_result_in[i].read();
			output_event_wire_local_reg_31_24[i] = ~clb_async_result_in[i].read();
    }

    output_event_wire = (((sc_uint<8>)output_event_wire_local_reg_31_24,(sc_uint<8>)output_event_wire_local_reg_23_16,(sc_uint<8>)output_event_wire_local_reg_15_8,(sc_uint<8>)output_event_wire_local_reg_7_0)); 

/////////////////////// This used to be the Seval function /////////////////////
 event_mux_sel[0] = EVENT_MUX_SEL_0;
 event_mux_sel[1] = EVENT_MUX_SEL_1;
 event_mux_sel[2] = EVENT_MUX_SEL_2;
 event_mux_sel[3] = EVENT_MUX_SEL_3;

 event_mux_alt[0] = EVENT_MUX_ALT_0;
 event_mux_alt[1] = EVENT_MUX_ALT_1;
 event_mux_alt[2] = EVENT_MUX_ALT_2;
 event_mux_alt[3] = EVENT_MUX_ALT_3;

    for (i = 0; i<=3; i=i+1) {
//         active_event_in[i] = P_EVENT_BUS_IN[event_mux_sel[i]].read();
         active_event_in[i] = (event_mux_alt[i] == 0) ? P_EVENT_BUS_IN[event_mux_sel[i]].read() : output_event_wire[event_mux_sel[i]];
         set_pending_event[i] =  active_event_in[i] && (!REG_event_dly[i]) ; // Do a pos edge detect on the event bus.
    }
// Brute force method to detect event being serviced and correspoding EVET register getting cleared
 clr_pending_event[0] = (activity_trigger == 1) && (next_instr_PTR == 0x0) ? 1 : 0;
 clr_pending_event[1] = (activity_trigger == 1) && (next_instr_PTR == 0x8) ? 1 : 0;
 clr_pending_event[2] = (activity_trigger == 1) && (next_instr_PTR == 0x10) ? 1 : 0;
 clr_pending_event[3] = (activity_trigger == 1) && (next_instr_PTR == 0x18) ? 1 : 0;

 instr_opcode = (INSTR_ARRAY[current_instr_PTR]>>6) & 0x1f;
 src_port  =    (INSTR_ARRAY[current_instr_PTR]>>3) & 0x7;
 dest_port =    (INSTR_ARRAY[current_instr_PTR] & 0x7);
 stop_bit =     (INSTR_ARRAY[current_instr_PTR]>> 11) & 1; // Bit 11 is the STOP bit of the opcode.

 instr_is_mov =  ((instr_active_T == 1) && (instr_opcode == OPCODE_MOV)) ? 1 : 0;
 instr_is_add =  ((instr_active_T == 1) && (instr_opcode == OPCODE_ADD)) ? 1 : 0;
 instr_is_sub =  ((instr_active_T == 1) && (instr_opcode == OPCODE_SUB))  ? 1 : 0;
 instr_is_T1_mov =  ((instr_active_T == 1) && (instr_opcode == OPCODE_T1_MOV)) ? 1 : 0;
 instr_is_T2_mov = ((instr_active_T == 1) &&  (instr_opcode == OPCODE_T2_MOV)) ? 1 : 0;
 instr_is_INTR = ((instr_active_T == 1) &&  (instr_opcode == OPCODE_INTR)) ? 1 : 0;

 pull_data_next_cycle = ((instr_active_T == 1) && (instr_opcode == OPCODE_PULL)) ? 1 : 0;

 push_data_en = ((instr_active_T == 1) && (instr_opcode == OPCODE_PUSH) && (dummy_state_T == 0)) ? 1 : 0;
 pull_data_en = ((instr_active_T == 1) && (instr_opcode == OPCODE_PULL) ) ? 1 : 0;

 if (push_data_en == 1)
	 	 cout << "PUSH_DATA_EN = TRUE ... " << current_instr_PTR << "--" << INSTR_ARRAY[current_instr_PTR] << "--" << instr_opcode <<"  active =  " << instr_active_T << endl;

 set_int_flag = ((instr_active_T == 1) && (instr_opcode == OPCODE_INTR)) ? 1 : 0;

 if(set_int_flag == 1)
 {
  interrupt_number = (INSTR_ARRAY[current_instr_PTR]) & 0x3F;       //Interrupt opcode uses lower 6 bits for interrupt value
 }
 else
 {
  interrupt_number = 0xFFFF;
 }


/////////////////////////////// This used to be the ctrl() function //////////////////////////

  for(i =0; i<=3; i++)
  	event_pending_wire[i] = event_pending_REG[i];

/// IF this is anyway the last instruction, then don't go to the dummy state.
/// Otherwise, it will spin endlessly there.
	next_cycle_dummy_state = (push_data_en || pull_data_en) && (stop_bit == 0);

	event_index_wire = (event_pending_wire[0] == 1)  ? 0x0 :
                       (event_pending_wire[1] == 1)  ? 0x1 :
			           (event_pending_wire[2] == 1)  ? 0x2 :
			           (event_pending_wire[3] == 1)  ? 0x3 :
				        0x7; // All ones will indicate that there is no active event.

	activity_trigger = (event_index_wire == 0x7) ? 0 : 1 ;

////////////////////////////////////////////////////////////////////////////////
/// This will return a fixed instruction pointer for the prioritized event
/// Currently, we will allow only 4 instructions on an event. Can increase this if needed.
///////////////////////////////////////////////////////////////////////////////
	event_instr_ptr = (event_pending_wire[0] == 1)  ? 0x0 :
                      (event_pending_wire[1] == 1)  ? 0x8 :
			          (event_pending_wire[2] == 1)  ? 0x10 :
			          (event_pending_wire[3] == 1)  ? 0x18 :
				      0x0 ;


/////////// On an event, jump to the vector and execute till the last instruction (seen by the stop-bit set).
	next_instr_PTR = ( (instr_active_T == 1) && (stop_bit == 0) )? current_instr_PTR + 1 : // Current execution is highest priority
                                    (dummy_state_T == 1) ? current_instr_PTR : // Dummy state should fall to next instruction only.
                                    (activity_trigger == 1) ? event_instr_ptr :  // Last instruction or new trigger
				    current_instr_PTR;

    instr_active_next_state = (activity_trigger && (dummy_state_T == 0) )
                                            || ((instr_active_T == 1) && (stop_bit == 0) && (next_cycle_dummy_state == 0))
                                            || (dummy_state_T == 1); // If this is a dummy_state, then next state has to be active.

////assign instr_array_load = (global_load_en && (global_load_addr[5] == 1));



/////////////////// Important NOTE on the operation of PULL ////////////////////////////
/// May 06 -2012
/// The way PULL buffer is expected to work is that the current Data present at the input of PULL_DATA_IN port
/// is valid and will be latched in. The PULL_DATA_EN signal driven to the CPU interface is expected to increment the
/// pointers and keep the next data ready.
/// The PULL operation DOES NOT expect to intiate a memory/reg read and then latch the data.Instead, it is
/// like "Latch current data" and indicate to the CPU interface to keep the next data ready for the next PULL
///////////////////////////////////////////////////////////////////////////////////////

 pull_data_en = pull_data_next_cycle;
 if((pull_data_en == 1) && (push_data_en != 1))
 {
    pull_data_in = hlc_pull_fifo[hlc_fifo_read_ptr];
    if(((hlc_fifo_read_ptr > 0) && (pull_fifo_refill_enable == 1)) || ((hlc_fifo_read_ptr > 4) && (pull_fifo_refill_enable == 0)))
    {
      if((hlc_fifo_read_ptr < 4) && (pull_fifo_refill_enable == 1))
      {
        pull_fifo_output[0] = hlc_pull_fifo[3];
        pull_fifo_output[1] = hlc_pull_fifo[2];
        pull_fifo_output[2] = hlc_pull_fifo[1];
        pull_fifo_output[3] = hlc_pull_fifo[0];
      }
      
      hlc_fifo_read_ptr = hlc_fifo_read_ptr - 1;
      hlc_fifo_overflow = 0;
    }
    else
    {
      if(pull_fifo_refill_enable == 1)
      {
        hlc_fifo_read_ptr = 3;
      }
      else
      {
        hlc_fifo_read_ptr = 7;
      }
      hlc_fifo_underflow = 1;
    }
 }

	// Pull data has the highest priority.
 comm_source_bus = (pull_data_next_cycle == 1) ? pull_data_in :
                         (instr_is_INTR == 1) ? ( (src_port<<3) |dest_port) :
		                 (src_port == 0x0) ? comm_R0 :
                         (src_port == 0x1) ? comm_R1 :
                         (src_port == 0x2) ? comm_R2 :
                         (src_port == 0x3) ? comm_R3 :
                         (src_port == 0x4) ? counter_in_0 :
                         (src_port == 0x5) ? counter_in_1 :
                         (src_port == 0x6) ? counter_in_2 :
                         (unsigned long) 0;

 comm_operand_bus = (dest_port == 0x0) ? comm_R0 :
                         (dest_port == 0x1) ? comm_R1 :
                         (dest_port == 0x2) ? comm_R2 :
                         (dest_port == 0x3) ? comm_R3 :
                         (dest_port == 0x4) ? counter_in_0 :
                         (dest_port == 0x5) ? counter_in_1 :
                         (dest_port == 0x6) ? counter_in_2 :
                         0;

 //Create artificial delay to match pull FIFO; shows in simulation 1 cycle after instruction ends
 P_push_fifo[0].write(hlc_push_fifo[0]);
 P_push_fifo[1].write(hlc_push_fifo[1]);
 P_push_fifo[2].write(hlc_push_fifo[2]);
 P_push_fifo[3].write(hlc_push_fifo[3]);

 if((push_data_en == 1) && (pull_data_en != 1))
 {
    hlc_push_fifo[hlc_fifo_write_ptr] = comm_source_bus;
    if(hlc_fifo_write_ptr < 3)
    {
      hlc_fifo_write_ptr = hlc_fifo_write_ptr + 1;
      hlc_fifo_underflow = 0;
    }
    else
    {
      hlc_fifo_write_ptr = 0;                         //Verified on Soprano LP: 5 consecutive pushes make the FIFO pointer wrap around (safe to assume pulls work the same)
      hlc_fifo_overflow = 1;
    }
 }

// If using the counter to be driven out, then always use channel0 to force the read/write.This simplifies the decode cone
     local_count_load_enable_0  =   ( instr_active_T && instr_is_mov && (dest_port  == 0x4) );
     local_count_load_enable_1  =   ( instr_active_T && instr_is_mov && (dest_port  == 0x5) );
     local_count_load_enable_2  =   ( instr_active_T && instr_is_mov && (dest_port  == 0x6) );

     local_count_match1_enable_0  =    ( instr_active_T && instr_is_T1_mov && (dest_port  == 0x4) );
     local_count_match1_enable_1  =    ( instr_active_T && instr_is_T1_mov && (dest_port  == 0x5) );
     local_count_match1_enable_2  =    ( instr_active_T && instr_is_T1_mov && (dest_port  == 0x6) );

     local_count_match2_enable_0  =   ( instr_active_T && instr_is_T2_mov && (dest_port  == 0x4) );
     local_count_match2_enable_1  =   ( instr_active_T && instr_is_T2_mov && (dest_port  == 0x5) );
     local_count_match2_enable_2  =   ( instr_active_T && instr_is_T2_mov && (dest_port  == 0x6) );

 comm_write_bus = (global_load_en  == 1) ? global_load_value.to_uint() :
                        instr_is_add ? (comm_operand_bus + comm_source_bus) :
                        instr_is_sub ? (comm_operand_bus - comm_source_bus) :
                        ((pull_data_next_cycle == 1) || ( instr_is_mov || instr_is_T1_mov || instr_is_T2_mov)) ? comm_source_bus :
  	                0;

 counter_load_bus = comm_write_bus;
 push_data_out = comm_source_bus;

 R0_write_en =  ( (instr_is_mov || instr_is_add || instr_is_sub) && (dest_port  == 0x0)) || (pull_data_next_cycle && (dest_port == 0x0));
 R1_write_en =  ( (instr_is_mov || instr_is_add || instr_is_sub) && (dest_port  == 0x1)) || (pull_data_next_cycle && (dest_port == 0x1));
 R2_write_en =  ( (instr_is_mov || instr_is_add || instr_is_sub) && (dest_port  == 0x2)) || (pull_data_next_cycle && (dest_port == 0x2));
 R3_write_en =  ( (instr_is_mov || instr_is_add || instr_is_sub) && (dest_port  == 0x3)) || (pull_data_next_cycle && (dest_port == 0x3));

/// These are being sent out only for debug visibility purpose. These can be pipelined if needed.
 P_comm_R0_out.write(comm_R0);
 P_comm_R1_out.write(comm_R1);
 P_comm_R2_out.write(comm_R2);
 P_comm_R3_out.write(comm_R3);


   P_counter_load_bus.write(counter_load_bus);
   P_local_count_load_enable_0.write(local_count_load_enable_0);
   P_local_count_load_enable_1.write(local_count_load_enable_1);
   P_local_count_load_enable_2.write(local_count_load_enable_2);
   P_local_count_match1_enable_0.write(local_count_match1_enable_0);
   P_local_count_match1_enable_1.write(local_count_match1_enable_1);
   P_local_count_match1_enable_2.write(local_count_match1_enable_2);
   P_local_count_match2_enable_0.write(local_count_match2_enable_0);
   P_local_count_match2_enable_1.write(local_count_match2_enable_1);
   P_local_count_match2_enable_2.write(local_count_match2_enable_2);
   P_push_data_en.write(push_data_en);
   P_push_data_out.write(push_data_out);
   P_pull_data_en.write(pull_data_en);
   P_set_intr_flag.write(set_int_flag);
   P_intr_val.write(interrupt_number);
   P_comm_R0_out.write(comm_R0);
   P_comm_R1_out.write(comm_R1);
   P_comm_R2_out.write(comm_R2);
   P_comm_R3_out.write(comm_R3);
   P_curr_instr.write((sc_uint<12>) (0xFFF & INSTR_ARRAY[current_instr_PTR]));

   P_pull_fifo[0].write(pull_fifo_output[0]);
   P_pull_fifo[1].write(pull_fifo_output[1]);
   P_pull_fifo[2].write(pull_fifo_output[2]);
   P_pull_fifo[3].write(pull_fifo_output[3]);

   P_fifo_read_ptr.write((sc_uint<2>) (0x3 & hlc_fifo_read_ptr));
   P_fifo_write_ptr.write((sc_uint<2>) (0x3 & hlc_fifo_write_ptr));
   P_fifo_underflow.write(hlc_fifo_underflow);
   P_fifo_overflow.write(hlc_fifo_overflow);

}
