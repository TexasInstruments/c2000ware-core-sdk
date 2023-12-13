;;#############################################################################
;; FILE: CLASinCosTable.asm
;; 
;; DESCRIPTION: Sine and Cosine Tables
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
	
    .def    _CLAsincosTable
    .def    _CLAsinTable
    .def    _CLAsincosTable_Sin0
    .def    _CLAcosTable
    .def    _CLAsincosTable_Cos0
    .def    _CLAsinTableEnd
    .def    _CLAcosTableEnd
    .def    _CLAsincosTable_TABLE_SIZE             
    .def    _CLAsincosTable_TABLE_SIZEDivTwoPi    
    .def    _CLAsincosTable_TwoPiDivTABLE_SIZE  
    .def    _CLAsincosTable_TABLE_MASK       
    .def    _CLAsincosTable_Coef0
    .def    _CLAsincosTable_Coef1
    .def    _CLAsincosTable_Coef1_pos
    .def    _CLAsincosTable_Coef2
    .def    _CLAsincosTable_Coef3
    .def    _CLAsincosTable_Coef3_neg
    .def    _CLAsincosTableEnd
        
    .sect    "CLA1mathTables"

_CLAsincosTable:
_CLAsinTable:
_CLAsincosTable_Sin0:
   .float   0.0;                        ; sin(  0 * 2*pi/TABLE_SIZE)
   .float   0.04906767432742;           ; sin(  1 * 2*pi/TABLE_SIZE)
   .float   0.09801714032956;           ; sin(  2 * 2*pi/TABLE_SIZE)
   .float   0.1467304744553;            ; sin(  3 * 2*pi/TABLE_SIZE)
   .float   0.1950903220162;            ; sin(  4 * 2*pi/TABLE_SIZE)
   .float   0.2429801799032;            ; sin(  5 * 2*pi/TABLE_SIZE)
   .float   0.2902846772544;            ; sin(  6 * 2*pi/TABLE_SIZE)
   .float   0.3368898533922;            ; sin(  7 * 2*pi/TABLE_SIZE)
   .float   0.3826834323651;            ; sin(  8 * 2*pi/TABLE_SIZE)
   .float   0.4275550934303;            ; sin(  9 * 2*pi/TABLE_SIZE)
   .float   0.4713967368260;            ; sin( 10 * 2*pi/TABLE_SIZE)
   .float   0.5141027441932;            ; sin( 11 * 2*pi/TABLE_SIZE)
   .float   0.5555702330196;            ; sin( 12 * 2*pi/TABLE_SIZE)
   .float   0.5956993044925;            ; sin( 13 * 2*pi/TABLE_SIZE)
   .float   0.6343932841637;            ; sin( 14 * 2*pi/TABLE_SIZE)
   .float   0.6715589548470;            ; sin( 15 * 2*pi/TABLE_SIZE)
   .float   0.7071067811865;            ; sin( 16 * 2*pi/TABLE_SIZE)
   .float   0.7409511253549;            ; sin( 17 * 2*pi/TABLE_SIZE)
   .float   0.7730104533627;            ; sin( 18 * 2*pi/TABLE_SIZE)
   .float   0.8032075314806;            ; sin( 19 * 2*pi/TABLE_SIZE)
   .float   0.8314696123026;            ; sin( 20 * 2*pi/TABLE_SIZE)
   .float   0.8577286100001;            ; sin( 21 * 2*pi/TABLE_SIZE)
   .float   0.8819212643481;            ; sin( 22 * 2*pi/TABLE_SIZE)
   .float   0.9039892931235;            ; sin( 23 * 2*pi/TABLE_SIZE)
   .float   0.9238795325113;            ; sin( 24 * 2*pi/TABLE_SIZE)
   .float   0.9415440651832;            ; sin( 25 * 2*pi/TABLE_SIZE)
   .float   0.9569403357322;            ; sin( 26 * 2*pi/TABLE_SIZE)
   .float   0.9700312531945;            ; sin( 27 * 2*pi/TABLE_SIZE)
   .float   0.9807852804033;            ; sin( 28 * 2*pi/TABLE_SIZE)
   .float   0.9891765099649;            ; sin( 29 * 2*pi/TABLE_SIZE)
   .float   0.9951847266721;            ; sin( 30 * 2*pi/TABLE_SIZE)
   .float   0.9987954562052;            ; sin( 31 * 2*pi/TABLE_SIZE)

