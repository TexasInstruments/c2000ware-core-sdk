

function onValidate(inst, validation) 
{
  for (var channel = 1; channel <= 4; channel++)
  {
  
	var dc_input = inst["Ch" + channel.toString() + "_DC_Input"];
	var FSR = inst["Ch" + channel.toString() + "_FSR"];
	
	if(dc_input > FSR)
	{
	validation.logError(
            "DC input is outside full scale range of modulator_" + inst[$name] + channel + " DC input = " + dc_input, 
            inst);
	}
	var cosr = inst["Ch" + channel.toString() + "_COSR"];
		
	if(cosr < 0 || cosr > 32)
	{
		validation.logError(
            "COSR should be between 1 to 32! - Check Filter_" + inst[$name] + channel + " COSR = " + cosr, 
            inst);
	}
	
	var dosr = inst["Ch" + channel.toString() + "_DOSR"];
		
	if(dosr < 0 || dosr > 256)
	{
		validation.logError(
            "dosr should be between 1 to 256! - Check Filter_" + channel + " DOSR = " + dosr, 
            inst);
	}
	
	var HLT1 = inst["Ch" + channel.toString() + "_HLT1"];
	
	if(HLT1 < 0 || HLT1 > 32767)
	{
		validation.logError(
            "HLT1 should be between 0 to 32767! - Check Filter_" + channel + " HLT1 = " + HLT1, 
            inst);
	}
	
	var HLT2 = inst["Ch" + channel.toString() + "_HLT2"];
	
	if(HLT2 < 0 || HLT2 > 32767)
	{
		validation.logError(
            "HLT2 should be between 0 to 32767! - Check Filter_" + channel + " HLT2 = " + HLT2, 
            inst);
	}
	
	var HLT = inst["Ch" + channel.toString() + "_HLT"];
	
	if(HLT < 0 || HLT > 32767)
	{
		validation.logError(
            "HLT should be between 0 to 32767! - Check Filter_" + channel + " HLT = " + HLT, 
            inst);
	}
	
	var HLTZ = inst["Ch" + channel.toString() + "_HLTZ"];
	
	if(HLTZ < 0 || HLTZ > 32767)
	{
		validation.logError(
            "HLTZ should be between 0 to 32767! - Check Filter_" + channel + " HLTZ = " + HLTZ, 
            inst);
	}

	var LLT1 = inst["Ch" + channel.toString() + "_LLT1"];
	
	if(LLT1 < 0 || LLT1 > 32767)
	{
		validation.logError(
            "LLT1 should be between 0 to 32767! - Check Filter_" + channel + " LLT1 = " + LLT1, 
            inst);
	}
	
	var LLT2 = inst["Ch" + channel.toString() + "_LLT2"];
	
	if(LLT2 < 0 || LLT2 > 32767)
	{
		validation.logError(
            "LLT2 should be between 0 to 32767! - Check Filter_" + channel + " LLT2 = " + LLT2, 
            inst);
	}
	
	var LLT = inst["Ch" + channel.toString() + "_LLT"];
	
	if(LLT < 0 || LLT > 32767)
	{
		validation.logError(
            "LLT should be between 0 to 32767! - Check Filter_" + channel + " LLT = " + LLT, 
            inst);
	}
	
	for(var event = 1; event <= 2; event++)
	{
		var Prescale_CEVT = inst["Ch" + channel.toString() + "_samplePrescale_CEVT" + event.toString()];
	
		if(Prescale_CEVT < 0 || Prescale_CEVT > 1023)
		{
		  validation.logError(
            "Comparator event Prescale should be between 0 to 1023! - Check Filter_" + channel + " CEVT" + event.toString() + "Prescale = " + Prescale_CEVT, 
            inst);
		}
		
		var threshold_CEVT = inst["Ch" + channel.toString() + "_Threshold_CEVT" + event.toString()];
		
		if(threshold_CEVT < 0 || threshold_CEVT > 31)
		{
		  validation.logError(
            "Comparator event Threshold should be between 0 to 31! - Check Filter_" + channel + " CEVT" + event.toString() + "Threshold = " + threshold_CEVT, 
            inst);
		}
		
		var sampleWindow_CEVT = inst["Ch" + channel.toString() + "_sampleWindow_CEVT" + event.toString()];
		
		if(sampleWindow_CEVT < 0 || sampleWindow_CEVT > 31)
		{
		  validation.logError(
            "Comparator event samplewindow should be between 0 to 31! - Check Filter_" + channel + " CEVT" + event.toString() + "sample window = " + sampleWindow_CEVT, 
            inst);
		}
	}
  }
}

exports =
{
    onValidate : onValidate,
}
