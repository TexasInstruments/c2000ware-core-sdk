let module = system.modules['/driverlib/sd.js'];
let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_sdfm.js");
		
function getBaseLog(x, y) {
  return Math.log(y) / Math.log(x);
}

function getShiftvalue(FilterType, OSR, rshift, datarep)
{
  var SincFast = [];
  var Sinc1 = [];
  var Sinc2 = [];
  var Sinc3 = [];

  var shiftValue;
  
  //var FilterType = "SINC3";
  //var OSR = 256;

  var shift_Sinc1 = [];
  var shift_Sinc2 = [];
  var shift_SincFast = [];
  var shift_Sinc3 = [];

  Sinc1[OSR] 	= OSR; 
  Sinc2[OSR] 	= OSR*OSR; 
  SincFast[OSR] = 2 * OSR*OSR;
  Sinc3[OSR]    = OSR*OSR*OSR;
    
  shift_SincFast[OSR] = ((getBaseLog(2, SincFast[OSR]) - 15) < 0) ? 0 : Math.ceil((getBaseLog(2, SincFast[OSR]) - 15));
  shift_Sinc1[OSR] 	  = ((getBaseLog(2, Sinc1[OSR]) - 15) < 0) ? 0 : Math.ceil((getBaseLog(2, Sinc1[OSR]) - 15));
  shift_Sinc2[OSR] = ((getBaseLog(2, Sinc2[OSR]) - 15) < 0) ? 0 : Math.ceil((getBaseLog(2, Sinc2[OSR]) - 15));
  shift_Sinc3[OSR] = ((getBaseLog(2, Sinc3[OSR]) - 15) < 0) ? 0 : Math.ceil((getBaseLog(2, Sinc3[OSR]) - 15));
    
  
  //var FilterType = 'SINC3';
  var filter_32bit_Output = 0;
  var filter_16bit_Output = 0;
  
  switch(FilterType)
  {
  case 'SDFM_FILTER_SINC_1':
    shiftValue = shift_Sinc1[OSR];
	filter_32bit_Output = Sinc1[OSR];	
	
	filter_16bit_Output = Sinc1[OSR] >> shift_Sinc1[OSR];
    break;
	
  case 'SDFM_FILTER_SINC_2':
    shiftValue = shift_Sinc2[OSR];
	filter_32bit_Output = Sinc2[OSR];	

    filter_16bit_Output = Sinc2[OSR] >> shift_Sinc2[OSR];
	if(filter_16bit_Output >= 32768)
	{
	   filter_16bit_Output = filter_16bit_Output >> 1; shiftValue++;
	}
    break;   
	
  case 'SDFM_FILTER_SINC_FAST':
    shiftValue = shift_SincFast[OSR];
	filter_32bit_Output = SincFast[OSR];	

    filter_16bit_Output = SincFast[OSR] >> shift_SincFast[OSR];
	if(filter_16bit_Output >= 32768)
	{
	   filter_16bit_Output = filter_16bit_Output >> 1; shiftValue++;
	}
    break;  
	
  case 'SDFM_FILTER_SINC_3':
    shiftValue = shift_Sinc3[OSR];
	filter_32bit_Output = Sinc3[OSR];	

    filter_16bit_Output = Sinc3[OSR] >> shift_Sinc3[OSR];
    if(filter_16bit_Output >= 32768)
	{
	   filter_16bit_Output = filter_16bit_Output >> 1; shiftValue++;
	}
    break;  
	
  }
  
  if(rshift)
  {
	return shiftValue;
  }
  else
  {
   if(datarep == "SDFM_DATA_FORMAT_16_BIT")
   {
	 return Math.floor(filter_16bit_Output);
   } 
   if(datarep == "SDFM_DATA_FORMAT_32_BIT")
   {
	 return filter_32bit_Output;
   } 
  }
}
		
function getArgument()
{
	for(var i = 0; i < module.$instances.length; i++) 
	{
		var instance = module.$instances[i];		
	
		
	}
}

exports = 
{
	//comparatorSettings_Type2  : comparatorSettings_Type2,
	getArgument : getArgument,
	getShiftvalue : getShiftvalue,
	getBaseLog: getBaseLog
};
