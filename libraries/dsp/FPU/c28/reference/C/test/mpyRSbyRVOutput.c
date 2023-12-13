//#############################################################################
//! \file mpyRSbyRVOutput.c
//! \brief  Ouput Vector (64) 
//! \author Vishal Coelho 
//! \date   22-Jul-2016
//! 
//
//  Group:          C2000
//  Target Family:  $DEVICE$
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com
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
     0.382973710053L,  0.038974179699L,  0.855366578660L, -0.487406021100L, 
    -0.682973109503L, -0.676217576466L, -0.756098561101L, -0.165319663806L, 
    -0.089446368161L, -0.232479811049L,  0.456534235435L,  0.221586518150L, 
     0.471218863442L,  0.749939253920L,  0.819045856825L, -0.533575429931L, 
    -0.625667499351L,  0.340040698537L, -0.703725987247L,  0.044014329521L, 
     0.052572791505L,  0.625691779654L, -0.026242314989L, -0.184591886186L, 
     0.297012546074L,  0.417990781501L,  0.034741846820L, -0.263844989450L, 
    -0.606396288155L,  0.149158572555L, -0.412094470769L, -0.789254800286L, 
     0.441683925822L, -0.445636515667L, -0.099790713028L,  0.325365586966L, 
    -0.243893774045L,  0.409470340926L, -0.182424271982L,  0.317776652142L, 
     0.353521810091L, -0.099958596194L, -0.832354457252L, -0.293046711009L, 
    -0.131137371553L, -0.398017341393L, -0.524868602765L,  0.557397147642L, 
    -0.121414468013L,  0.671831492437L, -0.188530599725L,  0.466253386260L, 
    -0.178813571248L,  0.534515242059L,  0.441933121167L, -0.212418009107L, 
    -0.492010640352L,  0.503144220885L,  0.778440247632L, -0.298751029445L, 
     0.296723610520L, -0.106300465428L,  0.577805532889L,  0.465802690158L, 
}; 


// End of File
