#include <string>
#include "CLB_LUT4_SC_model.h"

using namespace std;

void SOPRANO_CLB_LUT4::lut4_evaluate()
{
	unsigned int i0_val, i1_val, i2_val, i3_val, lut_fn_val;
	unsigned int index, out_value;

	lut_fn_val = LUT4_fn.read().to_uint();

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

    if (I3.read() == true)
	  i3_val = 1;
  else
	  i3_val = 0;

	index = (i3_val<<3) | (i2_val<<2) | (i1_val<<1) | i0_val;

	out_value = (lut_fn_val>>index) & 0x1;

  if (out_value == 1)
	  OUT.write(true);
  else
	  OUT.write(false);
}
