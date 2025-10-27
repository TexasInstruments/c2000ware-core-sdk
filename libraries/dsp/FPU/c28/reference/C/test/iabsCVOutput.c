//#############################################################################
//! \file iabsCVOutput.c
//! \brief  Ouput Vector (64) 
//! \author Vishal Coelho 
//! \date   20-Jul-2016
//! 
//
//  Group:          C2000
//  Target Family:  $DEVICE$
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


const double test_golden[64] = {
     0.321188510489L,  0.778657233514L,  0.377528524369L,  0.269511778315L, 
     0.325783835931L,  0.513273739245L,  0.370147113489L,  0.274476247481L, 
     0.386053300824L,  0.493560033891L,  0.346971752187L,  0.536658146168L, 
     0.412540236662L,  0.396265344941L,  0.422804239047L,  1.133841690575L, 
     0.357861747662L,  2.696430810362L,  0.387868546889L,  0.490500947540L, 
     0.347868450088L,  0.288671544641L,  0.550690160630L,  0.542748456672L, 
     0.381461998629L,  0.378839157346L,  0.614058299317L,  0.421948388559L, 
     0.351968955371L,  0.303829391823L,  0.391913222926L,  0.388113799092L, 
     0.321466323371L,  0.510413917246L,  0.396143146104L,  0.256739290738L, 
     0.316888466255L,  0.317408893901L,  0.649937084577L,  0.243415127706L, 
     0.296733464982L,  0.300386432665L,  0.251649438453L,  0.390695661240L, 
     0.550861307981L,  0.399329762059L,  0.269270662877L,  0.811372074496L, 
     0.380371971998L,  0.247993659381L,  0.329328509399L,  0.321360283210L, 
     0.778118408626L,  0.512992758291L,  1.177670991782L,  0.364980876805L, 
     0.251305587384L,  0.361372787064L,  0.388739351578L,  0.447432966152L, 
     0.379477270560L,  0.481923779813L,  0.335591635922L,  0.415523160006L, 
}; 


// End of File