_CLAcosTable:
_CLAsincosTable_Cos0:
   .float   1.0;                        ; sin( 32 * 2*pi/TABLE_SIZE)
   .float   0.9987954562052;            ; sin( 33 * 2*pi/TABLE_SIZE)
   .float   0.9951847266721;            ; sin( 34 * 2*pi/TABLE_SIZE)
   .float   0.9891765099649;            ; sin( 35 * 2*pi/TABLE_SIZE)
   .float   0.9807852804033;            ; sin( 36 * 2*pi/TABLE_SIZE)
   .float   0.9700312531945;            ; sin( 37 * 2*pi/TABLE_SIZE)
   .float   0.9569403357322;            ; sin( 38 * 2*pi/TABLE_SIZE)
   .float   0.9415440651832;            ; sin( 39 * 2*pi/TABLE_SIZE)
   .float   0.9238795325113;            ; sin( 40 * 2*pi/TABLE_SIZE)
   .float   0.9039892931235;            ; sin( 41 * 2*pi/TABLE_SIZE)
   .float   0.8819212643481;            ; sin( 42 * 2*pi/TABLE_SIZE)
   .float   0.8577286100001;            ; sin( 43 * 2*pi/TABLE_SIZE)
   .float   0.8314696123026;            ; sin( 44 * 2*pi/TABLE_SIZE)
   .float   0.8032075314806;            ; sin( 45 * 2*pi/TABLE_SIZE)
   .float   0.7730104533627;            ; sin( 46 * 2*pi/TABLE_SIZE)
   .float   0.7409511253549;            ; sin( 47 * 2*pi/TABLE_SIZE)
   .float   0.7071067811865;            ; sin( 48 * 2*pi/TABLE_SIZE)
   .float   0.6715589548470;            ; sin( 49 * 2*pi/TABLE_SIZE)
   .float   0.6343932841637;            ; sin( 50 * 2*pi/TABLE_SIZE)
   .float   0.5956993044925;            ; sin( 51 * 2*pi/TABLE_SIZE)
   .float   0.5555702330196;            ; sin( 52 * 2*pi/TABLE_SIZE)
   .float   0.5141027441932;            ; sin( 53 * 2*pi/TABLE_SIZE)
   .float   0.4713967368260;            ; sin( 54 * 2*pi/TABLE_SIZE)
   .float   0.4275550934303;            ; sin( 55 * 2*pi/TABLE_SIZE)
   .float   0.3826834323651;            ; sin( 56 * 2*pi/TABLE_SIZE)
   .float   0.3368898533922;            ; sin( 57 * 2*pi/TABLE_SIZE)
   .float   0.2902846772544;            ; sin( 58 * 2*pi/TABLE_SIZE)
   .float   0.2429801799032;            ; sin( 59 * 2*pi/TABLE_SIZE)
   .float   0.1950903220162;            ; sin( 60 * 2*pi/TABLE_SIZE)
   .float   0.1467304744553;            ; sin( 61 * 2*pi/TABLE_SIZE)
   .float   0.09801714032956;           ; sin( 62 * 2*pi/TABLE_SIZE)
   .float   0.04906767432742;           ; sin( 63 * 2*pi/TABLE_SIZE)
   .float   0.0;                        ; sin( 64 * 2*pi/TABLE_SIZE)
   .float  -0.04906767432742;           ; sin( 65 * 2*pi/TABLE_SIZE)
   .float  -0.09801714032956;           ; sin( 66 * 2*pi/TABLE_SIZE)
   .float  -0.1467304744553;            ; sin( 67 * 2*pi/TABLE_SIZE)
   .float  -0.1950903220162;            ; sin( 68 * 2*pi/TABLE_SIZE)
   .float  -0.2429801799032;            ; sin( 69 * 2*pi/TABLE_SIZE)
   .float  -0.2902846772544;            ; sin( 70 * 2*pi/TABLE_SIZE)
   .float  -0.3368898533922;            ; sin( 71 * 2*pi/TABLE_SIZE)
   .float  -0.3826834323651;            ; sin( 72 * 2*pi/TABLE_SIZE)
   .float  -0.4275550934303;            ; sin( 73 * 2*pi/TABLE_SIZE)
   .float  -0.4713967368260;            ; sin( 74 * 2*pi/TABLE_SIZE)
   .float  -0.5141027441932;            ; sin( 75 * 2*pi/TABLE_SIZE)
   .float  -0.5555702330196;            ; sin( 76 * 2*pi/TABLE_SIZE)
   .float  -0.5956993044925;            ; sin( 77 * 2*pi/TABLE_SIZE)
   .float  -0.6343932841637;            ; sin( 78 * 2*pi/TABLE_SIZE)
   .float  -0.6715589548470;            ; sin( 79 * 2*pi/TABLE_SIZE)
   .float  -0.7071067811865;            ; sin( 80 * 2*pi/TABLE_SIZE)
   .float  -0.7409511253549;            ; sin( 81 * 2*pi/TABLE_SIZE)
   .float  -0.7730104533627;            ; sin( 82 * 2*pi/TABLE_SIZE)
   .float  -0.8032075314806;            ; sin( 83 * 2*pi/TABLE_SIZE)
   .float  -0.8314696123026;            ; sin( 84 * 2*pi/TABLE_SIZE)
   .float  -0.8577286100001;            ; sin( 85 * 2*pi/TABLE_SIZE)
   .float  -0.8819212643481;            ; sin( 86 * 2*pi/TABLE_SIZE)
   .float  -0.9039892931235;            ; sin( 87 * 2*pi/TABLE_SIZE)
   .float  -0.9238795325113;            ; sin( 88 * 2*pi/TABLE_SIZE)
   .float  -0.9415440651832;            ; sin( 89 * 2*pi/TABLE_SIZE)
   .float  -0.9569403357322;            ; sin( 90 * 2*pi/TABLE_SIZE)
   .float  -0.9700312531945;            ; sin( 91 * 2*pi/TABLE_SIZE)
   .float  -0.9807852804033;            ; sin( 92 * 2*pi/TABLE_SIZE)
   .float  -0.9891765099649;            ; sin( 93 * 2*pi/TABLE_SIZE)
   .float  -0.9951847266721;            ; sin( 94 * 2*pi/TABLE_SIZE)
   .float  -0.9987954562052;            ; sin( 95 * 2*pi/TABLE_SIZE)
   .float  -1.0;                        ; sin( 96 * 2*pi/TABLE_SIZE)
   .float  -0.9987954562052;            ; sin( 97 * 2*pi/TABLE_SIZE)
   .float  -0.9951847266721;            ; sin( 98 * 2*pi/TABLE_SIZE)
   .float  -0.9891765099649;            ; sin( 99 * 2*pi/TABLE_SIZE)
   .float  -0.9807852804033;            ; sin(100 * 2*pi/TABLE_SIZE)
   .float  -0.9700312531945;            ; sin(101 * 2*pi/TABLE_SIZE)
   .float  -0.9569403357322;            ; sin(102 * 2*pi/TABLE_SIZE)
   .float  -0.9415440651832;            ; sin(103 * 2*pi/TABLE_SIZE)
   .float  -0.9238795325113;            ; sin(104 * 2*pi/TABLE_SIZE)
   .float  -0.9039892931235;            ; sin(105 * 2*pi/TABLE_SIZE)
   .float  -0.8819212643481;            ; sin(106 * 2*pi/TABLE_SIZE)
   .float  -0.8577286100001;            ; sin(107 * 2*pi/TABLE_SIZE)
   .float  -0.8314696123026;            ; sin(108 * 2*pi/TABLE_SIZE)
   .float  -0.8032075314806;            ; sin(109 * 2*pi/TABLE_SIZE)
   .float  -0.7730104533627;            ; sin(110 * 2*pi/TABLE_SIZE)
   .float  -0.7409511253549;            ; sin(111 * 2*pi/TABLE_SIZE)
   .float  -0.7071067811865;            ; sin(112 * 2*pi/TABLE_SIZE)
   .float  -0.6715589548470;            ; sin(113 * 2*pi/TABLE_SIZE)
   .float  -0.6343932841637;            ; sin(114 * 2*pi/TABLE_SIZE)
   .float  -0.5956993044925;            ; sin(115 * 2*pi/TABLE_SIZE)
   .float  -0.5555702330196;            ; sin(116 * 2*pi/TABLE_SIZE)
   .float  -0.5141027441932;            ; sin(117 * 2*pi/TABLE_SIZE)
   .float  -0.4713967368260;            ; sin(118 * 2*pi/TABLE_SIZE)
   .float  -0.4275550934303;            ; sin(119 * 2*pi/TABLE_SIZE)
   .float  -0.3826834323651;            ; sin(120 * 2*pi/TABLE_SIZE)
   .float  -0.3368898533922;            ; sin(121 * 2*pi/TABLE_SIZE)
   .float  -0.2902846772544;            ; sin(122 * 2*pi/TABLE_SIZE)
   .float  -0.2429801799032;            ; sin(123 * 2*pi/TABLE_SIZE)
   .float  -0.1950903220162;            ; sin(124 * 2*pi/TABLE_SIZE)
   .float  -0.1467304744553;            ; sin(125 * 2*pi/TABLE_SIZE)
   .float  -0.09801714032956;           ; sin(126 * 2*pi/TABLE_SIZE)
   .float  -0.04906767432742;           ; sin(127 * 2*pi/TABLE_SIZE)
