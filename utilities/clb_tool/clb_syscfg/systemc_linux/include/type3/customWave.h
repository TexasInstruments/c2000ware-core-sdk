#include "stdint.h"
#include "systemc.h"

SC_MODULE(customWave)
{
    sc_in<bool> clk;
    sc_out<bool> out;
    char *input_source;

    void generator(void)
    {
		uint32_t index = 0;
		wait(1);

		while(1)
		{
			if(input_source[index] == '0')
			{
				out.write(false);
				wait(1);
			}
			else if(input_source[index] == '1')
			{
				out.write(true);
				wait(1);
			}
			else
			{
				break;
			}
			index++;
		}
    }

    typedef customWave SC_CURRENT_USER_MODULE;
    customWave(sc_module_name name_, char *input_source_) : input_source(input_source_)
    {
        SC_THREAD(generator);
        sensitive << clk.pos();
    }
};
