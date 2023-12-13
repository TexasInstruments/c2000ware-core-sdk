#include <string>
#include "../type2/CLB_OutputLUT_SC_model.h"

using namespace std;

void POTENZA_CLB_OUTPUT_LUT::lut3_evaluate()
{
	unsigned int i0_val, i1_val, i2_val,lut_fn_val;
	unsigned int index, out_value;

	lut_fn_val = OUTPUT_LUT_fn.read().to_uint();

	if (I0.read() == true)
		i0_val = 1;
	else
		i0_val = 0;

	if (I1.read() == true)
		i1_val = 1;
	else
		i1_val = 0;

	if (I2.read() == true)
		i2_val = 1;
	else
		i2_val = 0;

	index = (i2_val<<2) | (i1_val<<1) | i0_val;

	out_value = (lut_fn_val >> index) & 0x1;

	if (out_value == 1)
		OUT.write(true);
	else
		OUT.write(false);
}
