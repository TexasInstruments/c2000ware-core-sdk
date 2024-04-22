#include "../type2/CLB_counter_SC_model.h"

void POTENZA_CLB_COUNTER::counter_logic()
{
    bool         reset_S;                   // Keep this a active high reset. This is a logic generated reset
    bool         event_in_S;
    sc_uint<32>  event_load_val_S;
    bool         glbl_en_S;
    bool         add_shift_mode_S;          // Set to 1 for add and set to 0 for shift
    bool         add_shift_on_event_en_S;   // Set to 1 to enable the add/shift on event
    bool         add_shift_dir_S;           // Set to 1 for add and left shift. Set to 0 for subtract and right shift.
    bool         glbl_rst_n_S;              // This is a global reset
    bool         count_mode_0_S;
    bool         count_mode_1_S;
    sc_uint<32>  match1_val_S;
    sc_uint<32>  match2_val_S;
    sc_uint<32>  match1_val_out_S;
    sc_uint<32>  match2_val_out_S;
    bool         glbl_serializer_mode_S;

    bool 		 lfsr_mode_S;
    bool 		 match1_tap_en_S;
    sc_uint<5> 	 match1_tap_S;
    bool 		 match2_tap_en_S;
    sc_uint<5> 	 match2_tap_S;

    sc_uint<32>  hlc_count_load_val_S;      // In RTL, this is physically same as the event_load_val.
    bool         hlc_count_load_en_S;
    bool         hlc_match1_load_en_S;
    bool         hlc_match2_load_en_S;

    sc_uint<32>  count_out_S;
    bool         count_zero_S;
    bool         count_match1_S;
    bool         count_match2_S;

    sc_uint<32>  count_next_val, load_val, serializer_val, event_bus_1, event_bus_2, final_serial_val;
    sc_uint<32>  count_tmp_bus_1, count_tmp_bus_2, count_tmp_bus3;
    sc_uint<32>  lfsr_feedback_bus, lfsr_nxt_val, lfsr_feed;
	bool 		 lfsr_msb, lfsr_feedback;
	sc_uint<32>  counter_REG, match1_REG, match2_REG, count_plus, count_minus;

    bool         event_dly_REG_S, event_occurred;
    bool         count_match1_level1, count_match2_level1;
    int 	 i; 
    

    reset_S                 = reset.read();
    event_in_S              = event.read();
    event_load_val_S        = event_load_val.read();
    glbl_en_S               = glbl_en.read();
    add_shift_mode_S        = add_shift_mode.read();
    add_shift_on_event_en_S = add_shift_on_event_en.read();
    add_shift_dir_S         = add_shift_dir.read();
    glbl_rst_n_S            = glbl_rst_n.read();
    count_mode_0_S          = mode0.read();
    count_mode_1_S          = mode1.read();
    match1_val_S            = match1_val.read();
    match2_val_S            = match2_val.read();
    glbl_serializer_mode_S  = glbl_serializer_mode.read();
	
    lfsr_mode_S		    = lfsr_mode.read();
    match1_tap_en_S	    = match1_tap_en.read();	
    match1_tap_S	    = match1_tap.read();	
    match2_tap_en_S  	= match2_tap_en.read(); 
    match2_tap_S	    = match2_tap.read();


    hlc_count_load_val_S    = hlc_count_load_val.read();
    hlc_count_load_en_S     = hlc_count_load_en.read();
    hlc_match1_load_en_S    = hlc_match1_load_en.read();
    hlc_match2_load_en_S    = hlc_match2_load_en.read();

    event_dly_REG_S         = event_dly_REG_SIG;

    counter_REG             = counter_REG_SIG;
    match1_REG              = match1_REG_SIG;
    match2_REG              = match2_REG_SIG;

    event_occurred          = event_in_S && (!event_dly_REG_S);
    lfsr_feed               = 0x0;

    // By definition, >> is a logical shift operation.
    load_val = ((add_shift_mode_S == 1) && (add_shift_dir_S == 1))? (counter_REG + event_load_val_S ) :
               ((add_shift_mode_S == 1) && (add_shift_dir_S == 0))? (counter_REG - event_load_val_S) :
               ((add_shift_mode_S == 0) && (add_shift_dir_S == 1))? (counter_REG << (event_load_val_S & 0x1f) ) :
               ((add_shift_mode_S == 0) && (add_shift_dir_S == 0))? (counter_REG >> (event_load_val_S & 0x1f) ) : 0;

    event_bus_1     = event_in_S & 0x1;
    event_bus_2     = event_in_S<<31;
    count_tmp_bus_1 = (counter_REG>>1) & 0x7fffffff;  // This is the same as right shift;
    count_tmp_bus_2 = counter_REG<<1;                 // This is the same as left shift;

    serializer_val  = (count_mode_1_S == 0) ? (count_tmp_bus_1  | event_bus_2)
                    : ( count_tmp_bus_2 | event_bus_1 ) ;


	///////////////// This is the LFSR Logic///////////////
	lfsr_msb = counter_REG[(match1_REG & 0x1f)];
	lfsr_feedback = (count_mode_1_S == 0) ? (lfsr_msb ^ event_in_S) : lfsr_msb;
	for(i=0;i<32;i++) 
	{
         lfsr_feed |= (lfsr_feedback << i);
   	}
	lfsr_feedback_bus = lfsr_feed & match2_REG;
	lfsr_nxt_val = (count_mode_1_S == 0) ? ( count_tmp_bus_2 ^ lfsr_feedback_bus ) : 
	              ( ( count_tmp_bus_2 | event_in_S) ^ lfsr_feedback_bus);

	final_serial_val = (lfsr_mode_S == 1) ? lfsr_nxt_val : serializer_val;

    /////////////// Important note on the glbl_load_en /////////////////////////
    /// We have only one global path to create a LOAD VALUE. There are two scenarios
    //// 1 . Just load the value into the counter either directly or by instructions in the HLC
    //// 2.  The load value is a place holder. This will be used whenever there is an event
    ////     and based on the event_mode and event_dir, the value will be used appropriately.
    ////   Since the event mode and direct loads are mutually exclusive, you can really use only one at a time.
    ////
    ////    To directly load the value, make sure the add_shift_on_even_en is set to 0.
    ////    If you set the add_shift_on_even_en , then the global loads and moves through HLC will not load the 
    ///      counter register.
    ///////////////////////////////////////////////////////////////////////////////

    count_plus  = counter_REG + 1;
    count_minus = counter_REG - 1;

    counter_REG =  ( (glbl_en_S == 1) && (reset_S == 0) ) ? (sc_uint<32>)0 : //Highest priority
                  ( (hlc_count_load_en_S == 1)    && (add_shift_on_event_en_S == 0)) ? hlc_count_load_val_S : // Next highest is the direct load
                  ( (glbl_serializer_mode_S == 0) && (glbl_en_S == 1) && (add_shift_on_event_en_S == 1) && (event_occurred == 1)) ? load_val:
                  ( (glbl_serializer_mode_S == 0) && (glbl_en_S == 1) && (add_shift_on_event_en_S == 0) && (event_occurred == 1)) ? event_load_val_S:
                  ( (glbl_serializer_mode_S == 0) && (glbl_en_S == 1) && ( (count_mode_1_S == 1) && (count_mode_0_S == 1) ) ) ? count_plus :
                  ( (glbl_serializer_mode_S == 0) && (glbl_en_S == 1) && ( (count_mode_1_S == 0) && (count_mode_0_S == 1 )) ) ? count_minus :
                  ( (glbl_serializer_mode_S == 1) && (glbl_en_S == 1) && (count_mode_0_S == 1) ) ? final_serial_val : counter_REG;

    match1_REG = (hlc_match1_load_en_S == 1) ? hlc_count_load_val_S : match1_REG;
    match2_REG = (hlc_match2_load_en_S == 1) ? hlc_count_load_val_S : match2_REG;
    match1_val_out_S = match1_REG;
    match2_val_out_S = match2_REG;

    if (glbl_rst_n_S == 0) {
        counter_REG = 0;
        match1_REG = match1_val_S; // Since there is no CPU preload of register possible, in the SystemC environment, the MATCH1 and MATCH2 initial values
        match2_REG = match2_val_S; // are loaded on the global reset.This is done solely for the purpose of simulation only.
    }

    if ((glbl_en_S == 1) && (glbl_rst_n_S == 1))
        count_out_S = counter_REG;
    else
        count_out_S = 0;

    if ((glbl_en_S == 1) && (counter_REG == match1_REG)  && (glbl_rst_n_S == 1) )
        count_match1_level1 = 1;
    else
        count_match1_level1 = 0;

    if ((glbl_en_S == 1) && (counter_REG == match2_REG)  && (glbl_rst_n_S == 1) )
        count_match2_level1 = 1;
    else
        count_match2_level1 = 0;

    if (glbl_en_S == 0)
    	count_match1_S = 0;
    else
    {
    	if(match1_tap_en_S == 1)
    		count_match1_S = counter_REG[match1_tap_S];
    	else
    		count_match1_S = count_match1_level1;
    }
    
    if (glbl_en_S == 0)
    	count_match2_S = 0;
    else
    {
    	if(match2_tap_en_S == 1)
    		count_match2_S = counter_REG[match2_tap_S];
    	else
    		count_match2_S = count_match2_level1;
    }

    if ((glbl_en_S == 1) && (counter_REG == 0)  && (glbl_rst_n_S == 1) )
        count_zero_S = 1;
    else
        count_zero_S = 0;

    counter_REG_SIG   = counter_REG;
    event_dly_REG_SIG = event_in_S;
    match1_REG_SIG    = match1_REG;
    match2_REG_SIG    = match2_REG;

    count_out.write(count_out_S);
    count_match1.write(count_match1_S);
    count_match2.write(count_match2_S);
    match1_reg_out.write(match1_val_out_S);
    match2_reg_out.write(match2_val_out_S);
    count_zero.write(count_zero_S);
}
