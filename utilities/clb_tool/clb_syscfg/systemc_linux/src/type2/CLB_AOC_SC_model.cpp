#include "systemc.h"
#include "../type2/CLB_AOC_SC_model.h"

void POTENZA_CLB_AOC::aoc_clocked_logic() {

    sc_uint<32>   aoc_mux_ctrl_val = aoc_mux_ctrl.read();
    clb_tile_output_delay = clb_tile_output.read();
    gate_clb_output_delay = aoc_gate_signal.read();
    release_clb_output_delay = aoc_release_signal.read();

    if((aoc_mux_ctrl_val & 0x18) == 0x18)
    {
        aoc_stage3_delay_out = aoc_stage2_out;
    }
}

void POTENZA_CLB_AOC::aoc_nonclocked_logic() {

    sc_uint<16>   aoc_mux_ctrl_val = aoc_mux_ctrl.read();

    //Choose input to AOC
    bool unmod_aoc_in_val = (aoc_mux_ctrl_val & 0x2000) ? boundary_in.read() : clb_tile_output.read(); //For AOC Bypass mode
    aoc_out.write(unmod_aoc_in_val);
    bool aoc_in_val = (aoc_mux_ctrl_val & 0x2000) ? boundary_in.read() : clb_tile_output_delay;

    //Stage 1
    if(aoc_mux_ctrl_val & 0x1)
    {
        aoc_stage1_out = !aoc_in_val;
    }
    else
    {
        aoc_stage1_out = aoc_in_val;
    }

    //Stage 2
    
    if((aoc_mux_ctrl_val & 0x800))  //If gate signal is coming from a CLB output, add delay
    {
        if((aoc_mux_ctrl_val & 0x6) == 0x2)
        {
            aoc_stage2_out = gate_clb_output_delay.read() & aoc_stage1_out;
        }
        else if((aoc_mux_ctrl_val & 0x6) == 0x4)
        {
            aoc_stage2_out = gate_clb_output_delay.read() | aoc_stage1_out;
        }
        else if((aoc_mux_ctrl_val & 0x6) == 0x6)
        {
            aoc_stage2_out = gate_clb_output_delay.read() ^ aoc_stage1_out;
        }
        else
        {
            aoc_stage2_out = aoc_stage1_out;
        }
    }
    else
    {
        if((aoc_mux_ctrl_val & 0x6) == 0x2)
        {
            aoc_stage2_out = aoc_gate_signal.read() & aoc_stage1_out;
        }
        else if((aoc_mux_ctrl_val & 0x6) == 0x4)
        {
            aoc_stage2_out = aoc_gate_signal.read() | aoc_stage1_out;
        }
        else if((aoc_mux_ctrl_val & 0x6) == 0x6)
        {
            aoc_stage2_out = aoc_gate_signal.read() ^ aoc_stage1_out;
        }
        else
        {
            aoc_stage2_out = aoc_stage1_out;
        }
    }

    //Stage 3  
    if((aoc_mux_ctrl_val & 0x1000))  //If release signal is coming from a CLB output, add delay
    {
        if((aoc_mux_ctrl_val & 0x18) == 0x8)
        {
            if(release_clb_output_delay.read() == 1)
            {
                aoc_stage3_out = 0;
            }
            else
            {
                aoc_stage3_out = aoc_stage2_out;
            }
        }
        else if((aoc_mux_ctrl_val & 0x18) == 0x10)
        {
            if(release_clb_output_delay.read() == 1)
            {
                aoc_stage3_out = 1;
            }
            else
            {
                aoc_stage3_out = aoc_stage2_out;
            }
        }
        else if((aoc_mux_ctrl_val & 0x18) == 0x18)
        {
            if(release_clb_output_delay.read() == 1)
            {
                aoc_stage3_out = aoc_stage3_delay_out;
            }
            else
            {
                aoc_stage3_out = aoc_stage2_out;
            }
        }
        else
        {
            aoc_stage3_out = aoc_stage2_out;
        }
    }
    else
    {
        if((aoc_mux_ctrl_val & 0x18) == 0x8)
        {
            if(aoc_release_signal.read() == 1)
            {
                aoc_stage3_out = 0;
            }
            else
            {
                aoc_stage3_out = aoc_stage2_out;
            }
        }
        else if((aoc_mux_ctrl_val & 0x18) == 0x10)
        {
            if(aoc_release_signal.read() == 1)
            {
                aoc_stage3_out = 1;
            }
            else
            {
                aoc_stage3_out = aoc_stage2_out;
            }
        }
        else if((aoc_mux_ctrl_val & 0x18) == 0x18)
        {
            if(aoc_release_signal.read() == 1)
            {
                aoc_stage3_out = aoc_stage3_delay_out;
            }
            else
            {
                aoc_stage3_out = aoc_stage2_out;
            }
        }
        else
        {
            aoc_stage3_out = aoc_stage2_out;
        }
    }

    if(aoc_mux_ctrl_val & 0x4000)
    {
        aoc_out.write(aoc_stage3_out);
    }
}
