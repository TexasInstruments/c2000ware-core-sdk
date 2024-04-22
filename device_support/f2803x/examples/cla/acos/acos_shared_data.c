//###########################################################################
//
// FILE:  acos_shared_data.c
//
// TITLE: ACOS Shared Data
//
// Description: Declare shared memory variables and assign them to specific 
// CLA-accessible memory locations
//
//! \addtogroup f2803x_example_cla_list
//! \b Memory \b Allocation \n
//!  - CLA1 Math Tables (RAML2)
//!    - CLAacosinTable - Lookup table
//!  - CLA1 to CPU Message RAM
//!    - fResult - Result of the lookup algorithm
//!  - CPU to CLA1 Message RAM
//!    - fVal - Sample input to the lookup algorithm
//
//###########################################################################
// $TI Release: $
// $Release Date: $
// $Copyright:
// Copyright (C) 2009-2024 Texas Instruments Incorporated - http://www.ti.com/
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
//###########################################################################

//
// Included Files
//
#include "DSP28x_Project.h"

//
// Include the test header file whose name is based on the test name
// which is defined by the macro TEST on the command line
//
#include XSTRINGIZE(XCONCAT(TEST_NAME,_shared.h))

//
// Globals (Ensure that all data is placed in the data rams)
//

//
// Task 1 (C) Variables
//
float y[BUFFER_SIZE];
#pragma DATA_SECTION(fVal,"CpuToCla1MsgRAM")
float fVal;
#pragma DATA_SECTION(fResult,"Cla1ToCpuMsgRAM")
float fResult;

//
// Task 2 (C) Variables
//

//
// Task 3 (C) Variables
//

//
// Task 4 (C) Variables
//

//
// Task 5 (C) Variables
//

//
// Task 6 (C) Variables
// 

//
// Task 7 (C) Variables
//

//
// Task 8 (C) Variables
//

//
// Common (C) Variables
//
#pragma DATA_SECTION(CLAacosinTable,"CLA1mathTables");
float CLAacosinTable[]={
    1.570795690593,-0.999877862610,-0.007815361896,
    1.570791227101, -0.999510644409, -0.015647916155, 
    1.570779058483, -0.998895919094, -0.023514960332, 
    1.570755205030, -0.998029615282, -0.031434003631, 
    1.570715532275, -0.996905974725, -0.039422875916, 
    1.570655695706, -0.995517492804, -0.047499840611, 
    1.570571082211, -0.993854840311, -0.055683712914, 
    1.570456747283, -0.991906765146, -0.063993984848, 
    1.570307346943, -0.989659972212, -0.072450958820, 
    1.570117063183, -0.987098979366, -0.081075891529, 
    1.569879521613, -0.984205946802, -0.089891150305, 
    1.569587699755, -0.980960476685, -0.098920384204, 
    1.569233824246, -0.977339379243, -0.108188712551, 
    1.568809254867, -0.973316400729, -0.117722933997, 
    1.568304353010, -0.968861907789, -0.127551759665, 
    1.567708331742, -0.963942521723, -0.137706074532, 
    1.567009084103, -0.958520694794, -0.148219231941, 
    1.566192985657, -0.952554219267, -0.159127386977, 
    1.565244666501, -0.945995657913, -0.170469875522, 
    1.564146746998, -0.938791682505, -0.182289647088, 
    1.562879530320, -0.930882303984, -0.194633761132, 
    1.561420643385, -0.922199974574, -0.207553958472, 
    1.559744615987, -0.912668537890, -0.221107321885, 
    1.557822385620, -0.902201997769, -0.235357042896, 
    1.555620712621, -0.890703070035, -0.250373315541, 
    1.553101486693, -0.878061473098, -0.266234382514, 
    1.550220901258, -0.864151902887, -0.283027765009, 
    1.546928466282, -0.848831624374, -0.300851714968, 
    1.543165822740, -0.831937595031, -0.319816937941, 
    1.538865312248, -0.813283013821, -0.340048646894, 
    1.533948242840, -0.792653161200, -0.361689022958, 
    1.528322775521, -0.769800358920, -0.384900179460, 
    1.521881334589, -0.744437830278, -0.409867752228, 
    1.514497416045, -0.716232177740, -0.436805274317, 
    1.506021630009, -0.684794109766, -0.465959540059, 
    1.496276761095, -0.649666934178, -0.497617226179, 
    1.485051559906, -0.610312179660, -0.532113122767, 
    1.472092881189, -0.566091493186, -0.569840443472, 
    1.457095648266, -0.516243664372, -0.611263845480, 
    1.439689931785, -0.459855210927, -0.656936015611, 
    1.419424157563, -0.395822366759, -0.707518998893, 
    1.395743063136, -0.322801460177, -0.763811905770, 
    1.367958442925, -0.239143420888, -0.826787304376, 
    1.335209858030, -0.142806299514, -0.897639596948, 
    1.296411176970, -0.031236880585, -0.977850174820, 
    1.250176790856, 0.098791845166, -1.069276441800, 
    1.194718157174, 0.251407364538, -1.174275392129, 
    1.127696183180, 0.431959397725, -1.295878193174, 
    1.046006454968, 0.647485610469, -1.438041695773, 
    0.945459855532, 0.907400624736, -1.606018804842, 
    0.820295736860, 1.224540947101, -1.806917563896, 
    0.662418669454, 1.616794995066, -2.050569262035, 
    0.460162432609, 2.109729648039, -2.350920816737, 
    0.196211605358, 2.740985157716, -2.728353889708, 
    -0.156051915958, 3.567962877198, -3.213722960014, 
    -0.639321234262, 4.682006534082, -3.855770086891, 
    -1.325757685059, 6.236312386687, -4.735651038017, 
    -2.345709388587, 8.505488022524, -5.997790945975, 
    -3.956059541908, 12.026617159136, -7.922628470498, 
    -6.727400789527, 17.983705080358, -11.123941286820, 
    -12.170909745654, 29.488929624542, -17.203344479111, 
    -25.631911490690, 57.466598393615, -31.741016484669, 
    -81.587305009103, 171.803399517566, -90.149831709374, 
    0.0, 0.0, 0.0
};

//
// End of File
//


