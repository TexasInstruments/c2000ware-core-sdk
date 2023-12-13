;;#############################################################################
;; FILE: CLAacosineTable.asm
;; 
;; DESCRIPTION: acosine Tables
;; 
;; Group:            C2000
;; Target Family:    C28x+CLA
;;
;;#############################################################################
;;!
;;! Copyright: Copyright (C) 2023 Texas Instruments Incorporated -
;;!	All rights reserved not granted herein.
;;!	Limited License.
;;!
;;! Texas Instruments Incorporated grants a world-wide, royalty-free,
;;! non-exclusive license under copyrights and patents it now or hereafter
;;! owns or controls to make, have made, use, import, offer to sell and sell
;;! ("Utilize") this software subject to the terms herein. With respect to the
;;! foregoing patent license, such license is granted solely to the extent that
;;! any such patent is necessary to Utilize the software alone. The patent
;;! license shall not apply to any combinations which include this software,
;;! other than combinations with devices manufactured by or for TI 
;;! ("TI Devices").
;;! No hardware patent is licensed hereunder.
;;!
;;! Redistributions must preserve existing copyright notices and reproduce this
;;! license (including the above copyright notice and the disclaimer and
;;! (if applicable) source code license limitations below) in the documentation
;;!  and/or other materials provided with the distribution.
;;!
;;! Redistribution and use in binary form, without modification, are permitted
;;! provided that the following conditions are met:
;;!
;;! * No reverse engineering, decompilation, or disassembly of this software is 
;;! permitted with respect to any software provided in binary form.
;;! * Any redistribution and use are licensed by TI for use only 
;;!   with TI Devices.
;;! * Nothing shall obligate TI to provide you with source code for the 
;;!   software licensed and provided to you in object code.
;;!
;;! If software source code is provided to you, modification and redistribution
;;! of the source code are permitted provided that the following conditions 
;;! are met:
;;!
;;! * any redistribution and use of the source code, including any resulting
;;!   derivative works, are licensed by TI for use only with TI Devices.
;;! * any redistribution and use of any object code compiled from the source
;;!   code and any resulting derivative works, are licensed by TI for use 
;;!   only with TI Devices.
;;!
;;! Neither the name of Texas Instruments Incorporated nor the names of its
;;! suppliers may be used to endorse or promote products derived from this 
;;! software without specific prior written permission.
;;#############################################################################

    .include "CLAeabi.asm"

    .def    _CLAacosinHalfPITable
    .def    _CLAacosinTable
    .def    _CLAacosinTableEnd
    
   .sect    "CLA1mathTables"
   
_CLAacosinHalfPITable:
    .float   2.0    ; 2.0
    .float   3.141592653589 ; PI

