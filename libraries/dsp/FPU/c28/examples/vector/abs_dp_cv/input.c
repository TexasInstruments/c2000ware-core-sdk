//#############################################################################
//! \file   input.c
//! \brief  Input Vector (64) 
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
// C2000Ware v5.03.00.00
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


#include "dsp.h"

float64_t test_input[128] = {
    -1.508778756628L, -0.082990621216L,  1.885385866093L, -0.403012373810L, 
    -0.430939631557L, -0.334367563686L,  2.580174931748L, -1.216742152153L, 
    -1.999014077203L,  0.053461458475L, -1.484070044508L,  0.067679733742L, 
    -2.227144270415L,  1.995713750084L, -2.286648684742L,  1.852480426657L, 
     2.320331373100L,  0.906777555193L,  0.500798692250L, -0.762719743298L, 
     0.313280887591L,  1.957717757485L, -2.230814795185L,  0.206249257244L, 
     2.218159931847L, -0.937909269566L,  0.766895008813L,  2.758328164187L, 
    -0.936493810448L,  2.362118349513L,  0.083249314220L,  0.315141596761L, 
    -0.616958319613L,  0.769533660858L, -2.664279852523L,  0.546918008580L, 
    -1.634155002626L, -1.836309332210L, -2.366756934136L, -1.248806137336L, 
    -1.986065940378L, -0.182693989376L, -1.633926469911L, -1.693392831870L, 
    -0.519826335949L,  2.163355947396L, -2.829604666531L, -1.917852531019L, 
     2.530339944784L, -1.722084238812L,  2.794680335281L, -2.069002359933L, 
    -0.057402599972L, -1.711135682579L, -0.067527664496L, -0.404017083271L, 
    -1.019639019851L, -1.186879337078L,  2.513612449892L,  2.660172746622L, 
    -0.821546703732L, -0.438519893348L, -2.442885135410L, -1.980357466459L, 
     1.760875677982L,  2.543942153566L, -0.692791319558L,  3.014347962030L, 
    -1.623001517063L, -0.384091286682L, -0.603737795039L, -2.443409981523L, 
    -2.535550998241L, -1.520124347933L, -2.312380000546L, -0.573530121743L, 
     2.777485776991L,  0.596249617920L,  2.865977841269L, -1.494067652563L, 
     0.472549539571L,  0.646182188150L, -2.765986707674L,  1.327107888265L, 
    -1.666426951467L, -1.748316832498L, -0.922631907783L, -2.403835794929L, 
     2.018121674125L, -1.277523165990L, -3.044810000457L, -1.138649510681L, 
    -2.871266135154L, -0.476474301162L, -2.079796983410L,  0.049375058722L, 
     0.936920161319L, -2.604281053782L,  1.455954688915L, -1.492368133138L, 
     0.928315264773L,  1.891330655033L, -0.308355446684L, -2.957996234940L, 
     0.295365581320L,  2.694570028092L, -1.279754121583L,  1.447211493283L, 
     1.537450250181L, -0.071571928431L, -1.954353279419L,  0.493387509668L, 
     1.173544658663L, -1.650695951534L, -1.988558056158L, -0.258560438153L, 
    -0.826335651000L,  2.909671105971L,  0.789284695086L,  0.294089004273L, 
     1.760720903212L,  0.1328001341563L, -2.631864414619L, -1.686442205798L, 
     2.697911623900L, -0.069757532277L,  1.732353851235L,  0.779492523220L, 
}; 

// End of File
