;;#############################################################################
;; FILE: CLAasineTable.asm
;; 
;; DESCRIPTION: asine Tables
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
	
    .def    _CLAasinHalfPITable 
    .def    _CLAasinTable
    .def    _CLAasinTableEnd

   .sect    "CLA1mathTables"

_CLAasinHalfPITable:
    .float   2.0    ; 2.0
    .float   1.570796327    ; PI/2

_CLAasinTable:

    .float  0.0
    .float  1.0
    .float  0.0
    .float  0.000000636202          
    .float  0.999877862610          
    .float  0.007815361896   
    .float  0.000005099694          
    .float  0.999510644409          
    .float  0.015647916155   
    .float  0.000017268312          
    .float  0.998895919094          
    .float  0.023514960332   
    .float  0.000041121765          
    .float  0.998029615282          
    .float  0.031434003631   
    .float  0.000080794520          
    .float  0.996905974725          
    .float  0.039422875916   
    .float  0.000140631089          
    .float  0.995517492804          
    .float  0.047499840611   
    .float  0.000225244584          
    .float  0.993854840311          
    .float  0.055683712914   
    .float  0.000339579512          
    .float  0.991906765146          
    .float  0.063993984848   
    .float  0.000488979852          
    .float  0.989659972212          
    .float  0.072450958820   
    .float  0.000679263611          
    .float  0.987098979366          
    .float  0.081075891529   
    .float  0.000916805182          
    .float  0.984205946802          
    .float  0.089891150305   
    .float  0.001208627040          
    .float  0.980960476685          
    .float  0.098920384204   
    .float  0.001562502549          
    .float  0.977339379243          
    .float  0.108188712551   
    .float  0.001987071928          
    .float  0.973316400729          
    .float  0.117722933997   
    .float  0.002491973784          
    .float  0.968861907789          
    .float  0.127551759665   
    .float  0.003087995053          
    .float  0.963942521723          
    .float  0.137706074532   
    .float  0.003787242692          
    .float  0.958520694794          
    .float  0.148219231941   
    .float  0.004603341138          
    .float  0.952554219267          
    .float  0.159127386977   
    .float  0.005551660294          
    .float  0.945995657913          
    .float  0.170469875522   
    .float  0.006649579796          
    .float  0.938791682505          
    .float  0.182289647088   
    .float  0.007916796475          
    .float  0.930882303984          
    .float  0.194633761132   
    .float  0.009375683410          
    .float  0.922199974574          
    .float  0.207553958472   
    .float  0.011051710808          
    .float  0.912668537890          
    .float  0.221107321885   
    .float  0.012973941175          
    .float  0.902201997769          
    .float  0.235357042896   
    .float  0.015175614174          
    .float  0.890703070035          
    .float  0.250373315541   
    .float  0.017694840102          
    .float  0.878061473098          
    .float  0.266234382514   
    .float  0.020575425537          
    .float  0.864151902887          
    .float  0.283027765009   
    .float  0.023867860513          
    .float  0.848831624374      
    .float  0.300851714968   
    .float  0.027630504055          
    .float  0.831937595031          
    .float  0.319816937941   
    .float  0.031931014547          
    .float  0.813283013821          
    .float  0.340048646894   
    .float  0.036848083955          
    .float  0.792653161200          
    .float  0.361689022958   
    .float  0.042473551274          
    .float  0.769800358920          
    .float  0.384900179460   
    .float  0.048914992206          
    .float  0.744437830278          
    .float  0.409867752228   
    .float  0.056298910750          
    .float  0.716232177740          
    .float  0.436805274317   
    .float  0.064774696786          
    .float  0.684794109766          
    .float  0.465959540059   
    .float  0.074519565699          
    .float  0.649666934178          
    .float  0.497617226179   
    .float  0.085744766889          
    .float  0.610312179660          
    .float  0.532113122767   
    .float  0.098703445606          
    .float  0.566091493186          
    .float  0.569840443472   
    .float  0.113700678529          
    .float  0.516243664372          
    .float  0.611263845480   
    .float  0.131106395009          
    .float  0.459855210927          
    .float  0.656936015611   
    .float  0.151372169232          
    .float  0.395822366759          
    .float  0.707518998893   
    .float  0.175053263659          
    .float  0.322801460177          
    .float  0.763811905770   
    .float  0.202837883870          
    .float  0.239143420888          
    .float  0.826787304376   
    .float  0.235586468765          
    .float  0.142806299514          
    .float  0.897639596948   
    .float  0.274385149825          
    .float  0.031236880585          
    .float  0.977850174820   
    .float  0.320619535938          
    .float  -0.098791845166         
    .float  1.069276441800   
    .float  0.376078169620          
    .float  -0.251407364538         
    .float  1.174275392129   
    .float  0.443100143614          
    .float  -0.431959397725         
    .float  1.295878193174   
    .float  0.524789871827          
    .float  -0.647485610469         
    .float  1.438041695773   
    .float  0.625336471263          
    .float  -0.907400624736         
    .float  1.606018804842   
    .float  0.750500589935          
    .float  -1.224540947101         
    .float  1.806917563896   
    .float  0.908377657341          
    .float  -1.616794995066         
    .float  2.050569262035   
    .float  1.110633894185          
    .float  -2.109729648039         
    .float  2.350920816737   
    .float  1.374584721437          
    .float  -2.740985157716         
    .float  2.728353889708   
    .float  1.726848242753          
    .float  -3.567962877198         
    .float  3.213722960014   
    .float  2.210117561056          
    .float  -4.682006534082         
    .float  3.855770086891   
    .float  2.896554011854          
    .float  -6.236312386687         
    .float  4.735651038017   
    .float  3.916505715382          
    .float  -8.505488022524         
    .float  5.997790945975   
    .float  5.526855868703          
    .float  -12.026617159136            
    .float  7.922628470498   
    .float  8.298197116322          
    .float  -17.983705080358            
    .float  11.123941286820  
    .float  13.741706072449         
    .float  -29.488929624542            
    .float  17.203344479111  
    .float  27.202707817485         
    .float  -57.466598393615            
    .float  31.741016484669  
    .float  83.158101335898         
    .float  -171.803399517566           
    .float  90.149831709374  

    .float  1.5707963267948966192313216916398
    .float  0
    .float  0 
     
_CLAasinTableEnd:

 ;; End of File
