//#############################################################################
//! \file qsortRVOutput.c
//! \brief  Ouput Vector (64) 
//! \author Vishal Coelho 
//! \date   05-Oct-2015
//! 
//
//  Group:			C2000
//  Target Family:	$DEVICE$
//
//#############################################################################
//
//
// 
// C2000Ware v6.00.01.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//#############################################################################


const float test_golden[64] = {
	-3.11281802769F, -3.04329415030F, -3.01830985518F, -2.82529718855F, 
	-2.78988408394F, -2.78757902732F, -2.65107032663F, -2.62032295565F, 
	-2.52773852966F, -2.50855851740F, -2.46290374806F, -2.45462536624F, 
	-2.37385557581F, -2.24211683900F, -2.18340289184F, -2.06686626305F, 
	-1.77189722023F, -1.70470618574F, -1.43620029100F, -0.87945089983F, 
	-0.71383331991F, -0.69158607773F, -0.43807721941F, -0.40730405882F, 
	-0.37300330160F, -0.30193401352F, -0.28769215242F, -0.25522268580F, 
	 0.00132778962F,  0.03225222980F,  0.04931565855F,  0.10668229573F, 
	 0.10679378074F,  0.12647684652F,  0.37303630820F,  0.44997487362F, 
	 0.53789800077F,  0.56852256917F,  0.57117126644F,  0.62571445277F, 
	 0.73758420049F,  0.97963542463F,  1.01533882607F,  1.06212591829F, 
	 1.07546916020F,  1.21738332703F,  1.29164607858F,  1.47196876914F, 
	 1.65176833847F,  1.67561241543F,  1.73136087951F,  1.78588608503F, 
	 2.08740909223F,  2.09977179825F,  2.13438184275F,  2.19100468816F, 
	 2.28526276338F,  2.28625147209F,  2.56386760763F,  2.61896528098F, 
	 2.75554032952F,  2.77665852990F,  2.79735884114F,  3.05971190918F, 
}; 


// End of File