_CLAacosinTable:
    .float  1.570795690593  ;       
    .float  -0.999877862610 ;       
    .float  -0.007815361896 ;
    .float  1.570791227101  ;       
    .float  -0.999510644409 ;       
    .float  -0.015647916155 ;
    .float  1.570779058483  ;       
    .float  -0.998895919094 ;       
    .float  -0.023514960332 ;
    .float  1.570755205030  ;       
    .float  -0.998029615282 ;       
    .float  -0.031434003631 ;
    .float  1.570715532275  ;       
    .float  -0.996905974725 ;       
    .float  -0.039422875916 ;
    .float  1.570655695706  ;       
    .float  -0.995517492804 ;       
    .float  -0.047499840611 ;
    .float  1.570571082211  ;       
    .float  -0.993854840311 ;       
    .float  -0.055683712914 ;
    .float  1.570456747283  ;       
    .float  -0.991906765146 ;       
    .float  -0.063993984848 ;
    .float  1.570307346943  ;       
    .float  -0.989659972212 ;       
    .float  -0.072450958820 ;
    .float  1.570117063183  ;       
    .float  -0.987098979366 ;       
    .float  -0.081075891529 ;
    .float  1.569879521613  ;       
    .float  -0.984205946802 ;       
    .float  -0.089891150305 ;
    .float  1.569587699755  ;       
    .float  -0.980960476685 ;       
    .float  -0.098920384204 ;
    .float  1.569233824246  ;       
    .float  -0.977339379243 ;       
    .float  -0.108188712551 ;
    .float  1.568809254867  ;       
    .float  -0.973316400729 ;       
    .float  -0.117722933997 ;
    .float  1.568304353010  ;       
    .float  -0.968861907789 ;       
    .float  -0.127551759665 ;
    .float  1.567708331742  ;       
    .float  -0.963942521723 ;       
    .float  -0.137706074532 ;
    .float  1.567009084103  ;       
    .float  -0.958520694794 ;       
    .float  -0.148219231941 ;
    .float  1.566192985657  ;       
    .float  -0.952554219267 ;       
    .float  -0.159127386977 ;
    .float  1.565244666501  ;       
    .float  -0.945995657913 ;       
    .float  -0.170469875522 ;
    .float  1.564146746998  ;       
    .float  -0.938791682505 ;       
    .float  -0.182289647088 ;
    .float  1.562879530320  ;       
    .float  -0.930882303984 ;       
    .float  -0.194633761132 ;
    .float  1.561420643385  ;       
    .float  -0.922199974574 ;       
    .float  -0.207553958472 ;
    .float  1.559744615987  ;       
    .float  -0.912668537890 ;       
    .float  -0.221107321885 ;
    .float  1.557822385620  ;       
    .float  -0.902201997769 ;       
    .float  -0.235357042896 ;
    .float  1.555620712621  ;       
    .float  -0.890703070035 ;       
    .float  -0.250373315541 ;
    .float  1.553101486693  ;       
    .float  -0.878061473098 ;       
    .float  -0.266234382514 ;
    .float  1.550220901258  ;       
    .float  -0.864151902887 ;       
    .float  -0.283027765009 ;
    .float  1.546928466282  ;       
    .float  -0.848831624374 ;       
    .float  -0.300851714968 ;
    .float  1.543165822740  ;       
    .float  -0.831937595031 ;       
    .float  -0.319816937941 ;
    .float  1.538865312248  ;       
    .float  -0.813283013821 ;       
    .float  -0.340048646894 ;
    .float  1.533948242840  ;       
    .float  -0.792653161200 ;       
    .float  -0.361689022958 ;
    .float  1.528322775521  ;       
    .float  -0.769800358920 ;       
    .float  -0.384900179460 ;
    .float  1.521881334589  ;       
    .float  -0.744437830278 ;       
    .float  -0.409867752228 ;
    .float  1.514497416045  ;       
    .float  -0.716232177740 ;       
    .float  -0.436805274317 ;
    .float  1.506021630009  ;       
    .float  -0.684794109766 ;       
    .float  -0.465959540059 ;
    .float  1.496276761095  ;       
    .float  -0.649666934178 ;       
    .float  -0.497617226179 ;
    .float  1.485051559906  ;       
    .float  -0.610312179660 ;       
    .float  -0.532113122767 ;
    .float  1.472092881189  ;       
    .float  -0.566091493186 ;       
    .float  -0.569840443472 ;
    .float  1.457095648266  ;       
    .float  -0.516243664372 ;       
    .float  -0.611263845480 ;
    .float  1.439689931785  ;       
    .float  -0.459855210927 ;       
    .float  -0.656936015611 ;
    .float  1.419424157563  ;       
    .float  -0.395822366759 ;       
    .float  -0.707518998893 ;
    .float  1.395743063136  ;       
    .float  -0.322801460177 ;       
    .float  -0.763811905770 ;
    .float  1.367958442925  ;       
    .float  -0.239143420888 ;       
    .float  -0.826787304376 ;
    .float  1.335209858030  ;       
    .float  -0.142806299514 ;       
    .float  -0.897639596948 ;
    .float  1.296411176970  ;       
    .float  -0.031236880585 ;       
    .float  -0.977850174820 ;
    .float  1.250176790856  ;       
    .float  0.098791845166  ;       
    .float  -1.069276441800 ;
    .float  1.194718157174  ;       
    .float  0.251407364538  ;       
    .float  -1.174275392129 ;
    .float  1.127696183180  ;       
    .float  0.431959397725  ;       
    .float  -1.295878193174 ;
    .float  1.046006454968  ;       
    .float  0.647485610469  ;       
    .float  -1.438041695773 ;
    .float  0.945459855532  ;       
    .float  0.907400624736  ;       
    .float  -1.606018804842 ;
    .float  0.820295736860  ;       
    .float  1.224540947101  ;       
    .float  -1.806917563896 ;
    .float  0.662418669454  ;       
    .float  1.616794995066  ;       
    .float  -2.050569262035 ;
    .float  0.460162432609  ;       
    .float  2.109729648039  ;       
    .float  -2.350920816737 ;
    .float  0.196211605358  ;       
    .float  2.740985157716  ;       
    .float  -2.728353889708 ;
    .float  -0.156051915958 ;       
    .float  3.567962877198  ;       
    .float  -3.213722960014 ;
    .float  -0.639321234262 ;       
    .float  4.682006534082  ;       
    .float  -3.855770086891 ;
    .float  -1.325757685059 ;       
    .float  6.236312386687  ;       
    .float  -4.735651038017 ;
    .float  -2.345709388587 ;       
    .float  8.505488022524  ;       
    .float  -5.997790945975 ;
    .float  -3.956059541908 ;       
    .float  12.026617159136 ;       
    .float  -7.922628470498 ;
    .float  -6.727400789527 ;       
    .float  17.983705080358 ;       
    .float  -11.123941286820;
    .float  -12.170909745654;   
    .float  29.488929624542 ;       
    .float  -17.203344479111;
    .float  -25.631911490690;       
    .float  57.466598393615 ;       
    .float  -31.741016484669;
    .float  -81.587305009103;       
    .float  171.803399517566;       
    .float  -90.149831709374;
    .float  0.0;        
    .float  0.0;        
    .float  0.0;
_CLAacosinTableEnd:

 ;; End of File
