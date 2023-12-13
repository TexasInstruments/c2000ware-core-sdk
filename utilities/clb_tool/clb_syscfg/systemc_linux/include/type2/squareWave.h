#include "stdint.h"
#include "systemc.h"
SC_MODULE(squareWave)
{
    sc_in<bool> clk;
    sc_out<bool> out;
    uint32_t period;
    uint32_t duty_cycle;
	uint32_t repeat_count;
	uint32_t static_value;
	uint32_t initial_delay;

    void generator(void)
    {
		uint32_t localcount=0;

        if(static_value == 0)
		{
			out.write(false);
			if(initial_delay >= 1)
			{
				wait(initial_delay);
			}

			while (1) {
				if(localcount==repeat_count) {
					out.write(false);
					break;
				}
				out.write(false);
				wait(period - duty_cycle);
				out.write(true);
				wait(duty_cycle);
				localcount++;
			}
		}
		else
		{
			out.write(true);
			if(initial_delay >= 1)
			{
				wait(initial_delay);
			}

			while (1) {
				if(localcount==repeat_count) {
				out.write(true);
					break;
				}
				out.write(true);
				wait(period - duty_cycle);
				out.write(false);
				wait(duty_cycle);
				localcount++;
			}
		}
    }

    typedef squareWave SC_CURRENT_USER_MODULE;
    squareWave(sc_module_name name_, uint32_t period_, uint32_t duty_cycle_, uint32_t repeat_count_, uint32_t static_value_, uint32_t initial_delay_) :
        period(period_), duty_cycle(duty_cycle_), repeat_count(repeat_count_), static_value(static_value_), initial_delay(initial_delay_)
    {
        SC_THREAD(generator);
        sensitive << clk.pos();
    }
};