_CLAsinTableEnd:
   .float   0.0;                        ; sin(  0 * 2*pi/TABLE_SIZE)
   .float   0.04906767432742;           ; sin(  1 * 2*pi/TABLE_SIZE)
   .float   0.09801714032956;           ; sin(  2 * 2*pi/TABLE_SIZE)
   .float   0.1467304744553;            ; sin(  3 * 2*pi/TABLE_SIZE)
   .float   0.1950903220162;            ; sin(  4 * 2*pi/TABLE_SIZE)
   .float   0.2429801799032;            ; sin(  5 * 2*pi/TABLE_SIZE)
   .float   0.2902846772544;            ; sin(  6 * 2*pi/TABLE_SIZE)
   .float   0.3368898533922;            ; sin(  7 * 2*pi/TABLE_SIZE)
   .float   0.3826834323651;            ; sin(  8 * 2*pi/TABLE_SIZE)
   .float   0.4275550934303;            ; sin(  9 * 2*pi/TABLE_SIZE)
   .float   0.4713967368260;            ; sin( 10 * 2*pi/TABLE_SIZE)
   .float   0.5141027441932;            ; sin( 11 * 2*pi/TABLE_SIZE)
   .float   0.5555702330196;            ; sin( 12 * 2*pi/TABLE_SIZE)
   .float   0.5956993044925;            ; sin( 13 * 2*pi/TABLE_SIZE)
   .float   0.6343932841637;            ; sin( 14 * 2*pi/TABLE_SIZE)
   .float   0.6715589548470;            ; sin( 15 * 2*pi/TABLE_SIZE)
   .float   0.7071067811865;            ; sin( 16 * 2*pi/TABLE_SIZE)
   .float   0.7409511253549;            ; sin( 17 * 2*pi/TABLE_SIZE)
   .float   0.7730104533627;            ; sin( 18 * 2*pi/TABLE_SIZE)
   .float   0.8032075314806;            ; sin( 19 * 2*pi/TABLE_SIZE)
   .float   0.8314696123026;            ; sin( 20 * 2*pi/TABLE_SIZE)
   .float   0.8577286100001;            ; sin( 21 * 2*pi/TABLE_SIZE)
   .float   0.8819212643481;            ; sin( 22 * 2*pi/TABLE_SIZE)
   .float   0.9039892931235;            ; sin( 23 * 2*pi/TABLE_SIZE)
   .float   0.9238795325113;            ; sin( 24 * 2*pi/TABLE_SIZE)
   .float   0.9415440651832;            ; sin( 25 * 2*pi/TABLE_SIZE)
   .float   0.9569403357322;            ; sin( 26 * 2*pi/TABLE_SIZE)
   .float   0.9700312531945;            ; sin( 27 * 2*pi/TABLE_SIZE)
   .float   0.9807852804033;            ; sin( 28 * 2*pi/TABLE_SIZE)
   .float   0.9891765099649;            ; sin( 29 * 2*pi/TABLE_SIZE)
   .float   0.9951847266721;            ; sin( 30 * 2*pi/TABLE_SIZE)
   .float   0.9987954562052;            ; sin( 31 * 2*pi/TABLE_SIZE)
   .float   1.0;                        ; sin( 32 * 2*pi/TABLE_SIZE)
_CLAcosTableEnd:


_CLAsincosTable_TABLE_SIZE         .float  128.0             
_CLAsincosTable_TABLE_SIZEDivTwoPi .float  20.37183271576    
_CLAsincosTable_TwoPiDivTABLE_SIZE .float  0.04908738521234  
_CLAsincosTable_TABLE_MASK         .long   0x0000007F;       
_CLAsincosTable_Coef0              .float -0.5;
_CLAsincosTable_Coef1              .float -0.1666666666666;
_CLAsincosTable_Coef1_pos          .float  0.1666666666666;
_CLAsincosTable_Coef2              .float  4.1666666666666e-2;
_CLAsincosTable_Coef3              .float  8.3333333333333e-3;
_CLAsincosTable_Coef3_neg          .float -8.3333333333333e-3;
_CLAsincosTableEnd:

 ;; End of File
